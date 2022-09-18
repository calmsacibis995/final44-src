/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdb.c,v $
 * Revision 1.5.1.5  90/05/14  13:17:55  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * 	Add play back buf for kdb at end of phys memory.
 * 	[90/05/01            rvb]
 * 
 * Revision 1.5.1.4  90/03/07  13:28:21  rvb
 * 	kdbwlong, kdbrlong were moved to copy_user.s
 * 	[90/03/07            rvb]
 * 
 * Revision 1.5.1.3  90/02/01  13:36:33  rvb
 * 	Fix up kdbtrapok. to allow kdb bad address faults to not hoes the
 * 	kernel.
 * 	[90/02/01            rvb]
 * 
 * 	esym must always be defined even if there is no MACH_KDB
 * 	[90/01/31            rvb]
 * 
 * Revision 1.5.1.2  89/12/28  12:43:14  rvb
 * 	Debugging printout for sym table initialization.
 * 	[89/12/26            rvb]
 * 
 * Revision 1.5.1.1  89/12/21  17:59:09  rvb
 * 	enable a.out symbols
 * 
 * 
 * Revision 1.5  89/07/17  10:37:34  rvb
 * 	Temporary hack(?) so 2nd invocation of kdb does not recursively fault 
 * 	and blow away.
 * 
 * Revision 1.4  89/03/09  19:59:37  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  22:10:25  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *	NEEDS WORK .. TOO VAXISH
 *
 * 29-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Make kdbgetprocess return a useful map pointer if proc->task is
 *	TASK_NULL (a zombie process).
 *
 */

#include <sys/param.h>
#include <sys/reboot.h>
#include <sys/systm.h>
#include <sys/vmmac.h>

#include <i386/pcb.h>
#include <i386/psl.h>
#include <i386/reg.h>
#include <i386/trap.h>

#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <sys/dir.h>		/* for user.h (!) */
#include <sys/user.h>		/* for u.u_procp  */
#include <sys/proc.h>
#include <kern/task.h>
#include <kern/thread.h>

extern char *kdbsbrk();

int   play_back_size = 0x10000;
char *play_back_buf = (char *) 0;
char *play_back_ptr = (char *) 0;

/*
 *  kdb_init - initialize kernel debugger:
 *	needs kmem_alloc_pageable() -> wait till after
 *	vm_mem_init() in startup()
 */
kdb_init()
{
#ifdef	wheeze
#else	wheeze
	extern char *esym;
	extern int end;

	if (esym > (char *)&end) {
	    int len = end;
	    char *ss = (char *)&end+sizeof(int);
	    char *es = ss+len;
	    int tablen = *((int *)(es));
	    extern char *esym;

	    printf("end %x, sym %x(%x) str = %x(%x)\n",
		   &end, ss, len, es, tablen);

	    if ((es+((tablen+sizeof(int)-1)&~(sizeof(int)-1))) == esym) {
		printf("[ preserving %d bytes of symbol table ]\n",
		   esym-ss);
		kdbsetsym(ss, es, es); 
	    } else
		printf("[ no valid symbol table present ]\n");
	}
	play_back_buf = (char *)kmem_alloc_pageable(kernel_map, play_back_size);
	play_back_ptr = play_back_buf;
	
	pmap_map_bd(play_back_buf,
	 	     mem_size,
		     round_page(mem_size + play_back_size),
		     VM_PROT_READ | VM_PROT_WRITE);
#endif	wheeze
}

/*
 *  kdbsbrk - extended debugger dynamic memory
 */
static char kdbbuf[1024];
char *kdbend = kdbbuf; 

char *
kdbsbrk(n)
unsigned n;
{
    char *old = kdbend;

    if ((kdbend+n) >= &kdbbuf[sizeof(kdbbuf)])
    {
	return((char *)-1);
    }
    kdbend += n;
    return(old);
}

/*
 *	Reads or writes a longword to/from the specified address
 *	in the specified map.  The map is forced to be the kernel
 *	map if the address is in the kernel address space.
 *
 *	Returns 0 if read/write OK, -1 if not.
 */

int kdbreadwrite(map, addr, value, rd)
	vm_map_t	map;
	vm_offset_t	addr;
	long		*value;	/* IN/OUT */
	boolean_t	rd;
{
	int ret;

	if (rd)
		ret = kdbrlong(addr, value);
	else
		ret = kdbwlong(addr, value);
	return (!ret ? ret : -1);
}

play_record(c)
{
	if (play_back_size) {
		if (play_back_ptr >= &play_back_buf[play_back_size])
			play_back_ptr = play_back_buf;
		*play_back_ptr++ = c;
	}
}

/*
 *  kdbread - read character from input queue
 */
kdbread(x, cp, len)
register char *cp;
{
	register int c;

	c = cngetc();
	play_record(c);
	*cp = c;
	return(*cp != 04);
}

/*
 *  kdbwrite - send characters to terminal
 */
kdbwrite(x, cp, len)
register char *cp;
register int len;
{
   int n = len;
   register int c;

   while (len--) {
	c = *cp++;
	play_record(c);
	cnputc(c);
   }
   return(n);
}

pb(a1, a2)
{
register char *pp = play_back_buf;
register int c;

	if (a1 == -1) {
		play_back_ptr = play_back_buf;
		return;
	}

	while (c = *pp++) {
		if (pp >= &play_back_buf[play_back_size])
			pp = play_back_buf;
		if (c != '\n')
		 	cnputc(c);
		else {
			c = cngetc();
			if (c == ' ')
				cnputc('\n');
			else if (c == '\n')
				/* overwrite */;
			else
				return;
		}
	}
}
