def main() -> str:
    from pathlib import Path

    import subprocess
    import os

    def install_wheel(wheel_path):
        """Installs a .whl file from a specific file path using pip."""
        # Ensure the path is absolute for reliability
        abs_wheel_path = os.path.abspath(wheel_path)

        print(f"Attempting to install: {abs_wheel_path}")
        try:
            # Run pip install command
            subprocess.check_call(["uv", "pip", "install", abs_wheel_path])
            print(f"Successfully installed: {abs_wheel_path}")
        except subprocess.CalledProcessError as e:
            print(f"Failed to install the wheel file: {e}")
            # Handle installation error if necessary

    projectpath = Path(__file__).parent.parent.parent
    buildpath = projectpath.joinpath("dist")
    whlpath = buildpath.joinpath("ext_cxx-0.1.0-cp312-cp312-linux_x86_64.whl")
    print(whlpath)
    install_wheel(whlpath)

    from importlib import import_module
    from nanobind.stubgen import StubGen, load_pattern_file

    ext_cxx = import_module("ext_cxx")
    from ext_cxx import __init__
    from __init__ import __all__

    output_file = projectpath.joinpath("ext-cxx/src/ext_cxx/_core.pyi")
    sg = StubGen(
        ext_cxx,
        recursive=False,
        output_file=output_file,
        patterns=load_pattern_file(
            str(projectpath.joinpath("ext-cxx/buildscripts/patternfile"))
        ),
    )
    for modname in __all__:
        mod = getattr(ext_cxx, modname)
        sg.put(mod, modname, ext_cxx)
        stub = sg.get()
        print(f"generated {modname} stub")
        print("######################################")
        print(f"{stub}")
        for pattern in sg.patterns:
            found = sg.apply_pattern(modname, mod)
            if found:
                print(f"{str(pattern)} stub matched!")
    sg.output_file.write_text(stub)


if __name__ == "__main__":
    main()
