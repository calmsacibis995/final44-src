/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	print.c,v $
 * Revision 2.9  89/03/09  21:35:12  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/25  19:42:13  gm0w
 * 	Removed else leg of KERNEL conditionals as part of kernel
 * 	cleanup.
 * 	[88/02/08            jjc]
 * 
 * Revision 2.7  89/02/17  21:36:21  rpd
 * 	Moved to sun3/.
 * 
 * Revision 2.6  88/12/19  02:48:53  mwyoung
 * 	Fix include file references.
 * 	[88/12/19            mwyoung]
 * 	
 * 	Put the 'm' print cases in the common file.
 * 	[88/12/06  01:02:35  mwyoung]
 * 
 * Revision 2.5  88/11/21  17:06:31  rvb
 * 	Revision 2.4.1.1  88/11/17  05:52:05  mwyoung
 * 	Correct handling of current_thread() in print_stack_trace().
 * 	[88/11/17            mwyoung]
 * 
 * Revision 2.4  88/10/25  03:42:00  mwyoung
 * 	Use standard print cases from <kern/kdb_print.h>.
 * 
 * 17-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Changed thread times printout to match new thread timer fields.
 *
 * 04-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed printstack() to only give stack trace for kernel
 *	with $k and $K commands.  Also, modified to accept
 *	<thread address>$K.
 *
 * 29-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed thread state printout to match new scheduling state
 *	machine.
 *
 * 29-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added task/thread list printout for MACH.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL and changed pathnames
 *	of include files to be kernel relative in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 */
#ifndef	lint
static	char sccsid[] = "@(#)print.c 1.1 86/02/03 SMI"; /* from UCB X.X XX/XX/XX */
#endif

/*
 * adb - print routines ($ command)
 */

#define REGNAMES
#include <sun3/kdb/adb.h>
#include <sun3/kdb/fpascii.h>
#include <sys/proc.h>

int	infile;
int	outfile;

#define MAXOFF	0x8000
int	maxoff = MAXOFF;

#define MAXPOS	80
int	maxpos = MAXPOS;

/* breakpoints */
struct	bkpt *bkpthead;

char *signals[NSIG] = {
	"",
	"hangup",
	"interrupt",
	"quit",
	"illegal instruction",
	"trace/BPT",
	"IOT",
	"EMT",
	"floating exception",
	"killed",
	"bus error",
	"memory fault",
	"bad system call",
	"broken pipe",
	"alarm call",
	"terminated",
	"signal 16",
	"stop (signal)",
	"stop (tty)",
	"continue (signal)",
	"child termination",
	"stop (tty input)",
	"stop (tty output)",
	"input available (signal)",
	"cpu timelimit",
	"file sizelimit",
	"signal 26",
	"signal 27",
	"signal 28",
	"signal 29",
	"signal 30",
	"signal 31",
};

#define ADDRESS_WAS_SPECIFIED	hadaddress
#define ADDRESS_VALUE		address

#include <kern/kdb_print.h>

printtrace(modif)
	int modif;
{
	int i, stack;

	if (hadcount ==0)
		count = -1;
	switch (modif) {

	    case 'p':
		/*
		 *	pid$p	sets process to pid
		 *	$p	sets process to the one that invoked
		 *		kdb
		 */
		{
			struct proc 	*p;
			extern struct proc *	pfind();

			extern void	kdbgetprocess();

			if (hadaddress) {
				p = pfind(dot);
			}
			else {
				p = pfind(curpid);	/* pid at entry */
			}
			if (p) {
				printf("proc entry at 0x%X\n", p);
				kdbgetprocess(p, &curmap, &curpcb);
				var[varchk('m')] = (int)curmap;
				pid = p->p_pid;
				if (pid == curpid) {
					/*
					 * pcb for entry process is saved
					 * register set
					 */
					 curpcb = &pcb;
				}
			}
			else {
				printf("no such process");
			}
		}
		break;

	KDB_PRINT_CASES

	case 'i':
		whichsigs();
		break;

	case 'd':
		if (hadaddress) {
			if (address < 2 || address > 16)
				error("must have 2 <= radix <= 16");
			radix = address;
		}
		printf("radix=%d base ten", radix);
		break;

	case 'w':
		maxpos = hadaddress ? address : MAXPOS;
		break;

	case 's':
		maxoff = hadaddress ? address : MAXOFF;
		break;

	case 'v':
		prints("variables\n");
		for (i=0; i <= 35; i++)
			if (var[i]) {
				printc(i + (i <= 9 ? '0' : 'a' - 10));
				printf(" = %Q\n", var[i]);
			}
		break;


	case 0: case '?':
		if (pid)
			printf("pcs id = %d\n", pid);
		else
			prints("no process\n");
		sigprint( signo ); flushbuf();
		/* fall into ... */
	case 'r':
		printregs();
		return;

	case 'x':
	case 'X':
		if(mc68881==1) 
			printfregs() ;
		else
			error("no 68881") ;
		return ;

	case 'C':
	case 'c':
		printstack(modif);
		return;

	case 'e': {
		register struct nlist	*sp;

		for (sp = symtab; sp < esymtab; sp++) {
			if (sp->n_type==(N_DATA|N_EXT) || sp->n_type==(N_BSS|N_EXT))
				printf("%s:%12t%R\n", sp->n_un.n_name,
				   get(sp->n_value,DSP));
		}
									   
		}
		break;

	case 'a':
		error("No algol 68 here");
		/*NOTREACHED*/

	case 'b': {
		register struct bkpt *bkptr;
		printf("breakpoints\ncount%8tbkpt%24tcommand\n");
		for (bkptr = bkpthead; bkptr; bkptr = bkptr->nxtbkpt)
			if (bkptr->flag) {
		   		printf("%-8.8d", bkptr->count);
				psymoff(bkptr->loc, ISYM, "%24t");
				printf("%s", bkptr->comm);
			}
		}
		break;

	default:
		error("bad modifier");
	}
}

