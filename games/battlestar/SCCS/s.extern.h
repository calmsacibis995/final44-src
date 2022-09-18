h52313
s 00002/00002/00269
d D 8.1 93/05/31 16:13:02 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00270
d D 5.4 90/06/01 13:01:56 bostic 7 6
c new copyright notice
e
s 00000/00003/00281
d D 5.3 90/04/30 21:40:01 bostic 6 5
c move log file to /var/games
e
s 00011/00006/00273
d D 5.2 88/06/19 14:11:11 bostic 5 4
c install approved copyright notice
e
s 00011/00005/00268
d D 5.1 88/05/08 15:49:36 bostic 4 3
c add Berkeley header; yank to 5.1
e
s 00006/00000/00267
d D 1.3 85/04/24 15:32:59 edward 3 2
c copyright messages
e
s 00002/00001/00265
d D 1.2 84/11/28 18:31:36 edward 2 1
c Dave's changes
e
s 00266/00000/00000
d D 1.1 84/11/18 19:28:11 edward 1 0
c date and time created 84/11/18 19:28:11 by edward
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
D 5
 * Copyright (c) 1988 Regents of the University of California.
E 5
I 5
D 8
 * Copyright (c) 1983 Regents of the University of California.
E 5
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
 *
 *	%W% (Berkeley) %G%
E 4
 */
D 4

E 3
I 1
/* %W% %G% */
E 4

#include <sys/signal.h>
#include <stdio.h>

D 6
#define PATH(x)		"/usr/games/lib/x"
#define logfile		PATH(battlestar.log)

E 6
#define BITS (8 * sizeof (int))

#define OUTSIDE		(position > 68 && position < 246 && position != 218)
#define rnd(x)		(rand() % (x))
#define max(a,b)	((a) < (b) ? (b) : (a))
#define testbit(array, index)	(array[index/BITS] & (1 << (index % BITS)))
#define setbit(array, index)	(array[index/BITS] |= (1 << (index % BITS)))
#define clearbit(array, index)	(array[index/BITS] &= ~(1 << (index % BITS)))

	/* well known rooms */
#define FINAL	275
#define GARDEN	197
#define POOLS	126
#define DOCK	93

	/* word types */
#define VERB	0
#define OBJECT  1
#define NOUNS	2
#define PREPS	3
#define ADJS	4
#define CONJ	5

	/* words numbers */
#define KNIFE		0 
#define SWORD		1
#define LAND		2
#define WOODSMAN 	3
#define TWO_HANDED	4
#define CLEAVER		5
#define BROAD		6
#define MAIL		7
#define HELM		8
#define SHIELD		9
#define MAID		10
#define BODY		10
#define VIPER		11
#define LAMPON		12
#define SHOES		13
#define CYLON		14
#define PAJAMAS		15
#define ROBE		16
#define AMULET		17
#define MEDALION	18
#define TALISMAN	19
#define DEADWOOD	20
#define MALLET		21
#define LASER		22
#define BATHGOD		23
#define NORMGOD		24
#define GRENADE		25
#define CHAIN		26
#define ROPE		27
#define LEVIS		28
#define MACE		29
#define SHOVEL		30
#define HALBERD		31
#define	COMPASS		32
#define	CRASH		33
#define ELF		34
#define FOOT		35
#define COINS		36
#define MATCHES		37
#define MAN		38
#define PAPAYAS		39
#define PINEAPPLE	40
#define KIWI		41
#define COCONUTS	42
#define MANGO		43
#define RING		44
#define POTION		45
#define BRACELET	46
#define GIRL		47
#define GIRLTALK	48
#define DARK		49
#define TIMER		50
#define CHAR		53
#define BOMB		54
#define DEADGOD		55
#define DEADTIME	56
#define DEADNATIVE	57
#define NATIVE		58
#define HORSE		59
#define CAR		60
#define POT		61
#define BAR		62
#define	BLOCK		63
#define NUMOFOBJECTS	64
	/* non-objects below */
