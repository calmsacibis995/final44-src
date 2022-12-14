h43747
s 00034/00018/00503
d D 8.2 95/05/04 17:59:57 christos 6 5
c 
e
s 00005/00005/00516
d D 8.1 93/05/31 15:19:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00518
d D 5.4 92/06/23 18:04:55 marc 4 3
c off_t is now a quad.  0L looses.
e
s 00034/00020/00485
d D 5.3 91/03/13 19:00:58 marc 3 2
c wrong source
e
s 00002/00011/00503
d D 5.2 91/03/08 16:46:20 bostic 2 1
c make the world safe for pcc
e
s 00514/00000/00000
d D 5.1 91/03/07 20:27:43 bostic 1 0
c date and time created 91/03/07 20:27:43 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 5
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
D 3
 * Usage:  mkinit command sourcefile...
 *
E 3
 * This program scans all the source files for code to handle various
 * special events and combines this code into one file.  This (allegedly)
 * improves the structure of the program since there is no need for
 * anyone outside of a module to know that that module performs special
 * operations on particular events.  The command is executed iff init.c
 * is actually changed.
I 3
 *
 * Usage:  mkinit command sourcefile...
E 3
 */


I 2
#include <sys/cdefs.h>
I 4
#include <sys/types.h>
E 4
E 2
#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
E 6
I 3
#include <fcntl.h>
I 4
#include <unistd.h>
E 4
E 3


/*
 * OUTFILE is the name of the output file.  Output is initially written
 * to the file OUTTEMP, which is then moved to OUTFILE if OUTTEMP and
 * OUTFILE are different.
 */

#define OUTFILE "init.c"
#define OUTTEMP "init.c.new"
#define OUTOBJ "init.o"


/*
 * A text structure is basicly just a string that grows as more characters
 * are added onto the end of it.  It is implemented as a linked list of
 * blocks of characters.  The routines addstr and addchar append a string
 * or a single character, respectively, to a text structure.  Writetext
 * writes the contents of a text structure to a file.
 */

#define BLOCKSIZE 512

struct text {
	char *nextc;
	int nleft;
	struct block *start;
	struct block *last;
};      

struct block {
	struct block *next;
	char text[BLOCKSIZE];
};


/*
 * There is one event structure for each event that mkinit handles.
 */

struct event {
	char *name;		/* name of event (e.g. INIT) */
	char *routine;		/* name of routine called on event */
	char *comment;		/* comment describing routine */
	struct text code;		/* code for handling event */
};


char writer[] = "\
/*\n\
 * This file was generated by the mkinit program.\n\
 */\n\
\n";

char init[] = "\
/*\n\
 * Initialization code.\n\
 */\n";

char reset[] = "\
/*\n\
 * This routine is called when an error or an interrupt occurs in an\n\
 * interactive shell and control is returned to the main command loop.\n\
 */\n";

char shellproc[] = "\
/*\n\
 * This routine is called to initialize the shell to run a shell procedure.\n\
 */\n";


struct event event[] = {
	{"INIT", "init", init},
	{"RESET", "reset", reset},
	{"SHELLPROC", "initshellproc", shellproc},
	{NULL, NULL}
};


char *curfile;				/* current file */
int linno;				/* current line */
char *header_files[200];		/* list of header files */
struct text defines;			/* #define statements */
struct text decls;			/* declarations */
int amiddecls;				/* for formatting */


D 6
void readfile(), doevent(), doinclude(), dodecl(), output();
void addstr(), addchar(), writetext();
E 6
I 6
void readfile __P((char *));
int match __P((char *, char *));
int gooddefine __P((char *));
void doevent __P((struct event *, FILE *, char *));
void doinclude __P((char *));
void dodecl __P((char *, FILE *));
void output __P((void));
int file_changed __P((void));
int touch __P((char *));
void addstr __P((char *, struct text *));
void addchar __P((int, struct text *));
void writetext __P((struct text *, FILE *));
FILE *ckfopen __P((char *, char *));
void *ckmalloc __P((int));
char *savestr __P((char *)); 
void error __P((char *));  
E 6

#define equal(s1, s2)	(strcmp(s1, s2) == 0)

D 6
FILE *ckfopen();
char *savestr();
D 2
#ifdef __STDC__
void *ckmalloc(int);
#else
char *ckmalloc();
#endif
E 2
I 2
void *ckmalloc __P((int));
E 2
void error();

E 6
I 6
int
E 6
D 2


E 2
main(argc, argv)
I 6
	int argc;
E 6
	char **argv;
