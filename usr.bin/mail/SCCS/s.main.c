h47679
s 00012/00006/00264
d D 8.2 95/04/20 09:59:21 dab 50 49
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00005/00005/00265
d D 8.1 93/06/06 15:08:13 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00005/00262
d D 5.29 92/06/26 12:03:19 bostic 48 47
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00003/00002/00264
d D 5.28 91/04/01 08:59:17 bostic 47 46
c ANSI
e
s 00001/00001/00265
d D 5.27 90/06/25 00:01:42 edward 46 45
c remove call of _fwalk
e
s 00001/00011/00265
d D 5.26 90/06/01 16:59:29 bostic 45 44
c new copyright notice
e
s 00002/00001/00274
d D 5.25 89/11/24 23:07:16 edward 44 43
c sig_t
e
s 00001/00001/00274
d D 5.24 89/05/19 18:22:38 bostic 43 42
c gtty and utime are in compatibility library now
e
s 00001/00001/00274
d D 5.23 89/05/11 09:44:14 bostic 42 41
c file reorg, pathnames.h, paths.h
e
s 00002/00009/00273
d D 5.22 89/02/13 23:51:56 edward 41 40
c more accurate error message when editing system mailbox
e
s 00000/00002/00282
d D 5.21 89/01/27 09:02:49 bostic 40 39
c remove TIOCGWINSZ #ifdef's
e
s 00009/00018/00275
d D 5.20 89/01/16 01:34:24 edward 39 38
c don't catch SIGCONT, catch the stop signals instead,
c cleaned up quitting of mail and signal catch in general,
c could use more work
e
s 00005/00001/00288
d D 5.19 88/08/17 14:23:43 edward 38 37
c don't need to keep the name of mailrc around
e
s 00004/00002/00285
d D 5.18 88/07/08 01:43:28 edward 37 36
c rationalized handling of child processes, cleaned up mail1 some more
e
s 00003/00002/00284
d D 5.17 88/07/07 06:55:18 edward 36 35
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00014/00009/00272
d D 5.16 88/06/29 21:01:55 bostic 35 34
c install approved copyright notice
e
s 00017/00026/00264
d D 5.15 88/06/19 04:21:05 edward 34 33
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00007/00043/00283
d D 5.14 88/06/18 14:54:30 edward 33 32
c removed support for -r, -h, and rmail
e
s 00006/00004/00320
d D 5.13 88/06/17 15:38:55 edward 32 31
c some general cleanup
e
s 00010/00017/00314
d D 5.12 88/06/17 15:05:11 edward 31 30
c cleaned up file handling code, now allows "mbox" variable
e
s 00005/00007/00326
d D 5.11 88/06/16 21:50:33 edward 30 29
c replaced intty and outtty by value("interactive"), ~ only in interactive mode
e
s 00012/00017/00321
d D 5.10 88/06/16 19:23:06 edward 29 28
c let "crt" default to the screen height from TIOCGWINSZ
e
s 00000/00003/00338
d D 5.9 88/06/16 17:41:20 edward 28 27
c prehistoric (e.g., pre-sendmail) code removed
e
s 00009/00011/00332
d D 5.8 88/06/11 03:32:30 edward 27 26
c changed the way -N is handled
e
s 00006/00001/00337
d D 5.7 88/06/11 03:31:10 edward 26 25
c real usage message
e
s 00052/00071/00286
d D 5.6 88/06/11 01:15:54 edward 25 24
c added -c -b -t flags, end echo with newline,
c from Tom Newcomb (newcomb@arpa)
e
s 00014/00008/00343
d D 5.5 88/02/18 17:04:07 bostic 24 23
c written by Kurt Shoens; added Berkeley specific header
e
s 00046/00021/00305
d D 5.4 87/05/18 12:28:14 edward 23 22
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00003/00325
d D 5.3 85/09/15 16:58:12 serge 22 21
c always print headers of first few messages when editing different file
e
s 00002/00002/00326
d D 5.2 85/06/21 17:12:19 mckusick 21 20
c botched copyright
e
s 00014/00002/00314
d D 5.1 85/06/06 10:37:28 dist 20 19
c Add copyright
e
s 00008/00001/00308
d D 2.15 85/05/27 15:02:19 serge 19 18
c Added -I flag, which causes Mail to assume that input is a tty
e
s 00001/00002/00308
d D 2.14 84/08/08 17:05:47 ralph 18 17
c fix stdio flushing, don't mess with stdio buffers
e
s 00000/00002/00310
d D 2.13 84/07/19 15:42:49 ralph 17 16
c use flock for mailbox locking
e
s 00003/00003/00309
d D 2.12 83/08/11 22:17:48 sam 16 15
c standardize sccs keyword lines
e
s 00000/00001/00312
d D 2.11 83/06/12 11:16:43 sam 15 14
c new signals
e
s 00008/00001/00305
d D 2.10 83/01/22 15:22:37 leres 14 13
c Added (restored?) missing required argument in call to announce() so that
c initial greeting is printed (unless "quiet" is set.) Added verbose
c command/option.
e
s 00003/00000/00303
d D 2.9 82/09/02 12:34:28 mckusick 13 12
c added call to inithost() if GETHOST is defined
e
s 00006/00001/00297
d D 2.8 82/07/28 15:35:54 kurt 12 11
c changed to print own error message if setfile fails 
c 
e
s 00002/00001/00296
d D 2.7 82/06/24 23:53:28 kurt 11 10
c made handling of "mailname" global variable simpler -- now it 
c is an array of chars rather than a pointer that used to get set to a small 
c calloc'd space that would get clobbered if you changed to a longer name. 
c 
e
s 00006/00001/00291
d D 2.6 82/02/26 08:01:49 kurt 10 9
c changed the -T flag to close(creat()) the file at the beginning 
c in case you user x's from Mail so readnews won't be upset. 
c 
e
s 00040/00011/00252
d D 2.5 82/02/13 14:49:35 kurt 9 8
c changed to load user's .mailrc before figuring out file 
c from -f so we can interpret +name.  Header printing now invoked by 
c main() with special escape to be able to ^C it. 
c 
e
s 00007/00000/00256
d D 2.4 81/12/10 12:54:37 kurt 8 7
c changed to set global "baud" to the output rate code from gtty 
c 
e
s 00005/00000/00251
d D 2.3 81/09/22 08:44:36 kurt 7 6
c changed start up code to exit if there are 0 messages and 
c we are not in edit mode 
c 
e
s 00013/00000/00238
d D 2.2 81/07/20 17:06:58 kurt 6 5
c changed to notice a flag of the form -T filename so that netnews can
c discover which articles were read or deleted
e
s 00000/00000/00238
d D 2.1 81/07/01 11:09:49 kurt 5 4
c Release to Heidi Stettner
e
s 00005/00001/00233
d D 1.4 81/04/01 12:57:48 kurt 4 3
c changed to ignore tty signals when about to quit
e
s 00007/00000/00227
d D 1.3 81/02/06 09:40:38 kas 3 2
c added -N flag to suppress header printing
e
s 00002/00047/00225
d D 1.2 80/10/09 13:39:52 kas 2 1
c changed to call setfile/lex.c to set up initial input file.
e
s 00272/00000/00000
d D 1.1 80/10/08 09:50:49 kas 1 0
c date and time created 80/10/08 09:50:49 by kas
e
u
U
f b 
t
T
I 20
/*
D 49
 * Copyright (c) 1980 Regents of the University of California.
D 24
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 24
I 24
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 49
 *
D 45
 * Redistribution and use in source and binary forms are permitted
D 35
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 35
I 35
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
E 45
I 45
 * %sccs.include.redist.c%
E 45
E 35
E 24
 */

