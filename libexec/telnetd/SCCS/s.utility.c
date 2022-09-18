h49246
s 00015/00015/01151
d D 8.4 95/05/30 22:02:52 dab 16 15
c code cleanup, change b*() to mem*()
c Add setting up of LINEMODE environment variable.
e
s 00001/00001/01165
d D 8.3 95/03/23 07:56:30 dab 15 14
c Remove an unneeded "\r\n" from fatalperror()
c The fix is from Craig Leres <leres@ee.lbl.gov>
e
s 00025/00017/01141
d D 8.2 93/12/15 11:40:05 dab 14 13
c A bunch of bugfixes.
c Support for Solaris.
c new LOGIN_R option for systems that
c don't have "login -f".
c Support for the new ENVIRON option.
e
s 00002/00002/01156
d D 8.1 93/06/04 19:07:34 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00016/01142
d D 5.12 93/05/20 11:38:00 dab 12 11
c Several fixes.  The big one is that all of the
c code that was "#if defined(ENCRYPTION)" is now changed
c to "#ifdef ENCRYPTION", so that all the encryption code
c can be stripped out using unifdef.
c Other fixes:
c 	Add support for HP-UX (untested...)
c 	Simplification of the ENV_HACK stuff
c 	Add in UNICOS 8.0 secure system changes
c 	Clean up the option processing
c 	Fix up the usage() statement
e
s 00001/00005/01157
d D 5.11 93/04/05 16:48:21 dab 11 10
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00006/00002/01156
d D 5.10 93/01/19 12:47:18 dab 10 9
c Fix up the code that deals with the
c flowcontrol option to properly deal with the
c RESTART_ANY and RESTART_XON suboptions.
e
s 00021/00008/01137
d D 5.9 92/12/18 14:05:44 dab 9 8
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00026/00006/01119
d D 5.8 91/03/22 13:16:36 dab 8 7
c Upgrade to the latest & greatest authentication/encryption
e
s 00262/00097/00863
d D 5.7 91/03/01 01:35:17 dab 7 6
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
c Bug fixes and code cleanup
e
s 00006/00005/00954
d D 5.6 91/02/26 11:50:38 bostic 6 5
c ANSI fixes (one real bug!)
e
s 00008/00008/00951
d D 5.5 91/01/21 09:44:43 bostic 5 4
c delete get_date, just use strftime
e
s 00551/00002/00408
d D 5.4 90/06/28 13:06:23 borman 4 3
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00409
d D 5.3 90/06/01 15:56:43 bostic 3 2
c new copyright notice
e
s 00002/00003/00418
d D 5.2 90/05/28 12:37:58 bostic 2 1
c sys_errlist -> strerror(3)
e
s 00421/00000/00000
d D 5.1 89/09/01 15:17:55 borman 1 0
c New telnetd, with LINEMODE support
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 4

E 4
I 4
#define PRINTOPTIONS
E 4
#include "telnetd.h"

/*
 * utility functions performing io related tasks
 */

/*
 * ttloop
 *
 *	A small subroutine to flush the network output buffer, get some data
 * from the network, and pass it through the telnet state machine.  We
 * also flush the pty input buffer (by dropping its data) if it becomes
 * too full.
 */

D 7
void
E 7
I 7
    void
E 7
ttloop()
{
    void netflush();

I 4
D 7
#ifdef DIAGNOSTICS
    if (diagnostic & TD_REPORT) {
	sprintf(nfrontp, "td: ttloop\r\n");
	nfrontp += strlen(nfrontp);
    }
#endif /* DIAGNOSTICS */
E 7
I 7
    DIAG(TD_REPORT, {sprintf(nfrontp, "td: ttloop\r\n");
		     nfrontp += strlen(nfrontp);});
E 7
E 4
    if (nfrontp-nbackp) {
	netflush();
    }
    ncc = read(net, netibuf, sizeof netibuf);
    if (ncc < 0) {
	syslog(LOG_INFO, "ttloop:  read: %m\n");
	exit(1);
    } else if (ncc == 0) {
	syslog(LOG_INFO, "ttloop:  peer died: %m\n");
	exit(1);
    }
I 4
D 7
#ifdef DIAGNOSTICS
    if (diagnostic & TD_REPORT) {
	sprintf(nfrontp, "td: ttloop read %d chars\r\n", ncc);
	nfrontp += strlen(nfrontp);
    }
#endif /* DIAGNOSTICS */
E 7
I 7
    DIAG(TD_REPORT, {sprintf(nfrontp, "td: ttloop read %d chars\r\n", ncc);
		     nfrontp += strlen(nfrontp);});
E 7
E 4
    netip = netibuf;
    telrcv();			/* state machine */
    if (ncc > 0) {
	pfrontp = pbackp = ptyobuf;
	telrcv();
    }
}  /* end of ttloop */

/*
 * Check a descriptor to see if out of band data exists on it.
 */
I 7
    int
E 7
stilloob(s)
D 7
int	s;		/* socket number */
E 7
I 7
    int	s;		/* socket number */
E 7
{
    static struct timeval timeout = { 0 };
    fd_set	excepts;
    int value;

    do {
	FD_ZERO(&excepts);
	FD_SET(s, &excepts);
	value = select(s+1, (fd_set *)0, (fd_set *)0, &excepts, &timeout);
    } while ((value == -1) && (errno == EINTR));

    if (value < 0) {
	fatalperror(pty, "select");
    }
    if (FD_ISSET(s, &excepts)) {
	return 1;
    } else {
	return 0;
    }
}

I 7
	void
