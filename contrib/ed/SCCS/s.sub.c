h25356
s 00002/00002/00354
d D 8.1 93/05/31 14:30:05 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00006/00337
d D 5.8 93/05/11 12:08:26 bostic 8 7
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00005/00003/00338
d D 5.7 93/04/30 00:10:07 bostic 7 6
c update from Rodney Ruddock for 4.4BSD; bug fixes, plus reworking
c of the bang command to permit sh scripts from within ed, a la SunOS
e
s 00001/00001/00340
d D 5.6 93/04/28 18:24:42 bostic 6 5
c bcopy -> memmove
e
s 00019/00004/00322
d D 5.5 93/04/28 18:07:16 bostic 5 4
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00009/00009/00317
d D 5.4 93/03/08 18:32:01 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00020/00009/00306
d D 5.3 93/02/28 15:29:04 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00273/00262/00042
d D 5.2 93/01/23 15:47:56 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00304/00000/00000
d D 5.1 93/01/23 11:21:42 bostic 1 0
c date and time created 93/01/23 11:21:42 by bostic
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
 * The substitute command. It's big because of the backward compatability.
 */
D 2

E 2
void
s(inputt, errnum)
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
  static int l_count2=1, l_global=0, l_print=0, l_first_pass_flag=0;
  static char *l_match=NULL, *l_repl=NULL;
  int l_s_flag, l_count, l_matched, l_nflag, l_cnt, yy, l_sr_flag=0, l_err, l_sl;
  char *l_match2=NULL, *l_local=NULL, *l_local_temp=NULL;
  LINE *l_s_ret, *l_temp_line, *l_temp_line2, *l_kval, *l_last;
E 2
I 2
	static int l_count2 = 1, l_global = 0, l_print = 0;
	static int l_first_pass_flag = 0;
	static char *l_match = NULL, *l_repl = NULL;
D 8
	LINE *l_s_ret, *l_temp_line, *l_temp_line2, *l_kval, *l_last;
E 8
I 8
	LINE *l_s_ret, *l_temp_line, *l_temp_line2, *l_kval, *l_last, *l_cur;
E 8
	int l_s_flag, l_count, l_matched, l_nflag, l_cnt, yy, l_sr_flag = 0;
D 5
	int l_err, l_sl;
E 5
I 5
D 7
	int l_err, l_sl, l_rep_flag, l_u_reuse_flag=0;
E 7
I 7
D 8
	int l_err, l_sl, l_rep_flag, l_u_reuse_flag=0, l_local_len;
E 8
I 8
	int l_err, l_sl, l_rep_flag, l_u_reuse_flag=0, l_local_len, l_nudge=0;
E 8
E 7
E 5
	char *l_match2 = NULL, *l_local = NULL, *l_local_temp = NULL;
E 2
#ifndef REG_STARTEND
D 2
  size_t l_offset=0;
E 2
I 2
	size_t l_offset = 0;
E 2
#endif

D 2
  if (start_default && End_default)
    start = End = current;
  else if (start_default)
    start = End;
  if (start == NULL)
    {
      *errnum = -1;
      return;
    }
  start_default = End_default = 0;
E 2
I 2
D 4
	if (start_default && End_default)
		start = End = current;
E 4
I 4
	if (Start_default && End_default)
		Start = End = current;
E 4
	else
