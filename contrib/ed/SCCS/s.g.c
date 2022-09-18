h36053
s 00002/00002/00355
d D 8.1 93/05/31 14:29:12 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00356
d D 5.10 93/05/11 12:07:41 bostic 10 9
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00007/00002/00352
d D 5.9 93/04/30 00:10:04 bostic 9 8
c update from Rodney Ruddock for 4.4BSD; bug fixes, plus reworking
c of the bang command to permit sh scripts from within ed, a la SunOS
e
s 00001/00001/00353
d D 5.8 93/04/28 18:24:17 bostic 8 7
c bcopy -> memmove
e
s 00085/00067/00269
d D 5.7 93/04/28 18:07:09 bostic 7 6
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00001/00001/00335
d D 5.6 93/03/18 12:17:31 bostic 6 5
c update from Rodney Ruddock
e
s 00006/00006/00330
d D 5.5 93/03/08 18:31:48 ralph 5 4
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00003/00003/00333
d D 5.4 93/02/28 15:43:33 bostic 4 3
c lint
e
s 00053/00015/00283
d D 5.3 93/02/28 15:28:50 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00229/00247/00069
d D 5.2 93/01/23 15:47:42 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00316/00000/00000
d D 5.1 93/01/23 11:13:10 bostic 1 0
c date and time created 93/01/23 11:13:10 by bostic
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

I 2
static int	find_line __P((LINE *));
static void	w_cmd_l_file __P((FILE *, FILE *, int *));

E 2
/*
 * Find a line that we noted matched the RE earlier in the current
 * buffer (it may have disappeared because of the commands in the
 * command list).
 */
D 2

E 2
D 3
int
E 3
I 3
static int
E 3
find_line(dot)
D 2

LINE *dot;

E 2
I 2
	LINE *dot;
E 2
{
D 2
  LINE *l_cl;
E 2
I 2
	LINE *l_cl;
E 2

D 2
  l_cl = top;
  while (1)
       {
         if (l_cl == dot)
           return(1);
        if (l_cl == bottom)
          return(0);
        l_cl = l_cl->below;
       }
} /*end-find_line */
E 2
I 2
	l_cl = top;
	for (;;) {
		if (l_cl == dot)
			return (1);
		if (l_cl == bottom)
			return (0);
		l_cl = l_cl->below;
	}
}
E 2

D 2

E 2
/*
 * Write the command line to a STDIO tmp file. See g() below.
 * This allows us to use cmd_loop to run the command list because
 * we "trick" cmd_loop into reading a STDIO file instead of stdin.
 */
I 7

E 7
D 2

E 2
D 3
void
E 3
I 3
static void
E 3
w_cmd_l_file(fp, inputt, errnum)
D 2

FILE *fp, *inputt;
int *errnum;

E 2
I 2
	FILE *fp, *inputt;
	int *errnum;
