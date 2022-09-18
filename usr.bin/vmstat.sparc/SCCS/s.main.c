h03362
s 00005/00005/00274
d D 8.1 93/06/06 22:22:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00279/00000/00000
d D 5.1 93/05/21 15:10:06 torek 1 0
c date and time created 93/05/21 15:10:06 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1980, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1980, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1980, 1986, 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1980, 1986, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/device.h>
#include <sys/disklabel.h>
#include <sys/disk.h>
#include <sys/time.h>
#include <sys/dkstat.h>
#include <sys/ioctl.h>
#include <vm/vm.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <kvm.h>
#include <limits.h>
#include <nlist.h>
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "extern.h"
#include "getdev.h"

struct nlist nl[] = {
	{ "_alldevs" },
#define	X_ALLDEVS	0
	{ "_boottime" },
#define	X_BOOTTIME	1
	0
};

struct dkinfo *dkinfo, **nextdk = &dkinfo;
int	ndrives;
kvm_t	*kd;

void	dkadd __P((u_long, struct device *));
char	**dkselect __P((char **));
void	getdisks __P((u_long));
int	isdk __P((struct device *));

#define	INTRSTAT	0x01
#define	MEMSTAT		0x02
#define	SUMSTAT		0x04
#define	VMSTAT		0x08

int
main(argc, argv)
	register int argc;
	register char **argv;
{
	extern int optind;
	extern char *optarg;
	register int c, todo;
	u_int interval;
	int reps;
	char *memf, *nlistf;
        char errbuf[_POSIX2_LINE_MAX];

	memf = nlistf = NULL;
	interval = reps = todo = 0;
	while ((c = getopt(argc, argv, "c:iM:mN:sw:")) != EOF) {
		switch (c) {
		case 'c':
			reps = atoi(optarg);
			break;
		case 'i':
			todo |= INTRSTAT;
			break;
		case 'M':
			memf = optarg;
			break;
		case 'm':
			todo |= MEMSTAT;
			break;
		case 'N':
			nlistf = optarg;
			break;
		case 's':
			todo |= SUMSTAT;
			break;
		case 'w':
			interval = atoi(optarg);
			break;
		case '?':
		default:
			errexit("usage: vmstat [-ims] [-c count] [-M core] \
[-N system] [-w wait] [disks]\n");
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (todo == 0)
		todo = VMSTAT;

	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
		setgid(getgid());

        kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf);
	if (kd == 0) {
		(void)fprintf(stderr,
		    "vmstat: kvm_openfiles: %s\n", errbuf);
		exit(1);
	}

	if ((c = kvm_nlist(kd, nl)) != 0) {
		if (c > 0) {
			(void)fprintf(stderr,
			    "vmstat: undefined symbols: ");
			for (c = 0; c < sizeof(nl)/sizeof(nl[0]) - 1; c++)
				if (nl[c].n_type == 0)
					printf(" %s", nl[c].n_name);
			(void)fputc('\n', stderr);
		} else
			(void)fprintf(stderr, "vmstat: kvm_nlist: %s\n",
			    kvm_geterr(kd));
		exit(1);
	}

	if (todo & VMSTAT) {
		getdev(nl[X_ALLDEVS].n_value, isdk, dkadd);
		argv = dkselect(argv);
	}

#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		interval = atoi(*argv);
		if (*++argv)
			reps = atoi(*argv);
	}
#endif

	if (interval) {
		if (!reps)
			reps = -1;
	} else if (reps)
		interval = 1;

	if (todo & MEMSTAT)
		domem();
	if (todo & SUMSTAT)
		dosum();
	if (todo & INTRSTAT)
		dointr();
	if (todo & VMSTAT)
		dovmstat(interval, reps);
	exit(0);
}

int
isdk(dv)
	struct device *dv;
{

	return (dv->dv_class == DV_DISK);
}

void
dkadd(addr, dv)
	u_long addr;
	struct device *dv;
{
	register struct dkinfo *dk;
	register char *name;

	name = dv->dv_xname;
	dk = malloc(sizeof *dk);
	if (dk == NULL || (dk->dk_name = strdup(name)) == NULL)
		errexit("dkadd(%s): malloc: %s\n", name, strerror(errno));
	*nextdk = dk;
	nextdk = &dk->dk_next;
	dk->dk_next = NULL;
	dk->dk_sel = 0;
	dk->dk_addr = addr;
	dk->dk_2c[0] = name[0];
	dk->dk_2c[1] = name[strlen(name) - 1];
	dk->dk_2c[2] = 0;
#ifdef notyet
	/*
	 * Fill in dk_oxfer so that we can compute deltas next time.
	 */
	(void)snprintf(buf, sizeof buf, "%s xfer", name);
	kread(addr + offsetof(struct dkdevice, dk_xfer),
	    &dk->dk_oxfer, sizeof dk->dk_oxfer, buf);
#endif
}

/*
 * Choose drives to be displayed.  Priority goes to (in order) drives
 * supplied as arguments, default drives.  If everything isn't filled
 * in and there are drives not taken care of, display the first few
 * that fit.
 */
char **
dkselect(argv)
	char **argv;
{
	register struct dkinfo *dk;
	register char **cpp, *cp;
	extern char *defdrives[];
#define BACKWARD_COMPATIBILITY

	for (; (cp = *argv) != NULL; ++argv) {
#ifdef	BACKWARD_COMPATIBILITY
		if (isdigit(*cp))
			break;
#endif
		for (dk = dkinfo; dk != NULL; dk = dk->dk_next) {
			if (strcmp(dk->dk_name, cp) != 0)
				continue;
			if (!dk->dk_sel) {
				dk->dk_sel = 1;
				++ndrives;
			}
			break;
		}
	}
	for (dk = dkinfo; dk != NULL && ndrives < 4; dk = dk->dk_next) {
		if (dk->dk_sel)
			continue;
		for (cpp = defdrives; (cp = *cpp) != NULL; cpp++)
			if (strcmp(dk->dk_name, cp) == 0) {
				dk->dk_sel = 1;
				++ndrives;
				break;
			}
	}
	for (dk = dkinfo; dk != NULL && ndrives < 4; dk = dk->dk_next) {
		if (dk->dk_sel)
			continue;
		dk->dk_sel = 1;
		++ndrives;
	}
	return (argv);
}

long
getuptime()
{
	static time_t boottime;
	time_t now, uptime;

	if (boottime == 0)
		kread(nl[X_BOOTTIME].n_value, &boottime, sizeof boottime,
		    "boottime");
	(void)time(&now);
	uptime = now - boottime;
	if (uptime <= 0 || uptime > 60*60*24*365*10) {
		(void)fprintf(stderr,
		    "vmstat: time makes no sense; namelist must be wrong.\n");
		exit(1);
	}
	return (uptime);
}
E 1
