#include <stdio.h>
#include "data_viewing.c"

void main() {
    float data[10] = { 0.4, 0.2, 0.3, 0.2, 1.1, 1.2, 2.1, 0.9, 1.0, 0.7 };

    draw_graph(data, 10);
}