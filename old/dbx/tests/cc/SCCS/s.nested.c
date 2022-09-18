h22879
s 00033/00000/00000
d D 5.1 90/06/25 15:29:54 bostic 1 0
c date and time created 90/06/25 15:29:54 by bostic
e
u
U
t
T
I 1
/*
 * Test of nested blocks.
 */
 
int i;

main ()
{
    i = 3;
    sub();
}

sub ()
{
    int i, j;

    for (i = 1; i <= 10; i++) {
	int j;

	j = j + i;
    }
    j = 0;
    for (i = 11; i <= 20; i++) {
	j = j + i;
    }
}

after ()
{
    int a;

    a = 3;
}
E 1
