#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include "schrodinger.h"
#include "simulation.h"
#include "utils.h"


double potential(Simulation *simulation, double x) {
    // Gives the potential at the point x

    // Harmonic
    // double displacement = simulation->points_x / 2 + x;
    // double V = 0.5 * pow(displacement, 2.0);

    // Free particle in a box
    double V = 0.0;
    if (x <= -simulation->width_x || x >= simulation->width_x) {
        V = 999999999.9;
    }

    return V;
}

double_c* init_wavefunction(Simulation *simulation) {
    // Initializes the wavefunction
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

void crank_nicolson_step(Simulation *simulation, double_c *wavefunction) {
    /* Evolves the given wavefunction one step forwad with the Crank-Nicolson method */

    double x = -simulation->width_x;
    // printf("\nx: %lf\n", x);

    double_c s_i = I * simulation->dt * potential(simulation, x) / 2.0;
    // printf("s_i: %lf %lfj\n", creal(s_i), cimag(s_i));

    double_c r = I * simulation->dt / (4.0 * pow(simulation->dx, 2.0));
    // printf("r: %lf %lfj\n", creal(r), cimag(r));

    double_c ac = -r;
    // printf("ac: %lf %lfj\n", creal(ac), cimag(ac));

    double_c b_i = 1.0 + 2.0 * r + s_i;
    // printf("b_i: %lf %lfj\n", creal(b_i), cimag(b_i));

    double_c d_i = r * wavefunction[1] + (1.0 - 2.0 * r - s_i) * wavefunction[0];
    // printf("d_i: %lf %lfj\n", creal(d_i), cimag(d_i));

    double_c *c_prime_i = malloc((simulation->n_points_x - 1) * sizeof(double_c));
    c_prime_i[0] = ac / b_i;
    double_c *d_prime_i = malloc(simulation->n_points_x * sizeof(double_c));
    d_prime_i[0] = d_i / b_i;

    // printf("c_prime_i: %lf %lfj\n", creal(c_prime_i[0]), cimag(c_prime_i[0]));
    // printf("d_prime_i: %lf %lfj\n", creal(d_prime_i[0]), cimag(d_prime_i[0]));

    double_c divisor; 
    for (int i = 1; i < simulation->n_points_x; i++) {
        x += simulation->dx;

        s_i = I * potential(simulation, x) / 2.0;
        b_i = 1.0 + 2.0 * r + s_i;

        d_i = (1.0 - 2.0 * r - s_i) * wavefunction[i] + r * wavefunction[i-1];
        if (i != simulation->n_points_x - 1) d_i += r * wavefunction[i+1];

        divisor = b_i - ac * c_prime_i[i-1];
        if (i != simulation->n_points_x - 1) c_prime_i[i] = ac / divisor;
        d_prime_i[i] = (d_i - ac * d_prime_i[i-1]) / divisor;
    }

    // printf("\n\n\n\n\n\n\n\n\n\n\n\nc_prime_i:");
    // for (int i = 0; i < simulation->n_points_x-1; i++) {
    //     printf("%f j%f   ", creal(c_prime_i[i]), cimag(c_prime_i[i]));
    // }
    // printf("\n\n\n\n\n\n\n\n\n\n\n\n");

    // printf("\n\n\n\n\n\n\n\n\n\n\n\nd_prime_i:");
    // for (int i = 0; i < simulation->n_points_x; i++) {
    //     printf("%f j%f   ", creal(d_prime_i[i]), cimag(d_prime_i[i]));
    // }
    // printf("\n\n\n\n\n\n\n\n\n\n\n\n");

    // Now we go backwards...
    wavefunction[simulation->n_points_x-1] = d_prime_i[simulation->n_points_x-1];
    for (int i = simulation->n_points_x-2; i >= 0; i--) {
        wavefunction[i] = d_prime_i[i] - c_prime_i[i] * wavefunction[i+1];
    }
}
