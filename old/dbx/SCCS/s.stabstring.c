h15596
s 00001/00001/01222
d D 5.6 91/03/05 08:17:52 bostic 8 7
c ANSI, rename inline
e
s 00001/00011/01222
d D 5.5 90/06/01 16:06:30 bostic 7 6
c new copyright notice
e
s 00015/00006/01218
d D 5.4 89/05/23 10:21:51 bostic 6 5
c add Berkeley specific copyright notice
e
s 00009/00007/01215
d D 5.3 88/05/11 02:06:22 donn 5 4
c Print the register version of register parameters, not the useless stack
c copy.
e
s 00127/00018/01095
d D 5.2 88/01/12 01:22:26 donn 4 3
c merge in latest Linton version plus mediocre support for AT&T's C++ 1.2.1
c compiler plus fix to make visible static block variables which have the same
c names as external variables.
e
s 00007/00003/01106
d D 5.1 85/05/31 10:17:33 dist 3 2
c Add copyright
e
s 00222/00048/00887
d D 1.2 85/03/01 20:31:35 linton 2 1
c update to version 3.0
e
s 00935/00000/00000
d D 1.1 84/06/23 10:59:16 sam 1 0
c date and time created 84/06/23 10:59:16 by sam
e
u
U
t
T
I 2
D 3
/* Copyright (c) 1982 Regents of the University of California */
E 3
I 3
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 */
E 3

E 2
I 1
#ifndef lint
D 3
static	char sccsid[] = "%W% (Berkeley) %G%"; /* from 1.4 84/03/27 10:24:04 linton Exp */
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 3

I 2
D 4
static char rcsid[] = "$Header: stabstring.c,v 1.6 84/12/26 10:42:17 linton Exp $";
E 4
I 4
D 5
static char rcsid[] = "$Header: stabstring.c,v 1.4 87/12/01 01:41:33 donn Exp $";
E 5
I 5
static char rcsid[] = "$Header: stabstring.c,v 1.5 88/04/01 18:13:58 donn Exp $";
E 6
I 6
#endif /* not lint */
E 6
E 5
E 4

E 2
/*
 * String information interpretation
 *
 * The string part of a stab entry is broken up into name and type information.
 */

#include "defs.h"
#include "stabstring.h"
#include "object.h"
#include "main.h"
#include "symbols.h"
#include "names.h"
#include "languages.h"
I 2
#include "tree.h"
E 2
#include <a.out.h>
#include <ctype.h>

#ifndef public
#endif

/*
 * Special characters in symbol table information.
 */

I 2
#define CONSTNAME 'c'
E 2
#define TYPENAME 't'
#define TAGNAME 'T'
#define MODULEBEGIN 'm'
#define EXTPROCEDURE 'P'
#define PRIVPROCEDURE 'Q'
#define INTPROCEDURE 'I'
#define EXTFUNCTION 'F'
#define PRIVFUNCTION 'f'
#define INTFUNCTION 'J'
#define EXTVAR 'G'
#define MODULEVAR 'S'
#define OWNVAR 'V'
#define REGVAR 'r'
#define VALUEPARAM 'p'
#define VARIABLEPARAM 'v'
#define LOCALVAR /* default */

/*
 * Type information special characters.
 */

#define T_SUBRANGE 'r'
#define T_ARRAY 'a'
D 2
#define T_OPENARRAY 'A'
E 2
I 2
#define T_OLDOPENARRAY 'A'
#define T_OPENARRAY 'O'
#define T_DYNARRAY 'D'
#define T_SUBARRAY 'E'
E 2
#define T_RECORD 's'
#define T_UNION 'u'
#define T_ENUM 'e'
#define T_PTR '*'
#define T_FUNCVAR 'f'
#define T_PROCVAR 'p'
#define T_IMPORTED 'i'
#define T_SET 'S'
#define T_OPAQUE 'o'
I 2
#define T_FILE 'd'
E 2

/*
 * Table of types indexed by per-file unique identification number.
 */

#define NTYPES 1000

private Symbol typetable[NTYPES];

public initTypeTable ()
{
    bzero(typetable, sizeof(typetable));
    (*language_op(curlang, L_MODINIT))(typetable);
}

/*
 * Put an nlist entry into the symbol table.
 * If it's already there just add the associated information.
 *
 * Type information is encoded in the name following a ":".
 */

