#ifndef SCHRODINGER_H
#define SCHRODINGER_H

#include "simulation.h"
#include "utils.h"

double_c* init_wavefunction(Simulation *simulation);
double potential(Simulation *simulation, double x);
void crank_nicolson_step(Simulation *simulation, double_c *wavefunction);

#endif
