h60077
s 00005/00003/00119
d D 8.2 94/04/16 13:56:52 bostic 14 13
c put the optoins array into text space
c option() is now static to op
e
s 00002/00002/00120
d D 8.1 93/06/06 14:39:31 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00045/00056/00077
d D 5.12 93/05/01 11:51:41 bostic 12 11
c use library err/warn(3) functions; lint, prettiness police
e
s 00002/00002/00131
d D 5.11 91/08/21 22:47:59 bostic 11 10
c make options static, make the comment clearer
e
s 00001/00001/00132
d D 5.10 91/08/21 16:43:34 torek 10 9
c do not strcmp NULL (just take it out of the table entirely)
e
s 00001/00000/00132
d D 5.9 91/07/19 15:05:14 bostic 9 8
c add -path, -fstype rdonly; document values for PLAN->flags
e
s 00003/00003/00129
d D 5.8 91/06/04 16:49:25 bostic 8 7
c ANSI function pointers are fun!
e
s 00044/00050/00088
d D 5.7 91/05/24 15:17:15 bostic 7 6
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00033/00033/00105
d D 5.6 91/05/23 18:53:27 bostic 6 5
c T_USER used in the kernel, included by <sys/param.h> -- change to
c be N_ instead.  Make it an enum while we're there...
e
s 00002/00000/00136
d D 5.5 91/03/09 18:44:22 bostic 5 4
c ANSI
e
s 00002/00003/00134
d D 5.4 90/11/15 12:22:50 bostic 4 3
c make status variables consistent
e
s 00005/00002/00132
d D 5.3 90/07/01 17:09:52 bostic 3 2
c -a wasn't getting discarded completely; test case is:
c find /tmp '(' -fstype local -o -prune ')' -a -print
e
s 00039/00029/00095
d D 5.2 90/05/12 15:29:40 bostic 2 1
c new syntax
e
s 00124/00000/00000
d D 5.1 90/04/16 17:23:12 bostic 1 0
c new version derived from Cimarron Taylor's
e
u
U
t
T
I 1
/*-
D 13
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
D 14
 * Copyright (c) 1990, 1993
E 14
I 14
 * Copyright (c) 1990, 1993, 1994
E 14
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
I 12

#include <err.h>
E 12
#include <fts.h>
#include <stdio.h>
I 5
#include <stdlib.h>
#include <string.h>
I 12

E 12
E 5
#include "find.h"

I 14
static OPTION *option __P((char *));

E 14
D 12
typedef struct _option {
	char *name;		/* option name */
D 6
	int token;		/* token value */
E 6
I 6
	enum ntype token;	/* token type */
E 6
	PLAN *(*create)();	/* create function */
#define	O_NONE		0x01	/* no call required */
#define	O_ZERO		0x02	/* pass: nothing */
#define	O_ARGV		0x04	/* pass: argv, increment argv */
D 6
#define	O_ARGVP		0x08	/* pass: *argv, T_OK || T_EXEC */
E 6
I 6
#define	O_ARGVP		0x08	/* pass: *argv, N_OK || N_EXEC */
E 6
I 2
D 7
#define	O_MASK		0x0f	/* mask of op bits */
#define	O_OLD		0x10	/* deprecated syntax */
#define	O_NEW		0x20	/* new syntax */
E 7
E 2
	int flags;
} OPTION;

E 12
I 10
D 11
/* NB: the following table must be sorted in machine (strcmp) order */
E 10
D 7
PLAN	*c_atime(), *c_ctime(), *c_depth(), *c_exec(), *c_follow(),
	*c_fstype(), *c_group(), *c_inum(), *c_links(), *c_ls(),
	*c_mtime(), *c_name(), *c_newer(), *c_nogroup(), *c_nouser(),
D 2
	*c_ok(), *c_perm(), *c_print(), *c_prune(), *c_size(), *c_type(),
E 2
I 2
	*c_perm(), *c_print(), *c_prune(), *c_size(), *c_type(),
E 2
	*c_user(), *c_xdev(), *c_openparen(), *c_closeparen(), *c_not(),
	*c_or();