print_stack_trace(thread)
	thread_t	thread;
{
	hadaddress = (thread != current_thread());
	address = (int) thread;
	printstack(hadaddress ? 'K' : 'k');
}

printstack(modif)
	int modif;
{
	int i, val, nargs, spa;
	addr_t regp;
	char *name;
	struct stackpos pos;
	struct nlist *savesym;

	if (!hadaddress)
 		stacktop(&pos);
	else if (modif == 'K') {	/* <thread address>$K */
		/*
		 *	Get stack trace for kernel given thread address.
		 */
		struct pcb *oldpcb;
		thread_t thread;

		thread = (thread_t)address;
		oldpcb = curpcb;	/* save current pcb */
		curpcb = (struct pcb *)chkget(&(thread->pcb), DSP);
		stacktop(&pos);		/* grab good stuff from curpcb */
		curpcb = oldpcb;	/* put back old pcb */
	}
	else {
		pos.k_flags = 0;
		pos.k_fp = address;
#ifdef	vax
		/*
		 *	Get the prior value of the argument pointer
		 *	We do this by seeing how many registers were saved
		 */
		val = get(pos.k_fp+FR_RMASK, DSP) & 0xFFFF;
		/*
		 *	Test if this framw was constructed with a calls.
		 */
		if (FR_CALLS(val)) {
			regp = pos.k_fp + sizeof (struct frame);
			spa = FR_SPA(val);
			val = FR_REGMASK(val);
			i = 0;
			while (val) {
				if (val & 1)
					regp += sizeof (int);
				val >>= 1; i++;
			}
			/*
			 *	Compute the prior argument pointer:
			 *	We've adjusted for the saved registers,
			 *	and unaligned it with the saved bits
			 */
			pos.k_ap = regp + spa;
		} else	/* who knows what the ap was */
			pos.k_ap = 0;
		pos.k_pc = get(pos.k_fp+FR_SAVPC, DSP);
#endif
#ifdef	sun
		pos.k_nargs = 0;
		pos.k_pc = MAXINT;
		pos.k_entry=MAXINT;
		/* sorry, we cannot find our registers without knowing our pc */
		for( i=0; i<NREGISTERS; pos.k_regloc[i++] = 0) ;
		findentry( &pos );
#endif

	}
	while (count) {
		count--;
		chkerr();
#ifdef	vax
		/* HACK */
		if (INUDOT(pos.k_pc))
			name = "sigtramp";
#endif
#ifdef	sun
		/* EQUAL HACK */
		if (pos.k_pc == MAXINT) {
			name = "?";
			pos.k_pc = 0;
		}
#endif
		else
		    {
			val =  findsym(pos.k_pc, ISYM);
			if (cursym && !strcmp(cursym->n_un.n_name, "start"))
				break;
			if (cursym)
				name = cursym->n_un.n_name;
			else
				name = "?";
		}
		printf("%s", name);
#ifdef	sun
		if (pos.k_entry != MAXINT){
		    savesym = cursym;
		    findsym(pos.k_entry, ISYM);
		    if (cursym != NULL && cursym != savesym && 
		      cursym->n_value != savesym->n_value) {
			printf("(?)\n");
			if (cursym)
				name = cursym->n_un.n_name;
			else
				name = "?";
		        printf("%s", name);
		    }
		}
#endif
		printf("(");
#ifdef	vax
		if ((regp=pos.k_ap) == 0 ||
		    ((nargs = get(pos.k_ap, DSP)) &~ 0xff))
			printf("???");
		else 
#endif
#ifdef	sun
		regp = pos.k_fp+FR_SAVFP+4;
		if ((nargs = pos.k_nargs))
#endif
		    {
			while (nargs--) {
				printf("%R", get(regp += 4, DSP));
				if (nargs)
					printf(",");
			}
		}
		if (val == MAXINT)
		    printf(") at %X\n", pos.k_pc );
		else
		    printf(") + %X\n", val);
		/*
		 *	Stop tracing if frame ptr doesn't point into kernel
		 *	stack anymore
		 */
		if ((modif == 'k' || modif == 'K') && !INKERNEL(pos.k_fp))
				break;
		if (nextframe(&pos, (modif == 'k' || modif == 'K')) == 0)
			break;
#ifndef	sun
		/* due to our different interpretation of the stack frame,
		   this fails to work					    */
		if (hadaddress == 0 && !INSTACK(pos.k_fp))
			break;
#endif
	}
}

