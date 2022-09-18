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
 * Revision 2.6  89/03/09  22:18:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:23:57  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/24  03:00:54  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:07:38  mwyoung]
 * 
 *
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed more lint.
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

#include <vax/kdb/defs.h>
#include <vax/kdb/fp.h>

#define R_0_5  "    R0        R1        R2        R3        R4        R5\n"
#define R_6_11 "    R6        R7        R8        R9        R10       R11\n"
#define R_INDENT "                   "

static int dump = 0;

long lastframe;
long callpc;
long lastfp;
long rpc;

char *errflg;

long dot;
long adrval;
short adrflg;
long cntval;
short cntflg;

#define IN_KERNEL_STACK(x)	((unsigned)(x) >= (unsigned)(0x80000000))

oldtrace(modif)
{
	short narg ;
	long word;
	long argp, frame;
	short ntramp;
	long trap_argp;
	if ( adrflg ) {
		frame=adrval;
		word=get(adrval+6,DSP)&0xFFFF;
		if ( word&0x2000 ) {
			argp=adrval+20+((word>>14)&3);
			word &= 0xFFF;
			while ( word ) {
				if ( word&1 ) {
					argp+=4;
				}
				word>>=1;
			}
		} else {
			argp=frame;
		}
		callpc=get(frame+16,DSP);
	} else if ( kcore ) {
		argp = curpcb->pcb_ap;
		frame = curpcb->pcb_fp;
		callpc = curpcb->pcb_pc;
	} else {
		argp= *(long *)(((long)&u)+AP);
		frame= *(long *)(((long)&u)+FP);
		callpc= *(long *)(((long)&u)+PC);
	}
	lastframe=0;
	ntramp = 0;
	while ( cntval-- ) {
		char *name;
		chkerr();
		trap_argp = 0;
		if (callpc > 0x80000000 - 0x200 * UPAGES) {
			name = "sigtramp";
			ntramp++;
		} else {
			ntramp = 0;
			findsym(callpc,ISYM);
			if (cursym &&
			    !strcmp(cursym->n_un.n_name, "start"))
				break;
			if (cursym)
				name = cursym->n_un.n_name;
			else
				name = "?";
			if (IN_KERNEL_STACK(frame) && !strcmp(name, "_trap")) {
				/*
				 *	call from Trap routine.
				 *	Its argument list is:
				 *	(usp, type, code, pc, psl)
				 */
				trap_argp = argp;
			}
		}
		printf("%s(", name);
		narg = get(argp,DSP);
		if ( narg&~0xFF ) {
			narg=0;
		}
		if (trap_argp)
			narg = 5;
		for ( ; ; ) {
			if ( narg==0 ) {
				break;
			}
			printf("%R", get(argp += 4, DSP));
			if ( --narg!=0 ) {
				printc(',');
			}
		}
		printf(") from %X\n",callpc);  /* jkf mod */

		if ( modif=='C' ) {
			while ( localsym(frame,argp) ) {
				word=get(localval,DSP);
				printf("%8t%s:%10t", cursym->n_un.n_name);
				if ( errflg ) {
					prints("?\n");
					errflg=0;
				} else {
					printf("%R\n",word);
				}
			}
		}

		if (trap_argp)
			callpc = get(trap_argp + 4*4, DSP);	/* pc in trap arg list */
		else
			if (ntramp == 1)
				callpc=get(frame+84, DSP);
			else
				callpc=get(frame+16, DSP);
		argp=get(frame+8, DSP);
		lastframe=frame;
		frame=get(frame+12, DSP)&EVEN;
		if (frame == 0)
			break;
		if (!IN_KERNEL_STACK(frame)) {
			if (modif == 'k')
				break;	/* kernel stack only */
			if (!adrflg && !INSTACK(frame))
				break;
		}
	}
}

newtrace(modif)
{
	long word;
	long ap, fp;
	short ntramp;

	if ( adrflg ) {
		fp=adrval;
		word=get(adrval+6,DSP)&0xFFFF;
		if ( word&0x2000 ) {
			ap=adrval+20+((word>>14)&3);
			word &= 0xFFF;
			while ( word ) {
				if ( word&1 ) {
					ap+=4;
				}
				word>>=1;
			}
		} else {
			ap=fp;
		}
		rpc=get(fp+16,DSP);
	} else if ( kcore ) {
		ap = curpcb->pcb_ap;
		fp = curpcb->pcb_fp;
		rpc = curpcb->pcb_pc;
	} else {
		ap= *(long *)(((long)&u)+AP);
		fp= *(long *)(((long)&u)+FP);
		rpc= *(long *)(((long)&u)+PC);
	}
	lastfp=0;
	ntramp = 0;
	while ( cntval-- ) {
		char *name;
		chkerr();
		if (rpc > 0x80000000 - 0x200 * UPAGES) {
			name = "sigtramp";
			ntramp++;
		} else {
			ntramp = 0;
			findsym(rpc,ISYM);
			if (cursym &&
			    !strcmp(cursym->n_un.n_name, "start"))
				break;
			if (cursym)
				name = cursym->n_un.n_name;
			else
				name = "?";
		}

		if (one_stack_frame(fp, ap) < 0)
			return ;

		if (ntramp == 1)
			rpc=get(fp+84, DSP);
		else
			rpc=get(fp+16, DSP);

		ap=get(fp+8, DSP);
		lastfp=fp;
		fp=get(fp+12, DSP)&EVEN;
		if (kernel && ((unsigned) rpc) < (unsigned) 0x80000000)
			return ;
		if ( fp==0 || (!adrflg && !INSTACK(fp)) ) {
			break;
		}
		if (modif == 'K' && ! IN_KERNEL_STACK(fp)) {
			/*
			 * crossed to user stack - stop to avoid fault
			 */
			break;
		}
#ifdef	lint
		if (name) panic(""); /* XXX reference name, rather than fixing the problem */
#endif	lint
	}
}

