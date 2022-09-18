h63173
s 00002/00002/00122
d D 8.1 93/06/06 14:30:28 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00123
d D 5.2 93/02/23 18:33:40 torek 6 5
c sqrt => dcsqrt for gcc2, ANSI
e
s 00008/00001/00116
d D 5.1 91/04/17 17:08:54 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00002/00116
d D 1.4 89/09/15 21:09:44 bostic 4 3
c POSIX signals
e
s 00000/00001/00118
d D 1.3 86/04/26 04:47:54 lepreau 3 2
c remove "compacting" free/realloc stuff
e
s 00002/00003/00117
d D 1.2 83/03/30 11:50:34 sam 2 1
c close to what sun sent up
e
s 00120/00000/00000
d D 1.1 83/02/11 15:02:12 rrh 1 0
c date and time created 83/02/11 15:02:12 by rrh
e
u
U
t
T
I 1
D 2
/*
 *	%W%	(Berkeley)	%G%
 */
E 2
I 2
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*-
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 5

E 2
#define FATAL 0
#define NFATAL 1
#define BLK sizeof(struct blk)
#define PTRSZ sizeof(int *)
#define HEADSZ 1024
#define STKSZ 100
#define RDSKSZ 100
#define TBLSZ 256
#define ARRAYST 0241
#define MAXIND 2048
#define NL 1
#define NG 2
#define NE 3
#define length(p) ((p)->wt-(p)->beg)
#define rewind(p) (p)->rd=(p)->beg
#define create(p)	(p)->rd = (p)->wt = (p)->beg
#define fsfile(p)	(p)->rd = (p)->wt
#define truncate(p)	(p)->wt = (p)->rd
#define sfeof(p)	(((p)->rd==(p)->wt)?1:0)
#define sfbeg(p)	(((p)->rd==(p)->beg)?1:0)
#define sungetc(p,c)	*(--(p)->rd)=c
#ifdef interdata
#define NEGBYTE 0200
#define MASK (-1 & ~0377)
#define sgetc(p)	( ((p)->rd==(p)->wt) ? EOF :( ((*(p)->rd & NEGBYTE) != 0) ? ( *(p)->rd++ | MASK): *(p)->rd++ ))
#define slookc(p)	( ((p)->rd==(p)->wt) ? EOF :( ((*(p)->rd & NEGBYTE) != 0) ? (*(p)->rd | MASK) : *(p)->rd ))
#define sbackc(p)	( ((p)->rd==(p)->beg) ? EOF :( ((*(--(p)->rd) & NEGBYTE) != 0) ? (*(p)->rd | MASK): *(p)->rd ))
#endif
#ifndef interdata
#define sgetc(p)	(((p)->rd==(p)->wt)?EOF:*(p)->rd++)
#define slookc(p)	(((p)->rd==(p)->wt)?EOF:*(p)->rd)
#define sbackc(p)	(((p)->rd==(p)->beg)?EOF:*(--(p)->rd))
#endif
#define sputc(p,c)	{if((p)->wt==(p)->last)more(p); *(p)->wt++ = c; }
#define salterc(p,c)	{if((p)->rd==(p)->last)more(p); *(p)->rd++ = c; if((p)->rd>(p)->wt)(p)->wt=(p)->rd;}
#define sunputc(p)	(*( (p)->rd = --(p)->wt))
#define zero(p)	for(pp=(p)->beg;pp<(p)->last;)*pp++='\0'
#define OUTC(x) {printf("%c",x); if(--count == 0){printf("\\\n"); count=ll;} }
#define TEST2	{if((count -= 2) <=0){printf("\\\n");count=ll;}}
#define EMPTY if(stkerr != 0){printf("stack empty\n"); continue; }
#define EMPTYR(x) if(stkerr!=0){pushp(x);printf("stack empty\n");continue;}
#define EMPTYS if(stkerr != 0){printf("stack empty\n"); return(1);}
#define EMPTYSR(x) if(stkerr !=0){printf("stack empty\n");pushp(x);return(1);}
#define error(p)	{printf(p); continue; }
#define errorrt(p)	{printf(p); return(1); }
struct blk {
	char	*rd;
	char	*wt;
	char	*beg;
	char	*last;
};
struct	blk *hfree;
struct	blk *getwd();
struct	blk *lookwd();
struct	blk *getdec();
struct	blk *morehd();

struct	blk *arg1, *arg2;
int	svargc;
char	savk;
char	**svargv;
int	dbg;
int	ifile;
FILE	*curfile;
struct	blk *scalptr, *basptr, *tenptr, *inbas;
struct	blk *sqtemp, *chptr, *strptr, *divxyz;
struct	blk *stack[STKSZ];
struct	blk **stkptr,**stkbeg;
struct	blk **stkend;
int	stkerr;
int	lastchar;
struct	blk *readstk[RDSKSZ];
struct	blk **readptr;
struct	blk *rem;
int	k;
struct	blk *irem;
int	skd,skr;
struct	blk *pop(),*readin(),*add0(),*mult();
struct	blk *scalint();
struct	blk *removc();
struct	blk *add(),*div(),*removr();
struct	blk *exp();
D 6
struct	blk *sqrt();
E 6
I 6
struct	blk *dcsqrt();
E 6
struct	blk *salloc(),*copy();
struct	blk *scale();
int	neg;
struct	sym {
	struct	sym *next;
	struct	blk *val;
} symlst[TBLSZ];
struct	sym *stable[TBLSZ];
struct	sym *sptr,*sfree;
struct	wblk {
	struct blk **rdw;
	struct blk **wtw;
	struct blk **begw;
	struct blk **lastw;
};
FILE	*fsave;
long	rel;
long	nbytes;
long	all;
long	headmor;
long	obase;
int	fw,fw1,ll;
int	(*outdit)();
int	bigot(),hexot();
int	logo;
int	log10;
int	count;
char	*pp;
D 4
int	(*signal())();
int	onintr();
E 4
I 4
void	onintr();
E 4
char	*malloc();
char	*nalloc();
char	*realloc();
D 3
char	*dummy;
E 3
E 1
