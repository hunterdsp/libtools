if __name__ == "__main__":
    from cffi import FFI
    from pathlib import Path

    # Define the different dirs
    cmpdir = Path("__file__").parent
    blddir = cmpdir.parent.joinpath("build")
    libdir = blddir.joinpath("lib")
    incdir = cmpdir.parent.joinpath("inc")

    # C-to-Python Module builder
    ffibuilder = FFI()

    # Module export names (implementation in "sources").
    # Exposed in Python as top-level module attributes.
    ffibuilder.cdef("float pi_approx(int n);")

    # Module sources (C code)
    include_header_c_code_literally = '#include "mylib-cffi.h"'
    module_c_sources = [  # implementation of cdef's in here
        str(cmpdir.joinpath("src/mylib-cffi.c"))
    ]

    # Extension module definition
    module_import_name = "mylib_cffi"  # Bare-names
    ffibuilder.set_source(
        module_import_name,
        include_header_c_code_literally,
        sources=module_c_sources,
        # External libs for to link with, e.g. "libm" here
        libraries=["m"],
        library_dirs=[str(libdir)],
        include_dirs=[str(incdir)],
    )

    # Beuild the module => f"{ext_module_import_name}.lib.so"
    # ...which is imported as:
    #   import <ext_module_import_name>.lib as mod
    #   myfunction = mod.<cdef>
    # So for thiss example:
    #   import mylib_cffi.lib as mod
    #   myfunction = mod.pi_approx
    ffibuilder.compile(target=str(libdir.joinpath("mylib_cffi.so")))

    # Clean-up object files
    for obj in module_c_sources:
        Path(obj).with_suffix(".o").unlink(missing_ok=True)
