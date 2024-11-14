#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/csv_backend/csv.h"
#include "lib/Frontend/data_display.h"

// View the readme.md for a guide on how to add stuff in here

// Emums -------------------------------------------------------------

// Enum for command id's
typedef enum {
    CMD_QUIT,
    CMD_HELP,
    CMD_RESET,
    CMD_LOCATION,
    CMD_GRAPH,
    CMD_TIME, //TO BE IMPLEMENTED
    CMD_DATA
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
    LAST_LOCATION = HILLEROESGADE,
} Location;

typedef enum {
    PM2_5 = 1,
    PM10,
    NO2,
    // Im not expecting us to add more measurement types, but if it does happen remember to edit NO2 to the new last value in command_graph()
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
        {"d", CMD_DATA}
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


// Function Prototypes -------------------------------------------------------------

// Main functions
void get_input(char *input);
struct entered_command get_command(char *input_string);
void execute_command(struct entered_command entered_command, Screen *screen_id, Location *current_location, Measurement_type *current_measurement);
void display_screen(Screen current_screen, Location current_location, int current_date, Measurement_type current_measurement);

// Command functions
void command_quit(Screen *screen_id);
void command_help(Screen *screen_id);
void command_reset(Screen *screen_id);
void command_location(Screen *screen_id, Location *current_location);
void command_graph(Screen *screen_id, Measurement_type *current_measurement);
void command_data(Screen *screen_id);

// Screen functions
void screen_help();
void screen_main();
void screen_data(Location location_id, int date);
void screen_graph(Location location_id, Measurement_type measurement);

// Helper functions
void clear_terminal();
void clear_input();

// Main Functions -----------------------------------------------------------------------

int main( )
{
    Screen current_screen = SCREEN_MAIN;
    //standards
    int current_date = 1728932400; // TODO: might want to do this dynamically instead
    Location current_location = FOLEHAVEN;
    Measurement_type current_measurement = PM2_5;
    char user_input[10];

    while(current_screen > 0) {
        struct entered_command entered_command;
        clear_terminal();

        display_screen(current_screen, current_location, current_date, current_measurement);
        get_input(user_input);
        entered_command = get_command(user_input);
        execute_command(entered_command, &current_screen, &current_location, &current_measurement);
    }

    return 0;
}

// Displays a screen based on the id of the current screen using a switch statement
void display_screen(Screen current_screen, Location current_location, int current_date, Measurement_type current_measurement) {
    switch (current_screen) {
        case SCREEN_MAIN:
            screen_main();
            break;
        case SCREEN_HELP:
            screen_help();
            break;
        case SCREEN_DATA:
            screen_data(current_location, current_date);
            break;
        case SCREEN_GRAPH:
            screen_graph(current_location, current_measurement);
            break;
        default:
            printf("Error: Screen with id %i does not exist", current_screen);
    }
}

// Gets the input of the user
void get_input(char *input) {
    printf("Enter Command:");

    // Using fgets instead of scanf to prevent input overflow.
    //fgets(input, 50, stdin);
    scanf("%10s", input);

    // Removes the newline at the end of the string (cus fgets includes that).
    // strcspn returns how many characters there are before a newline is encountered. This number is also the placement of the newline, which then gets set to null.
    //input[strcspn(input, "\n")] = '\0';
    return;
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
void execute_command(struct entered_command entered_command, Screen *screen_id, Location *current_location, Measurement_type *current_measurement) {
    switch (entered_command.command_id) {
        case CMD_QUIT:
            command_quit(screen_id);
            break;
        case CMD_HELP:
            command_help(screen_id);
            break;
        case CMD_RESET:
            command_reset(screen_id);
            break;
        case CMD_LOCATION:
            command_location(screen_id, current_location);
            break;
        case CMD_GRAPH:
            command_graph(screen_id, current_measurement);
            break;
        case CMD_DATA:
            command_data(screen_id);
            break;
        default:
            printf("Invalid Command\n");
    }
}

// Commands ---------------------------------------------------------

void command_help(Screen *screen_id) {
    *screen_id = SCREEN_HELP;
}

void command_data(Screen *screen_id){
    *screen_id = SCREEN_DATA;
}

void command_quit(Screen *screen_id) {
    clear_terminal();
    exit(0); //yes it's nasty, but it works
}

void command_reset(Screen *screen_id) {
    *screen_id = SCREEN_MAIN;
}

void command_location(Screen *screen_id, Location *current_location) {
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

    *current_location = new_location;
    *screen_id = SCREEN_DATA;
}

void command_graph(Screen *screen_id, Measurement_type *current_measurement) { //threshold value does not change
    clear_terminal();
    printf("Select measurement type:\n");
    printf("_____________________________________________\n");
    printf(" [1] PM2.5\n");
    printf(" [2] PM10\n");
    printf(" [3] NO2\n");
    printf("______________________________________________\n");
    printf("Enter Number: ");

    Measurement_type new_measurement_type = -1;

    // Gets input for what location to choose until the input is valid and withing the accepted values.
    while (!scanf("%i", &new_measurement_type) || new_measurement_type > 3 || new_measurement_type < 1) {
        clear_input();
        printf("Invalid Input, please try again: ");
    };

    *current_measurement = new_measurement_type;
    *screen_id = SCREEN_GRAPH;
}

// Screens -----------------------------------------------------------------

void screen_main() {
    printf("Welcome\n\n");
    printf("Enter h or help for help\n");
    printf("Enter q or quit to quit\n");
    printf("Enter l or location to select location\n");
    printf("Enter g or graph to create a barchart of selected data\n");
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
    printf("  d or data to display data table");
    printf("  \n");
    printf("  \n");
}

void screen_data(Location location_id, int date) {
    char *filename = "none";

    for (int i = 0; i < sizeof (location_table) / sizeof (location_table[0]); i++) {
        if (location_id == location_table[i].location_id) {
            filename = location_table[i].filename;
            break;
        }
    }

    float data[5];

    if (get_data_for_date(filename, data, date) == -1) {
        printf("Couldnt load data for file: %s\n", filename);
        return;
    }

    print_data(data);
}

//TODO: Lot of repetition from screen_data, could shorten it by having a helper function
void screen_graph(Location location_id, Measurement_type measurement) {
    char *filename = "none";

    for (int i = 0; i < sizeof (location_table) / sizeof (location_table[0]); i++) {
        if (location_id == location_table[i].location_id) {
            filename = location_table[i].filename;
            break;
        }
    }

    float location_data[5][MAX_ROWS];

    if (load_data(filename, location_data) == -1) {
        printf("Couldnt load data for file: %s\n", filename);
        return;
    }

    // TODO: Set threshold depending on selected measurement type. Add option to chose date interval as well cus rn it just takes the first 10 entries
    // TODO: Print Road name, Time and substance type
    draw_graph(10, location_data[measurement], 5.0, 3.0);

    printf("\n\n--------------------------------------------\n");
}

// Helper functions ----------------------------------------

// Used to clear the terminal.
void clear_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Clears just the input
void clear_input() {
    while ((getchar()) != '\n');
}
