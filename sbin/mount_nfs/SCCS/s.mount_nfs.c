h14263
s 00001/00000/00718
d D 8.11 95/05/04 16:33:25 mckusick 21 20
c add NFS_ARGSVERSION to nfs_args structure
e
s 00008/00009/00710
d D 8.10 95/04/28 10:41:44 bostic 20 19
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00006/00003/00713
d D 8.9 95/03/30 14:58:22 mckusick 19 18
c bug fix for OSF/1 servers
e
s 00003/00001/00713
d D 8.8 95/03/29 21:30:04 mckusick 18 17
c minor nits from Rick Macklem
e
s 00242/00058/00472
d D 8.7 95/03/29 15:30:22 mckusick 17 16
c update for version 3 from Rick Macklem
e
s 00001/00001/00529
d D 8.6 95/01/07 17:04:36 mckusick 16 15
c usage on error (from cgd)
e
s 00007/00003/00523
d D 8.5 94/10/09 21:55:26 mckusick 15 14
c do not assume that root file handle can always be obtained
c by UDP (from mycroft)
e
s 00001/00000/00525
d D 8.4 94/10/09 20:59:06 mckusick 14 13
c better error message on failure (from mycroft)
e
s 00000/00007/00525
d D 8.3 94/03/27 15:42:34 bostic 13 12
c Rick Macklem notes that NFS should get MNT_RDONLY and MNT_UPDATE
c add MNT_FORCE so that MNT_UPDATE can be forced
e
s 00061/00101/00471
d D 8.2 94/03/27 13:05:59 bostic 12 11
c Jan-Simon Pendry's and my new mount code
e
s 00005/00005/00567
d D 8.1 93/06/05 11:02:59 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00571
d D 5.10 93/02/03 10:47:32 mckusick 10 9
c cleanup from Rick Macklem
e
s 00001/00001/00575
d D 5.9 92/10/26 08:44:41 hibler 9 8
c we allow -g as well
e
s 00003/00002/00573
d D 5.8 92/10/21 15:30:44 mckusick 8 7
c we do allow -F flags
e
s 00003/00003/00572
d D 5.7 92/10/05 10:03:46 bostic 7 6
c err doesn't need newlines, thanks, Craig!
e
s 00000/00005/00577
d D 5.6 92/10/04 13:00:11 bostic 6 5
c let mount(2) do existence and type checking
e
s 00293/00195/00289
d D 5.5 92/10/04 12:45:18 bostic 5 4
c Welcome to the wonderful world of ANSI C!  (Not to mention prototypes
c and general cleanliness...)
e
s 00003/00003/00481
d D 5.4 92/04/03 20:51:23 torek 4 3
c 1,$s/exit()/exit(0)/
e
s 00001/00000/00483
d D 5.3 92/03/17 17:24:00 mckusick 3 2
c add set_rpc_maxgrouplist() to control maximum number of groups used
e
s 00004/00001/00479
d D 5.2 92/03/17 17:13:27 mckusick 2 1
c add -P option to request use of reserved port
e
s 00480/00000/00000
d D 5.1 92/01/06 16:31:44 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
/*
D 11
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 12
 * Copyright (c) 1992, 1993
E 12
I 12
 * Copyright (c) 1992, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 11
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
D 12
"%Z% Copyright (c) 1992, 1993\n\
E 12
I 12
"%Z% Copyright (c) 1992, 1993, 1994\n\
E 12
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 5
#include <stdio.h>
#include <signal.h>
#include <strings.h>
#include <sys/syslog.h>
E 5
#include <sys/param.h>
D 5
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/ucred.h>
E 5
#include <sys/mount.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
D 5
#include <netdb.h>
E 5
I 5
#include <sys/stat.h>
#include <sys/syslog.h>

E 5
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
I 5

E 5
#ifdef ISO
#include <netiso/iso.h>
#endif
I 5

E 5
D 17
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
I 10
#include <kerberosIV/des.h>
E 10
#include <kerberosIV/krb.h>
#endif
I 5

E 5
#include <nfs/rpcv2.h>
D 17
#include <nfs/nfsv2.h>
E 17
I 17
#include <nfs/nfsproto.h>
E 17
I 5
#define KERNEL
E 5
#include <nfs/nfs.h>
I 5
#undef KERNEL
E 5
#include <nfs/nqnfs.h>

D 5
int xdr_dir(), xdr_fh();
E 5
I 5
#include <arpa/inet.h>

#include <ctype.h>
I 12
#include <err.h>
E 12
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

I 12
#include "mntopts.h"

I 17
#define	ALTF_BG		0x1
#define ALTF_NOCONN	0x2
#define ALTF_DUMBTIMR	0x4
#define ALTF_INTR	0x8
#define ALTF_KERB	0x10
#define ALTF_NFSV3	0x20
#define ALTF_RDIRPLUS	0x40
#define	ALTF_MNTUDP	0x80
#define ALTF_RESVPORT	0x100
#define ALTF_SEQPACKET	0x200
#define ALTF_NQNFS	0x400
#define ALTF_SOFT	0x800
#define ALTF_TCP	0x1000

E 17
D 13
/*
 * XXX
 * This is without question incorrect -- not sure what the right
 * values are.
 */
E 13
struct mntopt mopts[] = {
	MOPT_STDOPTS,
D 13
	MOPT_ASYNC,
E 13
	MOPT_FORCE,
D 13
	MOPT_SYNCHRONOUS,
E 13
	MOPT_UPDATE,
I 17
	{ "bg", 0, ALTF_BG, 1 },
	{ "conn", 1, ALTF_NOCONN, 1 },
	{ "dumbtimer", 0, ALTF_DUMBTIMR, 1 },
	{ "intr", 0, ALTF_INTR, 1 },
#ifdef NFSKERB
	{ "kerb", 0, ALTF_KERB, 1 },
#endif
	{ "nfsv3", 0, ALTF_NFSV3, 1 },
	{ "rdirplus", 0, ALTF_RDIRPLUS, 1 },
	{ "mntudp", 0, ALTF_MNTUDP, 1 },
	{ "resvport", 0, ALTF_RESVPORT, 1 },
#ifdef ISO
	{ "seqpacket", 0, ALTF_SEQPACKET, 1 },
#endif
	{ "nqnfs", 0, ALTF_NQNFS, 1 },
	{ "soft", 0, ALTF_SOFT, 1 },
	{ "tcp", 0, ALTF_TCP, 1 },
E 17
	{ NULL }
};

