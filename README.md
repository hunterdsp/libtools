# libtools

__dead-simple__ *native library creation.

After install run `buildme -t TYPE`. Where `TYPE` is one of:

- EXE (-cutable)
- STATIC (.o)
- SHARED (.so)
- DYNAMIC (-ally loadable) (.so usable with :func:`dlopen`)
- PYTHON (extension)

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

## Intstallation

One time procedure:

```{console=}
git clone git@github.com:hunterdsp/libtools.git

```

## Development

After installation you can edit the code and as long as the run-time is left alone. No other steps are necessary.