h34993
s 00002/00002/00280
d D 8.1 93/06/06 16:29:21 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00281
d D 5.7 93/05/21 15:34:19 mckusick 8 7
c update header to reflect redistributable status
e
s 00037/00019/00245
d D 5.6 92/07/23 18:06:08 bostic 7 6
c Elan's new kvm version; update copyright/header; lint
e
s 00011/00007/00253
d D 5.5 91/02/04 23:26:35 torek 6 5
c fix gcc-detected lint
e
s 00001/00000/00259
d D 5.4 90/04/11 19:17:47 sklower 5 4
c in_pcb.h now requires ip.h first
e
s 00001/00001/00258
d D 5.3 87/09/15 16:29:00 bostic 4 3
c ignore port fix; bug report 4.3BSD/ucb/87
e
s 00001/00003/00258
d D 5.2 85/12/11 16:07:54 bloom 3 2
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00007/00001/00254
d D 5.1 85/05/30 17:00:40 mckusick 2 1
c Add copyright
e
s 00255/00000/00000
d D 1.1 85/05/30 16:59:16 mckusick 1 0
c date and time created 85/05/30 16:59:16 by mckusick
e
u
U
t
T
I 2
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 9
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * %sccs.include.proprietary.c%
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 2

/*
 * Common network command support routines.
 */
D 7
#include "systat.h"
#include <ctype.h>

E 7
I 7
#include <sys/param.h>
E 7
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>

#include <net/route.h>
I 7
#include <netinet/in.h>
E 7
#include <netinet/in_systm.h>
I 5
#include <netinet/ip.h>
E 5
#include <netinet/in_pcb.h>

I 7
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "systat.h"
#include "extern.h"

E 7
#define	streq(a,b)	(strcmp(a,b)==0)

I 6
D 7
static void changeitems(), showprotos(), showports(), showhosts();
static int selectproto(), selectport(), selecthost();
E 7
I 7
static	struct hitem {
	struct	in_addr addr;
	int	onoff;
} *hosts;
E 7

I 7
int nports, nhosts, protos;

static void changeitems __P((char *, int));
static int selectproto __P((char *));
static void showprotos __P((void));
static int selectport __P((long, int));
static void showports __P((void));
static int selecthost __P((struct in_addr *, int));
static void showhosts __P((void));

int
E 7
E 6
netcmd(cmd, args)
	char *cmd, *args;
{

	if (prefix(cmd, "tcp") || prefix(cmd, "udp")) {
		selectproto(cmd);
		return (1);
	}
	if (prefix(cmd, "ignore") || prefix(cmd, "display")) {
		changeitems(args, prefix(cmd, "display"));
		return (1);
	}
	if (prefix(cmd, "reset")) {
		selectproto(0);
D 7
		selecthost(0);
		selectport(-1);
E 7
I 7
		selecthost(0, 0);
		selectport(-1, 0);
E 7
		return (1);
	}
	if (prefix(cmd, "show")) {
		move(CMDLINE, 0); clrtoeol();
		if (*args == '\0') {
			showprotos();
			showhosts();
			showports();
			return (1);
		}
		if (prefix(args, "protos"))
			showprotos();
		else if (prefix(args, "hosts"))
			showhosts();
		else if (prefix(args, "ports"))
			showports();
		else
			addstr("show what?");
		return (1);
	}
	return (0);
}

I 7

E 7
D 6
static
E 6
I 6
static void
E 6
changeitems(args, onoff)
	char *args;
	int onoff;
{
	register char *cp;
D 3
	register int i;
E 3
	struct servent *sp;
	struct hostent *hp;
	struct in_addr in;
	char *index();

	cp = index(args, '\n');
	if (cp)
		*cp = '\0';
	for (;;args = cp) {
		for (cp = args; *cp && isspace(*cp); cp++)
			;
		args = cp;
		for (; *cp && !isspace(*cp); cp++)
			;
		if (*cp)
			*cp++ = '\0';
		if (cp - args == 0)
			break;
		sp = getservbyname(args,
		    protos == TCP ? "tcp" : protos == UDP ? "udp" : 0);
		if (sp) {
D 4
			selectport(sp->s_name, onoff);
E 4
I 4
			selectport(sp->s_port, onoff);
E 4
			continue;
		}
		hp = gethostbyname(args);
		if (hp == 0) {
			in.s_addr = inet_addr(args);
			if (in.s_addr == -1) {
				error("%s: unknown host or port", args);
				continue;
			}
		} else
			in = *(struct in_addr *)hp->h_addr;
		selecthost(&in, onoff);
	}
}

