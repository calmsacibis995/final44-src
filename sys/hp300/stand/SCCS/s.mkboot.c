h61353
s 00003/00003/00302
d D 8.1 93/07/15 17:00:01 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00007/00273
d D 7.6 93/07/15 16:11:51 hibler 7 5
c allow for a third boot program
e
s 00005/00005/00275
d R 8.1 93/06/10 21:47:28 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00013/00240
d D 7.5 92/12/26 16:49:45 hibler 5 4
c Utah update (mostly disklabels)
e
s 00007/00006/00246
d D 7.4 92/10/11 10:01:46 bostic 4 3
c make kernel includes standard
e
s 00034/00005/00218
d D 7.3 92/06/18 21:33:30 hibler 3 2
c merge with latest Utah version
e
s 00001/00001/00222
d D 7.2 90/12/16 16:39:36 bostic 2 1
c kernel reorg
e
s 00223/00000/00000
d D 7.1 90/05/08 22:46:09 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef lint
D 7
char copyright[] =
D 3
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 3
I 3
"@(#) Copyright (c) 1990 The Regents of the University of California.\n\
E 3
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
D 8
"@(#) Copyright (c) 1990, 1993\n\
E 8
I 8
"%Z% Copyright (c) 1990, 1993\n\
E 8
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
static char sccsid[] = "@(#)mkboot.c	7.2 (Berkeley) 12/16/90";
E 3
#endif /* not lint */

D 2
#include "machine/machparam.h"
E 2
I 2
D 3
#include "../include/param.h"
E 3
I 3
D 4
#include "sys/param.h"
#include "sys/exec.h"
#include "sys/file.h"
E 3
E 2
#include "volhdr.h"
E 4
I 4
#include <sys/param.h>
#include <sys/exec.h>
#include <sys/file.h>
E 4
D 3
#include <sys/exec.h>
#include <sys/file.h>
E 3
I 3

I 4
#include <hp300/stand/volhdr.h>

E 4
E 3
#include <stdio.h>
#include <ctype.h>

I 5
#define LIF_NUMDIR	8

#define LIF_VOLSTART	0
#define LIF_VOLSIZE	sizeof(struct lifvol)
#define LIF_DIRSTART	512
#define LIF_DIRSIZE	(LIF_NUMDIR * sizeof(struct lifdir))
#define LIF_FILESTART	8192

#define btolifs(b)	(((b) + (SECTSIZE - 1)) / SECTSIZE)
#define lifstob(s)	((s) * SECTSIZE)

E 5
int lpflag;
int loadpoint;
struct load ld;
struct lifvol lifv;
D 5
struct lifdir lifd[8];
E 5
I 5
struct lifdir lifd[LIF_NUMDIR];
E 5
struct exec ex;
char buf[10240];

I 5
/*
 * Old Format:
 *	sector 0:	LIF volume header (40 bytes)
 *	sector 1:	<unused>
 *	sector 2:	LIF directory (8 x 32 == 256 bytes)
 *	sector 3-:	LIF file 0, LIF file 1, etc.
 * where sectors are 256 bytes.
 *
 * New Format:
 *	sector 0:	LIF volume header (40 bytes)
 *	sector 1:	<unused>
 *	sector 2:	LIF directory (8 x 32 == 256 bytes)
 *	sector 3:	<unused>
 *	sector 4-31:	disklabel (~300 bytes right now)
 *	sector 32-:	LIF file 0, LIF file 1, etc.
 */
