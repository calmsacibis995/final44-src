h18912
s 00002/00002/00156
d D 8.1 93/05/31 15:55:09 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00158
d D 5.3 93/05/13 17:03:59 bostic 7 6
c lint from JG
e
s 00140/00088/00019
d D 5.2 93/05/12 14:04:12 bostic 6 5
c new version of adventure from Jim Gillogly (jim@rand.org)
e
s 00015/00002/00092
d D 5.1 91/04/08 17:08:24 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00050/00092
d D 4.3 89/03/05 20:20:59 bostic 4 3
c make this work with dm(8) -- fix is ugly, but the code is worse
e
s 00005/00000/00137
d D 4.2 86/11/17 17:52:26 mckusick 3 2
c add CCI (tahoe) support
e
s 00000/00000/00137
d D 4.1 82/05/11 14:42:10 rrh 2 1
c release version 4.1
e
s 00137/00000/00000
d D 1.1 82/05/11 14:35:07 rrh 1 0
c date and time created 82/05/11 14:35:07 by rrh
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
E 6
I 6
D 8
 * Copyright (c) 1991, 1993 The Regents of the University of California.
E 6
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
 * The game adventure was original written Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by
 * Jim Gillogly.
E 6
I 6
 * The game adventure was originally written in Fortran by Will Crowther
 * and Don Woods.  It was later translated to C and enhanced by Jim
 * Gillogly.  This code is derived from software contributed to Berkeley
 * by Jim Gillogly at The Rand Corporation.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
I 1
D 6
/* save (III)   J. Gillogly
 * save user core image for restarting
 * usage: save(<command file (argv[0] from main)>,<output file>)
 * bugs
 *   -  impure code (i.e. changes in instructions) is not handled
 *      (but people that do that get what they deserve)
 */
E 6
I 6
#include <stdio.h>
#include "hdr.h"
E 6
D 5

static char sccsid[] = "	%M%	%I%	%E%	";
E 5

I 4
D 6
#include <sys/file.h>
E 4
#include <a.out.h>
int filesize;                    /* accessible to caller         */
E 6
I 6
struct savestruct
{
	void *address;
	int width;
};
E 6

