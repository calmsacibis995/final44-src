/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	tty.h,v $
 * Revision 2.7  91/04/03  13:16:13  mbj
 * 	Omron changes[sic]
 * 
 * Revision 2.6  90/07/03  16:50:45  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:17:32  mrt]
 * 
 * Revision 2.5  89/03/09  22:09:01  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  17:57:24  gm0w
 * 	Made all CMUCS stuff unconditional except for
 * 	struct ttyloc.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.3  88/08/24  02:50:13  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:26:18  mwyoung]
 *
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_TTYLOC,CS_TTY => CS_GENERIC.
 *	[ V5.1(XF23) ]
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Added TS_LOGGEDIN and TS_LOGGEDOUT bit
 *	definitions.
 *	[ V5.1(F1) ]
 *
 * 21-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added definition of "TS_OUT" for dialout tty on Sun, but
 *	didn't define it to be the same number as Sun Unix does.
 *
 * 26-Aug-86  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Added TS_ONDELAY for X.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 09-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below.
 *	[V1(1)]
 *
 * 28-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Added t_ttyloc field to tty structure for
 *	recording terminal location information (V3.06h).
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)tty.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_TTY_H_
#define _SYS_TTY_H_

#include <sys/types.h>
#include <sys/ioctl.h>		/* for struct winsize */
#include <sys/ttychars.h>
#include <sys/ttydev.h>
#ifdef	CMU
#include <sys/ttyloc.h>
#endif	/* CMU */

#ifdef luna88k
#include <luna88k/jtermio.h>
#endif luna88k


/*
 * A clist structure is the head of a linked list queue
 * of characters.  The characters are stored in blocks
 * containing a link and CBSIZE (param.h) characters. 
 * The routines in tty_subr.c manipulate these structures.
 */
struct clist {
	int	c_cc;		/* character count */
	char	*c_cf;		/* pointer to first char */
	char	*c_cl;		/* pointer to last char */
};

/*
 * Per-tty structure.
 *
 * Should be split in two, into device and tty drivers.
 * Glue could be masks of what to echo and circular buffer
 * (low, high, timeout).
 */
struct tty {
	union {
		struct {
			struct	clist T_rawq;
			struct	clist T_canq;
		} t_t;
#define t_rawq	t_nu.t_t.T_rawq		/* raw characters or partial line */
#define t_canq	t_nu.t_t.T_canq		/* raw characters or partial line */
		struct {
			struct	buf *T_bufp;
			char	*T_cp;
			int	T_inbuf;
			int	T_rec;
		} t_n;
#define t_bufp	t_nu.t_n.T_bufp		/* buffer allocated to protocol */
#define t_cp	t_nu.t_n.T_cp		/* pointer into the ripped off buffer */
#define t_inbuf	t_nu.t_n.T_inbuf	/* number chars in the buffer */
#define t_rec	t_nu.t_n.T_rec		/* have a complete record */
	} t_nu;
	struct	clist t_outq;		/* device */
	int	(*t_oproc)();		/* device */
	struct	proc *t_rsel;		/* tty */
	struct	proc *t_wsel;
	caddr_t	T_LINEP;		/* ### */
	caddr_t	t_addr;			/* ??? */
	dev_t	t_dev;			/* device */
	int	t_flags;		/* some of both */
	int	t_state;		/* some of both */
	short	t_pgrp;			/* tty */
	char	t_delct;		/* tty */
	char	t_line;			/* glue */
	char	t_col;			/* tty */
	char	t_ispeed, t_ospeed;	/* device */
	char	t_rocount, t_rocol;	/* tty */
	struct	ttychars t_chars;	/* tty */
	struct	winsize t_winsize;	/* window size */
/* be careful of tchars & co. */
#define t_erase		t_chars.tc_erase
#define t_kill		t_chars.tc_kill
#define t_intrc		t_chars.tc_intrc
#define t_quitc		t_chars.tc_quitc
#define t_startc	t_chars.tc_startc
#define t_stopc		t_chars.tc_stopc
#define t_eofc		t_chars.tc_eofc
#define t_brkc		t_chars.tc_brkc
#define t_suspc		t_chars.tc_suspc
#define t_dsuspc	t_chars.tc_dsuspc
#define t_rprntc	t_chars.tc_rprntc
#define t_flushc	t_chars.tc_flushc
#define t_werasc	t_chars.tc_werasc
#define t_lnextc	t_chars.tc_lnextc
#ifdef	CMU
	struct ttyloc t_ttyloc;		/* terminal location (CMU) */
#endif	/* CMU */
#ifdef	luna
/* OMRON : for kanji output */
        struct jterm    t_jt;
        short   t_jstate;
	char    t_term;         /* terminal type */
	char    t_tmflag;       /* terminal flags */
	ushort  t_omron;        /* OMRON extended status flag : 04/27/86 */
	int     *t_kfptr;
#endif	luna
};

#define TTIPRI	28
#define TTOPRI	29

/* limits */
#define NSPEEDS	16
#define TTMASK	15
#define OBUFSIZ	100
#define TTYHOG	255

#ifdef	KERNEL
extern short	tthiwat[NSPEEDS], ttlowat[NSPEEDS];
#define TTHIWAT(tp)	tthiwat[(tp)->t_ospeed&TTMASK]
#define TTLOWAT(tp)	ttlowat[(tp)->t_ospeed&TTMASK]

extern	struct ttychars ttydefaults;
#endif	KERNEL

