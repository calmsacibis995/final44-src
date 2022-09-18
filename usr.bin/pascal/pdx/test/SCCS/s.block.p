h51672
s 00002/00002/00022
d D 8.1 93/06/06 15:47:59 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 5.1 91/04/16 14:58:46 bostic 1 0
c date and time created 91/04/16 14:58:46 by bostic
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

program blocktest(input, output);
procedure A;
	procedure B;
	begin
		writeln('in procedure B');
	end;
begin
	writeln('in procedure A');
	B;
end;

begin
	writeln('in main program');
	A;
end.
E 1
