h21533
s 00002/00002/00297
d D 8.1 93/06/06 11:41:15 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00049/00001/00250
d D 5.4 92/02/09 08:48:59 pendry 4 3
c merge in new release
e
s 00021/00009/00230
d D 5.3 91/05/12 15:56:07 pendry 3 2
c checkpoint for network tape
e
s 00005/00005/00234
d D 5.2 91/03/17 13:33:59 pendry 2 1
c from amd5.3 alpha11
e
s 00239/00000/00000
d D 5.1 90/06/29 12:01:18 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: sched.c,v 5.2 90/06/23 22:19:58 jsp Rel $
E 2
I 2
D 3
 * $Id: sched.c,v 5.2.1.3 91/03/17 17:42:03 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: sched.c,v 5.2.1.5 91/05/07 22:18:32 jsp Alpha $
E 4
I 4
 * $Id: sched.c,v 5.2.2.1 1992/02/09 15:09:02 jsp beta $
E 4
 *
E 3
 */

/*
 * Process scheduler
 */

#include "am.h"
#include <sys/signal.h>
#include WAIT
#include <setjmp.h>
extern jmp_buf select_intr;
extern int select_intr_valid;

typedef struct pjob pjob;
struct pjob {
	qelem hdr;			/* Linked list */
	int pid;			/* Process ID of job */
	cb_fun cb_fun;			/* Callback function */
	voidp cb_closure;		/* Closure for callback */
	union wait w;			/* Status filled in by sigchld */
	voidp wchan;			/* Wait channel */
};

extern qelem proc_list_head;
qelem proc_list_head = { &proc_list_head, &proc_list_head };
extern qelem proc_wait_list;
qelem proc_wait_list = { &proc_wait_list, &proc_wait_list };

int task_notify_todo;

void ins_que(elem, pred)
qelem *elem, *pred;
{
	qelem *p = pred->q_forw;
	elem->q_back = pred;
	elem->q_forw = p;
	pred->q_forw = elem;
	p->q_back = elem;
}

void rem_que(elem)
qelem *elem;
{
	qelem *p = elem->q_forw;
	qelem *p2 = elem->q_back;
	p2->q_forw = p;
	p->q_back = p2;
}

static pjob *sched_job(cf, ca)
cb_fun cf;
voidp ca;
{
	pjob *p = ALLOC(pjob);

	p->cb_fun = cf;
	p->cb_closure = ca;

	/*
	 * Now place on wait queue
	 */
	ins_que(&p->hdr, &proc_wait_list);

	return p;
}

void run_task(tf, ta, cf, ca)
task_fun tf;
voidp ta;
cb_fun cf;
voidp ca;
{
	pjob *p = sched_job(cf, ca);
	int mask;

	p->wchan = (voidp) p;

	mask = sigblock(sigmask(SIGCHLD));

	if (p->pid = background()) {
		sigsetmask(mask);
		return;
	}

	exit((*tf)(ta));
	/* firewall... */
	abort();
}

/*
 * Schedule a task to be run when woken up
 */
void sched_task(cf, ca, wchan)
cb_fun cf;
voidp ca;
voidp wchan;
{
	/*
	 * Allocate a new task
	 */
	pjob *p = sched_job(cf, ca);
D 3
#ifdef DEBUG
	/*dlog("sleep(%#x)", wchan);*/
#endif /* DEBUG */
E 3
I 3
#ifdef DEBUG_SLEEP
	dlog("SLEEP on %#x", wchan);
#endif
E 3
	p->wchan = wchan;
	p->pid = 0;
	bzero((voidp) &p->w, sizeof(p->w));
}

static void wakeupjob(p)
pjob *p;
{
	rem_que(&p->hdr);
	ins_que(&p->hdr, &proc_list_head);
	task_notify_todo++;
}

