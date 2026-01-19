# libtools

__dead-simple__ native library creation.

```{console=}
buildme -t TYPE . 
```

Where `TYPE` is one of:

- STATIC (These are built-in - i.e. fixed at compile-time.)
- SHARED (Loadable at run-time and accessible to all.)
- DYNAMIC (Loadable aytime.)
- PYTHON (extension)
- EXE (-cutable)

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

## Intallation & Usage

```{console=}
# Run the following and add to [e.g.] .bashrc
LIBTOOLS="${HOME}/libtools" && export PATH=$PATH:$LIBTOOLS

# Clone the repo
git clone git@github.com:hunterdsp/libtools.git $LIBTOOLS

# Run
buildme -t EXE
```
