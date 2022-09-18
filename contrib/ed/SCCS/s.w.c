h14424
s 00002/00002/00173
d D 8.1 93/05/31 14:30:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00006/00171
d D 5.8 93/05/11 12:08:19 bostic 8 7
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00002/00001/00175
d D 5.7 93/04/30 00:10:08 bostic 7 6
c update from Rodney Ruddock for 4.4BSD; bug fixes, plus reworking
c of the bang command to permit sh scripts from within ed, a la SunOS
e
s 00035/00011/00141
d D 5.6 93/04/28 18:07:18 bostic 6 5
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00001/00001/00151
d D 5.5 93/03/18 12:17:35 bostic 5 4
c update from Rodney Ruddock
e
s 00007/00007/00145
d D 5.4 93/03/08 18:32:00 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00016/00011/00136
d D 5.3 93/02/28 15:29:06 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00102/00109/00045
d D 5.2 93/01/23 15:47:59 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00154/00000/00000
d D 5.1 93/01/23 11:13:27 bostic 1 0
c date and time created 93/01/23 11:13:27 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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

I 6
#include <limits.h>
E 6
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
 * Write the contents of the buffer out to the real file (spec'd or
 * remembered). If 'w' then overwrite, if 'W' append to the file. 'W'
 * is probably _the_ command that most editors don't have, and it's
 * so(!) useful. The 'wq' works as 'w' but 'q' immediately follows.
 * Shame on POSIX for not including 'W' and 'wq', they're not that
 * hard to implement; yaaa! BSD for keeping it! :-)
 */
D 2

E 2
void
w(inputt, errnum)
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
  int l_ttl=0, l_q_flag=0, l_sl;
  FILE *fopen(), *fp;
  char *filename_read, *temp;
E 2
I 2
D 6
	FILE *fp;
	int l_ttl = 0, l_q_flag = 0, l_sl;
D 3
	char *filename_read, *temp;
E 3
I 3
	char *filename_read=NULL, *temp;
E 6
I 6
	FILE *l_fp;
	int l_ttl = 0, l_q_flag = 0, l_sl, l_bang_flag=0;
	char *filename_read=NULL, *l_temp;
E 6
E 3
E 2

D 2
  if (start_default && End_default)
    {
      start = top;
      End = bottom;
    }
  else if (start_default)
    start = End;
  if (start == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      return;
    }
  start_default = End_default = 0;
