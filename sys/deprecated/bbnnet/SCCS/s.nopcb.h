h29584
s 00011/00000/00000
d D 1.1 85/10/14 18:14:17 karels 1 0
c from BBN
e
u
U
t
T
I 1

/*
 * send an IP datagram.  Used when don't have any Internet protocol
 * control block associated with the action.  Dummies one up.
 */

#define NOPCB_IPSEND(mp, len, asis, retval)     \
	{ struct inpcb inp;                     \
	bzero ((caddr_t) &inp, sizeof(inp));	\
	retval = ip_send (&inp, mp, len, asis); \
	}
E 1
