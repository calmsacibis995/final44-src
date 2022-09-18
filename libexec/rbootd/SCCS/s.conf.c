h22550
s 00002/00002/00062
d D 8.1 93/06/04 19:02:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00063
d D 5.3 93/06/04 19:02:12 bostic 4 2
c put the Regents copyright last so 44yank works
e
s 00002/00002/00062
d R 8.1 93/06/04 18:58:18 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00060
d D 5.2 92/07/23 16:42:17 bostic 2 1
c Welcome to the Wonderful World of ANSI C!
e
s 00060/00000/00000
d D 5.1 92/07/23 15:44:52 bostic 1 0
c date and time created 92/07/23 15:44:52 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
E 4
 * Copyright (c) 1988, 1992 The University of Utah and the Center
 *	for Software Science (CSS).
I 4
D 5
 * Copyright (c) 1992 Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Center for Software Science of the University of Utah Computer
 * Science Department.  CSS requests users of this software to return
 * to css-dist@cs.utah.edu any improvements that they make and grant
 * CSS redistribution rights.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * Utah $Hdr: conf.c 3.1 92/07/06$
 * Author: Jeff Forys, University of Utah CSS
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <sys/param.h>
#include <sys/time.h>

#include <stdio.h>
E 2
#include "defs.h"
#include "pathnames.h"

/*
**  Define (and possibly initialize) global variables here.
**
**  Caveat:
**	The maximum number of bootable files (`char *BootFiles[]') is
**	limited to C_MAXFILE (i.e. the maximum number of files that
**	can be spec'd in the configuration file).  This was done to
**	simplify the boot file search code.
*/

char	*ProgName;				/* path-stripped argv[0] */
char	MyHost[MAXHOSTNAMELEN+1];		/* host name */
int	MyPid;					/* process id */
int	DebugFlg = 0;				/* set true if debugging */
int	BootAny = 0;				/* set true if we boot anyone */

char	*ConfigFile = NULL;			/* configuration file */
char	*DfltConfig = _PATH_RBOOTDCONF;		/* default configuration file */
char	*PidFile = _PATH_RBOOTDPID;		/* file w/pid of server */
char	*BootDir = _PATH_RBOOTDLIB;		/* directory w/boot files */
char	*DbgFile = _PATH_RBOOTDDBG;		/* debug output file */

FILE	*DbgFp = NULL;				/* debug file pointer */
char	*IntfName = NULL;			/* intf we are attached to */

u_short	SessionID = 0;				/* generated session ID */

char	*BootFiles[C_MAXFILE];			/* list of boot files */

CLIENT	*Clients = NULL;			/* list of addrs we'll accept */
RMPCONN	*RmpConns = NULL;			/* list of active connections */

char	RmpMcastAddr[RMP_ADDRLEN] = RMP_ADDR;	/* RMP multicast address */
E 1
