#include <assert.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "schrodinger.h"
#include "simulation.h"
#include "utils_tests.h"


/* Test that the initial wavefunciton is normalized. */
void test_init_wavefunction() {
    Simulation simulation = init_simulation();

    double_c *arr = init_wavefunction(&simulation);
    double sum = 0;
    for (int i = 0; i < simulation.n_points_x; i++) {
        sum += pow(cabs(arr[i]), 2.0) * simulation.dx;
    }
    assert_double_close_to(sum, 1.0);
    free(arr);
}

/* Test that the implemented Crank-Nicolson preserves the norm of the state */
void test_crank_nicolson_step() {

    Simulation simulation = init_simulation();

    double_c *arr = init_wavefunction(&simulation);

    for (int i = 1; i <= simulation.steps; i++) {
        crank_nicolson_step(&simulation, arr);

        double sum = 0;
        for (int i = 0; i < simulation.n_points_x; i++) {
            sum += pow(cabs(arr[i]), 2.0) * simulation.dx;
        }

        assert_double_close_to(sum, 1.0);
    }

    free(arr);
}

/* Test that the potential works as intended. */
void test_potential() {
    Simulation simulation = init_simulation();
    
    double V;

    V = potential(&simulation, -0.1);
    assert_double_is_zero(V);

    V = potential(&simulation, -simulation.visible_x * 0.79);
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
