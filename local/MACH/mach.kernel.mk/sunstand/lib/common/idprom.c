/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	idprom.c,v $
 * Revision 2.2  89/07/12  00:19:17  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)idprom.c 1.2 88/02/08 Copyright (c) 1983 by Sun Microsystems, Inc.
 */

#include <mon/idprom.h>

/*
 * Read the ID prom and check it.
 * Arguments are a format number and an address to store prom contents at.
 *
 * Result is format number if prom has the right format and good checksum.
 * Result is -1		   if prom has the right format and bad checksum.
 * Result is prom's format if prom has the wrong format.
 *
 * If the PROM is in the wrong format, the addressed area is not changed.
 *
 * This routine must know the size, and checksum algorithm, of each format.
 * (Currently there's only one.)
 */

int
idprom(format, idp)
	unsigned char format;
	register struct idprom *idp;
{
	unsigned char *cp, sum=0, promform;
	short i;

	getidprom(&promform, 1);		/* Get format byte */
	if (format != promform)
		return promform;
	getidprom((unsigned char *)idp, sizeof(*idp));	/* The whole thing */
	cp = (unsigned char *)idp;
	for (i=0; i<16; i++)
		sum ^= *cp++;
	if (sum != 0)
		return -1;
	return promform;
}
