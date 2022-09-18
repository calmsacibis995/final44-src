h32189
s 00001/00001/00223
d D 7.22 91/05/25 15:27:16 bostic 22 21
c delete obsolete printf formats (%X -> %lx)
e
s 00004/00013/00220
d D 7.21 91/05/12 16:55:05 mckusick 21 20
c code for printing locked vnodes moves to vfs_subr.c
e
s 00001/00000/00232
d D 7.20 90/12/16 16:38:12 bostic 20 19
c kernel reorg
e
s 00002/00069/00230
d D 7.19 90/06/22 15:44:33 sklower 19 18
c changes to accomodage vax specific printing of stack
e
s 00002/00002/00297
d D 7.18 90/05/04 20:57:15 mckusick 18 17
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00097/00097/00202
d D 7.17 90/05/03 17:47:11 sklower 17 16
c first crack at torek changes, may need bug fixes
e
s 00001/00001/00298
d D 7.16 90/05/03 15:44:59 marc 16 15
c comm moved to proc
e
s 00016/00029/00283
d D 7.15 90/01/15 18:43:22 mckusick 15 14
c get rid of $i and replace with $v to print out vnodes 
c with underlying object locked
e
s 00006/00000/00306
d D 7.14 89/12/30 22:35:55 mckusick 14 13
c debugging, print out inode lock owner and waiter
e
s 00001/00002/00305
d D 7.13 89/11/30 12:39:59 mckusick 13 12
c use vprint
e
s 00013/00007/00294
d D 7.12 89/11/25 22:26:09 mckusick 12 11
c do NOT use v_tag; rather search ufs mount table to find inodes
e
s 00005/00001/00296
d D 7.11 89/10/24 18:34:03 mckusick 11 10
c inode table is replaced by a vnode table
e
s 00006/00005/00291
d D 7.10 89/10/13 16:36:52 karels 10 9
c tune up $l format
e
s 00004/00000/00292
d D 7.9 89/08/26 00:32:51 mckusick 9 8
c add $k command to kill the kernel (kdb requested panic)
e
s 00015/00000/00277
d D 7.8 89/06/10 08:42:18 mckusick 8 7
c add $i to print out locked inodes
e
s 00043/00003/00234
d D 7.7 89/05/11 12:12:48 marc 7 6
c add $l $t commands
e
s 00002/00000/00235
d D 7.6 89/04/25 10:02:01 mckusick 6 5
c clamp number of arguments printed to 10 to avoid infinite output
e
s 00020/00013/00215
d D 7.5 86/12/15 20:26:51 sam 5 4
c lint
e
s 00029/00048/00199
d D 7.4 86/11/23 13:36:04 sam 4 3
c move machine dependencies to ../machine/kdbparam.h
e
s 00009/00005/00238
d D 7.3 86/11/20 15:48:58 sam 3 2
c keep trap info around as well as current proc; move printing 
c of this stuff into machine-dependent routine
e
s 00008/00010/00235
d D 7.2 86/11/20 14:44:40 sam 2 1
c put back old radix handling; print current values on $s and $w
e
s 00245/00000/00000
d D 7.1 86/11/20 12:22:06 sam 1 0
c date and time created 86/11/20 12:22:06 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 5

I 7
#include "machine/mtpr.h"
#undef ISP
I 20
#undef TB
E 20
E 7
#include "../kdb/defs.h"
I 7
#undef CTRL
I 10
#include "ioctl.h"
E 10
#include "tty.h"
I 8
#include "vnode.h"
I 12
#include "mount.h"
E 12
D 15
#include "../ufs/inode.h"
I 12
#include "../ufs/ufsmount.h"
E 15
E 12
E 8
E 7

I 2
D 17
char	*BADRAD;
E 17
I 17
char	*kdbBADRAD;
E 17

E 2
D 17
ADDR	lastframe;
ADDR	callpc;
E 17
I 17
D 19
ADDR	kdblastframe;
ADDR	kdbcallpc;
E 17

E 19
D 17
char	*BADMOD;
char	*lp;
long	maxpos;
int	radix;
char	lastc;
E 17
I 17
char	*kdbBADMOD;
char	*kdblp;
long	kdbmaxpos;
int	kdbradix;
char	kdblastc;
E 17

/* breakpoints */
D 17
BKPTR	bkpthead;
E 17
I 17
BKPTR	kdbbkpthead;
E 17

