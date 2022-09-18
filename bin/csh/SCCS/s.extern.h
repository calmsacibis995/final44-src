h57971
s 00002/00002/00310
d D 8.1 93/05/31 16:42:02 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00312
d D 5.15 93/05/22 19:06:29 christos 15 14
c Fixed gcc -Wall warnings
e
s 00000/00007/00312
d D 5.14 92/02/12 20:07:59 christos 14 13
c Use the system's version of malloc
e
s 00001/00001/00318
d D 5.13 92/02/05 16:30:08 christos 13 12
c Use vis(3) to print unprintable characters
e
s 00001/00001/00318
d D 5.12 91/11/12 20:22:10 bostic 12 11
c fix sortscmp to compile under pcc
e
s 00002/00000/00317
d D 5.11 91/11/06 16:09:38 christos 11 10
c Added support for displaying non-printable characters
e
s 00003/00005/00314
d D 5.10 91/11/04 18:22:40 christos 10 9
c We need strstr now...
e
s 00001/00001/00318
d D 5.9 91/10/27 16:01:13 christos 9 8
c Loops were broken again. (Michael Schroeder's fix)
e
s 00001/00001/00318
d D 5.8 91/09/06 01:25:47 christos 8 7
c Replaced exp with expr to avoild libm conflict
e
s 00002/00001/00317
d D 5.7 91/08/30 21:23:49 christos 7 6
c Bugfix for loops in aliases.
e
s 00002/00000/00316
d D 5.6 91/07/28 14:14:20 christos 6 5
c Added dowhich() and doprintf() builtins.
e
s 00058/00074/00258
d D 5.5 91/07/19 17:30:47 christos 5 4
c stdio based version; brace glob fix; builtin prototypes
e
s 00034/00039/00298
d D 5.4 91/06/08 17:09:10 christos 4 3
c More prototype fixes, Removed TERMIOS define
e
s 00003/00000/00334
d D 5.3 91/06/07 20:58:23 christos 3 2
c Fixed sortscmp from glob.c
e
s 00209/00215/00125
d D 5.2 91/06/07 11:13:23 bostic 2 1
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00340/00000/00000
d D 5.1 91/06/04 16:56:10 christos 1 0
c date and time created 91/06/04 16:56:10 by christos
e
u
U
t
T
I 1
/*-
D 16
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#include <sys/cdefs.h>

E 2
/*
D 2
 * sh.c
E 2
I 2
 * csh.c
E 2
 */
D 2
extern void rechist();
extern void goodbye();
extern void exitstat();
extern void pintr();
extern void pintr1();
extern void process();
extern void dosource();
extern int gethdir();
extern void importpath();
extern void initdesc();
extern void untty();
#ifndef PROF
extern void xexit();
E 2
I 2
int	gethdir __P((Char *));
D 5
void	dosource __P((Char **));
E 5
I 5
void	dosource __P((Char **, struct command *));
E 5
void	exitstat __P((void));
void	goodbye __P((void));
void	importpath __P((Char *));
void	initdesc __P((void));
void	pintr __P((int));
void	pintr1 __P((bool));
void	printprompt __P((void));
void	process __P((bool));
void	rechist __P((void));
void	untty __P((void));
I 11
int	vis_fputc __P((int, FILE *));
E 11

#ifdef PROF
void done __P((int));
E 2
#else
D 2
extern void done();
E 2
I 2
void xexit __P((int));
E 2
#endif
D 2
extern void printprompt();
E 2

/*
D 2
 * sh.dir.c
E 2
I 2
 * dir.c
E 2
 */
D 2
extern void dinit();
extern void dodirs();
extern Char *dcanon();
extern void dtildepr();
extern void dtilde();
extern void dochngd();
extern Char *dnormalize();
extern void dopushd();
extern void dopopd();
extern void dfree();
E 2
I 2
void	 dinit __P((Char *));
D 5
void	 dodirs __P((Char **));
E 5
I 5
void	 dodirs __P((Char **, struct command *));
E 5
Char	*dcanon __P((Char *, Char *));
void	 dtildepr __P((Char *, Char *));
void	 dtilde __P((void));
D 5
void	 dochngd __P((Char **));
E 5
I 5
void	 dochngd __P((Char **, struct command *));
E 5
Char	*dnormalize __P((Char *));
D 5
void	 dopushd __P((Char **));
void	 dopopd __P((Char **));
E 5
I 5
void	 dopushd __P((Char **, struct command *));
void	 dopopd __P((Char **, struct command *));
E 5
struct directory;
void	 dfree __P((struct directory *));
E 2

/*
D 2
 * sh.dol.c
E 2
I 2
 * dol.c
E 2
 */
D 2
extern void Dfix();
extern Char *Dfix1();
extern void heredoc();
E 2
I 2
void	 Dfix __P((struct command *));
Char	*Dfix1 __P((Char *));
void	 heredoc __P((Char *));
E 2

/*
D 2
 * sh.err.c
E 2
I 2
 * err.c
E 2
 */
D 2
extern void seterror();
extern void stderror();
E 2
I 2
void	seterror __P((int, ...));
void	stderror __P((int, ...));
E 2

/*
D 2
 * sh.exec.c
E 2
I 2
 * exec.c
E 2
 */
D 2
extern void doexec();
extern void execash();
extern void xechoit();
extern void dohash();
extern void dounhash();
#ifdef VFORK
extern void hashstat();
#endif
E 2
I 2
D 5
void	doexec __P((struct command *));
void	dohash __P((void));
void	dounhash __P((void));
void	execash __P((char **, struct command *));
void	hashstat __P((void));
E 5
I 5
void	doexec __P((Char **, struct command *));
void	dohash __P((Char **, struct command *));
void	dounhash __P((Char **, struct command *));
I 6
void	dowhich __P((Char **, struct command *));
E 6
void	execash __P((Char **, struct command *));
void	hashstat __P((Char **, struct command *));
E 5
void	xechoit __P((Char **));
E 2

/*
D 2
 * sh.exp.c
E 2
I 2
 * exp.c
E 2
 */
D 2
extern int exp();
extern int exp0();
E 2
I 2
D 8
int	exp __P((Char ***));
E 8
I 8
int	expr __P((Char ***));
E 8
int	exp0 __P((Char ***, bool));
E 2

/*
D 2
 * sh.time.c
E 2
I 2
 * file.c
E 2
 */
D 2
extern void settimes();

/*
 * sh.file.c
 */
E 2
#ifdef FILEC
D 2
extern int tenex();
E 2
I 2
int	tenex __P((Char *, int));
E 2
#endif

/*
D 2
 * sh.func.c
E 2
I 2
 * func.c
E 2
 */
D 2
extern struct biltins *isbfunc();
extern void func();
extern void doonintr();
extern void donohup();
extern void dozip();
extern void prvars();
extern void doalias();
extern void unalias();
extern void dologout();
extern void dologin();
extern void doif();
extern void doelse();
extern void dogoto();
extern void doswitch();
extern void dobreak();
extern void doexit();
extern void doforeach();
extern void dowhile();
extern void doend();
extern void docontin();
extern void dorepeat();
extern void doswbrk();
extern int srchx();
extern void search();
extern void wfree();
extern void doecho();
extern void doglob();
extern void dosetenv();
extern void dounsetenv();
extern void Setenv();
extern void doumask();
extern void dolimit();
extern void dounlimit();
extern void dosuspend();
extern void doeval();
E 2
I 2
void	Setenv __P((Char *, Char *));
D 5
void	doalias __P((Char **));
void	dobreak __P((void));
void	docontin __P((void));
void	doecho __P((Char **));
void	doelse __P((void));
void	doend __P((void));
void	doeval __P((Char **));
void	doexit __P((Char **));
void	doforeach __P((Char **));
void	doglob __P((Char **));
void	dogoto __P((Char **));
E 5
I 5
void	doalias __P((Char **, struct command *));
void	dobreak __P((Char **, struct command *));
void	docontin __P((Char **, struct command *));
void	doecho __P((Char **, struct command *));
void	doelse __P((Char **, struct command *));
void	doend __P((Char **, struct command *));
void	doeval __P((Char **, struct command *));
void	doexit __P((Char **, struct command *));
void	doforeach __P((Char **, struct command *));
void	doglob __P((Char **, struct command *));
void	dogoto __P((Char **, struct command *));
E 5
void	doif __P((Char **, struct command *));
D 5
void	dolimit __P((Char **));
void	dologin __P((Char **));
void	dologout __P((void));
void	donohup __P((void));
void	doonintr __P((Char **));
E 5
I 5
void	dolimit __P((Char **, struct command *));
void	dologin __P((Char **, struct command *));
void	dologout __P((Char **, struct command *));
void	donohup __P((Char **, struct command *));
void	doonintr __P((Char **, struct command *));
I 6
void	doprintf __P((Char **, struct command *));
E 6
E 5
void	dorepeat __P((Char **, struct command *));
D 5
void	dosetenv __P((Char **));
void	dosuspend __P((void));
void	doswbrk __P((void));
void	doswitch __P((Char **));
void	doumask __P((Char **));
void	dounlimit __P((Char **));
void	dounsetenv __P((Char **));
void	dowhile __P((Char **));
void	dozip __P((void));
E 5
I 5
void	dosetenv __P((Char **, struct command *));
void	dosuspend __P((Char **, struct command *));
void	doswbrk __P((Char **, struct command *));
void	doswitch __P((Char **, struct command *));
void	doumask __P((Char **, struct command *));
void	dounlimit __P((Char **, struct command *));
void	dounsetenv __P((Char **, struct command *));
void	dowhile __P((Char **, struct command *));
void	dozip __P((Char **, struct command *));
E 5
void	func __P((struct command *, struct biltins *));
struct	biltins *
	isbfunc __P((struct command *));
void	prvars __P((void));
D 9
void	search __P((int, int, Char *));
E 9
I 9
void	gotolab __P((Char *));
E 9
int	srchx __P((Char *));
D 5
void	unalias __P((Char **));
E 5
I 5
void	unalias __P((Char **, struct command *));
E 5
void	wfree __P((void));
E 2

/*
D 2
 * sh.glob.c
E 2
I 2
 * glob.c
E 2
 */
D 2
extern Char **globall();
extern void ginit();
extern void trim();
extern int Gmatch();
extern void Gcat();
extern void rscan();
extern void tglob();
extern Char *globone();
extern Char **dobackp();
E 2
I 2
Char	**dobackp __P((Char *, bool));
void	  Gcat __P((Char *, Char *));
Char	 *globone __P((Char *, int));
int	  Gmatch __P((Char *, Char *));
void	  ginit __P((void));
Char	**globall __P((Char **));
void	  rscan __P((Char **, void (*)()));
void	  tglob __P((Char **));
void	  trim __P((Char **));
I 3
#ifdef FILEC
D 12
int	  sortscmp __P((Char **, Char **));
E 12
I 12
D 13
int	  sortscmp __P((void *, void *));
E 13
I 13
int	  sortscmp __P((const ptr_t, const ptr_t));
E 13
E 12
#endif /* FILEC */
E 3
E 2

D 2
#ifdef FILEC
extern int sortcmp();

#endif


E 2
/*
D 2
 * sh.hist.c
E 2
I 2
 * hist.c
E 2
 */
D 2
extern void savehist();
extern struct Hist *enthist();
extern void dohist();
E 2
I 2
D 5
void	dohist __P((Char **));
E 5
I 5
void	dohist __P((Char **, struct command *));
E 5
struct Hist *
	enthist __P((int, struct wordent *, bool));
void	savehist __P((struct wordent *));
E 2

/*
D 2
 * sh.lex.c
E 2
I 2
 * lex.c
E 2
 */
D 2
extern int lex();
extern void prlex();
extern void copylex();
extern void freelex();
extern void addla();
extern Char *domod();
extern void unreadc();
extern int readc();
extern void bseek();
#ifndef btell
extern off_t btell();
#endif
extern void btoeof();
extern void settell();
E 2
I 2
void	 addla __P((Char *));
D 7
void	 bseek __P((off_t));
E 7
I 7
void	 bseek __P((struct Ain *));
void	 btell __P((struct Ain *));
E 7
void	 btoeof __P((void));
void	 copylex __P((struct wordent *, struct wordent *));
Char	*domod __P((Char *, int));
void	 freelex __P((struct wordent *));
int	 lex __P((struct wordent *));
D 5
void	 prlex __P((struct wordent *));
E 5
I 5
void	 prlex __P((FILE *, struct wordent *));
E 5
int	 readc __P((bool));
void	 settell __P((void));
void	 unreadc __P((int));
E 2

/*
D 2
 * sh.misc.c
E 2
I 2
 * misc.c
E 2
 */
D 2
extern int any();
extern char *strsave();
extern Char **blkend();
extern void blkpr();
extern int number();
extern int blklen();
extern Char **blkcpy();
extern Char **blkcat();
extern void blkfree();
extern Char **saveblk();
extern void setzero();
#ifndef NOTUSED
extern char *strstr();
E 2
I 2
int	  any __P((char *, int));
Char	**blkcat __P((Char **, Char **));
Char	**blkcpy __P((Char **, Char **));
Char	**blkend __P((Char **));
void	  blkfree __P((Char **));
int	  blklen __P((Char **));
D 5
void	  blkpr __P((Char **));
E 5
I 5
void	  blkpr __P((FILE *, Char **));
E 5
Char	**blkspl __P((Char **, Char **));
void	  closem __P((void));
Char	**copyblk __P((Char **));
int	  dcopy __P((int, int));
int	  dmove __P((int, int));
void	  donefds __P((void));
Char	  lastchr __P((Char *));
void	  lshift __P((Char **, int));
int	  number __P((Char *));
int	  prefix __P((Char *, Char *));
Char	**saveblk __P((Char **));
void	  setzero __P((char *, int));
Char	 *strip __P((Char *));
char	 *strsave __P((char *));
char	 *strspl __P((char *, char *));
void	  udvar __P((Char *));

D 10
#ifndef	NOTUSED
char	 *strstr __P((const char *, const char *));
E 2
#endif
E 10
D 2
extern char *strspl();
extern Char **blkspl();
extern Char lastchr();
extern void closem();
extern void donefds();
extern int dmove();
extern int dcopy();
extern void lshift();
extern int number();
extern Char **copyblk();
#ifndef SHORT_STRINGS
extern char *strend();
E 2
I 2
#ifndef	SHORT_STRINGS
I 10
# ifdef NOTUSED
char	 *strstr __P((const char *, const char *));
# endif /* NOTUSED */
E 10
char	 *strend __P((char *));
E 2
#endif
D 2
extern Char *strip();
extern void udvar();
extern int prefix();
E 2

/*
D 2
 * sh.parse.c
E 2
I 2
 * parse.c
E 2
 */
D 2
extern void alias();
extern struct command *syntax();
extern void freesyn();
E 2
I 2
void	alias __P((struct wordent *));
void	freesyn __P((struct command *));
struct command *
	syntax __P((struct wordent *, struct wordent *, int));
E 2

D 5
/*
D 2
 * sh.print.c
E 2
I 2
 * print.c
E 2
 */
D 2
extern void psecs();
extern void pcsecs();
extern void xputchar();
extern int putraw();
extern int putpure();
extern void draino();
extern void flush();
E 2
I 2
void	draino __P((void));
void	flush __P((void));
void	pcsecs __P((long));
void	psecs __P((long));
int	putpure __P((int));
int	putraw __P((int));
void	xputchar __P((int));
E 5
E 2

/*
D 2
 * sh.proc.c
E 2
I 2
 * proc.c
E 2
 */
D 2
extern void pchild();
extern void pnote();
extern void pwait();
extern void pjwait();
extern void dowait();
extern void palloc();
extern void psavejob();
extern void prestjob();
extern void pendjob();
extern void dojobs();
extern void dofg();
extern void dofg1();
extern void dobg();
extern void dobg1();
extern void dokill();
extern void dostop();
extern void pstart();
extern void panystop();
extern struct process *pfind();
extern void donotify();
extern int pfork();
extern void pgetty();
E 2
I 2
D 5
void	dobg __P((Char **));
void	dobg1 __P((Char **));
void	dofg __P((Char **));
void	dofg1 __P((Char **));
void	dojobs __P((Char **));
void	dokill __P((Char **));
void	donotify __P((Char **));
void	dostop __P((Char **));
void	dowait __P((void));
E 5
I 5
void	dobg __P((Char **, struct command *));
void	dobg1 __P((Char **, struct command *));
void	dofg __P((Char **, struct command *));
void	dofg1 __P((Char **, struct command *));
void	dojobs __P((Char **, struct command *));
void	dokill __P((Char **, struct command *));
void	donotify __P((Char **, struct command *));
void	dostop __P((Char **, struct command *));
void	dowait __P((Char **, struct command *));
E 5
void	palloc __P((int, struct command *));
void	panystop __P((bool));
void	pchild __P((int));
void	pendjob __P((void));
struct process *
	pfind __P((Char *));
int	pfork __P((struct command *, int));
void	pgetty __P((int, int));
void	pjwait __P((struct process *));
void	pnote __P((void));
void	prestjob __P((void));
void	psavejob __P((void));
void	pstart __P((struct process *, int));
void	pwait __P((void));
E 2

/*
D 2
 * sh.sem.c
E 2
I 2
 * sem.c
E 2
 */
D 2
extern void execute();
extern void mypipe();
E 2
I 2
void	execute __P((struct command *, int, int *, int *));
void	mypipe __P((int *));
E 2

/*
D 2
 * sh.set.c
E 2
I 2
 * set.c
E 2
 */
D 2
extern void doset();
extern void dolet();
extern Char *putn();
extern int getn();
extern Char *value1();
extern struct varent *adrof1();
extern void set();
extern void set1();
extern void setq();
extern void unset();
extern void unset1();
extern void unsetv();
extern void setNS();
extern void shift();
extern void plist();
E 2
I 2
struct	varent
	*adrof1 __P((Char *, struct varent *));
D 5
void	 doset __P((Char **));
void	 dolet __P((Char **));
E 5
I 5
void	 doset __P((Char **, struct command *));
void	 dolet __P((Char **, struct command *));
E 5
Char	*putn __P((int));
int	 getn __P((Char *));
Char	*value1 __P((Char *, struct varent *));
void	 set __P((Char *, Char *));
void	 set1 __P((Char *, Char **, struct varent *));
void	 setq __P((Char *, Char **, struct varent *));
D 5
void	 unset __P((Char *[]));
E 5
I 5
void	 unset __P((Char **, struct command *));
E 5
void	 unset1 __P((Char *[], struct varent *));
void	 unsetv __P((Char *));
void	 setNS __P((Char *));
D 5
void	 shift __P((Char **));
E 5
I 5
void	 shift __P((Char **, struct command *));
E 5
void	 plist __P((struct varent *));
E 2

/*
D 2
 * sh.time.c
E 2
I 2
 * time.c
E 2
 */
D 2
extern void settimes();
extern void dotime();
extern void donice();
extern void ruadd();
extern void tvadd();
extern void tvsub();
extern void prusage();
E 2
I 2
D 5
void	donice __P((Char **));
void	dotime __P((void));
E 5
I 5
void	donice __P((Char **, struct command *));
void	dotime __P((Char **, struct command *));
E 5
void	prusage __P((struct rusage *, struct rusage *,
	    struct timeval *, struct timeval *));
void	ruadd __P((struct rusage *, struct rusage *));
void	settimes __P((void));
void	tvadd __P((struct timeval *, struct timeval *));
void	tvsub __P((struct timeval *, struct timeval *, struct timeval *));
I 5
void	pcsecs __P((long));
void	psecs __P((long));
E 5
E 2

/*
D 4
 * tc.alloc.c
E 4
I 4
 * alloc.c
E 4
 */
D 14
#ifndef SYSMALLOC
D 4
#ifdef sun
extern int free();
E 4
I 4
void	free __P((ptr_t));
ptr_t	malloc __P((size_t));
ptr_t	realloc __P((ptr_t, size_t));
ptr_t	calloc __P((size_t, size_t));
E 4
#else
E 14
D 4
extern void free();
#endif
extern ptr_t malloc();
extern ptr_t realloc();
extern ptr_t calloc();
#else
extern void Free();
extern ptr_t Malloc();
extern ptr_t Realloc();
extern ptr_t Calloc();
E 4
I 4
void	Free __P((ptr_t));
ptr_t	Malloc __P((size_t));
ptr_t	Realloc __P((ptr_t, size_t));
ptr_t	Calloc __P((size_t, size_t));
E 4
D 14
#endif				/* SYSMALLOC */
E 14
D 4
extern void showall();
E 4
I 4
D 5
void	showall __P((void));
E 5
I 5
void	showall __P((Char **, struct command *));
E 5
E 4

/*
D 4
 * tc.printf.h
E 4
I 4
D 5
 * printf.h
E 4
 */
D 4
extern void xprintf();
extern void xsprintf();
extern void xvprintf();
extern void xvsprintf();
E 4
I 4
void	xprintf __P((char *, ...));
void	xsprintf __P((char *, char *, ...));
void	xvprintf __P((char *, va_list));
void	xvsprintf __P((char *, char *, va_list));
E 4

/*
E 5
D 4
 * tc.str.c:
E 4
I 4
 * str.c:
E 4
 */
#ifdef SHORT_STRINGS
D 4
extern Char *s_strchr();
extern Char *s_strrchr();
extern Char *s_strcat();
E 4
I 4
Char	 *s_strchr __P((Char *, int));
Char	 *s_strrchr __P((Char *, int));
Char	 *s_strcat __P((Char *, Char *));
E 4
#ifdef NOTUSED
D 4
extern Char *s_strncat();
E 4
I 4
Char	 *s_strncat __P((Char *, Char *, size_t));
E 4
#endif
D 4
extern Char *s_strcpy();
extern Char *s_strncpy();
extern Char *s_strspl();
extern int s_strlen();
extern int s_strcmp();
extern int s_strncmp();
extern Char *s_strsave();
extern Char *s_strend();
extern Char *s_strspl();
E 4
I 4
Char	 *s_strcpy __P((Char *, Char *));
Char	 *s_strncpy __P((Char *, Char *, size_t));
Char	 *s_strspl __P((Char *, Char *));
size_t	  s_strlen __P((Char *));
int	  s_strcmp __P((Char *, Char *));
int	  s_strncmp __P((Char *, Char *, size_t));
Char	 *s_strsave __P((Char *));
Char	 *s_strend __P((Char *));
E 4
D 10
#ifdef NOTUSED
E 10
D 4
extern Char *s_strstr();
E 4
I 4
Char	 *s_strstr __P((Char *, Char *));
E 4
D 10
#endif
E 10
D 4
extern Char *str2short();
extern Char **blk2short();
extern char *short2str();
extern char *short2qstr();
extern char **short2blk();
E 4
I 4
Char	 *str2short __P((char *));
Char	**blk2short __P((char **));
char	 *short2str __P((Char *));
D 5
char	 *short2qstr __P((Char *));
E 5
char	**short2blk __P((Char **));
E 4
#endif
I 5
char	 *short2qstr __P((Char *));
I 11
char	 *vis_str    __P((Char *));
E 11
E 5
E 1
