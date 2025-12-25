#include <assert.h>
#include <complex.h>
#include <math.h>
#include "simulation.h"
#include "utils_tests.h"
#include "window.h"


void test_get_x_from_i() {
    Window window = init_window();
    Simulation simulation = init_simulation();

    double x = get_x_from_i(&window, &simulation, 0);
    assert(x == -simulation.visible_x);
    
    x = get_x_from_i(&window, &simulation, 16 * 60 / 4);
    assert(x == -2.5);
    
    x = get_x_from_i(&window, &simulation, 16 * 60 / 2);
    assert(x == 0.0);
    
    x = get_x_from_i(&window, &simulation, 16 * 60 * 3 / 4);
    assert(x == 2.5);

    x = get_x_from_i(&window, &simulation, 16 * 60);
    assert(x == simulation.visible_x);
}

void test_get_i_from_x() {
    Simulation simulation = init_simulation();

    int i = get_i_from_x(&simulation, -10.0);
    assert(i == 0);

    i = get_i_from_x(&simulation, -5.0);
    assert(i == simulation.n_points_x / 4);

    i = get_i_from_x(&simulation, -2.5);
    assert(i == 3 * simulation.n_points_x / 8);

    i = get_i_from_x(&simulation, 0.0);
    assert(i == simulation.n_points_x / 2);

    i = get_i_from_x(&simulation, 2.5);
    assert(i == 5 * simulation.n_points_x / 8);

    i = get_i_from_x(&simulation, 5.0);
    assert(i == 3 * simulation.n_points_x / 4);

    i = get_i_from_x(&simulation, 10.0);
    assert(i == simulation.n_points_x);
}

void test_window() {
    test_get_i_from_x();
    test_get_x_from_i();
}
