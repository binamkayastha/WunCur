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
#include <stdlib.h>
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
        exit(1);

    if ((listOfTasks = a_get_inbox_tasks()) == NULL)
        l_log(ERROR, "Failed to get inbox tasks.");
    else
        v_display_inbox(listOfTasks);

    if ((listOfProjects = a_get_projects()) == NULL)
        l_log(ERROR, "Failed to get projects.");
    else
        v_display_projects(listOfProjects);

    // Todo: Take the JsonNode and throw it into the model

    // Listen for character inputs from view, because only view should have
    //  access to user input via ncurses.
    v_listen();

    l_log(ERROR, "Exited view listen loop");
    exit(1);
}

/** Logs and exits out of the view. */
void c_event_exit()
{
    l_log(DEBUG, "Reached c_event_exit().");
    v_exit();
    exit(0);
}
