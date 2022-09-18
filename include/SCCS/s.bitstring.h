h13224
s 00002/00002/00115
d D 8.1 93/07/19 11:10:54 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00009/00098
d D 5.6 93/07/19 11:10:46 bostic 7 5
c the bit_alloc() macro had a typo
c bit_nset() and bit_nclear() didn't work if only a single byte of bits
c From: abaddon@abyss.demon.co.uk (David Boyce)
e
s 00002/00002/00105
d R 8.1 93/06/02 20:05:01 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00102
d D 5.5 91/04/03 16:08:25 bostic 5 4
c protect all user-level include files against reinclusion
e
s 00001/00011/00101
d D 5.4 90/06/01 14:00:13 bostic 4 3
c new copyright notice
e
s 00001/00001/00111
d D 5.3 90/05/30 10:45:07 bostic 3 2
c calloc to clear bits first
e
s 00036/00028/00076
d D 5.2 90/04/04 11:06:30 bostic 2 1
c remove side-effects, make value a pointer so could be a function
e
s 00104/00000/00000
d D 5.1 89/12/13 20:57:41 bostic 1 0
c date and time created 89/12/13 20:57:41 by bostic
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Vixie.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

I 5
#ifndef _BITSTRING_H_
#define	_BITSTRING_H_

E 5
typedef	unsigned char bitstr_t;

/* internal macros */
				/* byte of the bitstring bit is in */
#define	_bit_byte(bit) \
	((bit) >> 3)

				/* mask for the bit within its byte */
#define	_bit_mask(bit) \
	(1 << ((bit)&0x7))

/* external macros */
				/* bytes in a bitstring of nbits bits */
#define	bitstr_size(nbits) \
	((((nbits) - 1) >> 3) + 1)

				/* allocate a bitstring */
#define	bit_alloc(nbits) \
D 3
	(bitstr_t *)malloc(1, \
E 3
I 3
	(bitstr_t *)calloc(1, \
E 3
D 7
	    (unsigned int)_bitstr_size(nbits) * sizeof(bitstr_t))
E 7
I 7
	    (unsigned int)bitstr_size(nbits) * sizeof(bitstr_t))
E 7

				/* allocate a bitstring on the stack */
#define	bit_decl(name, nbits) \
	(name)[bitstr_size(nbits)]

				/* is bit N of bitstring name set? */
#define	bit_test(name, bit) \
	((name)[_bit_byte(bit)] & _bit_mask(bit))

				/* set bit N of bitstring name */
#define	bit_set(name, bit) \
	(name)[_bit_byte(bit)] |= _bit_mask(bit)

				/* clear bit N of bitstring name */
#define	bit_clear(name, bit) \
	(name)[_bit_byte(bit)] &= ~_bit_mask(bit)

D 2
				/* clear bits 0 ... N in bitstring name */
E 2
I 2
				/* clear bits start ... stop in bitstring */
E 2
#define	bit_nclear(name, start, stop) { \
D 2
	register int _startbyte, _stopbyte; \
	_startbyte = _bit_byte(start); \
	(name)[_startbyte] &= 0xff >> (8 - ((start)&0x7)); \
	for (_stopbyte = _bit_byte(stop); ++_startbyte < _stopbyte; \
	    (name)[_startbyte] = 0); \
	(name)[_stopbyte] &= 0xff << (((stop)&0x7) + 1); \
E 2
I 2
	register bitstr_t *_name = name; \
	register int _start = start, _stop = stop; \
	register int _startbyte = _bit_byte(_start); \
	register int _stopbyte = _bit_byte(_stop); \
D 7
	_name[_startbyte] &= 0xff >> (8 - (_start&0x7)); \
	while (++_startbyte < _stopbyte) \
		_name[_startbyte] = 0; \
	_name[_stopbyte] &= 0xff << ((_stop&0x7) + 1); \
