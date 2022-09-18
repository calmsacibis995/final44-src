h31586
s 00001/00001/00297
d D 8.2 95/04/28 15:41:51 bostic 8 7
c externs.h -> extern.h
e
s 00002/00002/00296
d D 8.1 93/05/31 16:12:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00297
d D 5.3 90/06/01 13:00:43 bostic 6 5
c new copyright notice
e
s 00010/00005/00298
d D 5.2 88/06/19 14:10:55 bostic 5 4
c install approved copyright notice
e
s 00011/00005/00292
d D 5.1 88/05/08 15:49:19 bostic 4 3
c add Berkeley header; yank to 5.1
e
s 00006/00000/00291
d D 1.3 85/04/24 15:28:33 edward 3 2
c copyright messages
e
s 00013/00012/00278
d D 1.2 84/11/28 18:29:27 edward 2 1
c Dave's changes
e
s 00290/00000/00000
d D 1.1 84/11/18 18:58:41 edward 1 0
c date and time created 84/11/18 18:58:41 by edward
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

kiss()
{
	while (wordtype[++wordnumber] != NOUNS && wordnumber <= wordcount);
	if (wordtype[wordnumber] == NOUNS && testbit(location[position].objects,wordvalue[wordnumber])){
		pleasure++;
		printf("Kissed.\n");
		switch (wordvalue[wordnumber]){
			case NORMGOD:
			switch(godready++){
				case 0:
					puts("She squirms and avoids your advances.");
					break;
				case 1:
					puts("She is coming around; she didn't fight it as much.");
					break;
				case 2:
					puts("She's begining to like it.");
					break;
				default:
					puts("She's gone limp.");
					
			}
			break;
			case NATIVE:
				puts("The lips are warm and her body robust.  She pulls you down to the ground.");
				break;
			case TIMER:
				puts("The old man blushes.");
				break;
			case MAN:
				puts("The dwarf punches you in the kneecap.");
				break;
			default:
				pleasure--;
		}
	}
	else	puts("I'd prefer not to.");
}

love()
{
	register int n;

	while (wordtype[++wordnumber] != NOUNS && wordnumber <= wordcount);
	if (wordtype[wordnumber] == NOUNS && testbit(location[position].objects,wordvalue[wordnumber])){
		if (wordvalue[wordnumber] == NORMGOD && !loved)
			if (godready >= 2){
				puts("She cuddles up to you, and her mouth starts to work:\n'That was my sister's amulet.  The lovely goddess, Purl, was she.  The Empire\ncaptured her just after the Darkness came.  My other sister, Vert, was killed\nby the Dark Lord himself.  He took her amulet and warped its power.\nYour quest was foretold by my father before he died, but to get the Dark Lord's\namulet you must use cunning and skill.  I will leave you my amulet.");
				puts("which you may use as you wish.  As for me, I am the last goddess of the\nwaters.  My father was the Island King, and the rule is rightfully mine.'\n\nShe pulls the throne out into a large bed.");
				power++;
				pleasure += 15;
				ego++;
				if (card(injuries, NUMOFINJURIES)){
					puts("Her kisses revive you; your wounds are healed.\n");
					for (n=0; n < NUMOFINJURIES; n++)
						injuries[n] = 0;
					WEIGHT = MAXWEIGHT;
					CUMBER = MAXCUMBER;
				}
				printf("Goddess:\n");
				if (!loved)
					setbit(location[position].objects,MEDALION);
				loved = 1;
				time += 10;
				zzz();
			}
			else {
				puts("You wish!");
				return;
			}
		if (wordvalue[wordnumber] == NATIVE){
			puts("The girl is easy prey.  She peals off her sarong and indulges you.");
			power++;
			pleasure += 5;
			printf("Girl:\n");
			time += 10;
			zzz();
		}
		printf("Loved.\n");
	}
	else puts("I't doesn't seem to work.");
}

