h26171
s 00002/00002/00504
d D 8.1 93/06/10 23:18:34 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00505
d D 7.10 93/06/04 17:02:05 sklower 10 9
c fix #endif something to #endif /* something */
e
s 00013/00014/00493
d D 7.9 92/10/11 12:21:36 bostic 9 8
c make kernel includes standard
e
s 00009/00005/00498
d D 7.8 91/05/06 18:58:51 bostic 8 7
c new copyright; att/bsd/shared
e
s 00003/00002/00500
d D 7.7 90/01/16 23:50:43 sklower 7 6
c mitre decbit changes
e
s 00008/00018/00494
d D 7.6 89/09/26 23:57:54 sklower 6 5
c Fixes from Dave Katz at um
e
s 00001/00000/00511
d D 7.5 89/08/29 13:43:58 sklower 5 4
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00008/00008/00503
d D 7.4 89/04/25 17:19:34 mckusick 4 3
c ../h => (implicitly) ../sys
e
s 00004/00004/00507
d D 7.3 89/04/22 11:53:25 sklower 3 2
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00010/00010/00501
d D 7.2 89/02/14 18:32:35 sklower 2 1
c wisconsin changes
e
s 00511/00000/00000
d D 7.1 88/12/14 15:29:25 sklower 1 0
c date and time created 88/12/14 15:29:25 by sklower
e
u
U
t
T
I 8
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
D 2
/* $Header: clnp_options.c,v 4.3 88/09/15 18:57:36 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_options.c,v $ */
E 2
I 2
/* $Header: /var/src/sys/netiso/RCS/clnp_options.c,v 5.1 89/02/09 16:20:37 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_options.c,v $ */
I 5
D 8
/*	%W% (Berkeley) %G% */
E 5
E 2

#ifndef lint
D 2
static char *rcsid = "$Header: clnp_options.c,v 4.3 88/09/15 18:57:36 hagens Exp $";
E 2
I 2
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/clnp_options.c,v 5.1 89/02/09 16:20:37 hagens Exp $";
E 2
#endif lint
E 8

#ifdef ISO

D 4
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 4
I 4
D 9
#include "types.h"
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
E 9
I 9
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 9
E 4

D 9
#include "../net/if.h"
#include "../net/route.h"
E 9
I 9
#include <net/if.h>
#include <net/route.h>
E 9

D 3
#include "../netiso/iso.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 3
I 3
D 9
#include "iso.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 9
I 9
#include <netiso/iso.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 9
E 3

/*
 * FUNCTION:		clnp_update_srcrt
 *
 * PURPOSE:			Process src rt option accompanying a clnp datagram.
 *						- bump src route ptr if src routing and
 *							we appear current in src route list.
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			If source routing has been terminated, do nothing.
 */
clnp_update_srcrt(options, oidx)
struct mbuf			*options;	/* ptr to options mbuf */
struct clnp_optidx	*oidx;		/* ptr to option index */
{
	u_char			len;	/* length of current address */
	struct iso_addr	isoa;	/* copy current address into here */

	if (CLNPSRCRT_TERM(oidx, options)) {
		IFDEBUG(D_OPTIONS)
			printf("clnp_update_srcrt: src rt terminated\n");
		ENDDEBUG
		return;
	}

	len = CLNPSRCRT_CLEN(oidx, options);
	bcopy(CLNPSRCRT_CADDR(oidx, options), (caddr_t)&isoa, len);
	isoa.isoa_len = len;
		
	IFDEBUG(D_OPTIONS)
		printf("clnp_update_srcrt: current src rt: %s\n", 
			clnp_iso_addrp(&isoa));
	ENDDEBUG

	if (clnp_ours(&isoa)) {
		IFDEBUG(D_OPTIONS)
			printf("clnp_update_srcrt: updating src rt\n");
		ENDDEBUG

		/* update pointer to next src route */
		len++;	/* count length byte too! */
		CLNPSRCRT_OFF(oidx, options) += len;
	}
}