/* internal state bits */
#define TS_TIMEOUT	0x000001	/* delay timeout in progress */
#define TS_WOPEN	0x000002	/* waiting for open to complete */
#define TS_ISOPEN	0x000004	/* device is open */
#define TS_FLUSH	0x000008	/* outq has been flushed during DMA */
#define TS_CARR_ON	0x000010	/* software copy of carrier-present */
#define TS_BUSY		0x000020	/* output in progress */
#define TS_ASLEEP	0x000040	/* wakeup when output done */
#define TS_XCLUDE	0x000080	/* exclusive-use flag against open */
#define TS_TTSTOP	0x000100	/* output stopped by ctl-s */
#define TS_HUPCLS	0x000200	/* hang up upon last close */
#define TS_TBLOCK	0x000400	/* tandem queue blocked */
#define TS_RCOLL	0x000800	/* collision in read select */
#define TS_WCOLL	0x001000	/* collision in write select */
#define TS_NBIO		0x002000	/* tty in non-blocking mode */
#define TS_ASYNC	0x004000	/* tty in async i/o mode */
#define TS_ONDELAY	0x008000	/* device is open; software copy of 
 					 * carrier is not present */
#ifdef	sun
#define TS_OUT          0x010000        /* tty in use for dialout only */
					/* NOTE: This was 0x008000 in 
						 Sun Unix */
#endif	sun
/* state for intra-line fancy editing work */
#define TS_BKSL		0x010000	/* state for lowercase \ work */
#define TS_QUOT		0x020000	/* last character input was \ */
#define TS_ERASE	0x040000	/* within a \.../ for PRTRUB */
#define TS_LNCH		0x080000	/* next character is literal */
#define TS_TYPEN	0x100000	/* retyping suspended input (PENDIN) */
#define TS_CNTTB	0x200000	/* counting tab width; leave FLUSHO alone */

/* special CMU local state */
#define TS_LOGGEDIN	0x400000	/* terminal is "logged-in" */
#define TS_LOGGEDOUT	0x800000	/* login process has exited */


#define TS_LOCAL	(TS_BKSL|TS_QUOT|TS_ERASE|TS_LNCH|TS_TYPEN|TS_CNTTB)

/* define partab character types */
#define ORDINARY	0
#define CONTROL		1
#define BACKSPACE	2
#define NEWLINE		3
#define TAB		4
#define VTAB		5
#define RETURN		6

#ifdef	luna
/* OMRON extended flag (set in t_OMRON) : 04/27/86 */
#define PTY_TTY         040             /* this struct tty for pty */
#define	TS_TWOSB	0x400000	/* set two stop bits */

/* OMRON extended device command : 04/27/86 */
#define T_TXWAIT        20      /* flush up AS-octal trasmit buf */


/* For Kanji Output */
#define	ASCII	0		/* must send kout */
#define	KINPROC	0x01		/* kanji output in progress */
#define	GCPROC	0x02		/* gaiji output in progress */
#define	TBUFNE	0x04		/* tbuf not empty */

/* Kanji Codes */
#define	JIS1S	0x21		/* JIS code 1st byte start */
#define	JIS1E	0x7e		/* JIS code 1st byte end */
#define	JIS2S	JIS1S		/* JIS code 2nd byte start */
#define	JIS2E	JIS1E		/* JIS code 2nd byte end */
#define JISG1S	0x75		/* JIS gaiji code 1st byte start */
#define JISG1E	JIS1E		/* JIS gaiji code 1st byte end */
#define JISG2S	JIS2S		/* JIS gaiji code 2nd byte start */
#define JISG2E	JIS2E		/* JIS gaiji code 2nd byte end */

#define	SJISH1S	0x81		/* SJIS code (high) 1st byte start */
#define	SJISH1E	0x9f		/* SJIS code (high) 1st byte start */
#define	SJISL1S	0xe0		/* SJIS code (low) 1st byte end */
#define	SJISL1E	0xfc		/* SJIS code (low) 1st byte end */
#define	SJIS2S	0x40		/* SJIS code 2nd byte start */
#define	SJIS2E	0xfc		/* SJIS code 2nd byte end */
#define SJISG1S	0xeb		/* SJIS gaiji code 1st byte start */
#define SJISG1E	SJISL1E		/* SJIS gaiji code 1st byte end */
#define SJISG2S	SJIS2S		/* SJIS gaiji code 2nd byte start */
#define SJISG2E	SJIS2E		/* SJIS gaiji code 2nd byte end */

#define	_1_S	0xa1		/* Internal kanji code 1st byte start */
#define	_1_E	0xfe		/* Internal kanji code 1st byte end */
#define	_2_S	0xa1		/* Internal kanji code 2nd byte start */
#define	_2_E	0xfe		/* Internal kanji code 2nd byte end */
#define	G_1_S	0xf5		/* Gaiji code 1st byte start */
#define	G_1_E	0xfe		/* Gaiji code 1st byte end */
#define	G_2_S	0xa1		/* Gaiji code 2nd byte start */
#define	G_2_E	0xfe		/* Gaiji code 2nd byte end */
#define	H_K_1	0x8e		/* Han-kaku kana code 1st byte code */
#define	H_K_S	0xa0		/* Han-kaku kana code start byte */
#define	H_K_E	0xdf		/* Han-kaku kana code end byte */

#define	G_1_L	(G_1_E - G_1_S + 1)
#define	G_2_L	(G_2_E - G_2_S + 1)

#define	SJISGAS	3384		/* SJIS gaiji address table size */
#endif	luna

#endif	_SYS_TTY_H_
