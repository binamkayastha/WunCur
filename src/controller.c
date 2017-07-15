#include <stdio.h>
#include "extlib/json.h"

#include "controller.h"
#include "api_handler.h"
#include "view.h"

static JsonNode *listOfTasks;

/**
 * The initial function called when program starts.
 *
 * returns: 1 if initialization successful, 0 if not
 */
int c_init() {
    //printf("Debug: Reached controller initialization.\n");
    if(!v_init()) {
        return 0;
    }
    listOfTasks = a_get_inbox_tasks();
    v_display_inbox(listOfTasks);

    // Take the JsonNode and throw it into the model

    v_end();
    return 1;
}
