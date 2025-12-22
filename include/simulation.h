#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct {
    const int n_points_x;
    const int steps;
    const double width_x;
    const double duration;
    double dx;
    double dt;
    double t;
} Simulation;

#endif
