/**
 * Handles the logs by sending the printw statements to a pop up window
 *
 * This is terrible code, but relies on v_init() in view.c to be called first
 * to work.
 * Todo: Refactor this into the view.c
 */

#include <ncurses.h>
#include "logger.h"
#include "view.h"

static WINDOW *log_win;

/** Prints the log level and the message */
void l_log(enum LogLevel log_level, char *msg)
{
    char *str_log_level;
    switch(log_level) /* I'm sorry */
    {
        case DEBUG:
            str_log_level = "DEBUG";
            break;
        case INFO:
            str_log_level = "INFO";
            break;
        case WARN:
            str_log_level = "WARN";
            break;
        case ERROR:
            str_log_level = "ERROR";
            break;
        default:
            str_log_level = "UNKOWN";
    }

    v_display_log(str_log_level, msg);
}
