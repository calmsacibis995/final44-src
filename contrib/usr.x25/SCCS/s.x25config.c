h26029
s 00013/00002/00382
d D 5.3 93/04/25 23:29:10 sklower 3 2
c changes needed for 802.2 support from dkhusema
e
s 00026/00021/00358
d D 5.2 91/04/29 18:49:19 sklower 2 1
c versions for networking tape 2
e
s 00379/00000/00000
d D 5.1 90/09/03 18:55:37 sklower 1 0
c date and time created 90/09/03 18:55:37 by sklower
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
/*
E 2
 * Configure X.25 interface
 *
 * Copyright (c) 1986 University of British Columbia
 *
 * Frank Pronk
 * February 1986
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <netccitt/x25.h>

#include <stdio.h>
#include <netdb.h>

#define	IFFBITS \
"\020\1UP\2BROADCAST\3DEBUG\4ROUTE\5POINTOPOINT\6NOTRAILERS\7RUNNING\10NOARP"

int	setifflags (), setdefault (), setnet (), setntn ();
D 3
int	setlproto (), sethdlc (), setlwsize (), setltrace ();
E 3
I 3
int	setlproto (), sethdlc (), setlwsize (), setlkeepalive (), setltrace ();
E 3
int	setyear (), setpwsize (), setpacketsize (), setmaxlcn (), setptrace ();

struct	cmd {
	char	*c_name;
	int	c_arg;
	int	(*c_func) ();
} cmds[] = {
	"up",		IFF_UP,			setifflags,
	"-up",		-IFF_UP,		setifflags,
	"down",		-IFF_UP,		setifflags,
	"debug",	IFF_DEBUG,		setifflags,
	"-debug",	-IFF_DEBUG,		setifflags,
	"default",	0,			setdefault,
	"hdlc",		CCITTPROTO_HDLC,	setlproto,
	"ieee802llc",	IEEEPROTO_802LLC,	setlproto,
I 3
	"llc2",		IEEEPROTO_802LLC,	setlproto,
E 3
	"lap",		HDLCPROTO_LAP,		sethdlc,
	"lapb",		HDLCPROTO_LAPB,		sethdlc,
	"lapd",		HDLCPROTO_LAPD,		sethdlc,
	"unset",	HDLCPROTO_UNSET,	sethdlc,
	"-ltrace",	0,			setltrace,
	"ltrace",	1,			setltrace,
I 3
	"keepalive",	1,			setlkeepalive,
	"-keepalive",	0,			setlkeepalive,
E 3

	"1976",		X25_1976,		setyear,
	"1980",		X25_1980,		setyear,
	"1984",		X25_1984,		setyear,
	"-ptrace",	0,			setptrace,
	"ptrace",	1,			setptrace,

	"-net",		0,			setnet,
	"-ntn",		0,			setntn,
	"-lwsize",	0,			setlwsize,
	"-pwsize",	0,			setpwsize,
	"-psize",	0,			setpacketsize,
	"-maxlcn",	0,			setmaxlcn,
	0,		0,			0
};

struct	ifreq ifr;
D 2
struct	x25config x25conf = { AF_CCITT };
E 2
I 2
struct	ifreq_x25 ifrx25;
#define x25conf ifrx25.ifr_xc
E 2

char	*myname;
char	*ifname;	/* interface name */
short	ifflags;	/* local copy of interface flags */