E 12
E 5
struct nfs_args nfsdefargs = {
I 21
	NFS_ARGSVERSION,
E 21
	(struct sockaddr *)0,
	sizeof (struct sockaddr_in),
	SOCK_DGRAM,
	0,
D 17
	(nfsv2fh_t *)0,
E 17
I 17
	(u_char *)0,
E 17
	0,
I 17
	0,
E 17
	NFS_WSIZE,
	NFS_RSIZE,
D 17
	NFS_TIMEO,
E 17
I 17
	NFS_READDIRSIZE,
	10,
E 17
	NFS_RETRANS,
	NFS_MAXGRPS,
	NFS_DEFRAHEAD,
	NQ_DEFLEASE,
	NQ_DEADTHRESH,
	(char *)0,
};

struct nfhret {
D 17
	u_long	stat;
	nfsv2fh_t nfh;
E 17
I 17
	u_long		stat;
	long		vers;
	long		auth;
	long		fhsize;
	u_char		nfh[NFSX_V3FHMAX];
E 17
};
#define	DEF_RETRY	10000
#define	BGRND	1
#define	ISBGRND	2
int retrycnt = DEF_RETRY;
int opflags = 0;
I 17
int nfsproto = IPPROTO_UDP;
int mnttcp_ok = 1;
E 17
D 5
extern int errno;
E 5

D 5
#ifdef ISO
struct iso_addr *iso_addr();
#endif

E 5
D 17
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
char inst[INST_SZ];
char realm[REALM_SZ];
D 17
KTEXT_ST kt;
E 17
I 17
struct {
	u_long		kind;
	KTEXT_ST	kt;
} ktick;
struct nfsrpc_nickverf kverf;
struct nfsrpc_fullblock kin, kout;
NFSKERBKEY_T kivec;
CREDENTIALS kcr;
struct timeval ktv;
NFSKERBKEYSCHED_T kerb_keysched;
E 17
#endif

D 5
main(argc, argv, arge)
E 5
I 5
D 12
void	err __P((const char *, ...));
E 12
int	getnfsargs __P((char *, struct nfs_args *));
#ifdef ISO
struct	iso_addr *iso_addr __P((const char *));
#endif
void	set_rpc_maxgrouplist __P((int));
__dead	void usage __P((void));
D 12
void	warn __P((const char *, ...));
E 12
int	xdr_dir __P((XDR *, char *));
int	xdr_fh __P((XDR *, struct nfhret *));

int
main(argc, argv)
E 5
	int argc;
D 5
	char **argv;
	char **arge;
E 5
I 5
	char *argv[];
E 5
{
D 5
	struct nfs_args nfsargs;
E 5
	register int c;
D 5
	register struct nfs_args *nfsargsp = &nfsargs;
E 5
I 5
	register struct nfs_args *nfsargsp;
	struct nfs_args nfsargs;
E 5
	struct nfsd_cargs ncd;
D 5
	int num, flags = 0, match = 1, i, nfssvc_flag;
	char *spec, *name;
	uid_t last_ruid = -1;
	extern int optind;
	extern char *optarg;
E 5
I 5
D 6
	struct stat sb;
E 6
D 12
	int flags, i, nfssvc_flag, num;
E 12
I 12
D 17
	int mntflags, i, nfssvc_flag, num;
E 17
I 17
	int mntflags, altflags, i, nfssvc_flag, num;
E 17
E 12
	char *name, *p, *spec;
I 12
	int error = 0;
E 12
D 17
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
	uid_t last_ruid;
D 17
#endif
E 17
E 5

D 17
#ifdef KERBEROS
E 17
D 5
	strcpy(realm, KRB_REALM);
E 5
I 5
	last_ruid = -1;
	(void)strcpy(realm, KRB_REALM);
E 5
D 17
#endif
E 17
I 17
	if (sizeof (struct nfsrpc_nickverf) != RPCX_NICKVERF ||
	    sizeof (struct nfsrpc_fullblock) != RPCX_FULLBLOCK ||
	    ((char *)&ktick.kt) - ((char *)&ktick) != NFSX_UNSIGNED ||
	    ((char *)ktick.kt.dat) - ((char *)&ktick) != 2 * NFSX_UNSIGNED)
		fprintf(stderr, "Yikes! NFSKERB structs not packed!!\n");
#endif /* NFSKERB */
E 17
D 5
	nfsargs = nfsdefargs;
E 5
	retrycnt = DEF_RETRY;
I 5

E 5
D 12
	if (argc <= 1)
D 5
		Usage(argc, argv);
D 2
	while ((c = getopt(argc, argv, "bsiTpMlqdckF:R:r:w:t:x:g:a:L:D:Km:"))
E 2
I 2
	while ((c = getopt(argc, argv, "bsiTpMlqdckPF:R:r:w:t:x:g:a:L:D:Km:"))
E 2
		!= EOF)
E 5
I 5
		usage();

	flags = 0;
E 12
I 12
	mntflags = 0;
I 17
	altflags = 0;
E 17
E 12
	nfsargs = nfsdefargs;
	nfsargsp = &nfsargs;
	while ((c = getopt(argc, argv,
D 12
	    "a:bcdD:F:g:iKklL:Mm:PpqR:r:sTt:w:x:")) != EOF)
E 12
I 12
D 17
	    "a:bcdD:g:iKklL:Mm:o:PpqR:r:sTt:w:x:")) != EOF)
