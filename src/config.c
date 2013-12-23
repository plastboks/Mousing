/*
 * Mousing config source code file
 *
 * @filename: config.c
 *
 * @version: 0.0.4
 *
 * @date: 2013-12-17
 *
 * @description: Mousing functions source code file
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

#include "config.h"

/**
 * Setup mousing. Create folders for database files and config files
 *
 * Returns nothing.
 */
void config_setup()
{
    char *homedir;
    char path[512];
    struct stat st;

    homedir = getenv("HOME");
    sprintf(path, "%s/.mousing", homedir);

    /**
     * Check if directory exists, if not create it.
     */
    if (stat(path, &st) != 0) {
        mkdir(path, 0755);
    }
}
