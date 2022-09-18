/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 **************************************************************************
 * HISTORY
 * $Log:	boot.c,v $
 * Revision 2.5  89/03/09  21:13:35  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  14:17:10  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/08  13:41:46  rvb
 * Save bootdev for open(), to serve as a default.
 * Changed interpretation of unit number field in boot device for
 * multiple controllers on the adpator;  changed to pass
 * parameters to loaded image in the argument list (as well as the
 * registers for compatibility) and added linkage parameters that
 * the debugger can use to return to the boot loader but regain
 * control on the first instruction of the progam next loaded.
 * [ V5.1(F8) ]
 * Cannot put r* into registers or changes will not be reflected
 * out.
 * Also fix up the way r9 is passed out.
 * Pass all registers to main() and have main return entry address.
 * Generalize boot spec to allow, xx()/mach, xx(n,[a..h])/mach,
 * xx([a..h])/mach, ...
 * 
 *
 * 12-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Boot MACH, not UNIX.
 *
 * 01-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_BOOT:  picked up the ULTRIX-32 boot options to pass in
 *	the boot unit in the second byte of R10 and the partition in
 *	the high 4 bits of R11 so so that these may be passed through
 *	to UNIX for use in determining the root device;
 *	CS_KDB:  changed copyunix() to save the symbol table after _end
 *	if bit 2 (04) was supplied in the boot flags and pass its
 *	top through to UNIX in R9.
 *
 * 20-Aug-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Allow code to be loaded directly into shared memory, by letting
 *	the high 16 bits of "howto" (r11) specify a 64k boundary foR
 *	loading to.
 *	Pass the correct major/minor as r10 to the program that was
 *	started.
 *
 **************************************************************************
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)boot.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/vm.h>
#include <a.out.h>
#include "saio.h"
#define MACH_KDB 1
#include <sys/reboot.h>

/*
 * Boot program... arguments passed in r10 and r11 determine
 * whether boot stops to ask for system name and which device
 * boot comes from.
 */


#define MACH	"mach"
char line[100] = MACH;
char bootresult[100];

extern	char	*openstr;
extern	int	unit_part_dev;
int	retry;
int	esym;

/*
 *  The original contents of these registers upon entry to the program 
 *  are made available as parameters here by the run-time startup code.
 */
main(r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,devtype,howto,ap)
{
	int io, i;
	register type, part, unit;
	register char *cp;
	register int ret;
	long atol();

#ifdef	lint
	howto = 0; devtype = 0;
#endif
	retry = 0; esym = 0;
#ifdef	JUSTASK
	howto = RB_ASKNAME|RB_SINGLE;
#endif
	for (;;) {
		if (howto & RB_ASKNAME) {
			printf("Boot: ");
			gets(line);
		} else
			printf("Boot: %s\n", line);
		openstr = bootresult;
		io = open(line, 0);
		if (io >= 0) {
			printf("Open: %s\n", bootresult);
			loadpcs();
			if (iob[io-3].i_ino.i_mode&IEXEC)
			    howto |= RB_KDB;
			devtype = unit_part_dev;
			devtype |= B_DEVMAGIC;
			if ((ret = copyunix(howto, devtype, io)) != -1) {
				r9 = esym;
				return ret;
			} else {
			   close(io);
			   howto = (howto&RB_KDB)|RB_SINGLE|RB_ASKNAME;
			}
		} else {
			printf("Errr: %s\n", bootresult);
		}
		if (++retry > 2)
			howto = RB_SINGLE|RB_ASKNAME;
	}
}

