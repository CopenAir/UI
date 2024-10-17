#include <stdio.h>

// Returns the maximum value of a and b
int max(int a, int b) {
    if (a >= b) 
        return a;
    else 
        return b;
}

// Draw a graph of the given float data
// n is the number of elements in the data
// threshold is the value where the data starts to get red
void draw_graph(float data[], int n, float threshold) {
    // copy and convert the data to integers so it can be used in the for loop,
    // and get the maximum value to know how tall the graph should be
    int data_as_int[n];
    int mx = 0;
    for (int i = 0; i < n; i++) {
        data_as_int[i] = (int)(data[i] * 10);
        mx = max(mx, data_as_int[i]);
    }

    // Draw graph from top left to bottom right
    for (int i = mx; i > 0; i--) {
        if (i > (threshold * 10)) {
            printf("\033[0;31m"); // Switch print color to red
            printf("%4.1f ║", ((float) i) / 10);
        }
        else {
            printf("\033[0;32m"); // Switch print color to green
            printf("%4.1f ║", ((float) i) / 10);
        }
        for (int j = 0; j < n; j++) {
            if (data_as_int[j] >= i)
                printf(" ███");
            else
                printf("    ");
        }
        printf("\n");
    }

    // Draw the bottom line and numbers
    printf("\033[0m"); // Reset print color
    printf("     ╚═");
    for (int i = 0; i < n; i++)
        printf("════"); 
    printf("\n      ");
    for (int i = 1; i <= n; i++)
        printf(" %3d", i);
    printf("\n"); 
}