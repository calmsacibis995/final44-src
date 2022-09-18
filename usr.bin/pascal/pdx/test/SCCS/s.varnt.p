h54415
s 00002/00002/00028
d D 8.1 93/06/06 15:49:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 91/04/16 14:59:07 bostic 1 0
c date and time created 91/04/16 14:59:07 by bostic
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

program varnt(input, output);
type
	vrec = record
		rfield : integer;
		case integer of
		1: (
			vfield : integer;
		);
		2: (
			vfield2 : real;
		);
	end;

var
	r : vrec;
begin
	r.vfield := 1;
	r.vfield2 := 2.5;
	r.rfield := 0;
	writeln('done');
end.
E 1
