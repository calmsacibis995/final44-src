/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	readfile.c,v $
 * Revision 2.2  89/07/12  01:13:24  jjc
 * 	Modified for kdb to load symbol table.
 * 	[88/11/25            jjc]
 * 
 */
/*
 * @(#)readfile.c 1.19 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <stand/saio.h>
#include <a.out.h>

/*
 * Read in a Unix executable file and return its entry point.
 * Handle the various a.out formats correctly.
 * "Io" is the standalone file descriptor to read from.
 * Print informative little messages if "print" is on.
 * Returns -1 for errors.
 *
 * The parameter <LOAD> must be set in the command line to cc, e.g.
 * 	cc -DLOAD=0x4000 -o readfile.c
 * The makefile takes care of this.
 */
#if	MACH_KDB
/*
 *      returns 2 values:
 *      loadaddr        address to start loaded program
 *      esym            address of end of loaded symbol table
 */
void readfile(io, print, load_symbols,
                loadaddr, esym)
        register int io;
        int print;
        int load_symbols;
        int (**loadaddr)();     /* OUT */
        int *esym;              /* OUT */
#else   MACH_KDB
int (*
readfile(io, print))()
	register int io;
	int print;
#endif	MACH_KDB
{
	struct exec x;
	register int i;
	register char *addr;
	register int shared = 0;
#if	MACH_KDB
#else	MACH_KDB
	register int loadaddr;
#endif	MACH_KDB
	register int segsiz;
	register int datasize;
	extern char start[];

	i = read(io, (char *)&x, sizeof x);
	if (x.a_magic == ZMAGIC || x.a_magic == NMAGIC)
		shared = 1;
	if (i != sizeof x || (!shared && x.a_magic != OMAGIC)) {
		printf("Not executable\n");
#if	MACH_KDB
		*loadaddr = (int (*)()) -1;
		return;
#else	MACH_KDB
		return (int (*)()) -1;
#endif	MACH_KDB
	}
	if (print)
		printf("Size: %d", x.a_text);
	datasize = x.a_data;
	if (!shared) {
	        x.a_text = x.a_text + x.a_data;
	        x.a_data = 0;
	}
	if (lseek(io, N_TXTOFF(x), 0) == -1)
		goto shread;
	addr = (char *)(x.a_text + LOAD);
	if (addr  > (char *)start) {
		printf("\nProgram text overlaps boot code! 0x%x > 0x%x\n",
			addr, start);
		goto shread;
	}
#ifdef	NFS_BOOT
#define	FUDGE	(0x2000-0x20)
	if (read(io, (char *)LOAD, FUDGE) < FUDGE)
		goto shread;
	if (read(io, (char *)(LOAD+FUDGE), (int)x.a_text-FUDGE) <
		(x.a_text-FUDGE))
		goto shread;
#else
	if (read(io, (char *)LOAD, (int)x.a_text) <
		x.a_text)
		goto shread;
#endif NFS_BOOT
	if (x.a_machtype == M_OLDSUN2)
	        segsiz = OLD_SEGSIZ;
	else
	        segsiz = SEGSIZ;
	if (shared)
		while ((int)addr & (segsiz-1))
			*addr++ = 0;
	if (addr + x.a_data > (char *)start) {
		printf("\nProgram data overlaps boot code!\n");
		goto shread;
	}
	if (print)
		printf("+%d", datasize);
	if (read(io, addr, (int)x.a_data) < x.a_data)
		goto shread;
#if	MACH_KDB
        /* close after we read symbols */
#else   MACH_KDB
	close(io);		/* Done with it. */
#endif	MACH_KDB
	if (print)
		printf("+%d", x.a_bss);
	addr += x.a_data;
	for (i = 0; i < x.a_bss && addr < (char *)start; i++)
		*addr++ = 0;
#if	MACH_KDB
        if (load_symbols && x.a_syms) {
                /*
                 *      Load name-list and string table.
                 */
                *((int *)addr) = x.a_syms;      /* size of name list */
                addr += sizeof(x.a_syms);
                if (print)
                        printf("[+%d", x.a_syms);
                if (read(io, addr, x.a_syms) != x.a_syms)
                        goto shread;
                addr += x.a_syms;
                /* read size of string table */
                if (read(io, addr, sizeof(int)) != sizeof(int))
                        goto shread;
                i = *((int *)addr) - sizeof(int);
                                        /* size of string table */
                addr += sizeof(int);
                if (print)
                        printf("+%d]", i);
                if (read(io, addr, i) != i)
                        goto shread;
                addr += i;
        }
        /*
         *      Round up last loaded address (bss or string table) to a word
         *      boundary, and remember it.
         */
        *esym = ((int)(addr+sizeof(int)-1))&~(sizeof(int)-1);

        if (print)
                printf(" bytes\n");
        if (x.a_machtype != M_OLDSUN2 && x.a_magic == ZMAGIC)
                *loadaddr = (int (*)()) (LOAD + sizeof (struct exec));
        else
                *loadaddr = (int (*)()) LOAD;
        close(io);
        return;

shread:
        printf("Truncated file\n");
        *loadaddr = (int (*)()) -1;
        return;
#else	MACH_KDB
	if (print)
		printf(" bytes\n");
	if (x.a_machtype != M_OLDSUN2 && x.a_magic == ZMAGIC)
	        loadaddr = LOAD + sizeof (struct exec);
	else
	        loadaddr = LOAD;
	return (int (*)()) (loadaddr);

shread:
	printf("Truncated file\n");
	return (int (*)()) -1;
#endif	MACH_KDB
}
