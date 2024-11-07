/*  Backend CSV matrix loader
    21/10/2024 @ 11:24
    csv.c V1.2

    Sebastian Lindau-Skands & Fabian Loki */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 5
#define MAX_ROWS 8785

int load_data(char *filename, float data_matrix[][MAX_ROWS]) {
    char delimiter = ',';
    FILE *data = fopen(filename, "r");
    if (data == NULL) {
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int row = 0;

    while (fgets(line, sizeof(line), data)) {
        char *value = strtok(line, &delimiter);
        for (int col = 0; col < MAX_COLUMNS; col++) {
            if (value != NULL) {
                data_matrix[col][row] = atof(value);
            }
            value = strtok(NULL, &delimiter);
        }
        row++;
    }

    fclose(data);

    return 0;
}

int get_data_for_date(char *filename, float data_array[], int date) {
    float location_data[5][MAX_ROWS];

    if (load_data(filename, location_data) == -1) {
        return -1;
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        if (location_data[0][i] == date) {
            // When the date is found, extract the data for that date
            for (int j = 0; j < 5; j++) {
                data_array[j] = location_data[j][i];
            }

            break;
        }
    }

    return 0;
}
