h58323
s 00038/00000/00000
d D 5.1 90/05/02 08:40:45 bostic 1 0
c date and time created 90/05/02 08:40:45 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* hack.track.c - version 1.0.2 */

#include "hack.h"

#define	UTSZ	50

coord utrack[UTSZ];
int utcnt = 0;
int utpnt = 0;

initrack(){
	utcnt = utpnt = 0;
}

/* add to track */
settrack(){
	if(utcnt < UTSZ) utcnt++;
	if(utpnt == UTSZ) utpnt = 0;
	utrack[utpnt].x = u.ux;
	utrack[utpnt].y = u.uy;
	utpnt++;
}

coord *
gettrack(x,y) register x,y; {
register int i,cnt,dist;
coord tc;
	cnt = utcnt;
	for(i = utpnt-1; cnt--; i--){
		if(i == -1) i = UTSZ-1;
		tc = utrack[i];
		dist = (x-tc.x)*(x-tc.x) + (y-tc.y)*(y-tc.y);
		if(dist < 3)
			return(dist ? &(utrack[i]) : 0);
	}
	return(0);
}
E 1
