/**
 * Connects the api calls, model, and view.
 *
 * The controller also stores the model as static variables in this file,
 * because the model is relatively simple.
 *
 * After initialization, the view will be waiting for character inputs from the
 * user, and call the respective controller functions. We do this because event
 * driven programming is easier to read.
 */

#include <stdio.h>
#include "extlib/json.h"
#include "api_handler.h"
#include "controller.h"
#include "view.h"

/* Private function declarations */
static JsonNode *listOfTasks;

/**
 * The initial function called when program starts.
 *
 * returns: 1 if initialization successful, 0 if not
 */
int c_init() {
    // Todo: debug printf("Debug: Reached controller initialization.\n");
    if(!v_init()) {
        return 0;
    }
    listOfTasks = a_get_inbox_tasks();
    v_display_inbox(listOfTasks);

    // Todo: Take the JsonNode and throw it into the model

    v_end();
    return 1;
}