private Symbol constype();
private Char *curchar;

#define skipchar(ptr, ch) \
{ \
    if (*ptr != ch) { \
	panic("expected char '%c', found '%s'", ch, ptr); \
    } \
    ++ptr; \
}

#define optchar(ptr, ch) \
{ \
    if (*ptr == ch) { \
	++ptr; \
    } \
}

D 4
#define chkcont(ptr) \
E 4
I 4
#ifdef sun
#    define chkcont(ptr) \
E 4
{ \
I 4
    if (*ptr == '\\' or *ptr == '?') { \
	ptr = getcont(); \
    } \
}
#else if notsun
#    define chkcont(ptr) \
{ \
E 4
    if (*ptr == '?') { \
	ptr = getcont(); \
    } \
}
I 4
#endif
E 4

#define newSym(s, n) \
{ \
    s = insert(n); \
    s->level = curblock->level + 1; \
    s->language = curlang; \
    s->block = curblock; \
}

#define makeVariable(s, n, off) \
{ \
    newSym(s, n); \
    s->class = VAR; \
    s->symvalue.offset = off; \
    getType(s); \
}

#define makeParameter(s, n, cl, off) \
{ \
D 5
    newSym(s, n); \
I 4
    s->storage = STK; \
E 4
    s->class = cl; \
    s->symvalue.offset = off; \
E 5
I 5
    if ((s = lookup(n)) == nil or s->block != curblock) { \
	newSym(s, n); \
	s->storage = STK; \
	s->class = cl; \
	s->symvalue.offset = off; \
	getType(s); \
    } \
E 5
    curparam->chain = s; \
    curparam = s; \
D 5
    getType(s); \
E 5
}

public entersym (name, np)
String name;
struct nlist *np;
{
D 2
    Symbol s;
E 2
I 2
D 4
    Symbol s, t;
E 2
    char *p;
E 4
I 4
    Symbol s;
    register char *p, *q, *r;
E 4
    register Name n;
    char c;

