# libtools

Experimenting with and capturing - via runnable example - different ways to
interact with native code on Linux.

## Installation & Usage

From the top-level directory you can run

```{console=}
./buildme -t TYPE
```

Where `TYPE` is one of:

- EXE (-cutable)
- STATIC (These are built-in - i.e. fixed at compile-time.)
- SHARED (Loadable at run-time and accessible to all.)
- DYNAMIC (Loadable aytime.)
- PYTHON (extension)
- LLVM (Python llvmlite-generated ELF object called from C application.)
- CFFI (Python C extension module built with Foreign Function Interface.)
- CFFI-CALLBACK (C code calling pure Python.)
- NUMBA (Calling JIT compiled code embedded in AOT compiled lib.)
- NUMBA-CALLBACK (C code calling pure Python and JIT code.)

For example

```{console=}
./buildme -t STATIC
```

should output something like:

```{console}
Building static library!
Building application & linking in library!
Running the application: 10 + 5 = 15
Cleaning up!!!
```
