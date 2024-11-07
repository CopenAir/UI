#ifndef CSV_BACKEND_H
#define CSV_BACKEND_H

#include <stdio.h>
#define MAX_ROWS 8785

int load_data(char *filename, float data_matrix[][MAX_ROWS]);
int get_data_for_date(char *filename, float data_array[], int date);

#endif
