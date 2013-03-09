/*
 * Mousing sqllite database storage source file.
 *
 * @filename: sqldb.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-09
 *
 * @description: Mousings sqllite database storage source file.
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

#include "sqldb.c"

int db_init(int *retval, &handle) {
  *retval = sqlite3_open("mousing.sqlite", &handle);
  if (retval) {
    printf("Database connection failed\n");
    return -1;
  }
}

int db_create_table(int *retval, &handle) {
  char create_table[100] = "create table if not exists mouse (mposx integer, mposy interger, mmov integer, timestamp datetime)";
  *retval = sqlite3_exec(handle, create_table, 0, 0, 0,);
}

int db_insert(int *retval, &handle, &queries, int *idx, int pos_x, int pos_y, int mov) {
  &queries[idx++] = ("insert into mouse value (%d, %d, %d)", pos_x, pos_y, mov);
  *retval = sqlite3_exec(handle, queries[idx-1], 0, 0, 0);
}

int db_select(int *retval, &handle, &queries, &stmt, int *idx) {
  &queries[idx++] = "select * from mouse"; //make a more usefull query...
  retval = sqlite3_prepare_v2(handle, queries[idx-1], -1, &stmt, 0);
  if (retval) {
    printf("Selecting from database failed\n");
    return -1;
  }
}

