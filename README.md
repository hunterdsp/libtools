# libtools

__simple__ native library creation examples.

```{console=}
buildme -t TYPE . 
```

Where `TYPE` is one of:

- STATIC (These are built-in - i.e. fixed at compile-time.)
- SHARED (Loadable at run-time and accessible to all.)
- DYNAMIC (Loadable aytime.)
- LLVM (Python llvmlite-generated ELF object called from C application.)
- PYTHON (extension)
- EXE (-cutable)
- CFFI (Python C extension module built with Foreign Function Interface.)

For example

```{console=}
buildme -t STATIC
```

should output something like:

```{console}
Building static library!
Building application & linking in library!
Running the application: 10 + 5 = 15
Cleaning up!!!
```

## Installation & Usage

Clone the repo and (from the project root) run e.g.

```{console=}
uv sync
```
