/*  CLI Bar Chart Engine Library
    18/10/2024 @ 09:19
    graph_engine.c V1.3

    Sebastian Lindau-Skands
    slinda24@student.aau.dk*/

#include "graph_engine.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET_COLOUR "\x1b[0m"

void generate_table(int size, float *a, int max_val, int threshold) {
    //size = size of x-axis
    //*a = float array with data points
    //max_val = maximum value in the data points
    //threshold = value to use as a threshold for the bar chart

    /*  \x1b[ = how to define colour
        31m=red
        32m=green*/
    int max_val_int = (int)(max_val * 10.0);
    int threshold_int = (int)(threshold * 10.0);

    for (int i = max_val_int; i > 0; i--) {
        //printf statement with ternary operator inside. Essentially an if statement that returns the appropriate colour value
        printf("%s%2d║", (i*10) < threshold_int ? GREEN : RED, i);
        for (int j = 0; j < size; j++) {
            int data = (int)(a[j] * 10.0);
            //printf statement with ternary operator inside. Essentially an if statement that returns the appropriate thing to be printed
            printf("%s", data >= (i*10) ? "███ " : "    ");
        }
        printf("\n");
        printf(RESET_COLOUR);
    }

    printf("  ╚");
    for (int i = 0; i < size; i++) {
        printf("════");
    }
    printf("\n  ");
    for (int i = 1; i <= size; printf("%4d", i++));
}
