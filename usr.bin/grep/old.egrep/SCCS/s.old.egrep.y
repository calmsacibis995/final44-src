h22960
s 00005/00005/00654
d D 8.1 93/06/06 14:48:50 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00001/00642
d D 4.7 91/04/17 17:52:25 bostic 8 7
c new copyright; att/bsd/shared
e
s 00006/00001/00637
d D 4.6 87/10/07 17:25:18 bostic 7 6
c implement -o flag; *always* print the file name
e
s 00024/00002/00614
d D 4.5 87/10/03 15:41:41 bostic 6 5
c support -i flag
e
s 00032/00015/00584
d D 4.4 85/05/29 18:11:39 mckusick 5 4
c do more reasonable buffering
e
s 00004/00002/00595
d D 4.3 83/03/13 16:21:04 edward 4 3
c Fixed exit after file open error bug.  Same as fgrep.
e
s 00009/00003/00588
d D 4.2 82/11/08 12:00:04 rrh 3 1
c Allow -f option and reading subject text from stdin to not be disjoint options
e
s 00008/00002/00589
d R 4.2 82/11/08 08:56:24 rrh 2 1
c Allow -f option and reading subject text from stdin to not be disjoint
e
s 00591/00000/00000
d D 4.1 80/10/01 17:29:51 bill 1 0
c date and time created 80/10/01 17:29:51 by bill
e
u
U
t
T
I 1
/*
 * egrep -- print lines containing (or not containing) a regular expression
 *
 *	status returns:
 *		0 - ok, and some matches
 *		1 - ok, but no matches
 *		2 - some error
 */
%token CHAR DOT CCL NCCL OR CAT STAR PLUS QUEST
%left OR
%left CHAR DOT CCL NCCL '('
%left CAT
%left STAR PLUS QUEST

%{
D 8
static char *sccsid = "%W% (Berkeley) %G%";
E 8
I 8
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 8
#include <stdio.h>
I 5
#include <sys/types.h>
#include <sys/stat.h>
I 6
#include <ctype.h>
E 6
E 5

I 5
#define BLKSIZE 8192
E 5
#define MAXLIN 350
#define MAXPOS 4000
#define NCHARS 128
#define NSTATES 128
#define FINAL -1
char gotofn[NSTATES][NCHARS];
I 6
char cmap[256];
E 6
int state[NSTATES];
char out[NSTATES];
int line = 1;
int name[MAXLIN];
int left[MAXLIN];
int right[MAXLIN];
int parent[MAXLIN];
int foll[MAXLIN];
int positions[MAXPOS];
char chars[MAXLIN];
int nxtpos;
int nxtchar = 0;
int tmpstat[MAXLIN];
int initstat[MAXLIN];
int xstate;
int count;
int icount;
char *input;
I 3
FILE *exprfile;
E 3

long	lnum;
int	bflag;
int	cflag;
int	fflag;
I 6
int	iflag;
E 6
int	lflag;
int	nflag;
int	hflag	= 1;
I 7
int	oflag;
E 7
int	sflag;
int	vflag;
I 4
int	retcode = 0;
E 4
int	nfile;
int	blkno;
long	tln;
int	nsucc;

int	f;
D 3
int	fname;
E 3
I 3
char	*fname;
E 3
%}

%%
s:	t
		={ unary(FINAL, $1);
		  line--;
		}
	;
t:	b r
		={ $$ = node(CAT, $1, $2); }
	| OR b r OR
		={ $$ = node(CAT, $2, $3); }
	| OR b r
		={ $$ = node(CAT, $2, $3); }
	| b r OR
		={ $$ = node(CAT, $1, $2); }
	;
b:
		={ $$ = enter(DOT);
		   $$ = unary(STAR, $$); }
	;
r:	CHAR
		={ $$ = enter($1); }
	| DOT
		={ $$ = enter(DOT); }
	| CCL
		={ $$ = cclenter(CCL); }
	| NCCL
		={ $$ = cclenter(NCCL); }
	;

