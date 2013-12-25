/*
 * Mousing functions sourcecode file
 *
 * @filename: functions.c
 *
 * @version: 0.0.4
 *
 * @date: 2013-11-07
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
 * Code found on the interwebs 
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


/**
 * My own implementation of the pow function found in the
 * math library. This function is declared here because I
 * did not want to include a whole library for one function.
 * mpow is just a aberration of mousing power.
 *
 * @base        int base integer.
 * @exponent    int exponent.
 *
 * Returns integer
 */
int mpow(int base, int exponent)
{
    for (int i = 0; i <= exponent; i++) {
        base  = base * exponent;
    }
    return base;
}


/**
 * A small and banal function for doing something quite easy.
 * This function is placed here mostly for aesthetic reasons.
 *
 * @input       int input
 * @expo        int expo
 *
 * Returns int
 */
void exp_inc(int *input, int expo)
{
  *input += 10;
  if (*input > mpow(2,expo)) {
    *input = 1;
  }
}
