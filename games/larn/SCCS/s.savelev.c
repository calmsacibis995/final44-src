h53693
s 00000/00047/00000
d R 5.2 91/06/04 16:58:52 sellgren 2 1
c remove brain damaged "storage" of dungeon levels
e
s 00047/00000/00000
d D 5.1 89/03/05 18:59:30 bostic 1 0
c date and time created 89/03/05 18:59:30 by bostic
e
u
U
t
T
I 1
/* savelev.c		 Larn is copyrighted 1986 by Noah Morgan. */
#include "header.h"
extern struct cel *cell;

/*
 *	routine to save the present level into storage
 */
savelevel()
	{
	register struct cel *pcel;
	register char *pitem,*pknow,*pmitem;
	register short *phitp,*piarg;
	register struct cel *pecel;
	pcel = &cell[level*MAXX*MAXY];	/* pointer to this level's cells */
	pecel = pcel + MAXX*MAXY;	/* pointer to past end of this level's cells */
	pitem=item[0]; piarg=iarg[0]; pknow=know[0]; pmitem=mitem[0]; phitp=hitp[0];
	while (pcel < pecel)
		{
		pcel->mitem  = *pmitem++;
		pcel->hitp   = *phitp++;
		pcel->item   = *pitem++;
		pcel->know   = *pknow++;
		pcel++->iarg = *piarg++;
		}
	}

/*
 *	routine to restore a level from storage
 */
getlevel()
	{
	register struct cel *pcel;
	register char *pitem,*pknow,*pmitem;
	register short *phitp,*piarg;
	register struct cel *pecel;
	pcel = &cell[level*MAXX*MAXY];	/* pointer to this level's cells */
	pecel = pcel + MAXX*MAXY;	/* pointer to past end of this level's cells */
	pitem=item[0]; piarg=iarg[0]; pknow=know[0]; pmitem=mitem[0]; phitp=hitp[0];
	while (pcel < pecel)
		{
		*pmitem++ = pcel->mitem;
		*phitp++ = pcel->hitp;
		*pitem++ = pcel->item;
		*pknow++ = pcel->know;
		*piarg++ = pcel++->iarg;
		}
	}
E 1
