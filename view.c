#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "extlib/json.h"
#include "view.h"

static WINDOW *task_view;

int _refresh(void *win) {
    box(win, 0 , 0);
    //wborder(task_view, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
}

int v_init() {
    initscr();
    cbreak(); // Change to raw() laters. Raw controlls all user input
    noecho();
    keypad(stdscr, TRUE); // Allow capturing of Fn keys and arrow keys

    //use_default_colors();
    start_color();
    init_color(COLOR_WHITE, 225, 255, 255);
    init_color(COLOR_BLUE, 225, 242, 254);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);

    refresh();

    task_view = newwin(LINES, COLS, 0, 0);
    mvwprintw(task_view, 1, 1, "Loading ...\n");
    _refresh(task_view);

    return 1;
}

int v_display_inbox(JsonNode *listOfTasks) {
    //printw("Debug: Reached v_display_inbox\n");
    JsonNode *task;
    int counter = 1;
    wattron(task_view, COLOR_PAIR(1) | A_BOLD);
    json_foreach(task, listOfTasks) {
        mvwprintw(
            task_view, counter, 1,
            "%d: %s\n",
            counter, json_find_member(task, "title")->string_
        );
        counter++;
    }
    wattroff(task_view, COLOR_PAIR(1) | A_BOLD);
    //chgat(10, A_REVERSE, 1, NULL);
    _refresh(task_view);
}

int v_end() {
    getch();
    endwin();
    return 1;
}