E 20
I 1
D 16
#
E 16
I 16
D 24
#ifndef lint
D 19
static char sccsid[] = "%W% (Berkeley) %G%";
E 19
I 19
D 20
static char *sccsid = "%W% (Berkeley) %G%";
E 19
#endif
E 20
I 20
D 21
char copyright[] =
E 21
I 21
char *copyright =
E 24
I 24
D 35
#ifdef notdef
E 35
I 35
#ifndef lint
E 35
D 49
char copyright[] =
E 24
E 21
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 49
I 49
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 49
D 24
#endif not lint
E 24
I 24
D 35
#endif /* notdef */
E 35
I 35
#endif /* not lint */
E 35
E 24

D 24
#ifndef lint
D 21
static char sccsid[] = "%W% (Berkeley) %G%";
E 21
I 21
static char *sccsid = "%W% (Berkeley) %G%";
E 21
#endif not lint
E 24
I 24
D 35
#ifdef notdef
E 35
I 35
#ifndef lint
E 35
static char sccsid[] = "%W% (Berkeley) %G%";
D 35
#endif /* notdef */
E 35
I 35
#endif /* not lint */
E 35
E 24
E 20
E 16

#include "rcv.h"
D 48
#include <sys/stat.h>
E 48
I 48
#include <fcntl.h>
#include "extern.h"
E 48

