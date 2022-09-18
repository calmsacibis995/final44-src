h30957
s 00001/00001/00225
d D 8.2 95/01/09 17:54:19 cgd 11 10
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00002/00002/00224
d D 8.1 93/06/10 22:39:45 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00004/00214
d D 7.5 93/06/04 17:30:38 bostic 9 8
c prototype everything
e
s 00023/00001/00195
d D 7.4 92/06/07 19:32:40 mccanne 8 7
c update from helios -- added BIOCVERSION
e
s 00005/00031/00191
d D 7.3 91/10/29 19:58:52 mccanne 7 6
c restore sccs keywords
e
s 00038/00009/00184
d D 7.2 91/10/27 21:30:09 mccanne 6 5
c add DLT_NULL; BIOCGFLEN no longer exists
e
s 00008/00019/00185
d D 7.1 91/05/07 09:18:34 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00011/00201
d D 1.4 91/05/05 22:55:15 mccanne 4 3
c nuked bpf_devp struct; BIOCDEVP now BIOCGDLT
e
s 00057/00023/00155
d D 1.3 91/05/02 21:26:58 mccanne 3 2
c merged in new insn encodings
e
s 00003/00000/00175
d D 1.2 91/05/02 11:04:09 mccanne 2 1
c checkpoint before porting new insn format from horse
e
s 00175/00000/00000
d D 1.1 91/03/22 16:01:51 mccanne 1 0
c date and time created 91/03/22 16:01:51 by mccanne
e
u
U
t
T
I 1
D 5
/*
E 5
I 5
D 7
/*-
E 5
D 6
 * Copyright (c) 1990 The Regents of the University of California.
E 6
I 6
 * Copyright (c) 1990-1991 The Regents of the University of California.
E 7
I 7
/*
D 10
 * Copyright (c) 1990, 1991 Regents of the University of California.
E 7
E 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
D 6
 * to Berkeley by Steven McCanne of Lawrence Berkeley Laboratory.
E 6
I 6
D 7
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence 
E 7
I 7
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence
E 7
 * Berkeley Laboratory.
E 6
E 5
 *
D 3
 * @(#) $Header: bpf.h,v 1.19 91/01/30 18:20:21 mccanne Exp $ (LBL)
E 3
I 3
D 5
 * @(#) $Header: bpf.h,v 1.20 91/04/24 22:06:24 mccanne Locked $ (LBL)
E 5
I 5
D 6
 * %sccs.include.redist.c%
E 6
I 6
D 7
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
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
E 3
 *
D 5
 * This code is derived from the Stanford/CMU enet packet filter,
 * (net/enet.h) distributed with 4.3BSD Unix.
E 5
I 5
D 6
 *	%W% (Berkeley) %G%
E 6
I 6
D 7
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
E 6
 *
D 6
 * @(#) $Header: bpf.h,v 1.20 91/04/24 22:06:24 mccanne Locked $ (LBL)
E 6
I 6
 *      @(#)bpf.h       7.1 (Berkeley) 5/7/91
E 7
I 7
 *      %W% (Berkeley) %G%
E 7
 *
 * @(#) $Header: bpf.h,v 1.24 91/10/27 21:22:32 mccanne Exp $ (LBL)
E 6
E 5
 */

/*
 * Alignment macros.  BPF_WORDALIGN rounds up to the next 
 * even multiple of BPF_ALIGNMENT. 
 */
#define BPF_ALIGNMENT sizeof(long)
#define BPF_WORDALIGN(x) (((x)+(BPF_ALIGNMENT-1))&~(BPF_ALIGNMENT-1))

I 2
#define BPF_MAXINSNS 512
#define BPF_MAXBUFSIZE 0x8000
I 8
#define BPF_MINBUFSIZE 32
E 8

E 2
/*
 *  Structure for BIOCSETF.
 */
struct bpf_program {
	u_int bf_len;
	struct bpf_insn *bf_insns;
};
 
/*
 * Struct returned by BIOCGSTATS.
 */
struct bpf_stat {
	u_int bs_recv;		/* number of packets received */
	u_int bs_drop;		/* number of packets dropped */
};

/*
I 8
 * Struct return by BIOCVERSION.  This represents the version number of 
 * the filter language described by the instruction encodings below.
 * bpf understands a program iff kernel_major == filter_major &&
 * kernel_minor >= filter_minor, that is, if the value returned by the
 * running kernel has the same major number and a minor number equal
 * equal to or less than the filter being downloaded.  Otherwise, the
 * results are undefined, meaning an error may be returned or packets
 * may be accepted haphazardly.
 * It has nothing to do with the source code version.
 */
struct bpf_version {
	u_short bv_major;
	u_short bv_minor;
};
/* Current version number. */
#define BPF_MAJOR_VERSION 1
#define BPF_MINOR_VERSION 1

