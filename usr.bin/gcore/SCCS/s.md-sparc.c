h11983
s 00002/00002/00158
d D 8.1 93/06/06 14:41:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00159
d D 5.4 93/05/15 22:23:37 torek 4 3
c <sys/kinfo_proc.h> information moved to <sys/sysctl.h>
e
s 00000/00001/00160
d D 5.3 93/03/31 17:27:38 mckusick 3 2
c convert from kinfo to sysctl
e
s 00038/00037/00123
d D 5.2 92/06/29 18:58:29 bostic 2 1
c quad fixes, but some general cleanup too
e
s 00160/00000/00000
d D 5.1 92/06/19 16:48:50 mccanne 1 0
c date and time created 92/06/19 16:48:50 by mccanne
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 Regents of the University of California.
E 2
I 2
D 5
 * Copyright (c) 1992 The Regents of the University of California.
E 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 */

D 2
#include <stdio.h>
#include <kvm.h>
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
#include <sys/param.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/proc.h>
#include <sys/user.h>
D 3
#include <sys/kinfo.h>
E 3
D 4
#include <sys/kinfo_proc.h>
E 4
I 4
#include <sys/sysctl.h>
E 4
#include <machine/vmparam.h>

I 2
#include <kvm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "extern.h"

E 2
#ifndef offsetof
#define	offsetof(s, f) ((int)&((s *)0)->f)
#endif

static void
shift_page(fd, off, ssize)
	register int fd;
	register off_t off;
	register int ssize;
{
	char buffer[NBPG];

D 2
	(void)lseek(fd, -NBPG, SEEK_END);
E 2
I 2
	(void)lseek(fd, (off_t)-NBPG, SEEK_END);
E 2
	for (; ssize > 0; ssize -= NBPG) {
D 2
		read(fd, buffer, NBPG);
		write(fd, buffer, NBPG);
		(void)lseek(fd, -2 * NBPG, SEEK_CUR);
E 2
I 2
		(void)read(fd, buffer, NBPG);
		(void)write(fd, buffer, NBPG);
		(void)lseek(fd, (off_t)-2 * NBPG, SEEK_CUR);
E 2
	}
}

/*
 * Fix up the core image for the sparc.  We need to flush any register
 * windows that are cached in the pcb out to the user stack.
 * Also, we need to get the trap frame and possible floating point state
 * from the top of the kernel stack and store it in the pcb.
 */
D 2
int
E 2
I 2
void
E 2
md_core(kd, fd, ki)
	kvm_t *kd;
	int fd;
	struct kinfo_proc *ki;
{
	register struct rwindow *rw;
	register int nsaved, cc, ssize;
	register off_t off, s;
	register u_long sp;
	struct pcb pcb;
	struct trapframe tf;

