/**
 * Entry point of the program.
 *
 * WunCur was initialized by Binam Kayastha. It was made due to the frustration
 * he faced in not having good terminal based to-do lists as a linux user.
 * (He uses vim, so org-mode was out of the question).
 */

#include <ncurses.h>
#include <stdio.h>
#include "controller.h"

/*
 * Initializes controller.
 *
 * This program follows MVC pattern. This main function allows contributors to
 * know where to start.
 *
 * @return 0 for success, and 1 for failure
 */
int main() {
    if(c_init()) {
        return 0; // Success
    }
    return 1;
}
