h21273
s 00018/00000/00000
d D 5.1 90/06/25 15:37:25 bostic 1 0
c date and time created 90/06/25 15:37:25 by bostic
e
u
U
t
T
I 1
(*
 * Test of reals.
 *)

program realtest (input, output);
var
    x : real;
    y : real;

function f (x : real) : real;
begin
    f := 3.14*x;
end;

begin
    y := 3.0;
    x := f(y);
end.
E 1
