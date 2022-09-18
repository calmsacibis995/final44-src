/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdb.c,v $
 * Revision 2.6  89/03/09  22:16:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:20:44  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/10  10:25:41  rvb
 * Changed splx(0x1f) to splhigh().  (which no longer is 0x1f).
 * 
 *
 * 15-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: Pass current thread to kdb instead of process.  Some MACH
 *	tasks don't have corresponding processes.
 *
 *	Make kdbwlong work when target crosses a page boundary.
 *
 * 29-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Make kdbgetprocess return a useful map pointer if proc->task is
 *	TASK_NULL (a zombie process).
 *
 * 15-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Save SSP in kdb's printed pcb (this is meaningful, it holds the
 *	current thread).
 *
 * 12-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed printf of "from kernel stack" since this made multiple
 *	instruction stepping a pain on a real console device.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Omit references to task and thread tables and replace with proc
 *	table references (through back pointers).
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
 *
 */

#include <sys/param.h>
#include <sys/reboot.h>
#include <sys/systm.h>
#include <sys/vmmac.h>

#include <vax/mtpr.h>
#include <vax/pcb.h>
#include <vax/psl.h>
#include <vax/pte.h>
#include <vax/reg.h>
#include <vax/trap.h>

#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <sys/dir.h>		/* for user.h (!) */
#include <sys/user.h>		/* for u.u_procp  */
#include <sys/proc.h>
#include <kern/task.h>
#include <kern/thread.h>

#define MOVL	0xd0	/* MOVL instruction op-code */
#define CLRL	0xd4	/* CLRL instruction op-code */

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
 *  first oppurtunity.  This is not done if we are already in the
 *  debugger or if the system was booted without the KDB boot flag.
 */

int kdbactive = 0;

kdb_kintr()
{
    if (kdbactive == 0 && (boothowto&RB_NOSYNC))
    {
	printf("\n\nkernel: keyboard interrupt\n");
	mtpr(SIRR, 0xf);
    }
}



/*
 *  kdb_trap - field a TRACE or BPT trap
 */

int kdbtrapok = 0;
int kdbreturn = 1;

