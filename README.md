# libtools

Using native libraries.

Experimenting with and capturing - via runnable example - the different ways to
interact with compiled code.

## Installation & Usage

[Get `uv`](https://docs.astral.sh/uv/getting-started/installation/), clone, and
install dependencies

```{console=}
curl -LsSf https://astral.sh/uv/install.sh | sh
git clone https://github.com/hunterdsp/libtools.git
cd libtools
uv sync
```

Each example is runnable via Bash script:

```{console=}
./buildme -t TYPE . 
```

Where `TYPE` is one of:

- STATIC (These are built-in - i.e. fixed at compile-time.)
- SHARED (Loadable at run-time and accessible to all.)
- DYNAMIC (Loadable aytime.)
- LLVM (Python llvmlite-generated ELF object called from C application.)
- PYTHON (extension)
- EXE (-cutable)
- CFFI (Python C extension module built with Foreign Function Interface.)
- CFFIC (C code calling pure Python.)

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
