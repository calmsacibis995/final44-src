h34643
s 00002/00002/00520
d D 8.1 93/06/10 22:45:49 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00521
d D 7.6 93/06/04 17:30:42 bostic 10 9
c prototype everything
e
s 00014/00016/00508
d D 7.5 92/06/07 19:37:28 mccanne 9 8
c update from helios -- some minor bug fixes
e
s 00005/00035/00519
d D 7.4 91/10/29 19:58:53 mccanne 8 7
c restore sccs keywords
e
s 00040/00009/00514
d D 7.3 91/10/27 21:31:02 mccanne 7 6
c silly C precedence bug fix
e
s 00154/00073/00369
d D 7.2 91/05/14 16:15:51 mccanne 6 5
c reorganized loop for better performance
c added much ugly code to catch case where data crosses an mbuf boundary
e
s 00012/00021/00430
d D 7.1 91/05/07 09:18:35 bostic 5 4
c new copyright; att/bsd/shared
e
s 00113/00012/00338
d D 1.4 91/05/05 22:54:10 mccanne 4 3
c filter now works with mbufs (buflen = 0)
e
s 00141/00106/00209
d D 1.3 91/05/02 21:27:22 mccanne 3 2
c new insn encodings
e
s 00002/00000/00313
d D 1.2 91/05/02 11:04:37 mccanne 2 1
c checkpoint before porting new insn format from horse
e
s 00313/00000/00000
d D 1.1 91/03/19 18:50:37 mccanne 1 0
c date and time created 91/03/19 18:50:37 by mccanne
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1990 The Regents of the University of California.
E 5
I 5
D 8
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
E 7
I 7
 * Copyright (c) 1990-1991 The Regents of the University of California.
E 8
I 8
/*
D 11
 * Copyright (c) 1990, 1991 Regents of the University of California.
E 8
E 7
E 5
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 5
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * This code is derived from the Stanford/CMU enet packet filter,
 * (net/enet.c) distributed as part of 4.3BSD, and code contributed
D 7
 * to Berkeley by Steven McCanne of Lawrence Berkeley Laboratory.
E 7
I 7
D 8
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence 
E 8
I 8
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence
E 8
 * Berkeley Laboratory.
E 7
 *
D 7
 * %sccs.include.redist.c%
E 7
I 7
D 8
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 *
D 7
 *	%W% (Berkeley) %G%
E 7
I 7
D 8
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 8
I 8
 *      %W% (Berkeley) %G%
E 8
E 7
 *
I 7
D 8
 *	@(#)bpf.c	7.5 (Berkeley) 7/15/91
 *
E 8
E 7
 * static char rcsid[] =
D 7
 * "@(#) $Header: bpf_filter.c,v 1.10 91/04/24 22:07:07 mccanne Locked $ (LBL)";
E 7
I 7
 * "$Header: bpf_filter.c,v 1.16 91/10/27 21:22:35 mccanne Exp $";
E 7
E 5
 */
I 7
D 8
#if !(defined(lint) || defined(KERNEL))
static char rcsid[] =
    "@(#) $Header: bpf_filter.c,v 1.16 91/10/27 21:22:35 mccanne Exp $ (LBL)";
#endif
E 8
E 7
D 5
#if !(defined(lint) || defined(KERNEL))
static char rcsid[] =
D 3
    "@(#) $Header: bpf_filter.c,v 1.9 91/01/30 18:21:54 mccanne Exp $ (LBL)";
E 3
I 3
    "@(#) $Header: bpf_filter.c,v 1.10 91/04/24 22:07:07 mccanne Locked $ (LBL)";
E 3
#endif
E 5

I 2
#include <sys/param.h>
E 2
#include <sys/types.h>
I 2
D 3
#include <protosw.h>
E 2
#include <netinet/in.h>
E 3
#include <sys/time.h>
D 10
#include <net/bpf.h>
E 10

I 6
#ifdef sun
#include <netinet/in.h>
#endif

E 6
D 7
#if defined(sparc) || defined(mips)
E 7
I 7
#if defined(sparc) || defined(mips) || defined(ibm032)
E 7
D 9
#define ALIGN
E 9
I 9
#define BPF_ALIGN
E 9
#endif

