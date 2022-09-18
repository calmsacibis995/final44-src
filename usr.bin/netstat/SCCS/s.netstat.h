h08926
s 00001/00001/00082
d D 8.2 94/01/04 11:41:55 bostic 9 8
c use -g for multicast instead of -B (follow BSDI)
e
s 00002/00002/00081
d D 8.1 93/06/12 17:05:18 bostic 8 7
c add 1993 to the copyright notice, yank to 8.1 for 4.4BSD snapshot
e
s 00000/00001/00083
d D 5.6 93/06/12 16:45:23 mckusick 7 5
c delete -h option for printing out IMP host table
e
s 00002/00002/00082
d R 8.1 93/06/06 15:44:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00083
d D 5.5 93/02/16 22:58:43 andrew 5 4
c add prototype for igmp routine
e
s 00029/00027/00054
d D 5.4 92/07/07 16:57:22 sklower 4 3
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00008/00001/00073
d D 5.3 92/07/06 15:36:21 sklower 3 2
c Multicast changes from lbl
e
s 00001/00001/00073
d D 5.2 92/05/27 18:11:59 sklower 2 1
c incorporate changes for new kvm interfaces from lbl
e
s 00074/00000/00000
d D 5.1 92/04/27 17:35:35 sklower 1 0
c date and time created 92/04/27 17:35:35 by sklower
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/cdefs.h>

int	Aflag;		/* show addresses of protocol control block */
int	aflag;		/* show all sockets (including servers) */
int	dflag;		/* show i/f dropped packets */
I 9
int	gflag;		/* show group (multicast) routing or stats */
E 9
D 7
int	hflag;		/* show IMP host table */
E 7
int	iflag;		/* show interfaces */
I 3
D 9
int	Bflag;		/* show multicast tables (or multicast stats) */
E 9
E 3
int	mflag;		/* show memory stats */
int	nflag;		/* show addresses numerically */
int	pflag;		/* show given protocol */
int	rflag;		/* show routing tables (or routing stats) */
int	sflag;		/* show protocol statistics */
int	tflag;		/* show i/f watchdog timers */

int	interval;	/* repeat interval for i/f stats */

char	*interface;	/* desired i/f for stats, or NULL for all i/fs */
int	unit;		/* unit number for above */

int	af;		/* address family */

char	*prog;		/* program name */


D 4
int	kread __P((off_t addr, char *buf, int size));
E 4
I 4
int	kread __P((u_long addr, char *buf, int size));
E 4
char	*plural __P((int));
I 3
char	*plurales __P((int));
E 3

D 4
void	protopr __P((off_t, char *));
void	tcp_stats __P((off_t, char *));
void	udp_stats __P((off_t, char *));
void	ip_stats __P((off_t, char *));
void	icmp_stats __P((off_t, char *));
void	protopr __P((off_t, char *));
E 4
I 4
void	protopr __P((u_long, char *));
void	tcp_stats __P((u_long, char *));
void	udp_stats __P((u_long, char *));
void	ip_stats __P((u_long, char *));
void	icmp_stats __P((u_long, char *));
I 5
void	igmp_stats __P((u_long, char *));
E 5
void	protopr __P((u_long, char *));
E 4

D 4
void	mbpr(off_t);
E 4
I 4
void	mbpr(u_long);
E 4

D 4
void	hostpr __P((off_t, off_t));
void	impstats __P((off_t, off_t));
E 4
I 4
void	hostpr __P((u_long, u_long));
void	impstats __P((u_long, u_long));
E 4

I 4
void	intpr __P((int, u_long));

E 4
void	pr_rthdr __P(());
void	pr_family __P((int));
D 4
void	rt_stats __P((off_t));
E 4
I 4
void	rt_stats __P((u_long));
E 4
char	*ns_phost __P((struct sockaddr *));
void	upHex __P((char *));

char	*routename __P((u_long));
char	*netname __P((u_long, u_long));
char	*ns_print __P((struct sockaddr *));
D 4
void	routepr __P((off_t));
E 4
I 4
void	routepr __P((u_long));
E 4

D 4
void	nsprotopr __P((off_t, char *));
void	spp_stats __P((off_t, char *));
void	idp_stats __P((off_t, char *));
void	nserr_stats __P((off_t, char *));
E 4
I 4
void	nsprotopr __P((u_long, char *));
void	spp_stats __P((u_long, char *));
void	idp_stats __P((u_long, char *));
void	nserr_stats __P((u_long, char *));
E 4
D 3
void	ns_erputil __P((int, int));
E 3

D 4
void	intpr __P((int, off_t));
E 4
I 4
void	intpr __P((int, u_long));
E 4

D 2
void	unixpr __P((off_t, off_t, struct protosw *));
E 2
I 2
D 4
void	unixpr __P((struct protosw *));
E 4
I 4
void	unixpr __P((u_long));
E 4
E 2

D 4
void	esis_stats __P((off_t, char *));
void	clnp_stats __P((off_t, char *));
void	cltp_stats __P((off_t, char *));
void	iso_protopr __P((off_t, char *));
I 3
void	iso_protopr1 __P((off_t, int));
void	tp_protopr __P((off_t, char *));
void	tp_inproto __P((off_t));
E 4
I 4
void	esis_stats __P((u_long, char *));
void	clnp_stats __P((u_long, char *));
void	cltp_stats __P((u_long, char *));
void	iso_protopr __P((u_long, char *));
void	iso_protopr1 __P((u_long, int));
void	tp_protopr __P((u_long, char *));
void	tp_inproto __P((u_long));
E 4
E 3
void	tp_stats __P((caddr_t, caddr_t));
I 3

D 4
void	mroutepr __P((off_t, off_t, off_t));
void	mrt_stats __P((off_t, off_t));
E 4
I 4
void	mroutepr __P((u_long, u_long, u_long));
void	mrt_stats __P((u_long, u_long));
E 4
E 3
E 1
