h18030
s 00040/00023/00465
d D 8.3 95/04/28 17:33:50 bostic 27 26
c Before I started to make changes, I fixed all the things cc -Wall
c and gcc2 -Wall complained about; here are the diffs for that.
c From: Chris Torek <torek@BSDI.COM>
e
s 00001/00000/00487
d D 8.2 94/01/02 12:53:54 bostic 26 25
c If you're going to fall through, say so!
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/00482
d D 8.1 93/06/06 13:50:31 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00007/00474
d D 5.17 93/04/01 12:14:55 mckusick 24 23
c convert from kinfo to sysctl
e
s 00002/00001/00479
d D 5.16 93/03/08 19:30:45 ralph 23 22
c use the standard decl from <arpa/inet.h> for inet_ntoa().
e
s 00003/00002/00477
d D 5.15 92/07/30 16:34:16 bostic 22 21
c set RTF_ANNOUNCE when an arp entry is published.
e
s 00005/00005/00474
d D 5.14 92/07/08 15:39:34 sklower 21 20
c we no longer support sending trailers
e
s 00001/00001/00478
d D 5.13 92/02/25 12:22:57 sklower 20 18
c mark installed routes as static so that gated won't get rid of them
e
s 00010/00055/00370
d D 5.11.1.1 91/07/22 17:10:27 bostic 19 17
c Keith Sklower -- version of arp that should work with network.2 release
e
s 00247/00193/00232
d D 5.12 91/06/25 21:50:32 sklower 18 17
c arp now smashed into routing table; rewrite user command
e
s 00001/00011/00424
d D 5.11 90/06/01 18:37:31 bostic 17 16
c new copyright notice
e
s 00003/00004/00432
d D 5.10 89/05/11 14:05:39 bostic 16 15
c file reorg, pathnames.h, paths.h
e
s 00004/00002/00432
d D 5.9 89/04/02 12:09:25 bostic 15 14
c add pathnames.h
e
s 00009/00009/00425
d D 5.8 88/10/10 18:35:01 bostic 14 13
c use herror
e
s 00001/00001/00433
d D 5.7 88/08/18 10:59:26 bostic 13 12
c typo city; bug report 4.3BSD/etc/145
e
s 00028/00002/00406
d D 5.6 88/06/30 14:28:36 bostic 12 11
c taken off the net; done by SUN
e
s 00128/00069/00280
d D 5.5 88/03/01 18:31:33 bostic 11 10
c add getopt, general cleanup, make it work with dead kernels
e
s 00017/00007/00332
d D 5.4 87/11/18 18:36:40 mckusick 10 9
c support for full arp syntax (4.3BSD/etc/99 from guy@sun.com (Guy Harris))
e
s 00001/00002/00338
d D 5.3 87/04/06 09:59:42 bostic 9 8
c sscanf argument count fix
e
s 00044/00023/00296
d D 5.2 86/02/21 12:30:25 karels 8 7
c accept host by number; only wait for nameserver once
e
s 00000/00000/00319
d D 5.1 86/02/16 23:03:17 karels 7 6
c bring up to release 5
e
s 00010/00004/00309
d D 1.4 86/01/09 18:51:11 karels 6 3
c print trailer flag, allow it to be set
e
s 00002/00000/00313
d R 1.4 86/01/09 18:26:41 karels 5 3
c print trailer flag
e
s 00001/00000/00313
d R 1.4 86/01/08 20:04:26 karels 4 3
c print value of new trailer flag
e
s 00003/00003/00310
d D 1.3 85/10/09 14:32:13 bloom 3 2
c return value incorrect, portability fixes (from ks@purdue)
e
s 00009/00011/00304
d D 1.2 85/05/30 12:48:47 karels 2 1
c no more struct ether_addr's
e
s 00315/00000/00000
d D 1.1 84/03/30 08:38:00 karels 1 0
c date and time created 84/03/30 08:38:00 by karels
e
u
U
f b 
t
T
I 12
/*
D 25
 * Copyright (c) 1984 Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1984, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * This code is derived from software contributed to Berkeley by
 * Sun Microsystems, Inc.
 *
D 17
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
 */

E 12
I 1
#ifndef lint
D 12
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 12
I 12
D 25
char copyright[] =
"%Z% Copyright (c) 1984 Regents of the University of California.\n\
 All rights reserved.\n";
E 25
I 25
static char copyright[] =
"%Z% Copyright (c) 1984, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 25
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 12

/*
 * arp - display, set, and delete arp table entries
 */

D 11
#include <stdio.h>
#include <sys/types.h>
E 11
I 11
D 18
D 19
#include <machine/pte.h>
E 18

E 19
#include <sys/param.h>
D 18
D 19
#include <sys/vmmac.h>
E 19
E 18
#include <sys/file.h>
E 11
#include <sys/socket.h>
D 11
#include <netinet/in.h>
E 11
D 18
#include <sys/ioctl.h>
E 18
I 18
D 24
#include <sys/kinfo.h>
E 24
I 24
#include <sys/sysctl.h>
E 24
E 18
D 11
#include <errno.h>
E 11
I 11

