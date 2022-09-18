h20706
s 00002/00002/00117
d D 8.1 93/06/06 16:40:24 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00116
d D 4.3 91/04/26 15:40:55 bostic 13 12
c new copyright; att/bsd/shared
e
s 00000/00004/00129
d D 4.2 89/02/06 19:06:41 minshall 12 11
c Remove unused #define's.
e
s 00000/00000/00133
d D 4.1 88/12/04 15:11:45 minshall 11 10
c Release 4.1
e
s 00010/00005/00123
d D 3.4 88/06/29 19:50:00 bostic 10 9
c install approved copyright notice
e
s 00011/00001/00117
d D 3.3 88/03/28 12:34:32 bostic 9 8
c add Berkeley specific header
e
s 00021/00003/00097
d D 3.2 88/03/17 21:17:31 minshall 8 7
c Fix bug where, on an unformatted screen, we were changing the
c character at location zero on the screen.  Reported by Ed Jankawski at
c Boston U. and by Greg Small and Mike Friedman at UC Berkeley - both
c groups bitten because of CICS using unformatted screens!
e
s 00000/00000/00100
d D 3.1 87/08/11 10:18:33 minshall 7 6
c New version numbering.
e
s 00001/00001/00099
d D 1.6 87/07/17 10:03:04 minshall 6 5
c Install sccs headers and copyright notices.
e
s 00023/00017/00077
d D 1.5 87/05/18 15:57:10 minshall 5 4
c Various changes to make 'Host' structure changeable
c (and, make it a 'char' for the MSDOS world).
e
s 00006/00000/00088
d D 1.4 87/05/18 09:55:35 minshall 4 3
c Reduce memory requirements for DOS version.
e
s 00003/00011/00085
d D 1.3 87/05/10 13:01:05 minshall 3 2
c Get rid of FieldForward, FieldReverse.
e
s 00016/00012/00080
d D 1.2 86/11/12 17:16:30 minshall 2 1
c This version has the attribute bytes inline (3278 style).
e
s 00092/00000/00000
d D 1.1 86/11/11 22:54:17 minshall 1 0
c date and time created 86/11/11 22:54:17 by minshall
e
u
U
t
T
I 1
D 13
/*
D 6
 *	@(#)screen.h	3.1  10/29/86
E 6
I 6
D 9
 * %W% (Berkeley) %G%
E 9
I 9
 * Copyright (c) 1988 Regents of the University of California.
E 13
I 13
/*-
D 14
 * Copyright (c) 1988 The Regents of the University of California.
E 13
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 10
 *
 *	%W% (Berkeley) %G%
E 9
E 6
 */

#define	INCLUDED_SCREEN

/* defines and defines to describe how to deal with the screen */

I 4
#if	!defined(MSDOS)
E 4
#define	MAXNUMBERLINES		43		/* 3278-4 */
#define	MAXNUMBERCOLUMNS	132		/* 3278-5 */
#define	MAXSCREENSIZE		3564		/* (27*132) 3278-5 */
I 4
#else	/* !defined(MSDOS) */	/* MSDOS has memory constraints */
#define	MAXNUMBERLINES		25		/* XXX */
#define	MAXNUMBERCOLUMNS	80
#define	MAXSCREENSIZE		(MAXNUMBERLINES*MAXNUMBERCOLUMNS)
#endif	/* !defined(MSDOS) */	/* MSDOS has memory constraints */
E 4
#define LowestScreen()	0
#define HighestScreen()	(ScreenSize-1)

#define ScreenLineOffset(x)	((x)%NumberColumns)
#define ScreenLine(x)	((int)((x)/NumberColumns))
#define ScreenInc(x)	(((x)==HighestScreen())? LowestScreen():x+1)
#define ScreenDec(x)	(((x)==LowestScreen())? HighestScreen():x-1)
#define ScreenUp(x)	(((x)+(ScreenSize-NumberColumns))%ScreenSize)
#define ScreenDown(x)	(((x)+NumberColumns)%ScreenSize)
#define	IsOrder(x)	(Orders[x])
#define BAIC(x)		((x)&0x3f)
#define CIAB(x)		(CIABuffer[(x)&0x3f])
#define BufferTo3270_0(x)	(CIABuffer[(int)((x)/0x40)])
#define BufferTo3270_1(x)	(CIABuffer[(x)&0x3f])
#define Addr3270(x,y)	(BAIC(x)*64+BAIC(y))
#define SetBufferAddress(x,y)	((x)*NumberColumns+(y))

