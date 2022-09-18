h44586
s 00005/00002/00355
d D 8.3 95/05/04 15:29:11 bostic 14 13
c optarg/optind moved to unistd.h
e
s 00002/00002/00355
d D 8.2 94/01/03 10:04:35 bostic 13 12
c rename fgetline -> fgetln
e
s 00005/00005/00352
d D 8.1 93/05/31 17:44:13 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00007/00347
d D 5.3 93/03/04 14:32:32 bostic 11 10
c rework fgetline(3) to be 8-bit clean
e
s 00002/00001/00352
d D 5.2 92/01/08 14:19:16 bostic 10 9
c add Keith Gabryelski to contrib listing
e
s 00282/00420/00071
d D 5.1 91/11/10 14:24:27 bostic 9 8
c Jim Oldroyd's version of quiz
e
s 00006/00001/00485
d D 4.8 91/04/08 18:03:44 bostic 8 7
c new copyright; att/bsd/shared
e
s 00004/00001/00482
d D 4.7 91/02/28 14:24:24 bostic 7 6
c ANSI
e
s 00001/00001/00482
d D 4.6 91/02/04 23:29:06 bostic 6 5
c _IONBF -> setvbuf(3)
e
s 00003/00001/00480
d D 4.5 90/05/12 15:26:43 bostic 5 4
c move paths to pathnames.h, move to /usr/share
e
s 00006/00004/00475
d D 4.4 88/01/02 17:36:05 bostic 4 3
c assign getc return to an int; fix for ANSI C
e
s 00006/00004/00473
d D 4.3 87/06/17 17:39:46 bostic 3 2
c fix dropping core on ^C
e
s 00002/00000/00475
d D 4.2 85/01/09 16:36:03 ralph 2 1
c fix type warnings
e
s 00475/00000/00000
d D 4.1 82/10/24 18:26:43 mckusick 1 0
c date and time created 82/10/24 18:26:43 by mckusick
e
u
U
t
T
I 8
/*-
D 9
 * %sccs.include.proprietary.c%
E 9
I 9
D 12
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
D 10
 * Jim R. Oldroyd at The Instruction Set.
E 10
I 10
 * Jim R. Oldroyd at The Instruction Set and Keith Gabryelski at
 * Commodore Business Machines.
E 10
 *
 * %sccs.include.redist.c%
E 9
 */
E 8
I 1

D 8
static char sccsid[] = "	%M%	%I%	%E%	";
E 8
I 8
#ifndef lint
I 9
D 12
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8

I 9
#include <sys/types.h>
I 14

#include <ctype.h>
E 14
#include <errno.h>
D 14
#include <time.h>
E 14
E 9
#include <stdio.h>
D 9
#include <signal.h>
E 9
I 9
#include <stdlib.h>
#include <string.h>
D 14
#include <ctype.h>
E 14
I 14
#include <time.h>
#include <unistd.h>

E 14
#include "quiz.h"
E 9
I 5
#include "pathnames.h"

E 5
D 9
#define NF 10
#define NL 300
#define NC 200
#define SL 100
#define NA 10
E 9
I 9
static QE qlist;
static int catone, cattwo, tflag;
static u_int qsize;
E 9

D 9
int tflag;
int xx[NL];
char score[NL];
int rights;
int wrongs;
int guesses;
FILE *input;
int nl = 0;
int na = NA;
int inc;
int ptr = 0;
int nc = 0;
char line[150];
char response[100];
char *tmp[NF];
int select[NF];
E 9
I 9
D 11
char	*appdstr __P((char *, char *));
E 11
I 11
char	*appdstr __P((char *, char *, size_t));
E 11
void	 downcase __P((char *));
void	 err __P((const char *, ...));
void	 get_cats __P((char *, char *));
void	 get_file __P((char *));
char	*next_cat __P((char *));
void	 quiz __P((void));
void	 score __P((u_int, u_int, u_int));
void	 show_index __P((void));
void	 usage __P((void));
E 9

D 9
readline()
E 9
I 9
int
main(argc, argv)
	int argc;
	char *argv[];
