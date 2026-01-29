// main() application will be compiled directly to binary executable

// Need dlfcn.h for the routines to dynamically load libraries
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>


int main(void)
{
  const char *error;
  // WE DO NOT include the actual library we are using but WE DO need to specify a type that will hold the value we're going to get from dlsym(). The type for the dynamic function we will load:
  int (*mycadder)(int, int);
  void *module;
  int a = 10;
  int b = 5;

  // Load dynamic library
  module = dlopen("./libtools.so", RTLD_LAZY);
  if (!module)
  {
    fprintf(stderr, "Couldn't open dynamic library: %s\n",
            dlerror());
    exit(1);
  }
  // Load symbol
  dlerror();
  // Work-around to avoid warning between ISO C and POSIX for function pointer assignment to void pointer even though disym returns such
  *(void**)(&mycadder) = dlsym(module, "mycadder");
  if ((error = dlerror()))
  {
    fprintf(stderr, "Couldn't find function: %s\n", error);
    exit(1);
  }
  /* Now call the function in the DL library */
  fprintf(stdout, "Calling symbol %s with %d and %d ... gives: %d\n",
    "mycadder", a, b, (*mycadder)(a, b));
  /* All done, close things cleanly */
  dlclose(module);
  return 0;
}