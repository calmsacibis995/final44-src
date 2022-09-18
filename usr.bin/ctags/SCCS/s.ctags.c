h25216
s 00003/00003/00243
d D 8.4 95/02/07 04:49:36 pendry 17 16
c add missing \n to usage message
e
s 00002/00002/00244
d D 8.3 94/04/02 10:08:27 pendry 16 15
c add 1994 copyright
e
s 00088/00077/00158
d D 8.2 94/04/01 13:02:02 pendry 15 14
c prettyness police
e
s 00005/00005/00230
d D 8.1 93/06/06 14:29:41 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00232
d D 5.8 91/02/26 13:42:13 bostic 13 12
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00232
d D 5.7 90/06/01 15:58:14 bostic 12 11
c new copyright notice
c possibly distributed as revision 5.5.
e
s 00001/00001/00242
d D 5.6 90/05/15 19:51:05 bostic 11 10
c string.h is ANSI C include file
c possibly distributed as revision 5.4.
e
s 00017/00006/00226
d D 5.5 88/12/31 12:32:28 bostic 10 9
c original by Ken Arnold -- Berkeley copyright
c possibly distributed as revision 5.3.
e
s 00005/00001/00227
d D 5.4 87/03/16 18:15:43 bostic 9 8
c fixed line numbers for xflag
c possibly distributed as revision 5.2.
e
s 00064/00941/00164
d D 5.3 87/03/16 17:57:30 bostic 8 7
c break up into multiple files
c possibly distributed as revision 5.1.
e
s 00675/00599/00430
d D 5.2 88/10/22 16:45:27 bostic 7 6
c rework
e
s 00345/00091/00684
d D 5.1 85/05/31 09:09:54 bostic 6 5
c 4.3bsd version
e
s 00065/00015/00710
d D 4.7 83/08/18 17:47:15 bostic 5 4
c 4.2bsd version (dates out of order, but sccs id's in order)
e
s 00115/00061/00610
d D 4.4 83/09/03 05:46:54 bostic 4 3
c 2.9bsd version (dates out of order, but sccs id's in order)
e
s 00009/00002/00662
d D 4.3 80/11/24 20:12:17 bostic 3 2
c 4.1bsd version
e
s 00354/00305/00310
d D 4.2 80/10/09 03:23:43 bostic 2 1
c 4.0bsd version
e
s 00615/00000/00000
d D 4.1 79/12/04 15:58:14 bostic 1 0
c 3bsd version
e
u
U
t
T
I 1
D 2
#include	<stdio.h>
E 2
I 2
D 3
static char *sccsid = "@(#)ctags.c	4.2 (Berkeley) 10/3/80";
E 3
I 3
D 4
static char *sccsid = "@(#)ctags.c	4.3 (Berkeley) 11/24/80";
E 4
I 4
D 5
#ifndef	lint
static char *sccsid = "@(#)ctags.c	4.4 (Berkeley) 8/30/82";
#endif
E 5
I 5
D 6
static char *sccsid = "@(#)ctags.c	4.7 (Berkeley) 8/18/83";
E 6
I 6
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
E 8
I 8
D 10
 * Copyright (c) 1987 Regents of the University of California.
E 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
D 14
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
D 16
 * Copyright (c) 1987, 1993
E 16
I 16
D 17
 * Copyright (c) 1987, 1993, 1994
E 17
I 17
 * Copyright (c) 1987, 1993, 1994, 1995
E 17
E 16
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 12
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 10
 */
E 6
E 5

I 6
#ifndef lint
D 14
char copyright[] =
D 8
"@(#) Copyright (c) 1980 Regents of the University of California.\n\
E 8
I 8
D 10
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 10
I 10
"%Z% Copyright (c) 1987 The Regents of the University of California.\n\
E 10
E 8
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
D 16
"%Z% Copyright (c) 1987, 1993\n\
E 16
I 16
D 17
"%Z% Copyright (c) 1987, 1993, 1994\n\
E 17
I 17
"%Z% Copyright (c) 1987, 1993, 1994, 1995\n\
E 17
E 16
	The Regents of the University of California.  All rights reserved.\n";
E 14
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

#ifndef lint
D 7
static char sccsid[] = "@(#)ctags.c	5.1 (Berkeley) 5/31/85";
E 7
I 7
D 8
static char sccsid[] = "@(#)ctags.x	5.1 (Berkeley) 10/22/88";
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
E 8
E 7
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

I 15
#include <err.h>
#include <limits.h>
E 15
I 7
D 8
#include <sys/types.h>
#include <sys/file.h>
E 7
E 6
E 4
E 3
#include <stdio.h>
#include <ctype.h>
E 8
I 8
D 13
#include <ctags.h>
E 13
I 13
#include <stdio.h>
E 13
E 8
I 7
D 11
#include <strings.h>
E 11
I 11
#include <string.h>
I 13
#include <stdlib.h>
I 15
#include <unistd.h>

E 15
#include "ctags.h"
E 13
E 11
E 7
E 2

/*
D 2
 *	This program examines each of its arguments for C function
 * definitions, and puts them in a file "tags" for use by the editor
 * (and anyone else who wants to).
E 2
I 2
D 3
 * ctags
E 3
I 3
 * ctags: create a tags file
E 3
E 2
 */

D 2
/*
 *	program history:
 *	ken arnold wrote this program.  ask him.
 *	brought over to the vax by peter b. kessler 7/79
 *	who disavows any knowledge of its actions,
 *	except for the stuff related to the construction
 *	of the search patterns.
 *	Some additional enhancements made by Mark Horton, involving
 *	the options and special treatment of "main", "}" at beginning
 *	of line, and a few bug fixes.
 */

E 2
D 7
#define	reg	register
E 7
D 6
#define	logical	char
E 6
I 6
D 8
#define	bool	char
E 6

D 7
#define	TRUE	(1)
#define	FALSE	(0)
E 7
I 7
#define	YES		1
#define	NO		0
#define	EOS		'\0'
#define	MAXTOKEN	250		/* max size of single token */
#define	SETLINE		{++lineno;lineftell = ftell(inf);}
E 7

D 7
#define	iswhite(arg)	(_wht[arg])	/* T if char is white		*/
#define	begtoken(arg)	(_btk[arg])	/* T if char can start token	*/
#define	intoken(arg)	(_itk[arg])	/* T if char can be in token	*/
#define	endtoken(arg)	(_etk[arg])	/* T if char ends tokens	*/
#define	isgood(arg)	(_gd[arg])	/* T if char can be after ')'	*/
E 7
I 7
#define	iswhite(arg)	(_wht[arg])	/* T if char is white */
#define	begtoken(arg)	(_btk[arg])	/* T if char can start token */
#define	intoken(arg)	(_itk[arg])	/* T if char can be in token */
#define	endtoken(arg)	(_etk[arg])	/* T if char ends tokens */
#define	isgood(arg)	(_gd[arg])	/* T if char can be after ')' */
E 7

D 7
#define	max(I1,I2)	(I1 > I2 ? I1 : I2)
E 7
I 7
typedef struct nd_st {			/* sorting structure */
	struct nd_st	*left,
			*right;		/* left and right sons */
	char	*entry,			/* function or type name */
		*file,			/* file name */
		*pat;			/* search pattern */
	int	lno;			/* for -x option */
	bool	been_warned;		/* set if noticed dup */
} NODE;
E 8
NODE	*head;			/* head of the sorted binary tree */
E 7

D 7
struct	nd_st {			/* sorting structure			*/
D 4
	char	*func;			/* function name		*/
E 4
I 4
	char	*entry;			/* function or type name	*/
E 4
	char	*file;			/* file name			*/
I 4
D 6
	logical f;			/* use pattern or line no	*/
E 6
I 6
	bool	f;			/* use pattern or line no	*/
E 6
E 4
I 2
	int	lno;			/* for -x option		*/
E 2
	char	*pat;			/* search pattern		*/
D 6
	logical	been_warned;		/* set if noticed dup		*/
E 6
I 6
	bool	been_warned;		/* set if noticed dup		*/
E 6
	struct	nd_st	*left,*right;	/* left and right sons		*/
};
E 7
I 7
				/* boolean "func" (see init()) */
D 15
bool	_wht[0177],_etk[0177],_itk[0177],_btk[0177],_gd[0177];
E 15
I 15
bool	_wht[256], _etk[256], _itk[256], _btk[256], _gd[256];
E 15
E 7

D 7
long	ftell();
D 2
#ifdef DEBUG
char	*unctrl();
#endif
E 2
typedef	struct	nd_st	NODE;
E 7
I 7
D 15
FILE	*inf,			/* ioptr for current input file */
	*outf;			/* ioptr for tags file */
E 15
I 15
FILE	*inf;			/* ioptr for current input file */
FILE	*outf;			/* ioptr for tags file */
E 15
E 7

D 6
logical	number,				/* T if on line starting with #	*/
E 6
I 6
D 7
bool	number,				/* T if on line starting with #	*/
E 6
I 5
	term	= FALSE,		/* T if print on terminal	*/
	makefile= TRUE,			/* T if to creat "tags" file	*/
E 5
D 4
	term	= FALSE,		/* T if print on terminal	*/
	makefile= TRUE,			/* T if to creat "tags" file	*/
E 4
	gotone,				/* found a func already on line	*/
					/* boolean "func" (see init)	*/
	_wht[0177],_etk[0177],_itk[0177],_btk[0177],_gd[0177];
E 7
I 7
long	lineftell;		/* ftell after getc( inf ) == '\n' */
E 7

D 4
char	searchar = '?';			/* use ?...? searches 		*/
E 4
I 4
D 7
	/* typedefs are recognized using a simple finite automata,
	 * tydef is its state variable.
	 */
typedef enum {none, begin, middle, end } TYST;
E 7
I 7
D 15
int	lineno,			/* line number of current line */
D 8
	aflag,			/* -a: append to tags */
E 8
	dflag,			/* -d: non-macro defines */
	tflag,			/* -t: create tags for typedefs */
D 8
	uflag,			/* -u: update tags */
E 8
	wflag,			/* -w: suppress warnings */
	vflag,			/* -v: vgrind style index output */
	xflag;			/* -x: cxref style output */
E 15
I 15
int	lineno;			/* line number of current line */
int	dflag;			/* -d: non-macro defines */
int	tflag;			/* -t: create tags for typedefs */
int	vflag;			/* -v: vgrind style index output */
int	wflag;			/* -w: suppress warnings */
int	xflag;			/* -x: cxref style output */
E 15
E 7
E 4
D 2
#define	MAXPATTERN	50		/* according to bill		*/
E 2

I 4
D 7
TYST tydef = none;
E 7
I 7
D 15
char	*curfile,		/* current input file name */
	searchar = '/',		/* use /.../ searches by default */
D 8
	line[4*BUFSIZ],		/* current input line */
E 8
	lbuf[BUFSIZ];
E 15
I 15
char	*curfile;		/* current input file name */
char	searchar = '/';		/* use /.../ searches by default */
char	lbuf[LINE_MAX];
E 15
E 7

D 7
char	searchar = '/';			/* use /.../ searches 		*/

E 4
int	lineno;				/* line number of current line */
D 2
char	line[256],		/* current input line			*/
E 2
I 2
char	line[4*BUFSIZ],		/* current input line			*/
E 2
	*curfile,		/* current input file name		*/
	*outfile= "tags",	/* output file				*/
	*white	= " \f\t\n",	/* white chars				*/
	*endtk	= " \t\n\"'#()[]{}=-+%*/&|^~!<>;,.:?",
				/* token ending chars			*/
	*begtk	= "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz",
				/* token starting chars			*/
D 4
	*intk	= "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz0123456789",				/* valid in-token chars			*/
E 4
I 4
	*intk	= "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz0123456789",
				/* valid in-token chars			*/
E 4
	*notgd	= ",;";		/* non-valid after-function chars	*/

int	file_num;		/* current file number			*/
int	aflag;			/* -a: append to tags */
I 4
int	tflag;			/* -t: create tags for typedefs */
E 4
int	uflag;			/* -u: update tags */
int	wflag;			/* -w: suppress warnings */
I 3
int	vflag;			/* -v: create vgrind style index output */
E 3
I 2
int	xflag;			/* -x: create cxref style output */
E 2

I 2
char	lbuf[BUFSIZ];

E 2
FILE	*inf,			/* ioptr for current input file		*/
	*outf;			/* ioptr for tags file			*/

long	lineftell;		/* ftell after getc( inf ) == '\n' 	*/

NODE	*head;			/* the head of the sorted binary tree	*/

I 2
char	*savestr();
D 6
char	*rindex();
E 6
I 6
char	*rindex(), *index();
char	*toss_comment();

E 6
E 2
main(ac,av)
int	ac;
char	*av[];
E 7
I 7
D 15
main(argc,argv)
E 15
I 15
void	init __P((void));
void	find_entries __P((char *));

int
main(argc, argv)
E 15
	int	argc;
	char	**argv;
E 7
{
D 7
	char cmd[100];
	int i;
E 7
I 7
D 15
	extern char	*optarg;		/* getopt arguments */
	extern int	optind;
E 15
	static char	*outfile = "tags";	/* output file */
D 8
	int	exit_val,			/* exit value */
E 8
I 8
D 15
	int	aflag,				/* -a: append to tags */
		uflag,				/* -u: update tags */
		exit_val,			/* exit value */
E 8
		step,				/* step through args */
		ch;				/* getopts char */
E 15
I 15
	int	aflag;				/* -a: append to tags */
	int	uflag;				/* -u: update tags */
	int	exit_val;			/* exit value */
	int	step;				/* step through args */
	int	ch;				/* getopts char */
E 15
D 8
	char	cmd[100],			/* too ugly to explain */
		*savestr();
E 8
I 8
	char	cmd[100];			/* too ugly to explain */
E 8
E 7

I 8
	aflag = uflag = NO;
E 8
D 7
	while (ac > 1 && av[1][0] == '-') {
		for (i=1; av[1][i]; i++) {
			switch(av[1][i]) {
I 4
D 6
				case 'B':
					searchar='?';
					break;
				case 'F':
					searchar='/';
					break;
E 4
				case 'a':
					aflag++;
					break;
I 4
				case 't':
					tflag++;
					break;
E 4
				case 'u':
					uflag++;
					break;
				case 'w':
					wflag++;
					break;
I 3
				case 'v':
					vflag++;
					xflag++;
					break;
E 3
D 2

E 2
I 2
				case 'x':
					xflag++;
					break;
E 2
				default:
E 6
I 6
			  case 'B':
				searchar='?';
E 7
I 7
D 15
	while ((ch = getopt(argc,argv,"BFadf:tuwvx")) != EOF)
		switch((char)ch) {
			case 'B':
				searchar = '?';
E 7
				break;
D 7
			  case 'F':
				searchar='/';
E 7
I 7
			case 'F':
				searchar = '/';
E 7
				break;
D 7
			  case 'a':
E 7
I 7
			case 'a':
E 7
				aflag++;
				break;
D 7
			  case 't':
E 7
I 7
			case 'd':
				dflag++;
				break;
			case 'f':
				outfile = optarg;
				break;
			case 't':
E 7
				tflag++;
				break;
D 7
			  case 'u':
E 7
I 7
			case 'u':
E 7
				uflag++;
				break;
D 7
			  case 'w':
E 7
I 7
			case 'w':
E 7
				wflag++;
				break;
D 7
			  case 'v':
E 7
I 7
			case 'v':
E 7
				vflag++;
I 7
			case 'x':
E 7
				xflag++;
				break;
D 7
			  case 'x':
				xflag++;
				break;
			  case 'f':
				if (ac < 2)
E 6
					goto usage;
D 6
			}
E 6
I 6
				ac--, av++;
				outfile = av[1];
				goto next;
			  default:
E 7
I 7
			case '?':
			default:
E 7
				goto usage;
E 15
I 15
	while ((ch = getopt(argc, argv, "BFadf:tuwvx")) != EOF)
		switch(ch) {
		case 'B':
			searchar = '?';
			break;
		case 'F':
			searchar = '/';
			break;
		case 'a':
			aflag++;
			break;
		case 'd':
			dflag++;
			break;
		case 'f':
			outfile = optarg;
			break;
		case 't':
			tflag++;
			break;
		case 'u':
			uflag++;
			break;
		case 'w':
			wflag++;
			break;
		case 'v':
			vflag++;
		case 'x':
			xflag++;
			break;
		case '?':
		default:
			goto usage;
E 15
E 6
		}
I 6
D 7
		}
	next:
E 6
		ac--; av++;
	}

	if (ac <= 1) {
D 4
		usage: printf("Usage: ctags [-au] file ...\n");
E 4
I 4
D 6
usage:		printf("Usage: ctags [-BFatuwvx] file ...\n");
E 6
I 6
usage:
		printf("Usage: ctags [-BFatuwvx] [-f tagsfile] file ...\n");
E 7
I 7
	argv += optind;
	argc -= optind;
	if (!argc) {
D 15
usage:		puts("Usage: ctags [-BFadtuwvx] [-f tagsfile] file ...");
E 15
I 15
usage:		(void)fprintf(stderr,
D 17
			"usage: ctags [-BFadtuwvx] [-f tagsfile] file ...");
E 17
I 17
			"usage: ctags [-BFadtuwvx] [-f tagsfile] file ...\n");
E 17
E 15
E 7
E 6
E 4
		exit(1);
	}

D 7
	init();			/* set up boolean "functions"		*/
	/*
	 * loop through files finding functions
	 */
	for (file_num = 1; file_num < ac; file_num++)
D 4
		find_funcs(av[file_num]);
E 4
I 4
		find_entries(av[file_num]);
E 7
I 7
	init();
E 7
E 4

I 7
D 8
	for (exit_val = step = 0;step < argc;++step) {
		curfile = savestr(argv[step]);
E 8
I 8
D 15
	for (exit_val = step = 0;step < argc;++step)
E 8
		if (!(inf = fopen(argv[step],"r"))) {
			perror(argv[step]);
E 15
I 15
	for (exit_val = step = 0; step < argc; ++step)
		if (!(inf = fopen(argv[step], "r"))) {
			warn("%s", argv[step]);
E 15
			exit_val = 1;
		}
D 8
		else
E 8
I 8
		else {
			curfile = argv[step];
E 8
			find_entries(argv[step]);
D 8
	}
E 8
I 8
			(void)fclose(inf);
		}
E 8

E 7
I 2
D 8
	if (xflag) {
D 4
		put_funcs(head);
E 4
I 4
		put_entries(head);
E 4
D 7
		exit(0);
E 7
I 7
		exit(exit_val);
E 7
	}
E 2
	if (uflag) {
D 7
		for (i=1; i<ac; i++) {
D 2
			sprintf(cmd, "mv %s OTAGS ; fgrep -v '\t%s\t' OTAGS > %s ; rm OTAGS", outfile, av[i], outfile);
E 2
I 2
			sprintf(cmd,
				"mv %s OTAGS;fgrep -v '\t%s\t' OTAGS >%s;rm OTAGS",
				outfile, av[i], outfile);
E 7
I 7
		for (step = 0;step < argc;step++) {
			(void)sprintf(cmd,"mv %s OTAGS;fgrep -v '\t%s\t' OTAGS >%s;rm OTAGS",outfile,argv[step],outfile);
E 7
E 2
			system(cmd);
E 8
I 8
	if (head)
		if (xflag)
			put_entries(head);
		else {
			if (uflag) {
D 15
				for (step = 0;step < argc;step++) {
					(void)sprintf(cmd,"mv %s OTAGS;fgrep -v '\t%s\t' OTAGS >%s;rm OTAGS",outfile,argv[step],outfile);
E 15
I 15
				for (step = 0; step < argc; step++) {
					(void)sprintf(cmd,
						"mv %s OTAGS; fgrep -v '\t%s\t' OTAGS >%s; rm OTAGS",
							outfile, argv[step],
							outfile);
E 15
					system(cmd);
				}
				++aflag;
			}
D 15
			if (!(outf = fopen(outfile, aflag ? "a" : "w"))) {
				perror(outfile);
				exit(exit_val);
			}
E 15
I 15
			if (!(outf = fopen(outfile, aflag ? "a" : "w")))
				err(exit_val, "%s", outfile);
E 15
			put_entries(head);
			(void)fclose(outf);
			if (uflag) {
D 15
				(void)sprintf(cmd,"sort %s -o %s",outfile,outfile);
E 15
I 15
				(void)sprintf(cmd, "sort -o %s %s",
						outfile, outfile);
E 15
				system(cmd);
			}
E 8
		}
D 7
		aflag++;
E 7
I 7
D 8
		++aflag;
E 7
	}
D 2

	if ((outf = fopen(outfile, aflag ? "a" : "w")) == NULL) {
E 2
I 2
	outf = fopen(outfile, aflag ? "a" : "w");
D 7
	if (outf == NULL) {
E 7
I 7
	if (!outf) {
E 7
E 2
		perror(outfile);
D 7
		exit(1);
E 7
I 7
		exit(exit_val);
E 7
	}
D 2
	put_funcs(head);	/* put the data in "tags"		*/
E 2
I 2
D 4
	put_funcs(head);
E 4
I 4
	put_entries(head);
E 4
D 7
	fclose(outf);
E 7
I 7
	(void)fclose(outf);
E 7
	if (uflag) {
D 7
		sprintf(cmd, "sort %s -o %s", outfile, outfile);
E 7
I 7
		(void)sprintf(cmd,"sort %s -o %s",outfile,outfile);
E 7
		system(cmd);
	}
E 8
E 2
D 7
	exit(0);
E 7
I 7
	exit(exit_val);
E 7
}

/*
D 2
 *	This routine sets up the boolean psuedo-functions which work
E 2
I 2
D 7
 * This routine sets up the boolean psuedo-functions which work
E 2
 * by seting boolean flags dependent upon the corresponding character
D 2

E 2
 * Every char which is NOT in that string is not a white char.  Therefore,
 * all of the array "_wht" is set to FALSE, and then the elements
 * subscripted by the chars in "white" are set to TRUE.  Thus "_wht"
 * of a char is TRUE if it is the string "white", else FALSE.
E 7
I 7
 * init --
 *	this routine sets up the boolean psuedo-functions which work by
 *	setting boolean flags dependent upon the corresponding character.
 *	Every char which is NOT in that string is false with respect to
 *	the pseudo-function.  Therefore, all of the array "_wht" is NO
 *	by default and then the elements subscripted by the chars in
 *	CWHITE are set to YES.  Thus, "_wht" of a char is YES if it is in
 *	the string CWHITE, else NO.
E 7
D 2
 * It also open up the "tags" output file.
E 2
 */
I 15
void
E 15
init()
{
I 7
D 15
	register int	i;
	register char	*sp;
E 15
I 15
	int		i;
	unsigned char	*sp;
E 15
E 7

D 7
	reg	char	*sp;
	reg	int	i;

E 7
D 15
	for (i = 0; i < 0177; i++) {
E 15
I 15
	for (i = 0; i < 256; i++) {
E 15
D 7
		_wht[i] = _etk[i] = _itk[i] = _btk[i] = FALSE;
		_gd[i] = TRUE;
E 7
I 7
		_wht[i] = _etk[i] = _itk[i] = _btk[i] = NO;
		_gd[i] = YES;
E 7
	}
D 7
	for (sp = white; *sp; sp++)
		_wht[*sp] = TRUE;
	for (sp = endtk; *sp; sp++)
		_etk[*sp] = TRUE;
	for (sp = intk; *sp; sp++)
		_itk[*sp] = TRUE;
	for (sp = begtk; *sp; sp++)
		_btk[*sp] = TRUE;
	for (sp = notgd; *sp; sp++)
		_gd[*sp] = FALSE;
E 7
I 7
#define	CWHITE	" \f\t\n"
	for (sp = CWHITE; *sp; sp++)	/* white space chars */
		_wht[*sp] = YES;
#define	CTOKEN	" \t\n\"'#()[]{}=-+%*/&|^~!<>;,.:?"
	for (sp = CTOKEN; *sp; sp++)	/* token ending chars */
		_etk[*sp] = YES;
#define	CINTOK	"ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz0123456789"
	for (sp = CINTOK; *sp; sp++)	/* valid in-token chars */
		_itk[*sp] = YES;
#define	CBEGIN	"ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"
	for (sp = CBEGIN; *sp; sp++)	/* token starting chars */
		_btk[*sp] = YES;
#define	CNOTGD	",;"
	for (sp = CNOTGD; *sp; sp++)	/* invalid after-function chars */
		_gd[*sp] = NO;
E 7
}

/*
D 2
 *	This program opens the specified file and calls the function
 * which finds the function defenitions.
E 2
I 2
D 7
 * This routine opens the specified file and calls the function
D 4
 * which finds the function definitions.
E 4
I 4
 * which finds the function and type definitions.
E 7
I 7
 * find_entries --
 *	this routine opens the specified file and calls the function
 *	which searches the file.
E 7
E 4
E 2
 */
I 15
void
E 15
D 4
find_funcs(file)
E 4
I 4
find_entries(file)
E 4
D 7
char	*file;
E 7
I 7
	char	*file;
E 7
{
I 2
D 7
	char *cp;
E 7
I 7
D 15
	register char	*cp;
E 15
I 15
	char	*cp;
E 15
E 7
E 2

D 6
	if ((inf=fopen(file,"r")) == NULL) {
E 6
I 6
D 7
	if ((inf = fopen(file,"r")) == NULL) {
E 6
		perror(file);
		return;
	}
D 2

	curfile = (char *) calloc(strlen(file)+1,1);
	strcpy(curfile, file);
	lineno = 1;
	C_funcs();		/* find the C-style functions		*/
E 2
I 2
	curfile = savestr(file);
I 6
	lineno = 0;
E 6
	cp = rindex(file, '.');
D 5
	if (cp && (cp[1] != 'c' || cp[1] != 'h') && cp[2] == 0) {
		if (PF_funcs(inf) == 0) {
			rewind(inf);
D 4
			C_funcs();
E 4
I 4
			C_entries();
E 5
I 5
D 6
	/* .l implies lisp source code */
E 6
I 6
	/* .l implies lisp or lex source code */
E 6
	if (cp && cp[1] == 'l' && cp[2] == '\0') {
D 6
		L_funcs(inf);
E 6
I 6
		if (index(";([", first_char()) != NULL) {	/* lisp */
			L_funcs(inf);
			fclose(inf);
			return;
E 7
I 7
	lineno = 0;				/* should be 1 ?? KB */
D 15
	if (cp = rindex(file, '.')) {
E 15
I 15
	if (cp = strrchr(file, '.')) {
E 15
		if (cp[1] == 'l' && !cp[2]) {
D 8
/* lisp */		if (index(";([",(char)first_char())) {
				L_funcs();
				goto done;
			}
/* lex */		else {
				toss_yysec();
				getline();
				pfnote("yylex",lineno);
				toss_yysec();
			}
E 7
		}
D 7
		else {						/* lex */
			/*
			 * throw away all the code before the second "%%"
			 */
			toss_yysec();
			getline();
			pfnote("yylex", lineno, TRUE);
			toss_yysec();
			C_entries();
			fclose(inf);
			return;
E 7
I 7
/* yacc */	else if (cp[1] == 'y' && !cp[2])
			Y_entries();
/* fortran */	else if ((cp[1] != 'c' && cp[1] != 'h') && !cp[2]) {
			if (PF_funcs())
				goto done;
			rewind(inf);
E 7
		}
	}
D 7
	/* .y implies a yacc file */
	if (cp && cp[1] == 'y' && cp[2] == '\0') {
		toss_yysec();
		Y_entries();
		C_entries();
E 6
		fclose(inf);
		return;
	}
	/* if not a .c or .h file, try fortran */
	if (cp && (cp[1] != 'c' && cp[1] != 'h') && cp[2] == '\0') {
		if (PF_funcs(inf) != 0) {
			fclose(inf);
			return;
E 5
E 4
		}
D 5
	} else
D 4
		C_funcs();
E 4
I 4
		C_entries();
E 5
I 5
		rewind(inf);	/* no fortran tags found, try C */
	}
	C_entries();
E 5
E 4
E 2
	fclose(inf);
E 7
I 7
	c_entries();		/* default: try C */
done:	(void)fclose(inf);
E 7
}
E 8
I 8
D 15
			register int	c;
E 15
I 15
			int	c;
E 15
E 8

I 2
D 4
pfnote(name, ln)
E 4
I 4
D 7
pfnote(name, ln, f)
E 4
D 6
	char *name;
I 4
	logical f;			/* f == TRUE when function */
E 6
I 6
char	*name;
int	ln;
bool	f;		/* f == TRUE when function */
E 7
I 7
D 8
/*
 * pfnote --
 *	enter a new node in the tree
 */
pfnote(name,ln)
	char	*name;
	int	ln;
E 7
E 6
E 4
{
D 7
	register char *fp;
	register NODE *np;
	char nbuf[BUFSIZ];
E 7
I 7
	register NODE	*np;
	register char	*fp;
	char	nbuf[BUFSIZ],
		*malloc(), *savestr();
E 7

D 7
	if ((np = (NODE *) malloc(sizeof (NODE))) == NULL) {
D 4
		fprintf(stderr, "ctags: too many functions to sort\n");
		put_funcs(head);
E 4
I 4
		fprintf(stderr, "ctags: too many entries to sort\n");
E 7
I 7
	if (!(np = (NODE *)malloc(sizeof(NODE)))) {
		fputs("ctags: too many entries to sort\n",stderr);
E 7
		put_entries(head);
E 4
		free_tree(head);
D 7
		head = np = (NODE *) malloc(sizeof (NODE));
E 7
I 7
		if (!(np = (NODE *)malloc(sizeof(NODE)))) {
			fputs("ctags: out of space.\n",stderr);
			exit(1);
		}
		head = np;
E 7
	}
D 7
	if (xflag == 0 && !strcmp(name, "main")) {
		fp = rindex(curfile, '/');
		if (fp == 0)
E 7
I 7
	if (!xflag && !bcmp(name,"main",4)) {
		if (!(fp = rindex(curfile,'/')))
E 7
			fp = curfile;
		else
D 7
			fp++;
		sprintf(nbuf, "M%s", fp);
		fp = rindex(nbuf, '.');
		if (fp && fp[2] == 0)
E 7
I 7
			++fp;
		(void)sprintf(nbuf,"M%s",fp);
		fp = rindex(nbuf,'.');
		if (fp && !fp[2])
E 7
			*fp = 0;
		name = nbuf;
	}
D 4
	np->func = savestr(name);
E 4
I 4
	np->entry = savestr(name);
E 4
	np->file = curfile;
I 4
D 7
	np->f = f;
E 7
E 4
	np->lno = ln;
	np->left = np->right = 0;
D 7
	if (xflag == 0) {
E 7
I 7
	if (!xflag) {
E 7
		lbuf[50] = 0;
D 7
		strcat(lbuf, "$");
E 7
I 7
		(void)strcat(lbuf,"$");
E 7
		lbuf[50] = 0;
	}
	np->pat = savestr(lbuf);
D 7
	if (head == NULL)
E 7
I 7
	if (!head)
E 7
		head = np;
	else
		add_node(np, head);
}

E 2
/*
D 2
 *	This routine finds functions in C syntax and adds them
E 2
I 2
D 4
 * This routine finds functions in C syntax and adds them
E 4
I 4
D 7
 * This routine finds functions and typedefs in C syntax and adds them
E 4
E 2
 * to the list.
E 7
I 7
 * c_entries --
 *	read .c and .h files and call appropriate routines
E 7
 */
D 4
C_funcs()
E 4
I 4
D 7
C_entries()
E 7
I 7
c_entries()
E 7
E 4
{
I 2
D 7
	register int c;
	register char *token, *tp;
D 4
	int incomm, inquote, inchar, midtoken, level;
E 4
I 4
D 6
	logical incomm, inquote, inchar, midtoken;
E 6
I 6
	bool incomm, inquote, inchar, midtoken;
E 6
	int level;
E 4
	char *sp;
	char tok[BUFSIZ];
E 7
I 7
	register int	c,		/* current character */
			level;		/* brace level */
	register char	*sp;		/* buffer pointer */
	int	token,			/* if reading a token */
		t_def,			/* if reading a typedef */
		t_level;		/* typedef's brace level */
	char	tok[MAXTOKEN];		/* token buffer */
E 7
E 2

D 2
	reg	char	c,		/* current input char		*/
			*token,		/* start of current token	*/
			*tp;		/* end of current token		*/
	logical	incom,			/* T if inside a comment	*/
		inquote,		/* T if inside a quoted string	*/
		inchar,			/* T if inside a single char '	*/
		midtoken;		/* T if in middle of token	*/
	char	*sp;			/* current input char		*/
	char	tok[100];
	long	insub;			/* level of "{}"s deep		*/

	/*
	 * init boolean flags, counters, and pointers
	 */

	number = gotone = midtoken = inquote = inchar = incom = FALSE;
	insub = 0L;
E 2
I 2
D 6
	lineno = 1;
E 6
D 7
	number = gotone = midtoken = inquote = inchar = incomm = FALSE;
	level = 0;
E 2
	sp = tp = token = line;
I 6
	lineno++;
E 7
	lineftell = ftell(inf);
E 6
D 2
#ifdef DEBUG
	printf("           t  s c m q c g n\n");
	printf("     s  t  k  u o i u h o u\n");
	printf(" c   p  p  n  b m d o r t m\n");
#endif
	while ((*sp=c=getc(inf)) != EOF) {
#ifdef DEBUG
		printf("%2.2s: ",unctrl(c));
		printf("%2.2s ",unctrl(*sp));
		printf("%2.2s ",unctrl(*tp));
		printf("%2.2s ",unctrl(*token));
		printf("%2ld %d %d %d %d %d %d\n",insub,incom,midtoken,inquote,inchar,gotone,number);
#endif
		/*
		 * action based on mixture of character type, *sp,
		 * and logical flags
		 */

E 2
I 2
D 7
	for (;;) {
D 6
		*sp=c=getc(inf);
E 6
I 6
		*sp = c = getc(inf);
E 6
		if (feof(inf))
			break;
		if (c == '\n')
			lineno++;
E 2
D 6
		if (c == '\\') {
E 6
I 6
		else if (c == '\\') {
E 6
			c = *++sp = getc(inf);
D 2
			/*
			 * Handling of backslash is very naive.
			 * We do, however, turn escaped newlines
			 * into spaces.
			 */
E 2
D 6
			if (c = '\n')
E 6
I 6
			if (c == '\n')
E 6
				c = ' ';
D 2
		}
		else if (incom) {
E 2
I 2
D 6
		} else if (incomm) {
E 6
I 6
		}
		else if (incomm) {
E 6
E 2
			if (c == '*') {
D 2
				while ((*++sp=c=getc(inf)) == '*') {
#ifdef DEBUG
					printf("%2.2s- ",unctrl(c));
					printf("%2.2s ",unctrl(*sp));
					printf("%2.2s ",unctrl(*tp));
					printf("%2.2s ",unctrl(*token));
					printf("%2ld %d %d %d %d %d %d\n",insub,incom,midtoken,inquote,inchar,gotone,number);
#endif
E 2
I 2
				while ((*++sp=c=getc(inf)) == '*')
E 2
					continue;
D 2
				}
#ifdef DEBUG
				printf("%2.2s- ",unctrl(c));
				printf("%2.2s ",unctrl(*sp));
				printf("%2.2s ",unctrl(*tp));
				printf("%2.2s ",unctrl(*token));
				printf("%2ld %d %d %d %d %d %d\n",insub,incom,midtoken,inquote,inchar,gotone,number);
#endif
E 2
I 2
				if (c == '\n')
					lineno++;
E 2
				if (c == '/')
D 2
					incom = FALSE;
E 2
I 2
					incomm = FALSE;
E 2
			}
D 2
		}
		else if (inquote) {
E 2
I 2
D 6
		} else if (inquote) {
E 6
I 6
		}
		else if (inquote) {
E 7
I 7
	sp = tok; token = t_def = NO; t_level = -1; level = 0; lineno = 1;
	while ((c = getc(inf)) != EOF) {

	switch ((char)c) {
		/*
		 * Here's where it DOESN'T handle:
		 *	foo(a)
		 *	{
		 *	#ifdef notdef
		 *		}
		 *	#endif
		 *		if (a)
		 *			puts("hello, world");
		 *	}
		 */
		case '{':
			++level;
			goto endtok;
		case '}':
E 7
E 6
E 2
			/*
D 7
			 * Too dumb to know about \" not being magic, but
			 * they usually occur in pairs anyway.
E 7
I 7
			 * if level goes below zero, try and fix
			 * it, even though we've already messed up
E 7
			 */
D 2
			if ( c == '"' )
E 2
I 2
D 7
			if (c == '"')
E 2
				inquote = FALSE;
			continue;
D 2
		     }
		else if (inchar) {
			if ( c == '\'' )
E 2
I 2
D 6
		} else if (inchar) {
E 6
I 6
		}
		else if (inchar) {
E 6
			if (c == '\'')
E 2
				inchar = FALSE;
			continue;
D 2
		     }
		else if (c == '"')
E 2
I 2
D 6
		} else switch (c) {
		case '"':
E 6
I 6
		}
		else switch (c) {
		  case '"':
E 6
E 2
			inquote = TRUE;
D 2
		else if (c == '\'')
E 2
I 2
			continue;
D 6
		case '\'':
E 6
I 6
		  case '\'':
E 6
E 2
			inchar = TRUE;
D 2
		else if (c == '/')
E 2
I 2
			continue;
D 6
		case '/':
E 6
I 6
		  case '/':
E 6
E 2
			if ((*++sp=c=getc(inf)) == '*')
D 2
				incom = TRUE;
E 2
I 2
				incomm = TRUE;
E 7
I 7
			if (--level < 0)
				level = 0;
			goto endtok;

		case '\n':
			SETLINE;
			/*
			 * the above 3 cases are similar in that they
			 * are special characters that also end tokens.
			 */
endtok:			if (sp > tok) {
				*sp = EOS;
				token = YES;
				sp = tok;
E 8
I 8
			for (;;) {
D 15
				if (GETC(==,EOF))
E 15
I 15
				if (GETC(==, EOF))
E 15
					return;
				if (!iswhite(c)) {
					rewind(inf);
					break;
				}
E 8
			}
E 7
E 2
D 8
			else
D 2
				ungetc(*sp,inf);
		else if (c == '#' && sp == line)
			number = TRUE;
		else if (c == '{')
			insub++;
		else if (c == '}')
E 2
I 2
D 7
				ungetc(*sp, inf);
E 7
I 7
				token = NO;
E 7
			continue;
D 6
		case '#':
E 6
I 6
D 7
		  case '#':
E 6
E 2
			if (sp == line)
D 2
				/*
				 * Kludge to get back in sync after getting confused.
				 * We really shouldn't be looking at indenting style,
				 * but tricking with the preprocessor can get us off,
				 * and most people indent this way anyway.
				 * This resets level of indenting to zero if '}' is
				 * found at beginning of line.
				 */
				insub = 0;
E 2
I 2
				number = TRUE;
			continue;
D 6
		case '{':
E 6
I 6
		  case '{':
E 6
I 4
			if (tydef == begin) {
				tydef=middle;
E 7
I 7

		/* we ignore quoted strings and comments in their entirety */
		case '"':
		case '\'':
			skip_key(c);
			break;
		case '/':
			if ((c = getc(inf)) == '*') {
				skip_comment();
				break;
E 7
			}
E 4
D 7
			level++;
			continue;
D 6
		case '}':
E 6
I 6
		  case '}':
E 6
			if (sp == line)
				level = 0;	/* reset */
E 2
			else
D 2
				insub--;
		else if (!insub && !inquote && !inchar && !gotone) {
E 2
I 2
				level--;
I 4
			if (!level && tydef==middle) {
				tydef=end;
E 7
I 7
			(void)ungetc(c,inf);
			c = '/';
			goto storec;

		/* hash marks are interesting if they start #define's. */
		case '#':
			if (sp == tok) {
				hash_entry();
				break;
E 7
			}
E 4
D 7
			continue;
		}
D 4
		if (!level && !inquote && !incomm && gotone == 0) {
E 4
I 4
		if (!level && !inquote && !incomm && gotone == FALSE) {
E 4
E 2
			if (midtoken) {
				if (endtoken(c)) {
I 4
					int f;
E 4
I 2
					int pfline = lineno;
E 2
D 4
					if (start_func(&sp,token,tp)) {
E 4
I 4
D 5
					if (start_entry(&sp,token,&f)) {
E 5
I 5
					if (start_entry(&sp,token,tp,&f)) {
E 5
E 4
						strncpy(tok,token,tp-token+1);
						tok[tp-token+1] = 0;
E 7
I 7
			goto storec;

		/*
	 	 * if we have a current token, parenthesis on
		 * level zero indicates a function.
		 */
		case '(':
			if (!level && token) {
				int	curline;

				if (sp != tok)
					*sp = EOS;
E 8
I 8
#define	LISPCHR	";(["
D 15
/* lisp */		if (index(LISPCHR,(char)c)) {
E 15
I 15
/* lisp */		if (strchr(LISPCHR, c)) {
E 15
				l_entries();
				return;
			}
/* lex */		else {
E 8
				/*
D 8
				 * grab the line immediately, we may
				 * already be wrong, for example,
				 *	foo
				 *	(arg1,
E 8
I 8
				 * we search all 3 parts of a lex file
				 * for C references.  This may be wrong.
E 8
				 */
I 9
				toss_yysec();
E 9
D 8
				getline();
				curline = lineno;
				if (func_entry()) {
					++level;
					pfnote(tok,curline);
				}
				break;
E 8
I 8
D 15
				(void)strcpy(lbuf,"%%$");
D 9
				pfnote("yylex",0);
E 9
I 9
				pfnote("yylex",lineno);
E 15
I 15
				(void)strcpy(lbuf, "%%$");
				pfnote("yylex", lineno);
E 15
				rewind(inf);
E 9
E 8
			}
D 8
			goto storec;

		/*
		 * semi-colons are interesting in that they indicate the end
		 * of a typedef; if we find a typedef we search for the next
		 * semi-colon of the same level as the typedef.  They are
		 * fairly tough, can be:
		 *
		 *	"typedef long time_t;"
		 *	"typedef unsigned int u_int;"
		 *	"typedef unsigned int u_int [10];"
		 *
		 * If looking at a typedef, we save a copy of the last token
		 * found.  Then, when we find the ';' we take the current
		 * token if it starts with a valid token name, else we take
		 * the one we saved.  There's probably some reasonable
		 * alternative to this...
		 */
		case ';':
			if (t_def && level == t_level) {
				t_def = NO;
				getline();
				if (sp != tok)
					*sp = EOS;
				pfnote(tok,lineno);
				break;
			}
			goto storec;

		/*
		 * store characters until one that can't be part of a token
		 * comes along; check the current token against certain
		 * reserved words.
		 */
		default:
storec:			if (!intoken(c)) {
				if (sp == tok)
					break;
				*sp = EOS;
				if (tflag) {
					/* no typedefs inside typedefs */
					if (!t_def && !bcmp(tok,"typedef",8)) {
						t_def = YES;
						t_level = level;
						break;
					}
					/* catch "typedef struct" */
					if ((!t_def || t_level < level)
					    && (!bcmp(tok,"struct",7)
					    || !bcmp(tok,"union",6)
					    || !bcmp(tok,"enum",5))) {
						/*
						 * get line immediately;
						 * may change before '{'
						 */
E 7
D 2
						add_func(tok);
E 2
I 2
						getline();
D 4
						pfnote(tok, pfline);
E 2
						gotone = TRUE;
E 4
I 4
D 7
						pfnote(tok, pfline, f);
						gotone = f;	/* function */
E 7
I 7
						if (str_entry(c))
							++level;
						break;
E 7
E 4
					}
D 7
					midtoken = FALSE;
					token = sp;
E 7
D 2
				}
				else if (intoken(c))
E 2
I 2
D 6
				} else if (intoken(c))
E 6
I 6
				}
D 7
				else if (intoken(c))
E 6
E 2
					tp++;
E 7
I 7
				sp = tok;
E 7
D 2
			}
			else if (begtoken(c)) {
E 2
I 2
D 6
			} else if (begtoken(c)) {
E 6
I 6
			}
D 7
			else if (begtoken(c)) {
E 6
E 2
				token = tp = sp;
				midtoken = TRUE;
E 7
I 7
			else if (sp != tok || begtoken(c)) {
				*sp++ = c;
				token = YES;
E 7
			}
I 7
			continue;
E 8
E 7
		}
I 4
D 7
		if (c == ';'  &&  tydef==end)	/* clean with typedefs */
			tydef=none;
E 4
D 2

		/*
		 * move on to next char, and set flags accordingly
		 */

E 2
		sp++;
D 2
		if (c == '\n') {
E 2
I 2
		if (c == '\n' || sp > &line[sizeof (line) - BUFSIZ]) {
E 2
			tp = token = sp = line;
D 2
			lineftell = ftell( inf );
#ifdef DEBUG
			printf("lineftell saved as %ld\n",lineftell);
#endif
E 2
I 2
			lineftell = ftell(inf);
E 2
			number = gotone = midtoken = inquote = inchar = FALSE;
D 2
			lineno++;
E 2
		}
E 7
I 7
D 8
		sp = tok;
		token = NO;
E 7
	}
}

/*
D 4
 *	This routine  checks to see if the current token is
 * at the start of a function.  It updates the input line
 * so that the '(' will be in it when it returns.
E 4
I 4
D 7
 * This routine  checks to see if the current token is
 * at the start of a function, or corresponds to a typedef
 * It updates the input line * so that the '(' will be
 * in it when it returns.
E 7
I 7
 * func_entry --
 *	handle a function reference
E 7
E 4
 */
D 4
start_func(lp,token,tp)
char	**lp,*token,*tp;
E 4
I 4
D 5
start_entry(lp,token,f)
char	**lp;
register char *token;
E 5
I 5
D 7
start_entry(lp,token,tp,f)
char	**lp,*token,*tp;
E 5
int	*f;
E 7
I 7
func_entry()
E 7
E 4
{
D 6

E 6
D 4
	reg	char	c,*sp,*tsp;
E 4
I 4
D 5
	reg	char	c,*sp;
E 5
I 5
D 7
	reg	char	c,*sp,*tsp;
E 5
E 4
D 6
	static	logical	found;
	logical	firsttok;		/* T if have seen first token in ()'s */
E 6
I 6
	static	bool	found;
	bool	firsttok;		/* T if have seen first token in ()'s */
E 6
	int	bad;
E 7
I 7
	register int	c;		/* current character */
E 7

I 4
D 7
	*f = 1;			/* a function */
E 4
	sp = *lp;
	c = *sp;
	bad = FALSE;
D 2
	if (!number)		/* space is not allowed in macro defs	*/
E 2
I 2
	if (!number) {		/* space is not allowed in macro defs	*/
E 2
		while (iswhite(c)) {
			*++sp = c = getc(inf);
D 2
#ifdef DEBUG
			printf("%2.2s:\n",unctrl(c));
#endif
E 2
I 2
			if (c == '\n') {
				lineno++;
				if (sp > &line[sizeof (line) - BUFSIZ])
					goto ret;
			}
E 2
		}
	/* the following tries to make it so that a #define a b(c)	*/
	/* doesn't count as a define of b.				*/
E 7
I 7
	skip_key((int)')');
	while ((c = getc(inf)) != EOF && iswhite(c))
		if (c == (int)'\n')
			SETLINE;
	if (!intoken(c) && c != (int)'{')
		return(NO);
	if (c != (int)'{')
		skip_key((int)'{');
	return(YES);
}

/*
 * hash_entry --
 *	handle a line starting with a '#'
 */
hash_entry()
{
	register int	c,		/* character read */
			curline;	/* line started on */
	register char	*sp;		/* buffer pointer */
	char	tok[MAXTOKEN];		/* storage buffer */

	curline = lineno;
	for (sp = tok;;) {		/* get next token */
		if ((c = getc(inf)) == EOF)
			return;
		if (iswhite(c))
			break;
		*sp++ = c;
E 7
D 2
	else {
E 2
I 2
D 6
	} else {
E 6
I 6
	}
D 7
	else {
E 6
E 2
D 4
		logical	define;

		define = TRUE;
		for (tsp = "define"; *tsp && token < tp; tsp++)
			if (*tsp != *token++) {
				define = FALSE;
				break;
			}
		if (define)
E 4
I 4
		if (!strncmp(token, "define", 6))
E 4
			found = 0;
		else
			found++;
		if (found >= 2) {
			gotone = TRUE;
badone:			bad = TRUE;
			goto ret;
		}
E 7
I 7
	*sp = EOS;
	if (bcmp(tok,"define",6))	/* only interested in #define's */
		goto skip;
	for (;;) {			/* this doesn't handle "#define \n" */
		if ((c = getc(inf)) == EOF)
			return;
		if (!iswhite(c))
			break;
E 7
	}
I 4
D 7
	/* check for the typedef cases		*/
	if (tflag && !strncmp(token, "typedef", 7)) {
		tydef=begin;
		goto badone;
E 7
I 7
	for (sp = tok;;) {		/* get next token */
		*sp++ = c;
		if ((c = getc(inf)) == EOF)
			return;
		/*
		 * this is where it DOESN'T handle
		 * "#define \n"
		 */
		if (!intoken(c))
			break;
E 7
	}
D 7
	if (tydef==begin && (!strncmp(token, "struct", 6) ||
	    !strncmp(token, "union", 5) || !strncmp(token, "enum", 4))) {
		goto badone;
E 7
I 7
	*sp = EOS;
	if (dflag || c == (int)'(') {	/* only want macros */
		getline();
		pfnote(tok,curline);
E 7
	}
D 7
	if (tydef==begin) {
		tydef=end;
		goto badone;
E 7
I 7
skip:	if (c == (int)'\n') {		/* get rid of rest of define */
		SETLINE
		if (*(sp - 1) != '\\')
			return;
E 7
	}
D 7
	if (tydef==end) {
		*f = 0;
		goto ret;
E 7
I 7
	skip_line();
}

/*
 * str_entry --
 *	handle a struct, union or enum entry
 */
str_entry(c)
	register int	c;		/* current character */
{
	register char	*sp;		/* buffer pointer */
	int	curline;		/* line started on */
	char	tok[BUFSIZ];		/* storage buffer */

	curline = lineno;
	while (iswhite(c))
		if ((c = getc(inf)) == EOF)
			return(NO);
	if (c == (int)'{')		/* it was "struct {" */
		return(YES);
	for (sp = tok;;) {		/* get next token */
		*sp++ = c;
		if ((c = getc(inf)) == EOF)
			return(NO);
		if (!intoken(c))
			break;
E 7
	}
E 4
D 7
	if (c != '(')
		goto badone;
	firsttok = FALSE;
	while ((*++sp=c=getc(inf)) != ')') {
I 2
		if (c == '\n') {
			lineno++;
			if (sp > &line[sizeof (line) - BUFSIZ])
				goto ret;
		}
E 2
		/*
		 * This line used to confuse ctags:
		 *	int	(*oldhup)();
		 * This fixes it. A nonwhite char before the first
		 * token, other than a / (in case of a comment in there)
		 * makes this not a declaration.
		 */
D 6
		if (begtoken(c) || c=='/') firsttok++;
		else if (!iswhite(c) && !firsttok) goto badone;
E 6
I 6
		if (begtoken(c) || c=='/')
			firsttok++;
		else if (!iswhite(c) && !firsttok)
			goto badone;
E 7
I 7
	switch ((char)c) {
		case '{':		/* it was "struct foo{" */
			--sp;
			break;
		case '\n':		/* it was "struct foo\n" */
			SETLINE;
			/*FALLTHROUGH*/
		default:		/* probably "struct foo " */
			while ((c = getc(inf)) != EOF)
				if (!iswhite(c))
					break;
			if (c != (int)'{')
				return(NO);
E 7
E 6
D 2
#ifdef DEBUG
		printf("%2.2s:\n",unctrl(c));
#endif
E 2
	}
D 2
#ifdef DEBUG
	printf("%2.2s:\n",unctrl(c));
#endif
E 2
D 7
	while (iswhite(*++sp=c=getc(inf)))
D 2
#ifdef DEBUG
		printf("%2.2s:\n",unctrl(c))
#endif
		;
#ifdef DEBUG
	printf("%2.2s:\n",unctrl(c));
#endif
E 2
I 2
		if (c == '\n') {
			lineno++;
			if (sp > &line[sizeof (line) - BUFSIZ])
E 7
I 7
	*sp = EOS;
	pfnote(tok,curline);
	return(YES);
}

/*
 * skip_line --
 *	skip to next line
 */
skip_line()
{
	register int	c,
			savec;

	for (savec = '\0';(c = getc(inf)) != EOF;savec = c)
		if (c == (int)'\n') {
			SETLINE;
			if (savec != (int)'\\')
				return;
E 8
I 8
/* yacc */	else if (cp[1] == 'y' && !cp[2]) {
			/*
			 * we search only the 3rd part of a yacc file
			 * for C references.  This may be wrong.
			 */
			toss_yysec();
I 9
D 15
			(void)strcpy(lbuf,"%%$");
			pfnote("yyparse",lineno);
E 15
I 15
			(void)strcpy(lbuf, "%%$");
			pfnote("yyparse", lineno);
E 15
E 9
			y_entries();
E 8
		}
D 8
}

/*
 * skip_key --
 *	skip to next char "key"
 */
skip_key(key)
	register int	key;
{
	register int	c;

	while((c = getc(inf)) != EOF && c != key)
		if (c == (int)'\n')
			SETLINE;
}

/*
 * skip_comment --
 *	skip over comment
 */
skip_comment()
{
	register int	c,
			level,
			star,
			slash;

	for (level = 1,slash = star = 0;(c = getc(inf)) != EOF;)
		switch((char)c) {
			case '*':
				if (slash) {
					++level;
					slash = 0;
				}
				else
					++star;
E 7
				break;
I 7
			case '/':
				if (star) {
					if (!--level)
						return;
					star = 0;
				}
				else
					++slash;
				break;
			case '\n':
				SETLINE;
			default:
				slash = star = 0;
E 7
		}
E 2
D 7
ret:
	*lp = --sp;
I 2
	if (c == '\n')
		lineno--;
E 2
	ungetc(c,inf);
D 4
	return !bad && isgood(c);
E 4
I 4
	return !bad && (!*f || isgood(c));
					/* hack for typedefs */
E 7
E 4
}

I 6
/*
 * Y_entries:
 *	Find the yacc tags and put them in.
 */
Y_entries()
{
D 7
	register char	*sp, *orig_sp;
E 7
I 7
	register char	*sp,
			*orig_sp;
E 7
	register int	brace;
D 7
	register bool	in_rule, toklen;
	char		tok[BUFSIZ];
E 7
I 7
	register bool	in_rule,
			toklen;
	char	tok[BUFSIZ],
		*toss_comment();
E 7

I 7
	toss_yysec();
E 7
	brace = 0;
	getline();
D 7
	pfnote("yyparse", lineno, TRUE);
	while (fgets(line, sizeof line, inf) != NULL)
		for (sp = line; *sp; sp++)
			switch (*sp) {
			  case '\n':
				lineno++;
				/* FALLTHROUGH */
			  case ' ':
			  case '\t':
			  case '\f':
			  case '\r':
				break;
			  case '"':
				do {
					while (*++sp != '"')
						continue;
				} while (sp[-1] == '\\');
				break;
			  case '\'':
				do {
					while (*++sp != '\'')
						continue;
				} while (sp[-1] == '\\');
				break;
			  case '/':
				if (*++sp == '*')
					sp = toss_comment(sp);
				else
					--sp;
				break;
			  case '{':
				brace++;
				break;
			  case '}':
				brace--;
				break;
			  case '%':
				if (sp[1] == '%' && sp == line)
					return;
				break;
			  case '|':
			  case ';':
				in_rule = FALSE;
				break;
			  default:
				if (brace == 0  && !in_rule && (isalpha(*sp) ||
								*sp == '.' ||
								*sp == '_')) {
					orig_sp = sp;
					++sp;
					while (isalnum(*sp) || *sp == '_' ||
					       *sp == '.')
						sp++;
					toklen = sp - orig_sp;
					while (isspace(*sp))
						sp++;
					if (*sp == ':' || (*sp == '\0' &&
							   first_char() == ':'))
					{
						strncpy(tok, orig_sp, toklen);
						tok[toklen] = '\0';
						strcpy(lbuf, line);
						lbuf[strlen(lbuf) - 1] = '\0';
						pfnote(tok, lineno, TRUE);
						in_rule = TRUE;
					}
					else
						sp--;
E 7
I 7
	pfnote("yyparse",lineno);
	while (fgets(line,sizeof(line),inf))
	    for (sp = line;*sp;++sp)
		switch (*sp) {
		case '\n':
			lineno++;
			/* FALLTHROUGH */
		case ' ':
		case '\t':
		case '\f':
		case '\r':
			break;
		case '"':
			do {
				while (*++sp != '"')
					continue;
			} while (sp[-1] == '\\');
			break;
		case '\'':
			do {
				while (*++sp != '\'')
					continue;
			} while (sp[-1] == '\\');
			break;
		case '/':
			if (*++sp == '*')
				sp = toss_comment(sp);
			else
				--sp;
			break;
		case '{':
			brace++;
			break;
		case '}':
			brace--;
			break;
		case '%':
			if (sp[1] == '%' && sp == line)
E 8
I 8
/* fortran */	else if ((cp[1] != 'c' && cp[1] != 'h') && !cp[2]) {
			if (PF_funcs())
E 8
				return;
D 8
			break;
		case '|':
		case ';':
			in_rule = NO;
			break;
		default:
			if (!brace && !in_rule && (isalpha(*sp) ||
			    *sp == '.' || *sp == '_')) {
				orig_sp = sp;
				++sp;
				while (isalnum(*sp) || *sp == '_' ||
				    *sp == '.')
					sp++;
				toklen = sp - orig_sp;
				while (isspace(*sp))
					sp++;
				if (*sp == ':' || (*sp == '\0' &&
				    first_char() == ':')) {
					(void)strncpy(tok, orig_sp, toklen);
					tok[toklen] = '\0';
					(void)strcpy(lbuf, line);
					lbuf[strlen(lbuf) - 1] = '\0';
					pfnote(tok,lineno);
					in_rule = YES;
E 7
				}
D 7
				break;
E 7
I 7
				else
					sp--;
E 7
			}
I 7
			break;
E 8
I 8
			rewind(inf);
E 8
		}
E 7
D 8
}

char *
toss_comment(start)
D 7
char	*start;
E 7
I 7
	char	*start;
E 7
{
	register char	*sp;

	/*
	 * first, see if the end-of-comment is on the same line
	 */
	do {
D 7
		while ((sp = index(start, '*')) != NULL)
E 7
I 7
		while ((sp = index(start,'*')))
E 7
			if (sp[1] == '/')
D 7
				return ++sp;
E 7
I 7
				return(++sp);
E 7
			else
				start = ++sp;
		start = line;
		lineno++;
D 7
	} while (fgets(line, sizeof line, inf) != NULL);
E 7
I 7
	} while(fgets(line,sizeof(line),inf));
E 7
}

I 7
/*
 * getline --
 *	get the line the token of interest occurred on
 */
E 7
E 6
D 2
/*
 *	This routine adds a function to the list
 */
add_func(token)
char *token;
E 2
I 2
getline()
E 2
{
D 2
	reg	char	*fp,*pp;
	reg	NODE	*np;
E 2
I 2
D 7
	long saveftell = ftell( inf );
	register char *cp;
E 7
I 7
	register char	*cp;
	long	saveftell;
E 7
E 2

D 2
	if ((np = (NODE *) calloc(1,sizeof (NODE))) == NULL) {
		printf("too many functions to sort\n");
		put_funcs(head);
		free_tree(head);
		head = np = (NODE *) calloc(1,sizeof (NODE));
	}
	if (strcmp(token,"main") == 0) {
		/*
		 * Since there are so many directories with lots of
		 * misc. complete programs in them, main tends to get
		 * redefined a lot. So we change all mains to instead
		 * refer to the name of the file, without leading
		 * pathname components and without a trailing .c.
		 */
		fp = curfile;
		for (pp=curfile; *pp; pp++)
			if (*pp == '/')
				fp = pp+1;
		*token = 'M';
		strcpy(token+1, fp);
		pp = &token[strlen(token)-2];
		if (*pp == '.')
			*pp = 0;
	}
	fp = np->func = (char *) calloc(strlen(token)+1,sizeof (char));
	np->file = curfile;
	strcpy(fp, token);
	{	/*
		 * this change to make the whole line the pattern
		 */
	    long	saveftell = ftell( inf );
	    int		patlen;
	    char	ch;

	    patlen = 0;
	    fseek( inf , lineftell , 0 );
#ifdef DEBUG
	    printf("saveftell=%ld, lseek back to %ld\n",saveftell,lineftell);
#endif
	    ch = getc( inf );
	    while ( ch != '\n' && ch != searchar && patlen < MAXPATTERN ) {
		patlen ++;
		ch = getc( inf );
	    }
	    pp = np -> pat = (char *) calloc( patlen + 2 , sizeof( char ) );
	    fseek( inf , lineftell , 0 );
	    ch = getc( inf );
	    while ( patlen -- ) {
		*pp ++ = ch;
		ch = getc( inf );
	    }
	    if ( ch == '\n' )
		*pp ++ = '$';
	    *pp = '\0';
	    fseek( inf , saveftell , 0 );
#ifdef DEBUG
	    printf("seek back to %ld, ftell is now %ld\n",saveftell,ftell(inf));
#endif
	}
#ifdef DEBUG
	printf("\"%s\"\t\"%s\"\t\"%s\"\n",np->func,np->file,np->pat);
#endif
	if (head == NULL)
		head = np;
	else
		add_node(np,head);
E 2
I 2
D 7
	fseek( inf , lineftell , 0 );
	fgets(lbuf, sizeof lbuf, inf);
	cp = rindex(lbuf, '\n');
	if (cp)
		*cp = 0;
	fseek(inf, saveftell, 0);
E 7
I 7
	saveftell = ftell(inf);
	fseek(inf,lineftell,L_SET);
	(void)fgets(lbuf,sizeof(lbuf),inf);
	if (cp = index(lbuf,'\n'))
		*cp = '\0';
	fseek(inf,saveftell,L_SET);
E 7
E 2
}

D 2
/*
 *	This routine cfrees the entire tree from the node down.
 */
E 2
free_tree(node)
D 7
NODE	*node;
E 7
I 7
	register NODE	*node;
E 7
{
D 7

E 7
	while (node) {
		free_tree(node->right);
		cfree(node);
		node = node->left;
E 8
	}
D 8
}

D 2
/*
 *	This routine finds the node where the new function node
 * should be added.
 */
add_node(node,cur_node)
NODE	*node,*cur_node;
E 2
I 2
D 7
add_node(node, cur_node)
	NODE *node,*cur_node;
E 7
I 7
add_node(node,cur_node)
	register NODE	*node,
			*cur_node;
E 7
E 2
{
I 2
D 7
	register int dif;
E 7
I 7
	register int	dif;
E 7
E 2

D 2
	reg	int	dif;

E 2
D 4
	dif = strcmp(node->func,cur_node->func);
E 4
I 4
D 7
	dif = strcmp(node->entry, cur_node->entry);
E 4
D 2
#ifdef DEBUG
	printf("strcmp(\"%s\",\"%s\") == %d\n",node->func,cur_node->func,dif);
#endif
E 2
	if (dif == 0) {
E 7
I 7
	dif = strcmp(node->entry,cur_node->entry);
	if (!dif) {
E 7
		if (node->file == cur_node->file) {
D 7
			if (!wflag) {
D 2
				fprintf(stderr,"Duplicate function in file \"%s\", line %d: %s\n",node->file,lineno,node->func);
				fprintf(stderr,"Second entry ignored\n");
E 2
I 2
D 4
fprintf(stderr,"Duplicate function in file %s, line %d: %s\n",
    node->file,lineno,node->func);
E 4
I 4
fprintf(stderr,"Duplicate entry in file %s, line %d: %s\n",
    node->file,lineno,node->entry);
E 4
fprintf(stderr,"Second entry ignored\n");
E 2
			}
E 7
I 7
			if (!wflag)
				fprintf(stderr,"Duplicate entry in file %s, line %d: %s\nSecond entry ignored\n",node->file,lineno,node->entry);
E 7
			return;
		}
D 2
		else {
			if (!cur_node->been_warned)
				if (!wflag)
					fprintf(stderr,"Duplicate function name in files %s and %s: %s (Warning only)\n",
						node->file, cur_node->file, node->func);
			cur_node->been_warned = TRUE;
		}
	}
	if (dif < 0)
E 2
I 2
		if (!cur_node->been_warned)
			if (!wflag)
D 4
fprintf(stderr,"Duplicate function in files %s and %s: %s (Warning only)\n",
    node->file, cur_node->file, node->func);
E 4
I 4
D 7
fprintf(stderr,"Duplicate entry in files %s and %s: %s (Warning only)\n",
    node->file, cur_node->file, node->entry);
E 4
		cur_node->been_warned = TRUE;
		return;
E 7
I 7
				fprintf(stderr,"Duplicate entry in files %s and %s: %s (Warning only)\n",node->file,cur_node->file,node->entry);
		cur_node->been_warned = YES;
E 7
D 6
	} 
E 6
I 6
	}
D 7

E 6
	if (dif < 0) {
E 2
		if (cur_node->left != NULL)
E 7
I 7
	else if (dif < 0)
		if (cur_node->left)
E 7
			add_node(node,cur_node->left);
D 2
		else {
#ifdef DEBUG
			printf("adding to left branch\n");
#endif
E 2
I 2
		else
E 2
			cur_node->left = node;
D 2
		}
E 2
I 2
D 7
		return;
	}
	if (cur_node->right != NULL)
E 7
I 7
	else if (cur_node->right)
E 7
		add_node(node,cur_node->right);
E 2
	else
D 2
		if (cur_node->right != NULL)
			add_node(node,cur_node->right);
		else {
#ifdef DEBUG
			printf("adding to right branch\n");
#endif
			cur_node->right = node;
		}
E 2
I 2
		cur_node->right = node;
E 2
}

I 7
/*
 * put_entries --
 *	write out the tags
 */
E 7
D 2
/*
 *	This routine puts the functions in the file.
 */
E 2
D 4
put_funcs(node)
E 4
I 4
put_entries(node)
E 4
D 2
NODE	*node;
E 2
I 2
D 7
reg NODE	*node;
E 7
I 7
	register NODE	*node;
E 7
E 2
{
I 2
D 7
	reg char	*sp;
E 7
I 7
	register char	*sp;
E 7
E 2

D 7
	if (node == NULL)
E 7
I 7
	if (!node)
E 7
		return;
D 4
	put_funcs(node->left);
D 2
	fprintf(outf,"%s\t%s\t%c^%s%c\n",node->func,node->file
	       ,searchar,node->pat,searchar);
E 2
I 2
	if (xflag == 0) {
		fprintf(outf, "%s\t%s\t%c^", node->func, node->file ,searchar);
		for (sp = node->pat; *sp; sp++)
			if (*sp == '\\')
				fprintf(outf, "\\\\");
			else
				putc(*sp, outf);
		fprintf(outf, "%c\n", searchar);
	}
E 4
I 4
	put_entries(node->left);
D 7
	if (xflag == 0)
		if (node->f) {		/* a function */
			fprintf(outf, "%s\t%s\t%c^",
				node->entry, node->file, searchar);
			for (sp = node->pat; *sp; sp++)
				if (*sp == '\\')
					fprintf(outf, "\\\\");
				else if (*sp == searchar)
					fprintf(outf, "\\%c", searchar);
				else
					putc(*sp, outf);
			fprintf(outf, "%c\n", searchar);
D 6
		} else {		/* a typedef; text pattern inadequate */
E 6
I 6
		}
		else {		/* a typedef; text pattern inadequate */
E 6
			fprintf(outf, "%s\t%s\t%d\n",
				node->entry, node->file, node->lno);
		}
E 7
I 7
	if (!xflag) {
		fprintf(outf,"%s\t%s\t%c^",node->entry,node->file,searchar);
		for (sp = node->pat; *sp; sp++)
			if (*sp == '\\')
				fputs("\\\\",outf);
			else if (*sp == searchar)
				fprintf(outf,"\\%c",searchar);
			else
				putc(*sp,outf);
		fprintf(outf,"%c\n",searchar);
	}
E 7
E 4
I 3
	else if (vflag)
D 4
		fprintf(stdout, "%s %s %d\n", node->func, node->file, (node->lno+63)/64);
E 4
I 4
D 7
		fprintf(stdout, "%s %s %d\n",
				node->entry, node->file, (node->lno+63)/64);
E 7
I 7
		printf("%s %s %d\n",node->entry,node->file,(node->lno+63)/64);
E 7
E 4
E 3
	else
D 7
		fprintf(stdout, "%-16s%4d %-16s %s\n",
D 4
		    node->func, node->lno, node->file, node->pat);
E 2
	put_funcs(node->right);
E 4
I 4
			node->entry, node->lno, node->file, node->pat);
E 7
I 7
		printf("%-16s%4d %-16s %s\n",node->entry,node->lno,node->file,node->pat);
E 7
	put_entries(node->right);
E 4
}
I 7

E 7
D 6

E 6
D 2
#ifdef DEBUG
char *
unctrl(c)
char c;
E 2
I 2
char	*dbp = lbuf;
int	pfcnt;

D 7
PF_funcs(fi)
	FILE *fi;
E 7
I 7
PF_funcs()
E 7
E 2
{
D 2
	static char buf[3];
	if (c>=' ' && c<='~') {
		buf[0] = c;
		buf[1] = 0;
	} else if (c > '~') {
		buf[0] = '^';
		buf[1] = '?';
		buf[2] = 0;
	} else if (c < 0) {
		buf[0] = buf[1] = '?';
		buf[2] = 0;
	} else {
		buf[0] = '\\';
		buf[2] = 0;
		switch(c) {
		case '\b':
			buf[1] = 'b';
E 2
I 2
D 7

E 7
D 6
	lineno = 0;
E 6
	pfcnt = 0;
D 7
	while (fgets(lbuf, sizeof(lbuf), fi)) {
E 7
I 7
	while (fgets(lbuf, sizeof(lbuf), inf)) {
E 7
		lineno++;
		dbp = lbuf;
		if ( *dbp == '%' ) dbp++ ;	/* Ratfor escape to fortran */
		while (isspace(*dbp))
			dbp++;
		if (*dbp == 0)
			continue;
		switch (*dbp |' ') {

D 6
		case 'i':
E 6
I 6
		  case 'i':
E 6
			if (tail("integer"))
				takeprec();
E 2
			break;
D 2
		case '\t':
			buf[1] = 't';
E 2
I 2
D 6
		case 'r':
E 6
I 6
		  case 'r':
E 6
			if (tail("real"))
				takeprec();
E 2
			break;
D 2
		case '\n':
			buf[1] = 'n';
E 2
I 2
D 6
		case 'l':
E 6
I 6
		  case 'l':
E 6
			if (tail("logical"))
				takeprec();
E 2
			break;
D 2
		default:
			buf[0] = '^';
			buf[1] = c + 64;
E 2
I 2
D 6
		case 'c':
E 6
I 6
		  case 'c':
E 6
			if (tail("complex") || tail("character"))
				takeprec();
			break;
D 6
		case 'd':
E 6
I 6
		  case 'd':
E 6
			if (tail("double")) {
				while (isspace(*dbp))
					dbp++;
				if (*dbp == 0)
					continue;
				if (tail("precision"))
					break;
				continue;
			}
			break;
E 2
		}
I 2
		while (isspace(*dbp))
			dbp++;
		if (*dbp == 0)
			continue;
		switch (*dbp|' ') {

D 6
		case 'f':
E 6
I 6
		  case 'f':
E 6
			if (tail("function"))
				getit();
			continue;
D 6
		case 's':
E 6
I 6
		  case 's':
E 6
			if (tail("subroutine"))
				getit();
			continue;
D 6
		case 'p':
E 6
I 6
		  case 'p':
E 6
			if (tail("program")) {
				getit();
				continue;
			}
			if (tail("procedure"))
				getit();
			continue;
		}
E 2
	}
D 2
	return(buf);
E 2
I 2
	return (pfcnt);
E 2
}
D 2
#endif
E 2
I 2

tail(cp)
	char *cp;
{
	register int len = 0;

	while (*cp && (*cp&~' ') == ((*(dbp+len))&~' '))
		cp++, len++;
	if (*cp == 0) {
		dbp += len;
		return (1);
	}
	return (0);
}

takeprec()
{
D 7

E 7
	while (isspace(*dbp))
		dbp++;
	if (*dbp != '*')
		return;
	dbp++;
	while (isspace(*dbp))
		dbp++;
	if (!isdigit(*dbp)) {
		--dbp;		/* force failure */
		return;
	}
	do
		dbp++;
	while (isdigit(*dbp));
}

getit()
{
	register char *cp;
	char c;
D 7
	char nambuf[BUFSIZ];
E 7
I 7
	char	nambuf[BUFSIZ];
E 7

	for (cp = lbuf; *cp; cp++)
		;
	*--cp = 0;	/* zap newline */
	while (isspace(*dbp))
		dbp++;
	if (*dbp == 0 || !isalpha(*dbp))
		return;
	for (cp = dbp+1; *cp && (isalpha(*cp) || isdigit(*cp)); cp++)
		continue;
	c = cp[0];
	cp[0] = 0;
D 7
	strcpy(nambuf, dbp);
E 7
I 7
	(void)strcpy(nambuf, dbp);
E 7
	cp[0] = c;
D 4
	pfnote(nambuf, lineno);
E 4
I 4
D 5
	pfnote(nambuf, lineno, FALSE);
E 5
I 5
	pfnote(nambuf, lineno);
E 5
E 4
	pfcnt++;
}

char *
D 7
savestr(cp)
	char *cp;
E 7
I 7
savestr(str)
	char	*str;
E 7
{
D 7
	register int len;
	register char *dp;
E 7
I 7
	register char	*space;
	char	*malloc();
E 7

D 7
	len = strlen(cp);
	dp = (char *)malloc(len+1);
	strcpy(dp, cp);
	return (dp);
E 7
I 7
	if (!(space = malloc((u_int)(strlen(str) + 1)))) {
		fputs("ctags: no more space.\n",stderr);
		exit(1);
	}
	return(strcpy(space,str));
E 7
}

/*
D 7
 * Return the ptr in sp at which the character c last
 * appears; NULL if not found
 *
 * Identical to v7 rindex, included for portability.
 */

char *
rindex(sp, c)
register char *sp, c;
{
	register char *r;

	r = NULL;
	do {
		if (*sp == c)
			r = sp;
	} while (*sp++);
	return(r);
I 5
}

/*
E 7
 * lisp tag functions
 * just look for (def or (DEF
 */
D 7

L_funcs (fi)
FILE *fi;
E 7
I 7
L_funcs()
E 7
{
D 6
	lineno = 0;
E 6
I 6
	register int	special;

E 6
	pfcnt = 0;
D 7
	while (fgets(lbuf, sizeof(lbuf), fi)) {
E 7
I 7
	while (fgets(lbuf, sizeof(lbuf), inf)) {
E 7
		lineno++;
		dbp = lbuf;
D 6
		if (dbp[0] == '(' && 
		     (dbp[1] == 'D' || dbp[1] == 'd') &&
		     (dbp[2] == 'E' || dbp[2] == 'e') &&
		     (dbp[3] == 'F' || dbp[3] == 'f')) {
		   while (!isspace(*dbp)) dbp++;
		   while (isspace(*dbp)) dbp++;
		   L_getit();
		   }
E 6
I 6
		if (dbp[0] == '(' &&
D 7
		    (dbp[1] == 'D' || dbp[1] == 'd') &&
		    (dbp[2] == 'E' || dbp[2] == 'e') &&
		    (dbp[3] == 'F' || dbp[3] == 'f')) {
E 7
I 7
		   (dbp[1] == 'D' || dbp[1] == 'd') &&
		   (dbp[2] == 'E' || dbp[2] == 'e') &&
		   (dbp[3] == 'F' || dbp[3] == 'f')) {
E 7
			dbp += 4;
			if (striccmp(dbp, "method") == 0 ||
			    striccmp(dbp, "wrapper") == 0 ||
			    striccmp(dbp, "whopper") == 0)
D 7
				special = TRUE;
E 7
I 7
				special = YES;
E 7
			else
D 7
				special = FALSE;
E 7
I 7
				special = NO;
E 7
			while (!isspace(*dbp))
D 7
				dbp++;
E 7
I 7
				++dbp;
E 7
			while (isspace(*dbp))
D 7
				dbp++;
E 7
I 7
				++dbp;
E 7
			L_getit(special);
E 6
		}
	}
I 6
}
E 6

D 6
L_getit()
E 6
I 6
L_getit(special)
D 7
int	special;
E 7
I 7
	int	special;
E 7
E 6
{
D 6
	register char *cp;
	char c;
	char nambuf[BUFSIZ];
E 6
I 6
D 7
	register char	*cp;
	register char	c;
	char		nambuf[BUFSIZ];
E 7
I 7
	register char	*cp,
			c;
	char	nambuf[BUFSIZ];
E 7
E 6

D 6
	for (cp = lbuf; *cp; cp++) ;
E 6
I 6
D 7
	for (cp = lbuf; *cp; cp++)
		continue;
E 7
I 7
	for (cp = lbuf;*cp;cp++);
E 7
E 6
	*--cp = 0;		/* zap newline */
D 6
	if (*dbp == 0) return;
	for (cp = dbp+1; *cp && *cp != '(' && *cp != ' '; cp++)
	        continue;
E 6
I 6
D 7
	if (*dbp == 0)
E 7
I 7
	if (!*dbp)
E 7
		return;
	if (special) {
D 7
		if ((cp = index(dbp, ')')) == NULL)
E 7
I 7
		if (!(cp = index(dbp,')')))
E 7
			return;
D 7
		while (cp >= dbp && *cp != ':')
			cp--;
E 7
I 7
		for (;cp >= dbp && *cp != ':';--cp);
E 7
		if (cp < dbp)
			return;
		dbp = cp;
D 7
		while (*cp && *cp != ')' && *cp != ' ')
			cp++;
E 7
I 7
		for (;*cp && *cp != ')' && *cp != ' ';++cp);
E 7
	}
	else
D 7
		for (cp = dbp + 1; *cp && *cp != '(' && *cp != ' '; cp++)
			continue;
E 7
I 7
		for (cp = dbp + 1; *cp && *cp != '(' && *cp != ' '; cp++);
E 7
E 6
	c = cp[0];
	cp[0] = 0;
D 7
	strcpy(nambuf, dbp);
E 7
I 7
	(void)strcpy(nambuf,dbp);
E 7
	cp[0] = c;
D 7
	pfnote(nambuf, lineno,TRUE);
	pfcnt++;
E 7
I 7
	pfnote(nambuf,lineno);
	++pfcnt;
E 7
E 5
}
I 6

/*
 * striccmp:
 *	Compare two strings over the length of the second, ignoring
 *	case distinctions.  If they are the same, return 0.  If they
 *	are different, return the difference of the first two different
 *	characters.  It is assumed that the pattern (second string) is
 *	completely lower case.
 */
striccmp(str, pat)
D 7
register char	*str, *pat;
E 7
I 7
	register char	*str, *pat;
E 7
{
	register int	c1;

	while (*pat) {
		if (isupper(*str))
			c1 = tolower(*str);
		else
			c1 = *str;
		if (c1 != *pat)
			return c1 - *pat;
		pat++;
		str++;
	}
	return 0;
}

/*
D 7
 * first_char:
 *	Return the first non-blank character in the file.  After
 *	finding it, rewind the input file so we start at the beginning
 *	again.
E 7
I 7
 * first_char --
 *	return the next non-blank character in the file.  After finding
 *	it, rewind the input file to the starting position.
E 7
 */
first_char()
{
	register int	c;
	register long	off;

	off = ftell(inf);
	while ((c = getc(inf)) != EOF)
D 7
		if (!isspace(c) && c != '\r') {
			fseek(inf, off, 0);
			return c;
E 7
I 7
		if (!iswhite(c)) {
			(void)fseek(inf,off,L_SET);
			return(c);
E 7
		}
D 7
	fseek(inf, off, 0);
	return EOF;
E 7
I 7
	(void)fseek(inf,off,L_SET);
	return(EOF);
E 7
}

/*
D 7
 * toss_yysec:
 *	Toss away code until the next "%%" line.
E 7
I 7
 * toss_yysec --
 *	toss away code until the next "%%" line.
E 7
 */
toss_yysec()
{
D 7
	char		buf[BUFSIZ];
E 7
I 7
	char	buf[BUFSIZ];
E 7

	for (;;) {
		lineftell = ftell(inf);
D 7
		if (fgets(buf, BUFSIZ, inf) == NULL)
E 7
I 7
		if (!fgets(buf,sizeof(buf),inf))
E 7
			return;
D 7
		lineno++;
		if (strncmp(buf, "%%", 2) == 0)
E 7
I 7
		++lineno;
		if (!strncmp(buf,"%%",2))
E 7
			return;
	}
E 8
I 8
/* C */	c_entries();
E 8
}
D 7

E 7
E 6
E 2
E 1