zzz()
{
	int oldtime;
	register int n;

	oldtime = time;
	if ((snooze - time) < (0.75 * CYCLE)){
		time += 0.75 * CYCLE - (snooze - time);
		printf("<zzz>");
		for (n = 0; n < time - oldtime; n++)
			printf(".");
		printf("\n");
		snooze += 3 * (time - oldtime);
		if (notes[LAUNCHED]){
			fuel -= (time - oldtime);
			if (location[position].down){
				position = location[position].down;
				crash();
			}
			else
				notes[LAUNCHED] = 0;
		}
D 2
		if (OUTSIDE && rnd(100) < 20){
E 2
I 2
		if (OUTSIDE && rnd(100) < 50){
E 2
			puts("You are awakened abruptly by the sound of someone nearby.");
D 2
			switch(rnd(3)){
E 2
I 2
			switch(rnd(4)){
E 2
				case 0:
					if (ucard(inven)){
						n = rnd(NUMOFOBJECTS);
						while(!testbit(inven,n))
							n = rnd(NUMOFOBJECTS);
						clearbit(inven,n);
						if (n != AMULET && n != MEDALION && n != TALISMAN)
							setbit(location[position].objects,n);
						carrying -= objwt[n];
						encumber -= objcumber[n];
					}
					puts("A fiendish little Elf is stealing your treasures!");
					fight(ELF,10);
					break;
				case 1:
					setbit(location[position].objects,DEADWOOD);
					break;
				case 2:
					setbit(location[position].objects,HALBERD);
					break;
I 2
				default:
					break;
E 2
			}
		}
	}
	else
		return(0);
	return(1);
}

chime()
{
	if ((time / CYCLE + 1) % 2 && OUTSIDE)
		switch((time % CYCLE)/(CYCLE / 7)){
			case 0:
				puts("It is just after sunrise.");
				break;
			case 1:
				puts("It is early morning.");
				break;
			case 2:
				puts("It is late morning.");
				break;
			case 3:
				puts("It is near noon.");
				break;
			case 4:
				puts("It is early afternoon.");
				break;
			case 5:
				puts("It is late afternoon.");
				break;
			case 6:
				puts("It is near sunset.");
				break;
		}
	else if (OUTSIDE)
		switch((time % CYCLE)/(CYCLE / 7)){
			case 0:
				puts("It is just after sunset.");
				break;
			case 1:
				puts("It is early evening.");
				break;
			case 2:
				puts("The evening is getting old.");
				break;
			case 3:
				puts("It is near midnight.");
				break;
			case 4:
				puts("These are the wee hours of the morning.");
				break;
			case 5:
				puts("The night is waning.");
				break;
			case 6:
				puts("It is almost morning.");
				break;
		}
	else
		puts("I can't tell the time in here.");
}

give()
{
	int obj = -1, result = -1, person = 0, firstnumber, last1, last2;

	firstnumber = wordnumber;
	while (wordtype[++wordnumber] != OBJECT  && wordvalue[wordnumber] != AMULET && wordvalue[wordnumber] != MEDALION && wordvalue[wordnumber] != TALISMAN && wordnumber <= wordcount);
	if (wordnumber <= wordcount){
		obj = wordvalue[wordnumber];
		if (obj == EVERYTHING)
			wordtype[wordnumber] = -1;
		last1 = wordnumber;
	}
	wordnumber = firstnumber;
	while ((wordtype[++wordnumber] != NOUNS || wordvalue[wordnumber] == obj) && wordnumber <= wordcount);
	if (wordtype[wordnumber] == NOUNS){
		person = wordvalue[wordnumber];
		last2 = wordnumber;
	}
	wordnumber = last1 - 1;
	if (person && testbit(location[position].objects,person))
		if (person == NORMGOD && godready < 2 && !(obj == RING || obj == BRACELET))
			puts("The goddess won't look at you.");
		else
			result = drop("Given");
	else {
		puts("I don't think that is possible.");
		return(0);
	}
	if (result != -1 && (testbit(location[position].objects,obj) || obj == AMULET || obj == MEDALION || obj == TALISMAN)){
		clearbit(location[position].objects,obj);
		time++;
		ego++;
		switch(person){
			case NATIVE:
				puts("She accepts it shyly.");
				ego += 2;
				break;
			case NORMGOD:
				if (obj == RING || obj == BRACELET){
					puts("She takes the charm and puts it on.  A little kiss on the cheek is");
					puts("your reward.");
					ego += 5;
					godready += 3;
				}
				if (obj == AMULET || obj == MEDALION || obj == TALISMAN){
					win++;
					ego += 5;
					power -= 5;
					if (win >= 3){
						puts("The powers of the earth are now legitimate.  You have destroyed the Darkness");
						puts("and restored the goddess to her thrown.  The entire island celebrates with");
						puts("dancing and spring feasts.  As a measure of her gratitude, the goddess weds you");
						puts("in the late summer and crowns you Prince Liverwort, Lord of Fungus.");
						puts("\nBut, as the year wears on and autumn comes along, you become restless and");
						puts("yearn for adventure.  The goddess, too, realizes that the marriage can't last.");
						puts("She becomes bored and takes several more natives as husbands.  One evening,");
						puts("after having been out drinking with the girls, she kicks the throne particulary");
						puts("hard and wakes you up.  (If you want to win this game, you're going to have to\nshoot her!)");
						clearbit(location[position].objects,MEDALION);
						wintime = time;
					}
				}
				break;
			case TIMER:
				if (obj == COINS){
D 2
					puts("He fingers the coins for a moment and then looks up agape. 'Kind you are and");
					puts("I mean to repay you as best I can.'  Grabbing a pencil and cocktail napkin...");
					printf("\n-------------------------------------------------------------------------------\n");
					printf(  "|				xxxxxxxxxx\\				      |\n");
					printf(  "|				    xxxxxxx\\	CLIFFS			      |\n");
					printf(  "|					xxxx\\				      |\n");
					printf(  "|		FOREST			   xx\\				      |\n");
E 2
I 2
					puts("He fingers the coins for a moment and then looks up agape.  `Kind you are and");
					puts("I mean to repay you as best I can.'  Grabbing a pencil and cocktail napkin...\n");
					printf(  "+-----------------------------------------------------------------------------+\n");
					printf(  "|				   xxxxxxxx\\				      |\n");
					printf(  "|				       xxxxx\\	CLIFFS			      |\n");
					printf(  "|		FOREST			  xxx\\				      |\n");
E 2
					printf(  "|				\\\\	     x\\        	OCEAN		      |\n");
					printf(  "|				||	       x\\			      |\n");
					printf(  "|				||  ROAD	x\\			      |\n");
					printf(  "|				||		x\\			      |\n");
					printf(  "|		SECRET		||	  .........			      |\n");
					printf(  "|		 - + -		||	   ........			      |\n");
					printf(  "|		ENTRANCE	||		...      BEACH		      |\n");
					printf(  "|				||		...		  E	      |\n");
					printf(  "|				||		...		  |	      |\n");
D 2
					printf(  "|				//		...	    N <-- + ---  S     |\n");
E 2
I 2
					printf(  "|				//		...	    N <-- + --- S     |\n");
E 2
					printf(  "|		PALM GROVE     //		...		  |	      |\n");
					printf(  "|			      //		...		  W	      |\n");
D 2
					printf(  "-------------------------------------------------------------------------------\n");
					puts("\n'This map shows a secret entrance to the catacombs.");
E 2
I 2
					printf(  "+-----------------------------------------------------------------------------+\n");
					puts("\n`This map shows a secret entrance to the catacombs.");
E 2
					puts("You will know when you arrive because I left an old pair of shoes there.'");
				}
				break;
		}
	}
	wordnumber = max(last1,last2);
	return(firstnumber);
}
E 1
