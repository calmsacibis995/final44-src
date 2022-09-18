h44739
s 00002/00002/00243
d D 8.1 93/06/05 10:52:42 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00245
d D 5.17 93/05/11 13:50:16 torek 30 29
c lint (calloc declaration is provided elsewhere)
e
s 00023/00017/00226
d D 5.16 93/01/25 15:36:06 mckusick 29 28
c cleanups from leres@lbl
e
s 00000/00002/00243
d D 5.15 92/06/18 13:39:51 mckusick 28 27
c parametric routines in dump.h
e
s 00005/00009/00240
d D 5.14 92/06/18 13:30:24 mckusick 27 26
c lint
e
s 00001/00000/00248
d D 5.13 92/05/26 10:07:04 mckusick 26 25
c add <sys/time.h> for dinode.h
e
s 00002/00002/00246
d D 5.12 92/03/05 18:07:21 leres 25 24
c While we're at it, it's safer to use sizeof than a defined buffer size.
e
s 00006/00006/00242
d D 5.11 92/03/05 18:04:32 leres 24 23
c Rename buf -> tbuf to avoid gcc warnings about the buf defined in dump.h.
e
s 00001/00001/00247
d D 5.10 91/11/10 13:05:05 bostic 23 22
c break UFS up into FFS/UFS/LFS/MFS
e
s 00012/00000/00236
d D 5.9 91/07/23 15:58:07 mckusick 22 21
c temporarily add ifdef sunos (includes) to assist Steve Romig in debugging
e
s 00019/00006/00217
d D 5.8 91/07/23 15:05:23 mckusick 21 20
c try to create a `dumpdates' file if it does not exist
e
s 00005/00004/00218
d D 5.7 91/03/07 17:50:04 mckusick 20 19
c verified to be free of AT&T code
e
s 00013/00002/00209
d D 5.6 91/02/28 19:33:49 bostic 19 18
c ANSI; break #includes out of dump.h into separate files
e
s 00093/00104/00118
d D 5.5 91/02/28 18:53:19 mckusick 18 17
c KNF, more neumonic names for structures
e
s 00042/00072/00180
d D 5.4 91/02/23 16:16:19 torek 17 16
c warn about missing /etc/dumpdates, and detect errors when rewriting;
c perror => strerror; fix gcc warnings; quit via new quit() function;
c dump size estimate functions move to dumptraverse.c
e
s 00001/00009/00251
d D 5.3 89/08/22 14:04:36 mckusick 16 15
c the whole map is always dumped anyway, so just calculate its size
c and be done with it (allegra!jpl@research.att.com)
e
s 00052/00057/00208
d D 5.2 86/05/28 10:38:41 mckusick 15 14
c update /etc/dumpdates in place
e
s 00009/00001/00256
d D 5.1 85/06/05 08:45:26 dist 14 13
c Add copyright
e
s 00024/00007/00233
d D 1.13 84/03/28 19:03:30 mckusick 13 12
c better estimate for files with holes using "di_blocks"
e
s 00001/00000/00239
d D 1.12 83/09/13 18:26:58 mckusick 12 11
c initialize last dump time to the epoch (shannon)
e
s 00006/00002/00233
d D 1.11 83/06/15 15:11:32 sam 11 10
c defines changed
e
s 00001/00000/00234
d D 1.10 83/06/09 12:50:21 mckusick 10 9
c print out correct previous incremental number
e
s 00025/00044/00209
d D 1.9 83/05/19 19:26:05 mckusick 9 8
c introduce true locking on /etc/dumpdates; 
c get rid of -J option that converts from /etc/ddates to /etc/dumpdates
e
s 00006/00000/00247
d D 1.8 83/05/19 18:01:05 mckusick 8 7
c re-read /etc/dumpdates before updating it
e
s 00001/00001/00246
d D 1.7 82/12/02 17:52:19 mckusick 7 6
c fix to properly dump 4096/512 byte file systems
e
s 00001/00001/00246
d D 1.6 82/10/14 12:51:33 mckusick 6 5
c fix to properly dump file systems with 512 byte frags
e
s 00001/00001/00246
d D 1.5 82/02/25 14:55:58 mckusic 5 4
c use speed-up macros in fs.h
e
s 00012/00013/00235
d D 1.4 82/01/05 01:37:11 mckusic 4 3
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00004/00003/00244
d D 1.3 81/11/07 14:53:08 mckusic 3 2
c dump to "standard" (ie 1K file system) dump tapes
e
s 00010/00008/00237
d D 1.2 81/10/31 18:29:59 mckusic 2 1
c 8K only dump/restor
e
s 00245/00000/00000
d D 1.1 80/10/13 17:30:25 root 1 0
c date and time created 80/10/13 17:30:25 by root
e
u
U
t
T
I 1
D 14
static	char *sccsid = "%W% (Berkeley) %G%";
E 14
I 14
D 20
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
/*-
D 31
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
 * %sccs.include.redist.c%
E 20
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17
E 14
I 9

I 22
D 29
#ifdef sunos
#include <stdio.h>
#include <ctype.h>
E 29
E 22
E 9
D 19
#include "dump.h"
I 9
#include <sys/file.h>
E 19
I 19
#include <sys/param.h>
I 22
D 29
#include <sys/stat.h>
E 29
I 29
#include <sys/time.h>
#ifdef sunos
#include <sys/vnode.h>

#include <ufs/fsdir.h>
#include <ufs/inode.h>
E 29
D 27
#include <sys/time.h>
#include <sys/dir.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 27
#include <ufs/fs.h>
#else
D 29
#include <sys/param.h>
I 26
#include <sys/time.h>
E 26
E 22
D 21
#include <ufs/dir.h>
E 21
D 23
#include <ufs/dinode.h>
E 23
I 23
D 27
#include <ufs/ufs/dinode.h>
E 27
E 23
I 22
#endif
E 29
I 27
#include <ufs/ufs/dinode.h>
E 27
E 22
D 29
#include <fcntl.h>
E 29
I 29
#endif

E 29
#include <protocols/dumprestore.h>
I 29

E 29
E 19
I 17
#include <errno.h>
I 29
#include <fcntl.h>
E 29
I 19
#include <stdio.h>
#ifdef __STDC__
D 29
#include <time.h>
#include <unistd.h>
E 29
#include <stdlib.h>
#include <string.h>
I 29
#include <unistd.h>
E 29
#endif
I 29

E 29
#include "dump.h"
E 19
E 17
E 9

D 17
char *prdate(d)
E 17
I 17
D 18
char *
prdate(d)
E 17
	time_t d;
{
	char *p;
E 18
I 18
struct	dumpdates **ddatev = 0;
int	nddates = 0;
int	ddates_in = 0;
struct	dumptime *dthead = 0;
E 18

D 18
	if(d == 0)
		return("the epoch");
	p = ctime(&d);
	p[24] = 0;
	return(p);
}

struct	idates	**idatev = 0;
int	nidates = 0;
int	idates_in = 0;
struct	itime	*ithead = 0;

I 17
void	readitimes();
E 18
I 18
D 29
void	readdumptimes();
E 18
int	getrecord();
D 18
int	makeidate();
E 18
I 18
int	makedumpdate();
E 29
I 29
static	void dumprecout __P((FILE *, struct dumpdates *));
static	int getrecord __P((FILE *, struct dumpdates *));
static	int makedumpdate __P((struct dumpdates *, char *));
static	void readdumptimes __P((FILE *));
E 29
E 18

D 18
static void recout();
E 18
I 18
D 29
static void dumprecout();
E 29
I 29
D 30
#ifdef COMPAT
extern	char *calloc();
#endif
E 29
E 18

E 30
void
E 17
D 18
inititimes()
E 18
I 18
initdumptimes()
E 18
{
D 15
			FILE	*df;
	register	int	i;
	register	struct	itime	*itwalk;
I 9
			int fd;
E 15
I 15
	FILE *df;
E 15
E 9

D 15
	if (idates_in)
		return;
D 9
	if ( (df = fopen(increm, "r")) == NULL){
E 9
I 9
D 11
	if ((fd = open(increm, FSHLOCK|FRDONLY, 0600)) < 0) {
E 11
I 11
	fd = open(increm, O_RDONLY);
	if (fd < 0) {
E 15
I 15
D 18
	if ((df = fopen(increm, "r")) == NULL) {
E 18
I 18
	if ((df = fopen(dumpdates, "r")) == NULL) {
E 18
E 15
E 11
D 17
		perror(increm);
		return;
E 17
I 17
D 21
		if (errno == ENOENT) {
D 18
			msg("WARNING: no file `%s'\n", increm);
