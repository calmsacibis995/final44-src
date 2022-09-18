h63991
s 00005/00005/00704
d D 8.1 93/05/31 16:20:24 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00114/00062/00595
d D 5.7 93/05/07 06:38:22 torek 10 9
c lint, prototype, get past -Wall (it all started with lseek...)
e
s 00008/00007/00649
d D 5.6 91/04/08 17:26:15 bostic 9 7
c new copyright; att/bsd/shared
e
s 00008/00007/00649
d R 5.6 91/04/08 17:25:04 bostic 8 7
c new copyright; att/bsd/shared
e
s 00004/00002/00652
d D 5.5 91/02/27 17:37:21 bostic 7 6
c ANSI fix, move log file into /var/games
e
s 00003/00004/00651
d D 5.4 90/04/30 21:48:20 bostic 6 5
c move dictionary to /usr/share/games
e
s 00001/00001/00654
d D 5.3 87/10/22 12:10:54 bostic 5 4
c ANSI C; sprintf now returns an int.
e
s 00001/00001/00654
d D 5.2 87/09/19 14:19:03 bostic 4 3
c move bogdict to /usr/games/lib
e
s 00014/00002/00641
d D 5.1 85/05/30 19:40:43 mckusick 3 2
c Add copyright
e
s 00001/00001/00642
d D 4.2 85/05/13 15:14:58 mckusick 2 1
c fix spelling errors
e
s 00643/00000/00000
d D 4.1 82/12/24 13:07:50 sam 1 0
c date and time created 82/12/24 13:07:50 by sam
e
u
U
t
T
I 3
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 11
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.proprietary.c%
E 9
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif
E 3
I 3
D 11
char copyright[] =
D 9
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1982 The Regents of the University of California.\n\
E 9
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
"%Z% Copyright (c) 1982, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 11
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 3

I 10
#include <sys/types.h>
#include <sys/wait.h>
E 10
#include <ctype.h>
#include <errno.h>
I 10
#include <fcntl.h>
E 10
#include <setjmp.h>
#include <sgtty.h>
#include <signal.h>
#include <stdio.h>
I 10
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
E 10
I 6
#include "pathnames.h"
E 6

/* basic parameters */
#define N 4
#define SSIZE 200
#define MAXWORDS 1000
#define CWIDTH 10
#define LWIDTH 80

/* parameters defined in terms of above */
#define BSIZE (N*N)
#define row(x) (x/N)
#define col(x) (x%N)

/* word being searched for */
int wlength;
int numsame;
char wbuff [BSIZE+1];

/* tty and process control */
extern int errno;
int status;
int pipefd[2];
int super = 0;
int delct = 1;
int zero = 0;
int master = 1;
int column;
int *timept;
int timeint[] = {60,60,50,7,1,1,1,0};
D 10
long timein;
extern long int time();
E 10
I 10
time_t timein;
E 10
struct sgttyb origttyb, tempttyb;
int ctlecho = 0;
int lctlech = LCTLECH;
jmp_buf env;

/* monitoring variables */
int games;
int logfile = -1;
D 10
long logloc;
E 10
I 10
off_t logloc;
E 10
char logbuff[100] = {"inst\t"};
D 10
extern char *ctime(), *getlogin();
extern long lseek();
E 10

/* dictionary interface */
D 4
char defname[] = "/usr/games/bogdict";
E 4
I 4
D 6
char defname[] = "/usr/games/lib/bogdict";
E 4
char *dictname = &defname[0];
E 6
FILE *dict;

/* structures for doing matching */
struct frame {
	struct frame *parent;
	int place;
};
D 10
struct frame stack [SSIZE];
struct frame *level [BSIZE+1];
E 10
I 10
struct frame stack[SSIZE];
struct frame *level[BSIZE+1];
E 10

/* the board and subsidiary structures */
D 10
char present [BSIZE+1];
char board [BSIZE];
char olink [BSIZE];
char adj [BSIZE+1][BSIZE];
char occurs [26];
E 10
I 10
char present[BSIZE+1];
char board[BSIZE];
char olink[BSIZE];
char adj[BSIZE+1][BSIZE];
char occurs[26];
E 10

