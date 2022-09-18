h05873
s 00002/00001/02036
d D 8.15 95/05/01 22:51:34 mckusick 41 40
c more descriptive error message (from David Greenman)
e
s 00023/00037/02014
d D 8.14 95/04/28 10:44:59 bostic 40 39
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00015/00009/02036
d D 8.13 95/03/30 15:15:27 mckusick 39 38
c further updates from Rick Macklem for version 3
e
s 00133/00055/01912
d D 8.12 95/03/29 21:54:05 mckusick 38 37
c update for version 3 NFS from Rick Macklem
e
s 00003/00002/01964
d D 8.11 94/12/27 12:43:12 hibler 37 36
c close netgroup file on a bad netgroup
c have get_host say what host it fails on
e
s 00009/00020/01957
d D 8.10 94/08/17 21:57:25 mckusick 36 35
c -n option allows access from non-priviledged ports (from cgd)
e
s 00003/00005/01974
d D 8.9 94/06/14 16:50:47 mkm 35 34
c fix to allow mounting of swap files (from mycroft)
e
s 00184/00132/01795
d D 8.8 94/02/20 13:20:12 pendry 34 33
c lint, KNF
e
s 00001/00085/01926
d D 8.7 94/02/20 12:21:22 pendry 33 32
c remove local version of realpath - now in libc
e
s 00031/00003/01980
d D 8.6 94/01/28 17:18:01 bostic 32 31
c The change ensures that symbolic links are not used in export paths,
c since the match can never succeed after realpath() converts incoming
c paths to the "real" one.
c From Rick Macklem root@snowhite.cis.uoguelph.ca (Charlie Root)
e
s 00000/00001/01983
d D 8.5 94/01/25 15:02:19 hibler 31 30
c CD9660 is now defined in Makefile (ala NFS and MFS)
e
s 00019/00016/01965
d D 8.4 94/01/24 06:46:57 bostic 30 29
c Mirror Kirk's 8.9 change to /sys/sys/mount.h; ISOFS => CD9660
c cleanup the include files
e
s 00036/00021/01945
d D 8.3 94/01/12 22:03:17 hibler 29 28
c reflect changes to mount.h and ability to export other than UFS
e
s 00018/00010/01948
d D 8.2 93/11/16 15:10:34 mckusick 28 27
c allow for world export (from Macklem)
e
s 00005/00005/01953
d D 8.1 93/06/05 11:05:25 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01957
d D 5.25 93/04/09 16:19:21 mckusick 26 25
c recover from gethostbyname timeouts (from Macklem)
e
s 00002/00002/01956
d D 5.24 92/08/09 13:28:50 mckusick 25 24
c zero out unused part of structure so kernel will not complain
e
s 00005/00003/01953
d D 5.23 92/07/16 13:37:10 mckusick 24 23
c fix for -alldirs and netgroups
e
s 00001/00001/01955
d D 5.22 92/04/20 15:58:39 mckusick 23 22
c do not wait for mount info
e
s 00097/00041/01859
d D 5.21 92/04/09 19:19:58 mckusick 22 21
c update from Rick Macklem
e
s 00036/00049/01864
d D 5.20 92/01/06 10:51:48 mckusick 21 20
c minor updates from Rick Macklem
e
s 01067/00645/00846
d D 5.19 91/12/12 14:38:42 mckusick 20 19
c update for new syntax and semantics from Rick Macklem
e
s 00001/00001/01490
d D 5.18 91/11/14 21:57:45 mckusick 19 18
c -allanon becomes -all
e
s 00022/00024/01469
d D 5.17 91/11/14 21:56:24 mckusick 18 17
c fixes from Rick Macklem
e
s 00014/00000/01479
d D 5.16 91/11/14 21:44:46 mckusick 17 16
c add debugging for syslog messages
e
s 00889/00226/00589
d D 5.15 91/11/12 23:15:50 mckusick 16 15
c update from Rick Macklem, with further semantic refinements by me
e
s 00005/00003/00810
d D 5.14 91/02/26 15:38:35 bostic 15 14
c ANSI fixes
e
s 00071/00055/00742
d D 5.13 90/09/30 18:38:38 mckusick 14 13
c just ignore bad hostnames, do not exit!
e
s 00004/00001/00793
d D 5.12 90/08/31 11:45:23 mckusick 13 12
c do not lose flags when exporting
e
s 00002/00019/00792
d D 5.11 90/06/29 20:00:12 karels 12 11
c use daemon() call
e
s 00003/00002/00808
d D 5.10 90/06/27 17:40:00 mckusick 11 9
c openlog earlier; create mountdtab if it does not exist
e
s 00003/00002/00808
d R 5.10 90/06/27 17:26:48 mckusick 10 9
c openlog earlier; create mountdtab if it does not exist
e
s 00350/00164/00460
d D 5.9 90/06/25 14:17:29 mckusick 9 8
c update to allow mounting of subtrees (from Macklem)
e
s 00001/00011/00623
d D 5.8 90/06/01 16:18:26 bostic 8 7
c new copyright notice
e
s 00004/00004/00630
d D 5.7 90/05/15 19:52:16 bostic 7 6
c string.h is ANSI C include file
e
s 00003/00003/00631
d D 5.6 90/05/04 22:39:35 mckusick 6 5
c mount flags changed from M_ to MNT_
e
s 00006/00000/00628
d D 5.5 90/03/15 17:24:28 mckusick 5 4
c store pid in /var/run/mountd.pid for mount to notify of changes
e
s 00006/00002/00622
d D 5.4 90/03/08 15:20:45 mckusick 4 3
c exportfs is replaced by mount
e
s 00000/00006/00624
d D 5.3 90/03/08 10:45:00 mckusick 3 2
c get rid of unneeded header files
e
s 00176/00119/00454
d D 5.2 89/11/30 23:45:26 mckusick 2 1
c update from Rick Macklem
e
s 00573/00000/00000
d D 5.1 89/07/16 17:36:29 mckusick 1 0
c original code from Rick Macklem
e
u
U
t
T
I 1
/*
D 27
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * This code is derived from software contributed to Berkeley by
D 16
 * Rick Macklem at The University of Guelph.
E 16
I 16
 * Herb Hasler and Rick Macklem at The University of Guelph.
E 16
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
D 27
char copyright[] =
"%Z% Copyright (c) 1989 Regents of the University of California.\n\
 All rights reserved.\n";
E 27
I 27
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 27
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

I 16
D 30
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
E 30
D 21
#include <fcntl.h>
E 21
E 16
D 7
#include <stdio.h>
#include <strings.h>
#include <syslog.h>
#include <signal.h>
E 7
D 3
#include <fcntl.h>
E 3
#include <sys/param.h>
D 3
#include <sys/types.h>
E 3
D 30
#include <sys/ioctl.h>
#include <sys/stat.h>
E 30
I 2
#include <sys/file.h>
E 2
D 3
#include <sys/dir.h>
#include <sys/uio.h>
#include <sys/namei.h>
E 3
I 16
D 30
#include <sys/ucred.h>
E 30
I 30
#include <sys/ioctl.h>
D 31
#define CD9660
E 31
E 30
E 16
#include <sys/mount.h>
#include <sys/socket.h>
D 3
#include <sys/socketvar.h>
E 3
D 30
#include <sys/errno.h>
I 7
#include <sys/signal.h>
#include <stdio.h>
#include <string.h>
E 30
I 30
#include <sys/stat.h>
E 30
D 21
#include <syslog.h>
E 21
I 21
#include <sys/syslog.h>
E 21
E 7
D 30
#include <netdb.h>
E 30
I 30
#include <sys/ucred.h>

E 30
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
I 16
#ifdef ISO
#include <netiso/iso.h>
#endif
E 16
#include <nfs/rpcv2.h>
D 38
#include <nfs/nfsv2.h>
E 38
I 38
#include <nfs/nfsproto.h>
#include <ufs/ufs/ufsmount.h>
#include <sys/../isofs/cd9660/cd9660_mount.h>	/* XXX need isofs in include */
E 38
I 2
D 30
#include "pathnames.h"
E 30
I 30

I 34
#include <arpa/inet.h>

#include <ctype.h>
E 34
#include <errno.h>
#include <grp.h>
#include <netdb.h>
#include <pwd.h>
#include <signal.h>
E 30
I 22
D 34
#ifdef DEBUG
#include <stdarg.h>
#endif
E 34
I 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pathnames.h"
E 30
E 22
E 2

I 34
#ifdef DEBUG
#include <stdarg.h>
#endif

E 34
D 16
struct ufid {
	u_short	ufid_len;
	ino_t	ufid_ino;
	long	ufid_gen;
E 16
I 16
D 18
#define DEF_NAME "default"

E 18
D 20
#define MNT_HOST   0
#define MNT_GROUP  1
#define	MNT_ISO    2

struct namelist {
	char name[RPCMNT_NAMELEN+1];
	struct namelist *next;
E 16
};
I 16
struct namegrp {
	char gname[RPCMNT_NAMELEN+1];
	struct namegrp *next;
	struct namelist *names;
};
E 20
E 16
/*
 * Structures for keeping the mount list and export list
 */
struct mountlist {
I 9
	struct mountlist *ml_next;
E 9
D 2
	struct mountlist *ml_next;
	struct mountlist *ml_prev;
E 2
	char	ml_host[RPCMNT_NAMELEN+1];
	char	ml_dirp[RPCMNT_PATHLEN+1];
};

I 20
struct dirlist {
	struct dirlist	*dp_left;
	struct dirlist	*dp_right;
	int		dp_flag;
	struct hostlist	*dp_hosts;	/* List of hosts this dir exported to */
	char		dp_dirp[1];	/* Actually malloc'd to size of dir */
};
/* dp_flag bits */
#define	DP_DEFSET	0x1
I 38
#define DP_HOSTSET	0x2
#define DP_KERB		0x4
E 38

E 20
struct exportlist {
	struct exportlist *ex_next;
D 20
	struct exportlist *ex_prev;
	struct grouplist *ex_groups;
D 16
	int	ex_rootuid;
	int	ex_exflags;
I 9
	dev_t	ex_dev;
E 16
I 16
	int	ex_defset;
E 16
E 9
	char	ex_dirp[RPCMNT_PATHLEN+1];
E 20
I 20
	struct dirlist	*ex_dirl;
	struct dirlist	*ex_defdir;
	int		ex_flag;
	fsid_t		ex_fs;
	char		*ex_fsdir;
E 20
};
I 20
/* ex_flag bits */
D 21
#define	EX_DONEDEL	0x2
#define	EX_LINKED	0x4
E 21
I 21
#define	EX_LINKED	0x1
E 21
E 20

I 20
struct netmsk {
	u_long	nt_net;
	u_long	nt_mask;
	char *nt_name;
};

E 20
I 16
union grouptypes {
	struct hostent *gt_hostent;
D 20
	struct groupnames *gt_grpname;
E 20
I 20
	struct netmsk	gt_net;
E 20
#ifdef ISO
	struct sockaddr_iso *gt_isoaddr;
#endif
};

E 16
struct grouplist {
I 16
D 20
	int type;
	int exflags;
	struct ucred anoncr;
E 20
I 20
	int gr_type;
E 20
	union grouptypes gr_ptr;
E 16
	struct grouplist *gr_next;
D 2
	char	gr_name[RPCMNT_NAMELEN+1];
E 2
I 2
D 16
	struct hostent *gr_hp;
E 16
E 2
};
I 20
/* Group types */
#define	GT_NULL		0x0
#define	GT_HOST		0x1
#define	GT_NET		0x2
#define	GT_ISO		0x4
E 20

I 16
D 20
struct al_mnt {
	struct al_mnt *al_next;
	fsid_t	al_mnted;
E 20
I 20
struct hostlist {
I 38
	int		 ht_flag;	/* Uses DP_xx bits */
E 38
	struct grouplist *ht_grp;
	struct hostlist	 *ht_next;
E 20
};

I 38
struct fhreturn {
	int	fhr_flag;
	int	fhr_vers;
	nfsfh_t	fhr_fh;
};

E 38
D 20
struct groupnames {
	char gn_name[RPCMNT_NAMELEN+1];
	struct grouplist *gn_glist;
	struct groupnames *gn_next;
};

E 20
E 16
/* Global defs */
D 15
int xdr_fhs(), xdr_mlist(), xdr_dir(), xdr_explist();
D 9
int mntsrv(), get_exportlist();
E 9
I 9
int mntsrv(), get_exportlist(), send_umntall(), umntall_each();
void get_mountlist(), add_mlist(), del_mlist();
E 15
I 15
D 34
int mntsrv(), umntall_each(), xdr_fhs(), xdr_mlist(), xdr_dir(), xdr_explist();
I 32
int check_dirpath();
E 32
D 16
void add_mlist(), del_mlist(), get_exportlist(), get_mountlist();
void send_umntall();
E 16
I 16
D 20
void get_exportlist(), send_umntall(), nextfield(), do_opt();
E 20
I 20
void get_exportlist(), send_umntall(), nextfield(), out_of_mem();
E 20
void get_mountlist(), add_mlist(), del_mlist(), free_exp(), free_grp();
D 20
void get_group(), get_host(), do_group();
char *realpath();
E 20
I 20
void getexp_err(), hang_dirp(), add_dlist(), free_dir(), free_host();
I 22
void setnetgrent(), endnetgrent();
E 22
struct exportlist *ex_search(), *get_exp();
struct grouplist *get_grp();
D 33
char *realpath(), *add_expdir();
E 33
I 33
char *add_expdir();
E 33
struct in_addr inet_makeaddr();
char *inet_ntoa();
struct dirlist *dirp_search();
struct hostlist *get_ht();
E 34
I 34
char	*add_expdir __P((struct dirlist **, char *, int));
void	add_dlist __P((struct dirlist **, struct dirlist *,
D 38
				struct grouplist *));
E 38
I 38
				struct grouplist *, int));
E 38
void	add_mlist __P((char *, char *));
int	check_dirpath __P((char *));
int	check_options __P((struct dirlist *));
D 38
int	chk_host __P((struct dirlist *, u_long, int *));
E 38
I 38
int	chk_host __P((struct dirlist *, u_long, int *, int *));
E 38
void	del_mlist __P((char *, char *));
struct dirlist *dirp_search __P((struct dirlist *, char *));
int	do_mount __P((struct exportlist *, struct grouplist *, int,
D 38
				struct ucred *, char *, int, struct statfs *));
E 38
I 38
		struct ucred *, char *, int, struct statfs *));
E 38
int	do_opt __P((char **, char **, struct exportlist *, struct grouplist *,
				int *, int *, struct ucred *));
struct	exportlist *ex_search __P((fsid_t *));
struct	exportlist *get_exp __P((void));
void	free_dir __P((struct dirlist *));
void	free_exp __P((struct exportlist *));
void	free_grp __P((struct grouplist *));
void	free_host __P((struct hostlist *));
void	get_exportlist __P((void));
int	get_host __P((char *, struct grouplist *));
I 38
int	get_num __P((char *));
E 38
struct hostlist *get_ht __P((void));
int	get_line __P((void));
void	get_mountlist __P((void));
int	get_net __P((char *, struct netmsk *, int));
void	getexp_err __P((struct exportlist *, struct grouplist *));
struct grouplist *get_grp __P((void));
void	hang_dirp __P((struct dirlist *, struct grouplist *,
				struct exportlist *, int));
void	mntsrv __P((struct svc_req *, SVCXPRT *));
void	nextfield __P((char **, char **));
void	out_of_mem __P((void));
void	parsecred __P((char *, struct ucred *));
int	put_exlist __P((struct dirlist *, XDR *, struct dirlist *, int *));
int	scan_tree __P((struct dirlist *, u_long));
void	send_umntall __P((void));
int	umntall_each __P((caddr_t, struct sockaddr_in *));
int	xdr_dir __P((XDR *, char *));
int	xdr_explist __P((XDR *, caddr_t));
D 38
int	xdr_fhs __P((XDR *, nfsv2fh_t *));
E 38
I 38
int	xdr_fhs __P((XDR *, caddr_t));
E 38
int	xdr_mlist __P((XDR *, caddr_t));

/* C library */
int	getnetgrent();
void	endnetgrent();
void	setnetgrent();

E 34
E 20
#ifdef ISO
struct iso_addr *iso_addr();
#endif
I 34

E 34
E 16
E 15
E 9
D 20
struct exportlist exphead;
E 20
I 20
struct exportlist *exphead;
E 20
D 2
struct mountlist mlhead;
E 2
I 2
D 9
int mlfile;
E 9
I 9
struct mountlist *mlhead;
I 16
D 20
struct groupnames *grpnames;
E 20
I 20
struct grouplist *grphead;
E 20
E 16
E 9
E 2
char exname[MAXPATHLEN];
D 16
int def_rootuid = -2;
E 16
I 16
struct ucred def_anon = {
D 34
	(u_short) 1,
E 34
I 34
	1,
E 34
	(uid_t) -2,
	1,
D 34
	(gid_t) -2,
E 34
I 34
	{ (gid_t) -2 }
E 34
};
E 16
I 9
D 36
int root_only = 1;
E 36
I 36
int resvport_only = 1;
I 38
int dir_only = 1;
E 38
E 36
I 20
int opt_flags;
/* Bits for above */
#define	OP_MAPROOT	0x01
#define	OP_MAPALL	0x02
#define	OP_KERB		0x04
#define	OP_MASK		0x08
#define	OP_NET		0x10
#define	OP_ISO		0x20
#define	OP_ALLDIRS	0x40

E 20
E 9
D 34
extern int errno;
E 34
I 16
D 20
struct al_mnt *al_head = (struct al_mnt *)0;
E 20
E 16
#ifdef DEBUG
int debug = 1;
I 17
void	SYSLOG __P((int, const char *, ...));
#define syslog SYSLOG
E 17
#else
int debug = 0;
#endif

/*
 * Mountd server for NFS mount protocol as described in:
D 2
 *  Networking on the Sun Workstation,
 *  Part #800-1324-03 Rev. B
 *  Network File System Protocol Specification Chap. 3
E 2
I 2
 * NFS: Network File System Protocol Specification, RFC1094, Appendix A
E 2
D 9
 * The optional argument is the exports file name
E 9
I 9
 * The optional arguments are the exports file name
E 9
D 2
 * default: /etc/exports
E 2
I 2
 * default: _PATH_EXPORTS
I 9
 * and "-n" to allow nonroot mount.
E 9
E 2
 */
I 34
int
E 34
main(argc, argv)
	int argc;
D 9
	char *argv[];
E 9
I 9
	char **argv;
