#include <nanobind/nanobind.h>

namespace nb = nanobind;

// Option 3: Wrappers
// ------------------
// The last option is only rarely used, but it can be powerful alternative in some cases. nanobind provides wrapper classes to use Python types within C++. You can think of this as a kind of reverse binding. For example, a Python list can be accessed through the nb::list type:

nb::list decrement_it(nb::list l) {
    nb::list result;
    for (nb::handle h: l)
        result.append(h - nb::int_(1));
    return result;
}

// Wrap it
void ext_wrapper(nb::module_ &m) {
    m.def("decrement_it", &decrement_it);
}

/* The implications of using wrappers are:

XXX Pro:

 Wrappers require no copying or type conversion. With them, C++ begins to resemble dynamically typed Python code and can perform highly general operations on Python objects. Wrappers are useful to tap into the powerful Python software ecosystem (NumPy, Matplotlib, PyTorch, etc).

XXX Con: 

Functions based on wrappers cannot run without Python. In contrast to option 1 (type casters) and 2 (bindings), we can no longer reuse an existing function and process its arguments and return value to interface the Python and C++ worlds: the entire function must be rewritten using nanobind-specific wrapper types. Every operation will translate into a corresponding Python C API call, which means that wrappers aren’t suitable for performance-critical loops or multithreaded computations.


++++++++++
Discussion
++++++++++

The choices outlined above are more fine-grained than they may appear. For example, it is possible to use type casters, bindings, and wrappers to handle multiple arguments of a single function.

They can also be combined within a single function argument. For example, you can type cast a std::vector<T> containing bindings or wrappers.

In general, we recommend that you use type casters for STL containers, and  bindings for other custom types.

If the former turn out to be a performance bottleneck, it is easy to replace them with bindings or wrappers later on. Wrappers are only rarely useful; you will usually know it when you need them. */