kdb_trap(apsl)
register int *apsl;
{
    extern struct pcb kdbpcb;
    register struct pcb *pcb = &kdbpcb;
    register int *locr0 = (apsl-PS);
    register int type = locr0[PS-3];

    if ((boothowto&RB_NOSYNC) == 0)
	return(0);

    switch (type)
    {
	case T_TRCTRAP:
	case T_BPTFLT:
	case T_KDB_ENTRY:
	    break;

	default:
	{
	    extern char *trap_type[];
	    extern int TRAP_TYPES;
	    extern char *kdberrflg;
	    register int code = locr0[PS-2];

	    printf("kernel: ");
	    if ((unsigned)type >= TRAP_TYPES)
		printf("type %d", type);
	    else
		printf("%s", trap_type[type]);
	    printf(" trap, code=%X\n", code);
	    if (kdbtrapok)
	    {
		if (*(u_char *)(locr0[PC]) == MOVL &&
		    *(u_char *)(locr0[PC]+5) == CLRL)
		{
		    kdberrflg = "";
		    locr0[PC] += 5;
		    return(1);
		}
	    }
	}
    }

    /*
     *  We'd rather run the debugger while on the interrupt stack so as not to
     *  run into kernel stack overflow problems depending on how deep we were
     *  when the trap occurred.  Thus, if we aren't already on the interrupt
     *  stack schedule a software interrupt at IPL 0xf to get us there.
     *  First, raise the IPL to the maximum, though, to insure that the
     *	software interrupt won't happen until the REI which returns from the
     *  current trap completes and it can appears to happen at the same PC.
     */
    if ((movpsl()&PSL_IS) == 0)
    {
	int ipl;

	ipl = splhigh();
	if (ipl < 0xf)
	{
	    mtpr(SIRR, 0xf);
	    return(1);
	}
	splx(ipl);
    }

    pcb->pcb_r0 = locr0[R0];
    pcb->pcb_r1 = locr0[R1];
    pcb->pcb_r2 = locr0[R2];
    pcb->pcb_r3 = locr0[R3];
    pcb->pcb_r4 = locr0[R4];
    pcb->pcb_r5 = locr0[R5];
    pcb->pcb_r6 = locr0[R6];
    pcb->pcb_r7 = locr0[R7];
    pcb->pcb_r8 = locr0[R8];
    pcb->pcb_r9 = locr0[R9];
    pcb->pcb_r10 = locr0[R10];
    pcb->pcb_r11 = locr0[R11];
    pcb->pcb_ap = locr0[AP];
    pcb->pcb_fp = locr0[FP];
    pcb->pcb_usp = locr0[SP];
    pcb->pcb_pc = locr0[PC];
    pcb->pcb_psl = locr0[PS];
    pcb->pcb_ksp = mfpr(KSP);
    pcb->pcb_esp = mfpr(ISP);
    pcb->pcb_ssp = mfpr(SSP);
    pcb->pcb_p0br = (pt_entry_t *) mfpr(P0BR);
    pcb->pcb_p0lr = mfpr(P0LR);
    pcb->pcb_p1br = (pt_entry_t *) mfpr(P1BR);
    pcb->pcb_p1lr = mfpr(P1LR);
    kdbactive++;
    cnpollc(TRUE);
    kdb(type == T_TRCTRAP, apsl - 22, current_thread());
    cnpollc(FALSE);
    kdbactive--;
    locr0[R0] = pcb->pcb_r0;
    locr0[R1] = pcb->pcb_r1;
    locr0[R2] = pcb->pcb_r2;
    locr0[R3] = pcb->pcb_r3;
    locr0[R4] = pcb->pcb_r4;
    locr0[R5] = pcb->pcb_r5;
    locr0[R6] = pcb->pcb_r6;
    locr0[R7] = pcb->pcb_r7;
    locr0[R8] = pcb->pcb_r8;
    locr0[R9] = pcb->pcb_r9;
    locr0[R10] = pcb->pcb_r10;
    locr0[R11] = pcb->pcb_r11;
    locr0[AP] = pcb->pcb_ap;
    locr0[FP] = pcb->pcb_fp;
    locr0[SP] = pcb->pcb_usp;
    locr0[PC] = pcb->pcb_pc;
    locr0[PS] = pcb->pcb_psl;
    return(kdbreturn);
}



/*
 *  kdbread - read character from input queue
 */

kdbread(x, cp, len)
register char *cp;
{
#ifdef	lint
    while (x--) len--;
#endif	lint
    *cp = cngetc();
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
long *addr;
long *p;
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
long *addr;	/* must NOT be register for kdbtrap test to work! */
long *p;
{
    register int pn;
    register int *ptep;
    register int oldmap = 0;
    register int oldmap2 = 0;
    register long va = (long)addr;
    extern char *Sysbase;
    extern char etext;

    if (va >= (long)Sysbase && va <= (long)&etext)
    {
	pn = btop(va & ~0x80000000);
	ptep = (int *)(Sysmap+pn);
	oldmap = *(ptep);
	*ptep = ((*ptep&~PG_PROT)|PG_KW);
	mtpr(TBIS, va);

	if ((va & ~(NBPG-1)) != ((va + sizeof(long)-1) & ~(NBPG-1))) {
	    /* long at addr crosses a page boundary */
	    oldmap2 = ptep[1];
	    ptep[1] = ((ptep[1]&~PG_PROT)|PG_KW);
	    mtpr(TBIS, va + NBPG);
	}
    }
    kdbtrapok = 1;
    *addr = *p;
    kdbtrapok = 0;
    if (oldmap)
    {
	*ptep = oldmap;
	mtpr(TBIS, va);
	if (oldmap2) {
	    ptep[1] = oldmap;
	    mtpr(TBIS, va + NBPG);
	}
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
			for (i = 3; i >= 0; i--) {
				temp <<= 8;
				temp |= (getmemc(pa + i)) & 0xFF;
			}
			*value = (int) temp;
		}
		else {
			extern void putmemc();
			temp = *value;
			for (i = 0; i < 4; i++) {
				putmemc(pa + i, temp & 0xFF);
				temp >>= 8;
			}
		}
		return (0);
	}
}
