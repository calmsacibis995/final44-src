h20897
s 00002/00002/00184
d D 8.1 93/06/10 21:44:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00184
d D 7.4 92/12/27 09:25:39 hibler 4 3
c new stack alignment
e
s 00055/00001/00130
d D 7.3 92/06/05 15:29:24 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00130
d D 7.2 90/11/02 16:29:17 mckusick 2 1
c update identifier from Utah
e
s 00131/00000/00000
d D 7.1 90/05/08 17:51:16 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: frame.h 1.6 89/02/24$
E 2
I 2
D 3
 * from: Utah $Hdr: frame.h 1.1 90/07/09$
E 3
I 3
D 4
 * from: Utah $Hdr: frame.h 1.7 91/03/25$
E 4
I 4
 * from: Utah $Hdr: frame.h 1.8 92/12/20$
E 4
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

struct frame {
	int	f_regs[16];
I 4
	short	f_pad;
E 4
	short	f_stackadj;
	u_short	f_sr;
	u_int	f_pc;
	u_short	f_format:4,
		f_vector:12;
	union F_u {
		struct fmt2 {
			u_int	f_iaddr;
		} F_fmt2;

I 3
		struct fmt3 {
			u_int	f_ea;
		} F_fmt3;

		struct fmt7 {
			u_int	f_ea;
			u_short	f_ssw;
			u_short	f_wb3s, f_wb2s, f_wb1s;
			u_int	f_fa;
			u_int	f_wb3a, f_wb3d;
			u_int	f_wb2a, f_wb2d;
			u_int	f_wb1a, f_wb1d;
#define				f_pd0 f_wb1d
			u_int	f_pd1, f_pd2, f_pd3;
		} F_fmt7;

E 3
		struct fmt9 {
			u_int	f_iaddr;
			u_short	f_iregs[4];
		} F_fmt9;

		struct fmtA {
			u_short	f_ir0;
			u_short	f_ssw;
			u_short	f_ipsc;
			u_short	f_ipsb;
			u_int	f_dcfa;
			u_short	f_ir1, f_ir2;
			u_int	f_dob;
			u_short	f_ir3, f_ir4;
		} F_fmtA;

		struct fmtB {
			u_short	f_ir0;
			u_short	f_ssw;
			u_short	f_ipsc;
			u_short	f_ipsb;
			u_int	f_dcfa;
			u_short	f_ir1, f_ir2;
			u_int	f_dob;
			u_short	f_ir3, f_ir4;
			u_short	f_ir5, f_ir6;
			u_int	f_sba;
			u_short	f_ir7, f_ir8;
			u_int	f_dib;
			u_short	f_iregs[22];
		} F_fmtB;
	} F_u;
};

#define	f_fmt2		F_u.F_fmt2
I 3
#define	f_fmt3		F_u.F_fmt3
#define	f_fmt7		F_u.F_fmt7
#define	f_fmt9		F_u.F_fmt9
E 3
#define	f_fmtA		F_u.F_fmtA
#define	f_fmtB		F_u.F_fmtB

/* common frame size */
#define	CFSIZE		(sizeof(struct frame) - sizeof(union F_u))
#define	NFMTSIZE	8

#define	FMT0		0x0
#define	FMT1		0x1
#define	FMT2		0x2
I 3
#define	FMT3		0x3
#define	FMT7		0x7
E 3
#define	FMT9		0x9
#define	FMTA		0xA
#define	FMTB		0xB

/* frame specific info sizes */
#define	FMT0SIZE	0
#define	FMT1SIZE	0
#define	FMT2SIZE	sizeof(struct fmt2)
I 3
#define	FMT3SIZE	sizeof(struct fmt3)
#define	FMT7SIZE	sizeof(struct fmt7)
E 3
#define	FMT9SIZE	sizeof(struct fmt9)
#define	FMTASIZE	sizeof(struct fmtA)
#define	FMTBSIZE	sizeof(struct fmtB)

#define	V_BUSERR	0x008
#define	V_ADDRERR	0x00C
#define	V_TRAP1		0x084

I 3
/* 68020/68030 SSW bits */
E 3
#define	SSW_RC		0x2000
#define	SSW_RB		0x1000
#define	SSW_DF		0x0100
#define	SSW_RM		0x0080
#define	SSW_RW		0x0040
#define	SSW_FCMASK	0x0007

I 3
/* 68040 SSW bits */
#define	SSW4_CP		0x8000
#define	SSW4_CU		0x4000
#define	SSW4_CT		0x2000
#define	SSW4_CM		0x1000
#define	SSW4_MA		0x0800
#define	SSW4_ATC	0x0400
#define	SSW4_LK		0x0200
#define	SSW4_RW		0x0100
#define SSW4_WBSV	0x0080	/* really in WB status, not SSW */
#define	SSW4_SZMASK	0x0060
#define	SSW4_SZLW	0x0000
#define	SSW4_SZB	0x0020
#define	SSW4_SZW	0x0040
#define	SSW4_SZLN	0x0060
#define	SSW4_TTMASK	0x0018
#define	SSW4_TTNOR	0x0000
#define	SSW4_TTM16	0x0008
#define	SSW4_TMMASK	0x0007
#define	SSW4_TMDCP	0x0000
#define	SSW4_TMUD	0x0001
#define	SSW4_TMUC	0x0002
#define	SSW4_TMKD	0x0005
#define	SSW4_TMKC	0x0006

E 3
struct fpframe {
	union FPF_u1 {
		u_int	FPF_null;
		struct {
			u_char	FPF_version;
			u_char	FPF_fsize;
			u_short	FPF_res1;
		} FPF_nonnull;
	} FPF_u1;
	union FPF_u2 {
		struct fpidle {
			u_short	fpf_ccr;
			u_short	fpf_res2;
			u_int	fpf_iregs1[8];
			u_int	fpf_xops[3];
			u_int	fpf_opreg;
			u_int	fpf_biu;
		} FPF_idle;

		struct fpbusy {
			u_int	fpf_iregs[53];
		} FPF_busy;
I 3

		struct fpunimp {
			u_int	fpf_state[10];
		} FPF_unimp;
E 3
	} FPF_u2;
	u_int	fpf_regs[8*3];
	u_int	fpf_fpcr;
	u_int	fpf_fpsr;
	u_int	fpf_fpiar;
};

#define fpf_null	FPF_u1.FPF_null
#define fpf_version	FPF_u1.FPF_nonnull.FPF_version
#define fpf_fsize	FPF_u1.FPF_nonnull.FPF_fsize
#define fpf_res1	FPF_u1.FPF_nonnull.FPF_res1
#define fpf_idle	FPF_u2.FPF_idle
#define fpf_busy	FPF_u2.FPF_busy
I 3
#define fpf_unimp	FPF_u2.FPF_unimp
E 3
E 1
