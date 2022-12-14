h65515
s 00002/00002/00248
d D 8.1 93/06/10 21:34:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00044/00062/00206
d D 7.4 92/12/27 09:32:36 hibler 4 3
c disklabel support
e
s 00021/00008/00247
d D 7.3 91/02/25 22:41:08 mckusick 3 2
c update from Hibler for additional HP disks
e
s 00001/00001/00254
d D 7.2 90/11/04 19:39:24 mckusick 2 1
c update identifier from Utah
e
s 00255/00000/00000
d D 7.1 90/05/08 22:06:47 mckusick 1 0
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
 * from: Utah $Hdr: rdreg.h 1.14 89/02/27$
E 2
I 2
D 3
 * from: Utah $Hdr: rdreg.h 1.1 90/07/09$
E 3
I 3
 * from: Utah $Hdr: rdreg.h 1.2 90/10/12$
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

struct	rd_iocmd {
	char	c_pad;
	char	c_unit;
	char	c_volume;
	char	c_saddr;
	short	c_hiaddr;
	long	c_addr;
	char	c_nop2;
	char	c_slen;
	long	c_len;
	char	c_cmd;
	char	c_pad2;
};

struct	rd_rscmd {
	char	c_unit;
	char	c_sram;
	char	c_ram;
	char	c_cmd;
};

struct	rd_stat {
	char	c_vu;
	char	c_pend;
	short	c_ref;
	short	c_fef;
	short	c_aef;
	short	c_ief;
	union {
		char cu_raw[10];
		struct {
			short	cu_msw;
			long	cu_lsl;
		} cu_sva;
		struct {
			long	cu_cyhd;
			short	cu_sect;
		} cu_tva;
	} c_pf;
};
#define c_raw	c_pf.cu_raw
#define c_blk	c_pf.cu_sva.cu_lsl	/* for now */
#define c_tva	c_pf.cu_tva

struct	rd_ssmcmd {
	char	c_unit;
	char	c_cmd;
	short	c_refm;
	short	c_fefm;
	short	c_aefm;
	short	c_iefm;
};

struct	rd_srcmd {
	char	c_unit;
	char	c_nop;
	char	c_cmd;
	char	c_param;
};

struct	rd_clearcmd {
	char	c_unit;
	char	c_cmd;
};

struct rd_describe {
	u_int	d_iuw:16,	/* controller: installed unit word */
		d_cmaxxfr:16,	/* controller: max transfer rate (Kb) */
		d_ctype:8,	/* controller: controller type */
		d_utype:8,	/* unit: unit type */
		d_name:24,	/* unit: name (6 BCD digits) */
		d_sectsize:16,	/* unit: # of bytes per block (sector) */
		d_blkbuf:8,	/* unit: # of blocks which can be buffered */
		d_burstsize:8,	/* unit: recommended burst size */
		d_blocktime:16,	/* unit: block time (u-sec) */
		d_uavexfr:16,	/* unit: average transfer rate (Kb) */
		d_retry:16,	/* unit: optimal retry time (1/100-sec) */
		d_access:16,	/* unit: access time param (1/100-sec) */
		d_maxint:8,	/* unit: maximum interleave */
		d_fvbyte:8,	/* unit: fixed volume byte */
		d_rvbyte:8,	/* unit: removeable volume byte */
		d_maxcyl:24,	/* volume: maximum cylinder */
		d_maxhead:8,	/* volume: maximum head */
		d_maxsect:16,	/* volume: maximum sector on track */
		d_maxvsecth:16,	/* volume: maximum sector on volume (MSW) */
		d_maxvsectl:32,	/* volume: maximum sector on volume (LSWs) */
		d_interleave:8;	/* volume: current interleave */
 };

D 4
/* indicies into rdinfo -- order is arbitrary */
#define	RD7945A		0
#define	RD9134D		1
#define	RD9122S		2
#define	RD7912P		3
#define	RD7914P		4
#define	RD7958A		5
#define RD7957A		6
#define	RD7933H		7
#define	RD9134L		8
#define	RD7936H		9
#define	RD7937H		10
#define RD7914CT	11
#define RD7946A		12
#define RD9122D		13
#define RD7957B		14
#define RD7958B		15
#define RD7959B		16

