h65239
s 00004/00003/00119
d D 8.6 94/06/01 21:50:52 bostic 6 5
c make it work better than once a second
e
s 00002/00002/00120
d D 8.5 94/04/05 12:30:08 bostic 5 4
c rewrite the test for clarity
e
s 00003/00002/00119
d D 8.4 94/04/05 07:18:40 pendry 4 3
c random wasn't.  now uses integer compare with 0, which does
e
s 00001/00001/00120
d D 8.3 94/03/31 08:52:23 bostic 3 2
c make man page and random usage match
e
s 00000/00001/00121
d D 8.2 94/03/31 08:51:20 bostic 2 1
c typo
e
s 00122/00000/00000
d D 8.1 94/03/31 08:50:52 bostic 1 0
c date and time created 94/03/31 08:50:52 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Guy Harris at Network Appliance Corp.
 *
D 2
 *
E 2
 * %sccs.include.redist.c%
 */

#ifndef lint
static char copyright[] =
"%Z% Copyright (c) 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 6
#include <sys/time.h>
E 6

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	extern int optind;
D 6
	time_t now;
E 6
I 6
	struct timeval tp;
E 6
	double denom;
	int ch, random_exit, selected, unbuffer_output;
	char *ep;

	random_exit = unbuffer_output = 0;
	while ((ch = getopt(argc, argv, "er")) != EOF)
		switch (ch) {
		case 'e':
			random_exit = 1;
			break;
		case 'r':
			unbuffer_output = 1;
			break;
		default:
		case '?':
			usage();
			/* NOTREACHED */
		}

	argc -= optind;
	argv += optind;

	switch (argc) {
	case 0:
		denom = 2;
		break;
	case 1:
		errno = 0;
		denom = strtod(*argv, &ep);
		if (errno == ERANGE)
			err(1, "%s", *argv);
		if (denom == 0 || *ep != '\0')
			errx(1, "denominator is not valid.");
		break;
	default:
		usage(); 
		/* NOTREACHED */
	}

D 6
	(void)time(&now);
	srandom((u_int)(now + getpid()));
E 6
I 6
	(void)gettimeofday(&tp, NULL);
	srandom((u_int)(tp.tv_usec + tp.tv_sec + getpid()));
E 6

	/* Compute a random exit status between 0 and denom - 1. */
	if (random_exit)
		return ((denom * random()) / LONG_MAX);

	/*
	 * Act as a filter, randomly choosing lines of the standard input
	 * to write to the standard output.
	 */
	if (unbuffer_output)
		setbuf(stdout, NULL);
	
	/*
	 * Select whether to print the first line.  (Prime the pump.)
	 * We find a random number between 0 and denom - 1 and, if it's
	 * 0 (which has a 1 / denom chance of being true), we select the
	 * line.
	 */
D 4
	selected = !((denom * random()) / LONG_MAX);
E 4
I 4
D 5
	selected = !(int)((denom * random()) / LONG_MAX);
E 5
I 5
	selected = (int)(denom * random() / LONG_MAX) == 0;
E 5
E 4
	while ((ch = getchar()) != EOF) {
		if (selected)
			(void)putchar(ch);
		if (ch == '\n') {
			/* End of that line.  See if we got an error. */
			if (ferror(stdout))
				err(2, "stdout");

			/* Now see if the next line is to be printed. */
D 4
			selected = !((denom * random()) / LONG_MAX);
E 4
I 4
D 5
			selected = !(int)((denom * random()) / LONG_MAX);
E 5
I 5
			selected = (int)(denom * random() / LONG_MAX) == 0;
E 5
E 4
		}
	}
	if (ferror(stdin))
		err(2, "stdin");
	exit (0);
}

void
usage()
{
I 4

E 4
D 3
	(void)fprintf(stderr, "usage: random [-er] [divisor]\n");
E 3
I 3
	(void)fprintf(stderr, "usage: random [-er] [denominator]\n");
E 3
	exit(1);
}
E 1
