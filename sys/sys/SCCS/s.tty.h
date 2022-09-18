h47565
s 00002/00002/00189
d D 8.7 95/01/09 18:16:21 cgd 43 42
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00000/00002/00191
d D 8.6 94/01/21 22:45:21 mckusick 42 41
c get rid of extraneous ifdef's
e
s 00005/00000/00188
d D 8.5 94/01/21 17:25:23 bostic 41 40
c add USL's copyright notice
e
s 00001/00001/00187
d D 8.4 93/09/23 15:29:38 bostic 40 39
c changes for 4.4BSD-Lite requested by USL
e
s 00065/00063/00123
d D 8.3 93/09/21 07:14:21 bostic 39 38
c changes for 4.4BSD-Lite requested by USL
e
s 00115/00079/00071
d D 8.2 93/09/05 09:43:02 bostic 38 37
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00148
d D 8.1 93/06/02 19:56:08 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00149
d D 7.14 92/02/17 23:45:32 mckusick 36 35
c include selinfo (for struct selinfo)
e
s 00002/00004/00147
d D 7.13 92/02/15 17:04:13 mckusick 35 34
c t_rsel and t_wsel are now struct selinfo, not proc pointers
e
s 00001/00001/00150
d D 7.12 92/02/05 18:36:50 mckusick 34 33
c t_param does return a value
e
s 00005/00002/00146
d D 7.11 92/02/05 17:44:07 torek 33 32
c add t_stop function, specific for sun4 (goes away with bstreams)
e
s 00001/00001/00147
d D 7.10 91/06/26 13:58:33 marc 32 31
c remove TS_HUPCLS
e
s 00015/00016/00133
d D 7.9 91/05/09 20:48:58 bostic 31 30
c delete last of the AT&T proprietary stuff; new copyright; att/bsd/shared
e
s 00000/00004/00149
d D 7.8 90/12/16 16:42:20 bostic 30 29
c kernel reorg
e
s 00009/00006/00144
d D 7.7 90/06/28 15:22:07 marc 29 28
c add generation number for revoke; col numbers stored as shorts; 
c 
e
s 00006/00001/00144
d D 7.6 90/04/04 22:21:56 karels 28 27
c add strings for sleep messages; increase ttyhog to 1K
e
s 00009/00001/00136
d D 7.5 89/11/20 18:10:49 marc 27 26
c controlling terminal is a vnode
e
s 00026/00027/00111
d D 7.4 89/10/26 20:42:37 marc 26 25
c cleanups, remove berknet, reorg
e
s 00000/00001/00138
d D 7.3 89/05/01 23:18:24 marc 25 24
c remove TS_NBIO
e
s 00030/00028/00109
d D 7.2 88/10/18 15:23:53 marc 24 23
c new terminal driver
e
s 00001/00001/00136
d D 7.1 86/06/04 23:30:03 mckusick 23 22
c 4.3BSD release version
e
s 00007/00001/00130
d D 6.4 85/06/08 15:10:22 mckusick 22 21
c Add copyright
e
s 00001/00000/00130
d D 6.3 84/12/31 12:42:45 bloom 21 20
c added window sizes to tty structure
e
s 00002/00002/00128
d D 6.2 84/08/28 17:29:41 bloom 20 19
c Change include paths.  No more ../h
e
s 00000/00000/00130
d D 6.1 83/07/29 06:14:30 sam 19 18
c 4.2 distribution
e
s 00000/00001/00130
d D 4.13 82/12/19 17:29:50 sam 18 17
c t_char not used
e
s 00056/00063/00075
d D 4.12 82/12/05 21:52:44 sam 17 16
c merge local state and flags; move ioctl stuff to other files
e
s 00001/00000/00137
d D 4.11 82/03/15 04:48:58 wnj 16 15
c name changes; get/sethostname
e
s 00001/00000/00136
d D 4.10 82/02/08 23:50:36 root 15 14
c add DMGET for DZ32
e
s 00001/00001/00135
d D 4.9 82/01/30 19:15:12 wnj 14 13
c restore sccs line
e
s 00019/00003/00117
d D 4.8 82/01/30 19:14:39 wnj 13 12
c concessiont to bk line disc
e
s 00015/00013/00105
d D 4.7 82/01/14 17:01:40 wnj 12 11
c more non-blocking stuff
e
s 00045/00075/00073
d D 4.6 81/10/17 16:14:39 wnj 11 10
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00001/00001/00147
d D 4.5 81/06/11 16:08:36 wnj 10 9
c /TTYHOG/s/256/255/ to fix problem with counting in chars in ttynew.c
e
s 00000/00001/00148
d D 4.4 81/04/19 13:36:48 wnj 9 8
c remove t_[io]bp
e
s 00001/00001/00148
d D 4.3 81/02/19 21:42:39 wnj 8 7
c %G%->%E%
e
s 00008/00003/00141
d D 4.2 80/12/17 11:46:48 wnj 7 6
c combined 750/780
e
s 00000/00000/00144
d D 4.1 80/11/09 17:01:53 bill 6 5
c stamp for 4bsd
e
s 00007/00002/00137
d D 3.5 80/09/27 17:55:21 bill 5 4
c speed dependent lo/hi water marks
e
s 00001/00001/00138
d D 3.4 80/06/07 03:01:36 bill 4 3
c %H%->%G%
e
s 00055/00116/00084
d D 3.3 80/05/15 17:18:19 bill 3 2
c new fields for new tty driver
e
s 00029/00002/00171
d D 3.2 80/05/08 10:14:51 bill 2 1
c added BNETLDIS
e
s 00173/00000/00000
d D 3.1 80/04/09 16:25:39 bill 1 0
c date and time created 80/04/09 16:25:39 by bill
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%H%	*/
E 4
I 4
D 8
/*	%M%	%I%	%G%	*/
E 8
I 8
D 13
/*	%M%	%I%	%E%	*/
E 13
I 13
D 14
/*	tty.h	4.8	82/01/20	*/
E 14
I 14
D 22
/*	%M%	%I%	%E%	*/
E 22
I 22
D 31
/*
D 23
 * Copyright (c) 1982 Regents of the University of California.
E 23
I 23
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 23
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
/*-
D 37
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 37
I 37
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
I 41
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 41
E 37
E 31
 *
I 31
 * %sccs.include.redist.c%
 *
E 31
 *	%W% (Berkeley) %G%
 */
