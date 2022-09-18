h21731
s 00016/00000/00000
d D 5.1 90/06/25 15:30:15 bostic 1 0
c date and time created 90/06/25 15:30:15 by bostic
e
u
U
t
T
I 1
/*
 * Test of displaying strings compiled into the text segment via -R.
 */

char str[] = "this is a test";

main ()
{
    f("parameter test");
}

f (s)
char *s;
{
    abort();
}
E 1
