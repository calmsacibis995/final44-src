h54098
s 00002/00002/00023
d D 8.1 93/06/06 15:48:56 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 91/04/16 14:59:03 bostic 1 0
c date and time created 91/04/16 14:59:03 by bostic
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

program recursion(input, output);
var	i : integer;

function fact(n : integer) : integer;
begin
	if n <= 1 then begin
		fact := 1;
	end else begin
		fact := n * fact(n-1);
	end;
end;

begin
	i := 3;
	writeln(i:1, '! = ', fact(i):1);
end.
E 1
