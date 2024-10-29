#ifndef CSV_BACKEND_H
#define CSV_BACKEND_H

#include <stdio.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 5
#define MAX_ROWS 8785
int load_data(char *filename, double data_matrix[][MAX_ROWS]);

#endif