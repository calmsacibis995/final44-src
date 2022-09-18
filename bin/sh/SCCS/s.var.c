h07241
s 00046/00013/00631
d D 8.3 95/05/04 18:00:13 christos 10 9
c 
e
s 00002/00002/00642
d D 8.2 95/04/28 10:24:03 bostic 9 8
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00642
d D 8.1 93/05/31 15:20:52 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00637
d D 5.7 92/07/15 09:09:13 marc 7 6
c history and new option changes
e
s 00028/00011/00612
d D 5.6 92/06/23 18:08:28 marc 6 5
c unset -f
e
s 00001/00001/00622
d D 5.5 92/05/19 15:40:57 marc 5 4
c fix error message
e
s 00001/00001/00622
d D 5.4 92/04/16 14:34:29 marc 4 3
c check if effective userid is root
e
s 00016/00016/00607
d D 5.3 91/04/12 18:31:24 marc 3 2
c redo how PS1 is initialized
e
s 00004/00004/00619
d D 5.2 91/03/13 19:43:23 marc 2 1
c wrong source
e
s 00623/00000/00000
d D 5.1 91/03/07 20:28:03 bostic 1 0
c date and time created 91/03/07 20:28:03 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 10
#include <unistd.h>
#include <stdlib.h>

E 10
/*
 * Shell variables.
 */

D 2

E 2
#include "shell.h"
#include "output.h"
#include "expand.h"
#include "nodes.h"	/* for other headers */
#include "eval.h"	/* defines cmdenviron */
#include "exec.h"
#include "syntax.h"
#include "options.h"
#include "mail.h"
#include "var.h"
#include "memalloc.h"
#include "error.h"
#include "mystring.h"
I 10
#ifndef NO_HISTORY
#include "myhistedit.h"
#endif
E 10


#define VTABSIZE 39


struct varinit {
	struct var *var;
	int flags;
	char *text;
};


#if ATTY
struct var vatty;
#endif
I 10
#ifndef NO_HISTORY
E 10
I 7
struct var vhistsize;
I 10
#endif
E 10
E 7
struct var vifs;
struct var vmail;
struct var vmpath;
struct var vpath;
struct var vps1;
struct var vps2;
struct var vvers;
#if ATTY
struct var vterm;
#endif

const struct varinit varinit[] = {
#if ATTY
	{&vatty,	VSTRFIXED|VTEXTFIXED|VUNSET,	"ATTY="},
#endif
I 10
#ifndef NO_HISTORY
E 10
I 7
	{&vhistsize,	VSTRFIXED|VTEXTFIXED|VUNSET,	"HISTSIZE="},
I 10
#endif
E 10
E 7
	{&vifs,	VSTRFIXED|VTEXTFIXED,		"IFS= \t\n"},
	{&vmail,	VSTRFIXED|VTEXTFIXED|VUNSET,	"MAIL="},
	{&vmpath,	VSTRFIXED|VTEXTFIXED|VUNSET,	"MAILPATH="},
D 10
	{&vpath,	VSTRFIXED|VTEXTFIXED,		"PATH=:/bin:/usr/bin"},
E 10
I 10
	{&vpath,	VSTRFIXED|VTEXTFIXED,		"PATH=/bin:/usr/bin"},
E 10
D 3
	{&vps1,	VSTRFIXED|VTEXTFIXED,		"PS1=$ "},
E 3
I 3
	/* 
	 * vps1 depends on uid
	 */
E 3
	{&vps2,	VSTRFIXED|VTEXTFIXED,		"PS2=> "},
D 2
	{&vvers,	VSTRFIXED|VTEXTFIXED,		"SHELLVERS=ash 0.2"},
E 2
#if ATTY
	{&vterm,	VSTRFIXED|VTEXTFIXED|VUNSET,	"TERM="},
#endif
	{NULL,	0,				NULL}
};

struct var *vartab[VTABSIZE];

