h45764
s 00025/00000/00000
d D 5.1 90/09/03 18:58:37 sklower 1 0
c date and time created 90/09/03 18:58:37 by sklower
e
u
U
t
T
I 1
/*
 * Fetch netdb entry from /etc/x25hosts for a
 * host given its X.121 address.
 *
 * Copyright 1985 Frank Pronk
 */

#include <sys/types.h>
#include <netccitt/x25.h>
#include <netdb.h>

struct hostent *
getx25hostbyaddr (addr)
char *addr;
{
	register struct hostent *p;
	struct hostent *getx25hostent ();

	setx25hostent(0);
	while ((p = getx25hostent ()) &&
		strcmp (((struct sockaddr_x25 *)p->h_addr)->x25_addr, addr))
			;
	endx25hostent ();
	return (p);
}
E 1
