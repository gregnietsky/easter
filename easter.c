/*           Simple EASTER date programme                    *
 *           ============================                    *
 * Read the year from the command line (no error checking!)  *
 * and write the date of Easter, according to the Gregorian  *
 * calendar (for years after 1752) or the Julian Calendar    *
 * (for years before 1753), to standard output               *
 * Simon Kershaw: 29.Jan, 1996, 2.Feb.1996.                  *
 */

/*
 *   Copyright (c) Simon Kershaw 1996. All rights reserved.  *
 *   ================================= ====================  *
 *     This code may be reproduced and used, without fee,    *
 *     in part or in full provided the copyright notice and  *
 *     these conditions are distributed with it.  No fee,    *
 *     other than recovery of reasonable costs, may be       *
 *     charged without explicit permission from the          *
 *     author, Simon Kershaw, <webmaster@ely.anglican.org>.  *
 *     All rights reserved.                                  *
 */

/*
 * The date of Easter Day was defined by the Council of      *
 * Nicaea in AD325 as the Sunday after the first full moon   *
 * which falls on or after the Spring Equinox.  The          *
 * Equinox is assumed to always fall on 21st March, so the   *
 * calculation reduces to determining the date of the full   *
 * moon and the date of the following Sunday.  The algorithm *
 * used here was introduced around the year 532 by Dionysius *
 * Exiguus.  Under the Julian Calendar a simple 19-year      *
 * cycle is used to track the phases of the Moon.  Under the *
 * Gregorian Calendar (devised by Clavius and Lilius, and    *
 * introduced by Pope Gregory XIII in October 1582, and into *
 * Britain and its then colonies in September 1752) two      *
 * correction factors are added to make the cycle more       *
 * accurate.                                                 *
 */

#include <stdio.h>
#include <stdlib.h>

main (argc, argv)
int argc;
char *argv[];
{
  int year, golden, solar, lunar, pfm, dom, tmp, easter;
  for(year=2007;year<2200;year++) {
    
    /* the Golden number */
    golden = (year % 19) + 1;

    if ( year <= 1752 )
    {
	/* JULIAN CALENDAR */
	/* the "Dominical number" - finding a Sunday */
	dom = (year + (year/4) + 5) % 7;
	if (dom < 0) dom += 7;

	/* uncorrected date of the Paschal full moon */
	pfm = (3 - (11*golden) - 7) % 30;
	if (pfm < 0) pfm += 30;
    }
    else
    {
	/* GREGORIAN CALENDAR */
	/* the "Dominical number" - finding a Sunday */
	dom = (year + (year/4) - (year/100) + (year/400)) % 7;
	if (dom < 0) dom += 7;

	/* the solar and lunar corrections */
	solar = (year-1600)/100 - (year-1600)/400;
	lunar = (((year-1400) / 100) * 8) / 25;

	/* uncorrected date of the Paschal full moon */
	pfm = (3 - (11*golden) + solar - lunar) % 30;
	if (pfm < 0) pfm += 30;
    }

    /* corrected date of the Paschal full moon - days after 21st March */
    if ((pfm == 29) || (pfm == 28 && golden > 11))
      pfm--;

    tmp = (4-pfm-dom) % 7;
    if (tmp < 0) tmp += 7;

    /* Easter as the number of days after 21st March */
    easter = pfm + tmp + 1;

    if (easter < 13)
	printf("'Good Friday','%i','%i','3'\n",year,easter+19);
    else
	printf("'Good Friday','%i','%i','4'\n",year,easter-12);

    if (easter < 11)
	printf("'Easter Sunday','%i','%i','3'\n",year,easter+21);
    else
	printf("'Easter Sunday','%i','%i','4'\n",year,easter-10);

  }
}

