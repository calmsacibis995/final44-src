h56598
s 00002/00002/00020
d D 8.1 93/06/06 15:48:16 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00000/00000
d D 5.1 91/04/16 14:58:50 bostic 1 0
c date and time created 91/04/16 14:58:50 by bostic
e
u
U
t
T
I 1
(*
D 2
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *)

program enum(input, output);
const	BLAH = 3;
type	Color = (RED, GREEN, BLUE);
	String = array[1..5] of char;
var	i : (red, green, blue);
	s : array[Color] of String;
	c : char;
begin
	i := blue;
	c := 'a';
	s[RED] := 'red';
	writeln('test of enumerated types');
end.
E 1
