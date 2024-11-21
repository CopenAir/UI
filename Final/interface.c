#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/csv_backend/csv.h"
#include "lib/Frontend/data_display.h"
#include "lib/custom_time/custom_time.h"

// View the readme.md for a guide on how to add stuff in here

#define RST_TERM "\033c"
#define WHO_24HOUR_PM2_5 1.5
#define WHO_24HOUR_PM10 4.5
#define WHO_24HOUR_NO2 2.5

// Emums -------------------------------------------------------------

// Enum for command id's
typedef enum {
    CMD_QUIT,
    CMD_HELP,
    CMD_RESET,
    CMD_LOCATION,
    CMD_GRAPH,
    CMD_TIME,
    CMD_DATA,
    CMD_TIMESPAN
} Command_id;

// Enum for screen id's
typedef enum {
    SCREEN_MAIN = 1,
    SCREEN_HELP,
    SCREEN_DATA,
    SCREEN_GRAPH,
} Screen;

// Enum for locations
typedef enum {
    FOLEHAVEN = 1,
    BACKERSVEJ,
    HILLEROESGADE,
} Location;

typedef enum {
    PM2_5 = 1,
    PM10,
    NO2,
} Measurement_type;

// Structs ------------------------------------------------------------------------

// Struct for each command entry
struct command_entry {
    char* command_string;
    Command_id command_id;
};

// Struct for location entries
struct location_entry {
    char* filename;
    Location location_id;
};

// Lookup table for storing the command entries
struct command_entry command_table[] = {
        {"quit", CMD_QUIT},
        {"q", CMD_QUIT},
        {"help", CMD_HELP},
        {"h", CMD_HELP},
        {"reset", CMD_RESET},
        {"r", CMD_RESET},
        {"location", CMD_LOCATION},
        {"l", CMD_LOCATION},
        {"graph", CMD_GRAPH},
        {"g", CMD_GRAPH},
        {"data", CMD_DATA},
        {"d", CMD_DATA},
        {"time", CMD_TIME},
        {"t", CMD_TIME},
        {"span", CMD_TIMESPAN},
        {"timespan", CMD_TIMESPAN},
        {"s", CMD_TIMESPAN}
};

struct location_entry location_table[] = {
        {"../data/folehaven.csv", FOLEHAVEN},
        {"../data/backersvej.csv", BACKERSVEJ},
        {"../data/hilleroedsgade.csv", HILLEROESGADE},
};

// Struct for handling the entered command
struct entered_command {
    int command_id;
    char* argument;
};

// Struct for program state
struct program_state {
    Screen current_screen;
    time_t current_time;
    Location current_location;
    Measurement_type current_measurement;
    struct timespan current_timespan;
    int running;
};

struct graph_args {
    char date[20];
    char *location_to_print;
    char *measurement;
    float threshold;
    float max_val;
    float x_size;
};

// Function Prototypes -------------------------------------------------------------

// Main functions
void get_input(char *input);
struct entered_command get_command(char *input_string);
void execute_command(struct entered_command entered_command, struct program_state *program_state);
void display_screen(struct program_state program_state);

// Command functions
void command_quit(struct program_state *program_state);
void command_help(struct program_state *program_state);
void command_reset(struct program_state *program_state);
void command_location(struct program_state *program_state);
void command_graph(struct program_state *program_state);
void command_data(struct program_state *program_state);
void command_time(struct program_state *program_state, char* argument);
void command_timespan(struct program_state *program_state);

// Screen functions
void screen_help();
void screen_main();
void screen_data(struct program_state *program_state);
void screen_graph(struct program_state *program_state);

// Helper functions
void screen_graph_args(struct program_state *program_state, struct graph_args *graph_args, float location_data[][MAX_ROWS]);
void clear_terminal();
void clear_input();

// Main Functions -----------------------------------------------------------------------

int main( )
{
    struct program_state program_state = {
            SCREEN_MAIN,
            1728932400,
            FOLEHAVEN,
            PM2_5,
            {
                1727992800,
                1728856800
            },
            1
    };
    char user_input[50];

    while(program_state.running) {
        struct entered_command entered_command;
        clear_terminal();

        display_screen(program_state);
        get_input(user_input);
        entered_command = get_command(user_input);

        execute_command(entered_command, &program_state);
    }

    return 0;
}

