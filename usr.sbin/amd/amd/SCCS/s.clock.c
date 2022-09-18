h25617
s 00002/00002/00213
d D 8.1 93/06/06 11:39:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00214
d D 5.4 92/02/09 08:48:01 pendry 4 3
c merge in new release
e
s 00003/00002/00212
d D 5.3 91/05/12 15:55:06 pendry 3 2
c checkpoint for network tape
e
s 00032/00005/00182
d D 5.2 91/03/17 13:32:56 pendry 2 1
c from amd5.3 alpha11
e
s 00187/00000/00000
d D 5.1 90/06/29 12:01:01 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: clock.c,v 5.2 90/06/23 22:19:21 jsp Rel $
E 2
I 2
D 3
 * $Id: clock.c,v 5.2.1.4 91/03/03 20:41:36 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
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
 * $Id: clock.c,v 5.2.1.5 91/05/07 22:17:49 jsp Alpha $
E 4
I 4
 * $Id: clock.c,v 5.2.2.1 1992/02/09 15:08:20 jsp beta $
E 4
 *
E 3
 */

/*
 * Callouts.
 *
 * Modelled on kernel object of the same name.
 * See usual references.
 *
 * Use of a heap-based mechanism was rejected:
D 2
 * 1.  more complext implementation needed.
 * 2.  not obvious that a list is too slow for amd.
E 2
I 2
 * 1.  more complex implementation needed.
 * 2.  not obvious that a list is too slow for Amd.
E 2
 */

#include "am.h"

typedef struct callout callout;
struct callout {
	callout	*c_next;		/* List of callouts */
	void	(*c_fn)();		/* Function to call */
	voidp	c_closure;		/* Closure to pass to call */
	time_t	c_time;			/* Time of call */
	int	c_id;			/* Unique identifier */
};

static callout callouts;		/* List of pending callouts */
static callout *free_callouts;		/* Cache of free callouts */
static int nfree_callouts;		/* Number on free list */
static int callout_id;			/* Next free callout identifier */
time_t next_softclock;			/* Time of next call to softclock() */

/*
 * Number of callout slots we keep on the free list
 */
#define	CALLOUT_FREE_SLOP	10

/*
D 2
 * Assumption: valid id's are non-zero.
E 2
I 2
 * Global assumption: valid id's are non-zero.
E 2
 */
#define	CID_ALLOC()	(++callout_id)
#define	CID_UNDEF	(0)

I 2
static callout *alloc_callout(P_void);
E 2
static callout *alloc_callout()
{
	callout *cp = free_callouts;
	if (cp) {
		--nfree_callouts;
		free_callouts = free_callouts->c_next;
		return cp;
	}
	return ALLOC(callout);
}

I 2
static void free_callout P((callout *cp));
E 2
static void free_callout(cp)
callout *cp;
{
	if (nfree_callouts > CALLOUT_FREE_SLOP) {
		free((voidp) cp);
	} else {
		cp->c_next = free_callouts;
		free_callouts = cp;
		nfree_callouts++;
	}
}

/*
 * Schedule a callout.
 *
 * (*fn)(closure) will be called at clocktime() + secs
 */
I 2
int timeout P((unsigned int secs, void (*fn)(), voidp closure));
E 2
int timeout(secs, fn, closure)
unsigned int secs;
void (*fn)();
voidp closure;
{
	callout *cp, *cp2;
	time_t t = clocktime() + secs;

	/*
	 * Allocate and fill in a new callout structure
	 */
	callout *cpnew = alloc_callout();
	cpnew->c_closure = closure;
	cpnew->c_fn = fn;
	cpnew->c_time = t;
	cpnew->c_id = CID_ALLOC();

	if (t < next_softclock)
		next_softclock = t;

	/*
	 * Find the correct place in the list
	 */
	for (cp = &callouts; cp2 = cp->c_next; cp = cp2)
		if (cp2->c_time >= t)
			break;

	/*
	 * And link it in
	 */
	cp->c_next = cpnew;
	cpnew->c_next = cp2;

	/*
	 * Return callout identifier
	 */
	return cpnew->c_id;
}

/*
 * De-schedule a callout
 */
I 2
void untimeout P((int id));
E 2
void untimeout(id)
int id;
{
	callout *cp, *cp2;
	for (cp = &callouts; cp2 = cp->c_next; cp = cp2) {
		if (cp2->c_id == id) {
			cp->c_next = cp2->c_next;
			free_callout(cp2);
			break;
		}
	}
}

/*
I 2
 * Reschedule after clock changed
 */
void reschedule_timeouts P((time_t now, time_t then));
void reschedule_timeouts(now, then)
time_t now;
time_t then;
{
	callout *cp;

	for (cp = callouts.c_next; cp; cp = cp->c_next) {
		if (cp->c_time >= now && cp->c_time <= then) {
			plog(XLOG_WARNING, "job %d rescheduled to run immediately", cp->c_id);
#ifdef DEBUG
			dlog("rescheduling job %d back %d seconds",
				cp->c_id, cp->c_time - now);
#endif
			next_softclock = cp->c_time = now;
		}
	}
}

/*
E 2
 * Clock handler
 */
I 2
int softclock(P_void);
E 2
int softclock()
{
	time_t now;
	callout *cp;

	do {
		if (task_notify_todo)
D 2
			task_notify();
E 2
I 2
			do_task_notify();
E 2

		now = clocktime();

		/*
		 * While there are more callouts waiting...
		 */
		while ((cp = callouts.c_next) && cp->c_time <= now) {
			/*
			 * Extract first from list, save fn & closure and
			 * unlink callout from list and free.
			 * Finally call function.
			 *
			 * The free is done first because
			 * it is quite common that the
			 * function will call timeout()
			 * and try to allocate a callout
			 */
			void (*fn)() = cp->c_fn;
			voidp closure = cp->c_closure;

			callouts.c_next = cp->c_next;
			free_callout(cp);
#ifdef DEBUG
			/*dlog("Calling %#x(%#x)", fn, closure);*/
#endif /* DEBUG */
			(*fn)(closure);
		}

	} while (task_notify_todo);

	/*
	 * Return number of seconds to next event,
	 * or 0 if there is no event.
	 */
	if (cp = callouts.c_next)
		return cp->c_time - now;
	return 0;
}
E 1
