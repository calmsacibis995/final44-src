h26266
s 00016/00000/00000
d D 5.1 90/06/25 15:34:14 bostic 1 0
c date and time created 90/06/25 15:34:14 by bostic
e
u
U
t
T
I 1
module main;
type
    Rec = record
	charValue : char;
	intValue : integer;
	subrange : [0..1000];
	realValue : real;
    end;
var
    r : Rec;
begin
    r.charValue := 'c';
    r.intValue := 3;
    r.subrange := 10;
    r.realValue := 3.4;
end main.
E 1
