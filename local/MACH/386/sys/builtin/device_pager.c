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
 * $Log:	device_pager.c,v $
 * Revision 2.19  89/05/31  12:27:29  rvb
 * 	Stylistic change. [af]
 * 
 * Revision 2.18  89/05/01  15:21:34  rpd
 * 	Don't initialize task->reply_port here.
 * 	[89/05/01  13:46:52  rpd]
 * 
 * Revision 2.17  89/04/18  16:42:23  mwyoung
 * 	Handle memory_object_data_write() calls, and document why
 * 	it's necessary to do so.
 * 	[89/04/07            mwyoung]
 * 
 * Revision 2.16  89/04/05  12:56:09  rvb
 * 	Forward declaration of device_pager_server() as boolean_t.
 * 	[89/03/21            rvb]
 *
 * Revision 2.10  89/01/10  23:33:09  rpd
 * 	Eliminated use of xxx_port_allocate, xxx_port_enable.
 * 	[89/01/10  13:35:38  rpd]
 * 	
 * 	Use object_copyin/object_copyout instead of port_copyin/port_copyout.
 * 	[89/01/09  14:49:04  rpd]
 *
 *  8-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	vm/device_pager.c
 *
 *	Provide paging objects for memory-mapped devices.
 */
#include <mach/memory_object.h>
#include <mach/port.h>
#include <mach/machine/vm_types.h>
#include <mach/vm_param.h>
#include <vm/vm_page.h>
#include <vm/vm_object.h>
#include <kern/lock.h>
#include <kern/zalloc.h>
#include <kern/task.h>
#include <vm/vm_kern.h>
#include <kern/kern_obj.h>
#include <kern/kern_port.h>
#include <kern/ipc_copyin.h>
#include <kern/ipc_copyout.h>

	/*
	 *	Forward Declarations.
	 */

boolean_t	device_pager_server();

/* Something above pulls in sys/types.h... I'm morally
 * opposed to bringing it in merely to get dev_t.
 */

/*
 *	Type:		dev_pager_t
 *	Synopsis:	Descriptor for a device paging object.
 *
 *	Implementation:
 *		One device_pager record is kept for each active
 *		device paging object; all such records are kept
 *		in a singly-linked list.
 */
typedef struct dev_pager {
	struct dev_pager *next;		/* Next in list */
	memory_object_t	pager;		/* Paging port */
	memory_object_control_t
			pager_request;	/* Pager request port */

	/*
	 *	Arguments passed to device_pager_create to be
	 *	use to do the mapping.
	 */

	dev_t		dev;
	int		(*mapfun)();
	int		prot;
	vm_offset_t	offset;
	vm_size_t	size;

	/*
	 *	State associated with this object
	 */

	struct vm_page	*pages;		/* Page structures allocated */
	vm_size_t	pages_size;	/* ... amount thereof */
} *dev_pager_t;

#define		DEV_PAGER_NULL	((dev_pager_t) 0)

decl_simple_lock_data(,device_pager_lock)
dev_pager_t	device_pager_list = DEV_PAGER_NULL;
zone_t		device_pager_zone;

/*
 *	Other state variables
 */

task_t		device_pager_task;
port_name_t	device_pager_self;
port_set_name_t	device_pager_enabled_set;

/*
 *	Routine:	device_pager_init
 *	Function:
 *		Initialize the device pager data structures.
 *	Arguments:
 *		The single argument names the task that
 *		has been created to run the device_pager.
 *	Note:
 *		This call does not operate in the context of
 *		the device_pager task.
 *	In/out conditions:
 *		This routine must be called before any threads
 *		in the device_pager task are started.
 */
