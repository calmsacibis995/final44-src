h56131
s 00005/00005/00022
d D 6.2 84/08/29 15:32:59 bloom 7 6
c Change includes.  No more ../h
e
s 00000/00000/00027
d D 6.1 83/07/29 07:16:31 sam 6 5
c 4.2 distribution
e
s 00003/00003/00024
d D 4.5 83/05/30 18:37:02 sam 5 4
c attempt to make it work in agreement with reality
e
s 00000/00002/00027
d D 4.4 82/10/17 13:38:17 root 4 3
c lint cleanup
e
s 00003/00003/00026
d D 4.3 82/10/09 05:45:00 wnj 3 2
c localize header files
e
s 00000/00002/00029
d D 4.2 82/06/20 00:54:45 sam 2 1
c purge COUNT stuff now that we can use gprof
e
s 00031/00000/00000
d D 4.1 82/06/13 14:10:28 sam 1 0
c date and time created 82/06/13 14:10:28 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

D 7
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
E 7
I 7
#include "param.h"
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
E 7
D 3
#include "../net/in.h"
#include "../net/in_systm.h"
E 3
#include "../net/af.h"
D 3
#include "../net/pup.h"
E 3
I 3
#include "../netpup/pup.h"
E 3

#ifdef PUP
pup_hash(spup, hp)
	struct sockaddr_pup *spup;
	struct afhash *hp;
{
I 3

E 3
D 2
COUNT(PUP_HASH);
E 2
D 5
	hp->afh_nethash = spup->spup_addr.pp_net;
	hp->afh_hosthash = spup->spup_addr.pp_host;
E 5
I 5
	hp->afh_nethash = spup->spup_net;
	hp->afh_hosthash = spup->spup_host;
E 5
D 4
	if (hp->afh_hosthash < 0)
		hp->afh_hosthash = -hp->afh_hosthash;
E 4
}

pup_netmatch(spup1, spup2)
	struct sockaddr_pup *spup1, *spup2;
{
I 3

E 3
D 2
COUNT(PUP_NETMATCH);
E 2
D 5
	return (spup1->spup_addr.pp_net == spup2->spup_addr.pp_net);
E 5
I 5
	return (spup1->spup_net == spup2->spup_net);
E 5
}
#endif
E 1
