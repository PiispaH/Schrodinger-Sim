#include <assert.h>
#include <stdlib.h>
#include "window.h"
#include "simulation.h"

void assert_double_close_to(double x, double target) {
    assert(0.99999999 * target < x);
    assert(x < 1.00000001 * target);
}

void assert_double_is_zero(double x) {
    assert(x < 0.000000001);
    assert(x > -0.000000001);
}

Window init_window() {
    return (Window){
        .width = 16 * 60,
        .height = 9 * 60
    };
}

Simulation init_simulation() {
    return (Simulation){
        .duration = 100.0,
        .n_points_x = 200,
        .width_x = 10.0,
        .visible_x = 5.0,
        .t = 0.0,
        .steps = 100.0 * 120,
        .dx = 2.0 * 10.0 / 200,
        .dt = 100 / 100.0 * 120
    };
}