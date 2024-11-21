# CopenAir data visualisation interface
---------------------------------------
# Default values
  Data = Folehaven
  Time = 2024-10-03 -> 2024-10-13
  Graph index = PM2.5

# Usage
User can freely use following commands to set time, location, timespan, and view the data in several different ways
  printf("Enter h or help for help\n");
  printf("Enter q or quit to quit\n");
  printf("Enter l or location to select location\n");
  printf("Enter g or graph to create a barchart of selected data\n");
  printf("Enter t or time to select time\n");
  printf("Enter span or timespan to select the timespan of data\n");
  printf("Enter d or data to display data table\n");

From any screen it's possible to navigate to a different screen.
Some screens will function like individual screens, meaning once you've gone to them you'll actively have to go to another for it to disappear
Others will act as menus (timespan is an example of this) that will automatically take you back to previous screen once interaction is completed

**PLEASE DO NOT MOVE, REMOVE, OR OTHERWISE MODIFY THE "data" FOLDER OR IT'S CONTENT**

# Technical

## Code Organization
### Enumerations
**Command_id**

Defines commands supported by the application:

    CMD_QUIT, CMD_HELP, CMD_RESET, etc.

**Screen**

Defines screen states for the program:

    SCREEN_MAIN, SCREEN_HELP, SCREEN_DATA, SCREEN_GRAPH.

**Location**

Defines available data locations:

    FOLEHAVEN, BACKERSVEJ, HILLEROESGADE.

**Measurement_type**

Defines air quality measurements:

    PM2_5, PM10, NO2.

Structs**
**command_entry**

Maps user-entered commands to their corresponding Command_id.
```c
struct command_entry {
    char* command_string;
    Command_id command_id;
};```

**location_entry**

Maps locations to their corresponding CSV file paths.
```c
struct location_entry {
    char* filename;
    Location location_id;
};```

**entered_command**

Represents a parsed user command.

struct entered_command {
    int command_id;
    char* argument;
};

**program_state**

Represents the current state of the program, including active screen, selected location, time range, etc.

```c
struct program_state {
    Screen current_screen;
    time_t current_time;
    Location current_location;
    Measurement_type current_measurement;
    struct timespan current_timespan;
    int running; // Program status: 1 = running, 0 = stopped
};```

**graph_args**

Stores arguments used for graph visualization.
```c
struct graph_args {
    char date[20];
    char *location_to_print;
    char *measurement;
    float threshold;
    float max_val;
    float x_size;
};```

## Functions
### Main Functions
main**

Initializes the program state and enters the main loop, where it continuously processes user input until terminated.
get_input

Captures user input safely, ensuring no overflow.

void get_input(char *input);

get_command

Parses user input to identify the command and argument.

struct entered_command get_command(char *input_string);

execute_command

Executes commands based on the parsed input.

void execute_command(struct entered_command entered_command, struct program_state *program_state);

display_screen

Switches between screens based on the current program state.

void display_screen(struct program_state program_state);

Command Functions

Each function corresponds to a command:

    command_quit: Stops the program.
    command_help: Switches to the help screen.
    command_reset: Resets the program to its initial state.
    command_location: Allows the user to select a location.
    command_graph: Prompts the user to select a measurement type and visualizes the data as a graph.
    command_time: Updates the current time based on user input.
    command_timespan: Allows the user to select a start and end date.

Screen Functions
**screen_main**

Displays the main menu with available commands.

void screen_main();

**screen_help**

Displays detailed help information.

void screen_help();

**screen_data**

Displays data for the current location and time.

void screen_data(struct program_state *program_state);

**screen_graph**

Visualizes the selected data as a graph.

void screen_graph(struct program_state *program_state);

Helper Functions
**screen_graph_args**

Populates arguments for the graph visualization.

void screen_graph_args(struct program_state *program_state, struct graph_args *graph_args, float location_data[][MAX_ROWS]);

**clear_terminal**

Clears the terminal display.

void clear_terminal();

**clear_input**

Clears residual input from the stdin buffer.

void clear_input();

## Data Management
### CSV Integration

    Location-Specific Files: Data is loaded from CSV files defined in the location_table.
    Functions:
        get_data_for_date: Fetches data for a specific date.
        get_data_for_timespan: Retrieves data for a time range.

### Dependencies

    lib/csv_backend/csv.h: Handles CSV parsing.
    lib/Frontend/data_display.h: Provides UI-related functions like draw_graph.
    lib/custom_time/custom_time.h: Converts date strings to Unix time and vice versa.