E 2
{
D 2
  int l_esc=0, l_cnt=0;
E 2
I 2
D 7
	int l_esc = 0, l_cnt = 0;
E 7
I 7
	int sl=0, jmp_flag, l_cnt=0;
E 7
E 2

I 7
	if (jmp_flag = setjmp(ctrl_position3))
		return;

E 7
D 2
  while (1)
       {
         ss = getc(inputt);
         if (ss == '\\')
           {
             l_esc = 1;
             ss = getc(inputt);
           }
         if (((ss == '\n') && (l_esc == 0)) || (ss == EOF))
           {
             /* if no command list default command list to 'p' */
             if (l_cnt == 0)
               fputc('p', fp);
             break;
           }
         l_esc = 0;
         fputc(ss, fp);
         l_cnt++;
       } /* end-while */
  if (ss == EOF)
    clearerr(inputt);
} /* end-w_cmd_l_file */
E 2
I 2
	for (;;) {
I 7
		sigspecial3 = 1;
E 7
		ss = getc(inputt);
D 7
		if (ss == '\\') {
			l_esc = 1;
			ss = getc(inputt);
E 7
I 7
		sigspecial3 = 0;
skip1:
		if (ss == EOF)
			goto skip2;
		else if (ss == '\n') {
			if (sl != '\\') {
skip2:
				if (l_cnt == 0)
					fputc('p', fp);
				else
					fputc(sl, fp);
				break;
			}
E 7
		}
D 7
		if (((ss == '\n') && (l_esc == 0)) || (ss == EOF)) {
			/* if no command list default command list to 'p' */
			if (l_cnt == 0)
				fputc('p', fp);
			break;
E 7
I 7
		else if ((ss == '\\') && (sl == '\\')) {
			sigspecial3 = 1;
			sl = getc(inputt);
			sigspecial3 = 0;
			if (sl == '\\') {
				sigspecial3 = 1;
				sl = getc(inputt);
				sigspecial3 = 0;
				if (sl == EOF)
					goto skip2;
				if (sl == '\n') {
					fputc('\\', fp);
					ss = sl;
				}
				else {
					fputc('\\', fp);
					fputc('\\', fp);
					ss = sl;
					sl = '\\';
					goto skip1;
				}
			}
			else {
				fputc('\\', fp);
				fputc('\\', fp);
				if ((sl == '\n') || (sl == EOF))
					goto skip2;
				else
					ss = sl;
			}
E 7
		}
D 7
		l_esc = 0;
		fputc(ss, fp);
E 7
I 7
		else if (l_cnt)
			fputc(sl, fp);
		sl = ss;
E 7
		l_cnt++;
	}
I 9

	fputc('\n', fp);
E 9
	if (ss == EOF)
		clearerr(inputt);
}
E 2

I 7

E 7
D 2

E 2
/*
 * The global function. All global commands (g, G, v, and V) are handled
 * in here. The lines to be affected by the command list are 1st noted
 * and then the command list is invoked for each line matching the RE.
 * Note the trick of how the command list is executed. Saves a lot of
 * code (and allows for \n's in substitutions).
 */
D 2

E 2
void
g(inputt, errnum)
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
  struct g_list *l_Head, *l_Foot, *l_gut, *l_old;
  static char *l_template_g;
  char *l_patt;
  static int l_template_flag=0;
  int l_re_success, l_flag_v=0, l_err;
  FILE *l_fp, *fopen();
E 2
I 2
D 7
	struct g_list *l_Head, *l_Foot, *l_gut, *l_old;
E 7
	static char *l_template_g;
D 9
	char *l_patt;
E 9
I 9
D 10
	char *l_patt, l_ohm[130];
E 10
I 10
	char *l_patt;
E 10
E 9
	static int l_template_flag = 0;
D 7
	int l_re_success, l_flag_v = 0, l_err;
E 7
I 7
	int l_re_success, l_flag_v = 0, l_err, l_num;
	register l_gut_cnt, a;
	register LINE **l_gut=gut;
E 7
	FILE *l_fp;
E 2
#ifdef POSIX
D 2
  LINE *l_posix_cur;
E 2
I 2
	LINE *l_posix_cur;
E 2
#endif

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
  if (sigint_flag)
    SIGINT_ACTION;
E 2
I 2
D 5
	if (start_default && End_default) {
		start = top;
E 5
I 5
	if (Start_default && End_default) {
		Start = top;
E 5
		End = bottom;
	} else
D 5
		if (start_default)
			start = End;
	if (start == NULL) {
E 5
I 5
		if (Start_default)
			Start = End;
	if (Start == NULL) {
E 5
D 3
		strcpy(help_msg, "bad address");
E 3
I 3
		strcpy(help_msg, "buffer empty");
E 3
		*errnum = -1;
		return;
	}
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

D 2
  if (l_template_flag == 0)
    {
      l_template_flag = 1;
      l_template_g = (char *)calloc(FILENAME_LEN, sizeof(char));
      if (l_template_g == NULL)
        {
          *errnum = -1;
          strcpy(help_msg, "out of memory error");
          return;
        }
    }
  /* set up the STDIO command list file */
  bcopy("/tmp/_4.4bsd_ed_g_XXXXXX\0", l_template_g, 24);
  mktemp(l_template_g);
E 2
I 2
	if (l_template_flag == 0) {
I 3
		sigspecial++;
E 3
		l_template_flag = 1;
		l_template_g = calloc(FILENAME_LEN, sizeof(char));
I 3
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		if (l_template_g == NULL) {
			*errnum = -1;
			strcpy(help_msg, "out of memory error");
			return;
		}
	}
	/* set up the STDIO command list file */
D 8
	bcopy("/tmp/_4.4bsd_ed_g_XXXXXX\0", l_template_g, 24);
E 8
I 8
	memmove(l_template_g, "/tmp/_4.4bsd_ed_g_XXXXXX\0", 24);
E 8
	mktemp(l_template_g);
E 2

D 2
  l_Head = l_Foot = l_gut = l_old = NULL;
E 2
I 2
D 7
	l_Head = l_Foot = l_gut = l_old = NULL;
E 2

E 7
D 2
  if ((ss == 'v') || (ss == 'V'))
    l_flag_v = 1;
E 2
I 2
	if ((ss == 'v') || (ss == 'V'))
		l_flag_v = 1;
E 2

D 2
  if ((ss == 'G') || (ss == 'V'))
    {
      /* if it's an interactive global command we use stdin, not a file */
      GV_flag = 1;
      l_fp = stdin;
    }
  else
    {
      if ((l_fp = fopen(l_template_g, "w+")) == NULL)
        {
          perror("ed: file I/O error");
          exit(1);
        }   
    }
E 2
I 2
	if ((ss == 'G') || (ss == 'V')) {
		/*
		 * If it's an interactive global command we use stdin, not a
		 * file.
		 */
		GV_flag = 1;
		l_fp = stdin;
	} else {
I 3
		sigspecial++;
E 3
		if ((l_fp = fopen(l_template_g, "w+")) == NULL) {
D 3
			perror("ed: file I/O error");
			exit(1);
E 3
I 3
			perror("ed: file I/O error, save buffer in ed.hup");
			do_hup(); /* does not return */
I 6
		}
E 6
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			goto point;
E 3
D 6
		}
E 6
	}
E 2

D 2
  ss = getc(inputt);
E 2
I 2
	ss = getc(inputt);
E 2

D 2
  /* get the RE for the global command */
  l_patt = get_pattern(ss, inputt, errnum, 0);
  if (sigint_flag)
    SIGINT_ACTION;
  if (*errnum < -1) /* instead of: if ((*errnum == -1) && (ss == '\n'))... */
    return;
  *errnum = 0;
  if ((l_patt[1] == '\0') && (RE_flag == 0))
    {
      *errnum = -1;
      ungetc(ss, inputt);
      return;
    }
  else if (l_patt[1] || (RE_patt == NULL))
    {
      free(RE_patt);
      RE_patt = l_patt;
    }
  RE_sol = (RE_patt[1] == '^')?1:0;
  if ((RE_patt[1]) && (regfree(&RE_comp), l_err = regcomp(&RE_comp, &RE_patt[1], 0)))
    {
      regerror(l_err, &RE_comp, help_msg, 128);
      *errnum = -1;
       RE_flag = 0;
      ungetc(ss, inputt);
      return;
    }
  RE_flag = 1;
  if (sigint_flag)
    SIGINT_ACTION;
E 2
I 2
	/* Get the RE for the global command. */
	l_patt = get_pattern(ss, inputt, errnum, 0);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
I 3

E 3
	/* Instead of: if ((*errnum == -1) && (ss == '\n'))... */
	if (*errnum < -1)
		return;
	*errnum = 0;
	if ((l_patt[1] == '\0') && (RE_flag == 0)) {
		*errnum = -1;
		ungetc(ss, inputt);
		return;
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
				goto point;
E 3
		}
	RE_sol = (RE_patt[1] == '^') ? 1 : 0;
	if ((RE_patt[1]) &&
	    (regfree(&RE_comp), l_err = regcomp(&RE_comp, &RE_patt[1], 0))) {
		regerror(l_err, &RE_comp, help_msg, 128);
		*errnum = -1;
		RE_flag = 0;
		ungetc(ss, inputt);
		return;
	}
	RE_flag = 1;
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
I 3

	if (GV_flag)
		ss = getc(inputt);

E 3
E 2
#ifdef POSIX
D 2
  l_posix_cur = current;
E 2
I 2
	l_posix_cur = current;
E 2
#endif
D 2
  current = start;
E 2
I 2
D 5
	current = start;
E 5
I 5
	current = Start;
I 9
D 10
	strcpy(l_ohm, help_msg);
E 10
E 9
E 5
E 2

I 3
	sigspecial++;

I 7
	if ((l_num = line_number(bottom)) > gut_num) {
		sigspecial++;
		gut_num = l_num + 512;
		free(l_gut);
D 9
		l_gut = malloc(sizeof(LINE **) * gut_num);
E 9
I 9
		gut = l_gut = malloc(sizeof(LINE **) * gut_num);
E 9
		sigspecial--;
		if (l_gut == NULL) {
			*errnum = -1;
			strcpy(help_msg, "out of memory error");
#ifdef POSIX
			current = l_posix_cur;
#endif
I 9
			ungetc('\n', inputt);
E 9
			return;
		}
	}
	l_gut_cnt = 0;

E 7
E 3
D 2
  while (1)
       {
         /* find the lines in the buffer that the global command wants
          * to work with
          */
         if (sigint_flag)
           goto point;
         get_line(current->handle, current->len);
         l_re_success = regexec(&RE_comp, text, (size_t)RE_SEC, RE_match, 0);
         /* l_re_success=0 => success */
         if ((l_re_success  != 0 && l_flag_v == 1) || (l_re_success == 0 && l_flag_v == 0))
           {
             if (l_Head == NULL)
               {
                 l_gut = (struct g_list *)malloc(sizeof(struct g_list));
                 if (l_gut == NULL)
                   {
                     *errnum = -1;
                     strcpy(help_msg, "out of memory error");
E 2
I 2
	for (;;) {
		/*
		 * Find the lines in the buffer that the global command wants
		 * to work with.
		 */
D 3
		if (sigint_flag)
E 3
I 3
D 7
		if (sigint_flag && (!sigspecial))
E 3
			goto point;
E 7
		get_line(current->handle, current->len);
I 3
		if (sigint_flag && (!sigspecial))
			goto point;
E 3
		l_re_success =
		    regexec(&RE_comp, text, (size_t) RE_SEC, RE_match, 0);
		/* l_re_success=0 => success */
D 7
		if ((l_re_success != 0 && l_flag_v == 1) ||
		    (l_re_success == 0 && l_flag_v == 0)) {
			if (l_Head == NULL) {
				l_gut = malloc(sizeof(struct g_list));
				if (l_gut == NULL) {
					*errnum = -1;
					strcpy(help_msg, "out of memory error");
E 2
#ifdef POSIX
D 2
                     current = l_posix_cur;
E 2
I 2
					current = l_posix_cur;
E 2
#endif
D 2
                     return;
                   }
                 (l_gut->next) = NULL;
                 (l_gut->cell) = current;
                 l_Foot = l_Head = l_gut;
               }
             else
               {
                 (l_gut->next) = (struct g_list *)malloc(sizeof(struct g_list));
                 if ((l_gut->next) == NULL)
                   {
                     *errnum = -1;
                     strcpy(help_msg, "out of memory error");
                     goto clean;
                   }
                 l_gut = l_gut->next;
                 (l_gut->cell) = current;
                 (l_gut->next) = NULL;
                 l_Foot = l_gut;
               }
           }
E 2
I 2
					return;
				}
				(l_gut->next) = NULL;
				(l_gut->cell) = current;
				l_Foot = l_Head = l_gut;
			} else {
				(l_gut->next) = malloc(sizeof(struct g_list));
				if ((l_gut->next) == NULL) {
					*errnum = -1;
					strcpy(help_msg, "out of memory error");
					goto clean;
				}
				l_gut = l_gut->next;
				(l_gut->cell) = current;
				(l_gut->next) = NULL;
				l_Foot = l_gut;
			}
E 7
I 7
		if ( (l_re_success == 0 && l_flag_v == 0) ||
			(l_re_success && l_flag_v)) {
				l_gut[l_gut_cnt++] = current;
E 7
		}
		if (End == current)
			break;
		current = current->below;
	}
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		goto point;
E 3
E 2

D 2
         if (End == current)
           break;
         current = current->below;
       } /* end-while */
   
  if (l_Head == NULL)
    {
      strcpy(help_msg, "no matches found");
      *errnum = -1;
E 2
I 2
D 7
	if (l_Head == NULL) {
E 7
I 7
	if (l_gut_cnt == 0) {
E 7
		strcpy(help_msg, "no matches found");
D 7
		*errnum = -1;
E 7
E 2
#ifdef POSIX
D 2
      current = l_posix_cur;
E 2
I 2
		current = l_posix_cur;
E 2
#endif
D 2
      return;
    }
E 2
I 2
		return;
	}
	/* if non-interactive, get the command list */
D 3
	if (GV_flag == 0)
E 3
I 3
	if (GV_flag == 0) {
		sigspecial++;
E 3
		w_cmd_l_file(l_fp, inputt, errnum);
I 3
		sigspecial--;
D 7
		if (sigint_flag && (!sigspecial))
E 7
I 7
		if (sigint_flag)
E 7
			goto point;
	}
E 3
D 7
	l_gut = l_Head;
E 7
E 2

D 2
  /* if non-interactive, get the command list */
  if (GV_flag == 0)
    w_cmd_l_file(l_fp, inputt, errnum);
  l_gut = l_Head;
E 2
I 2
	if (g_flag == 0)
		u_clr_stk();
E 2

I 3
	sigspecial++;
E 3
D 2
  if (g_flag == 0)
    u_clr_stk();
E 2
I 2
D 7
	for (;;) {
E 7
I 7
	for (a=0; a<l_gut_cnt; a++) {
E 7
		/*
		 * Execute the command list on the lines that still exist that
		 * we indicated earlier that global wants to work with.
		 */
D 3
		if (sigint_flag)
E 3
I 3
D 7
		if (sigint_flag && (!sigspecial))
E 7
I 7
		if (sigint_flag)
E 7
E 3
			goto point;
		if (GV_flag == 0)
			fseek(l_fp, (off_t)0, 0);
D 7
		if (find_line(l_gut->cell)) {
			current = (l_gut->cell);
E 7
I 7
		if (find_line(l_gut[a])) {
			current = (l_gut[a]);
E 7
			get_line(current->handle, current->len);
I 3
D 7
			if (sigint_flag && (!sigspecial))
E 7
I 7
			if (sigint_flag)
E 7
				goto point;
E 3
			if (GV_flag == 1)
				printf("%s\n", text);
			g_flag++;
			explain_flag--;
I 3
			sigspecial--;
E 3
			cmd_loop(l_fp, errnum);
I 3
			sigspecial++;
E 3
			explain_flag++;
			g_flag--;
			if ((GV_flag == 1) && (*errnum < 0)) {
				ungetc('\n', l_fp);
				break;
			}
			*errnum = 0;
D 7
			if (l_gut == l_Foot)
				break;
			l_gut = l_gut->next;
E 7
		}
	}
E 2

D 2
  while (1)
       {
         /* execute the command list on the lines that still exist
          * that we indicated earlier that global wants to work with.
          */
         if (sigint_flag)
           goto point;
         if (GV_flag == 0)
           fseek(l_fp, 0L, 0);
         if (find_line(l_gut->cell))
           {
             current = (l_gut->cell);
             get_line(current->handle, current->len);
             if (GV_flag == 1)
               printf("%s\n", text);
             g_flag++;
             explain_flag--;
             cmd_loop(l_fp, errnum);
             explain_flag++;
             g_flag--;
             if ((GV_flag == 1) && (*errnum < 0))
               {
                 ungetc('\n', l_fp);
                 break;
               }
             *errnum = 0;
             if (l_gut == l_Foot)
               break;
             l_gut = l_gut->next;
           } /* end-if */
       } /* end-while */

  point:
  if (GV_flag == 0)
    {
      fclose(l_fp);
      unlink(l_template_g);
    }
  GV_flag = 0;
E 2
I 2
point:
I 9
D 10
	strcpy(help_msg, l_ohm);
E 10
E 9
	if (GV_flag == 0) {
		fclose(l_fp);
		unlink(l_template_g);
	}
I 3
D 4
	else {
		ungetc("\n", inputt);
	}
E 4
I 4
	else
		ungetc('\n', inputt);

E 4
E 3
	GV_flag = 0;
E 2
D 7
clean:
D 2
  /* clean up */
  l_gut = l_Head;
  while (1)
       {
         if (l_gut == NULL)
           break;
         l_old = l_gut;
         l_gut = l_gut->next;
         free(l_old);
       } /* end-while */
E 2
I 2
	/* clean up */
	l_gut = l_Head;
	while (1) {
		if (l_gut == NULL)
			break;
		l_old = l_gut;
		l_gut = l_gut->next;
		free(l_old);
	}
E 7
I 7

E 7
E 2
#ifdef POSIX
D 2
  current = l_posix_cur;
E 2
I 2
	current = l_posix_cur;
E 2
#endif
I 3
	sigspecial--;
D 7
	if (sigint_flag && (!sigspecial))
E 7
I 7
	if (sigint_flag)
E 7
		SIGINT_ACTION;
E 3
D 2
  return;
} /* end-g */
E 2
I 2
}
E 2
E 1