E 7
I 7
	if (_startbyte == _stopbyte) { \
		_name[_startbyte] &= ((0xff >> (8 - (_start&0x7))) | \
				      (0xff << ((_stop&0x7) + 1))); \
	} else { \
		_name[_startbyte] &= 0xff >> (8 - (_start&0x7)); \
		while (++_startbyte < _stopbyte) \
			_name[_startbyte] = 0; \
		_name[_stopbyte] &= 0xff << ((_stop&0x7) + 1); \
	} \
E 7
E 2
}

D 2
				/* set bits 0 ... N in string name */
E 2
I 2
				/* set bits start ... stop in bitstring */
E 2
#define	bit_nset(name, start, stop) { \
D 2
	register int _startbyte, _stopbyte; \
	_startbyte = _bit_byte(start); \
	(name)[_startbyte] |= 0xff << ((start)&0x7); \
	for (_stopbyte = _bit_byte(stop); ++_startbyte < _stopbyte; \
	    (name)[_startbyte] = 0xff); \
	(name)[_stopbyte] |= 0xff >> (7 - ((stop)&0x7)); \
E 2
I 2
	register bitstr_t *_name = name; \
	register int _start = start, _stop = stop; \
	register int _startbyte = _bit_byte(_start); \
	register int _stopbyte = _bit_byte(_stop); \
D 7
	_name[_startbyte] |= 0xff << ((start)&0x7); \
	while (++_startbyte < _stopbyte) \
	    _name[_startbyte] = 0xff; \
	_name[_stopbyte] |= 0xff >> (7 - (_stop&0x7)); \
E 7
I 7
	if (_startbyte == _stopbyte) { \
		_name[_startbyte] |= ((0xff << (_start&0x7)) & \
				    (0xff >> (7 - (_stop&0x7)))); \
	} else { \
		_name[_startbyte] |= 0xff << ((_start)&0x7); \
		while (++_startbyte < _stopbyte) \
	    		_name[_startbyte] = 0xff; \
		_name[_stopbyte] |= 0xff >> (7 - (_stop&0x7)); \
	} \
E 7
E 2
}

				/* find first bit clear in name */
#define	bit_ffc(name, nbits, value) { \
D 2
	register int _byte, _stopbyte; \
	for ((value) = -1, _byte = 0, _stopbyte = _bit_byte(nbits); \
	    _byte <= _stopbyte; _byte++) \
		if ((name)[_byte] != 0xff) { \
			(value) = _byte << 3; \
			for (_stopbyte = (name)[_byte]; (_stopbyte&0x1); \
			    ++(value), _stopbyte >>= 1); \
E 2
I 2
	register bitstr_t *_name = name; \
	register int _byte, _nbits = nbits; \
	register int _stopbyte = _bit_byte(_nbits), _value = -1; \
	for (_byte = 0; _byte <= _stopbyte; ++_byte) \
		if (_name[_byte] != 0xff) { \
			_value = _byte << 3; \
			for (_stopbyte = _name[_byte]; (_stopbyte&0x1); \
			    ++_value, _stopbyte >>= 1); \
E 2
			break; \
		} \
I 2
	*(value) = _value; \
E 2
}

				/* find first bit set in name */
#define	bit_ffs(name, nbits, value) { \
D 2
	register int _byte, _stopbyte; \
	for ((value) = -1, _byte = 0, _stopbyte = _bit_byte(nbits); \
	    _byte <= _stopbyte; _byte++) \
		if ((name)[_byte]) { \
			(value) = _byte << 3; \
			for (_stopbyte = (name)[_byte]; !(_stopbyte&0x1); \
			    ++(value), _stopbyte >>= 1); \
E 2
I 2
	register bitstr_t *_name = name; \
	register int _byte, _nbits = nbits; \
	register int _stopbyte = _bit_byte(_nbits), _value = -1; \
	for (_byte = 0; _byte <= _stopbyte; ++_byte) \
		if (_name[_byte]) { \
			_value = _byte << 3; \
			for (_stopbyte = _name[_byte]; !(_stopbyte&0x1); \
			    ++_value, _stopbyte >>= 1); \
E 2
			break; \
		} \
I 2
	*(value) = _value; \
E 2
}
I 5

#endif /* !_BITSTRING_H_ */
E 5
E 1
