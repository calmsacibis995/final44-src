h18592
s 00002/00002/00103
d D 8.1 93/06/04 18:46:24 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00008/00093
d D 5.13 93/05/17 10:04:11 bostic 14 13
c lint, ANSI C prototypes, index->strchr
e
s 00016/00007/00085
d D 5.12 91/04/01 08:50:00 bostic 13 12
c use fgets, not gets
e
s 00004/00002/00088
d D 5.11 91/02/25 16:23:12 bostic 12 11
c ANSI fixes (two real bug fixes!), convert to struct dirent, cleanups
e
s 00001/00011/00089
d D 5.10 90/06/01 15:50:11 bostic 11 10
c new copyright notice
e
s 00001/00000/00099
d D 5.9 89/05/11 09:57:28 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00089
d D 5.8 88/06/29 21:43:13 bostic 9 8
c install approved copyright notice
e
s 00008/00002/00086
d D 5.7 88/04/01 13:30:02 karels 8 7
c don't let sendmail add apparently-to lines (always have a To: line)
e
s 00011/00005/00077
d D 5.6 88/02/01 16:16:35 bostic 7 6
c add Berkeley specific header
e
s 00046/00045/00036
d D 5.5 87/12/12 18:14:41 bostic 6 4
c handle "all" keyword, minor cleanups
e
s 00047/00045/00036
d R 5.5 87/11/23 10:56:21 bostic 5 4
c add "all:" label
e
s 00002/00001/00079
d D 5.4 87/09/01 19:28:33 karels 4 3
c try to preserve To, etc (or translate from Apparently-To)
c to make redisted messages look right
e
s 00000/00001/00080
d D 5.3 87/04/11 16:00:58 bostic 3 2
c cleaner unlink of redist file
e
s 00025/00031/00056
d D 5.2 87/04/11 15:38:44 bostic 2 1
c version #2; -f flag, remove home_dir, redist per folder
e
s 00087/00000/00000
d D 5.1 86/11/25 12:37:10 bostic 1 0
c date and time created 86/11/25 12:37:10 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 15
 * Copyright (c) 1986, 1987 Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
E 7
 */

#ifndef lint
D 7
static char sccsid[] = "%W% (Berkeley) %E%";
D 6
#endif not lint
E 6
I 6
#endif /* !lint */
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7
E 6

D 12
#include <sys/file.h>
E 12
I 12
#include <sys/param.h>
I 14

#include <ctype.h>
E 14
#include <dirent.h>
E 12
#include <stdio.h>
I 6
D 14
#include <ctype.h>
E 14
E 6
D 12
#include <bug.h>
E 12
I 12
#include <string.h>
I 14

E 14
#include "bug.h"
E 12
I 10
#include "pathnames.h"
I 14
#include "extern.h"
E 14
E 10

D 2
extern HEADER	mailhead[];			/* mail headers */
extern char	*distf,				/* redist temp file */
		pfile[],			/* permanent bug file */
		folder[];			/* system name */

E 2
/*
 * redist --
 *	Redistribute a bug report to those people indicated in the
 *	redistribution list file.
 */
