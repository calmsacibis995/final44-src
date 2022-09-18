h58991
s 00001/00001/00617
d D 8.5 95/05/09 16:39:32 mckusick 17 16
c allow argument to trim down output for -A
e
s 00002/00001/00616
d D 8.4 95/04/27 15:41:06 bostic 16 15
c lint
c From: Chris Torek <torek@BSDI.COM>
e
s 00001/00001/00616
d D 8.3 95/04/27 13:49:16 bostic 15 14
c argument pointer not being incremented through arguments
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00075/00004/00542
d D 8.2 95/04/26 15:57:47 mckusick 14 13
c add CTL_VFS output
e
s 00005/00005/00541
d D 8.1 93/06/06 14:07:51 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00037/00007/00509
d D 5.12 93/05/26 00:11:03 mckusick 12 11
c add code for console device (if present)
e
s 00014/00000/00502
d D 5.11 93/05/20 13:04:24 mckusick 11 10
c add support for printing out boottime
e
s 00003/00000/00499
d D 5.10 93/05/04 12:05:47 bostic 10 9
c add CTL_USER
e
s 00018/00001/00481
d D 5.9 93/05/02 16:08:04 mckusick 9 8
c add provision for kern.profiling
e
s 00004/00002/00478
d D 5.8 93/04/27 16:14:46 bostic 8 7
c <sys/sysctl.h> now needs <sys/param.h>
e
s 00023/00003/00457
d D 5.7 93/04/27 00:19:04 mckusick 7 6
c add support for getting udp checksum
e
s 00002/00001/00458
d D 5.6 93/04/21 11:55:40 torek 6 5
c "unspec" changed to NULL in the sysctl structs; handle it here
e
s 00034/00002/00425
d D 5.5 93/04/19 00:15:45 mckusick 5 4
c add support for listing debugging variables
e
s 00138/00039/00289
d D 5.4 93/04/18 00:33:52 mckusick 4 3
c add support for net.inet variables
e
s 00003/00002/00325
d D 5.3 93/04/01 11:34:11 mckusick 3 2
c update usage message
e
s 00053/00030/00274
d D 5.2 93/04/01 11:22:50 mckusick 2 1
c add -n option (number only); partial matching; better int vs char heuristic
e
s 00304/00000/00000
d D 5.1 93/03/30 23:48:06 mckusick 1 0
c date and time created 93/03/30 23:48:06 by mckusick
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 13
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 8
#include <sys/types.h>
E 8
I 8
#include <sys/param.h>
I 9
#include <sys/gmon.h>
I 14
#include <sys/mount.h>
E 14
E 9
E 8
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <vm/vm_param.h>
I 12
#include <machine/cpu.h>
E 12
I 8

E 8
I 4
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp_var.h>
I 7
#include <netinet/ip_var.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>
I 8

E 8
E 7
E 4
#include <errno.h>
I 8
#include <stdio.h>
E 8
#include <stdlib.h>
#include <string.h>
D 8
#include <stdio.h>
E 8

D 4
char *topname[] = CTL_NAMES;
char *kernname[] = CTL_KERN_NAMES;
char *vmname[] = CTL_VM_NAMES;
char *netname[] = CTL_NET_NAMES;
char *hwname[] = CTL_HW_NAMES;
E 4
I 4
struct ctlname topname[] = CTL_NAMES;
struct ctlname kernname[] = CTL_KERN_NAMES;
struct ctlname vmname[] = CTL_VM_NAMES;
struct ctlname netname[] = CTL_NET_NAMES;
struct ctlname hwname[] = CTL_HW_NAMES;
I 10
struct ctlname username[] = CTL_USER_NAMES;
E 10
I 5
struct ctlname debugname[CTL_DEBUG_MAXID];
I 14
struct ctlname *vfsname;
E 14
I 12
#ifdef CTL_MACHDEP_NAMES
struct ctlname machdepname[] = CTL_MACHDEP_NAMES;
#endif
E 12
char names[BUFSIZ];
I 14
int lastused;
E 14
E 5
E 4

