h44444
s 00002/00002/00195
d D 8.1 93/06/07 11:30:05 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00194
d D 6.17 93/06/07 11:29:52 bostic 34 32
c index -> strcghr
e
s 00002/00002/00195
d R 8.1 93/06/04 12:51:21 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00046/00015/00151
d D 6.16 93/06/02 17:04:55 karels 32 31
c integrate changes from bind 4.9 (most of them); continue to use address
c INADDR_ANY rather than 127.1; convert u_short to u_int16_t as appropriate
e
s 00006/00006/00160
d D 6.15 91/02/24 12:40:25 bostic 31 30
c Add include files to get prototype declarations, and fix bugs found.
e
s 00006/00012/00160
d D 6.14 90/06/27 14:26:00 bloom 30 29
c new copyright; make sure domain search terminates last domain
e
s 00004/00001/00168
d D 6.13 90/05/20 14:07:25 bloom 29 28
c fix the resolver addresses to be as before if an error occurs
e
s 00003/00003/00166
d D 6.12 89/12/27 13:31:44 bloom 28 27
c fgets leaves the newline - check for a truncated line by looking at
c a newline in addition to null
e
s 00010/00003/00159
d D 6.11 89/12/14 11:30:37 karels 27 25
c make LOCALDOMAIN override "search" like "domain"; bigger limit
c for "search" than default domain search
e
s 00007/00002/00160
d R 6.11 89/12/14 10:25:16 karels 26 25
c LOCALDOMAIN needs to override search if it overrides domain
e
s 00111/00092/00051
d D 6.10 89/12/14 08:31:17 karels 25 24
c add "search" keyword, attempt to reformat
e
s 00010/00005/00133
d D 6.9 88/06/27 17:14:16 bostic 24 23
c install approved copyright notice
e
s 00009/00003/00129
d D 6.8 88/03/07 21:17:21 bostic 23 22
c added Berkeley specific header
e
s 00003/00005/00129
d D 6.7 87/09/30 10:20:45 bostic 22 21
c get rid of global conffile
e
s 00018/00013/00116
d D 6.6 87/05/12 22:12:16 karels 21 20
c keep list of local domains
e
s 00001/00001/00128
d D 6.5 86/04/11 11:14:46 kjd 20 19
c change RES_TIMEOUT to 4
e
s 00007/00007/00122
d D 6.4 86/03/18 08:57:08 kjd 19 17
c move resolver.h to /usr/include
e
s 00001/00001/00128
d R 6.4 86/03/17 09:06:53 kjd 18 17
c move resolv.h to /usr/include
e
s 00002/00002/00127
d D 6.3 86/03/09 20:35:53 donn 17 16
c added LIBC_SCCS condition for sccs ids
e
s 00001/00006/00128
d D 6.2 85/11/26 18:25:04 kjd 16 15
c Stop announcing what server we are trying
e
s 00000/00000/00134
d D 6.1 85/10/31 15:29:43 kjd 15 14
c Freeze for November 1 network distribution
e
s 00002/00002/00132
d D 5.10 85/10/23 19:16:58 bloom 14 13
c bitwise not logical and kevin
e
s 00083/00057/00051
d D 5.9 85/10/21 17:18:09 kjd 13 12
c Changes to make work on sun and have resolver query multiple servers
e
s 00003/00005/00105
d D 5.8 85/10/08 16:10:16 karels 12 11
c don't fail if can't get domain name from hostname
e
s 00001/00005/00109
d D 5.7 85/09/15 14:16:56 bloom 11 10
c must have port number compiled in
e
s 00059/00015/00055
d D 5.6 85/09/14 11:28:00 bloom 10 9
c change algorithm for initialization, move conf file, return error code
e
s 00002/00002/00068
d D 5.5 85/08/05 14:29:25 kjd 9 8
c Change default settings of resolver state
e
s 00013/00001/00057
d D 5.4 85/07/31 14:26:27 kjd 8 7
c Move definition of CONFFILE from resolv.h to here
e
s 00002/00002/00056
d D 5.3 85/07/29 18:01:10 kjd 7 6
c Move /usr/include/nameser.h to /usrs/include/arpa/nameser.h 
c and move /usr/include/resolv.h /usr/include/arpa/resolv.h
e
s 00001/00001/00057
d D 5.2 85/07/16 11:02:44 kjd 6 5
c Change HTONS to standard htons()
e
s 00007/00006/00051
d D 5.1 85/05/30 12:05:59 dist 5 4
c Add copyright
e
s 00005/00000/00052
d D 4.4 85/04/01 15:11:14 ralph 4 3
c add copyright notice
e
s 00000/00002/00052
d D 4.3 85/03/28 09:26:04 ralph 3 2
c name changes and fix return value in res_init().
e
s 00007/00010/00047
d D 4.2 85/03/27 14:57:07 ralph 2 1
c allow environment LOCALDOMAIN to override default domain.
e
s 00048/00000/00000
d D 4.1 85/03/01 10:42:16 ralph 1 0
c date and time created 85/03/01 10:42:16 by ralph
e
u
U
t
T
I 1
D 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif

