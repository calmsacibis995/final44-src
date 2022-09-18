h19968
s 00002/00002/00100
d D 8.1 93/05/31 14:28:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00019/00072
d D 5.6 93/04/30 00:10:01 bostic 6 5
c update from Rodney Ruddock for 4.4BSD; bug fixes, plus reworking
c of the bang command to permit sh scripts from within ed, a la SunOS
e
s 00003/00001/00088
d D 5.5 93/04/28 18:07:02 bostic 5 4
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00001/00001/00088
d D 5.4 93/03/18 12:17:29 bostic 4 3
c update from Rodney Ruddock
e
s 00012/00006/00077
d D 5.3 93/02/28 15:28:29 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00057/00055/00026
d D 5.2 93/01/23 15:47:34 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00081/00000/00000
d D 5.1 93/01/23 11:13:00 bostic 1 0
c date and time created 93/01/23 11:13:00 by bostic
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
I 3
#include <limits.h>
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
 * Execute a command in sh (and always sh). For those wondering the
 * proper name for '!' _is_ bang.
 */

void
bang(inputt, errnum)
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
  static char l_shellcmd[FILENAME_LEN]; /* static for "!!" */
  int l_cnt=0, l_esc=0;
  static int l_cnt_last_pos; /* for "!!", offset in _static_ l_shellcmd */
E 2
I 2
D 6
	static int l_cnt_last_pos;		/* "!!", l_shellcmd offset */
E 6
I 6
	static int l_cnt_last_pos=0;		/* "!!", l_shellcmd offset */
E 6
	static char l_shellcmd[FILENAME_LEN];	/* "!!" */
D 6
	int l_cnt = 0, l_esc = 0;
E 6
I 6
	static char l_shellcmd2[FILENAME_LEN];	/* "!!" */
	int l_cnt = 0, l_esc=0, l_flag=0;
E 6
E 2

I 6
	memcpy(l_shellcmd, l_shellcmd2, FILENAME_LEN);

E 6
D 2
  while (1)
       {
         if (sigint_flag)
           SIGINT_ACTION;
         ss = getchar();
         if ((ss == '\\') && (l_esc == 0))
           {
             ss = getchar();
             l_esc = 1;
           }
         else
           l_esc = 0;
         if ((ss == '\n') || (ss == EOF))
           {
             if (l_cnt==0)
               {
                 strcpy(help_msg, "no shell command given");
                 *errnum = -1;
                 ungetc('\n', inputt);
                 return;
               }
             l_shellcmd[l_cnt] = '\0';
             break;
           }
         else if ((ss == '!') && (l_esc == 0))
           l_cnt = l_cnt_last_pos;
         else if ((ss == '%') && (l_esc == 0))
           {
             l_shellcmd[l_cnt] = '\0';
             strcat(l_shellcmd, filename_current);
             l_cnt = l_cnt + strlen(filename_current);
           }
         else
           l_shellcmd[l_cnt++] = ss;
         if (l_cnt >= FILENAME_LEN)
           {
             strcpy(help_msg, "shell command too long");
             *errnum = -1;
             ungetc('\n', inputt);
             return;
           }
       } /* end-while(1) */
E 2
I 2
	for (;;) {
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
D 6
		ss = getchar();
		if ((ss == '\\') && (l_esc == 0)) {
			ss = getchar();
E 6
I 6
		ss = getc(inputt);
		l_esc = 0;
		if (ss == '\\') {
			ss = getc(inputt);
E 6
			l_esc = 1;
D 6
		} else
			l_esc = 0;
		if ((ss == '\n') || (ss == EOF)) {
			if (l_cnt == 0) {
				strcpy(help_msg, "no shell command given");
				*errnum = -1;
				ungetc('\n', inputt);
				return;
			}
E 6
I 6
		}
		if (((!l_esc) && (ss == '\n')) || (ss == EOF)) {
E 6
			l_shellcmd[l_cnt] = '\0';
			break;
		} else
D 5
			if ((ss == '!') && (l_esc == 0))
E 5
I 5
D 6
			if ((ss == '!') && (l_esc == 0)) {
E 6
I 6
			if ((ss == '!') && (l_cnt == 0) && (l_esc == 0)) {
				if (l_cnt_last_pos == 0) {
					strcpy(help_msg,
					    "no remembered command");
					*errnum = -1;
					return;
				}
E 6
E 5
				l_cnt = l_cnt_last_pos;
I 5
D 6
				printf("%s\n", l_shellcmd);
E 6
I 6
				l_flag = 1;
E 6
			}
E 5
			else
				if ((ss == '%') && (l_esc == 0)) {
D 6
					l_shellcmd[l_cnt] = '\0';
E 6
D 3
					strcat(l_shellcmd, filename_current);
					l_cnt =
					    l_cnt + strlen(filename_current);
E 3
I 3
					if (filename_current) {
I 6
						l_shellcmd[l_cnt] = '\0';
E 6
						strcat(l_shellcmd,
						    filename_current);
						l_cnt =
						    l_cnt +
D 6
						    strlen(filename_current);
E 6
I 6
						    strlen(filename_current); 
E 6
					}
I 6
					else {
						strcpy(help_msg,
						    "no current filename");
						*errnum = -1;
						return;
					}
E 6
E 3
				} else
					l_shellcmd[l_cnt++] = ss;
		if (l_cnt >= FILENAME_LEN) {
			strcpy(help_msg, "shell command too long");
			*errnum = -1;
D 6
			ungetc('\n', inputt);
E 6
			return;
		}
	}
E 2

I 6
	if (l_flag)
		printf("%s\n", l_shellcmd);
E 6
D 2
  system(l_shellcmd);
  if (explain_flag != 0)  /* for the -s option */
    printf("!\n");
  l_cnt_last_pos = l_cnt;
  *errnum = 0;
} /* end-bang */
E 2
I 2
	system(l_shellcmd);
D 4
	if (explain_flag != 0)	/* for the -s option */
E 4
I 4
	if (explain_flag > 0)	/* for the -s option */
E 4
		printf("!\n");
	l_cnt_last_pos = l_cnt;
I 6
	memcpy(l_shellcmd2, l_shellcmd, FILENAME_LEN);
E 6
	*errnum = 0;
}
E 2
E 1
