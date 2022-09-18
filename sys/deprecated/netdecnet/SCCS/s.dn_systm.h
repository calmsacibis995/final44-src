h22220
s 00000/00000/00031
d D 1.3 82/10/09 05:48:37 wnj 3 2
c fix header files
e
s 00001/00000/00030
d D 1.2 82/05/15 21:52:44 sam 2 1
c add keywords
e
s 00030/00000/00000
d D 1.1 82/05/15 21:46:17 sam 1 0
c date and time created 82/05/15 21:46:17 by sam
e
u
U
t
T
I 2
/*	%M%	%I%	%E%	*/
E 2
I 1

/*
 * Miscellaneous DECnet definitions for kernel
 */

/*
 * Network types.
 *
 * The DECnet protocols often use unaligned 16 bit fields
 * as integers.  The d_short type represents such a field
 * in a protocol structure definition and the D_SHORT macro
 * extracts such a field given a pointer to the first byte.
 * The AD_SHORT macro assigns to such a field.
 * On the VAX it's easy since unaligned references are
 * allowed, on the 11 it would be a bit harder.
 */
typedef	char	d_short[2];

#if vax
#define	D_SHORT(x)	(*((u_short *)(x)))
#define	AD_SHORT(x, v)	(*((u_short *)(x))) = (v)
#endif

/*
 * The DECnet code, like the Internet code, runs off software
 * interrupts.  At present there is only a software interrupt
 * for the NSP layer, which will hand the data to the socket.
 */
#define	setnspintr()	mtpr(SIRR, 14)
#define	splimp		spl5
E 1
