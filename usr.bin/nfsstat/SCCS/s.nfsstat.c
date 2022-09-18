h62444
s 00103/00059/00275
d D 8.2 95/03/31 18:13:21 mckusick 17 16
c update for version 3 NFS from Rick Macklem
e
s 00005/00005/00329
d D 8.1 93/06/06 15:45:34 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00008/00317
d D 5.14 92/11/02 22:13:25 mckusick 15 14
c use new kvm library functions
e
s 00014/00008/00311
d D 5.13 92/01/27 12:17:49 bostic 14 13
c don't let users create their own symbol table for the running kernel
e
s 00000/00000/00319
d D 5.12 92/01/10 00:04:52 mckusick 13 11
i 12
c merge in 5.4.1.1 branch
e
s 00059/00037/00291
d D 5.4.1.1 92/01/09 23:57:49 mckusick 12 4
c update from Rick Macklem
e
s 00002/00002/00295
d D 5.11 92/01/09 19:02:30 marc 11 10
c formatting glitches in error messages
e
s 00012/00071/00285
d D 5.10 91/07/01 18:59:42 marc 10 9
c kvm
e
s 00016/00001/00340
d D 5.9 91/07/01 12:18:55 karels 9 8
c disable kflag for new vm
e
s 00068/00053/00273
d D 5.8 91/04/23 17:52:43 bostic 8 7
c consistency/cleanup/ANSI/lint pass -- add -M, -N
e
s 00069/00062/00257
d D 5.7 91/04/22 18:48:06 bostic 7 6
c interval should not be a positional parameter (neither should kernel
c or core, but that's another matter).  Use getopt, minor ANSI/cleanups
e
s 00002/00001/00317
d D 5.6 91/03/01 15:18:02 bostic 6 5
c ANSI
e
s 00001/00011/00317
d D 5.5 90/06/01 17:07:35 bostic 5 4
c new copyright notice
e
s 00020/00004/00308
d D 5.4 90/05/14 13:52:18 mckusick 4 3
c update from Rick Macklem for TCP based NFS
e
s 00003/00000/00309
d D 5.3 90/03/05 19:41:29 mckusick 3 2
c update for new statistics from Rick Macklem
e
s 00018/00003/00291
d D 5.2 90/01/04 15:13:20 mckusick 2 1
c update from Rick Macklem
e
s 00294/00000/00000
d D 5.1 89/07/16 15:53:56 mckusick 1 0
c initial version from Rick Macklem
e
u
U
f b 
t
T
I 1
/*
D 16
 * Copyright (c) 1983, 1989 Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1983, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
D 16
char copyright[] =
"%Z% Copyright (c) 1983, 1989 Regents of the University of California.\n\
 All rights reserved.\n";
E 16
I 16
static char copyright[] =
"%Z% Copyright (c) 1983, 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
I 9
D 17
#if BSD >= 199103
#define NEWVM
#endif
#ifndef NEWVM
E 9
#include <sys/vmmac.h>
D 7
#include <sys/file.h>
I 12
#include <sys/ucred.h>
E 12
E 7
#include <machine/pte.h>
D 9
#include <sys/namei.h>
E 9
I 9
#endif
E 17
E 9
#include <sys/mount.h>
D 17
#include <nfs/nfsv2.h>
E 17
I 17
#include <sys/sysctl.h>
#include <nfs/rpcv2.h>
#include <nfs/nfsproto.h>
E 17
#include <nfs/nfs.h>
I 7
#include <signal.h>
#include <fcntl.h>
E 7
#include <ctype.h>
#include <errno.h>
I 15
#include <kvm.h>
E 15
#include <nlist.h>
I 7
#include <unistd.h>
E 7
#include <stdio.h>
I 7
#include <stdlib.h>
#include <string.h>
E 7
#include <paths.h>
I 17
#include <err.h>
E 17

D 8
#define	YES	1
#define	NO	0

E 8
struct nlist nl[] = {
#define	N_NFSSTAT	0
	{ "_nfsstats" },
I 9
D 10
#ifndef NEWVM
E 9
#define	N_SYSMAP	1
	{ "_Sysmap" },
#define	N_SYSSIZE	2
	{ "_Syssize" },
I 9
#endif
E 10
E 9
	"",
};
I 15
kvm_t *kd;
E 15

I 9
D 10
#ifndef NEWVM
E 9
D 7
struct	pte *Sysmap;
E 7
I 7
struct pte *Sysmap;
I 9
#endif
E 10
I 10
D 14
char *kernel = NULL;
char *kmemf = NULL;
E 10
E 9
E 7

E 14
D 7
char	*system = _PATH_UNIX;
char	*kmemf = _PATH_KMEM;
int	kmem;
int	kflag;
int	interval;
E 7
I 7
D 10
int kflag, kmem;
char *kernel = _PATH_UNIX;
char *kmemf = _PATH_KMEM;
I 8

E 8
off_t klseek();
E 10
I 8
D 17
void intpr(), printhdr(), sidewaysintpr(), usage();
E 17
I 17
static int deadkernel = 0;
E 17
E 8
E 7

I 17
void intpr __P((void));
void printhdr __P((void));
void sidewaysintpr __P((u_int));
void usage __P((void));

E 17
D 7
extern	char *malloc();
extern	off_t lseek();

E 7
main(argc, argv)
	int argc;
D 7
	char *argv[];
E 7
I 7
	char **argv;
E 7
{
I 7
	extern int optind;
	extern char *optarg;
D 8
	unsigned int interval;
E 8
I 8
	u_int interval;
E 8
E 7
	int ch;
I 14
	char *memf, *nlistf;
I 15
	char errbuf[80];
E 15
E 14

	interval = 0;
I 14
	memf = nlistf = NULL;
E 14
D 7
	argc--;
	argv++;
	if (argc > 0) {
		interval = atoi(argv[0]);
		if (interval <= 0)
E 7
I 7
D 8
	while ((ch = getopt(argc, argv, "i:")) != EOF)
E 8
I 8
	while ((ch = getopt(argc, argv, "M:N:w:")) != EOF)
E 8
		switch(ch) {
D 8
		case 'i':
E 8
I 8
		case 'M':
D 14
			kmemf = optarg;
E 14
I 14
			memf = optarg;
E 14
D 10
			kflag = 1;
E 10
			break;
		case 'N':
D 14
			kernel = optarg;
E 14
I 14
			nlistf = optarg;
E 14
			break;
		case 'w':
E 8
			interval = atoi(optarg);
			break;
		case '?':
		default:
E 7
			usage();
D 7
		argv++, argc--;
		if (argc > 0) {
			system = *argv;
			argv++, argc--;
			if (argc > 0) {
				kmemf = *argv;
				kflag++;
			}
E 7
		}
I 7
	argc -= optind;
	argv += optind;

I 8
#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
E 8
	if (*argv) {
D 10
		kernel = *++argv;
E 10
I 10
		interval = atoi(*argv);
E 10
		if (*++argv) {
D 10
			kmemf = *argv;
			kflag = 1;
E 10
I 10
D 14
			kernel = *argv;
E 14
I 14
			nlistf = *argv;
E 14
			if (*++argv)
D 14
				kmemf = *argv;
E 14
I 14
				memf = *argv;
E 14
E 10
		}
E 7
	}
I 8
#endif
E 8
D 7
	if (nlist(system, nl) < 0 || nl[0].n_type == 0) {
		fprintf(stderr, "%s: no namelist\n", system);
E 7
I 7
D 10
	if (nlist(kernel, nl) < 0 || nl[0].n_type == 0) {
		(void)fprintf(stderr, "nfsstate: %s: no namelist\n", kernel);
E 10
I 10
D 14
	if (kvm_openfiles(kernel, kmemf, NULL) == -1) {
E 14
I 14
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
D 17
	if (nlistf != NULL || memf != NULL)
E 17
I 17
	if (nlistf != NULL || memf != NULL) {
E 17
		setgid(getgid());
I 17
		deadkernel = 1;
E 17

D 15
	if (kvm_openfiles(nlistf, memf, NULL) == -1) {
E 14
D 11
		fprintf(stderr, "nfsstate: kvm_openfiles: %s", kvm_geterr());
E 11
I 11
		fprintf(stderr, "nfsstate: kvm_openfiles: %s\n", kvm_geterr());
E 15
I 15
D 17
	if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf)) == 0) {
		fprintf(stderr, "nfsstat: kvm_openfiles: %s\n", errbuf);
E 15
E 11
E 10
E 7
		exit(1);
E 17
I 17
		if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY,
					errbuf)) == 0) {
			errx(1, "kvm_openfiles: %s", errbuf);
		}
		if (kvm_nlist(kd, nl) != 0) {
			errx(1, "kvm_nlist: can't get names");
		}
E 17
	}
D 10
	kmem = open(kmemf, O_RDONLY);
	if (kmem < 0) {
D 7
		perror(kmemf);
E 7
I 7
		(void)fprintf(stderr,
		    "nfsstat: %s: %s\n", kmemf, strerror(errno));
E 10
I 10
D 15
	if (kvm_nlist(nl) != 0) {
D 11
		fprintf(stderr, "nfsstate: kvm_nlist: can't get names");
E 11
I 11
		fprintf(stderr, "nfsstate: kvm_nlist: can't get names\n");
E 15
I 15
D 17
	if (kvm_nlist(kd, nl) != 0) {
		fprintf(stderr, "nfsstat: kvm_nlist: can't get names\n");
E 15
E 11
E 10
E 7
		exit(1);
	}
E 17
D 10
	if (kflag) {
I 9
#ifdef NEWVM
		(void)fprintf(stderr, "nfsstat: can't do core files yet\n");
		exit(1);
#else
E 9
		off_t off;
E 10

D 10
		Sysmap = (struct pte *)
		   malloc((u_int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
		if (!Sysmap) {
D 7
			fputs("nfsstat: can't get memory for Sysmap.\n", stderr);
E 7
I 7
			(void)fprintf(stderr, "nfsstat: %s\n", strerror(errno));
E 7
			exit(1);
		}
		off = nl[N_SYSMAP].n_value & ~KERNBASE;
		(void)lseek(kmem, off, L_SET);
		(void)read(kmem, (char *)Sysmap,
D 7
			(int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
E 7
I 7
		    (int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
I 9
#endif
E 9
E 7
	}
D 7
	intpr(interval, nl[N_NFSSTAT].n_value);
	exit(0);
}
E 7

D 7
/*
 * Seek into the kernel for a value.
 */
off_t
klseek(fd, base, off)
	int fd, off;
	off_t base;
{
	if (kflag) {
		/* get kernel pte */
		base &= ~KERNBASE;
		base = ctob(Sysmap[btop(base)].pg_pfnum) + (base & PGOFSET);
E 7
I 7
	if (!nl[N_NFSSTAT].n_value) {
		(void)fprintf(stderr, "nfsstat: nfsstats symbol not defined\n");
		exit(1);
E 7
	}
E 10
D 7
	return (lseek(fd, base, off));
E 7
I 7
	if (interval)
D 17
		sidewaysintpr(interval, nl[N_NFSSTAT].n_value);
E 17
I 17
		sidewaysintpr(interval);
E 17
	else
D 17
		intpr(nl[N_NFSSTAT].n_value);
E 17
I 17
		intpr();
E 17
	exit(0);
E 7
}

D 7
usage()
{
	fputs("Usage: nfsstat [interval [ system [ corefile ] ] ]\n", stderr);
	exit(1);
}

E 7
/*
I 17
 * Read the nfs stats using sysctl(3) for live kernels, or kvm_read
 * for dead ones.
 */
void
readstats(stp)
	struct nfsstats *stp;
{
	if(deadkernel) {
		if(kvm_read(kd, (u_long)nl[N_NFSSTAT].n_value, stp,
			    sizeof *stp) < 0) {
			err(1, "kvm_read");
		}
	} else {
		int name[3];
		size_t buflen = sizeof *stp;
		struct vfsconf vfc;

		if (getvfsbyname("nfs", &vfc) < 0)
			err(1, "getvfsbyname: NFS not compiled into kernel");
		name[0] = CTL_VFS;
		name[1] = vfc.vfc_typenum;
		name[2] = NFS_NFSSTATS;
		if (sysctl(name, 3, stp, &buflen, (void *)0, (size_t)0) < 0) {
			err(1, "sysctl");
		}
	}
}

/*
E 17
D 12
 * Print a description of the network interfaces.
E 12
I 12
 * Print a description of the nfs stats.
E 12
 */
I 8
void
E 8
D 7
intpr(interval, nfsstataddr)
	int interval;
E 7
I 7
D 17
intpr(nfsstataddr)
E 7
D 15
	off_t nfsstataddr;
E 15
I 15
	u_long nfsstataddr;
E 17
I 17
intpr()
E 17
E 15
{
	struct nfsstats nfsstats;

D 7
	if (nfsstataddr == 0) {
		printf("nfsstat: symbol not defined\n");
		return;
	}
	if (interval) {
		sidewaysintpr((unsigned)interval, nfsstataddr);
		return;
	}
E 7
D 8
	klseek(kmem, nfsstataddr, 0);
E 8
I 8
D 10
	klseek(kmem, nfsstataddr, 0L);
E 8
	read(kmem, (char *)&nfsstats, sizeof(struct nfsstats));
E 10
I 10
D 15
	kvm_read((void *)nfsstataddr, (char *)&nfsstats, sizeof(struct nfsstats));
E 15
I 15
D 17
	if (kvm_read(kd, (u_long)nfsstataddr, (char *)&nfsstats, sizeof(struct nfsstats)) < 0) {
		fprintf(stderr, "nfsstat: kvm_read failed\n");
		exit(1);
	}
E 17
I 17
	readstats(&nfsstats);

E 17
E 15
E 10
	printf("Client Info:\n");
I 4
	printf("Rpc Counts:\n");
E 4
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
		"Getattr", "Setattr", "Lookup", "Readlink", "Read",
		"Write", "Create", "Remove");
	printf("%9d %9d %9d %9d %9d %9d %9d %9d\n",
D 12
		nfsstats.rpccnt[1],
		nfsstats.rpccnt[2],
		nfsstats.rpccnt[4],
		nfsstats.rpccnt[5],
		nfsstats.rpccnt[6],
		nfsstats.rpccnt[8],
		nfsstats.rpccnt[9],
		nfsstats.rpccnt[10]);
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
E 12
I 12
		nfsstats.rpccnt[NFSPROC_GETATTR],
		nfsstats.rpccnt[NFSPROC_SETATTR],
		nfsstats.rpccnt[NFSPROC_LOOKUP],
		nfsstats.rpccnt[NFSPROC_READLINK],
		nfsstats.rpccnt[NFSPROC_READ],
		nfsstats.rpccnt[NFSPROC_WRITE],
		nfsstats.rpccnt[NFSPROC_CREATE],
		nfsstats.rpccnt[NFSPROC_REMOVE]);
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
E 12
		"Rename", "Link", "Symlink", "Mkdir", "Rmdir",
D 12
		"Readdir", "Statfs");
	printf("%9d %9d %9d %9d %9d %9d %9d\n",
		nfsstats.rpccnt[11],
		nfsstats.rpccnt[12],
		nfsstats.rpccnt[13],
		nfsstats.rpccnt[14],
		nfsstats.rpccnt[15],
		nfsstats.rpccnt[16],
		nfsstats.rpccnt[17]);
