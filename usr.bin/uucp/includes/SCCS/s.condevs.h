h23174
s 00002/00002/00118
d D 8.1 93/06/06 22:08:09 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00022/00099
d D 4.10 93/05/16 00:48:13 torek 10 9
c ANSI C says no tokens after #else, #endif
e
s 00008/00001/00113
d D 4.9 91/04/24 17:28:35 bostic 9 8
c new copyright; att/bsd/shared
e
s 00001/00001/00113
d D 4.8 91/03/02 13:12:42 bostic 8 7
c ANSI, break up into multiple directories, new style Makefiles
e
s 00001/00001/00113
d D 4.7 88/05/05 11:21:43 rick 7 6
c add sccsid
e
s 00001/00001/00113
d D 4.6 86/02/13 14:44:27 bloom 6 5
c let's get the defines right
e
s 00006/00001/00108
d D 4.5 86/02/12 17:18:20 bloom 5 4
c add new dialer
e
s 00008/00000/00101
d D 4.4 86/01/24 13:19:23 bloom 4 3
c still more fixes and changes from rick@seismo
e
s 00001/00001/00100
d D 4.3 85/06/19 18:16:11 bloom 3 2
c fix from rick adams
e
s 00009/00002/00092
d D 4.2 85/04/10 15:19:13 ralph 2 1
c more changes from rick adams.
e
s 00094/00000/00000
d D 4.1 85/01/22 13:49:25 ralph 1 0
c date and time created 85/01/22 13:49:25 by ralph
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
D 9
/*	%W%	(Berkeley)	%G%	*/
E 9
I 9
/*-
D 11
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 9
E 7

D 2
#include <sys/types.h>
E 2
I 2
#include "uucp.h"
E 2
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <sgtty.h>
D 2
#include "uucp.h"
E 2
#ifdef VMSDTR	/* Modem control on vms(works dtr) */
#include <eunice/eunice.h>
#define TT$M_MODEM	0x00200000 /* These should be in a '.h' somewhere */
#define SS$_NORMAL	0x00000001
#define IO$_SETMODE	0x00000023
#define IO$_SENSEMODE	0x00000027
#endif

extern char devSel[];	/* name to pass to delock() in close */
extern int errno, next_fd;
extern jmp_buf Sjbuf;
D 8
extern int alarmtr();
E 8
I 8
extern void alarmtr();
E 8
int nulldev(), nodev(), Acuopn(), diropn(), dircls();

#ifdef DATAKIT
int dkopn();
D 10
#endif DATAKIT
E 10
I 10
#endif
E 10

#ifdef DN11
int dnopn(), dncls();
D 10
#endif DN11
E 10
I 10
#endif
E 10

#ifdef HAYES
D 3
int hysopn(), hyscls();
E 3
I 3
int hyspopn(), hystopn(), hyscls();
E 3
D 10
#endif HAYES
E 10
I 10
#endif
E 10

I 4
#ifdef HAYES2400
D 6
int hyspopn24(), hystop24n(), hyscls();
E 6
I 6
int hyspopn24(), hystopn24(), hyscls24();
E 6
D 10
#endif HAYES2400
E 10
I 10
#endif
E 10

E 4
#ifdef HAYESQ
int hysqopn(), hysqcls();  /* a version of hayes that doesn't use ret codes */
D 10
#endif HAYESQ
E 10
I 10
#endif
E 10

#ifdef NOVATION
int novopn(), novcls();
D 10
#endif NOVATION
E 10
I 10
#endif
E 10
I 4

#ifdef CDS224
int cdsopn224(), cdscls224();
D 10
#endif CDs224
E 10
I 10
#endif
E 10
E 4

#ifdef DF02
int df2opn(), df2cls();
D 10
#endif DF02
E 10
I 10
#endif
E 10

I 2
#ifdef DF112
int df12popn(), df12topn(), df12cls();
D 10
#endif DF112
E 10
I 10
#endif
E 10

E 2
#ifdef PNET
int pnetopn();
D 10
#endif PNET
E 10
I 10
#endif
E 10

#ifdef VENTEL
int ventopn(), ventcls();
D 10
#endif VENTEL
E 10
I 10
#endif
E 10
I 2

#ifdef PENRIL
int penopn(), pencls();
D 10
#endif PENRIL
E 10
I 10
#endif
E 10
E 2

#ifdef	UNETTCP
#define TO_ACTIVE	0
int unetopn(), unetcls();
D 10
#endif UNETTCP
E 10
I 10
#endif
E 10

#ifdef BSDTCP
int bsdtcpopn(), bsdtcpcls();
D 10
#endif BSDTCP
E 10
I 10
#endif
E 10

#ifdef VADIC
int vadopn(), vadcls();
D 10
#endif VADIC
E 10
I 10
#endif
E 10

#ifdef VA212
int va212opn(), va212cls();
D 10
#endif VA212
E 10
I 10
#endif
E 10

#ifdef VA811S
int va811opn(), va811cls();
D 10
#endif VA811S
E 10
I 10
#endif
E 10

#ifdef VA820
int va820opn(), va820cls();
D 10
#endif VA820
E 10
I 10
#endif
E 10

#ifdef	RVMACS
int rvmacsopn(), rvmacscls();
#endif

#ifdef	VMACS
int vmacsopn(), vmacscls();
#endif

#ifdef MICOM
int micopn(), miccls();
D 10
#endif MICOM
E 10
I 10
#endif
E 10

#ifdef SYTEK
int sykopn(), sykcls();
D 5
#endif
E 5
I 5
D 10
#endif SYTEK
E 10
I 10
#endif
E 10

#ifdef ATT2224
int attopn(), attcls();
D 10
#endif	ATT2224

E 10
I 10
#endif
E 10
E 5
E 1
