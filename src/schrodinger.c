#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "schrodinger.h"
#include "simulation.h"
#include "utils.h"


/* Defines the potential at the point x */
double potential(Simulation *simulation, double x) {

    // Infinite well
    double V = 0.0;
    if (x <= -simulation->visible_x * 0.8 || x >= simulation->visible_x * 0.8) {
        V = 999999999.9;
    }

    return V;
}

/* Initializes the wavefunction */
double_c* init_wavefunction(Simulation *simulation) {

    double var_x = 0.25;
    double a = 1.0 / (4.0 * pow(var_x, 2.0));
    double pi = 3.1415926535897932;
    double norm = pow(2.0 * a / pi, 0.25);
    
    double x = -simulation->width_x;
    double_c *wavefunction = malloc(simulation->n_points_x * sizeof(double_c));
    for (int i = 0; i < simulation->n_points_x; i++) {
        wavefunction[i] = norm * cexp(-a * x * x);
        x += simulation->dx;
    }

    return wavefunction;
}

/* Evolves the given wavefunction one step forwad with the Crank-Nicolson method */
void crank_nicolson_step(Simulation *simulation, double_c *wavefunction) {

    double x = -simulation->width_x;

    double_c s_i = I * simulation->dt * potential(simulation, x) / 2.0;
    double_c r = I * simulation->dt / (4.0 * pow(simulation->dx, 2.0));
    double_c b_i = 1.0 + 2.0 * r + s_i;
    double_c d_i = r * wavefunction[1] + (1.0 - 2.0 * r - s_i) * wavefunction[0];

    double_c *c_prime_i = malloc((simulation->n_points_x - 1) * sizeof(double_c));
    double_c *d_prime_i = malloc(simulation->n_points_x * sizeof(double_c));
    c_prime_i[0] = -r / b_i;
    d_prime_i[0] = d_i / b_i;

    double_c divisor;

    // Forwards step
    for (int i = 1; i < simulation->n_points_x; i++) {
        x += simulation->dx;

        s_i = I * simulation->dt * potential(simulation, x) / 2.0;
        b_i = 1.0 + 2.0 * r + s_i;

        d_i = (1.0 - 2.0 * r - s_i) * wavefunction[i] + r * wavefunction[i-1];
        if (i != simulation->n_points_x - 1) d_i += r * wavefunction[i+1];

        divisor = b_i + r * c_prime_i[i-1];
        if (i != simulation->n_points_x - 1) c_prime_i[i] = -r / divisor;
        d_prime_i[i] = (d_i + r * d_prime_i[i-1]) / divisor;
    }

    // Backwards step
    wavefunction[simulation->n_points_x-1] = d_prime_i[simulation->n_points_x-1];
    for (int i = simulation->n_points_x-2; i >= 0; i--) {
        wavefunction[i] = d_prime_i[i] - c_prime_i[i] * wavefunction[i+1];
    }

    free(c_prime_i);
    free(d_prime_i);

}
