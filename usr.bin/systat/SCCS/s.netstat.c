h34303
s 00002/00002/00442
d D 8.1 93/06/06 16:29:27 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00443
d D 5.12 93/05/21 15:34:21 mckusick 14 13
c update header to reflect redistributable status
e
s 00001/00001/00443
d D 5.11 92/11/10 12:24:33 elan 13 12
c Converted to new curses(3) library.
e
s 00006/00006/00438
d D 5.10 92/09/02 11:56:35 bostic 12 11
c nl is an exported curses function
e
s 00006/00006/00438
d D 5.9 92/07/24 12:41:20 bostic 11 10
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00009/00007/00435
d D 5.8 92/07/23 18:29:33 bostic 10 9
c replace insque/remque
e
s 00030/00007/00412
d D 5.7 92/07/23 18:07:08 bostic 9 8
c Elan's new kvm version; update copyright/header; lint
e
s 00018/00018/00401
d D 5.6 91/06/26 13:50:28 marc 8 7
c changes for new kernel, plus use kvm
e
s 00007/00004/00412
d D 5.5 91/02/04 23:31:10 torek 7 6
c fix gcc-detected lint
e
s 00001/00001/00415
d D 5.4 90/04/11 19:19:22 sklower 6 5
c in_pcb.h needs ip.h first
e
s 00007/00009/00409
d D 5.3 89/05/11 10:57:50 bostic 5 4
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00003/00003/00415
d D 5.2 85/12/11 16:07:59 bloom 4 3
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00007/00001/00411
d D 5.1 85/05/30 16:25:04 mckusick 3 2
c Add copyright
e
s 00047/00223/00365
d D 1.2 85/05/01 01:34:22 sam 2 1
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00588/00000/00000
d D 1.1 85/04/29 00:44:35 sam 1 0
c date and time created 85/04/29 00:44:35 by sam
e
u
U
t
T
I 3
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 15
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 14
 * %sccs.include.proprietary.c%
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 9
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 3

/*
 * netstat
 */
D 9
#include "systat.h"
E 9
D 10

E 10
I 9
#include <sys/param.h>
E 9
D 2
#include <netdb.h>
#include <nlist.h>
#include <signal.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/file.h>
E 2
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>

I 9
#include <netinet/in.h>
E 9
#include <net/route.h>
D 2
#include <netinet/in.h>
E 2
#include <netinet/in_systm.h>
D 6
#include <netinet/in_pcb.h>
E 6
#include <netinet/ip.h>
I 6
#include <netinet/in_pcb.h>
E 6
#include <netinet/ip_icmp.h>
#include <netinet/icmp_var.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcpip.h>
#include <netinet/tcp_seq.h>
#define TCPSTATES
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_debug.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>
I 9

#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <nlist.h>
E 9
I 5
#include <paths.h>
I 9
#include "systat.h"
#include "extern.h"
E 9
E 5

I 9
static void enter __P((struct inpcb *, struct socket *, int, char *));
static char *inetname __P((struct in_addr));
static void inetprint __P((struct in_addr *, int, char *));

E 9
#define	streq(a,b)	(strcmp(a,b)==0)
I 2
D 13
#define	YMAX(w)		((w)->_maxy-1)
E 13
I 13
#define	YMAX(w)		((w)->maxy-1)
E 13
E 2

WINDOW *
opennetstat()
{
D 5

E 5
	sethostent(1);
	setnetent(1);
	return (subwin(stdscr, LINES-5-1, 0, 5, 0));
}

struct netinfo {
	struct	netinfo *ni_forw, *ni_prev;
	short	ni_line;		/* line on screen */
	short	ni_seen;		/* 0 when not present in list */
	short	ni_flags;
#define	NIF_LACHG	0x1		/* local address changed */
#define	NIF_FACHG	0x2		/* foreign address changed */
	short	ni_state;		/* tcp state */
	char	*ni_proto;		/* protocol */
	struct	in_addr ni_laddr;	/* local address */
	long	ni_lport;		/* local port */
	struct	in_addr	ni_faddr;	/* foreign address */
	long	ni_fport;		/* foreign port */
	long	ni_rcvcc;		/* rcv buffer character count */
	long	ni_sndcc;		/* snd buffer character count */
};

static struct {
	struct	netinfo *ni_forw, *ni_prev;
} netcb;

