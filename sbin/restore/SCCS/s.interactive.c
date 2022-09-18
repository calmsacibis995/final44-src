h33011
s 00001/00001/00747
d D 8.5 95/05/01 23:23:17 mckusick 32 31
c new dinode organization and naming
e
s 00001/00001/00747
d D 8.4 95/04/28 10:57:38 bostic 31 30
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00007/00002/00741
d D 8.3 94/09/13 12:26:47 mckusick 30 29
c add support for restoring whiteouts
e
s 00025/00011/00718
d D 8.2 94/08/31 21:18:15 mckusick 29 28
c correctly show which links are being extracted
e
s 00002/00002/00727
d D 8.1 93/06/05 11:11:47 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00728
d D 5.21 93/05/30 11:42:36 bostic 27 26
c cast to avoid the warning message
e
s 00000/00001/00729
d D 5.20 93/02/11 08:28:39 bostic 26 25
c gcc -Wall from Craig Leres (no substantive changes)
e
s 00002/00002/00728
d D 5.19 93/02/10 14:47:51 bostic 25 24
c make declarations work with new prototypes in globh
e
s 00231/00403/00499
d D 5.18 92/12/02 01:11:06 mckusick 24 23
c replace old adhoc globbing code with call to libc glob function
e
s 00046/00014/00856
d D 5.17 92/10/16 16:21:18 bostic 23 22
c ANSI C, convert options handling to getopt(3)
e
s 00001/00000/00869
d D 5.16 92/10/06 00:56:32 mckusick 22 21
c have to set type of single name ls commands
e
s 00003/00001/00866
d D 5.15 92/10/05 23:58:07 mckusick 21 20
c do not longjmp before starting command shell
e
s 00003/00003/00864
d D 5.14 92/10/05 21:50:33 mckusick 20 19
c use standard bit test macros
e
s 00002/00002/00865
d D 5.13 92/08/09 14:02:05 mckusick 19 18
c allow setdirmodes to force setting of modes when used explicitly
e
s 00040/00007/00827
d D 5.12 92/07/02 16:19:03 mckusick 18 17
c use d_type information to indicate file types
e
s 00001/00001/00833
d D 5.11 91/11/11 11:39:10 bostic 17 16
c break UFS up into FFS/UFS/LFS/MFS
e
s 00002/00002/00832
d D 5.10 91/07/29 15:59:27 mckusick 16 15
c use RST_DIR in place of DIR (to avoid conflicts with dirirectory
c access routine library
e
s 00001/00011/00833
d D 5.9 90/06/01 16:20:41 bostic 15 14
c new copyright notice
e
s 00001/00000/00843
d D 5.8 90/02/15 13:14:46 mckusick 14 13
c need to include ufs/dir.h since no longer done by restore.h
e
s 00001/00000/00842
d D 5.7 90/01/19 14:53:08 bostic 13 12
c new signals
e
s 00015/00004/00827
d D 5.6 88/10/24 16:38:18 bostic 12 11
c Berkeley copyright notice
e
s 00003/00001/00828
d D 5.5 87/04/23 22:43:53 mckusick 11 10
c can only define inumber if file exists on tape (from shannon@sun.com)
e
s 00036/00001/00793
d D 5.4 86/10/21 16:35:16 mckusick 10 9
c check interactive commands more closely; add `what' command
e
s 00009/00003/00785
d D 5.3 85/07/21 16:58:02 mckusick 9 7
c deal with arbitrary sized inode numbers
e
s 00001/00001/00787
d R 5.3 85/07/21 16:46:46 mckusick 8 7
c use wider format for inode numbers
e
s 00001/00001/00787
d D 5.2 85/06/18 21:11:24 mckusick 7 6
c dumprestor.h moves to /usr/include/protocols
e
s 00006/00002/00782
d D 5.1 85/05/28 15:11:46 dist 6 5
c Add copyright
e
s 00003/00002/00781
d D 3.5 85/05/27 17:29:46 mckusick 5 4
c make 'R' into a real mode
e
s 00001/00001/00782
d D 3.4 85/05/17 17:25:10 mckusick 4 3
c must use static declarations for variables passed back (from tef@ucsfcgl)
e
s 00143/00159/00640
d D 3.3 85/02/18 17:00:16 mckusick 3 2
c glob'ed files are now sorted; canon() elides extra /'s and /.'s
e
s 00275/00000/00524
d D 3.2 85/01/18 22:39:38 mckusick 2 1
c add globbing of file names
e
s 00524/00000/00000
d D 3.1 85/01/18 22:36:07 mckusick 1 0
c date and time created 85/01/18 22:36:07 by mckusick
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1985 Regents of the University of California */
E 6
I 6
/*
D 12
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 28
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 12
 */
E 6

#ifndef lint
D 6
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 6
I 6
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
D 12
#endif not lint
E 12
I 12
#endif /* not lint */
E 12

D 23
#include "restore.h"
E 23
I 23
#include <sys/param.h>
#include <sys/time.h>
I 24
#include <sys/stat.h>
E 24

D 32
#include <ufs/ffs/fs.h>
E 32
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/dir.h>
I 32
#include <ufs/ffs/fs.h>
E 32
E 23
D 7
#include <dumprestor.h>
E 7
I 7
#include <protocols/dumprestore.h>
I 23

E 23
E 7
#include <setjmp.h>
I 24
#include <glob.h>
E 24
I 14
D 17
#include <ufs/dir.h>
E 17
I 17
D 23
#include <ufs/ufs/dir.h>
E 23
I 23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 23
E 17
E 14

I 23
#include "restore.h"
#include "extern.h"

E 23
I 2
#define round(a, b) (((a) + (b) - 1) / (b) * (b))

E 2
/*
 * Things to handle interruptions.
 */
I 21
static int runshell;
E 21
static jmp_buf reset;
static char *nextarg = NULL;

/*
I 2
D 3
 * Structure associated with file name globbing.
 */
struct argnod {
	struct argnod *argnxt;
	char argval[1];
}; 
static struct argnod *gchain, *stakbot, *staktop;
static char *brkend, *nullstr = "";
struct argnod *locstak(), *endstak();

/*
E 3
E 2
 * Structure and routines associated with listing directories.
 */
struct afile {
	ino_t	fnum;		/* inode number of file */
	char	*fname;		/* file name */
D 24
	short	fflags;		/* extraction flags, if any */
	char	ftype;		/* file type, e.g. LEAF or NODE */
I 18
	char	finotype;	/* file type specified in directory entry */
E 24
I 24
	short	len;		/* name length */
	char	prefix;		/* prefix character */
	char	postfix;	/* postfix character */
E 24
E 18
};
I 3
struct arglist {
D 24
	struct afile	*head;	/* start of argument list */
	struct afile	*last;	/* end of argument list */
	struct afile	*base;	/* current list arena */
	int		nent;	/* maximum size of list */
	char		*cmd;	/* the current command */
E 24
I 24
	int	freeglob;	/* glob structure needs to be freed */
	int	argcnt;		/* next globbed argument to return */
	glob_t	glob;		/* globbing information */
	char	*cmd;		/* the current command */
E 24
};
E 3
D 23
extern int fcmp();
extern char *fmtentry();
char *copynext();
E 23

I 23
D 24
static int	 addg __P((struct direct *, char *, char *, struct arglist *));
E 24
static char	*copynext __P((char *, char *));
D 24
static int	 expand __P((char *, int, struct arglist *));
static void	 expandarg __P((char *, struct arglist *));
E 24
static int	 fcmp __P((const void *, const void *));
D 26
static char	*fmtentry __P((struct afile *));
E 26
D 24
static void	 formatf __P((struct arglist *));
E 24
I 24
static void	 formatf __P((struct afile *, int));
E 24
static void	 getcmd __P((char *, char *, char *, struct arglist *));
D 24
static int	 gmatch __P((char *, char *));
static int	 mkentry __P((char *, struct direct *, struct arglist *));
static void	 printlist __P((char *, ino_t, char *));
E 24
I 24
struct dirent	*glob_readdir __P((RST_DIR *dirp));
D 25
static int	 glob_stat __P((char *, struct stat *));
E 25
I 25
static int	 glob_stat __P((const char *, struct stat *));
E 25
D 29
static void	 mkentry __P((struct direct *, struct afile *));
E 29
I 29
static void	 mkentry __P((char *, struct direct *, struct afile *));
E 29
static void	 printlist __P((char *, char *));
E 24

E 23
/*
 * Read and execute commands from the terminal.
 */
I 23
void
E 23
runcmdshell()
{
	register struct entry *np;
	ino_t ino;
I 3
D 24
	static struct arglist alist = { 0, 0, 0, 0, 0 };
E 24
I 24
	struct arglist arglist;
E 24
E 3
	char curdir[MAXPATHLEN];
	char name[MAXPATHLEN];
	char cmd[BUFSIZ];

I 24
	arglist.freeglob = 0;
	arglist.argcnt = 0;
	arglist.glob.gl_flags = GLOB_ALTDIRFUNC;
	arglist.glob.gl_opendir = (void *)rst_opendir;
	arglist.glob.gl_readdir = (void *)glob_readdir;
D 27
	arglist.glob.gl_closedir = rst_closedir;
E 27
I 27
	arglist.glob.gl_closedir = (void *)rst_closedir;
E 27
	arglist.glob.gl_lstat = glob_stat;
	arglist.glob.gl_stat = glob_stat;
E 24
	canon("/", curdir);
loop:
	if (setjmp(reset) != 0) {
I 2
D 3
		gchain = 0;
E 3
I 3
D 24
		for (; alist.head < alist.last; alist.head++)
			freename(alist.head->fname);
E 24
I 24
		if (arglist.freeglob != 0) {
			arglist.freeglob = 0;
			arglist.argcnt = 0;
			globfree(&arglist.glob);
		}
E 24
E 3
E 2
		nextarg = NULL;
		volno = 0;
	}
I 21
	runshell = 1;
E 21
D 3
	getcmd(curdir, cmd, name);
E 3
I 3
D 24
	getcmd(curdir, cmd, name, &alist);
E 24
I 24
	getcmd(curdir, cmd, name, &arglist);
E 24
E 3
	switch (cmd[0]) {
	/*
	 * Add elements to the extraction list.
	 */
	case 'a':
I 10
		if (strncmp(cmd, "add", strlen(cmd)) != 0)
			goto bad;
E 10
		ino = dirlookup(name);
		if (ino == 0)
			break;
		if (mflag)
			pathcheck(name);
		treescan(name, ino, addfile);
		break;
	/*
	 * Change working directory.
	 */
	case 'c':
I 10
		if (strncmp(cmd, "cd", strlen(cmd)) != 0)
			goto bad;
E 10
		ino = dirlookup(name);
		if (ino == 0)
			break;
		if (inodetype(ino) == LEAF) {
			fprintf(stderr, "%s: not a directory\n", name);
			break;
		}
		(void) strcpy(curdir, name);
		break;
	/*
	 * Delete elements from the extraction list.
	 */
	case 'd':
I 10
		if (strncmp(cmd, "delete", strlen(cmd)) != 0)
			goto bad;
E 10
		np = lookupname(name);
D 23
		if (np == NIL || (np->e_flags & NEW) == 0) {
E 23
I 23
		if (np == NULL || (np->e_flags & NEW) == 0) {
E 23
			fprintf(stderr, "%s: not on extraction list\n", name);
			break;
		}
		treescan(name, np->e_ino, deletefile);
		break;
	/*
	 * Extract the requested list.
	 */
	case 'e':
I 10
		if (strncmp(cmd, "extract", strlen(cmd)) != 0)
			goto bad;
E 10
		createfiles();
		createlinks();
D 19
		setdirmodes();
E 19
I 19
		setdirmodes(0);
E 19
		if (dflag)
			checkrestore();
		volno = 0;
		break;
	/*
	 * List available commands.
	 */
	case 'h':
I 10
		if (strncmp(cmd, "help", strlen(cmd)) != 0)
			goto bad;
E 10
	case '?':
D 5
		fprintf(stderr, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
E 5
I 5
D 10
		fprintf(stderr, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
E 10
I 10
		fprintf(stderr, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
E 10
E 5
			"Available commands are:\n",
			"\tls [arg] - list directory\n",
			"\tcd arg - change directory\n",
			"\tpwd - print current directory\n",
			"\tadd [arg] - add `arg' to list of",
			" files to be extracted\n",
			"\tdelete [arg] - delete `arg' from",
			" list of files to be extracted\n",
			"\textract - extract requested files\n",
I 5
			"\tsetmodes - set modes of requested directories\n",
E 5
			"\tquit - immediately exit program\n",
I 10
			"\twhat - list dump header information\n",
E 10
			"\tverbose - toggle verbose flag",
			" (useful with ``ls'')\n",
			"\thelp or `?' - print this list\n",
			"If no `arg' is supplied, the current",
			" directory is used\n");
		break;
	/*
	 * List a directory.
	 */
	case 'l':
