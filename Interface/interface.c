#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// View the readme.md for a guide on how to add stuff in here


// Emums -------------------------------------------------------------

// Enum for command id's
typedef enum {
    CMD_QUIT,
    CMD_HELP,
    CMD_RESET,
    CMD_LOCATION,
    CMD_ARG_TEST,
} Command_id;

// Enum for screen id's
typedef enum {
    SCREEN_MAIN = 1,
    SCREEN_HELP,
    SCREEN_DATA,
    SCREEN_GRAPH
} Screen;

// Enum for booleans cus C doesnt have these for some reason >:(
typedef enum {
    FALSE,
    TRUE
} Bool;


// Structs ------------------------------------------------------------------------

// Struct for each command entry
struct command_entry {
    char* command_string;
    Command_id command_id;
    Bool allow_argument;
};

// Lookup table for storing the command entries
struct command_entry command_table[] = {
        {"quit", CMD_QUIT, FALSE},
        {"q", CMD_QUIT, FALSE},
        {"help", CMD_HELP, FALSE},
        {"h", CMD_HELP, FALSE},
        {"reset", CMD_RESET, FALSE},
        {"r", CMD_RESET, FALSE},
        {"location", CMD_LOCATION, FALSE},
        {"arg_test", CMD_ARG_TEST, TRUE},
};

// Struct for handling the entered command
struct entered_command {
    int command_id;
    char* argument;
};


// Function Declarations -------------------------------------------------------------

// Main functions
char* get_input();
struct entered_command get_command(char *input_string);
void execute_command(struct entered_command entered_command, int *screen_id);
void display_screen(int current_screen);

// Command functions
void command_quit(int *screen_id);
void command_help(int *screen_id);
void command_reset(int *screen_id);
void command_arg_test(char* argument);

// Screen functions
void screen_help();
void screen_main();

// Helper functions
void clear_terminal();

int main( )
{
    int current_screen = SCREEN_MAIN;

    while(current_screen > 0) {
        struct entered_command entered_command;

        clear_terminal();

        display_screen(current_screen);

        char *user_input = get_input();
        entered_command = get_command(user_input);
        execute_command(entered_command, &current_screen);

        free(user_input);
    }

    return 0;
}

// Displays a screen based on the id of the current screen using a switch statement
void display_screen(int current_screen) {
    switch (current_screen) {
        case SCREEN_MAIN:
            screen_main();
            break;
        case SCREEN_HELP:
            screen_help();
            break;
        case SCREEN_DATA:
            // TODO
            break;
        default:
            printf("Error");
    }
}

// Gets the input of the user
char* get_input() {
    char *input = malloc(50);
    printf("Enter Command:");

    // Using fgets instead of scanf to prevent input overflow.
    fgets(input, 50, stdin);

    // Removes the newline at the end of the string (cus fgets includes that).
    // strcspn returns how many characters there are before a newline is encountered. This number is also the placement of the newline, which then gets set to null.
    input[strcspn(input, "\n")] = '\0';

    return input;
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
void execute_command(struct entered_command entered_command, int *screen_id) {
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
            printf("location\n");
            // TODO
            break;
        case CMD_ARG_TEST:
            command_arg_test(entered_command.argument);
            break;
        default:
            printf("Invalid Command\n");
    }
}

// Commands ---------------------------------------------------------

void command_help(int *screen_id) {
    *screen_id = 2;
}

void command_quit(int *screen_id) {
    *screen_id = -1;
}

void command_reset(int *screen_id) {
    *screen_id = 1;
}

void command_arg_test(char* argument) {
    printf("You entered argument: %s\nEnter any key to continue:", argument);
    fgets(argument, 10, stdin);
}

// Screens -----------------------------------------------------------------

void screen_main() {
    printf("welcome\n\n");
    printf("Enter help for help\n");
    printf("Enter quit to quit\n");
    printf("--------------------------------------\n");
}

void screen_help() {
    printf("Commands:\n");
    printf("  q or quit - Quits the program\n");
    printf("  h or help - Display this message\n");
    printf("  r or reset - Resets program back to original state\n");
    printf("  \n");
    printf("  \n");
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
