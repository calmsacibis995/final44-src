h50706
s 00001/00001/00203
d D 8.3 94/04/02 10:02:26 pendry 10 9
c add 1994 copyright
e
s 00002/00002/00202
d D 8.2 94/04/01 03:39:14 pendry 9 8
c prettyness police
e
s 00002/00002/00202
d D 8.1 93/05/31 15:47:44 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00130/00129/00074
d D 5.7 93/04/29 15:17:59 bostic 7 6
c make GCC 2 happy
e
s 00002/00002/00201
d D 5.6 92/08/24 16:48:16 marc 6 5
c MDMBUF is a cflag!
e
s 00001/00002/00202
d D 5.5 92/07/10 11:12:47 marc 5 4
c remove xtabs synonym, and add -pass8 for orthogonality
e
s 00006/00000/00198
d D 5.4 91/06/10 07:39:45 bostic 4 3
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00043/00000/00155
d D 5.3 91/06/05 15:22:20 bostic 3 2
c distribute the rest of the main loop into the modes and cchars modules
c bsearch the cchars arrays, minor cleanups
e
s 00000/00001/00155
d D 5.2 91/06/04 17:42:46 bostic 2 1
c stty.h includes ioctl.h and termios.h; extern.h defines mode/char arrays
e
s 00156/00000/00000
d D 5.1 91/05/02 13:34:42 bostic 1 0
c date and time created 91/05/02 13:34:42 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 10
 * Copyright (c) 1991, 1993
E 10
I 10
 * Copyright (c) 1991, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 2
#include <termios.h>
E 2
#include <stddef.h>
I 3
#include <string.h>
E 3
#include "stty.h"

I 4
struct modes {
	char *name;
	long set;
	long unset;
};

E 4
/*
 * The code in optlist() depends on minus options following regular
 * options, i.e. "foo" must immediately precede "-foo".
 */
struct modes cmodes[] = {
D 7
	"cs5",		CS5, CSIZE,
	"cs6",		CS6, CSIZE,
	"cs7",		CS7, CSIZE,
	"cs8",		CS8, CSIZE,
	"cstopb",	CSTOPB, 0,
	"-cstopb",	0, CSTOPB,
	"cread",	CREAD, 0,
	"-cread",	0, CREAD,
	"parenb",	PARENB, 0,
	"-parenb",	0, PARENB,
	"parodd",	PARODD, 0,
	"-parodd",	0, PARODD,
	"parity",	PARENB | CS7, PARODD | CSIZE,
	"-parity",	CS8, PARODD | PARENB | CSIZE,
	"evenp",	PARENB | CS7, PARODD | CSIZE,
	"-evenp",	CS8, PARODD | PARENB | CSIZE,
	"oddp",		PARENB | CS7 | PARODD, CSIZE,
	"-oddp",	CS8, PARODD | PARENB | CSIZE,
	"pass8",	CS8, PARODD | PARENB | CSIZE,
I 5
	"-pass8",	PARENB | CS7, PARODD | CSIZE,
E 5
	"hupcl",	HUPCL, 0,
	"-hupcl",	0, HUPCL,
	"hup",		HUPCL, 0,
	"-hup",		0, HUPCL,
	"clocal",	CLOCAL, 0,
	"-clocal",	0, CLOCAL,
	"crtscts",	CRTSCTS, 0,
	"-crtscts",	0, CRTSCTS,
I 6
	"mdmbuf",	MDMBUF, 0,
	"-mdmbuf",	0, MDMBUF,
E 6
	NULL
E 7
I 7
	{ "cs5",	CS5, CSIZE },
	{ "cs6",	CS6, CSIZE },
	{ "cs7",	CS7, CSIZE },
	{ "cs8",	CS8, CSIZE },
	{ "cstopb",	CSTOPB, 0 },
	{ "-cstopb",	0, CSTOPB },
	{ "cread",	CREAD, 0 },
	{ "-cread",	0, CREAD },
	{ "parenb",	PARENB, 0 },
	{ "-parenb",	0, PARENB },
	{ "parodd",	PARODD, 0 },
	{ "-parodd",	0, PARODD },
	{ "parity",	PARENB | CS7, PARODD | CSIZE },
	{ "-parity",	CS8, PARODD | PARENB | CSIZE },
	{ "evenp",	PARENB | CS7, PARODD | CSIZE },
	{ "-evenp",	CS8, PARODD | PARENB | CSIZE },
	{ "oddp",	PARENB | CS7 | PARODD, CSIZE },
	{ "-oddp",	CS8, PARODD | PARENB | CSIZE },
	{ "pass8",	CS8, PARODD | PARENB | CSIZE },
	{ "-pass8",	PARENB | CS7, PARODD | CSIZE },
	{ "hupcl",	HUPCL, 0 },
	{ "-hupcl",	0, HUPCL },
	{ "hup",	HUPCL, 0 },
	{ "-hup",	0, HUPCL },
	{ "clocal",	CLOCAL, 0 },
	{ "-clocal",	0, CLOCAL },
	{ "crtscts",	CRTSCTS, 0 },
	{ "-crtscts",	0, CRTSCTS },
	{ "mdmbuf",	MDMBUF, 0 },
	{ "-mdmbuf",	0, MDMBUF },
	{ NULL },
E 7
};

