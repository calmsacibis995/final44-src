h45541
s 00001/00011/00087
d D 7.4 90/06/28 22:01:29 bostic 4 3
c new copyright notice
e
s 00077/00154/00021
d D 7.3 90/06/28 15:26:59 marc 3 2
c NIXED
e
s 00061/00061/00114
d D 7.2 90/02/15 14:28:16 marc 2 1
c checkpoint work in progress (this file will probably go away anyway)...
e
s 00175/00000/00000
d D 7.1 90/02/08 18:45:10 marc 1 0
c date and time created 90/02/08 18:45:10 by marc
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1989 The Regents of the University of California.
E 3
I 3
 * Copyright (c) 1990 The Regents of the University of California.
E 3
 * All rights reserved.
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */
I 3

E 3
#ifndef _TSLEEP_
#define _TSLEEP_

D 3
#define	SLP_WAIT	0
#define	SLP_PAUSE	1
#define	SLP_LOGREAD	2
#define	SLP_SELECT	3
#define	SLP_TTYOUT	4
#define	SLP_TTY_NOTFG	5
#define	SLP_TTY_CARR	6
#define	SLP_TTYIN_NOTFG	7
#define	SLP_TTY_READ	8
#define	SLP_TTY_TSTP	9
#define	SLP_TTYOUT_NOTFG	10
#define	SLP_TTYOUT_CLIST	11
#define	SLP_PTS_OPEN	12
#define	SLP_PTC_WRITE	13
I 2
#define	SLP_SO_LINGER	14
#define	SLP_SO_SBWAIT	15
#define	SLP_SO_ACCEPT	16
#define	SLP_SO_ACCEPT2	17
#define	SLP_EXLCK	18
#define	SLP_SHLCK	19
#define	SLP_ISO_CONSOUT	20
#define	SLP_ISO_CONSCONN 21
#define	SLP_NFS_IOD	22
#define	SLP_SO_SBLOCK	23
#define	SLP_TU_OPN	24
#define	SLP_MFS		25
#define	SLP_HP_OPEN	26
#define	SLP_AD_GETW	27
#define	SLP_PCAT_OUT	28
#define	SLP_PCAT_CLIST	29
#define	SLP_DH_OPN	30
#define	SLP_DHU_OPN	31
#define	SLP_DMFL_ASLP	32
#define	SLP_DMFL_ERROR	33
#define	SLP_DMX_OPN	34
#define	SLP_DN_REG	35
#define	SLP_DN_PAUSE	36
#define	SLP_DZ_OPN	37
#define	SLP_IK_BUSY	38
#define	SLP_LP_OUT	39
#define	SLP_LP_CLIST	40
#define	SLP_NP_SLP	41
#define	SLP_PS_REFRESH	42
#define	SLP_PS_MAP	43
#define	SLP_TM_OPN	44
#define	SLP_UDA_OPN	45
#define SLP_UT_OPN	46
#define	SLP_UU_OPN	47
#define	SLP_VS_WAIT	48
#define SLP_VS_USRWAIT	49
#define	SLP_VS_START	50
#define SLP_VS_ABORT	51
#define SLP_VS_PWRUP	52
#define	SLP_VS_IOBCTL	53
#define	SLP_VS_FIB	54
#define	SLP_VS_FIBRET	55
#define	SLP_VS_INITF	56
#define SLP_VS_INITDEV	57
#define	SLP_DR_WAIT	58
#define	SLP_DR_RESET	59
#define	SLP_DR_ACTV	60
#define	SLP_HD_OPN	61
#define	SLP_MP_1OPN	62
#define	SLP_MP_POPN	63
#define	SLP_MP_OPN	64
#define	SLP_MP_1CLS	65
#define	SLP_MP_CLS	66
#define	SLP_MP_BRK	67
#define	SLP_MP_STDL	68
#define	SLP_MP_DLWAIT	69
#define	SLP_VD_OPN	70
#define	SLP_VX_OPN	71
#define	SLP_VX_CLS	72
#define	SLP_VX_PARAM	73
#endif
E 2

