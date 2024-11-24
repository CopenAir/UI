#include "custom_time.h"
#include <stdio.h>
#include <string.h>

// checks if a unixtime value is at midday. May be one hour behind (most likely cus of day light savings) but as its just for  the day it doesnt really matter
int is_midday(time_t unixtime) {
    struct tm *tm = localtime(&unixtime);

    if (tm->tm_hour == 12) {
        return 1;
    }

    return 0;
}

// takes a string in the format "YYYY-MM-DD HH" and converts it to unixtime.
// For some reason strptime isnt avaliable on Windows so we have to do our own thing
time_t string_to_unixtime(char *string) {
    // tm is a struct defined in time.h used to represent calendar time
    struct tm tm;
    int year, month, day, hour;

    // reads the string input and stores the values in the corresponding variables
    if (sscanf(string, "%d-%d-%d %d", &year, &month, &day, &hour) != 4) {
        printf("Invalid Time format: %s\n", string);
        return -1;
    }

    memset(&tm, 0, sizeof(struct tm));
    tm.tm_year = year - 1900; // years since 1900 cus thats how tm works
    tm.tm_mon = month - 1; // months since january (index starts at 0, so we have to subtract 1)
    tm.tm_mday = day; // mday is day of the month
    tm.tm_hour = hour;
    tm.tm_isdst = -1; // isdst is the daylight saving flag. -1 tells the system to determine it automatically

    time_t unixtime = mktime(&tm);
    if (unixtime == -1) {
        printf("Some error happened when converting string to unixtime: %s\n\n", string);
        return -1;
    }

    if (unixtime < 1697313600 || unixtime > 1728932400) {
        printf("Selected time outside of accepted range: %s\n\n", string);
        return -1;
    }

    return unixtime;
}