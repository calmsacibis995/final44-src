h03639
s 00001/00001/00223
d D 8.2 95/04/28 15:41:47 bostic 8 7
c externs.h -> extern.h
e
s 00002/00002/00222
d D 8.1 93/05/31 16:12:27 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00223
d D 5.3 90/06/01 13:00:02 bostic 6 5
c new copyright notice
e
s 00010/00005/00224
d D 5.2 88/06/19 14:10:46 bostic 5 4
c install approved copyright notice
e
s 00011/00005/00218
d D 5.1 88/05/08 15:49:11 bostic 4 3
c add Berkeley header; yank to 5.1
e
s 00006/00000/00217
d D 1.3 85/04/24 15:28:58 edward 3 2
c copyright messages
e
s 00038/00030/00179
d D 1.2 84/11/28 18:29:42 edward 2 1
c Dave's changes
e
s 00209/00000/00000
d D 1.1 84/11/18 18:58:33 edward 1 0
c date and time created 84/11/18 18:58:33 by edward
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 4
I 4
D 7
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

E 3
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

D 8
#include "externs.h"
E 8
I 8
#include "extern.h"
E 8

move(thataway, token)
int thataway, token;
{
	wordnumber++;
	if ((!notes[CANTMOVE] && !notes[LAUNCHED]) || testbit(location[position].objects, LAND) || fuel > 0 && notes[LAUNCHED])
		if (thataway) {
			position = thataway;
			newway(token);
			time++;
		}
		else {
			puts("You can't go this way.");
			newway(token);
			whichway(location[position]);
			return(0);
		}
	else if (notes[CANTMOVE] && !notes[LAUNCHED])
D 2
		puts("You aren't able to move, you better drop something.");
E 2
I 2
		puts("You aren't able to move; you better drop something.");
E 2
	else
D 2
		puts("You are out of fuel, now we will rot in space forever!");
E 2
I 2
		puts("You are out of fuel; now you will rot in space forever!");
E 2
	return(1);
}

