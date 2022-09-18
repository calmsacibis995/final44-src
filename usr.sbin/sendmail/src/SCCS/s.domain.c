h34200
s 00000/00002/00773
d D 8.47 95/06/20 10:46:32 eric 114 113
c h_errno now in conf.h
e
s 00007/00001/00768
d D 8.46 95/06/19 18:12:44 eric 113 112
c another wildcard MX hack
e
s 00029/00000/00740
d D 8.45 95/06/15 19:24:12 eric 112 111
c change bestmx map to not do resolver domain searching (RES_DNSRCH)
e
s 00007/00009/00733
d D 8.44 95/06/15 14:04:43 eric 111 110
c improved wildcard MX handling
e
s 00007/00000/00735
d D 8.43 95/06/10 18:11:26 eric 110 109
c add DontExpandCnames option -- IETF seems to be moving in this direction
e
s 00003/00002/00732
d D 8.42 95/06/10 10:18:57 eric 109 108
c improved debugging
e
s 00002/00000/00732
d D 8.41 95/05/28 11:49:34 eric 108 107
c lint
e
s 00002/00000/00730
d D 8.40 95/05/24 16:23:27 eric 107 106
c don't leave rcode uninitialized if everything is OK
e
s 00001/00001/00729
d D 8.39 95/05/19 17:10:20 eric 106 105
c don't have getmxrr return 1 for unknown addresses
e
s 00001/00001/00729
d D 8.38 95/05/19 16:00:13 eric 105 104
c fix compile problems on various platforms
e
s 00016/00039/00714
d D 8.37 95/05/13 15:06:01 eric 104 103
c put getcanonname into service switch
e
s 00001/00001/00752
d D 8.36 95/04/21 09:57:06 eric 103 102
c update copyright notice
e
s 00000/00002/00753
d D 8.35 95/04/07 19:15:27 eric 102 101
c eliminate unnecessary redundant #include
e
s 00002/00003/00753
d D 8.34 95/03/31 10:51:54 eric 101 100
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00001/00001/00755
d D 8.33 95/03/10 12:21:53 eric 100 98
c improved security when opening files
e
s 00001/00000/00743
d D 8.19.1.1 95/03/06 16:02:59 eric 99 84
c avoid possible attacks against hidden files; this isn't perfect
e
s 00002/00001/00754
d D 8.32 95/03/06 15:11:49 eric 98 97
c fix some race conditions for file opens
e
s 00004/00003/00751
d D 8.31 95/02/23 16:07:27 eric 97 95
c cleanup to make gcc -Winitialized happier
e
s 00002/00001/00753
d R 8.31 95/02/20 08:24:22 eric 96 95
c look in $=j as well as $=w for MX short circuit records per IDA
e
s 00002/00007/00752
d D 8.30 95/01/24 08:28:37 eric 95 94
c use wordinclass() abstraction for searching classes
e
s 00003/00013/00756
d D 8.29 94/11/13 15:55:19 eric 94 93
c if MX lookup fails, the name may still be good (because of NIS
c or /etc/hosts entries) -- don't reject it too quickly
e
s 00001/00037/00768
d D 8.28 94/11/13 09:52:39 eric 93 92
c set UseNameServer on the basis of whether "dns" is in the service switch
e
s 00002/00001/00803
d D 8.27 94/10/24 21:19:18 eric 92 91
c get it to compile on other environments
e
s 00046/00000/00758
d D 8.26 94/10/24 18:32:29 eric 91 90
c first cut at service switch abstraction
e
s 00015/00002/00743
d D 8.25 94/09/03 08:39:18 eric 90 89
c try to auto-adapt to misconfigured /etc/hosts file that have
c short names preceding the long names
e
s 00001/00001/00744
d D 8.24 94/08/15 06:43:02 eric 89 88
c eliminate compiler warning
e
s 00014/00007/00731
d D 8.23 94/07/11 07:24:59 eric 88 87
c clean up resolver casts to handle both old and new libraries
e
s 00002/00002/00736
d D 8.22 94/06/18 09:55:53 eric 87 86
c avoid linking problems against BIND 4.9.3
e
s 00006/00011/00732
d D 8.21 94/06/17 17:39:58 eric 86 85
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00001/00001/00742
d D 8.20 94/06/17 11:12:51 eric 85 84
c Cray fixes from Eric Wassenaar
e
s 00002/00002/00741
d D 8.19 94/03/11 14:42:03 eric 84 83
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00012/00002/00731
d D 8.18 94/03/07 12:10:25 eric 83 82
c fix CNAME loop problem: gave error messages and requeued messages
e
s 00004/00000/00729
d D 8.17 94/03/06 09:06:06 eric 82 81
c apply workaround to broken res_search on Ultrix
e
s 00002/00000/00727
d D 8.16 94/02/25 20:33:29 eric 81 80
c add additional error message for configuration error
e
s 00006/00000/00721
d D 8.15 94/02/25 10:15:06 eric 80 79
c diagnose problems caused by resolver bugs (sigh)
e
s 00006/00000/00715
d D 8.14 94/02/17 09:49:00 eric 79 78
c some extra debugging info
e
s 00004/00000/00711
d D 8.13 94/02/09 15:21:01 eric 78 77
c strip trailing dot off of names that have one in getcanonname
c to avoid ending up with double dots
e
s 00001/00001/00710
d D 8.12 94/01/31 17:34:00 eric 77 76
c use better MX hash function
e
s 00006/00002/00705
d D 8.11 94/01/15 12:38:52 eric 76 75
c Unicos portability changes
e
s 00064/00000/00643
d D 8.10 93/12/21 14:52:15 eric 75 74
c if HOSTALIASES is set, be sure to use it during canonification
e
s 00006/00000/00637
d D 8.9 93/11/26 18:47:21 eric 74 72
c if option I is not set, be more forgiving on host unknown errors
c to allow fallback to hosts table
e
s 00018/00003/00634
d D 8.8.1.1 93/11/20 10:14:12 eric 73 72
c changes to delete FallBackMX if it is already in the MX list; save
c for major release
e
s 00005/00001/00632
d D 8.8 93/09/29 14:35:47 eric 72 71
c canonify [host] addresses in getmxrr
e
s 00021/00001/00612
d D 8.7 93/09/29 13:12:41 eric 71 70
c improve connection caching by making [host] look like host after
c hostsignature call
e
s 00002/00002/00611
d D 8.6 93/07/24 08:04:41 eric 70 69
c really ignore MX records if !trymx
e
s 00006/00002/00607
d D 8.5 93/07/23 09:59:29 eric 69 68
c really ignore MX if !trymx in getcanonname; minimize unnecessary
c nameserver calls
e
s 00004/00000/00605
d D 8.4 93/07/21 11:45:43 eric 68 67
c old 4.3BSD changes
e
s 00002/00002/00603
d D 8.3 93/07/19 12:09:45 eric 67 66
c FallBackMX wasn't properly supressed if it pointed to yourself
e
s 00063/00050/00542
d D 8.2 93/07/16 10:29:55 eric 66 65
c add 'w' option handling; be sure to fully qualify all MX addresses
e
s 00000/00000/00592
d D 8.1 93/06/07 10:31:36 bostic 65 64
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00002/00579
d D 6.23 93/06/07 10:30:11 bostic 64 63
c check for CNAME loops
e
s 00001/00001/00580
d D 6.22 93/06/05 17:07:54 eric 63 62
c lint-style cleanup
e
s 00012/00006/00569
d D 6.21 93/04/26 13:13:55 eric 62 61
c have getmxrr look at $=w to determine local host name
e
s 00005/00006/00570
d D 6.20 93/04/26 12:44:09 eric 61 59
c fix problem that can cause CNAMEs to be misinterpreted
e
s 00124/00000/00576
d D 6.19.1.1 93/04/14 15:30:19 eric 60 59
c some first thoughts at a MAILB lookup
e
s 00008/00006/00568
d D 6.19 93/04/14 07:47:14 eric 59 58
c random cleanup -- nothing major
e
s 00032/00032/00542
d D 6.18 93/04/01 14:59:14 eric 58 57
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00021/00002/00553
d D 6.17 93/03/31 08:12:41 eric 57 56
c FallBackMX fixes
e
s 00008/00005/00547
d D 6.16 93/03/29 17:24:23 eric 56 55
c fix botch with getmxrr when there was no MX record
e
s 00007/00002/00545
d D 6.15 93/03/29 12:42:48 eric 55 54
c implement FallBackMX
e
s 00009/00001/00538
d D 6.14 93/03/29 11:39:01 eric 54 53
c do recursive evaluation of CNAMEs
e
s 00002/00002/00537
d D 6.13 93/03/23 19:50:50 eric 53 52
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00008/00001/00531
d D 6.12 93/03/13 22:53:02 eric 52 51
c fix MX signature to always have trailing dot so compares work right
e
s 00003/00001/00529
d D 6.11 93/03/06 08:31:06 eric 51 50
c print query class in debugging output
e
s 00016/00005/00514
d D 6.10 93/03/05 15:09:43 eric 50 49
c avoid loops on nameserver NO_DATA errors; getsockname can return
c zero length names on SunOS
e
s 00010/00002/00509
d D 6.9 93/03/03 11:44:28 eric 49 48
c optimizations; don't ignore _res.options bits in getcanonname()
e
s 00029/00003/00482
d D 6.8 93/03/03 10:05:29 eric 48 47
c don't assume that T_ANY returns all info for a domain
e
s 00022/00002/00463
d D 6.7 93/02/26 08:20:03 eric 47 46
c portability changes for 64 bit machines like the Alpha
e
s 00003/00002/00462
d D 6.6 93/02/20 13:46:35 eric 46 45
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00001/00001/00463
d D 6.5 93/02/18 15:12:45 eric 45 44
c increase size of searchlist to allow for extra "" entry
e
s 00008/00006/00456
d D 6.4 93/02/15 16:44:49 eric 44 43
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00133/00164/00329
d D 6.3 93/02/12 11:51:16 eric 43 42
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00075/00013/00418
d D 6.2 93/01/10 12:56:45 eric 42 41
c MX piggybacking, based on code from John Myers@CMU; allow checkcompat
c to return -1 to mean tempfail; bug fix in m_mno computation
e
s 00000/00000/00431
d D 6.1 92/12/21 16:08:24 eric 41 40
c Release 6
e
s 00000/00001/00431
d D 5.39 92/12/20 11:14:18 eric 40 39
c change random constants to be #defines
e
s 00003/00007/00429
d D 5.38 92/12/18 10:06:34 eric 39 38
c allow I option to arbitrarily set and clear resolver options
e
s 00052/00012/00384
d D 5.37 92/12/18 08:52:58 eric 38 37
c when searching the name server, when there is at least one dot,
c search the unmodified name first (this is so foo.cs will get the
c Czechoslovakian foo, for example)
e
s 00021/00009/00375
d D 5.36 92/12/15 12:34:44 eric 37 36
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00017/00008/00367
d D 5.35 92/09/23 15:04:28 eric 36 35
c fix bug in envp handling in main(); always put trailing dot on
c results of MX lookups
e
s 00001/00001/00374
d D 5.34 92/06/23 12:24:13 eric 35 34
c fix botch in random choice function for preferences
e
s 00002/00002/00373
d D 5.33 92/03/06 17:05:15 eric 34 33
c print host name in debugging info
e
s 00009/00004/00366
d D 5.32 91/12/13 12:09:28 eric 33 32
c fix lockf code; have getcanonname recognize canonical names
e
s 00000/00003/00370
d D 5.31 91/11/11 16:39:52 eric 32 31
c __hostalias is a front end issue, not a back end issue
e
s 00142/00041/00231
d D 5.30 91/10/07 11:31:21 eric 31 30
c have DNS return what matched on a T_CNAME query
e
s 00011/00005/00261
d D 5.29 91/10/05 10:06:10 eric 30 29
c return indication of whether nameserver found a match
e
s 00002/00002/00264
d D 5.28 91/10/02 12:59:31 eric 29 28
c reverse sense of w (wildcard MX) flag to default to the safest option,
c instead of the most desirable option.
e
s 00002/00006/00264
d D 5.27 91/09/03 10:04:54 karels 28 27
c use #define for dn_skipname from resolv.h
e
s 00004/00032/00266
d D 5.26 91/07/29 13:04:45 eric 27 26
c better hack for __dn_skipname
e
s 00001/00001/00297
d D 5.25 91/07/26 14:59:53 eric 26 25
c cleanup for non-ANSI C compilers
e
s 00034/00005/00264
d D 5.24 91/07/25 11:12:07 eric 25 24
c some compatibility with SunOS for future work here at Berkeley;
c change NO_WILDCARD_MX compilation flag to configuration option "w".
e
s 00010/00008/00259
d D 5.23 91/03/02 17:15:21 bostic 24 23
c ANSI
e
s 00001/00011/00266
d D 5.22 90/06/01 19:01:33 bostic 23 22
c new copyright notice
e
s 00001/00001/00276
d D 5.21 90/04/18 12:15:25 bostic 22 21
c don't break old makefiles; bug report 4.3BSD/usr.lib/114
e
s 00001/00000/00276
d D 5.20 90/03/05 11:41:42 bostic 21 20
c fix h_errno for ANSI C variable scoping
e
s 00000/00008/00276
d D 5.19 89/01/01 17:17:12 bostic 20 19
c remove DEBUG
e
s 00021/00001/00263
d D 5.18 89/01/01 13:26:14 phil 19 18
c Add getcanonname using gethostbyname if NAMED_BIND undefined.
e
s 00015/00001/00249
d D 5.17 88/12/28 19:45:42 bostic 18 17
c add NO_WILDCARD_MX #define
e
s 00032/00009/00218
d D 5.16 88/09/20 23:45:11 eric 17 16
c some cleanup of I option handling
e
s 00012/00011/00215
d D 5.15 88/06/30 14:58:51 bostic 16 15
c install approved copyright notice
e
s 00001/00001/00225
d D 5.14 88/05/03 17:13:42 bostic 15 14
c change T_ANY to T_CNAME; fix match where sites have *.domain for
c MX records
e
s 00001/00001/00225
d D 5.13 88/04/19 13:42:02 bostic 14 13
c change NO_ADDRESS to NO_DATA
e
s 00103/00170/00123
d D 5.12 88/04/01 15:33:06 bostic 13 11
c redo getcanonname and getmxrr for new name server
e
s 00104/00171/00122
d R 5.12 88/04/01 15:30:51 bostic 12 11
c redo getmxrr and getcanonname for new name server
e
s 00003/00009/00290
d D 5.11 88/03/24 09:00:16 bostic 11 10
c MXDOMAIN is always in place
e
s 00021/00016/00278
d D 5.10 88/03/24 08:49:38 bostic 10 9
c add Berkeley specific header
e
s 00007/00019/00287
d D 5.9 88/03/24 08:48:14 bostic 9 8
c use the C library/resolver's version of getshort
e
s 00001/00001/00305
d D 5.8 88/03/13 18:21:58 bostic 8 7
c replace sameword with strcasecmp
e
s 00004/00004/00302
d D 5.7 87/12/12 09:31:34 bostic 7 6
c dn_skip -> dn_skipname
e
s 00013/00002/00293
d D 5.6 87/02/03 20:49:45 eric 6 5
c do it right
e
s 00003/00002/00292
d D 5.5 87/02/03 20:44:00 eric 5 4
c pass sending hostname correctly back via the $s macro (broken sometime
c earlier); hack around some name server changes
e
s 00002/00001/00292
d D 5.4 86/07/25 17:11:00 bloom 4 3
c move the include of sendmail.h so MXDOMAIN can come from it
e
s 00101/00000/00192
d D 5.3 86/07/21 10:30:06 bloom 3 2
c hack for Jeeves being broken, replace gethostbyname by a specific 
c routine for canonicalizing hostnames
e
s 00054/00014/00138
d D 5.2 86/07/10 15:41:06 bloom 2 1
c totally implement rfc974 in getmxrr(), just return a list of hosts
e
s 00152/00000/00000
d D 5.1 86/07/01 14:40:44 bloom 1 0
c Name Server MX support from Satz@su-sierra
e
u
U
t
T
I 1
/*
I 16
D 103
 * Copyright (c) 1986 Eric P. Allman
E 103
I 103
 * Copyright (c) 1986, 1995 Eric P. Allman
E 103
E 16
D 10
**  Sendmail
**  Copyright (c) 1986  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1986 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 10
I 10
D 64
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 64
I 64
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 64
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1986  Eric P. Allman
 *  Berkeley, California
E 16
I 16
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 16
 */