I 14
void
E 14
redist()
{
D 2
	register char	*C1,		/* traveling chars */
E 2
I 2
	extern FILE	*dfp;		/* dist file fp */
	extern char	pfile[];	/* permanent bug file */
D 6
	register char	*C1,
E 2
			*C2;
D 2
	register int	first = YES;	/* if first blank line */
	FILE	*pf,			/* pipe pointer */
		*dfp,			/* dist file fp */
E 2
I 2
	register int	first;		/* if first blank line */
	FILE	*pf,
E 2
		*popen();
E 6
I 6
	register char	*C1, *C2;
D 14
	FILE	*pf, *popen();
E 14
I 14
	FILE	*pf;
E 14
	int	group;
E 6
D 2
	char	*index(), *mktemp();
E 2
I 2
D 13
	char	*index();
E 13
I 13
D 14
	char	*p, *index();
E 14
E 13
E 2

D 2
	if (!freopen(DIST_FILE,"r",stdin))
E 2
I 2
D 6
	sprintf(bfr, "%s/%s", dir, DIST_FILE);
E 6
I 6
	(void)sprintf(bfr, "%s/%s", dir, DIST_FILE);
E 6
	if (!freopen(bfr, "r", stdin))
E 2
		return;
D 2

E 2
D 6
	for (;;) {			/* get first part of entry */
		if (!gets(bfr))
			return;
D 2
		if (*bfr == COMMENT || *bfr == ' ' || *bfr == '\t' || !(C1 = index(bfr,':')))
E 2
I 2
		if (*bfr == COMMENT || *bfr == ' ' || *bfr == '\t' || !(C1 = index(bfr, ':')))
E 6
I 6
D 13
	for (pf = NULL, group = 0; gets(bfr);) {
		if (*bfr == COMMENT || isspace(*bfr) || !(C1 = index(bfr, ':')))
E 13
I 13
	for (pf = NULL, group = 0; fgets(bfr, sizeof(bfr), stdin);) {
D 14
		if (C1 = index(bfr, '\n'))
E 14
I 14
		if (C1 = strchr(bfr, '\n'))
E 14
			*C1 = '\0';
D 14
nextline:	if (*bfr == COMMENT || isspace(*bfr) || !(C1 = index(bfr, ':')))
E 14
I 14
nextline:	if (*bfr == COMMENT ||
		    isspace(*bfr) || !(C1 = index(bfr, ':')))
E 14
E 13
E 6
E 2
			continue;
		*C1 = EOS;
D 2
		if (!strcmp(bfr,folder))
E 2
I 2
D 6
		if (!strcmp(bfr, folder))
E 2
			break;
E 6
I 6
		if (!strcmp(bfr, folder) || !strcmp(bfr, "all")) {
			for (++C1; *C1 && (*C1 == ' ' || *C1 == '\t'); ++C1);
			if (!*C1)			/* if empty list */
				continue;
			if (!pf) {
				if (!(pf = popen(MAIL_CMD, "w")))
					error("sendmail pipe failed.", CHN);
				if (mailhead[SUBJ_TAG].found)
D 13
					fprintf(pf, "%s", mailhead[SUBJ_TAG].line);
E 13
I 13
					fprintf(pf,
					    "%s", mailhead[SUBJ_TAG].line);
E 13
				else
D 13
					fputs("Subject: Untitled Bug Report\n", pf);
E 13
I 13
					fprintf(pf,
					    "Subject: Untitled Bug Report\n");
E 13
D 8
				if (!mailhead[TO_TAG].line && mailhead[APPAR_TO_TAG].line)
					fprintf(pf, "To%s", index(mailhead[APPAR_TO_TAG].line, ':'));
E 8
I 8
				if (!mailhead[TO_TAG].line) {
					if (mailhead[APPAR_TO_TAG].line)
					    fprintf(pf, "To%s",
D 14
					      index(mailhead[APPAR_TO_TAG].line,
E 14
I 14
				      strchr(mailhead[APPAR_TO_TAG].line,
E 14
					      ':'));
					else
					    fprintf(pf, "To: %s\n",  BUGS_ID);
				}
E 8
				fputs("Resent-To: ", pf);
			}
			/*
			 * write out first entry, then succeeding entries
			 * backward compatible, handles back slashes at end
			 * of line
			 */
			if (group++)
				fputs(", ", pf);
			for (;;) {
D 14
				if (C2 = index(C1, '\\'))
E 14
I 14
				if (C2 = strchr(C1, '\\'))
E 14
					*C2 = EOS;
				fputs(C1, pf);
D 13
				if (!gets(bfr) || *bfr != ' ' && *bfr != '\t')
E 13
I 13
				if (!fgets(bfr, sizeof(bfr), stdin))
E 13
					break;
D 13
				for (C1 = bfr; *C1 && (*C1 == ' ' || *C1 == '\t'); ++C1);
E 13
I 13
D 14
				if (C1 = index(bfr, '\n'))
E 14
I 14
				if (C1 = strchr(bfr, '\n'))
E 14
					*C1 = '\0';
				if (*bfr != ' ' && *bfr != '\t')
					goto nextline;
				for (C1 = bfr;
				    *C1 && (*C1 == ' ' || *C1 == '\t'); ++C1);
E 13
			}
		}
E 6
	}
D 6
	for (++C1;*C1 && (*C1 == ' ' || *C1 == '\t');++C1);
	if (!*C1)			/* if empty */
E 6
I 6
	if (!pf)
E 6
		return;

D 2
	if (!(pf = popen(MAIL_CMD,"w")))
		error("sendmail pipe failed.",CHN);
E 2
I 2
D 6
	if (!(pf = popen(MAIL_CMD, "w")))
		error("sendmail pipe failed.", CHN);
E 2

D 2
	fprintf(pf,"Reply-To: %s\n",BUGS_HOME);
E 2
I 2
D 4
	fprintf(pf, "Reply-To: %s\n", BUGS_HOME);
E 4
E 2
	if (mailhead[SUBJ_TAG].found)
D 2
		fprintf(pf,"%s",mailhead[SUBJ_TAG].line);
E 2
I 2
		fprintf(pf, "%s", mailhead[SUBJ_TAG].line);
E 2
	else
D 2
		fputs("Subject: Untitled Bug Report\n",pf);
	fputs("Resent-To: ",pf);
E 2
I 2
		fputs("Subject: Untitled Bug Report\n", pf);
I 4
	if (mailhead[TO_TAG].line == 0 && mailhead[APPAR_TO_TAG].line != 0)
		fprintf(pf, "To%s", index(mailhead[APPAR_TO_TAG].line, ':'));
E 4
	fputs("Resent-To: ", pf);
E 2

	/*
	 * write out first entry, then succeeding entries
	 * backward compatible, handles back slashes at end of line
	 */
	for (;;) {
D 2
		if (C2 = index(C1,'\\'))
E 2
I 2
		if (C2 = index(C1, '\\'))
E 2
			*C2 = EOS;
D 2
		fputs(C1,pf);
E 2
I 2
		fputs(C1, pf);
E 2
		if (!gets(bfr) || (*bfr != ' ' && *bfr != '\t'))
			break;
		for (C1 = bfr;*C1 && (*C1 == ' ' || *C1 == '\t');++C1);
	}
E 6
D 2
	fputs("\n",pf);
E 2
I 2
	putc('\n', pf);
E 2

D 2
	if (!(dfp = fopen(distf,"r")))
		error("unable to read temporary file %s.",distf);
	while (fgets(bfr,sizeof(bfr),dfp))
E 2
I 2
	rewind(dfp);
D 6
	for (first = YES;fgets(bfr, sizeof(bfr), dfp);)
E 2
		if (*bfr == '\n' && first) {
			first = NO;
D 2
			fprintf(pf,"\n%sReference: %s\n",mailhead[INDX_TAG].line,pfile);
E 2
I 2
			fprintf(pf, "\n%sReference: %s\n", mailhead[INDX_TAG].line, pfile);
E 2
		}
		else
D 2
			fputs(bfr,pf);
	fclose(dfp);
	pclose(pf);
	unlink(distf);
E 2
I 2
			fputs(bfr, pf);
E 6
I 6
	/* add Reference header and copy bug report out */
	while (fgets(bfr, sizeof(bfr), dfp) && *bfr != '\n')
		fputs(bfr, pf);
	fprintf(pf, "\n%sReference: %s\n\n", mailhead[INDX_TAG].line, pfile);
	while (fgets(bfr, sizeof(bfr), dfp))
		fputs(bfr, pf);
E 6
	(void)pclose(pf);
D 3
	(void)fclose(dfp);
E 3
E 2
}
E 1