E 12
I 12
D 17
		"Readdir", "Statfs", "RdirLook");
E 17
I 17
		"Readdir", "RdirPlus", "Access");
E 17
	printf("%9d %9d %9d %9d %9d %9d %9d %9d\n",
		nfsstats.rpccnt[NFSPROC_RENAME],
		nfsstats.rpccnt[NFSPROC_LINK],
		nfsstats.rpccnt[NFSPROC_SYMLINK],
		nfsstats.rpccnt[NFSPROC_MKDIR],
		nfsstats.rpccnt[NFSPROC_RMDIR],
		nfsstats.rpccnt[NFSPROC_READDIR],
D 17
		nfsstats.rpccnt[NFSPROC_STATFS],
		nfsstats.rpccnt[NQNFSPROC_READDIRLOOK]);
	printf("%9.9s %9.9s %9.9s\n",
E 17
I 17
		nfsstats.rpccnt[NFSPROC_READDIRPLUS],
		nfsstats.rpccnt[NFSPROC_ACCESS]);
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
		"Mknod", "Fsstat", "Fsinfo", "PathConf", "Commit",
E 17
		"GLease", "Vacate", "Evict");
D 17
	printf("%9d %9d %9d\n",
E 17
I 17
	printf("%9d %9d %9d %9d %9d %9d %9d %9d\n",
		nfsstats.rpccnt[NFSPROC_MKNOD],
		nfsstats.rpccnt[NFSPROC_FSSTAT],
		nfsstats.rpccnt[NFSPROC_FSINFO],
		nfsstats.rpccnt[NFSPROC_PATHCONF],
		nfsstats.rpccnt[NFSPROC_COMMIT],
E 17
		nfsstats.rpccnt[NQNFSPROC_GETLEASE],
		nfsstats.rpccnt[NQNFSPROC_VACATED],
		nfsstats.rpccnt[NQNFSPROC_EVICTED]);
E 12
D 4
	printf("Rpc retries\n%11d\n",nfsstats.rpcretries);
E 4
I 4
	printf("Rpc Info:\n");
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s\n",
		"TimedOut", "Invalid", "X Replies", "Retries", "Requests");
	printf("%9d %9d %9d %9d %9d\n",
		nfsstats.rpctimeouts,
		nfsstats.rpcinvalid,
		nfsstats.rpcunexpected,
		nfsstats.rpcretries,
		nfsstats.rpcrequests);