E 10

I 17
D 22
#include <sendmail.h>
E 22
I 22
#include "sendmail.h"
E 22

E 17
I 4
D 13
#include "sendmail.h"
E 13
I 13
D 16
#include <sendmail.h>
E 13

E 16
E 4
I 2
D 10
#ifndef MXDOMAIN
E 10
E 2
#ifndef lint
I 2
D 10
static char	SccsId[] = "%W% (Berkeley) %G% (no MXDOMAIN)";
#endif not lint
#else MXDOMAIN
E 10
I 10
D 11
#ifdef MXDOMAIN
static char sccsid[] = "%W% (Berkeley) %G% (with MXDOMAIN)";
#else
static char sccsid[] = "%W% (Berkeley) %G% (without MXDOMAIN)";
#endif
E 11
I 11
D 17
static char sccsid[] = "%W% (Berkeley) %G%";
E 17
I 17
D 84
#ifdef NAMED_BIND
E 84
I 84
#if NAMED_BIND
E 84
static char sccsid[] = "%W% (Berkeley) %G% (with name server)";
#else
static char sccsid[] = "%W% (Berkeley) %G% (without name server)";
#endif
E 17
E 11
#endif /* not lint */
E 10

I 16
D 17
#include <sendmail.h>
E 17
I 17
D 84
#ifdef NAMED_BIND
E 84
I 84
#if NAMED_BIND
E 84

E 17
E 16
D 10
#ifndef lint
E 2
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint

E 10
I 10
D 11
#ifdef MXDOMAIN
E 11
E 10
D 13
# include <sys/param.h>
D 2
# include <netinet/in.h>
E 2
I 2
D 4
# include "sendmail.h"
E 4
E 2
# include <arpa/nameser.h>
# include <resolv.h>
D 2
# include <stdio.h>
E 2
# include <netdb.h>
E 13
I 13
D 40
#include <sys/param.h>
E 40
I 17
#include <errno.h>
E 17
D 86
#include <arpa/nameser.h>
E 86
#include <resolv.h>
D 101
#include <netdb.h>
E 101
E 13

I 27
D 28
#ifndef BSD4_4
#define __dn_skipname	dn_skipname
#endif

