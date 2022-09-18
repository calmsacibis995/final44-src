h23151
s 00019/00024/00634
d D 8.2 94/02/16 12:03:02 bostic 43 42
c if an arg is expected but none suppled, null deref happens.
c netmask should be printed with a leading 0x, so that output from ifconfig
c can be used as input, too.
c fprintf/exit combinations converted to use err()
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00005/00005/00653
d D 8.1 93/06/05 10:59:13 bostic 42 41
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00006/00645
d D 5.8 92/07/08 15:37:06 sklower 41 40
c multicast bit needs to be printed & we are obsoleteing trailers
e
s 00001/00001/00650
d D 5.7 92/03/06 12:41:15 bostic 40 39
c typo, LINK1 and lINK2 have the same value in the IFFBITS string
e
s 00001/00001/00650
d D 5.6 92/02/14 16:45:06 karels 39 38
c change the rest of the llc? strings
e
s 00007/00007/00644
d D 5.5 92/02/12 12:34:36 sklower 38 37
c change -llc<n> to -link<n>
e
s 00004/00030/00647
d D 5.4 91/10/16 14:59:27 william 37 36
c oops, dropped the keywords, put them back in
e
s 00040/00007/00637
d D 5.3 91/10/16 14:43:45 william 36 35
c added three new flags for link layer control (LLC) 
c this can be used to enable slip compression and other LL options.
e
s 00002/00002/00642
d D 5.2 91/10/15 15:54:56 sklower 35 34
c report other bits beyond IFF_NOARP (from jch)
e
s 00006/00003/00638
d D 5.1 91/02/28 17:46:51 bostic 34 33
c ANSI
e
s 00000/00001/00641
d D 4.30 90/06/14 16:30:10 sklower 33 32
c changed my mind once again about interpretation of nsels
e
s 00029/00019/00613
d D 4.29 90/06/12 17:29:40 sklower 32 31
c changed my mind.  Ifconfig should set NSAP not NET
e
s 00031/00013/00601
d D 4.28 90/06/07 16:08:13 sklower 31 30
c add nsellength processing for GOSIP, default 1;
c fix bugs in iso_status().
e
s 00001/00011/00613
d D 4.27 90/06/01 16:17:17 bostic 30 29
c new copyright notice
e
s 00001/00011/00623
d D 4.26 90/04/06 15:47:58 sklower 29 28
c ISO ip encapsulation targets set by route rather than ifconfig
e
s 00011/00022/00623
d D 4.25 89/09/25 12:55:03 sklower 28 27
c ssufixlen --> slen; fix other minor bugs concerning masks.
e
s 00036/00017/00609
d D 4.24 89/04/22 12:35:59 sklower 27 26
c iso/IP stuff works, fix bug in that ifconfig up deletes primary inet address.
e
s 00177/00057/00449
d D 4.23 89/04/07 17:43:23 sklower 26 25
c checkpoint working iso code; start adding iso/ip encapsulation
e
s 00005/00003/00501
d D 4.22 89/03/23 12:06:38 sklower 25 24
c base level changes for var length sockaddrs
e
s 00015/00004/00489
d D 4.21 88/07/01 08:36:50 bostic 24 23
c written by Sam Leffler; add Berkeley specific copyright
e
s 00001/00001/00492
d D 4.20 87/04/06 11:34:30 bostic 23 22
c fprintf format/argument mismatch
e
s 00001/00001/00492
d D 4.19 87/03/29 16:14:37 mckusick 22 21
c fix errorneous error message from ifconfig (tef@cgl.ucsf.edu (Tom Ferrin))
e
s 00032/00024/00461
d D 4.18 86/05/22 16:07:01 karels 21 20
c cleanup status for uninitialized interfaces
e
s 00009/00010/00476
d D 4.17 86/04/12 22:04:15 karels 20 19
c logic error; zero netmask when setting new addr
e
s 00001/00001/00485
d D 4.16 86/02/27 00:40:05 karels 19 16
c off by one
e
s 00011/00005/00481
d R 4.16 86/02/26 17:10:05 karels 18 16
c kernel now wants dstaddr set after local addr
e
s 00009/00003/00483
d R 4.16 86/02/26 16:14:22 karels 17 16
c kernel now wants dstaddr set after local addr
e
s 00035/00019/00451
d D 4.15 86/02/16 21:08:45 karels 16 15
c add if metric, rm local, separate af-dependent and -independent
e
s 00015/00054/00455
d D 4.14 86/02/07 10:25:08 sklower 15 14
c a.) list other end of pt to pt xns interfaces. 
c b.) use standard routines to print and convert xns addresses. (from libc)
e
s 00004/00004/00505
d D 4.13 85/08/10 14:11:52 sklower 14 12
c Fix two bugs: 1.) wrong sizeof for name 2.) if ns not configured 
c Don't barf when asked to report status.
e
s 00001/00002/00507
d R 4.13 85/07/13 12:05:52 sklower 13 12
c fix bug introduced last rev that limited if names to 4 chars.
e
s 00208/00041/00301
d D 4.12 85/06/06 11:00:12 sklower 12 11
c Include Maryland XNS changes
e
s 00111/00026/00231
d D 4.11 85/06/03 09:32:53 karels 11 10
c netmask stuff
e
s 00002/00000/00255
d D 4.10 84/10/17 13:00:46 tef 10 9
c must save and restore flags when dest addr is set.
e
s 00024/00002/00231
d D 4.9 84/09/26 09:35:42 tef 9 8
c allow dest addr to be set on point-to-point interfaces; 
c report dest addr during status printout
e
s 00001/00001/00232
d D 4.8 84/08/02 00:30:38 lepreau 8 7
c missing arg to an fprintf
e
s 00020/00019/00213
d D 4.7 84/04/10 21:46:16 karels 7 6
c add `local' option; set address last always
e
s 00010/00000/00222
d D 4.6 83/11/07 14:01:54 karels 6 5
c need to reread flags after setting address (interface may add new flags)
e
s 00006/00005/00216
d D 4.5 83/11/02 09:51:21 karels 5 4
c correct sense of arp; report state of arp; handle multiple flags
c (from Tom Lyons)
e
s 00002/00000/00219
d D 4.4 83/10/23 23:51:02 leres 4 3
c Add support for changing the IFF_DEBUG bit
e
s 00005/00000/00214
d D 4.3 83/09/16 18:39:22 sam 3 2
c show stanford how to add swabip crap
e
s 00003/00003/00211
d D 4.2 83/08/28 02:01:35 sam 2 1
c oops
e
s 00214/00000/00000
d D 4.1 83/08/28 00:37:35 sam 1 0
c date and time created 83/08/28 00:37:35 by sam
e
u
U
t
T
I 11
/*
D 37
 * Copyright (c) 1983 Regents of the University of California.
E 37
I 37
D 42
 * Copyright (c) 1983 The Regents of the University of California.
E 37
D 24
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 24
I 24
 * All rights reserved.
E 42
I 42
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 42
 *
D 30
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
E 30
I 30
D 36
 * %sccs.include.redist.c%
E 36
I 36
D 37
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
 *
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
E 37
I 37
 * %sccs.include.redist.c%
E 37
E 36
E 30
E 24
 */

E 11
I 1
#ifndef lint
I 11
D 42
char copyright[] =
D 36
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 36
I 36
D 37
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 37
I 37
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 37
E 36
 All rights reserved.\n";
E 42
I 42
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 42
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24

#ifndef lint
E 11
D 36
static char sccsid[] = "%W% (Berkeley) %G%";
E 36
I 36
D 37
static char sccsid[] = "@(#)ifconfig.c	5.1 (Berkeley) 2/28/91";
E 37
I 37
static char sccsid[] = "%W% (Berkeley) %G%";
E 37
E 36
D 11
#endif
E 11
I 11
D 24
#endif not lint
E 24
I 24
#endif /* not lint */
E 24
E 11

I 11
D 14

E 14
E 11
D 34
#include <sys/types.h>
E 34
I 34
#include <sys/param.h>
E 34
#include <sys/socket.h>
#include <sys/ioctl.h>

D 12
#include <netinet/in.h>
E 12
#include <net/if.h>
I 12
#include <netinet/in.h>
I 34
#include <arpa/inet.h>
E 34
E 12

I 12
#define	NSIP
#include <netns/ns.h>
#include <netns/ns_if.h>
I 34
#include <netdb.h>
E 34

I 27
#define EON
E 27
I 26
#include <netiso/iso.h>
#include <netiso/iso_var.h>
I 27
#include <sys/protosw.h>
D 29
#include <netiso/eonvar.h>
E 29
E 27

I 34
D 43
#include <unistd.h>
E 34
E 26
E 12
#include <stdio.h>
#include <errno.h>
E 43
#include <ctype.h>
I 43
#include <err.h>
#include <errno.h>
#include <stdio.h>
E 43
D 34
#include <netdb.h>
E 34
I 34
#include <stdlib.h>
#include <string.h>
I 43
#include <unistd.h>
E 43
E 34

I 12
D 34
extern int errno;
E 34
E 12
D 26
struct	ifreq ifr;
D 25
struct	sockaddr_in sin = { AF_INET };
E 25
I 25
struct	sockaddr_in sin = { sizeof(sin), AF_INET };
E 25
I 11
struct	sockaddr_in broadaddr;
D 25
struct	sockaddr_in netmask = { AF_INET };
I 12
struct	sockaddr_in ipdst = { AF_INET };
E 25
I 25
struct	sockaddr_in netmask = {sizeof(sin),  AF_INET };
struct	sockaddr_in ipdst = {sizeof(sin),  AF_INET };
E 26
I 26
struct	ifreq		ifr, ridreq;
struct	ifaliasreq	addreq;
struct	iso_ifreq	iso_ridreq;
D 31
struct	iso_aliasreq	iso_addreq;
E 31
I 31
D 32
struct	iso_aliasreq	iso_addreq = {"", {0,0,0,0,1}}; /* default nsellen = 1*/
E 32
I 32
struct	iso_aliasreq	iso_addreq;
E 32
E 31
struct	sockaddr_in	netmask;

E 26
E 25
E 12
E 11
char	name[30];
I 11
int	flags;
I 16
int	metric;
I 32
int	nsellength = 1;
E 32
E 16
E 11
D 7
int	flags;
E 7
I 7
int	setaddr;
I 11
D 26
int	setmask;
int	setbroadaddr;
E 26
I 12
int	setipdst;
I 26
int	doalias;
D 27
int	clearaddr = 1;
E 27
I 27
int	clearaddr;
E 27
int	newaddr = 1;
E 26
E 12
E 11
E 7
int	s;
I 11
extern	int errno;
E 11

D 9
int	setifflags(), setifaddr();
E 9
I 9
D 11
int	setifflags(), setifaddr(), setifdstaddr();
E 11
I 11
int	setifflags(), setifaddr(), setifdstaddr(), setifnetmask();
D 12
int	setifbroadaddr();
E 12
I 12
D 16
int	setifbroadaddr(), setifipdst();
E 16
I 16
int	setifmetric(), setifbroadaddr(), setifipdst();
I 26
D 31
int	notealias(), setsnpaoffset();
E 31
I 31
D 41
int	notealias(), setsnpaoffset(), setnsellength();
E 41
I 41
int	notealias(), setsnpaoffset(), setnsellength(), notrailers();
E 41
E 31
E 26
E 16
E 12
E 11
E 9

I 11
#define	NEXTARG		0xffffff

E 11
struct	cmd {
	char	*c_name;
D 11
	int	c_parameter;
E 11
I 11
	int	c_parameter;		/* NEXTARG means next argv */
E 11
	int	(*c_func)();
} cmds[] = {
	{ "up",		IFF_UP,		setifflags } ,
	{ "down",	-IFF_UP,	setifflags },
D 41
	{ "trailers",	-IFF_NOTRAILERS,setifflags },
	{ "-trailers",	IFF_NOTRAILERS,	setifflags },
E 41
I 41
	{ "trailers",	-1,		notrailers },
	{ "-trailers",	1,		notrailers },
E 41
D 5
	{ "arp",	IFF_NOARP,	setifflags },
	{ "-arp",	-IFF_NOARP,	setifflags },
E 5
I 5
	{ "arp",	-IFF_NOARP,	setifflags },
	{ "-arp",	IFF_NOARP,	setifflags },
I 11
D 16
#ifdef IFF_LOCAL
E 11
I 7
	{ "local",	IFF_LOCAL,	setifflags },
	{ "-local",	-IFF_LOCAL,	setifflags },
I 11
#endif
E 16
E 11
E 7
E 5
I 4
	{ "debug",	IFF_DEBUG,	setifflags },
	{ "-debug",	-IFF_DEBUG,	setifflags },
I 26
	{ "alias",	IFF_UP,		notealias },
	{ "-alias",	-IFF_UP,	notealias },
	{ "delete",	-IFF_UP,	notealias },
E 26
E 4
I 3
#ifdef notdef
D 11
#define	EN_SWABIPS	0x100
E 11
I 11
#define	EN_SWABIPS	0x1000
E 11
	{ "swabips",	EN_SWABIPS,	setifflags },
	{ "-swabips",	-EN_SWABIPS,	setifflags },
#endif
I 11
	{ "netmask",	NEXTARG,	setifnetmask },
I 16
	{ "metric",	NEXTARG,	setifmetric },
I 26
D 31
	{ "snpaoffset",	NEXTARG,	setsnpaoffset },
E 31
E 26
E 16
	{ "broadcast",	NEXTARG,	setifbroadaddr },
I 12
	{ "ipdst",	NEXTARG,	setifipdst },
I 31
	{ "snpaoffset",	NEXTARG,	setsnpaoffset },
	{ "nsellength",	NEXTARG,	setnsellength },
I 36
D 38
	{ "llc0",	IFF_LLC0,	setifflags } ,
	{ "-llc0",	-IFF_LLC0,	setifflags } ,
	{ "llc1",	IFF_LLC1,	setifflags } ,
	{ "-llc1",	-IFF_LLC1,	setifflags } ,
	{ "llc2",	IFF_LLC2,	setifflags } ,
	{ "-llc2",	-IFF_LLC2,	setifflags } ,
E 38
I 38
	{ "link0",	IFF_LINK0,	setifflags } ,
	{ "-link0",	-IFF_LINK0,	setifflags } ,
	{ "link1",	IFF_LINK1,	setifflags } ,
	{ "-link1",	-IFF_LINK1,	setifflags } ,
	{ "link2",	IFF_LINK2,	setifflags } ,
	{ "-link2",	-IFF_LINK2,	setifflags } ,
E 38
E 36
E 31
E 12
E 11
E 3
	{ 0,		0,		setifaddr },
I 9
	{ 0,		0,		setifdstaddr },
E 9
};

I 12
/*
D 43
 * XNS support liberally adapted from
 * code written at the University of Maryland
 * principally by James O'Toole and Chris Torek.
E 43
I 43
 * XNS support liberally adapted from code written at the University of
 * Maryland principally by James O'Toole and Chris Torek.
E 43
 */
D 26

E 26
int	in_status(), in_getaddr();
int	xns_status(), xns_getaddr();
I 26
int	iso_status(), iso_getaddr();
E 26

/* Known address families */
struct afswtch {
	char *af_name;
	short af_af;
	int (*af_status)();
	int (*af_getaddr)();
I 26
	int af_difaddr;
	int af_aifaddr;
	caddr_t af_ridreq;
	caddr_t af_addreq;
E 26
} afs[] = {
D 26
	{ "inet",	AF_INET,	in_status,	in_getaddr },
	{ "ns",		AF_NS,		xns_status,	xns_getaddr },
	{ 0,		0,		0,		0 }
E 26
I 26
#define C(x) ((caddr_t) &x)
	{ "inet", AF_INET, in_status, in_getaddr,
	     SIOCDIFADDR, SIOCAIFADDR, C(ridreq), C(addreq) },
	{ "ns", AF_NS, xns_status, xns_getaddr,
	     SIOCDIFADDR, SIOCAIFADDR, C(ridreq), C(addreq) },
	{ "iso", AF_ISO, iso_status, iso_getaddr,
	     SIOCDIFADDR_ISO, SIOCAIFADDR_ISO, C(iso_ridreq), C(iso_addreq) },
	{ 0,	0,	    0,		0 }
E 26
};

struct afswtch *afp;	/*the address family being set or asked about*/

I 26
D 32
int testing = 0;
Ioctl(a,b,c) {
	int error = 0;
	if (testing)
		printf("would call ioctl with %x, %x, %x\n", a, b, c);
	else
		error = ioctl(a, b, c);
	return error;
}
#define ioctl(a, b, c) Ioctl(a,b,c)

E 32
E 26
E 12
main(argc, argv)
	int argc;
	char *argv[];
{
D 12

E 12
I 12
	int af = AF_INET;
I 26
	register struct afswtch *rafp;
E 26
I 20

E 20
E 12
	if (argc < 2) {
D 12
		fprintf(stderr, "usage: ifconfig interface %s %s %s\n",
E 12
I 12
D 16
		fprintf(stderr, "usage: ifconfig interface [ af %s %s %s %s\n",
E 12
D 9
		    "[ address ] [ up ] [ down ]",
E 9
I 9
		    "[ address [ dest_addr ] ] [ up ] [ down ]",
I 11
D 12
		    "[ netmask mask ]",
E 12
I 12
		    "[ netmask mask ] ]",
E 12
E 11
E 9
		    "[ trailers | -trailers ]",
D 12
		    "[ arp | -arp ]");
E 12
I 12
		    "[ arp | -arp ] ]");
E 16
I 16
D 23
		fprintf(stderr, "usage: ifconfig interface\n%s%s%s%s",
E 23
I 23
D 36
		fprintf(stderr, "usage: ifconfig interface\n%s%s%s%s%s",
E 36
I 36
D 41
		fprintf(stderr, "usage: ifconfig interface\n%s%s%s%s%s%s",
E 41
I 41
		fprintf(stderr, "usage: ifconfig interface\n%s%s%s%s%s",
E 41
E 36
E 23
		    "\t[ af [ address [ dest_addr ] ] [ up ] [ down ]",
			    "[ netmask mask ] ]\n",
		    "\t[ metric n ]\n",
D 41
		    "\t[ trailers | -trailers ]\n",
E 41
D 36
		    "\t[ arp | -arp ]\n");
E 36
I 36
		    "\t[ arp | -arp ]\n",
D 39
		    "\t[ llc0 | -llc0 ] [ llc1 | -llc1 ] [ llc2 | -llc2 ] \n");
E 39
I 39
		    "\t[ link0 | -link0 ] [ link1 | -link1 ] [ link2 | -link2 ] \n");
E 39
E 36
E 16
E 12
		exit(1);
	}
D 12
	s = socket(AF_INET, SOCK_DGRAM, 0);
E 12
I 12
	argc--, argv++;
D 14
	strncpy(name, *argv, sizeof(name - 1));
	name[sizeof name - 1] = 0;
E 14
I 14
	strncpy(name, *argv, sizeof(name));
E 14
	strncpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	argc--, argv++;
	if (argc > 0) {
D 26
		struct afswtch *myafp;
		
		for (myafp = afp = afs; myafp->af_name; myafp++)
			if (strcmp(myafp->af_name, *argv) == 0) {
				afp = myafp; argc--; argv++;
E 26
I 26
		for (afp = rafp = afs; rafp->af_name; rafp++)
			if (strcmp(rafp->af_name, *argv) == 0) {
				afp = rafp; argc--; argv++;
E 26
				break;
			}
D 26
		af = ifr.ifr_addr.sa_family = afp->af_af;
E 26
I 26
		rafp = afp;
		af = ifr.ifr_addr.sa_family = rafp->af_af;
E 26
	}
	s = socket(af, SOCK_DGRAM, 0);
E 12
	if (s < 0) {
		perror("ifconfig: socket");
		exit(1);
	}
D 12
	argc--, argv++;
	strcpy(name, *argv);
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
	if (ioctl(s, SIOCGIFFLAGS, (caddr_t)&ifr) < 0) {
		Perror("ioctl (SIOCGIFFLAGS)");
		exit(1);
	}
I 12
	strncpy(ifr.ifr_name, name, sizeof ifr.ifr_name);
E 12
I 11
	flags = ifr.ifr_flags;
I 16
	if (ioctl(s, SIOCGIFMETRIC, (caddr_t)&ifr) < 0)
		perror("ioctl (SIOCGIFMETRIC)");
	else
		metric = ifr.ifr_metric;
E 16
D 12
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
	if (ioctl(s, SIOCGIFNETMASK, (caddr_t)&ifr) < 0) {
		if (errno != EADDRNOTAVAIL)
			Perror("ioctl (SIOCGIFNETMASK)");
	} else
		netmask.sin_addr = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
E 11
D 7
	flags = ifr.ifr_flags;
E 7
	argc--, argv++;
E 12
I 12
D 20
	if (af == AF_INET) {
		if (ioctl(s, SIOCGIFNETMASK, (caddr_t)&ifr) < 0) {
			if (errno != EADDRNOTAVAIL)
				Perror("ioctl (SIOCGIFNETMASK)");
		} else
			netmask.sin_addr =
			      ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
		strncpy(ifr.ifr_name, name, sizeof ifr.ifr_name);
	}
E 20
E 12
	if (argc == 0) {
		status();
		exit(0);
	}
	while (argc > 0) {
		register struct cmd *p;

		for (p = cmds; p->c_name; p++)
			if (strcmp(*argv, p->c_name) == 0)
				break;
I 9
		if (p->c_name == 0 && setaddr)
			p++;	/* got src, do dst */
E 9
D 11
		if (p->c_func)
			(*p->c_func)(*argv, p->c_parameter);
E 11
I 11
		if (p->c_func) {
			if (p->c_parameter == NEXTARG) {
I 43
				if (argv[1] == NULL)
					errx(1, "'%s' requires argument",
					    p->c_name);
E 43
				(*p->c_func)(argv[1]);
				argc--, argv++;
			} else
				(*p->c_func)(*argv, p->c_parameter);
		}
E 11
		argc--, argv++;
	}
I 32
	if (af == AF_ISO)
		adjust_nsellength();
E 32
I 11
D 12
	if (setmask || setaddr) {
E 12
I 12
D 20
	if ((setmask || setaddr) && (af == AF_INET)){
E 20
I 20
D 26
	if ((setmask || setaddr) && (af == AF_INET)) {
E 20
E 12
		/*
		 * If setting the address and not the mask,
		 * clear any existing mask and the kernel will then
		 * assign the default.  If setting both,
		 * set the mask first, so the address will be
		 * interpreted correctly.
		 */
D 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
		ifr.ifr_addr = *(struct sockaddr *)&netmask;
		if (ioctl(s, SIOCSIFNETMASK, (caddr_t)&ifr) < 0)
			Perror("ioctl (SIOCSIFNETMASK)");
E 26
I 26
D 27
	if (clearaddr) {
		int ret;
		strncpy(rafp->af_ridreq, name, sizeof ifr.ifr_name);
		if ((ret = ioctl(s, rafp->af_difaddr, rafp->af_ridreq)) < 0) {
			if (errno == EADDRNOTAVAIL && (doalias >= 0)) {
				/* means no previous address for interface */
			} else
				Perror("ioctl (SIOCDIFADDR)");
		}
E 26
	}
E 27
I 12
	if (setipdst && af==AF_NS) {
		struct nsip_req rq;
		int size = sizeof(rq);

D 26
		rq.rq_ns = *(struct sockaddr *) &sin;
		rq.rq_ip = *(struct sockaddr *) &ipdst;
E 26
I 26
		rq.rq_ns = addreq.ifra_addr;
		rq.rq_ip = addreq.ifra_dstaddr;
E 26

		if (setsockopt(s, 0, SO_NSIP_ROUTE, &rq, size) < 0)
			Perror("Encapsulation Routing");
D 26
		setaddr = 0;
E 26
I 26
D 27
		newaddr = 0;
E 27
E 26
	}
I 27
D 29
	if (setipdst && af == AF_ISO) {
		iso_ridreq.ifr_Addr = iso_addreq.ifra_addr;
D 28
		iso_ridreq.ifr_Addr.siso_ssuffixlen =
E 28
I 28
		iso_ridreq.ifr_Addr.siso_slen =
E 28
			((struct sockaddr_in *)&addreq.ifra_dstaddr)->
				sin_addr.s_addr;
		strncpy(rafp->af_ridreq, name, sizeof ifr.ifr_name);
		if (ioctl(s, SIOCSEONCORE, &iso_ridreq) < 0)
			Perror("Iso Encapsulation Routing");
	}
E 29
	if (clearaddr) {
		int ret;
		strncpy(rafp->af_ridreq, name, sizeof ifr.ifr_name);
		if ((ret = ioctl(s, rafp->af_difaddr, rafp->af_ridreq)) < 0) {
			if (errno == EADDRNOTAVAIL && (doalias >= 0)) {
				/* means no previous address for interface */
			} else
				Perror("ioctl (SIOCDIFADDR)");
		}
	}
E 27
E 12
E 11
I 7
D 26
	if (setaddr) {
D 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
		ifr.ifr_addr = *(struct sockaddr *) &sin;
		if (ioctl(s, SIOCSIFADDR, (caddr_t)&ifr) < 0)
			Perror("ioctl (SIOCSIFADDR)");
E 26
I 26
	if (newaddr) {
		strncpy(rafp->af_addreq, name, sizeof ifr.ifr_name);
		if (ioctl(s, rafp->af_aifaddr, rafp->af_addreq) < 0)
			Perror("ioctl (SIOCAIFADDR)");
E 26
	}
I 11
D 26
	if (setbroadaddr) {
D 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
		ifr.ifr_addr = *(struct sockaddr *)&broadaddr;
		if (ioctl(s, SIOCSIFBRDADDR, (caddr_t)&ifr) < 0)
			Perror("ioctl (SIOCSIFBRDADDR)");
	}
E 26
E 11
E 7
	exit(0);
}
I 26
#define RIDADDR 0
#define ADDR	1
#define MASK	2
#define DSTADDR	3
E 26

/*ARGSUSED*/
setifaddr(addr, param)
	char *addr;
D 12
	int param;
E 12
I 12
	short param;
E 12
{
D 12

D 7
	getaddr(addr, (struct sockaddr_in *)&ifr.ifr_addr);
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
	if (ioctl(s, SIOCSIFADDR, (caddr_t)&ifr) < 0)
		Perror("ioctl (SIOCSIFADDR)");
I 6
	/* 
	 * SIFADDR ioctl above can change the flags value if it is
	 * the first time the address has been set.  Must get the
	 * new flags so that we don't store outdated ones later on.
E 7
I 7
	getaddr(addr, &sin);
E 12
	/*
	 * Delay the ioctl to set the interface addr until flags are all set.
	 * The address interpretation may depend on the flags,
	 * and the flags may change when the address is set.
E 7
	 */
D 7
	if (ioctl(s, SIOCGIFFLAGS, (caddr_t)&ifr) < 0) {
		Perror("ioctl (SIOCGIFFLAGS) 2");
		exit(1);
	}
	flags = ifr.ifr_flags;
E 7
I 7
	setaddr++;
I 27
D 29
	if (doalias = 0)
E 29
I 29
	if (doalias == 0)
E 29
		clearaddr = 1;
E 27
I 12
D 26
	(*afp->af_getaddr)(addr, &sin);
E 26
I 26
	(*afp->af_getaddr)(addr, (doalias >= 0 ? ADDR : RIDADDR));
E 26
E 12
E 7
E 6
}

I 11
setifnetmask(addr)
	char *addr;
{
D 12

	getaddr(addr, &netmask);
E 12
I 12
D 26
	in_getaddr(addr, &netmask);
E 12
	setmask++;
E 26
I 26
	(*afp->af_getaddr)(addr, MASK);
E 26
}

setifbroadaddr(addr)
	char *addr;
{
D 12
	getaddr(addr, &broadaddr);
E 12
I 12
D 26
	(*afp->af_getaddr)(addr, &broadaddr);
E 12
	setbroadaddr++;
E 26
I 26
	(*afp->af_getaddr)(addr, DSTADDR);
E 26
}

I 12
setifipdst(addr)
	char *addr;
{
D 26
	in_getaddr(addr, &ipdst);
E 26
I 26
	in_getaddr(addr, DSTADDR);
E 26
	setipdst++;
I 27
	clearaddr = 0;
	newaddr = 0;
E 27
}
D 27

E 27
I 27
#define rqtosa(x) (&(((struct ifreq *)(afp->x))->ifr_addr))
E 27
E 12
E 11
I 9
/*ARGSUSED*/
I 26
notealias(addr, param)
	char *addr;
{
I 27
	if (setaddr && doalias == 0 && param < 0)
		bcopy((caddr_t)rqtosa(af_addreq),
		      (caddr_t)rqtosa(af_ridreq),
		      rqtosa(af_addreq)->sa_len);
E 27
	doalias = param;
D 27
	if (param > 0)
		clearaddr = 0;
	else
E 27
I 27
	if (param < 0) {
		clearaddr = 1;
E 27
		newaddr = 0;
I 27
	} else
		clearaddr = 0;
E 27
}

/*ARGSUSED*/
I 41
notrailers(vname, value)
	char *vname;
	int value;
{
	printf("Note: trailers are no longer sent, but always received\n");
}

/*ARGSUSED*/
E 41
E 26
setifdstaddr(addr, param)
	char *addr;
	int param;
{
I 10
D 11
	int flags = ifr.ifr_flags;
E 11
E 10
D 27

E 27
D 12
	getaddr(addr, (struct sockaddr_in *)&ifr.ifr_dstaddr);
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
I 12
D 26
	(*afp->af_getaddr)(addr, &ifr.ifr_addr);
E 12
	if (ioctl(s, SIOCSIFDSTADDR, (caddr_t)&ifr) < 0)
		Perror("ioctl (SIOCSIFDSTADDR)");
E 26
I 26
	(*afp->af_getaddr)(addr, DSTADDR);
E 26
I 10
D 11
	ifr.ifr_flags = flags;
E 11
E 10
}

E 9
D 2
setifflags(name, value)
	char *name;
E 2
I 2
setifflags(vname, value)
	char *vname;
E 2
D 12
	int value;
E 12
I 12
	short value;
E 12
{
I 12
 	if (ioctl(s, SIOCGIFFLAGS, (caddr_t)&ifr) < 0) {
 		Perror("ioctl (SIOCGIFFLAGS)");
 		exit(1);
 	}
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
 	flags = ifr.ifr_flags;
E 12

	if (value < 0) {
		value = -value;
D 5
		ifr.ifr_flags = (flags &~ value);
E 5
I 5
D 7
		flags &= ~value;
E 7
I 7
D 11
		ifr.ifr_flags &= ~value;
E 11
I 11
		flags &= ~value;
E 11
E 7
E 5
	} else
D 5
		ifr.ifr_flags |= value;
E 5
I 5
D 7
		flags |= value;
	ifr.ifr_flags = flags;
E 7
I 7
D 11
		ifr.ifr_flags |= value;
E 11
I 11
		flags |= value;
E 11
E 7
E 5
D 12
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
I 11
	ifr.ifr_flags = flags;
E 11
	if (ioctl(s, SIOCSIFFLAGS, (caddr_t)&ifr) < 0)
D 2
		Perror(name);
E 2
I 2
		Perror(vname);
E 2
}

I 16
setifmetric(val)
	char *val;
{
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
	ifr.ifr_metric = atoi(val);
	if (ioctl(s, SIOCSIFMETRIC, (caddr_t)&ifr) < 0)
		perror("ioctl (set metric)");
}

I 26
setsnpaoffset(val)
	char *val;
{
	iso_addreq.ifra_snpaoffset = atoi(val);
}

E 26
#define	IFFBITS \
D 35
"\020\1UP\2BROADCAST\3DEBUG\4LOOPBACK\5POINTOPOINT\6NOTRAILERS\7RUNNING\10NOARP\
"
E 35
I 35
D 36
"\020\1UP\2BROADCAST\3DEBUG\4LOOPBACK\5POINTOPOINT\6NOTRAILERS\7RUNNING\
\10NOARP\11PROMISC\12ALLMULTI\13OACTIVE\14SIMPLEX"
E 36
I 36
"\020\1UP\2BROADCAST\3DEBUG\4LOOPBACK\5POINTOPOINT\6NOTRAILERS\7RUNNING\10NOARP\
D 38
\11PROMISC\12ALLMULTI\13OACTIVE\14SIMPLEX\15LLC0\16LLC1\16LLC2"
E 38
I 38
D 40
\11PROMISC\12ALLMULTI\13OACTIVE\14SIMPLEX\15LINK0\16LINK1\16LINK2"
E 40
I 40
D 41
\11PROMISC\12ALLMULTI\13OACTIVE\14SIMPLEX\15LINK0\16LINK1\17LINK2"
E 41
I 41
\11PROMISC\12ALLMULTI\13OACTIVE\14SIMPLEX\15LINK0\16LINK1\17LINK2\20MULTICAST"
E 41
E 40
E 38
E 36
E 35

E 16
I 12
/*
 * Print the status of the interface.  If an address family was
 * specified, show it and it only; otherwise, show them all.
 */
E 12
status()
{
I 12
	register struct afswtch *p = afp;
	short af = ifr.ifr_addr.sa_family;

I 16
	printf("%s: ", name);
	printb("flags", flags, IFFBITS);
	if (metric)
		printf(" metric %d", metric);
	putchar('\n');
E 16
	if ((p = afp) != NULL) {
D 21
		(*p->af_status)();
		return;
	}
	for (p = afs; p->af_name; p++) {
E 21
I 21
		(*p->af_status)(1);
	} else for (p = afs; p->af_name; p++) {
E 21
		ifr.ifr_addr.sa_family = p->af_af;
D 21
		(*p->af_status)();
E 21
I 21
		(*p->af_status)(0);
E 21
	}
}

D 16
#define	IFFBITS \
"\020\1UP\2BROADCAST\3DEBUG\4ROUTE\5POINTOPOINT\6NOTRAILERS\7RUNNING\10NOARP\
\11LOCAL"

E 16
D 21
in_status()
E 21
I 21
in_status(force)
	int force;
E 21
{
E 12
	struct sockaddr_in *sin;
I 12
	char *inet_ntoa();
E 12
I 7
D 11
	int flags = ifr.ifr_flags;
E 11
E 7

I 20
D 21
	if (ioctl(s, SIOCGIFNETMASK, (caddr_t)&ifr) < 0) {
		if (errno != EADDRNOTAVAIL)
			Perror("ioctl (SIOCGIFNETMASK)");
	} else
		netmask.sin_addr =
		    ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
E 21
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 20
D 12
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
D 11
	if (ioctl(s, SIOCGIFADDR, (caddr_t)&ifr) < 0)
		Perror("ioctl (SIOCGIFADDR)");
E 11
I 11
	if (ioctl(s, SIOCGIFADDR, (caddr_t)&ifr) < 0) {
D 21
		if (errno == EADDRNOTAVAIL)
E 21
I 21
		if (errno == EADDRNOTAVAIL || errno == EAFNOSUPPORT) {
			if (!force)
				return;
E 21
			bzero((char *)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
D 21
		else
			Perror("ioctl (SIOCGIFADDR)");
E 21
I 21
		} else
			perror("ioctl (SIOCGIFADDR)");
E 21
	}
I 12
D 21
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 21
E 12
E 11
	sin = (struct sockaddr_in *)&ifr.ifr_addr;
D 16
	printf("%s: %s ", name, inet_ntoa(sin->sin_addr));
E 16
I 16
D 19
	printf("\tinet %s ", name, inet_ntoa(sin->sin_addr));
E 19
I 19
	printf("\tinet %s ", inet_ntoa(sin->sin_addr));
I 21
	strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
	if (ioctl(s, SIOCGIFNETMASK, (caddr_t)&ifr) < 0) {
		if (errno != EADDRNOTAVAIL)
			perror("ioctl (SIOCGIFNETMASK)");
		bzero((char *)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
	} else
		netmask.sin_addr =
		    ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
E 21
E 19
E 16
I 9
	if (flags & IFF_POINTOPOINT) {
D 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
D 11
		if (ioctl(s, SIOCGIFDSTADDR, (caddr_t)&ifr) < 0)
			Perror("ioctl (SIOCGIFDSTADDR)");
E 11
I 11
		if (ioctl(s, SIOCGIFDSTADDR, (caddr_t)&ifr) < 0) {
			if (errno == EADDRNOTAVAIL)
			    bzero((char *)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
			else
D 21
			    Perror("ioctl (SIOCGIFDSTADDR)");
E 21
I 21
			    perror("ioctl (SIOCGIFDSTADDR)");
E 21
		}
I 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
E 11
		sin = (struct sockaddr_in *)&ifr.ifr_dstaddr;
		printf("--> %s ", inet_ntoa(sin->sin_addr));
	}
I 11
D 43
	printf("netmask %x ", ntohl(netmask.sin_addr.s_addr));
E 43
I 43
	printf("netmask 0x%x ", ntohl(netmask.sin_addr.s_addr));
E 43
E 11
E 9
D 12
#define	IFFBITS \
D 5
"\020\1UP\2BROADCAST\3DEBUG\4ROUTE\5POINTOPOINT\6NOTRAILERS\7RUNNING"
E 5
I 5
D 7
"\020\1UP\2BROADCAST\3DEBUG\4ROUTE\5POINTOPOINT\6NOTRAILERS\7RUNNING\10NOARP"
E 7
I 7
"\020\1UP\2BROADCAST\3DEBUG\4ROUTE\5POINTOPOINT\6NOTRAILERS\7RUNNING\10NOARP\
\11LOCAL"
E 12
E 7
E 5
D 16
	printb("flags", flags, IFFBITS); putchar('\n');
E 16
I 11
	if (flags & IFF_BROADCAST) {
D 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
		if (ioctl(s, SIOCGIFBRDADDR, (caddr_t)&ifr) < 0) {
			if (errno == EADDRNOTAVAIL)
D 21
				return;
			Perror("ioctl (SIOCGIFADDR)");
E 21
I 21
			    bzero((char *)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
			else
			    perror("ioctl (SIOCGIFADDR)");
E 21
		}
I 12
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
E 12
		sin = (struct sockaddr_in *)&ifr.ifr_addr;
D 16
		printf("broadcast: %s\n", inet_ntoa(sin->sin_addr));
E 16
I 16
D 21
		printf("broadcast %s", inet_ntoa(sin->sin_addr));
E 21
I 21
		if (sin->sin_addr.s_addr != 0)
			printf("broadcast %s", inet_ntoa(sin->sin_addr));
E 21
E 16
	}
I 16
	putchar('\n');
E 16
E 11
}

I 12

D 21
xns_status()
E 21
I 21
xns_status(force)
	int force;
E 21
{
	struct sockaddr_ns *sns;
D 15
	char *xns_ntoa();
E 15

	close(s);
	s = socket(AF_NS, SOCK_DGRAM, 0);
	if (s < 0) {
I 14
D 22
		if (errno == EAFNOSUPPORT)
E 22
I 22
		if (errno == EPROTONOSUPPORT)
E 22
			return;
E 14
		perror("ifconfig: socket");
		exit(1);
	}
	if (ioctl(s, SIOCGIFADDR, (caddr_t)&ifr) < 0) {
D 14
		if (errno == EAFNOSUPPORT)
E 14
I 14
D 21
		if (errno == EADDRNOTAVAIL || errno==EAFNOSUPPORT)
E 14
			return;
		Perror("ioctl (SIOCGIFADDR)");
E 21
I 21
		if (errno == EADDRNOTAVAIL || errno == EAFNOSUPPORT) {
			if (!force)
				return;
			bzero((char *)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
		} else
			perror("ioctl (SIOCGIFADDR)");
E 21
	}
	strncpy(ifr.ifr_name, name, sizeof ifr.ifr_name);
	sns = (struct sockaddr_ns *)&ifr.ifr_addr;
D 15
	printf("%s: xns %s ", name, xns_ntoa(sns));
E 15
I 15
D 16
	printf("%s: ns:%s ", name, ns_ntoa(sns->sns_addr));
E 16
I 16
	printf("\tns %s ", ns_ntoa(sns->sns_addr));
E 16
	if (flags & IFF_POINTOPOINT) { /* by W. Nesheim@Cornell */
		if (ioctl(s, SIOCGIFDSTADDR, (caddr_t)&ifr) < 0) {
			if (errno == EADDRNOTAVAIL)
			    bzero((char *)&ifr.ifr_addr, sizeof(ifr.ifr_addr));
			else
			    Perror("ioctl (SIOCGIFDSTADDR)");
		}
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
		sns = (struct sockaddr_ns *)&ifr.ifr_dstaddr;
		printf("--> %s ", ns_ntoa(sns->sns_addr));
	}
E 15
D 16
	printb("flags", flags, IFFBITS);
E 16
	putchar('\n');
}

I 26
iso_status(force)
	int force;
{
	struct sockaddr_iso *siso;
	struct iso_ifreq ifr;

	close(s);
	s = socket(AF_ISO, SOCK_DGRAM, 0);
	if (s < 0) {
		if (errno == EPROTONOSUPPORT)
			return;
		perror("ifconfig: socket");
		exit(1);
	}
D 31
	if (ioctl(s, SIOCGIFADDR, (caddr_t)&ifr) < 0) {
E 31
I 31
	bzero((caddr_t)&ifr, sizeof(ifr));
	strncpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	if (ioctl(s, SIOCGIFADDR_ISO, (caddr_t)&ifr) < 0) {
E 31
		if (errno == EADDRNOTAVAIL || errno == EAFNOSUPPORT) {
			if (!force)
				return;
			bzero((char *)&ifr.ifr_Addr, sizeof(ifr.ifr_Addr));
D 31
		} else
			perror("ioctl (SIOCGIFADDR)");
E 31
I 31
		} else {
			perror("ioctl (SIOCGIFADDR_ISO)");
			exit(1);
		}
E 31
	}
	strncpy(ifr.ifr_name, name, sizeof ifr.ifr_name);
	siso = &ifr.ifr_Addr;
D 31
	printf("\tiso %s ", iso_ntoa(siso->siso_addr));
	if (ioctl(s, SIOCGIFNETMASK, (caddr_t)&ifr) < 0) {
E 31
I 31
	printf("\tiso %s ", iso_ntoa(&siso->siso_addr));
	if (ioctl(s, SIOCGIFNETMASK_ISO, (caddr_t)&ifr) < 0) {
E 31
		if (errno != EADDRNOTAVAIL)
D 31
			perror("ioctl (SIOCGIFNETMASK)");
E 31
I 31
			perror("ioctl (SIOCGIFNETMASK_ISO)");
E 31
	} else {
D 31
		printf("\n netmask %s ", iso_ntoa(siso->siso_addr));
E 31
I 31
		printf(" netmask %s ", iso_ntoa(&siso->siso_addr));
E 31
	}
	if (flags & IFF_POINTOPOINT) {
D 31
		if (ioctl(s, SIOCGIFDSTADDR, (caddr_t)&ifr) < 0) {
E 31
I 31
		if (ioctl(s, SIOCGIFDSTADDR_ISO, (caddr_t)&ifr) < 0) {
E 31
			if (errno == EADDRNOTAVAIL)
			    bzero((char *)&ifr.ifr_Addr, sizeof(ifr.ifr_Addr));
			else
D 31
			    Perror("ioctl (SIOCGIFDSTADDR)");
E 31
I 31
			    Perror("ioctl (SIOCGIFDSTADDR_ISO)");
E 31
		}
		strncpy(ifr.ifr_name, name, sizeof (ifr.ifr_name));
		siso = &ifr.ifr_Addr;
D 31
		printf("--> %s ", iso_ntoa(siso->siso_addr));
E 31
I 31
		printf("--> %s ", iso_ntoa(&siso->siso_addr));
E 31
	}
	putchar('\n');
}

E 26
E 12
Perror(cmd)
	char *cmd;
{
	extern int errno;

D 43
	fprintf(stderr, "ifconfig: ");
E 43
	switch (errno) {

	case ENXIO:
D 12
		fprintf(stderr, "%s: ", cmd);
		fprintf(stderr, "no such interface\n");
E 12
I 12
D 43
		fprintf(stderr, "%s: no such interface\n", cmd);
E 43
I 43
		errx(1, "%s: no such interface", cmd);
E 43
E 12
		break;

	case EPERM:
D 8
		fprintf(stderr, "%s: permission denied\n");
E 8
I 8
D 43
		fprintf(stderr, "%s: permission denied\n", cmd);
E 43
I 43
		errx(1, "%s: permission denied", cmd);
E 43
E 8
		break;

	default:
D 43
		perror(cmd);
E 43
I 43
		err(1, "%s", cmd);
E 43
	}
D 43
	exit(1);
E 43
}

struct	in_addr inet_makeaddr();

D 12
getaddr(s, sin)
E 12
I 12
D 26
in_getaddr(s, saddr)
E 26
I 26
#define SIN(x) ((struct sockaddr_in *) &(x))
struct sockaddr_in *sintab[] = {
SIN(ridreq.ifr_addr), SIN(addreq.ifra_addr),
SIN(addreq.ifra_mask), SIN(addreq.ifra_broadaddr)};

in_getaddr(s, which)
E 26
E 12
	char *s;
D 12
	struct sockaddr_in *sin;
E 12
I 12
D 26
	struct sockaddr *saddr;
E 26
E 12
{
I 12
D 26
	register struct sockaddr_in *sin = (struct sockaddr_in *)saddr;
E 26
I 26
	register struct sockaddr_in *sin = sintab[which];
E 26
E 12
	struct hostent *hp;
	struct netent *np;
	int val;

I 11
D 26
	sin->sin_family = AF_INET;
I 25
	sin->sin_len = sizeof(*sin);
E 26
I 26
D 28
	if (which == MASK)
		sin->sin_len = 8;
	else {
E 28
I 28
	sin->sin_len = sizeof(*sin);
	if (which != MASK)
E 28
		sin->sin_family = AF_INET;
D 28
		sin->sin_len = sizeof(*sin);
	}
E 26
E 25
	val = inet_addr(s);
	if (val != -1) {
E 28
I 28

	if ((val = inet_addr(s)) != -1)
E 28
		sin->sin_addr.s_addr = val;
D 28
		return;
	}
E 11
	hp = gethostbyname(s);
	if (hp) {
		sin->sin_family = hp->h_addrtype;
E 28
I 28
	else if (hp = gethostbyname(s))
E 28
		bcopy(hp->h_addr, (char *)&sin->sin_addr, hp->h_length);
D 28
		return;
	}
	np = getnetbyname(s);
	if (np) {
		sin->sin_family = np->n_addrtype;
E 28
I 28
	else if (np = getnetbyname(s))
E 28
		sin->sin_addr = inet_makeaddr(np->n_net, INADDR_ANY);
D 11
		return;
	}
	sin->sin_family = AF_INET;
	val = inet_addr(s);
	if (val != -1) {
		sin->sin_addr.s_addr = val;
		return;
	}
	val = inet_network(s);
	if (val != -1) {
		sin->sin_addr = inet_makeaddr(val, INADDR_ANY);
E 11
D 28
		return;
E 28
I 28
D 43
	else {
		fprintf(stderr, "%s: bad value\n", s);
		exit(1);
E 28
	}
E 43
I 43
	else
		errx(1, "%s: bad value", s);
E 43
D 28
	fprintf(stderr, "%s: bad value\n", s);
	exit(1);
E 28
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
	}
I 12
}

D 15
#define setxnnet(a,b) {a = * (union ns_net *) &(b);}

E 15
D 26
xns_getaddr(addr, saddr)
E 26
I 26
#define SNS(x) ((struct sockaddr_ns *) &(x))
struct sockaddr_ns *snstab[] = {
SNS(ridreq.ifr_addr), SNS(addreq.ifra_addr),
SNS(addreq.ifra_mask), SNS(addreq.ifra_broadaddr)};

xns_getaddr(addr, which)
E 26
char *addr;
D 26
struct sockaddr *saddr;
E 26
{
D 15
	register struct sockaddr_ns *sns = (struct sockaddr_ns *)saddr;
	u_long netnum;
	char *index();
	register char *s = index(addr, ':');
	register int i;

	if (s!=NULL) *s = 0;
	netnum = atoi(addr);
	netnum = htonl(netnum);
	setxnnet(sns->sns_addr.x_net, netnum);
E 15
I 15
D 26
	struct sockaddr_ns *sns = (struct sockaddr_ns *)saddr;
E 26
I 26
	struct sockaddr_ns *sns = snstab[which];
E 26
	struct ns_addr ns_addr();
I 26

E 26
E 15
	sns->sns_family = AF_NS;
I 25
	sns->sns_len = sizeof(*sns);
E 25
D 15

	for (i = 0; i < 6; i++) {
		if (s == NULL || *++s == 0) 
			break;
		sns->sns_addr.x_host.c_host[i] = xtoi(s);
		s = index(s, '.');
	}

}

char *
xns_ntoa(sns)
register struct sockaddr_ns *sns;
{
	static char buf[30];

	sprintf (buf, "%d:%x.%x.%x.%x.%x.%x",
	    ntohl(ns_netof(sns->sns_addr)),
	    sns->sns_addr.x_host.c_host[0], sns->sns_addr.x_host.c_host[1],
	    sns->sns_addr.x_host.c_host[2], sns->sns_addr.x_host.c_host[3],
	    sns->sns_addr.x_host.c_host[4], sns->sns_addr.x_host.c_host[5]);
	return (buf);
}

int xtoi(s)
register char *s;
{
	register int res = 0, delta;
	register char *cp;
	static char base[] = "0123456789ABCDEFabcdef";

	for(; *s; s++) {
		cp = index(base, *s);	
		if (cp==NULL)
			break;
		if ((delta = cp - base) > 15)
			delta -= 6;
		res = (res << 4) + delta;
	}
	return(res);
E 15
I 15
	sns->sns_addr = ns_addr(addr);
I 26
	if (which == MASK)
		printf("Attempt to set XNS netmask will be ineffectual\n");
}

#define SISO(x) ((struct sockaddr_iso *) &(x))
struct sockaddr_iso *sisotab[] = {
SISO(iso_ridreq.ifr_Addr), SISO(iso_addreq.ifra_addr),
SISO(iso_addreq.ifra_mask), SISO(iso_addreq.ifra_dstaddr)};

iso_getaddr(addr, which)
char *addr;
{
D 32
	struct sockaddr_iso *siso = sisotab[which];
E 32
I 32
	register struct sockaddr_iso *siso = sisotab[which];
E 32
	struct iso_addr *iso_addr();
	siso->siso_addr = *iso_addr(addr);
I 32

E 32
	if (which == MASK) {
D 28
		siso->siso_len = siso->siso_nlen + 5;
E 28
I 28
		siso->siso_len = TSEL(siso) - (caddr_t)(siso);
E 28
		siso->siso_nlen = 0;
	} else {
D 32
	    siso->siso_family = AF_ISO;
	    siso->siso_len =  sizeof(*siso);
E 32
I 32
		siso->siso_len = sizeof(*siso);
		siso->siso_family = AF_ISO;
E 32
	}
I 31
}

setnsellength(val)
	char *val;
{
D 32
	register struct sockaddr_iso *siso = sisotab[ADDR];
	int n = atoi(val);
E 32
I 32
	nsellength = atoi(val);
D 43
	if (nsellength < 0) {
		fprintf(stderr, "Negative NSEL length is absurd\n");
		exit (1);
	}
E 32
	if (afp == 0 || afp->af_af != AF_ISO) {
		fprintf(stderr, "Setting NSEL length valid only for iso\n");
		exit (1);
	}
E 43
I 43
	if (nsellength < 0)
		errx(1, "Negative NSEL length is absurd");
	if (afp == 0 || afp->af_af != AF_ISO)
		errx(1, "Setting NSEL length valid only for iso");
E 43
D 32
	if (n >= 0)
		siso->siso_tlen = n;
E 32
I 32
}

fixnsel(s)
register struct sockaddr_iso *s;
{
	if (s->siso_family == 0)
		return;
D 33
	s->siso_nlen -= nsellength;
E 33
	s->siso_tlen = nsellength;
}

adjust_nsellength()
{
	fixnsel(sisotab[RIDADDR]);
	fixnsel(sisotab[ADDR]);
	fixnsel(sisotab[DSTADDR]);
E 32
E 31
E 26
E 15
E 12
}
E 1