D 3
#ifdef __STDC__
STATIC void unsetvar(char *);
STATIC struct var **hashvar(char *);
STATIC int varequal(char *, char *);
#else
STATIC void unsetvar();
STATIC struct var **hashvar();
STATIC int varequal();
#endif
E 3
I 3
D 6
STATIC void unsetvar __P((char *));
E 6
I 6
STATIC int unsetvar __P((char *));
E 6
STATIC struct var **hashvar __P((char *));
STATIC int varequal __P((char *, char *));
E 3

D 3


E 3
/*
 * Initialize the varable symbol tables and import the environment
 */

#ifdef mkinit
INCLUDE "var.h"
INIT {
	char **envp;
	extern char **environ;

	initvar();
	for (envp = environ ; *envp ; envp++) {
		if (strchr(*envp, '=')) {
			setvareq(*envp, VEXPORT|VTEXTFIXED);
		}
	}
}
#endif


/*
 * This routine initializes the builtin variables.  It is called when the
 * shell is initialized and again when a shell procedure is spawned.
 */

void
initvar() {
	const struct varinit *ip;
	struct var *vp;
	struct var **vpp;

	for (ip = varinit ; (vp = ip->var) != NULL ; ip++) {
		if ((vp->flags & VEXPORT) == 0) {
I 2
D 3
			if ((strncmp(ip->text, "PS1=", 4) == 0) &&
			    getuid() == 0)
				ip->text = "PS1=# ";
E 3
E 2
			vpp = hashvar(ip->text);
			vp->next = *vpp;
			*vpp = vp;
			vp->text = ip->text;
			vp->flags = ip->flags;
		}
	}
D 2
}
E 2
D 3

E 3
I 3
	/*
	 * PS1 depends on uid
	 */
	if ((vps1.flags & VEXPORT) == 0) {
		vpp = hashvar("PS1=");
		vps1.next = *vpp;
		*vpp = &vps1;
D 4
		vps1.text = getuid() ? "PS1=$ " : "PS1=# ";
E 4
I 4
		vps1.text = geteuid() ? "PS1=$ " : "PS1=# ";
E 4
		vps1.flags = VSTRFIXED|VTEXTFIXED;
	}
E 3
D 2

E 2
I 2
}
E 2

/*
 * Set the value of a variable.  The flags argument is ored with the
 * flags of the variable.  If val is NULL, the variable is unset.
 */

void
setvar(name, val, flags)
	char *name, *val;
