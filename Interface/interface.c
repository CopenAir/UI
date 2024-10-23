#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// View the readme.md for a guide on how to add stuff in here


// Enum for command id's
typedef enum {
    CMD_QUIT,
    CMD_HELP,
    CMD_RESET,
    CMD_LOCATION,
} Command;

// Enum for screen id's
typedef enum {
    SCREEN_MAIN = 1,
    SCREEN_HELP,
    SCREEN_DATA,
    SCREEN_GRAPH
} Screen;

// Struct for each command entry
struct command_entry {
    char* command_string;
    Command command_id;
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
};

// Function Declarations ------------------------------------
// Main functions
char* get_input();
int get_command(char *command_string);
void execute_command(int command_id, int *screen_id);
void display_screen(int current_screen);

// Command functions
void command_quit(int *screen_id);
void command_help(int *screen_id);
void command_reset(int *screen_id);

// Screen functions
void screen_help();
void screen_main();

// Helper functions
void clear_terminal();

int main( )
{
    int current_screen = SCREEN_MAIN;

    while(current_screen > 0) {
        int command_id;

        clear_terminal(); // Clears terminal

        // Displays the screen based on its id (could refactor into its own function)
        display_screen(current_screen);

        char *user_input = get_input();

        command_id = get_command(user_input);
        execute_command(command_id, &current_screen);

        free(user_input);
    }

    return 0;
}

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
    scanf("%s", input);

    return input;
}

// Figures out what command the user typed.
int get_command(char *command_string) {
    int command_id = -1;

    for (int i = 0; i < sizeof (command_table) / sizeof (command_table[0]); i++) {
        if (strcmp(command_string, command_table[i].command_string) == 0) {
            command_id = command_table[i].command_id;
            break;
        }
    }

    return command_id;
}

// Executes a command based on its id
void execute_command(int command_id, int *screen_id) {
    switch (command_id) {
        case CMD_QUIT:
            printf("command_quit\n");
            command_quit(screen_id);
            break;
        case CMD_HELP:
            printf("help\n");
            command_help(screen_id);
            break;
        case CMD_RESET:
            printf("reset\n");
            command_reset(screen_id);
            break;
        case CMD_LOCATION:
            printf("location\n");
            // TODO
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