struct list {
D 4
	char	**list;
E 4
I 4
	struct	ctlname *list;
E 4
	int	size;
D 4
} secondlevel[] = {
E 4
I 4
};
struct list toplist = { topname, CTL_MAXID };
struct list secondlevel[] = {
E 4
	{ 0, 0 },			/* CTL_UNSPEC */
	{ kernname, KERN_MAXID },	/* CTL_KERN */
	{ vmname, VM_MAXID },		/* CTL_VM */
D 14
	{ 0, 0 },			/* CTL_FS */
E 14
I 14
	{ 0, 0 },			/* CTL_VFS */
E 14
	{ netname, NET_MAXID },		/* CTL_NET */
D 5
	{ 0, 0 },			/* CTL_DEBUG */
E 5
I 5
	{ 0, CTL_DEBUG_MAXID },		/* CTL_DEBUG */
E 5
	{ hwname, HW_MAXID },		/* CTL_HW */
I 12
#ifdef CTL_MACHDEP_NAMES
	{ machdepname, CPU_MAXID },	/* CTL_MACHDEP */
#else
E 12
	{ 0, 0 },			/* CTL_MACHDEP */
I 12
#endif
E 12
I 10
	{ username, USER_MAXID },	/* CTL_USER_NAMES */
E 10
};

D 2
int	Aflag, aflag, wflag;
E 2
I 2
int	Aflag, aflag, nflag, wflag;
E 2

I 12
/*
 * Variables requiring special processing.
 */
#define	CLOCK		0x00000001
#define	BOOTTIME	0x00000002
#define	CONSDEV		0x00000004

