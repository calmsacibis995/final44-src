h59077
s 00009/00009/02615
d D 8.4 95/05/30 20:57:13 dab 92 91
c code cleanup, change b*() calls to mem*() calls
e
s 00001/00001/02623
d D 8.3 95/03/23 08:06:40 dab 91 90
c When looking for command characters in the data stream,
c don't strip off the upper bit if we are in binary mode.
e
s 00077/00026/02547
d D 8.2 93/12/15 11:36:01 dab 90 89
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00002/00002/02571
d D 8.1 93/06/06 16:33:39 bostic 89 88
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00022/02551
d D 5.56 93/05/20 10:49:23 dab 88 86
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00022/00022/02551
d R 5.56 93/05/20 10:37:14 dab 87 86
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00040/00006/02533
d D 5.55 93/04/05 17:05:50 dab 86 85
c Fix gcc2 warnings.
c Fix the generation/parsing of the Environment option SEND suboption.
c Add code (#ifdef ENV_HACK) to help interoperation with Telnet servers
c that have the definitions for ENV_VAR and ENV_VALUE reversed.
e
s 00052/00022/02487
d D 5.54 92/12/18 14:06:43 dab 85 84
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00018/00002/02491
d D 5.53 91/03/22 13:08:44 dab 84 83
c Upgrade to the latest & greatest authentication/encryption
e
s 00426/00318/02067
d D 5.52 91/03/01 01:32:02 dab 83 82
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00032/00015/02353
d D 5.51 90/09/14 10:48:38 borman 82 81
c Latest batch of changes.  See the README file
c for a list of all the changes to telnet & telnetd.
e
s 00267/00026/02101
d D 5.50 90/06/28 12:57:32 borman 81 80
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00011/00016/02116
d D 5.49 90/06/20 16:44:28 kfall 80 79
c towards Kerberized telnet
e
s 00145/00000/01987
d D 5.48 90/06/20 16:33:16 kfall 79 78
c put in code for authentication option
e
s 00001/00011/01986
d D 5.47 90/06/01 17:46:07 bostic 78 77
c new copyright notice
e
s 00000/00004/01997
d D 5.46 90/05/15 20:00:14 bostic 77 76
c string.h is ANSI C include file
e
s 00011/00012/01990
d D 5.45 90/03/01 06:18:39 borman 76 75
c Several items:
c 1) Change from TC[GS]ETA* to TIOC[GS]ETA*
c 2) Use the cc_t typedef from terios.h
c 3) Add SLC_FORW support
c 4) Add TOS support
c 5) Fix the SLC_SUSP support.  The escape
c    character now uses one of the VEOL characters.
e
s 00014/00011/01988
d D 5.44 89/11/14 10:20:10 borman 75 74
c Latest & greatest version of telnet
e
s 00238/00026/01761
d D 5.43 89/09/01 15:47:41 borman 74 73
c  RFC 1091 term type support, STATUS support, BINARY changes
e
s 00006/00002/01781
d D 5.42 89/08/28 09:58:17 borman 73 72
c Fix tty state when turning off/on LINEMODE option
e
s 00772/00166/01011
d D 5.41 89/08/21 14:58:48 borman 72 71
c Add support for LINEMODE option
e
s 00126/00081/01051
d D 5.40 89/03/21 22:30:45 minshall 71 70
c Keep track of each side's idea of what the state of each option is.
e
s 00083/00003/01049
d D 5.39 89/03/20 23:52:17 minshall 70 69
c Mods from DDP, et al, for LFLOW, TSPEED, and NAWS support.
e
s 00001/00001/01051
d D 5.38 89/02/06 19:58:49 minshall 69 68
c Restore sccs ID.
e
s 00001/00000/01051
d D 5.37 88/12/21 22:57:33 minshall 68 67
c Bug fix from Tony Li, USC.  Turn off options for future negotiations.
e
s 00002/00005/01049
d D 5.36 88/11/18 22:30:46 minshall 67 66
c Count SIGIO's (for debugging).  Separate out noasynch between
c tty and net.
e
s 00032/00094/01022
d D 5.35 88/09/16 22:35:28 minshall 66 65
c Well, this is version 5.33 with one fix.  The intermediate
c versions were but an interesting diversion.  This fixes the isolated
c CR problem.  The fix is from Karl Reuss <reuss@umd5.umd.edu> who says
c he got it from someone at DEC who says HE got it from someone at
c Berkeley.  Sigh.
e
s 00092/00032/01024
d D 5.34 88/09/14 23:50:58 minshall 65 64
c First try - adaptive algorithms for telnet to deal with
c isolated CR's.
e
s 00010/00005/01046
d D 5.33 88/06/29 20:15:31 bostic 64 63
c install approved copyright notice
e
s 00008/00002/01043
d D 5.32 88/06/27 22:19:24 minshall 63 62
c Fix up lint errors.
e
s 00002/00002/01043
d D 5.31 88/05/15 12:47:57 minshall 62 61
c Make it work for tn3270.
e
s 00006/00005/01039
d D 5.30 88/03/27 13:52:19 minshall 61 60
c Make it *compile* with -DTN3270.
e
s 00013/00007/01031
d D 5.29 88/03/08 10:31:04 bostic 60 59
c add Berkeley specific copyright
e
s 00001/00000/01037
d D 5.28 88/02/17 18:50:24 minshall 59 58
c Fix bug when no TERM environment variable set (len not set).
c (Reported by M. Karels.)
e
s 00003/00001/01034
d D 5.27 88/01/07 15:26:42 minshall 58 57
c Make SYNCH work (ie: urgent (ie: ring markers)).
e
s 00001/00003/01034
d D 5.26 88/01/07 11:54:07 minshall 57 56
c Reduce extern's.
e
s 00005/00003/01032
d D 5.25 87/11/23 20:37:58 minshall 56 55
c Fixes from Dave Borman.
e
s 00001/00001/01034
d D 5.24 87/11/23 11:15:34 minshall 55 54
c Add in some changes from Dave Borman (borman@monet).
e
s 00166/00022/00869
d D 5.23 87/10/27 16:03:16 minshall 54 53
c Various changes, moves.
e
s 00038/00420/00853
d D 5.22 87/10/23 15:15:45 minshall 53 52
c Try to move system dependent stuff to system dependent files.
e
s 00020/00019/01253
d D 5.21 87/10/23 11:57:20 minshall 52 51
c Make the ring buffer a two-state buffer (supplier and consumer)
c rather than a three-state buffer (supplier, sender, and acker).
e
s 00148/00118/01124
d D 5.20 87/10/10 17:46:14 minshall 51 50
c Lots of changes.  telsnd() is new; move to ring's for
c input buffers.
e
s 00016/00067/01226
d D 5.19 87/10/10 14:27:22 minshall 50 49
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00958/02032/00335
d D 5.18 87/10/10 11:47:10 minshall 49 48
c This is the new, restructured version.
e
s 00004/00001/02363
d D 5.17 87/07/07 14:36:09 minshall 48 47
c Fix core dumps on suns (from sun!nowicki, Bill Nowicki).
c bug report 4.2BSD/ucb/237
e
s 00004/00003/02360
d D 5.16 86/05/27 09:46:24 minshall 47 46
c Fixed the mapping of \n to \r\n (from tty to network) whenever 
c CRMOD is true.
e
s 00004/00000/02359
d D 5.15 86/05/13 11:45:58 minshall 46 45
c Add acknowledgement to Dave Borman.
e
s 00002/00002/02357
d D 5.14 86/05/06 21:14:30 minshall 45 44
c Get back the SCCS keywords.
e
s 00178/00045/02181
d D 5.13 86/05/02 11:46:53 minshall 44 43
c This version handles terminal type correctly, and
c responds well to various DONT commands.
e
s 00273/00123/01953
d D 5.12 86/04/22 22:17:27 minshall 43 42
c Various changes, including flushing the network buffer
c before sending TELNET SYNCH.
e
s 00146/00089/01930
d D 5.11 86/04/20 21:27:02 minshall 42 41
c Various fixes, plus adding "autoflush", plus ^O recognition.
e
s 00380/00361/01639
d D 5.10 86/04/19 16:34:48 minshall 41 40
c Minor change to allow for certain hosts whose TCP urgent pointer is off by one.
e
s 00291/00071/01709
d D 5.9 86/04/17 22:41:11 minshall 40 39
c This version is fairly close to a production one.
c We should now send SYNCH in a 4.2/4.3 compatible manner.
c We should now come as close as possible in receiving SYNCH.
c We now implement the "display" command.
e
s 00528/00122/01252
d D 5.8 86/04/16 22:37:11 minshall 39 38
c One more day of hacking.
c Basically, most of Dave Borman's changes are in.  This is by
c no means a finished product.  There are still unanswered questions,
c plus a lot of rough edges.
e
s 00783/00462/00591
d D 5.7 86/04/15 16:12:08 minshall 38 37
c This version is restructured, and includes a
c "send" and "toggle" command.
e
s 00161/00061/00892
d D 5.6 86/04/09 09:25:18 minshall 37 36
c This version handles CR-LF, CR-NULL, CR-whatever correctly.
e
s 00006/00000/00947
d D 5.5 86/03/11 12:00:55 karels 36 34
c can't reconnect after some errors
e
s 00003/00001/00946
d R 5.5 86/03/11 11:34:54 karels 35 34
c can't retry if got too far
e
s 00002/00004/00945
d D 5.4 86/01/10 02:08:13 lepreau 34 33
c In command mode exit on EOF on stdin
e
s 00028/00012/00921
d D 5.3 85/11/08 11:49:22 karels 33 32
c try host numbers before addresses, try multiple addresses in turn
e
s 00020/00010/00913
d D 5.2 85/10/24 21:18:00 karels 32 30
c don't send initial SGA option if not using standard port;
c clean up help a bit
e
s 00022/00010/00913
d R 5.2 85/10/24 21:04:20 karels 31 30
c don't unset local start/stop (won't trash connection info, either);
c don't send initial SGA option if not using standard port; add help as well as ?
e
s 00013/00001/00910
d D 5.1 85/05/31 09:35:02 dist 30 29
c Add copyright
e
s 00047/00007/00864
d D 4.27 85/02/05 08:32:22 ralph 29 28
c added sendesc, ayt, interrupt commands; fix half duplex bugs.
e
s 00002/00000/00869
d D 4.26 84/12/23 17:40:17 sam 28 27
c didn't convert \r to \r\n; from brl
e
s 00010/00005/00859
d D 4.25 84/12/06 18:09:36 leres 27 26
c Use new setsockopt() interface
e
s 00002/00002/00862
d D 4.24 83/07/20 16:09:29 helge 26 25
c fix debug stuff
e
s 00006/00001/00858
d D 4.23 83/07/19 22:33:19 sam 25 22
c handle EOF from tty properly
e
s 00006/00001/00858
d R 4.23 83/07/19 22:28:48 sam 24 22
c handle EOF on tty properly
e
s 00006/00001/00858
d R 4.23 83/07/18 20:31:49 sam 23 22
c handle EOF from tty properly
e
s 00006/00000/00853
d D 4.22 83/06/21 20:43:54 sam 22 21
c fix from jdd@allegra.UUCP
e
s 00025/00019/00828
d D 4.21 83/06/13 02:48:48 sam 21 20
c and another put back to before
e
s 00004/00006/00843
d D 4.20 83/06/10 23:34:19 sam 20 19
c new signals, no libjobs
e
s 00003/00003/00846
d D 4.19 83/05/03 19:57:36 sam 19 18
c move from netser forces telnet.h to <arpa/telnet.h>
e
s 00032/00028/00817
d D 4.18 83/03/29 11:29:11 sam 18 17
c fix shutdown problem; double IAC's on output; misc cleanups
e
s 00001/00001/00844
d D 4.17 83/01/23 13:46:01 sam 17 16
c declare setdebug function
e
s 00016/00000/00829
d D 4.16 83/01/16 16:57:58 sam 16 15
c add debugging
e
s 00060/00034/00769
d D 4.15 82/12/25 22:33:21 sam 15 14
c use new ioctl calls; negate crmod by default and add user
c settable cr mapping on output for multics braindamage (really terminal handler)
e
s 00001/00001/00802
d D 4.14 82/12/25 21:19:35 sam 14 13
c port numbers now byte swapped
e
s 00001/00001/00802
d D 4.13 82/11/17 16:09:14 sam 13 12
c forgot to change socket calls
e
s 00018/00010/00785
d D 4.12 82/11/14 15:19:34 sam 12 11
c convert to 4.1c sys calls and directory layout
e
s 00054/00049/00741
d D 4.11 82/10/07 22:34:27 sam 11 10
c bug with options not being reset/reverse echo option request
e
s 00017/00008/00773
d D 4.10 82/10/07 21:38:59 sam 10 9
c handle . notation for host names
e
s 00032/00034/00749
d D 4.9 82/10/06 18:26:15 sam 9 8
c bugs with error ignored error returns & new net data base library
e
s 00006/00002/00777
d D 4.8 82/07/13 09:49:38 feldman 8 7
c changed escape char, added debug option, byte swap port #
e
s 00009/00001/00770
d D 4.7 82/04/10 18:21:27 sam 7 6
c watch for write failures to the net
e
s 00003/00000/00768
d D 4.6 82/03/31 10:04:47 sam 6 5
c assume initial option state reflects options automatically sent
e
s 00014/00008/00754
d D 4.5 82/03/23 14:35:01 root 5 4
c debugging stuff
e
s 00001/00002/00761
d D 4.4 82/03/16 21:25:18 root 4 3
c set up sccsid's
e
s 00001/00001/00762
d D 4.3 82/03/01 20:49:27 sam 3 2
c s_addr is u_long, so <= is pointless
e
s 00064/00005/00699
d D 4.2 82/03/01 11:52:00 sam 2 1
c bug fix, plus code to view option negotiation
e
s 00704/00000/00000
d D 4.1 82/02/28 10:34:16 root 1 0
c date and time created 82/02/28 10:34:16 by root
e
u
U
t
T
I 30
D 49
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

E 49
E 30
I 18
D 60
#ifndef lint
I 30
D 49
char copyright[] =
D 44
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 44
I 44
D 45
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 45
I 45
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 49
I 49
static char copyright[] =
"@(#) Copyright (c) 1984-1987 Regents of the University of California.\n\
E 49
E 45
E 44
 All rights reserved.\n";
D 49
#endif not lint
E 49
I 49
#endif	/* not lint */
E 60
I 60
/*
D 82
 * Copyright (c) 1988 Regents of the University of California.
E 82
I 82
D 89
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 82
 * All rights reserved.
E 89
I 89
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 89
 *
D 78
 * Redistribution and use in source and binary forms are permitted
D 64
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 64
I 64
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
E 78
I 78
 * %sccs.include.redist.c%
E 78
E 64
 */
E 60
E 49

#ifndef lint
E 30
E 18
I 1
D 4
/*	%M%	%I%	%E%	*/

E 4
I 4
D 44
static char sccsid[] = "%W% (Berkeley) %G%";
E 44
I 44
D 45
static char sccsid[] = "@(#)telnet.c	5.12 (Berkeley) 4/22/86";
E 45
I 45
D 49
static char sccsid[] = "%W% (Berkeley) %G%";
E 45
E 44
I 18
D 30
#endif
E 30
I 30
#endif not lint
E 49
I 49
D 60
static char sccsid[] = "@(#)telnet.c	1.2 (Berkeley) 9/25/87";
#endif	/* not lint */
E 60
I 60
D 66
static char sccsid[] = "%W% (Berkeley) %G%";
E 66
I 66
D 69
static char sccsid[] = "@(#)telnet.c	5.33 (Berkeley) 6/29/88";
E 69
I 69
static char sccsid[] = "%W% (Berkeley) %G%";
E 69
E 66
#endif /* not lint */
E 60
E 49
E 30

E 18
E 4
D 50
/*
D 49
 * User telnet program.
E 49
I 49
 * User telnet program, modified for use by tn3270.c.
E 49
I 46
 *
D 49
 * Many of the FUNCTIONAL changes in this newest version of telnet
E 49
I 49
 * Many of the FUNCTIONAL changes in this newest version of TELNET
E 49
 * were suggested by Dave Borman of Cray Research, Inc.
I 49
 *
 * Other changes in the tn3270 side come from Alan Crosswell (Columbia),
 * Bob Braden (ISI), Steve Jacobson (Berkeley), and Cliff Frost (Berkeley).
 *
 * This code is common between telnet(1c) and tn3270(1c).  There are the
 * following defines used to generate the various versions:
 *
 *	TN3270		- 	This is to be linked with tn3270.
 *
 *	NOT43		-	Allows the program to compile and run on
 *				a 4.2BSD system.
 *
 *	PUTCHAR		-	Within tn3270, on a NOT43 system,
 *				allows the use of the 4.3 curses
 *				(greater speed updating the screen).
 *				You need the 4.3 curses for this to work.
 *
 *	FD_SETSIZE	-	On whichever system, if this isn't defined,
 *				we patch over the FD_SET, etc., macros with
 *				some homebrewed ones.
 *
 *	SO_OOBINLINE	-	This is a socket option which we would like
 *				to set to allow TCP urgent data to come
 *				to us "inline".  This is NECESSARY for
 *				CORRECT operation, and desireable for
 *				simpler operation.
 *
 *	LNOFLSH		-	Detects the presence of the LNOFLSH bit
 *				in the tty structure.
 *
 *	unix		-	Compiles in unix specific stuff.
 *
 *	MSDOS		-	Compiles in MSDOS specific stuff.
 *
E 49
E 46
 */
I 46

E 50
E 46
I 12
#include <sys/types.h>
D 49
#include <sys/socket.h>
I 15
#include <sys/ioctl.h>
E 49
I 40
D 53
#include <sys/time.h>
I 49
#include <sys/socket.h>
E 53
E 49
E 40
E 15

I 79
D 83
#ifdef	KERBEROS
#include <sys/socket.h>
#include <netinet/in.h>
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
#include "krb4-proto.h"
#endif

E 83
E 79
D 53
#include <netinet/in.h>

E 53
I 19
D 49
#define	TELOPTS
E 49
I 49
#if	defined(unix)
I 61
#include <signal.h>
E 61
/* By the way, we need to include curses.h before telnet.h since,
 * among other things, telnet.h #defines 'DO', which is a variable
 * declared in curses.h.
 */
D 75
#include <curses.h>
E 75
#endif	/* defined(unix) */

E 49
#include <arpa/telnet.h>
I 49

I 81
D 83
#if	defined(unix)
#include <strings.h>
#else	/* defined(unix) */
E 81
D 53
#if	!defined(NOT43)
E 49
I 41
#include <arpa/inet.h>
I 49
#else	/* !defined(NOT43) */
extern unsigned long inet_addr();
extern char	*inet_ntoa();
#endif	/* !defined(NOT43) */
E 49
E 41

E 19
E 12
D 49
#include <stdio.h>
E 49
#include <ctype.h>
#include <errno.h>
D 49
#include <signal.h>
D 15
#include <sgtty.h>
E 15
#include <setjmp.h>
E 49
D 12
#include <sys/types.h>
#include <sys/socket.h>
#include <net/in.h>
E 12
I 9
#include <netdb.h>
I 49

E 53
D 77
#if	defined(unix)
E 49
I 41
#include <strings.h>
I 49
#else	/* defined(unix) */
E 77
#include <string.h>
I 81
#endif	/* defined(unix) */
E 81
D 77
#endif	/* defined(unix) */
E 77
E 49
E 41
I 12
D 19

E 12
E 9
I 2
#define	TELOPTS
E 2
#include "telnet.h"
E 19

E 83
I 74
#include <ctype.h>

E 74
I 50
#include "ring.h"

E 50
I 49
#include "defines.h"
#include "externs.h"
#include "types.h"
#include "general.h"
E 49
I 40

D 53

I 49
D 50
#if	!defined(TN3270)
#define	ExitString(f,s,r)	{ fprintf(f, s); exit(r); }
#define	Exit(x)			exit(x)
#define	SetIn3270()

E 50
void	setcommandmode(), command();	/* forward declarations */
D 50
#endif	/* !defined(TN3270) */
E 50

E 49
I 44
#ifndef	FD_SETSIZE
E 44
/*
 * The following is defined just in case someone should want to run
 * this telnet on a 4.2 system.
 *
D 44
 * This has never been tested, so good luck...
E 44
 */
D 44
#ifndef	FD_SETSIZE
E 44

D 44
typedef long	fd_set;
E 44
I 44
#define	FD_SET(n, p)	((p)->fds_bits[0] |= (1<<(n)))
#define	FD_CLR(n, p)	((p)->fds_bits[0] &= ~(1<<(n)))
#define	FD_ISSET(n, p)	((p)->fds_bits[0] & (1<<(n)))
#define FD_ZERO(p)	((p)->fds_bits[0] = 0)
E 44

D 44
#define	FD_SET(n, p)	(*(p) |= (1<<(n)))
#define	FD_CLR(n, p)	(*(p) &= ~(1<<(n)))
#define	FD_ISSET(n, p)	(*(p) & (1<<(n)))
#define FD_ZERO(p)	(*(p) = 0)

E 44
#endif
E 53

E 40
D 15
#define	ctrl(x)		((x) & 037)
E 15
D 41
#define	strip(x)	((x)&0177)
E 41
I 41
D 42
#define	strip(x)	((x)&0x3f)
E 42
I 42
D 91
#define	strip(x)	((x)&0x7f)
E 91
I 91
#define	strip(x) ((my_want_state_is_wont(TELOPT_BINARY)) ? ((x)&0x7f) : (x))
E 91
I 49
D 53
#define min(x,y)	((x<y)? x:y)
E 53
E 49
E 42
E 41
D 12
#define	INFINITY	10000000
E 12
D 9
#define	swab(x)		((((x) >> 8) | ((x) << 8)) & 0xffff)
E 9

I 81
D 83
extern char *env_getvalue();
E 81
D 42
char	ttyobuf[BUFSIZ], *tfrontp = ttyobuf, *tbackp = ttyobuf;
I 38
D 41
#define	TTYADD(c)	{ if (!flushing) { *tfrontp++ = c; } }
E 41
I 41
#define	TTYADD(c)	{ if (!SYNCHing) { *tfrontp++ = c; } }
E 42
I 42
D 49
char	ttyobuf[2*BUFSIZ], *tfrontp = ttyobuf, *tbackp = ttyobuf;
#define	TTYADD(c)	{ if (!(SYNCHing||flushout)) { *tfrontp++ = c; } }
#define	TTYLOC()	(tfrontp)
#define	TTYMAX()	(ttyobuf+sizeof ttyobuf-1)
#define	TTYMIN()	(netobuf)
#define	TTYBYTES()	(tfrontp-tbackp)
#define	TTYROOM()	(TTYMAX()-TTYLOC()+1)
E 49
I 49
D 53
#if	defined(TN3270)
static char	Ibuf[8*BUFSIZ], *Ifrontp, *Ibackp;
#endif	/* defined(TN3270) */
E 53
E 49
E 42
E 41

E 38
D 11
char	netobuf[BUFSIZ] =
	{ IAC, DO, TELOPT_ECHO, IAC, DO, TELOPT_SGA,
	  IAC, WONT, TELOPT_SGA },
	*nfrontp = netobuf + 9, *nbackp = netobuf;
E 11
I 11
D 42
char	netobuf[BUFSIZ], *nfrontp = netobuf, *nbackp = netobuf;
E 42
I 42
D 49
char	netobuf[2*BUFSIZ], *nfrontp = netobuf, *nbackp = netobuf;
E 42
I 38
#define	NETADD(c)	{ *nfrontp++ = c; }
#define	NET2ADD(c1,c2)	{ NETADD(c1); NETADD(c2); }
#define NETLOC()	(nfrontp)
I 42
#define	NETMAX()	(netobuf+sizeof netobuf-1)
#define	NETBYTES()	(nfrontp-nbackp)
#define	NETROOM()	(NETMAX()-NETLOC()+1)
E 42
char	*neturg = 0;		/* one past last byte of urgent data */
E 49
E 38
E 11
D 53

E 53
I 44
D 49
char	subbuffer[100], *subpointer, *subend;	/* buffer for sub-options */
E 49
I 49
static char	subbuffer[SUBBUFSIZE],
		*subpointer, *subend;	 /* buffer for sub-options */
E 83
I 83
static unsigned char	subbuffer[SUBBUFSIZE],
			*subpointer, *subend;	 /* buffer for sub-options */
E 83
E 49
#define	SB_CLEAR()	subpointer = subbuffer;
D 83
#define	SB_TERM()	subend = subpointer;
E 83
I 83
#define	SB_TERM()	{ subend = subpointer; SB_CLEAR(); }
E 83
#define	SB_ACCUM(c)	if (subpointer < (subbuffer+sizeof subbuffer)) { \
				*subpointer++ = (c); \
			}

I 83
#define	SB_GET()	((*subpointer++)&0xff)
#define	SB_PEEK()	((*subpointer)&0xff)
#define	SB_EOF()	(subpointer >= subend)
#define	SB_LEN()	(subend - subpointer)

E 83
I 49
D 53
static char	sb_terminal[] = { IAC, SB,
			TELOPT_TTYPE, TELQUAL_IS,
			'I', 'B', 'M', '-', '3', '2', '7', '8', '-', '2',
			IAC, SE };
#define	SBTERMMODEL	13


E 53
E 49
E 44
D 71
char	hisopts[256];
char	myopts[256];
E 71
I 71
char	options[256];		/* The combined options */
D 72
#define	he_said_will(c)		options[c] |= OPT_HE_SAID_WILL
#define	he_said_wont(c)		options[c] &= ~OPT_HE_SAID_WILL
#define	he_said_do(c)		options[c] |= OPT_HE_SAID_DO
#define	he_said_dont(c)		options[c] &= ~OPT_HE_SAID_DO
E 72
I 72
char	do_dont_resp[256];
char	will_wont_resp[256];
E 72
E 71

D 71
char	doopt[] = { IAC, DO, '%', 'c', 0 };
char	dont[] = { IAC, DONT, '%', 'c', 0 };
char	will[] = { IAC, WILL, '%', 'c', 0 };
char	wont[] = { IAC, WONT, '%', 'c', 0 };
E 71
I 71
D 72
#define	I_said_will(c)		options[c] |= OPT_I_SAID_WILL
#define	I_said_wont(c)		options[c] &= ~OPT_I_SAID_WILL
#define	I_said_do(c)		options[c] |= OPT_I_SAID_DO
#define	I_said_dont(c)		options[c] &= ~OPT_I_SAID_DO
E 71

E 72
I 38
D 49
struct cmd {
	char	*name;		/* command name */
	char	*help;		/* help string */
	int	(*handler)();	/* routine which executes command */
	int	dohelp;		/* Should we give general help information? */
	int	needconnect;	/* Do we need to be connected to execute? */
};
E 49
I 49
D 51
static char	sibuf[BUFSIZ], *sbp;
static char	tibuf[BUFSIZ], *tbp;
E 51
I 51
D 53
static Ring	netiring, ttyiring;
static char	netibuf[BUFSIZ];
static char	ttyibuf[BUFSIZ];
E 51
static fd_set ibits, obits, xbits;
E 49

E 38
D 49
int	connected;
int	net;
I 38
int	tout;
E 38
I 2
D 15
int	showoptions;
E 15
I 15
int	showoptions = 0;
E 15
I 8
D 41
int	options;
E 41
I 16
int	debug = 0;
E 16
I 15
int	crmod = 0;
I 37
D 38
int	printnet = 0;
E 38
I 38
int	netdata = 0;
E 38
static FILE	*NetTrace;
E 37
I 32
int	telnetport = 1;
E 49
I 38

E 53
I 49
int
I 83
	eight = 0,
	autologin = 0,	/* Autologin anyone? */
I 84
	skiprc = 0,
E 84
E 83
	connected,
D 53
	net,
E 53
D 51
	scc,
	tcc,
E 51
	showoptions,
	In3270,		/* Are we in 3270 mode? */
	ISend,		/* trying to send network data in */
I 79
D 83
#ifdef	KERBEROS
	kerberized = 0,	/* Are we using Kerberos authentication ? */
#endif
E 83
E 79
	debug = 0,
	crmod,
	netdata,	/* Print out network data flow */
	crlf,		/* Should '\r' be mapped to <CR><LF> (or <CR><NUL>)? */
I 63
#if	defined(TN3270)
E 63
D 67
	noasynch = 0,	/* User specified "-noasynch" on command line */
E 67
I 67
	noasynchtty = 0,/* User specified "-noasynch" on command line */
	noasynchnet = 0,/* User specified "-noasynch" on command line */
E 67
	askedSGA = 0,	/* We have talked about suppress go ahead */
I 63
#endif	/* defined(TN3270) */
E 63
D 53
	telnetport = 1;
E 53
I 53
D 57
	telnetport = 1,
E 57
I 57
	telnetport,
E 57
	SYNCHing,	/* we are in TELNET SYNCH mode */
	flushout,	/* flush output */
	autoflush = 0,	/* flush output when interrupting? */
	autosynch,	/* send interrupt characters with SYNCH? */
I 70
	localflow,	/* we handle flow control locally */
I 85
	restartany,	/* if flow control enabled, restart on any character */
E 85
E 70
	localchars,	/* we recognize interrupt/quit */
	donelclchars,	/* the user has set "localchars" */
	donebinarytoggle,	/* the user has put us in binary */
	dontlecho,	/* do we suppress local echoing right now? */
	globalmode;
E 53
E 49
D 41
int	flushing = 0;		/* are we in TELNET SYNCH mode? */
E 41

E 38
E 32
E 15
E 8
E 2
D 49
char	*prompt;
D 8
char	escape = ctrl('_');
E 8
I 8
D 15
char	escape = ctrl(']');
E 15
I 15
char	escape = CTRL(]);
I 39
char	echoc = CTRL(E);
E 49
I 49
D 81
#define	CONTROL(x)	((x)&0x1f)		/* CTRL(x) is not portable */
E 81
I 81
char *prompt = 0;
E 81
E 49
D 41
int	flushout = 0;
int	localsigs = 0;
int	donelclsigs = 0;
int	linemode;
int	doechocharrecognition = 0;
int	dontlecho = 0;		/* do we do local echoing right now? */
E 41
E 39
E 15
E 8

I 41
D 49
int	SYNCHing = 0;		/* we are in TELNET SYNCH mode */
int	flushout = 0;		/* flush output */
I 42
int	autoflush = 0;		/* flush output when interrupting? */
E 42
int	autosynch = 0;		/* send interrupt characters with SYNCH? */
D 43
int	localsigs = 0;		/* we recognize interrupt/quit */
int	donelclsigs = 0;	/* the user has set "localsigs" */
int	doechocharrecognition = 1;	/* in line mode recognize echo toggle */
E 43
I 43
int	localchars = 0;		/* we recognize interrupt/quit */
int	donelclchars = 0;	/* the user has set "localchars" */
E 43
int	dontlecho = 0;		/* do we suppress local echoing right now? */
E 49
I 49
D 75
char
E 75
I 75
D 76
unsigned char
E 75
	*prompt = 0,
	escape,
	echoc;
E 76
I 76
D 81
unsigned char *prompt = 0;
E 81
I 81
cc_t escape;
I 83
cc_t rlogin;
E 83
#ifdef	KLUDGELINEMODE
cc_t echoc;
#endif
E 81
E 76
E 49

I 76
D 81
cc_t escape, echoc;

E 81
E 76
E 41
D 49
char	line[200];
int	margc;
char	*margv[20];
E 49
I 49
D 53
int
	SYNCHing,		/* we are in TELNET SYNCH mode */
	flushout,		/* flush output */
	autoflush = 0,		/* flush output when interrupting? */
	autosynch,		/* send interrupt characters with SYNCH? */
	localchars,		/* we recognize interrupt/quit */
	donelclchars,		/* the user has set "localchars" */
	donebinarytoggle,	/* the user has put us in binary */
	dontlecho,		/* do we suppress local echoing right now? */
	globalmode;
E 49

D 49
jmp_buf	toplevel;
jmp_buf	peerdied;
E 49
I 49
/*	The following are some tn3270 specific flags */
#if	defined(TN3270)
E 49

D 49
extern	int errno;
E 49
I 49
static int
	Sent3270TerminalType;	/* Have we said we are a 3270? */
E 49

D 38
int	tn(), quit(), suspend(), bye(), help();
D 2
int	setescape(), status(), toggle();
E 2
I 2
int	setescape(), status(), toggle(), setoptions();
I 15
D 17
int	setcrmod();
E 17
I 17
D 29
int	setcrmod(), setdebug();
E 29
I 29
int	setcrmod(), setdebug(), sendesc(), ayt(), intp();
I 37
int	setprintnet();
E 38
E 37
E 29
E 17
E 15
E 2
D 49

D 11
#define HELPINDENT (sizeof("connect"))
E 11
I 11
D 38
#define HELPINDENT (sizeof ("connect"))
E 11

struct cmd {
D 18
	char	*name;
	char	*help;
	int	(*handler)();
E 18
I 18
	char	*name;		/* command name */
	char	*help;		/* help string */
	int	(*handler)();	/* routine which executes command */
I 37
	int	dohelp;		/* Should we give general help information? */
E 37
E 18
};

D 18
char	ohelp[] = "connect to a site";
char	chelp[] = "close current connection";
char	qhelp[] = "exit telnet";
char	zhelp[] = "suspend telnet";
I 16
char	dhelp[] = "toggle debugging";
E 16
char	ehelp[] = "set escape character";
char	shelp[] = "print status information";
char	hhelp[] = "print help information";
I 2
char	phelp[] = "toggle viewing of options processing";
I 15
char	rhelp[] = "toggle mapping of received carriage returns";
E 18
I 18
char	openhelp[] =	"connect to a site";
char	closehelp[] =	"close current connection";
char	quithelp[] =	"exit telnet";
char	zhelp[] =	"suspend telnet";
char	debughelp[] =	"toggle debugging";
char	escapehelp[] =	"set escape character";
char	statushelp[] =	"print status information";
char	helphelp[] =	"print help information";
char	optionshelp[] =	"toggle viewing of options processing";
char	crmodhelp[] =	"toggle mapping of received carriage returns";
I 29
char	sendeschelp[] =	"send escape character";
D 32
char	aythelp[] =	"send Are You There";
char	intphelp[] =	"send Interrupt Process";
E 32
I 32
char	aythelp[] =	"send \"Are You There\"";
char	intphelp[] =	"send \"Interrupt Process\"";
I 37
char	printnethelp[] ="toggle printing of raw network data";
E 37
E 32
E 29
E 18
E 15
E 2

struct cmd cmdtab[] = {
D 18
	{ "open",	ohelp,		tn },
	{ "close",	chelp,		bye },
	{ "quit",	qhelp,		quit },
E 18
I 18
D 37
	{ "open",	openhelp,	tn },
	{ "close",	closehelp,	bye },
	{ "quit",	quithelp,	quit },
E 18
	{ "z",		zhelp,		suspend },
D 18
	{ "escape",	ehelp,		setescape },
	{ "status",	shelp,		status },
I 2
	{ "options",	phelp,		setoptions },
I 15
	{ "crmod",	rhelp,		setcrmod },
I 16
	{ "debug",	dhelp,		setdebug },
E 16
E 15
E 2
	{ "?",		hhelp,		help },
E 18
I 18
	{ "escape",	escapehelp,	setescape },
	{ "status",	statushelp,	status },
	{ "options",	optionshelp,	setoptions },
	{ "crmod",	crmodhelp,	setcrmod },
	{ "debug",	debughelp,	setdebug },
I 29
	{ "ayt",	aythelp,	ayt },
	{ "interrupt",	intphelp,	intp },
	{ "passthru",	sendeschelp,	sendesc },
I 32
	{ "help",	helphelp,	help },
E 32
E 29
	{ "?",		helphelp,	help },
E 37
I 37
	{ "open",	openhelp,	tn, 1 },
	{ "close",	closehelp,	bye, 1 },
	{ "quit",	quithelp,	quit, 1 },
	{ "z",		zhelp,		suspend, 1 },
	{ "escape",	escapehelp,	setescape, 1 },
	{ "status",	statushelp,	status, 1 },
	{ "crmod",	crmodhelp,	setcrmod, 1 },
	{ "ayt",	aythelp,	ayt, 1 },
	{ "interrupt",	intphelp,	intp, 1 },
	{ "passthru",	sendeschelp,	sendesc, 1 },
	{ "help",	helphelp,	help, 1 },
	{ "?",		helphelp,	help, 0 },
	{ "options",	optionshelp,	setoptions, 0 },
	{ "debug",	debughelp,	setdebug, 0 },
	{ "printnet",	printnethelp,	setprintnet, 0 },
E 37
E 18
	0
};

