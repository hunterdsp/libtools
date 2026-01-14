#!/bin/sh -eu

curdir="$(pwd)"
rm -rf build
mkdir build
LDFLAGS=-static-libstdc++ ~/meson/meson.py build --buildtype=release \
    --prefix=/tmp/myapp --libdir=lib --strip
ninja -C build install
rm -rf build
cd /tmp/
tar czf myapp.tar.gz myapp
mv myapp.tar.gz "${curdir}"
rm -rf myapp