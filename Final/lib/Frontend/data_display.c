#include <stdio.h>
#include <time.h>

// WHO guidelines for air pollution from 2021
// https://www.who.int/news-room/feature-stories/detail/what-are-the-who-air-quality-guidelines
#define WHO_24HOUR_PM2_5 15
#define WHO_24HOUR_PM10 45
#define WHO_24HOUR_NO2 25

void draw_graph(int size, float *data, float max_val, float threshold) {
    /*  size = size of x-axis
        *a = float array with data points
        max_val = maximum value in the data points
        threshold = value to use as a threshold for the bar chart

        \x1b[ = how to define colour
        31m=red
        32m=green */

    /*  Interesting behaviour on certain csv data, with y-axis repeating multiple times
        Implement dynamic scalling*/

    for (float i = max_val; i > 0; i -= 0.1) {
        //printf statement with ternary operator inside. Essentially an if statement that returns the appropriate colour value
        printf("%s", i>=10.0 ? "" : " ");
        printf("%s%.1f║", i <= threshold ? "\x1b[32m" : "\x1b[31m", i);
        for (int j = 0; j < size; j++) {
            //printf statement with ternary operator inside. Essentially an if statement that returns the appropriate thing to be printed
            printf("%s", data[j] >= i ? "███ " : "    ");
        }
        printf("\n\x1b[0m");
    }

    printf("    ╚");
    for (int i = 0; i < size; i++) {
        printf("════");
    }
    printf("\n     ");
    for (int i = 1; i <= size; printf("%d   ", i++));
}

// prints the rating in different color based on data and threshold
void print_rating(float data, int threshold) {
    if (data < threshold)
        printf("\033[0;32m within tolerances\033[0m");
    else
        printf("\033[0;31m outside tolerances\033[0m");
}

void print_data(float data[]) {
    printf("---------------------------------------------\n");
    printf(" %-10s %-10s %-10s\n", "Substance", "Data", "Rating");
    printf("---------------------------------------------\n");
    printf("[%d]PM2.5:  %-4.1f %-5s", 1, data[1], "μg/m3");
    print_rating(data[1], WHO_24HOUR_PM2_5);
    printf("\n");

    printf("[%d]PM10:   %-4.1f %-5s", 2, data[2], "μg/m3");
    print_rating(data[2], WHO_24HOUR_PM10);
    printf("\n");

    printf("[%d]NO2:    %-4.1f %-5s", 3, data[3], "μg/m3");
    print_rating(data[3], WHO_24HOUR_NO2);
    printf("\n");

    printf("[%d]Temp:   %-4.1f %-5s  N/A\n", 4, data[4], "°C");
    printf("---------------------------------------------\n");
}

// Calculates the averages of the given data sets into avg
void average(float** data, int n, float* avg) {
    float pm25_sum = 0, pm10_sum = 0, no2_sum = 0, temp_sum = 0;

    for (int i = 0; i < n; i++) {
        pm25_sum += data[1][i];
        pm10_sum += data[2][i];
        no2_sum += data[3][i];
        temp_sum += data[4][i];
    }

    avg[0] = pm25_sum / n;
    avg[1] = pm10_sum / n;
    avg[2] = no2_sum / n;
    avg[3] = temp_sum / n;
}

void unix_to_date(time_t unix_time, char* date) {
    struct tm* time_info = localtime(&unix_time);
    strftime(date, 20, "%Y-%m-%d", time_info);
}

void unix_to_hour(time_t unix_time, char* hour) {
    struct tm* time_info = localtime(&unix_time);
    strftime(hour, 10, "%H", time_info);
}

void hour_display(char* road, time_t unix_time) {
    printf("\033[H\033[J");  // ANSI escape code to clear the screen
    float data[4] = {10, 5, 25, 20};

    char date[20];
    char hour[2];
    unix_to_date(unix_time, date);
    unix_to_hour(unix_time, hour);


    printf("%-20s%-20s%-20s:00\n", road, date, hour);
}

void day_display(char* road, time_t unix_time) {
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

    char date[20];
    unix_to_date(unix_time, date);
    printf("%-35s%s\n", road, date);

    print_data(avg);
}

void month_display(char* road, time_t unix_time) {
    //needs adaptation
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

    char date[20];
    unix_to_date(unix_time, date);
    printf("%-35s%s\n", road, date);

    print_data(avg);
}
