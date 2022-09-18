/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	kdb.c,v $
 * Revision 2.4  89/03/09  21:15:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:32:51  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *	[ V5.1(F8) ]
 *
 **********************************************************************
 */

/*
 *  kdb.c - stand-alone interface to kernel-mode debugger
 */

#define NCPUS 1

#include <sys/types.h>
#include <machine/frame.h>
#include <machine/mtpr.h>
#include <machine/pcb.h>
#include <machine/pmap.h>
#include <machine/psl.h>
#include <machine/pte.h>



/*
 *  External forward declarations.  
 */


/*
 *  The system control block (defined in the low level startup module).
 */

extern int scb[];


/*
 *  Internal forward declarations
 */

extern void kdb_entry();
extern void kdb_fault();
extern void kdb_init();
extern void kdb_syminit();



/*
 *  kdb_init - initialize debugger
 *
 *  reloc = relocation address
 *
 *  If the relcoation address is non-zero, this is the first call from the
 *  low-level.  If it is zero, this is a re-initialization (usually invoked by
 *  manually restarting the processor at the relocation address).  In either
 *  case, initialize the SCBB before getting too far along so that the debugger
 *  will receive all faults.  On the first call, create an empty symbol table
 *  so that the address maps will be initialized (the symbol table itself will
 *  be loaded when the debugger is re-entered from the bootstrap program).
 *
 *  The low level startup module performs only the minimum initialization of
 *  the debugger to transfer control to this C routine.  This involves saving
 *  the processor state, relocating to high memory first and calling us to
 *  complete the initialization.  Second and subsequent entries into the
 *  debugger bypass the relocation stage.
 *
 *  Return: with the debugger initialized and the SCBB register set to refer
 *  all exceptions to the kdb_fault() handler.  When the debugger is entered
 *  via a procedure call, the low-level code will return control to the caller.
 *  When entered via a restart, the low-level code will simply pause in an
 *  internal breakpoint to transfer control into the debugger command level.
 *
 *  N.B.  Most stand-alone code will usually reset the SCBB fairly early in its
 *  execution and care must be taken when debugging such code.  Most often the
 *  code in question doesn't use the SCB and it is safe to simply skip over the
 *  corresponding instruction.
 */

void
kdb_init(reloc)
    char *reloc;
{
    mtpr(SCBB, scb);
    kdbprintf("[ Stand-Alone Kernel-mode debugger ");
    if (reloc)
    {
	kdbprintf("(restart: %X, SCBB: %X) ", reloc, scb);
	kdbsetsym((char *)0, (char *)0, (char *)0); 
    }
    else
	kdbprintf("re-");
    kdbprintf("initialized ]\n");
}



/*
 *  kdb_entry - entry point from bootstrap program
 *
 *  flags = bootstrap flags (R11)
 *  dev   = bootstrap device (R10)
 *  ssym  = start of program symbol table  
 *  esym  = end of program symbol table  
 *  xpc   = program transfer PC
 *  funcp = bootstrap transfer function pointer
 *
 *  This routine is entered under two different circumstances.
 *
 *  The first type of entry occurs when the bootstrap program transfers control
 *  to the debugger image after loading it into memory.  A kdb_init() has
 *  already been done and the bootstrap parameters are those of the debugger
 *  image.  This case is detected by a null bootstrap transfer function pointer
 *  and simply provides the opportunity for the debugger to initialize this
 *  pointer so that when the next image is loaded by the bootstrap program,
 *  control will be transferred here instead of directly to its transfer
 *  address.
 *
 *  The second type of entry occurs in this case when the bootstrap program has
 *  loaded the image to be debugged.  This call will come directly from the
 *  bootstrap program and the SCBB register must be initialized to insure that
 *  the debugger catches the trace faults which are about to be generated).
 *  Also, at this point the (optionally loaded) symbol table is still intact
 *  and is used to initialize symbols for the debugger.  Then two fault frames
 *  are initialized on the stack through which control will be transferred into
 *  the image.  A standard frame consisting of the current PSL and the supplied
 *  transfer PC+2 (procedure call) is used for the second step.  A special
 *  frame consisting of the current PSL (with the Trace bit set) and the PC of
 *  an REI instruction is used for the first step.  This transfer is done in
 *  these two steps so that the Trace trap will occur on the first instruction
 *  in the program image (a Trace bit in the PSL loaded by an REI will not take
 *  effect until the instruction at the associated PC completes which in the
 *  single step case would not trap until the second instruction in the
 *  program).
 */

