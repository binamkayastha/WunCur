#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "extlib/json.h"
#include "view.h"

void _init_proj_view(int width);
void _init_task_view(int left_pad);
void _print_loading(WINDOW *win);

static WINDOW *proj_view;
static WINDOW *task_view;

int _refresh(WINDOW *win) {
    box(win, 0 , 0);
    //wborder(task_view, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
}

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

void _init_proj_view(int width) {
    proj_view = newwin(LINES, width, 0, 0);
    _print_loading(proj_view);
}

void _init_task_view(int left_pad) {
    task_view = newwin(LINES, COLS-left_pad, 0, left_pad);
    _print_loading(task_view);
}

void _print_loading(WINDOW *win) {
    mvwprintw(win, 1, 1, "Loading ...\n");
    _refresh(win);
}

int v_display_inbox(JsonNode *listOfTasks) {
    //printw("Debug: Reached v_display_inbox\n");
    JsonNode *task;
    int counter = 1;
    wattron(task_view, A_BOLD);
    json_foreach(task, listOfTasks) {
        mvwprintw(
            task_view, counter, 1,
            "%d: %s\n",
            counter, json_find_member(task, "title")->string_
        );
        counter++;
    }
    wattroff(task_view, A_BOLD);
    //chgat(10, A_REVERSE, 1, NULL);
    _refresh(task_view);
}

int v_end() {
    getch();
    endwin();
    return 1;
}
