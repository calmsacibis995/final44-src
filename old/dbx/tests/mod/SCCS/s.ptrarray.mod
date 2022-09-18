h18903
s 00009/00000/00000
d D 5.1 90/06/25 15:34:11 bostic 1 0
c date and time created 90/06/25 15:34:11 by bostic
e
u
U
t
T
I 1
module main;
var p : pointer to array [1..10] of integer;
    i : integer;
begin
    new(p);
    for i := 1 to 10 do
	p^[i] := i;
    end;
end main.
E 1
