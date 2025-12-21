#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "schrodinger.h"
#include "window.h"
#include "simulation.h"


double* painter(Window *window, Simulation *simulation) {
    double *arr = malloc(window->width * sizeof(double));

    double *grid_x = schrodinger(simulation);

    int multiplier = window->width / simulation->size_x;

    // printf("%d\n", multiplier);
    for (int i = 0; i < window->width; i++) {
        // printf("%f\n", grid_x[i / multiplier]);
        arr[i] = grid_x[i / multiplier] * window->height / 6;
        // Here interpolation to some degree is probably needed...
    }
    return arr;
}

int main() {

    Window window = {
        .width = 16 * 60,
        .height = 9 * 60
    };

    Simulation simulation = {
        .duration = 5.0,
        .size_x = 100,
        .steps = 60,
        .dt = 5.0 / 60.0,
        .t = 0.0
    };

    char buffer[256];
    for (int i = 0; i < simulation.steps; i++) {
        snprintf(buffer, sizeof(buffer), "data/output-%04d.ppm", i);
        const char *output_path = buffer;

        simulation.t += simulation.dt;

        FILE *pf = fopen(output_path, "wb");

        // Insert the metadata for the fileformat
        fprintf(pf, "P6\n");
        fprintf(pf, "%d %d\n", window.width, window.height);
        fprintf(pf, "255\n");

        double *arr = painter(&window, &simulation);

        // The actual pixel values
        for (int y = 0; y < window.height; y++) {
            for (int x = 0; x < window.width; x++) {
                // paint(pf, x, y, n * dt); 
                // if (((x + i) / 10 + (y + i) / 10) % 5 == 0) fputc(255, pf); 

                // Paint under the value at point x
                if (arr[x] > window.height - y) fputc(255, pf);
                else fputc(0, pf);

                fputc(0, pf); 
                fputc(0, pf); 
            }
        }

        fclose(pf);
    }

    return 0;
}
