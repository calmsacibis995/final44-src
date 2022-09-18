/* 
 * Mach Operating System
 * Copyright (c) 1994,1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	sched_policy_config.c,v $
 * Revision 2.3  94/12/16  10:51:23  dbg
 * 	Give the background and timesharing policies the same rank, since
 * 	they share the same set of run queues.
 * 	[94/07/14            dbg]
 * 
 * Revision 2.2  93/11/17  17:21:49  dbg
 * 	Conditionalized on MACH_RT.
 * 	[93/05/17            dbg]
 * 
 * 	Created.
 * 	[93/04/02            dbg]
 * 
 */

#include <mach_rt.h>

/*
 *	List of scheduling policies.
 *
 *	The list is kept as an array - scheduling policies are
 *	not (yet) added or removed while the system is running.
 *
 *	Rank is determined by the position in the array.  The
 *	higher-indexed policies have higher rank.
 */

#include <kern/sched_policy.h>

extern struct sched_policy	bg_sched_policy,
				ts_sched_policy,
				fp_sched_policy;
#if	MACH_RT
extern struct sched_policy	dm_sched_policy,
				rm_sched_policy,
				edf_sched_policy;
#endif

sched_policy_t	sched_policy_array[] = {
	&bg_sched_policy,
	&ts_sched_policy,
	&fp_sched_policy,
#if	MACH_RT
	&rm_sched_policy,
	&dm_sched_policy,
	&edf_sched_policy
#endif
};

int	sched_policy_count = sizeof(sched_policy_array)
				/ sizeof(sched_policy_array[0]);

void
sched_policy_init(void)
{
	/*
	 *	Run down the list, assigning rank.
	 *	We make an exception for the background
	 *	policy, since it uses the same run
	 *	queues as the timesharing policy.	XXX
	 */
	int	i;

	sched_policy_array[0]->rank = 0;	/* background */
	for (i = 1; i < sched_policy_count; i++)
	    sched_policy_array[i]->rank = i-1;
}

/*
 *	Lookup a scheduling policy by name.
 */
sched_policy_t
sched_policy_lookup(
	int	policy)
{
	int	i;

	for (i = 0; i < sched_policy_count; i++)
	    if (sched_policy_array[i]->name == policy)
		return sched_policy_array[i];

	return 0;
}

