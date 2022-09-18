h49853
s 00002/00002/00145
d D 8.1 93/05/31 14:29:53 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00142
d D 5.8 93/05/11 12:08:00 bostic 8 7
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00041/00008/00102
d D 5.7 93/04/28 18:07:14 bostic 7 6
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00001/00001/00109
d D 5.6 93/03/18 12:17:35 bostic 6 5
c update from Rodney Ruddock
e
s 00003/00027/00107
d D 5.5 93/03/01 17:03:22 bostic 5 4
c make it 8-bit clean
e
s 00001/00001/00133
d D 5.4 93/02/28 15:43:36 bostic 4 3
c lint
e
s 00009/00006/00125
d D 5.3 93/02/28 15:29:00 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00102/00121/00029
d D 5.2 93/01/23 15:47:53 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00150/00000/00000
d D 5.1 93/01/23 11:13:21 bostic 1 0
c date and time created 93/01/23 11:13:21 by bostic
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

D 2
#include "ed.h"
E 2
I 2
#include <sys/types.h>
#include <sys/stat.h>

I 7
#include <limits.h>
E 7
E 2
#include <a.out.h>
I 2
D 3
#include <db.h>
E 3
E 2
#include <errno.h>
I 2
#include <regex.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 2

I 3
#ifdef DBI
#include <db.h>
#endif

E 3
I 2
#include "ed.h"
#include "extern.h"

E 2
/*
 * This sets up things for the central input routine to place the
 * incoming text at the proper place in the buffer.
 */
D 2

E 2
void
r(inputt, errnum)
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
  FILE *fopen(), *l_fp;
  long l_num;
  char *l_filename_read, *l_temp;
  struct stat l_s_buf;
  int l_srv;
  struct exec l_magic;
E 2
I 2
D 5
	struct exec l_magic;
	struct stat l_s_buf;
E 5
	FILE *l_fp;
	long l_num;
D 3
	char *l_filename_read, *l_temp;
E 3
I 3
D 7
	char *l_filename_read=NULL, *l_temp;
E 7
I 7
	int l_bang_flag=0;
	char *l_filename_read=NULL, *l_temp=NULL;
E 7
E 3
D 5
	int l_srv;
E 5
E 2

D 2
  if (filename_flag == 1)
    {
      l_filename_read = filename_current;
      filename_flag = 0;
    }
  else
    {
      l_temp = filename(inputt, errnum);
      if (*errnum == 1)
        l_filename_read = l_temp;
      else if (*errnum == -2)
        {
          while (((ss = getc(inputt)) != '\n') || (ss == EOF))
               ;
          l_filename_read = filename_current;
        }
      else if (*errnum < 0)
        return;
      *errnum = 0;
    } /* end-else */
E 2
I 2
	if (filename_flag == 1) {
I 3
		sigspecial++;
E 3
		l_filename_read = filename_current;
D 7
		filename_flag = 0;
E 7
I 7
		l_temp = filename_current;
E 7
I 3
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
	} else {
I 8
		if (End_default) {
			End = bottom;
			End_default = 0;
		}
E 8
		l_temp = filename(inputt, errnum);
		if (*errnum == 1)
			l_filename_read = l_temp;
		else
			if (*errnum == -2) {
				while (((ss = getc(inputt)) != '\n') ||
				    (ss == EOF));
				l_filename_read = filename_current;
			} else
D 7
				if (*errnum < 0)
E 7
I 7
				if (*errnum < 0) {
					filename_flag = 0;
E 7
					return;
I 7
				}
E 7
		*errnum = 0;
	}
E 2

D 2
  if (filename_current == NULL)
    {
      if (l_filename_read == NULL)
        {
          strcpy(help_msg, "no filename given");
          *errnum = -1;
          if (ss)
            ungetc('\n', inputt);
          return;
        }
      else
        filename_current = l_filename_read;
    }
E 2
I 2
	if (filename_current == NULL) {
		if (l_filename_read == NULL) {
			strcpy(help_msg, "no filename given");
			*errnum = -1;
I 7
			filename_flag = 0;
E 7
			if (ss)
				ungetc('\n', inputt);
			return;
		} else
			filename_current = l_filename_read;
	}
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

D 2
  if (sigint_flag)
    SIGINT_ACTION;
E 2
I 2
	/*
	 * Determine if the file can be read.  If not set the help message to
	 * something descriptive that the user should understand.
I 5
	 * We're now allowing ed to read directory and executable files
D 7
	 * for as much as it can, if there are NULL's in the file it
	 * is guaranteed to be different since ed doesn't do NULL's.
E 7
I 7
	 * for as much as it can, if the last character in the file
	 * isn't a '\n' then one will be added and a warning given - the
	 * user (for now) has to figure out how to remove it if they want.
	 * Ed accepts the NUL character now.
E 7
E 5
	 */
D 5
	if (((l_srv = stat(l_filename_read, &l_s_buf)) == -1) ||
	    (l_s_buf.st_mode & S_IFDIR)) {
		if (l_srv == -1)
			strcpy(help_msg, strerror(errno));
		else
			strcpy(help_msg,
			    "filename is directory, not a text file");
		printf("?%s\n", l_filename_read);
		*errnum = 0;
		return;
	}