/* the boggle cubes */
D 10
char *cube [BSIZE] = {
E 10
I 10
char *cube[BSIZE] = {
E 10
	"forixb", "moqabj", "gurilw", "setupl",
	"cmpdae", "acitao", "slcrae", "romash",
	"nodesw", "hefiye", "onudtk", "tevign",
	"anedvz", "pinesh", "abilyt", "gkyleu"
};


/* storage for words found */
int ubotch, ustart, wcount;
D 10
char *word [MAXWORDS];
E 10
I 10
char *word[MAXWORDS];
E 10
char *freesp;
char space[10000];

D 10
endline ()
E 10
I 10
void		aputuword __P((int));
void		aputword __P((int));
void		clearscreen __P((void));
int		compare __P((const void *, const void *));
void		endline __P((void));
int		evalboard __P((int (*)(void), void (*)(int)));
void		genboard __P((void));
int		getdword __P((void));
int		getuword __P((void));
__dead void	goodbye __P((int));
void		interrupt __P((int));
void		makelists __P((void));
int		numways __P((struct frame *, struct frame *));
void		outword __P((char *));
void		printboard __P((void));
void		printdiff __P((void));
void		printinst __P((void));
void		setup __P((void));
void		timeout __P((int));
void		tputword __P((int));
int		wordcomp __P((char *, char *));


void
endline()
E 10
{
	if (column != 0) {
		putchar('\n');
		column = 0;
	}
}

I 7
void
E 7
D 10
timeout ()
E 10
I 10
timeout(sig)
	int sig;
E 10
{
	if (*timept > 0) {
D 10
		signal (SIGALRM, timeout);
E 10
I 10
		signal(SIGALRM, timeout);
E 10
		alarm(*timept++);
	}
	putchar('\007');
}

I 7
void
E 7
D 10
interrupt ()
E 10
I 10
interrupt(sig)
	int sig;
E 10
{
I 10

E 10
	signal(SIGINT, interrupt);
	if (delct++ >= 1)
		longjmp(env, 1);
	timept = &zero;
}

D 10
goodbye (stat)
int stat;
E 10
I 10
__dead void
goodbye(stat)
	int stat;
E 10
{
	if (master != 0) {
		wait(&status);
D 10
		if ( ctlecho & LCTLECH ) {
			ioctl( fileno(stdin), TIOCLBIS, &lctlech );
		}
E 10
I 10
		if (ctlecho & LCTLECH)
			ioctl(fileno(stdin), TIOCLBIS, &lctlech);
E 10
		stty(fileno(stdin), &origttyb);
	}
	exit(stat);
}

D 10
clearscreen ()
E 10
I 10
void
clearscreen()
E 10
{
D 10
	stty (fileno(stdin), &tempttyb);
E 10
I 10
	stty(fileno(stdin), &tempttyb);
E 10
	printf("\n\033\f\r");
}

D 10
compare (a, b)
char **a, **b;
E 10
I 10
int
compare(a, b)
	const void *a, *b;
E 10
{
D 10
	return(wordcomp(*a, *b));
E 10
I 10

	return(wordcomp(*(char **)a, *(char **)b));
E 10
}

D 10
wordcomp (p, q)
register char *p, *q;
E 10
I 10
int
wordcomp(p, q)
	register char *p, *q;
E 10
{
	if (*p=='0' && *q!='0')
		return(-1);
	if (*p!='0' && *q=='0')
		return(1);
	while (*++p == *++q && isalpha(*p)) ;
	if (!isalpha(*p))
		return(-isalpha(*q));
	if (!isalpha(*q))
		return(1);
	return(*p-*q);
}

D 10
printinst ()
E 10
I 10
void
printinst()
E 10
{
D 10
	stty (fileno(stdin), &tempttyb);
E 10
I 10
	stty(fileno(stdin), &tempttyb);
E 10
	printf("instructions?");
	if (getchar() == 'y') {
		clearscreen();
		printf("     The object of Boggle (TM  Parker  Bros.)  is  to  find,  within  3\n");
		printf("minutes,  as many words as possible in a 4 by 4 grid of letters.  Words\n");
		printf("may be formed from any sequence of 3 or more adjacent  letters  in  the\n");
		printf("grid.   The  letters  may join horizontally, vertically, or diagonally.\n");
		printf("However, no position in the grid may be used more than once within  any\n");
		printf("one  word.   In  competitive  play amongst humans, each player is given\n");
		printf("credit for those of his words which no other player has found.\n");
		printf("     This program is intended  for  people  wishing  to  sharpen  their\n");
		printf("skills  at  Boggle.   If  you  invoke the program with 4 arguments of 4\n");
		printf("letters each, (e.g. \"boggle appl epie moth erhd\") the program forms the\n");
		printf("obvious  Boggle grid and lists all the words from /usr/dict/words found\n");
		printf("therein.  If you invoke the program without arguments, it will generate\n");
		printf("a  board  for you, let you enter words for 3 minutes, and then tell you\n");
		printf("how well you did relative to /usr/dict/words.\n");
		printf("     In interactive play, enter your words separated by  spaces,  tabs,\n");
		printf("or  newlines.   A  bell will ring when there is 2:00, 1:00, 0:10, 0:02,\n");
		printf("0:01, and 0:00 time left.  You may complete any word started before the\n");
		printf("expiration  of  time.   You  can surrender before time is up by hitting\n");
		printf("'break'.  While entering words, your erase character is only  effective\n");
		printf("within the current word and your line kill character is ignored.\n");
		printf("     Advanced players may wish to invoke the program with 1 or 2 +'s as\n");
D 2
		printf("the  first argument.  The first + removes the restriction that postions\n");
E 2
I 2
		printf("the  first argument.  The first + removes the restriction that positions\n");
E 2
		printf("can only be used once in each word.  The second + causes a position  to\n");
		printf("be  considered  adjacent  to itself as well as its (up to) 8 neighbors.\n");
		printf("Hit any key to begin.\n");
D 10
		stty (fileno(stdin), &tempttyb);
E 10
I 10
		stty(fileno(stdin), &tempttyb);
E 10
		getchar();
	}
D 10
	stty (fileno(stdin), &tempttyb);
E 10
I 10
	stty(fileno(stdin), &tempttyb);
E 10
}

D 10
setup ()
E 10
I 10
void
setup()
E 10
{
	register int i, j;
	int rd, cd, k;
	for (i=0; i<BSIZE; i++) {
		adj[i][i] = super>=2 ? 1 : 0;
		adj[BSIZE][i] = 1;
		for (j=0; j<i; j++) {
			rd = row(i)-row(j);
			cd = col(i)-col(j);
			k = 0;
			switch (rd) {
			case -1:
			case 1:
				if (-1<=cd && cd<=1)
					k = 1;
				break;
			case 0:
				if (cd==-1 || cd==1)
					k = 1;
				break;
			}
			adj[i][j] = adj[j][i] = k;
		}
	}
	stack[0].parent = &stack[0];
	stack[0].place = BSIZE;
	level[0] = &stack[0];
	level[1] = &stack[1];
}

D 10
makelists ()
E 10
I 10
void
makelists()
E 10
{
	register int i, c;
	for (i=0; i<26; i++)
		occurs[i] = BSIZE;
	for (i=0; i<BSIZE; i++) {
		c = board[i];
		olink[i] = occurs[c-'a'];
		occurs[c-'a'] = i;
	}
}

D 10
genboard ()
E 10
I 10
void
genboard()
E 10
{
	register int i, j;
	for (i=0; i<BSIZE; i++)
		board[i] = 0;
	for (i=0; i<BSIZE; i++) {
		j = rand()%BSIZE;
		while (board[j] != 0)
			j = (j+1)%BSIZE;
		board[j] = cube[i][rand()%6];
	}
}

D 10
printboard ()
E 10
I 10
void
printboard()
E 10
{
	register int i, j;
	for (i=0; i<N; i++) {
		printf("\t\t\t\t\b\b");
		for (j=0; j<N; j++) {
			putchar ((putchar(board[i*N+j]) == 'q') ? 'u' : ' ');
			putchar(' ');
		}
		putchar('\n');
	}
	putchar('\n');
}

D 10
getdword ()
E 10
I 10
int
getdword()
E 10
{
	/* input:  numsame = # chars same as last word   */
	/* output: numsame = # same chars for next word  */
	/*        word in wbuff[0]...wbuff[wlength-1]    */
	register int c;
	register char *p;
	if (numsame == EOF)
		return (0);
	p = &wbuff[numsame]+1;
	while ((*p++ = c = getc(dict)) != EOF && isalpha(c)) ;
	numsame = c;
	wlength = p - &wbuff[2];
	return (1);
}

D 10
getuword ()
E 10
I 10
int
getuword()
E 10
{
	int c;
	register char *p, *q, *r;
	numsame = 0;
	while (*timept>0 && (isspace(c=getchar()) || c==EOF));
	if (*timept == 0)
		return(0);
	word[wcount++] = freesp;
	*freesp++ = '0';
	r = &wbuff[1];
	q = p = freesp;
	*p++ = c;
	while (!isspace(c = getchar())) {
		if (c == EOF)
			continue;
		if (c == origttyb.sg_erase) {
			if (p > q)
				p--;
			continue;
		}
		*p++ = c;
	}
	freesp = p;
	for (p=q; p<freesp && r<&wbuff[BSIZE]; )
		if (islower(c = *p++) && (*r++ = *q++ = c) == 'q' && *p == 'u')
			p++;
	*(freesp = q) = '0';
	wlength = r-&wbuff[1];
	return(1);
}

D 10
aputuword (ways)
int ways;
E 10
I 10
void
aputuword(ways)
	int ways;
E 10
{
	*word[wcount-1] = ways>=10 ? '*' : '0'+ways;
}

D 10
aputword (ways)
int ways;
E 10
I 10
void
aputword(ways)
	int ways;
E 10
{
	/* store (wbuff, ways) in next slot in space */
	register int i;
	*freesp++ = ways>=10 ? '*' : '0'+ways;
	for (i=1; i<= wlength; i++)
		*freesp++ = wbuff[i];
	word[++wcount] = freesp;
}

D 10
tputword (ways)
int ways;
E 10
I 10
void
tputword(ways)
	int ways;
E 10
{
	/* print (wbuff, ways) on terminal */
	wbuff[wlength+1] = '0';
	wbuff[0] = ways>=10 ? '*' : '0'+ways;
	outword(&wbuff[0]);
}

D 10
outword (p)
register char *p;
E 10
I 10
void
outword(p)
	register char *p;
E 10
{
	register int newcol;
	register char *q;
	for (q=p+1; isalpha(*q); ) {
		putchar(*q);
		if (*q++ == 'q') {
			putchar('u');
			column++;
		}
	}
	column += q-p-1;
	if (column > LWIDTH-CWIDTH) {
		putchar('\n');
		column = 0;
		return;
	}
	newcol = ((column+CWIDTH)/CWIDTH)*CWIDTH;
	while (((column+8)/8)*8 <= newcol) {
		putchar('\t');
		column = ((column+8)/8)*8;
	}
	while (column < newcol) {
		putchar(' ');
		column++;
	}
}

D 10
printdiff ()
E 10
I 10
void
printdiff()
E 10
{
	register int c, d, u;
	char both, donly, uonly;
	word[wcount] = freesp;
	*freesp = '0';
	both = donly = uonly = column = d = 0;
	u = ustart;
	while (d < ubotch) {
		c = u<wcount ? wordcomp (word[d], word[u]) : -1;
		if (c == 0) {
			/* dict and user found same word */
			if (both == 0) {
				both = 1;
				printf("\t\t\t   we both found:\n");
			}
			outword(word[d]);
			word[d++] = NULL;
			word[u++] = NULL;
		} else if (c < 0) {
			/* dict found it, user didn't */
			donly = 1;
			d++;
		} else {
			/* user found it, dict didn't */
			uonly = 1;
			u++;
		}
	}
	endline();
	if (donly) {
		printf("\n\t\t\tI alone found these:\n");
		for (d=0; d<ubotch; d++)
			if (word[d] != NULL)
				outword(word[d]);
		endline();
	}
	if (uonly) {
		printf("\n\t\t\tyou alone found these:\n");
		for (u=ustart; u<wcount; u++)
			if (word[u] != NULL)
				outword(word[u]);
		endline();
	}
	if (ubotch < ustart) {
		printf("\n\t\t\t  you botched these:\n");
		for (u=ubotch; u<ustart; u++)
			outword(word[u]);
		endline();
	}
}

D 10
numways (leaf, last)
register struct frame *leaf;
struct frame *last;
E 10
I 10
int
numways(leaf, last)
	register struct frame *leaf;
	struct frame *last;
E 10
{
	int count;
	register char *p;
	register struct frame *node;
	if (super > 0)
		return(last-leaf);
	count = 0;
	present[BSIZE] = 1;
	while (leaf < last) {
		for (p = &present[0]; p < &present[BSIZE]; *p++ = 0);
		for (node = leaf; present[node->place]++ == 0; node = node->parent);
		if (node == &stack[0])
			count++;
		leaf++;
	}
	return(count);
}

I 10
int
E 10
evalboard (getword, putword)
D 10
int (*getword)(), (*putword)();
E 10
I 10
	int (*getword) __P((void));
	void (*putword) __P((int));
E 10
{
	register struct frame *top;
	register int l, q;
	int fo, found;
	struct frame *parent, *lastparent;
	char *padj;

	numsame = found = 0;
	makelists ();

	while (1) {
		l = numsame;
		if (!(*getword) ())
			break;
		top = level[l+1];
	
		while (1) {
			level[l+1] = lastparent = top;
			/* wbuff[1]...wbuff[l] have been matched */
			/* level[0],...,level[l] of tree built */
			if (l == wlength) {
				if (wlength >= 3 && (q = numways(level[l], top)) != 0) {
					(*putword) (q);
					found++;
				}
				l = BSIZE+1;
				break;
			}
			if ((fo = occurs[wbuff[++l]-'a']) == BSIZE)
				break;
			/* wbuff[1]...wbuff[l-1] have been matched */
			/* level[0],...,level[l-1] of tree built */
			for (parent=level[l-1]; parent<lastparent; parent++) {
				padj = &adj[parent->place][0];
				for (q=fo; q!=BSIZE; q=olink[q])
					if (padj[q]) {
						top->parent = parent;
						top->place = q;
						if (++top >= &stack[SSIZE]) {
							printf("stack overflow\n");
							goodbye(1);
						}
					}
			}
			/* were any nodes added? */
			if (top == lastparent)
				break;
		}

		/* advance until first l characters of next word are different */
		while (numsame >= l && (*getword)()) ;
	}
	return(found);
}

D 10
main (argc, argv)
int argc;
char **argv;
E 10
I 10
int
main(argc, argv)
	int argc;
	char **argv;
E 10
{
	char *q;
	register char *p;
	register int i, c;

D 10
	gtty (fileno(stdin), &origttyb);
E 10
I 10
	gtty(fileno(stdin), &origttyb);
E 10
	setbuf(stdin, NULL);
	tempttyb = origttyb;
	if (setjmp(env) != 0)
		goodbye(0);
D 10
	signal (SIGINT, interrupt);
E 10
I 10
	signal(SIGINT, interrupt);
E 10
D 7
	timein = time(0L);
	if (argv[0][0] != 'a' && (logfile = open("/usr/games/boglog", 1)) >= 0) {
E 7
I 7
	timein = time((time_t *)NULL);
D 10
	if (argv[0][0] != 'a' && (logfile = open(_PATH_BOGLOG, 1)) >= 0) {
E 10
I 10
	if (argv[0][0] != 'a' &&
	    (logfile = open(_PATH_BOGLOG, O_WRONLY, 0)) >= 0) {
E 10
E 7
		p = &logbuff[5];
		q = getlogin();
D 10
		while (*p++ = *q++);
E 10
I 10
		while ((*p++ = *q++) != 0);
E 10
		p[-1] = '\t';
		q = ctime(&timein);
D 10
		while (*p++ = *q++);
E 10
I 10
		while ((*p++ = *q++) != 0);
E 10
		logloc = lseek(logfile, 0L, 2);
		write(logfile, &logbuff[0], p-&logbuff[1]);
	}
D 6
	if ((dict = fopen(dictname, "r")) == NULL) {
		printf("can't open %s\n", dictname);
E 6
I 6
	if ((dict = fopen(_PATH_DICTIONARY, "r")) == NULL) {
		printf("can't open %s\n", _PATH_DICTIONARY);
E 6
		goodbye (2);
	}
	while ( argc > 1 && ( argv[1][0] == '+' || argv[1][0] == '-' ) ) {
		if (argv[1][0]=='+') {
			while(*(argv[1]++) == '+')
				super++;
			argc--;
			argv++;
		}
		if ( argv[1][0] == '-' ) {
			timeint[0] = 60 * ( atol( &argv[1][1] ) - 2 );
			if ( timeint[0] <= 0 ) {
				timeint[0] = 60;
			}
			argc--;
			argv++;
		}
	}
	setup ();
	switch (argc) {
	default:  punt:
		printf("usage: boggle [+[+]] [row1 row2 row3 row4]\n");
		goodbye (3);
	case 5:
		for (i=0; i<BSIZE; i++) {
			board[i] = c = argv[row(i)+1][col(i)];
			if (!islower(c)) {
				printf("bad board\n");
				goto punt;
			}
		}
		printboard();
		column = 0;
		evalboard(getdword, tputword);
		endline();
		if (logfile >= 0) {
			strncpy(&logbuff[0], "eval", 4);
			lseek(logfile, logloc, 0);
			write(logfile, &logbuff[0], 4);
		}
		goodbye(0);
	case 1:
		tempttyb.sg_flags |= CBREAK;
		if ( ioctl( fileno(stdin), TIOCLGET, &ctlecho ) == 0 ) {
			if ( ctlecho & LCTLECH ) {
				ioctl( fileno(stdin), TIOCLBIC, &lctlech );
			}
		}
		printinst();
		srand((int) timein);
		while (setjmp(env) == 0) {
			errno = 0;
			if (pipe(&pipefd[0]) != 0) {
				printf("can't create pipe\n");
				goodbye(4);
			}
			genboard();
			delct = wcount = 0;
			word[0] = freesp = &space[0];
			if ((master = fork()) == 0) {
				close(pipefd[0]);
				clearscreen();
				printboard();
				signal(SIGALRM, timeout);
				timept = &timeint[0];
				alarm(*timept++);
				evalboard(getuword, aputuword);
				clearscreen();
D 10
				qsort(&word[0], wcount, sizeof (int), compare);
E 10
I 10
				qsort(&word[0], wcount, sizeof(int), compare);
E 10
				for (i=0; i<wcount; i++)
					if (i==0 || wordcomp(word[i], word[i-1])!=0) {
						p = word[i];
						while (isalpha(*++p)) ;
						write (pipefd[1], word[i], p-word[i]);
					}
				close(pipefd[1]);
				goodbye(0);
			}
			close(pipefd[1]);
			rewind(dict);
			getc(dict);
			evalboard(getdword, aputword);
			p = freesp;
			while ((i = read(pipefd[0], freesp, 512)) != 0) {
				if (i < 0)
					if (errno != EINTR)
						break;
					else
						i = 0;
				freesp += i;
			}
			close(pipefd[0]);
			ustart = ubotch = wcount;
			while (p < freesp) {
				word[wcount++] = p;
				if (*p == '0')
					ustart = wcount;
				while (isalpha(*++p));
			}
			wait(&status);
			if (status != 0)
				goodbye (5);
			delct = 1;
			printdiff();
			printboard();
			games++;
			if (logfile >= 0) {
D 5
				sprintf(&logbuff[0], "%4d", games);
E 5
I 5
				(void)sprintf(&logbuff[0], "%4d", games);
E 5
				lseek(logfile, logloc, 0);
				write(logfile, &logbuff[0], 4);
			}
			stty (fileno(stdin), &tempttyb);
			printf("\nanother game?");
			if (getchar() != 'y') {
				putchar('\n');
				break;
			}
			stty (fileno(stdin), &tempttyb);
		}
		goodbye(0);
	}
}
E 1
