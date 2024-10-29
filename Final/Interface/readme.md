## How to create a new command

Step 1: Make a new constant in the Command enum (use the format `CMD_[name]`

Step 2: In command_table, add an entry for you command. The command string is the command itself the id is the constant you just created

Step 3: Create the function the command should call in the "Commands" section (use the format `command_[name]()`

Step 4: In the switch statement in `Execute_command()`, create a case for your command which is what the command does.


## How to create a new screen

Step 1: Make a new constant in the Screen enum (use the format `SCREEN_[name]`)

Step 2: Create the function used to print the screen in the "screens" sections (use the format `screen_[name]()`)

Step 3: Add the function that handles the screen to the switch statement in `display_screen()`.