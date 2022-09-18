/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	io_map.h,v $
 * Revision 2.1  89/08/03  16:36:46  rwd
 * Created.
 * 
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * Routines to map IO memory.
 */
#include <mach/vm_param.h>

vm_offset_t	io_map();
void		io_unmap();
void		io_map_done();
void		ioaccess();

void		scb_write_protect();
