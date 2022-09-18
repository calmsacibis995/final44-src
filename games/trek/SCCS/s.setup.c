h50160
s 00002/00002/00275
d D 8.1 93/05/31 17:57:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00276
d D 5.4 90/06/01 13:26:01 bostic 6 5
c new copyright notice
e
s 00010/00005/00277
d D 5.3 88/06/18 15:08:16 bostic 5 4
c install approved copyright notice
e
s 00009/00003/00273
d D 5.2 88/05/05 18:34:40 bostic 4 3
c written by Eric Allman; add Berkeley header
e
s 00007/00001/00269
d D 5.1 86/01/29 16:36:58 mckusick 3 2
c add copyright
e
s 00022/00022/00248
d D 4.2 83/05/27 14:58:04 layer 2 1
c git rid of compiler warns
e
s 00270/00000/00000
d D 4.1 83/03/23 15:01:18 mckusick 1 0
c date and time created 83/03/23 15:01:18 by mckusick
e
u
U
t
T
I 3
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
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
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

# include	"trek.h"
# include	"getpar.h"

/*
**  INITIALIZE THE GAME
**
**	The length, skill, and password are read, and the game
**	is initialized.  It is far too difficult to describe all
**	that goes on in here, but it is all straight-line code;
**	give it a look.
**
**	Game restart and tournament games are handled here.
*/

D 2
struct cvntab	Lentab[]
E 2
I 2
struct cvntab	Lentab[] =
E 2
{
D 2
	"s",		"hort",			1,		0,
	"m",		"edium",		2,		0,
	"l",		"ong",			4,		0,
E 2
I 2
	"s",		"hort",			(int (*)())1,		0,
	"m",		"edium",		(int (*)())2,		0,
	"l",		"ong",			(int (*)())4,		0,
E 2
	"restart",	"",			0,		0,
	0
};

D 2
struct cvntab	Skitab[]
E 2
I 2
struct cvntab	Skitab[] =
E 2
{
D 2
	"n",		"ovice",		1,		0,
	"f",		"air",			2,		0,
	"g",		"ood",			3,		0,
	"e",		"xpert",		4,		0,
	"c",		"ommodore",		5,		0,
	"i",		"mpossible",		6,		0,
E 2
I 2
	"n",		"ovice",		(int (*)())1,		0,
	"f",		"air",			(int (*)())2,		0,
	"g",		"ood",			(int (*)())3,		0,
	"e",		"xpert",		(int (*)())4,		0,
	"c",		"ommodore",		(int (*)())5,		0,
	"i",		"mpossible",		(int (*)())6,		0,
E 2
	0
};

