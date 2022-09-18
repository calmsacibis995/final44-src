h40948
s 00000/00000/00043
d D 6.1 83/07/29 07:16:33 sam 8 7
c 4.2 distribution
e
s 00019/00019/00024
d D 4.6 83/05/30 18:37:05 sam 7 6
c attempt to make it work in agreement with reality
e
s 00001/00001/00042
d D 4.5 82/04/10 23:39:45 sam 6 5
c typo
e
s 00001/00001/00042
d D 4.4 82/03/13 16:43:53 sam 5 4
c fix pup stuff
e
s 00004/00000/00039
d D 4.3 82/03/13 12:52:20 sam 4 3
c lint
e
s 00011/00001/00028
d D 4.2 82/03/03 11:04:10 sam 3 2
c cleanup raw pup interface
e
s 00000/00000/00029
d D 4.1 82/02/15 11:27:58 root 2 1
c just changing rev level
e
s 00029/00000/00000
d D 1.1 82/02/15 11:27:16 root 1 0
c date and time created 82/02/15 11:27:16 by root
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

D 7
/*
 * PUP port addressing.
 */
struct pupport {
	u_char	pp_net;
	u_char	pp_host;
	u_long	pp_socket;
E 7
I 7
struct	pupport {
	u_char	pup_net;
	u_char	pup_host;
	u_char	pup_socket[4];
E 7
D 3
}
E 3
I 3
};
E 3

/*
 * PUP header.
 */
struct pup_header {
	u_short	pup_length;
	u_char	pup_tcontrol;		/* transport control */
	u_char	pup_type;		/* protocol type */
	u_long	pup_id;			/* used by protocols */
D 7
	struct	pupport pup_dport, pup_sport;
#define	pup_dnet	pup_dport.pp_net
D 5
#define	pup_dhost	pup_dport.pp_dhost
E 5
I 5
#define	pup_dhost	pup_dport.pp_host
E 5
#define	pup_dsocket	pup_dport.pp_socket
#define	pup_snet	pup_sport.pp_net
#define	pup_shost	pup_sport.pp_host
#define	pup_ssocket	pup_sport.pp_socket
E 7
I 7
	u_char	pup_dnet;		/* destination */
	u_char	pup_dhost;
	u_char	pup_dsock[4];
	u_char	pup_snet;		/* source */
	u_char	pup_shost;
	u_char	pup_ssock[4];
E 7
};

#define	PUP_TRACE	01		/* trace pup in network */
I 3

I 7
#define	MINPUPSIZ	(sizeof (struct pup_header) + sizeof (short))
#define	MAXPUPDATA	532
#define	MAXPUPSIZ	(MINPUPSIZ + MAXPUPDATA)

#define	PUP_NOCKSUM	0xffff		/* no checksum supplied */

E 7
/*
 * A sockaddr, as seen through the eyes of PUP.
 */
struct sockaddr_pup {
	short	spup_family;
	short	spup_zero1;
D 7
	struct	pupport spup_addr;
E 7
I 7
	u_char	spup_net;
	u_char	spup_host;
	u_char	spup_sock[4];
E 7
	char	spup_zero2[4];
};
I 4
D 7

#define	sp_net		spup_addr.pp_net
#define	sp_host		spup_addr.pp_host
D 6
#define	sp_socket	spup_addr.pp_port
E 6
I 6
#define	sp_socket	spup_addr.pp_socket
E 7
E 6
E 4
E 3
E 1
