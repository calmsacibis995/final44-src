h05616
s 00002/00002/00117
d D 8.1 93/06/10 22:44:45 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00071/00008/00048
d D 7.3 93/02/25 16:42:26 sklower 3 2
c many insertions from Dirk Husemann for 802.2 class 2
e
s 00001/00011/00055
d D 7.2 90/06/28 21:30:42 bostic 2 1
c new copyright notice
e
s 00066/00000/00000
d D 7.1 89/09/04 17:31:17 karels 1 0
c new file by sklower
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1988 Regents of the University of California.
E 3
I 3
D 4
 * Copyright (c) 1988, 1993 Regents of the University of California.
E 3
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *      %W% (Berkeley) %G%
 */

/*
 * IEEE 802.2 Link Level Control headers, for use in conjunction with
 * 802.{3,4,5} media access control methods.
 *
 * Headers here do not use bit fields due to shortcommings in many
 * compilers.
 */

struct llc {
	u_char	llc_dsap;
	u_char	llc_ssap;
	union {
	    struct {
		u_char control;
		u_char format_id;
		u_char class;
		u_char window_x2;
	    } type_u;
	    struct {
		u_char num_snd_x2;
		u_char num_rcv_x2;
	    } type_i;
	    struct {
		u_char control;
		u_char num_rcv_x2;
	    } type_s;
	    struct {
I 3
	        u_char control;
		struct frmrinfo {
			u_char rej_pdu_0;
			u_char rej_pdu_1;
			u_char frmr_control;
			u_char frmr_control_ext;
			u_char frmr_cause;
		} frmrinfo;
	    } type_frmr;
	    struct {
E 3
		u_char control;
		u_char org_code[3];
		u_short ether_type;
	    } type_snap;
I 3
	    struct {
		u_char control;
		u_char control_ext;
	    } type_raw;
E 3
	} llc_un;
};
D 3
#define llc_control llc_un.type_u.control
#define llc_fid llc_un.type_u.format_id
#define llc_class llc_un.type_u.class
#define llc_window llc_un.type_u.window_x2
E 3
I 3
#define llc_control            llc_un.type_u.control
#define	llc_control_ext        llc_un.type_raw.control_ext
#define llc_fid                llc_un.type_u.format_id
#define llc_class              llc_un.type_u.class
#define llc_window             llc_un.type_u.window_x2
#define llc_frmrinfo           llc_un.type_frmr.frmrinfo
#define llc_frmr_pdu0          llc_un.type_frmr.frmrinfo.rej_pdu0
#define llc_frmr_pdu1          llc_un.type_frmr.frmrinfo.rej_pdu1
#define llc_frmr_control       llc_un.type_frmr.frmrinfo.frmr_control
#define llc_frmr_control_ext   llc_un.type_frmr.frmrinfo.frmr_control_ext
#define llc_frmr_cause         llc_un.type_frmr.frmrinfo.frmr_control_ext
E 3

I 3
/*
 * Don't use sizeof(struct llc_un) for LLC header sizes
 */
#define LLC_ISFRAMELEN 4
#define LLC_UFRAMELEN  3
#define LLC_FRMRLEN    7

/*
 * Unnumbered LLC format commands
 */
E 3
#define LLC_UI		0x3
#define LLC_UI_P	0x13
D 3
#define LLC_XID		0xaf
#define LLC_XID_P	0xbf
E 3
I 3
#define LLC_DISC	0x43
#define	LLC_DISC_P	0x53
#define LLC_UA		0x63
#define LLC_UA_P	0x73
E 3
#define LLC_TEST	0xe3
#define LLC_TEST_P	0xf3
I 3
#define LLC_FRMR	0x87
#define	LLC_FRMR_P	0x97
#define LLC_DM		0x0f
#define	LLC_DM_P	0x1f
#define LLC_XID		0xaf
#define LLC_XID_P	0xbf
#define LLC_SABME	0x6f
#define LLC_SABME_P	0x7f
E 3

D 3
#define LLC_ISO_LSAP	0xfe
E 3
I 3
/*
 * Supervisory LLC commands
 */
#define	LLC_RR		0x01
#define	LLC_RNR		0x05
#define	LLC_REJ		0x09

/*
 * Info format - dummy only
 */
#define	LLC_INFO	0x00

/*
 * ISO PDTR 10178 contains among others
 */
#define LLC_X25_LSAP	0x7e
E 3
#define LLC_SNAP_LSAP	0xaa
I 3
#define LLC_ISO_LSAP	0xfe






E 3
E 1
