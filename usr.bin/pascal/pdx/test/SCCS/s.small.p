h42518
s 00002/00002/00011
d D 8.1 93/06/06 15:49:08 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00000/00000
d D 5.1 91/04/16 14:59:05 bostic 1 0
c date and time created 91/04/16 14:59:05 by bostic
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

program small(input, output);
begin
	writeln('this is small', 1 div 0);
end.
E 1