// Displays a screen based on the id of the current screen using a switch statement
void display_screen(struct program_state program_state) {
    switch (program_state.current_screen) {
        case SCREEN_MAIN:
            screen_main();
            break;
        case SCREEN_HELP:
            screen_help();
            break;
        case SCREEN_DATA:
            screen_data(&program_state);
            break;
        case SCREEN_GRAPH:
            screen_graph(&program_state);
            break;
        default:
            printf("Error: Screen with id %i does not exist", program_state.current_screen);
    }
}

// Gets the input of the user
void get_input(char *input) {
    printf("Enter Command:");

    // Using fgets instead of scanf to prevent input overflow.
    fgets(input, 50, stdin);

    // Removes the newline at the end of the string (cus fgets includes that).
    // strcspn returns how many characters there are before a newline is encountered. This number is also the placement of the newline, which then gets set to null.
    input[strcspn(input, "\n")] = '\0';
}

// Figures out what command the user typed.
struct entered_command get_command(char *input_string) {
    int command_id = -1;
    char command_string[50];
    char argument_string[50];

    // Creates a pointer to the first instance of a space. This indicates if an argument is starting here
    char *space_pointer = strchr(input_string, ' ');

    if (space_pointer != NULL) {
        // Copies the command part of the input to command_string. The length of the command part is calculated by subtracting the input_string pointer from space_pointer.
        strncpy(command_string, input_string, space_pointer - input_string);

        // Adds a null terminator to the end of command_string, as otherwise the string isnt stringing.
        command_string[space_pointer - input_string] = '\0';

        // Copies the argument part of the input to argument_string (not including the space)
        strcpy(argument_string, space_pointer + 1);
    } else {
        strcpy(command_string, input_string);
    }

    // Finds the command id of the command_string (if it exists)
    for (int i = 0; i < sizeof (command_table) / sizeof (command_table[0]); i++) {
        if (strcmp(command_string, command_table[i].command_string) == 0) {
            command_id = command_table[i].command_id;
            break;
        }
    }

    struct entered_command entered_command = {command_id, argument_string};

    return entered_command;
}

// Executes a command based on its id using a switch statement
void execute_command(struct entered_command entered_command, struct program_state *program_state) {
    switch (entered_command.command_id) {
        case CMD_QUIT:
            command_quit(program_state);
            break;
        case CMD_HELP:
            command_help(program_state);
            break;
        case CMD_RESET:
            command_reset(program_state);
            break;
        case CMD_LOCATION:
            command_location(program_state);
            break;
        case CMD_GRAPH:
            command_graph(program_state);
            break;
        case CMD_DATA:
            command_data(program_state);
            break;
        case CMD_TIME:
            command_time(program_state, entered_command.argument);
            break;
        case CMD_TIMESPAN:
            command_timespan(program_state);
            break;
        default:
            printf("Error: No command found with ID: %i\n", entered_command.command_id);
    }
}

// Commands ---------------------------------------------------------

void command_help(struct program_state *program_state) {
    program_state->current_screen = SCREEN_HELP;
}

void command_data(struct program_state *program_state){
    program_state->current_screen = SCREEN_DATA;
}

void command_quit(struct program_state *program_state) {
    clear_terminal();
    program_state->running = 0;
}

void command_reset(struct program_state *program_state) {
    program_state->current_screen = SCREEN_MAIN;
    program_state->current_time = 1728932400;
    program_state->current_location = FOLEHAVEN;
    program_state->current_measurement = PM2_5;
    program_state->current_timespan.start_date = 1727992800;
    program_state->current_timespan.end_date = 1728856800;
}

void command_location(struct program_state *program_state) {
    clear_terminal();
    printf("Select Location:\n");
    printf("_____________________________________________\n");
    printf(" [1] Folehaven\n");
    printf(" [2] Backersvej\n");
    printf(" [3] Hillerroedsgade\n");
    printf("______________________________________________\n");
    printf("Enter Number: ");

    Location new_location = -1;

    // Gets input for what location to choose until the input is valid and withing the accepted values.
    while (!scanf("%i", &new_location) || new_location > 3 || new_location < 1) {
        clear_input();
        printf("Invalid Input, please try again: ");
    };

    program_state->current_location = new_location;
    program_state->current_screen = SCREEN_DATA;
}

