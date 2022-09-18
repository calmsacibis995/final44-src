h15147
s 00020/00000/00000
d D 5.1 90/06/25 15:30:13 bostic 1 0
c date and time created 90/06/25 15:30:13 by bostic
e
u
U
t
T
I 1

int i;

p2 (i) int i;
{
    if (i < 5) {
	p2(i+1);
    }
}

p1 (i) int i;
{
    p2(i+1);
}

main ()
{
    i = 0;
    p1(i+1);
}
E 1
