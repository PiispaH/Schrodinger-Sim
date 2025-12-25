#ifndef UTILS_TESTS_H
#define UTILS_TESTS_H

#include "window.h"
#include "simulation.h"

void assert_double_close_to(double x, double target);
void assert_double_is_zero(double x);
Window init_window();
Simulation init_simulation();

#endif
