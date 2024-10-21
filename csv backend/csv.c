#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_data(char *filename, double data_matrix[][8785]);

int main() {
    double data_matrix[5][8785];
    char *filename = "data.csv";

    switch(load_data(filename, data_matrix)) {
        case -1:
            printf("Error opening file %s\n", filename);
            return -1;
        default:
            printf("Data loaded successfully\n");
            break;
    }

    return 0; 
}

int load_data(char *filename, double data_matrix[][8785]) {
    FILE *data = fopen(filename, "r");
    if (data == NULL) {
        return -1;
    }

    char *headers[] = {"Time", "PM2", "PM10", "NO2", "TEMP"}; // Declare and initialize headers array
    char line[1024];
    int row = 0;
    while (fgets(line, sizeof(line), data)) {
        char *value = strtok(line, ",");
        for (int col = 0; col < 5; col++) {
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