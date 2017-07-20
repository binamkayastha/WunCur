int v_init();
#include "extlib/json.h"
void v_display_inbox(JsonNode *listOfTasks);
void v_display_log(char *log_level, char *msg);
void v_display_projects(JsonNode *listOfProjects);
void v_listen();
void v_exit();
