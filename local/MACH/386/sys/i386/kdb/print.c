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
 * $Log:	print.c,v $
 * Revision 1.6.1.5  90/07/10  11:42:07  rvb
 * 	Typeo, on $>
 * 	[90/06/19            rvb]
 * 
 * Revision 1.6.1.4  90/06/07  08:04:34  rvb
 * 	Use $c when someone types $C.
 * 	[90/06/06            rvb]
 * 
 * Revision 1.6.1.3  90/05/14  13:18:52  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * 	Sync up with vax and KDB_PRINT_CASES technology.
 * 	[90/05/07            rvb]
 * 
 * Revision 1.6.1.2  90/01/08  13:27:05  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.6.1.1  89/12/21  17:57:03  rvb
 * 	Revision 1.2  89/12/05  18:07:39  kupfer
 * 	Add debugging output for 'bad modifier'.
 * 
 * Revision 1.6  89/09/25  15:21:12  rvb
 * 	Print u.u_comm on a $l.
 * 	[89/09/25            rvb]
 * 
 * Revision 1.5  89/07/17  10:37:39  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 		No more mCOMreset
 * 	[89/07/11            rvb]
 * 
 * Revision 1.4  89/03/09  20:01:59  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:35:28  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 *  8-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed $K to print specified thread's stack (<thread>$K).
 *
 *  5-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed thread state printout to accommodate new scheduling
 *	state machine.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 27-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	sigcode -> kdbsigcode.
 *
 * 15-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Have $z go to the mach_db debugger.
 *
 * 14-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Better support for MACH_TT.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Preliminary support for MACH_TT in $l command.
 *
 *  7-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made $l command print 'W' for swapped-out processes.
 *
 *  8-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added $k (old format) and $K (new format) to trace only the
 *	kernel stack.
 *
 * 16-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Support for multiple-process debugging
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Flushed the stupid #
 */

#include <mach_db.h>

/*
 *
 *	UNIX debugger
 *
 */
#include "defs.h"


#include <kern/task.h>
#include <kern/thread.h>
#include <kern/kdb_print.h>
#include <sys/proc.h>

msg		BADMOD;

map		txtmap;
map		datmap;

long		lastframe;
long		callpc;

INT		infile;
INT		outfile;
char		*lp;
long		maxoff;
long		maxpos;
INT		radix;

/* symbol management */
long		localval;

/* breakpoints */
bkpt_t		bkpthead;

extern int	*kdb_regs;

REGLIST reglist [] = {
	"eip",	EIP,	0,
	"pc",	EIP,	0,

	"eax",	EAX,	0,
	"ax",	EAX,	0,

	"ebx",	EBX,	0,
	"bx",	EBX,	0,

	"ecx",	ECX,	0,
	"cx",	ECX,	0,

	"edx",	EDX,	0,
	"dx",	EDX,	0,

	"esi",	ESI,	0,
	"si",	ESI,	0,

	"edi",	EDI,	0,
	"di",	EDI,	0,

	"esp",	ESP,	0,
	"sp",	ESP,	0,

	"ebp",	EBP,	0,
	"bp",	EBP,	0,

	"cs",	CS,	0,
	"ds",	DS,	0,
	"es",	ES,	0,
	"fs",	FS,	0,
	"gs",	GS,	0,
	"err",	ERR,	0,
	"trapno",TRAPNO,0,

	"efl",	EFL,	0,
	"flags",EFL,	0
};

#define NREGS	(sizeof(reglist)/sizeof (REGLIST))

char		lastc;

INT		fcor;
string_t		errflg;
INT		signo;
INT		kdbsigcode;


long		dot;
long		var[];
string_t	symfil;
string_t	corfil;
INT		pid;
long		adrval;
INT		adrflg;
long		cntval;
INT		cntflg;

/* general printing routines ($) */

printtrace(modif)
{
	extern long	expv;
	INT		i;
	register bkpt_t	bkptr;
	int		dr7;
	string_t	comptr;
	register struct nlist *sp;

	if ( cntflg==0 ) {
		cntval = -1;
	}

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

			if (adrflg) {
				p = pfind(dot);
			} else {
				p = pfind(curpid);	/* pid at entry */
			}
			if (p) {
				printf("proc entry at 0x%X\n", p);
				kdbgetprocess(p);
				var[varchk('m')] = (long) curmap;
				pid = p->p_pid;
			} else {
				printf("no such process");
			}
		}
		break;

	KDB_PRINT_CASES

	case 'd':
		if (adrflg) {
			if (adrval<2 || adrval>16) {
				printf("must have 2 <= radix <= 16");
				break;
			}
			printf("radix=%d base ten",radix=adrval);
		}
		break;

	case 'w':
	case 'W':
		maxpos=(adrflg?adrval:MAXPOS);
		break;

	case 's':
	case 'S':
		maxoff=(adrflg?adrval:MAXOFF);
		break;

	case 'v':
	case 'V':
		prints("variables\n");
		for ( i=0;i<=35;i++ ) {
			    if ( var[i] ) {
				printc((i<=9 ? '0' : 'a'-10) + i);
				printf(" = %X\n",var[i]);
			}
		}
		break;

	case 'M':
		vm_map_print(dot);
		break;

	case 0:
	case '?':
		if ( pid ) {
			printf("pcs id = %d\n",pid);
		} else {
			prints("no process\n");
		}
		flushbuf();

	case 'r':
	case 'R':
		printregs();
		return;

	case 'c':
	case 'C':
		oldtrace('c') ;
		break;