E 2
I 2
D 4
	if (start_default && End_default) {
		start = top;
E 4
I 4
	if (Start_default && End_default) {
		Start = top;
E 4
		End = bottom;
	} else
D 4
		if (start_default)
			start = End;
	if (start == NULL) {
E 4
I 4
		if (Start_default)
			Start = End;
D 8
	if (Start == NULL) {
E 4
D 3
		strcpy(help_msg, "bad address");
E 3
I 3
		strcpy(help_msg, "buffer empty");
E 3
		*errnum = -1;
		return;
	}
E 8
D 4
	start_default = End_default = 0;
E 4
I 4
	Start_default = End_default = 0;
E 4
E 2

D 2
  l_sl = ss;
  ss = getc(inputt);
E 2
I 2
	l_sl = ss;
	ss = getc(inputt);
E 2

D 2
  if (ss == 'q')  /* "wq" and "Wq" command */
    l_q_flag = 1;
  else
    ungetc(ss, inputt);
E 2
I 2
	if (ss == 'q')		/* "wq" and "Wq" command */
		l_q_flag = 1;
	else
		ungetc(ss, inputt);
E 2

D 2
  temp = filename(inputt, errnum);
  if (sigint_flag)
    SIGINT_ACTION;
  if (*errnum == 1)
    filename_read = temp;
  else if (*errnum == -2)
    {
      while (((ss = getc(inputt)) != '\n') || (ss == EOF))
           ;
      filename_read = filename_current;
    }
  else if (*errnum < 0)
    return;
  *errnum = 0;
E 2
I 2
D 6
	temp = filename(inputt, errnum);
E 6
I 6
	l_temp = filename(inputt, errnum);
E 6
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	if (*errnum == 1)
D 6
		filename_read = temp;
E 6
I 6
		filename_read = l_temp;
E 6
	else
		if (*errnum == -2) {
			while (((ss = getc(inputt)) != '\n') || (ss == EOF));
			filename_read = filename_current;
		} else
			if (*errnum < 0)
				return;
	*errnum = 0;
E 2

D 2
  if (filename_current == NULL)
    {
      if (filename_read == NULL)
        {
          strcpy(help_msg, "no filename given");
          *errnum = -1;
          ungetc('\n', inputt);
          return;
        }
      else
        filename_current = filename_read;
    }
E 2
I 2
	if (filename_current == NULL) {
		if (filename_read == NULL) {
			strcpy(help_msg, "no filename given");
			*errnum = -1;
			ungetc('\n', inputt);
			return;
		} else
			filename_current = filename_read;
	}
I 3
	sigspecial++;
E 3
D 6
	if (l_sl == 'W')
		fp = fopen(filename_read, "a");
E 6
I 6
	if (l_temp && l_temp[FILENAME_LEN+1]) { /* bang flag */
		FILE *popen();

		if (l_temp[0] == '\0') {
			strcpy(help_msg, "no command given");
			*errnum = -1;
			sigspecial--;
			return;
		}
		if ((l_fp = popen(l_temp, "w")) == NULL) {
			strcpy(help_msg, "error executing command");
			*errnum = -1;
			if (l_fp != NULL)
				pclose(l_fp);
			sigspecial--;
			return;
		}
		l_bang_flag = 1;
	}
	else if (l_sl == 'W')
		l_fp = fopen(filename_read, "a");
E 6
	else
D 6
		fp = fopen(filename_read, "w");
E 6
I 6
		l_fp = fopen(filename_read, "w");
E 6
E 2

D 2
  if (l_sl == 'W')
    fp = fopen(filename_read, "a");
  else
    fp = fopen(filename_read, "w");
E 2
I 2
D 6
	if (fp == NULL) {
E 6
I 6
	if (l_fp == NULL) {
E 6
		strcpy(help_msg, "cannot write to file");
		*errnum = -1;
		ungetc('\n', inputt);
I 6
		sigspecial--;
E 6
		return;
	}
D 3
	if (sigint_flag)
E 3
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
E 3
		goto point;
E 2

D 2
  if (fp == NULL) 
    {
      strcpy(help_msg, "cannot write to file");
      *errnum = -1;
      ungetc('\n', inputt);
      return;
    }
E 2
I 2
	/* Write it out and get a report on the number of bytes written. */
D 4
	l_ttl = edwrite(fp, start, End);
E 4
I 4
D 6
	l_ttl = edwrite(fp, Start, End);
E 6
I 6
D 8
	l_ttl = edwrite(l_fp, Start, End);
E 8
I 8
	if (Start == NULL)
		l_ttl = 0;
	else
		l_ttl = edwrite(l_fp, Start, End);
E 8
E 6
E 4
D 5
	if (explain_flag != 0)		/* For -s option. */
E 5
I 5
	if (explain_flag > 0)		/* For -s option. */
E 5
		printf("%d\n", l_ttl);
E 2

D 2
  if (sigint_flag)
    goto point;

  /* write it out and get a report on the number of bytes written */
  l_ttl = edwrite(fp, start, End);
  if (explain_flag != 0)  /* for -s option */
    printf("%d\n", l_ttl);
  point:
  fclose(fp);
  if (sigint_flag)
    SIGINT_ACTION;
  if (filename_read != filename_current)
    free(filename_read);
  change_flag = 0L;
  *errnum = 1;
  if (l_q_flag)  /* for "wq" */
    {
      ungetc('\n', inputt);
      ss = (int)'q';
      q(inputt, errnum);
    }
  return;
E 2
I 2
D 6
point:	fclose(fp);
E 6
I 6
point:	if (l_bang_flag)
		pclose(l_fp);
	else
		fclose(l_fp);
E 6
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	if (filename_read != filename_current)
		free(filename_read);
D 7
	change_flag = 0L;
E 7
I 7
	if ((Start == top) && (End == bottom))
		change_flag = 0L;
E 7
	*errnum = 1;
D 3
	if (l_q_flag) {			/* For "wq". */
E 3
I 3
	if (l_q_flag) {			/* For "wq" and "Wq". */
E 3
		ungetc('\n', inputt);
		ss = (int) 'q';
		q(inputt, errnum);
	}
E 2
}

/*
 * Actually writes out the contents of the buffer to the specified
 * STDIO file pointer for the range of lines specified.
 */
D 2

E 2
int
edwrite(fp, begi, fini)
D 2

FILE *fp;
LINE *begi, *fini;

E 2
I 2
	FILE *fp;
	LINE *begi, *fini;
E 2
{
D 2
  register int l_ttl=0;
E 2
I 2
	register int l_ttl = 0;
E 2

D 2
  while (1)
       {
         get_line(begi->handle, begi->len);
         /* fwrite is about 20+% faster than fprintf -- no surprise */
         fwrite(text, sizeof(char), begi->len, fp);
         fputc('\n', fp);
         l_ttl = l_ttl + (begi->len) + 1;
         if (begi == fini)
           break;
         else
           begi = begi->below;
         if (sigint_flag)
           return(l_ttl);
       }
  return(l_ttl);
} /* end-write */
E 2
I 2
	for (;;) {
		get_line(begi->handle, begi->len);
I 3
		if (sigint_flag && (!sigspecial))
			break;
E 3

I 3
		sigspecial++;
E 3
		/* Fwrite is about 20+% faster than fprintf -- no surprise. */
		fwrite(text, sizeof(char), begi->len, fp);
		fputc('\n', fp);
		l_ttl = l_ttl + (begi->len) + 1;
		if (begi == fini)
			break;
		else
			begi = begi->below;
D 3
		if (sigint_flag)
			return (l_ttl);
E 3
I 3
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			break;
E 3
	}
	return (l_ttl);
}
E 2
E 1
