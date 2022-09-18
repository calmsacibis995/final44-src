h30319
s 00023/00027/00061
d D 8.2 95/05/04 18:00:03 christos 5 4
c 
e
s 00002/00002/00086
d D 8.1 93/05/31 15:20:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00016/00048
d D 5.3 92/07/15 09:13:20 marc 3 2
c support set -o options
e
s 00003/00002/00061
d D 5.2 92/06/23 18:06:59 marc 2 1
c new options
e
s 00063/00000/00000
d D 5.1 91/03/07 20:27:50 bostic 1 0
c date and time created 91/03/07 20:27:50 by bostic
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
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct shparam {
	int nparam;	/* number of positional parameters (without $0) */
	char malloc;	/* true if parameter list dynamicly allocated */
	char **p;		/* parameter list */
	char **optnext;	/* next parameter to be processed by getopts */
	char *optptr;	/* used by getopts */
};



D 3
#define eflag optval[0]
#define fflag optval[1]
#define Iflag optval[2]
#define iflag optval[3]
#define jflag optval[4]
#define nflag optval[5]
#define sflag optval[6]
#define xflag optval[7]
#define zflag optval[8]
#define vflag optval[9]
I 2
#define	Eflag optval[10]
E 3
I 3
#define eflag optlist[0].val
#define fflag optlist[1].val
#define Iflag optlist[2].val
#define iflag optlist[3].val
#define mflag optlist[4].val
#define nflag optlist[5].val
#define sflag optlist[6].val
#define xflag optlist[7].val
#define vflag optlist[8].val
#define Vflag optlist[9].val
#define	Eflag optlist[10].val
#define	Cflag optlist[11].val
#define	aflag optlist[12].val
#define	bflag optlist[13].val
#define	uflag optlist[14].val
E 3
E 2

D 2
#define NOPTS	10
E 2
I 2
D 3
#define NOPTS	11
E 3
I 3
#define NOPTS	15
E 3
E 2

I 3
struct optent {
	const char *name;
	const char letter;
	char val;
};

E 3
#ifdef DEFINE_OPTIONS
D 2
const char optchar[NOPTS+1] = "efIijnsxzv";       /* shell flags */
E 2
I 2
D 3
const char optchar[NOPTS+1] = "efIijnsxzvE";       /* shell flags */
E 2
char optval[NOPTS+1];           /* values of option flags */
E 3
I 3
struct optent optlist[NOPTS] = {
D 5
	"errexit",	'e',	0,
	"noglob",	'f',	0,
	"ignoreeof",	'I',	0,
	"interactive",	'i',	0,
	"monitor",	'm',	0,
	"noexec",	'n',	0,
	"stdin",	's',	0,
	"xtrace",	'x',	0,
	"verbose",	'v',	0,
	"vi",		'V',	0,
	"emacs",	'E',	0,
	"noclobber",	'C',	0,
	"allexport",	'a',	0,
	"notify",	'b',	0,
	"nounset",	'u',	0,
E 5
I 5
	{ "errexit",	'e',	0 },
	{ "noglob",	'f',	0 },
	{ "ignoreeof",	'I',	0 },
	{ "interactive",'i',	0 },
	{ "monitor",	'm',	0 },
	{ "noexec",	'n',	0 },
	{ "stdin",	's',	0 },
	{ "xtrace",	'x',	0 },
	{ "verbose",	'v',	0 },
	{ "vi",		'V',	0 },
	{ "emacs",	'E',	0 },
	{ "noclobber",	'C',	0 },
	{ "allexport",	'a',	0 },
	{ "notify",	'b',	0 },
	{ "nounset",	'u',	0 },
E 5
};
E 3
#else
D 3
extern const char optchar[NOPTS+1];
extern char optval[NOPTS+1];
E 3
I 3
extern struct optent optlist[NOPTS];
E 3
#endif


extern char *minusc;		/* argument to -c option */
extern char *arg0;		/* $0 */
extern struct shparam shellparam;  /* $@ */
extern char **argptr;		/* argument list for builtin commands */
extern char *optarg;		/* set by nextopt */
extern char *optptr;		/* used by nextopt */

D 5

#ifdef __STDC__
void procargs(int, char **);
void setparam(char **);
void freeparam(struct shparam *);
int nextopt(char *);
#else
void procargs();
void setparam();
void freeparam();
int nextopt();
#endif
E 5
I 5
void procargs __P((int, char **)); 
void optschanged __P((void));
void setparam __P((char **));
void freeparam __P((struct shparam *)); 
int shiftcmd __P((int, char **));
int setcmd __P((int, char **));
int getoptscmd __P((int, char **));
int nextopt __P((char *));
E 5
E 1
