h43074
s 00000/00000/00021
d D 8.1 93/06/08 18:09:16 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00000/00000
d D 5.1 90/06/07 16:14:36 bostic 1 0
c date and time created 90/06/07 16:14:36 by bostic
e
u
U
t
T
I 1
program x(output);
var
	a: set of char;
	b: Boolean;
	c: (red, green, blue);
	p: ^ integer;
	A: alfa;
	B: packed array [1..5] of char;
begin
	b := true;
	c := red;
	new(p);
	a := [];
	A := 'Hello, yellow';
	b := a and b;
	a := a * 3;
	if input < 2 then writeln('boo');
	if p <= 2 then writeln('sure nuff');
	if A = B then writeln('same');
	if c = true then writeln('hue''s and color''s')
end.
E 1
