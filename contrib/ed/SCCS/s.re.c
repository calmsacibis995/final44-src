h22200
s 00002/00002/00283
d D 8.1 93/05/31 14:29:56 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00015/00273
d D 5.6 93/05/11 12:08:06 bostic 6 5
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00004/00004/00284
d D 5.5 93/04/28 18:24:41 bostic 5 4
c bcopy -> memmove
e
s 00014/00001/00274
d D 5.4 93/04/28 18:07:15 bostic 4 3
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00004/00001/00271
d D 5.3 93/02/28 15:29:01 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00186/00189/00086
d D 5.2 93/01/23 15:47:53 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00275/00000/00000
d D 5.1 93/01/23 11:13:22 bostic 1 0
c date and time created 93/01/23 11:13:22 by bostic
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
I 3

#ifdef DBI
#include <db.h>
#endif
E 3
E 2

I 2
#include "ed.h"
#include "extern.h"

E 2
/*
 * This finds the n-th occurrence of an RE in a line. If '^' was at the start
D 2
 * of the RE then look once (in case n=1). There is no standard RE
 * interface to do this. returns 0 for success.
 * NOTE: the #ifdef REG_STARTEND is if the regex package has the BSD
 * extensions to it.
E 2
I 2
 * of the RE then look once (in case n=1). There is no standard RE interface
 * to do this.  Returns 0 for success.  NOTE: the #ifdef REG_STARTEND is if
 * the regex package has the BSD extensions to it.
E 2
 */
D 2

E 2
int
#ifdef REG_STARTEND
regexec_n(reprecomp, strg, num_subexp, reprematch, flags, n, len, pass)
#else
regexec_n(reprecomp, strg, num_subexp, reprematch, flags, n, offset, pass)
#endif
D 2

regex_t *reprecomp;
char *strg;
size_t num_subexp;
regmatch_t reprematch[];
int flags, n;
E 2
I 2
	regex_t *reprecomp;
	char *strg;
	size_t num_subexp;
	regmatch_t reprematch[];
	int flags, n;
E 2
#ifdef REG_STARTEND
D 2
size_t len;
E 2
I 2
	size_t len;
E 2
#else
D 2
size_t *offset;
E 2
I 2
	size_t *offset;
E 2
#endif
D 2
int pass; /* if pass==0 .rm_so user set, else set default */

E 2
I 2
	int pass; /* if pass == 0 .rm_so user set, else set default */
