h26888
s 00018/00000/00000
d D 5.1 90/06/25 15:37:34 bostic 1 0
c date and time created 90/06/25 15:37:34 by bostic
e
u
U
t
T
I 1
program sets (input, output);
type
    Color = (RED, BLUE, GREEN);
    ColorSet = set of Color;
var
    s : ColorSet;

procedure p (var s : ColorSet);
begin
    s := [RED, BLUE];
end;

begin
    p(s);
    if BLUE in s then begin
	s := s - [BLUE];
    end;
end.
E 1
