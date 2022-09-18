h21093
s 00023/00000/00000
d D 5.1 90/06/25 15:29:59 bostic 1 0
c date and time created 90/06/25 15:29:59 by bostic
e
u
U
t
T
I 1
/*
 * Test of static variables.
 */
 
static int ownx;

main()
{
    ownx = 2;
    f(3);
    f(4);
    return(0);
}

static int owny;

f(x)
int x;
{
    static int ownx;

    ownx = x;
}
E 1
