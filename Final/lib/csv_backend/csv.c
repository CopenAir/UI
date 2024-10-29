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

int load_data(char *filename, double data_matrix[][MAX_ROWS]) {
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
            value = strtok(NULL, ",");
        }
        row++;
    }

    fclose(data);

    return 0;
}