E 18
I 18
			msg("WARNING: no file `%s'\n", dumpdates);
E 18
			return;
E 21
I 21
		if (errno != ENOENT) {
			quit("cannot read %s: %s\n", dumpdates,
			    strerror(errno));
			/* NOTREACHED */
E 21
		}
D 18
		quit("cannot read %s: %s\n", increm, strerror(errno));
E 18
I 18
D 21
		quit("cannot read %s: %s\n", dumpdates, strerror(errno));
E 18
		/* NOTREACHED */
E 21
I 21
		/*
		 * Dumpdates does not exist, make an empty one.
		 */
		msg("WARNING: no file `%s', making an empty one\n", dumpdates);
		if ((df = fopen(dumpdates, "w")) == NULL) {
			quit("cannot create %s: %s\n", dumpdates,
			    strerror(errno));
			/* NOTREACHED */
		}
		(void) fclose(df);
		if ((df = fopen(dumpdates, "r")) == NULL) {
			quit("cannot read %s even after creating it: %s\n",
			    dumpdates, strerror(errno));
			/* NOTREACHED */
		}
E 21
E 17
	}
I 11
D 15
	(void) flock(fd, LOCK_SH);
E 11
	if ((df = fdopen(fd, "r")) == NULL) {
E 9
		nidates = 0;
		ithead = 0;
	} else {
		do{
			itwalk=(struct itime *)calloc(1,sizeof (struct itime));
			if (getrecord(df, &(itwalk->it_value)) < 0)
				break;
			nidates++;
			itwalk->it_next = ithead;
			ithead = itwalk;
		} while (1);
		fclose(df);
E 15
I 15
	(void) flock(fileno(df), LOCK_SH);
D 18
	readitimes(df);
E 18
I 18
	readdumptimes(df);
E 18
D 27
	fclose(df);
E 27
I 27
	(void) fclose(df);
E 27
}

