h41011
s 00001/00001/00272
d D 1.5 90/06/24 18:32:22 trent 5 4
c signal int to void
e
s 00011/00011/00262
d D 1.4 86/06/05 23:06:42 lepreau 4 3
c lint
e
s 00167/00101/00106
d D 1.3 86/06/05 22:59:31 lepreau 3 2
c handle stdin via temp file.  This code needlessly uses temp file
c in case 'tac <file' but who's  going to do that?  Also should stat the temp 
c file to determine optimum klsize for write's to it.
e
s 00004/00003/00203
d D 1.2 86/01/11 00:51:35 lepreau 2 1
c give pike some credit
e
s 00206/00000/00000
d D 1.1 85/06/09 01:42:35 lepreau 1 0
c date and time created 85/06/09 01:42:35 by lepreau
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% %G%";
#endif

/*
 * tac.c - Print file segments in reverse order
 *
 * Original line-only version by unknown author off the net.
D 2
 * 1985 mods by Jay Lepreau, Univ of Utah, to allocate memory dynamically
 * and handle string bounded segments.
E 2
I 2
D 3
 * 1985 mods by Jay Lepreau, Univ of Utah, to allocate memory
 * dynamically and handle string bounded segments (latter idea
 * suggested by Rob Pike).
E 3
I 3
 * Rewritten in 1985 by Jay Lepreau, Univ of Utah, to allocate memory
 * dynamically, handle string bounded segments (suggested by Rob Pike),
 * and handle pipes.
E 3
E 2
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
I 3
#include <signal.h>
E 3

/*
 * This should be defined for BSD releases later than 4.2 and for Sys V.2,
 * at least.  fwrite is faster than putc only if you have a new speedy fwrite.
 */
#define FAST_FWRITE

#ifdef DEBUG				/* dbx can't handle registers */
#include <ctype.h>
# define register
#endif

/* Default target string and bound */
int right = 1;				/* right or left bounded segments? */
char *targ = "\n";

I 3
char *tfile;
char *buf;

E 3
int readsize = 4096;			/* significantly faster than 1024 */
int bufsize;
int targlen;
int numerr;

I 3
int cleanup();
E 3
extern off_t lseek();
D 3
extern char *malloc(), *realloc();
E 3
I 3
D 4
extern char *malloc(), *realloc(), *mktemp();
E 4
I 4
extern char *strcpy(), *malloc(), *realloc(), *mktemp();
E 4
E 3

