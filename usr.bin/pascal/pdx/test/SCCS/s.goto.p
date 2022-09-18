h49764
s 00002/00002/00028
d D 8.1 93/06/06 15:48:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 91/04/16 14:58:55 bostic 1 0
c date and time created 91/04/16 14:58:55 by bostic
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


program gototest(input, output);
label 1;

procedure A;
begin
	writeln('A');
	goto 1;
end;

procedure B;
begin
	writeln('B');
	A;
end;

begin
	B;
1:
	writeln('exiting');
end.
E 1
