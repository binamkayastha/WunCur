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

/* Private function declarations */
static char* _make_wlist_call(char *arg);

/** Returns a json node struct containing all tasks from the inbox */
JsonNode* a_get_inbox_tasks() {
    char *jsonString = _make_wlist_call("inbox:tasks");
    return json_decode(jsonString);
}

/**
 * Uses wlist to make a call given the arguments.
 *
 * Relies on the fact that the wlist binary is in ./extlib/wlist/bin/wlist
 *
 * @param arg The values passed into wlist.
 * @return A response in json string format from wlist.
 */
static char* _make_wlist_call(char *arg) {
    // Todo: debug printf("Debug: Reached _make_wlist_call.\n");
    FILE *fp;
    int status;
    char path[2048];

    // Allocate enough memory for base command + arg + null byte
    char* command = (char *) malloc(26 + strlen(arg));
    strcpy(command, "./extlib/wlist/bin/wlist ");
    strncat(command, arg, strlen(arg));

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

    while (getline(&line_buff, &nbytes, fp) > 0){
        size_t new_length = strlen(response_buff) + strlen(line_buff);
        response_buff = (char *) realloc(response_buff, new_length);
        strcat(response_buff, line_buff);
    }
    free(line_buff);

    pclose(fp);
    return response_buff;
}