E 7
ptyflush()
{
	int n;

D 4
	if ((n = pfrontp - pbackp) > 0)
E 4
I 4
	if ((n = pfrontp - pbackp) > 0) {
D 7
#ifdef DIAGNOSTICS
		if (diagnostic & (TD_REPORT | TD_PTYDATA)) {
			sprintf(nfrontp, "td: ptyflush %d chars\r\n", n);
			nfrontp += strlen(nfrontp);
		}
		if (diagnostic & TD_PTYDATA) {
			printdata("pd", pbackp, n);
		}
#endif /* DIAGNOSTICS */
E 7
I 7
		DIAG((TD_REPORT | TD_PTYDATA),
			{ sprintf(nfrontp, "td: ptyflush %d chars\r\n", n);
			  nfrontp += strlen(nfrontp); });
		DIAG(TD_PTYDATA, printdata("pd", pbackp, n));
E 7
E 4
		n = write(pty, pbackp, n);
I 4
	}
E 4
D 7
	if (n < 0)
		return;
E 7
I 7
	if (n < 0) {
		if (errno == EWOULDBLOCK || errno == EINTR)
			return;
		cleanup(0);
	}
E 7
	pbackp += n;
	if (pbackp == pfrontp)
		pbackp = pfrontp = ptyobuf;
}

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
D 7
char *
E 7
I 7
    char *
E 7
nextitem(current)
D 7
char	*current;
E 7
I 7
    char	*current;
E 7
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
}  /* end of nextitem */


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
I 7
    void
E 7
netclear()
{
    register char *thisitem, *next;
    char *good;
#define	wewant(p)	((nfrontp > p) && ((*p&0xff) == IAC) && \
				((*(p+1)&0xff) != EC) && ((*(p+1)&0xff) != EL))

I 7
D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
    thisitem = nclearto > netobuf ? nclearto : netobuf;
D 12
#else
E 12
I 12
#else	/* ENCRYPTION */
E 12
E 7
    thisitem = netobuf;
I 7
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12
E 7

    while ((next = nextitem(thisitem)) <= nbackp) {
	thisitem = next;
    }

    /* Now, thisitem is first before/at boundary. */

I 7
D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
    good = nclearto > netobuf ? nclearto : netobuf;
D 12
#else
E 12
I 12
#else	/* ENCRYPTION */
E 12
E 7
    good = netobuf;	/* where the good bytes go */
I 7
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12
E 7

    while (nfrontp > thisitem) {
	if (wewant(thisitem)) {
	    int length;

	    next = thisitem;
	    do {
		next = nextitem(next);
	    } while (wewant(next) && (nfrontp > next));
	    length = next-thisitem;
D 16
	    bcopy(thisitem, good, length);
E 16
I 16
	    memmove(good, thisitem, length);
E 16
	    good += length;
	    thisitem = next;
	} else {
	    thisitem = nextitem(thisitem);
	}
    }

    nbackp = netobuf;
    nfrontp = good;		/* next byte to be sent */
    neturg = 0;
}  /* end of netclear */

/*
 *  netflush
 *		Send as much data as possible to the network,
 *	handling requests for urgent data.
 */
D 7
void
E 7
I 7
    void
E 7
netflush()
{
    int n;
    extern int not42;

    if ((n = nfrontp - nbackp) > 0) {
I 4
D 7
#ifdef DIAGNOSTICS
	if (diagnostic & TD_REPORT) {
	    sprintf(nfrontp, "td: netflush %d chars\r\n", n);
	    n += strlen(nfrontp);  /* get count first */
	    nfrontp += strlen(nfrontp);  /* then move pointer */
E 7
I 7
	DIAG(TD_REPORT,
	    { sprintf(nfrontp, "td: netflush %d chars\r\n", n);
	      n += strlen(nfrontp);  /* get count first */
	      nfrontp += strlen(nfrontp);  /* then move pointer */
	    });
D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
	if (encrypt_output) {
		char *s = nclearto ? nclearto : nbackp;
		if (nfrontp - s > 0) {
			(*encrypt_output)((unsigned char *)s, nfrontp-s);
			nclearto = nfrontp;
		}
E 7
	}
D 7
#endif /* DIAGNOSTICS */
E 7
I 7
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12
E 7
E 4
	/*
	 * if no urgent data, or if the other side appears to be an
	 * old 4.2 client (and thus unable to survive TCP urgent data),
	 * write the entire buffer in non-OOB mode.
	 */
	if ((neturg == 0) || (not42 == 0)) {
	    n = write(net, nbackp, n);	/* normal write */
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
		n = send(net, nbackp, n-1, 0);	/* send URGENT all by itself */
	    } else {
		n = send(net, nbackp, n, MSG_OOB);	/* URGENT data */
	    }
	}
    }
    if (n < 0) {
	if (errno == EWOULDBLOCK || errno == EINTR)
		return;
D 7
	cleanup();
E 7
I 7
	cleanup(0);
E 7
    }
    nbackp += n;
I 7
D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
    if (nbackp > nclearto)
	nclearto = 0;
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12
E 7
    if (nbackp >= neturg) {
	neturg = 0;
    }
    if (nbackp == nfrontp) {
	nbackp = nfrontp = netobuf;
I 7
D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
	nclearto = 0;
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12
E 7
    }
    return;
}  /* end of netflush */


/*
 * writenet
 *
 * Just a handy little function to write a bit of raw data to the net.
 * It will force a transmit of the buffer if necessary
 *
 * arguments
 *    ptr - A pointer to a character string to write
 *    len - How many bytes to write
 */
I 7
	void
E 7
writenet(ptr, len)
D 7
register char *ptr;
register int len;
E 7
I 7
	register unsigned char *ptr;
	register int len;
E 7
{
	/* flush buffer if no room for new data) */
	if ((&netobuf[BUFSIZ] - nfrontp) < len) {
		/* if this fails, don't worry, buffer is a little big */
		netflush();
	}

D 16
	bcopy(ptr, nfrontp, len);
E 16
I 16
	memmove(nfrontp, ptr, len);
E 16
	nfrontp += len;

}  /* end of writenet */


