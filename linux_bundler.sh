#!/bin/sh -eu

libdir="${MESON_INSTALL_PREFIX}/lib"
mkdir -p "${libdir}"
myapp=$(ldd "${MESON_INSTALL_PREFIX}/bin/myapp")
$myapp "${libdir}"