E 12
int
main(argc, argv)
	int argc;
	char *argv[];
{
	extern char *optarg;
	extern int optind;
D 2
	int ch;
E 2
I 2
	int ch, lvl1;
E 2

D 2
	while ((ch = getopt(argc, argv, "Aaw")) != EOF) {
E 2
I 2
	while ((ch = getopt(argc, argv, "Aanw")) != EOF) {
E 2
		switch (ch) {

		case 'A':
			Aflag = 1;
			break;

		case 'a':
			aflag = 1;
			break;

I 2
		case 'n':
			nflag = 1;
			break;

E 2
		case 'w':
			wflag = 1;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

D 17
	if (Aflag || aflag) {
E 17
I 17
	if (argc == 0 && (Aflag || aflag)) {
E 17
I 5
		debuginit();
I 14
		vfsinit();
E 14
E 5
D 2
		listall();
E 2
I 2
		for (lvl1 = 1; lvl1 < CTL_MAXID; lvl1++)
D 4
			listall(lvl1);
E 4
I 4
			listall(topname[lvl1].ctl_name, &secondlevel[lvl1]);
E 4
E 2
		exit(0);
	}
	if (argc == 0)
		usage();
D 15
	while (argc-- > 0)
E 15
I 15
	for (; *argv != NULL; ++argv)
E 15
		parse(*argv, 1);
	exit(0);
}

/*
 * List all variables known to the system.
 */
D 2
listall()
E 2
I 2
D 4
listall(lvl1)
	int lvl1;
E 2
{
E 4
I 4
listall(prefix, lp)
	char *prefix;
E 4
	struct list *lp;
I 4
{
E 4
D 2
	int lvl1, lvl2;
E 2
I 2
	int lvl2;
E 2
	char *cp, name[BUFSIZ];

D 2
	for (lvl1 = 1; lvl1 < CTL_MAXID; lvl1++) {
		lp = &secondlevel[lvl1];
		if (lp->list == 0)
			continue;
		strcpy(name, topname[lvl1]);
		cp = &name[strlen(name)];
		*cp++ = '.';
		for (lvl2 = 1; lvl2 < lp->size; lvl2++) {
			strcpy(cp, lp->list[lvl2]);
			parse(name, Aflag);
		}
E 2
I 2
D 4
	lp = &secondlevel[lvl1];
E 4
	if (lp->list == 0)
		return;
D 4
	strcpy(name, topname[lvl1]);
E 4
I 4
	strcpy(name, prefix);
E 4
	cp = &name[strlen(name)];
	*cp++ = '.';
D 4
	for (lvl2 = 1; lvl2 < lp->size; lvl2++) {
		strcpy(cp, lp->list[lvl2]);
E 4
I 4
	for (lvl2 = 0; lvl2 < lp->size; lvl2++) {
		if (lp->list[lvl2].ctl_name == 0)
			continue;
		strcpy(cp, lp->list[lvl2].ctl_name);
E 4
		parse(name, Aflag);
E 2
	}
}

/*
 * Parse a name into a MIB entry.
 * Lookup and print out the MIB entry if it exists.
 * Set a new value if requested.
 */
parse(string, flags)
	char *string;
	int flags;
{
D 4
	int indx, size;
E 4
I 4
D 9
	int indx, type, size, len;
E 9
I 9
D 14
	int indx, type, state, size, len;
E 14
I 14
	int indx, type, state, len;
	size_t size;
E 14
E 9
E 4
D 12
	int isclockrate = 0;
I 11
	int isboottime = 0;
E 12
I 12
	int special = 0;
E 12
E 11
	void *newval = 0;
	int intval, newsize = 0;
D 4
	struct list top, *lp;
E 4
I 4
	quad_t quadval;
	struct list *lp;
I 14
	struct vfsconf vfc;
E 14
E 4
	int mib[CTL_MAXNAME];
	char *cp, *bufp, buf[BUFSIZ], strval[BUFSIZ];

	bufp = buf;
	snprintf(buf, BUFSIZ, "%s", string);
	if ((cp = strchr(string, '=')) != NULL) {
		if (!wflag) {
			fprintf(stderr, "Must specify -w to set variables\n");
			exit(2);
		}
		*strchr(buf, '=') = '\0';
		*cp++ = '\0';
		while (isspace(*cp))
			cp++;
D 4
		if (isdigit(*cp)) {
			intval = atoi(cp);
			newval = &intval;
			newsize = sizeof intval;
		} else {
			newval = cp;
			newsize = strlen(cp);
		}
E 4
I 4
		newval = cp;
		newsize = strlen(cp);
E 4
	}
D 4
	top.list = topname;
	top.size = CTL_MAXID;
	if ((indx = findname(string, "top", &bufp, &top)) == -1)
E 4
I 4
	if ((indx = findname(string, "top", &bufp, &toplist)) == -1)
E 4
		return;
	mib[0] = indx;
I 14
	if (indx == CTL_VFS)
		vfsinit();
E 14
I 5
	if (indx == CTL_DEBUG)
		debuginit();
E 5
	lp = &secondlevel[indx];
	if (lp->list == 0) {
		fprintf(stderr, "%s: class is not implemented\n",
		    topname[indx]);
		return;
	}
I 2
	if (bufp == NULL) {
D 4
		listall(indx);
E 4
I 4
		listall(topname[indx].ctl_name, lp);
E 4
		return;
	}
E 2
	if ((indx = findname(string, "second", &bufp, lp)) == -1)
		return;
	mib[1] = indx;
D 4
	if (bufp) {
		fprintf(stderr, "name %s in %s is unknown\n", *bufp, string);
		return;
	}
E 4
I 4
	type = lp->list[indx].ctl_type;
	len = 2;
E 4
	switch (mib[0]) {

	case CTL_KERN:
		switch (mib[1]) {
I 9
		case KERN_PROF:
			mib[2] = GPROF_STATE;
			size = sizeof state;
			if (sysctl(mib, 3, &state, &size, NULL, 0) < 0) {
				if (flags == 0)
					return;
				if (!nflag)
					fprintf(stdout, "%s: ", string);
				fprintf(stderr,
				    "kernel is not compiled for profiling\n");
				return;
			}
			if (!nflag)
				fprintf(stdout, "%s: %s\n", string,
				    state == GMON_PROF_OFF ? "off" : "running");
			return;
E 9
		case KERN_VNODE:
		case KERN_FILE:
			if (flags == 0)
				return;
			fprintf(stderr,
			    "Use pstat to view %s information\n", string);
			return;
		case KERN_PROC:
			if (flags == 0)
				return;
			fprintf(stderr,
			    "Use ps to view %s information\n", string);
			return;
		case KERN_CLOCKRATE:
D 12
			isclockrate = 1;
E 12
I 12
			special |= CLOCK;
E 12
			break;
I 11
		case KERN_BOOTTIME:
D 12
			isboottime = 1;
E 12
I 12
			special |= BOOTTIME;
E 12
			break;
E 11
		}
		break;

	case CTL_HW:
		break;

	case CTL_VM:
		if (mib[1] == VM_LOADAVG) {
			double loads[3];

			getloadavg(loads, 3);
D 2
			fprintf(stdout, "%s: %.2f %.2f %.2f\n", string,
E 2
I 2
			if (!nflag)
				fprintf(stdout, "%s: ", string);
			fprintf(stdout, "%.2f %.2f %.2f\n", 
E 2
			    loads[0], loads[1], loads[2]);
			return;
		}
		if (flags == 0)
			return;
		fprintf(stderr,
		    "Use vmstat or systat to view %s information\n", string);
		return;

	case CTL_NET:
I 4
		if (mib[1] == PF_INET) {
			len = sysctl_inet(string, &bufp, mib, flags, &type);
			if (len >= 0)
				break;
			return;
		}
E 4
		if (flags == 0)
			return;
		fprintf(stderr, "Use netstat to view %s information\n", string);
		return;

D 5
	case CTL_FS:
E 5
	case CTL_DEBUG:
I 5
		mib[2] = CTL_DEBUG_VALUE;
		len = 3;
		break;

D 12
	case CTL_FS:
E 12
E 5
	case CTL_MACHDEP:
I 12
#ifdef CPU_CONSDEV
		if (mib[1] == CPU_CONSDEV)
			special |= CONSDEV;
#endif
		break;

D 14
	case CTL_FS:
E 14
I 14
	case CTL_VFS:
		mib[3] = mib[1];
		mib[1] = VFS_GENERIC;
		mib[2] = VFS_CONF;
		len = 4;
		size = sizeof vfc;
		if (sysctl(mib, 4, &vfc, &size, (void *)0, (size_t)0) < 0) {
			perror("vfs print");
			return;
		}
		if (flags == 0 && vfc.vfc_refcount == 0)
			return;
		if (!nflag)
			fprintf(stdout, "%s has %d mounted instance%s\n",
			    string, vfc.vfc_refcount,
			    vfc.vfc_refcount != 1 ? "s" : "");
		else
			fprintf(stdout, "%d\n", vfc.vfc_refcount);
		return;

E 14
E 12
I 10
	case CTL_USER:
E 10
		break;

	default:
		fprintf(stderr, "Illegal top level value: %d\n", mib[0]);
		return;
	
	}
I 4
	if (bufp) {
		fprintf(stderr, "name %s in %s is unknown\n", *bufp, string);
		return;
	}
	if (newsize > 0) {
		switch (type) {
		case CTLTYPE_INT:
			intval = atoi(newval);
			newval = &intval;
			newsize = sizeof intval;
			break;
E 4

I 4
		case CTLTYPE_QUAD:
			sscanf(newval, "%qd", &quadval);
			newval = &quadval;
			newsize = sizeof quadval;
			break;
		}
	}
E 4
	size = BUFSIZ;
D 4
	if (sysctl(mib, 2, buf, &size, newsize ? newval : 0, newsize) == -1) {
E 4
I 4
	if (sysctl(mib, len, buf, &size, newsize ? newval : 0, newsize) == -1) {
E 4
		if (flags == 0)
			return;
		switch (errno) {
		case EOPNOTSUPP:
			fprintf(stderr, "%s: value is not available\n", string);
			return;
		case ENOTDIR:
			fprintf(stderr, "%s: specification is incomplete\n",
			    string);
			return;
		case ENOMEM:
			fprintf(stderr, "%s: type is unknown to this program\n",
			    string);
			return;
		default:
			perror(string);
			return;
		}
	}
D 12
	if (isclockrate) {
E 12
I 12
	if (special & CLOCK) {
E 12
		struct clockinfo *clkp = (struct clockinfo *)buf;

I 2
		if (!nflag)
			fprintf(stdout, "%s: ", string);
E 2
		fprintf(stdout,
D 2
		    "%s: hz = %d, tick = %d, profhz = %d, stathz = %d\n",
		    string, clkp->hz, clkp->tick, clkp->profhz, clkp->stathz);
E 2
I 2
		    "hz = %d, tick = %d, profhz = %d, stathz = %d\n",
		    clkp->hz, clkp->tick, clkp->profhz, clkp->stathz);
I 11
		return;
	}
D 12
	if (isboottime) {
E 12
I 12
	if (special & BOOTTIME) {
E 12
		struct timeval *btp = (struct timeval *)buf;

		if (!nflag)
			fprintf(stdout, "%s = %s\n", string,
			    ctime(&btp->tv_sec));
		else
			fprintf(stdout, "%d\n", btp->tv_sec);
I 12
		return;
	}
	if (special & CONSDEV) {
		dev_t dev = *(dev_t *)buf;

		if (!nflag)
			fprintf(stdout, "%s = %s\n", string,
			    devname(dev, S_IFCHR));
		else
			fprintf(stdout, "0x%x\n", dev);
E 12
E 11
E 2
		return;
	}
D 2
	if (size == sizeof(int) && !isprint(buf[0]))
		if (newsize == 0)
			fprintf(stdout, "%s = %d\n", string, *(int *)buf);
		else
			fprintf(stdout, "%s: %d -> %d\n", string, *(int *)buf,
			    *(int *)newval);
E 2
I 2
D 4
	if (size == sizeof(int) && !(isprint(buf[0]) && isprint(buf[1]) &&
	    isprint(buf[2]) && isprint(buf[3])))
E 4
I 4
	switch (type) {
	case CTLTYPE_INT:
E 4
		if (newsize == 0) {
			if (!nflag)
				fprintf(stdout, "%s = ", string);
			fprintf(stdout, "%d\n", *(int *)buf);
		} else {
			if (!nflag)
				fprintf(stdout, "%s: %d -> ", string,
				    *(int *)buf);
			fprintf(stdout, "%d\n", *(int *)newval);
		}
E 2
D 4
	else
E 4
I 4
		return;

	case CTLTYPE_STRING:
E 4
D 2
		if (newsize == 0)
			fprintf(stdout, "%s = %s\n", string, buf);
		else
			fprintf(stdout, "%s: %s -> %s\n", string, buf, newval);
E 2
I 2
		if (newsize == 0) {
			if (!nflag)
				fprintf(stdout, "%s = ", string);
			fprintf(stdout, "%s\n", buf);
		} else {
			if (!nflag)
				fprintf(stdout, "%s: %s -> ", string, buf);
			fprintf(stdout, "%s\n", newval);
		}
E 2
D 4
	return;
E 4
I 4
		return;

	case CTLTYPE_QUAD:
		if (newsize == 0) {
			if (!nflag)
				fprintf(stdout, "%s = ", string);
			fprintf(stdout, "%qd\n", *(quad_t *)buf);
		} else {
			if (!nflag)
				fprintf(stdout, "%s: %qd -> ", string,
				    *(quad_t *)buf);
			fprintf(stdout, "%qd\n", *(quad_t *)newval);
		}
		return;

	case CTLTYPE_STRUCT:
		fprintf(stderr, "%s: unknown structure returned\n",
		    string);
		return;

	default:
	case CTLTYPE_NODE:
		fprintf(stderr, "%s: unknown type returned\n",
		    string);
		return;
I 5
	}
}

/*
 * Initialize the set of debugging names
 */
debuginit()
{
D 16
	int mib[3], size, loc, i;
E 16
I 16
	int mib[3], loc, i;
	size_t size;
E 16

	if (secondlevel[CTL_DEBUG].list != 0)
		return;
	secondlevel[CTL_DEBUG].list = debugname;
	mib[0] = CTL_DEBUG;
	mib[2] = CTL_DEBUG_NAME;
D 14
	for (loc = 0, i = 0; i < CTL_DEBUG_MAXID; i++) {
E 14
I 14
	for (loc = lastused, i = 0; i < CTL_DEBUG_MAXID; i++) {
E 14
		mib[1] = i;
		size = BUFSIZ - loc;
		if (sysctl(mib, 3, &names[loc], &size, NULL, 0) == -1)
			continue;
		debugname[i].ctl_name = &names[loc];
		debugname[i].ctl_type = CTLTYPE_INT;
		loc += size;
E 5
	}
I 14
	lastused = loc;
}

/*
 * Initialize the set of filesystem names
 */
vfsinit()
{
	int mib[4], maxtypenum, cnt, loc, size;
	struct vfsconf vfc;
	size_t buflen;

	if (secondlevel[CTL_VFS].list != 0)
		return;
	mib[0] = CTL_VFS;
	mib[1] = VFS_GENERIC;
	mib[2] = VFS_MAXTYPENUM;
	buflen = 4;
	if (sysctl(mib, 3, &maxtypenum, &buflen, (void *)0, (size_t)0) < 0)
		return;
	if ((vfsname = malloc(maxtypenum * sizeof(*vfsname))) == 0)
		return;
	memset(vfsname, 0, maxtypenum * sizeof(*vfsname));
	mib[2] = VFS_CONF;
	buflen = sizeof vfc;
	for (loc = lastused, cnt = 0; cnt < maxtypenum; cnt++) {
		mib[3] = cnt;
		if (sysctl(mib, 4, &vfc, &buflen, (void *)0, (size_t)0) < 0) {
			if (errno == EOPNOTSUPP)
				continue;
			perror("vfsinit");
			free(vfsname);
			return;
		}
		strcat(&names[loc], vfc.vfc_name);
		vfsname[cnt].ctl_name = &names[loc];
		vfsname[cnt].ctl_type = CTLTYPE_INT;
		size = strlen(vfc.vfc_name) + 1;
		loc += size;
	}
	lastused = loc;
	secondlevel[CTL_VFS].list = vfsname;
	secondlevel[CTL_VFS].size = maxtypenum;
	return;
E 14
E 4
}

I 4
struct ctlname inetname[] = CTL_IPPROTO_NAMES;
struct ctlname ipname[] = IPCTL_NAMES;
struct ctlname icmpname[] = ICMPCTL_NAMES;
I 7
struct ctlname udpname[] = UDPCTL_NAMES;
E 7
struct list inetlist = { inetname, IPPROTO_MAXID };
struct list inetvars[] = {
D 7
	{ ipname, IPCTL_MAXID },
	{ icmpname, ICMPCTL_MAXID },
E 7
I 7
	{ ipname, IPCTL_MAXID },	/* ip */
	{ icmpname, ICMPCTL_MAXID },	/* icmp */
	{ 0, 0 },			/* igmp */
	{ 0, 0 },			/* ggmp */
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },			/* tcp */
	{ 0, 0 },
	{ 0, 0 },			/* egp */
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },			/* pup */
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ udpname, UDPCTL_MAXID },	/* udp */
E 7
};

E 4
/*
I 4
 * handle internet requests
 */
sysctl_inet(string, bufpp, mib, flags, typep)
	char *string;
	char **bufpp;
	int mib[];
	int flags;
	int *typep;
{
	struct list *lp;
	int indx;

	if (*bufpp == NULL) {
		listall(string, &inetlist);
		return (-1);
	}
	if ((indx = findname(string, "third", bufpp, &inetlist)) == -1)
		return (-1);
	mib[2] = indx;
D 7
	if (indx < 2)
E 7
I 7
	if (indx <= IPPROTO_UDP && inetvars[indx].list != NULL)
E 7
		lp = &inetvars[indx];
	else if (!flags)
		return (-1);
	else {
		fprintf(stderr, "%s: no variables defined for this protocol\n",
		    string);
		return (-1);
	}
	if (*bufpp == NULL) {
		listall(string, lp);
		return (-1);
	}
	if ((indx = findname(string, "fourth", bufpp, lp)) == -1)
		return (-1);
	mib[3] = indx;
	*typep = lp->list[indx].ctl_type;
	return (4);
}

/*
E 4
 * Scan a list of names searching for a particular name.
 */
findname(string, level, bufp, namelist)
	char *string;
	char *level;
	char **bufp;
	struct list *namelist;
{
	char *name;
	int i;

	if (namelist->list == 0 || (name = strsep(bufp, ".")) == NULL) {
		fprintf(stderr, "%s: incomplete specification\n", string);
		return (-1);
	}
	for (i = 0; i < namelist->size; i++)
D 4
		if (!strcmp(name, namelist->list[i]))
E 4
I 4
D 6
		if (!strcmp(name, namelist->list[i].ctl_name))
E 6
I 6
		if (namelist->list[i].ctl_name != NULL &&
		    strcmp(name, namelist->list[i].ctl_name) == 0)
E 6
E 4
			break;
	if (i == namelist->size) {
		fprintf(stderr, "%s level name %s in %s is invalid\n",
		    level, name, string);
		return (-1);
	}
	return (i);
}

usage()
{

D 3
	(void)fprintf(stderr, "usage:\t%s\n\t%s\n\t%s\n",
	    "sysctl [-w] variable ...", "sysctl -a", "sysctl -A");
E 3
I 3
	(void)fprintf(stderr, "usage:\t%s\n\t%s\n\t%s\n\t%s\n",
	    "sysctl [-n] variable ...", "sysctl [-n] -w variable=value ...",
	    "sysctl [-n] -a", "sysctl [-n] -A");
E 3
	exit(1);
}
E 1
