h34281
s 00003/00002/00098
d D 8.2 95/04/28 12:16:47 tef 21 20
c Support for printers connected via ethernet/TCP and terminal servers.
e
s 00002/00002/00098
d D 8.1 93/06/06 13:58:51 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00098
d D 5.10 93/02/26 11:08:33 torek 19 18
c fix typo (how did this ever work? gcc is unfathomable)
e
s 00001/00001/00099
d D 5.9 92/09/15 10:39:06 elan 18 17
c Added SCCS keywords.
e
s 00003/00028/00097
d D 5.8 92/09/14 16:30:18 elan 17 16
c Added SCCS keywords.
e
s 00066/00046/00059
d D 5.7 92/09/01 11:08:02 elan 16 15
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00036/00026/00069
d D 5.6 92/07/21 10:28:20 bostic 15 14
c prototype lpr to fix quad's
e
s 00001/00011/00094
d D 5.5 90/06/01 18:44:04 bostic 14 13
c new copyright notice
e
s 00002/00000/00103
d D 5.4 89/08/22 21:02:19 tef 13 12
c common code for checking if rm==localhost
e
s 00010/00005/00093
d D 5.3 88/06/30 17:59:44 bostic 12 11
c install approved copyright notice
e
s 00008/00002/00090
d D 5.2 88/05/05 18:07:50 bostic 11 10
c written by Ralph Campbell; add Berkeley specific header
e
s 00008/00001/00084
d D 5.1 85/06/06 10:10:50 dist 10 9
c Add copyright
e
s 00001/00000/00084
d D 4.9 85/02/27 16:19:36 ralph 9 8
c added 'hl' flag to printcap to print the banner last.
e
s 00001/00000/00083
d D 4.8 85/02/07 15:12:47 miriam 8 7
c Include restricted group.
e
s 00002/00001/00081
d D 4.7 84/07/24 16:52:47 ralph 7 6
c use syslog().
e
s 00001/00001/00081
d D 4.6 83/07/01 22:53:32 wnj 6 5
c <wait.h> -> <sys/wait.h>
e
s 00001/00000/00081
d D 4.5 83/06/29 17:08:59 ralph 5 4
c changed to use unix domain ipc.
e
s 00001/00000/00080
d D 4.4 83/06/22 09:33:49 ralph 4 3
c added -n option to print ditroff files.
e
s 00006/00004/00074
d D 4.3 83/06/17 15:09:37 ralph 3 2
c fixed `fc' and `fs' when 0177777 is needed.
e
s 00004/00000/00074
d D 4.2 83/05/13 11:54:11 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00074/00000/00000
d D 4.1 83/04/29 11:39:42 ralph 1 0
c date and time created 83/04/29 11:39:42 by ralph
e
u
U
t
T
I 1
D 10
/*	%M%	%I%	%E%	*/
E 10
I 10
/*
D 20
 * Copyright (c) 1983 Regents of the University of California.
D 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 14
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 14
I 14
D 16
 * %sccs.include.redist.c%
E 16
I 16
D 17
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 17
I 17
D 18
 * %sccs.include.redist.h%
E 18
I 18
 * %sccs.include.redist.c%
E 18
E 17
E 16
E 14
E 12
E 11
 *
D 16
 *	%W% (Berkeley) %G%
E 16
I 16
D 17
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)lp.h	5.7 (Berkeley) 8/6/92
E 17
I 17
 * 	%W% (Berkeley) %G%
E 17
E 16
 */
I 17

E 17

E 10
/*
 * Global definitions for the line printer system.
 */

D 15
#include <stdio.h>
D 7
#include <sys/types.h>
E 7
I 7
#include <sys/param.h>
E 7
#include <sys/file.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/socket.h>
I 5
#include <sys/un.h>
E 5
#include <netinet/in.h>
#include <netdb.h>
#include <pwd.h>
I 7
#include <syslog.h>
E 7
#include <signal.h>
D 6
#include <wait.h>
E 6
I 6
#include <sys/wait.h>
E 6
#include <sgtty.h>
#include <ctype.h>
#include <errno.h>
#include "lp.local.h"

