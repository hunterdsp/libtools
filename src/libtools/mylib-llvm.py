"""LLVM Module."""

from pathlib import Path

from ctypes import CFUNCTYPE, c_int32

from llvmlite import ir

from llvmlite import binding as llvm

libname = "mylib-llvm.o"
modname = "mylib_llvm_m"
funcname = "mylib_llvm_f"
libpath = Path(__file__).parent.parent.parent.joinpath(f"build/{libname}")


def init():
    """Initialize & create code generation machinery."""

    llvm.initialize_native_target()

    llvm.initialize_native_asmprinter()


def construct_lljit_compiler():
    """Build lljit compiler."""

    # Create a target machine representing the host

    target = llvm.Target.from_default_triple()

    target_machine = target.create_target_machine(jit=False)

    # Create compiler

    lljit = llvm.create_lljit_compiler(target_machine)

    return lljit, target_machine


def llvm_module(modname, funcname):
    """Build some function to ship using LLVMIR."""

    module = ir.Module(modname)

    # Function typing

    i32 = ir.IntType(32)

    fnty = ir.FunctionType(i32, (i32, i32))

    # Attach to parent module

    func = ir.Function(module, fnty, name=funcname)

    # Function definition

    block = func.append_basic_block()

    builder = ir.IRBuilder(block)

    a, b = func.args

    result = builder.mul(a, b)

    builder.ret(result)

    return module


if __name__ == "__main__":
    # Create & initialize compiler engine

    init()

    lljit, lljit_tm = construct_lljit_compiler()

    # Create a module

    ir_mod = llvm_module(modname, funcname)

    mod = llvm.parse_assembly(str(ir_mod))

    mod.verify()

    # Compile to machine code and write object to file - then link in to lib

    binary = lljit_tm.emit_object(mod)

    lib = llvm.JITLibraryBuilder()

    with open(libpath, mode="wb+") as fp:
        fp.write(binary)

        fp.close()

        del binary

        # Now add the object file to the library and link!

        lib.add_object_file(fp.name)

        lib.export_symbol(funcname)

        lljit_rt = lib.link(lljit, funcname)

    # Access the function via ctypes

    lljit_cfunc = CFUNCTYPE(c_int32, c_int32, c_int32)(lljit_rt[funcname])

    # Test
    a, b = -2, 5
    expected = a * b
    lljit_res = lljit_cfunc(a, b)
    assert expected == lljit_res