/* These know how fields are implemented... */

D 3
#define	FieldInc(p)	FieldFind(FieldForward, p, LowestScreen())
#define	FieldDec(p)	(HighestScreen() - \
				FieldFind(FieldReverse, \
D 2
					HighestScreen()-p, HighestScreen()))
E 2
I 2
					HighestScreen()-(p), HighestScreen()))
E 3
E 2
#define WhereAttrByte(p)	(IsStartField(p)? p: FieldDec(p))
#define	WhereHighByte(p)	ScreenDec(FieldInc(p))
#define WhereLowByte(p)		ScreenInc(WhereAttrByte(p))
D 2
#define FieldAttributes(x)	(IsStartField(x)? Host[x].field&0xff : \
				    Host[WhereAttrByte(x)].field&0xff)
#define TurnOffMdt(x)	(Host[WhereAttrByte(x)].field &= ~ATTR_MDT)
#define TurnOnMdt(x)	(Host[WhereAttrByte(x)].field |= ATTR_MDT)
#define HasMdt(x)	(Host[x].field&ATTR_MDT)	/* modified tag */
E 2
I 2
D 5
#define FieldAttributes(x)	(IsStartField(x)? Host[x].data : \
				    Host[WhereAttrByte(x)].data)
#define FieldAttributesPointer(p)	(IsStartFieldPointer(p)? (p)->data : \
				    Host[WhereAttrByte((p)-&Host[0])].data)
#define TurnOffMdt(x)	(Host[WhereAttrByte(x)].data &= ~ATTR_MDT)
#define TurnOnMdt(x)	(Host[WhereAttrByte(x)].data |= ATTR_MDT)
#define HasMdt(x)	(Host[x].data&ATTR_MDT)	/* modified tag */
E 5
I 5
#define FieldAttributes(x)	(IsStartField(x)? GetHost(x) : \
				    GetHost(WhereAttrByte(x)))
#define FieldAttributesPointer(p)	(IsStartFieldPointer(p)? \
				    GetHostPointer(p): \
				    GetHost(WhereAttrByte((p)-&Host[0])))
D 8
#define TurnOffMdt(x)	ModifyHost(WhereAttrByte(x), &= ~ATTR_MDT)
#define TurnOnMdt(x)	ModifyHost(WhereAttrByte(x), |= ATTR_MDT)
#define HasMdt(x)	(GetHost(x)&ATTR_MDT)	/* modified tag */
E 8
I 8

/*
 * The MDT functions need to protect against the case where the screen
 * is unformatted (sigh).
 */

/* Turn off the Modified Data Tag */
#define TurnOffMdt(x) \
    if (HasMdt(WhereAttrByte(x))) { \
	ModifyMdt(x, 0); \
    }

/* Turn on the Modified Data Tag */
#define TurnOnMdt(x) \
    if (!HasMdt(WhereAttrByte(x))) { \
	ModifyMdt(x, 1); \
    }

/* If this location has the MDT bit turned on (implies start of field) ... */
#define HasMdt(x) \
    ((GetHost(x)&(ATTR_MDT|ATTR_MASK)) == (ATTR_MDT|ATTR_MASK))
E 8
E 5
E 2

	/*
	 * Is the screen formatted?  Some algorithms change depending
	 * on whether there are any attribute bytes lying around.
	 */
#define	FormattedScreen() \
D 2
	    ((WhereAttrByte(0) != 0) || ((Host[0].field&ATTR_MASK) != 0))
E 2
I 2
D 5
	    ((WhereAttrByte(0) != 0) || ((Host[0].data&ATTR_MASK) == ATTR_MASK))
