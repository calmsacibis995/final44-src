h13951
s 00002/00002/00110
d D 8.1 93/05/31 15:54:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00107
d D 5.2 93/05/12 14:04:02 bostic 4 3
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00015/00004/00097
d D 5.1 91/04/08 17:08:13 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00101
d D 4.1 82/05/11 14:41:10 rrh 2 1
c release version 4.1
e
s 00101/00000/00000
d D 1.1 82/05/11 14:34:48 rrh 1 0
c date and time created 82/05/11 14:34:48 by rrh
e
u
U
t
T
I 1
D 3
#
/*      Re-coding of advent in C: termination routines                  */
E 3
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1991, 1993 The Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
 * The game adventure was original written Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by
 * Jim Gillogly.
E 4
I 4
 * The game adventure was originally written in Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by Jim
 * Gillogly.  This code is derived from software contributed to Berkeley
 * by Jim Gillogly at The Rand Corporation.
E 4
 *
 * %sccs.include.redist.c%
 */
E 3

D 3
static char sccsid[] = "	%M%	%I%	%E%	";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

I 3
/*      Re-coding of advent in C: termination routines                  */
E 3

D 3
# include "hdr.h"
E 3
I 3
#include "hdr.h"
E 3

score()                                         /* sort of like 20000   */
{       register int scor,i;
	mxscor=scor=0;
	for (i=50; i<=maxtrs; i++)
	{	if (ptext[i].txtlen==0) continue;
		k=12;
		if (i==chest) k=14;
		if (i>chest) k=16;
		if (prop[i]>=0) scor += 2;
		if (place[i]==3&&prop[i]==0) scor += k-2;
		mxscor += k;
	}
	scor += (maxdie-numdie)*10;
	mxscor += maxdie*10;
	if (!(scorng||gaveup)) scor += 4;
	mxscor += 4;
	if (dflag!=0) scor += 25;
	mxscor += 25;
	if (closng) scor += 25;
	mxscor += 25;
	if (closed)
	{       if (bonus==0) scor += 10;
		if (bonus==135) scor += 25;
		if (bonus==134) scor += 30;
		if (bonus==133) scor += 45;
	}
	mxscor += 45;
	if (place[magzin]==108) scor++;
	mxscor++;
	scor += 2;
	mxscor += 2;
	for (i=1; i<=hntmax; i++)
		if (hinted[i]) scor -= hints[i][2];
	return(scor);
}

done(entry)     /* entry=1 means goto 13000 */  /* game is over         */
int entry;      /* entry=2 means goto 20000 */ /* 3=19000 */
{       register int i,sc;
	if (entry==1) mspeak(1);
	if (entry==3) rspeak(136);
	printf("\n\n\nYou scored %d out of a ",(sc=score()));
	printf("possible %d using %d turns.\n",mxscor,turns);
	for (i=1; i<=clsses; i++)
		if (cval[i]>=sc)
		{       speak(&ctext[i]);
			if (i==clsses-1)
			{       printf("To achieve the next higher rating");
				printf(" would be a neat trick!\n\n");
				printf("Congratulations!!\n");
				exit(0);
			}
			k=cval[i]+1-sc;
			printf("To achieve the next higher rating, you need");
			printf(" %d more point",k);
			if (k==1) printf(".\n");
			else printf("s.\n");
			exit(0);
		}
	printf("You just went off my scale!!!\n");
	exit(0);
}


die(entry)                                      /* label 90             */
int entry;
{       register int i;
	if (entry != 99)
	{       rspeak(23);
		oldlc2=loc;
	}
	if (closng)                             /* 99                   */
	{       rspeak(131);
		numdie++;
		done(2);
	}
	yea=yes(81+numdie*2,82+numdie*2,54);
	numdie++;
	if (numdie==maxdie || !yea) done(2);
	place[water]=0;
	place[oil]=0;
	if (toting(lamp)) prop[lamp]=0;
	for (i=100; i>=1; i--)
	{       if (!toting(i)) continue;
		k=oldlc2;
		if (i==lamp) k=1;
		drop(i,k);
	}
	loc=3;
	oldloc=loc;
	return(2000);
}
D 4

E 4
E 1