/*
 * Mail -- a mail program
 *
 * Startup -- interface with user.
 */
D 16

static char *SccsId = "%W% %G%";
E 16

I 9
jmp_buf	hdrjmp;

I 48
int
E 48
E 9
D 33
/*
 * Find out who the user is, copy his mail file (if exists) into
 * /tmp/Rxxxxx and set up the message pointers.  Then, print out the
 * message headers and read user commands.
 *
 * Command line syntax:
 *	Mail [ -i ] [ -r address ] [ -h number ] [ -f [ name ] ]
 * or:
 *	Mail [ -i ] [ -r address ] [ -h number ] people ...
 */

E 33
main(argc, argv)
D 48
	char **argv;
E 48
I 48
	int argc;
	char *argv[];
E 48
{
D 25
	register char *ef;
	register int i, argp;
D 9
	int mustsend, uflag;
E 9
I 9
D 10
	int mustsend, uflag, hdrstop(), (*prevint)();
E 10
I 10
D 23
	int mustsend, uflag, hdrstop(), (*prevint)(), f;
E 10
E 9
	FILE *ibuf, *ftat;
E 23
I 23
	int mustsend, hdrstop(), (*prevint)(), f;
E 25
I 25
D 33
	register char *ef, opt;
E 33
I 33
D 34
	register char *ef;
E 34
E 33
	register int i;
	struct name *to, *cc, *bcc, *smopts;
D 31
	int  mustsend, hdrstop(), (*prevint)(), f;
E 31
I 31
D 33
	int mustsend, hdrstop(), (*prevint)(), f;
E 33
I 33
D 34
	int mustsend, hdrstop(), (*prevint)();
E 34
I 34
	char *subject;
	char *ef;
I 36
	char nosrc = 0;
I 39
D 41
	char isedit = 0;
E 41
E 39
E 36
D 44
	int hdrstop(), (*prevint)();
E 44
I 44
D 47
	int hdrstop();
E 47
I 47
	void hdrstop();
E 47
	sig_t prevint;
E 44
I 37
D 47
	int sigchild();
E 47
E 37
E 34
E 33
E 31
E 25
E 23
D 2
	extern char tempMesg[], _sobuf[];
E 2
I 2
D 17
	extern char _sobuf[];
E 17
I 8
D 29
	struct sgttyb tbuf;
E 29
I 25
D 48
	extern int getopt(), optind, opterr;
	extern char *optarg;
E 48
I 47
	void sigchild();
I 50
	char *rc;
E 50
E 47
E 25
E 8
E 2

D 23
#ifdef signal
	Siginit();
#endif

E 23
	/*
D 23
	 * Set up a reasonable environment.  We clobber the last
	 * element of argument list for compatibility with version 6,
	 * figure out whether we are being run interactively, set up
E 23
I 23
	 * Set up a reasonable environment.
D 37
	 * Figure out whether we are being run interactively, set up
E 23
	 * all the temporary files, buffer standard output, and so forth.
E 37
I 37
	 * Figure out whether we are being run interactively,
	 * start the SIGCHLD catcher, and so forth.
E 37
	 */
I 37
	(void) signal(SIGCHLD, sigchild);
E 37
D 32

E 32
D 23
	uflag = 0;
	argv[argc] = (char *) -1;
E 23
I 13
D 28
#ifdef	GETHOST
	inithost();
#endif	GETHOST
E 28
E 13
D 36
	mypid = getpid();
E 36
D 30
	intty = isatty(0);
	outtty = isatty(1);
E 30
I 30
	if (isatty(0))
		assign("interactive", "");
E 30
I 8
D 29
	if (outtty) {
		gtty(1, &tbuf);
		baud = tbuf.sg_ospeed;
D 23
	}
	else
E 23
I 23
	} else
