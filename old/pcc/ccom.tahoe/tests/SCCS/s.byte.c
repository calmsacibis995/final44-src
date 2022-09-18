h18039
s 00012/00000/00000
d D 5.1 90/06/25 14:58:11 bostic 1 0
c date and time created 90/06/25 14:58:11 by bostic
e
u
U
t
T
I 1
char c;
short w;
long l;

f() {
	if ((unsigned)c <= 0177)
		c = 0;
	if ((unsigned)w <= 0xefff)
		w = 0;
	if ((unsigned)l <= 0xefffffff)
		l = 0;
}
E 1
