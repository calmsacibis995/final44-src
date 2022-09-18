h56129
s 00001/00001/00258
d D 8.5 93/11/23 23:41:28 torek 11 10
c fix comment, Pinnacle is no longer secret
e
s 00003/00007/00256
d D 8.4 93/10/30 22:32:57 torek 10 9
c work around ss1+ hardware bug by moving cache enable to after autoconfig
e
s 00006/00004/00257
d D 8.3 93/09/30 15:40:05 torek 9 8
c 1.16: move cache enable into cpu configuration to save one output line and
c       to make booting go a bit faster.
e
s 00160/00079/00101
d D 8.2 93/09/27 14:01:10 torek 8 7
c new cpu decode, & fix for ss2 cache chip bug
e
s 00002/00002/00178
d D 8.1 93/06/11 15:16:24 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00179
d D 7.6 93/05/03 02:48:40 torek 6 5
c rm cpuspeed
e
s 00025/00004/00157
d D 7.5 93/04/27 07:35:30 torek 5 4
c set up cache info
e
s 00030/00016/00131
d D 7.4 93/04/20 23:05:33 torek 4 3
c update from elf: new world of sysclt
e
s 00005/00005/00142
d D 7.3 92/10/11 12:57:09 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00142
d D 7.2 92/07/21 16:54:23 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00142/00000/00000
d D 7.1 92/07/13 00:44:31 torek 1 0
c date and time created 92/07/13 00:44:31 by torek
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
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: cpu.c,v 1.8 92/06/17 05:22:01 torek Exp $ (LBL)
E 4
I 4
D 5
 * from: $Header: cpu.c,v 1.10 93/04/20 11:16:51 torek Exp $ (LBL)
E 5
I 5
D 6
 * from: $Header: cpu.c,v 1.11 93/04/27 14:34:42 torek Exp $ (LBL)
E 6
I 6
D 8
 * from: $Header: cpu.c,v 1.12 93/05/03 09:47:57 torek Exp $ (LBL)
E 8
I 8
D 9
 * from: $Header: cpu.c,v 1.15.1.1 93/09/27 20:59:04 torek Exp $ (LBL)
E 9
I 9
D 10
 * from: $Header: cpu.c,v 1.16.1.1 93/09/30 22:38:50 torek Exp $ (LBL)
E 10
I 10
 * from: $Header: cpu.c,v 1.18 93/10/31 05:28:13 torek Exp $ (LBL)
E 10
E 9
E 8
E 6
E 5
E 4
 */

D 3
#include "sys/param.h"
#include "sys/device.h"
E 3
I 3
#include <sys/param.h>
#include <sys/device.h>
E 3

D 3
#include "machine/autoconf.h"
#include "machine/cpu.h"
#include "machine/reg.h"
E 3
I 3
#include <machine/autoconf.h>
#include <machine/cpu.h>
#include <machine/reg.h>
I 8
#include <machine/trap.h>
E 8
E 3

I 5
#include <sparc/sparc/cache.h>

/* This is declared here so that you must include a CPU for the cache code. */
struct cacheinfo cacheinfo;

E 5
I 4
D 8
/* the following are used externally (sysctl_hw) */
E 8
I 8
/* The following are used externally (sysctl_hw). */
E 8
char	machine[] = "sparc";
D 8
char	cpu_model[80];
E 8
I 8
char	cpu_model[100];
E 8
D 6
int	cpuspeed;		/* XXX */
E 6

E 4
D 8
static char *psrtoname();
static char *fsrtoname();
E 8
I 8
/* The CPU configuration driver. */
static void cpu_attach __P((struct device *, struct device *, void *));
E 8

I 8
struct cfdriver cpucd =
    { NULL, "cpu", matchbyname, cpu_attach, DV_CPU, sizeof(struct device) };

static char *psrtoname __P((int, int, int, char *));
static char *fsrtoname __P((int, int, int, char *));

#define	IU_IMPL(psr)	((u_int)(psr) >> 28)
#define	IU_VERS(psr)	(((psr) >> 24) & 0xf)

#ifdef notdef
E 8
/*
I 8
 * IU implementations are parceled out to vendors (with some slight
 * glitches).  Printing these is cute but takes too much space.
 */