E 9
{
I 4
	register int ch;
E 4
D 9
	char *t;
loop:
D 4
	for(t=line;(*t=getc(input))!=-1;t++) {
E 4
I 4
	for(t=line;(ch=getc(input))!=-1;t++) {
		*t = ch;
E 4
		nc++;
		if(*t==' '&&(t==line||t[-1]==' '))
			t--;
		if(*t=='\n') {
			if(t[-1]=='\\')		/*inexact test*/
				continue;
			while(t>line&&t[-1]==' ')
				*--t = '\n';
			*++t = 0;
			return(1);
		}
		if(t-line>=NC) {
			printf("Too hard for me\n");
			do {
D 4
				*line = getc(input);
				if(*line==0377)
E 4
I 4
				if ((ch = getc(input)) == EOF)
E 4
					return(0);
D 4
			} while(*line!='\n');
E 4
I 4
			} while(ch!='\n');
			*line = '\n';
E 4
			goto loop;
		}
	}
	return(0);
}
E 9
I 9
	char *indexfile;
E 9

D 9
char *eu;
char *ev;
cmp(u,v)
char *u,*v;
{
	int x;
	eu = u;
	ev = v;
	x = disj(1);
	if(x!=1)
		return(x);
	return(eat(1,0));
}

disj(s)
{
	int t, x;
	char *u;
	u = eu;
	t = 0;
	for(;;) {
		x = string(s);
		if(x>1)
			return(x);
		switch(*ev) {
		case 0:
		case ']':
		case '}':
			return(t|x&s);
		case '|':
			ev++;
			t |= s;
			s = 0;
			continue;
		}
		if(s) eu = u;
		if(string(0)>1)
			return(2);
		switch(*ev) {
		case 0:
		case ']':
			return(0);
		case '}':
			return(1);
		case '|':
			ev++;
			continue;
E 9
I 9
	indexfile = _PATH_QUIZIDX;
	while ((ch = getopt(argc, argv, "i:t")) != EOF)
		switch(ch) {
		case 'i':
			indexfile = optarg;
			break;
		case 't':
			tflag = 1;
			break;
		case '?':
E 9
		default:
D 9
			return(2);
E 9
I 9
			usage();
E 9
		}
D 9
	}
}
E 9
I 9
	argc -= optind;
	argv += optind;
E 9

D 9
string(s)
{
	int x;
	for(;;) {
		switch(*ev) {
		case 0:
		case '|':
		case ']':
		case '}':
			return(1);
		case '\\':
			ev++;
			if(*ev==0)
				return(2);
			if(*ev=='\n') {
				ev++;
				continue;
			}
		default:
			if(eat(s,*ev)==1)
				continue;
			return(0);
		case '[':
			ev++;
			x = disj(s);
			if(*ev!=']' || x>1)
				return(2);
			ev++;
			if(s==0)
				continue;
			if(x==0)
				return(0);
			continue;
		case '{':
			ev++;
			x = disj(s);
			if(*ev!='}'||x>1)
				return(2);
			ev++;
			continue;
		}
E 9
I 9
	switch(argc) {
	case 0:
		get_file(indexfile);
		show_index();
		break;
	case 2:
		get_file(indexfile);
		get_cats(argv[0], argv[1]);
		quiz();
		break;
	default:
		usage();
E 9
	}
I 9
	exit(0);
E 9
}

D 9
eat(s,c)
char c;
E 9
I 9
void
get_file(file)
	char *file;
E 9
{
D 9
	if(*ev!=c)
		return(2);
	if(s==0) {
		ev++;
		return(1);
	}
	if(fold(*eu)!=fold(c))
		return(0);
	eu++;
	ev++;
	return(1);
}
E 9
I 9
	register FILE *fp;
	register QE *qp;
	size_t len;
	char *lp;
E 9

D 9
fold(c)
char c;
{
	if(c<'A'||c>'Z')
		return(c);
	return(c|040);
}
E 9
I 9
	if ((fp = fopen(file, "r")) == NULL)
		err("%s: %s", file, strerror(errno));
E 9

D 9
publish(t)
char *t;
{
	ev = t;
	pub1(1);
}

pub1(s)
{
	for(;;ev++){
		switch(*ev) {
		case '|':
			s = 0;
			ev;
			continue;
		case ']':
		case '}':
		case 0:
			return;
		case '[':
		case '{':
			ev++;
			pub1(s);
			ev;
			continue;
		case '\\':
			if(*++ev=='\n')
				continue;
		default:
			if(s)
				putchar(*ev);
E 9
I 9
	/*
	 * XXX
	 * Should really free up space from any earlier read list
	 * but there are no reverse pointers to do so with.
	 */
	qp = &qlist;
	qsize = 0;
D 13
	while ((lp = fgetline(fp, &len)) != NULL) {
E 13
I 13
	while ((lp = fgetln(fp, &len)) != NULL) {
E 13
		if (qp->q_text && qp->q_text[strlen(qp->q_text) - 1] == '\\')
D 11
			qp->q_text = appdstr(qp->q_text, lp);
E 11
I 11
			qp->q_text = appdstr(qp->q_text, lp, len);
E 11
		else {
			if ((qp->q_next = malloc(sizeof(QE))) == NULL)
				err("%s", strerror(errno));
			qp = qp->q_next;
I 11
			lp[len - 1] = '\0';
E 11
			if ((qp->q_text = strdup(lp)) == NULL)
				err("%s", strerror(errno));
			qp->q_asked = qp->q_answered = FALSE;
			qp->q_next = NULL;
			++qsize;
E 9
		}
	}
I 9
	(void)fclose(fp);
E 9
}

D 9
segment(u,w)
char *u, *w[];
E 9
I 9
void
show_index()
E 9
{
D 9
	char *s;
	int i;
	char *t;
	s = u;
	for(i=0;i<NF;i++) {
		u = s;
		t = w[i];
		while(*s!=':'&&*s!='\n'&&s-u<SL) {
			if(*s=='\\')  {
				if(s[1] == '\n') {
					s += 2;
					continue;
				}
				*t++ = *s++;
			}
			*t++ = *s++;
		}
E 9
I 9
	register QE *qp;
	register char *p, *s;
	FILE *pf;
E 9

D 9
		while(*s!=':'&&*s!='\n')
			s++;
		*t = 0;
		if(*s++=='\n') {
			return(i+1);
E 9
I 9
	if ((pf = popen(_PATH_PAGER, "w")) == NULL)
		err("%s: %s", _PATH_PAGER, strerror(errno));
	(void)fprintf(pf, "Subjects:\n\n");
	for (qp = qlist.q_next; qp; qp = qp->q_next) {
		for (s = next_cat(qp->q_text); s; s = next_cat(s)) {
			if (!rxp_compile(s))
				err("%s", rxperr);
			if (p = rxp_expand())
				(void)fprintf(pf, "%s ", p);
E 9
		}
I 9
		(void)fprintf(pf, "\n");
E 9
	}
D 9
	printf("Too many facts about one thing\n");
E 9
I 9
	(void)fprintf(pf, "\n%s\n%s\n%s\n",
"For example, \"quiz victim killer\" prints a victim's name and you reply",
"with the killer, and \"quiz killer victim\" works the other way around.",
"Type an empty line to get the correct answer.");
	(void)pclose(pf);
E 9
}

D 9
perm(u,m,v,n,p)
int p[];
char *u[], *v[];
E 9
I 9
void
get_cats(cat1, cat2)
	char *cat1, *cat2;
E 9
{
D 9
	int i, j;
	int x;
	for(i=0;i<m;i++) {
		for(j=0;j<n;j++) {
			x = cmp(u[i],v[j]);
			if(x>1) badinfo();
			if(x==0)
				continue;
			p[i] = j;
			goto uloop;
		}
		return(0);
uloop:		;
	}
	return(1);
}
E 9
I 9
	register QE *qp;
	int i;
	char *s;
E 9

D 9
find(u,m)
char *u[];
{
	int n;
	while(readline()){
		n = segment(line,tmp);
		if(perm(u,m,tmp+1,n-1,select))
			return(1);
	}
	return(0);
}

readindex()
{
	xx[0] = nc = 0;
	while(readline()) {
		xx[++nl] = nc;
		if(nl>=NL) {
			printf("I've forgotten some of it;\n");
			printf("I remember %d items.\n", nl);
			break;
E 9
I 9
	downcase(cat1);
	downcase(cat2);
	for (qp = qlist.q_next; qp; qp = qp->q_next) {
		s = next_cat(qp->q_text);
		catone = cattwo = i = 0;
		while (s) {
			if (!rxp_compile(s))
				err("%s", rxperr);
			i++;
			if (rxp_match(cat1))
				catone = i;
			if (rxp_match(cat2))
				cattwo = i;
			s = next_cat(s);
E 9
		}
I 9
		if (catone && cattwo && catone != cattwo) {
			if (!rxp_compile(qp->q_text))
				err("%s", rxperr);
			get_file(rxp_expand());
			return;
		}
E 9
	}
I 9
	err("invalid categories");
E 9
}

D 9
talloc()
E 9
I 9
void
quiz()
E 9
{
D 9
	int i;
I 2
	char *malloc();
E 9
I 9
	register QE *qp;
	register int i;
I 11
	size_t len;
E 11
	u_int guesses, rights, wrongs;
	int next;
D 11
	char *s, *t, question[LINE_SZ];
	char *answer;
E 11
I 11
	char *answer, *s, *t, question[LINE_SZ];
E 11
E 9

E 2
D 9
	for(i=0;i<NF;i++)
		tmp[i] = malloc(SL);
}

I 7
void done();

E 7
main(argc,argv)
char *argv[];
{
	register j;
	int i;
	int x;
	int z;
	char *info;
	int tvec[2];
	char *t;
D 7
	extern done();
E 7
	int count;
D 5
	info = "/usr/games/lib/quiz.k/index";
E 5
I 5
	info = _PATH_INDEX;
E 5
	time(tvec);
	inc = tvec[1]&077774|01;
loop:
	if(argc>1&&*argv[1]=='-') {
		switch(argv[1][1]) {
		case 'i':
			if(argc>2) 
				info = argv[2];
			argc -= 2;
			argv += 2;
			goto loop;
		case 't':
			tflag = 1;
			argc--;
			argv++;
			goto loop;
E 9
I 9
	srandom(time(NULL));
	guesses = rights = wrongs = 0;
	for (;;) {
		if (qsize == 0)
			break;
		next = random() % qsize;
		qp = qlist.q_next;
		for (i = 0; i < next; i++)
			qp = qp->q_next;
		while (qp && qp->q_answered)
			qp = qp->q_next;
		if (!qp) {
			qsize = next;
			continue;
E 9
		}
D 9
	}
	input = fopen(info,"r");
	if(input==NULL) {
		printf("No info\n");
		exit(0);
	}
	talloc();
	if(argc<=2)
		instruct(info);
	signal(SIGINT,done);
	argv[argc] = 0;
	if(find(&argv[1],argc-1)==0)
		dunno();
	fclose(input);
	input = fopen(tmp[0],"r");
	if(input==NULL)
		dunno();
	readindex();
	if(!tflag || na>nl)
		na = nl;
D 6
	stdout->_flag |= _IONBF;
E 6
I 6
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
E 6
	for(;;) {
		i = next();
		fseek(input,xx[i]+0L,0);
		z = xx[i+1]-xx[i];
		for(j=0;j<z;j++)
			line[j] = getc(input);
		segment(line,tmp);
		if(*tmp[select[0]] == '\0' || *tmp[select[1]] == '\0') {
			score[i] = 1;
E 9
I 9
		if (tflag && random() % 100 > 20) {
			/* repeat questions in tutorial mode */
			while (qp && (!qp->q_asked || qp->q_answered))
				qp = qp->q_next;
			if (!qp)
				continue;
		}
		s = qp->q_text;
		for (i = 0; i < catone - 1; i++)
			s = next_cat(s);
		if (!rxp_compile(s))
			err("%s", rxperr);
		t = rxp_expand();
		if (!t || *t == '\0') {
			qp->q_answered = TRUE;
E 9
			continue;
		}
D 9
		publish(tmp[select[0]]);
		printf("\n");
		for(count=0;;count++) {
			if(query(response)==0) {
				publish(tmp[select[1]]);
				printf("\n");
				if(count==0) wrongs++;
				score[i] = tflag?-1:1;
E 9
I 9
		(void)strcpy(question, t);
		s = qp->q_text;
		for (i = 0; i < cattwo - 1; i++)
			s = next_cat(s);
		if (!rxp_compile(s))
			err("%s", rxperr);
		t = rxp_expand();
		if (!t || *t == '\0') {
			qp->q_answered = TRUE;
			continue;
		}
		qp->q_asked = TRUE;
		(void)printf("%s?\n", question);
		for (;; ++guesses) {
D 11
			if ((answer = fgetline(stdin, NULL)) == NULL) {
E 11
I 11
D 13
			if ((answer = fgetline(stdin, &len)) == NULL) {
E 13
I 13
			if ((answer = fgetln(stdin, &len)) == NULL) {
E 13
E 11
				score(rights, wrongs, guesses);
				exit(0);
			}
I 11
			answer[len - 1] = '\0';
E 11
			downcase(answer);
			if (rxp_match(answer)) {
				(void)printf("Right!\n");
				++rights;
				qp->q_answered = TRUE;
E 9
				break;
			}
D 9
			x = cmp(response,tmp[select[1]]);
			if(x>1) badinfo();
			if(x==1) {
				printf("Right!\n");
				if(count==0) rights++;
				if(++score[i]>=1 && na<nl)
					na++;
E 9
I 9
			if (*answer == '\0') {
				(void)printf("%s\n", t);
				++wrongs;
				if (!tflag)
					qp->q_answered = TRUE;
E 9
				break;
			}
D 9
			printf("What?\n");
			if(count==0) wrongs++;
			score[i] = tflag?-1:1;
E 9
I 9
			(void)printf("What?\n");
E 9
		}
D 9
		guesses += count;
E 9
	}
I 9
	score(rights, wrongs, guesses);
E 9
}

D 9
query(r)
char *r;
E 9
I 9
char *
next_cat(s)
	register char *	s;
E 9
{
D 9
	char *t;
	for(t=r;;t++) {
		if(read(0,t,1)==0)
			done();
		if(*t==' '&&(t==r||t[-1]==' '))
			t--;
		if(*t=='\n') {
			while(t>r&&t[-1]==' ')
				*--t = '\n';
E 9
I 9
	for (;;)
		switch (*s++) {
		case '\0':
			return (NULL);
		case '\\':
E 9
			break;
I 9
		case ':':
			return (s);
E 9
		}
D 9
	}
	*t = 0;
	return(t-r);
E 9
I 9
	/* NOTREACHED */
E 9
}

D 9
next()
E 9
I 9
char *
D 11
appdstr(s, tp)
E 11
I 11
appdstr(s, tp, len)
E 11
	char *s;
	register char *tp;
I 11
	size_t len;
E 11
E 9
{
D 9
	int flag;
	inc = inc*3125&077777;
	ptr = (inc>>2)%na;
	flag = 0;
	while(score[ptr]>0)
		if(++ptr>=na) {
			ptr = 0;
			if(flag) done();
			flag = 1;
		}
	return(ptr);
E 9
I 9
	register char *mp, *sp;
	register int ch;
	char *m;

D 11
	if ((m = malloc(strlen(sp) + strlen(tp) + 1)) == NULL)
E 11
I 11
	if ((m = malloc(strlen(s) + len + 1)) == NULL)
E 11
		err("%s", strerror(errno));
	for (mp = m, sp = s; *mp++ = *sp++;);

	if (*(mp - 1) == '\\')
		--mp;
	while ((ch = *mp++ = *tp++) && ch != '\n');
	*mp = '\0';

	free(s);
	return (m);
E 9
}

I 7
void
E 7
D 9
done()
E 9
I 9
score(r, w, g)
	u_int r, w, g;
E 9
{
D 3
	printf("\nRights %d, wrongs %d, ", rights, wrongs);
	if(guesses)
		printf("extra guesses %d, ", guesses);
	printf("score %d%%\n",100*rights/(rights+wrongs));
E 3
I 3
D 9
	if (rights + wrongs) {
		printf("\nRights %d, wrongs %d, ", rights, wrongs);
		if (guesses)
			printf("extra guesses %d, ", guesses);
		printf("score %d%%\n",100 * rights / (rights + wrongs));
	}
E 3
	exit(0);
E 9
I 9
	(void)printf("Rights %d, wrongs %d,", r, w);
	if (g)
		(void)printf(" extra guesses %d,", g);
	(void)printf(" score %d%%\n", (r + w + g) ? r * 100 / (r + w + g) : 0);
E 9
}
D 9
instruct(info)
I 7
	char *info;
E 9
I 9

void
downcase(p)
	register char *p;
E 9
E 7
{
D 9
	char *t;
	int i, n;
	printf("Subjects:\n\n");
	while(readline()) {
		printf("-");
		n = segment(line,tmp);
		for(i=1;i<n;i++) {
			printf(" ");
			publish(tmp[i]);
		}
		printf("\n");
	}
	printf("\n");
	input = fopen(info,"r");
	if(input==NULL)
		abort();
	readline();
	segment(line,tmp);
	printf("For example,\n");
	printf("    quiz ");
	publish(tmp[1]);
	printf(" ");
	publish(tmp[2]);
	printf("\nasks you a ");
	publish(tmp[1]);
	printf(" and you answer the ");
	publish(tmp[2]);
	printf("\n    quiz ");
	publish(tmp[2]);
	printf(" ");
	publish(tmp[1]);
	printf("\nworks the other way around\n");
	printf("\nType empty line to get correct answer.\n");
	exit(0);
E 9
I 9
	register int ch;

	for (; ch = *p; ++p)
		if (isascii(ch) && isupper(ch))
			*p = tolower(ch);
E 9
}

D 9
badinfo(){
	printf("Bad info %s\n",line);
E 9
I 9
void
usage()
{
	(void)fprintf(stderr, "quiz [-t] [-i file] category1 category2\n");
	exit(1);
E 9
}

D 9
dunno()
E 9
I 9
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
E 9
{
D 9
	printf("I don't know about that\n");
	exit(0);
E 9
I 9
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "quiz: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
E 9
}
E 1