E 28
E 27
D 42
typedef union {
	HEADER qb1;
	char qb2[PACKETSZ];
E 42
I 42
typedef union
{
	HEADER	qb1;
D 87
	char	qb2[PACKETSZ];
E 87
I 87
	u_char	qb2[PACKETSZ];
E 87
E 42
} querybuf;

D 5
static char hostbuf[BUFSIZ];
E 5
I 5
D 13
static char	hostbuf[BUFSIZ];
int		h_errno;
I 6
D 9
extern u_short	getshort();
E 9
I 9
extern u_short	_getshort();
E 13
I 13
D 42
static char hostbuf[MAXMXHOSTS*PACKETSZ];
E 42
I 42
D 59
static char	hostbuf[MAXMXHOSTS*PACKETSZ];
E 59
I 59
static char	MXHostBuf[MAXMXHOSTS*PACKETSZ];
E 59
E 42
E 13
E 9
E 6
E 5

I 43
#ifndef MAXDNSRCH
#define MAXDNSRCH	6	/* number of possible domains to search */
#endif

I 44
#ifndef MAX
#define MAX(a, b)	((a) > (b) ? (a) : (b))
#endif

I 68
#ifndef NO_DATA
# define NO_DATA	NO_ADDRESS
#endif

I 76
D 86
#ifndef HEADERSZ
D 85
# define HEADERSZ	sizeof(HEADER)
E 85
I 85
# define HEADERSZ	12	/* sizeof(HEADER) */
E 86
I 86
#ifndef HFIXEDSZ
# define HFIXEDSZ	12	/* sizeof(HEADER) */
E 86
E 85
#endif

E 76
E 68
I 47
D 86
/* don't use sizeof because sizeof(long) is different on 64-bit machines */
#define SHORTSIZE	2	/* size of a short (really, must be 2) */
#define LONGSIZE	4	/* size of a long (really, must be 4) */
I 64

E 86
#define MAXCNAMEDEPTH	10	/* maximum depth of CNAME recursion */
I 88

#if defined(__RES) && (__RES >= 19940415)
# define RES_UNC_T	char *
#else
# define RES_UNC_T	u_char *
#endif
E 88
E 64
/*
**  GETMXRR -- get MX resource records for a domain
**
**	Parameters:
**		host -- the name of the host to MX.
**		mxhosts -- a pointer to a return buffer of MX records.
D 62
**		localhost -- the name of the local host.  All MX records
**			less preferred than this one will be discarded.
E 62
I 62
**		droplocalhost -- If TRUE, all MX records less preferred
**			than the local host (as determined by $=w) will
**			be discarded.
E 62
**		rcode -- a pointer to an EX_ status code.
**
**	Returns:
**		The number of MX records found.
**		-1 if there is an internal failure.
**		If no MX records are found, mxhosts[0] is set to host
**			and 1 is returned.
*/

I 108
int
E 108
E 47
E 44
E 43
D 5
int h_errno;
E 5
I 5
D 6
# define getshort	_getshort	/* XXX hack attack! */
E 5

E 6
D 2
getmxrr(host, mxhosts, maxmx)
E 2
I 2
D 13
getmxrr(host, mxhosts, maxmx, localhost)
E 2
	char *host, **mxhosts;
	int maxmx;
I 2
	char *localhost;
E 13
I 13
D 62
getmxrr(host, mxhosts, localhost, rcode)
E 62
I 62
getmxrr(host, mxhosts, droplocalhost, rcode)
E 62
D 59
	char *host, **mxhosts, *localhost;
E 59
I 59
	char *host;
	char **mxhosts;
D 62
	char *localhost;
E 62
I 62
	bool droplocalhost;
E 62
E 59
	int *rcode;
E 13
E 2
{
D 13

E 13
I 13
D 114
	extern int h_errno;
E 114
	register u_char *eom, *cp;
D 66
	register int i, j, n, nmx;
E 66
I 66
	register int i, j, n;
	int nmx = 0;
E 66
	register char *bp;
E 13
	HEADER *hp;
D 13
	char *eom, *bp, *cp;
	querybuf buf, answer;
	int n, n1, i, j, nmx, ancount, qdcount, buflen;
I 2
	int seenlocal;
E 2
	u_short prefer[BUFSIZ];
D 2
	u_short pref, type, class;
E 2
I 2
	u_short pref, localpref, type, class;
E 13
I 13
	querybuf answer;
D 56
	int ancount, qdcount, buflen, seenlocal;
E 56
I 56
	int ancount, qdcount, buflen;
D 66
	bool seenlocal;
E 66
I 66
	bool seenlocal = FALSE;
E 66
E 56
D 57
	u_short pref, localpref, type, prefer[MAXMXHOSTS];
E 57
I 57
D 97
	u_short pref, localpref, type;
E 97
I 97
	u_short pref, type;
	u_short localpref = 256;
E 97
	char *fallbackMX = FallBackMX;
	static bool firsttime = TRUE;
I 62
D 95
	STAB *st;
E 95
I 69
	bool trycanon = FALSE;
I 113
	int (*resfunc)();
	extern int res_query(), res_search();
E 113
E 69
E 62
	u_short prefer[MAXMXHOSTS];
E 57
I 42
	int weight[MAXMXHOSTS];
I 66
	extern bool getcanonname();
I 91
D 93
	extern bool mx_enabled();
E 93
E 91
E 66
E 42
E 13
E 2

I 79
	if (tTd(8, 2))
		printf("getmxrr(%s, droplocalhost=%d)\n", host, droplocalhost);

E 79
I 57
	if (fallbackMX != NULL)
	{
D 88
		if (firsttime && res_query(FallBackMX, C_IN, T_A,
					   (char *) &answer, sizeof answer) < 0)
E 88
I 88
		if (firsttime &&
		    res_query(FallBackMX, C_IN, T_A,
			      (u_char *) &answer, sizeof answer) < 0)
E 88
		{
			/* this entry is bogus */
			fallbackMX = FallBackMX = NULL;
		}
D 62
		else if (strcasecmp(fallbackMX, localhost) == 0)
E 62
I 62
D 95
		else if (droplocalhost &&
			 (st = stab(fallbackMX, ST_CLASS, ST_FIND)) != NULL &&
			 bitnset('w', st->s_class))
E 95
I 95
		else if (droplocalhost && wordinclass(fallbackMX, 'w'))
E 95
E 62
		{
			/* don't use fallback for this pass */
			fallbackMX = NULL;
		}
		firsttime = FALSE;
	}

I 107
	*rcode = EX_OK;

E 107
I 71
	/* efficiency hack -- numeric or non-MX lookups */
	if (host[0] == '[')
		goto punt;

I 91
	/*
	**  If we don't have MX records in our host switch, don't
	**  try for MX records.  Note that this really isn't "right",
	**  since we might be set up to try NIS first and then DNS;
	**  if the host is found in NIS we really shouldn't be doing
	**  MX lookups.  However, that should be a degenerate case.
	*/

D 93
	if (!mx_enabled())
E 93
I 93
	if (!UseNameServer)
E 93
		goto punt;
I 113
	if (HasWildcardMX && ConfigLevel >= 6)
		resfunc = res_query;
	else
		resfunc = res_search;
E 113

E 91
E 71
E 57
I 18
	errno = 0;
E 18
D 13
	n = res_mkquery(QUERY, host, C_IN, T_MX, (char *)NULL, 0, NULL,
		(char *)&buf, sizeof(buf));
E 13
I 13
D 88
	n = res_search(host, C_IN, T_MX, (char *)&answer, sizeof(answer));
E 88
I 88
D 113
	n = res_search(host, C_IN, T_MX, (u_char *) &answer, sizeof(answer));
E 113
I 113
	n = (*resfunc)(host, C_IN, T_MX, (u_char *) &answer, sizeof(answer));
E 113
E 88
E 13
D 17
	if (n < 0) {
E 17
I 17
	if (n < 0)
	{
E 17
D 20
#ifdef DEBUG
E 20
D 13
		if (tTd(8, 1) || _res.options & RES_DEBUG)
			printf("res_mkquery failed\n");
E 13
I 13
		if (tTd(8, 1))
D 34
			printf("getmxrr: res_search failed (errno=%d, h_errno=%d)\n",
			    errno, h_errno);
E 34
I 34
			printf("getmxrr: res_search(%s) failed (errno=%d, h_errno=%d)\n",
			    (host == NULL) ? "<NULL>" : host, errno, h_errno);
E 34
E 13
D 20
#endif
E 20
D 2
		return(-1);
E 2
I 2
D 13
		h_errno = NO_RECOVERY;
		return(-2);
E 2
	}
	n = res_send((char *)&buf, n, (char *)&answer, sizeof(answer));
	if (n < 0) {
#ifdef DEBUG
		if (tTd(8, 1) || _res.options & RES_DEBUG)
			printf("res_send failed\n");
#endif
		h_errno = TRY_AGAIN;
		return (-1);
	}
	eom = (char *)&answer + n;
	/*
	 * find first satisfactory answer
	 */
	hp = (HEADER *) &answer;
	ancount = ntohs(hp->ancount);
	qdcount = ntohs(hp->qdcount);
	if (hp->rcode != NOERROR || ancount == 0) {
#ifdef DEBUG
		if (tTd(8, 1) || _res.options & RES_DEBUG)
			printf("rcode = %d, ancount=%d\n", hp->rcode, ancount);
#endif
		switch (hp->rcode) {
			case NXDOMAIN:
				/* Check if it's an authoritive answer */
D 2
				if (hp->aa)
E 2
I 2
				if (hp->aa) {
E 2
					h_errno = HOST_NOT_FOUND;
D 2
				else
E 2
I 2
					return(-3);
				} else {
E 2
					h_errno = TRY_AGAIN;
D 2
				break;
E 2
I 2
					return(-1);
				}
E 2
			case SERVFAIL:
				h_errno = TRY_AGAIN;
D 2
				break;
E 2
I 2
				return(-1);
I 3
#ifdef OLDJEEVES
			/*
			 * Jeeves (TOPS-20 server) still does not
			 * support MX records.  For the time being,
			 * we must accept FORMERRs as the same as
			 * NOERROR.
			 */
			case FORMERR:
D 11
#endif OLDJEEVES
E 11
I 11
#endif
E 11
E 3
E 2
			case NOERROR:
D 2
				h_errno = NO_ADDRESS;
				break;
E 2
I 2
				(void) strcpy(hostbuf, host);
				mxhosts[0] = hostbuf;
				return(1);
I 3
#ifndef OLDJEEVES
E 3
E 2
			case FORMERR:
I 3
D 11
#endif OLDJEEVES
E 11
I 11
#endif
E 11
E 3
			case NOTIMP:
			case REFUSED:
				h_errno = NO_RECOVERY;
I 2
				return(-2);
E 13
I 13
D 17
		switch(h_errno) {
D 14
		case NO_ADDRESS:
E 14
I 14
		case NO_DATA:
E 14
		case NO_RECOVERY:
E 17
I 17
		switch (h_errno)
		{
		  case NO_DATA:
I 69
			trycanon = TRUE;
			/* fall through */

E 69
		  case NO_RECOVERY:
			/* no MX data on this host */
E 17
			goto punt;
D 17
		case HOST_NOT_FOUND:
E 17
I 17

		  case HOST_NOT_FOUND:
I 82
D 105
#ifdef BROKEN_RES_SEARCH
E 105
I 105
#if BROKEN_RES_SEARCH
E 105
D 94
			/* Ultrix resolver returns failure w/ h_errno=0 */
		  case 0:
E 94
I 94
		  case 0:	/* Ultrix resolver retns failure w/ h_errno=0 */
E 94
#endif
E 82
D 94
			/* the host just doesn't exist */
E 94
I 94
			/* host doesn't exist in DNS; might be in /etc/hosts */
E 94
E 17
			*rcode = EX_NOHOST;
I 94
			goto punt;
E 94
I 74

D 94
			if (!UseNameServer)
			{
				/* might exist in /etc/hosts */
				goto punt;
			}
E 74
			break;
D 17
		case TRY_AGAIN:
E 17
I 17

E 94
		  case TRY_AGAIN:
			/* couldn't connect to the name server */
D 94
			if (!UseNameServer && errno == ECONNREFUSED)
				goto punt;

E 94
			/* it might come up later; better queue it up */
E 17
			*rcode = EX_TEMPFAIL;
			break;
I 80

		  default:
			syserr("getmxrr: res_search (%s) failed with impossible h_errno (%d)\n",
				host, h_errno);
			*rcode = EX_OSERR;
			break;
E 80
E 13
E 2
		}
D 13
		return (-1);
E 13
I 13
D 17
		return(-1);
E 17
I 17

		/* irreconcilable differences */
		return (-1);
E 17
E 13
	}
D 13
	bp = hostbuf;
E 13
I 13

	/* find first satisfactory answer */
	hp = (HEADER *)&answer;
D 76
	cp = (u_char *)&answer + sizeof(HEADER);
E 76
I 76
D 86
	cp = (u_char *)&answer + HEADERSZ;
E 86
I 86
	cp = (u_char *)&answer + HFIXEDSZ;
E 86
E 76
	eom = (u_char *)&answer + n;
	for (qdcount = ntohs(hp->qdcount); qdcount--; cp += n + QFIXEDSZ)
D 24
		if ((n = dn_skipname(cp, eom)) < 0)
E 24
I 24
D 28
		if ((n = __dn_skipname(cp, eom)) < 0)
E 28
I 28
		if ((n = dn_skipname(cp, eom)) < 0)
E 28
E 24
			goto punt;
E 13
D 66
	nmx = 0;
I 2
D 56
	seenlocal = 0;
E 56
I 56
	seenlocal = FALSE;
E 66
E 56
E 2
D 36
	buflen = sizeof(hostbuf);
E 36
I 36
D 59
	buflen = sizeof(hostbuf) - 1;
E 36
D 13
	cp = (char *)&answer + sizeof(HEADER);
	if (qdcount) {
D 7
		cp += dn_skip(cp) + QFIXEDSZ;
E 7
I 7
		cp += dn_skipname(cp, eom) + QFIXEDSZ;
E 7
		while (--qdcount > 0)
D 7
			cp += dn_skip(cp) + QFIXEDSZ;
E 7
I 7
			cp += dn_skipname(cp, eom) + QFIXEDSZ;
E 7
	}
	while (--ancount >= 0 && cp < eom && nmx < maxmx) {
E 13
I 13
	bp = hostbuf;
E 59
I 59
	buflen = sizeof(MXHostBuf) - 1;
	bp = MXHostBuf;
E 59
	ancount = ntohs(hp->ancount);
D 36
	while (--ancount >= 0 && cp < eom && nmx < MAXMXHOSTS) {
E 36
I 36
D 55
	while (--ancount >= 0 && cp < eom && nmx < MAXMXHOSTS)
E 55
I 55
	while (--ancount >= 0 && cp < eom && nmx < MAXMXHOSTS - 1)
E 55
	{
E 36
E 13
D 24
		if ((n = dn_expand((char *)&answer, eom, cp, bp, buflen)) < 0)
E 24
I 24
		if ((n = dn_expand((u_char *)&answer,
D 88
		    eom, cp, (u_char *)bp, buflen)) < 0)
E 88
I 88
		    eom, cp, (RES_UNC_T) bp, buflen)) < 0)
E 88
E 24
			break;
		cp += n;
D 9
		type = getshort(cp);
E 9
I 9
D 13
		type = _getshort(cp);
E 9
 		cp += sizeof(u_short);
I 2
		/*
E 2
D 9
		class = getshort(cp);
E 9
I 9
		class = _getshort(cp);
E 9
I 2
		*/
E 13
I 13
		GETSHORT(type, cp);
E 13
E 2
D 47
 		cp += sizeof(u_short) + sizeof(u_long);
E 47
I 47
D 86
 		cp += SHORTSIZE + LONGSIZE;
E 86
I 86
 		cp += INT16SZ + INT32SZ;
E 86
E 47
D 9
		n = getshort(cp);
E 9
I 9
D 13
		n = _getshort(cp);
E 9
		cp += sizeof(u_short);
E 13
I 13
		GETSHORT(n, cp);
E 13
D 36
		if (type != T_MX)  {
E 36
I 36
		if (type != T_MX)
		{
E 36
D 20
#ifdef DEBUG
E 20
D 43
			if (tTd(8, 1) || _res.options & RES_DEBUG)
E 43
I 43
			if (tTd(8, 8) || _res.options & RES_DEBUG)
E 43
				printf("unexpected answer type %d, size %d\n",
D 13
					type, n);
E 13
I 13
				    type, n);
E 13
D 20
#endif
E 20
			cp += n;
			continue;
		}
D 9
		pref = getshort(cp);
E 9
I 9
D 13
		pref = _getshort(cp);
E 9
		cp += sizeof(u_short);
E 13
I 13
		GETSHORT(pref, cp);
E 13
D 24
		if ((n = dn_expand((char *)&answer, eom, cp, bp, buflen)) < 0)
E 24
I 24
D 36
		if ((n = dn_expand((u_char *)&answer,
		    eom, cp, (u_char *)bp, buflen)) < 0)
E 36
I 36
		if ((n = dn_expand((u_char *)&answer, eom, cp,
D 88
				   (u_char *)bp, buflen)) < 0)
E 88
I 88
				   (RES_UNC_T) bp, buflen)) < 0)
E 88
E 36
E 24
			break;
I 2
		cp += n;
D 8
		if (sameword(bp, localhost))
E 8
I 8
D 13
		if (!strcasecmp(bp, localhost))
E 8
		{
E 13
I 13
D 36
		if (!strcasecmp(bp, localhost)) {
E 36
I 36
D 56
		if (!strcasecmp(bp, localhost))
E 56
I 56
D 62
		if (strcasecmp(bp, localhost) == 0)
E 62
I 62
D 95
		if (droplocalhost &&
		    (st = stab(bp, ST_CLASS, ST_FIND)) != NULL &&
		    bitnset('w', st->s_class))
E 95
I 95
		if (droplocalhost && wordinclass(bp, 'w'))
E 95
E 62
E 56
		{
I 79
			if (tTd(8, 3))
				printf("found localhost (%s) in MX list, pref=%d\n",
					bp, pref);
E 79
E 36
D 56
			if (seenlocal == 0 || pref < localpref)
E 56
I 56
			if (!seenlocal || pref < localpref)
E 56
				localpref = pref;
E 13
D 56
			seenlocal = 1;
E 56
I 56
			seenlocal = TRUE;
E 56
D 13
			localpref = pref;
E 13
			continue;
		}
I 73
		if (fallbackMX != NULL && strcasecmp(bp, fallbackMX) == 0)
			fallbackMX = NULL;
E 73
I 42
		weight[nmx] = mxrand(bp);
E 42
E 2
		prefer[nmx] = pref;
		mxhosts[nmx++] = bp;
D 13
		n1 = strlen(bp)+1;
		bp += n1;
		buflen -= n1;
E 13
I 13
D 36
		n = strlen(bp) + 1;
E 36
I 36
		n = strlen(bp);
E 36
		bp += n;
D 36
		buflen -= n;
E 36
I 36
		if (bp[-1] != '.')
		{
			*bp++ = '.';
			n++;
		}
		*bp++ = '\0';
		buflen -= n + 1;
E 36
E 13
D 2
		cp += n;
E 2
	}
D 2
	if (nmx == 0)
		return(-1);
E 2
I 2
D 42
	if (nmx == 0) {
E 42
I 42
D 66
	if (nmx == 0)
E 66
I 66

	/* sort the records */
	for (i = 0; i < nmx; i++)
E 66
	{
E 42
D 13
		(void) strcpy(hostbuf, host);
		mxhosts[0] = hostbuf;
E 13
I 13
D 52
punt:		mxhosts[0] = strcpy(hostbuf, host);
E 52
I 52
D 66
punt:
D 59
		mxhosts[0] = strcpy(hostbuf, host);
		bp = &hostbuf[strlen(hostbuf)];
E 59
I 59
		mxhosts[0] = strcpy(MXHostBuf, host);
		bp = &MXHostBuf[strlen(MXHostBuf)];
E 59
		if (bp[-1] != '.')
E 66
I 66
		for (j = i + 1; j < nmx; j++)
E 66
		{
D 66
			*bp++ = '.';
			*bp = '\0';
E 66
I 66
			if (prefer[i] > prefer[j] ||
			    (prefer[i] == prefer[j] && weight[i] > weight[j]))
			{
				register int temp;
				register char *temp1;

				temp = prefer[i];
				prefer[i] = prefer[j];
				prefer[j] = temp;
				temp1 = mxhosts[i];
				mxhosts[i] = mxhosts[j];
				mxhosts[j] = temp1;
				temp = weight[i];
				weight[i] = weight[j];
				weight[j] = temp;
			}
E 66
		}
E 52
E 13
D 42
		return(1);
E 42
I 42
D 55
		return (1);
E 55
I 55
D 66
		nmx = 1;
E 66
I 66
		if (seenlocal && prefer[i] >= localpref)
		{
			/* truncate higher preference part of list */
			nmx = i;
		}
E 66
I 56
D 58
		prefer[0] = 0;
		weight[0] = 0;
E 58
E 56
E 55
E 42
	}
I 13
D 58

E 13
E 2
	/* sort the records */
D 42
	for (i = 0; i < nmx; i++) {
		for (j = i + 1; j < nmx; j++) {
E 42
I 42
	for (i = 0; i < nmx; i++)
E 58
I 58
D 66
	else
E 66
I 66

	if (nmx == 0)
E 66
E 58
	{
D 58
		for (j = i + 1; j < nmx; j++)
E 58
I 58
D 66
		/* sort the records */
		for (i = 0; i < nmx; i++)
E 66
I 66
punt:
		if (seenlocal &&
D 101
		    (!TryNullMXList || gethostbyname(host) == NULL))
E 101
I 101
		    (!TryNullMXList || sm_gethostbyname(host) == NULL))
E 101
E 66
E 58
		{
E 42
D 18
			if (prefer[i] > prefer[j]) {
E 18
I 18
D 58
			if (prefer[i] > prefer[j] ||
D 35
			    (prefer[i] == prefer[j] && rand() % 1 == 0)) {
E 35
I 35
D 42
			    (prefer[i] == prefer[j] && (rand() & 0100) == 0)) {
E 42
I 42
			    (prefer[i] == prefer[j] && weight[i] > weight[j]))
E 58
I 58
D 66
			for (j = i + 1; j < nmx; j++)
E 58
			{
E 42
E 35
E 18
D 13
				int temp;
				char *temp1;
E 13
I 13
D 58
				register int temp;
				register char *temp1;
E 58
I 58
				if (prefer[i] > prefer[j] ||
				    (prefer[i] == prefer[j] && weight[i] > weight[j]))
				{
					register int temp;
					register char *temp1;
E 66
I 66
			/*
			**  If we have deleted all MX entries, this is
			**  an error -- we should NEVER send to a host that
			**  has an MX, and this should have been caught
			**  earlier in the config file.
			**
			**  Some sites prefer to go ahead and try the
			**  A record anyway; that case is handled by
			**  setting TryNullMXList.  I believe this is a
			**  bad idea, but it's up to you....
			*/
E 66
E 58
E 13

D 58
				temp = prefer[i];
				prefer[i] = prefer[j];
				prefer[j] = temp;
				temp1 = mxhosts[i];
				mxhosts[i] = mxhosts[j];
				mxhosts[j] = temp1;
I 42
				temp = weight[i];
				weight[i] = weight[j];
				weight[j] = temp;
E 58
I 58
D 66
					temp = prefer[i];
					prefer[i] = prefer[j];
					prefer[j] = temp;
					temp1 = mxhosts[i];
					mxhosts[i] = mxhosts[j];
					mxhosts[j] = temp1;
					temp = weight[i];
					weight[i] = weight[j];
					weight[j] = temp;
				}
E 58
E 42
			}
D 58
		}
I 2
D 13
		if (seenlocal && (prefer[i] >= localpref))
		{
			nmx = i;
E 13
I 13
D 42
		if (seenlocal && prefer[i] >= localpref) {
E 42
I 42
		if (seenlocal && prefer[i] >= localpref)
		{
E 42
E 13
			/*
D 13
			 * We are the first MX, might as well try delivering
			 * since nobody is supposed to have more info.
E 13
I 13
			 * truncate higher pref part of list; if we're
			 * the best choice left, we should have realized
			 * awhile ago that this was a local delivery.
E 13
			 */
D 13
			if (nmx == 0)
			{
				(void) strcpy(hostbuf, host);
				mxhosts[0] = hostbuf;
				return(1);
E 13
I 13
D 42
			if (i == 0) {
E 42
I 42
			if (i == 0)
E 58
I 58
			if (seenlocal && prefer[i] >= localpref)
E 66
I 66
			*rcode = EX_CONFIG;
I 81
			syserr("MX list for %s points back to %s",
				host, MyHostName);
E 81
			return -1;
		}
D 71
		mxhosts[0] = strcpy(MXHostBuf, host);
E 71
I 71
		strcpy(MXHostBuf, host);
		mxhosts[0] = MXHostBuf;
		if (host[0] == '[')
		{
			register char *p;

			/* this may be an MX suppression-style address */
			p = strchr(MXHostBuf, ']');
			if (p != NULL)
			{
				*p = '\0';
				if (inet_addr(&MXHostBuf[1]) != -1)
					*p = ']';
				else
I 72
				{
					trycanon = TRUE;
E 72
					mxhosts[0]++;
I 72
				}
E 72
			}
		}
I 73
		n = strlen(MXHostBuf);
		bp = &MXHostBuf[n];
		buflen = sizeof MXHostBuf - n - 1;
E 73
E 71
D 69
		if (getcanonname(MXHostBuf, sizeof MXHostBuf - 1, FALSE))
E 69
I 69
D 72
		if (trycanon && getcanonname(MXHostBuf, sizeof MXHostBuf - 1, FALSE))
E 72
I 72
		if (trycanon &&
		    getcanonname(mxhosts[0], sizeof MXHostBuf - 2, FALSE))
E 72
E 69
		{
D 73
			bp = &MXHostBuf[strlen(MXHostBuf)];
E 73
			if (bp[-1] != '.')
E 66
E 58
			{
E 42
D 58
				*rcode = EX_CONFIG;
D 42
				return(-1);
E 42
I 42
				return (-1);
E 58
I 58
D 66
				/*
				 * truncate higher pref part of list; if we're
				 * the best choice left, we should have realized
				 * awhile ago that this was a local delivery.
				 */
				if (i == 0)
				{
					*rcode = EX_CONFIG;
					return (-1);
				}
				nmx = i;
				break;
E 66
I 66
				*bp++ = '.';
				*bp = '\0';
I 73
				buflen--;
E 73
E 66
E 58
E 42
E 13
			}
I 106
			nmx = 1;
E 106
I 13
D 58
			nmx = i;
E 13
			break;
E 58
		}
I 73
		bp++;
E 73
I 66
D 106
		nmx = 1;
E 106
E 66
E 2
	}
I 55

	/* if we have a default lowest preference, include that */
D 57
	if (FallBackMX != NULL)
E 57
I 57
D 67
	if (FallBackMX != NULL && !seenlocal)
E 57
		mxhosts[nmx++] = FallBackMX;
E 67
I 67
D 73
	if (fallbackMX != NULL && !seenlocal)
		mxhosts[nmx++] = fallbackMX;
E 73
I 73
	if (fallbackMX != NULL && !seenlocal && strlen(fallbackMX) < buflen)
	{
		strcpy(bp, fallbackMX);
		mxhosts[nmx++] = bp;
		bp += strlen(bp);
		if (bp[-1] != '.')
		{
			*bp++ = '.';
			*bp = '\0';
		}
	}
E 73
E 67

E 55
D 42
	return(nmx);
E 42
I 42
	return (nmx);
}
/*
**  MXRAND -- create a randomizer for equal MX preferences
**
**	If two MX hosts have equal preferences we want to randomize
**	the selection.  But in order for signatures to be the same,
**	we need to randomize the same way each time.  This function
**	computes a pseudo-random hash function from the host name.
**
**	Parameters:
**		host -- the name of the host.
**
**	Returns:
**		A random but repeatable value based on the host name.
**
**	Side Effects:
**		none.
*/

I 108
int
E 108
mxrand(host)
	register char *host;
{
	int hfunc;
	static unsigned int seed;

	if (seed == 0)
	{
		seed = (int) curtime() & 0xffff;
		if (seed == 0)
			seed++;
	}

	if (tTd(17, 9))
		printf("mxrand(%s)", host);

	hfunc = seed;
	while (*host != '\0')
	{
		int c = *host++;

		if (isascii(c) && isupper(c))
			c = tolower(c);
D 77
		hfunc = ((hfunc << 1) + c) % 2003;
E 77
I 77
		hfunc = ((hfunc << 1) ^ c) % 2003;
E 77
	}

	hfunc &= 0xff;

	if (tTd(17, 9))
		printf(" = %d\n", hfunc);
	return hfunc;
I 91
D 93
}
/*
**  MX_ENABLED -- check to see if MX records apply
**
**	This is done by seeing if "dns" is listed in the hosts
**	service switch.
*/

bool
mx_enabled()
{
	static bool firsttime = TRUE;
	static bool hasmx;
	char *maptype[MAXMAPSTACK];

	if (firsttime)
	{
		int nmaps;
I 92
		short mapreturn[3];
E 92

D 92
		nmaps = switch_map_find("hosts", maptype);
E 92
I 92
		nmaps = switch_map_find("hosts", maptype, mapreturn);
E 92
		hasmx = FALSE;
		if (nmaps > 0 && nmaps <= MAXMAPSTACK)
		{
			register int mapno;

			for (mapno = 0; mapno < nmaps && !hasmx; mapno++)
			{
				if (strcmp(maptype[mapno], "dns") == 0)
					hasmx = TRUE;
			}
		}
		firsttime = FALSE;
	}
	return hasmx;
E 93
E 91
E 42
I 3
}
D 37

I 31
/*
 * Use query type of ANY if possible (NoWildcardMX), which will
 * find types CNAME, A, and MX, and will cause all existing records
 * to be cached by our local server.  If there is (might be) a
 * wildcard MX record in the local domain or its parents that are
 * searched, we can't use ANY; it would cause fully-qualified names
 * to match as names in a local domain.
 */
E 37
I 37
/*
I 112
**  BESTMX -- find the best MX for a name
**
**	This is really a hack, but I don't see any obvious way
**	to generalize it at the moment.
*/

char *
bestmx_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
	int nmx;
	auto int rcode;
	int saveopts = _res.options;
	char *mxhosts[MAXMXHOSTS + 1];

	_res.options &= ~(RES_DNSRCH|RES_DEFNAMES);
	nmx = getmxrr(name, mxhosts, FALSE, &rcode);
	_res.options = saveopts;
	if (nmx <= 0)
		return NULL;
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, mxhosts[0], strlen(mxhosts[0]), av);
}
/*
E 112
D 104
**  GETCANONNAME -- get the canonical name for named host
E 104
I 104
**  DNS_GETCANONNAME -- get the canonical name for named host using DNS
E 104
**
I 43
**	This algorithm tries to be smart about wildcard MX records.
**	This is hard to do because DNS doesn't tell is if we matched
**	against a wildcard or a specific MX.
**	
**	We always prefer A & CNAME records, since these are presumed
**	to be specific.
**
**	If we match an MX in one pass and lose it in the next, we use
**	the old one.  For example, consider an MX matching *.FOO.BAR.COM.
**	A hostname bletch.foo.bar.com will match against this MX, but
**	will stop matching when we try bletch.bar.com -- so we know
**	that bletch.foo.bar.com must have been right.  This fails if
**	there was also an MX record matching *.BAR.COM, but there are
**	some things that just can't be fixed.
**
E 43
**	Parameters:
**		host -- a buffer containing the name of the host.
**			This is a value-result parameter.
**		hbsize -- the size of the host buffer.
I 66
**		trymx -- if set, try MX records as well as A and CNAME.
I 104
**		statp -- pointer to place to store status.
E 104
E 66
**
**	Returns:
**		TRUE -- if the host matched.
**		FALSE -- otherwise.
D 43
**
**	Notes:
**		Use query type of ANY if possible (NoWildcardMX), which
**		will find types CNAME, A, and MX, and will cause all
**		existing records to be cached by our local server.  If
**		there is (might be) a wildcard MX record in the local
**		domain or its parents that are searched, we can't use
**		ANY; it would cause fully-qualified names to match as
**		names in a local domain.
E 43
*/
E 37

E 31
I 30
bool
E 30
D 13

E 13
D 66
getcanonname(host, hbsize)
E 66
I 66
D 104
getcanonname(host, hbsize, trymx)
E 104
I 104
dns_getcanonname(host, hbsize, trymx, statp)
E 104
E 66
	char *host;
	int hbsize;
I 66
	bool trymx;
I 104
	int *statp;
E 104
E 66
{
I 21
D 114
	extern int h_errno;
E 114
E 21
D 13

E 13
I 13
D 31
	register u_char *eom, *cp;
E 31
I 31
	register u_char *eom, *ap;
	register char *cp;
E 31
	register int n; 
E 13
	HEADER *hp;
D 13
	char *eom, *cp;
	querybuf buf, answer;
	int n, ancount, qdcount;
E 13
I 13
	querybuf answer;
E 13
D 31
	u_short type;
E 31
D 13
	char nbuf[BUFSIZ];
	int first;
E 13
I 13
D 43
	int first, ancount, qdcount, loopcnt;
E 43
I 43
D 63
	int first, ancount, qdcount;
E 63
I 63
	int ancount, qdcount;
E 63
E 43
I 30
D 31
	bool rval = FALSE;
E 31
I 31
	int ret;
D 43
	int qtype = NoWildcardMX ? T_ANY : T_CNAME;
E 43
	char **domain;
D 43
	bool rval;
E 43
	int type;
I 43
	char **dp;
	char *mxmatch;
	bool amatch;
I 49
D 97
	bool gotmx;
E 97
I 97
	bool gotmx = FALSE;
E 97
E 49
I 48
	int qtype;
I 64
	int loopcnt;
I 75
	char *xp;
E 75
E 64
E 48
E 43
E 31
E 30
D 44
	char nbuf[PACKETSZ];
E 44
I 44
	char nbuf[MAX(PACKETSZ, MAXDNAME*2+2)];
E 44
I 43
D 45
	char *searchlist[MAXDNSRCH+1];
E 45
I 45
	char *searchlist[MAXDNSRCH+2];
I 75
	extern char *gethostalias();
E 75
E 45
E 43
I 31
D 32
	extern char *__hostalias();
E 32
E 31
E 13

I 31
	if (tTd(8, 2))
D 109
		printf("getcanonname(%s)\n", host);
E 109
I 109
		printf("dns_getcanonname(%s, trymx=%d)\n", host, trymx);
E 109

	if ((_res.options & RES_INIT) == 0 && res_init() == -1)
D 104
		return (FALSE);
E 104
I 104
	{
		*statp = EX_UNAVAILABLE;
		return FALSE;
	}
E 104

E 31
D 13
	n = res_mkquery(QUERY, host, C_IN, T_ANY, (char *)NULL, 0, NULL,
		(char *)&buf, sizeof(buf));
E 13
I 13
D 43
	loopcnt = 0;
I 31
	rval = FALSE;
E 31
loop:
E 43
I 31
D 61
	for (cp = host, n = 0; *cp; cp++)
		if (*cp == '.')
			n++;
D 43
	if (n > 0 && *--cp == '.')
	{
		cp = host;
		n = -1;
	}
E 43
D 32
	else if (n == 0 && (cp = __hostalias(host)))
		n = -1;
E 32

E 61
E 31
I 18
	/*
D 29
	 * Use query type of ANY if possible (NO_WILDCARD_MX), which will
E 29
I 29
D 31
	 * Use query type of ANY if possible (NoWildcardMX), which will
E 29
	 * find types CNAME, A, and MX, and will cause all existing records
	 * to be cached by our local server.  If there is (might be) a
	 * wildcard MX record in the local domain or its parents that are
	 * searched, we can't use ANY; it would cause fully-qualified names
	 * to match as names in a local domain.
E 31
I 31
D 38
	 * We do at least one level of search if
	 *	- there is no dot and RES_DEFNAME is set, or
	 *	- there is at least one dot, there is no trailing dot,
	 *	  and RES_DNSRCH is set.
E 31
	 */
E 38
I 38
D 43
	**  If there is at least one dot, start by searching the
	**  unmodified name.  This lets us get "vse.CS" in Czechoslovakia
	**  instead of CS.Berkeley.EDU.
E 43
I 43
	**  Initialize domain search list.  If there is at least one
	**  dot in the name, search the unmodified name first so we
	**  find "vse.CS" in Czechoslovakia instead of in the local
	**  domain (e.g., vse.CS.Berkeley.EDU).
	**
	**  Older versions of the resolver could create this
	**  list by tearing apart the host name.
E 43
	*/

I 64
	loopcnt = 0;
E 64
I 61
cnameloop:
D 111
	for (cp = host, n = 0; *cp; cp++)
E 111
I 111
	for (cp = host, n = 0; *cp != '\0'; cp++)
E 111
		if (*cp == '.')
			n++;

I 75
	if (n == 0 && (xp = gethostalias(host)) != NULL)
	{
		if (loopcnt++ > MAXCNAMEDEPTH)
		{
			syserr("loop in ${HOSTALIASES} file");
		}
		else
		{
			strncpy(host, xp, hbsize);
			host[hbsize - 1] = '\0';
			goto cnameloop;
		}
	}

E 75
E 61
E 38
D 25
# ifdef NO_WILDCARD_MX
	n = res_search(host, C_IN, T_ANY, (char *)&answer, sizeof(answer));
# else
E 18
D 15
	n = res_search(host, C_IN, T_ANY, (char *)&answer, sizeof(answer));
E 15
I 15
	n = res_search(host, C_IN, T_CNAME, (char *)&answer, sizeof(answer));
I 18
# endif
E 25
I 25
D 29
	n = res_search(host, C_IN, WildcardMX ? T_CNAME : T_ANY,
E 29
I 29
D 31
	n = res_search(host, C_IN, NoWildcardMX ? T_ANY : T_CNAME,
E 29
			(char *)&answer, sizeof(answer));
E 25
E 18
E 15
E 13
	if (n < 0) {
D 20
#ifdef DEBUG
E 20
D 13
		if (tTd(8, 1) || _res.options & RES_DEBUG)
			printf("res_mkquery failed\n");
E 13
I 13
		if (tTd(8, 1))
			printf("getcanonname:  res_search failed (errno=%d, h_errno=%d)\n",
			    errno, h_errno);
E 13
D 20
#endif
E 20
D 13
		h_errno = NO_RECOVERY;
E 13
D 30
		return;
E 30
I 30
		return (rval);
E 31
I 31
D 43
	ret = -1;
D 38
	if ((n == 0 && _res.options & RES_DEFNAMES) ||
	   (n > 0 && *--cp != '.' && _res.options & RES_DNSRCH))
E 38
I 38
	if (n >= 1)
E 43
I 43
	dp = searchlist;
	if (n > 0)
		*dp++ = "";
D 49
	if (n == 0 || n > 0 && *--cp != '.')
E 49
I 49
	if (n >= 0 && *--cp != '.' && bitset(RES_DNSRCH, _res.options))
E 49
E 43
E 38
	{
I 38
D 43
		/*
		**  Try the unmodified name.
		*/

		if (tTd(8, 5))
			printf("getcanonname: trying %s\n", host);
		ret = res_query(host, C_IN, qtype, &answer, sizeof(answer));
		if (ret > 0)
		{
			cp = host;
			if (tTd(8, 8))
				printf("\tYES\n");
		}
		else
		{
			if (tTd(8, 8))
				printf("\tNO: h_errno=%d\n", h_errno);
			if (errno == ECONNREFUSED)
			{
				/* no server -- try again later */
				h_errno = TRY_AGAIN;
				return FALSE;
			}
		}
E 43
I 43
		for (domain = _res.dnsrch; *domain != NULL; )
			*dp++ = *domain++;
E 43
	}
I 49
	else if (n == 0 && bitset(RES_DEFNAMES, _res.options))
	{
		*dp++ = _res.defdname;
	}
I 78
	else if (*cp == '.')
	{
		*cp = '\0';
	}
E 78
E 49
I 43
	*dp = NULL;
E 43

I 111
	/* if we have a wildcard MX and no dots, try MX anyhow */
	if (n == 0)
		trymx = TRUE;

E 111
	/*
D 39
	**  We do at least one level of search if
	**	- there is no dot and RES_DEFNAME is set, or
	**	- there is at least one dot, there is no trailing dot,
	**	  and RES_DNSRCH is set.
E 39
I 39
D 43
	**  We assume that RES_DEFNAMES and RES_DNSRCH are set -- if we
	**  don't want this behaviour, don't use $[ ... $] at all!
E 43
I 43
	**  Now run through the search list for the name in question.
E 43
E 39
	*/

I 54
D 61
cnameloop:
E 54
D 39
	if (ret < 0 &&
		((n == 0 && _res.options & RES_DEFNAMES) ||
		 (n > 0 && *--cp != '.' && _res.options & RES_DNSRCH)))
E 39
I 39
D 43
	if (ret < 0 && (n == 0 || (n > 0 && *--cp != '.')))
E 43
I 43
	dp = searchlist;
E 61
	mxmatch = NULL;
I 48
	qtype = T_ANY;
E 48

D 48
	for (dp = searchlist; *dp != NULL; dp++)
E 48
I 48
	for (dp = searchlist; *dp != NULL; )
E 48
E 43
E 39
	{
I 49
		if (qtype == T_ANY)
			gotmx = FALSE;
E 49
E 38
D 43
		for (domain = _res.dnsrch; *domain; domain++)
E 43
I 43
D 44
		(void) sprintf(nbuf, "%.*s%s%.*s", MAXDNAME, host,
				**dp == '\0' ? "" : ".",
				MAXDNAME, *dp);
E 44
		if (tTd(8, 5))
D 44
			printf("getcanonname: trying %s\n", nbuf);
		ret = res_query(nbuf, C_IN, T_ANY, &answer, sizeof(answer));
E 44
I 44
D 51
			printf("getcanonname: trying %s.%s\n", host, *dp);
E 51
I 51
D 109
			printf("getcanonname: trying %s.%s (%s)\n", host, *dp,
E 109
I 109
			printf("dns_getcanonname: trying %s.%s (%s)\n",
				host, *dp,
E 109
				qtype == T_ANY ? "ANY" : qtype == T_A ? "A" :
				qtype == T_MX ? "MX" : "???");
E 51
D 48
		ret = res_querydomain(host, *dp, C_IN, T_ANY,
E 48
I 48
		ret = res_querydomain(host, *dp, C_IN, qtype,
E 48
D 87
				      &answer, sizeof(answer));
E 87
I 87
D 89
				      &answer.qb2, sizeof(answer.qb2));
E 89
I 89
				      answer.qb2, sizeof(answer.qb2));
E 89
E 87
E 44
		if (ret <= 0)
E 43
		{
D 43
			(void) sprintf(nbuf, "%.*s.%.*s",
				MAXDNAME, host, MAXDNAME, *domain);
			if (tTd(8, 5))
				printf("getcanonname: trying %s\n", nbuf);
			ret = res_query(nbuf, C_IN, qtype, &answer, sizeof(answer));
			if (ret > 0)
			{
				if (tTd(8, 8))
					printf("\tYES\n");
				cp = nbuf;
				break;
			}
			else if (tTd(8, 8))
E 43
I 43
D 53
			if (tTd(8, 8))
E 53
I 53
			if (tTd(8, 7))
E 53
E 43
D 46
				printf("\tNO: h_errno=%d\n", h_errno);
E 46
I 46
				printf("\tNO: errno=%d, h_errno=%d\n",
					errno, h_errno);
E 46

D 43
			/*
			 * If no server present, give up.
			 * If name isn't found in this domain,
			 * keep trying higher domains in the search list
			 * (if that's enabled).
			 * On a NO_DATA error, keep trying, otherwise
			 * a wildcard entry of another type could keep us
			 * from finding this entry higher in the domain.
			 * If we get some other error (negative answer or
			 * server failure), then stop searching up,
D 38
			 * but try the input name below in case it's fully-qualified.
E 38
I 38
			 * but try the input name below in case it's
			 * fully-qualified.
E 38
			 */
D 38
			if (errno == ECONNREFUSED) {
E 38
I 38

E 43
D 46
			if (errno == ECONNREFUSED)
E 46
I 46
			if (errno == ECONNREFUSED || h_errno == TRY_AGAIN)
E 46
			{
I 43
				/* the name server seems to be down */
E 43
E 38
				h_errno = TRY_AGAIN;
I 104
				*statp = EX_TEMPFAIL;
E 104
D 33
				return rval;
E 33
I 33
				return FALSE;
E 33
			}
D 43
			if (h_errno == NO_DATA)
E 43
I 43

I 48
D 50
			if (h_errno == HOST_NOT_FOUND)
E 50
I 50
			if (h_errno != HOST_NOT_FOUND)
E 50
			{
D 50
				/* definitely no data for this address */
				dp++;
				qtype = T_ANY; 		/* just in case */
				continue;
E 50
I 50
				/* might have another type of interest */
				if (qtype == T_ANY)
				{
					qtype = T_A;
					continue;
				}
D 66
				else if (qtype == T_A && !gotmx)
E 66
I 66
				else if (qtype == T_A && !gotmx && trymx)
E 66
				{
					qtype = T_MX;
					continue;
				}
E 50
			}

E 48
D 111
			if (mxmatch != NULL)
E 43
			{
D 43
				ret = 0;
				cp = nbuf;
E 43
I 43
				/* we matched before -- use that one */
E 43
				break;
			}
I 50

			/* otherwise, try the next name */
E 111
I 111
			/* try the next name */
E 111
			dp++;
			qtype = T_ANY;
E 50
D 43
			if ((h_errno != HOST_NOT_FOUND) ||
			    (_res.options & RES_DNSRCH) == 0)
D 33
				return rval;
E 33
I 33
				return FALSE;
E 43
I 43
			continue;
E 43
E 33
		}
E 31
E 30
D 43
	}
I 31
D 38
	if (ret < 0)
E 38
I 38
	if (ret < 0 && n <= 0)
E 38
	{
E 43
I 43
D 48
		if (tTd(8, 8))
E 48
I 48
D 53
		else if (tTd(8, 8))
E 53
I 53
		else if (tTd(8, 7))
E 53
E 48
			printf("\tYES\n");

E 43
I 33
		/*
D 43
		**  Try the unmodified name.
E 43
I 43
		**  This might be a bogus match.  Search for A or
		**  CNAME records.  If we don't have a matching
		**  wild card MX record, we will accept MX as well.
E 43
		*/

E 33
D 43
		cp = host;
		if (tTd(8, 5))
			printf("getcanonname: trying %s\n", cp);
		ret = res_query(cp, C_IN, qtype, &answer, sizeof(answer));
		if (ret > 0)
E 43
I 43
		hp = (HEADER *) &answer;
D 76
		ap = (u_char *) &answer + sizeof(HEADER);
E 76
I 76
D 86
		ap = (u_char *) &answer + HEADERSZ;
E 86
I 86
		ap = (u_char *) &answer + HFIXEDSZ;
E 86
E 76
		eom = (u_char *) &answer + ret;

		/* skip question part of response -- we know what we asked */
		for (qdcount = ntohs(hp->qdcount); qdcount--; ap += ret + QFIXEDSZ)
E 43
		{
D 43
			if (tTd(8, 8))
				printf("\tYES\n");
E 43
I 43
			if ((ret = dn_skipname(ap, eom)) < 0)
			{
				if (tTd(8, 20))
					printf("qdcount failure (%d)\n",
						ntohs(hp->qdcount));
I 104
				*statp = EX_SOFTWARE;
E 104
				return FALSE;		/* ???XXX??? */
			}
E 43
		}
D 43
		else
E 43
I 43

		amatch = FALSE;
		for (ancount = ntohs(hp->ancount); --ancount >= 0 && ap < eom; ap += n)
E 43
		{
D 43
			if (tTd(8, 8))
				printf("\tNO: h_errno=%d\n", h_errno);
D 33
			return rval;
E 33
I 33
D 38
			if (h_errno != NO_DATA)
				return FALSE;
E 38
E 33
		}
	}
E 43
I 43
			n = dn_expand((u_char *) &answer, eom, ap,
D 88
				      (u_char *) nbuf, sizeof nbuf);
E 88
I 88
				      (RES_UNC_T) nbuf, sizeof nbuf);
E 88
			if (n < 0)
				break;
			ap += n;
			GETSHORT(type, ap);
D 47
			ap += sizeof(u_short) + sizeof(u_long);
E 47
I 47
D 86
			ap += SHORTSIZE + LONGSIZE;
E 86
I 86
			ap += INT16SZ + INT32SZ;
E 86
E 47
			GETSHORT(n, ap);
			switch (type)
			{
			  case T_MX:
I 49
				gotmx = TRUE;
E 49
D 69
				if (**dp != '\0')
E 69
I 69
D 70
				if (trymx && **dp != '\0')
E 70
I 70
D 111
				if (**dp != '\0')
E 111
I 111
				if (**dp != '\0' || !HasWildcardMX)
E 111
E 70
E 69
				{
					/* got a match -- save that info */
D 70
					if (mxmatch == NULL)
E 70
I 70
					if (trymx && mxmatch == NULL)
E 70
						mxmatch = *dp;
					continue;
				}
E 43
I 38

D 43
	if (ret <= 0 && h_errno != NO_DATA)
		return FALSE;
E 43
I 43
				/* exact MX matches are as good as an A match */
				/* fall through */
E 43
E 38
E 31
D 13
	n = res_send((char *)&buf, n, (char *)&answer, sizeof(answer));
	if (n < 0) {
#ifdef DEBUG
		if (tTd(8, 1) || _res.options & RES_DEBUG)
			printf("res_send failed\n");
#endif
		h_errno = TRY_AGAIN;
		return;
	}
	eom = (char *)&answer + n;
	/*
	 * find first satisfactory answer
	 */
	hp = (HEADER *) &answer;
E 13
I 13

D 43
	/* find first satisfactory answer */
	hp = (HEADER *)&answer;
E 13
	ancount = ntohs(hp->ancount);
I 31
	if (tTd(8, 3))
		printf("rcode = %d, ancount=%d, qdcount=%d\n",
			hp->rcode, ancount, ntohs(hp->qdcount));
E 43
I 43
			  case T_A:
				/* good show */
				amatch = TRUE;
E 43
E 31
D 13
	qdcount = ntohs(hp->qdcount);
	/*
	 * We don't care about errors here, only if we got an answer
	 */
E 13
I 13

D 43
	/* we don't care about errors here, only if we got an answer */
E 13
D 31
	if (ancount == 0) {
D 20
#ifdef DEBUG
E 20
D 13
		if (tTd(8, 1) || _res.options & RES_DEBUG)
E 13
I 13
		if (tTd(8, 1))
E 13
			printf("rcode = %d, ancount=%d\n", hp->rcode, ancount);
D 20
#endif
E 20
D 30
		return;
E 30
I 30
		return (rval);
E 31
I 31
	if (ancount == 0)
	{
		strncpy(host, cp, hbsize);
		host[hbsize - 1] = '\0';
		return (TRUE);
E 31
E 30
	}
D 13
	cp = (char *)&answer + sizeof(HEADER);
	if (qdcount) {
D 7
		cp += dn_skip(cp) + QFIXEDSZ;
E 7
I 7
		cp += dn_skipname(cp, eom) + QFIXEDSZ;
E 7
		while (--qdcount > 0)
D 7
			cp += dn_skip(cp) + QFIXEDSZ;
E 7
I 7
			cp += dn_skipname(cp, eom) + QFIXEDSZ;
E 7
	}
	first = 1;
	while (--ancount >= 0 && cp < eom) {
E 13
I 13
D 31
	cp = (u_char *)&answer + sizeof(HEADER);
	eom = (u_char *)&answer + n;
	for (qdcount = ntohs(hp->qdcount); qdcount--; cp += n + QFIXEDSZ)
D 24
		if ((n = dn_skipname(cp, eom)) < 0)
E 24
I 24
D 28
		if ((n = __dn_skipname(cp, eom)) < 0)
E 28
I 28
		if ((n = dn_skipname(cp, eom)) < 0)
E 28
E 24
D 30
			return;
E 30
I 30
			return (rval);
E 31
I 31
	ap = (u_char *)&answer + sizeof(HEADER);
	eom = (u_char *)&answer + ret;
	for (qdcount = ntohs(hp->qdcount); qdcount--; ap += ret + QFIXEDSZ)
	{
		if ((ret = dn_skipname(ap, eom)) < 0)
		{
			if (tTd(8, 20))
				printf("qdcount failure (%d)\n",
					ntohs(hp->qdcount));
D 33
			return rval;		/* ???XXX??? */
E 33
I 33
			return FALSE;		/* ???XXX??? */
E 43
I 43
				/* continue in case a CNAME also exists */
				continue;

			  case T_CNAME:
I 110
				if (DontExpandCnames)
				{
					/* got CNAME -- guaranteed canonical */
					amatch = TRUE;
					break;
				}

E 110
I 64
				if (loopcnt++ > MAXCNAMEDEPTH)
				{
D 83
					syserr("DNS failure: CNAME loop for %s",
E 83
I 83
					/*XXX should notify postmaster XXX*/
					message("DNS failure: CNAME loop for %s",
E 83
						host);
D 83
					continue;
E 83
I 83
					if (CurEnv->e_message == NULL)
					{
						char ebuf[MAXLINE];

						sprintf(ebuf, "Deferred: DNS failure: CNAME loop for %s",
							host);
						CurEnv->e_message = newstr(ebuf);
					}
					h_errno = NO_RECOVERY;
I 104
					*statp = EX_CONFIG;
E 104
					return FALSE;
E 83
				}

E 64
				/* value points at name */
				if ((ret = dn_expand((u_char *)&answer,
D 88
				    eom, ap, (u_char *)nbuf, sizeof(nbuf))) < 0)
E 88
I 88
				    eom, ap, (RES_UNC_T) nbuf, sizeof(nbuf))) < 0)
E 88
					break;
				(void)strncpy(host, nbuf, hbsize); /* XXX */
				host[hbsize - 1] = '\0';
D 54
				return TRUE;
E 54
I 54

				/*
				**  RFC 1034 section 3.6 specifies that CNAME
				**  should point at the canonical name -- but
				**  urges software to try again anyway.
				*/

				goto cnameloop;
E 54

			  default:
				/* not a record of interest */
				continue;
			}
E 43
E 33
		}
D 43
	}
E 43
E 31
E 30

D 43
	/*
D 31
	 * just in case someone puts a CNAME record after another record,
	 * check all records for CNAME; otherwise, just take the first
	 * name found.
	 */
	for (first = 1; --ancount >= 0 && cp < eom; cp += n) {
E 13
D 24
		if ((n = dn_expand((char *)&answer, eom, cp, nbuf,
		    sizeof(nbuf))) < 0)
E 24
I 24
		if ((n = dn_expand((u_char *)&answer,
		    eom, cp, (u_char *)nbuf, sizeof(nbuf))) < 0)
E 31
I 31
	* just in case someone puts a CNAME record after another record,
	* check all records for CNAME; otherwise, just take the first
	* name found.
	*/
	for (first = 1; --ancount >= 0 && ap < eom; ap += ret)
	{
		if ((ret = dn_expand((u_char *)&answer,
		    eom, ap, (u_char *)nbuf, sizeof(nbuf))) < 0)
E 43
I 43
		if (amatch)
		{
			/* got an A record and no CNAME */
			mxmatch = *dp;
E 43
E 31
E 24
			break;
I 48
		}

		/*
		**  If this was a T_ANY query, we may have the info but
		**  need an explicit query.  Try T_A, then T_MX.
		*/

		if (qtype == T_ANY)
			qtype = T_A;
D 49
		else if (qtype = T_A)
E 49
I 49
D 66
		else if (qtype == T_A && !gotmx)
E 66
I 66
		else if (qtype == T_A && !gotmx && trymx)
E 66
E 49
			qtype = T_MX;
		else
		{
			/* really nothing in this domain; try the next */
			qtype = T_ANY;
			dp++;
E 48
I 30
D 31
		rval = TRUE;
E 31
E 30
D 13
		if (first) {
E 13
I 13
D 43
		if (first) {			/* XXX */
E 13
			(void)strncpy(host, nbuf, hbsize);
			host[hbsize - 1] = '\0';
			first = 0;
I 31
			rval = TRUE;
E 43
E 31
		}
D 31
		cp += n;
D 9
		type = getshort(cp);
E 9
I 9
D 13
		type = _getshort(cp);
E 9
 		cp += sizeof(u_short);
E 13
I 13
		GETSHORT(type, cp);
E 13
 		cp += sizeof(u_short) + sizeof(u_long);
D 9
		n = getshort(cp);
E 9
I 9
D 13
		n = _getshort(cp);
E 9
		cp += sizeof(u_short);
E 13
I 13
		GETSHORT(n, cp);
E 31
I 31
D 43
		ap += ret;
		GETSHORT(type, ap);
		ap += sizeof(u_short) + sizeof(u_long);
		GETSHORT(ret, ap);
E 31
E 13
		if (type == T_CNAME)  {
			/*
D 13
			 * Assume that only one cname will be found.  More
			 * than one is undefined.
E 13
I 13
			 * assume that only one cname will be found.  More
			 * than one is undefined.  Copy so that if dn_expand
			 * fails, `host' is still okay.
E 13
			 */
D 24
			if ((n = dn_expand((char *)&answer, eom, cp, nbuf,
			    sizeof(nbuf))) < 0)
E 24
I 24
D 31
			if ((n = dn_expand((u_char *)&answer,
			    eom, cp, (u_char *)nbuf, sizeof(nbuf))) < 0)
E 31
I 31
			if ((ret = dn_expand((u_char *)&answer,
			    eom, ap, (u_char *)nbuf, sizeof(nbuf))) < 0)
E 31
E 24
				break;
D 13
			(void)strncpy(host, nbuf, hbsize);
E 13
I 13
			(void)strncpy(host, nbuf, hbsize); /* XXX */
E 13
			host[hbsize - 1] = '\0';
D 13
			getcanonname(host, hbsize);
			break;
E 13
I 13
			if (++loopcnt > 8)	/* never be more than 1 */
D 31
				return;
E 31
I 31
				return FALSE;
			rval = TRUE;
E 31
			goto loop;
E 13
		}
E 43
D 13
		cp += n;
E 13
	}
I 30
D 31
	return (rval);
E 31
I 31
D 43
	return rval;		/* ???XXX??? */
E 43
I 43

	if (mxmatch == NULL)
I 104
	{
		*statp = EX_NOHOST;
E 104
		return FALSE;
I 104
	}
E 104

	/* create matching name and return */
	(void) sprintf(nbuf, "%.*s%s%.*s", MAXDNAME, host,
			*mxmatch == '\0' ? "" : ".",
			MAXDNAME, mxmatch);
	strncpy(host, nbuf, hbsize);
	host[hbsize - 1] = '\0';
I 104
	*statp = EX_OK;
E 104
	return TRUE;
E 43
E 31
E 30
D 13
	return;
E 13
E 3
}
I 75


char *
gethostalias(host)
	char *host;
{
	char *fname;
	FILE *fp;
D 97
	register char *p;
E 97
I 97
	register char *p = NULL;
E 97
	char buf[MAXLINE];
	static char hbuf[MAXDNAME];

	fname = getenv("HOSTALIASES");
D 98
	if (fname == NULL || (fp = fopen(fname, "r")) == NULL)
E 98
I 98
	if (fname == NULL ||
D 100
	    (fp = safefopen(fname, O_RDONLY, 0, SFF_ANYFILE)) == NULL)
E 100
I 100
	    (fp = safefopen(fname, O_RDONLY, 0, SFF_REGONLY)) == NULL)
E 100
E 98
		return NULL;
I 99
	setbuf(fp, NULL);
E 99
	while (fgets(buf, sizeof buf, fp) != NULL)
	{
		for (p = buf; p != '\0' && !(isascii(*p) && isspace(*p)); p++)
			continue;
		if (*p == 0)
		{
			/* syntax error */
			continue;
		}
		*p++ = '\0';
		if (strcasecmp(buf, host) == 0)
			break;
	}

	if (feof(fp))
	{
		/* no match */
		fclose(fp);
		return NULL;
	}

	/* got a match; extract the equivalent name */
	while (*p != '\0' && isascii(*p) && isspace(*p))
		p++;
	host = p;
	while (*p != '\0' && !(isascii(*p) && isspace(*p)))
		p++;
	*p = '\0';
	strncpy(hbuf, host, sizeof hbuf - 1);
	hbuf[sizeof hbuf - 1] = '\0';
	return hbuf;
}

E 75
I 60
/*
**  MAILB_LOOKUP -- do DNS mailbox lookup
*/

#ifdef DNS_MAILB

mailb_lookup(addr)
	char *addr;
{
	/*
	**  Convert addr to DNS form (user.host).
	*/

	/* figure out how much space it needs */
	atp = strchr(addr, '@');
	if (atp == NULL)
		atp = &addr(strlen(addr));
	i = strlen(addr);
	for (p = addr; (p = strchr(p, '.')) != NULL; p++)
	{
		if (p > atp)
			break;
		i++;
	}
	if (i < sizeof abuf)
		bufp = abuf;
	else
		bufp = xalloc(i + 1);

	lhsmode = TRUE;
	for (p = addr, q = bufp; (c = *p++) != '\0'; )
	{
		if (c == '.' && lhsmode)
			*q++ = '\\';
		if (c == '@')
			lhsmode = FALSE;
		*q++ = c;
	}
	*q = '\0';

	/*
	**  Now do a MAILB lookup.
	*/

retry:
	if (res_query(bufp, C_IN, T_MAILB, (char *) &answer, sizeof answer < 0)
	{
		/* no match -- just continue as usual */
		return FALSE;
	}

	/* find first satisfactory answer */
	hp = (HEADER *)&answer;
	ap = (u_char *)&answer + sizeof(HEADER);
	eom = (u_char *)&answer + n;
	for (qdcount = ntohs(hp->qdcount); qdcount--; ap += n + QFIXEDSZ)
		if ((n = dn_skipname(ap, eom)) < 0)
			return FALSE;
	for (ancount = ntohs(hp->ancount); --ancount >= 0 && ap < eom; ap += n)
	{
		n = dn_expand((u_char *)&answer, eom, ap, (u_char *)bp, buflen);
		if (n < 0)
			break;
		ap += n;
		GETSHORT(type, ap);
 		ap += SHORTSIZE + LONGSIZE;
		GETSHORT(n, ap);
		switch (type)
		{
		  case T_MR:
			/* rename: try again */
			i = dn_expand((u_char *) &answer, eom, ap,
					(u_char) abuf, sizeof abuf);
			if (i < 0)
				break;
			if (bufp != abuf)
			{
				free(bufp);
				bufp = abuf;
			}
			goto retry;

		  case T_MB:
			i = dn_expand((u_char *) &answer, eom, ap,
					(u_char) hbuf, sizeof hbuf);
			if (i < 0)
				break;

			/* hbuf now has the host to deliver to */
			break;

		  case T_MG:
			i = dn_expand((u_char *) &answer, eom, ap,
					(u_char) gbuf, sizeof gbuf);
			if (i < 0)
				break;
			AliasLevel++;
			naddrs += sendtolist(ubuf, a, sendq, e);
			AliasLevel--;
			break;

		  case T_MINFO:
			/* bleach */
			XXX;
		}



		if (type != T_MX)
		{
			if (tTd(8, 8) || _res.options & RES_DEBUG)
				printf("unexpected answer type %d, size %d\n",
				    type, n);
			cp += n;
			continue;
		}
		GETSHORT(pref, cp);
		if ((n = dn_expand((u_char *)&answer, eom, cp,
				   (u_char *)bp, buflen)) < 0)
			break;
		cp += n;


#endif /* DNS_MAILB */
E 60
I 25
D 27

#ifndef BSD

/*
 * Skip over a compressed domain name. Return the size or -1.
 */
__dn_skipname(comp_dn, eom)
D 26
	const u_char *comp_dn, *eom;
E 26
I 26
	u_char *comp_dn, *eom;
E 26
{
	register u_char *cp;
	register int n;

	cp = (u_char *)comp_dn;
	while (cp < eom && (n = *cp++)) {
		/*
		 * check for indirection
		 */
		switch (n & INDIR_MASK) {
		case 0:		/* normal case, n == len */
			cp += n;
			continue;
		default:	/* illegal type */
			return (-1);
		case INDIR_MASK:	/* indirection */
			cp++;
		}
		break;
	}
	return (cp - comp_dn);
}

#endif /* not BSD */
E 27
E 25
I 17
D 104

D 19
#endif /* NAMED_BIND */
E 19
I 19
#else /* not NAMED_BIND */

D 102
#include <netdb.h>

E 102
I 30
bool
E 30
D 66
getcanonname(host, hbsize)
E 66
I 66
getcanonname(host, hbsize, trymx)
E 66
	char *host;
	int hbsize;
I 66
	bool trymx;
E 66
{
	struct hostent *hp;
I 90
	char *p;
E 90

D 101
	hp = gethostbyname(host);
E 101
I 101
	hp = sm_gethostbyname(host);
E 101
	if (hp == NULL)
D 30
		return;
E 30
I 30
		return (FALSE);
I 90
	p = hp->h_name;
	if (strchr(p, '.') == NULL)
	{
		/* first word is a short name -- try to find a long one */
		char **ap;
E 90
E 30

D 90
	if (strlen(hp->h_name) >= hbsize)
E 90
I 90
		for (ap = hp->h_aliases; *ap != NULL; ap++)
			if (strchr(*ap, '.') != NULL)
				break;
		if (*ap != NULL)
			p = *ap;
	}

	if (strlen(p) >= hbsize)
E 90
D 30
		return;
E 30
I 30
		return (FALSE);
E 30

D 90
	(void) strcpy(host, hp->h_name);
E 90
I 90
	(void) strcpy(host, p);
E 90
I 30
	return (TRUE);
E 30
}

#endif /* not NAMED_BIND */
E 104
I 104
#endif /* NAMED_BIND */
E 104
E 19
E 17
I 6
D 9

u_short
getshort(msgp)
	char *msgp;
{
	register u_char *p = (u_char *) msgp;
	register int u;

	u = *p++ << 8;
	return ((u_short)(u | *p));
}

E 9
E 6
I 2
D 11
#endif MXDOMAIN
E 11
E 2
E 1