#define bget(ptr) (0377 & (get(ptr, DSP)))

one_stack_frame(fp, ap)
register struct frame *fp ;
register int *ap ;
{
	register int *sp ;
#define cnt	local_cnt	/* For lint */
	register int cnt ;


	sp = ap + (get(ap, DSP)) + 1 ;	/* from end of args to mp fp*/

	if (dump) {
		register int *ip = (int *) fp ;
		for (cnt = 0; cnt < 18; cnt++) {
			if ( !(cnt&3) ) printf("\n%08X:\t", ip) ;
			printf(" %8X ", (get(ip++, DSP))) ;
		}
		printf("\n") ;
	}

	if (dump)
		printf("fp = %X, ap = %X(#%D), sp = %X(#%X), nfp = %X\n",
		fp, ap, (get(ap, DSP)), sp,
		(int *) (get(&fp->f_fp, DSP)) - sp,
		(get(&fp->f_fp, DSP)) ) ;

	/* call  */
	{
#define rpc	local_rpc	/* For lint */
		register unsigned char *rpc ;
		register unsigned char *cpc ;
		int svdot;

		rpc = (unsigned char *)(get(&fp->f_pc, DSP)) ;
		cpc = rpc - 8 ;

		if (dump)
			printf("*cpc(%X) = %X, *pc-4 = %X, *rpc(%X) = %X\n",
			cpc, (get((int *)cpc, DSP)),
			(get((int *)(rpc-4), DSP)), rpc,
			(get((int *)rpc, DSP)));

		/*
			 printf("%08X: calls $%D,", rpc, (get(ap, DSP))) ;
		*/
		psymoff(rpc, ISYM, ": ") ;

		while ( (cnt = bget(cpc++)) != 0xfb && cnt != 0xfa && cpc < rpc) ;

		switch (cnt) {
		case 0:
			printf("calls $%D,", (get(ap, DSP))) ;
			if (bget(cpc++) == (get(ap, DSP)) )	/* calls $#, ... */
				switch (cnt = bget(cpc++)) {
				case 0xef:	/* word rel */
					/*
									printf("%04x(", rpc +(get((int *) cpc, DSP)));
									*/
					psymoff(rpc+(get((int *)cpc, DSP)), ISYM, "(");
					break ;
				case 0x60:
					printf("(r0)(") ;
					break ;
				default:
					printf("??%x??%x??(", cnt, cnt) ;
				} else
				printf("calls #!=(") ;
			break ;
/*calls*/case 0xfa:
/*calls*/case 0xfb:
			svdot = dot ;
			dot = (int)--cpc ;
			printins(0, DSP, chkget(cpc, DSP)) ;
			printf("(") ;
			dot = svdot ;
			break ;
		default:
			printf("not a call(") ;
			return (-1) ;
		}

		/* args */
		for (cnt = (get(ap++, DSP)) ; cnt-- > 0 ;)
			printf("%X%s", (get(ap++, DSP)), cnt ? ", " : "") ;
	}
	printf(")\n") ;
#undef	rpc

	/* regs */
	{
		register int *rp = fp->f_r0 ;
		int mskword ;
		register msk ;

		mskword = (get(&fp->f_msk, DSP)) ;
		msk = ((struct f_fm *) &mskword)->fm_mask ;

		if (msk & 0x3f) {	/* first 6 saved */
			printf(R_INDENT) ;
			printf(R_0_5) ;
			printf(R_INDENT) ;
			for (cnt = 0 ; cnt < 6; cnt++ ) {
				if (msk & (1<<cnt))
					printf(" %08X ", (get(rp++, DSP))) ;
				else
					printf("   ????   ") ;
			}
			printf("\n") ;
		}

		printf(R_INDENT) ;
		printf(R_6_11) ;
		printf(R_INDENT) ;
		for (cnt = 6 ; cnt < 12; cnt++ ) {
			if (msk & (1<<cnt))
				printf(" %08X ", (get(rp++, DSP))) ;
			else
				printf("   ????   ") ;
		}
		printf("\n\n") ;
	}

	/* autos */
	{
		register int *nfp ;
		register int del ;

		nfp = (int *) (get(&fp->f_fp, DSP)) ;
		if ( (del = cnt = ((char *) nfp - (char *) sp) ) < 0)
			return (0);	/* used ti be -1 */
		while( sp < nfp ) {
			printf(R_INDENT) ;
			for (; (del - cnt) < 24 && (cnt > 0); cnt -= 4)
				printf("  -%02X(fp) ", cnt) ;
			printf("\n") ;
			printf(R_INDENT) ;
			for ( ; cnt != del; del -=4)
				printf(" %08X ", (get(sp++, DSP))) ;
			printf("\n") ;
		}
		printf("\n") ;
	}

	return (1) ;
#undef	cnt
}
