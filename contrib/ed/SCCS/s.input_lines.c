h22012
s 00002/00002/00149
d D 8.1 93/05/31 14:29:25 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00150
d D 5.10 93/04/28 18:24:41 bostic 10 9
c bcopy -> memmove
e
s 00007/00007/00144
d D 5.9 93/04/28 18:07:10 bostic 9 8
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00004/00004/00147
d D 5.8 93/03/18 12:17:32 bostic 8 7
c update from Rodney Ruddock
e
s 00008/00008/00143
d D 5.7 93/03/08 18:31:53 ralph 7 6
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00004/00000/00147
d D 5.6 93/03/01 17:05:58 bostic 6 5
c needs db.h include
e
s 00008/00009/00139
d D 5.5 93/03/01 17:00:13 bostic 5 4
c longjmp fixes
e
s 00001/00001/00147
d D 5.4 93/02/28 15:43:34 bostic 4 3
c lint
e
s 00030/00006/00118
d D 5.3 93/02/28 15:28:53 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00095/00097/00029
d D 5.2 93/01/23 15:47:45 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00126/00000/00000
d D 5.1 93/01/23 11:13:13 bostic 1 0
c date and time created 93/01/23 11:13:13 by bostic
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Rodney Ruddock of the University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include "ed.h"
E 2
I 2
#include <sys/types.h>
E 2

I 2
D 3
#include <db.h>
E 3
#include <regex.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 2

I 6
#ifdef DBI
#include <db.h>
#endif

E 6
I 3
D 5
#ifdef DBI
#include <db.h>
#endif

E 5
E 3
I 2
#include "ed.h"
#include "extern.h"

E 2
/*
 * This central function gets text from some file, which can (and most
 * oft is) stdin. This flexability allows any text inputing function
 * to use it.
 */
D 2

E 2
long
input_lines(fp, errnum)
D 2

FILE *fp;
int *errnum;

E 2
I 2
	FILE *fp;
	int *errnum;
