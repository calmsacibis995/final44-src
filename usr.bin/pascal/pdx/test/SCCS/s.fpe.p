h47234
s 00002/00002/00018
d D 8.1 93/06/06 15:48:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00000/00000
d D 5.1 91/04/16 14:58:53 bostic 1 0
c date and time created 91/04/16 14:58:53 by bostic
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

{
  test of floating point exception handling
}

program fpe(input, output);
var x, y : real;
begin
	x := 1;
	y := 0;
	writeln(x/y);
end.
E 1
