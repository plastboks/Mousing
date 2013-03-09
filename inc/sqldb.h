/*
 * Mousing sqlite3 database header file
 *
 * @filename: sqldb.h
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-09
 *
 * @description: Mousing sqlite3 database header file
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

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int db_init(int *retval, &handle);
int db_create_table(int *retval, &handle);
int db_insert(int *retval, &handle, &queries, int *idx, int pos_x, int pos_y, int mov);
int db_select(int *retval, &handle, &queries, &stmt, int *idx);