E 4
	printf("Cache Info:\n");
D 2
	printf("%9.9s %9.9s %9.9s %9.9s\n",
E 2
I 2
	printf("%9.9s %9.9s %9.9s %9.9s",
E 2
		"Attr Hits", "Misses", "Lkup Hits", "Misses");
D 2
	printf("%9d %9d %9d %9d\n",
E 2
I 2
	printf(" %9.9s %9.9s %9.9s %9.9s\n",
		"BioR Hits", "Misses", "BioW Hits", "Misses");
	printf("%9d %9d %9d %9d",
E 2
		nfsstats.attrcache_hits, nfsstats.attrcache_misses,
		nfsstats.lookupcache_hits, nfsstats.lookupcache_misses);
I 2
	printf(" %9d %9d %9d %9d\n",
		nfsstats.biocache_reads-nfsstats.read_bios,
		nfsstats.read_bios,
		nfsstats.biocache_writes-nfsstats.write_bios,
		nfsstats.write_bios);
I 3
D 4
	printf("%9.9s %9.9s\n", "DirE Hits", "Misses");
	printf("%9d %9d\n",
E 4
I 4
	printf("%9.9s %9.9s %9.9s %9.9s",
		"BioRLHits", "Misses", "BioD Hits", "Misses");
	printf(" %9.9s %9.9s\n", "DirE Hits", "Misses");
	printf("%9d %9d %9d %9d",
		nfsstats.biocache_readlinks-nfsstats.readlink_bios,
		nfsstats.readlink_bios,
		nfsstats.biocache_readdirs-nfsstats.readdir_bios,
		nfsstats.readdir_bios);
	printf(" %9d %9d\n",
E 4
		nfsstats.direofcache_hits, nfsstats.direofcache_misses);
E 3
E 2
D 4
	printf("Server Info:\n");
E 4
I 4
	printf("\nServer Info:\n");
E 4
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
		"Getattr", "Setattr", "Lookup", "Readlink", "Read",
		"Write", "Create", "Remove");
	printf("%9d %9d %9d %9d %9d %9d %9d %9d\n",
D 12
		nfsstats.srvrpccnt[1],
		nfsstats.srvrpccnt[2],
		nfsstats.srvrpccnt[4],
		nfsstats.srvrpccnt[5],
		nfsstats.srvrpccnt[6],
		nfsstats.srvrpccnt[8],
		nfsstats.srvrpccnt[9],
		nfsstats.srvrpccnt[10]);
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
E 12
I 12
		nfsstats.srvrpccnt[NFSPROC_GETATTR],
		nfsstats.srvrpccnt[NFSPROC_SETATTR],
		nfsstats.srvrpccnt[NFSPROC_LOOKUP],
		nfsstats.srvrpccnt[NFSPROC_READLINK],
		nfsstats.srvrpccnt[NFSPROC_READ],
		nfsstats.srvrpccnt[NFSPROC_WRITE],
		nfsstats.srvrpccnt[NFSPROC_CREATE],
		nfsstats.srvrpccnt[NFSPROC_REMOVE]);
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
E 12
		"Rename", "Link", "Symlink", "Mkdir", "Rmdir",
D 12
		"Readdir", "Statfs");
	printf("%9d %9d %9d %9d %9d %9d %9d\n",
		nfsstats.srvrpccnt[11],
		nfsstats.srvrpccnt[12],
		nfsstats.srvrpccnt[13],
		nfsstats.srvrpccnt[14],
		nfsstats.srvrpccnt[15],
		nfsstats.srvrpccnt[16],
		nfsstats.srvrpccnt[17]);
