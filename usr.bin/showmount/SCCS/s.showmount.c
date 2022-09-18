h16812
s 00008/00004/00329
d D 8.3 95/03/29 22:56:16 mckusick 10 8
c update for version 3 from Rick Macklem
e
s 00026/00030/00303
d R 8.3 95/03/29 22:50:40 mckusick 9 8
c update for version 3 from Rick Macklem
e
s 00029/00021/00304
d D 8.2 95/01/28 09:58:28 pendry 8 6
c fix error messages.
c lint, knf.
e
s 00002/00002/00323
d R 8.2 95/01/28 09:48:34 pendry 7 6
c fix error message
e
s 00005/00005/00320
d D 8.1 93/06/06 16:19:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00324
d D 6.5 91/03/01 18:35:48 bostic 5 4
c ANSI
e
s 00001/00011/00325
d D 6.4 90/06/01 17:42:02 bostic 4 3
c new copyright notice
e
s 00002/00002/00334
d D 6.3 90/05/15 19:58:12 bostic 3 2
c string.h is ANSI C include file
e
s 00002/00000/00334
d D 6.2 90/03/05 17:55:58 mckusick 2 1
c print_dump needs to check for an empty table (from macklem)
e
s 00334/00000/00000
d D 6.1 89/11/30 23:56:01 mckusick 1 0
c contributed by Rick Macklem
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1989, 1993
E 8
I 8
 * Copyright (c) 1989, 1993, 1995
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1989 Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
D 8
"%Z% Copyright (c) 1989, 1993\n\
E 8
I 8
"%Z% Copyright (c) 1989, 1993, 1995\n\
E 8
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

D 3
#include <stdio.h>
#include <strings.h>
E 3
#include <sys/types.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
I 8

E 8
#include <netdb.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
#include <nfs/rpcv2.h>
I 8

E 8
I 3
#include <stdio.h>
I 8
#include <stdlib.h>
E 8
#include <string.h>
I 8
#include <unistd.h>
E 8
E 3

/* Constant defs */
#define	ALL	1
#define	DIRS	2

#define	DODUMP		0x1
#define	DOEXPORTS	0x2

struct mountlist {
	struct mountlist *ml_left;
	struct mountlist *ml_right;
	char	ml_host[RPCMNT_NAMELEN+1];
	char	ml_dirp[RPCMNT_PATHLEN+1];
};

struct grouplist {
	struct grouplist *gr_next;
	char	gr_name[RPCMNT_NAMELEN+1];
};

struct exportslist {
	struct exportslist *ex_next;
	struct grouplist *ex_groups;
	char	ex_dirp[RPCMNT_PATHLEN+1];
};

static struct mountlist *mntdump;
static struct exportslist *exports;
static int type = 0;
D 8
int xdr_mntdump(), xdr_exports();
E 8

I 8
void	print_dump __P((struct mountlist *));
void	usage __P((void));
int	xdr_mntdump __P((XDR *, struct mountlist **));
int	xdr_exports __P((XDR *, struct exportslist **));

E 8
/*
 * This command queries the NFS mount daemon for it's mount list and/or
 * it's exports list and prints them out.
 * See "NFS: Network File System Protocol Specification, RFC1094, Appendix A"
I 10
 * and the "Network File System Protocol XXX.."
E 10
 * for detailed information on the protocol.
 */
