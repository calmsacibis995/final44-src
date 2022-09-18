h33653
s 00022/00000/00000
d D 5.1 90/06/25 15:33:51 bostic 1 0
c date and time created 90/06/25 15:33:51 by bostic
e
u
U
t
T
I 1
module main;
type
    Color = (RED, BLUE, GREEN);
var
    a : dynarray of array of integer;
    i, j : integer;

procedure p (i : integer; var a : array of array of integer; j : integer);
begin
    a[3, 1] := i;
    a[4, 2] := j;
end p;

begin
    new(a, 10, 5);
    for i := 0 to 9 do
	for j := 0 to 4 do
	    a^[i, j] := i;
	end;
    end;
    p(4, a^, 5);
end main.
E 1