E 11
D 18
#include <netdb.h>
D 11
#include <nlist.h>
E 11
I 11
#include <netinet/in.h>
E 18
E 11
#include <net/if.h>
I 18
#include <net/if_dl.h>
#include <net/if_types.h>
#include <net/route.h>

#include <netinet/in.h>
E 18
#include <netinet/if_ether.h>

I 23
#include <arpa/inet.h>

E 23
I 18
D 27
#include <netdb.h>
E 27
I 27
#include <err.h>
E 27
E 18
I 11
#include <errno.h>
I 27
#include <netdb.h>
E 27
#include <nlist.h>
I 19
#include <kvm.h>
E 19
D 27
#include <stdio.h>
E 27
I 16
#include <paths.h>
I 27
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 27
E 16

I 15
D 16
#include "pathnames.h"

E 16
E 15
E 11
D 27
extern int errno;
E 27
I 18
static int pid;
E 18
I 11
D 19
D 27
static int kflag;
E 27
E 19
I 18
static int nflag;
static int s = -1;
E 18
E 11

I 27
int	delete __P((char *, char *));
void	dump __P((u_long));
int	ether_aton __P((char *, u_char *));
void	ether_print __P((u_char *));
int	file __P((char *));
void	get __P((char *));
void	getsocket __P((void));
int	rtmsg __P((int));
int	set __P((int, char **));
void	usage __P((void));

int
E 27
main(argc, argv)
I 11
	int argc;
E 11
	char **argv;
{
D 11
	if (argc >= 2 && strcmp(argv[1], "-a") == 0) {
		char *kernel = "/vmunix", *mem = "/dev/kmem";
E 11
I 11
	int ch;
E 11

D 11
		if (argc >= 3)
			kernel = argv[2];
		if (argc >= 4)
			mem = argv[3];
		dump(kernel, mem);
		exit(0);
	}
	if (argc == 2) {
		get(argv[1]);
		exit(0);
	}
	if (argc >= 4 && strcmp(argv[1], "-s") == 0) {
D 10
		set(argc-2, &argv[2]);
E 10
I 10
		if (set(argc-2, &argv[2]))
			exit(1);
E 10
		exit(0);
	}
	if (argc == 3 && strcmp(argv[1], "-d") == 0) {
		delete(argv[2]);
		exit(0);
	}
	if (argc == 3 && strcmp(argv[1], "-f") == 0) {
D 10
		file(argv[2]);
E 10
I 10
		if (file(argv[2]))
			exit(1);
E 10
		exit(0);
	}
	usage();
	exit(1);
E 11
I 11
D 18
	while ((ch = getopt(argc, argv, "adsf")) != EOF)
E 18
I 18
	pid = getpid();
	while ((ch = getopt(argc, argv, "ands")) != EOF)
E 18
		switch((char)ch) {
D 18
		case 'a': {
D 19
			char *mem;
E 19
I 19
			char *mem = 0;
E 19

			if (argc > 4)
				usage();
			if (argc == 4) {
D 19
				kflag = 1;
E 19
				mem = argv[3];
			}
D 19
			else
D 15
				mem = "/dev/kmem";
			dump((argc >= 3) ? argv[2] : "/vmunix", mem);
E 15
I 15
				mem = _PATH_KMEM;
E 19
D 16
			dump((argc >= 3) ? argv[2] : _PATH_VMUNIX, mem);
E 16
I 16
			dump((argc >= 3) ? argv[2] : _PATH_UNIX, mem);
E 18
I 18
		case 'a':
			dump(0);
E 18
E 16
E 15
			exit(0);
D 18
		}
E 18
		case 'd':
D 18
			if (argc != 3)
E 18
I 18
			if (argc < 3 || argc > 4)
E 18
				usage();
D 18
			delete(argv[2]);
E 18
I 18
			delete(argv[2], argv[3]);
E 18
			exit(0);
I 18
		case 'n':
			nflag = 1;
			continue;
E 18
		case 's':
			if (argc < 4 || argc > 7)
				usage();
			exit(set(argc-2, &argv[2]) ? 1 : 0);
D 18
		case 'f':
			if (argc != 3)
				usage();
			exit (file(argv[2]) ? 1 : 0);
E 18
		case '?':
		default:
			usage();
		}
	if (argc != 2)
		usage();
	get(argv[1]);
D 27
	exit(0);
E 27
I 27
	return (0);
E 27
E 11
}

/*
 * Process a file to set standard arp entries
 */
