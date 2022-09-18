h12112
s 00000/00000/00045
d D 8.1 93/06/06 16:29:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00040
d D 4.3 91/04/16 16:48:32 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00003/00039
d D 4.2 83/08/11 21:07:24 sam 2 1
c standardize sccs keyword lines
e
s 00042/00000/00000
d D 4.1 83/02/11 15:44:10 rrh 1 0
c date and time created 83/02/11 15:44:10 by rrh
e
u
U
t
T
I 1
D 2
/*
 *	%W%	(Berkeley)	%E%
 */
E 2
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

E 2
#define maxlsw		10	/* max number of switches and labels per statement */
#define implicit 0L		/* "label" of following line so all flow can be treated as jump to label */
struct lablist	{long labelt;  struct lablist *nxtlab; };
extern struct lablist *endlab, *errlab, *reflab, *linelabs, *newlab;
extern long label();

extern int routbeg;			/* line number of first line of routine */
extern int nameline;			/* line number of function/subroutine st., if any */
extern int stflag;		/* determines whether at beginning or middle of block of straight line code */



extern char buffer[];
extern int endbuf;

extern int   nlabs, lswnum, swptr, flag,
	 counter, p1, p3, begline, endline, r1,r2, endcom;
extern long begchar, endchar, comchar;


/* statement types not associated with actual node types */
#define contst		-1
#define ungo		-2
#define arithif		-3
#define readst		-8
#define writest		-9
#define entry	-10


extern char *pred, *inc, *prerw, *postrw, *exp, *stcode;

#define maxdo	20	/* max nesting of do loops */
extern long dostack[maxdo];		/* labels of do nodes */
extern int doloc[maxdo];		/* loc of do node */
extern int doptr;


extern struct list *FMTLST;		/* list of FMTVX's generated */
extern struct list *ENTLST;		/* list of STLNVX nodes corresponding to entry statements */
E 1
