/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	chklabel.c,v $
 * Revision 2.2  89/07/12  00:18:43  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)chklabel.c 1.3 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <stand/saio.h>
#include <sun/dklabel.h>

char msg_nolabel[] = "No label found - attempting boot anyway.\n";

/*
 * Checks a disk label, returns 0 for success, 1 for failure.
 * If the magic number is right but the checksum is wrong, prints
 * "Corrupt label" error message, otherwise is silent.
 */
chklabel(label)
	register struct dk_label *label;
{
	register int count, sum = 0;
	register short *sp;

	if (label->dkl_magic != DKL_MAGIC)
		return (1);
	count = sizeof (struct dk_label) / sizeof (short);
	sp = (short *)label;
	while (count--) 
		sum ^= *sp++;
	if (sum != 0) {
		printf("Corrupt label\n");
		return (1);
	}
	return (0);
}
