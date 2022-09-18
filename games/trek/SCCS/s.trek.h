h07503
s 00002/00002/00352
d D 8.1 93/05/31 17:58:09 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00353
d D 5.5 90/06/01 13:26:44 bostic 7 6
c new copyright notice
e
s 00010/00005/00354
d D 5.4 88/06/18 15:08:30 bostic 6 5
c install approved copyright notice
e
s 00008/00003/00351
d D 5.3 88/05/05 18:34:56 bostic 5 4
c written by Eric Allman; add Berkeley header
e
s 00001/00001/00353
d D 5.2 88/04/24 15:22:33 bostic 4 3
c fix for ANSI C
e
s 00007/00001/00347
d D 5.1 86/01/29 16:37:37 mckusick 3 2
c add copyright
e
s 00027/00026/00321
d D 4.2 83/05/27 00:35:11 layer 2 1
c finished conversion to 4.1c
e
s 00347/00000/00000
d D 4.1 83/03/23 15:25:42 mckusick 1 0
c date and time created 83/03/23 15:25:42 by mckusick
e
u
U
t
T
I 1
D 3
/*	%W%	(Berkeley)	%E%	*/
E 3
I 3
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
E 5
 *
I 5
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 6
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 3

D 5
#
E 5
/*
**  Global Declarations
**
**	Virtually all non-local variable declarations are made in this
**	file.  Exceptions are those things which are initialized, which
**	are defined in "externs.c", and things which are local to one
**	program file.
**
**	So far as I know, nothing in here must be preinitialized to
**	zero.
**
**	You may have problems from the loader if you move this to a
**	different machine.  These things actually get allocated in each
**	source file, which UNIX allows; however, you may (on other
**	systems) have to change everything in here to be "extern" and
**	actually allocate stuff in "externs.c"
*/

/* external function definitions */
extern double	franf();	/* floating random number function */
extern double	sqrt();		/* square root */
extern double	sin(), cos();	/* trig functions */
extern double	atan2();	/* fancy arc tangent function */
extern double	log();		/* log base e */
extern double	pow();		/* power function */
extern double	fabs();		/* absolute value function */
extern double	exp();		/* exponential function */

/*********************  GALAXY  **************************/

/* galactic parameters */
# define	NSECTS		10	/* dimensions of quadrant in sectors */
# define	NQUADS		8	/* dimension of galazy in quadrants */
# define	NINHAB		32	/* number of quadrants which are inhabited */

struct quad		/* definition for each quadrant */
{
	char	bases;		/* number of bases in this quadrant */
	char	klings;		/* number of Klingons in this quadrant */
	char	holes;		/* number of black holes in this quadrant */
	int	scanned;	/* star chart entry (see below) */
	char	stars;		/* number of stars in this quadrant */
D 2
	char	systemname;	/* starsystem name (see below) */
E 2
I 2
	char	qsystemname;	/* starsystem name (see below) */
E 2
};

# define	Q_DISTRESSED	0200
# define	Q_SYSTEM	077

/*  systemname conventions:
 *	1 -> NINHAB	index into Systemname table for live system.
 *	+ Q_DISTRESSED	distressed starsystem -- systemname & Q_SYSTEM
 *			is the index into the Event table which will
 *			have the system name
 *	0		dead or nonexistent starsystem
 *
 *  starchart ("scanned") conventions:
 *	0 -> 999	taken as is
 *	-1		not yet scanned ("...")
 *	1000		supernova ("///")
 *	1001		starbase + ??? (".1.")
*/

/* ascii names of systems */
extern char	*Systemname[NINHAB];

/* quadrant definition */
struct quad	Quad[NQUADS][NQUADS];

/* defines for sector map  (below) */
# define	EMPTY		'.'
# define	STAR		'*'
# define	BASE		'#'
# define	ENTERPRISE	'E'
# define	QUEENE		'Q'
# define	KLINGON		'K'
# define	INHABIT		'@'
# define	HOLE		' '

