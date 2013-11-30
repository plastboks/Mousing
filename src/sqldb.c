/*
 * Mousing sqllite database storage source file.
 *
 * @filename: sqldb.c
 *
 * @version: 0.0.3
 *
 * @date: 2013-11-30
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mousing.    If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "sqldb.h"

/**
 * Open database.
 *
 * @retval:     int pointer retval.
 * @handle:     int pointer handle.
 *
 * Return nothing.
 */
void db_open_database(int *retval, sqlite3 **handle) {
    
    char *homedir = getenv("HOME");
    char buffr[150];
    sprintf(buffr, "%s/.mousing.db", homedir);

    if ((*retval = sqlite3_open(buffr, handle))) {
        printf("Database connection failed \n");
    }
}

/**
 * Create table for database.
 *
 * @retval:     int pointer retval.
 * @handle:     int pointer handle.
 *
 * Returns nothing.
 */
void db_table_create(int *retval, sqlite3 **handle)
{
    char id[30] = "id integer primary key";
    char mposx[30] = "mposx integer";
    char mposy[30] = "mposy integer";
    char mmov[30] = "mmov integer";
    char mlc[30] = "mlc interger"; // mouse left click.
    char mmc[30] = "mmc interger";
    char mrc[30] = "mrc interger integer"; //mouse right click.
    char times[50] = "timestamp datetime default current_timestamp";
    char buffr[300];

    sprintf(buffr, "create table if not exists mouse (%s, %s, %s, %s, %s, %s, %s, %s)",
            id, mposx, mposy, mmov, mlc, mmc, mrc, times);
    *retval = sqlite3_exec(*handle, buffr, 0, 0, 0);
}

/**
 * Insert data into database.
 *
 * @retval:     int pointer retval.
 * @handle:     int pointer handle.
 * @mposx:      int mouse pos x.
 * @mposy:      int mouse pos y.
 * @mmov:       int mouse movement.
 * @mlc:        int mouse left clicks.
 * @mrc:        int mouse right clicks.
 *
 * Returns nothing.
 */
void db_insert(int *retval,
               sqlite3 **handle,
               int mposx,
               int mposy,
               unsigned int mmov,
               unsigned int mlc,
               unsigned int mmc,
               unsigned int mrc)
{
    char buffr[150];

    sprintf(buffr, "insert into mouse (mposx, mposy, mmov, mlc, mmc, mrc) values ('%d', '%d', '%d', '%d', '%d', '%d')",
            mposx, mposy, mmov, mlc, mmc, mrc);
    *retval = sqlite3_exec(*handle, buffr, 0, 0, 0);
}

/**
 * Select from database.
 *
 * @retval:     int pointer retval.
 * @handle:     int pointer handle.
 * @stmt:       sqlite statement pointer.
 * @mmov:       int mouse movement.
 * @mlc:        int mouse left clicks.
 * @mrc:        int mouse right clicks.
 *
 * Returns nothing.
 */
void db_get_mov(int *retval,
                sqlite3 **handle,
                sqlite3_stmt **stmt,
                unsigned int *mmov,
                unsigned int *mlc,
                unsigned int *mmc,
                unsigned int *mrc)
{
    char buffr[150];
    char timestr[30];
    struct tm *local;
    time_t t;

    t = time(NULL);
    local = localtime(&t);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d", local);

    sprintf(buffr, "select mmov, mlc, mmc, mrc from mouse where timestamp like '%s%%' order by mmov desc limit 1", timestr);

    if ((*retval = sqlite3_prepare_v2(*handle, buffr, -1, stmt, 0))) {
        printf("Selecting from database failed \n");
    } else if (sqlite3_step(*stmt) == SQLITE_ROW) {
        *mmov = sqlite3_column_int(*stmt, 0);
        *mlc = sqlite3_column_int(*stmt, 1);
        *mmc = sqlite3_column_int(*stmt, 2);
        *mrc = sqlite3_column_int(*stmt, 3);
    }
}