r:	r OR r
		={ $$ = node(OR, $1, $3); }
	| r r %prec CAT
		={ $$ = node(CAT, $1, $2); }
	| r STAR
		={ $$ = unary(STAR, $1); }
	| r PLUS
		={ $$ = unary(PLUS, $1); }
	| r QUEST
		={ $$ = unary(QUEST, $1); }
	| '(' r ')'
		={ $$ = $2; }
	| error 
	;

%%
yyerror(s) {
	fprintf(stderr, "egrep: %s\n", s);
	exit(2);
}

yylex() {
	extern int yylval;
	int cclcnt, x;
	register char c, d;
	switch(c = nextch()) {
		case '$':
		case '^': c = '\n';
			goto defchar;
		case '|': return (OR);
		case '*': return (STAR);
		case '+': return (PLUS);
		case '?': return (QUEST);
		case '(': return (c);
		case ')': return (c);
		case '.': return (DOT);
		case '\0': return (0);
		case '\n': return (OR);
		case '[': 
			x = CCL;
			cclcnt = 0;
			count = nxtchar++;
			if ((c = nextch()) == '^') {
				x = NCCL;
				c = nextch();
			}
			do {
				if (c == '\0') synerror();
				if (c == '-' && cclcnt > 0 && chars[nxtchar-1] != 0) {
					if ((d = nextch()) != 0) {
						c = chars[nxtchar-1];
						while (c < d) {
							if (nxtchar >= MAXLIN) overflo();
							chars[nxtchar++] = ++c;
							cclcnt++;
						}
						continue;
					}
				}
				if (nxtchar >= MAXLIN) overflo();
				chars[nxtchar++] = c;
				cclcnt++;
			} while ((c = nextch()) != ']');
			chars[count] = cclcnt;
			return (x);
		case '\\':
			if ((c = nextch()) == '\0') synerror();
		defchar:
		default: yylval = c; return (CHAR);
	}
}
nextch() {
D 6
	register char c;
E 6
I 6
	register int c;
E 6
	if (fflag) {
D 3
		if ((c = getc(stdin)) == EOF) return(0);
E 3
I 3
		if ((c = getc(exprfile)) == EOF) {
			fclose(exprfile);
			return(0);
		}
E 3
	}
	else c = *input++;
	return(c);
}

synerror() {
	fprintf(stderr, "egrep: syntax error\n");
	exit(2);
}

enter(x) int x; {
	if(line >= MAXLIN) overflo();
	name[line] = x;
	left[line] = 0;
	right[line] = 0;
	return(line++);
}

cclenter(x) int x; {
	register linno;
	linno = enter(x);
	right[linno] = count;
	return (linno);
}

node(x, l, r) {
	if(line >= MAXLIN) overflo();
	name[line] = x;
	left[line] = l;
	right[line] = r;
	parent[l] = line;
	parent[r] = line;
	return(line++);
}

unary(x, d) {
	if(line >= MAXLIN) overflo();
	name[line] = x;
	left[line] = d;
	right[line] = 0;
	parent[d] = line;
	return(line++);
}
overflo() {
	fprintf(stderr, "egrep: regular expression too long\n");
	exit(2);
}