I 10
		if (strncmp(cmd, "ls", strlen(cmd)) != 0)
			goto bad;
E 10
D 24
		ino = dirlookup(name);
		if (ino == 0)
			break;
		printlist(name, ino, curdir);
E 24
I 24
		printlist(name, curdir);
E 24
		break;
	/*
	 * Print current directory.
	 */
	case 'p':
I 10
		if (strncmp(cmd, "pwd", strlen(cmd)) != 0)
			goto bad;
E 10
		if (curdir[1] == '\0')
			fprintf(stderr, "/\n");
		else
			fprintf(stderr, "%s\n", &curdir[1]);
		break;
	/*
	 * Quit.
	 */
	case 'q':
I 10
		if (strncmp(cmd, "quit", strlen(cmd)) != 0)
			goto bad;
		return;
E 10
	case 'x':
I 10
		if (strncmp(cmd, "xit", strlen(cmd)) != 0)
			goto bad;
E 10
		return;
	/*
	 * Toggle verbose mode.
	 */
	case 'v':
I 10
		if (strncmp(cmd, "verbose", strlen(cmd)) != 0)
			goto bad;
E 10
		if (vflag) {
			fprintf(stderr, "verbose mode off\n");
			vflag = 0;
			break;
		}
		fprintf(stderr, "verbose mode on\n");
		vflag++;
		break;
	/*
	 * Just restore requested directory modes.
	 */
