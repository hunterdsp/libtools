project(
  'libtools', 
  'c',
  'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3'])

lib = library('tools',
        'src/mylib.c',
         install : true)
incdir = include_directories('inc')
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
meson.add_install_script('linux_bundler.sh')
install_data('myapp.sh', install_dir : '.')
