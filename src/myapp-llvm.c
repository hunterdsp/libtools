// main() application will be compiled directly to binary executable

// import the libraries containing the implementations
#include <stdio.h>
#include "mylib.h"
#include "mylib-llvm.h"

// Run the app
int main()
{   int a = 10; int b = 5;
    printf("%d * %d = %d\n", a, b, mylib_llvm_f(a, b));
    return 0;
}