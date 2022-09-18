h29927
s 00009/00000/00000
d D 5.1 90/06/25 23:10:03 bostic 1 0
c date and time created 90/06/25 23:10:03 by bostic
e
u
U
t
T
I 1
"	@(#)mon.ex	4.4 (Berkeley) 7/26/83"
"	fix funny things done by mcount()"
"	fix its name, make it jsb'able, change registers to protect the caller"
g/_mcount/s//mcount/g
""
"	fix funny name for minbrk used by monstartup() to limit brk()"
g/_minbrk/s//minbrk/g
w
q
E 1
