h49345
s 00005/00005/00747
d D 8.1 93/05/31 18:42:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00751
d D 4.3 90/06/01 13:57:25 bostic 3 2
c new copyright notice
e
s 00686/00318/00076
d D 4.2 90/02/13 15:51:43 bostic 2 1
c new version from Dave Taylor
e
s 00394/00000/00000
d D 4.1 82/10/24 18:27:15 mckusick 1 0
c date and time created 82/10/24 18:27:15 by mckusick
e
u
U
t
T
I 2
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * Copyright (c) 1989 Dave Taylor, Intuitive Systems.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Dave Taylor, of Intuitive Systems.
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */
E 2
I 1

D 2
static char sccsid[] = "	%M%	%I%	%E%	";
E 2
I 2
#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */
E 2

D 2
#
#include <stdio.h>
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

/*
D 2
 *	wumpus
 *	stolen from PCC Vol 2 No 1
E 2
I 2
 * A very new version of the age old favorite Hunt-The-Wumpus game that has
 * been a part of the BSD distribution of Unix for longer than us old folk
 * would care to remember.
E 2
 */

D 2
#define	NBAT	3
#define	NROOM	20
#define	NTUNN	3
#define	NPIT	3
#define BIGINT 2147483648.0
E 2
I 2
#include <sys/types.h>
#include <sys/file.h>
#include <stdio.h>
#include "pathnames.h"
E 2

D 2
struct room
{
	int	tunn[NTUNN];
	int	flag;
} room[NROOM];
E 2
I 2
/* some defines to spec out what our wumpus cave should look like */
E 2

D 2
char	*intro[] =
{
	"\n",
	"Welcome to 'Hunt the Wumpus.'\n",
	"\n",
	"The Wumpus lives in a cave of %d rooms.\n",
	"Each room has %d tunnels leading to other rooms.\n",
	"\n",
	"Hazards:\n",
	"\n",
	"Bottomless Pits - Some rooms have Bottomless Pits in them.\n",
	"	If you go there, you fall into the pit and lose!\n",
	"Super Bats - Some other rooms have super bats.\n",
	"	If you go there, a bat will grab you and take you to\n",
	"	somewhere else in the cave where you could\n",
	"	fall into a pit or run into the . . .\n",
	"\n",
	"Wumpus:\n",
	"\n",
	"The Wumpus is not bothered by the hazards since\n",
	"he has sucker feet and is too big for a bat to lift.\n",
	"\n",
	"Usually he is asleep.\n",
	"Two things wake him up:\n",
	"	your entering his room\n",
	"	your shooting an arrow anywhere in the cave.\n",
	"If the wumpus wakes, he either decides to move one room or\n",
	"stay where he was.  But if he ends up where you are,\n",
	"he eats you up and you lose!\n",
	"\n",
	"You:\n",
	"\n",
	"Each turn you may either move or shoot a crooked arrow.\n",
	"\n",
	"Moving - You can move to one of the adjoining rooms;\n",
	"	that is, to one that has a tunnel connecting it with\n",
	"	the room you are in.\n",
	"\n",
	"Shooting - You have 5 arrows.  You lose when you run out.\n",
	"	Each arrow can go from 1 to 5 rooms.\n",
	"	You aim by telling the computer\n",
	"	The arrow's path is a list of room numbers\n",
	"	telling the arrow which room to go to next.\n",
	"	The list is terminated with a 0.\n",
	"	The first room in the path must be connected to the\n",
	"	room you are in.  Each succeeding room must be\n",
	"	connected to the previous room.\n",
	"	If there is no tunnel between two of the rooms\n",
	"	in the arrow's path, the arrow chooses one of the\n",
	"	three tunnels from the room it's in and goes its\n",
	"	own way.\n",
	"\n",
	"	If the arrow hits the wumpus, you win!\n",
	"	If the arrow hits you, you lose!\n",
	"\n",
	"Warnings:\n",
	"\n",
	"When you are one or two rooms away from the wumpus,\n",
	"the computer says:\n",
	"		'I smell a Wumpus'\n",
	"When you are one room away from some other hazard, it says:\n",
	"		Bat    - 'Bats nearby'\n",
	"		Pit    - 'I feel a draft'\n",
	"\n",
	0,
};
E 2
I 2
#define	MAX_ARROW_SHOT_DISTANCE	6		/* +1 for '0' stopper */
#define	MAX_LINKS_IN_ROOM	25		/* a complex cave */
E 2

