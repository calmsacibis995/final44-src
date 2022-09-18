h30542
s 00091/00047/00358
d D 8.2 95/05/04 17:59:58 christos 4 3
c 
e
s 00005/00005/00400
d D 8.1 93/05/31 15:19:53 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00404
d D 5.2 91/07/27 19:18:01 torek 2 1
c exit 0 on success
e
s 00404/00000/00000
d D 5.1 91/03/07 20:27:44 bostic 1 0
c date and time created 91/03/07 20:27:44 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 3
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * This program reads the nodetypes file and nodes.c.pat file.  It generates
 * the files nodes.h and nodes.c.
 */

#include <stdio.h>
I 4
#include <stdlib.h>
#include <string.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 4


#define MAXTYPES 50		/* max number of node types */
#define MAXFIELDS 20		/* max fields in a structure */
#define BUFLEN 100		/* size of character buffers */

/* field types */
#define T_NODE 1		/* union node *field */
#define T_NODELIST 2		/* struct nodelist *field */
#define T_STRING 3
#define T_INT 4			/* int field */
#define T_OTHER 5		/* other */
#define T_TEMP 6		/* don't copy this field */


struct field {			/* a structure field */
	char *name;		/* name of field */
	int type;			/* type of field */
	char *decl;		/* declaration of field */
};


struct str {			/* struct representing a node structure */
	char *tag;		/* structure tag */
	int nfields;		/* number of fields in the structure */
	struct field field[MAXFIELDS];	/* the fields of the structure */
	int done;			/* set if fully parsed */
};


D 4
int ntypes;			/* number of node types */
char *nodename[MAXTYPES];	/* names of the nodes */
struct str *nodestr[MAXTYPES];	/* type of structure used by the node */
int nstr;			/* number of structures */
struct str str[MAXTYPES];	/* the structures */
struct str *curstr;		/* current structure */
E 4
I 4
static int ntypes;			/* number of node types */
static char *nodename[MAXTYPES];	/* names of the nodes */
static struct str *nodestr[MAXTYPES];	/* type of structure used by the node */
static int nstr;			/* number of structures */
static struct str str[MAXTYPES];	/* the structures */
static struct str *curstr;		/* current structure */
static FILE *infp = stdin;
static char line[1024];
static int linno;
static char *linep;
E 4

I 4
static void parsenode __P((void));
static void parsefield __P((void));
static void output __P((char *));
static void outsizes __P((FILE *));
static void outfunc __P((FILE *, int));
static void indent __P((int, FILE *));
static int nextfield __P((char *));
static void skipbl __P((void));
static int readline __P((void));
static void error __P((const char *, ...));
static char *savestr __P((const char *));
E 4

D 4
FILE *infp = stdin;
char line[1024];
int linno;
char *linep;
E 4

D 4

char *savestr();
#define equal(s1, s2)	(strcmp(s1, s2) == 0)


E 4
I 4
int
E 4
main(argc, argv)
I 4
	int argc;
E 4
	char **argv;
