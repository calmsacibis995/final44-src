/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	copy_user.s,v $
 * Revision 2.1.1.5  91/03/28  08:43:43  rvb
 * 	Define careful_bcopy from mainline
 * 	[91/03/27            rvb]
 * 
 * Revision 2.1.1.4  90/03/22  17:59:47  rvb
 * 	Make it work w/o MACH_KDB.
 * 
 * Revision 2.1.1.3  90/03/12  11:17:15  rvb
 * 	Put userwrite on copyout and copyoutstr and make sure that we
 * 	ALWAYS check the return value.
 * 	[90/03/10            rvb]
 * 
 * Revision 2.1.1.2  90/03/10  00:31:42  rvb
 * 	ENTRY's should be Entry here, except those for ALLOW_FAULT
 * 	[90/03/07            rvb]
 * 
 * Revision 2.1.1.1  90/03/07  13:28:32  rvb
 * 	All the "copy" code that may fault referencing user data now
 * 	lives here.
 * 	[90/03/07            rvb]
 * 
 * 	Created.
 * 	[90/03/06            rvb]
 * 
 */

#include <mach_kdb.h>
#include <machine/asm.h>
#include <sys/errno.h>

#define MIN_KERNEL_ADDRESS (0xc0000000)

#define EFAULT_ERROR_FRAME \
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $EFAULT; MCOUNT

#define M1_ERROR_FRAME \
	pushl	%ebp; movl %esp, %ebp; pushl %esi; pushl %edi; pushl $-1; MCOUNT

#define ERROR_LEAVE \
	leal 4(%esp), %esp; popl %edi; popl %esi; popl %ebp

/ FAULT_ERROR is called if copyin() or copyout() generate a page fault
/ that can't be satisfied.  Through some stack magic FAULT_ERROR
/ returns EFAULT to the caller of copyin/copyout.
/ ALLOW_FAULT_START and ALLOW_FAULT_END bracket other code that can
/ use FAULT_ERROR.  See trap() for more details.

ENTRY(FAULT_ERROR)
#if	MACH_KDB
	cmpl	$1, EXT(kdbtrapok)
	je	LBf(in_kdb,0)
#endif	MACH_KDB
	movl	-4(%ebp),%esi
	movl	-8(%ebp),%edi
LB(in_kdb,0):
	movl	-12(%ebp),%eax
	movl	%ebp,%esp
	popl 	%ebp
	ret

ENTRY(ALLOW_FAULT_START)

	/*
	 * US(x)
	 * validates x (and the length), both to be < kernel address and
	 * that the range not include the kernel space
	 */
#define US(ur) \
	movl	$MIN_KERNEL_ADDRESS, %edx;\
	cmpl	%edx, ur;\
	ja	9f;\
	leal	(ur, %ecx), %eax;\
	cmpl	ur, %eax;\
	jb	9f;\
	cmpl	%edx, %eax;\
	jbe	8f;\
9:	movl	$EFAULT, %eax;\
	jmp	3f;\
8:

/*
	copyin(from, to, count)
	char *from, *to;
	vm_size_t count;
*/

Entry(copyin)
	EFAULT_ERROR_FRAME
	movl	B_ARG0, %esi
	movl	B_ARG1, %edi
	movl	B_ARG2, %ecx

	US(%esi)

	cld
	movl	%ecx, %edx
	sarl	$2, %ecx
	rep; movsl

	leal	3, %ecx
	andl	%edx, %ecx
	rep; movsb

	movl	%ecx, %eax
3:	ERROR_LEAVE
	ret

/*
 * Version of Copyin that copies from kernel space to kernel space
 * Careful_bcopy(from, to, len)
 *	r1 == from (user source address)
 *	r3 == to (kernel destination address)
 *	r5 == length
 *
 * Only called by kernel, don't need any range checks.
 */
Entry(careful_bcopy)
	EFAULT_ERROR_FRAME
	movl	B_ARG0, %esi
	movl	B_ARG1, %edi
	movl	B_ARG2, %ecx

	cld
	movl	%ecx, %edx
	sarl	$2, %ecx
	rep; movsl

	leal	3, %ecx
	andl	%edx, %ecx
	rep; movsb

	movl	%ecx, %eax
3:	ERROR_LEAVE
	ret

/*
	copyout(from,to,count)
	char *from,*to;
	vm_size_t count;
*/
Entry(copyout)
	EFAULT_ERROR_FRAME
	movl	B_ARG0, %esi
	movl	B_ARG1, %edi
	movl	B_ARG2, %ecx


	US(%edi)
	pushl	%ecx
	pushl	%edi
	call	EXT(userwrite)
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f

	cld
	movl	B_ARG2, %ecx
	movl	%ecx, %edx
	sarl	$2, %ecx
	rep; movsl

	leal	3, %ecx
	andl	%edx, %ecx
	rep; movsb

	movl	%ecx, %eax
3:	ERROR_LEAVE
	ret

	/*
	 * UT(x)
	 * validates x (and the length), both to be < kernel address and
	 * truncates the length to not cross into the kernel
	 */
#define UT(ur) \
	movl	$MIN_KERNEL_ADDRESS, %edx;\
	cmpl	%edx, ur;\
	ja	9f;\
	leal	(ur, %ecx), %eax;\
	cmpl	ur, %eax;\
	jb	9f;\
	cmpl	%edx, %eax;\
	jbe	8f;\
	movl	%edx, %ecx;\
	subl	ur, %ecx;\
	jmp	8f;\
