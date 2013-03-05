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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mousing.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ncbox.h"


WINDOW *create_newwin(int height, int width, int starty, int startx) { 
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  box(local_win, 0 , 0);
  wrefresh(local_win);
  return local_win;
}


void print_data(int starty, int startx, int m_y, int m_x, unsigned int mask_r) {
  int offset = 20;
  mvprintw(starty, startx + 10, "### Mousing ###");
  
  mvprintw(starty + 2, startx + 2, "Mouse y-pos:");
  mvprintw(starty + 3, startx + 2, "Mouse x-pos:");
  attron(COLOR_PAIR(2));
  mvprintw(starty + 2, startx + offset, "%d ", m_y);
  mvprintw(starty + 3, startx + offset, "%d ", m_x);
  attroff(COLOR_PAIR(2));
}


void destroy_win(WINDOW *local_win) { 
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(local_win);
  delwin(local_win);
  endwin();
  refresh();
}


void my_setup() {
  initscr();
  curs_set(0);
  cbreak();
  nodelay(stdscr, true);
}


void my_colors() {
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
