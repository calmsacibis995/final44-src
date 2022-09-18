h28010
s 00016/00000/00000
d D 5.1 90/06/25 15:34:03 bostic 1 0
c date and time created 90/06/25 15:34:03 by bostic
e
u
U
t
T
I 1
module main;

from io import Writef, output;

var global : integer;

procedure p (i : integer; s : array of char; j : integer);
begin
    Writef(output, "in p(%d, %s, %d)\n", i, s, j);
    global := 10;
end p;

begin
    global := 3;
    p(3, "blah", 4);
end main.
E 1