E 15
D 16
extern int	DU;		/* daeomon user-id */
extern int	MX;		/* maximum number of blocks to copy */
I 3
extern int	MC;		/* maximum number of copies allowed */
E 3
extern char	*LP;		/* line printer device name */
extern char	*RM;		/* remote machine name */
I 8
extern char	*RG;		/* restricted group */
E 8
extern char	*RP;		/* remote printer name */
extern char	*LO;		/* lock file name */
extern char	*ST;		/* status file name */
extern char	*SD;		/* spool directory */
E 16
extern char	*AF;		/* accounting file */
I 16
extern long	 BR;		/* baud rate if lp is a tty */
extern char	*CF;		/* name of cifplot filter (per job) */
extern char	*DF;		/* name of tex filter (per job) */
extern long	 DU;		/* daeomon user-id */
extern long	 FC;		/* flags to clear if lp is a tty */
extern char	*FF;		/* form feed string */
extern long	 FS;		/* flags to set if lp is a tty */
extern char	*GF;		/* name of graph(1G) filter (per job) */
extern long	 HL;		/* print header last */
extern char	*IF;		/* name of input filter (created per job) */
E 16
extern char	*LF;		/* log file for error messages */
I 16
extern char	*LO;		/* lock file name */
extern char	*LP;		/* line printer device name */
extern long	 MC;		/* maximum number of copies allowed */
extern long      MX;		/* maximum number of blocks to copy */
extern char	*NF;		/* name of ditroff(1) filter (per job) */
E 16
extern char	*OF;		/* name of output filter (created once) */
D 16
extern char	*IF;		/* name of input filter (created per job) */
E 16
I 16
extern long	 PL;		/* page length */
extern long	 PW;		/* page width */
extern long	 PX;		/* page width in pixels */
extern long	 PY;		/* page length in pixels */
E 16
I 2
extern char	*RF;		/* name of fortran text filter (per job) */
I 16
extern char	*RG;		/* restricted group */
extern char	*RM;		/* remote machine name */
extern char	*RP;		/* remote printer name */
extern long	 RS;		/* restricted to those with local accounts */
extern long	 RW;		/* open LP for reading and writing */
extern long	 SB;		/* short banner instead of normal header */
extern long	 SC;		/* suppress multiple copies */
extern char	*SD;		/* spool directory */
extern long	 SF;		/* suppress FF on each print job */
extern long	 SH;		/* suppress header page */
extern char	*ST;		/* status file name */
E 16
E 2
extern char	*TF;		/* name of troff(1) filter (per job) */
I 4
D 16
extern char	*NF;		/* name of ditroff(1) filter (per job) */
E 4
extern char	*DF;		/* name of tex filter (per job) */
extern char	*GF;		/* name of graph(1G) filter (per job) */
extern char	*VF;		/* name of raster filter (per job) */
extern char	*CF;		/* name of cifplot filter (per job) */
extern char	*FF;		/* form feed string */
E 16
extern char	*TR;		/* trailer string to be output when Q empties */
I 3
D 16
extern short	SC;		/* suppress multiple copies */
E 3
extern short	SF;		/* suppress FF on each print job */
extern short	SH;		/* suppress header page */
extern short	SB;		/* short banner instead of normal header */
I 9
extern short	HL;		/* print header last */
E 9
extern short	RW;		/* open LP for reading and writing */
extern short	PW;		/* page width */
I 2
extern short	PX;		/* page width in pixels */
extern short	PY;		/* page length in pixels */
E 2
extern short	PL;		/* page length */
extern short	BR;		/* baud rate if lp is a tty */
D 3
extern short	FC;		/* flags to clear if lp is a tty */
extern short	FS;		/* flags to set if lp is a tty */
extern short	XC;		/* flags to clear for local mode */
extern short	XS;		/* flags to set for local mode */
E 3
I 3
extern int	FC;		/* flags to clear if lp is a tty */
extern int	FS;		/* flags to set if lp is a tty */
extern int	XC;		/* flags to clear for local mode */
extern int	XS;		/* flags to set for local mode */
E 3
I 2
extern short	RS;		/* restricted to those with local accounts */
E 16
I 16
extern char	*VF;		/* name of raster filter (per job) */
extern long	 XC;		/* flags to clear for local mode */
extern long	 XS;		/* flags to set for local mode */
E 16
E 2

extern char	line[BUFSIZ];
D 16
extern char	pbuf[];		/* buffer for printcap entry */
extern char	*bp;		/* pointer into ebuf for pgetent() */
E 16
I 16
extern char	*bp;		/* pointer into printcap buffer */
E 16
extern char	*name;		/* program name */
extern char	*printer;	/* printer name */
D 15
extern char	host[32];	/* host machine name */
E 15
I 15
				/* host machine name */
extern char	host[MAXHOSTNAMELEN];
E 15
extern char	*from;		/* client's machine name */
I 13
D 21
extern int	sendtorem;	/* are we sending to a remote? */
E 21
I 21
extern int	remote;		/* true if sending files to a remote host */
E 21
E 13
D 15
extern int	errno;
E 15
D 16

E 16
I 16
extern char	*printcapdb[];  /* printcap database array */
E 16
/*
 * Structure used for building a sorted list of control files.
 */
struct queue {
	time_t	q_time;			/* modification time */
	char	q_name[MAXNAMLEN+1];	/* control file name */
};

D 15
char	*pgetstr();
char	*malloc();
char	*getenv();
char	*index();
char	*rindex();
I 13
char	*checkremote();
E 15
I 15
#include <sys/cdefs.h>
I 16

D 19
_BEGIN_DECLS
E 19
I 19
__BEGIN_DECLS
E 19
E 16
struct dirent;

void     blankfill __P((int));
char	*checkremote __P((void));
int      chk __P((char *));
void     displayq __P((int));
void     dump __P((char *, char *, int));
D 16
void     endprent __P((void));
E 16
void	 fatal __P((const char *, ...));
int	 getline __P((FILE *));
D 21
int	 getport __P((char *));
E 21
I 21
int	 getport __P((char *, int));
E 21
D 16
int      getprent __P((char *));
E 16
int	 getq __P((struct queue *(*[])));
void     header __P((void));
void     inform __P((char *));
int      inlist __P((char *, char *));
int      iscf __P((struct dirent *));
int      isowner __P((char *, char *));
void     ldump __P((char *, char *, int));
int      lockchk __P((char *));
void     prank __P((int));
void     process __P((char *));
void     rmjob __P((void));
void     rmremote __P((void));
void     show __P((char *, char *, int));
int      startdaemon __P((char *));
D 16
int      pgetent __P((char *, char *));
int      pgetflag __P((char *));
int      pgetnum __P((char *));
char    *pgetstr __P((char *, char **));
int      pnamatch __P((char *));
int      pnchktc __P((void));
E 16
void     warn __P((void));
I 21
void     delay __P((int));
E 21
I 16
D 19
_END_DECLS
E 19
I 19
__END_DECLS
E 19
E 16
E 15
E 13
E 1
