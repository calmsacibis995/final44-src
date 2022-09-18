h18331
s 00002/00002/00188
d D 8.1 93/06/02 19:14:04 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00189
d D 5.4 93/06/02 19:13:32 bostic 10 8
c adventure uses 'start' and conflicts with 'start' in crt0.s on MIPS
e
s 00002/00002/00188
d R 8.1 93/05/31 15:57:06 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00185
d D 5.3 93/05/31 15:57:02 bostic 8 5
c fix SCCS headers, copyright notice
e
s 00002/00002/00184
d R 8.1 93/05/31 15:55:57 bostic 7 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00184
d R 8.1 93/05/31 15:54:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00077/00083/00109
d D 5.2 93/05/12 14:04:08 bostic 5 4
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00015/00003/00177
d D 5.1 91/04/08 17:08:17 bostic 4 3
c new copyright; att/bsd/shared
e
s 00019/00020/00161
d D 4.2 89/03/05 20:20:57 bostic 3 2
c make this work with dm(8) -- fix is ugly, but the code is worse
e
s 00000/00000/00181
d D 4.1 82/05/11 14:41:46 rrh 2 1
c release version 4.1
e
s 00181/00000/00000
d D 1.1 82/05/11 14:34:52 rrh 1 0
c date and time created 82/05/11 14:34:52 by rrh
e
u
U
t
T
I 1
D 4
#
/*      Re-coding of advent in C: data initialization                   */
E 4
I 4
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
E 5
I 5
D 8
 * Copyright (c) 1991, 1993 The Regents of the University of California.
E 8
I 8
D 11
 * Copyright (c) 1993 The Regents of the University of California.
E 8
E 5
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 5
 * The game adventure was original written Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by
 * Jim Gillogly.
E 5
I 5
 * The game adventure was originally written in Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by Jim
 * Gillogly.  This code is derived from software contributed to Berkeley
 * by Jim Gillogly at The Rand Corporation.
E 5
 *
 * %sccs.include.redist.c%
 */
I 8

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
E 4

D 4
static char sccsid[] = "	%M%	%I%	%E%	";
E 4
I 4
D 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
/*      Re-coding of advent in C: data initialization                   */
E 4

D 3
# include "hdr.h"
E 3
I 3
#include <sys/types.h>
#include <stdio.h>
#include "hdr.h"
D 5
#include "pathnames.h"
E 5
E 3

int blklin = TRUE;
D 5
int setup  = 0;
E 5

int setbit[16] = {1,2,4,010,020,040,0100,0200,0400,01000,02000,04000,
		  010000,020000,040000,0100000};