E 5
main(argc, argv)
	char **argv;
{
	int ac;
	char **av;
D 7
	int from1, from2, to;
E 7
I 7
	int from1, from2, from3, to;
E 7
	register int n;
D 7
	char *n1, *n2, *lifname();
E 7
I 7
	char *n1, *n2, *n3, *lifname();
E 7

	ac = --argc;
	av = ++argv;
	if (ac == 0)
		usage();
	if (!strcmp(av[0], "-l")) {
		av++;
		ac--;
		if (ac == 0)
			usage();
		sscanf(av[0], "0x%x", &loadpoint);
		lpflag++;
		av++;
		ac--;
	}
	if (ac == 0)
		usage();
	from1 = open(av[0], O_RDONLY, 0);
	if (from1 < 0) {
		perror("open");
		exit(1);
	}
	n1 = av[0];
	av++;
	ac--;
	if (ac == 0)
		usage();
D 7
	if (ac == 2) {
E 7
I 7
	if (ac > 1) {
E 7
		from2 = open(av[0], O_RDONLY, 0);
		if (from2 < 0) {
			perror("open");
			exit(1);
		}
		n2 = av[0];
		av++;
		ac--;
I 7
		if (ac > 1) {
			from3 = open(av[0], O_RDONLY, 0);
			if (from3 < 0) {
				perror("open");
				exit(1);
			}
			n3 = av[0];
			av++;
			ac--;
		} else
			from3 = -1;
E 7
	} else
D 7
		from2 = -1;
E 7
I 7
		from2 = from3 = -1;
E 7
	to = open(av[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (to < 0) {
		perror("open");
		exit(1);
	}
	/* clear possibly unused directory entries */
	strncpy(lifd[1].dir_name, "          ", 10);
	lifd[1].dir_type = -1;
	lifd[1].dir_addr = 0;
	lifd[1].dir_length = 0;
	lifd[1].dir_flag = 0xFF;
	lifd[1].dir_exec = 0;
	lifd[7] = lifd[6] = lifd[5] = lifd[4] = lifd[3] = lifd[2] = lifd[1];
	/* record volume info */
	lifv.vol_id = VOL_ID;
	strncpy(lifv.vol_label, "BOOT43", 6);
D 5
	lifv.vol_addr = 2;
E 5
I 5
	lifv.vol_addr = btolifs(LIF_DIRSTART);
E 5
	lifv.vol_oct = VOL_OCT;
D 5
	lifv.vol_dirsize = 1;
E 5
I 5
	lifv.vol_dirsize = btolifs(LIF_DIRSIZE);
E 5
	lifv.vol_version = 1;
	/* output bootfile one */
D 5
	lseek(to, 3 * SECTSIZE, 0);
E 5
I 5
	lseek(to, LIF_FILESTART, 0);
E 5
	putfile(from1, to);
D 5
	n = (ld.count + sizeof(ld) + (SECTSIZE - 1)) / SECTSIZE;
E 5
I 5
	n = btolifs(ld.count + sizeof(ld));
E 5
	strcpy(lifd[0].dir_name, lifname(n1));
	lifd[0].dir_type = DIR_TYPE;
D 5
	lifd[0].dir_addr = 3;
E 5
I 5
	lifd[0].dir_addr = btolifs(LIF_FILESTART);
E 5
	lifd[0].dir_length = n;
I 3
	bcddate(from1, lifd[0].dir_toc);
E 3
	lifd[0].dir_flag = DIR_FLAG;
	lifd[0].dir_exec = lpflag? loadpoint + ex.a_entry : ex.a_entry;
	lifv.vol_length = lifd[0].dir_addr + lifd[0].dir_length;
	/* if there is an optional second boot program, output it */
	if (from2 >= 0) {
D 5
		lseek(to, (3 + n) * SECTSIZE, 0);
E 5
I 5
		lseek(to, LIF_FILESTART+lifstob(n), 0);
E 5
		putfile(from2, to);
D 5
		n = (ld.count + sizeof(ld) + (SECTSIZE - 1)) / SECTSIZE;
E 5
I 5
		n = btolifs(ld.count + sizeof(ld));
E 5
		strcpy(lifd[1].dir_name, lifname(n2));
		lifd[1].dir_type = DIR_TYPE;
D 5
		lifd[1].dir_addr = 3 + lifd[0].dir_length;
E 5
I 5
		lifd[1].dir_addr = lifv.vol_length;
E 5
		lifd[1].dir_length = n;
I 3
		bcddate(from2, lifd[1].dir_toc);
E 3
		lifd[1].dir_flag = DIR_FLAG;
		lifd[1].dir_exec = lpflag? loadpoint + ex.a_entry : ex.a_entry;
		lifv.vol_length = lifd[1].dir_addr + lifd[1].dir_length;
I 7
	}
	/* ditto for three */
	if (from3 >= 0) {
		lseek(to, LIF_FILESTART+lifstob(lifd[0].dir_length+n), 0);
		putfile(from3, to);
		n = btolifs(ld.count + sizeof(ld));
		strcpy(lifd[2].dir_name, lifname(n3));
		lifd[2].dir_type = DIR_TYPE;
		lifd[2].dir_addr = lifv.vol_length;
		lifd[2].dir_length = n;
		bcddate(from3, lifd[2].dir_toc);
		lifd[2].dir_flag = DIR_FLAG;
		lifd[2].dir_exec = lpflag? loadpoint + ex.a_entry : ex.a_entry;
		lifv.vol_length = lifd[2].dir_addr + lifd[2].dir_length;
E 7
	}
	/* output volume/directory header info */
D 5
	lseek(to, 0 * SECTSIZE, 0);
	write(to, &lifv, sizeof(lifv));
	lseek(to, 2 * SECTSIZE, 0);
	write(to, lifd, sizeof(lifd));
E 5
I 5
	lseek(to, LIF_VOLSTART, 0);
	write(to, &lifv, LIF_VOLSIZE);
	lseek(to, LIF_DIRSTART, 0);
	write(to, lifd, LIF_DIRSIZE);
E 5
	exit(0);
}

putfile(from, to)
{
	register int n, tcnt, dcnt;

	n = read(from, &ex, sizeof(ex));
	if (n != sizeof(ex)) {
		fprintf(stderr, "error reading file header\n");
		exit(1);
	}
	if (ex.a_magic == OMAGIC) {
		tcnt = ex.a_text;
		dcnt = ex.a_data;
	}
	else if (ex.a_magic == NMAGIC) {
		tcnt = (ex.a_text + PGOFSET) & ~PGOFSET;
		dcnt = ex.a_data;
	}
	else {
		fprintf(stderr, "bad magic number\n");
		exit(1);
	}
	ld.address = lpflag ? loadpoint : ex.a_entry;
	ld.count = tcnt + dcnt;
	write(to, &ld, sizeof(ld));
	while (tcnt) {
		n = sizeof(buf);
		if (n > tcnt)
			n = tcnt;
		n = read(from, buf, n);
		if (n < 0) {
			perror("read");
			exit(1);
		}
		if (n == 0) {
			fprintf(stderr, "short read\n");
			exit(1);
		}
		if (write(to, buf, n) < 0) {
			perror("write");
			exit(1);
		}
		tcnt -= n;
	}
	while (dcnt) {
		n = sizeof(buf);
		if (n > dcnt)
			n = dcnt;
		n = read(from, buf, n);
		if (n < 0) {
			perror("read");
			exit(1);
		}
		if (n == 0) {
			fprintf(stderr, "short read\n");
			exit(1);
		}
		if (write(to, buf, n) < 0) {
			perror("write");
			exit(1);
		}
		dcnt -= n;
	}
}

usage()
{
	fprintf(stderr,
		"usage:  mkboot [-l loadpoint] prog1 [ prog2 ] outfile\n");
	exit(1);
}

char *
lifname(str)
 char *str;
{
	static char lname[10] = "SYS_XXXXX";
	register int i;

	for (i = 4; i < 9; i++) {
		if (islower(*str))
			lname[i] = toupper(*str);
		else if (isalnum(*str) || *str == '_')
			lname[i] = *str;
		else
			break;
		str++;
	}
	for ( ; i < 10; i++)
		lname[i] = '\0';
	return(lname);
I 3
}

D 4
#include "sys/stat.h"
#include "/usr/include/time.h"	/* XXX */
E 4
I 4
#include <sys/stat.h>
#include <time.h>	/* XXX */
E 4

bcddate(fd, toc)
	int fd;
	char *toc;
{
	struct stat statb;
	struct tm *tm;

	fstat(fd, &statb);
	tm = localtime(&statb.st_ctime);
	*toc = ((tm->tm_mon+1) / 10) << 4;
	*toc++ |= (tm->tm_mon+1) % 10;
	*toc = (tm->tm_mday / 10) << 4;
	*toc++ |= tm->tm_mday % 10;
	*toc = (tm->tm_year / 10) << 4;
	*toc++ |= tm->tm_year % 10;
	*toc = (tm->tm_hour / 10) << 4;
	*toc++ |= tm->tm_hour % 10;
	*toc = (tm->tm_min / 10) << 4;
	*toc++ |= tm->tm_min % 10;
	*toc = (tm->tm_sec / 10) << 4;
	*toc |= tm->tm_sec % 10;
E 3
}
E 1
