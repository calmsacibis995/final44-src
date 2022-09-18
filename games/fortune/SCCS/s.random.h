h22078
s 00013/00000/00000
d D 5.1 89/09/05 15:50:56 bostic 1 0
c new distribution from Ken Arnold
e
u
U
t
T
I 1
/* $Header: random.h,v 1.2 87/11/21 17:19:53 arnold Exp $ */

#ifdef SYSV
# define	srandom	srand48
# define	random	lrand48
# ifdef NO_RANDOM
#	undef	NO_RANDOM
# endif
#endif

void	srnd();

long	rnd();
E 1
