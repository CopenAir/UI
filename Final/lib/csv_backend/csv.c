#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../custom_time/custom_time.h"

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

// gets the data for a specific date
int get_data_for_date(const char *filename, float data_array[], time_t date) {
    float location_data[MAX_COLUMNS][MAX_ROWS] = {0};  // Initialize to avoid uninitialized memory issues

    if (load_data(filename, location_data) == -1) {
        return -1;
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        if (location_data[0][i] == (float)date) {
            // Copy the row for the specified date
            for (int j = 0; j < MAX_COLUMNS; j++) {
                data_array[j] = location_data[j][i];
            }
            return 0;
        }
    }

    return -1;  // Return -1 if date not found
}

// Gets data from each day at midday within a timespan
// TODO: Instead of just grapping the values on midday, we could get the average instead. I cant be bothered to do this rn tho
int get_data_for_timespan(const char *filename, float data_matrix[MAX_COLUMNS][MAX_ROWS], struct timespan timespan) {
    float location_data[MAX_COLUMNS][MAX_ROWS] = {0}; // Initialize to avoid uninitialized memory issues

    if (load_data(filename, location_data) == -1) {
        return -1;
    }

    int data_index = 0;

    // iterates over every row in the raw data
    for (int i = 0; i < MAX_ROWS; i++) {

        // checks if the time of the current row is between the chosen start and end time
        if (!(location_data[0][i] >= (float) timespan.start_date && location_data[0][i] <= (float) timespan.end_date)) {
            continue;
        }

        // checks if the time is at midday (as we only want one measurement per day)
        if (!is_midday((time_t) location_data[0][i])) {
            continue;
        }

        // Copy the row for the specified date
        for (int j = 0; j < MAX_COLUMNS; j++) {
            data_matrix[j][data_index] = location_data[j][i];
        }

        data_index++;
    }

    return 0;
}
