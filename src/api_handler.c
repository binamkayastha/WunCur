#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extlib/json.h"

static char *_make_wlist_call(char *arg) {
    //printf("Debug: Reached _make_wlist_call.\n");
    FILE *fp;
    int status;
    char path[2048];

    // 26 is the length of the base command + null byte
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
    char *string_buff = (char *) malloc(1);
    *string_buff = '\0';

    while (getline(&line_buff, &nbytes, fp) > 0){
        size_t new_length = strlen(string_buff) + strlen(line_buff);
        string_buff = (char *) realloc(string_buff, new_length);
        strcat(string_buff, line_buff);
    }
    free(line_buff);

    pclose(fp);
    return string_buff;
}

JsonNode *a_get_inbox_tasks() {
    char *jsonString = _make_wlist_call("inbox:tasks");
    return json_decode(jsonString);
}

