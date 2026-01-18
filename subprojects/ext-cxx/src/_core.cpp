#include <nanobind/nanobind.h>

// For brevity's sake
namespace nb = nanobind;

// Include submodules
void ext_typecaster(nb::module_ &);
void ext_binding(nb::module_ &);
void ext_wrapper(nb::module_ &);
void ext_array(nb::module_ &);

// The top-level extension
NB_MODULE(ext_cxx, m) {
    ext_typecaster(m);
    ext_binding(m);
    ext_wrapper(m);
    ext_array(m);
}
