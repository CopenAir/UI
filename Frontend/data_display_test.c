#include <stdio.h>
#include <stdlib.h>
#include "data_display.c"

void main() {
    float data[24];
    // Perform 10 test with random data
    for (int test = 0; test < 10; test++) {
        for (int i = 0; i < 24; i++)
            data[i] = ((float)(rand() % 40)) / 10; // random float between 0.0 and 4.0
        draw_graph(data, 24, data[0]);
    }
    // 2 digit data, Negative data and zero
    data[0] = -1.0;
    data[1] = 0.0;
    data[2] = 10.11;
    draw_graph(data, 3, 5.0);
    // Empty list
    float* empty;
    draw_graph(empty, 0, 0);
}