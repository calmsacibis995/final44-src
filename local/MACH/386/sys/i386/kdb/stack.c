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
 * $Log:	stack.c,v $
 * Revision 1.5.1.5  90/06/07  08:04:26  rvb
 * 	Fix $c; make $k only do kernel stack.  Flush old dead code.
 * 	[90/06/04            rvb]
 * 
 * Revision 1.5.1.4  90/05/14  13:19:07  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * 	Set kdbnumargs() to guess 5 if it can not figure out
 * 	the number of arguments.
 * 	[90/04/30            rvb]
 * 
 * Revision 1.5.1.3  90/01/08  13:26:54  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.5.1.2  89/12/28  12:43:41  rvb
 * 	findsym takes 2 args.  printsym needs to account for cursym == 0
 * 	[89/12/26            rvb]
 * 
 * Revision 1.5.1.1  89/12/21  17:57:48  rvb
 * 	a.out/coff'ized.
 * 
 * Revision 1.5  89/07/17  10:37:44  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 		Trace thru trap frame
 * 	[89/07/11            rvb]
 * 
 * Revision 1.4  89/03/09  20:02:21  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:36:17  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 *  5-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fixed stack range check for MACH_TT.
 *
 *  8-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added kernel-stack-only stack tracing.  When in kernel, look for
 *	call from "_trap" and fudge argument list to show trap arguments
 *	if found (KLUDGE!).
 *
 * 16-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added support for debugging other processes than the one
 *	that kdb is executing in.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added the "n" format stack trace that includes registers and
 *	automatic vars.  Both the new and old trace are in NON algol
 *	format C.
 *
 */

/*
 *
 *	UNIX debugger
 *
 */

#define	UNKNOWN_NUM_ARGS 5

#include "defs.h"

long adrval;
short adrflg;
extern int *kdb_regs;

oldtrace(modif)
{
	if (adrflg == 0)
		adrval = kdb_regs[EBP];
        kdbtrace(adrval, kdb_regs[EIP], modif);
}

newtrace(modif)
{
}

struct i386_frame {
	struct i386_frame	*ofp;
	int			raddr;
	int			parm[1];
};

#define IN_KERNEL_STACK(x)	((unsigned)(x) >= (unsigned)(VM_MIN_KERNEL_ADDRESS))
#define PAGE(a)	((unsigned int)a & ~0xfff)
#define TRAP 0x1
#define INTERRUPT 0x2
#define SYSCALL 0x3

kdbtrace(fp, ip, modif)
struct i386_frame *fp;
int ip;
{
	int n;
	int *argp;
	char *prf;
	int is_trap;
	int sym;

/*
	while (fp > (struct i386_frame *)VM_MIN_KERNEL_ADDRESS) {
 */
	for (;;) {
		if (modif == 'k')
			if (!IN_KERNEL_STACK(fp))
				break;
		if (modif == 'c')
			if (PAGE(fp) != PAGE(fp->ofp))
				break;
		is_trap = 0;
		printsym(fp->raddr);
#ifdef	wheeze
		findsym(ip, ISYM);
		printf(":\t%s(", cursym->n_name);
#else	wheeze
		if (sym = findsym(ip, ISYM) != MAXINT)
			printf(":\t%s(", cursym->n_un.n_name);
		else
			printf(":\t%X(", ip);
#endif	wheeze

		/* Get number of arguments and display their addresses. */
		n = kdbnumargs(fp);
		if (n == UNKNOWN_NUM_ARGS && sym) {
#ifdef	wheeze
			if (strcmp(cursym->n_name, "trap") == 0 ||
			    strcmp(cursym->n_name, "_trap") == 0)
#else	wheeze
			if (strcmp(cursym->n_un.n_name, "trap") == 0 ||
			    strcmp(cursym->n_un.n_name, "_trap") == 0)
#endif	wheeze

			{
				n = 1;
				is_trap = TRAP;
			}
			
#ifdef	wheeze
			if (strcmp(cursym->n_name, "syscall") == 0 ||
			    strcmp(cursym->n_name, "_syscall") == 0)
#else	wheeze
			if (strcmp(cursym->n_un.n_name, "syscall") == 0 ||
			    strcmp(cursym->n_un.n_name, "_syscall") == 0)
#endif	wheeze
			{
				is_trap = SYSCALL;
			}

#ifdef	wheeze
			if (strcmp(cursym->n_name, "kdintr") == 0 ||
			    strcmp(cursym->n_name, "_kdintr") == 0)
#else	wheeze
			if (strcmp(cursym->n_un.n_name, "kdintr") == 0 ||
			    strcmp(cursym->n_un.n_name, "_kdintr") == 0)
#endif	wheeze
			{
				is_trap = INTERRUPT;
			}
		}
		argp = &fp->parm[0];
		prf = "";
		while (n--) {
			printf("%s%X", prf, *argp++);
			prf = ", ";
		}
		printf(")\n");

		kdbnextframe(&fp, &ip, &fp->parm[0], is_trap);
	}
}

