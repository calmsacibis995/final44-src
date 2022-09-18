/* 
 * Mach Operating System
 * Copyright (c) 1993-1986 Carnegie Mellon University
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
 * $Log:	phys.s,v $
 * Revision 2.5  93/02/01  09:52:53  danner
 * 	Cpp cleanups.
 * 
 * Revision 2.4  93/01/24  14:14:50  danner
 * 	Changed a few comments where the first non-blank symbol on the
 * 	line was #. The gcc preprossor took that as a directive.
 * 	[93/01/17            mrt]
 * 
 * Revision 2.2  91/05/08  13:20:56  dbg
 * 	Fix for ANSI C preprocessor.
 * 	[91/04/23            dbg]
 * 
 * 	Save and restore page table entries, rather than
 * 	using interrupt protection.
 * 	[89/07/09            mwyoung]
 * 
 * Revision 2.1  89/08/03  16:26:05  rwd
 * Created.
 * 
 * 16-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Really make copy_{to,from}_phys work for any alignment.
 *
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support any alignment/size in copy_{to,from}_phys routines.
 *
 *  7-Jun-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed copy_to_phys, copy_from_phys and phys_zero to round
 *	partial page sizes up to the nearest page size (machine
 *	dependent page size).
 *
 * 12-Mar-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added copy_to_phys, copy_from_phys, phys_zero.
 *
 * 17-Dec-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *	File:	vax/phys.s
 *	Author:	Avadis Tevanian, Jr., 1986.
 *
 *	Physical memory routines.
 */

#include <vax/asm.h>
#include <vax/mtpr.h>
#include <mach/vax/vm_param.h>
#include <vax/pmap.h>
#include <mach/vm_param.h>

#define	PTE_BITS	(VAX_PTE_VALID|VAX_PTE_KW)

/*
 *	phys_zero(phys_addr, size)
 *
 *	Zero some physical memory.
 *	NB: Assumes that the address and size describe an integral
 *	number of VAX pages!
 */
	.text
ENTRY(phys_zero, R10|R9|R8)
	addl3	$ VAX_PGBYTES-1,8(ap),r10	# prepare to round
	ashl	$ -VAX_PGSHIFT,r10,r10		# count
	bneq	phys_zero_mem			/* use common code if
						   work to do */
	ret

/*
 *	pmap_zero_page(phys_addr)
 *
 *	Zero a machine independent page of physical memory.
 */
	.text
ENTRY(pmap_zero_page, R10|R9|R8)
	ashl	$ -VAX_PGSHIFT,_page_size,r10	# count (won`t be 0)

/*
 *	Common code for phys_zero and pmap_zero_page.
 */
phys_zero_mem:
	CPU_NUMBER_R0				# which cpu am I?
	ashl	$2,r0,r9			# convert to long offset
	addl2	_phys_map_pte1,r9		# pte address.
	ashl	$ VAX_PGSHIFT,r0,r8		# now make it page offset
	addl2	_phys_map_vaddr1,r8		# get virtual address
	ashl	$ -VAX_PGSHIFT,4(ap),r0		/* convert physical address to
						  page frame number */
	pushl	(r9)				# save old PTE
	bisl3	$ PTE_BITS,r0,(r9)		# map the page
1:	mtpr	r8,$ TBIS			# invalidate
	movc5	$0,0,$0,$ VAX_PGBYTES,(r8)	# zero the page
	incl	(r9)				# next page
	sobgtr	r10,1b				# count done till done
	mtpr	r8,$ TBIS			# invalidate again
	movl	(sp)+,(r9)			# restore old PTE
	ret

/*
 *	pmap_copy_page(src_addr, dst_addr)
 *
 *	Copy one machine independent page of physical memory to another.
 */
	.text
