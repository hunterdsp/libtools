#!/bin/bash

cd "${0%/*}" || ecit 1
LD_LIBRARY_PATH="$(pwd)/lib"
export LD_LIBRARY_PATH
bin/myapp