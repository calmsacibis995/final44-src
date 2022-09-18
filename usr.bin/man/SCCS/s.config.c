h43169
s 00003/00001/00147
d D 8.8 95/01/31 05:12:24 pendry 19 17
c close config file after reading
e
s 00002/00000/00148
d R 8.8 95/01/31 05:08:52 pendry 18 17
c close config file after reading
e
s 00001/00001/00147
d D 8.7 94/01/03 10:05:48 bostic 17 16
c rename fgetline -> fgetln
e
s 00001/00001/00147
d D 8.6 94/01/02 10:26:02 bostic 16 15
c len == 1 for empty lines, now
e
s 00028/00026/00120
d D 8.5 94/01/02 10:25:19 bostic 15 14
c convert to new <sys/queue.h> structures
e
s 00007/00004/00139
d D 8.4 94/01/02 10:24:55 bostic 14 13
c add a way to specify the config file (-C)
e
s 00001/00002/00142
d D 8.3 94/01/02 10:24:22 bostic 13 12
c NULL dereference
e
s 00102/00169/00042
d D 8.2 94/01/02 10:23:55 bostic 12 11
c rewrite man to make the configuration file more flexible
e
s 00002/00002/00209
d D 8.1 93/06/17 11:46:09 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00206
d D 5.9 93/06/17 11:44:30 bostic 10 8
c litn
e
s 00002/00002/00209
d R 8.1 93/06/06 15:23:23 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00207
d D 5.8 93/04/21 11:54:39 hibler 8 7
c fix buffer overflow fix: bp was not updated properly after realloc
e
s 00006/00007/00203
d D 5.7 92/02/12 17:02:33 bostic 7 6
c fix buffer overflow problem; example was really long MANPATH variable
e
s 00001/00000/00209
d D 5.6 91/03/01 15:08:16 bostic 6 5
c ANSI
e
s 00002/00001/00207
d D 5.5 90/06/29 10:53:42 trent 5 4
c move a variable declaration
e
s 00009/00012/00199
d D 5.4 90/06/28 18:04:45 trent 4 3
c MANPATH subdirectories now specified by _config in man.conf
e
s 00001/00011/00210
d D 5.3 90/06/01 16:58:09 bostic 3 2
c new copyright notice
e
s 00169/00031/00052
d D 5.2 90/05/27 15:24:06 bostic 2 1
c new man version, with much more complicated configuration file
e
s 00083/00000/00000
d D 5.1 90/05/20 13:20:33 bostic 1 0
c date and time created 90/05/20 13:20:33 by bostic
e
u
U
t
T
I 1
/*
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 19
 * Copyright (c) 1989, 1993
E 19
I 19
 * Copyright (c) 1989, 1993, 1995
E 19
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 3
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include <sys/types.h>
E 2
I 2
D 12
#include <sys/param.h>
E 2
#include <stdio.h>
E 12
I 12
#include <sys/types.h>
#include <sys/queue.h>

#include <ctype.h>
#include <err.h>
E 12
#include <errno.h>
D 12
#include <string.h>
E 12
I 12
#include <stdio.h>
E 12
I 2
#include <stdlib.h>
D 12
#include <pwd.h>
E 12
I 12
#include <string.h>

#include "config.h"
E 12
E 2
#include "pathnames.h"

I 2
D 12
#define	MAXLINE		1024
E 12
I 12
D 15
struct queue_entry head;
E 15
I 15
struct _head head;
E 15
E 12

E 2
D 4
extern char *progname;
E 4
I 4
D 5
extern char *progname, *pathbuf, **arorder;
E 5
I 5
D 12
extern char *progname;
char *pathbuf, **arorder;
E 5
E 4

I 2
static FILE *cfp;
D 4
static char *buf;
E 4

E 12
E 2
/*
D 2
 * config --
 *	read in the configuration file, convert it to a colon separated
 *	path.
E 2
I 2
D 12
 * getpath --
 *	read in the configuration file, calling a function with the line
 *	from each matching section.
E 12
I 12
 * config --
 *
 * Read the configuration file and build a doubly linked
 * list that looks like:
 *
 *	tag1 <-> record <-> record <-> record
 *	|
 *	tag2 <-> record <-> record <-> record
E 12
E 2
 */
D 12
char *
D 2
config()
E 2
I 2
getpath(sects)
	char **sects;
E 12
I 12
void
D 14
config()
E 14
I 14
config(fname)
	char *fname;
