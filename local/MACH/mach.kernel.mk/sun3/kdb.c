/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdb.c,v $
 * Revision 2.6  89/06/03  15:41:34  jsb
 * 	Changed to use prom monitor for keyboard input.  Added code for
 * 	non-thread case. Removed previous keyboard input fix.
 * 	[89/05/20            rwd]
 * 
 * Revision 2.5  89/05/21  22:36:44  mrt
 * 	Import from jjc changes to make sun3 kbd work correctly in kdb.
 * 	[89/05/19            rvb]
 * 
 * Revision 2.4  89/03/09  21:33:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:34:55  gm0w
 * 	Added include of cputypes.h.
 * 	[89/02/18            mrt]
 * 
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 16-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Make kdbgetprocess return a useful map pointer if proc->task is
 *	TASK_NULL (a zombie process).
 *
 * 04-Aug-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed kdbwlong() to flush page before changing its 
 *	mapping.
 *
 * 22-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Merged in changes from VAX version:
 *	removed thread and task tables and replaced with
 *	back-pointers from proc structure.
 *
 *  8-Sep-86  David Golub (dbg) at Carnegie-Mellon University
 *	Modified for SUN3.
 *
 * 25-Jun-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added a new trap code for KDB entry to avoid conflict with trace
 *	trap from user mode.
 *
 * 19-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added kdbgetprocess, kdbreadwrite as interfaces between kdb
 *	and the kernel.  Pass the current process to kdb.
 *
 * 20-Nov-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_KDB: Changed to call new cnpollc() routine to set/clear
 *	console polling.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	added code to pass out the panic's frame pointer into kdb's <t
 *	variable
 *
 * 07-Oct-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Save p0 and p1 base and length registers in pcb.
 */

#include <cputypes.h>

#include <sys/param.h>
#include <sys/reboot.h>
#include <sys/systm.h>
#include <sys/vmmac.h>

#include <sun3/pcb.h>
#include <sun3/psl.h>
#include <sun3/reg.h>
#include <sun3/trap.h>

#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <sys/dir.h>		/* for user.h (!) */
#include <sys/user.h>		/* for u.u_procp  */
#include <sys/proc.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/eeprom.h>


#define Mask_MOVL	0xF000
#define Op_MOVL		0x2000
#define Mask_CLRL	0xFFC0
#define Op_CLRL		0x4280

#ifdef	lint
struct pcb kdbpcb;
char *kdberrflg;
#endif	lint


extern char *kdbsbrk();

/*
 *  kdb_init - initialize kernel debugger
 */

kdb_init()
{
	extern char *esym;
	extern int end;

	if (esym > (char *)&end)
	{
	    int len = end;
	    char *ss = (char *)&end+sizeof(int);
	    char *es = ss+len;
	    int tablen = *((int *)(es));
	    extern char *esym;

	    if ((es+((tablen+sizeof(int)-1)&~(sizeof(int)-1))) == esym)
	    {
		printf("[ preserving %d bytes of symbol table ]\n",
		   esym-ss);
		kdbsetsym(ss, es, es); 
	    }
	    else
		printf("[ no valid symbol table present ]\n");
	}
#ifdef	lint
	(void) kdbread(0, (char *)0, 0);
	kdbwrite(0, (char *)0, 0);
	kdbrlong((long *)0, (long *)0);
	kdbwlong((long *)0, (long *)0);
	(void) kdbsbrk(0);
#endif	lint
}



/*
 *  kdb_kintr - received keyboard interrupt sequence
 *
 *  Queue software interrupt to transfer into the debugger at the
 *  first opportunity.  This is not done if we are already in the
 *  debugger or if the system was booted without the KDB boot flag.
 */

int kdbactive = 0;

kdb_kintr()
{
    if (kdbactive == 0 && (boothowto&RB_NOSYNC))
    {
	extern void softcall(), enter_kdb();
	/*
	 *	Schedule a software interrupt to get to KDB.
	 */
	current_thread()->pcb->pcb_flag &= ~TRACE_AST;
	current_thread()->pcb->pcb_flag |= TRACE_KDB;
	softcall(enter_kdb, (caddr_t) 0);
    }
}



/*
 *  kdb_trap - field a TRACE or BPT trap
 */

int kdbtrapok = 0;
int kdbreturn = 1;

kdb_trap(type, a_regs)
	int		type;
	struct regs	*a_regs;

{
    extern struct pcb kdbpcb;
    register struct pcb *pcb = &kdbpcb;

    int spl;

    if ((boothowto&RB_NOSYNC) == 0)
	return(0);

