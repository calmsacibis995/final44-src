/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kdb_print.c	7.16 (Berkeley) 5/3/90
 */

#include "machine/mtpr.h"
#undef ISP
#include "../kdb/defs.h"
#undef CTRL
#include "ioctl.h"
#include "tty.h"
#include "vnode.h"
#include "mount.h"

char	*BADRAD;

ADDR	lastframe;
ADDR	callpc;

char	*BADMOD;
char	*lp;
long	maxpos;
int	radix;
char	lastc;

/* breakpoints */
BKPTR	bkpthead;

extern	REGLIST reglist[];

/* general printing routines ($) */

printtrace(modif)
{
	register narg, i;
	register BKPTR bkptr;
	register ADDR word;
	register char *comptr;
	register ADDR argp, frame;
	register struct nlist *sp;
	int ntramp;
	register struct proc *p;
	extern struct proc *allproc;

	if (cntflg==0)
		cntval = -1;
	switch (modif) {

	case 'd':
		if (adrflg) {
			if (adrval < 2 || adrval > 16)
				error(BADRAD);
			radix = adrval;
		}
		printf("radix=%d base ten", radix);
		break;

	case 'w': case 'W':
		printf("maxpos=%d", maxpos=(adrflg?adrval:MAXPOS));
		break;

	case 's': case 'S':
		printf("maxoff=%d", maxoff=(adrflg?adrval:MAXOFF));
		break;

	case 'V':
		printf("variables\n");
		for (i=0;i<=35;i++)
			if (var[i]) {
				printc((i<=9 ? '0' : 'a'-10) + i);
				printf(" = %R\n",var[i]);
			}
		break;

	case 0: case '?':
		if (p = (struct proc *)var[varchk('p')])
			printf("pid = %d\n", p->p_pid);
		else
			printf("in idle loop\n");
		printtrap(var[varchk('t')], var[varchk('c')]);
		/* fall thru... */
	case 'r': case 'R':
		printregs(modif);
		return;

	case 'c': case 'C':
		if (adrflg) {
			frame = adrval;
			callpc = getprevpc(frame);
		} else {
			frame = pcb.pcb_fp;
			callpc = pcb.pcb_pc;
		}
		lastframe = NOFRAME;
		ntramp = 0;
		while (cntval-- && frame != NOFRAME) {
			char *name;

			chkerr();
			/* check for pc in pcb (signal trampoline code) */
			if (issignalpc(callpc)) {
				name = "sigtramp";
				ntramp++;
			} else {
				ntramp = 0;
				(void) findsym((long)callpc, ISYM);
				if (cursym)
					name = cursym->n_un.n_name;
				else
					name = "?";
			}
			printf("%s(", name);
			narg = getnargs(frame);
			if (narg > 10)
				narg = 10;
			argp = frame;
			if (ntramp != 1)
				while (narg) {
					printf("%R",
					    get((off_t)(argp = nextarg(argp)),
					        DSP));
					if (--narg != 0)
						printc(',');
				}
			printf(") at ");
			psymoff((long)callpc, ISYM, "\n");

			if (modif=='C') {
				while (localsym((long)frame)) {
					word = get((off_t)localval, DSP);
					printf("%8t%s:%10t",
					    cursym->n_un.n_name);
					if (errflg) {
						printf("?\n");
						errflg = 0;
					} else
						printf("%R\n", word);
				}
			}
			if (ntramp != 1) {
				callpc = getprevpc(frame);
				lastframe = frame;
				frame = getprevframe(frame);
			} else
				callpc = getsignalpc(lastframe);
			if (!adrflg && !INSTACK(frame))
				break;
		}
		break;

		/*print externals*/
	case 'e': case 'E':
		for (sp = symtab; sp < esymtab; sp++)
			if (sp->n_type==(N_DATA|N_EXT) ||
			    sp->n_type==(N_BSS|N_EXT))
				printf("%s:%12t%R\n", sp->n_un.n_name,
					get((off_t)sp->n_value, DSP));
		break;

		/*print breakpoints*/
	case 'b': case 'B':
		printf("breakpoints\ncount%8tbkpt%24tcommand\n");
		for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
			if (bkptr->flag) {
		   		printf("%-8.8d",bkptr->count);
				psymoff((long)bkptr->loc,ISYM,"%24t");
				comptr=bkptr->comm;
				while (*comptr)
					printc(*comptr++);
			}
		break;

	case 'k':
		panic("kdb requested panic");
		/* NOTREACHED */

	case 'l': {
		struct pte savemmap;
		extern char vmmap[];

		savemmap = mmap[0];
		for (p = allproc; p; p = p->p_nxt) {
			printf("%X pid %5d%c%5d %c ", p, p->p_pid,
				p == (struct proc *)var[varchk('p')]? '*' : ' ',
				p->p_ppid,
				p->p_stat == SSLEEP ? 'S' :
				p->p_stat == SRUN ? 'R':
				p->p_stat == SIDL ? 'I':
				p->p_stat == SSTOP ? 'T' : '?');
			if (p->p_wchan)
				psymoff((long)p->p_wchan, ISYM, "");
			if ((p->p_flag & SLOAD) && p->p_addr) {
				int i;
				*(int *)mmap = *(int *)p->p_addr;
				mtpr(TBIS, vmmap);
#define U	((struct user *)vmmap)
#ifdef not_until_uarea_completely_mapped
				if (U->u_ttyp)
					printf(" ctty %x ", U->u_ttyp);
#endif
				printf(" %.8s ", p->p_comm);
#undef U
			}

			printc(EOR);
		}
		mmap[0] = savemmap;
		mtpr(TBIS, vmmap);
		break;
	}

	case 't':	/* XXX - debug */
		if (adrflg) {
		      printf("dev       state  rawq   canq  outq  lwat hwat\n");

#define T	((struct tty *)adrval)	
			printf("%x  %x %d %d %d %d %d\n", T->t_dev, 
				T->t_state, T->t_rawq.c_cc, 
				T->t_canq.c_cc, T->t_outq.c_cc,
				T->t_lowat, T->t_hiwat);
	       printf(" &rawq    &canq      &outq    &outq.c_cf  &rawq.c_cf\n");
	       		printf(" %x %x  %x %x %x \n", &T->t_rawq, 
				&T->t_canq, &T->t_outq, &T->t_outq.c_cf, 
				&T->t_rawq.c_cf);
#undef T
		}

	case 'v': {
		register struct mount *mp;
		register struct vnode *vp;

		printf("Locked vnodes\n");
		mp = rootfs;
		do {
			for (vp = mp->m_mounth; vp; vp = vp->v_mountf)
				if (VOP_ISLOCKED(vp))
					vprint((char *)0, vp);
			mp = mp->m_next;
		} while (mp != rootfs);
		break;
	}

	default:
		error(BADMOD);
	}
}

static
printregs(c)
{
	register REGPTR	p;
	ADDR v;

	for (p = reglist; p->rname; p++) {
		if (c != 'R' && ishiddenreg(p))
			continue;
		v = *p->rkern;
		printf("%s%6t%R %16t", p->rname, v);
		valpr((long)v, p->rkern == &pcb.pcb_pc ? ISYM : DSYM);
		printc(EOR);
	}
	printpc();
}

getreg(regnam)
{
	register REGPTR	p;
	register char *regptr;
	char *olp;

	olp = lp;
	for (p = reglist; p->rname; p++) {
		regptr = p->rname;
		if (regnam == *regptr++) {
			while (*regptr)
				if (readchar() != *regptr++) {
					--regptr;
					break;
				}
			if (*regptr)
				lp = olp;
			else
				return ((int)p->rkern);
		}
	}
	lp = olp;
	return (-1);
}

printpc()
{

	psymoff((long)pcb.pcb_pc, ISYM, ":%16t");
	printins(ISP, (long)chkget((off_t)pcb.pcb_pc, ISP));
	printc(EOR);
}