void command_graph(struct program_state *program_state) { //threshold value does not change
    char input[32];
    Measurement_type new_measurement_type = -1;

    clear_terminal();
    printf("Select measurement type:\n");
    printf("_____________________________________________\n");
    printf(" [1] PM2.5\n");
    printf(" [2] PM10\n");
    printf(" [3] NO2\n");
    printf("______________________________________________\n");

    // Gets input for what location to choose until the input is valid and withing the accepted values.
    do {
        printf("Enter Number: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        new_measurement_type = strtol(input, NULL, 10); // converts string to int, radix value 10 means decimal number
    } while (new_measurement_type < 1 || new_measurement_type > 3);

    program_state->current_measurement = new_measurement_type;
    program_state->current_screen = SCREEN_GRAPH;
}

// promts the user for what date to change to, then converts the time string to unixtime and sets the current time to that
void command_time(struct program_state *program_state, char* argument) {
    char input[32];
    time_t new_time;

    clear_terminal();

    // if the user gave an argument, attempt to change the time to that argument, otherwise continue as if no argument was given
    if (argument[0] != '\0') {
        new_time = string_to_unixtime(argument);
        if (new_time != -1) {
            program_state->current_time = new_time;
            return;
        }

        // printf("Invalid time format in argument\n");
    }

    printf("Data is available for dates between 2023-10-15 and 2024-10-13\n");
    printf("---------------------------------------------\n");
    printf("Enter data and time in 'YYYY-MM-DD HH' format: ");

    while(1) {
        // use fgets as the input requires a space (which scanf isnt able to handle)
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        clear_terminal();

        // converts the string to unixtime
        new_time = string_to_unixtime(input);

        // if there are no errors, set the current time to the new time and exit loop
        if (new_time != -1) {
            program_state->current_time = new_time;
            break;
        }

        printf("Data is available for dates between 2023-10-15 and 2024-10-13\n");
        printf("---------------------------------------------\n");
        printf("Enter data and time in 'YYYY-MM-DD HH' format: ");
    }
}

void command_timespan(struct program_state *program_state) {
    char input[32], start_date_string[32];
    struct timespan timespan;

    clear_terminal();
    printf("Data is available for dates between 2023-10-15 and 2024-10-13\n");
    printf("Selecting timespan: xxxx-xx-xx - xxxx-xx-xx\n");
    printf("---------------------------------------------\n");
    printf("Enter start date in 'YYYY-MM-DD' format: ");

    while(1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        strcpy(start_date_string, input); // start_date_string is just used for showing the user their chosen date

        strcat(input, " 12");
        clear_terminal();

        timespan.start_date = string_to_unixtime(input);
        if (timespan.start_date != -1) {
            break;
        }
        printf("Data is available for dates between 2023-10-15 and 2024-10-13\n");
        printf("Selecting timespan: xxxx-xx-xx - xxxx-xx-xx\n");
        printf("---------------------------------------------\n");
        printf("Enter end date in 'YYYY-MM-DD' format: ");
    }

    printf("Data is available for dates between 2023-10-15 and 2024-10-13\n");
    printf("Selecting timespan: %s - xxxx-xx-xx\n", start_date_string);
    printf("---------------------------------------------\n");
    printf("Enter end date in 'YYYY-MM-DD' format: ");

    while(1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        strcat(input, " 00");
        clear_terminal();

        timespan.end_date = string_to_unixtime(input);
        if (timespan.end_date != -1) {
            break;
        }

        printf("Data is available for dates between 2023-10-15 and 2024-10-13\n");
        printf("Selecting timespan: %s - xxxx-xx-xx\n", start_date_string);
        printf("---------------------------------------------\n");
        printf("Enter end date in 'YYYY-MM-DD' format: ");
    }

    program_state->current_timespan = timespan;
}

// Screens -----------------------------------------------------------------

void screen_main() {
    printf("Welcome\n\n");
    printf("Enter h or help for help\n");
    printf("Enter q or quit to quit\n");
    printf("Enter l or location to select location\n");
    printf("Enter g or graph to create a barchart of selected data\n");
    printf("Enter t or time to select time\n");
    printf("Enter span or timespan to select the timespan of data\n");
    printf("Enter d or data to display data table\n");
    printf("--------------------------------------\n");
}

void screen_help() {
    printf("Commands:\n");
    printf("  q or quit - Quits the program\n");
    printf("  h or help - Display this message\n");
    printf("  r or reset - Resets program back to original state\n");
    printf("  l or location - selects data location\n");
    printf("  g or graph - Prints out barchart of selected data\n");
    printf("  t or time to select time\n");
    printf("  span or timespan to select the timespan of data\n");
    printf("  d or data to display data table");
    printf("  \n");
    printf("------------------------------------------------------\n");
    printf("  Type l to select a location, and then choose one of the locations displayed on screen\n");
    printf("  Once a selection has been made, this will automatically show you the data for the given location\n");
    printf("  You can now type 't'/'time' to set a specific time or interval you wanna view the data for\n");
    printf("  Finally you can display the data visually using 'g'/'graph'\n");
    printf("  From any screen you can navigate to another. so from graph for example you can either select a different time, or go back to data\n");;
    printf("------------------------------------------------------\n");
}

void screen_data(struct program_state *program_state) {
    char *filename = "none";

    // gets the filename for the location
    for (int i = 0; i < sizeof (location_table) / sizeof (location_table[0]); i++) {
        if (program_state->current_location == location_table[i].location_id) {
            filename = location_table[i].filename;
            break;
        }
    }

    float data[5];

    if (get_data_for_date(filename, data, program_state->current_time) == -1) {
        printf("Couldnt load data for file: %s\n", filename);
        return;
    }

    print_data(data);
}

void screen_graph(struct program_state *program_state) {
    char *filename = "none";

    for (int i = 0; i < sizeof (location_table) / sizeof (location_table[0]); i++) {
        if (program_state->current_location == location_table[i].location_id) {
            filename = location_table[i].filename;
            break;
        }
    }

    float location_data[MAX_COLUMNS][MAX_ROWS];

    if (get_data_for_timespan(filename, location_data, program_state->current_timespan) == -1) {
        printf("Couldnt load data for file: %s\n", filename);
        return;
    }

    struct graph_args graph_args = {
        .date = "",
        .location_to_print = NULL,
        .measurement = NULL,
        .threshold = 0.0,
        .max_val = 0.0,
        .x_size = 0.0
    };

    screen_graph_args(program_state, &graph_args, location_data);

    printf("Date: %s | Area: %s\n", graph_args.date, graph_args.location_to_print);
    printf("Substance: %s\n", graph_args.measurement);

    draw_graph(graph_args.x_size, location_data[program_state->current_measurement], graph_args.max_val, graph_args.threshold);

    printf("\n\n--------------------------------------------\n");
}

// Helper functions ----------------------------------------
void screen_graph_args(struct program_state *program_state, struct graph_args *graph_args, float location_data[][MAX_ROWS]) {
    struct tm* time_info = localtime(&program_state->current_time);
    strftime(graph_args->date, 20, "%Y-%m-%d", time_info);

    switch(program_state->current_location) {
        case FOLEHAVEN:
            graph_args->location_to_print = "Folehaven";
            break;
        case BACKERSVEJ:
            graph_args->location_to_print = "Backersvej";
            break;
        case HILLEROESGADE:
            graph_args->location_to_print = "Hillerødsgade";
            break;
    }

    switch(program_state->current_measurement) {
        case PM2_5:
            graph_args->measurement = "P2.5";
            graph_args->threshold = WHO_24HOUR_PM2_5;
            break;
        case PM10:
            graph_args->measurement = "P10";
            graph_args->threshold = WHO_24HOUR_PM10;
            break;
        case NO2:
            graph_args->measurement = "NO2";
            graph_args->threshold = WHO_24HOUR_NO2;
            break;
    }

    float (*data)[MAX_ROWS] = location_data;
    for(int i = 0; i < MAX_ROWS; i++) {
        if (data[program_state->current_measurement][i] > 0.0) {
            graph_args->x_size += 1;
        }
        if(data[program_state->current_measurement][i] > graph_args->max_val) {
            graph_args->max_val = data[program_state->current_measurement][i];
        }
    }
}

// Used to clear the terminal.
void clear_terminal() {
    printf(RST_TERM);
}

// Clears just the input
void clear_input() {
    while ((getchar()) != '\n');
}
