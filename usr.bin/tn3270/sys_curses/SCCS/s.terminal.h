h49073
s 00002/00002/00053
d D 8.1 93/06/06 16:53:02 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00052
d D 4.3 91/04/26 16:01:22 bostic 12 11
c new copyright; att/bsd/shared
e
s 00007/00000/00058
d D 4.2 89/05/30 22:01:40 minshall 11 10
c Fix bug with unformatted screens (sigh).
e
s 00000/00000/00058
d D 4.1 88/12/04 15:12:27 minshall 10 9
c Release 4.1
e
s 00010/00005/00048
d D 3.3 88/06/29 20:06:20 bostic 9 8
c install approved copyright notice
e
s 00011/00001/00042
d D 3.2 88/03/28 11:55:28 bostic 8 7
c add Berkeley specific headers
e
s 00000/00000/00043
d D 3.1 87/08/11 10:20:06 minshall 7 6
c New version numbering.
e
s 00001/00001/00042
d D 1.6 87/07/17 10:04:32 minshall 6 5
c Install sccs headers and copyright notices.
e
s 00000/00003/00043
d D 1.5 87/06/18 16:26:42 minshall 5 4
c Remove -DSLOWSCREEN (make it an always thing, which it is and
c should be) (yeah!).
e
s 00001/00001/00045
d D 1.4 87/06/08 14:36:07 minshall 4 3
c Bring "TermIsStartField" up to date.
e
s 00009/00008/00037
d D 1.3 87/05/18 16:06:18 minshall 3 2
c Fixes to make ScreenImage type NOT hardcoded.
e
s 00005/00005/00040
d D 1.2 86/11/12 17:17:20 minshall 2 1
c This version works with 3278-style inline attribute characters.
e
s 00045/00000/00000
d D 1.1 86/11/12 12:06:18 minshall 1 0
c date and time created 86/11/12 12:06:18 by minshall
e
u
U
t
T
I 1
D 12
/*
D 6
 *	@(#)screen.h	3.1  10/29/86
E 6
I 6
D 8
 * %W% (Berkeley) %G%
E 8
I 8
 * Copyright (c) 1988 Regents of the University of California.
E 12
I 12
/*-
D 13
 * Copyright (c) 1988 The Regents of the University of California.
E 12
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 9
 *
 *	%W% (Berkeley) %G%
E 8
E 6
 */

#define	INCLUDED_TERMINAL

D 5
#if	defined(SLOWSCREEN)

E 5
/*
 * In the situation where we have a copy of the terminal screen in front
 * of us, here are some macros to deal with them.
 */

D 2
#define TermAttributes(x)	(TermIsStartField(x)? Terminal[x].field&0xff : \
				    Terminal[WhereTermAttrByte(x)].field&0xff)
#define TermIsStartField(x)	(Terminal[x].field&ATTR_MASK)
#define TermNewField(p,a)	(Terminal[p].field = (a)|ATTR_MASK)
#define TermDeleteField(p)	(Terminal[p].field = 0)
E 2
I 2
D 3
#define TermAttributes(x)	(TermIsStartField(x)? Terminal[x].data&0xff : \
				    Terminal[WhereTermAttrByte(x)].data&0xff)
#define TermIsStartField(x)	(Terminal[x].data&ATTR_MASK)
#define TermNewField(p,a)	(Terminal[p].data = (a)|ATTR_MASK)
#define TermDeleteField(p)	(Terminal[p].data = 0)
E 3
I 3
#define TermAttributes(x)	(TermIsStartField(x)? GetTerminal(x)&0xff : \
				    GetTerminal(WhereTermAttrByte(x))&0xff)
D 4
#define TermIsStartField(x)	(GetTerminal(x)&ATTR_MASK)
E 4
I 4
#define TermIsStartField(x)	((GetTerminal(x)&ATTR_MASK) == ATTR_MASK)
E 4
#define TermNewField(p,a)	SetTerminal(p, (a)|ATTR_MASK)
#define TermDeleteField(p)	SetTerminal(p, 0)
E 3
E 2
#define TermIsNonDisplay(x)	\
		    ((TermAttributes(x)&ATTR_DSPD_MASK) == ATTR_DSPD_NONDISPLAY)
#define TermIsHighlighted(x) \
		(((TermAttributes(x)&ATTR_DSPD_MASK) == ATTR_DSPD_HIGH) \
				    && !TermIsStartField(x))

#define TerminalCharacterAttr(c,p,a)	(IsNonDisplayAttr(a) ? ' ':c)
#define TerminalCharacter(c,p)	TerminalCharacterAttr(c,p,FieldAttributes(p))

I 11
	/*
	 * Is the screen formatted?  Some algorithms change depending
	 * on whether there are any attribute bytes lying around.
	 */
#define	TerminalFormattedScreen() \
	    ((WhereTermAttrByte(0) != 0) || ((GetTerminal(0)&ATTR_MASK) == ATTR_MASK))

E 11
#define NeedToRedisplayFields(p) ((TermIsNonDisplay(p) != IsNonDisplay(p)) || \
				(TermIsHighlighted(p) != IsHighlighted(p)))
#define NeedToRedisplayFieldsAttr(p,c) ( \
			(TermIsNonDisplay(p) != IsNonDisplayAttr(c)) || \
			(TermIsHighlighted(p) != IsHighlightedAttr(c)))

#define NotVisuallyCompatibleAttributes(p,c,d) ( \
			(IsNonDisplayAttr(c) != IsNonDisplayAttr(d)) || \
			(IsHighlightedAttr(c) != IsHighlightedAttr(d)))

#define NeedToRedisplayAttr(c,p,a) \
			((c != GetTerminal(p)) || NeedToRedisplayFieldsAttr(p,a))
#define NeedToRedisplay(c,p)	NeedToRedisplayAttr(c,p,FieldAttributes(p))

D 3
#define GetTerminal(i)		Terminal[i].data
#define SetTerminal(i,c)	(Terminal[i].data = c)

E 3
D 5
#endif	/* defined(SLOWSCREEN) */
E 5
I 3

#define GetTerminal(i)		GetGeneric(i, Terminal)
#define GetTerminalPointer(p)	GetGenericPointer(p)
#define SetTerminal(i,c)	SetGeneric(i,c,Terminal)
E 3
E 1