I 8
int
E 8
main(argc, argv)
	int argc;
	char **argv;
{
D 8
	register struct mountlist *mntp;
	register struct exportslist *exp;
	register struct grouplist *grp;
	extern char *optarg;
	extern int optind;
	register int rpcs = 0;
	char ch;
	char *host;
	int estat;
E 8
I 8
	struct exportslist *exp;
	struct grouplist *grp;
D 10
	int estat, rpcs = 0;
E 10
I 10
	int estat, rpcs = 0, mntvers = 1;
E 10
	char ch, *host;
E 8

D 10
	while ((ch = getopt(argc, argv, "ade")) != EOF)
E 10
I 10
	while ((ch = getopt(argc, argv, "ade3")) != EOF)
E 10
		switch((char)ch) {
		case 'a':
			if (type == 0) {
				type = ALL;
				rpcs |= DODUMP;
			} else
				usage();
			break;
		case 'd':
			if (type == 0) {
				type = DIRS;
				rpcs |= DODUMP;
			} else
				usage();
			break;
		case 'e':
			rpcs |= DOEXPORTS;
			break;
I 10
		case '3':
			mntvers = 3;
			break;
E 10
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc > 0)
		host = *argv;
	else
		host = "localhost";

	if (rpcs == 0)
		rpcs = DODUMP;

	if (rpcs & DODUMP)
D 10
		if ((estat = callrpc(host, RPCPROG_MNT, RPCMNT_VER1,
E 10
I 10
		if ((estat = callrpc(host, RPCPROG_MNT, mntvers,
E 10
			RPCMNT_DUMP, xdr_void, (char *)0,
			xdr_mntdump, (char *)&mntdump)) != 0) {
			clnt_perrno(estat);
D 8
			fprintf(stderr, "Can't do Mountdump rpc\n");
E 8
I 8
			fprintf(stderr, ": Can't do Mountdump rpc\n");
E 8
			exit(1);
		}
	if (rpcs & DOEXPORTS)
D 10
		if ((estat = callrpc(host, RPCPROG_MNT, RPCMNT_VER1,
E 10
I 10
		if ((estat = callrpc(host, RPCPROG_MNT, mntvers,
E 10
			RPCMNT_EXPORT, xdr_void, (char *)0,
			xdr_exports, (char *)&exports)) != 0) {
			clnt_perrno(estat);
D 8
			fprintf(stderr, "Can't do Exports rpc\n");
E 8
I 8
			fprintf(stderr, ": Can't do Exports rpc\n");
E 8
			exit(1);
		}

	/* Now just print out the results */
	if (rpcs & DODUMP) {
		switch (type) {
		case ALL:
			printf("All mount points on %s:\n", host);
			break;
		case DIRS:
			printf("Directories on %s:\n", host);
			break;
		default:
			printf("Hosts on %s:\n", host);
			break;
		};
		print_dump(mntdump);
	}
	if (rpcs & DOEXPORTS) {
		printf("Exports list on %s:\n", host);
		exp = exports;
		while (exp) {
			printf("%-35s", exp->ex_dirp);
			grp = exp->ex_groups;
			if (grp == NULL) {
				printf("Everyone\n");
			} else {
				while (grp) {
					printf("%s ", grp->gr_name);
					grp = grp->gr_next;
				}
				printf("\n");
			}
			exp = exp->ex_next;
		}
	}
I 8

	exit(0);
E 8
}

/*
 * Xdr routine for retrieving the mount dump list
 */
I 8
int
E 8
xdr_mntdump(xdrsp, mlp)
	XDR *xdrsp;
	struct mountlist **mlp;
{
D 8
	register struct mountlist *mp;
	register struct mountlist *tp;
	register struct mountlist **otp;
	int val, val2;
	int bool;
E 8
I 8
	struct mountlist *mp, **otp, *tp;
	int bool, val, val2;
E 8
	char *strp;

	*mlp = (struct mountlist *)0;
	if (!xdr_bool(xdrsp, &bool))
		return (0);
	while (bool) {
		mp = (struct mountlist *)malloc(sizeof(struct mountlist));
		if (mp == NULL)
			return (0);
		mp->ml_left = mp->ml_right = (struct mountlist *)0;
		strp = mp->ml_host;
		if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
			return (0);
		strp = mp->ml_dirp;
		if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
			return (0);

		/*
		 * Build a binary tree on sorted order of either host or dirp.
		 * Drop any duplications.
		 */
		if (*mlp == NULL) {
			*mlp = mp;
		} else {
			tp = *mlp;
			while (tp) {
				val = strcmp(mp->ml_host, tp->ml_host);
				val2 = strcmp(mp->ml_dirp, tp->ml_dirp);
				switch (type) {
				case ALL:
					if (val == 0) {
						if (val2 == 0) {
							free((caddr_t)mp);
							goto next;
						}
						val = val2;
					}
					break;
				case DIRS:
					if (val2 == 0) {
						free((caddr_t)mp);
						goto next;
					}
					val = val2;
					break;
				default:
					if (val == 0) {
						free((caddr_t)mp);
						goto next;
					}
					break;
				};
				if (val < 0) {
					otp = &tp->ml_left;
					tp = tp->ml_left;
				} else {
					otp = &tp->ml_right;
					tp = tp->ml_right;
				}
			}
			*otp = mp;
		}
next:
		if (!xdr_bool(xdrsp, &bool))
			return (0);
	}
	return (1);
}

/*
 * Xdr routine to retrieve exports list
 */
I 8
int
E 8
xdr_exports(xdrsp, exp)
	XDR *xdrsp;
	struct exportslist **exp;
{
D 8
	register struct exportslist *ep;
	register struct grouplist *gp;
E 8
I 8
	struct exportslist *ep;
	struct grouplist *gp;
E 8
	int bool, grpbool;
	char *strp;

	*exp = (struct exportslist *)0;
	if (!xdr_bool(xdrsp, &bool))
		return (0);
	while (bool) {
		ep = (struct exportslist *)malloc(sizeof(struct exportslist));
		if (ep == NULL)
			return (0);
		ep->ex_groups = (struct grouplist *)0;
		strp = ep->ex_dirp;
		if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
			return (0);
		if (!xdr_bool(xdrsp, &grpbool))
			return (0);
		while (grpbool) {
			gp = (struct grouplist *)malloc(sizeof(struct grouplist));
			if (gp == NULL)
				return (0);
			strp = gp->gr_name;
			if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
				return (0);
			gp->gr_next = ep->ex_groups;
			ep->ex_groups = gp;
			if (!xdr_bool(xdrsp, &grpbool))
				return (0);
		}
		ep->ex_next = *exp;
		*exp = ep;
		if (!xdr_bool(xdrsp, &bool))
			return (0);
	}
	return (1);
}

I 8
void
E 8
D 5
static
E 5
usage()
{
I 8

E 8
D 5
	fprintf(stderr, "Usage: showmount [-ade] host\n");
E 5
I 5
	fprintf(stderr, "usage: showmount [-ade] host\n");
E 5
	exit(1);
}

/*
 * Print the binary tree in inorder so that output is sorted.
 */
I 8
void
E 8
print_dump(mp)
	struct mountlist *mp;
{

I 2
	if (mp == NULL)
		return;
E 2
	if (mp->ml_left)
		print_dump(mp->ml_left);
	switch (type) {
	case ALL:
		printf("%s:%s\n", mp->ml_host, mp->ml_dirp);
		break;
	case DIRS:
		printf("%s\n", mp->ml_dirp);
		break;
	default:
		printf("%s\n", mp->ml_host);
		break;
	};
	if (mp->ml_right)
		print_dump(mp->ml_right);
}
E 1
