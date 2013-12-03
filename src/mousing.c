/*
 * Mousing main source file.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.3
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
#define VERSION 0.03

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "x11mouse.h"
#include "ncbox.h"
#include "sqldb.h"
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
    /* (x,y) cords for the ncurses box */
    int cords[2];
    int old_cords[2];
    int ch; /* input char */
    int box_height = 9, box_width = 32; 
    int sleep_time = pow(2,16);

    /* time specific vars */
    char timestr[30];
    char zero_time[30] = {"00:00:00"};
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

    cords[0] = (COLS - box_width) / 2;
    cords[1] = (LINES - box_height) / 2; 
    old_cords[1] = LINES;
    old_cords[0] = COLS;

    printw("Press Q to exit. Version: %.2f", VERSION);
    refresh();
    my_win = create_newwin(box_height, box_width, cords[1], cords[0]);

    /**
     * Do one initial reading and populate the integers
     * variables before getting the database information.
     * This to prevent the awkward movement incrementation
     * on every startup.
     */
    x11read_mouse(&mouse.pos[0], &mouse.pos[1], &mouse.mov[0], &mouse.state[0]);

    /* read previous data from database, if exists */
    db_get_mov(&retval, &handle, &stmt, &mouse.mov[0], mouse.click);

    do { 

        /** 
         * Get time
         */
        t = time(NULL);
        local = localtime(&t);
        strftime(timestr, sizeof(timestr), "%T", local);

        /* Read from mouse */
        x11read_mouse(&mouse.pos[0], &mouse.pos[1], &mouse.mov[0], &mouse.state[0]);

        /**
         * Redraw window if resized.
         * This should be split into another file, and
         * only run/checked if window changes.
         */
        if ((old_cords[1] != LINES) || (old_cords[0] != COLS)) {
            cords[1] = (LINES - box_height) / 2; 
            cords[0] = (COLS - box_width) / 2;
            old_cords[1] = LINES;
            old_cords[0] = COLS;
            destroy_win(my_win);
            my_win = create_newwin(box_height, box_width, cords[1], cords[0]);
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

        /**
         * Here be some fancy time checking...
         * If the time is zero_time, reset all
         * counters, (day change etc.)
         */
        if (!strcmp(timestr, zero_time)) {
            mouse.mov[0] = 0;
            mouse.click[0] = 0;
            mouse.click[1] = 0;
            mouse.click[2] = 0;
            /* redraw window and clean up garbage */
            destroy_win(my_win);
            my_win = create_newwin(box_height, box_width, cords[1], cords[0]);
            /* take a small break */
            usleep(pow(2,20));
        }
      
        /**
         * Update if mouse moves.
         */
        if (memcmp(mouse.old_pos, mouse.pos, sizeof(mouse.pos))
            || (memcmp(mouse.old_click, mouse.click, sizeof(mouse.click)))
            )
        {
            /* Insert data into database  */
            db_insert(&retval, &handle, mouse.mov[0], mouse.pos, mouse.click);
        }
        
        /* Print data to window */
        print_data(cords, mouse.pos, mouse.click, mouse.mov[0]);
        /* refresh the ncurses window */
        refresh();
        /* update mouse.pos and mouse.click with old */
        mouse.mov[1] = mouse.mov[0];
        memcpy(mouse.old_pos, mouse.pos, sizeof(mouse.pos));
        memcpy(mouse.old_click, mouse.click, sizeof(mouse.click));
        /* Sleep for a while, to prevent high CPU load */
        usleep(sleep_time);

    } while ((ch = getch()) != 'q');

    /* Final save to the database */
    db_insert(&retval, &handle, mouse.mov[0], mouse.pos, mouse.click);

    /* End routine */
    endwin();
    free(root_windows);
    sqlite3_close(handle);
    return 0;
}