E 2
{
D 2
  int l_cnt;
E 2
I 2
D 4
	int l_cnt;
E 4
I 4
	int l_cnt, l_flag=0;
E 4
E 2
#ifndef REG_STARTEND
D 2
  char *l_offset=strg;
E 2
I 2
D 6
	char *l_offset = strg;
E 6
I 6
	char *l_offset=strg, *l_end;
E 6
E 2
#endif

D 2
  if (n <= 0)
    return(REG_NOMATCH);
E 2
I 2
	if (n <= 0)
		return (REG_NOMATCH);
E 2
#ifdef REG_STARTEND
D 2
  flags = (flags | REG_STARTEND);
  if (pass)
    reprematch[0].rm_so = 0;
  reprematch[0].rm_eo = len;
E 2
I 2
	flags = (flags | REG_STARTEND);
	if (pass)
		reprematch[0].rm_so = 0;
	reprematch[0].rm_eo = len;
I 4
D 6
	if (!reprematch[0].rm_so)
		l_flag = 1;
E 6
E 4
E 2
#else
D 2
  strg = &strg[offset];
E 2
I 2
	strg = &strg[offset];
I 4
D 6
	if (!offset)
		l_flag = 1;
E 6
I 6
	l_end = &strg[strlen(strg)];
E 6
E 4
E 2
#endif
D 2
  for (l_cnt=0;;)
     {
       if (regexec(reprecomp, strg, num_subexp, reprematch, flags) == 0)
         l_cnt++;
       else
         return(REG_NOMATCH);
       if (l_cnt>=n)
         break;
E 2
I 2
	for (l_cnt = 0;;) {
		if (regexec(reprecomp,
		    strg, num_subexp, reprematch, flags) == 0)
			l_cnt++;
		else
			return (REG_NOMATCH);
I 4
D 6
		/* to skip over null RE matchings */
		if (l_flag)
			l_flag = 0;
		else
			if (reprematch[0].rm_so == reprematch[0].rm_eo) {
				l_cnt--;
				if ((++reprematch[0].rm_eo) > len)
					return (REG_NOMATCH);
			}
E 6
I 6

E 6
E 4
		if (l_cnt >= n)
			break;
E 2
#ifdef REG_STARTEND
I 6
		if (reprematch[0].rm_so == reprematch[0].rm_eo)
			reprematch[0].rm_eo++;
E 6
D 2
       reprematch[0].rm_so = reprematch[0].rm_eo;
       reprematch[0].rm_eo = len;
E 2
I 2
		reprematch[0].rm_so = reprematch[0].rm_eo;
I 6
		if (reprematch[0].rm_so == len)
			return (REG_NOMATCH);
E 6
		reprematch[0].rm_eo = len;
E 2
#else
D 2
       strg = &strg[reprematch[0].rm_eo];
E 2
I 2
		strg = &strg[reprematch[0].rm_eo];
I 6
		if (strg == l_end)
                        return (REG_NOMATCH);
E 6
E 2
#endif
D 2
       /* if a "^" started the current RE we only loop once */
       if (RE_sol)
         return(REG_NOMATCH);
     }
E 2
I 2
		/* if a "^" started the current RE we only loop once */
		if (RE_sol)
			return (REG_NOMATCH);
	}
E 2
#ifndef REG_STARTEND
D 2
  *offset = (size_t)(strg - l_offset);
E 2
I 2
	*offset = (size_t) (strg - l_offset);
E 2
#endif
D 2
  return(0); /* success */
} /* end-regexec_n */
E 2
I 2
	return (0);		/* success */
}
E 2

D 2


E 2
/*
 * Replace in the line specified at the found locations with the
 * specified replacement. There is no standard RE interface to do
 * this.
 */
D 2

char
E 2
I 2
char *
E 2
#ifdef REG_STARTEND
D 2
*re_replace(line, num_subexp, repmatch, replacer)
E 2
I 2
re_replace(line, num_subexp, repmatch, replacer)
E 2
#else
D 2
*re_replace(line, num_subexp, repmatch, replacer, offset)
E 2
I 2
re_replace(line, num_subexp, repmatch, replacer, offset)
E 2
#endif
D 2

char *line;
size_t num_subexp;
regmatch_t repmatch[];
char *replacer;
E 2
I 2
	char *line;
	size_t num_subexp;
	regmatch_t repmatch[];
	char *replacer;
E 2
#ifndef REG_STARTEND
D 2
size_t offset;
E 2
I 2
	size_t offset;
E 2
#endif
D 2

