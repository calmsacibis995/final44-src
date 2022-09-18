h21867
s 00005/00005/00398
d D 8.1 93/05/31 16:53:30 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00402
d D 5.4 91/01/18 23:24:24 bostic 5 4
c extra newline makes it more readable
e
s 00331/00431/00072
d D 5.3 91/01/18 23:17:20 bostic 4 3
c new version
e
s 00001/00007/00502
d D 5.2 89/11/30 11:26:50 bostic 3 2
c reversed arguments in mark() drops core; other lint
e
s 00014/00001/00495
d D 5.1 85/05/29 11:21:38 dist 2 1
c Add copyright
e
s 00496/00000/00000
d D 4.1 82/10/24 18:26:18 mckusick 1 0
c date and time created 82/10/24 18:26:18 by mckusick
e
u
U
t
T
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Muffy Barkocy.
 *
 * %sccs.include.redist.c%
E 4
 */
E 2
I 1

D 2
static char sccsid[] = "	%M%	%I%	%E%	";
E 2
I 2
#ifndef lint
D 6
char copyright[] =
D 4
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 4
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 2

D 4
# include <stdio.h>
E 4
I 4
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathnames.h"
E 4

D 4
/*	Through, `my' refers to the program, `your' to the player */
E 4
I 4
#define	RANKS		13
#define	HANDSIZE	7
#define	CARDS		4
E 4

D 4
# define CTYPE 13
# define CTSIZ (CTYPE+1)
# define DECK 52
# define NOMORE 0
# define DOUBTIT (-1);
E 4
I 4
#define	USER		1
#define	COMPUTER	0
#define	OTHER(a)	(1 - (a))
E 4

D 4
typedef char HAND[CTSIZ];
E 4
I 4
char *cards[] = {
	"A", "2", "3", "4", "5", "6", "7",
	"8", "9", "10", "J", "Q", "K", NULL,
};
#define	PRC(card)	(void)printf(" %s", cards[card])
E 4

D 4
/* data structures */
E 4
I 4
int promode;
int asked[RANKS], comphand[RANKS], deck[RANKS];
int userasked[RANKS], userhand[RANKS];
E 4

