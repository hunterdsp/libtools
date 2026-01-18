#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

// For brevity's sake
namespace nb = nanobind;
using namespace nb::literals;
using IntVector = std::vector<int>;

// Example: The C++ implementation
// ================================
// square the entries of a vector and return the result. 
IntVector square_it(const IntVector &in) { 

    IntVector out(in.size());

    for (size_t i = 0; i < in.size(); ++i)
        out[i] = in[i] * in[i];
    
    return out;

}


// OPTION #1
// To expose it in Python, we can use the std::vector<...> type caster.
// ---------------------------------------------------------------------
/* Pro: this approach is simple and convenient, especially when standard (STL) types are involved. Usually, all that is needed is an #include directive to pull in the right header file. Complex nested types (e.g. vectors of hash tables of strings) work automatically by combining type casters recursively.*/
void ext_typecaster(nb::module_ &m) {
    m.def("square_it", &square_it);
}
//
//// Con: Every transition between the Python and C++ side will generally require a conversion step (in this case, to re-create all list elements). This can be wasteful when the other side only needs to access a small part of the data. Conversely, the overhead should not be a problem when the data is fully “consumed” following conversion.
//
//// A select few type casters (std::unique_ptr<..>, std::shared_ptr<..>, nb::ndarray, and Eigen::*) are special in the sense that they can perform a type conversion without copying the underlying data. Besides those few exceptions type casting always implies that a copy is made
//
//// Mutable reference issue
//// ------------------------
//// Another subtle limitation of type casters is that they don’t propagate updates through mutable references. Consider the following alternative implementation of the square_it function
//
//void fail_square_it(IntVector &in) {
//    for (int &value : in)
//        value *= 2;
//}
//
//// Wrap this function without problems, but it won’t behave as expected: 
//void fail_square_it(nb::module_ &m) {
//    m.def("fail_square_it", &fail_square_it);
//}
//
///* Python
//----------
//>>> x = [1, 2, 3]
//>>> fail_square_it(x)
//>>> x
//[1, 2, 3]  # <-- oops, unchanged!
//
//*/
//
//// How could this happen? The reason is that type casters convert function arguments and return values once, but further changes will not automatically propagate across the language barrier because the representations are not intrinsically linked to each other.
//
//// This is because builtin types like int, str, bool, etc., are all handled by type casters. A simple alternative to propagate updates while retaining the convenience of type casters is to bind a small wrapper lambda function that returns a tuple with all output arguments. An example:
//
//int pass_square_it(int &in) { in *= 2; return in; }
//
//// And the binding code
//void pass_square_it(nb::module_ &m) {
//    m.def("pass_square_it", [](int i) { 
//        int rv = pass_square_it(i); return std::make_tuple(rv, i); 
//    });
//}
//
//// In this case, a type caster (#include <nanobind/stl/tuple.h) must be included to handle the std::tuple<int, int> return value.
NB_MAKE_OPAQUE(IntVector)