D 4
REGLIST reglist[] = {
	"p2lr",	&pcb.pcb_p2lr,	"p2br",	(int *)&pcb.pcb_p2br,
	"p1lr",	&pcb.pcb_p1lr,	"p1br",	(int *)&pcb.pcb_p1br,
	"p0lr",	&pcb.pcb_p0lr,	"p0br",	(int *)&pcb.pcb_p0br,
	"ksp",	&pcb.pcb_ksp,	"hfs",	&pcb.pcb_hfs,
	"psl",	&pcb.pcb_psl,	"pc",	&pcb.pcb_pc,
	"ach",	&pcb.pcb_ach,	"acl",	&pcb.pcb_acl,
	"usp",	&pcb.pcb_usp,	"fp",	&pcb.pcb_fp,
	"r12",	&pcb.pcb_r12,	"r11",	&pcb.pcb_r11,
	"r10",	&pcb.pcb_r10,	"r9",	&pcb.pcb_r9,
	"r8",	&pcb.pcb_r8,	"r7",	&pcb.pcb_r7,
	"r6",	&pcb.pcb_r6,	"r5",	&pcb.pcb_r5,
	"r4",	&pcb.pcb_r4,	"r3",	&pcb.pcb_r3,
	"r2",	&pcb.pcb_r2,	"r1",	&pcb.pcb_r1,
	"r0",	&pcb.pcb_r0,
	0
};
E 4
I 4
D 17
extern	REGLIST reglist[];
E 17
I 17
extern	REGLIST kdbreglist[];
E 17
E 4

/* general printing routines ($) */

