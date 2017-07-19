/**
 * Connects the api calls, model, and view.
 *
 * The controller also stores the model as static variables in this file,
 * because the model is relatively simple. Models are written with camelCase.
 *
 * After initialization, the view will be waiting for character inputs from the
 * user, and call the respective controller functions. We do this because event
 * driven programming is easier to read.
 */

#include <stdio.h>
#include "extlib/json.h"
#include "api_handler.h"
#include "controller.h"
#include "logger.h"
#include "view.h"

/* Private function declarations */
static JsonNode *listOfTasks;
static JsonNode *listOfProjects;

/**
 * The initial function called when program starts.
 *
 * @return
 *      1 if initialization successful \n
 *      0 if initialization failed
 */
int c_init()
{
    l_log(DEBUG, "Reached controller initialization.");
    if (!v_init())
        return 0;

    if ((listOfTasks = a_get_inbox_tasks()) == NULL)
        l_log(ERROR, "Failed to get inbox tasks.");
    else
        v_display_inbox(listOfTasks);

    if ((listOfProjects = a_get_projects()) == NULL)
        l_log(ERROR, "Failed to get projects.");
    else
        v_display_projects(listOfProjects);

    // Todo: Take the JsonNode and throw it into the model

    v_exit();
    return 1;
}
