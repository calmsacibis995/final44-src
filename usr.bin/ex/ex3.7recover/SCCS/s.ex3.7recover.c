h02302
s 00005/00005/00788
d D 8.1 93/06/09 21:48:10 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00791
d D 7.16 92/10/17 15:19:00 bostic 24 23
c snprintf returns printed length, not actual length
e
s 00021/00001/00773
d D 7.15 91/07/30 00:58:23 torek 23 22
c ANSI stdargs, for sparc among others
e
s 00010/00009/00764
d D 7.14 91/04/17 17:44:56 bostic 22 21
c new copyright; att/bsd/shared
e
s 00032/00031/00741
d D 7.13 91/03/01 14:07:21 bostic 21 20
c ANSI
e
s 00002/00006/00770
d D 7.12 90/05/28 12:57:10 bostic 20 19
c sys_errlist -> strerror(3)
e
s 00001/00006/00775
d D 7.11 89/05/19 18:46:23 bostic 19 18
c gtty is in a compatibility library now
e
s 00009/00016/00772
d D 7.10 89/05/11 09:52:29 bostic 18 17
c file reorg, pathnames.h, paths.h
e
s 00002/00002/00786
d D 7.9 85/06/07 18:26:09 bloom 17 16
c fix sccsid and copyright for xstr
e
s 00016/00002/00772
d D 7.8 85/05/31 15:20:05 dist 16 15
c Add copyright
e
s 00017/00000/00757
d D 7.7 85/03/19 19:27:56 mckusick 15 14
c eliminate use of stdio as it uses malloc while exrecover uses sbrk
e
s 00001/00001/00756
d D 7.6 83/07/03 22:54:05 sam 14 12
c 
e
s 00001/00002/00755
d R 7.6 83/07/03 22:39:57 sam 13 12
c no more local/uparm.h
e
s 00019/00024/00738
d D 7.5 83/06/10 10:08:45 ralph 12 11
c updating sccs files due to restoring an older SCCS directory
e
s 00001/00001/00761
d D 7.4 81/10/16 08:31:13 mark 11 10
c last minute fixes before release of 3.7
e
s 00002/00001/00760
d D 7.3 81/10/16 08:26:53 mark 10 9
c stuff to make loader work on 3b
e
s 00004/00005/00757
d D 7.2 81/07/09 23:08:40 mark 9 8
c fixed stuff broken by mjm
e
s 00011/00012/00751
d D 7.1 81/07/08 22:36:25 mark 8 7
c release 3.7 - a few bug fixes and a few new features.
e
s 00000/00000/00763
d D 6.1 80/10/19 01:23:11 mark 7 6
c preliminary release 3.6 10/18/80
e
s 00000/00000/00763
d D 5.1 80/08/20 16:16:58 mark 6 5
c Release 3.5, August 20, 1980
e
s 00002/00001/00761
d D 4.2 80/08/01 20:44:44 mark 5 4
c Bill added more buffers, and I put in sccs.
e
s 00005/00000/00757
d D 4.1 80/08/01 00:20:35 mark 4 3
c release 3.4, June 24, 1980
e
s 00000/00000/00757
d D 3.1 80/07/31 23:45:58 mark 3 2
c release 3.3, Feb 2, 1980
e
s 00004/00004/00753
d D 2.1 80/07/31 23:22:26 mark 2 1
c release 3.2, Jan 4, 1980
e
s 00757/00000/00000
d D 1.1 80/07/31 23:01:08 mark 1 0
c date and time created 80/07/31 23:01:08 by mark
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
D 8
/* Copyright (c) 1980 Regents of the University of California */
static char *sccsid = "%W% %G%";
E 8
I 8
D 16
/* Copyright (c) 1981 Regents of the University of California */
static char *sccsid = "%W%	%G%";
E 16
I 16
D 22
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
/*-
D 25
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * %sccs.include.proprietary.c%
E 22
 */

#ifndef lint
D 17
char copyright[] =
E 17
I 17
D 22
char *copyright =
E 17
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 22
I 22
D 25
char copyright[] =
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 22
 All rights reserved.\n";