main(argc, argv)
    int argc;
    char **argv;
{
D 3
    register char *p, *pastend;
    register int firstchar, targm1len;	/* target length minus 1 */
    int fd, i;
    off_t off;
    char *buf;
    struct stat st;
E 3

D 3
    if (argc < 2) {
	(void) fprintf(stderr, "Usage: tac [-string | +string] file ...\n");
	exit(1);
    }

E 3
#ifdef DEBUG
D 3
    if (isdigit(*argv[1])) {
E 3
I 3
    if (argc > 1 && isdigit(*argv[1])) {
E 3
	readsize = atoi(argv[1]);
	argc--, argv++;
    }
#endif
    
D 3
    if (argv[1][0] == '+' || argv[1][0] == '-') {
E 3
I 3
    if (argc > 1 && (argv[1][0] == '+' || argv[1][0] == '-') && argv[1][1]) {
E 3
	targ = &argv[1][1];
	right = (argv[1][0] == '+');
	argc--; argv++;
    }
D 3
    firstchar = *targ;
E 3
    targlen = strlen(targ);
D 3
    targm1len = targlen - 1;
E 3

    bufsize = (readsize << 1) + targlen + 2;
    if ((buf = malloc((unsigned) bufsize)) == NULL) {
	perror("tac: initial malloc");
	exit(1);
    }

    (void) strcpy(buf, targ);		/* stop string at beginning */
    buf += targlen;

I 3
    if (argc == 1)
	tacstdin();
E 3
    while (--argc) {
D 3
	if (stat(p = *++argv, &st) < 0) {
	    prterr(p);
	    numerr++;
	    continue;
	}
	if ((off = st.st_size) == 0)
	    continue;
	if ((fd = open(p, 0)) < 0) {
	    prterr(p);
	    numerr++;
	    continue;
	}
E 3
I 3
	if (strcmp(*++argv, "-") == 0)
	    tacstdin();
	else
	    tacit(*argv);
    }
    exit(numerr > 0 ? 1 : 0);
}
E 3

D 3
	/*
	 * Arrange for the first read to lop off enough to
	 * leave the rest of the file a multiple of readsize.
	 * Since readsize can change, this may not always hold during
	 * the pgm run, but since it usually will, leave it here
	 * for i/o efficiency (page/sector boundaries and all that).
D 2
	 * Note: Above statement has never been verified!
E 2
I 2
	 * Note: the efficiency gain has never been verified...
E 2
	 */
	if ((i = off % readsize) == 0)
	    i = readsize;
	off -= i;
E 3
I 3
tacstdin()
{
E 3

D 3
	(void) lseek(fd, off, 0);
	if (read(fd, buf, i) != i) {
	    prterr(p);
	    (void) close(fd);
	    numerr++;
	    continue;
E 3
I 3
D 5
    int (*sigint)(), (*sighup)(), (*sigterm)();
E 5
I 5
    void (*sigint)(), (*sighup)(), (*sigterm)();
E 5

    if ((sigint = signal(SIGINT, SIG_IGN)) != SIG_IGN)
D 4
	signal(SIGINT, cleanup);
E 4
I 4
	(void) signal(SIGINT, cleanup);
E 4
    if ((sighup = signal(SIGHUP, SIG_IGN)) != SIG_IGN)
D 4
	signal(SIGHUP, cleanup);
E 4
I 4
	(void) signal(SIGHUP, cleanup);
E 4
    if ((sigterm = signal(SIGTERM, SIG_IGN)) != SIG_IGN)
D 4
	signal(SIGTERM, cleanup);
E 4
I 4
	(void) signal(SIGTERM, cleanup);
E 4

    savestdin();
    tacit(tfile);
D 4
    unlink(tfile);
E 4
I 4
    (void) unlink(tfile);
E 4

D 4
    signal(SIGINT, sigint);
    signal(SIGHUP, sighup);
    signal(SIGTERM, sigterm);
E 4
I 4
    (void) signal(SIGINT, sigint);
    (void) signal(SIGHUP, sighup);
    (void) signal(SIGTERM, sigterm);
E 4
}

char template[] = "/tmp/tacXXXXXX";
char workplate[sizeof template];

savestdin()
{
    int fd;
    register int n;

D 4
    strcpy(workplate, template);
E 4
I 4
    (void) strcpy(workplate, template);
E 4
    tfile = mktemp(workplate);
    if ((fd = creat(tfile, 0600)) < 0) {
	prterr(tfile);
	cleanup();
    }
    while ((n = read(0, buf, readsize)) > 0)
	if (write(fd, buf, n) != n) {
	    prterr(tfile);
	    cleanup();
E 3
	}
D 3
	p = pastend = buf + i;		/* pastend always points to end+1 */
	p -= targm1len;
E 3
I 3
D 4
    close(fd);
E 4
I 4
    (void) close(fd);
E 4
    if (n < 0) {
	prterr("stdin read");
	cleanup();
    }
}
E 3

D 3
	for (;;) {
	    while ( *--p != firstchar ||
	      (targm1len && strncmp(p+1, targ+1, targm1len)) )
		continue;
	    if (p < buf) {		/* backed off front of buffer */
		if (off == 0) {
		    /* beginning of file: dump last segment */
		    output(p + targlen, pastend);
		    (void) close(fd);
		    break;
		}
		if ((i = pastend - buf) > readsize) {
		    char *tbuf;
		    int newbufsize = (readsize << 2) + targlen + 2;
		    
		    if ((tbuf = realloc(buf-targlen, (unsigned) newbufsize)) == NULL) {
			/* If realloc fails, old buf contents may be lost. */
			perror("tac: segment too long; may have garbage here");
			numerr++;
			i = readsize;
		    }
		    else {
			tbuf += targlen;	/* skip over the stop string */
			p += tbuf - buf;
			pastend += tbuf - buf;
			buf = tbuf;
			bufsize = newbufsize;
			readsize = readsize << 1;
			/* guaranteed to fit now (I think!) */
		    }
		}
		if (off - readsize < 0) {
		    readsize = off;
		    off = 0;
		}
		else
		    off -= readsize;
		(void) lseek(fd, off, 0);	/* back up */
		/* Shift pending old data right to make room for new */
		bcopy(buf, p = buf + readsize, i);
		pastend = p + i;
		if (read(fd, buf, readsize) != readsize) {
		    prterr(*argv);
E 3
I 3
tacit(name)
    char *name;
{
    register char *p, *pastend;
    register int firstchar, targm1len;	/* target length minus 1 */
    struct stat st;
    off_t off;
    int fd, i;

    firstchar = *targ;
    targm1len = targlen - 1;

    if (stat(name, &st) < 0) {
	prterr(name);
	numerr++;
	return;
    }
    if ((off = st.st_size) == 0)
	return;
    if ((fd = open(name, 0)) < 0) {
	prterr(name);
	numerr++;
	return;
    }

    /*
     * Arrange for the first read to lop off enough to
     * leave the rest of the file a multiple of readsize.
     * Since readsize can change, this may not always hold during
     * the pgm run, but since it usually will, leave it here
     * for i/o efficiency (page/sector boundaries and all that).
     * Note: the efficiency gain has not been verified.
     */
    if ((i = off % readsize) == 0)
	i = readsize;
    off -= i;

    (void) lseek(fd, off, 0);
    if (read(fd, buf, i) != i) {
	prterr(name);
	(void) close(fd);
	numerr++;
	return;
    }
    p = pastend = buf + i;		/* pastend always points to end+1 */
    p -= targm1len;

    for (;;) {
	while ( *--p != firstchar ||
	  (targm1len && strncmp(p+1, targ+1, targm1len)) )
	    continue;
	if (p < buf) {		/* backed off front of buffer */
	    if (off == 0) {
		/* beginning of file: dump last segment */
		output(p + targlen, pastend);
		(void) close(fd);
		break;
	    }
	    if ((i = pastend - buf) > readsize) {
		char *tbuf;
		int newbufsize = (readsize << 2) + targlen + 2;
		
		if ((tbuf = realloc(buf-targlen, (unsigned) newbufsize)) == NULL) {
		    /* If realloc fails, old buf contents may be lost. */
		    perror("tac: segment too long; may have garbage here");
E 3
		    numerr++;
D 3
		    (void) close(fd);
		    break;
E 3
I 3
		    i = readsize;
E 3
		}
D 3
		continue;
E 3
I 3
		else {
		    tbuf += targlen;	/* skip over the stop string */
		    p += tbuf - buf;
		    pastend += tbuf - buf;
		    buf = tbuf;
		    bufsize = newbufsize;
		    readsize = readsize << 1;
		    /* guaranteed to fit now (I think!) */
		}
E 3
	    }
D 3
	    /* Found a real instance of the target string */
	    output(right ? p + targlen : p, pastend);
	    pastend = p;
	    p -= targm1len;
E 3
I 3
	    if (off - readsize < 0) {
		readsize = off;
		off = 0;
	    }
	    else
		off -= readsize;
	    (void) lseek(fd, off, 0);	/* back up */
	    /* Shift pending old data right to make room for new */
	    bcopy(buf, p = buf + readsize, i);
	    pastend = p + i;
	    if (read(fd, buf, readsize) != readsize) {
		prterr(name);
		numerr++;
		(void) close(fd);
		break;
	    }
	    continue;
E 3
	}
I 3
	/* Found a real instance of the target string */
	output(right ? p + targlen : p, pastend);
	pastend = p;
	p -= targm1len;
E 3
    }
D 3
    exit(numerr);
E 3
}

/*
 * Dump chars from p to pastend-1.  If right-bounded by target
 * and not the first time through, append the target string.
 */
output(p, pastend)
    register char *p;
    char *pastend;
{
    static short first = 1;

#ifdef FAST_FWRITE
    (void) fwrite(p, 1, pastend - p, stdout);
#else
    while (p < pastend)
	(void) putc(*p++, stdout);
#endif
    if (right && !first)
	(void) fwrite(targ, 1, targlen, stdout);
    first = 0;
    if ferror(stdout) {
	perror("tac: fwrite/putc");
	exit(++numerr > 1 ? numerr : 1);
    }
}

prterr(s)
    char *s;
{

    fprintf(stderr, "tac: ");
    perror(s);
I 3
}

cleanup()
{

D 4
    unlink(tfile);
E 4
I 4
    (void) unlink(tfile);
E 4
    exit(1);
E 3
}
E 1
