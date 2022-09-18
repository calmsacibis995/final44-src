h28987
s 00001/00001/00241
d D 8.2 95/04/28 15:41:53 bostic 8 7
c externs.h -> extern.h
e
s 00002/00002/00240
d D 8.1 93/05/31 16:12:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00241
d D 5.3 90/06/01 13:01:07 bostic 6 5
c new copyright notice
e
s 00010/00005/00242
d D 5.2 88/06/19 14:10:59 bostic 5 4
c install approved copyright notice
e
s 00011/00005/00236
d D 5.1 88/05/08 15:49:22 bostic 4 3
c add Berkeley header; yank to 5.1
e
s 00006/00000/00235
d D 1.3 85/04/24 15:32:51 edward 3 2
c copyright messages
e
s 00003/00003/00232
d D 1.2 84/11/28 18:31:30 edward 2 1
c Dave's changes
e
s 00235/00000/00000
d D 1.1 84/11/18 18:58:45 edward 1 0
c date and time created 84/11/18 18:58:45 by edward
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

fight(enemy,strength)
int enemy,strength;
{
	int lifeline = 0;
	int hurt;
	char auxbuf[LINELENGTH];
	char *next;
	int i;
	int exhaustion;

fighton:
	time++;
	snooze -= 5;
	if (snooze > time)
		exhaustion = CYCLE/(snooze - time);
	else {
D 2
		puts("You collapse exhausted and he pulverizes your skull.");
E 2
I 2
		puts("You collapse exhausted, and he pulverizes your skull.");
E 2
		die();
	}
	if (snooze - time < 20)
D 2
		puts("You look tired, I hope you're able to fight.");
E 2
I 2
		puts("You look tired! I hope you're able to fight.");
E 2
	next = getcom(auxbuf, LINELENGTH, "<fight!>-: ", 0);
	for (i=0; next && i < 10; i++)
		next = getword(next, words[i], -1);
	parse();
	switch(wordvalue[wordnumber]){

		case KILL:
		case SMITE:
			if (testbit(inven,TWO_HANDED))
				hurt = rnd(70) - 2 * card(injuries,NUMOFINJURIES) - ucard(wear) - exhaustion;
			else if (testbit(inven,SWORD) || testbit(inven, BROAD))
				hurt = rnd(50)%(WEIGHT-carrying)-card(injuries,NUMOFINJURIES)-encumber - exhaustion;
			else if (testbit(inven,KNIFE) || testbit(inven,MALLET) || testbit(inven,CHAIN) || testbit(inven,MACE) || testbit(inven,HALBERD))
				hurt = rnd(15) - card(injuries,NUMOFINJURIES) - exhaustion;
			else 
				hurt = rnd(7) - encumber;
			if (hurt < 5)
				switch(rnd(3)){

					case 0:
						puts("You swung wide and missed.");
						break;
					case 1:
						puts("He checked your blow. CLASH! CLANG!");
						break;
					case 2:
						puts("His filthy tunic hangs by one less thread.");
						break;
				}
			else if (hurt < 10){
				switch(rnd(3)){
					case 0:
						puts("He's bleeding.");
						break;
					case 1:
						puts("A trickle of blood runs down his face.");
						break;
					case 2:
						puts("A huge purple bruise is forming on the side of his face.");
						break;
				}
				lifeline++;
			}
			else if (hurt < 20){
				switch(rnd(3)){
					case 0:
						puts("He staggers back quavering.");
						break;
					case 1:
						puts("He jumps back with his hand over the wound.");
						break;
					case 2:
						puts("His shirt falls open with a swath across the chest.");
						break;
				}
				lifeline += 5;
			}
			else if (hurt < 30){
				switch(rnd(3)){
					case 0:
						printf("A bloody gash opens up on his %s side.\n",(rnd(2) ? "left" : "right"));
						break;
					case 1:
						puts("The steel bites home and scrapes along his ribs.");
						break;
					case 2:
D 2
						puts("You pierce him and his breath hisses through clenched teeth.");
E 2
I 2
						puts("You pierce him, and his breath hisses through clenched teeth.");
E 2
						break;
				}
				lifeline += 10;
			}
			else if (hurt < 40){
				switch(rnd(3)){
					case 0:
						puts("You smite him to the ground.");
						if (strength - lifeline > 20)
							puts("But in a flurry of steel he regains his feet!");
						break;
					case 1:
						puts("The force of your blow sends him to his knees.");
						puts("His arm swings lifeless at his side.");
						break;
					case 2:
						puts("Clutching his blood drenched shirt, he collapses stunned.");
						break;
				}
				lifeline += 20;
			}
			else {
				switch(rnd(3)){
					case 0:
						puts("His ribs crack under your powerful swing, flooding his lungs with blood.");
						break;
					case 1:
						puts("You shatter his upheld arm in a spray of blood.  The blade continues deep");
						puts("into his back, severing the spinal cord.");
						lifeline += 25;
						break;
					case 2:
						puts("With a mighty lunge the steel slides in, and gasping, he falls to the ground.");
						lifeline += 25;
						break;
				}
				lifeline += 30;
			}
			break;

		case BACK:
			if (enemy == DARK && lifeline > strength * 0.33){
				puts("He throws you back against the rock and pummels your face.");
				if (testbit(inven,AMULET) || testbit(wear,AMULET)){
					printf("Lifting the amulet from you, ");
					if (testbit(inven,MEDALION) || testbit(wear,MEDALION)){
						puts("his power grows and the walls of\nthe earth tremble.");
						puts("When he touches the medallion, your chest explodes and the foundations of the\nearth collapse.");
						puts("The planet is consumed by darkness.");
						die();
					}
					if (testbit(inven,AMULET)){
						clearbit(inven,AMULET);
						carrying -= objwt[AMULET];
						encumber -= objcumber[AMULET];
					}
					else
						clearbit(wear,AMULET);
					puts("he flees down the dark caverns.");
					clearbit(location[position].objects,DARK);
					injuries[SKULL] = 1;
					followfight = time;
					return (0);
				}
				else{
					puts("I'm afraid you have been killed.");
					die();
				}
			}
			else{
				puts("You escape stunned and disoriented from the fight.");
				puts("A victorious bellow echoes from the battlescene.");
				if (back && position != back)
					move(back,BACK);
				else if (ahead &&position != ahead)
					move(ahead,AHEAD);
				else if (left && position != left)
					move(left,LEFT);
				else if (right && position != right)
					move(right,RIGHT);
				else
					move(location[position].down,AHEAD);
				return(0);
			}

		case SHOOT:
			if (testbit(inven,LASER)){
				if (strength - lifeline <= 50){
					printf("The %s took a direct hit!\n",objsht[enemy]);
					lifeline += 50;
				}
				else {
					puts("With his bare hand he deflects the laser blast and whips the pistol from you!");
					clearbit(inven,LASER);
					setbit(location[position].objects,LASER);
					carrying -= objwt[LASER];
					encumber -= objcumber[LASER];
				}
			}
			else
				puts("Unfortunately, you don't have a blaster handy.");
			break;

		case DROP:
		case DRAW:
			cypher();
			time--;
			break;
		
		default:
			puts("You don't have a chance, he is too quick.");
			break;

	}
	if (lifeline >= strength){
		printf("You have killed the %s.\n", objsht[enemy]);
		if (enemy == ELF || enemy == DARK)
			puts("A watery black smoke consumes his body and then vanishes with a peal of thunder!");
		clearbit(location[position].objects,enemy);
		power += 2;
		notes[JINXED]++;
		return(0);
	}
	puts("He attacks...");
	/* some embellisments */
	hurt = rnd(NUMOFINJURIES) - (testbit(inven,SHIELD) != 0) - (testbit(wear,MAIL) != 0) - (testbit(wear,HELM) != 0);
	hurt += (testbit(wear,AMULET) != 0) + (testbit(wear,MEDALION) != 0) + (testbit(wear,TALISMAN) != 0);
	hurt = hurt < 0 ? 0 : hurt;
	hurt =	hurt >= NUMOFINJURIES ? NUMOFINJURIES -1 : hurt;
	if (!injuries[hurt]){
		injuries[hurt] = 1;
		printf("I'm afraid you have suffered %s.\n", ouch[hurt]);
	}
	else
		puts("You emerge unscathed.");
	if (injuries[SKULL] && injuries[INCISE] && injuries[NECK]){
		puts("I'm afraid you have suffered fatal injuries.");
		die();
	}
	goto fighton;
}
E 1