cfoll(v) {
	register i;
	if (left[v] == 0) {
		count = 0;
		for (i=1; i<=line; i++) tmpstat[i] = 0;
		follow(v);
		add(foll, v);
	}
	else if (right[v] == 0) cfoll(left[v]);
	else {
		cfoll(left[v]);
		cfoll(right[v]);
	}
}
cgotofn() {
	register c, i, k;
	int n, s;
	char symbol[NCHARS];
	int j, nc, pc, pos;
	int curpos, num;
	int number, newpos;
	count = 0;
	for (n=3; n<=line; n++) tmpstat[n] = 0;
	if (cstate(line-1)==0) {
		tmpstat[line] = 1;
		count++;
		out[0] = 1;
	}
	for (n=3; n<=line; n++) initstat[n] = tmpstat[n];
	count--;		/*leave out position 1 */
	icount = count;
	tmpstat[1] = 0;
	add(state, 0);
	n = 0;
	for (s=0; s<=n; s++)  {
		if (out[s] == 1) continue;
		for (i=0; i<NCHARS; i++) symbol[i] = 0;
		num = positions[state[s]];
		count = icount;
		for (i=3; i<=line; i++) tmpstat[i] = initstat[i];
		pos = state[s] + 1;
		for (i=0; i<num; i++) {
			curpos = positions[pos];
			if ((c = name[curpos]) >= 0) {
				if (c < NCHARS) symbol[c] = 1;
				else if (c == DOT) {
					for (k=0; k<NCHARS; k++)
						if (k!='\n') symbol[k] = 1;
				}
				else if (c == CCL) {
					nc = chars[right[curpos]];
					pc = right[curpos] + 1;
					for (k=0; k<nc; k++) symbol[chars[pc++]] = 1;
				}
				else if (c == NCCL) {
					nc = chars[right[curpos]];
					for (j = 0; j < NCHARS; j++) {
						pc = right[curpos] + 1;
						for (k = 0; k < nc; k++)
							if (j==chars[pc++]) goto cont;
						if (j!='\n') symbol[j] = 1;
						cont:;
					}
				}
				else printf("something's funny\n");
			}
			pos++;
		}
		for (c=0; c<NCHARS; c++) {
			if (symbol[c] == 1) { /* nextstate(s,c) */
				count = icount;
				for (i=3; i <= line; i++) tmpstat[i] = initstat[i];
				pos = state[s] + 1;
				for (i=0; i<num; i++) {
					curpos = positions[pos];
					if ((k = name[curpos]) >= 0)
						if (
							(k == c)
							| (k == DOT)
							| (k == CCL && member(c, right[curpos], 1))
							| (k == NCCL && member(c, right[curpos], 0))
						) {
							number = positions[foll[curpos]];
							newpos = foll[curpos] + 1;
							for (k=0; k<number; k++) {
								if (tmpstat[positions[newpos]] != 1) {
									tmpstat[positions[newpos]] = 1;
									count++;
								}
								newpos++;
							}
						}
					pos++;
				} /* end nextstate */
				if (notin(n)) {
					if (n >= NSTATES) overflo();
					add(state, ++n);
					if (tmpstat[line] == 1) out[n] = 1;
					gotofn[s][c] = n;
				}
				else {
					gotofn[s][c] = xstate;
				}
			}
		}
	}
}

cstate(v) {
	register b;
	if (left[v] == 0) {
		if (tmpstat[v] != 1) {
			tmpstat[v] = 1;
			count++;
		}
		return(1);
	}
	else if (right[v] == 0) {
		if (cstate(left[v]) == 0) return (0);
		else if (name[v] == PLUS) return (1);
		else return (0);
	}
	else if (name[v] == CAT) {
		if (cstate(left[v]) == 0 && cstate(right[v]) == 0) return (0);
		else return (1);
	}
	else { /* name[v] == OR */
		b = cstate(right[v]);
		if (cstate(left[v]) == 0 || b == 0) return (0);
		else return (1);
	}
}


member(symb, set, torf) {
	register i, num, pos;
	num = chars[set];
	pos = set + 1;
	for (i=0; i<num; i++)
		if (symb == chars[pos++]) return (torf);
	return (!torf);
}

notin(n) {
	register i, j, pos;
	for (i=0; i<=n; i++) {
		if (positions[state[i]] == count) {
			pos = state[i] + 1;
			for (j=0; j < count; j++)
				if (tmpstat[positions[pos++]] != 1) goto nxt;
			xstate = i;
			return (0);
		}
		nxt: ;
	}
	return (1);
}