struct modes imodes[] = {
D 7
	"ignbrk",	IGNBRK, 0,
	"-ignbrk",	0, IGNBRK,
	"brkint",	BRKINT, 0,
	"-brkint",	0, BRKINT,
	"ignpar",	IGNPAR, 0,
	"-ignpar",	0, IGNPAR,
	"parmrk",	PARMRK, 0,
	"-parmrk",	0, PARMRK,
	"inpck",	INPCK, 0,
	"-inpck",	0, INPCK,
	"istrip",	ISTRIP, 0,
	"-istrip",	0, ISTRIP,
	"inlcr",	INLCR, 0,
	"-inlcr",	0, INLCR,
	"igncr",	IGNCR, 0,
	"-igncr",	0, IGNCR,
	"icrnl",	ICRNL, 0,
	"-icrnl",	0, ICRNL,
	"ixon",		IXON, 0,
	"-ixon",	0, IXON,
	"flow",		IXON, 0,
	"-flow",	0, IXON,
	"ixoff",	IXOFF, 0,
	"-ixoff",	0, IXOFF,
	"tandem",	IXOFF, 0,
	"-tandem",	0, IXOFF,
	"ixany",	IXANY, 0,
	"-ixany",	0, IXANY,
	"decctlq",	0, IXANY,
	"-decctlq",	IXANY, 0,
	"imaxbel",	IMAXBEL, 0,
	"-imaxbel",	0, IMAXBEL,
	NULL
E 7
I 7
	{ "ignbrk",	IGNBRK, 0 },
	{ "-ignbrk",	0, IGNBRK },
	{ "brkint",	BRKINT, 0 },
	{ "-brkint",	0, BRKINT },
	{ "ignpar",	IGNPAR, 0 },
	{ "-ignpar",	0, IGNPAR },
	{ "parmrk",	PARMRK, 0 },
	{ "-parmrk",	0, PARMRK },
	{ "inpck",	INPCK, 0 },
	{ "-inpck",	0, INPCK },
	{ "istrip",	ISTRIP, 0 },
	{ "-istrip",	0, ISTRIP },
	{ "inlcr",	INLCR, 0 },
	{ "-inlcr",	0, INLCR },
	{ "igncr",	IGNCR, 0 },
	{ "-igncr",	0, IGNCR },
	{ "icrnl",	ICRNL, 0 },
	{ "-icrnl",	0, ICRNL },
	{ "ixon",	IXON, 0 },
	{ "-ixon",	0, IXON },
	{ "flow",	IXON, 0 },
	{ "-flow",	0, IXON },
	{ "ixoff",	IXOFF, 0 },
	{ "-ixoff",	0, IXOFF },
	{ "tandem",	IXOFF, 0 },
	{ "-tandem",	0, IXOFF },
	{ "ixany",	IXANY, 0 },
	{ "-ixany",	0, IXANY },
	{ "decctlq",	0, IXANY },
	{ "-decctlq",	IXANY, 0 },
	{ "imaxbel",	IMAXBEL, 0 },
	{ "-imaxbel",	0, IMAXBEL },
	{ NULL },
E 7
};

