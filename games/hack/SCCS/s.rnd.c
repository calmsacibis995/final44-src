h28759
s 00030/00000/00000
d D 5.1 90/05/02 08:41:09 bostic 1 0
c date and time created 90/05/02 08:41:09 by bostic
e
u
U
t
T
I 1
/* rnd.c - version 1.0.2 */

#define RND(x)	((random()>>3) % x)

rn1(x,y)
register x,y;
{
	return(RND(x)+y);
}

rn2(x)
register x;
{
	return(RND(x));
}

rnd(x)
register x;
{
	return(RND(x)+1);
}

d(n,x)
register n,x;
{
	register tmp = n;

	while(n--) tmp += RND(x);
	return(tmp);
}
E 1
