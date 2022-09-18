/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	reg.h,v $
 * Revision 1.4.1.2  90/11/27  13:40:25  rvb
 * 	Change Prime copyright as per Peter J. Weyman authorization.
 * 	[90/11/19            rvb]
 * 
 * Revision 1.4.1.1  90/06/07  08:05:02  rvb
 * 	Add a couple clarifying comments.	[kupfer]
 * 	Update reg.h to track thread_status.h and put in some comments
 * 	to tie the two together.		[kupfer]
 * 
 * Revision 1.4  89/09/25  12:25:55  rvb
 * 	This is UNPUBLISHED PROPRIETARY SOURCE CODE of Prime Computer, Inc.
 * 	[89/09/23            rvb]
 * 
 */

/*
Copyright (c) 1988,1989 Prime Computer, Inc.  Natick, MA 01760
All Rights Reserved.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and
without fee is hereby granted, provided that the above
copyright notice appears in all copies and that both the
copyright notice and this permission notice appear in
supporting documentation, and that the name of Prime
Computer, Inc. not be used in advertising or publicity
pertaining to distribution of the software without
specific, written prior permission.

THIS SOFTWARE IS PROVIDED "AS IS", AND PRIME COMPUTER,
INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN
NO EVENT SHALL PRIME COMPUTER, INC.  BE LIABLE FOR ANY
SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN ACTION OF CONTRACT, NEGLIGENCE, OR
OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/* 
 * These constants give offsets into the register array that is saved 
 * when a thread enters the kernel.  See the definition of 
 * i386_saved_state in mach/i386/thread_status.h.
 * 
 * These definitions are useful for user programs that need to look at 
 * the register array (e.g., debuggers) but don't want to jump through 
 * hoops to look at i386_saved_state.
 */
#define I386_SAVED_REGISTERS	23	/* sizeof(i386_saved_state) / 4 */

#define OLDGS	0x0016
#define OLDFS	0x0015
#define OLDDS	0x0014
#define OLDES	0x0013

#define SS	0x0012
#define UESP	0x0011
#define EFL	0x0010
#define CS	0x000F
#define EIP	0x000E
#define ERR	0x000D
#define TRAPNO	0x000C
#define EAX	0x000B
#define ECX	0x000A
#define EDX	0x0009
#define EBX	0x0008
#define ESP	0x0007
#define EBP	0x0006
#define ESI	0x0005
#define EDI	0x0004
#define DS	0x0003
#define ES	0x0002
#define FS	0x0001
#define GS	0x0000
