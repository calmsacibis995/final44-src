h16092
s 00010/00000/00000
d D 5.1 90/06/25 14:58:28 bostic 1 0
c date and time created 90/06/25 14:58:28 by bostic
e
u
U
t
T
I 1
struct a {
	short	foo;
	short	timer[4];
};
f()
{
	register struct a *p;

	p->timer[2] = (int)p->foo;
}
E 1