#define UP	1000
#define DOWN	1001
#define AHEAD	1002
#define BACK	1003
#define RIGHT	1004
#define LEFT	1005
#define TAKE	1006
#define USE	1007
#define LOOK	1008
#define QUIT	1009
#define NORTH	1010
#define SOUTH	1011
#define EAST	1012
#define WEST	1013
#define SU      1014
#define DROP	1015
#define TAKEOFF	1016
#define DRAW	1017
#define PUTON	1018
#define WEARIT	1019
#define PUT	1020
#define INVEN	1021
#define EVERYTHING 1022
#define AND	1023
#define KILL	1024
#define RAVAGE	1025
#define UNDRESS	1026
#define THROW	1027
#define LAUNCH	1028
#define LANDIT	1029
#define LIGHT	1030
#define FOLLOW	1031
#define KISS	1032
#define LOVE	1033
#define GIVE	1034
#define SMITE	1035
#define SHOOT	1036
#define ON	1037
#define	OFF	1038
#define TIME	1039
#define SLEEP	1040
#define DIG	1041
#define EAT	1042
#define SWIM	1043
#define DRINK	1044
#define DOOR	1045
#define SAVE	1046
#define RIDE	1047
#define DRIVE	1048
#define SCORE	1049
#define BURY	1050 
#define JUMP	1051
I 2
#define KICK	1052
E 2

	/* injuries */
#define ARM	6		/* broken arm */
#define RIBS	7		/* broken ribs */
#define SPINE	9		/* broken back */
#define SKULL	11		/* fractured skull */
#define INCISE	10		/* deep incisions */
#define NECK	12		/* broken NECK */
#define NUMOFINJURIES 13

	/* notes */
#define	CANTLAUNCH	0
#define LAUNCHED	1
#define CANTSEE		2
#define CANTMOVE	3 
#define JINXED		4
#define DUG		5
#define NUMOFNOTES	6

	/* fundamental constants */
#define NUMOFROOMS	275
#define NUMOFWORDS	((NUMOFOBJECTS + BITS - 1) / BITS)
#define LINELENGTH	81

#define TODAY		0
#define TONIGHT		1
#define CYCLE		100

	/* initial variable values */
D 2
#define TANKFULL	50
E 2
I 2
#define TANKFULL	250
E 2
#define TORPEDOES	10
#define MAXWEIGHT	60
#define MAXCUMBER	10

struct room {
	char *name;
	int link[8];
#define north	link[0]
#define south	link[1]
#define east	link[2]
#define west	link[3]
#define up	link[4]
#define access	link[5]
#define down	link[6]
#define flyhere	link[7]
	char *desc;
	unsigned int objects[NUMOFWORDS];
};
struct room dayfile[];
struct room nightfile[];
struct room *location;

	/* object characteristics */
char *objdes[NUMOFOBJECTS];
char *objsht[NUMOFOBJECTS];
char *ouch[NUMOFINJURIES];
int objwt[NUMOFOBJECTS];
int objcumber[NUMOFOBJECTS];

	/* current input line */
#define NWORD	20			/* words per line */
char words[NWORD][15];
int wordvalue[NWORD];
int wordtype[NWORD];
int wordcount, wordnumber;

char *truedirec(), *rate();
char *getcom(), *getword();

	/* state of the game */
int time;
int position;
int direction;
int left, right, ahead, back;
int clock, fuel, torps;
int carrying, encumber;
int rythmn;
int followfight;
int ate;
int snooze;
int meetgirl;
int followgod;
int godready;
int win;
int wintime;
int wiz;
int tempwiz;
int matchlight, matchcount;
int loved;
int pleasure, power, ego;
int WEIGHT;
int CUMBER;
int notes[NUMOFNOTES];
unsigned int inven[NUMOFWORDS];
unsigned int wear[NUMOFWORDS];
char beenthere[NUMOFROOMS+1];
char injuries[NUMOFINJURIES];

char uname[9];

struct wlist {
	char *string;
	int value, article;
	struct wlist *next;
};
#define HASHSIZE	256
#define HASHMUL		81
#define HASHMASK	(HASHSIZE - 1)
struct wlist *hashtab[HASHSIZE];
struct wlist wlist[];

struct objs {
	short room;
	short obj;
};
struct objs dayobjs[];
struct objs nightobjs[];
E 1
