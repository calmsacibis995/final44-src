h02581
s 00002/00002/00125
d D 8.1 93/06/06 22:29:52 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00002/00120
d D 3.29 92/11/10 11:49:47 edward 29 28
c checkpointing stuff
e
s 00001/00000/00121
d D 3.28 92/06/24 14:54:41 edward 28 27
c input error correction stuff
e
s 00003/00000/00118
d D 3.27 90/06/06 21:44:17 bostic 27 26
c fix contrib notice (Edward Wang)
e
s 00001/00011/00117
d D 3.26 90/06/02 15:21:26 bostic 26 25
c new copyright notice
e
s 00012/00002/00116
d D 3.25 89/09/15 17:48:49 edward 25 24
c compress control characters as well
e
s 00008/00001/00110
d D 3.24 89/08/27 05:52:43 edward 24 23
c cleanup of output of control characters
e
s 00001/00002/00110
d D 3.23 89/08/23 21:43:22 edward 23 22
c insert mode bug fix and cleanup
e
s 00008/00001/00104
d D 3.22 89/08/02 19:13:04 edward 22 21
c data compression and some other stuff
e
s 00001/00001/00104
d D 3.21 89/05/11 17:01:58 edward 21 20
c the xx layer added, handle "ic" differently, compression added to zapple
e
s 00010/00005/00095
d D 3.20 88/06/29 21:36:35 bostic 20 19
c install approved copyright notice
e
s 00005/00001/00095
d D 3.19 88/05/11 18:04:12 edward 19 18
c scrolling region, suggestion from Ray Moody (ray@j.cc.purdue.edu)
e
s 00011/00007/00085
d D 3.18 88/02/21 13:37:31 bostic 18 17
c written by Edward Wang; attach Berkeley specific copyright
e
s 00001/00001/00091
d D 3.17 87/10/02 19:36:56 edward 17 16
c changes from mips!dce, most compatibility stuff
e
s 00001/00000/00091
d D 3.16 87/05/18 12:11:16 edward 16 15
c use \n at bottom to scroll entire screen,
c use clear to eos to clear entire screen
e
s 00009/00003/00082
d D 3.15 85/09/20 15:15:17 edward 15 14
c correct padding
e
s 00002/00000/00083
d D 3.14 85/08/14 21:50:45 edward 14 13
c tt_setinsert and tt_setmodes added
e
s 00006/00000/00077
d D 3.13 85/04/24 16:14:31 edward 13 12
c copyright messages
e
s 00001/00001/00076
d D 3.12 84/11/19 16:48:51 edward 12 11
c syntax fix for v7 C compiler
e
s 00001/00001/00076
d D 3.11 84/05/23 01:58:12 edward 11 10
c new sccs id
e
s 00016/00005/00061
d D 3.10 84/03/03 22:46:24 edward 10 9
c interrupt driven input
e
s 00001/00001/00065
d D 3.9 83/12/17 15:38:33 edward 9 8
c WWM_GRP added
e
s 00028/00011/00038
d D 3.8 83/09/15 12:23:01 edward 8 7
c reworked tt stuff
e
s 00001/00000/00048
d D 3.7 83/08/24 17:46:15 edward 7 6
c knows about the bd flag now
e
s 00001/00000/00047
d D 3.6 83/08/17 17:41:00 edward 6 5
c better wrap around handling.
e
s 00013/00000/00034
d D 3.5 83/08/17 15:35:25 edward 5 4
c nicer termcap interface and use vs and ve strings in tth19.c
e
s 00001/00000/00033
d D 3.4 83/08/17 14:51:54 edward 4 3
c tt_availmodes
e
s 00002/00005/00031
d D 3.3 83/08/15 18:14:46 edward 3 2
c tt cleanup
e
s 00000/00000/00036
d D 3.2 83/08/11 17:23:15 edward 2 1
i
c last few day's work
e
s 00036/00000/00000
d D 3.1 83/08/09 18:35:15 edward 1 0
c date and time created 83/08/09 18:35:15 by edward
e
u
U
t
T
I 1
/*
D 11
 *	%W% %E%
E 11
I 11
D 18
 * %W% %G%
E 11
 */

I 8
/*
I 13
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 18
I 18
D 30
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
I 27
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 27
D 26
 * Redistribution and use in source and binary forms are permitted
D 20
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 20
I 20
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 20
 *
 *	%W% (Berkeley) %G%
E 18
 */

/*
E 13
 * Interface structure for the terminal drivers.
 */
E 8
struct tt {
I 8
		/* startup and cleanup */
E 8
D 22
	int (*tt_init)();
E 22
I 22
	int (*tt_start)();
I 29
	int (*tt_reset)();
E 29
E 22
D 3
	int (*tt_reset)();
	int (*tt_cleanup)();
	int (*tt_move)();
E 3
I 3
	int (*tt_end)();
E 3
D 8
	int (*tt_setinsert)();
	int (*tt_setmodes)();
E 8
I 8

