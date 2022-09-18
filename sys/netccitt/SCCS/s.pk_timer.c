h43938
s 00002/00002/00098
d D 8.1 93/06/10 22:54:06 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00009/00082
d D 7.7 92/12/08 17:11:14 sklower 7 6
c changes to run over both LLC and HDLC, and also use explicit shifts
c instead of bitfields.
e
s 00011/00011/00080
d D 7.6 92/10/11 11:49:42 bostic 6 5
c make kernel includes standard
e
s 00002/00001/00089
d D 7.5 91/05/29 19:32:38 sklower 5 4
c check to see if socket exists before setting so_error on connect ftimeout.
e
s 00002/00002/00088
d D 7.4 91/01/09 15:38:33 sklower 4 3
c pk_clear now takes for diagnostic code and whether to allow 
c graceful close.
e
s 00010/00009/00080
d D 7.3 90/08/30 18:48:40 sklower 3 2
c this version compiles; completely untested
e
s 00013/00001/00076
d D 7.2 90/05/11 15:22:20 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00077/00000/00000
d D 7.1 90/05/11 11:19:42 sklower 1 0
c date and time created 90/05/11 11:19:42 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
D 7
/*
 * Copyright (c) University of British Columbia, 1984
 * Copyright (c) 1990 The Regents of the University of California.
E 7
I 7
/* 
 * Copyright (c) Computing Centre, University of British Columbia, 1984
 * Copyright (C) Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1990, 1992
D 8
 * Copyright (c) 1990, 1992   Regents of the University of California.
E 7
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
I 7
 * 
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 7
 *
D 7
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
E 7
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 3
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 3
I 3
D 6
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 6
E 3

D 6
#include "../net/if.h"
E 6
I 6
#include <net/if.h>
E 6

D 3
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 3
I 3
D 6
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
E 6
I 6
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 6
E 3

/*
 * Various timer values.  They can be adjusted
 * by patching the binary with adb if necessary.
 */
int	pk_t20 = 18 * PR_SLOWHZ;	/* restart timer */
int	pk_t21 = 20 * PR_SLOWHZ;	/* call timer */
/* XXX pk_t22 is never used */
int	pk_t22 = 18 * PR_SLOWHZ;	/* reset timer */
int	pk_t23 = 18 * PR_SLOWHZ;	/* clear timer */

pk_timer ()
{
	register struct pkcb *pkp;
	register struct pklcd *lcp, **pp;
	register int lcns_jammed, cant_restart;

D 7
	for (pkp = pkcbhead; pkp; pkp = pkp->pk_next) {
E 7
I 7
	FOR_ALL_PKCBS(pkp) {
E 7
		switch (pkp -> pk_state) {
		case DTE_SENT_RESTART:
			lcp = pkp -> pk_chan[0];
			/*
			 * If restart failures are common, a link level
			 * reset should be initiated here.
			 */
D 7
			if (lcp -> lcd_timer && --lcp -> lcd_timer == 0)
E 7
I 7
			if (lcp -> lcd_timer && --lcp -> lcd_timer == 0) {
E 7
				pk_message (0, pkp -> pk_xcp,
					"packet level restart failed");
I 7
				pkp -> pk_state = DTE_WAITING;
			}
E 7
			break;

		case DTE_READY:
			lcns_jammed = cant_restart = 0;
			for (pp = &pkp -> pk_chan[1]; pp <= &pkp -> pk_chan[pkp -> pk_maxlcn]; pp++) {
				if ((lcp = *pp) == 0)
					continue;
				switch (lcp -> lcd_state) {
				case SENT_CALL: 
					if (--lcp -> lcd_timer == 0) {
I 5
					    if (lcp -> lcd_so)
E 5
						lcp -> lcd_so -> so_error = ETIMEDOUT;
D 4
						pk_clear (lcp);
E 4
I 4
D 5
						pk_clear (lcp, 49, 1);
E 5
I 5
					    pk_clear (lcp, 49, 1);
E 5
E 4
					}
					break;

				case SENT_CLEAR: 
					if (lcp -> lcd_retry >= 3)
						lcns_jammed++;
					else
						if (--lcp -> lcd_timer == 0)
D 4
							pk_clear (lcp);
E 4
I 4
							pk_clear (lcp, 50, 1);
E 4
					break;

				case DATA_TRANSFER:	/* lcn active */
					cant_restart++;
I 7
					break;

				case LCN_ZOMBIE:       /* zombie state */
					pk_freelcd (lcp);
E 7
					break;
				}
			}
			if (lcns_jammed > pkp -> pk_maxlcn / 2 && cant_restart == 0) {
				pk_message (0, pkp -> pk_xcp, "%d lcns jammed: attempting restart", lcns_jammed);
				pk_restart (pkp, 0);
			}
		}
	}
}
E 1