D 6
static
E 6
I 6
static int
E 6
selectproto(proto)
	char *proto;
{
	int new = protos;

	if (proto == 0 || streq(proto, "all"))
		new = TCP|UDP;
	else if (streq(proto, "tcp"))
		new = TCP;
	else if (streq(proto, "udp"))
		new = UDP;
	return (new != protos, protos = new);
}

D 6
static
E 6
I 6
static void
E 6
showprotos()
{

	if ((protos&TCP) == 0)
		addch('!');
	addstr("tcp ");
	if ((protos&UDP) == 0)
		addch('!');
	addstr("udp ");
}

static	struct pitem {
	long	port;
	int	onoff;
} *ports;

D 6
static
E 6
I 6
static int
E 6
selectport(port, onoff)
	long port;
	int onoff;
{
D 3
	register struct pitem *p, *open;
E 3
I 3
	register struct pitem *p;
E 3

	if (port == -1) {
		if (ports == 0)
			return (0);
		free((char *)ports), ports = 0;
		nports = 0;
		return (1);
	}
D 3
	open = 0;
E 3
	for (p = ports; p < ports+nports; p++)
		if (p->port == port) {
			p->onoff = onoff;
			return (0);
		}
	if (nports == 0)
		ports = (struct pitem *)malloc(sizeof (*p));
	else
		ports = (struct pitem *)realloc(ports, (nports+1)*sizeof (*p));
	p = &ports[nports++];
	p->port = port;
	p->onoff = onoff;
	return (1);
}

I 7
int
E 7
checkport(inp)
	register struct inpcb *inp;
{
	register struct pitem *p;

	if (ports)
	for (p = ports; p < ports+nports; p++)
		if (p->port == inp->inp_lport || p->port == inp->inp_fport)
			return (p->onoff);
	return (1);
}

D 6
static
E 6
I 6
static void
E 6
showports()
{
	register struct pitem *p;
	struct servent *sp;

	for (p = ports; p < ports+nports; p++) {
		sp = getservbyport(p->port,
		    protos == TCP|UDP ? 0 : protos == TCP ? "tcp" : "udp");
		if (!p->onoff)
			addch('!');
		if (sp)
			printw("%s ", sp->s_name);
		else
			printw("%d ", p->port);
	}
}

D 7
static	struct hitem {
	struct	in_addr addr;
	int	onoff;
} *hosts;

E 7
D 6
static
E 6
I 6
static int
E 6
selecthost(in, onoff)
	struct in_addr *in;
I 6
	int onoff;
E 6
{
	register struct hitem *p;

	if (in == 0) {
		if (hosts == 0)
			return (0);
		free((char *)hosts), hosts = 0;
		nhosts = 0;
		return (1);
	}
	for (p = hosts; p < hosts+nhosts; p++)
		if (p->addr.s_addr == in->s_addr) {
			p->onoff = onoff;
			return (0);
		}
	if (nhosts == 0)
		hosts = (struct hitem *)malloc(sizeof (*p));
	else
		hosts = (struct hitem *)realloc(hosts, (nhosts+1)*sizeof (*p));
	p = &hosts[nhosts++];
	p->addr = *in;
	p->onoff = onoff;
	return (1);
}

I 7
int
E 7
checkhost(inp)
	register struct inpcb *inp;
{
	register struct hitem *p;

	if (hosts)
	for (p = hosts; p < hosts+nhosts; p++)
		if (p->addr.s_addr == inp->inp_laddr.s_addr ||
		    p->addr.s_addr == inp->inp_faddr.s_addr)
			return (p->onoff);
	return (1);
}

D 6
static
E 6
I 6
static void
E 6
showhosts()
{
	register struct hitem *p;
	struct hostent *hp;

	for (p = hosts; p < hosts+nhosts; p++) {
D 7
		hp = gethostbyaddr(&p->addr, sizeof (p->addr), AF_INET);
E 7
I 7
		hp = gethostbyaddr((char *)&p->addr, sizeof (p->addr), AF_INET);
E 7
		if (!p->onoff)
			addch('!');
D 7
		printw("%s ", hp ? hp->h_name : inet_ntoa(p->addr));
E 7
I 7
		printw("%s ", hp ? hp->h_name : (char *)inet_ntoa(p->addr));
E 7
	}
}
E 1