/* current sector map */
char	Sect[NSECTS][NSECTS];


/************************ DEVICES ******************************/

# define	NDEV		16	/* max number of devices */

/* device tokens */
# define	WARP		0	/* warp engines */
# define	SRSCAN		1	/* short range scanners */
# define	LRSCAN		2	/* long range scanners */
# define	PHASER		3	/* phaser control */
# define	TORPED		4	/* photon torpedo control */
# define	IMPULSE		5	/* impulse engines */
# define	SHIELD		6	/* shield control */
# define	COMPUTER	7	/* on board computer */
# define	SSRADIO		8	/* subspace radio */
# define	LIFESUP		9	/* life support systems */
# define	SINS		10	/* Space Inertial Navigation System */
# define	CLOAK		11	/* cloaking device */
# define	XPORTER		12	/* transporter */
# define	SHUTTLE		13	/* shuttlecraft */

/* device names */
struct device
{
	char	*name;		/* device name */
	char	*person;	/* the person who fixes it */
};

struct device	Device[NDEV];

/***************************  EVENTS  ****************************/

# define	NEVENTS		12	/* number of different event types */

# define	E_LRTB		1	/* long range tractor beam */
# define	E_KATSB		2	/* Klingon attacks starbase */
# define	E_KDESB		3	/* Klingon destroys starbase */
# define	E_ISSUE		4	/* distress call is issued */
# define	E_ENSLV		5	/* Klingons enslave a quadrant */
# define	E_REPRO		6	/* a Klingon is reproduced */
# define	E_FIXDV		7	/* fix a device */
# define	E_ATTACK	8	/* Klingon attack during rest period */
# define	E_SNAP		9	/* take a snapshot for time warp */
# define	E_SNOVA		10	/* supernova occurs */

# define	E_GHOST		0100	/* ghost of a distress call if ssradio out */
# define	E_HIDDEN	0200	/* event that is unreportable because ssradio out */
# define	E_EVENT		077	/* mask to get event code */

struct event
{
	char	x, y;			/* coordinates */
D 2
	float	date;			/* trap stardate */
E 2
I 2
	double	date;			/* trap stardate */
E 2
	char	evcode;			/* event type */
	char	systemname;		/* starsystem name */
};
/* systemname conventions:
 *	1 -> NINHAB	index into Systemname table for reported distress calls
 *
 * evcode conventions:
 *	1 -> NEVENTS-1	event type
 *	+ E_HIDDEN	unreported (SSradio out)
 *	+ E_GHOST	actually already expired
 *	0		unallocated
 */

# define	MAXEVENTS	25	/* max number of concurrently pending events */

struct event	Event[MAXEVENTS];	/* dynamic event list; one entry per pending event */

/*****************************  KLINGONS  *******************************/

struct kling
{
	char	x, y;		/* coordinates */
	int	power;		/* power left */
D 2
	float	dist;		/* distance to Enterprise */
	float	avgdist;	/* average over this move */
E 2
I 2
	double	dist;		/* distance to Enterprise */
	double	avgdist;	/* average over this move */
E 2
	char	srndreq;	/* set if surrender has been requested */
};

# define	MAXKLQUAD	9	/* maximum klingons per quadrant */

/********************** MISCELLANEOUS ***************************/

/* condition codes */
# define	GREEN		0
# define	DOCKED		1
# define	YELLOW		2
# define	RED		3

/* starbase coordinates */
# define	MAXBASES	9	/* maximum number of starbases in galaxy */

/*  distress calls  */
# define	MAXDISTR	5	/* maximum concurrent distress calls */

/* phaser banks */
# define	NBANKS		6	/* number of phaser banks */

struct xy
{
	char	x, y;		/* coordinates */
};


/*
 *	note that much of the stuff in the following structs CAN NOT
 *	be moved around!!!!
 */