D 9
#ifndef ALIGN
#define EXTRACT_SHORT(p)	(ntohs(*(u_short *)p))
E 9
I 9
#ifndef BPF_ALIGN
#define EXTRACT_SHORT(p)	((u_short)ntohs(*(u_short *)p))
E 9
#define EXTRACT_LONG(p)		(ntohl(*(u_long *)p))
#else
#define EXTRACT_SHORT(p)\
	((u_short)\
D 6
		(*((u_char *)p+0)<<8|\
		 *((u_char *)p+1)<<0))
E 6
I 6
D 9
		(*((u_char *)(p)+0)<<8|\
		 *((u_char *)(p)+1)<<0))
E 9
I 9
		((u_short)*((u_char *)p+0)<<8|\
		 (u_short)*((u_char *)p+1)<<0))
E 9
E 6
#define EXTRACT_LONG(p)\
D 6
		(*((u_char *)p+0)<<24|\
		 *((u_char *)p+1)<<16|\
		 *((u_char *)p+2)<<8|\
		 *((u_char *)p+3)<<0)
E 6
I 6
D 9
		(*((u_char *)(p)+0)<<24|\
		 *((u_char *)(p)+1)<<16|\
		 *((u_char *)(p)+2)<<8|\
		 *((u_char *)(p)+3)<<0)
E 9
I 9
		((u_long)*((u_char *)p+0)<<24|\
		 (u_long)*((u_char *)p+1)<<16|\
		 (u_long)*((u_char *)p+2)<<8|\
		 (u_long)*((u_char *)p+3)<<0)
E 9
E 6
#endif

I 4
#ifdef KERNEL
#include <sys/mbuf.h>
#define MINDEX(m, k) \
{ \
	register int len = m->m_len; \
 \
	while (k >= len) { \
		k -= len; \
		m = m->m_next; \
		if (m == 0) \
			return 0; \
		len = m->m_len; \
	} \
}
I 6

static int
m_xword(m, k, err)
	register struct mbuf *m;
	register int k, *err;
{
	register int len;
	register u_char *cp, *np;
	register struct mbuf *m0;

	len = m->m_len;
	while (k >= len) {
		k -= len;
		m = m->m_next;
		if (m == 0)
			goto bad;
		len = m->m_len;
	}
	cp = mtod(m, u_char *) + k;
	if (len - k >= 4) {
		*err = 0;
		return EXTRACT_LONG(cp);
	}
	m0 = m->m_next;
	if (m0 == 0 || m0->m_len + len - k < 4)
		goto bad;
	*err = 0;
	np = mtod(m0, u_char *);
	switch (len - k) {

	case 1:
		return (cp[k] << 24) | (np[0] << 16) | (np[1] << 8) | np[2];

	case 2:
		return (cp[k] << 24) | (cp[k + 1] << 16) | (np[0] << 8) | 
			np[1];

	default:
		return (cp[k] << 24) | (cp[k + 1] << 16) | (cp[k + 2] << 8) |
			np[0];
	}
    bad:
	*err = 1;
	return 0;
}

static int
m_xhalf(m, k, err)
	register struct mbuf *m;
	register int k, *err;
{
	register int len;
D 7
	register u_char *cp, *np;
E 7
I 7
	register u_char *cp;
E 7
	register struct mbuf *m0;

	len = m->m_len;
	while (k >= len) {
		k -= len;
		m = m->m_next;
		if (m == 0)
			goto bad;
		len = m->m_len;
	}
	cp = mtod(m, u_char *) + k;
	if (len - k >= 2) {
		*err = 0;
		return EXTRACT_SHORT(cp);
	}
	m0 = m->m_next;
	if (m0 == 0)
		goto bad;
	*err = 0;
	return (cp[k] << 8) | mtod(m0, u_char *)[0];
 bad:
	*err = 1;
	return 0;
}
D 9


E 9
E 6
#endif

