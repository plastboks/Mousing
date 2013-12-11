/*
 * Mousing sqlite3 database header file
 *
 * @filename: sqldb.h
 *
 * @version: 0.0.2
 *
 * @date: 2013-11-07
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
#include <time.h>

void db_open_database(int *retval, sqlite3 **handle);
void db_table_create(int *retval, sqlite3 **handle);
void db_insert(int *retval,
               sqlite3 **handle,
               unsigned int mmov,
               int pos[],
               unsigned int clicks[]);
void db_get_mov(int *retval,
                sqlite3 **handle,
                sqlite3_stmt **stmt,
                unsigned int *mmov,
                unsigned int clicks[]
                );
void db_get_stats_7(int *retval, sqlite3 **handle, sqlite3_stmt **stmt, int data[][4]);
