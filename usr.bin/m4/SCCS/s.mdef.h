h42685
s 00002/00002/00148
d D 8.1 93/06/06 15:04:34 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00017/00149
d D 5.9 91/11/20 16:27:13 bostic 9 8
c add affiliation for Oz
e
s 00001/00001/00165
d D 5.8 91/10/02 18:22:24 eric 8 7
c keep base of pushback buffer per file; this prevents pushed back
c characters from being read out of order on include directives.
e
s 00010/00004/00156
d D 5.7 91/09/03 11:38:17 bostic 7 6
c New version from Oz Yigit; BSD-ized
e
s 00000/00005/00160
d D 5.6 91/02/26 14:05:43 bostic 6 5
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00164
d D 5.5 90/06/01 16:09:53 bostic 5 4
c new copyright notice
e
s 00002/00010/00173
d D 5.4 89/08/28 15:31:07 bostic 4 3
c move pathnames to pathnames.h
e
s 00000/00028/00183
d D 5.3 89/08/28 15:28:20 bostic 3 2
c remove vms defines
e
s 00000/00004/00211
d D 5.2 89/08/28 15:16:23 bostic 2 1
c remove void define
e
s 00215/00000/00000
d D 5.1 89/08/28 15:14:21 bostic 1 0
c date and time created 89/08/28 15:14:21 by bostic
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
D 9
 * Ozan Yigit.
E 9
I 9
 * Ozan Yigit at York University.
E 9
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 9
/*
 * mdef.h
 * Facility: m4 macro processor
 * by: oz
 */

I 7
#ifdef vms
#include stdio
#include ctype
#include signal
#endif

E 7
I 4
D 6
#include <sys/signal.h>
E 4
D 3
#ifndef unix
#define unix 0
#endif 

#ifndef vms
#define vms 0
#endif

#if vms

#include stdio
#include ctype
#include signal

#else 

E 3
#include <stdio.h>
#include <ctype.h>
D 4
#include <signal.h>
E 4
I 4
#include "pathnames.h"
E 4

E 6
D 3
#endif

E 3
/*
D 7
 *
E 7
 * m4 constants..
D 7
 *
E 7
 */
 
E 9
#define MACRTYPE        1
#define DEFITYPE        2
#define EXPRTYPE        3
#define SUBSTYPE        4
#define IFELTYPE        5
#define LENGTYPE        6
#define CHNQTYPE        7
#define SYSCTYPE        8
#define UNDFTYPE        9
#define INCLTYPE        10
#define SINCTYPE        11
#define PASTTYPE        12
#define SPASTYPE        13
#define INCRTYPE        14
#define IFDFTYPE        15
#define PUSDTYPE        16
#define POPDTYPE        17
#define SHIFTYPE        18
#define DECRTYPE        19
#define DIVRTYPE        20
#define UNDVTYPE        21
#define DIVNTYPE        22
#define MKTMTYPE        23
#define ERRPTYPE        24
#define M4WRTYPE        25
#define TRNLTYPE        26
#define DNLNTYPE        27
#define DUMPTYPE        28
#define CHNCTYPE        29
#define INDXTYPE        30
#define SYSVTYPE        31
#define EXITTYPE        32
#define DEFNTYPE        33
 
#define STATIC          128

/*
 * m4 special characters
 */
 
#define ARGFLAG         '$'
#define LPAREN          '('
#define RPAREN          ')'
#define LQUOTE          '`'
#define RQUOTE          '\''
#define COMMA           ','
#define SCOMMT          '#'
#define ECOMMT          '\n'
D 4

/*
 * definitions of diversion files. If the name of
 * the file is changed, adjust UNIQUE to point to the
 * wildcard (*) character in the filename.
 */

D 3
#if unix
E 3
#define DIVNAM  "/tmp/m4*XXXXXX"        /* unix diversion files    */
#define UNIQUE          7               /* unique char location    */
E 4
D 3
#else
#if vms
#define DIVNAM  "sys$login:m4*XXXXXX"   /* vms diversion files     */
#define UNIQUE          12              /* unique char location    */
#else
#define DIVNAM	"\M4*XXXXXX"		/* msdos diversion files   */
#define	UNIQUE	    3			/* unique char location    */
#endif
#endif
E 3

I 7
#ifdef msdos
#define system(str)	(-1)
#endif

E 7
/*
 * other important constants
 */

#define EOS             (char) 0
#define MAXINP          10              /* maximum include files   */
#define MAXOUT          10              /* maximum # of diversions */
#define MAXSTR          512             /* maximum size of string  */
#define BUFSIZE         4096            /* size of pushback buffer */
#define STACKMAX        1024            /* size of call stack      */
#define STRSPMAX        4096            /* size of string space    */
#define MAXTOK          MAXSTR          /* maximum chars in a tokn */
#define HASHSIZE        199             /* maximum size of hashtab */
 
#define ALL             1
#define TOP             0
 
#define TRUE            1
#define FALSE           0
#define cycle           for(;;)

D 2
#ifdef VOID
#define void            int             /* define if void is void. */
#endif

E 2
/*
 * m4 data structures
 */
 
typedef struct ndblock *ndptr;
 
struct ndblock {                /* hastable structure         */
        char    *name;          /* entry name..               */
        char    *defn;          /* definition..               */
        int     type;           /* type of the entry..        */
        ndptr   nxtptr;         /* link to next entry..       */
};
 
#define nil     ((ndptr) 0)
 
struct keyblk {
        char    *knam;          /* keyword name */
        int     ktyp;           /* keyword type */
};

typedef union {			/* stack structure */
	int	sfra;		/* frame entry  */
	char 	*sstr;		/* string entry */
} stae;

/*
 * macros for readibility and/or speed
 *
 *      gpbc()  - get a possibly pushed-back character
D 7
 *      min()   - select the minimum of two elements
E 7
 *      pushf() - push a call frame entry onto stack
 *      pushs() - push a string pointer onto stack
 */
D 8
#define gpbc() 	 (bp > buf) ? *--bp : getc(infile[ilevel])
E 8
I 8
#define gpbc() 	 (bp > bufbase) ? *--bp : getc(infile[ilevel])
E 8
D 7
#define min(x,y) ((x > y) ? y : x)
E 7
#define pushf(x) if (sp < STACKMAX) mstack[++sp].sfra = (x)
#define pushs(x) if (sp < STACKMAX) mstack[++sp].sstr = (x)

/*
 *	    .				   .
 *	|   .	|  <-- sp		|  .  |
 *	+-------+			+-----+
 *	| arg 3 ----------------------->| str |
 *	+-------+			|  .  |
 *	| arg 2 ---PREVEP-----+ 	   .
 *	+-------+	      |
 *	    .		      |		|     |
 *	+-------+	      | 	+-----+
 *	| plev	|  PARLEV     +-------->| str |
 *	+-------+			|  .  |
 *	| type	|  CALTYP		   .
 *	+-------+
 *	| prcf	---PREVFP--+
 *	+-------+  	   |
 *	|   .	|  PREVSP  |
 *	    .	   	   |
 *	+-------+	   |
 *	|	<----------+
 *	+-------+
 *
 */
#define PARLEV  (mstack[fp].sfra)
#define CALTYP  (mstack[fp-1].sfra)
#define PREVEP	(mstack[fp+3].sstr)
#define PREVSP	(fp-3)
#define PREVFP	(mstack[fp-2].sfra)
E 1