/*
 * FUNCTION:		clnp_dooptions
 *
 * PURPOSE:			Process options accompanying a clnp datagram.
 *					Processing includes
 *						- log our address if recording route
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnp_dooptions(options, oidx, ifp, isoa)
struct mbuf			*options;	/* ptr to options mbuf */
struct clnp_optidx	*oidx;		/* ptr to option index */
struct ifnet		*ifp;		/* ptr to interface pkt is leaving on */
struct iso_addr		*isoa;		/* ptr to our address for this ifp */
{
	/*
	 *	If record route is specified, move all
	 *	existing records over, and insert the address of
	 *	interface passed
	 */
	if (oidx->cni_recrtp) {
		char 	*opt;			/* ptr to beginning of recrt option */
		u_char	off;			/* offset from opt of first free byte */
D 6
		char	*rec_start;		/* beginning of first record rt option */
E 6
I 6
		char	*rec_start;		/* beginning of new rt recorded */
E 6

D 2
		opt = oidx->cni_recrtp + (caddr_t)options;
E 2
I 2
		opt = CLNP_OFFTOOPT(options, oidx->cni_recrtp);
E 2
		off = *(opt + 1);
D 6
		rec_start = opt + 2;
E 6
I 6
		rec_start = opt + off - 1;
E 6

		IFDEBUG(D_OPTIONS)
			printf("clnp_dooptions: record route: option x%x for %d bytes\n",
				opt, oidx->cni_recrt_len);
			printf("\tfree slot offset x%x\n", off);
			printf("clnp_dooptions: recording %s\n", clnp_iso_addrp(isoa));
			printf("clnp_dooptions: option dump:\n");
			dump_buf(opt, oidx->cni_recrt_len);
		ENDDEBUG

		/* proceed only if recording has not been terminated */
		if (off != 0xff) {
I 6
			int new_addrlen = isoa->isoa_len + 1;
E 6
			/* 
			 *	if there is insufficient room to store the next address,
			 *	then terminate recording. Plus 1 on isoa_len is for the
			 *	length byte itself
			 */
D 6
			if (oidx->cni_recrt_len - off < isoa->isoa_len+1) {
E 6
I 6
			if (oidx->cni_recrt_len - (off - 1) < new_addrlen) {
E 6
				*(opt + 1) = 0xff;	/* terminate recording */
			} else {
D 6
				int new_addrlen = isoa->isoa_len + 1;
E 6
				IFDEBUG(D_OPTIONS)
D 6
					printf("clnp_dooptions: clnp_ypocb(x%x, x%x, %d)\n",
						rec_start, rec_start + new_addrlen, off - 3);
				ENDDEBUG
						
				/* move existing records over */
				clnp_ypocb(rec_start, rec_start + new_addrlen, off - 3);

				IFDEBUG(D_OPTIONS)
E 6
					printf("clnp_dooptions: new addr at x%x for %d\n",
						rec_start, new_addrlen);
				ENDDEBUG

D 6
				/* add new record */
				*rec_start = isoa->isoa_len;
				bcopy((caddr_t)isoa, rec_start + 1, isoa->isoa_len);
E 6
I 6
				bcopy((caddr_t)isoa, rec_start, new_addrlen);
E 6

				/* update offset field */
D 6
				*(opt + 1) = off + new_addrlen;
E 6
I 6
				*(opt + 1) += new_addrlen;
E 6

				IFDEBUG(D_OPTIONS)
					printf("clnp_dooptions: new option dump:\n");
					dump_buf(opt, oidx->cni_recrt_len);
				ENDDEBUG
			}
		}
	}
}

/*
 * FUNCTION:		clnp_set_opts
 *
 * PURPOSE:			Check the data mbuf passed for option sanity. If it is
 *					ok, then set the options ptr to address the data mbuf.
 *					If an options mbuf exists, free it. This implies that
 *					any old options will be lost. If data is NULL, simply
 *					free any old options.
 *
 * RETURNS:			unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnp_set_opts(options, data)
struct mbuf	**options;	/* target for option information */
struct mbuf	**data;		/* source of option information */
{
	int					error = 0;	/* error return value */
	struct clnp_optidx	dummy;		/* dummy index - not used */

