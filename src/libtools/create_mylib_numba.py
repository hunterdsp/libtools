from pathlib import Path
from numba.pycc import CC

mname = "mylib_numba"
cc = CC(mname)
cc.output_dir =  Path(__file__).parent.parent.parent.joinpath("build/lib")


@cc.export("multf", "f8(f8, f8)")
@cc.export("multi", "i4(i4, i4)")
def mult(a, b):
    return a * b


@cc.export("square", "f8(f8)")
def square(a):
    return a**2


if __name__ == "__main__":
    cc.compile()
    from libtools import import_from_path

    thisdir = Path(__file__).parent.parent.parent.joinpath("build/lib")
    so_file = f"{mname}.cpython-312-x86_64-linux-gnu.so"
    import_from_path(str(thisdir.joinpath(so_file)), f"{mname}")

    from mylib_numba import square

    print(f"Numba JIT function result from AOT compiled lib: {square(5)}")
