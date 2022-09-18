h54918
s 00002/00002/00182
d D 8.1 93/05/31 14:30:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00015/00152
d D 5.3 93/02/28 15:29:03 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00134/00140/00033
d D 5.2 93/01/23 15:47:55 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00173/00000/00000
d D 5.1 93/01/23 11:13:24 bostic 1 0
c date and time created 93/01/23 11:13:24 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
#include <stdlib.h>
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
 * searches forward through the buffer (wrapping if necessary) for a
 * line that contains a match to the RE.
 */

D 2
LINE
*search(inputt, errnum)

FILE *inputt;
int *errnum;

E 2
I 2
LINE *
search(inputt, errnum)
	FILE *inputt;
	int *errnum;
E 2
{
I 2
	LINE *l_temp;
	int l_err;
	char *l_patt;
E 2

D 2
  LINE *l_temp;
  int l_err;
  char *l_patt;
E 2
I 2
D 3
	l_temp = current->below;
E 3
I 3
	if (current)
		l_temp = current->below;
	else {
		*errnum = -1;
		ungetc(ss, inputt);
		strcpy(help_msg, "buffer empty");
		return(NULL);
	}
E 3
	/* Get the RE. */
	l_patt = get_pattern(ss, inputt, errnum, 0);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	if (*errnum < -1)
		return (NULL);
	*errnum = 0;
	if ((RE_flag == 0) && (l_patt[1] == '\0')) {
		*errnum = -1;
		ungetc(ss, inputt);
		return (NULL);
	} else
		if (l_patt[1] || (RE_patt == NULL)) {
I 3
			sigspecial++;
E 3
			free(RE_patt);
			RE_patt = l_patt;
I 3
			sigspecial--;
			if (sigint_flag && (!sigspecial))
				SIGINT_ACTION;
E 3
		}
	RE_sol = (RE_patt[1] == '^') ? 1 : 0;
E 2

D 2
  l_temp = current->below;
  /* get the RE */
  l_patt = get_pattern(ss, inputt, errnum, 0);
  if (sigint_flag)
    SIGINT_ACTION;
  if (*errnum < -1)
    return(NULL);
  *errnum = 0;
  if ((RE_flag == 0) && (l_patt[1] == '\0'))
    {
      *errnum = -1;
      ungetc(ss, inputt);
      return(NULL);
    }
  else if (l_patt[1] || (RE_patt == NULL))
    {
      free(RE_patt);
      RE_patt = l_patt;
    }
  RE_sol = (RE_patt[1] == '^')?1:0;
  /* compile it up */
  if ((l_patt[1]) && (regfree(&RE_comp), l_err = regcomp(&RE_comp, &RE_patt[1], 0)))
    {
      regerror(l_err, &RE_comp, help_msg, 128);
      *errnum = -1;
      RE_flag = 0;
      ungetc(ss, inputt);
      return(NULL);
    }
  RE_flag = 1;
  if (sigint_flag)
    SIGINT_ACTION;
  /* find a line that has the RE in it */
  while (1) /*(l_temp != current)*/
       {
         if (l_temp == NULL)
           {
             if (top != NULL)
               l_temp = top;
             else
               break;
           }
         get_line(l_temp->handle, l_temp->len);
         if (regexec(&RE_comp, text, (size_t)RE_SEC, RE_match, 0))
           {
             l_temp = l_temp->below;
             if (l_temp == (current->below))
                break;
           }
         else
           {
             *errnum = 0;
             return(l_temp);
           }
         if (sigint_flag)
           SIGINT_ACTION;
       } /* end-while */
  strcpy(help_msg, "RE not found");
  *errnum = -1;
  return(NULL);
} /* end-search */
E 2
I 2
	/* Compile it up. */
	if ((l_patt[1]) &&
	    (regfree(&RE_comp), l_err = regcomp(&RE_comp, &RE_patt[1], 0))) {
		regerror(l_err, &RE_comp, help_msg, 128);
		*errnum = -1;
		RE_flag = 0;
		ungetc(ss, inputt);
		return (NULL);
	}
	RE_flag = 1;
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

I 2
	/* Find a line that has the RE in it. */
	for (;;) {		/* (l_temp != current) */
		if (l_temp == NULL) {
			if (top != NULL)
				l_temp = top;
			else
				break;
		}
		get_line(l_temp->handle, l_temp->len);
I 3
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		if (regexec(&RE_comp, text, (size_t) RE_SEC, RE_match, 0)) {
			l_temp = l_temp->below;
			if (l_temp == (current->below))
				break;
		} else {
			*errnum = 0;
			return (l_temp);
		}
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
	}
	strcpy(help_msg, "RE not found");
	*errnum = -1;
	return (NULL);
}