E 5
D 7
	if ((l_fp = fopen(l_filename_read, "r")) == NULL) {
E 7
I 7
	if (l_temp && l_temp[FILENAME_LEN+1]) { /* bang flag */
		FILE *popen();

		if (l_temp[0] == '\0') {
			strcpy(help_msg, "no command given");
			*errnum = -1;
			return;
		}
		if ((l_fp = popen(l_temp, "r")) == NULL) {
			strcpy(help_msg, "error executing command");
			*errnum = -1;
			filename_flag = 0;
			if (l_fp != NULL)
				pclose(l_fp);
			return;
		}
		if (filename_flag == 1)
			filename_current = NULL;
		l_bang_flag = 1;
	}
	else if ((l_fp = fopen(l_filename_read, "r")) == NULL) {
E 7
		strcpy(help_msg, "permission lacking to read file");
		printf("?%s\n", l_filename_read);
I 7
		filename_flag = 0;
E 7
		*errnum = 0;
		return;
D 5
	}
	/*
	 * There is permission to read the file, but if it's an executable
	 * file of the object code and linked type, we really don't want to
	 * look at it (according to ed spec's).
	 */
	if (fread(&l_magic, sizeof(struct exec), 1, l_fp) != 0) {
		if (!(N_BADMAG(l_magic))) {
			strcpy(help_msg, "unable to read executable file");
			printf("?%s\n", l_filename_read);
			*errnum = 0;
			return;
		}
E 5
	}
D 7
	fseek(l_fp, (off_t)0, 0);
E 7
I 7
	filename_flag = 0;
	if (!l_bang_flag)
		fseek(l_fp, (off_t)0, 0);
E 7
	if (g_flag == 0)
		u_clr_stk();
	l_num = input_lines(l_fp, errnum);
D 3
	if (sigint_flag == 1)
		goto point;
E 3
	if (*errnum < 0)
		return;
	*errnum = 0;
E 2

D 2
  /* determine if the file can be read. If not set the help message
   * to something descritive that the user should understand.
   */
  if (((l_srv = stat(l_filename_read, &l_s_buf)) == -1) || (l_s_buf.st_mode & S_IFDIR))
    {
      if (l_srv == -1)
        {
          switch (errno)
                {
                  case ENOTDIR: strcpy(help_msg, "directory in pathname does not exist");
                                break;
                  case ENOENT: strcpy(help_msg, "file does not exist");
                               break;
                  case EACCES: strcpy(help_msg, "permission lacking to read file");
                               break;
                  case ENAMETOOLONG: strcpy(help_msg, "pathname or component of pathname too long");
                                     break;
                  case EIO: strcpy(help_msg, "I/O error during read");
                            break;
                  case ELOOP: strcpy(help_msg, "too many symbolic links in pathname");
                              break;
                  default: strcpy(help_msg, "unable to read file stat");
                           break;
                }
        }
      else
        strcpy(help_msg, "filename is directory, not a text file");
      printf("?%s\n", l_filename_read);
      *errnum = 0;
      return;
    }
E 2
I 2
D 6
	if (explain_flag)	/* !=0 */
E 6
I 6
	if (explain_flag > 0)
E 6
		printf("%ld\n", l_num);
	if (l_filename_read != filename_current)
		free(l_filename_read);
E 2

D 2
  if ((l_fp = fopen(l_filename_read, "r")) == 0)
    {
      strcpy(help_msg, "permission lacking to read file");
      printf("?%s\n", l_filename_read);
      *errnum = 0;
      return;
    }

  /* there is permission to read the file, but if it's an executable
   * file of the object code and linked type, we really don't want
   * to look at it (according ed spec's).
   */
  if (fread(&l_magic, sizeof(struct exec), 1, l_fp) != 0)
    {
      if (!(N_BADMAG(l_magic)))
        {
          strcpy(help_msg, "unable to read executable file");
          printf("?%s\n", l_filename_read);
          *errnum = 0;
          return;
        }
    }
  fseek(l_fp, 0L, 0);
  if (g_flag == 0)
    u_clr_stk();
  l_num = input_lines(l_fp, errnum);
  if (sigint_flag == 1)
    goto point;
  if (*errnum < 0)
    return;
  *errnum = 0;

  if (explain_flag) /* !=0 */
    printf("%ld\n", l_num);
  if (l_filename_read != filename_current)
    free(l_filename_read);
  point:
  fclose(l_fp);
  change_flag = 1;
  if (sigint_flag)
    SIGINT_ACTION;
  *errnum = 1;
} /* end-r */
E 2
I 2
D 4
point:	fclose(l_fp);
E 4
I 4
D 7
	fclose(l_fp);
E 7
I 7
	if (l_bang_flag)
		pclose(l_fp);
	else
		fclose(l_fp);
E 7
E 4
D 8
	change_flag = 1;
E 8
I 8
	/*change_flag = 1; done in input_lines() already */
E 8
	if (sigint_flag)
		SIGINT_ACTION;
	*errnum = 1;
}
E 2
E 1
