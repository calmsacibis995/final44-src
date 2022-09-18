h18880
s 00000/00000/00007
d D 8.1 93/06/04 17:02:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00000
d D 5.1 87/11/30 18:43:11 bostic 1 0
c date and time created 87/11/30 18:43:11 by bostic
e
u
U
t
T
I 1
s/.word	0x0.*$/&\
	.data\
1:\
	.long	0\
	.text\
	addr	1b,r0\
	jsb	mcount/
E 1
