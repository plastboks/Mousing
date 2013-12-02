/*
 * Mousing ncurses box sourcefile
 *
 * @filename: ncbox.c
 *
 * @version: 0.0.2
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

#include "ncbox.h"
#include "functions.h"

/**
 * Create ncurses window.
 *
 * @height:     int height.
 * @width:      int width.
 * @startx:     int start x pos.
 * @starty:     int start y pos.
 *
 * Returns WINDOW.
 */
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}

/**
 * Print window data.
 *
 * @staryx:     int start x pos for text.
 * @cords[]     int [x,y] cords for text positions.
 * @pos[]:      int [x,y] pos for mouse position.
 * @clicks[]:   int [0,1,2] array for mouse clicks.
 * @mMov:       int mouse movement.
 *
 * Returns nothing.
 */
void print_data(int cords[],
                int pos[],
                unsigned int clicks[],
                unsigned int mMov)
{
    int offset = 18;
    mvprintw(cords[1], cords[0] + 8, "### Mousing ###");
    /* shift to magenta colors */
    attron(COLOR_PAIR(3));
    mvprintw(cords[1] + 2, cords[0] + 2, "Pos:");
    mvprintw(cords[1] + 3, cords[0] + 2, "Movement:");
    mvprintw(cords[1] + 4, cords[0] + 2, "Left click:");
    mvprintw(cords[1] + 5, cords[0] + 2, "Middle click:");
    mvprintw(cords[1] + 6, cords[0] + 2, "Right click:");
    /* shift to cyan colors */
    attron(COLOR_PAIR(2));
    mvprintw(cords[1] + 2, cords[0] + offset, "(%04d,%04d)", pos[0], pos[1]);
    mvprintw(cords[1] + 3, cords[0] + offset, "%s ", commaprint(mMov));
    mvprintw(cords[1] + 4, cords[0] + offset, "%d ", clicks[0]);
    mvprintw(cords[1] + 5, cords[0] + offset, "%d ", clicks[1]);
    mvprintw(cords[1] + 6, cords[0] + offset, "%d ", clicks[2]);
    /* turn off colors */
    attroff(COLOR_PAIR(2));
}

/**
 * Destroy window.
 *
 * @local_win:      pointer to WINDOW.
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
 * Setup function for ncurses.
 *
 * Returns nothing.
 */
void my_setup()
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
void my_colors()
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
