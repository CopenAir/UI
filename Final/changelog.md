07/11/24 @ 07:53
--------------------
- Fixed an issue with folehaven.csv where "f" was capitalized
- Fixed an issue with the draw_graph() function where dual decimals would cause a left shift of the graph
- Updated main_screen and help_screen to accomodate for location and graph commands
- Removed unneeded function "arg_test"
- Added comments for issues and improvements on several functions

07/11/24 @ 09:40
--------------------
- Fixed "CMD_QUIT"

07/11/24 @ 16:28
--------------------
- Added "CMD_DATA"
- Cleaned up in ".h" files and removed unnecessary "#define"
- Defined "RED", "GREEN", "RESET_COLOUR" & "CLR_SCREEN" in "data_display.c" to improve readability

08/11/24 @ 08:20
--------------------
- Traced several issues including "empty first column" and "repeating y axis" back to interface.c
- replaced y-axis enumerator with integer system for easier scalability
- Patched an issue where "csv.c" would load the headers on line 1, from the csv files
