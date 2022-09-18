h31394
s 00030/00000/00000
d D 5.1 90/06/25 15:30:02 bostic 1 0
c date and time created 90/06/25 15:30:02 by bostic
e
u
U
t
T
I 1
struct blah {
    int x;
    int y;
};

main ()
{
    register int i;
    register struct blah *p;
    register char *s;
    struct blah b;
    int j;

    s = "this is a test";
    s += 5;
    j = 0;
    p = &b;
    p->x = 3;
    p->y = 4;
    for (i = 0; i < 2; i++) {
	j = i;
	put(i);
    }
}

static put(i)
register int i;
{
    printf("%d ", i);
}
E 1