main (argc, argv)
register char **argv;
int argc;
{
	register int s;

	myname = *argv;
	if (argc < 2)
		abort ("usage: x25ifconfig interface [default] [-net net] [-ntn ntn] [-maxlcn maxlcn] [up] [down] [zillions of other options]");

	if ((s = socket (AF_CCITT, SOCK_STREAM, 0)) < 0)
		syserr ("socket");
	argv[argc] = 0;
	argv++;

	ifname = *argv;
	strcpy (ifr.ifr_name, ifname);
	if (ioctl (s, SIOCGIFFLAGS, (char *)&ifr) < 0)
		syserr ("ioctl (SIOCGIFFLAGS)");
	ifflags = ifr.ifr_flags;
D 2
	strcpy (ifr.ifr_name, ifname);
	if (ioctl (s, SIOCGIFADDR, (char *)&ifr) == 0)
		bcopy ((char *)&ifr.ifr_addr, (char *)&x25conf, sizeof (x25conf));

E 2
I 2
	strcpy (ifrx25.ifr_name, ifname);
	if (ioctl (s, SIOCGIFCONF_X25, (char *)&ifrx25) < 0) {
		x25conf.xc_addr.x25_len = sizeof(x25conf);
		x25conf.xc_addr.x25_family = AF_CCITT;
	}
E 2
	if (argc == 2) {
		status ();
		exit (0);
	}
D 2

E 2
	argv++;
	while (*argv) {
		register struct cmd *cp;
		register int argneeded;

		argneeded = 0;
		for (cp = cmds; ; cp++) {
			if (cp->c_name == 0)
				abort ("invalid argument: %s", *argv);
			if (cp->c_func == setnet)
				argneeded++;
			if (strcmp (cp->c_name, *argv) == 0) {
				if (argneeded) {
					if (argv[1]) {
						argv++;
						(*cp->c_func) (*argv);
					} else
						abort ("argument expect after %s", *argv);
				} else
					(*cp->c_func) (cp->c_arg);
				break;
			}
		}
		argv++;
	}
	ifr.ifr_flags = ifflags;
	strcpy (ifr.ifr_name, ifname);
	if (ioctl (s, SIOCSIFFLAGS, (char *)&ifr) < 0)
		syserr ("ioctl (SIOCSIFFLAGS)");

D 2
	strcpy (ifr.ifr_name, ifname);
	bcopy ((char *)&x25conf, (char *)&ifr.ifr_addr, sizeof (x25conf));
	if (ioctl (s, SIOCSIFADDR, (char *)&ifr) < 0)
		syserr ("ioctl (SIOCSIFADDR)");
E 2
I 2
	strcpy (ifrx25.ifr_name, ifname);
	if (ioctl (s, SIOCSIFCONF_X25, (char *)&ifrx25) < 0)
		syserr ("ioctl (SIOCSIFCONF_X25)");
E 2
	exit (0);
}

/* VARARGS */
abort (fmt, a1, a2, a3, a4, a5)
char *fmt;
{
	char buf[128];

	sprintf (buf, "%s: %s\n", myname, fmt);
	fprintf (stderr, buf, a1, a2, a3, a4, a5);
	exit (1);
}

/* VARARGS */
syserr (fmt, a1, a2, a3, a4, a5)
char *fmt;
{
	char buf[128];
	extern int errno;
	extern char *sys_errlist[];

	sprintf (buf, "%s: %s: %s\n", myname, fmt, sys_errlist[errno]);
	fprintf (stderr, buf, a1, a2, a3, a4, a5);
	exit (1);
}

status ()
{
D 2
	char addr[sizeof (x25conf.xc_ntn) * 2 + 1];
E 2
I 2
	char *addr = x25conf.xc_addr.x25_addr;
E 2

	printf ("%s: ", ifname);
	printb ("interface flags", ifflags, IFFBITS);
	printf ("link level:\n");
	printf ("\twindow size: %d\n", x25conf.xc_lwsize);
	if (x25conf.xc_ltrace)
		printf ("\ttracing: on\n");
	printf ("\npacket level:\n");
D 2
	from_bcd (x25conf.xc_ntn, addr, x25conf.xc_ntnlen);
	printf ("\taddress: %04d %s\n", x25conf.xc_net, addr);
E 2
I 2
	printf ("\taddress: %04d %s\n", x25conf.xc_addr.x25_net, addr);
E 2
	printf ("\twindow size: %d\n", x25conf.xc_pwsize);
	printf ("\tpacket size: %d\n", 1 << x25conf.xc_psize);
	printf ("\tmax lcn: %d\n", x25conf.xc_maxlcn);
	if (x25conf.xc_ptrace)
		printf ("\ttracing: on\n");
}

setifflags (value)
{

	if (value < 0) {
		value = -value;
		ifflags &= ~value;
	} else
		ifflags |= value;
}

/* VARARGS */
setdefault (arg)
{

D 2
	x25conf.xc_family = AF_CCITT;
E 2
I 2
	x25conf.xc_addr.x25_family = AF_CCITT;
E 2
	x25conf.xc_lproto = CCITTPROTO_HDLC;
	x25conf.xc_lptype = HDLCPROTO_LAPB;
	x25conf.xc_lwsize = 7;

	x25conf.xc_pwsize = 2;
	x25conf.xc_psize = X25_PS128;
	x25conf.xc_type = X25_1976;
}

setnet (arg)
char *arg;
{
	register int net;
	register struct netent *np;

	if (*arg < '0' || *arg > '9') {	/* lookup name in /etc/networks */
		if ((np = getnetbyname (arg)) == 0)
			abort ("unknown network (%s)", arg);
		net = np->n_net;
	} else
		net = atoi (arg);
D 2
	x25conf.xc_net = net;
E 2
I 2
	x25conf.xc_addr.x25_net = net;
E 2
}

