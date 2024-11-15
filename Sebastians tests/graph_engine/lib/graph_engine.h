/*  CLI Bar Chart Engine Library Header
    18/10/2024 @ 09:19
    graph_engine.h V1

    Sebastian Lindau-Skands
    slinda24@student.aau.dk*/

#ifndef GRAPH_ENGINE_H
#define GRAPH_ENGINE_H

#include <stdio.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET_COLOUR "\x1b[0m"

void generate_table(int size, float *a, int max_val, int threshold);

#endif
