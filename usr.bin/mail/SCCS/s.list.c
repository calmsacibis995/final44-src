h17154
s 00001/00001/00818
d D 8.4 95/05/01 06:37:49 dab 30 28
c Make "/:y" and abbreviation for "/subject:y".
e
s 00007/00004/00815
d R 8.4 95/04/21 08:34:55 dab 29 28
c Make the check for "/to:" be case sensitive, so that
c "/To:" can be use to limit the search to just the "To:" field.
c Also make "/:y" and abbreviation for "/subject:y".
e
s 00044/00000/00775
d D 8.3 95/04/20 10:39:25 dab 28 27
c Add support for the special case of searchheaders,
c so that ``/To:y'' will search for the field ``y'' in not
c just the ``To'' field, but also in the ``Cc'' and ``Bcc'' fields.
e
s 00009/00004/00766
d D 8.2 94/04/19 14:39:14 edward 27 26
c backslash and ^ handling in getrawlist() fixed
e
s 00002/00002/00768
d D 8.1 93/06/06 15:08:04 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00761
d D 5.16 92/11/17 21:40:49 edward 25 24
c searchheaders
e
s 00026/00011/00737
d D 5.15 92/06/26 12:03:18 bostic 24 23
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00011/00747
d D 5.14 90/06/01 16:59:17 bostic 23 22
c new copyright notice
e
s 00004/00003/00754
d D 5.13 89/04/01 13:17:59 edward 22 21
c kludge to make undeleting an undeleted message work
e
s 00012/00013/00745
d D 5.12 89/02/13 23:50:07 edward 21 20
c check for no messages in getmsglist() and first()
e
s 00002/00002/00756
d D 5.11 88/10/20 19:40:37 edward 20 19
c non-flexname portability fix (from Ian Darwin, darwin!ian)
e
s 00014/00007/00744
d D 5.10 88/08/17 14:44:46 edward 19 18
c bug report from gumkowsk@nadc.arpa (fix is my own),
c handle unmatched quotes correctly and make null string match no sender
e
s 00003/00003/00748
d D 5.9 88/07/08 19:41:33 edward 18 17
c removed some functions in the C library
e
s 00012/00007/00739
d D 5.8 88/06/29 21:01:51 bostic 17 16
c install approved copyright notice
e
s 00074/00028/00672
d D 5.7 88/06/10 21:23:31 edward 16 15
c getrawlist changed to allow quoting inside strings
c and to support \ and ^ within quotes
e
s 00011/00005/00689
d D 5.6 88/02/18 17:04:03 bostic 15 14
c written by Kurt Shoens; added Berkeley specific header
e
s 00001/00001/00693
d D 5.5 87/05/18 12:28:06 edward 14 13
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00008/00001/00686
d D 5.4 85/11/02 20:29:38 serge 13 12
c check for overflow in getrawlist()
e
s 00031/00016/00656
d D 5.3 85/09/23 17:50:41 serge 12 10
c made "-" and "+" skip over deleted messages (from guy@sun)
c "type user" works now (does a substring match instead of literal comparison)
e
s 00030/00015/00657
d R 5.3 85/09/15 16:51:24 serge 11 10
c made "-" and "+" skip over deleted messages (from guy@sun)
c "type user" works now (does a substring match instead of literal comparison)
e
s 00001/00001/00671
d D 5.2 85/06/21 17:11:42 mckusick 10 9
c botched copyright
e
s 00007/00001/00665
d D 5.1 85/06/06 10:36:26 dist 9 8
c Add copyright
e
s 00003/00003/00663
d D 2.3 83/08/11 22:17:05 sam 8 7
c standardize sccs keyword lines
e
s 00002/00001/00664
d D 2.2 83/01/22 14:43:47 leres 7 6
c Fixed bug in marking a range; modified markall() to only mark messages
c that aren't deleted and match the passed flag.
e
s 00000/00000/00665
d D 2.1 81/07/01 11:09:29 kurt 6 5
c Release to Heidi Stettner
e
s 00001/00001/00664
d D 1.5 81/02/06 09:38:24 kas 5 4
c nameof now takes 2 args
e
s 00095/00003/00570
d D 1.4 81/01/23 17:06:33 kas 4 3
c added :{r,o,u,n,d} modifiers for read, old, unread, new, and deleted
c to message list syntax
e
s 00005/00002/00568
d D 1.3 80/10/10 13:45:12 kas 3 2
c Fixed imagined bug in subject pattern match about
c restarting the character search shifted over by 1 character.
e
s 00051/00003/00519
d D 1.2 80/10/09 13:37:40 kas 2 1
c added /pattern to search for pattern in subjects
e
s 00522/00000/00000
d D 1.1 80/10/08 09:50:32 kas 1 0
c date and time created 80/10/08 09:50:32 by kas
e
u
U
f b 
t
T
I 9
/*
D 26
 * Copyright (c) 1980 Regents of the University of California.
D 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 17
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 17
I 17
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 17
E 15
 */

