/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	boot.c,v $
 * Revision 2.2  89/07/12  00:10:04  jjc
 * 	Modified for kdb.
 * 	[88/11/25            jjc]
 * 
 */

#ifndef lint
static	char sccsid[] = "@(#)boot.c 1.17 88/02/08 Copyr 1983 Sun Micro";
#endif

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include <sys/user.h>
#include <stand/saio.h>
#include <sys/reboot.h>
#include <mon/sunromvec.h>
#include <sys/dir.h>
#ifdef sun3
#include <sun3/pte.h>
#endif
#ifdef	DUMP_DEBUG
static	int	dump_debug = 20;
#endif	/* DUMP_DEBUG */

#undef u
struct	user	u;
#if	MACH_KDB
#define RB_KDB	0x400
#endif	MACH_KDB

/*
 * Boot program... argument from monitor determines
 * whether boot stops to ask for system name and which device
 * boot comes from.
 */

int (*readfile())();

char aline[100];

char vmunix[50] = "vmunix";	/* and room to patch to whatever */
extern	int	boothowto;	/* defined in <sys/systm.h> */

#if defined(SUN3) || defined(sun3)
char	sun_3_defined;
#endif

#if defined(SUN2) || defined(sun2)
char	sun_2_defined;
#endif

char	boot_device[3];
struct	bootparam	*boot_bp;
#if defined (sun3) || defined (sun4)
int	memory_avail;
#endif sun3

main()
{
	register struct bootparam *bp;
	register char *arg;
	register int howto;
	register int io;
	int (*go2)();
	int	ctlr;
	int	unit;
	int	partition;
	char	filename[MAXNAMLEN];
	char	*dev_unit_file();
	void	mountroot();
#ifdef sun2
	int	*mem_p;
#endif sun2
#if	MACH_KDB
	int esym;	/* points at end of symbol table */
#endif	MACH_KDB

	if (romp->v_bootparam == 0)	{
		bp = (struct bootparam *)0x2000;	/* Old Sun-1 address */
	} else	{
		bp = *(romp->v_bootparam);		/* S-2: via romvec */
	}
	boot_bp = bp;
#ifdef sun2
	mem_p = (int *)&(bp->bp_strings[96]);
	*mem_p = 0x200000;
	bp->bp_strings[95] = '\0';
#endif sun2
#ifdef sun3
	/*
	 * Allocate memory starting below the top of physical
	 * memory, to avoid tromping on kadb.
	 */
	memory_avail = *romp->v_memoryavail - 0x100000;
#endif sun3
#ifdef sun4
	memory_avail = *romp->v_memoryavail - 0x200000;
#endif sun4

	kmem_init();
	bhinit();
	binit();
	init_syscalls();
#ifdef sun3
	kmem_remap();	/* map around video ram */
#endif sun3


#ifdef JUSTASK
	howto = RB_ASKNAME|RB_SINGLE;
#else	/* JUSTASK */
	arg = bp->bp_argv[0];
	howto = bootflags(bp->bp_argv[1]);
	/*
	 * Place in global location for gtfsype to
	 * pick up.
	 */
	boothowto = howto;
	(void) dev_unit_file(arg, &boot_device[0],
			&ctlr, &unit, &partition, &filename[0]);
	if ((howto&RB_ASKNAME)==0) {
		register char *s, *p;

		for (s = arg, p = aline; *s; s++, p++)
			*p = *s;
		
		/*
		 * If no file name given, default to "vmunix"
	  	 * We only do this if we aren't asking for input
		 */
		for (s = aline; *s;)
			if (*s++ == ')')
				break;
		if (*s == '\0') {
			for (p = vmunix; *p;)
				*s++ = *p++;
			*s = '\0';
		}
	}
#endif	/* JUSTASK */
#if	MACH_KDB
	howto |= RB_KDB;	/* load symbols */
#endif	MACH_KDB
	for (;;) {
		if (howto & RB_ASKNAME) {
			/*
			 * First try to mount a 'root' file system.
			 */
			mountroot();
			if (u.u_error)  {
				howto |= RB_ASKNAME;
				boothowto = howto;
				continue;
			}

		openit:
			printf("Boot: ");
			(void) gets(aline);
			if (*aline == 0)
				continue;	/* Null input - try again */

		} else	{
			/*
			 * First try to mount a 'root' file system.
			 */
			mountroot();
			if (u.u_error)  {
				howto |= RB_ASKNAME;
				boothowto = howto;
				continue;
			}
			{
				register char *s, *p;

				if(filename[0] == '\0')		{
				        for (s = aline, p = vmunix; *p;)
						*s++ = *p++;
				} else {
					for (s = aline, p = filename; *p;)
						*s++ = *p++;
				}
				*s = '\0';
			}
		printf("Boot: %s\n", aline);
		}

		if(!strcmp(aline, "*"))	{
		        if (list_directory("") != 0)
				printf ("Bad directory\n");
			goto openit;
		}

		io = open(aline, 0);
		if (io >= 0) {
#if	MACH_KDB
			readfile(io, 1, ((howto&RB_KDB) != 0),
					&go2, &esym);
			if (!(howto & RB_ASKNAME)) {
				exitto(go2, esym);
				/*NOTREACHED*/ ;
			}
			if ((int)go2 != -1)
			        call(arg, go2, esym);
#else	MACH_KDB
			go2 = readfile(io, 1);
			if (!(howto & RB_ASKNAME))  {
				_exitto(go2);
				/*NOTREACHED*/ ;
			}
			if ((int)go2 != -1)
				(*go2)(arg);
#endif	MACH_KDB
		} else {
			printf("boot failed\n");
				howto |= RB_ASKNAME;
				boothowto = howto;
				goto openit;
		}
	}
}


