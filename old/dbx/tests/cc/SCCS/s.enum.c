h17114
s 00015/00000/00000
d D 5.1 90/06/25 15:29:31 bostic 1 0
c date and time created 90/06/25 15:29:31 by bostic
e
u
U
t
T
I 1
typedef enum { RED, GREEN, BLUE } Color;

main()
{
    Color c;

    c = BLUE;
    f(RED);
}

f(c)
Color c;
{
    printf("c = %d\n", c);
}
E 1