void		device_pager_init(task)
	task_t		task;
{
	kern_port_t	port;

	/*
	 *	Initialize device_pager_task.
	 */

	device_pager_task = task;

	/*
	 *	Initialize device_pager_self.
	 *	This simulates a task_self(), which we can't use
	 *	because we're not running in the device_pager.
	 */

	ipc_task_lock(device_pager_task);
	port = (kern_port_t) device_pager_task->task_self;
	assert(port != KERN_PORT_NULL);
	port_reference(port);
	ipc_task_unlock(device_pager_task);

	object_copyout(device_pager_task, (kern_obj_t) port,
		       MSG_TYPE_PORT, &device_pager_self);

	/*
	 *	Initialize device_pager_enabled_set.
	 */

	if (port_set_allocate(device_pager_task, &device_pager_enabled_set)
				!= KERN_SUCCESS)
		panic("device_pager_init: device_pager_enabled_set");

	/*
	 *	Initialize device_pager_zone, device_pager_list,
	 *	and device_pager_lock.
	 */

	device_pager_zone = zinit(sizeof(struct dev_pager),
				100 * sizeof(struct dev_pager),
				sizeof(struct dev_pager),
				FALSE,
				"device pager structures");
	device_pager_list = DEV_PAGER_NULL;
	simple_lock_init(&device_pager_lock);
}

/*
 *	Routine:	device_pager_create
 *	Function:
 *		Returns a pager which can be vm_allocate_with_pager'd
 *		to map the specified device.
 *
 *	In/out conditions:
 *		Returns a reference to the port in question.
 *
 *	Implementation:
 *		Create a pager and record the arguments for
 *		later use.  The pager_init() handler does all of the
 *		real work.
 *	Note:
 *		This routine does not run in the context of the
 *		device_pager task.
 */
memory_object_t	device_pager_create(dev, mapfun, prot, offset, size)
	dev_t		dev;
	int		(*mapfun)();
	int		prot;
	vm_offset_t	offset;
	vm_size_t	size;
{
	dev_pager_t	d;
	memory_object_t	result;
	port_name_t	pager;

	/*
	 *	Allocate a structure to hold the arguments
	 *	and port to represent this object.
	 */

	d = (dev_pager_t) zalloc(device_pager_zone);

	if (port_allocate(device_pager_task, &pager) != KERN_SUCCESS)
		return(PORT_NULL);
	if (port_set_add(device_pager_task, device_pager_enabled_set, pager) != KERN_SUCCESS)
		panic("device_pager_create: can't enable");

	(void) object_copyin(device_pager_task, pager,
			     MSG_TYPE_PORT, FALSE,
			     (kern_obj_t *) &result);

	/*
	 *	Insert the descriptor into the list
	 */

	simple_lock(&device_pager_lock);
	d->next = device_pager_list;
	device_pager_list = d;
	d->pager = pager;
	simple_unlock(&device_pager_lock);


	/*
	 *	Record our arguments
	 */

	d->dev = dev;
	d->mapfun = mapfun;
	d->prot = prot;
	d->offset = offset;
	d->size = size;
	d->pager_request = PORT_NULL;

	return(result);
}

/*
 *	IMPORTANT NOTE:
 *		The pager interface functions are implemented below
 *		for the device pager.
 *
 *		Note that the routine names have all been changed to
 *		avoid confusion with the versions *used* by the kernel.
 *
 *		The only function of real importance to the device
 *		pager is initialization.  Data requests can occur, but
 *		are ignored, as initialization will provide the entire
 *		range of valid data.  Other interface functions should
 *		never be exercised; they're declared here for completeness
 *		(i.e., to make "lint" happy).
 */

#include <mach/mach_user_internal.h>

#define		memory_object_init		device_pager_init_pager
#define		memory_object_terminate		device_pager_terminate
#define		memory_object_data_request	device_pager_data_request
#define		memory_object_data_unlock	device_pager_data_unlock
#define		memory_object_data_write	device_pager_data_write
#define		memory_object_lock_completed	device_pager_lock_completed

kern_return_t memory_object_data_request(memory_object,memory_control_port,offset,length,desired_access)
	memory_object_t memory_object;
	memory_object_control_t memory_control_port;
	vm_offset_t offset;
	vm_size_t length;
	vm_prot_t desired_access;
{
#if	defined(lint) || defined(hc)
	memory_object++; memory_control_port++; offset++; length++; desired_access++;
#endif	defined(lint) || defined(hc)

	/*
	 *	It's quite possible that a page fault occurs before
	 *	initialization is handled.  We merely throw away any
	 *	pending pageins.
	 */

	return(KERN_SUCCESS);
}

