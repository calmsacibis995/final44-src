/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"

/*
 *	Compare bit fields with masking.  Compile this with
 *
 *		$ cc -S compare_bits.c
 *
 *	Bit fields are a considerable win for pulling out the
 *	character and attribute fields.  They break even with
 *	assignments.
 *
 */

main ()
{
	CHAR xxx;
	char x;
	int y;
	short int s;

BITS1 ();
	x = xxx.bits.letter;
	y = xxx.bits.attribute;
SHORT1 ();
	x = s & 0177;
	y = s & VT_VIDEO;

BITS2 ();
	xxx.bits.letter = x;
	xxx.bits.attribute = y;
SHORT2 ();
	s = x;
	s = y;

BITS3 ();
	xxx = y | x;
SHORT3 ();
	s = y | x;

DONE ();
}
