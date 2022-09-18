h60849
s 00005/00005/00223
d D 8.1 93/06/06 14:36:42 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00227
d D 4.10 93/04/05 21:47:55 ralph 10 9
c use Start instead of start. Conflicts with start in crt0.o (mips).
e
s 00016/00001/00212
d D 4.9 91/04/17 17:19:26 bostic 9 8
c new copyright; att/bsd/shared
e
s 00001/00000/00212
d D 4.8 91/03/01 13:49:01 bostic 8 7
c ANSI
e
s 00005/00003/00207
d D 4.7 89/05/11 09:59:08 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00208
d D 4.6 86/04/03 08:15:28 lepreau 6 5
c avoid unlink(0)
e
s 00004/00001/00205
d D 4.5 85/08/16 21:12:22 van 5 4
c added -n flag from rcs diff
e
s 00009/00000/00197
d D 4.4 85/06/07 03:02:39 van 4 3
c added -w, -i & -t flags.  Changed -c output to group together
c adjacent changes.
e
s 00005/00008/00192
d D 4.3 85/06/03 23:13:30 lepreau 3 2
c speedup by pitching the "compacting" realloc, which loses with new malloc
e
s 00000/00002/00200
d D 4.2 84/05/14 16:14:56 ralph 2 1
c don't call setbuf; use optimal size.
e
s 00202/00000/00000
d D 4.1 80/10/09 22:46:38 bill 1 0
c date and time created 80/10/09 22:46:38 by bill
e
u
U
t
T
I 1
D 9
static	char sccsid[] = "%Z%%M% %I% %G%";
E 9
I 9
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
D 11
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 9

#include "diff.h"
I 7
#include "pathnames.h"

E 7
/*
 * diff - driver and subroutines
 */

D 7
char	diff[] = DIFF;
char	diffh[] = DIFFH;
char	pr[] = PR;
E 7
I 7
char	diff[] = _PATH_DIFF;
char	diffh[] = _PATH_DIFFH;
char	pr[] = _PATH_PR;
E 7
D 2
extern	char _sobuf[];
E 2

main(argc, argv)
	int argc;
	char **argv;
{
	register char *argp;

	ifdef1 = "FILE1"; ifdef2 = "FILE2";
	status = 2;
	diffargv = argv;
D 2
	setbuf(stdout, _sobuf);
E 2
	argc--, argv++;
	while (argc > 2 && argv[0][0] == '-') {
		argp = &argv[0][1];
		argv++, argc--;
		while (*argp) switch(*argp++) {

#ifdef notdef
		case 'I':
			opt = D_IFDEF;
			wantelses = 0;
			continue;
		case 'E':
			opt = D_IFDEF;
			wantelses = 1;
			continue;
		case '1':
			opt = D_IFDEF;
			ifdef1 = argp;
			*--argp = 0;
			continue;
#endif
		case 'D':
			/* -Dfoo = -E -1 -2foo */
			wantelses = 1;
			ifdef1 = "";
			/* fall through */
#ifdef notdef
		case '2':
#endif
			opt = D_IFDEF;
			ifdef2 = argp;
			*--argp = 0;
			continue;
		case 'e':
			opt = D_EDIT;
			continue;
		case 'f':
			opt = D_REVERSE;
			continue;
I 5
		case 'n':
			opt = D_NREVERSE;
			continue;
E 5
		case 'b':
			bflag = 1;
			continue;
I 4
		case 'w':
			wflag = 1;
			continue;
		case 'i':
			iflag = 1;
			continue;
		case 't':
			tflag = 1;
			continue;
E 4
		case 'c':
			opt = D_CONTEXT;
			if (isdigit(*argp)) {
				context = atoi(argp);
				while (isdigit(*argp))
					argp++;
				if (*argp) {
					fprintf(stderr,
					    "diff: -c: bad count\n");
					done();
				}
				argp = "";
			} else
				context = 3;
			continue;
		case 'h':
			hflag++;
			continue;
		case 'S':
			if (*argp == 0) {
				fprintf(stderr, "diff: use -Sstart\n");
				done();
			}
D 10
			start = argp;
E 10
I 10
			Start = argp;
E 10
			*--argp = 0;		/* don't pass it on */
			continue;
		case 'r':
			rflag++;
			continue;
		case 's':
			sflag++;
			continue;
		case 'l':
			lflag++;
			continue;
		default:
			fprintf(stderr, "diff: -%s: unknown option\n",
			    --argp);
			done();
		}
	}
	if (argc != 2) {
		fprintf(stderr, "diff: two filename arguments required\n");
		done();
	}
	file1 = argv[0];
	file2 = argv[1];
	if (hflag && opt) {
		fprintf(stderr,
D 5
		    "diff: -h doesn't support -e, -f, -c, or -I\n");
E 5
I 5
		    "diff: -h doesn't support -e, -f, -n, -c, or -I\n");
E 5
		done();
	}
	if (!strcmp(file1, "-"))
		stb1.st_mode = S_IFREG;
	else if (stat(file1, &stb1) < 0) {
		fprintf(stderr, "diff: ");
		perror(file1);
		done();
	}
	if (!strcmp(file2, "-"))
		stb2.st_mode = S_IFREG;
	else if (stat(file2, &stb2) < 0) {
		fprintf(stderr, "diff: ");
		perror(file2);
		done();
	}
	if ((stb1.st_mode & S_IFMT) == S_IFDIR &&
	    (stb2.st_mode & S_IFMT) == S_IFDIR) {
		diffdir(argv);
	} else
		diffreg();
	done();
}

char *
savestr(cp)
	register char *cp;
{
	register char *dp = malloc(strlen(cp)+1);

	if (dp == 0) {
		fprintf(stderr, "diff: ran out of memory\n");
		done();
	}
	strcpy(dp, cp);
	return (dp);
}

min(a,b)
	int a,b;
{

	return (a < b ? a : b);
}

max(a,b)
	int a,b;
{

	return (a > b ? a : b);
}

I 8
void
E 8
done()
{
D 6
	unlink(tempfile);
E 6
I 6
	if (tempfile)
		unlink(tempfile);
E 6
	exit(status);
}

char *
talloc(n)
{
	register char *p;
D 3
	p = malloc((unsigned)n);
	if(p!=NULL)
E 3
I 3

	if ((p = malloc((unsigned)n)) != NULL)
E 3
		return(p);
	noroom();
}

char *
D 3
ralloc(p,n)	/*compacting reallocation */
E 3
I 3
ralloc(p,n)
E 3
char *p;
{
	register char *q;
	char *realloc();
D 3
	free(p);
	free(dummy);
	dummy = malloc(1);
	q = realloc(p, (unsigned)n);
	if(q==NULL)
E 3
I 3

	if ((q = realloc(p, (unsigned)n)) == NULL)
E 3
		noroom();
	return(q);
}

noroom()
{
	fprintf(stderr, "diff: files too big, try -h\n");
	done();
}
E 1
