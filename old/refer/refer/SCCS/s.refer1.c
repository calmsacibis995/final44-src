h13041
s 00006/00002/00165
d D 4.6 91/04/18 16:44:09 bostic 6 5
c new copyright; att/bsd/shared
e
s 00003/00002/00164
d D 4.5 91/03/01 15:29:47 bostic 5 4
c ANSI
e
s 00004/00003/00162
d D 4.4 89/05/11 10:04:52 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00011/00010/00154
d D 4.3 86/04/23 18:19:07 mckusick 3 2
c fix sequencing numbers (from Keith Muller)
e
s 00001/00001/00163
d D 4.2 85/08/26 19:13:32 mckusick 2 1
c fix syntax errors
e
s 00164/00000/00000
d D 4.1 83/05/06 23:30:05 tut 1 0
c date and time created 83/05/06 23:30:05 by tut
e
u
U
t
T
I 6
/*-
 * %sccs.include.proprietary.c%
 */

E 6
I 1
#ifndef lint
D 6
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 6
I 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

#include <signal.h>
#include "refer..c"
I 4
#include "pathnames.h"
E 4

main(argc,argv)		/* process command-line arguments */
char *argv[];
{
	char line[BUFSIZ], *s;
	int nodeflt = 0;

	signals();
	while (argv[1][0] == '-') {
		switch(argv[1][1]) {
		case 'e':
			endpush++; 
			break;
		case 's':
			sort++;
			endpush = 1;
			if (argv[1][2])
				keystr = argv[1]+2;
			break;
		case 'l': 
			labels++;
			s = argv[1]+2;
			nmlen = atoi(s);
			while (*s)
				if (*s++ == ',')
					break;
			dtlen = atoi(s);
			break;
		case 'k':
			keywant = (argv[1][2] ? argv[1][2] : 'L');
			labels++;
			break;
		case 'n':
			nodeflt = 1;
			break;
		case 'p':
			argc--; 
			argv++;
			*search++ = argv[1];
			if (search-rdata > NSERCH)
				err("too many -p options (%d)", NSERCH);
			break;
		case 'a':
			authrev = atoi(argv[1]+2);
			if (authrev<=0)
				authrev = 1000;
			break;
		case 'b':
			bare = (argv[1][2] == '1') ? 1 : 2;
			break;
		case 'c':
			smallcaps = argv[1]+2;
			break;
		case 'f':
			refnum = atoi(argv[1]+2) - 1;
			break;
		case 'B':
			biblio++;
			bare = 2;
			if (argv[1][2])
				convert = argv[1]+2;
			break;
		case 'S':
			science++;
			labels = 1;
			break;
		case 'P':
			postpunct++;
			break;
		}
		argc--; 
		argv++;
	}
	if (getenv("REFER") != NULL)
		*search++ = getenv("REFER");
	else if (nodeflt == 0)
D 4
		*search++ = "/usr/dict/papers/Ind";
E 4
I 4
		*search++ = _PATH_IND;
E 4
I 3
	if (!labels) {
D 4
		sprintf(ofile, "/tmp/rj%db", getpid());
E 4
I 4
		sprintf(ofile, "%s/rj%db", _PATH_TMP, getpid());
E 4
		ftemp = fopen(ofile, "w");
		if (ftemp == NULL) {
			fprintf(stderr, "Can't open scratch file\n");
			exit(1);
		}
	}
E 3
	if (endpush) {
D 4
		sprintf(tfile, "/tmp/rj%da", getpid());
E 4
I 4
		sprintf(tfile, "%s/rj%da", _PATH_TMP, getpid());
E 4
		fo = fopen(tfile, "w");
		if (fo == NULL) {
			fo = ftemp;
			fprintf(stderr, "Can't open scratch file");
		}
		sep = 002; /* separate records without confusing sort..*/
D 3
	}
	if (sort && !labels) {
		sprintf(ofile, "/tmp/rj%db", getpid());
		ftemp = fopen(ofile, "w");
		if (ftemp == NULL) {
			fprintf(stderr, "Can't open scratch file\n");
			exit(1);
		}
	}
E 3
I 3
	} else 
		fo = ftemp;
E 3
	do {
		if (argc > 1) {
			fclose(in);
			Iline = 0;
			in = fopen(Ifile = argv[1], "r");
			argc--; 
			argv++;
			if (in == NULL) {
D 2
				err("Can't read %s", (void) Ifile);
E 2
I 2
				err("Can't read %s", Ifile);
E 2
				continue;
			}
		}
		while (input(line)) {
			Iline++;
			if (biblio && *line == '\n')
				doref(line);
			else if (biblio && Iline == 1 && *line == '%')
				doref(line);
			else if (!prefix(".[", line))
				output(line);
			else
				doref(line);
		}
	} while (argc > 1);

	if (endpush && fo != NULL)
		dumpold();
	output("");
D 3
	if (sort && !labels)
E 3
I 3
	if (!labels)
E 3
		recopy(ofile);
	clfgrep();
	cleanup();
	exit(0);
}

D 5
extern int intr();

E 5
signals()
{
I 5
	void intr();

E 5
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, intr);
	signal(SIGHUP, intr);
	signal(SIGPIPE, intr);
	signal(SIGTERM, intr);
}

I 5
void
E 5
intr()
{
	signal(SIGINT, SIG_IGN);
	cleanup();
	exit(1);
}

cleanup()
{
	if (tfile[0])
		unlink(tfile);
	if (gfile[0])
		unlink(gfile);
	if (ofile[0])
		unlink(ofile);
	if (hidenam[0])
		unlink(hidenam);
}
E 1