static char *iu_vendor[16] = {
	"Fujitsu",	/* and also LSI Logic */
	"ROSS",		/* ROSS (ex-Cypress) */
	"BIT",
	"LSIL",		/* LSI Logic finally got their own */
	"TI",		/* Texas Instruments */
	"Matsushita",
	"Philips",
	"Harvest",	/* Harvest VLSI Design Center */
	"SPEC",		/* Systems and Processes Engineering Corporation */
	"Weitek",
	"vendor#10",
	"vendor#11",
	"vendor#12",
	"vendor#13",
	"vendor#14",
	"vendor#15"
};
#endif

/*
E 8
D 5
 * Attach the CPU.  Right now we just print stuff like "Sun 4/65 (25 MHz)".
 * Eventually we will need more....
E 5
I 5
 * Attach the CPU.
D 8
 * Discover interesting goop about the virtual address cache.
E 8
I 8
 * Discover interesting goop about the virtual address cache
 * (slightly funny place to do it, but this is where it is to be found).
E 8
E 5
 */
static void
cpu_attach(parent, dev, aux)
	struct device *parent;
	struct device *dev;
	void *aux;
{
D 4
	register int node = ((struct romaux *)aux)->ra_node;
E 4
I 4
D 5
	register int node, clk;
E 5
I 5
	register int node, clk, i, l;
E 5
E 4
D 8
	register u_int psr, fver;
E 8
I 8
	register int impl, vers, fver;
E 8
I 4
	register char *fpuname;
E 4
	struct fpstate fpstate;
I 8
	char iubuf[40], fpbuf[40];
E 8

D 4
	psr = getpsr();
	printf(": %s (%s @ %s MHz), ", getpropstring(node, "name"),
	    psrtoname(psr), clockfreq(getpropint(node, "clock-frequency", 0)));
E 4
	/*
	 * Get the FSR and clear any exceptions.  If we do not unload
	 * the queue here and it is left over from a previous crash, we
D 4
	 * will panic in the first loadfpstate(), due to a sequence error.
E 4
I 4
	 * will panic in the first loadfpstate(), due to a sequence error,
	 * so we need to dump the whole state anyway.
E 4
	 *
D 4
	 * If there is no FPU, trap.c will advance over all the stores.
E 4
I 4
	 * If there is no FPU, trap.c will advance over all the stores,
	 * so we initialize fs_fsr here.
E 4
	 */
D 4
	fpstate.fs_fsr = 7 << FSR_VER_SHIFT;
E 4
I 4
	fpstate.fs_fsr = 7 << FSR_VER_SHIFT;	/* 7 is reserved for "none" */
E 4
	savefpstate(&fpstate);
	fver = (fpstate.fs_fsr >> FSR_VER_SHIFT) & (FSR_VER >> FSR_VER_SHIFT);
D 4
	if (fver == 7)
		printf("no FPU\n");
	else {
E 4
I 4
D 8
	psr = getpsr();
E 8
I 8
	i = getpsr();
	impl = IU_IMPL(i);
	vers = IU_VERS(i);
E 8
	if (fver != 7) {
E 4
		foundfpu = 1;
D 4
		printf("fpu = %s\n", fsrtoname(psr, fver));
	}
E 4
I 4
D 8
		fpuname = fsrtoname(psr, fver);
E 8
I 8
		fpuname = fsrtoname(impl, vers, fver, fpbuf);
E 8
	} else
		fpuname = "no";

	/* tell them what we have */
	node = ((struct romaux *)aux)->ra_node;
	clk = getpropint(node, "clock-frequency", 0);
	sprintf(cpu_model, "%s (%s @ %s MHz, %s FPU)",
D 8
	    getpropstring(node, "name"), psrtoname(psr),
	    clockfreq(clk), fpuname);
E 8
I 8
	    getpropstring(node, "name"),
	    psrtoname(impl, vers, fver, iubuf), clockfreq(clk), fpuname);
E 8
	printf(": %s\n", cpu_model);
D 6
	cpuspeed = clk / 1000000;	/* XXX */
