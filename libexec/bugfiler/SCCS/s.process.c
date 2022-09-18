h13276
s 00002/00002/00087
d D 8.1 93/06/04 18:46:22 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00005/00077
d D 5.10 93/05/17 10:04:10 bostic 10 9
c lint, ANSI C prototypes, index->strchr
e
s 00009/00005/00073
d D 5.9 91/02/25 16:23:11 bostic 9 8
c ANSI fixes (two real bug fixes!), convert to struct dirent, cleanups
e
s 00001/00011/00077
d D 5.8 90/06/01 15:50:06 bostic 8 7
c new copyright notice
e
s 00010/00015/00078
d D 5.7 89/07/16 13:39:30 bostic 7 6
c minor (really minor) cleanup
e
s 00010/00005/00083
d D 5.6 88/06/29 21:43:11 bostic 6 5
c install approved copyright notice
e
s 00011/00005/00077
d D 5.5 88/02/01 16:16:33 bostic 5 4
c add Berkeley specific header
e
s 00001/00001/00081
d D 5.4 87/04/23 14:28:35 bostic 4 3
c Comment field is now Status
e
s 00039/00037/00043
d D 5.3 87/04/11 15:38:43 bostic 3 2
c version #2; -f flag, remove home_dir, redist per folder
e
s 00009/00002/00071
d D 5.2 87/01/28 12:03:59 bostic 2 1
c added date to logging, changed Status field to Comment field
e
s 00073/00000/00000
d D 5.1 86/11/25 13:36:09 bostic 1 0
c date and time created 86/11/25 13:36:09 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 11
 * Copyright (c) 1986, 1987 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
E 5
 */

#ifndef lint
D 5
static char sccsid[] = "%W% (Berkeley) %E%";
#endif not lint
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

D 9
#include <bug.h>
#include <sys/file.h>
E 9
I 9
#include <sys/param.h>
E 9
D 3
#include <sys/dir.h>
E 3
I 2
#include <sys/time.h>
I 9
D 10
#include <fcntl.h>
E 10
I 10

#include <ctype.h>
E 10
#include <dirent.h>
D 10
#include <unistd.h>
E 10
I 10
#include <fcntl.h>
E 10
E 9
E 2
#include <stdio.h>
I 3
D 10
#include <ctype.h>
E 10
I 9
#include <stdlib.h>
I 10
#include <unistd.h>

E 10
#include "bug.h"
I 10
#include "extern.h"
E 10
E 9
E 3

D 3
extern HEADER	mailhead[];			/* mail headers */
extern int	lfd;				/* lock file descriptor */
extern char	dir[],				/* directory */
		folder[];			/* sub-directory */

E 3
char	pfile[MAXPATHLEN];			/* permanent file name */

I 10
static int getnext __P((void));

E 10
/*
 * process --
D 3
 *	process a bug report
E 3
I 3
 *	copy report to permanent file,
 *	update summary file.
E 3
 */
