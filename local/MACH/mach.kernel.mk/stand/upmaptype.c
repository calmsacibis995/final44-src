/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * $Log:	upmaptype.c,v $
 * Revision 2.3  89/03/09  21:18:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:36:53  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)upmaptype.c	7.1 (Berkeley) 6/5/86
 */

/*
 * UNIBUS peripheral standalone
 * driver: drive type mapping routine.
 */

#include <sys/param.h> 
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/dkbad.h>
#include <sys/vmmac.h>

#include <vax/pte.h>
#include <vaxuba/upreg.h>
#include <vaxuba/ubareg.h>

#include "saio.h"
#include "savax.h"

static short	up9300_off[] = { 0, 27, 0, -1, -1, -1, 562, 82 };
static short	fj_off[] = { 0, 50, 0, -1, -1, -1, 155, -1 };
static short	upam_off[] = { 0, 32, 0, 668, 723, 778, 668, 98 };
static short	up980_off[] = { 0, 100, 0, -1, -1 , -1, 309, -1};
static short	eagle_off[8] =	{ 0, 17, 0, 391, 408, 728, 391, 87 };

struct st upst[] = {
	32,	19,	32*19,	815,	up9300_off,	/* 9300 */
	32,	19,	32*19,	823,	up9300_off,	/* 9766 */
	32,	10,	32*10,	823,	fj_off,		/* Fuji 160 */
	32,	16,	32*16,	1024,	upam_off,	/* Capricorn */
	32,	5,	32*5,	823,	up980_off,	/* DM980 */
	48,	20,	48*20,	842,	eagle_off,	/* Fuji Eagle */
	0,	0,	0,	0,	0,
};

upmaptype(unit, upaddr)
	int unit;
	register struct updevice *upaddr;
{
	register struct st *st;
	int type = -1;

	upaddr->upcs1 = 0;
	upaddr->upcs2 = unit % 8;
	upaddr->uphr = UPHR_MAXTRAK;
	for (st = upst; st->ntrak != 0; st++)
		if (upaddr->uphr == st->ntrak - 1) {
			type = st - upst;
			break;
		}
	if (st->ntrak == 0)
		printf("up%d: uphr=%x\n", unit, upaddr->uphr);
	if (type == 0) {
		upaddr->uphr = UPHR_MAXCYL;
		if (upaddr->uphr == 822)	/* CDC 9766 */
			type++;
	}
	upaddr->upcs2 = UPCS2_CLR;
	return (type);
}