E 25
I 25
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 25
D 22
#endif not lint
E 22
I 22
#endif /* not lint */
E 22

#ifndef lint
D 17
static char sccsid[] = "%W% (Berkeley) %G%";
E 17
I 17
D 22
static char *sccsid = "%W% (Berkeley) %G%";
E 17
#endif not lint
E 22
I 22
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 22

E 16
#include <stdio.h>	/* mjm: BUFSIZ: stdio = 512, VMUNIX = 1024 */
#undef	BUFSIZ		/* mjm: BUFSIZ different */
#undef	EOF		/* mjm: EOF and NULL effectively the same */
#undef	NULL
I 9

E 9
E 8
E 5
#include "ex.h"
#include "ex_temp.h"
#include "ex_tty.h"
D 14
#include "local/uparm.h"
E 14
I 9
D 12
#include "sys/dir.h"
E 12
I 12
#include <sys/dir.h>
I 23
#if __STDC__
E 23
I 21
#include <stdarg.h>
I 23
#else
#include <varargs.h>
#endif
E 23
E 21
I 14
D 18
#include "uparm.h"
E 18
E 14
E 12
E 9

D 8
#undef	BUFSIZ
#undef	EOF
#undef	NULL
E 8
I 8
D 9
/* #undef	BUFSIZ		mjm: move to before ex.h */
/* #undef	EOF		mjm: move to before ex.h */
/* #undef	NULL		mjm: move to before ex.h */
E 9
I 9
D 10
char xstr[1];	/* make loader happy */
E 10
I 10
char xstr[1];		/* make loader happy */
short tfile = -1;	/* ditto */
E 10
E 9
E 8

I 23
#if __STDC__
void	fpr(const char *fmt, ...);
#else
void	fpr();
#endif

E 23
D 8
#include <stdio.h>
E 8
I 8
D 9
/* #include <stdio.h>		mjm: move to before ex.h */
E 8
#include <sys/dir.h>
E 9
I 9
/*
E 9
D 8

/*
 * Ex recovery program
 *	exrecover dir name
 *	exrecover -r
E 8
 *
 * This program searches through the specified directory and then
D 18
 * the directory usrpath(preserve) looking for an instance of the specified
E 18
I 18
 * the directory _PATH_USRPRESERVE looking for an instance of the specified
E 18
 * file from a crashed editor or a crashed system.
 * If this file is found, it is unscrambled and written to
 * the standard output.
 *
 * If this program terminates without a "broken pipe" diagnostic
 * (i.e. the editor doesn't die right away) then the buffer we are
 * writing from is removed when we finish.  This is potentially a mistake
 * as there is not enough handshaking to guarantee that the file has actually
 * been recovered, but should suffice for most cases.
 */

/*
 * For lint's sake...
 */
#ifndef lint
#define	ignorl(a)	a
#endif

/*
D 18
 * This directory definition also appears (obviously) in expreserve.c.
 * Change both if you change either.
 */
char	mydir[] =	usrpath(preserve);

/*
E 18
 * Limit on the number of printed entries
 * when an, e.g. ``ex -r'' command is given.
 */
#define	NENTRY	50

char	*ctime();
char	nb[BUFSIZ];
int	vercnt;			/* Count number of versions of file found */