kern_return_t memory_object_data_unlock(memory_object,memory_control_port,offset,length,desired_access)
	memory_object_t memory_object;
	memory_object_control_t memory_control_port;
	vm_offset_t offset;
	vm_size_t length;
	vm_prot_t desired_access;
{
#if	defined(lint) || defined(hc)
	memory_object++; memory_control_port++; offset++; length++; desired_access++;
#endif	defined(lint) || defined(hc)
	printf("(device_pager)memory_object_data_unlock: called!\n");
	return(KERN_FAILURE);
}

kern_return_t memory_object_data_write(memory_object,memory_control_port,offset,data,dataCnt)
	memory_object_t memory_object;
	memory_object_control_t memory_control_port;
	vm_offset_t offset;
	/* pointer_t */ int data;
	unsigned int dataCnt;
{
#if	defined(lint) || defined(hc)
	memory_object++; memory_control_port++; offset++; data++; dataCnt++;
#endif	defined(lint) || defined(hc)

	/*
	 *	This should only occur when the object is being terminated.
	 *	Memory-mapped device pages are wired down, so the pageout
	 *	daemon will never initiate a write.
	 *
	 *	If the "device" memory is really kernel virtual memory,
	 *	it is possible that the physical map module will indicate
	 *	that pages have been modified (in kernel VM).
	 */

	(void) vm_deallocate(device_pager_self,
		(vm_offset_t) data, (vm_size_t) dataCnt);

	return(KERN_FAILURE);
}

kern_return_t memory_object_lock_completed(memory_object,memory_control_port,offset,length)
	memory_object_t memory_object;
	memory_object_control_t memory_control_port;
	vm_offset_t offset;
	vm_size_t length;
{
#if	defined(lint) || defined(hc)
	memory_object++; memory_control_port++; offset++; length++;
#endif	defined(lint) || defined(hc)
	printf("(device_pager)memory_object_lock_completed: called!\n");
	return(KERN_FAILURE);
}

kern_return_t	memory_object_init(pager, pager_request, pager_name, pager_page_size)
	memory_object_t		pager;
	memory_object_control_t	pager_request;
	memory_object_name_t	pager_name;
	vm_size_t		pager_page_size;
{
	dev_pager_t	d;
	vm_object_t	object;
	vm_offset_t	offset;
	int		num_pages;
	vm_page_t	pg_cur;
	int		i;

	if (pager_page_size != PAGE_SIZE)
		panic("(device_pager)memory_object_init: wrong page size");

	/*
	 *	Find the mapping arguments associated with this object
	 */

	simple_lock(&device_pager_lock);
	for (d = device_pager_list; d != DEV_PAGER_NULL; d = d->next)
		if (d->pager == pager)
			break;
	simple_unlock(&device_pager_lock);

	if (d == DEV_PAGER_NULL)
		panic("(device_pager)memory_object_init: bad pager");

	/*
	 *	Record the request port
	 */

	if (d->pager_request != PORT_NULL)
		panic("(device_pager)memory_object_init: already initialized!");

	d->pager_request = pager_request;
#ifdef	lint
	pager_name++;
#endif	lint

	/*
	 *	Look for the object into which we will jam
	 *	physical pages.
	 */

    {
	kern_port_t pager_port;

	object = VM_OBJECT_NULL;

	if (object_copyin(device_pager_task, pager_request, MSG_TYPE_PORT,
			  FALSE, (kern_obj_t *) &pager_port)) {
		object = vm_object_lookup(pager_port);
		port_release(pager_port);
	}
    }

	if (object == VM_OBJECT_NULL) {
		/*
		 *	Termination has already occurred or
		 *	someone did something bogus with our
		 *	pager port.
		 *
		 *	We can safely ignore initialization
		 *	in either case.
		 */
		d->pages_size = 0;
		return(KERN_FAILURE);
	}

	/*
	 *	Grab enough memory for vm_page structures to
	 *	represent all pages in the object, and a little
	 *	bit more for a handle on them.
	 */
	num_pages = atop(d->size);
	d->pages_size = round_page(num_pages * sizeof(struct vm_page));
	d->pages = (vm_page_t) kmem_alloc(kernel_map, d->pages_size);

	/*
	 *	Fill in each page with the proper physical address,
	 *	and attach it to the object.  Mark it as wired-down
	 *	to keep the pageout daemon's hands off it.
	 */

	for (i = 0, pg_cur = d->pages, offset = d->offset; i < num_pages;
			i++, pg_cur++, offset += PAGE_SIZE) {
		vm_offset_t	addr;
		vm_page_t	old_page;

		/*
		 *	The mapping function takes a byte offset, but returns
		 *	a machine-dependent page frame number.  We convert
		 *	that into something that the pmap module will
		 *	accept later.
		 */

		addr = pmap_phys_address(
		   (*(d->mapfun))(d->dev, offset, d->prot));

		/*
		 *	Insert a page with the appropriate physical
		 *	address.  [In the even that a thread using this data
		 *	gets to it before we initialize, it will have
		 *	entered a page and waited on it.  We throw it away,
		 *	causing that thread to be awakened.  We'll later
		 *	ignore the pagein request.]
		 */

		vm_object_lock(object);
		if ((old_page = vm_page_lookup(object, offset)) != VM_PAGE_NULL) {
			vm_page_lock_queues();
			vm_page_free(old_page);
			vm_page_unlock_queues();
		}
		/* XXX This is very close to vm_page_replace */

		vm_page_init(pg_cur, object, offset, addr);
  		pg_cur->wire_count = 1;
		pg_cur->fictitious = TRUE;	/* Page structure is ours */
		PAGE_WAKEUP(pg_cur);
		vm_object_unlock(object);
	}
	
	vm_object_deallocate(object);

	memory_object_set_attributes(pager_request, TRUE, FALSE, MEMORY_OBJECT_COPY_NONE);

	return(KERN_SUCCESS);
}


