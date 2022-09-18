h14010
s 00002/00002/00136
d D 8.1 93/05/31 15:55:34 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00136
d D 5.3 93/05/13 17:03:57 bostic 5 4
c lint from JG
e
s 00017/00009/00119
d D 5.2 93/05/12 14:04:08 bostic 4 3
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00013/00004/00115
d D 5.1 91/04/08 17:08:15 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00119
d D 4.1 82/05/11 14:41:41 rrh 2 1
c release version 4.1
e
s 00119/00000/00000
d D 1.1 82/05/11 14:35:23 rrh 1 0
c date and time created 82/05/11 14:35:23 by rrh
e
u
U
t
T
I 1
D 3
#
E 3
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
E 4
I 4
D 6
 * Copyright (c) 1991, 1993 The Regents of the University of California.
E 4
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
 * The game adventure was original written Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by
 * Jim Gillogly.
E 4
I 4
 * The game adventure was originally written in Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by Jim
 * Gillogly.  This code is derived from software contributed to Berkeley
 * by Jim Gillogly at The Rand Corporation.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
/*   ADVENTURE -- Jim Gillogly, Jul 1977
 * This program is a re-write of ADVENT, written in FORTRAN mostly by
 * Don Woods of SAIL.  In most places it is as nearly identical to the
 * original as possible given the language and word-size differences.
 * A few places, such as the message arrays and travel arrays were changed
 * to reflect the smaller core size and word size.  The labels of the
 * original are reflected in this version, so that the comments of the
 * fortran are still applicable here.
 *
 * The data file distributed with the fortran source is assumed to be called
 * "glorkz" in the directory where the program is first run.
 */

D 3
static char hdr_sccsid[] = "	%M%	%I%	%E%	";

/*  hdr.h */
E 3
/* hdr.h: included by c advent files */

D 4
extern int setup;                       /* changed by savec & init      */
E 4
int datfd;                              /* message file descriptor      */
int delhit;
int yea;
I 4
extern char data_file[];                /* Virtual data file            */
E 4

#define TAB     011
#define LF      012
#define FLUSHLINE while (getchar()!='\n')
#define FLUSHLF   while (next()!=LF)

D 4
int loc,newloc,oldloc,oldlc2,wzdark,SHORT,gaveup,kq,k,k2;
E 4
I 4
int loc,newloc,oldloc,oldlc2,wzdark,gaveup,kq,k,k2;
E 4
char *wd1,*wd2;                         /* the complete words           */
int verb,obj,spk;
extern int blklin;
int saved,savet,mxscor,latncy;

I 4
#define SHORT 50                        /* How short is a demo game?    */

E 4
#define MAXSTR  20                      /* max length of user's words   */

#define HTSIZE  512                     /* max number of vocab words    */
struct hashtab                          /* hash table for vocabulary    */
{       int val;                        /* word type &index (ktab)      */
	char *atab;                     /* pointer to actual string     */
} voc[HTSIZE];

D 4
#define DATFILE "glorkz"                /* all the original msgs        */
#define TMPFILE "tmp.foo.baz"           /* just the text msgs           */
E 4
I 4
#define SEED 1815622                    /* "Encryption" seed            */
E 4

D 4

E 4
struct text
I 4
#ifdef OLDSTUFF
E 4
{       int seekadr;                    /* DATFILE must be < 2**16      */
I 4
#endif OLDSTUFF
{       char *seekadr;                  /* Msg start in virtual disk    */
E 4
	int txtlen;                     /* length of msg starting here  */
};

#define RTXSIZ  205
struct text rtext[RTXSIZ];              /* random text messages         */

#define MAGSIZ  35
struct text mtext[MAGSIZ];              /* magic messages               */

int clsses;
#define CLSMAX  12
struct text ctext[CLSMAX];              /* classes of adventurer        */
int cval[CLSMAX];

struct text ptext[101];                 /* object descriptions          */

#define LOCSIZ  141                     /* number of locations          */
struct text ltext[LOCSIZ];              /* long loc description         */
struct text stext[LOCSIZ];              /* short loc descriptions       */

struct travlist                         /* direcs & conditions of travel*/
{       struct travlist *next;          /* ptr to next list entry       */
	int conditions;                 /* m in writeup (newloc / 1000) */
	int tloc;                       /* n in writeup (newloc % 1000) */
	int tverb;                      /* the verb that takes you there*/
} *travel[LOCSIZ],*tkk;                 /* travel is closer to keys(...)*/

int atloc[LOCSIZ];

int  plac[101];                         /* initial object placement     */
int  fixd[101],fixed[101];              /* location fixed?              */

int actspk[35];                         /* rtext msg for verb <n>       */

int cond[LOCSIZ];                       /* various condition bits       */

extern int setbit[16];                  /* bit defn masks 1,2,4,...     */

int hntmax;
int hints[20][5];                       /* info on hints                */
int hinted[20],hintlc[20];

int place[101], prop[101],link[201];
int abb[LOCSIZ];

int maxtrs,tally,tally2;                /* treasure values              */

#define FALSE   0
#define TRUE    1

int keys,lamp,grate,cage,rod,rod2,steps,/* mnemonics                    */
	bird,door,pillow,snake,fissur,tablet,clam,oyster,magzin,
	dwarf,knife,food,bottle,water,oil,plant,plant2,axe,mirror,dragon,
	chasm,troll,troll2,bear,messag,vend,batter,
	nugget,coins,chest,eggs,tridnt,vase,emrald,pyram,pearl,rug,chain,
	spices,
	back,look,cave,null,entrnc,dprssn,
I 4
	enter, stream, pour,
E 4
	say,lock,throw,find,invent;

int chloc,chloc2,dseen[7],dloc[7],      /* dwarf stuff                  */
	odloc[7],dflag,daltlc;

int tk[21],stick,dtotal,attack;
int turns,lmwarn,iwest,knfloc,detail,   /* various flags & counters     */
	abbnum,maxdie,numdie,holdng,dkill,foobar,bonus,clock1,clock2,
	saved,closng,panic,closed,scorng;

int demo,newloc,limit;

char *malloc();
I 5
char *decr();
unsigned long crc();
E 5
I 4

/* We need to get a little tricky to avoid strings */
#define DECR(a,b,c,d,e) decr('a'+'+','b'+'-','c'+'#','d'+'&','e'+'%')
E 4
E 1
