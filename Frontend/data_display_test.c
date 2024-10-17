#include <stdio.h>
#include <stdlib.h>
#include "data_display.c"

void draw_graph_test() {
    float data[24];
    // Perform 10 test with random data
    for (int test = 0; test < 10; test++) {
        for (int i = 0; i < 24; i++)
            data[i] = ((float)(rand() % 20)) / 10; // random float between 0 and 2.0
        draw_graph(data, 24, data[0]);
    }
    // testing 2 digit data, negative data and zero
    float new_data[3];
    new_data[0] = -1.0;
    new_data[1] = 0.0;
    new_data[2] = 10.11;
    draw_graph(new_data, 3, 5.0);
    // Empty list
    float* empty_data;
    draw_graph(empty_data, 0, 0.1);
}

void hour_display_test() {
    // test here
}

void day_display_test() {
    // test here
}

void month_display_test() {
    // test here
}

// Call tests in main function
void main() {
    draw_graph_test();
}