    p = index(name, ':');
    *p = '\0';
    c = *(p+1);
I 4
    if (autostrip and streq(language_name(curlang), "c++")) {
	/*
	 * Strip off redundant prefixes from C++ names.
	 * Static variables are prefixed with _static_.
	 * Formal arguments of functions are prefixed with _au0_.
	 * Automatic variables are prefixed with _au[1-9][0-9]*_.
	 * Class members are prefixed with _T_, where T is a class tag.
	 */
	if (strncmp("_static_", name, 8) == 0 and name[8] != '\0') {
	    name += 8;
	}
	q = name;
	if (*q++ == '_' and *q++ == 'a' and *q++ == 'u' and isdigit(*q++)) {
	    while (isdigit(*q))
		++q;
	    if (*q++ == '_' and *q != '\0')
		name = q;
	}
	q = name;
	if (*q++ == '_' and c == EXTFUNCTION) {
	    /*
	     * Punt on static class members, for speed.
	     */
	    for (r = q; (r = index(r, '_')) != nil; ++r) {
		if (r == q) {
		    continue;
		}
		*r = '\0';
		s = lookup(identname(q, true));
		if (s != nil and s->class == TYPE) {
		    char *newname = r + 1;
		    if (*newname != '\0') {
			name = newname;
			break;
		    }
		}
		*r = '_';
	    }
	}
    }
E 4
    n = identname(name, true);
    chkUnnamedBlock();
    curchar = p + 2;
    switch (c) {
I 2
	case CONSTNAME:
	    newSym(s, n);
	    constName(s);
	    break;

E 2
	case TYPENAME:
	    newSym(s, n);
	    typeName(s);
	    break;

	case TAGNAME:
D 2
	    newSym(s, n);
E 2
I 2
	    s = symbol_alloc();
	    s->name = n;
	    s->level = curblock->level + 1;
	    s->language = curlang;
	    s->block = curblock;
E 2
	    tagName(s);
	    break;

	case MODULEBEGIN:
D 2
	    newSym(s, n);
	    publicRoutine(s, MODULE, np->n_value);
E 2
I 2
	    publicRoutine(&s, n, MODULE, np->n_value, false);
E 2
	    curmodule = s;
	    break;

	case EXTPROCEDURE:
D 2
	    newSym(s, n);
	    publicRoutine(s, PROC, np->n_value);
E 2
I 2
	    publicRoutine(&s, n, PROC, np->n_value, false);
E 2
	    break;

	case PRIVPROCEDURE:
	    privateRoutine(&s, n, PROC, np->n_value);
	    break;

	case INTPROCEDURE:
D 2
	    newSym(s, n);
	    markInternal(s);
	    publicRoutine(s, PROC, np->n_value);
E 2
I 2
	    publicRoutine(&s, n, PROC, np->n_value, true);
E 2
	    break;

	case EXTFUNCTION:
D 2
	    newSym(s, n);
	    publicRoutine(s, FUNC, np->n_value);
E 2
I 2
	    publicRoutine(&s, n, FUNC, np->n_value, false);
E 2
	    break;

	case PRIVFUNCTION:
	    privateRoutine(&s, n, FUNC, np->n_value);
	    break;

	case INTFUNCTION:
D 2
	    newSym(s, n);
	    markInternal(s);
	    publicRoutine(s, FUNC, np->n_value);
E 2
I 2
	    publicRoutine(&s, n, FUNC, np->n_value, true);
E 2
	    break;

	case EXTVAR:
D 2
	    find(s, n) where
		s->level == program->level and s->class == VAR
	    endfind(s);
	    if (s == nil) {
		makeVariable(s, n, np->n_value);
		s->level = program->level;
		s->block = program;
		getExtRef(s);
	    }
E 2
I 2
	    extVar(&s, n, np->n_value);
E 2
	    break;

	case MODULEVAR:
	    if (curblock->class != MODULE) {
		exitblock();
	    }
	    makeVariable(s, n, np->n_value);
I 4
	    s->storage = EXT;
E 4
	    s->level = program->level;
	    s->block = curmodule;
	    getExtRef(s);
	    break;

	case OWNVAR:
	    makeVariable(s, n, np->n_value);
	    ownVariable(s, np->n_value);
	    getExtRef(s);
	    break;

	case REGVAR:
	    makeVariable(s, n, np->n_value);
D 4
	    s->level = -(s->level);
E 4
I 4
	    s->storage = INREG;
E 4
	    break;

	case VALUEPARAM:
	    makeParameter(s, n, VAR, np->n_value);
I 4
#	    ifdef IRIS
		/*
		 * Bug in SGI C compiler -- generates stab offset
		 * for parameters with size added in.
		 */
D 5
		if (curlang == findlanguage(".c")) {
E 5
I 5
		if (s->storage == STK and curlang == findlanguage(".c")) {
E 5
		    s->symvalue.offset -= size(s);
		}
#	    endif
E 4
	    break;

	case VARIABLEPARAM:
	    makeParameter(s, n, REF, np->n_value);
	    break;

	default:	/* local variable */
	    --curchar;
	    makeVariable(s, n, np->n_value);
I 4
	    s->storage = STK;
E 4
	    break;
    }
    if (tracesyms) {
	printdecl(s);
	fflush(stdout);
    }
}

/*
I 2
 * Enter a named constant.
 */

private constName (s)
Symbol s;
{
    integer i;
    double d;
    char *p, buf[1000];

    s->class = CONST;
    skipchar(curchar, '=');
    p = curchar;
    ++curchar;
    switch (*p) {
	case 'b':
	    s->type = t_boolean;
	    s->symvalue.constval = build(O_LCON, getint());
	    break;

	case 'c':
	    s->type = t_char;
	    s->symvalue.constval = build(O_LCON, getint());
	    break;

	case 'i':
	    s->type = t_int;
	    s->symvalue.constval = build(O_LCON, getint());
	    break;

	case 'r':
	    sscanf(curchar, "%lf", &d);
	    while (*curchar != '\0' and *curchar != ';') {
		++curchar;
	    }
	    --curchar;
	    s->type = t_real;
	    s->symvalue.constval = build(O_FCON, d);
	    break;

	case 's':
	    p = &buf[0];
	    skipchar(curchar, '\'');
	    while (*curchar != '\'') {
		*p = *curchar;
		++p;
		++curchar;
	    }
	    *p = '\0';
	    s->symvalue.constval = build(O_SCON, strdup(buf));
	    s->type = s->symvalue.constval->nodetype;
	    break;

	case 'e':
	    getType(s);
	    skipchar(curchar, ',');
	    s->symvalue.constval = build(O_LCON, getint());
	    break;

	case 'S':
	    getType(s);
	    skipchar(curchar, ',');
	    i = getint(); /* set size */
	    skipchar(curchar, ',');
	    i = getint(); /* number of bits in constant */
	    s->symvalue.constval = build(O_LCON, 0);
	    break;

	default:
	    s->type = t_int;
	    s->symvalue.constval = build(O_LCON, 0);
	    printf("[internal error: unknown constant type '%c']", *p);
	    break;
    }
    s->symvalue.constval->nodetype = s->type;
}

/*
E 2
 * Enter a type name.
 */

private typeName (s)
Symbol s;
{
    register integer i;

    s->class = TYPE;
    s->language = curlang;
    s->block = curblock;
    s->level = curblock->level + 1;
    i = getint();
    if (i == 0) {
	panic("bad input on type \"%s\" at \"%s\"", symname(s), curchar);
    } else if (i >= NTYPES) {
	panic("too many types in file \"%s\"", curfilename());
    }
    /*
     * A hack for C typedefs that don't create new types,
     * e.g. typedef unsigned int Hashvalue;
     *  or  typedef struct blah BLAH;
     */
    if (*curchar != '=') {
	s->type = typetable[i];
	if (s->type == nil) {
	    s->type = symbol_alloc();
	    typetable[i] = s->type;
	}
    } else {
	if (typetable[i] != nil) {
	    typetable[i]->language = curlang;
	    typetable[i]->class = TYPE;
	    typetable[i]->type = s;
	} else {
	    typetable[i] = s;
	}
	skipchar(curchar, '=');
	getType(s);
    }
}

/*
 * Enter a tag name.
 */

private tagName (s)
Symbol s;
{
    register integer i;

    s->class = TAG;
    i = getint();
    if (i == 0) {
	panic("bad input on tag \"%s\" at \"%s\"", symname(s), curchar);
    } else if (i >= NTYPES) {
	panic("too many types in file \"%s\"", curfilename());
    }
    if (typetable[i] != nil) {
	typetable[i]->language = curlang;
	typetable[i]->class = TYPE;
	typetable[i]->type = s;
    } else {
	typetable[i] = s;
    }
    skipchar(curchar, '=');
    getType(s);
}

/*
 * Setup a symbol entry for a public procedure or function.
I 2
 *
 * If it contains nested procedures, then it may already be defined
 * in the current block as a MODULE.
E 2
 */

D 2
private publicRoutine (s, class, addr)
Symbol s;
E 2
I 2
private publicRoutine (s, n, class, addr, isinternal)
Symbol *s;
Name n;
E 2
Symclass class;
Address addr;
I 2
boolean isinternal;
E 2
{
D 2
    enterRoutine(s, class);
    s->level = program->level;
E 2
I 2
    Symbol nt, t;

    newSym(nt, n);
    if (isinternal) {
	markInternal(nt);
    }
    enterRoutine(nt, class);
    find(t, n) where
	t != nt and t->class == MODULE and t->block == nt->block
    endfind(t);
    if (t == nil) {
	t = nt;
    } else {
	t->language = nt->language;
	t->class = nt->class;
	t->type = nt->type;
	t->chain = nt->chain;
	t->symvalue = nt->symvalue;
	nt->class = EXTREF;
	nt->symvalue.extref = t;
	delete(nt);
	curparam = t;
	changeBlock(t);
    }
    if (t->block == program) {
	t->level = program->level;
    } else if (t->class == MODULE) {
	t->level = t->block->level;
    } else if (t->block->class == MODULE) {
	t->level = t->block->block->level;
    } else {
	t->level = t->block->level + 1;
    }
    *s = t;
E 2
}

/*
 * Setup a symbol entry for a private procedure or function.
 */

private privateRoutine (s, n, class, addr)
Symbol *s;
Name n;
Symclass class;
Address addr;
{
    Symbol t;
    boolean isnew;

    find(t, n) where
	t->level == curmodule->level and t->class == class
    endfind(t);
    if (t == nil) {
	isnew = true;
	t = insert(n);
    } else {
	isnew = false;
    }
    t->language = curlang;
    enterRoutine(t, class);
    if (isnew) {
	t->symvalue.funcv.src = false;
D 8
	t->symvalue.funcv.inline = false;
E 8
I 8
	t->symvalue.funcv.inlne = false;
E 8
	t->symvalue.funcv.beginaddr = addr;
	newfunc(t, codeloc(t));
	findbeginning(t);
    }
    *s = t;
}

/*
 * Set up for beginning a new procedure, function, or module.
 * If it's a function, then read the type.
 *
 * If the next character is a ",", then read the name of the enclosing block.
 * Otherwise assume the previous function, if any, is over, and the current
 * routine is at the same level.
 */

private enterRoutine (s, class)
Symbol s;
Symclass class;
{
    s->class = class;
    if (class == FUNC) {
	getType(s);
    }
    if (s->class != MODULE) {
	getExtRef(s);
    } else if (*curchar == ',') {
	++curchar;
    }
    if (*curchar != '\0') {
	exitblock();
	enterNestedBlock(s);
    } else {
	if (curblock->class == FUNC or curblock->class == PROC) {
	    exitblock();
	}
	if (class == MODULE) {
	    exitblock();
	}
	enterblock(s);
    }
    curparam = s;
}

/*
I 2
 * Handling an external variable is tricky, since we might already
 * know it but need to define it's type for other type information
 * in the file.  So just in case we read the type information anyway.
 */

private extVar (symp, n, off)
Symbol *symp;
Name n;
integer off;
{
    Symbol s, t;

    find(s, n) where
	s->level == program->level and s->class == VAR
    endfind(s);
    if (s == nil) {
	makeVariable(s, n, off);
I 4
	s->storage = EXT;
E 4
	s->level = program->level;
	s->block = curmodule;
	getExtRef(s);
    } else {
	t = constype(nil);
    }
    *symp = s;
}

/*
E 2
 * Check to see if the stab string contains the name of the external
 * reference.  If so, we create a symbol with that name and class EXTREF, and
 * connect it to the given symbol.  This link is created so that when
 * we see the linker symbol we can resolve it to the given symbol.
 */

private getExtRef (s)
Symbol s;
{
    char *p;
    Name n;
    Symbol t;

    if (*curchar == ',' and *(curchar + 1) != '\0') {
	p = index(curchar + 1, ',');
	*curchar = '\0';
	if (p != nil) {
	    *p = '\0';
	    n = identname(curchar + 1, false);
	    curchar = p + 1;
	} else {
	    n = identname(curchar + 1, true);
	}
	t = insert(n);
	t->language = s->language;
	t->class = EXTREF;
	t->block = program;
	t->level = program->level;
	t->symvalue.extref = s;
    }
}

/*
 * Find a block with the given identifier in the given outer block.
 * If not there, then create it.
 */

private Symbol findBlock (id, m)
String id;
Symbol m;
{
    Name n;
    Symbol s;

    n = identname(id, true);
    find(s, n) where s->block == m and isblock(s) endfind(s);
    if (s == nil) {
	s = insert(n);
	s->block = m;
	s->language = curlang;
	s->class = MODULE;
	s->level = m->level + 1;
    }
    return s;
}

/*
 * Enter a nested block.
 * The block within which it is nested is described
 * by "module{:module}[:proc]".
 */

private enterNestedBlock (b)
Symbol b;
{
    register char *p, *q;
    Symbol m, s;
    Name n;

    q = curchar;
    p = index(q, ':');
    m = program;
    while (p != nil) {
	*p = '\0';
	m = findBlock(q, m);
	q = p + 1;
	p = index(q, ':');
    }
    if (*q != '\0') {
	m = findBlock(q, m);
    }
    b->level = m->level + 1;
    b->block = m;
    pushBlock(b);
}

/*
 * Enter a statically-allocated variable defined within a routine.
 *
 * Global BSS variables are chained together so we can resolve them
 * when the start of common is determined.  The list is kept in order
 * so that f77 can display all vars in a COMMON.
 */

private ownVariable (s, addr)
Symbol s;
Address addr;
{
D 4
    s->level = 1;
E 4
I 4
    s->storage = EXT;
    /* s->level = 1; */
E 4
    if (curcomm) {
	if (commchain != nil) {
	    commchain->symvalue.common.chain = s;
	} else {
	    curcomm->symvalue.common.offset = (integer) s;
	}			  
	commchain = s;
	s->symvalue.common.offset = addr;
	s->symvalue.common.chain = nil;
    }
}

/*
 * Get a type from the current stab string for the given symbol.
 */

private getType (s)
Symbol s;
{
D 4
    s->type = constype(nil);
E 4
I 4
    Symbol t, addtag();

E 4
    if (s->class == TAG) {
D 4
	addtag(s);
E 4
I 4
	t = addtag(s);
	t->type = constype(nil);
	s->type = t->type;
    } else {
	s->type = constype(nil);
E 4
    }
}

/*
 * Construct a type out of a string encoding.
D 2
 *
 * The forms of the string are
 *
 *	<number>
 *	<number>=<type>
 *	r<type>;<number>;<number>		-- subrange
 *	a<type>;<type>				-- array[index] of element
 *      A<type>					-- open array
 *	s<size>{<name>:<type>;<number>;<number>}-- record
 *	u<size>{<name>:<type>;<number>;<number>}-- union
 *	*<type>					-- pointer
 *	f<type>,<integer>;<paramlist>		-- function variable
 *	p<integer>;<paramlist>			-- procedure variable
 *	S<type>					-- set of type
 *	o<name>[,<type>]			-- opaque type
 *	i<name>,<type>				-- imported type
E 2
 */

private Rangetype getRangeBoundType();

private Symbol constype (type)
Symbol type;
{
    register Symbol t;
    register integer n;
    char class;
I 2
    char *p;
E 2

I 2
    while (*curchar == '@') {
	p = index(curchar, ';');
	if (p == nil) {
	    fflush(stdout);
	    fprintf(stderr, "missing ';' after type attributes");
	} else {
	    curchar = p + 1;
	}
    }
E 2
    if (isdigit(*curchar)) {
	n = getint();
	if (n >= NTYPES) {
	    panic("too many types in file \"%s\"", curfilename());
	}
	if (*curchar == '=') {
	    if (typetable[n] != nil) {
		t = typetable[n];
	    } else {
		t = symbol_alloc();
		typetable[n] = t;
	    }
	    ++curchar;
	    constype(t);
	} else {
	    t = typetable[n];
	    if (t == nil) {
		t = symbol_alloc();
		typetable[n] = t;
	    }
	}
    } else {
	if (type == nil) {
	    t = symbol_alloc();
	} else {
	    t = type;
	}
	t->language = curlang;
	t->level = curblock->level + 1;
	t->block = curblock;
	class = *curchar++;
	switch (class) {
	    case T_SUBRANGE:
		consSubrange(t);
		break;

	    case T_ARRAY:
		t->class = ARRAY;
		t->chain = constype(nil);
		skipchar(curchar, ';');
		chkcont(curchar);
		t->type = constype(nil);
		break;

I 2
	    case T_OLDOPENARRAY:
		t->class = DYNARRAY;
		t->symvalue.ndims = 1;
		t->type = constype(nil);
		t->chain = t_int;
		break;

E 2
	    case T_OPENARRAY:
I 4
		consDynarray(t, OPENARRAY);
		break;

E 4
D 2
		t->class = ARRAY;
		t->chain = t_open;
E 2
I 2
	    case T_DYNARRAY:
D 4
		consDynarray(t);
E 4
I 4
		consDynarray(t, DYNARRAY);
E 4
		break;

	    case T_SUBARRAY:
		t->class = SUBARRAY;
		t->symvalue.ndims = getint();
		skipchar(curchar, ',');
E 2
		t->type = constype(nil);
I 2
		t->chain = t_int;
E 2
		break;

	    case T_RECORD:
		consRecord(t, RECORD);
		break;

	    case T_UNION:
		consRecord(t, VARNT);
		break;

	    case T_ENUM:
		consEnum(t);
		break;

	    case T_PTR:
		t->class = PTR;
		t->type = constype(nil);
		break;

	    /*
	     * C function variables are different from Modula-2's.
	     */
	    case T_FUNCVAR:
		t->class = FFUNC;
		t->type = constype(nil);
D 4
		if (not streq(language_name(curlang), "c")) {
E 4
I 4
		if (streq(language_name(curlang), "modula-2")) {
E 4
		    skipchar(curchar, ',');
		    consParamlist(t);
		}
		break;

	    case T_PROCVAR:
		t->class = FPROC;
		consParamlist(t);
		break;

	    case T_IMPORTED:
		consImpType(t);
		break;

	    case T_SET:
		t->class = SET;
		t->type = constype(nil);
		break;

	    case T_OPAQUE:
		consOpaqType(t);
		break;

I 2
	    case T_FILE:
		t->class = FILET;
		t->type = constype(nil);
		break;

E 2
	    default:
		badcaseval(class);
	}
    }
    return t;
}

/*
 * Construct a subrange type.
 */

private consSubrange (t)
Symbol t;
{
    t->class = RANGE;
    t->type = constype(nil);
    skipchar(curchar, ';');
    chkcont(curchar);
    t->symvalue.rangev.lowertype = getRangeBoundType();
    t->symvalue.rangev.lower = getint();
    skipchar(curchar, ';');
    chkcont(curchar);
    t->symvalue.rangev.uppertype = getRangeBoundType();
    t->symvalue.rangev.upper = getint();
}

/*
 * Figure out the bound type of a range.
 *
 * Some letters indicate a dynamic bound, ie what follows
 * is the offset from the fp which contains the bound; this will
 * need a different encoding when pc a['A'..'Z'] is
 * added; J is a special flag to handle fortran a(*) bounds
 */

private Rangetype getRangeBoundType ()
{
    Rangetype r;

    switch (*curchar) {
	case 'A':
	    r = R_ARG;
	    curchar++;
	    break;

	case 'T':
	    r = R_TEMP;
	    curchar++;
	    break;

	case 'J': 
	    r = R_ADJUST;
	    curchar++;
	    break;

	default:
	    r = R_CONST;
	    break;
    }
    return r;
}

/*
I 2
 * Construct a dynamic array descriptor.
 */

D 4
private consDynarray (t)
E 4
I 4
private consDynarray (t, c)
E 4
register Symbol t;
I 4
Symclass c;
E 4
{
D 4
    t->class = DYNARRAY;
E 4
I 4
    t->class = c;
E 4
    t->symvalue.ndims = getint();
    skipchar(curchar, ',');
    t->type = constype(nil);
    t->chain = t_int;
}

/*
E 2
 * Construct a record or union type.
 */

private consRecord (t, class)
Symbol t;
Symclass class;
{
    register Symbol u;
    register char *cur, *p;
    Name name;
    integer d;

    t->class = class;
    t->symvalue.offset = getint();
    d = curblock->level + 1;
    u = t;
I 4
    chkcont(curchar);
E 4
    cur = curchar;
    while (*cur != ';' and *cur != '\0') {
	p = index(cur, ':');
	if (p == nil) {
	    panic("index(\"%s\", ':') failed", curchar);
	}
	*p = '\0';
I 4
	if (
	    autostrip and
	    *cur == '_' and
	    streq(language_name(curlang), "c++")
	) {
	    /*
	     * Strip off redundant prefixes from C++ names.
	     * Class members are prefixed with _T_, where T is a class tag.
	     */
	    register char *q, *r;
	    Symbol s;

	    /*
	     * The slow way...  Check for members defined in the base class.
	     */
	    for (q = cur + 1, r = q; (r = index(r, '_')) != nil; ++r) {
		if (r == q) {
		    continue;
		}
		*r = '\0';
		s = lookup(identname(q, true));
		if (s != nil and s->class == TYPE) {
		    char *newcur = r + 1;
		    if (*newcur != '\0') {
			cur = newcur;
			break;
		    }
		}
		*r = '_';
	    }
	}
E 4
	name = identname(cur, true);
	u->chain = newSymbol(name, d, FIELD, nil, nil);
	cur = p + 1;
	u = u->chain;
	u->language = curlang;
	curchar = cur;
	u->type = constype(nil);
	skipchar(curchar, ',');
	u->symvalue.field.offset = getint();
	skipchar(curchar, ',');
	u->symvalue.field.length = getint();
	skipchar(curchar, ';');
	chkcont(curchar);
	cur = curchar;
    }
    if (*cur == ';') {
	++cur;
    }
    curchar = cur;
}

/*
 * Construct an enumeration type.
 */

private consEnum (t)
Symbol t;
{
    register Symbol u;
    register char *p;
    register integer count;

    t->class = SCAL;
    count = 0;
    u = t;
D 4
    while (*curchar != ';' and *curchar != '\0') {
E 4
I 4
    while (*curchar != ';' and *curchar != '\0' and *curchar != ',') {
E 4
	p = index(curchar, ':');
	assert(p != nil);
	*p = '\0';
	u->chain = insert(identname(curchar, true));
	curchar = p + 1;
	u = u->chain;
	u->language = curlang;
	u->class = CONST;
	u->level = curblock->level + 1;
	u->block = curblock;
	u->type = t;
D 2
	u->symvalue.iconval = getint();
E 2
I 2
	u->symvalue.constval = build(O_LCON, (long) getint());
E 2
	++count;
	skipchar(curchar, ',');
	chkcont(curchar);
    }
    if (*curchar == ';') {
	++curchar;
    }
    t->symvalue.iconval = count;
}

/*
 * Construct a parameter list for a function or procedure variable.
 */

private consParamlist (t)
Symbol t;
{
    Symbol p;
    integer i, d, n, paramclass;

    n = getint();
    skipchar(curchar, ';');
    p = t;
    d = curblock->level + 1;
    for (i = 0; i < n; i++) {
	p->chain = newSymbol(nil, d, VAR, nil, nil);
	p = p->chain;
	p->type = constype(nil);
	skipchar(curchar, ',');
	paramclass = getint();
	if (paramclass == 0) {
	    p->class = REF;
	}
	skipchar(curchar, ';');
	chkcont(curchar);
    }
}

/*
 * Construct an imported type.
 * Add it to a list of symbols to get fixed up.
 */

private consImpType (t)
Symbol t;
{
    register char *p;
    Symbol tmp;

    p = curchar;
    while (*p != ',' and *p != ';' and *p != '\0') {
	++p;
    }
    if (*p == '\0') {
	panic("bad import symbol entry '%s'", curchar);
    }
    t->class = TYPEREF;
    t->symvalue.typeref = curchar;
D 2
    curchar = p + 1;
E 2
    if (*p == ',') {
	curchar = p + 1;
	tmp = constype(nil);
I 2
    } else {
	curchar = p;
E 2
    }
    skipchar(curchar, ';');
    *p = '\0';
}

/*
 * Construct an opaque type entry.
 */

private consOpaqType (t)
Symbol t;
{
    register char *p;
    register Symbol s;
    register Name n;
    boolean def;

    p = curchar;
    while (*p != ';' and *p != ',') {
	if (*p == '\0') {
	    panic("bad opaque symbol entry '%s'", curchar);
	}
	++p;
    }
    def = (Boolean) (*p == ',');
    *p = '\0';
    n = identname(curchar, true);
    find(s, n) where s->class == TYPEREF endfind(s);
    if (s == nil) {
	s = insert(n);
	s->class = TYPEREF;
	s->type = nil;
    }
    curchar = p + 1;
    if (def) {
	s->type = constype(nil);
	skipchar(curchar, ';');
    }
    t->class = TYPE;
    t->type = s;
}

/*
 * Read an integer from the current position in the type string.
 */

private integer getint ()
{
    register integer n;
    register char *p;
    register Boolean isneg;

    n = 0;
    p = curchar;
    if (*p == '-') {
	isneg = true;
	++p;
    } else {
	isneg = false;
    }
    while (isdigit(*p)) {
	n = 10*n + (*p - '0');
	++p;
    }
    curchar = p;
    return isneg ? (-n) : n;
}

/*
 * Add a tag name.  This is a kludge to be able to refer
 * to tags that have the same name as some other symbol
 * in the same block.
 */

D 4
private addtag (s)
E 4
I 4
private Symbol addtag (s)
E 4
register Symbol s;
{
    register Symbol t;
    char buf[100];

D 4
    sprintf(buf, "$$%.90s", ident(s->name));
    t = insert(identname(buf, false));
E 4
I 4
    if (streq(language_name(curlang), "c++")) {
	t = insert(s->name);
	t->class = TYPE;
    } else {
	sprintf(buf, "$$%.90s", ident(s->name));
	t = insert(identname(buf, false));
	t->class = TAG;
    }
E 4
    t->language = s->language;
D 4
    t->class = TAG;
    t->type = s->type;
E 4
    t->block = s->block;
I 4
    return t;
E 4
}
E 1