E 12
I 12
D 17
		"Readdir", "Statfs", "RdirLook");
E 17
I 17
		"Readdir", "RdirPlus", "Access");
E 17
	printf("%9d %9d %9d %9d %9d %9d %9d %9d\n",
		nfsstats.srvrpccnt[NFSPROC_RENAME],
		nfsstats.srvrpccnt[NFSPROC_LINK],
		nfsstats.srvrpccnt[NFSPROC_SYMLINK],
		nfsstats.srvrpccnt[NFSPROC_MKDIR],
		nfsstats.srvrpccnt[NFSPROC_RMDIR],
		nfsstats.srvrpccnt[NFSPROC_READDIR],
D 17
		nfsstats.srvrpccnt[NFSPROC_STATFS],
		nfsstats.srvrpccnt[NQNFSPROC_READDIRLOOK]);
	printf("%9.9s %9.9s %9.9s\n",
E 17
I 17
		nfsstats.srvrpccnt[NFSPROC_READDIRPLUS],
		nfsstats.srvrpccnt[NFSPROC_ACCESS]);
	printf("%9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n",
		"Mknod", "Fsstat", "Fsinfo", "PathConf", "Commit",
E 17
		"GLease", "Vacate", "Evict");
D 17
	printf("%9d %9d %9d\n",
E 17
I 17
	printf("%9d %9d %9d %9d %9d %9d %9d %9d\n",
		nfsstats.srvrpccnt[NFSPROC_MKNOD],
		nfsstats.srvrpccnt[NFSPROC_FSSTAT],
		nfsstats.srvrpccnt[NFSPROC_FSINFO],
		nfsstats.srvrpccnt[NFSPROC_PATHCONF],
		nfsstats.srvrpccnt[NFSPROC_COMMIT],
E 17
		nfsstats.srvrpccnt[NQNFSPROC_GETLEASE],
		nfsstats.srvrpccnt[NQNFSPROC_VACATED],
		nfsstats.srvrpccnt[NQNFSPROC_EVICTED]);
E 12
D 2
	printf("Server Rpc Errors\n");
E 2
I 2
	printf("Server Ret-Failed\n");
E 2
	printf("%17d\n", nfsstats.srvrpc_errs);
	printf("Server Faults\n");
	printf("%13d\n", nfsstats.srv_errs);
I 2
	printf("Server Cache Stats:\n");
	printf("%9.9s %9.9s %9.9s %9.9s\n",
		"Inprog", "Idem", "Non-idem", "Misses");
	printf("%9d %9d %9d %9d\n",
		nfsstats.srvcache_inproghits,
		nfsstats.srvcache_idemdonehits,
		nfsstats.srvcache_nonidemdonehits,
		nfsstats.srvcache_misses);
I 12
	printf("Server Lease Stats:\n");
	printf("%9.9s %9.9s %9.9s\n",
		"Leases", "PeakL", "GLeases");
	printf("%9d %9d %9d\n",
		nfsstats.srvnqnfs_leases,
		nfsstats.srvnqnfs_maxleases,
		nfsstats.srvnqnfs_getleases);
I 17
	printf("Server Write Gathering:\n");
	printf("%9.9s %9.9s %9.9s\n",
		"WriteOps", "WriteRPC", "Opsaved");
	printf("%9d %9d %9d\n",
		nfsstats.srvvop_writes,
		nfsstats.srvrpccnt[NFSPROC_WRITE],
		nfsstats.srvrpccnt[NFSPROC_WRITE] - nfsstats.srvvop_writes);
E 17
E 12
E 2
}