void
kdb_entry(flags, dev, ssym, esym, xpc, funcp)
    int flags;
    int dev;
    char *ssym;
    char *esym;
    char *xpc;
    void (**funcp)();
{
    /*
     *  We happen to KNOW that this local variable array gets allocated on the
     *  top of the stack exactly where we want it ...
     */   
    struct {char *pc; int ps;} sp[2];
    extern char rei[];

#ifdef	lint
    if (flags) 
	;
    if (dev) 
	;
#endif

    /*
     *  Initial call.  Set transfer function pointer and return (through low-
     *  level) to bootstrap program.
     */
    if (*funcp == 0)
    {
	*funcp = kdb_entry;
	return;
    }

    /*
     *  Subsequent call(s) direct from bootstrap program.  Initialize the
     *  symbol table and transfer to the loaded program under debugger control.
     */
    mtpr(SCBB, scb);
    if (esym > ssym)
	kdb_syminit(ssym, esym);
    sp[1].ps = psl();
    sp[1].pc = xpc+2;
    sp[0].ps = sp[1].ps | PSL_T;
    sp[0].pc = rei;
    asm("_rei: rei");
    /* NOTREACHED */
}



/*
 *  kdb_syminit - initialize symbol table debugger
 *
 *  ssym = start of program symbol table (longword aligned)
 *  esym = end of program symbol table (longword aligned)
 *
 *  The bootstrap program places the symbol table immediately following the bss
 *  segment.  The first part consists of the symbol table entry array preceded
 *  by its longword length (exclusive, this value is simply the saved contents
 *  of symbol table size field of the exec header).  The second part consists
 *  of the string table preceded by its longword length (inclusive, as stored
 *  in the exec file).
 *
 *  Check the symbol and string table lengths to verify that they are
 *  consistent with the specified end address.  Preserve the symbol and string
 *  tables by copying them to immediately beyond the debugger bss segment where
 *  they will be safe from any subsequent mashing by the running program and
 *  initialize the debugger symbol module with this set of symbols.
 */

void
kdb_syminit(ssym, esym)
    char *ssym;
    char *esym;
{
    extern int end;
    int len = *(int *)ssym;
    char *ss = (char *)ssym+sizeof(int);
    char *es = ss+len;
    int tablen = *((int *)(es));

    if ((es+((tablen+sizeof(int)-1)&~(sizeof(int)-1))) == esym)
    {
	bcopy(ssym, (char *)&end, esym-ssym);
	ss = ((char *)(&end)) + sizeof(int);
	es = ss+len;
	kdbprintf("[ preserving %D bytes of symbol table ]\n",
		  esym-ssym-sizeof(int));
	kdbsetsym(ss, es, es); 
    }
    else
	kdbprintf("[ no valid symbol table present (%X-%X) ]\n", ssym, esym);
}



/*
 *  Fault vector description table. 
 */

char *kdb_fault_names[] =
{
    "#00",				/* 00 */
    "Machine Check",			/* 04 */
    "Kernel Stack Not Valid",		/* 08 */
    "Power Fail",			/* 0C */
    "Reserved/Privileged Instruction",	/* 10 */
    "Customer Reserved Instruction",	/* 14 */
    "Reserved Operand",			/* 18 */
    "Reserved Addressing Mode",		/* 1C */
    "Access Control Violation",		/* 20 */
    "Translation Not Valid",		/* 24 */
    "Trace Pending",			/* 28 */
    "Breakpoint Instruction",		/* 2C */
    "Compatibility",			/* 30 */
    "Arithmetic",			/* 34 */
    "#38",				/* 38 */
    "#3C",				/* 3C */
    "CHMK",				/* 40 */
    "CHME",				/* 44 */
    "CHMS",				/* 48 */
    "CHMU",				/* 4C */
};


/*
 *  Fault call-frame layout from low-level.
 */

struct kdb_frame
{
    struct frame fr_call;
    int		 fr_r0;
    int		 fr_r1;
    int		 fr_r2;
    int		 fr_r3;
    int		 fr_r4;
    int		 fr_r5;
    int		 fr_r6;
    int		 fr_r7;
    int		 fr_r8;
    int		 fr_r9;
    int		 fr_r10;
    int		 fr_r11;
    int		 fr_argc;	/* <== AP (always 1) */
    /*		    arg1	   type argument */
    /*		    arg2	   parameter length pseudo-argument */
    /*		    params;	   arg2 bytes (fault-specific) ... */
    /*  Common fault frame (below)  */
};
#define fr_ap	fr_call.fr_savap
#define fr_fp	fr_call.fr_savfp