E 9
I 1
D 8
#
E 8
I 8
D 15
#ifndef lint
D 10
static char sccsid[] = "%W% (Berkeley) %G%";
E 10
I 10
static char *sccsid = "%W% (Berkeley) %G%";
E 10
D 9
#endif
E 9
I 9
#endif not lint
E 15
I 15
D 17
#ifdef notdef
E 17
I 17
#ifndef lint
E 17
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif /* notdef */
E 17
I 17
#endif /* not lint */
E 17
E 15
E 9
E 8

#include "rcv.h"
#include <ctype.h>
I 24
#include "extern.h"
E 24

/*
 * Mail -- a mail program
 *
 * Message list handling.
 */
D 8

static char *SccsId = "%W% %G%";
E 8

/*
 * Convert the user string of message numbers and
 * store the numbers into vector.
 *
 * Returns the count of messages picked up or -1 on error.
 */
D 24

E 24
I 24
int
E 24
getmsglist(buf, vector, flags)
	char *buf;
D 24
	int *vector;
E 24
I 24
	int *vector, flags;
E 24
{
	register int *ip;
	register struct message *mp;

I 21
	if (msgCount == 0) {
		*vector = 0;
		return 0;
	}
E 21
	if (markall(buf, flags) < 0)
		return(-1);
	ip = vector;
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if (mp->m_flag & MMARK)
			*ip++ = mp - &message[0] + 1;
D 21
	*ip = NULL;
E 21
I 21
	*ip = 0;
E 21
	return(ip - vector);
}

/*
 * Mark all messages that the user wanted from the command
 * line in the message structure.  Return 0 on success, -1
 * on error.
 */

I 4
/*
 * Bit values for colon modifiers.
 */

#define	CMNEW		01		/* New messages */
#define	CMOLD		02		/* Old messages */
#define	CMUNREAD	04		/* Unread messages */
#define	CMDELETED	010		/* Deleted messages */
#define	CMREAD		020		/* Read messages */

/*
 * The following table describes the letters which can follow
 * the colon and gives the corresponding modifier bit.
 */

struct coltab {
	char	co_char;		/* What to find past : */
	int	co_bit;			/* Associated modifier bit */
	int	co_mask;		/* m_status bits to mask */
	int	co_equal;		/* ... must equal this */
} coltab[] = {
	'n',		CMNEW,		MNEW,		MNEW,
	'o',		CMOLD,		MNEW,		0,
	'u',		CMUNREAD,	MREAD,		0,
	'd',		CMDELETED,	MDELETED,	MDELETED,
	'r',		CMREAD,		MREAD,		MREAD,
	0,		0,		0,		0
};

static	int	lastcolmod;

I 24
int
E 24
E 4
markall(buf, f)
	char buf[];
I 24
	int f;
