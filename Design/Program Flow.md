# Program Flow
These are just suggestion, feel free to come with different ideas or changes.

## Global Commands

| Command             | Description                                                                                                                                                                                                                                   |
| ------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `r`, `reset`        | Resets the program to its original state                                                                                                                                                                                                      |
| `q`, `quit`, `exit` | Exits the program                                                                                                                                                                                                                             |
| `h`, `help`         | Displays a list of commands the user can use. Should only be the ones the user can use at this specific screen. We can have a `-a`, `--all` flag for showing a comprehensive list of commands categorized on where they can be used.          |
| `l`, `location`     | Navigates to the screen where the user can select a location                                                                                                                                                                                  |
| `g`, `graph`        | Navigates to the graph page. We need to consider whether to do this, or just have the graph show up when the user selects it in the location menu. If we do it this way. If we do it this way we need to save the graph the user last viewed. |

## Start message
```txt
*Fancy Welcome Message*

Enter h for help
Enter q to quit

Select your action:
 [1] View data for specific location
 [2] Whatever else we think abt
----------------------------------------------
Enter Command: 
```

Alternatively we can just only use the commands for navigating, and then the user just have to figure those out, and then not have the "select your action" thing.

## Choosing Location
```txt
(Selecting Road)
Page 1 of 5
----------------------------------------------

 [1] Vej                           05-09-2024
 [2] Vej                           05-09-2024
 [3] Vej                           05-09-2024
 [4] Vej                           05-09-2024
 [5] Vej                           05-09-2024
 [6] Vej                           06-02-2024
 [7] Vej                           12-01-2024
 [8] Vej                           06-01-2024
 [9] Vej                           06-01-2024
 [0] Vej                           06-01-2024
 
----------------------------------------------
Enter Command: 
```

### Commands:

| Commands        | Description                                                                        |
| --------------- | ---------------------------------------------------------------------------------- |
| `<number>`      | Selects that location and goes to the data page showing the data for that location |
| `page <number>` | Navigates to the page the user entered                                             |
| `prev`          | Navigates to the previous page                                                     |
| `next`          | Navigates to the next page                                                         |


## Data for location

**General Data Version 1**

```txt
(Showing General Data For Location)
Vejvej 12         05-09-2024           14:00
---------------------------------------------

 [1] Pm2.5:  xx  Normal Level
 [2] Pm10:   xx  Normal Level
 [3] No2:    xx  High Levels
 [4] CO:     xx  Normal Levels
 [5] CH4:    xx  Normal Levels
 [6] Temp:   xx  Normal Levels
 
----------------------------------------------
Enter Command: 
```

**General Data Version 2**

```txt
(Showing General Data For Location)
Vejvej            05-09-2024            14:00
---------------------------------------------
[1] Pm2.5          [2] Pm10          [3] No2
    xxx                xxx               xxx

[4] CO             [5] CH4           [6] Temp
    xxx                xxx               xxx
----------------------------------------------
Enter Command: 
```

### Commands:

| Commands      | Description                                                                                                                                               |
| ------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `<number>`    | Displays the graph for that thing                                                                                                                         |
| `date <date>` | Changes the graph to show that specific date. The format should be `day-month-year`. Theres probably a more elegant way to do this (like a submenu maybe) |
| `time <hour>` | Changes the graph to show that specific time.                                                                                                             |
| `next`        | Goes to the next day. Could have a `-t`, `--time` flag for going to next timestamp instead                                                                |
| `prev`        | Goes to previous day. Could have the same flag as next.                                                                                                   |
|               |                                                                                                                                                           |


## Graph

**TODO: Insert Design here**

### Commands

| Command       | Description                                                                                                                                               |
| ------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `back`        | Goes back to general information                                                                                                                          |
| `date <date>` | Changes the graph to show that specific date. The format should be `day-month-year`. Theres probably a more elegant way to do this (like a submenu maybe) |
| `next`        | Goes to the next day                                                                                                                                      |
| `prev`        | Goes to the previous day                                                                                                                                  |
