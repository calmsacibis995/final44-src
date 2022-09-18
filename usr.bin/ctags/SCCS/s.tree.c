h46061
s 00001/00001/00108
d D 8.3 94/04/02 10:08:52 pendry 9 8
c add 1994 copyright
e
s 00034/00035/00075
d D 8.2 94/04/01 13:02:00 pendry 8 7
c prettyness police
e
s 00002/00002/00108
d D 8.1 93/06/06 14:29:57 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00109
d D 5.6 93/01/22 17:13:15 bostic 6 5
c cfree -> free
e
s 00013/00005/00097
d D 5.5 91/02/26 13:42:21 bostic 5 4
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00101
d D 5.4 90/06/01 15:58:36 bostic 4 3
c new copyright notice
e
s 00001/00001/00111
d D 5.3 90/05/15 19:51:08 bostic 3 2
c string.h is ANSI C include file
e
s 00015/00004/00097
d D 5.2 88/12/31 12:32:34 bostic 2 1
c original by Ken Arnold -- Berkeley copyright
e
s 00101/00000/00000
d D 5.1 87/03/16 17:57:36 bostic 1 0
c date and time created 87/03/16 17:57:36 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 7
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1987, 1993
E 9
I 9
 * Copyright (c) 1987, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

D 5
#include <ctags.h>
E 5
I 5
D 8
#include <errno.h>
E 8
I 8
#include <err.h>
#include <limits.h>
E 8
#include <stdio.h>
#include <stdlib.h>
E 5
D 3
#include <strings.h>
E 3
I 3
#include <string.h>
I 8

E 8
I 5
#include "ctags.h"
E 5
E 3

I 8
static void	add_node __P((NODE *, NODE *));
static void	free_tree __P((NODE *));

E 8
/*
 * pfnote --
 *	enter a new node in the tree
 */
D 8
pfnote(name,ln)
E 8
I 8
void
pfnote(name, ln)
E 8
	char	*name;
	int	ln;
{
D 8
	extern NODE	*head;		/* head of the sorted binary tree */
	extern char	*curfile;	/* current input file name */
	register NODE	*np;
	register char	*fp;
E 8
I 8
	NODE	*np;
	char	*fp;
E 8
D 5
	char	nbuf[MAXTOKEN],
		*malloc(), *savestr();
E 5
I 5
	char	nbuf[MAXTOKEN];
E 5

	/*NOSTRICT*/
	if (!(np = (NODE *)malloc(sizeof(NODE)))) {
D 8
		fputs("ctags: too many entries to sort\n",stderr);
E 8
I 8
		warnx("too many entries to sort");
E 8
		put_entries(head);
		free_tree(head);
		/*NOSTRICT*/
D 8
		if (!(head = np = (NODE *)malloc(sizeof(NODE)))) {
			fputs("ctags: out of space.\n",stderr);
			exit(1);
		}
E 8
I 8
		if (!(head = np = (NODE *)malloc(sizeof(NODE))))
			err(1, "out of space");
E 8
	}
D 8
	if (!xflag && !strcmp(name,"main")) {
		if (!(fp = rindex(curfile,'/')))
E 8
I 8
	if (!xflag && !strcmp(name, "main")) {
		if (!(fp = strrchr(curfile, '/')))
E 8
			fp = curfile;
		else
			++fp;
D 8
		(void)sprintf(nbuf,"M%s",fp);
		fp = rindex(nbuf,'.');
E 8
I 8
		(void)sprintf(nbuf, "M%s", fp);
		fp = strrchr(nbuf, '.');
E 8
		if (fp && !fp[2])
			*fp = EOS;
		name = nbuf;
	}
D 5
	np->entry = savestr(name);
E 5
I 5
D 8
	if (!(np->entry = strdup(name))) {
		(void)fprintf(stderr, "ctags: %s\n", strerror(errno));
		exit(1);
	}
E 8
I 8
	if (!(np->entry = strdup(name)))
		err(1, NULL);
E 8
E 5
	np->file = curfile;
	np->lno = ln;
	np->left = np->right = 0;
D 5
	np->pat = savestr(lbuf);
E 5
I 5
D 8
	if (!(np->pat = strdup(lbuf))) {
		(void)fprintf(stderr, "ctags: %s\n", strerror(errno));
		exit(1);
	}
E 8
I 8
	if (!(np->pat = strdup(lbuf)))
		err(1, NULL);
E 8
E 5
	if (!head)
		head = np;
	else
D 8
		add_node(np,head);
E 8
I 8
		add_node(np, head);
E 8
}

D 8
add_node(node,cur_node)
	register NODE	*node,
			*cur_node;
E 8
I 8
static void
add_node(node, cur_node)
	NODE	*node,
		*cur_node;
E 8
{
D 8
	extern int	wflag;			/* -w: suppress warnings */
	register int	dif;
E 8
I 8
	int	dif;
E 8

D 8
	dif = strcmp(node->entry,cur_node->entry);
E 8
I 8
	dif = strcmp(node->entry, cur_node->entry);
E 8
	if (!dif) {
		if (node->file == cur_node->file) {
			if (!wflag)
D 8
				fprintf(stderr,"Duplicate entry in file %s, line %d: %s\nSecond entry ignored\n",node->file,lineno,node->entry);
E 8
I 8
				fprintf(stderr, "Duplicate entry in file %s, line %d: %s\nSecond entry ignored\n", node->file, lineno, node->entry);
E 8
			return;
		}
		if (!cur_node->been_warned)
			if (!wflag)
D 8
				fprintf(stderr,"Duplicate entry in files %s and %s: %s (Warning only)\n",node->file,cur_node->file,node->entry);
E 8
I 8
				fprintf(stderr, "Duplicate entry in files %s and %s: %s (Warning only)\n", node->file, cur_node->file, node->entry);
E 8
		cur_node->been_warned = YES;
	}
	else if (dif < 0)
		if (cur_node->left)
D 8
			add_node(node,cur_node->left);
E 8
I 8
			add_node(node, cur_node->left);
E 8
		else
			cur_node->left = node;
	else if (cur_node->right)
D 8
		add_node(node,cur_node->right);
E 8
I 8
		add_node(node, cur_node->right);
E 8
	else
		cur_node->right = node;
}

I 8
static void
E 8
free_tree(node)
D 8
	register NODE	*node;
E 8
I 8
	NODE	*node;
E 8
{
	while (node) {
		if (node->right)
			free_tree(node->right);
D 6
		cfree(node);
E 6
I 6
		free(node);
E 6
		node = node->left;
	}
}
E 1