E 23
		baud = B9600;
E 29
E 8
	image = -1;
D 17
	setbuf(stdout, _sobuf);
E 17
D 32

E 32
	/*
	 * Now, determine how we are being used.
D 33
	 * We successively pick off instances of -r, -h, -f, and -i.
	 * If called as "rmail" we note this fact for letter sending.
E 33
I 33
	 * We successively pick off - flags.
E 33
	 * If there is anything left, it is the base of the list
	 * of users to mail to.  Argp will be set to point to the
	 * first of these users.
	 */
D 32

E 32
	ef = NOSTR;
D 25
	argp = -1;
E 25
I 25
D 34
	to = NULL;
	cc = NULL;
	bcc = NULL;
	smopts = NULL;
E 25
	mustsend = 0;
E 34
I 34
	to = NIL;
	cc = NIL;
	bcc = NIL;
	smopts = NIL;
	subject = NOSTR;
E 34
D 33
	if (argc > 0 && **argv == 'r')
		rmail++;
D 25
	for (i = 1; i < argc; i++) {

		/*
		 * If current argument is not a flag, then the
		 * rest of the arguments must be recipients.
		 */

		if (*argv[i] != '-') {
			argp = i;
			break;
		}
		switch (argv[i][1]) {
E 25
I 25
	while ((opt = getopt(argc, argv, "INT:b:c:dfh:inr:s:u:v")) != EOF) {
		switch (opt) {
E 25
		case 'r':
			/*
			 * Next argument is address to be sent along
			 * to the mailer.
			 */
D 25
			if (i >= argc - 1) {
				fprintf(stderr, "Address required after -r\n");
				exit(1);
			}
E 25
			mustsend++;
D 25
			rflag = argv[i+1];
			i++;
E 25
I 25
			rflag = optarg;
E 25
			break;
E 33
I 33
	while ((i = getopt(argc, argv, "INT:b:c:dfins:u:v")) != EOF) {
		switch (i) {
E 33
D 25

E 25
I 6
		case 'T':
			/*
			 * Next argument is temp file to write which
			 * articles have been read/deleted for netnews.
			 */
D 25
			if (i >= argc - 1) {
				fprintf(stderr, "Name required after -T\n");
				exit(1);
			}
			Tflag = argv[i+1];
E 25
I 25
			Tflag = optarg;
E 25
I 10
D 33
			if ((f = creat(Tflag, 0600)) < 0) {
E 33
I 33
			if ((i = creat(Tflag, 0600)) < 0) {
E 33
				perror(Tflag);
				exit(1);
			}
D 33
			close(f);
E 33
I 33
			close(i);
E 33
E 10
D 25
			i++;
E 25
			break;
D 25

E 25
E 6
		case 'u':
			/*
			 * Next argument is person to pretend to be.
			 */
D 23
			uflag++;
E 23
D 25
			if (i >= argc - 1) {
D 9
				fprintf(stderr, "You obviously dont know what you're doing\n");
E 9
I 9
				fprintf(stderr, "Missing user name for -u\n");
E 9
				exit(1);
			}
			strcpy(myname, argv[i+1]);
			i++;
E 25
I 25
D 36
			strcpy(myname, optarg);
E 36
I 36
			myname = optarg;
E 36
E 25
			break;
D 25

E 25
		case 'i':
			/*
			 * User wants to ignore interrupts.
			 * Set the variable "ignore"
			 */
			assign("ignore", "");
			break;
D 25

E 25
		case 'd':
			debug++;
D 33
			break;
D 25

E 25
		case 'h':
			/*
			 * Specified sequence number for network.
			 * This is the number of "hops" made so
			 * far (count of times message has been
			 * forwarded) to help avoid infinite mail loops.
			 */
D 25
			if (i >= argc - 1) {
				fprintf(stderr, "Number required for -h\n");
				exit(1);
			}
E 25
			mustsend++;
D 25
			hflag = atoi(argv[i+1]);
E 25
I 25
			hflag = atoi(optarg);
E 25
			if (hflag == 0) {
				fprintf(stderr, "-h needs non-zero number\n");
				exit(1);
			}
E 33
D 25
			i++;
E 25
			break;
D 25

E 25
		case 's':
			/*
			 * Give a subject field for sending from
			 * non terminal
			 */
D 25
			if (i >= argc - 1) {
				fprintf(stderr, "Subject req'd for -s\n");
				exit(1);
			}
E 25
D 34
			mustsend++;
D 25
			sflag = argv[i+1];
			i++;
E 25
I 25
			sflag = optarg;
E 34
I 34
			subject = optarg;
E 34
E 25
			break;
D 25

E 25
		case 'f':
			/*
			 * User is specifying file to "edit" with Mail,
			 * as opposed to reading system mailbox.
			 * If no argument is given after -f, we read his
D 31
			 * mbox file in his home directory.
E 31
I 31
			 * mbox file.
E 31
I 25
			 *
			 * getopt() can't handle optional arguments, so here
			 * is an ugly hack to get around it.
E 25
			 */
D 25
			if (i >= argc - 1)
				ef = mbox;
E 25
I 25
D 27
			if ((argv[optind]) && (argv[optind][0] != '-')) 
E 27
I 27
			if ((argv[optind]) && (argv[optind][0] != '-'))
E 27
				ef = argv[optind++];
E 25
			else
D 25
				ef = argv[i + 1];
			i++;
E 25
I 25
D 31
				ef = mbox;
E 31
I 31
				ef = "&";
E 31
E 25
			break;
D 25

E 25
		case 'n':
			/*
			 * User doesn't want to source /usr/lib/Mail.rc
			 */
			nosrc++;
			break;
D 25

E 25
I 3
		case 'N':
			/*
			 * Avoid initial header printing.
			 */
D 27
			noheader++;
E 27
I 27
			assign("noheader", "");
E 27
			break;
D 25

E 25
I 14
		case 'v':
			/*
			 * Send mailer verbose flag
			 */
			assign("verbose", "");
I 19
			break;
D 25

E 25
		case 'I':
			/*
			 * We're interactive
			 */
D 30
			intty = 1;
E 30
I 30
			assign("interactive", "");
E 30
E 19
			break;
D 25

E 14
E 3
		default:
			fprintf(stderr, "Unknown flag: %s\n", argv[i]);
E 25
I 25
		case 'c':
			/*
			 * Get Carbon Copy Recipient list
			 */
D 34
			cc = cat(cc, nalloc(optarg));
			mustsend++;
E 34
I 34
			cc = cat(cc, nalloc(optarg, GCC));
E 34
			break;
		case 'b':
			/*
			 * Get Blind Carbon Copy Recipient list
			 */
D 34
			bcc = cat(bcc, nalloc(optarg));
			mustsend++;
E 34
I 34
			bcc = cat(bcc, nalloc(optarg, GBCC));
E 34
			break;
		case '?':
D 26
			fputs("Usage: XXX\n", stderr);
E 26
I 26
			fputs("\
Usage: mail [-iInv] [-s subject] [-c cc-addr] [-b bcc-addr] to-addr ...\n\
            [- sendmail-options ...]\n\
       mail [-iInNv] -f [name]\n\
       mail [-iInNv] [-u user]\n",
				stderr);
E 26
E 25
			exit(1);
		}
	}
D 25

E 25
I 25
D 27
	for (i = optind; (argv[i]) && (*argv[i] != '-'); i++) 
E 27
I 27
	for (i = optind; (argv[i]) && (*argv[i] != '-'); i++)
E 27
D 34
		to = cat(to, nalloc(argv[i]));
E 34
I 34
		to = cat(to, nalloc(argv[i], GTO));
E 34
	for (; argv[i]; i++)
D 34
		smopts = cat(smopts, nalloc(argv[i]));
E 34
I 34
		smopts = cat(smopts, nalloc(argv[i], 0));
E 34
E 25
	/*
	 * Check for inconsistent arguments.
	 */
D 25

D 9
	if (rflag != NOSTR && strcmp(rflag, "daemon") == 0) {
		ftat = fopen("/crp/kas/gotcha", "a");
		if (ftat != NULL) {
			fprintf(ftat, "user daemon, real uid %d\n", getuid());
			fclose(ftat);
		}
	}
E 9
	if (ef != NOSTR && argp != -1) {
E 25
I 25
D 34
	if (!to && (cc || bcc)) {
		fputs("You must also specify direct recipients of mail.\n", stderr);
E 34
I 34
	if (to == NIL && (subject != NOSTR || cc != NIL || bcc != NIL)) {
		fputs("You must specify direct recipients with -s, -c, or -b.\n", stderr);
E 34
		exit(1);
	}
D 34
	if ((ef != NOSTR) && to) {
E 34
I 34
	if (ef != NOSTR && to != NIL) {
E 34
E 25
		fprintf(stderr, "Cannot give -f and people to send to.\n");
		exit(1);
	}
D 25
	if (mustsend && argp == -1) {
E 25
I 25
D 34
	if (mustsend && !to) {
E 25
		fprintf(stderr, "The flags you gave make no sense since you're not sending mail.\n");
		exit(1);
	}
E 34
	tinit();
I 23
	setscreensize();
E 23
I 9
	input = stdin;
D 25
	rcvmode = argp == -1;
E 25
I 25
	rcvmode = !to;
I 36
	spreserve();
E 36
E 25
	if (!nosrc)
D 42
		load(MASTER);
E 42
I 42
		load(_PATH_MASTER_RC);
E 42
D 38
	load(mailrc);
E 38
I 38
	/*
	 * Expand returns a savestr, but load only uses the file name
D 46
	 * for fopen, so it's save to do this.
E 46
I 46
	 * for fopen, so it's safe to do this.
E 46
	 */
D 50
	load(expand("~/.mailrc"));
E 50
I 50
	if ((rc = getenv("MAILRC")) == 0)
		rc = "~/.mailrc";
	load(expand(rc));
E 50
E 38
E 9
D 25
	if (argp != -1) {
D 9
		commands();
E 9
		mail(&argv[argp]);
E 25
I 25
	if (!rcvmode) {
D 34
		mail(to, cc, bcc, smopts);
E 25

E 34
I 34
		mail(to, cc, bcc, smopts, subject);
E 34
		/*
		 * why wait?
		 */
D 34

E 34
		exit(senderr);
	}
D 34

E 34
	/*
	 * Ok, we are reading mail.
	 * Decide whether we are editing a mailbox or reading
	 * the system mailbox, and open up the right stuff.
	 */
D 31

D 9
	rcvmode++;
E 9
	if (ef != NOSTR) {
I 9
		char *ename;

E 31
I 31
D 41
	if (ef != NOSTR)
E 31
E 9
D 39
		edit++;
E 39
I 39
		isedit++;
E 39
I 9
D 31
		ename = expand(ef);
		if (ename != ef) {
D 23
			ef = (char *) calloc(1, strlen(ename) + 1);
E 23
I 23
			ef = malloc((unsigned) strlen(ename) + 1);
E 23
			strcpy(ef, ename);
		}
E 9
D 11
		editfile = mailname = ef;
E 11
I 11
		editfile = ef;
		strcpy(mailname, ef);
E 11
D 2
		if ((ibuf = fopen(mailname, "r")) == NULL) {
			perror(mailname);
			exit(1);
		}
		if ((i = open(mailname, 1)) < 0)
			printf("Warning: \"%s\" not writable.\n", mailname);
		else
			close(i);
E 2
	}
D 2
	else {
		if ((ibuf = fopen(mailname, "r")) == NULL) {
			if (uflag)
				printf("No mail for %s\n", myname);
			else
				printf("No mail.\n");
			exit(0);
		}
	}

	/*
	 * Copy the messages into /tmp
	 * and set pointers.
	 */

	mailsize = fsize(ibuf);
	if ((otf = fopen(tempMesg, "w")) == NULL) {
		perror(tempMesg);
E 2
I 2
D 12
	if (setfile(mailname, edit) < 0)
E 12
I 12
	if (setfile(mailname, edit) < 0) {
E 31
I 31
	else
E 41
I 41
	if (ef == NOSTR)
E 41
		ef = "%";
D 39
	if ((ef = expand(ef)) == NOSTR)
E 39
I 39
D 41
	if ((ef = expand(ef)) == NOSTR || setfile(ef, isedit) < 0)
E 41
I 41
	if (setfile(ef) < 0)
E 41
E 39
		exit(1);		/* error already reported */
D 39
	if (setfile(ef, edit) < 0) {
E 31
		if (edit)
D 31
			perror(mailname);
E 31
I 31
			perror(ef);
E 31
		else
			fprintf(stderr, "No mail for %s\n", myname);
E 39
I 39
D 41
	if (!edit && msgCount == 0) {
		fprintf(stderr, "No mail for %s\n", myname);
E 39
E 12
E 2
		exit(1);
I 12
	}
E 41
E 12
I 9
D 22
	if (!edit && !noheader && value("noheader") == NOSTR) {
E 22
I 22
D 27
	if (!noheader && value("noheader") == NOSTR) {
E 22
		if (setjmp(hdrjmp) == 0) {
D 23
			if ((prevint = sigset(SIGINT, SIG_IGN)) != SIG_IGN)
				sigset(SIGINT, hdrstop);
E 23
I 23
			if ((prevint = signal(SIGINT, SIG_IGN)) != SIG_IGN)
				signal(SIGINT, hdrstop);
E 23
D 14
			announce();
E 14
I 14
			announce(!0);
E 14
			fflush(stdout);
D 23
			sigset(SIGINT, prevint);
E 23
I 23
			signal(SIGINT, prevint);
E 23
		}
E 27
I 27
	if (setjmp(hdrjmp) == 0) {
I 32
		extern char *version;

E 32
		if ((prevint = signal(SIGINT, SIG_IGN)) != SIG_IGN)
			signal(SIGINT, hdrstop);
D 32
		announce(!0);
E 32
I 32
		if (value("quiet") == NOSTR)
			printf("Mail version %s.  Type ? for help.\n",
				version);
		announce();
E 32
		fflush(stdout);
		signal(SIGINT, prevint);
E 27
	}
D 22
	if (edit)
		newfileinfo();
E 22
E 9
I 7
D 39
	if (!edit && msgCount == 0) {
		printf("No mail\n");
		fflush(stdout);
		exit(0);
	}
E 39
E 7
D 2
	}
	if ((itf = fopen(tempMesg, "r")) == NULL) {
		perror(tempMesg);
		exit(1);
	}
	remove(tempMesg);
	setptr(ibuf);
	fclose(ibuf);

	/*
	 * print headings and accept user commands.
	 */

	if (msgCount == 0) {
		if (uflag)
			printf("No mail for %s\n", myname);
		else
			printf("No messages.\n");
		exit(1);
	}
E 2
	commands();
D 4
	if (!edit)
E 4
I 4
D 39
	if (!edit) {
D 23
		sigset(SIGHUP, SIG_IGN);
		sigset(SIGINT, SIG_IGN);
		sigset(SIGQUIT, SIG_IGN);
E 23
I 23
		signal(SIGHUP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
E 23
E 4
		quit();
I 4
	}
E 39
I 39
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	quit();
E 39
E 4
	exit(0);
I 9
}

/*
 * Interrupt printing of the headers.
 */
I 47
void
E 47
D 48
hdrstop()
E 48
I 48
hdrstop(signo)
	int signo;
E 48
{

D 18
	clrbuf(stdout);
	printf("\nInterrupt\n");
E 18
	fflush(stdout);
I 18
	fprintf(stderr, "\nInterrupt\n");
E 18
D 15
	sigrelse(SIGINT);
E 15
	longjmp(hdrjmp, 1);
I 23
}

/*
D 29
 * Compute what the screen size should be.
E 29
I 29
 * Compute what the screen size for printing headers should be.
E 29
 * We use the following algorithm for the height:
 *	If baud rate < 1200, use  9
 *	If baud rate = 1200, use 14
 *	If baud rate > 1200, use 24 or ws_row
 * Width is either 80 or ws_col;
 */
I 48
void
E 48
setscreensize()
{
I 29
D 50
	struct sgttyb tbuf;
E 50
I 50
	struct termios tbuf;
E 50
E 29
D 40
#ifdef	TIOCGWINSZ
E 40
	struct winsize ws;
I 50
	int ospeed;
E 50

D 30
	if (ioctl(fileno(stdout), TIOCGWINSZ, (char *) &ws) < 0)
E 30
I 30
	if (ioctl(1, TIOCGWINSZ, (char *) &ws) < 0)
E 30
D 29
		ws.ws_col = ws.ws_row = 0;
E 29
D 40
#endif
E 40
D 29
	if (baud < B1200)
E 29
I 29
		ws.ws_col = ws.ws_row = 0;
D 30
	if (outtty)
		gtty(1, &tbuf);
	else
E 30
I 30
D 43
	if (gtty(1, &tbuf) < 0)
E 43
I 43
D 50
	if (ioctl(1, TIOCGETP, &tbuf) < 0)
E 43
E 30
		tbuf.sg_ospeed = B9600;
	if (tbuf.sg_ospeed < B1200)
E 50
I 50
	if (ioctl(1, TIOCGETA, &tbuf) < 0)
		ospeed = B9600;
	else
		ospeed = cfgetospeed(&tbuf);
	if (ospeed < B1200)
E 50
E 29
		screenheight = 9;
D 29
	else if (baud == B1200)
E 29
I 29
D 50
	else if (tbuf.sg_ospeed == B1200)
E 50
I 50
	else if (ospeed == B1200)
E 50
E 29
		screenheight = 14;
D 29
#ifdef	TIOCGWINSZ
E 29
	else if (ws.ws_row != 0)
		screenheight = ws.ws_row;
D 29
#endif
E 29
	else
		screenheight = 24;
D 29
#ifdef TIOCGWINSZ
	if (ws.ws_col != 0)
		screenwidth = ws.ws_col;
	else
#endif
E 29
I 29
	if ((realscreenheight = ws.ws_row) == 0)
		realscreenheight = 24;
	if ((screenwidth = ws.ws_col) == 0)
E 29
		screenwidth = 80;
E 23
E 9
}
E 1
