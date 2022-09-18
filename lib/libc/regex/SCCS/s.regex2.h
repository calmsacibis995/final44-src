h17004
s 00001/00001/00146
d D 8.4 94/03/20 14:35:08 bostic 6 5
c delete UofT; requested change from Henry Spencer <henry@zoo.toronto.edu>
e
s 00013/00013/00134
d D 8.3 94/03/16 12:43:02 bostic 5 4
c alpha3.3
e
s 00001/00000/00146
d D 8.2 94/01/02 14:30:41 bostic 4 3
c Henry Spencer's fix for end-of-word matching
c Word matching considers '_' to terminate a word, i.e. vm_page_free\>
c matches vm_page_free_count.  This isn't historic vi practice.
e
s 00002/00002/00144
d D 8.1 93/06/04 12:58:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00009/00111
d D 5.2 93/05/21 16:06:55 bostic 2 1
c Henry Spencer's Alpha 3.0 regex release
e
s 00120/00000/00000
d D 5.1 92/08/06 11:58:10 bostic 1 0
c date and time created 92/08/06 11:58:10 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 Henry Spencer.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
E 5
I 5
 * Copyright (c) 1992, 1993, 1994 Henry Spencer.
 * Copyright (c) 1992, 1993, 1994
E 5
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
D 6
 * Henry Spencer of the University of Toronto.
E 6
I 6
 * Henry Spencer.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
I 2
 * First, the stuff that ends up in the outside-world include file
 = typedef off_t regoff_t;
 = typedef struct {
 = 	int re_magic;
 = 	size_t re_nsub;		// number of parenthesized subexpressions
D 5
 =	const char *re_endp;	// end pointer for REG_PEND
E 5
I 5
 = 	const char *re_endp;	// end pointer for REG_PEND
E 5
 = 	struct re_guts *re_g;	// none of your business :-)
 = } regex_t;
 = typedef struct {
 = 	regoff_t rm_so;		// start of match
 = 	regoff_t rm_eo;		// end of match
 = } regmatch_t;
 */
/*
E 2
 * internals of regex_t
 */
#define	MAGIC1	((('r'^0200)<<8) | 'e')

/*
 * The internal representation is a *strip*, a sequence of
 * operators ending with an endmarker.  (Some terminology etc. is a
 * historical relic of earlier versions which used multiple strips.)
 * Certain oddities in the representation are there to permit running
 * the machinery backwards; in particular, any deviation from sequential
 * flow must be marked at both its source and its destination.  Some
 * fine points:
 *
 * - OPLUS_ and O_PLUS are *inside* the loop they create.
 * - OQUEST_ and O_QUEST are *outside* the bypass they create.
 * - OCH_ and O_CH are *outside* the multi-way branch they create, while
 *   OOR1 and OOR2 are respectively the end and the beginning of one of
 *   the branches.  Note that there is an implicit OOR2 following OCH_
 *   and an implicit OOR1 preceding O_CH.
 *
 * In state representations, an operator's bit is on to signify a state
 * immediately *preceding* "execution" of that operator.
 */
typedef unsigned long sop;	/* strip operator */
typedef long sopno;
#define	OPRMASK	0xf8000000
#define	OPDMASK	0x07ffffff
D 2
#define	OPSHIFT	27
E 2
I 2
#define	OPSHIFT	((unsigned)27)
E 2
#define	OP(n)	((n)&OPRMASK)
#define	OPND(n)	((n)&OPDMASK)
#define	SOP(op, opnd)	((op)|(opnd))
/* operators			   meaning	operand			*/
/*						(back, fwd are offsets)	*/
#define	OEND	(1<<OPSHIFT)	/* endmarker	-			*/
#define	OCHAR	(2<<OPSHIFT)	/* character	unsigned char		*/
#define	OBOL	(3<<OPSHIFT)	/* left anchor	-			*/
#define	OEOL	(4<<OPSHIFT)	/* right anchor	-			*/
#define	OANY	(5<<OPSHIFT)	/* .		-			*/
#define	OANYOF	(6<<OPSHIFT)	/* [...]	set number		*/
#define	OBACK_	(7<<OPSHIFT)	/* begin \d	paren number		*/
#define	O_BACK	(8<<OPSHIFT)	/* end \d	paren number		*/
#define	OPLUS_	(9<<OPSHIFT)	/* + prefix	fwd to suffix		*/
#define	O_PLUS	(10<<OPSHIFT)	/* + suffix	back to prefix		*/
#define	OQUEST_	(11<<OPSHIFT)	/* ? prefix	fwd to suffix		*/
#define	O_QUEST	(12<<OPSHIFT)	/* ? suffix	back to prefix		*/
#define	OLPAREN	(13<<OPSHIFT)	/* (		fwd to )		*/
#define	ORPAREN	(14<<OPSHIFT)	/* )		back to (		*/
#define	OCH_	(15<<OPSHIFT)	/* begin choice	fwd to OOR2		*/
#define	OOR1	(16<<OPSHIFT)	/* | pt. 1	back to OOR1 or OCH_	*/
#define	OOR2	(17<<OPSHIFT)	/* | pt. 2	fwd to OOR2 or O_CH	*/
#define	O_CH	(18<<OPSHIFT)	/* end choice	back to OOR1		*/
I 2
#define	OBOW	(19<<OPSHIFT)	/* begin word	-			*/
#define	OEOW	(20<<OPSHIFT)	/* end word	-			*/
E 2

