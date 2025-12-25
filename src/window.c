#include <stdlib.h>
#include <math.h>
#include "window.h"
#include "simulation.h"
#include "utils.h"


/* Get the simulation position x from the window pixel index i.*/
double get_x_from_i(Window *window, Simulation *simulation, int i) {
    return i * 2.0 * simulation->visible_x / window->width - simulation->visible_x;
}

/* Get the wavefunction index i from the simulation position x. */
int get_i_from_x(Simulation *simulation, double x) {
    return (int)round(simulation->n_points_x * (x + simulation->width_x) / (simulation->width_x * 2));
}

double_c* format_array(Window *window, Simulation *simulation, double_c *wavefunction) {
    double x;
    double_c *arr = malloc(window->width * sizeof(double_c));
    for (int i = 0; i < window->width; i++) {
        x = get_x_from_i(window, simulation, i);
        if (x < -simulation->visible_x || x > simulation->visible_x) arr[i] =  0.0;
        else {
            arr[i] = wavefunction[get_i_from_x(simulation, x)];
        }
    }

    return arr;

}

/* Makes sure that the ratio is in [0, 1] */
double ratio_(double ratio) {
    if (ratio < 0.0) ratio = 0.0;
    if (ratio > 1.0) ratio = 1.0;
    return ratio;
}

/* Paints one coloured pixel based on the phase of the wavefunction at that point. */
void colorwheel(double_c value, FILE *pf) {
    const double pi = acos(-1.0);
    double segment = pi / 3;

    double phi = carg(value);
    if (phi < 0.0) phi += 2 * pi;

    double ratio;

    if (phi <= 1 * segment) {
        ratio = ratio_(phi / segment);
        fputc(255, pf);
        fputc((int)round(255 * ratio), pf); 
        fputc(0, pf); 
    } else if (phi <= 2 * segment) {
        ratio = ratio_((phi - 1 * segment) / segment);
        fputc((int)round(255 * (1 - ratio)), pf);
        fputc(255, pf);
        fputc(0, pf); 
    } else if (phi <= 3 * segment) {
        ratio = ratio_((phi - 2 * segment) / segment);
        fputc(0, pf); 
        fputc(255, pf);
        fputc((int)round(255 * ratio), pf); 
    } else if (phi <= 4 * segment) {
        ratio = ratio_((phi - 3 * segment) / segment);
        fputc(0, pf);
        fputc((int)round(255 * (1 - ratio)), pf);
        fputc(255, pf);
    } else if (phi <= 5 * segment) {
        ratio = ratio_((phi - 4 * segment) / segment);
        fputc((int)round(255 * ratio), pf);
        fputc(0, pf);
        fputc(255, pf);
    } else if (phi <= 6 * segment) {
        ratio = ratio_((phi - 5 * segment) / segment);
        fputc(255, pf);
        fputc(0, pf);
        fputc((int)round(255 * (1 - ratio)), pf);
    }
}

void painter(double_c *wavefunction, FILE *pf, Window *window, Simulation *simulation) {
    double_c *arr = format_array(window, simulation, wavefunction);

    for (int y = 0; y < window->height; y++) {
        for (int x = 0; x < window->width; x++) {
            // Paint under the value at point x
            if (pow(cabs(arr[x]), 2.0) * window->height * 0.5 > window->height - y) {
                colorwheel(arr[x], pf);
            } else {
                fputc(0, pf);
                fputc(0, pf);
                fputc(0, pf);
            }
        }
    }

    free(arr);
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

    // Paint the actual pixel values for the frame
    painter(wavefunction, pf, window, simulation);

    fclose(pf);

}
