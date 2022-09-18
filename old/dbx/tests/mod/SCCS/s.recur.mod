h23908
s 00016/00000/00000
d D 5.1 90/06/25 15:34:15 bostic 1 0
c date and time created 90/06/25 15:34:15 by bostic
e
u
U
t
T
I 1
module main;

from io import Writef, output;

procedure r (n : integer);
begin
    Writef(output, "blah\n");
    if n > 0 then
	r(n - 1);
	Writef(output, "blah2\n");
    end;
end r;

begin
    r(5);
end main.
E 1