E 4
/* HW ids */
#define	RD7946AID	0x220	/* also 7945A */
#define	RD9134DID	0x221	/* also 9122S */
#define	RD9134LID	0x222	/* also 9122D */
#define	RD7912PID	0x209
#define RD7914CTID	0x20A
#define	RD7914PID	0x20B
#define	RD7958AID	0x22B
#define RD7957AID	0x22A
#define	RD7933HID	0x212
#define	RD7936HID	0x213	/* just guessing -- as of yet unknown */
#define	RD7937HID	0x214
#define RD7957BID	0x22C	/* another guess based on 7958B */
#define RD7958BID	0x22D
#define RD7959BID	0x22E	/* another guess based on 7958B */
I 3
#define RD2200AID	0x22F
#define RD2203AID	0x230	/* yet another guess */
E 3

D 4
#define	NRD7945ABPT	(32 >> (DEV_BSHIFT-8))
E 4
I 4
/* SW ids -- indicies into rdidentinfo, order is arbitrary */
#define	RD7945A		0
#define	RD9134D		1
#define	RD9122S		2
#define	RD7912P		3
#define	RD7914P		4
#define	RD7958A		5
#define RD7957A		6
#define	RD7933H		7
#define	RD9134L		8
#define	RD7936H		9
#define	RD7937H		10
#define RD7914CT	11
#define RD7946A		12
#define RD9122D		13
#define RD7957B		14
#define RD7958B		15
#define RD7959B		16

#define	NRD7945ABPT	16
E 4
#define	NRD7945ATRK	7
D 4
#define	NRD9134DBPT	(32 >> (DEV_BSHIFT-8))
E 4
I 4
#define	NRD9134DBPT	16
E 4
#define	NRD9134DTRK	6
D 4
#define	NRD9122SBPT	(16 >> (DEV_BSHIFT-8))
E 4
I 4
#define	NRD9122SBPT	8
E 4
#define	NRD9122STRK	2
D 4
#define	NRD7912PBPT	(64 >> (DEV_BSHIFT-8))
E 4
I 4
#define	NRD7912PBPT	32
E 4
#define	NRD7912PTRK	7
D 4
#define	NRD7914PBPT	(64 >> (DEV_BSHIFT-8))
E 4
I 4
#define	NRD7914PBPT	32
E 4
#define	NRD7914PTRK	7
D 4
#define	NRD7933HBPT	(92 >> (DEV_BSHIFT-8))
E 4
I 4
#define	NRD7933HBPT	46
E 4
#define	NRD7933HTRK	13
D 4
#define	NRD9134LBPT	(32 >> (DEV_BSHIFT-8))
E 4
I 4
#define	NRD9134LBPT	16
E 4
#define	NRD9134LTRK	5

/*
 * Several HP drives have an odd number of 256 byte sectors per track.
 * This makes it rather difficult to break them into 512 and 1024 byte blocks.
 * So...we just do like HPUX and don't bother to respect hardware track/head
 * boundries -- we just mold the disk so that we use the entire capacity.
 * HPUX also sometimes doen't abide by cylinder boundries, we attempt to
 * whenever possible.
 *
 * DISK		REAL (256 BPS)		HPUX (1024 BPS)		BSD (512 BPS)
 * 		SPT x HD x CYL		SPT x HD x CYL		SPT x HD x CYL
 * -----	---------------		---------------		--------------
D 3
 * 7936:	123 x  7 x 1396		25 x  7 x 1716		123 x  7 x  698
 * 7937:	123 x 13 x 1396		25 x 16 x 1395		123 x 13 x  698
E 3
I 3
 * 7936:	123 x  7 x 1396		 25 x  7 x 1716		123 x  7 x  698
 * 7937:	123 x 13 x 1396		 25 x 16 x 1395		123 x 13 x  698
E 3
 *
D 3
 * 7957A:	 63 x  5 x 1013		11 x  7 x 1036		 22 x  7 x 1036
 * 7958A:	 63 x  8 x 1013		21 x  6 x 1013		 36 x  7 x 1013
E 3
I 3
 * 7957A:	 63 x  5 x 1013		 11 x  7 x 1036		 22 x  7 x 1036
 * 7958A:	 63 x  8 x 1013		 21 x  6 x 1013		 36 x  7 x 1013
E 3
 *
D 3
 * 7957B:	 63 x  4 x 1269		 9 x  7 x 1269		 18 x  7 x 1269
 * 7958B:	 63 x  6 x 1572		21 x  9 x  786		 42 x  9 x  786
 * 7959B:	 63 x 12 x 1572		21 x  9 x 1572		 42 x  9 x 1572
E 3
I 3
 * 7957B:	 63 x  4 x 1269		  9 x  7 x 1269		 18 x  7 x 1269
 * 7958B:	 63 x  6 x 1572		 21 x  9 x  786		 42 x  9 x  786
 * 7959B:	 63 x 12 x 1572		 21 x  9 x 1572		 42 x  9 x 1572
 *
 * 2200A:	113 x  8 x 1449		113 x  2 x 1449		113 x  4 x 1449
 * 2203A:	113 x 16 x 1449		113 x  4 x 1449		113 x  8 x 1449
E 3
 */
