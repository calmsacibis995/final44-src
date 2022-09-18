h38477
s 00015/00006/00219
d D 8.3 95/05/04 17:59:33 christos 7 6
c 
e
s 00001/00001/00224
d D 8.2 95/04/28 10:23:58 bostic 6 5
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00000/00000/00225
d D 8.1 93/05/31 15:29:32 bostic 5 4
c yank to 8.1
e
s 00014/00000/00211
d D 1.3 93/05/31 15:28:48 bostic 4 2
c add copyright notices, SCCS headers, yank to 8.1
e
s 00014/00000/00211
d R 8.1 93/05/31 15:25:20 bostic 3 2
c add copyright notices, SCCS headers, yank to 8.1
e
s 00000/00019/00211
d D 1.2 92/07/15 10:36:18 marc 2 1
c remove debug routine
e
s 00230/00000/00000
d D 1.1 92/05/22 15:06:16 marc 1 0
c date and time created 92/05/22 15:06:16 by marc
e
u
U
t
T
I 4
/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 7
#include <stdlib.h>
E 7
E 4
I 1
#include "shell.h"
#include "input.h"
#include "output.h"
#include "error.h"
#include "memalloc.h"
#include "mystring.h"
#include "alias.h"
#include "options.h"	/* XXX for argptr (should remove?) */

#define ATABSIZE 39

struct alias *atab[ATABSIZE];

I 7
STATIC void setalias __P((char *, char *));
STATIC int unalias __P((char *));
E 7
STATIC struct alias **hashalias __P((char *));

STATIC
I 7
void
E 7
setalias(name, val)
	char *name, *val;
D 7
	{
E 7
I 7
{
E 7
	struct alias *ap, **app;

	app = hashalias(name);
	for (ap = *app; ap; ap = ap->next) {
		if (equal(name, ap->name)) {
			INTOFF;
			ckfree(ap->val);
			ap->val	= savestr(val);
			INTON;
			return;
		}
	}
	/* not found */
	INTOFF;
	ap = ckmalloc(sizeof (struct alias));
	ap->name = savestr(name);
	/*
	 * XXX - HACK: in order that the parser will not finish reading the
	 * alias value off the input before processing the next alias, we
	 * dummy up an extra space at the end of the alias.  This is a crock
	 * and should be re-thought.  The idea (if you feel inclined to help)
	 * is to avoid alias recursions.  The mechanism used is: when
	 * expanding an alias, the value of the alias is pushed back on the
	 * input as a string and a pointer to the alias is stored with the
	 * string.  The alias is marked as being in use.  When the input
	 * routine finishes reading the string, it markes the alias not
	 * in use.  The problem is synchronization with the parser.  Since
	 * it reads ahead, the alias is marked not in use before the
	 * resulting token(s) is next checked for further alias sub.  The
	 * H A C K is that we add a little fluff after the alias value
	 * so that the string will not be exhausted.  This is a good
	 * idea ------- ***NOT***
	 */
#ifdef notyet
	ap->val = savestr(val);
#else /* hack */
	{
	int len = strlen(val);
	ap->val = ckmalloc(len + 2);
D 6
	bcopy(val, ap->val, len);
E 6
I 6
D 7
	memmove(ap->val, val, len);
E 7
I 7
	memcpy(ap->val, val, len);
E 7
E 6
	ap->val[len] = ' ';	/* fluff */
	ap->val[len+1] = '\0';
	}
#endif
	ap->next = *app;
	*app = ap;
	INTON;
}

STATIC int
unalias(name)
	char *name;
	{
	struct alias *ap, **app;

	app = hashalias(name);

	for (ap = *app; ap; app = &(ap->next), ap = ap->next) {
		if (equal(name, ap->name)) {
			/*
			 * if the alias is currently in use (i.e. its
			 * buffer is being used by the input routine) we
			 * just null out the name instead of freeing it.
			 * We could clear it out later, but this situation
			 * is so rare that it hardly seems worth it.
			 */
			if (ap->flag & ALIASINUSE)
				*ap->name = '\0';
			else {
				INTOFF;
				*app = ap->next;
				ckfree(ap->name);
				ckfree(ap->val);
				ckfree(ap);
				INTON;
			}
			return (0);
		}
	}

	return (1);
}

#ifdef mkinit
MKINIT void rmaliases();

SHELLPROC {
	rmaliases();
}
#endif

void
rmaliases() {
	struct alias *ap, *tmp;
	int i;

	INTOFF;
	for (i = 0; i < ATABSIZE; i++) {
		ap = atab[i];
		atab[i] = NULL;
		while (ap) {
			ckfree(ap->name);
			ckfree(ap->val);
			tmp = ap;
			ap = ap->next;
			ckfree(tmp);
		}
	}
	INTON;
}

struct alias *
lookupalias(name, check)
	char *name;
D 7
	{
E 7
I 7
	int check;
{
E 7
	struct alias *ap = *hashalias(name);

	for (; ap; ap = ap->next) {
		if (equal(name, ap->name)) {
			if (check && (ap->flag & ALIASINUSE))
				return (NULL);
			return (ap);
		}
	}

	return (NULL);
}

/*
 * TODO - sort output
 */
I 7
int
E 7
aliascmd(argc, argv)
I 7
	int argc;
E 7
	char **argv;
D 7
	{
E 7
I 7
{
E 7
	char *n, *v;
	int ret = 0;
	struct alias *ap;

	if (argc == 1) {
		int i;

		for (i = 0; i < ATABSIZE; i++)
			for (ap = atab[i]; ap; ap = ap->next) {
				if (*ap->name != '\0')
				    out1fmt("alias %s=%s\n", ap->name, ap->val);
			}
		return (0);
	}
D 7
	while (n = *++argv) {
E 7
I 7
	while ((n = *++argv) != NULL) {
E 7
		if ((v = strchr(n+1, '=')) == NULL) /* n+1: funny ksh stuff */
			if ((ap = lookupalias(n, 0)) == NULL) {
				outfmt(out2, "alias: %s not found\n", n);
				ret = 1;
			} else
				out1fmt("alias %s=%s\n", n, ap->val);
		else {
			*v++ = '\0';
			setalias(n, v);
		}
	}

	return (ret);
}

I 7
int
E 7
unaliascmd(argc, argv)
I 7
	int argc;
E 7
	char **argv;
D 7
	{
E 7
I 7
{
E 7
	int i;
	
	while ((i = nextopt("a")) != '\0') {
		if (i == 'a') {
			rmaliases();
			return (0);
		}
	}
	for (i = 0; *argptr; argptr++)
		i = unalias(*argptr);

	return (i);
}

D 2
/*
 * XXX -- for playing with the builtin command routines -- REMOVE
 */
foocmd(argc, argv)  
	char **argv; 
	{
	char **ap;

	out1fmt("argc: %d argv: %x argptr: %x\n", argc, argv, argptr);
	out1fmt("ARGV:\n");
	ap = argv;
	while (*ap)
		out1fmt("%s\n", *ap++);
	out1fmt("ARGPTR:\n");
	ap = argptr;
	while (*ap)
		out1fmt("%s\n", *ap++);
}

E 2
STATIC struct alias **
hashalias(p)
	register char *p;
	{
	unsigned int hashval;

	hashval = *p << 4;
	while (*p)
		hashval+= *p++;
	return &atab[hashval % ATABSIZE];
}
E 1
