h62595
s 00002/00002/00081
d D 8.1 93/06/06 15:24:21 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00075
d D 1.2 91/04/12 16:53:36 bostic 2 1
c new copyright; att/bsd/shared
e
s 00076/00000/00000
d D 1.1 81/06/17 00:40:37 mckusick 1 0
c date and time created 81/06/17 00:40:37 by mckusick
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

var
filesize, headsize, tailsize :integer;
result :fileptr;

begin
tailsize := 0;
while not eof(fptr) do begin
	get(fptr);
	tailsize := tailsize + 1
	end;
filesize := 0;
reset(fptr);
while not eof(fptr) do begin
	get(fptr);
	filesize := filesize + 1
	end;
reset(fptr);
for headsize := 1 to filesize - tailsize do
	get(fptr);
result.cnt := headsize;
TELL := result
end;

procedure SEEK(
 var	fptr :text;
 var	cnt :fileptr);

var
i :integer;

begin
reset(fptr);
for i := 1 to cnt.cnt do
	get(fptr)
end;

procedure APPEND(
 var	fptr :text);

var
tmp :text;

begin
rewrite(tmp);
reset(fptr);
while not eof(fptr) do begin
	if eoln(fptr) then
		writeln(tmp)
	else
		write(tmp, fptr^);
	get(fptr)
	end;
reset(tmp);
rewrite(fptr);
while not eof(tmp) do begin
	if eoln(tmp) then
		writeln(fptr)
	else
		write(fptr, tmp^);
	get(tmp)
	end
end;
E 1
