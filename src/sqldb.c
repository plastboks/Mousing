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

#include "sqldb.h"

void db_open_database(int *retval, sqlite3 **handle) {

  if ((*retval = sqlite3_open("mousing.db", handle))) {
    printf("Database connection failed \n");
  }
}


void db_table_create(int *retval, sqlite3 **handle) {
 
  char id[30] = "id integer primary key";
  char mposx[30] = "mposx integer";
  char mposy[30] = "mposy integer";
  char mmov[30] = "mmov integer";
  char times[50] = "timestamp datetime default current_timestamp";
  char buffr[300];

  sprintf(buffr, "create table if not exists mouse (%s, %s, %s, %s, %s)", id, mposx, mposy, mmov, times);
  *retval = sqlite3_exec(*handle, buffr, 0, 0, 0);
}


void db_insert(int *retval, sqlite3 **handle, int mposx, int mposy, unsigned int mmov) {

  char buffr[150];

  sprintf(buffr, "insert into mouse (mposx, mposy, mmov) values ('%d', '%d', '%d')", mposx, mposy, mmov);
  *retval = sqlite3_exec(*handle, buffr, 0, 0, 0);
}

void db_get_mov(int *retval, sqlite3 **handle, sqlite3_stmt **stmt, unsigned int *mmov) {

  char buffr[150];
  char timestr[30];
  struct tm *local;
  time_t t;

  t = time(NULL);
  local = localtime(&t);
  strftime(timestr, sizeof(timestr), "%Y-%m-%d", local);

  sprintf(buffr, "select mmov from mouse where timestamp like '%s%%' order by mmov desc limit 1", timestr);
  if ((*retval = sqlite3_prepare_v2(*handle, buffr, -1, stmt, 0))) {
    printf("Selecting from database failed \n");
  } else if (sqlite3_step(*stmt) == SQLITE_ROW) {
    *mmov = sqlite3_column_int(*stmt, 0);
  }
}