convert(tothis)		/* Converts day to night and vice versa. 	    */
int tothis;		/* Day objects are permanent.  Night objects are added*/
{			/* at dusk, and subtracted at dawn.		*/
	register struct objs *p;
I 2
	register i, j;
E 2

D 2
	if (tothis == TONIGHT){
		location = nightfile;
E 2
I 2
	if (tothis == TONIGHT) {
		for (i = 1; i <= NUMOFROOMS; i++)
			for (j = 0; j < NUMOFWORDS; j++)
				nightfile[i].objects[j] = dayfile[i].objects[j];
E 2
		for (p = nightobjs; p->room != 0; p++)
D 2
			setbit(location[p->room].objects, p->obj);
E 2
I 2
			setbit(nightfile[p->room].objects, p->obj);
		location = nightfile;
E 2
	} else {
D 2
		location = dayfile;
E 2
I 2
		for (i = 1; i <= NUMOFROOMS; i++)
			for (j = 0; j < NUMOFWORDS; j++)
				dayfile[i].objects[j] = nightfile[i].objects[j];
E 2
		for (p = nightobjs; p->room != 0; p++)
D 2
			clearbit(location[p->room].objects, p->obj);
E 2
I 2
			clearbit(dayfile[p->room].objects, p->obj);
		location = dayfile;
E 2
	}
}

news()
{
	register int n;
	int hurt;

	if (time > 30 && position < 32){
		puts("An explosion of shuddering magnitude splinters bulkheads and");
		puts("ruptures the battlestar's hull.  You are sucked out into the");
D 2
		puts("frozen void of space and killed...");
E 2
I 2
		puts("frozen void of space and killed.");
E 2
		die();
	}
	if (time > 20 && position < 32)
		puts("Explosions rock the battlestar.");
	if (time > snooze){
		puts("You drop from exhaustion...");
		zzz();
	}
	if (time > snooze - 5)
D 2
		puts("I'm getting tired.");
	if (time > (rythmn + CYCLE) && location == nightfile){
		convert(TODAY);
		if (OUTSIDE && time - rythmn - CYCLE < 10){
			puts("Dew lit sunbeams stretch out from a watery sunrise and herald the dawn.");
			puts("You awake from a misty dream-world into stark reality");
			puts("It is day.");
E 2
I 2
		puts("You're getting tired.");
	if (time > (rythmn + CYCLE)) {
		if (location == nightfile) {
			convert(TODAY);
			if (OUTSIDE && time - rythmn - CYCLE < 10) {
				puts("Dew lit sunbeams stretch out from a watery sunrise and herald the dawn.");
				puts("You awake from a misty dream-world into stark reality.");
				puts("It is day.");
			}
		} else {
			convert(TONIGHT);
			clearbit(location[POOLS].objects, BATHGOD);
			if (OUTSIDE && time - rythmn - CYCLE < 10) {
				puts("The dying sun sinks into the ocean, leaving a blood stained sunset.");
				puts("The sky slowly fades from orange to violet to black.  A few stars");
				puts("flicker on, and it is night.");
				puts("The world seems completly different at night.");
			}
E 2
		}
D 2
		rythmn = time;
E 2
I 2
		rythmn = time - time % CYCLE;
E 2
	}
D 2
	else if (time > (rythmn + CYCLE)){
		convert(TONIGHT);
		clearbit(location[POOLS].objects,BATHGOD);
		if (OUTSIDE && time - rythmn - CYCLE < 10){
			puts("The dying sun sinks into the ocean, leaving a blood stained sunset.");
			puts("The sky slowly fades from orange to violet to black.  A few stars");
			puts("flicker on, and it is night.");
			puts("The world seems completly different at night.");
		}
		rythmn = time;
	}
E 2
	if (!wiz && !tempwiz)
		if ((testbit(inven,TALISMAN) || testbit(wear,TALISMAN)) && (testbit(inven,MEDALION) || testbit(wear,MEDALION)) && (testbit(inven,AMULET) || testbit(wear,AMULET))){
			tempwiz = 1;
D 2
			puts("The three amulets glow and reenforce each other in power.  You are now a wizard.");
E 2
I 2
			puts("The three amulets glow and reenforce each other in power.\nYou are now a wizard.");
E 2
	}
	if (testbit(location[position].objects,ELF)){
		printf("%s\n",objdes[ELF]);
		fight(ELF,rnd(30));
	}
	if (testbit(location[position].objects,DARK)){
		printf("%s\n",objdes[DARK]);
		fight(DARK,100);
	}
	if (testbit(location[position].objects,WOODSMAN)){
		printf("%s\n",objdes[WOODSMAN]);
		fight(WOODSMAN,50);
	}
	switch(position){
		
		case 267:
		case 257:	/* entering a cave */
		case 274:
		case 246:
			notes[CANTSEE] = 1;
			break;
		case 160:
		case 216:	/* leaving a cave */
		case 230:
		case 231:
		case 232:
			notes[CANTSEE] = 0;
			break;
	}
	if (testbit(location[position].objects, GIRL))
		meetgirl = 1;
	if (meetgirl && CYCLE * 1.5 - time < 10){
		setbit(location[GARDEN].objects,GIRLTALK);
		setbit(location[GARDEN].objects,LAMPON);
		setbit(location[GARDEN].objects,ROPE);
	}
	if (position == DOCK && (beenthere[position] || time > CYCLE)){
		clearbit(location[DOCK].objects, GIRL);
		clearbit(location[DOCK].objects,MAN);
	}
	if (meetgirl && time - CYCLE * 1.5 > 10){
		clearbit(location[GARDEN].objects,GIRLTALK);
		clearbit(location[GARDEN].objects,LAMPON);
		clearbit(location[GARDEN].objects,ROPE);
		meetgirl = 0;
	}
	if (testbit(location[position].objects,CYLON)){
		puts("Oh my God, you're being shot at by an alien spacecraft!");
		printf("The targeting computer says we have %d seconds to attack!\n",clock);
		fflush(stdout);
I 2
		sleep(1);
E 2
		if (!visual()){
			hurt = rnd(NUMOFINJURIES);
			injuries[hurt] = 1;
D 2
			puts("Laser blasts sear the cockpit, but then he veers off.");
E 2
I 2
			puts("Laser blasts sear the cockpit, and the alien veers off in a victory roll.");
E 2
			puts("The viper shudders under a terrible explosion.");
			printf("I'm afraid you have suffered %s.\n", ouch[hurt]);
		}
		else
			clearbit(location[position].objects,CYLON);
	}
	if (injuries[SKULL] && injuries[INCISE] && injuries[NECK]){
		puts("I'm afraid you have suffered fatal injuries.");
		die();
	}
	for (n=0; n < NUMOFINJURIES; n++)
		if (injuries[n] == 1){
			injuries[n] = 2;
			if (WEIGHT > 5)
				WEIGHT -= 5;
			else
				WEIGHT = 0;
		}
	if (injuries[ARM] == 2){
		CUMBER -= 5;
		injuries[ARM]++;
	}
	if (injuries[RIBS] == 2){
		CUMBER -= 2;
		injuries[RIBS]++;
	}
	if (injuries[SPINE] == 2){
		WEIGHT = 0;
		injuries[SPINE]++;
	}
	if (carrying > WEIGHT || encumber > CUMBER)
		notes[CANTMOVE] = 1;
	else
		notes[CANTMOVE] = 0;
}

crash()
{
	int hurt1,hurt2;

	fuel--;
	if (!location[position].flyhere || (testbit(location[position].objects,LAND) && fuel <= 0)){
		if (!location[position].flyhere)
			puts("You're flying too low.  We're going to crash!");
		else{ 
			puts("You're out of fuel.  We'll have to crash land!");
			if (!location[position].down){
D 2
				puts("You're viper strikes the ground and explodes into firey fragments.");
E 2
I 2
				puts("Your viper strikes the ground and explodes into firey fragments.");
E 2
				puts("Thick black smoke billows up from the wreckage.");
				die();
			}
			position = location[position].down;
		}
		notes[LAUNCHED] = 0;
		setbit(location[position].objects,CRASH);
		time += rnd(CYCLE/4);
		puts("The viper explodes into the ground and you lose consciousness...");
		zzz();
		hurt1 = rnd(NUMOFINJURIES - 2) + 2;
		hurt2 = rnd(NUMOFINJURIES - 2) + 2;
		injuries[hurt1] = 1;
		injuries[hurt2] = 1;
		injuries[0] = 1;	/* abrasions */
		injuries[1] = 1;	/* lacerations */
		printf("I'm afraid you have suffered %s and %s.\n",ouch[hurt1],ouch[hurt2]);
	}
}
E 1
