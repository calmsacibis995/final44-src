h42630
s 00002/00002/00054
d D 8.1 93/06/06 15:15:45 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00047
d D 1.5 90/04/09 18:26:17 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00011/00006/00038
d D 1.4 83/10/01 01:18:19 mckusick 4 3
c add 750 fault conditions
e
s 00004/00004/00040
d D 1.3 83/01/10 18:33:50 mckusick 3 2
c ifdef VAX => ifdef vax
e
s 00011/00000/00033
d D 1.2 82/02/08 20:20:04 mckusic 2 1
c add return statements after errors
e
s 00033/00000/00000
d D 1.1 82/02/02 23:09:47 mckusick 1 0
c date and time created 82/02/02 23:09:47 by mckusick
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1982 Regents of the University of California */
E 5
I 5
/*-
D 6
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */
E 5

D 5
static char sccsid[] = "%Z%%M% %I% %G%";
E 5
I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include	<signal.h>
D 3
#include	"whoami.h"
E 3

/*
 * catch runtime arithmetic errors
 */
EXCEPT(signum, type)
	int signum, type;
{
	signal(SIGFPE, EXCEPT);
D 3
#ifndef VAX
E 3
I 3
#ifndef vax
E 3
	ERROR("Overflow, underflow, or division by zero in arithmetic operation\n");
I 2
	return;
E 2
D 3
#else
E 3
I 3
#endif notvax
#ifdef vax
E 3
I 2
	/*
	 * The values for this switch statement come from page 12-5 of
	 * Volume 1 of the 1978 VAX 11/780 Architecture Handbook
	 */
E 2
	switch (type) {
D 4
	case 1:
E 4
I 4
	case FPE_INTOVF_TRAP:
E 4
		ERROR("Integer overflow\n");
I 2
		return;
E 2
D 4
	case 2:
E 4
I 4
	case FPE_INTDIV_TRAP:
E 4
		ERROR("Integer division by zero\n");
I 2
		return;
E 2
D 4
	case 3:
E 4
I 4
	case FPE_FLTOVF_TRAP:
	case FPE_FLTOVF_FAULT:
E 4
		ERROR("Real overflow\n");
I 2
		return;
E 2
D 4
	case 4:
E 4
I 4
	case FPE_FLTDIV_TRAP:
	case FPE_FLTDIV_FAULT:
E 4
		ERROR("Real division by zero\n");
I 2
		return;
E 2
D 4
	case 5:
E 4
I 4
	case FPE_FLTUND_TRAP:
	case FPE_FLTUND_FAULT:
E 4
		ERROR("Real underflow\n");
I 2
		return;
I 4
	case FPE_DECOVF_TRAP:
	case FPE_SUBRNG_TRAP:
E 4
E 2
	default:
D 4
		ERROR("Panic: Computational error in interpreter\n");
E 4
I 4
		ERROR("Undefined arithmetic exception type (%d)\n", type);
E 4
I 2
		return;
E 2
	}
D 3
#endif
E 3
I 3
#endif vax
E 3
}
E 1
