h54693
s 00000/00000/00018
d D 8.1 93/06/08 18:09:11 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00018/00000/00000
d D 5.1 90/06/07 16:13:13 bostic 1 0
c date and time created 90/06/07 16:13:13 by bostic
e
u
U
t
T
I 1
{ This is a left marginal comment. }
program hello(output);
var i : integer; {This is a trailing comment}
j : integer;	{This is a right marginal comment}
k : array [ 1..10] of array [1..10] of integer;	{Marginal, but past the margin}
{
  An aligned, multi-line comment
  which explains what this program is
  all about
}
begin
i := 1; {Trailing i comment}
{A left marginal comment}
 {An aligned comment}
j := 1;		{Right marginal comment}
k[1] := 1;
writeln(i, j, k[1])
end.
E 1
