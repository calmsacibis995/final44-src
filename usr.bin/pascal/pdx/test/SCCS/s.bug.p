h54384
s 00002/00002/00025
d D 8.1 93/06/06 15:48:02 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 91/04/16 14:58:48 bostic 1 0
c date and time created 91/04/16 14:58:48 by bostic
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

program test (output);
var a : array [1..10] of integer;
procedure foo;
begin
 a[4] := 100;
 a[5] := 100;
 a[6] := 100;
end;
function bar (x:integer):integer;
  begin
    bar := 10*x;
  end;
begin
 a[1] := 100;
 foo;
 a[2] := bar(2);
 a[3] := 100;
end.
E 1
