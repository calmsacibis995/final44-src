h43878
s 00002/00002/00015
d D 8.1 93/06/06 15:49:04 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00000/00000
d D 5.1 91/04/16 14:59:04 bostic 1 0
c date and time created 91/04/16 14:59:04 by bostic
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

program pdxtest( output );
var
    x : real;
begin
    x := 0.5;
    x := 0.0;
    writeln( '17.0/x ', 17.0/x );
end.
E 1
