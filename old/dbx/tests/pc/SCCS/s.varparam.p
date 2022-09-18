h29039
s 00020/00000/00000
d D 5.1 90/06/25 15:37:37 bostic 1 0
c date and time created 90/06/25 15:37:37 by bostic
e
u
U
t
T
I 1
program varparam(input, output);
var i : integer;

procedure p(var i : integer);
begin
	i := 3;
	writeln('end of p');
end;

procedure q(var i : integer);
var j : integer;
begin
	p(i);
	writeln('end of q');
end;

begin
	q(i);
	writeln('end of test, i = ', i:1);
end.
E 1
