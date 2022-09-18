h59983
s 00002/00002/01036
d D 8.4 93/10/01 14:25:40 torek 10 9
c 1.38: memory-error should still be found first
e
s 00012/00010/01026
d D 8.3 93/09/30 15:37:44 torek 9 8
c 1.36, 1.37: make parsedisk global
e
s 00043/00007/00993
d D 8.2 93/09/27 13:56:11 torek 8 7
c 1.33: Ignore rom property "aliases" (found on the IPX).
c 1.34: don't need LBL diskless hack anymore
c 1.35: add romgetcursoraddr, and move it and rominterpret into ifdef RCONSOLE
e
s 00002/00002/00998
d D 8.1 93/06/11 15:15:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00995
d D 7.5 93/05/27 20:57:20 torek 6 5
c 1.32: make GENERIC code compile
e
s 00240/00163/00758
d D 7.4 93/04/20 21:10:41 torek 5 3
c update from elf: lots of boot cleanup; bootpath and bootdv
e
s 00239/00162/00759
d R 7.4 93/04/20 21:07:45 torek 4 3
c update from elf: lots of boot cleanup; bootpath and bootdv
e
s 00015/00015/00906
d D 7.3 92/10/11 12:57:03 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00916
d D 7.2 92/07/21 16:54:16 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00916/00000/00000
d D 7.1 92/07/13 00:44:27 torek 1 0
c date and time created 92/07/13 00:44:27 by torek
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 5
 *	California, Lawrence Berkeley Laboratories.
E 5
I 5
 *	California, Lawrence Berkeley Laboratory.
E 5
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 5
 * from: $Header: autoconf.c,v 1.23 92/07/10 22:35:23 torek Exp $ (LBL)
E 5
I 5
D 6
 * from: $Header: autoconf.c,v 1.31 93/04/07 01:34:47 torek Exp $ (LBL)
E 6
I 6
D 8
 * from: $Header: autoconf.c,v 1.32 93/05/28 03:55:59 torek Exp $ (LBL)
E 8
I 8
D 9
 * from: $Header: autoconf.c,v 1.35 93/09/27 00:50:04 torek Exp $ (LBL)
E 9
I 9
D 10
 * from: $Header: autoconf.c,v 1.37 93/09/28 07:19:48 leres Exp $ (LBL)
E 10
I 10
 * from: $Header: autoconf.c,v 1.38 93/10/01 21:24:51 torek Exp $ (LBL)
E 10
E 9
E 8
E 6
E 5
 */

D 3
#include "sys/param.h"
#include "sys/map.h"
#include "sys/buf.h"
#include "sys/disklabel.h"
#include "sys/device.h"
#include "sys/dkstat.h"
#include "sys/conf.h"
#include "sys/dmap.h"
#include "sys/reboot.h"
#include "sys/socket.h"
#include "sys/systm.h"
E 3
I 3
#include <sys/param.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/disklabel.h>
#include <sys/device.h>
I 5
#include <sys/disk.h>
E 5
#include <sys/dkstat.h>
#include <sys/conf.h>
#include <sys/dmap.h>
#include <sys/reboot.h>
#include <sys/socket.h>
#include <sys/systm.h>
E 3

D 3
#include "net/if.h"
E 3
I 3
#include <net/if.h>
E 3

D 3
#include "machine/autoconf.h"
#include "machine/bsd_openprom.h"
#include "machine/cpu.h"
E 3
I 3
#include <machine/autoconf.h>
#include <machine/bsd_openprom.h>
#include <machine/cpu.h>
E 3

D 5
#ifndef	FS_NFS		/* XXX */
#define	FS_NFS	100	/* XXX */
#endif			/* XXX */

E 5
/*
 * The following several variables are related to
 * the configuration process, and are used in initializing
 * the machine.
 */
int	cold;		/* if 1, still working on cold-start */
int	dkn;		/* number of iostat dk numbers assigned so far */
D 5
int	cpuspeed = 10;	/* relative cpu speed */
E 5
int	fbnode;		/* node ID of ROM's console frame buffer */
int	optionsnode;	/* node ID of ROM's options */

D 5
extern struct promvec *promvec;
E 5
I 5
extern	struct promvec *promvec;
E 5

static	int rootnode;
D 5
int	findroot();
static	struct	bootinfo *findbootdev();
E 5
I 5
int	findroot __P((void));
void	setroot __P((void));
static	int getstr __P((char *, int));
static	int findblkmajor __P((struct dkdevice *));
static	struct device *getdisk __P((char *, int, int, dev_t *));
D 9
static	struct device *parsedisk __P((char *, int, int, dev_t *));
E 9
E 5

D 5
static	struct bootinfo {
	char	name[16];	/* device name */
	int	val[3];		/* up to 3 values */
	int	type;		/* FS type */
	caddr_t	data;		/* FS dependant info */
} bootinfo;
E 5
I 5
struct	bootpath bootpath[8];
E 5