setntn (arg)
register char *arg;
{
	register int l;
	register char *p;
	register struct hostent *hp;
	struct hostent *getx25hostbyname ();

	if (*arg < '0' || *arg > '9') {	/* lookup in /etc/x25hosts */
		if ((hp = getx25hostbyname (arg)) == 0)
			abort ("can't find '%s' in /etc/x25hosts", arg);
		arg = ((struct sockaddr_x25 *)hp->h_addr)->x25_addr;
D 2
		l = strlen (arg);
E 2
I 2
		l = strlen (arg) + 1;
E 2
	} else
D 2
		for (l = 0, p = arg; *p; p++) {
E 2
I 2
		for (l = 1, p = arg; *p; p++) {
E 2
			l++;
			if (*p < '0' || *p > '9')
				abort ("invalid character in ntn address");
		}
D 2
	if (l > sizeof (x25conf.xc_ntn) * 2 || l == 0)
E 2
I 2
	if (l > sizeof (x25conf.xc_addr.x25_addr))
E 2
		abort ("invalid ntn address");
D 2

	x25conf.xc_ntnlen = l;
	to_bcd (arg, x25conf.xc_ntn);
E 2
I 2
	bcopy(arg, x25conf.xc_addr.x25_addr, l);
E 2
}

to_bcd (src, dest)
register char *src, *dest;
{
	register int i;

	for(i = 0; *src; i++)	
		if (i & 0x01 )
			*dest++ |= *src++ & 0x0F;
		else
			*dest = *src++ << 4;
}

from_bcd (src, dest, len)
char *src, *dest;
{
	register int i;

	for (i = 0; i < len/2; i++) {
		*dest++ = ((*src & 0xf0) >> 4) + '0';
		*dest++ = (*src++ & 0xf) + '0';
	}
	*dest = 0;
}

setlproto (arg)
{
	x25conf.xc_lproto = arg;
}

sethdlc (arg)
{
	x25conf.xc_lptype = arg;
}

setlwsize (arg)
char *arg;
{
	register int ws;

D 3
	if ((ws = atoi (arg)) <= 0 || ws > 31)
E 3
I 3
	if ((ws = atoi (arg)) <= 0 || 
	    ( ws > 31 && x25conf.xc_lproto != IEEEPROTO_802LLC ) 
	    || ws > 127)
E 3
		abort ("invalid link level window size");
	x25conf.xc_lwsize = ws;
I 3
}

setlkeepalive (arg)
int arg;
{
	/* x25conf.xc_lkeepalive = arg; */
E 3
}

setltrace (arg)
{
	x25conf.xc_ltrace = arg;
}

setyear (arg)
{
	x25conf.xc_type = arg;
	switch (arg) {
	case X25_1976:
		return;

	case X25_1980:
	case X25_1984:
		x25conf.xc_pwsize = 7;
		x25conf.xc_psize = 12;		/* 4096 bytes */
	}
}

setpwsize (arg)
char *arg;
{
	register int ws;

	if ((ws = atoi (arg)) <= 0 || ws > 7)
		abort ("invalid packet level window size");
	x25conf.xc_pwsize = ws;
}

setpacketsize (arg)
char *arg;
{
	register int psize, logpsize = 0;

	if ((psize = atoi (arg)) < 64 || psize > 4096)
		abort ("invalid packet size");
	while (psize > 1) {
		psize >>= 1;
		logpsize++;
	}
	x25conf.xc_psize = logpsize;
}

setmaxlcn (arg)
char *arg;
{
	register int lcn;

	if ((lcn = atoi (arg)) <= 0)
		abort ("invalid maximum lcn");
	x25conf.xc_maxlcn = lcn;
}

setptrace (arg)
{
	x25conf.xc_ptrace = arg;
}

/*
 * Print a value a la the %b format of the kernel's printf
 */

printb(s, v, bits)
	char *s;
	register char *bits;
	register unsigned short v;
{
	register int i, any = 0;
	register char c;

	if (bits && *bits == 8)
		printf("%s=%o", s, v);
	else
		printf("%s=%x", s, v);
	bits++;
	if (bits) {
		putchar('<');
		while (i = *bits++) {
			if (v & (1 << (i-1))) {
				if (any)
					putchar(',');
				any = 1;
				for (; (c = *bits) > 32; bits++)
					putchar(c);
			} else
				for (; *bits > 32; bits++)
					;
		}
		putchar('>');
		putchar('\n');
	}
}
E 1