E 38
D 9
struct	sockaddr_in sin = { AF_INET, swab(IPPORT_TELNET) };
E 9
I 9
D 15
struct sockaddr_in sin = { AF_INET };
E 15
I 15
struct sockaddr_in sin;
E 15
E 9

D 39
int	intr(), deadpeer();
E 39
I 39
D 41
int	intr(), deadpeer(), doescape();
E 39
char	*control();
E 41
struct	cmd *getcmd();
I 9
struct	servent *sp;
E 9

I 11
D 15
struct	sgttyb ostbuf;
struct	tchars otchars;
int	odisc;
E 15
I 15
D 21
struct	ttychars otc;
int	oflags;
E 21
I 21
D 39
struct	tchars otc;
E 39
I 39
struct	tchars otc, ntc;
E 39
D 42
struct	ltchars oltc;
E 42
I 42
struct	ltchars oltc, nltc;
E 42
D 39
struct	sgttyb ottyb;
E 39
I 39
struct	sgttyb ottyb, nttyb;
int	globalmode = 0;
int	flushline = 1;
E 39
E 21
E 15

I 39
char	*hostname;
char	hnamebuf[32];

/*
 * The following are some clocks used to decide how to interpret
D 40
 * the relationship between various varibles.
E 40
I 40
 * the relationship between various variables.
E 40
 */

struct {
    int
	system,			/* what the current time is */
	echotoggle,		/* last time user entered echo character */
D 40
	modenegotiated;		/* last time operating mode negotiated */
E 40
I 40
	modenegotiated,		/* last time operating mode negotiated */
	didnetreceive,		/* last time we read data from network */
	gotDM;			/* when did we last see a data mark */
E 40
D 41
} times;
E 41
I 41
} clocks;
E 41

D 41
#define	settimer(x)	times.x = times.system++


E 39
E 11
main(argc, argv)
	int argc;
	char *argv[];
{
I 9
	sp = getservbyname("telnet", "tcp");
	if (sp == 0) {
		fprintf(stderr, "telnet: tcp/telnet: unknown service\n");
		exit(1);
	}
I 37
	NetTrace = stdout;
E 37
I 11
D 15
	ioctl(0, TIOCGETP, (char *)&ostbuf);
	ioctl(0, TIOCGETC, (char *)&otchars);
	ioctl(0, TIOCGETD, (char *)&odisc);
E 15
I 15
D 21
	ioctl(0, TIOCGET, (char *)&oflags);
	ioctl(0, TIOCCGET, (char *)&otc);
E 21
I 21
	ioctl(0, TIOCGETP, (char *)&ottyb);
	ioctl(0, TIOCGETC, (char *)&otc);
	ioctl(0, TIOCGLTC, (char *)&oltc);
I 39
	ntc = otc;
	ntc.t_eofc = -1;		/* we don't want to use EOF */
	nttyb = ottyb;
E 39
E 21
E 15
E 11
E 9
	setbuf(stdin, 0);
	setbuf(stdout, 0);
	prompt = argv[0];
I 8
D 27
	if (argc > 1 && !strcmp(argv[1], "-d"))
D 26
		options = SO_DEBUG, argv++, argc--;
E 26
I 26
		debug = SO_DEBUG, argv++, argc--;
E 27
I 27
	if (argc > 1 && !strcmp(argv[1], "-d")) {
		debug = 1;
		argv++;
		argc--;
	}
I 37
	if (argc > 1 && !strcmp(argv[1], "-n")) {
	    argv++;
	    argc--;
	    if (argc > 1) {		/* get file name */
		NetTrace = fopen(argv[1], "w");
		argv++;
		argc--;
		if (NetTrace == NULL) {
		    NetTrace = stdout;
		}
	    }
	}
E 37
E 27
E 26
E 8
	if (argc != 1) {
		if (setjmp(toplevel) != 0)
			exit(0);
		tn(argc, argv);
	}
	setjmp(toplevel);
	for (;;)
		command(1);
}
E 41
I 41
#define	settimer(x)	clocks.x = clocks.system++
E 41
I 39

/*
 * Various utility routines.
 */
E 39

I 41
char *ambiguous;		/* special return value */
#define Ambiguous(t)	((t)&ambiguous)


E 41
D 9
char host_name[100];
E 9
I 9
D 10
struct	hostent *host;
E 10
I 10
D 39
char	*hostname;
char	hnamebuf[32];
E 10
E 9

D 38
tn(argc, argv)
	int argc;
	char *argv[];
E 38
I 38

