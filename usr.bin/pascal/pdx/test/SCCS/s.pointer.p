h49346
s 00002/00002/00021
d D 8.1 93/06/06 15:48:50 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00000/00000
d D 5.1 91/04/16 14:59:02 bostic 1 0
c date and time created 91/04/16 14:59:02 by bostic
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

program pointer(input, output);
type	xp = ^x;
	x = record
		y : integer;
		a : real;
	end;

var	p : xp;
begin
	new(p);
	p^.y := 5;
	p^.a := 3.14;
	writeln('pointer test');
end.
E 1