E 22
E 14
E 13
E 8
E 4
I 3

D 7
#include <sgtty.h>
E 7
I 7
D 30
#ifdef KERNEL
D 17
#include "../h/ioctl.h"
E 17
I 17
D 20
#include "../h/ttychars.h"
#include "../h/ttydev.h"
E 20
I 20
D 26
#include "ttychars.h"
#include "ttydev.h"
E 26
I 24
#include "termios.h"
E 24
E 20
E 17
#else
E 30
E 7
D 17
#include <sys/ioctl.h>
E 17
I 17
D 26
#include <sys/ttychars.h>
#include <sys/ttydev.h>
E 26
I 24
#include <sys/termios.h>
I 36
D 38
#include <sys/select.h>			/* for struct selinfo */
E 38
I 38
#include <sys/select.h>		/* For struct selinfo. */
E 38
E 36
E 24
E 17
I 7
D 30
#endif
E 30
D 17
#include <sgtty.h>
E 17
E 7

E 3
/*
D 11
 * A clist structure is the head
 * of a linked list queue of characters.
D 3
 * The characters are stored in 4-word
 * blocks containing a link and several characters.
 * The routines getc and putc
E 3
I 3
 * The characters are stored in
 * blocks containing a link and CBSIZE (param.h)
 * characters.  The routines getc, putc, ... in prim.c
E 3
 * manipulate these structures.
E 11
I 11
D 17
 * A clist structure is the head of a linked list queue of characters.
 * The characters are stored in blocks containing a link and CBSIZE (param.h)
 * characters.  The routines in prim.c manipulate these structures.
E 17
I 17
D 31
 * A clist structure is the head of a linked list queue
 * of characters.  The characters are stored in blocks
 * containing a link and CBSIZE (param.h) characters. 
 * The routines in tty_subr.c manipulate these structures.
E 31
I 31
 * Clists are character lists, which is a variable length linked list
D 38
 * of cblocks, wiht a count of the number of characters in the list.
E 38
I 38
 * of cblocks, with a count of the number of characters in the list.
E 38
E 31
E 17
E 11
 */