D 10
	{
E 10
I 10
	int flags;
{
E 10
	char *p, *q;
	int len;
	int namelen;
	char *nameeq;
	int isbad;

	isbad = 0;
	p = name;
	if (! is_name(*p++))
		isbad = 1;
	for (;;) {
		if (! is_in_name(*p)) {
			if (*p == '\0' || *p == '=')
				break;
			isbad = 1;
		}
		p++;
	}
	namelen = p - name;
	if (isbad)
D 5
		error("%.*s: is read only", namelen, name);
E 5
I 5
		error("%.*s: bad variable name", namelen, name);
E 5
	len = namelen + 2;		/* 2 is space for '=' and '\0' */
	if (val == NULL) {
		flags |= VUNSET;
	} else {
		len += strlen(val);
	}
	p = nameeq = ckmalloc(len);
	q = name;
	while (--namelen >= 0)
		*p++ = *q++;
	*p++ = '=';
	*p = '\0';
	if (val)
		scopy(val, p);
	setvareq(nameeq, flags);
}



/*
 * Same as setvar except that the variable and value are passed in
 * the first argument as name=value.  Since the first argument will
 * be actually stored in the table, it should not be a string that
 * will go away.
 */

void
setvareq(s, flags)
	char *s;
D 10
	{
E 10
I 10
	int flags;
{
E 10
	struct var *vp, **vpp;

	vpp = hashvar(s);
	for (vp = *vpp ; vp ; vp = vp->next) {
		if (varequal(s, vp->text)) {
			if (vp->flags & VREADONLY) {
				int len = strchr(s, '=') - s;
				error("%.*s: is read only", len, s);
			}
			INTOFF;
			if (vp == &vpath)
				changepath(s + 5);	/* 5 = strlen("PATH=") */
			if ((vp->flags & (VTEXTFIXED|VSTACK)) == 0)
				ckfree(vp->text);
			vp->flags &=~ (VTEXTFIXED|VSTACK|VUNSET);
			vp->flags |= flags;
			vp->text = s;
			if (vp == &vmpath || (vp == &vmail && ! mpathset()))
				chkmail(1);
I 10
#ifndef NO_HISTORY
E 10
I 7
			if (vp == &vhistsize)
				sethistsize();
I 10
#endif
E 10
E 7
			INTON;
			return;
		}
	}
	/* not found */
	vp = ckmalloc(sizeof (*vp));
	vp->flags = flags;
	vp->text = s;
	vp->next = *vpp;
	*vpp = vp;
}



/*
 * Process a linked list of variable assignments.
 */

void
listsetvar(list)
	struct strlist *list;
	{
	struct strlist *lp;

	INTOFF;
	for (lp = list ; lp ; lp = lp->next) {
		setvareq(savestr(lp->text), 0);
	}
	INTON;
}



/*
 * Find the value of a variable.  Returns NULL if not set.
 */

char *
lookupvar(name)
	char *name;
	{
	struct var *v;

	for (v = *hashvar(name) ; v ; v = v->next) {
		if (varequal(v->text, name)) {
			if (v->flags & VUNSET)
				return NULL;
			return strchr(v->text, '=') + 1;
		}
	}
	return NULL;
}



/*
 * Search the environment of a builtin command.  If the second argument
 * is nonzero, return the value of a variable even if it hasn't been
 * exported.
 */

char *
bltinlookup(name, doall)
	char *name;
D 10
	{
E 10
I 10
	int doall;
{
E 10
	struct strlist *sp;
	struct var *v;

	for (sp = cmdenviron ; sp ; sp = sp->next) {
		if (varequal(sp->text, name))
			return strchr(sp->text, '=') + 1;
	}
	for (v = *hashvar(name) ; v ; v = v->next) {
		if (varequal(v->text, name)) {
D 10
			if (v->flags & VUNSET
			 || ! doall && (v->flags & VEXPORT) == 0)
E 10
I 10
			if ((v->flags & VUNSET)
			 || (!doall && (v->flags & VEXPORT) == 0))
E 10
				return NULL;
			return strchr(v->text, '=') + 1;
		}
	}
	return NULL;
}



/*
 * Generate a list of exported variables.  This routine is used to construct
 * the third argument to execve when executing a program.
 */

char **
environment() {
	int nenv;
	struct var **vpp;
	struct var *vp;
	char **env, **ep;

	nenv = 0;
	for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
		for (vp = *vpp ; vp ; vp = vp->next)
			if (vp->flags & VEXPORT)
				nenv++;
	}
	ep = env = stalloc((nenv + 1) * sizeof *env);
	for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
		for (vp = *vpp ; vp ; vp = vp->next)
			if (vp->flags & VEXPORT)
				*ep++ = vp->text;
	}
	*ep = NULL;
	return env;
}


/*
 * Called when a shell procedure is invoked to clear out nonexported
 * variables.  It is also necessary to reallocate variables of with
 * VSTACK set since these are currently allocated on the stack.
 */

#ifdef mkinit
MKINIT void shprocvar();

SHELLPROC {
	shprocvar();
}
#endif

void
shprocvar() {
	struct var **vpp;
	struct var *vp, **prev;

	for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
		for (prev = vpp ; (vp = *prev) != NULL ; ) {
			if ((vp->flags & VEXPORT) == 0) {
				*prev = vp->next;
				if ((vp->flags & VTEXTFIXED) == 0)
					ckfree(vp->text);
				if ((vp->flags & VSTRFIXED) == 0)
					ckfree(vp);
			} else {
				if (vp->flags & VSTACK) {
					vp->text = savestr(vp->text);
					vp->flags &=~ VSTACK;
				}
				prev = &vp->next;
			}
		}
	}
	initvar();
}



/*
 * Command to list all variables which are set.  Currently this command
 * is invoked from the set command when the set command is called without
 * any variables.
 */

