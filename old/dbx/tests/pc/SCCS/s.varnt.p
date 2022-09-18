h26341
s 00021/00000/00000
d D 5.1 90/06/25 15:37:36 bostic 1 0
c date and time created 90/06/25 15:37:36 by bostic
e
u
U
t
T
I 1
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