/*
 * Structure for [] character-set representation.  Character sets are
 * done as bit vectors, grouped 8 to a byte vector for compactness.
 * The individual set therefore has both a pointer to the byte vector
 * and a mask to pick out the relevant bit of each byte.  A hash code
 * simplifies testing whether two sets could be identical.
 *
 * This will get trickier for multicharacter collating elements.  As
 * preliminary hooks for dealing with such things, we also carry along
 * a string of multi-character elements, and decide the size of the
 * vectors at run time.
 */
typedef struct {
D 5
	uchar *ptr;		/* -> uchar [csetsize] */
	uchar mask;		/* bit within array */
	uchar hash;		/* hash code */
E 5
I 5
	uch *ptr;		/* -> uch [csetsize] */
	uch mask;		/* bit within array */
	uch hash;		/* hash code */
E 5
	size_t smultis;
D 2
	uchar *multis;		/* -> uchar[smulti]  ab\0cd\0ef\0\0 */
E 2
I 2
	char *multis;		/* -> char[smulti]  ab\0cd\0ef\0\0 */
E 2
} cset;
/* note that CHadd and CHsub are unsafe, and CHIN doesn't yield 0/1 */
D 2
#define	CHadd(cs, c)	((cs)->ptr[(c)] |= (cs)->mask, (cs)->hash += (c))
#define	CHsub(cs, c)	((cs)->ptr[(c)] &= ~(cs)->mask, (cs)->hash -= (c))
#define	CHIN(cs, c)	((cs)->ptr[(c)] & (cs)->mask)
#define	MCadd(cs, cp)	mcadd(p, cs, cp)	/* regcomp() internal fns */
#define	MCsub(cs, cp)	mcsub(p, cs, cp)
#define	MCin(cs, cp)	mcin(p, cs, cp)
E 2
I 2
D 5
#define	CHadd(cs, c)	((cs)->ptr[(uchar)(c)] |= (cs)->mask, (cs)->hash += (c))
#define	CHsub(cs, c)	((cs)->ptr[(uchar)(c)] &= ~(cs)->mask, (cs)->hash -= (c))
#define	CHIN(cs, c)	((cs)->ptr[(uchar)(c)] & (cs)->mask)
#define	MCadd(cs, cp)	mcadd(cs, cp)	/* regcomp() internal fns */
#define	MCsub(cs, cp)	mcsub(cs, cp)
#define	MCin(cs, cp)	mcin(cs, cp)
E 5
I 5
#define	CHadd(cs, c)	((cs)->ptr[(uch)(c)] |= (cs)->mask, (cs)->hash += (c))
#define	CHsub(cs, c)	((cs)->ptr[(uch)(c)] &= ~(cs)->mask, (cs)->hash -= (c))
#define	CHIN(cs, c)	((cs)->ptr[(uch)(c)] & (cs)->mask)
#define	MCadd(p, cs, cp)	mcadd(p, cs, cp)	/* regcomp() internal fns */
#define	MCsub(p, cs, cp)	mcsub(p, cs, cp)
#define	MCin(p, cs, cp)	mcin(p, cs, cp)
E 5
E 2

I 2
/* stuff for character categories */
typedef unsigned char cat_t;

E 2
/*
 * main compiled-expression structure
 */
struct re_guts {
	int magic;
#		define	MAGIC2	((('R'^0200)<<8)|'E')
	sop *strip;		/* malloced area for strip */
	int csetsize;		/* number of bits in a cset vector */
	int ncsets;		/* number of csets in use */
	cset *sets;		/* -> cset [ncsets] */
D 5
	uchar *setbits;		/* -> uchar[csetsize][ncsets/CHAR_BIT] */
E 5
I 5
	uch *setbits;		/* -> uch[csetsize][ncsets/CHAR_BIT] */
E 5
	int cflags;		/* copy of regcomp() cflags argument */
	sopno nstates;		/* = number of sops */
	sopno firststate;	/* the initial OEND (normally 0) */
	sopno laststate;	/* the final OEND */
	int iflags;		/* internal flags */
#		define	USEBOL	01	/* used ^ */
#		define	USEEOL	02	/* used $ */
#		define	BAD	04	/* something wrong */
I 2
	int nbol;		/* number of ^ used */
	int neol;		/* number of $ used */
E 2
	int ncategories;	/* how many character categories */
D 2
	uchar *categories;	/* -> uchar[NUC] */
E 2
I 2
	cat_t *categories;	/* ->catspace[-CHAR_MIN] */
E 2
	char *must;		/* match must contain this string */
	int mlen;		/* length of must */
	size_t nsub;		/* copy of re_nsub */
	int backrefs;		/* does it use back references? */
	sopno nplus;		/* how deep does it nest +s? */
I 2
	/* catspace must be last */
	cat_t catspace[1];	/* actually [NC] */
E 2
};
I 2

/* misc utilities */
#define	OUT	(CHAR_MAX+1)	/* a non-character value */
I 4
#define	ISWORD(c)	(isalnum(c) || (c) == '_')
E 4
E 2
E 1
