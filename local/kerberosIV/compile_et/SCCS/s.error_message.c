h39815
s 00001/00001/00080
d D 5.3 93/05/21 09:06:32 bostic 4 3
c cast const char * so it compiles without complaining
c (no, I didn't fix the problem)
e
s 00001/00001/00080
d D 5.2 93/05/15 22:18:09 torek 3 1
c sys_errlist type changed
e
s 00000/00000/00081
d R 5.2 93/05/15 22:16:02 torek 2 1
c sys_errlist is now const char *const []
e
s 00081/00000/00000
d D 5.1 93/05/15 22:15:05 torek 1 0
c date and time created 93/05/15 22:15:05 by torek
e
u
U
t
T
I 1
/*
 * $Header: error_message.c,v 1.1 86/11/10 21:34:34 spook Exp $
 * $Source: /mit/s/p/spook/Work/et/RCS/error_message.c,v $
 * $Locker: spook $
 *
 * Copyright 1987 by the Student Information Processing Board
 * of the Massachusetts Institute of Technology
 *
 * For copyright info, see "mit-sipb-copyright.h".
 */

#include <stdio.h>
#include "error_table.h"
#include "mit-sipb-copyright.h"
D 3
extern char *sys_errlist[];
E 3
I 3
extern const char *const sys_errlist[];
E 3
extern int sys_nerr;

static char buffer[25];

char *
error_message(code)
     int code;
{
     register int offset;
     register error_table **et;
     register int table_num;
     register int div;
     register char *cp;

     offset = code & ((1<<ERRCODE_RANGE)-1);
     table_num = code - offset;
     if ((_et_list == (error_table **)NULL) && table_num)
	  goto oops;
     if (!table_num) {
	  if (offset < sys_nerr)
D 4
	       return(sys_errlist[offset]);
E 4
I 4
	       return((char *)sys_errlist[offset]);
E 4
	  else
	       goto oops;
     }
     for (et = _et_list; *et != (error_table *)NULL; et++) {
	  if ((*et)->base == table_num) {
	       /* This is the right table */
	       if ((*et)->n_msgs <= offset)
		    goto oops;
	       return((*et)->msgs[offset]);
	  }
     }
 oops:
     cp = buffer;
     {
	  register char *cp1;
	  for (cp1 = "Unknown code "; *cp1; cp1++, cp++)
	       *cp = *cp1;
	  if (table_num) {
	       for (cp1 = error_table_name(table_num); *cp1; cp1++, cp++)
		    *cp = *cp1;
	       *cp++ = ' ';
	       *cp = '\0';
	  }
     }
     div = 1000000000;
     if (offset == 0) {
	  *cp++ = '0';
	  *cp = '\0';
	  return(buffer);
     }
     while (div > offset)
	  div /= 10;
     do {
	  register int n = offset / div;
	  *cp++ = '0' + n;
	  offset -= n * div;
	  div /= 10;
     } while (offset && div);
     while (div) {
	  *cp++ = '0';
	  div /= 10;
     }
     *cp = '\0';
     return(buffer);
}
E 1