E 2
{
D 2
  int l_cnt, l_len_new=0, l_new_rm_eo=0;
  regoff_t l_len_before, l_len_whole, l_slen[RE_SEC];
  char *l_string, *l_head;
  static char *l_prev_r=NULL;
  static int l_prev_r_flag=0;
E 2
I 2
	static char *l_prev_r = NULL;
	static int l_prev_r_flag = 0;
	regoff_t l_len_before, l_len_whole, l_slen[RE_SEC];
	int l_cnt, l_len_new = 0, l_new_rm_eo = 0;
	char *l_string, *l_head;
E 2

D 2
  if (l_prev_r_flag == 0)
    {
      l_prev_r_flag = 1;
      l_prev_r = NULL;
    }
  l_head = replacer;
  l_len_before = (repmatch[0].rm_so); /* length of what stays the same before */
  l_len_whole = strlen(line);
  if (num_subexp > RE_SEC-1)
    num_subexp = RE_SEC-1;
  for (l_cnt=0; l_cnt<=num_subexp; l_cnt++)
     l_slen[l_cnt] = (repmatch[l_cnt].rm_eo) - (repmatch[l_cnt].rm_so);
     /* l_slen[0] == len of what is to be replaced */
     /* l_slen[1-9] == len of each backref */
E 2
I 2
	if (l_prev_r_flag == 0) {
		l_prev_r_flag = 1;
		l_prev_r = NULL;
	}
	l_head = replacer;
	/* Length of what stays the same before. */
	l_len_before = (repmatch[0].rm_so);
	l_len_whole = strlen(line);
	if (num_subexp > RE_SEC - 1)
		num_subexp = RE_SEC - 1;
	for (l_cnt = 0; l_cnt <= num_subexp; l_cnt++)
		l_slen[l_cnt] =
		    (repmatch[l_cnt].rm_eo) - (repmatch[l_cnt].rm_so);
E 2

D 2
  if ((*replacer == '%') && (replacer[1] == 1))
    {
      l_string = (char *)calloc(l_len_whole-l_slen[0]+(strlen(l_prev_r))+2, sizeof(char));
      if (l_string == NULL)
        {
          /* *errnum = -1;*/
          strcpy(help_msg, "out of memory error");
          return(NULL);
        }
E 2
I 2
	/*
	 * l_slen[0] == len of what is to be replaced.
	 * l_slen[1-9] == len of each backref.
	 */
D 6
	if ((*replacer == '%') && (replacer[1] == 1)) {
E 6
I 6
	if ((*replacer == '%') && (replacer[1] == '\0')) {
E 6
		l_string = calloc(l_len_whole - l_slen[0] +
		    (strlen(l_prev_r)) + 2, sizeof(char));
		if (l_string == NULL) {
			/* *errnum = -1; */
			strcpy(help_msg, "out of memory error");
			return (NULL);
		}
E 2
#ifdef REG_STARTEND
D 2
      bcopy(line, l_string, (int)l_len_before);
E 2
I 2
D 5
		bcopy(line, l_string, (int) l_len_before);
E 5
I 5
		memmove(l_string, line, (int) l_len_before);
E 5
E 2
#else
D 2
      bcopy(line, l_string, (int)l_len_before+offset);
E 2
I 2
D 5
		bcopy(line, l_string, (int) l_len_before + offset);
E 5
I 5
		memmove(l_string, line, (int) l_len_before + offset);
E 5
E 2
#endif
#ifdef REG_STARTEND
D 2
      l_string[l_len_before] = '\0';
E 2
I 2
		l_string[l_len_before] = '\0';
E 2
#else
D 2
      l_string[l_len_before+offset] = '\0';
E 2
I 2
		l_string[l_len_before + offset] = '\0';
E 2
#endif
D 2
      strcat(l_string, l_prev_r);
E 2
I 2
		strcat(l_string, l_prev_r);
I 6
		l_new_rm_eo = strlen(l_string);
E 6
E 2
#ifdef REG_STARTEND
D 2
      strcat(l_string, &line[repmatch[0].rm_eo]);
E 2
I 2
		strcat(l_string, &line[repmatch[0].rm_eo]);
E 2
#else
D 2
      strcat(l_string, &line[repmatch[0].rm_eo+offset]);
E 2
I 2
		strcat(l_string, &line[repmatch[0].rm_eo + offset]);
E 2
#endif
I 6
		repmatch[0].rm_eo = l_new_rm_eo;
E 6
D 2
      return(l_string);
    }
E 2
I 2
		return (l_string);
	}
E 2

D 2
  /* figure out length of new line first */
  while (*replacer != '\0')
       {
         /* add in the length of the RE match */
         if (*replacer == '&')
           l_len_new = l_len_new + l_slen[0];
         /* add in the length of a backref */
         else if (*replacer == '\\')
           {
             replacer++;
             if ((*replacer > '0') && (*replacer < ('9'+1)) && (repmatch[*replacer-'0'].rm_so > -1))
               l_len_new = l_len_new + l_slen[*replacer-'0']; /* -1 - -1 = 0 */
             else
               l_len_new++;
           }
         else
           l_len_new++;
E 2
I 2
	/* Figure out length of new line first. */
	while (*replacer != '\0') {
		/* Add in the length of the RE match. */
		if (*replacer == '&')
			l_len_new = l_len_new + l_slen[0];
		/* Add in the length of a backref. */
		else if (*replacer == '\\') {
			replacer++;
			if ((*replacer > '0') &&
			    (*replacer < ('9' + 1)) &&
			    (repmatch[*replacer - '0'].rm_so > -1))
				/* -1 - -1 = 0 */
				l_len_new = l_len_new + l_slen[*replacer - '0'];
			else
				l_len_new++;
		} else
			l_len_new++;
		replacer++;
	}
E 2

D 2
         replacer++;
       }

  /* create the line of an appropriate length */
  l_string = (char *)calloc(l_len_whole-l_slen[0]+l_len_new+2, sizeof(char));
  if (l_string == NULL)
    {
      strcpy(help_msg, "out of memory error");
      return(NULL);
    }
  if (l_prev_r != NULL)
    free(l_prev_r);
  l_prev_r = (char *)calloc(l_len_new+2, sizeof(char));
  if (l_prev_r == NULL)
    {
      strcpy(help_msg, "out of memory error");
      return(NULL);
    }

  /* copy over what doesn't change before the chars to be replaced */
E 2
I 2
	/* Create the line of an appropriate length. */
	l_string =
	    calloc(l_len_whole - l_slen[0] + l_len_new + 2, sizeof(char));
	if (l_string == NULL) {
		strcpy(help_msg, "out of memory error");
		return (NULL);
	}
	if (l_prev_r != NULL)
		free(l_prev_r);
	l_prev_r = calloc(l_len_new + 2, sizeof(char));
	if (l_prev_r == NULL) {
		strcpy(help_msg, "out of memory error");
		return (NULL);
	}
	/* Copy over what doesn't change before the chars to be replaced. */
E 2
#ifdef REG_STARTEND
D 2
  bcopy(line, l_string, (int)l_len_before);
E 2
I 2
D 5
	bcopy(line, l_string, (int) l_len_before);
E 5
I 5
	memmove(l_string, line, (size_t)l_len_before);
E 5
E 2
#else
D 2
  bcopy(line, l_string, l_len_before+offset);
E 2
I 2
D 5
	bcopy(line, l_string, l_len_before + offset);
E 5
I 5
	memmove(l_string, line, l_len_before + offset);
E 5
E 2
#endif
#ifdef REG_STARTEND
D 2
  l_string[l_len_before] = '\0';
E 2
I 2
	l_string[l_len_before] = '\0';
E 2
#else
D 2
  l_string[l_len_before+offset] = '\0';
E 2
I 2
	l_string[l_len_before + offset] = '\0';
E 2
#endif
D 2
  l_prev_r[0] = '\0';
E 2
I 2
	l_prev_r[0] = '\0';
E 2

D 2
  /* make the replacement */
  replacer = l_head;
  while (*replacer != '\0')
       {
         /* put what matched the RE into the replacement */
         if (*replacer == '&')
           {
E 2
I 2
	/* Make the replacement. */
	replacer = l_head;
	while (*replacer != '\0') {
		/* Put what matched the RE into the replacement. */
		if (*replacer == '&') {
E 2
#ifdef REG_STARTEND
D 2
            strncat(l_string, &line[repmatch[0].rm_so], (int)l_slen[0]);
E 2
I 2
			strncat(l_string,
			    &line[repmatch[0].rm_so], (int)l_slen[0]);
			strncat(l_prev_r,
			    &line[repmatch[0].rm_so], (int) l_slen[0]);
E 2
#else
D 2
            strncat(l_string, &line[repmatch[0].rm_so+offset], (int)l_slen[0]);
E 2
I 2
			strncat(l_string,
			    &line[repmatch[0].rm_so + offset], (int) l_slen[0]);
			strncat(l_prev_r,
			    &line[repmatch[0].rm_so + offset], (int) l_slen[0]);
E 2
#endif
I 2
		} else if (*replacer == '\\') {
			/* Likely a backref to be included. */
			replacer++;
			if ((*replacer > '0') && (*replacer < ('9' + 1)) &&
			    (repmatch[*replacer - '0'].rm_so > -1)) {
E 2
#ifdef REG_STARTEND
D 2
            strncat(l_prev_r, &line[repmatch[0].rm_so], (int)l_slen[0]);
E 2
I 2
				strncat(l_string,
				    &line[repmatch[*replacer - '0'].rm_so],
				    (int) l_slen[*replacer - '0']);
				strncat(l_prev_r,
				    &line[repmatch[*replacer - '0'].rm_so],
				    (int) l_slen[*replacer - '0']);
E 2
#else
D 2
            strncat(l_prev_r, &line[repmatch[0].rm_so+offset], (int)l_slen[0]);
E 2
I 2
				strncat(l_string,
				    &line[repmatch[*replacer - '0'].rm_so +
				    offset], (int) l_slen[*replacer - '0']);
				strncat(l_prev_r,
				    &line[repmatch[*replacer - '0'].rm_so +
				    offset], (int) l_slen[*replacer - '0']);
E 2
#endif
D 2
           }
         else if (*replacer == '\\')
           {
             /* likely a backref to be included */
             replacer++;
             if ((*replacer > '0') && (*replacer < ('9'+1)) && (repmatch[*replacer-'0'].rm_so > -1))
               {
#ifdef REG_STARTEND
                 strncat(l_string, &line[repmatch[*replacer-'0'].rm_so], (int)l_slen[*replacer-'0']);
#else
                 strncat(l_string, &line[repmatch[*replacer-'0'].rm_so+offset], (int)l_slen[*replacer-'0']);
#endif
#ifdef REG_STARTEND
                 strncat(l_prev_r, &line[repmatch[*replacer-'0'].rm_so], (int)l_slen[*replacer-'0']);
#else
                 strncat(l_prev_r, &line[repmatch[*replacer-'0'].rm_so+offset], (int)l_slen[*replacer-'0']);
#endif
               }
             /* put the replacement in */
             else
               {
                 strncat(l_string, replacer, 1);
                 strncat(l_prev_r, replacer, 1);
               }
           }
         /* put the replacement in */
         else
           {
             strncat(l_string, replacer, 1);
             strncat(l_prev_r, replacer, 1);
           }
E 2
I 2
			}
			/* Put the replacement in. */
			else {
				strncat(l_string, replacer, 1);
				strncat(l_prev_r, replacer, 1);
			}
		}
		/* Put the replacement in. */
		else {
			strncat(l_string, replacer, 1);
			strncat(l_prev_r, replacer, 1);
		}
		replacer++;
	}
E 2

D 2
         replacer++;
       }
  
 l_new_rm_eo = strlen(l_string);
E 2
I 2
	l_new_rm_eo = strlen(l_string);
E 2

D 2
  /* copy over what was after the chars to be replaced to the new line */
E 2
I 2
	/* Copy over what was after the chars to be replaced to the new line. */
E 2
#ifdef REG_STARTEND
D 2
  strcat(l_string, &line[repmatch[0].rm_eo]);
E 2
I 2
	strcat(l_string, &line[repmatch[0].rm_eo]);
E 2
#else
D 2
  strcat(l_string, &line[repmatch[0].rm_eo+offset]);
E 2
I 2
	strcat(l_string, &line[repmatch[0].rm_eo + offset]);
E 2
#endif

D 2
  repmatch[0].rm_eo = l_new_rm_eo; /* update rm_eo */
E 2
I 2
	repmatch[0].rm_eo = l_new_rm_eo;	/* Update rm_eo. */
E 2
#ifndef REG_STARTEND
D 2
  offset += l_new_rm_eo; /* update offset */
E 2
I 2
	offset += l_new_rm_eo;			/* Update offset. */
E 2
#endif
D 2
  return(l_string);   /* return the new line */
} /* end-re_replace */

E 2
I 2
	return (l_string);			/* Return the new line. */
}
E 2
E 1
