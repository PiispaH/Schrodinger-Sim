#include <assert.h>

void assert_double_close_to(double x, double target) {
    assert(0.99999999 * target < x);
    assert(x < 1.00000001 * target);
}

void assert_double_is_zero(double x) {
    assert(x < 0.000000001);
    assert(x > -0.000000001);
}