D 4
		if (start_default)
			start = End;
	if (start == NULL) {
E 4
I 4
		if (Start_default)
			Start = End;
	if (Start == NULL) {
E 4
		*errnum = -1;
		return;
	}
D 4
	start_default = End_default = 0;
E 4
I 4
	Start_default = End_default = 0;
E 4
E 2

D 2
  l_sl = ss = getc(inputt);
   if (l_first_pass_flag == 0)
    l_match = l_repl = NULL;
  l_match2 = get_pattern(l_sl, inputt, errnum, 0);
  if (sigint_flag)
    SIGINT_ACTION;
  if (*errnum < 0)
    {
      if ((*errnum == -2) && (l_sl != '\n'))
        return;
      if ((l_match2 == NULL) || (strlen(l_match2) > 4) || (l_first_pass_flag == 0))
        return;
      *errnum = 0;
      l_sr_flag = -1;
      for (yy=0; yy<(strlen(l_match2)); yy++)
         {
           switch (l_match2[yy])
                 {
                   case '\n': ss = getc(inputt);
                              goto bcg1;
                              break;
                   case 'r': l_sr_flag = 1;
                             break;
                   case 'p': l_print = (l_print)?0:1;
                             break;
                   case 'g': l_global = (l_global)?0:1;
                             break;
                   case 'N': l_count2 = 1;
                             break;
                   default: *errnum = -1;
                            strcpy(help_msg, "illegal modifier to s");
                            return;
                 } /* end-switch */
         } /* end-for */
      ss = getc(inputt);
      if (l_sr_flag == 1)
        goto bcg2;
      else
        goto bcg1;
    }
E 2
I 2
	l_sl = ss = getc(inputt);
	if (l_first_pass_flag == 0)
		l_match = l_repl = NULL;
	l_match2 = get_pattern(l_sl, inputt, errnum, 0);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
I 3

E 3
	if (*errnum < 0) {
		if ((*errnum == -2) && (l_sl != '\n'))
			return;
		if ((l_match2 == NULL) ||
		    (strlen(l_match2) > 4) || (l_first_pass_flag == 0))
			return;
		*errnum = 0;
		l_sr_flag = -1;
		for (yy = 0; yy < (strlen(l_match2)); yy++) {
			switch (l_match2[yy]) {
			case '\n':
				ss = getc(inputt);
				goto bcg1;
				break;
			case 'r':
				l_sr_flag = 1;
				break;
			case 'p':
				l_print = (l_print) ? 0 : 1;
				break;
			case 'g':
				l_global = (l_global) ? 0 : 1;
				break;
			case 'N':
				l_count2 = 1;
				break;
			default:
				*errnum = -1;
				strcpy(help_msg, "illegal modifier to s");
				return;
			}
		}
		ss = getc(inputt);
		if (l_sr_flag == 1)
			goto bcg2;
		else
			goto bcg1;
	}
	if (l_first_pass_flag) {
		free(l_match);
		free(l_repl);
	} else
		l_first_pass_flag = 1;
	l_match = l_match2;
	*errnum = 0;
	l_repl = get_pattern(ss, inputt, errnum, 1);
D 3
	if (sigint_flag)
E 3
I 3
	if (sigint_flag && (!sigspecial))
E 3
		SIGINT_ACTION;
	l_global = l_print = 0;
	if (*errnum < 0)
		if ((*errnum == -1) && (ss == '\n'))
			/* Note, \n still in stream for next getc. */
			l_print = 1;
		else
			return;
	*errnum = 0;
E 2

D 2
  if (l_first_pass_flag)
    {
      free(l_match);
      free(l_repl);
    }
  else
      l_first_pass_flag = 1;
  l_match = l_match2;
  *errnum = 0;
  l_repl = get_pattern(ss, inputt, errnum, 1);
  if (sigint_flag)
    SIGINT_ACTION;
  l_global = l_print = 0;
  if (*errnum < 0)
    {
      if ((*errnum == -1) && (ss == '\n'))
          l_print = (int)1; /* note: \n still in stream for next getc */
      else
        return;
    }
  *errnum = 0;
E 2
I 2
	l_count2 = 1;
E 2

D 2
  l_count2 = 1;
E 2
I 2
	while (((ss = getc(inputt)) != '\n') && (ss != EOF))
		if (ss == 'g')
			l_global = 1;
		else
			switch (ss) {
			case 'p':
				l_print = (l_print | (int) 1);
				break;
			case 'n':
				l_print = (l_print | (int) 2);
				break;
			case 'l':
				l_print = (l_print | (int) 4);
				break;
			default:
				if ((ss > ('0' - 1)) && (ss < ('9' + 1)))
					l_count2 = dig_num_conv(inputt, errnum);
				else {
					*errnum = -1;
					strcpy(help_msg,
					    "illegal command option");
					return;
				}
		}
E 2

D 2
  while (((ss=getc(inputt)) != '\n') && (ss != EOF))
       {
         if (ss == 'g')
           l_global = 1;
         else if (ss == 'p')
           l_print = (l_print | (int)1);
         else if (ss == 'n')
           l_print = (l_print | (int)2);
         else if (ss == 'l')
           l_print = (l_print | (int)4);
         else if ((ss > ('0'-1)) && (ss < ('9'+1)))
             l_count2 = dig_num_conv(inputt, errnum);
         else
           {
             *errnum = -1;
             strcpy(help_msg, "illegal command option");
             return;
           }
       }

E 2
bcg1:
D 2
  if ((RE_flag == 0) && (l_match[1] == '\0'))
    {
      *errnum = -1;
      ungetc(ss, inputt);
      return;
    }
  else if ((l_sr_flag == 0) && (l_match[1] || (RE_patt == NULL)))
    {
      free(RE_patt);
      RE_patt = (char *)malloc(sizeof(char)*(2+strlen(l_match)));
      bcopy(l_match, RE_patt);
    }
  RE_sol = (l_match[1] == '^')?1:0;
  if ((l_match[1]) && (regfree(&RE_comp), l_err = regcomp(&RE_comp, &l_match[1], 0)))
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
	if ((RE_flag == 0) && (l_match[1] == '\0')) {
		*errnum = -1;
		ungetc(ss, inputt);
		return;
	} else
		if ((l_sr_flag == 0) && (l_match[1] || (RE_patt == NULL))) {
I 3
			int l_m_len = 2 + strlen(l_match);
			sigspecial++;
E 3
			free(RE_patt);
D 3
			RE_patt = malloc(sizeof(char) * (2 + strlen(l_match)));
			bcopy(l_match, RE_patt, strlen(l_match + 1));
E 3
I 3
			RE_patt = malloc(sizeof(char) * (l_m_len));
D 6
			bcopy(l_match, RE_patt, l_m_len);
E 6
I 6
			memmove(RE_patt, l_match, l_m_len);
E 6
			sigspecial--;
			if (sigint_flag && (!sigspecial))
				SIGINT_ACTION;
E 3
		}
	RE_sol = (l_match[1] == '^') ? 1 : 0;
	if ((l_match[1]) &&
	    (regfree(&RE_comp), l_err = regcomp(&RE_comp, &l_match[1], 0))) {
		regerror(l_err, &RE_comp, help_msg, 128);
		*errnum = -1;
		RE_flag = 0;
		ungetc(ss, inputt);
		return;
	}
	RE_flag = 1;
D 3
	if (sigint_flag)
E 3
I 3
	if (sigint_flag && (!sigspecial))
E 3
		SIGINT_ACTION;
E 2
bcg2:
I 8
	l_cur = current;
E 8
D 2
  current = start;
  l_s_flag = 0;
  do
    {
      if (sigint_flag)
        SIGINT_ACTION;
      RE_match[0].rm_eo = 0;
      get_line(current->handle, current->len);
      l_count = l_count2;
      l_local = text;
E 2
I 2
D 4
	current = start;
E 4
I 4
	current = Start;
E 4
	l_s_flag = 0;
	do {
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
		RE_match[0].rm_eo = 0;
		get_line(current->handle, current->len);
I 3
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		l_count = l_count2;
		l_local = text;
I 5
		l_rep_flag = 1;
E 5
E 2
#ifndef REG_STARTEND
D 2
      l_offset = 0;
E 2
I 2
		l_offset = 0;
I 7
#else
		l_local_len = current->len;
E 7
E 2
#endif
D 2
      do
        {
          RE_match[0].rm_so = RE_match[0].rm_eo;
E 2
I 2
		do {
			RE_match[0].rm_so = RE_match[0].rm_eo;
I 8
			if (l_nudge)
				RE_match[0].rm_so++;
			l_nudge = 0;
E 8
E 2
#ifdef REG_STARTEND
D 2
          l_matched = regexec_n(&RE_comp, l_local, (size_t)RE_SEC, RE_match, 0, l_count, (size_t)current->len, 0);
E 2
I 2
			l_matched = regexec_n(&RE_comp, l_local,
			    (size_t)RE_SEC, RE_match, 0, l_count,
D 7
			    (size_t)current->len, 0);
E 7
I 7
			    (size_t)l_local_len, 0);
E 7
E 2
#else
D 2
          l_matched = regexec_n(&RE_comp, l_local, (size_t)RE_SEC, RE_match, 0, l_count, &l_offset, 0);
E 2
I 2
			l_matched = regexec_n(&RE_comp, l_local,
			    (size_t)RE_SEC, RE_match, 0, l_count,
			    &l_offset, 0);
E 2
#endif
D 2
          if (l_matched == 0)
            {
              if ((l_s_flag == 0) && (g_flag == 0))
                u_clr_stk();
              l_count = l_s_flag = 1;
              /* the l_local passed into re_replace is not freed in re_replace
               * because it is "text", the global line holder, for the first
               * pass through this loop. The value returned by re_replace is
               * a new string (with the first replacement in it). If the 'g'
               * flag was set with substitute then this new string is passed in
               * for the second pass and can be freed once re_replace is done
               * with it. (...and so on for the rest of the 'g' passes.
               * RE_match[0].rm_eo is changed in re_replace to be the
               * new location of the next character immediately after
               * the replacement since it is likely the position of that
               * character has changed because of the replacement.
               */
E 2
I 2
			if (l_matched == 0) {
D 8
				if ((l_s_flag == 0) && (g_flag == 0))
E 8
I 8
				if ((l_s_flag == 0) && (g_flag == 0)) {
					current = l_cur;
E 8
					u_clr_stk();
I 8
					current = Start;
				}
E 8
				l_count = l_s_flag = 1;
I 5
				l_rep_flag = 0;
E 5
				/*
				 * The l_local passed into re_replace is not
				 * freed in re_replace because it is "text",
				 * the global line holder, for the first pass
				 * through this loop. The value returned by
				 * re_replace is a new string (with the first
				 * replacement in it). If the 'g' flag was
				 * set with substitute then this new string
				 * is passed in for the second pass and can
				 * be freed once re_replace is done with it.
				 * (...and so on for the rest of the 'g'
				 * passes. RE_match[0].rm_eo is changed in
				 * re_replace to be the new location of the
				 * next character immediately after the
				 * replacement since it is likely the
				 * position of that character has changed
				 * because of the replacement.
				 */
I 8
				if (RE_match[0].rm_so == RE_match[0].rm_eo)
					l_nudge = 1;
E 8
E 2
#ifdef REG_STARTEND
D 2
              l_local = re_replace(l_local, (size_t)(RE_SEC-1), RE_match, &l_repl[1]);
E 2
I 2
				l_local = re_replace(l_local,
				    (size_t)(RE_SEC - 1), RE_match, &l_repl[1]);
I 5
D 7
				(current->len) = strlen(l_local);
E 7
I 7
				l_local_len = strlen(l_local);
E 7
E 5
E 2
#else
D 2
              l_local = re_replace(l_local, (size_t)(RE_SEC-1), RE_match, &l_repl[1], l_offset);
E 2
I 2
				l_local = re_replace(l_local,
				    (size_t)(RE_SEC - 1), RE_match, &l_repl[1],
				    l_offset);
E 2
#endif
D 2
            }
          if (l_global == 0)
            break;
          if (l_local[RE_match[0].rm_eo] == '\0')
            break;
        } while (!l_matched);
E 2
I 2
			}
			if (l_global == 0)
				break;
			if (l_local[RE_match[0].rm_eo] == '\0')
				break;
		} while (!l_matched);
E 2

I 5
		if (l_rep_flag)
			goto next;
E 5
D 2
      l_cnt = l_nflag = 0;
      l_kval = current;
      l_temp_line = current->above;
      l_temp_line2 = current->below;
      l_local_temp = l_local;
      while (1)
           {
             /* make the new string the one for this line. Check if
              * it needs to be split.
              */
             if ((l_local[l_cnt] == '\n') || (l_local[l_cnt] == '\0'))
               {
                 if (l_local[l_cnt] == '\0')
                   l_nflag = 1;
                 l_local[l_cnt] = '\0';
                 l_s_ret = (LINE *)malloc(sizeof(LINE));
                 if (l_s_ret == NULL)
                   {
                     *errnum = -1;
                     strcpy(help_msg, "out of memory error");
                     return;
                   }
                 (l_s_ret->len) = strlen(l_local);
                 (l_s_ret->handle) = add_line(l_local, l_s_ret->len);
                 (l_s_ret->above) = l_temp_line;
                 (l_s_ret->below) = NULL;
                 if (l_temp_line == NULL)
                   top = l_s_ret;
                 else
                   {
                     u_add_stk(&(l_temp_line->below));
                     (l_temp_line->below) = l_s_ret;
                   }
                 l_temp_line = l_s_ret;
                 if ((l_local[l_cnt] == '\0') && (l_nflag == 1))
                   break;
                 else
                   {
                     l_local = &(l_local[l_cnt+1]);
                     l_cnt = 0;
                   }
               } /* end-if */
             else
               l_cnt++;
           } /* end-while */
      (l_s_ret->below) = l_temp_line2;
      ku_chk(current, current, l_kval->below);
      if (current == End)
        End = l_s_ret;
      current = l_s_ret;
      l_last = current;
      if (l_temp_line2 == NULL)
        bottom = l_s_ret;
      else
        {
          u_add_stk(&(l_temp_line2->above));
          (l_temp_line2->above) = current;
        }
      if (l_local_temp != text)
        free(l_local_temp);
      current = current->below;
    } while (current != (End->below));
E 2
I 2
		l_cnt = l_nflag = 0;
		l_kval = current;
		l_temp_line = current->above;
		l_temp_line2 = current->below;
		l_local_temp = l_local;
I 3
		sigspecial++;
E 3
		for (;;) {
			/*
			 * Make the new string the one for this line.  Check if
			 * it needs to be split.
			 */
			if (l_local[l_cnt] == '\n' || l_local[l_cnt] == '\0') {
				if (l_local[l_cnt] == '\0')
					l_nflag = 1;
				l_local[l_cnt] = '\0';
				l_s_ret = malloc(sizeof(LINE));
				if (l_s_ret == NULL) {
					*errnum = -1;
					strcpy(help_msg, "out of memory error");
					return;
				}
				(l_s_ret->len) = strlen(l_local);
				(l_s_ret->handle) = add_line(l_local, l_s_ret->len);
				(l_s_ret->above) = l_temp_line;
				(l_s_ret->below) = NULL;
				if (l_temp_line == NULL)
					top = l_s_ret;
				else {
D 5
					u_add_stk(&(l_temp_line->below));
E 5
I 5
					if ((current != Start) &&
						((&(current->above)) == u_stk->cell))
						l_u_reuse_flag = 1;
					else {
						u_add_stk(&(l_temp_line->below));
						l_u_reuse_flag = 0;
					}
E 5
					(l_temp_line->below) = l_s_ret;
				}
				l_temp_line = l_s_ret;
				if ((l_local[l_cnt] == '\0') && (l_nflag == 1))
					break;
				else {
					l_local = &(l_local[l_cnt + 1]);
					l_cnt = 0;
				}
			} else
				l_cnt++;
		}
		(l_s_ret->below) = l_temp_line2;
		ku_chk(current, current, l_kval->below);
		if (current == End)
			End = l_s_ret;
		current = l_s_ret;
		l_last = current;
		if (l_temp_line2 == NULL)
			bottom = l_s_ret;
		else {
D 5
			u_add_stk(&(l_temp_line2->above));
E 5
I 5
			if (l_u_reuse_flag)
				u_pop_n_swap(&(l_temp_line2->above));
			else
				u_add_stk(&(l_temp_line2->above));
E 5
			(l_temp_line2->above) = current;
		}
I 3
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		if (l_local_temp != text)
			free(l_local_temp);
I 5
next:
E 5
		current = current->below;
	} while (current != (End->below));
