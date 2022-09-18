h54667
s 00005/00005/00255
d D 8.1 93/06/06 16:29:12 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00259
d D 5.16 93/05/21 15:34:18 mckusick 25 24
c update header to reflect redistributable status
e
s 00000/00002/00260
d D 5.15 93/05/12 12:37:35 elan 24 23
c No private suspend routine for systat (use curses).
e
s 00014/00004/00248
d D 5.14 92/11/12 13:48:33 elan 23 22
c Changed errror() to go through curses(3) rather than to stderr.
e
s 00011/00010/00241
d D 5.13 92/09/02 11:56:33 bostic 22 21
c nl is an exported curses function
e
s 00004/00004/00247
d D 5.12 92/07/24 12:41:19 bostic 21 20
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00090/00029/00161
d D 5.11 92/07/23 18:03:16 bostic 20 19
c Elan's new kvm version; update copyright header, lots of lint
e
s 00010/00045/00180
d D 5.10 91/06/26 13:50:24 marc 19 18
c changes for new kernel, plus use kvm
e
s 00004/00004/00221
d D 5.9 91/04/25 14:29:06 bostic 18 17
c ANSI
e
s 00015/00006/00210
d D 5.8 91/02/04 23:19:02 torek 17 16
c fix gcc-detected lint
e
s 00004/00001/00212
d D 5.7 90/03/12 09:34:37 karels 16 15
c new signal type; mv cursor to bottom when interrupted
e
s 00001/00001/00212
d D 5.6 89/05/29 17:25:16 mckusick 15 14
c minor cleanup
e
s 00008/00010/00205
d D 5.5 89/05/29 17:17:15 mckusick 14 13
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00043/00045/00172
d D 5.4 89/05/11 10:57:46 bostic 13 12
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00002/00002/00215
d D 5.3 87/03/26 00:30:34 tef 12 11
c Get the right args on the command line; allow naptimes < 5 seconds.
e
s 00002/00001/00215
d D 5.2 85/08/13 11:08:57 mckusick 11 10
c let curses handle SIGTSTP
e
s 00013/00001/00203
d D 5.1 85/05/30 16:23:42 mckusick 10 9
c Add copyright
e
s 00005/00014/00199
d D 1.9 85/05/01 01:34:07 sam 9 8
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00041/00024/00172
d D 1.8 85/04/28 00:37:34 sam 8 7
c add vsta in; add help command (minimal); make loadav display something 
c which can be turned off
e
s 00013/00004/00183
d D 1.7 84/08/09 19:12:54 mckusick 7 6
c update to new sources from sam; weed out unnecessary #includes
e
s 00002/00006/00185
d D 1.6 83/10/02 21:59:58 sam 6 5
c add command prefix recognition
e
s 00021/00011/00170
d D 1.5 83/10/02 21:31:55 sam 5 4
c put load average in a separate window; make idle process be 
c named <idle> (instead of using name field)
e
s 00050/00235/00131
d D 1.4 83/10/02 20:45:34 sam 4 3
c reorganize window management to allow display routines to set 
c up optimal window definitions
e
s 00040/00010/00326
d D 1.3 83/10/02 14:40:20 sam 3 2
c add init routine and mbuf display; redo swap space display
e
s 00042/00012/00294
d D 1.2 83/10/01 21:22:27 sam 2 1
c add command from arg line, addition of 1st version of swap usage
e
s 00306/00000/00000
d D 1.1 83/10/01 12:20:59 sam 1 0
c date and time created 83/10/01 12:20:59 by sam
e
u
U
t
T
I 10
D 20
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
/*-
D 26
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 25
 * %sccs.include.proprietary.c%
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 20
 */

E 10
I 1
D 2
/*% cc -a % -lcurses -ltermlib -lm
 */
E 2
#ifndef lint
I 10
D 26
char copyright[] =
D 20
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 20
I 20
"%Z% Copyright (c) 1980, 1992 The Regents of the University of California.\n\
E 20
 All rights reserved.\n";
