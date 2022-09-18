h36519
s 00023/00000/00000
d D 5.1 90/06/25 15:36:27 bostic 1 0
c date and time created 90/06/25 15:36:27 by bostic
e
u
U
t
T
I 1
program test (input, output);
type
    Color = (RED, BLUE, GREEN);
    IntArray = array [1..10] of integer;
var a : IntArray;
    i : integer;
    b : array [Color] of integer;
    c : Color;

procedure p (i : integer; var a : IntArray; j : integer);
begin
    a[3] := i;
    a[4] := j;
end;

begin
    for i := 1 to 10 do begin
	a[i] := i;
    end;
    p(4, a, 5);
    b[BLUE] := 3;
    c := RED;
end.
E 1
