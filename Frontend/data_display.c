#include <stdio.h>
#include "constants.h"

int max(int a, int b) {
    if (a >= b) 
        return a;
    else 
        return b;
}

// Draw a graph of the given float array
// n is the number of elements in the array
// threshold is the value where the data starts to get red
void draw_graph(float data[], int n, float threshold) {
    // copy and convert the data to integers so it can be used in the for loop.
    // We cut off some precision to fit the graph in the terminal,
    // and get the maximum value to know how tall the graph should be
    int data_as_int[n];
    int mx = 0;
    for (int i = 0; i < n; i++) {
        data_as_int[i] = (int)(data[i] * 2); 
        mx = max(mx, data_as_int[i]);
    }
    mx += 10 - (mx % 10); // round up for a more pretty graph

    // Draw graph from top left to bottom right
    for (int i = mx; i > 0; i--) {
        if (i > (threshold * 2)) 
            printf("\033[0;31m"); // Switch print color to red
        else 
            printf("\033[0;32m"); // Switch print color to green
        if (i % 10 == 0) // display x-axis value for every 10th line
            printf("%4d ║", i / 2);
        else
            printf("     ║");
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
    for (int i = 0; i < n;)
        printf(" %3d", ++i);
    printf("\n"); 
}

// prints the rating in different color based on data and threshold
void print_rating(float data, int threshold) {
    if (data < threshold / 2)
        printf("\033[0;32m low\033[0m");
    else if (data < threshold)
        printf("\033[0;33m medium\033[0m");
    else
        printf("\033[0;31m high\033[0m");
}

void draw_data(float data[]) {
    printf("---------------------------------------------\n\n");
    printf("Substance  Data       Rating\n\n");
    printf("[%d]PM2.5:  %-4.1f %-5s", 1, data[0], "μg/m3");
    print_rating(data[0], WHO_24HOUR_PM2_5);
    printf("\n[%d]PM10:   %-4.1f %-5s", 2, data[1], "μg/m3");
    print_rating(data[1], WHO_24HOUR_PM10);
    printf("\n[%d]NO2:    %-4.1f %-5s", 3, data[2], "μg/m3");
    print_rating(data[2], WHO_24HOUR_NO2);
    printf("\n[%d]Temp:   %-4.1f %-5s  N/A\n", 4, data[3], "°C");   
    printf("\n---------------------------------------------\n");
}

// Calculates the averages of the given data sets into avg
void average(float** data, int n, float* avg) {
    float pm25_sum = 0, pm10_sum = 0, no2_sum = 0, temp_sum = 0;

    for (int i = 0; i < n; i++) {
        pm25_sum += data[i][1];
        pm10_sum += data[i][2];
        no2_sum += data[i][3];
        temp_sum += data[i][4];
    }

    avg[0] = pm25_sum / n;
    avg[1] = pm10_sum / n;
    avg[2] = no2_sum / n;
    avg[3] = temp_sum / n; 
}

void hour_display(char* road, char* date, int hour) {
    printf("\033[H\033[J");  // ANSI escape code to clear the screen
    float data[4] = {10, 5, 25, 20};

    printf("%-20s%-20s%d:00\n", road, date, hour);

    draw_data(data);
}

void day_display(char* road, char* date) {
    printf("\033[H\033[J");  // ANSI escape code to clear the screen
    float* data[4];
    float a[5] = {1 ,2 ,3 ,4 ,5};
    float b[5] = {5, 4, 3, 2, 1}; 

    data[0] = a;
    data[1] = a;
    data[2] = b;
    data[3] = b;

    float avg[4];
    average(data, 4, avg);

    printf("%-35s%s\n", road, date);

    draw_data(avg);
}

void month_display(char* road, char* date) {
    // todo
}