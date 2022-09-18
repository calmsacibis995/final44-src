h27270
s 00039/00044/00136
d D 5.4 91/01/20 16:17:17 bostic 11 10
c document the rest of the flags, use getopt(3)
e
s 00001/00011/00179
d D 5.3 90/06/01 18:40:25 bostic 10 9
c new copyright notice
e
s 00019/00007/00171
d D 5.2 89/05/11 14:15:20 bostic 9 7
c file reorg, pathnames.h, paths.h
e
s 00016/00000/00178
d R 5.2 87/06/02 14:19:58 bostic 8 7
c make vax specific
e
s 00014/00002/00164
d D 5.1 86/06/06 20:14:01 mckusick 7 6
c add copyright
e
s 00001/00000/00165
d D 4.6 83/07/10 19:17:59 sam 6 5
c insure exit 0 on success for make update script
e
s 00025/00009/00140
d D 4.5 83/07/07 15:37:16 sam 5 4
c add f flag to specify file
e
s 00103/00080/00046
d D 4.4 81/11/25 16:55:02 sam 4 3
c time to reformat
e
s 00009/00004/00117
d D 4.3 80/10/21 02:09:14 bill 3 2
c make more resilient to command line errors.
e
s 00037/00018/00084
d D 4.2 80/10/21 01:21:00 bill 2 1
c add option to limit number of tracks to be copied.
e
s 00102/00000/00000
d D 4.1 80/10/01 17:26:47 bill 1 0
c date and time created 80/10/01 17:26:47 by bill
e
u
U
t
T
I 7
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
D 10
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
 */

E 7
I 5
#ifndef lint
E 5
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 7
static char *sccsid ="%W% (Berkeley) %G%";
I 5
#endif
E 7
I 7
char copyright[] =
D 9
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 9
 All rights reserved.\n";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 7
E 5
E 2
D 4
int floppydes;
char *flopname = "/dev/floppy";
I 2
long dsize = 77 * 26 * 128;
int hflag;
int rflag;
E 4
E 2

I 5
#include <sys/file.h>
I 11
#include <stdio.h>
E 11
I 9
#include "pathnames.h"
E 9

E 5
D 4
main(argc,argv)
D 2
char *argv[];
E 2
I 2
register char **argv;
E 4
I 4
int	floppydes;
D 9
char	*flopname = "/dev/floppy";
E 9
I 9
char	*flopname = _PATH_FLOPPY;
E 9
long	dsize = 77 * 26 * 128;
int	hflag;
int	rflag;

main(argc, argv)
	register char **argv;
