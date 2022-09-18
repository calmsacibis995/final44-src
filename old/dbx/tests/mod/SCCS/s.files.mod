h26474
s 00016/00000/00000
d D 5.1 90/06/25 15:33:55 bostic 1 0
c date and time created 90/06/25 15:33:55 by bostic
e
u
U
t
T
I 1
module main;
import io;

var globalf : io.File;

procedure p (var f : io.File);
begin
    f := io.terminal;
    io.Writef(f, 'this is a test');
    io.Writef(f, '\n');
end p;

begin
    globalf := io.terminal;
    p(io.output);
end main.
E 1