/*
 *  Common fault frame layout. 
 */

struct kdb_fault
{
    int fault_pc;
    int fault_psl;
};


/*
 *  Definitions for the two instructions generated by kdbrlong() to access
 *  memory.  When a fault occurs while operating within the debugger and the
 *  faulting instruction sequence consists of these two instructions, the
 *  access is aborted without transferring recursively into the debugger.
 */

#define MOVL	0xd0	/* MOVL instruction op-code */
#define CLRL	0xd4	/* CLRL instruction op-code */

int kdbtrapok = 0;


/* So we can compile without MACH enabled ... */



/*
 *  kdb_fault - common fault handling
 *
 *  type   = fault type (the fault vector shifted right 2 bits)
 *  arglen = fault parameter length (bytes)
 *
 *  Process the fault as appropiate.  Trace and Breakpoint faults are the
 *  normal case and should be handled silently.  Any other faults generate a
 *  diagnostic mesage consisting of the fault name and all parameters.
 */

void
kdb_fault(type, arglen)
    u_int type;
    u_int arglen;
{
    extern struct pcb kdbpcb;
    register struct pcb *pcb = &kdbpcb;
    register struct kdb_frame *fr =
	 (struct kdb_frame *)((&type)-((sizeof *fr)/sizeof(int)));
    register struct kdb_fault *fault =
	(struct kdb_fault *)(((char *)(&arglen))+arglen+sizeof(arglen));

    switch (type)
    {
	case (0x28>>2):  /* Trace Pending */
	case (0x2c>>2):  /* Breakpoint Instruction */
	    break;

	case (0x04>>2):  /* Machine Check */
	{
	    /* TODO: per-cputype error recovery here */
	}
	/* fall through */

	default:
	{
	    extern char *kdberrflg;

	    if (type >= (sizeof(kdb_fault_names)/sizeof(kdb_fault_names[0])))
		kdbprintf("#%x fault", type);
	    else
		kdbprintf("%s fault", kdb_fault_names[type]);
	    if (arglen != 0)
	    {
		u_int *argp = &arglen;
		char *sep = " (";

		for (;arglen != 0; arglen -= sizeof(*argp))
		{
		    kdbprintf("%s0x%x", sep, *++argp);
		    sep = ",";
		}
		kdbprintf(")\n");
	    }
	    /*
	     *  Intercept recursive faults from within the debugger and simply
	     *  abort the access attempt.
	     */
	    if (kdbtrapok)
	    {
		if (*(u_char *)(fault->fault_pc) == MOVL &&
		    *(u_char *)(fault->fault_pc+5) == CLRL)
		{
		    kdberrflg = "";
		    fault->fault_pc += 5;
		}
	    }
	}
    }

    /*
     *  Save the processor state from the call frame and privileged registers
     *  where the debugger can access it and call the debugger.  On return,
     *  restore the (possibly updated) state and return from the fault (through
     *  the low-level code).
     */
    pcb->pcb_r0   = fr->fr_r0;
    pcb->pcb_r1   = fr->fr_r1;
    pcb->pcb_r2   = fr->fr_r2;
    pcb->pcb_r3   = fr->fr_r3;
    pcb->pcb_r4   = fr->fr_r4;
    pcb->pcb_r5   = fr->fr_r5;
    pcb->pcb_r6   = fr->fr_r6;
    pcb->pcb_r7   = fr->fr_r7;
    pcb->pcb_r8   = fr->fr_r8;
    pcb->pcb_r9   = fr->fr_r9;
    pcb->pcb_r10  = fr->fr_r10;
    pcb->pcb_r11  = fr->fr_r11;
    pcb->pcb_ap   = fr->fr_ap;
    pcb->pcb_fp   = fr->fr_fp;
    pcb->pcb_pc   = fault->fault_pc;
    pcb->pcb_psl  = fault->fault_psl;
    pcb->pcb_usp  = mfpr(USP);
    pcb->pcb_esp  = mfpr(ESP);
    pcb->pcb_ssp  = mfpr(SSP);
    pcb->pcb_ksp  = (int)(fault+1);
    pcb->pcb_p0br = (pt_entry_t *) mfpr(P0BR);
    pcb->pcb_p0lr = mfpr(P0LR);
    pcb->pcb_p1br = (pt_entry_t *) mfpr(P1BR);
    pcb->pcb_p1lr = mfpr(P1LR);

    kdb(type == (0x28>>2));

    fr->fr_r0        = pcb->pcb_r0;
    fr->fr_r1        = pcb->pcb_r1;
    fr->fr_r2        = pcb->pcb_r2;
    fr->fr_r3        = pcb->pcb_r3;
    fr->fr_r4        = pcb->pcb_r4;
    fr->fr_r5        = pcb->pcb_r5;
    fr->fr_r6        = pcb->pcb_r6;
    fr->fr_r7        = pcb->pcb_r7;
    fr->fr_r8        = pcb->pcb_r8;
    fr->fr_r9        = pcb->pcb_r9;
    fr->fr_r10       = pcb->pcb_r10;
    fr->fr_r11       = pcb->pcb_r11;
    fr->fr_ap        = pcb->pcb_ap;
    fr->fr_fp        = pcb->pcb_fp;
    fault->fault_pc  = pcb->pcb_pc;
    fault->fault_psl = pcb->pcb_psl;
}