I 10
#include <net/bpf.h>
E 10
E 4
/*
D 3
 * Execute the filter program pointed to by 'pc' on the 
 * packet pointed to by 'p'.  'wirelen' is the length of actual
 * packet received by the interface.  'buflen' is the amount of
 * contiguous data.  The return value is the return value of the
 * filter program, or 0 on an error.
E 3
I 3
 * Execute the filter program starting at pc on the packet p
 * wirelen is the length of the original packet
 * buflen is the amount of data present
E 3
 */
u_int
bpf_filter(pc, p, wirelen, buflen)
	register struct bpf_insn *pc;
	register u_char *p;
	u_int wirelen;
D 3
	u_int buflen;
E 3
I 3
	register u_int buflen;
E 3
{
D 3
#define	JUMP(delta)	pc += (delta)
#define	BR(cond)	JUMP((cond) ? pc->jt : pc->jf)

E 3
D 9
	register long A, X;
E 9
I 9
	register u_long A, X;
E 9
I 3
	register int k;
E 3
	long mem[BPF_MEMWORDS];

	if (pc == 0)
		/*
		 * No filter means accept all.
		 */
D 3
		return 1;

E 3
I 3
		return (u_int)-1;
E 3
#ifdef lint
	A = 0;
	X = 0;
#endif
D 3

E 3
I 3
	--pc;
E 3
	while (1) {
D 3

E 3
I 3
		++pc;
E 3
		switch (pc->code) {

		default:
#ifdef KERNEL
			return 0;
#else
			abort();
#endif			
D 3
		case RetOp:
E 3
I 3
		case BPF_RET|BPF_K:
E 3
			return (u_int)pc->k;

D 3
		case RetAOp:
E 3
I 3
		case BPF_RET|BPF_A:
E 3
			return (u_int)A;

D 3
		case LdOp:
			if (pc->k + sizeof(long) > buflen)
E 3
I 3
		case BPF_LD|BPF_W|BPF_ABS:
			k = pc->k;
D 4
			if (k + sizeof(long) > buflen)
E 4
I 4
			if (k + sizeof(long) > buflen) {
#ifdef KERNEL
D 6
				register struct mbuf *m;
E 6
I 6
				int merr;
E 6

				if (buflen != 0)
					return 0;
D 6
				m = (struct mbuf *)p;
				MINDEX(m, k);
				A = EXTRACT_LONG(mtod(m, char *) + k);
				break;
E 6
I 6
				A = m_xword((struct mbuf *)p, k, &merr);
				if (merr != 0)
					return 0;
				continue;
E 6
#else
E 4
E 3
				return 0;
I 4
#endif
			}
E 4
D 3
			A = EXTRACT_LONG(&p[pc->k]);
E 3
I 3
D 9
#ifdef ALIGN
E 9
I 9
#ifdef BPF_ALIGN
E 9
			if (((int)(p + k) & 3) != 0)
				A = EXTRACT_LONG(&p[k]);
			else
#endif
D 9
				A = *(long *)(p + k);
E 9
I 9
				A = ntohl(*(long *)(p + k));
E 9
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LdHOp:
			if (pc->k + sizeof(short) > buflen)
E 3
I 3
		case BPF_LD|BPF_H|BPF_ABS:
			k = pc->k;
D 4
			if (k + sizeof(short) > buflen)
E 4
I 4
			if (k + sizeof(short) > buflen) {
#ifdef KERNEL
D 6
				register struct mbuf *m;
E 6
I 6
				int merr;
E 6

				if (buflen != 0)
					return 0;
D 6
				m = (struct mbuf *)p;
				MINDEX(m, k);
				A = EXTRACT_SHORT(mtod(m, char *) + k);
				break;
E 6
I 6
				A = m_xhalf((struct mbuf *)p, k, &merr);
				continue;
E 6
#else
E 4
E 3
				return 0;
I 4
#endif
			}
E 4
D 3
			A = EXTRACT_SHORT(&p[pc->k]);
E 3
I 3
			A = EXTRACT_SHORT(&p[k]);
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LdBOp:
			if (pc->k >= buflen)
E 3
I 3
		case BPF_LD|BPF_B|BPF_ABS:
			k = pc->k;
D 4
			if (k >= buflen)
E 4
I 4
			if (k >= buflen) {
#ifdef KERNEL
				register struct mbuf *m;

				if (buflen != 0)
					return 0;
				m = (struct mbuf *)p;
				MINDEX(m, k);
D 6
				A = mtod(m, char *)[k];
				break;
E 6
I 6
				A = mtod(m, u_char *)[k];
				continue;
E 6
#else
E 4
E 3
				return 0;
I 4
#endif
			}
E 4
D 3
			A = p[pc->k];
E 3
I 3
			A = p[k];
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LdLenOp:
E 3
I 3
		case BPF_LD|BPF_W|BPF_LEN:
E 3
			A = wirelen;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case ILdOp:
			if (X + pc->k + sizeof(long) > buflen)
E 3
I 3
		case BPF_LDX|BPF_W|BPF_LEN:
			X = wirelen;
D 6
			break;
E 6
I 6
			continue;
E 6

		case BPF_LD|BPF_W|BPF_IND:
			k = X + pc->k;
D 4
			if (k + sizeof(long) > buflen)
E 4
I 4
			if (k + sizeof(long) > buflen) {
#ifdef KERNEL
D 6
				register struct mbuf *m;
E 6
I 6
				int merr;
E 6

				if (buflen != 0)
					return 0;
D 6
				m = (struct mbuf *)p;
				MINDEX(m, k);
				A = EXTRACT_LONG(mtod(m, char *) + k);
				break;
E 6
I 6
				A = m_xword((struct mbuf *)p, k, &merr);
				if (merr != 0)
					return 0;
				continue;
E 6
#else
E 4
E 3
				return 0;
I 4
#endif
			}
E 4
D 3
			A = EXTRACT_LONG(&p[X + pc->k]);
E 3
I 3
D 9
#ifdef ALIGN
E 9
I 9
#ifdef BPF_ALIGN
E 9
			if (((int)(p + k) & 3) != 0)
				A = EXTRACT_LONG(&p[k]);
			else
#endif
D 9
				A = *(long *)(p + k);
E 9
I 9
				A = ntohl(*(long *)(p + k));
E 9
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case ILdHOp:
			if (X + pc->k + sizeof(short) > buflen)
E 3
I 3
		case BPF_LD|BPF_H|BPF_IND:
			k = X + pc->k;
D 4
			if (k + sizeof(short) > buflen)
E 4
I 4
			if (k + sizeof(short) > buflen) {
#ifdef KERNEL
D 6
				register struct mbuf *m;
E 6
I 6
				int merr;
E 6

				if (buflen != 0)
					return 0;
D 6
				m = (struct mbuf *)p;
				MINDEX(m, k);
				A = EXTRACT_SHORT(mtod(m, char *) + k);
				break;
E 6
I 6
				A = m_xhalf((struct mbuf *)p, k, &merr);
				if (merr != 0)
					return 0;
				continue;
E 6
#else
E 4
E 3
				return 0;
I 4
#endif
			}
E 4
D 3
			A = EXTRACT_SHORT(&p[X + pc->k]);
E 3
I 3
			A = EXTRACT_SHORT(&p[k]);
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case ILdBOp:
			if (X + pc->k >= buflen)
E 3
I 3
		case BPF_LD|BPF_B|BPF_IND:
			k = X + pc->k;
D 4
			if (k >= buflen)
E 4
I 4
			if (k >= buflen) {
#ifdef KERNEL
				register struct mbuf *m;

				if (buflen != 0)
					return 0;
				m = (struct mbuf *)p;
				MINDEX(m, k);
				A = mtod(m, char *)[k];
D 6
				break;
E 6
I 6
				continue;
E 6
#else
E 4
E 3
				return 0;
I 4
#endif
			}
E 4
D 3
			A = p[X + pc->k];
E 3
I 3
			A = p[k];
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

I 4
		case BPF_LDX|BPF_MSH|BPF_B:
			k = pc->k;
			if (k >= buflen) {
#ifdef KERNEL
				register struct mbuf *m;

				if (buflen != 0)
					return 0;
				m = (struct mbuf *)p;
				MINDEX(m, k);
				X = (mtod(m, char *)[k] & 0xf) << 2;
D 6
				break;
E 6
I 6
				continue;
E 6
#else
				return 0;
#endif
			}
			X = (p[pc->k] & 0xf) << 2;
D 6
			break;
E 6
I 6
			continue;
E 6

E 4
D 3
		case LdIOp:
E 3
I 3
		case BPF_LD|BPF_IMM:
E 3
			A = pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LdXIOp:
E 3
I 3
		case BPF_LDX|BPF_IMM:
E 3
			X = pc->k;
D 4
			break;

D 3
		case LdxmsOp:
E 3
I 3
		case BPF_LDX|BPF_MSH|BPF_B:
E 3
			if (pc->k >= buflen)
				return 0;
			X = (p[pc->k] & 0xf) << 2;
E 4
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case TaxOp:
			X = A;
E 3
I 3
		case BPF_LD|BPF_MEM:
			A = mem[pc->k];
E 3
D 6
			break;
E 6
I 6
			continue;
E 6
D 3

		case TxaOp:
			A = X;
E 3
I 3
			
		case BPF_LDX|BPF_MEM:
			X = mem[pc->k];
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case StmOp:
E 3
I 3
		case BPF_ST:
E 3
			mem[pc->k] = A;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LdmOp:
			A = mem[pc->k];
			break;
			
		case StmXOp:
E 3
I 3
		case BPF_STX:
E 3
			mem[pc->k] = X;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LdmXOp:
			X = mem[pc->k];
E 3
I 3
		case BPF_JMP|BPF_JA:
			pc += pc->k;
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case NopOp:
E 3
I 3
		case BPF_JMP|BPF_JGT|BPF_K:
			pc += (A > pc->k) ? pc->jt : pc->jf;
E 3
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case GTOp:
			BR(A > pc->k);
			continue;
E 3
I 3
		case BPF_JMP|BPF_JGE|BPF_K:
			pc += (A >= pc->k) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6
E 3

D 3
		case GEOp:
			BR(A >= pc->k);
			continue;
E 3
I 3
		case BPF_JMP|BPF_JEQ|BPF_K:
			pc += (A == pc->k) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6
E 3

D 3
		case EQOp:
			BR(A == pc->k);
			continue;
E 3
I 3
		case BPF_JMP|BPF_JSET|BPF_K:
			pc += (A & pc->k) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6
E 3

D 3
		case AddXOp:
E 3
I 3
		case BPF_JMP|BPF_JGT|BPF_X:
			pc += (A > X) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6

		case BPF_JMP|BPF_JGE|BPF_X:
			pc += (A >= X) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6

		case BPF_JMP|BPF_JEQ|BPF_X:
			pc += (A == X) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6

		case BPF_JMP|BPF_JSET|BPF_X:
			pc += (A & X) ? pc->jt : pc->jf;
D 6
			break;
E 6
I 6
			continue;
E 6

		case BPF_ALU|BPF_ADD|BPF_X:
E 3
			A += X;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case SubXOp:
E 3
I 3
		case BPF_ALU|BPF_SUB|BPF_X:
E 3
			A -= X;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case MulXOp:
E 3
I 3
		case BPF_ALU|BPF_MUL|BPF_X:
E 3
			A *= X;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case DivXOp:
E 3
I 3
		case BPF_ALU|BPF_DIV|BPF_X:
E 3
			if (X == 0)
				return 0;
			A /= X;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case AndXOp:
E 3
I 3
		case BPF_ALU|BPF_AND|BPF_X:
E 3
			A &= X;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case OrXOp:
E 3
I 3
		case BPF_ALU|BPF_OR|BPF_X:
E 3
			A |= X;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LshXOp:
E 3
I 3
		case BPF_ALU|BPF_LSH|BPF_X:
E 3
			A <<= X;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case RshXOp:
E 3
I 3
		case BPF_ALU|BPF_RSH|BPF_X:
E 3
			A >>= X;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case AddIOp:
E 3
I 3
		case BPF_ALU|BPF_ADD|BPF_K:
E 3
			A += pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case SubIOp:
E 3
I 3
		case BPF_ALU|BPF_SUB|BPF_K:
E 3
			A -= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case MulIOp:
E 3
I 3
		case BPF_ALU|BPF_MUL|BPF_K:
E 3
			A *= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case DivIOp:
			if (pc->k == 0)
				return 0;
E 3
I 3
		case BPF_ALU|BPF_DIV|BPF_K:
E 3
			A /= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case AndIOp:
E 3
I 3
		case BPF_ALU|BPF_AND|BPF_K:
E 3
			A &= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6
			
D 3
		case OrIOp:
E 3
I 3
		case BPF_ALU|BPF_OR|BPF_K:
E 3
			A |= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case LshIOp:
E 3
I 3
		case BPF_ALU|BPF_LSH|BPF_K:
E 3
			A <<= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case RshIOp:
E 3
I 3
		case BPF_ALU|BPF_RSH|BPF_K:
E 3
			A >>= pc->k;
D 6
			break;
E 6
I 6
			continue;
E 6

D 3
		case NegOp:
E 3
I 3
		case BPF_ALU|BPF_NEG:
E 3
			A = -A;
D 6
			break;
E 6
I 6
			continue;
E 6
I 3

		case BPF_MISC|BPF_TAX:
			X = A;
D 6
			break;
E 6
I 6
			continue;
E 6

		case BPF_MISC|BPF_TXA:
			A = X;
D 6
			break;
E 6
I 6
			continue;
E 6
E 3
		}
D 3
		++pc;
E 3
	}
}