void wakeup(wchan)
voidp wchan;
{
	pjob *p, *p2;
D 3

E 3
I 3
#ifdef DEBUG_SLEEP
	int done = 0;
#endif
E 3
	if (!foreground)
		return;

D 3
#ifdef DEBUG
E 3
I 3
#ifdef DEBUG_SLEEP
E 3
	/*dlog("wakeup(%#x)", wchan);*/
D 3
#endif /* DEBUG */
E 3
I 3
#endif
E 3
	/*
	 * Can't user ITER() here because
	 * wakeupjob() juggles the list.
	 */
	for (p = FIRST(pjob, &proc_wait_list);
			p2 = NEXT(pjob, p), p != HEAD(pjob, &proc_wait_list);
			p = p2) {
D 3
		if (p->wchan == wchan)
E 3
I 3
		if (p->wchan == wchan) {
#ifdef DEBUG_SLEEP
			done = 1;
#endif
E 3
			wakeupjob(p);
I 3
		}
E 3
	}
I 3

#ifdef DEBUG_SLEEP
	if (!done)
		dlog("Nothing SLEEPing on %#x", wchan);
#endif
E 3
}

void wakeup_task(rc, term, cl)
int rc;
int term;
voidp cl;
{
	wakeup(cl);
}

/*ARGSUSED*/

void sigchld(sig)
int sig;
{
	union wait w;
	int pid;

#ifdef SYS5_SIGNALS
	if ((pid = wait(&w)) > 0) {
#else
D 2
	while ((pid = wait3(&w, WNOHANG, (union wait *) 0)) > 0) {
E 2
I 2
	while ((pid = wait3((int *) &w, WNOHANG, (struct rusage *) 0)) > 0) {
E 2
#endif /* SYS5_SIGNALS */
		pjob *p, *p2;

		if (WIFSIGNALED(w))
			plog(XLOG_ERROR, "Process %d exited with signal %d",
				pid, w.w_termsig);
#ifdef DEBUG
		else
			dlog("Process %d exited with status %d",
				pid, w.w_retcode);
#endif /* DEBUG */

		for (p = FIRST(pjob, &proc_wait_list);
				p2 = NEXT(pjob, p), p != HEAD(pjob, &proc_wait_list);
				p = p2) {
			if (p->pid == pid) {
				p->w = w;
				wakeupjob(p);
				break;
			}
		}

#ifdef DEBUG
		if (p) ; else dlog("can't locate task block for pid %d", pid);
#endif /* DEBUG */
	}

#ifdef SYS5_SIGNALS
	signal(sig, sigchld);
#endif /* SYS5_SIGNALS */
	if (select_intr_valid)
D 2
		longjmp(select_intr, sigchld);
E 2
I 2
		longjmp(select_intr, sig);
E 2
}

/*
 * Run any pending tasks.
 * This must be called with SIGCHLD disabled
 */
D 2
void task_notify(P_void)
E 2
I 2
void do_task_notify(P_void)
E 2
{
	/*
	 * Keep taking the first item off the list and processing it.
	 *
	 * Done this way because the the callback can, quite reasonably,
	 * queue a new task, so no local reference into the list can be
	 * held here.
	 */
	while (FIRST(pjob, &proc_list_head) != HEAD(pjob, &proc_list_head)) {
		pjob *p = FIRST(pjob, &proc_list_head);
		rem_que(&p->hdr);
		/*
		 * This job has completed
		 */
		--task_notify_todo;

		/*
		 * Do callback if it exists
		 */
		if (p->cb_fun)
			(*p->cb_fun)(p->w.w_retcode,
				p->w.w_termsig, p->cb_closure);

D 2
		free(p);
E 2
I 2
		free((voidp) p);
E 2
	}
}
I 4

#ifdef HAS_SVR3_SIGNALS
/*
 * 4.2 signal library based on svr3 (4.1+ bsd) interface
 * From Stephen C. Pope <scp@acl.lanl.gov).
 */

static int current_mask = 0;

int sigblock(mask)
int mask;
{
    int sig;
    int m;
    int oldmask;

    oldmask = current_mask;
    for ( sig = 1, m = 1; sig <= MAXSIG; sig++, m <<= 1 ) {
        if (mask & m)  {
	    sighold(sig);
            current_mask |= m;
        }
    }
    return oldmask;
}

int sigsetmask(mask)
int mask;
{
    int sig;
    int m;
    int oldmask;

    oldmask = current_mask;
    for ( sig = 1, m = 1; sig <= MAXSIG; sig++, m <<= 1 ) {
        if (mask & m)  {
            sighold(sig);
            current_mask |= m;
        }
        else  {
            sigrelse(sig);
            current_mask &= ~m;
        }
    }
    return oldmask;
}

#endif /* HAS_SVR3_SIGNALS */
E 4
E 1
