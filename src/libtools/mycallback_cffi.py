import cffi
from pathlib import Path
from libtools import import_from_path

ffibuilder = cffi.FFI()

# Declare a pure python function we want to call from C
ffibuilder.cdef("""
    extern "Python" int f(int);
    int my_algo(int);
""")

# The C code that calls the Python function "f"
ffibuilder.set_source(
    "_example_cffi",
    r"""
    static int f(int);   /* the forward declaration */

    static int my_algo(int n) {
        int i, sum = 0;
        printf("From C implementation...\n");
        for (i = 0; i < n; i++)
            sum += f(i);     /* call f() here */
        return sum;
    }
""",
)

# Write the Python code to be embedded in C
ffibuilder.embedding_init_code(r"""

    import sys
    from _example_cffi import ffi, lib

    @ffi.def_extern()
    def f(x):
        print("squaring %d" % (x))
        sys.stdout.flush()
        return x ** 2
    print("From Python Embedded in C code:")
    x = lib.my_algo(3)
    print('<<< %d >>>' % (x,))

""")

fn = ffibuilder.compile(
    tmpdir=Path(__file__).parent.parent.parent.joinpath("build/lib"),
    verbose=True,
)
print("FILENAME: %s" % (fn,))

modname = "_example_cffi"
modpath = fn
mod = import_from_path(fn)
mod.lib.my_algo(x := 2)
print("XXX %d XXX" % (x,))
