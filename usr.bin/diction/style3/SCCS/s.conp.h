h20840
s 00000/00000/00020
d D 8.1 93/06/06 14:35:35 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00015
d D 4.4 91/04/17 17:17:41 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00003/00014
d D 4.3 83/08/11 20:30:31 sam 3 2
c standardize sccs keyword lines
e
s 00001/00000/00016
d D 4.2 82/11/06 14:31:54 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00016/00000/00000
d D 4.1 82/11/06 13:47:30 rrh 1 0
c Oldest available version at Berkeley
e
u
U
t
T
I 1
D 3
/*
 *	%W%	(Berkeley)	%E%
 */
E 3
I 3
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 4

E 3
#define SLENG 250
#define SCHAR 1500
extern struct ss {char *sp,ic,cc; int leng;} sent[SLENG];
extern struct ss *sentp;
extern comma,j,i;
I 2
extern int nsleng;
E 2
extern question;
int must;
int be;
int sav;
int prep;
int aflg,bflg,subty,verb,verbty;
int hflg;
int iverb,pverb,done;
E 1
