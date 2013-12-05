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
#define DB_WRITE_INTVAL 8
/* reset time */
#define RESET_HOUR 0
#define RESET_MIN 0
#define RESET_SEC 0
/* ncurses box */
#define BOX_HEIGHT 9
#define BOX_WIDTH 32

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
} m = {
    /* set zero values */
    {0, 0},
    {0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0},
    {0, 0}
};

int main(int argc, char *argv[]) 
{
    int retval;
    int cords[2]; /* (x,y) cords for the ncurses box */
    int old_cords[2];
    int box_height = BOX_HEIGHT, box_width = BOX_WIDTH; 
    int sleep_time = pow(2,14);
    int db_write_intval = 0;

    char ch; /* input char [current, old] */

    /* time specific vars */
    char timestr[30];
    char zero_time[30];
    struct tm *local;
    time_t t;
    sprintf(zero_time, "%02d:%02d:%02d",
            RESET_HOUR, RESET_MIN, RESET_SEC
            );

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
    x11read_mouse(m.pos, m.click, m.state, &m.mov[0]);

    /* read previous data from database, if exists */
    db_get_mov(&retval, &handle, &stmt, &m.mov[0], m.click);

    /* do the following until user presses the Q key */
    do { 

        ch = getch();

        /** 
         * Get time
         */
        t = time(NULL);
        local = localtime(&t);
        strftime(timestr, sizeof(timestr), "%T", local);

        /* Read from mouse */
        x11read_mouse(m.pos, m.click, m.state, &m.mov[0]);

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
            /* redraw window and clean up garbage */
            destroy_win(my_win);
            my_win = create_newwin(box_height, box_width, cords[1], cords[0]);
        }

        /**
         * Here be some fancy time checking...
         * If the time is zero_time, reset all counters, (day change etc.)
         */
        if (!strcmp(timestr, zero_time)) {
            m.mov[0] = 0;
            m.click[0] = 0;
            m.click[1] = 0;
            m.click[2] = 0;
            /* redraw window and clean up garbage */
            destroy_win(my_win);
            my_win = create_newwin(box_height, box_width, cords[1], cords[0]);
            /* take a small break */
            usleep(pow(2,20));
        }
      
        /**
         * Update if mouse moves.
         * First check if the write intval correct (this to prevent mass insert
         * to the database), and then check if the mouse has moved since last
         * db_write_intval.
         */
        if (db_write_intval == 1) {
            if (memcmp(m.old_pos, m.pos, sizeof(m.pos))
                || (memcmp(m.old_click, m.click, sizeof(m.click)))
                )
            {
                /* Insert data into database  */
                db_insert(&retval, &handle, m.mov[0], m.pos, m.click);
                /* update m.pos and m.click with old */
                m.mov[1] = m.mov[0];
                memcpy(m.old_pos, m.pos, sizeof(m.pos));
                memcpy(m.old_click, m.click, sizeof(m.click));
            }
        }
        
        /* Print data to window */
        print_mouse_data(cords, m.pos, m.click, m.mov[0]);

        /* refresh the ncurses window */
        refresh();

        /* Increment the db_write_intval var */
        exp_inc(&db_write_intval, DB_WRITE_INTVAL);

        /* Sleep for a while, to prevent high CPU load */
        usleep(sleep_time);
        
    } while (ch != 'q');

    /* Do one final save to the database */
    db_insert(&retval, &handle, m.mov[0], m.pos, m.click);

    /* Clean up and end program, end routine */
    endwin();
    free(root_windows);
    sqlite3_close(handle);
    return 0;
}
