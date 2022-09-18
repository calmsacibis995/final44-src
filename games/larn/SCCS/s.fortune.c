h48309
s 00040/00069/00021
d D 5.5 91/06/10 13:39:14 sellgren 5 4
c Why have this fortune file around?!
e
s 00073/00046/00017
d D 5.4 91/06/06 16:06:22 sellgren 4 3
c Bostic's cleanup
e
s 00000/00005/00063
d D 5.3 91/02/28 13:31:46 bostic 3 2
c ANSI
e
s 00002/00002/00066
d D 5.2 91/02/27 17:18:43 bostic 2 1
c ANSI fix
e
s 00068/00000/00000
d D 5.1 89/03/05 18:59:17 bostic 1 0
c date and time created 89/03/05 18:59:17 by bostic
e
u
U
t
T
I 4
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
I 1
/* fortune.c		 Larn is copyrighted 1986 by Noah Morgan. */
I 4

E 4
D 5
#include <sys/types.h>
#include <sys/stat.h>
D 3

#ifndef BSD4.1
E 3
#include <fcntl.h>
D 2
#else BSD4.1
E 2
I 2
D 3
#else
E 2
#define O_RDONLY 0
D 2
#endif BSD4.1
E 2
I 2
#endif
E 3
E 2
D 4

E 4
I 4
#include <unistd.h>
#include <stdlib.h>
E 4
#include "header.h"
I 4
#include "pathnames.h"

E 5
E 4
/*
D 4
 *	function to return a random fortune from the fortune file
E 4
I 4
 * function to return a random fortune from the fortune file
E 4
 */
D 4
static char *base=0;	/* pointer to the fortune text */
static char **flines=0;	/* array of pointers to each fortune */
static int fd=0;		/* true if we have load the fortune info */
static int nlines=0;	/* # lines in fortune database */
E 4

I 5
char *flines[] = {
	"gem value = gem * 2 ^ perfection",
	"sitting down can have unexpected results",
	"don't pry into the affairs of others",
	"drinking can be hazardous to your health",
	"beware of the gusher!",
	"some monsters are greedy",
	"nymphs have light fingers",
	"try kissing a disenchantress!",
	"hammers and brains don't mix",
	"what does a potion of cure dianthroritis taste like?",
	"hit point gain/loss when raising a level depends on constitution",
	"healing a mighty wizard can be exhilarating",
	"be sure to pay your taxes",
	"are Vampires afraid of something?",
	"some dragons can fly",
	"dos thou strive for perfection?",
	"patience is a virtue, unless your daughter dies",
	"what does the Eye of Larn see in its guardian?",
	"a level 25 player casts like crazy!",
	"energy rings affect spell regeneration",
	"difficulty affects regeneration",
	"control of the pesty spirits is most helpful",
	"don't fall into a bottomless pit",
	"dexterity allows you to carry more",
	"you can get 2 points of WC for the price of one",
	"never enter the dungeon naked!  the monsters will laugh at you!",
	"did someone put itching powder in your armor?",
	"you klutz!",
	"avoid opening doors.  you never know whats on the other side.",
	"infinite regeneration ---> temptation",
	"the greatest weapon in the game has not the highest Weapon Class",
	"you can't buy the most powerful scroll",
	"identify things before you use them",
	"there's more than one way through a wall"
};

#define NFORTUNES	34

E 5
D 4
char *fortune(file)
	char *file;
	{
E 4
I 4
char *
fortune()
{
D 5
	static int fd = -1;	/* true if we have load the fortune info */
	static int nlines;	/* # lines in fortune database */
	register int tmp;
E 4
	register char *p;
D 4
	register int lines,tmp;
	struct stat stat;
	char *malloc();
	if (fd==0)
		{
		if ((fd=open(file,O_RDONLY)) < 0)	/* open the file */
			return(0); /* can't find file */
E 4
I 4
	char *base, **flines;
	struct stat sb;
E 4

D 4
	/* find out how big fortune file is and get memory for it */
		stat.st_size = 16384;
		if ((fstat(fd,&stat) < 0) || ((base=malloc(1+stat.st_size)) == 0))
			{
			close(fd); fd= -1; free((char*)base); return(0); 	/* can't stat file */
			}
E 4
I 4
	if (fd != -1)
		return (flines[random() % nlines]);
E 4

D 4
	/* read in the entire fortune file */
		if (read(fd,base,stat.st_size) != stat.st_size)
			{
			close(fd); fd= -1; free((char*)base); return(0); 	/* can't read file */
			}
		close(fd);  base[stat.st_size]=0;	/* final NULL termination */
E 4
I 4
	if ((fd = open(_PATH_FORTS, O_RDONLY)) < 0)
		return (NULL);
E 4

D 4
	/* count up all the lines (and NULL terminate) to know memory needs */
		for (p=base,lines=0; p<base+stat.st_size; p++) /* count lines */
			if (*p == '\n') *p=0,lines++;
		nlines = lines;
E 4
I 4
	/* Find out how big fortune file is and get memory for it. */
	if ((fstat(fd, &sb) < 0) ||
	    ((base = malloc(1 + sb.st_size)) == NULL)) {
		(void)close(fd);
		goto bad;
	}
E 4

D 4
	/* get memory for array of pointers to each fortune */
		if ((flines=(char**)malloc(nlines*sizeof(char*))) == 0)
			{
			free((char*)base); fd= -1; return(0); /* malloc() failure */
			}
E 4
I 4
	/* Read in the entire fortune file. */
	if (read(fd, base, sb.st_size) != sb.st_size) {
		free(base);
		goto bad;
	}
	base[sb.st_size] = '\0';	/* Final NULL termination. */
E 4

D 4
	/* now assign each pointer to a line */
		for (p=base,tmp=0; tmp<nlines; tmp++)
			{
			flines[tmp]=p;  while (*p++); /* advance to next line */
			}
E 4
I 4
	(void)close(fd);


	/*
	 * Count up all the lines (and NULL terminate) to know memory
	 * needs.
	 */
	for (p = base; p < base + sb.st_size; p++)
		if (*p == '\n') {
			*p = '\0';
			++nlines;
E 4
		}

D 4
	if (fd > 2)	/* if we have a database to look at */
		return(flines[rund((nlines<=0)?1:nlines)]);
	else 
		return(0);
E 4
I 4
	if (nlines <= 0) {
		free(base);
		goto bad;
E 4
	}
I 4

	/* Get memory for array of pointers to each fortune. */
	if ((flines = malloc(nlines * sizeof(char *))) == NULL) {
		free(base);
		goto bad;
	}

	/* Now assign each pointer to a line. */
	for (p = base, tmp = 0; tmp < nlines; ++tmp) {
		flines[tmp] = p;
		while (*p++);
	}

	return (flines[random() % nlines]);

bad:	fd = -1;
	return (NULL);
E 5
I 5
	return (flines[random() % NFORTUNES]);
E 5
}
E 4
E 1