init(command)                           /* everything for 1st time run  */
char *command;                          /* command we were called with  */
D 5
{       int stat,adfd;
E 5
I 5
{
E 5
	rdata();                        /* read data from orig. file    */
	linkdata();
	poof();
D 5
	setup=1;                        /* indicate that data is in     */
D 3
	if (confirm("got the data.  save as \"advent\"? "))
	{       if (save(command,"advent")<0)   /* save core image      */
		{       printf("Save failed\n");
			exit(0);
		}
E 3
I 3
	if (save(command, "adventure") < 0) {
		fprintf(stderr, "adventure: save failed\n");
		exit(1);
E 3
	}
D 3
	else exit(0);
	printf("Save succeeded.  Adding messages.\n");
	adfd=open("advent",1);
E 3
I 3
	adfd=open("adventure",1);
E 3
	lseek(adfd,0L,2);
	close(datfd);
D 3
	if (fork()==0)                  /* child process                */
	{       close(1);
		dup(adfd);              /* output goes to advent file   */
		execl("/bin/cat","cat",TMPFILE,0);
		printf("unable to find /bin/cat\n");
E 3
I 3
	if (vfork() == 0) {
		dup2(adfd, 1);
		execl(_PATH_CAT, "cat", TMPFILE, 0);
		fprintf(stderr, "adventure: unable to find %s\n", _PATH_CAT);
		exit(1);
E 3
	}
	wait(&stat);
	unlink(TMPFILE);
D 3
	printf("Advent is ready.\n");
	exit(0);
E 3
I 3
	exit(stat);
E 5
E 3
}

I 5
char *decr(a,b,c,d,e)
char a,b,c,d,e;
{
	static char buf[6];
E 5

I 5
	buf[0] = a-'+';
	buf[1] = b-'-';
	buf[2] = c-'#';
	buf[3] = d-'&';
	buf[4] = e-'%';
	buf[5] = 0;
	return buf;
}

E 5
linkdata()                              /*  secondary data manipulation */
{       register int i,j;
I 5

E 5
	/*      array linkages          */
	for (i=1; i<=LOCSIZ; i++)
		if (ltext[i].seekadr!=0 && travel[i] != 0)
			if ((travel[i]->tverb)==1) cond[i]=2;
	for (j=100; j>0; j--)
		if (fixd[j]>0)
		{       drop(j+100,fixd[j]);
			drop(j,plac[j]);
		}
	for (j=100; j>0; j--)
	{       fixed[j]=fixd[j];
		if (plac[j]!=0 && fixd[j]<=0) drop(j,plac[j]);
	}

	maxtrs=79;
	tally=0;
	tally2=0;

	for (i=50; i<=maxtrs; i++)
	{       if (ptext[i].seekadr!=0) prop[i] = -1;
		tally -= prop[i];
	}

	/* define mnemonics */
D 5
	keys=vocab("keys",1);
	lamp=vocab("lamp",1);
	grate=vocab("grate",1);
	cage=vocab("cage",1);
	rod=vocab("rod",1);
E 5
I 5
	keys = vocab(DECR(k,e,y,s,\0), 1);
	lamp = vocab(DECR(l,a,m,p,\0), 1);
	grate = vocab(DECR(g,r,a,t,e), 1);
	cage  = vocab(DECR(c,a,g,e,\0),1);
	rod   = vocab(DECR(r,o,d,\0,\0),1);
E 5
	rod2=rod+1;
D 5
	steps=vocab("steps",1);
	bird=vocab("bird",1);
	door=vocab("door",1);
	pillow=vocab("pillow",1);
	snake=vocab("snake",1);
	fissur=vocab("fissu",1);
	tablet=vocab("table",1);
	clam=vocab("clam",1);
	oyster=vocab("oyster",1);
	magzin=vocab("magaz",1);
	dwarf=vocab("dwarf",1);
	knife=vocab("knife",1);
	food=vocab("food",1);
	bottle=vocab("bottl",1);
	water=vocab("water",1);
	oil=vocab("oil",1);
	plant=vocab("plant",1);
E 5
I 5
	steps=vocab(DECR(s,t,e,p,s),1);
	bird  = vocab(DECR(b,i,r,d,\0),1);
	door  = vocab(DECR(d,o,o,r,\0),1);
	pillow= vocab(DECR(p,i,l,l,o), 1);
	snake = vocab(DECR(s,n,a,k,e), 1);
	fissur= vocab(DECR(f,i,s,s,u), 1);
	tablet= vocab(DECR(t,a,b,l,e), 1);
	clam  = vocab(DECR(c,l,a,m,\0),1);
	oyster= vocab(DECR(o,y,s,t,e), 1);
	magzin= vocab(DECR(m,a,g,a,z), 1);
	dwarf = vocab(DECR(d,w,a,r,f), 1);
	knife = vocab(DECR(k,n,i,f,e), 1);
	food  = vocab(DECR(f,o,o,d,\0),1);
	bottle= vocab(DECR(b,o,t,t,l), 1);
	water = vocab(DECR(w,a,t,e,r), 1);
	oil   = vocab(DECR(o,i,l,\0,\0),1);
	plant = vocab(DECR(p,l,a,n,t), 1);
E 5
	plant2=plant+1;
D 5
	axe=vocab("axe",1);
	mirror=vocab("mirro",1);
	dragon=vocab("drago",1);
	chasm=vocab("chasm",1);
	troll=vocab("troll",1);
E 5
I 5
	axe   = vocab(DECR(a,x,e,\0,\0),1);
	mirror= vocab(DECR(m,i,r,r,o), 1);
	dragon= vocab(DECR(d,r,a,g,o), 1);
	chasm = vocab(DECR(c,h,a,s,m), 1);
	troll = vocab(DECR(t,r,o,l,l), 1);
E 5
	troll2=troll+1;
D 5
	bear=vocab("bear",1);
	messag=vocab("messa",1);
	vend=vocab("vendi",1);
	batter=vocab("batte",1);
E 5
I 5
	bear  = vocab(DECR(b,e,a,r,\0),1);
	messag= vocab(DECR(m,e,s,s,a), 1);
	vend  = vocab(DECR(v,e,n,d,i), 1);
	batter= vocab(DECR(b,a,t,t,e), 1);
E 5

D 5
	nugget=vocab("gold",1);
	coins=vocab("coins",1);
	chest=vocab("chest",1);
	eggs=vocab("eggs",1);
	tridnt=vocab("tride",1);
	vase=vocab("vase",1);
	emrald=vocab("emera",1);
	pyram=vocab("pyram",1);
	pearl=vocab("pearl",1);
	rug=vocab("rug",1);
	chain=vocab("chain",1);
E 5
I 5
	nugget= vocab(DECR(g,o,l,d,\0),1);
	coins = vocab(DECR(c,o,i,n,s), 1);
	chest = vocab(DECR(c,h,e,s,t), 1);
	eggs  = vocab(DECR(e,g,g,s,\0),1);
	tridnt= vocab(DECR(t,r,i,d,e), 1);
	vase  = vocab(DECR(v,a,s,e,\0),1);
	emrald= vocab(DECR(e,m,e,r,a), 1);
	pyram = vocab(DECR(p,y,r,a,m), 1);
	pearl = vocab(DECR(p,e,a,r,l), 1);
	rug   = vocab(DECR(r,u,g,\0,\0),1);
	chain = vocab(DECR(c,h,a,i,n), 1);
E 5

D 5
	back=vocab("back",0);
	look=vocab("look",0);
	cave=vocab("cave",0);
	null=vocab("null",0);
	entrnc=vocab("entra",0);
	dprssn=vocab("depre",0);
E 5
I 5
	back  = vocab(DECR(b,a,c,k,\0),0);
	look  = vocab(DECR(l,o,o,k,\0),0);
	cave  = vocab(DECR(c,a,v,e,\0),0);
	null  = vocab(DECR(n,u,l,l,\0),0);
	entrnc= vocab(DECR(e,n,t,r,a), 0);
	dprssn= vocab(DECR(d,e,p,r,e), 0);
	enter = vocab(DECR(e,n,t,e,r), 0);
E 5

D 5
	say=vocab("say",2);
	lock=vocab("lock",2);
	throw=vocab("throw",2);
	find=vocab("find",2);
	invent=vocab("inven",2);
E 5
I 5
	pour  = vocab(DECR(p,o,u,r,\0), 2);
	say   = vocab(DECR(s,a,y,\0,\0),2);
	lock  = vocab(DECR(l,o,c,k,\0),2);
	throw = vocab(DECR(t,h,r,o,w), 2);
	find  = vocab(DECR(f,i,n,d,\0),2);
	invent= vocab(DECR(i,n,v,e,n), 2);

E 5
	/* initialize dwarves */
	chloc=114;
	chloc2=140;
	for (i=1; i<=6; i++)
		dseen[i]=FALSE;
	dflag=0;
	dloc[1]=19;
	dloc[2]=27;
	dloc[3]=33;
	dloc[4]=44;
	dloc[5]=64;
	dloc[6]=chloc;
	daltlc=18;

	/* random flags & ctrs */
	turns=0;
	lmwarn=FALSE;
	iwest=0;
	knfloc=0;
	detail=0;
	abbnum=5;
	for (i=0; i<=4; i++)
		if (rtext[2*i+81].seekadr!=0) maxdie=i+1;
	numdie=holdng=dkill=foobar=bonus=0;
	clock1=30;
	clock2=50;
	saved=0;
	closng=panic=closed=scorng=FALSE;
}



trapdel()                               /* come here if he hits a del   */
{	delhit++;			/* main checks, treats as QUIT  */
	signal(2,trapdel);		/* catch subsequent DELs        */
}


startup()
D 3
{       int tvec[2];
E 3
I 3
{
	time_t time();

E 3
D 10
	demo=start(0);
E 10
I 10
	demo=Start(0);
E 10
D 3
	time(tvec);
	srand(tvec[1]|1);               /* random odd seed              */
/*      srand(371);             */      /* non-random seed                      */
E 3
I 3
	srand((int)(time((time_t *)NULL)));	/* random seed */
	/* srand(371);				/* non-random seed */
E 3
	hinted[3]=yes(65,1,0);
	newloc=1;
D 5
	setup=3;
E 5
I 5
	delhit = 0;
E 5
	limit=330;
	if (hinted[3]) limit=1000;      /* better batteries if instrucs */
}
D 5

E 5
E 1
