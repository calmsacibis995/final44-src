h33541
s 00007/00007/00030
d D 4.5 90/11/16 12:53:03 torek 5 4
c raise those sizes again, for X11R4 -- I doubled everything
c and fixed MAXSCOPES not to depend on TREESZ
e
s 00002/00002/00035
d D 4.4 90/02/21 17:42:29 mckusick 4 3
c raise the static sizes for X11
e
s 00001/00000/00036
d D 4.3 85/08/22 19:03:53 mckusick 3 2
c update from donn@utah-cs
e
s 00003/00003/00033
d D 4.2 85/04/08 11:47:16 ralph 2 1
c move ONEPASS definition so lint will compile.
e
s 00036/00000/00000
d D 4.1 85/03/19 13:01:22 ralph 1 0
c date and time created 85/03/19 13:01:22 by ralph
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

#ifndef _CONFIG_
#define	_CONFIG_
/*
 * Compiler configuration definitions.
 */

/*
 * These flags control global compiler operation.
 */
D 2
#ifndef FORT
#define	ONEPASS		1		/* one-pass compiler */
#endif
E 2
#define	BUFSTDERR	1		/* buffer output to stderr */
#define STDPRTREE	1		/* means include prtree */
#define NESTCALLS	1		/* disallow two concurrent store()'s */
#define	FLEXNAMES	1		/* arbitrary length identifiers */
I 2
#ifdef FORT
#define	NOMAIN		1		/* use f1 main routine */
#endif
E 2

/*
 * Table sizes.
 */
D 5
#define TREESZ		1000		/* parse tree table size */
#define BCSZ		100		/* break/continue table size */
D 4
#define SYMTSZ		3000		/* symbol table size */
#define DIMTABSZ 	4200		/* dimension/size table size */
E 4
I 4
#define SYMTSZ		4000		/* symbol table size */
#define DIMTABSZ 	5000		/* dimension/size table size */
E 4
#define PARAMSZ		300		/* parameter stack size */
#define SWITSZ		500		/* switch table size */
E 5
I 5
#define TREESZ		2000		/* parse tree table size */
#define BCSZ		200		/* break/continue table size */
#define SYMTSZ		8000		/* symbol table size */
#define DIMTABSZ 	10000		/* dimension/size table size */
#define PARAMSZ		600		/* parameter stack size */
#define SWITSZ		1000		/* switch table size */
E 5
#define	DELAYS		20		/* delayed evaluation table size */
#define NRECUR		(10*TREESZ)	/* maximum eval recursion depth */
I 3
D 5
#define	MAXSCOPES	(SYMTSZ/30)	/* maximum active scopes */
E 5
I 5
#define	MAXSCOPES	200		/* maximum active scopes ('{' depth) */
E 5
E 3

/* in case anyone still uses fixed length names */
#ifndef FLEXNAMES
#define	NCHNAM		8		/* significant chars of identifier */
#endif
#endif
E 1