/*
 * miscellaneous functions doing a variety of little jobs follow ...
 */


I 7
	void
E 7
fatal(f, msg)
	int f;
	char *msg;
{
	char buf[BUFSIZ];

	(void) sprintf(buf, "telnetd: %s.\r\n", msg);
I 7
D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
	if (encrypt_output) {
		/*
		 * Better turn off encryption first....
		 * Hope it flushes...
		 */
		encrypt_send_end();
		netflush();
	}
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12
E 7
	(void) write(f, buf, (int)strlen(buf));
	sleep(1);	/*XXX*/
	exit(1);
}

I 7
	void
E 7
fatalperror(f, msg)
	int f;
	char *msg;
{
D 2
	char buf[BUFSIZ];
	extern char *sys_errlist[];
E 2
I 2
	char buf[BUFSIZ], *strerror();
E 2

D 2
	(void) sprintf(buf, "%s: %s\r\n", msg, sys_errlist[errno]);
E 2
I 2
D 15
	(void) sprintf(buf, "%s: %s\r\n", msg, strerror(errno));
E 15
I 15
	(void) sprintf(buf, "%s: %s", msg, strerror(errno));
E 15
E 2
	fatal(f, buf);
}

char editedhost[32];

I 7
	void
E 7
edithost(pat, host)
	register char *pat;
	register char *host;
{
	register char *res = editedhost;
	char *strncpy();

	if (!pat)
		pat = "";
	while (*pat) {
		switch (*pat) {

		case '#':
			if (*host)
				host++;
			break;

		case '@':
			if (*host)
				*res++ = *host++;
			break;

		default:
			*res++ = *pat;
			break;
		}
		if (res == &editedhost[sizeof editedhost - 1]) {
			*res = '\0';
			return;
		}
		pat++;
	}
	if (*host)
		(void) strncpy(res, host,
				sizeof editedhost - (res - editedhost) -1);
	else
		*res = '\0';
	editedhost[sizeof editedhost - 1] = '\0';
}

static char *putlocation;

I 7
	void
E 7
putstr(s)
D 7
register char *s;
E 7
I 7
	register char *s;
E 7
{

	while (*s)
		putchr(*s++);
}

I 7
	void
E 7
putchr(cc)
I 7
	int cc;
E 7
{
	*putlocation++ = cc;
}

I 7
/*
 * This is split on two lines so that SCCS will not see the M
 * between two % signs and expand it...
 */
static char fmtstr[] = { "%l:%M\
%P on %A, %d %B %Y" };

	void
E 7
putf(cp, where)
D 7
register char *cp;
char *where;
E 7
I 7
	register char *cp;
	char *where;
E 7
{
I 7
	char *slash;
E 7
D 5
	char *slash;
#ifndef	NO_GETTYTAB
	char datebuffer[60];
#endif	/* NO_GETTYTAB */
E 5
I 5
	time_t t;
D 7
	char *fmt, *slash, db[100];
E 7
I 7
	char db[100];
I 14
#ifdef	STREAMSPTY
D 16
	extern char *index();
E 16
I 16
	extern char *strchr();
E 16
#else
E 14
E 7
E 5
D 16
	extern char *rindex();
E 16
I 16
	extern char *strrchr();
E 16
I 14
#endif
E 14

	putlocation = where;

	while (*cp) {
		if (*cp != '%') {
			putchr(*cp++);
			continue;
		}
		switch (*++cp) {

		case 't':
I 9
#ifdef	STREAMSPTY
			/* names are like /dev/pts/2 -- we want pts/2 */
D 16
			slash = index(line+1, '/');
E 16
I 16
			slash = strchr(line+1, '/');
E 16
#else
E 9
D 16
			slash = rindex(line, '/');
E 16
I 16
			slash = strrchr(line, '/');
E 16
I 9
#endif
E 9
			if (slash == (char *) 0)
				putstr(line);
			else
				putstr(&slash[1]);
			break;

		case 'h':
			putstr(editedhost);
			break;

D 5
#ifndef	NO_GETTYTAB
E 5
D 6
		case 'd':
E 6
I 6
D 7
		case 'd': {
			char fmt[] = "%l:% %P on %A, %d %B %Y";

			fmt[4] = 'M';		/* I *hate* SCCS... */
E 7
I 7
		case 'd':
E 7
E 6
D 5
			get_date(datebuffer);
			putstr(datebuffer);
E 5
I 5
			(void)time(&t);
D 6
						/* SCCS *likes* %M%... */
			fmt = "%l:% %P on %A, %d %B %Y";
			fmt[4] = 'M';
			(void)strftime(db, sizeof(db), fmt, &t);
E 6
I 6
D 7
			(void)strftime(db, sizeof(db), fmt, localtime(&t));
E 7
I 7
			(void)strftime(db, sizeof(db), fmtstr, localtime(&t));
E 7
E 6
			putstr(db);
E 5
			break;
I 6
D 7
		}
E 7
E 6
D 5
#endif	/* NO_GETTYTAB */
E 5

		case '%':
			putchr('%');
			break;
		}
		cp++;
	}
}

D 7
/*ARGSUSED*/
#ifdef	NO_GETTYTAB
getent(cp, name)
char *cp, *name;
{
	return(0);
}

/*ARGSUSED*/
char *
getstr(cp, cpp)
char *cp, **cpp;
{
	return(0);
}
#endif	/* NO_GETTYTAB */
I 4

E 7
#ifdef DIAGNOSTICS
/*
 * Print telnet options and commands in plain text, if possible.
 */
D 7
void
E 7
I 7
	void
E 7
printoption(fmt, option)
D 7
register char *fmt;
register int option;
E 7
I 7
	register char *fmt;
	register int option;
