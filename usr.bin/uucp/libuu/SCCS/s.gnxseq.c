h41709
s 00002/00002/00127
d D 8.1 93/06/06 22:10:53 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00121
d D 5.5 91/04/24 17:33:47 bostic 5 4
c new copyright; att/bsd/shared
e
s 00006/00008/00116
d D 5.4 85/06/20 09:51:37 bloom 4 3
c fixes from rick adams
e
s 00016/00002/00108
d D 5.3 85/01/22 14:08:59 ralph 3 2
c bug fixes and changes from Rick Adams
e
s 00001/00001/00109
d D 5.2 83/07/02 18:25:13 sam 2 1
c include fixes
e
s 00110/00000/00000
d D 5.1 83/07/02 17:57:04 sam 1 0
c date and time created 83/07/02 17:57:04 by sam
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5

#include "uucp.h"
D 4
#include <sys/types.h>
E 4
I 3
#ifdef BSD4_2
E 3
D 2
#include <time.h>
E 2
I 2
#include <sys/time.h>
I 3
#else sane
#include <time.h>
#endif sane
E 3
E 2

I 4
/*LINTLIBRARY*/

E 4
I 3
#ifdef GNXSEQ

E 3
D 4
extern	time_t	time();

/*******
 *	gnxseq(rmtname)		get next conversation sequence number
 *	char *rmtname;
E 4
I 4
/*
 *	get next conversation sequence number
E 4
 *
 *	return - 0 no entry | >0 sequence number
 */

gnxseq(rmtname)
char *rmtname;
{
	int count = 0, ct, ret, i;
	register struct tm *tp;
	extern struct tm *localtime();
	time_t clock;
	register FILE *fp0, *fp1;
	char buf[BUFSIZ], name[NAMESIZE];

	if (access(SQFILE, 0) != 0)	/* nothing to do here */
		return(0);

	for (i = 0; i < 5; i++) {
		if ((ret = ulockf(SQLOCK, (time_t)  SQTIME)) == 0)
			break;
		sleep(5);
	}
	if (ret != 0) {
		logent("CAN'T LOCK", SQLOCK);
		DEBUG(4, "can't lock %s\n", SQLOCK);
		return(0);
	}
	if ((fp0 = fopen(SQFILE, "r")) == NULL)
		return(0);
	if ((fp1 = fopen(SQTMP, "w")) == NULL) {
		fclose(fp0);
		return(0);
	}
	chmod(SQTMP, 0400);

	while (fgets(buf, BUFSIZ, fp0) != NULL) {
		ret = sscanf(buf, "%s%d", name, &ct);
		if (ret < 2)
			ct = 0;
D 4
		name[7] = '\0';
E 4
I 4
		name[MAXBASENAME] = '\0';
E 4
		if (ct > 9998)
			ct = 0;
D 4
		if (strcmp(rmtname, name) != SAME) {
E 4
I 4
		if (strncmp(rmtname, name, MAXBASENAME) != SAME) {
E 4
			fputs(buf, fp1);
			continue;
		}

		/*  found name  */
		count = ++ct;
		time(&clock);
		tp = localtime(&clock);
D 3
		fprintf(fp1, "%s %d %d/%d-%d:%02d\n", name, ct,
E 3
I 3
#ifdef USG
		fprintf(fp1, "%s %d %d/%d-%2.2d:%2.2d\n", name, ct,
E 3
		  tp->tm_mon + 1, tp->tm_mday, tp->tm_hour,
		  tp->tm_min);
I 3
#endif
#ifndef USG
		fprintf(fp1, "%s %d %d/%d-%02d:%02d\n", name, ct,
		  tp->tm_mon + 1, tp->tm_mday, tp->tm_hour,
		  tp->tm_min);
#endif
E 3
		while (fgets(buf, BUFSIZ, fp0) != NULL)
			fputs(buf, fp1);
	}
	fclose(fp0);
	fclose(fp1);
	if (count == 0) {
		rmlock(SQLOCK);
		unlink(SQTMP);
	}
	return(count);
}


/***
 *	cmtseq()	commit sequence update
 *
 *	return  0  ok | other - link failed
 */

cmtseq()
{
	register int ret;

D 3
	if ((ret = access(SQTMP, 0400)) != 0) {
E 3
I 3
	if ((ret = access(SQTMP, 04)) != 0) {
E 3
		rmlock(SQLOCK);
		return(0);
	}
	unlink(SQFILE);
	ret = link(SQTMP, SQFILE);
	unlink(SQTMP);
	rmlock(SQLOCK);
	return(ret);
}

/***
 *	ulkseq()	unlock sequence file
 */

ulkseq()
{
	unlink(SQTMP);
	rmlock(SQLOCK);
}
I 3
#endif GNXSEQ
E 3
E 1
