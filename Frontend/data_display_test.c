#include <stdio.h>
#include <stdlib.h>
#include "data_display.c"

void draw_graph_test() {
    float data[24];
    // Perform 10 test with random data
    for (int test = 0; test < 10; test++) {
        for (int i = 0; i < 24; i++)
            data[i] = ((float)(rand() % 200)) / 10; // random float between 0 and 20.0
        draw_graph(data, 24, WHO_24HOUR_PM2_5);
    }
    // Testing negative data and zero
    float new_data[2];
    new_data[0] = -1.0;
    new_data[1] = 0.0;
    draw_graph(new_data, 2, 0);
    // Empty list
    float* empty_data;
    draw_graph(empty_data, 0, 0);
}

void hour_display_test() {
    hour_display("A.C. Meyers", "2024-10-18", 10);
}

void day_display_test() {
    day_display("A.C. Meyers", "2024-10-18");
}

void month_display_test() {
    // test here
}

// Call tests in main function
void main() {
    //draw_graph_test();
    hour_display_test();
    //day_display_test();
}