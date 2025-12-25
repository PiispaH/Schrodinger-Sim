#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct {
    const int n_points_x;
    const double width_x;
    const double visible_x;
    const double duration;
    int steps;
    double dx;
    double dt;
    double t;
} Simulation;

#endif
