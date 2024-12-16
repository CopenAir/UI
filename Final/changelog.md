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

12/11/24 @ 16:26
--------------------
- fixed several issues in csv.c that prevented O2, O3, Ofast, Os and Og optimisation in reading data correctly

14/11/24 @ 14:05
-------------------
- Fixed a memory leak by replacing memaloc with a staticly allocated char pointer
- Fixed the Y-axis repetition issue by replacing system("clear") with printf("\033c") (the reset_terminal signal)
- rewrote clear_screen function to acomodate for y-axis fix
- created definition for RST_TERM
- Removed unnecesarry definitions and lines in data_display.c for screen clearing
- Fixed an issue where column 0 in graphs would be empty
- Fixed an issue where draw_graph() would be called twice (however only 1 graph would be shown)
- removed redundant print statements

21/11/24 @ 17:19
-------------------
- Updated welcome and help screen to accomodate for 4 new time commands
- Fixed a declaration issue with screen_graph()
- Added start and end date in command_time()
- Added dynamic Date/Place/substance printing to screen_graph()
- Removed 6 unused function from data_display.c:
  - hour_display()
  - day_display()
  - month_display()
  - unix_to_hour()
  - unix_to_date()
  - average()
- Implemented dynamic y-axis size
- Implemented dynamic x-axis size (slightly broken :D)
- Implemented dynamic threshold values for graph
- Removed unneded importan "time.h" from data_display.c
- Seperated all screen_graph_variables into seperate helper function
- Moved string_to_unixtime() to library custom_time.c
- Updated Makefile to include custom_time.c
- Replaced special UNICODE characters in draw_graph() with standard ASCII characters
- Added guided tutorial / example to screen_help to enhance user experience

16/12/24 @ 09:50
-------------------
- Added dynamic scalling of graph
- Added notice to inform user of graphing inprecisions introduced by dynamic scalling
- Added missing units and tittles on graph
- Corrected several mistakes resulting in "PM2.5" and "PM10" occasionally being showed as "P2.5" and "P10"
- Removed "span" command
- Updated home and help to reflect the remvoed span, and use "s"(vim) instead:
