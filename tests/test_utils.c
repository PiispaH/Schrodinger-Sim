#include <stdio.h>
#include <assert.h>
#include <complex.h>
#include "utils.h"

void test_utils() {
    double_c z = 2.12342113521314253 * I + 1;
    
    double a = 2.12342113521314253;
    double b = 1.0;

    assert(cimag(z) == a);
    assert(creal(z) == b);

    assert(sizeof(double) == sizeof(cimag(z)));
    assert(sizeof(double) == sizeof(creal(z)));

    assert((float)cimag(z) != cimag(z));
}
