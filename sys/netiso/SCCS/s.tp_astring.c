h63262
s 00002/00002/00046
d D 8.1 93/06/10 23:20:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00048
d D 7.5 92/06/29 16:43:39 sklower 5 4
c get rid of spurious reference to stdio
e
s 00009/00003/00042
d D 7.4 91/05/06 19:24:16 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00000/00042
d D 7.3 89/08/29 13:44:48 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00000/00042
d D 7.2 89/04/22 11:54:40 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00042/00000/00000
d D 7.1 88/12/14 15:29:54 sklower 1 0
c date and time created 88/12/14 15:29:54 by sklower
e
u
U
t
T
I 1
D 4
/* $Header$ */
/* $Source$ */
I 3
/*	%W% (Berkeley) %G% */
E 4
I 4
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 4
E 3
D 5
#ifndef _NFILE
#include <stdio.h>
#endif _NFILE
E 5
char *tp_sstring[] = {
"ST_ERROR(0x0)",
"TP_CLOSED(0x1)",
"TP_CRSENT(0x2)",
"TP_AKWAIT(0x3)",
"TP_OPEN(0x4)",
"TP_CLOSING(0x5)",
"TP_REFWAIT(0x6)",
"TP_LISTENING(0x7)",
I 3
"TP_CONFIRMING(0x8)",
E 3
};

char *tp_estring[] = {
"TM_inact(0x0)",
"TM_retrans(0x1)",
"TM_sendack(0x2)",
"TM_notused(0x3)",
"TM_reference(0x4)",
"TM_data_retrans(0x5)",
"ER_TPDU(0x6)",
"CR_TPDU(0x7)",
"DR_TPDU(0x8)",
"DC_TPDU(0x9)",
"CC_TPDU(0xa)",
"AK_TPDU(0xb)",
"DT_TPDU(0xc)",
"XPD_TPDU(0xd)",
"XAK_TPDU(0xe)",
"T_CONN_req(0xf)",
"T_DISC_req(0x10)",
"T_LISTEN_req(0x11)",
"T_DATA_req(0x12)",
"T_XPD_req(0x13)",
"T_USR_rcvd(0x14)",
"T_USR_Xrcvd(0x15)",
"T_DETACH(0x16)",
"T_NETRESET(0x17)",
I 3
"T_ACPT_req(0x18)",
E 3
};
E 1