E 6
I 5

	/*
	 * Fill in the cache info.  Note, vac-hwflush is spelled
	 * with an underscore on 4/75s.
	 */
	cacheinfo.c_totalsize = getpropint(node, "vac-size", 65536);
	cacheinfo.c_hwflush = getpropint(node, "vac_hwflush", 0) |
	    getpropint(node, "vac-hwflush", 0);
	cacheinfo.c_linesize = l = getpropint(node, "vac-linesize", 16);
	for (i = 0; (1 << i) < l; i++)
		/* void */;
	if ((1 << i) != l)
		panic("bad cache line size %d", l);
	cacheinfo.c_l2linesize = i;
I 8
	vactype = VAC_WRITETHROUGH;
D 9
	printf("%s: %d byte write-through cache, %d bytes/line, %cw flush\n",
	    dev->dv_xname, cacheinfo.c_totalsize, l,
	    cacheinfo.c_hwflush ? 'h' : 's');
E 9
E 8

D 8
	vactype = VAC_WRITETHROUGH;	/* ??? */
E 8
I 8
	/*
	 * Machines with "buserr-type" 1 have a bug in the cache
	 * chip that affects traps.  (I wish I knew more about this
	 * mysterious buserr-type variable....)
	 */
	if (getpropint(node, "buserr-type", 0) == 1) {
		kvm_uncache((caddr_t)trapbase, 1);
		printf("%s: cache chip bug; trap page uncached\n",
		    dev->dv_xname);
	}
I 9
D 10

	printf("%s: %d byte write-through, %d bytes/line, %cw flush ",
	    dev->dv_xname, cacheinfo.c_totalsize, l,
	    cacheinfo.c_hwflush ? 'h' : 's');
	cache_enable();
E 10
E 9
E 8
E 5
E 4
}

D 8
struct cfdriver cpucd =
    { NULL, "cpu", matchbyname, cpu_attach, DV_CPU, sizeof(struct device) };
E 8
I 8
/*
 * The following tables convert <IU impl, IU version, FPU version> triples
 * into names for the CPU and FPU chip.  In most cases we do not need to
 * inspect the FPU version to name the IU chip, but there is one exception
 * (for Tsunami), and this makes the tables the same.
 *
 * The table contents (and much of the structure here) are from Guy Harris.
 *
 * NOTE: we have Sun-4m cpu types here, even though this only runs on the
 * Sun-4c (yet)...
 */
struct info {
	u_char	valid;
	u_char	iu_impl;
	u_char	iu_vers;
	u_char	fpu_vers;
	char	*name;
};
E 8

I 8
#define	ANY	0xff	/* match any FPU version (or, later, IU version) */

static struct info iu_types[] = {
	{ 1, 0x0, 0x0, ANY, "MB86900/1A or L64801" },
	{ 1, 0x1, 0x0, ANY, "RT601 or L64811 v1" },
	{ 1, 0x1, 0x1, ANY, "RT601 or L64811 v2" },
	{ 1, 0x1, 0x3, ANY, "RT611" },
	{ 1, 0x1, 0xf, ANY, "RT620" },
	{ 1, 0x2, 0x0, ANY, "B5010" },
	{ 1, 0x4, 0x0,   0, "TMS390Z50 v0" },
	{ 1, 0x4, 0x1,   0, "TMS390Z50 v1" },
	{ 1, 0x4, 0x1,   4, "TMS390S10" },
	{ 1, 0x5, 0x0, ANY, "MN10501" },
	{ 1, 0x9, 0x0, ANY, "W8601/8701 or MB86903" },
	{ 0 }
};

E 8
static char *
D 8
psrtoname(psr)
	register u_int psr;
E 8
I 8
psrtoname(impl, vers, fver, buf)
	register int impl, vers, fver;
	char *buf;
