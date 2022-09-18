h09631
s 00004/00003/00502
d D 8.4 95/05/04 15:27:57 bostic 4 3
c optarg/optind moved to unistd.h
e
s 00104/00059/00401
d D 8.3 95/05/03 19:33:23 mckusick 3 2
c update from Ralph
e
s 00019/00003/00441
d D 8.2 94/08/04 17:33:17 mckusick 2 1
c fixes from Ralph
e
s 00444/00000/00000
d D 8.1 94/07/24 22:58:10 mckusick 1 0
c from Ralph Campbell
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
 * Ralph Campbell.
 *
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

I 4
#include <curses.h>
#include <err.h>
#include <signal.h>
E 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
D 4
#include <signal.h>
#include <curses.h>
#include <err.h>
E 4
I 4
#include <unistd.h>
E 4

#include "gomoku.h"

#define USER	0		/* get input from standard input */
#define PROGRAM	1		/* get input from program */
#define INPUTF	2		/* get input from a file */

int	interactive = 1;	/* true if interactive */
int	debug;			/* true if debugging */
int	test;			/* both moves come from 1: input, 2: computer */
char	*prog;			/* name of program */
FILE	*debugfp;		/* file for debug output */
FILE	*inputfp;		/* file for debug input */

D 3
char	*color[]	= { "black", "white", "empty", "border" };
E 3
char	pdir[4]		= "-\\|/";
char	fmtbuf[128];

struct	spotstr	board[BAREA];		/* info for board */
struct	combostr frames[FAREA];		/* storage for all frames */
struct	combostr *sortframes[2];	/* sorted list of non-empty frames */
D 3
char	overlap[FAREA * FAREA];		/* true if frame [a][b] overlap */
E 3
I 3
u_char	overlap[FAREA * FAREA];		/* true if frame [a][b] overlap */
E 3
short	intersect[FAREA * FAREA];	/* frame [a][b] intersection */
int	movelog[BSZ * BSZ];		/* log of all the moves */
int	movenum;			/* current move number */
char	*plyr[2];			/* who's who */

I 3
extern void quit();
#ifdef DEBUG
extern void whatsup();
#endif

