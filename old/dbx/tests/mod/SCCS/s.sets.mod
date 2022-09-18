h27156
s 00018/00000/00000
d D 5.1 90/06/25 15:34:17 bostic 1 0
c date and time created 90/06/25 15:34:17 by bostic
e
u
U
t
T
I 1
module sets;
type
    Color = (RED, BLUE, GREEN);
    ColorSet = set of Color;
var
    s : ColorSet;

procedure p (var s : ColorSet);
begin
    s := ColorSet{RED, BLUE};
end p;

begin
    p(s);
    if BLUE in s then
	s := s - ColorSet{BLUE};
    end;
end sets.
E 1