D 4
	{
E 4
I 4
{
E 4
	if (argc != 3)
		error("usage: mknodes file\n");
	if ((infp = fopen(argv[1], "r")) == NULL)
		error("Can't open %s", argv[1]);
	while (readline()) {
		if (line[0] == ' ' || line[0] == '\t')
			parsefield();
		else if (line[0] != '\0')
			parsenode();
	}
	output(argv[2]);
I 2
	exit(0);
E 2
}



D 4
parsenode() {
E 4
I 4
static void
parsenode()
{
E 4
	char name[BUFLEN];
	char tag[BUFLEN];
	struct str *sp;

	if (curstr && curstr->nfields > 0)
		curstr->done = 1;
	nextfield(name);
	if (! nextfield(tag))
		error("Tag expected");
	if (*linep != '\0')
		error("Garbage at end of line");
	nodename[ntypes] = savestr(name);
	for (sp = str ; sp < str + nstr ; sp++) {
D 4
		if (equal(sp->tag, tag))
E 4
I 4
		if (strcmp(sp->tag, tag) == 0)
E 4
			break;
	}
	if (sp >= str + nstr) {
		sp->tag = savestr(tag);
		sp->nfields = 0;
		curstr = sp;
		nstr++;
	}
	nodestr[ntypes] = sp;
	ntypes++;
}


D 4
parsefield() {
E 4
I 4
static void
parsefield()
{
E 4
	char name[BUFLEN];
	char type[BUFLEN];
	char decl[2 * BUFLEN];
	struct field *fp;

	if (curstr == NULL || curstr->done)
		error("No current structure to add field to");
	if (! nextfield(name))
		error("No field name");
	if (! nextfield(type))
		error("No field type");
	fp = &curstr->field[curstr->nfields];
	fp->name = savestr(name);
D 4
	if (equal(type, "nodeptr")) {
E 4
I 4
	if (strcmp(type, "nodeptr") == 0) {
E 4
		fp->type = T_NODE;
		sprintf(decl, "union node *%s", name);
D 4
	} else if (equal(type, "nodelist")) {
E 4
I 4
	} else if (strcmp(type, "nodelist") == 0) {
E 4
		fp->type = T_NODELIST;
		sprintf(decl, "struct nodelist *%s", name);
D 4
	} else if (equal(type, "string")) {
E 4
I 4
	} else if (strcmp(type, "string") == 0) {
E 4
		fp->type = T_STRING;
		sprintf(decl, "char *%s", name);
D 4
	} else if (equal(type, "int")) {
E 4
I 4
	} else if (strcmp(type, "int") == 0) {
E 4
		fp->type = T_INT;
		sprintf(decl, "int %s", name);
D 4
	} else if (equal(type, "other")) {
E 4
I 4
	} else if (strcmp(type, "other") == 0) {
E 4
		fp->type = T_OTHER;
D 4
	} else if (equal(type, "temp")) {
E 4
I 4
	} else if (strcmp(type, "temp") == 0) {
E 4
		fp->type = T_TEMP;
	} else {
		error("Unknown type %s", type);
	}
	if (fp->type == T_OTHER || fp->type == T_TEMP) {
		skipbl();
		fp->decl = savestr(linep);
	} else {
		if (*linep)
			error("Garbage at end of line");
		fp->decl = savestr(decl);
	}
	curstr->nfields++;
}


char writer[] = "\
/*\n\
 * This file was generated by the mknodes program.\n\
 */\n\
\n";

I 4
static void
E 4
output(file)
	char *file;
D 4
	{
E 4
I 4
{
E 4
	FILE *hfile;
	FILE *cfile;
	FILE *patfile;
	int i;
	struct str *sp;
	struct field *fp;
	char *p;

	if ((patfile = fopen(file, "r")) == NULL)
		error("Can't open %s", file);
	if ((hfile = fopen("nodes.h", "w")) == NULL)
		error("Can't create nodes.h");
	if ((cfile = fopen("nodes.c", "w")) == NULL)
		error("Can't create nodes.c");
	fputs(writer, hfile);
	for (i = 0 ; i < ntypes ; i++)
		fprintf(hfile, "#define %s %d\n", nodename[i], i);
	fputs("\n\n\n", hfile);
	for (sp = str ; sp < &str[nstr] ; sp++) {
		fprintf(hfile, "struct %s {\n", sp->tag);
		for (i = sp->nfields, fp = sp->field ; --i >= 0 ; fp++) {
			fprintf(hfile, "      %s;\n", fp->decl);
		}
		fputs("};\n\n\n", hfile);
	}
	fputs("union node {\n", hfile);
	fprintf(hfile, "      int type;\n");
	for (sp = str ; sp < &str[nstr] ; sp++) {
		fprintf(hfile, "      struct %s %s;\n", sp->tag, sp->tag);
	}
	fputs("};\n\n\n", hfile);
	fputs("struct nodelist {\n", hfile);
	fputs("\tstruct nodelist *next;\n", hfile);
	fputs("\tunion node *n;\n", hfile);
	fputs("};\n\n\n", hfile);
	fputs("#ifdef __STDC__\n", hfile);
	fputs("union node *copyfunc(union node *);\n", hfile);
	fputs("void freefunc(union node *);\n", hfile);
	fputs("#else\n", hfile);
	fputs("union node *copyfunc();\n", hfile);
	fputs("void freefunc();\n", hfile);
	fputs("#endif\n", hfile);

	fputs(writer, cfile);
	while (fgets(line, sizeof line, patfile) != NULL) {
		for (p = line ; *p == ' ' || *p == '\t' ; p++);
D 4
		if (equal(p, "%SIZES\n"))
E 4
I 4
		if (strcmp(p, "%SIZES\n") == 0)
E 4
			outsizes(cfile);
D 4
		else if (equal(p, "%CALCSIZE\n"))
E 4
I 4
		else if (strcmp(p, "%CALCSIZE\n") == 0)
E 4
			outfunc(cfile, 1);
D 4
		else if (equal(p, "%COPY\n"))
E 4
I 4
		else if (strcmp(p, "%COPY\n") == 0)
E 4
			outfunc(cfile, 0);
		else
			fputs(line, cfile);
	}
}



I 4
static void
E 4
outsizes(cfile)
	FILE *cfile;
D 4
	{
E 4
I 4
{
E 4
	int i;

	fprintf(cfile, "static const short nodesize[%d] = {\n", ntypes);
	for (i = 0 ; i < ntypes ; i++) {
		fprintf(cfile, "      ALIGN(sizeof (struct %s)),\n", nodestr[i]->tag);
	}
	fprintf(cfile, "};\n");
}


I 4
static void
E 4
outfunc(cfile, calcsize)
	FILE *cfile;
D 4
	{
E 4
I 4
	int calcsize;
{
E 4
	struct str *sp;
	struct field *fp;
	int i;

	fputs("      if (n == NULL)\n", cfile);
	if (calcsize)
		fputs("	    return;\n", cfile);
	else
		fputs("	    return NULL;\n", cfile);
	if (calcsize)
		fputs("      funcblocksize += nodesize[n->type];\n", cfile);
	else {
		fputs("      new = funcblock;\n", cfile);
		fputs("      funcblock += nodesize[n->type];\n", cfile);
	}
	fputs("      switch (n->type) {\n", cfile);
	for (sp = str ; sp < &str[nstr] ; sp++) {
		for (i = 0 ; i < ntypes ; i++) {
			if (nodestr[i] == sp)
				fprintf(cfile, "      case %s:\n", nodename[i]);
		}
		for (i = sp->nfields ; --i >= 1 ; ) {
			fp = &sp->field[i];
			switch (fp->type) {
			case T_NODE:
				if (calcsize) {
					indent(12, cfile);
					fprintf(cfile, "calcsize(n->%s.%s);\n",
						sp->tag, fp->name);
				} else {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = copynode(n->%s.%s);\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			case T_NODELIST:
				if (calcsize) {
					indent(12, cfile);
					fprintf(cfile, "sizenodelist(n->%s.%s);\n",
						sp->tag, fp->name);
				} else {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = copynodelist(n->%s.%s);\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			case T_STRING:
				if (calcsize) {
					indent(12, cfile);
					fprintf(cfile, "funcstringsize += strlen(n->%s.%s) + 1;\n",
						sp->tag, fp->name);
				} else {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = nodesavestr(n->%s.%s);\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			case T_INT:
			case T_OTHER:
				if (! calcsize) {
					indent(12, cfile);
					fprintf(cfile, "new->%s.%s = n->%s.%s;\n",
						sp->tag, fp->name, sp->tag, fp->name);
				}
				break;
			}
		}
		indent(12, cfile);
		fputs("break;\n", cfile);
	}
	fputs("      };\n", cfile);
	if (! calcsize)
		fputs("      new->type = n->type;\n", cfile);
}


I 4
static void
E 4
indent(amount, fp)
I 4
	int amount;
E 4
	FILE *fp;
D 4
	{
E 4
I 4
{
E 4
	while (amount >= 8) {
		putc('\t', fp);
		amount -= 8;
	}
	while (--amount >= 0) {
		putc(' ', fp);
	}
}


D 4
int
E 4
I 4
static int
E 4
nextfield(buf)
	char *buf;
D 4
	{
E 4
I 4
{
E 4
	register char *p, *q;

	p = linep;
	while (*p == ' ' || *p == '\t')
		p++;
	q = buf;
	while (*p != ' ' && *p != '\t' && *p != '\0')
		*q++ = *p++;
	*q = '\0';
	linep = p;
	return (q > buf);
}


D 4
skipbl() {
E 4
I 4
static void
skipbl()
{
E 4
	while (*linep == ' ' || *linep == '\t')
		linep++;
}


D 4
int
readline() {
E 4
I 4
static int
readline()
{
E 4
	register char *p;

	if (fgets(line, 1024, infp) == NULL)
		return 0;
	for (p = line ; *p != '#' && *p != '\n' && *p != '\0' ; p++);
	while (p > line && (p[-1] == ' ' || p[-1] == '\t'))
		p--;
	*p = '\0';
	linep = line;
	linno++;
	if (p - line > BUFLEN)
		error("Line too long");
	return 1;
}



D 4
error(msg, a1, a2, a3, a4, a5, a6)
E 4
I 4
static void
#if __STDC__
error(const char *msg, ...)
#else
error(va_alist)
	va_dcl
#endif
{
	va_list va;
#if __STDC__
	va_start(va, msg);
#else
E 4
	char *msg;
D 4
	{
	fprintf(stderr, "line %d: ", linno);
	fprintf(stderr, msg, a1, a2, a3, a4, a5, a6);
	putc('\n', stderr);
E 4
I 4
	va_start(va);
	msg = va_arg(va, char *);
#endif

	(void) fprintf(stderr, "line %d: ", linno);
	(void) vfprintf(stderr, msg, va);
	(void) fputc('\n', stderr);

	va_end(va);

E 4
	exit(2);
}



D 4
char *
E 4
I 4
static char *
E 4
savestr(s)
D 4
	char *s;
	{
E 4
I 4
	const char *s;
{
E 4
	register char *p;
D 4
	char *malloc();
E 4

	if ((p = malloc(strlen(s) + 1)) == NULL)
		error("Out of space");
D 4
	strcpy(p, s);
E 4
I 4
	(void) strcpy(p, s);
E 4
	return p;
}
E 1