D 6
char *sbrk();
E 6
I 6
struct savestruct save_array[] =
{
	&abbnum,        sizeof(abbnum),
	&attack,        sizeof(attack),
	&blklin,        sizeof(blklin),
	&bonus,         sizeof(bonus),
	&chloc,         sizeof(chloc),
	&chloc2,        sizeof(chloc2),
	&clock1,        sizeof(clock1),
	&clock2,        sizeof(clock2),
	&closed,        sizeof(closed),
	&closng,        sizeof(closng),
	&daltlc,        sizeof(daltlc),
	&demo,          sizeof(demo),
	&detail,        sizeof(detail),
	&dflag,         sizeof(dflag),
	&dkill,         sizeof(dkill),
	&dtotal,        sizeof(dtotal),
	&foobar,        sizeof(foobar),
	&gaveup,        sizeof(gaveup),
	&holdng,        sizeof(holdng),
	&iwest,         sizeof(iwest),
	&k,             sizeof(k),
	&k2,            sizeof(k2),
	&knfloc,        sizeof(knfloc),
	&kq,            sizeof(kq),
	&latncy,        sizeof(latncy),
	&limit,         sizeof(limit),
	&lmwarn,        sizeof(lmwarn),
	&loc,           sizeof(loc),
	&maxdie,        sizeof(maxdie),
	&mxscor,        sizeof(mxscor),
	&newloc,        sizeof(newloc),
	&numdie,        sizeof(numdie),
	&obj,           sizeof(obj),
	&oldlc2,        sizeof(oldlc2),
	&oldloc,        sizeof(oldloc),
	&panic,         sizeof(panic),
	&saved,         sizeof(saved),
	&savet,         sizeof(savet),
	&scorng,        sizeof(scorng),
	&spk,           sizeof(spk),
	&stick,         sizeof(stick),
	&tally,         sizeof(tally),
	&tally2,        sizeof(tally2),
	&tkk,           sizeof(tkk),
	&turns,         sizeof(turns),
	&verb,          sizeof(verb),
	&wd1,           sizeof(wd1),
	&wd2,           sizeof(wd2),
	&wzdark,        sizeof(wzdark),
	&yea,           sizeof(yea),
	atloc,          sizeof(atloc),
	dloc,           sizeof(dloc),
	dseen,          sizeof(dseen),
	fixed,          sizeof(fixed),
	hinted,         sizeof(hinted),
	link,           sizeof(link),
	odloc,          sizeof(odloc),
	place,          sizeof(place),
	prop,           sizeof(prop),
	tk,             sizeof(tk),
E 6

D 6
save(cmdfile,outfile)                   /* save core image              */
char *cmdfile,*outfile;
{       register char *c;
	register int i,fd;
	int fdaout;
	struct exec header;
	int counter;
	char buff[512],pwbuf[120];
D 4
	fdaout=getcmd(cmdfile);         /* open command wherever it is  */
E 4
I 4
	fdaout = open(cmdfile, O_RDONLY, 0);	/* open command */
E 4
	if (fdaout<0) return(-1);       /* can do nothing without text  */
D 4
	if ((fd=open(outfile,0))>0)     /* this restriction is so that  */
	{       printf("Can't use an existing file\n"); /* we don't try */
		close(fd);              /* to write over the commnd file*/
		return(-1);
	}
E 4
	if ((fd=creat(outfile,0755))== -1)
	{       printf("Cannot create %s\n",outfile);
		return(-1);
E 6
I 6
	NULL,   0
};

save(outfile)   /* Two passes on data: first to get checksum, second */
char *outfile;  /* to output the data using checksum to start random #s */
{
	FILE *out;
	struct savestruct *p;
	char *s;
D 7
	int crc();
E 7
	long sum;
	int i;

	crc_start();
	for (p = save_array; p->address != NULL; p++)
		sum = crc(p->address, p->width);
	srandom((int) sum);

	if ((out = fopen(outfile, "wb")) == NULL)
	{
	    fprintf(stderr,
		"Hmm.  The name \"%s\" appears to be magically blocked.\n",
		outfile);
	    return 1;
E 6
	}
D 6
	/* can get the text segment from the command that we were
	 * called with, and change all data from uninitialized to
	 * initialized.  It will start at the top again, so the user
	 * is responsible for checking whether it was restarted
	 * could ignore sbrks and breaks for the first pass
	 */
	read(fdaout,&header,sizeof header);/* get the header       */
	header.a_bss = 0;                  /* no data uninitialized        */
	header.a_syms = 0;                 /* throw away symbol table      */
	switch (header.a_magic)            /* find data segment            */
	{   case 0407:                     /* non sharable code            */
		c = (char *) header.a_text;/* data starts right after text */
		header.a_data=sbrk(0)-c;   /* current size (incl allocs)   */
		break;
	    case 0410:                     /* sharable code                */
		c = (char *)
#ifdef pdp11
		    (header.a_text	   /* starts after text            */
		    & 0160000)             /* on an 8K boundary            */
		    +  020000;             /* i.e. the next one up         */
#endif
#ifdef vax
		    (header.a_text	   /* starts after text            */
		    & 037777776000)        /* on an 1K boundary            */
		    +        02000;        /* i.e. the next one up         */
#endif
I 3
#ifdef tahoe
		    (header.a_text	   /* starts after text            */
		    & 037777776000)        /* on an 1K boundary            */
		    +        02000;        /* i.e. the next one up         */
#endif
E 3
#ifdef z8000
		    (header.a_text	   /* starts after text            */
		    & 0174000)             /* on an 2K boundary            */
		    +  004000;             /* i.e. the next one up         */
#endif
		header.a_data=sbrk(0)-c;   /* current size (incl allocs)   */
		break;
	    case 0411:                     /* sharable with split i/d      */
		c = 0;                     /* can't reach text             */
		header.a_data=(int)sbrk(0);/* current size (incl allocs)   */
		break;
	    case 0413:
		c = (char *) header.a_text;/* starts after text            */
		lseek(fdaout, 1024L, 0);   /* skip unused part of 1st block*/
E 6
I 6
	fwrite(&sum, sizeof(sum), 1, out);      /* Here's the random() key */
	for (p = save_array; p->address != NULL; p++)
	{
		for (s = p->address, i = 0; i < p->width; i++, s++)
			*s = (*s ^ random()) & 0xFF;      /* Lightly encrypt */
		fwrite(p->address, p->width, 1, out);
E 6
	}
D 6
	if (header.a_data<0)               /* data area very big           */
		return(-1);                /* fail for now                 */
E 6
I 6
	fclose(out);
	return 0;
}
E 6

D 6
	filesize=sizeof header+header.a_text+header.a_data;
	write(fd,&header,sizeof header);   /* make the new header          */
	if (header.a_magic==0413)
		lseek(fd, 1024L, 0);       /* Start on 1K boundary	   */
	counter=header.a_text;             /* size of text                 */
	while (counter>512)                /* copy 512-byte blocks         */
	{       read(fdaout,buff,512);     /* as long as possible          */
		write(fd,buff,512);
		counter -= 512;
E 6
I 6
restore(infile)
char *infile;
{
	FILE *in;
	struct savestruct *p;
	char *s;
	long sum, cksum;
	int i;

	if ((in = fopen(infile, "rb")) == NULL)
	{
	    fprintf(stderr,
		"Hmm.  The file \"%s\" appears to be magically blocked.\n",
		infile);
	    return 1;
E 6
	}
D 6
	read(fdaout,buff,counter);         /* then pick up the rest        */
	write(fd,buff,counter);
	write(fd,c,header.a_data);         /* write all data in 1 glob     */
	close(fd);
E 6
I 6
	fread(&sum, sizeof(sum), 1, in);        /* Get the seed */
	srandom((int) sum);
	for (p = save_array; p->address != NULL; p++)
	{
		fread(p->address, p->width, 1, in);
		for (s = p->address, i = 0; i < p->width; i++, s++)
			*s = (*s ^ random()) & 0xFF;  /* Lightly decrypt */
	}
	fclose(in);

	crc_start();                            /* See if she cheated */
	for (p = save_array; p->address != NULL; p++)
		cksum = crc(p->address, p->width);
	if (sum != cksum)                       /* Tsk tsk */
	    return 2;                           /* Altered the file */
	/* We successfully restored, so this really was a save file */
	/* Get rid of the file, but don't bother checking that we did */
	return 0;
E 6
D 4
}

#define	NULL	0

char	*execat(), *getenv();

getcmd(command)         /* get command name (wherever it is) like shell */
char *command;
{
	char *pathstr;
	register char *cp;
	char fname[128];
	int fd;

	if ((pathstr = getenv("PATH")) == NULL)
		pathstr = ":/bin:/usr/bin";
	cp = index(command, '/')? "": pathstr;

	do {
		cp = execat(cp, command, fname);
		if ((fd=open(fname,0))>0)
			return(fd);
	} while (cp);

	printf("Couldn't open %s\n",command);
	return(-1);
}

static char *
execat(s1, s2, si)
register char *s1, *s2;
char *si;
{
	register char *s;

	s = si;
	while (*s1 && *s1 != ':' && *s1 != '-')
		*s++ = *s1++;
	if (si != s)
		*s++ = '/';
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return(*s1? ++s1: 0);
E 4
}
E 1