E 2
{
D 2
  long l_ttl=0;
  register long l_nn=0;
  register int l_ss=ss;
  LINE *l_temp_line, *l_temp1;
  register char *l_text=text;
  char *l_text2;
  int l_nn_max=nn_max;
E 2
I 2
	register long l_nn = 0;
	register int l_ss = ss;
	register char *l_text = text;
	LINE *l_temp_line, *l_temp1;
	long l_ttl = 0;
D 3
	int l_nn_max = nn_max;
E 3
I 3
D 4
	int l_nn_max = nn_max, l_jmp_flag;
E 4
I 4
D 5
	int l_nn_max = nn_max;
E 5
I 5
	int l_nn_max = nn_max, l_jmp_flag;
E 5
E 4
E 3
	char *l_text2;
E 2

D 2
  if (End_default)
    start = current;
  else
    start = End;
  start_default = End_default = 0;
  /* start==NULL means line 0 which is legal for this function only */
E 2
I 2
	if (End_default)
D 7
		start = current;
E 7
I 7
		Start = current;
E 7
	else
D 7
		start = End;
	start_default = End_default = 0;
E 7
I 7
		Start = End;
	Start_default = End_default = 0;
E 7
E 2

I 3
	sigspecial++;
E 3
D 2
  nn_max_end = l_temp_line = start;
  if (start == NULL)
    {
      l_temp1 = top;
      u_add_stk(&(top->above));
    }
  else
    {
      u_add_stk(&(start->below));
      l_temp1 = start->below;
    }
E 2
I 2
D 7
	/* start == NULL means line 0 which is legal for this function only. */
	nn_max_end = l_temp_line = start;
	if (start == NULL) {
E 7
I 7
	/* Start == NULL means line 0 which is legal for this function only. */
	nn_max_end = l_temp_line = Start;
	if (Start == NULL) {
E 7
		l_temp1 = top;
		u_add_stk(&(top->above));
	} else {
D 7
		u_add_stk(&(start->below));
		l_temp1 = start->below;
E 7
I 7
		u_add_stk(&(Start->below));
		l_temp1 = Start->below;
E 7
	}
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
E 3
E 2

I 3
	sigspecial++;
I 5
        if (l_jmp_flag = setjmp(ctrl_position3))
                goto point;
E 5

E 3
D 2
  while (1)
  {
    if ((l_ss=getc(fp)) == EOF)
      break; /* if NULL or bit-8 high not text; chuck */
    if ((!l_ss) || (l_ss > 127))
      continue;
    if (sigint_flag)
      goto point;
    l_text[l_nn++] = (char)l_ss;
    if (l_ss == '\n')
      {
       l_text[l_nn-1] = '\0';
       if ((l_nn == 2) && (l_text[0] == '.') && add_flag)
         break;
       nn_max_end = (LINE *)malloc(sizeof(LINE));
       if (nn_max_end == NULL)
         {
           *errnum = -1;
           strcpy(help_msg, "out of memory error");
           return(0L);
         }
       (nn_max_end->len) = l_nn - 1;
       (nn_max_end->handle) = add_line(l_text, l_nn-1);
       (nn_max_end->above) = l_temp_line;
       (nn_max_end->below) = NULL;
       if (l_temp_line)
         (l_temp_line->below) = nn_max_end;
       else
         top = nn_max_end;
       l_temp_line = nn_max_end;
E 2
I 2
	for (;;) {
I 3
D 8
		if (sigint_flag && (!sigspecial))
E 8
I 8
		if (sigint_flag)
E 8
			goto point;
E 3
D 5
		/* If NULL or bit-8 high not text; chuck. */
E 5
I 5
        	sigspecial3 = 1;
E 5
D 3
		if ((l_ss = getc(fp)) == EOF)
E 3
I 3
		l_ss = getc(fp);
I 5
        	sigspecial3 = 0;
E 5
		if (l_ss == EOF) {
D 9
			if (add_flag) {
				l_text[l_nn++] = '\0';
				goto eof_mk;
			}
E 9
I 9
				clearerr(fp);
				if (l_nn) {
					printf("<newline> added at end of line\n");
					l_nn++;
					goto eof_mk;
				}
E 9
E 3
			break;
I 3
		}
E 3
D 5
		if ((!l_ss) || (l_ss > 127))
E 5
I 5
D 8
		if (!l_ss) /* 8-bit okay, but NULL not */
E 5
			continue;
E 8
I 8
D 9
		/*if (!l_ss)*/ /* 8-bit okay, but NULL not */
			/*continue;*/
E 9
E 8
D 3
		if (sigint_flag)
			goto point;
		l_text[l_nn++] = (char) l_ss;
E 3
I 3
		l_text[l_nn++] = (char)l_ss;
E 3
		if (l_ss == '\n') {
I 3
D 8
			if (sigint_flag && (!sigspecial))
E 8
I 8
			if (sigint_flag)
E 8
				goto point;
I 9
eof_mk:
E 9
E 3
			l_text[l_nn - 1] = '\0';
			if ((l_nn == 2) && (l_text[0] == '.') && add_flag)
				break;
I 3
D 9
eof_mk:
E 9
E 3
D 5
			nn_max_end = malloc(sizeof(LINE));
E 5
I 5
			nn_max_end = (LINE *)malloc(sizeof(LINE));
E 5
			if (nn_max_end == NULL) {
				*errnum = -1;
				strcpy(help_msg, "out of memory error");
				return (0L);
			}
			(nn_max_end->len) = l_nn - 1;
			(nn_max_end->handle) = add_line(l_text, l_nn - 1);
			(nn_max_end->above) = l_temp_line;
			(nn_max_end->below) = NULL;
			if (l_temp_line)
				(l_temp_line->below) = nn_max_end;
			else
				top = nn_max_end;
			l_temp_line = nn_max_end;
E 2

D 2
       l_ttl += l_nn;
       l_nn = 0;
      }
    else if (l_nn > l_nn_max)
           {
             l_nn_max += 512;
             nn_max = l_nn_max;
             l_text2 = l_text;
             l_text = text = (char *)calloc(l_nn_max+2, sizeof(char));
             if (text == NULL)
               {
                 *errnum = -1;
                 strcpy(help_msg, "out of memory error");
                 return(0L);
               }
             bcopy(l_text2, l_text, l_nn);
             free(l_text2);
           }
  } /* end-while */
E 2
I 2
			l_ttl += l_nn;
			l_nn = 0;
I 3
			if (l_ss == EOF)
				break;
E 3
		} else
			if (l_nn > l_nn_max) {
				l_nn_max += 512;
				nn_max = l_nn_max;
				l_text2 = l_text;
				l_text = text =
				    calloc(l_nn_max + 2, sizeof(char));
				if (text == NULL) {
					*errnum = -1;
					strcpy(help_msg, "out of memory error");
					return (0L);
				}
D 10
				bcopy(l_text2, l_text, l_nn);
E 10
I 10
				memmove(l_text, l_text2, l_nn);
E 10
				free(l_text2);
			}
	}
E 2

D 2
point:
  current = nn_max_end;
  if (current == NULL)
    current == top;
  if (l_temp1 == NULL)
    bottom = nn_max_end;
  else if (nn_max_end != NULL)
    {
      (nn_max_end->below) = l_temp1;
      u_add_stk(&(l_temp1->above));
      (l_temp1->above) = nn_max_end;
    }

  change_flag = 1;
  *errnum = 1;
  ss = l_ss;
  return(l_ttl);
} /* end-input_lines */
E 2
I 2
point:	current = nn_max_end;
	if (current == NULL)
		current = top;
	if (l_temp1 == NULL)
		bottom = nn_max_end;
	else
		if (nn_max_end != NULL) {
			(nn_max_end->below) = l_temp1;
			u_add_stk(&(l_temp1->above));
			(l_temp1->above) = nn_max_end;
		}
	change_flag = 1;
I 3
	sigspecial--;
I 5
	sigspecial3 = 0;
E 5
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
E 3
	*errnum = 1;
	ss = l_ss;
I 3
D 5
	sigspecial = 0;
E 5
E 3
	return (l_ttl);
}
E 2
E 1