/*
E 8
 * BPF ioctls
 *
 * The first set is for compatibility with Sun's pcc style
 * header files.  If your using gcc, we assume that you
 * have run fixincludes so the latter set should work.
 */
D 6
#if defined(sun) && !defined(__GNUC__)
#define	BIOCGFLEN	_IOR(B,101, u_int)
#define	BIOCGBLEN	_IOR(B,102, u_int)
E 6
I 6
#if (defined(sun) || defined(ibm032)) && !defined(__GNUC__)
#define	BIOCGBLEN	_IOR(B,102, u_int)
#define	BIOCSBLEN	_IOWR(B,102, u_int)
E 6
#define	BIOCSETF	_IOW(B,103, struct bpf_program)
#define	BIOCFLUSH	_IO(B,104)
#define BIOCPROMISC	_IO(B,105)
D 4
#define	BIOCDEVP	_IOR(B,106, struct bpf_devp)
E 4
I 4
#define	BIOCGDLT	_IOR(B,106, u_int)
E 4
#define BIOCGETIF	_IOR(B,107, struct ifreq)
#define BIOCSETIF	_IOW(B,108, struct ifreq)
#define BIOCSRTIMEOUT	_IOW(B,109, struct timeval)
#define BIOCGRTIMEOUT	_IOR(B,110, struct timeval)
#define BIOCGSTATS	_IOR(B,111, struct bpf_stat)
#define BIOCIMMEDIATE	_IOW(B,112, u_int)
I 8
#define BIOCVERSION	_IOR(B,113, struct bpf_version)
E 8
#else
D 6
#define	BIOCGFLEN	_IOR('B',101, u_int)
E 6
#define	BIOCGBLEN	_IOR('B',102, u_int)
I 6
#define	BIOCSBLEN	_IOWR('B',102, u_int)
E 6
#define	BIOCSETF	_IOW('B',103, struct bpf_program)
#define	BIOCFLUSH	_IO('B',104)
#define BIOCPROMISC	_IO('B',105)
D 4
#define	BIOCDEVP	_IOR('B',106, struct bpf_devp)
E 4
I 4
#define	BIOCGDLT	_IOR('B',106, u_int)
E 4
#define BIOCGETIF	_IOR('B',107, struct ifreq)
#define BIOCSETIF	_IOW('B',108, struct ifreq)
#define BIOCSRTIMEOUT	_IOW('B',109, struct timeval)
#define BIOCGRTIMEOUT	_IOR('B',110, struct timeval)
#define BIOCGSTATS	_IOR('B',111, struct bpf_stat)
#define BIOCIMMEDIATE	_IOW('B',112, u_int)
I 8
#define BIOCVERSION	_IOR('B',113, struct bpf_version)
E 8
#endif

/*
D 4
 * The device parameters of a network interface.
 */
struct bpf_devp {
	u_short	bdev_type;	/* data link layer type, codes below */
	u_short	bdev_hdrlen;	/* length of a hardware packet header */
};

/*
E 4
 * Structure prepended to each packet.
 */
struct bpf_hdr {
	struct timeval	bh_tstamp;	/* time stamp */
	u_long		bh_caplen;	/* length of captured portion */
	u_long		bh_datalen;	/* original length of packet */
	u_short		bh_hdrlen;	/* length of bpf header (this struct
					   plus alignment padding) */
};
/*
 * Because the structure above is not a multiple of 4 bytes, some compilers
 * will insist on inserting padding; hence, sizeof(struct bpf_hdr) won't work.
 * Only the kernel needs to know about it; applications use bh_hdrlen.
 */
#ifdef KERNEL
#define SIZEOF_BPF_HDR 18
#endif

/*
 * Data-link level type codes.
D 4
 * Currently, only ENDT_10MB and DLT_SLIP are supported.
E 4
I 4
 * Currently, only DLT_EN10MB and DLT_SLIP are supported.
E 4
 */
I 6
#define DLT_NULL	0	/* no link-layer encapsulation */
E 6
#define DLT_EN10MB	1	/* Ethernet (10Mb) */
#define DLT_EN3MB	2	/* Experimental Ethernet (3Mb) */
#define DLT_AX25	3	/* Amateur Radio AX.25 */
#define DLT_PRONET	4	/* Proteon ProNET Token Ring */
#define DLT_CHAOS	5	/* Chaos */
#define DLT_IEEE802	6	/* IEEE 802 Networks */
#define DLT_ARCNET	7	/* ARCNET */
#define DLT_SLIP	8	/* Serial Line IP */
#define DLT_PPP		9	/* Point-to-point Protocol */
#define DLT_FDDI	10	/* FDDI */

/*
D 3
 * The opcodes are defined as an enumeration.  However, they are stored
 * explicitly in the code array as 'u_short'.
E 3
I 3
 * The instruction encondings.
E 3
 */