/*
 *	Deallocate the page structures allocated for a device pager
 */
kern_return_t	memory_object_terminate(pager, pager_request, pager_name)
	memory_object_t		pager;
	memory_object_control_t	pager_request;
	memory_object_name_t	pager_name;
{
	dev_pager_t	d, p;

	/*
	 *	Find this pager
	 */

	simple_lock(&device_pager_lock);
	for (d = device_pager_list; d != DEV_PAGER_NULL; p = d, d = d->next)
		if (d->pager_request == pager_request)
			break;

	if (d == DEV_PAGER_NULL) {
		printf("(device_pager)memory_object_terminate: unknown user\n");
		return(KERN_FAILURE);
	}
	 else {
		if (d->pager == pager)
			port_deallocate(device_pager_self, pager);
		 else
			printf("(device_pager)memory_object_terminate: wrong object port\n");
		 
		/*
		 *	Remove this pager from the list.
		 */

		if (d == device_pager_list)
			device_pager_list = d->next;
		 else
		 	p->next = d->next;

		simple_unlock(&device_pager_lock);

		/*
		 *	Free the memory allocated for the page structures
		 *	and free the device pager structure.
		 */

		kmem_free(kernel_map, (vm_offset_t) d->pages, d->pages_size);
		zfree(device_pager_zone, (vm_offset_t) d);
	}
	

	port_deallocate(device_pager_self, pager_request);
	port_deallocate(device_pager_self, pager_name);
	return(KERN_SUCCESS);
}

void		device_pager_port_death(port)
	port_t		port;
{
	printf("device_pager_port_death: 0x%x died\n", port);
}

#define SERVER_LOOP		device_pager_server_loop
#define SERVER_NAME		"device_pager"
#define SERVER_DISPATCH(in,out)	device_pager_server(in, out)
#define TERMINATE_FUNCTION	device_pager_port_death
#define LOCAL_PORT		device_pager_enabled_set
#define memory_object_server	device_pager_server

#include <kern/server_loop.c>
#include <mach/memory_object_server.c>

void		device_pager()
{
	extern void task_name();

	task_name("device pager");
	SERVER_LOOP();
}