D 5
	case 'R':
E 5
I 5
	case 's':
I 10
		if (strncmp(cmd, "setmodes", strlen(cmd)) != 0)
			goto bad;
E 10
E 5
D 19
		setdirmodes();
E 19
I 19
		setdirmodes(FORCE);
E 19
		break;
	/*
I 10
	 * Print out dump header information.
	 */
	case 'w':
		if (strncmp(cmd, "what", strlen(cmd)) != 0)
			goto bad;
		printdumpinfo();
		break;
	/*
E 10
	 * Turn on debugging.
	 */
	case 'D':
I 10
		if (strncmp(cmd, "Debug", strlen(cmd)) != 0)
			goto bad;
E 10
		if (dflag) {
			fprintf(stderr, "debugging mode off\n");
			dflag = 0;
			break;
		}
		fprintf(stderr, "debugging mode on\n");
		dflag++;
		break;
	/*
	 * Unknown command.
	 */
	default:
I 10
	bad:
E 10
		fprintf(stderr, "%s: unknown command; type ? for help\n", cmd);
		break;
	}
	goto loop;
}

/*
 * Read and parse an interactive command.
 * The first word on the line is assigned to "cmd". If
 * there are no arguments on the command line, then "curdir"
 * is returned as the argument. If there are arguments
 * on the line they are returned one at a time on each
 * successive call to getcmd. Each argument is first assigned
 * to "name". If it does not start with "/" the pathname in
 * "curdir" is prepended to it. Finally "canon" is called to
 * eliminate any embedded ".." components.
 */
I 23
static void
E 23
D 3
getcmd(curdir, cmd, name)
E 3
I 3
getcmd(curdir, cmd, name, ap)
E 3
	char *curdir, *cmd, *name;
I 3
	struct arglist *ap;
E 3
{
	register char *cp;
	static char input[BUFSIZ];
	char output[BUFSIZ];
#	define rawname input	/* save space by reusing input buffer */

	/*
	 * Check to see if still processing arguments.
	 */
I 2
D 3
	if (gchain != 0)
		goto getnextexp;
E 3
I 3
D 24
	if (ap->head != ap->last) {
		strcpy(name, ap->head->fname);
		freename(ap->head->fname);
		ap->head++;
		return;
	}
E 24
I 24
	if (ap->argcnt > 0)
		goto retnext;
E 24
E 3
E 2
	if (nextarg != NULL)
		goto getnext;
	/*
	 * Read a command line and trim off trailing white space.
	 */
	do	{
		fprintf(stderr, "restore > ");
		(void) fflush(stderr);
		(void) fgets(input, BUFSIZ, terminal);
	} while (!feof(terminal) && input[0] == '\n');
	if (feof(terminal)) {
		(void) strcpy(cmd, "quit");
		return;
	}
	for (cp = &input[strlen(input) - 2]; *cp == ' ' || *cp == '\t'; cp--)
		/* trim off trailing white space and newline */;
	*++cp = '\0';
	/*
	 * Copy the command into "cmd".
	 */
	cp = copynext(input, cmd);
I 3
	ap->cmd = cmd;
E 3
	/*
	 * If no argument, use curdir as the default.
	 */
	if (*cp == '\0') {
		(void) strcpy(name, curdir);
		return;
	}
	nextarg = cp;
	/*
	 * Find the next argument.
	 */
getnext:
	cp = copynext(nextarg, rawname);
	if (*cp == '\0')
		nextarg = NULL;
	else
		nextarg = cp;
	/*
D 24
	 * If it an absolute pathname, canonicalize it and return it.
E 24
I 24
	 * If it is an absolute pathname, canonicalize it and return it.
E 24
	 */
	if (rawname[0] == '/') {
		canon(rawname, name);
	} else {
		/*
		 * For relative pathnames, prepend the current directory to
		 * it then canonicalize and return it.
		 */
		(void) strcpy(output, curdir);
		(void) strcat(output, "/");
		(void) strcat(output, rawname);
		canon(output, name);
	}
I 2
D 3
	expandarg(name);
getnextexp:
	strcpy(name, gchain->argval);
	gchain = gchain->argnxt;
E 3
I 3
D 24
	expandarg(name, ap);
	strcpy(name, ap->head->fname);
	freename(ap->head->fname);
	ap->head++;
E 24
I 24
	if (glob(name, GLOB_ALTDIRFUNC, NULL, &ap->glob) < 0)
		fprintf(stderr, "%s: out of memory\n", ap->cmd);
	if (ap->glob.gl_pathc == 0)
		return;
	ap->freeglob = 1;
	ap->argcnt = ap->glob.gl_pathc;

retnext:
	strcpy(name, ap->glob.gl_pathv[ap->glob.gl_pathc - ap->argcnt]);
	if (--ap->argcnt == 0) {
		ap->freeglob = 0;
		globfree(&ap->glob);
	}
E 24
E 3
E 2
#	undef rawname
}

