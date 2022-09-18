h33590
s 00028/00185/01011
d D 2.3 93/07/27 09:15:36 bostic 4 3
c checkpoint; Mike Karels left this checked out.
e
s 00003/00003/01193
d D 2.2 88/03/31 16:24:23 jaap 3 2
c Fixed bug with \X'..' which was popping up with psfig, fixed suggested by bwk.
e
s 00362/00300/00834
d D 2.1 85/07/18 14:20:07 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 01134/00000/00000
d D 1.1 85/07/17 17:54:15 jaap 1 0
c date and time created 85/07/17 17:54:15 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% (CWI) %E%";
E 4
I 4
/*
static char sccsid[] = "@(#)n1.c	2.2 (CWI) 88/03/31";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
#endif lint
I 2
/*
 * n1.c
 *
 *	consume options, initialization, main loop,
 *	input routines, escape function calling
 */

E 2
#include <ctype.h>
I 2
#include <signal.h>
E 2
#include <sys/types.h>
#include <sys/stat.h>
I 2
#include <setjmp.h>
#include <sgtty.h>

E 2
#include "tdef.h"
I 4
#include "pathnames.h"
E 4
D 2
extern
#include "d.h"
extern
#include "v.h"
E 2
I 2
#include "ext.h"

#include	<time.h>	/* See cvtime() (jaap) */

E 2
#ifdef NROFF
D 2
extern
E 2
#include "tw.h"
#endif
D 2
#include "s.h"
#include <setjmp.h>
jmp_buf sjbuf;
#include	<sgtty.h>
/*
troff1.c
E 2

D 2
consume options, initialization, main loop,
input routines, escape function calling
*/

#include "ext.h"

char	*sprintf();
tchar	inchar[LNSIZE], *pinchar = inchar;	/* XXX */
filep ipl[NSO];
E 2
I 2
jmp_buf sjbuf;
D 4
extern	char	*sprintf();
E 4
filep	ipl[NSO];
E 2
long	offl[NSO];
long	ioff;
char	*ttyp;
D 2
extern struct contab {
	int	rq;
	union {
		int	(*f)();
		unsigned	mx;
	} x;
} contab[NM];
E 2
I 2
char	cfname[NSO][NS] = "<standard input>";	/*file name stack*/
int	cfline[NSO];		/*input line count stack*/
char	*progname;	/* program name (troff) */
E 2

