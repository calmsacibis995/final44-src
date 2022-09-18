h03892
s 00002/00002/00031
d D 8.1 93/06/06 15:13:32 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00025
d D 1.2 91/04/12 16:53:35 bostic 2 1
c new copyright; att/bsd/shared
e
s 00026/00000/00000
d D 1.1 81/06/17 00:40:19 mckusick 1 0
c date and time created 81/06/17 00:40:19 by mckusick
e
u
U
t
T
I 1
D 2
(* Copyright (c) 1979 Regents of the University of California *)
E 2
I 2
(*
D 3
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *)
E 2

const
sccsid = '%Z%%M% %I% %G%';

type
fileptr = record
	cnt :integer
	end;

function TELL(
var	fptr :text)
{returns} :fileptr;

  external;

procedure SEEK(
 var	fptr :text;
 var	cnt :fileptr);

  external;

procedure APPEND(
 var	fptr :text);

   external;
E 1
