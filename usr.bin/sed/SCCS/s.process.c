h36943
s 00001/00005/00602
d D 8.6 94/04/20 15:14:41 bostic 23 22
c P1003.2b/D9 says:
c If the end of the input is reached, the n command shall branch to the end
c of the script and quit without starting a new cycle
e
s 00037/00020/00570
d D 8.5 94/04/20 14:51:51 bostic 22 21
c change the replacement algoricthm to only replace when:
c (1) the previous replacement was for an empty match, or
c (2) the current replacement is for a non-empty match.
c this makes empty RE's work as they did historically
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00001/00001/00589
d D 8.4 94/04/20 13:57:13 bostic 21 20
c The `D' command in sed was leaving junk at the end of the pattern space.
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00001/00001/00589
d D 8.3 94/04/16 08:12:21 bostic 20 19
c update copyright notice
e
s 00003/00001/00587
d D 8.2 94/02/16 14:28:43 bostic 19 18
c sed -e 's/$/ \\/g' /etc/passwd loops forever
c break out of the "g" loop when the regular expression being substituted
c is of zero length
c From: Diomidis Spinellis <dspin@leon.nrcps.ariadne-t.gr>
e
s 00002/00002/00586
d D 8.1 93/06/06 16:16:23 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00586
d D 5.16 93/05/18 14:46:20 elan 17 16
c Strnchr() -> memchr().
e
s 00004/00001/00584
d D 5.15 93/04/14 09:13:53 torek 16 15
c fix REs over completely empty spaces
c (test case: echo '' | sed 'x;s/^.*/foo/')
e
s 00017/00035/00568
d D 5.14 93/04/14 06:22:36 elan 15 14
c make sed work on 8-bit objects
c TK checking in for Elan Amir
e
s 00043/00023/00560
d D 5.13 93/01/27 14:28:10 elan 14 13
c Initial version that will work with binary files.
e
s 00001/00001/00582
d D 5.12 93/01/15 13:53:08 elan 13 12
c Fixed bug in cspace -- precdence of == is less that '+'.
e
s 00002/00000/00581
d D 5.11 93/01/06 11:26:07 bostic 12 11
c "echo '1+1' | sed -f /usr/src/usr.bin/sed/math.sed" drops core
c from Donn at BSDI
e
s 00002/00003/00579
d D 5.10 92/12/02 09:06:04 bostic 11 10
c branch should succeed if any substitution has succeeded, not just the
c last one; from Diomidis Spinellis <dds@doc.ic.ac.uk>
e
s 00001/00003/00581
d D 5.9 92/11/01 12:46:11 bostic 10 9
c unneeded set
e
s 00004/00004/00580
d D 5.8 92/08/30 12:07:10 bostic 9 8
c don't access entries multiple times; from Diomidis
e
s 00002/00002/00582
d D 5.7 92/08/29 15:56:03 bostic 8 7
c re_off is a size_t, cspace is an external function
e
s 00055/00087/00529
d D 5.6 92/08/28 15:32:09 bostic 7 6
c MUST copy data from stdio buffer, change interface to mf_fgets;
c this simplifies the interface to cspace, so clean that up, too;
c make match (pmatch) a single global structure, cleaning up regexec_e();
c fix default RE calculation for re_nsub > maxbref; fix default RE bugs
e
s 00000/00002/00616
d D 5.5 92/08/27 22:45:03 bostic 6 4
c let's not be tricky...
e
s 00002/00002/00616
d R 5.5 92/08/27 14:01:12 bostic 5 4
c fix the process linkages, but was that fd's got closed more than
c once, Diomidis says there were other bad effects as well.
e
s 00002/00000/00616
d D 5.4 92/08/27 12:52:43 bostic 4 3
c don't close fd's twice.
e
s 00050/00053/00566
d D 5.3 92/08/24 21:27:39 bostic 3 2
c make empty RE's work, some minor cleanups, too
e
s 00004/00006/00615
d D 5.2 92/08/24 12:06:02 bostic 2 1
c fix the 'd' and 'D' flags for the new "pd" variable
e
s 00621/00000/00000
d D 5.1 92/08/23 18:26:16 bostic 1 0
c date and time created 92/08/23 18:26:16 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Diomidis Spinellis.
D 18
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
D 20
 * Copyright (c) 1992, 1993
E 20
I 20
 * Copyright (c) 1992, 1993, 1994
E 20
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis of Imperial College, University of London.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/uio.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "extern.h"

D 7
typedef struct {
	char *space;		/* Current space pointer. */
	size_t len;		/* Current length. */
	int deleted;		/* If deleted. */
	char *back;		/* Backing memory. */
	size_t blen;		/* Backing memory length. */
} SPACE;
E 7
static SPACE HS, PS, SS;
#define	pd		PS.deleted
#define	ps		PS.space
#define	psl		PS.len
#define	hs		HS.space
#define	hsl		HS.len

static inline int	 applies __P((struct s_command *));
D 7
static void		 cspace __P((SPACE *, char *, size_t, int));
E 7
I 7
D 8
static void		 cspace __P((SPACE *, char *, size_t, enum e_spflag));
E 8
E 7
static void		 flush_appends __P((void));
static void		 lputs __P((char *));
D 3
static inline int	 match __P((struct s_addr *));
static int		 regexec_check __P((regex_t *, const char *,
			    int, regmatch_t[], int));
E 3
I 3
D 7
static inline int	 regexec_e __P((regex_t *, const char *,
			    size_t, regmatch_t [], int));
E 3
static void		 regsub __P((regmatch_t *, char *, char *, SPACE *));
E 7
I 7
D 14
static inline int	 regexec_e __P((regex_t *, const char *, int, int));
E 14
I 14
static inline int	 regexec_e __P((regex_t *, const char *, int, int, size_t));
E 14
static void		 regsub __P((SPACE *, char *, char *));
E 7
static int		 substitute __P((struct s_command *));

struct s_appends *appends;	/* Array of pointers to strings to append. */
static int appendx;		/* Index into appends array. */
int appendnum;			/* Size of appends array. */

static int lastaddr;		/* Set by applies if last address of a range. */
static int sdone;		/* If any substitutes since last line input. */
				/* Iov structure for 'w' commands. */
D 15
static struct iovec iov[2] = { NULL, 0, "\n", 1 };

E 15
I 3
static regex_t *defpreg;
D 7
static size_t defnmatch;
E 7
I 7
size_t maxnsub;
D 14
regmatch_t *match;
E 14
I 14
D 15
regmatch_t *match, startend;
E 15
I 15
regmatch_t *match;
E 15
E 14
E 7

I 14
D 15
#define OUT(s) { fwrite(s, sizeof(u_char), psl, stdout); putchar('\n'); }
E 15
I 15
#define OUT(s) { fwrite(s, sizeof(u_char), psl, stdout); }
E 15

E 14
E 3
void
process()
{
	struct s_command *cp;
	SPACE tspace;
	size_t len;
I 7
D 23
	int r;
E 23
E 7
	char oldc, *p;

D 7
	for (linenum = 0; ps = mf_fgets(&psl);) {
E 7
I 7
	for (linenum = 0; mf_fgets(&PS, REPLACE);) {
E 7
		pd = 0;
		cp = prog;
redirect:
		while (cp != NULL) {
			if (!applies(cp)) {
				cp = cp->next;
				continue;
			}
			switch (cp->code) {
			case '{':
				cp = cp->u.c;
				goto redirect;
			case 'a':
				if (appendx >= appendnum)
					appends = xrealloc(appends,
					    sizeof(struct s_appends) *
					    (appendnum *= 2));
				appends[appendx].type = AP_STRING;
				appends[appendx].s = cp->t;
I 14
				appends[appendx].len = strlen(cp->t);
E 14
				appendx++;
				break;
			case 'b':
				cp = cp->u.c;
				goto redirect;
			case 'c':
				pd = 1;
				psl = 0;
				if (cp->a2 == NULL || lastaddr)
					(void)printf("%s", cp->t);
				break;
			case 'd':
D 6
				if (pd)
					goto new;
E 6
D 2
				psl = 0;
				ps[0] = '\0';
E 2
I 2
				pd = 1;
E 2
				goto new;
			case 'D':
				if (pd)
					goto new;
D 2
				if ((p = strchr(ps, '\n')) == NULL) {
					psl = 0;
					ps[0] = '\0';
				} else {
E 2
I 2
D 14
				if ((p = strchr(ps, '\n')) == NULL)
E 14
I 14
D 17
				if ((p = strnchr(ps, '\n', psl)) == NULL)
E 17
I 17
				if ((p = memchr(ps, '\n', psl)) == NULL)
E 17
E 14
					pd = 1;
				else {
E 2
D 21
					psl -= (p - ps) - 1;
E 21
I 21
					psl -= (p - ps) + 1;
E 21
					memmove(ps, p + 1, psl);
				}
				goto new;
			case 'g':
D 7
				ps = hs;
				psl = hsl;
E 7
I 7
				cspace(&PS, hs, hsl, REPLACE);
E 7
				break;
			case 'G':
D 7
				cspace(&PS, hs, hsl, 1);
E 7
I 7
D 15
				cspace(&PS, hs, hsl, APPENDNL);
E 15
I 15
				cspace(&PS, hs, hsl, 0);
E 15
E 7
				break;
			case 'h':
D 7
				cspace(&HS, ps, psl, 0);
E 7
I 7
				cspace(&HS, ps, psl, REPLACE);
E 7
				break;
			case 'H':
D 7
				cspace(&HS, ps, psl, 1);
E 7
I 7
D 15
				cspace(&HS, ps, psl, APPENDNL);
E 15
I 15
				cspace(&HS, ps, psl, 0);
E 15
E 7
				break;
			case 'i':
				(void)printf("%s", cp->t);
				break;
			case 'l':
				lputs(ps);
				break;
			case 'n':
				if (!nflag && !pd)
D 14
					(void)printf("%s\n", ps);
E 14
I 14
					OUT(ps)
E 14
				flush_appends();
D 7
				ps = mf_fgets(&psl);
E 7
I 7
D 23
				r = mf_fgets(&PS, REPLACE);
E 7
#ifdef HISTORIC_PRACTICE
D 7
				if (ps == NULL)
E 7
I 7
				if (!r)
E 23
I 23
				if (!mf_fgets(&PS, REPLACE))
E 23
E 7
					exit(0);
D 23
#endif
E 23
				pd = 0;
				break;
			case 'N':
				flush_appends();
D 7
				if (ps != PS.back)
					cspace(&PS, NULL, 0, 0);
				if ((p = mf_fgets(&len)) == NULL) {
E 7
I 7
D 15
				if (!mf_fgets(&PS, APPENDNL)) {
E 15
I 15
				if (!mf_fgets(&PS, 0)) {
E 15
E 7
					if (!nflag && !pd)
D 14
						(void)printf("%s\n", ps);
E 14
I 14
						OUT(ps)
E 14
					exit(0);
				}
D 7
				cspace(&PS, p, len, 1);
E 7
				break;
			case 'p':
				if (pd)
					break;
D 14
				(void)printf("%s\n", ps);
E 14
I 14
				OUT(ps)
E 14
				break;
			case 'P':
				if (pd)
					break;
D 14
				if ((p = strchr(ps, '\n')) != NULL) {
E 14
I 14
D 17
				if ((p = strnchr(ps, '\n', psl)) != NULL) {
E 17
I 17
				if ((p = memchr(ps, '\n', psl)) != NULL) {
E 17
E 14
					oldc = *p;
					*p = '\0';
				}
D 14
				(void)printf("%s\n", ps);
E 14
I 14
				OUT(ps)
E 14
				if (p != NULL)
					*p = oldc;
				break;
			case 'q':
				if (!nflag && !pd)
D 14
					(void)printf("%s\n", ps);
E 14
I 14
					OUT(ps)
E 14
				flush_appends();
				exit(0);
			case 'r':
				if (appendx >= appendnum)
					appends = xrealloc(appends,
					    sizeof(struct s_appends) *
					    (appendnum *= 2));
				appends[appendx].type = AP_FILE;
				appends[appendx].s = cp->t;
I 14
				appends[appendx].len = strlen(cp->t);
E 14
				appendx++;
				break;
			case 's':
D 11
				sdone = substitute(cp);
E 11
I 11
				sdone |= substitute(cp);
E 11
				break;
			case 't':
				if (sdone) {
					sdone = 0;
					cp = cp->u.c;
					goto redirect;
				}
				break;
			case 'w':
				if (pd)
					break;
				if (cp->u.fd == -1 && (cp->u.fd = open(cp->t,
				    O_WRONLY|O_APPEND|O_CREAT|O_TRUNC,
				    DEFFILEMODE)) == -1)
					err(FATAL, "%s: %s\n",
					    cp->t, strerror(errno));
D 15
				iov[0].iov_base = ps;
				iov[0].iov_len = psl;
				if (writev(cp->u.fd, iov, 2) != psl + 1)
E 15
I 15
				if (write(cp->u.fd, ps, psl) != psl)
E 15
					err(FATAL, "%s: %s\n",
					    cp->t, strerror(errno));
				break;
			case 'x':
I 12
				if (hs == NULL)
					cspace(&HS, "", 0, REPLACE);
E 12
				tspace = PS;
				PS = HS;
				HS = tspace;
				break;
			case 'y':
				if (pd)
					break;
D 15
				for (p = ps, len = psl; len--; ++p)
E 15
I 15
				for (p = ps, len = psl; --len; ++p)
E 15
					*p = cp->u.y[*p];
				break;
			case ':':
			case '}':
				break;
			case '=':
				(void)printf("%lu\n", linenum);
			}
			cp = cp->next;
		} /* for all cp */

new:		if (!nflag && !pd)
D 14
			(void)printf("%s\n", ps);
E 14
I 14
			OUT(ps)
E 14
		flush_appends();
	} /* for all lines */
}

/*
I 3
 * TRUE if the address passed matches the current program state
 * (lastline, linenumber, ps).
 */
D 14
#define	MATCH(a)							\
D 7
	(a)->type == AT_RE ?						\
	    regexec_e((a)->u.r, ps, 0, NULL, 0) :			\
E 7
I 7
	(a)->type == AT_RE ? regexec_e((a)->u.r, ps, 0, 1) :		\
E 14
I 14
#define	MATCH(a)						\
	(a)->type == AT_RE ? regexec_e((a)->u.r, ps, 0, 1, psl) :	\
E 14
E 7
	    (a)->type == AT_LINE ? linenum == (a)->u.l : lastline

/*
E 3
 * Return TRUE if the command applies to the current line.  Sets the inrange
 * flag to process ranges.  Interprets the non-select (``!'') flag.
 */
static inline int
applies(cp)
	struct s_command *cp;
{
	int r;

	lastaddr = 0;
	if (cp->a1 == NULL && cp->a2 == NULL)
		r = 1;
	else if (cp->a2)
		if (cp->inrange) {
D 3
			if (match(cp->a2)) {
E 3
I 3
			if (MATCH(cp->a2)) {
E 3
				cp->inrange = 0;
				lastaddr = 1;
			}
			r = 1;
D 3
		} else if (match(cp->a1)) {
E 3
I 3
		} else if (MATCH(cp->a1)) {
E 3
			/*
			 * If the second address is a number less than or
			 * equal to the line number first selected, only
			 * one line shall be selected.
			 *	-- POSIX 1003.2
			 */
			if (cp->a2->type == AT_LINE &&
			    linenum >= cp->a2->u.l)
				lastaddr = 1;
			else
				cp->inrange = 1;
			r = 1;
		} else
			r = 0;
	else
D 3
		r = match(cp->a1);
E 3
I 3
		r = MATCH(cp->a1);
E 3
	return (cp->nonsel ? ! r : r);
}

/*
D 3
 * Return TRUE if the address passed matches the current program
 * state (linenumber, ps, lastline)
 */
static int inline
match(a)
	struct s_addr *a;
{
	int eval;

	switch (a->type) {
	case AT_RE:
		switch (eval = regexec(a->u.r, ps, 0, NULL, 0)) {
		case 0:
			return (1);
		case REG_NOMATCH:
			return (0);
		default:
			err(FATAL, "RE error: %s", strregerror(eval, a->u.r));
		}
	case AT_LINE:
		return (linenum == a->u.l);
	case AT_LAST:
		return (lastline);
	}
	/* NOTREACHED */
}

/*
E 3
 * substitute --
 *	Do substitutions in the pattern space.  Currently, we build a
 *	copy of the new pattern space in the substitute space structure
 *	and then swap them.
 */
static int
substitute(cp)
	struct s_command *cp;
{
	SPACE tspace;
D 3
	static regex_t *re;
E 3
I 3
	regex_t *re;
D 7
	size_t nsub;
E 7
E 3
D 8
	int n, re_off;
E 8
I 8
D 14
	size_t re_off;
E 14
I 14
	size_t re_off, slen;
E 14
D 22
	int n;
E 22
I 22
	int lastempty, n;
E 22
E 8
D 10
	char *endp, *s;
E 10
I 10
	char *s;
E 10

	s = ps;
D 3
	re = &cp->u.s->re;
	if (regexec_check(re,
	    s, re->re_nsub + 1, cp->u.s->pmatch, 0) == REG_NOMATCH)
E 3
I 3
	re = cp->u.s->re;
	if (re == NULL) {
D 7
		nsub = 1;
		if (defpreg != NULL && cp->u.s->maxbref > defnmatch) {
E 7
I 7
		if (defpreg != NULL && cp->u.s->maxbref > defpreg->re_nsub) {
E 7
			linenum = cp->u.s->linenum;
			err(COMPILE, "\\%d not defined in the RE",
			    cp->u.s->maxbref);
		}
D 7
	} else
		nsub = re->re_nsub + 1;
	if (!regexec_e(re, s, nsub, cp->u.s->pmatch, 0))
E 7
I 7
	}
D 14
	if (!regexec_e(re, s, 0, 0))
E 14
I 14
	if (!regexec_e(re, s, 0, 0, psl))
E 14
E 7
E 3
		return (0);

D 22
	SS.len = 0;				/* Clean substitute space. */
I 14
	slen = psl;
E 14
	n = cp->u.s->n;
	switch (n) {
	case 0:					/* Global */
		do {
			/* Locate start of replaced string. */
D 7
			re_off = cp->u.s->pmatch[0].rm_so;
E 7
I 7
			re_off = match[0].rm_so;
E 7
D 10
			/* Locate end of replaced string + 1. */
D 7
			endp = s + cp->u.s->pmatch[0].rm_eo;
E 7
I 7
			endp = s + match[0].rm_eo;
E 10
E 7
			/* Copy leading retained string. */
D 7
			cspace(&SS, s, re_off, 0);
E 7
I 7
			cspace(&SS, s, re_off, APPEND);
E 7
			/* Add in regular expression. */
D 7
			regsub(cp->u.s->pmatch, s, cp->u.s->new, &SS);
E 7
I 7
			regsub(&SS, s, cp->u.s->new);
E 7
			/* Move past this match. */
D 7
			s += cp->u.s->pmatch[0].rm_eo;
D 3
		} while(regexec_check(re, s, re->re_nsub + 1,
		    cp->u.s->pmatch, REG_NOTBOL) != REG_NOMATCH);
E 3
I 3
		} while(regexec_e(re, s, nsub, cp->u.s->pmatch, REG_NOTBOL));
E 7
I 7
			s += match[0].rm_eo;
D 14
		} while(regexec_e(re, s, REG_NOTBOL, 0));
E 14
I 14
			slen -= match[0].rm_eo;
D 19
		} while(regexec_e(re, s, REG_NOTBOL, 0, slen));
E 19
I 19
		} while(match[0].rm_so != match[0].rm_eo &&
		    regexec_e(re, s, REG_NOTBOL, 0, slen));
E 22
I 22
  	SS.len = 0;				/* Clean substitute space. */
  	slen = psl;
  	n = cp->u.s->n;
	lastempty = 1;
E 22

I 22
  	switch (n) {
  	case 0:					/* Global */
  		do {
			if (lastempty || match[0].rm_so != match[0].rm_eo) {
				/* Locate start of replaced string. */
				re_off = match[0].rm_so;
				/* Copy leading retained string. */
				cspace(&SS, s, re_off, APPEND);
				/* Add in regular expression. */
				regsub(&SS, s, cp->u.s->new);
			}

  			/* Move past this match. */
			if (match[0].rm_so != match[0].rm_eo) {
				s += match[0].rm_eo;
				slen -= match[0].rm_eo;
				lastempty = 0;
			} else {
				if (match[0].rm_so == 0)
					cspace(&SS,
					    s, match[0].rm_so + 1, APPEND);
				else
					cspace(&SS,
					    s + match[0].rm_so, 1, APPEND);
				s += match[0].rm_so + 1;
				slen -= match[0].rm_so + 1;
				lastempty = 1;
			}
		} while (slen > 0 && regexec_e(re, s, REG_NOTBOL, 0, slen));
E 22
E 19
E 14
E 7
E 3
		/* Copy trailing retained string. */
D 7
		cspace(&SS, s, strlen(s), 0);
E 7
I 7
D 14
		cspace(&SS, s, strlen(s), APPEND);
E 14
I 14
D 22
		cspace(&SS, s, slen, APPEND);
E 14
E 7
		break;
E 22
I 22
		if (slen > 0)
			cspace(&SS, s, slen, APPEND);
  		break;
E 22
	default:				/* Nth occurrence */
		while (--n) {
D 7
			s += cp->u.s->pmatch[0].rm_eo;
D 3
			if (regexec_check(re, s, re->re_nsub + 1,
			    cp->u.s->pmatch, REG_NOTBOL) == REG_NOMATCH)
E 3
I 3
			if (!regexec_e(re,
			    s, nsub, cp->u.s->pmatch, REG_NOTBOL))
E 7
I 7
			s += match[0].rm_eo;
D 14
			if (!regexec_e(re, s, REG_NOTBOL, 0))
E 14
I 14
			slen -= match[0].rm_eo;
			if (!regexec_e(re, s, REG_NOTBOL, 0, slen))
E 14
E 7
E 3
				return (0);
		}
		/* FALLTHROUGH */
	case 1:					/* 1st occurrence */
		/* Locate start of replaced string. */
D 7
		re_off = cp->u.s->pmatch[0].rm_so + s - ps;
E 7
I 7
		re_off = match[0].rm_so + (s - ps);
E 7
		/* Copy leading retained string. */
D 7
		cspace(&SS, ps, re_off, 0);
E 7
I 7
		cspace(&SS, ps, re_off, APPEND);
E 7
		/* Add in regular expression. */
D 7
		regsub(cp->u.s->pmatch, s, cp->u.s->new, &SS);
E 7
I 7
		regsub(&SS, s, cp->u.s->new);
E 7
		/* Copy trailing retained string. */
D 7
		s += cp->u.s->pmatch[0].rm_eo;
		cspace(&SS, s, strlen(s), 0);
E 7
I 7
		s += match[0].rm_eo;
D 14
		cspace(&SS, s, strlen(s), APPEND);
E 14
I 14
		slen -= match[0].rm_eo;
		cspace(&SS, s, slen, APPEND);
E 14
E 7
		break;
	}

	/*
	 * Swap the substitute space and the pattern space, and make sure
	 * that any leftover pointers into stdio memory get lost.
	 */
	tspace = PS;
	PS = SS;
	SS = tspace;
	SS.space = SS.back;

	/* Handle the 'p' flag. */
	if (cp->u.s->p)
D 14
		(void)printf("%s\n", ps);
E 14
I 14
		OUT(ps)
E 14

	/* Handle the 'w' flag. */
	if (cp->u.s->wfile && !pd) {
		if (cp->u.s->wfd == -1 && (cp->u.s->wfd = open(cp->u.s->wfile,
		    O_WRONLY|O_APPEND|O_CREAT|O_TRUNC, DEFFILEMODE)) == -1)
			err(FATAL, "%s: %s\n", cp->u.s->wfile, strerror(errno));
D 15
		iov[0].iov_base = ps;
		iov[0].iov_len = psl;	
		if (writev(cp->u.s->wfd, iov, 2) != psl + 1)
E 15
I 15
		if (write(cp->u.s->wfd, ps, psl) != psl)
E 15
			err(FATAL, "%s: %s\n", cp->u.s->wfile, strerror(errno));
	}
	return (1);
}

/*
 * Flush append requests.  Always called before reading a line,
 * therefore it also resets the substitution done (sdone) flag.
 */
static void
flush_appends()
{
	FILE *f;
	int count, i;
	char buf[8 * 1024];

	for (i = 0; i < appendx; i++) 
		switch (appends[i].type) {
		case AP_STRING:
D 14
			(void)printf("%s", appends[i].s);
E 14
I 14
			fwrite(appends[i].s, sizeof(char), appends[i].len, 
			    stdout);
E 14
			break;
		case AP_FILE:
			/*
			 * Read files probably shouldn't be cached.  Since
			 * it's not an error to read a non-existent file,
			 * it's possible that another program is interacting
			 * with the sed script through the file system.  It
			 * would be truly bizarre, but possible.  It's probably
			 * not that big a performance win, anyhow.
			 */
			if ((f = fopen(appends[i].s, "r")) == NULL)
				break;
D 14
			while (count = fread(buf, 1, sizeof(buf), f))
				(void)fwrite(buf, 1, count, stdout);
E 14
I 14
D 15
			while (count = fread(buf, sizeof(char), sizeof(buf), 
			    f))
E 15
I 15
			while (count = fread(buf, sizeof(char), sizeof(buf), f))
E 15
				(void)fwrite(buf, sizeof(char), count, stdout);
E 14
			(void)fclose(f);
			break;
		}
	if (ferror(stdout))
		err(FATAL, "stdout: %s", strerror(errno ? errno : EIO));
D 11
	appendx = 0;
	sdone = 0;
E 11
I 11
	appendx = sdone = 0;
E 11
}

static void
lputs(s)
	register char *s;
{
	register int count;
	register char *escapes, *p;
	struct winsize win;
	static int termwidth = -1;

	if (termwidth == -1)
		if (p = getenv("COLUMNS"))
			termwidth = atoi(p);
		else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == 0 &&
		    win.ws_col > 0)
			termwidth = win.ws_col;
		else
			termwidth = 60;

	for (count = 0; *s; ++s) { 
		if (count >= termwidth) {
			(void)printf("\\\n");
			count = 0;
		}
		if (isascii(*s) && isprint(*s) && *s != '\\') {
			(void)putchar(*s);
			count++;
		} else {
			escapes = "\\\a\b\f\n\r\t\v";
			(void)putchar('\\');
			if (p = strchr(escapes, *s)) {
				(void)putchar("\\abfnrtv"[p - escapes]);
				count += 2;
			} else {
D 15
				(void)printf("%03o", (u_char)*s);
E 15
I 15
				(void)printf("%03o", *(u_char *)s);
E 15
				count += 4;
			}
		}
	}
	(void)putchar('$');
	(void)putchar('\n');
	if (ferror(stdout))
		err(FATAL, "stdout: %s", strerror(errno ? errno : EIO));
}

D 3
/*
 * Regexec with checking for errors
 */
static int
regexec_check(preg, string, nmatch, pmatch, eflags)
E 3
I 3
static inline int
D 7
regexec_e(preg, string, nmatch, pmatch, eflags)
E 7
I 7
D 14
regexec_e(preg, string, eflags, nomatch)
E 14
I 14
regexec_e(preg, string, eflags, nomatch, slen)
E 14
E 7
E 3
	regex_t *preg;
	const char *string;
D 3
	int nmatch;
E 3
I 3
D 7
	size_t nmatch;
E 3
	regmatch_t pmatch[];
	int eflags;
E 7
I 7
	int eflags, nomatch;
I 14
	size_t slen;
E 14
E 7
{
	int eval;
I 14
	
D 15
	/* So we can work with binary files */
	startend.rm_so = 0;
	startend.rm_eo = slen;
	match[0] = startend;
	
E 14

I 14
	eflags |= REG_STARTEND;	
	
E 15
E 14
D 3
	switch (eval = regexec(preg, string, nmatch, pmatch, eflags)) {
E 3
I 3
	if (preg == NULL) {
		if (defpreg == NULL)
			err(FATAL, "first RE may not be empty");
D 7
	} else {
E 7
I 7
	} else
E 7
		defpreg = preg;
D 7
		defnmatch = nmatch;
	}
E 7

I 16
	/* Set anchors, discounting trailing newline (if any). */
	if (slen > 0 && string[slen - 1] == '\n')
		slen--;
E 16
I 15
	match[0].rm_so = 0;
D 16
	match[0].rm_eo = slen - 1;	/* Length minus trailing newline. */
E 16
I 16
	match[0].rm_eo = slen;
E 16
	
E 15
D 7
	eval = regexec(defpreg,
	    string, pmatch == NULL ? 0 : defnmatch, pmatch, eflags);
E 7
I 7
	eval = regexec(defpreg, string,
D 15
	    nomatch ? 0 : maxnsub + 1, match, eflags);
E 15
I 15
	    nomatch ? 0 : maxnsub + 1, match, eflags | REG_STARTEND);
E 15
E 7
	switch(eval) {
E 3
	case 0:
D 3
		return (0);
E 3
I 3
		return (1);
E 3
	case REG_NOMATCH:
D 3
		return (REG_NOMATCH);
	default:
		err(FATAL, "RE error: %s", strregerror(eval, preg));
E 3
I 3
		return (0);
E 3
	}
I 3
	err(FATAL, "RE error: %s", strregerror(eval, defpreg));
E 3
	/* NOTREACHED */
}

/*
 * regsub - perform substitutions after a regexp match
 * Based on a routine by Henry Spencer
 */
static void
D 7
regsub(pmatch, string, src, sp)
	regmatch_t *pmatch;
	char *string, *src;
E 7
I 7
regsub(sp, string, src)
E 7
	SPACE *sp;
I 7
	char *string, *src;
E 7
{
	register int len, no;
	register char c, *dst;

#define	NEEDSP(reqlen)							\
	if (sp->len >= sp->blen - (reqlen) - 1) {			\
		sp->blen += (reqlen) + 1024;				\
		sp->space = sp->back = xrealloc(sp->back, sp->blen);	\
		dst = sp->space + sp->len;				\
	}

	dst = sp->space + sp->len;
	while ((c = *src++) != '\0') {
		if (c == '&')
			no = 0;
		else if (c == '\\' && isdigit(*src))
			no = *src++ - '0';
		else
			no = -1;
		if (no < 0) {		/* Ordinary character. */
 			if (c == '\\' && (*src == '\\' || *src == '&'))
 				c = *src++;
			NEEDSP(1);
 			*dst++ = c;
			++sp->len;
D 7
 		} else if (pmatch[no].rm_so != -1 && pmatch[no].rm_eo != -1) {
			len = pmatch[no].rm_eo - pmatch[no].rm_so;
E 7
I 7
 		} else if (match[no].rm_so != -1 && match[no].rm_eo != -1) {
			len = match[no].rm_eo - match[no].rm_so;
E 7
			NEEDSP(len);
D 7
			memmove(dst, string + pmatch[no].rm_so, len);
E 7
I 7
			memmove(dst, string + match[no].rm_so, len);
E 7
			dst += len;
			sp->len += len;
		}
	}
	NEEDSP(1);
	*dst = '\0';
}

/*
 * aspace --
 *	Append the source space to the destination space, allocating new
 *	space as necessary.
 */
D 7
static void
cspace(sp, p, len, append)
E 7
I 7
void
cspace(sp, p, len, spflag)
E 7
	SPACE *sp;
	char *p;
	size_t len;
D 7
	int append;
E 7
I 7
	enum e_spflag spflag;
E 7
{
	size_t tlen;
D 7
	int needcopy;
E 7

D 7
	/* Current pointer may point to something else at the moment. */
	needcopy = sp->space != sp->back;

E 7
D 15
	/*
D 7
	 * Make sure SPACE has enough memory and ramp up quickly.
	 * Add in two extra bytes, one for the newline, one for a
	 * terminating NULL.
E 7
I 7
	 * Make sure SPACE has enough memory and ramp up quickly.  Appends
	 * need two extra bytes, one for the newline, one for a terminating
	 * NULL.
E 7
	 */
D 7
	tlen = sp->len + len + 2;
E 7
I 7
D 13
	tlen = sp->len + len + spflag == APPENDNL ? 2 : 1;
E 13
I 13
	tlen = sp->len + len + (spflag == APPENDNL ? 2 : 1);
E 15
I 15
	/* Make sure SPACE has enough memory and ramp up quickly. */
	tlen = sp->len + len + 1;
E 15
E 13
E 7
	if (tlen > sp->blen) {
		sp->blen = tlen + 1024;
D 7
		sp->back = xrealloc(sp->back, sp->blen);
E 7
I 7
		sp->space = sp->back = xrealloc(sp->back, sp->blen);
E 7
	}

D 7
	if (needcopy)
		memmove(sp->back, sp->space, sp->len + 1);
	sp->space = sp->back;

	/* May just be copying out of a stdio buffer. */
	if (len == NULL)
		return;

	/* Append a separating newline. */
	if (append)
E 7
I 7
D 15
	if (spflag == APPENDNL)
E 7
		sp->space[sp->len++] = '\n';
I 7
	else if (spflag == REPLACE)
E 15
I 15
	if (spflag == REPLACE)
E 15
		sp->len = 0;
E 7

D 7
	/* Append the new stuff, plus its terminating NULL. */
	memmove(sp->space + sp->len, p, len + 1);
	sp->len += len;
E 7
I 7
	memmove(sp->space + sp->len, p, len);
I 14

E 14
	sp->space[sp->len += len] = '\0';
E 7
}

/*
 * Close all cached opened files and report any errors
 */
void
D 9
cfclose(cp)
	register struct s_command *cp;
E 9
I 9
cfclose(cp, end)
	register struct s_command *cp, *end;
E 9
{

D 9
	for (; cp != NULL; cp = cp->next)
E 9
I 9
	for (; cp != end; cp = cp->next)
E 9
		switch(cp->code) {
		case 's':
			if (cp->u.s->wfd != -1 && close(cp->u.s->wfd))
				err(FATAL,
				    "%s: %s", cp->u.s->wfile, strerror(errno));
I 4
			cp->u.s->wfd = -1;
E 4
			break;
		case 'w':
			if (cp->u.fd != -1 && close(cp->u.fd))
				err(FATAL, "%s: %s", cp->t, strerror(errno));
I 4
			cp->u.fd = -1;
E 4
			break;
		case '{':
D 9
			cfclose(cp->u.c);
E 9
I 9
			cfclose(cp->u.c, cp->next);
E 9
			break;
		}
}
E 1
