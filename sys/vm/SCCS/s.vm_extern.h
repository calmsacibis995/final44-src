h12920
s 00002/00002/00097
d D 8.5 95/05/03 16:43:32 mckusick 9 8
c kinfo_* is gone; add vm_sysctl
e
s 00001/00001/00098
d D 8.4 95/02/19 07:47:21 cgd 8 7
c getpagesize -> compat_43_getpagesize
e
s 00005/00005/00094
d D 8.3 95/01/09 17:50:30 cgd 7 6
c KNF, and 64-bit safety.
e
s 00000/00005/00099
d D 8.2 94/01/12 15:51:32 hibler 6 5
c get rid of unused vm_move/vm_region routines.
e
s 00002/00002/00102
d D 8.1 93/06/11 16:37:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00101
d D 7.4 93/03/09 10:37:01 hibler 4 3
c prototype changes: new param for vm_mmap, return type for vm_fault_wire
e
s 00002/00000/00102
d D 7.3 92/05/12 15:55:59 bostic 3 2
c user programs get to this through vm.h
e
s 00001/00000/00101
d D 7.2 92/05/04 17:28:28 bostic 2 1
c quiet the warnings
e
s 00101/00000/00000
d D 7.1 92/05/04 17:19:52 bostic 1 0
c date and time created 92/05/04 17:19:52 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct buf;
struct loadavg;
struct proc;
struct vmspace;
struct vmtotal;
struct mount;
I 2
struct vnode;
E 2

#ifdef KGDB
void		 chgkprot __P((caddr_t, int, int));
#endif

I 3
#ifdef KERNEL
E 3
#ifdef TYPEDEF_FOR_UAP
D 8
int		 getpagesize __P((struct proc *p, void *, int *));
E 8
I 8
int		 compat_43_getpagesize __P((struct proc *p, void *, int *));
E 8
int		 madvise __P((struct proc *, void *, int *));
int		 mincore __P((struct proc *, void *, int *));
int		 mprotect __P((struct proc *, void *, int *));
int		 msync __P((struct proc *, void *, int *));
int		 munmap __P((struct proc *, void *, int *));
int		 obreak __P((struct proc *, void *, int *));
int		 sbrk __P((struct proc *, void *, int *));
int		 smmap __P((struct proc *, void *, int *));
int		 sstk __P((struct proc *, void *, int *));
#endif

D 7
void		 assert_wait __P((int, boolean_t));
int		 grow __P((struct proc *, u_int));
E 7
I 7
void		 assert_wait __P((void *, boolean_t));
int		 grow __P((struct proc *, vm_offset_t));
E 7
void		 iprintf __P((const char *, ...));
int		 kernacc __P((caddr_t, int, int));
D 9
int		 kinfo_loadavg __P((int, char *, int *, int, int *));
int		 kinfo_meter __P((int, caddr_t, int *, int, int *));
E 9
vm_offset_t	 kmem_alloc __P((vm_map_t, vm_size_t));
vm_offset_t	 kmem_alloc_pageable __P((vm_map_t, vm_size_t));
vm_offset_t	 kmem_alloc_wait __P((vm_map_t, vm_size_t));
void		 kmem_free __P((vm_map_t, vm_offset_t, vm_size_t));
void		 kmem_free_wakeup __P((vm_map_t, vm_offset_t, vm_size_t));
void		 kmem_init __P((vm_offset_t, vm_offset_t));
vm_offset_t	 kmem_malloc __P((vm_map_t, vm_size_t, boolean_t));
vm_map_t	 kmem_suballoc __P((vm_map_t, vm_offset_t *, vm_offset_t *,
		    vm_size_t, boolean_t));