E 17
I 17
	    "3a:bcdD:g:I:iKL:lm:o:PpqR:r:sTt:w:x:U")) != EOF)
E 17
E 12
E 5
		switch (c) {
I 17
		case '3':
			nfsargsp->flags |= NFSMNT_NFSV3;
			break;
E 17
I 5
		case 'a':
			num = strtol(optarg, &p, 10);
			if (*p || num < 0)
D 12
				err("illegal -a value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -a value -- %s", optarg);
E 12
			nfsargsp->readahead = num;
			nfsargsp->flags |= NFSMNT_READAHEAD;
			break;
E 5
		case 'b':
			opflags |= BGRND;
			break;
D 5
		case 's':
			nfsargsp->flags |= NFSMNT_SOFT;
E 5
I 5
		case 'c':
			nfsargsp->flags |= NFSMNT_NOCONN;
E 5
			break;
I 5
		case 'D':
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
D 12
				err("illegal -D value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -D value -- %s", optarg);
E 12
			nfsargsp->deadthresh = num;
			nfsargsp->flags |= NFSMNT_DEADTHRESH;
			break;
		case 'd':
			nfsargsp->flags |= NFSMNT_DUMBTIMR;
			break;
D 12
		case 'F':
			num = strtol(optarg, &p, 10);
D 8
			if (*p || num != 0)
E 8
I 8
			if (*p)
E 8
				err("illegal -F value -- %s", optarg);
D 8
			flags = num;
E 8
I 8
			if (num != 0)
				flags = num;
E 8
			break;
E 12
		case 'g':
			num = strtol(optarg, &p, 10);
D 9
			if (*p || num > 0)
E 9
I 9
			if (*p || num <= 0)
E 9
D 12
				err("illegal -g value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -g value -- %s", optarg);
E 12
			set_rpc_maxgrouplist(num);
			nfsargsp->maxgrouplist = num;
			nfsargsp->flags |= NFSMNT_MAXGRPS;
			break;
I 17
		case 'I':
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
				errx(1, "illegal -I value -- %s", optarg);
			nfsargsp->readdirsize = num;
			nfsargsp->flags |= NFSMNT_READDIRSIZE;
			break;
E 17
E 5
		case 'i':
			nfsargsp->flags |= NFSMNT_INT;
			break;
D 5
		case 'T':
			nfsargsp->sotype = SOCK_STREAM;
E 5
I 5
D 17
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
		case 'K':
			nfsargsp->flags |= NFSMNT_KERB;
E 5
			break;
D 5
#ifdef ISO
		case 'p':
			nfsargsp->sotype = SOCK_SEQPACKET;
			break;
E 5
#endif
D 5
		case 'M':
			nfsargsp->flags |= NFSMNT_MYWRITE;
E 5
I 5
D 17
		case 'k':
			nfsargsp->flags |= NFSMNT_NQLOOKLEASE;
E 5
			break;
E 17
I 5
		case 'L':
			num = strtol(optarg, &p, 10);
			if (*p || num < 2)
D 12
				err("illegal -L value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -L value -- %s", optarg);
E 12
			nfsargsp->leaseterm = num;
			nfsargsp->flags |= NFSMNT_LEASETERM;
			break;
E 5
		case 'l':
D 17
			nfsargsp->flags |= NFSMNT_RDIRALOOK;
E 17
I 17
			nfsargsp->flags |= NFSMNT_RDIRPLUS;
E 17
			break;
D 5
		case 'q':
			nfsargsp->flags |= NFSMNT_NQNFS;
E 5
I 5
D 17
		case 'M':
			nfsargsp->flags |= NFSMNT_MYWRITE;
E 5
			break;
D 5
		case 'd':
			nfsargsp->flags |= NFSMNT_DUMBTIMR;
E 5
I 5
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
		case 'm':
			(void)strncpy(realm, optarg, REALM_SZ - 1);
			realm[REALM_SZ - 1] = '\0';
E 5
			break;
D 5
		case 'c':
			nfsargsp->flags |= NFSMNT_NOCONN;
			break;
		case 'k':
			nfsargsp->flags |= NFSMNT_NQLOOKLEASE;
I 2
			break;
E 5
I 5
#endif
I 12
		case 'o':
D 17
			getmntopts(optarg, mopts, &mntflags);
E 17
I 17
			getmntopts(optarg, mopts, &mntflags, &altflags);
			if(altflags & ALTF_BG)
				opflags |= BGRND;
			if(altflags & ALTF_NOCONN)
				nfsargsp->flags |= NFSMNT_NOCONN;
			if(altflags & ALTF_DUMBTIMR)
				nfsargsp->flags |= NFSMNT_DUMBTIMR;
			if(altflags & ALTF_INTR)
				nfsargsp->flags |= NFSMNT_INT;
#ifdef NFSKERB
			if(altflags & ALTF_KERB)
				nfsargsp->flags |= NFSMNT_KERB;
#endif
			if(altflags & ALTF_NFSV3)
				nfsargsp->flags |= NFSMNT_NFSV3;
			if(altflags & ALTF_RDIRPLUS)
				nfsargsp->flags |= NFSMNT_RDIRPLUS;
			if(altflags & ALTF_MNTUDP)
				mnttcp_ok = 0;
			if(altflags & ALTF_RESVPORT)
				nfsargsp->flags |= NFSMNT_RESVPORT;
#ifdef ISO
			if(altflags & ALTF_SEQPACKET)
				nfsargsp->sotype = SOCK_SEQPACKET;
#endif
			if(altflags & ALTF_NQNFS)
				nfsargsp->flags |= (NFSMNT_NQNFS|NFSMNT_NFSV3);
			if(altflags & ALTF_SOFT)
				nfsargsp->flags |= NFSMNT_SOFT;
			if(altflags & ALTF_TCP) {
				nfsargsp->sotype = SOCK_STREAM;
				nfsproto = IPPROTO_TCP;
			}
			altflags = 0;
E 17
			break;
E 12
E 5
		case 'P':
			nfsargsp->flags |= NFSMNT_RESVPORT;
E 2
			break;
D 5
		case 'F':
			if ((num = atoi(optarg)) != 0)
				flags = num;
E 5
I 5
#ifdef ISO
		case 'p':
			nfsargsp->sotype = SOCK_SEQPACKET;
E 5
			break;
I 5
#endif
		case 'q':
D 17
			nfsargsp->flags |= NFSMNT_NQNFS;
E 17
I 17
			nfsargsp->flags |= (NFSMNT_NQNFS | NFSMNT_NFSV3);
E 17
			break;
E 5
		case 'R':
D 5
			if ((num = atoi(optarg)) > 0)
				retrycnt = num;
E 5
I 5
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
D 12
				err("illegal -R value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -R value -- %s", optarg);
E 12
			retrycnt = num;
E 5
			break;
		case 'r':
D 5
			if ((num = atoi(optarg)) > 0) {
				nfsargsp->rsize = num;
				nfsargsp->flags |= NFSMNT_RSIZE;
			}
E 5
I 5
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
D 12
				err("illegal -r value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -r value -- %s", optarg);
E 12
			nfsargsp->rsize = num;
			nfsargsp->flags |= NFSMNT_RSIZE;
E 5
			break;
D 5
		case 'w':
			if ((num = atoi(optarg)) > 0) {
				nfsargsp->wsize = num;
				nfsargsp->flags |= NFSMNT_WSIZE;
			}
E 5
I 5
		case 's':
			nfsargsp->flags |= NFSMNT_SOFT;
E 5
			break;
I 5
		case 'T':
			nfsargsp->sotype = SOCK_STREAM;
I 17
			nfsproto = IPPROTO_TCP;
E 17
			break;
E 5
		case 't':
D 5
			if ((num = atoi(optarg)) > 0) {
				nfsargsp->timeo = num;
				nfsargsp->flags |= NFSMNT_TIMEO;
			}
E 5
I 5
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
D 12
				err("illegal -t value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -t value -- %s", optarg);
E 12
			nfsargsp->timeo = num;
			nfsargsp->flags |= NFSMNT_TIMEO;
E 5
			break;
I 5
		case 'w':
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
D 12
				err("illegal -w value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -w value -- %s", optarg);
E 12
			nfsargsp->wsize = num;
			nfsargsp->flags |= NFSMNT_WSIZE;
			break;
E 5
		case 'x':
D 5
			if ((num = atoi(optarg)) > 0) {
				nfsargsp->retrans = num;
				nfsargsp->flags |= NFSMNT_RETRANS;
			}
E 5
I 5
			num = strtol(optarg, &p, 10);
			if (*p || num <= 0)
D 12
				err("illegal -x value -- %s", optarg);
E 12
I 12
				errx(1, "illegal -x value -- %s", optarg);
E 12
			nfsargsp->retrans = num;
			nfsargsp->flags |= NFSMNT_RETRANS;
E 5
			break;
I 17
		case 'U':
			mnttcp_ok = 0;
			break;
E 17
D 5
		case 'g':
			if ((num = atoi(optarg)) > 0) {
I 3
				set_rpc_maxgrouplist(num);
E 3
				nfsargsp->maxgrouplist = num;
				nfsargsp->flags |= NFSMNT_MAXGRPS;
			}
			break;
		case 'a':
			if ((num = atoi(optarg)) >= 0) {
				nfsargsp->readahead = num;
				nfsargsp->flags |= NFSMNT_READAHEAD;
			}
			break;
		case 'L':
			if ((num = atoi(optarg)) >= 2) {
				nfsargsp->leaseterm = num;
				nfsargsp->flags |= NFSMNT_LEASETERM;
			}
			break;
		case 'D':
			if ((num = atoi(optarg)) > 0) {
				nfsargsp->deadthresh = num;
				nfsargsp->flags |= NFSMNT_DEADTHRESH;
			}
			break;
#ifdef KERBEROS
		case 'K':
			nfsargsp->flags |= NFSMNT_KERB;
			break;
		case 'm':
			strncpy(realm, optarg, REALM_SZ - 1);
			realm[REALM_SZ - 1] = '\0';
			break;
#endif /* KERBEROS */
E 5
		default:
D 5
			Usage(argc, argv);
E 5
I 5
			usage();
E 5
D 12
		};