#ifdef SLP_MSGLIST
char *slp_mesg[] = {
	"wait",
	"pause",
	"log_read",
	"select",
	"ttyout",
	"tty_notfg",
	"tty_carrier",
	"ttyin_notfg",
	"ttread",
	"tty_tstp",
	"ttyout_notfg",
	"tty_clists",
	"tty_ptsopen",
	"tty_ptcwrite",	/* 13 */
D 2
#define	SLP_SO_LINGER	14
E 2
	"so_linger",
D 2
#define	SLP_SO_SBWAIT	15
E 2
	"so_sbwait",
D 2
#define	SLP_SO_ACCEPT	16
E 2
	"so_accept",
D 2
#define	SLP_SO_ACCEPT2	17
E 2
	"so_accept2",
D 2
#define	SLP_EXLCK	18
E 2
	"exlock",
D 2
#define	SLP_SHLCK	19
E 2
	"shlock",
D 2
#define	SLP_ISO_CONSOUT	20
E 2
	"iso_cons",
D 2
#define	SLP_ISO_CONSCONN 21
E 2
	"iso_consconn",
D 2
#define	SLP_NFS_IOD	22
E 2
	"nfs_iod",
D 2
#define	SLP_SO_SBLOCK	23
E 2
	"so_sblock",
D 2
#define	SLP_TU_OPN	24
E 2
	"tu58_opn",
D 2
#define	SLP_MFS		25
E 2
	"mfs_idle",
D 2
#define	SLP_HP_OPEN	26
E 2
	"hp_open",
D 2
#define	SLP_AD_GETW	27
E 2
	"ad_getw",
D 2
#define	SLP_PCAT_OUT	28
E 2
	"pcat_out",
D 2
#define	SLP_PCAT_CLIST	29
E 2
	"pcat_clist",
D 2
#define	SLP_DH_OPN	30
E 2
	"dh_opn",
D 2
#define	SLP_DHU_OPN	31
E 2
	"dhu_opn",
D 2
#define	SLP_DMFL_ASLP	32
E 2
	"dmfl_aslp",
D 2
#define	SLP_DMFL_ERROR	33
E 2
	"dmfl_err",
D 2
#define	SLP_DMX_OPN	34
E 2
	"dmx_opn",
D 2
#define	SLP_DN_REG	35
E 2
	"dn_reg",
D 2
#define	SLP_DN_PAUSE	36
E 2
	"dn_pause",
D 2
#define	SLP_DZ_OPN	37
E 2
	"dz_opn",
D 2
#define	SLP_IK_BUSY	38
E 2
	"ik_busy",
D 2
#define	SLP_LP_OUT	39
E 2
	"lp_out",
D 2
#define	SLP_LP_CLIST	40
E 2
	"lp_clist",
D 2
#define	SLP_NP_SLP	41
E 2
	"np_slp",
D 2
#define	SLP_PS_REFRESH	42
E 2
	"ps_refresh",
D 2
#define	SLP_PS_MAP	43
E 2
	"ps_map",
D 2
#define	SLP_TM_OPN	44
E 2
	"tm_opn",
D 2
#define	SLP_UDA_OPN	45
E 2
	"uda_opn",
D 2
#define SLP_UT_OPN	46
E 2
	"ut_opn",
D 2
#define	SLP_UU_OPN	47
E 2
	"uu_opn",
D 2
#define	SLP_VS_WAIT	48
E 2
	"vs_wait",
D 2
#define SLP_VS_USRWAIT	49
E 2
	"vs_usrwait",
D 2
#define	SLP_VS_START	50
E 2
	"vs_start",
D 2
#define SLP_VS_ABORT	51
E 2
	"vs_abort",
D 2
#define SLP_VS_PWRUP	52
E 2
	"vs_pwrup",
D 2
#define	SLP_VS_IOBCTL	53
E 2
	"vs_iobctl",
D 2
#define	SLP_VS_FIB	54
E 2
	"vs_fib",
D 2
#define	SLP_VS_FIBRET	55
E 2
	"vs_fibret",
D 2
#define	SLP_VS_INITF	56
E 2
	"vs_initf",
D 2
#define SLP_VS_INITDEV	57
E 2
	"vs_initdev",
D 2
#define	SLP_DR_WAIT	58
E 2
	"dr_wait",
D 2
#define	SLP_DR_RESET	59
E 2
	"dr_reset",
D 2
#define	SLP_DR_ACTV	60
E 2
	"dr_actv",
D 2
#define	SLP_HD_OPN	61
E 2
	"hd_opn",
D 2
#define	SLP_MP_1OPN	62
E 2
	"mp_1opn",
D 2
#define	SLP_MP_POPN	63
E 2
	"mp_popn",
D 2
#define	SLP_MP_OPN	64
E 2
	"mp_opn",
D 2
#define	SLP_MP_1CLS	65
E 2
	"mp_1cls",
D 2
#define	SLP_MP_CLS	66
E 2
	"mp_cls",
D 2
#define	SLP_MP_BRK	67
E 2
	"mp_brk",
D 2
#define	SLP_MP_STDL	68
E 2
	"mp_stdl",
D 2
#define	SLP_MP_DLWAIT	69
E 2
	"mp_dlwait",
D 2
#define	SLP_VD_OPN	70
E 2
	"vd_opn",
D 2
#define	SLP_VX_OPN	71
E 2
	"vx_opn",
D 2
#define	SLP_VX_CLS	72
E 2
	"vx_cls",
D 2
#define	SLP_VX_PARAM	73
E 2
	"vx_param",
};
E 3
I 3
#define tsleep ttsleep	/* tmp tsleep, does longjmp */
#define SLP_WAIT	"child"		/* "wait" */
#define SLP_LOGREAD	"syslog"	/* "log_read" */
#define SLP_SELECT	"select"	/* "select" */
#define SLP_TTYOUT	"ttyout"	/* "ttyout" */
#define SLP_TTY_NOTFG	"tty"		/* "tty_notfg" */
#define SLP_TTY_CARR	"ttyopn"	/* "tty_carrier" */
#define SLP_TTYIN_NOTFG	"ttyin"		/* "ttyin_notfg" */
#define SLP_TTY_READ	"ttyin"		/* "ttread" */
#define SLP_TTY_TSTP	"ttyin"		/* "tty_tstp" */
#define SLP_TTYOUT_NOTFG	"ttyout"	/* "ttyout_notfg" */
#define SLP_TTYOUT_CLIST	"ttybuf"	/* "tty_clists" */
#define SLP_PTS_OPEN	"ttyopn"	/* "tty_ptsopen" */
#define SLP_PTC_WRITE	"ttyout"	/* "tty_ptcwrite" */
#define SLP_SO_LINGER	"netcls"	/* "so_linger" */
#define SLP_SO_SBWAIT	"netio"		/* "so_sbwait" */
#define SLP_SO_ACCEPT	"netcon"	/* "so_accept" */
#define SLP_SO_ACCEPT2	"netcon"	/* "so_accept2" */
#define SLP_EXLCK	"flock"		/* "exlock" */
#define SLP_SHLCK	"flock"		/* "shlock" */
#define SLP_ISO_CONSOUT	"netcon"	/* "iso_cons" */
#define SLP_ISO_CONSCONN	"netcon"	/* "iso_consconn" */
#define SLP_NFS_IOD	"nfsio"		/* "nfs_iod" */
#define SLP_SO_SBLOCK	"netio"		/* "so_sblock" */
#define SLP_TU_OPN	"devopn"	/* "tu58_opn" */
#define SLP_MFS		"mfsio"		/* "mfs_idle" */
#define SLP_FIFO_OPEN	"devopn"	/* "fifo_open" */
#define SLP_HP_OPEN	"devopn"	/* "hp_open" */
#define SLP_AD_GETW	"devi"		/* "ad_getw" */
#define SLP_PCAT_OUT	"devout"		/* "pcat_out" */
#define SLP_PCAT_CLIST	"ttybuf"	/* "pcat_clist" */
#define SLP_DH_OPN	"ttyopn"	/* "dh_opn" */
#define SLP_DHU_OPN	"ttyopn"	/* "dhu_opn" */
#define SLP_DMFL_ASLP	"ttyout"		/* "dmfl_aslp" */
#define SLP_DMFL_ERROR	"ttyout"		/* "dmfl_err" */
#define SLP_DMX_OPN	"devopn"	/* "dmx_opn" */
#define SLP_DN_REG	"ttyout"	/* "dn_reg" */
#define SLP_DN_PAUSE	"ttyout"	/* "dn_pause" */
#define SLP_DZ_OPN	"ttyopn"	/* "dz_opn" */
#define SLP_IK_BUSY	"devout"		/* "ik_busy" */
#define SLP_LP_OUT	"devout"	/* "lp_out" */
#define SLP_LP_CLIST	"ttybuf"	/* "lp_clist" */
#define SLP_NP_SLP	"devin"		/* "np_slp" */
#define SLP_PS_REFRESH	"devout"		/* "ps_refresh" */
#define SLP_PS_MAP	"devout"		/* "ps_map" */
#define SLP_TM_OPN	"devopn"		/* "tm_opn" */
#define SLP_UDA_OPN	"devopn"	/* "uda_opn" */
#define SLP_UT_OPN	"devopn"		/* "ut_opn" */
#define SLP_UU_OPN	"devopn"		/* "uu_opn" */
#define SLP_VS_WAIT	"devout"		/* "vs_wait" */
#define SLP_VS_USRWAIT	"devout"		/* "vs_usrwait" */
#define SLP_VS_START	"devout"	/* "vs_start" */
#define SLP_VS_ABORT	"devout"	/* "vs_abort" */
#define SLP_VS_PWRUP	"devout"	/* "vs_pwrup" */
#define SLP_VS_IOBCTL	"devout"	/* "vs_iobctl" */
#define SLP_VS_FIB	"devout"	/* "vs_fib" */
#define SLP_VS_FIBRET	"devout"	/* "vs_fibret" */
#define SLP_VS_INITF	"devout"	/* "vs_initf" */
#define SLP_VS_INITDEV	"devout"	/* "vs_initdev" */
#define SLP_DR_WAIT	"devout"	/* "dr_wait" */
#define SLP_DR_RESET	"devout"	/* "dr_reset" */
#define SLP_DR_ACTV	"devout"	/* "dr_actv" */
#define SLP_HD_OPN	"devopn"	/* "hd_opn" */
#define SLP_MP_1OPN	"ttyopn"	/* "mp_1opn" */
#define SLP_MP_POPN	"ttyopn"	/* "mp_popn" */
#define SLP_MP_OPN	"ttyopn"	/* "mp_opn" */
#define SLP_MP_1CLS	"ttycls"	/* "mp_1cls" */
#define SLP_MP_CLS	"ttycls"	/* "mp_cls" */
#define SLP_MP_BRK	"ttyout"	/* "mp_brk" */
#define SLP_MP_STDL	"ttyout"	/* "mp_stdl" */
#define SLP_MP_DLWAIT	"ttyout"	/* "mp_dlwait" */
#define SLP_VD_OPN	"devopn"	/* "vd_opn" */
#define SLP_VX_OPN	"ttyopn"	/* "vx_opn" */
#define SLP_VX_CLS	"ttycls"	/* "vx_cls" */
#define SLP_VX_PARAM	"ttyout"	/* "vx_param" */
E 3
D 2
#endif
E 2
#endif
E 1
