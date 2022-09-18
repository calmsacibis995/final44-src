h05234
s 00004/00004/00041
d D 6.3 84/08/29 15:33:03 bloom 6 5
c Change includes.  No more ../h
e
s 00007/00004/00038
d D 6.2 84/08/21 10:20:43 karels 5 4
c change protocol family number in protosw to pointer to domain
e
s 00000/00000/00042
d D 6.1 83/07/29 07:16:35 sam 4 3
c 4.2 distribution
e
s 00019/00000/00023
d D 5.3 83/06/30 01:23:39 sam 3 2
c add etherlink support definitions
e
s 00002/00000/00021
d D 5.2 82/08/01 12:15:56 root 2 1
c typos
e
s 00021/00000/00000
d D 5.1 82/07/31 21:28:05 root 1 0
c date and time created 82/07/31 21:28:05 by root
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

D 6
#include "../h/param.h"
#include "../h/socket.h"
#include "../h/protosw.h"
I 2
#include "../h/domain.h"
E 6
I 6
#include "param.h"
#include "socket.h"
#include "protosw.h"
#include "domain.h"
E 6
E 2

/*
 * PUP-I protocol family: raw interface
 */
int	rpup_output();
I 2
extern	int raw_usrreq();
I 5
extern	struct domain pupdomain;		/* or at least forward */
E 5
E 2

struct protosw pupsw[] = {
D 5
{ SOCK_RAW,	PF_PUP,		0,		PR_ATOMIC|PR_ADDR,
E 5
I 5
{ SOCK_RAW,	&pupdomain,	0,		PR_ATOMIC|PR_ADDR,
E 5
  0,		rpup_output,	0,		0,
  raw_usrreq,
  0,		0,		0,		0,
},
};

struct domain pupdomain =
D 5
    { AF_PUP, "pup", pupsw, &pupsw[sizeof(pupsw)/sizeof(pupsw[0])] };
E 5
I 5
    { AF_PUP, "pup", 0, 0, 0,
      pupsw, &pupsw[sizeof(pupsw)/sizeof(pupsw[0])] };
E 5
I 3

#ifdef notdef
/*
 * 3 Mb/s Ethernet link protocol family: raw interface
 */
int	raw_enoutput();
extern	int raw_usrreq();

struct protosw ensw[] = {
D 5
{ SOCK_RAW,	PF_ETHERLINK,	0,		PR_ATOMIC|PR_ADDR,
E 5
I 5
{ SOCK_RAW,	&endomain,	0,		PR_ATOMIC|PR_ADDR,
E 5
  0,		raw_enoutput,	0,		0,
  raw_usrreq,
  0,		0,		0,		0,
},
};

struct domain endomain =
D 5
    { AF_ETHERLINK "ether", ensw, &ensw[sizeof(ensw)/sizeof(ensw[0])] };
E 5
I 5
    { AF_ETHERLINK "ether", 0, 0, 0,
      ensw, &ensw[sizeof(ensw)/sizeof(ensw[0])] };
E 5
#endif
E 3
E 1