D 6
	{
E 6
I 6
{
E 6
	char **ap;
I 3
D 6
	int fd;
	char c;
E 6
E 3

	if (argc < 2)
		error("Usage:  mkinit command file...");
	header_files[0] = "\"shell.h\"";
	header_files[1] = "\"mystring.h\"";
	for (ap = argv + 2 ; *ap ; ap++)
		readfile(*ap);
	output();
	if (file_changed()) {
		unlink(OUTFILE);
		link(OUTTEMP, OUTFILE);
		unlink(OUTTEMP);
D 3
		printf("%s\n", argv[1]);
		execl("/bin/sh", "sh", "-c", argv[1], (char *)0);
		error("Can't exec shell");
E 3
	} else {
		unlink(OUTTEMP);
D 3
		exit(0);
E 3
I 3
		if (touch(OUTOBJ))
			exit(0);		/* no compilation necessary */
E 3
	}
I 3
	printf("%s\n", argv[1]);
	execl("/bin/sh", "sh", "-c", argv[1], (char *)0);
	error("Can't exec shell");
I 6

	exit(1);
E 6
E 3
}


/*
 * Parse an input file.
 */

void
readfile(fname)
	char *fname;
	{
	FILE *fp;
	char line[1024];
	struct event *ep;

	fp = ckfopen(fname, "r");
	curfile = fname;
	linno = 0;
	amiddecls = 0;
	while (fgets(line, sizeof line, fp) != NULL) {
		linno++;
		for (ep = event ; ep->name ; ep++) {
			if (line[0] == ep->name[0] && match(ep->name, line)) {
				doevent(ep, fp, fname);
				break;
			}
		}
		if (line[0] == 'I' && match("INCLUDE", line))
			doinclude(line);
		if (line[0] == 'M' && match("MKINIT", line))
			dodecl(line, fp);
		if (line[0] == '#' && gooddefine(line))
			addstr(line, &defines);
	}
	fclose(fp);
}


int
match(name, line)
	char *name;
	char *line;
D 6
	{
E 6
I 6
{
E 6
	register char *p, *q;

	p = name, q = line;
	while (*p) {
		if (*p++ != *q++)
			return 0;
	}
	if (*q != '{' && *q != ' ' && *q != '\t' && *q != '\n')
		return 0;
	return 1;
}


int
gooddefine(line)
	char *line;
D 6
	{
E 6
I 6
{
E 6
	register char *p;

	if (! match("#define", line))
		return 0;			/* not a define */
	p = line + 7;
	while (*p == ' ' || *p == '\t')
		p++;
	while (*p != ' ' && *p != '\t') {
		if (*p == '(')
			return 0;		/* macro definition */
		p++;
	}
	while (*p != '\n' && *p != '\0')
		p++;
	if (p[-1] == '\\')
		return 0;			/* multi-line definition */
	return 1;
}


void
doevent(ep, fp, fname)
	register struct event *ep;
	FILE *fp;
	char *fname;
	{
	char line[1024];
	int indent;
	char *p;

	sprintf(line, "\n      /* from %s: */\n", fname);
	addstr(line, &ep->code);
	addstr("      {\n", &ep->code);
	for (;;) {
		linno++;
		if (fgets(line, sizeof line, fp) == NULL)
			error("Unexpected EOF");
		if (equal(line, "}\n"))
			break;
		indent = 6;
		for (p = line ; *p == '\t' ; p++)
			indent += 8;
		for ( ; *p == ' ' ; p++)
			indent++;
		if (*p == '\n' || *p == '#')
			indent = 0;
		while (indent >= 8) {
			addchar('\t', &ep->code);
			indent -= 8;
		}
		while (indent > 0) {
			addchar(' ', &ep->code);
			indent--;
		}
		addstr(p, &ep->code);
	}
	addstr("      }\n", &ep->code);
}


void
doinclude(line)
	char *line;
	{
	register char *p;
	char *name;
	register char **pp;

	for (p = line ; *p != '"' && *p != '<' && *p != '\0' ; p++);
	if (*p == '\0')
		error("Expecting '\"' or '<'");
	name = p;
	while (*p != ' ' && *p != '\t' && *p != '\n')
		p++;
	if (p[-1] != '"' && p[-1] != '>')
		error("Missing terminator");
	*p = '\0';

	/* name now contains the name of the include file */
	for (pp = header_files ; *pp && ! equal(*pp, name) ; pp++);
	if (*pp == NULL)
		*pp = savestr(name);
}


void
dodecl(line1, fp)
	char *line1;
	FILE *fp;
	{
	char line[1024];
	register char *p, *q;

	if (strcmp(line1, "MKINIT\n") == 0) { /* start of struct/union decl */
		addchar('\n', &decls);
		do {
			linno++;
			if (fgets(line, sizeof line, fp) == NULL)
				error("Unterminated structure declaration");
			addstr(line, &decls);
		} while (line[0] != '}');
		amiddecls = 0;
	} else {
		if (! amiddecls)
			addchar('\n', &decls);
		q = NULL;
D 6
		for (p = line1 + 6 ; *p != '=' && *p != '/' ; p++);
E 6
I 6
		for (p = line1 + 6 ; *p != '\0' && *p != '=' && *p != '/' ; p++);
E 6
		if (*p == '=') {		/* eliminate initialization */
			for (q = p ; *q && *q != ';' ; q++);
			if (*q == '\0')
				q = NULL;
			else {
				while (p[-1] == ' ')
					p--;
				*p = '\0';
			}
		}
		addstr("extern", &decls);
		addstr(line1 + 6, &decls);
		if (q != NULL)
			addstr(q, &decls);
		amiddecls = 1;
	}
}



/*
 * Write the output to the file OUTTEMP.
 */

void
output() {
	FILE *fp;
	char **pp;
	struct event *ep;

	fp = ckfopen(OUTTEMP, "w");
	fputs(writer, fp);
	for (pp = header_files ; *pp ; pp++)
		fprintf(fp, "#include %s\n", *pp);
	fputs("\n\n\n", fp);
	writetext(&defines, fp);
	fputs("\n\n", fp);
	writetext(&decls, fp);
	for (ep = event ; ep->name ; ep++) {
		fputs("\n\n\n", fp);
		fputs(ep->comment, fp);
		fprintf(fp, "\nvoid\n%s() {\n", ep->routine);
		writetext(&ep->code, fp);
		fprintf(fp, "}\n");
	}
	fclose(fp);
}


/*
 * Return true if the new output file is different from the old one.
D 3
 * Also return true if init.o has been deleted since we want to force
 * a recompilation in this case.
E 3
 */

int
D 6
file_changed() {
E 6
I 6
file_changed() 
{
E 6
	register FILE *f1, *f2;
	register int c;

D 3
	if ((c = open(OUTOBJ, 0)) < 0)
		return 1;
	close(c);
E 3
	if ((f1 = fopen(OUTFILE, "r")) == NULL
	 || (f2 = fopen(OUTTEMP, "r")) == NULL)
		return 1;
	while ((c = getc(f1)) == getc(f2)) {
		if (c == EOF)
			return 0;
	}
	return 1;
}


I 3
/*
 * Touch a file.  Returns 0 on failure, 1 on success.
 */
E 3

I 3
int
touch(file)
	char *file;
D 6
	{
E 6
I 6
{
E 6
	int fd;
	char c;

	if ((fd = open(file, O_RDWR)) < 0)
		return 0;
	if (read(fd, &c, 1) != 1) {
		close(fd);
		return 0;
	}
D 4
	lseek(fd, 0L, 0);
E 4
I 4
	lseek(fd, (off_t)0, 0);
E 4
	write(fd, &c, 1);
	close(fd);
	return 1;
}



E 3
/*
 * A text structure is simply a block of text that is kept in memory.
 * Addstr appends a string to the text struct, and addchar appends a single
 * character.
 */

void
addstr(s, text)
	register char *s;
	register struct text *text;
	{
	while (*s) {
		if (--text->nleft < 0)
			addchar(*s++, text);
		else
			*text->nextc++ = *s++;
	}
}


void
addchar(c, text)
I 6
	int c;
E 6
	register struct text *text;
D 6
	{
E 6
I 6
{
E 6
	struct block *bp;

	if (--text->nleft < 0) {
		bp = ckmalloc(sizeof *bp);
		if (text->start == NULL)
			text->start = bp;
		else
			text->last->next = bp;
		text->last = bp;
		text->nextc = bp->text;
		text->nleft = BLOCKSIZE - 1;
	}
	*text->nextc++ = c;
}

D 3

E 3
/*
 * Write the contents of a text structure to a file.
 */
D 3

E 3
void
writetext(text, fp)
	struct text *text;
	FILE *fp;
	{
	struct block *bp;

	if (text->start != NULL) {
		for (bp = text->start ; bp != text->last ; bp = bp->next)
			fwrite(bp->text, sizeof (char), BLOCKSIZE, fp);
		fwrite(bp->text, sizeof (char), BLOCKSIZE - text->nleft, fp);
	}
}

D 3


E 3
FILE *
ckfopen(file, mode)
	char *file;
	char *mode;
	{
	FILE *fp;

	if ((fp = fopen(file, mode)) == NULL) {
		fprintf(stderr, "Can't open %s\n", file);
		exit(2);
	}
	return fp;
}

D 3


E 3
D 2
#ifdef __STDC__
E 2
void *
D 2
#else
char *
#endif
E 2
D 6
ckmalloc(nbytes) {
E 6
I 6
ckmalloc(nbytes) 
	int nbytes;
{
E 6
	register char *p;
D 6
	char *malloc();
E 6

	if ((p = malloc(nbytes)) == NULL)
		error("Out of space");
	return p;
}

D 3

E 3
char *
savestr(s)
	char *s;
	{
	register char *p;

	p = ckmalloc(strlen(s) + 1);
	strcpy(p, s);
	return p;
}
D 3


E 3

void
error(msg)
	char *msg;
	{
	if (curfile != NULL)
		fprintf(stderr, "%s:%d: ", curfile, linno);
	fprintf(stderr, "%s\n", msg);
	exit(2);
}
E 1
