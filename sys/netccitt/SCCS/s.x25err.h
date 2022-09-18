h03916
s 00002/00002/00036
d D 8.1 93/06/10 22:54:24 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00000/00024
d D 7.2 90/05/11 15:22:28 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00024/00000/00000
d D 7.1 90/05/11 11:19:45 sklower 1 0
c date and time created 90/05/11 11:19:45 by sklower
e
u
U
t
T
I 2
/*
 * Copyright (c) University of British Columbia, 1984
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/* 
 *  
 *  X.25 Reset and Clear errors and diagnostics.  These values are 
 *  returned in the u_error field of the u structure.
 *
 */

#define EXRESET		100	/* Reset: call reset			*/
#define EXROUT		101	/* Reset: out of order			*/
#define EXRRPE		102	/* Reset: remote procedure error	*/
#define EXRLPE		103	/* Reset: local procedure error		*/
#define EXRNCG		104	/* Reset: network congestion		*/

#define EXCLEAR		110	/* Clear: call cleared			*/
#define EXCBUSY 	111	/* Clear: number busy			*/
#define EXCOUT		112	/* Clear: out of order			*/
#define EXCRPE		113	/* Clear: remote procedure error	*/
#define EXCRRC		114	/* Clear: collect call refused		*/
#define EXCINV		115	/* Clear: invalid call			*/
#define EXCAB		116	/* Clear: access barred			*/
#define EXCLPE		117	/* Clear: local procedure error		*/
#define EXCNCG		118	/* Clear: network congestion		*/
#define EXCNOB		119	/* Clear: not obtainable		*/

E 1
