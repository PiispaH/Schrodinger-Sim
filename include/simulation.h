#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct {
    const int size_x;
    const int steps;
    const double duration;
    const double dt;
    double t;
} Simulation;

#endif