/* information regarding the state of the starship */
struct
{
D 2
	float	warp;		/* warp factor */
	float	warp2;		/* warp factor squared */
	float	warp3;		/* warp factor cubed */
E 2
I 2
	double	warp;		/* warp factor */
	double	warp2;		/* warp factor squared */
	double	warp3;		/* warp factor cubed */
E 2
	char	shldup;		/* shield up flag */
	char	cloaked;	/* set if cloaking device on */
	int	energy;		/* starship's energy */
	int	shield;		/* energy in shields */
D 2
	float	reserves;	/* life support reserves */
E 2
I 2
	double	reserves;	/* life support reserves */
E 2
	int	crew;		/* ship's complement */
	int	brigfree;	/* space left in brig */
	char	torped;		/* torpedoes */
	char	cloakgood;	/* set if we have moved */
	int	quadx;		/* quadrant x coord */
	int	quady;		/* quadrant y coord */
	int	sectx;		/* sector x coord */
	int	secty;		/* sector y coord */
	char	cond;		/* condition code */
	char	sinsbad;	/* Space Inertial Navigation System condition */
	char	*shipname;	/* name of current starship */
	char	ship;		/* current starship */
I 2
D 4
	int	distressed	/* number of distress calls */
E 4
I 4
	int	distressed;	/* number of distress calls */
E 4
E 2
}	Ship;

/* sinsbad is set if SINS is working but not calibrated */

/* game related information, mostly scoring */
struct
{
	int	killk;		/* number of klingons killed */
	int	deaths;		/* number of deaths onboard Enterprise */
	char	negenbar;	/* number of hits on negative energy barrier */
	char	killb;		/* number of starbases killed */
	int	kills;		/* number of stars killed */
	char	skill;		/* skill rating of player */
	char	length;		/* length of game */
	char	killed;		/* set if you were killed */
	char	killinhab;	/* number of inhabited starsystems killed */
	char	tourn;		/* set if a tournament game */
	char	passwd[15];	/* game password */
	char	snap;		/* set if snapshot taken */
	char	helps;		/* number of help calls */
	int	captives;	/* total number of captives taken */
}	Game;

/* per move information */
struct
{
	char	free;		/* set if a move is free */
	char	endgame;	/* end of game flag */
	char	shldchg;	/* set if shields changed this move */
	char	newquad;	/* set if just entered this quadrant */
	char	resting;	/* set if this move is a rest */
D 2
	float	time;		/* time used this move */
E 2
I 2
	double	time;		/* time used this move */
E 2
}	Move;

/* parametric information */
struct
{
	char	bases;		/* number of starbases */
	char	klings;		/* number of klingons */
D 2
	float	date;		/* stardate */
	float	time;		/* time left */
	float	resource;	/* Federation resources */
E 2
I 2
	double	date;		/* stardate */
	double	time;		/* time left */
	double	resource;	/* Federation resources */
E 2
	int	energy;		/* starship's energy */
	int	shield;		/* energy in shields */
D 2
	float	reserves;	/* life support reserves */
E 2
I 2
	double	reserves;	/* life support reserves */
E 2
	int	crew;		/* size of ship's complement */
	int	brigfree;	/* max possible number of captives */
	char	torped;		/* photon torpedos */
D 2
	float	damfac[NDEV];	/* damage factor */
	float	dockfac;	/* docked repair time factor */
	float	regenfac;	/* regeneration factor */
E 2
I 2
	double	damfac[NDEV];	/* damage factor */
	double	dockfac;	/* docked repair time factor */
	double	regenfac;	/* regeneration factor */
E 2
	int	stopengy;	/* energy to do emergency stop */
	int	shupengy;	/* energy to put up shields */
	int	klingpwr;	/* Klingon initial power */
	int	warptime;	/* time chewer multiplier */
D 2
	float	phasfac;	/* Klingon phaser power eater factor */
E 2
I 2
	double	phasfac;	/* Klingon phaser power eater factor */
E 2
	char	moveprob[6];	/* probability that a Klingon moves */
D 2
	float	movefac[6];	/* Klingon move distance multiplier */
	float	eventdly[NEVENTS];	/* event time multipliers */
	float	navigcrud[2];	/* navigation crudup factor */
E 2
I 2
	double	movefac[6];	/* Klingon move distance multiplier */
	double	eventdly[NEVENTS];	/* event time multipliers */
	double	navigcrud[2];	/* navigation crudup factor */
E 2
	int	cloakenergy;	/* cloaking device energy per stardate */
D 2
	float	damprob[NDEV];	/* damage probability */
	float	hitfac;		/* Klingon attack factor */
E 2
I 2
	double	damprob[NDEV];	/* damage probability */
	double	hitfac;		/* Klingon attack factor */
E 2
	int	klingcrew;	/* number of Klingons in a crew */
D 2
	float	srndrprob;	/* surrender probability */
E 2
I 2
	double	srndrprob;	/* surrender probability */
E 2
	int	energylow;	/* low energy mark (cond YELLOW) */
}	Param;