E 7
{
	if (TELOPT_OK(option))
		sprintf(nfrontp, "%s %s\r\n", fmt, TELOPT(option));
	else if (TELCMD_OK(option))
		sprintf(nfrontp, "%s %s\r\n", fmt, TELCMD(option));
	else
		sprintf(nfrontp, "%s %d\r\n", fmt, option);
	nfrontp += strlen(nfrontp);
	return;
}

D 7
char *slcnames[] = { SLC_NAMES };

void
printsub(dirp, pointer, length)
char	*dirp;
unsigned char	*pointer;	/* where suboption data sits */
int	length;			/* length of suboption data */
E 7
I 7
    void
printsub(direction, pointer, length)
    char		direction;	/* '<' or '>' */
    unsigned char	*pointer;	/* where suboption data sits */
    int			length;		/* length of suboption data */
E 7
{
    register int i;
I 7
D 8
    char buf[256];
E 8
I 8
    char buf[512];
E 8
E 7

D 7
	if (dirp) {
	    sprintf(nfrontp, "%s suboption ", dirp);
E 7
I 7
D 16
        if (!(diagnostic & TD_OPTIONS))
E 16
I 16
	if (!(diagnostic & TD_OPTIONS))
E 16
		return;

	if (direction) {
	    sprintf(nfrontp, "td: %s suboption ",
					direction == '<' ? "recv" : "send");
E 7
	    nfrontp += strlen(nfrontp);
	    if (length >= 3) {
		register int j;

		i = pointer[length-2];
		j = pointer[length-1];

		if (i != IAC || j != SE) {
		    sprintf(nfrontp, "(terminated by ");
		    nfrontp += strlen(nfrontp);
		    if (TELOPT_OK(i))
			sprintf(nfrontp, "%s ", TELOPT(i));
		    else if (TELCMD_OK(i))
			sprintf(nfrontp, "%s ", TELCMD(i));
		    else
			sprintf(nfrontp, "%d ", i);
		    nfrontp += strlen(nfrontp);
		    if (TELOPT_OK(j))
			sprintf(nfrontp, "%s", TELOPT(j));
		    else if (TELCMD_OK(j))
			sprintf(nfrontp, "%s", TELCMD(j));
		    else
			sprintf(nfrontp, "%d", j);
		    nfrontp += strlen(nfrontp);
		    sprintf(nfrontp, ", not IAC SE!) ");
		    nfrontp += strlen(nfrontp);
		}
	    }
	    length -= 2;
	}
	if (length < 1) {
D 14
	    sprintf(nfrontp, "(Empty suboption???)");
E 14
I 14
	    sprintf(nfrontp, "(Empty suboption??\?)");
E 14
	    nfrontp += strlen(nfrontp);
	    return;
	}
	switch (pointer[0]) {
	case TELOPT_TTYPE:
	    sprintf(nfrontp, "TERMINAL-TYPE ");
	    nfrontp += strlen(nfrontp);
	    switch (pointer[1]) {
	    case TELQUAL_IS:
		sprintf(nfrontp, "IS \"%.*s\"", length-2, (char *)pointer+2);
		break;
	    case TELQUAL_SEND:
		sprintf(nfrontp, "SEND");
		break;
	    default:
		sprintf(nfrontp,
				"- unknown qualifier %d (0x%x).",
				pointer[1], pointer[1]);
	    }
	    nfrontp += strlen(nfrontp);
	    break;
	case TELOPT_TSPEED:
	    sprintf(nfrontp, "TERMINAL-SPEED");
	    nfrontp += strlen(nfrontp);
	    if (length < 2) {
D 14
		sprintf(nfrontp, " (empty suboption???)");
E 14
I 14
		sprintf(nfrontp, " (empty suboption??\?)");
E 14
		nfrontp += strlen(nfrontp);
		break;
	    }
	    switch (pointer[1]) {
	    case TELQUAL_IS:
		sprintf(nfrontp, " IS %.*s", length-2, (char *)pointer+2);
		nfrontp += strlen(nfrontp);
		break;
	    default:
		if (pointer[1] == 1)
		    sprintf(nfrontp, " SEND");
		else
		    sprintf(nfrontp, " %d (unknown)", pointer[1]);
		nfrontp += strlen(nfrontp);
		for (i = 2; i < length; i++) {
		    sprintf(nfrontp, " ?%d?", pointer[i]);
		    nfrontp += strlen(nfrontp);
		}
		break;
	    }
	    break;

	case TELOPT_LFLOW:
	    sprintf(nfrontp, "TOGGLE-FLOW-CONTROL");
	    nfrontp += strlen(nfrontp);
	    if (length < 2) {
D 14
		sprintf(nfrontp, " (empty suboption???)");
E 14
I 14
		sprintf(nfrontp, " (empty suboption??\?)");
E 14
		nfrontp += strlen(nfrontp);
		break;
	    }
	    switch (pointer[1]) {
D 10
	    case 0:
E 10
I 10
	    case LFLOW_OFF:
E 10
		sprintf(nfrontp, " OFF"); break;
D 10
	    case 1:
E 10
I 10
	    case LFLOW_ON:
E 10
		sprintf(nfrontp, " ON"); break;
I 10
	    case LFLOW_RESTART_ANY:
		sprintf(nfrontp, " RESTART-ANY"); break;
	    case LFLOW_RESTART_XON:
		sprintf(nfrontp, " RESTART-XON"); break;
E 10
	    default:
		sprintf(nfrontp, " %d (unknown)", pointer[1]);
	    }
	    nfrontp += strlen(nfrontp);
	    for (i = 2; i < length; i++) {
		sprintf(nfrontp, " ?%d?", pointer[i]);
		nfrontp += strlen(nfrontp);
	    }
	    break;

	case TELOPT_NAWS:
	    sprintf(nfrontp, "NAWS");
	    nfrontp += strlen(nfrontp);
	    if (length < 2) {
D 14
		sprintf(nfrontp, " (empty suboption???)");
E 14
I 14
		sprintf(nfrontp, " (empty suboption??\?)");
E 14
		nfrontp += strlen(nfrontp);
		break;
	    }
	    if (length == 2) {
		sprintf(nfrontp, " ?%d?", pointer[1]);
		nfrontp += strlen(nfrontp);
		break;
	    }
	    sprintf(nfrontp, " %d %d (%d)",
		pointer[1], pointer[2],
		(int)((((unsigned int)pointer[1])<<8)|((unsigned int)pointer[2])));
	    nfrontp += strlen(nfrontp);
	    if (length == 4) {
		sprintf(nfrontp, " ?%d?", pointer[3]);
		nfrontp += strlen(nfrontp);
		break;
	    }
	    sprintf(nfrontp, " %d %d (%d)",
		pointer[3], pointer[4],
		(int)((((unsigned int)pointer[3])<<8)|((unsigned int)pointer[4])));
	    nfrontp += strlen(nfrontp);
	    for (i = 5; i < length; i++) {
		sprintf(nfrontp, " ?%d?", pointer[i]);
		nfrontp += strlen(nfrontp);
	    }
	    break;

	case TELOPT_LINEMODE:
	    sprintf(nfrontp, "LINEMODE ");
	    nfrontp += strlen(nfrontp);
	    if (length < 2) {
D 14
		sprintf(nfrontp, " (empty suboption???)");
E 14
I 14
		sprintf(nfrontp, " (empty suboption??\?)");
E 14
		nfrontp += strlen(nfrontp);
		break;
	    }
	    switch (pointer[1]) {
	    case WILL:
		sprintf(nfrontp, "WILL ");
		goto common;
	    case WONT:
		sprintf(nfrontp, "WONT ");
		goto common;
	    case DO:
		sprintf(nfrontp, "DO ");
		goto common;
	    case DONT:
		sprintf(nfrontp, "DONT ");
	    common:
		nfrontp += strlen(nfrontp);
		if (length < 3) {
D 14
		    sprintf(nfrontp, "(no option???)");
E 14
I 14
		    sprintf(nfrontp, "(no option??\?)");
E 14
		    nfrontp += strlen(nfrontp);
		    break;
		}
		switch (pointer[2]) {
		case LM_FORWARDMASK:
		    sprintf(nfrontp, "Forward Mask");
		    nfrontp += strlen(nfrontp);
		    for (i = 3; i < length; i++) {
			sprintf(nfrontp, " %x", pointer[i]);
			nfrontp += strlen(nfrontp);
		    }
		    break;
		default:
		    sprintf(nfrontp, "%d (unknown)", pointer[2]);
		    nfrontp += strlen(nfrontp);
		    for (i = 3; i < length; i++) {
			sprintf(nfrontp, " %d", pointer[i]);
			nfrontp += strlen(nfrontp);
		    }
		    break;
		}
		break;
D 16
		
E 16
I 16

E 16
	    case LM_SLC:
		sprintf(nfrontp, "SLC");
		nfrontp += strlen(nfrontp);
		for (i = 2; i < length - 2; i += 3) {
D 7
		    if (pointer[i+SLC_FUNC] <= NSLC)
			sprintf(nfrontp, " %s", slcnames[pointer[i+SLC_FUNC]]);
E 7
I 7
		    if (SLC_NAME_OK(pointer[i+SLC_FUNC]))
			sprintf(nfrontp, " %s", SLC_NAME(pointer[i+SLC_FUNC]));
E 7
		    else
			sprintf(nfrontp, " %d", pointer[i+SLC_FUNC]);
		    nfrontp += strlen(nfrontp);
		    switch (pointer[i+SLC_FLAGS]&SLC_LEVELBITS) {
		    case SLC_NOSUPPORT:
			sprintf(nfrontp, " NOSUPPORT"); break;
		    case SLC_CANTCHANGE:
			sprintf(nfrontp, " CANTCHANGE"); break;
		    case SLC_VARIABLE:
			sprintf(nfrontp, " VARIABLE"); break;
		    case SLC_DEFAULT:
			sprintf(nfrontp, " DEFAULT"); break;
		    }
		    nfrontp += strlen(nfrontp);
		    sprintf(nfrontp, "%s%s%s",
			pointer[i+SLC_FLAGS]&SLC_ACK ? "|ACK" : "",
			pointer[i+SLC_FLAGS]&SLC_FLUSHIN ? "|FLUSHIN" : "",
			pointer[i+SLC_FLAGS]&SLC_FLUSHOUT ? "|FLUSHOUT" : "");
		    nfrontp += strlen(nfrontp);
		    if (pointer[i+SLC_FLAGS]& ~(SLC_ACK|SLC_FLUSHIN|
						SLC_FLUSHOUT| SLC_LEVELBITS)) {
			sprintf(nfrontp, "(0x%x)", pointer[i+SLC_FLAGS]);
			nfrontp += strlen(nfrontp);
		    }
		    sprintf(nfrontp, " %d;", pointer[i+SLC_VALUE]);
		    nfrontp += strlen(nfrontp);
		    if ((pointer[i+SLC_VALUE] == IAC) &&
			(pointer[i+SLC_VALUE+1] == IAC))
				i++;
		}
		for (; i < length; i++) {
		    sprintf(nfrontp, " ?%d?", pointer[i]);
		    nfrontp += strlen(nfrontp);
		}
		break;

	    case LM_MODE:
		sprintf(nfrontp, "MODE ");
		nfrontp += strlen(nfrontp);
		if (length < 3) {
D 14
		    sprintf(nfrontp, "(no mode???)");
E 14
I 14
		    sprintf(nfrontp, "(no mode??\?)");
E 14
		    nfrontp += strlen(nfrontp);
		    break;
		}
		{
		    char tbuf[32];
		    sprintf(tbuf, "%s%s%s%s%s",
			pointer[2]&MODE_EDIT ? "|EDIT" : "",
			pointer[2]&MODE_TRAPSIG ? "|TRAPSIG" : "",
			pointer[2]&MODE_SOFT_TAB ? "|SOFT_TAB" : "",
			pointer[2]&MODE_LIT_ECHO ? "|LIT_ECHO" : "",
			pointer[2]&MODE_ACK ? "|ACK" : "");
		    sprintf(nfrontp, "%s", tbuf[1] ? &tbuf[1] : "0");
		    nfrontp += strlen(nfrontp);
		}
		if (pointer[2]&~(MODE_EDIT|MODE_TRAPSIG|MODE_ACK)) {
		    sprintf(nfrontp, " (0x%x)", pointer[2]);
		    nfrontp += strlen(nfrontp);
		}
		for (i = 3; i < length; i++) {
		    sprintf(nfrontp, " ?0x%x?", pointer[i]);
		    nfrontp += strlen(nfrontp);
		}
		break;
	    default:
		sprintf(nfrontp, "%d (unknown)", pointer[1]);
		nfrontp += strlen(nfrontp);
		for (i = 2; i < length; i++) {
		    sprintf(nfrontp, " %d", pointer[i]);
		    nfrontp += strlen(nfrontp);
		}
	    }
	    break;

	case TELOPT_STATUS: {
	    register char *cp;
	    register int j, k;

	    sprintf(nfrontp, "STATUS");
	    nfrontp += strlen(nfrontp);

	    switch (pointer[1]) {
	    default:
		if (pointer[1] == TELQUAL_SEND)
		    sprintf(nfrontp, " SEND");
		else
		    sprintf(nfrontp, " %d (unknown)", pointer[1]);
		nfrontp += strlen(nfrontp);
		for (i = 2; i < length; i++) {
		    sprintf(nfrontp, " ?%d?", pointer[i]);
		    nfrontp += strlen(nfrontp);
		}
		break;
	    case TELQUAL_IS:
		sprintf(nfrontp, " IS\r\n");
		nfrontp += strlen(nfrontp);

		for (i = 2; i < length; i++) {
		    switch(pointer[i]) {
		    case DO:	cp = "DO"; goto common2;
		    case DONT:	cp = "DONT"; goto common2;
		    case WILL:	cp = "WILL"; goto common2;
		    case WONT:	cp = "WONT"; goto common2;
		    common2:
			i++;
D 11
			if (TELOPT_OK((int)pointer[i]))
E 11
I 11
			if (TELOPT_OK(pointer[i]))
E 11
			    sprintf(nfrontp, " %s %s", cp, TELOPT(pointer[i]));
			else
			    sprintf(nfrontp, " %s %d", cp, pointer[i]);
			nfrontp += strlen(nfrontp);

			sprintf(nfrontp, "\r\n");
			nfrontp += strlen(nfrontp);
			break;

		    case SB:
			sprintf(nfrontp, " SB ");
			nfrontp += strlen(nfrontp);
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
			    sprintf(nfrontp, " SE");
			    nfrontp += strlen(nfrontp);
			    i = j;
			} else
			    i = j - 1;

			sprintf(nfrontp, "\r\n");
			nfrontp += strlen(nfrontp);

			break;
D 16
				
E 16
I 16

E 16
		    default:
			sprintf(nfrontp, " %d", pointer[i]);
			nfrontp += strlen(nfrontp);
			break;
		    }
		}
		break;
	    }
	    break;
	  }

	case TELOPT_XDISPLOC:
	    sprintf(nfrontp, "X-DISPLAY-LOCATION ");
	    nfrontp += strlen(nfrontp);
	    switch (pointer[1]) {
	    case TELQUAL_IS:
		sprintf(nfrontp, "IS \"%.*s\"", length-2, (char *)pointer+2);
		break;
	    case TELQUAL_SEND:
		sprintf(nfrontp, "SEND");
		break;
	    default:
		sprintf(nfrontp, "- unknown qualifier %d (0x%x).",
				pointer[1], pointer[1]);
	    }
	    nfrontp += strlen(nfrontp);
	    break;

D 14
	case TELOPT_ENVIRON:
	    sprintf(nfrontp, "ENVIRON ");
E 14
I 14
	case TELOPT_NEW_ENVIRON:
	    sprintf(nfrontp, "NEW-ENVIRON ");
	    goto env_common1;
	case TELOPT_OLD_ENVIRON:
	    sprintf(nfrontp, "OLD-ENVIRON");
	env_common1:
E 14
	    nfrontp += strlen(nfrontp);
	    switch (pointer[1]) {
	    case TELQUAL_IS:
		sprintf(nfrontp, "IS ");
		goto env_common;
	    case TELQUAL_SEND:
		sprintf(nfrontp, "SEND ");
		goto env_common;
	    case TELQUAL_INFO:
		sprintf(nfrontp, "INFO ");
	    env_common:
D 14
	    nfrontp += strlen(nfrontp);
E 14
I 14
		nfrontp += strlen(nfrontp);
E 14
		{
		    register int noquote = 2;
		    for (i = 2; i < length; i++ ) {
			switch (pointer[i]) {
D 14
			case ENV_VAR:
E 14
I 14
			case NEW_ENV_VAR:
E 14
D 11
			    if (pointer[1] == TELQUAL_SEND)
				goto def_case;
E 11
			    sprintf(nfrontp, "\" VAR " + noquote);
			    nfrontp += strlen(nfrontp);
			    noquote = 2;
			    break;

D 14
			case ENV_VALUE:
E 14
I 14
			case NEW_ENV_VALUE:
E 14
			    sprintf(nfrontp, "\" VALUE " + noquote);
			    nfrontp += strlen(nfrontp);
			    noquote = 2;
			    break;

			case ENV_ESC:
			    sprintf(nfrontp, "\" ESC " + noquote);
			    nfrontp += strlen(nfrontp);
			    noquote = 2;
			    break;

I 9
			case ENV_USERVAR:
D 11
			    if (pointer[1] == TELQUAL_SEND)
				goto def_case;
E 11
			    sprintf(nfrontp, "\" USERVAR " + noquote);
			    nfrontp += strlen(nfrontp);
			    noquote = 2;
			    break;

E 9
			default:
			def_case:
			    if (isprint(pointer[i]) && pointer[i] != '"') {
				if (noquote) {
				    *nfrontp++ = '"';
				    noquote = 0;
				}
				*nfrontp++ = pointer[i];
			    } else {
				sprintf(nfrontp, "\" %03o " + noquote,
							pointer[i]);
				nfrontp += strlen(nfrontp);
				noquote = 2;
			    }
			    break;
			}
		    }
		    if (!noquote)
			*nfrontp++ = '"';
		    break;
		}
	    }
	    break;

I 7
D 9
#if	defined(AUTHENTICATE)
E 9
I 9
#if	defined(AUTHENTICATION)
E 9
	case TELOPT_AUTHENTICATION:
	    sprintf(nfrontp, "AUTHENTICATION");
	    nfrontp += strlen(nfrontp);
D 16
	
E 16
I 16

E 16
	    if (length < 2) {
D 14
		sprintf(nfrontp, " (empty suboption???)");
E 14
I 14
		sprintf(nfrontp, " (empty suboption??\?)");
E 14
		nfrontp += strlen(nfrontp);
		break;
	    }
	    switch (pointer[1]) {
	    case TELQUAL_REPLY:
	    case TELQUAL_IS:
		sprintf(nfrontp, " %s ", (pointer[1] == TELQUAL_IS) ?
							"IS" : "REPLY");
		nfrontp += strlen(nfrontp);
		if (AUTHTYPE_NAME_OK(pointer[2]))
		    sprintf(nfrontp, "%s ", AUTHTYPE_NAME(pointer[2]));
		else
		    sprintf(nfrontp, "%d ", pointer[2]);
		nfrontp += strlen(nfrontp);
		if (length < 3) {
D 14
		    sprintf(nfrontp, "(partial suboption???)");
E 14
I 14
		    sprintf(nfrontp, "(partial suboption??\?)");
E 14
		    nfrontp += strlen(nfrontp);
		    break;
		}
		sprintf(nfrontp, "%s|%s",
D 8
			(pointer[3] & AUTH_WHO_MASK == AUTH_WHO_CLIENT) ?
E 8
I 8
			((pointer[3] & AUTH_WHO_MASK) == AUTH_WHO_CLIENT) ?
E 8
			"CLIENT" : "SERVER",
D 8
			(pointer[3] & AUTH_HOW_MASK == AUTH_HOW_MUTUAL) ?
E 8
I 8
			((pointer[3] & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) ?
E 8
			"MUTUAL" : "ONE-WAY");
		nfrontp += strlen(nfrontp);

		auth_printsub(&pointer[1], length - 1, buf, sizeof(buf));
		sprintf(nfrontp, "%s", buf);
		nfrontp += strlen(nfrontp);
		break;

	    case TELQUAL_SEND:
		i = 2;
		sprintf(nfrontp, " SEND ");
		nfrontp += strlen(nfrontp);
		while (i < length) {
		    if (AUTHTYPE_NAME_OK(pointer[i]))
			sprintf(nfrontp, "%s ", AUTHTYPE_NAME(pointer[i]));
		    else
			sprintf(nfrontp, "%d ", pointer[i]);
		    nfrontp += strlen(nfrontp);
		    if (++i >= length) {
D 14
			sprintf(nfrontp, "(partial suboption???)");
E 14
I 14
			sprintf(nfrontp, "(partial suboption??\?)");
E 14
			nfrontp += strlen(nfrontp);
			break;
		    }
		    sprintf(nfrontp, "%s|%s ",
D 8
			(pointer[i] & AUTH_WHO_MASK == AUTH_WHO_CLIENT) ?
E 8
I 8
			((pointer[i] & AUTH_WHO_MASK) == AUTH_WHO_CLIENT) ?
E 8
							"CLIENT" : "SERVER",
D 8
			(pointer[i] & AUTH_HOW_MASK == AUTH_HOW_MUTUAL) ?
E 8
I 8
			((pointer[i] & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) ?
E 8
							"MUTUAL" : "ONE-WAY");
		    nfrontp += strlen(nfrontp);
		    ++i;
		}
		break;

I 8
	    case TELQUAL_NAME:
		i = 2;
		sprintf(nfrontp, " NAME \"");
		nfrontp += strlen(nfrontp);
		while (i < length)
		    *nfrontp += pointer[i++];
		*nfrontp += '"';
		break;

E 8
	    default:
		    for (i = 2; i < length; i++) {
			sprintf(nfrontp, " ?%d?", pointer[i]);
			nfrontp += strlen(nfrontp);
		    }
		    break;
	    }
	    break;
#endif

D 9
#if	defined(ENCRYPT)
E 9
I 9
D 12
#if	defined(ENCRYPTION)
E 12
I 12
#ifdef	ENCRYPTION
E 12
E 9
	case TELOPT_ENCRYPT:
	    sprintf(nfrontp, "ENCRYPT");
	    nfrontp += strlen(nfrontp);
	    if (length < 2) {
D 14
		sprintf(nfrontp, " (empty suboption???)");
E 14
I 14
		sprintf(nfrontp, " (empty suboption??\?)");
E 14
		nfrontp += strlen(nfrontp);
		break;
	    }
	    switch (pointer[1]) {
	    case ENCRYPT_START:
		sprintf(nfrontp, " START");
		nfrontp += strlen(nfrontp);
		break;

	    case ENCRYPT_END:
		sprintf(nfrontp, " END");
		nfrontp += strlen(nfrontp);
		break;

	    case ENCRYPT_REQSTART:
		sprintf(nfrontp, " REQUEST-START");
		nfrontp += strlen(nfrontp);
		break;

	    case ENCRYPT_REQEND:
		sprintf(nfrontp, " REQUEST-END");
		nfrontp += strlen(nfrontp);
		break;

	    case ENCRYPT_IS:
	    case ENCRYPT_REPLY:
		sprintf(nfrontp, " %s ", (pointer[1] == ENCRYPT_IS) ?
							"IS" : "REPLY");
		nfrontp += strlen(nfrontp);
		if (length < 3) {
D 14
		    sprintf(nfrontp, " (partial suboption???)");
E 14
I 14
		    sprintf(nfrontp, " (partial suboption??\?)");
E 14
		    nfrontp += strlen(nfrontp);
		    break;
		}
		if (ENCTYPE_NAME_OK(pointer[2]))
		    sprintf(nfrontp, "%s ", ENCTYPE_NAME(pointer[2]));
		else
		    sprintf(nfrontp, " %d (unknown)", pointer[2]);
		nfrontp += strlen(nfrontp);

		encrypt_printsub(&pointer[1], length - 1, buf, sizeof(buf));
		sprintf(nfrontp, "%s", buf);
		nfrontp += strlen(nfrontp);
		break;

	    case ENCRYPT_SUPPORT:
		i = 2;
		sprintf(nfrontp, " SUPPORT ");
		nfrontp += strlen(nfrontp);
		while (i < length) {
		    if (ENCTYPE_NAME_OK(pointer[i]))
			sprintf(nfrontp, "%s ", ENCTYPE_NAME(pointer[i]));
		    else
			sprintf(nfrontp, "%d ", pointer[i]);
		    nfrontp += strlen(nfrontp);
		    i++;
		}
		break;

I 8
	    case ENCRYPT_ENC_KEYID:
		sprintf(nfrontp, " ENC_KEYID", pointer[1]);
		nfrontp += strlen(nfrontp);
		goto encommon;

	    case ENCRYPT_DEC_KEYID:
		sprintf(nfrontp, " DEC_KEYID", pointer[1]);
		nfrontp += strlen(nfrontp);
		goto encommon;

E 8
	    default:
D 8
		sprintf(nfrontp, "%d (unknown)", pointer[1]);
E 8
I 8
		sprintf(nfrontp, " %d (unknown)", pointer[1]);
E 8
		nfrontp += strlen(nfrontp);
I 8
	    encommon:
E 8
		for (i = 2; i < length; i++) {
		    sprintf(nfrontp, " %d", pointer[i]);
		    nfrontp += strlen(nfrontp);
		}
		break;
	    }
	    break;
D 12
#endif
E 12
I 12
#endif	/* ENCRYPTION */
E 12

E 7
	default:
D 7
	    sprintf(nfrontp, "Unknown option ");
E 7
I 7
	    if (TELOPT_OK(pointer[0]))
D 16
	        sprintf(nfrontp, "%s (unknown)", TELOPT(pointer[0]));
E 16
I 16
		sprintf(nfrontp, "%s (unknown)", TELOPT(pointer[0]));
E 16
	    else
D 16
	        sprintf(nfrontp, "%d (unknown)", pointer[i]);
E 16
I 16
		sprintf(nfrontp, "%d (unknown)", pointer[i]);
E 16
E 7
	    nfrontp += strlen(nfrontp);
D 7
	    for (i = 0; i < length; i++) {
E 7
I 7
	    for (i = 1; i < length; i++) {
E 7
		sprintf(nfrontp, " %d", pointer[i]);
		nfrontp += strlen(nfrontp);
	    }
	    break;
	}
	sprintf(nfrontp, "\r\n");
	nfrontp += strlen(nfrontp);
}

/*
 * Dump a data buffer in hex and ascii to the output data stream.
 */
D 7
void
E 7
I 7
	void
E 7
printdata(tag, ptr, cnt)
D 7
register char *tag;
register char *ptr;
register int cnt;
E 7
I 7
	register char *tag;
	register char *ptr;
	register int cnt;
E 7
{
D 7
register int i;
char xbuf[30];
E 7
I 7
	register int i;
	char xbuf[30];
E 7

	while (cnt) {
		/* flush net output buffer if no room for new data) */
		if ((&netobuf[BUFSIZ] - nfrontp) < 80) {
			netflush();
		}

		/* add a line of output */
		sprintf(nfrontp, "%s: ", tag);
		nfrontp += strlen(nfrontp);
		for (i = 0; i < 20 && cnt; i++) {
			sprintf(nfrontp, "%02x", *ptr);
D 16
			nfrontp += strlen(nfrontp); 
E 16
I 16
			nfrontp += strlen(nfrontp);
E 16
			if (isprint(*ptr)) {
				xbuf[i] = *ptr;
			} else {
				xbuf[i] = '.';
			}
D 16
			if (i % 2) { 
E 16
I 16
			if (i % 2) {
E 16
				*nfrontp = ' ';
				nfrontp++;
			}
			cnt--;
			ptr++;
		}
		xbuf[i] = '\0';
		sprintf(nfrontp, " %s\r\n", xbuf );
		nfrontp += strlen(nfrontp);
D 16
	} 
E 16
I 16
	}
E 16
}
D 7

E 7
#endif /* DIAGNOSTICS */
D 7

#ifdef	NO_STRERROR
char *
strerror(errno)
{
	extern char *sys_errlist[];

	return(sys_errlist[errno]);
}
#endif
E 7
E 4
E 1
