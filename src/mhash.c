/*
 * Mousing hash sourcecode file
 *
 * @filename: hash.c
 *
 * @version: 0.0.2
 *
 * @date: 2013-11-07
 *
 * @description: Mousing hash sourcecode file
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

#include <stdio.h>
#include <stdlib.h>
#include "mhash.h"

/**
 * Make a hash out of the mouse paramenters.
 *
 * @mhash       char mhash SHA1 hash.
 * @mposx       int mouse pos x.
 * @mposy       int mouse pos y.
 * @mmov        int mouse movement.
 * @mlc         int mouse left clicks.
 * @mrc         int mouse right clicks.
 *
 * Returns nothing
 */
void mouse_hash(char *mhash, int mposx, int mposy, unsigned int mmov, unsigned int mlc, unsigned int mrc)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    char buffr[300];
    int qc;

    qc = sprintf(buffr, "%d,%d,%d,%d,%d", mposx, mposy, mmov, mlc, mrc);
    size_t length = sizeof(buffr);
    
    SHA1(buffr, length, hash);

    //*mhash = hash;
}