/* Sum of damage probabilities must add to 1000 */

/* other information kept in a snapshot */
struct
{
	char	bases;		/* number of starbases */
	char	klings;		/* number of klingons */
D 2
	float	date;		/* stardate */
	float	time;		/* time left */
	float	resource;	/* Federation resources */
E 2
I 2
	double	date;		/* stardate */
	double	time;		/* time left */
	double	resource;	/* Federation resources */
E 2
	char	distressed;	/* number of currently distressed quadrants */
	struct event	*eventptr[NEVENTS];	/* pointer to event structs */
	struct xy	base[MAXBASES];		/* locations of starbases */
}	Now;

/* Other stuff, not dumped in a snapshot */
struct
{
	struct kling	klingon[MAXKLQUAD];	/* sorted Klingon list */
	char		nkling;			/* number of Klingons in this sector */
						/* < 0 means automatic override mode */
	char		fast;			/* set if speed > 300 baud */
	struct xy	starbase;	/* starbase in current quadrant */
	char		snapshot[sizeof Quad + sizeof Event + sizeof Now];	/* snapshot for time warp */
	char		statreport;		/* set to get a status report on a srscan */
}	Etc;

/*
 *	eventptr is a pointer to the event[] entry of the last
 *	scheduled event of each type.  Zero if no such event scheduled.
 */

/* Klingon move indicies */
# define	KM_OB		0	/* Old quadrant, Before attack */
# define	KM_OA		1	/* Old quadrant, After attack */
# define	KM_EB		2	/* Enter quadrant, Before attack */
# define	KM_EA		3	/* Enter quadrant, After attack */
# define	KM_LB		4	/* Leave quadrant, Before attack */
# define	KM_LA		5	/* Leave quadrant, After attack */

/* you lose codes */
# define	L_NOTIME	1	/* ran out of time */
# define	L_NOENGY	2	/* ran out of energy */
# define	L_DSTRYD	3	/* destroyed by a Klingon */
# define	L_NEGENB	4	/* ran into the negative energy barrier */
# define	L_SUICID	5	/* destroyed in a nova */
# define	L_SNOVA		6	/* destroyed in a supernova */
# define	L_NOLIFE	7	/* life support died (so did you) */
# define	L_NOHELP	8	/* you could not be rematerialized */
# define	L_TOOFAST	9	/* pretty stupid going at warp 10 */
# define	L_STAR		10	/* ran into a star */
# define	L_DSTRCT	11	/* self destructed */
# define	L_CAPTURED	12	/* captured by Klingons */
# define	L_NOCREW	13	/* you ran out of crew */

/******************  COMPILE OPTIONS  ***********************/

/* Trace info */
# define	xTRACE		1
int	Trace;
E 1