/*
 *  kdbread - read characters from console for debugger
 *
 *  d   = descriptor
 *  cp  = buffer to receive character
 *  len = buffer length  
 *
 *  Read a character from the console.
 *
 *  Return: number of bytes read (always 1 at a time for proper echoing).
 */

kdbread(d, cp, len)
    int d;
    register char *cp;
    register int len;
{
#ifdef	lint
    if (d)
	d = len;
#endif
    *cp = getchar();
    return(1);
}



/*
 *  kdbwrite - send characters to console from debugger
 *
 *  d   = descriptor
 *  cp  = buffer to receive character
 *  len = buffer length  
 *
 *  Return: the buffer length always.
 */

kdbwrite(d, cp, len)
    int d;
    register char *cp;
    int len;
{
    register int l = len;

#ifdef	lint
    if (d)
	;
#endif

    while (l--)
    {
	putchar(*cp++);
    }
    return(len);
}



/*
 *  kdbrlong - read long word from address space for debugger
 *
 *  addr = address to access
 *  p    = location to receive its contents
 *
 *  Return: with location set to indicated contents (or 0 on error).
 *
 *  N.B.  The fault handling code above "knows" that the instruction sequence
 *  below begins with a MOVL to access the address followed by a CLRL 5 bytes
 *  later to clear the flag (in order to intercept recursive faults).
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
 *  kdbwlong - write long word to address space for debugger
 *
 *  addr = address to access
 *  p    = new contents for address
 *
 *  Return: with address set to indicated contents (or 0 on error).
 *
 *  N.B.  The fault handling code above "knows" that the instruction sequence
 *  below begins with a MOVL to access the address followed by a CLRL 5 bytes
 *  later to clear the flag (in order to intercept recursive faults).
 */

kdbwlong(addr, p)
    register long *addr;
    long *p;
{
    kdbtrapok = 1;
    *addr = *p;
    kdbtrapok = 0;
}



/*
 *  kdbsbrk - extend dynamic memory for debugger 
 *
 *  n = number of bytes to extend by
 *
 *  Return: a pointer to the old memory end point
 *
 *  N.B.  The dynamic memory area is actually allocated from the static buffer
 *  below to simplify things since the debugger's need for dynamic memory
 *  is not large.
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
	kdbprintf("[ kdsbsbrk(%d): failed ]\n", n);
	return((char *)-1);
    }
    kdbend += n;
    return(old);
}



#ifdef	lint
main()
{
    kdb_init((char *)0);
    kdb_fault(0, 0);

    if (kdbread(0, (char *)0, 0))
	;
    if (kdbwrite(0, (char *)0, 0))
	;
    if (kdbsbrk((u_int)0))
	;
    kdbrlong((long *)0, (long *)0);
    kdbwlong((long *)0, (long *)0);
}

char rei[1];
int scb[128];
int end;

/*VARARGS*/
/*ARGSUSED*/
           kdbprintf( s ) char *s; {;}
struct pcb kdbpcb;
char      *kdberrflg;
#endif	lint
