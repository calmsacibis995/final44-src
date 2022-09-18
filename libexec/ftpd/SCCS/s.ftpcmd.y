h64743
s 00006/00004/01234
d D 8.3 94/04/06 11:05:04 pendry 45 44
c fix REST.
c fix globbing - need NOCHECK flag
e
s 00337/00305/00901
d D 8.2 94/04/04 12:36:03 pendry 44 43
c eliminate local version of glob (cf ftp)
c clean up yacc grammar.  prettiness police.
e
s 00002/00002/01204
d D 8.1 93/06/04 18:48:21 bostic 43 42
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01205
d D 5.28 93/05/17 10:10:03 bostic 42 41
c index, rindex -> strchr, strrchr
e
s 00025/00007/01181
d D 5.27 92/06/27 16:57:25 andrew 41 40
c (bostic) changes for prototyping, fix error in MDTM error reply
e
s 00001/00004/01187
d D 5.26 92/06/18 16:12:44 andrew 40 39
c remove unneeded declarations, fix restart msg
e
s 00025/00013/01166
d D 5.25 92/03/18 15:11:32 bostic 39 38
c Don't log user passwords when debug is turned on with -d.
c Set "home" to "/" when logging in as a guest.
c Don't syslog() trailing CR-LF when using -d.
c Don't timestamp connect message, syslog() already does that.
c Don't timestamp timeout message, syslog() already does that.
c Minor whitespace cleanups.
c from Craig Leres (leres@ee.lbl.gov)
e
s 00011/00016/01168
d D 5.24 91/02/25 16:46:16 bostic 38 37
c ANSI fixes, struct direct -> struct dirent, rename glob() -> ftpglob()
e
s 00001/00011/01183
d D 5.23 90/06/01 15:52:15 bostic 37 36
c new copyright notice
e
s 00001/00001/01193
d D 5.22 90/02/20 21:32:55 mckusick 36 35
c allocate a null string so that free will not bomb out (4.3BSD/etc/165)
e
s 00002/00001/01192
d D 5.21 89/05/26 13:12:28 rick 35 33
c change an int to a long for portability
e
s 00001/00014/01179
d D 5.20.1.1 89/03/02 09:38:31 karels 34 33
c remove restart for network release
e
s 00332/00042/00861
d D 5.20 89/02/28 12:09:54 karels 33 32
c lots of changes, mostly from Rick Adams: implement restart, stat,
c site (from Dave Borman), size, mdtm; pointer fixes for cray; more cleanups;
c proctitle stuff
e
s 00004/00000/00899
d D 5.19 89/01/26 21:21:01 rick 32 31
c add ifdef unix in case this gets "ported" to a non-unix system
e
s 00028/00023/00871
d D 5.18 89/01/25 14:43:40 rick 31 30
c add support for REST (restart at arbitrary byte position) SYST (system
c type); fix chroot bug; add setproctitle (#ifdef'd); clean up 400/500
c return codes; make NLST/LIST RFC conformant
e
s 00027/00008/00867
d D 5.17 89/01/15 15:15:46 bostic 30 29
c add SYST (sys type), REST (resetart); null deref; from Rick Adams
e
s 00004/00002/00871
d D 5.16 88/12/08 15:33:24 bostic 29 28
c typo...
e
s 00002/00002/00871
d D 5.15 88/12/08 08:36:30 bostic 28 27
c typo in CWD
e
s 00053/00067/00820
d D 5.14 88/12/07 11:35:40 karels 27 26
c fix user/pass to reset all on failure (*don't* leave failed anonymous
c login as root!), limit login attempts, sleep after failures to slow down
c guessing, correct telnet option processing, various cleanups
e
s 00015/00019/00872
d D 5.13 88/11/30 20:28:57 bostic 26 25
c Rick Adams for Bill Scherlis, the night that MilNet died
e
s 00003/00003/00888
d D 5.12 88/10/30 14:07:38 bostic 25 24
c security problem with user; bug report 4.3BSD/ucb/251
e
s 00012/00005/00879
d D 5.11 88/06/18 13:46:46 bostic 24 23
c install approved copyright notice
e
s 00010/00004/00874
d D 5.10 88/03/14 17:27:47 bostic 23 22
c add Berkeley specific header
e
s 00002/00004/00876
d D 5.9 87/05/15 17:39:20 mckusick 22 21
c ftpd remotehelp output columnated improperly (from abe@j.cc.purdue.edu)
e
s 00029/00032/00851
d D 5.8 87/04/23 13:57:13 csvsj 21 20
c redo yacc grammer for RNFR and RNTO
e
s 00002/00000/00881
d D 5.7 86/05/28 15:25:06 mckusick 20 19
c return error code 530 when user is denied access
e
s 00021/00007/00860
d D 5.6 86/05/06 21:24:23 minshall 19 18
c Robustly filter telnet commands on the control connection 
c (from Steve Jacobson).
e
s 00012/00007/00855
d D 5.5 86/04/16 17:38:16 mckusick 18 17
c standardize the reply codes (from mcvax!dpk@seismo.CSS.GOV)
e
s 00062/00063/00800
d D 5.4 86/03/07 12:01:49 minshall 17 16
c Clean up for lint; add syslog.
e
s 00069/00012/00794
d D 5.3 86/02/03 14:32:36 minshall 16 15
c Steve Jacobson's changes (from <csvsj@ucbopal>).
e
s 00006/00007/00800
d D 5.2 85/06/06 11:10:46 dist 15 14
c Add copyright
e
s 00007/00000/00800
d D 5.1 85/06/06 11:08:49 dist 14 13
c Add copyright
e
s 00001/00001/00799
d D 4.13 85/03/12 11:35:20 ralph 13 12
c return null in getline() so dologout() is called rather than exit.
e
s 00002/00002/00798
d D 4.12 84/04/11 14:55:10 karels 12 11
c convert for inetd
e
s 00003/00003/00797
d D 4.11 83/06/22 14:33:03 sam 11 10
c do wtmp logging and cleanup some stuff
e
s 00003/00002/00797
d D 4.10 83/06/12 02:44:52 sam 10 9
c new signals == no libjobs
e
s 00029/00004/00770
d D 4.9 83/03/23 10:26:38 sam 9 8
c merge of changes from jsq@utexas-11
e
s 00002/00002/00772
d D 4.8 83/02/21 19:05:39 sam 8 7
c -C violates standard
e
s 00001/00001/00773
d D 4.7 83/02/02 16:25:03 sam 7 6
c 2 holes: disallow |'s in ls and dir; 2nd, provide forbidden user list
e
s 00007/00005/00767
d D 4.6 83/01/16 13:13:29 sam 6 5
c check user existence before requesting password
e
s 00002/00000/00770
d D 4.5 83/01/16 12:29:10 sam 5 4
c insure default address used even if some transfers supply PORT
e
s 00005/00007/00765
d D 4.4 83/01/16 12:10:07 sam 4 3
c restrict anonymous logins to machines with an ftp account
e
s 00004/00004/00768
d D 4.3 83/01/16 11:54:26 sam 3 2
c only execute /bin/ls so noone can place a dummy ls in the 
c path of the server and become root through its execution
e
s 00043/00032/00729
d D 4.2 83/01/15 16:58:39 sam 2 1
c watch out for glob failing; add -C so NLST comes 
c out columnized; fix help command not to print extra CR-NL
e
s 00761/00000/00000
d D 4.1 83/01/13 23:57:03 sam 1 0
c date and time created 83/01/13 23:57:03 by sam
e
u
U
f b 
t
T
I 14
D 15
#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#
E 15
I 15
/*
D 16
 * Copyright (c) 1980 Regents of the University of California.
E 16
I 16
D 27
 * Copyright (c) 1985 Regents of the University of California.
E 27
I 27
D 43
 * Copyright (c) 1985, 1988 Regents of the University of California.
E 27
E 16
D 23
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 23
I 23
 * All rights reserved.
E 43
I 43
D 44
 * Copyright (c) 1985, 1988, 1993
E 44
I 44
 * Copyright (c) 1985, 1988, 1993, 1994
E 44
 *	The Regents of the University of California.  All rights reserved.
E 43
 *
D 37
 * Redistribution and use in source and binary forms are permitted
D 24
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 24
I 24
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 33
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 33
I 33
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 37
I 37
 * %sccs.include.redist.c%
E 37
E 33
 *
 *	%W% (Berkeley) %G%
E 24
E 23
 */

E 15
E 14
I 1
/*
 * Grammar for FTP commands.
D 33
 * See RFC 765.
E 33
I 33
 * See RFC 959.
E 33
 */

%{

#ifndef lint
D 12
static char sccsid[] = "%W% %E%";
E 12
I 12
D 23
static	char sccsid[] = "%W% (Berkeley) %G%";
E 12
#endif
E 23
I 23
D 31
static char sccsid[] = "%W% (Berkeley) %G%";
E 31
I 31
D 33
static char sccsid[] = "%W%	(Berkeley) %G%";
E 33
I 33
static char sccsid[] = "%W% (Berkeley) %G%";
E 33
E 31
#endif /* not lint */
E 23

D 30
#include <sys/types.h>
E 30
I 30
#include <sys/param.h>
E 30
#include <sys/socket.h>
D 38

E 38
I 38
#include <sys/stat.h>
I 41

E 41
E 38
#include <netinet/in.h>
D 38

E 38
I 10
#include <arpa/ftp.h>
I 41

E 41
D 38

E 10
#include <stdio.h>
E 38
I 9
D 44
#include <signal.h>
E 9
D 38
#include <ctype.h>
#include <pwd.h>
E 38
#include <setjmp.h>
I 17
#include <syslog.h>
I 33
D 38
#include <sys/stat.h>
E 38
#include <time.h>
I 38
#include <pwd.h>
E 44
I 44
#include <ctype.h>
E 44
I 41
#include <errno.h>
E 41
D 44
#include <unistd.h>
E 44
I 44
#include <glob.h>
#include <pwd.h>
#include <setjmp.h>
#include <signal.h>
E 44
#include <stdio.h>
D 44
#include <ctype.h>
E 44
#include <stdlib.h>
#include <string.h>
I 44
#include <syslog.h>
#include <time.h>
#include <unistd.h>

E 44
I 41
#include "extern.h"
E 41
E 38
E 33
E 17
D 10
#include "ftp.h"
E 10

extern	struct sockaddr_in data_dest;
extern	int logged_in;
extern	struct passwd *pw;
extern	int guest;
extern	int logging;
extern	int type;
extern	int form;
extern	int debug;
I 9
extern	int timeout;
I 33
extern	int maxtimeout;
E 33
I 16
extern  int pdata;
E 16
E 9
D 31
extern	char hostname[];
E 31
I 31
extern	char hostname[], remotehost[];
I 33
extern	char proctitle[];
E 33
E 31
D 44
extern	char *globerr;
E 44
I 5
extern	int usedefault;
I 16
D 27
extern	int unique;
E 27
extern  int transflag;
extern  char tmpline[];
E 16
E 5
D 38
char	**glob();
E 38
I 38
D 41
char	**ftpglob();
E 41
E 38

I 30
D 34
off_t	restart_point;

E 34
E 30
static	int cmd_type;
static	int cmd_form;
static	int cmd_bytesz;
I 16
D 27
char cbuf[512];
I 21
char *fromname;
E 27
I 27
char	cbuf[512];
char	*fromname;
E 27
E 21
E 16

D 4
static	struct passwd nobody = { "?", "?" };

E 4
D 38
char	*index();
E 38
%}

I 44
%union {
	int	i;
	char   *s;
}

E 44
%token
	A	B	C	E	F	I
	L	N	P	R	S	T

D 44
	SP	CRLF	COMMA	STRING	NUMBER
E 44
I 44
	SP	CRLF	COMMA
E 44

	USER	PASS	ACCT	REIN	QUIT	PORT
	PASV	TYPE	STRU	MODE	RETR	STOR
	APPE	MLFL	MAIL	MSND	MSOM	MSAM
	MRSQ	MRCP	ALLO	REST	RNFR	RNTO
	ABOR	DELE	CWD	LIST	NLST	SITE
D 31
	STAT	HELP	NOOP	XMKD	XRMD	XPWD
D 16
	XCUP
E 16
I 16
D 30
	XCUP	STOU
E 30
I 30
	XCUP	STOU	SYST
E 31
I 31
	STAT	HELP	NOOP	MKD	RMD	PWD
D 33
	CDUP	STOU	SYST
E 33
I 33
	CDUP	STOU	SMNT	SYST	SIZE	MDTM
E 33
E 31
E 30
E 16

I 33
	UMASK	IDLE	CHMOD

E 33
	LEXERR

I 44
%token	<s> STRING
%token	<i> NUMBER

%type	<i> check_login octal_number byte_size
%type	<i> struct_code mode_code type_code form_code
%type	<s> pathstring pathname password username

E 44
%start	cmd_list

%%

D 44
cmd_list:	/* empty */
	|	cmd_list cmd
I 21
		= {
E 44
I 44
cmd_list
	: /* empty */
	| cmd_list cmd
		{
E 44
			fromname = (char *) 0;
I 30
D 34
			restart_point = (off_t) 0;
E 34
E 30
		}
D 44
	|	cmd_list rcmd
E 44
I 44
	| cmd_list rcmd
E 44
E 21
	;

D 44
cmd:		USER SP username CRLF
		= {
D 25
			extern struct passwd *getpwnam();
E 25
I 25
D 27
			extern struct passwd *sgetpwnam();
E 25

I 16
			logged_in = 0;
E 16
D 4
			if (strcmp($3, "ftp") == 0 ||
			    strcmp($3, "anonymous") == 0) {
E 4
I 4
D 6
			if ((strcmp($3, "ftp") == 0 ||
			    strcmp($3, "anonymous") == 0) &&
			    (pw = getpwnam("ftp")) != NULL) {
E 4
				guest = 1;
D 4
				pw = getpwnam("ftp");
E 4
				reply(331,
E 6
I 6
D 17
			if (strcmp($3, "ftp") == 0 ||
			  strcmp($3, "anonymous") == 0) {
E 17
I 17
			if (strcmp((char *) $3, "ftp") == 0 ||
			  strcmp((char *) $3, "anonymous") == 0) {
E 17
D 25
				if ((pw = getpwnam("ftp")) != NULL) {
E 25
I 25
				if ((pw = sgetpwnam("ftp")) != NULL) {
E 25
					guest = 1;
					reply(331,
E 6
				  "Guest login ok, send ident as password.");
I 6
				}
I 16
				else {
					reply(530, "User %s unknown.", $3);
				}
E 16
E 6
D 7
			} else {
E 7
I 7
D 17
			} else if (checkuser($3)) {
E 17
I 17
			} else if (checkuser((char *) $3)) {
E 17
E 7
				guest = 0;
D 17
				pw = getpwnam($3);
E 17
I 17
D 25
				pw = getpwnam((char *) $3);
E 25
I 25
				pw = sgetpwnam((char *) $3);
E 25
E 17
D 16
				reply(331, "Password required for %s.", $3);
E 16
I 16
				if (pw == NULL) {
					reply(530, "User %s unknown.", $3);
				}
				else {
				    reply(331, "Password required for %s.", $3);
				}
I 20
			} else {
				reply(530, "User %s access denied.", $3);
E 20
E 16
			}
E 27
I 27
			user((char *) $3);
E 27
D 4
			free($3);
E 4
D 16
			if (pw == NULL)
D 4
				pw = &nobody;
E 4
I 4
				reply(530, "User %s unknown.", $3);
E 16
D 17
			free($3);
E 17
I 17
			free((char *) $3);
E 44
I 44
cmd
	: USER SP username CRLF
		{
			user($3);
			free($3);
E 44
E 17
E 4
		}
D 44
	|	PASS SP password CRLF
		= {
D 17
			pass($3);
			free($3);
E 17
I 17
			pass((char *) $3);
			free((char *) $3);
E 44
I 44
	| PASS SP password CRLF
		{
			pass($3);
			free($3);
E 44
E 17
		}
D 44
	|	PORT SP host_port CRLF
		= {
E 44
I 44
	| PORT SP host_port CRLF
		{
E 44
I 5
			usedefault = 0;
I 16
D 27
			if (pdata > 0) {
E 27
I 27
			if (pdata >= 0) {
E 27
				(void) close(pdata);
I 27
				pdata = -1;
E 27
			}
D 27
			pdata = -1;
E 27
E 16
E 5
D 17
			ack($1);
E 17
I 17
D 18
			ack((char *) $1);
E 18
I 18
			reply(200, "PORT command successful.");
E 18
E 17
		}
I 16
D 44
	|	PASV CRLF
		= {
E 44
I 44
	| PASV CRLF
		{
E 44
			passive();
		}
E 16
D 44
	|	TYPE SP type_code CRLF
		= {
E 44
I 44
	| TYPE SP type_code CRLF
		{
E 44
			switch (cmd_type) {

			case TYPE_A:
				if (cmd_form == FORM_N) {
					reply(200, "Type set to A.");
					type = cmd_type;
					form = cmd_form;
				} else
					reply(504, "Form must be N.");
				break;

			case TYPE_E:
				reply(504, "Type E not implemented.");
				break;

			case TYPE_I:
				reply(200, "Type set to I.");
				type = cmd_type;
				break;

			case TYPE_L:
D 30
				if (cmd_bytesz == 8) {
E 30
I 30
D 33
				if (cmd_bytesz == NBBY) {
E 33
I 33
#if NBBY == 8
				if (cmd_bytesz == 8) {
E 33
E 30
					reply(200,
D 30
					    "Type set to L (byte size 8).");
E 30
I 30
D 33
					    "Type set to L (byte size %d).",
					    NBBY);
E 33
I 33
					    "Type set to L (byte size 8).");
E 33
E 30
					type = cmd_type;
				} else
D 30
					reply(504, "Byte size must be 8.");
E 30
I 30
D 33
					reply(504, "Byte size must be %d.",
					    NBBY);
E 33
I 33
					reply(504, "Byte size must be 8.");
#else /* NBBY == 8 */
				UNIMPLEMENTED for NBBY != 8
#endif /* NBBY == 8 */
E 33
E 30
			}
		}
D 44
	|	STRU SP struct_code CRLF
		= {
E 44
I 44
	| STRU SP struct_code CRLF
		{
E 44
			switch ($3) {

			case STRU_F:
				reply(200, "STRU F ok.");
				break;

			default:
D 18
				reply(502, "Unimplemented STRU type.");
E 18
I 18
				reply(504, "Unimplemented STRU type.");
E 18
			}
		}
D 44
	|	MODE SP mode_code CRLF
		= {
E 44
I 44
	| MODE SP mode_code CRLF
		{
E 44
			switch ($3) {

			case MODE_S:
				reply(200, "MODE S ok.");
				break;

			default:
				reply(502, "Unimplemented MODE type.");
			}
		}
D 44
	|	ALLO SP NUMBER CRLF
		= {
E 44
I 44
	| ALLO SP NUMBER CRLF
		{
E 44
D 17
			ack($1);
E 17
I 17
D 18
			ack((char *) $1);
E 18
I 18
			reply(202, "ALLO command ignored.");
E 18
E 17
		}
I 33
D 44
	|	ALLO SP NUMBER SP R SP NUMBER CRLF
		= {
E 44
I 44
	| ALLO SP NUMBER SP R SP NUMBER CRLF
		{
E 44
			reply(202, "ALLO command ignored.");
		}
E 33
D 44
	|	RETR check_login SP pathname CRLF
		= {
E 44
I 44
	| RETR check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
E 2
I 2
			if ($2 && $4 != NULL)
E 2
D 17
				retrieve(0, $4);
E 17
I 17
D 31
				retrieve((char *) 0, (char *) $4);
E 31
I 31
D 33
				retrieve((char *) 0, (char *)$4);
E 33
I 33
D 44
				retrieve((char *) 0, (char *) $4);
E 44
I 44
				retrieve((char *) 0, $4);
E 44
E 33
E 31
E 17
D 2
			free($4);
E 2
I 2
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 44
	|	STOR check_login SP pathname CRLF
		= {
E 44
I 44
	| STOR check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
E 2
I 2
			if ($2 && $4 != NULL)
E 2
D 17
				store($4, "w");
E 17
I 17
D 27
				store((char *) $4, "w");
E 27
I 27
D 44
				store((char *) $4, "w", 0);
E 44
I 44
				store($4, "w", 0);
E 44
E 27
E 17
D 2
			free($4);
E 2
I 2
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 44
	|	APPE check_login SP pathname CRLF
		= {
E 44
I 44
	| APPE check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
E 2
I 2
			if ($2 && $4 != NULL)
E 2
D 17
				store($4, "a");
E 17
I 17
D 27
				store((char *) $4, "a");
E 27
I 27
D 44
				store((char *) $4, "a", 0);
E 44
I 44
				store($4, "a", 0);
E 44
E 27
E 17
D 2
			free($4);
E 2
I 2
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 44
	|	NLST check_login CRLF
		= {
E 44
I 44
	| NLST check_login CRLF
		{
E 44
			if ($2)
D 2
				retrieve("ls", "");
E 2
I 2
D 3
				retrieve("ls -C", "");
E 3
I 3
D 8
				retrieve("/bin/ls -C", "");
E 8
I 8
D 31
				retrieve("/bin/ls", "");
E 31
I 31
				send_file_list(".");
E 31
E 8
E 3
E 2
		}
D 31
	|	NLST check_login SP pathname CRLF
E 31
I 31
D 44
	|	NLST check_login SP STRING CRLF
E 31
		= {
E 44
I 44
	| NLST check_login SP STRING CRLF
		{
E 44
D 2
			if ($2)
				retrieve("ls %s", $4);
			free($4);
E 2
I 2
D 31
			if ($2 && $4 != NULL)
D 3
				retrieve("ls -C %s", $4);
E 3
I 3
D 8
				retrieve("/bin/ls -C %s", $4);
E 8
I 8
D 17
				retrieve("/bin/ls %s", $4);
E 17
I 17
				retrieve("/bin/ls %s", (char *) $4);
E 31
I 31
D 39
			if ($2 && $4 != NULL) 
E 39
I 39
			if ($2 && $4 != NULL)
E 39
D 44
				send_file_list((char *) $4);
E 44
I 44
				send_file_list($4);
E 44
E 31
E 17
E 8
E 3
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 44
	|	LIST check_login CRLF
		= {
E 44
I 44
	| LIST check_login CRLF
		{
E 44
			if ($2)
D 2
				retrieve("ls -l", "");
E 2
I 2
D 3
				retrieve("ls -lg", "");
E 3
I 3
D 31
				retrieve("/bin/ls -lg", "");
E 31
I 31
				retrieve("/bin/ls -lgA", "");
E 31
E 3
E 2
		}
D 44
	|	LIST check_login SP pathname CRLF
		= {
E 44
I 44
	| LIST check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
				retrieve("ls -l %s", $4);
			free($4);
E 2
I 2
			if ($2 && $4 != NULL)
D 3
				retrieve("ls -lg %s", $4);
E 3
I 3
D 17
				retrieve("/bin/ls -lg %s", $4);
E 17
I 17
D 31
				retrieve("/bin/ls -lg %s", (char *) $4);
E 31
I 31
D 44
				retrieve("/bin/ls -lgA %s", (char *) $4);
E 44
I 44
				retrieve("/bin/ls -lgA %s", $4);
E 44
E 31
E 17
E 3
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
I 33
D 44
	|	STAT check_login SP pathname CRLF
		= {
E 44
I 44
	| STAT check_login SP pathname CRLF
		{
E 44
			if ($2 && $4 != NULL)
D 44
				statfilecmd((char *) $4);
E 44
I 44
				statfilecmd($4);
E 44
			if ($4 != NULL)
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
		}
D 44
	|	STAT CRLF
		= {
E 44
I 44
	| STAT CRLF
		{
E 44
			statcmd();
		}
E 33
D 44
	|	DELE check_login SP pathname CRLF
		= {
E 44
I 44
	| DELE check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
E 2
I 2
			if ($2 && $4 != NULL)
E 2
D 17
				delete($4);
E 17
I 17
D 44
				delete((char *) $4);
E 44
I 44
				delete($4);
E 44
E 17
D 2
			free($4);
E 2
I 2
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
I 21
D 44
	|	RNTO SP pathname CRLF
		= {
E 44
I 44
	| RNTO SP pathname CRLF
		{
E 44
			if (fromname) {
D 44
				renamecmd(fromname, (char *) $3);
E 44
I 44
				renamecmd(fromname, $3);
E 44
				free(fromname);
				fromname = (char *) 0;
			} else {
				reply(503, "Bad sequence of commands.");
			}
D 44
			free((char *) $3);
E 44
I 44
			free($3);
E 44
		}
E 21
I 16
D 44
	|	ABOR CRLF
		= {
E 44
I 44
	| ABOR CRLF
		{
E 44
D 17
			ack($1);
E 17
I 17
D 18
			ack((char *) $1);
E 18
I 18
			reply(225, "ABOR command successful.");
E 18
E 17
		}
E 16
D 44
	|	CWD check_login CRLF
		= {
E 44
I 44
	| CWD check_login CRLF
		{
E 44
			if ($2)
				cwd(pw->pw_dir);
		}
D 44
	|	CWD check_login SP pathname CRLF
		= {
E 44
I 44
	| CWD check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
E 2
I 2
			if ($2 && $4 != NULL)
E 2
D 17
				cwd($4);
E 17
I 17
D 44
				cwd((char *) $4);
E 44
I 44
				cwd($4);
E 44
E 17
D 2
			free($4);
E 2
I 2
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 21
	|	rename_cmd
E 21
D 44
	|	HELP CRLF
		= {
E 44
I 44
	| HELP CRLF
		{
E 44
D 17
			help(0);
E 17
I 17
D 33
			help((char *) 0);
E 33
I 33
			help(cmdtab, (char *) 0);
E 33
E 17
		}
D 44
	|	HELP SP STRING CRLF
		= {
D 17
			help($3);
E 17
I 17
D 33
			help((char *) $3);
E 33
I 33
			register char *cp = (char *)$3;
E 44
I 44
	| HELP SP STRING CRLF
		{
			char *cp = $3;
E 44

			if (strncasecmp(cp, "SITE", 4) == 0) {
D 44
				cp = (char *)$3 + 4;
E 44
I 44
				cp = $3 + 4;
E 44
				if (*cp == ' ')
					cp++;
				if (*cp)
					help(sitetab, cp);
				else
					help(sitetab, (char *) 0);
			} else
D 44
				help(cmdtab, (char *) $3);
E 44
I 44
				help(cmdtab, $3);
E 44
E 33
E 17
		}
D 44
	|	NOOP CRLF
		= {
E 44
I 44
	| NOOP CRLF
		{
E 44
D 17
			ack($1);
E 17
I 17
D 18
			ack((char *) $1);
E 18
I 18
			reply(200, "NOOP command successful.");
E 18
E 17
		}
D 31
	|	XMKD check_login SP pathname CRLF
E 31
I 31
D 44
	|	MKD check_login SP pathname CRLF
E 31
		= {
E 44
I 44
	| MKD check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
				do_mkdir($4);
			free($4);
E 2
I 2
			if ($2 && $4 != NULL)
D 17
				makedir($4);
E 17
I 17
D 44
				makedir((char *) $4);
E 44
I 44
				makedir($4);
E 44
E 17
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 31
	|	XRMD check_login SP pathname CRLF
E 31
I 31
D 44
	|	RMD check_login SP pathname CRLF
E 31
		= {
E 44
I 44
	| RMD check_login SP pathname CRLF
		{
E 44
D 2
			if ($2)
				do_rmdir($4);
			free($4);
E 2
I 2
			if ($2 && $4 != NULL)
D 17
				removedir($4);
E 17
I 17
D 44
				removedir((char *) $4);
E 44
I 44
				removedir($4);
E 44
E 17
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
E 2
		}
D 31
	|	XPWD check_login CRLF
E 31
I 31
D 44
	|	PWD check_login CRLF
E 31
		= {
E 44
I 44
	| PWD check_login CRLF
		{
E 44
			if ($2)
D 2
				do_pwd();
E 2
I 2
				pwd();
E 2
		}
D 31
	|	XCUP check_login CRLF
E 31
I 31
D 44
	|	CDUP check_login CRLF
E 31
		= {
E 44
I 44
	| CDUP check_login CRLF
		{
E 44
			if ($2)
				cwd("..");
		}
I 33
D 44
	|	SITE SP HELP CRLF
		= {
E 44
I 44
	| SITE SP HELP CRLF
		{
E 44
			help(sitetab, (char *) 0);
		}
D 44
	|	SITE SP HELP SP STRING CRLF
		= {
			help(sitetab, (char *) $5);
E 44
I 44
	| SITE SP HELP SP STRING CRLF
		{
			help(sitetab, $5);
E 44
		}
D 44
	|	SITE SP UMASK check_login CRLF
		= {
E 44
I 44
	| SITE SP UMASK check_login CRLF
		{
E 44
			int oldmask;

			if ($4) {
				oldmask = umask(0);
				(void) umask(oldmask);
				reply(200, "Current UMASK is %03o", oldmask);
			}
		}
D 44
	|	SITE SP UMASK check_login SP octal_number CRLF
		= {
E 44
I 44
	| SITE SP UMASK check_login SP octal_number CRLF
		{
E 44
			int oldmask;

			if ($4) {
				if (($6 == -1) || ($6 > 0777)) {
					reply(501, "Bad UMASK value");
				} else {
					oldmask = umask($6);
					reply(200,
					    "UMASK set to %03o (was %03o)",
					    $6, oldmask);
				}
			}
		}
D 44
	|	SITE SP CHMOD check_login SP octal_number SP pathname CRLF
		= {
E 44
I 44
	| SITE SP CHMOD check_login SP octal_number SP pathname CRLF
		{
E 44
			if ($4 && ($8 != NULL)) {
				if ($6 > 0777)
					reply(501,
				"CHMOD: Mode value must be between 0 and 0777");
D 44
				else if (chmod((char *) $8, $6) < 0)
					perror_reply(550, (char *) $8);
E 44
I 44
				else if (chmod($8, $6) < 0)
					perror_reply(550, $8);
E 44
				else
					reply(200, "CHMOD command successful.");
			}
			if ($8 != NULL)
D 44
				free((char *) $8);
E 44
I 44
				free($8);
E 44
		}
D 44
	|	SITE SP IDLE CRLF
		= {
E 44
I 44
	| SITE SP IDLE CRLF
		{
E 44
			reply(200,
			    "Current IDLE time limit is %d seconds; max %d",
				timeout, maxtimeout);
		}
D 44
	|	SITE SP IDLE SP NUMBER CRLF
		= {
E 44
I 44
	| SITE SP IDLE SP NUMBER CRLF
		{
E 44
			if ($5 < 30 || $5 > maxtimeout) {
				reply(501,
			"Maximum IDLE time must be between 30 and %d seconds",
				    maxtimeout);
			} else {
				timeout = $5;
				(void) alarm((unsigned) timeout);
				reply(200,
				    "Maximum IDLE time set to %d seconds",
				    timeout);
			}
		}
E 33
I 16
D 44
	|	STOU check_login SP pathname CRLF
		= {
E 44
I 44
	| STOU check_login SP pathname CRLF
		{
E 44
D 27
			if ($2 && $4 != NULL) {
				unique++;
D 17
				store($4, "w");
E 17
I 17
				store((char *) $4, "w");
E 17
				unique = 0;
			}
E 27
I 27
			if ($2 && $4 != NULL)
D 44
				store((char *) $4, "w", 1);
E 44
I 44
				store($4, "w", 1);
E 44
E 27
			if ($4 != NULL)
D 17
				free($4);
E 17
I 17
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
E 17
		}
I 30
D 44
	|	SYST CRLF
		= {
E 44
I 44
	| SYST CRLF
		{
E 44
I 32
#ifdef unix
I 33
#ifdef BSD
E 33
E 32
			reply(215, "UNIX Type: L%d Version: BSD-%d",
I 32
D 33
#else
			reply(215, "UNKNOWN Type: L%d Version: BSD-%d",
#endif
E 33
E 32
				NBBY, BSD);
I 33
#else /* BSD */
			reply(215, "UNIX Type: L%d", NBBY);
#endif /* BSD */
#else /* unix */
			reply(215, "UNKNOWN Type: L%d", NBBY);
#endif /* unix */
E 33
		}
I 33

		/*
		 * SIZE is not in RFC959, but Postel has blessed it and
		 * it will be in the updated RFC.
		 *
		 * Return size of file in a format suitable for
		 * using with RESTART (we just count bytes).
		 */
D 44
	|	SIZE check_login SP pathname CRLF
		= {
E 44
I 44
	| SIZE check_login SP pathname CRLF
		{
E 44
			if ($2 && $4 != NULL)
D 44
				sizecmd((char *) $4);
E 44
I 44
				sizecmd($4);
E 44
			if ($4 != NULL)
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
		}

		/*
		 * MDTM is not in RFC959, but Postel has blessed it and
		 * it will be in the updated RFC.
		 *
		 * Return modification time of file as an ISO 3307
		 * style time. E.g. YYYYMMDDHHMMSS or YYYYMMDDHHMMSS.xxx
		 * where xxx is the fractional second (of any precision,
		 * not necessarily 3 digits)
		 */
D 44
	|	MDTM check_login SP pathname CRLF
		= {
E 44
I 44
	| MDTM check_login SP pathname CRLF
		{
E 44
			if ($2 && $4 != NULL) {
				struct stat stbuf;
D 44
				if (stat((char *) $4, &stbuf) < 0)
E 44
I 44
				if (stat($4, &stbuf) < 0)
E 44
D 41
					perror_reply(550, "%s", (char *) $4);
E 41
I 41
					reply(550, "%s: %s",
D 44
					    (char *)$4, strerror(errno));
E 41
				else if ((stbuf.st_mode&S_IFMT) != S_IFREG) {
					reply(550, "%s: not a plain file.",
						(char *) $4);
E 44
I 44
					    $4, strerror(errno));
				else if (!S_ISREG(stbuf.st_mode)) {
					reply(550, "%s: not a plain file.", $4);
E 44
				} else {
D 44
					register struct tm *t;
E 44
I 44
					struct tm *t;
E 44
D 40
					struct tm *gmtime();
E 40
					t = gmtime(&stbuf.st_mtime);
					reply(213,
					    "19%02d%02d%02d%02d%02d%02d",
					    t->tm_year, t->tm_mon+1, t->tm_mday,
					    t->tm_hour, t->tm_min, t->tm_sec);
				}
			}
			if ($4 != NULL)
D 44
				free((char *) $4);
E 44
I 44
				free($4);
E 44
		}
E 33
E 30
E 16
D 44
	|	QUIT CRLF
		= {
E 44
I 44
	| QUIT CRLF
		{
E 44
			reply(221, "Goodbye.");
D 11
			exit(0);
E 11
I 11
			dologout(0);
E 11
		}
D 44
	|	error CRLF
		= {
E 44
I 44
	| error CRLF
		{
E 44
			yyerrok;
		}
	;
D 30

E 30
I 21
D 44
rcmd:		RNFR check_login SP pathname CRLF
		= {
E 44
I 44
rcmd
	: RNFR check_login SP pathname CRLF
		{
E 44
			char *renamefrom();

I 30
D 34
			restart_point = (off_t) 0;
E 34
E 30
			if ($2 && $4) {
D 44
				fromname = renamefrom((char *) $4);
E 44
I 44
				fromname = renamefrom($4);
E 44
				if (fromname == (char *) 0 && $4) {
D 44
					free((char *) $4);
E 44
I 44
					free($4);
E 44
				}
			}
		}
I 30
D 34
D 44
	|	REST SP byte_size CRLF
		= {
E 44
I 44
	| REST SP byte_size CRLF
		{
E 44
D 40
			long atol();

E 40
			fromname = (char *) 0;
D 45
			restart_point = $3;
D 33
			reply(350, "Restarting at %ld. Send STORE or RETRIEVE to initiate transfer.", restart_point);
E 33
I 33
			reply(350, "Restarting at %ld. %s", restart_point,
E 45
I 45
			restart_point = $3;	/* XXX $3 is only "int" */
			reply(350, "Restarting at %qd. %s", restart_point,
E 45
			    "Send STORE or RETRIEVE to initiate transfer.");
E 33
		}
E 34
E 30
	;
D 39
		
E 39
I 39

E 39
E 21
D 44
username:	STRING
E 44
I 44
username
	: STRING
E 44
	;

D 27
password:	STRING
E 27
I 27
D 44
password:	/* empty */
		= {
D 33
			$$ = (int) "";
E 33
I 33
D 36
			*(char **)&($$) = "";
E 36
I 36
			*(char **)&($$) = (char *)calloc(1, sizeof(char));
E 44
I 44
password
	: /* empty */
		{
			$$ = (char *)calloc(1, sizeof(char));
E 44
E 36
E 33
		}
D 44
	|	STRING
E 44
I 44
	| STRING
E 44
E 27
	;

D 44
byte_size:	NUMBER
E 44
I 44
byte_size
	: NUMBER
E 44
	;

D 39
host_port:	NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA 
E 39
I 39
D 44
host_port:	NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA
E 44
I 44
host_port
	: NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA
E 44
E 39
		NUMBER COMMA NUMBER
D 44
		= {
			register char *a, *p;
E 44
I 44
		{
			char *a, *p;
E 44

			a = (char *)&data_dest.sin_addr;
			a[0] = $1; a[1] = $3; a[2] = $5; a[3] = $7;
			p = (char *)&data_dest.sin_port;
			p[0] = $9; p[1] = $11;
I 6
			data_dest.sin_family = AF_INET;
E 6
		}
	;

D 44
form_code:	N
	= {
		$$ = FORM_N;
	}
	|	T
	= {
		$$ = FORM_T;
	}
	|	C
	= {
		$$ = FORM_C;
	}
E 44
I 44
form_code
	: N
		{
			$$ = FORM_N;
		}
	| T
		{
			$$ = FORM_T;
		}
	| C
		{
			$$ = FORM_C;
		}
E 44
	;

D 44
type_code:	A
	= {
		cmd_type = TYPE_A;
		cmd_form = FORM_N;
	}
	|	A SP form_code
	= {
		cmd_type = TYPE_A;
		cmd_form = $3;
	}
	|	E
	= {
		cmd_type = TYPE_E;
		cmd_form = FORM_N;
	}
	|	E SP form_code
	= {
		cmd_type = TYPE_E;
		cmd_form = $3;
	}
	|	I
	= {
		cmd_type = TYPE_I;
	}
	|	L
	= {
		cmd_type = TYPE_L;
D 30
		cmd_bytesz = 8;
E 30
I 30
		cmd_bytesz = NBBY;
E 30
	}
	|	L SP byte_size
	= {
		cmd_type = TYPE_L;
		cmd_bytesz = $3;
	}
	/* this is for a bug in the BBN ftp */
	|	L byte_size
	= {
		cmd_type = TYPE_L;
		cmd_bytesz = $2;
	}
E 44
I 44
type_code
	: A
		{
			cmd_type = TYPE_A;
			cmd_form = FORM_N;
		}
	| A SP form_code
		{
			cmd_type = TYPE_A;
			cmd_form = $3;
		}
	| E
		{
			cmd_type = TYPE_E;
			cmd_form = FORM_N;
		}
	| E SP form_code
		{
			cmd_type = TYPE_E;
			cmd_form = $3;
		}
	| I
		{
			cmd_type = TYPE_I;
		}
	| L
		{
			cmd_type = TYPE_L;
			cmd_bytesz = NBBY;
		}
	| L SP byte_size
		{
			cmd_type = TYPE_L;
			cmd_bytesz = $3;
		}
		/* this is for a bug in the BBN ftp */
	| L byte_size
		{
			cmd_type = TYPE_L;
			cmd_bytesz = $2;
		}
E 44
	;

D 44
struct_code:	F
	= {
		$$ = STRU_F;
	}
	|	R
	= {
		$$ = STRU_R;
	}
	|	P
	= {
		$$ = STRU_P;
	}
E 44
I 44
struct_code
	: F
		{
			$$ = STRU_F;
		}
	| R
		{
			$$ = STRU_R;
		}
	| P
		{
			$$ = STRU_P;
		}
E 44
	;

D 44
mode_code:	S
	= {
		$$ = MODE_S;
	}
	|	B
	= {
		$$ = MODE_B;
	}
	|	C
	= {
		$$ = MODE_C;
	}
E 44
I 44
mode_code
	: S
		{
			$$ = MODE_S;
		}
	| B
		{
			$$ = MODE_B;
		}
	| C
		{
			$$ = MODE_C;
		}
E 44
	;

D 44
pathname:	pathstring
	= {
I 18
		/*
		 * Problem: this production is used for all pathname
		 * processing, but only gives a 550 error reply.
		 * This is a valid reply in some cases but not in others.
		 */
E 18
D 17
		if ($1 && strncmp($1, "~", 1) == 0) {
			$$ = (int)*glob($1);
E 17
I 17
D 27
		if ($1 && strncmp((char *) $1, "~", 1) == 0) {
E 27
I 27
		if (logged_in && $1 && strncmp((char *) $1, "~", 1) == 0) {
E 27
D 33
			$$ = (int)*glob((char *) $1);
E 33
I 33
D 38
			*(char **)&($$) = *glob((char *) $1);
E 38
I 38
			*(char **)&($$) = *ftpglob((char *) $1);
E 38
E 33
E 17
D 2
			if (globerr != NULL)
E 2
I 2
			if (globerr != NULL) {
E 2
				reply(550, globerr);
I 2
				$$ = NULL;
			}
E 2
D 17
			free($1);
E 17
I 17
			free((char *) $1);
E 17
		} else
			$$ = $1;
	}
E 44
I 44
pathname
	: pathstring
		{
			/*
			 * Problem: this production is used for all pathname
			 * processing, but only gives a 550 error reply.
			 * This is a valid reply in some cases but not in others.
			 */
			if (logged_in && $1 && *$1 == '~') {
				glob_t gl;
D 45
				int flags = GLOB_BRACE|GLOB_QUOTE|GLOB_TILDE;
E 45
I 45
				int flags =
				 GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
E 45

				memset(&gl, 0, sizeof(gl));
D 45
				if (glob($1, flags, NULL, &gl)) {
E 45
I 45
				if (glob($1, flags, NULL, &gl) ||
				    gl.gl_pathc == 0) {
E 45
					reply(550, "not found");
					$$ = NULL;
				} else {
					$$ = strdup(gl.gl_pathv[0]);
				}
				globfree(&gl);
				free($1);
			} else
				$$ = $1;
		}
E 44
	;

D 44
pathstring:	STRING
E 44
I 44
pathstring
	: STRING
E 44
D 21
	;

rename_cmd:	rename_from rename_to
	= {
		if ($1 && $2)
D 17
			renamecmd($1, $2);
E 17
I 17
			renamecmd((char *) $1, (char *) $2);
E 17
		else
			reply(503, "Bad sequence of commands.");
		if ($1)
D 17
			free($1);
E 17
I 17
			free((char *) $1);
E 17
		if ($2)
D 17
			free($2);
E 17
I 17
			free((char *) $2);
E 17
	}
	;

rename_from:	RNFR check_login SP pathname CRLF
	= {
		char *from = 0, *renamefrom();

D 2
		if ($2)
E 2
I 2
		if ($2 && $4)
E 2
D 17
			from = renamefrom($4);
E 17
I 17
			from = renamefrom((char *) $4);
E 17
D 2
		if (from == 0)
E 2
I 2
		if (from == 0 && $4)
E 2
D 17
			free($4);
E 17
I 17
			free((char *) $4);
E 17
		$$ = (int)from;
	}
	;

rename_to:	RNTO SP pathname CRLF
	= {
		$$ = $3;
	}
E 21
	;

I 33
D 44
octal_number:	NUMBER
	= {
		register int ret, dec, multby, digit;
E 44
I 44
octal_number
	: NUMBER
		{
			int ret, dec, multby, digit;
E 44

D 44
		/*
		 * Convert a number that was read as decimal number
		 * to what it would be if it had been read as octal.
		 */
		dec = $1;
		multby = 1;
		ret = 0;
		while (dec) {
			digit = dec%10;
			if (digit > 7) {
				ret = -1;
				break;
E 44
I 44
			/*
			 * Convert a number that was read as decimal number
			 * to what it would be if it had been read as octal.
			 */
			dec = $1;
			multby = 1;
			ret = 0;
			while (dec) {
				digit = dec%10;
				if (digit > 7) {
					ret = -1;
					break;
				}
				ret += digit * multby;
				multby *= 8;
				dec /= 10;
E 44
			}
D 44
			ret += digit * multby;
			multby *= 8;
			dec /= 10;
E 44
I 44
			$$ = ret;
E 44
		}
D 44
		$$ = ret;
	}
E 44
	;

E 33
D 44
check_login:	/* empty */
	= {
		if (logged_in)
			$$ = 1;
		else {
			reply(530, "Please login with USER and PASS.");
			$$ = 0;
E 44
I 44

check_login
	: /* empty */
		{
			if (logged_in)
				$$ = 1;
			else {
				reply(530, "Please login with USER and PASS.");
				$$ = 0;
			}
E 44
		}
D 44
	}
E 44
	;

%%

extern jmp_buf errcatch;

#define	CMD	0	/* beginning of command */
#define	ARGS	1	/* expect miscellaneous arguments */
#define	STR1	2	/* expect SP followed by STRING */
#define	STR2	3	/* expect STRING */
D 27
#define	OSTR	4	/* optional STRING */
E 27
I 27
#define	OSTR	4	/* optional SP then STRING */
#define	ZSTR1	5	/* SP then optional STRING */
#define	ZSTR2	6	/* optional STRING after SP */
I 33
#define	SITECMD	7	/* SITE command */
#define	NSTR	8	/* Number followed by a string */
E 33
E 27

struct tab {
	char	*name;
	short	token;
	short	state;
	short	implemented;	/* 1 if command is implemented */
	char	*help;
};

struct tab cmdtab[] = {		/* In order defined in RFC 765 */
	{ "USER", USER, STR1, 1,	"<sp> username" },
D 27
	{ "PASS", PASS, STR1, 1,	"<sp> password" },
E 27
I 27
	{ "PASS", PASS, ZSTR1, 1,	"<sp> password" },
E 27
	{ "ACCT", ACCT, STR1, 0,	"(specify account)" },
I 33
	{ "SMNT", SMNT, ARGS, 0,	"(structure mount)" },
E 33
	{ "REIN", REIN, ARGS, 0,	"(reinitialize server state)" },
	{ "QUIT", QUIT, ARGS, 1,	"(terminate service)", },
	{ "PORT", PORT, ARGS, 1,	"<sp> b0, b1, b2, b3, b4" },
D 16
	{ "PASV", PASV, ARGS, 0,	"(set server in passive mode)" },
E 16
I 16
	{ "PASV", PASV, ARGS, 1,	"(set server in passive mode)" },
E 16
	{ "TYPE", TYPE, ARGS, 1,	"<sp> [ A | E | I | L ]" },
	{ "STRU", STRU, ARGS, 1,	"(specify file structure)" },
	{ "MODE", MODE, ARGS, 1,	"(specify transfer mode)" },
	{ "RETR", RETR, STR1, 1,	"<sp> file-name" },
	{ "STOR", STOR, STR1, 1,	"<sp> file-name" },
	{ "APPE", APPE, STR1, 1,	"<sp> file-name" },
	{ "MLFL", MLFL, OSTR, 0,	"(mail file)" },
	{ "MAIL", MAIL, OSTR, 0,	"(mail to user)" },
	{ "MSND", MSND, OSTR, 0,	"(mail send to terminal)" },
	{ "MSOM", MSOM, OSTR, 0,	"(mail send to terminal or mailbox)" },
	{ "MSAM", MSAM, OSTR, 0,	"(mail send to terminal and mailbox)" },
	{ "MRSQ", MRSQ, OSTR, 0,	"(mail recipient scheme question)" },
	{ "MRCP", MRCP, STR1, 0,	"(mail recipient)" },
	{ "ALLO", ALLO, ARGS, 1,	"allocate storage (vacuously)" },
D 30
	{ "REST", REST, STR1, 0,	"(restart command)" },
E 30
I 30
D 34
D 40
	{ "REST", REST, ARGS, 1,	"(restart command)" },
E 40
I 40
	{ "REST", REST, ARGS, 1,	"<sp> offset (restart command)" },
E 40
E 34
I 34
	{ "REST", REST, ARGS, 0,	"(restart command)" },
E 34
E 30
	{ "RNFR", RNFR, STR1, 1,	"<sp> file-name" },
	{ "RNTO", RNTO, STR1, 1,	"<sp> file-name" },
D 16
	{ "ABOR", ABOR, ARGS, 0,	"(abort operation)" },
E 16
I 16
	{ "ABOR", ABOR, ARGS, 1,	"(abort operation)" },
E 16
	{ "DELE", DELE, STR1, 1,	"<sp> file-name" },
D 27
	{ "CWD",  CWD,  OSTR, 1,	"[ <sp> directory-name]" },
E 27
I 27
	{ "CWD",  CWD,  OSTR, 1,	"[ <sp> directory-name ]" },
E 27
	{ "XCWD", CWD,	OSTR, 1,	"[ <sp> directory-name ]" },
	{ "LIST", LIST, OSTR, 1,	"[ <sp> path-name ]" },
	{ "NLST", NLST, OSTR, 1,	"[ <sp> path-name ]" },
D 33
	{ "SITE", SITE, STR1, 0,	"(get site parameters)" },
E 33
I 33
	{ "SITE", SITE, SITECMD, 1,	"site-cmd [ <sp> arguments ]" },
E 33
I 30
	{ "SYST", SYST, ARGS, 1,	"(get type of operating system)" },
E 30
D 33
	{ "STAT", STAT, OSTR, 0,	"(get server status)" },
E 33
I 33
	{ "STAT", STAT, OSTR, 1,	"[ <sp> path-name ]" },
E 33
	{ "HELP", HELP, OSTR, 1,	"[ <sp> <string> ]" },
	{ "NOOP", NOOP, ARGS, 1,	"" },
I 16
D 31
	{ "MKD",  XMKD, STR1, 1,	"<sp> path-name" },
E 16
	{ "XMKD", XMKD, STR1, 1,	"<sp> path-name" },
I 16
	{ "RMD",  XRMD, STR1, 1,	"<sp> path-name" },
E 16
	{ "XRMD", XRMD, STR1, 1,	"<sp> path-name" },
I 16
	{ "PWD",  XPWD, ARGS, 1,	"(return current directory)" },
E 16
	{ "XPWD", XPWD, ARGS, 1,	"(return current directory)" },
I 16
	{ "CDUP", XCUP, ARGS, 1,	"(change to parent directory)" },
E 16
	{ "XCUP", XCUP, ARGS, 1,	"(change to parent directory)" },
E 31
I 31
	{ "MKD",  MKD,  STR1, 1,	"<sp> path-name" },
	{ "XMKD", MKD,  STR1, 1,	"<sp> path-name" },
	{ "RMD",  RMD,  STR1, 1,	"<sp> path-name" },
	{ "XRMD", RMD,  STR1, 1,	"<sp> path-name" },
	{ "PWD",  PWD,  ARGS, 1,	"(return current directory)" },
	{ "XPWD", PWD,  ARGS, 1,	"(return current directory)" },
	{ "CDUP", CDUP, ARGS, 1,	"(change to parent directory)" },
	{ "XCUP", CDUP, ARGS, 1,	"(change to parent directory)" },
E 31
I 16
	{ "STOU", STOU, STR1, 1,	"<sp> file-name" },
I 33
	{ "SIZE", SIZE, OSTR, 1,	"<sp> path-name" },
	{ "MDTM", MDTM, OSTR, 1,	"<sp> path-name" },
E 33
E 16
	{ NULL,   0,    0,    0,	0 }
};

I 33
struct tab sitetab[] = {
	{ "UMASK", UMASK, ARGS, 1,	"[ <sp> umask ]" },
	{ "IDLE", IDLE, ARGS, 1,	"[ <sp> maximum-idle-time ]" },
	{ "CHMOD", CHMOD, NSTR, 1,	"<sp> mode <sp> file-name" },
	{ "HELP", HELP, OSTR, 1,	"[ <sp> <string> ]" },
	{ NULL,   0,    0,    0,	0 }
};

E 33
D 41
struct tab *
E 41
I 41
static char	*copy __P((char *));
static void	 help __P((struct tab *, char *));
static struct tab *
		 lookup __P((struct tab *, char *));
static void	 sizecmd __P((char *));
static void	 toolong __P((int));
static int	 yylex __P((void));

static struct tab *
E 41
D 33
lookup(cmd)
E 33
I 33
lookup(p, cmd)
D 44
	register struct tab *p;
E 44
I 44
	struct tab *p;
E 44
E 33
	char *cmd;
{
D 33
	register struct tab *p;
E 33

D 33
	for (p = cmdtab; p->name != NULL; p++)
E 33
I 33
	for (; p->name != NULL; p++)
E 33
		if (strcmp(cmd, p->name) == 0)
			return (p);
	return (0);
}

D 10
#include "../telnet/telnet.h"
E 10
I 10
#include <arpa/telnet.h>
E 10

/*
 * getline - a hacked up version of fgets to ignore TELNET escape codes.
 */
char *
getline(s, n, iop)
	char *s;
I 41
	int n;
E 41
D 44
	register FILE *iop;
E 44
I 44
	FILE *iop;
E 44
{
D 44
	register c;
E 44
I 44
	int c;
E 44
D 16
	register char *cs;
E 16
I 16
D 17
	register char *cs, ch;
E 17
I 17
	register char *cs;
D 19
	char ch;
E 19
E 17
E 16

	cs = s;
I 19
/* tmpline may contain saved command from urgent mode interruption */
E 19
D 16
	while (--n > 0 && (c = getc(iop)) >= 0) {
E 16
I 16
	for (c = 0; tmpline[c] != '\0' && --n > 0; ++c) {
		*cs++ = tmpline[c];
		if (tmpline[c] == '\n') {
			*cs++ = '\0';
D 27
			if (debug) {
D 17
				fprintf(stderr, "FTPD: command: %s", s);
E 17
I 17
				syslog(LOG_DEBUG, "FTPD: command: %s", s);
E 17
			}
E 27
I 27
			if (debug)
				syslog(LOG_DEBUG, "command: %s", s);
E 27
			tmpline[0] = '\0';
			return(s);
		}
D 27
		if (c == 0) {
E 27
I 27
		if (c == 0)
E 27
			tmpline[0] = '\0';
D 27
		}
E 27
	}
D 19
	while (--n > 0 && read(fileno(iop),&ch,1) >= 0) {
		c = 0377 & ch;
E 19
I 19
D 27
	while (--n > 0 && (c = getc(iop)) != EOF) {
D 26
		c = 0377 & c;
E 19
E 16
		while (c == IAC) {
D 16
			c = getc(iop);	/* skip command */
			c = getc(iop);	/* try next char */
E 16
I 16
D 17
			read(fileno(iop),&ch,1);	/* skip command */
			read(fileno(iop),&ch,1);	/* try next char */
E 17
I 17
D 19
			(void) read(fileno(iop),&ch,1);	/* skip command */
			(void) read(fileno(iop),&ch,1);	/* try next char */
E 17
			c = 0377 & ch;
E 19
I 19
			switch (c = 0377 & getc(iop)) {
E 26
I 26
		while ((0377&c) == IAC) {
			switch (0377&(c = getc(iop))) {
E 27
I 27
	while ((c = getc(iop)) != EOF) {
		c &= 0377;
		if (c == IAC) {
		    if ((c = getc(iop)) != EOF) {
			c &= 0377;
			switch (c) {
E 27
E 26
			case WILL:
			case WONT:
D 26
				c = 0377 & getc(iop);
				printf("%c%c%c", IAC, WONT, c);
E 26
I 26
				c = getc(iop);
D 27
				printf("%c%c%c", IAC, WONT, 0377&c);
E 27
I 27
				printf("%c%c%c", IAC, DONT, 0377&c);
E 27
E 26
				(void) fflush(stdout);
D 27
				break;
E 27
I 27
				continue;
E 27
			case DO:
			case DONT:
D 26
				c = 0377 & getc(iop);
				printf("%c%c%c", IAC, DONT, c);
E 26
I 26
				c = getc(iop);
D 27
				printf("%c%c%c", IAC, DONT, 0377&c);
E 27
I 27
				printf("%c%c%c", IAC, WONT, 0377&c);
E 27
E 26
				(void) fflush(stdout);
I 27
				continue;
			case IAC:
E 27
				break;
			default:
D 27
				break;
E 27
I 27
				continue;	/* ignore command */
E 27
			}
D 26
			c = 0377 & getc(iop); /* try next character */
E 26
I 26
D 27
			c = getc(iop); /* try next character */
E 27
I 27
		    }
E 27
E 26
E 19
E 16
		}
D 26
		*cs++ = c;
		if (c=='\n')
E 26
I 26
D 27
		*cs++ = 0377&c;
		if ((0377&c) == '\n')
E 27
I 27
		*cs++ = c;
		if (--n <= 0 || c == '\n')
E 27
E 26
			break;
	}
D 19
	if (c < 0 && cs == s)
E 19
I 19
	if (c == EOF && cs == s)
E 19
D 12
		return (NULL);
E 12
I 12
D 13
		exit(1);
E 13
I 13
		return (NULL);
E 13
E 12
	*cs++ = '\0';
D 2
	fprintf(stderr, "FTPD: command: '%s'\n", s);
E 2
I 2
D 9
	fprintf(stderr, "FTPD: command: %s", s);
	if (c != '\n')
		putc('\n', stderr);
E 2
	fflush(stderr);
E 9
I 9
D 27
	if (debug) {
D 17
		fprintf(stderr, "FTPD: command: %s", s);
		if (c != '\n')
			putc('\n', stderr);
		fflush(stderr);
E 17
I 17
		syslog(LOG_DEBUG, "FTPD: command: %s", s);
E 17
	}
E 27
I 27
D 39
	if (debug)
		syslog(LOG_DEBUG, "command: %s", s);
E 39
I 39
	if (debug) {
		if (!guest && strncasecmp("pass ", s, 5) == 0) {
			/* Don't syslog passwords */
			syslog(LOG_DEBUG, "command: %.5s ???", s);
		} else {
			register char *cp;
			register int len;

			/* Don't syslog trailing CR-LF */
			len = strlen(s);
			cp = s + len - 1;
			while (cp >= s && (*cp == '\n' || *cp == '\r')) {
				--cp;
				--len;
			}
			syslog(LOG_DEBUG, "command: %.*s", len, s);
		}
	}
E 39
E 27
E 9
	return (s);
}

I 9
D 38
static int
E 38
I 38
static void
E 38
D 41
toolong()
E 41
I 41
toolong(signo)
	int signo;
E 41
{
D 17
	long now;
E 17
I 17
D 39
	time_t now;
E 39
E 17
D 38
	extern char *ctime();
I 17
	extern time_t time();
E 38
E 17

	reply(421,
D 39
	  "Timeout (%d seconds): closing control connection.", timeout);
D 17
	time(&now);
E 17
I 17
	(void) time(&now);
E 17
	if (logging) {
D 17
		fprintf(stderr,
E 17
I 17
		syslog(LOG_INFO,
E 17
D 27
			"FTPD: User %s timed out after %d seconds at %s",
E 27
I 27
			"User %s timed out after %d seconds at %s",
E 27
			(pw ? pw -> pw_name : "unknown"), timeout, ctime(&now));
D 17
		fflush(stderr);
E 17
	}
E 39
I 39
	    "Timeout (%d seconds): closing control connection.", timeout);
	if (logging)
		syslog(LOG_INFO, "User %s timed out after %d seconds",
		    (pw ? pw -> pw_name : "unknown"), timeout);
E 39
D 11
	exit(1);
E 11
I 11
	dologout(1);
E 11
}

I 41
static int
E 41
E 9
yylex()
{
D 16
	static char cbuf[512];
E 16
	static int cpos, state;
D 33
	register char *cp;
E 33
I 33
D 44
	register char *cp, *cp2;
E 33
	register struct tab *p;
E 44
I 44
	char *cp, *cp2;
	struct tab *p;
E 44
	int n;
D 26
	char c;
E 26
I 26
D 38
	char c, *strpbrk();
I 33
	char *copy();
E 38
I 38
D 41
	char c, *copy();
E 41
I 41
	char c;
E 41
E 38
E 33
E 26

	for (;;) {
		switch (state) {

		case CMD:
I 9
D 17
			signal(SIGALRM, toolong);
			alarm(timeout);
E 17
I 17
			(void) signal(SIGALRM, toolong);
			(void) alarm((unsigned) timeout);
E 17
E 9
			if (getline(cbuf, sizeof(cbuf)-1, stdin) == NULL) {
				reply(221, "You could at least say goodbye.");
D 11
				exit(0);
E 11
I 11
				dologout(0);
E 11
			}
I 9
D 17
			alarm(0);
E 17
I 17
			(void) alarm(0);
I 31
#ifdef SETPROCTITLE
D 33
			if (strncasecmp(cbuf, "PASS", 4) != NULL) {
				setproctitle("%s: %s", remotehost, cbuf);
			}
E 33
I 33
			if (strncasecmp(cbuf, "PASS", 4) != NULL)
				setproctitle("%s: %s", proctitle, cbuf);
E 33
#endif /* SETPROCTITLE */
E 31
E 17
E 9
D 26
			if (index(cbuf, '\r')) {
				cp = index(cbuf, '\r');
				cp[0] = '\n'; cp[1] = 0;
E 26
I 26
D 27
			if ((cp = index(cbuf, '\r'))) {
E 27
I 27
D 29
			if ((cp = index(cbuf, '\r')))
E 27
				*cp++ = '\n'; *cp = '\0';
E 29
I 29
D 42
			if ((cp = index(cbuf, '\r'))) {
E 42
I 42
			if ((cp = strchr(cbuf, '\r'))) {
E 42
				*cp++ = '\n';
				*cp = '\0';
			}
E 29
E 26
D 27
			}
E 27
D 26
			if (index(cbuf, ' '))
				cpos = index(cbuf, ' ') - cbuf;
			else
I 16
				cpos = index(cbuf, '\n') - cbuf;
E 26
I 26
			if ((cp = strpbrk(cbuf, " \n")))
				cpos = cp - cbuf;
E 26
D 27
			if (cpos == 0) {
E 27
I 27
			if (cpos == 0)
E 27
E 16
				cpos = 4;
I 16
D 27
			}
E 27
E 16
			c = cbuf[cpos];
			cbuf[cpos] = '\0';
			upper(cbuf);
D 33
			p = lookup(cbuf);
E 33
I 33
			p = lookup(cmdtab, cbuf);
E 33
			cbuf[cpos] = c;
			if (p != 0) {
				if (p->implemented == 0) {
					nack(p->name);
D 17
					longjmp(errcatch);
E 17
I 17
					longjmp(errcatch,0);
E 17
					/* NOTREACHED */
				}
				state = p->state;
D 33
				yylval = (int) p->name;
E 33
I 33
D 44
				*(char **)&yylval = p->name;
E 44
I 44
				yylval.s = p->name;
E 44
E 33
				return (p->token);
			}
			break;

I 33
		case SITECMD:
			if (cbuf[cpos] == ' ') {
				cpos++;
				return (SP);
			}
			cp = &cbuf[cpos];
			if ((cp2 = strpbrk(cp, " \n")))
				cpos = cp2 - cbuf;
			c = cbuf[cpos];
			cbuf[cpos] = '\0';
			upper(cp);
			p = lookup(sitetab, cp);
			cbuf[cpos] = c;
			if (p != 0) {
				if (p->implemented == 0) {
					state = CMD;
					nack(p->name);
					longjmp(errcatch,0);
					/* NOTREACHED */
				}
				state = p->state;
D 44
				*(char **)&yylval = p->name;
E 44
I 44
				yylval.s = p->name;
E 44
				return (p->token);
			}
			state = CMD;
			break;

E 33
		case OSTR:
			if (cbuf[cpos] == '\n') {
				state = CMD;
				return (CRLF);
			}
D 28
			/* FALL THRU */
E 28
I 28
			/* FALLTHROUGH */
E 28

		case STR1:
I 27
		case ZSTR1:
I 33
		dostr1:
E 33
E 27
			if (cbuf[cpos] == ' ') {
				cpos++;
D 27
				state = STR2;
E 27
I 27
D 28
				state++;
E 28
I 28
				state = state == OSTR ? STR2 : ++state;
E 28
E 27
				return (SP);
			}
			break;
I 27

		case ZSTR2:
			if (cbuf[cpos] == '\n') {
				state = CMD;
				return (CRLF);
			}
D 33
			/* FALL THRU */
E 33
I 33
			/* FALLTHROUGH */
E 33
E 27

		case STR2:
			cp = &cbuf[cpos];
			n = strlen(cp);
			cpos += n - 1;
			/*
			 * Make sure the string is nonempty and \n terminated.
			 */
			if (n > 1 && cbuf[cpos] == '\n') {
				cbuf[cpos] = '\0';
D 33
				yylval = copy(cp);
E 33
I 33
D 44
				*(char **)&yylval = copy(cp);
E 44
I 44
				yylval.s = copy(cp);
E 44
E 33
				cbuf[cpos] = '\n';
				state = ARGS;
				return (STRING);
			}
			break;

I 33
		case NSTR:
			if (cbuf[cpos] == ' ') {
				cpos++;
				return (SP);
			}
			if (isdigit(cbuf[cpos])) {
				cp = &cbuf[cpos];
				while (isdigit(cbuf[++cpos]))
					;
				c = cbuf[cpos];
				cbuf[cpos] = '\0';
D 44
				yylval = atoi(cp);
E 44
I 44
				yylval.i = atoi(cp);
E 44
				cbuf[cpos] = c;
				state = STR1;
				return (NUMBER);
			}
			state = STR1;
			goto dostr1;

E 33
		case ARGS:
			if (isdigit(cbuf[cpos])) {
				cp = &cbuf[cpos];
				while (isdigit(cbuf[++cpos]))
					;
				c = cbuf[cpos];
				cbuf[cpos] = '\0';
D 44
				yylval = atoi(cp);
E 44
I 44
				yylval.i = atoi(cp);
E 44
				cbuf[cpos] = c;
				return (NUMBER);
			}
			switch (cbuf[cpos++]) {

			case '\n':
				state = CMD;
				return (CRLF);

			case ' ':
				return (SP);

			case ',':
				return (COMMA);

			case 'A':
			case 'a':
				return (A);

			case 'B':
			case 'b':
				return (B);

			case 'C':
			case 'c':
				return (C);

			case 'E':
			case 'e':
				return (E);

			case 'F':
			case 'f':
				return (F);

			case 'I':
			case 'i':
				return (I);

			case 'L':
			case 'l':
				return (L);

			case 'N':
			case 'n':
				return (N);

			case 'P':
			case 'p':
				return (P);

			case 'R':
			case 'r':
				return (R);

			case 'S':
			case 's':
				return (S);

			case 'T':
			case 't':
				return (T);

			}
			break;

		default:
			fatal("Unknown state in scanner.");
		}
D 17
		yyerror();
E 17
I 17
		yyerror((char *) 0);
E 17
		state = CMD;
D 17
		longjmp(errcatch);
E 17
I 17
		longjmp(errcatch,0);
E 17
	}
}

I 41
void
E 41
upper(s)
D 26
	char *s;
E 26
I 26
D 44
	register char *s;
E 44
I 44
	char *s;
E 44
E 26
{
	while (*s != '\0') {
		if (islower(*s))
			*s = toupper(*s);
		s++;
	}
}

I 33
D 41
char *
E 41
I 41
static char *
E 41
E 33
copy(s)
	char *s;
{
	char *p;
D 17
	extern char *malloc();
E 17
I 17
D 38
	extern char *malloc(), *strcpy();
E 38
E 17

D 17
	p = malloc(strlen(s) + 1);
E 17
I 17
	p = malloc((unsigned) strlen(s) + 1);
E 17
	if (p == NULL)
		fatal("Ran out of memory.");
D 17
	strcpy(p, s);
E 17
I 17
	(void) strcpy(p, s);
E 17
D 33
	return ((int)p);
E 33
I 33
	return (p);
E 33
}

I 41
static void
E 41
D 33
help(s)
E 33
I 33
help(ctab, s)
	struct tab *ctab;
E 33
	char *s;
{
D 44
	register struct tab *c;
	register int width, NCMDS;
E 44
I 44
	struct tab *c;
	int width, NCMDS;
E 44
I 33
	char *type;
E 33

I 33
	if (ctab == sitetab)
		type = "SITE ";
	else
		type = "";
E 33
	width = 0, NCMDS = 0;
D 33
	for (c = cmdtab; c->name != NULL; c++) {
D 22
		int len = strlen(c->name);
E 22
I 22
		int len = strlen(c->name) + 1;
E 33
I 33
	for (c = ctab; c->name != NULL; c++) {
		int len = strlen(c->name);
E 33
E 22

D 22
		if (c->implemented == 0)
			len++;
E 22
		if (len > width)
			width = len;
		NCMDS++;
	}
	width = (width + 8) &~ 7;
	if (s == 0) {
D 44
		register int i, j, w;
E 44
I 44
		int i, j, w;
E 44
		int columns, lines;

D 33
		lreply(214,
	  "The following commands are recognized (* =>'s unimplemented).");
E 33
I 33
		lreply(214, "The following %scommands are recognized %s.",
		    type, "(* =>'s unimplemented)");
E 33
		columns = 76 / width;
		if (columns == 0)
			columns = 1;
		lines = (NCMDS + columns - 1) / columns;
		for (i = 0; i < lines; i++) {
D 18
			printf("    ");
E 18
I 18
			printf("   ");
E 18
			for (j = 0; j < columns; j++) {
D 33
				c = cmdtab + j * lines + i;
E 33
I 33
				c = ctab + j * lines + i;
E 33
				printf("%s%c", c->name,
					c->implemented ? ' ' : '*');
D 2
				if (c + lines >= &cmdtab[NCMDS]) {
					printf("\r\n");
E 2
I 2
D 33
				if (c + lines >= &cmdtab[NCMDS])
E 33
I 33
				if (c + lines >= &ctab[NCMDS])
E 33
E 2
					break;
D 2
				}
E 2
D 22
				w = strlen(c->name);
E 22
I 22
				w = strlen(c->name) + 1;
E 22
				while (w < width) {
					putchar(' ');
					w++;
				}
			}
			printf("\r\n");
		}
D 17
		fflush(stdout);
E 17
I 17
		(void) fflush(stdout);
E 17
		reply(214, "Direct comments to ftp-bugs@%s.", hostname);
		return;
	}
	upper(s);
D 33
	c = lookup(s);
E 33
I 33
	c = lookup(ctab, s);
E 33
	if (c == (struct tab *)0) {
D 18
		reply(504, "Unknown command %s.", s);
E 18
I 18
		reply(502, "Unknown command %s.", s);
E 18
		return;
	}
	if (c->implemented)
D 33
		reply(214, "Syntax: %s %s", c->name, c->help);
E 33
I 33
		reply(214, "Syntax: %s%s %s", type, c->name, c->help);
E 33
	else
D 33
		reply(214, "%-*s\t%s; unimplemented.", width, c->name, c->help);
E 33
I 33
		reply(214, "%s%-*s\t%s; unimplemented.", type, width,
		    c->name, c->help);
}

I 41
static void
E 41
sizecmd(filename)
D 41
char *filename;
E 41
I 41
	char *filename;
E 41
{
	switch (type) {
	case TYPE_L:
	case TYPE_I: {
		struct stat stbuf;
D 44
		if (stat(filename, &stbuf) < 0 ||
		    (stbuf.st_mode&S_IFMT) != S_IFREG)
E 44
I 44
		if (stat(filename, &stbuf) < 0 || !S_ISREG(stbuf.st_mode))
E 44
			reply(550, "%s: not a plain file.", filename);
		else
D 44
			reply(213, "%lu", stbuf.st_size);
		break;}
E 44
I 44
			reply(213, "%qu", stbuf.st_size);
		break; }
E 44
	case TYPE_A: {
		FILE *fin;
D 35
		register int c, count;
E 35
I 35
D 44
		register int c;
		register long count;
E 44
I 44
		int c;
		off_t count;
E 44
E 35
		struct stat stbuf;
		fin = fopen(filename, "r");
		if (fin == NULL) {
			perror_reply(550, filename);
			return;
		}
D 44
		if (fstat(fileno(fin), &stbuf) < 0 ||
		    (stbuf.st_mode&S_IFMT) != S_IFREG) {
E 44
I 44
		if (fstat(fileno(fin), &stbuf) < 0 || !S_ISREG(stbuf.st_mode)) {
E 44
			reply(550, "%s: not a plain file.", filename);
			(void) fclose(fin);
			return;
		}

		count = 0;
		while((c=getc(fin)) != EOF) {
			if (c == '\n')	/* will get expanded to \r\n */
				count++;
			count++;
		}
		(void) fclose(fin);

D 44
		reply(213, "%ld", count);
		break;}
E 44
I 44
		reply(213, "%qd", count);
		break; }
E 44
	default:
		reply(504, "SIZE not implemented for Type %c.", "?AEIL"[type]);
	}
E 33
}
E 1