D 4
#if DEV_BSIZE == 512
#	define	NRD7936HBPT	123
#	define	NRD7936HTRK	7
#	define	NRD7937HBPT	123
#	define	NRD7937HTRK	13
#	define	NRD7957ABPT	22
#	define	NRD7957ATRK	7
#	define	NRD7958ABPT	36
#	define	NRD7958ATRK	7
#	define	NRD7957BBPT	18
#	define	NRD7957BTRK	7
#	define	NRD7958BBPT	42
#	define	NRD7958BTRK	9
#	define	NRD7959BBPT	42
#	define	NRD7959BTRK	9
I 3
#	define	NRD2200ABPT	113
#	define	NRD2200ATRK	4
#	define	NRD2203ABPT	113
#	define	NRD2203ATRK	8
E 3
#endif
#if DEV_BSIZE == 1024
#	define	NRD7957ABPT	11
#	define	NRD7957ATRK	7
#	define	NRD7958ABPT	21
#	define	NRD7958ATRK	6
#	define	NRD7957BBPT	9
#	define	NRD7957BTRK	7
#	define	NRD7958BBPT	21
#	define	NRD7958BTRK	9
#	define	NRD7959BBPT	21
#	define	NRD7959BTRK	9
I 3
#	define	NRD2200ABPT	113
#	define	NRD2200ATRK	2
#	define	NRD2203ABPT	113
#	define	NRD2203ATRK	4
E 3
#endif
E 4
I 4
#define	NRD7936HBPT	123
#define	NRD7936HTRK	7
#define	NRD7937HBPT	123
#define	NRD7937HTRK	13
#define	NRD7957ABPT	22
#define	NRD7957ATRK	7
#define	NRD7958ABPT	36
#define	NRD7958ATRK	7
#define	NRD7957BBPT	18
#define	NRD7957BTRK	7
#define	NRD7958BBPT	42
#define	NRD7958BTRK	9
#define	NRD7959BBPT	42
#define	NRD7959BTRK	9
#define	NRD2200ABPT	113
#define	NRD2200ATRK	4
#define	NRD2203ABPT	113
#define	NRD2203ATRK	8
E 4

/* controller "unit" number */
#define	RDCTLR		15

/* convert 512 byte count into DEV_BSIZE count */
#define RDSZ(x)		((x) >> (DEV_BSHIFT-9))

/* convert block number into sector number and back */
#define	RDBTOS(x)	((x) << (DEV_BSHIFT-8))
#define RDSTOB(x)	((x) >> (DEV_BSHIFT-8))

/* extract cyl/head/sect info from three-vector address */
#define RDCYL(tva)	((u_long)(tva).cu_cyhd >> 8)
#define RDHEAD(tva)	((tva).cu_cyhd & 0xFF)
#define RDSECT(tva)	((tva).cu_sect)

#define	REF_MASK	0x0
#define	FEF_MASK	0x0
#define	AEF_MASK	0x0
#define	IEF_MASK	0xF970

#define FEF_CU		0x4000	/* cross-unit */
#define FEF_DR		0x0080	/* diagnostic result */
#define FEF_IMR		0x0008	/* internal maintenance release */
#define	FEF_PF		0x0002	/* power fail */
#define	FEF_REXMT	0x0001	/* retransmit */
#define AEF_UD		0x0040	/* unrecoverable data */
#define IEF_RRMASK	0xe000	/* request release bits */
#define IEF_MD		0x0020	/* marginal data */
#define IEF_RD		0x0010	/* recoverable data */

#define	C_READ		0x00
#define	C_RAM		0x00	/* single vector (i.e. sector number) */
#define	C_WRITE		0x02
#define	C_CLEAR		0x08
#define	C_STATUS	0x0d
#define	C_SADDR		0x10
#define	C_SLEN		0x18
#define	C_SUNIT(x)	(0x20 | (x))
#define C_SVOL(x)	(0x40 | (x))
#define	C_NOP		0x34
#define C_DESC		0x35
#define	C_SREL		0x3b
#define	C_SSM		0x3e
#define	C_SRAM		0x48
#define	C_REL		0x140

#define	C_CMD		0x05
#define	C_EXEC		0x0e
#define	C_QSTAT		0x10
#define	C_TCMD		0x12
E 1
