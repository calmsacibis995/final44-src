h04286
s 00002/00002/00061
d D 8.1 93/06/06 14:09:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00063/00000/00000
d D 5.1 93/05/11 11:53:22 bostic 1 0
c date and time created 93/05/11 11:53:22 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct hosttbl;
struct netinfo;
struct sockaddr_in;
struct timeval;
struct tsp;

struct hosttbl *addmach __P((char *, struct sockaddr_in *, struct netinfo *));
struct hosttbl *findhost __P((char *));
struct hosttbl *remmach __P((struct hosttbl *));

struct tsp *readmsg __P((int,
	    char *, struct timeval *, struct netinfo *));
struct tsp *acksend __P((struct tsp *,
	    struct sockaddr_in *, char *, int, struct netinfo *, int));

void	 addnetname __P((char *));
void	 adj_msg_time __P((struct tsp *, struct timeval *));
void	 bytehostorder __P((struct tsp *));
void	 bytenetorder __P((struct tsp *));
void	 byteorder __P((struct tsp *));
long	 casual __P((long, long));
int	 cksum __P((u_short *, int));
void	 correct __P((long));
char	*date __P((void));
void	 doquit __P((struct tsp *));
int	 election __P((struct netinfo *));
void	 get_goodgroup __P((int));
int	 good_host_name __P((char *));
void	 ignoreack __P((void));
int	 in_cksum __P((u_short *, int));
void	 lookformaster __P((struct netinfo *));
void	 makeslave __P((struct netinfo *));
int	 master __P((void));
void	 masterack __P((void));
void	 masterup __P((struct netinfo *));
int	 measure __P((u_long, u_long, char *, struct sockaddr_in *, int));
void	 msterup __P((struct netinfo *));
void	 mstotvround __P((struct timeval *, long));
long	 networkdelta __P((void));
void	 newslave __P((struct tsp *));
void	 print __P((struct tsp *, struct sockaddr_in *));
void	 prthp __P((clock_t));
void	 rmnetmachs __P((struct netinfo *));
void	 setstatus __P((void));
int	 slave __P((void));
void	 slaveack __P((void));
void	 spreadtime __P((void));
void	 suppress __P((struct sockaddr_in *, char *, struct netinfo *));
void	 synch __P((long));
void	 timevaladd __P((struct timeval *, struct timeval *));
void	 timevalsub __P((struct timeval *, struct timeval *, struct timeval *));
void	 traceoff __P((char *));
void	 traceon __P((void));
void	 xmit __P((int, u_int, struct sockaddr_in *));
E 1
