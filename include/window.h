#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include "simulation.h"
#include "utils.h"

typedef struct {
    const int width;
    const int height;
} Window;

double get_x_from_i(Window *window, Simulation *simulation, int i);
int get_i_from_x(Simulation *simulation, double x);
double_c* format_array(Window *window, Simulation *simulation, double_c *wavefunction);
void colorwheel(double_c value, FILE *pf);
void render_frame(Window *window, Simulation *simulation, double_c *wavefunction, int frame);
void painter(double_c *arr, FILE *pf, Window *window, Simulation *simulation);
double ratio_(double ratio);

#endif
