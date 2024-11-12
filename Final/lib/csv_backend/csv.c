#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 5
#define MAX_ROWS 8785

int load_data(const char *filename, float data_matrix[][MAX_ROWS]) {
    const char *delimiter = ",";  // Delimiter as a string for strtok
    FILE *data = fopen(filename, "r");
    if (data == NULL) {
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int row = 0;

    // Skip the first line with headers
    if (fgets(line, sizeof(line), data) == NULL) {
        fclose(data);
        return -1;  // Failed to read header line
    }

    // Read data rows
    while (fgets(line, sizeof(line), data) && row < MAX_ROWS) {
        char *value = strtok(line, delimiter);
        for (int col = 0; col < MAX_COLUMNS; col++) {
            if (value != NULL) {
                data_matrix[col][row] = atof(value);
                value = strtok(NULL, delimiter);
            } else {
                data_matrix[col][row] = 0.0f;  // Set missing values to 0 for safety
            }
        }
        row++;
    }

    fclose(data);
    return 0;
}

int get_data_for_date(const char *filename, float data_array[], int date) {
    float location_data[MAX_COLUMNS][MAX_ROWS] = {0};  // Initialize to avoid uninitialized memory issues

    if (load_data(filename, location_data) == -1) {
        return -1;
    }

    int date_found = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        if (location_data[0][i] == (float)date) {
            date_found = 1;
            // Copy the row for the specified date
            for (int j = 0; j < MAX_COLUMNS; j++) {
                data_array[j] = location_data[j][i];
            }
            break;
        }
    }

    return date_found ? 0 : -1;  // Return -1 if date not found
}