main(argc, argv)
	int argc;
	char *argv[];
{
	register char *cp;
	register int b, i;

	/*
	 * Initialize as though the editor had just started.
	 */
	fendcore = (line *) sbrk(0);
	dot = zero = dol = fendcore;
	one = zero + 1;
	endcore = fendcore - 2;
	iblock = oblock = -1;

	/*
	 * If given only a -r argument, then list the saved files.
	 */
	if (argc == 2 && eq(argv[1], "-r")) {
D 18
		listfiles(mydir);
E 18
I 18
		listfiles(_PATH_PRESERVE);
E 18
		exit(0);
	}
	if (argc != 3)
		error(" Wrong number of arguments to exrecover", 0);

	CP(file, argv[2]);

	/*
	 * Search for this file.
	 */
	findtmp(argv[1]);

	/*
	 * Got (one of the versions of) it, write it back to the editor.
	 */
	cp = ctime(&H.Time);
	cp[19] = 0;
D 21
	fprintf(stderr, " [Dated: %s", cp);
	fprintf(stderr, vercnt > 1 ? ", newest of %d saved]" : "]", vercnt);
E 21
I 21
	fpr(" [Dated: %s", cp);
	fpr(vercnt > 1 ? ", newest of %d saved]" : "]", vercnt);
E 21
	H.Flines++;

	/*
	 * Allocate space for the line pointers from the temp file.
	 */
	if ((int) sbrk((int) (H.Flines * sizeof (line))) == -1)
		/*
		 * Good grief.
		 */
		error(" Not enough core for lines", 0);
#ifdef DEBUG
D 21
	fprintf(stderr, "%d lines\n", H.Flines);
E 21
I 21
	fpr("%d lines\n", H.Flines);
E 21
#endif

	/*
	 * Now go get the blocks of seek pointers which are scattered
	 * throughout the temp file, reconstructing the incore
	 * line pointers at point of crash.
	 */
	b = 0;
	while (H.Flines > 0) {
		ignorl(lseek(tfile, (long) blocks[b] * BUFSIZ, 0));
		i = H.Flines < BUFSIZ / sizeof (line) ?
			H.Flines * sizeof (line) : BUFSIZ;
		if (read(tfile, (char *) dot, i) != i) {
			perror(nb);
			exit(1);
		}
		dot += i / sizeof (line);
		H.Flines -= i / sizeof (line);
		b++;
	}
	dot--; dol = dot;

	/*
	 * Sigh... due to sandbagging some lines may really not be there.
	 * Find and discard such.  This shouldn't happen much.
	 */
	scrapbad();

	/*
	 * Now if there were any lines in the recovered file
	 * write them to the standard output.
	 */
	if (dol > zero) {
		addr1 = one; addr2 = dol; io = 1;
D 8
		putfile();
E 8
I 8
		putfile(0);
E 8
	}

	/*
	 * Trash the saved buffer.
	 * Hopefully the system won't crash before the editor
	 * syncs the new recovered buffer; i.e. for an instant here
	 * you may lose if the system crashes because this file
	 * is gone, but the editor hasn't completed reading the recovered
	 * file from the pipe from us to it.
	 *
	 * This doesn't work if we are coming from an non-absolute path
	 * name since we may have chdir'ed but what the hay, noone really
	 * ever edits with temporaries in "." anyways.
	 */
	if (nb[0] == '/')
		ignore(unlink(nb));

	/*
	 * Adieu.
	 */
	exit(0);
}

/*
 * Print an error message (notably not in error
 * message file).  If terminal is in RAW mode, then
 * we should be writing output for "vi", so don't print
 * a newline which would screw up the screen.
 */
/*VARARGS2*/
error(str, inf)
	char *str;
	int inf;
{

D 21
	fprintf(stderr, str, inf);
E 21
I 21
	fpr(str, inf);
E 21
I 4
D 19
#ifndef USG3TTY
E 4
	gtty(2, &tty);
E 19
I 19
	(void)ioctl(2, TIOCGETP, &tty);
E 19
	if ((tty.sg_flags & RAW) == 0)
I 4
D 19
#else
	ioctl(2, TCGETA, &tty);
	if (tty.c_lflag & ICANON)
#endif
E 19
E 4
D 21
		fprintf(stderr, "\n");
E 21
I 21
		fpr("\n");
E 21
	exit(1);
}

/*
 * Here we save the information about files, when
 * you ask us what files we have saved for you.
 * We buffer file name, number of lines, and the time
 * at which the file was saved.
 */
struct svfile {
	char	sf_name[FNSIZE + 1];
	int	sf_lines;
D 12
	char	sf_entry[DIRSIZ + 1];
E 12
I 12
	char	sf_entry[MAXNAMLEN + 1];
E 12
	time_t	sf_time;
};

