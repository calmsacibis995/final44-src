h57116
s 00002/00002/00027
d D 8.1 93/06/06 15:49:21 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00000/00000
d D 5.1 91/04/16 14:59:08 bostic 1 0
c date and time created 91/04/16 14:59:08 by bostic
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

program varparam(input, output);
var i : integer;

procedure p(var i : integer);
begin
	i := 3;
	writeln('end of p');
end;

procedure q(var i : integer);
var j : integer;
begin
	p(i);
	writeln('end of q');
end;

begin
	q(i);
	writeln('end of test, i = ', i:1);
end.
E 1
