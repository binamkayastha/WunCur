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
 * @return
 *      1 if initialization successful \n
 *      0 if initialization failed
 */
int c_init()
{
    // Todo: debug printf("Debug: Reached controller initialization.\n");
    if (!v_init())
        return 0;

    if ((listOfTasks = a_get_inbox_tasks()) == NULL)
        v_display_error("Failed to get inbox tasks\n");
    else
        v_display_inbox(listOfTasks);
    // Todo: Take the JsonNode and throw it into the model

    v_exit();
    return 1;
}