struct modes lmodes[] = {
D 7
	"echo",		ECHO, 0,
	"-echo",	0, ECHO,
	"echoe",	ECHOE, 0,
	"-echoe",	0, ECHOE,
	"crterase",	ECHOE, 0,
	"-crterase",	0, ECHOE,
	"crtbs",	ECHOE, 0,   /* crtbs not supported, close enough */
	"-crtbs",	0, ECHOE,
	"echok",	ECHOK, 0,
	"-echok",	0, ECHOK,
	"echoke",	ECHOKE, 0,
	"-echoke",	0, ECHOKE,
	"crtkill",	ECHOKE, 0,
	"-crtkill",	0, ECHOKE,
	"altwerase",	ALTWERASE, 0,
	"-altwerase",	0, ALTWERASE,
	"iexten",	IEXTEN, 0,
	"-iexten",	0, IEXTEN,
	"echonl",	ECHONL, 0,
	"-echonl",	0, ECHONL,
	"echoctl",	ECHOCTL, 0,
	"-echoctl",	0, ECHOCTL,
	"ctlecho",	ECHOCTL, 0,
	"-ctlecho",	0, ECHOCTL,
	"echoprt",	ECHOPRT, 0,
	"-echoprt",	0, ECHOPRT,
	"prterase",	ECHOPRT, 0,
	"-prterase",	0, ECHOPRT,
	"isig",		ISIG, 0,
	"-isig",	0, ISIG,
	"icanon",	ICANON, 0,
	"-icanon",	0, ICANON,
	"noflsh",	NOFLSH, 0,
	"-noflsh",	0, NOFLSH,
	"tostop",	TOSTOP, 0,
	"-tostop",	0, TOSTOP,
D 6
	"mdmbuf",	MDMBUF, 0,
	"-mdmbuf",	0, MDMBUF,
E 6
	"flusho",	FLUSHO, 0,
	"-flusho",	0, FLUSHO,
	"pendin",	PENDIN, 0,
	"-pendin",	0, PENDIN,
	"crt",		ECHOE|ECHOKE|ECHOCTL, ECHOK|ECHOPRT,
	"-crt",		ECHOK, ECHOE|ECHOKE|ECHOCTL,
	"newcrt",	ECHOE|ECHOKE|ECHOCTL, ECHOK|ECHOPRT,
	"-newcrt",	ECHOK, ECHOE|ECHOKE|ECHOCTL, 
	"nokerninfo",	NOKERNINFO, 0,
	"-nokerninfo",	0, NOKERNINFO,
	"kerninfo",	0, NOKERNINFO,
	"-kerninfo",	NOKERNINFO, 0,
	NULL
E 7
I 7
	{ "echo",	ECHO, 0 },
	{ "-echo",	0, ECHO },
	{ "echoe",	ECHOE, 0 },
	{ "-echoe",	0, ECHOE },
	{ "crterase",	ECHOE, 0 },
	{ "-crterase",	0, ECHOE },
	{ "crtbs",	ECHOE, 0 },	/* crtbs not supported, close enough */
	{ "-crtbs",	0, ECHOE },
	{ "echok",	ECHOK, 0 },
	{ "-echok",	0, ECHOK },
	{ "echoke",	ECHOKE, 0 },
	{ "-echoke",	0, ECHOKE },
	{ "crtkill",	ECHOKE, 0 },
	{ "-crtkill",	0, ECHOKE },
	{ "altwerase",	ALTWERASE, 0 },
	{ "-altwerase",	0, ALTWERASE },
	{ "iexten",	IEXTEN, 0 },
	{ "-iexten",	0, IEXTEN },
	{ "echonl",	ECHONL, 0 },
	{ "-echonl",	0, ECHONL },
	{ "echoctl",	ECHOCTL, 0 },
	{ "-echoctl",	0, ECHOCTL },
	{ "ctlecho",	ECHOCTL, 0 },
	{ "-ctlecho",	0, ECHOCTL },
	{ "echoprt",	ECHOPRT, 0 },
	{ "-echoprt",	0, ECHOPRT },
	{ "prterase",	ECHOPRT, 0 },
	{ "-prterase",	0, ECHOPRT },
	{ "isig",	ISIG, 0 },
	{ "-isig",	0, ISIG },
	{ "icanon",	ICANON, 0 },
	{ "-icanon",	0, ICANON },
	{ "noflsh",	NOFLSH, 0 },
	{ "-noflsh",	0, NOFLSH },
	{ "tostop",	TOSTOP, 0 },
	{ "-tostop",	0, TOSTOP },
	{ "flusho",	FLUSHO, 0 },
	{ "-flusho",	0, FLUSHO },
	{ "pendin",	PENDIN, 0 },
	{ "-pendin",	0, PENDIN },
	{ "crt",	ECHOE|ECHOKE|ECHOCTL, ECHOK|ECHOPRT },
	{ "-crt",	ECHOK, ECHOE|ECHOKE|ECHOCTL },
	{ "newcrt",	ECHOE|ECHOKE|ECHOCTL, ECHOK|ECHOPRT },
	{ "-newcrt",	ECHOK, ECHOE|ECHOKE|ECHOCTL },
	{ "nokerninfo",	NOKERNINFO, 0 },
	{ "-nokerninfo",0, NOKERNINFO },
	{ "kerninfo",	0, NOKERNINFO },
	{ "-kerninfo",	NOKERNINFO, 0 },
	{ NULL },
E 7
};

