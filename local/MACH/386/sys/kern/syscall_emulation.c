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
 * $Log:	syscall_emulation.c,v $
 * Revision 2.4  89/02/25  18:08:42  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/15  16:26:59  rpd
 * 	Updated includes for the new mach/ directory.
 * 	[89/01/15  15:06:37  rpd]
 * 
 * Revision 2.2  88/12/19  02:47:04  mwyoung
 * 	Fix include file references.
 * 	[88/12/19  00:12:23  mwyoung]
 * 	
 * 	Removed lint.
 * 	[88/12/09            mwyoung]
 * 
 */

#include <mach_emulation.h>

#include <mach/mach_types.h>
#include <kern/syscall_emulation.h>

#if	MACH_EMULATION
#include <mach/error.h>
#include <kern/task.h>
#include <kern/zalloc.h>
#include <mach/vm_param.h>

zone_t		eml_zone;
int		eml_max_emulate_count;
/*
 *  eml_init:	initialize user space emulation code
 */
eml_init()
{
	extern int nsysent;
	
	eml_max_emulate_count = nsysent;

	eml_zone = zinit( sizeof(struct eml_dispatch)+((eml_max_emulate_count-1) * sizeof (eml_routine_t)),
		 PAGE_SIZE, PAGE_SIZE, FALSE, "emulation routines" );
		 
}

/*
 *   task_set_emulation:  [Server Entry]
 *   set up for user space emulation of syscalls within this task.
 */
kern_return_t task_set_emulation( task, routine_entry_pt, routine_number)
	task_t		task;
	eml_routine_t 	routine_entry_pt;
	int		routine_number;
{
    	int i;
    
	if ( task == TASK_NULL )
	        return( EML_BAD_TASK );

	if ( routine_number >= eml_max_emulate_count
	     || routine_number < 0 )
		return( EML_BAD_CNT );
/*
 * If either the task does not have an emulation vector, or if
 * it points to a common one, then give it a new one.
 */
	if (task->eml_dispatch != EML_DISPATCH_NULL) {
		/* XXX lock the old dispatch structure */
	}

	if ((task->eml_dispatch == EML_DISPATCH_NULL)
	     || (task->eml_dispatch->eml_ref > 1)) {
	        eml_dispatch_t old_vec = task->eml_dispatch;

		task->eml_dispatch = (eml_dispatch_t)zalloc( eml_zone );
		task->eml_dispatch->eml_ref = 1;
		task->eml_dispatch->disp_count = eml_max_emulate_count;
		/* XXX lock the new dispatch structure */

		if( old_vec == EML_DISPATCH_NULL ) {
			/*  zero the vector */
			for ( i = 0; i < task->eml_dispatch->disp_count; i++)
				task->eml_dispatch->disp_vector[i] = EML_ROUTINE_NULL;
		} else {
			old_vec->eml_ref--;

			/*  copy the parent's vector */
			for ( i = 0; i < task->eml_dispatch->disp_count; i++)
				task->eml_dispatch->disp_vector[i] = old_vec->disp_vector[i];
	     	}
	}

	task->eml_dispatch->disp_vector[routine_number] = routine_entry_pt;

	/* XXX unlock the dispatch structure */

	return( KERN_SUCCESS );
}

/*
 * eml_task_fork() [Exported]
 *
 *	Bumps the reference count on the common emulation
 *	vector.
 */

kern_return_t eml_task_fork(parent,child)
task_t parent,child;
{
	if( parent->eml_dispatch != EML_DISPATCH_NULL ) {
		/* XXX lock the dispatch structure */
		parent->eml_dispatch->eml_ref++;
	}

	child->eml_dispatch = parent->eml_dispatch;
	return(KERN_SUCCESS);    
}


/*
 * eml_task_exit() [Exported]
 *
 *	Cleans up after the emulation code when a process exits.
 */
 
kern_return_t eml_task_exit(task)
task_t task;
{
	if (task->eml_dispatch != EML_DISPATCH_NULL) {
		/* XXX lock the dispatch structure */
		if (--task->eml_dispatch->eml_ref == 0 ) 
			zfree(eml_zone,task->eml_dispatch);
		return(KERN_SUCCESS);
	}

    return(KERN_FAILURE);
}
#else

/*
 *   task_set_emulation:  [Server Entry]
 *   set up for user space emulation of syscalls within this task.
 */
kern_return_t task_set_emulation( task, routine_entry_pt, routine_number)
	task_t		task;
	eml_routine_t 	routine_entry_pt;
	int		routine_number;
{
	return( KERN_FAILURE );
}
#endif	MACH_EMULATION
