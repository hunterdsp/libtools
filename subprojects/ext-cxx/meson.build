# The first function called in each project, to initialize Meson
project(
  # Arguments
  # ---------
  'ext-cxx',      # The name of the project
  'c', 'cpp',      # The languages that Meson should initialize

  # Keyword arguments:
  # ------------------
  # Strings in the form `key=value`
  default_options : ['cpp_std=c++17', 'buildtype=debugoptimized'],
  # String or array of strings describing the license(s) the code is under
  license         : 'MIT',                                
  # Takes a string or array of strings with the paths to the license file(s)
  license_files   : 'LICENSE',                                
  # Takes a string describing which Meson version the project requires
  meson_version   : '>=1.3.2',
  # Specifies the top level directory name that holds Meson subprojects
  subproject_dir  : 'subprojects',                                       
  # A free form string describing the version of this project
  version         : '0.1.0',
)

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_EXT_CXX']

shlib = shared_library('ext_cxx', 'ext_cxx.cpp',
  install : true,
  cpp_args : lib_args,
  gnu_symbol_visibility : 'hidden',
)

test_exe = executable('ext_cxx_test', 'ext_cxx_test.cpp',
  link_with : shlib)
test('ext_cxx', test_exe)

# Make this library usable as a Meson subproject.
ext_cxx_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with : shlib)

# Make this library usable from the system's
# package manager.
install_headers('ext_cxx.hpp', subdir : 'ext_cxx')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : 'ext-cxx',
  filebase : 'ext_cxx',
  description : 'Meson sample project.',
  subdirs : 'ext_cxx',
  libraries : shlib,
  version : '0.1.0',
)

# Build Python extension module
python = import('python').find_installation()
python.install_sources(
    meson.current_source_dir() / 'src' / 'ext_cxx' / '__init__.py',
)
nanobind_dep = dependency('nanobind')
mod = python.extension_module(
  'ext_cxx',
  sources: [
    'src/_core.cpp',           
    'src/array.cpp',
    'src/mod/binding.cpp',
    'src/mod/typecaster.cpp',
    'src/mod/wrapper.cpp',
  ],
  dependencies: [nanobind_dep],
  install: true,
  limited_api: '3.12',
)