int
D 10
showvarscmd(argc, argv)  char **argv; {
E 10
I 10
showvarscmd(argc, argv)
	int argc;
	char **argv; 
{
E 10
	struct var **vpp;
	struct var *vp;

	for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
		for (vp = *vpp ; vp ; vp = vp->next) {
			if ((vp->flags & VUNSET) == 0)
				out1fmt("%s\n", vp->text);
		}
	}
	return 0;
}



/*
 * The export and readonly commands.
 */

int
D 10
exportcmd(argc, argv)  char **argv; {
E 10
I 10
exportcmd(argc, argv)
	int argc;
	char **argv; 
{
E 10
	struct var **vpp;
	struct var *vp;
	char *name;
	char *p;
	int flag = argv[0][0] == 'r'? VREADONLY : VEXPORT;

	listsetvar(cmdenviron);
	if (argc > 1) {
		while ((name = *argptr++) != NULL) {
			if ((p = strchr(name, '=')) != NULL) {
				p++;
			} else {
				vpp = hashvar(name);
				for (vp = *vpp ; vp ; vp = vp->next) {
					if (varequal(vp->text, name)) {
						vp->flags |= flag;
						goto found;
					}
				}
			}
			setvar(name, p, flag);
found:;
		}
	} else {
		for (vpp = vartab ; vpp < vartab + VTABSIZE ; vpp++) {
			for (vp = *vpp ; vp ; vp = vp->next) {
				if (vp->flags & flag) {
					for (p = vp->text ; *p != '=' ; p++)
						out1c(*p);
					out1c('\n');
				}
			}
		}
	}
	return 0;
}


/*
 * The "local" command.
 */

D 10
localcmd(argc, argv)  char **argv; {
E 10
I 10
int
localcmd(argc, argv)
	int argc;
	char **argv; 
{
E 10
	char *name;

	if (! in_function())
		error("Not in a function");
	while ((name = *argptr++) != NULL) {
		mklocal(name);
	}
	return 0;
}


/*
 * Make a variable a local variable.  When a variable is made local, it's
 * value and flags are saved in a localvar structure.  The saved values
 * will be restored when the shell function returns.  We handle the name
 * "-" as a special case.
 */

void
mklocal(name)
	char *name;
	{
	struct localvar *lvp;
	struct var **vpp;
	struct var *vp;

	INTOFF;
	lvp = ckmalloc(sizeof (struct localvar));
	if (name[0] == '-' && name[1] == '\0') {
D 7
		lvp->text = ckmalloc(sizeof optval);
		bcopy(optval, lvp->text, sizeof optval);
E 7
I 7
		lvp->text = ckmalloc(sizeof optlist);
D 9
		bcopy(optlist, lvp->text, sizeof optlist);
E 9
I 9
D 10
		memmove(lvp->text, optlist, sizeof optlist);
E 10
I 10
		memcpy(lvp->text, optlist, sizeof optlist);
E 10
E 9
E 7
		vp = NULL;
	} else {
		vpp = hashvar(name);
		for (vp = *vpp ; vp && ! varequal(vp->text, name) ; vp = vp->next);
		if (vp == NULL) {
			if (strchr(name, '='))
				setvareq(savestr(name), VSTRFIXED);
			else
				setvar(name, NULL, VSTRFIXED);
			vp = *vpp;	/* the new variable */
			lvp->text = NULL;
			lvp->flags = VUNSET;
		} else {
			lvp->text = vp->text;
			lvp->flags = vp->flags;
			vp->flags |= VSTRFIXED|VTEXTFIXED;
			if (strchr(name, '='))
				setvareq(savestr(name), 0);
		}
	}
	lvp->vp = vp;
	lvp->next = localvars;
	localvars = lvp;
	INTON;
}


/*
 * Called after a function returns.
 */

void
poplocalvars() {
	struct localvar *lvp;
	struct var *vp;

	while ((lvp = localvars) != NULL) {
		localvars = lvp->next;
		vp = lvp->vp;
		if (vp == NULL) {	/* $- saved */
D 7
			bcopy(lvp->text, optval, sizeof optval);
E 7
I 7
D 9
			bcopy(lvp->text, optlist, sizeof optlist);
E 9
I 9
D 10
			memmove(optlist, lvp->text, sizeof optlist);
E 10
I 10
			memcpy(optlist, lvp->text, sizeof optlist);
E 10
E 9
E 7
			ckfree(lvp->text);
		} else if ((lvp->flags & (VUNSET|VSTRFIXED)) == VUNSET) {
D 6
			unsetvar(vp->text);
E 6
I 6
			(void)unsetvar(vp->text);
E 6
		} else {
			if ((vp->flags & VTEXTFIXED) == 0)
				ckfree(vp->text);
			vp->flags = lvp->flags;
			vp->text = lvp->text;
		}
		ckfree(lvp);
	}
}


D 10
setvarcmd(argc, argv)  char **argv; {
E 10
I 10
int
setvarcmd(argc, argv)
	int argc;
	char **argv; 
{
E 10
	if (argc <= 2)
		return unsetcmd(argc, argv);
	else if (argc == 3)
		setvar(argv[1], argv[2], 0);
	else
		error("List assignment not implemented");
	return 0;
}


/*
 * The unset builtin command.  We unset the function before we unset the
 * variable to allow a function to be unset when there is a readonly variable
 * with the same name.
 */

D 10
unsetcmd(argc, argv)  char **argv; {
E 10
I 10
int
unsetcmd(argc, argv)
	int argc;
	char **argv; 
{
E 10
	char **ap;
I 6
	int i;
	int flg_func = 0;
	int flg_var = 0;
	int ret = 0;
E 6

D 6
	for (ap = argv + 1 ; *ap ; ap++) {
		unsetfunc(*ap);
		unsetvar(*ap);
E 6
I 6
	while ((i = nextopt("vf")) != '\0') {
		if (i == 'f')
			flg_func = 1;
		else
			flg_var = 1;
E 6
	}
D 6
	return 0;
E 6
I 6
	if (flg_func == 0 && flg_var == 0)
		flg_var = 1;
			
	for (ap = argptr; *ap ; ap++) {
		if (flg_func)
			ret |= unsetfunc(*ap);
		if (flg_var)
			ret |= unsetvar(*ap);
	}
	return ret;
E 6
}


/*
 * Unset the specified variable.
 */

D 6
STATIC void
E 6
I 6
STATIC int
E 6
unsetvar(s)
	char *s;
	{
	struct var **vpp;
	struct var *vp;

	vpp = hashvar(s);
	for (vp = *vpp ; vp ; vpp = &vp->next, vp = *vpp) {
		if (varequal(vp->text, s)) {
I 6
			if (vp->flags & VREADONLY)
				return (1);
E 6
			INTOFF;
D 6
			if (*(strchr(vp->text, '=') + 1) != '\0'
			 || vp->flags & VREADONLY) {
E 6
I 6
			if (*(strchr(vp->text, '=') + 1) != '\0')
E 6
				setvar(s, nullstr, 0);
D 6
			}
E 6
			vp->flags &=~ VEXPORT;
			vp->flags |= VUNSET;
			if ((vp->flags & VSTRFIXED) == 0) {
				if ((vp->flags & VTEXTFIXED) == 0)
					ckfree(vp->text);
				*vpp = vp->next;
				ckfree(vp);
			}
			INTON;
D 6
			return;
E 6
I 6
			return (0);
E 6
		}
	}
I 6

	return (1);
E 6
}



/*
 * Find the appropriate entry in the hash table from the name.
 */

STATIC struct var **
hashvar(p)
	register char *p;
	{
	unsigned int hashval;

	hashval = *p << 4;
	while (*p && *p != '=')
		hashval += *p++;
	return &vartab[hashval % VTABSIZE];
}



/*
 * Returns true if the two strings specify the same varable.  The first
 * variable name is terminated by '='; the second may be terminated by
 * either '=' or '\0'.
 */

STATIC int
varequal(p, q)
	register char *p, *q;
	{
	while (*p == *q++) {
		if (*p++ == '=')
			return 1;
	}
	if (*p == '=' && *(q - 1) == '\0')
		return 1;
	return 0;
}
E 1
