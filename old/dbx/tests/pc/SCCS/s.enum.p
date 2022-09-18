h23134
s 00016/00000/00000
d D 5.1 90/06/25 15:36:59 bostic 1 0
c date and time created 90/06/25 15:36:59 by bostic
e
u
U
t
T
I 1
program enumtest (input, output);
type
    Color = (RED, GREEN, BLUE);

var c1, c2 : Color;

procedure P (c : Color);
begin
    writeln('c = ', ord(c):1);
end;

begin
    c1 := BLUE;
    c2 := GREEN;
    P(RED);
end.
E 1