E 14
E 12
E 2
{
D 2
	register char *p;
	u_int buflen;
	int len;
	char *buf, *endp, line[256], *realloc();
E 2
I 2
D 12
	register char **av, *p;
E 12
I 12
D 15
	ENTRY *ep, *qp;
E 15
I 15
	TAG *tp;
	ENTRY *ep;
E 15
	FILE *cfp;
E 12
	size_t len;
D 4
	char **ar, line[MAXLINE], **getorder();
E 4
I 4
D 12
	char line[MAXLINE];
I 6
	static int openconfig();
E 12
I 12
	int lcnt;
	char *p, *t;
E 12
E 6
E 4
E 2

D 2
	if (!freopen(_PATH_MANCONF, "r", stdin)) {
E 2
I 2
D 4
	ar = getorder();
E 4
D 12
	openconfig();
	while (fgets(line, sizeof(line), cfp)) {
D 10
		if (!index(line, '\n')) {
E 10
I 10
		if (!strchr(line, '\n')) {
E 10
			(void)fprintf(stderr, "%s: config line too long.\n",
			    progname);
			exit(1);
		}
		p = strtok(line, " \t\n");
		if (!p || *p == '#')
E 12
I 12
D 14
	if ((cfp = fopen(_PATH_MANCONF, "r")) == NULL)
		err(1, "%s", _PATH_MANCONF);
E 14
I 14
	if (fname == NULL)
		fname = _PATH_MANCONF;
	if ((cfp = fopen(fname, "r")) == NULL)
		err(1, "%s", fname);
E 14
D 15
	queue_init(&head);
E 15
I 15
	TAILQ_INIT(&head);
E 15
D 17
	for (lcnt = 1; (p = fgetline(cfp, &len)) != NULL; ++lcnt) {
E 17
I 17
	for (lcnt = 1; (p = fgetln(cfp, &len)) != NULL; ++lcnt) {
E 17
D 16
		if (!len)			/* Skip empty lines. */
E 16
I 16
		if (len == 1)			/* Skip empty lines. */
E 16
E 12
			continue;
D 12
		for (av = sects; *av; ++av)
			if (!strcmp(p, *av))
				break;
		if (!*av)
E 12
I 12
		if (p[len - 1] != '\n') {	/* Skip corrupted lines. */
D 14
			warnx("%s: line %d corrupted", _PATH_MANCONF, lcnt);
E 14
I 14
			warnx("%s: line %d corrupted", fname, lcnt);
E 14
E 12
			continue;
D 12
		while (p = strtok((char *)NULL, " \t\n")) {
			len = strlen(p);
			if (p[len - 1] == '/')
D 4
				for (av = ar; *av; ++av)
					cadd(p, len, *av);
E 4
I 4
				for (av = arorder; *av; ++av)
D 10
                			cadd(p, len, *av);
E 10
I 10
					cadd(p, len, *av);
E 10
E 4
			else
				cadd(p, len, (char *)NULL);
E 12
		}
D 12
	}
D 4
	return(buf);
E 4
I 4
	return(pathbuf);
E 4
}
E 12
I 12
		p[len - 1] = '\0';		/* Terminate the line. */
E 12

D 4
static
E 4
D 12
cadd(add1, len1, add2)
D 7
char *add1, *add2;
register size_t len1;
E 7
I 7
	char *add1, *add2;
	register size_t len1;
E 7
{
D 8
	static size_t buflen;
E 8
I 8
	static size_t buflen, boff;
E 8
	static char *bp, *endp;
	register size_t len2;
E 12
I 12
						/* Skip leading space. */
		for (; *p != '\0' && isspace(*p); ++p);
						/* Skip empty/comment lines. */
		if (*p == '\0' || *p == '#')
			continue;
						/* Find first token. */
		for (t = p; *t && !isspace(*t); ++t);
		if (*t == '\0')			/* Need more than one token.*/
			continue;
		*t = '\0';
E 12

D 12
	len2 = add2 ? strlen(add2) : 0;
D 7
	if (!bp || bp + len1 + len2 + 2 >= endp) {
D 4
		if (!(buf = realloc(buf, buflen += 1024)))
E 4
I 4
		if (!(pathbuf = realloc(pathbuf, buflen += 1024)))
E 7
I 7
	if (bp == NULL || bp + len1 + len2 + 2 >= endp) {
		buflen += MAX(len1 + len2 + 2, 1024);
I 8
		boff = bp ? bp - pathbuf : 0;
E 8
		if ((pathbuf = realloc(pathbuf, buflen)) == NULL)
E 7
E 4
			enomem();
D 7
		if (!bp)
D 4
			bp = buf;
		endp = buf + buflen;
E 4
I 4
			bp = pathbuf;
		endp = pathbuf + buflen;
E 7
I 7
D 8
		endp = (bp = pathbuf) + buflen;
E 8
I 8
		bp = pathbuf + boff;
		endp = pathbuf + buflen;
E 8
E 7
E 4
	}
	bcopy(add1, bp, len1);
	bp += len1;
	if (len2) {
		bcopy(add2, bp, len2);
		bp += len2;
	}
	*bp++ = ':';
	*bp = '\0';
}
E 12
I 12
D 15
		for (qp = head.qe_next;		/* Find any matching tag. */
		    qp != NULL && strcmp(p, qp->s); qp = qp->tags.qe_next);
E 15
I 15
		for (tp = head.tqh_first;	/* Find any matching tag. */
		    tp != NULL && strcmp(p, tp->s); tp = tp->q.tqe_next);
E 15
E 12

D 12
static
openconfig()
{
	if (cfp) {
		rewind(cfp);
		return;
	}
	if (!(cfp = fopen(_PATH_MANCONF, "r"))) {
E 2
		(void)fprintf(stderr, "%s: no configuration file %s.\n",
		    progname, _PATH_MANCONF);
		exit(1);
	}
D 2
	buflen = 0;
	buf = endp = p = NULL;
	while (fgets(line, sizeof(line), stdin)) {
E 2
I 2
}
E 12
I 12
D 15
		if (qp == NULL)			/* Create a new tag. */
			qp = addlist(p);
E 15
I 15
		if (tp == NULL)		/* Create a new tag. */
			tp = addlist(p);
E 15
E 12

D 12
char **
getdb()
{
	register char *p;
	int cnt, num;
	char **ar, line[MAXLINE];

	ar = NULL;
	num = 0;
	cnt = -1;
	openconfig();
	while (fgets(line, sizeof(line), cfp)) {
E 2
D 10
		if (!index(line, '\n')) {
E 10
I 10
		if (!strchr(line, '\n')) {
E 10
			(void)fprintf(stderr, "%s: config line too long.\n",
			    progname);
			exit(1);
E 12
I 12
		/*
		 * Attach new records.  The keyword _build takes the rest of
		 * the line as a single entity, everything else is white
		 * space separated.  The reason we're not just using strtok(3)
		 * for all of the parsing is so we don't get caught if a line
		 * has only a single token on it.
		 */
		if (!strcmp(p, "_build")) {
			while (*++t && isspace(*t));
			if ((ep = malloc(sizeof(ENTRY))) == NULL ||
			    (ep->s = strdup(t)) == NULL)
				err(1, NULL);
D 15
			queue_enter_tail(&qp->list, ep, ENTRY *, list);
E 15
I 15
			TAILQ_INSERT_TAIL(&tp->list, ep, q);
E 15
D 13
		} else while ((p = strtok(t + 1, " \t\n")) != NULL) {
E 13
I 13
		} else for (++t; (p = strtok(t, " \t\n")) != NULL; t = NULL) {
E 13
			if ((ep = malloc(sizeof(ENTRY))) == NULL ||
			    (ep->s = strdup(p)) == NULL)
				err(1, NULL);
D 15
			queue_enter_tail(&qp->list, ep, ENTRY *, list);
E 15
I 15
			TAILQ_INSERT_TAIL(&tp->list, ep, q);
E 15
D 13
			t = NULL;
E 13
E 12
		}
D 2
		len = strcspn(line, " \t\n");
		if (!len || *line == '#')
E 2
I 2
D 12
		p = strtok(line, " \t\n");
#define	WHATDB	"_whatdb"
		if (!p || *p == '#' || strcmp(p, WHATDB))
E 2
			continue;
D 2
		if (!p || p + len + 2 >= endp) {
			if (!(buf = realloc(buf, buflen += 1024)))
E 2
I 2
		while (p = strtok((char *)NULL, " \t\n")) {
			if (cnt == num - 1 &&
			    !(ar = realloc(ar, (num += 30) * sizeof(char **))))
E 2
				enomem();
D 2
			if (!p)
				p = buf;
			endp = buf + buflen;
E 2
I 2
			if (!(ar[++cnt] = strdup(p)))
				enomem();
E 2
		}
E 12
D 2
		bcopy(line, p, len);
		p += len;
		*p++ = ':';
E 2
	}
I 19

	fclose(cfp);
E 19
D 2
	if (!buf)
		return((char *)NULL);
	*--p = '\0';
	return(buf);
E 2
I 2
D 12
	if (ar) {
		if (cnt == num - 1 &&
		    !(ar = realloc(ar, ++num * sizeof(char **))))
			enomem();
		ar[++cnt] = NULL;
	}
	return(ar);
E 12
E 2
}

D 2
enomem()
E 2
I 2
D 4
static char **
E 4
I 4
D 12
char **
E 4
getorder()
E 12
I 12
/*
 * addlist --
 *	Add a tag to the list.
 */
D 15
ENTRY *
E 15
I 15
TAG *
E 15
addlist(name)
	char *name;
E 12
E 2
{
D 2
	extern int errno;
	char *strerror();
E 2
I 2
D 12
	register char *p;
	int cnt, num;
	char **ar, line[MAXLINE];
E 12
I 12
D 15
	ENTRY *ep;
E 15
I 15
	TAG *tp;
E 15
E 12
E 2

D 2
	(void)fprintf(stderr, "%s: %s\n", strerror(ENOMEM), progname);
E 2
I 2
D 12
	ar = NULL;
	num = 0;
	cnt = -1;
	openconfig();
	while (fgets(line, sizeof(line), cfp)) {
D 10
		if (!index(line, '\n')) {
E 10
I 10
		if (!strchr(line, '\n')) {
E 10
			(void)fprintf(stderr, "%s: config line too long.\n",
			    progname);
			exit(1);
		}
		p = strtok(line, " \t\n");
#define	SUBDIR	"_subdir"
		if (!p || *p == '#' || strcmp(p, SUBDIR))
			continue;
		while (p = strtok((char *)NULL, " \t\n")) {
			if (cnt == num - 1 &&
			    !(ar = realloc(ar, (num += 30) * sizeof(char **))))
				enomem();
			if (!(ar[++cnt] = strdup(p)))
				enomem();
		}
	}
	if (ar) {
		if (cnt == num - 1 &&
		    !(ar = realloc(ar, ++num * sizeof(char **))))
			enomem();
		ar[++cnt] = NULL;
	}
	return(ar);
E 12
I 12
D 15
	if ((ep = malloc(sizeof(ENTRY))) == NULL ||
	    (ep->s = strdup(name)) == NULL)
E 15
I 15
	if ((tp = calloc(1, sizeof(TAG))) == NULL ||
	    (tp->s = strdup(name)) == NULL)
E 15
		err(1, NULL);
D 15
	queue_init(&ep->list);
	queue_enter_head(&head, ep, ENTRY *, tags);
	return (head.qe_next);
E 15
I 15
	TAILQ_INIT(&tp->list);
	TAILQ_INSERT_TAIL(&head, tp, q);
	return (tp);
E 15
E 12
}

D 12
getsection(sect)
	char *sect;
E 12
I 12
/*
 * getlist --
D 15
 *	Return the linked list for a tag if it exists.
E 15
I 15
 *	Return the linked list of entries for a tag if it exists.
E 15
 */
D 15
ENTRY *
E 15
I 15
TAG *
E 15
getlist(name)
	char *name;
E 12
{
D 12
	register char *p;
	char line[MAXLINE];
E 12
I 12
D 15
	ENTRY *qp;
E 15
I 15
	TAG *tp;
E 15
E 12

D 12
	openconfig();
	while (fgets(line, sizeof(line), cfp)) {
D 10
		if (!index(line, '\n')) {
E 10
I 10
		if (!strchr(line, '\n')) {
E 10
			(void)fprintf(stderr, "%s: config line too long.\n",
			    progname);
			exit(1);
		}
		p = strtok(line, " \t\n");
		if (!p || *p == '#')
			continue;
		if (!strcmp(p, sect))
			return(1);
	}
	return(0);
E 12
I 12
D 15
	for (qp = head.qe_next; qp != NULL; qp = qp->tags.qe_next)
		if (!strcmp(name, qp->s))
			return (qp);
E 15
I 15
	for (tp = head.tqh_first; tp != NULL; tp = tp->q.tqe_next)
		if (!strcmp(name, tp->s))
			return (tp);
E 15
	return (NULL);
E 12
}

D 12
enomem()
E 12
I 12
void
debug(l)
	char *l;
E 12
{
D 12
	(void)fprintf(stderr, "%s: %s\n", progname, strerror(ENOMEM));
E 2
	exit(1);
E 12
I 12
D 15
	ENTRY *ep, *qp;
E 15
I 15
	TAG *tp;
	ENTRY *ep;
E 15

	(void)printf("%s ===============\n", l);
D 15
	for (qp = head.qe_next; qp != NULL; qp = qp->tags.qe_next) {
		printf("%s\n", qp->s);
		for (ep = qp->list.qe_next; ep != NULL; ep = ep->list.qe_next)
E 15
I 15
	for (tp = head.tqh_first; tp != NULL; tp = tp->q.tqe_next) {
		printf("%s\n", tp->s);
		for (ep = tp->list.tqh_first; ep != NULL; ep = ep->q.tqe_next)
E 15
			printf("\t%s\n", ep->s);
	}
E 12
}
E 1