struct bootf {
	char	let;
	short	bit;
} bootf[] = {
	'a',	RB_ASKNAME,
	's',	RB_SINGLE,
	'i',	0,
	'h',	RB_HALT,
	'b',	RB_NOBOOTRC,
	'd',	RB_DEBUG,
	0,	0,

};

#ifndef JUSTASK
/*
 * Parse the boot line to determine boot flags 
 */
bootflags(cp)
	register char *cp;
{
	register int i, boothowto = 0;

	if (*cp++ == '-')
	do {
		for (i = 0; bootf[i].let; i++) {
			if (*cp == bootf[i].let) {
				boothowto |= bootf[i].bit;
				break;
			}
		}
		cp++;
	} while (bootf[i].let && *cp);
	return (boothowto);
}
#endif
 
/*
 * Parse the boot line and put it in bootparam.  Stuff in -a -s or -as if
 * s/he only typed one argument and if they were in effect before.
 */
parseparam(line, defaults, bp)
	register char *line;
	int defaults;
	register struct bootparam *bp;
{
	register int narg = 0, i;
	register char *cp = bp->bp_strings;

	while(*line) {
		if (narg == 1)		/* terminate line for open */
			*line++ = 0;
		while (*line == ' ')
			line++;
		if (*line)
			bp->bp_argv[narg++] = cp;
		while (*line != ' ' && *line != 0)
			*cp++ = *line++;
		*cp++ = 0;
	};
	bp->bp_argv[narg] = 0;
	/*
	 * Stuff in default switches
	 */
	if (narg == 1 && defaults) {
		bp->bp_argv[narg++] = cp;
		*cp++ = '-';
		for (i = 0; bootf[i].let; i++) {
			if (defaults & bootf[i].bit)
				*cp++ = bootf[i].let;
		}
		*cp = 0;
		bp->bp_argv[narg] = 0;
	}
}

#ifdef sun3

#define VIDEO_START	0x100000	/* physical address of start of video ram */
#define ONE_PMEG	16*PAGESIZE
#define VIDEO_SIZE	ONE_PMEG

kmem_remap()
{
    extern struct pte getpgmap();
    extern int setpgmap();
    extern int start;

    register int vaddr, paddr;
    struct pte p;

    p.pg_v = 1; p.pg_prot = KW; p.pg_nc = 1; p.pg_type = OBMEM;
    p.pg_r = 0; p.pg_m = 0; 

    /* map 0-VIDEO_START virtual addresses 1:1 to physical addresses */
    for (vaddr = 0, paddr = 0; paddr < VIDEO_START; vaddr += PAGESIZE, paddr += PAGESIZE)
    {
	p.pg_pfnum = paddr >> PAGESHIFT;
	setpgmap(vaddr,p);
    }
    paddr += VIDEO_SIZE;
    for (; vaddr < (int)&start - 2*ONE_PMEG; vaddr += PAGESIZE, paddr += PAGESIZE)
    {
	p.pg_pfnum = paddr >> PAGESHIFT;
	setpgmap(vaddr,p);
    }
}
#endif sun3
