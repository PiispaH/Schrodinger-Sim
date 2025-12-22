#include <assert.h>
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "utils.h"
#include "schrodinger.h"
#include "simulation.h"
#include "utils_tests.h"


void test_init_wavefunction() {
    Simulation simulation = {
        .duration = 5.0,
        .n_points_x = 200,
        .width_x = 10.0,
        .steps = 1,
        .t = 0.0
    };
    simulation.dx = 2.0 * simulation.width_x / simulation.n_points_x;
    simulation.dt = simulation.duration / simulation.steps;

    double_c *arr = init_wavefunction(&simulation);
    double sum = 0;
    for (int i = 0; i < simulation.n_points_x; i++) {
        sum += pow(cabs(arr[i]), 2.0) * simulation.dx;
    }

    assert_double_close_to(sum, 1.0);
}

void test_crank_nicolson_step() {
    /* Test that the implemented Crank-Nicolson preserves the norm of the state */

    Simulation simulation = {
        .duration = 100.0,
        .n_points_x = 200,
        .width_x = 10.0,
        .steps = 500,
        .t = 0.0
    };
    simulation.dx = 2.0 * simulation.width_x / simulation.n_points_x;
    simulation.dt = simulation.duration / simulation.steps;

    double_c *arr = init_wavefunction(&simulation);

    for (int i = 1; i <= simulation.steps; i++) {
        crank_nicolson_step(&simulation, arr);

        double sum = 0;
        for (int i = 0; i < simulation.n_points_x; i++) {
            sum += pow(cabs(arr[i]), 2.0) * simulation.dx;
        }

        assert_double_close_to(sum, 1.0);
    }
}

void test_potential() {
    Simulation simulation = {
        .duration = 5.0,
        .n_points_x = 200,
        .width_x = 10.0,
        .steps = 60,
        .dt = 5.0 / 60.0,
        .dx = 2.0 * 10.0 / 200,
        .t = 0.0
    };

    double V;

    V = potential(&simulation, -simulation.width_x + 0.1);
    assert_double_is_zero(V);

    V = potential(&simulation, simulation.width_x - 0.1);
    assert_double_is_zero(V);

    V = potential(&simulation, 0.0);
    assert_double_is_zero(V);

    V = potential(&simulation, 1.232);
    assert_double_is_zero(V);

    V = potential(&simulation, -simulation.width_x);
    assert(V > 9999999.9);

    V = potential(&simulation, simulation.width_x);
    assert(V > 9999999.9);
}

void test_schrodinger() {
    test_init_wavefunction();
    test_crank_nicolson_step();
    test_potential();
}
