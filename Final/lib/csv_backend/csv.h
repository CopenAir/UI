#ifndef CSV_BACKEND_H
#define CSV_BACKEND_H

#include <stdio.h>
#define MAX_COLUMNS 5
#define MAX_ROWS 8785

// TODO: we should probably have a header file with all the structs, but im just gonna put this here for now
struct timespan {
    time_t start_date;
    time_t end_date;
};

int load_data(char *filename, float data_matrix[][MAX_ROWS]);
int get_data_for_date(char *filename, float data_array[], time_t date);
int get_data_for_timespan(const char *filename, float data_matrix[MAX_COLUMNS][MAX_ROWS], struct timespan timespan);
int is_midday(time_t unixtime);

#endif
