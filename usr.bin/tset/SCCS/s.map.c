h64660
s 00002/00002/00235
d D 8.1 93/06/09 22:53:58 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00009/00225
d D 5.2 91/12/24 10:33:34 bostic 2 1
c add the -a, -d, -p and -r options back in
e
s 00234/00000/00000
d D 5.1 91/12/22 18:54:45 bostic 1 0
c date and time created 91/12/22 18:54:45 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

int	baudrate __P((char *));

/* Baud rate conditionals for mapping. */
#define	GT		0x01
#define	EQ		0x02
#define	LT		0x04
#define	NOT		0x08
#define	GE		(GT | EQ)
#define	LE		(LT | EQ)

typedef struct map {
	struct map *next;	/* Linked list of maps. */
	char *porttype;		/* Port type, or "" for any. */
	char *type;		/* Terminal type to select. */
	int conditional;	/* Baud rate conditionals bitmask. */
	int speed;		/* Baud rate to compare against. */
} MAP;

MAP *cur, *maplist;

/*
 * Syntax for -m:
 * [port-type][test baudrate]:terminal-type
 * The baud rate tests are: >, <, @, =, !
 */
void
D 2
add_mapping(arg)
	char *arg;
E 2
I 2
add_mapping(port, arg)
	char *port, *arg;
E 2
{
	MAP *mapp;
	char *copy, *p, *termp;

	copy = strdup(arg);
	mapp = malloc((u_int)sizeof(MAP));
	if (copy == NULL || mapp == NULL)
		err("%s", strerror(errno));
	mapp->next = NULL;
	if (maplist == NULL)
		cur = maplist = mapp;
	else {
		cur->next = mapp;
		cur =  mapp;
	}

	mapp->porttype = arg;
	mapp->conditional = 0;

	arg = strpbrk(arg, "><@=!:");

	if (arg == NULL) {			/* [?]term */
		mapp->type = mapp->porttype;
		mapp->porttype = NULL;
D 2
#ifdef MAPDEBUG
		goto mdebug;
#else
		return;
#endif
E 2
I 2
		goto done;
E 2
	}

	if (arg == mapp->porttype)		/* [><@=! baud]:term */
		termp = mapp->porttype = NULL;
	else
		termp = arg;

	for (;; ++arg)				/* Optional conditionals. */
		switch(*arg) {
		case '<':
			if (mapp->conditional & GT)
				goto badmopt;
			mapp->conditional |= LT;
			break;
		case '>':
			if (mapp->conditional & LT)
				goto badmopt;
			mapp->conditional |= GT;
			break;
		case '@':
		case '=':			/* Not documented. */
			mapp->conditional |= EQ;
			break;
		case '!':
			mapp->conditional |= NOT;
			break;
		default:
			goto next;
		}

next:	if (*arg == ':') {
		if (mapp->conditional)
			goto badmopt;
		++arg;
	} else {				/* Optional baudrate. */
		arg = index(p = arg, ':');
		if (arg == NULL)
			goto badmopt;
		*arg++ = '\0';
		mapp->speed = baudrate(p);
	}

	if (*arg == NULL)			/* Non-optional type. */
D 2
badmopt:	err("illegal -m option format: %s", copy);
E 2
I 2
		goto badmopt;
E 2

	mapp->type = arg;

	/* Terminate porttype, if specified. */
	if (termp != NULL)
		*termp = '\0';

	/* If a NOT conditional, reverse the test. */
	if (mapp->conditional & NOT)
		mapp->conditional = ~mapp->conditional & (EQ | GT | LT);

I 2
	/* If user specified a port with an option flag, set it. */
done:	if (port) {
		if (mapp->porttype)
badmopt:		err("illegal -m option format: %s", copy);
		mapp->porttype = port;
	}

E 2
#ifdef MAPDEBUG
D 2
mdebug:	(void)printf("port: %s\n", mapp->porttype ? mapp->porttype : "ANY");
E 2
I 2
	(void)printf("port: %s\n", mapp->porttype ? mapp->porttype : "ANY");
E 2
	(void)printf("type: %s\n", mapp->type);
	(void)printf("conditional: ");
	p = "";
	if (mapp->conditional & GT) {
		(void)printf("GT");
		p = "/";
	}
	if (mapp->conditional & EQ) {
		(void)printf("%sEQ", p);
		p = "/";
	}
	if (mapp->conditional & LT)
		(void)printf("%sLT", p);
	(void)printf("\nspeed: %d\n", mapp->speed);
#endif
}

/*
 * Return the type of terminal to use for a port of type 'type', as specified
 * by the first applicable mapping in 'map'.  If no mappings apply, return
 * 'type'.
 */
char *
mapped(type)
	char *type;
{
	MAP *mapp;
	int match;

	for (mapp = maplist; mapp; mapp = mapp->next)
		if (mapp->porttype == NULL || !strcmp(mapp->porttype, type)) {
			switch (mapp->conditional) {
			case 0:			/* No test specified. */
				match = 1;
				break;
			case EQ:
				match = (ospeed == mapp->speed);
				break;
			case GE:
				match = (ospeed >= mapp->speed);
				break;
			case GT:
				match = (ospeed > mapp->speed);
				break;
			case LE:
				match = (ospeed <= mapp->speed);
				break;
			case LT:
				match = (ospeed < mapp->speed);
				break;
			}
			if (match)
				return (mapp->type);
		}
	/* No match found; return given type. */
	return (type);
}

typedef struct speeds {
	char	*string;
	int	speed;
} SPEEDS;

SPEEDS speeds[] = {
	"0",		B0,
	"50",		B50,
	"75",		B75,
	"110",		B110,
	"134",		B134,
	"134.5",	B134,
	"150",		B150,
	"200",		B200,
	"300",		B300,
	"600",		B600,
	"1200",		B1200,
	"1800",		B1800,
	"2400",		B2400,
	"4800",		B4800,
	"9600",		B9600,
	"19200",	B19200,
	"38400",	B38400,
	"exta",		B19200,
	"extb",		B38400,
	NULL
};

int
baudrate(rate)
	char *rate;
{
	SPEEDS *sp;

	/* The baudrate number can be preceded by a 'B', which is ignored. */
	if (*rate == 'B')
		++rate;

	for (sp = speeds; sp->string; ++sp)
		if (!strcasecmp(rate, sp->string))
			return (sp->speed);
	err("unknown baud rate %s", rate);
	/* NOTREACHED */
}
E 1
