h64252
s 00006/00002/00364
d D 4.3 91/04/18 16:44:06 bostic 3 2
c new copyright; att/bsd/shared
e
s 00005/00004/00361
d D 4.2 85/01/09 15:51:52 ralph 2 1
c fix type warnings
e
s 00365/00000/00000
d D 4.1 83/05/06 23:47:12 tut 1 0
c date and time created 83/05/06 23:47:12 by tut
e
u
U
t
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include <stdio.h>
#include <ctype.h>
/*
 * fgrep -- print all lines containing any of a set of keywords
 *
 *	status returns:
 *		0 - ok, and some matches
 *		1 - ok, but no matches
 *		2 - some error
 */
#define	MAXSIZ 700
#define QSIZE 400
struct words {
	char 	inp;
	char	out;
	struct	words *nst;
	struct	words *link;
	struct	words *fail;
} 
*www, *smax, *q;

char	buf[2*BUFSIZ];
int	nsucc;
int	need;
char	*instr;
int	inct;
int	rflag;
int	xargc;
char	**xargv;
int	numwords;
int	nfound;
static int flag = 0;

fgrep(argc, argv)
char **argv;
{
D 2
	instr = nsucc = need = inct = rflag = numwords = nfound = 0;
E 2
I 2
	nsucc = need = inct = rflag = numwords = nfound = 0;
	instr = 0;
E 2
	flag = 0;
	if (www==0)
D 2
		www = zalloc(MAXSIZ, sizeof (*www));
E 2
I 2
		www = (struct words *) zalloc(MAXSIZ, sizeof (*www));
E 2
	if (www==NULL)
		err("Can't get space for machines", 0);
	for (q=www; q<www+MAXSIZ; q++) {
		q->inp =0; q->out =0; q->nst =0; q->link =0; q->fail =0;
	}
	xargc = argc-1;
	xargv = argv+1;
	while (xargc>0 && xargv[0][0]=='-')
		{
		switch(xargv[0][1])
			{
			case 'r': /* return value only */
				rflag++;
				break;
			case 'n': /* number of answers needed */
D 2
				need = xargv[1];
E 2
I 2
				need = (int) xargv[1];
E 2
				xargv++; xargc--;
				break;
			case 'i':
				instr = xargv[1];
D 2
				inct = xargv[2]+2;
E 2
I 2
				inct = (int) xargv[2]+2;
E 2
# if D2
fprintf(stderr,"inct %d xargv.2. %o %d\n",inct, xargv[2],xargv[2]);
# endif
				xargv += 2; xargc -= 2;
				break;
			}
		xargv++; xargc--;
		}
	if (xargc<=0)
		{
		write (2, "bad fgrep call\n", 15);
		exit(2);
		}
# if D1
	fprintf(stderr, "before cgoto\n");
# endif
	cgotofn();
# if D1
	fprintf(stderr, "before cfail\n");
# endif
	cfail();
# if D1
	fprintf(stderr, "before execute instr %.20s\n", instr? instr: "");
	fprintf(stderr, "end of string %d %c %c %c\n", inct, instr[inct-3],
		instr[inct-2], instr[inct-1]);
# endif
	execute();
# if D1
	fprintf(stderr, "returning nsucc %d\n", nsucc);
	fprintf(stderr, "fgrep done www %o\n",www);
# endif
	return(nsucc == 0);
}