D 11
struct clist
{
E 11
I 11
struct clist {
E 11
D 31
	int	c_cc;		/* character count */
	char	*c_cf;		/* pointer to first char */
	char	*c_cl;		/* pointer to last char */
E 31
I 31
D 38
	int	c_cc;		/* count of characters in queue */
	char	*c_cf;		/* first character/cblock */
	char	*c_cl;		/* last chararacter/cblock */
E 38
I 38
	int	c_cc;		/* Number of characters in the clist. */
	char	*c_cf;		/* Pointer to the first cblock. */
	char	*c_cl;		/* Pointer to the last cblock. */
E 38
E 31
};

/*
D 11
 * A tty structure is needed for
 * each UNIX character device that
 * is used for normal terminal IO.
 * The routines in tty.c handle the
 * common code associated with
D 3
 * these structures.
 * The definition and device dependent
 * code is in each driver. (kl.c dz.c)
E 3
I 3
 * these structures.  The definition
 * and device dependent code is in
 * each driver. (cons.c, dh.c, dz.c, kl.c)
E 11
I 11
D 17
 * Per-tty structre.
E 17
I 17
 * Per-tty structure.
E 17
 *
 * Should be split in two, into device and tty drivers.
 * Glue could be masks of what to echo and circular buffer
 * (low, high, timeout).
E 11
E 3
 */
D 3

struct tc {
	char	t_intrc;	/* interrupt */
	char	t_quitc;	/* quit */
	char	t_startc;	/* start output */
	char	t_stopc;	/* stop output */
	char	t_eofc;		/* end-of-file */
	char	t_brkc;		/* input delimiter (like nl) */
};

E 3
D 17
struct tty
{
E 17
I 17
struct tty {
E 17
D 2
	struct	clist t_rawq;	/* input chars right off device */
	struct	clist t_canq;	/* input chars after erase and kill */
E 2
I 2
D 11
	union {
		struct {
			struct	clist T_rawq;
			struct	clist T_canq;
		} t_t;
D 3
#define	t_rawq	t_nu.t_t.T_rawq	/* input chars right off device */
#define	t_canq	t_nu.t_t.T_canq	/* input chars after erase and kill */
#ifdef BERKNET
E 3
I 3
#define	t_rawq	t_nu.t_t.T_rawq		/* raw characters or partial line */
#define	t_canq	t_nu.t_t.T_canq		/* complete input lines */
E 3
		struct {
			struct	buf *T_bufp;
			char	*T_cp;
			int	T_inbuf;
I 3
			int	T_rec;
E 3
		} t_n;
D 3
#define	t_bufp	t_nu.t_n.T_bufp	/* buffer we ripped off for network */
#define	t_cp	t_nu.t_n.T_cp	/* pointer into the ripped off buffer */
#define	t_inbuf	t_nu.t_n.T_inbuf/* number chars in the magic buffer */
#endif
E 3
I 3
#define	t_bufp	t_nu.t_n.T_bufp		/* buffer allocated to protocol */
#define	t_cp	t_nu.t_n.T_cp		/* pointer into the ripped off buffer */
#define	t_inbuf	t_nu.t_n.T_inbuf	/* number chars in the buffer */
#define	t_rec	t_nu.t_n.T_rec		/* have a complete record */
E 3
	} t_nu;
E 2
	struct	clist t_outq;	/* output list to device */
	int	(*t_oproc)();	/* routine to start output */
	int	(*t_iproc)();	/* routine to start input */
	struct chan *t_chan;	/* destination channel */
	caddr_t	t_linep;	/* aux line discipline pointer */
	caddr_t	t_addr;		/* device address */
	dev_t	t_dev;		/* device number */
	short	t_flags;	/* mode, settable by ioctl call */
	short	t_state;	/* internal state, not visible externally */
	short	t_pgrp;		/* process group name */
	char	t_delct;	/* number of delimiters in raw q */
	char	t_line;		/* line discipline */
	char	t_col;		/* printing column of device */
	char	t_erase;	/* erase character */
	char	t_kill;		/* kill character */
	char	t_char;		/* character temporary */
	char	t_ispeed;	/* input speed */
	char	t_ospeed;	/* output speed */
E 11
I 11
D 13
	struct	clist t_rawq;		/* device */
	struct	clist t_canq;		/* tty */
E 13
I 13
D 26
	union {
		struct {
			struct	clist T_rawq;
			struct	clist T_canq;
		} t_t;
#define	t_rawq	t_nu.t_t.T_rawq		/* raw characters or partial line */
D 24
#define	t_canq	t_nu.t_t.T_canq		/* raw characters or partial line */
E 24
I 24
#define	t_canq	t_nu.t_t.T_canq		/* canonicalized lines */
E 24
		struct {
			struct	buf *T_bufp;
			char	*T_cp;
			int	T_inbuf;
			int	T_rec;
		} t_n;
#define	t_bufp	t_nu.t_n.T_bufp		/* buffer allocated to protocol */
#define	t_cp	t_nu.t_n.T_cp		/* pointer into the ripped off buffer */
#define	t_inbuf	t_nu.t_n.T_inbuf	/* number chars in the buffer */
#define	t_rec	t_nu.t_n.T_rec		/* have a complete record */
	} t_nu;
E 26
I 26
D 29
	struct	clist t_rawq;
E 29
I 29
D 38
	struct	clist t_rawq;		/* queues */
E 29
	struct	clist t_canq;
E 26
E 13
D 29
	struct	clist t_outq;		/* device */
E 29
I 29
	struct	clist t_outq;
E 29
D 33
	int	(*t_oproc)();		/* device */
I 24
	int	(*t_param)();		/* device */
E 33
I 33
	void	(*t_oproc)();		/* device */
E 38
I 38
	struct	clist t_rawq;		/* Device raw input queue. */
I 39
	long	t_rawcc;		/* Raw input queue statistics. */
E 39
	struct	clist t_canq;		/* Device canonical queue. */
I 39
	long	t_cancc;		/* Canonical queue statistics. */
E 39
	struct	clist t_outq;		/* Device output queue. */
D 39
	void	(*t_oproc)();		/* Device. */
E 38
#ifdef sun4c
D 38
	void	(*t_stop)();		/* device */
E 38
I 38
	void	(*t_stop)();		/* Device. */
E 38
#endif
D 34
	void	(*t_param)();		/* device */
E 34
I 34
D 38
	int	(*t_param)();		/* device */
E 34
E 33
E 24
D 35
	struct	proc *t_rsel;		/* tty */
D 12
				struct chan *T_CHAN;	/* ### */
E 12
I 12
	struct	proc *t_wsel;
E 35
I 35
	struct	selinfo t_rsel;		/* tty read/oob select */
	struct	selinfo t_wsel;		/* tty write select */
E 38
I 38
	int	(*t_param)();		/* Device. */
	struct	selinfo t_rsel;		/* Tty read/oob select. */
	struct	selinfo t_wsel;		/* Tty write select. */
E 38
E 35
E 12
D 24
				caddr_t	T_LINEP;	/* ### */
E 24
I 24
D 26
			caddr_t	T_LINEP;	/* ### */
E 26
I 26
	caddr_t	T_LINEP; 		/* XXX */
E 26
E 24
D 38
	caddr_t	t_addr;			/* ??? */
	dev_t	t_dev;			/* device */
E 38
I 38
	caddr_t	t_addr;			/* XXX */
E 39
I 39
	long	t_outcc;		/* Output queue statistics. */
D 43
	char	t_line;			/* Interface to device drivers. */
E 43
I 43
	u_char	t_line;			/* Interface to device drivers. */
E 43
E 39
	dev_t	t_dev;			/* Device. */
E 38
D 17
	short	t_flags;		/* some of both */
	short	t_state;		/* some of both */
E 17
I 17
D 24
	int	t_flags;		/* some of both */
E 24
I 24
D 26
	int	t_flags;		/* (old) some of both */
E 26
I 26
D 39
	int	t_flags;		/* (compat) some of both */
E 26
E 24
D 38
	int	t_state;		/* some of both */
E 38
I 38
	int	t_state;		/* Device and driver internal state. */
E 38
E 17
D 24
	short	t_pgrp;			/* tty */
E 24
I 24
D 26
	struct session *t_session;	/* tty */
E 26
I 26
	struct	session *t_session;	/* tty */
E 39
I 39
	int	t_state;		/* Device and driver (TS*) state. */
	int	t_flags;		/* Tty flags. */
E 39
E 26
D 27
	pid_t	t_pgid;			/* tty */
E 27
I 27
D 38
	struct	pgrp *t_pgrp;		/* foreground process group */
E 27
E 24
D 26
	char	t_delct;		/* tty */
E 26
I 17
D 18
	char	t_char;			/* tty */
E 18
E 17
	char	t_line;			/* glue */
D 29
	char	t_col;			/* tty */
D 17
	char	t_erase, t_kill;	/* tty */
	char	t_char;			/* tty */
E 17
D 24
	char	t_ispeed, t_ospeed;	/* device */
E 24
E 11
I 3
D 17
/* begin local */
E 17
D 11
	char	t_rocount;	/* chars input since a ttwrite() */
	char	t_rocol;	/* t_col when first input this line */
	struct	ltchars t_lchr;	/* local special characters */
	short	t_local;	/* local mode word */
	short	t_lstate;	/* local state bits */
E 11
I 11
	char	t_rocount, t_rocol;	/* tty */
E 29
I 29
	short	t_col;			/* tty */
	short	t_rocount, t_rocol;	/* tty */
E 29
D 17
	struct	ltchars t_lchr;		/* tty */
	short	t_local;		/* tty */
	short	t_lstate;		/* tty */
E 11
/* end local */
E 3
	union {
D 3
		struct tc t_chr;
E 3
I 3
D 11
		struct tchars t_chr;
E 3
		struct clist t_ctlq;
E 11
I 11
		struct tchars t_chr;	/* tty */
		struct clist T_CTLQ;
E 11
	} t_un;
E 17
I 17
D 24
	struct	ttychars t_chars;	/* tty */
E 24
I 24
	short	t_hiwat;		/* hi water mark */
	short	t_lowat;		/* low water mark */
E 24
I 21
	struct	winsize t_winsize;	/* window size */
E 21
D 24
/* be careful of tchars & co. */
#define	t_erase		t_chars.tc_erase
#define	t_kill		t_chars.tc_kill
#define	t_intrc		t_chars.tc_intrc
#define	t_quitc		t_chars.tc_quitc
#define	t_startc	t_chars.tc_startc
#define	t_stopc		t_chars.tc_stopc
#define	t_eofc		t_chars.tc_eofc
#define	t_brkc		t_chars.tc_brkc
#define	t_suspc		t_chars.tc_suspc
#define	t_dsuspc	t_chars.tc_dsuspc
#define	t_rprntc	t_chars.tc_rprntc
#define	t_flushc	t_chars.tc_flushc
#define	t_werasc	t_chars.tc_werasc
#define	t_lnextc	t_chars.tc_lnextc
E 24
I 24
	struct	termios t_termios;	/* termios state */
E 38
I 38
	struct	pgrp *t_pgrp;		/* Foreground process group. */
D 39
	char	t_line;			/* Glue. */
	short	t_col;			/* Tty. */
E 39
I 39
	struct	session *t_session;	/* Enclosing session. */
	struct	selinfo t_rsel;		/* Tty read/oob select. */
	struct	selinfo t_wsel;		/* Tty write select. */
	struct	termios t_termios;	/* Termios state. */
	struct	winsize t_winsize;	/* Window size. */
					/* Start output. */
	void	(*t_oproc) __P((struct tty *));
D 42
#ifdef sun4c
E 42
					/* Stop output. */
	void	(*t_stop) __P((struct tty *, int));
D 42
#endif
E 42
					/* Set hardware state. */
	int	(*t_param) __P((struct tty *, struct termios *));
	void	*t_sc;			/* XXX: net/if_sl.c:sl_softc. */
	short	t_column;		/* Tty output column. */
E 39
	short	t_rocount, t_rocol;	/* Tty. */
	short	t_hiwat;		/* High water mark. */
	short	t_lowat;		/* Low water mark. */
D 39
	struct	winsize t_winsize;	/* Window size. */
	struct	termios t_termios;	/* Termios state. */
E 38
#define	t_iflag		t_termios.c_iflag
#define	t_oflag		t_termios.c_oflag
E 39
I 39
	short	t_gen;			/* Generation number. */
};

#define	t_cc		t_termios.c_cc
E 39
#define	t_cflag		t_termios.c_cflag
I 39
#define	t_iflag		t_termios.c_iflag
#define	t_ispeed	t_termios.c_ispeed
E 39
#define	t_lflag		t_termios.c_lflag
#define	t_min		t_termios.c_min
D 39
#define	t_time		t_termios.c_time
#define	t_cc		t_termios.c_cc
D 38
#define t_ispeed	t_termios.c_ispeed
#define t_ospeed	t_termios.c_ospeed
	long	t_cancc;		/* stats */
E 38
I 38
#define	t_ispeed	t_termios.c_ispeed
E 39
I 39
#define	t_oflag		t_termios.c_oflag
E 39
#define	t_ospeed	t_termios.c_ospeed
D 39
	long	t_cancc;		/* Statistics. */
E 38
	long	t_rawcc;
	long	t_outcc;
I 29
D 38
	short	t_gen;			/* generation number */
E 38
I 38
	short	t_gen;			/* Generation number. */
E 38
E 29
E 24
E 17
I 7
D 9
	struct	buf *t_ibp, *t_obp;
E 9
E 7
};
E 39
I 39
#define	t_time		t_termios.c_time
E 39

D 17
#define	tun	tp->t_un.t_chr
I 3
#define	tlun	tp->t_lchr
E 3

E 17
D 3
/*
 * structure of arg for ioctl
 */
struct	ttiocb {
	char	ioc_ispeed;
	char	ioc_ospeed;
	char	ioc_erase;
	char	ioc_kill;
	short	ioc_flags;
};

E 3
D 31
#define	TTIPRI	28
#define	TTOPRI	29
E 31
I 31
D 38
#define	TTIPRI	25			/* sleep priority for tty reads */
#define	TTOPRI	26			/* sleep priority for tty writes */
E 38
I 38
#define	TTIPRI	25			/* Sleep priority for tty reads. */
#define	TTOPRI	26			/* Sleep priority for tty writes. */
E 38
E 31

D 3
#define	CERASE	'#'		/* default special characters */
#define	CEOT	004
E 3
I 3
D 17
#define	CTRL(c)	('c'&037)

/* default special characters */
#define	CERASE	'#'
#define	CEOT	CTRL(d)
E 3
#define	CKILL	'@'
#define	CQUIT	034		/* FS, cntl shift L */
#define	CINTR	0177		/* DEL */
D 3
#define	CSTOP	023		/* Stop output: ctl-s */
#define	CSTART	021		/* Start output: ctl-q */
E 3
I 3
#define	CSTOP	CTRL(s)
#define	CSTART	CTRL(q)
E 3
#define	CBRK	0377

E 17
D 31
/* limits */
E 31
D 5
#define	TTHIWAT	650
#define	TTLOWAT	125
E 5
I 5
D 26
#define	NSPEEDS	16
E 26
#define	TTMASK	15
I 17
#define	OBUFSIZ	100
D 28
#define	TTYHOG	255
E 28
I 28
#define	TTYHOG	1024
I 31

E 31
E 28
E 17
#ifdef KERNEL
D 24
short	tthiwat[NSPEEDS], ttlowat[NSPEEDS];
#define	TTHIWAT(tp)	tthiwat[(tp)->t_ospeed&TTMASK]
#define	TTLOWAT(tp)	ttlowat[(tp)->t_ospeed&TTMASK]
E 24
I 24
D 38
#define TTMAXHIWAT	roundup(2048, CBSIZE)
#define TTMINHIWAT	roundup(100, CBSIZE)
#define TTMAXLOWAT	256
#define TTMINLOWAT	32
E 24
I 17
extern	struct ttychars ttydefaults;
E 38
I 38
#define	TTMAXHIWAT	roundup(2048, CBSIZE)
#define	TTMINHIWAT	roundup(100, CBSIZE)
#define	TTMAXLOWAT	256
#define	TTMINLOWAT	32
E 38
E 17
D 24
#endif
E 24
I 24
D 31
#endif /*KERNEL*/
E 31
I 31
D 39
#endif /* KERNEL */
E 39
I 39
#endif
E 39
E 31
E 24
E 5
D 10
#define	TTYHOG	256
E 10
I 10
D 17
#define	TTYHOG	255
E 17
E 10

D 3
/* modes */
#define	TANDEM	01
#define	CBREAK	02
#define	LCASE	04
#define	ECHO	010
#define	CRMOD	020
#define	RAW	040
#define	ODDP	0100
#define	EVENP	0200
#define	NLDELAY	001400
#define	TBDELAY	006000
#define	XTABS	006000
#define	CRDELAY	030000
#define	VTDELAY	040000

/* Hardware bits */
E 3
I 3
D 17
/* hardware bits */
E 3
#define	DONE	0200
#define	IENABLE	0100

E 17
D 3
/* Internal state bits */
#define	TIMEOUT	01		/* Delay timeout in progress */
#define	WOPEN	02		/* Waiting for open to complete */
#define	ISOPEN	04		/* Device is open */
E 3
I 3
D 38
/* internal state bits */
D 11
#define	TIMEOUT	01		/* delay timeout in progress */
#define	WOPEN	02		/* waiting for open to complete */
#define	ISOPEN	04		/* device is open */
E 3
#define	FLUSH	010		/* outq has been flushed during DMA */
D 3
#define	CARR_ON	020		/* Software copy of carrier-present */
#define	BUSY	040		/* Output in progress */
#define	ASLEEP	0100		/* Wakeup when output done */
E 3
I 3
#define	CARR_ON	020		/* software copy of carrier-present */
#define	BUSY	040		/* output in progress */
#define	ASLEEP	0100		/* wakeup when output done */
E 3
#define	XCLUDE	0200		/* exclusive-use flag against open */
D 3
#define	TTSTOP	0400		/* Output stopped by ctl-s */
#define	HUPCLS	01000		/* Hang up upon last close */
E 3
I 3
#define	TTSTOP	0400		/* output stopped by ctl-s */
#define	HUPCLS	01000		/* hang up upon last close */
E 3
#define	TBLOCK	02000		/* tandem queue blocked */
#define	SPEEDS	04000		/* t_ispeed and t_ospeed used by driver */
D 7
#define	PROTO1	010000		/* reserved for line discipline */
E 7
I 7
#define	NDQB	010000
E 7
#define	EXTPROC	020000		/* external processor (kmc) */
#define	FSLEEP	040000		/* Wakeup on input framing */
D 7
#define	CNTLQ	0100000		/* interpret t_un as clist */
E 7
I 7
#define	BEXT	0100000		/* use (external) system buffers */
E 11
I 11
D 12
#define	TIMEOUT	000001		/* delay timeout in progress */
#define	WOPEN	000002		/* waiting for open to complete */
#define	ISOPEN	000004		/* device is open */
#define	FLUSH	000010		/* outq has been flushed during DMA */
#define	CARR_ON	000020		/* software copy of carrier-present */
#define	BUSY	000040		/* output in progress */
#define	ASLEEP	000100		/* wakeup when output done */
#define	XCLUDE	000200		/* exclusive-use flag against open */
#define	TTSTOP	000400		/* output stopped by ctl-s */
#define	HUPCLS	001000		/* hang up upon last close */
#define	TBLOCK	002000		/* tandem queue blocked */
#define	RCOLL	004000		/* collision in read select */
E 12
I 12
D 17
#define	TS_TIMEOUT	000001		/* delay timeout in progress */
#define	TS_WOPEN	000002		/* waiting for open to complete */
#define	TS_ISOPEN	000004		/* device is open */
#define	TS_FLUSH	000010		/* outq has been flushed during DMA */
#define	TS_CARR_ON	000020		/* software copy of carrier-present */
#define	TS_BUSY		000040		/* output in progress */
#define	TS_ASLEEP	000100		/* wakeup when output done */
#define	TS_XCLUDE	000200		/* exclusive-use flag against open */
#define	TS_TTSTOP	000400		/* output stopped by ctl-s */
#define	TS_HUPCLS	001000		/* hang up upon last close */
#define	TS_TBLOCK	002000		/* tandem queue blocked */
#define	TS_RCOLL	004000		/* collision in read select */
#define	TS_WCOLL	010000		/* collision in write select */
#define	TS_NBIO		020000		/* tty in non-blocking mode */
I 16
#define	TS_ASYNC	040000		/* tty in async i/o mode */
E 17
I 17
#define	TS_TIMEOUT	0x000001	/* delay timeout in progress */
#define	TS_WOPEN	0x000002	/* waiting for open to complete */
#define	TS_ISOPEN	0x000004	/* device is open */
#define	TS_FLUSH	0x000008	/* outq has been flushed during DMA */
#define	TS_CARR_ON	0x000010	/* software copy of carrier-present */
#define	TS_BUSY		0x000020	/* output in progress */
#define	TS_ASLEEP	0x000040	/* wakeup when output done */
#define	TS_XCLUDE	0x000080	/* exclusive-use flag against open */
#define	TS_TTSTOP	0x000100	/* output stopped by ctl-s */
D 32
#define	TS_HUPCLS	0x000200	/* hang up upon last close */
E 32
I 32
/* was	TS_HUPCLS	0x000200 	 * hang up upon last close */
E 32
#define	TS_TBLOCK	0x000400	/* tandem queue blocked */
D 35
#define	TS_RCOLL	0x000800	/* collision in read select */
#define	TS_WCOLL	0x001000	/* collision in write select */
E 35
D 25
#define	TS_NBIO		0x002000	/* tty in non-blocking mode */
E 25
#define	TS_ASYNC	0x004000	/* tty in async i/o mode */
/* state for intra-line fancy editing work */
#define	TS_BKSL		0x010000	/* state for lowercase \ work */
D 24
#define	TS_QUOT		0x020000	/* last character input was \ */
E 24
#define	TS_ERASE	0x040000	/* within a \.../ for PRTRUB */
#define	TS_LNCH		0x080000	/* next character is literal */
#define	TS_TYPEN	0x100000	/* retyping suspended input (PENDIN) */
D 24
#define	TS_CNTTB	0x200000	/* counting tab width; leave FLUSHO alone */
E 24
I 24
D 31
#define	TS_CNTTB	0x200000	/* counting tab width, leave FLUSHO alone */
E 31
I 31
#define	TS_CNTTB	0x200000	/* counting tab width, ignore FLUSHO */
E 38
I 38
D 39
/* Internal state bits. */
#define	TS_TIMEOUT	0x000001	/* Delay timeout in progress. */
#define	TS_WOPEN	0x000002	/* Waiting for open to complete. */
#define	TS_ISOPEN	0x000004	/* Indicates the device is open. */
#define	TS_FLUSH	0x000008	/* Outq has been flushed during DMA. */
#define	TS_CARR_ON	0x000010	/* Software image of carrier-present. */
#define	TS_BUSY		0x000020	/* Indicates output is in progress. */
#define	TS_ASLEEP	0x000040	/* Wakeup when output done. */
#define	TS_XCLUDE	0x000080	/* Exclusive-use flag against open. */
#define	TS_TTSTOP	0x000100	/* Output stopped by ctl-s. */
/* was	TS_HUPCLS	0x000200 	 * Hang up upon last close. */
#define	TS_TBLOCK	0x000400	/* Tandem queue blocked. */
#define	TS_ASYNC	0x004000	/* Tty in async i/o mode. */
E 39
I 39
/* These flags are kept in t_state. */
#define	TS_ASLEEP	0x00001		/* Process waiting for tty. */
#define	TS_ASYNC	0x00002		/* Tty in async I/O mode. */
#define	TS_BUSY		0x00004		/* Draining output. */
#define	TS_CARR_ON	0x00008		/* Carrier is present. */
#define	TS_FLUSH	0x00010		/* Outq has been flushed during DMA. */
#define	TS_ISOPEN	0x00020		/* Open has completed. */
#define	TS_TBLOCK	0x00040		/* Further input blocked. */
#define	TS_TIMEOUT	0x00080		/* Wait for output char processing. */
#define	TS_TTSTOP	0x00100		/* Output paused. */
#define	TS_WOPEN	0x00200		/* Open in progress. */
#define	TS_XCLUDE	0x00400		/* Tty requires exclusivity. */

E 39
/* State for intra-line fancy editing work. */
D 39
#define	TS_BKSL		0x010000	/* State for lowercase \ work. */
#define	TS_ERASE	0x040000	/* Within a \.../ for PRTRUB. */
#define	TS_LNCH		0x080000	/* Next character is literal. */
#define	TS_TYPEN	0x100000	/* Retyping suspended input (PENDIN). */
#define	TS_CNTTB	0x200000	/* Counting tab width, ignore FLUSHO. */
E 39
I 39
#define	TS_BKSL		0x00800		/* State for lowercase \ work. */
#define	TS_CNTTB	0x01000		/* Counting tab width, ignore FLUSHO. */
#define	TS_ERASE	0x02000		/* Within a \.../ for PRTRUB. */
#define	TS_LNCH		0x04000		/* Next character is literal. */
#define	TS_TYPEN	0x08000		/* Retyping suspended input (PENDIN). */
#define	TS_LOCAL	(TS_BKSL | TS_CNTTB | TS_ERASE | TS_LNCH | TS_TYPEN)
E 39
E 38
E 31
E 24
E 17
E 16
E 12
E 11
E 7

I 17
D 24
#define	TS_LOCAL	(TS_BKSL|TS_QUOT|TS_ERASE|TS_LNCH|TS_TYPEN|TS_CNTTB)
E 24
I 24
D 39
#define	TS_LOCAL	(TS_BKSL|TS_ERASE|TS_LNCH|TS_TYPEN|TS_CNTTB)
E 24

E 39
E 17
D 3
/*
 * tty ioctl commands
 */
#define	TIOCGETD	(('t'<<8)|0)
#define	TIOCSETD	(('t'<<8)|1)
#define	TIOCHPCL	(('t'<<8)|2)
#define	TIOCMODG	(('t'<<8)|3)
#define	TIOCMODS	(('t'<<8)|4)
#define	TIOCGETP	(('t'<<8)|8)
#define	TIOCSETP	(('t'<<8)|9)
#define	TIOCSETN	(('t'<<8)|10)
#define	TIOCEXCL	(('t'<<8)|13)
#define	TIOCNXCL	(('t'<<8)|14)
#define	TIOCFLUSH	(('t'<<8)|16)
#define	TIOCSETC	(('t'<<8)|17)
#define	TIOCGETC	(('t'<<8)|18)
#define	TIOCSBRK	(('t'<<8)|19)
#define	DIOCLSTN	(('d'<<8)|1)
#define	DIOCNTRL	(('d'<<8)|2)
#define	DIOCMPX		(('d'<<8)|3)
#define	DIOCNMPX	(('d'<<8)|4)
#define	DIOCSCALL	(('d'<<8)|5)
#define	DIOCRCALL	(('d'<<8)|6)
#define	DIOCPGRP	(('d'<<8)|7)
#define	DIOCGETP	(('d'<<8)|8)
#define	DIOCSETP	(('d'<<8)|9)
#define	DIOCLOSE	(('d'<<8)|10)
#define	DIOCTIME	(('d'<<8)|11)
#define	DIOCRESET	(('d'<<8)|12)
#define	DIOCSMETA	(('d'<<8)|13)
#define	DIOCMERGE	(('d'<<8)|14)
#define	DIOCICHAN	(('d'<<8)|15)
#define	DIOCPAD		(('d'<<8)|16)
#define	DIOCRMETA	(('d'<<8)|17)
#define	DIOCXOUT	(('d'<<8)|18)
#define	DIOCBMETA	(('d'<<8)|19)
#define	DIOCAMETA	(('d'<<8)|20)
#define	DIOCSBMETA	(('d'<<8)|21)
#define	FIOCLEX		(('f'<<8)|1)
#define	FIONCLEX	(('f'<<8)|2)
#define	MXLSTN		(('x'<<8)|1)
#define	MXNBLK		(('x'<<8)|2)
E 3
I 3
D 38
/* define partab character types */
E 38
I 38
/* Character type information. */
E 38
#define	ORDINARY	0
#define	CONTROL		1
#define	BACKSPACE	2
#define	NEWLINE		3
#define	TAB		4
#define	VTAB		5
#define	RETURN		6
I 26

struct speedtab {
D 38
        int sp_speed;
        int sp_code;
E 38
I 38
D 39
        int sp_speed;			/* Speed. */
        int sp_code;			/* Code. */
E 39
I 39
	int sp_speed;			/* Speed. */
	int sp_code;			/* Code. */
E 39
E 38
};
D 38
/*
 * Flags on character passed to ttyinput
 */
#define TTY_CHARMASK    0x000000ff      /* Character mask */
#define TTY_QUOTE       0x00000100      /* Character quoted */
#define TTY_ERRORMASK   0xff000000      /* Error mask */
#define TTY_FE          0x01000000      /* Framing error or BREAK condition */
#define TTY_PE          0x02000000      /* Parity error */
E 38
I 27

I 39
/* Modem control commands (driver). */
#define	DMSET		0
#define	DMBIS		1
#define	DMBIC		2
#define	DMGET		3

E 39
D 38
/*
D 29
 * Macros
E 29
I 29
 * Is tp controlling terminal for p
E 29
 */
#define isctty(p, tp)	((p)->p_session == (tp)->t_session && \
			 (p)->p_flag&SCTTY)
