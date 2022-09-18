h21192
s 00000/00000/00010
d D 8.1 93/06/08 18:09:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 90/06/07 16:15:38 bostic 1 0
c date and time created 90/06/07 16:15:38 by bostic
e
u
U
t
T
I 1
program x(output);
var
	x: ^ integer;
	y: ^ integer;
begin
	new(y);
	x := y;
	x^ := 1;
	x := x;
end.
E 1