/*ARGSUSED*/
copyunix(howto, devtype, io)
	register howto, devtype, io;	/* howto=r11, devtype=r10 */
{
	struct exec x;
	register int i;
	char *addr;
	register char *ssym = 0;
	char *base = (char *) (howto & 0xffff0000); /* high 16 bits */
 
	if (badloc(base))
		base = 0;
	addr = base;

	i = read(io, (char *)&x, sizeof x);
	if (i != sizeof x ||
	    (x.a_magic != 0407 && x.a_magic != 0413 && x.a_magic != 0410)) {
		printf("Bad format\n");
		return -1;
	}
	if (base)
		printf("%x // ", base);
	printf("%d", x.a_text);
	if (x.a_magic == 0413 && lseek(io, 0x400, 0) == -1)
		goto shread;
	if (read(io, addr, x.a_text) != x.a_text)
		goto shread;
	addr += x.a_text;
	if (x.a_magic == 0413 || x.a_magic == 0410)
		while ((int)addr & CLOFSET)
			*addr++ = 0;
	printf("+%d", x.a_data);
	if (read(io, addr, x.a_data) != x.a_data)
		goto shread;
	addr += x.a_data;
	printf("+%d", x.a_bss);
	if ((howto&RB_KDB) && x.a_syms)
	{
		for (i = 0; i < x.a_bss; i++)
			*addr++ = 0;
		ssym = addr;
		*((int *)addr) = x.a_syms;
		addr += sizeof(x.a_syms);
		printf("[+%d", x.a_syms);
		if (read(io, addr, x.a_syms) != x.a_syms)
			goto shread;
		addr += x.a_syms;
		if (read(io, addr, sizeof(int)) != sizeof(int))
			goto shread;
		i = *((int *)addr) - sizeof(int);
		addr += sizeof(int);
		printf("+%d]", i);
		if (read(io, addr, i) != i)
			goto shread;
		addr += i;
		esym = ((int)(addr+sizeof(int)-1))&~(sizeof(int)-1);
		x.a_bss = 0;
	}
	else
		howto &= ~RB_KDB;
	/*
	 *  Zeroing the large extent of slop (below) has caused more problems
	 *  than it has solved in the past when loading large images that only
	 *  over-run the boot area because of it.  The kernel should no
	 *  longer depend on this...
	 */
	for (i = 0; i < x.a_bss; i++)
		*addr++ = 0;
	x.a_entry &= 0x7fffffff;
	x.a_entry = (long)(base+x.a_entry);
	io = esym;	/* XXX */
	/*
	 *  We now pass the various bootstrap parameters to the loaded
	 *  image via the argument list (as well as in the registers for
	 *  compatibility). 
	 *
	 *  arg1 = boot flags [R11]
	 *  arg2 = boot device [R10]
	 *  arg3 = start of symbol table (0 if not loaded)
	 *  arg4 = end of symbol table (0 if not loaded) [R9]
	 *  arg5 = transfer address from image (for indirect transfers)
	 *  arg6 = transfer address for next image pointer (a previously
	 *	   loaded program will use this to cause the transfer to the
	 *	   next loaded program to first indirect through it, such as
	 *	   when using the debugger).
	 */
	{
		static int (*x_entry)() = 0;
		extern int argv[];

		argv[1] = howto;
		argv[2] = devtype;
		argv[3] = (int) ssym;
		argv[4] = esym;
		argv[5] = (int) x.a_entry;
		argv[6] = (int) &x_entry;
		argv[0] = 6;

		printf(" start 0x%x\n", x.a_entry);
		if (x_entry)
			return (int) x_entry;
		else
			return (int) x.a_entry;
	}
shread:
	printf("Short read\n");
	return -1;
}

/* 750 Patchable Control Store magic */

#include <vax/mtpr.h>
#include <vax/cpu.h>
#define PCS_BITCNT	0x2000		/* number of patchbits */
#define PCS_MICRONUM	0x400		/* number of ucode locs */
#define PCS_PATCHADDR	0xf00000	/* start addr of patchbits */
#define PCS_PCSADDR	(PCS_PATCHADDR+0x8000)	/* start addr of pcs */
#define PCS_PATCHBIT	(PCS_PATCHADDR+0xc000)	/* patchbits enable reg */
#define PCS_ENABLE	0xfff00000	/* enable bits for pcs */

loadpcs()
{
	register int *ip;	/* known to be r11 below */
	register int i;		/* known to be r10 below */
	register int *jp;	/* known to be r9 below */
	register int j;
	static int pcsdone = 0;
	union cpusid sid;
	char pcs[100];
	char *closeparen;
	char *index();

	sid.cpusid = mfpr(SID);
	if (sid.cpuany.cp_type!=VAX_750 || sid.cpu750.cp_urev<95 || pcsdone)
		return;
	printf("Updating 11/750 microcode: ");
	strncpy(pcs, line, 99);
	pcs[99] = 0;
	closeparen = index(pcs, ')');
	if (closeparen)
		*(++closeparen) = 0;
	else
		return;
	strcat(pcs, "pcs750.bin");
	i = open(pcs, 0);
	if (i < 0)
		return;
	/*
	 * We ask for more than we need to be sure we get only what we expect.
	 * After read:
	 *	locs 0 - 1023	packed patchbits
	 *	 1024 - 11264	packed microcode
	 */
	if (read(i, (char *)0, 23*512) != 22*512) {
		printf("Error reading %s\n", pcs);
		close(i);
		return;
	}
	close(i);

	/*
	 * Enable patchbit loading and load the bits one at a time.
	 */
	*((int *)PCS_PATCHBIT) = 1;
	ip = (int *)PCS_PATCHADDR;
	jp = (int *)0;
	for (i=0; i < PCS_BITCNT; i++) {
		asm("	extzv	r10,$1,(r9),(r11)+");
	}
	*((int *)PCS_PATCHBIT) = 0;

	/*
	 * Load PCS microcode 20 bits at a time.
	 */
	ip = (int *)PCS_PCSADDR;
	jp = (int *)1024;
	for (i=j=0; j < PCS_MICRONUM * 4; i+=20, j++) {
		asm("	extzv	r10,$20,(r9),(r11)+");
	}

	/*
	 * Enable PCS.
	 */
	i = *jp;		/* get 1st 20 bits of microcode again */
	i &= 0xfffff;
	i |= PCS_ENABLE;	/* reload these bits with PCS enable set */
	*((int *)PCS_PCSADDR) = i;

	sid.cpusid = mfpr(SID);
	printf("new rev level=%d\n", sid.cpu750.cp_urev);
	pcsdone = 1;
}