E 24
{
	register char **np;
	register int i;
I 4
	register struct message *mp;
E 4
	char *namelist[NMLSIZE], *bufp;
D 4
	int tok, beg, mc, star, other, valdot;
E 4
I 4
	int tok, beg, mc, star, other, valdot, colmod, colresult;
E 4

	valdot = dot - &message[0] + 1;
I 4
	colmod = 0;
E 4
	for (i = 1; i <= msgCount; i++)
		unmark(i);
	bufp = buf;
	mc = 0;
	np = &namelist[0];
	scaninit();
	tok = scan(&bufp);
	star = 0;
	other = 0;
	beg = 0;
	while (tok != TEOL) {
		switch (tok) {
		case TNUMBER:
number:
			if (star) {
				printf("No numbers mixed with *\n");
				return(-1);
			}
			mc++;
			other++;
			if (beg != 0) {
				if (check(lexnumber, f))
					return(-1);
				for (i = beg; i <= lexnumber; i++)
D 7
					mark(i);
E 7
I 7
D 22
					if ((message[i - 1].m_flag & MDELETED) == f)
E 22
I 22
					if (f == MDELETED || (message[i - 1].m_flag & MDELETED) == 0)
E 22
						mark(i);
E 7
				beg = 0;
				break;
			}
			beg = lexnumber;
			if (check(beg, f))
				return(-1);
			tok = scan(&bufp);
			regret(tok);
			if (tok != TDASH) {
				mark(beg);
				beg = 0;
			}
			break;

		case TPLUS:
			if (beg != 0) {
				printf("Non-numeric second argument\n");
				return(-1);
			}
D 12
			if (valdot < msgCount)
				mark(valdot+1);
			else {
				printf("Referencing beyond EOF\n");
				return(-1);
			}
E 12
I 12
			i = valdot;
			do {
				i++;
				if (i > msgCount) {
					printf("Referencing beyond EOF\n");
					return(-1);
				}
			} while ((message[i - 1].m_flag & MDELETED) != f);
			mark(i);
E 12
			break;

		case TDASH:
			if (beg == 0) {
D 12
				if (valdot > 1)
					mark(valdot-1);
				else {
					printf("Referencing before 1\n");
					return(-1);
				}
E 12
I 12
				i = valdot;
				do {
					i--;
					if (i <= 0) {
						printf("Referencing before 1\n");
						return(-1);
					}
				} while ((message[i - 1].m_flag & MDELETED) != f);
				mark(i);
E 12
			}
			break;

		case TSTRING:
			if (beg != 0) {
				printf("Non-numeric second argument\n");
				return(-1);
			}
			other++;
D 4
			*np++ = savestr(lexstring);
E 4
I 4
			if (lexstring[0] == ':') {
				colresult = evalcol(lexstring[1]);
				if (colresult == 0) {
					printf("Unknown colon modifier \"%s\"\n",
					    lexstring);
					return(-1);
				}
				colmod |= colresult;
			}
			else
				*np++ = savestr(lexstring);
E 4
			break;

		case TDOLLAR:
		case TUP:
		case TDOT:
			lexnumber = metamess(lexstring[0], f);
			if (lexnumber == -1)
				return(-1);
			goto number;

		case TSTAR:
			if (other) {
				printf("Can't mix \"*\" with anything\n");
				return(-1);
			}
			star++;
			break;
I 19

		case TERROR:
			return -1;
E 19
		}
		tok = scan(&bufp);
	}
I 4
	lastcolmod = colmod;
E 4
	*np = NOSTR;
	mc = 0;
	if (star) {
		for (i = 0; i < msgCount; i++)
			if ((message[i].m_flag & MDELETED) == f) {
				mark(i+1);
				mc++;
			}
		if (mc == 0) {
			printf("No applicable messages.\n");
			return(-1);
		}
		return(0);
	}

	/*
	 * If no numbers were given, mark all of the messages,
	 * so that we can unmark any whose sender was not selected
	 * if any user names were given.
	 */

D 4
	if (np > namelist && mc == 0)
E 4
I 4
	if ((np > namelist || colmod != 0) && mc == 0)
E 4
		for (i = 1; i <= msgCount; i++)
D 12
			if ((message[i-1].m_flag & (MSAVED|MDELETED)) == f)
E 12
I 12
			if ((message[i-1].m_flag & MDELETED) == f)
E 12
				mark(i);

	/*
	 * If any names were given, go through and eliminate any
	 * messages whose senders were not requested.
	 */

	if (np > namelist) {
		for (i = 1; i <= msgCount; i++) {
			for (mc = 0, np = &namelist[0]; *np != NOSTR; np++)
D 2
				if (sender(*np, i)) {
					mc++;
					break;
E 2
I 2
				if (**np == '/') {
					if (matchsubj(*np, i)) {
						mc++;
						break;
					}
E 2
				}
I 2
				else {
D 19
					if (sender(*np, i)) {
E 19
I 19
					if (matchsender(*np, i)) {
E 19
						mc++;
						break;
					}
				}
E 2
			if (mc == 0)
				unmark(i);
		}

		/*
		 * Make sure we got some decent messages.
		 */

		mc = 0;
		for (i = 1; i <= msgCount; i++)
			if (message[i-1].m_flag & MMARK) {
				mc++;
				break;
			}
		if (mc == 0) {
			printf("No applicable messages from {%s",
				namelist[0]);
			for (np = &namelist[1]; *np != NOSTR; np++)
				printf(", %s", *np);
			printf("}\n");
			return(-1);
		}
	}
I 4

	/*
	 * If any colon modifiers were given, go through and
	 * unmark any messages which do not satisfy the modifiers.
	 */

	if (colmod != 0) {
		for (i = 1; i <= msgCount; i++) {
			register struct coltab *colp;

			mp = &message[i - 1];
			for (colp = &coltab[0]; colp->co_char; colp++)
				if (colp->co_bit & colmod)
					if ((mp->m_flag & colp->co_mask)
					    != colp->co_equal)
						unmark(i);
			
		}
		for (mp = &message[0]; mp < &message[msgCount]; mp++)
			if (mp->m_flag & MMARK)
				break;
		if (mp >= &message[msgCount]) {
			register struct coltab *colp;

			printf("No messages satisfy");
			for (colp = &coltab[0]; colp->co_char; colp++)
				if (colp->co_bit & colmod)
					printf(" :%c", colp->co_char);
			printf("\n");
			return(-1);
		}
	}
	return(0);
}

/*
 * Turn the character after a colon modifier into a bit
 * value.
 */
I 24
int
E 24
evalcol(col)
I 24
	int col;
E 24
{
	register struct coltab *colp;

	if (col == 0)
		return(lastcolmod);
	for (colp = &coltab[0]; colp->co_char; colp++)
		if (colp->co_char == col)
			return(colp->co_bit);
E 4
	return(0);
}

/*
 * Check the passed message number for legality and proper flags.
I 22
 * If f is MDELETED, then either kind will do.  Otherwise, the message
 * has to be undeleted.
E 22
 */
I 24
int
E 24
D 22

E 22
check(mesg, f)
I 24
	int mesg, f;
E 24
{
	register struct message *mp;

	if (mesg < 1 || mesg > msgCount) {
		printf("%d: Invalid message number\n", mesg);
		return(-1);
	}
	mp = &message[mesg-1];
D 22
	if ((mp->m_flag & MDELETED) != f) {
E 22
I 22
	if (f != MDELETED && (mp->m_flag & MDELETED) != 0) {
E 22
		printf("%d: Inappropriate message\n", mesg);
		return(-1);
	}
	return(0);
}

/*
 * Scan out the list of string arguments, shell style
 * for a RAWLIST.
 */
D 24

E 24
I 24
int
E 24
D 13
getrawlist(line, argv)
E 13
I 13
getrawlist(line, argv, argc)
E 13
	char line[];
	char **argv;
I 13
	int  argc;
E 13
{
D 16
	register char **ap, *cp, *cp2;
	char linebuf[BUFSIZ], quotec;
I 13
	register char **last;
E 16
I 16
	register char c, *cp, *cp2, quotec;
	int argn;
	char linebuf[BUFSIZ];
E 16
E 13

D 16
	ap = argv;
E 16
I 16
	argn = 0;
E 16
	cp = line;
I 13
D 16
	last = argv + argc - 1;
E 13
	while (*cp != '\0') {
		while (any(*cp, " \t"))
			cp++;
		cp2 = linebuf;
		quotec = 0;
		if (any(*cp, "'\""))
			quotec = *cp++;
		if (quotec == 0)
			while (*cp != '\0' && !any(*cp, " \t"))
				*cp2++ = *cp++;
		else {
			while (*cp != '\0' && *cp != quotec)
				*cp2++ = *cp++;
			if (*cp != '\0')
				cp++;
		}
		*cp2 = '\0';
		if (cp2 == linebuf)
E 16
I 16
	for (;;) {
		for (; *cp == ' ' || *cp == '\t'; cp++)
			;
		if (*cp == '\0')
E 16
			break;
I 13
D 16
		if (ap >= last) {
			printf("Too many elements in the list; excess discarded\n");
E 16
I 16
		if (argn >= argc - 1) {
			printf(
			"Too many elements in the list; excess discarded.\n");
E 16
			break;
		}
E 13
D 16
		*ap++ = savestr(linebuf);
E 16
I 16
		cp2 = linebuf;
		quotec = '\0';
		while ((c = *cp) != '\0') {
			cp++;
			if (quotec != '\0') {
				if (c == quotec)
					quotec = '\0';
				else if (c == '\\')
					switch (c = *cp++) {
					case '\0':
D 27
						*cp2++ = *--cp;
E 27
I 27
						*cp2++ = '\\';
						cp--;
E 27
						break;
					case '0': case '1': case '2': case '3':
					case '4': case '5': case '6': case '7':
						c -= '0';
						if (*cp >= '0' && *cp <= '7')
							c = c * 8 + *cp++ - '0';
						if (*cp >= '0' && *cp <= '7')
							c = c * 8 + *cp++ - '0';
						*cp2++ = c;
						break;
					case 'b':
						*cp2++ = '\b';
						break;
					case 'f':
						*cp2++ = '\f';
						break;
					case 'n':
						*cp2++ = '\n';
						break;
					case 'r':
						*cp2++ = '\r';
						break;
					case 't':
						*cp2++ = '\t';
						break;
					case 'v':
						*cp2++ = '\v';
						break;
I 27
					default:
						*cp2++ = c;
E 27
					}
				else if (c == '^') {
					c = *cp++;
					if (c == '?')
						*cp2++ = '\177';
					/* null doesn't show up anyway */
					else if (c >= 'A' && c <= '_' ||
						 c >= 'a' && c <= 'z')
D 27
						*cp2++ &= 037;
					else
						*cp2++ = *--cp;
E 27
I 27
						*cp2++ = c & 037;
					else {
						*cp2++ = '^';
						cp--;
					}
E 27
				} else
					*cp2++ = c;
			} else if (c == '"' || c == '\'')
				quotec = c;
			else if (c == ' ' || c == '\t')
				break;
			else
				*cp2++ = c;
		}
		*cp2 = '\0';
		argv[argn++] = savestr(linebuf);
E 16
	}
D 16
	*ap = NOSTR;
	return(ap-argv);
E 16
I 16
	argv[argn] = NOSTR;
	return argn;
E 16
}

/*
 * scan out a single lexical item and return its token number,
 * updating the string pointer passed **p.  Also, store the value
 * of the number or string scanned in lexnumber or lexstring as
 * appropriate.  In any event, store the scanned `thing' in lexstring.
 */

struct lex {
	char	l_char;
	char	l_token;
} singles[] = {
	'$',	TDOLLAR,
	'.',	TDOT,
	'^',	TUP,
	'*',	TSTAR,
	'-',	TDASH,
	'+',	TPLUS,
	'(',	TOPEN,
	')',	TCLOSE,
	0,	0
};

I 24
int
E 24
scan(sp)
	char **sp;
{
	register char *cp, *cp2;
	register int c;
	register struct lex *lp;
	int quotec;

	if (regretp >= 0) {
D 14
		copy(stringstack[regretp], lexstring);
E 14
I 14
D 20
		strcpy(lexstring, stringstack[regretp]);
E 20
I 20
		strcpy(lexstring, string_stack[regretp]);
E 20
E 14
		lexnumber = numberstack[regretp];
		return(regretstack[regretp--]);
	}
	cp = *sp;
	cp2 = lexstring;
	c = *cp++;

	/*
	 * strip away leading white space.
	 */

D 18
	while (any(c, " \t"))
E 18
I 18
	while (c == ' ' || c == '\t')
E 18
		c = *cp++;

	/*
	 * If no characters remain, we are at end of line,
	 * so report that.
	 */

	if (c == '\0') {
		*sp = --cp;
		return(TEOL);
	}

	/*
	 * If the leading character is a digit, scan
	 * the number and convert it on the fly.
	 * Return TNUMBER when done.
	 */

	if (isdigit(c)) {
		lexnumber = 0;
		while (isdigit(c)) {
			lexnumber = lexnumber*10 + c - '0';
			*cp2++ = c;
			c = *cp++;
		}
		*cp2 = '\0';
		*sp = --cp;
		return(TNUMBER);
	}

	/*
	 * Check for single character tokens; return such
	 * if found.
	 */

	for (lp = &singles[0]; lp->l_char != 0; lp++)
		if (c == lp->l_char) {
			lexstring[0] = c;
			lexstring[1] = '\0';
			*sp = cp;
			return(lp->l_token);
		}

	/*
	 * We've got a string!  Copy all the characters
	 * of the string into lexstring, until we see
	 * a null, space, or tab.
	 * If the lead character is a " or ', save it
	 * and scan until you get another.
	 */

	quotec = 0;
D 18
	if (any(c, "'\"")) {
E 18
I 18
	if (c == '\'' || c == '"') {
E 18
		quotec = c;
		c = *cp++;
	}
	while (c != '\0') {
D 19
		if (c == quotec)
E 19
I 19
		if (c == quotec) {
			cp++;
E 19
			break;
I 19
		}
E 19
D 18
		if (quotec == 0 && any(c, " \t"))
E 18
I 18
		if (quotec == 0 && (c == ' ' || c == '\t'))
E 18
			break;
		if (cp2 - lexstring < STRINGLEN-1)
			*cp2++ = c;
		c = *cp++;
	}
D 19
	if (quotec && c == 0)
E 19
I 19
	if (quotec && c == 0) {
E 19
		fprintf(stderr, "Missing %c\n", quotec);
I 19
		return TERROR;
	}
E 19
	*sp = --cp;
	*cp2 = '\0';
	return(TSTRING);
}

/*
 * Unscan the named token by pushing it onto the regret stack.
 */
D 24

E 24
I 24
void
E 24
regret(token)
I 24
	int token;
E 24
{
	if (++regretp >= REGDEP)
		panic("Too many regrets");
	regretstack[regretp] = token;
	lexstring[STRINGLEN-1] = '\0';
D 20
	stringstack[regretp] = savestr(lexstring);
E 20
I 20
	string_stack[regretp] = savestr(lexstring);
E 20
	numberstack[regretp] = lexnumber;
}

/*
 * Reset all the scanner global variables.
 */
D 24

E 24
I 24
void
E 24
scaninit()
{
	regretp = -1;
}

/*
 * Find the first message whose flags & m == f  and return
 * its message number.
 */
D 24

E 24
I 24
int
E 24
first(f, m)
I 24
	int f, m;
E 24
{
D 21
	register int mesg;
E 21
	register struct message *mp;

D 21
	mesg = dot - &message[0] + 1;
E 21
I 21
	if (msgCount == 0)
		return 0;
E 21
	f &= MDELETED;
	m &= MDELETED;
D 21
	for (mp = dot; mp < &message[msgCount]; mp++) {
E 21
I 21
	for (mp = dot; mp < &message[msgCount]; mp++)
E 21
		if ((mp->m_flag & m) == f)
D 21
			return(mesg);
		mesg++;
	}
	mesg = dot - &message[0];
	for (mp = dot-1; mp >= &message[0]; mp--) {
E 21
I 21
			return mp - message + 1;
	for (mp = dot-1; mp >= &message[0]; mp--)
E 21
		if ((mp->m_flag & m) == f)
D 21
			return(mesg);
		mesg--;
	}
	return(NULL);
E 21
I 21
			return mp - message + 1;
	return 0;
E 21
}

/*
 * See if the passed name sent the passed message number.  Return true
 * if so.
 */
D 24

E 24
I 24
int
E 24
D 19
sender(str, mesg)
E 19
I 19
matchsender(str, mesg)
E 19
	char *str;
I 24
	int mesg;
E 24
{
D 19
	register struct message *mp;
E 19
D 12
	register char *cp;
E 12
I 12
	register char *cp, *cp2, *backup;
E 12

D 19
	mp = &message[mesg-1];
D 5
	cp = nameof(mp);
E 5
I 5
D 12
	cp = nameof(mp, 0);
E 5
	return(icequal(cp, str));
E 12
I 12
	backup = cp2 = nameof(mp, 0);
E 19
I 19
	if (!*str)	/* null string matches nothing instead of everything */
		return 0;
	backup = cp2 = nameof(&message[mesg - 1], 0);
E 19
	cp = str;
	while (*cp2) {
		if (*cp == 0)
			return(1);
		if (raise(*cp++) != raise(*cp2++)) {
			cp2 = ++backup;
			cp = str;
		}
	}
	return(*cp == 0);
E 12
I 2
}

/*
I 28
 * See if the passed name received the passed message number.  Return true
 * if so.
 */

static char *to_fields[] = { "to", "cc", "bcc", 0 };

matchto(str, mesg)
	char *str;
{
	register struct message *mp;
	register char *cp, *cp2, *backup, **to;

	str++;

	if (*str == 0)	/* null string matches nothing instead of everything */
		return(0);

	mp = &message[mesg-1];

	for (to = to_fields; *to; to++) {
		cp = str;
		cp2 = hfield(*to, mp);
		if (cp2 != NOSTR) {
			backup = cp2;
			while (*cp2) {
				if (*cp == 0)
					return(1);
				if (raise(*cp++) != raise(*cp2++)) {
					cp2 = ++backup;
					cp = str;
				}
			}
			if (*cp == 0)
				return(1);
		}
	}
	return(0);
}

/*
E 28
 * See if the given string matches inside the subject field of the
 * given message.  For the purpose of the scan, we ignore case differences.
 * If it does, return true.  The string search argument is assumed to
 * have the form "/search-string."  If it is of the form "/," we use the
 * previous search string.
 */

char lastscan[128];
D 24

E 24
I 24
int
E 24
matchsubj(str, mesg)
	char *str;
I 24
	int mesg;
E 24
{
	register struct message *mp;
D 3
	register char *cp, *cp2;
E 3
I 3
	register char *cp, *cp2, *backup;
E 3

	str++;
	if (strlen(str) == 0)
		str = lastscan;
	else
		strcpy(lastscan, str);
	mp = &message[mesg-1];
	
	/*
	 * Now look, ignoring case, for the word in the string.
	 */

D 25
	cp = str;
	cp2 = hfield("subject", mp);
E 25
I 25
	if (value("searchheaders") && (cp = index(str, ':'))) {
I 28
		/* Check for special case "/To:" */
		if (raise(str[0]) == 'T' && raise(str[1]) == 'O' &&
		    str[2] == ':')
			return(matchto(cp, mesg));
E 28
		*cp++ = '\0';
D 30
		cp2 = hfield(str, mp);
E 30
I 30
		cp2 = hfield(*str ? str : "subject", mp);
E 30
		cp[-1] = ':';
		str = cp;
	} else {
		cp = str;
		cp2 = hfield("subject", mp);
	}
E 25
	if (cp2 == NOSTR)
		return(0);
I 3
	backup = cp2;
E 3
	while (*cp2) {
		if (*cp == 0)
			return(1);
D 3
		if (raise(*cp++) != raise(*cp2++))
E 3
I 3
		if (raise(*cp++) != raise(*cp2++)) {
			cp2 = ++backup;
E 3
			cp = str;
I 3
		}
E 3
	}
	return(*cp == 0);
E 2
}

/*
 * Mark the named message by setting its mark bit.
 */
D 24

E 24
I 24
void
E 24
mark(mesg)
I 24
	int mesg;
E 24
{
	register int i;

	i = mesg;
	if (i < 1 || i > msgCount)
		panic("Bad message number to mark");
	message[i-1].m_flag |= MMARK;
}

/*
 * Unmark the named message.
 */
D 24

E 24
I 24
void
E 24
unmark(mesg)
I 24
	int mesg;
E 24
{
	register int i;

	i = mesg;
	if (i < 1 || i > msgCount)
		panic("Bad message number to unmark");
	message[i-1].m_flag &= ~MMARK;
}

/*
 * Return the message number corresponding to the passed meta character.
 */
D 24

E 24
I 24
int
E 24
metamess(meta, f)
I 24
	int meta, f;
E 24
{
	register int c, m;
	register struct message *mp;

	c = meta;
	switch (c) {
	case '^':
		/*
		 * First 'good' message left.
		 */
		for (mp = &message[0]; mp < &message[msgCount]; mp++)
			if ((mp->m_flag & MDELETED) == f)
				return(mp - &message[0] + 1);
		printf("No applicable messages\n");
		return(-1);

	case '$':
		/*
		 * Last 'good message left.
		 */
		for (mp = &message[msgCount-1]; mp >= &message[0]; mp--)
			if ((mp->m_flag & MDELETED) == f)
				return(mp - &message[0] + 1);
		printf("No applicable messages\n");
		return(-1);

	case '.':
		/* 
		 * Current message.
		 */
		m = dot - &message[0] + 1;
		if ((dot->m_flag & MDELETED) != f) {
			printf("%d: Inappropriate message\n", m);
			return(-1);
		}
		return(m);

	default:
		printf("Unknown metachar (%c)\n", c);
		return(-1);
	}
}
E 1
