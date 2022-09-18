h48524
s 00001/00000/00403
d D 8.3 95/05/04 15:47:57 bostic 14 13
c optarg/optind moved to unistd.h
e
s 00079/00074/00324
d D 8.2 94/03/30 14:19:09 bostic 13 12
c change tsort to not look for the longest cycle (add a -l flag for
c users that actually want the longest cycle).  This is backward compatible
c with historic tsort, it didn't find the longest cycle either.
c This provides a major speedup for some tsort runs.
c From: christos@deshaw.com (Christos Zoulas)
e
s 00005/00005/00393
d D 8.1 93/06/09 22:54:23 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00396
d D 5.8 92/10/13 10:38:19 bostic 11 10
c db->get does not return a longword aligned buffer; from Craig Leres
e
s 00011/00007/00386
d D 5.7 92/06/23 17:39:32 marc 10 9
c It makes a BIG difference if you prune duplicate entries.
c Normally LOTS of them occur...
e
s 00005/00007/00388
d D 5.6 92/06/23 17:19:24 bostic 9 8
c don't bother to cast malloc
e
s 00035/00049/00360
d D 5.5 92/02/03 14:20:32 bostic 8 7
c combine find_node and add_node, use db(3) hashing; malloc node and
c node name in one shot
e
s 00092/00050/00317
d D 5.4 92/02/03 13:03:00 bostic 7 6
c fix argument parsing, add getopt(3), minor cleanups
e
s 00001/00011/00366
d D 5.3 90/06/01 16:11:45 bostic 6 5
c new copyright notice
e
s 00001/00001/00376
d D 5.2 90/05/15 19:50:19 bostic 5 4
c string.h is ANSI C include file
e
s 00337/00167/00040
d D 5.1 90/03/06 21:14:10 bostic 4 3
c AT&T free version, from Michael Rendell (michael@stretch.cs.mun.ca)
e
s 00001/00000/00206
d D 4.3 87/09/14 16:14:44 bostic 3 2
c add exit from main; bug report 4.3BSD/usr.bin/84
e
s 00001/00001/00205
d D 4.2 82/10/20 21:07:31 mckusick 2 1
c use <> for include
e
s 00206/00000/00000
d D 4.1 80/10/01 17:29:02 bill 1 0
c date and time created 80/10/01 17:29:02 by bill
e
u
U
t
T
I 1
D 4
static char *sccsid = "%W% (Berkeley) %G%";
/*	topological sort
 *	input is sequence of pairs of items (blank-free strings)
 *	nonidentical pair is a directed edge in graph
 *	identical pair merely indicates presence of node
 *	output is ordered list of items consistent with
 *	the partial ordering specified by the graph
*/
E 4
I 4
/*
D 12
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
D 13
 * Copyright (c) 1989, 1993
E 13
I 13
 * Copyright (c) 1989, 1993, 1994
E 13
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * Michael Rendell of Memorial University of Newfoundland.
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 12
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
D 13
"%Z% Copyright (c) 1989, 1993\n\
E 13
I 13
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 13
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 13

#include <ctype.h>
#include <db.h>
#include <err.h>
E 13
#include <errno.h>
I 8
#include <fcntl.h>
D 13
#include <db.h>
E 13
E 8
E 4
D 2
#include "stdio.h"
E 2
I 2
#include <stdio.h>
I 7
#include <stdlib.h>
E 7
I 4
D 13
#include <ctype.h>
E 13
D 5
#include <strings.h>
E 5
I 5
#include <string.h>
I 14
#include <unistd.h>
E 14
E 5
E 4
E 2

D 4
/*	the nodelist always has an empty element at the end to
 *	make it easy to grow in natural order
 *	states of the "live" field:*/