I 10
int
E 10
process()
{
	register int	rval;			/* read return value */
I 2
	struct timeval	tp;			/* time of day */
D 3
	struct timezone	tzp;
E 3
I 3
	int	lfd;				/* lock file descriptor */
E 3
D 9
	char	*ctime();
E 9
I 9
D 10
	static int getnext();
E 10
E 9
E 2

D 3
	/* copy report to permanent file */
	sprintf(pfile,"%s/%s/%d",dir,folder,getnext());
	fprintf(stderr,"\t%s\n",pfile);
	if (!(freopen(pfile,"w",stdout)))
		error("unable to create permanent bug file %s.",pfile);
E 3
I 3
	if (access(LOCK_FILE, R_OK) || (lfd = open(LOCK_FILE, O_RDONLY, 0)) < 0)
		error("can't find lock file %s.", LOCK_FILE);
	if (flock(lfd, LOCK_EX))
		error("can't get lock.", CHN);
	sprintf(pfile, "%s/%s/%d", dir, folder, getnext());
	fprintf(stderr, "\t%s\n", pfile);
	if (!(freopen(pfile, "w", stdout)))
		error("can't create %s.", pfile);
E 3
	rewind(stdin);
D 3
	while ((rval = read(fileno(stdin),bfr,sizeof(bfr))) != ERR && rval)
		write(fileno(stdout),bfr,rval);
	REL_LOCK;
E 3
I 3
	while ((rval = read(fileno(stdin), bfr, sizeof(bfr))) != ERR && rval)
		if (write(fileno(stdout), bfr, rval) != rval)
			error("write to %s failed.", pfile);
E 3

	/* append information to the summary file */
D 3
	sprintf(bfr,"%s/%s",dir,SUMMARY_FILE);
	GET_LOCK;
	if (!(freopen(bfr,"a",stdout)))
		error("unable to append to summary file %s.",bfr);
D 2
	else
		printf("\n%s\n\t%s\t%s\tOwner: Bugs Bunny\n\tStatus: Received\n",pfile,mailhead[INDX_TAG].line,mailhead[SUBJ_TAG].found ? mailhead[SUBJ_TAG].line : "Subject:\n");
E 2
I 2
	else {
		if (gettimeofday(&tp,&tzp))
			error("unable to get time of day.",CHN);
		printf("\n%s\t\t%s\t%s\t%s\tOwner: Bugs Bunny\n\tComment: Received\n",pfile,ctime(&tp.tv_sec),mailhead[INDX_TAG].line,mailhead[SUBJ_TAG].found ? mailhead[SUBJ_TAG].line : "Subject:\n");
	}
E 2
	REL_LOCK;
	fclose(stdout);
E 3
I 3
	sprintf(bfr, "%s/%s", dir, SUMMARY_FILE);
	if (!(freopen(bfr, "a", stdout)))
		error("can't append to summary file %s.", bfr);
	if (gettimeofday(&tp, (struct timezone *)NULL))
		error("can't get time of day.", CHN);
D 4
	printf("\n%s\t\t%s\t%s\t%s\tOwner: Bugs Bunny\n\tComment: Received\n", pfile, ctime(&tp.tv_sec), mailhead[INDX_TAG].line, mailhead[SUBJ_TAG].found ? mailhead[SUBJ_TAG].line : "Subject:\n");
E 4
I 4
D 10
	printf("\n%s\t\t%s\t%s\t%s\tOwner: Bugs Bunny\n\tStatus: Received\n", pfile, ctime(&tp.tv_sec), mailhead[INDX_TAG].line, mailhead[SUBJ_TAG].found ? mailhead[SUBJ_TAG].line : "Subject:\n");
E 10
I 10
	printf("\n%s\t\t%s\t%s\t%s\tOwner: Bugs Bunny\n\tStatus: Received\n",
	    pfile, ctime(&tp.tv_sec), mailhead[INDX_TAG].line,
	    mailhead[SUBJ_TAG].found ? mailhead[SUBJ_TAG].line : "Subject:\n");
E 10
E 4
	(void)flock(lfd, LOCK_UN);
	(void)fclose(stdout);
E 3
}

/*
 * getnext --
 *	get next file name (number)
 */
D 9
static
E 9
I 9
static int
E 9
getnext()
{
D 7
	register struct direct	*d;		/* directory structure */
	register DIR	*dirp;			/* directory pointer */
D 3
	register int	n;			/* number values */
E 3
I 3
	register int	highval,
			newval;
	register char	*C;
E 7
I 7
D 9
	register struct direct *d;		/* directory structure */
E 9
I 9
	register struct dirent *d;		/* directory structure */
E 9
	register DIR *dirp;			/* directory pointer */
	register int highval, newval;
	register char *p;
E 7
E 3

D 3
	GET_LOCK;
	sprintf(bfr,"%s/%s",dir,folder);
	if (!(dirp = opendir(bfr))) {
		REL_LOCK;
		error("unable to read folder directory %s.",bfr);
	}
	for (n = 0;d = readdir(dirp);)
		n = MAX(n,atoi(d->d_name));
E 3
I 3
D 7
	sprintf(bfr, "%s/%s", dir, folder);
E 7
I 7
	(void)sprintf(bfr, "%s/%s", dir, folder);
E 7
	if (!(dirp = opendir(bfr)))
		error("can't read folder directory %s.", bfr);
D 7
	for (highval = 0;d = readdir(dirp);)
		for (C = d->d_name;;++C)
			if (!*C) {
				if ((newval = atoi(d->d_name)) > highval)
					highval = newval;
				break;
			}
			else if (!isdigit(*C))
				break;
E 7
I 7
	for (highval = -1; d = readdir(dirp);) {
		for (p = d->d_name; *p && isdigit(*p); ++p);
		if (!*p && (newval = atoi(d->d_name)) > highval)
			highval = newval;
	}
E 7
E 3
	closedir(dirp);
D 3
	return(++n);
E 3
I 3
	return(++highval);
E 3
}
E 1