I 27
int
E 27
file(name)
	char *name;
{
	FILE *fp;
D 11
	int i;
E 11
I 11
	int i, retval;
E 11
D 6
	char line[100], arg[4][50], *args[4];
E 6
I 6
	char line[100], arg[5][50], *args[5];
I 10
D 11
	int retval;
E 11
E 10
E 6

	if ((fp = fopen(name, "r")) == NULL) {
		fprintf(stderr, "arp: cannot open %s\n", name);
		exit(1);
	}
	args[0] = &arg[0][0];
	args[1] = &arg[1][0];
	args[2] = &arg[2][0];
	args[3] = &arg[3][0];
I 6
	args[4] = &arg[4][0];
I 10
	retval = 0;
E 10
E 6
	while(fgets(line, 100, fp) != NULL) {
D 6
		i = sscanf(line, "%s %s %s %s", arg[0], arg[1], arg[2], arg[3]);
E 6
I 6
D 9
		i = sscanf(line, "%s %s %s %s", arg[0], arg[1], arg[2], arg[3],
			arg[4]);
E 9
I 9
D 10
		i = sscanf(line, "%s %s %s %s", arg[0], arg[1], arg[2], arg[3]);
E 10
I 10
		i = sscanf(line, "%s %s %s %s %s", arg[0], arg[1], arg[2],
		    arg[3], arg[4]);
E 10
E 9
E 6
		if (i < 2) {
			fprintf(stderr, "arp: bad line: %s\n", line);
I 10
			retval = 1;
E 10
			continue;
		}
D 10
		set(i, args);
E 10
I 10
		if (set(i, args))
			retval = 1;
E 10
	}
	fclose(fp);
I 10
	return (retval);
E 10
}

I 27
void
E 27
I 18
getsocket() {
	if (s < 0) {
		s = socket(PF_ROUTE, SOCK_RAW, 0);
		if (s < 0) {
			perror("arp: socket");
			exit(1);
		}
	}
}

struct	sockaddr_in so_mask = {8, 0, 0, { 0xffffffff}};
struct	sockaddr_inarp blank_sin = {sizeof(blank_sin), AF_INET }, sin_m;
struct	sockaddr_dl blank_sdl = {sizeof(blank_sdl), AF_LINK }, sdl_m;
int	expire_time, flags, export_only, doing_proxy, found_entry;
struct	{
	struct	rt_msghdr m_rtm;
	char	m_space[512];
}	m_rtmsg;

E 18
/*
 * Set an individual arp entry 
 */
I 27
int
E 27
set(argc, argv)
I 11
	int argc;