E 5
I 4
D 30
/*
E 30
I 30
/*-
E 30
D 5
 * Copyright (c) 1985 Regents of the University of California
 *	All Rights Reserved
E 5
I 5
D 25
 * Copyright (c) 1985 Regents of the University of California.
E 25
I 25
D 35
 * Copyright (c) 1985, 1989 Regents of the University of California.
E 25
D 23
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 23
I 23
 * All rights reserved.
E 35
I 35
 * Copyright (c) 1985, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
D 30
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 30
I 30
 * %sccs.include.redist.c%
I 32
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * --Copyright--
E 32
E 30
E 24
E 23
E 5
 */
I 5

D 17
#ifndef lint
E 17
I 17
#if defined(LIBC_SCCS) && !defined(lint)
E 17
static char sccsid[] = "%W% (Berkeley) %G%";
I 32
static char rcsid[] = "$Id: res_init.c,v 4.9.1.1 1993/05/02 22:43:03 vixie Rel $";
E 32
D 17
#endif not lint
E 17
I 17
D 23
#endif LIBC_SCCS and not lint
E 23
I 23
#endif /* LIBC_SCCS and not lint */
E 23
E 17
E 5

E 4
D 31
#include <sys/types.h>
E 31
I 31
#include <sys/param.h>
E 31
#include <sys/socket.h>
#include <netinet/in.h>
D 31
#include <stdio.h>
E 31
I 31
#include <arpa/inet.h>
E 31
I 10
D 11
#include <netdb.h>
E 11
E 10
D 7
#include <nameser.h>
#include <resolv.h>
E 7
I 7
#include <arpa/nameser.h>
D 19
#include <arpa/resolv.h>
E 19
I 19
#include <resolv.h>
I 31
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 31
E 19
E 7

/*
I 8
D 25
 * Resolver configuration file. Contains the address of the
 * inital name server to query and the default domain for
 * non fully qualified domain names.
 */

D 22
#ifdef CONFFILE
D 13
char	*conffile = CONFFILE;
E 13
I 13
char    *conffile = CONFFILE;
E 13
#else
D 10
char	*conffile = "/usr/local/lib/resolv.conf";
E 10
I 10
D 13
char	*conffile = "/etc/resolv.conf";
E 13
I 13
char    *conffile = "/etc/resolv.conf";
E 22
I 22
#ifndef	CONFFILE
#define	CONFFILE	"/etc/resolv.conf"
E 22
E 13
E 10
#endif

/*
E 25
E 8
 * Resolver state default settings
 */
I 13

D 21
#ifndef RES_TIMEOUT
D 20
#define RES_TIMEOUT 10
E 20
I 20
#define RES_TIMEOUT 4
E 20
#endif