I 17
D 29
void
E 29
I 29
static void
E 29
E 17
D 18
readitimes(df)
E 18
I 18
readdumptimes(df)
E 18
	FILE *df;
{
D 18
	register	int	i;
	register	struct	itime	*itwalk;
E 18
I 18
	register int i;
	register struct	dumptime *dtwalk;
E 18

	for (;;) {
D 18
		itwalk = (struct itime *)calloc(1, sizeof (struct itime));
		if (getrecord(df, &(itwalk->it_value)) < 0)
E 18
I 18
		dtwalk = (struct dumptime *)calloc(1, sizeof (struct dumptime));
		if (getrecord(df, &(dtwalk->dt_value)) < 0)
E 18
			break;
D 18
		nidates++;
		itwalk->it_next = ithead;
		ithead = itwalk;
E 18
I 18
		nddates++;
		dtwalk->dt_next = dthead;
		dthead = dtwalk;
E 18
E 15
	}

D 18
	idates_in = 1;
E 18
I 18
	ddates_in = 1;
E 18
	/*
	 *	arrayify the list, leaving enough room for the additional
D 18
	 *	record that we may have to add to the idate structure
E 18
I 18
	 *	record that we may have to add to the ddate structure
E 18
	 */
D 18
	idatev = (struct idates **)calloc(nidates + 1,sizeof (struct idates *));
D 15
	for (i = nidates-1, itwalk = ithead; i >= 0; i--, itwalk = itwalk->it_next)
E 15
I 15
	itwalk = ithead;
	for (i = nidates - 1; i >= 0; i--, itwalk = itwalk->it_next)
E 15
		idatev[i] = &itwalk->it_value;
E 18
I 18
	ddatev = (struct dumpdates **)
D 27
		calloc(nddates + 1, sizeof (struct dumpdates *));
E 27
I 27
		calloc((unsigned) (nddates + 1), sizeof (struct dumpdates *));
E 27
	dtwalk = dthead;
	for (i = nddates - 1; i >= 0; i--, dtwalk = dtwalk->dt_next)
		ddatev[i] = &dtwalk->dt_value;
E 18
}

