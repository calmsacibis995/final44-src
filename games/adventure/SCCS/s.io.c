h06717
s 00002/00002/00486
d D 8.1 93/05/31 15:54:53 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00070/00091/00418
d D 5.2 93/05/12 14:04:09 bostic 5 4
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00015/00003/00494
d D 5.1 91/04/08 17:08:19 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00495
d D 4.2 88/09/22 17:48:47 bostic 3 2
c fixes for ANSI C
e
s 00000/00000/00497
d D 4.1 82/05/11 14:41:50 rrh 2 1
c release version 4.1
e
s 00497/00000/00000
d D 1.1 82/05/11 14:34:55 rrh 1 0
c date and time created 82/05/11 14:34:55 by rrh
e
u
U
t
T
I 1
D 4
#
/*      Re-coding of advent in C: file i/o and user i/o                 */
E 4
I 4
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
E 5
I 5
D 6
 * Copyright (c) 1991, 1993 The Regents of the University of California.
E 5
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
E 4

D 4
static char sccsid[] = "	%M%	%I%	%E%	";
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*      Re-coding of advent in C: file i/o and user i/o                 */
E 4

#include "hdr.h"
#include <stdio.h>


getin(wrd1,wrd2)                        /* get command from user        */
char **wrd1,**wrd2;                     /* no prompt, usually           */
{       register char *s;
	static char wd1buf[MAXSTR],wd2buf[MAXSTR];
	int first, numch;

	*wrd1=wd1buf;                   /* return ptr to internal string*/
	*wrd2=wd2buf;
	wd2buf[0]=0;                    /* in case it isn't set here    */
	for (s=wd1buf, first=1, numch=0;;)
	{       if ((*s=getchar())>='A' && *s <='Z') *s = *s - ('A' -'a');
					/* convert to upper case        */
		switch(*s)              /* start reading from user      */
		{   case '\n':
			*s=0;
			return;
		    case ' ':
			if (s==wd1buf||s==wd2buf)  /* initial blank   */
				continue;
			*s=0;
			if (first)      /* finished 1st wd; start 2nd   */
			{       first=numch=0;
				s=wd2buf;
				break;
			}
			else            /* finished 2nd word            */
			{       FLUSHLINE;
				*s=0;
				return;
			}
		    default:
			if (++numch>=MAXSTR)    /* string too long      */
			{       printf("Give me a break!!\n");
				wd1buf[0]=wd2buf[0]=0;
				FLUSHLINE;
				return;
			}
			s++;
		}
	}
}


confirm(mesg)                           /* confirm irreversible action  */
char *mesg;
{       register int result;
	printf("%s",mesg);              /* tell him what he did         */
	if (getchar()=='y')             /* was his first letter a 'y'?  */
		result=1;
	else    result=0;
	FLUSHLINE;
	return(result);
}

yes(x,y,z)                              /* confirm with rspeak          */
int x,y,z;
{       register int result;
	register char ch;
	for (;;)
	{       rspeak(x);                     /* tell him what we want*/
		if ((ch=getchar())=='y')
			result=TRUE;
		else if (ch=='n') result=FALSE;
		FLUSHLINE;
		if (ch=='y'|| ch=='n') break;
		printf("Please answer the question.\n");
	}
	if (result==TRUE) rspeak(y);
	if (result==FALSE) rspeak(z);
	return(result);
}

yesm(x,y,z)                             /* confirm with mspeak          */
int x,y,z;
{       register int result;
	register char ch;
	for (;;)
	{       mspeak(x);                     /* tell him what we want*/
		if ((ch=getchar())=='y')
			result=TRUE;
		else if (ch=='n') result=FALSE;
		FLUSHLINE;
		if (ch=='y'|| ch=='n') break;
		printf("Please answer the question.\n");
	}
	if (result==TRUE) mspeak(y);
	if (result==FALSE) mspeak(z);
	return(result);
}

D 5
FILE *inbuf,*outbuf;
E 5
I 5
/* FILE *inbuf,*outbuf; */
E 5

D 5
int adrptr;                             /* current seek adr ptr         */
E 5
I 5
char *inptr;                            /* Pointer into virtual disk    */

E 5
int outsw = 0;				/* putting stuff to data file?  */

