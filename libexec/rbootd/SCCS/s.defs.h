h05415
s 00002/00002/00157
d D 8.1 93/06/04 19:02:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00158
d D 5.3 93/06/04 19:02:13 bostic 4 2
c put the Regents copyright last so 44yank works
e
s 00002/00002/00157
d R 8.1 93/06/04 18:58:21 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00017/00124
d D 5.2 92/07/23 16:42:18 bostic 2 1
c Welcome to the Wonderful World of ANSI C!
e
s 00141/00000/00000
d D 5.1 92/07/23 15:44:55 bostic 1 0
c date and time created 92/07/23 15:44:55 by bostic
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
 * Utah $Hdr: defs.h 3.1 92/07/06$
 * Author: Jeff Forys, University of Utah CSS
 */

D 2
#include <stdio.h>
#include <signal.h>

#include <sys/param.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>

E 2
#include "rmp.h"
#include "rmp_var.h"

/*
**  Common #define's and external variables.  All other files should
**  include this.
*/

/*
 *  This may be defined in <sys/param.h>, if not, it's defined here.
 */
#ifndef	MAXHOSTNAMELEN
#define	MAXHOSTNAMELEN 64
#endif

/*
 *  SIGUSR1 and SIGUSR2 are defined in <signal.h> for 4.3BSD systems.
 */
#ifndef SIGUSR1
#define	SIGUSR1 SIGEMT
#endif
#ifndef SIGUSR2
#define	SIGUSR2 SIGFPE
#endif

/*
 *  These can be faster & more efficient than strcmp()/strncmp()...
 */
#define	STREQN(s1,s2)		((*s1 == *s2) && (strcmp(s1,s2) == 0))
#define	STRNEQN(s1,s2,n)	((*s1 == *s2) && (strncmp(s1,s2,n) == 0))

/*
 *  Configuration file limitations.
 */
#define	C_MAXFILE	10		/* max number of boot-able files */
#define	C_LINELEN	1024		/* max length of line */

/*
 *  Direction of packet (used as argument to DispPkt).
 */
#define	DIR_RCVD	0
#define	DIR_SENT	1
#define	DIR_NONE	2

/*
 *  These need not be functions, so...
 */
D 2
#define	FreeStr(str)	free((char *) str)
#define	FreeClient(cli)	free((char *) cli)
E 2
I 2
#define	FreeStr(str)	free(str)
#define	FreeClient(cli)	free(cli)
E 2
#define	GenSessID()	(++SessionID ? SessionID: ++SessionID)

/*
 *  Converting an Ethernet address to a string is done in many routines.
 *  Using `rmp.hp_hdr.saddr' works because this field is *never* changed;
 *  it will *always* contain the source address of the packet.
 */
D 2
extern	char *GetEtherAddr();
E 2
#define	EnetStr(rptr)	GetEtherAddr(&(rptr)->rmp.hp_hdr.saddr[0])

/*
 *  Every machine we can boot will have one of these allocated for it
 *  (unless there are no restrictions on who we can boot).
 */
typedef struct client_s {
	u_char			addr[RMP_ADDRLEN];	/* addr of machine */
	char			*files[C_MAXFILE];	/* boot-able files */
	struct client_s		*next;			/* ptr to next */
} CLIENT;

/*
 *  Every active connection has one of these allocated for it.
 */
typedef struct rmpconn_s {
	struct rmp_packet	rmp;			/* RMP packet */
	int			rmplen;			/* length of packet */
	struct timeval		tstamp;			/* last time active */
	int			bootfd;			/* open boot file */
	struct rmpconn_s	*next;			/* ptr to next */
} RMPCONN;

/*
 *  All these variables are defined in "conf.c".
 */
extern	char	*ProgName;		/* path-stripped argv[0] */
extern	char	MyHost[];		/* this hosts' name */
extern	int	MyPid;			/* this processes' ID */
extern	int	DebugFlg;		/* set true if debugging */
extern	int	BootAny;		/* set true if we can boot anyone */

extern	char	*ConfigFile;		/* configuration file */
extern	char	*DfltConfig;		/* default configuration file */
extern	char	*DbgFile;		/* debug output file */
extern	char	*PidFile;		/* file containing pid of server */
extern	char	*BootDir;		/* directory w/boot files */

extern	FILE	*DbgFp;			/* debug file pointer */
extern	char	*IntfName;		/* interface we are attached to */

extern	u_short	SessionID;		/* generated session ID */

extern	char	*BootFiles[];		/* list of boot files */

extern	CLIENT	*Clients;		/* list of addrs we'll accept */
extern	RMPCONN	*RmpConns;		/* list of active connections */

extern	char	RmpMcastAddr[];		/* RMP multicast address */

D 2
/*
 * Some common routines that generally cause lint to complain.
 */
#if defined(lint) && !defined(BSD4_4)
extern	char	*malloc();
#endif
E 2
I 2
void	 AddConn __P((RMPCONN *));
int	 BootDone __P((RMPCONN *));
void	 BpfClose __P((void));
char	*BpfGetIntfName __P((char **));
int	 BpfOpen __P((void));
int	 BpfRead __P((RMPCONN *, int));
int	 BpfWrite __P((RMPCONN *));
void	 DebugOff __P((int));
void	 DebugOn __P((int));
void	 DispPkt __P((RMPCONN *, int));
void	 DoTimeout __P((void));
void	 DspFlnm __P((u_int, char *));
void	 Exit __P((int));
CLIENT	*FindClient __P((RMPCONN *));
RMPCONN	*FindConn __P((RMPCONN *));
void	 FreeClients __P((void));
void	 FreeConn __P((RMPCONN *));
void	 FreeConns __P((void));
int	 GetBootFiles __P((void));
char	*GetEtherAddr __P((u_char *));
CLIENT	*NewClient __P((u_char *));
RMPCONN	*NewConn __P((RMPCONN *));
char	*NewStr __P((char *));
u_char	*ParseAddr __P((char *));
int	 ParseConfig __P((void));
void	 ProcessPacket __P((RMPCONN *, CLIENT *));
void	 ReConfig __P((int));
void	 RemoveConn __P((RMPCONN *));
int	 SendBootRepl __P((struct rmp_packet *, RMPCONN *, char *[]));
int	 SendFileNo __P((struct rmp_packet *, RMPCONN *, char *[]));
int	 SendPacket __P((RMPCONN *));
int	 SendReadRepl __P((RMPCONN *));
int	 SendServerID __P((RMPCONN *));
E 2
E 1