	/*
	 * Before anything else read the trapframe.  Synchronizing here
	 * is impossible if the process is running.
	 */
	cc = kvm_read(kd, (u_long)ki->kp_proc.p_md.md_tf,
		      /* XXX */
		      (void *)&tf, sizeof(tf));
	if (cc < 0)
D 2
		error("kvm_read: %s (reading kernel trapframe)",
E 2
I 2
		err(1, "kvm_read: %s (reading kernel trapframe)",
E 2
		      kvm_geterr(kd));
	if (cc != sizeof(tf))
D 2
		error("cannot read kernel trapframe");
E 2
I 2
		err(1, "cannot read kernel trapframe");
E 2

	/*
	 * Write out the real trap frame.
	 */
	off = offsetof(struct user, u_md);
	off += offsetof(struct md_coredump, md_tf);
D 2
	if (lseek(fd, off, SEEK_SET) == -1) {
		perror("lseek");
		exit(1);
	}
	(void)write(fd, (char *)&tf, sizeof(tf));
E 2
I 2
	if (lseek(fd, off, SEEK_SET) == -1)
		err(1, "lseek: %s", strerror(errno));
	(void)write(fd, &tf, sizeof(tf));
E 2

	if (ki->kp_proc.p_md.md_fpstate != 0) {
		/*
		 * If floating point state is present, write it out too.
		 * It comes right after the trapframe so we don't need to seek.
		 */
		struct fpstate fs;
		cc = kvm_read(kd, (u_long)ki->kp_proc.p_md.md_fpstate,
			      (void *)&fs, sizeof(fs));
		if (cc < 0)
D 2
			error("kvm_read: %s (fpu state)", kvm_geterr(kd));
E 2
I 2
			err(1, "kvm_read: %s (fpu state)", kvm_geterr(kd));
E 2
		if (cc != sizeof(fs))
D 2
			error("cannot read fpu state");
E 2
I 2
			err(1, "cannot read fpu state");
E 2
		(void)write(fd, (char *)&fs, sizeof(fs));
	}
	/*
	 * Read pcb.
	 */
D 2
	if (lseek(fd, offsetof(struct user, u_pcb), SEEK_SET) == -1) {
		perror("lseek");
		exit(1);
	}
E 2
I 2
	if (lseek(fd, (off_t)offsetof(struct user, u_pcb), SEEK_SET) == -1)
		err(1, "lseek: %s", strerror(errno));
E 2
	cc = read(fd, (char *)&pcb, sizeof(pcb));
D 2
	if (cc < 0) {
		perror("read");
		exit(1);
E 2
I 2
	if (cc != sizeof(pcb)) {
		if (cc < 0)
			err(1, "read: %s", strerror(errno));
		err(1, "couldn't read pcb from core file");
E 2
	}
D 2
	if (cc != sizeof(pcb))
		error("couldn't read pcb from core file");
E 2

	/*
	 * Write any unsaved windows to the appropriate stack locations.
	 */
	nsaved = pcb.pcb_nsaved;
	if (nsaved == 0)
D 2
		return (0);
E 2
I 2
		return;
E 2

	rw = &pcb.pcb_rw[0];
	off = ctob(UPAGES + ki->kp_eproc.e_vm.vm_dsize);
	ssize = ctob(ki->kp_eproc.e_vm.vm_ssize);
	sp = tf.tf_out[6];
	for (; --nsaved >= 0; ++rw) {
		/*
		 * Copy register window into appropriate stack location.
		 */
		s = ssize - (USRSTACK - sp);
		if (s < 0) {
			if (s < -NBPG)
D 2
				error("cannot copy pcb windows to stack");
E 2
I 2
				err(1, "cannot copy pcb windows to stack");
E 2
			/*
			 * It's possible to be missing the bottomost
			 * page because a stack page hasn't been allocated
			 * for the register save area.  Shift over
			 * the stack segment by a page, and update 
			 * the u-area to reflect the new stack size.  YECH!
			 */
			shift_page(fd, off, ssize);
			ssize += NBPG;
			s += NBPG;
			++ki->kp_eproc.e_vm.vm_ssize;
D 2
			(void)lseek(fd, offsetof(struct user,
						 u_kproc.kp_eproc.e_vm),
				    SEEK_SET);
			(void)write(fd, (char *)&ki->kp_eproc.e_vm, 
				    sizeof(ki->kp_eproc.e_vm));
E 2
I 2
			(void)lseek(fd,
			    (off_t)offsetof(struct user, u_kproc.kp_eproc.e_vm),
			    SEEK_SET);
			(void)write(fd,
			    &ki->kp_eproc.e_vm, sizeof(ki->kp_eproc.e_vm));
E 2
		}
		if (lseek(fd, off + s, SEEK_SET) == -1)
D 2
			error("cannot copy pcb windows to stack");
E 2
I 2
			err(1, "cannot copy pcb windows to stack");
E 2

D 2
		write(fd, (char *)rw, sizeof(*rw));
E 2
I 2
		(void)write(fd, rw, sizeof(*rw));
E 2
		sp = rw->rw_in[6];
	}
D 2
	return (0);
E 2
}
D 2

E 2
E 1