D 3
enum bpf_code {
#define OPDEF(opcode, opstr) opcode ,
#include <net/bpfcodes.h>
#undef OPDEF
	/* this idea is borrowed from gcc */
	LAST_AND_UNUSED_ENUM
};
E 3
I 3
D 8
/* classes <2:0> */
E 8
I 8
/* instruction classes */
E 8
#define BPF_CLASS(code) ((code) & 0x07)
#define		BPF_LD		0x00
#define		BPF_LDX		0x01
#define		BPF_ST		0x02
#define		BPF_STX		0x03
#define		BPF_ALU		0x04
#define		BPF_JMP		0x05
#define		BPF_RET		0x06
#define		BPF_MISC	0x07
E 3

D 3
#define BPF_NCODES ((unsigned)LAST_AND_UNUSED_ENUM)
#define BPF_VALIDCODE(code) ((unsigned)(code) < BPF_NCODES)
E 3
I 3
/* ld/ldx fields */
#define BPF_SIZE(code)	((code) & 0x18)
#define		BPF_W		0x00
#define		BPF_H		0x08
#define		BPF_B		0x10
#define BPF_MODE(code)	((code) & 0xe0)
#define		BPF_IMM 	0x00
#define		BPF_ABS		0x20
#define		BPF_IND		0x40
#define		BPF_MEM		0x60
#define		BPF_LEN		0x80
#define		BPF_MSH		0xa0
E 3

I 3
/* alu/jmp fields */
#define BPF_OP(code)	((code) & 0xf0)
#define		BPF_ADD		0x00
#define		BPF_SUB		0x10
#define		BPF_MUL		0x20
#define		BPF_DIV		0x30
#define		BPF_OR		0x40
#define		BPF_AND		0x50
#define		BPF_LSH		0x60
#define		BPF_RSH		0x70
#define		BPF_NEG		0x80
#define		BPF_JA		0x00
#define		BPF_JEQ		0x10
#define		BPF_JGT		0x20
#define		BPF_JGE		0x30
#define		BPF_JSET	0x40
#define BPF_SRC(code)	((code) & 0x08)
#define		BPF_K		0x00
#define		BPF_X		0x08

/* ret - BPF_K and BPF_X also apply */
#define BPF_RVAL(code)	((code) & 0x18)
#define		BPF_A		0x10

/* misc */
#define BPF_MISCOP(code) ((code) & 0xf8)
#define		BPF_TAX		0x00
#define		BPF_TXA		0x80

E 3
/*
 * The instruction data structure.
 */
struct bpf_insn {
	u_short	code;
	u_char 	jt;
	u_char 	jf;
	long	k;
};

/*
D 3
 * Macros for array initializers.
E 3
I 3
 * Macros for insn array initializers.
E 3
 */
D 3
#define BPF_STMT(code, k) { (u_short)code, 0, 0, k }
#define BPF_JUMP(code, k, jt, jf) { (u_short)code, jt, jf, k }
E 3
I 3
#define BPF_STMT(code, k) { (u_short)(code), 0, 0, k }
#define BPF_JUMP(code, k, jt, jf) { (u_short)(code), jt, jf, k }
E 3

#ifdef KERNEL
D 9
extern u_int bpf_filter();
extern void bpfattach();
extern void bpf_tap();
extern void bpf_mtap();
E 9
I 9
int	 bpf_validate __P((struct bpf_insn *, int));
int	 bpfopen __P((dev_t, int));
int	 bpfclose __P((dev_t, int));
int	 bpfread __P((dev_t, struct uio *));
int	 bpfwrite __P((dev_t, struct uio *));
D 11
int	 bpfioctl __P((dev_t, int, caddr_t, int));
E 11
I 11
int	 bpfioctl __P((dev_t, u_long, caddr_t, int));
E 11
int	 bpf_select __P((dev_t, int, struct proc *));
void	 bpf_tap __P((caddr_t, u_char *, u_int));
void	 bpf_mtap __P((caddr_t, struct mbuf *));
void	 bpfattach __P((caddr_t *, struct ifnet *, u_int, u_int));
void	 bpfilterattach __P((int));
u_int	 bpf_filter __P((struct bpf_insn *, u_char *, u_int, u_int));
E 9
#endif

/*
D 3
 * These two macros are sensitive to the order in which the
 * opcodes appear in bpfcodes.h.
 */
#define BPF_ISJUMP(code) ((unsigned)(code) <= (unsigned)EQOp)
#define BPF_ISLEAF(code) ((unsigned)(code) >= (unsigned)RetOp)

/*
 * Number of scratch memory words.
E 3
I 3
 * Number of scratch memory words (for BPF_LD|BPF_MEM and BPF_ST).
E 3
 */
#define BPF_MEMWORDS 16
I 6

E 6
E 1
