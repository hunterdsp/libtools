import shutil
import pytest
from pathlib import Path
from libtools import TYPES
from subprocess import check_call


# Verify all app selections run from scratch without error
appname = "buildme"
apppath = Path(__file__).parent.parent.joinpath(appname)
distdpath = apppath.parent.joinpath("dist")
buildpath = apppath.parent.joinpath("build")
builddirpath = apppath.parent.joinpath("builddir")
temppaths = [distdpath, buildpath, builddirpath]


@pytest.mark.parametrize("TYPE", TYPES)
def test_target(TYPE):
    for p in temppaths:
        shutil.rmtree(p, True)
        assert not p.exists()

    check_call(["uv", "run", f"{str(apppath)}", "-t", TYPE])