I 17
void
E 17
D 18
getitime()
E 18
I 18
getdumptime()
E 18
{
D 18
	register	struct	idates	*ip;
	register	int	i;
			char	*fname;
E 18
I 18
	register struct dumpdates *ddp;
	register int i;
	char *fname;
E 18

	fname = disk;
#ifdef FDEBUG
D 18
	msg("Looking for name %s in increm = %s for delta = %c\n",
		fname, increm, incno);
E 18
I 18
	msg("Looking for name %s in dumpdates = %s for level = %c\n",
		fname, dumpdates, level);
E 18
#endif
	spcl.c_ddate = 0;
I 12
D 18
	lastincno = '0';
E 18
I 18
	lastlevel = '0';
E 18
E 12

D 18
	inititimes();
E 18
I 18
	initdumptimes();
E 18
	/*
	 *	Go find the entry with the same name for a lower increment
	 *	and older date
	 */
D 15
	ITITERATE(i, ip){
		if(strncmp(fname, ip->id_name,
				sizeof (ip->id_name)) != 0)
E 15
I 15
D 18
	ITITERATE(i, ip) {
		if (strncmp(fname, ip->id_name, sizeof (ip->id_name)) != 0)
E 18
I 18
	ITITERATE(i, ddp) {
		if (strncmp(fname, ddp->dd_name, sizeof (ddp->dd_name)) != 0)
E 18
E 15
			continue;
D 18
		if (ip->id_incno >= incno)
E 18
I 18
		if (ddp->dd_level >= level)
E 18
			continue;
D 18
		if (ip->id_ddate <= spcl.c_ddate)
E 18
I 18
		if (ddp->dd_ddate <= spcl.c_ddate)
E 18
			continue;
D 18
		spcl.c_ddate = ip->id_ddate;
I 10
D 15
 		lastincno = ip->id_incno;
E 10
	} 
E 15
I 15
		lastincno = ip->id_incno;
E 18
I 18
		spcl.c_ddate = ddp->dd_ddate;
		lastlevel = ddp->dd_level;
E 18
	}
E 15
}

I 17
void
E 17
D 18
putitime()
E 18
I 18
putdumptime()
E 18
{
D 18
	FILE		*df;
	register	struct	idates	*itwalk;
	register	int	i;
I 9
	int		fd;
E 9
	char		*fname;
E 18
I 18
	FILE *df;
	register struct dumpdates *dtwalk;
	register int i;
	int fd;
	char *fname;
E 18

	if(uflag == 0)
		return;
I 9
D 11
	if ((fd = open(temp, FCREATE|FEXLOCK|FRDWR, 0600)) < 0) {
E 11
I 11
D 15
	fd = open(temp, O_RDWR|O_CREAT, 0600);
	if (fd < 0) {
E 11
		perror(temp);
E 15
I 15
D 17
	if ((df = fopen(increm, "r+")) == NULL) {
		perror(increm);
E 15
		dumpabort();
	}
E 17
I 17
D 18
	if ((df = fopen(increm, "r+")) == NULL)
		quit("cannot rewrite %s: %s\n", increm, strerror(errno));
E 18
I 18
	if ((df = fopen(dumpdates, "r+")) == NULL)
		quit("cannot rewrite %s: %s\n", dumpdates, strerror(errno));
E 18
E 17
I 15
	fd = fileno(df);
E 15
I 11
	(void) flock(fd, LOCK_EX);
E 11
D 15
	if ((df = fdopen(fd, "w")) == NULL) {
		perror(temp);
		dumpabort();
	}
E 15
E 9
	fname = disk;
I 8
D 18
	free(idatev);
	idatev = 0;
	nidates = 0;
	ithead = 0;
	idates_in = 0;
D 15
	inititimes();
E 8

E 15
I 15
	readitimes(df);
E 18
I 18
D 27
	free(ddatev);
E 27
I 27
	free((char *)ddatev);
E 27
	ddatev = 0;
	nddates = 0;
	dthead = 0;
	ddates_in = 0;
	readdumptimes(df);
E 18
D 17
	if (fseek(df,0L,0) < 0) {   /* rewind() was redefined in dumptape.c */
		perror("fseek");
		dumpabort();
	}
E 17
I 17
	if (fseek(df, 0L, 0) < 0)
		quit("fseek: %s\n", strerror(errno));
E 17
E 15
	spcl.c_ddate = 0;
D 17
	ITITERATE(i, itwalk){
E 17
I 17
D 18
	ITITERATE(i, itwalk) {
E 17
		if (strncmp(fname, itwalk->id_name,
				sizeof (itwalk->id_name)) != 0)
E 18
I 18
	ITITERATE(i, dtwalk) {
		if (strncmp(fname, dtwalk->dd_name,
				sizeof (dtwalk->dd_name)) != 0)
E 18
			continue;
D 18
		if (itwalk->id_incno != incno)
E 18
I 18
		if (dtwalk->dd_level != level)
E 18
			continue;
		goto found;
	}
	/*
	 *	construct the new upper bound;
	 *	Enough room has been allocated.
	 */
D 18
	itwalk = idatev[nidates] =
		(struct idates *)calloc(1, sizeof(struct idates));
	nidates += 1;
E 18
I 18
	dtwalk = ddatev[nddates] =
D 25
		(struct dumpdates *)calloc(1, sizeof(struct dumpdates));
E 25
I 25
		(struct dumpdates *)calloc(1, sizeof (struct dumpdates));
E 25
	nddates += 1;
E 18
  found:
D 17
	strncpy(itwalk->id_name, fname, sizeof (itwalk->id_name));
E 17
I 17
D 18
	(void) strncpy(itwalk->id_name, fname, sizeof (itwalk->id_name));
E 17
	itwalk->id_incno = incno;
	itwalk->id_ddate = spcl.c_date;
E 18
I 18
	(void) strncpy(dtwalk->dd_name, fname, sizeof (dtwalk->dd_name));
	dtwalk->dd_level = level;
	dtwalk->dd_ddate = spcl.c_date;
E 18

D 9
	if ( (df = fopen(increm, "w")) == NULL){
		msg("Cannot open %s\n", increm);
		dumpabort();
	}
E 9
D 17
	ITITERATE(i, itwalk){
E 17
I 17
D 18
	ITITERATE(i, itwalk) {
E 17
		recout(df, itwalk);
E 18
I 18
	ITITERATE(i, dtwalk) {
		dumprecout(df, dtwalk);
E 18
	}
D 9
	fclose(df);
E 9
I 9
D 15
	if (rename(temp, increm) < 0) {
		perror("rename");
		(void) unlink(temp);
E 15
I 15
D 17
	if (ftruncate(fd, ftell(df))) {
		perror("ftruncate");
E 15
		dumpabort();
	}
E 17
I 17
	if (fflush(df))
D 18
		quit("%s: %s\n", increm, strerror(errno));
E 18
I 18
		quit("%s: %s\n", dumpdates, strerror(errno));
E 18
	if (ftruncate(fd, ftell(df)))
D 18
		quit("ftruncate (%s): %s\n", increm, strerror(errno));
E 18
I 18
		quit("ftruncate (%s): %s\n", dumpdates, strerror(errno));
E 18
E 17
D 15
	(void) chmod(increm, 0644);
E 15
	(void) fclose(df);
E 9
D 18
	msg("level %c dump on %s\n", incno, prdate(spcl.c_date));
E 18
I 18
	msg("level %c dump on %s", level,
		spcl.c_date == 0 ? "the epoch\n" : ctime(&spcl.c_date));
E 18
}

I 17
static void
E 17
D 18
recout(file, what)
	FILE	*file;
	struct	idates	*what;
E 18
I 18
dumprecout(file, what)
	FILE *file;
	struct dumpdates *what;
E 18
{
D 17
	fprintf(file, DUMPOUTFMT,
		what->id_name,
		what->id_incno,
		ctime(&(what->id_ddate))
	);
E 17
I 17

	if (fprintf(file, DUMPOUTFMT,
D 18
		    what->id_name,
		    what->id_incno,
		    ctime(&what->id_ddate)) < 0)
		quit("%s: %s\n", increm, strerror(errno));
E 18
I 18
		    what->dd_name,
		    what->dd_level,
		    ctime(&what->dd_ddate)) < 0)
		quit("%s: %s\n", dumpdates, strerror(errno));
E 18
E 17
}

int	recno;
D 17
int getrecord(df, idatep)
E 17
I 17
D 29
int
E 29
I 29

static int
E 29
D 18
getrecord(df, idatep)
E 17
	FILE	*df;
	struct	idates	*idatep;
E 18
I 18
getrecord(df, ddatep)
	FILE *df;
	struct dumpdates *ddatep;
E 18
{
D 18
	char		buf[BUFSIZ];
E 18
I 18
D 24
	char buf[BUFSIZ];
E 24
I 24
	char tbuf[BUFSIZ];
E 24
E 18

	recno = 0;
D 24
	if ( (fgets(buf, BUFSIZ, df)) != buf)
E 24
I 24
D 25
	if ( (fgets(tbuf, BUFSIZ, df)) != tbuf)
E 25
I 25
	if ( (fgets(tbuf, sizeof (tbuf), df)) != tbuf)
E 25
E 24
		return(-1);
	recno++;
D 18
	if (makeidate(idatep, buf) < 0)
E 18
I 18
D 24
	if (makedumpdate(ddatep, buf) < 0)
E 24
I 24
	if (makedumpdate(ddatep, tbuf) < 0)
E 24
E 18
		msg("Unknown intermediate format in %s, line %d\n",
D 9
			NINCREM, recno);
E 9
I 9
D 18
			increm, recno);
E 18
I 18
			dumpdates, recno);
E 18
E 9

#ifdef FDEBUG
D 18
	msg("getrecord: %s %c %s\n",
		idatep->id_name, idatep->id_incno, prdate(idatep->id_ddate));
E 18
I 18
	msg("getrecord: %s %c %s", ddatep->dd_name, ddatep->dd_level,
	    ddatep->dd_ddate == 0 ? "the epoch\n" : ctime(&ddatep->dd_ddate));
E 18
#endif
	return(0);
D 9
}

/*
 *	Convert from old format to new format
 *	Convert from /etc/ddate to /etc/dumpdates format
 */
o_nconvert()
{
	FILE	*oldfile;
	FILE	*newfile;
	struct	idates	idate;
	struct	idates	idatecopy;

	if( (newfile = fopen(NINCREM, "w")) == NULL){
		msg("%s: Can not open %s to update.\n", processname, NINCREM);
		Exit(X_ABORT);
	}
	if ( (oldfile = fopen(OINCREM, "r")) != NULL){
		while(!feof(oldfile)){
			if (fread(&idate, sizeof(idate), 1, oldfile) != 1)
				break;
			/*
			 *	The old format ddate did not have
			 *	the full special path name on it;
			 *	we add the prefix /dev/ to the
			 *	special name, although this may not be
			 *	always the right thing to do.
			 */
			idatecopy = idate;
			strcpy(idatecopy.id_name, "/dev/");
			strncat(idatecopy.id_name, idate.id_name,
				sizeof(idate.id_name) - sizeof ("/dev/"));
			recout(newfile, &idatecopy);
		}
	}
	fclose(oldfile);
	fclose(newfile);
E 9
}

D 28
time_t	unctime();

E 28
D 17
int makeidate(ip, buf)
E 17
I 17
D 29
int
E 29
I 29
static int
E 29
D 18
makeidate(ip, buf)
E 17
	struct	idates	*ip;
	char	*buf;
E 18
I 18
D 24
makedumpdate(ddp, buf)
E 24
I 24
makedumpdate(ddp, tbuf)
E 24
	struct dumpdates *ddp;
D 24
	char *buf;
E 24
I 24
	char *tbuf;
E 24
E 18
{
D 18
	char	un_buf[128];
E 18
I 18
	char un_buf[128];
E 18

D 18
	sscanf(buf, DUMPINFMT, ip->id_name, &ip->id_incno, un_buf);
	ip->id_ddate = unctime(un_buf);
	if (ip->id_ddate < 0)
E 18
I 18
D 24
	sscanf(buf, DUMPINFMT, ddp->dd_name, &ddp->dd_level, un_buf);
E 24
I 24
D 27
	sscanf(tbuf, DUMPINFMT, ddp->dd_name, &ddp->dd_level, un_buf);
E 27
I 27
	(void) sscanf(tbuf, DUMPINFMT, ddp->dd_name, &ddp->dd_level, un_buf);
E 27
E 24
	ddp->dd_ddate = unctime(un_buf);
	if (ddp->dd_ddate < 0)
E 18
		return(-1);
	return(0);
D 17
}

I 2
/*
D 4
 * This is an estimation of the size of the file.
E 4
I 4
 * This is an estimation of the number of TP_BSIZE blocks in the file.
E 4
D 13
 * It assumes that there are no unallocated blocks; hence
 * the estimate may be high
E 13
I 13
 * It estimates the number of blocks in files with holes by assuming
 * that all of the blocks accounted for by di_blocks are data blocks
 * (when some of the blocks are usually used for indirect pointers);
 * hence the estimate may be high.
E 13
 */
E 2
est(ip)
	struct dinode *ip;
{
D 13
	long s;
E 13
I 13
	long s, t;
E 13

I 13
D 15
 	/*
 	 * ip->di_size is the size of the file in bytes.
 	 * ip->di_blocks stores the number of sectors actually in the file.
 	 * If there are more sectors than the size would indicate, this just
 	 *	means that there are indirect blocks in the file or unused
	 *	sectors in the last file block;	we can safely ignore these
E 15
I 15
	/*
	 * ip->di_size is the size of the file in bytes.
	 * ip->di_blocks stores the number of sectors actually in the file.
	 * If there are more sectors than the size would indicate, this just
	 *	means that there are indirect blocks in the file or unused
	 *	sectors in the last file block; we can safely ignore these
E 15
	 *	(s = t below).
D 15
 	 * If the file is bigger than the number of sectors would indicate,
 	 *	then the file has holes in it.  In this case we must use the
 	 *	block count to estimate the number of data blocks used, but
 	 *	we use the actual size for estimating the number of indirect
 	 *	dump blocks (t vs. s in the indirect block calculation).
 	 */
E 15
I 15
	 * If the file is bigger than the number of sectors would indicate,
	 *	then the file has holes in it.	In this case we must use the
	 *	block count to estimate the number of data blocks used, but
	 *	we use the actual size for estimating the number of indirect
	 *	dump blocks (t vs. s in the indirect block calculation).
	 */
E 15
E 13
	esize++;
D 3
	s = (ip->di_size + BSIZE-1) / BSIZE;
E 3
I 3
D 4
	s = (ip->di_size + FSIZE-1) / FSIZE;
E 3
	esize += s;
I 3
	s /= FRAG;
E 3
D 2
	if(s > NADDR-3) {
		/*
		 *	This code is only appproximate.
		 *	it totally estimates low on doubly and triply indirect
		 *	files.
		 */
		s -= NADDR-3;
		s = (s + (BSIZE/sizeof(daddr_t))-1) / (BSIZE/sizeof(daddr_t));
E 2
I 2
	if (s > NDADDR) {
		s -= NDADDR;
		if (s > BSIZE / sizeof(daddr_t))
			esize++;
		s = (s + (BSIZE/sizeof(daddr_t)) - 1) / (BSIZE/sizeof(daddr_t));
E 2
D 3
		esize += s;
E 3
I 3
		esize += s * FRAG;
E 4
I 4
D 13
	/* calc number of TP_BSIZE blocks */
D 5
	s = roundup(ip->di_size, sblock->fs_fsize) / TP_BSIZE;
E 5
I 5
D 7
	s = fragroundup(sblock, ip->di_size) / TP_BSIZE;
E 7
I 7
	s = howmany(ip->di_size, TP_BSIZE);
E 13
I 13
D 15
 	s = howmany(dbtob(ip->di_blocks), TP_BSIZE);
 	t = howmany(ip->di_size, TP_BSIZE);
 	if ( s > t )
 		s = t;
E 15
I 15
	s = howmany(dbtob(ip->di_blocks), TP_BSIZE);
	t = howmany(ip->di_size, TP_BSIZE);
	if ( s > t )
		s = t;
E 15
E 13
E 7
E 5
	if (ip->di_size > sblock->fs_bsize * NDADDR) {
D 13
		/* calc number of indirect blocks on the dump tape */
D 6
		s += howmany(s - NDADDR * BLKING(sblock) * sblock->fs_frag,
E 6
I 6
		s += howmany(s - NDADDR * sblock->fs_bsize / TP_BSIZE,
E 13
I 13
		/* calculate the number of indirect blocks on the dump tape */
		s += howmany(t - NDADDR * sblock->fs_bsize / TP_BSIZE,
E 13
E 6
			TP_NINDIR);
E 4
E 3
	}
I 4
	esize += s;
E 4
}

bmapest(map)
D 4
short *map;
E 4
I 4
	char *map;
E 4
{
D 16
	register i, n;
E 16

D 16
	n = -1;
D 4
	for(i=0; i<MSIZ; i++)
E 4
I 4
	for (i = 0; i < msiz; i++)
E 4
		if(map[i])
			n = i;
	if(n < 0)
		return;
I 4
	n++;
E 16
E 4
	esize++;
D 3
	esize += (n + (BSIZE/sizeof(short))-1) / (BSIZE/sizeof(short));
E 3
I 3
D 4
	esize += (n + (BSIZE/sizeof(short))-1) / (BSIZE/sizeof(short)) * FRAG;
E 4
I 4
D 16
	esize += howmany(n * sizeof map[0], TP_BSIZE);
E 16
I 16
	esize += howmany(msiz * sizeof map[0], TP_BSIZE);
E 17
E 16
E 4
E 3
}
E 1