E 11
	char **argv;
{
D 18
	struct arpreq ar;
E 18
	struct hostent *hp;
D 18
	struct sockaddr_in *sin;
E 18
I 18
	register struct sockaddr_inarp *sin = &sin_m;
	register struct sockaddr_dl *sdl;
	register struct rt_msghdr *rtm = &(m_rtmsg.m_rtm);
E 18
D 2
	struct ether_addr *ea;
E 2
I 2
	u_char *ea;
E 2
D 18
	int s;
E 18
	char *host = argv[0], *eaddr = argv[1];

I 18
	getsocket();
E 18
	argc -= 2;
	argv += 2;
D 8
	hp = gethostbyname(host);
	if (hp == NULL) {
		fprintf(stderr, "arp: %s: unknown host\n", host);
D 3
		return (1);
E 3
I 3
		return;
E 3
	}
E 8
D 18
	bzero((caddr_t)&ar, sizeof ar);
D 8
	ar.arp_pa.sa_family = AF_INET;
E 8
	sin = (struct sockaddr_in *)&ar.arp_pa;
D 3
	sin->sin_addr = *(struct in_addr *)hp->h_addr;
E 3
I 3
D 8
	bcopy((char *)hp->h_addr, (char *)&sin->sin_addr, sizeof sin->sin_addr);
E 8
I 8
	sin->sin_family = AF_INET;
E 18
I 18
	sdl_m = blank_sdl;
	sin_m = blank_sin;
E 18
	sin->sin_addr.s_addr = inet_addr(host);
	if (sin->sin_addr.s_addr == -1) {
D 14
		hp = gethostbyname(host);
		if (hp == NULL) {
			fprintf(stderr, "arp: %s: unknown host\n", host);
E 14
I 14
		if (!(hp = gethostbyname(host))) {
			fprintf(stderr, "arp: %s: ", host);
			herror((char *)NULL);
E 14
D 10
			return;
E 10
I 10
			return (1);
E 10
		}
		bcopy((char *)hp->h_addr, (char *)&sin->sin_addr,
		    sizeof sin->sin_addr);
	}
E 8
E 3
D 2
	ea = (struct ether_addr *)ar.arp_ha.sa_data;
E 2
I 2
D 18
	ea = (u_char *)ar.arp_ha.sa_data;
E 2
	if (ether_aton(eaddr, ea))
D 10
		return;
E 10
I 10
		return (1);
E 10
	ar.arp_flags = ATF_PERM;
E 18
I 18
	ea = (u_char *)LLADDR(&sdl_m);
	if (ether_aton(eaddr, ea) == 0)
		sdl_m.sdl_alen = 6;
	doing_proxy = flags = export_only = expire_time = 0;
E 18
D 8
	while(argc-- > 0) {
E 8
I 8
	while (argc-- > 0) {
E 8
D 18
		if (strncmp(argv[0], "temp", 4) == 0)
			ar.arp_flags &= ~ATF_PERM;
E 18
I 18
		if (strncmp(argv[0], "temp", 4) == 0) {
			struct timeval time;
			gettimeofday(&time, 0);
			expire_time = time.tv_sec + 20 * 60;
		}
E 18
D 11
		if (strncmp(argv[0], "pub", 3) == 0)
E 11
I 11
D 22
		else if (strncmp(argv[0], "pub", 3) == 0)
E 22
I 22
		else if (strncmp(argv[0], "pub", 3) == 0) {
			flags |= RTF_ANNOUNCE;
E 22
E 11
D 18
			ar.arp_flags |= ATF_PUBL;
E 18
I 18
			doing_proxy = SIN_PROXY;
E 18
I 6
D 11
		if (strncmp(argv[0], "trail", 5) == 0)
E 11
I 11
D 21
		else if (strncmp(argv[0], "trail", 5) == 0)
E 11
D 18
			ar.arp_flags |= ATF_USETRAILERS;
E 18
I 18
			flags = RTF_PROTO1;
E 21
I 21
D 22
		else if (strncmp(argv[0], "trail", 5) == 0) {
E 22
I 22
		} else if (strncmp(argv[0], "trail", 5) == 0) {
E 22
			printf("%s: Sending trailers is no longer supported\n",
				host);
		}
E 21
E 18
E 6
		argv++;
	}
D 18
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
D 11
                perror("arp: socket");
                exit(1);
        }
E 11
I 11
		perror("arp: socket");
		exit(1);
	}
E 11
	if (ioctl(s, SIOCSARP, (caddr_t)&ar) < 0) {
E 18
I 18
tryagain:
	if (rtmsg(RTM_GET) < 0) {
E 18
		perror(host);
D 18
		exit(1);
E 18
I 18
		return (1);
E 18
	}
D 18
	close(s);
I 10
	return (0);
E 18
I 18
	sin = (struct sockaddr_inarp *)(rtm + 1);
	sdl = (struct sockaddr_dl *)(sin->sin_len + (char *)sin);
	if (sin->sin_addr.s_addr == sin_m.sin_addr.s_addr) {
		if (sdl->sdl_family == AF_LINK &&
		    (rtm->rtm_flags & RTF_LLINFO) &&
		    !(rtm->rtm_flags & RTF_GATEWAY)) switch (sdl->sdl_type) {
		case IFT_ETHER: case IFT_FDDI: case IFT_ISO88023:
		case IFT_ISO88024: case IFT_ISO88025:
			goto overwrite;
		}
		if (doing_proxy == 0) {
			printf("set: can only proxy for %s\n", host);
			return (1);
		}
		if (sin_m.sin_other & SIN_PROXY) {
			printf("set: proxy entry exists for non 802 device\n");
			return(1);
		}
		sin_m.sin_other = SIN_PROXY;
		export_only = 1;
		goto tryagain;
	}
overwrite:
	if (sdl->sdl_family != AF_LINK) {
		printf("cannot intuit interface index and type for %s\n", host);
		return (1);
	}
	sdl_m.sdl_type = sdl->sdl_type;
	sdl_m.sdl_index = sdl->sdl_index;
	return (rtmsg(RTM_ADD));
E 18
E 10
}

D 11

E 11
/*
 * Display an individual arp entry
 */
I 27
void
E 27
get(host)
	char *host;
{
D 18
	struct arpreq ar;
E 18
	struct hostent *hp;
D 18
	struct sockaddr_in *sin;
E 18
I 18
	struct sockaddr_inarp *sin = &sin_m;
E 18
D 2
	struct ether_addr *ea;
E 2
I 2
D 27
	u_char *ea;
E 27
E 2
D 18
	int s;
E 18
I 11
D 23
	char *inet_ntoa();
E 23
E 11

D 8
	hp = gethostbyname(host);
	if (hp == NULL) {
		fprintf(stderr, "arp: %s: unknown host\n", host);
		exit(1);
	}
E 8
D 18
	bzero((caddr_t)&ar, sizeof ar);
	ar.arp_pa.sa_family = AF_INET;
	sin = (struct sockaddr_in *)&ar.arp_pa;
D 8
	sin->sin_addr = *(struct in_addr *)hp->h_addr;
E 8
I 8
	sin->sin_family = AF_INET;
E 18
I 18
	sin_m = blank_sin;
E 18
	sin->sin_addr.s_addr = inet_addr(host);
	if (sin->sin_addr.s_addr == -1) {
D 14
		hp = gethostbyname(host);
		if (hp == NULL) {
			fprintf(stderr, "arp: %s: unknown host\n", host);
E 14
I 14
		if (!(hp = gethostbyname(host))) {
			fprintf(stderr, "arp: %s: ", host);
			herror((char *)NULL);
E 14
			exit(1);
		}
		bcopy((char *)hp->h_addr, (char *)&sin->sin_addr,
		    sizeof sin->sin_addr);
	}
E 8
D 18
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
D 11
                perror("arp: socket");
                exit(1);
        }
E 11
I 11
		perror("arp: socket");
E 18
I 18
	dump(sin->sin_addr.s_addr);
	if (found_entry == 0) {
		printf("%s (%s) -- no entry\n",
		    host, inet_ntoa(sin->sin_addr));
E 18
		exit(1);
	}
E 11
D 18
	if (ioctl(s, SIOCGARP, (caddr_t)&ar) < 0) {
		if (errno == ENXIO)
			printf("%s (%s) -- no entry\n",
			    host, inet_ntoa(sin->sin_addr));
		else
			perror("SIOCGARP");
		exit(1);
	}
	close(s);
D 2
	ea = (struct ether_addr *)ar.arp_ha.sa_data;
E 2
I 2
	ea = (u_char *)ar.arp_ha.sa_data;
E 2
	printf("%s (%s) at ", host, inet_ntoa(sin->sin_addr));
	if (ar.arp_flags & ATF_COM)
		ether_print(ea);
	else
		printf("(incomplete)");
D 6
	if (!(ar.arp_flags & ATF_PERM)) printf(" temporary");
E 6
I 6
D 11
	if (ar.arp_flags & ATF_PERM) printf(" permanent");
E 6
	if (ar.arp_flags & ATF_PUBL) printf(" published");
I 6
	if (ar.arp_flags & ATF_USETRAILERS) printf(" trailers");
E 11
I 11
	if (ar.arp_flags & ATF_PERM)
		printf(" permanent");
	if (ar.arp_flags & ATF_PUBL)
		printf(" published");
	if (ar.arp_flags & ATF_USETRAILERS)
		printf(" trailers");
E 11
E 6
	printf("\n");
E 18
}

/*
 * Delete an arp entry 
 */
I 27
int
E 27
D 18
delete(host)
E 18
I 18
delete(host, info)
E 18
	char *host;
I 18
	char *info;
E 18
{
D 18
	struct arpreq ar;
E 18
	struct hostent *hp;
D 18
	struct sockaddr_in *sin;
	int s;
E 18
I 18
	register struct sockaddr_inarp *sin = &sin_m;
	register struct rt_msghdr *rtm = &m_rtmsg.m_rtm;
	struct sockaddr_dl *sdl;
D 27
	u_char *ea;
	char *eaddr;
E 27
E 18

D 8
	hp = gethostbyname(host);
	if (hp == NULL) {
		fprintf(stderr, "arp: %s: unknown host\n", host);
		exit(1);
	}
E 8
D 18
	bzero((caddr_t)&ar, sizeof ar);
	ar.arp_pa.sa_family = AF_INET;
	sin = (struct sockaddr_in *)&ar.arp_pa;
D 3
	sin->sin_addr = *(struct in_addr *)hp->h_addr;
E 3
I 3
D 8
	bcopy((char *)hp->h_addr, (char *)&sin->sin_addr, sizeof sin->sin_addr);
E 8
I 8
	sin->sin_family = AF_INET;
E 18
I 18
	if (info && strncmp(info, "pro", 3) )
		export_only = 1;
	getsocket();
	sin_m = blank_sin;
E 18
	sin->sin_addr.s_addr = inet_addr(host);
	if (sin->sin_addr.s_addr == -1) {
D 14
		hp = gethostbyname(host);
		if (hp == NULL) {
			fprintf(stderr, "arp: %s: unknown host\n", host);
E 14
I 14
		if (!(hp = gethostbyname(host))) {
			fprintf(stderr, "arp: %s: ", host);
			herror((char *)NULL);
E 14
D 18
			exit(1);
E 18
I 18
			return (1);
E 18
		}
		bcopy((char *)hp->h_addr, (char *)&sin->sin_addr,
		    sizeof sin->sin_addr);
	}
E 8
E 3
D 18
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
D 11
                perror("arp: socket");
                exit(1);
        }
E 11
I 11
		perror("arp: socket");
		exit(1);
E 18
I 18
tryagain:
	if (rtmsg(RTM_GET) < 0) {
		perror(host);
		return (1);
E 18
	}
E 11
D 18
	if (ioctl(s, SIOCDARP, (caddr_t)&ar) < 0) {
		if (errno == ENXIO)
			printf("%s (%s) -- no entry\n",
			    host, inet_ntoa(sin->sin_addr));
		else
			perror("SIOCDARP");
		exit(1);
E 18
I 18
	sin = (struct sockaddr_inarp *)(rtm + 1);
	sdl = (struct sockaddr_dl *)(sin->sin_len + (char *)sin);
	if (sin->sin_addr.s_addr == sin_m.sin_addr.s_addr) {
		if (sdl->sdl_family == AF_LINK &&
		    (rtm->rtm_flags & RTF_LLINFO) &&
		    !(rtm->rtm_flags & RTF_GATEWAY)) switch (sdl->sdl_type) {
		case IFT_ETHER: case IFT_FDDI: case IFT_ISO88023:
		case IFT_ISO88024: case IFT_ISO88025:
			goto delete;
		}
E 18
	}
D 18
	close(s);
	printf("%s (%s) deleted\n", host, inet_ntoa(sin->sin_addr));
E 18
I 18
	if (sin_m.sin_other & SIN_PROXY) {
		fprintf(stderr, "delete: can't locate %s\n",host);
		return (1);
	} else {
		sin_m.sin_other = SIN_PROXY;
		goto tryagain;
	}
delete:
	if (sdl->sdl_family != AF_LINK) {
		printf("cannot locate %s\n", host);
		return (1);
	}
D 27
	if (rtmsg(RTM_DELETE) == 0)
		printf("%s (%s) deleted\n", host, inet_ntoa(sin->sin_addr));
E 27
I 27
	if (rtmsg(RTM_DELETE))
		return (1);
	printf("%s (%s) deleted\n", host, inet_ntoa(sin->sin_addr));
	return (0);
E 27
E 18
}

D 18
struct nlist nl[] = {
#define	X_ARPTAB	0
	{ "_arptab" },
#define	X_ARPTAB_SIZE	1
	{ "_arptab_size" },
I 11
D 19
#define	N_SYSMAP	2
	{ "_Sysmap" },
#define	N_SYSSIZE	3
	{ "_Syssize" },
E 19
E 11
	{ "" },
};

I 11
D 19
static struct pte *Sysmap;

E 19
E 18
E 11
/*
 * Dump the entire arp table
 */
I 27
void
E 27
D 18
dump(kernel, mem)
	char *kernel, *mem;
E 18
I 18
dump(addr)
D 27
u_long addr;
E 27
I 27
	u_long addr;
E 27
E 18
{
I 18
D 24
	int sz, needed, rlen;
	long op = KINFO_RT_FLAGS | (((long)AF_INET) << 16);
E 24
I 24
	int mib[6];
	size_t needed;
E 24
D 27
	char *host, *malloc(), *lim, *buf, *next;
E 27
I 27
	char *host, *lim, *buf, *next;
E 27
	struct rt_msghdr *rtm;
	struct sockaddr_inarp *sin;
	struct sockaddr_dl *sdl;
E 18
D 11
	int mf, arptab_size, sz;
E 11
I 11
	extern int h_errno;
E 11
D 18
	struct arptab *at;
E 18
	struct hostent *hp;
D 11
	char *host;
I 8
	int bynumber = 0;
I 10
	extern int h_errno;
E 11
I 11
D 18
	int bynumber, mf, arptab_size, sz;
	char *host, *malloc();
	off_t lseek();
E 18
E 11
E 10
E 8

D 11
	nlist(kernel, nl);
	if(nl[X_ARPTAB_SIZE].n_type == 0) {
E 11
I 11
D 18
D 19
	if (nlist(kernel, nl) < 0 || nl[X_ARPTAB_SIZE].n_type == 0) {
E 11
		fprintf(stderr, "arp: %s: bad namelist\n", kernel);
E 19
I 19
	if (kvm_openfiles(kernel, mem, NULL) == -1) {
		fprintf(stderr, "arp: kvm_openfiles: %s\n", kvm_geterr());
E 19
		exit(1);
	}
D 11
	mf = open(mem, 0);
	if(mf < 0) {
E 11
I 11
D 19
	mf = open(mem, O_RDONLY);
	if (mf < 0) {
E 11
D 13
		fprintf(fprintf, "arp: cannot open %s\n", mem);
E 13
I 13
		fprintf(stderr, "arp: cannot open %s\n", mem);
E 19
I 19
	if (kvm_nlist(nl) < 0 || nl[X_ARPTAB_SIZE].n_type == 0) {
		fprintf(stderr, "arp: %s: bad namelist\n", kernel);
E 19
E 13
		exit(1);
	}
D 11
	lseek(mf, (long)nl[X_ARPTAB_SIZE].n_value, 0);
E 11
I 11
D 19
	if (kflag) {
		off_t off;

		Sysmap = (struct pte *)
		   malloc((u_int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
		if (!Sysmap) {
			fputs("arp: can't get memory for Sysmap.\n", stderr);
			exit(1);
E 18
I 18
D 24
	if ((needed = getkerninfo(op, 0, 0, RTF_LLINFO)) < 0)
		quit("route-getkerninfo-estimate");
E 24
I 24
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_INET;
	mib[4] = NET_RT_FLAGS;
	mib[5] = RTF_LLINFO;
	if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
D 27
		quit("route-sysctl-estimate");
E 27
I 27
		err(1, "route-sysctl-estimate");
E 27
E 24
	if ((buf = malloc(needed)) == NULL)
D 27
		quit("malloc");
E 27
I 27
		err(1, "malloc");
E 27
D 24
	if ((rlen = getkerninfo(op, buf, &needed, RTF_LLINFO)) < 0)
E 24
I 24
	if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
E 24
D 27
		quit("actual retrieval of routing table");
E 27
I 27
		err(1, "actual retrieval of routing table");
E 27
D 24
	lim = buf + rlen;
E 24
I 24
	lim = buf + needed;
E 24
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)next;
		sin = (struct sockaddr_inarp *)(rtm + 1);
		sdl = (struct sockaddr_dl *)(sin + 1);
		if (addr) {
			if (addr != sin->sin_addr.s_addr)
				continue;
			found_entry = 1;
E 18
		}
D 18
		off = nl[N_SYSMAP].n_value & ~KERNBASE;
		(void)lseek(mf, off, L_SET);
		(void)read(mf, (char *)Sysmap,
		    (int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
	}
	klseek(mf, (long)nl[X_ARPTAB_SIZE].n_value, L_SET);
E 11
	read(mf, &arptab_size, sizeof arptab_size);
D 11
	if (arptab_size <=0 || arptab_size > 1000) {
E 11
I 11
	if (arptab_size <= 0 || arptab_size > 1000) {
E 19
I 19
	if (kvm_read((void *)(nl[X_ARPTAB_SIZE].n_value),
		     &arptab_size, sizeof arptab_size) == -1 ||
	    arptab_size <= 0 || arptab_size > 1000) {
E 19
E 11
		fprintf(stderr, "arp: %s: namelist wrong\n", kernel);
		exit(1);
	}
	sz = arptab_size * sizeof (struct arptab);
D 11
	at = (struct arptab *)malloc(sz);
E 11
I 11
	at = (struct arptab *)malloc((u_int)sz);
E 11
	if (at == NULL) {
D 11
		fprintf(stderr, "arp: can't get memory for arptab\n");
E 11
I 11
		fputs("arp: can't get memory for arptab.\n", stderr);
E 11
		exit(1);
	}
D 11
	lseek(mf, (long)nl[X_ARPTAB].n_value, 0);
E 11
I 11
D 19
	klseek(mf, (long)nl[X_ARPTAB].n_value, L_SET);
E 11
	if (read(mf, (char *)at, sz) != sz) {
E 19
I 19
	if (kvm_read((void *)(nl[X_ARPTAB].n_value), (char *)at, sz) == -1) {
E 19
		perror("arp: error reading arptab");
		exit(1);
	}
D 19
	close(mf);
E 19
D 11
	for (; arptab_size-- > 0; at++) {
E 11
I 11
	for (bynumber = 0; arptab_size-- > 0; at++) {
E 11
		if (at->at_iaddr.s_addr == 0 || at->at_flags == 0)
			continue;
D 8
		hp = gethostbyaddr((caddr_t)&at->at_iaddr, sizeof at->at_iaddr,
			AF_INET);
E 8
I 8
		if (bynumber == 0)
			hp = gethostbyaddr((caddr_t)&at->at_iaddr,
			    sizeof at->at_iaddr, AF_INET);
E 18
I 18
		if (nflag == 0)
			hp = gethostbyaddr((caddr_t)&(sin->sin_addr),
			    sizeof sin->sin_addr, AF_INET);
E 18
		else
			hp = 0;
E 8
		if (hp)
			host = hp->h_name;
D 8
		else
E 8
I 8
		else {
E 8
			host = "?";
I 8
			if (h_errno == TRY_AGAIN)
D 18
				bynumber = 1;
E 18
I 18
				nflag = 1;
E 18
		}
E 8
D 18
		printf("%s (%s) at ", host, inet_ntoa(at->at_iaddr));
		if (at->at_flags & ATF_COM)
D 2
			ether_print(&at->at_enaddr);
E 2
I 2
			ether_print(at->at_enaddr);
E 18
I 18
		printf("%s (%s) at ", host, inet_ntoa(sin->sin_addr));
		if (sdl->sdl_alen)
D 27
			ether_print(LLADDR(sdl));
E 27
I 27
			ether_print((u_char *)LLADDR(sdl));
E 27
E 18
E 2
		else
			printf("(incomplete)");
D 6
		if (!(at->at_flags & ATF_PERM)) printf(" temporary");
E 6
I 6
D 11
		if (at->at_flags & ATF_PERM) printf(" permanent");
E 6
		if (at->at_flags & ATF_PUBL) printf(" published");
I 6
		if (at->at_flags & ATF_USETRAILERS) printf(" trailers");
E 11
I 11
D 18
		if (at->at_flags & ATF_PERM)
E 18
I 18
		if (rtm->rtm_rmx.rmx_expire == 0)
E 18
			printf(" permanent");
D 18
		if (at->at_flags & ATF_PUBL)
			printf(" published");
		if (at->at_flags & ATF_USETRAILERS)
E 18
I 18
		if (sin->sin_other & SIN_PROXY)
			printf(" published (proxy only)");
D 21
		if (rtm->rtm_flags & RTF_PROTO1)
E 18
			printf(" trailers");
E 21
I 18
		if (rtm->rtm_addrs & RTA_NETMASK) {
			sin = (struct sockaddr_inarp *)
				(sdl->sdl_len + (char *)sdl);
			if (sin->sin_addr.s_addr == 0xffffffff)
				printf(" published");
			if (sin->sin_len != 8)
				printf("(wierd)");
		}
E 18
E 11
E 6
		printf("\n");
	}
D 19
}

I 27
void
E 27
I 11
D 18
/*
 * Seek into the kernel for a value.
 */
klseek(fd, base, off)
	int fd, off;
	off_t base;
{
	off_t lseek();

	if (kflag) {	/* get kernel pte */
		base &= ~KERNBASE;
		base = ctob(Sysmap[btop(base)].pg_pfnum) + (base & PGOFSET);
	}
	(void)lseek(fd, base, off);
E 19
}

E 18
E 11
D 2
ether_print(ea)
	struct ether_addr *ea;
E 2
I 2
ether_print(cp)
	u_char *cp;
E 2
{
D 2
	u_char *cp = &ea->ether_addr_octet[0];

E 2
	printf("%x:%x:%x:%x:%x:%x", cp[0], cp[1], cp[2], cp[3], cp[4], cp[5]);
}

I 27
int
E 27
ether_aton(a, n)
	char *a;
D 2
	struct ether_addr *n;
E 2
I 2
	u_char *n;
E 2
{
	int i, o[6];

	i = sscanf(a, "%x:%x:%x:%x:%x:%x", &o[0], &o[1], &o[2],
					   &o[3], &o[4], &o[5]);
	if (i != 6) {
		fprintf(stderr, "arp: invalid Ethernet address '%s'\n", a);
		return (1);
	}
	for (i=0; i<6; i++)
D 2
		n->ether_addr_octet[i] = o[i];
E 2
I 2
		n[i] = o[i];
E 2
	return (0);
}

I 27
void
E 27
usage()
{
D 11
	printf("Usage: arp hostname\n");
E 11
I 11
	printf("usage: arp hostname\n");
E 11
D 16
	printf("       arp -a [/vmunix] [/dev/kmem]\n");
E 16
I 16
	printf("       arp -a [kernel] [kernel_memory]\n");
E 16
	printf("       arp -d hostname\n");
D 10
	printf("       arp -s hostname ether_addr [temp] [pub]\n");
E 10
I 10
D 21
	printf("       arp -s hostname ether_addr [temp] [pub] [trail]\n");
E 21
I 21
	printf("       arp -s hostname ether_addr [temp] [pub]\n");
E 21
E 10
	printf("       arp -f filename\n");
I 18
	exit(1);
}

I 27
int
E 27
rtmsg(cmd)
I 27
	int cmd;
E 27
{
	static int seq;
	int rlen;
	register struct rt_msghdr *rtm = &m_rtmsg.m_rtm;
	register char *cp = m_rtmsg.m_space;
	register int l;

	errno = 0;
	if (cmd == RTM_DELETE)
		goto doit;
	bzero((char *)&m_rtmsg, sizeof(m_rtmsg));
	rtm->rtm_flags = flags;
	rtm->rtm_version = RTM_VERSION;

	switch (cmd) {
	default:
		fprintf(stderr, "arp: internal wrong cmd\n");
		exit(1);
	case RTM_ADD:
		rtm->rtm_addrs |= RTA_GATEWAY;
		rtm->rtm_rmx.rmx_expire = expire_time;
		rtm->rtm_inits = RTV_EXPIRE;
D 20
		rtm->rtm_flags |= RTF_HOST;
E 20
I 20
		rtm->rtm_flags |= (RTF_HOST | RTF_STATIC);
E 20
		sin_m.sin_other = 0;
		if (doing_proxy) {
			if (export_only)
				sin_m.sin_other = SIN_PROXY;
			else {
				rtm->rtm_addrs |= RTA_NETMASK;
				rtm->rtm_flags &= ~RTF_HOST;
			}
		}
I 26
		/* FALLTHROUGH */
E 26
	case RTM_GET:
		rtm->rtm_addrs |= RTA_DST;
	}
#define NEXTADDR(w, s) \
	if (rtm->rtm_addrs & (w)) { \
		bcopy((char *)&s, cp, sizeof(s)); cp += sizeof(s);}

	NEXTADDR(RTA_DST, sin_m);
	NEXTADDR(RTA_GATEWAY, sdl_m);
	NEXTADDR(RTA_NETMASK, so_mask);

	rtm->rtm_msglen = cp - (char *)&m_rtmsg;
doit:
	l = rtm->rtm_msglen;
	rtm->rtm_seq = ++seq;
	rtm->rtm_type = cmd;
	if ((rlen = write(s, (char *)&m_rtmsg, l)) < 0) {
		if (errno != ESRCH || cmd != RTM_DELETE) {
			perror("writing to routing socket");
			return (-1);
		}
	}
	do {
		l = read(s, (char *)&m_rtmsg, sizeof(m_rtmsg));
	} while (l > 0 && (rtm->rtm_seq != seq || rtm->rtm_pid != pid));
	if (l < 0)
		(void) fprintf(stderr, "arp: read from routing socket: %s\n",
		    strerror(errno));
	return (0);
D 27
}

quit(msg)
char *msg;
{
	fprintf(stderr, "%s\n", msg);
E 18
I 11
	exit(1);
E 27
E 11
}
E 1