u_char	signalled;			/* set if alarm goes off "early" */

/*
 * Print a running summary of nfs statistics.
 * Repeat display every interval seconds, showing statistics
 * collected over that interval.  Assumes that interval is non-zero.
 * First line printed at top of screen is always cumulative.
 */
I 8
void
E 8
D 17
sidewaysintpr(interval, off)
E 17
I 17
sidewaysintpr(interval)
E 17
D 8
	unsigned interval;
E 8
I 8
	u_int interval;
E 8
D 15
	off_t off;
E 15
I 15
D 17
	u_long off;
E 17
E 15
{
	struct nfsstats nfsstats, lastst;
D 8
	register int line;
	int oldmask;
E 8
I 8
	int hdrcnt, oldmask;
E 8
D 6
	int catchalarm();
E 6
I 6
	void catchalarm();
E 6

D 8
	klseek(kmem, off, 0);
E 8
I 8
D 10
	klseek(kmem, off, 0L);
E 8

E 10
	(void)signal(SIGALRM, catchalarm);
D 8
	signalled = NO;
E 8
I 8
	signalled = 0;
E 8
	(void)alarm(interval);
	bzero((caddr_t)&lastst, sizeof(lastst));
D 8
banner:
	printf("        %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s\n",
		"Getattr", "Lookup", "Readlink", "Read",
		"Write", "Rename", "Link", "Readdir");
	fflush(stdout);
	line = 0;
loop:
	klseek(kmem, off, 0);
	read(kmem, (char *)&nfsstats, sizeof nfsstats);
	printf("Client: %8d %8d %8d %8d %8d %8d %8d %8d\n",
		nfsstats.rpccnt[1]-lastst.rpccnt[1],
		nfsstats.rpccnt[4]-lastst.rpccnt[4],
		nfsstats.rpccnt[5]-lastst.rpccnt[5],
		nfsstats.rpccnt[6]-lastst.rpccnt[6],
		nfsstats.rpccnt[8]-lastst.rpccnt[8],
		nfsstats.rpccnt[11]-lastst.rpccnt[11],
		nfsstats.rpccnt[12]-lastst.rpccnt[12],
		nfsstats.rpccnt[16]-lastst.rpccnt[16]);
	printf("Server: %8d %8d %8d %8d %8d %8d %8d %8d\n",
		nfsstats.srvrpccnt[1]-lastst.srvrpccnt[1],
		nfsstats.srvrpccnt[4]-lastst.srvrpccnt[4],
		nfsstats.srvrpccnt[5]-lastst.srvrpccnt[5],
		nfsstats.srvrpccnt[6]-lastst.srvrpccnt[6],
		nfsstats.srvrpccnt[8]-lastst.srvrpccnt[8],
		nfsstats.srvrpccnt[11]-lastst.srvrpccnt[11],
		nfsstats.srvrpccnt[12]-lastst.srvrpccnt[12],
		nfsstats.srvrpccnt[16]-lastst.srvrpccnt[16]);
	lastst = nfsstats;
	fflush(stdout);
	line++;
	oldmask = sigblock(sigmask(SIGALRM));
D 7
	if (! signalled) {
E 7
I 7
	if (!signalled) {
E 7
		sigpause(0);
E 8
I 8

	for (hdrcnt = 1;;) {
		if (!--hdrcnt) {
			printhdr();
			hdrcnt = 20;
		}
D 10
		klseek(kmem, off, 0L);
		read(kmem, (char *)&nfsstats, sizeof nfsstats);
E 10
I 10
D 15
		kvm_read((void *)off, (char *)&nfsstats, sizeof nfsstats);
E 15
I 15
D 17
		if (kvm_read(kd, off, (char *)&nfsstats, sizeof nfsstats) < 0) {
			fprintf(stderr, "nfsstat: kvm_read failed\n");
			exit(1);
		}
E 17
I 17
		readstats(&nfsstats);
E 17
E 15
E 10
		printf("Client: %8d %8d %8d %8d %8d %8d %8d %8d\n",
D 17
		    nfsstats.rpccnt[1]-lastst.rpccnt[1],
		    nfsstats.rpccnt[4]-lastst.rpccnt[4],
		    nfsstats.rpccnt[5]-lastst.rpccnt[5],
		    nfsstats.rpccnt[6]-lastst.rpccnt[6],
		    nfsstats.rpccnt[8]-lastst.rpccnt[8],
		    nfsstats.rpccnt[11]-lastst.rpccnt[11],
		    nfsstats.rpccnt[12]-lastst.rpccnt[12],
		    nfsstats.rpccnt[16]-lastst.rpccnt[16]);
E 17
I 17
		    nfsstats.rpccnt[NFSPROC_GETATTR]-lastst.rpccnt[NFSPROC_GETATTR],
		    nfsstats.rpccnt[NFSPROC_LOOKUP]-lastst.rpccnt[NFSPROC_LOOKUP],
		    nfsstats.rpccnt[NFSPROC_READLINK]-lastst.rpccnt[NFSPROC_READLINK],
		    nfsstats.rpccnt[NFSPROC_READ]-lastst.rpccnt[NFSPROC_READ],
		    nfsstats.rpccnt[NFSPROC_WRITE]-lastst.rpccnt[NFSPROC_WRITE],
		    nfsstats.rpccnt[NFSPROC_RENAME]-lastst.rpccnt[NFSPROC_RENAME],
		    nfsstats.rpccnt[NFSPROC_ACCESS]-lastst.rpccnt[NFSPROC_ACCESS],
		    (nfsstats.rpccnt[NFSPROC_READDIR]-lastst.rpccnt[NFSPROC_READDIR])
		    +(nfsstats.rpccnt[NFSPROC_READDIRPLUS]-lastst.rpccnt[NFSPROC_READDIRPLUS]));
E 17
		printf("Server: %8d %8d %8d %8d %8d %8d %8d %8d\n",
D 17
		    nfsstats.srvrpccnt[1]-lastst.srvrpccnt[1],
		    nfsstats.srvrpccnt[4]-lastst.srvrpccnt[4],
		    nfsstats.srvrpccnt[5]-lastst.srvrpccnt[5],
		    nfsstats.srvrpccnt[6]-lastst.srvrpccnt[6],
		    nfsstats.srvrpccnt[8]-lastst.srvrpccnt[8],
		    nfsstats.srvrpccnt[11]-lastst.srvrpccnt[11],
		    nfsstats.srvrpccnt[12]-lastst.srvrpccnt[12],
		    nfsstats.srvrpccnt[16]-lastst.srvrpccnt[16]);
E 17
I 17
		    nfsstats.srvrpccnt[NFSPROC_GETATTR]-lastst.srvrpccnt[NFSPROC_GETATTR],
		    nfsstats.srvrpccnt[NFSPROC_LOOKUP]-lastst.srvrpccnt[NFSPROC_LOOKUP],
		    nfsstats.srvrpccnt[NFSPROC_READLINK]-lastst.srvrpccnt[NFSPROC_READLINK],
		    nfsstats.srvrpccnt[NFSPROC_READ]-lastst.srvrpccnt[NFSPROC_READ],
		    nfsstats.srvrpccnt[NFSPROC_WRITE]-lastst.srvrpccnt[NFSPROC_WRITE],
		    nfsstats.srvrpccnt[NFSPROC_RENAME]-lastst.srvrpccnt[NFSPROC_RENAME],
		    nfsstats.srvrpccnt[NFSPROC_ACCESS]-lastst.srvrpccnt[NFSPROC_ACCESS],
		    (nfsstats.srvrpccnt[NFSPROC_READDIR]-lastst.srvrpccnt[NFSPROC_READDIR])
		    +(nfsstats.srvrpccnt[NFSPROC_READDIRPLUS]-lastst.srvrpccnt[NFSPROC_READDIRPLUS]));
E 17
		lastst = nfsstats;
		fflush(stdout);
		oldmask = sigblock(sigmask(SIGALRM));
		if (!signalled)
			sigpause(0);
		sigsetmask(oldmask);
		signalled = 0;
		(void)alarm(interval);
E 8
	}
D 8
	sigsetmask(oldmask);
	signalled = NO;
	(void)alarm(interval);
	if (line == 21)
		goto banner;
	goto loop;
E 8
	/*NOTREACHED*/
}

