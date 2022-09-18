h05272
s 00002/00002/00069
d D 8.1 93/06/06 16:34:10 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00067
d D 5.5 93/05/03 15:01:50 hibler 13 12
c add t3000
e
s 00001/00011/00066
d D 5.4 90/06/01 17:46:36 bostic 12 11
c new copyright notice
e
s 00015/00004/00062
d D 5.3 88/09/02 12:04:31 bostic 11 10
c add Berkeley specific copyright
e
s 00004/00000/00062
d D 5.2 86/04/03 16:55:29 donn 10 9
c Added an entry for Kirk Smith's USR Courier driver.
e
s 00007/00001/00055
d D 5.1 85/04/30 12:44:09 dist 9 8
c Add copyright
e
s 00005/00000/00051
d D 4.8 85/04/11 16:43:32 miriam 8 7
c Include hayes driver.
e
s 00013/00004/00038
d D 4.7 83/06/25 01:13:05 sam 7 6
c so much...clean up after ralph's merge of wendel and mo code;
c purge VMUNIX include since changes for signals make it no longer portable 
c to systems other than 4.2; fix ventel for no echo strapping; do setjmps 
c instead of assuming interrupted system calls; purge lcmd, if people use 
e
s 00008/00001/00034
d D 4.6 83/06/15 13:51:28 ralph 6 5
c changes for local info, parity, vadic auto dialers
e
s 00000/00000/00035
d D 4.5 81/11/29 22:48:56 sam 5 4
c reformatting
e
s 00004/00000/00031
d D 4.4 81/11/20 10:28:09 sam 4 3
c added ventel entry
e
s 00005/00002/00026
d D 4.3 81/10/09 15:27:47 sam 3 2
c shannon changes to support DF02+DF03 -- require kernel hack
e
s 00012/00006/00016
d D 4.2 81/09/17 09:43:32 sam 2 1
c split out bizcomp 1031 and 1022
e
s 00022/00000/00000
d D 4.1 81/05/09 16:45:08 root 1 0
c date and time created 81/05/09 16:45:08 by root
e
u
U
t
T
I 9
/*
D 11
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 14
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 12
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
 */

E 9
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif
E 9
I 9
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 9

E 7
#include "tip.h"

D 3
extern int df_dialer(), df_disconnect(), df_abort(),
E 3
I 3
extern int df02_dialer(), df03_dialer(), df_disconnect(), df_abort(),
E 3
D 2
	   bizf_dialer(), biz_disconnect(), biz_abort(),
	   bizw_dialer(), dn_dialer(), dn_disconnect(),
	   dn_abort();
E 2
I 2
	   biz31f_dialer(), biz31_disconnect(), biz31_abort(),
	   biz31w_dialer(),
	   biz22f_dialer(), biz22_disconnect(), biz22_abort(),
	   biz22w_dialer(),
I 4
	   ven_dialer(), ven_disconnect(), ven_abort(),
I 8
	   hay_dialer(), hay_disconnect(), hay_abort(),
I 10
	   cour_dialer(), cour_disconnect(), cour_abort(),
I 13
	   t3000_dialer(), t3000_disconnect(), t3000_abort(),
E 13
E 10
E 8
I 6
D 7
	   vadic_dialer(), vadic_disconnect(), vadic_abort(),
E 7
I 7
	   v3451_dialer(), v3451_disconnect(), v3451_abort(),
E 7
	   v831_dialer(), v831_disconnect(), v831_abort(),
E 6
E 4
	   dn_dialer(), dn_disconnect(), dn_abort();
E 2

acu_t acutable[] = {
D 2
#if BIZCOMP
	"bizf",	bizf_dialer,	biz_disconnect,		biz_abort,
	"bizw", bizw_dialer,	biz_disconnect,		biz_abort,
E 2
I 2
#if BIZ1031
	"biz31f", biz31f_dialer, biz31_disconnect,	biz31_abort,
	"biz31w", biz31w_dialer, biz31_disconnect,	biz31_abort,
#endif
#if BIZ1022
	"biz22f", biz22f_dialer, biz22_disconnect,	biz22_abort,
	"biz22w", biz22w_dialer, biz22_disconnect,	biz22_abort,
E 2
#endif
#if DF02
D 3
	"df02",	df_dialer,	df_disconnect,		df_abort,
E 3
I 3
	"df02",	df02_dialer,	df_disconnect,		df_abort,
#endif
#if DF03
	"df03",	df03_dialer,	df_disconnect,		df_abort,
E 3
#endif
#if DN11
	"dn11",	dn_dialer,	dn_disconnect,		dn_abort,
I 4
#endif
#ifdef VENTEL
	"ventel",ven_dialer,	ven_disconnect,		ven_abort,
E 4
#endif
I 8
#ifdef HAYES
	"hayes",hay_dialer,	hay_disconnect,		hay_abort,
I 10
#endif
#ifdef COURIER
	"courier",cour_dialer,	cour_disconnect,	cour_abort,
I 13
#endif
#ifdef T3000
	"t3000",t3000_dialer,	t3000_disconnect,	t3000_abort,
E 13
E 10
#endif
E 8
I 6
D 7
#ifdef VADIC
	"vadic",vadic_dialer,	vadic_disconnect,	vadic_abort,
E 7
I 7
#ifdef V3451
#ifndef V831
	"vadic",v3451_dialer,	v3451_disconnect,	v3451_abort,
E 7
#endif
I 7
	"v3451",v3451_dialer,	v3451_disconnect,	v3451_abort,
#endif
E 7
#ifdef V831
I 7
#ifndef V3451
	"vadic",v831_dialer,	v831_disconnect,	v831_abort,
#endif
E 7
	"v831",v831_dialer,	v831_disconnect,	v831_abort,
#endif
E 6
	0,	0,		0,			0
};
I 8

E 8
D 6

E 6
E 1