setup()
{
	struct cvntab		*r;
	register int		i, j;
D 2
	float			f;
E 2
I 2
	double			f;
E 2
	int			d;
	int			fd;
	int			klump;
	int			ix, iy;
	register struct quad	*q;
	struct event		*e;

	while (1)
	{
		r = getcodpar("What length game", Lentab);
D 2
		Game.length = r->value;
E 2
I 2
		Game.length = (int) r->value;
E 2
		if (Game.length == 0)
		{
			if (restartgame())
				continue;
			return;
		}
		break;
	}
	r = getcodpar("What skill game", Skitab);
D 2
	Game.skill = r->value;
E 2
I 2
	Game.skill = (int) r->value;
E 2
	Game.tourn = 0;
	getstrpar("Enter a password", Game.passwd, 14, 0);
	if (sequal(Game.passwd, "tournament"))
	{
		getstrpar("Enter tournament code", Game.passwd, 14, 0);
		Game.tourn = 1;
		d = 0;
		for (i = 0; Game.passwd[i]; i++)
D 2
			d =+ Game.passwd[i] << i;
E 2
I 2
			d += Game.passwd[i] << i;
E 2
		srand(d);
	}
	Param.bases = Now.bases = ranf(6 - Game.skill) + 2;
	if (Game.skill == 6)
		Param.bases = Now.bases = 1;
	Param.time = Now.time = 6.0 * Game.length + 2.0;
	i = Game.skill;
	j = Game.length;
	Param.klings = Now.klings = i * j * 3.5 * (franf() + 0.75);
	if (Param.klings < i * j * 5)
		Param.klings = Now.klings = i * j * 5;
	if (Param.klings <= i)		/* numerical overflow problems */
		Param.klings = Now.klings = 127;
	Param.energy = Ship.energy = 5000;
	Param.torped = Ship.torped = 10;
	Ship.ship = ENTERPRISE;
	Ship.shipname = "Enterprise";
	Param.shield = Ship.shield = 1500;
	Param.resource = Now.resource = Param.klings * Param.time;
	Param.reserves = Ship.reserves = (6 - Game.skill) * 2.0;
	Param.crew = Ship.crew = 387;
	Param.brigfree = Ship.brigfree = 400;
	Ship.shldup = 1;
	Ship.cond = GREEN;
	Ship.warp = 5.0;
	Ship.warp2 = 25.0;
	Ship.warp3 = 125.0;
	Ship.sinsbad = 0;
	Ship.cloaked = 0;
	Param.date = Now.date = (ranf(20) + 20) * 100;
	f = Game.skill;
	f = log(f + 0.5);
	for (i = 0; i < NDEV; i++)
		if (Device[i].name[0] == '*')
			Param.damfac[i] = 0;
		else
			Param.damfac[i] = f;
	/* these probabilities must sum to 1000 */
	Param.damprob[WARP] = 70;	/* warp drive		 7.0% */
	Param.damprob[SRSCAN] = 110;	/* short range scanners	11.0% */
	Param.damprob[LRSCAN] = 110;	/* long range scanners	11.0% */
	Param.damprob[PHASER] = 125;	/* phasers		12.5% */
	Param.damprob[TORPED] = 125;	/* photon torpedoes	12.5% */
	Param.damprob[IMPULSE] = 75;	/* impulse engines	 7.5% */
	Param.damprob[SHIELD] = 150;	/* shield control	15.0% */
	Param.damprob[COMPUTER] = 20;	/* computer		 2.0% */
	Param.damprob[SSRADIO] = 35;	/* subspace radio	 3.5% */
	Param.damprob[LIFESUP] = 30;	/* life support		 3.0% */
	Param.damprob[SINS] = 20;	/* navigation system	 2.0% */
	Param.damprob[CLOAK] = 50;	/* cloaking device	 5.0% */
	Param.damprob[XPORTER] = 80;	/* transporter		 8.0% */
	/* check to see that I didn't blow it */
	for (i = j = 0; i < NDEV; i++)
D 2
		j =+ Param.damprob[i];
E 2
I 2
		j += Param.damprob[i];
E 2
	if (j != 1000)
		syserr("Device probabilities sum to %d", j);
	Param.dockfac = 0.5;
	Param.regenfac = (5 - Game.skill) * 0.05;
	if (Param.regenfac < 0.0)
		Param.regenfac = 0.0;
	Param.warptime = 10;
	Param.stopengy = 50;
	Param.shupengy = 40;
	i = Game.skill;
	Param.klingpwr = 100 + 150 * i;
	if (i >= 6)
D 2
		Param.klingpwr =+ 150;
E 2
I 2
		Param.klingpwr += 150;
E 2
	Param.phasfac = 0.8;
	Param.hitfac = 0.5;
	Param.klingcrew = 200;
	Param.srndrprob = 0.0035;
	Param.moveprob[KM_OB] = 45;
	Param.movefac[KM_OB] = .09;
	Param.moveprob[KM_OA] = 40;
	Param.movefac[KM_OA] = -0.05;
	Param.moveprob[KM_EB] = 40;
	Param.movefac[KM_EB] = 0.075;
	Param.moveprob[KM_EA] = 25 + 5 * Game.skill;
	Param.movefac[KM_EA] = -0.06 * Game.skill;
	Param.moveprob[KM_LB] = 0;
	Param.movefac[KM_LB] = 0.0;
	Param.moveprob[KM_LA] = 10 + 10 * Game.skill;
	Param.movefac[KM_LA] = 0.25;
	Param.eventdly[E_SNOVA] = 0.5;
	Param.eventdly[E_LRTB] = 25.0;
	Param.eventdly[E_KATSB] = 1.0;
	Param.eventdly[E_KDESB] = 3.0;
	Param.eventdly[E_ISSUE] = 1.0;
	Param.eventdly[E_SNAP] = 0.5;
	Param.eventdly[E_ENSLV] = 0.5;
	Param.eventdly[E_REPRO] = 2.0;
	Param.navigcrud[0] = 1.50;
	Param.navigcrud[1] = 0.75;
	Param.cloakenergy = 1000;
	Param.energylow = 1000;
	for (i = 0; i < MAXEVENTS; i++)
	{
		e = &Event[i];
		e->date = 1e50;
		e->evcode = 0;
	}
	xsched(E_SNOVA, 1, 0, 0, 0);
	xsched(E_LRTB, Param.klings, 0, 0, 0);
	xsched(E_KATSB, 1, 0, 0, 0);
	xsched(E_ISSUE, 1, 0, 0, 0);
	xsched(E_SNAP, 1, 0, 0, 0);
	Ship.sectx = ranf(NSECTS);
	Ship.secty = ranf(NSECTS);
	Game.killk = Game.kills = Game.killb = 0;
	Game.deaths = Game.negenbar = 0;
	Game.captives = 0;
	Game.killinhab = 0;
	Game.helps = 0;
	Game.killed = 0;
	Game.snap = 0;
	Move.endgame = 0;

	/* setup stars */
	for (i = 0; i < NQUADS; i++)
		for (j = 0; j < NQUADS; j++)
		{
			q = &Quad[i][j];
			q->klings = q->bases = 0;
			q->scanned = -1;
			q->stars = ranf(9) + 1;
			q->holes = ranf(3) - q->stars / 5;
D 2
			q->systemname = 0;
E 2
I 2
			q->qsystemname = 0;
E 2
		}

	/* select inhabited starsystems */
	for (d = 1; d < NINHAB; d++)
	{
		do
		{
			i = ranf(NQUADS);
			j = ranf(NQUADS);
			q = &Quad[i][j];
D 2
		} while (q->systemname);
		q->systemname = d;
E 2
I 2
		} while (q->qsystemname);
		q->qsystemname = d;
E 2
	}

	/* position starbases */
	for (i = 0; i < Param.bases; i++)
	{
		while (1)
		{
			ix = ranf(NQUADS);
			iy = ranf(NQUADS);
			q = &Quad[ix][iy];
			if (q->bases > 0)
				continue;
			break;
		}
		q->bases = 1;
		Now.base[i].x = ix;
		Now.base[i].y = iy;
		q->scanned = 1001;
		/* start the Enterprise near starbase */
		if (i == 0)
		{
			Ship.quadx = ix;
			Ship.quady = iy;
		}
	}

	/* position klingons */
	for (i = Param.klings; i > 0; )
	{
		klump = ranf(4) + 1;
		if (klump > i)
			klump = i;
		while (1)
		{
			ix = ranf(NQUADS);
			iy = ranf(NQUADS);
			q = &Quad[ix][iy];
			if (q->klings + klump > MAXKLQUAD)
				continue;
D 2
			q->klings =+ klump;
			i =- klump;
E 2
I 2
			q->klings += klump;
			i -= klump;
E 2
			break;
		}
	}

	/* initialize this quadrant */
	printf("%d Klingons\n%d starbase", Param.klings, Param.bases);
	if (Param.bases > 1)
		printf("s");
	printf(" at %d,%d", Now.base[0].x, Now.base[0].y);
	for (i = 1; i < Param.bases; i++)
		printf(", %d,%d", Now.base[i].x, Now.base[i].y);
	printf("\nIt takes %d units to kill a Klingon\n", Param.klingpwr);
	Move.free = 0;
	initquad(0);
	srscan(1);
	attack(0);
}
E 1