E 26
I 26
static char copyright[] =
"%Z% Copyright (c) 1980, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 26
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20

#ifndef lint
E 10
D 9
static char sccsid[] = "%W% (Lucasfilm) %G%";
E 9
I 9
static char sccsid[] = "%W% (Berkeley) %G%";
E 9
D 10
#endif
E 10
I 10
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20
E 10

I 20
#include <sys/param.h>

#include <nlist.h>
#include <signal.h>
#include <stdio.h>
E 20
#include "systat.h"
I 17
D 20
#include <varargs.h>
E 20
I 20
#include "extern.h"
E 20
E 17
I 13
D 19
#include <paths.h>
E 19
E 13
I 7
D 9
#include <sys/file.h>
#include <nlist.h>
#include <signal.h>
E 9
E 7

D 4
struct nlist nlst[] = {
#define X_PROC          0
        { "_proc" },
#define X_NPROC         1
        { "_nproc" },
#define X_CCPU          2
E 4
I 4
D 21
static struct nlist nlst[] = {
E 21
I 21
D 22
static struct nlist nl[] = {
E 22
I 22
static struct nlist namelist[] = {
E 22
E 21
D 19
#define X_CCPU          0
E 4
D 13
        { "_ccpu" },
E 13
I 13
	{ "_ccpu" },
E 13
D 4
#define X_AVENRUN       3
E 4
I 4
D 14
#define X_AVENRUN       1
E 4
D 13
        { "_avenrun" },
E 13
I 13
	{ "_avenrun" },
E 14
I 14
#define X_FSCALE	1
	{ "_fscale" },
E 14
E 13
I 8
D 9
#define	X_DK_MSPW	2
	{ "_dk_mspw" },
#define	X_HZ		3
E 9
I 9
#define	X_HZ		2
E 19
I 19
#define X_FIRST		0
#define	X_HZ		0
E 19
E 9
	{ "_hz" },
D 9
#define	X_PHZ		4
E 9
I 9
D 19
#define	X_PHZ		3
E 19
I 19
D 20
#define	X_PHZ		1
E 19
E 9
	{ "_phz" },
E 20
I 20
#define	X_STATHZ		1
	{ "_stathz" },
E 20
E 8
D 4
#define X_USRPTMAP      4
        { "_Usrptmap" },
#define X_USRPT         5
        { "_usrpt" },
#define X_NSWAP         6
        { "_nswap" },
#define X_SWAPMAP       7
        { "_swapmap" },
#define X_NSWAPMAP      8
        { "_nswapmap" },
#define X_DMMIN         9
        { "_dmmin" },
#define X_DMMAX         10
        { "_dmmax" },
#define X_NSWDEV        11
        { "_nswdev" },
I 2
#define	X_SWDEVT	12
	{ "_swdevt" },
I 3
#define	X_NTEXT		13
	{ "_ntext" },
#define	X_TEXT		14
	{ "_text" },
#define	X_DMTEXT	15
	{ "_dmtext" },
#define	X_MBSTAT	16
	{ "_mbstat" },
E 4
E 3
E 2
D 13
        { "" }
E 13
I 13
	{ "" }
E 13
};
D 23

E 23
I 23
D 24
n
E 24
E 23
D 19
int     kmem = -1;
int     mem = -1;
int     swap = -1;
E 19
I 2
D 20
int	naptime = 5;
E 20
I 20
static int     dellave;
E 20
E 2

D 18
int     die();
int     display();
int     suspend();
I 11
D 16
int	(*sigtstpdfl)();
E 16
I 16
sig_t	sigtstpdfl;
E 18
I 18
D 20
void	die(), display(), suspend();
E 18
E 16
E 11

E 20
I 20
kvm_t *kd;
E 20
I 18
sig_t	sigtstpdfl;
E 18
I 7
D 8
double	lave, ccpu;
E 8
I 8
D 14
double	ccpu;
E 14
I 14
D 15
fixpt_t	ccpu;
E 15
E 14
E 8
D 20
int     dellave;
E 20
I 20
double avenrun[3];
int     col;
int	naptime = 5;
int     verbose = 1;                    /* to report kvm read errs */
int     hz, stathz;
char    c;
char    *namp;
char    hostname[MAXHOSTNAMELEN];
WINDOW  *wnd;
int     CMDLINE;
E 20

E 7
I 5
static	WINDOW *wload;			/* one line window for load average */

I 19
D 20
int     verbose = 1;                    /* to report kvm read errs */

E 20
I 20
void
E 20
E 19
E 5
D 3
int     showpigs(), openpigs(), fetchpigs(), labelpigs();
int     showswap(), fetchswap(), labelswap();
int     showuser(), openuser(), fetchuser(), labeluser();
int     shownet(), opennet(), fetchnet(), labelnet();
E 3
I 3
D 4
int     showpigs(), openpigs(), fetchpigs(), labelpigs(), initpigs();
int     showswap(), fetchswap(), labelswap(), initswap();
int	showmbufs(), fetchmbufs(), labelmbufs(), initmbufs();
#ifdef notdef
int     showuser(), openuser(), fetchuser(), labeluser(), inituser();
int     shownet(), opennet(), fetchnet(), labelnet(), initnet();
#endif
E 3

struct  cmdtab {
        char    *c_name;
        int     (*c_refresh)();
        int     (*c_open)();
        int     (*c_fetch)();
        int     (*c_label)();
I 3
	int	(*c_init)();
	char	c_flags;
E 3
} cmdtab[] = {
        { "pigs",       showpigs,       openpigs,       fetchpigs,
D 3
          labelpigs },
E 3
I 3
          labelpigs,	initpigs },
E 3
        { "swap",       showswap,       openpigs,       fetchswap,
D 3
          labelswap },
E 3
I 3
          labelswap,	initswap },
        { "mbufs",	showmbufs,	openpigs,       fetchmbufs,
          labelmbufs,	initmbufs },
E 3
#ifdef notdef
        { "user",       showuser,       openuser,       fetchuser,
D 3
          labeluser },
E 3
I 3
          labeluser,	inituser },
E 3
        { "net",        shownet,        opennet,        fetchnet,
D 3
          labelnet },
E 3
I 3
          labelnet,	initnet },
