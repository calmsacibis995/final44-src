/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * hashindex = chash(char* s, unsigned int size)
 *
 * compute a hash table index for string s
 * size is the number of slots in the table
 */

#if vax

asm("		.text			");
asm("		.align	2		");
asm("		.globl	_chash		");
asm("	_chash:				");
asm("		.word	0x00		");
asm("		movq	4(ap),r2	");
asm("		clrl	r0		");
asm("	L1:				");
asm("		movb	(r2)+,r1	");
asm("		beql	L2		");
asm("		rotl	$7,r0,r0	");
asm("		xorb2	r1,r0		");
asm("		brb	L1		");
asm("	L2:				");
asm("		clrl	r1		");
asm("		ediv	r3,r0,r1,r0	");
asm("		ret			");

#else

#include <values.h>

#define LSHIFT		(BITSPERBYTE*sizeof(unsigned char)-1)
#define RSHIFT		(BITSPERBYTE*(sizeof(unsigned int)-1)+1)

int
chash(s, size)
register char	*s;
unsigned int	size;
{
	register unsigned int	i, c;

	for (i = 0; c = *s++;)
		i = ((i<<LSHIFT)|(i>>RSHIFT)) ^ c;
#if tahoe
	/*
	 * the power6 (tahoe) optimizer bombs without this
	 */

	i %= size;
	return(i);
#else
	return(i % size);
#endif
}

#endif
