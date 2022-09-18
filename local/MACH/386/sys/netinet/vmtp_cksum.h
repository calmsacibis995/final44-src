/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmtp_cksum.h,v $
 * Revision 2.3  89/03/09  20:48:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:09  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * $ Header: vmtp_cksum.h,v 2.1 87/08/14 15:43:07 mrt Exp $
 */

/*
 * 	vmtp_cksum.h	
 *	Written by Erik Nordmark
 */

/* Checksum handling */

#define VMTP_CKSUMLEN	sizeof(u_long)

/* 
 * Note that the m_len in the last mbuf should be the length of the data i.e.
 * with the space for the checksum included and the checksum length should be
 * included in the length specified for vmtp_cksum.
 */

#define vh_checksum(m) 	(u_long *)(mtod(m, caddr_t)+m->m_len-VMTP_CKSUMLEN)
	/* use on last mbuf of packet - even if no segment */
	/* NOTE: checksum must be completely within that mbuf! */


/* for gathering the parts of a checksum that span mbuf boundaries */
union vmtp_cksumconv {
	u_long	total;
	struct { u_short 	first, second; } h;
	struct { u_char	q1st, q2nd, q3rd, q4th; } q;
};


#define vmtp_readcksum(m,off,len,result)			\
{								\
	register int length = len+off;				\
	register struct mbuf *mm = m;				\
								\
	while (length >= mm->m_len + VMTP_CKSUMLEN) {		\
		length -= mm->m_len;				\
		mm = mm->m_next;				\
	}							\
	if (length == mm->m_len) {				\
		result = *vh_checksum(mm);			\
	} else {						\
		register struct mbuf *nn = mm->m_next;		\
		union vmtp_cksumconv conv;			\
								\
		switch (length - mm->m_len) {			\
			case 1: { 				\
				conv.h.first =				\
				    *(u_short *)(mtod(mm, caddr_t)+m->m_len-3);\
				conv.q.q3rd = *(mtod(mm, caddr_t)+m->m_len-1);\
				conv.q.q4th = *(mtod(nn, caddr_t));	\
				break;					\
				}					\
			case 2: { 					\
				conv.h.first =				\
				    *(u_short *)(mtod(mm, caddr_t)+m->m_len-2);\
				conv.h.second =				\
					*(u_short *)(mtod(nn, caddr_t));\
				break;					\
				}					\
			case 3: { 					\
				conv.q.q1st = *(mtod(mm, caddr_t)+m->m_len-1);\
				conv.q.q2nd = *(mtod(nn, caddr_t));	\
				conv.h.second =				\
					*(u_short *)(mtod(nn, caddr_t)+1);\
				break;					\
				}					\
			default: { printf("vmtp_readcksum - out of data\n");}\
		}						\
		result = conv.total;				\
	}							\
}


/*
 * Pad the packet to be sent with zero's to get a multiple of 4 bytes.
 * Should be done before the checksum is computed!
 *
 * Note: the correctness of this relies on that m_get and mclget always 
 * allocates a multiple 4 bytes i.e. it's possible to pad with zeros without
 * going beyond the end of the mbuf or cluster!
 */

#define vmtp_padlength(m, len)						\
{									\
	if (len & 0x3) {						\
		/* have to pad */					\
		register struct mbuf *mm = m;				\
									\
		while (mm->m_next)					\
			mm = mm->m_next;				\
		switch (len & 3) {					\
			case 1: {					\
				*(mtod(mm, caddr_t)+mm->m_len) = (u_char)0; \
				*(u_short *)(mtod(mm, caddr_t)+mm->m_len + 1) =\
					(u_short)0;			\
				mm->m_len += 3;				\
				len += 3;				\
				break;					\
			}						\
			case 2: {					\
				*(u_short *)(mtod(mm, caddr_t)+mm->m_len) = \
					(u_short)0;			\
				mm->m_len += 2;				\
				len += 2;				\
				break;					\
			}						\
			case 3: {					\
				*(mtod(mm, caddr_t)+mm->m_len) = (u_char)0; \
				mm->m_len += 3;				\
				len += 3;				\
				break;					\
			}						\
			default: panic("vmtp_padlength()");		\
		}							\
	}								\
}

