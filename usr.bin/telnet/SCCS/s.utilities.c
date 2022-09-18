h50141
s 00002/00002/00911
d D 8.3 95/05/30 20:57:19 dab 31 30
c code cleanup, change b*() calls to mem*() calls
e
s 00056/00032/00857
d D 8.2 93/12/15 11:36:05 dab 30 29
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00002/00002/00887
d D 8.1 93/06/06 16:34:00 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00887
d D 5.8 93/05/20 10:49:40 dab 28 26
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00002/00002/00887
d R 5.8 93/05/20 10:37:28 dab 27 26
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00013/00004/00876
d D 5.7 93/04/05 17:06:00 dab 26 25
c Fix gcc2 warnings.
c Fix the generation/parsing of the Environment option SEND suboption.
c Add code (#ifdef ENV_HACK) to help interoperation with Telnet servers
c that have the definitions for ENV_VAR and ENV_VALUE reversed.
e
s 00006/00002/00874
d D 5.6 93/01/19 12:53:11 dab 25 24
c Add in knowledge of RESTART-ANY and
c RESTART-XON in the option printing code where
c it prints out flow control suboptions.
e
s 00009/00002/00867
d D 5.5 92/12/18 14:06:59 dab 24 23
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00001/00001/00868
d D 5.4 92/11/16 23:24:42 torek 23 22
c gcc -Wall points out bogus subscript
e
s 00023/00006/00846
d D 5.3 91/03/22 13:08:36 dab 22 21
c Upgrade to the latest & greatest authentication/encryption
e
s 00173/00084/00679
d D 5.2 91/03/01 01:31:52 dab 21 20
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00000/00000/00763
d D 5.1 90/09/14 10:42:11 borman 20 19
c Bump the sccs id to 5.1
e
s 00091/00028/00672
d D 1.19 90/06/28 12:58:09 borman 19 18
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00065/00002/00635
d D 1.18 90/06/20 16:44:37 kfall 18 17
c towards Kerberized telnet
e
s 00001/00011/00636
d D 1.17 90/06/01 17:47:01 bostic 17 16
c new copyright notice
e
s 00001/00013/00646
d D 1.16 89/11/14 10:20:22 borman 16 15
c Latest & greatest version of telnet
e
s 00115/00030/00544
d D 1.15 89/09/01 15:47:56 borman 15 14
c  RFC 1091 term type support, STATUS support, BINARY changes
e
s 00324/00027/00250
d D 1.14 89/08/21 14:59:03 borman 14 13
c Add support for LINEMODE option
e
s 00002/00002/00275
d D 1.13 89/05/30 22:08:18 minshall 13 12
c Put \r's to STDOUT, not to anyone else.
e
s 00013/00019/00264
d D 1.12 89/03/21 22:30:53 minshall 12 11
c Keep track of each side's idea of what the state of each option is.
e
s 00002/00000/00281
d D 1.11 89/02/06 19:05:10 minshall 11 10
c Flush NetTrace in case of a crash or loop.
e
s 00002/00000/00279
d D 1.10 88/12/01 09:21:20 minshall 10 9
c Oops - make work on older (4.2) systems.
e
s 00005/00000/00274
d D 1.9 88/11/30 22:36:43 minshall 9 8
c OK, flush out network input buffer also...
e
s 00086/00000/00188
d D 1.8 88/11/30 22:27:59 minshall 8 7
c Flush out the last dregs in the terminal before quitting when
c the remote side quits (actually, there *may* be something left in the
c network input ring, so we don't actually guarantee to get everything).
e
s 00010/00005/00178
d D 1.7 88/06/29 20:15:42 bostic 7 6
c install approved copyright notice
e
s 00002/00001/00181
d D 1.6 88/06/27 22:19:37 minshall 6 5
c Fix up lint errors.
e
s 00002/00000/00180
d D 1.5 88/05/15 19:24:36 minshall 5 4
c Include "general.h" to get rid of ansi mem* functions.
e
s 00016/00000/00164
d D 1.4 88/03/08 10:31:26 bostic 4 3
c add Berkeley specific copyright
e
s 00001/00001/00163
d D 1.3 88/01/07 11:54:05 minshall 3 2
c Reduce extern's.
e
s 00003/00000/00161
d D 1.2 87/10/10 14:27:21 minshall 2 1
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00161/00000/00000
d D 1.1 87/09/11 15:40:52 minshall 1 0
c date and time created 87/09/11 15:40:52 by minshall
e
u
U
t
T
I 4
/*
D 29
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 17
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 17
I 17
D 18
 * %sccs.include.redist.c%
E 18
I 18
D 19
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 18
E 17
E 7
 */

#ifndef lint
D 18
static char sccsid[] = "%W% (Berkeley) %G%";
E 18
I 18
D 19
static char sccsid[] = "@(#)utilities.c	1.17 (Berkeley) 6/1/90";
E 19
I 19
static char sccsid[] = "%W% (Berkeley) %G%";
E 19
E 18
#endif /* not lint */

E 4
I 1
#define	TELOPTS
I 14
#define	TELCMDS
I 21
#define	SLC_NAMES
E 21
E 14
#include <arpa/telnet.h>
I 2
#include <sys/types.h>
I 19
#include <sys/time.h>
E 19
E 2

#include <ctype.h>
I 2

I 5
#include "general.h"

I 10
#include "fdset.h"

E 10
E 5
#include "ring.h"
E 2

I 8
#include "defines.h"

E 8
#include "externs.h"

FILE	*NetTrace = 0;		/* Not in bss, since needs to stay */
I 14
int	prettydump;
E 14

/*
 * upcase()
 *
 *	Upcase (in place) the argument.
 */

D 21
void
E 21
I 21
    void
E 21
upcase(argument)
D 21
register char *argument;
E 21
I 21
    register char *argument;
E 21
{
    register int c;

    while ((c = *argument) != 0) {
	if (islower(c)) {
	    *argument = toupper(c);
	}
	argument++;
    }
}

/*
 * SetSockOpt()
 *
 * Compensate for differences in 4.2 and 4.3 systems.
 */

D 21
int
E 21
I 21
    int
E 21
SetSockOpt(fd, level, option, yesno)
D 21
int
	fd,
	level,
	option,
	yesno;
E 21
I 21
    int fd, level, option, yesno;
E 21
{
#ifndef	NOT43
    return setsockopt(fd, level, option,
				(char *)&yesno, sizeof yesno);
#else	/* NOT43 */
    if (yesno == 0) {		/* Can't do that in 4.2! */
	fprintf(stderr, "Error: attempt to turn off an option 0x%x.\n",
				option);
	return -1;
    }
    return setsockopt(fd, level, option, 0, 0);
#endif	/* NOT43 */
}

/*
 * The following are routines used to print out debugging information.
 */

I 14
D 16
char NetTraceFile[256] = "(standard output)";
E 16
I 16
unsigned char NetTraceFile[256] = "(standard output)";
E 16
E 14

D 21
void
E 21
I 21
    void
E 21
I 14
SetNetTrace(file)
D 21
register char *file;
E 21
I 21
    register char *file;
E 21
{
    if (NetTrace && NetTrace != stdout)
	fclose(NetTrace);
    if (file  && (strcmp(file, "-") != 0)) {
	NetTrace = fopen(file, "w");
	if (NetTrace) {
D 21
	    strcpy(NetTraceFile, file);
E 21
I 21
	    strcpy((char *)NetTraceFile, file);
E 21
	    return;
	}
	fprintf(stderr, "Cannot open %s.\n", file);
    }
    NetTrace = stdout;
D 21
    strcpy(NetTraceFile, "(standard output)");
E 21
I 21
    strcpy((char *)NetTraceFile, "(standard output)");
E 21
}

D 21
void
E 21
I 21
    void
E 21
E 14
Dump(direction, buffer, length)
D 21
char	direction;
char	*buffer;
int	length;
E 21
I 21
    char direction;
    unsigned char *buffer;
    int length;
E 21
{
#   define BYTES_PER_LINE	32
#   define min(x,y)	((x<y)? x:y)
D 21
    char *pThis;
E 21
I 21
    unsigned char *pThis;
E 21
    int offset;
I 14
    extern pettydump;
E 14

    offset = 0;

    while (length) {
	/* print one line */
	fprintf(NetTrace, "%c 0x%x\t", direction, offset);
	pThis = buffer;
D 14
	buffer = buffer+min(length, BYTES_PER_LINE);
	while (pThis < buffer) {
	    fprintf(NetTrace, "%.2x", (*pThis)&0xff);
	    pThis++;
E 14
I 14
	if (prettydump) {
D 15
	    buffer = buffer + min(length, BYTES_PER_LINE);
E 15
I 15
	    buffer = buffer + min(length, BYTES_PER_LINE/2);
E 15
	    while (pThis < buffer) {
		fprintf(NetTrace, "%c%.2x",
		    (((*pThis)&0xff) == 0xff) ? '*' : ' ',
		    (*pThis)&0xff);
		pThis++;
	    }
I 15
	    length -= BYTES_PER_LINE/2;
	    offset += BYTES_PER_LINE/2;
E 15
	} else {
D 15
	    buffer = buffer + min(length, BYTES_PER_LINE/2);
E 15
I 15
	    buffer = buffer + min(length, BYTES_PER_LINE);
E 15
	    while (pThis < buffer) {
		fprintf(NetTrace, "%.2x", (*pThis)&0xff);
		pThis++;
	    }
I 15
	    length -= BYTES_PER_LINE;
	    offset += BYTES_PER_LINE;
E 15
E 14
	}
D 12
	fprintf(NetTrace, "\n");
E 12
I 12
	if (NetTrace == stdout) {
D 13
	    fprintf(NetTrace, "\n");
	} else {
E 13
	    fprintf(NetTrace, "\r\n");
I 13
	} else {
	    fprintf(NetTrace, "\n");
E 13
	}
E 12
D 15
	length -= BYTES_PER_LINE;
	offset += BYTES_PER_LINE;
E 15
	if (length < 0) {
I 11
	    fflush(NetTrace);
E 11
	    return;
	}
	/* find next unique line */
    }
I 11
    fflush(NetTrace);
E 11
}


D 12
/*VARARGS*/
E 12
D 21
void
D 12
printoption(direction, fmt, option, what)
E 12
I 12
printoption(direction, fmt, option)
E 12
	char *direction, *fmt;
D 12
	int option, what;
E 12
I 12
	int option;
E 21
I 21
	void
printoption(direction, cmd, option)
	char *direction;
	int cmd, option;
E 21
E 12
{
	if (!showoptions)
		return;
D 12
	fprintf(NetTrace, "%s ", direction+1);
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
E 12
I 12
D 21
	fprintf(NetTrace, "%s ", direction);
E 12
D 14
	if (option < (sizeof telopts/sizeof telopts[0]))
		fprintf(NetTrace, "%s %s", fmt, telopts[option]);
E 14
I 14
	if (TELOPT_OK(option))
		fprintf(NetTrace, "%s %s", fmt, TELOPT(option));
	else if (TELCMD_OK(option))
		fprintf(NetTrace, "%s %s", fmt, TELCMD(option));
E 14
	else
		fprintf(NetTrace, "%s %d", fmt, option);
E 21
I 21
	if (cmd == IAC) {
		if (TELCMD_OK(option))
		    fprintf(NetTrace, "%s IAC %s", direction, TELCMD(option));
		else
		    fprintf(NetTrace, "%s IAC %d", direction, option);
	} else {
		register char *fmt;
		fmt = (cmd == WILL) ? "WILL" : (cmd == WONT) ? "WONT" :
			(cmd == DO) ? "DO" : (cmd == DONT) ? "DONT" : 0;
		if (fmt) {
		    fprintf(NetTrace, "%s %s ", direction, fmt);
		    if (TELOPT_OK(option))
			fprintf(NetTrace, "%s", TELOPT(option));
		    else if (option == TELOPT_EXOPL)
			fprintf(NetTrace, "EXOPL");
		    else
			fprintf(NetTrace, "%d", option);
		} else
		    fprintf(NetTrace, "%s %d %d", direction, cmd, option);
	}
E 21
D 12
	if (*direction == '<') {
		fprintf(NetTrace, "\r\n");
		return;
E 12
I 12
D 14
	if (NetTrace == stdout) {
E 14
I 14
D 30
	if (NetTrace == stdout)
E 30
I 30
	if (NetTrace == stdout) {
E 30
E 14
	    fprintf(NetTrace, "\r\n");
D 14
	} else {
E 14
I 14
D 30
	else
E 30
I 30
	    fflush(NetTrace);
	} else {
E 30
E 14
	    fprintf(NetTrace, "\n");
I 30
	}
E 30
E 12
D 14
	}
E 14
D 12
	fprintf(NetTrace, " (%s)\r\n", what ? "reply" : "don't reply");
E 12
I 12
	return;
E 12
}

I 21
    void
E 21
I 14
optionstatus()
{
    register int i;
    extern char will_wont_resp[], do_dont_resp[];

    for (i = 0; i < 256; i++) {
	if (do_dont_resp[i]) {
	    if (TELOPT_OK(i))
		printf("resp DO_DONT %s: %d\n", TELOPT(i), do_dont_resp[i]);
	    else if (TELCMD_OK(i))
		printf("resp DO_DONT %s: %d\n", TELCMD(i), do_dont_resp[i]);
	    else
		printf("resp DO_DONT %d: %d\n", i,
				do_dont_resp[i]);
	    if (my_want_state_is_do(i)) {
		if (TELOPT_OK(i))
		    printf("want DO   %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want DO   %s\n", TELCMD(i));
		else
		    printf("want DO   %d\n", i);
	    } else {
		if (TELOPT_OK(i))
		    printf("want DONT %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want DONT %s\n", TELCMD(i));
		else
		    printf("want DONT %d\n", i);
	    }
	} else {
	    if (my_state_is_do(i)) {
		if (TELOPT_OK(i))
		    printf("     DO   %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("     DO   %s\n", TELCMD(i));
		else
		    printf("     DO   %d\n", i);
	    }
	}
	if (will_wont_resp[i]) {
	    if (TELOPT_OK(i))
		printf("resp WILL_WONT %s: %d\n", TELOPT(i), will_wont_resp[i]);
	    else if (TELCMD_OK(i))
		printf("resp WILL_WONT %s: %d\n", TELCMD(i), will_wont_resp[i]);
	    else
		printf("resp WILL_WONT %d: %d\n",
				i, will_wont_resp[i]);
	    if (my_want_state_is_will(i)) {
		if (TELOPT_OK(i))
		    printf("want WILL %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want WILL %s\n", TELCMD(i));
		else
		    printf("want WILL %d\n", i);
	    } else {
		if (TELOPT_OK(i))
		    printf("want WONT %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want WONT %s\n", TELCMD(i));
		else
		    printf("want WONT %d\n", i);
	    }
	} else {
	    if (my_state_is_will(i)) {
		if (TELOPT_OK(i))
		    printf("     WILL %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("     WILL %s\n", TELCMD(i));
		else
		    printf("     WILL %d\n", i);
	    }
	}
    }

}

D 21
char *slcnames[] = { SLC_NAMES };

I 18
#ifdef	KERBEROS
static char *authtypes[3] = { "NONE", "PRIVATE", "KERBEROS" };
D 19
#else
static char *authtypes[2] = { "NONE", "PRIVATE" };
E 19
#endif

E 18
E 14
void
E 21
I 21
    void
E 21
printsub(direction, pointer, length)
D 14
char	*direction,		/* "<" or ">" */
	*pointer;		/* where suboption data sits */
E 14
I 14
D 21
char	direction;		/* '<' or '>' */
unsigned char	*pointer;	/* where suboption data sits */
E 14
int	length;			/* length of suboption data */
E 21
I 21
    char direction;	/* '<' or '>' */
    unsigned char *pointer;	/* where suboption data sits */
    int		  length;	/* length of suboption data */
E 21
{
I 14
    register int i;
I 21
D 22
    char buf[256];
E 22
I 22
    char buf[512];
E 22
    extern int want_status_response;
E 21

E 14
D 21
    if (showoptions) {
E 21
I 21
    if (showoptions || direction == 0 ||
	(want_status_response && (pointer[0] == TELOPT_STATUS))) {
E 21
D 15
	fprintf(NetTrace, "%s suboption ",
E 15
I 15
	if (direction) {
D 21
	    fprintf(NetTrace, "%s suboption ",
E 15
D 14
				(direction[0] == '<')? "Received":"Sent");
E 14
I 14
				(direction == '<')? "Received":"Sent");
E 21
I 21
	    fprintf(NetTrace, "%s IAC SB ",
				(direction == '<')? "RCVD":"SENT");
E 21
D 15
	if (length >= 3) {
	    register int j;
E 15
I 15
	    if (length >= 3) {
		register int j;
E 15

D 15
	    i = pointer[length-2];
	    j = pointer[length-1];
E 15
I 15
		i = pointer[length-2];
		j = pointer[length-1];
E 15

D 15
	    if (i != IAC || j != SE) {
		fprintf(NetTrace, "(terminated by ");
		if (TELOPT_OK(i))
		    fprintf(NetTrace, "%s ", TELOPT(i));
		else if (TELCMD_OK(i))
		    fprintf(NetTrace, "%s ", TELCMD(i));
		else
		    fprintf(NetTrace, "%d ", i);
		if (TELOPT_OK(j))
		    fprintf(NetTrace, "%s", TELOPT(j));
		else if (TELCMD_OK(j))
		    fprintf(NetTrace, "%s", TELCMD(j));
		else
		    fprintf(NetTrace, "%d", j);
		fprintf(NetTrace, ", not IAC SE!) ");
E 15
I 15
		if (i != IAC || j != SE) {
		    fprintf(NetTrace, "(terminated by ");
		    if (TELOPT_OK(i))
			fprintf(NetTrace, "%s ", TELOPT(i));
		    else if (TELCMD_OK(i))
			fprintf(NetTrace, "%s ", TELCMD(i));
		    else
			fprintf(NetTrace, "%d ", i);
		    if (TELOPT_OK(j))
			fprintf(NetTrace, "%s", TELOPT(j));
		    else if (TELCMD_OK(j))
			fprintf(NetTrace, "%s", TELCMD(j));
		    else
			fprintf(NetTrace, "%d", j);
		    fprintf(NetTrace, ", not IAC SE!) ");
		}
E 15
	    }
I 15
	    length -= 2;
E 15
	}
D 15
	length -= 2;
E 15
	if (length < 1) {
D 30
	    fprintf(NetTrace, "(Empty suboption???)");
E 30
I 30
	    fprintf(NetTrace, "(Empty suboption??\?)");
	    if (NetTrace == stdout)
		fflush(NetTrace);
E 30
	    return;
	}
E 14
	switch (pointer[0]) {
	case TELOPT_TTYPE:
D 14
	    fprintf(NetTrace, "Terminal type ");
E 14
I 14
	    fprintf(NetTrace, "TERMINAL-TYPE ");
E 14
	    switch (pointer[1]) {
	    case TELQUAL_IS:
D 14
		{
D 3
		    char tmpbuf[sizeof subbuffer];
E 3
I 3
		    char tmpbuf[SUBBUFSIZE];
E 3
		    int minlen = min(length, sizeof tmpbuf);

		    memcpy(tmpbuf, pointer+2, minlen);
		    tmpbuf[minlen-1] = 0;
		    fprintf(NetTrace, "is %s.\n", tmpbuf);
		}
E 14
I 14
D 19
		fprintf(NetTrace, "IS \"%.*s\"", length-2, pointer+2);
E 19
I 19
		fprintf(NetTrace, "IS \"%.*s\"", length-2, (char *)pointer+2);
E 19
E 14
		break;
	    case TELQUAL_SEND:
D 14
		fprintf(NetTrace, "- request to send.\n");
E 14
I 14
		fprintf(NetTrace, "SEND");
E 14
		break;
	    default:
		fprintf(NetTrace,
D 6
				"- unknown qualifier %d (0x%x).\n", pointer[1]);
E 6
I 6
D 14
				"- unknown qualifier %d (0x%x).\n",
E 14
I 14
				"- unknown qualifier %d (0x%x).",
E 14
				pointer[1], pointer[1]);
E 6
	    }
	    break;
I 14
	case TELOPT_TSPEED:
	    fprintf(NetTrace, "TERMINAL-SPEED");
	    if (length < 2) {
D 30
		fprintf(NetTrace, " (empty suboption???)");
E 30
I 30
		fprintf(NetTrace, " (empty suboption??\?)");
E 30
		break;
	    }
	    switch (pointer[1]) {
D 15
	    case 0:
E 15
I 15
	    case TELQUAL_IS:
E 15
		fprintf(NetTrace, " IS ");
D 19
		fprintf(NetTrace, "%.*s", length-2, pointer+2);
E 19
I 19
		fprintf(NetTrace, "%.*s", length-2, (char *)pointer+2);
E 19
		break;
	    default:
		if (pointer[1] == 1)
		    fprintf(NetTrace, " SEND");
		else
D 19
		    fprintf(NetTrace, " %d (unknown)");
E 19
I 19
		    fprintf(NetTrace, " %d (unknown)", pointer[1]);
E 19
		for (i = 2; i < length; i++)
		    fprintf(NetTrace, " ?%d?", pointer[i]);
		break;
	    }
	    break;

	case TELOPT_LFLOW:
	    fprintf(NetTrace, "TOGGLE-FLOW-CONTROL");
	    if (length < 2) {
D 30
		fprintf(NetTrace, " (empty suboption???)");
E 30
I 30
		fprintf(NetTrace, " (empty suboption??\?)");
E 30
		break;
	    }
	    switch (pointer[1]) {
D 25
	    case 0:
E 25
I 25
	    case LFLOW_OFF:
E 25
		fprintf(NetTrace, " OFF"); break;
D 25
	    case 1:
E 25
I 25
	    case LFLOW_ON:
E 25
		fprintf(NetTrace, " ON"); break;
I 25
	    case LFLOW_RESTART_ANY:
		fprintf(NetTrace, " RESTART-ANY"); break;
	    case LFLOW_RESTART_XON:
		fprintf(NetTrace, " RESTART-XON"); break;
E 25
	    default:
D 19
		fprintf(NetTrace, " %d (unknown)");
E 19
I 19
		fprintf(NetTrace, " %d (unknown)", pointer[1]);
E 19
	    }
	    for (i = 2; i < length; i++)
		fprintf(NetTrace, " ?%d?", pointer[i]);
	    break;

	case TELOPT_NAWS:
	    fprintf(NetTrace, "NAWS");
	    if (length < 2) {
D 30
		fprintf(NetTrace, " (empty suboption???)");
E 30
I 30
		fprintf(NetTrace, " (empty suboption??\?)");
E 30
		break;
	    }
	    if (length == 2) {
		fprintf(NetTrace, " ?%d?", pointer[1]);
		break;
	    }
	    fprintf(NetTrace, " %d %d (%d)",
		pointer[1], pointer[2],
D 19
		(((unsigned int)pointer[1])<<8)|((unsigned int)pointer[2]));
E 19
I 19
		(int)((((unsigned int)pointer[1])<<8)|((unsigned int)pointer[2])));
E 19
	    if (length == 4) {
		fprintf(NetTrace, " ?%d?", pointer[3]);
		break;
	    }
	    fprintf(NetTrace, " %d %d (%d)",
		pointer[3], pointer[4],
D 19
		(((unsigned int)pointer[3])<<8)|((unsigned int)pointer[4]));
E 19
I 19
		(int)((((unsigned int)pointer[3])<<8)|((unsigned int)pointer[4])));
E 19
	    for (i = 5; i < length; i++)
		fprintf(NetTrace, " ?%d?", pointer[i]);
	    break;
I 18

D 21
#ifdef	KERBEROS
E 21
I 21
D 24
#if	defined(AUTHENTICATE)
E 24
I 24
#if	defined(AUTHENTICATION)
E 24
E 21
	case TELOPT_AUTHENTICATION:
D 21
	    fprintf(NetTrace, "Authentication information ");
E 21
I 21
	    fprintf(NetTrace, "AUTHENTICATION");
	    if (length < 2) {
D 30
		fprintf(NetTrace, " (empty suboption???)");
E 30
I 30
		fprintf(NetTrace, " (empty suboption??\?)");
E 30
		break;
	    }
E 21
	    switch (pointer[1]) {
I 21
	    case TELQUAL_REPLY:
E 21
	    case TELQUAL_IS:
D 21
		switch (pointer[2]) {
		case TELQUAL_AUTHTYPE_NONE:
		case TELQUAL_AUTHTYPE_PRIVATE:
		case TELQUAL_AUTHTYPE_KERBEROS:
E 21
I 21
		fprintf(NetTrace, " %s ", (pointer[1] == TELQUAL_IS) ?
							"IS" : "REPLY");
		if (AUTHTYPE_NAME_OK(pointer[2]))
		    fprintf(NetTrace, "%s ", AUTHTYPE_NAME(pointer[2]));
		else
		    fprintf(NetTrace, "%d ", pointer[2]);
		if (length < 3) {
D 30
		    fprintf(NetTrace, "(partial suboption???)");
E 30
I 30
		    fprintf(NetTrace, "(partial suboption??\?)");
E 30
		    break;
		}
		fprintf(NetTrace, "%s|%s",
D 22
			(pointer[3] & AUTH_WHO_MASK == AUTH_WHO_CLIENT) ?
E 22
I 22
			((pointer[3] & AUTH_WHO_MASK) == AUTH_WHO_CLIENT) ?
E 22
			"CLIENT" : "SERVER",
D 22
			(pointer[3] & AUTH_HOW_MASK == AUTH_HOW_MUTUAL) ?
E 22
I 22
			((pointer[3] & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) ?
E 22
			"MUTUAL" : "ONE-WAY");
E 21

D 21
			fprintf(NetTrace, "is type %s\r\n", authtypes[pointer[2]]);
E 21
I 21
		auth_printsub(&pointer[1], length - 1, buf, sizeof(buf));
		fprintf(NetTrace, "%s", buf);
		break;

	    case TELQUAL_SEND:
		i = 2;
		fprintf(NetTrace, " SEND ");
		while (i < length) {
		    if (AUTHTYPE_NAME_OK(pointer[i]))
			fprintf(NetTrace, "%s ", AUTHTYPE_NAME(pointer[i]));
		    else
			fprintf(NetTrace, "%d ", pointer[i]);
		    if (++i >= length) {
D 30
			fprintf(NetTrace, "(partial suboption???)");
E 30
I 30
			fprintf(NetTrace, "(partial suboption??\?)");
E 30
E 21
			break;
D 21
		default:
			fprintf(NetTrace, "is type unknown\r\n");
			break;
E 21
I 21
		    }
		    fprintf(NetTrace, "%s|%s ",
D 22
			(pointer[i] & AUTH_WHO_MASK == AUTH_WHO_CLIENT) ?
E 22
I 22
			((pointer[i] & AUTH_WHO_MASK) == AUTH_WHO_CLIENT) ?
E 22
							"CLIENT" : "SERVER",
D 22
			(pointer[i] & AUTH_HOW_MASK == AUTH_HOW_MUTUAL) ?
E 22
I 22
			((pointer[i] & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) ?
E 22
							"MUTUAL" : "ONE-WAY");
		    ++i;
E 21
		}
I 21
		break;
E 21

I 22
	    case TELQUAL_NAME:
		i = 2;
		fprintf(NetTrace, " NAME \"");
		while (i < length)
		    putc(pointer[i++], NetTrace);
		putc('"', NetTrace);
		break;

E 22
D 21
	    case TELQUAL_SEND:
	    {
		int	idx = 2;
		fprintf(NetTrace, "- request to send, types");
		for (idx = 2; idx < length - 1; idx++)
			switch (pointer[idx]) {
			case TELQUAL_AUTHTYPE_NONE:
			case TELQUAL_AUTHTYPE_PRIVATE:
			case TELQUAL_AUTHTYPE_KERBEROS:
				fprintf(NetTrace, " %s",
					authtypes[pointer[idx]]);
					break;
			default:
				fprintf(NetTrace, " <unknown %u>",
					pointer[idx]);
				break;
			}
		fprintf(NetTrace, "\r\n");
E 21
I 21
	    default:
		    for (i = 2; i < length; i++)
			fprintf(NetTrace, " ?%d?", pointer[i]);
		    break;
E 21
	    }
I 21
	    break;
#endif

D 24
#if	defined(ENCRYPT)
E 24
I 24
D 28
#if	defined(ENCRYPTION)
E 28
I 28
#ifdef	ENCRYPTION
E 28
E 24
	case TELOPT_ENCRYPT:
	    fprintf(NetTrace, "ENCRYPT");
	    if (length < 2) {
D 30
		fprintf(NetTrace, " (empty suboption???)");
E 30
I 30
		fprintf(NetTrace, " (empty suboption??\?)");
E 30
E 21
		break;
I 21
	    }
	    switch (pointer[1]) {
	    case ENCRYPT_START:
		fprintf(NetTrace, " START");
		break;
E 21

I 21
	    case ENCRYPT_END:
		fprintf(NetTrace, " END");
		break;

	    case ENCRYPT_REQSTART:
		fprintf(NetTrace, " REQUEST-START");
		break;

	    case ENCRYPT_REQEND:
		fprintf(NetTrace, " REQUEST-END");
		break;

	    case ENCRYPT_IS:
	    case ENCRYPT_REPLY:
		fprintf(NetTrace, " %s ", (pointer[1] == ENCRYPT_IS) ?
							"IS" : "REPLY");
		if (length < 3) {
D 30
		    fprintf(NetTrace, " (partial suboption???)");
E 30
I 30
		    fprintf(NetTrace, " (partial suboption??\?)");
E 30
		    break;
		}
		if (ENCTYPE_NAME_OK(pointer[2]))
		    fprintf(NetTrace, "%s ", ENCTYPE_NAME(pointer[2]));
		else
		    fprintf(NetTrace, " %d (unknown)", pointer[2]);

		encrypt_printsub(&pointer[1], length - 1, buf, sizeof(buf));
		fprintf(NetTrace, "%s", buf);
		break;

	    case ENCRYPT_SUPPORT:
		i = 2;
		fprintf(NetTrace, " SUPPORT ");
		while (i < length) {
		    if (ENCTYPE_NAME_OK(pointer[i]))
			fprintf(NetTrace, "%s ", ENCTYPE_NAME(pointer[i]));
		    else
			fprintf(NetTrace, "%d ", pointer[i]);
		    i++;
		}
		break;

I 22
	    case ENCRYPT_ENC_KEYID:
		fprintf(NetTrace, " ENC_KEYID ");
		goto encommon;

	    case ENCRYPT_DEC_KEYID:
		fprintf(NetTrace, " DEC_KEYID ");
		goto encommon;

E 22
E 21
	    default:
D 21
		fprintf(NetTrace, " - unknown qualifier %d (0x%x).\r\n",
			pointer[1], pointer[1]);
E 21
I 21
D 22
		fprintf(NetTrace, "%d (unknown)", pointer[1]);
E 22
I 22
		fprintf(NetTrace, " %d (unknown)", pointer[1]);
	    encommon:
E 22
		for (i = 2; i < length; i++)
		    fprintf(NetTrace, " %d", pointer[i]);
		break;
E 21
	    }
	    break;
D 21
#endif /* KERBEROS */
E 21
I 21
D 28
#endif
E 28
I 28
#endif	/* ENCRYPTION */
E 28
E 21
E 18

	case TELOPT_LINEMODE:
	    fprintf(NetTrace, "LINEMODE ");
	    if (length < 2) {
D 30
		fprintf(NetTrace, " (empty suboption???)");
E 30
I 30
		fprintf(NetTrace, " (empty suboption??\?)");
E 30
		break;
	    }
	    switch (pointer[1]) {
	    case WILL:
		fprintf(NetTrace, "WILL ");
		goto common;
	    case WONT:
		fprintf(NetTrace, "WONT ");
		goto common;
	    case DO:
		fprintf(NetTrace, "DO ");
		goto common;
	    case DONT:
		fprintf(NetTrace, "DONT ");
	    common:
		if (length < 3) {
D 30
		    fprintf(NetTrace, "(no option???)");
E 30
I 30
		    fprintf(NetTrace, "(no option??\?)");
E 30
		    break;
		}
		switch (pointer[2]) {
		case LM_FORWARDMASK:
		    fprintf(NetTrace, "Forward Mask");
		    for (i = 3; i < length; i++)
			fprintf(NetTrace, " %x", pointer[i]);
		    break;
		default:
		    fprintf(NetTrace, "%d (unknown)", pointer[2]);
		    for (i = 3; i < length; i++)
			fprintf(NetTrace, " %d", pointer[i]);
		    break;
		}
		break;
D 31
		
E 31
I 31

E 31
	    case LM_SLC:
		fprintf(NetTrace, "SLC");
		for (i = 2; i < length - 2; i += 3) {
D 21
		    if (pointer[i+SLC_FUNC] <= NSLC)
			fprintf(NetTrace, " %s", slcnames[pointer[i+SLC_FUNC]]);
E 21
I 21
		    if (SLC_NAME_OK(pointer[i+SLC_FUNC]))
			fprintf(NetTrace, " %s", SLC_NAME(pointer[i+SLC_FUNC]));
E 21
		    else
			fprintf(NetTrace, " %d", pointer[i+SLC_FUNC]);
		    switch (pointer[i+SLC_FLAGS]&SLC_LEVELBITS) {
		    case SLC_NOSUPPORT:
			fprintf(NetTrace, " NOSUPPORT"); break;
		    case SLC_CANTCHANGE:
			fprintf(NetTrace, " CANTCHANGE"); break;
		    case SLC_VARIABLE:
			fprintf(NetTrace, " VARIABLE"); break;
		    case SLC_DEFAULT:
			fprintf(NetTrace, " DEFAULT"); break;
		    }
		    fprintf(NetTrace, "%s%s%s",
			pointer[i+SLC_FLAGS]&SLC_ACK ? "|ACK" : "",
			pointer[i+SLC_FLAGS]&SLC_FLUSHIN ? "|FLUSHIN" : "",
			pointer[i+SLC_FLAGS]&SLC_FLUSHOUT ? "|FLUSHOUT" : "");
		    if (pointer[i+SLC_FLAGS]& ~(SLC_ACK|SLC_FLUSHIN|
						SLC_FLUSHOUT| SLC_LEVELBITS))
			fprintf(NetTrace, "(0x%x)", pointer[i+SLC_FLAGS]);
		    fprintf(NetTrace, " %d;", pointer[i+SLC_VALUE]);
I 19
		    if ((pointer[i+SLC_VALUE] == IAC) &&
			(pointer[i+SLC_VALUE+1] == IAC))
				i++;
E 19
		}
		for (; i < length; i++)
		    fprintf(NetTrace, " ?%d?", pointer[i]);
		break;

	    case LM_MODE:
		fprintf(NetTrace, "MODE ");
		if (length < 3) {
D 30
		    fprintf(NetTrace, "(no mode???)");
E 30
I 30
		    fprintf(NetTrace, "(no mode??\?)");
E 30
		    break;
		}
		{
D 19
		    char tbuf[32];
		    sprintf(tbuf, "%s%s%s",
E 19
I 19
		    char tbuf[64];
		    sprintf(tbuf, "%s%s%s%s%s",
E 19
			pointer[2]&MODE_EDIT ? "|EDIT" : "",
			pointer[2]&MODE_TRAPSIG ? "|TRAPSIG" : "",
I 19
			pointer[2]&MODE_SOFT_TAB ? "|SOFT_TAB" : "",
			pointer[2]&MODE_LIT_ECHO ? "|LIT_ECHO" : "",
E 19
			pointer[2]&MODE_ACK ? "|ACK" : "");
		    fprintf(NetTrace, "%s", tbuf[1] ? &tbuf[1] : "0");
		}
D 21
		if (pointer[2]&~(MODE_EDIT|MODE_TRAPSIG|MODE_ACK))
E 21
I 21
		if (pointer[2]&~(MODE_MASK))
E 21
		    fprintf(NetTrace, " (0x%x)", pointer[2]);
		for (i = 3; i < length; i++)
		    fprintf(NetTrace, " ?0x%x?", pointer[i]);
		break;
	    default:
		fprintf(NetTrace, "%d (unknown)", pointer[1]);
		for (i = 2; i < length; i++)
		    fprintf(NetTrace, " %d", pointer[i]);
	    }
	    break;

I 15
	case TELOPT_STATUS: {
	    register char *cp;
	    register int j, k;

	    fprintf(NetTrace, "STATUS");

	    switch (pointer[1]) {
	    default:
		if (pointer[1] == TELQUAL_SEND)
		    fprintf(NetTrace, " SEND");
		else
D 19
		    fprintf(NetTrace, " %d (unknown)");
E 19
I 19
		    fprintf(NetTrace, " %d (unknown)", pointer[1]);
E 19
		for (i = 2; i < length; i++)
		    fprintf(NetTrace, " ?%d?", pointer[i]);
		break;
	    case TELQUAL_IS:
I 21
		if (--want_status_response < 0)
		    want_status_response = 0;
E 21
		if (NetTrace == stdout)
		    fprintf(NetTrace, " IS\r\n");
		else
		    fprintf(NetTrace, " IS\n");

		for (i = 2; i < length; i++) {
		    switch(pointer[i]) {
		    case DO:	cp = "DO"; goto common2;
		    case DONT:	cp = "DONT"; goto common2;
		    case WILL:	cp = "WILL"; goto common2;
		    case WONT:	cp = "WONT"; goto common2;
		    common2:
			i++;
D 19
			if (TELOPT_OK(pointer[i]))
E 19
I 19
			if (TELOPT_OK((int)pointer[i]))
E 19
			    fprintf(NetTrace, " %s %s", cp, TELOPT(pointer[i]));
			else
			    fprintf(NetTrace, " %s %d", cp, pointer[i]);

			if (NetTrace == stdout)
			    fprintf(NetTrace, "\r\n");
			else
			    fprintf(NetTrace, "\n");
			break;

		    case SB:
			fprintf(NetTrace, " SB ");
			i++;
			j = k = i;
			while (j < length) {
			    if (pointer[j] == SE) {
				if (j+1 == length)
				    break;
				if (pointer[j+1] == SE)
				    j++;
				else
				    break;
			    }
			    pointer[k++] = pointer[j++];
			}
			printsub(0, &pointer[i], k - i);
			if (i < length) {
			    fprintf(NetTrace, " SE");
			    i = j;
			} else
			    i = j - 1;

			if (NetTrace == stdout)
			    fprintf(NetTrace, "\r\n");
			else
			    fprintf(NetTrace, "\n");

			break;
D 31
				
E 31
I 31

E 31
		    default:
			fprintf(NetTrace, " %d", pointer[i]);
			break;
		    }
		}
		break;
	    }
	    break;
	  }

I 19
	case TELOPT_XDISPLOC:
	    fprintf(NetTrace, "X-DISPLAY-LOCATION ");
	    switch (pointer[1]) {
	    case TELQUAL_IS:
		fprintf(NetTrace, "IS \"%.*s\"", length-2, (char *)pointer+2);
		break;
	    case TELQUAL_SEND:
		fprintf(NetTrace, "SEND");
		break;
	    default:
		fprintf(NetTrace, "- unknown qualifier %d (0x%x).",
				pointer[1], pointer[1]);
	    }
	    break;

D 30
	case TELOPT_ENVIRON:
	    fprintf(NetTrace, "ENVIRON ");
E 30
I 30
	case TELOPT_NEW_ENVIRON:
	    fprintf(NetTrace, "NEW-ENVIRON ");
#ifdef	OLD_ENVIRON
	    goto env_common1;
	case TELOPT_OLD_ENVIRON:
	    fprintf(NetTrace, "OLD-ENVIRON");
	env_common1:
#endif
E 30
	    switch (pointer[1]) {
	    case TELQUAL_IS:
		fprintf(NetTrace, "IS ");
		goto env_common;
	    case TELQUAL_SEND:
		fprintf(NetTrace, "SEND ");
		goto env_common;
	    case TELQUAL_INFO:
		fprintf(NetTrace, "INFO ");
	    env_common:
		{
		    register int noquote = 2;
I 26
D 30
#ifdef	ENV_HACK
		    extern int env_var, env_value;
E 30
I 30
#if defined(ENV_HACK) && defined(OLD_ENVIRON)
		    extern int old_env_var, old_env_value;
E 30
#endif
E 26
		    for (i = 2; i < length; i++ ) {
			switch (pointer[i]) {
D 30
			case ENV_VAR:
D 26
			    if (pointer[1] == TELQUAL_SEND)
				goto def_case;
E 26
I 26
#ifdef	ENV_HACK
			    if (env_var == ENV_VALUE)
				fprintf(NetTrace, "\" (VALUE) " + noquote);
			    else
#endif
E 26
			    fprintf(NetTrace, "\" VAR " + noquote);
E 30
I 30
			case NEW_ENV_VALUE:
#ifdef OLD_ENVIRON
		     /*	case NEW_ENV_OVAR: */
			    if (pointer[0] == TELOPT_OLD_ENVIRON) {
# ifdef	ENV_HACK
				if (old_env_var == OLD_ENV_VALUE)
				    fprintf(NetTrace, "\" (VALUE) " + noquote);
				else
# endif
				    fprintf(NetTrace, "\" VAR " + noquote);
			    } else
#endif /* OLD_ENVIRON */
				fprintf(NetTrace, "\" VALUE " + noquote);
E 30
			    noquote = 2;
			    break;

D 30
			case ENV_VALUE:
I 26
#ifdef	ENV_HACK
			    if (env_value == ENV_VAR)
				fprintf(NetTrace, "\" (VAR) " + noquote);
			    else
#endif
E 26
			    fprintf(NetTrace, "\" VALUE " + noquote);
E 30
I 30
			case NEW_ENV_VAR:
#ifdef OLD_ENVIRON
		     /* case OLD_ENV_VALUE: */
			    if (pointer[0] == TELOPT_OLD_ENVIRON) {
# ifdef	ENV_HACK
				if (old_env_value == OLD_ENV_VAR)
				    fprintf(NetTrace, "\" (VAR) " + noquote);
				else
# endif
				    fprintf(NetTrace, "\" VALUE " + noquote);
			    } else
#endif /* OLD_ENVIRON */
				fprintf(NetTrace, "\" VAR " + noquote);
E 30
			    noquote = 2;
			    break;

			case ENV_ESC:
			    fprintf(NetTrace, "\" ESC " + noquote);
I 24
			    noquote = 2;
			    break;

			case ENV_USERVAR:
D 26
			    if (pointer[1] == TELQUAL_SEND)
				goto def_case;
E 26
			    fprintf(NetTrace, "\" USERVAR " + noquote);
E 24
			    noquote = 2;
			    break;

			default:
			def_case:
			    if (isprint(pointer[i]) && pointer[i] != '"') {
				if (noquote) {
				    putc('"', NetTrace);
				    noquote = 0;
				}
				putc(pointer[i], NetTrace);
			    } else {
				fprintf(NetTrace, "\" %03o " + noquote,
							pointer[i]);
				noquote = 2;
			    }
			    break;
			}
		    }
		    if (!noquote)
			putc('"', NetTrace);
		    break;
		}
	    }
	    break;

E 19
E 15
E 14
	default:
D 14
	    fprintf(NetTrace, "Unknown option %d (0x%x)\n",
					pointer[0], pointer[0]);
E 14
I 14
D 21
	    fprintf(NetTrace, "Unknown option ");
	    for (i = 0; i < length; i++)
E 21
I 21
	    if (TELOPT_OK(pointer[0]))
		fprintf(NetTrace, "%s (unknown)", TELOPT(pointer[0]));
	    else
D 23
		fprintf(NetTrace, "%d (unknown)", pointer[i]);
E 23
I 23
		fprintf(NetTrace, "%d (unknown)", pointer[0]);
E 23
	    for (i = 1; i < length; i++)
E 21
		fprintf(NetTrace, " %d", pointer[i]);
	    break;
E 14
	}
I 14
D 15
	if (NetTrace == stdout)
	    fprintf(NetTrace, "\r\n");
	else
	    fprintf(NetTrace, "\n");
E 15
I 15
	if (direction) {
	    if (NetTrace == stdout)
		fprintf(NetTrace, "\r\n");
	    else
		fprintf(NetTrace, "\n");
	}
I 30
	if (NetTrace == stdout)
	    fflush(NetTrace);
E 30
E 15
E 14
    }
}
I 8

/* EmptyTerminal - called to make sure that the terminal buffer is empty.
 *			Note that we consider the buffer to run all the
 *			way to the kernel (thus the select).
 */

D 21
void
E 21
I 21
    void
E 21
EmptyTerminal()
{
#if	defined(unix)
    fd_set	o;

    FD_ZERO(&o);
#endif	/* defined(unix) */

    if (TTYBYTES() == 0) {
#if	defined(unix)
	FD_SET(tout, &o);
	(void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
			(struct timeval *) 0);	/* wait for TTLOWAT */
#endif	/* defined(unix) */
    } else {
	while (TTYBYTES()) {
D 19
	    ttyflush(0);
E 19
I 19
	    (void) ttyflush(0);
E 19
#if	defined(unix)
	    FD_SET(tout, &o);
	    (void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
				(struct timeval *) 0);	/* wait for TTLOWAT */
#endif	/* defined(unix) */
	}
    }
}

D 21
void
E 21
I 21
    void
E 21
SetForExit()
{
D 14
    setconnmode();
E 14
I 14
    setconnmode(0);
E 14
#if	defined(TN3270)
    if (In3270) {
	Finish3270();
    }
I 9
#else	/* defined(TN3270) */
    do {
D 19
	telrcv();			/* Process any incoming data */
E 19
I 19
	(void)telrcv();			/* Process any incoming data */
E 19
	EmptyTerminal();
    } while (ring_full_count(&netiring));	/* While there is any */
E 9
#endif	/* defined(TN3270) */
    setcommandmode();
    fflush(stdout);
    fflush(stderr);
#if	defined(TN3270)
    if (In3270) {
	StopScreen(1);
    }
#endif	/* defined(TN3270) */
D 14
    setconnmode();
E 14
I 14
    setconnmode(0);
E 14
    EmptyTerminal();			/* Flush the path to the tty */
    setcommandmode();
}

D 21
void
E 21
I 21
    void
E 21
Exit(returnCode)
D 21
int returnCode;
E 21
I 21
    int returnCode;
E 21
{
    SetForExit();
    exit(returnCode);
}

D 21
void
E 21
I 21
    void
E 21
ExitString(string, returnCode)
D 21
char *string;
int returnCode;
E 21
I 21
    char *string;
    int returnCode;
E 21
{
    SetForExit();
    fwrite(string, 1, strlen(string), stderr);
    exit(returnCode);
}
D 16

#if defined(MSDOS)
void
ExitPerror(string, returnCode)
char *string;
int returnCode;
{
    SetForExit();
    perror(string);
    exit(returnCode);
}
#endif /* defined(MSDOS) */
E 16
E 8
E 1
