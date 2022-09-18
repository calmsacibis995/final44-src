h54963
s 00002/00002/00217
d D 8.1 93/06/11 15:54:12 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00216
d D 7.1 91/05/09 23:32:50 bostic 3 2
c new copyright; att/bsd/shared
e
s 00013/00012/00206
d D 5.2 90/11/08 19:44:01 bill 2 1
c trivial changes
e
s 00218/00000/00000
d D 5.1 90/04/22 17:53:04 william 1 0
c date and time created 90/04/22 17:53:04 by william
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
E 3
I 3
D 4
 * Copyright (c) 1991 The Regents of the University of California.
E 3
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 3
 * Tim L. Tucker
E 3
I 3
 * Tim L. Tucker.
E 3
 *
D 3
 * %sccs.include.noredist.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Western Digital 8003 ethernet/starlan adapter 
 */
 
/*
 * Memory Select Register (MSR)
 */
D 2
union wd_mem_sel {
E 2
I 2
union we_mem_sel {
E 2
    struct memory_decode {
        u_char msd_addr:6,		/* Memory decode bits		*/
	       msd_enable:1,		/* Memory (RAM) enable		*/
	       msd_reset:1;		/* Software reset 		*/
    } msd_decode;
#define ms_addr		msd_decode.msd_addr
#define ms_enable	msd_decode.msd_enable
#define ms_reset	msd_decode.msd_reset
    u_char ms_byte;			/* entire byte			*/
};

/*
 * receive ring discriptor
 *
D 2
 * The National Semiconductor NS32490 Network interface controller uses
E 2
I 2
 * The National Semiconductor DS8390 Network interface controller uses
E 2
 * the following receive ring headers.  The way this works is that the
 * memory on the interface card is chopped up into 256 bytes blocks.
D 2
 * A contiuguous portion of those blocks are marked for receive packets
E 2
I 2
 * A contiguous portion of those blocks are marked for receive packets
E 2
 * by setting start and end block #'s in the NIC.  For each packet that
 * is put into the receive ring, one of these headers (4 bytes each) is
 * tacked onto the front.
 */
D 2
struct wd_ring	{
	struct wdr_status {		/* received packet status	*/
E 2
I 2
struct we_ring	{
	struct wer_status {		/* received packet status	*/
E 2
	    u_char rs_prx:1,		    /* packet received intack	*/
		   rs_crc:1,		    /* crc error		*/
	           rs_fae:1,		    /* frame alignment error	*/
	           rs_fo:1,		    /* fifo overrun		*/
	           rs_mpa:1,		    /* packet received intack	*/
	           rs_phy:1,		    /* packet received intack	*/
	           rs_dis:1,		    /* packet received intack	*/
	           rs_dfr:1;		    /* packet received intack	*/
D 2
	} wd_rcv_status;		/* received packet status	*/
	u_char	wd_next_packet;		/* pointer to next packet	*/
	u_short	wd_count;		/* bytes in packet (length + 4)	*/
E 2
I 2
	} we_rcv_status;		/* received packet status	*/
	u_char	we_next_packet;		/* pointer to next packet	*/
	u_short	we_count;		/* bytes in packet (length + 4)	*/
E 2
};

/*
 * Command word definition
 */
D 2
union wd_command {
E 2
I 2
union we_command {
E 2
    struct command_decode {
	u_char csd_stp:1,		/* STOP!			*/
	       csd_sta:1,		/* START!			*/
               csd_txp:1,		/* Transmit packet		*/
               csd_rd:3,		/* Remote DMA command		*/
               csd_ps:2;		/* Page select			*/
    } csd_decode;
#define cs_stp		csd_decode.csd_stp
#define cs_sta		csd_decode.csd_sta
#define cs_txp		csd_decode.csd_txp
#define cs_rd		csd_decode.csd_rd
#define cs_ps		csd_decode.csd_ps
    u_char cs_byte;			/* entire command byte		*/
};

/*
 * Interrupt status definition
 */
D 2
union wd_interrupt {
E 2
I 2
union we_interrupt {
E 2
    struct interrupt_decode {
	u_char isd_prx:1,		/* Packet received		*/
	       isd_ptx:1,		/* Packet transmitted		*/
               isd_rxe:1,		/* Receive error		*/
               isd_txe:1,		/* Transmit error		*/
               isd_ovw:1,		/* Overwrite warning		*/
               isd_cnt:1,		/* Counter overflow		*/
               isd_rdc:1,		/* Remote DMA complete		*/
               isd_rst:1;		/* Reset status			*/
    } isd_decode;
#define is_prx		isd_decode.isd_prx
#define is_ptx		isd_decode.isd_ptx
#define is_rxe		isd_decode.isd_rxe
#define is_txe		isd_decode.isd_txe
#define is_ovw		isd_decode.isd_ovw
#define is_cnt		isd_decode.isd_cnt
#define is_rdc		isd_decode.isd_rdc
#define is_rst		isd_decode.isd_rst
    u_char is_byte;			/* entire interrupt byte	*/
};
 
/*
 * Status word definition (transmit)
 */
D 2
union wdt_status {
E 2
I 2
union wet_status {
E 2
    struct tstat {
	u_char tsd_ptx:1,		/* Packet transmitted intack	*/
	       tsd_dfr:1,		/* Non deferred transmition	*/
               tsd_col:1,		/* Transmit Collided		*/
               tsd_abt:1,		/* Transmit Aborted (coll > 16)	*/
               tsd_crs:1,		/* Carrier Sense Lost		*/
               tsd_fu:1,		/* Fifo Underrun		*/
               tsd_chd:1,		/* CD Heartbeat			*/
               tsd_owc:1;		/* Out of Window Collision	*/
    } tsd_decode;
#define ts_ptx		tsd_decode.tsd_ptx
#define ts_dfr		tsd_decode.tsd_dfr
#define ts_col		tsd_decode.tsd_col
#define ts_abt		tsd_decode.tsd_abt
#define ts_crs		tsd_decode.tsd_crs
#define ts_fu		tsd_decode.tsd_fu
#define ts_chd		tsd_decode.tsd_chd
#define ts_owc		tsd_decode.tsd_owc
    u_char ts_byte;			/* entire transmit byte		*/
};

/*
 * General constant definitions
 */
#define	WD_STARLAN	0x02		/* WD8003S Identification	*/
#define	WD_ETHER	0x03		/* WD8003E Identification	*/
I 2
#define	WD_ETHER2	0x05		/* WD8003EBT Identification	*/
E 2
#define WD_CHECKSUM	0xFF		/* Checksum byte		*/
#define WD_PAGE_SIZE	256		/* Size of RAM pages in bytes	*/
#define WD_TXBUF_SIZE	6		/* Size of TX buffer in pages	*/
#define WD_ROM_OFFSET	8		/* i/o base offset to ROM	*/
#define WD_IO_PORTS	32		/* # of i/o addresses used	*/
#define WD_NIC_OFFSET	16		/* i/o base offset to NIC	*/

/*
 * Page register offset values
 */
#define WD_P0_COMMAND	0x00		/* Command register 		*/
#define WD_P0_PSTART	0x01		/* Page Start register		*/
#define WD_P0_PSTOP	0x02		/* Page Stop register		*/
#define WD_P0_BNRY	0x03		/* Boundary Pointer		*/
#define WD_P0_TSR	0x04		/* Transmit Status (read-only)	*/
#define WD_P0_TPSR	WD_P0_TSR	/* Transmit Page (write-only)	*/
#define WD_P0_TBCR0	0x05		/* Transmit Byte count, low  WO	*/
#define WD_P0_TBCR1	0x06		/* Transmit Byte count, high WO	*/
#define WD_P0_ISR	0x07		/* Interrupt status register	*/
#define WD_P0_RBCR0	0x0A		/* Remote byte count low     WO	*/
#define WD_P0_RBCR1	0x0B		/* Remote byte count high    WO	*/
#define WD_P0_RSR	0x0C		/* Receive status            RO	*/
#define WD_P0_RCR	WD_P0_RSR	/* Receive configuration     WO */
#define WD_P0_TCR	0x0D		/* Transmit configuration    WO */
#define WD_P0_DCR	0x0E		/* Data configuration	     WO */
#define WD_P0_IMR	0x0F		/* Interrupt masks	     WO	*/
#define WD_P1_COMMAND	0x00		/* Command register 		*/
#define WD_P1_PAR0	0x01		/* Physical address register 0	*/
#define WD_P1_PAR1	0x02		/* Physical address register 1	*/
#define WD_P1_PAR2	0x03		/* Physical address register 2	*/
#define WD_P1_PAR3	0x04		/* Physical address register 3	*/
#define WD_P1_PAR4	0x05		/* Physical address register 4	*/
#define WD_P1_PAR5	0x06		/* Physical address register 5	*/
#define WD_P1_CURR	0x07		/* Current page (receive unit)  */
#define WD_P1_MAR0	0x08		/* Multicast address register 0	*/

/*
 * Configuration constants (receive unit)
 */
#define WD_R_SEP	0x01		/* Save error packets		*/
#define WD_R_AR		0x02		/* Accept Runt packets		*/
#define WD_R_AB		0x04		/* Accept Broadcast packets	*/
#define WD_R_AM		0x08		/* Accept Multicast packets	*/
#define WD_R_PRO	0x10		/* Promiscuous physical		*/
#define WD_R_MON	0x20		/* Monitor mode			*/
#define WD_R_RES1	0x40		/* reserved...			*/
#define WD_R_RES2	0x80		/* reserved...			*/
#define	WD_R_CONFIG	(WD_R_AB)

/*
 * Configuration constants (transmit unit)
 */
#define WD_T_CRC	0x01		/* Inhibit CRC			*/
#define WD_T_LB0	0x02		/* Encoded Loopback Control	*/
#define WD_T_LB1	0x04		/* Encoded Loopback Control	*/
#define WD_T_ATD	0x08		/* Auto Transmit Disable	*/
#define WD_T_OFST	0x10		/* Collision Offset Enable	*/
#define WD_T_RES1	0x20		/* reserved...			*/
#define WD_T_RES2	0x40		/* reserved...			*/
#define WD_T_RES3	0x80		/* reserved...			*/
#define	WD_T_CONFIG	(0)

/*
 * Configuration constants (data unit)
 */
#define WD_D_WTS	0x01		/* Word Transfer Select		*/
#define WD_D_BOS	0x02		/* Byte Order Select		*/
#define WD_D_LAS	0x04		/* Long Address Select		*/
#define WD_D_BMS	0x08		/* Burst Mode Select		*/
#define WD_D_AR		0x10		/* Autoinitialize Remote	*/
#define WD_D_FT0	0x20		/* Fifo Threshold Select	*/
#define WD_D_FT1	0x40		/* Fifo Threshold Select	*/
#define WD_D_RES	0x80		/* reserved...			*/
#define	WD_D_CONFIG	(WD_D_FT1|WD_D_BMS)

/*
 * Configuration constants (interrupt mask register)
 */
#define WD_I_PRXE	0x01		/* Packet received enable	*/
#define WD_I_PTXE	0x02		/* Packet transmitted enable	*/
#define WD_I_RXEE	0x04		/* Receive error enable		*/
#define WD_I_TXEE	0x08		/* Transmit error enable	*/
#define WD_I_OVWE	0x10		/* Overwrite warning enable	*/
#define WD_I_CNTE	0x20		/* Counter overflow enable	*/
#define WD_I_RDCE	0x40		/* Dma complete enable		*/
#define WD_I_RES	0x80		/* reserved...			*/
D 2
#define	WD_I_CONFIG	(WD_I_PRXE|WD_I_PTXE|WD_I_RXEE|WD_I_TXEE)
E 2
I 2
#define WD_I_CONFIG     (WD_I_PRXE|WD_I_PTXE|WD_I_RXEE|WD_I_TXEE)
E 2
E 1