E 3
#endif
        { "" }
};
struct  cmdtab *curcmd = &cmdtab[0];

E 4
main(argc, argv)
D 13
        int argc;
        char **argv;
E 13
I 13
	int argc;
	char **argv;
E 13
{
I 20
	char errbuf[80];
E 20
I 15
D 19
	fixpt_t	ccpu;
E 19
E 15
D 4
        char ch, line[80];
E 4

I 2
	argc--, argv++;
	while (argc > 0) {
		if (argv[0][0] == '-') {
			struct cmdtab *p;

D 6
			for (p = cmdtab; *p->c_name; p++)
				if (strcmp(p->c_name, &argv[0][1]) == 0)
					break;
			if (*p->c_name == 0) {
E 6
I 6
			p = lookup(&argv[0][1]);
			if (p == (struct cmdtab *)-1) {
E 6
				fprintf(stderr, "%s: unknown request\n",
				    &argv[0][1]);
				exit(1);
			}
			curcmd = p;
		} else {
D 12
			naptime = atoi(argv[1]);
			if (naptime < 5)
E 12
I 12
			naptime = atoi(argv[0]);
			if (naptime <= 0)
E 12
				naptime = 5;
		}
		argc--, argv++;
	}
E 2
D 13
        nlist("/vmunix", nlst);
E 13
I 13
D 19
	nlist(_PATH_UNIX, nlst);
E 13
D 4
        (*curcmd->c_open)();
E 4
I 4
	if (nlst[X_CCPU].n_type == 0) {
D 13
		fprintf(stderr, "Couldn't namelist /vmunix.\n");
E 13
I 13
		fprintf(stderr, "Couldn't namelist %s.\n", _PATH_UNIX);
E 19
I 19
D 20
	kvm_nlist(nlst);
E 20
I 20
	kd = kvm_openfiles(NULL, NULL, NULL, O_RDONLY, errbuf);
	if (kd == NULL) {
		error("%s", errbuf);
		exit(1);
	}
D 21
	if (kvm_nlist(kd, nlst)) {
		nlisterr(nlst);
E 21
I 21
D 22
	if (kvm_nlist(kd, nl)) {
		nlisterr(nl);
E 22
I 22
	if (kvm_nlist(kd, namelist)) {
		nlisterr(namelist);
E 22
E 21
		exit(1);
	}
E 20
D 21
	if (nlst[X_FIRST].n_type == 0) {
E 21
I 21
D 22
	if (nl[X_FIRST].n_type == 0) {
E 21
		fprintf(stderr, "Couldn't namelist.\n");
E 22
I 22
	if (namelist[X_FIRST].n_type == 0) {
		fprintf(stderr, "couldn't read namelist.\n");
E 22
E 19
E 13
		exit(1);
	}
D 13
	kmemf = "/dev/kmem";
E 13
I 13
D 19
	kmemf = _PATH_KMEM;
E 13
	kmem = open(kmemf, O_RDONLY);
	if (kmem < 0) {
		perror(kmemf);
		exit(1);
	}
D 13
	memf = "/dev/mem";
E 13
I 13
	memf = _PATH_MEM;
E 13
	mem = open(memf, O_RDONLY);
	if (mem < 0) {
		perror(memf);
		exit(1);
	}
D 13
	swapf = "/dev/drum";
E 13
I 13
	swapf = _PATH_DRUM;
E 13
	swap = open(swapf, O_RDONLY);
	if (swap < 0) {
		perror(swapf);
		exit(1);
	}
E 19
E 4
D 2
        naptime = 5;
        if (argc != 1)
                naptime = atoi(argv[1]);
        if (naptime < 5)
                naptime = 5;
E 2
D 13
        signal(SIGINT, die);
        signal(SIGQUIT, die);
        signal(SIGTERM, die);
E 13
I 13
	signal(SIGINT, die);
	signal(SIGQUIT, die);
	signal(SIGTERM, die);
E 13

D 4
        /* Initialize curses. */
E 4
I 4
D 13
        /*
E 13
I 13
	/*
E 13
D 5
	 * Initialize display.  Load average appears in standard
	 * window with current display's overlapping sub-window
	 * maintained by the display routines to minimize update
	 * work by curses.
E 5
I 5
	 * Initialize display.  Load average appears in a one line
	 * window of its own.  Current command's display appears in
	 * an overlapping sub-window of stdscr configured by the display
	 * routines to minimize update work by curses.
E 5
	 */
E 4
D 13
        initscr();
E 13
I 13
	initscr();
E 13
I 7
	CMDLINE = LINES - 1;
E 7
D 4
        wnd = newwin(20, 70, 3, 5);
E 4
I 4
	wnd = (*curcmd->c_open)();
	if (wnd == NULL) {
		fprintf(stderr, "Couldn't initialize display.\n");
D 20
		die();
E 20
I 20
		die(0);
E 20
	}
I 5
	wload = newwin(1, 0, 3, 20);
	if (wload == NULL) {
		fprintf(stderr, "Couldn't set up load average window.\n");
D 20
		die();
E 20
I 20
		die(0);
E 20
	}
E 5
E 4
D 19

E 19
I 2
D 6
#ifdef notdef
E 6
D 13
        gethostname(hostname, sizeof (hostname));
D 6
#endif
E 6
E 2
D 8
        lseek(kmem, nlst[X_CCPU].n_value, 0);
E 8
I 8
        lseek(kmem, nlst[X_CCPU].n_value, L_SET);
E 8
        read(kmem, &ccpu, sizeof (ccpu));
        lccpu = log(ccpu);
E 13
I 13
	gethostname(hostname, sizeof (hostname));
D 14
	lseek(kmem, nlst[X_CCPU].n_value, L_SET);
	read(kmem, &ccpu, sizeof (ccpu));
	lccpu = log(ccpu);
E 14
I 14
D 17
	ccpu = getw(nlst[X_CCPU].n_value);
	fscale = getw(nlst[X_FSCALE].n_value);
E 17
I 17
D 19
	ccpu = getword(nlst[X_CCPU].n_value);
	fscale = getword(nlst[X_FSCALE].n_value);
E 17
	lccpu = log((double) ccpu / fscale);
E 14
E 13
I 8
D 9
	lseek(kmem, nlst[X_DK_MSPW].n_value, L_SET);
	read(kmem, dk_mspw, sizeof (dk_mspw));
	lseek(kmem, nlst[X_HZ].n_value, L_SET);
	read(kmem, &hz, sizeof (hz));
	lseek(kmem, nlst[X_PHZ].n_value, L_SET);
	read(kmem, &phz, sizeof (phz));
E 9
I 9
D 17
	hz = getw(nlst[X_HZ].n_value);
	phz = getw(nlst[X_PHZ].n_value);
E 17
I 17
	hz = getword(nlst[X_HZ].n_value);
	phz = getword(nlst[X_PHZ].n_value);
E 19
I 19
	NREAD(X_HZ, &hz, LONG);
D 20
	NREAD(X_PHZ, &phz, LONG);
E 20
I 20
	NREAD(X_STATHZ, &stathz, LONG);
E 20
E 19
E 17
E 9
E 8
I 4
	(*curcmd->c_init)();
D 8
	curcmd->c_flags = 1;
E 8
I 8
	curcmd->c_flags |= CF_INIT;
E 8
E 4
D 3
        (*curcmd->c_fetch)();
E 3
D 2
        gethostname(hostname, sizeof (hostname));
E 2
D 13
        labels();
E 13
I 13
	labels();
E 13

D 13
        known[0].k_uid = -1;
E 13
I 13
D 19
	known[0].k_uid = -1;
E 13
D 5
        strcpy(known[0].k_name, "<idle>");
E 5
I 5
	known[0].k_name[0] = '\0';
E 5
D 13
        numknown = 1;
E 13
I 13
	numknown = 1;
E 13
I 5
	procs[0].pid = -1;
	strcpy(procs[0].cmd, "<idle>");
	numprocs = 1;
E 19
E 5
D 13
        dellave = 0.0;
E 13
I 13
	dellave = 0.0;
E 13

D 13
        signal(SIGALRM, display);
D 11
        signal(SIGTSTP, suspend);
E 11
I 11
        sigtstpdfl = signal(SIGTSTP, suspend);
E 11
        display();
        noecho();
        crmode();
E 13
I 13
	signal(SIGALRM, display);
D 24
	sigtstpdfl = signal(SIGTSTP, suspend);
E 24
D 20
	display();
E 20
I 20
	display(0);
E 20
	noecho();
	crmode();
E 13
D 4
        for (;;) {
                col = 0;
                move(22, 0);
                do {
                        refresh();
                        ch = getch() & 0177;
                        if (ch == 0177 && ferror(stdin)) {
                                clearerr(stdin);
                                continue;
                        }
                        if (ch >= 'A' && ch <= 'Z')
                                ch += 'a' - 'A';
                        if (col == 0) {
I 3
#define	mask(s)	(1 << ((s) - 1))
E 3
                                if (ch == CTRL(l)) {
D 3
                                        wrefresh(curscr);
E 3
I 3
					int oldmask = sigblock(mask(SIGALRM));

					wrefresh(curscr);
					sigsetmask(oldmask);
E 3
                                        continue;
                                }
                                if (ch != ':')
                                        continue;
                                move(22, 0);
                                clrtoeol();
                        }
                        if (ch == _tty.sg_erase && col > 0) {
                                if (col == 1 && line[0] == ':')
                                        continue;
                                col--;
                                goto doerase;
                        }
                        if (ch == CTRL(w) && col > 0) {
                                while (--col >= 0 && isspace(line[col]))
                                        ;
                                col++;
                                while (--col >= 0 && !isspace(line[col]))
                                        if (col == 0 && line[0] == ':')
                                                break;
                                col++;
                                goto doerase;
                        }
                        if (ch == _tty.sg_kill && col > 0) {
                                col = 0;
                                if (line[0] == ':')
                                        col++;
                doerase:
                                move(22, col);
                                clrtoeol();
                                continue;
                        }
                        if (isprint(ch)) {
                                line[col] = ch;
                                mvaddch(22, col, ch);
                                col++;
                        }
                } while (col == 0 || (ch != '\r' && ch != '\n'));
                line[col] = '\0';
                command(line + 1);
        }
}
E 4
I 4
	keyboard();
	/*NOTREACHED*/
}
E 4

I 20
void
E 20
D 4
command(cmd)
        char *cmd;
{
        register char *cp;
        register struct cmdtab *p;
        char *arg;

        for (cp = cmd; *cp && !isspace(*cp); cp++)
                ;
        if (*cp)
                *cp++ = '\0';
        if (strcmp(cmd, "quit") == 0)
                die();
        if (strcmp(cmd, "status") == 0 || strcmp(cmd, "help") == 0) {
                status();
                return;
        }
I 2
	if (strcmp(cmd, "load") == 0) {
		lseek(kmem, nlst[X_AVENRUN].n_value, L_SET);
		read(kmem, &lave, sizeof (lave));
		mvprintw(22, 0, "%4.1f", lave);
		clrtoeol();
		return;
	}
E 2
        for (p = cmdtab; *p->c_name; p++)
                if (strcmp(cmd, p->c_name) == 0)
                        break;
        if (*p->c_name) {
                if (curcmd == p)
                        return;
                alarm(0);
                curcmd = p;
D 2
                wclear(wnd);
                (*p->c_label)();
E 2
I 2
		clear(); wclear(wnd);
		labels();
E 2
                display();
                status();
                return;
        }
        if (strcmp(cmd, "stop") == 0) {
                alarm(0);
                mvaddstr(22, 0, "Refresh disabled.");
                clrtoeol();
                return;
        }
        /* commands with arguments */
        for (; *cp && isspace(*cp); cp++)
                ;
        if (strcmp(cmd, "start") == 0) {
                int x;

                if (*cp == '\0')
                        x = naptime;
                else
                        x = atoi(cp);
                if (x <= 0) {
                        mvprintw(22, 0, "%d: bad interval.", x);
                        clrtoeol();
                        return;
                }
                alarm(0);
                naptime = x;
                display();
                status();
                return;
        }
D 2
        mvprintw(22, 0, "%s: Unknown command.", cmd);
        clrtoeol();
E 2
I 2
	if (*cmd) {
		mvprintw(22, 0, "%s: Unknown command.", cmd);
		clrtoeol();
	}
E 2
}

status()
{

        mvprintw(22, 0, "Showing %s, refresh every %d seconds.",
          curcmd->c_name, naptime);
        clrtoeol();
}

suspend()
{
        int oldmask;

I 2
	alarm(0);
E 2
        move(22, 0);
        refresh();
        echo();
        nocrmode();
        signal(SIGTSTP, SIG_DFL);
        oldmask = sigsetmask(0);
        kill(getpid(), SIGTSTP);
        sigsetmask(oldmask);
        signal(SIGTSTP, suspend);
        crmode();
        noecho();
        move(22, col);
        wrefresh(curscr);
I 2
	alarm(naptime);
E 2
}

E 4
labels()
{
D 13

E 13
D 8
        mvaddstr(2, 20,
                "/0   /1   /2   /3   /4   /5   /6   /7   /8   /9   /10");
D 5
        mvwaddstr(wnd, 0, 0, "Load Average");
E 5
I 5
        mvaddstr(3, 5, "Load Average");
E 8
I 8
	if (curcmd->c_flags & CF_LOADAV) {
		mvaddstr(2, 20,
		    "/0   /1   /2   /3   /4   /5   /6   /7   /8   /9   /10");
		mvaddstr(3, 5, "Load Average");
	}
E 8
E 5
D 13
        (*curcmd->c_label)();
E 13
I 13
	(*curcmd->c_label)();
E 13
#ifdef notdef
D 13
        mvprintw(21, 25, "CPU usage on %s", hostname);
E 13
I 13
	mvprintw(21, 25, "CPU usage on %s", hostname);
E 13
#endif
D 13
        refresh();
E 13
I 13
	refresh();
E 13
}

I 18
void
E 18
D 20
display()
E 20
I 20
display(signo)
	int signo;
E 20
{
D 13
        register int i, j;
E 13
I 13
	register int i, j;
E 13

D 13
        /* Get the load average over the last minute. */
        lseek(kmem, nlst[X_AVENRUN].n_value, L_SET);
E 13
I 13
	/* Get the load average over the last minute. */
D 14
	lseek(kmem, nlst[X_AVENRUN].n_value, L_SET);
E 13
D 8
        read(kmem, &lave, sizeof (lave));
E 8
I 8
	read(kmem, avenrun, sizeof (avenrun));
E 14
I 14
	(void) getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0]));
E 14
E 8
I 3
D 4
	if (curcmd->c_flags == 0) {
		(*curcmd->c_init)();
		curcmd->c_flags = 1;
	}
E 4
E 3
D 13
        (*curcmd->c_fetch)();
E 13
I 13
	(*curcmd->c_fetch)();
E 13
D 8
        j = 5.0*lave + 0.5;
        dellave -= lave;
        if (dellave >= 0.0)
                c = '<';
        else {
                c = '>';
                dellave = -dellave;
        }
        if (dellave < 0.1)
                c = '|';
        dellave = lave;
D 5
        wmove(wnd, 0, 15);
        wclrtoeol(wnd);
        for (i = (j > 50)? 50 : j; i > 0; i--)
                waddch(wnd, c);
E 5
I 5
        wmove(wload, 0, 0); wclrtoeol(wload);
        for (i = (j > 50) ? 50 : j; i > 0; i--)
                waddch(wload, c);
E 5
        if (j > 50)
D 5
                wprintw(wnd, " %4.1f", lave);
E 5
I 5
                wprintw(wload, " %4.1f", lave);
E 8
I 8
	if (curcmd->c_flags & CF_LOADAV) {
		j = 5.0*avenrun[0] + 0.5;
		dellave -= avenrun[0];
		if (dellave >= 0.0)
			c = '<';
		else {
			c = '>';
			dellave = -dellave;
		}
		if (dellave < 0.1)
			c = '|';
		dellave = avenrun[0];
		wmove(wload, 0, 0); wclrtoeol(wload);
		for (i = (j > 50) ? 50 : j; i > 0; i--)
			waddch(wload, c);
		if (j > 50)
			wprintw(wload, " %4.1f", avenrun[0]);
	}
E 8
E 5
D 13
        (*curcmd->c_refresh)();
E 13
I 13
	(*curcmd->c_refresh)();
E 13
I 5
D 8
	wrefresh(wload);
E 8
I 8
	if (curcmd->c_flags & CF_LOADAV)
		wrefresh(wload);
E 8
E 5
D 13
        wrefresh(wnd);
D 7
        move(22, col);
E 7
I 7
        move(CMDLINE, col);
E 7
        refresh();
        alarm(naptime);
E 13
I 13
	wrefresh(wnd);
	move(CMDLINE, col);
	refresh();
	alarm(naptime);
E 13
I 4
}

I 20
void
E 20
load()
{
I 7
D 19
	double	avenrun[3];
E 19
E 7

D 14
	lseek(kmem, nlst[X_AVENRUN].n_value, L_SET);
D 7
	read(kmem, &lave, sizeof (lave));
	mvprintw(22, 0, "%4.1f", lave);
E 7
I 7
	read(kmem, avenrun, sizeof (avenrun));
E 14
I 14
	(void) getloadavg(avenrun, sizeof(avenrun)/sizeof(avenrun[0]));
E 14
	mvprintw(CMDLINE, 0, "%4.1f %4.1f %4.1f",
	    avenrun[0], avenrun[1], avenrun[2]);
E 7
	clrtoeol();
E 4
}

I 18
void
E 18
D 20
die()
E 20
I 20
die(signo)
	int signo;
E 20
{
I 16
	move(CMDLINE, 0);
	clrtoeol();
	refresh();
E 16
D 13

        endwin();
        exit(0);
E 13
I 13
	endwin();
	exit(0);
E 13
I 3
}

D 17
error(fmt, a1, a2, a3)
E 17
I 17
D 20
error(va_alist)
E 20
I 20
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#if __STDC__
void
error(const char *fmt, ...)
#else
void
error(fmt, va_alist)
	char *fmt;
E 20
	va_dcl
I 20
#endif
E 20
E 17
{
D 13

E 13
D 7
	mvprintw(22, 0, fmt, a1, a2, a3);
E 7
I 7
D 17
	mvprintw(CMDLINE, 0, fmt, a1, a2, a3);
E 17
I 17
	va_list ap;
I 23
	char buf[255];
	int oy, ox;
E 23
D 20
	char *fmt, msg[200];

E 20
I 20
#if __STDC__
	va_start(ap, fmt);
#else
E 20
	va_start(ap);
D 20
	fmt = va_arg(ap, char *);
	(void) vsnprintf(msg, sizeof msg, fmt, ap);
E 20
I 20
#endif
D 23
	(void) vfprintf(stderr, fmt, ap);
E 20
	va_end(ap);
E 23
I 23

E 23
D 20
	mvaddstr(CMDLINE, 0, msg);
E 20
I 20
	if (wnd) {
I 23
		getyx(stdscr, oy, ox);
		(void) vsprintf(buf, fmt, ap);
E 23
		clrtoeol();
I 23
		standout();
		mvaddstr(CMDLINE, 0, buf);
		standend();
		move(oy, ox);
E 23
		refresh();
D 23
	} else
E 23
I 23
	} else {
		(void) vfprintf(stderr, fmt, ap);
E 23
		fprintf(stderr, "\n");
I 23
	}
	va_end(ap);
E 23
}

void
D 22
nlisterr(nl)
	struct nlist nl[];
E 22
I 22
nlisterr(namelist)
	struct nlist namelist[];
E 22
{
	int i, n;

	n = 0;
	clear();
	mvprintw(2, 10, "systat: nlist: can't find following symbols:");
D 22
	for (i = 0; nl[i].n_name != NULL && *nl[i].n_name != '\0'; i++)
		if (nl[i].n_value == 0)
			mvprintw(2 + ++n, 10, "%s", nl[i].n_name);
E 22
I 22
	for (i = 0;
	    namelist[i].n_name != NULL && *namelist[i].n_name != '\0'; i++)
		if (namelist[i].n_value == 0)
			mvprintw(2 + ++n, 10, "%s", namelist[i].n_name);
E 22
	move(CMDLINE, 0);
E 20
E 17
E 7
	clrtoeol();
	refresh();
I 20
	endwin();
	exit(1);
E 20
E 3
}
E 1
