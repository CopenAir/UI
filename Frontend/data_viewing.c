#include <stdio.h>

// Returns the maximum value of a and b
int max(int a, int b) {
    if (a >= b) return a;
    else return b;
}

// Draw a graph of the given float data
// n is length of data
void draw_graph(float data[], int n) {
    // copy and convert the data to integers for display purposes and get 
    // the maximum value in data_as_int to know how tall the graph should be
    int data_as_int[n];
    int m;
    for (int i = 0; i < n; i++) {
        data_as_int[i] = (int)(data[i] * 10);
        m = max(m, data_as_int[i]);
    }

    // Draw graph from top left to bottom right
    for (int i = m; i > 0; i--) {
        for (int j = 0; j < n; j++) {
            if (data_as_int[j] >= i)
                printf(" ███");
            else
                printf("    ");
        }
        printf("\n");
    }
}