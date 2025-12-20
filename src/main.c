#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "schrodinger.h"


double* painter(double t, double duration, int width, int height, int size_x) {
    double* arr = (double*)malloc(width * sizeof(double));
    
    double* grid_x = schrodinger(size_x, t, duration);

    int multiplier = width / size_x;

    printf("%d\n", multiplier);
    for (int i = 0; i < width; i++) {
        arr[i] = grid_x[i / multiplier] * height / 6;
        // printf("Value: %f\n", grid_x[i]);
    }
    return arr;
}

int main() {

    const int width = 16*60;
    const int height = 9*60;

    // the size of the computational grid
    const int size_x = 100;

    const double duration = 1.0;
    const int steps = 60;
    const double dt = duration / (double)steps;

    char buffer[256];
    for (int i = 0; i < steps; i++) {
        snprintf(buffer, sizeof(buffer), "data/output-%04d.ppm", i);
        const char *output_path = buffer;

        FILE *pf = fopen(output_path, "wb");

        // Insert the metadata for the fileformat
        fprintf(pf, "P6\n");
        fprintf(pf, "%d %d\n", width, height);
        fprintf(pf, "255\n");

        double* arr = painter((double)i *dt, duration, width, height, size_x);

        // The actual pixel values
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // paint(pf, x, y, n * dt); 
                // if (((x + i) / 10 + (y + i) / 10) % 5 == 0) fputc(255, pf); 
                
                // Paint under the value at point x
                if (arr[x] > height - y) fputc(255, pf);
                else fputc(0, pf);
                
                fputc(0, pf); 
                fputc(0, pf); 
            }
        }
        
        fclose(pf);

        printf("Generated file output-%04d.ppm\n", i);    
    }
    
    return 0;

}
