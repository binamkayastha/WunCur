#include <stdio.h>
#include <ncurses.h>

#include "controller.h"

int main() {
    if(c_init()) {
        return 0; // Success
    }
    return 1;
}