E 8
{
D 8
	int impl = psr >> 28, vers = (psr >> 24) & 15;
E 8
I 8
	register struct info *p;
E 8

D 8
	switch (impl) {
E 8
I 8
	for (p = iu_types; p->valid; p++)
		if (p->iu_impl == impl && p->iu_vers == vers &&
		    (p->fpu_vers == fver || p->fpu_vers == ANY))
			return (p->name);
E 8

D 8
	case 0:
		if (vers == 0)
			return ("MB86900/1A or L64801");
		break;
E 8
I 8
	/* Not found. */
	sprintf(buf, "IU impl 0x%x vers 0x%x", impl, vers);
	return (buf);
}
E 8

D 8
	case 1:
		if (vers < 2)
			return ("CY7C601 or L64811");
		if (vers == 3)
			return ("CY7C611");
		break;
E 8
I 8
/* NB: table order matters here; specific numbers must appear before ANY. */
static struct info fpu_types[] = {
	/*
	 * Vendor 0, IU Fujitsu0.
	 */
	{ 1, 0x0, ANY, 0, "MB86910 or WTL1164/5" },
	{ 1, 0x0, ANY, 1, "MB86911 or WTL1164/5" },
	{ 1, 0x0, ANY, 2, "L64802 or ACT8847" },
	{ 1, 0x0, ANY, 3, "WTL3170/2" },
	{ 1, 0x0, ANY, 4, "L64804" },
E 8

D 8
	case 2:
		if (vers == 0)
			return ("B5010");
		break;
E 8
I 8
	/*
D 10
	 * Vendor 1, IU ROSS0/1.
E 10
I 10
	 * Vendor 1, IU ROSS0/1 or Pinnacle.
E 10
	 */
I 10
D 11
	{ 1, 0x1, 0xf, 0, "on-chip" },		/* Pinnacle (shhh) */
E 11
I 11
	{ 1, 0x1, 0xf, 0, "on-chip" },		/* Pinnacle */
E 11
E 10
	{ 1, 0x1, ANY, 0, "L64812 or ACT8847" },
	{ 1, 0x1, ANY, 1, "L64814" },
	{ 1, 0x1, ANY, 2, "TMS390C602A" },
	{ 1, 0x1, ANY, 3, "RT602 or WTL3171" },
E 8

D 8
	case 5:
		if (vers == 0)
			return ("MN10501");
		break;
	}
D 4
	return ("mystery cpu type");
E 4
I 4
	return ("???");
E 4
}
E 8
I 8
	/*
	 * Vendor 2, IU BIT0.
	 */
	{ 1, 0x2, ANY, 0, "B5010 or B5110/20 or B5210" },
E 8

D 8
static char *
fsrtoname(psr, fver)
	register u_int psr, fver;
{
E 8
I 8
	/*
	 * Vendor 4, Texas Instruments.
	 */
	{ 1, 0x4, ANY, 0, "on-chip" },		/* Viking */
	{ 1, 0x4, ANY, 4, "on-chip" },		/* Tsunami */
E 8

D 8
	switch (psr >> 28) {
E 8
I 8
	/*
	 * Vendor 5, IU Matsushita0.
	 */
	{ 1, 0x5, ANY, 0, "on-chip" },
E 8

D 8
	case 0:
		switch (fver) {
		case 0:
			return ("MB86910 or WTL1164/5");
		case 1:
			return ("MB86911 or WTL1164/5");
		case 2:
			return ("L64802 or ACT8847");
		case 3:
			return ("WTL3170/2");
		case 4:
			return ("L64804");
		}
		break;
E 8
I 8
	/*
	 * Vendor 9, Weitek.
	 */
	{ 1, 0x9, ANY, 3, "on-chip" },
E 8

D 8
	case 1:
		switch (fver) {
		case 0:
			return ("L64812 or ACT8847");
		case 1:
			return ("L64814");
		case 2:
			return ("TMS390C602A");
		case 3:
			return ("WTL3171");
		}
		break;
E 8
I 8
	{ 0 }
};
E 8

D 8
	case 2:
		if (fver == 0)
			return ("B5010 or B5110/20 or B5210");
		break;
E 8
I 8
static char *
fsrtoname(impl, vers, fver, buf)
	register int impl, vers, fver;
	char *buf;
{
	register struct info *p;
E 8

D 8
	case 5:
		if (fver == 0)
			return ("MN10501");
	}
D 4
	return ("mystery fpu type");
E 4
I 4
	return ("???");
E 8
I 8
	for (p = fpu_types; p->valid; p++)
		if (p->iu_impl == impl &&
		    (p->iu_vers == vers || p->iu_vers == ANY) &
		    p->fpu_vers == fver)
			return (p->name);
	sprintf(buf, "version %x", fver);
	return (buf);
E 8
E 4
}
E 1
