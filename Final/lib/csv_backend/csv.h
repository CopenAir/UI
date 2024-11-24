#ifndef CSV_BACKEND_H
#define CSV_BACKEND_H

#include <stdio.h>
#include "../custom_time/custom_time.h"

#define MAX_COLUMNS 5
#define MAX_ROWS 8785

int load_data(char *filename, double data_matrix[][MAX_ROWS]);
int get_data_for_date(char *filename, double data_array[], time_t date);
int get_data_for_timespan(const char *filename, double data_matrix[MAX_COLUMNS][MAX_ROWS], struct timespan timespan);

#endif
