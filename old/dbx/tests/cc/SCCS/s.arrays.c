h21007
s 00023/00000/00000
d D 5.1 90/06/25 15:29:20 bostic 1 0
c date and time created 90/06/25 15:29:20 by bostic
e
u
U
t
T
I 1
/*
 * Test of debugging arrays in C.
 */

int a[10], *b;

p (i, a, j)
int i, a[], j;
{
    a[3] = i;
    a[4] = j;
}

main ()
{
    int i;

    b = a;
    for (i = 0; i < 10; i++) {
	a[i] = i;
    }
    p(4, a, 5);
}
E 1