add(array, n) int *array; {
	register i;
	if (nxtpos + count > MAXPOS) overflo();
	array[n] = nxtpos;
	positions[nxtpos++] = count;
	for (i=3; i <= line; i++) {
		if (tmpstat[i] == 1) {
			positions[nxtpos++] = i;
		}
	}
}

follow(v) int v; {
	int p;
	if (v == line) return;
	p = parent[v];
	switch(name[p]) {
		case STAR:
		case PLUS:	cstate(v);
				follow(p);
				return;

		case OR:
		case QUEST:	follow(p);
				return;

		case CAT:	if (v == left[p]) {
					if (cstate(right[p]) == 0) {
						follow(p);
						return;
					}
				}
				else follow(p);
				return;
		case FINAL:	if (tmpstat[line] != 1) {
					tmpstat[line] = 1;
					count++;
				}
				return;
	}
}


main(argc, argv)
char **argv;
{
I 6
	register int i;

E 6
	while (--argc > 0 && (++argv)[0][0]=='-')
		switch (argv[0][1]) {

		case 's':
			sflag++;
			continue;

		case 'h':
			hflag = 0;
			continue;

I 7
		case 'o':
			oflag++;
			continue;

E 7
		case 'b':
			bflag++;
			continue;

		case 'c':
			cflag++;
			continue;

		case 'e':
			argc--;
			argv++;
			goto out;

		case 'f':
			fflag++;
			continue;

I 6
		case 'i':
			iflag++;
			for ( i = 'A'; i <= 'Z'; i++ )
				cmap[i] = (char) tolower ( i );
			continue;

E 6
		case 'l':
			lflag++;
			continue;

		case 'n':
			nflag++;
			continue;

		case 'v':
			vflag++;
			continue;

		default:
			fprintf(stderr, "egrep: unknown flag\n");
			continue;
		}
out:
	if (argc<=0)
		exit(2);
I 6

	for (i = 0; i < 256; ++i)
		cmap[i] = (char)i;

E 6
	if (fflag) {
D 3
		if (freopen(fname = *argv, "r", stdin) == NULL) {
E 3
I 3
		fname = *argv;
		exprfile = fopen(fname, "r");
		if (exprfile == (FILE *)NULL) {
E 3
			fprintf(stderr, "egrep: can't open %s\n", fname);
			exit(2);
		}
	}
	else input = *argv;
I 6
	if ( iflag ) {
		register char *s;
		for ( s = input; *s != '\0'; s++ )
			if ( isupper ( (int)(*s) ) )
				*s = (char) tolower ( (int)(*s) );
	}
E 6
	argc--;
	argv++;

	yyparse();

	cfoll(line-1);
	cgotofn();
	nfile = argc;
	if (argc<=0) {
		if (lflag) exit(1);
		execute(0);
	}
	else while (--argc >= 0) {
		execute(*argv);
		argv++;
	}
D 4
	exit(nsucc == 0);
E 4
I 4
	exit(retcode != 0 ? retcode : nsucc == 0);
E 4
}

execute(file)
char *file;
{
	register char *p;
	register cstat;
	register ccount;
I 6
	register char *cmapr = cmap;
E 6
D 5
	char buf[1024];
E 5
I 5
	static char *buf;
	static int blksize;
	struct stat stb;
E 5
	char *nlp;
	int istat;
	if (file) {
		if ((f = open(file, 0)) < 0) {
			fprintf(stderr, "egrep: can't open %s\n", file);
D 4
			exit(2);
E 4
I 4
			retcode = 2;
			return;
E 4
		}
	}
	else f = 0;
I 5
	if (buf == NULL) {
		if (fstat(f, &stb) > 0 && stb.st_blksize > 0)
			blksize = stb.st_blksize;
		else
			blksize = BLKSIZE;
		buf = (char *)malloc(2*blksize);
		if (buf == NULL) {
			fprintf(stderr, "egrep: no memory for %s\n", file);
			retcode = 2;
			return;
		}
	}
E 5
	ccount = 0;
	lnum = 1;
	tln = 0;
	blkno = 0;
	p = buf;
	nlp = p;
D 5
	if ((ccount = read(f,p,512))<=0) goto done;
E 5
I 5
	if ((ccount = read(f,p,blksize))<=0) goto done;
E 5
	istat = cstat = gotofn[0]['\n'];
	if (out[cstat]) goto found;
	for (;;) {
D 6
		cstat = gotofn[cstat][*p&0377];	/* all input chars made positive */
E 6
I 6
		cstat = gotofn[cstat][(unsigned char)cmapr[*(unsigned char *)p]];
E 6
		if (out[cstat]) {
		found:	for(;;) {
				if (*p++ == '\n') {
					if (vflag == 0) {
				succeed:	nsucc = 1;
						if (cflag) tln++;
						else if (sflag)
							;	/* ugh */
						else if (lflag) {
							printf("%s\n", file);
							close(f);
							return;
						}
						else {
D 7
							if (nfile > 1 && hflag) printf("%s:", file);
E 7
I 7
							if (nfile > 1 && hflag || oflag) printf("%s:", file);
E 7
							if (bflag) printf("%d:", blkno);
							if (nflag) printf("%ld:", lnum);
							if (p <= nlp) {
D 5
								while (nlp < &buf[1024]) putchar(*nlp++);
E 5
I 5
								while (nlp < &buf[2*blksize]) putchar(*nlp++);
E 5
								nlp = buf;
							}
							while (nlp < p) putchar(*nlp++);
						}
					}
					lnum++;
					nlp = p;
					if ((out[(cstat=istat)]) == 0) goto brk2;
				}
				cfound:
				if (--ccount <= 0) {
D 5
					if (p <= &buf[512]) {
						if ((ccount = read(f, p, 512)) <= 0) goto done;
E 5
I 5
					if (p <= &buf[blksize]) {
						if ((ccount = read(f, p, blksize)) <= 0) goto done;
E 5
					}
D 5
					else if (p == &buf[1024]) {
E 5
I 5
					else if (p == &buf[2*blksize]) {
E 5
						p = buf;
D 5
						if ((ccount = read(f, p, 512)) <= 0) goto done;
E 5
I 5
						if ((ccount = read(f, p, blksize)) <= 0) goto done;
E 5
					}
					else {
D 5
						if ((ccount = read(f, p, &buf[1024]-p)) <= 0) goto done;
E 5
I 5
						if ((ccount = read(f, p, &buf[2*blksize]-p)) <= 0) goto done;
E 5
					}
D 5
					blkno++;
E 5
I 5
					blkno += ccount / 512;
E 5
				}
			}
		}
		if (*p++ == '\n') {
			if (vflag) goto succeed;
			else {
				lnum++;
				nlp = p;
				if (out[(cstat=istat)]) goto cfound;
			}
		}
		brk2:
		if (--ccount <= 0) {
D 5
			if (p <= &buf[512]) {
				if ((ccount = read(f, p, 512)) <= 0) break;
E 5
I 5
			if (p <= &buf[blksize]) {
				if ((ccount = read(f, p, blksize)) <= 0) break;
E 5
			}
D 5
			else if (p == &buf[1024]) {
E 5
I 5
			else if (p == &buf[2*blksize]) {
E 5
				p = buf;
D 5
				if ((ccount = read(f, p, 512)) <= 0) break;
E 5
I 5
				if ((ccount = read(f, p, blksize)) <= 0) break;
E 5
			}
			else {
D 5
				if ((ccount = read(f, p, &buf[1024] - p)) <= 0) break;
E 5
I 5
				if ((ccount = read(f, p, &buf[2*blksize] - p)) <= 0) break;
E 5
			}
D 5
			blkno++;
E 5
I 5
			blkno += ccount / 512;
E 5
		}
	}
done:	close(f);
	if (cflag) {
		if (nfile > 1)
			printf("%s:", file);
		printf("%ld\n", tln);
	}
}
E 1
