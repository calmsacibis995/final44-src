h43889
s 00002/00002/00134
d D 8.1 93/06/06 15:11:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00131
d D 5.3 91/04/12 16:47:47 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00006/00135
d D 5.2 88/09/22 17:25:48 bostic 2 1
c fixes for ANSI C
e
s 00141/00000/00000
d D 5.1 85/04/29 18:36:51 mckusick 1 0
c date and time created 85/04/29 18:36:51 by mckusick
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1979 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

#include <stdio.h>
/*  MANIFEST CONSTANT DEFINITIONS */

# define NTBASE 010000

  /* internal codes for error and accept actions */

# define ERRCODE  8190
# define ACCEPTCODE 8191

# define errfileno stderr      /* file number for erros and reduction message */
# define _tbitset 6  /* 16*_tbitset - 1 >= _nterms */

extern int tbitset;  /* number of wds of lookahead vector */
extern int nolook;  /* flag to turn off lookahed computations */
struct looksets { int lset[ _tbitset ]; } ;
struct item { int *pitem; struct looksets *look; } ;

  /* output actions */

# define ERRACT 4096
# define SHIFTACT 8192
# define REDUCACT 12288
# define ACCEPTACT 16384

# define _REGISTER register

extern int nstate ;		/* number of states */
extern struct item *pstate[];	/* pointers to the descriptions of the states */
extern int apstate[];		/* index to actions in amem by state */
extern int actsiz;  	/* size of the action table array */
extern int tystate[];	/* contains type information about the states */
  /* 0 = simple state, completely generated
     1 = state awaiting generation
     2 = state with an empty production in closure 
     */
extern int stsize ;	/* maximum number of states, at present */
extern int memsiz ;	/* maximum size for productions and states */
extern int mem0[] ; /* added production */
extern int *mem ;
extern int amem[];  /* action table storage */
extern int actsiz;  /* action table size */
extern int memact ;		/* next free action table position */
extern int nprod ;	/* number of productions */
extern int *prdptr[];	/* pointers to descriptions of productions */
extern int prdlim; /* the number of productions allowed */
extern int levprd[] ;	/* contains production levels to break conflicts */
  /* last two bits code associativity:
       0 = no definition
       1 = left associative
       2 = binary
       3 = right associative
     bit 04 is 1 if the production has an action
     the high 13 bits have the production level
     */
extern int nterms ;	/* number of terminals */
extern int nerrors;	/* number of errors */
extern int fatfl;  	/* if on, error is fatal */
  /*	the ascii representations of the terminals	*/
extern int extval;  /* start of output values */
extern struct sxxx1 {char *name; int value;} trmset[];
extern char cnames[];
extern int cnamsz;
extern char *cnamp;
extern int maxtmp ;	/* the size of the temp arrays */
 /* temporary vectors, indexable by states, terms, or nterms */
extern int temp1[];
extern int temp2[];
extern int trmlev[];	/* vector with the precedence of the terminals */
  /* The levels are the same as for levprd, but bit 04 is always 0 */
  /* the ascii representations of the nonterminals */
extern struct sxxx2 { char *name; } nontrst[];
extern int indgo[];		/* index to the stored goto table */
extern int ***pres; /* vector of pointers to the productions yielding each nonterminal */
extern struct looksets **pfirst; /* vector of pointers to first sets for each nonterminal */
extern char *pempty; /* table of nonterminals nontrivially deriving e */
extern char stateflags[]; /* flags defining properties of a state (see below) */
#define GENLAMBDA   1	/* the state can nontrivially derive lambda */
#define SINGLE_NT   2	/* the state has a single nonterminal before its dot */
#define NEEDSREDUCE 4	/* the state needs a full reduce state generated */
extern struct looksets lastate[]; /* saved lookahead sets */
extern unsigned char lookstate[]; /* index mapping states to saved lookaheads */
extern int savedlook; /* number of saved lookahead sets used */
extern int maxlastate; /* maximum number of saved lookahead sets */
extern int nnonter ;	/* the number of nonterminals */
extern int lastred ;	/* the number of the last reduction of a state */
extern FILE *ftable;		/* y.tab.c file */
extern FILE *foutput;		/* y.output file */
extern FILE *cin;		/* current input file */
extern FILE *cout;		/* current output file */
extern int arrndx;
extern int zzcwset;
extern int zzpairs ;
extern int zzgoent ;
extern int zzgobest ;
extern int zzacent ;
extern int zzacsave ;
extern int zznsave ;
extern int zzclose ;
extern int zzrrconf ;
extern int zzsrconf ;
extern char *ctokn;
struct {int **ppi;} ;
extern int ntlim ;	/* maximum number of nonterminals */
extern int tlim ;	/* maximum number of terminals */
extern int lineno; /* current line number */
extern int peekc; /* look-ahead character */
extern int tstates[];
extern int ntstates[];
extern int mstates[];

extern struct looksets clset;
extern struct looksets lkst[];
extern int nlset;  /* next lookahead set index */
extern int lsetsz; /* number of lookahead sets */

extern struct wset { int *pitem, flag, ws[ _tbitset ]; } wsets[];
extern int cwset;
extern int wssize;
extern int lambdarule; /* index to rule that derives lambda */

extern int numbval;  /* the value of an input number */
extern int rflag;  /* ratfor flag */
extern int oflag;  /* optimization flag */
extern int ndefout;  /* number of defined symbols output */

D 2
extern int machine;

# define UNIX 1
# define GCOS 2
# define IBM 3

E 2
struct looksets *flset();
E 1