ENTRY(pmap_copy_page, R10|R9|R8|R7|R6)
	ashl	$ -VAX_PGSHIFT,_page_size,r10	# count
	CPU_NUMBER_R0				# which cpu am I?
	ashl	$2,r0,r0			# convert to long offset
	addl3	r0,_phys_map_pte1,r9		# src pte
	addl3	r0,_phys_map_pte2,r8		# dst pte
	ashl	$ VAX_PGSHIFT-2,r0,r0		# now page offset
	addl3	r0,_phys_map_vaddr1,r7		# source virtual address
	addl3	r0,_phys_map_vaddr2,r6		# destination virtual address
	pushl	(r9)				# save old source PTE
	pushl	(r8)				# save old destination PTE
	ashl	$ -VAX_PGSHIFT,4(ap),r0		# convert src address to pfn
	bisl3	$ PTE_BITS,r0,(r9)		# map the source page
	ashl	$ -VAX_PGSHIFT,8(ap),r0		# convert dst address to pfn
	bisl3	$ PTE_BITS,r0,(r8)		# map the destination page
1:	mtpr	r7,$ TBIS			# invalidate source
	mtpr	r6,$ TBIS			# invalidate destination
	movc3	$ VAX_PGBYTES,(r7),(r6)		# copy the page
	incl	(r9)				# next source
	incl	(r8)				# next destination
	sobgtr	r10,1b				# loop back for more
	mtpr	r7,$ TBIS			# invalidate source again
	mtpr	r6,$ TBIS			# invalidate destination again
	movl	(sp)+,(r8)			# restore old destination PTE
	movl	(sp)+,(r9)			# restore old source PTE
	ret

/*
 *	copy_to_phys(src_addr_v, dst_addr_p, count)
 *
 *	Copy virtual memory to physical memory.  The virtual memory
 *	must be resident.
 *
 *	Works with any alignment/offset.
 */
	.text
ENTRY(copy_to_phys, R10|R9|R8|R7)
	movl	12(ap),r10			# pick up count
	CPU_NUMBER_R0				# which cpu am I?
	ashl	$2,r0,r9			# convert to long offset
	addl2	_phys_map_pte2,r9		# dst pte
	ashl	$ VAX_PGSHIFT,r0,r8		# now page offset
	addl2	_phys_map_vaddr2,r8		# destination virtual address
	movl	$ VAX_PGBYTES,r7			# copy size (per iteration)
	pushl	(r9)				# save old PTE
	movl	4(ap),r1			# src virtual address
	movl	8(ap),r0			# dst physical address
	ashl	$ -VAX_PGSHIFT,r0,r2		# convert to pfn
	bisl3	$ PTE_BITS,r2,(r9)		# map the destination page
	bicl2	$~( VAX_PGBYTES-1),r0		# get byte offset in dest
	beql	1f				# no offset, do aligned copy
	subl2	r0,r7				# count until alignment
	cmpl	r10,r7				# size OK?
	bgtr	0f				# yes, continue
	movl	r10,r7				# no, use minimum
0:	mtpr	r8,$ TBIS			# invalidate TLB
	movc3	r7,(r1),(r8)[r0]		/* copy to (va + offset)
						   r1 & r8 ready for loop */
	subl2	r7,r10				# decrement by amount copied
	movl	$ VAX_PGBYTES,r7			# reset r7
	incl	(r9)				# next destination pfn
1:	cmpl	r10,r7				# enough for full copy left?
	bgtr	2f				# yes, do it
	movl	r10,r7				# no, use minimum
2:	mtpr	r8,$ TBIS			# invalidate destination
	movc3	r7,(r1),(r8)			/* copy the page
						  (increments source address)*/
	incl	(r9)				# next destination pfn
	subl2	r7,r10				# decrement by amount copied
	bgtr	1b				# more to do
	mtpr	r8,$ TBIS			# invalidate TLB again
	movl	(sp)+,(r9)			# restore old PTE
	ret

/*
 *	copy_from_phys(src_addr_p, dst_addr_v, count)
 *
 *	Copy physical memory to virtual memory.  The virtual memory
 *	must be resident (e.g. the buffer pool).
 *
 *	Works with any alignment/offset.
 */
	.text
