h17957
s 00011/00000/00000
d D 5.1 90/06/25 14:58:13 bostic 1 0
c date and time created 90/06/25 14:58:13 by bostic
e
u
U
t
T
I 1
typedef	unsigned short dev_t;

main()
{
	dev_t x = (dev_t)(-1);

	if (x == (dev_t)(-1))
		printf("ok\n");
	else
		printf("nope\n");
}
E 1