	/*
	 *	remove any existing options
	 */
	if (*options != NULL) {
		m_freem(*options);
		*options = NULL;
	}

	if (*data != NULL) {
		/*
		 *	Insure that the options are reasonable.
		 *
D 7
		 *	Also, we do not support security, priority, or QOS
E 7
I 7
		 *	Also, we do not support security, priority,
E 7
		 *	nor do we allow one to send an ER option
I 7
		 *
		 *	The QOS parameter is checked for the DECBIT.
E 7
		 */
		if ((clnp_opt_sanity(*data, mtod(*data, caddr_t), (*data)->m_len, 
			&dummy) != 0) ||
				(dummy.cni_securep) ||
				(dummy.cni_priorp) ||
D 7
				(dummy.cni_qos_formatp) ||
E 7
				(dummy.cni_er_reason != ER_INVALREAS)) {
			error = EINVAL;
		} else {
			*options = *data;
			*data = NULL;	/* so caller won't free mbuf @ *data */
		}
	}
	return error;
}

/*
 * FUNCTION:		clnp_opt_sanity
 *
 * PURPOSE:			Check the options (beginning at opts for len bytes) for
 *					sanity. In addition, fill in the option index structure 
 *					in with information about each option discovered.
 *
 * RETURNS:			success (options check out) - 0
 *					failure - an ER pdu error code describing failure
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Each pointer field of the option index is filled in with
D 2
 *					the offset from the beginning of the mbuf, not the
E 2
I 2
 *					the offset from the beginning of the mbuf data, not the
E 2
 *					actual address.
 */
clnp_opt_sanity(m, opts, len, oidx)
struct mbuf 		*m;		/* mbuf options reside in */
caddr_t				opts;	/* ptr to buffer containing options */
int					len;	/* length of buffer */
struct clnp_optidx	*oidx;	/* RETURN: filled in with option idx info */
{
	u_char	opcode;			/* code of particular option */
	u_char	oplen;			/* length of a particular option */
	caddr_t	opts_end;		/* ptr to end of options */
	u_char	pad = 0, secure = 0, srcrt = 0, recrt = 0, qos = 0, prior = 0;
							/* flags for catching duplicate options */
	
	IFDEBUG(D_OPTIONS)
		printf("clnp_opt_sanity: checking %d bytes of data:\n", len);
		dump_buf(opts, len);
	ENDDEBUG

	/* clear option index field if passed */
	bzero((caddr_t)oidx, sizeof(struct clnp_optidx));

	/*
	 *	We need to indicate whether the ER option is present. This is done
	 *	by overloading the er_reason field to also indicate presense of
	 *	the option along with the option value. I would like ER_INVALREAS
	 *	to have value 0, but alas, 0 is a valid er reason...
	 */
	oidx->cni_er_reason = ER_INVALREAS;

