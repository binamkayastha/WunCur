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
static JsonNode *_get_JsonNode_for(char *cmd);
static char *_make_wlist_call(char *arg);
static char *_construct_wlist_command(char *arg);

/** Returns a JsonNode with all tasks in inbox list, or NULL on fail. */
JsonNode *a_get_inbox_tasks()
{
    return _get_JsonNode_for("inbox:tasks");
}

/** Returns a JsonNode with all project lists, or NULL on fail. */
JsonNode *a_get_projects()
{
    return _get_JsonNode_for("lists");
}

/** Returns a JsonNode object from given wlist command */
static JsonNode *_get_JsonNode_for(char *cmd)
{
    char *jsonString;
    if ((jsonString = _make_wlist_call(cmd)) == NULL)
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
static char *_make_wlist_call(char *arg)
{
    // Todo: Refactor. Add log message for returning NULL
    l_log(DEBUG, "Reached _make_wlist_call in api_handler.");
    char *command = _construct_wlist_command(arg);
    if (command == NULL)
        return NULL;

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        l_log(ERROR, "Failed to open file");
        return NULL;
    }
    free(command);

    char *line_buff = NULL;
    size_t nbytes = 0;
    char *response_buff = (char *) malloc(1);
    *response_buff = '\0';
    size_t response_buff_len = 1;

    while (getline(&line_buff, &nbytes, fp) > 0) {
        response_buff_len = response_buff_len + strlen(line_buff);
        char *temp_buff = (char *) realloc(response_buff, response_buff_len);
        if (temp_buff == NULL)
            return NULL;
        response_buff = temp_buff;
        strncat(response_buff, line_buff, strlen(line_buff) + 1);
    }
    free(line_buff);
    pclose(fp);

    if (*response_buff == '\0')
        return NULL;

    return response_buff;
}

/** Returns an allocated char* for proper wlist command, or NULL on failure */
static char *_construct_wlist_command(char *arg)
{
    char *wlist_bin = "./extlib/wlist/bin/wlist";
    char *reroute_stderr = "2>/dev/null";

    int command_len = strlen(wlist_bin)
                      + strlen(arg)
                      + strlen(reroute_stderr)
                      + 2 /* Two spaces */
                      + 1; /* null byte */
    char *command = (char *) malloc(command_len); // Todo: Support UTF-8/Unicode
    snprintf(command, command_len, "%s %s %s", wlist_bin, arg, reroute_stderr);
    return command;
}