E 2

D 2
  if (l_s_flag == 0)
    {
      current = start;
      strcpy(help_msg, "no matches found for substitution");
      *errnum = -1;
      ungetc('\n', inputt);
      return;
    }
E 2
I 2
	if (l_s_flag == 0) {
D 4
		current = start;
E 4
I 4
		current = Start;
E 4
D 8
		strcpy(help_msg, "no matches found for substitution");
		*errnum = -1;
		ungetc('\n', inputt);
E 8
I 8
		if (!g_flag) {
			strcpy(help_msg, "no matches found for substitution");
			*errnum = -1;
			ungetc('\n', inputt);
		}
		else
			*errnum = 0;
E 8
		return;
	}
	change_flag = 1;
	current = l_last;
E 2

D 2
  change_flag = 1;
  current = l_last;

  if (l_print > 0)
    {
      start = End = current;
      ungetc(ss, inputt);
      if (l_print == (l_print | (int)1))
        p(inputt, errnum, 0);
      if (l_print == (l_print | (int)2))
        p(inputt, errnum, 1);
      if (l_print == (l_print | (int)4))
        l(inputt, errnum);
      if (*errnum < 0)
        return;
    }

  if (l_sr_flag == -1)
    {
      regfree(&RE_comp);
      regcomp(&RE_comp, &RE_patt[1], 0);
    }
  *errnum = 1;
} /* end-s */
E 2
I 2
	if (l_print > 0) {
D 4
		start = End = current;
E 4
I 4
D 5
		Start = End = current;
E 5
I 5
		Start = End = l_s_ret; /*current;*/
E 5
E 4
		ungetc(ss, inputt);
		if (l_print == (l_print | (int) 1))
			p(inputt, errnum, 0);
		if (l_print == (l_print | (int) 2))
			p(inputt, errnum, 1);
		if (l_print == (l_print | (int) 4))
			l(inputt, errnum);
		if (*errnum < 0)
			return;
	}
	if (l_sr_flag == -1) {
		regfree(&RE_comp);
		regcomp(&RE_comp, &RE_patt[1], 0);
	}
	*errnum = 1;
}
E 2
E 1
