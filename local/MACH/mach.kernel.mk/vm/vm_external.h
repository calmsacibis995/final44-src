/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vm_external.h,v $
 * Revision 2.5  89/10/19  13:16:44  af
 * 	Remember bitmap size, for safer deallocation.
 * 	[89/10/16  15:32:58  af]
 * 
 * Revision 2.4  89/10/10  11:06:26  mwyoung
 * 	Declare vm_external_destroy().
 * 	[89/08/08            mwyoung]
 * 
 * Revision 2.3  89/04/18  21:24:53  mwyoung
 * 	Created.
 * 	[89/04/18            mwyoung]
 * 
 */

#ifndef	_VM_VM_EXTERNAL_H_
#define _VM_VM_EXTERNAL_H_

/*
 *	External page management hint technology
 *
 *	The data structure exported by this module maintains
 *	a (potentially incomplete) map of the pages written
 *	to external storage for a range of virtual memory.
 */

/*
 *	The data structure representing the state of pages
 *	on external storage.
 */

typedef struct vm_external {
    	int		existence_size;	/* Size of the following bitmap */
	char		*existence_map;	/* A bitmap of pages that have
					 * been written to backing
					 * storage.
					 */
	int		existence_count;/* Number of bits turned on in
					 * existence_map.
					 */
} *vm_external_t;

#define	VM_EXTERNAL_NULL	((vm_external_t) 0)

/*
 *	The states that may be recorded for a page of external storage.
 */

typedef int	vm_external_state_t;
#define	VM_EXTERNAL_STATE_EXISTS		1
#define	VM_EXTERNAL_STATE_UNKNOWN		2
#define	VM_EXTERNAL_STATE_ABSENT		3


/*
 *	Routines exported by this module.
 */

extern void		vm_external_module_initialize();
						/* Initialize the module */

extern vm_external_t	vm_external_create();	/* Create a vm_external_t */
extern void vm_external_destroy();		/* Destroy one */

extern void		vm_external_state_set();/* Set state of a page. */
#define	vm_external_state_get(e,offset)	(((e) != VM_EXTERNAL_NULL) ? \
					  _vm_external_state_get(e, offset) :	\
					  VM_EXTERNAL_STATE_UNKNOWN)
						/* Retrieve the state
						 * for a given page, if known.
						 */
extern vm_external_state_t _vm_external_state_get();
						/* HIDDEN routine */

#endif	_VM_VM_EXTERNAL_H_