E 2
/*
 * Searches backward through the buffer (wrapping if necessary) to find
 * a line that contains a match to the RE.
 */
D 2

LINE
*search_r(inputt, errnum)
E 2
I 2
LINE *
search_r(inputt, errnum)
	FILE *inputt;
	int *errnum;
{
	LINE *l_temp;
	int l_err;
	char *l_patt;
E 2

D 2
FILE *inputt;
int *errnum;
E 2
I 2
D 3
	l_temp = current->above;
E 3
I 3
	if (current)
		l_temp = current->above;
	else {
		*errnum = -1;
		ungetc(ss, inputt);
		strcpy(help_msg, "buffer empty");
		return(NULL);
	}
E 3
E 2

D 2
{
E 2
I 2
	/* Get the RE. */
	l_patt = get_pattern(ss, inputt, errnum, 0);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	if (*errnum < -1)
		return (NULL);
	*errnum = 0;
	if ((RE_flag == 0) && (l_patt[1] == '\0')) {
		*errnum = -1;
		ungetc(ss, inputt);
		return (NULL);
	} else
		if (l_patt[1] || (RE_patt == NULL)) {
I 3
			sigspecial++;
E 3
			free(RE_patt);
			RE_patt = l_patt;
I 3
			sigspecial--;
			if (sigint_flag && (!sigspecial))
				SIGINT_ACTION;
E 3
		}
	RE_sol = (RE_patt[1] == '^') ? 1 : 0;
E 2

D 2
  LINE *l_temp;
  int l_err;
  char *l_patt;
E 2
I 2
	/* Compile up the RE. */
	if ((l_patt[1]) &&
	    (regfree(&RE_comp), l_err = regcomp(&RE_comp, &RE_patt[1], 0))) {
		regerror(l_err, &RE_comp, help_msg, 128);
		*errnum = -1;
		RE_flag = 0;
		ungetc(ss, inputt);
		return (NULL);
	}
	RE_flag = 1;
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

D 2
  l_temp = current->above;
  /* get the RE */
  l_patt = get_pattern(ss, inputt, errnum, 0);
  if (sigint_flag)
    SIGINT_ACTION;
  if (*errnum < -1)
    return(NULL);
  *errnum = 0;
  if ((RE_flag == 0) && (l_patt[1] == '\0'))
    {
      *errnum = -1;
      ungetc(ss, inputt);
      return(NULL);
    }
  else if (l_patt[1] || (RE_patt == NULL))
    {
      free(RE_patt);
      RE_patt = l_patt;
    }
  RE_sol = (RE_patt[1] == '^')?1:0;
  /* compile up the RE */
  if ((l_patt[1]) && (regfree(&RE_comp), l_err = regcomp(&RE_comp, &RE_patt[1], 0)))
    {
      regerror(l_err, &RE_comp, help_msg, 128);
      *errnum = -1;
      RE_flag = 0;
      ungetc(ss, inputt);
      return(NULL);
    }
  RE_flag = 1;
  if (sigint_flag)
    SIGINT_ACTION;
  /* search for a line that has the RE in it */
  while (1) /*(l_temp != (current->above))*/
       {
         if (l_temp == NULL)
           {
             if (bottom != NULL)
               l_temp = bottom;
             else
               break;
           }
         get_line(l_temp->handle, l_temp->len);
         if (regexec(&RE_comp, text, (size_t)RE_SEC, RE_match, 0))
           {
             l_temp = l_temp->above;
             if (l_temp == (current->above))
               break;
           }
         else
           {
             *errnum = 0;
             return(l_temp);
           }
        if (sigint_flag)
          SIGINT_ACTION;
       } /* end-while */
  strcpy(help_msg, "RE not found");
  *errnum = -1;
  return(NULL);
} /* end-search */
E 2
I 2
	/* Search for a line that has the RE in it. */
	for (;;) {		/* (l_temp != (current->above)) */
		if (l_temp == NULL) {
			if (bottom != NULL)
				l_temp = bottom;
			else
				break;
		}
		get_line(l_temp->handle, l_temp->len);
I 3
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		if (regexec(&RE_comp, text, (size_t) RE_SEC, RE_match, 0)) {
			l_temp = l_temp->above;
			if (l_temp == (current->above))
				break;
		} else {
			*errnum = 0;
			return (l_temp);
		}
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
	}
	strcpy(help_msg, "RE not found");
	*errnum = -1;
	return (NULL);
}
E 2
E 1