#define DEAD 0	/* already printed*/
#define LIVE 1	/* not yet printed*/
#define VISITED 2	/*used only in findloop()*/
E 4
I 4
/*
D 9
 *  Topological sort.  Input is a list of pairs of strings seperated by
E 9
I 9
 *  Topological sort.  Input is a list of pairs of strings separated by
E 9
 *  white space (spaces, tabs, and/or newlines); strings are written to
 *  standard output in sorted order, one per line.
 *
 *  usage:
D 13
 *     tsort [inputfile]
E 13
I 13
 *     tsort [-l] [inputfile]
E 13
 *  If no input file is specified, standard input is read.
 *
 *  Should be compatable with AT&T tsort HOWEVER the output is not identical
 *  (i.e. for most graphs there is more than one sorted order, and this tsort
 *  usually generates a different one then the AT&T tsort).  Also, cycle
 *  reporting seems to be more accurate in this version (the AT&T tsort
 *  sometimes says a node is in a cycle when it isn't).
 *
 *  Michael Rendell, michael@stretch.cs.mun.ca - Feb 26, '90
 */
#define	HASHSIZE	53		/* doesn't need to be big */
#define	NF_MARK		0x1		/* marker for cycle detection */
#define	NF_ACYCLIC	0x2		/* this node is cycle free */
I 13
#define	NF_NODEST	0x4		/* Unreachable */
E 13
E 4

I 13

E 13
D 4
struct nodelist {
	struct nodelist *nextnode;
	struct predlist *inedges;
	char *name;
	int live;
} firstnode = {NULL, NULL, NULL, DEAD};
E 4
I 4
typedef struct node_str NODE;
E 4