		/* terminal functions */
E 8
I 3
	int (*tt_move)();
E 3
	int (*tt_insline)();
	int (*tt_delline)();
I 21
	int (*tt_inschar)();
I 23
	int (*tt_insspace)();
E 23
E 21
	int (*tt_delchar)();
D 8
	int (*tt_write)();
	int (*tt_putc)();
	int (*tt_blank)();
E 8
I 8
	int (*tt_write)();		/* write a whole block */
	int (*tt_putc)();		/* write one character */
E 8
	int (*tt_clreol)();
	int (*tt_clreos)();
	int (*tt_clear)();
I 19
	int (*tt_scroll_down)();
	int (*tt_scroll_up)();
	int (*tt_setscroll)();		/* set scrolling region */
E 19
I 14
D 23
	int (*tt_setinsert)();		/* set insert mode */
E 23
	int (*tt_setmodes)();		/* set display modes */
I 22
	int (*tt_set_token)();		/* define a token */
	int (*tt_put_token)();		/* refer to a defined token */
I 29
	int (*tt_compress)();		/* begin, end compression */
	int (*tt_checksum)();		/* compute checksum */
	int (*tt_checkpoint)();		/* checkpoint protocol */
E 29
I 28
	int (*tt_rint)();		/* input processing */
E 28
E 22
E 14
D 3
	int (*tt_window)();
	int (*tt_flash)();
E 3
D 8
	int tt_nrow;
	int tt_ncol;
I 4
	char tt_availmodes;
E 8
I 8

		/* internal variables */
	char tt_modes;			/* the current display modes */
	char tt_nmodes;			/* the new modes for next write */
	char tt_insert;			/* currently in insert mode */
D 23
	char tt_ninsert;		/* insert mode on next write */
E 23
	int tt_row;			/* cursor row */
	int tt_col;			/* cursor column */
I 19
	int tt_scroll_top;		/* top of scrolling region */
	int tt_scroll_bot;		/* bottom of scrolling region */
E 19

		/* terminal info */
	int tt_nrow;			/* number of display rows */
	int tt_ncol;			/* number of display columns */
D 21
	char tt_hasinsert;		/* has insert character */
E 21
	char tt_availmodes;		/* the display modes supported */
E 8
I 6
	char tt_wrap;			/* has auto wrap around */
I 7
	char tt_retain;			/* can retain below (db flag) */
I 25
	short tt_padc;			/* the pad character */
E 25
I 22
	int tt_ntoken;			/* number of compression tokens */
	int tt_token_min;		/* minimun token size */
	int tt_token_max;		/* maximum token size */
	int tt_set_token_cost;		/* cost in addition to string */
	int tt_put_token_cost;		/* constant cost */
I 29
	int tt_ack;			/* checkpoint ack-nack flag */
E 29
E 22
I 16
D 19
	char tt_noscroll;		/* terminal doesn't scroll (ns flag) */
E 19
E 16
I 8

		/* the frame characters */
E 8
E 7
E 6
E 4
D 9
	char *tt_frame;
E 9
I 9
	short *tt_frame;
I 25

D 29
		/* the output routine */
E 29
I 29
		/* ttflush() hook */
E 29
	int (*tt_flush)();
E 25
E 9
};
D 8

E 8
struct tt tt;

I 8
/*
I 25
 * tt_padc is used by the compression routine.
 * It is a short to allow the driver to indicate that there is no padding.
 */
#define TT_PADC_NONE 0x100

/*
E 25
 * List of terminal drivers.
 */
E 8
struct tt_tab {
	char *tt_name;
	int tt_len;
	int (*tt_func)();
};
D 8

E 8
D 17
struct tt_tab tt_tab[];
E 17
I 17
extern struct tt_tab tt_tab[];
E 17
I 5

/*
D 8
 * nicer interface to termcap routines
E 8
I 8
 * Clean interface to termcap routines.
I 10
 * Too may t's.
E 10
E 8
 */
char tt_strings[1024];		/* string buffer */
char *tt_strp;			/* pointer for it */

D 10
int tt_pc();			/* just putchar() */
int tt_sc();			/* *tt_strp++ = c */
char *tt_xgetstr();		/* tgetstr() and expand delays */
E 10
I 10
D 15
#define tttgetstr(s)	tgetstr((s), &tt_strp)
char *ttxgetstr();		/* tgetstr() and expand delays */
E 15
I 15
struct tt_str {
	char *ts_str;
	int ts_n;
};
E 15
E 10

I 15
struct tt_str *tttgetstr();
struct tt_str *ttxgetstr();	/* tgetstr() and expand delays */

E 15
D 10
#define tt_tgetstr(s)	tgetstr((s), &tt_strp)
#define tt_tputs(s, n)	tputs((s), (n), tt_pc)
E 10
I 10
int tttputc();
D 15
#define tttputs(s, n)	tputs((s), (n), tttputc)
E 15
I 15
#define tttputs(s, n)	tputs((s)->ts_str, (n), tttputc)
#define ttxputs(s)	ttwrite((s)->ts_str, (s)->ts_n)
E 15

/*
 * Buffered output without stdio.
D 24
 * These variables have different meanings from the ww_ob* variabels.
E 24
I 24
 * These variables have different meanings from the ww_ob* variables.
E 24
 * But I'm too lazy to think up different names.
 */
D 25
char tt_ob[512];
E 25
I 25
char *tt_ob;
E 25
char *tt_obp;
char *tt_obe;
D 12
#define ttputc(c)	(tt_obp < tt_obe ? *tt_obp++ = (c) \
E 12
I 12
#define ttputc(c)	(tt_obp < tt_obe ? (*tt_obp++ = (c)) \
E 12
D 25
				: (ttflush(), *tt_obp++ = (c)))
E 25
I 25
D 29
				: ((*tt.tt_flush)(), *tt_obp++ = (c)))
E 29
I 29
				: (ttflush(), *tt_obp++ = (c)))
E 29
E 25
I 24

/*
 * Convenience macros for the drivers
 * They require char.h
 */
#define ttctrl(c)	ttputc(ctrl(c))
#define ttesc(c)	(ttctrl('['), ttputc(c))
E 24
E 10
E 5
E 1
