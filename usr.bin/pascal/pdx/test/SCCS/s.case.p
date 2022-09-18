h61304
s 00002/00002/00032
d D 8.1 93/06/06 15:48:12 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
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

program casetest(input, output);
var c : char;
	s : 0..1000;
	i : integer;
begin
	c := 'a';
	case c of
		'b': writeln('b');
		'c': writeln('c');
		'a': writeln('a');
	end;
	s := 3;
	case s of
		5: writeln('5');
		3: writeln('3');
		7: writeln('7');
	end;
	i := 1001;
	case i of
		0: writeln('0');
		-1: writeln('-1');
		1001: writeln('1001');
		-1001: writeln('-1001');
	end;
end.
E 1