/* 
 * XXX - This should go in sym.c.
 */
printsym(addr)
	int addr;
{
	int n = findsym(addr, ISYM);

#ifdef	wheeze
	printf("%s+%X", cursym->n_name, n);
#else	wheeze
	if (!(int)cursym) {
		printf("%X", addr);
	} else {
		printf("%s+%X", cursym->n_un.n_name, n);
	}
#endif	wheeze
}

/* 
 * Figure out how many arguments were passed into the frame at "fp". 
 * XXX - will this work with gcc?
 */
int
kdbnumargs(fp)
	struct i386_frame *fp;
{
	extern int vstart(), etext();
	int *argp;
	int inst;			/* an i386 instruction */
	int args = UNKNOWN_NUM_ARGS;

	argp = (int *)fp->raddr;
	if (argp < (int *)vstart || argp > (int *)etext)
		args = UNKNOWN_NUM_ARGS;
	else {
		inst = *argp;
		if ((inst & 0xff) == 0x59) /* popl %ecx */
			args = 1;
		else if ((inst & 0xffff) == 0xc483) /* addl $n,%esp */
			args = ((inst >> 16) & 0xff) / 4;
		else
			args = UNKNOWN_NUM_ARGS;
	}
	return(args);
}


/* 
 * Figure out the next frame up in the call stack.  
 * For trap(), we print the address of the faulting instruction and 
 *   proceed with the calling frame.  We return the ip that faulted.
 *   If the trap was caused by jumping through a bogus pointer, then
 *   the next line in the backtrace will list some random function as 
 *   being called.  It should get the argument list correct, though.  
 *   It might be possible to dig out from the next frame up the name
 *   of the function that faulted, but that could get hairy.
 */

kdbnextframe(fp, ip, argp, is_trap)
	struct i386_frame **fp;		/* in/out */
	int *ip;			/* out */
	int *argp;			/* in */
	int is_trap;			/* in */
{
	int *saved_regs;
	char *trap_name;

	if (is_trap == 0) {
		*ip = (*fp)->raddr;
		*fp = (*fp)->ofp;
	} else {
		/* 
		 * We know that trap() has 1 argument and we know that
		 * it's an (int *).
		 */
		if (is_trap == INTERRUPT ) {
			saved_regs = (int *) ((*fp)->ofp);
			printf("--- interrupt (number 0x%x) ---\n",
			       saved_regs[TRAPNO] & 0xffff);
		} else if (is_trap == TRAP) {
			saved_regs = (int *)*argp;
			trap_name = (saved_regs[TRAPNO] < TRAP_TYPES) ? 
				trap_type[saved_regs[TRAPNO]] :
				"?????";
			printf("--- %s ---\n", trap_name);
			printsym(saved_regs[EIP]);
			printf(":\n");
		} else {
			extern char *syscallnames[];

			saved_regs = (int *)*argp;
			printf("--- SYSCALL %d (%s)---\n",
				saved_regs[EAX],
				syscallnames[saved_regs[EAX]]);
			printsym(saved_regs[EIP]);
			printf(":\n");
		}
		*fp = (struct i386_frame *)saved_regs[EBP];
		*ip = saved_regs[EIP];
	}

}
