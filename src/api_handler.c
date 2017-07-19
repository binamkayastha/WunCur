/**
 * Handles the api calls to wunderlist.
 *
 * The api_handler uses a program called wlist to get Wunderlist data in a
 * quick and easy way. In the future, this should use curl to remove ruby
 * dependencies, feel free to discuss via github issues.
 *
 * The api_handler returns json objects from the external json program to
 * allow the controller to easily manipulate data.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extlib/json.h"
#include "logger.h"

/* Private function declarations */
static char* _make_wlist_call(char *arg);

/**
 * Returns a json node struct containing all tasks from the inbox
 *
 * @return
 *      JsonNode array of all the tasks in JsonNode objects\n
 *      NULL if API call failed
 */
JsonNode* a_get_inbox_tasks()
{
    char *jsonString;
    if ((jsonString = _make_wlist_call("inbox:tasks")) == NULL)
        return NULL;
    return json_decode(jsonString);
}

/**
 * Uses wlist to make a call given the arguments.
 *
 * Relies on the fact that the wlist binary is in ./extlib/wlist/bin/wlist
 *
 * @param arg The values passed into wlist.
 * @return
 *      Json string formatted response from wlist\n
 *      NULL if response failed
 */
static char* _make_wlist_call(char *arg)
{
    l_log(DEBUG, "Reached _make_wlist_call in api_handler.");
    char* wlist_bin = "./extlib/wlist/bin/wlist";
    char* reroute_stderr = "2>/dev/null";

    int command_len = strlen(wlist_bin)
                      + strlen(arg)
                      + strlen(reroute_stderr)
                      + 2 /* Two spaces */
                      + 1; /* null byte */
    char* command = (char *) malloc(command_len); // Todo: Support UTF-8/Unicode
    snprintf(command, command_len, "%s %s %s", wlist_bin, arg, reroute_stderr);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Err\n");
        return NULL;
    }
    free(command);

    char *line_buff = NULL;
    size_t nbytes = 0;
    char *response_buff = (char *) malloc(1);
    *response_buff = '\0';

    while (getline(&line_buff, &nbytes, fp) > 0) {
        size_t new_length = strlen(response_buff) + strlen(line_buff);
        response_buff = (char *) realloc(response_buff, new_length);
        strcat(response_buff, line_buff);
    }
    free(line_buff);
    pclose(fp);

    if (*response_buff == '\0')
        return NULL;

    return response_buff;
}