E 3
main(argc, argv)
	int argc;
	char **argv;
{
	char buf[128];
	int color, curmove, i, ch;
	int input[2];
D 3
	extern void whatsup(), quit();
E 3
	static char *fmt[2] = {
		"%3d %-6s",
		"%3d        %-6s"
	};

	prog = strrchr(argv[0], '/');
	if (prog)
		prog++;
	else
		prog = argv[0];

	while ((ch = getopt(argc, argv, "bcdD:u")) != EOF) {
		switch (ch) {
		case 'b':	/* background */
			interactive = 0;
			break;
		case 'd':	/* debugging */
			debug++;
			break;
		case 'D':	/* log debug output to file */
			if ((debugfp = fopen(optarg, "w")) == NULL)
				err(1, "%s", optarg);
			break;
		case 'u':	/* testing: user verses user */
			test = 1;
			break;
		case 'c':	/* testing: computer verses computer */
			test = 2;
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc) {
		if ((inputfp = fopen(*argv, "r")) == NULL)
			err(1, "%s", *argv);
D 3
		test = 3;
E 3
	}

	if (!debug)
#ifdef SVR4
D 2
		srandom(time(0));
#else
E 2
		srand(time(0));
I 2
#else
		srandom(time(0));
E 2
#endif
	if (interactive)
		cursinit();		/* initialize curses */
again:
	bdinit(board);			/* initialize board contents */

	if (interactive) {
		plyr[BLACK] = plyr[WHITE] = "???";
		bdisp_init();		/* initialize display of board */
#ifdef DEBUG
		signal(SIGINT, whatsup);
#else
		signal(SIGINT, quit);
#endif

D 2
		if (test != 3) {
E 2
I 2
D 3
		if (test == 0) {
E 3
I 3
		if (inputfp == NULL && test == 0) {
E 3
E 2
			for (;;) {
				ask("black or white? ");
D 3
				getline(buf, sizeof buf);
E 3
I 3
				getline(buf, sizeof(buf));
E 3
				if (buf[0] == 'b' || buf[0] == 'B') {
					color = BLACK;
					break;
				}
				if (buf[0] == 'w' || buf[0] == 'W') {
					color = WHITE;
					break;
				}
				move(22, 0);
				printw("Black moves first. Please enter `black' or `white'\n");
			}
			move(22, 0);
			clrtoeol();
		}
	} else {
		setbuf(stdout, 0);
D 3
		getline(buf, sizeof buf);
E 3
I 3
		getline(buf, sizeof(buf));
E 3
		if (strcmp(buf, "black") == 0)
			color = BLACK;
		else if (strcmp(buf, "white") == 0)
			color = WHITE;
		else {
			sprintf(fmtbuf,
			    "Huh?  Expected `black' or `white', got `%s'\n",
			    buf);
			panic(fmtbuf);
		}
	}

D 3
	switch (test) {
	case 0: /* user verses program */
		input[color] = USER;
		input[!color] = PROGRAM;
		break;

	case 1: /* user verses user */
		input[BLACK] = USER;
		input[WHITE] = USER;
		break;

	case 2: /* program verses program */
		input[BLACK] = PROGRAM;
		input[WHITE] = PROGRAM;
		break;

	case 3: /* user verses program */
E 3
I 3
	if (inputfp) {
E 3
		input[BLACK] = INPUTF;
		input[WHITE] = INPUTF;
I 3
	} else {
		switch (test) {
		case 0: /* user verses program */
			input[color] = USER;
			input[!color] = PROGRAM;
			break;

		case 1: /* user verses user */
			input[BLACK] = USER;
			input[WHITE] = USER;
			break;

		case 2: /* program verses program */
			input[BLACK] = PROGRAM;
			input[WHITE] = PROGRAM;
			break;
		}
E 3
	}
	if (interactive) {
		plyr[BLACK] = input[BLACK] == USER ? "you" : prog;
		plyr[WHITE] = input[WHITE] == USER ? "you" : prog;
		bdwho(1);
	}

	for (color = BLACK; ; color = !color) {
I 3
	top:
E 3
		switch (input[color]) {
		case INPUTF: /* input comes from a file */
			curmove = readinput(inputfp);
			if (curmove != ILLEGAL)
				break;
D 3
			input[color] = USER;
			input[!color] = PROGRAM;
			plyr[color] = "you";
E 3
I 3
			switch (test) {
			case 0: /* user verses program */
				input[color] = USER;
				input[!color] = PROGRAM;
				break;

			case 1: /* user verses user */
				input[BLACK] = USER;
				input[WHITE] = USER;
				break;

			case 2: /* program verses program */
				input[BLACK] = PROGRAM;
				input[WHITE] = PROGRAM;
				break;
			}
			plyr[BLACK] = input[BLACK] == USER ? "you" : prog;
			plyr[WHITE] = input[WHITE] == USER ? "you" : prog;
E 3
			bdwho(1);
D 3
			/* FALLTHROUGH */
E 3
I 3
			goto top;
E 3

		case USER: /* input comes from standard input */
		getinput:
			if (interactive)
				ask("move? ");
D 3
			if (!getline(buf, sizeof buf)) {
E 3
I 3
			if (!getline(buf, sizeof(buf))) {
E 3
				curmove = RESIGN;
				break;
			}
			if (buf[0] == '\0')
				goto getinput;
			curmove = ctos(buf);
			if (interactive) {
				if (curmove == SAVE) {
					FILE *fp;

					ask("save file name? ");
D 3
					(void)getline(buf, sizeof buf);
E 3
I 3
					(void)getline(buf, sizeof(buf));
E 3
					if ((fp = fopen(buf, "w")) == NULL) {
						log("cannot create save file");
						goto getinput;
					}
					for (i = 0; i < movenum - 1; i++)
						fprintf(fp, "%s\n",
							stoc(movelog[i]));
					fclose(fp);
					goto getinput;
				}
				if (curmove != RESIGN &&
				    board[curmove].s_occ != EMPTY) {
					log("Illegal move");
					goto getinput;
				}
			}
			break;

		case PROGRAM: /* input comes from the program */
			curmove = pickmove(color);
			break;
		}
		if (interactive) {
			sprintf(fmtbuf, fmt[color], movenum, stoc(curmove));
			log(fmtbuf);
		}
		if ((i = makemove(color, curmove)) != MOVEOK)
			break;
		if (interactive)
			bdisp();
	}
	if (interactive) {
		move(22, 0);
		switch (i) {
		case WIN:
			if (input[color] == PROGRAM)
				addstr("Ha ha, I won");
			else
				addstr("Rats! you won");
			break;
		case TIE:
			addstr("Wow! its a tie");
			break;
		case ILLEGAL:
			addstr("Illegal move");
			break;
		}
		clrtoeol();
		bdisp();
		if (i != RESIGN) {
I 2
		replay:
E 2
			ask("replay? ");
D 3
			if (getline(buf, sizeof buf) &&
E 3
I 3
			if (getline(buf, sizeof(buf)) &&
E 3
			    buf[0] == 'y' || buf[0] == 'Y')
				goto again;
I 2
			if (strcmp(buf, "save") == 0) {
				FILE *fp;

				ask("save file name? ");
D 3
				(void)getline(buf, sizeof buf);
E 3
I 3
				(void)getline(buf, sizeof(buf));
E 3
				if ((fp = fopen(buf, "w")) == NULL) {
					log("cannot create save file");
					goto replay;
				}
				for (i = 0; i < movenum - 1; i++)
					fprintf(fp, "%s\n",
						stoc(movelog[i]));
				fclose(fp);
				goto replay;
			}
E 2
		}
	}
	quit();
}

readinput(fp)
	FILE *fp;
{
	char *cp;
	int c;

	cp = fmtbuf;
	while ((c = getc(fp)) != EOF && c != '\n')
		*cp++ = c;
	*cp = '\0';
	return (ctos(fmtbuf));
}

#ifdef DEBUG
/*
 * Handle strange situations.
 */
void
whatsup(signum)
	int signum;
{
D 3
	int i, pnum, n;
E 3
I 3
	int i, pnum, n, s1, s2, d1, d2;
E 3
	struct spotstr *sp;
	FILE *fp;
	char *str;
	struct elist *ep;
	struct combostr *cbp;

	if (!interactive)
		quit();
top:
	ask("cmd? ");
D 3
	if (!getline(fmtbuf, 128))
E 3
I 3
	if (!getline(fmtbuf, sizeof(fmtbuf)))
E 3
		quit();
	switch (*fmtbuf) {
I 3
	case '\0':
		goto top;
E 3
	case 'q':		/* conservative quit */
		quit();
	case 'd':		/* set debug level */
		debug = fmtbuf[1] - '0';
		sprintf(fmtbuf, "Debug set to %d", debug);
		dlog(fmtbuf);
		sleep(1);
	case 'c':
		break;
	case 'b':		/* back up a move */
		if (movenum > 1) {
			movenum--;
			board[movelog[movenum - 1]].s_occ = EMPTY;
			bdisp();
		}
		goto top;
I 3
	case 's':		/* suggest a move */
		i = fmtbuf[1] == 'b' ? BLACK : WHITE;
		sprintf(fmtbuf, "suggest %c %s", i == BLACK ? 'B' : 'W',
			stoc(pickmove(i)));
		dlog(fmtbuf);
		goto top;
E 3
	case 'f':		/* go forward a move */
		board[movelog[movenum - 1]].s_occ = movenum & 1 ? BLACK : WHITE;
		movenum++;
		bdisp();
		goto top;
	case 'l':		/* print move history */
		if (fmtbuf[1] == '\0') {
			for (i = 0; i < movenum - 1; i++)
				dlog(stoc(movelog[i]));
			goto top;
		}
		if ((fp = fopen(fmtbuf + 1, "w")) == NULL)
			goto top;
		for (i = 0; i < movenum - 1; i++) {
			fprintf(fp, "%s", stoc(movelog[i]));
			if (++i < movenum - 1)
				fprintf(fp, " %s\n", stoc(movelog[i]));
			else
				fputc('\n', fp);
		}
		bdump(fp);
		fclose(fp);
		goto top;
I 3
	case 'o':
		n = 0;
		for (str = fmtbuf + 1; *str; str++)
			if (*str == ',') {
				for (d1 = 0; d1 < 4; d1++)
					if (str[-1] == pdir[d1])
						break;
				str[-1] = '\0';
				sp = &board[s1 = ctos(fmtbuf + 1)];
				n = (sp->s_frame[d1] - frames) * FAREA;
				*str++ = '\0';
				break;
			}
		sp = &board[s2 = ctos(str)];
		while (*str)
			str++;
		for (d2 = 0; d2 < 4; d2++)
			if (str[-1] == pdir[d2])
				break;
		n += sp->s_frame[d2] - frames;
		str = fmtbuf;
		sprintf(str, "overlap %s%c,", stoc(s1), pdir[d1]);
		str += strlen(str);
		sprintf(str, "%s%c = %x", stoc(s2), pdir[d2], overlap[n]);
		dlog(fmtbuf);
		goto top;
E 3
	case 'p':
		sp = &board[i = ctos(fmtbuf + 1)];
		sprintf(fmtbuf, "V %s %x/%d %d %x/%d %d %d %x", stoc(i),
			sp->s_combo[BLACK].s, sp->s_level[BLACK],
			sp->s_nforce[BLACK],
			sp->s_combo[WHITE].s, sp->s_level[WHITE],
			sp->s_nforce[WHITE], sp->s_wval, sp->s_flg);
		dlog(fmtbuf);
		sprintf(fmtbuf, "FB %s %x %x %x %x", stoc(i),
			sp->s_fval[BLACK][0].s, sp->s_fval[BLACK][1].s,
			sp->s_fval[BLACK][2].s, sp->s_fval[BLACK][3].s);
		dlog(fmtbuf);
		sprintf(fmtbuf, "FW %s %x %x %x %x", stoc(i),
			sp->s_fval[WHITE][0].s, sp->s_fval[WHITE][1].s,
			sp->s_fval[WHITE][2].s, sp->s_fval[WHITE][3].s);
		dlog(fmtbuf);
		goto top;
D 3
	case 'P':
		sp = &board[i = ctos(fmtbuf + 1)];
		for (pnum = BLACK; pnum <= WHITE; pnum++) {
			for (ep = sp->s_empty[pnum]; ep; ep = ep->e_next) {
				cbp = ep->e_combo;
				str = fmtbuf;
				sprintf(str, "C%c %s", "BW"[pnum], stoc(i));
				str += strlen(str);
				if (cbp->c_nframes == 2) {
					sprintf(str, " %s%c",
						stoc(cbp->c_link[0]->c_vertex),
						pdir[cbp->c_link[0]->c_dir]);
					str += strlen(str);
					sprintf(str, " %s%c %x/%d",
						stoc(cbp->c_link[1]->c_vertex),
						pdir[cbp->c_link[1]->c_dir],
						cbp->c_combo.s, cbp->c_nframes);
				} else {
					sprintf(str, " %s%c %x/%d",
						stoc(cbp->c_vertex),
						pdir[ep->e_frame->c_dir],
						cbp->c_combo.s, cbp->c_nframes);
				}
				dlog(fmtbuf);
E 3
I 3
	case 'e':	/* e {b|w} [0-9] spot */
		str = fmtbuf + 1;
		if (*str >= '0' && *str <= '9')
			n = *str++ - '0';
		else
			n = 0;
		sp = &board[i = ctos(str)];
		for (ep = sp->s_empty; ep; ep = ep->e_next) {
			cbp = ep->e_combo;
			if (n) {
				if (cbp->c_nframes > n)
					continue;
				if (cbp->c_nframes != n)
					break;
E 3
			}
I 3
			printcombo(cbp, fmtbuf);
			dlog(fmtbuf);
E 3
		}
		goto top;
	default:
syntax:
		dlog("Options are:");
		dlog("q    - quit");
		dlog("c    - continue");
		dlog("d#   - set debug level to #");
		dlog("p#   - print values at #");
		goto top;
	}
}
#endif /* DEBUG */

/*
 * Display debug info.
 */
dlog(str)
	char *str;
{

	if (debugfp)
		fprintf(debugfp, "%s\n", str);
D 3
	else if (interactive)
E 3
I 3
	if (interactive)
E 3
		dislog(str);
	else
		fprintf(stderr, "%s\n", str);
}

log(str)
	char *str;
{

	if (debugfp)
		fprintf(debugfp, "%s\n", str);
	if (interactive)
		dislog(str);
	else
		printf("%s\n", str);
}

void
quit()
{
	if (interactive) {
		bdisp();		/* show final board */
		cursfini();
	}
	exit(0);
}

/*
 * Die gracefully.
 */
panic(str)
	char *str;
{
	fprintf(stderr, "%s: %s\n", prog, str);
	fputs("resign\n", stdout);
	quit();
}
E 1
