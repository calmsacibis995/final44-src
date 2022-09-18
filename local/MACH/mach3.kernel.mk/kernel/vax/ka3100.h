/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 * HISTORY
 * $Log:	ka3100.h,v $
 * Revision 2.4  93/05/12  13:58:37  rvb
 * 	Include <sys/types.h> because pm_hdw.c no longer does.
 * 	[93/05/12            rvb]
 * 
 * Revision 2.3  93/03/11  13:47:40  danner
 * 	Elimate u_long.
 * 	[93/03/09            danner]
 * 
 * Revision 2.2  91/06/19  17:11:54  rvb
 * 	Changes from sandro
 * 	[91/06/19            rvb]
 * 
 * 	Support for VaxStation 3100: new processor cvax + different
 * 	memory and bus.
 * 	[91/06/04            rvb]
 * 
 * 	Created
 * 	[91/04/26            rvb]
 * 
 * 30-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Created
 */

#include <sys/types.h>

#define KA42MEM		0
#define KA42MEM_SIZE	(32*1024*1024)

#define C2DATA		0x10000000
#define C2DATA_SIZE	(32*1024)
#define C2TAG		0x10010000
#define C2TAG_SIZE	(32*1024)

#define IO_RESET	0x20020000
#define CFGTST		0x20020000
#define   STCOPT	0xc000
#define      VS42X_RB	0x0000
#define      VS42X_SCSC	0x4000
#define      VS42X_RD	0x8000
#define      VS42X_NONE	0xC000
#define	  SCSIPR_	0x1000
#define   DRV3PR_	0x0800
#define   DRV2PR_	0x0400
#define   DRV1PR_	0x0200
#define   DRV0PR_	0x0100
#define   MULTU_	0x0080
#define   CACHPR	0x0040
#define   ALCON		0x0020
#define   CURTEST	0x0010
#define   VIDOPT	0x0008
#define   MTYPE		0x0007

#define ROM3100		0x20040000
#define ROM3100_SIZE	(256*1024)
struct rom {
/*00*/		long	rom_jmp;
/*04*/		u_char  arch_ident;
/*05*/		u_char  sys_depend;
/*06*/		u_char  revision;
/*07*/		u_char  sys_type;
/*08*/		u_int	fill[8-2];
/*20*/		u_int   intA[8];
};

#define STAT		0x20080000
#define STAT_SIZE	0x20
struct stat {
/*00*/	u_int	hltcode;
/*04*/	u_int	resv0;
/*08*/	u_int	resv1;
/*0c*/	u_char	int_msk;
/*0d*/	u_char	vdc_org;
/*0e*/	u_char	vdc_sel;
/*0f*/	u_char	int_req;
#define int_clr int_req
#define		INT_DC	0
#define		INT_SC	1
#define		INT_VS	2
#define		INT_VF	3
#define		INT_NS	4
#define		INT_NI	5
#define		INT_ST	6
#define		INT_SR	7
/*10*/	u_short	diagdisp;
	u_short resv2;
/*14*/	u_int	par_ctl;
#define		PAR_CTL_DMA	0x01000000
#define		PAR_CTL_CPEN	0x00000002
#define		PAR_CTL_DPEN	0x00000001
#define		PAR_CTL_PEN	0x00000003
/*18*/	u_int	resv3;
/*1c*/	u_short	resv4;
/*1e*/	u_short	diagtime;
};

#define CACR		0x20084000
#define C2CACR_SIZE	4
#define   CACR_CSP	0xc0
#define   CACR_TPE	0x20
#define   CACR_CEN	0x10
#define   CACR_ERR	0x20


#define ETHERADDR	0x20090000
#define ETHER_SIZE	128

#define SER_xxx		0x200a0000
#define SER_SIZE	16

#define WAT_xxx		0x200b0000
#define WAT_SIZE	256
/* NV-RAM usage (from Ultrix 4.1) */
struct ka3100_nvram {
/*00*/	u_int	cpmbx;		/* Console program mailbox	*/
/*04*/	u_int	cpflg;		/* Console program flags	*/
/*08*/	u_int	lk201_id;	/* LK201 keyboard variation	*/
/*0c*/	u_int	console_id;	/* Console device type		*/
/*10*/	u_int	scr[4];		/* Scratch RAM physical address	*/
/*20*/	u_int	temp[12];	/* Used by System Firmware	*/
/*50*/	u_int	bat_chk[4];	/* Battery check data		*/
/*60*/	u_int	boot_dev[4];	/* Default boot device		*/
/*70*/	u_int	boot_flg[4];	/* Default boot flags		*/
/*80*/	u_int	scr_length;	/* # of pages of scratch RAM	*/
/*84*/	u_int	cpu_scsi_id;	/* System's SCSI bus 0 & 1 IDs  */
/*88*/	u_int	reserved[16];	/* reserved			*/
};

#define LANCE		0x200e0000
#define LANCE_SIZE	8

#define CUR_xxx		0x200f0000
#define CUR_SIZE	64

#define	OPT0		0x20100000
#define	OPT0_SIZE	0x40000

#define	OPT1		0x20140000
#define	OPT1_SIZE	0x40000

#define	OPT2		0x20180000
#define	OPT2_SIZE	0x40000

#define	OPT3		0x201c0000
#define	OPT3_SIZE	0x40000

#define BM_MEM		0x30000000
#define BM_MEM_SIZE	(256*1024)

#define MSER_DAL	0x40
#define MSER_MCD	0x20
#define MSER_MCC	0x10
#define MSER_DAT	0x02
#define MSER_TAG	0x01
#define MSER_ERR	0x73

#ifdef	KERNEL
extern	u_int			*cacr;
extern	u_int			*c2data;
extern	u_short			*cfgtst;
extern	struct rom		*rom;
extern	struct stat		*stat;
extern	struct watch_chip/*_3100*/	*watch_chip;	/* can't cast esily */
extern	u_char			*etheraddr;
extern	struct ser		*ser_xxx;
extern	u_short			*lance;
extern	u_char			*cur_xxx;
extern	u_char			*bm_mem;
#endif	KERNEL
