/*
 * Mousing main sourcefile.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.2
 *
 * @date: 2013-11-07
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
#define VERSION 0.02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "x11mouse.h"
#include "ncbox.h"
#include "sqldb.h"
#include "mhash.h"
#include "functions.h"

struct {
    int pos[2];                     /* pos (x,y) */
    int old_pos[2];                 /* old pos (x,y) */
    unsigned int click[3];          /* clicks (left,middle,right) */
    unsigned int old_click[3];      /* clicks (left,middle,right) */
    unsigned int state[2];          /* state (current, previous) */
    unsigned int mov[2];            /* movement (current, previous) */ 
} mouse = {
    /* set zero values */
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0, 0},
    {0, 0},
    {0, 0}
};

int main(int argc, char *argv[]) 
{
    int retval;
    int oldlines, oldcols, sX, sY, ch;
    int box_height = 10, box_width = 35; 
    int sleep_time = pow(2,15);

    /* time spesifict vars */
    char timestr[30];
    //char zero_time[30] = {"0000"};
    struct tm *local;
    time_t t;

    WINDOW *my_win;
    sqlite3_stmt *stmt;
    sqlite3 *handle;

    x11read_init();

    /* open database and create/check for tables */
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

    /* read previous data from database, if exists */
    db_get_mov(&retval,
               &handle,
               &stmt,
               &mouse.mov[0],
               &mouse.click[0],
               &mouse.click[2]
               );

    /**
     * set the old counters to be the same as
     * the current, before starting the never
     * ending loop that follows
     *
     * This is the first out of two times this
     * mass update sequence happens. It might
     * be a good idea to branch this sequence
     * of to a place never to be seen again...
     */
    mouse.mov[1] = mouse.mov[0];
    mouse.old_pos[0] = mouse.pos[0];
    mouse.old_pos[1] = mouse.pos[1];
    mouse.old_click[0] = mouse.click[0];
    mouse.old_click[1] = mouse.click[1];
    mouse.old_click[2] = mouse.click[2];

    do { 
        /* Read from mouse */
        x11read_mouse(&mouse.pos[0],
                      &mouse.pos[1],
                      &mouse.mov[0],
                      &mouse.state[0]
                      );

        /**
         * Redraw window if resized.
         * This should be split into another file, and
         * only run/checked if window changes.
         */
        if ((oldlines != LINES) || (oldcols != COLS)) {
            sY = (LINES - box_height) / 2; 
            sX = (COLS - box_width) / 2;
            oldlines = LINES;
            oldcols = COLS;
            destroy_win(my_win);
            my_win = create_newwin(box_height, box_width, sY, sX);
        }

        /* right click */
        if ((mouse.state[0] == 1024) && (mouse.state[1] == 0)) {
            mouse.click[2]++;
            mouse.state[1] = 1;
        }
        /* left click */
        if ((mouse.state[0] == 256) && (mouse.state[1] == 0)) {
            mouse.click[0]++;
            mouse.state[1] = 1;
        }
        /* middle click */
        if ((mouse.state[0] == 512) && (mouse.state[1] == 0)) {
            mouse.click[1]++;
            mouse.state[1] = 1;
        }
        if (mouse.state[0] == 0) {
            mouse.state[1] = 0;
        }

        /* Print data to window */
        print_data(sY,
                   sX,
                   mouse.pos[0],
                   mouse.pos[1],
                   mouse.click[0],
                   mouse.click[2],
                   mouse.mov[0]
                   );

        /* refresh the ncurses window */
        refresh();
      
        /**
         * Update if mouse moves.
         * 
         * This check is a bit nasty. Might consider improving it.
         */
        if (((mouse.old_pos[0] != mouse.pos[0])
            && (mouse.old_pos[1] != mouse.pos[1]))
            || (mouse.old_click[0] != mouse.click[0])
            || (mouse.old_click[1] != mouse.click[1])
            || (mouse.old_click[2] != mouse.click[2])
            )
        {
            /* Insert data into database  */
            db_insert(&retval,
                      &handle,
                      mouse.pos[0],
                      mouse.pos[1],
                      mouse.mov[0],
                      mouse.click[0],
                      mouse.click[2]
                      );
        }
        
        /* update mouse.pos and mouse.click with old */
        mouse.mov[1] = mouse.mov[0];
        mouse.old_pos[0] = mouse.pos[0];
        mouse.old_pos[1] = mouse.pos[1];
        mouse.old_click[0] = mouse.click[0];
        mouse.old_click[1] = mouse.click[1];
        mouse.old_click[2] = mouse.click[2];

        /** 
         * Check time.
         * If the time is 00:00, reset the counters
         */
        t = time(NULL);
        local = localtime(&t);
        strftime(timestr, sizeof(timestr), "%H%M", local);
        /**
         * Here be some fancy time checking...
         * Does not work. Need fixing!
         *
        if (timestr == zero_time) {
            mouse.mov[0] = 0;
            mouse.click[0] = 0;
            mouse.click[1] = 0;
            mouse.click[2] = 0;
        }
        */

        /* Sleep for a while, to prevent CPU load */
        usleep(sleep_time);

    } while ((ch = getch()) != 'q');

    /* Final save to the database */
    db_insert(&retval,
              &handle,
              mouse.pos[0],
              mouse.pos[1],
              mouse.mov[0],
              mouse.click[0],
              mouse.click[2]
              );

    /* End routine */
    endwin();
    free(root_windows);
    sqlite3_close(handle);
    return 0;
}
