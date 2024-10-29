//generate .h file for data_display.c
#ifndef DATA_DISPLAY_H
#define DATA_DISPLAY_H

#include <stdbool.h>

#define WHO_ANNUAL_PM2_5 5
#define WHO_24HOUR_PM2_5 15
#define WHO_ANNUAL_PM10 15
#define WHO_24HOUR_PM10 45
#define WHO_ANNUAL_NO2 10
#define WHO_24HOUR_NO2 25

void draw_graph(int size, float *a, int max_val, int threshold);
void print_rating(float data, int threshold);
void print_data(float data[]);
void print_data(float data[]);
void average(float** data, int n, float* avg);
void hour_display(char* road, char* date, int hour);
void day_display(char* road, char* date);
void month_display(char* road, char* date);

#endif