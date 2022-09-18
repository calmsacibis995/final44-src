h19239
s 00002/00002/00116
d D 8.1 93/05/31 14:29:34 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00004/00110
d D 5.6 93/05/31 13:58:17 bostic 6 5
c fix 'l' to work on other than text -- from Rodney for 4.4BSD
e
s 00007/00007/00107
d D 5.5 93/03/08 18:31:55 ralph 5 4
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00001/00001/00113
d D 5.4 93/03/02 08:54:06 bostic 4 3
c typo
e
s 00007/00004/00107
d D 5.3 93/02/28 15:28:55 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00084/00075/00027
d D 5.2 93/01/23 15:47:47 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00102/00000/00000
d D 5.1 93/01/23 11:13:16 bostic 1 0
c date and time created 93/01/23 11:13:16 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Rodney Ruddock of the University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <sys/types.h>

D 3
#include <db.h>
E 3
#include <regex.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

I 3
#ifdef DBI
#include <db.h>
#endif

E 3
E 2
#include "ed.h"
I 2
#include "extern.h"
E 2

/*
 * This is the list command. It's not wrapped in with n and p because
D 4
 * of the unambiguous printing needed.
E 4
I 4
 * of the unambiguous printing need.
E 4
 */
D 2

E 2
void
l(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
D 2
  int l_cnt, l_len=1;
E 2
I 2
	int l_cnt, l_len = 1;
E 2

D 2
  if (start_default && End_default)
    start = End = current;
  else if (start_default)
    start = End;
E 2
I 2
D 5
	if (start_default && End_default)
		start = End = current;
E 5
I 5
	if (Start_default && End_default)
		Start = End = current;
E 5
	else
D 5
		if (start_default)
			start = End;
E 5
I 5
		if (Start_default)
			Start = End;
E 5
E 2

D 2
  if (start == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      return;
    }
  start_default = End_default = 0;
E 2
I 2
D 5
	if (start == NULL) {
E 5
I 5
	if (Start == NULL) {
E 5
D 3
		strcpy(help_msg, "bad address");
E 3
I 3
		strcpy(help_msg, "empty buffer");
E 3
		*errnum = -1;
		return;
	}
D 5
	start_default = End_default = 0;
E 5
I 5
	Start_default = End_default = 0;
E 5
E 2

D 2
  if (rol(inputt, errnum))  /* for "command-suffix pairs" */
    return;
E 2
I 2
	if (rol(inputt, errnum))	/* For "command-suffix pairs". */
		return;
E 2

D 2
  current = start;
  while (1)
       {
         /* print out the line character-by-character and split the line
          * when line length is at line_length.
          */
         if (sigint_flag)
           SIGINT_ACTION;
         if (current == NULL)
           break;
         get_line(current->handle, current->len);
         for (l_cnt=0; l_cnt<current->len; l_cnt++)
            {
              /* check if line needs to be broken first */
              if ((l_len)%line_length == 0)
                putchar('\n');
              /* print out the next character */
              if (text[l_cnt] == '\b') /* backspace (cntl-H) */
                fwrite("\\b", sizeof(char), 2, stdout);
              else if (text[l_cnt] == '\t') /* horizontal tab */
                fwrite("\\t", sizeof(char), 2, stdout);
              else if (text[l_cnt] == '\n') /* newline, not that there is one */
                fwrite("\\n", sizeof(char), 2, stdout);
              else if (text[l_cnt] == '\v') /* vertical tab */
                fwrite("\\v", sizeof(char), 2, stdout);
              else if (text[l_cnt] == '\f') /* form feed */
                fwrite("\\f", sizeof(char), 2, stdout);
              else if (text[l_cnt] == '\r') /* return */
                fwrite("\\r", sizeof(char), 2, stdout);
              else if ((text[l_cnt] < 32) || (text[l_cnt] > 126)) /* not printable */
/* 127 is del */
                {
                  putchar('\\');
                  putchar(text[l_cnt]/64+'0');
                  putchar(text[l_cnt]/8+'0');
                  putchar(text[l_cnt]%8+'0');
                  l_len += 2;
                }
              else if (text[l_cnt] == '\\')
                fwrite("\\\\", sizeof(char), 2, stdout);
              else
                {
                  l_len--;
                  putchar(text[l_cnt]);
                }
              l_len += 2;
            }
         l_len = 1;
         putchar('\n');
         if (current == End)
           break;
         current = current->below;
       } /* end-while */

  *errnum = 1;
} /* end-l */
E 2
I 2
D 5
	current = start;
E 5
I 5
	current = Start;
E 5
	for (;;) {
		/*
		 * Print out the line character-by-character and split the
		 * line when line length is at line_length.
		 */
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
		if (current == NULL)
			break;
		get_line(current->handle, current->len);
I 3
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		for (l_cnt = 0; l_cnt < current->len; l_cnt++, l_len += 2) {
			/* Check if line needs to be broken first. */
D 6
			if ((l_len) % line_length == 0)
E 6
I 6
			if (l_len > line_length) {
E 6
				putchar('\n');
I 6
				l_len = 0;
			}
E 6
			else switch (text[l_cnt]) {
			case '\b':	/* backspace (cntl-H) */
				fwrite("\\b", sizeof(char), 2, stdout);
				break;
			case '\t':	/* horizontal tab */
				fwrite("\\t", sizeof(char), 2, stdout);
				break;
			case '\n':	/* newline (not that there is one). */
				fwrite("\\n", sizeof(char), 2, stdout);
				break;
			case '\v':	/* vertical tab */
				fwrite("\\v", sizeof(char), 2, stdout);
				break;
			case '\f':	/* form feed */
				fwrite("\\f", sizeof(char), 2, stdout);
				break;
			case '\r':	/* return */
				fwrite("\\r", sizeof(char), 2, stdout);
				break;
			default:
				if ((text[l_cnt] < 32) ||
				    (text[l_cnt] > 126)) {
					putchar('\\');
D 6
					putchar(text[l_cnt] / 64 + '0');
					putchar(text[l_cnt] / 8 + '0');
					putchar(text[l_cnt] % 8 + '0');
E 6
I 6
					putchar(((text[l_cnt] & 0xC0) >> 6)
					    + '0');
					putchar(((text[l_cnt] & 0x38) >> 3)
					    + '0');
					putchar((text[l_cnt] & 0x07) + '0');
E 6
					l_len += 2;
				} else if (text[l_cnt] == '\\')
					fwrite("\\\\", sizeof(char), 2, stdout);
				else {
					l_len--;
					putchar(text[l_cnt]);
				}
				break;
			}
		}
		l_len = 1;
		putchar('\n');
		if (current == End)
			break;
		current = current->below;
	}
	*errnum = 1;
}
E 2
E 1