I 8
void
printhdr()
{
	printf("        %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s\n",
	    "Getattr", "Lookup", "Readlink", "Read", "Write", "Rename",
D 17
	    "Link", "Readdir");
E 17
I 17
	    "Access", "Readdir");
E 17
	fflush(stdout);
}

E 8
/*
 * Called if an interval expires before sidewaysintpr has completed a loop.
 * Sets a flag to not wait for the alarm.
 */
I 6
void
E 6
catchalarm()
{
D 8
	signalled = YES;
E 8
I 8
	signalled = 1;
E 8
I 7
D 10
}

/*
 * Seek into the kernel for a value.
 */
off_t
klseek(fd, base, off)
	int fd, off;
	off_t base;
{
I 9
#ifndef NEWVM
E 9
	if (kflag) {
		/* get kernel pte */
		base &= ~KERNBASE;
		base = ctob(Sysmap[btop(base)].pg_pfnum) + (base & PGOFSET);
	}
I 9
#endif
E 9
	return (lseek(fd, base, off));
E 10
}

I 8
void
E 8
usage()
{
	(void)fprintf(stderr,
D 8
	    "usage: nfsstat [-i interval] [kernel [corefile]]\n");
E 8
I 8
	    "usage: nfsstat [-M core] [-N system] [-w interval]\n");
E 8
	exit(1);
E 7
}
E 1
