h32963
s 00000/00000/00015
d D 8.1 93/06/08 18:09:13 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00015/00000/00000
d D 5.1 90/06/07 16:13:23 bostic 1 0
c date and time created 90/06/07 16:13:23 by bostic
e
u
U
t
T
I 1
program copydata(data, output);
var
    ch: char;
    data: text;
begin
    reset(data);
    while not eof(data) do begin
	while not eoln(data) do begin
	    read(data, ch);
	    write(ch)
	end;
	readln(data);
	writeln
    end
end { copydata }.
E 1
