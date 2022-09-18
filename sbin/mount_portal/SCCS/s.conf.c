h63866
s 00001/00001/00302
d D 8.2 94/03/27 13:44:54 pendry 5 4
c fix typo
e
s 00002/00002/00301
d D 8.1 93/06/05 11:03:46 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00303
d D 5.1 92/07/13 15:47:26 pendry 3 2
c move to rev 5
e
s 00001/00001/00302
d D 1.2 92/07/12 09:03:47 pendry 2 1
c checkpoint
e
s 00303/00000/00000
d D 1.1 92/07/09 14:47:40 pendry 1 0
c date and time created 92/07/09 14:47:40 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: conf.c,v 1.2 1992/05/27 07:09:27 jsp Exp jsp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <regexp.h>
#include <sys/types.h>
D 2
/*#include <sys/param.h>*/
E 2
I 2
#include <sys/param.h>
E 2
#include <sys/syslog.h>

#include "portald.h"

#define	ALLOC(ty)	(xmalloc(sizeof(ty)))

typedef struct path path;
struct path {
	qelem p_q;		/* 2-way linked list */
	int p_lno;		/* Line number of this record */
	char *p_args;		/* copy of arg string (malloc) */
	char *p_key;		/* Pathname to match (also p_argv[0]) */
	regexp *p_re;		/* RE to match against pathname (malloc) */
	int p_argc;		/* number of elements in arg string */
	char **p_argv;		/* argv[] pointers into arg string (malloc) */
};

static char *conf_file;		/* XXX for regerror */
static path *curp;		/* XXX for regerror */

/*
 * Add an element to a 2-way list,
 * just after (pred)
 */
static void ins_que(elem, pred)
qelem *elem, *pred;
{
	qelem *p = pred->q_forw;
	elem->q_back = pred;
	elem->q_forw = p;
	pred->q_forw = elem;
	p->q_back = elem;
}

/*
 * Remove an element from a 2-way list
 */
static void rem_que(elem)
qelem *elem;
{
	qelem *p = elem->q_forw;
	qelem *p2 = elem->q_back;
	p2->q_forw = p;
	p->q_back = p2;
}

/*
 * Error checking malloc
 */
static void *xmalloc(siz)
unsigned siz;
{
	void *p = malloc(siz);
	if (p)
		return (p);
	syslog(LOG_ALERT, "malloc: failed to get %d bytes", siz);
	exit(1);
}

/*
 * Insert the path in the list.
 * If there is already an element with the same key then
 * the *second* one is ignored (return 0).  If the key is
 * not found then the path is added to the end of the list
 * and 1 is returned.
 */
static int pinsert(p0, q0)
path *p0;
qelem *q0;
{
	qelem *q;

	if (p0->p_argc == 0)
		return (0);

	for (q = q0->q_forw; q != q0; q = q->q_forw) {
		path *p = (path *) q;
		if (strcmp(p->p_key, p0->p_key) == 0)
			return (0);
	}
	ins_que(&p0->p_q, q0->q_back);
	return (1);
	
}

void regerror(s)
const char *s;
{
	syslog(LOG_ERR, "%s:%s: regcomp %s: %s",
			conf_file, curp->p_lno, curp->p_key, s);
}

static path *palloc(cline, lno)
char *cline;
int lno;
{
	int c;
	char *s;
	char *key;
	path *p;
	char **ap;

	/*
	 * Implement comment chars
	 */
	s = strchr(cline, '#');
	if (s)
		*s = 0;

	/*
	 * Do a pass through the string to count the number
	 * of arguments
	 */
	c = 0;
	key = strdup(cline);
	for (s = key; s != NULL; ) {
		char *val;
		while ((val = strsep(&s, " \t\n")) != NULL && *val == '\0')
			;
		if (val)
			c++;
	}
	c++;
	free(key);

	if (c <= 1)
		return (0);

	/*
	 * Now do another pass and generate a new path structure
	 */
	p = ALLOC(path);
	p->p_argc = 0;
	p->p_argv = xmalloc(c * sizeof(char *));
	p->p_args = strdup(cline);
	ap = p->p_argv;
	for (s = p->p_args; s != NULL; ) {
		char *val;
		while ((val = strsep(&s, " \t\n")) != NULL && *val == '\0')
			;
		if (val) {
			*ap++ = val;
			p->p_argc++;
		}
	}
	*ap = 0;

#ifdef DEBUG
	for (c = 0; c < p->p_argc; c++)
		printf("%sv[%d] = %s\n", c?"\t":"", c, p->p_argv[c]);
#endif

	p->p_key = p->p_argv[0];
	if (strpbrk(p->p_key, RE_CHARS)) {
		curp = p;			/* XXX */
		p->p_re = regcomp(p->p_key);
		curp = 0;			/* XXX */
	} else {
		p->p_re = 0;
	}
	p->p_lno = lno;

	return (p);
}

/*
 * Free a path structure
 */
static void pfree(p)
path *p;
{
	free(p->p_args);
	if (p->p_re)
		free((char *) p->p_re);
	free((char *) p->p_argv);
	free((char *) p);
}

/*
 * Discard all currently held path structures on q0.
 * and add all the ones on xq.
 */
static void preplace(q0, xq)
qelem *q0;
qelem *xq;
{
	/*
	 * While the list is not empty,
	 * take the first element off the list
	 * and free it.
	 */
	while (q0->q_forw != q0) {
D 5
		qelem *q = q->q_forw;
E 5
I 5
		qelem *q = q0->q_forw;
E 5
		rem_que(q);
		pfree((path *) q);
	}
	while (xq->q_forw != xq) {
		qelem *q = xq->q_forw;
		rem_que(q);
		ins_que(q, q0);
	}
}

/*
 * Read the lines from the configuration file and
 * add them to the list of paths.
 */
static void readfp(q0, fp)
qelem *q0;
FILE *fp;
{
	char cline[LINE_MAX];
	int nread = 0;
	qelem q;

	/*
	 * Make a new empty list.
	 */
	q.q_forw = q.q_back = &q;

	/*
	 * Read the lines from the configuration file.
	 */
	while (fgets(cline, sizeof(cline), fp)) {
		path *p = palloc(cline, nread+1);
		if (p && !pinsert(p, &q))
			pfree(p);
		nread++;
	}

	/*
	 * If some records were read, then throw
	 * away the old list and replace with the
	 * new one.
	 */
	if (nread)
		preplace(q0, &q);
}

/*
 * Read the configuration file (conf) and replace
 * the existing path list with the new version.
 * If the file is not readable, then no changes take place
 */
void conf_read(q, conf)
qelem *q;
char *conf;
{
	FILE *fp = fopen(conf, "r");
	if (fp) {
		conf_file = conf;		/* XXX */
		readfp(q, fp);
		conf_file = 0;		/* XXX */
		(void) fclose(fp);
	} else {
		syslog(LOG_ERR, "open config file \"%s\": %s", conf, strerror(errno));
	}
}


char **conf_match(q0, key)
qelem *q0;
char *key;
{
	qelem *q;

	for (q = q0->q_forw; q != q0; q = q->q_forw) {
		path *p = (path *) q;
		if (p->p_re) {
			if (regexec(p->p_re, key))
				return (p->p_argv+1);
		} else {
			if (strncmp(p->p_key, key, strlen(p->p_key)) == 0)
				return (p->p_argv+1);
		}
	}

	return (0);
}
E 1
