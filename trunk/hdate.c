/*
    hdate - Displays Hijri date.
    Copyright (C) 2004,2005 Mohammad Hafiz bin Ismail (mypapit) <mypapit@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Note : This program is inspired by (but not copied from!) ddate.

    Project's web : http://hdate.googlecode.com/
   
*/

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
  int wDay;
  int wMonth;
  int wYear;
} Haribulan;

int
shortusage ()
{
  puts ("\nPrints Hijri date:\n\t hdate [-nm]");
  puts ("\nConverts Gregorian date:\n\t hdate [-nm] [day month year]\n");
  
  return 0;
}

int
usage ()
{
  puts ("hdate (0.1.0) - Display Hijri date, by Mohammad Hafiz bin Ismail <mypapit@gmail.com>");
  shortusage ();
  puts ("-n\t: dd/mm/yyyy format");
  puts ("-m\t: mm/dd/yyyy format");
  puts ("-h\t: this help\n");
  puts ("This software is licensed under the GNU General Public License version 2.");
  return 0;
}



char *
p (int day)
{
  switch (day)
	{
	case 1:
	case 21:
	  return "st";
	  break;
	case 2:
	case 22:
	  return "nd";
	  break;
	case 3:
	case 23:
	  return "rd";
	  break;

	default:
	  return "th";
	  break;


	}
}
static char *BulanMelayu[] =
  { "Muharam", "Safar", "Rabiulawal", "Rabiulakhir", "Jamaldiawal",
  "Jamaldiakhir", "Rajab", "Syaban", "Ramadhan", "Syawal", "Zulkaedah",
  "Zulhijjah"
};

/* 
static char *weekDay[] =
  { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
  "Saturday"
};
*/

static int
toHijrah (int d, int m, int y, Haribulan * hijrah)
{

  int jd, l, j, n;

/*era Julian */
  if ((y > 1582) || ((y == 1582) && (m > 10))
	  || ((y == 1582) && (m == 10) && (d > 14)))
	{
	  jd =
		(int) ((1461 * (y + 4800 + (int) ((m - 14) / 12))) / 4) +
		(int) ((367 * (m - 2 - 12 * ((int) ((m - 14) / 12)))) / 12) -
		(int) ((3 *
				((int) ((y + 4900 + (int) ((m - 14) / 12)) / 100))) /
			   4) + d - 32075;
	}
  else							/*era Gregorian */
	{
	  jd =
		367 * y - (int) ((7 * (y + 5001 + (int) ((m - 9) / 7))) / 4) +
		(int) ((275 * m) / 9) + d + 1729777;
	}
  l = jd - 1948440 + 10632;
  n = (int) ((l - 1) / 10631);
  l = l - 10631 * n + 354;
  j =
	((int) ((10985 - l) / 5316)) * ((int) ((50 * l) / 17719)) +
	((int) (l / 5670)) * ((int) ((43 * l) / 15238));
  l =
	l - ((int) ((30 - j) / 15)) * ((int) ((17719 * j) / 50)) -
	((int) (j / 16)) * ((int) ((15238 * j) / 43)) + 29;
  m = (int) ((24 * l) / 709);
  d = l - (int) ((709 * m) / 24);
  y = 30 * n + j - 30;
  hijrah->wDay = d;
  hijrah->wMonth = m;
  hijrah->wYear = y;
  return 0;
}

int
main (int argc, char *argv[])
{
  time_t now;
  Haribulan hb;
  struct tm *timeinfo;
  char temp[1024];

  int date, month, year;
  int option = 0;
  int flag = 0;

  now = time (NULL);
  timeinfo = localtime (&now);


  toHijrah (timeinfo->tm_mday, timeinfo->tm_mon + 1,
			timeinfo->tm_year + 1900, &hb);
  if (argc < 2)
	{
	  /*empty */


	}

  else if ((argv[1][0] == '-'))
	{
	  flag = 1;
	  if (argv[1][1] == 'n')
		{
		  option = 1;
		}
	  else if (argv[1][1] == 'm')
		{
		  option = 2;
		}
	  else if (argv[1][1] == 'h')
		{
		  option = 900;
		}

	  else
		{
		  option = 200;
		}

	}
  else if (argc < 4)
	{
	  option = 200;
	}
  if (argc > 3)
	{


	  date = atoi (argv[flag + 1]);
	  month = atoi (argv[flag + 2]);
	  year = atoi (argv[flag + 3]);
	  flag += 10;

	  if ((date < 1) || (month < 1) || (date > 31) || (month > 12)
		  || (year < 622))
		{
		  option = 100;

		}
	  switch (month)
		{
		case 4:
		case 6:
		case 9:
		case 11:
		  if (month > 30)
			{
			  option = 100;
			}

		  break;
		case 2:
		  if (((year % 4) == 0))
			{
			  if (!(year % 100) && !(year % 400))
				{

				  if (date > 29)
					{
					  option = 100;
					}
				}
			  else if (!(year % 100))
				{
				  if (date > 28)
					{
					  option = 100;
					}
				}



			}
		  else if (date > 28)
			{
			  option = 100;
			}
		  break;
		}


	  toHijrah (date, month, year, &hb);


	}

/*  if (flag > 10)
	{

	  toHijrah (timeinfo->tm_mday, timeinfo->tm_mon + 1,
				timeinfo->tm_year + 1900, &hb);
	}
  else
	{
	  toHijrah (date, month, year, &hb);
	}
*/
  switch (option)
	{
	case 0:
	  if (flag > 9)
		{
		  sprintf (temp, "%d%s of %s in %d H",
				   hb.wDay, p (hb.wDay), BulanMelayu[hb.wMonth - 1],
				   hb.wYear);
		}
	  else
		{

		  sprintf (temp, "Today is the %d%s day of %s in %d H",
				   hb.wDay, p (hb.wDay), BulanMelayu[hb.wMonth - 1],
				   hb.wYear);
		}
	  break;

	case 1:
	  sprintf (temp, "%02d/%02d/%d", hb.wDay, hb.wMonth, hb.wYear);
	  break;

	case 2:
	  sprintf (temp, "%02d/%02d/%d", hb.wMonth, hb.wDay, hb.wYear);
	  break;

	case 100:
	  fprintf (stderr, "Error : invalid date\n");
	  shortusage ();
	  return option;
	  break;

	case 200:
	  usage ();
	  fprintf (stderr, "Error : invalid argument!\n");
	  return option;
	  break;

	case 900:
	  usage ();
	  break;

	default:

	  /*intentionally left blank :) */
	  break;
	}


  printf ("%s\n", temp);
  return 0;
}
