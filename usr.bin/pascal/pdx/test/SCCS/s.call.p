h53263
s 00002/00002/00024
d D 8.1 93/06/06 15:48:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 5.1 91/04/16 14:58:49 bostic 1 0
c date and time created 91/04/16 14:58:49 by bostic
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

program calltest(input, output);
var i : integer;

procedure p(i : integer; r : real);
begin
    writeln('i = ', (i/0):1, ', r = ', r:1:2);
end;

procedure q(var i : integer);
begin
    i := 3;
end;

begin
    q(i);
    p(1, 3.4);
end.
E 1
