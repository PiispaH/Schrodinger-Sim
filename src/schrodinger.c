#include <math.h>
#include <stdlib.h>
#include "schrodinger.h"
#include "simulation.h"

double* schrodinger(Simulation *simulation) {
    // double a = 0.01;
    // double x;

    double *wavefunction = malloc(simulation->size_x * sizeof(double));
    
    // The initial wavefunction
    for (int i = 0; i < simulation->size_x; i++) {
        
        wavefunction[i] = exp((double)i / simulation->steps) * (simulation->duration - simulation->t) / simulation->duration;
        // x = (i - simulation->size_x / 2.0 ) / simulation->size_x;        
        // wavefunction[i] = exp(-pow(x, 2.0) / (2.0 * a));
    }

    return wavefunction;
}