printmap(s, amap)
	char *s;
	struct map *amap;
{
	int file;

	file = amap->ufd;
	printf("%s%12t`%s'\n", s,
	    file<0 ? "-" : (file == fcor ? corfil : symfil));
	printf("b1 = %-16R", amap->b1);
	printf("e1 = %-16R", amap->e1);
	printf("f1 = %-16R", amap->f1);
	printf("\n");
	printf("b2 = %-16R", amap->b2);
	printf("e2 = %-16R", amap->e2);
	printf("f2 = %-16R", amap->f2);
	printf("\n");
}

printregs()
{
	register int i;
	int val, off;

	for (i = 0; i < REG_FP0 ; i++) {
		val = readreg(i);
		printf("%s%6t%R %16t", regnames[i], val);
		off = findsym(val, DSP);
		if (off < maxoff) {
			printf("%s", cursym->n_un.n_name);
			if (off)
				printf("+%R", off);
		}
		printf("\n");
	}
	printpc();
}

printfregs()
{
	int i;
	int val;

	for (i = REG_FP0 ; i <= REG_FP7 ; i = i + 3 ) 
		{
		char s[64] ;

		printf("%s%4t%X%16t",regnames[i],readreg(i)) ;
		printf("%s%4t%X%16t",regnames[i+1],readreg(i+1)) ;
		printf("%s%4t%X%16t",regnames[i+2],readreg(i+2)) ;
		val = readreg(i) ;
		fprtos( fp_reg_address, s) ;
		printf("%s",s) ;
 		printf("\n") ;
		}
	for (i = REG_FPC ; i <= REG_FPF ; i++ )
		{
		printf("%s%4t%X%16t",regnames[i],readreg(i)) ;
		}
	printf("\n") ;
}

getreg(regnam)
	int regnam;
{
	register int i;
	register char *regptr;
	char *olp = lp;

	olp = lp;
	for (i = 0; i < NREGISTERS; i++) {
		regptr = regnames[i];
		if (regnam == *regptr++) {
			while (*regptr)
				if (readchar() != *regptr++) {
					--regptr;
					break;
				}
			if (*regptr == 0)
				return (i);
			lp = olp;
		}
	}
	lp = olp;
	return (-1);
}

printpc()
{
	psymoff(dot, ISYM, ":%16t");
#ifdef	vax
	printins(0, ISP, (u_char)chkget(dot, ISP));
#endif
#ifdef	mc68000
	printins(0, ISP, (chkget(dot, ISP)>>16)&0xffff);
#endif
	printc('\n');
}

#ifdef	vax
char	*illinames[] = {
	"reserved addressing fault",
	"priviliged instruction fault",
	"reserved operand fault"
};
char	*fpenames[] = {
	0,
	"integer overflow trap",
	"integer divide by zero trap",
	"floating overflow trap",
	"floating/decimal divide by zero trap",
	"floating underflow trap",
	"decimal overflow trap",
	"subscript out of range trap",
	"floating overflow fault",
	"floating divide by zero fault",
	"floating undeflow fault"
};
#endif

whichsigs()
{
	/* indicate which signals are passed to the subprocess. */
	/* implements the $i command				*/
	register i;
	for (i=0; i<NSIG; i++)
		if (sigpass[i]){
			printf("%R\t", i);
			sigprint( i );
			prints("\n");
		}
}

sigprint( signo )
	int signo;
{

	if ((signo>=0) && (signo<sizeof signals/sizeof signals[0]))
		prints(signals[signo]);
#ifdef	vax
	switch (signo) {

	case SIGFPE:
		if (sigcode > 0 &&
		    sigcode < sizeof fpenames / sizeof fpenames[0]) {
			prints(" ("); prints(fpenames[sigcode]); prints(")");
		}
		break;

	case SIGILL:
		if (sigcode >= 0 &&
		    sigcode < sizeof illinames / sizeof illinames[0]) {
			prints(" ("); prints(illinames[sigcode]); prints(")");
		}
		break;
	}
#endif
}

