h33679
s 00023/00000/00000
d D 5.1 90/06/25 15:34:19 bostic 1 0
c date and time created 90/06/25 15:34:19 by bostic
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
    a : array [1..10] of integer;
    i : integer;
    b : array Color of integer;
    c : Color;

procedure p (i : integer; var a : array of integer; j : integer);
begin
    a[3] := i;
    a[4] := j;
end p;

begin
    for i := 1 to 2 do
	a[i] := i;
    end;
    p(4, a, 5);
    b[BLUE] := 3;
    c := RED;
end main.
E 1