D 4
short debug;
E 4
I 4
main(argc, argv)
	int argc;
	char **argv;
{
	int ch, move;
E 4

D 4
HAND myhand;
HAND yourhand;
char deck[DECK];
short nextcd;
int proflag;

/* utility and output programs */

shuffle(){
	/* shuffle the deck, and reset nextcd */
	/* uses the random number generator `rand' in the C library */
	/* assumes that `srand' has already been called */

	register i;

	for( i=0; i<DECK; ++i ) deck[i] = (i%13)+1;  /* seed the deck */

	for( i=DECK; i>0; --i ){ /* select the next card at random */
		deck[i-1] = choose( deck, i );
E 4
I 4
	while ((ch = getopt(argc, argv, "p")) != EOF)
		switch(ch) {
		case 'p':
			promode = 1;
			break;
		case '?':
		default:
			(void)fprintf(stderr, "usage: fish [-p]\n");
			exit(1);
E 4
		}

D 4
	nextcd = 0;
	}
E 4
I 4
	srandom(time((time_t *)NULL));
	instructions();
	init();
E 4

D 4
choose( a, n ) char a[]; {
	/* pick and return one at random from the n choices in a */
	/* The last one is moved to replace the one chosen */
	register j, t;

	if( n <= 0 ) error( "null choice" );

	j = rand() % n;
	t = a[j];
	a[j] = a[n-1];
	return(t);
E 4
I 4
	if (nrandom(2) == 1) {
		printplayer(COMPUTER);
		(void)printf("get to start.\n");
		goto istart;
E 4
	}
D 4

draw() {
	if( nextcd >= DECK ) return( NOMORE );
	return( deck[nextcd++] );
	}

error( s ) char *s; {
	fprintf( stderr, "error: " );
	fprintf( stderr, s );
	exit( 1 );
	}

empty( h ) HAND h; {
	register i;

	for( i=1; i<=CTYPE; ++i ){
		if( h[i] != 0 && h[i] != 4 ) return( 0 );
E 4
I 4
	printplayer(USER);
	(void)printf("get to start.\n");
	
	for (;;) {
		move = usermove();
		if (!comphand[move]) {
			if (gofish(move, USER, userhand))
				continue;
		} else {
			goodmove(USER, move, userhand, comphand);
			continue;
E 4
		}
D 4
	return( i );
	}
E 4

D 3
mark( cd, hand ) HAND hand; {
E 3
I 3
D 4
mark( hand, cd ) HAND hand; {
E 3
	if( cd != NOMORE ){
		++hand[cd];
		if( hand[cd] > 4 ){
			error( "mark overflow" );
			}
E 4
I 4
istart:		for (;;) {
			move = compmove();
			if (!userhand[move]) {
				if (!gofish(move, COMPUTER, comphand))
					break;
			} else
				goodmove(COMPUTER, move, comphand, userhand);
E 4
		}
D 4
	return( cd );
E 4
	}
I 4
	/* NOTREACHED */
}
E 4

D 4
deal( hand, n ) HAND hand; {
	while( n-- ){
		if( mark( hand, draw() ) == NOMORE ) error( "deck exhausted" );
		}
	}
E 4
I 4
usermove()
{
	register int n;
	register char **p;
	char buf[256];
E 4

D 4
char *cname[] = {
	"NOMORE!!!",
	"A",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"J",
	"Q",
	"K",
	};
E 4
I 4
D 5
	(void)printf("Your hand is:");
E 5
I 5
	(void)printf("\nYour hand is:");
E 5
	printhand(userhand);
E 4

D 4
stats(){
	register i, ct, b;

	if( proflag ) printf( "Pro level\n" );
	b = ct = 0;

	for( i=1; i<=CTYPE; ++i ){
		if( myhand[i] == 4 ) ++b;
		else ct += myhand[i];
E 4
I 4
	for (;;) {
		(void)printf("You ask me for: ");
		(void)fflush(stdout);
		if (fgets(buf, BUFSIZ, stdin) == NULL)
			exit(0);
		if (buf[0] == '\0')
			continue;
		if (buf[0] == '\n') {
			(void)printf("%d cards in my hand, %d in the pool.\n",
			    countcards(comphand), countcards(deck));
			(void)printf("My books:");
			(void)countbooks(comphand);
			continue;
E 4
		}
D 4

	if( b ){
		printf( "My books: " );
		for( i=1; i<=CTYPE; ++i ){
			if( myhand[i] == 4 ) printf( "%s ", cname[i] );
			}
		printf( "\n" );
E 4
I 4
		buf[strlen(buf) - 1] = '\0';
		if (!strcasecmp(buf, "p") && !promode) {
			promode = 1;
			(void)printf("Entering pro mode.\n");
			continue;
E 4
		}
D 4

	printf( "%d cards in my hand, %d in the pool\n", ct, DECK-nextcd );
	printf( "You ask me for: " );
	}

phand( h ) HAND h; {
	register i, j;

	j = 0;

	for( i = 1; i<= CTYPE; ++i ){
		if( h[i] == 4 ) {
			++j;
E 4
I 4
		if (!strcasecmp(buf, "quit"))
			exit(0);
		for (p = cards; *p; ++p)
			if (!strcasecmp(*p, buf))
				break;
		if (!*p) {
			(void)printf("I don't understand!\n");
E 4
			continue;
D 4
			}
		if( h[i] ){
			register k;
			k = h[i];
			while( k-- ) printf( "%s ", cname[i] );
			}
E 4
		}
D 4

	if( j ){
		printf( "+ Books of " );
		for( i=1; i<=CTYPE; ++i ){
			if( h[i] == 4 ) printf( "%s ", cname[i] );
			}
E 4
I 4
		n = p - cards;
		if (userhand[n]) {
			userasked[n] = 1;
			return(n);
E 4
		}
D 4

	printf( "\n" );
E 4
I 4
		if (nrandom(3) == 1)
			(void)printf("You don't have any of those!\n");
		else
			(void)printf("You don't have any %s's!\n", cards[n]);
		if (nrandom(4) == 1)
			(void)printf("No cheating!\n");
		(void)printf("Guess again.\n");
E 4
	}
I 4
	/* NOTREACHED */
}
E 4

D 4
main( argc, argv ) char * argv[]; { 
	/* initialize shuffling, ask for instructions, play game, die */
	register c;
E 4
I 4
compmove()
{
	static int lmove;
E 4

D 4
	if( argc > 1 && argv[1][0] == '-' ){
		while( argv[1][0] == '-' ) { ++argv[1]; ++debug; }
		argv++;
		argc--;
		}

	srand( getpid() );

	printf( "instructions?\n" );
	if( (c=getchar()) != '\n' ){
		if( c != 'n' ) instruct();
		while( getchar() != '\n' );
		}

	game();
E 4
I 4
	if (promode)
		lmove = promove();
	else {
		do {
			lmove = (lmove + 1) % RANKS;
		} while (!comphand[lmove] || comphand[lmove] == CARDS);
E 4
	}
I 4
	asked[lmove] = 1;
E 4

D 4
/*	print instructions */
E 4
I 4
	(void)printf("I ask you for: %s.\n", cards[lmove]);
	return(lmove);
}
E 4

D 4
char *inst[] = {
	"`Go Fish' is a childrens' card game.  The Object is to",
	"accumulate `books' of 4 cards with the same face value.  The",
	"players alternate turns; each turn begins with one player",
	"selecting a card from his hand, and asking the other player for",
	"all cards of that face value.  If the other player has one or",
	"more cards of that face value in his hand, he gives them to the",
	"first player, and the first player makes another request.",
	"Eventually, the first player asks for a card which is not in",
	"the second player's hand: he replies `GO FISH!' The first",
	"player then draws a card from the `pool' of undealt cards.  If",
	"this is the card he had last requested, he draws again.  When a",
	"book is made, either through drawing or requesting, the cards",
	"are laid down and no further action takes place with that face",
	"value.  To play the computer, simply make guesses by typing a,",
	"2, 3, 4, 5, 6, 7, 8, 9, 10, j, q, or k when asked.  Hitting",
	"return gives you information about the size of my hand and the",
	"pool, and tells you about my books.  Saying `p' as a first",
	"guess puts you into `pro' level; The default is pretty dumb!",
	"Good Luck!\n",
	"",
	};
E 4
I 4
promove()
{
	register int i, max;
E 4

D 4
instruct(){
	register char **cpp;

	printf( "\n" );

	for( cpp = inst; **cpp != '\0'; ++cpp ){
		printf( "%s\n", *cpp );
E 4
I 4
	for (i = 0; i < RANKS; ++i)
		if (userasked[i] &&
		    comphand[i] > 0 && comphand[i] < CARDS) {
			userasked[i] = 0;
			return(i);
E 4
		}
I 4
	if (nrandom(3) == 1) {
		for (i = 0;; ++i)
			if (comphand[i] && comphand[i] != CARDS) {
				max = i;
				break;
			}
		while (++i < RANKS) 
			if (comphand[i] != CARDS &&
			    comphand[i] > comphand[max])
				max = i;
		return(max);
	} 
	if (nrandom(1024) == 0723) {
		for (i = 0; i < RANKS; ++i)
			if (userhand[i] && comphand[i])
				return(i);
E 4
	}
I 4
	for (;;) {
		for (i = 0; i < RANKS; ++i)
			if (comphand[i] && comphand[i] != CARDS &&
			    !asked[i])
				return(i);
		for (i = 0; i < RANKS; ++i)
			asked[i] = 0;
	}
	/* NOTREACHED */
}
E 4

D 4
game(){
E 4
I 4
drawcard(player, hand)
	int player;
	int *hand;
{
	int card;
E 4

D 4
	shuffle();

	deal( myhand, 7 );
	deal( yourhand, 7 );

D 3
	start( myhand );

E 3
	for(;;){

		register g;


		/* you make repeated guesses */

		for(;;) {
			printf( "your hand is: " );
			phand( yourhand );
			printf( "you ask me for: " );
			if( !move( yourhand, myhand, g=guess(), 0 ) ) break;
			printf( "Guess again\n" );
			}

		/* I make repeated guesses */

		for(;;) {
			if( (g=myguess()) != NOMORE ){
				printf( "I ask you for: %s\n", cname[g] );
				}
			if( !move( myhand, yourhand, g, 1 ) ) break;
			printf( "I get another guess\n" );
			}
		}
E 4
I 4
	while (deck[card = nrandom(RANKS)] == 0);
	++hand[card];
	--deck[card];
	if (player == USER || hand[card] == CARDS) {
		printplayer(player);
		(void)printf("drew %s", cards[card]);
		if (hand[card] == CARDS) {
			(void)printf(" and made a book of %s's!\n",
			     cards[card]);
			chkwinner(player, hand);
		} else
			(void)printf(".\n");
E 4
	}
I 4
	return(card);
}
E 4

D 4
/*	reflect the effect of a move on the hands */

move( hs, ht, g, v ) HAND hs, ht; {
	/* hand hs has made a guess, g, directed towards ht */
	/* v on indicates that the guess was made by the machine */
	register d;
	char *sp, *tp;

	sp = tp = "I";
	if( v ) tp = "You";
	else sp = "You";

	if( g == NOMORE ){
		d = draw();
		if( d == NOMORE ) score();
		else {

			printf( "Empty Hand\n" );
			if( !v ) printf( "You draw %s\n", cname[d] );
			mark( hs, d );
			}
		return( 0 );
		}

	if( !v ) heguessed( g );

	if( hs[g] == 0 ){
		if( v ) error( "Rotten Guess" );
		printf( "You don't have any %s's\n", cname[g] );
E 4
I 4
gofish(askedfor, player, hand)
	int askedfor, player;
	int *hand;
{
	printplayer(OTHER(player));
	(void)printf("say \"GO FISH!\"\n");
	if (askedfor == drawcard(player, hand)) {
		printplayer(player);
		(void)printf("drew the guess!\n");
		printplayer(player);
		(void)printf("get to ask again!\n");
E 4
		return(1);
D 4
		}
E 4
I 4
	}
	return(0);
}
E 4

D 4
	if( ht[g] ){ /* successful guess */
		printf( "%s have %d %s%s\n", tp, ht[g], cname[g], ht[g]>1?"'s":"" );
		hs[g] += ht[g];
		ht[g] = 0;
		if( hs[g] == 4 ) madebook(g);
		return(1);
		}
E 4
I 4
goodmove(player, move, hand, opphand)
	int player, move;
	int *hand, *opphand;
{
	printplayer(OTHER(player));
	(void)printf("have %d %s%s.\n",
	    opphand[move], cards[move], opphand[move] == 1 ? "": "'s");
E 4

D 4
	/* GO FISH! */
E 4
I 4
	hand[move] += opphand[move];
	opphand[move] = 0;
E 4

D 4
	printf( "%s say \"GO FISH!\"\n", tp );

	newdraw:
	d = draw();
	if( d == NOMORE ) {
		printf( "No more cards\n" );
		return(0);
		}
	mark( hs, d );
	if( !v ) printf( "You draw %s\n", cname[d] );
	if( hs[d] == 4 ) madebook(d);
	if( d == g ){
		printf( "%s drew the guess, so draw again\n", sp );
		if( !v ) hedrew( d );
		goto newdraw;
		}
	return( 0 );
E 4
I 4
	if (hand[move] == CARDS) {
		printplayer(player);
		(void)printf("made a book of %s's!\n", cards[move]);
		chkwinner(player, hand);
E 4
	}

D 4
madebook( x ){
	printf( "Made a book of %s's\n", cname[x] );
	}
E 4
I 4
	chkwinner(OTHER(player), opphand);
E 4

D 4
score(){
	register my, your, i;
E 4
I 4
	printplayer(player);
	(void)printf("get another guess!\n");
}
E 4

D 4
	my = your = 0;
E 4
I 4
chkwinner(player, hand)
	int player;
	register int *hand;
{
	register int cb, i, ub;
E 4

D 4
	printf( "The game is over.\nMy books: " );
E 4
I 4
	for (i = 0; i < RANKS; ++i)
		if (hand[i] > 0 && hand[i] < CARDS)
			return;
	printplayer(player);
	(void)printf("don't have any more cards!\n");
	(void)printf("My books:");
	cb = countbooks(comphand);
	(void)printf("Your books:");
	ub = countbooks(userhand);
	(void)printf("\nI have %d, you have %d.\n", cb, ub);
	if (ub > cb) {
		(void)printf("\nYou win!!!\n");
		if (nrandom(1024) == 0723)
			(void)printf("Cheater, cheater, pumpkin eater!\n");
	} else if (cb > ub) {
		(void)printf("\nI win!!!\n");
		if (nrandom(1024) == 0723)
			(void)printf("Hah!  Stupid peasant!\n");
	} else
		(void)printf("\nTie!\n");
	exit(0);
}
E 4

D 4
	for( i=1; i<=CTYPE;++i ){
		if( myhand[i] == 4 ){
			++my;
			printf( "%s ", cname[i] );
			}
		}
E 4
I 4
printplayer(player)
	int player;
{
	switch (player) {
	case COMPUTER:
		(void)printf("I ");
		break;
	case USER:
		(void)printf("You ");
		break;
	}
}
E 4

D 4
	printf( "\nYour books: " );
E 4
I 4
printhand(hand)
	int *hand;
{
	register int book, i, j;
E 4

D 4
	for( i=1; i<=CTYPE;++i ){
		if( yourhand[i] == 4 ){
			++your;
			printf( "%s ", cname[i] );
			}
		}

	printf( "\n\nI have %d, you have %d\n", my, your );

	printf( "\n%s win!!!\n", my>your?"I":"You" );
	exit(0);
E 4
I 4
	for (book = i = 0; i < RANKS; i++)
		if (hand[i] < CARDS)
			for (j = hand[i]; --j >= 0;) 
				PRC(i);
		else
			++book;
	if (book) {
		(void)printf(" + Book%s of", book > 1 ? "s" : "");
		for (i = 0; i < RANKS; i++)
			if (hand[i] == CARDS)
				PRC(i);
E 4
	}
I 4
	(void)putchar('\n');
}
E 4

D 4
# define G(x) { if(go) goto err;  else go = x; }
E 4
I 4
countcards(hand)
	register int *hand;
{
	register int i, count;
E 4

D 4
guess(){
	/* get the guess from the tty and return it... */
	register g, go;
E 4
I 4
	for (count = i = 0; i < RANKS; i++)
		count += *hand++;
	return(count);
}
E 4

D 4
	go = 0;
E 4
I 4
countbooks(hand)
	int *hand;
{
	int i, count;
E 4

D 4
	for(;;) {
		switch( g = getchar() ){

		case 'p':
		case 'P':
			++proflag;
			continue;

		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			G(g-'0');
			continue;

		case 'a':
		case 'A':
			G(1);
			continue;

		case '1':
			G(10);
			continue;

		case '0':
			if( go != 10 ) goto err;
			continue;

		case 'J':
		case 'j':
			G(11);
			continue;

		case 'Q':
		case 'q':
			G(12);
			continue;

		case 'K':
		case 'k':
			G(13);
			continue;

		case '\n':
			if( empty( yourhand ) ) return( NOMORE );
			if( go == 0 ){
				stats();
				continue;
				}
			return( go );

		case ' ':
		case '\t':
			continue;

		default:
			err:
			while( g != '\n' ) g = getchar();
			printf( "what?\n" );
			continue;
			}
E 4
I 4
	for (count = i = 0; i < RANKS; i++)
		if (hand[i] == CARDS) {
			++count;
			PRC(i);
E 4
		}
D 4
	}
E 4
I 4
	if (!count)
		(void)printf(" none");
	(void)putchar('\n');
	return(count);
}
E 4

D 4
/*	the program's strategy appears from here to the end */
E 4
I 4
init()
{
	register int i, rank;
E 4

D 4
char try[100];
char ntry;
char haveguessed[CTSIZ];

char hehas[CTSIZ];
D 3

start( h ) HAND h; {
	;
	}
E 3

hedrew( d ){
	++hehas[d];
E 4
I 4
	for (i = 0; i < RANKS; ++i)
		deck[i] = CARDS;
	for (i = 0; i < HANDSIZE; ++i) {
		while (!deck[rank = nrandom(RANKS)]);
		++userhand[rank];
		--deck[rank];
E 4
	}
D 4

heguessed( d ){
	++hehas[d];
E 4
I 4
	for (i = 0; i < HANDSIZE; ++i) {
		while (!deck[rank = nrandom(RANKS)]);
		++comphand[rank];
		--deck[rank];
E 4
	}
I 4
}
E 4

D 4
myguess(){
E 4
I 4
nrandom(n)
	int n;
{
	long random();
E 4

D 4
	register i, lg, t;
E 4
I 4
	return((int)random() % n);
}
E 4

D 4
	if( empty( myhand ) ) return( NOMORE );
E 4
I 4
instructions()
{
	int input;
	char buf[1024];
E 4

D 4
	/* make a list of those things which i have */
	/* leave off any which are books */
	/* if something is found that he has, guess it! */
E 4
I 4
	(void)printf("Would you like instructions (y or n)? ");
	input = getchar();
	while (getchar() != '\n');
	if (input != 'y')
		return;
E 4

D 4
	ntry = 0;
	for( i=1; i<=CTYPE; ++i ){
		if( myhand[i] == 0 || myhand[i] == 4 ) continue;
		try[ntry++] = i;
		}
E 4
I 4
	(void)sprintf(buf, "%s %s", _PATH_MORE, _PATH_INSTR);
	(void)system(buf);
	(void)printf("Hit return to continue...\n");
	while ((input = getchar()) != EOF && input != '\n');
}
E 4

D 4
	if( !proflag ) goto random;

	/* get ones he has, if any */

	for( i=0; i<ntry; ++i ){
		if( hehas[try[i]] ) {
			i = try[i];
			goto gotguess;
			}
		}

	/* is there one that has never been guessed; if so, guess it */
	lg = 101;
	for( i=0; i<ntry; ++i ){
		if( haveguessed[try[i]] < lg ) lg = haveguessed[try[i]];
		}
	/* remove all those not guessed longest ago */

	t = 0;
	for( i=0; i<ntry; ++i ){
		if( haveguessed[try[i]] == lg ) try[t++] = try[i];
		}
	ntry = t;
	if( t <= 0 ) error( "bad guessing loop" );

	random:
	i = choose( try, ntry );  /* make a random choice */

	gotguess:  /* do bookkeeping */

	hehas[i] = 0;  /* he won't anymore! */
	for( t=1; t<=CTYPE; ++t ){
		if( haveguessed[t] ) --haveguessed[t];
		}
	haveguessed[i] = 100;  /* will have guessed it */
	return(i);

	}

E 4
I 4
usage()
{
	(void)fprintf(stderr, "usage: fish [-p]\n");
	exit(1);
}
E 4
E 1