I 29
/*
 * Is p in background of tp
 */
E 29
#define isbackground(p, tp)	(isctty((p), (tp)) && \
				(p)->p_pgrp != (tp)->t_pgrp)
E 27
D 29

E 29
/*
 * Modem control commands (driver).
 */
E 38
I 38
/* Flags on a character passed to ttyinput. */
D 39
#define	TTY_CHARMASK    0x000000ff      /* Character mask */
#define	TTY_QUOTE       0x00000100      /* Character quoted */
#define	TTY_ERRORMASK   0xff000000      /* Error mask */
#define	TTY_FE          0x01000000      /* Framing error or BREAK condition */
#define	TTY_PE          0x02000000      /* Parity error */
E 39
I 39
#define	TTY_CHARMASK	0x000000ff	/* Character mask */
#define	TTY_QUOTE	0x00000100	/* Character quoted */
#define	TTY_ERRORMASK	0xff000000	/* Error mask */
#define	TTY_FE		0x01000000	/* Framing error or BREAK condition */
#define	TTY_PE		0x02000000	/* Parity error */
E 39

/* Is tp controlling terminal for p? */
D 39
#define	isctty(p, tp) \
	((p)->p_session == (tp)->t_session && (p)->p_flag&SCTTY)
E 39
I 39
#define	isctty(p, tp)							\
D 40
	((p)->p_session == (tp)->t_session && (p)->p_flag & SCTTY)
