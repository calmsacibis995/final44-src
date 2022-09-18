h64497
s 00050/00000/00000
d D 7.1 92/01/07 17:32:21 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * TLB hash table values.
 * SHIFT2 should shift virtual address bit 22 to the high bit of the index.
 *			address:	index:
 *	USRTEXT		0x00400000	10xxxxxxx
 *	USRDATA		0x10000000	00xxxxxxx
 *	USRSTACK	0x7FFFFFFF	11xxxxxxx
 * This gives 1/2 the table to data, 1/4 for text and 1/4 for stack.
 * Note: the current process has its hash table mapped at PMAP_HASH_UADDR.
 *	the kernel's hash table is mapped at PMAP_HASH_KADDR.
 *	The size of the hash table is known in locore.s and machdep.c.
 */
#define PMAP_HASH_PAGES		1
#define PMAP_HASH_UADDR		(UADDR - PMAP_HASH_PAGES * NBPG)
#define PMAP_HASH_KADDR		(UADDR - 2 * PMAP_HASH_PAGES * NBPG)
#define PMAP_HASH_LOW_OFFSET	0
#define PMAP_HASH_HIGH_OFFSET	4
#define PMAP_HASH_NUM_ENTRIES	512
#define PMAP_HASH_SIZE_SHIFT	3
#define PMAP_HASH_SHIFT1	12
#define PMAP_HASH_SHIFT2	14
#define PMAP_HASH_MASK		(PMAP_HASH_NUM_ENTRIES - 1)
#define PMAP_HASH_SIZE		(PMAP_HASH_NUM_ENTRIES*sizeof(struct pmap_hash))

#define PMAP_HASH_USER(va) \
    (((int)va >= 0 ? \
	(((va) >> PMAP_HASH_SHIFT1) | ((va) >> PMAP_HASH_SHIFT2)) : \
	((va) >> PMAP_HASH_SHIFT1)) & PMAP_HASH_MASK)

/*
 * Defines for pmap_attributes[phys_mach_page];
 */
#define PMAP_ATTR_MOD	0x01	/* page has been modified */
#define PMAP_ATTR_REF	0x02	/* page has been referenced */

#ifndef LOCORE
extern char	*pmap_attributes;	/* reference and modify bits */
#endif
E 1
