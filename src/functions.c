/*
 * Mousing functions sourcecode file
 *
 * @filename: functions.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-02-26
 *
 * @description: Mousing functions sourcecode file
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

#include "functions.h"

/**
 * code found on the interwebs 
 * @ http://www.eskimo.com/~scs/c-faq.com/stdio/commaprint.html 
 * this adds a function for printing unsigned integers (longs)
 * with tousands commaseperator.
 *
 * @n:      number
 *
 * Returns char.
 */
char *commaprint(unsigned long n) 
{
    static int comma = '\0';
    static char retbuf[30];
    char *p = &retbuf[sizeof(retbuf)-1];
    int i = 0;

    if(comma == '\0') {
        struct lconv *lcp = localeconv();
        if(lcp != NULL) {
            if(lcp->thousands_sep != NULL && *lcp->thousands_sep != '\0') {
                comma = *lcp->thousands_sep;
            } else { 
                comma = ',';
            }
        }
    }

    *p = '\0';

    do {
        if(i%3 == 0 && i != 0) {
            *--p = comma;
        }
        *--p = '0' + n % 10;
        n /= 10;
        i++;
    } while(n != 0);

    return p;
}


void exp_inc(int *input, int expo) 
{
    *input += 10;
    if (*input > pow(2,expo)) {
        *input = 1;
    }
}
