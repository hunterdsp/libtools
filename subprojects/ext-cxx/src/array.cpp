#include <cmath>
#include <complex>
#include <nanobind/ndarray.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/complex.h>


// Object Definitions
// --------------------
struct ExpAverage {
    
    public:
     double smoothing = 0.9;
     double sample_interval = 1.0;
     double time_constant = sample_interval / smoothing;
     std::complex<double> state = 0.0;

     void step(nanobind::ndarray<nanobind::c_contig, nanobind::device::cpu> x) {

         if (
             x.dtype() == nanobind::dtype<std::complex<double>>() 
             && x.ndim() == 1
         ) {
             auto v = x.view<std::complex<double>, nanobind::ndim<1>>();
             for (size_t i = 0; i < v.shape(0); ++i) {
                     v(i) = state + smoothing * (v(i) - state);
                     state = v(i);
             }
         }
    }
};


// Module Exports
// ---------------
void ext_array(nanobind::module_ &m){
    nanobind::class_<ExpAverage>(m, "ExpAverage")
        .def(nanobind::init<>())
        .def(nanobind::init<double>())
        .def(nanobind::init<double, double>())
        .def("step", &ExpAverage::step)
        .def_ro("time_constant", &ExpAverage::time_constant)
        .def_ro("state", &ExpAverage::state);
}
