/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * $Log:	installboot.c,v $
 * Revision 2.3  89/03/09  20:26:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:14:06  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	lint
char copyright[] =
"@(#) Copyright (c) 1980, 1986 Regents of the University of California.\n\
 All rights reserved.\n";
#endif	not lint

#ifndef	lint
static char sccsid[] = "@(#)installboot.c	7.1 (Berkeley) 6/5/86";
#endif	not lint

#include <sys/param.h>
#include <sys/fs.h>

char bootimage[BBSIZE];

main(argc, argv)
	int argc;
	char *argv[];
{
	int fd;

	if (argc != 4) {
		printf("Usage: installboot bootblock bootprog device\n");
		exit(1);
	}
	fd = open(argv[1], 0);
	if (fd < 0) {
		perror(argv[1]);
		exit(1);
	}
	read(fd, bootimage, DEV_BSIZE);
	close(fd);
	fd = open(argv[2], 0);
	if (fd < 0) {
		perror(argv[2]);
		exit(1);
	}
	read(fd, &bootimage[DEV_BSIZE], BBSIZE - DEV_BSIZE);
	close(fd);
	fd = open(argv[3], 1);
	if (fd < 0) {
		perror(argv[3]);
		exit(1);
	}
	write(fd, bootimage, BBSIZE);
	close(fd);
}
