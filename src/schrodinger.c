#include <math.h>
#include <stdlib.h>
#include "schrodinger.h"

double* schrodinger(int size_x, double t, double duration) {
    double* grid_x = (double*)malloc(size_x * sizeof(double));

    for (int i = 0; i < size_x; i++) {
        grid_x[i] = exp(i / 60.0) * (1.0 - t);
    }

    return grid_x;
}