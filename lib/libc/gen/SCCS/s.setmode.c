h33616
s 00041/00040/00386
d D 8.2 94/03/25 14:16:25 bostic 13 12
c only clear bits specified in perm, or, if setting as well, clear all in group.
c deal with "g=" vs. "g=u" bogon.  update commands if:
c 	(1) perm set and we get a 'permcopy'
c 	(2) perm set and nothing left to do
c 	(3) nothing left to do and we've there's an 'outstanding ='
c fix umask handling for '-' when 'who' is unset.
c condense code for '='.
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00002/00002/00424
d D 8.1 93/06/04 12:05:05 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00418
d D 5.11 92/04/07 08:49:39 bostic 11 10
c block all the signals that can be blocked while the umask is modified
e
s 00001/00000/00418
d D 5.10 92/03/16 14:15:52 bostic 10 9
c NULL not defined w/o stdio.h
e
s 00000/00001/00418
d D 5.9 92/03/16 14:14:01 bostic 9 8
c forgot to turn off debug
e
s 00005/00002/00414
d D 5.8 92/03/02 16:45:11 bostic 8 7
c make = of no permissions (ex: "g=") work
e
s 00095/00093/00321
d D 5.7 92/03/02 16:17:43 bostic 7 6
c KNF; only real change was to pass u_int instead of mode_t around,
c make the promotion explicit.  Shouldn't cause any problems, though.
e
s 00001/00000/00413
d D 5.6 91/05/27 16:24:56 bostic 6 5
c use the isdigit() macro...
e
s 00008/00005/00405
d D 5.5 91/02/23 11:02:52 bostic 5 4
c blackbox the token passed between getmode and setmode via the application
e
s 00309/00085/00101
d D 5.4 91/01/09 16:56:52 bostic 4 3
c update from Dave Borman; make "u=g" work.
e
s 00001/00011/00185
d D 5.3 90/06/01 14:15:03 bostic 3 2
c new copyright notice
e
s 00022/00010/00174
d D 5.2 90/05/10 21:18:29 bostic 2 1
c allow multiple callers
e
s 00191/00000/00000
d D 5.1 90/02/01 21:44:13 bostic 1 0
c date and time created 90/02/01 21:44:13 by bostic
e
u
U
t
T
I 1
/*
D 12
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
D 13
 * Copyright (c) 1989, 1993
E 13
I 13
 * Copyright (c) 1989, 1993, 1994
E 13
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
I 8
 * This code is derived from software contributed to Berkeley by
 * Dave Borman at Cray Research, Inc.
 *
E 8
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 4
#include <sys/types.h>
E 4
I 4
D 7
#include <sys/param.h>
E 7
I 7
#include <sys/types.h>
E 7
E 4
#include <sys/stat.h>
I 11
D 13
#include <signal.h>
E 13
I 13

#include <ctype.h>
E 13
E 11
I 2
D 4
#include <errno.h>
E 4
I 4
D 7
#include <sys/errno.h>
E 7
I 7
#include <errno.h>
I 13
#include <signal.h>
E 13
I 10
#include <stddef.h>
I 13
#include <stdlib.h>

E 13
E 10
D 9
#define SETMODE_DEBUG
E 9
E 7
#ifdef SETMODE_DEBUG
E 4
#include <stdio.h>
I 4
#endif
D 13
#include <stdlib.h>
I 6
#include <ctype.h>
E 13
E 6
E 4
E 2

D 2
static mode_t setbits, clrbits, Xbits;
E 2
I 2
D 4
#define	setbits	set[0]
#define	clrbits	set[1]
#define	Xbits	set[2]
E 4
I 4
#define	SET_LEN	6		/* initial # of bitcmd struct to malloc */
#define	SET_LEN_INCR 4		/* # of bitcmd structs to add as needed */
E 4
E 2

I 4
D 7
struct bitcmd {
E 7
I 7
typedef struct bitcmd {
E 7
	char	cmd;
	char	cmd2;
	mode_t	bits;
D 7
};
E 7
I 7
} BITCMD;
E 7

#define	CMD2_CLR	0x01
#define	CMD2_SET	0x02
#define	CMD2_GBITS	0x04
#define	CMD2_OBITS	0x08
#define	CMD2_UBITS	0x10

