/**
 * Handles the ncurses portion of the program.
 *
 * The view has two main jobs:
 * 1) Updates the view based on what the controller wants.
 * 2) Handles user input, and calls event functions in the controller.
 *
 * LINES and COLS are ncurses macros of how high and wide the window is.
 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "extlib/json.h"
#include "view.h"

/* Private function declarations */
static void _init_proj_view(int width);
static void _init_task_view(int left_pad);
static void _print_loading(WINDOW *win);

/* Private variables */
static WINDOW *proj_view;
static WINDOW *task_view;

/**
 * Draws a box and refreshes the window.
 *
 * A box needs to be redrawn
 *
 * @param win Window to refresh
 */
static int _refresh(WINDOW *win) {
    // Todo: potentially choose thicker borders
    // wborder(task_view, '|', '|', '-', '-', '+', '+', '+', '+');
    box(win, 0 , 0);
    wrefresh(win);
}

/**
 * Initializes the view with inbox selected.
 *
 * Calls initialization functions to begin ncurses, and setup the windows.
 *
 * @return 1 on success
 */
int v_init() {
    initscr();
    cbreak(); // Change to raw() laters. Raw controlls all user input
    noecho();
    keypad(stdscr, TRUE); // Allow capturing of Fn keys and arrow keys

    use_default_colors();
    start_color();
    init_color(COLOR_WHITE, 225, 255, 255);
    init_color(COLOR_BLUE, 225, 242, 254);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);

    refresh();

    /* proj_view is on the left side of task_view */
    int proj_view_size = 20;
    _init_proj_view(proj_view_size);
    _init_task_view(proj_view_size);

    return 1;
}

/* Initializes a window on the left to hold project lists. */
static void _init_proj_view(int width) {
    proj_view = newwin(LINES, width, 0, 0);
    _print_loading(proj_view);
}

/* Initializes the center window for the list of tasks. */
static void _init_task_view(int left_pad) {
    task_view = newwin(LINES, COLS-left_pad, 0, left_pad);
    _print_loading(task_view);
}

/* Prints a loading string on the given window. */
static void _print_loading(WINDOW *win) {
    mvwprintw(win, 1, 1, "Loading ...\n");
    _refresh(win);
}

/**
 * Prints all the tasks in bold from the inbox list into the task_view.
 *
 * @param listOfTask A json array to be printed
 */
int v_display_inbox(JsonNode *listOfTasks) {
    // Todo: debug printw("Debug: Reached v_display_inbox\n");
    JsonNode *task;
    int counter = 1;
    wattron(task_view, A_BOLD);
    json_foreach(task, listOfTasks) {
        mvwprintw(
            task_view, counter, 1,
            "%d: %s\n", counter, json_find_member(task, "title")->string_
        );
        counter++;
    }
    wattroff(task_view, A_BOLD);
    _refresh(task_view);
}

/* Close out of ncurses, and return 1 for success */
int v_end() {
    getch();
    endwin();
    return 1;
}