struct modes omodes[] = {
D 7
	"opost",	OPOST, 0,
	"-opost",	0, OPOST,
	"litout",	0, OPOST,
	"-litout",	OPOST, 0,
	"onlcr",	ONLCR, 0,
	"-onlcr",	0, ONLCR,
	"tabs",		0, OXTABS,	/* "preserve" tabs */
	"-tabs",	OXTABS, 0,
D 5
	"xtabs",	OXTABS, 0,
	"-xtabs",	0, OXTABS,
E 5
	"oxtabs",	OXTABS, 0,
	"-oxtabs",	0, OXTABS,
	NULL
E 7
I 7
	{ "opost",	OPOST, 0 },
	{ "-opost",	0, OPOST },
	{ "litout",	0, OPOST },
	{ "-litout",	OPOST, 0 },
	{ "onlcr",	ONLCR, 0 },
	{ "-onlcr",	0, ONLCR },
	{ "tabs",	0, OXTABS },		/* "preserve" tabs */
	{ "-tabs",	OXTABS, 0 },
	{ "oxtabs",	OXTABS, 0 },
	{ "-oxtabs",	0, OXTABS },
	{ NULL },
E 7
};
I 3

#define	CHK(s)	(*name == s[0] && !strcmp(name, s))

I 7
int
E 7
msearch(argvp, ip)
	char ***argvp;
	struct info *ip;
{
D 9
	register struct modes *mp;
	register char *name;
E 9
I 9
	struct modes *mp;
	char *name;
E 9

	name = **argvp;

	for (mp = cmodes; mp->name; ++mp)
		if (CHK(mp->name)) {
			ip->t.c_cflag &= ~mp->unset;
			ip->t.c_cflag |= mp->set;
			ip->set = 1;
D 7
			return(1);
E 7
I 7
			return (1);
E 7
		}
	for (mp = imodes; mp->name; ++mp)
		if (CHK(mp->name)) {
			ip->t.c_iflag &= ~mp->unset;
			ip->t.c_iflag |= mp->set;
			ip->set = 1;
D 7
			return(1);
E 7
I 7
			return (1);
E 7
		}
	for (mp = lmodes; mp->name; ++mp)
		if (CHK(mp->name)) {
			ip->t.c_lflag &= ~mp->unset;
			ip->t.c_lflag |= mp->set;
			ip->set = 1;
D 7
			return(1);
E 7
I 7
			return (1);
E 7
		}
	for (mp = omodes; mp->name; ++mp)
		if (CHK(mp->name)) {
			ip->t.c_oflag &= ~mp->unset;
			ip->t.c_oflag |= mp->set;
			ip->set = 1;
D 7
			return(1);
E 7
I 7
			return (1);
E 7
		}
D 7
	return(0);
E 7
I 7
	return (0);
E 7
}
E 3
E 1
