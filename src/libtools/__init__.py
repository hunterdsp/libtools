"""Some useful tools."""

from pathlib import Path
from importlib.util import spec_from_loader, module_from_spec
from importlib.machinery import (
    ExtensionFileLoader,
    SourceFileLoader,
    SourcelessFileLoader,
)

TYPES = ["STATIC", "SHARED", "DYNAMIC", "LLVM", "PYTHON", "EXE", "CFFI", "CFFIC"]


def import_from_path(modpath, modname=None):
    """Import source, extension, or other sourceless module from path."""

    # Try different loaders
    loaders = [SourceFileLoader, SourcelessFileLoader, ExtensionFileLoader]

    # Use the filename if no modname is given
    if modname is None:
        modname = Path(modpath).name.split(".")[0]

    for loader in loaders:
        spec = spec_from_loader(modname, loader(modname, modpath))
        mod = module_from_spec(spec)

        # Suppress expected errors if not an extension moduke
        try:
            spec.loader.exec_module(mod)
        except (SyntaxError, ImportError):
            mod = None

        # Exit if the module made it through import
        if mod is not None:
            break

    return mod