E 21
E 13
D 32
struct state _res = {
E 32
I 32
struct __res_state _res = {
E 32
D 9
	90,
	2,
E 9
I 9
D 13
	10,
	4,
E 9
	RES_RECURSE|RES_DEFNAMES,
E 13
I 13
D 21
    RES_TIMEOUT,                 /* retransmition time interval */
    4,                           /* number of times to retransmit */
    RES_RECURSE|RES_DEFNAMES,    /* options flags */
    1,                           /* number of name servers */
E 21
I 21
D 25
    RES_TIMEOUT,               	/* retransmition time interval */
    4,                         	/* number of times to retransmit */
    RES_DEFAULT,		/* options flags */
    1,                         	/* number of name servers */
E 25
I 25
	RES_TIMEOUT,               	/* retransmition time interval */
	4,                         	/* number of times to retransmit */
	RES_DEFAULT,			/* options flags */
	1,                         	/* number of name servers */
E 25
E 21
E 13
};

/*
D 10
 * Read the configuration file for default settings.
 * Return true if the name server address is initialized.
E 10
I 10
 * Set up default settings.  If the configuration file exist, the values
 * there will have precedence.  Otherwise, the server address is set to
 * INADDR_ANY and the default domain name comes from the gethostname().
 *
 * The configuration file should only be used if you want to redefine your
 * domain or run without a server on your machine.
 *
 * Return 0 if completes successfully, -1 on error
E 10
 */
res_init()
{
D 13
	FILE *fp;
	char buf[BUFSIZ], *cp;
D 10
	int n;
E 10
	extern u_long inet_addr();
D 2
	extern char *index();
E 2
I 2
D 10
	extern char *index(), *getenv();
E 10
I 10
	extern char *index();
	extern char *strcpy(), *strncpy();
E 13
I 13
D 25
    register FILE *fp;
D 21
    char buf[BUFSIZ], *cp;
E 21
I 21
    register char *cp, **pp;
    char buf[BUFSIZ];
E 21
    extern u_long inet_addr();
    extern char *index();
    extern char *strcpy(), *strncpy();
E 13
D 11
	struct servent *serv;
E 11
D 21
#ifdef DEBUG
E 21
D 13
	extern char *getenv();
#endif
E 13
I 13
    extern char *getenv();
D 21
#endif DEBUG
E 21
    int n = 0;    /* number of nameserver records read from file */
E 25
I 25
	register FILE *fp;
	register char *cp, **pp;
	register int n;
	char buf[BUFSIZ];
D 31
	extern u_long inet_addr();
	extern char *index();
	extern char *strcpy(), *strncpy();
	extern char *getenv();
E 31
	int nserv = 0;    /* number of nameserver records read from file */
I 27
	int haveenv = 0;
E 27
	int havesearch = 0;
E 25
E 13
E 10
E 2

I 32
#ifdef USELOOPBACK
	_res.nsaddr.sin_addr = inet_makeaddr(IN_LOOPBACKNET, 1);
#else
E 32
D 10
	_res.options |= RES_INIT;
E 10
D 13
	_res.nsaddr.sin_family = AF_INET;
	_res.nsaddr.sin_addr.s_addr = INADDR_ANY;
D 2
	_res.nsaddr.sin_port = HTONS(53);	/* well known port number */
E 2
I 2
D 6
	_res.nsaddr.sin_port = HTONS(NAMESERVER_PORT);
E 6
I 6
D 10
	_res.nsaddr.sin_port = htons(NAMESERVER_PORT);
E 10
I 10
	_res.defdname[0] = '\0';
D 11
	if ((serv = getservbyname(NAMESERVER_SNAME, "tcp")) == NULL)
		return(-1);
	_res.nsaddr.sin_port = (u_short)serv->s_port;
E 11
I 11
	_res.nsaddr.sin_port = htons(NAMESERVER_PORT);
E 13
I 13
D 25
    _res.nsaddr.sin_addr.s_addr = INADDR_ANY;
    _res.nsaddr.sin_family = AF_INET;
    _res.nsaddr.sin_port = htons(NAMESERVER_PORT);
    _res.nscount = 1;
    _res.defdname[0] = '\0';
E 25
I 25
	_res.nsaddr.sin_addr.s_addr = INADDR_ANY;
I 32
#endif
E 32
	_res.nsaddr.sin_family = AF_INET;
	_res.nsaddr.sin_port = htons(NAMESERVER_PORT);
	_res.nscount = 1;
I 32
	_res.pfcode = 0;
E 32
E 25
E 13
E 11
E 10
E 6
E 2

D 10
	/* first try reading the config file */
E 10
D 8
	if ((fp = fopen(CONFFILE, "r")) != NULL) {
E 8
I 8
D 13
	if ((fp = fopen(conffile, "r")) != NULL) {
E 8
D 2
		if (fgets(_res.defdname, MAXDNAME, fp) == NULL)
E 2
I 2
D 10
		if (fgets(_res.defdname, sizeof(_res.defdname), fp) == NULL)
E 2
			_res.defdname[0] = '\0';
		else if ((cp = index(_res.defdname, '\n')) != NULL)
			*cp = '\0';
D 2
		if (fgets(buf, sizeof (buf), fp) != NULL) {
			(void) fclose(fp);
E 2
I 2
		if (fgets(buf, sizeof (buf), fp) != NULL)
E 2
			_res.nsaddr.sin_addr.s_addr = inet_addr(buf);
E 10
I 10
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			if (!strncmp(buf, "domain", sizeof("domain") - 1)) {
				cp = buf + sizeof("domain") - 1;
				while (*cp == ' ' || *cp == '\t')
					cp++;
				if (*cp == '\0')
					continue;
				(void)strncpy(_res.defdname, cp,
				        sizeof(_res.defdname));
				_res.defdname[sizeof(_res.defdname) - 1] = '\0';
				if ((cp = index(_res.defdname, '\n')) != NULL)
					*cp = '\0';
				continue;
			}
			if (!strncmp(buf, "resolver", sizeof("resolver") - 1)) {
				cp = buf + sizeof("resolver") - 1;
				while (*cp == ' ' || *cp == '\t')
					cp++;
				if (*cp == '\0')
					continue;
				_res.nsaddr.sin_addr.s_addr = inet_addr(cp);
				if (_res.nsaddr.sin_addr.s_addr == (unsigned)-1)
					_res.nsaddr.sin_addr.s_addr =
						INADDR_ANY;
				continue;
			}
		}
E 10
D 2
			return (1);
		}
E 2
		(void) fclose(fp);
	}
I 10
	if (_res.defdname[0] == 0) {
D 12
		if (gethostname(buf, sizeof(_res.defdname)) == -1)
			return(-1);
		if ((cp = index(buf, '.')) == NULL)
			return(-1);
		(void)strcpy(_res.defdname, cp + 1);
E 12
I 12
		if (gethostname(buf, sizeof(_res.defdname)) == 0 &&
		    (cp = index(buf, '.')))
			(void)strcpy(_res.defdname, cp + 1);
E 12
	}
E 13
I 13
D 22
    if ((fp = fopen(conffile, "r")) != NULL) {
E 22
I 22
D 25
    if ((fp = fopen(CONFFILE, "r")) != NULL) {
E 22
        /* read the config file */
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            /* read default domain name */
            if (!strncmp(buf, "domain", sizeof("domain") - 1)) {
                cp = buf + sizeof("domain") - 1;
                while (*cp == ' ' || *cp == '\t')
                    cp++;
                if (*cp == '\0')
                    continue;
                (void)strncpy(_res.defdname, cp, sizeof(_res.defdname));
                _res.defdname[sizeof(_res.defdname) - 1] = '\0';
                if ((cp = index(_res.defdname, '\n')) != NULL)
                    *cp = '\0';
                continue;
            }
            /* read nameservers to query */
            if (!strncmp(buf, "nameserver", 
               sizeof("nameserver") - 1) && (n < MAXNS)) {
                cp = buf + sizeof("nameserver") - 1;
                while (*cp == ' ' || *cp == '\t')
                    cp++;
                if (*cp == '\0')
                    continue;
                _res.nsaddr_list[n].sin_addr.s_addr = inet_addr(cp);
                if (_res.nsaddr_list[n].sin_addr.s_addr == (unsigned)-1) 
                    _res.nsaddr_list[n].sin_addr.s_addr = INADDR_ANY;
D 19
                    _res.nsaddr_list[n].sin_family = AF_INET;
                    _res.nsaddr_list[n].sin_port = htons(NAMESERVER_PORT);
D 16
#ifdef DEBUG
D 14
                if ( _res.options && RES_DEBUG )
E 14
I 14
                if ( _res.options & RES_DEBUG )
E 14
                    printf("Server #%d address = %s\n", n+1,
                         inet_ntoa(_res.nsaddr_list[n].sin_addr.s_addr));
#endif DEBUG
E 16
                    if ( ++n >= MAXNS) { 
                       n = MAXNS;
E 19
I 19
                _res.nsaddr_list[n].sin_family = AF_INET;
                _res.nsaddr_list[n].sin_port = htons(NAMESERVER_PORT);
                if ( ++n >= MAXNS) { 
                    n = MAXNS;
E 19
#ifdef DEBUG
D 14
                       if ( _res.options && RES_DEBUG )
E 14
I 14
D 19
                       if ( _res.options & RES_DEBUG )
E 14
D 16
                          printf("MAXNS reached\n");
E 16
I 16
                          printf("MAXNS reached, reading resolv.conf\n");
E 19
I 19
                    if ( _res.options & RES_DEBUG )
                        printf("MAXNS reached, reading resolv.conf\n");
E 19
E 16
#endif DEBUG
                }
                continue;
            }
        }
        if ( n > 1 ) 
            _res.nscount = n;
        (void) fclose(fp);
    }
    if (_res.defdname[0] == 0) {
        if (gethostname(buf, sizeof(_res.defdname)) == 0 &&
           (cp = index(buf, '.')))
             (void)strcpy(_res.defdname, cp + 1);
    }
E 25
I 25
	/* Allow user to override the local domain definition */
D 27
	if ((cp = getenv("LOCALDOMAIN")) != NULL)
E 27
I 27
	if ((cp = getenv("LOCALDOMAIN")) != NULL) {
E 27
		(void)strncpy(_res.defdname, cp, sizeof(_res.defdname));
I 32
		if ((cp = strpbrk(_res.defdname, " \t\n")) != NULL)
			*cp = '\0';
E 32
I 27
		haveenv++;
	}
E 27
E 25
E 13
E 10

I 10
D 21
#ifdef DEBUG
E 21
E 10
D 2
	/* next, try getting the address of this host */

	/* finally, try broadcast */
E 2
I 2
D 13
	/* Allow user to override the local domain definition */
	if ((cp = getenv("LOCALDOMAIN")) != NULL)
D 10
		strncpy(_res.defdname, cp, sizeof(_res.defdname));
E 10
I 10
		(void)strncpy(_res.defdname, cp, sizeof(_res.defdname));
#endif
	_res.options |= RES_INIT;
	return(0);
E 13
I 13
D 25
    /* Allow user to override the local domain definition */
    if ((cp = getenv("LOCALDOMAIN")) != NULL)
        (void)strncpy(_res.defdname, cp, sizeof(_res.defdname));
E 25
I 25
	if ((fp = fopen(_PATH_RESCONF, "r")) != NULL) {
	    /* read the config file */
	    while (fgets(buf, sizeof(buf), fp) != NULL) {
I 32
		/* skip comments */
		if ((*buf == ';') || (*buf == '#'))
			continue;
E 32
		/* read default domain name */
		if (!strncmp(buf, "domain", sizeof("domain") - 1)) {
D 27
		    if (_res.defdname[0])	/* skip if have from environ */
E 27
I 27
		    if (haveenv)	/* skip if have from environ */
E 27
			    continue;
		    cp = buf + sizeof("domain") - 1;
		    while (*cp == ' ' || *cp == '\t')
			    cp++;
D 28
		    if (*cp == '\0')
E 28
I 28
		    if ((*cp == '\0') || (*cp == '\n'))
E 28
			    continue;
D 32
		    (void)strncpy(_res.defdname, cp, sizeof(_res.defdname) - 1);
		    if ((cp = index(_res.defdname, '\n')) != NULL)
E 32
I 32
		    (void)strncpy(_res.defdname, cp,
				  sizeof(_res.defdname) - 1);
		    if ((cp = strpbrk(_res.defdname, " \t\n")) != NULL)
E 32
			    *cp = '\0';
		    havesearch = 0;
		    continue;
		}
		/* set search list */
		if (!strncmp(buf, "search", sizeof("search") - 1)) {
I 27
		    if (haveenv)	/* skip if have from environ */
			    continue;
E 27
		    cp = buf + sizeof("search") - 1;
		    while (*cp == ' ' || *cp == '\t')
			    cp++;
D 28
		    if (*cp == '\0')
E 28
I 28
		    if ((*cp == '\0') || (*cp == '\n'))
E 28
			    continue;
D 32
		    (void)strncpy(_res.defdname, cp, sizeof(_res.defdname) - 1);
E 32
I 32
		    (void)strncpy(_res.defdname, cp,
				  sizeof(_res.defdname) - 1);
E 32
D 34
		    if ((cp = index(_res.defdname, '\n')) != NULL)
E 34
I 34
		    if ((cp = strchr(_res.defdname, '\n')) != NULL)
E 34
			    *cp = '\0';
		    /*
		     * Set search list to be blank-separated strings
		     * on rest of line.
		     */
		    cp = _res.defdname;
		    pp = _res.dnsrch;
		    *pp++ = cp;
		    for (n = 0; *cp && pp < _res.dnsrch + MAXDNSRCH; cp++) {
			    if (*cp == ' ' || *cp == '\t') {
				    *cp = 0;
				    n = 1;
			    } else if (n) {
				    *pp++ = cp;
				    n = 0;
			    }
		    }
I 30
		    /* null terminate last domain if there are excess */
		    while (*cp != '\0' && *cp != ' ' && *cp != '\t')
			    cp++;
		    *cp = '\0';
E 30
I 27
		    *pp++ = 0;
E 27
		    havesearch = 1;
		    continue;
		}
		/* read nameservers to query */
		if (!strncmp(buf, "nameserver", sizeof("nameserver") - 1) &&
		   nserv < MAXNS) {
I 32
		   struct in_addr a;

E 32
		    cp = buf + sizeof("nameserver") - 1;
		    while (*cp == ' ' || *cp == '\t')
D 32
			    cp++;
D 28
		    if (*cp == '\0')
E 28
I 28
		    if ((*cp == '\0') || (*cp == '\n'))
E 28
			    continue;
		    if ((_res.nsaddr_list[nserv].sin_addr.s_addr =
D 29
			inet_addr(cp)) == (unsigned)-1) 
E 29
I 29
			inet_addr(cp)) == (unsigned)-1) {
			    _res.nsaddr_list[nserv].sin_addr.s_addr
				= INADDR_ANY;
E 29
			    continue;
E 32
I 32
			cp++;
		    if ((*cp != '\0') && (*cp != '\n') && inet_aton(cp, &a)) {
			_res.nsaddr_list[nserv].sin_addr = a;
			_res.nsaddr_list[nserv].sin_family = AF_INET;
			_res.nsaddr_list[nserv].sin_port =
				htons(NAMESERVER_PORT);
			nserv++;
E 32
I 29
		    }
E 29
D 32
		    _res.nsaddr_list[nserv].sin_family = AF_INET;
		    _res.nsaddr_list[nserv].sin_port = htons(NAMESERVER_PORT);
		    nserv++;
E 32
		    continue;
		}
	    }
	    if (nserv > 1) 
		_res.nscount = nserv;
	    (void) fclose(fp);
	}
	if (_res.defdname[0] == 0) {
		if (gethostname(buf, sizeof(_res.defdname)) == 0 &&
D 34
		   (cp = index(buf, '.')))
E 34
I 34
		   (cp = strchr(buf, '.')))
E 34
			(void)strcpy(_res.defdname, cp + 1);
	}
E 25
D 21
#endif DEBUG
E 21
I 21

D 25
    /* find components of local domain that might be searched */
    pp = _res.dnsrch;
    *pp++ = _res.defdname;
    for (cp = _res.defdname, n = 0; *cp; cp++)
	if (*cp == '.')
	    n++;
    cp = _res.defdname;
    for (; n >= LOCALDOMAINPARTS && pp < _res.dnsrch + MAXDNSRCH; n--) {
	cp = index(cp, '.');
	*pp++ = ++cp;
    }
E 21
    _res.options |= RES_INIT;
    return(0);
E 25
I 25
	/* find components of local domain that might be searched */
	if (havesearch == 0) {
		pp = _res.dnsrch;
		*pp++ = _res.defdname;
		for (cp = _res.defdname, n = 0; *cp; cp++)
			if (*cp == '.')
				n++;
		cp = _res.defdname;
D 27
		for (; n >= LOCALDOMAINPARTS && pp < _res.dnsrch + MAXDNSRCH;
E 27
I 27
		for (; n >= LOCALDOMAINPARTS && pp < _res.dnsrch + MAXDFLSRCH;
E 27
		    n--) {
D 34
			cp = index(cp, '.');
E 34
I 34
			cp = strchr(cp, '.');
E 34
			*pp++ = ++cp;
		}
I 27
		*pp++ = 0;
E 27
	}
	_res.options |= RES_INIT;
	return (0);
E 25
E 13
E 10
E 2
D 3

	return (0);
E 3
}
E 1
