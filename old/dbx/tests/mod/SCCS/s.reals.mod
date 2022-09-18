h23616
s 00018/00000/00000
d D 5.1 90/06/25 15:34:13 bostic 1 0
c date and time created 90/06/25 15:34:13 by bostic
e
u
U
t
T
I 1
(*
 * Test of reals and longreals.
 *)

module main;
var
    x : longreal;
    y : real;

procedure f (x : real) : longreal;
begin
    return longfloat(3.14*x);
end f;

begin
    y := 3.0;
    x := f(y);
end main.
E 1