D 5

E 5
/*
 * Most configuration on the SPARC is done by matching OPENPROM Forth
 * device names with our internal names.
 */
int
matchbyname(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{

	return (strcmp(cf->cf_driver->cd_name, *(char **)aux) == 0);
}

/*
 * Convert hex ASCII string to a value.  Returns updated pointer.
 * Depends on ASCII order (this *is* machine-dependent code, you know).
 */
static char *
str2hex(str, vp)
	register char *str;
	register int *vp;
{
	register int v, c;

	for (v = 0;; v = v * 16 + c, str++) {
		c = *(u_char *)str;
		if (c <= '9') {
			if ((c -= '0') < 0)
				break;
		} else if (c <= 'F') {
			if ((c -= 'A' - 10) < 10)
				break;
		} else if (c <= 'f') {
			if ((c -= 'a' - 10) < 10)
				break;
		} else
			break;
	}
	*vp = v;
	return (str);
}

/*
 * locore.s code calls bootstrap() just before calling main(), after double
 * mapping the kernel to high memory and setting up the trap base register.
 * We must finish mapping the kernel properly and glean any bootstrap info.
 */
void
bootstrap()
{
D 5
	register char *cp, *bp, *ep;
	register int i;
E 5
I 5
	register char *cp, *pp;
	register struct bootpath *bp;
	int v0val[3];
E 5
	int nmmu, ncontext, node;
#ifdef KGDB
	extern int kgdb_debug_panic;
#endif
D 5
	extern char *rindex(const char *, int);
E 5

	node = findroot();
	nmmu = getpropint(node, "mmu-npmg", 128);
	ncontext = getpropint(node, "mmu-nctx", 8);
	pmap_bootstrap(nmmu, ncontext);
#ifdef KGDB
	zs_kgdb_init();			/* XXX */
#endif
	/*
	 * On SS1s, promvec->pv_v0bootargs->ba_argv[1] contains the flags
	 * that were given after the boot command.  On SS2s, pv_v0bootargs
	 * is NULL but *promvec->pv_v2bootargs.v2_bootargs points to
	 * "vmunix -s" or whatever.
	 * ###	DO THIS BEFORE pmap_boostrap?
	 */
I 5
	bp = bootpath;
E 5
	if (promvec->pv_romvec_vers < 2) {
		/* Grab boot device name and values. */
		cp = (*promvec->pv_v0bootargs)->ba_argv[0];
		if (cp != NULL) {
D 5
			bp = bootinfo.name;
			ep = &bootinfo.name[sizeof(bootinfo.name)];
			while (*cp != '(' && *cp != '\0' && bp < ep - 1)
				*bp++ = *cp++;
			*bp = '\0';
E 5
I 5
			/* Kludge something up */
			pp = cp + 2;
			v0val[0] = v0val[1] = v0val[2] = 0;
			if (*pp == '(' &&
			    *(pp = str2hex(++pp, &v0val[0])) == ',' &&
			    *(pp = str2hex(++pp, &v0val[1])) == ',')
				(void)str2hex(++pp, &v0val[2]);
E 5

D 5
			if (*cp == '(' &&
			    *(cp = str2hex(++cp, &bootinfo.val[0])) == ',' &&
			    *(cp = str2hex(++cp, &bootinfo.val[1])) == ',')
				(void)str2hex(++cp, &bootinfo.val[2]);
E 5
I 5
			/* Assume sbus0 */
			strcpy(bp->name, "sbus");
			bp->val[0] = 0;
			++bp;

			if (cp[0] == 'l' && cp[1] == 'e') {
				/* le */
				strcpy(bp->name, "le");
				bp->val[0] = -1;
				bp->val[1] = v0val[0];
			} else {
				/* sd or maybe st; assume espN */
				strcpy(bp->name, "esp");
				bp->val[0] = -1;
				bp->val[1] = v0val[0];

/* XXX map target 0 to 3, 3 to 0. Should really see how the prom is configed */
#define CRAZYMAP(v) ((v) == 3 ? 0 : (v) == 0 ? 3 : (v))

				++bp;
				bp->name[0] = cp[0];
				bp->name[1] = cp[1];
				bp->name[2] = '\0';
				bp->val[0] = CRAZYMAP(v0val[1]);
				bp->val[1] = v0val[2];
			}
E 5
		}

		/* Setup pointer to boot flags */
		cp = (*promvec->pv_v0bootargs)->ba_argv[1];
		if (cp == NULL || *cp != '-')
			return;
	} else {
D 5
		/* Grab boot device name and values. */
E 5
I 5
		/* Grab boot path */
E 5
		cp = *promvec->pv_v2bootargs.v2_bootpath;
D 5
		if (cp != NULL && (cp = rindex(cp, '/')) != NULL) {
E 5
I 5
		while (cp != NULL && *cp == '/') {
			/* Step over '/' */
E 5
			++cp;
D 5
			bp = bootinfo.name;
			ep = &bootinfo.name[sizeof(bootinfo.name)];
			while (*cp != '@' && *cp != '\0' && bp < ep - 1)
				*bp++ = *cp++;
			*bp = '\0';
E 5
I 5
			/* Extract name */
			pp = bp->name;
			while (*cp != '@' && *cp != '/' && *cp != '\0')
				*pp++ = *cp++;
			*pp = '\0';
E 5

D 5
			if (*cp == '@' &&
			    *(cp = str2hex(++cp, &bootinfo.val[0])) == ',' &&
			    *(cp = str2hex(++cp, &bootinfo.val[1])) == ',')
				(void)str2hex(++cp, &bootinfo.val[2]);
E 5
I 5
			if (*cp == '@') {
				cp = str2hex(++cp, &bp->val[0]);
				if (*cp == ',')
					cp = str2hex(++cp, &bp->val[1]);
			}
			++bp;
E 5
		}

		/* Setup pointer to boot flags */
		cp = *promvec->pv_v2bootargs.v2_bootargs;
		if (cp == NULL)
			return;
		while (*cp != '-')
			if (*cp++ == '\0')
				return;
	}
	for (;;) {
		switch (*++cp) {

		case '\0':
			return;

		case 'a':
			boothowto |= RB_ASKNAME;
			break;

		case 'b':
			boothowto |= RB_DFLTROOT;
			break;

		case 'd':	/* kgdb - always on zs	XXX */
#ifdef KGDB
			boothowto |= RB_KDB;	/* XXX unused */
			kgdb_debug_panic = 1;
			kgdb_connect(1);
#else
			printf("kernel not compiled with KGDB\n");
#endif
			break;

		case 's':
			boothowto |= RB_SINGLE;
			break;
		}
	}
}

/*
 * Determine mass storage and memory configuration for a machine.
 * We get the PROM's root device and make sure we understand it, then
 * attach it as `mainbus0'.  We also set up to handle the PROM `sync'
 * command.
 */
configure()
{
	register int node;
	register char *cp;
	struct romaux ra;
	void sync_crash();
D 5
#ifdef NFS
	register struct bootinfo *bi;
	extern int (*mountroot)(), nfs_mountroot();
#endif
E 5

	node = findroot();
	cp = getpropstring(node, "device_type");
	if (strcmp(cp, "cpu") != 0) {
		printf("PROM root device type = %s\n", cp);
		panic("need CPU as root");
	}
	*promvec->pv_synchook = sync_crash;
	ra.ra_node = node;
	ra.ra_name = cp = "mainbus";
	if (!config_rootfound(cp, (void *)&ra))
		panic("mainbus not configured");
D 5
	(void) spl0();
E 5
I 5
	(void)spl0();
	if (bootdv)
		printf("Found boot device %s\n", bootdv->dv_xname);
E 5
	cold = 0;
D 5
#ifdef NFS
	if (boothowto & RB_ASKNAME) {
		char ans[100];

		printf("nfs root? (y/n) [n] ");
		gets(ans);
		if (ans[0] == 'y')
			mountroot = nfs_mountroot;
	} else if ((bi = findbootdev()) != NULL && bi->type == FS_NFS) {
		mountroot = nfs_mountroot;
#ifdef LBL
		lbl_diskless_setup();
#endif /* LBL */
	}
#endif /* NFS */
#if GENERIC
	if ((boothowto & RB_ASKNAME) == 0)
		setroot();
	setconf();
#else
E 5
	setroot();
D 5
#endif
E 5
	swapconf();
I 5
	dumpconf();
E 5
}

/*
 * Console `sync' command.  SunOS just does a `panic: zero' so I guess
 * no one really wants anything fancy...
 */
void
sync_crash()
{

	panic("PROM sync command");
}

char *
clockfreq(freq)
	register int freq;
{
	register char *p;
	static char buf[10];

	freq /= 1000;
	sprintf(buf, "%d", freq / 1000);
	freq %= 1000;
	if (freq) {
		freq += 1000;	/* now in 1000..1999 */
		p = buf + strlen(buf);
		sprintf(p, "%d", freq);
		*p = '.';	/* now buf = %d.%3d */
	}
	return (buf);
}

/* ARGSUSED */
static int
mbprint(aux, name)
	void *aux;
	char *name;
{
	register struct romaux *ra = aux;

	if (name)
		printf("%s at %s", ra->ra_name, name);
	if (ra->ra_paddr)
		printf(" %saddr 0x%x", ra->ra_iospace ? "io" : "",
		    (int)ra->ra_paddr);
	return (UNCONF);
}

int
findroot()
{
	register int node;

	if ((node = rootnode) == 0 && (node = nextsibling(0)) == 0)
		panic("no PROM root device");
	rootnode = node;
	return (node);
}

/*
 * Given a `first child' node number, locate the node with the given name.
 * Return the node number, or 0 if not found.
 */
int
findnode(first, name)
	int first;
	register char *name;
{
	register int node;

	for (node = first; node; node = nextsibling(node))
		if (strcmp(getpropstring(node, "name"), name) == 0)
			return (node);
	return (0);
}

/*
 * Fill in a romaux.  Returns 1 on success, 0 if the register property
 * was not the right size.
 */
int
romprop(rp, cp, node)
	register struct romaux *rp;
	const char *cp;
	register int node;
{
	register int len;
	union { char regbuf[64]; int ireg[3]; } u;
	static const char pl[] = "property length";

	len = getprop(node, "reg", (void *)u.regbuf, sizeof u.regbuf);
	if (len < 12) {
		printf("%s \"reg\" %s = %d (need 12)\n", cp, pl, len);
		return (0);
	}
	if (len > 12)
		printf("warning: %s \"reg\" %s %d > 12, excess ignored\n",
		    cp, pl, len);
	rp->ra_node = node;
	rp->ra_name = cp;
	rp->ra_iospace = u.ireg[0];
	rp->ra_paddr = (caddr_t)u.ireg[1];
	rp->ra_len = u.ireg[2];
	rp->ra_vaddr = (caddr_t)getpropint(node, "address", 0);
	len = getprop(node, "intr", (void *)&rp->ra_intr, sizeof rp->ra_intr);
	if (len == -1)
		len = 0;
	if (len & 7) {
		printf("%s \"intr\" %s = %d (need multiple of 8)\n",
		    cp, pl, len);
		len = 0;
	}
	rp->ra_nintr = len >>= 3;
	/* SPARCstation interrupts are not hardware-vectored */
	while (--len >= 0) {
		if (rp->ra_intr[len].int_vec) {
			printf("WARNING: %s interrupt %d has nonzero vector\n",
			    cp, len);
			break;
		}
	}
	return (1);
}

/*
 * Attach the mainbus.
 *
 * Our main job is to attach the CPU (the root node we got in configure())
 * and iterate down the list of `mainbus devices' (children of that node).
 * We also record the `node id' of the default frame buffer, if any.
 */
static void
mainbus_attach(parent, dev, aux)
	struct device *parent, *dev;
	void *aux;
{
	register int node0, node;
	register const char *cp, *const *ssp, *sp;
#define L1A_HACK		/* XXX hack to allow L1-A during autoconf */
#ifdef L1A_HACK
	int nzs = 0, audio = 0;
#endif
	struct romaux ra;
	static const char *const special[] = {
		/* find these first (end with empty string) */
I 10
		"memory-error",	/* as early as convenient, in case of error */
E 10
D 8
		"memory-error", "eeprom", "counter-timer", "",
E 8
I 8
		"eeprom",
		"counter-timer",
D 10
		"memory-error",
E 10
		"",
E 8

		/* ignore these (end with NULL) */
D 8
		"options", "packages", "openprom", "memory", "virtual-memory",
		"interrupt-enable", NULL
E 8
I 8
		"aliases",
		"interrupt-enable",
		"memory",
		"openprom",
		"options",
		"packages",
		"virtual-memory",
		NULL
E 8
	};

	printf("\n");

	/* configure the cpu */
	node = ((struct romaux *)aux)->ra_node;
	ra.ra_node = node;
	ra.ra_name = cp = "cpu";
	ra.ra_paddr = 0;
	config_found(dev, (void *)&ra, mbprint);

	/* remember which frame buffer, if any, is to be /dev/fb */
	fbnode = getpropint(node, "fb", 0);

	/* Find the "options" node */
	node0 = firstchild(node);
	optionsnode = findnode(node0, "options");
	if (optionsnode == 0)
		panic("no options in OPENPROM");

I 5
	/* Start at the beginning of the bootpath */
	ra.ra_bp = bootpath;

E 5
	/*
	 * Locate and configure the ``early'' devices.  These must be
	 * configured before we can do the rest.  For instance, the
	 * EEPROM contains the Ethernet address for the LANCE chip.
	 * If the device cannot be located or configured, panic.
	 */
	for (ssp = special; *(sp = *ssp) != 0; ssp++) {
		if ((node = findnode(node0, sp)) == 0) {
			printf("could not find %s in OPENPROM\n", sp);
			panic(sp);
		}
		if (!romprop(&ra, sp, node) ||
		    !config_found(dev, (void *)&ra, mbprint))
			panic(sp);
	}

	/*
	 * Configure the rest of the devices, in PROM order.  Skip
	 * PROM entries that are not for devices, or which must be
	 * done before we get here.
	 */
	for (node = node0; node; node = nextsibling(node)) {
		cp = getpropstring(node, "name");
		for (ssp = special; (sp = *ssp) != NULL; ssp++)
			if (strcmp(cp, sp) == 0)
				break;
		if (sp == NULL && romprop(&ra, cp, node)) {
#ifdef L1A_HACK
			if (strcmp(cp, "audio") == 0)
				audio = 1;
			if (strcmp(cp, "zs") == 0)
				nzs++;
			if (audio && nzs >= 2)
				(void) splx(11 << 8);	/* XXX */
#endif
			(void) config_found(dev, (void *)&ra, mbprint);
		}
	}
}

struct cfdriver mainbuscd =
    { NULL, "mainbus", matchbyname, mainbus_attach,
      DV_DULL, sizeof(struct device) };

/*
 * findzs() is called from the zs driver (which is, at least in theory,
 * generic to any machine with a Zilog ZSCC chip).  It should return the
 * address of the corresponding zs channel.  It may not fail, and it
 * may be called before the VM code can be used.  Here we count on the
 * FORTH PROM to map in the required zs chips.
 */
void *
findzs(zs)
	int zs;
{
	register int node, addr;

	node = firstchild(findroot());
	while ((node = findnode(node, "zs")) != 0) {
		if (getpropint(node, "slave", -1) == zs) {
			if ((addr = getpropint(node, "address", 0)) == 0)
				panic("findzs: zs%d not mapped by PROM", zs);
			return ((void *)addr);
		}
		node = nextsibling(node);
	}
	panic("findzs: cannot find zs%d", zs);
	/* NOTREACHED */
}

int
makememarr(ap, max, which)
	register struct memarr *ap;
	int max, which;
{
	struct v2rmi {
		int	zero;
		int	addr;
		int	len;
	} v2rmi[200];		/* version 2 rom meminfo layout */
#define	MAXMEMINFO (sizeof(v2rmi) / sizeof(*v2rmi))
	register struct v0mlist *mp;
	register int i, node, len;
	char *prop;

	switch (i = promvec->pv_romvec_vers) {

	case 0:
		/*
		 * Version 0 PROMs use a linked list to describe these
		 * guys.
		 */
		switch (which) {

		case MEMARR_AVAILPHYS:
			mp = *promvec->pv_v0mem.v0_physavail;
			break;

		case MEMARR_TOTALPHYS:
			mp = *promvec->pv_v0mem.v0_phystot;
			break;

		default:
			panic("makememarr");
		}
		for (i = 0; mp != NULL; mp = mp->next, i++) {
			if (i >= max)
				goto overflow;
			ap->addr = (u_int)mp->addr;
			ap->len = mp->nbytes;
			ap++;
		}
		break;

	default:
		printf("makememarr: hope version %d PROM is like version 2\n",
		    i);
		/* FALLTHROUGH */

	case 2:
		/*
		 * Version 2 PROMs use a property array to describe them.
		 */
		if (max > MAXMEMINFO) {
			printf("makememarr: limited to %d\n", MAXMEMINFO);
			max = MAXMEMINFO;
		}
		if ((node = findnode(firstchild(findroot()), "memory")) == 0)
			panic("makememarr: cannot find \"memory\" node");
		switch (which) {

		case MEMARR_AVAILPHYS:
			prop = "available";
			break;

		case MEMARR_TOTALPHYS:
			prop = "reg";
			break;

		default:
			panic("makememarr");
		}
		len = getprop(node, prop, (void *)v2rmi, sizeof v2rmi) /
		    sizeof(struct v2rmi);
		for (i = 0; i < len; i++) {
			if (i >= max)
				goto overflow;
			ap->addr = v2rmi[i].addr;
			ap->len = v2rmi[i].len;
			ap++;
		}
		break;
	}

	/*
	 * Success!  (Hooray)
	 */
	if (i == 0)
		panic("makememarr: no memory found");
	return (i);

overflow:
	/*
	 * Oops, there are more things in the PROM than our caller
	 * provided space for.  Truncate any extras.
	 */
	printf("makememarr: WARNING: lost some memory\n");
	return (i);
}

/*
 * Internal form of getprop().  Returns the actual length.
 */
int
getprop(node, name, buf, bufsiz)
	int node;
	char *name;
	void *buf;
	register int bufsiz;
{
	register struct nodeops *no;
	register int len;

	no = promvec->pv_nodeops;
	len = no->no_proplen(node, name);
	if (len > bufsiz) {
		printf("node %x property %s length %d > %d\n",
		    node, name, len, bufsiz);
#ifdef DEBUG
		panic("getprop");
#else
		return (0);
#endif
	}
	no->no_getprop(node, name, buf);
	return (len);
}

/*
 * Return a string property.  There is a (small) limit on the length;
 * the string is fetched into a static buffer which is overwritten on
 * subsequent calls.
 */
char *
getpropstring(node, name)
	int node;
	char *name;
{
	register int len;
	static char stringbuf[32];

	len = getprop(node, name, (void *)stringbuf, sizeof stringbuf - 1);
	stringbuf[len] = '\0';	/* usually unnecessary */
	return (stringbuf);
}

/*
 * Fetch an integer (or pointer) property.
 * The return value is the property, or the default if there was none.
 */
int
getpropint(node, name, deflt)
	int node;
	char *name;
	int deflt;
{
	register int len;
	char intbuf[16];

	len = getprop(node, name, (void *)intbuf, sizeof intbuf);
	if (len != 4)
		return (deflt);
	return (*(int *)intbuf);
}

/*
 * OPENPROM functions.  These are here mainly to hide the OPENPROM interface
 * from the rest of the kernel.
 */
int
firstchild(node)
	int node;
{

	return (promvec->pv_nodeops->no_child(node));
}

int
nextsibling(node)
	int node;
{

	return (promvec->pv_nodeops->no_nextnode(node));
}

I 8
#ifdef RCONSOLE
E 8
/* Pass a string to the FORTH PROM to be interpreted */
void
rominterpret(s)
	register char *s;
{

	if (promvec->pv_romvec_vers < 2)
		promvec->pv_fortheval.v0_eval(strlen(s), s);
	else
		promvec->pv_fortheval.v2_eval(s);
}

I 8
/*
 * Try to figure out where the PROM stores the cursor row & column
 * variables.  Returns nonzero on error.
 */
int
romgetcursoraddr(rowp, colp)
	register int **rowp, **colp;
{
	char buf[100];

	/*
	 * line# and column# are global in older proms (rom vector < 2)
	 * and in some newer proms.  They are local in version 2.9.  The
	 * correct cutoff point is unknown, as yet; we use 2.9 here.
	 */
	if (promvec->pv_romvec_vers < 2 || promvec->pv_printrev < 0x00020009)
		sprintf(buf,
		    "' line# >body >user %x ! ' column# >body >user %x !",
		    rowp, colp);
	else
		sprintf(buf,
		    "stdout @ is my-self addr line# %x ! addr column# %x !",
		    rowp, colp);
	*rowp = *colp = NULL;
	rominterpret(buf);
	return (*rowp == NULL || *colp == NULL);
}
#endif

E 8
volatile void
romhalt()
{

	promvec->pv_halt();
	panic("PROM exit failed");
}

volatile void
romboot(str)
	char *str;
{

	promvec->pv_reboot(str);
	panic("PROM boot failed");
}

callrom()
{

#ifdef notdef		/* sun4c FORTH PROMs do this for us */
	fb_unblank();
#endif
	promvec->pv_abort();
}

/*
 * Configure swap space and related parameters.
 */
swapconf()
{
	register struct swdevt *swp;
	register int nblks;

D 5
	for (swp = swdevt; swp->sw_dev; swp++)
E 5
I 5
	for (swp = swdevt; swp->sw_dev != NODEV; swp++)
E 5
		if (bdevsw[major(swp->sw_dev)].d_psize) {
			nblks =
			  (*bdevsw[major(swp->sw_dev)].d_psize)(swp->sw_dev);
			if (nblks != -1 &&
			    (swp->sw_nblks == 0 || swp->sw_nblks > nblks))
				swp->sw_nblks = nblks;
		}
D 5
	dumpconf();
E 5
}

D 5
#define	DOSWAP			/* Change swdevt, argdev, and dumpdev too */
E 5
I 5
#define	DOSWAP			/* Change swdevt and dumpdev too */
E 5
u_long	bootdev;		/* should be dev_t, but not until 32 bits */

D 5
static	char devname[][2] = {
	0,0,		/* 0 = xx */
};

E 5
#define	PARTITIONMASK	0x7
#define	PARTITIONSHIFT	3

I 5
static int
findblkmajor(dv)
	register struct dkdevice *dv;
{
	register int i;

	for (i = 0; i < nblkdev; ++i)
		if ((void (*)(struct buf *))bdevsw[i].d_strategy ==
		    dv->dk_driver->d_strategy)
			return (i);

	return (-1);
}

static struct device *
getdisk(str, len, defpart, devp)
	char *str;
	int len, defpart;
	dev_t *devp;
{
	register struct device *dv;

	if ((dv = parsedisk(str, len, defpart, devp)) == NULL) {
		printf("use one of:");
		for (dv = alldevs; dv != NULL; dv = dv->dv_next)
			if (dv->dv_class == DV_DISK)
				printf(" %s[a-h]", dv->dv_xname);
		printf("\n");
	}
	return (dv);
}

D 9
static struct device *
E 9
I 9
struct device *
E 9
parsedisk(str, len, defpart, devp)
	char *str;
	int len, defpart;
	dev_t *devp;
{
	register struct device *dv;
D 9
	register char *cp;
E 9
I 9
	register char *cp, c;
E 9
	int majdev, mindev, part;

	if (len == 0)
		return (NULL);
	cp = str + len - 1;
D 9
	if (*cp >= 'a' && *cp <= 'h') {
		part = *cp - 'a';
		*cp-- = '\0';
E 9
I 9
	c = *cp;
	if (c >= 'a' && c <= 'h') {
		part = c - 'a';
		*cp = '\0';
E 9
	} else
		part = defpart;

D 9
	for (dv = alldevs; dv != NULL; dv = dv->dv_next)
E 9
I 9
	for (dv = alldevs; dv != NULL; dv = dv->dv_next) {
E 9
		if (dv->dv_class == DV_DISK &&
		    strcmp(str, dv->dv_xname) == 0) {
			majdev = findblkmajor((struct dkdevice *)dv);
			if (majdev < 0)
				panic("parsedisk");
			mindev = (dv->dv_unit << PARTITIONSHIFT) + part;
			*devp = makedev(majdev, mindev);
D 9
			return (dv);
E 9
I 9
			break;
E 9
		}
I 9
	}
E 9

D 9
	return (NULL);
E 9
I 9
	*cp = c;
	return (dv);
E 9
}

E 5
/*
 * Attempt to find the device from which we were booted.
 * If we can do so, and not instructed not to do so,
 * change rootdev to correspond to the load device.
 */
I 5
void
E 5
setroot()
{
D 5
#ifdef notyet
	struct swdevt *swp;
E 5
I 5
	register struct swdevt *swp;
	register struct device *dv;
	register int len, majdev, mindev, part;
	dev_t nrootdev, nswapdev;
	char buf[128];
#ifdef DOSWAP
	dev_t temp;
#endif
#ifdef NFS
	extern int (*mountroot)(), nfs_mountroot();
#endif
E 5

D 5
	if (boothowto & RB_DFLTROOT ||
	    (bootdev & B_MAGICMASK) != (u_long)B_DEVMAGIC)
E 5
I 5
	if (boothowto & RB_ASKNAME) {
		for (;;) {
			printf("root device? ");
			len = getstr(buf, sizeof(buf));
#ifdef GENERIC
			if (len > 0 && buf[len - 1] == '*') {
				buf[--len] = '\0';
				dv = getdisk(buf, len, 1, &nrootdev);
				if (dv != NULL) {
					bootdv = dv;
					nswapdev = nrootdev;
D 6
					swaponroot++;
					goto setswap;
E 6
I 6
					goto gotswap;
E 6
				}
			}
#endif
			dv = getdisk(buf, len, 0, &nrootdev);
			if (dv != NULL) {
				bootdv = dv;
				break;
			}
		}
		for (;;) {
			printf("swap device (default %sb)? ", bootdv->dv_xname);
			len = getstr(buf, sizeof(buf));
			if (len == 0) {
				nswapdev = makedev(major(nrootdev),
				    (minor(nrootdev) & ~ PARTITIONMASK) | 1);
				break;
			}
			if (getdisk(buf, len, 1, &nswapdev) != NULL)
				break;
		}
I 6
#ifdef GENERIC
gotswap:
#endif
E 6
		rootdev = nrootdev;
		swapdev = nswapdev;
		dumpdev = nswapdev;		/* ??? */
		swdevt[0].sw_dev = nswapdev;
		swdevt[1].sw_dev = NODEV;
E 5
		return;
D 5
	majdev = (bootdev >> B_TYPESHIFT) & B_TYPEMASK;
	if (majdev > sizeof(devname) / sizeof(devname[0]))
E 5
I 5
	}

	/* XXX currently there's no way to set RB_DFLTROOT... */
	if (boothowto & RB_DFLTROOT || bootdv == NULL)
E 5
		return;
D 5
	adaptor = (bootdev >> B_ADAPTORSHIFT) & B_ADAPTORMASK;
	part = (bootdev >> B_PARTITIONSHIFT) & B_PARTITIONMASK;
	unit = (bootdev >> B_UNITSHIFT) & B_UNITMASK;
	/*
	 * First, find the controller type which support this device.
	 */
	for (hd = hp_dinit; hd->hp_driver; hd++)
		if (hd->hp_driver->d_name[0] == devname[majdev][0] &&
		    hd->hp_driver->d_name[1] == devname[majdev][1])
			break;
	if (hd->hp_driver == 0)
E 5
I 5

	switch (bootdv->dv_class) {

#ifdef NFS
	case DV_IFNET:
		mountroot = nfs_mountroot;
D 8
#ifdef LBL
		lbl_diskless_setup();
#endif
E 8
E 5
		return;
D 5
	/*
	 * Next, find the controller of that type corresponding to
	 * the adaptor number.
	 */
	for (hc = hp_cinit; hc->hp_driver; hc++)
		if (hc->hp_alive && hc->hp_unit == adaptor &&
		    hc->hp_driver == hd->hp_cdriver)
			break;
	if (hc->hp_driver == 0)
E 5
I 5
#endif

#if defined(FFS) || defined(LFS)
	case DV_DISK:
		majdev = findblkmajor((struct dkdevice *)bootdv);
		if (majdev < 0)
			return;
		part = 0;
		mindev = (bootdv->dv_unit << PARTITIONSHIFT) + part;
		break;
#endif

	default:
		printf("can't figure root, hope your kernel is right\n");
E 5
		return;
I 5
	}

E 5
	/*
D 5
	 * Finally, find the device in question attached to that controller.
	 */
	for (hd = hp_dinit; hd->hp_driver; hd++)
		if (hd->hp_alive && hd->hp_slave == unit &&
		    hd->hp_cdriver == hc->hp_driver &&
		    hd->hp_ctlr == hc->hp_unit)
			break;
	if (hd->hp_driver == 0)
		return;
	mindev = hd->hp_unit;
	/*
E 5
	 * Form a new rootdev
	 */
D 5
	mindev = (mindev << PARTITIONSHIFT) + part;
	orootdev = rootdev;
	rootdev = makedev(majdev, mindev);
E 5
I 5
	nrootdev = makedev(majdev, mindev);
E 5
	/*
	 * If the original rootdev is the same as the one
	 * just calculated, don't need to adjust the swap configuration.
	 */
D 5
	if (rootdev == orootdev)
E 5
I 5
	if (rootdev == nrootdev)
E 5
		return;

D 5
	printf("Changing root device to %c%c%d%c\n",
		devname[majdev][0], devname[majdev][1],
		mindev >> PARTITIONSHIFT, part + 'a');
E 5
I 5
	rootdev = nrootdev;
	printf("Changing root device to %s%c\n", bootdv->dv_xname, part + 'a');
E 5

#ifdef DOSWAP
	mindev &= ~PARTITIONMASK;
D 5
	for (swp = swdevt; swp->sw_dev; swp++) {
E 5
I 5
	temp = NODEV;
	for (swp = swdevt; swp->sw_dev != NODEV; swp++) {
E 5
		if (majdev == major(swp->sw_dev) &&
		    mindev == (minor(swp->sw_dev) & ~PARTITIONMASK)) {
			temp = swdevt[0].sw_dev;
			swdevt[0].sw_dev = swp->sw_dev;
			swp->sw_dev = temp;
			break;
		}
	}
D 5
	if (swp->sw_dev == 0)
E 5
I 5
	if (swp->sw_dev == NODEV)
E 5
		return;

	/*
D 5
	 * If argdev and dumpdev were the same as the old primary swap
	 * device, move them to the new primary swap device.
E 5
I 5
	 * If dumpdev was the same as the old primary swap device, move
	 * it to the new primary swap device.
E 5
	 */
	if (temp == dumpdev)
		dumpdev = swdevt[0].sw_dev;
D 5
	if (temp == argdev)
		argdev = swdevt[0].sw_dev;
E 5
#endif
D 5
#endif
E 5
}

D 5
/*
 * Return pointer to device we booted from. Return NULL if we can't
 * figure this out.
 * XXX currently only works for network devices.
 */

static struct bootinfo *
findbootdev()
{
	register struct bootinfo *bi;
	register char *bp;
	register int unit, controller;
	register struct ifnet *ifp;

	bi = &bootinfo;
	bp = bi->name;
printf("findbootdev: (v%d rom) trying \"%s(%x,%x,%x)\"... ",
    promvec->pv_romvec_vers, bp, bi->val[0], bi->val[1], bi->val[2]);

	/* Try network devices first */
	unit = bi->val[0];
	for (ifp = ifnet; ifp; ifp = ifp->if_next)
		if (unit == ifp->if_unit && strcmp(bp, ifp->if_name) == 0) {
printf("found \"%s%d\"\n", ifp->if_name, ifp->if_unit);
			bi->type = FS_NFS;
			bi->data = (caddr_t)ifp;
			return (bi);
		}
printf("not found\n");
	return (NULL);
}

gets(cp)
E 5
I 5
static int
getstr(cp, size)
E 5
	register char *cp;
I 5
	register int size;
E 5
{
	register char *lp;
	register int c;
I 5
	register int len;
E 5

	lp = cp;
I 5
	len = 0;
E 5
	for (;;) {
		c = cngetc();
		switch (c) {
		case '\n':
		case '\r':
			printf("\n");
			*lp++ = '\0';
D 5
			return;
E 5
I 5
			return (len);
E 5
		case '\b':
		case '\177':
		case '#':
D 5
			if (lp > cp) {
				lp--;
E 5
I 5
			if (len) {
				--len;
				--lp;
E 5
				printf(" \b ");
			}
			continue;
		case '@':
		case 'u'&037:
I 5
			len = 0;
E 5
			lp = cp;
D 5
			cnputc('\n');
E 5
I 5
			printf("\n");
E 5
			continue;
		default:
D 5
			if (c < ' ')
E 5
I 5
			if (len + 1 >= size || c < ' ') {
				printf("\007");
E 5
				continue;
D 5
			cnputc(c);
E 5
I 5
			}
			printf("%c", c);
			++len;
E 5
			*lp++ = c;
		}
	}
}
E 1