E 9
{
D 38
	SVCXPRT *transp;
E 38
I 38
	SVCXPRT *udptransp, *tcptransp;
E 38
I 9
	int c;
D 34
	extern int optind;
	extern char *optarg;
E 34
E 9

I 9
D 38
	while ((c = getopt(argc, argv, "n")) != EOF)
E 38
I 38
D 39
	while ((c = getopt(argc, argv, "ntr")) != EOF)
E 39
I 39
	while ((c = getopt(argc, argv, "nr")) != EOF)
E 39
E 38
		switch (c) {
		case 'n':
D 36
			root_only = 0;
E 36
I 36
			resvport_only = 0;
E 36
			break;
I 38
		case 'r':
			dir_only = 0;
			break;
E 38
		default:
D 38
			fprintf(stderr, "Usage: mountd [-n] [export_file]\n");
E 38
I 38
			fprintf(stderr, "Usage: mountd [-r] [-n] [export_file]\n");
E 38
			exit(1);
		};
	argc -= optind;
	argv += optind;
I 16
D 20
	grpnames = (struct groupnames *)0;
E 16
	exphead.ex_next = exphead.ex_prev = (struct exportlist *)0;
E 20
I 20
D 34
	grphead = (struct grouplist *)0;
	exphead = (struct exportlist *)0;
E 20
	mlhead = (struct mountlist *)0;
E 34
I 34
	grphead = (struct grouplist *)NULL;
	exphead = (struct exportlist *)NULL;
	mlhead = (struct mountlist *)NULL;
E 34
	if (argc == 1) {
		strncpy(exname, *argv, MAXPATHLEN-1);
		exname[MAXPATHLEN-1] = '\0';
	} else
		strcpy(exname, _PATH_EXPORTS);
I 11
D 34
	openlog("mountd:", LOG_PID, LOG_DAEMON);
E 34
I 34
	openlog("mountd", LOG_PID, LOG_DAEMON);
E 34
I 16
	if (debug)
		fprintf(stderr,"Getting export list.\n");
E 16
E 11
	get_exportlist();
I 16
	if (debug)
		fprintf(stderr,"Getting mount list.\n");
E 16
	get_mountlist();
I 16
	if (debug)
		fprintf(stderr,"Here we go.\n");
E 16
E 9
	if (debug == 0) {
D 12
		if (fork())
			exit(0);
		{ int s;
		for (s = 0; s < 10; s++)
			(void) close(s);
		}
		(void) open("/", O_RDONLY);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
		{ int tt = open("/dev/tty", O_RDWR);
		  if (tt > 0) {
			ioctl(tt, TIOCNOTTY, (char *)0);
			close(tt);
		  }
		}
		(void) setpgrp(0, 0);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
E 12
I 12
		daemon(0, 0);
E 12
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
D 9
		signal(SIGTERM, SIG_IGN);
E 9
	}
D 11
	openlog("mountd:", LOG_PID, LOG_DAEMON);
E 11
D 2
	mlhead.ml_next = mlhead.ml_prev = (struct mountlist *)0;
E 2
D 9
	exphead.ex_next = exphead.ex_prev = (struct exportlist *)0;
	if (argc == 2) {
		strncpy(exname, argv[1], MAXPATHLEN-1);
		exname[MAXPATHLEN-1] = '\0';
	} else
D 2
		strcpy(exname, "/etc/exports");
E 2
I 2
		strcpy(exname, _PATH_EXPORTS);
E 2
	get_exportlist();
E 9
D 34
	signal(SIGHUP, get_exportlist);
I 9
	signal(SIGTERM, send_umntall);
E 34
I 34
	signal(SIGHUP, (void (*) __P((int))) get_exportlist);
	signal(SIGTERM, (void (*) __P((int))) send_umntall);
E 34
E 9
I 5
	{ FILE *pidfile = fopen(_PATH_MOUNTDPID, "w");
	  if (pidfile != NULL) {
		fprintf(pidfile, "%d\n", getpid());
		fclose(pidfile);
	  }
	}
E 5
I 2
D 9
	if ((mlfile = open(_PATH_RMOUNTLIST, (O_RDWR|O_CREAT), 0600)) < 0) {
		syslog(LOG_ERR, "Can't open mountlist file");
		exit(1);
	}
E 9
E 2
D 38
	if ((transp = svcudp_create(RPC_ANYSOCK)) == NULL) {
E 38
I 38
	if ((udptransp = svcudp_create(RPC_ANYSOCK)) == NULL ||
	    (tcptransp = svctcp_create(RPC_ANYSOCK, 0, 0)) == NULL) {
E 38
		syslog(LOG_ERR, "Can't create socket");
		exit(1);
	}
D 38
	pmap_unset(RPCPROG_MNT, RPCMNT_VER1);
D 16
	if (!svc_register(transp, RPCPROG_MNT, RPCMNT_VER1, mntsrv, IPPROTO_UDP)) {
E 16
I 16
	if (!svc_register(transp, RPCPROG_MNT, RPCMNT_VER1, mntsrv,
	    IPPROTO_UDP)) {
E 38
I 38
	pmap_unset(RPCPROG_MNT, 1);
	pmap_unset(RPCPROG_MNT, 3);
	if (!svc_register(udptransp, RPCPROG_MNT, 1, mntsrv, IPPROTO_UDP) ||
	    !svc_register(udptransp, RPCPROG_MNT, 3, mntsrv, IPPROTO_UDP) ||
	    !svc_register(tcptransp, RPCPROG_MNT, 1, mntsrv, IPPROTO_TCP) ||
	    !svc_register(tcptransp, RPCPROG_MNT, 3, mntsrv, IPPROTO_TCP)) {
E 38
E 16
		syslog(LOG_ERR, "Can't register mount");
		exit(1);
	}
	svc_run();
	syslog(LOG_ERR, "Mountd died");
I 12
	exit(1);
E 12
}

/*
 * The mount rpc service
 */
I 34
void
E 34
mntsrv(rqstp, transp)
D 34
	register struct svc_req *rqstp;
	register SVCXPRT *transp;
E 34
I 34
	struct svc_req *rqstp;
	SVCXPRT *transp;
E 34
{
D 2
	register struct mountlist *mlp;
	register struct exportlist *ep;
E 2
D 20
	register struct grouplist *grp;
D 2
	struct mountlist *mlp2;
E 2
I 2
	register u_long **addrp;
E 20
D 34
	register struct exportlist *ep;
I 20
	register struct dirlist *dp;
E 34
I 34
	struct exportlist *ep;
	struct dirlist *dp;
E 34
E 20
D 9
	struct mountlist ml;
E 9
E 2
D 38
	nfsv2fh_t nfh;
E 38
I 38
	struct fhreturn fhr;
E 38
D 36
	struct authunix_parms *ucr;
E 36
	struct stat stb;
I 20
	struct statfs fsb;
E 20
	struct hostent *hp;
D 2
	struct sockaddr_in saddr;
E 2
I 2
	u_long saddr;
I 36
	u_short sport;
E 36
E 2
D 16
	char dirpath[RPCMNT_PATHLEN+1];
E 16
I 16
D 38
	char rpcpath[RPCMNT_PATHLEN+1], dirpath[MAXPATHLEN];
E 16
D 9
	int ok = 0;
E 9
D 20
	int bad = ENOENT;
I 16
	int found, matched;
E 16
	int omask;
E 20
I 20
	int bad = ENOENT, omask, defset;
E 38
I 38
	char rpcpath[RPCMNT_PATHLEN + 1], dirpath[MAXPATHLEN];
D 39
	int bad = ENOENT, omask, defset, hostset;
E 39
I 39
	int bad = ENOENT, defset, hostset;
	sigset_t sighup_mask;
E 39
E 38
E 20
I 2
D 36
	uid_t uid = -2;
E 36
E 2

I 39
	sigemptyset(&sighup_mask);
	sigaddset(&sighup_mask, SIGHUP);
E 39
D 2
fprintf(stderr,"in mntsrv\n");
	if (rqstp->rq_proc == NULLPROC) {
		if (!svc_sendreply(transp, xdr_void, (caddr_t)0))
			syslog(LOG_ERR, "Can't send reply");
		return;
	}

E 2
D 36
	/* Get authorization */
	switch (rqstp->rq_cred.oa_flavor) {
	case AUTH_UNIX:
		ucr = (struct authunix_parms *)rqstp->rq_clntcred;
D 2
		if (ucr->aup_uid == 0)
			break;
		/* Fall thru to */
fprintf(stderr,"weak auth\n");
E 2
I 2
		uid = ucr->aup_uid;
		break;
E 2
	case AUTH_NULL:
	default:
D 2
		svcerr_weakauth(transp);
		return;
E 2
I 2
		break;
E 2
	}

E 36
D 2
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = ntohl(transp->xp_raddr.sin_addr.s_addr);
	saddr.sin_port = 0;
	hp = gethostbyaddr((caddr_t)&saddr, transp->xp_addrlen, AF_INET);
fprintf(stderr,"net_addr=0x%x\n",transp->xp_raddr.sin_addr.s_addr);
fprintf(stderr,"aft gethost hp=0x%x\n",hp);
E 2
I 2
	saddr = transp->xp_raddr.sin_addr.s_addr;
I 36
	sport = ntohs(transp->xp_raddr.sin_port);
E 36
D 34
	hp = (struct hostent *)0;
E 34
I 34
	hp = (struct hostent *)NULL;
E 34
E 2
	switch (rqstp->rq_proc) {
I 2
	case NULLPROC:
D 34
		if (!svc_sendreply(transp, xdr_void, (caddr_t)0))
E 34
I 34
		if (!svc_sendreply(transp, xdr_void, (caddr_t)NULL))
E 34
			syslog(LOG_ERR, "Can't send reply");
		return;
E 2
	case RPCMNT_MOUNT:
D 2
fprintf(stderr,"in mnt req\n");
E 2
I 2
D 9
		if (uid != 0) {
E 9
I 9
D 16
		if (uid != 0 && root_only) {
E 16
I 16
D 36
		if ((uid != 0 && root_only) || uid == -2) {
E 36
I 36
		if (sport >= IPPORT_RESERVED && resvport_only) {
E 36
E 16
E 9
			svcerr_weakauth(transp);
			return;
		}
E 2
D 16
		if (!svc_getargs(transp, xdr_dir, dirpath)) {
E 16
I 16
		if (!svc_getargs(transp, xdr_dir, rpcpath)) {
E 16
			svcerr_decode(transp);
			return;
		}

D 2
fprintf(stderr,"dirpath=%s\n",dirpath);
		/* If no hostname, return err */
#ifdef notdef
		if (hp == NULL) {
			if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
				syslog(LOG_ERR, "Can't send reply");
			return;
		}

#endif
E 2
D 16
		/* Check to see if it's a valid dirpath */
		if (stat(dirpath, &stb) < 0 || (stb.st_mode&S_IFMT) !=
			S_IFDIR) {
E 16
I 16
		/*
D 36
		 * Get the real pathname and make sure it is a directory
		 * that exists.
E 36
I 36
D 38
		 * Get the real pathname and make sure it is a file or
		 * directory that exists.
E 38
I 38
		 * Get the real pathname and make sure it is a directory
		 * or a regular file if the -r option was specified
		 * and it exists.
E 38
E 36
		 */
D 20
		if (realpath(rpcpath, dirpath) == 0 || stat(dirpath, &stb) < 0
			|| (stb.st_mode&S_IFMT) != S_IFDIR) {
E 20
I 20
		if (realpath(rpcpath, dirpath) == 0 ||
		    stat(dirpath, &stb) < 0 ||
D 35
		    (stb.st_mode & S_IFMT) != S_IFDIR ||
E 35
I 35
D 38
		    (!S_ISDIR(stb.st_mode) && !S_ISREG(stb.st_mode)) ||
E 38
I 38
		    (!S_ISDIR(stb.st_mode) &&
		     (dir_only || !S_ISREG(stb.st_mode))) ||
E 38
E 35
		    statfs(dirpath, &fsb) < 0) {
E 20
			chdir("/");	/* Just in case realpath doesn't */
			if (debug)
D 20
				fprintf(stderr,"stat failed on %s\n",dirpath);
E 20
I 20
				fprintf(stderr, "stat failed on %s\n", dirpath);
E 20
E 16
			if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
				syslog(LOG_ERR, "Can't send reply");
			return;
		}

D 2
fprintf(stderr,"Look in exports list\n");
E 2
		/* Check in the exports list */
D 39
		omask = sigblock(sigmask(SIGHUP));
E 39
I 39
		sigprocmask(SIG_BLOCK, &sighup_mask, NULL);
E 39
D 20
		ep = exphead.ex_next;
D 16
		while (ep != NULL) {
E 16
I 16
		found = FALSE;
		matched = FALSE;
		while (ep != NULL && !found && !matched) {
			struct grouplist *tgrp;
			if (debug)
			    fprintf(stderr,"dirp=[%s]\n",ep->ex_dirp);
E 16
			if (!strcmp(ep->ex_dirp, dirpath)) {
I 16
			    if (ep->ex_defset)
				grp = (struct grouplist *)0;
			    else
E 16
				grp = ep->ex_groups;
D 16
				if (grp == NULL)
					break;
D 2
				while (grp != NULL) {
					if (!strcmp(grp->gr_name, hp->h_name))
E 2
I 2

				/* Check for a host match */
				addrp = (u_long **)grp->gr_hp->h_addr_list;
				for (;;) {
					if (**addrp == saddr)
E 16
I 16
			    if (grp == NULL) {
				if (debug)
				    fprintf(stderr,"grp is null\n");
				found = TRUE;
			    } 
			    while (grp && !found) {
				matched = TRUE;
				if (debug)
				    fprintf(stderr,"type = [%d]\n",grp->type);
				if (grp->type == MNT_GROUP) {
				    tgrp = grp->gr_ptr.gt_grpname->gn_glist;
				    if (tgrp)
					addrp = (u_long **)
					   tgrp->gr_ptr.gt_hostent->h_addr_list;
				    while(tgrp && !found) {
					if (debug)
					    fprintf(stderr, "cmp [%d] [%d]\n",
						**addrp,saddr);
					if (**addrp == saddr) {
					    found = TRUE;
					    hp = tgrp->gr_ptr.gt_hostent;
					    break;
					}
					if (*++addrp == NULL) {
					    tgrp = tgrp->gr_next;
					    if (tgrp == NULL)
E 16
E 2
						break;
D 2
					grp = grp->gr_next;
E 2
I 2
D 16
					if (*++addrp == NULL)
						if (grp = grp->gr_next) {
							addrp = (u_long **)
								grp->gr_hp->h_addr_list;
						} else {
							bad = EACCES;
							if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
								syslog(LOG_ERR, "Can't send reply");
							sigsetmask(omask);
							return;
						}
E 16
I 16
					    addrp = (u_long **)tgrp->
						gr_ptr.gt_hostent->h_addr_list;
					}
				    }
				} else if (grp->type == MNT_HOST) {
				    addrp = (u_long **)
					grp->gr_ptr.gt_hostent->h_addr_list;
				    while (*addrp) {
					if (debug)
					    fprintf(stderr, "cmp [%d] [%d]\n",
						**addrp,saddr);
					if (**addrp == saddr) {
					    found = TRUE;
					    hp = grp->gr_ptr.gt_hostent;
					    break;
					}
					addrp++;
				    }
E 16
E 2
				}
D 2
				bad = EACCES;
				if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
					syslog(LOG_ERR, "Can't send reply");
				sigsetmask(omask);
				return;
E 2
I 2
D 16
				hp = grp->gr_hp;
				break;
E 16
I 16
				grp = grp->gr_next;
			    }
E 16
E 2
			}
			ep = ep->ex_next;
		}
D 16
		sigsetmask(omask);
		if (ep == NULL) {
E 16
I 16
		if (!found) {
E 16
			bad = EACCES;
			if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
				syslog(LOG_ERR, "Can't send reply");
I 16
			sigsetmask(omask);
E 16
			return;
D 16
		}

D 2
fprintf(stderr,"get file handle\n");
E 2
		/* Get the file handle */
		bzero((caddr_t)&nfh, sizeof(nfh));
		if (getfh(dirpath, (fhandle_t *)&nfh) < 0) {
			bad = errno;
			if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
E 16
I 16
		} else {
E 20
I 20
		ep = ex_search(&fsb.f_fsid);
D 38
		defset = 0;
		if (ep && (chk_host(ep->ex_defdir, saddr, &defset) ||
E 38
I 38
		hostset = defset = 0;
		if (ep && (chk_host(ep->ex_defdir, saddr, &defset, &hostset) ||
E 38
		    ((dp = dirp_search(ep->ex_dirl, dirpath)) &&
D 38
		     chk_host(dp, saddr, &defset)) ||
E 38
I 38
		     chk_host(dp, saddr, &defset, &hostset)) ||
E 38
		     (defset && scan_tree(ep->ex_defdir, saddr) == 0 &&
		      scan_tree(ep->ex_dirl, saddr) == 0))) {
I 38
			if (hostset & DP_HOSTSET)
				fhr.fhr_flag = hostset;
			else
				fhr.fhr_flag = defset;
			fhr.fhr_vers = rqstp->rq_vers;
E 38
E 20
			/* Get the file handle */
D 38
			bzero((caddr_t)&nfh, sizeof(nfh));
			if (getfh(dirpath, (fhandle_t *)&nfh) < 0) {
E 38
I 38
D 40
			bzero((caddr_t)&fhr.fhr_fh, sizeof(nfsfh_t));
E 40
I 40
			memset(&fhr.fhr_fh, 0, sizeof(nfsfh_t));
E 40
			if (getfh(dirpath, (fhandle_t *)&fhr.fhr_fh) < 0) {
E 38
				bad = errno;
D 20
				fprintf(stderr,
				    "Couldn't get file handle for %s.\n",
				    dirpath);
E 20
I 20
				syslog(LOG_ERR, "Can't get fh for %s", dirpath);
E 20
				if (!svc_sendreply(transp, xdr_long,
				    (caddr_t)&bad))
					syslog(LOG_ERR, "Can't send reply");
D 39
				sigsetmask(omask);
E 39
I 39
				sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
E 39
				return;
			}
D 38
			if (!svc_sendreply(transp, xdr_fhs, (caddr_t)&nfh))
E 38
I 38
			if (!svc_sendreply(transp, xdr_fhs, (caddr_t)&fhr))
E 38
E 16
				syslog(LOG_ERR, "Can't send reply");
D 16
			return;
E 16
I 16
			if (hp == NULL)
				hp = gethostbyaddr((caddr_t)&saddr,
				    sizeof(saddr), AF_INET);
			if (hp)
				add_mlist(hp->h_name, dirpath);
			else
				add_mlist(inet_ntoa(transp->xp_raddr.sin_addr),
					dirpath);
			if (debug)
				fprintf(stderr,"Mount successfull.\n");
I 20
		} else {
			bad = EACCES;
			if (!svc_sendreply(transp, xdr_long, (caddr_t)&bad))
				syslog(LOG_ERR, "Can't send reply");
E 20
E 16
		}
D 2
{ struct ufid *ufp;
ufp = (struct ufid *)&nfh.fh_generic;
fprintf(stderr,"ftyp=%d fnum=%d\n",nfh.fh_generic.fh_fsid.val[1],
nfh.fh_generic.fh_fsid.val[0]);
fprintf(stderr,"fid num=%d gen=%d\n",ufp->ufid_ino,ufp->ufid_gen);
}
E 2
I 2
D 9
#ifdef notnow
nfh.fh_generic.fh_fid.fid_gen = htonl(nfh.fh_generic.fh_fid.fid_gen);
#endif
E 9
E 2
D 16
		if (!svc_sendreply(transp, xdr_fhs, (caddr_t)&nfh))
			syslog(LOG_ERR, "Can't send reply");
D 2
		mlp = (struct mountlist *)malloc(sizeof(struct mountlist));
fprintf(stderr,"add to list\n");
#ifdef notdef
		if (mlp != NULL) {
			strcpy(mlp->ml_host, hp->h_name);
			strcpy(mlp->ml_dirp, dirpath);
			mlp->ml_prev = &mlhead;
			mlp->ml_next = mlhead.ml_next;
			if (mlhead.ml_next != NULL)
				mlhead.ml_next->ml_prev = mlp;
			mlhead.ml_next = mlp;
E 2
I 2
		if (hp == NULL)
			hp = gethostbyaddr((caddr_t)&saddr, sizeof(saddr), AF_INET);
D 9
		if (hp) {
			if (!fnd_mnt(hp->h_name, dirpath)) {
				strcpy(ml.ml_host, hp->h_name);
				strcpy(ml.ml_dirp, dirpath);
				write(mlfile, (caddr_t)&ml, sizeof(ml));
			}
E 2
		}
E 9
I 9
		if (hp)
			add_mlist(hp->h_name, dirpath);
E 16
I 16
D 39
		sigsetmask(omask);
E 39
I 39
		sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
E 39
E 16
E 9
D 2
#endif
E 2
		return;
	case RPCMNT_DUMP:
D 34
		if (!svc_sendreply(transp, xdr_mlist, (caddr_t)0))
E 34
I 34
		if (!svc_sendreply(transp, xdr_mlist, (caddr_t)NULL))
E 34
			syslog(LOG_ERR, "Can't send reply");
		return;
	case RPCMNT_UMOUNT:
I 2
D 9
		if (uid != 0) {
E 9
I 9
D 16
		if (uid != 0 && root_only) {
E 16
I 16
D 36
		if ((uid != 0 && root_only) || uid == -2) {
E 36
I 36
		if (sport >= IPPORT_RESERVED && resvport_only) {
E 36
E 16
E 9
			svcerr_weakauth(transp);
			return;
		}
E 2
		if (!svc_getargs(transp, xdr_dir, dirpath)) {
			svcerr_decode(transp);
			return;
		}
D 2
		if (hp != NULL) {
			mlp = mlhead.ml_next;
			while (mlp != NULL) {
				if (!strcmp(mlp->ml_host, hp->h_name) &&
				    !strcmp(mlp->ml_dirp, dirpath)) {
					mlp->ml_prev->ml_next = mlp->ml_next;
					if (mlp->ml_next != NULL)
						mlp->ml_next->ml_prev =
						   mlp->ml_prev;
					free((caddr_t)mlp);
					break;
				}
				mlp = mlp->ml_next;
			}
E 2
I 2
D 9
		hp = gethostbyaddr((caddr_t)&saddr, sizeof(saddr), AF_INET);
		if (hp && fnd_mnt(hp->h_name, dirpath)) {
			ml.ml_host[0] = '\0';
			write(mlfile, (caddr_t)&ml, sizeof(ml));
E 2
		}
E 9
D 34
		if (!svc_sendreply(transp, xdr_void, (caddr_t)0))
E 34
I 34
		if (!svc_sendreply(transp, xdr_void, (caddr_t)NULL))
E 34
			syslog(LOG_ERR, "Can't send reply");
I 9
		hp = gethostbyaddr((caddr_t)&saddr, sizeof(saddr), AF_INET);
		if (hp)
			del_mlist(hp->h_name, dirpath);
I 16
		del_mlist(inet_ntoa(transp->xp_raddr.sin_addr), dirpath);
E 16
E 9
		return;
	case RPCMNT_UMNTALL:
D 2
		if (hp != NULL) {
			mlp = mlhead.ml_next;
			while (mlp != NULL) {
				if (!strcmp(mlp->ml_host, hp->h_name)) {
					mlp2 = mlp;
					mlp->ml_prev->ml_next = mlp->ml_next;
					if (mlp->ml_next != NULL)
						mlp->ml_next->ml_prev =
						   mlp->ml_prev;
					mlp = mlp->ml_next;
					free((caddr_t)mlp2);
				} else
					mlp = mlp->ml_next;
E 2
I 2
D 9
		if (uid != 0) {
E 9
I 9
D 16
		if (uid != 0 && root_only) {
E 16
I 16
D 36
		if ((uid != 0 && root_only) || uid == -2) {
E 36
I 36
		if (sport >= IPPORT_RESERVED && resvport_only) {
E 36
E 16
E 9
			svcerr_weakauth(transp);
			return;
		}
D 9
		hp = gethostbyaddr((caddr_t)&saddr, sizeof(saddr), AF_INET);
		if (hp) {
			lseek(mlfile, (off_t)0, L_SET);
			while (read(mlfile, (caddr_t)&ml, sizeof(ml)) ==
				sizeof(ml)) {
				if (!strcmp(hp->h_name, ml.ml_host)) {
					lseek(mlfile, (off_t)-sizeof(ml),
						L_INCR);
					ml.ml_host[0] = '\0';
					write(mlfile, (caddr_t)&ml, sizeof(ml));
				}
E 2
			}
		}
E 9
D 34
		if (!svc_sendreply(transp, xdr_void, (caddr_t)0))
E 34
I 34
		if (!svc_sendreply(transp, xdr_void, (caddr_t)NULL))
E 34
			syslog(LOG_ERR, "Can't send reply");
I 9
		hp = gethostbyaddr((caddr_t)&saddr, sizeof(saddr), AF_INET);
		if (hp)
D 34
			del_mlist(hp->h_name, (char *)0);
I 16
		del_mlist(inet_ntoa(transp->xp_raddr.sin_addr), (char *)0);
E 34
I 34
			del_mlist(hp->h_name, (char *)NULL);
		del_mlist(inet_ntoa(transp->xp_raddr.sin_addr), (char *)NULL);
E 34
E 16
E 9
		return;
	case RPCMNT_EXPORT:
D 34
		if (!svc_sendreply(transp, xdr_explist, (caddr_t)0))
E 34
I 34
		if (!svc_sendreply(transp, xdr_explist, (caddr_t)NULL))
E 34
			syslog(LOG_ERR, "Can't send reply");
		return;
	default:
		svcerr_noproc(transp);
		return;
	}
}

/*
 * Xdr conversion for a dirpath string
 */
I 34
int
E 34
xdr_dir(xdrsp, dirp)
	XDR *xdrsp;
	char *dirp;
{
	return (xdr_string(xdrsp, &dirp, RPCMNT_PATHLEN));
}

/*
D 38
 * Xdr routine to generate fhstatus
E 38
I 38
 * Xdr routine to generate file handle reply
E 38
 */
I 34
int
E 34
D 38
xdr_fhs(xdrsp, nfh)
E 38
I 38
xdr_fhs(xdrsp, cp)
E 38
	XDR *xdrsp;
D 38
	nfsv2fh_t *nfh;
E 38
I 38
	caddr_t cp;
E 38
{
D 38
	int ok = 0;
E 38
I 38
	register struct fhreturn *fhrp = (struct fhreturn *)cp;
	long ok = 0, len, auth;
E 38

	if (!xdr_long(xdrsp, &ok))
		return (0);
D 2
fprintf(stderr,"eo xdr_fhs\n");
E 2
D 38
	return (xdr_opaque(xdrsp, (caddr_t)nfh, NFSX_FH));
E 38
I 38
	switch (fhrp->fhr_vers) {
	case 1:
		return (xdr_opaque(xdrsp, (caddr_t)&fhrp->fhr_fh, NFSX_V2FH));
	case 3:
		len = NFSX_V3FH;
		if (!xdr_long(xdrsp, &len))
			return (0);
		if (!xdr_opaque(xdrsp, (caddr_t)&fhrp->fhr_fh, len))
			return (0);
		if (fhrp->fhr_flag & DP_KERB)
			auth = RPCAUTH_KERB4;
		else
			auth = RPCAUTH_UNIX;
		len = 1;
		if (!xdr_long(xdrsp, &len))
			return (0);
		return (xdr_long(xdrsp, &auth));
	};
	return (0);
E 38
}

I 34
int
E 34
xdr_mlist(xdrsp, cp)
	XDR *xdrsp;
	caddr_t cp;
{
D 2
	register struct mountlist *mlp;
E 2
I 2
D 9
	struct mountlist ml;
E 9
I 9
D 34
	register struct mountlist *mlp;
E 34
I 34
	struct mountlist *mlp;
E 34
E 9
E 2
	int true = 1;
	int false = 0;
	char *strp;

D 2
	mlp = mlhead.ml_next;
	while (mlp != NULL) {
		if (!xdr_bool(xdrsp, &true))
			return (0);
		strp = &mlp->ml_host[0];
		if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
			return (0);
		strp = &mlp->ml_dirp[0];
		if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
			return (0);
		mlp = mlp->ml_next;
E 2
I 2
D 9
	lseek(mlfile, (off_t)0, L_SET);
	while (read(mlfile, (caddr_t)&ml, sizeof(ml)) == sizeof(ml)) {
		if (ml.ml_host[0] != '\0') {
			if (!xdr_bool(xdrsp, &true))
				return (0);
			strp = &ml.ml_host[0];
			if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
				return (0);
			strp = &ml.ml_dirp[0];
			if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
				return (0);
		}
E 9
I 9
	mlp = mlhead;
	while (mlp) {
		if (!xdr_bool(xdrsp, &true))
			return (0);
		strp = &mlp->ml_host[0];
		if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
			return (0);
		strp = &mlp->ml_dirp[0];
		if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
			return (0);
		mlp = mlp->ml_next;
E 9
E 2
	}
	if (!xdr_bool(xdrsp, &false))
		return (0);
	return (1);
}

/*
 * Xdr conversion for export list
 */
I 34
int
E 34
xdr_explist(xdrsp, cp)
	XDR *xdrsp;
	caddr_t cp;
{
D 34
	register struct exportlist *ep;
E 34
I 34
	struct exportlist *ep;
E 34
D 16
	register struct grouplist *grp;
E 16
I 16
D 20
	register struct grouplist *grp, *tgrp;
E 16
	int true = 1;
E 20
	int false = 0;
D 20
	char *strp;
E 20
D 28
	int omask;
E 28
I 28
D 39
	int omask, putdef;
E 39
I 39
	int putdef;
	sigset_t sighup_mask;
E 39
E 28

D 39
	omask = sigblock(sigmask(SIGHUP));
E 39
I 39
	sigemptyset(&sighup_mask);
	sigaddset(&sighup_mask, SIGHUP);
	sigprocmask(SIG_BLOCK, &sighup_mask, NULL);
E 39
D 20
	ep = exphead.ex_next;
	while (ep != NULL) {
		if (!xdr_bool(xdrsp, &true))
E 20
I 20
	ep = exphead;
	while (ep) {
D 28
		if (put_exlist(ep->ex_dirl, xdrsp, ep->ex_defdir))
E 28
I 28
		putdef = 0;
		if (put_exlist(ep->ex_dirl, xdrsp, ep->ex_defdir, &putdef))
E 28
E 20
			goto errout;
I 28
		if (ep->ex_defdir && putdef == 0 &&
D 34
			put_exlist(ep->ex_defdir, xdrsp, (struct dirlist *)0,
E 34
I 34
			put_exlist(ep->ex_defdir, xdrsp, (struct dirlist *)NULL,
E 34
			&putdef))
			goto errout;
E 28
D 20
		strp = &ep->ex_dirp[0];
		if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
			goto errout;
		grp = ep->ex_groups;
		while (grp != NULL) {
D 16
			if (!xdr_bool(xdrsp, &true))
				goto errout;
D 2
			strp = &grp->gr_name[0];
E 2
I 2
			strp = grp->gr_hp->h_name;
E 2
			if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
				goto errout;
E 16
I 16
			if (grp->type == MNT_GROUP) {
				tgrp = grp->gr_ptr.gt_grpname->gn_glist;
				while (tgrp) {
					if (!xdr_bool(xdrsp, &true))
						goto errout;
					strp = tgrp->gr_ptr.gt_hostent->h_name;
					if (!xdr_string(xdrsp, &strp,
					    RPCMNT_NAMELEN))
						goto errout;
					tgrp = tgrp->gr_next;
				}
			} else if (grp->type == MNT_HOST) {
				if (!xdr_bool(xdrsp, &true))
					goto errout;
				strp = grp->gr_ptr.gt_hostent->h_name;
				if (!xdr_string(xdrsp, &strp, RPCMNT_NAMELEN))
					goto errout;
			}
E 16
			grp = grp->gr_next;
		}
		if (!xdr_bool(xdrsp, &false))
			goto errout;
E 20
		ep = ep->ex_next;
	}
D 39
	sigsetmask(omask);
E 39
I 39
	sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
E 39
	if (!xdr_bool(xdrsp, &false))
		return (0);
	return (1);
errout:
D 39
	sigsetmask(omask);
E 39
I 39
	sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
E 39
	return (0);
}

I 20
/*
 * Called from xdr_explist() to traverse the tree and export the
 * directory paths.
 */
I 34
int
E 34
D 28
put_exlist(dp, xdrsp, adp)
E 28
I 28
put_exlist(dp, xdrsp, adp, putdefp)
E 28
D 34
	register struct dirlist *dp;
E 34
I 34
	struct dirlist *dp;
E 34
	XDR *xdrsp;
	struct dirlist *adp;
I 28
	int *putdefp;
E 28
{
D 34
	register struct grouplist *grp;
	register struct hostlist *hp;
	struct in_addr inaddr;
E 34
I 34
	struct grouplist *grp;
	struct hostlist *hp;
E 34
	int true = 1;
	int false = 0;
	int gotalldir = 0;
	char *strp;

	if (dp) {
D 28
		if (put_exlist(dp->dp_left, xdrsp, adp))
E 28
I 28
		if (put_exlist(dp->dp_left, xdrsp, adp, putdefp))
E 28
			return (1);
		if (!xdr_bool(xdrsp, &true))
			return (1);
		strp = dp->dp_dirp;
		if (!xdr_string(xdrsp, &strp, RPCMNT_PATHLEN))
			return (1);
D 28
		if (adp && !strcmp(dp->dp_dirp, adp->dp_dirp))
E 28
I 28
		if (adp && !strcmp(dp->dp_dirp, adp->dp_dirp)) {
E 28
			gotalldir = 1;
I 28
			*putdefp = 1;
		}
E 28
		if ((dp->dp_flag & DP_DEFSET) == 0 &&
		    (gotalldir == 0 || (adp->dp_flag & DP_DEFSET) == 0)) {
			hp = dp->dp_hosts;
			while (hp) {
				grp = hp->ht_grp;
				if (grp->gr_type == GT_HOST) {
					if (!xdr_bool(xdrsp, &true))
						return (1);
					strp = grp->gr_ptr.gt_hostent->h_name;
					if (!xdr_string(xdrsp, &strp, 
					    RPCMNT_NAMELEN))
						return (1);
				} else if (grp->gr_type == GT_NET) {
					if (!xdr_bool(xdrsp, &true))
						return (1);
					strp = grp->gr_ptr.gt_net.nt_name;
					if (!xdr_string(xdrsp, &strp, 
					    RPCMNT_NAMELEN))
						return (1);
				}
				hp = hp->ht_next;
D 34
				if (gotalldir && hp == (struct hostlist *)0) {
E 34
I 34
				if (gotalldir && hp == (struct hostlist *)NULL) {
E 34
					hp = adp->dp_hosts;
					gotalldir = 0;
				}
			}
		}
		if (!xdr_bool(xdrsp, &false))
			return (1);
D 28
		if (put_exlist(dp->dp_right, xdrsp, adp))
E 28
I 28
		if (put_exlist(dp->dp_right, xdrsp, adp, putdefp))
E 28
			return (1);
	}
	return (0);
}

E 20
#define LINESIZ	10240
char line[LINESIZ];
I 20
FILE *exp_file;
E 20

/*
 * Get the export list
 */
I 15
void
E 15
get_exportlist()
{
D 2
	register struct exportlist *ep, *ep2;
E 2
I 2
D 16
	register struct hostent *hp, *nhp;
	register char **addrp, **naddrp;
	register int i;
E 2
D 9
	register struct grouplist *grp, *grp2;
E 9
I 9
	register struct grouplist *grp;
E 16
I 16
D 20
	struct grouplist *grp, *tgrp;
	struct al_mnt *al_mp, *t_almp;
E 20
E 16
E 9
I 2
D 34
	register struct exportlist *ep, *ep2;
I 13
D 16
	struct statfs stfsbuf;
E 13
I 4
	struct ufs_args args;
I 9
	struct stat sb;
E 16
I 16
D 20
	struct groupnames *t_gn, *t_gn2;
	struct ucred anoncr;
E 16
E 9
E 4
E 2
	FILE *inf;
	char *cp, *endcp;
E 20
I 20
	register struct grouplist *grp, *tgrp;
E 34
I 34
	struct exportlist *ep, *ep2;
	struct grouplist *grp, *tgrp;
E 34
	struct exportlist **epp;
	struct dirlist *dirhead;
D 32
	struct stat sb;
E 32
D 21
	struct statfs fsb;
E 21
I 21
	struct statfs fsb, *fsp;
E 21
	struct hostent *hpe;
	struct ucred anon;
I 21
D 29
	struct ufs_args targs;
E 29
E 21
D 22
	char *cp, *endcp, *dirp;
E 20
I 2
	char savedc;
E 2
D 9
	int len;
E 9
I 9
D 16
	int len, dirplen;
E 9
	int rootuid, exflags;
I 9
	u_long saddr;
	struct exportlist *fep;
E 16
I 16
D 20
	int len, dirplen, def_set;
	int exflags;
E 20
I 20
D 21
	int len, has_host, exflags, got_nondir, dirplen;
E 21
I 21
	int len, has_host, exflags, got_nondir, dirplen, num, i;
E 22
I 22
	char *cp, *endcp, *dirp, *hst, *usr, *dom, savedc;
	int len, has_host, exflags, got_nondir, dirplen, num, i, netgrp;
E 22
E 21
E 20
E 16
E 9

	/*
	 * First, get rid of the old list
	 */
D 20
	ep = exphead.ex_next;
	while (ep != NULL) {
E 20
I 20
	ep = exphead;
	while (ep) {
E 20
D 9
		grp = ep->ex_groups;
		while (grp != NULL) {
I 2
			addrp = grp->gr_hp->h_addr_list;
			while (*addrp)
				free(*addrp++);
			free((caddr_t)grp->gr_hp->h_addr_list);
			free(grp->gr_hp->h_name);
			free((caddr_t)grp->gr_hp);
E 2
			grp2 = grp;
			grp = grp->gr_next;
			free((caddr_t)grp2);
		}
E 9
		ep2 = ep;
		ep = ep->ex_next;
D 9
		free((caddr_t)ep2);
E 9
I 9
		free_exp(ep2);
E 9
	}
I 16
D 20
	exphead.ex_next = exphead.ex_prev = (struct exportlist *)0;
E 20
I 20
D 34
	exphead = (struct exportlist *)0;
E 34
I 34
	exphead = (struct exportlist *)NULL;
E 34
E 20
E 16

I 16
D 20
	t_gn = grpnames;
	while(t_gn != NULL) {
		t_gn2 = t_gn;
		t_gn = t_gn->gn_next;
		free_grp(t_gn2);
E 20
I 20
	grp = grphead;
	while (grp) {
		tgrp = grp;
		grp = grp->gr_next;
		free_grp(tgrp);
E 20
	}
D 20
	grpnames = (struct groupnames *)0;
E 20
I 20
D 34
	grphead = (struct grouplist *)0;
E 34
I 34
	grphead = (struct grouplist *)NULL;
E 34
E 20

D 20
	al_mp = al_head;
	while (al_mp) {
		t_almp = al_mp;
		al_mp = al_mp->al_next;
		free((caddr_t)t_almp);
	}
	al_head = (struct al_mnt *)0;

E 20
E 16
	/*
I 21
	 * And delete exports that are in the kernel for all local
	 * file systems.
	 * XXX: Should know how to handle all local exportable file systems
D 38
	 *      instead of just MOUNT_UFS.
E 38
I 38
	 *      instead of just "ufs".
E 38
	 */
D 23
	num = getmntinfo(&fsp, MNT_WAIT);
E 23
I 23
	num = getmntinfo(&fsp, MNT_NOWAIT);
E 23
	for (i = 0; i < num; i++) {
D 29
		if (fsp->f_type == MOUNT_UFS) {
			targs.fspec = (char *)0;
			targs.exflags = MNT_DELEXPORT;
E 29
I 29
		union {
			struct ufs_args ua;
			struct iso_args ia;
			struct mfs_args ma;
		} targs;

D 38
		switch (fsp->f_type) {
D 30
		case MOUNT_UFS:
		case MOUNT_ISOFS:
E 30
		case MOUNT_MFS:
D 30
			targs.ua.fspec = (char *)0;
E 30
I 30
		case MOUNT_UFS:
		case MOUNT_CD9660:
E 38
I 38
		if (!strcmp(fsp->f_fstypename, "mfs") ||
		    !strcmp(fsp->f_fstypename, "ufs") ||
		    !strcmp(fsp->f_fstypename, "cd9660")) {
E 38
			targs.ua.fspec = NULL;
E 30
			targs.ua.export.ex_flags = MNT_DELEXPORT;
E 29
D 38
			if (mount(fsp->f_type, fsp->f_mntonname,
E 38
I 38
			if (mount(fsp->f_fstypename, fsp->f_mntonname,
E 38
D 29
			    fsp->f_flags | MNT_UPDATE, (caddr_t)&targs) < 0)
				syslog(LOG_ERR, "Can't del exports %s",
E 29
I 29
				  fsp->f_flags | MNT_UPDATE,
				  (caddr_t)&targs) < 0)
				syslog(LOG_ERR, "Can't delete exports for %s",
E 29
				       fsp->f_mntonname);
		}
		fsp++;
	}

	/*
E 21
	 * Read in the exports file and build the list, calling
D 16
	 * exportfs() as we go along
E 16
I 16
	 * mount() as we go along to push the export rules into the kernel.
E 16
	 */
D 16
	exphead.ex_next = exphead.ex_prev = (struct exportlist *)0;
E 16
D 20
	if ((inf = fopen(exname, "r")) == NULL) {
E 20
I 20
	if ((exp_file = fopen(exname, "r")) == NULL) {
E 20
		syslog(LOG_ERR, "Can't open %s", exname);
		exit(2);
	}
D 20
	while (fgets(line, LINESIZ, inf)) {
D 4
		exflags = 0;
E 4
I 4
D 6
		exflags = M_EXPORTED;
E 6
I 6
D 16
		exflags = MNT_EXPORTED;
E 6
E 4
		rootuid = def_rootuid;
E 16
I 16
		def_set = TRUE;
E 20
I 20
D 34
	dirhead = (struct dirlist *)0;
E 34
I 34
	dirhead = (struct dirlist *)NULL;
E 34
	while (get_line()) {
E 20
		if (debug)
			fprintf(stderr,"Got line %s\n",line);
E 16
		cp = line;
		nextfield(&cp, &endcp);
I 9
D 16

		/*
		 * Get file system devno and see if an entry for this
		 * file system already exists.
		 */
		savedc = *endcp;
		*endcp = '\0';
D 14
		if (stat(cp, &sb) < 0 || (sb.st_mode & S_IFMT) != S_IFDIR)
			goto err;
E 14
I 14
		if (stat(cp, &sb) < 0 || (sb.st_mode & S_IFMT) != S_IFDIR) {
			syslog(LOG_ERR,
			    "Bad Exports File, %s: %s, mountd Failed",
			    cp, "Not a directory");
			exit(2);
E 16
I 16
		if (*cp == '#')
			goto nextline;
D 20
		if (*cp != '/') {
			/* create group listing of names */
			get_group(cp, ep);
			goto nextline;
E 16
		}
E 20
I 20

		/*
		 * Set defaults.
		 */
		has_host = FALSE;
		anon = def_anon;
E 20
E 14
D 16
		fep = (struct exportlist *)0;
		ep = exphead.ex_next;
		while (ep) {
			if (ep->ex_dev == sb.st_dev) {
				fep = ep;
				break;
			}
			ep = ep->ex_next;
		}
		*endcp = savedc;
E 16
I 16
		exflags = MNT_EXPORTED;
D 20
		anoncr = def_anon;
E 20
I 20
		got_nondir = 0;
		opt_flags = 0;
D 34
		ep = (struct exportlist *)0;
E 34
I 34
		ep = (struct exportlist *)NULL;
E 34
E 20
E 16

		/*
		 * Create new exports list entry
		 */
E 9
		len = endcp-cp;
D 20
		if (len <= RPCMNT_PATHLEN && len > 0) {
D 16
			ep = (struct exportlist *)malloc(sizeof(*ep));
I 14
			if (ep == NULL)
				goto err;
E 14
			ep->ex_next = ep->ex_prev = (struct exportlist *)0;
			ep->ex_groups = (struct grouplist *)0;
			bcopy(cp, ep->ex_dirp, len);
			ep->ex_dirp[len] = '\0';
E 16
I 16
			/*
			 * See if this directory is already in the list.
			 */
			ep = exphead.ex_next;
			while (ep) {
				if (!strcmp(ep->ex_dirp, cp))
					break;
				ep = ep->ex_next;
			}
			if (ep == (struct exportlist *)0) {
				ep = (struct exportlist *)malloc(sizeof(*ep));
				if (ep == NULL)
					goto err;
				ep->ex_next = (struct exportlist *)0;
				ep->ex_prev = (struct exportlist *)0;
				ep->ex_groups = (struct grouplist *)0;
				ep->ex_defset = FALSE;
				bcopy(cp, ep->ex_dirp, len);
				ep->ex_dirp[len] = '\0';
			}
E 16
I 9
			dirplen = len;
I 16
			if (debug)
				fprintf(stderr, "Making new ep. [%s]\n",
				    ep->ex_dirp);
E 16
E 9
D 14
		} else
			goto err;
E 14
I 14
		} else {
D 16
			syslog(LOG_ERR, "Bad Exports File, mountd Failed");
			exit(2);
E 16
I 16
			syslog(LOG_ERR, "Bad Exports File line: %s\n", line);
			goto nextline;
E 16
		}
E 14
		cp = endcp;
		nextfield(&cp, &endcp);
		len = endcp-cp;
E 20
I 20
D 22
		grp = get_grp();
E 22
I 22
		tgrp = grp = get_grp();
E 22
E 20
		while (len > 0) {
I 2
D 20
			savedc = *endcp;
			*endcp = '\0';
E 2
D 14
			if (len <= RPCMNT_NAMELEN) {
				if (*cp == '-') {
D 9
					cp++;
					switch (*cp) {
					case 'o':
D 6
						exflags |= M_EXRDONLY;
E 6
I 6
						exflags |= MNT_EXRDONLY;
E 6
						break;
					case 'r':
						if (*++cp == '=')
							rootuid = atoi(++cp);
						break;
					default:
						syslog(LOG_WARNING,
						  "Bad -%c option in %s",
						  *cp, exname);
						break;
					};
D 2
				} else {
					grp = (struct grouplist *)malloc(*grp);
E 2
I 2
				} else if (hp = gethostbyname(cp)) {
					grp = (struct grouplist *)
						malloc(sizeof(struct grouplist));
E 2
					if (grp == NULL)
E 9
I 9
				    do_opt(cp+1, fep, ep, &exflags, &rootuid);
				} else {
				    if (isdigit(*cp)) {
					saddr = inet_addr(cp);
					if (saddr == -1 ||
					    (hp = gethostbyaddr((caddr_t)&saddr,
					     sizeof(saddr), AF_INET)) == NULL)
E 9
						goto err;
D 2
					bcopy(cp, grp->gr_name, len);
					grp->gr_name[len] = '\0';
E 2
I 2
D 9
					nhp = grp->gr_hp = (struct hostent *)
						malloc(sizeof(struct hostent));
					if (nhp == NULL)
E 9
I 9
				    } else if ((hp = gethostbyname(cp)) == NULL)
					goto err;
				    grp = (struct grouplist *)
					    malloc(sizeof(struct grouplist));
				    if (grp == NULL)
					    goto err;
				    nhp = grp->gr_hp = (struct hostent *)
					    malloc(sizeof(struct hostent));
				    if (nhp == NULL)
					    goto err;
				    bcopy((caddr_t)hp, (caddr_t)nhp,
					    sizeof(struct hostent));
				    i = strlen(hp->h_name)+1;
				    nhp->h_name = (char *)malloc(i);
				    if (nhp->h_name == NULL)
					    goto err;
				    bcopy(hp->h_name, nhp->h_name, i);
				    addrp = hp->h_addr_list;
				    i = 1;
				    while (*addrp++)
					    i++;
				    naddrp = nhp->h_addr_list = (char **)
					    malloc(i*sizeof(char *));
				    if (naddrp == NULL)
					    goto err;
				    addrp = hp->h_addr_list;
				    while (*addrp) {
					    *naddrp = (char *)
					        malloc(hp->h_length);
					    if (*naddrp == NULL)
E 9
						goto err;
D 9
					bcopy((caddr_t)hp, (caddr_t)nhp,
						sizeof(struct hostent));
					i = strlen(hp->h_name)+1;
					nhp->h_name = (char *)malloc(i);
					if (nhp->h_name == NULL)
						goto err;
					bcopy(hp->h_name, nhp->h_name, i);
					addrp = hp->h_addr_list;
					i = 1;
					while (*addrp++)
						i++;
					naddrp = nhp->h_addr_list = (char **)
						malloc(i*sizeof(char *));
					if (naddrp == NULL)
						goto err;
					addrp = hp->h_addr_list;
					while (*addrp) {
						*naddrp = (char *)
						    malloc(hp->h_length);
						bcopy(*addrp, *naddrp,
							hp->h_length);
						addrp++;
						naddrp++;
					}
					*naddrp = (char *)0;
E 2
					grp->gr_next = ep->ex_groups;
					ep->ex_groups = grp;
E 9
I 9
					    bcopy(*addrp, *naddrp,
						    hp->h_length);
					    addrp++;
					    naddrp++;
				    }
				    *naddrp = (char *)0;
				    grp->gr_next = ep->ex_groups;
				    ep->ex_groups = grp;
E 14
I 14
			if (len > RPCMNT_NAMELEN)
				goto more;
E 20
I 20
			if (len > RPCMNT_NAMELEN) {
D 22
			    getexp_err(ep, grp);
E 22
I 22
			    getexp_err(ep, tgrp);
E 22
			    goto nextline;
			}
E 20
			if (*cp == '-') {
D 16
				do_opt(cp + 1, fep, ep, &exflags, &rootuid);
E 16
I 16
D 20
				do_opt(cp + 1, ep, &exflags, &anoncr);
				exflags |= MNT_EXPORTED;
				def_set = TRUE;
				if (debug)
					fprintf(stderr, "got r=%d, ex=%d\n",
					    anoncr.cr_uid,exflags);
E 16
				goto more;
D 16
			}
			if (isdigit(*cp)) {
				saddr = inet_addr(cp);
				if (saddr == -1 ||
				    (hp = gethostbyaddr((caddr_t)&saddr,
				     sizeof(saddr), AF_INET)) == NULL) {
					syslog(LOG_ERR,
					    "Bad Exports File, %s: %s", cp,
					    "Gethostbyaddr failed, ignored");
					goto more;
E 16
I 16
			} else {
				def_set = FALSE;
				if (*cp == '$') {
					do_group(cp + 1, endcp, &grp);
					grp->type = MNT_GROUP;
E 20
I 20
D 34
			    if (ep == (struct exportlist *)0) {
E 34
I 34
			    if (ep == (struct exportlist *)NULL) {
E 34
D 22
				getexp_err(ep, grp);
E 22
I 22
				getexp_err(ep, tgrp);
E 22
				goto nextline;
			    }
			    if (debug)
				fprintf(stderr, "doing opt %s\n", cp);
			    got_nondir = 1;
			    if (do_opt(&cp, &endcp, ep, grp, &has_host,
				&exflags, &anon)) {
D 22
				getexp_err(ep, grp);
E 22
I 22
				getexp_err(ep, tgrp);
E 22
				goto nextline;
			    }
			} else if (*cp == '/') {
			    savedc = *endcp;
			    *endcp = '\0';
D 32
			    if (stat(cp, &sb) >= 0 &&
				(sb.st_mode & S_IFMT) == S_IFDIR &&
E 32
I 32
			    if (check_dirpath(cp) &&
E 32
				statfs(cp, &fsb) >= 0) {
				if (got_nondir) {
				    syslog(LOG_ERR, "Dirs must be first");
D 22
				    getexp_err(ep, grp);
E 22
I 22
				    getexp_err(ep, tgrp);
E 22
				    goto nextline;
				}
				if (ep) {
				    if (ep->ex_fs.val[0] != fsb.f_fsid.val[0] ||
					ep->ex_fs.val[1] != fsb.f_fsid.val[1]) {
D 22
					getexp_err(ep, grp);
E 22
I 22
					getexp_err(ep, tgrp);
E 22
					goto nextline;
				    }
E 20
				} else {
D 20
					get_host(cp, endcp, ep, &grp);
E 20
I 20
				    /*
				     * See if this directory is already
				     * in the list.
				     */
				    ep = ex_search(&fsb.f_fsid);
D 34
				    if (ep == (struct exportlist *)0) {
E 34
I 34
				    if (ep == (struct exportlist *)NULL) {
E 34
					ep = get_exp();
					ep->ex_fs = fsb.f_fsid;
					ep->ex_fsdir = (char *)
					    malloc(strlen(fsb.f_mntonname) + 1);
					if (ep->ex_fsdir)
					    strcpy(ep->ex_fsdir,
						fsb.f_mntonname);
					else
					    out_of_mem();
					if (debug)
					  fprintf(stderr,
					      "Making new ep fs=0x%x,0x%x\n",
					      fsb.f_fsid.val[0],
					      fsb.f_fsid.val[1]);
				    } else if (debug)
					fprintf(stderr,
					    "Found ep fs=0x%x,0x%x\n",
					    fsb.f_fsid.val[0],
					    fsb.f_fsid.val[1]);
E 20
E 16
E 14
E 9
				}
I 14
D 16
			} else if ((hp = gethostbyname(cp)) == NULL) {
				syslog(LOG_ERR, "Bad Exports File, %s: %s",
				    cp, "Gethostbyname failed, ignored");
				goto more;
E 16
I 16
D 20
				if (grp != NULL) {
					grp->exflags = exflags;
					grp->anoncr = anoncr;
					grp->gr_next = ep->ex_groups;
					ep->ex_groups = grp;
				}
E 20
I 20

				/*
				 * Add dirpath to export mount point.
				 */
				dirp = add_expdir(&dirhead, cp, len);
				dirplen = len;
			    } else {
D 22
				getexp_err(ep, grp);
E 22
I 22
				getexp_err(ep, tgrp);
E 22
				goto nextline;
			    }
			    *endcp = savedc;
			} else {
			    savedc = *endcp;
			    *endcp = '\0';
			    got_nondir = 1;
D 22
			    if (ep == (struct exportlist *)0 || has_host) {
				getexp_err(ep, grp);
E 22
I 22
D 34
			    if (ep == (struct exportlist *)0) {
E 34
I 34
			    if (ep == (struct exportlist *)NULL) {
E 34
				getexp_err(ep, tgrp);
E 22
				goto nextline;
			    }
D 22
			    if (get_host(cp, grp)) {
				getexp_err(ep, grp);
				goto nextline;
			    }
			    has_host = TRUE;
E 22
I 22

			    /*
			     * Get the host or netgroup.
			     */
			    setnetgrent(cp);
			    netgrp = getnetgrent(&hst, &usr, &dom);
			    do {
				if (has_host) {
				    grp->gr_next = get_grp();
				    grp = grp->gr_next;
				}
				if (netgrp) {
				    if (get_host(hst, grp)) {
					syslog(LOG_ERR, "Bad netgroup %s", cp);
					getexp_err(ep, tgrp);
I 37
					endnetgrent();
E 37
					goto nextline;
				    }
				} else if (get_host(cp, grp)) {
				    getexp_err(ep, tgrp);
				    goto nextline;
				}
				has_host = TRUE;
			    } while (netgrp && getnetgrent(&hst, &usr, &dom));
			    endnetgrent();
E 22
			    *endcp = savedc;
E 20
E 16
E 14
			}
I 14
D 16
			grp = (struct grouplist *)
				malloc(sizeof(struct grouplist));
			if (grp == NULL)
				goto err;
			nhp = grp->gr_hp = (struct hostent *)
				malloc(sizeof(struct hostent));
			if (nhp == NULL)
				goto err;
			bcopy((caddr_t)hp, (caddr_t)nhp,
				sizeof(struct hostent));
			i = strlen(hp->h_name)+1;
			nhp->h_name = (char *)malloc(i);
			if (nhp->h_name == NULL)
				goto err;
			bcopy(hp->h_name, nhp->h_name, i);
			addrp = hp->h_addr_list;
			i = 1;
			while (*addrp++)
				i++;
			naddrp = nhp->h_addr_list = (char **)
				malloc(i*sizeof(char *));
			if (naddrp == NULL)
				goto err;
			addrp = hp->h_addr_list;
			while (*addrp) {
				*naddrp = (char *)
				    malloc(hp->h_length);
				if (*naddrp == NULL)
				    goto err;
				bcopy(*addrp, *naddrp,
					hp->h_length);
				addrp++;
				naddrp++;
			}
			*naddrp = (char *)0;
			grp->gr_next = ep->ex_groups;
			ep->ex_groups = grp;
E 16
D 20
		more:
E 20
E 14
			cp = endcp;
I 2
D 20
			*cp = savedc;
E 20
E 2
			nextfield(&cp, &endcp);
D 14
			len = endcp-cp;
E 14
I 14
			len = endcp - cp;
E 14
		}
D 4
		if (exportfs(ep->ex_dirp, rootuid, exflags) < 0) {
E 4
I 4
D 9
		args.fspec = 0;
		args.exflags = exflags;
		args.exroot = rootuid;
D 6
		if (mount(MOUNT_UFS, ep->ex_dirp, M_UPDATE, &args) < 0) {
E 6
I 6
		if (mount(MOUNT_UFS, ep->ex_dirp, MNT_UPDATE, &args) < 0) {
E 6
E 4
			syslog(LOG_WARNING, "Can't export %s", ep->ex_dirp);
			free((caddr_t)ep);
		} else {
E 9
I 9
D 16
		if (fep == NULL) {
			args.fspec = 0;
			args.exflags = exflags;
			args.exroot = rootuid;
E 16
I 16
D 20
		if (def_set == TRUE) {
		    if (ep->ex_defset == TRUE)
			syslog(LOG_ERR, "Default specified again dir:%s\n",
				ep->ex_dirp);
		    else {
			struct hostent *hpe;

			ep->ex_defset = TRUE;
E 20
I 20
		if (check_options(dirhead)) {
D 22
			getexp_err(ep, grp);
E 22
I 22
			getexp_err(ep, tgrp);
E 22
			goto nextline;
		}
		if (!has_host) {
			grp->gr_type = GT_HOST;
E 20
			if (debug)
				fprintf(stderr,"Adding a default entry\n");
			/* add a default group and make the grp list NULL */
			hpe = (struct hostent *)malloc(sizeof(struct hostent));
D 20
			if (hpe == NULL) {
				syslog(LOG_ERR,"No more memory: mountd Failed");
				exit(2);
			}
			tgrp = (struct grouplist *)
			    malloc(sizeof(struct grouplist));
			if (tgrp == NULL) {
				syslog(LOG_ERR,"No more memory: mountd Failed");
				exit(2);
			}
			tgrp->anoncr = anoncr;
			tgrp->exflags = exflags;
D 18
			hpe->h_name = (char *)malloc(sizeof(DEF_NAME)+1);
			if (hpe->h_name == NULL) {
				syslog(LOG_ERR,"No more memory: mountd Failed");
				exit(2);
			}
			strcpy(hpe->h_name,DEF_NAME);
E 18
I 18
			tgrp->type = MNT_HOST;
			hpe->h_name = (char *)0;
E 20
I 20
D 34
			if (hpe == (struct hostent *)0)
E 34
I 34
			if (hpe == (struct hostent *)NULL)
E 34
				out_of_mem();
			hpe->h_name = "Default";
E 20
E 18
			hpe->h_addrtype = AF_INET;
			hpe->h_length = sizeof (u_long);
D 18
			hpe->h_addr_list = INADDR_ANY;
E 18
I 18
D 34
			hpe->h_addr_list = (char **)0;
E 34
I 34
			hpe->h_addr_list = (char **)NULL;
E 34
E 18
D 20
			tgrp->gr_ptr.gt_hostent = hpe;
			tgrp->gr_next = ep->ex_groups;
			ep->ex_groups = tgrp;
		    }
E 20
I 20
			grp->gr_ptr.gt_hostent = hpe;
I 22

		/*
		 * Don't allow a network export coincide with a list of
		 * host(s) on the same line.
		 */
		} else if ((opt_flags & OP_NET) && tgrp->gr_next) {
			getexp_err(ep, tgrp);
			goto nextline;
E 22
E 20
		}
D 20
		grp = ep->ex_groups;
		while (grp != NULL) {
			exflags = grp->exflags;
			anoncr = grp->anoncr;
			if (grp->type == MNT_GROUP) {
				tgrp = grp->gr_ptr.gt_grpname->gn_glist;
				while(tgrp != NULL) {
					if (do_mount(ep, tgrp, exflags, &anoncr,
					    dirplen) == FALSE)
						goto nextline;
					tgrp = tgrp->gr_next;
E 20
I 20
D 22
		if (do_mount(ep, grp, exflags, &anon, dirp,
E 22
I 22

		/*
		 * Loop through hosts, pushing the exports into the kernel.
		 * After loop, tgrp points to the start of the list and
		 * grp points to the last entry in the list.
		 */
		grp = tgrp;
		do {
		    if (do_mount(ep, grp, exflags, &anon, dirp,
E 22
			dirplen, &fsb)) {
D 22
			getexp_err(ep, grp);
E 22
I 22
			getexp_err(ep, tgrp);
E 22
			goto nextline;
D 22
		}
E 22
I 22
		    }
		} while (grp->gr_next && (grp = grp->gr_next));
E 22

		/*
		 * Success. Update the data structures.
		 */
		if (has_host) {
I 22
D 38
			hang_dirp(dirhead, tgrp, ep, (opt_flags & OP_ALLDIRS));
E 38
I 38
			hang_dirp(dirhead, tgrp, ep, opt_flags);
E 38
E 22
			grp->gr_next = grphead;
D 22
			grphead = grp;
			hang_dirp(dirhead, grp, ep, (opt_flags & OP_ALLDIRS));
E 22
I 22
			grphead = tgrp;
E 22
		} else {
D 34
			hang_dirp(dirhead, (struct grouplist *)0, ep,
E 34
I 34
			hang_dirp(dirhead, (struct grouplist *)NULL, ep,
E 34
D 22
				(opt_flags & OP_ALLDIRS));
E 22
I 22
D 38
			(opt_flags & OP_ALLDIRS));
E 38
I 38
				opt_flags);
E 38
E 22
			free_grp(grp);
		}
D 34
		dirhead = (struct dirlist *)0;
E 34
I 34
		dirhead = (struct dirlist *)NULL;
E 34
		if ((ep->ex_flag & EX_LINKED) == 0) {
			ep2 = exphead;
			epp = &exphead;

			/*
			 * Insert in the list in alphabetical order.
			 */
			while (ep2 && strcmp(ep2->ex_fsdir, ep->ex_fsdir) < 0) {
				epp = &ep2->ex_next;
				ep2 = ep2->ex_next;
			}
			if (ep2)
				ep->ex_next = ep2;
			*epp = ep;
			ep->ex_flag |= EX_LINKED;
		}
nextline:
		if (dirhead) {
			free_dir(dirhead);
D 34
			dirhead = (struct dirlist *)0;
E 34
I 34
			dirhead = (struct dirlist *)NULL;
E 34
		}
	}
	fclose(exp_file);
}

/*
 * Allocate an export list element
 */
struct exportlist *
get_exp()
{
D 34
	register struct exportlist *ep;
E 34
I 34
	struct exportlist *ep;
E 34

	ep = (struct exportlist *)malloc(sizeof (struct exportlist));
D 34
	if (ep == (struct exportlist *)0)
E 34
I 34
	if (ep == (struct exportlist *)NULL)
E 34
		out_of_mem();
D 40
	bzero((caddr_t)ep, sizeof (struct exportlist));
E 40
I 40
	memset(ep, 0, sizeof(struct exportlist));
E 40
	return (ep);
}

/*
 * Allocate a group list element
 */
struct grouplist *
get_grp()
{
D 34
	register struct grouplist *gp;
E 34
I 34
	struct grouplist *gp;
E 34

	gp = (struct grouplist *)malloc(sizeof (struct grouplist));
D 34
	if (gp == (struct grouplist *)0)
E 34
I 34
	if (gp == (struct grouplist *)NULL)
E 34
		out_of_mem();
D 40
	bzero((caddr_t)gp, sizeof (struct grouplist));
E 40
I 40
	memset(gp, 0, sizeof(struct grouplist));
E 40
	return (gp);
}

/*
 * Clean up upon an error in get_exportlist().
 */
void
getexp_err(ep, grp)
	struct exportlist *ep;
	struct grouplist *grp;
{
I 22
	struct grouplist *tgrp;
E 22

	syslog(LOG_ERR, "Bad exports list line %s", line);
D 26
	if (ep && ep->ex_next == (struct exportlist *)0)
E 26
I 26
	if (ep && (ep->ex_flag & EX_LINKED) == 0)
E 26
		free_exp(ep);
D 22
	if (grp && grp->gr_next == (struct grouplist *)0)
		free_grp(grp);
E 22
I 22
	while (grp) {
		tgrp = grp;
		grp = grp->gr_next;
		free_grp(tgrp);
	}
E 22
}

/*
 * Search the export list for a matching fs.
 */
struct exportlist *
ex_search(fsid)
D 21
	quad *fsid;
E 21
I 21
	fsid_t *fsid;
E 21
{
D 34
	register struct exportlist *ep;
E 34
I 34
	struct exportlist *ep;
E 34

	ep = exphead;
	while (ep) {
		if (ep->ex_fs.val[0] == fsid->val[0] &&
		    ep->ex_fs.val[1] == fsid->val[1])
			return (ep);
		ep = ep->ex_next;
	}
	return (ep);
}

/*
 * Add a directory path to the list.
 */
char *
add_expdir(dpp, cp, len)
	struct dirlist **dpp;
	char *cp;
	int len;
{
D 34
	register struct dirlist *dp;
E 34
I 34
	struct dirlist *dp;
E 34

	dp = (struct dirlist *)malloc(sizeof (struct dirlist) + len);
	dp->dp_left = *dpp;
D 34
	dp->dp_right = (struct dirlist *)0;
E 34
I 34
	dp->dp_right = (struct dirlist *)NULL;
E 34
	dp->dp_flag = 0;
D 34
	dp->dp_hosts = (struct hostlist *)0;
E 34
I 34
	dp->dp_hosts = (struct hostlist *)NULL;
E 34
	strcpy(dp->dp_dirp, cp);
	*dpp = dp;
	return (dp->dp_dirp);
}

/*
 * Hang the dir list element off the dirpath binary tree as required
 * and update the entry for host.
 */
void
D 38
hang_dirp(dp, grp, ep, alldirs)
E 38
I 38
hang_dirp(dp, grp, ep, flags)
E 38
D 34
	register struct dirlist *dp;
E 34
I 34
	struct dirlist *dp;
E 34
	struct grouplist *grp;
	struct exportlist *ep;
D 38
	int alldirs;
E 38
I 38
	int flags;
E 38
{
D 34
	register struct hostlist *hp;
E 34
I 34
	struct hostlist *hp;
E 34
	struct dirlist *dp2;

D 38
	if (alldirs) {
E 38
I 38
	if (flags & OP_ALLDIRS) {
E 38
		if (ep->ex_defdir)
			free((caddr_t)dp);
		else
			ep->ex_defdir = dp;
D 24
		if (grp) {
E 24
I 24
D 34
		if (grp == (struct grouplist *)0)
E 34
I 34
D 38
		if (grp == (struct grouplist *)NULL)
E 38
I 38
		if (grp == (struct grouplist *)NULL) {
E 38
E 34
			ep->ex_defdir->dp_flag |= DP_DEFSET;
D 38
		else while (grp) {
E 38
I 38
			if (flags & OP_KERB)
				ep->ex_defdir->dp_flag |= DP_KERB;
		} else while (grp) {
E 38
E 24
			hp = get_ht();
I 38
			if (flags & OP_KERB)
				hp->ht_flag |= DP_KERB;
E 38
			hp->ht_grp = grp;
			hp->ht_next = ep->ex_defdir->dp_hosts;
			ep->ex_defdir->dp_hosts = hp;
D 24
		} else
			ep->ex_defdir->dp_flag |= DP_DEFSET;
E 24
I 24
			grp = grp->gr_next;
		}
E 24
	} else {
I 22

		/*
		 * Loop throught the directories adding them to the tree.
		 */
E 22
		while (dp) {
D 22
			if (grp) {
				hp = get_ht();
				hp->ht_grp = grp;
			} else
				hp = (struct hostlist *)0;
E 22
			dp2 = dp->dp_left;
D 22
			add_dlist(&ep->ex_dirl, dp, hp);
E 22
I 22
D 38
			add_dlist(&ep->ex_dirl, dp, grp);
E 38
I 38
			add_dlist(&ep->ex_dirl, dp, grp, flags);
E 38
E 22
			dp = dp2;
		}
	}
}

/*
 * Traverse the binary tree either updating a node that is already there
 * for the new directory or adding the new node.
 */
void
D 22
add_dlist(dpp, newdp, hp)
E 22
I 22
D 38
add_dlist(dpp, newdp, grp)
E 38
I 38
add_dlist(dpp, newdp, grp, flags)
E 38
E 22
	struct dirlist **dpp;
	struct dirlist *newdp;
D 22
	struct hostlist *hp;
E 22
I 22
D 34
	register struct grouplist *grp;
E 34
I 34
	struct grouplist *grp;
I 38
	int flags;
E 38
E 34
E 22
{
D 34
	register struct dirlist *dp;
I 22
	register struct hostlist *hp;
E 34
I 34
	struct dirlist *dp;
	struct hostlist *hp;
E 34
E 22
	int cmp;

	dp = *dpp;
	if (dp) {
		cmp = strcmp(dp->dp_dirp, newdp->dp_dirp);
		if (cmp > 0) {
D 22
			add_dlist(&dp->dp_left, newdp, hp);
E 22
I 22
D 38
			add_dlist(&dp->dp_left, newdp, grp);
E 38
I 38
			add_dlist(&dp->dp_left, newdp, grp, flags);
E 38
E 22
			return;
		} else if (cmp < 0) {
D 22
			add_dlist(&dp->dp_right, newdp, hp);
E 22
I 22
D 38
			add_dlist(&dp->dp_right, newdp, grp);
E 38
I 38
			add_dlist(&dp->dp_right, newdp, grp, flags);
E 38
E 22
			return;
		} else
			free((caddr_t)newdp);
	} else {
		dp = newdp;
D 34
		dp->dp_left = (struct dirlist *)0;
E 34
I 34
		dp->dp_left = (struct dirlist *)NULL;
E 34
		*dpp = dp;
	}
D 22
	if (hp) {
		hp->ht_next = dp->dp_hosts;
		dp->dp_hosts = hp;
E 22
I 22
	if (grp) {

		/*
		 * Hang all of the host(s) off of the directory point.
		 */
		do {
			hp = get_ht();
I 38
			if (flags & OP_KERB)
				hp->ht_flag |= DP_KERB;
E 38
			hp->ht_grp = grp;
			hp->ht_next = dp->dp_hosts;
			dp->dp_hosts = hp;
			grp = grp->gr_next;
		} while (grp);
E 22
D 38
	} else
E 38
I 38
	} else {
E 38
		dp->dp_flag |= DP_DEFSET;
I 38
		if (flags & OP_KERB)
			dp->dp_flag |= DP_KERB;
	}
E 38
}

/*
 * Search for a dirpath on the export point.
 */
struct dirlist *
dirp_search(dp, dirpath)
D 34
	register struct dirlist *dp;
E 34
I 34
	struct dirlist *dp;
E 34
	char *dirpath;
{
D 34
	register int cmp;
E 34
I 34
	int cmp;
E 34

	if (dp) {
		cmp = strcmp(dp->dp_dirp, dirpath);
		if (cmp > 0)
			return (dirp_search(dp->dp_left, dirpath));
		else if (cmp < 0)
			return (dirp_search(dp->dp_right, dirpath));
		else
			return (dp);
	}
	return (dp);
}

/*
 * Scan for a host match in a directory tree.
 */
I 34
int
E 34
D 38
chk_host(dp, saddr, defsetp)
E 38
I 38
chk_host(dp, saddr, defsetp, hostsetp)
E 38
	struct dirlist *dp;
	u_long saddr;
	int *defsetp;
I 38
	int *hostsetp;
E 38
{
D 34
	register struct hostlist *hp;
	register struct grouplist *grp;
	register u_long **addrp;
E 34
I 34
	struct hostlist *hp;
	struct grouplist *grp;
	u_long **addrp;
E 34

	if (dp) {
		if (dp->dp_flag & DP_DEFSET)
D 38
			*defsetp = 1;
E 38
I 38
			*defsetp = dp->dp_flag;
E 38
		hp = dp->dp_hosts;
		while (hp) {
			grp = hp->ht_grp;
			switch (grp->gr_type) {
			case GT_HOST:
			    addrp = (u_long **)
				grp->gr_ptr.gt_hostent->h_addr_list;
			    while (*addrp) {
D 38
				if (**addrp == saddr)
E 38
I 38
				if (**addrp == saddr) {
				    *hostsetp = (hp->ht_flag | DP_HOSTSET);
E 38
				    return (1);
I 38
				}
E 38
				addrp++;
			    }
			    break;
			case GT_NET:
			    if ((saddr & grp->gr_ptr.gt_net.nt_mask) ==
D 38
				grp->gr_ptr.gt_net.nt_net)
E 38
I 38
				grp->gr_ptr.gt_net.nt_net) {
				*hostsetp = (hp->ht_flag | DP_HOSTSET);
E 38
				return (1);
I 38
			    }
E 38
			    break;
			};
			hp = hp->ht_next;
		}
	}
	return (0);
}

/*
 * Scan tree for a host that matches the address.
 */
I 34
int
E 34
scan_tree(dp, saddr)
D 34
	register struct dirlist *dp;
E 34
I 34
	struct dirlist *dp;
E 34
	u_long saddr;
{
D 38
	int defset;
E 38
I 38
	int defset, hostset;
E 38

	if (dp) {
		if (scan_tree(dp->dp_left, saddr))
			return (1);
D 38
		if (chk_host(dp, saddr, &defset))
E 38
I 38
		if (chk_host(dp, saddr, &defset, &hostset))
E 38
			return (1);
		if (scan_tree(dp->dp_right, saddr))
			return (1);
	}
	return (0);
}

/*
 * Traverse the dirlist tree and free it up.
 */
void
free_dir(dp)
D 34
	register struct dirlist *dp;
E 34
I 34
	struct dirlist *dp;
E 34
{

	if (dp) {
		free_dir(dp->dp_left);
		free_dir(dp->dp_right);
		free_host(dp->dp_hosts);
		free((caddr_t)dp);
	}
}

/*
 * Parse the option string and update fields.
 * Option arguments may either be -<option>=<value> or
 * -<option> <value>
 */
I 34
int
E 34
do_opt(cpp, endcpp, ep, grp, has_hostp, exflagsp, cr)
	char **cpp, **endcpp;
	struct exportlist *ep;
	struct grouplist *grp;
	int *has_hostp;
	int *exflagsp;
	struct ucred *cr;
{
D 34
	register char *cpoptarg, *cpoptend;
E 34
I 34
	char *cpoptarg, *cpoptend;
E 34
	char *cp, *endcp, *cpopt, savedc, savedc2;
	int allflag, usedarg;

	cpopt = *cpp;
	cpopt++;
	cp = *endcpp;
	savedc = *cp;
	*cp = '\0';
	while (cpopt && *cpopt) {
		allflag = 1;
		usedarg = -2;
D 40
		if (cpoptend = index(cpopt, ',')) {
E 40
I 40
		if (cpoptend = strchr(cpopt, ',')) {
E 40
			*cpoptend++ = '\0';
D 40
			if (cpoptarg = index(cpopt, '='))
E 40
I 40
			if (cpoptarg = strchr(cpopt, '='))
E 40
				*cpoptarg++ = '\0';
		} else {
D 40
			if (cpoptarg = index(cpopt, '='))
E 40
I 40
			if (cpoptarg = strchr(cpopt, '='))
E 40
				*cpoptarg++ = '\0';
			else {
				*cp = savedc;
				nextfield(&cp, &endcp);
				**endcpp = '\0';
				if (endcp > cp && *cp != '-') {
					cpoptarg = cp;
					savedc2 = *endcp;
					*endcp = '\0';
					usedarg = 0;
E 20
				}
D 20
			} else {
				if (do_mount(ep, grp, exflags, &anoncr, dirplen)
				    == FALSE)
					goto nextline;
E 20
			}
D 20
			grp = grp->gr_next;
E 20
		}
D 20
		if (cp)
			*cp = savedc;
		if (ep->ex_prev == (struct exportlist *)0) {
			ep->ex_next = exphead.ex_next;
			ep->ex_prev = &exphead;
			if (ep->ex_next != NULL)
				ep->ex_next->ex_prev = ep;
			exphead.ex_next = ep;
E 20
I 20
		if (!strcmp(cpopt, "ro") || !strcmp(cpopt, "o")) {
			*exflagsp |= MNT_EXRDONLY;
		} else if (cpoptarg && (!strcmp(cpopt, "maproot") ||
		    !(allflag = strcmp(cpopt, "mapall")) ||
		    !strcmp(cpopt, "root") || !strcmp(cpopt, "r"))) {
			usedarg++;
			parsecred(cpoptarg, cr);
			if (allflag == 0) {
				*exflagsp |= MNT_EXPORTANON;
				opt_flags |= OP_MAPALL;
			} else
				opt_flags |= OP_MAPROOT;
		} else if (!strcmp(cpopt, "kerb") || !strcmp(cpopt, "k")) {
			*exflagsp |= MNT_EXKERB;
			opt_flags |= OP_KERB;
D 22
		} else if (cpoptarg && !strcmp(cpopt, "mask")) {
E 22
I 22
		} else if (cpoptarg && (!strcmp(cpopt, "mask") ||
			!strcmp(cpopt, "m"))) {
E 22
			if (get_net(cpoptarg, &grp->gr_ptr.gt_net, 1)) {
				syslog(LOG_ERR, "Bad mask: %s", cpoptarg);
				return (1);
			}
			usedarg++;
			opt_flags |= OP_MASK;
D 22
		} else if (cpoptarg && !strcmp(cpopt, "network")) {
E 22
I 22
		} else if (cpoptarg && (!strcmp(cpopt, "network") ||
			!strcmp(cpopt, "n"))) {
E 22
			if (grp->gr_type != GT_NULL) {
				syslog(LOG_ERR, "Network/host conflict");
				return (1);
			} else if (get_net(cpoptarg, &grp->gr_ptr.gt_net, 0)) {
				syslog(LOG_ERR, "Bad net: %s", cpoptarg);
				return (1);
			}
			grp->gr_type = GT_NET;
			*has_hostp = 1;
			usedarg++;
			opt_flags |= OP_NET;
		} else if (!strcmp(cpopt, "alldirs")) {
			opt_flags |= OP_ALLDIRS;
#ifdef ISO
		} else if (cpoptarg && !strcmp(cpopt, "iso")) {
			if (get_isoaddr(cpoptarg, grp)) {
				syslog(LOG_ERR, "Bad iso addr: %s", cpoptarg);
				return (1);
			}
			*has_hostp = 1;
			usedarg++;
			opt_flags |= OP_ISO;
#endif /* ISO */
		} else {
			syslog(LOG_ERR, "Bad opt %s", cpopt);
			return (1);
E 20
		}
D 20
nextline:
		;
E 20
I 20
		if (usedarg >= 0) {
			*endcp = savedc2;
			**endcpp = savedc;
			if (usedarg > 0) {
				*cpp = cp;
				*endcpp = endcp;
			}
			return (0);
		}
		cpopt = cpoptend;
E 20
	}
D 20
	fclose(inf);
	return;
err:
	syslog(LOG_ERR, "No more memory: mountd Failed");
E 20
I 20
	**endcpp = savedc;
	return (0);
}

/*
 * Translate a character string to the corresponding list of network
 * addresses for a hostname.
 */
I 34
int
E 34
get_host(cp, grp)
	char *cp;
D 34
	register struct grouplist *grp;
E 34
I 34
	struct grouplist *grp;
E 34
{
D 34
	register struct hostent *hp, *nhp;
	register char **addrp, **naddrp;
E 34
I 34
	struct hostent *hp, *nhp;
	char **addrp, **naddrp;
E 34
	struct hostent t_host;
	int i;
	u_long saddr;
	char *aptr[2];

	if (grp->gr_type != GT_NULL)
		return (1);
	if ((hp = gethostbyname(cp)) == NULL) {
		if (isdigit(*cp)) {
			saddr = inet_addr(cp);
			if (saddr == -1) {
D 37
				syslog(LOG_ERR, "Inet_addr failed");
E 37
I 37
				syslog(LOG_ERR, "Inet_addr failed for %s", cp);
E 37
				return (1);
			}
			if ((hp = gethostbyaddr((caddr_t)&saddr, sizeof (saddr),
				AF_INET)) == NULL) {
				hp = &t_host;
				hp->h_name = cp;
				hp->h_addrtype = AF_INET;
				hp->h_length = sizeof (u_long);
				hp->h_addr_list = aptr;
				aptr[0] = (char *)&saddr;
D 34
				aptr[1] = (char *)0;
E 34
I 34
				aptr[1] = (char *)NULL;
E 34
			}
		} else {
D 37
			syslog(LOG_ERR, "Gethostbyname failed");
E 37
I 37
			syslog(LOG_ERR, "Gethostbyname failed for %s", cp);
E 37
			return (1);
		}
	}
	grp->gr_type = GT_HOST;
	nhp = grp->gr_ptr.gt_hostent = (struct hostent *)
		malloc(sizeof(struct hostent));
D 34
	if (nhp == (struct hostent *)0)
E 34
I 34
	if (nhp == (struct hostent *)NULL)
E 34
		out_of_mem();
D 40
	bcopy((caddr_t)hp, (caddr_t)nhp,
		sizeof(struct hostent));
E 40
I 40
	memmove(nhp, hp, sizeof(struct hostent));
E 40
	i = strlen(hp->h_name)+1;
	nhp->h_name = (char *)malloc(i);
D 34
	if (nhp->h_name == (char *)0)
E 34
I 34
	if (nhp->h_name == (char *)NULL)
E 34
		out_of_mem();
D 40
	bcopy(hp->h_name, nhp->h_name, i);
E 40
I 40
	memmove(nhp->h_name, hp->h_name, i);
E 40
	addrp = hp->h_addr_list;
	i = 1;
	while (*addrp++)
		i++;
	naddrp = nhp->h_addr_list = (char **)
		malloc(i*sizeof(char *));
D 34
	if (naddrp == (char **)0)
E 34
I 34
	if (naddrp == (char **)NULL)
E 34
		out_of_mem();
	addrp = hp->h_addr_list;
	while (*addrp) {
		*naddrp = (char *)
		    malloc(hp->h_length);
D 34
		if (*naddrp == (char *)0)
E 34
I 34
		if (*naddrp == (char *)NULL)
E 34
		    out_of_mem();
D 40
		bcopy(*addrp, *naddrp,
			hp->h_length);
E 40
I 40
		memmove(*naddrp, *addrp, hp->h_length);
E 40
		addrp++;
		naddrp++;
	}
D 34
	*naddrp = (char *)0;
E 34
I 34
	*naddrp = (char *)NULL;
E 34
I 22
	if (debug)
		fprintf(stderr, "got host %s\n", hp->h_name);
E 22
	return (0);
}

/*
 * Free up an exports list component
 */
void
free_exp(ep)
D 34
	register struct exportlist *ep;
E 34
I 34
	struct exportlist *ep;
E 34
{

	if (ep->ex_defdir) {
		free_host(ep->ex_defdir->dp_hosts);
		free((caddr_t)ep->ex_defdir);
	}
	if (ep->ex_fsdir)
		free(ep->ex_fsdir);
	free_dir(ep->ex_dirl);
	free((caddr_t)ep);
}

/*
 * Free hosts.
 */
void
free_host(hp)
D 34
	register struct hostlist *hp;
E 34
I 34
	struct hostlist *hp;
E 34
{
D 34
	register struct hostlist *hp2;
E 34
I 34
	struct hostlist *hp2;
E 34

	while (hp) {
		hp2 = hp;
		hp = hp->ht_next;
		free((caddr_t)hp2);
	}
}

struct hostlist *
get_ht()
{
D 34
	register struct hostlist *hp;
E 34
I 34
	struct hostlist *hp;
E 34

	hp = (struct hostlist *)malloc(sizeof (struct hostlist));
D 34
	if (hp == (struct hostlist *)0)
E 34
I 34
	if (hp == (struct hostlist *)NULL)
E 34
		out_of_mem();
D 34
	hp->ht_next = (struct hostlist *)0;
E 34
I 34
	hp->ht_next = (struct hostlist *)NULL;
I 38
	hp->ht_flag = 0;
E 38
E 34
	return (hp);
}

#ifdef ISO
/*
 * Translate an iso address.
 */
get_isoaddr(cp, grp)
	char *cp;
	struct grouplist *grp;
{
	struct iso_addr *isop;
	struct sockaddr_iso *isoaddr;

	if (grp->gr_type != GT_NULL)
		return (1);
	if ((isop = iso_addr(cp)) == NULL) {
		syslog(LOG_ERR,
		    "iso_addr failed, ignored");
		return (1);
	}
	isoaddr = (struct sockaddr_iso *)
	    malloc(sizeof (struct sockaddr_iso));
D 34
	if (isoaddr == (struct sockaddr_iso *)0)
E 34
I 34
	if (isoaddr == (struct sockaddr_iso *)NULL)
E 34
		out_of_mem();
D 40
	bzero((caddr_t)isoaddr, sizeof (struct sockaddr_iso));
	bcopy((caddr_t)isop, (caddr_t)&isoaddr->siso_addr,
		sizeof (struct iso_addr));
	isoaddr->siso_len = sizeof (struct sockaddr_iso);
E 40
I 40
	memset(isoaddr, 0, sizeof(struct sockaddr_iso));
	memmove(&isoaddr->siso_addr, isop, sizeof(struct iso_addr));
	isoaddr->siso_len = sizeof(struct sockaddr_iso);
E 40
	isoaddr->siso_family = AF_ISO;
	grp->gr_type = GT_ISO;
	grp->gr_ptr.gt_isoaddr = isoaddr;
	return (0);
}
#endif	/* ISO */

/*
 * Out of memory, fatal
 */
void
out_of_mem()
{

	syslog(LOG_ERR, "Out of memory");
E 20
	exit(2);
}

D 20
do_mount(ep, grp, exflags, anoncrp, dirplen)
E 20
I 20
/*
 * Do the mount syscall with the update flag to push the export info into
 * the kernel.
 */
I 34
int
E 34
do_mount(ep, grp, exflags, anoncrp, dirp, dirplen, fsb)
E 20
	struct exportlist *ep;
	struct grouplist *grp;
D 20
	int exflags, dirplen;
E 20
I 20
	int exflags;
E 20
	struct ucred *anoncrp;
I 20
	char *dirp;
	int dirplen;
	struct statfs *fsb;
E 20
{
D 20
	int done, found;
E 20
I 20
D 34
	register char *cp = (char *)0;
E 20
	register u_long **addrp;
E 34
I 34
	char *cp = (char *)NULL;
	u_long **addrp;
E 34
D 20
	struct sockaddr_in sin;
	struct statfs stfsbuf;
E 20
I 20
	int done;
D 34
	char savedc;
E 34
I 34
	char savedc = '\0';
E 34
	struct sockaddr_in sin, imask;
E 20
D 21
	struct ufs_args args, targs;
E 21
I 21
D 29
	struct ufs_args args;
E 29
I 29
	union {
		struct ufs_args ua;
		struct iso_args ia;
		struct mfs_args ma;
	} args;
E 29
E 21
D 20
	struct al_mnt *al_mp;
	char *cp, savedc;
E 20
I 20
	u_long net;
E 20

D 29
	args.fspec = 0;
	args.exflags = exflags;
	args.anon = *anoncrp;
E 29
I 29
	args.ua.fspec = 0;
	args.ua.export.ex_flags = exflags;
	args.ua.export.ex_anon = *anoncrp;
E 29
I 25
D 40
	bzero((char *)&sin, sizeof(sin));
	bzero((char *)&imask, sizeof(imask));
E 40
I 40
	memset(&sin, 0, sizeof(sin));
	memset(&imask, 0, sizeof(imask));
E 40
E 25
	sin.sin_family = AF_INET;
D 25
	sin.sin_port = 0;
E 25
	sin.sin_len = sizeof(sin);
D 20
	if (grp->type == MNT_HOST)
E 20
I 20
	imask.sin_family = AF_INET;
D 25
	imask.sin_port = 0;
E 25
	imask.sin_len = sizeof(sin);
	if (grp->gr_type == GT_HOST)
E 20
		addrp = (u_long **)grp->gr_ptr.gt_hostent->h_addr_list;
I 20
	else
D 34
		addrp = (u_long **)0;
E 34
I 34
		addrp = (u_long **)NULL;
E 34
E 20
	done = FALSE;
D 20
	while(!done) {
		if (grp->type == MNT_HOST) {
D 18
			if (!strcmp(grp->gr_ptr.gt_hostent->h_name, DEF_NAME))
				sin.sin_addr.s_addr = INADDR_ANY;
			else
E 18
I 18
			if (grp->gr_ptr.gt_hostent->h_name)
E 20
I 20
	while (!done) {
		switch (grp->gr_type) {
		case GT_HOST:
D 28
			if (addrp)
E 28
I 28
			if (addrp) {
E 28
E 20
E 18
				sin.sin_addr.s_addr = **addrp;
I 18
D 28
			else
				sin.sin_addr.s_addr = INADDR_ANY;
E 28
I 28
D 29
				args.slen = sizeof(sin);
E 29
I 29
				args.ua.export.ex_addrlen = sizeof(sin);
E 29
			} else
D 29
				args.slen = 0;
E 28
E 18
			args.saddr = (struct sockaddr *)&sin;
D 28
			args.slen = sizeof(sin);
E 28
I 20
			args.msklen = 0;
E 29
I 29
				args.ua.export.ex_addrlen = 0;
			args.ua.export.ex_addr = (struct sockaddr *)&sin;
			args.ua.export.ex_masklen = 0;
E 29
			break;
		case GT_NET:
			if (grp->gr_ptr.gt_net.nt_mask)
			    imask.sin_addr.s_addr = grp->gr_ptr.gt_net.nt_mask;
			else {
			    net = ntohl(grp->gr_ptr.gt_net.nt_net);
			    if (IN_CLASSA(net))
				imask.sin_addr.s_addr = inet_addr("255.0.0.0");
			    else if (IN_CLASSB(net))
				imask.sin_addr.s_addr =
				    inet_addr("255.255.0.0");
			    else
				imask.sin_addr.s_addr =
				    inet_addr("255.255.255.0");
			    grp->gr_ptr.gt_net.nt_mask = imask.sin_addr.s_addr;
			}
			sin.sin_addr.s_addr = grp->gr_ptr.gt_net.nt_net;
D 29
			args.saddr = (struct sockaddr *)&sin;
			args.slen = sizeof (sin);
			args.smask = (struct sockaddr *)&imask;
			args.msklen = sizeof (imask);
E 29
I 29
			args.ua.export.ex_addr = (struct sockaddr *)&sin;
			args.ua.export.ex_addrlen = sizeof (sin);
			args.ua.export.ex_mask = (struct sockaddr *)&imask;
			args.ua.export.ex_masklen = sizeof (imask);
E 29
			break;
E 20
#ifdef ISO
D 20
		} else if (grp->type == MNT_ISO) {
E 20
I 20
		case GT_ISO:
E 20
D 29
			args.saddr = (struct sockaddr *)grp->gr_ptr.gt_isoaddr;
			args.slen = sizeof (struct sockaddr_iso);
I 20
			args.msklen = 0;
E 29
I 29
			args.ua.export.ex_addr =
				(struct sockaddr *)grp->gr_ptr.gt_isoaddr;
			args.ua.export.ex_addrlen =
				sizeof(struct sockaddr_iso);
			args.ua.export.ex_masklen = 0;
E 29
			break;
E 20
#endif	/* ISO */
D 20
		} else {
E 20
I 20
		default:
E 20
			syslog(LOG_ERR, "Bad grouptype");
D 20
			free_exp(ep);
			return (FALSE);
		}
		if (statfs(ep->ex_dirp, &stfsbuf) < 0) {
			if (debug) {
				fprintf(stderr,"statfs failed.\n");
			}
			syslog(LOG_ERR, "Invalid path: %s", ep->ex_dirp);
			free_exp(ep);
			return(FALSE);
		}
		found = FALSE;
		for (al_mp = al_head; al_mp && !found; al_mp = al_mp->al_next)
			if (al_mp->al_mnted.val[0] == stfsbuf.f_fsid.val[0] &&
			    al_mp->al_mnted.val[1] == stfsbuf.f_fsid.val[1])
				found = TRUE;
		if (!found) {
			/* first time for fs, so must send a MNT_DELEXPORT
E 20
I 20
			if (cp)
				*cp = savedc;
			return (1);
		};
D 21
		if ((ep->ex_flag & EX_DONEDEL) == 0) {
			/*
			 * first time for fs, so must send a MNT_DELEXPORT
E 20
			 * to clear the old export list held in the kernel
			 * for this fs.
			 */
D 20
			al_mp = (struct al_mnt *)malloc(sizeof (struct al_mnt));
			al_mp->al_mnted = stfsbuf.f_fsid;
			al_mp->al_next = al_head;
			al_head = al_mp;
E 20
			targs.fspec = 0;
			targs.exflags = MNT_DELEXPORT;
E 16
D 20
			cp = (char *)0;
D 13
			while (mount(MOUNT_UFS, ep->ex_dirp, MNT_UPDATE, &args) < 0) {
E 13
I 13
D 16
			while (statfs(ep->ex_dirp, &stfsbuf) < 0 ||
			       mount(MOUNT_UFS, ep->ex_dirp,
				     stfsbuf.f_flags|MNT_UPDATE, &args) < 0) {
E 16
I 16
			while (mount(MOUNT_UFS, ep->ex_dirp,
			       stfsbuf.f_flags | MNT_UPDATE, &targs) < 0) {
				if (debug) {
E 20
I 20
			while (mount(MOUNT_UFS, dirp,
			       fsb->f_flags | MNT_UPDATE, &targs) < 0) {
				if (debug)
E 20
					fprintf(stderr,
					    "tried [%s][%d]\n",
D 20
					    ep->ex_dirp,errno);
				}
E 16
E 13
				if (cp == NULL)
					cp = ep->ex_dirp + dirplen - 1;
E 20
I 20
					    dirp,errno);
				if (cp)
					*cp-- = savedc;
E 20
				else
D 20
					*cp = savedc;
I 16
				cp--;
E 20
I 20
					cp = dirp + dirplen - 1;
				if (opt_flags & OP_ALLDIRS) {
					syslog(LOG_ERR, "Not root dir");
					return (1);
				}
E 20
E 16
				/* back up over the last component */
D 20
				while (*cp == '/' && cp > ep->ex_dirp)
E 20
I 20
				while (*cp == '/' && cp > dirp)
E 20
					cp--;
D 20
				while (*(cp - 1) != '/' && cp > ep->ex_dirp)
E 20
I 20
				while (*(cp - 1) != '/' && cp > dirp)
E 20
					cp--;
D 20
				if (cp == ep->ex_dirp) {
D 16
					syslog(LOG_WARNING,
					      "Can't export %s", ep->ex_dirp);
E 16
I 16
					if (debug) {
E 20
I 20
				if (cp == dirp) {
					if (debug)
E 20
						fprintf(stderr,"mnt unsucc\n");
D 20
					}
E 20
					syslog(LOG_ERR,
D 20
					    "Can't export %s", ep->ex_dirp);
E 16
					free_exp(ep);
D 16
					goto nextline;
E 16
I 16
					return(FALSE);
E 20
I 20
					    "Can't export %s", dirp);
					return (1);
E 20
E 16
				}
				savedc = *cp;
				*cp = '\0';
			}
D 16
			if (cp)
E 16
I 16
D 20
			if (cp != NULL) {
E 16
				*cp = savedc;
E 9
D 16
			ep->ex_rootuid = rootuid;
			ep->ex_exflags = exflags;
D 9
			ep->ex_next = exphead.ex_next;
			ep->ex_prev = &exphead;
			if (ep->ex_next != NULL)
				ep->ex_next->ex_prev = ep;
			exphead.ex_next = ep;
E 9
I 9
		} else {
			ep->ex_rootuid = fep->ex_rootuid;
			ep->ex_exflags = fep->ex_exflags;
E 16
I 16
			}
E 20
I 20
			ep->ex_flag |= EX_DONEDEL;
E 20
E 16
E 9
		}
I 9
D 16
		ep->ex_dev = sb.st_dev;
		ep->ex_next = exphead.ex_next;
		ep->ex_prev = &exphead;
		if (ep->ex_next != NULL)
			ep->ex_next->ex_prev = ep;
		exphead.ex_next = ep;
nextline:
		;
E 16
I 16
D 20
		cp = (char *)0;
		while (mount(MOUNT_UFS, ep->ex_dirp,
		       stfsbuf.f_flags | MNT_UPDATE, &args) < 0) {
E 20
I 20
		while (mount(MOUNT_UFS, dirp,
		       fsb->f_flags | MNT_UPDATE, &args) < 0) {
E 21
I 21

		/*
		 * XXX:
		 * Maybe I should just use the fsb->f_mntonname path instead
		 * of looping back up the dirp to the mount point??
		 * Also, needs to know how to export all types of local
D 38
		 * exportable file systems and not just MOUNT_UFS.
E 38
I 38
		 * exportable file systems and not just "ufs".
E 38
		 */
D 38
		while (mount(fsb->f_type, dirp,
E 38
I 38
		while (mount(fsb->f_fstypename, dirp,
E 38
		       fsb->f_flags | MNT_UPDATE, (caddr_t)&args) < 0) {
E 21
			if (cp)
				*cp-- = savedc;
			else
				cp = dirp + dirplen - 1;
E 20
			if (errno == EPERM) {
				syslog(LOG_ERR,
D 20
				     "Can't change attributes for %s.\n",
				     ep->ex_dirp);
				if (cp != NULL)
					*cp = savedc;
				break;
E 20
I 20
				   "Can't change attributes for %s.\n", dirp);
				return (1);
E 20
			}
D 20
			if (cp == NULL)
				cp = ep->ex_dirp + dirplen - 1;
			else
				*cp = savedc;
			cp--;
E 20
I 20
			if (opt_flags & OP_ALLDIRS) {
D 41
				syslog(LOG_ERR, "Not root dir");
E 41
I 41
				syslog(LOG_ERR, "Could not remount %s: %m",
					dirp);
E 41
				return (1);
			}
E 20
			/* back up over the last component */
D 20
			while (*cp == '/' && cp > ep->ex_dirp)
E 20
I 20
			while (*cp == '/' && cp > dirp)
E 20
				cp--;
D 20
			while (*(cp - 1) != '/' && cp > ep->ex_dirp)
E 20
I 20
			while (*(cp - 1) != '/' && cp > dirp)
E 20
				cp--;
D 20
			if (cp == ep->ex_dirp) {
				if (debug) {
E 20
I 20
			if (cp == dirp) {
				if (debug)
E 20
					fprintf(stderr,"mnt unsucc\n");
D 20
				}
				syslog(LOG_ERR, "Can't export %s", ep->ex_dirp);
				free_exp(ep);
				return(FALSE);
E 20
I 20
				syslog(LOG_ERR, "Can't export %s", dirp);
				return (1);
E 20
			}
			savedc = *cp;
			*cp = '\0';
		}
D 20
		if (addrp == NULL)
			done = TRUE;
		else {
E 20
I 20
		if (addrp) {
E 20
			++addrp;
D 20
			if (*addrp == NULL)
E 20
I 20
D 34
			if (*addrp == (u_long *)0)
E 34
I 34
			if (*addrp == (u_long *)NULL)
E 34
E 20
				done = TRUE;
D 20
		}
		if (cp != NULL)
			*cp = savedc;
E 20
I 20
		} else
			done = TRUE;
E 20
E 16
E 9
	}
D 16
	fclose(inf);
	return;
err:
D 2
	syslog(LOG_ERR, "Bad /etc/exports, mountd Failed");
E 2
I 2
D 14
	syslog(LOG_ERR, "Bad Exports File, mountd Failed");
E 14
I 14
	syslog(LOG_ERR, "No more memory: mountd Failed");
E 14
E 2
	exit(2);
E 16
I 16
D 20
	return(TRUE);
E 20
I 20
	if (cp)
		*cp = savedc;
	return (0);
E 20
E 16
}

I 20
/*
 * Translate a net address.
 */
I 34
int
E 34
get_net(cp, net, maskflg)
	char *cp;
	struct netmsk *net;
	int maskflg;
{
D 34
	register struct netent *np;
	register long netaddr;
E 34
I 34
	struct netent *np;
	long netaddr;
E 34
	struct in_addr inetaddr, inetaddr2;
	char *name;
E 20
I 16

I 20
	if (np = getnetbyname(cp))
		inetaddr = inet_makeaddr(np->n_net, 0);
	else if (isdigit(*cp)) {
		if ((netaddr = inet_network(cp)) == -1)
			return (1);
		inetaddr = inet_makeaddr(netaddr, 0);
		/*
		 * Due to arbritrary subnet masks, you don't know how many
		 * bits to shift the address to make it into a network,
		 * however you do know how to make a network address into
		 * a host with host == 0 and then compare them.
		 * (What a pest)
		 */
		if (!maskflg) {
			setnetent(0);
			while (np = getnetent()) {
				inetaddr2 = inet_makeaddr(np->n_net, 0);
				if (inetaddr2.s_addr == inetaddr.s_addr)
					break;
			}
			endnetent();
		}
	} else
		return (1);
	if (maskflg)
		net->nt_mask = inetaddr.s_addr;
	else {
		if (np)
			name = np->n_name;
		else
			name = inet_ntoa(inetaddr);
		net->nt_name = (char *)malloc(strlen(name) + 1);
D 34
		if (net->nt_name == (char *)0)
E 34
I 34
		if (net->nt_name == (char *)NULL)
E 34
			out_of_mem();
		strcpy(net->nt_name, name);
		net->nt_net = inetaddr.s_addr;
	}
	return (0);
}

E 20
E 16
/*
 * Parse out the next white space separated field
 */
I 16
void
E 16
nextfield(cp, endcp)
	char **cp;
	char **endcp;
{
D 34
	register char *p;
E 34
I 34
	char *p;
E 34

	p = *cp;
	while (*p == ' ' || *p == '\t')
		p++;
D 20
	if (*p == '\n' || *p == '\0') {
E 20
I 20
	if (*p == '\n' || *p == '\0')
E 20
		*cp = *endcp = p;
D 20
		return;
E 20
I 20
	else {
		*cp = p++;
		while (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
			p++;
		*endcp = p;
E 20
	}
D 20
	*cp = p++;
	while (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
		p++;
	*endcp = p;
E 20
I 2
}

/*
D 9
 * Search the remote mounts file for a match.
 * Iff found
 *	- set file offset to record and return TRUE
 * else
 *	- set file offset to an unused record if found or eof otherwise
 *	  and return FALSE
E 9
I 9
D 20
 * Parse the option string
E 20
I 20
 * Get an exports file line. Skip over blank lines and handle line
 * continuations.
E 20
E 9
 */
I 34
int
E 34
D 9
fnd_mnt(host, dirp)
	char *host;
	char *dirp;
E 9
I 9
D 16
do_opt(cpopt, fep, ep, exflagsp, rootuidp)
E 16
I 16
D 20
void
do_opt(cpopt, ep, exflagsp, cr)
E 16
	register char *cpopt;
D 16
	struct exportlist *fep, *ep;
	int *exflagsp, *rootuidp;
E 16
I 16
	struct exportlist *ep;
	int *exflagsp;
	struct ucred *cr;
E 20
I 20
get_line()
E 20
E 16
E 9
{
D 9
	struct mountlist ml;
	off_t off, pos;
E 9
I 9
D 20
	register char *cpoptarg, *cpoptend;
I 16
D 18
	int allflag;
E 18
I 18
	int allflag = 1;
E 20
I 20
D 34
	register char *p, *cp;
	register int len;
E 34
I 34
	char *p, *cp;
	int len;
E 34
	int totlen, cont_line;
E 20
E 18
E 16
E 9

D 9
	off = -1;
	pos = 0;
	lseek(mlfile, (off_t)0, L_SET);
	while (read(mlfile, (caddr_t)&ml, sizeof(ml)) == sizeof(ml)) {
		if (!strcmp(host, ml.ml_host) && !strcmp(dirp, ml.ml_dirp)) {
			lseek(mlfile, (off_t)-sizeof(ml), L_INCR);
			return (TRUE);
		} else if (ml.ml_host[0] == '\0') {
			off = pos;
E 9
I 9
D 20
	while (cpopt && *cpopt) {
		if (cpoptend = index(cpopt, ','))
			*cpoptend++ = '\0';
		if (cpoptarg = index(cpopt, '='))
			*cpoptarg++ = '\0';
		if (!strcmp(cpopt, "ro") || !strcmp(cpopt, "o")) {
D 16
			if (fep && (fep->ex_exflags & MNT_EXRDONLY) == 0)
				syslog(LOG_WARNING, "ro failed for %s",
				       ep->ex_dirp);
			else
				*exflagsp |= MNT_EXRDONLY;
		} else if (!strcmp(cpopt, "root") || !strcmp(cpopt, "r")) {
			if (cpoptarg && isdigit(*cpoptarg)) {
				*rootuidp = atoi(cpoptarg);
				if (fep && fep->ex_rootuid != *rootuidp)
					syslog(LOG_WARNING,
					       "uid failed for %s",
					       ep->ex_dirp);
			} else
				syslog(LOG_WARNING,
				       "uid failed for %s",
				       ep->ex_dirp);
E 16
I 16
			*exflagsp |= MNT_EXRDONLY;
		} else if ((!strcmp(cpopt, "root") || !strcmp(cpopt, "r") ||
D 19
		    !(allflag = strcmp(cpopt, "allanon"))) && cpoptarg) {
E 19
I 19
		    !(allflag = strcmp(cpopt, "all"))) && cpoptarg) {
E 19
			parsecred(cpoptarg, cr);
			if (allflag == 0)
				*exflagsp |= MNT_EXPORTANON;
		} else if (!strcmp(cpopt, "kerb") || !strcmp(cpopt, "k")) {
			*exflagsp |= MNT_EXKERB;
E 16
		} else
D 16
			syslog(LOG_WARNING, "opt %s ignored for %s", cpopt,
E 16
I 16
			syslog(LOG_ERR, "opt %s ignored for %s", cpopt,
E 16
			       ep->ex_dirp);
		cpopt = cpoptend;
	}
E 20
I 20
	/*
	 * Loop around ignoring blank lines and getting all continuation lines.
	 */
	p = line;
	totlen = 0;
	do {
		if (fgets(p, LINESIZ - totlen, exp_file) == NULL)
			return (0);
		len = strlen(p);
		cp = p + len - 1;
		cont_line = 0;
		while (cp >= p &&
		    (*cp == ' ' || *cp == '\t' || *cp == '\n' || *cp == '\\')) {
			if (*cp == '\\')
				cont_line = 1;
			cp--;
			len--;
		}
		*++cp = '\0';
		if (len > 0) {
			totlen += len;
			if (totlen >= LINESIZ) {
				syslog(LOG_ERR, "Exports line too long");
				exit(2);
			}
			p = cp;
		}
	} while (totlen == 0 || cont_line);
	return (1);
E 20
}

I 16
/*
 * Parse a description of a credential.
 */
I 34
void
E 34
parsecred(namelist, cr)
	char *namelist;
D 34
	register struct ucred *cr;
E 34
I 34
	struct ucred *cr;
E 34
{
D 34
	register char *name;
	register int cnt;
E 34
I 34
	char *name;
	int cnt;
E 34
	char *names;
	struct passwd *pw;
	struct group *gr;
	int ngroups, groups[NGROUPS + 1];

	/*
	 * Set up the unpriviledged user.
	 */
	cr->cr_ref = 1;
	cr->cr_uid = -2;
	cr->cr_groups[0] = -2;
	cr->cr_ngroups = 1;
	/*
	 * Get the user's password table entry.
	 */
	names = strsep(&namelist, " \t\n");
	name = strsep(&names, ":");
	if (isdigit(*name) || *name == '-')
		pw = getpwuid(atoi(name));
	else
		pw = getpwnam(name);
	/*
	 * Credentials specified as those of a user.
	 */
	if (names == NULL) {
		if (pw == NULL) {
D 34
			syslog(LOG_ERR, "Unknown user: %s\n", name);
E 34
I 34
			syslog(LOG_ERR, "Unknown user: %s", name);
E 34
			return;
		}
		cr->cr_uid = pw->pw_uid;
		ngroups = NGROUPS + 1;
		if (getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups))
D 34
			syslog(LOG_ERR, "Too many groups\n");
E 34
I 34
			syslog(LOG_ERR, "Too many groups");
E 34
		/*
		 * Convert from int's to gid_t's and compress out duplicate
		 */
		cr->cr_ngroups = ngroups - 1;
		cr->cr_groups[0] = groups[0];
		for (cnt = 2; cnt < ngroups; cnt++)
			cr->cr_groups[cnt - 1] = groups[cnt];
		return;
	}
	/*
	 * Explicit credential specified as a colon separated list:
	 *	uid:gid:gid:...
	 */
	if (pw != NULL)
		cr->cr_uid = pw->pw_uid;
	else if (isdigit(*name) || *name == '-')
		cr->cr_uid = atoi(name);
	else {
D 34
		syslog(LOG_ERR, "Unknown user: %s\n", name);
E 34
I 34
		syslog(LOG_ERR, "Unknown user: %s", name);
E 34
		return;
	}
	cr->cr_ngroups = 0;
	while (names != NULL && *names != '\0' && cr->cr_ngroups < NGROUPS) {
		name = strsep(&names, ":");
		if (isdigit(*name) || *name == '-') {
			cr->cr_groups[cr->cr_ngroups++] = atoi(name);
		} else {
			if ((gr = getgrnam(name)) == NULL) {
D 34
				syslog(LOG_ERR, "Unknown group: %s\n", name);
E 34
I 34
				syslog(LOG_ERR, "Unknown group: %s", name);
E 34
				continue;
			}
			cr->cr_groups[cr->cr_ngroups++] = gr->gr_gid;
		}
	}
	if (names != NULL && *names != '\0' && cr->cr_ngroups == NGROUPS)
D 34
		syslog(LOG_ERR, "Too many groups\n");
E 34
I 34
		syslog(LOG_ERR, "Too many groups");
E 34
}

E 16
#define	STRSIZ	(RPCMNT_NAMELEN+RPCMNT_PATHLEN+50)
/*
 * Routines that maintain the remote mounttab
 */
D 16
void get_mountlist()
E 16
I 16
void
get_mountlist()
E 16
{
D 34
	register struct mountlist *mlp, **mlpp;
	register char *eos, *dirp;
E 34
I 34
	struct mountlist *mlp, **mlpp;
D 40
	char *eos, *dirp;
E 40
I 40
	char *host, *dirp, *cp;
E 40
E 34
	int len;
	char str[STRSIZ];
	FILE *mlfile;

D 11
	if ((mlfile = fopen(_PATH_RMOUNTLIST, "r")) == NULL) {
E 11
I 11
D 18
	if (((mlfile = fopen(_PATH_RMOUNTLIST, "r")) == NULL) &&
	    ((mlfile = fopen(_PATH_RMOUNTLIST, "w")) == NULL)) {
E 18
I 18
	if ((mlfile = fopen(_PATH_RMOUNTLIST, "r")) == NULL) {
E 18
E 11
D 16
		syslog(LOG_WARNING, "Can't open %s", _PATH_RMOUNTLIST);
E 16
I 16
		syslog(LOG_ERR, "Can't open %s", _PATH_RMOUNTLIST);
E 16
		return;
	}
	mlpp = &mlhead;
	while (fgets(str, STRSIZ, mlfile) != NULL) {
D 40
		if ((dirp = index(str, '\t')) == NULL &&
		    (dirp = index(str, ' ')) == NULL)
E 40
I 40
		cp = str;
		host = strsep(&cp, " \t\n");
		dirp = strsep(&cp, " \t\n");
		if (host == NULL || dirp == NULL)
E 40
			continue;
		mlp = (struct mountlist *)malloc(sizeof (*mlp));
D 40
		len = dirp-str;
		if (len > RPCMNT_NAMELEN)
			len = RPCMNT_NAMELEN;
		bcopy(str, mlp->ml_host, len);
		mlp->ml_host[len] = '\0';
		while (*dirp == '\t' || *dirp == ' ')
			dirp++;
		if ((eos = index(dirp, '\t')) == NULL &&
		    (eos = index(dirp, ' ')) == NULL &&
		    (eos = index(dirp, '\n')) == NULL)
			len = strlen(dirp);
		else
			len = eos-dirp;
		if (len > RPCMNT_PATHLEN)
			len = RPCMNT_PATHLEN;
		bcopy(dirp, mlp->ml_dirp, len);
		mlp->ml_dirp[len] = '\0';
E 40
I 40
		strncpy(mlp->ml_host, host, RPCMNT_NAMELEN);
		mlp->ml_host[RPCMNT_NAMELEN] = '\0';
		strncpy(mlp->ml_dirp, dirp, RPCMNT_PATHLEN);
		mlp->ml_dirp[RPCMNT_PATHLEN] = '\0';
E 40
D 34
		mlp->ml_next = (struct mountlist *)0;
E 34
I 34
		mlp->ml_next = (struct mountlist *)NULL;
E 34
		*mlpp = mlp;
		mlpp = &mlp->ml_next;
	}
	fclose(mlfile);
}

D 16
void del_mlist(hostp, dirp)
E 16
I 16
void
del_mlist(hostp, dirp)
E 16
D 34
	register char *hostp, *dirp;
E 34
I 34
	char *hostp, *dirp;
E 34
{
D 34
	register struct mountlist *mlp, **mlpp;
E 34
I 34
	struct mountlist *mlp, **mlpp;
E 34
I 18
	struct mountlist *mlp2;
E 18
	FILE *mlfile;
	int fnd = 0;

	mlpp = &mlhead;
	mlp = mlhead;
	while (mlp) {
		if (!strcmp(mlp->ml_host, hostp) &&
		    (!dirp || !strcmp(mlp->ml_dirp, dirp))) {
			fnd = 1;
D 18
			*mlpp = mlp->ml_next;
			free((caddr_t)mlp);
E 18
I 18
			mlp2 = mlp;
			*mlpp = mlp = mlp->ml_next;
			free((caddr_t)mlp2);
		} else {
			mlpp = &mlp->ml_next;
			mlp = mlp->ml_next;
E 18
E 9
		}
D 9
		pos += sizeof(ml);
E 9
I 9
D 18
		mlpp = &mlp->ml_next;
		mlp = mlp->ml_next;
E 18
E 9
	}
D 9
	if (off != -1)
		lseek(mlfile, off, L_SET);
	else
		lseek(mlfile, (off_t)0, L_XTND);
	return (FALSE);
E 9
I 9
	if (fnd) {
		if ((mlfile = fopen(_PATH_RMOUNTLIST, "w")) == NULL) {
D 16
			syslog(LOG_WARNING, "Can't update %s", _PATH_RMOUNTLIST);
E 16
I 16
D 20
			syslog(LOG_WARNING,"Can't update %s", _PATH_RMOUNTLIST);
E 20
I 20
			syslog(LOG_ERR,"Can't update %s", _PATH_RMOUNTLIST);
E 20
E 16
			return;
		}
		mlp = mlhead;
		while (mlp) {
			fprintf(mlfile, "%s %s\n", mlp->ml_host, mlp->ml_dirp);
			mlp = mlp->ml_next;
		}
		fclose(mlfile);
	}
}

D 16
void add_mlist(hostp, dirp)
E 16
I 16
void
add_mlist(hostp, dirp)
E 16
D 34
	register char *hostp, *dirp;
E 34
I 34
	char *hostp, *dirp;
E 34
{
D 34
	register struct mountlist *mlp, **mlpp;
E 34
I 34
	struct mountlist *mlp, **mlpp;
E 34
	FILE *mlfile;

	mlpp = &mlhead;
	mlp = mlhead;
	while (mlp) {
		if (!strcmp(mlp->ml_host, hostp) && !strcmp(mlp->ml_dirp, dirp))
			return;
		mlpp = &mlp->ml_next;
		mlp = mlp->ml_next;
	}
	mlp = (struct mountlist *)malloc(sizeof (*mlp));
	strncpy(mlp->ml_host, hostp, RPCMNT_NAMELEN);
	mlp->ml_host[RPCMNT_NAMELEN] = '\0';
	strncpy(mlp->ml_dirp, dirp, RPCMNT_PATHLEN);
	mlp->ml_dirp[RPCMNT_PATHLEN] = '\0';
D 34
	mlp->ml_next = (struct mountlist *)0;
E 34
I 34
	mlp->ml_next = (struct mountlist *)NULL;
E 34
	*mlpp = mlp;
	if ((mlfile = fopen(_PATH_RMOUNTLIST, "a")) == NULL) {
D 20
		syslog(LOG_WARNING, "Can't update %s", _PATH_RMOUNTLIST);
E 20
I 20
		syslog(LOG_ERR, "Can't update %s", _PATH_RMOUNTLIST);
E 20
		return;
	}
	fprintf(mlfile, "%s %s\n", mlp->ml_host, mlp->ml_dirp);
	fclose(mlfile);
}

/*
 * This function is called via. SIGTERM when the system is going down.
 * It sends a broadcast RPCMNT_UMNTALL.
 */
I 15
void
E 15
send_umntall()
{
	(void) clnt_broadcast(RPCPROG_MNT, RPCMNT_VER1, RPCMNT_UMNTALL,
		xdr_void, (caddr_t)0, xdr_void, (caddr_t)0, umntall_each);
D 16
	exit();
E 16
I 16
	exit(0);
E 16
}

I 34
int
E 34
umntall_each(resultsp, raddr)
	caddr_t resultsp;
	struct sockaddr_in *raddr;
{
	return (1);
}

/*
D 20
 * Free up an exports list component
 */
I 16
void
E 16
free_exp(ep)
	register struct exportlist *ep;
{
	register struct grouplist *grp;
D 16
	register char **addrp;
E 16
	struct grouplist *grp2;

	grp = ep->ex_groups;
	while (grp != NULL) {
D 16
		addrp = grp->gr_hp->h_addr_list;
		while (*addrp)
			free(*addrp++);
		free((caddr_t)grp->gr_hp->h_addr_list);
		free(grp->gr_hp->h_name);
		free((caddr_t)grp->gr_hp);
E 16
		grp2 = grp;
		grp = grp->gr_next;
D 16
		free((caddr_t)grp2);
E 16
I 16
		free_grp(grp2);
E 16
	}
	free((caddr_t)ep);
I 16
}

/*
E 20
 * Free up a group list.
 */
void
free_grp(grp)
D 34
	register struct grouplist *grp;
E 34
I 34
	struct grouplist *grp;
E 34
{
D 34
	register char **addrp;
E 34
I 34
	char **addrp;
E 34

D 20
	if (grp->type == MNT_HOST) {
E 20
I 20
	if (grp->gr_type == GT_HOST) {
E 20
D 18
		addrp = grp->gr_ptr.gt_hostent->h_addr_list;
		while (addrp && *addrp)
			free(*addrp++);
		free((caddr_t)grp->gr_ptr.gt_hostent->h_addr_list);
		free(grp->gr_ptr.gt_hostent->h_name);
E 18
I 18
		if (grp->gr_ptr.gt_hostent->h_name) {
			addrp = grp->gr_ptr.gt_hostent->h_addr_list;
			while (addrp && *addrp)
				free(*addrp++);
			free((caddr_t)grp->gr_ptr.gt_hostent->h_addr_list);
			free(grp->gr_ptr.gt_hostent->h_name);
		}
E 18
		free((caddr_t)grp->gr_ptr.gt_hostent);
I 20
	} else if (grp->gr_type == GT_NET) {
		if (grp->gr_ptr.gt_net.nt_name)
			free(grp->gr_ptr.gt_net.nt_name);
E 20
	}
#ifdef ISO
D 20
	else if (grp->type == MNT_ISO)
E 20
I 20
	else if (grp->gr_type == GT_ISO)
E 20
		free((caddr_t)grp->gr_ptr.gt_isoaddr);
#endif
	free((caddr_t)grp);
D 33
}

D 20
void
get_group(line, ep)
	char *line;
	struct export_list *ep;
{
	int done;
	struct grouplist *grp;
	struct groupnames *t_gn;
	char *cp, *endcp, savedc;

	cp = line;
	nextfield(&cp, &endcp);
	savedc = *endcp;
	*endcp = NULL;
	if (*(endcp-1) == '=') {
		*(endcp-1) = NULL;
	}
	/* check to see if this group exists already */
	t_gn = grpnames;
	while(t_gn != NULL) {
		if (strcmp(t_gn->gn_name,cp) == 0) {
			syslog(LOG_ERR,"Group redifined, second ignored.");
			return;
		}
		t_gn = t_gn->gn_next;
	}

	/* make a new group list entry */
	t_gn = (struct groupnames *)malloc(sizeof(struct groupnames));
	if (t_gn == NULL) {
		syslog(LOG_ERR,"Group: Couldn't Malloc.");
		exit(2);
	}
	strcpy(t_gn->gn_name,cp);
	t_gn->gn_next = grpnames;
	grpnames = t_gn;
	t_gn->gn_glist = NULL;
	*endcp = savedc;
	cp = endcp;
	done = FALSE;
	while(!done) {
		nextfield(&cp, &endcp);
		if (cp == endcp)
			done = TRUE;
		else {
			savedc = *endcp;
			*endcp = NULL;
			if (strcmp(cp, "=")) {
				/* add to group list */
				get_host(cp, endcp, ep, &grp);
				if (grp != NULL) {
					grp->gr_next = t_gn->gn_glist;
					t_gn->gn_glist = grp;
				}
			}
			*endcp = savedc;
			cp = endcp;
		}
	}
}

void
get_host(cp, endcp, ep, gp)
	char *cp, *endcp;
	struct exportlist *ep;
	struct grouplist **gp;
{
	register struct hostent *hp, *nhp;
	register struct grouplist *grp;
	register char **addrp, **naddrp;
	struct hostent t_host;
	int i;
	u_long saddr;
	char *aptr[2];
#ifdef ISO
	struct iso_addr *isop;
	struct sockaddr_iso *isoaddr;
#endif

	if (isdigit(*cp)) {
		saddr = inet_addr(cp);
		if (saddr == -1) {
			syslog(LOG_ERR,
			    "Bad Exports File, %s: %s", cp,
			    "inet_addr failed, ignored");
			*gp = NULL;
			return;
		}
		hp = &t_host;
		hp->h_name = cp;
		hp->h_addrtype = AF_INET;
		hp->h_length = sizeof (u_long);
		hp->h_addr_list = aptr;
		aptr[0] = (char *)&saddr;
		aptr[1] = (char *)0;
#ifdef ISO
	} else if (!strncmp(cp, "iso=", 4)) {
		if ((isop = iso_addr(cp + 4)) == NULL) {
			syslog(LOG_ERR,
			    "Bad Exports File, %s: %s", cp,
			    "iso_addr failed, ignored");
			*gp = NULL;
			return;
		}
		isoaddr = (struct sockaddr_iso *)
		    malloc(sizeof (struct sockaddr_iso));
		if (isoaddr == NULL)
			goto err1;
		bzero((caddr_t)isoaddr, sizeof (struct sockaddr_iso));
		bcopy((caddr_t)isop, (caddr_t)isoaddr->siso_addr,
			sizeof (struct iso_addr));
		isoaddr->siso_len = sizeof (struct sockaddr_iso);
		isoaddr->siso_family = AF_ISO;
		grp = (struct grouplist *)
			malloc(sizeof(struct grouplist));
		if (grp == NULL)
			goto err1;
		grp->type = MNT_ISO;
		grp->gr_ptr.gt_isoaddr = isoaddr;
		*gp = grp;
		return;
#endif	/* ISO */
	} else if ((hp = gethostbyname(cp)) == NULL) {
		syslog(LOG_ERR, "Bad Exports File, %s: %s",
		    cp, "Gethostbyname failed, ignored");
		*gp = NULL;
		return;
	}
	grp = (struct grouplist *)
		malloc(sizeof(struct grouplist));
	if (grp == NULL)
		goto err1;
	grp->type = MNT_HOST;
	nhp = grp->gr_ptr.gt_hostent = (struct hostent *)
		malloc(sizeof(struct hostent));
	if (nhp == NULL)
		goto err1;
	bcopy((caddr_t)hp, (caddr_t)nhp,
		sizeof(struct hostent));
	i = strlen(hp->h_name)+1;
	nhp->h_name = (char *)malloc(i);
	if (nhp->h_name == NULL)
		goto err1;
	bcopy(hp->h_name, nhp->h_name, i);
	addrp = hp->h_addr_list;
	i = 1;
	while (*addrp++)
		i++;
	naddrp = nhp->h_addr_list = (char **)
		malloc(i*sizeof(char *));
	if (naddrp == NULL)
		goto err1;
	addrp = hp->h_addr_list;
	while (*addrp) {
		*naddrp = (char *)
		    malloc(hp->h_length);
		if (*naddrp == NULL)
		    goto err1;
		bcopy(*addrp, *naddrp,
			hp->h_length);
		addrp++;
		naddrp++;
	}
	*naddrp = (char *)0;
	*gp = grp;
	return;
err1:
	syslog(LOG_ERR, "No more memory: mountd Failed");
	exit(2);
}

void
do_group(cp, endcp, gp)
	char *cp, *endcp;
	struct grouplist **gp;
{
	int found;
	struct groupnames *t_gn;

	t_gn = grpnames;
	found = FALSE;
	while((t_gn != NULL) && !found) {
		if(strcmp(t_gn->gn_name,cp) == 0) {
			found = TRUE;
			*gp = (struct grouplist *)
			    malloc(sizeof(struct grouplist));
			if (*gp == NULL) {
				syslog(LOG_ERR,"No more memory: mountd Failed");
				exit(2);
			}
			(*gp)->gr_ptr.gt_grpname = (struct groupnames *)
			    malloc(sizeof(struct groupnames));
			if ((*gp)->gr_ptr.gt_grpname == NULL) {
				syslog(LOG_ERR,"No more memory: mountd Failed");
				exit(2);
			}
			(*gp)->gr_ptr.gt_grpname->gn_glist = t_gn->gn_glist;
			return;
		}
		t_gn = t_gn->gn_next;
	}
	*gp = NULL;
}

E 20
/*
 * char *realpath(const char *path, char resolved_path[MAXPATHLEN])
 *
 * find the real name of path, by removing all ".", ".."
 * and symlink components.
 *
 * Jan-Simon Pendry, September 1991.
 */
char *
realpath(path, resolved)
	char *path;
	char resolved[MAXPATHLEN];
{
	int d = open(".", O_RDONLY);
	int rootd = 0;
	char *p, *q;
	struct stat stb;
	char wbuf[MAXPATHLEN];

	strcpy(resolved, path);

	if (d < 0)
		return 0;

loop:;
	q = strrchr(resolved, '/');
	if (q) {
		p = q + 1;
		if (q == resolved)
			q = "/";
		else {
			do
				--q;
			while (q > resolved && *q == '/');
			q[1] = '\0';
			q = resolved;
		}
		if (chdir(q) < 0)
			goto out;
	} else
		p = resolved;

	if (lstat(p, &stb) == 0) {
		if (S_ISLNK(stb.st_mode)) {
			int n = readlink(p, resolved, MAXPATHLEN);
			if (n < 0)
				goto out;
			resolved[n] = '\0';
			goto loop;
		}
		if (S_ISDIR(stb.st_mode)) {
			if (chdir(p) < 0)
				goto out;
			p = "";
		}
	}

	strcpy(wbuf, p);
	if (getcwd(resolved, MAXPATHLEN) == 0)
		goto out;
	if (resolved[0] == '/' && resolved[1] == '\0')
		rootd = 1;

	if (*wbuf) {
		if (strlen(resolved) + strlen(wbuf) + rootd + 1 > MAXPATHLEN) {
			errno = ENAMETOOLONG;
			goto out;
		}
		if (rootd == 0)
			strcat(resolved, "/");
		strcat(resolved, wbuf);
	}

	if (fchdir(d) < 0)
		goto out;
	(void) close(d);

	return resolved;

out:;
	(void) close(d);
	return 0;
E 33
E 16
E 9
E 2
}
I 17

#ifdef DEBUG
void
SYSLOG(int pri, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}
#endif /* DEBUG */
I 20

/*
 * Check options for consistency.
 */
I 34
int
E 34
check_options(dp)
	struct dirlist *dp;
{

D 34
	if (dp == (struct dirlist *)0)
E 34
I 34
	if (dp == (struct dirlist *)NULL)
E 34
	    return (1);
	if ((opt_flags & (OP_MAPROOT | OP_MAPALL)) == (OP_MAPROOT | OP_MAPALL) ||
	    (opt_flags & (OP_MAPROOT | OP_KERB)) == (OP_MAPROOT | OP_KERB) ||
	    (opt_flags & (OP_MAPALL | OP_KERB)) == (OP_MAPALL | OP_KERB)) {
	    syslog(LOG_ERR, "-mapall, -maproot and -kerb mutually exclusive");
	    return (1);
	}
	if ((opt_flags & OP_MASK) && (opt_flags & OP_NET) == 0) {
	    syslog(LOG_ERR, "-mask requires -net");
	    return (1);
	}
	if ((opt_flags & (OP_NET | OP_ISO)) == (OP_NET | OP_ISO)) {
	    syslog(LOG_ERR, "-net and -iso mutually exclusive");
	    return (1);
	}
	if ((opt_flags & OP_ALLDIRS) && dp->dp_left) {
	    syslog(LOG_ERR, "-alldir has multiple directories");
	    return (1);
	}
	return (0);
I 32
}

/*
 * Check an absolute directory path for any symbolic links. Return true
 * if no symbolic links are found.
 */
int
check_dirpath(dirp)
D 34
	register char *dirp;
E 34
I 34
	char *dirp;
E 34
{
D 34
	register char *cp;
E 34
I 34
	char *cp;
E 34
	int ret = 1;
	struct stat sb;

	cp = dirp + 1;
	while (*cp && ret) {
		if (*cp == '/') {
			*cp = '\0';
D 35
			if (lstat(dirp, &sb) < 0 ||
				(sb.st_mode & S_IFMT) != S_IFDIR)
E 35
I 35
			if (lstat(dirp, &sb) < 0 || !S_ISDIR(sb.st_mode))
E 35
				ret = 0;
			*cp = '/';
		}
		cp++;
	}
D 35
	if (lstat(dirp, &sb) < 0 ||
		(sb.st_mode & S_IFMT) != S_IFDIR)
E 35
I 35
	if (lstat(dirp, &sb) < 0 || !S_ISDIR(sb.st_mode))
E 35
		ret = 0;
	return (ret);
I 38
}

/*
 * Just translate an ascii string to an integer.
 */
int
get_num(cp)
	register char *cp;
{
	register int res = 0;

	while (*cp) {
		if (*cp < '0' || *cp > '9')
			return (-1);
		res = res * 10 + (*cp++ - '0');
	}
	return (res);
E 38
E 32
}
E 20
E 17
E 1