D 4
/*	a predecessor list tells all the immediate
 *	predecessors of a given node
*/
struct predlist {
	struct predlist *nextpred;
	struct nodelist *pred;
E 4
I 4
struct node_str {
D 8
	char *n_name;			/* name of this node */
E 8
	NODE **n_prevp;			/* pointer to previous node's n_next */
	NODE *n_next;			/* next node in graph */
D 8
	NODE *n_hash;			/* next node in hash table */
E 8
I 8
	NODE **n_arcs;			/* array of arcs to other nodes */
E 8
	int n_narcs;			/* number of arcs in n_arcs[] */
	int n_arcsize;			/* size of n_arcs[] array */
D 8
	NODE **n_arcs;			/* array of arcs to other nodes */
E 8
	int n_refcnt;			/* # of arcs pointing to this node */
	int n_flags;			/* NF_* */
I 8
	char n_name[1];			/* name of this node */
E 8
E 4
};

D 4
struct nodelist *index();
struct nodelist *findloop();
struct nodelist *mark();
char *malloc();
char *empty = "";
E 4
I 4
typedef struct _buf {
	char *b_buf;
	int b_bsize;
} BUF;
E 4

I 8
DB *db;
E 8
D 4
/*	the first for loop reads in the graph,
 *	the second prints out the ordering
*/
main(argc,argv)
char **argv;
E 4
I 4
D 7
NODE *add_node(), *find_node();
void add_arc(), no_memory(), remove_node(), tsort();
char *grow_buf(), *malloc();

extern int errno;
E 7
D 13
NODE *graph;
D 8
NODE *hashtable[HASHSIZE];
E 8
NODE **cycle_buf;
NODE **longest_cycle;
E 13
I 13
NODE *graph, **cycle_buf, **longest_cycle;
int debug, longest;
E 13

I 7
void	 add_arc __P((char *, char *));
D 8
NODE	*add_node __P((char *));
E 8
D 13
void	 err __P((const char *, ...));
E 13
int	 find_cycle __P((NODE *, NODE *, int, int));
D 8
NODE	*find_node __P((char *));
E 8
I 8
NODE	*get_node __P((char *));
E 8
void	*grow_buf __P((void *, int));
D 8
int	 hash_string __P((char *));
E 8
void	 remove_node __P((NODE *));
void	 tsort __P((void));
void	 usage __P((void));

int
E 7
main(argc, argv)
	int argc;
D 7
	char **argv;
E 7
I 7
	char *argv[];
E 7
E 4
{
D 4
	register struct predlist *t;
	FILE *input = stdin;
	register struct nodelist *i, *j;
	int x;
	char precedes[50], follows[50];
	if(argc>1) {
		input = fopen(argv[1],"r");
		if(input==NULL)
			error("cannot open ", argv[1]);
E 4
I 4
	register BUF *b;
	register int c, n;
	FILE *fp;
D 7
	int bsize, nused;
E 7
I 7
	int bsize, ch, nused;
E 7
	BUF bufs[2];

D 7
	if (argc < 2)
E 7
I 7
D 13
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
E 13
I 13
	while ((ch = getopt(argc, argv, "dl")) != EOF)
		switch (ch) {
		case 'd':
			debug = 1;
			break;
		case 'l':
			longest = 1;
			break;
E 13
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 13
	switch(argc) {
E 13
I 13
	switch (argc) {
E 13
	case 0:
E 7
		fp = stdin;
D 7
	else if (argc == 2) {
		(void)fprintf(stderr, "usage: tsort [ inputfile ]\n");
		exit(1);
	} else if (!(fp = fopen(argv[1], "r"))) {
		(void)fprintf(stderr, "tsort: %s.\n", strerror(errno));
		exit(1);
E 7
I 7
		break;
	case 1:
		if ((fp = fopen(*argv, "r")) == NULL)
D 13
			err("%s: %s", *argv, strerror(errno));
E 13
I 13
			err(1, "%s", *argv);
E 13
		break;
	default:
		usage();
E 7
E 4
	}
D 4
	for(;;) {
		x = fscanf(input,"%s%s",precedes, follows);
		if(x==EOF)
E 4
I 4

	for (b = bufs, n = 2; --n >= 0; b++)
D 7
		b->b_buf = grow_buf((char *)NULL, b->b_bsize = 1024);
E 7
I 7
		b->b_buf = grow_buf(NULL, b->b_bsize = 1024);
E 7

	/* parse input and build the graph */
	for (n = 0, c = getc(fp);;) {
		while (c != EOF && isspace(c))
			c = getc(fp);
		if (c == EOF)
E 4
			break;
D 4
		if(x!=2)
			error("odd data",empty);
		i = index(precedes);
		j = index(follows);
		if(i==j||present(i,j)) 
			continue;
		t = (struct predlist *)malloc(sizeof(struct predlist));
		t->nextpred = j->inedges;
		t->pred = i;
		j->inedges = t;
	}
	for(;;) {
		x = 0;	/*anything LIVE on this sweep?*/
		for(i= &firstnode; i->nextnode!=NULL; i=i->nextnode) {
			if(i->live==LIVE) {
				x = 1;
				if(!anypred(i))
					break;
E 4
I 4

		nused = 0;
		b = &bufs[n];
		bsize = b->b_bsize;
		do {
			b->b_buf[nused++] = c;
D 7
			if (nused == bsize) {
				bsize *= 2;
				b->b_buf = grow_buf(b->b_buf, bsize);
E 4
			}
E 7
I 7
			if (nused == bsize)
				b->b_buf = grow_buf(b->b_buf, bsize *= 2);
E 7
D 4
		}
		if(x==0)
			break;
		if(i->nextnode==NULL)
			i = findloop();
		printf("%s\n",i->name);
		i->live = DEAD;
E 4
I 4
			c = getc(fp);
		} while (c != EOF && !isspace(c));

		b->b_buf[nused] = '\0';
		b->b_bsize = bsize;
		if (n)
			add_arc(bufs[0].b_buf, bufs[1].b_buf);
		n = !n;
E 4
	}
I 4
	(void)fclose(fp);
D 7
	if (n) {
		(void)fprintf(stderr, "tsort: odd data count.\n");
		exit(1);
	}
E 7
I 7
	if (n)
D 13
		err("odd data count");
E 13
I 13
		errx(1, "odd data count");
E 13
E 7

	/* do the sort */
	tsort();
E 4
I 3
	exit(0);
E 3
}

D 4
/*	is i present on j's predecessor list?
*/
present(i,j)
struct nodelist *i, *j;
E 4
I 4
/* double the size of oldbuf and return a pointer to the new buffer. */
D 7
char *
E 7
I 7
void *
E 7
grow_buf(bp, size)
D 7
	char *bp;
E 7
I 7
	void *bp;
E 7
	int size;
E 4
{
D 4
	register struct predlist *t;
	for(t=j->inedges; t!=NULL; t=t->nextpred)
		if(t->pred==i)
			return(1);
	return(0);
E 4
I 4
D 7
	char *realloc();

	if (!(bp = realloc(bp, (u_int)size)))
		no_memory();
	return(bp);
E 7
I 7
	if ((bp = realloc(bp, (u_int)size)) == NULL)
D 13
		err("%s", strerror(errno));
E 13
I 13
		err(1, NULL);
E 13
	return (bp);
E 7
E 4
}

D 4
/*	is there any live predecessor for i?
*/
anypred(i)
struct nodelist *i;
E 4
I 4
/*
 * add an arc from node s1 to node s2 in the graph.  If s1 or s2 are not in
 * the graph, then add them.
 */
void
add_arc(s1, s2)
	char *s1, *s2;
E 4
{
D 4
	register struct predlist *t;
	for(t=i->inedges; t!=NULL; t=t->nextpred)
		if(t->pred->live==LIVE)
			return(1);
	return(0);
E 4
I 4
	register NODE *n1;
	NODE *n2;
D 10
	int bsize;
E 10
I 10
	int bsize, i;
E 10

D 8
	n1 = find_node(s1);
	if (!n1)
		n1 = add_node(s1);
E 8
I 8
	n1 = get_node(s1);
E 8

	if (!strcmp(s1, s2))
		return;

D 8
	n2 = find_node(s2);
	if (!n2)
		n2 = add_node(s2);
E 8
I 8
	n2 = get_node(s2);
E 8

	/*
D 10
	 * could check to see if this arc is here already, but it isn't
	 * worth the bother -- there usually isn't and it doesn't hurt if
	 * there is (I think :-).
E 10
I 10
	 * Check if this arc is already here.
E 10
	 */
I 10
	for (i = 0; i < n1->n_narcs; i++)
		if (n1->n_arcs[i] == n2)
			return;
	/*
	 * Add it.
	 */
E 10
	if (n1->n_narcs == n1->n_arcsize) {
		if (!n1->n_arcsize)
			n1->n_arcsize = 10;
		bsize = n1->n_arcsize * sizeof(*n1->n_arcs) * 2;
D 7
		n1->n_arcs = (NODE **)grow_buf((char *)n1->n_arcs, bsize);
E 7
I 7
		n1->n_arcs = grow_buf(n1->n_arcs, bsize);
E 7
		n1->n_arcsize = bsize / sizeof(*n1->n_arcs);
	}
	n1->n_arcs[n1->n_narcs++] = n2;
	++n2->n_refcnt;
E 4
}

I 7
D 8
int
E 7
D 4
/*	turn a string into a node pointer
*/
struct nodelist *
index(s)
register char *s;
E 4
I 4
hash_string(s)
	char *s;
E 4
{
D 4
	register struct nodelist *i;
	register char *t;
	for(i= &firstnode; i->nextnode!=NULL; i=i->nextnode)
		if(cmp(s,i->name))
			return(i);
	for(t=s; *t; t++) ;
	t = malloc((unsigned)(t+1-s));
	i->nextnode = (struct nodelist *)malloc(sizeof(struct nodelist));
	if(i->nextnode==NULL||t==NULL)
		error("too many items",empty);
	i->name = t;
	i->live = LIVE;
	i->nextnode->nextnode = NULL;
	i->nextnode->inedges = NULL;
	i->nextnode->live = DEAD;
	while(*t++ = *s++);
	return(i);
E 4
I 4
	register int hash, i;

	for (hash = 0, i = 1; *s; s++, i++)
		hash += *s * i;
D 7
	return(hash % HASHSIZE);
E 7
I 7
	return (hash % HASHSIZE);
E 7
E 4
}

D 4
cmp(s,t)
register char *s, *t;
E 4
I 4
/*
 * find a node in the graph and return a pointer to it - returns null if not
 * found.
 */
E 8
I 8
/* Find a node in the graph (insert if not found) and return a pointer to it. */
E 8
NODE *
D 8
find_node(name)
E 8
I 8
get_node(name)
E 8
	char *name;
E 4
{
D 4
	while(*s==*t) {
		if(*s==0)
			return(1);
		s++;
		t++;
	}
	return(0);
E 4
I 4
D 8
	register NODE *n;
E 8
I 8
	DBT data, key;
	NODE *n;
E 8

D 8
	for (n = hashtable[hash_string(name)]; n; n = n->n_hash)
		if (!strcmp(n->n_name, name))
D 7
			return(n);
	return((NODE *)NULL);
E 7
I 7
			return (n);
	return (NULL);
E 7
E 4
}
E 8
I 8
	if (db == NULL &&
	    (db = dbopen(NULL, O_RDWR, 0, DB_HASH, NULL)) == NULL)
D 13
		err("db: open: %s", name, strerror(errno));
E 13
I 13
		err(1, "db: %s", name);
E 13
E 8

D 4
error(s,t)
char *s, *t;
E 4
I 4
D 8
/* Add a node to the graph and return a pointer to it. */
NODE *
add_node(name)
	char *name;
E 4
{
D 4
	note(s,t);
	exit(1);
E 4
I 4
	register NODE *n;
	int hash;
E 8
I 8
	key.data = name;
	key.size = strlen(name) + 1;
E 8

D 7
	if (!(n = (NODE *)malloc(sizeof(NODE))) || !(n->n_name = strdup(name)))
		no_memory();
E 7
I 7
D 8
	if ((n = malloc(sizeof(NODE))) == NULL ||
	    (n->n_name = strdup(name)) == NULL)
E 8
I 8
D 13
	switch((*db->get)(db, &key, &data, 0)) {
E 13
I 13
	switch ((*db->get)(db, &key, &data, 0)) {
E 13
	case 0:
D 11
		return (*(NODE **)data.data);
E 11
I 11
		bcopy(data.data, &n, sizeof(n));
		return (n);
E 11
	case 1:
		break;
	default:
	case -1:
D 13
		err("db: get %s: %s", name, strerror(errno));
E 13
I 13
		err(1, "db: %s", name);
E 13
	}

	if ((n = malloc(sizeof(NODE) + key.size)) == NULL)
E 8
D 13
		err("%s", strerror(errno));
E 13
I 13
		err(1, NULL);
E 13
E 7

	n->n_narcs = 0;
	n->n_arcsize = 0;
D 7
	n->n_arcs = (NODE **)NULL;
E 7
I 7
	n->n_arcs = NULL;
E 7
	n->n_refcnt = 0;
	n->n_flags = 0;
I 8
	bcopy(name, n->n_name, key.size);
E 8

D 8
	/* add to linked list */
E 8
I 8
	/* Add to linked list. */
E 8
D 13
	if (n->n_next = graph)
E 13
I 13
	if ((n->n_next = graph) != NULL)
E 13
		graph->n_prevp = &n->n_next;
	n->n_prevp = &graph;
	graph = n;

D 8
	/* add to hash table */
	hash = hash_string(name);
	n->n_hash = hashtable[hash];
	hashtable[hash] = n;
E 8
I 8
	/* Add to hash table. */
	data.data = &n;
	data.size = sizeof(n);
	if ((*db->put)(db, &key, &data, 0))
D 13
		err("db: put %s: %s", name, strerror(errno));
E 13
I 13
		err(1, "db: %s", name);
E 13
E 8
D 7
	return(n);
E 7
I 7
	return (n);
E 7
E 4
}

I 13

/*
 * Clear the NODEST flag from all nodes.
 */
void
clear_cycle()
{
	NODE *n;

	for (n = graph; n != NULL; n = n->n_next)
		n->n_flags &= ~NF_NODEST;
}

E 13
D 4
note(s,t)
char *s,*t;
E 4
I 4
/* do topological sort on graph */
void
tsort()
E 4
{
D 4
	fprintf(stderr,"tsort: %s%s\n",s,t);
E 4
I 4
	register NODE *n, *next;
D 13
	register int cnt;
E 13
I 13
	register int cnt, i;
E 13

D 13
	while (graph) {
E 13
I 13
	while (graph != NULL) {
E 13
		/*
D 9
		 * keep getting rid of simple cases until there are none left,
E 9
I 9
		 * Keep getting rid of simple cases until there are none left,
E 9
		 * if there are any nodes still in the graph, then there is
		 * a cycle in it.
		 */
		do {
D 13
			for (cnt = 0, n = graph; n; n = next) {
E 13
I 13
			for (cnt = 0, n = graph; n != NULL; n = next) {
E 13
				next = n->n_next;
				if (n->n_refcnt == 0) {
					remove_node(n);
					++cnt;
				}
			}
D 13
		} while (graph && cnt);
E 13
I 13
		} while (graph != NULL && cnt);
E 13

D 13
		if (!graph)
E 13
I 13
		if (graph == NULL)
E 13
			break;

		if (!cycle_buf) {
			/*
D 10
			 * allocate space for two cycle logs - one to be used
E 10
I 10
			 * Allocate space for two cycle logs - one to be used
E 10
			 * as scratch space, the other to save the longest
			 * cycle.
			 */
D 13
			for (cnt = 0, n = graph; n; n = n->n_next)
E 13
I 13
			for (cnt = 0, n = graph; n != NULL; n = n->n_next)
E 13
				++cnt;
D 9
			cycle_buf =
			    (NODE **)malloc((u_int)sizeof(NODE *) * cnt);
			longest_cycle =
			    (NODE **)malloc((u_int)sizeof(NODE *) * cnt);
			if (!cycle_buf || !longest_cycle)
E 9
I 9
			cycle_buf = malloc((u_int)sizeof(NODE *) * cnt);
			longest_cycle = malloc((u_int)sizeof(NODE *) * cnt);
			if (cycle_buf == NULL || longest_cycle == NULL)
E 9
D 7
				no_memory();
E 7
I 7
D 13
				err("%s", strerror(errno));
E 13
I 13
				err(1, NULL);
E 13
E 7
		}
D 13
		for (n = graph; n; n = n->n_next)
			if (!(n->n_flags & NF_ACYCLIC)) {
E 13
I 13
		for (n = graph; n != NULL; n = n->n_next)
			if (!(n->n_flags & NF_ACYCLIC))
E 13
				if (cnt = find_cycle(n, n, 0, 0)) {
D 13
					register int i;

					(void)fprintf(stderr,
D 7
					    "tsort: cycle in data.\n");
E 7
I 7
					    "tsort: cycle in data\n");
E 13
I 13
					warnx("cycle in data");
E 13
E 7
					for (i = 0; i < cnt; i++)
D 13
						(void)fprintf(stderr,
D 7
				"tsort: %s.\n", longest_cycle[i]->n_name);
E 7
I 7
				"tsort: %s\n", longest_cycle[i]->n_name);
E 13
I 13
						warnx("%s", 
						    longest_cycle[i]->n_name);
E 13
E 7
					remove_node(n);
I 13
					clear_cycle();
E 13
					break;
D 13
				} else
E 13
I 13
				} else {
E 13
					/* to avoid further checks */
D 13
					n->n_flags  = NF_ACYCLIC;
			}
E 13
I 13
					n->n_flags  |= NF_ACYCLIC;
					clear_cycle();
				}
E 13

D 7
		if (!n) {
			(void)fprintf(stderr,
			    "tsort: internal error -- could not find cycle.\n");
			exit(1);
		}
E 7
I 7
D 13
		if (!n)
			err("internal error -- could not find cycle");
E 13
I 13
		if (n == NULL)
			errx(1, "internal error -- could not find cycle");
E 13
E 7
	}
E 4
}

D 4
/*	given that there is a cycle, find some
 *	node in it
*/
struct nodelist *
findloop()
E 4
I 4
/* print node and remove from graph (does not actually free node) */
void
remove_node(n)
	register NODE *n;
E 4
{
D 4
	register struct nodelist *i, *j;
	for(i= &firstnode; i->nextnode!=NULL; i=i->nextnode)
		if(i->live==LIVE)
			break;
	note("cycle in data",empty);
	i = mark(i);
	if(i==NULL)
		error("program error",empty);
	for(j= &firstnode; j->nextnode!=NULL; j=j->nextnode)
		if(j->live==VISITED)
			j->live = LIVE;
	return(i);
E 4
I 4
	register NODE **np;
	register int i;

	(void)printf("%s\n", n->n_name);
	for (np = n->n_arcs, i = n->n_narcs; --i >= 0; np++)
		--(*np)->n_refcnt;
	n->n_narcs = 0;
	*n->n_prevp = n->n_next;
	if (n->n_next)
		n->n_next->n_prevp = n->n_prevp;
E 4
}

D 4
/*	depth-first search of LIVE predecessors
 *	to find some element of a cycle;
 *	VISITED is a temporary state recording the
 *	visits of the search
*/
struct nodelist *
mark(i)
register struct nodelist *i;
E 4
I 4
D 13
/* look for the longest cycle from node from to node to. */
E 13
I 13

/* look for the longest? cycle from node from to node to. */
E 13
I 7
int
E 7
find_cycle(from, to, longest_len, depth)
	NODE *from, *to;
	int depth, longest_len;
E 4
{
D 4
	register struct nodelist *j;
	register struct predlist *t;
	if(i->live==DEAD)
		return(NULL);
	if(i->live==VISITED)
		return(i);
	i->live = VISITED;
	for(t=i->inedges; t!=NULL; t=t->nextpred) {
		j = mark(t->pred);
		if(j!=NULL) {
			note(i->name,empty);
			return(j);
E 4
I 4
	register NODE **np;
	register int i, len;

	/*
	 * avoid infinite loops and ignore portions of the graph known
	 * to be acyclic
	 */
D 13
	if (from->n_flags & (NF_MARK|NF_ACYCLIC))
E 13
I 13
	if (from->n_flags & (NF_NODEST|NF_MARK|NF_ACYCLIC))
E 13
D 7
		return(0);
E 7
I 7
		return (0);
E 7
D 13
	from->n_flags = NF_MARK;
E 13
I 13
	from->n_flags |= NF_MARK;
E 13

	for (np = from->n_arcs, i = from->n_narcs; --i >= 0; np++) {
		cycle_buf[depth] = *np;
		if (*np == to) {
			if (depth + 1 > longest_len) {
				longest_len = depth + 1;
				(void)memcpy((char *)longest_cycle,
				    (char *)cycle_buf,
				    longest_len * sizeof(NODE *));
			}
		} else {
I 13
			if ((*np)->n_flags & (NF_MARK|NF_ACYCLIC|NF_NODEST))
				continue;
E 13
			len = find_cycle(*np, to, longest_len, depth + 1);
I 13

			if (debug)
				(void)printf("%*s %s->%s %d\n", depth, "",
				    from->n_name, to->n_name, len);

			if (len == 0)
				(*np)->n_flags |= NF_NODEST;

E 13
			if (len > longest_len)
				longest_len = len;
I 13

			if (len > 0 && !longest)
				break;
E 13
E 4
		}
	}
D 4
	return(NULL);
E 4
I 4
	from->n_flags &= ~NF_MARK;
D 7
	return(longest_len);
E 7
I 7
	return (longest_len);
E 7
}

void
D 7
no_memory()
E 7
I 7
usage()
E 7
{
D 7
	(void)fprintf(stderr, "tsort: %s.\n", strerror(ENOMEM));
E 7
I 7
D 13
	(void)fprintf(stderr, "usage: tsort [file]\n");
E 13
I 13
	(void)fprintf(stderr, "usage: tsort [-l] [file]\n");
E 13
E 7
	exit(1);
I 7
D 13
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "tsort: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 13
E 7
E 4
}
E 1