    switch (type)
    {
	case T_TRACE:
	case T_BRKPT:
	    break;

	default:
	{
	    int	i;
	    extern char *trap_type[];
	    extern int TRAP_TYPES;
	    extern char *kdberrflg;

	    i = type / sizeof(int);
	    printf("kernel: ");
	    if ((unsigned)i >= TRAP_TYPES)
		printf("type %d", type);
	    else
		printf("%s", trap_type[i]);
	    printf(" trap\n");
	    if (kdbtrapok)
	    {
		/*
		 *	PC now points to next instruction (on a 68020)
		 */
		if (((*(u_short *)(a_regs->r_pc - 2)) & Mask_MOVL) == Op_MOVL &&
		    ((*(u_short *)(a_regs->r_pc)) & Mask_CLRL) == Op_CLRL)
		{
		    kdberrflg = "";
		    /* clear bus error frame! */
		    return(1);
		}
	    }
	}
    }

#if	0	/* ? do we need this ? */
    /*
     *  We'd rather run the debugger while on the interrupt stack so as not to
     *  run into kernel stack overflow problems depending on how deep we were
     *  when the trap occurred.  Thus, if we aren't already on the interrupt
     *  stack schedule a software interrupt at IPL 0xf to get us there.  First,
     *  raise the IPL to the maximum, though, to insure that the software
     *  interrupt won't happen until the REI which returns from the current
     *  trap completes and it can appears to happen at the same PC.
     */
    if ((movpsl()&PSL_IS) == 0)
    {
	int ipl;

	ipl = splx(0x1f);
	if (ipl < 0xf)
	{
	    mtpr(SIRR, 0xf);
	    return(1);
	}
	splx(ipl);
    }
#endif	0	/* ? do we need this ? */

    pcb->pcb_regs = *a_regs;

    /* store FP registers ? */

    kdbactive++;
    cnpollc(TRUE);

    kdb(type == T_TRACE, (int *)a_regs,	/* sp at trap */
    	    (allproc) ? u.u_procp : NULL);
    cnpollc(FALSE);
    kdbactive--;

    *a_regs = pcb->pcb_regs;

    /*
     *	indicate that single-step is for KDB
     *  But lock out interrupts to prevent KDB_STEP from setting
     *  the trace bit in the current SR (and trapping while exiting
     *  kdb).
     */
    (void) spl7();
    if (!USERMODE(a_regs->r_sr) && (a_regs->r_sr & PSL_T) && current_thread())
	current_thread()->pcb->pcb_flag |= TRACE_KDB;
    /* restore FP regs ? */

    return(kdbreturn);
}



/*
 *  kdbread - read character from input queue
 */

kdbread(x, cp, len)
register char *cp;
{
    register char c;
#ifdef	lint
    while (x--) len--;
#endif	lint
    c = cngetc();
    if (c == '\r')
	c = '\n';
    cnputc(c);
    *cp = c;
    return(1);
}



/*
 *  kdbwrite - send characters to terminal
 */

/* ARGSUSED */
kdbwrite(x, cp, len)
register char *cp;
register int len;
{
#ifdef	lint
   while (x--);
#endif	lint
   while (len--)
	cnputc(*cp++);
}



/*
 *   kdbrlong - read long word from kernel address space
 */

kdbrlong(addr, p)
register long *addr;
register long *p;
{
    *p = 0;
    kdbtrapok = 1;
    *p = *addr;
    kdbtrapok = 0;
}



/*
 *  kdbwlong - write long word to kernel address space
 */

kdbwlong(addr, p)
register long *addr;
register long *p;
{
    int	pme, oldpme = 0;
    extern char etext;

    if (addr >= (long *)KERNELBASE && addr <= (long *)&etext)
    {
	oldpme = getpgmap(addr);
#ifdef	SUN3_260
	vac_pageflush((caddr_t)addr);
#endif	SUN3_260
	setpgmap(addr, (oldpme & ~PG_PROT) | PG_KW);
    }
    kdbtrapok = 1;
    *addr = *p;
    kdbtrapok = 0;
    if (oldpme)
    {
#ifdef	SUN3_260
	vac_pageflush((caddr_t)addr);
#endif	SUN3_260
	setpgmap(addr, oldpme);
    }
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
 *	Return the map and pcb for a process.
 */
void kdbgetprocess(p, map, pcb)
	struct proc	*p;
	vm_map_t	*map;	/* OUT */
	struct pcb	**pcb;	/* OUT */

{
	/*
	 *	special case for current process
	 */
	if (p == u.u_procp) {
		*map = current_task()->map;
		*pcb = current_thread()->pcb;
	}
	else {
		if (p->task)
			*map = p->task->map;
		else
			*map = VM_MAP_NULL;
		if (p->thread)
			*pcb = p->thread->pcb;
		else
			*pcb = (struct pcb *)0;
	}
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
	if (addr >= VM_MIN_KERNEL_ADDRESS) {
		/*
		 *	in kernel
		 */
		if (rd)
			kdbrlong(addr, value);
		else
			kdbwlong(addr, value);
		return (0);
	}
	else {
		vm_offset_t	pa;	/* physical address */
		unsigned long	temp;
		int		i, ret;

		do {
			pa = pmap_extract(vm_map_pmap(map), addr);
			if (pa == 0) {
				ret = vm_fault(map, trunc_page(addr),
					rd ? VM_PROT_READ : VM_PROT_READ|VM_PROT_WRITE,
					FALSE);
				if (ret != KERN_SUCCESS)
					return (-1);
			}
		} while (pa == 0);

		if (rd) {
			extern unsigned getmemc();

			temp = 0;
			for (i = 0; i <= 3; i++) {
				temp <<= 8;
				temp |= (getmemc(pa + i)) & 0xFF;
			}
			*value = (int) temp;
		}
		else {
			extern void putmemc();
			temp = *value;
			for (i = 3; i >= 0; i--) {
				putmemc(pa + i, temp & 0xFF);
				temp >>= 8;
			}
		}
		return (0);
	}
}