E 4
E 2
{
I 11
	extern char *optarg;
	extern int optind;
E 11
	static char buff[512];
D 2
	register count = 77 * 26 * 128, startad = -26 * 128;
	register int n, file;
E 2
I 2
	register long count;
	register startad = -26 * 128;
D 4
	register int n, file; register char *cp;
E 4
I 4
	register int n, file;
	register char *cp;
I 11
	int ch;
E 11
E 4
E 2

D 2
	if(argc==2) {
E 2
I 2
D 3
	for(cp = *++argv; --argc > 0; cp ++) {
E 3
I 3
D 4
	while((cp = *++argv), --argc > 0) {
E 3
	    if(*cp++!='-') continue;
	    while(*cp) switch(*cp++) {
	    case 'h':
		hflag++;
E 2
		printf("Halftime!\n");
D 2
		if(strcmp(argv[1],"-h")!=0)
			printf("Bad halftime option.\n"),
			exit(1);
E 2
		if((file = open("floppy",0))<0)
D 2
			printf("failed to open floppy image"),
			exit(1);
		goto halftime;
E 2
I 2
		    printf("failed to open floppy image, for reading\n"),
		    exit(1);
		continue;
	    case 't':
D 3
		dsize = atoi(*++argv) * 26 * 128;
		argc--;
		if (dsize <= 0)
E 3
I 3
		if(*cp >= '0' && *cp <= '9')
		    dsize = atoi(cp);
		else if(argc > 1) {
		    dsize = atoi(*++argv);
		    argc--;
		} else dsize = 77;
		if (dsize <= 0 || dsize > 77)
E 3
		    printf("Bad number of tracks\n"), exit(2);
I 3
		dsize *= 26 * 128;
E 3
		continue;
	    case 'r':
		rflag++;
	    }
E 4
I 4
D 11
	while ((cp = *++argv), --argc > 0) {
D 5
		if (*cp++!='-')
			continue;
		while (*cp)
E 5
I 5
		while (*cp) {
E 5
			switch(*cp++) {

I 5
			case '-':
				continue;

E 5
			case 'h':
				hflag++;
				printf("Halftime!\n");
D 5
				if ((file = open("floppy", 0)) < 0)
					printf("can't open \"floppy\"\n"),
				exit(1);
E 5
I 5
				if ((file = open("floppy", 0)) < 0) {
					printf("can't open \"floppy\"\n");
					exit(1);
				}
E 5
				continue;

I 5
			case 'f':
				if (argc < 1) {
					printf(
					    "flcopy: -f: missing file name\n");
					exit(1);
				}
				flopname = *++argv;
				argc--;
				break;

E 5
			case 't':
				if (*cp >= '0' && *cp <= '9')
					dsize = atoi(cp);
				else if (argc > 1) {
					dsize = atoi(*++argv);
					argc--;
				} else
					dsize = 77;
				if (dsize <= 0 || dsize > 77) {
					printf("Bad number of tracks\n");
					exit(2);
				}
				dsize *= 26 * 128;
				continue;

			case 'r':
				rflag++;
E 11
I 11
	while ((ch = getopt(argc, argv, "f:hrt:")) != EOF)
		switch(ch) {
		case 'f':
			flopname = optarg;
			break;
		case 'h':
			hflag = 1;
			printf("Halftime!\n");
			if ((file = open("floppy", 0)) < 0) {
				printf("can't open \"floppy\"\n");
				exit(1);
E 11
			}
I 5
			break;
I 11
		case 'r':
			rflag = 1;
			break;
		case 't':
			dsize = atoi(optarg);
			if (dsize <= 0 || dsize > 77) {
				(void)fprintf(stderr,
				    "flcopy: bad number of tracks (0 - 77).\n");
				exit(2);
			}
			dsize *= 26 * 128;
			break;
		case '?':
		default:
			usage();
E 11
		}
E 5
E 4
E 2
D 11
	}
E 11
I 11
	argc -= optind;
	argv += optind;

E 11
D 2
	file = creat("floppy",0666);
	close(file);
	file = open("floppy",2);
	if(file < 0) exit(1);
	for( ; count > 0 ; count -= 512) {
E 2
I 2
D 4
	if(!hflag) {
	    file = creat("floppy",0666);
	    close(file);
	    file = open("floppy",2);
	    if(file < 0)
		printf("failed to open floppy image"),
		exit(1);
	    for(count = dsize; count > 0 ; count -= 512) {
E 2
		n = count > 512 ? 512 : count ;
		lread(startad,n,buff);
		write(file,buff,n);
		startad += 512;
I 2
	    }
E 4
I 4
	if (!hflag) {
D 5
		file = creat("floppy", 0666);
		close(file);
		file = open("floppy", 2);
E 5
I 5
		file = open("floppy", O_RDWR|O_CREAT|O_TRUNC, 0666);
E 5
		if (file < 0) {
			printf("can't open \"floppy\"\n");
			exit(1);
		}
		for (count = dsize; count > 0 ; count -= 512) {
			n = count > 512 ? 512 : count;
			lread(startad, n, buff);
			write(file, buff, n);
			startad += 512;
		}
E 4
E 2
	}
D 2
halftime:
E 2
I 2
D 4
	if(rflag) exit(0);
E 4
I 4
	if (rflag)
		exit(0);
E 4
E 2
	printf("Change Floppy, Hit return when done.\n");
	gets(buff);
D 4
	lseek(file,0,0);
D 2
	count = 77 * 26 * 128; startad = -26 * 128;
E 2
I 2
	count = dsize; startad = -26 * 128;
E 2
	for( ; count > 0 ; count -= 512) {
		n = count > 512 ? 512 : count ;
		read(file,buff,n);
		lwrite(startad,n,buff);
E 4
I 4
	lseek(file, 0, 0);
	count = dsize;
	startad = -26 * 128;
	for ( ; count > 0 ; count -= 512) {
		n = count > 512 ? 512 : count;
		read(file, buff, n);
		lwrite(startad, n, buff);
E 4
		startad += 512;
	}
I 6
	exit(0);
E 6
}
I 4

E 4
rt_init()
{
	static initized = 0;
	int mode = 2;

D 4
	if(initized) return;
I 2
	if(rflag) mode = 0;
E 4
I 4
	if (initized)
		return;
	if (rflag)
		mode = 0;
E 4
E 2
	initized = 1;
D 4
	if((floppydes = open(flopname,mode)) < 0) {
E 4
I 4
	if ((floppydes = open(flopname, mode)) < 0) {
E 4
		printf("Floppy open failed\n");
		exit(1);
	}
}
D 4
		
long trans(logical)
register int logical;
E 4
I 4

/*
 * Logical to physical adress translation
 */
long
trans(logical)
	register int logical;
E 4
{
D 4
	/*  Logical to physical adress translation */
E 4
	register int sector, bytes, track;

	logical += 26 * 128;
	bytes = (logical & 127);
	logical >>= 7;
	sector = logical % 26;
D 4
	if(sector >= 13)
		sector = sector *2 +1;
E 4
I 4
	if (sector >= 13)
		sector = sector*2 +1;
E 4
	else
		sector *= 2;
	sector += 26 + ((track = (logical / 26)) - 1) * 6;
	sector %= 26;
D 4
	return( (((track *26) + sector) << 7) + bytes);
E 4
I 4
	return ((((track *26) + sector) << 7) + bytes);
E 4
}
D 4
lread(startad,count,obuff)
register startad, count;
register char * obuff;
E 4
I 4

lread(startad, count, obuff)
	register startad, count;
	register char *obuff;
E 4
{
	long trans();
	extern floppydes;
I 4

E 4
	rt_init();
D 4
		while( (count -= 128) >= 0) {
			lseek(floppydes, trans(startad), 0);
			read(floppydes,obuff,128);
			obuff += 128;
			startad += 128;
		}
E 4
I 4
	while ((count -= 128) >= 0) {
		lseek(floppydes, trans(startad), 0);
		read(floppydes, obuff, 128);
		obuff += 128;
		startad += 128;
	}
E 4
}
D 4
lwrite(startad,count,obuff)
register startad, count;
register char * obuff;
E 4
I 4

lwrite(startad, count, obuff)
	register startad, count;
	register char *obuff;
E 4
{
	long trans();
	extern floppydes;
I 4

E 4
	rt_init();
D 4
		while( (count -= 128) >= 0) {
			lseek(floppydes, trans(startad), 0);
			write(floppydes,obuff,128);
			obuff += 128;
			startad += 128;
		}
E 4
I 4
	while ((count -= 128) >= 0) {
		lseek(floppydes, trans(startad), 0);
		write(floppydes, obuff, 128);
		obuff += 128;
		startad += 128;
	}
I 11
}

usage()
{
	(void)fprintf(stderr, "usage: flcopy [-hr] [-f file] [-t ntracks]\n");
	exit(1);
E 11
E 4
}
E 1
