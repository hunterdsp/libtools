#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

// For brevity's sake
namespace nb = nanobind;
using namespace nb::literals;
using IntVector = std::vector<int>;

// Example: The C++ implementation
// ================================
// Double the entries of a vector and return the result. 
IntVector double_it(const IntVector &in) { 

    IntVector out(in.size());

    for (size_t i = 0; i < in.size(); ++i)
        out[i] = in[i] * 2;
    
    return out;

}
NB_MAKE_OPAQUE(IntVector)
#include <nanobind/stl/bind_vector.h> // NOTICE NEW HEADER!!!
using IntVector = std::vector<int>;
// Option 2: Bindings
// -------------------
// Bindings expose C++ types in Python; the ability to create them is the main feature of nanobind. In the list-of-integer example, they cause Python to interpret std::vector<int> as a new Python type called my_ext.IntVector.
void ext_binding(nb::module_ &m) {
     nb::bind_vector<IntVector>(m, "IntVector");
     m.def("double_it", &double_it);
 }

// Any function taking or returning integer vectors will now use the type binding. In the Python session below, nanobind performs an implicit conversion from the Python list [1, 2, 3] to a my_ext.IntVector before calling the double_it function.

// Pro: bindings don’t require the costly conversion step when crossing the language boundary. They also support mutable references, so the issue discussed in the context of type casters does not arise. Sometimes, binding is the only available option: when a C++ type does not have an equivalent Python type, casting simply does not make sense.

// Con: Creating good bindings that feel natural in Python requires some additional work. We cheated in this example by relying on the nb::bind_vector<T>() helper function that did all the heavy lifting. Such helpers are currently only available for a few special cases (vectors, ordered/unordered maps, iterators