/*
 * Strip off the next token of the input.
 */
D 23
char *
E 23
I 23
static char *
E 23
copynext(input, output)
	char *input, *output;
{
	register char *cp, *bp;
	char quote;

	for (cp = input; *cp == ' ' || *cp == '\t'; cp++)
		/* skip to argument */;
	bp = output;
	while (*cp != ' ' && *cp != '\t' && *cp != '\0') {
		/*
		 * Handle back slashes.
		 */
		if (*cp == '\\') {
			if (*++cp == '\0') {
				fprintf(stderr,
					"command lines cannot be continued\n");
				continue;
			}
			*bp++ = *cp++;
			continue;
		}
		/*
		 * The usual unquoted case.
		 */
		if (*cp != '\'' && *cp != '"') {
			*bp++ = *cp++;
			continue;
		}
		/*
		 * Handle single and double quotes.
		 */
		quote = *cp++;
		while (*cp != quote && *cp != '\0')
			*bp++ = *cp++ | 0200;
		if (*cp++ == '\0') {
			fprintf(stderr, "missing %c\n", quote);
			cp--;
			continue;
		}
	}
	*bp = '\0';
	return (cp);
}

/*
 * Canonicalize file names to always start with ``./'' and
D 3
 * remove any imbedded ".." components.
E 3
I 3
 * remove any imbedded "." and ".." components.
E 3
 */
I 23
void
E 23
canon(rawname, canonname)
	char *rawname, *canonname;
{
	register char *cp, *np;
D 23
	int len;
E 23

	if (strcmp(rawname, ".") == 0 || strncmp(rawname, "./", 2) == 0)
		(void) strcpy(canonname, "");
	else if (rawname[0] == '/')
		(void) strcpy(canonname, ".");
	else
		(void) strcpy(canonname, "./");
	(void) strcat(canonname, rawname);
D 3
	len = strlen(canonname) - 1;
	if (canonname[len] == '/')
		canonname[len] = '\0';
E 3
	/*
D 3
	 * Eliminate extraneous ".." from pathnames.
E 3
I 3
	 * Eliminate multiple and trailing '/'s
E 3
	 */
I 3
	for (cp = np = canonname; *np != '\0'; cp++) {
		*cp = *np++;
		while (*cp == '/' && *np == '/')
			np++;
	}
	*cp = '\0';
	if (*--cp == '/')
		*cp = '\0';
	/*
	 * Eliminate extraneous "." and ".." from pathnames.
	 */
E 3
	for (np = canonname; *np != '\0'; ) {
		np++;
		cp = np;
		while (*np != '/' && *np != '\0')
			np++;
I 3
		if (np - cp == 1 && *cp == '.') {
			cp--;
			(void) strcpy(cp, np);
			np = cp;
		}
E 3
		if (np - cp == 2 && strncmp(cp, "..", 2) == 0) {
			cp--;
			while (cp > &canonname[1] && *--cp != '/')
				/* find beginning of name */;
			(void) strcpy(cp, np);
			np = cp;
		}
	}
I 2
}

/*
D 24
 * globals (file name generation)
 *
 * "*" in params matches r.e ".*"
 * "?" in params matches r.e. "."
 * "[...]" in params matches character class
 * "[...a-z...]" in params matches a through z.
 */
I 23
static void
E 23
D 3
expandarg(arg)
E 3
I 3
expandarg(arg, ap)
E 3
	char *arg;
I 3
	register struct arglist *ap;
E 3
{
D 3
	static char *expbuf = NULL;
	static unsigned expsize = BUFSIZ;
E 3
I 3
D 4
	struct afile single;
E 4
I 4
	static struct afile single;
I 11
	struct entry *ep;
E 11
E 4
E 3
	int size;
D 3
	char argbuf[BUFSIZ];
E 3

D 3
	do {
		if (expbuf != NULL)
			free(expbuf);
		expbuf = malloc(expsize);
		brkend = expbuf + expsize;
		expsize <<= 1;
		stakbot = (struct argnod *)expbuf;
		gchain = 0;
		(void)strcpy(argbuf, arg);
		size = expand(argbuf, 0);
	} while (size < 0);
E 3
I 3
	ap->head = ap->last = (struct afile *)0;
	size = expand(arg, 0, ap);
E 3
	if (size == 0) {
D 3
		gchain = (struct argnod *)expbuf;
		gchain->argnxt = 0;
		(void)strcpy(gchain->argval, arg);
E 3
I 3
D 11
		single.fnum = lookupname(arg)->e_ino;
E 11
I 11
		ep = lookupname(arg);
		single.fnum = ep ? ep->e_ino : 0;
E 11
		single.fname = savename(arg);
		ap->head = &single;
		ap->last = ap->head + 1;
		return;
E 3
	}
I 3
	qsort((char *)ap->head, ap->last - ap->head, sizeof *ap->head, fcmp);
E 3
}

/*
 * Expand a file name
 */
I 23
static int
E 23
D 3
expand(as, rflg)
E 3
I 3
expand(as, rflg, ap)
E 3
	char *as;
	int rflg;
I 3
	register struct arglist *ap;