#ifdef KERNEL
/*
 * Return true if the 'fcode' is a valid filter program.
 * The constraints are that each jump be forward and to a valid
 * code.  The code must terminate with either an accept or reject. 
 * 'valid' is an array for use by the routine (it must be at least
 * 'len' bytes long).  
 *
 * The kernel needs to be able to verify an application's filter code.
 * Otherwise, a bogus program could easily crash the system.
 */
int
D 3
bpf_validate(fcode, len)
	struct bpf_insn *fcode;
E 3
I 3
bpf_validate(f, len)
	struct bpf_insn *f;
E 3
	int len;
{
D 3
	struct bpf_insn *p;
	int i;
E 3
I 3
	register int i;
	register struct bpf_insn *p;
E 3

D 3
	p = fcode;
	for (i = 0; i < len; ++p, ++i)
		if (!BPF_VALIDCODE(p->code))
			return 0;
	p = fcode;
	for (i = 0; i < len; ++p, ++i) {
E 3
I 3
	for (i = 0; i < len; ++i) {
E 3
		/*
		 * Check that that jumps are forward, and within 
		 * the code block.
		 */
D 3
		if (BPF_ISJUMP(p->code) &&
		    (p->jt <= 0 || i + p->jt >= len ||
		     p->jf <= 0 || i + p->jf >= len))
			return 0;
E 3
I 3
		p = &f[i];
		if (BPF_CLASS(p->code) == BPF_JMP) {
			register int from = i + 1;

			if (BPF_OP(p->code) == BPF_JA) {
				if (from + p->k >= len)
					return 0;
			}
			else if (from + p->jt >= len || from + p->jf >= len)
				return 0;
		}
E 3
		/*
		 * Check that memory operations use valid addresses.
		 */
D 3
		switch (p->code) {
		case StmOp:
		case StmXOp:
		case LdmOp:
		case LdmXOp:
			if (p->k >= BPF_MEMWORDS || p->k < 0)
				return 0;
		}
E 3
I 3
		if ((BPF_CLASS(p->code) == BPF_ST ||
		     (BPF_CLASS(p->code) == BPF_LD && 
		      (p->code & 0xe0) == BPF_MEM)) &&
		    (p->k >= BPF_MEMWORDS || p->k < 0))
			return 0;
		/*
		 * Check for constant division by 0.
		 */
D 7
		if (p->code == BPF_ALU|BPF_DIV|BPF_K && p->k == 0)
			return;
E 7
I 7
		if (p->code == (BPF_ALU|BPF_DIV|BPF_K) && p->k == 0)
			return 0;
E 7
E 3
	}
D 3
	return BPF_ISLEAF(fcode[len - 1].code);
E 3
I 3
	return BPF_CLASS(f[len - 1].code) == BPF_RET;
E 3
}
#endif
E 1