E 7
OPTION options[] = {
E 11
I 11
/* NB: the following table must be sorted lexically. */
D 14
static OPTION options[] = {
E 14
I 14
static OPTION const options[] = {
E 14
E 11
D 6
	"!",		T_NOT,		c_not,		O_ZERO,
	"(",		T_OPENPAREN,	c_openparen,	O_ZERO,
	")",		T_CLOSEPAREN,	c_closeparen,	O_ZERO,
D 2
	"-a",		T_AND,		(PLAN *(*)())-1,O_NONE,
	"-atime",	T_ATIME,	c_atime,	O_ARGV,
	"-ctime",	T_CTIME,	c_ctime,	O_ARGV,
	"-depth",	T_DEPTH,	c_depth,	O_ZERO,
	"-exec",	T_EXEC,		c_exec,		O_ARGVP,
	"-follow",	T_FOLLOW,	c_follow,	O_ZERO,
	"-fstype",	T_FSTYPE,	c_fstype,	O_ARGV,
	"-group",	T_GROUP,	c_group,	O_ARGV,
	"-inum",	T_INUM,		c_inum,		O_ARGV,
	"-links",	T_LINKS,	c_links,	O_ARGV,
	"-ls",		T_LS,		c_ls,		O_ZERO,
	"-mtime",	T_MTIME,	c_mtime,	O_ARGV,
	"-name",	T_NAME,		c_name,		O_ARGV,
	"-newer",	T_NEWER,	c_newer,	O_ARGV,
	"-nogroup",	T_NOGROUP,	c_nogroup,	O_ZERO,
	"-nouser",	T_NOUSER,	c_nouser,	O_ZERO,
	"-o",		T_OR,		c_or,		O_ZERO,
	"-ok",		T_OK,		c_exec,		O_ARGVP,
	"-perm",	T_PERM,		c_perm,		O_ARGV,
	"-print",	T_PRINT,	c_print,	O_ZERO,
	"-prune",	T_PRUNE,	c_prune,	O_ZERO,
	"-size",	T_SIZE,		c_size,		O_ARGV,
	"-type",	T_TYPE,		c_type,		O_ARGV,
	"-user",	T_USER,		c_user,		O_ARGV,
	"-xdev",	T_XDEV,		c_xdev,		O_ZERO,
E 2
I 2
D 3
	"a",		T_AND,		(PLAN *(*)())-1,O_NONE|O_OLD,
	"and",		T_AND,		(PLAN *(*)())-1,O_NONE|O_NEW,
E 3
I 3
	"a",		T_AND,		NULL,		O_NONE|O_OLD,
	"and",		T_AND,		NULL,		O_NONE|O_NEW,
E 3
	"atime",	T_ATIME,	c_atime,	O_ARGV,
	"ctime",	T_CTIME,	c_ctime,	O_ARGV,
	"depth",	T_DEPTH,	c_depth,	O_ZERO|O_OLD,
	"exec",		T_EXEC,		c_exec,		O_ARGVP,
	"follow",	T_FOLLOW,	c_follow,	O_ZERO|O_OLD,
	"fstype",	T_FSTYPE,	c_fstype,	O_ARGV,
	"group",	T_GROUP,	c_group,	O_ARGV,
	"inum",		T_INUM,		c_inum,		O_ARGV,
	"links",	T_LINKS,	c_links,	O_ARGV,
	"ls",		T_LS,		c_ls,		O_ZERO,
	"mtime",	T_MTIME,	c_mtime,	O_ARGV,
	"name",		T_NAME,		c_name,		O_ARGV,
	"newer",	T_NEWER,	c_newer,	O_ARGV,
	"nogroup",	T_NOGROUP,	c_nogroup,	O_ZERO,
	"nouser",	T_NOUSER,	c_nouser,	O_ZERO,
	"o",		T_OR,		c_or,		O_ZERO|O_OLD,
	"ok",		T_OK,		c_exec,		O_ARGVP,
	"or",		T_OR,		c_or,		O_ZERO|O_NEW,
	"perm",		T_PERM,		c_perm,		O_ARGV,
	"print",	T_PRINT,	c_print,	O_ZERO,
	"prune",	T_PRUNE,	c_prune,	O_ZERO,
	"size",		T_SIZE,		c_size,		O_ARGV,
	"type",		T_TYPE,		c_type,		O_ARGV,
	"user",		T_USER,		c_user,		O_ARGV,
	"xdev",		T_XDEV,		c_xdev,		O_ZERO|O_OLD,
E 6
I 6
D 12
	"!",		N_NOT,		c_not,		O_ZERO,
	"(",		N_OPENPAREN,	c_openparen,	O_ZERO,
	")",		N_CLOSEPAREN,	c_closeparen,	O_ZERO,
D 7
	"a",		N_AND,		NULL,		O_NONE|O_OLD,
	"and",		N_AND,		NULL,		O_NONE|O_NEW,
	"atime",	N_ATIME,	c_atime,	O_ARGV,
	"ctime",	N_CTIME,	c_ctime,	O_ARGV,
	"depth",	N_DEPTH,	c_depth,	O_ZERO|O_OLD,
	"exec",		N_EXEC,		c_exec,		O_ARGVP,
	"follow",	N_FOLLOW,	c_follow,	O_ZERO|O_OLD,
	"fstype",	N_FSTYPE,	c_fstype,	O_ARGV,
	"group",	N_GROUP,	c_group,	O_ARGV,
	"inum",		N_INUM,		c_inum,		O_ARGV,
	"links",	N_LINKS,	c_links,	O_ARGV,
	"ls",		N_LS,		c_ls,		O_ZERO,
	"mtime",	N_MTIME,	c_mtime,	O_ARGV,
	"name",		N_NAME,		c_name,		O_ARGV,
	"newer",	N_NEWER,	c_newer,	O_ARGV,
	"nogroup",	N_NOGROUP,	c_nogroup,	O_ZERO,
	"nouser",	N_NOUSER,	c_nouser,	O_ZERO,
	"o",		N_OR,		c_or,		O_ZERO|O_OLD,
	"ok",		N_OK,		c_exec,		O_ARGVP,
	"or",		N_OR,		c_or,		O_ZERO|O_NEW,
	"perm",		N_PERM,		c_perm,		O_ARGV,
	"print",	N_PRINT,	c_print,	O_ZERO,
	"prune",	N_PRUNE,	c_prune,	O_ZERO,
	"size",		N_SIZE,		c_size,		O_ARGV,
	"type",		N_TYPE,		c_type,		O_ARGV,
	"user",		N_USER,		c_user,		O_ARGV,
	"xdev",		N_XDEV,		c_xdev,		O_ZERO|O_OLD,
E 7
I 7
	"-a",		N_AND,		NULL,		O_NONE,
	"-and",		N_AND,		NULL,		O_NONE,
	"-atime",	N_ATIME,	c_atime,	O_ARGV,
	"-ctime",	N_CTIME,	c_ctime,	O_ARGV,
	"-depth",	N_DEPTH,	c_depth,	O_ZERO,
	"-exec",	N_EXEC,		c_exec,		O_ARGVP,
	"-follow",	N_FOLLOW,	c_follow,	O_ZERO,
	"-fstype",	N_FSTYPE,	c_fstype,	O_ARGV,
	"-group",	N_GROUP,	c_group,	O_ARGV,
	"-inum",	N_INUM,		c_inum,		O_ARGV,
	"-links",	N_LINKS,	c_links,	O_ARGV,
	"-ls",		N_LS,		c_ls,		O_ZERO,
	"-mtime",	N_MTIME,	c_mtime,	O_ARGV,
	"-name",	N_NAME,		c_name,		O_ARGV,
	"-newer",	N_NEWER,	c_newer,	O_ARGV,
	"-nogroup",	N_NOGROUP,	c_nogroup,	O_ZERO,
	"-nouser",	N_NOUSER,	c_nouser,	O_ZERO,
	"-o",		N_OR,		c_or,		O_ZERO,
	"-ok",		N_OK,		c_exec,		O_ARGVP,
	"-or",		N_OR,		c_or,		O_ZERO,
I 9
	"-path", 	N_PATH,		c_path,		O_ARGV,
E 9
	"-perm",	N_PERM,		c_perm,		O_ARGV,
	"-print",	N_PRINT,	c_print,	O_ZERO,
	"-prune",	N_PRUNE,	c_prune,	O_ZERO,
	"-size",	N_SIZE,		c_size,		O_ARGV,
	"-type",	N_TYPE,		c_type,		O_ARGV,
	"-user",	N_USER,		c_user,		O_ARGV,
	"-xdev",	N_XDEV,		c_xdev,		O_ZERO,
E 12
I 12
	{ "!",		N_NOT,		c_not,		O_ZERO },
	{ "(",		N_OPENPAREN,	c_openparen,	O_ZERO },
	{ ")",		N_CLOSEPAREN,	c_closeparen,	O_ZERO },
	{ "-a",		N_AND,		NULL,		O_NONE },
	{ "-and",	N_AND,		NULL,		O_NONE },
	{ "-atime",	N_ATIME,	c_atime,	O_ARGV },
	{ "-ctime",	N_CTIME,	c_ctime,	O_ARGV },
	{ "-depth",	N_DEPTH,	c_depth,	O_ZERO },
	{ "-exec",	N_EXEC,		c_exec,		O_ARGVP },
	{ "-follow",	N_FOLLOW,	c_follow,	O_ZERO },
	{ "-fstype",	N_FSTYPE,	c_fstype,	O_ARGV },
	{ "-group",	N_GROUP,	c_group,	O_ARGV },
	{ "-inum",	N_INUM,		c_inum,		O_ARGV },
	{ "-links",	N_LINKS,	c_links,	O_ARGV },
	{ "-ls",	N_LS,		c_ls,		O_ZERO },
	{ "-mtime",	N_MTIME,	c_mtime,	O_ARGV },
	{ "-name",	N_NAME,		c_name,		O_ARGV },
	{ "-newer",	N_NEWER,	c_newer,	O_ARGV },
	{ "-nogroup",	N_NOGROUP,	c_nogroup,	O_ZERO },
	{ "-nouser",	N_NOUSER,	c_nouser,	O_ZERO },
	{ "-o",		N_OR,		c_or,		O_ZERO },
	{ "-ok",	N_OK,		c_exec,		O_ARGVP },
	{ "-or",	N_OR,		c_or,		O_ZERO },
	{ "-path", 	N_PATH,		c_path,		O_ARGV },
	{ "-perm",	N_PERM,		c_perm,		O_ARGV },
	{ "-print",	N_PRINT,	c_print,	O_ZERO },
	{ "-prune",	N_PRUNE,	c_prune,	O_ZERO },
	{ "-size",	N_SIZE,		c_size,		O_ARGV },
	{ "-type",	N_TYPE,		c_type,		O_ARGV },
	{ "-user",	N_USER,		c_user,		O_ARGV },
	{ "-xdev",	N_XDEV,		c_xdev,		O_ZERO },
E 12
E 7
E 6
E 2
D 10
	{ NULL },
E 10
};

/*
 * find_create --
 *	create a node corresponding to a command line argument.
 *
 * TODO:
 *	add create/process function pointers to node, so we can skip
 *	this switch stuff.
 */
PLAN *
find_create(argvp)
	char ***argvp;
{
I 2
D 4
	extern int deprecated;
E 4
E 2
	register OPTION *p;
D 7
	OPTION tmp;
E 7
	PLAN *new;
	char **argv;
D 2
	OPTION *find_typelookup();
E 2
D 7
	int typecompare();
E 7
I 7
D 12
	OPTION *option();
E 12
E 7

	argv = *argvp;
D 7
	tmp.name = *argv++;
E 7

I 2
D 7
	/* strip off any leading dash */
	if (*tmp.name == '-')
		++tmp.name;

E 2
	p = (OPTION *)bsearch(&tmp, options, sizeof(options)/sizeof(OPTION),
	    sizeof(OPTION), typecompare);
D 2
	if (!p) {
E 2
I 2
D 4
	if (!p || deprecated && p->flags&O_NEW ||
	    !deprecated && p->flags&O_OLD) {
E 4
I 4
	if (!p || isdeprecated && p->flags&O_NEW ||
	    !isdeprecated && p->flags&O_OLD) {
E 4
E 2
		(void)fprintf(stderr, "find: unknown option %s.\n", *--argv);
E 7
I 7
D 12
	if ((p = option(*argv)) == NULL) {
		(void)fprintf(stderr, "find: unknown option %s.\n", *argv);
E 7
		exit(1);
	}
E 12
I 12
	if ((p = option(*argv)) == NULL)
		errx(1, "%s: unknown option", *argv);
E 12
I 7
	++argv;
E 7
D 12
	if (p->flags & (O_ARGV|O_ARGVP) && !*argv) {
		(void)fprintf(stderr,
		    "find: %s requires additional arguments.\n", *--argv);
		exit(1);
	}
E 12
I 12
	if (p->flags & (O_ARGV|O_ARGVP) && !*argv)
		errx(1, "%s: requires additional arguments", *--argv);
E 12

D 2
	switch(p->flags) {
E 2
I 2
D 7
	switch(p->flags&O_MASK) {
E 7
I 7
	switch(p->flags) {
E 7
I 3
	case O_NONE:
		new = NULL;
		break;
E 3
E 2
	case O_ZERO:
		new = (p->create)();
		break;
	case O_ARGV:
		new = (p->create)(*argv++);
		break;
	case O_ARGVP:
D 6
		new = (p->create)(&argv, p->token == T_OK);
E 6
I 6
		new = (p->create)(&argv, p->token == N_OK);
E 6
		break;
I 12
	default:
		abort();
E 12
	}
	*argvp = argv;
D 12
	return(new);
E 12
I 12
	return (new);
E 12
}

I 7
D 14
OPTION *
E 14
I 14
static OPTION *
E 14
option(name)
	char *name;
{
	OPTION tmp;
D 8
	int typecompare();
E 8
I 8
	int typecompare __P((const void *, const void *));
E 8

	tmp.name = name;
D 12
	return((OPTION *)bsearch(&tmp, options,
E 12
I 12
	return ((OPTION *)bsearch(&tmp, options,
E 12
	    sizeof(options)/sizeof(OPTION), sizeof(OPTION), typecompare));
}
D 12
	
E 12
I 12

int
E 12
E 7
typecompare(a, b)
D 8
	OPTION *a, *b;
E 8
I 8
	const void *a, *b;
E 8
{
D 8
	return(strcmp(a->name, b->name));
E 8
I 8
D 12
	return(strcmp(((OPTION *)a)->name, ((OPTION *)b)->name));
E 12
I 12
	return (strcmp(((OPTION *)a)->name, ((OPTION *)b)->name));
E 12
E 8
}
E 1
