h26471
s 00002/00002/00066
d D 8.1 93/06/06 15:49:12 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00068/00000/00000
d D 5.1 91/04/16 14:59:06 bostic 1 0
c date and time created 91/04/16 14:59:06 by bostic
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

program blah(input, output);
const
	CONSTANT = 3;
	FLTCON = 3.14;
type
	Index = 1..10;
	intarray = array[Index] of 0..100;
	rec = record
		x : integer;
		y : char;
		z : integer;
	end;
var
	i : integer;
	x : real;
	a : array[1..10] of intarray;
	r : rec;
	p : ^rec;
	b : boolean;
	unused : integer;

function first(var p : integer) : integer;
begin
	i := p;
	r.x := 4;
	r.y := 'y';
	r.z := 6;
	b := true;
	first := p;
end;

procedure start;
var	q : integer;
begin
	q := -5;
	q := first(q);
	a[i][1] := q;
end;

procedure init;
var	i, j : integer;
begin
	b := false;
	for i := 1 to 10 do begin
		for j := 1 to 10 do begin
			a[i][j] := 10*(i-1) + j;
		end;
	end;
	start;
end;

begin
	init;
	a[1][1] := 3;
	a[10][1] := 2;
	a[1][10] := 1;
	writeln('garbage');
	readln(i);
end.
E 1