ENTRY(copy_from_phys, R10|R9|R8|R7)
	movl	12(ap),r10			# pick up count
	CPU_NUMBER_R0				# which cpu am I?
	ashl	$2,r0,r9			# convert to long offset
	addl2	_phys_map_pte1,r9		# src pte
	ashl	$ VAX_PGSHIFT,r0,r8		# now page offset
	addl2	_phys_map_vaddr1,r8		# source virtual address
	movl	$ VAX_PGBYTES,r7			# copy size (per iteration)
	pushl	(r9)				# save old PTE
	movl	8(ap),r3			# dst virtual address
	movl	4(ap),r0			# get src physical address
	ashl	$ -VAX_PGSHIFT,r0,r2		# convert to pfn
	bisl3	$ PTE_BITS,r2,(r9)		# map the source page
	bicl2	$~( VAX_PGBYTES-1),r0		# get byte offset in src
	beql	1f				# no offset, do aligned copy
	subl2	r0,r7				# count until alignment
	cmpl	r10,r7				# size OK?
	bgtr	0f				# yes, continue
	movl	r10,r7				# no, use minimum
0:	mtpr	r8,$ TBIS			# invalidate TLB
	movc3	r7,(r8)[r0],(r3)		/* copy unaligned portion
						  (increments destination) */
	subl2	r7,r10				# adjust total count
	movl	$ VAX_PGBYTES,r7			# reset r7
	incl	(r9)				# next source pfn
1:	cmpl	r10,r7				# enough for full copy left?
	bgtr	2f				# yes, do it
	movl	r10,r7				# no, use minimum
2:	mtpr	r8,$ TBIS			# invalidate source
	movc3	r7,(r8),(r3)			/* copy the page
						  (increments destination)*/
	incl	(r9)				# next source
	subl2	r7,r10				# decrement total count
	bgtr	1b				# branch back for more
	mtpr	r8,$ TBIS			# invalidate TLB again
	movl	(sp)+,(r9)			# restore old PTE
	ret


/*
 *	unsigned char getmemc(phys_addr)
 *
 *	Get one byte from physical memory.
 */
	.text
ENTRY(getmemc, R11|R10|R9)
	CPU_NUMBER_R0				# which cpu am I?
	ashl	$2,r0,r10			# convert to long offset
	addl2	_phys_map_pte1,r10		# pte address.
	ashl	$ VAX_PGSHIFT,r0,r11		# now make it page offset
	addl2	_phys_map_vaddr1,r11		# get virtual address
	movl	4(ap),r1			# get physical address
	ashl	$ -VAX_PGSHIFT,r1,r2		# convert to pfn
	pushl	(r10)				# save old PTE
	bisl3	$ PTE_BITS,r2,(r10)		# map the page
	mtpr	r11,$ TBIS			# invalidate
	bicl2	$~( VAX_PGBYTES-1),r1		# get byte offset in page
	movzbl	(r11)[r1],r0			# get the byte
	mtpr	r11,$ TBIS			# invalidate again
	movl	(sp)+,(r10)			# restore old PTE
	ret

/*
 *	void putmemc(phys_addr, byte)
 *
 *	Put one byte to physical memory.
 */
	.text
ENTRY(putmemc, R11|R10)
	CPU_NUMBER_R0				# which cpu am I?
	ashl	$2,r0,r10			# convert to long offset
	addl2	_phys_map_pte1,r10		# pte address.
	ashl	$ VAX_PGSHIFT,r0,r11		# now make it page offset
	addl2	_phys_map_vaddr1,r11		# get virtual address
	movl	4(ap),r1			# get physical address
	ashl	$ -VAX_PGSHIFT,r1,r2		# convert to pfn
	pushl	(r10)				# save old PTE
	bisl3	$ PTE_BITS,r2,(r10)		# map the page
	mtpr	r11,$ TBIS			# invalidate
	bicl2	$~( VAX_PGBYTES-1),r1		# get byte offset in page
	movb	8(ap),(r11)[r1]			# put the byte
	mtpr	r11,$ TBIS			# invalidate again
	movl	(sp)+,(r10)			# restore old PTE
	ret