execute()
{
	register char *p;
	register struct words *c;
	register ch;
	register ccount;
	int f;
	char *nlp;
	f=0;
	ccount = instr ? inct : 0;
	nfound=0;
	p = instr ? instr : buf;
	if (need == 0) need = numwords;
	nlp = p;
	c = www;
# if D2
fprintf(stderr, "in execute ccount %d inct %d\n",ccount, inct );
# endif
	for (;;) {
# if D3
fprintf(stderr, "down ccount\n");
# endif
		if (--ccount <= 0) {
# if D2
fprintf(stderr, "ex loop ccount %d instr %o\n",ccount, instr);
# endif
			if (instr) break;
			if (p == &buf[2*BUFSIZ]) p = buf;
			if (p > &buf[BUFSIZ]) {
				if ((ccount = read(f, p, &buf[2*BUFSIZ] - p)) <= 0) break;
			}
			else if ((ccount = read(f, p, BUFSIZ)) <= 0) break;
# if D2
fprintf(stderr, " normal read %d bytres\n", ccount);
{char xx[20]; sprintf(xx, "they are %%.%ds\n", ccount);
fprintf(stderr, xx, p);
}
# endif
		}
nstate:
		ch = *p;
# if D2
fprintf(stderr, "roaming along in ex ch %c c %o\n",ch,c);
# endif
		if (isupper(ch)) ch |= 040;
		if (c->inp == ch) {
			c = c->nst;
		}
		else if (c->link != 0) {
			c = c->link;
			goto nstate;
		}
		else {
			c = c->fail;
			if (c==0) {
				c = www;
istate:
				if (c->inp == ch) {
					c = c->nst;
				}
				else if (c->link != 0) {
					c = c->link;
					goto istate;
				}
			}
			else goto nstate;
		}
		if (c->out && new (c)) {
# if D2
fprintf(stderr, " found: nfound %d need %d\n",nfound,need);
# endif
			if (++nfound >= need)
			{
# if D1
fprintf(stderr, "found, p %o nlp %o ccount %d buf %o buf[2*BUFSIZ] %o\n",p,nlp,ccount,buf,buf+2*BUFSIZ);
# endif
				if (instr==0)
				while (*p++ != '\n') {
# if D3
fprintf(stderr, "down ccount2\n");
# endif
					if (--ccount <= 0) {
						if (p == &buf[2*BUFSIZ]) p = buf;
						if (p > &buf[BUFSIZ]) {
							if ((ccount = read(f, p, &buf[2*BUFSIZ] - p)) <= 0) break;
						}
						else if ((ccount = read(f, p, BUFSIZ)) <= 0) break;
# if D2
fprintf(stderr, " read %d bytes\n",ccount);
{ char xx[20]; sprintf(xx, "they are %%.%ds\n", ccount);
fprintf(stderr, xx, p);
}
# endif
					}
				}
				nsucc = 1;
				if (rflag==0)
					{
# if D2
fprintf(stderr, "p %o nlp %o buf %o\n",p,nlp,buf);
if (p>nlp)
{write (2, "XX\n", 3); write (2, nlp, p-nlp); write (2, "XX\n", 3);}
# endif
					if (p > nlp) write(1, nlp, p-nlp);
					else {
						write(1, nlp, &buf[2*BUFSIZ] - nlp);
						write(1, buf, p-&buf[0]);
						}
					if (p[-1]!= '\n') write (1, "\n", 1);
					}
				if (instr==0)
					{
					nlp = p;
					c = www;
					nfound=0; 
					}
			}
			else
				ccount++;
			continue;
		}
# if D2
fprintf(stderr, "nr end loop p %o\n",p);
# endif
		if (instr)
			p++;
		else
		if (*p++ == '\n')
		{
			nlp = p;
			c = www;
			nfound=0;
		}
	}
	if (instr==0)
		close(f);
}

cgotofn() {
	register c;
	register struct words *s;
	s = smax = www;
nword:	
	for(;;) {
# if D1
	fprintf(stderr, " in for loop c now %o %c\n",c, c>' ' ? c : ' ');
# endif
		if ((c = gch())==0) return;
		else if (c == '\n') {
			s->out = 1;
			s = www;
		}
		else {
loop:	
			if (s->inp == c) {
				s = s->nst;
				continue;
			}
			if (s->inp == 0) goto enter;
			if (s->link == 0) {
				if (smax >= &www[MAXSIZ - 1]) overflo();
				s->link = ++smax;
				s = smax;
				goto enter;
			}
			s = s->link;
			goto loop;
		}
	}

enter:
	do {
		s->inp = c;
		if (smax >= &www[MAXSIZ - 1]) overflo();
		s->nst = ++smax;
		s = smax;
	} 
	while ((c = gch()) != '\n');
	smax->out = 1;
	s = www;
	numwords++;
	goto nword;

}

gch()
{
	static char *s;
	if (flag==0)
	{
		flag=1;
		s = *xargv++;
# if D1
	fprintf(stderr, "next arg is %s xargc %d\n",s,xargc);
# endif
		if (xargc-- <=0) return(0);
	}
	if (*s) return(*s++);
	for(flag=0; flag<2*BUFSIZ; flag++)
		buf[flag]=0;
	flag=0;
	return('\n');
}

overflo() {
	write(2,"wordlist too large\n", 19);
	exit(2);
}
cfail() {
	struct words *queue[QSIZE];
	struct words **front, **rear;
	struct words *state;
	register char c;
	register struct words *s;
	s = www;
	front = rear = queue;
init:	
	if ((s->inp) != 0) {
		*rear++ = s->nst;
		if (rear >= &queue[QSIZE - 1]) overflo();
	}
	if ((s = s->link) != 0) {
		goto init;
	}

	while (rear!=front) {
		s = *front;
		if (front == &queue[QSIZE-1])
			front = queue;
		else front++;
cloop:	
		if ((c = s->inp) != 0) {
			*rear = (q = s->nst);
			if (front < rear)
				if (rear >= &queue[QSIZE-1])
					if (front == queue) overflo();
					else rear = queue;
			else rear++;
			else
				if (++rear == front) overflo();
			state = s->fail;
floop:	
			if (state == 0) state = www;
			if (state->inp == c) {
				q->fail = state->nst;
				if ((state->nst)->out == 1) q->out = 1;
				continue;
			}
			else if ((state = state->link) != 0)
				goto floop;
		}
		if ((s = s->link) != 0)
			goto cloop;
	}
}

static int seen[50];
new (x)
{
	int i;
	for(i=0; i<nfound; i++)
		if (seen[i]==x)
			return(0);
	seen[i]=x;
	return(1);
}
E 1
