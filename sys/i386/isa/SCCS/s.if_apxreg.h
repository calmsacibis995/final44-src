h56218
s 00002/00002/00173
d D 8.1 93/06/11 15:53:52 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00016/00154
d D 7.4 92/03/05 19:17:44 sklower 4 3
c this version works, has been tidied up for public consumption
e
s 00008/00006/00162
d D 7.3 92/03/03 17:00:00 sklower 3 2
c correct misspellings
e
s 00003/00003/00165
d D 7.2 91/08/09 12:43:04 sklower 2 1
c this version compiles, probably doesn't run.
e
s 00168/00000/00000
d D 7.1 91/08/09 12:04:13 sklower 1 0
c Driver for ADAX APC-PCX, an SGS Thompson MK5025 based HDLC board
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */


D 3
/* SGS Thompson MK5205 structures and registers */
E 3
I 3
/*
 * SGS Thompson MK5205 structures and registers
 */
E 3

/* 
D 3
 * Device Control Ports
 * (Multiplexed CSR's)
E 3
I 3
 * Device Control Ports (Multiplexed CSR's)
E 3
 */
struct sgcp {
D 4
	u_short sgcp_rdp;
	u_short sgcp_rap;
E 4
I 4
	u_short	sgcp_rdp;
	u_short	sgcp_rap;
E 4
};
I 3

E 3
/*
 * Operating Parameters for timers etc.
 * (Suitable for reseting by ioctl).
 */ 
struct sgop {
D 4
	u_short lsaddr;
	u_short rsaddr;
E 4
I 4
	u_short	lsaddr;
	u_short	rsaddr;
E 4
	u_short	n1;
	u_short	n2_scale;
	u_short	t1;
	u_short	t3;
	u_short	tp;
};

/*
I 4
 * Common addressing element rife through chip
 */
struct sgae {
	u_short	f_hi;
	u_short	lo;
};
/*
E 4
D 3
 * common format for tx/rx descriptors
E 3
I 3
 * Common format for tx/rx descriptors
E 3
 */

struct sgdx {
D 4
	u_short	sgdx_flags;
	u_short	sgdx_addr;
E 4
I 4
	struct	sgae sgdx_ae;
#define		sgdx_flags sgdx_ae.f_hi
#define		sgdx_addr sgdx_ae.lo
E 4
	short	sgdx_bcnt;
D 4
	u_short	sgdx_mcnt;
E 4
I 4
	short	sgdx_mcnt;
E 4
};

/*
D 3
 * interpretation of reported errors 
E 3
I 3
 * Interpretation of reported errors 
E 3
 */
struct sger {
	u_short	sger_bad;
	u_short	sger_t1timo;
	u_short	sger_frmr;
	u_short	sger_txrej;
	u_short	sger_rxrej;
	u_short	sger_short;
};

/*
D 3
 * Status Buffer, paried bytes hi order low order
E 3
I 3
 * Status buffer, paired bytes hi order low order
E 3
 */
struct sgsb {
	u_short	sgsb_vrvs;
	u_short	sgsb_lsrs;
D 4
	u_short sgsb_phzva;
E 4
I 4
	u_short	sgsb_phzva;
E 4
	u_short	sgsb_hirxcnt;
	u_short	sgsb_lorxcnt;
	u_short	sgsb_hitxcnt;
	u_short	sgsb_lotxcnt;
};

#define SGMTU 1032
#define SGRBUF 16
D 2
#define SGRBUFLOG2 4
E 2
I 2
#define SGRBUF_LOG2 4
E 2
#define SG_RLEN (SGRBUF_LOG2 << 12)
#define SGTBUF 8
D 2
#define SGTBUFLOG2 3
E 2
I 2
#define SGTBUF_LOG2 3
E 2
#define SG_TLEN (SGTBUF_LOG2 << 12)

/*
 * APC-PCX RAM
 */

struct apc_mem {
	/* Initialization Block */
	u_short	apc_mode;
	struct	sgop apc_sgop;
D 4
	u_short	apc_rlen;
	u_short	apc_rdra;
	u_short	apc_tlen;
	u_short	apc_tdra;
E 4
I 4
	struct	sgae apc_rxdd;
	struct	sgae apc_txdd;
E 4
	struct	sgdx apc_txtid;
	struct	sgdx apc_rxtid;
D 4
	u_short	apc_stathi;
	u_short	apc_statlo;
E 4
I 4
	struct	sgae apc_stdd;
E 4
	struct	sger apc_sger;
	struct	sgsb apc_sgsb;		/* Status Buffer */
	struct	sgdx apc_rxmd[SGRBUF];	/* Receive Message Descriptors */
	struct	sgdx apc_txmd[SGTBUF];	/* Transmit Message Descriptors */
	char	apc_rbuf[SGRBUF][SGMTU]; /* Receive Message Buffers */
	char	apc_tbuf[SGTBUF][SGMTU]; /* Transmit Message Buffers */
	char	apc_rxidbuf[SGMTU];
	char	apc_txidbuf[SGMTU];
};
/*
 * APC-PCX registers
 */
struct apc_reg {
D 2
	struct	sgcb axr_sgcb[2];
E 2
I 2
	struct	sgcp axr_sgcp[2];
E 2
	u_char	arx_pad0[4];
	u_char	axr_cnt0;
	u_char	axr_cnt1;
	u_char	axr_cnt2;
	u_char	axr_ccr;
	u_char	axr_mode;
	u_char	axr_pad1;
	u_char	axr_status;
	u_char	axr_pad2;
	u_char	axr_altmode;
	u_char	axr_pad3[11];
};

/*
 * Hardware tweaking
 */
struct apc_modes {
	struct	sgop apm_sgop;	/* tweak timers */
	u_char	apm_txwin;	/* set parameter for transmit window */
	u_char	apm_apxmode;
	u_char	apm_apxaltmode;
D 4
	u_char 	apm_iftype;	/* someday indicate PPP vs X.25 */
E 4
I 4
	u_char	apm_iftype;	/* someday indicate PPP vs X.25 */
E 4
};

#define	SIOCSIFMODE	_IOW('i', 127, struct apc_modes) /* set parameters */

/* TX RX descriptor bits */
#define SG_OWN 0x8000
#define SG_SLF 0x2000
#define SG_ELF 0x1000
#define	SG_TUI 0x800

/* CSR0 quantities */
#define SG_TDMD	0x8000
#define SG_STOPPED 0x4000
#define SG_DTX	0x2000
#define SG_DRX	0x1000
#define SG_TXON 0x800
#define SG_RXON 0x400
#define SG_INEA 0x200
#define SG_INTR 0x100
#define SG_MERR 0x80
#define SG_MISS 0x40
#define SG_ROR	0x20
#define SG_TUR	0x10
#define SG_PINT 0x8
#define SG_TINT 0x4
#define SG_RINT 0x2

/* CSR1 quantities */
#define SG_UAV	0x4000
#define SG_PAV	0x40
#define SG_STOP	0
D 4
#define	SG_INIT	(2 << 8)
E 4
I 4
#define SG_INIT	(2 << 8)
E 4
#define SG_TRANS (3 << 8)
#define SG_STAT	(4 << 8)

#define SG_PROM	0x400
#define SG_UIE	0x200
#define SG_BSWAP 0x20
E 1
