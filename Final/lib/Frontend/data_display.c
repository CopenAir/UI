#include <stdio.h>
#include <time.h>

// WHO guidelines for air pollution from 2021
// https://www.who.int/news-room/feature-stories/detail/what-are-the-who-air-quality-guidelines
#define WHO_24HOUR_PM2_5 15
#define WHO_24HOUR_PM10 45
#define WHO_24HOUR_NO2 25

//define colour
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET_COLOUR "\x1b[0m"

void draw_graph(int size, float *data, float max_val, float threshold) {
    //TODO: Implement dynamic scalling
    int steps = (int)(max_val * 10);

    for (int step = steps; step >= 0; step--) {
        float i = step / 10.0;

        printf("%s", i >= 10.0 ? "" : " ");
        printf("%s%.1f║", i <= threshold ? GREEN : RED, i);

        for (int j = 0; j < size; j++) {
            printf("%s", data[j] >= i ? "███ " : "    ");
        }
        printf("\n%s", RESET_COLOUR);
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
        printf("%s  within tolerances %s", GREEN, RESET_COLOUR);
    else
        printf("%s  outside tolerances %s", RED, RESET_COLOUR);
}

void print_data(float data[]) {
    printf("---------------------------------------------\n");
    printf(" %-10s %-10s %-10s\n", "Substance", "Data", "Rating");
    printf("---------------------------------------------\n");
    printf("[%d]PM2.5:   %-4.1f%-5s", 1, data[1], "μg/m3"); //add spaces as needed
    print_rating(data[1], WHO_24HOUR_PM2_5);
    printf("\n");

    printf("[%d]PM10:    %-4.1f%-5s", 2, data[2], "μg/m3");
    print_rating(data[2], WHO_24HOUR_PM10);
    printf("\n");

    printf("[%d]NO2:     %-4.1f%-5s", 3, data[3], "μg/m3");
    print_rating(data[3], WHO_24HOUR_NO2);
    printf("\n");

    printf("[%d]Temp:    %-4.1f%-5s   N/A\n", 4, data[4], "°C");
    printf("---------------------------------------------\n");
}
