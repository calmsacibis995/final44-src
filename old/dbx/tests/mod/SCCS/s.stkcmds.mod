h22775
s 00020/00000/00000
d D 5.1 90/06/25 15:34:18 bostic 1 0
c date and time created 90/06/25 15:34:18 by bostic
e
u
U
t
T
I 1
module main;
var
    i : integer;

procedure p2 (i : integer);
begin
    if i < 5 then
	p2(i+1);
    end;
end p2;

procedure p1 (i : integer);
begin
    p2(i+1);
end p1;

begin
    i := 0;
    p1(i+1);
end main.
E 1
