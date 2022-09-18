h27703
s 00000/00000/00013
d D 8.1 93/06/08 18:09:20 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 5.1 90/06/07 16:14:43 bostic 1 0
c date and time created 90/06/07 16:14:43 by bostic
e
u
U
t
T
I 1
program kat(input, output);
var
    ch: char;
begin
    while not eof do begin
	while not eoln do begin
	    read(ch);
	    write(ch)
	end;
	readln;
	writeln
    end
end { kat }.
E 1