/*	case 'n':
	case 'N':
		newtrace(modif) ;
		break;
*/
		/*print externals*/
	case 'e':
	case 'E':
#ifdef	wheeze
#else	wheeze
		for (sp = symtab; sp < esymtab; sp++) {
			if (sp->n_type==(N_DATA|N_EXT) || sp->n_type==(N_BSS|N_EXT))
				printf("%s:%12t%R\n", sp->n_un.n_name, get(sp->n_value));
		}
#endif	wheeze
		break;

		/*print breakpoints*/
	case 'b':
		printf("bkpt\taddress\n");
		dr7 = _dr7();
		for (i = 0; i < 4; i++)
			if (dr7 & (2 << (i + i)))
				prbkpt(i);
		break;
	case 'B':
		printf("breakpoints:\ncount  bkpt address\tcommand\n");
		for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
			if (bkptr->flag) {
				printf("%-5.5d\t",bkptr->count);
				psymoff(bkptr->loc, ISYM, "\t");
				comptr=bkptr->comm;
				while ( *comptr ) {
					printc(*comptr++);
				}
			}
		break;
	case '<':
		printf("inb(%x) = %x\n", dot, inb(dot) & 0xff);
		break;
	case '>':
		if (expr(0) == 0)
			error("need value for outb");
		printf("outb(%x, %x) = %x\n", dot, expv, outb(dot, expv));
		break;
	default:
		printf("don't understand modifier 0%o\n", modif);
		error(BADMOD);
	}
}

prbkpt(n)
int n;
{
	register int pc;

	switch (n) {

	case 0:
		pc = _dr0();
		break;
	case 1:
		pc = _dr1();
		break;
	case 2:
		pc = _dr2();
		break;
	case 3:
		pc = _dr3();
		break;

	}
	printf("   %d\t", n);
	psymoff(pc, ISYM, "\n");
	return;
}

printregs()
{
	register REGPTR	p;
	long		v;
	int		i, n;

	printf("pc %9X, sp %9X, bp %9X, flags %9X\n",
		kdb_regs[EIP], kdb_regs[ESP], kdb_regs[EBP],
		kdb_regs[EFL]);

	printf("ax %9X, bx %9X, cx %9X, dx %9X\n",
		kdb_regs[EAX], kdb_regs[EBX], kdb_regs[ECX], kdb_regs[EDX]);
	printf("si %9X, di %9X, err %9X, trapno %9X\n",
		kdb_regs[ESI], kdb_regs[EDI], kdb_regs[ERR], kdb_regs[TRAPNO]);
	printf("cs %4x, ss %4x, es %4x, ds %4x, fs %4x, gs %4x\n",
		kdb_regs[CS], kdb_regs[SS], kdb_regs[ES],
		kdb_regs[DS], kdb_regs[FS], kdb_regs[GS]);

	printpc();
}

int *
getreg(regnam)
{
	register REGPTR	p;
	register string_t	regptr;
	char	*olp=lp;

	for ( p=reglist; p < &reglist[NREGS]; p++ ) {
		regptr=p->rname;

		if ( (regnam == *regptr++) ) {
			while ( *regptr ) {
				if (readchar() != *regptr++) {
					--regptr;
					break;
				}
			}
			if ( *regptr ) {
				lp=olp;
			} else {
				return (&kdb_regs[p->roffs]);
			}
		}
	}
	lp=olp;
	return(0);
}

printpc()
{
	dot = kdb_regs[EIP];
	psymoff(dot,ISYM,":%16t");
	printins(0,ISP,chkget(dot));
	printc(EOR);
}

print_stack_trace(thread)
	thread_t	thread;
{
/*	label_t		save_kdb_save;*/
	int		save_jmpbuf[6];
	extern int	jmpbuf[6];
	int		*savekdb_regs = kdb_regs;
	int		hold_regs[20];
	int		saveadrflg = adrflg;

	bcopy(jmpbuf, save_jmpbuf, sizeof jmpbuf);

	if (thread != current_thread()) {
		kdb_regs = hold_regs;
		cntxt2regs(thread->pcb, kdb_regs);
	} else {
		extern int *active_regs;

		kdb_regs = active_regs;
	}

	printf("thread 0x%X, ", thread);
	if (!kdbsetjmp(jmpbuf)) {
		printf("W_EVENT ");
		psymoff((long)thread->wait_event, ISYM, "");
		printc(EOR);
		adrflg = 0;
		oldtrace('k');
	} else {
		errflg = 0;
		printf(" FAILED\n");
	}
	adrflg = saveadrflg;

	kdb_regs = savekdb_regs;
	bcopy(save_jmpbuf, jmpbuf, sizeof jmpbuf);
}
