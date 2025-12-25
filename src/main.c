#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "schrodinger.h"
#include "utils.h"
#include "window.h"
#include "simulation.h"


int main() {
    Window window = {
        .width = 16 * 60,
        .height = 9 * 60
    };

    Simulation simulation = {
        .duration = 60.0,
        .n_points_x = window.width / 2,
        .width_x = 10.0,
        .visible_x = 10.0,
        .t = 0.0
    };
    simulation.steps = simulation.duration * 60;
    simulation.dx = 2.0 * simulation.width_x / simulation.n_points_x;
    simulation.dt = simulation.duration / simulation.steps;

    double_c *wavefunction = init_wavefunction(&simulation);

    render_frame(&window, &simulation, wavefunction, 0);

    for (int i = 1; i <= simulation.steps; i++) {
        simulation.t += simulation.dt;
        crank_nicolson_step(&simulation, wavefunction);
        render_frame(&window, &simulation, wavefunction, i);
    
    }

    free(wavefunction);
        
    return 0;
}