	opts_end = opts + len;
	while (opts < opts_end) {
		/* must have at least 2 bytes per option (opcode and len) */
		if (opts + 2 > opts_end)
			return(GEN_INCOMPLETE);
		
		opcode = *opts++;
		oplen = *opts++;
		IFDEBUG(D_OPTIONS)
			printf("clnp_opt_sanity: opcode is %x and oplen %d\n",
				opcode, oplen);
			printf("clnp_opt_sanity: clnpoval_SRCRT is %x\n", CLNPOVAL_SRCRT);

				switch (opcode) {
					case CLNPOVAL_PAD: {
						printf("CLNPOVAL_PAD\n");
					} break;
					case CLNPOVAL_SECURE: {
						printf("CLNPOVAL_SECURE\n");
					} break;
					case CLNPOVAL_SRCRT: {
							printf("CLNPOVAL_SRCRT\n");
					} break;
					case CLNPOVAL_RECRT: {
						printf("CLNPOVAL_RECRT\n");
					} break;
					case CLNPOVAL_QOS: {
						printf("CLNPOVAL_QOS\n");
					} break;
					case CLNPOVAL_PRIOR: {
						printf("CLNPOVAL_PRIOR\n");
					} break;
					case CLNPOVAL_ERREAS: {
						printf("CLNPOVAL_ERREAS\n");
					} break;
					default:
						printf("UKNOWN option %x\n", opcode);
				}
		ENDDEBUG

		/* don't allow crazy length values */
		if (opts + oplen > opts_end)
			return(GEN_INCOMPLETE);

		switch (opcode) {
D 6
			case CLNPOVAL_PAD: {
E 6
I 6
			case CLNPOVAL_PAD:
E 6
				/*
				 *	Padding: increment pointer by length of padding
				 */
				if (pad++)						/* duplicate ? */
					return(GEN_DUPOPT);
				opts += oplen;
D 6
			} break;
E 6
I 6
				break;
E 6

			case CLNPOVAL_SECURE: {
				u_char	format = *opts;

				if (secure++)					/* duplicate ? */
					return(GEN_DUPOPT);
				/*
				 *	Security: high 2 bits of first octet indicate format
				 *	(00 in high bits is reserved).
				 *	Remaining bits must be 0. Remaining octets indicate
				 *	actual security
				 */
				if (((format & 0x3f) > 0) ||	/* low 6 bits set ? */
					((format & 0xc0) == 0))		/* high 2 bits zero ? */
					return(GEN_HDRSYNTAX);

D 2
				oidx->cni_securep = opts - (caddr_t)m;
E 2
I 2
				oidx->cni_securep = CLNP_OPTTOOFF(m, opts);
E 2
				oidx->cni_secure_len = oplen;
				opts += oplen;
			} break;

			case CLNPOVAL_SRCRT: {
				u_char	type, offset;	/* type of rt, offset of start */
				caddr_t	route_end;		/* address of end of route option */

				IFDEBUG(D_OPTIONS)
					printf("clnp_opt_sanity: SRC RT\n");
				ENDDEBUG

				if (srcrt++)					/* duplicate ? */
					return(GEN_DUPOPT);
				/* 
				 *	source route: There must be 2 bytes following the length
				 *	field: type and offset. The type must be either
				 *	partial route or complete route. The offset field must
				 *	be within the option. A single exception is made, however.
				 *	The offset may be 1 greater than the length. This case 
				 *	occurs when the last source route record is consumed. 
				 *	In this case, we ignore the source route option.
				 *	RAH? You should be able to set offset to 'ff' like in record
				 *	route!
				 *	Following this is a series of address fields. 
				 *	Each address field is composed of a (length, address) pair.
				 *	Insure that the offset and each address length is reasonable
				 */
				route_end = opts + oplen;

				if (opts + 2 > route_end)
					return(SRCRT_SYNTAX);

				type = *opts;
				offset = *(opts+1);


				/* type must be partial or complete */
				if (!((type == CLNPOVAL_PARTRT) || (type == CLNPOVAL_COMPRT)))
					return(SRCRT_SYNTAX);
				
D 2
				oidx->cni_srcrt_s = opts - (caddr_t)m;
E 2
I 2
				oidx->cni_srcrt_s = CLNP_OPTTOOFF(m, opts);
E 2
				oidx->cni_srcrt_len = oplen;

				opts += offset-1;	/*set opts to first addr in rt */

				/* 
				 *	Offset must be reasonable:
				 *	less than end of options, or equal to end of options
				 */
				if (opts >= route_end) {
					if (opts == route_end) {
						IFDEBUG(D_OPTIONS)
							printf("clnp_opt_sanity: end of src route info\n");
						ENDDEBUG
						break;
					} else 
						return(SRCRT_SYNTAX);
				}

				while (opts < route_end) {
					u_char	addrlen = *opts++;
					if (opts + addrlen > route_end)
						return(SRCRT_SYNTAX);
					opts += addrlen;
				}
			} break;
			case CLNPOVAL_RECRT: {
				u_char	type, offset;	/* type of rt, offset of start */
				caddr_t	record_end;		/* address of end of record option */

				if (recrt++)					/* duplicate ? */
					return(GEN_DUPOPT);
				/*
				 *	record route: after the length field, expect a
				 *	type and offset. Type must be partial or complete.
				 *	Offset indicates where to start recording. Insure it
				 *	is within the option. All ones for offset means
				 *	recording is terminated.
				 */
				record_end = opts + oplen;

D 2
				oidx->cni_recrtp = opts - (caddr_t)m;
E 2
I 2
				oidx->cni_recrtp = CLNP_OPTTOOFF(m, opts);
E 2
				oidx->cni_recrt_len = oplen;

				if (opts + 2 > record_end)
					return(GEN_INCOMPLETE);

				type = *opts;
				offset = *(opts+1);

				/* type must be partial or complete */
				if (!((type == CLNPOVAL_PARTRT) || (type == CLNPOVAL_COMPRT)))
					return(GEN_HDRSYNTAX);
				
				/* offset must be reasonable */
				if ((offset < 0xff) && (opts + offset > record_end))
					return(GEN_HDRSYNTAX);
				opts += oplen;
			} break;
			case CLNPOVAL_QOS: {
				u_char	format = *opts;

				if (qos++)					/* duplicate ? */
					return(GEN_DUPOPT);
				/*
				 *	qos: high 2 bits of first octet indicate format
				 *	(00 in high bits is reserved).
				 *	Remaining bits must be 0 (unless format indicates
				 *	globally unique qos, in which case remaining bits indicate
				 *	qos (except bit 6 which is reserved)).  Otherwise,
				 *	remaining octets indicate actual qos.
				 */
				if (((format & 0xc0) == 0) ||	/* high 2 bits zero ? */
					(((format & 0xc0) != CLNPOVAL_GLOBAL) && 
						((format & 0x3f) > 0))) /* not global,low bits used ? */
					return(GEN_HDRSYNTAX);
				
D 2
				oidx->cni_qos_formatp = opts - (caddr_t)m;
E 2
I 2
				oidx->cni_qos_formatp = CLNP_OPTTOOFF(m, opts);
E 2
				oidx->cni_qos_len = oplen;

				opts += oplen;
			} break;

			case CLNPOVAL_PRIOR: {
				if (prior++)				/* duplicate ? */
					return(GEN_DUPOPT);
				/*
				 *	priority: value must be one byte long
				 */
				if (oplen != 1)
					return(GEN_HDRSYNTAX);
				
D 2
				oidx->cni_priorp = opts - (caddr_t)m;
E 2
I 2
				oidx->cni_priorp = CLNP_OPTTOOFF(m, opts);
E 2

				opts += oplen;
			} break;

			case CLNPOVAL_ERREAS: {
				/*
				 *	er reason: value must be two bytes long
				 */
				if (oplen != 2)
					return(GEN_HDRSYNTAX);

				oidx->cni_er_reason = *opts;

				opts += oplen;
			} break;

			default: {
				IFDEBUG(D_OPTIONS)
					printf("clnp_opt_sanity: UNKNOWN OPTION 0x%x\n", opcode);
				ENDDEBUG
				return(DISC_UNSUPPOPT);
			}
		}
	}
		IFDEBUG(D_OPTIONS)
			printf("clnp_opt_sanity: return(0)\n", opcode);
		ENDDEBUG
	return(0);
}
D 10
#endif	ISO
E 10
I 10
#endif	/* ISO */
E 10
E 1