static	int aflag = 0;
static	int nflag = 0;
static	int lastrow = 1;
I 7
static	void enter(), inetprint();
E 7
static	char *inetname();

I 9
void
E 9
closenetstat(w)
        WINDOW *w;
{
D 4
	register struct netinfo *p, *q;
E 4
I 4
	register struct netinfo *p;
E 4

	endhostent();
	endnetent();
D 10
	p = netcb.ni_forw;
E 10
I 10
	p = (struct netinfo *)netcb.ni_forw;
E 10
	while (p != (struct netinfo *)&netcb) {
		if (p->ni_line != -1)
			lastrow--;
		p->ni_line = -1;
		p = p->ni_forw;
	}
        if (w != NULL) {
		wclear(w);
		wrefresh(w);
		delwin(w);
	}
}

D 11
static struct nlist nlst[] = {
E 11
I 11
D 12
static struct nlist nl[] = {
E 12
I 12
static struct nlist namelist[] = {
E 12
E 11
#define	X_TCB	0
	{ "_tcb" },
#define	X_UDB	1
	{ "_udb" },
D 5
        { "" },
E 5
I 5
	{ "" },
E 5
};

I 9
int
E 9
D 2
static	long *ports;
static	int nports;
static	struct in_addr *hosts;
static	int nhosts;
static	int protos;
#define	TCP	0x1
#define	UDP	0x2

E 2
initnetstat()
{
D 4
        register  i;
E 4
D 5

	nlist("/vmunix", nlst);
E 5
I 5
D 8
	nlist(_PATH_UNIX, nlst);
E 8
I 8
D 9
	kvm_nlist(nlst);
E 9
I 9
D 11
	if (kvm_nlist(kd, nlst)) {
		nlisterr(nlst);
E 11
I 11
D 12
	if (kvm_nlist(kd, nl)) {
		nlisterr(nl);
E 12
I 12
	if (kvm_nlist(kd, namelist)) {
		nlisterr(namelist);
E 12
E 11
		return(0);
	}
E 9
E 8
E 5
D 11
	if (nlst[X_TCB].n_value == 0) {
E 11
I 11
D 12
	if (nl[X_TCB].n_value == 0) {
E 12
I 12
	if (namelist[X_TCB].n_value == 0) {
E 12
E 11
		error("No symbols in namelist");
D 4
		return;
E 4
I 4
		return(0);
E 4
	}
	netcb.ni_forw = netcb.ni_prev = (struct netinfo *)&netcb;
D 2
	selectproto(0);
	selectport(-1);
	selecthost(0);
E 2
I 2
	protos = TCP|UDP;
I 4
	return(1);
E 4
E 2
}

I 9
void
E 9
D 2
static
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

static
selectport(port)
	long port;
{
	register long *p;

	if (port == -1) {
		if (nports == 1)
			return (0);
		if (ports)
			free((char *)ports);
		ports = (long *)malloc(sizeof (long));
		*ports = -1;
		nports = 1;
		return (1);
	}
	for (p = ports; *p != -1; p++)
		if (*p == port)
			return (0);
	ports = (long *)realloc(ports, (nports + 1)*sizeof (long));
	ports[nports-1] = port;
	ports[nports++] = -1;
	return (1);
}

static
checkport(inp)
	register struct inpcb *inp;
{
	register long *p;

	for (p = ports; *p != -1; p++)
		if (*p == inp->inp_lport || *p == inp->inp_fport)
			return (1);
	return (0);
}

static
selecthost(in)
	struct in_addr *in;
{
	register struct in_addr *p;

	if (in == 0) {
		if (nhosts == 1)
			return (0);
		if (hosts)
			free((char *)hosts);
		hosts = (struct in_addr *)malloc(sizeof (struct in_addr));
		hosts->s_addr = -1;
		nhosts = 1;
		return (1);
	}
	for (p = hosts; p->s_addr != -1; p++)
		if (p->s_addr == in->s_addr)
			return (0);
	hosts = (struct in_addr *)realloc(hosts,
	    (nhosts + 1)*sizeof (struct in_addr));
	hosts[nhosts-1] = *in;
	hosts[nhosts++].s_addr = -1;
	return (1);
}

static
checkhost(inp)
	register struct inpcb *inp;
{
	register struct in_addr *p;

	for (p = hosts; p->s_addr != -1; p++)
		if (p->s_addr == inp->inp_laddr.s_addr ||
		    p->s_addr == inp->inp_faddr.s_addr)
			return (1);
	return (0);
}

E 2
fetchnetstat()
{
	register struct inpcb *prev, *next;
	register struct netinfo *p;
	struct inpcb inpcb;
	struct socket sockb;
	struct tcpcb tcpcb;
D 8
	off_t off;
E 8
I 8
	void *off;
E 8
	int istcp;

D 11
	if (nlst[X_TCB].n_value == 0)
E 11
I 11
D 12
	if (nl[X_TCB].n_value == 0)
E 12
I 12
	if (namelist[X_TCB].n_value == 0)
E 12
E 11
		return;
	for (p = netcb.ni_forw; p != (struct netinfo *)&netcb; p = p->ni_forw)
		p->ni_seen = 0;
I 2
D 7
	if (protos == 0)
		error("No protocols to display");
E 7
E 2
D 8
	if (protos&TCP)
		off = nlst[X_TCB].n_value, istcp = 1;
	else if (protos&UDP)
		off = nlst[X_UDB].n_value, istcp = 0;
E 8
I 8
	if (protos&TCP) {
		off = NPTR(X_TCB); 
		istcp = 1;
	}
	else if (protos&UDP) {
		off = NPTR(X_UDB); 
		istcp = 0;
	}
E 8
I 7
	else {
		error("No protocols to display");
		return;
	}
E 7
again:
D 8
	lseek(kmem, off, L_SET);
	read(kmem, &inpcb, sizeof (struct inpcb));
	prev = (struct inpcb *)off;
	for (; inpcb.inp_next != (struct inpcb *)off; prev = next) {
E 8
I 8
	KREAD(off, &inpcb, sizeof (struct inpcb));
	prev = off;
	for (; inpcb.inp_next != off; prev = next) {
E 8
		next = inpcb.inp_next;
D 8
		lseek(kmem, (off_t)next, L_SET);
		read(kmem, &inpcb, sizeof (inpcb));
E 8
I 8
		KREAD(next, &inpcb, sizeof (inpcb));
E 8
		if (inpcb.inp_prev != prev) {
			p = netcb.ni_forw;
			for (; p != (struct netinfo *)&netcb; p = p->ni_forw)
				p->ni_seen = 1;
			error("Kernel state in transition");
			return;
		}
		if (!aflag && inet_lnaof(inpcb.inp_laddr) == INADDR_ANY)
			continue;
D 2
		if (nhosts != 1 && !checkhost(&inpcb))
E 2
I 2
		if (nhosts && !checkhost(&inpcb))
E 2
			continue;
D 2
		if (nports != 1 && !checkport(&inpcb))
E 2
I 2
		if (nports && !checkport(&inpcb))
E 2
			continue;
D 8
		lseek(kmem, (off_t)inpcb.inp_socket, L_SET);
		read(kmem, &sockb, sizeof (sockb));
		lseek(kmem, (off_t)inpcb.inp_ppcb, L_SET);
E 8
I 8
		KREAD(inpcb.inp_socket, &sockb, sizeof (sockb));
E 8
		if (istcp) {
D 8
			read(kmem, &tcpcb, sizeof (tcpcb));
E 8
I 8
			KREAD(inpcb.inp_ppcb, &tcpcb, sizeof (tcpcb));
E 8
			enter(&inpcb, &sockb, tcpcb.t_state, "tcp");
		} else
			enter(&inpcb, &sockb, 0, "udp");
	}
	if (istcp && (protos&UDP)) {
		istcp = 0;
D 8
		off = nlst[X_UDB].n_value;
E 8
I 8
		off = NPTR(X_UDB);
E 8
		goto again;
	}
}

D 7
static
E 7
I 7
static void
E 7
enter(inp, so, state, proto)
	register struct inpcb *inp;
	register struct socket *so;
	int state;
	char *proto;
{
D 2
	register struct netinfo *p, *match = 0;
	int matchwild = 3, wildcard;
E 2
I 2
	register struct netinfo *p;
E 2

	/*
D 2
	 * Must mimic in_pcblookup to match partial connections.
E 2
I 2
	 * Only take exact matches, any sockets with
	 * previously unbound addresses will be deleted
	 * below in the display routine because they
	 * will appear as ``not seen'' in the kernel
	 * data structures.
E 2
	 */
	for (p = netcb.ni_forw; p != (struct netinfo *)&netcb; p = p->ni_forw) {
		if (!streq(proto, p->ni_proto))
			continue;
D 2
		if (p->ni_lport != inp->inp_lport)
E 2
I 2
		if (p->ni_lport != inp->inp_lport ||
		    p->ni_laddr.s_addr != inp->inp_laddr.s_addr)
E 2
			continue;
D 2
		wildcard = 0;
		if (p->ni_laddr.s_addr != INADDR_ANY) {
			if (inp->inp_laddr.s_addr == INADDR_ANY)
				wildcard++;
			else if (p->ni_laddr.s_addr != inp->inp_laddr.s_addr)
				continue;
		} else {
			if (inp->inp_laddr.s_addr != INADDR_ANY)
				wildcard++;
E 2
I 2
		if (p->ni_faddr.s_addr == inp->inp_faddr.s_addr &&
		    p->ni_fport == inp->inp_fport)
			break;
	}
	if (p == (struct netinfo *)&netcb) {
D 10
		p = (struct netinfo *)malloc(sizeof (*p));
		if (p == 0) {
E 10
I 10
		if ((p = malloc(sizeof(*p))) == NULL) {
E 10
			error("Out of memory");
			return;
E 2
		}
D 2
		if (p->ni_faddr.s_addr != INADDR_ANY) {
			if (inp->inp_faddr.s_addr == INADDR_ANY)
				wildcard++;
			else if (p->ni_faddr.s_addr != inp->inp_faddr.s_addr ||
			    p->ni_fport != inp->inp_fport)
				continue;
		} else {
			if (inp->inp_faddr.s_addr != INADDR_ANY)
				wildcard++;
		}
		if (wildcard < matchwild) {
			match = p;
			matchwild = wildcard;
			if (matchwild == 0)
				break;
		}
E 2
I 2
D 10
		insque(p, &netcb);
E 10
I 10
		p->ni_prev = (struct netinfo *)&netcb;
		p->ni_forw = netcb.ni_forw;
		netcb.ni_forw->ni_prev = p;
		netcb.ni_forw = p;
E 10
		p->ni_line = -1;
		p->ni_laddr = inp->inp_laddr;
		p->ni_lport = inp->inp_lport;
		p->ni_faddr = inp->inp_faddr;
		p->ni_fport = inp->inp_fport;
		p->ni_proto = proto;
		p->ni_flags = NIF_LACHG|NIF_FACHG;
E 2
	}
D 2
	if (match == 0) {
		match = (struct netinfo *)malloc(sizeof (*p));
		insque(match, &netcb);
		match->ni_line = -1;
		match->ni_flags = NIF_LACHG|NIF_FACHG;
	}
	if (match->ni_laddr.s_addr != inp->inp_laddr.s_addr ||
	    match->ni_lport != inp->inp_lport)
		match->ni_flags |= NIF_LACHG;
	match->ni_laddr = inp->inp_laddr;
	match->ni_lport = inp->inp_lport;
	if (match->ni_faddr.s_addr != inp->inp_faddr.s_addr ||
	    match->ni_fport != inp->inp_fport)
		match->ni_flags |= NIF_FACHG;
	match->ni_faddr = inp->inp_faddr;
	match->ni_fport = inp->inp_fport;
	match->ni_proto = proto;
	match->ni_rcvcc = so->so_rcv.sb_cc;
	match->ni_sndcc = so->so_snd.sb_cc;
	match->ni_state = state;
	match->ni_seen = 1;
E 2
I 2
	p->ni_rcvcc = so->so_rcv.sb_cc;
	p->ni_sndcc = so->so_snd.sb_cc;
	p->ni_state = state;
	p->ni_seen = 1;
E 2
}

/* column locations */
#define	LADDR	0
#define	FADDR	LADDR+23
#define	PROTO	FADDR+23
#define	RCVCC	PROTO+6
#define	SNDCC	RCVCC+7
#define	STATE	SNDCC+7

I 9

void
E 9
labelnetstat()
{
D 5

        if (nlst[X_TCB].n_type == 0)
                return;
        wmove(wnd, 0, 0); wclrtobot(wnd);
E 5
I 5
D 11
	if (nlst[X_TCB].n_type == 0)
E 11
I 11
D 12
	if (nl[X_TCB].n_type == 0)
E 12
I 12
	if (namelist[X_TCB].n_type == 0)
E 12
E 11
		return;
	wmove(wnd, 0, 0); wclrtobot(wnd);
E 5
	mvwaddstr(wnd, 0, LADDR, "Local Address");
	mvwaddstr(wnd, 0, FADDR, "Foreign Address");
	mvwaddstr(wnd, 0, PROTO, "Proto");
	mvwaddstr(wnd, 0, RCVCC, "Recv-Q");
	mvwaddstr(wnd, 0, SNDCC, "Send-Q");
	mvwaddstr(wnd, 0, STATE, "(state)"); 
}

I 9
void
E 9
shownetstat()
{
	register struct netinfo *p, *q;

	/*
	 * First, delete any connections that have gone
	 * away and adjust the position of connections
	 * below to reflect the deleted line.
	 */
	p = netcb.ni_forw;
	while (p != (struct netinfo *)&netcb) {
		if (p->ni_line == -1 || p->ni_seen) {
			p = p->ni_forw;
			continue;
		}
		wmove(wnd, p->ni_line, 0); wdeleteln(wnd);
		q = netcb.ni_forw;
		for (; q != (struct netinfo *)&netcb; q = q->ni_forw)
D 2
			if (q != p && q->ni_line > p->ni_line)
E 2
I 2
			if (q != p && q->ni_line > p->ni_line) {
E 2
				q->ni_line--;
I 2
				/* this shouldn't be necessary */
				q->ni_flags |= NIF_LACHG|NIF_FACHG;
			}
E 2
		lastrow--;
		q = p->ni_forw;
D 10
		remque(p);
		free((char *)p);
E 10
I 10
		p->ni_prev->ni_forw = p->ni_forw;
		p->ni_forw->ni_prev = p->ni_prev;
		free(p);
E 10
		p = q;
	}
D 2
	wmove(wnd, lastrow, 0); wclrtobot(wnd);
E 2
	/*
	 * Update existing connections and add new ones.
	 */
	for (p = netcb.ni_forw; p != (struct netinfo *)&netcb; p = p->ni_forw) {
		if (p->ni_line == -1) {
			/*
			 * Add a new entry if possible.
			 */
D 2
			if (lastrow >= wnd->_maxy)
E 2
I 2
			if (lastrow > YMAX(wnd))
E 2
				continue;
			p->ni_line = lastrow++;
			p->ni_flags |= NIF_LACHG|NIF_FACHG;
		}
		if (p->ni_flags & NIF_LACHG) {
			wmove(wnd, p->ni_line, LADDR);
			inetprint(&p->ni_laddr, p->ni_lport, p->ni_proto);
			p->ni_flags &= ~NIF_LACHG;
		}
		if (p->ni_flags & NIF_FACHG) {
			wmove(wnd, p->ni_line, FADDR);
			inetprint(&p->ni_faddr, p->ni_fport, p->ni_proto);
			p->ni_flags &= ~NIF_FACHG;
		}
		mvwaddstr(wnd, p->ni_line, PROTO, p->ni_proto);
		mvwprintw(wnd, p->ni_line, RCVCC, "%6d", p->ni_rcvcc);
		mvwprintw(wnd, p->ni_line, SNDCC, "%6d", p->ni_sndcc);
		if (streq(p->ni_proto, "tcp"))
			if (p->ni_state < 0 || p->ni_state >= TCP_NSTATES)
				mvwprintw(wnd, p->ni_line, STATE, "%d",
				    p->ni_state);
			else
				mvwaddstr(wnd, p->ni_line, STATE,
				    tcpstates[p->ni_state]);
		wclrtoeol(wnd);
	}
I 2
	if (lastrow < YMAX(wnd)) {
		wmove(wnd, lastrow, 0); wclrtobot(wnd);
		wmove(wnd, YMAX(wnd), 0); wdeleteln(wnd);	/* XXX */
	}
E 2
}

/*
 * Pretty print an Internet address (net address + port).
 * If the nflag was specified, use numbers instead of names.
 */
D 7
static
E 7
I 7
static void
E 7
inetprint(in, port, proto)
	register struct in_addr *in;
	int port;
	char *proto;
{
	struct servent *sp = 0;
	char line[80], *cp, *index();

	sprintf(line, "%.*s.", 16, inetname(*in));
	cp = index(line, '\0');
	if (!nflag && port)
		sp = getservbyport(port, proto);
	if (sp || port == 0)
		sprintf(cp, "%.8s", sp ? sp->s_name : "*");
	else
		sprintf(cp, "%d", ntohs((u_short)port));
	/* pad to full column to clear any garbage */
	cp = index(line, '\0');
	while (cp - line < 22)
		*cp++ = ' ';
	*cp = '\0';
	waddstr(wnd, line);
}

/*
 * Construct an Internet address representation.
 * If the nflag has been supplied, give 
 * numeric value, otherwise try for symbolic name.
 */
static char *
inetname(in)
	struct in_addr in;
{
	char *cp = 0;
	static char line[50];
	struct hostent *hp;
	struct netent *np;

	if (!nflag && in.s_addr != INADDR_ANY) {
		int net = inet_netof(in);
		int lna = inet_lnaof(in);

		if (lna == INADDR_ANY) {
			np = getnetbyaddr(net, AF_INET);
			if (np)
				cp = np->n_name;
		}
		if (cp == 0) {
D 8
			hp = gethostbyaddr(&in, sizeof (in), AF_INET);
E 8
I 8
			hp = gethostbyaddr((char *)&in, sizeof (in), AF_INET);
E 8
			if (hp)
				cp = hp->h_name;
		}
	}
	if (in.s_addr == INADDR_ANY)
		strcpy(line, "*");
	else if (cp)
		strcpy(line, cp);
	else {
		in.s_addr = ntohl(in.s_addr);
#define C(x)	((x) & 0xff)
		sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
	}
	return (line);
}

I 9
int
E 9
cmdnetstat(cmd, args)
D 5
        char *cmd, *args;
E 5
I 5
	char *cmd, *args;
E 5
{
	register struct netinfo *p;
D 2
	int omask;
E 2

D 2
	omask = sigblock(sigmask(SIGALRM));
E 2
	if (prefix(cmd, "all")) {
		aflag = !aflag;
		goto fixup;
	}
	if  (prefix(cmd, "numbers") || prefix(cmd, "names")) {
		int new;

		new = prefix(cmd, "numbers");
		if (new == nflag)
D 2
			goto done;
E 2
I 2
			return (1);
E 2
		p = netcb.ni_forw;
		for (; p != (struct netinfo *)&netcb; p = p->ni_forw) {
			if (p->ni_line == -1)
				continue;
			p->ni_flags |= NIF_LACHG|NIF_FACHG;
		}
		nflag = new;
		goto redisplay;
	}
D 2
	if (prefix(cmd, "tcp") || prefix(cmd, "udp")) {
		if (selectproto(cmd))
			goto fixup;
		goto done;
	}
	if (prefix(cmd, "protocol")) {
		if (selectproto(args))
			goto fixup;
		goto done;
	}
	if (prefix(cmd, "port")) {
		struct servent *sp;
		long port;

		sp = getservbyname(args,
			protos == TCP ? "tcp" : protos == UDP ? "udp" : 0);
		if (sp == 0) {
			port = atoi(args);
			if (port <= 0) {
				error("%s: unknown port", args);
				goto done;
			}
			port = htons((u_short)port);
		} else
			port = sp->s_port;
		if (selectport(port))
			goto fixup;
		goto done;
	}
	if (prefix(cmd, "host")) {
		struct hostent *hp;
		struct in_addr in;

		hp = gethostbyname(args);
		if (hp == 0) {
			in.s_addr = inet_addr(args);
			if (in.s_addr == -1) {
				error("%s: unknown host", args);
				goto done;
			}
		} else
			in = *(struct in_addr *)hp->h_addr;
		if (selecthost(&in))
			goto fixup;
		goto done;
	}
	if (prefix(cmd, "reset")) {
		if (selectproto(0) | selecthost(0) | selectport(-1))
			goto fixup;
		goto done;
	}
	sigsetmask(omask);
	return (0);
E 2
I 2
	if (!netcmd(cmd, args))
		return (0);
E 2
fixup:
	fetchnetstat();
redisplay:
	shownetstat();
	refresh();
D 2
done:
	sigsetmask(omask);
E 2
	return (1);
}
E 1
