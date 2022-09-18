/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	scsi.h,v $
 * Revision 2.1.1.1  91/03/28  08:47:07  rvb
 * 	Acquired from osf.
 * 	[91/03/25            rvb]
 * 
 */

/*
 * SCSI interface description
 * Copyright (c) 1990 OSF Research Institute 
 */

/*
 * Copyright 1990 by Open Software Foundation,
 * Grenoble, FRANCE
 *
 * 		All Rights Reserved
 * 
 *   Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OSF or Open Software
 * Foundation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 *   OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * SCSI command format
 *
 * Teh sense field at end of each item is used to get the address
 * of the replied data (specific to the adaptec board.
 */

struct scsi_cmd{
	u_char opcode;
    union {
	struct scsi_test_unit_ready {
		u_char	:5;
		u_char	lun:3;
		u_char	unused[3];
		u_char	link:1;
		u_char	flag:4;
		u_char	:3;
		u_char	sense[1];
	 
	} test_unit_ready;

	struct scsi_sense {
		u_char	:5;
		u_char	lun:3;	
		u_char	page_code:6;
		u_char	page_ctrl:2;
		u_char	unused;
		u_char	length;
		u_char	link:1;
		u_char	flag:1;
		u_char	:6;
		u_char	sense[1];
	} sense;

	struct scsi_rw {
		u_char	addr_2:5;	/* Most significant */
		u_char	lun:3;
		u_char	addr_1;
		u_char	addr_0;		/* least significant */
		u_char	length;
		u_char	link:1;
		u_char	flag:1;
		u_char	:6;
		u_char	sense[1];
	} rw;

	struct scsi_read_capacity {
		u_char	:5;
		u_char	lun:3;
		u_char	addr_3;	/* Most Significant */
		u_char	addr_2;
		u_char	addr_1;
		u_char	addr_0;	/* Least Significant */
		u_char	unused[3];
		u_char	link:1;
		u_char	flag:1;
		u_char	:6;	
		u_char	sense[1];
	} read_capacity;

	struct scsi_start_stop {
		u_char	:5;
		u_char	lun:3;
		u_char	unused[2];
		u_char	start:1;
		u_char	:7;
		u_char	:8;
		u_char	sense[1];
	} start_stop;

    } cmd;
    unsigned char sense[50];
};

/*
 * Opcodes
 */

#define	TEST_UNIT_READY		0x00
#define REQUEST_SENSE		0x03		
#define	READ_COMMAND		0x08	
#define WRITE_COMMAND		0x0a		
#define INQUIRY			0x12		
#define MODE_SELECT		0x15	
#define MODE_SENSE		0x1a
#define START_STOP		0x1b
#define	READ_CAPACITY		0x25

/*
 * sense data format
 */

struct scsi_data {
    union {
	struct scsi_extended_sense {
		u_char	error_code:4;
		u_char	error_class:3;
		u_char	valid:1;
		u_char	segment;
		u_char	sense_key:4;
		u_char	:4;
	} extended_sense;

	struct scsi_read_cap_data {
		u_char	addr_3;	/* Most significant */
		u_char	addr_2;
		u_char	addr_1;
		u_char	addr_0;	/* Least significant */
		u_char	length_3;	/* Most significant */
		u_char	length_2;
		u_char	length_1;
		u_char	length_0;	/* Least significant */
	} read_capacity;

	struct scsi_mode_sense {

		u_char	data_length;	/* Sense data length */
		u_char	unused1[3];

		u_char	density;
		u_char	nblocks_2;
		u_char	nblocks_1;
		u_char	nblocks_0;
		u_char	unused2;
		u_char	blksz_2;
		u_char	blksz_1;
		u_char	blksz_0;
	
	    union {
		struct pgcode_3 {
		   u_char pg_code:6;	/* page code (should be 3)	      */
		   u_char :2;		
		   u_char pg_length;	/* page length (should be 0x16)	      */
		   u_char trk_z_1;	/* tracks per zone (MSB)	      */
		   u_char trk_z_0;	/* tracks per zone (LSB)	      */
		   u_char alt_sec_1;	/* alternate sectors per zone (MSB)   */
		   u_char alt_sec_0;	/* alternate sectors per zone (LSB)   */
		   u_char alt_trk_z_1;	/* alternate tracks per zone (MSB)    */
		   u_char alt_trk_z_0;	/* alternate tracks per zone (LSB)    */
		   u_char alt_trk_v_1;	/* alternate tracks per volume (MSB)  */
		   u_char alt_trk_v_0;	/* alternate tracks per volume (LSB)  */
		   u_char ph_sec_t_1;	/* physical sectors per track (MSB)   */
		   u_char ph_sec_t_0;	/* physical sectors per track (LSB)   */
		   u_char bytes_s_1;	/* bytes per sector (MSB)	      */
		   u_char bytes_s_0;	/* bytes per sector (LSB)	      */
		   u_char interleave_1;/* interleave (MSB)		      */
		   u_char interleave_0;/* interleave (LSB)		      */
		   u_char trk_skew_1;	/* track skew factor (MSB)	      */
		   u_char trk_skew_0;	/* track skew factor (LSB)	      */
		   u_char cyl_skew_1;	/* cylinder skew (MSB)		      */
		   u_char cyl_skew_0;	/* cylinder skew (LSB)		      */
		   u_char reserved1:4;
		   u_char surf:1;
		   u_char rmb:1;
		   u_char hsec:1;
		   u_char ssec:1;
		   u_char reserved2;
		   u_char reserved3;
		} pgcode_3;
		struct pgcode_4 {
		   u_char pg_code:7;	/* page code (should be 4)	      */
		   u_char mbone:1;	/* must be one			      */
		   u_char pg_length;	/* page length (should be 0x16)	      */
		   u_char ncyl_2;	/* number of cylinders (MSB)	      */
		   u_char ncyl_1;	/* number of cylinders 		      */
		   u_char ncyl_0;	/* number of cylinders (LSB)	      */
		   u_char nheads;	/* number of heads 		      */
		   u_char st_cyl_wp_2;	/* starting cyl., write precomp (MSB) */
		   u_char st_cyl_wp_1;	/* starting cyl., write precomp	      */
		   u_char st_cyl_wp_0;	/* starting cyl., write precomp (LSB) */
		   u_char st_cyl_rwc_2;/* starting cyl., red. write cur (MSB)*/
		   u_char st_cyl_rwc_1;/* starting cyl., red. write cur      */
		   u_char st_cyl_rwc_0;/* starting cyl., red. write cur (LSB)*/
		   u_char driv_step_1;	/* drive step rate (MSB)	      */
		   u_char driv_step_0;	/* drive step rate (LSB)	      */
		   u_char land_zone_2;	/* landing zone cylinder (MSB)	      */
		   u_char land_zone_1;	/* landing zone cylinder 	      */
		   u_char land_zone_0;	/* landing zone cylinder (LSB)	      */
		   u_char reserved1;
		   u_char reserved2;
		   u_char reserved3;
	    	} pgcode_4;
	    } params;
	} mode_sense;
    } data;
};

/*
 * Status Byte
 */
#define	SCSI_OK		0x00
#define	SCSI_CHECK		0x02
#define	SCSI_BUSY		0x08	
#define SCSI_INTERM		0x10
