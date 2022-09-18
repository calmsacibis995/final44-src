/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	copy.c,v $
 * Revision 2.2  89/07/12  00:10:40  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static	char sccsid[] = "@(#)copy.c	1.11 88/02/08	SMI"; /* From ancient history */
#endif

#include <mon/sunromvec.h>

#define	BUFSIZ	(3*10*1024)	/* must be multiple of 10K, < 32K */

/*
 * Copy from to in large units.
 * Intended for use in bootstrap procedure.
 */
main()
{
	int from, to;
	char fbuf[50], tbuf[50];
	static char buffer[BUFSIZ];
	register int i;
	register int count = 0;

	printf("Standalone Copy\n");
	from = getdev("From", fbuf, 0);
	to = getdev("To", tbuf, 1);
	for (;;) {
		i = read(from, buffer, sizeof (buffer));
		if (i <= 0)
			break;
		if (write(to, buffer, i) != i) {
			printf("Write error\n");
			break;
		}
		count += i;
	}
	if (i < 0)
		printf("Read error\n");
	printf("Copy completed - %d bytes\n", count);
}

getdev(prompt, buf, mode)
	char *prompt, *buf;
	int mode;
{
	register int i;

	do {
		printf("%s: ", prompt);
		gets(buf);
		i = open(buf, mode);
	} while (i <= 0);
	return (i);
}