I 7
static BITCMD	*addcmd __P((BITCMD *, int, int, int, u_int));
static int	 compress_mode __P((BITCMD *));
#ifdef SETMODE_DEBUG
static void	 dumpmode __P((BITCMD *));
#endif

E 7
/*
 * Given the old mode and an array of bitcmd structures, apply the operations
 * described in the bitcmd structures to the old mode, and return the new mode.
 * Note that there is no '=' command; a strict assignment is just a '-' (clear
 * bits) followed by a '+' (set bits).
 */
E 4
mode_t
D 2
getmode(omode)
	mode_t omode;
E 2
I 2
D 5
getmode(set, omode)
D 4
	mode_t *set, omode;
E 4
I 4
	register struct bitcmd *set;
E 5
I 5
getmode(bbox, omode)
	void *bbox;
E 5
	mode_t omode;
E 4
E 2
{
I 5
D 7
	register struct bitcmd *set;
E 7
I 7
	register BITCMD *set;
E 7
E 5
D 4
	register mode_t newmode;
E 4
I 4
D 13
	register mode_t newmode, value;
E 13
I 13
	register mode_t clrval, newmode, value;
E 13
E 4

I 5
D 7
	set = (struct bitcmd *)bbox;
E 7
I 7
	set = (BITCMD *)bbox;
E 7
E 5
D 4
	newmode = omode & clrbits;
	newmode |= setbits;
	if (omode & (S_IFDIR|S_IXUSR|S_IXGRP|S_IXOTH))
		newmode |= Xbits;
	return(newmode);
E 4
I 4
	newmode = omode;
	for (value = 0;; set++)
		switch(set->cmd) {
		/*
		 * When copying the user, group or other bits around, we "know"
D 7
		 * where the bit are in the mode so that we can do shifts to
E 7
I 7
		 * where the bits are in the mode so that we can do shifts to
E 7
		 * copy them around.  If we don't use shifts, it gets real
		 * grundgy with lots of single bit checks and bit sets.
		 */
		case 'u':
			value = (newmode & S_IRWXU) >> 6;
			goto common;

		case 'g':
			value = (newmode & S_IRWXG) >> 3;
			goto common;

		case 'o':
			value = newmode & S_IRWXO;
D 7
		common:
			if (set->cmd2 & CMD2_CLR) {
E 7
I 7
common:			if (set->cmd2 & CMD2_CLR) {
I 13
				clrval =
				    (set->cmd2 & CMD2_SET) ?  S_IRWXO : value;
E 13
E 7
				if (set->cmd2 & CMD2_UBITS)
D 13
					newmode &= ~(S_IRWXU & set->bits);
E 13
I 13
					newmode &= ~((clrval<<6) & set->bits);
E 13
				if (set->cmd2 & CMD2_GBITS)
D 13
					newmode &= ~(S_IRWXG & set->bits);
E 13
I 13
					newmode &= ~((clrval<<3) & set->bits);
E 13
				if (set->cmd2 & CMD2_OBITS)
D 13
					newmode &= ~(S_IRWXO & set->bits);
E 13
I 13
					newmode &= ~(clrval & set->bits);
E 13
			}
			if (set->cmd2 & CMD2_SET) {
				if (set->cmd2 & CMD2_UBITS)
					newmode |= (value<<6) & set->bits;
				if (set->cmd2 & CMD2_GBITS)
					newmode |= (value<<3) & set->bits;
				if (set->cmd2 & CMD2_OBITS)
					newmode |= value & set->bits;
			}
			break;

		case '+':
			newmode |= set->bits;
			break;

		case '-':
			newmode &= ~set->bits;
			break;

		case 'X':
			if (omode & (S_IFDIR|S_IXUSR|S_IXGRP|S_IXOTH))
				newmode |= set->bits;
			break;

		case '\0':
		default:
#ifdef SETMODE_DEBUG
D 7
			(void)printf("getmode(, %04o) -> %04o\n",
			    omode, newmode);
E 7
I 7
			(void)printf("getmode:%04o -> %04o\n", omode, newmode);
E 7
#endif
D 7
			return(newmode);
E 7
I 7
			return (newmode);
E 7
		}
E 4
}

D 7
#define	STANDARD_BITS	(S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO)
D 4
#define	CLR(a)		{ clrbits |= a; setbits &= ~(a); Xbits &= ~(a); }
E 4

I 2
D 4
mode_t *
E 4
I 4
static struct bitcmd *
addcmd(set, op, who, oparg, mask)
	struct bitcmd *set;
	register int oparg, who;
	register int op;
	mode_t mask;
{
	switch (op) {
	case '+':
	case 'X':
		set->cmd = op;
		set->bits = (who ? who : mask) & oparg;
		break;

	case '-':
		set->cmd = '-';
		set->bits = (who ? who : (S_IRWXU|S_IRWXG|S_IRWXO)) & oparg;
		break;

	case '=':
		set->cmd = '-';
		if (!who) {
			set->bits = STANDARD_BITS;
			who = mask;
		} else
			set->bits = who;
		set++;

		set->cmd = '+';
		set->bits = who & oparg;
		break;
	case 'u':
	case 'g':
	case 'o':
		set->cmd = op;
		if (who) {
			set->cmd2 = ((who & S_IRUSR) ? CMD2_UBITS : 0) |
				    ((who & S_IRGRP) ? CMD2_GBITS : 0) |
				    ((who & S_IROTH) ? CMD2_OBITS : 0);
			set->bits = ~0;
		} else {
			set->cmd2 = CMD2_UBITS | CMD2_GBITS | CMD2_OBITS;
			set->bits = mask;
		}
	
		if (oparg == '+')
			set->cmd2 |= CMD2_SET;
		else if (oparg == '-')
			set->cmd2 |= CMD2_CLR;
		else if (oparg == '=')
			set->cmd2 |= CMD2_SET|CMD2_CLR;
		break;
	}
	return(set+1);
}

E 7
D 13
#define	ADDCMD(a, b, c, d) \
	if (set >= endset) { \
D 7
		register struct bitcmd *newset; \
E 7
I 7
		register BITCMD *newset; \
E 7
		setlen += SET_LEN_INCR; \
D 7
		newset = realloc(saveset, sizeof(struct bitcmd) * setlen); \
E 7
I 7
		newset = realloc(saveset, sizeof(BITCMD) * setlen); \
E 7
		if (!saveset) \
D 7
			return(NULL); \
E 7
I 7
			return (NULL); \
E 7
		set = newset + (set - saveset); \
		saveset = newset; \
		endset = newset + (setlen - 2); \
	} \
E 13
I 13
#define	ADDCMD(a, b, c, d)						\
	if (set >= endset) {						\
		register BITCMD *newset;				\
		setlen += SET_LEN_INCR;					\
		newset = realloc(saveset, sizeof(BITCMD) * setlen);	\
		if (!saveset)						\
			return (NULL);					\
		set = newset + (set - saveset);				\
		saveset = newset;					\
		endset = newset + (setlen - 2);				\
	}								\
E 13
	set = addcmd(set, (a), (b), (c), (d))

I 7
#define	STANDARD_BITS	(S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO)

E 7
D 5
struct bitcmd *
E 5
I 5
void *
E 5
E 4
E 2
setmode(p)
	register char *p;
{
I 2
D 4
	extern int errno;
E 4
E 2
	register int perm, who;
	register char op;
I 7
	BITCMD *set, *saveset, *endset;
I 11
	sigset_t sigset, sigoset;
E 11
E 7
D 2
	mode_t mask;
E 2
I 2
D 4
	mode_t mask, *set;
E 2
	int permXbits;
I 2
	char *malloc();
E 4
I 4
	mode_t mask;
D 7
	struct bitcmd *set, *saveset, *endset;
E 7
D 13
	int permXbits, setlen;
E 13
I 13
	int equalopdone, permXbits, setlen;
E 13
I 5
D 7
	static int compress_mode();
E 7
E 5
E 4
E 2

I 7
	if (!*p)
		return (NULL);

E 7
	/*
D 4
	 * get a copy of the mask for the permissions that are mask
	 * relative.  Flip the bits, we want what's not set.
E 4
I 4
	 * Get a copy of the mask for the permissions that are mask relative.
D 11
	 * Flip the bits, we want what's not set.
E 11
I 11
	 * Flip the bits, we want what's not set.  Since it's possible that
	 * the caller is opening files inside a signal handler, protect them
	 * as best we can.
E 11
E 4
	 */
I 11
	sigfillset(&sigset);
        (void)sigprocmask(SIG_BLOCK, &sigset, &sigoset);
E 11
	(void)umask(mask = umask(0));
	mask = ~mask;
I 11
        (void)sigprocmask(SIG_SETMASK, &sigoset, NULL);
E 11

I 2
D 4
	if (!(set = (mode_t *)malloc((u_int)(sizeof(mode_t) * 3)))) {
		errno = ENOMEM;
E 4
I 4
	setlen = SET_LEN + 2;
	
D 7
	set = (struct bitcmd *)malloc((u_int)(sizeof(struct bitcmd) * setlen));
	if (!set)
E 4
		return(NULL);
E 7
I 7
	if ((set = malloc((u_int)(sizeof(BITCMD) * setlen))) == NULL)
		return (NULL);
E 7
D 4
	}
E 4
I 4
	saveset = set;
	endset = set + (setlen - 2);
E 4

E 2
D 4
	setbits = clrbits = Xbits = 0;

E 4
	/*
D 4
	 * if an absolute number, get it and return; disallow non-octal
	 * digits or illegal bits.
E 4
I 4
	 * If an absolute number, get it and return; disallow non-octal digits
	 * or illegal bits.
E 4
	 */
	if (isdigit(*p)) {
D 4
		setbits = (mode_t)strtol(p, (char **)0, 8);
		clrbits = ~(STANDARD_BITS|S_ISTXT);
		Xbits = 0;
E 4
I 4
D 13
		perm = (mode_t)strtol(p, (char **)0, 8);
E 13
I 13
		perm = (mode_t)strtol(p, NULL, 8);
E 13
		if (perm & ~(STANDARD_BITS|S_ISTXT)) {
			free(saveset);
D 7
			return(NULL);
E 7
I 7
			return (NULL);
E 7
		}
E 4
		while (*++p)
D 4
			if (*p < '0' || *p > '7')
E 4
I 4
			if (*p < '0' || *p > '7') {
				free(saveset);
E 4
D 2
				return(-1);
E 2
I 2
D 7
				return(NULL);
E 7
I 7
				return (NULL);
E 7
E 2
D 4
		if (setbits & clrbits)
D 2
			return(-1);
		return(0);
E 2
I 2
			return(NULL);
		return(set);
E 4
I 4
			}
		ADDCMD('=', (STANDARD_BITS|S_ISTXT), perm, mask);
D 5
		return(saveset);
E 5
I 5
D 7
		return((void *)saveset);
E 7
I 7
		return (saveset);
E 7
E 5
E 4
E 2
	}

D 4
	if (!*p)
E 4
I 4
D 7
	if (!*p) {
		free(saveset);
E 4
D 2
		return(-1);
E 2
I 2
		return(NULL);
I 4
	}
E 7
E 4
E 2
	/*
D 4
	 * accumulate bits to add and subtract from each clause of
	 * the symbolic mode
E 4
I 4
	 * Build list of structures to set/clear/copy bits as described by
	 * each clause of the symbolic mode.
E 4
	 */
	for (;;) {
D 4
		for (who = 0;; ++p)
E 4
I 4
		/* First, find out which bits might be modified. */
		for (who = 0;; ++p) {
E 4
			switch (*p) {
			case 'a':
				who |= STANDARD_BITS;
				break;
			case 'u':
				who |= S_ISUID|S_IRWXU;
				break;
			case 'g':
				who |= S_ISGID|S_IRWXG;
				break;
			case 'o':
				who |= S_IRWXO;
				break;
			default:
				goto getop;
			}
I 4
		}
D 7
	getop:		
E 7
E 4

D 4
getop:		if ((op = *p++) != '+' && op != '-' && op != '=')
E 4
I 4
D 7
		if ((op = *p++) != '+' && op != '-' && op != '=') {
E 7
I 7
getop:		if ((op = *p++) != '+' && op != '-' && op != '=') {
E 7
			free(saveset);
E 4
D 2
			return(-1);
E 2
I 2
D 7
			return(NULL);
E 7
I 7
			return (NULL);
E 7
I 4
		}
I 13
		if (op == '=')
			equalopdone = 0;
E 13
E 4
E 2

		who &= ~S_ISTXT;
D 4
		for (perm = 0;; ++p)
E 4
I 4
		for (perm = 0, permXbits = 0;; ++p) {
E 4
			switch (*p) {
			case 'r':
				perm |= S_IRUSR|S_IRGRP|S_IROTH;
				break;
			case 's':
D 4
				/* if only "other" bits ignore set-id */
E 4
I 4
				/* If only "other" bits ignore set-id. */
E 4
				if (who & ~S_IRWXO)
					perm |= S_ISUID|S_ISGID;
				break;
			case 't':
D 4
				/* if only "other" bits ignore sticky */
E 4
I 4
				/* If only "other" bits ignore sticky. */
E 4
				if (who & ~S_IRWXO) {
					who |= S_ISTXT;
					perm |= S_ISTXT;
				}
				break;
			case 'w':
				perm |= S_IWUSR|S_IWGRP|S_IWOTH;
				break;
			case 'X':
				permXbits = S_IXUSR|S_IXGRP|S_IXOTH;
				break;
			case 'x':
				perm |= S_IXUSR|S_IXGRP|S_IXOTH;
				break;
I 4
			case 'u':
			case 'g':
			case 'o':
				/*
				 * When ever we hit 'u', 'g', or 'o', we have
				 * to flush out any partial mode that we have,
				 * and then do the copying of the mode bits.
				 */
D 8
				if (perm) {
E 8
I 8
D 13
				if (perm || op == '=') {
E 13
I 13
				if (perm) {
E 13
E 8
					ADDCMD(op, who, perm, mask);
					perm = 0;
				}
I 13
				if (op == '=')
					equalopdone = 1;
E 13
				if (op == '+' && permXbits) {
					ADDCMD('X', who, permXbits, mask);
					permXbits = 0;
				}
				ADDCMD(*p, who, op, mask);
				break;

E 4
			default:
I 4
				/*
				 * Add any permissions that we haven't already
				 * done.
				 */
D 8
				if (perm) {
E 8
I 8
D 13
				if (perm || op == '=') {
E 13
I 13
				if (perm || (op == '=' && !equalopdone)) {
					if (op == '=')
						equalopdone = 1;
E 13
E 8
					ADDCMD(op, who, perm, mask);
					perm = 0;
				}
				if (permXbits) {
					ADDCMD('X', who, permXbits, mask);
					permXbits = 0;
				}
E 4
				goto apply;
			}
D 4

apply:		switch(op) {
		case '+':
			/*
			 * If no perm value, skip.  If no who value, use umask
			 * bits.  Don't bother clearing any bits, getmode
			 * clears first, then sets.
			 */
			if (perm || permXbits) {
				if (!who)
					who = mask;
				if (permXbits)
					Xbits |= who & permXbits;
				setbits |= who & perm;
			}
			break;
		case '-':
			/*
			 * If no perm value, skip.  If no who value, use
			 * owner, group, and other.
			 */
			if (perm) {
				if (!who)
					who = S_IRWXU|S_IRWXG|S_IRWXO;
				CLR(who & perm);
			}
			break;
		case '=':
			/*
			 * If no who value, clear all the bits.  Otherwise,
			 * clear the bits specified by who.
			 */
			if (!who) {
				CLR(STANDARD_BITS);
				who = mask;
			} else
				CLR(who);
			if (perm)
				setbits |= who & perm;
			break;
E 4
		}

D 4
		if (!*p)
E 4
I 4
apply:		if (!*p)
E 4
			break;
		if (*p != ',')
			goto getop;
		++p;
	}
D 4
	clrbits = ~clrbits;
D 2
	return(0);
E 2
I 2
	return(set);
E 4
I 4
	set->cmd = 0;
#ifdef SETMODE_DEBUG
	(void)printf("Before compress_mode()\n");
	dumpmode(saveset);
#endif
	compress_mode(saveset);
#ifdef SETMODE_DEBUG
	(void)printf("After compress_mode()\n");
	dumpmode(saveset);
#endif
D 5
	return(saveset);
E 5
I 5
D 7
	return((void *)saveset);
E 7
I 7
	return (saveset);
E 7
E 5
}

I 7
static BITCMD *
addcmd(set, op, who, oparg, mask)
	BITCMD *set;
	register int oparg, who;
	register int op;
	u_int mask;
{
	switch (op) {
I 13
	case '=':
		set->cmd = '-';
		set->bits = who ? who : STANDARD_BITS;
		set++;

		op = '+';
		/* FALLTHROUGH */
E 13
	case '+':
I 13
	case '-':
E 13
	case 'X':
		set->cmd = op;
		set->bits = (who ? who : mask) & oparg;
		break;

D 13
	case '-':
		set->cmd = '-';
		set->bits = (who ? who : (S_IRWXU|S_IRWXG|S_IRWXO)) & oparg;
		break;

	case '=':
		set->cmd = '-';
		if (!who) {
			set->bits = STANDARD_BITS;
			who = mask;
		} else
			set->bits = who;
		set++;

		set->cmd = '+';
		set->bits = who & oparg;
		break;
E 13
	case 'u':
	case 'g':
	case 'o':
		set->cmd = op;
		if (who) {
			set->cmd2 = ((who & S_IRUSR) ? CMD2_UBITS : 0) |
				    ((who & S_IRGRP) ? CMD2_GBITS : 0) |
				    ((who & S_IROTH) ? CMD2_OBITS : 0);
			set->bits = ~0;
		} else {
			set->cmd2 = CMD2_UBITS | CMD2_GBITS | CMD2_OBITS;
			set->bits = mask;
		}
	
		if (oparg == '+')
			set->cmd2 |= CMD2_SET;
		else if (oparg == '-')
			set->cmd2 |= CMD2_CLR;
		else if (oparg == '=')
			set->cmd2 |= CMD2_SET|CMD2_CLR;
		break;
	}
	return (set + 1);
}

E 7
#ifdef SETMODE_DEBUG
I 7
static void
E 7
dumpmode(set)
D 7
	register struct bitcmd *set;
E 7
I 7
	register BITCMD *set;
E 7
{
	for (; set->cmd; ++set)
		(void)printf("cmd: '%c' bits %04o%s%s%s%s%s%s\n",
		    set->cmd, set->bits, set->cmd2 ? " cmd2:" : "",
		    set->cmd2 & CMD2_CLR ? " CLR" : "",
		    set->cmd2 & CMD2_SET ? " SET" : "",
		    set->cmd2 & CMD2_UBITS ? " UBITS" : "",
		    set->cmd2 & CMD2_GBITS ? " GBITS" : "",
		    set->cmd2 & CMD2_OBITS ? " OBITS" : "");
}
#endif

/*
 * Given an array of bitcmd structures, compress by compacting consecutive
 * '+', '-' and 'X' commands into at most 3 commands, one of each.  The 'u',
 * 'g' and 'o' commands continue to be separate.  They could probably be 
 * compacted, but it's not worth the effort.
 */
D 7
static
E 7
I 7
static int
E 7
compress_mode(set)
D 7
	register struct bitcmd *set;
E 7
I 7
	register BITCMD *set;
E 7
{
D 7
	register struct bitcmd *nset;
E 7
I 7
	register BITCMD *nset;
E 7
	register int setbits, clrbits, Xbits, op;

	for (nset = set;;) {
		/* Copy over any 'u', 'g' and 'o' commands. */
		while ((op = nset->cmd) != '+' && op != '-' && op != 'X') {
			*set++ = *nset++;
			if (!op)
				return;
		}

		for (setbits = clrbits = Xbits = 0;; nset++) {
			if ((op = nset->cmd) == '-') {
				clrbits |= nset->bits;
				setbits &= ~nset->bits;
				Xbits &= ~nset->bits;
			} else if (op == '+') {
				setbits |= nset->bits;
				clrbits &= ~nset->bits;
				Xbits &= ~nset->bits;
			} else if (op == 'X')
				Xbits |= nset->bits & ~setbits;
			else
				break;
		}
		if (clrbits) {
			set->cmd = '-';
			set->cmd2 = 0;
			set->bits = clrbits;
			set++;
		}
		if (setbits) {
			set->cmd = '+';
			set->cmd2 = 0;
			set->bits = setbits;
			set++;
		}
		if (Xbits) {
			set->cmd = 'X';
			set->cmd2 = 0;
			set->bits = Xbits;
			set++;
		}
	}
E 4
E 2
}
E 1