E 3
{
	int		count, size;
	char		dir = 0;
	char		*rescan = 0;
D 16
	DIR		*dirp;
E 16
I 16
	RST_DIR		*dirp;
E 16
	register char	*s, *cs;
D 3
	struct argnod	*schain = gchain;
E 3
I 3
	int		sindex, rindex, lindex;
E 3
	struct direct	*dp;
	register char	slash; 
	register char	*rs; 
D 3
	struct argnod	*rchain;
E 3
	register char	c;

	/*
	 * check for meta chars
	 */
	s = cs = as;
	slash = 0;
	while (*cs != '*' && *cs != '?' && *cs != '[') {	
D 3
		if (*cs++==0) {	
E 3
I 3
		if (*cs++ == 0) {	
E 3
			if (rflg && slash)
				break; 
			else
				return (0) ;
D 3
		} else if (*cs=='/') {	
E 3
I 3
		} else if (*cs == '/') {	
E 3
			slash++;
		}
	}
	for (;;) {	
		if (cs == s) {	
D 3
			s = nullstr;
E 3
I 3
			s = "";
E 3
			break;
		} else if (*--cs == '/') {	
			*cs = 0;
			if (s == cs)
				s = "/";
			break;
		}
	}
	if ((dirp = rst_opendir(s)) != NULL)
		dir++;
	count = 0;
	if (*cs == 0)
D 3
		*cs++=0200 ;
E 3
I 3
		*cs++ = 0200;
E 3
	if (dir) {
		/*
		 * check for rescan
		 */
		rs = cs;
		do {	
			if (*rs == '/') { 
				rescan = rs; 
				*rs = 0; 
D 3
				gchain = 0 ;
E 3
			}
		} while (*rs++);
I 3
		sindex = ap->last - ap->head;
E 3
		while ((dp = rst_readdir(dirp)) != NULL && dp->d_ino != 0) {
D 20
			if (!dflag && BIT(dp->d_ino, dumpmap) == 0)
E 20
I 20
			if (!dflag && TSTINO(dp->d_ino, dumpmap) == 0)
E 20
				continue;
			if ((*dp->d_name == '.' && *cs != '.'))
				continue;
			if (gmatch(dp->d_name, cs)) {	
D 3
				if (addg(s, dp->d_name, rescan) < 0)
E 3
I 3
				if (addg(dp, s, rescan, ap) < 0)
E 3
					return (-1);
				count++;
			}
		}
		if (rescan) {	
D 3
			rchain = gchain; 
			gchain = schain;
E 3
I 3
			rindex = sindex; 
			lindex = ap->last - ap->head;
E 3
			if (count) {	
				count = 0;
D 3
				while (rchain) {	
					size = expand(rchain->argval, 1);
E 3
I 3
				while (rindex < lindex) {	
					size = expand(ap->head[rindex].fname,
					    1, ap);
E 3
					if (size < 0)
						return (size);
					count += size;
D 3
					rchain = rchain->argnxt;
E 3
I 3
					rindex++;
E 3
				}
			}
I 3
			bcopy((char *)&ap->head[lindex],
			     (char *)&ap->head[sindex],
			     (ap->last - &ap->head[rindex]) * sizeof *ap->head);
			ap->last -= lindex - sindex;
E 3
			*rescan = '/';
		}
	}
	s = as;
	while (c = *s)
		*s++ = (c&0177 ? c : '/');
	return (count);
}

/*
 * Check for a name match
 */
I 23
static int
E 23
gmatch(s, p)
	register char	*s, *p;
{
	register int	scc;
	char		c;
	char		ok; 
	int		lc;

	if (scc = *s++)
		if ((scc &= 0177) == 0)
			scc = 0200;
	switch (c = *p++) {

	case '[':
		ok = 0; 
		lc = 077777;
		while (c = *p++) {	
D 3
			if (c==']') {
E 3
I 3
			if (c == ']') {
E 3
				return (ok ? gmatch(s, p) : 0);
			} else if (c == '-') {	
				if (lc <= scc && scc <= (*p++))
					ok++ ;
			} else {	
				if (scc == (lc = (c&0177)))
					ok++ ;
			}
		}
		return (0);

	default:
		if ((c&0177) != scc)
			return (0) ;
		/* falls through */

	case '?':
		return (scc ? gmatch(s, p) : 0);

	case '*':
		if (*p == 0)
			return (1) ;
		s--;
		while (*s) {  
			if (gmatch(s++, p))
				return (1);
		}
		return (0);

	case 0:
		return (scc == 0);
	}
}

/*
 * Construct a matched name.
 */
I 23
static int
E 23
D 3
addg(as1, as2, as3)
	char		*as1, *as2, *as3;
E 3
I 3
addg(dp, as1, as3, ap)
	struct direct	*dp;
	char		*as1, *as3;
	struct arglist	*ap;
E 3
{
	register char	*s1, *s2;
	register int	c;
I 3
	char		buf[BUFSIZ];
E 3

D 3
	if ((s2 = (char *)locstak()) == 0)
		return (-1);
	s2 += sizeof(char *);
E 3
I 3
	s2 = buf;
E 3
	s1 = as1;
	while (c = *s1++) {	
		if ((c &= 0177) == 0) {	
D 3
			*s2++='/';
E 3
I 3
			*s2++ = '/';
E 3
			break;
		}
		*s2++ = c;
	}
D 3
	s1 = as2;
E 3
I 3
	s1 = dp->d_name;
E 3
	while (*s2 = *s1++)
		s2++;
	if (s1 = as3) {	
		*s2++ = '/';
		while (*s2++ = *++s1)
			/* void */;
	}
D 3
	makearg(endstak(s2));
	return (0);
E 3
I 3
D 18
	if (mkentry(buf, dp->d_ino, ap) == FAIL)
E 18
I 18
	if (mkentry(buf, dp, ap) == FAIL)
E 18
		return (-1);
I 23
	return (0);
E 23
E 3
}

/*
E 24
D 3
 * Add a matched name to the list.
 */
makearg(args)
	register struct argnod *args;
{
	args->argnxt = gchain;
	gchain = args;
}

/*
 * set up stack for local use
 * should be followed by `endstak'
 */
struct argnod *
locstak()
{
	if (brkend - (char *)stakbot < 100) {	
		fprintf(stderr, "ran out of arg space\n");
		return (0);
	}
	return (stakbot);
}

/*
 * tidy up after `locstak'
 */
struct argnod *
endstak(argp)
	register char *argp;
{
	register struct argnod *oldstak;

	*argp++ = 0;
	oldstak = stakbot;
	stakbot = staktop = (struct argnod *)round((int)argp, sizeof(char *));
	return (oldstak);
E 2
}

/*
E 3
 * Do an "ls" style listing of a directory
 */
I 23
static void
E 23
D 24
printlist(name, ino, basename)
E 24
I 24
printlist(name, basename)
E 24
	char *name;
D 24
	ino_t ino;
E 24
	char *basename;
{
D 24
	register struct afile *fp;
E 24
I 24
	register struct afile *fp, *list, *listp;
E 24
D 3
	struct afile *dfp0, *dfplast;
E 3
I 3
	register struct direct *dp;
D 24
	static struct arglist alist = { 0, 0, 0, 0, "ls" };
E 24
E 3
	struct afile single;
D 16
	DIR *dirp;
E 16
I 16
	RST_DIR *dirp;
I 24
D 29
	int entries, len;
E 29
I 29
	int entries, len, namelen;
	char locname[MAXPATHLEN + 1];
E 29
E 24
E 16

I 24
	dp = pathsearch(name);
D 29
	if (dp == NULL || (!dflag && TSTINO(dp->d_ino, dumpmap) == 0))
E 29
I 29
	if (dp == NULL || (!dflag && TSTINO(dp->d_ino, dumpmap) == 0) ||
	    (!vflag && dp->d_ino == WINO))
E 29
		return;
E 24
	if ((dirp = rst_opendir(name)) == NULL) {
D 24
		single.fnum = ino;
I 22
		single.finotype = DT_UNKNOWN;
E 22
D 3
		single.fname = savename(name + strlen(basename));
		dfp0 = &single;
		dfplast = dfp0 + 1;
E 3
I 3
		single.fname = savename(name + strlen(basename) + 1);
		alist.head = &single;
		alist.last = alist.head + 1;
E 24
I 24
		entries = 1;
		list = &single;
D 29
		mkentry(dp, list);
E 29
I 29
		mkentry(name, dp, list);
E 29
		len = strlen(basename) + 1;
		if (strlen(name) - len > single.len) {
			freename(single.fname);
			single.fname = savename(&name[len]);
			single.len = strlen(single.fname);
		}
E 24
E 3
	} else {
D 3
		if (getdir(dirp, &dfp0, &dfplast) == FAIL)
			return;
E 3
I 3
D 24
		alist.head = (struct afile *)0;
E 24
I 24
		entries = 0;
		while (dp = rst_readdir(dirp))
			entries++;
		rst_closedir(dirp);
		list = (struct afile *)malloc(entries * sizeof(struct afile));
		if (list == NULL) {
			fprintf(stderr, "ls: out of memory\n");
			return;
		}
		if ((dirp = rst_opendir(name)) == NULL)
			panic("directory reopen failed\n");
E 24
		fprintf(stderr, "%s:\n", name);
I 24
		entries = 0;
		listp = list;
I 29
		(void) strncpy(locname, name, MAXPATHLEN);
		(void) strncat(locname, "/", MAXPATHLEN);
		namelen = strlen(locname);
E 29
E 24
		while (dp = rst_readdir(dirp)) {
D 29
			if (dp == NULL || dp->d_ino == 0)
E 29
I 29
			if (dp == NULL)
E 29
				break;
D 20
			if (!dflag && BIT(dp->d_ino, dumpmap) == 0)
E 20
I 20
			if (!dflag && TSTINO(dp->d_ino, dumpmap) == 0)
E 20
				continue;
D 29
			if (vflag == 0 &&
			    (strcmp(dp->d_name, ".") == 0 ||
E 29
I 29
			if (!vflag && (dp->d_ino == WINO ||
			     strcmp(dp->d_name, ".") == 0 ||
E 29
			     strcmp(dp->d_name, "..") == 0))
				continue;
D 18
			if (!mkentry(dp->d_name, dp->d_ino, &alist))
E 18
I 18
D 24
			if (!mkentry(dp->d_name, dp, &alist))
E 18
				return;
E 24
I 24
D 29
			mkentry(dp, listp++);
			entries++;
E 29
I 29
			locname[namelen] = '\0';
			if (namelen + dp->d_namlen >= MAXPATHLEN) {
				fprintf(stderr, "%s%s: name exceeds %d char\n",
					locname, dp->d_name, MAXPATHLEN);
			} else {
				(void) strncat(locname, dp->d_name,
				    (int)dp->d_namlen);
				mkentry(locname, dp, listp++);
				entries++;
			}
E 29
E 24
		}
I 24
		rst_closedir(dirp);
		if (entries == 0) {
			fprintf(stderr, "\n");
			free(list);
			return;
		}
		qsort((char *)list, entries, sizeof(struct afile), fcmp);
E 24
E 3
	}
D 3
	qsort((char *)dfp0, dfplast - dfp0, sizeof (struct afile), fcmp);
	formatf(dfp0, dfplast);
	for (fp = dfp0; fp < dfplast; fp++)
		freename(fp->fname);
E 3
I 3
D 24
	if (alist.head != 0) {
		qsort((char *)alist.head, alist.last - alist.head,
			sizeof *alist.head, fcmp);
		formatf(&alist);
		for (fp = alist.head; fp < alist.last; fp++)
E 24
I 24
	formatf(list, entries);
	if (dirp != NULL) {
		for (fp = listp - 1; fp >= list; fp--)
E 24
			freename(fp->fname);
D 24
	}
	if (dirp != NULL)
E 24
		fprintf(stderr, "\n");
I 24
		free(list);
	}
E 24
E 3
}

/*
 * Read the contents of a directory.
 */
I 23
D 24
static int
E 23
D 3
getdir(dirp, pfp0, pfplast)
	DIR *dirp;
	struct afile **pfp0, **pfplast;
E 3
I 3
D 18
mkentry(name, ino, ap)
E 18
I 18
mkentry(name, dp, ap)
E 18
	char *name;
E 24
I 24
static void
D 29
mkentry(dp, fp)
E 29
I 29
mkentry(name, dp, fp)
	char *name;
E 29
E 24
D 18
	ino_t ino;
E 18
I 18
	struct direct *dp;
E 18
D 24
	register struct arglist *ap;
E 3
{
E 24
	register struct afile *fp;
I 24
{
	char *cp;
	struct entry *np;
E 24
D 3
	register struct direct *dp;
	static struct afile *basefp = NULL;
	static long nent = 20;
E 3

D 3
	if (basefp == NULL) {
		basefp = (struct afile *)calloc((unsigned)nent,
E 3
I 3
D 24
	if (ap->base == NULL) {
		ap->nent = 20;
		ap->base = (struct afile *)calloc((unsigned)ap->nent,
E 3
			sizeof (struct afile));
D 3
		if (basefp == NULL) {
			fprintf(stderr, "ls: out of memory\n");
E 3
I 3
		if (ap->base == NULL) {
			fprintf(stderr, "%s: out of memory\n", ap->cmd);
E 3
			return (FAIL);
		}
	}
D 3
	fp = *pfp0 = basefp;
	*pfplast = *pfp0 + nent;
	while (dp = rst_readdir(dirp)) {
		if (dp == NULL || dp->d_ino == 0)
			break;
		if (!dflag && BIT(dp->d_ino, dumpmap) == 0)
			continue;
		if (vflag == 0 &&
		    (strcmp(dp->d_name, ".") == 0 ||
		     strcmp(dp->d_name, "..") == 0))
			continue;
		fp->fnum = dp->d_ino;
		fp->fname = savename(dp->d_name);
		fp++;
		if (fp == *pfplast) {
			basefp = (struct afile *)realloc((char *)basefp,
			    (unsigned)(2 * nent * sizeof (struct afile)));
			if (basefp == 0) {
				fprintf(stderr, "ls: out of memory\n");
				return (FAIL);
			}
			*pfp0 = basefp;
			fp = *pfp0 + nent;
			*pfplast = fp + nent;
			nent *= 2;
E 3
I 3
	if (ap->head == 0)
		ap->head = ap->last = ap->base;
	fp = ap->last;
E 24
D 18
	fp->fnum = ino;
E 18
I 18
	fp->fnum = dp->d_ino;
D 24
	if (oldinofmt)
		fp->finotype = DT_UNKNOWN;
E 24
I 24
	fp->fname = savename(dp->d_name);
	for (cp = fp->fname; *cp; cp++)
		if (!vflag && (*cp < ' ' || *cp >= 0177))
			*cp = '?';
	fp->len = cp - fp->fname;
	if (dflag && TSTINO(fp->fnum, dumpmap) == 0)
		fp->prefix = '^';
D 29
	else if ((np = lookupino(fp->fnum)) != NULL && (np->e_flags & NEW))
E 29
I 29
	else if ((np = lookupname(name)) != NULL && (np->e_flags & NEW))
E 29
		fp->prefix = '*';
E 24
	else
D 24
		fp->finotype = dp->d_type;
E 18
	fp->fname = savename(name);
	fp++;
	if (fp == ap->head + ap->nent) {
		ap->base = (struct afile *)realloc((char *)ap->base,
		    (unsigned)(2 * ap->nent * sizeof (struct afile)));
		if (ap->base == 0) {
			fprintf(stderr, "%s: out of memory\n", ap->cmd);
			return (FAIL);
E 3
		}
I 3
		ap->head = ap->base;
		fp = ap->head + ap->nent;
		ap->nent *= 2;
E 24
I 24
		fp->prefix = ' ';
	switch(dp->d_type) {

	default:
		fprintf(stderr, "Warning: undefined file type %d\n",
		    dp->d_type);
		/* fall through */
	case DT_REG:
		fp->postfix = ' ';
		break;

	case DT_LNK:
		fp->postfix = '@';
		break;

	case DT_FIFO:
	case DT_SOCK:
		fp->postfix = '=';
		break;

	case DT_CHR:
	case DT_BLK:
		fp->postfix = '#';
		break;

I 30
	case DT_WHT:
		fp->postfix = '%';
		break;

E 30
	case DT_UNKNOWN:
	case DT_DIR:
		if (inodetype(dp->d_ino) == NODE)
			fp->postfix = '/';
		else
			fp->postfix = ' ';
		break;
E 24
E 3
	}
D 3
	*pfplast = fp;
E 3
I 3
D 24
	ap->last = fp;
E 3
	return (GOOD);
E 24
I 24
	return;
E 24
}

/*
 * Print out a pretty listing of a directory
 */
I 23
static void
E 23
D 3
formatf(fp0, fplast)
	struct afile *fp0, *fplast;
E 3
I 3
D 24
formatf(ap)
	register struct arglist *ap;
E 24
I 24
formatf(list, nentry)
	register struct afile *list;
	int nentry;
E 24
E 3
{
D 24
	register struct afile *fp;
	struct entry *np;
D 3
	int width = 0, w, nentry = fplast - fp0;
E 3
I 3
	int width = 0, w, nentry = ap->last - ap->head;
E 3
	int i, j, len, columns, lines;
	char *cp;
E 24
I 24
	register struct afile *fp, *endlist;
	int width, bigino, haveprefix, havepostfix;
	int i, j, w, precision, columns, lines;
E 24

D 3
	if (fp0 == fplast)
E 3
I 3
D 24
	if (ap->head == ap->last)
E 3
		return;
D 3
	for (fp = fp0; fp < fplast; fp++) {
E 3
I 3
	for (fp = ap->head; fp < ap->last; fp++) {
E 3
		fp->ftype = inodetype(fp->fnum);
		np = lookupino(fp->fnum);
D 23
		if (np != NIL)
E 23
I 23
		if (np != NULL)
E 23
			fp->fflags = np->e_flags;
		else
			fp->fflags = 0;
		len = strlen(fmtentry(fp));
		if (len > width)
			width = len;
E 24
I 24
	width = 0;
	haveprefix = 0;
	havepostfix = 0;
	bigino = ROOTINO;
	endlist = &list[nentry];
	for (fp = &list[0]; fp < endlist; fp++) {
		if (bigino < fp->fnum)
			bigino = fp->fnum;
		if (width < fp->len)
			width = fp->len;
		if (fp->prefix != ' ')
			haveprefix = 1;
		if (fp->postfix != ' ')
			havepostfix = 1;
E 24
	}
D 24
	width += 2;
	columns = 80 / width;
E 24
I 24
	if (haveprefix)
		width++;
	if (havepostfix)
		width++;
	if (vflag) {
		for (precision = 0, i = bigino; i > 0; i /= 10)
			precision++;
		width += precision + 1;
	}
	width++;
	columns = 81 / width;
E 24
	if (columns == 0)
		columns = 1;
	lines = (nentry + columns - 1) / columns;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
D 3
			fp = fp0 + j * lines + i;
E 3
I 3
D 24
			fp = ap->head + j * lines + i;
E 3
			cp = fmtentry(fp);
			fprintf(stderr, "%s", cp);
D 3
			if (fp + lines >= fplast) {
E 3
I 3
			if (fp + lines >= ap->last) {
E 24
I 24
			fp = &list[j * lines + i];
			if (vflag) {
				fprintf(stderr, "%*d ", precision, fp->fnum);
				fp->len += precision + 1;
			}
			if (haveprefix) {
				putc(fp->prefix, stderr);
				fp->len++;
			}
			fprintf(stderr, "%s", fp->fname);
			if (havepostfix) {
				putc(fp->postfix, stderr);
				fp->len++;
			}
			if (fp + lines >= endlist) {
E 24
E 3
				fprintf(stderr, "\n");
				break;
			}
D 24
			w = strlen(cp);
			while (w < width) {
				w++;
				fprintf(stderr, " ");
			}
E 24
I 24
			for (w = fp->len; w < width; w++)
				putc(' ', stderr);
E 24
		}
	}
}

/*
D 24
 * Comparison routine for qsort.
E 24
I 24
 * Skip over directory entries that are not on the tape
 *
 * First have to get definition of a dirent.
E 24
 */
I 23
D 24
static int
E 23
fcmp(f1, f2)
D 23
	register struct afile *f1, *f2;
E 23
I 23
	register const void *f1, *f2;
E 24
I 24
#undef DIRBLKSIZ
#include <dirent.h>
#undef d_ino

struct dirent *
glob_readdir(dirp)
	RST_DIR *dirp;
E 24
E 23
{
D 23

	return (strcmp(f1->fname, f2->fname));
E 23
I 23
D 24
	return (strcmp(((struct afile *)f1)->fname,
	    ((struct afile *)f2)->fname));
E 24
I 24
	struct direct *dp;
	static struct dirent adirent;

	while ((dp = rst_readdir(dirp)) != NULL) {
D 30
		if (dp->d_ino == 0)
E 30
I 30
		if (!vflag && dp->d_ino == WINO)
E 30
			continue;
		if (dflag || TSTINO(dp->d_ino, dumpmap))
			break;
	}
	if (dp == NULL)
		return (NULL);
	adirent.d_fileno = dp->d_ino;
	adirent.d_namlen = dp->d_namlen;
D 31
	bcopy(dp->d_name, adirent.d_name, dp->d_namlen + 1);
E 31
I 31
	memmove(adirent.d_name, dp->d_name, dp->d_namlen + 1);
E 31
	return (&adirent);
E 24
E 23
}

/*
D 24
 * Format a directory entry.
E 24
I 24
 * Return st_mode information in response to stat or lstat calls
E 24
 */
D 23
char *
E 23
I 23
D 24
static char *
E 23
fmtentry(fp)
	register struct afile *fp;
E 24
I 24
static int
glob_stat(name, stp)
D 25
	char *name;
E 25
I 25
	const char *name;
E 25
	struct stat *stp;
E 24
{
D 24
	static char fmtres[BUFSIZ];
I 9
	static int precision = 0;
	int i;
E 9
	register char *cp, *dp;
E 24
I 24
	register struct direct *dp;
E 24

D 9
	if (vflag)
		(void) sprintf(fmtres, "%5d ", fp->fnum);
	else
E 9
I 9
D 24
	if (!vflag) {
E 9
		fmtres[0] = '\0';
I 9
	} else {
		if (precision == 0)
			for (i = maxino; i > 0; i /= 10)
				precision++;
		(void) sprintf(fmtres, "%*d ", precision, fp->fnum);
	}
E 9
	dp = &fmtres[strlen(fmtres)];
D 20
	if (dflag && BIT(fp->fnum, dumpmap) == 0)
E 20
I 20
	if (dflag && TSTINO(fp->fnum, dumpmap) == 0)
E 20
		*dp++ = '^';
	else if ((fp->fflags & NEW) != 0)
		*dp++ = '*';
E 24
I 24
	dp = pathsearch(name);
D 30
	if (dp == NULL || (!dflag && TSTINO(dp->d_ino, dumpmap) == 0))
E 30
I 30
	if (dp == NULL || (!dflag && TSTINO(dp->d_ino, dumpmap) == 0) ||
	    (!vflag && dp->d_ino == WINO))
E 30
		return (-1);
	if (inodetype(dp->d_ino) == NODE)
		stp->st_mode = IFDIR;
E 24
	else
D 24
		*dp++ = ' ';
	for (cp = fp->fname; *cp; cp++)
		if (!vflag && (*cp < ' ' || *cp >= 0177))
			*dp++ = '?';
		else
			*dp++ = *cp;
D 18
	if (fp->ftype == NODE)
		*dp++ = '/';
E 18
I 18
	switch(fp->finotype) {
E 24
I 24
		stp->st_mode = IFREG;
	return (0);
}
E 24

D 24
	case DT_LNK:
		*dp++ = '@';
		break;

	case DT_FIFO:
	case DT_SOCK:
		*dp++ = '=';
		break;

	case DT_CHR:
	case DT_BLK:
		*dp++ = '#';
		break;

	case DT_UNKNOWN:
	case DT_DIR:
		if (fp->ftype == NODE)
			*dp++ = '/';
		break;

	case DT_REG:
		/* nothing */
		break;

	default:
		fprintf(stderr, "Warning: undefined file type %d\n",
		    fp->finotype);
	}
E 18
	*dp++ = 0;
	return (fmtres);
E 24
I 24
/*
 * Comparison routine for qsort.
 */
static int
fcmp(f1, f2)
	register const void *f1, *f2;
{
	return (strcmp(((struct afile *)f1)->fname,
	    ((struct afile *)f2)->fname));
E 24
}

/*
 * respond to interrupts
 */
I 13
void
E 13
D 23
onintr()
E 23
I 23
onintr(signo)
	int signo;
E 23
{
D 21
	if (command == 'i')
E 21
I 21
	if (command == 'i' && runshell)
E 21
		longjmp(reset, 1);
	if (reply("restore interrupted, continue") == FAIL)
		done(1);
}
E 1
