h51161
s 00016/00000/00020
d D 4.2 90/06/23 16:20:43 bostic 2 1
c add Chris Torek's comment before removing
e
s 00020/00000/00000
d D 4.1 83/06/30 16:11:54 sam 1 0
c date and time created 83/06/30 16:11:54 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

/*
I 2
 * This can't be written in C.  You have to longjmp from a context
 * below (stackwise) the call to setjmp:
 *
 *	/* test reset/setexit *(/
 *	main()
 *	{
 *		int i = setexit();
 *		printf("i=%d\n", i);
 *		if (i == 0)
 *			reset(1);
 *	}
 *
 * The above prints `longjmp botch' and dumps core.
 */

/*
E 2
 * Backwards compatible setexit/reset.
 */
#include <setjmp.h>

static	jmp_buf save;

setexit()
{
	
	return (setjmp(save));
}

reset(x)
{

	longjmp(save, x);
}
E 1