D 5
char iotape[] = "Ax3F'tt$8hqer*hnGKrX:!l";
E 5
I 5
char iotape[] = "Ax3F'\003tt$8h\315qer*h\017nGKrX\207:!l";
E 5
char *tape = iotape;			/* pointer to encryption tape   */

D 5
next()                                  /* next char frm file, bump adr */
{       register char ch,t;
	adrptr++;                       /* seek address in file         */
	ch=getc(inbuf);
E 5
I 5
next()                                  /* next virtual char, bump adr  */
{
	int ch;

	ch=(*inptr ^ random()) & 0xFF;  /* Decrypt input data           */
E 5
	if (outsw)                      /* putting data in tmp file     */
D 5
	{       if (*tape==0) tape=iotape; /* rewind encryption tape    */
		putc(ch ^ *tape++,outbuf); /* encrypt & output char     */
E 5
I 5
	{   if (*tape==0) tape=iotape;  /* rewind encryption tape       */
	    *inptr = ch ^ *tape++;      /* re-encrypt and replace value */
E 5
	}
I 5
	inptr++;
E 5
	return(ch);
}

D 5

E 5
char breakch;                           /* tell which char ended rnum   */

D 5

rdata()                                 /* read all data from orig file */
E 5
I 5
rdata()                                 /* "read" data from virtual file*/
E 5
{       register int sect;
	register char ch;
D 5
	if ((inbuf=fopen(DATFILE,"r"))==NULL)     /* all the data lives in here   */
	{       printf("Cannot open data file %s\n",DATFILE);
		exit(0);
	}
	if ((outbuf=fopen(TMPFILE,"w"))==NULL)   /* the text lines will go here  */
	{       printf("Cannot create output file %s\n",TMPFILE);
		exit(0);
	}
	setup=clsses=1;
E 5
I 5

	inptr = data_file;              /* Pointer to virtual data file */
	srandom(SEED);                  /* which is lightly encrypted.  */

	clsses=1;
E 5
	for (;;)                        /* read data sections           */
	{       sect=next()-'0';        /* 1st digit of section number  */
I 5
#ifdef VERBOSE
E 5
		printf("Section %c",sect+'0');
I 5
#endif
E 5
		if ((ch=next())!=LF)    /* is there a second digit?     */
D 5
		{       FLUSHLF;
E 5
I 5
		{
			FLUSHLF;
#ifdef VERBOSE
E 5
			putchar(ch);
I 5
#endif
E 5
			sect=10*sect+ch-'0';
		}
I 5
#ifdef VERBOSE
E 5
		putchar('\n');
I 5
#endif
E 5
		switch(sect)
		{   case 0:             /* finished reading database    */
D 5
			fclose(inbuf);
			fclose(outbuf);
E 5
			return;
		    case 1:             /* long form descriptions       */
			rdesc(1);
			break;
		    case 2:             /* short form descriptions      */
			rdesc(2);
			break;
		    case 3:             /* travel table                 */
			rtrav();   break;
		    case 4:             /* vocabulary                   */
			rvoc();
			break;
		    case 5:             /* object descriptions          */
			rdesc(5);
			break;
		    case 6:             /* arbitrary messages           */
			rdesc(6);
			break;
		    case 7:             /* object locations             */
			rlocs();   break;
		    case 8:             /* action defaults              */
			rdflt();   break;
		    case 9:             /* liquid assets                */
			rliq();    break;
		    case 10:            /* class messages               */
			rdesc(10);
			break;
		    case 11:            /* hints                        */
			rhints();  break;
		    case 12:            /* magic messages               */
			rdesc(12);
			break;
		    default:
			printf("Invalid data section number: %d\n",sect);
			for (;;) putchar(next());
		}
		if (breakch!=LF)        /* routines return after "-1"   */
			FLUSHLF;
	}
}

char nbf[12];


rnum()                                  /* read initial location num    */
{       register char *s;
	tape = iotape;                  /* restart encryption tape      */
	for (s=nbf,*s=0;; s++)
		if ((*s=next())==TAB || *s=='\n' || *s==LF)
			break;
	breakch= *s;                    /* save char for rtrav()        */
	*s=0;                           /* got the number as ascii      */
	if (nbf[0]=='-') return(-1);    /* end of data                  */
	return(atoi(nbf));              /* convert it to integer        */
}

D 5
int seekhere = 1;			/* initial seek for output file */
E 5
I 5
char *seekhere;
E 5

rdesc(sect)                             /* read description-format msgs */
int sect;
{       register char *s,*t;
	register int locc;
D 5
	int  seekstart, maystart, adrstart;
E 5
I 5
	char *seekstart, *maystart, *adrstart;
E 5
	char *entry;
I 5

	seekhere = inptr;               /* Where are we in virtual file?*/
E 5
	outsw=1;                        /* these msgs go into tmp file  */
D 5
	if (sect==1) putc('X',outbuf);  /* so seekadr > 0               */
	adrptr=0;
E 5
	for (oldloc= -1, seekstart=seekhere;;)
D 5
	{       maystart=adrptr;        /* maybe starting new entry     */
E 5
I 5
	{       maystart=inptr;         /* maybe starting new entry     */
E 5
		if ((locc=rnum())!=oldloc && oldloc>=0  /* finished msg */
		    && ! (sect==5 && (locc==0 || locc>=100)))/* unless sect 5*/
		{       switch(sect)    /* now put it into right table  */
			{   case 1:     /* long descriptions            */
				ltext[oldloc].seekadr=seekhere;
				ltext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 2:     /* short descriptions           */
				stext[oldloc].seekadr=seekhere;
				stext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 5:     /* object descriptions          */
				ptext[oldloc].seekadr=seekhere;
				ptext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 6:     /* random messages              */
				if (oldloc>RTXSIZ)
				{       printf("Too many random msgs\n");
					exit(0);
				}
				rtext[oldloc].seekadr=seekhere;
				rtext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 10:    /* class messages               */
				ctext[clsses].seekadr=seekhere;
				ctext[clsses].txtlen=maystart-seekstart;
				cval[clsses++]=oldloc;
				break;
			    case 12:    /* magic messages               */
				if (oldloc>MAGSIZ)
				{       printf("Too many magic msgs\n");
					exit(0);
				}
				mtext[oldloc].seekadr=seekhere;
				mtext[oldloc].txtlen=maystart-seekstart;
				break;
			    default:
				printf("rdesc called with bad section\n");
				exit(0);
			}
			seekhere += maystart-seekstart;
		}
		if (locc<0)
		{       outsw=0;        /* turn off output              */
			seekhere += 3;  /* -1<delimiter>                */
			return;
		}
		if (sect!=5 || (locc>0 && locc<100))
		{       if (oldloc!=locc)/* starting a new message       */
				seekstart=maystart;
			oldloc=locc;
		}
		FLUSHLF;                /* scan the line                */
	}
}


rtrav()                                 /* read travel table            */
{       register int locc;
	register struct travlist *t;
	register char *s;
	char buf[12];
	int len,m,n,entries;
	for (oldloc= -1;;)              /* get another line             */
	{       if ((locc=rnum())!=oldloc && oldloc>=0) /* end of entry */
		{
			t->next = 0;    /* terminate the old entry      */
		/*      printf("%d:%d entries\n",oldloc,entries);       */
		/*      twrite(oldloc);                                 */
		}
		if (locc== -1) return;
		if (locc!=oldloc)        /* getting a new entry         */
		{       t=travel[locc]=(struct travlist *) malloc(sizeof (struct travlist));
		/*      printf("New travel list for %d\n",locc);        */
			entries=0;
			oldloc=locc;
		}
		for (s=buf;; *s++)      /* get the newloc number /ASCII */
			if ((*s=next())==TAB || *s==LF) break;
		*s=0;
		len=length(buf)-1;      /* quad long number handling    */
	/*      printf("Newloc: %s (%d chars)\n",buf,len);              */
		if (len<4)              /* no "m" conditions            */
		{       m=0;
			n=atoi(buf);    /* newloc mod 1000 = newloc     */
		}
		else                    /* a long integer               */
		{       n=atoi(buf+len-3);
			buf[len-3]=0;   /* terminate newloc/1000        */
			m=atoi(buf);
		}
		while (breakch!=LF)     /* only do one line at a time   */
		{       if (entries++) t=t->next=(struct travlist *) malloc(sizeof (struct travlist));
			t->tverb=rnum();/* get verb from the file       */
			t->tloc=n;      /* table entry mod 1000         */
			t->conditions=m;/* table entry / 1000           */
		/*      printf("entry %d for %d\n",entries,locc);       */
		}
	}
}

I 5
#ifdef DEBUG
E 5

twrite(loq)                             /* travel options from this loc */
int loq;
{       register struct travlist *t;
	printf("If");
	speak(&ltext[loq]);
	printf("then\n");
	for (t=travel[loq]; t!=0; t=t->next)
	{       printf("verb %d takes you to ",t->tverb);
		if (t->tloc<=300)
			speak(&ltext[t->tloc]);
		else if (t->tloc<=500)
			printf("special code %d\n",t->tloc-300);
		else
			rspeak(t->tloc-500);
		printf("under conditions %d\n",t->conditions);
	}
}

I 5
#endif DEBUG
E 5

D 5

E 5
rvoc()
{       register char *s;               /* read the vocabulary          */
	register int index;
	char buf[6];
	for (;;)
	{       index=rnum();
		if (index<0) break;
		for (s=buf,*s=0;; s++)  /* get the word                 */
			if ((*s=next())==TAB || *s=='\n' || *s==LF
				|| *s==' ') break;
			/* terminate word with newline, LF, tab, blank  */
		if (*s!='\n' && *s!=LF) FLUSHLF;  /* can be comments    */
		*s=0;
	/*      printf("\"%s\"=%d\n",buf,index);*/
		vocab(buf,-2,index);
	}
/*	prht();	*/
}


rlocs()                                 /* initial object locations     */
{	for (;;)
	{       if ((obj=rnum())<0) break;
		plac[obj]=rnum();       /* initial loc for this obj     */
		if (breakch==TAB)       /* there's another entry        */
			fixd[obj]=rnum();
		else    fixd[obj]=0;
	}
}

rdflt()                                 /* default verb messages        */
{	for (;;)
	{       if ((verb=rnum())<0) break;
		actspk[verb]=rnum();
	}
}

rliq()                                  /* liquid assets &c: cond bits  */
{       register int bitnum;
	for (;;)                        /* read new bit list            */
	{       if ((bitnum=rnum())<0) break;
		for (;;)                /* read locs for bits           */
		{       cond[rnum()] |= setbit[bitnum];
			if (breakch==LF) break;
		}
	}
}

rhints()
{       register int hintnum,i;
	hntmax=0;
	for (;;)
	{       if ((hintnum=rnum())<0) break;
		for (i=1; i<5; i++)
			hints[hintnum][i]=rnum();
		if (hintnum>hntmax) hntmax=hintnum;
	}
}


rspeak(msg)
int msg;
{       if (msg!=0) speak(&rtext[msg]);
}


mspeak(msg)
int msg;
{       if (msg!=0) speak(&mtext[msg]);
}


D 5
doseek(offset)  /* do 2 seeks to get to right place in the file         */
unsigned offset;
{
	extern unsigned filesize;
	lseek(datfd,(long)offset+(long)filesize, 0);
#ifdef notdef
	blockadr=chadr=0;
	if (offset<0)                   /* right place is offset+filesize*/
	{       blockadr += 64;         /* take off 32768 bytes         */
		chadr += offset+32768;  /* & make them into 64 blocks   */
	}
	else chadr += offset;
	if (filesize<0)                 /* data starts after file       */
	{       blockadr += 64;         /* which may also be large      */
		chadr += filesize+32768;
	}
	else chadr += filesize;
	if (chadr<0)                    /* and the leftovers may be lge */
	{       blockadr += 64;
		chadr += 32768;
	}
	seek(datfd,blockadr,3);         /* get within 32767             */
	seek(datfd,chadr,1);            /* then the rest of the way     */
#endif
}


E 5
speak(msg)       /* read, decrypt, and print a message (not ptext)      */
struct text *msg;/* msg is a pointer to seek address and length of mess */
D 5
{       register char *s,nonfirst;
	register char *tbuf;
	doseek(msg->seekadr);
D 3
	if ((tbuf=(char *) malloc(msg->txtlen+1))<0) bug(109);
E 3
I 3
	if ((tbuf=(char *) malloc(msg->txtlen+1)) == 0) bug(109);
E 3
	read(datfd,tbuf,msg->txtlen);
	s=tbuf;
E 5
I 5
{
	register char *s, nonfirst;

	s = msg->seekadr;
E 5
	nonfirst=0;
D 5
	while (s-tbuf<msg->txtlen)      /* read a line at a time        */
E 5
I 5
	while (s - msg->seekadr < msg->txtlen)  /* read a line at a time */
E 5
	{       tape=iotape;            /* restart decryption tape      */
D 5
		while ((*s++^*tape++)!=TAB); /* read past loc num       */
E 5
I 5
		while ((*s++ ^ *tape++) != TAB); /* read past loc num       */
E 5
		/* assume tape is longer than location number           */
		/*   plus the lookahead put together                    */
D 5
		if ((*s^*tape)=='>' &&
			(*(s+1)^*(tape+1))=='$' &&
			(*(s+2)^*(tape+2))=='<') break;
		if (blklin&&!nonfirst++) putchar('\n');
E 5
I 5
		if ((*s ^ *tape) == '>' &&
			(*(s+1) ^ *(tape+1)) == '$' &&
			(*(s+2) ^ *(tape+2)) == '<') break;
		if (blklin && !nonfirst++) putchar('\n');
E 5
		do
D 5
		{       if (*tape==0) tape=iotape;/* rewind decryp tape */
			putchar(*s^*tape);
		} while ((*s++^*tape++)!=LF);   /* better end with LF   */
E 5
I 5
		{       if (*tape == 0) tape = iotape;/* rewind decryp tape */
			putchar(*s ^ *tape);
		} while ((*s++ ^ *tape++) != LF);   /* better end with LF   */
E 5
	}
D 5
	free(tbuf);
E 5
}


D 5
pspeak(msg,skip) /* read, decrypt an print a ptext message              */
int msg;         /* msg is the number of all the p msgs for this place  */
E 5
I 5
pspeak(m,skip) /* read, decrypt an print a ptext message              */
int m;         /* msg is the number of all the p msgs for this place  */
E 5
int skip;       /* assumes object 1 doesn't have prop 1, obj 2 no prop 2 &c*/
D 5
{       register char *s,nonfirst;
	register char *tbuf;
	char *numst;
	int lstr;
	doseek(ptext[msg].seekadr);
D 3
	if ((tbuf=(char *) malloc((lstr=ptext[msg].txtlen)+1))<0) bug(108);
E 3
I 3
	if ((tbuf=(char *) malloc((lstr=ptext[msg].txtlen)+1)) == 0) bug(108);
E 3
	read(datfd,tbuf,lstr);
	s=tbuf;
E 5
I 5
{
	register char *s,nonfirst;
	char *numst, save;
	struct text *msg;
	char *tbuf;

	msg = &ptext[m];
	if ((tbuf=(char *) malloc(msg->txtlen + 1)) == 0) bug(108);
	memcpy(tbuf, msg->seekadr, msg->txtlen + 1);   /* Room to null */
	s = tbuf;

E 5
	nonfirst=0;
D 5
	while (s-tbuf<lstr)             /* read a line at a time        */
E 5
I 5
	while (s - tbuf < msg->txtlen) /* read line at a time */
E 5
	{       tape=iotape;            /* restart decryption tape      */
		for (numst=s; (*s^= *tape++)!=TAB; s++); /* get number  */
D 5
		*s++=0; /* decrypting number within the string          */
		if (atoi(numst)!=100*skip && skip>=0)
E 5
I 5

		save = *s; /* Temporarily trash the string (cringe) */
		*s++ = 0; /* decrypting number within the string          */

		if (atoi(numst) != 100 * skip && skip >= 0)
E 5
		{       while ((*s++^*tape++)!=LF) /* flush the line    */
				if (*tape==0) tape=iotape;
			continue;
		}
		if ((*s^*tape)=='>' && (*(s+1)^*(tape+1))=='$' &&
			(*(s+2)^*(tape+2))=='<') break;
		if (blklin && ! nonfirst++) putchar('\n');
		do
		{       if (*tape==0) tape=iotape;
			putchar(*s^*tape);
		} while ((*s++^*tape++)!=LF);   /* better end with LF   */
		if (skip<0) break;
	}
	free(tbuf);
}
D 5

E 5
E 1
