h19116
s 00019/00000/00000
d D 5.1 90/06/25 15:29:36 bostic 1 0
c date and time created 90/06/25 15:29:36 by bostic
e
u
U
t
T
I 1
/*
 * Test of floats and doubles.
 */

double f(x)
double x;
{
    return 3.14*x;
}

main()
{
    double x;
    float y;

    y = 3.0;
    x = f(y);
    return 0;
}
E 1
