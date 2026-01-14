# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/myapp/
WORKDIR /usr/src/myapp
RUN rm -rf build

# This command compiles your app using GCC, adjust for your source code
RUN apt update && apt upgrade
RUN apt install -y meson ninja-build python3 python3-dev
RUN mkdir build 
RUN meson setup build
WORKDIR '/usr/src/myapp/build'
RUN meson compile
RUN ./myapp-dynamic

RUN bash

LABEL Name=libtools Version=0.0.1
