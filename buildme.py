#!#/usr/bin/env python
# /// script
# requires-python = ">=3.12"
# dependencies = [
#     "libtools",
# ]
#
# [tool.uv.sources]
# libtools = { path = "." }
# ///

import sys
import subprocess
from pathlib import Path

def main():
    script = Path(__file__).parent.joinpath('buildme')
    subprocess.call([f"{str(script)}", *sys.argv[1:]])

if __name__ == "__main__":
    main()
