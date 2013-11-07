/*
 * Mousing main sourcefile.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.10
 *
 * @date: 2013-02-24
 *
 * @description: Mousing main program file
 *
 * This file is part of Mousing.
 *
 * Mousing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mousing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mousing.    If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define _BSD_SOURCE
#define VERSION 0.0010

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "x11mouse.h"
#include "ncbox.h"
#include "sqldb.h"
#include "functions.h"

int main(int argc, char *argv[]) 
{
    WINDOW *my_win;

    int retval;
    int oldlines, oldcols, sX, sY, mX, mY, ch;
    int interval = 0;
    int box_height = 10, box_width = 35; 
    int hold_time = pow(2,15);
    unsigned int mR, mO;

    sqlite3_stmt *stmt;
    sqlite3 *handle;

    x11read_init();

    db_open_database(&retval, &handle);
    db_table_create(&retval, &handle);

    my_setup();
    my_colors();

    sY = (LINES - box_height) / 2; 
    sX = (COLS - box_width) / 2;
    oldlines = LINES;
    oldcols = COLS;

    printw("Press Q to exit. Version: %.2f", VERSION);
    refresh();
    my_win = create_newwin(box_height, box_width, sY, sX);

    db_get_mov(&retval, &handle, &stmt, &mO);

    do { 

        x11read_mouse(&interval, &mX, &mY, &mO, &mR);
        if ((oldlines != LINES) || (oldcols != COLS)) {
            sY = (LINES - box_height) / 2; 
            sX = (COLS - box_width) / 2;
            oldlines = LINES;
            oldcols = COLS;
            destroy_win(my_win);
            my_win = create_newwin(box_height, box_width, sY, sX);
        }
        print_data(sY, sX, mY, mX, mR, mO);
        refresh();

        if (interval == 1) {
            db_insert(&retval, &handle, mX, mY, mO);
        }

        exp_inc(&interval, 10);
        usleep(hold_time);

    } while ((ch = getch()) != 'q');

    db_insert(&retval, &handle, mX, mY, mO);
    endwin();
    free(root_windows);
    sqlite3_close(handle);
    return 0;
}
