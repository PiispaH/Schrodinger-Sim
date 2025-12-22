#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "schrodinger.h"
#include "utils.h"
#include "window.h"
#include "simulation.h"


double* format_array(Window *window, Simulation *simulation, double_c *wavefunction) {
    // Calculate the probability amplitudes
    int multiplier = window->width / simulation->n_points_x;
    
    double *arr = malloc(window->width * sizeof(double));
    for (int i = 0; i < window->width; i++) {
        arr[i] = pow(cabs(wavefunction[i / multiplier]), 2.0) * window->height / 2;
    }
    return arr;
}

void painter(double *arr, FILE *pf, Window *window) {
    for (int y = 0; y < window->height; y++) {
        for (int x = 0; x < window->width; x++) {
            // Paint under the value at point x
            if (arr[x] > window->height - y) fputc(255, pf);
            else fputc(0, pf);

            fputc(0, pf); 
            fputc(0, pf); 
        }
    }
}

void render_frame(Window *window, Simulation *simulation, double_c *wavefunction, int frame) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "data/output-%04d.ppm", frame);
    const char *output_path = buffer;
    
    FILE *pf = fopen(output_path, "wb");

    // Insert the metadata for the fileformat
    fprintf(pf, "P6\n");
    fprintf(pf, "%d %d\n", window->width, window->height);
    fprintf(pf, "255\n");
    
    double *arr = format_array(window, simulation, wavefunction);
    
    // Paint the actual pixel values for the frame
    painter(arr, pf, window);
    
    fclose(pf);

}

void run(Window *window, Simulation *simulation) {

    double_c *wavefunction = init_wavefunction(simulation);

    render_frame(window, simulation, wavefunction, 0);

    for (int i = 1; i <= simulation->steps; i++) {
        simulation->t += simulation->dt;
        crank_nicolson_step(simulation, wavefunction);

        render_frame(window, simulation, wavefunction, i);
    
    }
}

int main() {
    Window window = {
        .width = 16 * 60,
        .height = 9 * 60
    };
    
    // Outputs 60fps video, so (duration * steps / 60) gives the length of the output video.
    Simulation simulation = {
        .duration = 1.0,
        .n_points_x = window.width / 2,
        .width_x = 10.0,
        .steps = 240,
        .t = 0.0
    };
    simulation.dx = 2.0 * simulation.width_x / simulation.n_points_x;
    simulation.dt = simulation.duration / simulation.steps;
    run(&window, &simulation);

    return 0;
}