D 17
printtrace(modif)
E 17
I 17
kdbprinttrace(modif)
E 17
{
D 19
	register narg, i;
E 19
I 19
	register int i;
E 19
	register BKPTR bkptr;
D 19
	register ADDR word;
E 19
	register char *comptr;
D 19
	register ADDR argp, frame;
E 19
	register struct nlist *sp;
D 5
	int stack, ntramp;
E 5
I 5
D 19
	int ntramp;
E 19
E 5
I 3
D 10
	register struct  proc *p;
E 10
I 10
	register struct proc *p;
E 10
	extern struct proc *allproc;
E 3

D 17
	if (cntflg==0)
		cntval = -1;
E 17
I 17
	if (kdbcntflg==0)
		kdbcntval = -1;
E 17
	switch (modif) {

	case 'd':
D 17
		if (adrflg) {
D 2
			if (!(adrval>=2 &&
			      adrval<=16 || adrval<=-2 && adrval>=-16)) {
				printf("illegal radix %d base ten", radix);
				break;
			}
			radix=adrval;
E 2
I 2
			if (adrval < 2 || adrval > 16)
				error(BADRAD);
			radix = adrval;
E 17
I 17
		if (kdbadrflg) {
			if (kdbadrval < 2 || kdbadrval > 16)
				kdberror(kdbBADRAD);
			kdbradix = kdbadrval;
E 17
E 2
		}
D 2
		printf("radix=%d base ten",radix);
E 2
I 2
D 17
		printf("radix=%d base ten", radix);
E 17
I 17
		kdbprintf("radix=%d base ten", kdbradix);
E 17
E 2
		break;

	case 'w': case 'W':
D 2
		maxpos=(adrflg?adrval:MAXPOS);
E 2
I 2
D 17
		printf("maxpos=%d", maxpos=(adrflg?adrval:MAXPOS));
E 17
I 17
		kdbprintf("maxpos=%d", kdbmaxpos=(kdbadrflg?kdbadrval:MAXPOS));
E 17
E 2
		break;

	case 's': case 'S':
D 2
		maxoff=(adrflg?adrval:MAXOFF);
E 2
I 2
D 17
		printf("maxoff=%d", maxoff=(adrflg?adrval:MAXOFF));
E 17
I 17
		kdbprintf("maxoff=%d", kdbmaxoff=(kdbadrflg?kdbadrval:MAXOFF));
E 17
E 2
		break;

D 15
	case 'v': case 'V':
E 15
I 15
	case 'V':
E 15
D 17
		printf("variables\n");
E 17
I 17
		kdbprintf("variables\n");
E 17
		for (i=0;i<=35;i++)
D 17
			if (var[i]) {
				printc((i<=9 ? '0' : 'a'-10) + i);
				printf(" = %R\n",var[i]);
E 17
I 17
			if (kdbvar[i]) {
				kdbprintc((i<=9 ? '0' : 'a'-10) + i);
				kdbprintf(" = %R\n",kdbvar[i]);
E 17
			}
		break;

	case 0: case '?':
I 3
D 17
		if (p = (struct proc *)var[varchk('p')])
			printf("pid = %d\n", p->p_pid);
E 17
I 17
		if (p = (struct proc *)kdbvar[kdbvarchk('p')])
			kdbprintf("pid = %d\n", p->p_pid);
E 17
		else
D 17
			printf("in idle loop\n");
		printtrap(var[varchk('t')], var[varchk('c')]);
E 17
I 17
			kdbprintf("in idle loop\n");
		kdbprinttrap(kdbvar[kdbvarchk('t')], kdbvar[kdbvarchk('c')]);
E 17
		/* fall thru... */
E 3
D 2

E 2
	case 'r': case 'R':
D 17
		printregs(modif);
E 17
I 17
		kdbprintregs(modif);
E 17
		return;

	case 'c': case 'C':
D 17
		if (adrflg) {
D 4
			frame=adrval;
			callpc=get(frame-8,DSP);
E 4
I 4
			frame = adrval;
			callpc = getprevpc(frame);
E 17
I 17
D 19
		if (kdbadrflg) {
			frame = kdbadrval;
			kdbcallpc = getprevpc(frame);
E 17
E 4
		} else {
D 17
			frame = pcb.pcb_fp;
			callpc = pcb.pcb_pc;
E 17
I 17
			frame = kdbpcb.pcb_fp;
			kdbcallpc = kdbpcb.pcb_pc;
E 17
		}
D 4
		lastframe=0;
E 4
I 4
D 17
		lastframe = NOFRAME;
E 17
I 17
		kdblastframe = NOFRAME;
E 17
E 4
		ntramp = 0;
D 4
		while (cntval-- && frame!=0) {
E 4
I 4
D 17
		while (cntval-- && frame != NOFRAME) {
E 17
I 17
		while (kdbcntval-- && frame != NOFRAME) {
E 17
E 4
			char *name;

D 17
			chkerr();
E 17
I 17
			kdbchkerr();
E 17
			/* check for pc in pcb (signal trampoline code) */
D 4
			if (MAXSTOR < callpc &&
			   callpc < MAXSTOR+ctob(UPAGES)) {
E 4
I 4
D 17
			if (issignalpc(callpc)) {
E 17
I 17
			if (issignalpc(kdbcallpc)) {
E 17
E 4
				name = "sigtramp";
				ntramp++;
			} else {
				ntramp = 0;
D 4
				findsym(callpc,ISYM);
E 4
I 4
D 5
				findsym(callpc, ISYM);
E 5
I 5
D 17
				(void) findsym((long)callpc, ISYM);
E 5
E 4
				if (cursym)
					name = cursym->n_un.n_name;
E 17
I 17
				(void) kdbfindsym((long)kdbcallpc, ISYM);
				if (kdbcursym)
					name = kdbcursym->n_un.n_name;
E 17
				else
					name = "?";
			}
D 17
			printf("%s(", name);
E 17
I 17
			kdbprintf("%s(", name);
E 17
D 4
			narg = ((get(frame-4, DSP)&0xffff)-4)/4;
E 4
I 4
			narg = getnargs(frame);
I 6
			if (narg > 10)
				narg = 10;
E 6
E 4
			argp = frame;
			if (ntramp != 1)
D 4
				for (;;) {
					if (narg==0)
						break;
					printf("%R", get(argp += 4, DSP));
					if (--narg!=0)
E 4
I 4
				while (narg) {
D 17
					printf("%R",
D 5
					    get(argp = nextarg(argp), DSP));
E 5
I 5
					    get((off_t)(argp = nextarg(argp)),
E 17
I 17
					kdbprintf("%R",
					    kdbget((off_t)(argp = nextarg(argp)),
E 17
					        DSP));
E 5
					if (--narg != 0)
E 4
D 17
						printc(',');
E 17
I 17
						kdbprintc(',');
E 17
				}
D 17
			printf(") at ");
D 5
			psymoff(callpc, ISYM, "\n");
E 5
I 5
			psymoff((long)callpc, ISYM, "\n");
E 17
I 17
			kdbprintf(") at ");
			kdbpsymoff((long)kdbcallpc, ISYM, "\n");
E 17
E 5

			if (modif=='C') {
D 4
				while (localsym(frame,argp)) {
					word=get(localval,DSP);
E 4
I 4
D 5
				while (localsym(frame, argp)) {
					word = get(localval, DSP);
E 5
I 5
D 17
				while (localsym((long)frame)) {
					word = get((off_t)localval, DSP);
E 5
E 4
					printf("%8t%s:%10t",
					    cursym->n_un.n_name);
					if (errflg) {
						printf("?\n");
D 4
						errflg=0;
E 4
I 4
						errflg = 0;
E 17
I 17
				while (kdblocalsym((long)frame)) {
					word = kdbget((off_t)kdblocalval, DSP);
					kdbprintf("%8t%s:%10t",
					    kdbcursym->n_un.n_name);
					if (kdberrflg) {
						kdbprintf("?\n");
						kdberrflg = 0;
E 17
E 4
					} else
D 4
						printf("%R\n",word);
E 4
I 4
D 17
						printf("%R\n", word);
E 17
I 17
						kdbprintf("%R\n", word);
E 17
E 4
				}
			}
			if (ntramp != 1) {
D 4
				callpc = get(frame-8, DSP);
E 4
I 4
D 17
				callpc = getprevpc(frame);
E 4
				lastframe = frame;
E 17
I 17
				kdbcallpc = getprevpc(frame);
				kdblastframe = frame;
E 17
D 4
				frame = get(frame, DSP)&ALIGN;
E 4
I 4
				frame = getprevframe(frame);
E 4
			} else
D 4
				callpc = get(lastframe+44, DSP);
			if (frame == 0 || (!adrflg && !INSTACK(frame)))
E 4
I 4
D 17
				callpc = getsignalpc(lastframe);
			if (!adrflg && !INSTACK(frame))
E 17
I 17
				kdbcallpc = getsignalpc(kdblastframe);
			if (!kdbadrflg && !INSTACK(frame))
E 17
E 4
				break;
		}
E 19
I 19
		kdbstacktrace(modif == 'C');
E 19
		break;

		/*print externals*/
	case 'e': case 'E':
D 17
		for (sp = symtab; sp < esymtab; sp++)
E 17
I 17
		for (sp = kdbsymtab; sp < kdbesymtab; sp++)
E 17
			if (sp->n_type==(N_DATA|N_EXT) ||
			    sp->n_type==(N_BSS|N_EXT))
D 17
				printf("%s:%12t%R\n", sp->n_un.n_name,
D 5
					get(sp->n_value,DSP));
E 5
I 5
					get((off_t)sp->n_value, DSP));
E 17
I 17
				kdbprintf("%s:%12t%R\n", sp->n_un.n_name,
					kdbget((off_t)sp->n_value, DSP));
E 17
E 5
		break;

		/*print breakpoints*/
	case 'b': case 'B':
D 17
		printf("breakpoints\ncount%8tbkpt%24tcommand\n");
		for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
E 17
I 17
		kdbprintf("breakpoints\ncount%8tbkpt%24tcommand\n");
		for (bkptr=kdbbkpthead; bkptr; bkptr=bkptr->nxtbkpt)
E 17
			if (bkptr->flag) {
D 17
		   		printf("%-8.8d",bkptr->count);
D 5
				psymoff(bkptr->loc,ISYM,"%24t");
E 5
I 5
				psymoff((long)bkptr->loc,ISYM,"%24t");
E 17
I 17
		   		kdbprintf("%-8.8d",bkptr->count);
				kdbpsymoff((long)bkptr->loc,ISYM,"%24t");
E 17
E 5
				comptr=bkptr->comm;
				while (*comptr)
D 17
					printc(*comptr++);
E 17
I 17
					kdbprintc(*comptr++);
E 17
			}
		break;
I 8

D 15
	case 'i': {
I 11
		register struct vnode *vp;
E 11
		register struct inode *ip;
I 12
		register struct ufsmount *ump;
E 12

		printf("Locked inodes\n");
D 11
		for (ip = inode; ip < inodeNINODE; ip++) {
E 11
I 11
D 12
		for (vp = vnode; vp < vnodeNVNODE; vp++) {
			if (vp->v_tag != VT_UFS)
E 12
I 12
		for (ump = &mounttab[0]; ump < &mounttab[NMOUNT]; ump++) {
			if (ump->um_fs == NULL)
E 12
				continue;
D 12
			ip = VTOI(vp);
E 11
			if ((ip->i_flag & ILOCKED) == 0)
				continue;
			printf("inode %d dev 0x%x type %d\n", ip->i_number,
				ip->i_dev, ITOV(ip)->v_type);
E 12
I 12
			for (vp = ump->um_mountp->m_mounth;
			     vp; vp = vp->v_mountf) {
				ip = VTOI(vp);
				if ((ip->i_flag & ILOCKED) == 0)
					continue;
D 13
				printf("inode %d dev 0x%x type %d\n",
				    ip->i_number, ip->i_dev, vp->v_type);
E 13
I 13
				vprint((char *)0, vp);
I 14
				if (ip->i_spare0 == 0)
					continue;
				printf("\towner pid %d", ip->i_spare0);
				if (ip->i_spare1)
					printf(" waiting pid %d", ip->i_spare1);
				printf("\n");
E 14
E 13
			}
E 12
		}
		break;
	}
E 8

E 15
I 9
	case 'k':
		panic("kdb requested panic");
		/* NOTREACHED */

E 9
D 3
	case 'l': {
		register struct  proc *p;
		extern struct proc *allproc;

E 3
I 3
D 7
	case 'l':
E 7
I 7
	case 'l': {
		struct pte savemmap;
		extern char vmmap[];

		savemmap = mmap[0];
E 7
E 3
		for (p = allproc; p; p = p->p_nxt) {
D 7
			printf("%X pid %5d %c", p, p->p_pid,
E 7
I 7
D 10
			printf("%X pid %5d %5d %c", p, p->p_pid, p->p_ppid,
E 10
I 10
D 17
			printf("%X pid %5d%c%5d %c ", p, p->p_pid,
				p == (struct proc *)var[varchk('p')]? '*' : ' ',
E 17
I 17
D 22
			kdbprintf("%X pid %5d%c%5d %c ", p, p->p_pid,
E 22
I 22
			kdbprintf("%lx pid %5d%c%5d %c ", p, p->p_pid,
E 22
				p == (struct proc *)kdbvar[kdbvarchk('p')]? '*' : ' ',
E 17
				p->p_ppid,
E 10
E 7
				p->p_stat == SSLEEP ? 'S' :
				p->p_stat == SRUN ? 'R':
				p->p_stat == SIDL ? 'I':
				p->p_stat == SSTOP ? 'T' : '?');
D 10
			if (p->p_wchan) {
				printf(" wait ");
E 10
I 10
			if (p->p_wchan)
E 10
D 5
				psymoff(p->p_wchan, ISYM, "");
E 5
I 5
D 17
				psymoff((long)p->p_wchan, ISYM, "");
E 17
I 17
				kdbpsymoff((long)p->p_wchan, ISYM, "");
E 17
E 5
D 10
			}
E 10
I 7
			if ((p->p_flag & SLOAD) && p->p_addr) {
				int i;
				*(int *)mmap = *(int *)p->p_addr;
				mtpr(TBIS, vmmap);
#define U	((struct user *)vmmap)
#ifdef not_until_uarea_completely_mapped
				if (U->u_ttyp)
D 17
					printf(" ctty %x ", U->u_ttyp);
E 17
I 17
					kdbprintf(" ctty %x ", U->u_ttyp);
E 17
#endif
D 16
				printf(" %.8s ", U->u_comm);
E 16
I 16
D 17
				printf(" %.8s ", p->p_comm);
E 17
I 17
				kdbprintf(" %.8s ", p->p_comm);
E 17
E 16
#undef U
			}

E 7
D 17
			printc(EOR);
E 17
I 17
			kdbprintc(EOR);
E 17
		}
I 7
		mmap[0] = savemmap;
		mtpr(TBIS, vmmap);
E 7
		break;
I 7
	}

	case 't':	/* XXX - debug */
D 17
		if (adrflg) {
		      printf("dev       state  rawq   canq  outq  lwat hwat\n");
E 17
I 17
		if (kdbadrflg) {
		      kdbprintf("dev       state  rawq   canq  outq  lwat hwat\n");
E 17

D 17
#define T	((struct tty *)adrval)	
			printf("%x  %x %d %d %d %d %d\n", T->t_dev, 
E 17
I 17
#define T	((struct tty *)kdbadrval)	
			kdbprintf("%x  %x %d %d %d %d %d\n", T->t_dev, 
E 17
				T->t_state, T->t_rawq.c_cc, 
				T->t_canq.c_cc, T->t_outq.c_cc,
				T->t_lowat, T->t_hiwat);
D 17
	       printf(" &rawq    &canq      &outq    &outq.c_cf  &rawq.c_cf\n");
	       		printf(" %x %x  %x %x %x \n", &T->t_rawq, 
E 17
I 17
	       kdbprintf(" &rawq    &canq      &outq    &outq.c_cf  &rawq.c_cf\n");
	       		kdbprintf(" %x %x  %x %x %x \n", &T->t_rawq, 
E 17
				&T->t_canq, &T->t_outq, &T->t_outq.c_cf, 
				&T->t_rawq.c_cf);
#undef T
		}
I 15

D 21
	case 'v': {
		register struct mount *mp;
		register struct vnode *vp;

D 17
		printf("Locked vnodes\n");
E 17
I 17
		kdbprintf("Locked vnodes\n");
E 17
		mp = rootfs;
		do {
D 18
			for (vp = mp->m_mounth; vp; vp = vp->v_mountf)
E 18
I 18
			for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf)
E 18
				if (VOP_ISLOCKED(vp))
					vprint((char *)0, vp);
D 18
			mp = mp->m_next;
E 18
I 18
			mp = mp->mnt_next;
E 18
		} while (mp != rootfs);
E 21
I 21
#ifdef DEBUG
	case 'v':
		printlockedvnodes();
E 21
		break;
D 21
	}
E 21
I 21
#endif
E 21
E 15
E 7
D 3
	}
E 3

	default:
D 17
		error(BADMOD);
E 17
I 17
		kdberror(kdbBADMOD);
E 17
	}
}

static
D 17
printregs(c)
E 17
I 17
kdbprintregs(c)
E 17
{
	register REGPTR	p;
	ADDR v;

D 4
	for (p=reglist; p->rname; p++) {
		if (c!='R' && p->rkern!=&pcb.pcb_psl)
E 4
I 4
D 17
	for (p = reglist; p->rname; p++) {
E 17
I 17
	for (p = kdbreglist; p->rname; p++) {
E 17
		if (c != 'R' && ishiddenreg(p))
E 4
			continue;
D 4
		c = 'R';
E 4
		v = *p->rkern;
D 17
		printf("%s%6t%R %16t", p->rname, v);
D 4
		valpr(v,(p->rkern==&pcb.pcb_pc?ISYM:DSYM));
E 4
I 4
D 5
		valpr(v, p->rkern == &pcb.pcb_pc ? ISYM : DSYM);
E 5
I 5
		valpr((long)v, p->rkern == &pcb.pcb_pc ? ISYM : DSYM);
E 5
E 4
		printc(EOR);
E 17
I 17
		kdbprintf("%s%6t%R %16t", p->rname, v);
		kdbvalpr((long)v, p->rkern == &kdbpcb.pcb_pc ? ISYM : DSYM);
		kdbprintc(EOR);
E 17
	}
D 17
	printpc();
E 17
I 17
	kdbprintpc();
E 17
}

D 17
getreg(regnam)
E 17
I 17
kdbgetreg(regnam)
E 17
{
	register REGPTR	p;
	register char *regptr;
	char *olp;

D 4
	olp=lp;
	for (p=reglist; p->rname; p++) {
		regptr=p->rname;
E 4
I 4
D 17
	olp = lp;
	for (p = reglist; p->rname; p++) {
E 17
I 17
	olp = kdblp;
	for (p = kdbreglist; p->rname; p++) {
E 17
		regptr = p->rname;
E 4
		if (regnam == *regptr++) {
			while (*regptr)
D 17
				if (readchar() != *regptr++) {
E 17
I 17
				if (kdbreadchar() != *regptr++) {
E 17
					--regptr;
					break;
				}
			if (*regptr)
D 4
				lp=olp;
E 4
I 4
D 17
				lp = olp;
E 17
I 17
				kdblp = olp;
E 17
E 4
			else
D 4
				return((int)p->rkern);
E 4
I 4
				return ((int)p->rkern);
E 4
		}
	}
D 4
	lp=olp;
E 4
I 4
D 17
	lp = olp;
E 17
I 17
	kdblp = olp;
E 17
E 4
	return (-1);
}

D 17
printpc()
E 17
I 17
kdbprintpc()
E 17
{

D 5
	psymoff(pcb.pcb_pc, ISYM, ":%16t");
	printins(ISP, chkget(pcb.pcb_pc, ISP));
E 5
I 5
D 17
	psymoff((long)pcb.pcb_pc, ISYM, ":%16t");
	printins(ISP, (long)chkget((off_t)pcb.pcb_pc, ISP));
E 5
	printc(EOR);
E 17
I 17
	kdbpsymoff((long)kdbpcb.pcb_pc, ISYM, ":%16t");
	kdbprintins(ISP, (long)kdbchkget((off_t)kdbpcb.pcb_pc, ISP));
	kdbprintc(EOR);
E 17
}
E 1
