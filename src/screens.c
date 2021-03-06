/*
 * Mousing ncurses box sourcefile
 *
 * @filename: screens.c
 *
 * @version: 0.0.4
 *
 * @date: 2013-11-07
 *
 * @description: Mousings ncurses box file
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

#include "screens.h"
#include "functions.h"

/**
 * Create ncurses window.
 *
 * @height      int height.
 * @width       int width.
 * @startx      int start x pos.
 * @starty      int start y pos.
 *
 * Returns WINDOW.
 */
WINDOW *create_newwin(int box_dim[][2], int starty, int startx, int screen)
{
    WINDOW *local_win;

    local_win = newwin(box_dim[screen][1],
                       box_dim[screen][0],
                       starty,
                       startx);
    box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}

/**
 * Print mouse data.
 *
 * @staryx      int start x pos for text.
 * @cords[]     int [x,y] cords for text positions.
 * @pos[]       int [x,y] pos for mouse position.
 * @clicks[]    int [0,1,2] array for mouse clicks.
 * @mMov        int mouse movement.
 *
 * Returns nothing.
 */
void print_mouse_data(int cords[], int pos[], unsigned int clicks[], unsigned int mMov)
{
    int offset = 18;

    /* box title */
    mvprintw(cords[1], cords[0] + 2, " Mousing ");

    /* shift to magenta colors */
    attron(COLOR_PAIR(3));
    mvprintw(cords[1] + 2, cords[0] + 2, "Position:");
    mvprintw(cords[1] + 3, cords[0] + 2, "Movement:");
    mvprintw(cords[1] + 4, cords[0] + 2, "Left click:");
    mvprintw(cords[1] + 5, cords[0] + 2, "Middle click:");
    mvprintw(cords[1] + 6, cords[0] + 2, "Right click:");
    /* shift to cyan colors */
    attron(COLOR_PAIR(2));
    mvprintw(cords[1] + 2, cords[0] + offset, "(%04d,%04d)", pos[0], pos[1]);
    mvprintw(cords[1] + 3, cords[0] + offset, "%s ", commaprint(mMov));
    mvprintw(cords[1] + 4, cords[0] + offset, "%s ", commaprint(clicks[0]));
    mvprintw(cords[1] + 5, cords[0] + offset, "%s ", commaprint(clicks[1]));
    mvprintw(cords[1] + 6, cords[0] + offset, "%s ", commaprint(clicks[2]));
    /* turn off colors */
    attroff(COLOR_PAIR(2));
}

/**
 * Print stats data
 *
 * @cords       int array box coordinates.
 * @stats_data  int array stats data.
 * @days        int days, number of days stats is generated for.
 *
 * Returns nothing.
 */
void print_mouse_stats(int cords[], int stats_data[][4], int days)
{
    int column[4] = {2, 15, 22, 30};

    /* box title */
    mvprintw(cords[1], cords[0] + 2, " Stats - Last %d days ", days);

    mvprintw(cords[1] + 2, cords[0] + column[0], "Movement");
    mvprintw(cords[1] + 2, cords[0] + column[1], "Left");
    mvprintw(cords[1] + 2, cords[0] + column[2], "Center");
    mvprintw(cords[1] + 2, cords[0] + column[3], "Right");


    for (int i = 1; i <= days; i++) {
        mvprintw(cords[1] + (3+i), cords[0] + column[0], "%s", commaprint(stats_data[i][0]));
        mvprintw(cords[1] + (3+i), cords[0] + column[1], "%s", commaprint(stats_data[i][1]));
        mvprintw(cords[1] + (3+i), cords[0] + column[2], "%s", commaprint(stats_data[i][2]));
        mvprintw(cords[1] + (3+i), cords[0] + column[3], "%s", commaprint(stats_data[i][3]));
    }
}

/**
 * Print Help page
 *
 * @cords       int array box coordinates.
 *
 * Returns nothing.
 */
void print_mousing_help(int cords[])
{
    int offset = 10;

    /* box title */
    mvprintw(cords[1], cords[0] + 2, " Help ");

    mvprintw(cords[1] + 2, cords[0] + 2, "Key");
    mvprintw(cords[1] + 2, cords[0] + offset, "Description");

    mvprintw(cords[1] + 4, cords[0] + 2, "h");
    mvprintw(cords[1] + 5, cords[0] + 2, "m");
    mvprintw(cords[1] + 6, cords[0] + 2, "s");
    mvprintw(cords[1] + 8, cords[0] + 2, "a");
    mvprintw(cords[1] + 9, cords[0] + 2, "q");

    mvprintw(cords[1] + 4, cords[0] + offset, "Help page (this)");
    mvprintw(cords[1] + 5, cords[0] + offset, "Mousing");
    mvprintw(cords[1] + 6, cords[0] + offset, "Stats page");
    mvprintw(cords[1] + 8, cords[0] + offset, "About page");
    mvprintw(cords[1] + 9, cords[0] + offset, "Quit");
}

/**
 * Print About page
 *
 * @cords       int array box coordinates.
 * @version     float version, mousing version.
 *
 * Returns nothing.
 */
void print_mousing_about(int cords[], float version)
{
    /* box title */
    mvprintw(cords[1], cords[0] + 2, " About ");

    mvprintw(cords[1] + 2, cords[0] + 2, "Mousing is a microscopic");
    mvprintw(cords[1] + 3, cords[0] + 2, "Linux program for tracking");
    mvprintw(cords[1] + 4, cords[0] + 2, "mouse movement, and output");
    mvprintw(cords[1] + 5, cords[0] + 2, "and log to database.");

    mvprintw(cords[1] + 7, cords[0] + 2, "The main reason for this");
    mvprintw(cords[1] + 8, cords[0] + 2, "program was to learn to");
    mvprintw(cords[1] + 9, cords[0] + 2, "reduce heavy mouse use.");
    mvprintw(cords[1] + 10, cords[0] + 2, "The best way to do this is");
    mvprintw(cords[1] + 11, cords[0] + 2, "to get some numbers and");
    mvprintw(cords[1] + 12, cords[0] + 2, "compare them on a daily");
    mvprintw(cords[1] + 13, cords[0] + 2, "basis.");

    mvprintw(cords[1] + 15, cords[0] + 2, "Version: %.2f", version);

}


/**
 * Destroy window.
 *
 * @local_win       pointer to WINDOW.
 *
 * Returns nothing.
 */
void destroy_win(WINDOW *local_win) 
{
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
    endwin();
    refresh();
}

/**
 * Update screen and box cords
 *
 * @cords       int array box coordinates.
 * @old_coords  int array old box coordinates.
 * @box_dim     int array box dimensions.
 * @screen      int representing screen.
 * 
 * Returns nothing.
 */
void cord_update(int cords[], int old_cords[], int box_dim[][2], int screen)
{
    cords[0] = (COLS - box_dim[screen][0]) / 2;
    cords[1] = (LINES - box_dim[screen][1]) / 2; 
    old_cords[1] = LINES;
    old_cords[0] = COLS;
}

/**
 * Setup function for ncurses.
 *
 * Returns nothing.
 */
void screen_setup()
{
    initscr();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
}

/**
 * ncurses color setup.
 *
 * Returns nothing.
 */
void screen_colors()
{
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support colors\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
}
