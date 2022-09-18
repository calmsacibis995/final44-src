h47520
s 00029/00000/00000
d D 5.1 90/09/03 18:58:38 sklower 1 0
c date and time created 90/09/03 18:58:38 by sklower
e
u
U
t
T
I 1
/*
 * Fetch netdb entry for a host given
 * its name from /etc/x25hosts
 *
 * Frank Pronk  1985
 */

#include <netdb.h>

struct hostent *
getx25hostbyname (name)
register char *name;
{
	register struct hostent *p;
	register char **cp;
	struct hostent *getx25hostent ();

	setx25hostent (0);
	while (p = getx25hostent ()) {
		if (strcmp (p->h_name, name) == 0)
			break;
		for (cp = p->h_aliases; *cp != 0; cp++)
			if (strcmp (*cp, name) == 0)
				goto found;
	}
found:
	endx25hostent ();
	return (p);
}
E 1