E 40
I 40
	((p)->p_session == (tp)->t_session && (p)->p_flag & P_CONTROLT)
E 40
E 39

/* Is p in background of tp? */
D 39
#define	isbackground(p, tp) \
E 39
I 39
#define	isbackground(p, tp)						\
E 39
	(isctty((p), (tp)) && (p)->p_pgrp != (tp)->t_pgrp)
D 39

/* Modem control commands (driver). */
E 38
#define	DMSET		0
#define	DMBIS		1
#define	DMBIC		2
#define	DMGET		3
E 39
I 28

#ifdef KERNEL
D 38
/* symbolic sleep message strings */
E 38
I 38
extern	struct ttychars ttydefaults;

/* Symbolic sleep message strings. */
E 38
extern	 char ttyin[], ttyout[], ttopen[], ttclos[], ttybg[], ttybuf[];
I 38

int	 b_to_q __P((char *cp, int cc, struct clist *q));
void	 catq __P((struct clist *from, struct clist *to));
void	 clist_init __P((void));
int	 getc __P((struct clist *q));
void	 ndflush __P((struct clist *q, int cc));
int	 ndqb __P((struct clist *q, int flag));
char	*nextc __P((struct clist *q, char *cp, int *c));
int	 putc __P((int c, struct clist *q));
int	 q_to_b __P((struct clist *q, char *cp, int cc));
int	 unputc __P((struct clist *q));

