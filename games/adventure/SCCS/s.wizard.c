h13811
s 00002/00002/00105
d D 8.1 93/06/02 19:13:59 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00106
d D 5.3 93/06/02 19:13:39 bostic 6 4
c adventure uses 'start' and conflicts with 'start' in crt0.s on MIPS
e
s 00002/00002/00105
d R 8.1 93/05/31 15:55:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00031/00079
d D 5.2 93/05/12 14:04:16 bostic 4 3
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00015/00003/00095
d D 5.1 91/04/08 17:08:32 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00098
d D 4.1 82/05/11 14:42:29 rrh 2 1
c release version 4.1
e
s 00098/00000/00000
d D 1.1 82/05/11 14:35:20 rrh 1 0
c date and time created 82/05/11 14:35:20 by rrh
e
u
U
t
T
I 1
D 3
#
/*      Re-coding of advent in C: privileged operations                 */
E 3
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
E 4
I 4
D 7
 * Copyright (c) 1991, 1993 The Regents of the University of California.
E 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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

/*      Re-coding of advent in C: privileged operations                 */
E 3

# include "hdr.h"

datime(d,t)
int *d,*t;
{       int tvec[2],*tptr;
	int *localtime();
I 4

E 4
	time(tvec);
	tptr=localtime(tvec);
	*d=tptr[7]+365*(tptr[5]-77);    /* day since 1977  (mod leap)   */
	/* bug: this will overflow in the year 2066 AD                  */
	/* it will be attributed to Wm the C's millenial celebration    */
	*t=tptr[2]*60+tptr[1];          /* and minutes since midnite    */
}                                       /* pretty painless              */


D 4
char *magic;
E 4
I 4
char magic[6];
E 4

poof()
D 4
{       magic="dwarf";
	latncy=45;
E 4
I 4
{
	strcpy(magic, DECR(d,w,a,r,f));
	latncy = 45;
E 4
}

D 6
start(n)
E 6
I 6
Start(n)
E 6
{       int d,t,delay;
I 4

E 4
	datime(&d,&t);
D 4
	delay=(d-saved)*1440+(t-savet); /* good for about a month       */
	if (delay>=latncy || setup >= 0)
	{       saved= -1;
E 4
I 4
	delay=(d-saved)*1440+(t-savet); /* good for about a month     */

	if (delay >= latncy)
	{       saved = -1;
E 4
		return(FALSE);
	}
D 4
	printf("This adventure was suspended a mere %d minutes ago.",delay);
	if (delay<=latncy/3)
E 4
I 4
	printf("This adventure was suspended a mere %d minute%s ago.",
		delay, delay == 1? "" : "s");
	if (delay <= latncy/3)
E 4
	{       mspeak(2);
		exit(0);
	}
	mspeak(8);
	if (!wizard())
	{       mspeak(9);
		exit(0);
	}
	saved = -1;
	return(FALSE);
}

wizard()                /* not as complex as advent/10 (for now)        */
{       register int wiz;
	char *word,*x;
	if (!yesm(16,0,7)) return(FALSE);
	mspeak(17);
	getin(&word,&x);
	if (!weq(word,magic))
	{       mspeak(20);
		return(FALSE);
	}
	mspeak(19);
	return(TRUE);
}

ciao(cmdfile)
char *cmdfile;
{       register char *c;
	register int outfd, size;
	char fname[80], buf[512];
	extern unsigned filesize;

D 4
	lseek(datfd,(long)filesize,0);
	for (;;)
	{       printf("What would you like to call the saved version?\n");
		for (c=fname;; c++)
			if ((*c=getchar())=='\n') break;
		*c=0;
		if (save(cmdfile,fname)>=0) break;
		printf("I can't use that one.\n");
		return;
	}
	outfd=open(fname,1);
	lseek(outfd,0L,2);                /* end of executable file       */
	while ((size=read(datfd,buf,512))>0)
		write(outfd,buf,size);  /* copy the message data        */
	printf("                    ^\n");
	printf("That should do it.  Gis revido.\n");
E 4
I 4
	printf("What would you like to call the saved version?\n");
	for (c=fname;; c++)
		if ((*c=getchar())=='\n') break;
	*c=0;
	if (save(fname) != 0) return;           /* Save failed */
	printf("To resume, say \"adventure %s\".\n", fname);
	printf("\"With these rooms I might now have been familiarly acquainted.\"\n");
E 4
	exit(0);
}


D 4
ran(range)                              /* uses unix rng                */
int range;                              /* can't div by 32768 because   */
E 4
I 4
ran(range)
int range;
E 4
{
	long rand(), i;
I 4

E 4
	i = rand() % range;
	return(i);
}
D 4

E 4
E 1