main(argc, argv)
int	argc;
char	**argv;
{
	register char	*p, *q;
	register j;
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2
	extern catch(), kcatch();
D 2
	int	oargc;
	char	**oargv;
E 2
I 2
	char	**oargv, *getenv();
E 2

I 2
	progname = argv[0];
E 2
	signal(SIGHUP, catch);
	if (signal(SIGINT, catch) == SIG_IGN) {
		signal(SIGHUP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	signal(SIGPIPE, catch);
	signal(SIGTERM, kcatch);
D 2
	oargc = argc;
E 2
	oargv = argv;
I 2
	mrehash();
	nrehash();
E 2
	init0();
D 2
options:
E 2
I 2
	if ((p = getenv("TYPESETTER")) != 0)
		strcpy(devname, p);
E 2
	while (--argc > 0 && (++argv)[0][0] == '-')
		switch (argv[0][1]) {

		case 'F':	/* switch font tables from default */
			if (argv[0][2] != '\0') {
				strcpy(termtab, &argv[0][2]);
				strcpy(fontfile, &argv[0][2]);
			} else {
				argv++; argc--;
				strcpy(termtab, argv[0]);
				strcpy(fontfile, argv[0]);
			}
			continue;
		case 0:
			goto start;
		case 'i':
			stdi++;
			continue;
		case 'q':
			quiet++;
			if (gtty(0, &ttys) >= 0)
				ttysave = ttys.sg_flags;
			continue;
		case 'n':
			npn = ctoi(&argv[0][2]);
			continue;
		case 'u':	/* set emboldening amount */
			bdtab[3] = ctoi(&argv[0][2]);
			if (bdtab[3] < 0 || bdtab[3] > 50)
				bdtab[3] = 0;
			continue;
		case 's':
			if (!(stop = ctoi(&argv[0][2])))
				stop++;
			continue;
		case 'r':
D 4
			eibuf = sprintf(ibuf+strlen(ibuf), ".nr %c %s\n",
E 4
I 4
			eibuf = ibuf+strlen(ibuf);
			(void) sprintf(eibuf, ".nr %c %s\n",
E 4
				argv[0][2], &argv[0][3]);
			continue;
I 2
		case 'c':
E 2
		case 'm':
D 2
			p = &nextf[nfi];
			q = &argv[0][2];
			while ((*p++ = *q++) != 0)
				;
E 2
I 2
			strcat(nextf, &argv[0][2]);
I 4
			if (access(nextf, 4) < 0) {
				char local[NS];

				strcpy(local, _PATH_LOCAL_TMAC);
				strcat(local, &argv[0][2]);
				if (access(local, 4) == 0)
					strcpy(nextf, local);
			}
E 4
E 2
			mflg++;
			continue;
		case 'o':
			getpn(&argv[0][2]);
			continue;
D 2
		case 'D':	/* select ``DUTCH'' as default dialect jna  */
E 2
I 2
		case 'T':
			strcpy(devname, &argv[0][2]);
			dotT++;
			continue;
		case 'D':	/* select DUTCH as hyphenation style (jaap) */
E 2
			hyalg1 = hyalg = DUTCH;
			thresh = DUTCH_THRESH;
			continue;
#ifdef NROFF
		case 'h':
			hflg++;
			continue;
		case 'z':
			no_out++;
			continue;
		case 'e':
			eqflg++;
			continue;
D 2
		case 'T':
			strcat(termtab, &argv[0][2]);
			dotT++;
			continue;
E 2
#endif
#ifndef NROFF
D 2
		case 'T':
			strcpy(devname, &argv[0][2]);
			dotT++;
			continue;
E 2
		case 'z':
			no_out++;
		case 'a':
			ascii = 1;
			nofeed++;
D 2
		case 't':
			ptid = 1;
E 2
			continue;
		case 'f':
			nofeed++;
			continue;
I 2
		case 't':		/* for backward compatability */
			continue;
E 2
#endif
		default:
D 2
			fprintf(stderr, "troff: unknown option %s\n", argv[0]);
E 2
I 2
			errprint("unknown option %s", argv[0]);
E 2
			done(02);
		}

start:
	init1(oargv[0][0]);
	argp = argv;
	rargc = argc;
	init2();
	setjmp(sjbuf);
loop:
	copyf = lgf = nb = nflush = nlflg = 0;
	if (ip && rbf0(ip) == 0 && ejf && frame->pframe <= ejl) {
		nflush++;
		trap = 0;
		eject((struct s *)0);
		goto loop;
	}
	i = getch();
	if (pendt)
D 2
		goto lt;
E 2
I 2
		goto Lt;
E 2
	if ((j = cbits(i)) == XPAR) {
		copyf++;
		tflg++;
		while (cbits(i) != '\n')
			pchar(i = getch());
		tflg = 0;
		copyf--;
		goto loop;
	}
	if (j == cc || j == c2) {
		if (j == c2)
			nb++;
		copyf++;
		while ((j = cbits(i = getch())) == ' ' || j == '\t')
			;
		ch = i;
		copyf--;
		control(getrq(), 1);
		flushi();
		goto loop;
	}
D 2
lt:
E 2
I 2
Lt:
E 2
	ch = i;
	text();
I 2
	if (nlflg)
		numtab[HP].val = 0;
E 2
	goto loop;
}


catch()
{
	done3(01);
}


kcatch()
{
	signal(SIGTERM, SIG_IGN);
	done3(01);
}


init0()
{
	eibuf = ibufp = ibuf;
	ibuf[0] = 0;
D 2
	v.nl = -1;
E 2
I 2
	numtab[NL].val = -1;
E 2
}


init1(a)
char	a;
{
D 4
	register char	*p;
	char	*mktemp();
E 4
	register i;

D 4
	p = mktemp("/usr/tmp/trtmpXXXXX");
	if (a == 'a')
		p = &p[9];
	if ((close(creat(p, 0600))) < 0) {
D 2
		fprintf(stderr, "troff: cannot create temp file.\n");
E 2
I 2
		errprint("cannot create temp file.");
E 2
		exit(-1);
	}
	ibf = open(p, 2);
	unlkp = p;
E 4
	for (i = NTRTAB; --i; )
		trtab[i] = i;
	trtab[UNPAD] = ' ';
}


init2()
{
	register i, j;
D 2
	register char *p;
	tchar *t;
	extern int	block;
E 2
D 4
	extern char	*setbrk();
E 4
	extern char	*ttyname();
I 4
	char *cp;
E 4

	ttyod = 2;
	if ((ttyp=ttyname(j=0)) != 0 || (ttyp=ttyname(j=1)) != 0 || (ttyp=ttyname(j=2)) != 0)
		;
	else 
		ttyp = "notty";
	iflg = j;
	if (ascii)
		mesg(0);
D 4
	obufp = obuf;
E 4
	ptinit();
	mchbits();
	cvtime();
D 2
	v.pid = getpid();
E 2
I 2
	numtab[PID].val = getpid();
E 2
	olinep = oline;
	ioff = 0;
D 2
	v.hp = init = 0;
	pinchar = inchar;	/* XXX */
	v.nl = -1;
E 2
I 2
	numtab[HP].val = init = 0;
	numtab[NL].val = -1;
E 2
	nfo = 0;
	ifile = 0;
	copyf = raw = 0;
D 2
	level = 0;
E 2
D 4
	eibuf = sprintf(ibuf+strlen(ibuf), ".ds .T %s\n", devname);
E 4
I 4
	cp = ibuf + strlen(ibuf);
	sprintf(cp, ".ds .T %s\n", devname);
	eibuf = cp + strlen(cp);
E 4
D 2
	for (p=ibuf, t=cbuf; *t++ = *p++; )
		;
	cp = cbuf;
	eibuf = ibuf;
E 2
I 2
	numtab[CD].val = -1;	/* compensation */
	cpushback(ibuf);
E 2
	ibufp = ibuf;
	nx = mflg;
D 4
	frame = stk = (struct s *)setbrk(DELTA);
E 4
I 4
	frame = stk = (struct s *)malloc(DELTA * sizeof(struct s));
E 4
	dip = &d[0];
	nxf = frame + 1;
D 4
	for (i = NEV; i--; )
D 2
		write(ibf, (char *) & block, EVS);
E 2
I 2
		write(ibf, (char *) & env, sizeof(env));
E 4
I 4
	for (i = 1; i < NEV; ++i)
		env_array[i] = *env;
E 4
E 2
}

D 2
				/*
				 * bug fix jna
				 * This replaces the old cvtime, so on well
				 * maintained systems, you don't need to change
				 * the (quite unknown) ZONE constant in
				 * tdef.h
				 */
#ifdef BSD42
#include	<sys/time.h>
#else
#include	<time.h>
#endif BSD42
E 2
I 2
/*
 * (jaap)
 * This replaces the old cvtime, so on well maintained systems, you don't
 * need to change the (quite unknown) ZONE constant in tdef.h
 */

E 2
cvtime() {
	long	tt;
	register struct tm	*tym;
	extern struct tm	*localtime();

	time(&tt);
	tym = localtime(&tt);
D 2
	v.dy = tym->tm_mday;
	v.dw = tym->tm_wday + 1;
	v.yr = tym->tm_year;
	v.mo = tym->tm_mon + 1;
E 2
I 2
	numtab[DY].val = tym->tm_mday;		/* Current day of the month */
	numtab[DW].val = tym->tm_wday + 1;	/* Current day of the week */
	numtab[YR].val = tym->tm_year;		/* Current year */
	numtab[MO].val = tym->tm_mon + 1;	/* Current month of year */
E 2
}

I 2

E 2
ctoi(s)
	register char *s;
{
	register n;

	while (*s == ' ')
		s++;
	n = 0;
	while (isdigit(*s))
		n = 10 * n + *s++ - '0';
	return n;
}


mesg(f)
int	f;
{
	static int	mode;
I 2
	struct stat stbuf;
E 2

	if (!f) {
D 2
		stat(ttyp, cbuf);
		mode = ((struct stat *)(cbuf))->st_mode;
E 2
I 2
		stat(ttyp, &stbuf);
		mode = stbuf.st_mode;
E 2
		chmod(ttyp, mode & ~0122);	/* turn off writing for others */
	} else {
D 2
		if( !init)
E 2
I 2
		if (ttyp && *ttyp && mode)
E 2
			chmod(ttyp, mode);
	}
}

I 2
errprint(s, s1, s2, s3, s4, s5)	/* error message printer */
	char *s, *s1, *s2, *s3, *s4, *s5;
{
	fdprintf(stderr, "%s: ", progname);
	fdprintf(stderr, s, s1, s2, s3, s4, s5);
	if (numtab[CD].val > 0)
		fdprintf(stderr, "; line %d, file %s", numtab[CD].val, cfname[ifi]);
	fdprintf(stderr, "\n");
	stackdump();
}
E 2

I 2
D 4

E 2
/*
 * Scaled down version of C Library printf.
 * Only %s %u %d (==%u) %o %c %x %D are recognized.
 */
#define	putchar(n)	(*pfbp++ = (n))	/* NO CHECKING! */

static char	pfbuf[NTM];
static char	*pfbp = pfbuf;
int	stderr	 = 2;	/* NOT stdio value */

D 2
/* VARARGS */
fprintf(fd, fmt, x1)
int	fd;
char	*fmt;
unsigned	x1;
E 2
I 2
/* VARARGS2 */
fdprintf(fd, fmt, x1)
	int	fd;
	register char	*fmt;
	unsigned	x1;
E 2
{
	register c;
	register unsigned int	*adx;
	char	*s;
	register i;

	pfbp = pfbuf;
	adx = &x1;
loop:
	while ((c = *fmt++) != '%') {
		if (c == '\0') {
			if (fd == stderr)
				write(stderr, pfbuf, pfbp - pfbuf);
			else {
				*pfbp = 0;
				pfbp = pfbuf;
				while (*pfbp) {
					*obufp++ = *pfbp++;
					if (obufp >= &obuf[OBUFSZ])
						flusho();
				}
			}
			return;
		}
		putchar(c);
	}
	c = *fmt++;
	if (c == 'd') {
		i = *adx;
		if (i < 0) {
			putchar('-');
			i = -i;
		}
		printn((long)i, 10);
	} else if (c == 'u' || c == 'o' || c == 'x')
		printn((long)*adx, c == 'o' ? 8 : (c == 'x' ? 16 : 10));
	else if (c == 'c') {
		if (c > 0177 || c < 040)
			putchar('\\');
		putchar(*adx & 0177);
	} else if (c == 's') {
		s = (char *) * adx;
		while (c = *s++)
			putchar(c);
	} else if (c == 'D') {
		printn(*(long *)adx, 10);
		adx += (sizeof(long) / sizeof(int)) - 1;
	} else if (c == 'O') {
		printn(*(long *)adx, 8);
		adx += (sizeof(long) / sizeof(int)) - 1;
	}
	adx++;
	goto loop;
}


/*
 * Print an unsigned integer in base b.
 */
static printn(n, b)
D 2
long	n;
E 2
I 2
	register long	n;
E 2
{
	register long	a;

	if (n < 0) {	/* shouldn't happen */
		putchar('-');
		n = -n;
	}
	if (a = n / b)
		printn(a, b);
	putchar("0123456789ABCDEF"[(int)(n%b)]);
}

/* scaled down version of library sprintf */
D 2
/* same limits as fprintf */
E 2
I 2
/* same limits as fdprintf */
E 2
/* returns pointer to \0 that ends the string */

D 2
/* VARARGS */
E 2
I 2
/* VARARGS2 */
E 2
char *sprintf(str, fmt, x1)
	char	*str;
	char	*fmt;
	unsigned	x1;
{
	register c;
	char *sprintn();
	register unsigned int	*adx;
	char	*s;
	register i;

	adx = &x1;
loop:
	while ((c = *fmt++) != '%') {
		if (c == '\0') {
			*str = 0;
			return str;
		}
		*str++ = c;
	}
	c = *fmt++;
	if (c == 'd') {
		i = *adx;
		if (i < 0) {
			*str++ = '-';
			i = -i;
		}
		str = sprintn(str, (long)i, 10);
	} else if (c == 'u' || c == 'o' || c == 'x')
		str = sprintn(str, (long)*adx, c == 'o' ? 8 : (c == 'x' ? 16 : 10));
	else if (c == 'c') {
		if (c > 0177 || c < 040)
			*str++ = '\\';
		*str++ = *adx & 0177;
	} else if (c == 's') {
		s = (char *) * adx;
		while (c = *s++)
			*str++ = c;
	} else if (c == 'D') {
		str = sprintn(str, *(long *)adx, 10);
		adx += (sizeof(long) / sizeof(int)) - 1;
	} else if (c == 'O') {
		str = sprintn(str, *(long *)adx, 8);
		adx += (sizeof(long) / sizeof(int)) - 1;
	}
	adx++;
	goto loop;
}

/*
 * Print an unsigned integer in base b.
 */
static char *sprintn(s, n, b)
	register char *s;
	register long n;
{
	register long	a;

	if (n < 0) {	/* shouldn't happen */
		*s++ = '-';
		n = -n;
	}
	if (a = n / b)
		s = sprintn(s, a, b);
	*s++ = "0123456789ABCDEF"[(int)(n%b)];
	return s;
}


E 4
control(a, b)
register int	a, b;
{
	register int	j;

	if (a == 0 || (j = findmn(a)) == -1)
		return(0);
D 2
	if (contab[j].rq & MMASK) {
E 2
I 2
	if (contab[j].f == 0) {
E 2
		nxf->nargs = 0;
		if (b)
			collect();
		flushi();
D 2
		return(pushi((filep)contab[j].x.mx));
E 2
I 2
		return pushi((filep)contab[j].mx, a);
E 2
	} else if (b)
D 2
		return((*contab[j].x.f)(0));
E 2
I 2
		return((*contab[j].f)(0));
E 2
	else
		return(0);
}


getrq()
{
	register i, j;

	if (((i = getach()) == 0) || ((j = getach()) == 0))
		goto rtn;
	i = PAIR(i, j);
rtn:
	return(i);
}

I 2
/*
 * table encodes some special characters, to speed up tests
 * in getchar, viz FLSS, RPT, f, \b, \n, fc, tabch, ldrch
 */
E 2

D 2
tchar getch()
E 2
I 2
char
gchtab[] = {
	000,004,000,000,010,000,000,000, /* fc, ldr */
	001,002,001,000,001,000,000,000, /* \b, tab, nl, RPT */
	000,000,000,000,000,000,000,000,
	000,001,000,000,000,000,000,000, /* FLSS */
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,001,000, /* f */
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
};

tchar
getch()
E 2
{
	register int	k;
D 2
	tchar i, j;
E 2
I 2
	register tchar i, j;
E 2
	tchar setht(), setslant();

D 2
	level++;
E 2
g0:
D 2
	if (ch) {
		if (cbits(i = ch) == '\n')
E 2
I 2
	if (i = ch) {
		if (cbits(i) == '\n')
E 2
			nlflg++;
		ch = 0;
D 2
		level--;
E 2
		return(i);
	}

D 2
	if (nlflg) {
		level--;
E 2
I 2
	if (nlflg)
E 2
		return('\n');
D 2
	}

	if ((k = cbits(i = getch0())) != ESC) {
		if (ismot(i))
			goto g2;
E 2
I 2
	i = getch0();
	if (ismot(i))
		return(i);
	k = cbits(i);
	if (k != ESC) {
		if (gchtab[k]==0)
			return(i);
		if (k == '\n') {
			if (cbits(i) == '\n') {
				nlflg++;
				if (ip == 0)
					numtab[CD].val++; /* line number */
			}
			return(k);
		}
E 2
		if (k == FLSS) {
			copyf++; 
			raw++;
			i = getch0();
			if (!fi)
				flss = i;
			copyf--; 
			raw--;
			goto g0;
		}
		if (k == RPT) {
			setrpt();
			goto g0;
		}
		if (!copyf) {
			if (k == 'f' && lg && !lgf) {
				i = getlg(i);
D 2
				goto g2;
E 2
I 2
				return(i);
E 2
			}
			if (k == fc || k == tabch || k == ldrch) {
				if ((i = setfield(k)) == 0)
					goto g0; 
				else 
D 2
					goto g2;
E 2
I 2
					return(i);
E 2
			}
			if (k == '\b') {
				i = makem(-width(' ' | chbits));
D 2
				goto g2;
E 2
I 2
				return(i);
E 2
			}
		}
D 2
		goto g2;
E 2
I 2
		return(i);
E 2
	}
	k = cbits(j = getch0());
D 2
	if (ismot(j)) {
		i = j;
		goto g2;
	}
E 2
I 2
	if (ismot(j))
		return(j);
E 2
	switch (k) {

I 2
D 3
	case 'X':	/* \X'...' for copy through */
		setxon();
		goto g0;
E 3
E 2
	case '\n':	/* concealed newline */
		goto g0;
	case 'n':	/* number register */
		setn();
		goto g0;
	case '*':	/* string indicator */
		setstr();
		goto g0;
	case '$':	/* argument indicator */
		seta();
		goto g0;
	case '{':	/* LEFT */
		i = LEFT;
		goto gx;
	case '}':	/* RIGHT */
		i = RIGHT;
		goto gx;
	case '"':	/* comment */
		while (cbits(i = getch0()) != '\n')
			;
D 2
		goto g2;
E 2
I 2
		nlflg++;
		if (ip == 0)
			numtab[CD].val++;
		return(i);
E 2
	case ESC:	/* double backslash */
		i = eschar;
		goto gx;
	case 'e':	/* printable version of current eschar */
		i = PRESC;
		goto gx;
	case ' ':	/* unpaddable space */
		i = UNPAD;
		goto gx;
D 2
	case '|':	/* narrow space */
		i = NARSP;
		goto gx;
	case '^':	/* half of narrow space */
		i = HNARSP;
		goto gx;
E 2
	case '\'':	/* \(aa */
		i = ACUTE;
		goto gx;
	case '`':	/* \(ga */
		i = GRAVE;
		goto gx;
	case '_':	/* \(ul */
		i = UNDERLINE;
		goto gx;
	case '-':	/* current font minus */
		i = MINUS;
		goto gx;
	case '&':	/* filler */
		i = FILLER;
		goto gx;
	case 'c':	/* to be continued */
		i = CONT;
		goto gx;
	case '!':	/* transparent indicator */
		i = XPAR;
		goto gx;
	case 't':	/* tab */
		i = '\t';
D 2
		goto g2;
E 2
I 2
		return(i);
E 2
	case 'a':	/* leader (SOH) */
		i = LEADER;
D 2
		goto g2;
E 2
I 2
		return(i);
E 2
	case '%':	/* ohc */
		i = OHC;
D 2
		goto g2;
E 2
I 2
		return(i);
E 2
	case 'g':	/* return format of a number register */
		setaf();
		goto g0;
I 2
	case 'N':	/* absolute character number */
		i = setabs();
		goto gx;
E 2
	case '.':	/* . */
		i = '.';
gx:
		setsfbits(i, sfbits(j));
D 2
		goto g2;
E 2
I 2
		return(i);
E 2
	}
D 2
	if (!copyf)
		switch (k) {
E 2
I 2
	if (copyf) {
		*pbp++ = j;
		return(eschar);
	}
	switch (k) {
E 2

I 3
	case 'X':	/* \X'...' for copy through */
		setxon();
		goto g0;
E 3
D 2
		case 'p':	/* spread */
			spread++;
E 2
I 2
	case 'p':	/* spread */
		spread++;
		goto g0;
	case '(':	/* special char name */
		if ((i = setch()) == 0)
E 2
			goto g0;
D 2
		case '(':	/* special char name */
			if ((i = setch()) == 0)
				goto g0;
			break;
		case 's':	/* size indicator */
			setps();
			goto g0;
		case 'H':	/* character height */
			i = setht();
			break;
		case 'S':	/* slant */
			i = setslant();
			break;
		case 'f':	/* font indicator */
			setfont(0);
			goto g0;
		case 'w':	/* width function */
			setwd();
			goto g0;
		case 'v':	/* vert mot */
			if (i = vmot())
				break;
			goto g0;
		case 'h': 	/* horiz mot */
			if (i = hmot())
				break;
			goto g0;
		case 'z':	/* zero with char */
			i = setz();
			break;
		case 'l':	/* hor line */
			setline();
			goto g0;
		case 'L':	/* vert line */
			setvline();
			goto g0;
		case 'D':	/* drawing function */
			setdraw();
			goto g0;
		case 'b':	/* bracket */
			setbra();
			goto g0;
		case 'o':	/* overstrike */
			setov();
			goto g0;
		case 'k':	/* mark hor place */
			if ((k = findr(getsn())) != -1) {
				vlist[k] = v.hp = sumhp();
			}
			goto g0;
		case '0':	/* number space */
			i = makem(width('0' | chbits));
			break;
		case 'x':	/* extra line space */
			if (i = xlss())
				break;
			goto g0;
		case 'u':	/* half em up */
		case 'r':	/* full em up */
		case 'd':	/* half em down */
			i = sethl(k);
			break;
		default:
			i = j;
E 2
I 2
		return(i);
	case 's':	/* size indicator */
		setps();
		goto g0;
	case 'H':	/* character height */
		return(setht());
	case 'S':	/* slant */
		return(setslant());
	case 'f':	/* font indicator */
		setfont(0);
		goto g0;
	case 'w':	/* width function */
		setwd();
		goto g0;
	case 'v':	/* vert mot */
		if (i = vmot())
			return(i);
		goto g0;
	case 'h': 	/* horiz mot */
		if (i = hmot())
			return(i);
		goto g0;
	case 'z':	/* zero with char */
		return(setz());
	case 'l':	/* hor line */
		setline();
		goto g0;
	case 'L':	/* vert line */
		setvline();
		goto g0;
	case 'D':	/* drawing function */
		setdraw();
		goto g0;
	case 'b':	/* bracket */
		setbra();
		goto g0;
	case 'o':	/* overstrike */
		setov();
		goto g0;
	case 'k':	/* mark hor place */
		if ((k = findr(getsn())) != -1) {
			numtab[k].val = numtab[HP].val;
E 2
		}
D 2
	else {
		ch0 = j;
		i = eschar;
E 2
I 2
		goto g0;
	case '0':	/* number space */
		return(makem(width('0' | chbits)));
#ifdef NROFF
	case '|':
	case '^':
		goto g0;
#else
	case '|':	/* narrow space */
		return(makem((int)(EM)/6));
	case '^':	/* half narrow space */
		return(makem((int)(EM)/12));
#endif
	case 'x':	/* extra line space */
		if (i = xlss())
			return(i);
		goto g0;
	case 'u':	/* half em up */
	case 'r':	/* full em up */
	case 'd':	/* half em down */
		return(sethl(k));
	default:
		return(j);
E 2
	}
D 2
g2:
	if (cbits(i) == '\n') {
		nlflg++;
		v.hp = 0;
		pinchar = inchar;	/* XXX */
		if (ip == 0)
			v.cd++;	/* current input line number in this file */
	}
	if (!--level) {
		if (pinchar >= inchar + LNSIZE) {	/* XXX */
			inchar[0] = makem(sumhp());
			pinchar = &inchar[1];
		}
		*pinchar++ = i;	/* XXX */
	}
	return(i);
E 2
I 2
	/* NOTREACHED */
E 2
}

D 2

char	ifilt[32] = {
	0, 001, 002, 003, 0, 005, 006, 007, 010, 011, 012};


sumhp()	/* XXX - add up values in inchar */
E 2
I 2
setxon()	/* \X'...' for copy through */
E 2
{
D 2
	register int n;
	register tchar *p;
E 2
I 2
	tchar xbuf[NC];
	register tchar *i;
	tchar c;
	int delim, k;
E 2

D 2
	n = 0;
	for (p = inchar; p < pinchar; p++)
		n += width(*p);
	return(n);
E 2
I 2
	if (ismot(c = getch()))
		return;
	delim = cbits(c);
	i = xbuf;
	*i++ = XON;
	while ((k = cbits(c = getch())) != delim && k != '\n' && i < xbuf+NC-1) {
		if (k == ' ')
			setcbits(c, UNPAD);
		*i++ = c | ZBIT;
	}
	*i++ = XOFF;
	*i = 0;
	pushback(xbuf);
E 2
}


I 4
#ifdef notdef
E 4
I 2
char	ifilt[32] = {
	0, 001, 002, 003, 0, 005, 006, 007, 010, 011, 012};
I 4
#endif
E 4

E 2
tchar getch0()
{
	register int	j;
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2

D 2
	if (ch0) {
		i = ch0; 
		ch0 = 0; 
		return(i);
	}
	if (nchar) {
		nchar--; 
		return(rchar);
	}

E 2
again:
D 2
	if (cp) {
		if ((i = *cp++) == 0) {
			cp = 0;
			goto again;
		}
	} else if (ap) {
		if ((i = *ap++) == 0) {
			ap = 0;
			goto again;
		}
	} else if (ip) {
		if (ip == -1)
			i = rdtty();
		else 
E 2
I 2
	if (pbp > lastpbp)
		i = *--pbp;
	else if (ip) {
#ifdef INCORE
		extern tchar corebuf[];
		i = corebuf[ip];
		if (i == 0)
E 2
			i = rbf();
I 2
		else {
			if ((++ip & (BLK - 1)) == 0) {
				--ip;
				(void)rbf();
			}
		}
#else
		i = rbf();
#endif
E 2
	} else {
		if (donef)
			done(0);
		if (nx || ibufp >= eibuf) {
D 2
			if (nfo)
				goto g1;
E 2
I 2
			if (nfo==0) {
E 2
g0:
D 2
			if (nextfile()) {
				if (ip)
					goto again;
				if (ibufp < eibuf)
					goto g2;
E 2
I 2
				if (nextfile()) {
					if (ip)
						goto again;
					if (ibufp < eibuf)
						goto g2;
				}
E 2
			}
D 2
g1:
E 2
			nx = 0;
			if ((j = read(ifile, ibuf, IBUFSZ)) <= 0)
				goto g0;
			ibufp = ibuf;
			eibuf = ibuf + j;
			if (ip)
				goto again;
		}
g2:
		i = *ibufp++ & 0177;
		ioff++;
D 2
		if (i >= 040)
			goto g4; 
		else 
E 2
I 2
		if (i >= 040 && i < 0177)
			goto g4;
I 4
#ifdef notdef
E 4
		if (i != 0177) 
E 2
			i = ifilt[i];
I 4
#endif
E 4
	}
D 2
	if (raw)
		return(i);
	if ((j = cbits(i)) == IMP)
E 2
I 2
	if (cbits(i) == IMP && !raw)
E 2
		goto again;
D 2
	if ((i == 0) && !init)
E 2
I 2
	if ((i == 0 || i == 0177) && !init && !raw) {
E 2
		goto again;
I 2
	}
E 2
g4:
D 2
	if (copyf == 0 && (i & ~BMASK) == 0 && !iscontrol(cbits(i)))
E 2
I 2
	if (copyf == 0 && (i & ~BYTEMASK) == 0)
E 2
		i |= chbits;
D 2
	if (cbits(i) == eschar)
E 2
I 2
	if (cbits(i) == eschar && !raw)
E 2
		setcbits(i, ESC);
	return(i);
}

I 2
pushback(b)
register tchar *b;
{
	register tchar *ob = b;
E 2

I 2
	while (*b++)
		;
	b--;
	while (b > ob && pbp < &pbbuf[NC-3])
		*pbp++ = *--b;
	if (pbp >= &pbbuf[NC-3]) {
		errprint("pushback overflow");
		done(2);
	}
}

cpushback(b)
register char *b;
{
	register char *ob = b;

	while (*b++)
		;
	b--;
	while (b > ob && pbp < &pbbuf[NC-3])
		*pbp++ = *--b;
	if (pbp >= &pbbuf[NC-3]) {
		errprint("cpushback overflow");
		done(2);
	}
}

E 2
nextfile()
{
	register char	*p;

n0:
	if (ifile)
		close(ifile);
	if (nx) {
		p = nextf;
		if (*p != 0)
			goto n1;
	}
	if (ifi > 0) {
		if (popf())
			goto n0; /* popf error */
		return(1); /* popf ok */
	}
	if (rargc-- <= 0) {
D 2
		goto n2;
E 2
I 2
		if ((nfo -= mflg) && !stdi)
			done(0);
		nfo++;
		numtab[CD].val = ifile = stdi = mflg = 0;
		strcpy(cfname[ifi], "<standard input>");
		ioff = 0;
		return(0);
E 2
	}
	p = (argp++)[0];
n1:
D 2
	if ((p[0] == '-') && (p[1] == 0)) {
E 2
I 2
	numtab[CD].val = 0;
	if (p[0] == '-' && p[1] == 0) {
E 2
		ifile = 0;
I 2
		strcpy(cfname[ifi], "<standard input>");
E 2
	} else if ((ifile = open(p, 0)) < 0) {
D 2
		fprintf(stderr, "troff: cannot open %s\n", p);
E 2
I 2
		errprint("cannot open file %s", p);
E 2
		nfo -= mflg;
		done(02);
D 2
	}
E 2
I 2
	} else
		strcpy(cfname[ifi],p);
E 2
	nfo++;
D 2
	v.cd = 0;
E 2
	ioff = 0;
	return(0);
D 2
n2:
	if ((nfo -= mflg) && !stdi)
		done(0);
	nfo++;
	v.cd = ifile = stdi = mflg = 0;
	ioff = 0;
	return(0);
E 2
}


popf()
{
	register i;
	register char	*p, *q;
	extern char	*ttyname();

	ioff = offl[--ifi];
I 2
	numtab[CD].val = cfline[ifi];		/*restore line counter*/
E 2
	ip = ipl[ifi];
	if ((ifile = ifl[ifi]) == 0) {
		p = xbuf;
		q = ibuf;
		ibufp = xbufp;
		eibuf = xeibuf;
		while (q < eibuf)
			*q++ = *p++;
		return(0);
	}
D 2
	if ((lseek(ifile, (long)(ioff & ~(IBUFSZ - 1)), 0) < 0) || ((i = read(ifile, ibuf, IBUFSZ)) < 0))
E 2
I 2
	if (lseek(ifile, (long)(ioff & ~(IBUFSZ-1)), 0) == (long) -1
	   || (i = read(ifile, ibuf, IBUFSZ)) < 0)
E 2
		return(1);
	eibuf = ibuf + i;
	ibufp = ibuf;
	if (ttyname(ifile) == 0)
D 2
		if ((ibufp = ibuf + (int)(ioff & (IBUFSZ - 1))) >= eibuf)
E 2
I 2
		/* was >= ... */
		if ((ibufp = ibuf + (int)(ioff & (IBUFSZ - 1))) > eibuf)
E 2
			return(1);
	return(0);
}


flushi()
{
	if (nflush)
		return;
	ch = 0;
D 2
	if (cbits(ch0) == '\n')
		nlflg++;
	ch0 = 0;
E 2
	copyf++;
	while (!nlflg) {
		if (donef && (frame == stk))
			break;
		getch();
	}
	copyf--;
D 2
	v.hp = 0;
	pinchar = inchar;	/* XXX */
E 2
}


getach()
{
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2
	register j;

	lgf++;
	j = cbits(i = getch());
	if (ismot(i) || j == ' ' || j == '\n' || j & 0200) {
		ch = i;
		j = 0;
	}
	lgf--;
	return(j & 0177);
}


casenx()
{
	lgf++;
	skip();
	getname();
	nx++;
	nextfile();
	nlflg++;
	ip = 0;
D 2
	ap = 0;
	nchar = pendt = 0;
E 2
I 2
	pendt = 0;
E 2
	frame = stk;
	nxf = frame + 1;
}


getname()
{
	register int	j, k;
	tchar i;

	lgf++;
	for (k = 0; k < (NS - 1); k++) {
		if (((j = cbits(i = getch())) <= ' ') || (j > 0176))
			break;
		nextf[k] = j;
	}
	nextf[k] = 0;
	ch = i;
	lgf--;
	return(nextf[0]);
}


caseso()
{
	register i;
	register char	*p, *q;

	lgf++;
	nextf[0] = 0;
	if (skip() || !getname() || ((i = open(nextf, 0)) < 0) || (ifi >= NSO)) {
D 2
		fprintf(stderr, "troff: can't open file %s\n", nextf);
E 2
I 2
		errprint("can't open file %s", nextf);
E 2
		done(02);
	}
I 2
	strcpy(cfname[ifi+1], nextf);
	cfline[ifi] = numtab[CD].val;		/*hold line counter*/
	numtab[CD].val = 0;
E 2
	flushi();
	ifl[ifi] = ifile;
	ifile = i;
	offl[ifi] = ioff;
	ioff = 0;
	ipl[ifi] = ip;
	ip = 0;
	nx++;
	nflush++;
	if (!ifl[ifi++]) {
		p = ibuf;
		q = xbuf;
		xbufp = ibufp;
		xeibuf = eibuf;
		while (p < eibuf)
			*q++ = *p++;
	}
}

I 2
caself()	/* set line number and file */
{
	int n;
E 2

I 2
	if (skip())
		return;
	n = atoi();
	cfline[ifi] = numtab[CD].val = n - 2;
	if (skip())
		return;
	if (getname())
		strcpy(cfname[ifi], nextf);
}


E 2
casecf()
{	/* copy file without change */
#ifndef NROFF
	int	fd, n;
D 4
	char	buf[512];
E 4
I 4
	char	buf[8192];
E 4
D 2
	extern int	un, hpos, esc, po;

E 2
I 2
	extern int hpos, esc, po;
E 2
	nextf[0] = 0;
	if (skip() || !getname() || (fd = open(nextf, 0)) < 0) {
D 2
		fprintf(stderr, "troff: can't open file %s\n", nextf);
E 2
I 2
		errprint("can't open file %s", nextf);
E 2
		done(02);
	}
	tbreak();
	/* make it into a clean state, be sure that everything is out */
	hpos = po;
	esc = un;
	ptesc();
	ptlead();
	ptps();
	ptfont();
	flusho();
D 2
	while ((n = read(fd, buf, 512)) > 0)
E 2
I 2
	while ((n = read(fd, buf, sizeof buf)) > 0)
E 2
D 4
		write(ptid, buf, n);
E 4
I 4
		write(fileno(ptid), buf, n);
E 4
	close(fd);
#endif
}


D 2
casesy()
{	/* call system */
E 2
I 2
casesy()	/* call system */
{
E 2
	char	sybuf[NTM];
	int	i;

	lgf++;
	copyf++;
	skip();
	for (i = 0; i < NTM - 2; i++)
		if ((sybuf[i] = getch()) == '\n')
			break;
	sybuf[i] = 0;
	system(sybuf);
	copyf--;
I 2
	lgf--;
E 2
}


getpn(a)
	register char *a;
{
	register int n, neg;

	if (*a == 0)
		return;
	neg = 0;
	for ( ; *a; a++)
		switch (*a) {
		case '+':
		case ',':
			continue;
		case '-':
			neg = 1;
			continue;
		default:
			n = 0;
			if (isdigit(*a)) {
				do
					n = 10 * n + *a++ - '0';
				while (isdigit(*a));
				a--;
			} else
				n = 9999;
			*pnp++ = neg ? -n : n;
			neg = 0;
			if (pnp >= &pnlist[NPN-2]) {
D 2
				fprintf(stderr, "troff: too many page numbers\n");
E 2
I 2
				errprint("too many page numbers");
E 2
				done3(-3);
			}
		}
	if (neg)
		*pnp++ = -9999;
	*pnp = -32767;
	print = 0;
	pnp = pnlist;
	if (*pnp != -32767)
		chkpn();
}


setrpt()
{
	tchar i, j;

	copyf++;
	raw++;
	i = getch0();
	copyf--;
	raw--;
	if (i < 0 || cbits(j = getch0()) == RPT)
		return;
D 2
	rchar = j;
	nchar = i & BMASK;
E 2
I 2
	i &= BYTEMASK;
	while (i>0 && pbp < &pbbuf[NC-3]) {
		i--;
		*pbp++ = j;
	}
E 2
}
E 1