int	 nullmodem __P((struct tty *tp, int flag));
int	 tputchar __P((int c, struct tty *tp));
D 43
int	 ttioctl __P((struct tty *tp, int com, void *data, int flag));
E 43
I 43
int	 ttioctl __P((struct tty *tp, u_long com, void *data, int flag));
E 43
int	 ttread __P((struct tty *tp, struct uio *uio, int flag));
void	 ttrstrt __P((void *tp));
int	 ttselect __P((dev_t device, int rw, struct proc *p));
void	 ttsetwater __P((struct tty *tp));
int	 ttspeedtab __P((int speed, struct speedtab *table));
int	 ttstart __P((struct tty *tp));
void	 ttwakeup __P((struct tty *tp));
int	 ttwrite __P((struct tty *tp, struct uio *uio, int flag));
void	 ttychars __P((struct tty *tp));
int	 ttycheckoutq __P((struct tty *tp, int wait));
int	 ttyclose __P((struct tty *tp));
void	 ttyflush __P((struct tty *tp, int rw));
void	 ttyinfo __P((struct tty *tp));
int	 ttyinput __P((int c, struct tty *tp));
int	 ttylclose __P((struct tty *tp, int flag));
int	 ttymodem __P((struct tty *tp, int flag));
int	 ttyopen __P((dev_t device, struct tty *tp));
int	 ttyoutput __P((int c, struct tty *tp));
void	 ttypend __P((struct tty *tp));
void	 ttyretype __P((struct tty *tp));
void	 ttyrub __P((int c, struct tty *tp));
int	 ttysleep __P((struct tty *tp,
	    void *chan, int pri, char *wmesg, int timeout));
int	 ttywait __P((struct tty *tp));
int	 ttywflush __P((struct tty *tp));
E 38
#endif
E 28
E 26
E 3
I 2
D 17

D 3
/* ##bsb 1/12/80 (from stt) ioctl code for "capacity" call */
/* returns no. of bytes left before EOF or hang in cp_nbytes */
/* returns flag indicating EOF versus hang in cp_eof */

#define	FIOCAPACITY	(('f'<<8)|99)

struct	capacity {
	off_t	cp_nbytes;
	int	cp_eof;
};
E 3
I 3
/* define dmctl actions */
#define	DMSET		0
#define	DMBIS		1
#define	DMBIC		2
I 15
#define	DMGET		3
E 17
E 15
E 3
E 2
E 1
