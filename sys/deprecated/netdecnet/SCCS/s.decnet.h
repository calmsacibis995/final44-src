h45202
s 00000/00000/00018
d D 1.3 82/10/09 05:48:32 wnj 3 2
c fix header files
e
s 00001/00000/00017
d D 1.2 82/05/15 21:52:41 sam 2 1
c add keywords
e
s 00017/00000/00000
d D 1.1 82/05/15 21:46:16 sam 1 0
c date and time created 82/05/15 21:46:16 by sam
e
u
U
t
T
I 2
/*	%M%	%I%	%E%	*/
E 2
I 1

/*
 * DECnet address (should be expanded for Phase 3E)
 */
struct dn_addr {
	u_short	s_host;		/* remote host address */
};

/*
 * Socket address, DECnet style.
 */
struct sockaddr_dn {
	short	sdn_family;		/* AF_DECNET */
	u_short	sdn_port;		/* local port number */
	struct	dn_addr sdn_addr;	/* remote host/port address */
	char	sdn_zero[];
};
E 1
