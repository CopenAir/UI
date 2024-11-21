#ifndef UI_CUSTOM_TIME_H
#define UI_CUSTOM_TIME_H

#include <time.h>

struct timespan {
    time_t start_date;
    time_t end_date;
};

time_t string_to_unixtime(char *string);
int is_midday(time_t unixtime);

#endif //UI_CUSTOM_TIME_H