E 12
I 12
			break;
		}
	argc -= optind;
	argv += optind;
E 12
D 5
	if ((argc - optind) == 2) {
		spec = argv[optind];
		name = argv[optind + 1];
	} else
		Usage(argc, argv);
	if (getnfsargs(spec, nfsargsp)) {
		if (mount(MOUNT_NFS, name, flags, nfsargsp))
			exit(1);
		if (nfsargsp->flags & (NFSMNT_NQNFS | NFSMNT_KERB)) {
			if ((opflags & ISBGRND) == 0) {
				if (i = fork()) {
					if (i == -1) {
						perror("nqnfs");
						exit(1);
					}
D 4
					exit();
E 4
I 4
					exit(0);
E 4
				}
				(void) setsid();
				(void) close(0);
				(void) close(1);
				(void) close(2);
				(void) chdir("/");
E 5
I 5

D 12
	if ((argc - optind) != 2)
		usage();
E 12
I 12
D 18
	if (argc != 2)
E 18
I 18
	if (argc != 2) {
E 18
D 16
		error = 1;
E 16
I 16
		usage();
I 18
		/* NOTREACHED */
	}
E 18
E 16
E 12

D 12
	spec = argv[optind];
	name = argv[optind + 1];
E 12
I 12
	spec = *argv++;
	name = *argv;
E 12

	if (!getnfsargs(spec, nfsargsp))
		exit(1);
D 6
	if (stat(name, &sb) < 0)
		err("%s: %s", name, strerror(errno));
	if (!S_ISDIR(sb.st_mode))
		err("%s: not a directory", name);
E 6
D 12
	if (mount(MOUNT_NFS, name, flags, nfsargsp))
D 7
		err("mount: %s: %s\n", name, strerror(errno));
E 7
I 7
		err("mount: %s: %s", name, strerror(errno));
E 12
I 12
D 17
	if (mount(MOUNT_NFS, name, mntflags, nfsargsp))
E 17
I 17

	if (mount("nfs", name, mntflags, nfsargsp))
E 17
		err(1, "%s", name);
E 12
E 7
	if (nfsargsp->flags & (NFSMNT_NQNFS | NFSMNT_KERB)) {
		if ((opflags & ISBGRND) == 0) {
			if (i = fork()) {
				if (i == -1)
D 7
					err("nqnfs 1: %s\n", strerror(errno));
E 7
I 7
D 12
					err("nqnfs 1: %s", strerror(errno));
E 12
I 12
					err(1, "nqnfs 1");
E 12
E 7
				exit(0);
E 5
			}
D 5
			openlog("mount_nfs:", LOG_PID, LOG_DAEMON);
			nfssvc_flag = NFSSVC_MNTD;
			ncd.ncd_dirp = name;
			while (nfssvc(nfssvc_flag, (caddr_t)&ncd) < 0) {
			    if (errno == ENEEDAUTH) {
E 5
I 5
			(void) setsid();
			(void) close(STDIN_FILENO);
			(void) close(STDOUT_FILENO);
			(void) close(STDERR_FILENO);
			(void) chdir("/");
		}
		openlog("mount_nfs:", LOG_PID, LOG_DAEMON);
		nfssvc_flag = NFSSVC_MNTD;
		ncd.ncd_dirp = name;
		while (nfssvc(nfssvc_flag, (caddr_t)&ncd) < 0) {
			if (errno != ENEEDAUTH) {
				syslog(LOG_ERR, "nfssvc err %m");
				continue;
			}
E 5
D 10
syslog(LOG_ERR, "in eacces");
E 10
D 5
				nfssvc_flag = NFSSVC_MNTD | NFSSVC_GOTAUTH |
					NFSSVC_AUTHINFAIL;
E 5
I 5
			nfssvc_flag =
			    NFSSVC_MNTD | NFSSVC_GOTAUTH | NFSSVC_AUTHINFAIL;
E 5
D 17
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
D 5
syslog(LOG_ERR,"Callin krb uid=%d inst=%s realm=%s",ncd.ncd_authuid,inst,realm);
				/*
				 * Set up as ncd_authuid for the kerberos call.
				 * Must set ruid to ncd_authuid and reset the
				 * ticket name iff ncd_authuid is not the same
				 * as last time, so that the right ticket file
				 * is found.
				 */
				if (ncd.ncd_authuid != last_ruid) {
					krb_set_tkt_string("");
					last_ruid = ncd.ncd_authuid;
				}
				setreuid(ncd.ncd_authuid, 0);
				if (krb_mk_req(&kt, "rcmd", inst, realm, 0) ==
				    KSUCCESS &&
				    kt.length <= (RPCAUTH_MAXSIZ - 2*NFSX_UNSIGNED)) {
syslog(LOG_ERR,"Got it\n");
				    ncd.ncd_authtype = RPCAUTH_NQNFS;
				    ncd.ncd_authlen = kt.length;
				    ncd.ncd_authstr = (char *)kt.dat;
				    nfssvc_flag = NFSSVC_MNTD | NFSSVC_GOTAUTH;
				}
				setreuid(0, 0);
syslog(LOG_ERR,"ktlen=%d\n", kt.length);
#endif /* KERBEROS */
			    } else
				syslog(LOG_ERR, "nfssvc err %m");
E 5
I 5
D 10
syslog(LOG_ERR,
    "Calling krb uid=%d inst=%s realm=%s", ncd.ncd_authuid, inst,realm);
E 10
			/*
			 * Set up as ncd_authuid for the kerberos call.
			 * Must set ruid to ncd_authuid and reset the
			 * ticket name iff ncd_authuid is not the same
			 * as last time, so that the right ticket file
			 * is found.
I 17
			 * Get the Kerberos credential structure so that
			 * we have the seesion key and get a ticket for
			 * this uid.
			 * For more info see the IETF Draft "Authentication
			 * in ONC RPC".
E 17
			 */
			if (ncd.ncd_authuid != last_ruid) {
				krb_set_tkt_string("");
				last_ruid = ncd.ncd_authuid;
E 5
			}
I 5
			setreuid(ncd.ncd_authuid, 0);
D 17
			if (krb_mk_req(&kt, "rcmd", inst, realm, 0) ==
			    KSUCCESS &&
			    kt.length <= (RPCAUTH_MAXSIZ - 2 * NFSX_UNSIGNED)) {
D 10
syslog(LOG_ERR, "Got it\n");
E 10
				ncd.ncd_authtype = RPCAUTH_NQNFS;
				ncd.ncd_authlen = kt.length;
				ncd.ncd_authstr = (char *)kt.dat;
				nfssvc_flag = NFSSVC_MNTD | NFSSVC_GOTAUTH;
E 17
I 17
			kret = krb_get_cred(NFS_KERBSRV, inst, realm, &kcr);
			if (kret == RET_NOTKT) {
		            kret = get_ad_tkt(NFS_KERBSRV, inst, realm,
				DEFAULT_TKT_LIFE);
			    if (kret == KSUCCESS)
				kret = krb_get_cred(NFS_KERBSRV, inst, realm,
				    &kcr);
E 17
			}
I 17
			if (kret == KSUCCESS)
			    kret = krb_mk_req(&ktick.kt, NFS_KERBSRV, inst,
				realm, 0);

			/*
			 * Fill in the AKN_FULLNAME authenticator and verfier.
			 * Along with the Kerberos ticket, we need to build
			 * the timestamp verifier and encrypt it in CBC mode.
			 */
			if (kret == KSUCCESS &&
			    ktick.kt.length <= (RPCAUTH_MAXSIZ-3*NFSX_UNSIGNED)
			    && gettimeofday(&ktv, (struct timezone *)0) == 0) {
			    ncd.ncd_authtype = RPCAUTH_KERB4;
			    ncd.ncd_authstr = (u_char *)&ktick;
			    ncd.ncd_authlen = nfsm_rndup(ktick.kt.length) +
				3 * NFSX_UNSIGNED;
			    ncd.ncd_verfstr = (u_char *)&kverf;
			    ncd.ncd_verflen = sizeof (kverf);
D 20
			    bcopy((caddr_t)kcr.session, (caddr_t)ncd.ncd_key,
E 20
I 20
			    memmove(ncd.ncd_key, kcr.session,
E 20
				sizeof (kcr.session));
			    kin.t1 = htonl(ktv.tv_sec);
			    kin.t2 = htonl(ktv.tv_usec);
			    kin.w1 = htonl(NFS_KERBTTL);
			    kin.w2 = htonl(NFS_KERBTTL - 1);
			    bzero((caddr_t)kivec, sizeof (kivec));

			    /*
			     * Encrypt kin in CBC mode using the session
			     * key in kcr.
			     */
			    XXX

			    /*
			     * Finally, fill the timestamp verifier into the
			     * authenticator and verifier.
			     */
			    ktick.kind = htonl(RPCAKN_FULLNAME);
			    kverf.kind = htonl(RPCAKN_FULLNAME);
			    NFS_KERBW1(ktick.kt) = kout.w1;
			    ktick.kt.length = htonl(ktick.kt.length);
			    kverf.verf.t1 = kout.t1;
			    kverf.verf.t2 = kout.t2;
			    kverf.verf.w2 = kout.w2;
			    nfssvc_flag = NFSSVC_MNTD | NFSSVC_GOTAUTH;
			}
E 17
			setreuid(0, 0);
D 10
syslog(LOG_ERR, "ktlen=%d\n", kt.length);
E 10
D 17
#endif /* KERBEROS */
E 17
I 17
#endif /* NFSKERB */
E 17
E 5
		}
D 4
		exit();
E 4
I 4
D 5
		exit(0);
E 4
	} else
		exit(1);
E 5
I 5
	}
	exit(0);
E 5
}

I 5
int
E 5
getnfsargs(spec, nfsargsp)
	char *spec;
	struct nfs_args *nfsargsp;
{
	register CLIENT *clp;
	struct hostent *hp;
	static struct sockaddr_in saddr;
#ifdef ISO
	static struct sockaddr_iso isoaddr;
	struct iso_addr *isop;
I 5
	int isoflag = 0;
E 5
#endif
	struct timeval pertry, try;
	enum clnt_stat clnt_stat;
D 5
	int so = RPC_ANYSOCK, isoflag = 0, i;
	char *hostp, *delimp, *cp;
E 5
I 5
D 17
	int so = RPC_ANYSOCK, i;
E 17
I 17
	int so = RPC_ANYSOCK, i, nfsvers, mntvers;
E 17
	char *hostp, *delimp;
D 17
#ifdef KERBEROS
E 17
I 17
#ifdef NFSKERB
E 17
	char *cp;
#endif
E 5
	u_short tport;
	static struct nfhret nfhret;
	static char nam[MNAMELEN + 1];

	strncpy(nam, spec, MNAMELEN);
	nam[MNAMELEN] = '\0';
D 12
	if ((delimp = index(spec, '@')) != NULL) {
E 12
I 12
	if ((delimp = strchr(spec, '@')) != NULL) {
E 12
		hostp = delimp + 1;
D 12
	} else if ((delimp = index(spec, ':')) != NULL) {
E 12
I 12
	} else if ((delimp = strchr(spec, ':')) != NULL) {
E 12
		hostp = spec;
		spec = delimp + 1;
	} else {
D 5
		fprintf(stderr,
		    "No <host>:<dirpath> or <dirpath>@<host> spec\n");
E 5
I 5
D 12
		warn("no <host>:<dirpath> or <dirpath>@<host> spec");
E 12
I 12
		warnx("no <host>:<dirpath> or <dirpath>@<host> spec");
E 12
E 5
		return (0);
	}
	*delimp = '\0';
	/*
	 * DUMB!! Until the mount protocol works on iso transport, we must
	 * supply both an iso and an inet address for the host.
	 */
#ifdef ISO
	if (!strncmp(hostp, "iso=", 4)) {
		u_short isoport;

		hostp += 4;
		isoflag++;
D 12
		if ((delimp = index(hostp, '+')) == NULL) {
D 5
			fprintf(stderr, "No iso+inet address\n");
E 5
I 5
			warn("no iso+inet address");
E 12
I 12
		if ((delimp = strchr(hostp, '+')) == NULL) {
			warnx("no iso+inet address");
E 12
E 5
			return (0);
		}
		*delimp = '\0';
		if ((isop = iso_addr(hostp)) == NULL) {
D 5
			fprintf(stderr, "Bad iso address\n");
E 5
I 5
D 12
			warn("bad ISO address");
E 12
I 12
			warnx("bad ISO address");
E 12
E 5
			return (0);
		}
D 20
		bzero((caddr_t)&isoaddr, sizeof (isoaddr));
		bcopy((caddr_t)isop, (caddr_t)&isoaddr.siso_addr,
			sizeof (struct iso_addr));
E 20
I 20
		memset(&isoaddr, 0, sizeof (isoaddr));
		memmove(&isoaddr.siso_addr, isop, sizeof (struct iso_addr));
E 20
		isoaddr.siso_len = sizeof (isoaddr);
		isoaddr.siso_family = AF_ISO;
		isoaddr.siso_tlen = 2;
		isoport = htons(NFS_PORT);
D 20
		bcopy((caddr_t)&isoport, TSEL(&isoaddr), isoaddr.siso_tlen);
E 20
I 20
		memmove(TSEL(&isoaddr), &isoport, isoaddr.siso_tlen);
E 20
		hostp = delimp + 1;
	}
#endif /* ISO */

	/*
	 * Handle an internet host address and reverse resolve it if
	 * doing Kerberos.
	 */
	if (isdigit(*hostp)) {
		if ((saddr.sin_addr.s_addr = inet_addr(hostp)) == -1) {
D 5
			fprintf(stderr, "Bad net addr %s\n", hostp);
E 5
I 5
D 12
			warn("bad net address %s\n", hostp);
E 12
I 12
			warnx("bad net address %s", hostp);
E 12
E 5
			return (0);
		}
D 17
		if ((nfsargsp->flags & NFSMNT_KERB) &&
		    (hp = gethostbyaddr((char *)&saddr.sin_addr.s_addr,
E 17
I 17
D 20
	} else if ((hp = gethostbyname(hostp)) != NULL) {
		bcopy(hp->h_addr, (caddr_t)&saddr.sin_addr, hp->h_length);
	} else {
E 20
I 20
	} else if ((hp = gethostbyname(hostp)) != NULL)
		memmove(&saddr.sin_addr, hp->h_addr, hp->h_length);
	else {
E 20
		warnx("can't get net id for host");
		return (0);
        }
#ifdef NFSKERB
	if ((nfsargsp->flags & NFSMNT_KERB)) {
		if ((hp = gethostbyaddr((char *)&saddr.sin_addr.s_addr,
E 17
D 5
			sizeof (u_long), AF_INET)) == (struct hostent *)0) {
			fprintf(stderr, "Can't reverse resolve net addr\n");
E 5
I 5
		    sizeof (u_long), AF_INET)) == (struct hostent *)0) {
D 12
			warn("can't reverse resolve net address");
E 12
I 12
			warnx("can't reverse resolve net address");
E 12
E 5
			return (0);
		}
D 17
	} else if ((hp = gethostbyname(hostp)) == NULL) {
D 5
		fprintf(stderr, "Can't get net id for host\n");
E 5
I 5
D 12
		warn("can't get net id for host");
E 12
I 12
		warnx("can't get net id for host");
E 12
E 5
		return (0);
	}
#ifdef KERBEROS
	if (nfsargsp->flags & NFSMNT_KERB) {
E 17
I 17
D 20
		bcopy(hp->h_addr, (caddr_t)&saddr.sin_addr, hp->h_length);
E 20
I 20
		memmove(&saddr.sin_addr, hp->h_addr, hp->h_length);
E 20
E 17
		strncpy(inst, hp->h_name, INST_SZ);
		inst[INST_SZ - 1] = '\0';
D 12
		if (cp = index(inst, '.'))
E 12
I 12
		if (cp = strchr(inst, '.'))
E 12
			*cp = '\0';
	}
D 17
#endif /* KERBEROS */
E 17
I 17
#endif /* NFSKERB */
E 17

D 17
	bcopy(hp->h_addr, (caddr_t)&saddr.sin_addr, hp->h_length);
E 17
I 17
	if (nfsargsp->flags & NFSMNT_NFSV3) {
		nfsvers = 3;
		mntvers = 3;
	} else {
		nfsvers = 2;
		mntvers = 1;
	}
E 17
	nfhret.stat = EACCES;	/* Mark not yet successful */
	while (retrycnt > 0) {
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(PMAPPORT);
		if ((tport = pmap_getport(&saddr, RPCPROG_NFS,
D 15
		    NFS_VER2, IPPROTO_UDP)) == 0) {
E 15
I 15
D 17
		    NFS_VER2, nfsargsp->sotype == SOCK_STREAM ? IPPROTO_TCP :
		    IPPROTO_UDP)) == 0) {
E 17
I 17
		    nfsvers, nfsproto)) == 0) {
E 17
E 15
			if ((opflags & ISBGRND) == 0)
				clnt_pcreateerror("NFS Portmap");
		} else {
			saddr.sin_port = 0;
			pertry.tv_sec = 10;
			pertry.tv_usec = 0;
D 15
			if ((clp = clntudp_create(&saddr, RPCPROG_MNT,
			    RPCMNT_VER1, pertry, &so)) == NULL) {
E 15
I 15
D 17
			if ((clp = (nfsargsp->sotype == SOCK_STREAM ?
			    clnttcp_create(&saddr, RPCPROG_MNT, RPCMNT_VER1,
					   &so, 0, 0) :
			    clntudp_create(&saddr, RPCPROG_MNT, RPCMNT_VER1,
					   pertry, &so))) == NULL) {
E 17
I 17
			if (mnttcp_ok && nfsargsp->sotype == SOCK_STREAM)
			    clp = clnttcp_create(&saddr, RPCPROG_MNT, mntvers,
				&so, 0, 0);
			else
			    clp = clntudp_create(&saddr, RPCPROG_MNT, mntvers,
				pertry, &so);
			if (clp == NULL) {
E 17
E 15
				if ((opflags & ISBGRND) == 0)
					clnt_pcreateerror("Cannot MNT PRC");
			} else {
				clp->cl_auth = authunix_create_default();
				try.tv_sec = 10;
				try.tv_usec = 0;
I 17
				if (nfsargsp->flags & NFSMNT_KERB)
				    nfhret.auth = RPCAUTH_KERB4;
				else
				    nfhret.auth = RPCAUTH_UNIX;
				nfhret.vers = mntvers;
E 17
				clnt_stat = clnt_call(clp, RPCMNT_MOUNT,
				    xdr_dir, spec, xdr_fh, &nfhret, try);
				if (clnt_stat != RPC_SUCCESS) {
D 5
					if ((opflags & ISBGRND) == 0)
						clnt_perror(clp, "Bad MNT RPC");
E 5
I 5
D 12
					if ((opflags & ISBGRND) == 0) {
						warn("%s", clnt_sperror(clp,
E 12
I 12
					if ((opflags & ISBGRND) == 0)
						warnx("%s", clnt_sperror(clp,
E 12
						    "bad MNT RPC"));
D 12
					}
E 12
E 5
				} else {
					auth_destroy(clp->cl_auth);
					clnt_destroy(clp);
					retrycnt = 0;
				}
			}
		}
		if (--retrycnt > 0) {
			if (opflags & BGRND) {
				opflags &= ~BGRND;
				if (i = fork()) {
D 5
					if (i == -1) {
						perror("nqnfs");
						exit(1);
					}
E 5
I 5
					if (i == -1)
D 7
						err("nqnfs 2: %s\n",
E 7
I 7
D 12
						err("nqnfs 2: %s",
E 7
						    strerror(errno));
E 12
I 12
						err(1, "nqnfs 2");
E 12
E 5
D 4
					exit();
E 4
I 4
					exit(0);
E 4
				}
				(void) setsid();
D 5
				(void) close(0);
				(void) close(1);
				(void) close(2);
E 5
I 5
				(void) close(STDIN_FILENO);
				(void) close(STDOUT_FILENO);
				(void) close(STDERR_FILENO);
E 5
				(void) chdir("/");
				opflags |= ISBGRND;
D 5
			} 
E 5
I 5
			}
E 5
			sleep(60);
		}
	}
	if (nfhret.stat) {
		if (opflags & ISBGRND)
			exit(1);
I 14
D 19
		errno = nfhret.stat;
E 14
D 5
		fprintf(stderr, "Can't access %s: ", spec);
		errno = nfhret.stat;
		perror(NULL);
E 5
I 5
D 12
		warn("can't access %s: %s\n", spec, strerror(nfhret.stat));
E 12
I 12
		warn("can't access %s", spec);
E 19
I 19
		warnx("can't access %s: %s", spec, strerror(nfhret.stat));
E 19
E 12
E 5
		return (0);
	}
	saddr.sin_port = htons(tport);
#ifdef ISO
	if (isoflag) {
		nfsargsp->addr = (struct sockaddr *) &isoaddr;
		nfsargsp->addrlen = sizeof (isoaddr);
	} else
#endif /* ISO */
	{
		nfsargsp->addr = (struct sockaddr *) &saddr;
		nfsargsp->addrlen = sizeof (saddr);
	}
D 17
	nfsargsp->fh = &nfhret.nfh;
E 17
I 17
	nfsargsp->fh = nfhret.nfh;
	nfsargsp->fhsize = nfhret.fhsize;
E 17
	nfsargsp->hostname = nam;
	return (1);
}

/*
 * xdr routines for mount rpc's
 */
I 5
int
E 5
xdr_dir(xdrsp, dirp)
	XDR *xdrsp;
	char *dirp;
{
	return (xdr_string(xdrsp, &dirp, RPCMNT_PATHLEN));
}

I 5
int
E 5
xdr_fh(xdrsp, np)
	XDR *xdrsp;
D 17
	struct nfhret *np;
E 17
I 17
	register struct nfhret *np;
E 17
{
D 17
	if (!xdr_u_long(xdrsp, &(np->stat)))
E 17
I 17
	register int i;
	long auth, authcnt, authfnd = 0;

	if (!xdr_u_long(xdrsp, &np->stat))
E 17
		return (0);
	if (np->stat)
		return (1);
D 17
	return (xdr_opaque(xdrsp, (caddr_t)&(np->nfh), NFSX_FH));
E 17
I 17
	switch (np->vers) {
	case 1:
		np->fhsize = NFSX_V2FH;
		return (xdr_opaque(xdrsp, (caddr_t)np->nfh, NFSX_V2FH));
	case 3:
		if (!xdr_long(xdrsp, &np->fhsize))
			return (0);
		if (np->fhsize <= 0 || np->fhsize > NFSX_V3FHMAX)
			return (0);
		if (!xdr_opaque(xdrsp, (caddr_t)np->nfh, np->fhsize))
			return (0);
		if (!xdr_long(xdrsp, &authcnt))
			return (0);
		for (i = 0; i < authcnt; i++) {
			if (!xdr_long(xdrsp, &auth))
				return (0);
			if (auth == np->auth)
				authfnd++;
		}
D 19
		if (!authfnd)
E 19
I 19
		/*
		 * Some servers, such as DEC's OSF/1 return a nil authenticator
		 * list to indicate RPCAUTH_UNIX.
		 */
		if (!authfnd && (authcnt > 0 || np->auth != RPCAUTH_UNIX))
E 19
			np->stat = EAUTH;
		return (1);
	};
	return (0);
E 17
}

D 5
Usage(argc, argv)
	int argc;
	char *argv[];
E 5
I 5
__dead void
usage()
E 5
{
D 5
	register int i;
E 5
I 5
	(void)fprintf(stderr, "usage: mount_nfs %s\n%s\n%s\n%s\n",
"[-bcdiKklMPqsT] [-a maxreadahead] [-D deadthresh]",
D 12
"\t[-g maxgroups] [-L leaseterm] [-m realm] [-R retrycnt]",
E 12
I 12
"\t[-g maxgroups] [-L leaseterm] [-m realm] [-o options] [-R retrycnt]",
E 12
"\t[-r readsize] [-t timeout] [-w writesize] [-x retrans]",
"\trhost:path node");
	exit(1);
D 12
}
E 5

D 5
	for (i = 0; i < argc; i++)
		fprintf(stderr, "%s ", argv[i]);
	fprintf(stderr, "\nBad mount_nfs arg\n");
E 5
I 5
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "mount_nfs: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 5
	exit(1);
I 5
	/* NOTREACHED */
}

void
#if __STDC__
warn(const char *fmt, ...)
#else
warn(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "mount_nfs: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 12
E 5
}
E 1