D 2
#define	BAT	01
#define	PIT	02
#define	WUMP	04
E 2
I 2
#define	MAX_ROOMS_IN_CAVE	250
#define	ROOMS_IN_CAVE		20
#define	MIN_ROOMS_IN_CAVE	10
E 2

D 2
int	arrow;
int	loc;
int	wloc;
int	tchar;
E 2
I 2
#define	LINKS_IN_ROOM		3
#define	NUMBER_OF_ARROWS	5
#define	PIT_COUNT		3
#define	BAT_COUNT		3
E 2

D 2
main()
{
	register i, j;
	register struct room *p;
	int k, icomp();
E 2
I 2
#define	EASY			1		/* levels of play */
#define	HARD			2
E 2

D 2
	printf("Instructions? (y-n) ");
	if(rline() == 'y')
		for(i=0; intro[i]; i++)
			printf(intro[i], i&1? NROOM: NTUNN);
E 2
I 2
/* some macro definitions for cleaner output */
E 2

I 2
#define	plural(n)	(n == 1 ? "" : "s")
E 2

I 2
/* simple cave data structure; +1 so we can index from '1' not '0' */
struct room_record {
	int tunnel[MAX_LINKS_IN_ROOM];
	int has_a_pit, has_a_bat;
} cave[MAX_ROOMS_IN_CAVE+1];

E 2
/*
D 2
 * initialize the room connections
E 2
I 2
 * global variables so we can keep track of where the player is, how
 * many arrows they still have, where el wumpo is, and so on...
E 2
 */
I 2
int player_loc = -1;			/* player location */
int wumpus_loc = -1;			/* The Bad Guy location */
int level = EASY;			/* level of play */
int arrows_left;			/* arrows unshot */
E 2

D 2
init:
	p = &room[0];
	for(i=0; i<NROOM; i++) {
		for(j=0; j<NTUNN; j++)
			p->tunn[j] = -1;
		p++;
E 2
I 2
#ifdef DEBUG
int debug = 0;
#endif

int pit_num = PIT_COUNT;		/* # pits in cave */
int bat_num = BAT_COUNT;		/* # bats */
int room_num = ROOMS_IN_CAVE;		/* # rooms in cave */
int link_num = LINKS_IN_ROOM;		/* links per room  */
int arrow_num = NUMBER_OF_ARROWS;	/* arrow inventory */

char answer[20];			/* user input */

main(argc, argv)
	int argc;
	char **argv;
{
	extern char *optarg;
	int c;

#ifdef DEBUG
	while ((c = getopt(argc, argv, "a:b:hp:r:t:d")) != EOF)
#else
	while ((c = getopt(argc, argv, "a:b:hp:r:t:")) != EOF)
#endif
		switch (c) {
		case 'a':
			arrow_num = atoi(optarg);
			break;
		case 'b':
			bat_num = atoi(optarg);
			break;
#ifdef DEBUG
		case 'd':
			debug = 1;
			break;
#endif
		case 'h':
			level = HARD;
			break;
		case 'p':
			pit_num = atoi(optarg);
			break;
		case 'r':
			room_num = atoi(optarg);
			if (room_num < MIN_ROOMS_IN_CAVE) {
				(void)fprintf(stderr,
	"No self-respecting wumpus would live in such a small cave!\n");
				exit(1);
			}
			if (room_num > MAX_ROOMS_IN_CAVE) {
				(void)fprintf(stderr,
	"Even wumpii can't furnish caves that large!\n");
				exit(1);
			}
			break;
		case 't':
			link_num = atoi(optarg);
			if (link_num < 2) {
				(void)fprintf(stderr,
	"Wumpii like extra doors in their caves!\n");
				exit(1);
			}
			break;
		case '?':
		default:
			usage();
E 2
	}
D 2
	k = 0;
	for(i=1; i<NROOM; ) {
		j = rnum(NROOM);
		p = &room[j];
		if(j == k || p->tunn[0] >= 0 || p->tunn[1] >= 0)
			continue;
		p->tunn[1] = k;
		room[k].tunn[0] = j;
		k = j;
		i++;
E 2
I 2

	if (link_num > MAX_LINKS_IN_ROOM ||
	    link_num > room_num - (room_num / 4)) {
		(void)fprintf(stderr,
"Too many tunnels!  The cave collapsed!\n(Fortunately, the wumpus escaped!)\n");
		exit(1);
E 2
	}
D 2
	p = &room[0];
	for(i=0; i<NROOM; i++) {
		for(j=0; j<NTUNN; j++) {
			if(p->tunn[j] < 0)
				p->tunn[j] = tunnel(i);
			if(p->tunn[j] == i)
				goto init;
			for(k=0; k<j; k++)
				if(p->tunn[j] == p->tunn[k])
					goto init;
		}
		qsort(&p->tunn[0], NTUNN, sizeof(p->tunn[0]), icomp);
		p++;
E 2
I 2

	if (level == HARD) {
		bat_num += ((random() % (room_num / 2)) + 1);
		pit_num += ((random() % (room_num / 2)) + 1);
E 2
	}

D 2
/*
 * put in player, wumpus,
 * pits and bats
 */
E 2
I 2
	if (bat_num > room_num / 2) {
		(void)fprintf(stderr,
"The wumpus refused to enter the cave, claiming it was too crowded!\n");
		exit(1);
	}
E 2

D 2
setup:
	arrow = 5;
	p = &room[0];
	for(i=0; i<NROOM; i++) {
		p->flag = 0;
		p++;
E 2
I 2
	if (pit_num > room_num / 2) {
		(void)fprintf(stderr,
"The wumpus refused to enter the cave, claiming it was too dangerous!\n");
		exit(1);
E 2
	}
D 2
	for(i=0; i<NPIT; ) {
		p = &room[rnum(NROOM)];
		if((p->flag&PIT) == 0) {
			p->flag |= PIT;
			i++;
E 2
I 2

	instructions();
	cave_init();

	/* and we're OFF!  da dum, da dum, da dum, da dum... */
	(void)printf(
"\nYou're in a cave with %d rooms and %d tunnels leading from each room.\n\
There are %d bat%s and %d pit%s scattered throughout the cave, and your\n\
quiver holds %d custom super anti-evil Wumpus arrows.  Good luck.\n",
	    room_num, link_num, bat_num, plural(bat_num), pit_num,
	    plural(pit_num), arrow_num);

	for (;;) {
		initialize_things_in_cave();
		arrows_left = arrow_num;
		do {
			display_room_stats();
			(void)printf("Move or shoot? (m-s) ");
			(void)fflush(stdout);
			if (!fgets(answer, sizeof(answer), stdin))
				break;
		} while (!take_action());

		if (!getans("\nCare to play another game? (y-n) "))
			exit(0);
		if (getans("In the same cave? (y-n) "))
			clear_things_in_cave();
		else
			cave_init();
	}
	/* NOTREACHED */
}

display_room_stats()
{
	register int i;

	/*
	 * Routine will explain what's going on with the current room, as well
	 * as describe whether there are pits, bats, & wumpii nearby.  It's
	 * all pretty mindless, really.
	 */
	(void)printf(
"\nYou are in room %d of the cave, and have %d arrow%s left.\n",
	    player_loc, arrows_left, plural(arrows_left));

	if (bats_nearby())
		(void)printf("*rustle* *rustle* (must be bats nearby)\n");
	if (pit_nearby())
		(void)printf("*whoosh* (I feel a draft from some pits).\n");
	if (wump_nearby())
		(void)printf("*sniff* (I can smell the evil Wumpus nearby!)\n");

	(void)printf("There are tunnels to rooms %d, ",
	   cave[player_loc].tunnel[0]);

	for (i = 1; i < link_num - 1; i++)
		if (cave[player_loc].tunnel[i] <= room_num)
			(void)printf("%d, ", cave[player_loc].tunnel[i]);
	(void)printf("and %d.\n", cave[player_loc].tunnel[link_num - 1]);
}

take_action()
{
	/*
	 * Do the action specified by the player, either 'm'ove, 's'hoot
	 * or something exceptionally bizarre and strange!  Returns 1
	 * iff the player died during this turn, otherwise returns 0.
	 */
	switch (*answer) {
		case 'M':
		case 'm':			/* move */
			return(move_to(answer + 1));
		case 'S':
		case 's':			/* shoot */
			return(shoot(answer + 1));
		case 'Q':
		case 'q':
		case 'x':
			exit(0);
		case '\n':
			return(0);
E 2
		}
I 2
	if (random() % 15 == 1)
		(void)printf("Que pasa?\n");
	else
		(void)printf("I don't understand!\n");
	return(0);
}

move_to(room_number)
	char *room_number;
{
	int i, just_moved_by_bats, next_room, tunnel_available;

	/*
	 * This is responsible for moving the player into another room in the
	 * cave as per their directions.  If room_number is a null string,
	 * then we'll prompt the user for the next room to go into.   Once
	 * we've moved into the room, we'll check for things like bats, pits,
	 * and so on.  This routine returns 1 if something occurs that kills
	 * the player and 0 otherwise...
	 */
	tunnel_available = just_moved_by_bats = 0;
	next_room = atoi(room_number);

	/* crap for magic tunnels */
	if (next_room == room_num + 1 &&
	    cave[player_loc].tunnel[link_num-1] != next_room)
		++next_room;

	while (next_room < 1 || next_room > room_num + 1) {
		if (next_room < 0 && next_room != -1)
(void)printf("Sorry, but we're constrained to a semi-Euclidean cave!\n");
		if (next_room > room_num + 1)
(void)printf("What?  The cave surely isn't quite that big!\n");
		if (next_room == room_num + 1 &&
		    cave[player_loc].tunnel[link_num-1] != next_room) {
			(void)printf("What?  The cave isn't that big!\n");
			++next_room;
		}
		(void)printf("To which room do you wish to move? ");
		(void)fflush(stdout);
		if (!fgets(answer, sizeof(answer), stdin))
			return(1);
		next_room = atoi(answer);
E 2
	}
D 2
	for(i=0; i<NBAT; ) {
		p = &room[rnum(NROOM)];
		if((p->flag&(PIT|BAT)) == 0) {
			p->flag |= BAT;
			i++;
E 2
I 2

	/* now let's see if we can move to that room or not */
	tunnel_available = 0;
	for (i = 0; i < link_num; i++)
		if (cave[player_loc].tunnel[i] == next_room)
			tunnel_available = 1;

	if (!tunnel_available) {
		(void)printf("*Oof!*  (You hit the wall)\n");
		if (random() % 6 == 1) {
(void)printf("Your colorful comments awaken the wumpus!\n");
			move_wump();
			if (wumpus_loc == player_loc) {
				wump_kill();
				return(1);
			}
E 2
		}
I 2
		return(0);
E 2
	}
D 2
	i = rnum(NROOM);
	wloc = i;
	room[i].flag |= WUMP;
	for(;;) {
		i = rnum(NROOM);
		if((room[i].flag&(PIT|BAT|WUMP)) == 0) {
			loc = i;
			break;
E 2
I 2

	/* now let's move into that room and check it out for dangers */
	if (next_room == room_num + 1)
		jump(next_room = (random() % room_num) + 1);

	player_loc = next_room;
	for (;;) {
		if (next_room == wumpus_loc) {		/* uh oh... */
			wump_kill();
			return(1);
E 2
		}
I 2
		if (cave[next_room].has_a_pit)
			if (random() % 12 < 2) {
				pit_survive();
				return(0);
			} else {
				pit_kill();
				return(1);
			}

		if (cave[next_room].has_a_bat) {
			(void)printf(
"*flap*  *flap*  *flap*  (humongous bats pick you up and move you%s!)\n",
			    just_moved_by_bats ? " again": "");
			next_room = player_loc = (random() % room_num) + 1;
			just_moved_by_bats = 1;
		}

		else
			break;
E 2
	}
I 2
	return(0);
}
E 2

D 2
/*
 *	main loop of the game
 */
E 2
I 2
shoot(room_list)
	char *room_list;
{
	int chance, next, roomcnt;
	int j, arrow_location, link, ok;
	char *p, *strtok();
E 2

D 2
loop:
	printf("You are in room %d\n", loc+1);
	p = &room[loc];
	if(p->flag&PIT) {
		printf("You fell into a pit\n");
		goto done;
E 2
I 2
	/*
	 * Implement shooting arrows.  Arrows are shot by the player indicating
	 * a space-separated list of rooms that the arrow should pass through;
	 * if any of the rooms they specify are not accessible via tunnel from
	 * the room the arrow is in, it will instead fly randomly into another
	 * room.  If the player hits the wumpus, this routine will indicate
	 * such.  If it misses, this routine will *move* the wumpus one room.
	 * If it's the last arrow, the player then dies...  Returns 1 if the
	 * player has won or died, 0 if nothing has happened.
	 */
	arrow_location = player_loc;
	for (roomcnt = 1;; ++roomcnt, room_list = NULL) {
		if (!(p = strtok(room_list, " \t\n")))
			if (roomcnt == 1) {
				(void)printf(
			"The arrow falls to the ground at your feet!\n");
				return(0);
			} else
				break;
		if (roomcnt > 5) {
			(void)printf(
"The arrow wavers in its flight and and can go no further!\n");
			break;
		}
		next = atoi(p);
		for (j = 0, ok = 0; j < link_num; j++)
			if (cave[arrow_location].tunnel[j] == next)
				ok = 1;

		if (ok) {
			if (next > room_num) {
				(void)printf(
"A faint gleam tells you the arrow has gone through a magic tunnel!\n");
				arrow_location = (random() % room_num) + 1;
			} else
				arrow_location = next;
		} else {
			link = (random() % link_num);
			if (link == player_loc)
				(void)printf(
"*thunk*  The arrow can't find a way from %d to %d and flys back into\n\
your room!\n",
				    arrow_location, next);
			else if (cave[arrow_location].tunnel[link] > room_num)
				(void)printf(
"*thunk*  The arrow flys randomly into a magic tunnel, thence into\n\
room %d!\n",
				    cave[arrow_location].tunnel[link]);
			else
				(void)printf(
"*thunk*  The arrow can't find a way from %d to %d and flys randomly\n\
into room %d!\n",
				    arrow_location, next,
				    cave[arrow_location].tunnel[link]);
			arrow_location = cave[arrow_location].tunnel[link];
			break;
		}
		chance = random() % 10;
		if (roomcnt == 3 && chance < 2) {
			(void)printf(
"Your bowstring breaks!  *twaaaaaang*\n\
The arrow is weakly shot and can go no further!\n");
			break;
		} else if (roomcnt == 4 && chance < 6) {
			(void)printf(
"The arrow wavers in its flight and and can go no further!\n");
			break;
		}
E 2
	}
D 2
	if(p->flag&WUMP) {
		printf("You were eaten by the wumpus\n");
		goto done;
E 2
I 2

	/*
	 * now we've gotten into the new room let us see if El Wumpo is
	 * in the same room ... if so we've a HIT and the player WON!
	 */
	if (arrow_location == wumpus_loc) {
		kill_wump();
		return(1);
E 2
	}
D 2
	if(p->flag&BAT) {
		printf("Theres a bat in your room\n");
		loc = rnum(NROOM);
		goto loop;
E 2
I 2

	if (arrow_location == player_loc) {
		shoot_self();
		return(1);
E 2
	}
D 2
	for(i=0; i<NTUNN; i++)
	if(near(&room[p->tunn[i]], WUMP))
		goto nearwump;
	if (near(p, WUMP)) {
	nearwump:
		printf("I smell a wumpus\n");
E 2
I 2

	if (!--arrows_left) {
		no_arrows();
		return(1);
E 2
	}
D 2
	if (near(p, BAT))
		printf("Bats nearby\n");
	if (near(p, PIT))
		printf("I feel a draft\n");
	printf("There are tunnels to");
	for(i=0; i<NTUNN; i++)
		printf(" %d", p->tunn[i]+1);
	printf("\n");
E 2

D 2
again:
	printf("Move or shoot (m-s) ");
	switch(rline()) {
	case 'm':
		if(tchar == '\n')
			printf("which room? ");
		i = rin()-1;
		for(j=0; j<NTUNN; j++)
			if(i == p->tunn[j])
				goto groom;
		printf("You hit the wall\n");
		goto again;
	groom:
		loc = i;
		if(i == wloc)
			goto mwump;
		goto loop;
E 2
I 2
	{
		/* each time you shoot, it's more likely the wumpus moves */
		static int lastchance = 2;
E 2

D 2
	case 's':
		if(tchar == '\n')
			printf("Give list of rooms terminated by 0\n");
		for(i=0; i<5; i++) {
			j = rin()-1;
			if(j == -1)
				break;
		ranarw:
			for(k=0; k<NTUNN; k++)
				if(j == p->tunn[k])
					goto garow;
			j = rnum(NROOM);
			goto ranarw;
		garow:
			p = &room[j];
			if(j == loc) {
				printf("You shot yourself\n");
				goto done;
			}
			if(p->flag&WUMP) {
				printf("You slew the wumpus\n");
				goto done;
			}
E 2
I 2
		if (random() % level == EASY ? 12 : 9 < (lastchance += 2)) {
			move_wump();
			if (wumpus_loc == player_loc)
				wump_kill();
			lastchance = random() % 3;

E 2
		}
D 2
		if(--arrow == 0) {
			printf("That was your last shot\n");
			goto done;
		}
		goto mwump;
E 2
	}
I 2
	return(0);
}
E 2

D 2
	goto again;
E 2
I 2
cave_init()
{
	register int i, j, k, link;
	int delta, int_compare();
	time_t time();
E 2

D 2
mwump:
	p = &room[wloc];
	p->flag &= ~WUMP;
	i = rnum(NTUNN+1);
	if(i != NTUNN)
		wloc = p->tunn[i];
	room[wloc].flag |= WUMP;
	goto loop;
E 2
I 2
	/*
	 * This does most of the interesting work in this program actually!
	 * In this routine we'll initialize the Wumpus cave to have all rooms
	 * linking to all others by stepping through our data structure once,
	 * recording all forward links and backwards links too.  The parallel
	 * "linkcount" data structure ensures that no room ends up with more
	 * than three links, regardless of the quality of the random number
	 * generator that we're using.
	 */
	srandom((int)time((time_t *)0));
E 2

D 2
done:
	drain();
	printf("Another game? (y-n) ");
	if(rline() != 'n') {
		drain();
		printf("Same room setup? (y-n) ");
		if(rline() != 'n')
			goto setup;
		goto init;
E 2
I 2
	/* initialize the cave first off. */
	for (i = 1; i <= room_num; ++i)
		for (j = 0; j < link_num ; ++j)
			cave[i].tunnel[j] = -1;

	/* choose a random 'hop' delta for our guaranteed link */
	while (!(delta = random() % room_num));

	for (i = 1; i <= room_num; ++i) {
		link = ((i + delta) % room_num) + 1;	/* connection */
		cave[i].tunnel[0] = link;		/* forw link */
		cave[link].tunnel[1] = i;		/* back link */
E 2
	}
I 2
	/* now fill in the rest of the cave with random connections */
	for (i = 1; i <= room_num; i++)
		for (j = 2; j < link_num ; j++) {
			if (cave[i].tunnel[j] != -1)
				continue;
try_again:		link = (random() % room_num) + 1;
			/* skip duplicates */
			for (k = 0; k < j; k++)
				if (cave[i].tunnel[k] == link)
					goto try_again;
			cave[i].tunnel[j] = link;
			if (random() % 2 == 1)
				continue;
			for (k = 0; k < link_num; ++k) {
				/* if duplicate, skip it */
				if (cave[link].tunnel[k] == i)
					k = link_num;

				/* if open link, use it, force exit */
				if (cave[link].tunnel[k] == -1) {
					cave[link].tunnel[k] = i;
					k = link_num;
				}
			}
		}
	/*
	 * now that we're done, sort the tunnels in each of the rooms to
	 * make it easier on the intrepid adventurer.
	 */
	for (i = 1; i <= room_num; ++i)
		qsort(cave[i].tunnel, (u_int)link_num,
		    sizeof(cave[i].tunnel[0]), int_compare);

#ifdef DEBUG
	if (debug)
		for (i = 1; i <= room_num; ++i) {
			(void)printf("<room %d  has tunnels to ", i);
			for (j = 0; j < link_num; ++j)
				(void)printf("%d ", cave[i].tunnel[j]);
			(void)printf(">\n");
		}
#endif
E 2
}

D 2
tunnel(i)
E 2
I 2
clear_things_in_cave()
E 2
{
D 2
	register struct room *p;
	register n, j;
	int c;
E 2
I 2
	register int i;
E 2

D 2
	c = 20;
E 2
I 2
	/*
	 * remove bats and pits from the current cave in preparation for us
	 * adding new ones via the initialize_things_in_cave() routines.
	 */
	for (i = 1; i <= room_num; ++i)
		cave[i].has_a_bat = cave[i].has_a_pit = 0;
}
E 2

D 2
loop:
	n = rnum(NROOM);
	if(n == i)
		if(--c > 0)
			goto loop;
	p = &room[n];
	for(j=0; j<NTUNN; j++)
	if(p->tunn[j] == -1) {
		p->tunn[j] = i;
		return(n);
E 2
I 2
initialize_things_in_cave()
{
	register int i, loc;

	/* place some bats, pits, the wumpus, and the player. */
	for (i = 0; i < bat_num; ++i) {
		do {
			loc = (random() % room_num) + 1;
		} while (cave[loc].has_a_bat);
		cave[loc].has_a_bat = 1;
#ifdef DEBUG
		if (debug)
			(void)printf("<bat in room %d>\n", loc);
#endif
E 2
	}
D 2
	goto loop;
E 2
I 2

	for (i = 0; i < pit_num; ++i) {
		do {
			loc = (random() % room_num) + 1;
		} while (cave[loc].has_a_pit && cave[loc].has_a_bat);
		cave[loc].has_a_pit = 1;
#ifdef DEBUG
		if (debug)
			(void)printf("<pit in room %d>\n", loc);
#endif
	}

	wumpus_loc = (random() % room_num) + 1;
#ifdef DEBUG
	if (debug)
		(void)printf("<wumpus in room %d>\n", loc);
#endif

	do {
		player_loc = (random() % room_num) + 1;
	} while (player_loc == wumpus_loc || (level == HARD ?
	    (link_num / room_num < 0.4 ? wump_nearby() : 0) : 0));
E 2
}

D 2
rline()
E 2
I 2
getans(prompt)
	char *prompt;
E 2
{
D 2
	register char c, r;
E 2
I 2
	char buf[20];
E 2

D 2
	while((c=getchar()) == ' ');
	r = c;
	while(c != '\n' && c != ' ') {
		if(c == EOF)
			exit();
		c = getchar();
E 2
I 2
	/*
	 * simple routine to ask the yes/no question specified until the user
	 * answers yes or no, then return 1 if they said 'yes' and 0 if they
	 * answered 'no'.
	 */
	for (;;) {
		(void)printf("%s", prompt);
		(void)fflush(stdout);
		if (!fgets(buf, sizeof(buf), stdin))
			return(0);
		if (*buf == 'N' || *buf == 'n')
			return(0);
		if (*buf == 'Y' || *buf == 'y')
			return(1);
		(void)printf(
"I don't understand your answer; please enter 'y' or 'n'!\n");
E 2
	}
D 2
	tchar = c;
	return(r);
E 2
I 2
	/* NOTREACHED */
E 2
}

D 2
rnum(n)
E 2
I 2
bats_nearby()
{ 
	register int i;

	/* check for bats in the immediate vicinity */
	for (i = 0; i < link_num; ++i)
		if (cave[cave[player_loc].tunnel[i]].has_a_bat)
			return(1);
	return(0);
}

pit_nearby()
{ 
	register int i;

	/* check for pits in the immediate vicinity */
	for (i = 0; i < link_num; ++i)
		if (cave[cave[player_loc].tunnel[i]].has_a_pit)
			return(1);
	return(0);
}

wump_nearby()
E 2
{
D 2
	static short first[2];
E 2
I 2
	register int i, j;
E 2

D 2
	if(first[1] == 0) {
		time(first);
		if(first[1]==0) first[1] = 1;
		srand((first[1]*first[0])^first[1]);
E 2
I 2
	/* check for a wumpus within TWO caves of where we are */
	for (i = 0; i < link_num; ++i) {
		if (cave[player_loc].tunnel[i] == wumpus_loc)
			return(1);
		for (j = 0; j < link_num; ++j)
			if (cave[cave[player_loc].tunnel[i]].tunnel[j] ==
			    wumpus_loc)
				return(1);
E 2
	}
D 2
	return((int)((rand()/BIGINT) * n));
E 2
I 2
	return(0);
E 2
}

D 2
rin()
E 2
I 2
move_wump()
E 2
{
D 2
	register n, c;
E 2
I 2
	wumpus_loc = cave[wumpus_loc].tunnel[random() % link_num];
}
E 2

D 2
	n = 0;
	c = getchar();
	while(c != '\n' && c != ' ') {
		if(c<'0' || c>'9') {
			while(c != '\n') {
				if(c == EOF)
					exit();
				c = getchar();
			}
			return(0);
		}
		n = n*10 + c-'0';
		c = getchar();
E 2
I 2
int_compare(a, b)
	int *a, *b;
{
	return(*a < *b ? -1 : 1);
}

instructions()
{
	char buf[120], *p, *getenv();

	/*
	 * read the instructions file, if needed, and show the user how to
	 * play this game!
	 */
	if (!getans("Instructions? (y-n) "))
		return;

	if (access(_PATH_WUMPINFO, R_OK)) {
		(void)printf(
"Sorry, but the instruction file seems to have disappeared in a\n\
puff of greasy black smoke! (poof)\n");
		return;
E 2
	}
D 2
	return(n);
E 2
I 2

	if (!(p = getenv("PAGER")) ||
	    strlen(p) > sizeof(buf) + strlen(_PATH_WUMPINFO) + 5)
		p = _PATH_PAGER;

	(void)sprintf(buf, "%s %s", p, _PATH_WUMPINFO);
	(void)system(buf);
E 2
}

D 2
near(ap, ahaz)
struct room *ap;
E 2
I 2
usage()
E 2
{
D 2
	register struct room *p;
	register haz, i;
E 2
I 2
	(void)fprintf(stderr,
"usage: wump [-h] [-a arrows] [-b bats] [-p pits] [-r rooms] [-t tunnels]\n");
	exit(1);
}
E 2

D 2
	p = ap;
	haz = ahaz;
	for(i=0; i<NTUNN; i++)
	if(room[p->tunn[i]].flag & haz)
		return (1);
	return(0);
E 2
I 2
/* messages */

wump_kill()
{
	(void)printf(
"*ROAR* *chomp* *snurfle* *chomp*!\n\
Much to the delight of the Wumpus, you walked right into his mouth,\n\
making you one of the easiest dinners he's ever had!  For you, however,\n\
it's a rather unpleasant death.  The only good thing is that it's been\n\
so long since the evil Wumpus cleaned his teeth that you immediately\n\
passed out from the stench!\n");
E 2
}

D 2
icomp(p1, p2)
int *p1, *p2;
E 2
I 2
kill_wump()
E 2
{
I 2
	(void)printf(
"*thwock!* *groan* *crash*\n\n\
A horrible roar fills the cave, and you realize, with a smile, that you\n\
have slain the evil Wumpus and won the game!  You don't want to tarry for\n\
long, however, because not only is the Wumpus famous, but the stench of\n\
dead Wumpus is also quite well known, a stench plenty enough to slay the\n\
mightiest adventurer at a single whiff!!\n");
}
E 2

D 2
	return(*p1 - *p2);
E 2
I 2
no_arrows()
{
	(void)printf(
"\nYou turn and look at your quiver, and realize with a sinking feeling\n\
that you've just shot your last arrow (figuratively, too).  Sensing this\n\
with its psychic powers, the evil Wumpus rampagees through the cave, finds\n\
you, and with a mighty *ROAR* eats you alive!\n");
E 2
}
D 2
#include <sgtty.h>
drain()
E 2
I 2

shoot_self()
E 2
{
D 2
	register FILE *port = stdin;
	register int iodes = fileno(port);
	struct sgttyb arg;
E 2
I 2
	(void)printf(
"\n*Thwack!*  A sudden piercing feeling informs you that the ricochet\n\
of your wild arrow has resulted in it wedging in your side, causing\n\
extreme agony.  The evil Wumpus, with its psychic powers, realizes this\n\
and immediately rushes to your side, not to help, alas, but to EAT YOU!\n\
(*CHOMP*)\n");
}
E 2

D 2
	port->_cnt = 0;
	port->_ptr = port->_base;
	if(gtty(iodes,&arg) != -1) stty(iodes,&arg);
E 2
I 2
jump(where)
	int where;
{
	(void)printf(
"\nWith a jaunty step you enter the magic tunnel.  As you do, you\n\
notice that the walls are shimmering and glowing.  Suddenly you feel\n\
a very curious, warm sensation and find yourself in room %d!!\n", where);
}

pit_kill()
{
	(void)printf(
"*AAAUUUUGGGGGHHHHHhhhhhhhhhh...*\n\
The whistling sound and updraft as you walked into this room of the\n\
cave apparently wasn't enough to clue you in to the presence of the\n\
bottomless pit.  You have a lot of time to reflect on this error as\n\
you fall many miles to the core of the earth.  Look on the bright side;\n\
you can at least find out if Jules Verne was right...\n");
}

pit_survive()
{
	(void)printf(
"Without conscious thought you grab for the side of the cave and manage\n\
to grasp onto a rocky outcrop.  Beneath your feet stretches the limitless\n\
depths of a bottomless pit!  Rock crumbles beneath your feet!\n");
E 2
}
E 1
