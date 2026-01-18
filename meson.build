# Set up main project: C/C++ shared library, a few apps & Python extensions
project(
  'libtools', 
  'c',
  'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3'])

# Build a library
lib = library('tools',
        'src/mylib.c',
         install : true)
incdir = include_directories('inc')

# Build some apps
executable(
  'myapp-dynamic', 
  'src/myapp-dynamic.c', 
  link_with : lib,
  include_directories : incdir,
)
executable(
  'myappc', 
  'src/myapp.c', 
  link_with : lib,
  include_directories : incdir,
)

# Make this project Linux-install-ready
meson.add_install_script('linux_bundler.sh')
install_data('myapp.sh', install_dir : '.')

# Add a subproject
ext_cxx_proj = subproject('ext-cxx')
ext_cxx_dep = ext_cxx_proj.get_variable('ext_cxx_dep')