listfiles(dirname)
	char *dirname;
{
D 12
	register FILE *dir;
	struct direct dirent;
E 12
I 12
	register DIR *dir;
	struct direct *dirent;
E 12
	int ecount, qucmp();
	register int f;
	char *cp;
	struct svfile *fp, svbuf[NENTRY];

	/*
D 18
	 * Open usrpath(preserve), and go there to make things quick.
E 18
I 18
	 * Open _PATH_PRESERVE, and go there to make things quick.
E 18
	 */
D 12
	dir = fopen(dirname, "r");
E 12
I 12
	dir = opendir(dirname);
E 12
	if (dir == NULL) {
		perror(dirname);
		return;
	}
	if (chdir(dirname) < 0) {
		perror(dirname);
		return;
	}

	/*
D 18
	 * Look at the candidate files in usrpath(preserve).
E 18
I 18
	 * Look at the candidate files in _PATH_PRESERVE.
E 18
	 */
	fp = &svbuf[0];
	ecount = 0;
D 12
	while (fread((char *) &dirent, sizeof dirent, 1, dir) == 1) {
		if (dirent.d_ino == 0)
E 12
I 12
	while ((dirent = readdir(dir)) != NULL) {
		if (dirent->d_name[0] != 'E')
E 12
			continue;
D 12
		if (dirent.d_name[0] != 'E')
			continue;
E 12
#ifdef DEBUG
D 12
		fprintf(stderr, "considering %s\n", dirent.d_name);
E 12
I 12
D 21
		fprintf(stderr, "considering %s\n", dirent->d_name);
E 21
I 21
		fpr("considering %s\n", dirent->d_name);
E 21
E 12
#endif
		/*
		 * Name begins with E; open it and
		 * make sure the uid in the header is our uid.
		 * If not, then don't bother with this file, it can't
		 * be ours.
		 */
D 12
		f = open(dirent.d_name, 0);
E 12
I 12
		f = open(dirent->d_name, 0);
E 12
		if (f < 0) {
#ifdef DEBUG
D 21
			fprintf(stderr, "open failed\n");
E 21
I 21
			fpr("open failed\n");
E 21
#endif
			continue;
		}
		if (read(f, (char *) &H, sizeof H) != sizeof H) {
#ifdef DEBUG
D 21
			fprintf(stderr, "culdnt read hedr\n");
E 21
I 21
			fpr("culdnt read hedr\n");
E 21
#endif
			ignore(close(f));
			continue;
		}
		ignore(close(f));
		if (getuid() != H.Uid) {
#ifdef DEBUG
D 21
			fprintf(stderr, "uid wrong\n");
E 21
I 21
			fpr("uid wrong\n");
E 21
#endif
			continue;
		}

		/*
		 * Saved the day!
		 */
D 12
		enter(fp++, dirent.d_name, ecount);
E 12
I 12
		enter(fp++, dirent->d_name, ecount);
E 12
		ecount++;
#ifdef DEBUG
D 12
		fprintf(stderr, "entered file %s\n", dirent.d_name);
E 12
I 12
D 21
		fprintf(stderr, "entered file %s\n", dirent->d_name);
E 21
I 21
		fpr("entered file %s\n", dirent->d_name);
E 21
E 12
#endif
	}
D 12
	ignore(fclose(dir));
E 12
I 12
	ignore(closedir(dir));
E 12

	/*
	 * If any files were saved, then sort them and print
	 * them out.
	 */
	if (ecount == 0) {
D 21
		fprintf(stderr, "No files saved.\n");
E 21
I 21
		fpr("No files saved.\n");
E 21
		return;
	}
	qsort(&svbuf[0], ecount, sizeof svbuf[0], qucmp);
	for (fp = &svbuf[0]; fp < &svbuf[ecount]; fp++) {
		cp = ctime(&fp->sf_time);
		cp[10] = 0;
D 21
		fprintf(stderr, "On %s at ", cp);
E 21
I 21
		fpr("On %s at ", cp);
E 21
 		cp[16] = 0;
D 21
		fprintf(stderr, &cp[11]);
		fprintf(stderr, " saved %d lines of file \"%s\"\n",
E 21
I 21
		fpr(&cp[11]);
		fpr(" saved %d lines of file \"%s\"\n",
E 21
		    fp->sf_lines, fp->sf_name);
	}
}

/*
 * Enter a new file into the saved file information.
 */
enter(fp, fname, count)
	struct svfile *fp;
	char *fname;
{
	register char *cp, *cp2;
	register struct svfile *f, *fl;
	time_t curtime, itol();

	f = 0;
	if (count >= NENTRY) {
		/*
		 * My god, a huge number of saved files.
		 * Would you work on a system that crashed this
		 * often?  Hope not.  So lets trash the oldest
		 * as the most useless.
		 *
		 * (I wonder if this code has ever run?)
		 */
		fl = fp - count + NENTRY - 1;
		curtime = fl->sf_time;
		for (f = fl; --f > fp-count; )
			if (f->sf_time < curtime)
				curtime = f->sf_time;
		for (f = fl; --f > fp-count; )
			if (f->sf_time == curtime)
				break;
		fp = f;
	}

	/*
	 * Gotcha.
	 */
	fp->sf_time = H.Time;
	fp->sf_lines = H.Flines;
	for (cp2 = fp->sf_name, cp = savedfile; *cp;)
		*cp2++ = *cp++;
	for (cp2 = fp->sf_entry, cp = fname; *cp && cp-fname < 14;)
		*cp2++ = *cp++;
	*cp2++ = 0;
}

/*
 * Do the qsort compare to sort the entries first by file name,
 * then by modify time.
 */
qucmp(p1, p2)
	struct svfile *p1, *p2;
{
	register int t;

	if (t = strcmp(p1->sf_name, p2->sf_name))
		return(t);
	if (p1->sf_time > p2->sf_time)
		return(-1);
	return(p1->sf_time < p2->sf_time);
}

/*
 * Scratch for search.
 */
char	bestnb[BUFSIZ];		/* Name of the best one */
long	besttime;		/* Time at which the best file was saved */
int	bestfd;			/* Keep best file open so it dont vanish */

/*
 * Look for a file, both in the users directory option value
D 18
 * (i.e. usually /tmp) and in usrpath(preserve).
E 18
I 18
 * (i.e. usually /tmp) and in _PATH_PRESERVE.
E 18
 * Want to find the newest so we search on and on.
 */
findtmp(dir)
	char *dir;
{

	/*
	 * No name or file so far.
	 */
	bestnb[0] = 0;
	bestfd = -1;

	/*
D 18
	 * Search usrpath(preserve) and, if we can get there, /tmp
E 18
I 18
	 * Search _PATH_PRESERVE and, if we can get there, /tmp
E 18
	 * (actually the users "directory" option).
	 */
	searchdir(dir);
D 18
	if (chdir(mydir) == 0)
		searchdir(mydir);
E 18
I 18
	if (chdir(_PATH_PRESERVE) == 0)
		searchdir(_PATH_PRESERVE);
E 18
	if (bestfd != -1) {
		/*
		 * Gotcha.
		 * Put the file (which is already open) in the file
		 * used by the temp file routines, and save its
		 * name for later unlinking.
		 */
		tfile = bestfd;
		CP(nb, bestnb);
		ignorl(lseek(tfile, 0l, 0));

		/*
		 * Gotta be able to read the header or fall through
		 * to lossage.
		 */
		if (read(tfile, (char *) &H, sizeof H) == sizeof H)
			return;
	}

	/*
	 * Extreme lossage...
	 */
	error(" File not found", 0);
}

/*
 * Search for the file in directory dirname.
 *
 * Don't chdir here, because the users directory
 * may be ".", and we would move away before we searched it.
 * Note that we actually chdir elsewhere (because it is too slow
D 18
 * to look around in usrpath(preserve) without chdir'ing there) so we
E 18
I 18
 * to look around in _PATH_PRESERVE without chdir'ing there) so we
E 18
 * can't win, because we don't know the name of '.' and if the path
 * name of the file we want to unlink is relative, rather than absolute
 * we won't be able to find it again.
 */
searchdir(dirname)
	char *dirname;
{
D 12
	struct direct dirent;
	register FILE *dir;
E 12
I 12
	struct direct *dirent;
	register DIR *dir;
E 12
	char dbuf[BUFSIZ];

D 12
	dir = fopen(dirname, "r");
E 12
I 12
	dir = opendir(dirname);
E 12
	if (dir == NULL)
		return;
D 11
	setbuf(dir, dbuf);
E 11
I 11
D 12
	/* setbuf(dir, dbuf); this breaks UNIX/370. */
E 11
	while (fread((char *) &dirent, sizeof dirent, 1, dir) == 1) {
		if (dirent.d_ino == 0)
E 12
I 12
	while ((dirent = readdir(dir)) != NULL) {
		if (dirent->d_name[0] != 'E')
E 12
			continue;
D 12
		if (dirent.d_name[0] != 'E' || dirent.d_name[DIRSIZ - 1] != 0)
			continue;
E 12
		/*
		 * Got a file in the directory starting with E...
		 * Save a consed up name for the file to unlink
		 * later, and check that this is really a file
		 * we are looking for.
		 */
D 12
		ignore(strcat(strcat(strcpy(nb, dirname), "/"), dirent.d_name));
E 12
I 12
		ignore(strcat(strcat(strcpy(nb, dirname), "/"), dirent->d_name));
E 12
		if (yeah(nb)) {
			/*
			 * Well, it is the file we are looking for.
			 * Is it more recent than any version we found before?
			 */
			if (H.Time > besttime) {
				/*
				 * A winner.
				 */
				ignore(close(bestfd));
				bestfd = dup(tfile);
				besttime = H.Time;
				CP(bestnb, nb);
			}
			/*
			 * Count versions so user can be told there are
			 * ``yet more pages to be turned''.
			 */
			vercnt++;
		}
		ignore(close(tfile));
	}
D 12
	ignore(fclose(dir));
E 12
I 12
	ignore(closedir(dir));
E 12
}

/*
 * Given a candidate file to be recovered, see
 * if its really an editor temporary and of this
 * user and the file specified.
 */
yeah(name)
	char *name;
{

	tfile = open(name, 2);
	if (tfile < 0)
		return (0);
	if (read(tfile, (char *) &H, sizeof H) != sizeof H) {
nope:
		ignore(close(tfile));
		return (0);
	}
	if (!eq(savedfile, file))
		goto nope;
	if (getuid() != H.Uid)
		goto nope;
	/*
	 * This is old and stupid code, which
	 * puts a word LOST in the header block, so that lost lines
	 * can be made to point at it.
	 */
D 2
	ignorl(lseek(tfile, 504l, 0));
E 2
I 2
	ignorl(lseek(tfile, (long)(BUFSIZ*HBLKS-8), 0));
E 2
	ignore(write(tfile, "LOST", 5));
	return (1);
}

preserve()
{

}

/*
 * Find the true end of the scratch file, and ``LOSE''
 * lines which point into thin air.  This lossage occurs
 * due to the sandbagging of i/o which can cause blocks to
 * be written in a non-obvious order, different from the order
 * in which the editor tried to write them.
 *
 * Lines which are lost are replaced with the text LOST so
 * they are easy to find.  We work hard at pretty formatting here
 * as lines tend to be lost in blocks.
 *
 * This only seems to happen on very heavily loaded systems, and
 * not very often.
 */
scrapbad()
{
	register line *ip;
	struct stat stbuf;
	off_t size, maxt;
	int bno, cnt, bad, was;
	char bk[BUFSIZ];

	ignore(fstat(tfile, &stbuf));
	size = stbuf.st_size;
D 2
	maxt = (size >> SHFT) | 7;
E 2
I 2
	maxt = (size >> SHFT) | (BNDRY-1);
E 2
	bno = (maxt >> OFFBTS) & BLKMSK;
#ifdef DEBUG
D 21
	fprintf(stderr, "size %ld, maxt %o, bno %d\n", size, maxt, bno);
E 21
I 21
	fpr("size %ld, maxt %o, bno %d\n", size, maxt, bno);
E 21
#endif

	/*
	 * Look for a null separating two lines in the temp file;
	 * if last line was split across blocks, then it is lost
	 * if the last block is.
	 */
	while (bno > 0) {
		ignorl(lseek(tfile, (long) BUFSIZ * bno, 0));
		cnt = read(tfile, (char *) bk, BUFSIZ);
		while (cnt > 0)
			if (bk[--cnt] == 0)
				goto null;
		bno--;
	}
null:

	/*
	 * Magically calculate the largest valid pointer in the temp file,
	 * consing it up from the block number and the count.
	 */
	maxt = ((bno << OFFBTS) | (cnt >> SHFT)) & ~1;
#ifdef DEBUG
D 21
	fprintf(stderr, "bno %d, cnt %d, maxt %o\n", bno, cnt, maxt);
E 21
I 21
	fpr("bno %d, cnt %d, maxt %o\n", bno, cnt, maxt);
E 21
#endif

	/*
	 * Now cycle through the line pointers,
	 * trashing the Lusers.
	 */
	was = bad = 0;
	for (ip = one; ip <= dol; ip++)
		if (*ip > maxt) {
#ifdef DEBUG
D 21
			fprintf(stderr, "%d bad, %o > %o\n", ip - zero, *ip, maxt);
E 21
I 21
			fpr("%d bad, %o > %o\n", ip - zero, *ip, maxt);
E 21
#endif
			if (was == 0)
				was = ip - zero;
D 2
			*ip = 504 >> SHFT;
E 2
I 2
			*ip = ((HBLKS*BUFSIZ)-8) >> SHFT;
E 2
		} else if (was) {
			if (bad == 0)
D 21
				fprintf(stderr, " [Lost line(s):");
			fprintf(stderr, " %d", was);
E 21
I 21
				fpr(" [Lost line(s):");
			fpr(" %d", was);
E 21
			if ((ip - 1) - zero > was)
D 21
				fprintf(stderr, "-%d", (ip - 1) - zero);
E 21
I 21
				fpr("-%d", (ip - 1) - zero);
E 21
			bad++;
			was = 0;
		}
	if (was != 0) {
		if (bad == 0)
D 21
			fprintf(stderr, " [Lost line(s):");
		fprintf(stderr, " %d", was);
E 21
I 21
			fpr(" [Lost line(s):");
		fpr(" %d", was);
E 21
		if (dol - zero != was)
D 21
			fprintf(stderr, "-%d", dol - zero);
E 21
I 21
			fpr("-%d", dol - zero);
E 21
		bad++;
	}
	if (bad)
D 21
		fprintf(stderr, "]");
E 21
I 21
		fpr("]");
E 21
}

/*
 * Aw shucks, if we only had a (void) cast.
 */
#ifdef lint
Ignorl(a)
	long a;
{

	a = a;
}

Ignore(a)
	char *a;
{

	a = a;
}

Ignorf(a)
	int (*a)();
{

	a = a;
}

ignorl(a)
	long a;
{

	a = a;
}
#endif

int	cntch, cntln, cntodd, cntnull;
/*
 * Following routines stolen mercilessly from ex.
 */
putfile()
{
	line *a1;
	register char *fp, *lp;
	register int nib;

	a1 = addr1;
	clrstats();
	cntln = addr2 - a1 + 1;
	if (cntln == 0)
		return;
	nib = BUFSIZ;
	fp = genbuf;
	do {
		getline(*a1++);
		lp = linebuf;
		for (;;) {
			if (--nib < 0) {
				nib = fp - genbuf;
				if (write(io, genbuf, nib) != nib)
					wrerror();
				cntch += nib;
				nib = 511;
				fp = genbuf;
			}
			if ((*fp++ = *lp++) == 0) {
				fp[-1] = '\n';
				break;
			}
		}
	} while (a1 <= addr2);
	nib = fp - genbuf;
	if (write(io, genbuf, nib) != nib)
		wrerror();
	cntch += nib;
}

wrerror()
{

	syserror();
}

clrstats()
{

	ninbuf = 0;
	cntch = 0;
	cntln = 0;
	cntnull = 0;
	cntodd = 0;
}

#define	READ	0
#define	WRITE	1

getline(tl)
	line tl;
{
	register char *bp, *lp;
	register int nl;

	lp = linebuf;
	bp = getblock(tl, READ);
	nl = nleft;
	tl &= ~OFFMSK;
	while (*lp++ = *bp++)
		if (--nl == 0) {
			bp = getblock(tl += INCRMT, READ);
			nl = nleft;
		}
}

int	read();
int	write();

char *
getblock(atl, iof)
	line atl;
	int iof;
{
	register int bno, off;
	
	bno = (atl >> OFFBTS) & BLKMSK;
	off = (atl << SHFT) & LBTMSK;
	if (bno >= NMBLKS)
		error(" Tmp file too large");
	nleft = BUFSIZ - off;
	if (bno == iblock) {
		ichanged |= iof;
		return (ibuff + off);
	}
	if (bno == oblock)
		return (obuff + off);
	if (iof == READ) {
		if (ichanged)
			blkio(iblock, ibuff, write);
		ichanged = 0;
		iblock = bno;
		blkio(bno, ibuff, read);
		return (ibuff + off);
	}
	if (oblock >= 0)
		blkio(oblock, obuff, write);
	oblock = bno;
	return (obuff + off);
}

blkio(b, buf, iofcn)
	short b;
	char *buf;
	int (*iofcn)();
{

	lseek(tfile, (long) (unsigned) b * BUFSIZ, 0);
D 2
	if ((*iofcn)(tfile, buf, BUFSIZ) != 512)
E 2
I 2
	if ((*iofcn)(tfile, buf, BUFSIZ) != BUFSIZ)
E 2
		syserror();
}

syserror()
{
D 20
	extern int sys_nerr;
	extern char *sys_errlist[];
E 20
I 20
	char *strerror();
E 20

	dirtcnt = 0;
	write(2, " ", 1);
D 20
	if (errno >= 0 && errno <= sys_nerr)
		error(sys_errlist[errno]);
	else
		error("System error %d", errno);
E 20
I 20
	error(strerror(errno));
E 20
	exit(1);
}
I 15

/*
 * Must avoid stdio because expreserve uses sbrk to do memory
 * allocation and stdio uses malloc.
 */
D 21
fprintf(fp, fmt, a1, a2, a3, a4, a5)
	FILE *fp;
E 21
I 21
D 23
fpr(fmt)
E 23
I 23
void
#if __STDC__
fpr(const char *fmt, ...)
#else
fpr(fmt, va_alist)
E 23
E 21
	char *fmt;
I 23
	va_dcl
#endif
E 23
D 21
	char *a1, *a2, *a3, *a4, *a5;
E 21
{
I 21
	va_list ap;
D 24
	int len;
E 24
E 21
	char buf[BUFSIZ];

I 23
#if __STDC__
E 23
D 21
	if (fp != stderr)
		return;
	sprintf(buf, fmt, a1, a2, a3, a4, a5);
	write(2, buf, strlen(buf));
E 21
I 21
	va_start(ap, fmt);
I 23
#else
	va_start(ap);
#endif
E 23
D 24
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
E 24
I 24
	(void)vsnprintf(buf, sizeof(buf), fmt, ap);
E 24
	va_end(ap);
D 24
	write(2, buf, len);
E 24
I 24
	write(2, buf, strlen(buf));
E 24
E 21
}
E 15
E 1