E 39
char **
genget(name, table, next)
char	*name;		/* name to match */
char	**table;		/* name entry in table */
char	**(*next)();	/* routine to return next entry in table */
E 38
{
D 38
	register int c;
I 10
D 33
	register struct hostent *host;
E 33
I 33
	register struct hostent *host = 0;
E 38
I 38
	register char *p, *q;
	register char **c, **found;
	register int nmatches, longest;
E 38
E 33
E 10

I 48
	if (name == 0) {
	    return 0;
	}
E 48
D 38
	if (connected) {
D 9
		printf("?Already connected to %s\n", host_name);
E 9
I 9
D 10
		printf("?Already connected to %s\n", host->h_name);
E 10
I 10
		printf("?Already connected to %s\n", hostname);
E 10
E 9
		return;
	}
	if (argc < 2) {
		strcpy(line, "Connect ");
		printf("(to) ");
		gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc > 3) {
		printf("usage: %s host-name [port]\n", argv[0]);
		return;
	}
D 9
	sin.sin_addr.s_addr = rhost(&argv[1]);
D 2
	if (sin.sin_addr.s_addr == 0) {
E 2
I 2
D 3
	if (sin.sin_addr.s_addr <= 0) {
E 3
I 3
	if (sin.sin_addr.s_addr == (u_long)-1) {
E 9
I 9
D 33
	host = gethostbyname(argv[1]);
D 10
	if (host == 0) {
E 9
E 3
E 2
		printf("%s: unknown host\n", argv[1]);
		return;
E 10
I 10
	if (host) {
D 12
		bcopy(host->h_addr, &sin.sin_addr, host->h_length);
E 12
I 12
		sin.sin_family = host->h_addrtype;
		bcopy(host->h_addr, (caddr_t)&sin.sin_addr, host->h_length);
E 12
		hostname = host->h_name;
	} else {
E 33
I 33
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	if (sin.sin_addr.s_addr != -1) {
E 33
I 12
		sin.sin_family = AF_INET;
E 12
D 33
		sin.sin_addr.s_addr = inet_addr(argv[1]);
		if (sin.sin_addr.s_addr == -1) {
E 33
I 33
		strcpy(hnamebuf, argv[1]);
		hostname = hnamebuf;
	} else {
		host = gethostbyname(argv[1]);
		if (host) {
			sin.sin_family = host->h_addrtype;
			bcopy(host->h_addr_list[0], (caddr_t)&sin.sin_addr,
				host->h_length);
			hostname = host->h_name;
		} else {
E 33
			printf("%s: unknown host\n", argv[1]);
			return;
E 38
I 38
	longest = 0;
	nmatches = 0;
	found = 0;
	for (c = table; p = *c; c = (*next)(c)) {
		for (q = name; *q == *p++; q++)
			if (*q == 0)		/* exact match? */
				return (c);
		if (!*q) {			/* the name was a prefix */
			if (q - name > longest) {
				longest = q - name;
				nmatches = 1;
				found = c;
			} else if (q - name == longest)
				nmatches++;
E 38
		}
D 33
		strcpy(hnamebuf, argv[1]);
		hostname = hnamebuf;
E 33
E 10
	}
I 9
D 10
	bcopy(host->h_addr, &sin.sin_addr, host->h_length);
E 10
D 38
	sin.sin_port = sp->s_port;
E 9
I 2
	if (argc == 3) {
		sin.sin_port = atoi(argv[2]);
D 32
		if (sin.sin_port < 0) {
			printf("%s: bad port number\n", argv[2]);
			return;
E 32
I 32
		if (sin.sin_port <= 0) {
			sp = getservbyname(argv[2], "tcp");
			if (sp)
				sin.sin_port = sp->s_port;
			else {
				printf("%s: bad port number\n", argv[2]);
				return;
			}
		} else {
			sin.sin_port = atoi(argv[2]);
			sin.sin_port = htons(sin.sin_port);
E 32
		}
I 14
D 32
		sin.sin_port = htons(sin.sin_port);
E 32
I 32
		telnetport = 0;
E 32
E 14
I 8
D 9
		sin.sin_port = swab(sin.sin_port);
E 9
E 8
	}
I 9
D 14
	sin.sin_port = htons(sin.sin_port);
E 14
E 9
E 2
D 8
	if ((net = socket(SOCK_STREAM, 0, 0, 0)) < 0) {
E 8
I 8
D 12
	if ((net = socket(SOCK_STREAM, 0, 0, options)) < 0) {
E 8
		perror("socket");
E 12
I 12
D 13
	net = socket(0, SOCK_STREAM, 0, 0);
E 13
I 13
D 29
	net = socket(AF_INET, SOCK_STREAM, 0, 0);
E 29
I 29
D 37
	net = socket(AF_INET, SOCK_STREAM, 0);
E 29
E 13
	if (net < 0) {
		perror("telnet: socket");
E 12
		return;
	}
I 16
D 18
	if (debug)
		if (setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
			perror("telnet: setsockopt");
E 18
I 18
D 27
	if (debug && setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
E 27
I 27
	if (debug &&
	    setsockopt(net, SOL_SOCKET, SO_DEBUG, &debug, sizeof(debug)) < 0)
E 27
		perror("setsockopt (SO_DEBUG)");
E 37
E 18
E 16
D 2
	if (argc == 3)
		sin.sin_port = atoi(argv[2]);
E 2
D 20
	sigset(SIGINT, intr);
	sigset(SIGPIPE, deadpeer);
E 20
I 20
	signal(SIGINT, intr);
	signal(SIGPIPE, deadpeer);
E 20
	printf("Trying...\n");
D 12
	if (connect(net, &sin)) {
		perror("connect");
E 12
I 12
D 29
	if (connect(net, (caddr_t)&sin, sizeof (sin), 0) < 0) {
E 29
I 29
D 33
	if (connect(net, (caddr_t)&sin, sizeof (sin)) < 0) {
E 33
I 33
D 37
	while (connect(net, (caddr_t)&sin, sizeof (sin)) < 0) {
		if (host && host->h_addr_list[1]) {
			int oerrno = errno;
E 37
I 37
	do {
		net = socket(AF_INET, SOCK_STREAM, 0);
		if (net < 0) {
			perror("telnet: socket");
			return;
		}
		if (debug && setsockopt(net, SOL_SOCKET, SO_DEBUG, &debug,
		    sizeof(debug)) < 0)
			perror("setsockopt (SO_DEBUG)");
		if (connect(net, (caddr_t)&sin, sizeof (sin)) < 0) {
			if (host && host->h_addr_list[1]) {
				int oerrno = errno;
E 37

D 37
			fprintf(stderr, "telnet: connect to address %s: ",
				inet_ntoa(sin.sin_addr));
			errno = oerrno;
			perror(0);
			host->h_addr_list++;
			bcopy(host->h_addr_list[0], (caddr_t)&sin.sin_addr,
				host->h_length);
			fprintf(stderr, "Trying %s...\n",
				inet_ntoa(sin.sin_addr));
I 36
			(void) close(net);
			net = socket(AF_INET, SOCK_STREAM, 0);
			if (net < 0) {
				perror("telnet: socket");
				return;
E 37
I 37
				fprintf(stderr,
				    "telnet: connect to address %s: ",
				    inet_ntoa(sin.sin_addr));
				errno = oerrno;
				perror(0);
				host->h_addr_list++;
				bcopy(host->h_addr_list[0],
				    (caddr_t)&sin.sin_addr, host->h_length);
				fprintf(stderr, "Trying %s...\n",
					inet_ntoa(sin.sin_addr));
				(void) close(net);
				continue;
E 37
			}
E 36
D 37
			continue;
E 37
I 37
			perror("telnet: connect");
			signal(SIGINT, SIG_DFL);
			return;
E 37
		}
E 33
E 29
D 37
		perror("telnet: connect");
E 12
D 20
		sigset(SIGINT, SIG_DFL);
E 20
I 20
		signal(SIGINT, SIG_DFL);
E 20
		return;
	}
D 9
	strcpy(host_name, argv[1]);
E 9
	connected++;
E 37
I 37
		connected++;
	} while (connected == 0);
E 37
	call(status, "status", 0);
	if (setjmp(peerdied) == 0)
		telnet(net);
	fprintf(stderr, "Connection closed by foreign host.\n");
	exit(1);
E 38
I 38
	if (nmatches > 1)
D 41
		return ((char **)-1);
E 41
I 41
		return Ambiguous(char **);
E 41
	return (found);
E 38
}

I 39
/*
 * Make a character string into a number.
 *
D 41
 * Todo:  1.  Could take random integers (123, 0x123, 0123, 0b123).
E 41
I 41
 * Todo:  1.  Could take random integers (12, 0x12, 012, 0b1).
E 41
 */
E 39
D 38
/*
 * Print status about the connection.
 */
/*VARARGS*/
status()
{
	if (connected)
D 9
		printf("Connected to %s.\n", host_name);
E 9
I 9
D 10
		printf("Connected to %s.\n", host->h_name);
E 10
I 10
		printf("Connected to %s.\n", hostname);
E 10
E 9
	else
		printf("No connection.\n");
	printf("Escape character is '%s'.\n", control(escape));
I 15
	fflush(stdout);
E 15
}
E 38

I 39
special(s)
register char *s;
{
	register char c;
	char b;

	switch (*s) {
	case '^':
		b = *++s;
		if (b == '?') {
D 42
		    c = b | 0x80;		/* DEL */
E 42
I 42
		    c = b | 0x40;		/* DEL */
E 42
		} else {
		    c = b & 0x1f;
		}
		break;
	default:
		c = *s;
		break;
	}
	return c;
}
I 41

/*
 * Construct a control character sequence
 * for a special character.
 */
char *
control(c)
	register int c;
{
	static char buf[3];

D 42
	if (c == 0x3f)
E 42
I 42
	if (c == 0x7f)
E 42
		return ("^?");
	if (c == '\377') {
		return "off";
	}
	if (c >= 0x20) {
		buf[0] = c;
		buf[1] = 0;
	} else {
		buf[0] = '^';
		buf[1] = '@'+c;
		buf[2] = 0;
	}
	return (buf);
}
I 44


/*
 * upcase()
 *
 *	Upcase (in place) the argument.
 */

void
upcase(argument)
register char *argument;
{
    register int c;

    while (c = *argument) {
	if (islower(c)) {
	    *argument = toupper(c);
	}
	argument++;
    }
}
E 44
E 41

/*
I 41
 * Check to see if any out-of-band data exists on a socket (for
 * Telnet "synch" processing).
 */

E 49
I 49
#endif	/* defined(TN3270) */
E 49
int
D 49
stilloob(s)
int	s;		/* socket number */
{
    static struct timeval timeout = { 0 };
    fd_set	excepts;
    int value;
E 49

D 49
    do {
	FD_ZERO(&excepts);
	FD_SET(s, &excepts);
	value = select(s+1, (fd_set *)0, (fd_set *)0, &excepts, &timeout);
    } while ((value == -1) && (errno = EINTR));
E 49
I 49
	tout,			/* Output file descriptor */
	tin;			/* Input file descriptor */
E 49

D 49
    if (value < 0) {
	perror("select");
	quit();
    }
    if (FD_ISSET(s, &excepts)) {
	return 1;
    } else {
	return 0;
    }
}
E 49


E 53
/*
D 49
 *  netflush
 *		Send as much data as possible to the network,
 *	handling requests for urgent data.
 */


netflush(fd)
{
    int n;

    if ((n = nfrontp - nbackp) > 0) {
	if (!neturg) {
	    n = write(fd, nbackp, n);	/* normal write */
	} else {
	    n = neturg - nbackp;
	    /*
	     * In 4.2 (and 4.3) systems, there is some question about
	     * what byte in a sendOOB operation is the "OOB" data.
	     * To make ourselves compatible, we only send ONE byte
	     * out of band, the one WE THINK should be OOB (though
	     * we really have more the TCP philosophy of urgent data
	     * rather than the Unix philosophy of OOB data).
	     */
	    if (n > 1) {
		n = send(fd, nbackp, n-1, 0);	/* send URGENT all by itself */
	    } else {
		n = send(fd, nbackp, n, MSG_OOB);	/* URGENT data */
	    }
	}
    }
    if (n < 0) {
	if (errno != ENOBUFS && errno != EWOULDBLOCK) {
	    setcommandmode();
	    perror(hostname);
	    close(fd);
	    neturg = 0;
	    longjmp(peerdied, -1);
	    /*NOTREACHED*/
	}
	n = 0;
    }
    if (netdata && n) {
	Dump('>', nbackp, n);
    }
    nbackp += n;
    if (nbackp >= neturg) {
	neturg = 0;
    }
    if (nbackp == nfrontp) {
	nbackp = nfrontp = netobuf;
    }
}
I 43

/*
 * nextitem()
 *
 *	Return the address of the next "item" in the TELNET data
 * stream.  This will be the address of the next character if
 * the current address is a user data character, or it will
 * be the address of the character following the TELNET command
 * if the current address is a TELNET IAC ("I Am a Command")
 * character.
 */
E 43

I 43
char *
nextitem(current)
char	*current;
{
    if ((*current&0xff) != IAC) {
	return current+1;
    }
    switch (*(current+1)&0xff) {
    case DO:
    case DONT:
    case WILL:
    case WONT:
	return current+3;
    case SB:		/* loop forever looking for the SE */
	{
	    register char *look = current+2;

	    for (;;) {
		if ((*look++&0xff) == IAC) {
		    if ((*look++&0xff) == SE) {
			return look;
		    }
		}
	    }
	}
    default:
	return current+2;
    }
}
E 43
/*
I 43
 * netclear()
 *
 *	We are about to do a TELNET SYNCH operation.  Clear
 * the path to the network.
 *
 *	Things are a bit tricky since we may have sent the first
 * byte or so of a previous TELNET command into the network.
 * So, we have to scan the network buffer from the beginning
 * until we are up to where we want to be.
 *
 *	A side effect of what we do, just to keep things
 * simple, is to clear the urgent data pointer.  The principal
 * caller should be setting the urgent data pointer AFTER calling
 * us in any case.
 */

netclear()
{
    register char *thisitem, *next;
    char *good;
#define	wewant(p)	((nfrontp > p) && ((*p&0xff) == IAC) && \
				((*(p+1)&0xff) != EC) && ((*(p+1)&0xff) != EL))

    thisitem = netobuf;

    while ((next = nextitem(thisitem)) <= nbackp) {
	thisitem = next;
    }

    /* Now, thisitem is first before/at boundary. */

    good = netobuf;	/* where the good bytes go */

    while (nfrontp > thisitem) {
	if (wewant(thisitem)) {
	    int length;

	    next = thisitem;
	    do {
		next = nextitem(next);
	    } while (wewant(next) && (nfrontp > next));
	    length = next-thisitem;
	    bcopy(thisitem, good, length);
	    good += length;
	    thisitem = next;
	} else {
	    thisitem = nextitem(thisitem);
	}
    }

    nbackp = netobuf;
    nfrontp = good;		/* next byte to be sent */
    neturg = 0;
}

/*
E 43
 * Send as much data as possible to the terminal.
 */


ttyflush()
{
    int n;

    if ((n = tfrontp - tbackp) > 0) {
D 42
	if (!SYNCHing) {
E 42
I 42
	if (!(SYNCHing||flushout)) {
E 42
	    n = write(tout, tbackp, n);
	} else {
	    ioctl(fileno(stdout), TIOCFLUSH, (char *) 0);
I 42
	    /* we leave 'n' alone! */
E 42
	}
    }
    if (n < 0) {
	return;
    }
    tbackp += n;
    if (tbackp == tfrontp) {
	tbackp = tfrontp = ttyobuf;
    }
}

/*
E 41
 * Various signal handling routines.
 */

deadpeer()
{
	setcommandmode();
	longjmp(peerdied, -1);
}

intr()
{
D 43
    if (localsigs) {
E 43
I 43
    if (localchars) {
E 43
	intp();
I 41
D 42
	if (autosynch) {
	    dosynch();
	}
E 42
E 41
	return;
    }
    setcommandmode();
    longjmp(toplevel, -1);
}

intr2()
{
D 43
    if (localsigs) {
E 43
I 43
    if (localchars) {
E 43
	sendbrk();
I 41
D 42
	if (autosynch) {
	    dosynch();
	}
E 42
E 41
	return;
    }
}

doescape()
{
    command(0);
}

/*
I 41
 * The following are routines used to print out debugging information.
 */


static
Dump(direction, buffer, length)
char	direction;
char	*buffer;
int	length;
{
#   define BYTES_PER_LINE	32
#   define min(x,y)	((x<y)? x:y)
    char *pThis;
    int offset;

    offset = 0;

    while (length) {
	/* print one line */
	fprintf(NetTrace, "%c 0x%x\t", direction, offset);
	pThis = buffer;
	buffer = buffer+min(length, BYTES_PER_LINE);
	while (pThis < buffer) {
	    fprintf(NetTrace, "%.2x", (*pThis)&0xff);
	    pThis++;
	}
	fprintf(NetTrace, "\n");
	length -= BYTES_PER_LINE;
	offset += BYTES_PER_LINE;
	if (length < 0) {
	    return;
	}
	/* find next unique line */
    }
}


/*VARARGS*/
printoption(direction, fmt, option, what)
	char *direction, *fmt;
	int option, what;
{
	if (!showoptions)
		return;
D 44
	printf("%s ", direction);
E 44
I 44
	printf("%s ", direction+1);
E 44
	if (fmt == doopt)
		fmt = "do";
	else if (fmt == dont)
		fmt = "dont";
	else if (fmt == will)
		fmt = "will";
	else if (fmt == wont)
		fmt = "wont";
	else
		fmt = "???";
D 44
	if (option < TELOPT_SUPDUP)
E 44
I 44
	if (option < (sizeof telopts/sizeof telopts[0]))
E 44
		printf("%s %s", fmt, telopts[option]);
	else
		printf("%s %d", fmt, option);
	if (*direction == '<') {
		printf("\r\n");
		return;
	}
	printf(" (%s)\r\n", what ? "reply" : "don't reply");
}

/*
E 41
 * Mode - set up terminal to a specific mode.
 */

E 39
D 38
makeargv()
{
	register char *cp;
	register char **argp = margv;

	margc = 0;
	for (cp = line; *cp;) {
		while (isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*argp++ = cp;
		margc += 1;
		while (*cp != '\0' && !isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*cp++ = '\0';
	}
	*argp++ = 0;
}

/*VARARGS*/
suspend()
{
	register int save;

	save = mode(0);
D 11
	kill(0, SIGTSTP);	/* get whole process group */
	mode(save);
E 11
I 11
	kill(0, SIGTSTP);
	/* reget parameters in case they were changed */
D 15
	ioctl(0, TIOCGETP, (char *)&ostbuf);
	ioctl(0, TIOCGETC, (char *)&otchars);
	ioctl(0, TIOCGETD, (char *)&odisc);
E 15
I 15
D 21
	ioctl(0, TIOCGET, (char *)&oflags);
	ioctl(0, TIOCCGET, (char *)&otc);
E 21
I 21
	ioctl(0, TIOCGETP, (char *)&ottyb);
	ioctl(0, TIOCGETC, (char *)&otc);
	ioctl(0, TIOCGLTC, (char *)&oltc);
E 21
E 15
	(void) mode(save);
E 11
}

/*VARARGS*/
bye()
{
D 18
	int how = 2;
E 18
I 11
	register char *op;
E 11

D 11
	mode(0);
E 11
I 11
	(void) mode(0);
E 11
	if (connected) {
I 12
D 15
#ifndef notdef
E 15
E 12
D 18
		ioctl(net, SIOCDONE, &how);
E 18
I 18
		shutdown(net, 2);
E 18
I 12
D 15
#endif
E 15
E 12
		printf("Connection closed.\n");
		close(net);
		connected = 0;
I 11
		/* reset his options */
		for (op = hisopts; op < &hisopts[256]; op++)
			*op = 0;
E 11
	}
}

/*VARARGS*/
quit()
{
	call(bye, "bye", 0);
	exit(0);
}

/*
 * Help command.
D 18
 * Call each command handler with argc == 0 and argv[0] == name.
E 18
 */
help(argc, argv)
	int argc;
	char *argv[];
{
	register struct cmd *c;

	if (argc == 1) {
		printf("Commands may be abbreviated.  Commands are:\n\n");
		for (c = cmdtab; c->name; c++)
D 37
			printf("%-*s\t%s\n", HELPINDENT, c->name, c->help);
E 37
I 37
			if (c->dohelp) {
				printf("%-*s\t%s\n", HELPINDENT, c->name,
								    c->help);
			}
E 37
		return;
	}
	while (--argc > 0) {
		register char *arg;
		arg = *++argv;
		c = getcmd(arg);
		if (c == (struct cmd *)-1)
			printf("?Ambiguous help command %s\n", arg);
		else if (c == (struct cmd *)0)
			printf("?Invalid help command %s\n", arg);
		else
			printf("%s\n", c->help);
	}
}

/*
 * Call routine with argc, argv set from args (terminated by 0).
 * VARARGS2
 */
call(routine, args)
	int (*routine)();
	int args;
{
	register int *argp;
	register int argc;

	for (argc = 0, argp = &args; *argp++ != 0; argc++)
		;
	(*routine)(argc, &args);
}

E 38
I 15
D 21
struct	ttychars notc = {
	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1
};
E 21
I 21
D 42
struct	tchars notc =	{ -1, -1, -1, -1, -1, -1 };
I 39
struct	tchars notc2;
E 39
struct	ltchars noltc =	{ -1, -1, -1, -1, -1, -1 };
I 39
struct	ltchars noltc2;
E 42
E 39
E 21

E 15
mode(f)
	register int f;
{
D 11
	register int old;
E 11
D 15
	struct sgttyb stbuf;
E 15
D 11
	static int ttymode = 0;
	int onoff;
E 11
I 11
	static int prevmode = 0;
D 15
	struct tchars tchars;
	int onoff, disc, old;
E 15
I 15
D 21
	struct ttychars *tc;
	int onoff, old, flags;
E 21
I 21
	struct tchars *tc;
	struct ltchars *ltc;
	struct sgttyb sb;
	int onoff, old;
I 42
	struct	tchars notc2;
	struct	ltchars noltc2;
	static struct	tchars notc =	{ -1, -1, -1, -1, -1, -1 };
	static struct	ltchars noltc =	{ -1, -1, -1, -1, -1, -1 };
E 42
E 21
E 15
E 11

I 39
	globalmode = f;
E 39
D 11
	ioctl(fileno(stdin), TIOCGETP, &stbuf);
	old = ttymode;
	ttymode = f;
E 11
I 11
	if (prevmode == f)
D 41
		return (f);
E 41
I 41
		return;
E 41
	old = prevmode;
	prevmode = f;
D 15
	stbuf = ostbuf;
	tchars = otchars;
E 15
I 15
D 21
	flags = oflags;
E 21
I 21
D 39
	sb = ottyb;
E 39
I 39
	sb = nttyb;
E 39
E 21
E 15
E 11
	switch (f) {
I 11

E 11
	case 0:
D 11
		stbuf.sg_flags &= ~RAW;
		stbuf.sg_flags |= ECHO|CRMOD;
E 11
I 11
D 15
		disc = odisc;
E 15
E 11
		onoff = 0;
I 15
		tc = &otc;
I 21
		ltc = &oltc;
E 21
E 15
		break;

D 39
	case 1:
D 11
		stbuf.sg_flags |= RAW;
		stbuf.sg_flags &= ~(ECHO|CRMOD);
		onoff = 1;
		break;

E 11
	case 2:
E 39
I 39
	case 1:		/* remote character processing, remote echo */
	case 2:		/* remote character processing, local echo */
E 39
D 11
		stbuf.sg_flags |= RAW;
		stbuf.sg_flags |= ECHO|CRMOD;
E 11
I 11
D 15
		stbuf.sg_flags |= CBREAK;
E 15
I 15
D 21
		flags |= CBREAK;
E 21
I 21
		sb.sg_flags |= CBREAK;
E 21
E 15
		if (f == 1)
D 15
			stbuf.sg_flags &= ~ECHO;
E 15
I 15
D 21
			flags &= ~(ECHO|CRMOD);
E 21
I 21
			sb.sg_flags &= ~(ECHO|CRMOD);
E 21
E 15
		else
D 15
			stbuf.sg_flags |= ECHO;
		tchars.t_intrc = tchars.t_quitc = -1;
I 12
		tchars.t_stopc = tchars.t_startc = -1;
E 12
		disc = OTTYDISC;
E 15
I 15
D 21
			flags |= ECHO|CRMOD;
E 21
I 21
			sb.sg_flags |= ECHO|CRMOD;
		sb.sg_erase = sb.sg_kill = -1;
E 21
		tc = &notc;
I 39
		/*
		 * If user hasn't specified one way or the other,
		 * then default to not trapping signals.
		 */
D 42
		if (!donelclsigs)
E 42
I 42
D 43
		if (!donelclsigs) {
E 42
			localsigs = 0;
E 43
I 43
		if (!donelclchars) {
			localchars = 0;
E 43
I 42
		}
E 42
D 43
		if (localsigs) {
E 43
I 43
		if (localchars) {
E 43
			notc2 = notc;
			notc2.t_intrc = ntc.t_intrc;
			notc2.t_quitc = ntc.t_quitc;
D 42
			notc2.t_eofc = ntc.t_eofc;
E 42
			tc = &notc2;
		} else
			tc = &notc;
E 39
I 21
		ltc = &noltc;
E 21
E 15
E 11
		onoff = 1;
I 39
D 41
		linemode = 0;
E 41
E 39
I 15
		break;
I 39
	case 3:		/* local character processing, remote echo */
	case 4:		/* local character processing, local echo */
	case 5:		/* local character processing, no echo */
		sb.sg_flags &= ~CBREAK;
		sb.sg_flags |= CRMOD;
		if (f == 4)
			sb.sg_flags |= ECHO;
		else
			sb.sg_flags &= ~ECHO;
I 42
		notc2 = ntc;
		tc = &notc2;
		noltc2 = oltc;
		ltc = &noltc2;
E 42
		/*
		 * If user hasn't specified one way or the other,
		 * then default to trapping signals.
		 */
D 42
		if (!donelclsigs)
E 42
I 42
D 43
		if (!donelclsigs) {
E 42
			localsigs = 1;
E 43
I 43
		if (!donelclchars) {
			localchars = 1;
E 43
D 42
		if (localsigs)
			tc = &ntc;
		else {
			notc2 = ntc;
E 42
I 42
		}
D 43
		if (localsigs) {
E 43
I 43
		if (localchars) {
E 43
			notc2.t_brkc = nltc.t_flushc;
			noltc2.t_flushc = -1;
		} else {
E 42
			notc2.t_intrc = notc2.t_quitc = -1;
D 42
			tc = &notc2;
E 42
		}
D 42
		noltc2 = oltc;
E 42
		noltc2.t_suspc = escape;
		noltc2.t_dsuspc = -1;
D 42
		ltc = &noltc2;
E 42
		onoff = 1;
D 41
		linemode = 1;
E 41
		break;
E 39

	default:
		return;
E 15
	}
I 11
D 15
	ioctl(fileno(stdin), TIOCSETD, &disc);
	ioctl(fileno(stdin), TIOCSETC, &tchars);
E 11
	ioctl(fileno(stdin), TIOCSETN, &stbuf);
E 15
I 15
D 21
	ioctl(fileno(stdin), TIOCCSET, (char *)tc);
	ioctl(fileno(stdin), TIOCSET, (char *)&flags);
E 21
I 21
	ioctl(fileno(stdin), TIOCSLTC, (char *)ltc);
	ioctl(fileno(stdin), TIOCSETC, (char *)tc);
	ioctl(fileno(stdin), TIOCSETP, (char *)&sb);
E 21
E 15
D 41
	ioctl(fileno(stdin), FIONBIO, &onoff);
	ioctl(fileno(stdout), FIONBIO, &onoff);
E 41
I 41
	ioctl(fileno(stdin), FIONBIO, (char *)&onoff);
	ioctl(fileno(stdout), FIONBIO, (char *)&onoff);
E 41
I 39
	if (f >= 3)
		signal(SIGTSTP, doescape);
	else if (old >= 3) {
		signal(SIGTSTP, SIG_DFL);
		sigsetmask(sigblock(0) & ~(1<<(SIGTSTP-1)));
	}
E 39
D 41
	return (old);
E 41
}
D 41

E 41
I 41

E 41
I 39
/*
 * These routines decides on what the mode should be (based on the values
 * of various global variables).
 */

D 40
setconnmode()
E 40
I 40
char *modedescriptions[] = {
	"telnet command mode",					/* 0 */
	"character-at-a-time mode",				/* 1 */
	"character-at-a-time mode (local echo)",		/* 2 */
	"line-by-line mode (remote echo)",			/* 3 */
	"line-by-line mode",					/* 4 */
	"line-by-line mode (local echoing suppressed)",		/* 5 */
};

getconnmode()
E 40
{
    static char newmode[8] = { 4, 5, 3, 3, 2, 2, 1, 1 };
D 41
    int index = 0;
E 41
I 41
    int modeindex = 0;
E 41

    if (hisopts[TELOPT_ECHO]) {
D 41
	index += 2;
E 41
I 41
	modeindex += 2;
E 41
    }
    if (hisopts[TELOPT_SGA]) {
D 41
	index += 4;
E 41
I 41
	modeindex += 4;
E 41
    }
D 41
    if (dontlecho && (times.echotoggle > times.modenegotiated)) {
	index += 1;
E 41
I 41
    if (dontlecho && (clocks.echotoggle > clocks.modenegotiated)) {
	modeindex += 1;
E 41
    }
D 40
    mode(newmode[index]);
E 40
I 40
D 41
    return newmode[index];
E 41
I 41
    return newmode[modeindex];
E 41
E 40
}

I 40
setconnmode()
{
    mode(getconnmode());
}
E 40

I 40

E 40
setcommandmode()
{
    mode(0);
}

E 39
char	sibuf[BUFSIZ], *sbp;
char	tibuf[BUFSIZ], *tbp;
int	scc, tcc;

I 42

E 42
/*
 * Select from tty and network...
 */
D 38
telnet(s)
	int s;
E 38
I 38
telnet()
E 38
{
	register int c;
D 38
	int tin = fileno(stdin), tout = fileno(stdout);
E 38
I 38
	int tin = fileno(stdin);
E 38
	int on = 1;
I 43
	fd_set ibits, obits, xbits;
E 43

I 38
	tout = fileno(stdout);
E 38
D 11
	mode(1);
I 2
D 9
	if (showoptions)
		printoption("<--", doopt, TELOPT_ECHO);
E 9
I 9
	printoption("SENT", doopt, TELOPT_ECHO);
E 9
E 2
	sprintf(nfrontp, doopt, TELOPT_ECHO);
	nfrontp += sizeof(doopt) - 2;
I 6
	hisopts[TELOPT_ECHO] = 1;
E 6
I 2
D 9
	if (showoptions)
		printoption("<--", doopt, TELOPT_SGA);
E 9
I 9
	printoption("SENT", doopt, TELOPT_SGA);
E 9
E 2
	sprintf(nfrontp, doopt, TELOPT_SGA);
	nfrontp += sizeof(doopt) - 2;
I 6
	hisopts[TELOPT_SGA] = 1;
E 6
I 2
D 9
	if (showoptions)
		printoption("<--", will, TELOPT_SGA);
E 9
I 9
	printoption("SENT", will, TELOPT_SGA);
E 9
E 2
	sprintf(nfrontp, will, TELOPT_SGA);
	nfrontp += sizeof(doopt) - 2;
I 6
	myopts[TELOPT_SGA] = 1;
E 11
I 11
D 39
	(void) mode(2);
E 39
I 39
	setconnmode();
I 42
	scc = 0;
	tcc = 0;
I 43
	FD_ZERO(&ibits);
	FD_ZERO(&obits);
	FD_ZERO(&xbits);

E 43
E 42
E 39
E 11
E 6
D 38
	ioctl(s, FIONBIO, &on);
I 29
D 32
	if (!hisopts[TELOPT_SGA])
E 32
I 32
	if (telnetport && !hisopts[TELOPT_SGA])
E 38
I 38
D 41
	ioctl(net, FIONBIO, &on);
E 41
I 41
	ioctl(net, FIONBIO, (char *)&on);
E 41
I 40
D 42
#if	defined(IOCTL_TO_DO_UNIX_OOB_IN_TCP_WAY)
	ioctl(net, asdf, asdf);		/* handle urgent data in band */
#endif	/* defined(IOCTL_TO_DO_UNIX_OOB_IN_TCP_WAY) */
E 42
I 42
D 44
#if	defined(xxxSO_OOBINLINE)
	setsockopt(net, SOL_SOCKET, SO_OOBINLINE, on, sizeof on);
#endif	/* defined(xxxSO_OOBINLINE) */
E 42
E 40
	if (telnetport && !hisopts[TELOPT_SGA]) {
E 38
E 32
		willoption(TELOPT_SGA);
E 44
I 44
#if	defined(SO_OOBINLINE)
	setsockopt(net, SOL_SOCKET, SO_OOBINLINE, &on, sizeof on);
#endif	/* defined(SO_OOBINLINE) */
	if (telnetport) {
	    if (!hisopts[TELOPT_SGA]) {
		willoption(TELOPT_SGA, 0);
	    }
	    if (!myopts[TELOPT_TTYPE]) {
		dooption(TELOPT_TTYPE, 0);
	    }
E 44
I 38
	}
E 38
E 29
	for (;;) {
D 38
		int ibits = 0, obits = 0;
E 38
I 38
D 39
		long ibits = 0, obits = 0, xbits = 0;
E 39
I 39
D 43
		fd_set ibits, obits, xbits;
E 39
E 38

E 43
D 39
		if (nfrontp - nbackp)
D 38
			obits |= (1 << s);
E 38
I 38
			obits |= (1 << net);
E 38
		else
			ibits |= (1 << tin);
		if (tfrontp - tbackp)
			obits |= (1 << tout);
		else
D 38
			ibits |= (1 << s);
E 38
I 38
			ibits |= (1 << net);
E 38
		if (scc < 0 && tcc < 0)
E 39
I 39
		if (scc < 0 && tcc < 0) {
E 39
			break;
D 12
		select(32, &ibits, &obits, INFINITY);
E 12
I 12
D 38
		select(16, &ibits, &obits, 0, 0);
E 12
		if (ibits == 0 && obits == 0) {
E 38
I 38
D 39
		if (flushing) {
			xbits = 0;
E 39
I 39
		}

D 43
		FD_ZERO(&ibits);
		FD_ZERO(&obits);
		FD_ZERO(&xbits);

E 43
D 42
		if (((globalmode < 4) || flushline) && (nfrontp - nbackp)) {
E 42
I 42
		if (((globalmode < 4) || flushline) && NETBYTES()) {
E 42
			FD_SET(net, &obits);
E 39
		} else {
D 39
			xbits = (1 << net);
E 39
I 39
			FD_SET(tin, &ibits);
E 39
		}
D 39
		select(16, &ibits, &obits, &xbits, 0);
		if (ibits == 0 && obits == 0 && xbits == 0) {
E 39
I 39
D 42
		if (tfrontp - tbackp) {
E 42
I 42
		if (TTYBYTES()) {
E 42
			FD_SET(tout, &obits);
		} else {
			FD_SET(net, &ibits);
		}
D 41
		if (!flushing) {
E 41
I 41
		if (!SYNCHing) {
E 41
			FD_SET(net, &xbits);
		}
D 41
		if ((c = select(16, &ibits, &obits, &xbits, 0)) < 1) {
E 41
I 41
		if ((c = select(16, &ibits, &obits, &xbits,
						(struct timeval *)0)) < 1) {
E 41
			if (c == -1) {
				/*
				 * we can get EINTR if we are in line mode,
				 * and the user does an escape (TSTP), or
				 * some other signal generator.
				 */
				if (errno == EINTR) {
					continue;
				}
			}
E 39
E 38
			sleep(5);
			continue;
		}

		/*
I 38
		 * Any urgent data?
		 */
D 39
		if (xbits) {
E 39
I 39
		if (FD_ISSET(net, &xbits)) {
I 43
		    FD_CLR(net, &xbits);
E 43
E 39
D 41
		    flushing = 1;
E 41
I 41
		    SYNCHing = 1;
E 41
		    ttyflush();	/* flush already enqueued data */
		}

		/*
E 38
		 * Something to read from the network...
		 */
D 38
		if (ibits & (1 << s)) {
D 11
			scc = read(s, sibuf, sizeof(sibuf));
E 11
I 11
			scc = read(s, sibuf, sizeof (sibuf));
E 38
I 38
D 39
		if (ibits & (1 << net)) {
E 39
I 39
		if (FD_ISSET(net, &ibits)) {
E 39
D 40
			scc = read(net, sibuf, sizeof (sibuf));
E 38
E 11
			if (scc < 0 && errno == EWOULDBLOCK)
				scc = 0;
			else {
				if (scc <= 0)
					break;
				sbp = sibuf;
I 37
D 38
				if (printnet) {
E 38
I 38
				if (netdata) {
E 38
					Dump('<', sbp, scc);
E 40
I 40
D 42
#if	!defined(IOCTL_TO_DO_UNIX_OOB_IN_TCP_WAY)
E 42
I 42
			int canread;

I 43
			FD_CLR(net, &ibits);
E 43
			if (scc == 0) {
			    sbp = sibuf;
			}
			canread = sibuf + sizeof sibuf - sbp;
D 44
#if	!defined(xxxSO_OOBINLINE)
E 44
I 44
#if	!defined(SO_OOBINLINE)
E 44
E 42
			/*
			 * In 4.2 (and some early 4.3) systems, the
			 * OOB indication and data handling in the kernel
			 * is such that if two separate TCP Urgent requests
			 * come in, one byte of TCP data will be overlaid.
			 * This is fatal for Telnet, but we try to live
			 * with it.
			 *
			 * In addition, in 4.2 (and...), a special protocol
			 * is needed to pick up the TCP Urgent data in
			 * the correct sequence.
			 *
			 * What we do is:  if we think we are in urgent
			 * mode, we look to see if we are "at the mark".
			 * If we are, we do an OOB receive.  If we run
			 * this twice, we will do the OOB receive twice,
			 * but the second will fail, since the second
			 * time we were "at the mark", but there wasn't
			 * any data there (the kernel doesn't reset
			 * "at the mark" until we do a normal read).
			 * Once we've read the OOB data, we go ahead
			 * and do normal reads.
			 *
			 * There is also another problem, which is that
			 * since the OOB byte we read doesn't put us
			 * out of OOB state, and since that byte is most
			 * likely the TELNET DM (data mark), we would
D 41
			 * stay in the TELNET SYNCH (flushing) state.
E 41
I 41
			 * stay in the TELNET SYNCH (SYNCHing) state.
E 41
			 * So, clocks to the rescue.  If we've "just"
			 * received a DM, then we test for the
			 * presence of OOB data when the receive OOB
			 * fails (and AFTER we did the normal mode read
			 * to clear "at the mark").
			 */
D 41
		    if (flushing) {
E 41
I 41
		    if (SYNCHing) {
E 41
			int atmark;

D 41
			ioctl(net, SIOCATMARK, &atmark);
E 41
I 41
			ioctl(net, SIOCATMARK, (char *)&atmark);
E 41
			if (atmark) {
D 42
			    scc = recv(net, sibuf, sizeof (sibuf), MSG_OOB);
			    if ((scc == -1) && (errno == EINVAL)) {
				scc = read(net, sibuf, sizeof (sibuf));
E 42
I 42
			    c = recv(net, sibuf, canread, MSG_OOB);
			    if ((c == -1) && (errno == EINVAL)) {
				c = read(net, sibuf, canread);
E 42
D 41
				if (times.didnetreceive < times.gotDM) {
				    flushing = stilloob();
E 41
I 41
				if (clocks.didnetreceive < clocks.gotDM) {
				    SYNCHing = stilloob(net);
E 41
E 40
				}
I 40
			    }
			} else {
D 42
			    scc = read(net, sibuf, sizeof (sibuf));
E 42
I 42
			    c = read(net, sibuf, canread);
E 42
E 40
E 37
			}
I 40
		    } else {
D 42
			scc = read(net, sibuf, sizeof (sibuf));
E 42
I 42
			c = read(net, sibuf, canread);
E 42
		    }
		    settimer(didnetreceive);
D 42
#else	/* !defined(IOCTL_TO_DO_UNIX_OOB_IN_TCP_WAY) */
		    scc = read(net, sibuf, sizeof (sibuf));
#endif	/* !defined(IOCTL_TO_DO_UNIX_OOB_IN_TCP_WAY) */
		    if (scc < 0 && errno == EWOULDBLOCK)
			scc = 0;
		    else {
			if (scc <= 0) {
			    break;
			}
			sbp = sibuf;
			if (netdata) {
			    Dump('<', sbp, scc);
			}
E 42
I 42
D 44
#else	/* !defined(xxxSO_OOBINLINE) */
E 44
I 44
#else	/* !defined(SO_OOBINLINE) */
E 44
		    c = read(net, sbp, canread);
D 44
#endif	/* !defined(xxxSO_OOBINLINE) */
E 44
I 44
#endif	/* !defined(SO_OOBINLINE) */
E 44
		    if (c < 0 && errno == EWOULDBLOCK) {
			c = 0;
		    } else if (c <= 0) {
			break;
E 42
		    }
I 42
		    if (netdata) {
			Dump('<', sbp, c);
		    }
		    scc += c;
E 42
E 40
		}

		/*
		 * Something to read from the tty...
		 */
D 39
		if (ibits & (1 << tin)) {
E 39
I 39
		if (FD_ISSET(tin, &ibits)) {
I 43
			FD_CLR(tin, &ibits);
E 43
E 39
D 11
			tcc = read(tin, tibuf, sizeof(tibuf));
E 11
I 11
D 42
			tcc = read(tin, tibuf, sizeof (tibuf));
E 11
			if (tcc < 0 && errno == EWOULDBLOCK)
				tcc = 0;
			else {
				if (tcc <= 0)
					break;
				tbp = tibuf;
E 42
I 42
			if (tcc == 0) {
			    tbp = tibuf;	/* nothing left, reset */
E 42
			}
I 42
			c = read(tin, tbp, tibuf+sizeof tibuf - tbp);
			if (c < 0 && errno == EWOULDBLOCK) {
				c = 0;
D 44
			} else if (c <= 0) {
				tcc = c;
				break;
E 44
I 44
			} else {
				/* EOF detection for line mode!!!! */
				if (c == 0 && globalmode >= 3) {
					/* must be an EOF... */
					*tbp = ntc.t_eofc;
					c = 1;
				}
				if (c <= 0) {
					tcc = c;
					break;
				}
E 44
			}
			tcc += c;
E 42
		}

		while (tcc > 0) {
D 41
			register int c;
E 41
I 41
			register int sc;
E 41

D 39
			if ((&netobuf[BUFSIZ] - nfrontp) < 2)
E 39
I 39
D 42
			if ((&netobuf[BUFSIZ] - nfrontp) < 2) {
E 42
I 42
			if (NETROOM() < 2) {
E 42
				flushline = 1;
E 39
				break;
I 39
			}
E 39
D 41
			c = *tbp++ & 0377, tcc--;
			if (strip(c) == escape) {
E 41
I 41
			c = *tbp++ & 0xff, sc = strip(c), tcc--;
			if (sc == escape) {
E 41
				command(0);
				tcc = 0;
I 39
				flushline = 1;
E 39
				break;
I 39
D 43
			} else if ((globalmode >= 4) && doechocharrecognition &&
D 41
							(strip(c) == echoc)) {
E 41
I 41
							(sc == echoc)) {
E 43
I 43
			} else if ((globalmode >= 4) && (sc == echoc)) {
E 43
E 41
				if (tcc > 0 && strip(*tbp) == echoc) {
					tbp++;
					tcc--;
				} else {
					dontlecho = !dontlecho;
					settimer(echotoggle);
					setconnmode();
					tcc = 0;
					flushline = 1;
					break;
				}
E 39
			}
I 39
D 43
			if (localsigs) {
E 43
I 43
			if (localchars) {
E 43
D 41
				if (c == ntc.t_intrc) {
E 41
I 41
				if (sc == ntc.t_intrc) {
E 41
					intp();
					break;
D 41
				} else if (c == ntc.t_quitc) {
E 41
I 41
				} else if (sc == ntc.t_quitc) {
E 41
					sendbrk();
					break;
I 42
				} else if (sc == nltc.t_flushc) {
					NET2ADD(IAC, AO);
					if (autoflush) {
					    doflush();
					}
					break;
E 42
				} else if (globalmode > 2) {
					;
D 41
				} else if (c == nttyb.sg_kill) {
E 41
I 41
				} else if (sc == nttyb.sg_kill) {
E 41
					NET2ADD(IAC, EL);
					break;
D 41
				} else if (c == nttyb.sg_erase) {
E 41
I 41
				} else if (sc == nttyb.sg_erase) {
E 41
					NET2ADD(IAC, EC);
					break;
				}
			}
E 39
I 18
D 29
			if (c == IAC)
				*nfrontp++ = c;
E 18
			*nfrontp++ = c;
I 28
			if (c == '\r')
E 29
I 29
			switch (c) {
I 37
D 39
			case '\n'|0x80:
E 39
E 37
			case '\n':
I 37
				/*
D 47
				 * If echoing is happening locally,
				 * then a newline (unix) is CRLF (TELNET).
E 47
I 47
				 * If we are in CRMOD mode (\r ==> \n)
				 * on our local machine, then probably
				 * a newline (unix) is CRLF (TELNET).
E 47
				 */
E 37
D 38
				if (!hisopts[TELOPT_ECHO])
					*nfrontp++ = '\r';
E 29
				*nfrontp++ = '\n';
E 38
I 38
D 47
				if (!hisopts[TELOPT_ECHO]) {
E 47
I 47
				if (globalmode >= 3) {
E 47
					NETADD('\r');
				}
				NETADD('\n');
I 39
				flushline = 1;
E 39
E 38
I 29
				break;
I 37
D 39
			case '\r'|0x80:
E 39
E 37
			case '\r':
D 38
				*nfrontp++ = '\r';
D 37
				if (hisopts[TELOPT_ECHO])
					*nfrontp++ = '\n';
				else
					*nfrontp++ = '\0';
E 37
I 37
				*nfrontp++ = '\0';
E 38
I 38
				NET2ADD('\r', '\0');
I 39
				flushline = 1;
E 39
E 38
E 37
				break;
			case IAC:
D 38
				*nfrontp++ = IAC;
D 37
				/* fall into ... */
E 37
I 37
				*nfrontp++ = IAC;
E 38
I 38
				NET2ADD(IAC, IAC);
E 38
				break;
E 37
			default:
D 38
				*nfrontp++ = c;
E 38
I 38
				NETADD(c);
E 38
				break;
			}
E 29
E 28
		}
D 38
		if ((obits & (1 << s)) && (nfrontp - nbackp) > 0)
			netflush(s);
E 38
I 38
D 39
		if ((obits & (1 << net)) && (nfrontp - nbackp) > 0)
E 39
I 39
		if (((globalmode < 4) || flushline) &&
D 42
		    (FD_ISSET(net, &obits) && (nfrontp - nbackp) > 0)) {
E 42
I 42
		    FD_ISSET(net, &obits) && (NETBYTES() > 0)) {
I 43
			FD_CLR(net, &obits);
E 43
E 42
E 39
			netflush(net);
I 39
		}
E 39
E 38
		if (scc > 0)
			telrcv();
D 39
		if ((obits & (1 << tout)) && (tfrontp - tbackp) > 0)
E 39
I 39
D 42
		if (FD_ISSET(tout, &obits) && (tfrontp - tbackp) > 0)
E 42
I 42
D 43
		if (FD_ISSET(tout, &obits) && (TTYBYTES() > 0))
E 43
I 43
		if (FD_ISSET(tout, &obits) && (TTYBYTES() > 0)) {
			FD_CLR(tout, &obits);
E 43
E 42
E 39
D 38
			ttyflush(tout);
E 38
I 38
			ttyflush();
I 43
		}
E 43
E 38
	}
D 11
	mode(0);
E 11
I 11
D 39
	(void) mode(0);
E 39
I 39
	setcommandmode();
E 39
E 11
}
D 39

E 39
I 39

E 39
D 38
command(top)
	int top;
{
	register struct cmd *c;
	int oldmode, wasopen;

	oldmode = mode(0);
	if (!top)
		putchar('\n');
	else
D 20
		sigset(SIGINT, SIG_DFL);
E 20
I 20
		signal(SIGINT, SIG_DFL);
E 20
	for (;;) {
		printf("%s> ", prompt);
D 25
		if (gets(line) == 0)
E 25
I 25
		if (gets(line) == 0) {
D 34
			if (feof(stdin)) {
				clearerr(stdin);
				putchar('\n');
			}
E 34
I 34
			if (feof(stdin))
				quit();
E 34
E 25
			break;
I 25
		}
E 25
		if (line[0] == 0)
			break;
		makeargv();
		c = getcmd(margv[0]);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == 0) {
			printf("?Invalid command\n");
			continue;
		}
		(*c->handler)(margc, margv);
		if (c->handler != help)
			break;
	}
	if (!top) {
		if (!connected)
			longjmp(toplevel, 1);
D 11
		mode(oldmode);
E 11
I 11
		(void) mode(oldmode);
E 11
	}
}

E 38
/*
E 49
 * Telnet receiver states for fsm
 */
#define	TS_DATA		0
#define	TS_IAC		1
#define	TS_WILL		2
#define	TS_WONT		3
#define	TS_DO		4
#define	TS_DONT		5
I 37
#define	TS_CR		6
I 44
#define	TS_SB		7		/* sub-option collection */
#define	TS_SE		8		/* looking for sub-option end */
E 44
E 37

D 49
telrcv()
{
	register int c;
	static int state = TS_DATA;
E 49
I 49
static int	telrcv_state;
I 90
#ifdef	OLD_ENVIRON
unsigned char telopt_environ = TELOPT_NEW_ENVIRON;
#else
# define telopt_environ TELOPT_NEW_ENVIRON
#endif
E 90
E 49

I 65
D 66
/*
 * This is all for our adaptive algorithm for dealing with
 * hosts which send CR with no following character.
 * We start off not knowing whether our peer does CR
 * legallly.  If our first isolated CR comes, we pretend
 * our peer does it wrong.  After this, we know that the
 * peer does it right ("yes") or wrong ("no").
 *
 * If our peer does it right, then we don't second-guess isolated
 * CR's (ie: we wait for the next character, even if it is in another
 * buffer).
 *
 * If our peer does it wrong, we pretend that the CR is followed
 * by whatever followed the last CR (XXX last isolated CR?).
 *
 * If our peer EVER does it wrong (isolated or not), we declare
 * our peer to be a wrong-doer (even if after that our peer
 * does it right for the rest of eternity [or this connection]).
 */

static enum	{ unknown, yes, no } peer_does_legal_CR;
static enum	{ didnt_guess, already_guessed } CR_substate;
static char	last_legal_CR_followed_by;

E 66
E 65
D 42
	while (scc > 0) {
E 42
I 42
D 49
	while ((scc > 0) && (TTYROOM() > 2)) {
E 42
D 41
		c = *sbp++ & 0377, scc--;
E 41
I 41
		c = *sbp++ & 0xff, scc--;
E 41
		switch (state) {
E 49
I 49
jmp_buf	toplevel = { 0 };
jmp_buf	peerdied;
E 49

I 37
D 49
		case TS_CR:
			state = TS_DATA;
D 42
			if ((c == '\0') || (c == '\n')) {
			    break;	/* by now, we ignore \n */
E 42
I 42
			if (c == '\0') {
			    break;	/* Ignore \0 after CR */
			} else if (c == '\n') {
			    if (hisopts[TELOPT_ECHO] && !crmod) {
				TTYADD(c);
			    }
			    break;
E 42
			}
I 42
			/* Else, fall through */
E 49
I 49
int	flushline;
I 73
int	linemode;
E 73
E 49
E 42

I 72
#ifdef	KLUDGELINEMODE
int	kludgelinemode = 1;
#endif

E 72
E 37
D 49
		case TS_DATA:
D 15
			if (c == IAC)
E 15
I 15
			if (c == IAC) {
E 15
				state = TS_IAC;
D 15
			else
				*tfrontp++ = c;
E 15
I 15
				continue;
			}
I 42
			    /*
			     * The 'crmod' hack (see following) is needed
			     * since we can't * set CRMOD on output only.
			     * Machines like MULTICS like to send \r without
			     * \n; since we must turn off CRMOD to get proper
			     * input, the mapping is done here (sigh).
			     */
E 42
D 37
			*tfrontp++ = c;
			/*
			 * This hack is needed since we can't set
			 * CRMOD on output only.  Machines like MULTICS
			 * like to send \r without \n; since we must
			 * turn off CRMOD to get proper input, the mapping
			 * is done here (sigh).
			 */
			if (c == '\r' && crmod)
				*tfrontp++ = '\n';
E 37
I 37
			if (c == '\r') {
				if (scc > 0) {
D 41
					c = *sbp&0377;
E 41
I 41
					c = *sbp&0xff;
E 41
					if (c == 0) {
						sbp++, scc--;
I 42
						/* a "true" CR */
E 42
D 38
						*tfrontp++ = '\r';
E 38
I 38
						TTYADD('\r');
E 38
D 42
				/*
				 * The following hack is needed since we can't
				 * set CRMOD on output only.  Machines like
				 * MULTICS like to send \r without \n; since
				 * we must turn off CRMOD to get proper input,
				 * the mapping is done here (sigh).
				 */
						if (crmod) {
D 38
							*tfrontp++ = '\n';
E 38
I 38
							TTYADD('\n');
E 38
						}
E 42
					} else if (!hisopts[TELOPT_ECHO] &&
								(c == '\n')) {
						sbp++, scc--;
D 38
						*tfrontp++ = '\n';
E 38
I 38
						TTYADD('\n');
E 38
					} else {
D 38
						*tfrontp++ = '\r';
E 38
I 38
						TTYADD('\r');
I 42
						if (crmod) {
							TTYADD('\n');
						}
E 42
E 38
					}
				} else {
					state = TS_CR;
D 38
					*tfrontp++ = '\r';
E 38
I 38
					TTYADD('\r');
I 42
					if (crmod) {
						TTYADD('\n');
					}
E 42
E 38
				}
			} else {
D 38
				*tfrontp++ = c;
E 38
I 38
				TTYADD(c);
E 38
			}
E 37
E 15
			continue;
E 49
I 49
/*
 * The following are some clocks used to decide how to interpret
 * the relationship between various variables.
 */
E 49

D 49
		case TS_IAC:
			switch (c) {
			
			case WILL:
				state = TS_WILL;
				continue;
E 49
I 49
Clocks clocks;

I 72
#ifdef	notdef
E 72
Modelist modelist[] = {
	{ "telnet command mode", COMMAND_LINE },
	{ "character-at-a-time mode", 0 },
	{ "character-at-a-time mode (local echo)", LOCAL_ECHO|LOCAL_CHARS },
	{ "line-by-line mode (remote echo)", LINE | LOCAL_CHARS },
	{ "line-by-line mode", LINE | LOCAL_ECHO | LOCAL_CHARS },
	{ "line-by-line mode (local echoing suppressed)", LINE | LOCAL_CHARS },
	{ "3270 mode", 0 },
};
I 72
#endif
E 72
E 49

D 49
			case WONT:
				state = TS_WONT;
				continue;
E 49
I 49

/*
 * Initialize telnet environment.
 */
E 49

I 83
    void
E 83
D 49
			case DO:
				state = TS_DO;
				continue;
E 49
I 49
init_telnet()
{
I 81
    env_init();

E 81
D 57
    /* Don't change telnetport */
E 57
    SB_CLEAR();
D 71
    ClearArray(hisopts);
    ClearArray(myopts);
E 71
I 71
    ClearArray(options);
E 71
D 51
    sbp = sibuf;
    tbp = tibuf;
E 51
I 51
D 53
    ring_init(&netiring, netibuf, sizeof netibuf);
    ring_init(&ttyiring, ttyibuf, sizeof ttyibuf);
E 53
E 51
E 49

D 49
			case DONT:
				state = TS_DONT;
				continue;
E 49
I 49
D 51
    connected = net = scc = tcc = In3270 = ISend = donebinarytoggle = 0;
E 51
I 51
D 54
    connected = net = In3270 = ISend = donebinarytoggle = 0;
E 54
I 54
D 70
    connected = In3270 = ISend = donebinarytoggle = 0;
E 70
I 70
    connected = In3270 = ISend = localflow = donebinarytoggle = 0;
I 83
D 85
#if	defined(ENCRYPT) || defined(AUTHENTICATE)
E 85
I 85
D 88
#if	defined(ENCRYPTION) || defined(AUTHENTICATION)
E 88
I 88
D 92
#if	defined(AUTHENTICATION) || defined(ENCRYPTION) 
E 92
I 92
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
E 92
E 88
E 85
    auth_encrypt_connect(connected);
D 88
#endif
E 88
I 88
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION)  */
E 88
I 85
    restartany = -1;
E 85
E 83
E 70
E 54
E 51
D 57
    telnetport = 0;
E 57
E 49
D 67

D 49
			case DM:
D 38
				ioctl(fileno(stdout), TIOCFLUSH, 0);
E 38
I 38
				/*
				 * We may have missed an urgent notification,
				 * so make sure we flush whatever is in the
				 * buffer currently.
				 */
D 41
				flushing = 1;
E 41
I 41
				SYNCHing = 1;
E 41
				ttyflush();
D 41
				flushing = stilloob(net);
E 41
I 41
				SYNCHing = stilloob(net);
E 41
I 40
				settimer(gotDM);
E 40
E 38
				break;
E 49
I 49
#if	defined(unix) && defined(TN3270)
    HaveInput = 0;
#endif	/* defined(unix) && defined(TN3270) */
E 67
E 49

D 49
			case NOP:
			case GA:
				break;
E 49
I 49
    SYNCHing = 0;
E 49

I 44
D 49
			case SB:
				SB_CLEAR();
				state = TS_SB;
				continue;
E 49
I 49
D 53
    errno = 0;
E 49

E 53
E 44
D 49
			default:
				break;
			}
			state = TS_DATA;
			continue;
E 49
I 49
    /* Don't change NetTrace */
E 49

D 49
		case TS_WILL:
I 2
D 9
			if (showoptions)
D 5
				printoption("-->", will, c);
E 5
I 5
				printoption("-->", will, c, !hisopts[c]);
E 9
I 9
D 44
			printoption("RCVD", will, c, !hisopts[c]);
E 44
I 44
			printoption(">RCVD", will, c, !hisopts[c]);
E 44
E 9
E 5
E 2
D 39
			if (!hisopts[c])
E 39
I 39
			if (c == TELOPT_TM) {
				if (flushout) {
D 41
					flushout = 1;
E 41
I 41
					flushout = 0;
E 41
				}
			} else if (!hisopts[c]) {
E 39
D 44
				willoption(c);
E 44
I 44
				willoption(c, 1);
E 44
I 39
			}
E 39
			state = TS_DATA;
			continue;
E 49
I 49
    escape = CONTROL(']');
I 83
    rlogin = _POSIX_VDISABLE;
E 83
I 81
#ifdef	KLUDGELINEMODE
E 81
    echoc = CONTROL('E');
I 81
#endif
E 81
E 49

D 49
		case TS_WONT:
I 2
D 9
			if (showoptions)
D 5
				printoption("-->", wont, c);
E 5
I 5
				printoption("-->", wont, c, hisopts[c]);
E 9
I 9
D 44
			printoption("RCVD", wont, c, hisopts[c]);
E 44
I 44
			printoption(">RCVD", wont, c, hisopts[c]);
E 44
E 9
E 5
E 2
D 39
			if (hisopts[c])
E 39
I 39
			if (c == TELOPT_TM) {
				if (flushout) {
D 41
					flushout = 1;
E 41
I 41
					flushout = 0;
E 41
				}
			} else if (hisopts[c]) {
E 39
D 44
				wontoption(c);
E 44
I 44
				wontoption(c, 1);
E 44
I 39
			}
E 39
			state = TS_DATA;
			continue;
E 49
I 49
    flushline = 1;
    telrcv_state = TS_DATA;
I 65
D 66
    peer_does_legal_CR = unknown;
    last_legal_CR_followed_by = 0;
E 66
E 65
}
I 54

E 54
E 49

I 81
#ifdef	notdef
E 81
I 54
#include <varargs.h>
E 54
D 49
		case TS_DO:
I 2
D 9
			if (showoptions)
D 5
				printoption("-->", doopt, c);
E 5
I 5
				printoption("-->", doopt, c, !myopts[c]);
E 9
I 9
D 44
			printoption("RCVD", doopt, c, !myopts[c]);
E 44
I 44
			printoption(">RCVD", doopt, c, !myopts[c]);
E 44
E 9
E 5
E 2
			if (!myopts[c])
				dooption(c);
			state = TS_DATA;
			continue;
E 49

I 63
D 83
/*VARARGS*/
E 63
I 54
static void
E 83
I 83
    /*VARARGS*/
    static void
E 83
printring(va_alist)
D 83
va_dcl
E 83
I 83
    va_dcl
E 83
{
    va_list ap;
    char buffer[100];		/* where things go */
    char *ptr;
    char *format;
    char *string;
    Ring *ring;
    int i;

    va_start(ap);

    ring = va_arg(ap, Ring *);
    format = va_arg(ap, char *);
    ptr = buffer;

    while ((i = *format++) != 0) {
	if (i == '%') {
	    i = *format++;
	    switch (i) {
	    case 'c':
		*ptr++ = va_arg(ap, int);
		break;
	    case 's':
		string = va_arg(ap, char *);
		ring_supply_data(ring, buffer, ptr-buffer);
		ring_supply_data(ring, string, strlen(string));
		ptr = buffer;
		break;
	    case 0:
		ExitString("printring: trailing %%.\n", 1);
		/*NOTREACHED*/
	    default:
		ExitString("printring: unknown format character.\n", 1);
		/*NOTREACHED*/
	    }
	} else {
	    *ptr++ = i;
	}
    }
    ring_supply_data(ring, buffer, ptr-buffer);
}
I 81
#endif
E 81

I 71
/*
 * These routines are in charge of sending option negotiations
 * to the other side.
 *
 * The basic idea is that we send the negotiation if either side
 * is in disagreement as to what the current state should be.
 */
E 71

I 83
    void
E 83
E 54
D 49
		case TS_DONT:
I 2
D 9
			if (showoptions)
D 5
				printoption("-->", dont, c);
E 5
I 5
				printoption("-->", dont, c, myopts[c]);
E 9
I 9
D 44
			printoption("RCVD", dont, c, myopts[c]);
E 44
I 44
			printoption(">RCVD", dont, c, myopts[c]);
E 44
E 9
E 5
E 2
			if (myopts[c]) {
				myopts[c] = 0;
				sprintf(nfrontp, wont, c);
D 11
				nfrontp += sizeof(wont) - 2;
E 11
I 11
				nfrontp += sizeof (wont) - 2;
I 39
				flushline = 1;
				setconnmode();	/* set new tty mode (maybe) */
E 39
E 11
I 2
D 9
				if (showoptions)
					printoption("<--", wont, c);
E 9
I 9
D 44
				printoption("SENT", wont, c);
E 44
I 44
				printoption(">SENT", wont, c);
E 44
E 9
E 2
			}
			state = TS_DATA;
			continue;
I 44
		case TS_SB:
			if (c == IAC) {
				state = TS_SE;
			} else {
				SB_ACCUM(c);
			}
			continue;

		case TS_SE:
			if (c != SE) {
				if (c != IAC) {
					SB_ACCUM(IAC);
				}
				SB_ACCUM(c);
				state = TS_SB;
			} else {
				SB_TERM();
				suboption();	/* handle sub-option */
				state = TS_DATA;
			}
E 44
		}
	}
}
D 39

E 39
I 39

E 49
I 49
D 72
void
E 49
E 39
D 44
willoption(option)
	int option;
E 44
I 44
D 71
willoption(option, reply)
	int option, reply;
E 71
I 71
send_do(c)
E 72
I 72
send_do(c, init)
D 83
register int c, init;
E 83
I 83
    register int c, init;
E 83
E 72
E 71
E 44
{
I 71
D 72
    if (!(did_he_say_will(c) && did_I_say_do(c))) {
	NET2ADD(IAC, DO);
	NETADD(c);
	I_said_do(c);
	printoption("SENT", "do", c);
E 72
I 72
    if (init) {
	if (((do_dont_resp[c] == 0) && my_state_is_do(c)) ||
				my_want_state_is_do(c))
	    return;
	set_my_want_state_do(c);
	do_dont_resp[c]++;
E 72
    }
I 72
    NET2ADD(IAC, DO);
    NETADD(c);
D 83
    printoption("SENT", "do", c);
E 83
I 83
    printoption("SENT", DO, c);
E 83
E 72
}

D 83
void
E 83
I 83
    void
E 83
D 72
send_dont(c)
E 72
I 72
send_dont(c, init)
D 83
register int c, init;
E 83
I 83
    register int c, init;
E 83
E 72
{
D 72
    if (did_he_say_will(c) || did_I_say_do(c)) {
	NET2ADD(IAC, DONT);
	NETADD(c);
	I_said_dont(c);
	printoption("SENT", "dont", c);
E 72
I 72
    if (init) {
	if (((do_dont_resp[c] == 0) && my_state_is_dont(c)) ||
				my_want_state_is_dont(c))
	    return;
	set_my_want_state_dont(c);
	do_dont_resp[c]++;
E 72
    }
I 72
    NET2ADD(IAC, DONT);
    NETADD(c);
D 83
    printoption("SENT", "dont", c);
E 83
I 83
    printoption("SENT", DONT, c);
E 83
E 72
}

D 83
void
E 83
I 83
    void
E 83
D 72
send_will(c)
E 72
I 72
send_will(c, init)
D 83
register int c, init;
E 83
I 83
    register int c, init;
E 83
E 72
{
D 72
    if (!(did_he_say_do(c) && did_I_say_will(c))) {
	NET2ADD(IAC, WILL);
	NETADD(c);
	I_said_will(c);
	printoption("SENT", "will", c);
E 72
I 72
    if (init) {
	if (((will_wont_resp[c] == 0) && my_state_is_will(c)) ||
				my_want_state_is_will(c))
	    return;
	set_my_want_state_will(c);
	will_wont_resp[c]++;
E 72
    }
I 72
    NET2ADD(IAC, WILL);
    NETADD(c);
D 83
    printoption("SENT", "will", c);
E 83
I 83
    printoption("SENT", WILL, c);
E 83
E 72
}

D 83
void
E 83
I 83
    void
E 83
D 72
send_wont(c)
E 72
I 72
send_wont(c, init)
D 83
register int c, init;
E 83
I 83
    register int c, init;
E 83
E 72
{
D 72
    if (did_he_say_do(c) || did_I_say_will(c)) {
	NET2ADD(IAC, WONT);
	NETADD(c);
	I_said_wont(c);
	printoption("SENT", "wont", c);
E 72
I 72
    if (init) {
	if (((will_wont_resp[c] == 0) && my_state_is_wont(c)) ||
				my_want_state_is_wont(c))
	    return;
	set_my_want_state_wont(c);
	will_wont_resp[c]++;
E 72
    }
I 72
    NET2ADD(IAC, WONT);
    NETADD(c);
D 83
    printoption("SENT", "wont", c);
E 83
I 83
    printoption("SENT", WONT, c);
E 83
E 72
}


D 83
void
E 83
I 83
	void
E 83
willoption(option)
	int option;
{
E 71
D 81
	char *fmt;
E 81
I 72
	int new_state_ok = 0;
E 72

I 71
D 72
	he_said_will(option);
E 72
I 72
	if (do_dont_resp[option]) {
	    --do_dont_resp[option];
	    if (do_dont_resp[option] && my_state_is_do(option))
		--do_dont_resp[option];
	}
E 72

E 71
D 72
	switch (option) {
E 72
I 72
	if ((do_dont_resp[option] == 0) && my_want_state_is_dont(option)) {
E 72

D 72
	case TELOPT_ECHO:
I 49
#	if defined(TN3270)
	    /*
	     * The following is a pain in the rear-end.
	     * Various IBM servers (some versions of Wiscnet,
	     * possibly Fibronics/Spartacus, and who knows who
	     * else) will NOT allow us to send "DO SGA" too early
	     * in the setup proceedings.  On the other hand,
	     * 4.2 servers (telnetd) won't set SGA correctly.
	     * So, we are stuck.  Empirically (but, based on
	     * a VERY small sample), the IBM servers don't send
	     * out anything about ECHO, so we postpone our sending
	     * "DO SGA" until we see "WILL ECHO" (which 4.2 servers
	     * DO send).
	     */
	    {
		if (askedSGA == 0) {
		    askedSGA = 1;
D 71
		    if (!hisopts[TELOPT_SGA]) {
			willoption(TELOPT_SGA, 0);
E 71
I 71
		    if (!did_I_say_do(TELOPT_SGA)) {
			send_do(TELOPT_SGA);
E 72
I 72
	    switch (option) {

	    case TELOPT_ECHO:
#	    if defined(TN3270)
		/*
		 * The following is a pain in the rear-end.
		 * Various IBM servers (some versions of Wiscnet,
		 * possibly Fibronics/Spartacus, and who knows who
		 * else) will NOT allow us to send "DO SGA" too early
		 * in the setup proceedings.  On the other hand,
		 * 4.2 servers (telnetd) won't set SGA correctly.
		 * So, we are stuck.  Empirically (but, based on
		 * a VERY small sample), the IBM servers don't send
		 * out anything about ECHO, so we postpone our sending
		 * "DO SGA" until we see "WILL ECHO" (which 4.2 servers
		 * DO send).
		  */
		{
		    if (askedSGA == 0) {
			askedSGA = 1;
			if (my_want_state_is_dont(TELOPT_SGA))
			    send_do(TELOPT_SGA, 1);
E 72
E 71
		    }
		}
D 72
	    }
		/* Fall through */
	case TELOPT_EOR:
	case TELOPT_BINARY:
#endif	/* defined(TN3270) */
E 49
D 11
		mode(1);
E 11
I 11
D 39
		(void) mode(1);
E 11

E 39
	case TELOPT_SGA:
E 72
I 72
		    /* Fall through */
	    case TELOPT_EOR:
D 74
	    case TELOPT_BINARY:
E 74
#endif	    /* defined(TN3270) */
I 74
	    case TELOPT_BINARY:
E 74
	    case TELOPT_SGA:
E 72
I 39
		settimer(modenegotiated);
I 74
		/* FALL THROUGH */
	    case TELOPT_STATUS:
I 83
D 85
#if	defined(AUTHENTICATE)
E 85
I 85
#if	defined(AUTHENTICATION)
E 85
	    case TELOPT_AUTHENTICATION:
#endif
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
	    case TELOPT_ENCRYPT:
D 88
#endif
E 88
I 88
#endif /* ENCRYPTION */
E 88
E 83
E 74
E 39
D 71
		hisopts[option] = 1;
		fmt = doopt;
E 71
I 71
D 72
		send_do(option);
E 71
I 39
		setconnmode();		/* possibly set new tty mode */
E 72
I 72
		new_state_ok = 1;
E 72
E 39
		break;

D 72
	case TELOPT_TM:
E 72
I 72
	    case TELOPT_TM:
		if (flushout)
		    flushout = 0;
		/*
		 * Special case for TM.  If we get back a WILL,
		 * pretend we got back a WONT.
		 */
		set_my_want_state_dont(option);
		set_my_state_dont(option);
E 72
D 39
		fmt = dont;
		break;
E 39
I 39
		return;			/* Never reply to TM will's/wont's */
E 39

D 72
	default:
D 71
		fmt = dont;
E 71
I 71
		send_dont(option);
E 72
I 72
	    case TELOPT_LINEMODE:
	    default:
E 72
E 71
		break;
I 72
	    }

	    if (new_state_ok) {
		set_my_want_state_do(option);
		send_do(option, 0);
		setconnmode(0);		/* possibly set new tty mode */
	    } else {
		do_dont_resp[option]++;
		send_dont(option, 0);
	    }
E 72
	}
I 72
	set_my_state_do(option);
I 83
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
	if (option == TELOPT_ENCRYPT)
		encrypt_send_support();
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83
E 72
D 2
	sprintf(nfrontp, dont, option);
E 2
I 2
D 50
	sprintf(nfrontp, fmt, option);
E 2
D 11
	nfrontp += sizeof(dont) - 2;
E 11
I 11
	nfrontp += sizeof (dont) - 2;
E 50
I 50
D 54
	netoprint(fmt, option);
E 54
I 54
D 71
	printring(&netoring, fmt, option);
E 54
E 50
E 11
I 2
D 9
	if (showoptions)
		printoption("<--", fmt, option);
E 9
I 9
D 44
	printoption("SENT", fmt, option);
E 44
I 44
	if (reply)
D 49
		printoption(">SENT", fmt, option);
E 49
I 49
		printoption(">SENT", fmt, option, reply);
E 49
	else
D 49
		printoption("<SENT", fmt, option);
E 49
I 49
		printoption("<SENT", fmt, option, reply);
E 71
E 49
E 44
E 9
E 2
}

I 49
D 83
void
E 83
I 83
	void
E 83
E 49
D 44
wontoption(option)
	int option;
E 44
I 44
D 71
wontoption(option, reply)
	int option, reply;
E 71
I 71
wontoption(option)
	int option;
E 71
E 44
{
D 81
	char *fmt;

E 81
I 71
D 72
	he_said_wont(option);
E 72
I 72
	if (do_dont_resp[option]) {
	    --do_dont_resp[option];
	    if (do_dont_resp[option] && my_state_is_dont(option))
		--do_dont_resp[option];
	}
E 72

E 71
D 72
	switch (option) {
E 72
I 72
	if ((do_dont_resp[option] == 0) && my_want_state_is_do(option)) {
E 72

D 72
	case TELOPT_ECHO:
D 11
		mode(2);
E 11
I 11
D 39
		(void) mode(2);
E 11

E 39
	case TELOPT_SGA:
E 72
I 72
	    switch (option) {

#ifdef	KLUDGELINEMODE
	    case TELOPT_SGA:
		if (!kludgelinemode)
		    break;
		/* FALL THROUGH */
#endif
	    case TELOPT_ECHO:
E 72
I 39
		settimer(modenegotiated);
E 39
D 71
		hisopts[option] = 0;
		fmt = dont;
E 71
I 71
D 72
		send_dont(option);
E 71
I 39
		setconnmode();			/* Set new tty mode */
E 72
E 39
		break;

I 39
D 72
	case TELOPT_TM:
E 72
I 72
	    case TELOPT_TM:
		if (flushout)
		    flushout = 0;
		set_my_want_state_dont(option);
		set_my_state_dont(option);
E 72
		return;		/* Never reply to TM will's/wont's */

E 39
D 72
	default:
I 68
D 71
		hisopts[option] = 0;
E 68
		fmt = dont;
E 71
I 71
		send_dont(option);
E 72
I 72
	    default:
		break;
	    }
	    set_my_want_state_dont(option);
D 81
	    send_dont(option, 0);
E 81
I 81
	    if (my_state_is_do(option))
		send_dont(option, 0);
E 81
	    setconnmode(0);			/* Set new tty mode */
	} else if (option == TELOPT_TM) {
	    /*
	     * Special case for TM.
	     */
	    if (flushout)
		flushout = 0;
	    set_my_want_state_dont(option);
E 72
E 71
	}
I 72
	set_my_state_dont(option);
E 72
D 50
	sprintf(nfrontp, fmt, option);
D 11
	nfrontp += sizeof(doopt) - 2;
E 11
I 11
	nfrontp += sizeof (doopt) - 2;
E 50
I 50
D 54
	netoprint(fmt, option);
E 54
I 54
D 71
	printring(&netoring, fmt, option);
E 54
E 50
E 11
I 2
D 9
	if (showoptions)
		printoption("<--", fmt, option);
E 9
I 9
D 44
	printoption("SENT", fmt, option);
E 44
I 44
	if (reply)
D 49
		printoption(">SENT", fmt, option);
E 49
I 49
		printoption(">SENT", fmt, option, reply);
E 49
	else
D 49
		printoption("<SENT", fmt, option);
E 49
I 49
		printoption("<SENT", fmt, option, reply);
E 71
E 49
E 44
E 9
E 2
}

I 49
D 83
static void
E 83
I 83
	static void
E 83
E 49
dooption(option)
	int option;
{
D 81
	char *fmt;
E 81
I 72
	int new_state_ok = 0;
E 72

I 71
D 72
	he_said_do(option);
E 72
I 72
	if (will_wont_resp[option]) {
	    --will_wont_resp[option];
	    if (will_wont_resp[option] && my_state_is_will(option))
		--will_wont_resp[option];
	}
E 72

E 71
D 72
	switch (option) {
E 72
I 72
	if (will_wont_resp[option] == 0) {
	  if (my_want_state_is_wont(option)) {
E 72

D 72
	case TELOPT_TM:
E 72
I 72
	    switch (option) {

	    case TELOPT_TM:
		/*
		 * Special case for TM.  We send a WILL, but pretend
		 * we sent WONT.
		 */
		send_will(option, 0);
		set_my_want_state_wont(TELOPT_TM);
		set_my_state_wont(TELOPT_TM);
		return;

I 79
D 83
#ifdef	KERBEROS
	    case TELOPT_AUTHENTICATION:
		if (kerberized)
			new_state_ok = 1;
		break;
#endif
E 83
E 79
E 72
D 39
		fmt = wont;
		break;

I 22
	case TELOPT_ECHO:
		(void) mode(2);
E 39
D 71
		fmt = will;
D 39
		hisopts[option] = 0;
E 39
		break;

E 71
I 49
#	if defined(TN3270)
D 70
	case TELOPT_EOR:
	case TELOPT_BINARY:
E 70
I 70
D 72
	case TELOPT_EOR:		/* end of record */
	case TELOPT_BINARY:		/* binary mode */
E 72
I 72
	    case TELOPT_EOR:		/* end of record */
D 74
	    case TELOPT_BINARY:		/* binary mode */
E 74
E 72
E 70
#	endif	/* defined(TN3270) */
I 74
	    case TELOPT_BINARY:		/* binary mode */
E 74
I 70
D 72
	case TELOPT_NAWS:		/* window size */
	case TELOPT_TSPEED:		/* terminal speed */
	case TELOPT_LFLOW:		/* local flow control */
E 70
E 49
I 44
	case TELOPT_TTYPE:		/* terminal type option */
E 44
E 22
D 39
	case TELOPT_SGA:
E 39
I 39
	case TELOPT_SGA:		/* no big deal */
E 39
D 71
		fmt = will;
I 39
		myopts[option] = 1;
E 71
I 71
		send_will(option);
E 72
I 72
	    case TELOPT_NAWS:		/* window size */
	    case TELOPT_TSPEED:		/* terminal speed */
	    case TELOPT_LFLOW:		/* local flow control */
	    case TELOPT_TTYPE:		/* terminal type option */
	    case TELOPT_SGA:		/* no big deal */
I 81
D 90
	    case TELOPT_ENVIRON:	/* environment variable option */
E 90
I 83
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
	    case TELOPT_ENCRYPT:	/* encryption variable option */
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83
E 81
		new_state_ok = 1;
E 72
E 71
E 39
		break;
I 90

	    case TELOPT_NEW_ENVIRON:	/* New environment variable option */
#ifdef	OLD_ENVIRON
		if (my_state_is_will(TELOPT_OLD_ENVIRON))
			send_wont(TELOPT_OLD_ENVIRON, 1); /* turn off the old */
		goto env_common;
	    case TELOPT_OLD_ENVIRON:	/* Old environment variable option */
		if (my_state_is_will(TELOPT_NEW_ENVIRON))
			break;		/* Don't enable if new one is in use! */
	    env_common:
		telopt_environ = option;
#endif
		new_state_ok = 1;
		break;

E 90
I 83
D 85
#if	defined(AUTHENTICATE)
E 85
I 85
#if	defined(AUTHENTICATION)
E 85
	    case TELOPT_AUTHENTICATION:
		if (autologin)
			new_state_ok = 1;
		break;
#endif
E 83

I 81
	    case TELOPT_XDISPLOC:	/* X Display location */
D 83
		if (env_getvalue("DISPLAY"))
E 83
I 83
		if (env_getvalue((unsigned char *)"DISPLAY"))
E 83
		    new_state_ok = 1;
		break;

E 81
I 39
D 72
	case TELOPT_ECHO:		/* We're never going to echo... */
E 39
	default:
D 71
		fmt = wont;
E 71
I 71
		send_wont(option);
E 72
I 72
	    case TELOPT_LINEMODE:
#ifdef	KLUDGELINEMODE
		kludgelinemode = 0;
I 81
		send_do(TELOPT_SGA, 1);
E 81
#endif
		set_my_want_state_will(TELOPT_LINEMODE);
		send_will(option, 0);
		set_my_state_will(TELOPT_LINEMODE);
		slc_init();
		return;

	    case TELOPT_ECHO:		/* We're never going to echo... */
	    default:
E 72
E 71
		break;
I 72
	    }

	    if (new_state_ok) {
		set_my_want_state_will(option);
		send_will(option, 0);
I 82
		setconnmode(0);			/* Set new tty mode */
E 82
	    } else {
		will_wont_resp[option]++;
		send_wont(option, 0);
	    }
	  } else {
	    /*
	     * Handle options that need more things done after the
	     * other side has acknowledged the option.
	     */
	    switch (option) {
	    case TELOPT_LINEMODE:
#ifdef	KLUDGELINEMODE
		kludgelinemode = 0;
I 81
		send_do(TELOPT_SGA, 1);
E 81
#endif
		set_my_state_will(option);
		slc_init();
I 81
		send_do(TELOPT_SGA, 0);
E 81
		return;
	    }
	  }
E 72
	}
I 72
	set_my_state_will(option);
E 72
D 50
	sprintf(nfrontp, fmt, option);
D 11
	nfrontp += sizeof(doopt) - 2;
E 11
I 11
	nfrontp += sizeof (doopt) - 2;
E 50
I 50
D 54
	netoprint(fmt, option);
E 54
I 54
D 71
	printring(&netoring, fmt, option);
E 54
E 50
E 11
I 2
D 9
	if (showoptions)
		printoption("<--", fmt, option);
E 9
I 9
D 44
	printoption("SENT", fmt, option);
E 44
I 44
D 49
	printoption(">SENT", fmt, option);
E 49
I 49
	printoption(">SENT", fmt, option, 0);
E 71
E 49
E 44
E 9
E 2
}
I 44

I 72
D 83
static void
E 83
I 83
	static void
E 83
dontoption(option)
	int option;
{

	if (will_wont_resp[option]) {
	    --will_wont_resp[option];
	    if (will_wont_resp[option] && my_state_is_wont(option))
		--will_wont_resp[option];
	}

	if ((will_wont_resp[option] == 0) && my_want_state_is_will(option)) {
I 73
	    switch (option) {
	    case TELOPT_LINEMODE:
		linemode = 0;	/* put us back to the default state */
		break;
I 90
#ifdef	OLD_ENVIRON
	    case TELOPT_NEW_ENVIRON:
		/*
		 * The new environ option wasn't recognized, try
		 * the old one.
		 */
		send_will(TELOPT_OLD_ENVIRON, 1);
		telopt_environ = TELOPT_OLD_ENVIRON;
		break;
#endif
E 90
	    }
E 73
	    /* we always accept a DONT */
	    set_my_want_state_wont(option);
D 81
	    send_wont(option, 0);
E 81
I 81
	    if (my_state_is_will(option))
		send_wont(option, 0);
E 81
I 75
	    setconnmode(0);			/* Set new tty mode */
E 75
	}
	set_my_state_wont(option);
}

E 72
/*
I 74
 * Given a buffer returned by tgetent(), this routine will turn
 * the pipe seperated list of names in the buffer into an array
 * of pointers to null terminated names.  We toss out any bad,
 * duplicate, or verbose names (names with spaces).
 */

D 83
static char *unknown[] = { "UNKNOWN", 0 };
E 83
I 83
static char *name_unknown = "UNKNOWN";
static char *unknown[] = { 0, 0 };
E 83

D 83
char **
E 83
I 83
	char **
E 83
mklist(buf, name)
D 83
char *buf, *name;
E 83
I 83
	char *buf, *name;
E 83
{
	register int n;
D 83
	register char c, *cp, **argvp, *cp2, **argv;
	char *malloc();
E 83
I 83
	register char c, *cp, **argvp, *cp2, **argv, **avt;
E 83

	if (name) {
D 83
		if (strlen(name) > 40)
E 83
I 83
D 92
		if (strlen(name) > 40) {
E 92
I 92
		if ((int)strlen(name) > 40) {
E 92
E 83
			name = 0;
D 83
		else {
E 83
I 83
			unknown[0] = name_unknown;
		} else {
E 83
			unknown[0] = name;
			upcase(name);
		}
D 83
	}
E 83
I 83
	} else
		unknown[0] = name_unknown;
E 83
	/*
	 * Count up the number of names.
	 */
	for (n = 1, cp = buf; *cp && *cp != ':'; cp++) {
		if (*cp == '|')
			n++;
	}
	/*
	 * Allocate an array to put the name pointers into
	 */
	argv = (char **)malloc((n+3)*sizeof(char *));
	if (argv == 0)
		return(unknown);

	/*
	 * Fill up the array of pointers to names.
	 */
	*argv = 0;
	argvp = argv+1;
	n = 0;
	for (cp = cp2 = buf; (c = *cp);  cp++) {
		if (c == '|' || c == ':') {
			*cp++ = '\0';
			/*
			 * Skip entries that have spaces or are over 40
			 * characters long.  If this is our environment
			 * name, then put it up front.  Otherwise, as
			 * long as this is not a duplicate name (case
			 * insensitive) add it to the list.
			 */
			if (n || (cp - cp2 > 41))
				;
			else if (name && (strncasecmp(name, cp2, cp-cp2) == 0))
				*argv = cp2;
			else if (is_unique(cp2, argv+1, argvp))
				*argvp++ = cp2;
			if (c == ':')
				break;
			/*
			 * Skip multiple delimiters. Reset cp2 to
			 * the beginning of the next name. Reset n,
			 * the flag for names with spaces.
			 */
			while ((c = *cp) == '|')
				cp++;
			cp2 = cp;
			n = 0;
		}
		/*
		 * Skip entries with spaces or non-ascii values.
		 * Convert lower case letters to upper case.
		 */
		if ((c == ' ') || !isascii(c))
			n = 1;
		else if (islower(c))
			*cp = toupper(c);
	}
D 92
	
E 92
I 92

E 92
	/*
	 * Check for an old V6 2 character name.  If the second
	 * name points to the beginning of the buffer, and is
	 * only 2 characters long, move it to the end of the array.
	 */
	if ((argv[1] == buf) && (strlen(argv[1]) == 2)) {
I 83
		--argvp;
		for (avt = &argv[1]; avt < argvp; avt++)
			*avt = *(avt+1);
E 83
		*argvp++ = buf;
D 83
		cp = *argv++;
		*argv = cp;
E 83
	}

	/*
	 * Duplicate last name, for TTYPE option, and null
	 * terminate the array.  If we didn't find a match on
	 * our terminal name, put that name at the beginning.
	 */
	cp = *(argvp-1);
	*argvp++ = cp;
	*argvp = 0;

	if (*argv == 0) {
		if (name)
			*argv = name;
D 83
		else
			argv++;
E 83
I 83
		else {
			--argvp;
			for (avt = argv; avt < argvp; avt++)
				*avt = *(avt+1);
		}
E 83
	}
	if (*argv)
		return(argv);
	else
		return(unknown);
}

I 83
	int
E 83
is_unique(name, as, ae)
D 83
register char *name, **as, **ae;
E 83
I 83
	register char *name, **as, **ae;
E 83
{
	register char **ap;
	register int n;

	n = strlen(name) + 1;
	for (ap = as; ap < ae; ap++)
		if (strncasecmp(*ap, name, n) == 0)
			return(0);
	return (1);
}

#ifdef	TERMCAP
D 75
char ttytype[1024];
E 75
I 75
char termbuf[1024];
I 81
D 83
/*ARGSUSED*/
E 83
I 83

	/*ARGSUSED*/
	int
E 83
E 81
E 75
setupterm(tname, fd, errp)
D 83
char *tname;
int fd, *errp;
E 83
I 83
	char *tname;
	int fd, *errp;
E 83
{
D 75
	if (tgetent(ttytype, tname) == 1) {
		ttytype[1023] = '\0';
E 75
I 75
	if (tgetent(termbuf, tname) == 1) {
		termbuf[1023] = '\0';
E 75
		if (errp)
			*errp = 1;
		return(0);
	}
	if (errp)
		*errp = 0;
	return(-1);
}
I 75
#else
#define	termbuf	ttytype
extern char ttytype[];
E 75
#endif

D 83
char *
E 83
I 83
int resettermname = 1;

	char *
E 83
gettermname()
{
	char *tname;
D 83
	static int first = 1;
D 75
	extern char ttytype[];
E 75
	static char **tnamep;
E 83
I 83
	static char **tnamep = 0;
E 83
	static char **next;
D 81
	char *getenv();
E 81
	int err;

D 83
	if (first) {
		first = 0;
D 81
		if ((tname = getenv("TERM")) &&
E 81
I 81
		if ((tname = env_getvalue("TERM")) &&
E 83
I 83
	if (resettermname) {
		resettermname = 0;
		if (tnamep && tnamep != unknown)
			free(tnamep);
		if ((tname = (char *)env_getvalue((unsigned char *)"TERM")) &&
E 83
E 81
				(setupterm(tname, 1, &err) == 0)) {
D 75
			tnamep = mklist(ttytype, tname);
E 75
I 75
			tnamep = mklist(termbuf, tname);
E 75
		} else {
D 92
			if (tname && (strlen(tname) <= 40)) {
E 92
I 92
			if (tname && ((int)strlen(tname) <= 40)) {
E 92
				unknown[0] = tname;
				upcase(tname);
D 83
			}
E 83
I 83
			} else
				unknown[0] = name_unknown;
E 83
			tnamep = unknown;
		}
		next = tnamep;
	}
	if (*next == 0)
		next = tnamep;
	return(*next++);
}
/*
E 74
 * suboption()
 *
 *	Look at the sub-option buffer, and try to be helpful to the other
 * side.
 *
 *	Currently we recognize:
 *
 *		Terminal type, send request.
I 70
 *		Terminal speed (send request).
 *		Local flow control (is request).
I 72
 *		Linemode
E 72
E 70
 */

I 72
D 74
static char tty1[] = { IAC, SB, TELOPT_TTYPE, TELQUAL_IS, 0 };
static char tty2[] = { IAC, SE, 0 };

E 74
E 72
I 49
D 83
static void
E 83
I 83
    static void
E 83
E 49
suboption()
{
I 90
    unsigned char subchar;

E 90
I 49
D 72
    printsub("<", subbuffer, subend-subbuffer+1);
E 72
I 72
D 83
    printsub('<', subbuffer, subend-subbuffer+2);
E 72
E 49
    switch (subbuffer[0]&0xff) {
E 83
I 83
    printsub('<', subbuffer, SB_LEN()+2);
D 90
    switch (SB_GET()) {
E 90
I 90
    switch (subchar = SB_GET()) {
E 90
E 83
    case TELOPT_TTYPE:
I 72
	if (my_want_state_is_wont(TELOPT_TTYPE))
	    return;
E 72
D 83
	if ((subbuffer[1]&0xff) != TELQUAL_SEND) {
	    ;
E 83
I 83
	if (SB_EOF() || SB_GET() != TELQUAL_SEND) {
	    return;
E 83
	} else {
	    char *name;
D 72
	    char namebuf[41];
E 72
D 49
	    char *getenv();
E 49
I 49
D 81
	    extern char *getenv();
E 81
I 74
D 83
	    char temp[50];
E 83
I 83
	    unsigned char temp[50];
E 83
E 74
E 49
	    int len;

I 49
#if	defined(TN3270)
D 53
	    /*
	     * Try to send a 3270 type terminal name.  Decide which one based
	     * on the format of our screen, and (in the future) color
	     * capaiblities.
	     */
#if	defined(unix)
	    if (initscr() != ERR) {	/* Initialize curses to get line size */
		MaxNumberLines = LINES;
		MaxNumberColumns = COLS;
	    }
#else	/* defined(unix) */
	    InitTerminal();
#endif	/* defined(unix) */
	    if ((MaxNumberLines >= 24) && (MaxNumberColumns >= 80)) {
		Sent3270TerminalType = 1;
		if ((MaxNumberLines >= 27) && (MaxNumberColumns >= 132)) {
		    MaxNumberLines = 27;
		    MaxNumberColumns = 132;
		    sb_terminal[SBTERMMODEL] = '5';
		} else if (MaxNumberLines >= 43) {
		    MaxNumberLines = 43;
		    MaxNumberColumns = 80;
		    sb_terminal[SBTERMMODEL] = '4';
		} else if (MaxNumberLines >= 32) {
		    MaxNumberLines = 32;
		    MaxNumberColumns = 80;
		    sb_terminal[SBTERMMODEL] = '3';
		} else {
		    MaxNumberLines = 24;
		    MaxNumberColumns = 80;
		    sb_terminal[SBTERMMODEL] = '2';
		}
		NumberLines = 24;		/* before we start out... */
		NumberColumns = 80;
		ScreenSize = NumberLines*NumberColumns;
		if ((MaxNumberLines*MaxNumberColumns) > MAXSCREENSIZE) {
D 50
		    ExitString(stderr,
			"Programming error:  MAXSCREENSIZE too small.\n", 1);
E 50
I 50
		    ExitString("Programming error:  MAXSCREENSIZE too small.\n",
									1);
E 50
		    /*NOTREACHED*/
		}
D 50
		memcpy(nfrontp, sb_terminal, sizeof sb_terminal);
		printsub(">", nfrontp+2, sizeof sb_terminal-2);
		nfrontp += sizeof sb_terminal;
E 50
I 50
		printsub(">", sb_terminal+2, sizeof sb_terminal-2);
D 52
		ring_add_data(&netoring, sb_terminal, sizeof sb_terminal);
E 52
I 52
		ring_supply_data(&netoring, sb_terminal, sizeof sb_terminal);
E 53
I 53
	    if (tn3270_ttype()) {
E 53
E 52
E 50
		return;
	    }
#endif	/* defined(TN3270) */
D 53

E 53
E 49
D 74
	    name = getenv("TERM");
	    if ((name == 0) || ((len = strlen(name)) > 40)) {
		name = "UNKNOWN";
I 59
		len = strlen(name);
E 59
	    }
	    if ((len + 4+2) < NETROOM()) {
I 71
		char temp[50];

E 71
D 72
		strcpy(namebuf, name);
		upcase(namebuf);
D 50
		sprintf(nfrontp, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
E 50
I 50
D 54
		netoprint("%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
E 54
I 54
D 71
		printring(&netoring, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
E 71
I 71
		sprintf(temp, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
E 71
E 54
E 50
				    TELQUAL_IS, namebuf, IAC, SE);
I 49
D 50
		printsub(">", nfrontp+2, 4+strlen(namebuf)+2-2-2);
E 49
		nfrontp += 4+strlen(namebuf)+2;
E 50
I 50
D 71
		/* XXX */
		/* printsub(">", nfrontp+2, 4+strlen(namebuf)+2-2-2); */
E 71
I 71
		ring_supply_data(&netoring, temp, 4+strlen(namebuf)+2);
		printsub(">", temp+2, 4+strlen(namebuf)+2-2-2);
E 72
I 72
		strcpy(temp, tty1);
		strcpy(&temp[4], name);
		upcase(&temp[4]);
		strcpy(&temp[4+len], tty2);
		len += 6;
E 74
I 74
	    name = gettermname();
	    len = strlen(name) + 4 + 2;
	    if (len < NETROOM()) {
D 83
		sprintf(temp, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
E 83
I 83
		sprintf((char *)temp, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
E 83
				TELQUAL_IS, name, IAC, SE);
E 74
		ring_supply_data(&netoring, temp, len);
D 74
		printsub('>', temp+2, len-2);
E 74
I 74
		printsub('>', &temp[2], len-2);
E 74
E 72
E 71
E 50
I 49
	    } else {
D 50
		ExitString(stderr, "No room in buffer for terminal type.\n",
E 50
I 50
D 71
		ExitString("No room in buffer for terminal type.\n",
E 50
							1);
E 71
I 71
		ExitString("No room in buffer for terminal type.\n", 1);
E 71
		/*NOTREACHED*/
E 49
	    }
	}
I 70
	break;
    case TELOPT_TSPEED:
I 72
	if (my_want_state_is_wont(TELOPT_TSPEED))
	    return;
E 72
D 83
	if ((subbuffer[1]&0xff) == TELQUAL_SEND) {
E 83
I 83
	if (SB_EOF())
	    return;
	if (SB_GET() == TELQUAL_SEND) {
E 83
D 72
	    long *ospeed,*ispeed;
	    char speedbuf[41];
	    char *getenv();
E 72
I 72
D 81
	    long ospeed,ispeed;
E 81
I 81
D 82
	    int ospeed, ispeed;
E 82
I 82
	    long ospeed, ispeed;
E 82
E 81
D 83
	    char temp[50];
E 83
I 83
	    unsigned char temp[50];
E 83
E 72
	    int len;
E 70

I 70
	    TerminalSpeeds(&ispeed, &ospeed);

D 72
	    sprintf(speedbuf, "%d,%d", ospeed, ispeed);
	    len = strlen(speedbuf);
E 72
I 72
D 83
	    sprintf(temp, "%c%c%c%c%d,%d%c%c", IAC, SB, TELOPT_TSPEED,
E 83
I 83
	    sprintf((char *)temp, "%c%c%c%c%d,%d%c%c", IAC, SB, TELOPT_TSPEED,
E 83
		    TELQUAL_IS, ospeed, ispeed, IAC, SE);
D 83
	    len = strlen(temp+4) + 4;	/* temp[3] is 0 ... */
E 83
I 83
	    len = strlen((char *)temp+4) + 4;	/* temp[3] is 0 ... */
E 83
E 72

D 72
	    if ((len + 4+2) < NETROOM()) {
		printring(&netoring, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TSPEED,
		    TELQUAL_IS, speedbuf, IAC, SE);
E 72
I 72
	    if (len < NETROOM()) {
		ring_supply_data(&netoring, temp, len);
		printsub('>', temp+2, len - 2);
E 72
	    }
I 81
/*@*/	    else printf("lm_will: not enough room in buffer\n");
E 81
	}
	break;
    case TELOPT_LFLOW:
I 72
	if (my_want_state_is_wont(TELOPT_LFLOW))
	    return;
E 72
D 83
	if ((subbuffer[1]&0xff) == 1) {
E 83
I 83
	if (SB_EOF())
	    return;
	switch(SB_GET()) {
D 85
	case 1:
E 85
I 85
	case LFLOW_RESTART_ANY:
	    restartany = 1;
	    break;
	case LFLOW_RESTART_XON:
	    restartany = 0;
	    break;
	case LFLOW_ON:
E 85
E 83
	    localflow = 1;
D 83
	} else if ((subbuffer[1]&0xff) == 0) {
E 83
I 83
	    break;
D 85
	case 0:
E 85
I 85
	case LFLOW_OFF:
E 85
E 83
	    localflow = 0;
I 83
	    break;
	default:
	    return;
E 83
	}
	setcommandmode();
D 72
	setconnmode();
E 72
I 72
	setconnmode(0);
E 72
	break;
I 72

    case TELOPT_LINEMODE:
	if (my_want_state_is_wont(TELOPT_LINEMODE))
	    return;
D 83
	switch (subbuffer[1]&0xff) {
E 83
I 83
	if (SB_EOF())
	    return;
	switch (SB_GET()) {
E 83
	case WILL:
D 83
	    lm_will(&subbuffer[2], subend - &subbuffer[2]);
E 83
I 83
	    lm_will(subpointer, SB_LEN());
E 83
	    break;
	case WONT:
D 83
	    lm_wont(&subbuffer[2], subend - &subbuffer[2]);
E 83
I 83
	    lm_wont(subpointer, SB_LEN());
E 83
	    break;
	case DO:
D 83
	    lm_do(&subbuffer[2], subend - &subbuffer[2]);
E 83
I 83
	    lm_do(subpointer, SB_LEN());
E 83
	    break;
	case DONT:
D 83
	    lm_dont(&subbuffer[2], subend - &subbuffer[2]);
E 83
I 83
	    lm_dont(subpointer, SB_LEN());
E 83
	    break;
	case LM_SLC:
D 83
	    slc(&subbuffer[2], subend - &subbuffer[2]);
E 83
I 83
	    slc(subpointer, SB_LEN());
E 83
	    break;
	case LM_MODE:
D 83
	    lm_mode(&subbuffer[2], subend - &subbuffer[2], 0);
E 83
I 83
	    lm_mode(subpointer, SB_LEN(), 0);
E 83
	    break;
	default:
I 81
	    break;
	}
	break;

D 90
    case TELOPT_ENVIRON:
E 90
I 90
#ifdef	OLD_ENVIRON
    case TELOPT_OLD_ENVIRON:
#endif
    case TELOPT_NEW_ENVIRON:
E 90
D 83
	switch(subbuffer[1]&0xff) {
E 83
I 83
	if (SB_EOF())
	    return;
	switch(SB_PEEK()) {
E 83
	case TELQUAL_IS:
	case TELQUAL_INFO:
D 90
	    if (my_want_state_is_dont(TELOPT_ENVIRON))
E 90
I 90
	    if (my_want_state_is_dont(subchar))
E 90
		return;
	    break;
	case TELQUAL_SEND:
D 90
	    if (my_want_state_is_wont(TELOPT_ENVIRON)) {
E 90
I 90
	    if (my_want_state_is_wont(subchar)) {
E 90
		return;
	    }
	    break;
	default:
	    return;
	}
D 83
	env_opt(&subbuffer[1], subend - &subbuffer[1]);
E 83
I 83
	env_opt(subpointer, SB_LEN());
E 83
	break;

    case TELOPT_XDISPLOC:
	if (my_want_state_is_wont(TELOPT_XDISPLOC))
	    return;
D 83
	if ((subbuffer[1]&0xff) == TELQUAL_SEND) {
	    char temp[50], *dp;
E 83
I 83
	if (SB_EOF())
	    return;
	if (SB_GET() == TELQUAL_SEND) {
	    unsigned char temp[50], *dp;
E 83
	    int len;

D 83
	    if ((dp = env_getvalue("DISPLAY")) == NULL) {
E 83
I 83
	    if ((dp = env_getvalue((unsigned char *)"DISPLAY")) == NULL) {
E 83
		/*
		 * Something happened, we no longer have a DISPLAY
		 * variable.  So, turn off the option.
		 */
		send_wont(TELOPT_XDISPLOC, 1);
E 81
		break;
I 81
	    }
D 83
	    sprintf(temp, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_XDISPLOC,
E 83
I 83
	    sprintf((char *)temp, "%c%c%c%c%s%c%c", IAC, SB, TELOPT_XDISPLOC,
E 83
		    TELQUAL_IS, dp, IAC, SE);
D 83
	    len = strlen(temp+4) + 4;	/* temp[3] is 0 ... */
E 83
I 83
	    len = strlen((char *)temp+4) + 4;	/* temp[3] is 0 ... */
E 83

	    if (len < NETROOM()) {
		ring_supply_data(&netoring, temp, len);
		printsub('>', temp+2, len - 2);
	    }
/*@*/	    else printf("lm_will: not enough room in buffer\n");
E 81
	}
I 81
	break;
E 81
I 79

D 83
#ifdef	KERBEROS
    case TELOPT_AUTHENTICATION:
	if ((subbuffer[1] & 0xff) == TELQUAL_SEND) {
		register char *cp = &subbuffer[2];
I 80
		char tmp[256];
E 80
		int dokrb4 = 0, unknowntypes = 0, noresponse = 1;

		while (cp < subend) {
D 82
			switch (*cp) {
E 82
I 82
			switch (*cp&0xff) {
E 82
			case TELQUAL_AUTHTYPE_KERBEROS_V4:
				dokrb4 = 1;
				break;
			default:
				unknowntypes++;
			}
			cp++;
E 83
I 83
D 85
#if	defined(AUTHENTICATE)
E 85
I 85
#if	defined(AUTHENTICATION)
E 85
	case TELOPT_AUTHENTICATION: {
		if (!autologin)
			break;
		if (SB_EOF())
			return;
		switch(SB_GET()) {
		case TELQUAL_IS:
			if (my_want_state_is_dont(TELOPT_AUTHENTICATION))
				return;
			auth_is(subpointer, SB_LEN());
			break;
		case TELQUAL_SEND:
			if (my_want_state_is_wont(TELOPT_AUTHENTICATION))
				return;
			auth_send(subpointer, SB_LEN());
			break;
		case TELQUAL_REPLY:
			if (my_want_state_is_wont(TELOPT_AUTHENTICATION))
				return;
			auth_reply(subpointer, SB_LEN());
			break;
I 84
		case TELQUAL_NAME:
			if (my_want_state_is_dont(TELOPT_AUTHENTICATION))
				return;
			auth_name(subpointer, SB_LEN());
			break;
E 84
E 83
		}
D 83

		if (noresponse && dokrb4) {
			register unsigned char *ucp = (unsigned char *)cp;
			char *krb_realm;
			char hst_inst[INST_SZ];
			KTEXT_ST authent_st;
			int space = 0;
			int retval;
			extern char *krb_realmofhost(), *krb_get_phost();

			fprintf(stderr,
				"[Trying Kerberos V4 authentication]\n");

			krb_realm = krb_get_phost(hostname);
			bzero(hst_inst, sizeof(hst_inst));
			if (krb_realm)
			    strncpy(hst_inst, krb_realm, sizeof(hst_inst));
			hst_inst[sizeof(hst_inst)-1] = '\0';
			if (!(krb_realm = krb_realmofhost(hst_inst))) {
			    fprintf(stderr, "no realm for %s\n", hostname);
			    goto cantsend4;
			}
			if (retval = krb_mk_req(&authent_st, "rcmd", hst_inst,
			    krb_realm, 0L)) {
				fprintf(stderr, "mk_req failed: %s\n",
				    krb_err_txt[retval]);
				goto cantsend4;
			}
			space = authent_st.length;
			for (ucp = authent_st.dat; ucp < authent_st.dat +
			     authent_st.length; ucp++) {
				if (*ucp == IAC)
					space++;
			}
D 80
			if (NETROOM() < 6 + 1 + strlen(remotename) + 2 +
E 80
I 80
			if (NETROOM() < 6 + 1 + 2 +
E 80
			    space + 2) {
				fprintf(stderr,
				   "no room to send V4 ticket/authenticator\n");
cantsend4:
			    if (7 < NETROOM()) {
				printring(&netoring, "%c%c%c%c%c%c%c", IAC, SB,
				  TELOPT_AUTHENTICATION,
				  TELQUAL_IS, TELQUAL_AUTHTYPE_NONE, IAC, SE);
				sprintf(tmp, "%c%c%c%c%c", TELOPT_AUTHENTICATION,
					TELQUAL_IS, TELQUAL_AUTHTYPE_NONE, IAC, SE);
				printsub(">", tmp, 4+2-2-2);
			    } else
				exit(1);
			} else {
#ifdef notdef
D 80
		    printring(&netoring, "%c%c%c%c%c%c%c%s", IAC, SB,
E 80
I 80
		    printring(&netoring, "%c%c%c%c%c%c", IAC, SB,
E 80
			      TELOPT_AUTHENTICATION,
			      TELQUAL_IS, TELQUAL_AUTHTYPE_KERBEROS,
D 80
			      TELQUAL_AUTHTYPE_KERBEROS_V4,
			      strlen(remotename),
			      remotename);
		    sprintf(tmp, "%c%c%c%c%s%c%c", TELOPT_AUTHENTICATION,
E 80
I 80
			      TELQUAL_AUTHTYPE_KERBEROS_V4);
		    sprintf(tmp, "%c%c%c%c%c%c", TELOPT_AUTHENTICATION,
E 80
			    TELQUAL_IS, TELQUAL_AUTHTYPE_KERBEROS,
D 80
			    TELQUAL_AUTHTYPE_KERBEROS_V4,
			    remotename, IAC, SE);
E 80
I 80
			    TELQUAL_AUTHTYPE_KERBEROS_V4, IAC, SE);
E 80
#else
D 80
			    printring(&netoring, "%c%c%c%c%c%c%s", IAC, SB,
E 80
I 80
			    printring(&netoring, "%c%c%c%c%c", IAC, SB,
E 80
			      TELOPT_AUTHENTICATION,
			      TELQUAL_IS,
D 80
			      TELQUAL_AUTHTYPE_KERBEROS_V4,
			      strlen(remotename),
			      remotename);
			    sprintf(tmp, "%c%c%c%s%c%c", TELOPT_AUTHENTICATION,
E 80
I 80
			      TELQUAL_AUTHTYPE_KERBEROS_V4);
			    sprintf(tmp, "%c%c%c%c%c", TELOPT_AUTHENTICATION,
E 80
			      TELQUAL_IS,
D 80
			      TELQUAL_AUTHTYPE_KERBEROS_V4,
			      remotename, IAC, SE);
E 80
I 80
			      TELQUAL_AUTHTYPE_KERBEROS_V4, IAC, SE);
E 80
#endif
D 80
			    printsub(">", tmp, 4+strlen(remotename)+2-2-2);
E 80
I 80
			    printsub(">", tmp, 4+2-2-2);
E 80
			    ring_supply_bindata(&netoring,
			        (char *)authent_st.dat, authent_st.length, IAC);
			    printring(&netoring, "%c%c", IAC, SE);
			}
			noresponse = 0;
	    	}
	    	if (noresponse) {
			if (NETROOM() < 7) {
			    ExitString("not enough room to reject unhandled authtype\n", 1);
			} else {
			    fprintf(stderr,"[Sending empty auth info in response to request for %d unknown type(s):\n\t", unknowntypes);
#ifdef notdef
			    cp = &subbuffer[3];
#else
			    cp = &subbuffer[2];
#endif
			    while (cp < subend) {
D 82
				switch (*cp) {
E 82
I 82
				switch (*cp&0xff) {
E 82
				case TELQUAL_AUTHTYPE_KERBEROS_V4:
			    		break;
				default:
			    		fprintf(stderr, "%d,", *cp);
			    		break;
				}
				cp++;
		    	    }
		    	    fputs("]\n", stderr);
		    	    printring(&netoring, "%c%c%c%c%c%c%c", IAC, SB,
			      TELOPT_AUTHENTICATION,
			      TELQUAL_IS, TELQUAL_AUTHTYPE_NONE, IAC, SE);
			}
	    	}
E 83
	}
E 79
	break;
I 79
D 83
#endif /* KERBEROS */
I 81

E 83
I 83
#endif
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
	case TELOPT_ENCRYPT:
		if (SB_EOF())
			return;
		switch(SB_GET()) {
		case ENCRYPT_START:
			if (my_want_state_is_dont(TELOPT_ENCRYPT))
				return;
D 84
			encrypt_start();
E 84
I 84
			encrypt_start(subpointer, SB_LEN());
E 84
			break;
		case ENCRYPT_END:
			if (my_want_state_is_dont(TELOPT_ENCRYPT))
				return;
			encrypt_end();
			break;
		case ENCRYPT_SUPPORT:
			if (my_want_state_is_wont(TELOPT_ENCRYPT))
				return;
			encrypt_support(subpointer, SB_LEN());
			break;
		case ENCRYPT_REQSTART:
			if (my_want_state_is_wont(TELOPT_ENCRYPT))
				return;
D 84
			encrypt_request_start();
E 84
I 84
			encrypt_request_start(subpointer, SB_LEN());
E 84
			break;
		case ENCRYPT_REQEND:
			if (my_want_state_is_wont(TELOPT_ENCRYPT))
				return;
			/*
			 * We can always send an REQEND so that we cannot
			 * get stuck encrypting.  We should only get this
			 * if we have been able to get in the correct mode
			 * anyhow.
			 */
			encrypt_request_end();
			break;
		case ENCRYPT_IS:
			if (my_want_state_is_dont(TELOPT_ENCRYPT))
				return;
			encrypt_is(subpointer, SB_LEN());
			break;
		case ENCRYPT_REPLY:
			if (my_want_state_is_wont(TELOPT_ENCRYPT))
				return;
			encrypt_reply(subpointer, SB_LEN());
I 84
			break;
		case ENCRYPT_ENC_KEYID:
			if (my_want_state_is_dont(TELOPT_ENCRYPT))
				return;
			encrypt_enc_keyid(subpointer, SB_LEN());
			break;
		case ENCRYPT_DEC_KEYID:
			if (my_want_state_is_wont(TELOPT_ENCRYPT))
				return;
			encrypt_dec_keyid(subpointer, SB_LEN());
E 84
			break;
		default:
			break;
		}
		break;
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83
E 81
E 79
E 72
E 70
    default:
	break;
    }
}
I 72

D 83
static char str_lm[] = { IAC, SB, TELOPT_LINEMODE, 0, 0, IAC, SE };
E 83
I 83
static unsigned char str_lm[] = { IAC, SB, TELOPT_LINEMODE, 0, 0, IAC, SE };
E 83

I 83
    void
E 83
lm_will(cmd, len)
D 82
char *cmd;
E 82
I 82
D 83
unsigned char *cmd;
E 83
I 83
    unsigned char *cmd;
    int len;
E 83
E 82
{
I 81
    if (len < 1) {
/*@*/	printf("lm_will: no command!!!\n");	/* Should not happen... */
	return;
    }
E 81
    switch(cmd[0]) {
    case LM_FORWARDMASK:	/* We shouldn't ever get this... */
    default:
	str_lm[3] = DONT;
	str_lm[4] = cmd[0];
	if (NETROOM() > sizeof(str_lm)) {
	    ring_supply_data(&netoring, str_lm, sizeof(str_lm));
	    printsub('>', &str_lm[2], sizeof(str_lm)-2);
	}
/*@*/	else printf("lm_will: not enough room in buffer\n");
	break;
    }
}

I 83
    void
E 83
lm_wont(cmd, len)
D 82
char *cmd;
E 82
I 82
D 83
unsigned char *cmd;
E 83
I 83
    unsigned char *cmd;
    int len;
E 83
E 82
{
I 81
    if (len < 1) {
/*@*/	printf("lm_wont: no command!!!\n");	/* Should not happen... */
	return;
    }
E 81
    switch(cmd[0]) {
    case LM_FORWARDMASK:	/* We shouldn't ever get this... */
    default:
	/* We are always DONT, so don't respond */
	return;
    }
}
D 73

int linemode;
E 73

I 83
    void
E 83
lm_do(cmd, len)
D 82
char *cmd;
E 82
I 82
D 83
unsigned char *cmd;
E 83
I 83
    unsigned char *cmd;
    int len;
E 83
E 82
{
I 81
    if (len < 1) {
/*@*/	printf("lm_do: no command!!!\n");	/* Should not happen... */
	return;
    }
E 81
    switch(cmd[0]) {
    case LM_FORWARDMASK:
    default:
	str_lm[3] = WONT;
	str_lm[4] = cmd[0];
	if (NETROOM() > sizeof(str_lm)) {
	    ring_supply_data(&netoring, str_lm, sizeof(str_lm));
	    printsub('>', &str_lm[2], sizeof(str_lm)-2);
	}
/*@*/	else printf("lm_do: not enough room in buffer\n");
	break;
    }
}

I 83
    void
E 83
lm_dont(cmd, len)
D 82
char *cmd;
E 82
I 82
D 83
unsigned char *cmd;
E 83
I 83
    unsigned char *cmd;
    int len;
E 83
E 82
{
I 81
    if (len < 1) {
/*@*/	printf("lm_dont: no command!!!\n");	/* Should not happen... */
	return;
    }
E 81
    switch(cmd[0]) {
    case LM_FORWARDMASK:
    default:
	/* we are always WONT, so don't respond */
	break;
    }
}

D 83
static char str_lm_mode[] = { IAC, SB, TELOPT_LINEMODE, LM_MODE, 0, IAC, SE };
E 83
I 83
static unsigned char str_lm_mode[] = {
	IAC, SB, TELOPT_LINEMODE, LM_MODE, 0, IAC, SE
};
E 83

I 83
	void
E 83
lm_mode(cmd, len, init)
D 83
char *cmd;
int len, init;
E 83
I 83
	unsigned char *cmd;
	int len, init;
E 83
{
	if (len != 1)
		return;
D 81
	if ((linemode&(MODE_EDIT|MODE_TRAPSIG)) == *cmd)
E 81
I 81
	if ((linemode&MODE_MASK&~MODE_ACK) == *cmd)
E 81
		return;
	if (*cmd&MODE_ACK)
		return;
D 81
	linemode = (*cmd&(MODE_EDIT|MODE_TRAPSIG));
E 81
I 81
	linemode = *cmd&(MODE_MASK&~MODE_ACK);
E 81
	str_lm_mode[4] = linemode;
	if (!init)
	    str_lm_mode[4] |= MODE_ACK;
	if (NETROOM() > sizeof(str_lm_mode)) {
	    ring_supply_data(&netoring, str_lm_mode, sizeof(str_lm_mode));
	    printsub('>', &str_lm_mode[2], sizeof(str_lm_mode)-2);
	}
/*@*/	else printf("lm_mode: not enough room in buffer\n");
	setconnmode(0);	/* set changed mode */
}

E 72
E 44
D 39

E 39
I 39
D 49

E 39
/*
D 38
 * Set the escape character.
E 38
I 38
D 41
 * Check to see if any out-of-band data exists on a socket (for
 * Telnet "synch" processing).
E 38
 */
D 38
setescape(argc, argv)
	int argc;
	char *argv[];
{
	register char *arg;
	char buf[50];
E 38

D 38
	if (argc > 2)
		arg = argv[1];
	else {
		printf("new escape character: ");
		gets(buf);
		arg = buf;
	}
	if (arg[0] != '\0')
		escape = arg[0];
	printf("Escape character is '%s'.\n", control(escape));
I 15
	fflush(stdout);
E 15
}

I 2
/*VARARGS*/
setoptions()
E 38
I 38
int
stilloob(s)
int	s;		/* socket number */
E 38
{
I 38
D 40
    struct timeval *timeout = { 0 };
    long	excepts = (1<<s);
E 40
I 40
    static struct timeval timeout = { 0 };
    fd_set	excepts;
    int value;
E 40
E 38
I 15

E 15
D 38
	showoptions = !showoptions;
D 32
	printf("%s show option processing.\n", showoptions ? "Will" : "Wont");
E 32
I 32
	printf("%s show option processing.\n", showoptions ? "Will" : "Won't");
E 32
I 15
	fflush(stdout);
E 38
I 38
D 40
    if (select(s+1, 0, 0, &excepts, timeout) < 0) {
E 40
I 40
    do {
	FD_ZERO(&excepts);
	FD_SET(s, &excepts);
	value = select(s+1, 0, 0, &excepts, &timeout);
    } while ((value >= 0) || ((value == -1) && (errno = EINTR)));

    if (value < 0) {
E 40
	perror("select");
	quit();
    }
D 40
    if (excepts) {
E 40
I 40
    if (FD_ISSET(s, &excepts)) {
E 40
	return 1;
    } else {
	return 0;
    }
E 38
}

D 38
/*VARARGS*/
setcrmod()
{

	crmod = !crmod;
D 32
	printf("%s map carriage return on output.\n", crmod ? "Will" : "Wont");
E 32
I 32
	printf("%s map carriage return on output.\n", crmod ? "Will" : "Won't");
E 32
I 16
	fflush(stdout);
}

/*VARARGS*/
setdebug()
{

D 27
	debug = !debug;
E 27
I 27
	debug = debug ? 0 : 1;
E 27
	printf("%s turn on socket level debugging.\n",
D 32
		debug ? "Will" : "Wont");
E 32
I 32
		debug ? "Will" : "Won't");
E 32
E 16
	fflush(stdout);
I 18
D 26
	if (debug && setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
E 26
I 26
D 27
	if (debug && net > 0 && setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
E 27
I 27
	if (net > 0 &&
	    setsockopt(net, SOL_SOCKET, SO_DEBUG, &debug, sizeof(debug)) < 0)
E 27
E 26
		perror("setsockopt (SO_DEBUG)");
I 29
}

I 37
/*VARARGS*/
static
setprintnet()
{

	printnet = !printnet;
	printf("%s turn on printing of raw network traffic.\n",
		printnet ? "Will" : "Wont");
}

E 37
sendesc()
{
	*nfrontp++ = escape;
}

ayt()
{
	*nfrontp++ = IAC;
	*nfrontp++ = AYT;
}

intp()
{
	*nfrontp++ = IAC;
	*nfrontp++ = IP;
E 29
E 18
E 15
}

E 38
E 2
/*
 * Construct a control character sequence
 * for a special character.
 */
char *
control(c)
	register int c;
{
	static char buf[3];

	if (c == 0177)
		return ("^?");
	if (c >= 040) {
		buf[0] = c;
		buf[1] = 0;
	} else {
		buf[0] = '^';
		buf[1] = '@'+c;
		buf[2] = 0;
	}
	return (buf);
}

D 38
struct cmd *
getcmd(name)
	register char *name;
{
	register char *p, *q;
	register struct cmd *c, *found;
	register int nmatches, longest;

	longest = 0;
	nmatches = 0;
	found = 0;
	for (c = cmdtab; p = c->name; c++) {
		for (q = name; *q == *p++; q++)
			if (*q == 0)		/* exact match? */
				return (c);
		if (!*q) {			/* the name was a prefix */
			if (q - name > longest) {
				longest = q - name;
				nmatches = 1;
				found = c;
			} else if (q - name == longest)
				nmatches++;
		}
	}
	if (nmatches > 1)
		return ((struct cmd *)-1);
	return (found);
}

E 38
D 39
deadpeer()
{
D 20
	sigset(SIGPIPE, deadpeer);
E 20
D 11
	mode(0);
E 11
I 11
	(void) mode(0);
E 11
	longjmp(peerdied, -1);
}

intr()
{
D 20
	sigset(SIGINT, intr);
E 20
D 11
	mode(0);
E 11
I 11
	(void) mode(0);
E 11
	longjmp(toplevel, -1);
}

E 39
D 38
ttyflush(fd)
E 38
I 38
ttyflush()
E 38
{
D 38
	int n;
E 38
I 38
    int n;
E 38

D 38
	if ((n = tfrontp - tbackp) > 0)
		n = write(fd, tbackp, n);
D 9
	if (n < 0 && errno == EWOULDBLOCK)
		n = 0;
E 9
I 9
	if (n < 0)
		return;
E 9
	tbackp += n;
	if (tbackp == tfrontp)
		tbackp = tfrontp = ttyobuf;
E 38
I 38
    if ((n = tfrontp - tbackp) > 0) {
	if (!flushing) {
	    n = write(tout, tbackp, n);
	} else {
	    ioctl(fileno(stdout), TIOCFLUSH, 0);
	}
    }
    if (n < 0) {
	return;
    }
    tbackp += n;
    if (tbackp == tfrontp) {
	tbackp = tfrontp = ttyobuf;
    }
E 38
}

netflush(fd)
{
D 38
	int n;
E 38
I 38
    int n;
E 38

D 38
	if ((n = nfrontp - nbackp) > 0)
		n = write(fd, nbackp, n);
D 7
	if (n < 0 && errno == EWOULDBLOCK)
E 7
I 7
	if (n < 0) {
		if (errno != ENOBUFS && errno != EWOULDBLOCK) {
D 11
			mode(0);
E 11
I 11
			(void) mode(0);
E 11
D 9
			perror(host_name);
E 9
I 9
D 10
			perror(host->h_name);
E 10
I 10
			perror(hostname);
E 10
E 9
			close(fd);
			longjmp(peerdied, -1);
			/*NOTREACHED*/
		}
E 7
		n = 0;
E 38
I 38
    if ((n = nfrontp - nbackp) > 0) {
	if (!neturg) {
	    n = write(fd, nbackp, n);	/* normal write */
	} else {
	    n = neturg - nbackp;
D 40
	    n = send(fd, nbackp, n, MSG_OOB);	/* URGENT data (SYNCH) */
E 40
I 40
	    /*
	     * In 4.2 (and 4.3) systems, there is some question about
	     * what byte in a sendOOB operation is the "OOB" data.
	     * To make ourselves compatible, we only send ONE byte
	     * out of band, the one WE THINK should be OOB (though
	     * we really have more the TCP philosophy of urgent data
	     * rather than the Unix philosophy of OOB data).
	     */
	    if (n > 1) {
		n = send(fd, nbackp, n-1, 0);	/* send URGENT all by itself */
	    } else {
		n = send(fd, nbackp, n, MSG_OOB);	/* URGENT data */
	    }
E 40
E 38
I 7
	}
I 37
D 38
	if (printnet) {
		Dump('>', nbackp, n);
E 38
I 38
    }
    if (n < 0) {
	if (errno != ENOBUFS && errno != EWOULDBLOCK) {
D 39
	    (void) mode(0);
E 39
I 39
	    setcommandmode();
E 39
	    perror(hostname);
	    close(fd);
	    neturg = 0;
	    longjmp(peerdied, -1);
	    /*NOTREACHED*/
E 38
	}
E 37
E 7
D 38
	nbackp += n;
	if (nbackp == nfrontp)
		nbackp = nfrontp = netobuf;
E 38
I 38
	n = 0;
    }
    if (netdata && n) {
	Dump('>', nbackp, n);
    }
    nbackp += n;
    if (nbackp >= neturg) {
	neturg = 0;
    }
    if (nbackp == nfrontp) {
	nbackp = nfrontp = netobuf;
    }
E 38
I 2
}
I 37

static
Dump(direction, buffer, length)
char	direction;
char	*buffer;
int	length;
{
#   define BYTES_PER_LINE	32
#   define min(x,y)	((x<y)? x:y)
    char *pThis;
    int offset;

    offset = 0;

    while (length) {
	/* print one line */
	fprintf(NetTrace, "%c 0x%x\t", direction, offset);
	pThis = buffer;
	buffer = buffer+min(length, BYTES_PER_LINE);
	while (pThis < buffer) {
	    fprintf(NetTrace, "%.2x", (*pThis)&0xff);
	    pThis++;
	}
	fprintf(NetTrace, "\n");
	length -= BYTES_PER_LINE;
	offset += BYTES_PER_LINE;
	if (length < 0) {
	    return;
	}
	/* find next unique line */
    }
}

E 37

D 5
printoption(direction, fmt, option)
E 5
I 5
/*VARARGS*/
printoption(direction, fmt, option, what)
E 5
	char *direction, *fmt;
D 5
	int option;
E 5
I 5
	int option, what;
E 5
{
I 9
	if (!showoptions)
		return;
E 9
	printf("%s ", direction);
	if (fmt == doopt)
		fmt = "do";
	else if (fmt == dont)
		fmt = "dont";
	else if (fmt == will)
		fmt = "will";
	else if (fmt == wont)
		fmt = "wont";
	else
		fmt = "???";
	if (option < TELOPT_SUPDUP)
D 5
		printf("%s %s\r\n", fmt, telopts[option]);
E 5
I 5
		printf("%s %s", fmt, telopts[option]);
E 5
	else
D 5
		printf("%s %d\r\n", fmt, option);
E 5
I 5
		printf("%s %d", fmt, option);
	if (*direction == '<') {
		printf("\r\n");
		return;
	}
	printf(" (%s)\r\n", what ? "reply" : "don't reply");
I 38
}

/*
E 41
 *	The following are data structures and routines for
 *	the "send" command.
 *
 */
 
struct sendlist {
    char	*name;		/* How user refers to it (case independent) */
    int		what;		/* Character to be sent (<0 ==> special) */
    char	*help;		/* Help information (0 ==> no help) */
    int		(*routine)();	/* Routine to perform (for special ops) */
};
E 49
D 53

I 41
D 49
/*ARGSUSED*/
E 41
dosynch(s)
struct sendlist *s;
E 49
I 49
#if	defined(TN3270)
static void
SetIn3270()
E 49
{
D 43
    /* XXX We really should purge the buffer to the network */
E 43
I 43
D 49
    netclear();			/* clear the path to the network */
E 43
    NET2ADD(IAC, DM);
D 41
    neturg = NETLOC();
E 41
I 41
    neturg = NETLOC()-1;	/* Some systems are off by one XXX */
E 41
}

I 42
doflush()
{
D 43
    /* This shouldn't really be here... */
E 43
    NET2ADD(IAC, DO);
    NETADD(TELOPT_TM);
D 44
    printoption("SENT", doopt, TELOPT_TM);
E 44
    flushline = 1;
    flushout = 1;
    ttyflush();
I 44
    /* do printoption AFTER flush, otherwise the output gets tossed... */
    printoption("<SENT", doopt, TELOPT_TM);
E 44
}

E 42
D 41
sendesc()
{
D 39
	NETADD(escape);
E 39
I 39
    NETADD(escape);
E 39
}

ayt()
{
D 39
	NET2ADD(IAC, AYT);
E 39
I 39
    NET2ADD(IAC, AYT);
E 39
}

E 41
intp()
{
D 39
	NET2ADD(IAC, IP);
E 39
I 39
    NET2ADD(IAC, IP);
I 42
    if (autoflush) {
	doflush();
E 49
I 49
    if (Sent3270TerminalType && myopts[TELOPT_BINARY]
			    && hisopts[TELOPT_BINARY] && !donebinarytoggle) {
	if (!In3270) {
	    In3270 = 1;
	    Init3270();		/* Initialize 3270 functions */
	    /* initialize terminal key mapping */
	    InitTerminal();	/* Start terminal going */
	    setconnmode();
	}
    } else {
	if (In3270) {
	    StopScreen(1);
	    In3270 = 0;
	    Stop3270();		/* Tell 3270 we aren't here anymore */
	    setconnmode();
	}
E 49
    }
D 49
    if (autosynch) {
	dosynch();
    }
E 49
E 42
E 39
}
I 49
#endif	/* defined(TN3270) */
E 53

I 65
D 66
/*
 * What to do with CR's in the input data stream which are
 * followed by a null.
 */
#define	CR_FOLLOWED_BY_NULL() \
		    TTYADD('\r');
E 66
E 65
E 49

I 72
/*
 * slc()
 * Handle special character suboption of LINEMODE.
 */

struct spc {
D 76
	char val;
	char *valp;
E 76
I 76
	cc_t val;
	cc_t *valp;
E 76
	char flags;	/* Current flags & level */
	char mylevel;	/* Maximum level & flags */
} spc_data[NSLC+1];

#define SLC_IMPORT	0
#define	SLC_EXPORT	1
#define SLC_RVALUE	2
static int slc_mode = SLC_EXPORT;

I 83
	void
E 83
slc_init()
{
	register struct spc *spcp;
D 76
	extern char *tcval();
E 76
I 76
D 83
	extern cc_t *tcval();
E 83
E 76

	localchars = 1;
	for (spcp = spc_data; spcp < &spc_data[NSLC+1]; spcp++) {
		spcp->val = 0;
		spcp->valp = 0;
		spcp->flags = spcp->mylevel = SLC_NOSUPPORT;
	}

#define	initfunc(func, flags) { \
					spcp = &spc_data[func]; \
					if (spcp->valp = tcval(func)) { \
					    spcp->val = *spcp->valp; \
					    spcp->mylevel = SLC_VARIABLE|flags; \
					} else { \
					    spcp->val = 0; \
					    spcp->mylevel = SLC_DEFAULT; \
					} \
				    }

	initfunc(SLC_SYNCH, 0);
	/* No BRK */
	initfunc(SLC_AO, 0);
	initfunc(SLC_AYT, 0);
	/* No EOR */
	initfunc(SLC_ABORT, SLC_FLUSHIN|SLC_FLUSHOUT);
	initfunc(SLC_EOF, 0);
D 75
#ifndef	CRAY
E 75
I 75
#ifndef	SYSV_TERMIO
E 75
	initfunc(SLC_SUSP, SLC_FLUSHIN);
#endif
	initfunc(SLC_EC, 0);
	initfunc(SLC_EL, 0);
D 75
#ifndef	CRAY
E 75
I 75
#ifndef	SYSV_TERMIO
E 75
	initfunc(SLC_EW, 0);
	initfunc(SLC_RP, 0);
	initfunc(SLC_LNEXT, 0);
#endif
	initfunc(SLC_XON, 0);
	initfunc(SLC_XOFF, 0);
D 75
#ifdef	CRAY
E 75
I 75
#ifdef	SYSV_TERMIO
E 75
	spc_data[SLC_XON].mylevel = SLC_CANTCHANGE;
	spc_data[SLC_XOFF].mylevel = SLC_CANTCHANGE;
#endif
D 81
	/* No FORW1 */
E 81
I 81
	initfunc(SLC_FORW1, 0);
#ifdef	USE_TERMIO
	initfunc(SLC_FORW2, 0);
E 81
	/* No FORW2 */
I 81
#endif
E 81

	initfunc(SLC_IP, SLC_FLUSHIN|SLC_FLUSHOUT);
#undef	initfunc

	if (slc_mode == SLC_EXPORT)
		slc_export();
	else
		slc_import(1);

}

I 83
    void
E 83
slcstate()
{
    printf("Special characters are %s values\n",
		slc_mode == SLC_IMPORT ? "remote default" :
		slc_mode == SLC_EXPORT ? "local" :
					 "remote");
}

I 83
    void
E 83
slc_mode_export()
{
    slc_mode = SLC_EXPORT;
    if (my_state_is_will(TELOPT_LINEMODE))
	slc_export();
}

I 83
    void
E 83
slc_mode_import(def)
I 83
    int def;
E 83
{
    slc_mode = def ? SLC_IMPORT : SLC_RVALUE;
    if (my_state_is_will(TELOPT_LINEMODE))
	slc_import(def);
}

D 83
char slc_import_val[] = {
E 83
I 83
unsigned char slc_import_val[] = {
E 83
	IAC, SB, TELOPT_LINEMODE, LM_SLC, 0, SLC_VARIABLE, 0, IAC, SE
};
D 83
char slc_import_def[] = {
E 83
I 83
unsigned char slc_import_def[] = {
E 83
	IAC, SB, TELOPT_LINEMODE, LM_SLC, 0, SLC_DEFAULT, 0, IAC, SE
};

I 83
    void
E 83
slc_import(def)
D 83
int def;
E 83
I 83
    int def;
E 83
{
    if (NETROOM() > sizeof(slc_import_val)) {
	if (def) {
	    ring_supply_data(&netoring, slc_import_def, sizeof(slc_import_def));
	    printsub('>', &slc_import_def[2], sizeof(slc_import_def)-2);
	} else {
	    ring_supply_data(&netoring, slc_import_val, sizeof(slc_import_val));
	    printsub('>', &slc_import_val[2], sizeof(slc_import_val)-2);
	}
    }
/*@*/ else printf("slc_import: not enough room\n");
}

I 83
    void
E 83
slc_export()
{
    register struct spc *spcp;

    TerminalDefaultChars();

    slc_start_reply();
    for (spcp = &spc_data[1]; spcp < &spc_data[NSLC+1]; spcp++) {
	if (spcp->mylevel != SLC_NOSUPPORT) {
D 82
	    spcp->flags = spcp->mylevel;
E 82
I 82
	    if (spcp->val == (cc_t)(_POSIX_VDISABLE))
		spcp->flags = SLC_NOSUPPORT;
	    else
		spcp->flags = spcp->mylevel;
E 82
	    if (spcp->valp)
		spcp->val = *spcp->valp;
D 82
	    slc_add_reply(spcp - spc_data, spcp->mylevel, spcp->val);
E 82
I 82
	    slc_add_reply(spcp - spc_data, spcp->flags, spcp->val);
E 82
	}
    }
    slc_end_reply();
D 83
    if (slc_update())
	setconnmode(1);	/* set the  new character values */
E 83
I 83
    (void)slc_update();
    setconnmode(1);	/* Make sure the character values are set */
E 83
}

I 83
	void
E 83
slc(cp, len)
D 83
register char *cp;
int len;
E 83
I 83
	register unsigned char *cp;
	int len;
E 83
{
	register struct spc *spcp;
	register int func,level;

	slc_start_reply();

	for (; len >= 3; len -=3, cp +=3) {

		func = cp[SLC_FUNC];

		if (func == 0) {
			/*
			 * Client side: always ignore 0 function.
			 */
			continue;
		}
		if (func > NSLC) {
D 82
			if (cp[SLC_FLAGS] & SLC_LEVELBITS != SLC_NOSUPPORT)
E 82
I 82
			if ((cp[SLC_FLAGS] & SLC_LEVELBITS) != SLC_NOSUPPORT)
E 82
				slc_add_reply(func, SLC_NOSUPPORT, 0);
			continue;
		}

		spcp = &spc_data[func];

		level = cp[SLC_FLAGS]&(SLC_LEVELBITS|SLC_ACK);

D 76
		if ((cp[SLC_VALUE] == spcp->val) &&
E 76
I 76
		if ((cp[SLC_VALUE] == (unsigned char)spcp->val) &&
E 76
		    ((level&SLC_LEVELBITS) == (spcp->flags&SLC_LEVELBITS))) {
			continue;
		}

		if (level == (SLC_DEFAULT|SLC_ACK)) {
			/*
			 * This is an error condition, the SLC_ACK
			 * bit should never be set for the SLC_DEFAULT
			 * level.  Our best guess to recover is to
			 * ignore the SLC_ACK bit.
			 */
			cp[SLC_FLAGS] &= ~SLC_ACK;
		}

		if (level == ((spcp->flags&SLC_LEVELBITS)|SLC_ACK)) {
D 76
			spcp->val = cp[SLC_VALUE];
E 76
I 76
			spcp->val = (cc_t)cp[SLC_VALUE];
E 76
			spcp->flags = cp[SLC_FLAGS];	/* include SLC_ACK */
			continue;
		}

		level &= ~SLC_ACK;

		if (level <= (spcp->mylevel&SLC_LEVELBITS)) {
			spcp->flags = cp[SLC_FLAGS]|SLC_ACK;
D 76
			spcp->val = cp[SLC_VALUE];
E 76
I 76
			spcp->val = (cc_t)cp[SLC_VALUE];
E 76
		}
		if (level == SLC_DEFAULT) {
			if ((spcp->mylevel&SLC_LEVELBITS) != SLC_DEFAULT)
				spcp->flags = spcp->mylevel;
			else
				spcp->flags = SLC_NOSUPPORT;
		}
		slc_add_reply(func, spcp->flags, spcp->val);
	}
	slc_end_reply();
	if (slc_update())
		setconnmode(1);	/* set the  new character values */
}

I 83
    void
E 83
slc_check()
{
    register struct spc *spcp;

    slc_start_reply();
    for (spcp = &spc_data[1]; spcp < &spc_data[NSLC+1]; spcp++) {
	if (spcp->valp && spcp->val != *spcp->valp) {
	    spcp->val = *spcp->valp;
D 82
	    slc_add_reply(spcp - spc_data, spcp->mylevel, spcp->val);
E 82
I 82
	    if (spcp->val == (cc_t)(_POSIX_VDISABLE))
		spcp->flags = SLC_NOSUPPORT;
	    else
		spcp->flags = spcp->mylevel;
	    slc_add_reply(spcp - spc_data, spcp->flags, spcp->val);
E 82
	}
    }
    slc_end_reply();
    setconnmode(1);
}


unsigned char slc_reply[128];
unsigned char *slc_replyp;
I 83

	void
E 83
slc_start_reply()
{
	slc_replyp = slc_reply;
	*slc_replyp++ = IAC;
	*slc_replyp++ = SB;
	*slc_replyp++ = TELOPT_LINEMODE;
	*slc_replyp++ = LM_SLC;
}

I 83
	void
E 83
slc_add_reply(func, flags, value)
D 83
char func;
char flags;
D 76
char value;
E 76
I 76
cc_t value;
E 83
I 83
	unsigned char func;
	unsigned char flags;
	cc_t value;
E 83
E 76
{
	if ((*slc_replyp++ = func) == IAC)
		*slc_replyp++ = IAC;
	if ((*slc_replyp++ = flags) == IAC)
		*slc_replyp++ = IAC;
D 76
	if ((*slc_replyp++ = value) == IAC)
E 76
I 76
	if ((*slc_replyp++ = (unsigned char)value) == IAC)
E 76
		*slc_replyp++ = IAC;
}

I 83
    void
E 83
slc_end_reply()
{
D 81
    register char *cp;
E 81
    register int len;

    *slc_replyp++ = IAC;
    *slc_replyp++ = SE;
    len = slc_replyp - slc_reply;
    if (len <= 6)
	return;
    if (NETROOM() > len) {
	ring_supply_data(&netoring, slc_reply, slc_replyp - slc_reply);
	printsub('>', &slc_reply[2], slc_replyp - slc_reply - 2);
    }
/*@*/else printf("slc_end_reply: not enough room\n");
}

I 83
	int
E 83
slc_update()
{
	register struct spc *spcp;
	int need_update = 0;

	for (spcp = &spc_data[1]; spcp < &spc_data[NSLC+1]; spcp++) {
		if (!(spcp->flags&SLC_ACK))
			continue;
		spcp->flags &= ~SLC_ACK;
		if (spcp->valp && (*spcp->valp != spcp->val)) {
			*spcp->valp = spcp->val;
			need_update = 1;
		}
	}
	return(need_update);
}

I 86
D 90
#ifdef	ENV_HACK
E 90
I 90
#ifdef	OLD_ENVIRON
# ifdef	ENV_HACK
E 90
/*
 * Earlier version of telnet/telnetd from the BSD code had
 * the definitions of VALUE and VAR reversed.  To ensure
 * maximum interoperability, we assume that the server is
 * an older BSD server, until proven otherwise.  The newer
 * BSD servers should be able to handle either definition,
 * so it is better to use the wrong values if we don't
 * know what type of server it is.
 */
int env_auto = 1;
D 90
int env_var = ENV_VALUE;
int env_value = ENV_VAR;
#else
#define env_var ENV_VAR
#define env_value ENV_VALUE
E 90
I 90
int old_env_var = OLD_ENV_VAR;
int old_env_value = OLD_ENV_VALUE;
# else
#  define old_env_var OLD_ENV_VAR
#  define old_env_value OLD_ENV_VALUE
# endif
E 90
#endif

E 86
I 83
	void
E 83
I 81
env_opt(buf, len)
D 83
register char *buf;
register int len;
E 83
I 83
	register unsigned char *buf;
	register int len;
E 83
{
D 83
	register char *ep = 0, *epc = 0;
E 83
I 83
	register unsigned char *ep = 0, *epc = 0;
E 83
	register int i;

D 82
	switch(buf[0]) {
E 82
I 82
	switch(buf[0]&0xff) {
E 82
	case TELQUAL_SEND:
		env_opt_start();
		if (len == 1) {
			env_opt_add(NULL);
		} else for (i = 1; i < len; i++) {
D 82
			switch (buf[i]) {
E 82
I 82
			switch (buf[i]&0xff) {
I 86
D 90
			case ENV_VAR:
#ifdef	ENV_HACK
				if (env_auto) {
					/* The server has correct definitions */
					env_var = ENV_VAR;
					env_value = ENV_VALUE;
E 90
I 90
#ifdef	OLD_ENVIRON
			case OLD_ENV_VAR:
# ifdef	ENV_HACK
				if (telopt_environ == TELOPT_OLD_ENVIRON
				    && env_auto) {
					/* Server has the same definitions */
					old_env_var = OLD_ENV_VAR;
					old_env_value = OLD_ENV_VALUE;
E 90
				}
				/* FALL THROUGH */
D 90
#endif
E 86
E 82
			case ENV_VALUE:
E 90
I 90
# endif
			case OLD_ENV_VALUE:
E 90
I 86
				/*
D 90
				 * Although ENV_VALUE is not legal, we will
E 90
I 90
				 * Although OLD_ENV_VALUE is not legal, we will
E 90
				 * still recognize it, just in case it is an
				 * old server that has VAR & VALUE mixed up...
				 */
				/* FALL THROUGH */
I 90
#else
			case NEW_ENV_VAR:
#endif
E 90
			case ENV_USERVAR:
E 86
				if (ep) {
					*epc = 0;
					env_opt_add(ep);
				}
				ep = epc = &buf[i+1];
				break;
			case ENV_ESC:
				i++;
				/*FALL THROUGH*/
			default:
				if (epc)
					*epc++ = buf[i];
				break;
			}
D 86
			if (ep) {
				*epc = 0;
				env_opt_add(ep);
			}
E 86
		}
I 86
		if (ep) {
			*epc = 0;
			env_opt_add(ep);
		}
E 86
		env_opt_end(1);
		break;

	case TELQUAL_IS:
	case TELQUAL_INFO:
		/* Ignore for now.  We shouldn't get it anyway. */
		break;

	default:
		break;
	}
}

#define	OPT_REPLY_SIZE	256
unsigned char *opt_reply;
unsigned char *opt_replyp;
unsigned char *opt_replyend;

I 83
	void
E 83
env_opt_start()
{
D 83
	extern char *realloc();
	extern char *malloc();

E 83
	if (opt_reply)
		opt_reply = (unsigned char *)realloc(opt_reply, OPT_REPLY_SIZE);
	else
		opt_reply = (unsigned char *)malloc(OPT_REPLY_SIZE);
	if (opt_reply == NULL) {
/*@*/		printf("env_opt_start: malloc()/realloc() failed!!!\n");
		opt_reply = opt_replyp = opt_replyend = NULL;
		return;
	}
	opt_replyp = opt_reply;
	opt_replyend = opt_reply + OPT_REPLY_SIZE;
	*opt_replyp++ = IAC;
	*opt_replyp++ = SB;
D 90
	*opt_replyp++ = TELOPT_ENVIRON;
E 90
I 90
	*opt_replyp++ = telopt_environ;
E 90
	*opt_replyp++ = TELQUAL_IS;
}

I 83
	void
E 83
env_opt_start_info()
{
	env_opt_start();
	if (opt_replyp)
	    opt_replyp[-1] = TELQUAL_INFO;
}

I 83
	void
E 83
env_opt_add(ep)
D 83
register char *ep;
E 83
I 83
	register unsigned char *ep;
E 83
{
D 83
	register char *vp, c;
	extern char *realloc();
	extern char *env_default();
E 83
I 83
	register unsigned char *vp, c;
E 83

	if (opt_reply == NULL)		/*XXX*/
		return;			/*XXX*/

	if (ep == NULL || *ep == '\0') {
D 85
		env_default(1);
		while (ep = env_default(0))
E 85
I 85
		/* Send user defined variables first. */
		env_default(1, 0);
		while (ep = env_default(0, 0))
E 85
			env_opt_add(ep);
I 85

		/* Now add the list of well know variables.  */
		env_default(1, 1);
		while (ep = env_default(0, 1))
			env_opt_add(ep);
E 85
		return;
	}
	vp = env_getvalue(ep);
D 83
	if (opt_replyp + (vp?strlen(vp):0) + strlen(ep) + 6 > opt_replyend) {
E 83
I 83
	if (opt_replyp + (vp ? strlen((char *)vp) : 0) +
				strlen((char *)ep) + 6 > opt_replyend)
	{
E 83
		register int len;
		opt_replyend += OPT_REPLY_SIZE;
		len = opt_replyend - opt_reply;
		opt_reply = (unsigned char *)realloc(opt_reply, len);
		if (opt_reply == NULL) {
/*@*/			printf("env_opt_add: realloc() failed!!!\n");
			opt_reply = opt_replyp = opt_replyend = NULL;
			return;
		}
		opt_replyp = opt_reply + len - (opt_replyend - opt_replyp);
		opt_replyend = opt_reply + len;
	}
D 85
	*opt_replyp++ = ENV_VAR;
E 85
I 85
	if (opt_welldefined(ep))
D 86
		*opt_replyp++ = ENV_VAR;
E 86
I 86
D 90
		*opt_replyp++ = env_var;
E 90
I 90
#ifdef	OLD_ENVIRON
		if (telopt_environ == TELOPT_OLD_ENVIRON)
			*opt_replyp++ = old_env_var;
		else
#endif
			*opt_replyp++ = NEW_ENV_VAR;
E 90
E 86
	else
		*opt_replyp++ = ENV_USERVAR;
E 85
	for (;;) {
		while (c = *ep++) {
D 82
			switch(c) {
E 82
I 82
			switch(c&0xff) {
E 82
			case IAC:
				*opt_replyp++ = IAC;
				break;
D 90
			case ENV_VALUE:
			case ENV_VAR:
E 90
I 90
			case NEW_ENV_VAR:
			case NEW_ENV_VALUE:
E 90
			case ENV_ESC:
I 85
			case ENV_USERVAR:
E 85
				*opt_replyp++ = ENV_ESC;
				break;
			}
			*opt_replyp++ = c;
		}
		if (ep = vp) {
D 86
			*opt_replyp++ = ENV_VALUE;
E 86
I 86
D 90
			*opt_replyp++ = env_value;
E 90
I 90
#ifdef	OLD_ENVIRON
			if (telopt_environ == TELOPT_OLD_ENVIRON)
				*opt_replyp++ = old_env_value;
			else
#endif
				*opt_replyp++ = NEW_ENV_VALUE;
E 90
E 86
			vp = NULL;
		} else
			break;
	}
}

I 85
	int
opt_welldefined(ep)
	char *ep;
{
	if ((strcmp(ep, "USER") == 0) ||
	    (strcmp(ep, "DISPLAY") == 0) ||
	    (strcmp(ep, "PRINTER") == 0) ||
	    (strcmp(ep, "SYSTEMTYPE") == 0) ||
	    (strcmp(ep, "JOB") == 0) ||
	    (strcmp(ep, "ACCT") == 0))
		return(1);
	return(0);
}
E 85
I 83
	void
E 83
env_opt_end(emptyok)
D 83
register int emptyok;
E 83
I 83
	register int emptyok;
E 83
{
	register int len;

	len = opt_replyp - opt_reply + 2;
	if (emptyok || len > 6) {
		*opt_replyp++ = IAC;
		*opt_replyp++ = SE;
		if (NETROOM() > len) {
			ring_supply_data(&netoring, opt_reply, len);
			printsub('>', &opt_reply[2], len - 2);
		}
/*@*/		else printf("slc_end_reply: not enough room\n");
	}
	if (opt_reply) {
		free(opt_reply);
		opt_reply = opt_replyp = opt_replyend = NULL;
	}
}

E 81


E 72
I 65
D 66
/*
 * What to do with CR's in the input data stream which are
 * followed by a line feed.
 */
#define	CR_FOLLOWED_BY_LF() \
		    if (!hisopts[TELOPT_ECHO]) { \
			TTYADD('\n'); \
		    } else { \
			TTYADD('\r'); \
			TTYADD('\n'); \
		    }
E 66
E 65
I 39
D 49
sendbrk()
E 49
I 49
D 51
static void
E 51
I 51
D 61
static int
E 61
I 61
D 83
int
E 83
I 83
    int
E 83
E 61
E 51
telrcv()
E 49
{
I 41
D 42
#if	0
    /*
     * There is a question here.  Should we send a TM to flush the stream?
     * Should we also send a TELNET SYNCH also?
     */
E 41
    *nfrontp++ = IAC;
    *nfrontp++ = DO;
    *nfrontp++ = TELOPT_TM;
    flushout = 1;
D 41
    *nfrontp++ = IAC;
    *nfrontp++ = BREAK;
    flushline = 1;
E 41
    printoption("SENT", doopt, TELOPT_TM);
I 41
#endif	/* 0 */
E 42
D 49
    NET2ADD(IAC, BREAK);
D 42
    flushline = 1;
E 42
I 42
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
    }
E 42
E 41
}
E 49
I 49
    register int c;
D 51
    static int telrcv_state = TS_DATA;
#   if defined(TN3270)
    register int Scc;
    register char *Sbp;
#   endif /* defined(TN3270) */
E 51
I 51
    register int scc;
D 83
    register char *sbp;
E 83
I 83
    register unsigned char *sbp;
E 83
    int count;
    int returnValue = 0;
E 51
E 49
E 39

I 49
D 51
    while ((scc > 0) && (TTYROOM() > 2)) {
	c = *sbp++ & 0xff, scc--;
E 51
I 51
    scc = 0;
    count = 0;
    while (TTYROOM() > 2) {
	if (scc == 0) {
	    if (count) {
D 52
		ring_sent_acked(&netiring, count);
E 52
I 52
		ring_consumed(&netiring, count);
E 52
		returnValue = 1;
		count = 0;
	    }
D 52
	    sbp = netiring.send;
	    scc = ring_unsent_consecutive(&netiring);
E 52
I 52
	    sbp = netiring.consume;
	    scc = ring_full_consecutive(&netiring);
E 52
	    if (scc == 0) {
		/* No more data coming in */
		break;
	    }
	}

	c = *sbp++ & 0xff, scc--; count++;
I 83
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
	if (decrypt_input)
		c = (*decrypt_input)(c);
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83

E 51
	switch (telrcv_state) {
E 49
I 39

E 39
D 49
#define	SENDQUESTION	-1
D 43
#define	SEND2QUESTION	-2
E 43
#define	SENDESCAPE	-3
E 49
I 49
	case TS_CR:
	    telrcv_state = TS_DATA;
D 65
	    if (c == '\0') {
		break;	/* Ignore \0 after CR */
	    } else if (c == '\n') {
D 55
		if (hisopts[TELOPT_ECHO] && !crmod) {
E 55
I 55
		if ((!hisopts[TELOPT_ECHO]) && !crmod) {
E 55
		    TTYADD(c);
E 65
I 65
D 66
	    switch (c) {
	    case '\0':
		if (peer_does_legal_CR == unknown) {
		    peer_does_legal_CR = yes;
E 65
		}
D 65
		break;
E 65
I 65
		if (CR_substate != already_guessed) {
			/* a "true" CR */
		    CR_FOLLOWED_BY_NULL();
		}
		last_legal_CR_followed_by = 0;	/* Adaptive if bad */
		continue;	/* Continue while loop */
	    case '\n':
		if (peer_does_legal_CR == unknown) {
		    peer_does_legal_CR = yes;
		}
		if (CR_substate != already_guessed) {
		    CR_FOLLOWED_BY_LF();
		}
		last_legal_CR_followed_by = '\n';	/* Adaptive if bad */
		continue;	/* Continue while loop */
	    default:
		peer_does_legal_CR = no;
		if (CR_substate != already_guessed) {
		    if (crmod) {
			TTYADD('\r');
			TTYADD('\n');
		    } else if (last_legal_CR_followed_by == 0) {
			CR_FOLLOWED_BY_NULL();
		    } else {
			CR_FOLLOWED_BY_LF();
		    }
		}
		break;	/* Out of this switch, but fall through ... */
E 66
I 66
	    if (c == '\0') {
		break;	/* Ignore \0 after CR */
D 71
	    } else if ((c == '\n') && (!hisopts[TELOPT_ECHO]) && !crmod) {
E 71
I 71
D 72
	    } else if ((c == '\n') && (!should_he(TELOPT_ECHO)) && !crmod) {
E 72
I 72
D 75
	    } else if ((c == '\n') && my_want_state_is_dont(TELOPT_ECHO) && !crmod) {
E 75
I 75
	    }
	    else if ((c == '\n') && my_want_state_is_dont(TELOPT_ECHO) && !crmod) {
E 75
E 72
E 71
		TTYADD(c);
		break;
E 66
E 65
	    }
D 65
	    /* Else, fall through */
E 65
I 65
D 66
	    /* fall through (from default above) */
E 66
I 66
	    /* Else, fall through */
E 66
E 65
E 49

D 49
struct sendlist Sendlist[] = {
D 43
    { "synch", SYNCH, "Perform Telnet 'Synch operation'", dosynch },
    { "brk", BREAK, "Send Telnet Break" },
	{ "break", BREAK, 0 },
    { "ip", IP, "Send Telnet Interrupt Process" },
	{ "intp", IP, 0 },
	{ "interrupt", IP, 0 },
	{ "intr", IP, 0 },
E 43
    { "ao", AO, "Send Telnet Abort output" },
D 43
	{ "abort", AO, 0 },
E 43
    { "ayt", AYT, "Send Telnet 'Are You There'" },
D 43
	{ "are", AYT, 0 },
	{ "hello", AYT, 0 },
E 43
I 43
    { "brk", BREAK, "Send Telnet Break" },
E 43
    { "ec", EC, "Send Telnet Erase Character" },
    { "el", EL, "Send Telnet Erase Line" },
I 43
    { "escape", SENDESCAPE, "Send current escape character" },
E 43
    { "ga", GA, "Send Telnet 'Go Ahead' sequence" },
D 43
	{ "go", GA, 0 },
E 43
I 43
    { "ip", IP, "Send Telnet Interrupt Process" },
E 43
    { "nop", NOP, "Send Telnet 'No operation'" },
D 43
    { "escape", SENDESCAPE, "Send current escape character" },
E 43
I 43
    { "synch", SYNCH, "Perform Telnet 'Synch operation'", dosynch },
E 43
    { "?", SENDQUESTION, "Display send options" },
D 43
	{ "help", SENDQUESTION, 0 },
    { "??", SEND2QUESTION, "Display all send options (including aliases)" },
E 43
    { 0 }
};
E 49
I 49
	case TS_DATA:
	    if (c == IAC) {
		telrcv_state = TS_IAC;
D 61
		continue;
E 61
I 61
		break;
E 61
	    }
#	    if defined(TN3270)
	    if (In3270) {
		*Ifrontp++ = c;
D 51
		Sbp = sbp;
		Scc = scc;
		while (Scc > 0) {
		    c = *Sbp++ & 0377, Scc--;
E 51
I 51
		while (scc > 0) {
		    c = *sbp++ & 0377, scc--; count++;
I 83
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
		    if (decrypt_input)
			c = (*decrypt_input)(c);
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83
E 51
		    if (c == IAC) {
			telrcv_state = TS_IAC;
D 61
			break;
E 61
I 61
D 62
			continue;
E 62
I 62
			break;
E 62
E 61
		    }
		    *Ifrontp++ = c;
		}
D 51
		sbp = Sbp;
		scc = Scc;
E 51
	    } else
#	    endif /* defined(TN3270) */
I 66
		    /*
		     * The 'crmod' hack (see following) is needed
		     * since we can't * set CRMOD on output only.
		     * Machines like MULTICS like to send \r without
		     * \n; since we must turn off CRMOD to get proper
		     * input, the mapping is done here (sigh).
		     */
E 66
D 65
		    /*
		     * The 'crmod' hack (see following) is needed
		     * since we can't * set CRMOD on output only.
		     * Machines like MULTICS like to send \r without
		     * \n; since we must turn off CRMOD to get proper
		     * input, the mapping is done here (sigh).
		     */
E 65
D 71
	    if ((c == '\r') && !hisopts[TELOPT_BINARY]) {
E 71
I 71
D 72
	    if ((c == '\r') && !should_he(TELOPT_BINARY)) {
E 72
I 72
	    if ((c == '\r') && my_want_state_is_dont(TELOPT_BINARY)) {
E 72
E 71
D 65
		if (scc > 0) {
		    c = *sbp&0xff;
		    if (c == 0) {
D 51
			sbp++, scc--;
E 51
I 51
			sbp++, scc--; count++;
E 51
			/* a "true" CR */
E 65
I 65
D 66
		telrcv_state = TS_CR;
		CR_substate = didnt_guess;
		if ((scc <= 0) && (count == ring_full_count(&netiring)))  {
		    /* We're here if this is an isolated CR */
		    if (crmod) {
			/*
			 * crmod means do this regardless of
			 * our estimation of the remote.
			 */
E 66
I 66
		if (scc > 0) {
		    c = *sbp&0xff;
I 83
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
		    if (decrypt_input)
			c = (*decrypt_input)(c);
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83
		    if (c == 0) {
			sbp++, scc--; count++;
			/* a "true" CR */
E 66
E 65
			TTYADD('\r');
I 66
D 71
		    } else if (!hisopts[TELOPT_ECHO] &&
E 71
I 71
D 72
		    } else if (!should_he(TELOPT_ECHO) &&
E 72
I 72
		    } else if (my_want_state_is_dont(TELOPT_ECHO) &&
E 72
E 71
					(c == '\n')) {
			sbp++, scc--; count++;
E 66
D 65
		    } else if (!hisopts[TELOPT_ECHO] &&
					(c == '\n')) {
D 51
			sbp++, scc--;
E 51
I 51
			sbp++, scc--; count++;
E 65
E 51
			TTYADD('\n');
D 65
		    } else {
			TTYADD('\r');
			if (crmod) {
				TTYADD('\n');
E 65
I 65
D 66
			CR_substate = already_guessed;
		    } else if (peer_does_legal_CR != yes) {
			if (last_legal_CR_followed_by == 0) {
			    CR_FOLLOWED_BY_NULL();
			} else {
			    CR_FOLLOWED_BY_LF();
E 66
I 66
		    } else {
I 83
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
D 92
		        if (decrypt_input)
E 92
I 92
			if (decrypt_input)
E 92
			    (*decrypt_input)(-1);
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88

E 83
			TTYADD('\r');
			if (crmod) {
				TTYADD('\n');
E 66
E 65
			}
D 65
		    }
		} else {
		    telrcv_state = TS_CR;
		    TTYADD('\r');
		    if (crmod) {
			    TTYADD('\n');
E 65
I 65
D 66
			CR_substate = already_guessed;
E 66
I 66
		    }
		} else {
		    telrcv_state = TS_CR;
		    TTYADD('\r');
		    if (crmod) {
			    TTYADD('\n');
E 66
E 65
		    }
		}
	    } else {
		TTYADD(c);
	    }
	    continue;
E 49

I 43
D 49
struct sendlist Sendlist2[] = {		/* some synonyms */
	{ "break", BREAK, 0 },
E 49
I 49
	case TS_IAC:
I 72
process_iac:
E 72
	    switch (c) {
D 92
	    
E 92
I 92

E 92
	    case WILL:
		telrcv_state = TS_WILL;
		continue;
E 49

D 49
	{ "intp", IP, 0 },
	{ "interrupt", IP, 0 },
	{ "intr", IP, 0 },
E 49
I 49
	    case WONT:
		telrcv_state = TS_WONT;
		continue;
E 49

D 49
	{ "help", SENDQUESTION, 0 },
E 49
I 49
	    case DO:
		telrcv_state = TS_DO;
		continue;
E 49

D 49
	{ 0 }
};
E 49
I 49
	    case DONT:
		telrcv_state = TS_DONT;
		continue;
E 49

E 43
D 49
char **
getnextsend(name)
char *name;
{
    struct sendlist *c = (struct sendlist *) name;
E 49
I 49
	    case DM:
		    /*
		     * We may have missed an urgent notification,
		     * so make sure we flush whatever is in the
		     * buffer currently.
		     */
I 82
D 83
		printoption("RCVD", "IAC", DM);
E 83
I 83
		printoption("RCVD", IAC, DM);
E 83
E 82
		SYNCHing = 1;
D 81
		ttyflush(1);
E 81
I 81
		(void) ttyflush(1);
E 81
D 54
		SYNCHing = stilloob(net);
E 54
I 54
		SYNCHing = stilloob();
E 54
		settimer(gotDM);
		break;
E 49

D 49
    return (char **) (c+1);
}
E 49
I 49
D 81
	    case NOP:
	    case GA:
		break;
E 49

E 81
D 49
struct sendlist *
getsend(name)
char *name;
{
D 43
    return (struct sendlist *) genget(name, (char **) Sendlist, getnextsend);
E 43
I 43
    struct sendlist *sl;
E 49
I 49
	    case SB:
		SB_CLEAR();
		telrcv_state = TS_SB;
I 72
D 83
		printoption("RCVD", "IAC", SB);
E 83
E 72
		continue;
E 49

D 49
    if (sl = (struct sendlist *)
				genget(name, (char **) Sendlist, getnextsend)) {
	return sl;
    } else {
	return (struct sendlist *)
				genget(name, (char **) Sendlist2, getnextsend);
    }
E 43
}

sendcmd(argc, argv)
int	argc;
char	**argv;
{
    int what;		/* what we are sending this time */
    int count;		/* how many bytes we are going to need to send */
    int hadsynch;	/* are we going to process a "synch"? */
    int i;
I 43
    int question = 0;	/* was at least one argument a question */
E 43
    struct sendlist *s;	/* pointer to current command */

    if (argc < 2) {
	printf("need at least one argument for 'send' command\n");
	printf("'send ?' for help\n");
D 43
	return;
E 43
I 43
	return 0;
E 43
    }
    /*
     * First, validate all the send arguments.
     * In addition, we see how much space we are going to need, and
     * whether or not we will be doing a "SYNCH" operation (which
     * flushes the network queue).
     */
    count = 0;
    hadsynch = 0;
    for (i = 1; i < argc; i++) {
	s = getsend(argv[i]);
	if (s == 0) {
	    printf("Unknown send argument '%s'\n'send ?' for help.\n",
			argv[i]);
D 43
	    return;
E 43
I 43
	    return 0;
E 43
D 41
	} else if (s == (struct sendlist *) -1) {
E 41
I 41
	} else if (s == Ambiguous(struct sendlist *)) {
E 41
	    printf("Ambiguous send argument '%s'\n'send ?' for help.\n",
			argv[i]);
D 43
	    return;
E 43
I 43
	    return 0;
E 43
	}
	switch (s->what) {
	case SENDQUESTION:
D 43
	case SEND2QUESTION:
E 43
	    break;
	case SENDESCAPE:
	    count += 1;
	    break;
	case SYNCH:
	    hadsynch = 1;
	    count += 2;
	    break;
	default:
	    count += 2;
	    break;
	}
    }
    /* Now, do we have enough room? */
D 42
    if (netobuf+sizeof netobuf-nfrontp-1 < count) {
E 42
I 42
    if (NETROOM() < count) {
E 42
	printf("There is not enough room in the buffer TO the network\n");
	printf("to process your request.  Nothing will be done.\n");
	printf("('send synch' will throw away most data in the network\n");
	printf("buffer, if this might help.)\n");
D 43
	return;
E 43
I 43
	return 0;
E 43
    }
    /* OK, they are all OK, now go through again and actually send */
    for (i = 1; i < argc; i++) {
	if (!(s = getsend(argv[i]))) {
	    fprintf(stderr, "Telnet 'send' error - argument disappeared!\n");
	    quit();
	    /*NOTREACHED*/
	}
	if (s->routine) {
	    (*s->routine)(s);
	} else {
	    switch (what = s->what) {
I 43
	    case SYNCH:
		dosynch();
		break;
E 43
	    case SENDQUESTION:
D 43
	    case SEND2QUESTION:
E 43
		for (s = Sendlist; s->name; s++) {
D 43
		    if (s->help || (what == SEND2QUESTION)) {
E 43
I 43
		    if (s->help) {
E 43
			printf(s->name);
			if (s->help) {
			    printf("\t%s", s->help);
			}
			printf("\n");
E 49
I 49
#	    if defined(TN3270)
	    case EOR:
		if (In3270) {
D 81
		    Ibackp += DataFromNetwork(Ibackp, Ifrontp-Ibackp, 1);
E 81
		    if (Ibackp == Ifrontp) {
			Ibackp = Ifrontp = Ibuf;
			ISend = 0;	/* should have been! */
		    } else {
I 81
			Ibackp += DataFromNetwork(Ibackp, Ifrontp-Ibackp, 1);
E 81
			ISend = 1;
E 49
		    }
		}
I 82
D 83
		printoption("RCVD", "IAC", EOR);
E 83
I 83
		printoption("RCVD", IAC, EOR);
E 83
E 82
I 43
D 49
		question = 1;
E 49
E 43
		break;
D 49
	    case SENDESCAPE:
		NETADD(escape);
E 49
I 49
#	    endif /* defined(TN3270) */

	    case IAC:
#	    if !defined(TN3270)
		TTYADD(IAC);
#	    else /* !defined(TN3270) */
		if (In3270) {
		    *Ifrontp++ = IAC;
		} else {
		    TTYADD(IAC);
		}
#	    endif /* !defined(TN3270) */
E 49
		break;
I 49

I 81
	    case NOP:
	    case GA:
E 81
E 49
	    default:
I 81
D 83
		printoption("RCVD", "IAC", c);
E 83
I 83
		printoption("RCVD", IAC, c);
E 83
E 81
D 49
		NET2ADD(IAC, what);
E 49
		break;
	    }
D 49
	}
    }
I 43
    return !question;
E 43
}

/*
 * The following are the routines and data structures referred
 * to by the arguments to the "toggle" command.
 */
E 49
I 49
	    telrcv_state = TS_DATA;
	    continue;
E 49

I 39
D 43
lclsigs()
E 43
I 43
D 49
lclchars()
E 43
{
D 41
    localsigs = !localsigs;
    printf("%s recognize interrupt/quit characters.\n",
					localsigs ? "Will" : "Won't");
E 41
D 43
    donelclsigs = 1;
E 43
I 43
    donelclchars = 1;
    return 1;
E 43
D 41
    fflush(stdout);
E 41
}
E 49
I 49
	case TS_WILL:
D 71
	    printoption(">RCVD", will, c, !hisopts[c]);
E 71
I 71
D 83
	    printoption("RCVD", "will", c);
E 83
I 83
	    printoption("RCVD", WILL, c);
E 83
E 71
D 72
	    if (c == TELOPT_TM) {
		if (flushout) {
		    flushout = 0;
		}
D 71
	    } else if (!hisopts[c]) {
		willoption(c, 1);
E 71
I 71
	    } else {
		willoption(c);
E 71
	    }
E 72
I 72
	    willoption(c);
E 72
	    SetIn3270();
	    telrcv_state = TS_DATA;
	    continue;
E 49

D 41
localecho()
{
    doechocharrecognition = !doechocharrecognition;
    printf("%s recognize echo toggle character.\n",
				doechocharrecognition ? "Will" : "Won't");
    fflush(stdout);
}

E 41
D 43
/*VARARGS*/
D 40
setcrmod()
E 40
I 40
togcrmod()
E 40
{
D 41

E 41
    crmod = !crmod;
I 41
    printf("Deprecated usage - please use 'toggle crmod' in the future.\n");
E 41
    printf("%s map carriage return on output.\n", crmod ? "Will" : "Won't");
    fflush(stdout);
}

E 43
E 39
D 40
setdebug()
E 40
I 40
D 49
togdebug()
E 40
{
I 44
#ifndef	NOT43
E 44
D 41

D 39
	debug = debug ? 0 : 1;
	printf("%s turn on socket level debugging.\n",
		debug ? "Will" : "Won't");
	fflush(stdout);
	if (net > 0 &&
	    setsockopt(net, SOL_SOCKET, SO_DEBUG, &debug, sizeof(debug)) < 0)
		perror("setsockopt (SO_DEBUG)");
E 39
I 39
    debug = debug ? 0 : 1;
    printf("%s turn on socket level debugging.\n",
	    debug ? "Will" : "Won't");
    fflush(stdout);
E 41
    if (net > 0 &&
D 41
	setsockopt(net, SOL_SOCKET, SO_DEBUG, &debug, sizeof(debug)) < 0)
E 41
I 41
	setsockopt(net, SOL_SOCKET, SO_DEBUG, (char *)&debug, sizeof(debug))
									< 0) {
E 41
	    perror("setsockopt (SO_DEBUG)");
I 41
    }
I 44
#else	NOT43
    if (debug) {
	if (net > 0 && setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
	    perror("setsockopt (SO_DEBUG)");
    } else
	printf("Cannot turn off socket debugging\n");
#endif	NOT43
E 44
I 43
    return 1;
E 43
E 41
E 39
}
E 49
I 49
	case TS_WONT:
D 71
	    printoption(">RCVD", wont, c, hisopts[c]);
E 71
I 71
D 83
	    printoption("RCVD", "wont", c);
E 83
I 83
	    printoption("RCVD", WONT, c);
E 83
E 71
D 72
	    if (c == TELOPT_TM) {
		if (flushout) {
		    flushout = 0;
		}
D 71
	    } else if (hisopts[c]) {
E 71
I 71
	    } else {
E 71
		wontoption(c, 1);
	    }
E 72
I 72
	    wontoption(c);
E 72
	    SetIn3270();
	    telrcv_state = TS_DATA;
	    continue;
E 49

I 49
	case TS_DO:
D 71
	    printoption(">RCVD", doopt, c, !myopts[c]);
	    if (!myopts[c])
		dooption(c);
E 71
I 71
D 83
	    printoption("RCVD", "do", c);
E 83
I 83
	    printoption("RCVD", DO, c);
E 83
	    dooption(c);
E 71
	    SetIn3270();
I 70
	    if (c == TELOPT_NAWS) {
		sendnaws();
	    } else if (c == TELOPT_LFLOW) {
		localflow = 1;
		setcommandmode();
D 72
		setconnmode();
E 72
I 72
		setconnmode(0);
E 72
	    }
E 70
	    telrcv_state = TS_DATA;
	    continue;
E 49
D 41
static
D 40
setnetdata()
E 40
I 40
tognetdata()
E 40
{
E 41

I 71
D 72
	/*
	 * Now, I've never understood this.  Why do we
	 * need separate routines for will, wont, do,
	 * but not for dont?
	 */
E 72
E 71
I 49
	case TS_DONT:
D 71
	    printoption(">RCVD", dont, c, myopts[c]);
	    if (myopts[c]) {
		myopts[c] = 0;
D 50
		sprintf(nfrontp, wont, c);
		nfrontp += sizeof (wont) - 2;
E 50
I 50
D 54
		netoprint(wont, c);
E 54
I 54
		printring(&netoring, wont, c);
E 54
E 50
		flushline = 1;
		setconnmode();	/* set new tty mode (maybe) */
		printoption(">SENT", wont, c, 0);
	    }
E 71
I 71
D 83
	    printoption("RCVD", "dont", c);
E 83
I 83
	    printoption("RCVD", DONT, c);
E 83
D 72
	    he_said_dont(c);
	    send_wont(c);
E 72
I 72
	    dontoption(c);
E 72
	    flushline = 1;
D 72
	    setconnmode();	/* set new tty mode (maybe) */
E 72
I 72
	    setconnmode(0);	/* set new tty mode (maybe) */
E 72
E 71
	    SetIn3270();
	    telrcv_state = TS_DATA;
	    continue;
E 49
D 39
	netdata = !netdata;
	printf("%s turn on printing of raw network traffic.\n",
		netdata ? "Will" : "Wont");
E 39
I 39
D 41
    netdata = !netdata;
    printf("%s turn on printing of raw network traffic.\n",
	    netdata ? "Will" : "Wont");
E 39
}
E 41

D 40
setoptions()
E 40
I 40
D 41
togoptions()
E 40
{

D 39
	showoptions = !showoptions;
	printf("%s show option processing.\n", showoptions ? "Will" : "Won't");
	fflush(stdout);
E 39
I 39
    showoptions = !showoptions;
    printf("%s show option processing.\n", showoptions ? "Will" : "Won't");
    fflush(stdout);
E 39
}

E 41
D 49
int togglehelp();
E 49
I 49
	case TS_SB:
	    if (c == IAC) {
		telrcv_state = TS_SE;
	    } else {
		SB_ACCUM(c);
	    }
	    continue;
E 49

I 39
D 43
char	crmodhelp[] =	"toggle mapping of received carriage returns";

E 43
E 39
D 40
struct cmd togglelist[] = {
D 39
    { "debug", "toggle debugging", setdebug, 1 },
    { "options", "toggle viewing of options processing", setoptions, 1 },
    { "netdata", "toggle printing of hexadecimal network data",
							setnetdata, 1 },
E 39
I 39
    { "localchars", "toggle local recognition of control characters",
								lclsigs, 1 },
    { "echochar", "toggle recognition of echo toggle character", localecho, 1 },
    { "crmod",	crmodhelp,	setcrmod, 1, 0 },
E 40
I 40
D 49
struct togglelist {
    char	*name;		/* name of toggle */
    char	*help;		/* help message */
D 41
    int	(*handler)();	/* routine to do actual setting */
E 41
I 41
    int		(*handler)();	/* routine to do actual setting */
E 41
    int		dohelp;		/* should we display help information */
    int		*variable;
    char	*actionexplanation;
};

struct togglelist Togglelist[] = {
D 43
    { "localchars",
	"toggle local recognition of control characters",
	    lclsigs,
		1,
		    &localsigs,
			"recognize interrupt/quit characters" },
    { "echochar",
	"toggle recognition of echo toggle character",
E 43
I 43
    { "autoflush",
	"toggle flushing of output when sending interrupt characters",
E 43
D 41
	    localecho,
E 41
I 41
	    0,
E 41
		1,
D 43
		    &doechocharrecognition,
			"recognize echo toggle character" },
E 43
I 43
		    &autoflush,
			"flush output when sending interrupt characters" },
E 43
I 41
    { "autosynch",
	"toggle automatic sending of interrupt characters in urgent mode",
	    0,
		1,
		    &autosynch,
			"send interrupt characters in urgent mode" },
I 42
D 43
    { "autoflush",
	"toggle automatic flushing of output when sending interrupt characters",
	    0,
		1,
		    &autoflush,
			"flush output when sending interrupt characters" },
E 43
E 42
E 41
    { "crmod",
D 43
	crmodhelp,
E 43
I 43
	"toggle mapping of received carriage returns",
E 43
D 41
	    togcrmod,
E 41
I 41
	    0,
E 41
		1,
		    &crmod,
			"map carriage return on output" },
I 43
    { "localchars",
	"toggle local recognition of certain control characters",
	    lclchars,
		1,
		    &localchars,
			"recognize certain control characters" },
E 43
E 40
    { " ", "", 0, 1 },		/* empty line */
D 40
    { "debug", "(debugging) toggle debugging", setdebug, 1 },
    { "options", "(debugging) toggle viewing of options processing",
								setoptions, 1 },
    { "netdata", "(debugging) toggle printing of hexadecimal network data",
								setnetdata, 1 },
E 39
    { "?", "display help information", togglehelp, 1 },
    { "help", "display help information", togglehelp, 0 },
E 40
I 40
    { "debug",
	"(debugging) toggle debugging",
	    togdebug,
		1,
		    &debug,
			"turn on socket level debugging" },
D 43
    { "options",
	"(debugging) toggle viewing of options processing",
D 41
	    togoptions,
E 41
I 41
	    0,
E 41
		1,
		    &showoptions,
			"show option processing" },
E 43
    { "netdata",
	"(debugging) toggle printing of hexadecimal network data",
D 41
	    tognetdata,
E 41
I 41
	    0,
E 41
		1,
		    &netdata,
			"print hexadecimal representation of network traffic" },
I 43
    { "options",
	"(debugging) toggle viewing of options processing",
	    0,
		1,
		    &showoptions,
			"show option processing" },
    { " ", "", 0, 1 },		/* empty line */
E 43
    { "?",
	"display help information",
	    togglehelp,
		1 },
    { "help",
	"display help information",
	    togglehelp,
		0 },
E 40
    { 0 }
};

togglehelp()
{
D 40
    struct cmd *c;
E 40
I 40
    struct togglelist *c;
E 40

D 40
    for (c = togglelist; c->name; c++) {
E 40
I 40
    for (c = Togglelist; c->name; c++) {
E 40
	if (c->dohelp) {
	    printf("%s\t%s\n", c->name, c->help);
E 49
I 49
	case TS_SE:
	    if (c != SE) {
		if (c != IAC) {
I 72
		    /*
		     * This is an error.  We only expect to get
		     * "IAC IAC" or "IAC SE".  Several things may
		     * have happend.  An IAC was not doubled, the
		     * IAC SE was left off, or another option got
		     * inserted into the suboption are all possibilities.
		     * If we assume that the IAC was not doubled,
		     * and really the IAC SE was left off, we could
		     * get into an infinate loop here.  So, instead,
		     * we terminate the suboption, and process the
		     * partial suboption if we can.
		     */
D 83
		    SB_TERM();
E 83
E 72
		    SB_ACCUM(IAC);
I 72
		    SB_ACCUM(c);
D 83
		    printoption("In SUBOPTION processing, RCVD", "IAC", c);
E 83
I 83
		    subpointer -= 2;
		    SB_TERM();

		    printoption("In SUBOPTION processing, RCVD", IAC, c);
E 83
		    suboption();	/* handle sub-option */
		    SetIn3270();
		    telrcv_state = TS_IAC;
		    goto process_iac;
E 72
		}
		SB_ACCUM(c);
		telrcv_state = TS_SB;
	    } else {
D 83
		SB_TERM();
E 83
I 72
		SB_ACCUM(IAC);
		SB_ACCUM(SE);
I 83
		subpointer -= 2;
		SB_TERM();
E 83
E 72
		suboption();	/* handle sub-option */
		SetIn3270();
		telrcv_state = TS_DATA;
	    }
E 49
	}
    }
I 51
D 52
    ring_sent_acked(&netiring, count);
E 52
I 52
D 56
    ring_consumed(&netiring, count);
E 56
I 56
    if (count)
	ring_consumed(&netiring, count);
E 56
E 52
    return returnValue||count;
E 51
I 43
D 49
    return 0;
E 49
E 43
}
I 51

D 83
static int
E 83
I 83
static int bol = 1, local = 0;

    int
rlogin_susp()
{
    if (local) {
	local = 0;
	bol = 1;
	command(0, "z\n", 2);
	return(1);
    }
    return(0);
}

    static int
E 83
D 54
telsnd(ring)
Ring	*ring;			/* Input ring */
E 54
I 54
telsnd()
E 54
{
    int tcc;
    int count;
    int returnValue = 0;
D 83
    char *tbp;
E 83
I 83
    unsigned char *tbp;
E 83

    tcc = 0;
    count = 0;
    while (NETROOM() > 2) {
	register int sc;
	register int c;

	if (tcc == 0) {
	    if (count) {
D 52
		ring_sent_acked(&ttyiring, count);
E 52
I 52
		ring_consumed(&ttyiring, count);
E 52
		returnValue = 1;
		count = 0;
	    }
D 52
	    tbp = ttyiring.send;
	    tcc = ring_unsent_consecutive(&ttyiring);
E 52
I 52
	    tbp = ttyiring.consume;
	    tcc = ring_full_consecutive(&ttyiring);
E 52
	    if (tcc == 0) {
		break;
	    }
	}
	c = *tbp++ & 0xff, sc = strip(c), tcc--; count++;
D 83
	if (sc == escape) {
E 83
I 83
	if (rlogin != _POSIX_VDISABLE) {
		if (bol) {
			bol = 0;
			if (sc == rlogin) {
				local = 1;
				continue;
			}
		} else if (local) {
			local = 0;
			if (sc == '.' || c == termEofChar) {
				bol = 1;
				command(0, "close\n", 6);
				continue;
			}
			if (sc == termSuspChar) {
				bol = 1;
				command(0, "z\n", 2);
				continue;
			}
			if (sc == escape) {
				command(0, (char *)tbp, tcc);
				bol = 1;
				count += tcc;
				tcc = 0;
				flushline = 1;
				break;
			}
			if (sc != rlogin) {
				++tcc;
				--tbp;
				--count;
				c = sc = rlogin;
			}
		}
		if ((sc == '\n') || (sc == '\r'))
			bol = 1;
	} else if (sc == escape) {
E 83
D 72
	    command(0);
	    tcc = 0;
	    flushline = 1;
	    break;
	} else if (MODE_LINE(globalmode) && (sc == echoc)) {
E 72
I 72
	    /*
	     * Double escape is a pass through of a single escape character.
	     */
	    if (tcc && strip(*tbp) == escape) {
		tbp++;
		tcc--;
		count++;
I 83
		bol = 0;
E 83
	    } else {
D 83
		command(0, tbp, tcc);
E 83
I 83
		command(0, (char *)tbp, tcc);
		bol = 1;
E 83
		count += tcc;
		tcc = 0;
		flushline = 1;
		break;
	    }
D 83
	}
E 83
I 83
	} else
	    bol = 0;
E 83
#ifdef	KLUDGELINEMODE
	if (kludgelinemode && (globalmode&MODE_EDIT) && (sc == echoc)) {
E 72
	    if (tcc > 0 && strip(*tbp) == echoc) {
		tcc--; tbp++; count++;
	    } else {
		dontlecho = !dontlecho;
		settimer(echotoggle);
D 72
		setconnmode();
E 72
I 72
		setconnmode(0);
E 72
		flushline = 1;
		break;
	    }
	}
D 72
	if (localchars) {
E 72
I 72
#endif
	if (MODE_LOCAL_CHARS(globalmode)) {
E 72
	    if (TerminalSpecialChars(sc) == 0) {
I 83
		bol = 1;
E 83
		break;
	    }
	}
D 71
	if (!myopts[TELOPT_BINARY]) {
E 71
I 71
D 72
	if (!should_I(TELOPT_BINARY)) {
E 72
I 72
	if (my_want_state_is_wont(TELOPT_BINARY)) {
E 72
E 71
	    switch (c) {
	    case '\n':
		    /*
		     * If we are in CRMOD mode (\r ==> \n)
		     * on our local machine, then probably
		     * a newline (unix) is CRLF (TELNET).
		     */
		if (MODE_LOCAL_CHARS(globalmode)) {
		    NETADD('\r');
		}
		NETADD('\n');
D 83
		flushline = 1;
E 83
I 83
		bol = flushline = 1;
E 83
		break;
	    case '\r':
		if (!crlf) {
		    NET2ADD('\r', '\0');
		} else {
		    NET2ADD('\r', '\n');
		}
D 83
		flushline = 1;
E 83
I 83
		bol = flushline = 1;
E 83
		break;
	    case IAC:
		NET2ADD(IAC, IAC);
		break;
	    default:
		NETADD(c);
		break;
	    }
	} else if (c == IAC) {
	    NET2ADD(IAC, IAC);
	} else {
	    NETADD(c);
	}
    }
D 52
    ring_sent_acked(&ttyiring, count);
E 52
I 52
D 56
    ring_consumed(&ttyiring, count);
E 56
I 56
    if (count)
	ring_consumed(&ttyiring, count);
E 56
E 52
    return returnValue||count;		/* Non-zero if we did anything */
}
E 51
D 49

char **
getnexttoggle(name)
char *name;
E 49
I 49

D 53
#if	defined(TN3270)
static void
SetForExit()
E 49
{
D 40
    struct cmd *c = (struct cmd *) name;
E 40
I 40
D 49
    struct togglelist *c = (struct togglelist *) name;
E 40

    return (char **) (c+1);
E 49
I 49
    setconnmode();
    if (In3270) {
	Finish3270();
    }
    setcommandmode();
    fflush(stdout);
    fflush(stderr);
    if (In3270) {
	StopScreen(1);
    }
    setconnmode();
    setcommandmode();
E 49
}

D 40
struct cmd *
E 40
I 40
D 49
struct togglelist *
E 40
gettoggle(name)
char *name;
E 49
I 49
static void
Exit(returnCode)
int returnCode;
E 49
{
D 40
    return (struct cmd *) genget(name, (char **) togglelist, getnexttoggle);
E 40
I 40
D 49
    return (struct togglelist *)
			genget(name, (char **) Togglelist, getnexttoggle);
E 49
I 49
    SetForExit();
    exit(returnCode);
E 49
E 40
}

D 49
toggle(argc, argv)
int	argc;
char	*argv[];
E 49
I 49
void
D 50
ExitString(file, string, returnCode)
FILE *file;
E 50
I 50
ExitString(string, returnCode)
E 50
char *string;
int returnCode;
E 49
{
I 43
D 49
    int retval = 1;
E 43
    char *name;
D 40
    struct cmd *c;
E 40
I 40
    struct togglelist *c;
E 49
I 49
    SetForExit();
D 50
    fwrite(string, 1, strlen(string), file);
E 50
I 50
    fwrite(string, 1, strlen(string), stderr);
E 50
    exit(returnCode);
}
E 49
E 40

D 49
    if (argc < 2) {
	fprintf(stderr,
	    "Need an argument to 'toggle' command.  'toggle ?' for help.\n");
D 43
	return;
E 43
I 43
	return 0;
E 43
    }
    argc--;
    argv++;
    while (argc--) {
	name = *argv++;
	c = gettoggle(name);
D 40
	if (c == (struct cmd *) -1) {
E 40
I 40
D 41
	if (c == (struct togglelist *) -1) {
E 41
I 41
	if (c == Ambiguous(struct togglelist *)) {
E 41
E 40
	    fprintf(stderr, "'%s': ambiguous argument ('toggle ?' for help).\n",
					name);
I 43
	    return 0;
E 43
	} else if (c == 0) {
	    fprintf(stderr, "'%s': unknown argument ('toggle ?' for help).\n",
					name);
I 43
	    return 0;
E 43
	} else {
D 41
	    (*c->handler)(c);
E 41
I 41
	    if (c->variable) {
		*c->variable = !*c->variable;		/* invert it */
		printf("%s %s.\n", *c->variable? "Will" : "Won't",
							c->actionexplanation);
	    }
	    if (c->handler) {
D 43
		(*c->handler)(c);
E 43
I 43
		retval &= (*c->handler)(c);
E 43
	    }
E 41
	}
    }
I 43
    return retval;
E 49
I 49
void
ExitPerror(string, returnCode)
char *string;
int returnCode;
{
    SetForExit();
    perror(string);
    exit(returnCode);
E 49
E 43
}
I 49
#endif	/* defined(TN3270) */

E 49

E 53
/*
I 39
D 49
 * The following perform the "set" command.
E 49
I 49
 * Scheduler()
 *
 * Try to do something.
 *
 * If we do something useful, return 1; else return 0.
 *
E 49
 */

D 40
struct chartab {
    char *label;			/* name */
E 40
I 40
D 49
struct setlist {
    char *name;				/* name */
E 40
    char *help;				/* help information */
    char *charp;			/* where it is located at */
};
E 49

D 40
struct chartab Chartab[] = {
E 40
I 40
D 49
struct setlist Setlist[] = {
E 40
    { "echo", 	"character to toggle local echoing on/off", &echoc },
    { "escape",	"character to escape back to telnet command mode", &escape },
I 42
D 43
    { "\200", "" },
    { "\200", "The following need 'localsigs' to be toggled true", 0 },
E 42
    { "interrupt", "character to cause an Interrupt Process", &ntc.t_intrc },
    { "quit",	"character to cause a Break", &ntc.t_quitc },
I 42
    { "flush output", "character to cause an Abort Oubput", &nltc.t_flushc },
E 43
I 43
    { " ", "" },
    { " ", "The following need 'localchars' to be toggled true", 0 },
E 43
E 42
    { "erase",	"character to cause an Erase Character", &nttyb.sg_erase },
I 43
    { "flushoutput", "character to cause an Abort Oubput", &nltc.t_flushc },
    { "interrupt", "character to cause an Interrupt Process", &ntc.t_intrc },
E 43
    { "kill",	"character to cause an Erase Line", &nttyb.sg_kill },
I 43
    { "quit",	"character to cause a Break", &ntc.t_quitc },
I 44
    { "eof",	"character to cause an EOF ", &ntc.t_eofc },
E 44
E 43
    { 0 }
};

char **
D 40
getnextchar(name)
E 40
I 40
getnextset(name)
E 40
char *name;
E 49
I 49
D 83
int
E 83
I 83
    int
E 83
Scheduler(block)
D 83
int	block;			/* should we block in the select ? */
E 83
I 83
    int	block;			/* should we block in the select ? */
E 83
E 49
{
D 40
    struct chartab *c = (struct chartab *)name;
E 40
I 40
D 49
    struct setlist *c = (struct setlist *)name;
E 49
I 49
D 63
    register int c;
E 63
		/* One wants to be a bit careful about setting returnValue
		 * to one, since a one implies we did some useful work,
		 * and therefore probably won't be called to block next
		 * time (TN3270 mode only).
		 */
D 53
    int returnValue = 0;
    static struct timeval TimeValue = { 0 };
E 53
I 53
    int returnValue;
    int netin, netout, netex, ttyin, ttyout;
E 53
E 49
E 40

D 49
    return (char **) (c+1);
}

D 40
struct chartab *
getchartab(name)
E 40
I 40
struct setlist *
getset(name)
E 40
char *name;
{
D 40
    return (struct chartab *) genget(name, (char **) Chartab, getnextchar);
E 40
I 40
    return (struct setlist *) genget(name, (char **) Setlist, getnextset);
E 40
}

setcmd(argc, argv)
int	argc;
char	*argv[];
{
    int value;
D 40
    struct chartab *ct;
E 40
I 40
    struct setlist *ct;
E 40

    /* XXX back we go... sigh */
    if (argc != 3) {
D 43
	printf("Format is 'set Name Value', where 'Name' is one of:\n\n");
D 40
	for (ct = Chartab; ct->label; ct++) {
	    printf("%s\t%s\n", ct->label, ct->help);
E 40
I 40
	for (ct = Setlist; ct->name; ct++) {
	    printf("%s\t%s\n", ct->name, ct->help);
E 43
I 43
	if ((argc == 2) &&
		    ((!strcmp(argv[1], "?")) || (!strcmp(argv[1], "help")))) {
	    for (ct = Setlist; ct->name; ct++) {
		printf("%s\t%s\n", ct->name, ct->help);
	    }
	    printf("?\tdisplay help information\n");
	} else {
	    printf("Format is 'set Name Value'\n'set ?' for help.\n");
E 43
E 40
	}
D 43
	return;
E 43
I 43
	return 0;
E 49
I 49
D 51
    if (scc < 0 && tcc < 0) {
	return -1;
E 49
E 43
    }

E 51
D 40
    ct = getchartab(argv[1]);
E 40
I 40
D 49
    ct = getset(argv[1]);
E 40
    if (ct == 0) {
	fprintf(stderr, "'%s': unknown argument ('set ?' for help).\n",
			argv[1]);
I 43
	return 0;
E 43
D 40
    } else if (ct == (struct chartab *) -1) {
E 40
I 40
D 41
    } else if (ct == (struct setlist *) -1) {
E 41
I 41
    } else if (ct == Ambiguous(struct setlist *)) {
E 41
E 40
	fprintf(stderr, "'%s': ambiguous argument ('set ?' for help).\n",
			argv[1]);
I 43
	return 0;
E 43
    } else {
	if (strcmp("off", argv[2])) {
	    value = special(argv[2]);
	} else {
	    value = -1;
	}
	*(ct->charp) = value;
D 40
	printf("%s character is '%s'.\n", ct->label, control(*(ct->charp)));
E 40
I 40
	printf("%s character is '%s'.\n", ct->name, control(*(ct->charp)));
E 49
I 49
D 53
    if ((!MODE_LINE(globalmode) || flushline) && NETBYTES()) {
	FD_SET(net, &obits);
    } 
#if	!defined(MSDOS)
    if (TTYBYTES()) {
	FD_SET(tout, &obits);
E 49
E 40
    }
E 53
I 53
    /* Decide which rings should be processed */

    netout = ring_full_count(&netoring) &&
D 71
	    (!MODE_LINE(globalmode) || flushline || myopts[TELOPT_BINARY]);
E 71
I 71
D 72
	    (!MODE_LINE(globalmode) || flushline || should_I(TELOPT_BINARY));
E 72
I 72
	    (flushline ||
		(my_want_state_is_wont(TELOPT_LINEMODE)
#ifdef	KLUDGELINEMODE
			&& (!kludgelinemode || my_want_state_is_do(TELOPT_SGA))
#endif
		) ||
			my_want_state_is_will(TELOPT_BINARY));
E 72
E 71
    ttyout = ring_full_count(&ttyoring);

E 53
I 43
D 49
    return 1;
E 43
}

/*
 * The following are the data structures and routines for the
 * 'mode' command.
 */

dolinemode()
{
    if (hisopts[TELOPT_SGA]) {
D 41
	wontoption(TELOPT_SGA, 0);
E 41
I 41
D 44
	wontoption(TELOPT_SGA);
E 44
I 44
	wontoption(TELOPT_SGA, 0);
E 49
I 49
#if	defined(TN3270)
D 53
    if ((tcc == 0) && NETROOM() && (shell_active == 0)) {
	FD_SET(tin, &ibits);
E 49
E 44
E 41
    }
E 53
I 53
    ttyin = ring_empty_count(&ttyiring) && (shell_active == 0);
E 53
D 49
    if (hisopts[TELOPT_ECHO]) {
D 41
	wontoption(TELOPT_ECHO, 0);
E 41
I 41
D 44
	wontoption(TELOPT_ECHO);
E 44
I 44
	wontoption(TELOPT_ECHO, 0);
E 49
I 49
#else	/* defined(TN3270) */
D 51
    if ((tcc == 0) && NETROOM()) {
E 51
I 51
D 53
    if (ring_empty_count(&netiring) && NETROOM()) {
E 51
	FD_SET(tin, &ibits);
E 49
E 44
E 41
    }
E 53
I 53
    ttyin = ring_empty_count(&ttyiring);
E 53
D 49
}

docharmode()
{
    if (!hisopts[TELOPT_SGA]) {
D 41
	willoption(TELOPT_SGA, 0);
E 41
I 41
D 44
	willoption(TELOPT_SGA);
E 44
I 44
	willoption(TELOPT_SGA, 0);
E 49
I 49
#endif	/* defined(TN3270) */
D 53
#endif	/* !defined(MSDOS) */
#   if !defined(TN3270)
    if (TTYROOM()) {
	FD_SET(net, &ibits);
E 49
E 44
E 41
    }
E 53
I 53

#if	defined(TN3270)
    netin = ring_empty_count(&netiring);
E 53
D 49
    if (!hisopts[TELOPT_ECHO]) {
D 41
	willoption(TELOPT_ECHO, 0);
E 41
I 41
D 44
	willoption(TELOPT_ECHO);
E 44
I 44
	willoption(TELOPT_ECHO, 0);
E 49
I 49
#   else /* !defined(TN3270) */
D 53
    if (!ISend && TTYROOM()) {
	FD_SET(net, &ibits);
E 49
E 44
E 41
    }
E 53
I 53
    netin = !ISend && ring_empty_count(&netiring);
E 53
D 49
}

struct cmd Modelist[] = {
D 43
    { "line",		"line-by-line mode",		dolinemode, 1, 1 },
E 43
    { "character",	"character-at-a-time mode",	docharmode, 1, 1 },
I 43
    { "line",		"line-by-line mode",		dolinemode, 1, 1 },
E 43
    { 0 },
};

char **
getnextmode(name)
char *name;
{
    struct cmd *c = (struct cmd *) name;

    return (char **) (c+1);
}

struct cmd *
getmodecmd(name)
char *name;
{
    return (struct cmd *) genget(name, (char **) Modelist, getnextmode);
}

modecmd(argc, argv)
int	argc;
char	*argv[];
{
    struct cmd *mt;

    if ((argc != 2) || !strcmp(argv[1], "?") || !strcmp(argv[1], "help")) {
	printf("format is:  'mode Mode', where 'Mode' is one of:\n\n");
	for (mt = Modelist; mt->name; mt++) {
	    printf("%s\t%s\n", mt->name, mt->help);
E 49
I 49
#   endif /* !defined(TN3270) */
D 53
    if (!SYNCHing) {
	FD_SET(net, &xbits);
    }
E 53
I 53

    netex = !SYNCHing;

    /* If we have seen a signal recently, reset things */
E 53
#   if defined(TN3270) && defined(unix)
    if (HaveInput) {
	HaveInput = 0;
D 81
	signal(SIGIO, inputAvailable);
E 81
I 81
	(void) signal(SIGIO, inputAvailable);
E 81
    }
#endif	/* defined(TN3270) && defined(unix) */
D 53
    if ((c = select(16, &ibits, &obits, &xbits,
			block? (struct timeval *)0 : &TimeValue)) < 0) {
	if (c == -1) {
		    /*
		     * we can get EINTR if we are in line mode,
		     * and the user does an escape (TSTP), or
		     * some other signal generator.
		     */
	    if (errno == EINTR) {
		return 0;
	    }
#	    if defined(TN3270)
		    /*
		     * we can get EBADF if we were in transparent
		     * mode, and the transcom process died.
		    */
	    if (errno == EBADF) {
			/*
			 * zero the bits (even though kernel does it)
			 * to make sure we are selecting on the right
			 * ones.
			*/
		FD_ZERO(&ibits);
		FD_ZERO(&obits);
		FD_ZERO(&xbits);
		return 0;
	    }
#	    endif /* defined(TN3270) */
		    /* I don't like this, does it ever happen? */
	    printf("sleep(5) from telnet, after select\r\n");
#if	defined(unix)
	    sleep(5);
#endif	/* defined(unix) */
E 49
	}
D 43
	return;
E 43
I 43
	return 0;
E 43
    }
E 53
D 49
    mt = getmodecmd(argv[1]);
    if (mt == 0) {
	fprintf(stderr, "Unknown mode '%s' ('mode ?' for help).\n", argv[1]);
I 43
	return 0;
E 43
D 41
    } else if (mt == (struct cmd *) -1) {
E 41
I 41
    } else if (mt == Ambiguous(struct cmd *)) {
E 41
	fprintf(stderr, "Ambiguous mode '%s' ('mode ?' for help).\n", argv[1]);
I 43
	return 0;
E 43
    } else {
	(*mt->handler)();
E 49
I 49

D 53
    /*
     * Any urgent data?
     */
    if (FD_ISSET(net, &xbits)) {
	FD_CLR(net, &xbits);
	SYNCHing = 1;
	ttyflush(1);	/* flush already enqueued data */
E 49
    }
E 53
I 53
    /* Call to system code to process rings */
E 53
I 43
D 49
    return 1;
E 43
}

/*
I 40
 * The following data structures and routines implement the
 * "display" command.
 */
E 49

D 49
display(argc, argv)
int	argc;
char	*argv[];
{
#define	dotog(tl)	if (tl->variable && tl->actionexplanation) { \
			    if (*tl->variable) { \
				printf("will"); \
			    } else { \
				printf("won't"); \
			    } \
			    printf(" %s.\n", tl->actionexplanation); \
			}
E 49
I 49
D 53
    /*
     * Something to read from the network...
     */
    if (FD_ISSET(net, &ibits)) {
	int canread;
E 53
I 53
    returnValue = process_rings(netin, netout, netex, ttyin, ttyout, !block);
E 53
E 49

D 43
#define	doset(sl)	printf("[%s]\t%s.\n", control(*sl->charp), sl->name);
E 43
I 43
D 49
#define	doset(sl)   if (sl->name && *sl->name != ' ') { \
			printf("[%s]\t%s.\n", control(*sl->charp), sl->name); \
E 49
I 49
D 53
	FD_CLR(net, &ibits);
D 51
	if (scc == 0) {
	    sbp = sibuf;
	}
	canread = sibuf + sizeof sibuf - (sbp+scc);
E 51
I 51
	canread = ring_empty_consecutive(&netiring);
E 51
#if	!defined(SO_OOBINLINE)
	    /*
	     * In 4.2 (and some early 4.3) systems, the
	     * OOB indication and data handling in the kernel
	     * is such that if two separate TCP Urgent requests
	     * come in, one byte of TCP data will be overlaid.
	     * This is fatal for Telnet, but we try to live
	     * with it.
	     *
	     * In addition, in 4.2 (and...), a special protocol
	     * is needed to pick up the TCP Urgent data in
	     * the correct sequence.
	     *
	     * What we do is:  if we think we are in urgent
	     * mode, we look to see if we are "at the mark".
	     * If we are, we do an OOB receive.  If we run
	     * this twice, we will do the OOB receive twice,
	     * but the second will fail, since the second
	     * time we were "at the mark", but there wasn't
	     * any data there (the kernel doesn't reset
	     * "at the mark" until we do a normal read).
	     * Once we've read the OOB data, we go ahead
	     * and do normal reads.
	     *
	     * There is also another problem, which is that
	     * since the OOB byte we read doesn't put us
	     * out of OOB state, and since that byte is most
	     * likely the TELNET DM (data mark), we would
	     * stay in the TELNET SYNCH (SYNCHing) state.
	     * So, clocks to the rescue.  If we've "just"
	     * received a DM, then we test for the
	     * presence of OOB data when the receive OOB
	     * fails (and AFTER we did the normal mode read
	     * to clear "at the mark").
	     */
	if (SYNCHing) {
	    int atmark;
E 53
I 53
    /* Now, look at the input rings, looking for work to do. */
E 53

D 53
	    ioctl(net, SIOCATMARK, (char *)&atmark);
	    if (atmark) {
		c = recv(net, sbp+scc, canread, MSG_OOB);
		if ((c == -1) && (errno == EINVAL)) {
		    c = recv(net, sbp+scc, canread, 0);
		    if (clocks.didnetreceive < clocks.gotDM) {
			SYNCHing = stilloob(net);
E 49
		    }
I 49
		}
	    } else {
		c = recv(net, sbp+scc, canread, 0);
	    }
	} else {
	    c = recv(net, sbp+scc, canread, 0);
	}
	settimer(didnetreceive);
#else	/* !defined(SO_OOBINLINE) */
D 51
	c = recv(net, sbp+scc, canread, 0);
E 51
I 51
D 52
	c = recv(net, netiring.add, canread, 0);
E 52
I 52
	c = recv(net, netiring.supply, canread, 0);
E 52
E 51
#endif	/* !defined(SO_OOBINLINE) */
	if (c < 0 && errno == EWOULDBLOCK) {
	    c = 0;
	} else if (c <= 0) {
	    return -1;
	}
	if (netdata) {
D 51
	    Dump('<', sbp+scc, c);
E 51
I 51
D 52
	    Dump('<', netiring.add, c);
E 52
I 52
	    Dump('<', netiring.supply, c);
E 52
E 51
	}
D 51
	scc += c;
E 51
I 51
D 52
	ring_added(&netiring, c);
E 52
I 52
	ring_supplied(&netiring, c);
E 52
E 51
	returnValue = 1;
    }
E 49
E 43

D 49
    struct togglelist *tl;
    struct setlist *sl;

    if (argc == 1) {
	for (tl = Togglelist; tl->name; tl++) {
	    dotog(tl);
E 49
I 49
    /*
     * Something to read from the tty...
     */
#if	defined(MSDOS)
    if ((tcc == 0) && NETROOM() && (shell_active == 0) && TerminalCanRead())
#else	/* defined(MSDOS) */
    if (FD_ISSET(tin, &ibits))
#endif	/* defined(MSDOS) */
				    {
	FD_CLR(tin, &ibits);
D 51
	if (tcc == 0) {
	    tbp = tibuf;	/* nothing left, reset */
E 49
	}
I 43
D 49
	printf("\n");
E 43
	for (sl = Setlist; sl->name; sl++) {
	    doset(sl);
E 49
I 49
	c = TerminalRead(tin, tbp, tibuf+sizeof tibuf - tbp);
E 51
I 51
D 52
	c = TerminalRead(tin, ttyiring.add, ring_empty_consecutive(&ttyiring));
E 52
I 52
	c = TerminalRead(tin, ttyiring.supply,
			ring_empty_consecutive(&ttyiring));
E 52
E 51
	if (c < 0 && errno == EWOULDBLOCK) {
	    c = 0;
	} else {
#if	defined(unix)
	    /* EOF detection for line mode!!!! */
	    if (c == 0 && MODE_LOCAL_CHARS(globalmode)) {
			/* must be an EOF... */
D 51
		*tbp = termEofChar;
E 51
I 51
D 52
		*ttyiring.add = termEofChar;
E 52
I 52
		*ttyiring.supply = termEofChar;
E 52
E 51
		c = 1;
	    }
#endif	/* defined(unix) */
	    if (c <= 0) {
D 51
		tcc = c;
E 51
		return -1;
	    }
E 49
	}
D 49
    } else {
	int i;
E 49
I 49
D 51
	tcc += c;
E 51
I 51
D 52
	ring_added(&ttyiring, c);
E 52
I 52
	ring_supplied(&ttyiring, c);
E 52
E 51
	returnValue = 1;		/* did something useful */
    }
E 49

D 49
	for (i = 1; i < argc; i++) {
	    sl = getset(argv[i]);
	    tl = gettoggle(argv[i]);
D 41
	    if ((tl && sl) || (sl == (struct setlist *) -1) ||
				(tl == (struct togglelist *) -1)) {
E 41
I 41
	    if ((sl == Ambiguous(struct setlist *)) ||
				(tl == Ambiguous(struct togglelist *))) {
E 41
		printf("?Ambiguous argument '%s'.\n", argv[i]);
I 43
		return 0;
E 43
	    } else if (!sl && !tl) {
		printf("?Unknown argument '%s'.\n", argv[i]);
I 43
		return 0;
E 43
D 41
	    } else if (tl) {
		dotog(tl);
E 41
	    } else {
D 41
		doset(sl);
E 41
I 41
		if (tl) {
		    dotog(tl);
E 49
I 49
#   if defined(TN3270)
E 53
D 51
    if (tcc > 0) {
E 51
I 51
D 52
    if (ring_unsent_count(&ttyiring)) {
E 52
I 52
    if (ring_full_count(&ttyiring)) {
I 53
#   if defined(TN3270)
E 53
E 52
E 51
	if (In3270) {
I 63
	    int c;

E 63
D 51
	    c = DataFromTerminal(tbp, tcc);
E 51
I 51
D 61
	    c = DataFromTerminal(ttyiring.send,
E 61
I 61
	    c = DataFromTerminal(ttyiring.consume,
E 61
D 52
					ring_unsent_consecutive(&ttyiring));
E 52
I 52
					ring_full_consecutive(&ttyiring));
E 52
E 51
	    if (c) {
		returnValue = 1;
I 56
D 92
	        ring_consumed(&ttyiring, c);
E 92
I 92
		ring_consumed(&ttyiring, c);
E 92
E 56
	    }
D 51
	    tcc -= c;
	    tbp += c;
E 51
I 51
D 52
	    ring_sent_acked(&ttyiring, c);
E 52
I 52
D 56
	    ring_consumed(&ttyiring, c);
E 56
E 52
E 51
	} else {
#   endif /* defined(TN3270) */
D 51
	    returnValue = 1;
	    while (tcc > 0) {
		register int sc;

		if (NETROOM() < 2) {
		    flushline = 1;
		    break;
E 49
		}
D 49
		if (sl) {
		    doset(sl);
E 49
I 49
		c = *tbp++ & 0xff, sc = strip(c), tcc--;
		if (sc == escape) {
		    command(0);
		    tcc = 0;
		    flushline = 1;
		    break;
		} else if (MODE_LINE(globalmode) && (sc == echoc)) {
		    if (tcc > 0 && strip(*tbp) == echoc) {
			tbp++;
			tcc--;
		    } else {
			dontlecho = !dontlecho;
			settimer(echotoggle);
			setconnmode();
			tcc = 0;
			flushline = 1;
			break;
		    }
E 49
		}
I 49
		if (localchars) {
		    if (TerminalSpecialChars(sc) == 0) {
			break;
		    }
		}
		if (!myopts[TELOPT_BINARY]) {
		    switch (c) {
		    case '\n':
			    /*
			     * If we are in CRMOD mode (\r ==> \n)
			     * on our local machine, then probably
			     * a newline (unix) is CRLF (TELNET).
			     */
			if (MODE_LOCAL_CHARS(globalmode)) {
			    NETADD('\r');
			}
			NETADD('\n');
			flushline = 1;
			break;
		    case '\r':
			if (!crlf) {
			    NET2ADD('\r', '\0');
			} else {
			    NET2ADD('\r', '\n');
			}
			flushline = 1;
			break;
		    case IAC:
			NET2ADD(IAC, IAC);
			break;
		    default:
			NETADD(c);
			break;
		    }
		} else if (c == IAC) {
		    NET2ADD(IAC, IAC);
		} else {
		    NETADD(c);
		}
E 49
E 41
	    }
E 51
I 51
D 54
	    returnValue |= telsnd(&ttyiring);
E 54
I 54
	    returnValue |= telsnd();
E 54
E 51
I 49
#   if defined(TN3270)
E 49
	}
D 53
    }
E 53
I 43
D 49
    return 1;
E 43
#undef	doset(sl)
#undef	dotog(tl)
E 49
I 49
#   endif /* defined(TN3270) */
D 53

    if ((!MODE_LINE(globalmode) || flushline || myopts[TELOPT_BINARY]) &&
	FD_ISSET(net, &obits) && (NETBYTES() > 0)) {
	FD_CLR(net, &obits);
	returnValue = netflush();
E 53
    }
I 53

E 53
D 51
    if (scc > 0) {
E 51
I 51
D 52
    if (ring_unsent_count(&netiring)) {
E 52
I 52
    if (ring_full_count(&netiring)) {
E 52
E 51
#	if !defined(TN3270)
D 51
	telrcv();
	returnValue = 1;
E 51
I 51
	returnValue |= telrcv();
E 51
#	else /* !defined(TN3270) */
	returnValue = Push3270();
#	endif /* !defined(TN3270) */
    }
D 53
#if	defined(MSDOS)
    if (TTYBYTES())
#else	/* defined(MSDOS) */
    if (FD_ISSET(tout, &obits) && (TTYBYTES() > 0))
#endif	/* defined(MSDOS) */
						    {
	FD_CLR(tout, &obits);
	returnValue = ttyflush(SYNCHing|flushout);
    }
E 53
    return returnValue;
E 49
}

/*
E 40
E 39
D 49
 * The following are the data structures, and many of the routines,
 * relating to command processing.
E 49
I 49
 * Select from tty and network...
E 49
 */
D 49

/*
 * Set the escape character.
 */
setescape(argc, argv)
	int argc;
	char *argv[];
E 49
I 49
D 83
void
telnet()
E 83
I 83
    void
telnet(user)
    char *user;
E 83
E 49
{
D 49
	register char *arg;
	char buf[50];
E 49
I 49
D 53
#if	defined(MSDOS)
#define	SCHED_BLOCK	0		/* Don't block in MSDOS */
#else	/* defined(MSDOS) */
#define	SCHED_BLOCK	1
#endif	/* defined(MSDOS) */
E 53
I 53
    sys_telnet_init();
E 53
E 49

I 83
D 85
#if defined(ENCRYPT) || defined(AUTHENTICATE)
E 85
I 85
D 88
#if defined(ENCRYPTION) || defined(AUTHENTICATION)
E 88
I 88
D 92
#if	defined(AUTHENTICATION) || defined(ENCRYPTION) 
E 92
I 92
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
E 92
E 88
E 85
    {
	static char local_host[256] = { 0 };
D 85
	int len = sizeof(local_host);
E 85

	if (!local_host[0]) {
D 85
		gethostname(local_host, &len);
E 85
I 85
		gethostname(local_host, sizeof(local_host));
E 85
		local_host[sizeof(local_host)-1] = 0;
	}
	auth_encrypt_init(local_host, hostname, "TELNET", 0);
	auth_encrypt_user(user);
    }
D 88
#endif
E 88
I 88
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION)  */
E 88
E 83
I 41
D 49
	printf(
	    "Deprecated usage - please use 'set escape%s%s' in the future.\n",
				(argc > 2)? " ":"", (argc > 2)? argv[1]: "");
E 41
	if (argc > 2)
		arg = argv[1];
	else {
		printf("new escape character: ");
		gets(buf);
		arg = buf;
	}
	if (arg[0] != '\0')
		escape = arg[0];
	printf("Escape character is '%s'.\n", control(escape));
	fflush(stdout);
I 43
	return 1;
E 43
}
E 49
I 49
D 53
#if	defined(TN3270) && defined(unix)
    int myPid;
#endif	/* defined(TN3270) */
E 49

D 49
/*VARARGS*/
I 43
togcrmod()
{
    crmod = !crmod;
    printf("Deprecated usage - please use 'toggle crmod' in the future.\n");
    printf("%s map carriage return on output.\n", crmod ? "Will" : "Won't");
    fflush(stdout);
    return 1;
}
E 49
I 49
    tout = fileno(stdout);
    tin = fileno(stdin);
    setconnmode();
D 51
    scc = 0;
    tcc = 0;
E 51
    FD_ZERO(&ibits);
    FD_ZERO(&obits);
    FD_ZERO(&xbits);
E 49

D 49
/*VARARGS*/
E 43
D 39
setcrmod()
{

	crmod = !crmod;
	printf("%s map carriage return on output.\n", crmod ? "Will" : "Won't");
	fflush(stdout);
}

/*VARARGS*/
E 39
suspend()
{
D 39
	register int save;

	save = mode(0);
E 39
I 39
	setcommandmode();
E 39
	kill(0, SIGTSTP);
	/* reget parameters in case they were changed */
	ioctl(0, TIOCGETP, (char *)&ottyb);
	ioctl(0, TIOCGETC, (char *)&otc);
	ioctl(0, TIOCGLTC, (char *)&oltc);
I 43
	return 1;
E 43
D 39
	(void) mode(save);
E 39
}
E 49
I 49
    NetNonblockingIO(net, 1);
E 49

D 49
/*VARARGS*/
bye()
{
	register char *op;
E 49
I 49
#if	defined(TN3270)
    if (noasynch == 0) {			/* DBX can't handle! */
	NetSigIO(net, 1);
    }
    NetSetPgrp(net);
#endif	/* defined(TN3270) */
E 49

D 39
	(void) mode(0);
E 39
D 49
	if (connected) {
		shutdown(net, 2);
		printf("Connection closed.\n");
		close(net);
		connected = 0;
		/* reset his options */
		for (op = hisopts; op < &hisopts[256]; op++)
			*op = 0;
	}
I 43
	return 1;
E 43
}
E 49

D 49
/*VARARGS*/
quit()
{
D 43
	call(bye, "bye", 0);
E 43
I 43
	(void) call(bye, "bye", 0);
E 43
	exit(0);
I 43
	/*NOTREACHED*/
E 43
}
E 49
I 49
#if	defined(SO_OOBINLINE) && !defined(MSDOS)
    SetSockOpt(net, SOL_SOCKET, SO_OOBINLINE, 1);
#endif	/* defined(SO_OOBINLINE) && !defined(MSDOS) */
E 49

E 53
D 49
/*
 * Print status about the connection.
 */
I 41
/*ARGSUSED*/
E 41
D 40
/*VARARGS*/
status()
E 40
I 40
status(argc, argv)
int	argc;
char	*argv[];
E 40
{
D 39
	if (connected)
E 39
I 39
D 40
	if (connected) {
E 39
		printf("Connected to %s.\n", hostname);
D 39
	else
E 39
I 39
		/* XXX should print out line modes, etc. */
	} else {
E 39
		printf("No connection.\n");
E 40
I 40
    if (connected) {
	printf("Connected to %s.\n", hostname);
	if (argc < 2) {
	    printf("Operating in %s.\n", modedescriptions[getconnmode()]);
D 42
	    if (localsigs || ((!donelclsigs) && (getconnmode() >= 3))) {
E 42
I 42
D 43
	    if (localsigs) {
E 43
I 43
	    if (localchars) {
E 43
E 42
		printf("Catching signals locally.\n");
	    }
E 49
I 49
#   if !defined(TN3270)
    if (telnetport) {
I 83
D 85
#if	defined(AUTHENTICATE)
E 85
I 85
#if	defined(AUTHENTICATION)
E 85
	if (autologin)
		send_will(TELOPT_AUTHENTICATION, 1);
#endif
D 85
#if	defined(ENCRYPT)
E 85
I 85
D 88
#if	defined(ENCRYPTION)
E 88
I 88
#ifdef	ENCRYPTION
E 88
E 85
	send_do(TELOPT_ENCRYPT, 1);
	send_will(TELOPT_ENCRYPT, 1);
D 88
#endif
E 88
I 88
#endif	/* ENCRYPTION */
E 88
E 83
D 71
	if (!hisopts[TELOPT_SGA]) {
	    willoption(TELOPT_SGA, 0);
E 49
E 40
I 39
	}
E 39
D 40
	printf("Escape character is '%s'.\n", control(escape));
	fflush(stdout);
E 40
I 40
D 49
    } else {
	printf("No connection.\n");
E 49
I 49
	if (!myopts[TELOPT_TTYPE]) {
D 63
	    dooption(TELOPT_TTYPE, 0);
E 63
I 63
	    dooption(TELOPT_TTYPE);
E 63
	}
I 70
	if (!myopts[TELOPT_NAWS]) {
	    dooption(TELOPT_NAWS);
	}
	if (!myopts[TELOPT_TSPEED]) {
	    dooption(TELOPT_TSPEED);
	}
	if (!myopts[TELOPT_LFLOW]) {
	    dooption(TELOPT_LFLOW);
	}
E 71
I 71
D 72
	send_do(TELOPT_SGA);
	send_will(TELOPT_TTYPE);
	send_will(TELOPT_NAWS);
	send_will(TELOPT_TSPEED);
	send_will(TELOPT_LFLOW);
E 72
I 72
	send_do(TELOPT_SGA, 1);
	send_will(TELOPT_TTYPE, 1);
	send_will(TELOPT_NAWS, 1);
	send_will(TELOPT_TSPEED, 1);
	send_will(TELOPT_LFLOW, 1);
	send_will(TELOPT_LINEMODE, 1);
I 79
D 83
#ifdef	KERBEROS
	if (kerberized)
		send_will(TELOPT_AUTHENTICATION, 1);
#endif
E 83
I 83
D 90
	send_will(TELOPT_ENVIRON, 1);
E 90
I 90
	send_will(TELOPT_NEW_ENVIRON, 1);
E 90
E 83
E 79
I 74
	send_do(TELOPT_STATUS, 1);
I 81
D 83
	if (env_getvalue("DISPLAY"))
E 83
I 83
	if (env_getvalue((unsigned char *)"DISPLAY"))
E 83
	    send_will(TELOPT_XDISPLOC, 1);
D 83
	send_will(TELOPT_ENVIRON, 1);
E 83
I 83
	if (eight)
	    tel_enter_binary(eight);
E 83
E 81
E 74
E 72
E 71
E 70
E 49
    }
D 49
    printf("Escape character is '%s'.\n", control(escape));
    fflush(stdout);
I 43
    return 1;
E 43
E 40
}
E 49
I 49
#   endif /* !defined(TN3270) */
E 49

D 49
tn(argc, argv)
	int argc;
	char *argv[];
{
D 41
	register int c;
E 41
	register struct hostent *host = 0;
E 49
I 49
#   if !defined(TN3270)
    for (;;) {
I 51
	int schedValue;

	while ((schedValue = Scheduler(0)) != 0) {
	    if (schedValue == -1) {
		setcommandmode();
		return;
	    }
	}

E 51
D 53
	if (Scheduler(SCHED_BLOCK) == -1) {
E 53
I 53
	if (Scheduler(1) == -1) {
E 53
	    setcommandmode();
	    return;
	}
    }
#   else /* !defined(TN3270) */
    for (;;) {
	int schedValue;
E 49

D 49
	if (connected) {
		printf("?Already connected to %s\n", hostname);
D 43
		return;
E 43
I 43
		return 0;
E 49
I 49
	while (!In3270 && !shell_active) {
D 53
	    if (Scheduler(SCHED_BLOCK) == -1) {
E 53
I 53
	    if (Scheduler(1) == -1) {
E 53
		setcommandmode();
		return;
	    }
E 49
E 43
	}
D 49
	if (argc < 2) {
D 41
		strcpy(line, "Connect ");
E 41
I 41
		(void) strcpy(line, "Connect ");
E 41
		printf("(to) ");
		gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
E 49
I 49

	while ((schedValue = Scheduler(0)) != 0) {
	    if (schedValue == -1) {
		setcommandmode();
		return;
	    }
E 49
	}
D 48
	if (argc > 3) {
E 48
I 48
D 49
	if ((argc < 2) || (argc > 3)) {
E 48
		printf("usage: %s host-name [port]\n", argv[0]);
D 43
		return;
E 43
I 43
		return 0;
E 43
	}
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	if (sin.sin_addr.s_addr != -1) {
		sin.sin_family = AF_INET;
D 41
		strcpy(hnamebuf, argv[1]);
E 41
I 41
		(void) strcpy(hnamebuf, argv[1]);
E 41
		hostname = hnamebuf;
E 49
I 49
		/* If there is data waiting to go out to terminal, don't
		 * schedule any more data for the terminal.
		 */
D 61
	if (tfrontp-tbackp) {
E 61
I 61
D 62
	if (ring_full_count(ttyoring)) {
E 62
I 62
	if (ring_full_count(&ttyoring)) {
E 62
E 61
	    schedValue = 1;
E 49
	} else {
D 49
		host = gethostbyname(argv[1]);
		if (host) {
			sin.sin_family = host->h_addrtype;
I 44
#ifndef	NOT43
E 44
			bcopy(host->h_addr_list[0], (caddr_t)&sin.sin_addr,
				host->h_length);
I 44
#else	NOT43
			bcopy(host->h_addr, (caddr_t)&sin.sin_addr,
				host->h_length);
#endif	NOT43
E 44
			hostname = host->h_name;
		} else {
			printf("%s: unknown host\n", argv[1]);
D 43
			return;
E 43
I 43
			return 0;
E 49
I 49
	    if (shell_active) {
		if (shell_continue() == 0) {
		    ConnectScreen();
E 49
E 43
		}
I 49
	    } else if (In3270) {
		schedValue = DoTerminalOutput();
	    }
E 49
	}
D 49
	sin.sin_port = sp->s_port;
	if (argc == 3) {
		sin.sin_port = atoi(argv[2]);
D 41
		if (sin.sin_port <= 0) {
E 41
I 41
		if (sin.sin_port == 0) {
E 41
			sp = getservbyname(argv[2], "tcp");
			if (sp)
				sin.sin_port = sp->s_port;
			else {
				printf("%s: bad port number\n", argv[2]);
D 43
				return;
E 43
I 43
				return 0;
E 43
			}
		} else {
			sin.sin_port = atoi(argv[2]);
			sin.sin_port = htons(sin.sin_port);
		}
		telnetport = 0;
I 39
	} else {
		telnetport = 1;
E 49
I 49
	if (schedValue && (shell_active == 0)) {
D 53
	    if (Scheduler(SCHED_BLOCK) == -1) {
E 53
I 53
	    if (Scheduler(1) == -1) {
E 53
		setcommandmode();
		return;
	    }
E 49
E 39
	}
D 49
	signal(SIGINT, intr);
I 39
	signal(SIGQUIT, intr2);
E 39
	signal(SIGPIPE, deadpeer);
	printf("Trying...\n");
	do {
		net = socket(AF_INET, SOCK_STREAM, 0);
		if (net < 0) {
			perror("telnet: socket");
D 43
			return;
E 43
I 43
			return 0;
E 43
		}
I 44
#ifndef	NOT43
E 44
D 41
		if (debug && setsockopt(net, SOL_SOCKET, SO_DEBUG, &debug,
		    sizeof(debug)) < 0)
E 41
I 41
		if (debug &&
				setsockopt(net, SOL_SOCKET, SO_DEBUG,
D 44
					(char *)&debug, sizeof(debug)) < 0) {
E 44
I 44
					(char *)&debug, sizeof(debug)) < 0)
#else	NOT43
		if (debug && setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
#endif	NOT43
E 44
E 41
			perror("setsockopt (SO_DEBUG)");
D 41
		if (connect(net, (caddr_t)&sin, sizeof (sin)) < 0) {
E 41
I 41
D 44
		}
E 44
I 44

E 44
		if (connect(net, (struct sockaddr *)&sin, sizeof (sin)) < 0) {
I 44
#ifndef	NOT43
E 44
E 41
			if (host && host->h_addr_list[1]) {
				int oerrno = errno;

				fprintf(stderr,
				    "telnet: connect to address %s: ",
				    inet_ntoa(sin.sin_addr));
				errno = oerrno;
D 41
				perror(0);
E 41
I 41
				perror((char *)0);
E 41
				host->h_addr_list++;
				bcopy(host->h_addr_list[0],
				    (caddr_t)&sin.sin_addr, host->h_length);
				fprintf(stderr, "Trying %s...\n",
					inet_ntoa(sin.sin_addr));
				(void) close(net);
				continue;
			}
I 44
#endif	NOT43
E 44
			perror("telnet: connect");
			signal(SIGINT, SIG_DFL);
D 43
			return;
E 43
I 43
			signal(SIGQUIT, SIG_DFL);
			return 0;
E 43
		}
		connected++;
	} while (connected == 0);
D 40
	call(status, "status", 0);
E 40
I 40
	call(status, "status", "notmuch", 0);
E 40
	if (setjmp(peerdied) == 0)
		telnet();
	fprintf(stderr, "Connection closed by foreign host.\n");
	exit(1);
I 43
	/*NOTREACHED*/
E 49
I 49
    }
#   endif /* !defined(TN3270) */
E 49
E 43
}
D 49


#define HELPINDENT (sizeof ("connect"))

char	openhelp[] =	"connect to a site";
char	closehelp[] =	"close current connection";
char	quithelp[] =	"exit telnet";
char	zhelp[] =	"suspend telnet";
D 43
char	escapehelp[] =	"set escape character";
E 43
char	statushelp[] =	"print status information";
char	helphelp[] =	"print help information";
D 39
char	crmodhelp[] =	"toggle mapping of received carriage returns";
char	togglestring[] = "toggle various (debugging) options";
char	sendhelp[] =	"transmit special characters";
E 39
I 39
D 40
char	togglestring[] = "toggle various options ('toggle ?' for more)";
E 40
char	sendhelp[] =	"transmit special characters ('send ?' for more)";
D 40
char	sethelp[] = 	"set various special characters ('set ?' for more)";
char	modehelp[] =	"change operating mode ('mode ?' for more)";
E 40
I 40
char	sethelp[] = 	"set operating parameters ('set ?' for more)";
char	togglestring[] ="toggle operating parameters ('toggle ?' for more)";
char	displayhelp[] =	"display operating parameters";
char	modehelp[] =
		"try to enter line-by-line or character-at-a-time mode";
E 40
E 39

int	help();

struct cmd cmdtab[] = {
D 39
	{ "open",	openhelp,	tn, 1, 0 },
	{ "close",	closehelp,	bye, 1, 1 },
	{ "quit",	quithelp,	quit, 1, 0 },
	{ "z",		zhelp,		suspend, 1, 0 },
	{ "escape",	escapehelp,	setescape, 1, 0 },
	{ "status",	statushelp,	status, 1, 0 },
	{ "crmod",	crmodhelp,	setcrmod, 1, 0 },
	{ "send",	sendhelp,	sendcmd, 1, 1 },
	    { "transmit",	sendhelp,	sendcmd, 0, 1 },
	    { "xmit",		sendhelp,	sendcmd, 0, 1 },
	{ "toggle",	togglestring,	toggle, 1, 0 },
	{ "?",		helphelp,	help, 1, 0 },
	{ "help",	helphelp,	help, 0, 0 },
E 39
I 39
D 43
	{ "open",	openhelp,	tn,		1, 0 },
E 43
	{ "close",	closehelp,	bye,		1, 1 },
I 43
	{ "display",	displayhelp,	display,	1, 0 },
	{ "mode",	modehelp,	modecmd,	1, 1 },
	{ "open",	openhelp,	tn,		1, 0 },
E 43
	{ "quit",	quithelp,	quit,		1, 0 },
D 43
	{ "z",		zhelp,		suspend,	1, 0 },
	{ "escape",	escapehelp,	setescape,	1, 0 },
	{ "status",	statushelp,	status,		1, 0 },
D 40
	{ "crmod",	crmodhelp,	setcrmod,	1, 0 },
E 40
I 40
	{ "crmod",	crmodhelp,	togcrmod,	1, 0 },
E 43
E 40
	{ "send",	sendhelp,	sendcmd,	1, 1 },
D 40
	{ "set",	sethelp,	setcmd,		1, 0 },
	{ "mode",	modehelp,	modecmd,	1, 1 },
E 40
D 43
	{ "transmit",	sendhelp,	sendcmd,	0, 1 },
	{ "xmit",	sendhelp,	sendcmd,	0, 1 },
E 43
I 40
	{ "set",	sethelp,	setcmd,		1, 0 },
I 43
	{ "status",	statushelp,	status,		1, 0 },
E 43
E 40
	{ "toggle",	togglestring,	toggle,		1, 0 },
I 40
D 43
	{ "display",	displayhelp,	display,	1, 0 },
	{ "mode",	modehelp,	modecmd,	1, 1 },
E 43
I 43
	{ "z",		zhelp,		suspend,	1, 0 },
E 43
E 40
	{ "?",		helphelp,	help,		1, 0 },
D 43
	{ "help",	helphelp,	help,		0, 0 },
E 43
E 39
	0
};

I 43
char	crmodhelp[] =	"deprecated command -- use 'toggle crmod' instead";
char	escapehelp[] =	"deprecated command -- use 'set escape' instead";
E 43

I 43
struct cmd cmdtab2[] = {
	{ "help",	helphelp,	help,		0, 0 },
	{ "escape",	escapehelp,	setescape,	1, 0 },
	{ "crmod",	crmodhelp,	togcrmod,	1, 0 },
	0
};

E 49
I 49

I 63
#if	0	/* XXX - this not being in is a bug */
E 63
E 49
E 43
/*
I 54
 * nextitem()
 *
 *	Return the address of the next "item" in the TELNET data
 * stream.  This will be the address of the next character if
 * the current address is a user data character, or it will
 * be the address of the character following the TELNET command
 * if the current address is a TELNET IAC ("I Am a Command")
 * character.
 */

D 83
static char *
E 83
I 83
    static char *
E 83
nextitem(current)
D 83
char	*current;
E 83
I 83
    char *current;
E 83
{
    if ((*current&0xff) != IAC) {
	return current+1;
    }
    switch (*(current+1)&0xff) {
    case DO:
    case DONT:
    case WILL:
    case WONT:
	return current+3;
    case SB:		/* loop forever looking for the SE */
	{
	    register char *look = current+2;

	    for (;;) {
		if ((*look++&0xff) == IAC) {
		    if ((*look++&0xff) == SE) {
			return look;
		    }
		}
	    }
	}
    default:
	return current+2;
    }
}
I 63
#endif	/* 0 */
E 63

/*
 * netclear()
 *
 *	We are about to do a TELNET SYNCH operation.  Clear
 * the path to the network.
 *
 *	Things are a bit tricky since we may have sent the first
 * byte or so of a previous TELNET command into the network.
 * So, we have to scan the network buffer from the beginning
 * until we are up to where we want to be.
 *
 *	A side effect of what we do, just to keep things
 * simple, is to clear the urgent data pointer.  The principal
 * caller should be setting the urgent data pointer AFTER calling
 * us in any case.
 */

D 83
static void
E 83
I 83
    static void
E 83
netclear()
{
#if	0	/* XXX */
    register char *thisitem, *next;
    char *good;
#define	wewant(p)	((nfrontp > p) && ((*p&0xff) == IAC) && \
				((*(p+1)&0xff) != EC) && ((*(p+1)&0xff) != EL))

    thisitem = netobuf;

    while ((next = nextitem(thisitem)) <= netobuf.send) {
	thisitem = next;
    }

    /* Now, thisitem is first before/at boundary. */

    good = netobuf;	/* where the good bytes go */

    while (netoring.add > thisitem) {
	if (wewant(thisitem)) {
	    int length;

	    next = thisitem;
	    do {
		next = nextitem(next);
	    } while (wewant(next) && (nfrontp > next));
	    length = next-thisitem;
D 92
	    memcpy(good, thisitem, length);
E 92
I 92
	    memmove(good, thisitem, length);
E 92
	    good += length;
	    thisitem = next;
	} else {
	    thisitem = nextitem(thisitem);
	}
    }

#endif	/* 0 */
}

/*
E 54
D 49
 * Help command.
E 49
I 49
 * These routines add various telnet commands to the data stream.
E 49
 */
D 49
help(argc, argv)
	int argc;
	char *argv[];
{
	register struct cmd *c;
E 49

I 54
D 83
static void
E 83
I 83
    static void
E 83
doflush()
{
    NET2ADD(IAC, DO);
    NETADD(TELOPT_TM);
    flushline = 1;
    flushout = 1;
D 81
    ttyflush(1);			/* Flush/drop output */
E 81
I 81
    (void) ttyflush(1);			/* Flush/drop output */
E 81
    /* do printoption AFTER flush, otherwise the output gets tossed... */
D 71
    printoption("<SENT", doopt, TELOPT_TM, 0);
E 71
I 71
D 83
    printoption("SENT", "do", TELOPT_TM);
E 83
I 83
    printoption("SENT", DO, TELOPT_TM);
E 83
E 71
}

E 54
D 49
	if (argc == 1) {
		printf("Commands may be abbreviated.  Commands are:\n\n");
		for (c = cmdtab; c->name; c++)
			if (c->dohelp) {
				printf("%-*s\t%s\n", HELPINDENT, c->name,
								    c->help);
			}
D 43
		return;
E 43
I 43
		return 0;
E 43
	}
	while (--argc > 0) {
		register char *arg;
		arg = *++argv;
		c = getcmd(arg);
D 41
		if (c == (struct cmd *)-1)
E 41
I 41
		if (c == Ambiguous(struct cmd *))
E 41
			printf("?Ambiguous help command %s\n", arg);
		else if (c == (struct cmd *)0)
			printf("?Invalid help command %s\n", arg);
		else
			printf("%s\n", c->help);
	}
I 43
	return 0;
E 43
}
/*
 * Call routine with argc, argv set from args (terminated by 0).
 * VARARGS2
 */
call(routine, args)
	int (*routine)();
D 41
	int args;
E 41
I 41
	char *args;
E 49
I 49
D 83
void
E 83
I 83
    void
E 83
xmitAO()
E 49
E 41
{
D 41
	register int *argp;
E 41
I 41
D 49
	register char **argp;
E 41
	register int argc;

	for (argc = 0, argp = &args; *argp++ != 0; argc++)
		;
D 43
	(*routine)(argc, &args);
E 43
I 43
	return (*routine)(argc, &args);
E 49
I 49
    NET2ADD(IAC, AO);
I 74
D 83
    printoption("SENT", "IAC", AO);
E 83
I 83
    printoption("SENT", IAC, AO);
E 83
E 74
    if (autoflush) {
	doflush();
    }
E 49
E 43
}

D 49
makeargv()
{
	register char *cp;
	register char **argp = margv;
E 49

D 49
	margc = 0;
	for (cp = line; *cp;) {
		while (isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*argp++ = cp;
		margc += 1;
		while (*cp != '\0' && !isspace(*cp))
			cp++;
		if (*cp == '\0')
			break;
		*cp++ = '\0';
	}
	*argp++ = 0;
E 49
I 49
D 83
void
E 83
I 83
    void
E 83
xmitEL()
{
    NET2ADD(IAC, EL);
I 74
D 83
    printoption("SENT", "IAC", EL);
E 83
I 83
    printoption("SENT", IAC, EL);
E 83
E 74
E 49
}

D 49
char **
getnextcmd(name)
char *name;
E 49
I 49
D 83
void
E 83
I 83
    void
E 83
xmitEC()
E 49
{
D 49
    struct cmd *c = (struct cmd *) name;

    return (char **) (c+1);
E 49
I 49
    NET2ADD(IAC, EC);
I 74
D 83
    printoption("SENT", "IAC", EC);
E 83
I 83
    printoption("SENT", IAC, EC);
E 83
E 74
E 49
}

D 49
struct cmd *
getcmd(name)
char *name;
E 49
I 49

D 83
#if	defined(NOT43)
int
#else	/* defined(NOT43) */
void
#endif	/* defined(NOT43) */
E 83
I 83
    int
E 83
dosynch()
E 49
{
D 43
    return (struct cmd *) genget(name, (char **) cmdtab, getnextcmd);
E 43
I 43
D 49
    struct cmd *cm;
E 49
I 49
    netclear();			/* clear the path to the network */
D 58
    NET2ADD(IAC, DM);
E 58
I 58
    NETADD(IAC);
    setneturg();
    NETADD(DM);
I 74
D 83
    printoption("SENT", "IAC", DM);
E 74
E 58
E 49

D 49
    if (cm = (struct cmd *) genget(name, (char **) cmdtab, getnextcmd)) {
	return cm;
    } else {
	return (struct cmd *) genget(name, (char **) cmdtab2, getnextcmd);
    }
E 49
I 49
#if	defined(NOT43)
    return 0;
#endif	/* defined(NOT43) */
E 83
I 83
    printoption("SENT", IAC, DM);
    return 1;
E 83
E 49
E 43
D 54
}

D 49
command(top)
	int top;
E 49
I 49
void
doflush()
E 49
{
D 49
	register struct cmd *c;
E 49
I 49
    NET2ADD(IAC, DO);
    NETADD(TELOPT_TM);
    flushline = 1;
    flushout = 1;
    ttyflush(1);			/* Flush/drop output */
    /* do printoption AFTER flush, otherwise the output gets tossed... */
    printoption("<SENT", doopt, TELOPT_TM, 0);
E 54
}
E 49
D 39
	int oldmode, wasopen;
E 39
I 39
D 41
	int wasopen;
E 41
E 39

D 39
	oldmode = mode(0);
E 39
I 39
D 49
	setcommandmode();
E 39
D 43
	if (!top)
E 43
I 43
	if (!top) {
E 43
		putchar('\n');
D 43
	else
E 43
I 43
	} else {
E 43
		signal(SIGINT, SIG_DFL);
I 43
		signal(SIGQUIT, SIG_DFL);
	}
E 43
	for (;;) {
		printf("%s> ", prompt);
		if (gets(line) == 0) {
			if (feof(stdin))
				quit();
			break;
		}
		if (line[0] == 0)
			break;
		makeargv();
		c = getcmd(margv[0]);
D 41
		if (c == (struct cmd *)-1) {
E 41
I 41
		if (c == Ambiguous(struct cmd *)) {
E 41
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == 0) {
			printf("?Invalid command\n");
			continue;
		}
		if (c->needconnect && !connected) {
			printf("?Need to be connected first.\n");
			continue;
		}
D 43
		(*c->handler)(margc, margv);
		if (c->handler != help)
E 43
I 43
		if ((*c->handler)(margc, margv)) {
E 43
			break;
I 43
		}
E 43
	}
	if (!top) {
D 39
		if (!connected)
E 39
I 39
		if (!connected) {
E 39
			longjmp(toplevel, 1);
D 39
		(void) mode(oldmode);
E 39
I 39
			/*NOTREACHED*/
		}
		setconnmode();
E 39
	}
E 49
I 49
D 83
void
E 83
I 83
int want_status_response = 0;

    int
E 83
I 74
get_status()
{
D 83
    char tmp[16];
    register char *cp;
E 83
I 83
    unsigned char tmp[16];
    register unsigned char *cp;
E 83

    if (my_want_state_is_dont(TELOPT_STATUS)) {
	printf("Remote side does not support STATUS option\n");
D 83
	return;
E 83
I 83
	return 0;
E 83
    }
D 83
    if (!showoptions)
	printf("You will not see the response unless you set \"options\"\n");

E 83
    cp = tmp;

    *cp++ = IAC;
    *cp++ = SB;
    *cp++ = TELOPT_STATUS;
    *cp++ = TELQUAL_SEND;
    *cp++ = IAC;
    *cp++ = SE;
    if (NETROOM() >= cp - tmp) {
	ring_supply_data(&netoring, tmp, cp-tmp);
	printsub('>', tmp+2, cp - tmp - 2);
    }
I 83
    ++want_status_response;
    return 1;
E 83
}

D 83
void
E 83
I 83
    void
E 83
E 74
intp()
{
    NET2ADD(IAC, IP);
I 74
D 83
    printoption("SENT", "IAC", IP);
E 83
I 83
    printoption("SENT", IAC, IP);
E 83
E 74
    flushline = 1;
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
    }
E 49
I 41
}
D 49

/*
 * main.  Parse arguments, invoke the protocol or command parser.
 */
E 49

D 49

main(argc, argv)
	int argc;
	char *argv[];
E 49
I 49
D 83
void
E 83
I 83
    void
E 83
sendbrk()
E 49
{
D 49
	sp = getservbyname("telnet", "tcp");
	if (sp == 0) {
		fprintf(stderr, "telnet: tcp/telnet: unknown service\n");
		exit(1);
	}
	NetTrace = stdout;
	ioctl(0, TIOCGETP, (char *)&ottyb);
	ioctl(0, TIOCGETC, (char *)&otc);
	ioctl(0, TIOCGLTC, (char *)&oltc);
I 42
#if	defined(LNOFLSH)
	ioctl(0, TIOCLGET, (char *)&autoflush);
D 43
	autoflush &= LNOFLSH;
E 43
I 43
	autoflush = !(autoflush&LNOFLSH);	/* if LNOFLSH, no autoflush */
#else	/* LNOFLSH */
	autoflush = 1;
E 43
#endif	/* LNOFLSH */
E 42
	ntc = otc;
D 44
	ntc.t_eofc = -1;		/* we don't want to use EOF */
E 44
I 42
	nltc = oltc;
E 42
	nttyb = ottyb;
	setbuf(stdin, (char *)0);
	setbuf(stdout, (char *)0);
	prompt = argv[0];
	if (argc > 1 && !strcmp(argv[1], "-d")) {
		debug = 1;
		argv++;
		argc--;
	}
	if (argc > 1 && !strcmp(argv[1], "-n")) {
	    argv++;
	    argc--;
	    if (argc > 1) {		/* get file name */
		NetTrace = fopen(argv[1], "w");
		argv++;
		argc--;
		if (NetTrace == NULL) {
		    NetTrace = stdout;
		}
	    }
	}
	if (argc != 1) {
		if (setjmp(toplevel) != 0)
			exit(0);
		tn(argc, argv);
	}
	setjmp(toplevel);
	for (;;)
		command(1);
E 49
I 49
    NET2ADD(IAC, BREAK);
I 74
D 83
    printoption("SENT", "IAC", BREAK);
E 83
I 83
    printoption("SENT", IAC, BREAK);
E 83
E 74
    flushline = 1;
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
I 70
    }
}
I 72

D 83
void
E 83
I 83
    void
E 83
sendabort()
{
    NET2ADD(IAC, ABORT);
I 74
D 83
    printoption("SENT", "IAC", ABORT);
E 83
I 83
    printoption("SENT", IAC, ABORT);
E 83
E 74
    flushline = 1;
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
    }
}

D 83
void
E 83
I 83
    void
E 83
sendsusp()
{
    NET2ADD(IAC, SUSP);
I 74
D 83
    printoption("SENT", "IAC", SUSP);
E 83
I 83
    printoption("SENT", IAC, SUSP);
E 83
E 74
    flushline = 1;
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
    }
}

D 83
void
E 83
I 83
    void
E 83
sendeof()
{
D 74
   NET2ADD(IAC, xEOF);
E 74
I 74
    NET2ADD(IAC, xEOF);
D 83
    printoption("SENT", "IAC", xEOF);
E 83
I 83
    printoption("SENT", IAC, xEOF);
E 83
I 82
}

D 83
void
E 83
I 83
    void
E 83
sendayt()
{
    NET2ADD(IAC, AYT);
D 83
    printoption("SENT", "IAC", AYT);
E 83
I 83
    printoption("SENT", IAC, AYT);
E 83
E 82
E 74
}

E 72
/*
 * Send a window size update to the remote system.
 */

D 83
void
E 83
I 83
    void
E 83
sendnaws()
{
    long rows, cols;
I 72
    unsigned char tmp[16];
    register unsigned char *cp;
E 72

D 72
#define        NETADDCHAR(x) \
    { \
	if (((x) & 0xff) == 0xff) { \
	    NET2ADD(IAC, IAC) \
	} else { \
	    NETADD(x) \
	} \
    }
#define        NETADDSHORT(x)  { NETADDCHAR(x >> 8); NETADDCHAR(x & 0xff) }
E 72
I 72
    if (my_state_is_wont(TELOPT_NAWS))
	return;
E 72

I 72
#define	PUTSHORT(cp, x) { if ((*cp++ = ((x)>>8)&0xff) == IAC) *cp++ = IAC; \
			    if ((*cp++ = ((x))&0xff) == IAC) *cp++ = IAC; }

E 72
    if (TerminalWindowSize(&rows, &cols) == 0) {	/* Failed */
	return;
    }

D 72
    if (NETROOM() >= 3 + 8 + 2) {
	NET2ADD(IAC, SB);
	NETADD(TELOPT_NAWS);
	NETADDSHORT(cols);
	NETADDSHORT(rows);
	NET2ADD(IAC, SE);
E 72
I 72
    cp = tmp;

    *cp++ = IAC;
    *cp++ = SB;
    *cp++ = TELOPT_NAWS;
    PUTSHORT(cp, cols);
    PUTSHORT(cp, rows);
    *cp++ = IAC;
    *cp++ = SE;
    if (NETROOM() >= cp - tmp) {
	ring_supply_data(&netoring, tmp, cp-tmp);
	printsub('>', tmp+2, cp - tmp - 2);
E 72
E 70
    }
I 71
}

I 83
    void
E 83
D 74
tel_enter_binary()
E 74
I 74
tel_enter_binary(rw)
D 83
int rw;
E 83
I 83
    int rw;
E 83
E 74
{
D 72
    send_do(TELOPT_BINARY);
    send_will(TELOPT_BINARY);
E 72
I 72
D 74
    send_do(TELOPT_BINARY, 1);
    send_will(TELOPT_BINARY, 1);
E 74
I 74
    if (rw&1)
	send_do(TELOPT_BINARY, 1);
    if (rw&2)
	send_will(TELOPT_BINARY, 1);
E 74
E 72
}

I 83
    void
E 83
D 74
tel_leave_binary()
E 74
I 74
tel_leave_binary(rw)
D 83
int rw;
E 83
I 83
    int rw;
E 83
E 74
{
D 72
    send_dont(TELOPT_BINARY);
    send_wont(TELOPT_BINARY);
E 72
I 72
D 74
    send_dont(TELOPT_BINARY, 1);
    send_wont(TELOPT_BINARY, 1);
E 74
I 74
    if (rw&1)
	send_dont(TELOPT_BINARY, 1);
    if (rw&2)
	send_wont(TELOPT_BINARY, 1);
E 74
E 72
E 71
E 49
E 41
E 38
E 5
E 2
}
E 1
