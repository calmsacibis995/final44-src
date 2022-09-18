h43516
s 00014/00001/00302
d D 5.6 91/04/04 18:01:55 bostic 6 5
c new copyright; att/bsd/shared
e
s 00007/00002/00296
d D 5.5 91/01/31 17:57:59 torek 5 4
c waserr was never set; other minor gcc warnings fixed
e
s 00002/00002/00296
d D 5.4 89/09/15 16:11:24 bostic 4 3
c POSIX signals
e
s 00002/00001/00296
d D 5.3 89/05/08 12:54:09 bostic 3 2
c file system reorg; pathnames.h
e
s 00003/00002/00294
d D 5.2 89/01/17 17:43:57 torek 2 1
c oops, complain about a.out and core files iff given as arguments
e
s 00296/00000/00000
d D 5.1 89/01/16 20:24:45 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 6
I 1
#ifndef lint
I 6
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif
E 6
I 6
#endif /* not lint */
E 6

/*
 * adb - main command loop and error/interrupt handling
 */

#include "defs.h"
#include <setjmp.h>
#include <sys/file.h>
#include <sys/uio.h>
I 3
#include "pathnames.h"
E 3

extern char NOEOR[];		/* "newline expected" */

/*
 * executing is set by command.c whenever we are running a subprocess.
 */
int	executing;

int	infile;			/* XXX */
D 3
char	*Ipath = "/usr/lib/adb";/* XXX */
E 3
I 3
char	*Ipath = _PATH_SCRIPTS;	/* XXX */
E 3

static int xargc;		/* remembers argc for getfile() */

static int reading;		/* set whenever reading input */
static jmp_buf mainloop;	/* label for error jumps */

D 4
int	fault();
E 4
I 4
void	fault();
E 4
off_t	lseek();

I 5
static	int readline();

E 5
main(argc, argv)
	register int argc;
	register char **argv;
{
	int waserr;
	char line[LINELEN];

	radix = 16;		/* default radix is hex */
	maxoff = MAXOFF;
	maxcol = MAXCOL;

	/*
	 * Set up machine dependent code (e.g., instruction decoding tables),
	 * then look at arguments, and open the object and core files;
	 * finally, set up signal handlers.  Alas, cannot really use getopt.
	 */
	mch_init();
	symfile.name = "a.out";
	corefile.name = "core";
	while (argc > 1 && argv[1][0] == '-') {
		register char *p = argv[1] + 1;

		if (*p == 'w' && p[1] == 0) {
			wtflag = 2;	/* suitable for open() */
			argc--, argv++;
		} else if (*p == 'k' && p[1] == 0) {
			kernel = 1;
			argc--, argv++;
		} else if (*p == 'I') {
			Ipath = argv[1] + 2;
			argc--, argv++;
		} else
			break;
	}
	if (argc > 1)
		symfile.name = argv[1];
	if (argc > 2)
		corefile.name = argv[2];
	xargc = argc;		/* remember for getfile() */
	setsym();
	setcore();
	if ((sigint = signal(SIGINT, SIG_IGN)) != SIG_IGN) {
		intcatch = fault;
		(void) signal(SIGINT, fault);
	}
	sigquit = signal(SIGQUIT, SIG_IGN);

	/*
	 * Errors jump back to the main loop here.
	 * If the error occurred while the process was running,
	 * we need to remove any breakpoints.
	 */
D 5
	(void) setjmp(mainloop);
E 5
I 5
	if (setjmp(mainloop))
		waserr = 1;		/* well, presumably */
	else
		waserr = 0;
E 5
	if (executing) {
		executing = 0;
		delbp();
	}

	/*
	 * Main loop:
	 *	flush pending output, and print any error message(s);
	 *	read a line; if end of file, close current input and
	 *	continue, unless input == stdin; otherwise, perform
	 *	the command(s) on the line and make sure that that
	 *	consumed the whole line.
	 */
	for (;;) {
		flushbuf();
		if (errflag) {
			adbprintf("%s\n", errflag);
			waserr = 1;
			errflag = NULL;
		}
		if (mkfault) {
			mkfault = 0;
			prints("\nadb\n");
		}
		if (readline(line, sizeof line)) {
			if (infile == 0)
				done(waserr);
			iclose(-1, 0);
		} else {
			waserr = 0;
			command(line, 0);
			if (/* lp && */ lastc != '\n')
				errflag = NOEOR;
		}
	}
}

