/*
 * Mousing ncurses box sourcefile
 *
 * @filename: ncbox.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-04
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
 * @starty:     int start y pos.
 * @startx:     int start x pos.
 *
 * Returns WINDOW.
 */
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);

    return local_win;
}

/**
 * Print window data.
 *
 * @starty:     int start y pos for text.
 * @staryx:     int start x pos for text.
 * @m_y:        int m_y.
 * @m_x:        int m_x.
 * @mask_r:     int mask_r.
 * @m_o:        int m_o
 *
 * Returns nothing.
 */
void print_data(int starty, int startx, int m_y, int m_x, unsigned int mask_r, unsigned int m_o)
{
    int offset = 20;
    mvprintw(starty, startx + 10, "### Mousing ###");
    mvprintw(starty + 2, startx + 2, "Y-pos:");
    mvprintw(starty + 3, startx + 2, "X-pos:");
    mvprintw(starty + 4, startx + 2, "Movement:");
    attron(COLOR_PAIR(2));
    mvprintw(starty + 2, startx + offset, "%d ", m_y);
    mvprintw(starty + 3, startx + offset, "%d ", m_x);
    mvprintw(starty + 4, startx + offset, "%s ", commaprint(m_o));
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
