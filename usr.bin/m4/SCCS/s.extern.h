h51439
s 00002/00002/00068
d D 8.1 93/06/06 15:04:20 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00069
d D 5.3 91/11/20 16:27:09 bostic 3 2
c add affiliation for Oz
e
s 00002/00000/00068
d D 5.2 91/10/02 18:22:26 eric 2 1
c keep base of pushback buffer per file; this prevents pushed back
c characters from being read out of order on include directives.
e
s 00065/00000/00000
d D 5.1 91/09/03 11:41:45 bostic 1 0
c New version from Oz Yigit
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 3
 * Ozan Yigit.
E 3
I 3
 * Ozan Yigit at York University.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

char	*basename __P((char *));
char	*xalloc __P((unsigned long));
int	expr __P((char *));
ndptr	addent __P((char *));
void	chrsave __P((int));
void	dochc __P((char *[], int));
void	dochq __P((char *[], int));
void	dodefine __P((char *, char *));
void	dodefn __P((char *));
void	dodiv __P((int));
void	dodump __P((char *[], int));
void	doifelse __P((char *[], int));
int	doincl __P((char *));
int	dopaste __P((char *));
void	dopushdef __P((char *, char *));
void	dosub __P((char *[], int));
void	doundiv __P((char *[], int));
void	eval __P((char *[], int, int));
void	expand __P((char *[], int));
void	getdiv __P((int));
char	*xstrdup __P((const char *));
int	hash __P((char *));
int	indx __P((char *, char *));
void	killdiv __P((void));
ndptr	lookup __P((char *));
void	map __P((char *, char *, char *, char *));
void	onintr __P((int));
void	oops __P((const char *, ...));
void	pbnum __P((int));
void	pbstr __P((char *));
void	putback __P((int));
void	remhash __P((char *, int));
void	usage __P((void));

extern ndptr hashtab[];		/* hash table for macros etc. */
extern stae mstack[];		/* stack of m4 machine */
extern FILE *active;		/* active output file pointer */
extern FILE *infile[];		/* input file stack (0=stdin) */
extern FILE *outfile[];		/* diversion array(0=bitbucket) */
extern int fp; 			/* m4 call frame pointer */
extern int ilevel;		/* input file stack pointer */
extern int oindex;		/* diversion index. */
extern int sp;			/* current m4 stack pointer */
extern char *bp;		/* first available character */
extern char buf[];		/* push-back buffer */
I 2
extern char *bufbase;		/* buffer base for this ilevel */
extern char *bbase[];		/* buffer base per ilevel */
E 2
extern char ecommt;		/* end character for comment */
extern char *endest;		/* end of string space */
extern char *endpbb;		/* end of push-back buffer */
extern char *ep;		/* first free char in strspace */
extern char lquote;		/* left quote character (`) */
extern char *m4temp;		/* filename for diversions */
extern char *m4wraps;		/* m4wrap string default. */
extern char *null;		/* as it says.. just a null. */
extern char *progname;		/* program name */
extern char rquote;		/* right quote character (') */
extern char scommt;		/* start character for comment */
E 1