9:	movl	$EFAULT, %eax;\
	jmp	3f;\
8:
/*
	copystr(s1, s2, max, len)
	register char *s1, *s2;
	register int max;
	int *len;
*/
Entry(copystr)
	EFAULT_ERROR_FRAME

	movl	B_ARG0, %esi
	movl	B_ARG1, %edi
	movl	B_ARG2, %ecx

	cld
0:	lodsb	
	stosb
	orb	%al, %al
	loopne	0b
	je	1f
	movl	$ENOENT, %eax
	jmp	3f

1:	movl	B_ARG3, %eax
	orl	%eax, %eax
	je	2f

	subl	B_ARG0, %esi
	movl	%esi, (%eax)

2:	xorl	%eax, %eax

3:	ERROR_LEAVE
	ret

/*
	copyinstr(up, kp, max, len)
	char *up, *kp;
	int max, *len;
*/

Entry(copyinstr)
	EFAULT_ERROR_FRAME

	movl	B_ARG0, %esi
	movl	B_ARG1, %edi
	movl	B_ARG2, %ecx

	UT(%esi)

	cld
0:	lodsb	
	stosb
	orb	%al, %al
	loopne	0b
	je	1f
	movl	$ENOENT, %eax
	jmp	3f

1:	movl	B_ARG3, %eax
	orl	%eax, %eax
	je	2f

	subl	B_ARG0, %esi
	movl	%esi, (%eax)

2:	xorl	%eax, %eax

3:	ERROR_LEAVE
	ret

/*
	copyoutstr(kp, up, max, len)
	char *kp, *up;
	int max, *len;
*/
Entry(copyoutstr)
	EFAULT_ERROR_FRAME

	movl	B_ARG0, %esi
	movl	B_ARG1, %edi
	movl	B_ARG2, %ecx

	UT(%edi)
	pushl	%ecx
	pushl	%edi
	call	EXT(userwrite)
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f

	cld
	movl	B_ARG2, %ecx
0:	lodsb	
	stosb
	orb	%al, %al
	loopne	0b
	je	1f
	movl	$ENOENT, %eax
	jmp	3f

1:	movl	B_ARG3, %eax
	orl	%eax, %eax
	je	2f

	subl	B_ARG0, %esi
	movl	%esi, (%eax)

2:	xorl	%eax, %eax

3:	ERROR_LEAVE
	ret


	/*
	 * US4(x)
	 * validates x (and the length), both to be < kernel address
	 */
#define US4(ur) \
	movl	$MIN_KERNEL_ADDRESS, %edx;\
	cmpl	%edx, ur;\
	ja	9f;\
	leal	(ur, %ecx), %eax;\
	cmpl	%edx, %eax;\
	jbe	8f;\
9:	movl	$-1, %eax;\
	jmp	3f;\
8:

Entry(fuword)
	M1_ERROR_FRAME
	movl	B_ARG0, %esi
	leal	4, %ecx
	US4(%esi)
	movl	(%esi), %eax	
3:	ERROR_LEAVE
	ret

Entry(suiword)
Entry(suword)
	M1_ERROR_FRAME
	movl	B_ARG0, %esi
	leal	4, %ecx
	US4(%esi)
	pushl	%ecx
	pushl	%esi
	call	EXT(userwrite)
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f
	movl	B_ARG1, %eax
	movl	%eax, (%esi)
3:	ERROR_LEAVE
	ret

Entry(fuibyte)
Entry(fubyte)
	M1_ERROR_FRAME
	movl	B_ARG0, %esi
	leal	1, %ecx
	US4(%esi)
	xorl	%eax, %eax
	movb	(%esi), %al
3:	ERROR_LEAVE
	ret

Entry(suibyte)
Entry(subyte)
	M1_ERROR_FRAME
	movl	B_ARG0, %esi
	leal	1, %ecx
	US4(%esi)
	pushl	%ecx
	pushl	%esi
	call	EXT(userwrite)
	leal	8(%esp), %esp
	orl	%eax, %eax
	jnz	3f
	movb	B_ARG1, %al
	movb	%al, (%esi)
3:	ERROR_LEAVE
	ret

#if	MACH_KDB
/*
 * write long word to kernel address space
	kdbwlong(addr, p)
	long *addr;
	long *p;
 */
Entry(kdbwlong)
	EFAULT_ERROR_FRAME
	incl	EXT(kdbtrapok)
	
	movl	B_ARG0, %eax
	movl	B_ARG1, %edx
	movl	(%edx), %ecx
	movl	%ecx, (%eax)
	xorl	%eax, %eax

	decl	EXT(kdbtrapok)
	ERROR_LEAVE
	ret

/*
 * read long word from kernel address space
	kdbrlong(addr, p)
	long *addr;
	long *p;
 */
Entry(kdbrlong)
	EFAULT_ERROR_FRAME
	incl	EXT(kdbtrapok)

	movl	B_ARG0, %eax
	movl	B_ARG1, %edx
	movl	(%eax), %ecx
	movl	%ecx, (%edx)
	xorl	%eax, %eax

	decl	EXT(kdbtrapok)
	ERROR_LEAVE
	ret
#endif	MACH_KDB

ENTRY(ALLOW_FAULT_END)