/*
 * Exit with optional error status.
 */
done(err)
	int err;
{

	endpcs();
	exit(err);
}

/*
 * Open the a.out (1) or core (2) file.  If the name was given,
 * rather than defaulted, and we were asked to open for writing,
 * create the file if necessary.
 */
getfile(which)
	int which;
{
	char *fname;
	int flags, fd;
I 2
	char *strerror();
E 2

	switch (which) {
	case 1:
		fname = symfile.name;
		break;
	case 2:
		fname = corefile.name;
		break;
	default:
		panic("getfile");
		/* NOTREACHED */
	}
	if (fname[0] == '-' && fname[1] == 0)
		return (-1);
	if ((flags = wtflag) != 0 && xargc > which)
		flags |= O_CREAT;
D 2
	if ((fd = open(fname, flags, 0666)) < 0 && flags & O_CREAT)
		adbprintf("cannot open `%s'\n", fname);
E 2
I 2
	if ((fd = open(fname, flags, 0666)) < 0 && xargc > which)
		adbprintf("cannot open `%s': %s\n", fname, strerror(errno));
E 2
	return (fd);
}


/*
 * Input routines
 */

/*
 * Read a character, skipping white space.
 */
rdc()
{

	while (*lp == ' ' || *lp == '\t')
		lp++;
	return (readchar());
}

#ifndef readchar
/*
 * Read a character, incrementing the pointer if not at end.
 */
readchar()
{

	if ((lastc = *lp) != 0)
		lp++;
	return (lastc);
}
#endif

/*
 * Read a line.  Return -1 at end of file.
 * Alas, cannot read more than one character at a time here (except
 * possibly on tty devices; must think about that later).
 */
D 5
static
E 5
I 5
static int
E 5
readline(p, n)
	register char *p;
	register int n;
{

	n--;		/* for \0 */
	reading++;
	do {
		if (--n > 0) {
			if (read(infile, p, 1) != 1)
				return (-1);
		} else 
			*p = '\n';
	} while (*p++ != '\n');
	reading = 0;
	*p = 0;		/* can we perhaps eliminate this? */
	return (0);
}

/*
 * Return the next non-white non-end-of-line character.
 */
nextchar()
{
	int c = rdc();

	if (eol(c)) {
		unreadc();
		return (0);
	}
	return (c);
}


/*
 * Error handlers
 */

#ifndef checkerr
/*
 * If there has been an error or a fault, take the error.
 */
checkerr()
{

	if (errflag || mkfault)
		error(errflag);
}
#endif

/*
 * An error occurred.  Save the message for later printing,
 * close open files, and reset to main command loop.
 */
error(which)
	char *which;
{

	errflag = which;
	iclose(0, 1);
	oclose();
	longjmp(mainloop, 1);
	/* NOTREACHED */
}

/*
 * An interrupt occurred.  Seek to the end of the current input file.
 * If we were reading commands, jump back to the main loop.
 */
/* ARGSUSED */
I 4
void
E 4
fault(sig)
	int sig;
{
D 4

E 4
	/* (void) signal(sig, fault); */	/* unnecessary */
	(void) lseek(infile, 0L, 2);
	mkfault++;
	if (reading) {
		reading = 0;
		error((char *)NULL);
	}
}

/*
 * Panic announces an internally detected error.
 */
panic(s)
	char *s;
{
	static char p[] = "panic: \n";
	static struct iovec iov[3] = { { p, 7 }, { 0 }, { p + 7, 1 } };

	iov[1].iov_base = s;
	iov[1].iov_len = strlen(s);
	(void) writev(2, iov, 3);
	abort();	/* beware, overwrites current core file! */
/*	exit(1); */
}
E 1