E 5
I 5
	    ((WhereAttrByte(0) != 0) || ((GetHost(0)&ATTR_MASK) == ATTR_MASK))
E 5
E 2

D 2
#define IsStartField(x)	(Host[x].field&ATTR_MASK)	/* field starts here */
#define NewField(p,a)	(Host[p].field = (a)|ATTR_MASK, \
E 2
I 2
					    /* field starts here */
D 5
#define IsStartField(x)	((Host[x].data&ATTR_MASK) == ATTR_MASK)
#define IsStartFieldPointer(p)	(((p)->data&ATTR_MASK) == ATTR_MASK)
E 5
I 5
#define IsStartField(x)	((GetHost(x)&ATTR_MASK) == ATTR_MASK)
#define IsStartFieldPointer(p)	((GetHostPointer(p)&ATTR_MASK) == ATTR_MASK)
E 5

D 3
#define NewField(p,a)	(Host[p].data = (a)|ATTR_MASK, \
E 2
			    FieldForward[p] = FieldReverse[ScreenSize-p-1] = 1)
D 2
#define DeleteField(p)	(Host[p].field = 0, \
E 2
I 2
#define DeleteField(p)	(Host[p].data = 0, \
E 2
			    FieldForward[p] = FieldReverse[ScreenSize-p-1] = 0)
#define	DeleteAllFields()	(bzero(FieldForward, sizeof FieldForward), \
				    bzero(FieldReverse, sizeof FieldReverse))

E 3
I 3
D 5
#define NewField(p,a)	(Host[p].data = (a)|ATTR_MASK)
#define DeleteField(p)	(Host[p].data = 0)
E 5
I 5
#define NewField(p,a)	SetHost(p, (a)|ATTR_MASK)
#define DeleteField(p)	SetHost(p, 0)
E 5
#define	DeleteAllFields()
E 3

/* The following are independent of the implementation of fields */
#define IsProtectedAttr(p,a)	(IsStartField(p) || ((a)&ATTR_PROT))
#define IsProtected(p)	IsProtectedAttr(p,FieldAttributes(p))

#define IsUnProtected(x)	(!IsProtected(x))

#define IsAutoSkip(x)	(FieldAttributes(x)&ATTR_AUTO_SKIP)

#define IsNonDisplayAttr(c)	(((c)&ATTR_DSPD_MASK) == ATTR_DSPD_NONDISPLAY)
#define	IsNonDisplay(p)	IsNonDisplayAttr(FieldAttributes(p))

#define IsHighlightedAttr(c) \
		(((c)&ATTR_DSPD_MASK) == ATTR_DSPD_HIGH)
#define	IsHighlighted(p) \
		(IsHighlightedAttr(FieldAttributes(p)) && !IsStartField(p))

D 12

#define MAX(x,y)	((x)<(y)? (y):(x))
#define MIN(x,y)	((x)<(y)? x:(y))

E 12
D 5
typedef struct {
D 2
	unsigned char	data,	/* data at this position */
			field;	/* field attributes if ATTR_MASK */
E 2
I 2
	unsigned char	data;	/* data at this position */
E 2
} ScreenImage;
E 5
I 5
typedef unsigned char ScreenImage;
E 5

extern int
	FieldFind();

extern char
	CIABuffer[];

D 5
#define GetHost(i)	Host[i].data
#define SetHost(p,c)	(Host[p].data = c)
E 5
I 5
#define	GetGeneric(i,h)		(h)[i]
#define	GetGenericPointer(p)	(*(p))
#define	SetGeneric(i,c,h)	((h)[i] = (c))
#define	ModifyGeneric(i,what,h)	{(h)[i] what;}

#define GetHost(i)		GetGeneric(i,Host)
#define GetHostPointer(p)	GetGenericPointer(p)
#define	SetHost(i,c)		SetGeneric(i,c,Host)
#define	ModifyHost(i,what)	ModifyGeneric(i,what,Host)
E 5
E 1