void		 loadav __P((struct loadavg *));
D 7
void		 munmapfd __P((int));
E 7
I 7
void		 munmapfd __P((struct proc *, int));
E 7
int		 pager_cache __P((vm_object_t, boolean_t));
void		 sched __P((void));
int		 svm_allocate __P((struct proc *, void *, int *));
int		 svm_deallocate __P((struct proc *, void *, int *));
int		 svm_inherit __P((struct proc *, void *, int *));
int		 svm_protect __P((struct proc *, void *, int *));
void		 swapinit __P((void));
int		 swapon __P((struct proc *, void *, int *));
void		 swapout __P((struct proc *));
void		 swapout_threads __P((void));
int		 swfree __P((struct proc *, int));
void		 swstrategy __P((struct buf *));
void		 thread_block __P((void));
D 7
void		 thread_sleep __P((int, simple_lock_t, boolean_t));
void		 thread_wakeup __P((int));
E 7
I 7
void		 thread_sleep __P((void *, simple_lock_t, boolean_t));
void		 thread_wakeup __P((void *));
E 7
int		 useracc __P((caddr_t, int, int));
int		 vm_allocate __P((vm_map_t,
		    vm_offset_t *, vm_size_t, boolean_t));
int		 vm_allocate_with_pager __P((vm_map_t, vm_offset_t *,
		    vm_size_t, boolean_t, vm_pager_t, vm_offset_t, boolean_t));
int		 vm_deallocate __P((vm_map_t, vm_offset_t, vm_size_t));
int		 vm_fault __P((vm_map_t, vm_offset_t, vm_prot_t, boolean_t));
void		 vm_fault_copy_entry __P((vm_map_t,
		    vm_map_t, vm_map_entry_t, vm_map_entry_t));
void		 vm_fault_unwire __P((vm_map_t, vm_offset_t, vm_offset_t));
D 4
void		 vm_fault_wire __P((vm_map_t, vm_offset_t, vm_offset_t));
E 4
I 4
int		 vm_fault_wire __P((vm_map_t, vm_offset_t, vm_offset_t));
E 4
int		 vm_fork __P((struct proc *, struct proc *, int));
int		 vm_inherit __P((vm_map_t,
		    vm_offset_t, vm_size_t, vm_inherit_t));
void		 vm_init_limits __P((struct proc *));
void		 vm_mem_init __P((void));
D 4
int		 vm_mmap __P((vm_map_t, vm_offset_t *,
		    vm_size_t, vm_prot_t, int, caddr_t, vm_offset_t));
E 4
I 4
int		 vm_mmap __P((vm_map_t, vm_offset_t *, vm_size_t,
		    vm_prot_t, vm_prot_t, int, caddr_t, vm_offset_t));
E 4
D 6
vm_offset_t	 vm_move __P((vm_map_t,
		    vm_offset_t, vm_map_t, vm_offset_t, boolean_t));
E 6
int		 vm_protect __P((vm_map_t,
		    vm_offset_t, vm_size_t, boolean_t, vm_prot_t));
D 6
int		 vm_region __P((vm_map_t, vm_offset_t *, vm_size_t *,
		    vm_prot_t *, vm_prot_t *, vm_inherit_t *, boolean_t *,
		    vm_object_t *, vm_offset_t *));
E 6
void		 vm_set_page_size __P((void));
I 9
int		 vm_sysctl __P((int *, u_int, void *, size_t *, void *,
		    size_t, struct proc *));
E 9
void		 vmmeter __P((void));
struct vmspace	*vmspace_alloc __P((vm_offset_t, vm_offset_t, int));
struct vmspace	*vmspace_fork __P((struct vmspace *));
void		 vmspace_free __P((struct vmspace *));
void		 vmtotal __P((struct vmtotal *));
void		 vnode_pager_setsize __P((struct vnode *, u_long));
void		 vnode_pager_umount __P((struct mount *));
boolean_t	 vnode_pager_uncache __P((struct vnode *));
void		 vslock __P((caddr_t, u_int));
void		 vsunlock __P((caddr_t, u_int, int));
I 3
#endif
E 3
E 1
