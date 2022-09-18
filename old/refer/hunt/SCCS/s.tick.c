h40369
s 00005/00001/00038
d D 4.4 91/04/18 16:39:05 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00003/00036
d D 4.3 89/05/11 10:05:03 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00004/00000/00035
d D 4.2 83/08/11 21:04:49 sam 2 1
c standardize sccs keyword lines
e
s 00035/00000/00000
d D 4.1 83/06/22 13:12:52 garrison 1 0
c date and time created 83/06/22 13:12:52 by garrison
e
u
U
t
T
I 4
/*-
 * %sccs.include.proprietary.c%
 */

E 4
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

E 2
I 1
/* time programs */
D 3
# include "stdio.h"
# include "sys/types.h"
# include "sys/timeb.h"
E 3
I 3
# include <stdio.h>
# include <sys/types.h>
# include <sys/timeb.h>
E 3
struct tbuffer {
	long	proc_user_time;
	long	proc_system_time;
	long	child_user_time;
	long	child_system_time;
};
static long start, user, system;
tick()
{
	struct tbuffer tx;
	struct timeb tp;
	times (&tx);
	ftime (&tp);
	user =  tx.proc_user_time;
	system= tx.proc_system_time;
	start = tp.time*1000+tp.millitm;
}
tock()
{
	struct tbuffer tx;
	struct timeb tp;
	float lap, use, sys;
	if (start==0) return;
	times (&tx);
	ftime (&tp);
	lap = (tp.time*1000+tp.millitm-start)/1000.;
	use = (tx.proc_user_time - user)/60.;
	sys = (tx.proc_system_time - system)/60.;
	printf("Elapsed %.2f CPU %.2f (user %.2f, sys %.2f)\n",
		lap, use+sys, use, sys);
}
E 1
