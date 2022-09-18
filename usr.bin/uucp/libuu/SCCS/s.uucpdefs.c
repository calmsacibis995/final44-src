h40563
s 00002/00002/00037
d D 8.1 93/06/06 22:11:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00031
d D 5.7 91/04/24 17:33:55 bostic 7 6
c new copyright; att/bsd/shared
e
s 00003/00002/00029
d D 5.6 89/05/11 13:44:56 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00030
d D 5.5 85/10/09 16:26:50 bloom 5 4
c use defined constant (from rick@seismo)
e
s 00002/00005/00029
d D 5.4 85/06/23 13:41:51 bloom 4 3
c fixes from rick adams
e
s 00003/00001/00031
d D 5.3 85/04/10 15:22:11 ralph 3 2
c more changes from rick adams.
e
s 00016/00010/00016
d D 5.2 85/01/22 14:12:49 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00026/00000/00000
d D 5.1 83/07/02 17:57:46 sam 1 0
c date and time created 83/07/02 17:57:46 by sam
e
u
U
t
T
I 7
/*-
D 8
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.proprietary.c%
 */

E 7
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
#endif /* not lint */
E 7

#include "uucp.h"
I 6
#include "pathnames.h"
E 6

D 2
char Progname[10];
E 2
I 2
char Progname[64];
E 2
int Ifn, Ofn;
D 2
char Rmtname[16];
char User[16];
E 2
I 2
D 3
char Rmtname[64];
E 3
I 3
D 5
char RRmtname[64];
E 5
I 5
char RRmtname[MAXFULLNAME];
E 5
char *Rmtname = RRmtname;
E 3
char User[128];
E 2
char Loginuser[16];
D 4
char Myname[16];
I 2
char Myfullname[64];
E 2
int Bspeed;
E 4
I 4
char Myname[MAXBASENAME+1];
E 4
char Wrkdir[WKDSIZE];

char *Spool = SPOOL;
D 2
#ifdef	UUDIR
char DLocal[16];
char DLocalX[16];
#endif
E 2
I 2
char DLocal[64];
char DLocalX[64];
E 2
int Debug = 0;
D 2
int Pkdebug = 0;
E 2
D 4
int Packflg = 0;
D 2
int Pkdrvon = 0;
E 2
long Retrytime;
E 4
I 4
time_t Retrytime;
E 4
D 2
int Unet = 0;	/* 1 == UNET connection, else 0.  kludge to suppress ioctl */
E 2
I 2
short Usrf = 0;			/* Uustat global flag */
int IsTcpIp = 0;	/* 1 == TCP/IP connection, else 0.  kludge to suppress ioctl */
char MaxGrade = '\177';
I 3
char DefMaxGrade = '\177';
E 3
int nologinflag = 0;
D 6
char NOLOGIN[] = "/etc/nologin";
E 6
I 6
char NOLOGIN[] = _PATH_NOLOGIN;
E 6

/* Save some data space */
D 6
char DEVNULL[] = "/dev/null";
E 6
I 6
char DEVNULL[] = _PATH_DEVNULL;
E 6
char CANTOPEN[] = "CAN'T OPEN";
char _FAILED[] = "FAILED";
E 2
E 1
