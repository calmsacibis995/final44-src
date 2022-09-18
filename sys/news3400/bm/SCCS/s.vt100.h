h30223
s 00002/00002/00198
d D 8.1 93/06/10 23:49:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00200
d D 7.4 93/03/09 23:33:15 utashiro 4 3
c cleanup header and machine dependency.
e
s 00002/00002/00200
d D 7.3 92/12/17 02:35:04 utashiro 3 2
c make kernel includes standard
e
s 00000/00009/00202
d D 7.2 92/07/28 17:31:21 bostic 2 1
c update from Kazumasa Utashiro
e
s 00211/00000/00000
d D 7.1 92/06/04 15:55:40 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: vt100.h,v 4.300 91/06/09 06:14:58 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "../include/fix_machine_type.h"
E 3
I 3
D 4
#include <machine/fix_machine_type.h>
E 3

E 4
/*
 *  vt100 emulator header
 */

D 3
#include "../bm/vt100esc.h"
E 3
I 3
#include <news3400/bm/vt100esc.h>
E 3

/*
 *  terminal mode
 */
#define	KAM		0x00000001	/*  k-action(lock or not) */
#define	IRM		0x00000002	/*  insert mode 	*/
#define	SRM		0x00000004	/*  local echo disable	*/
#define	LNM		0x00000008	/*  new line mode	*/
#define	DECCKM		0x00000010	/*  cursor application	*/
#define	DECCOLM		0x00000020	/*  132 column mode	*/
#define	DECSCLM		0x00000040	/*  jump scroll		*/
#define	DECSCNM		0x00000080	/*  screen reverse	*/
#define	DECOM		0x00000100	/*  origin mode		*/
#define	DECAWM		0x00000200	/*  auto wrap mode	*/
#define	DECARM		0x00000400	/*  auto repeat mode	*/
#define	DECKPA_NM	0x00000800	/*  ten key application	*/
#define	DECCSR_ACTV	0x00001000	/*  cursor active	*/


/*
 *  cursor attributes
 */
#define	NORMALM		0x0000		/*  attributes clear	*/
#define	BOLD		0x0001		/*  bold	*/
#define	USCORE		0x0002		/*  under line	*/
#define	BLINK		0x0004		/*  blinking	*/
#define	REVERSE		0x0008		/*  reverse	*/


/*
 *  cursor current status
 */
#define	ESCAPE	0x00000001		/*  processing esc sequence	*/
#define	WRAP	0x00000002		/*  local flag in addch()	*/
#define	SKANJI	0x00000004		/*  receive kanji shift jis code  */
#define	JKANJI	0x00000008		/*  kanji mode (JIS)	*/
#define EKANA	0x00000010
#define EKANJI	0x00000020

/*
 *  shift jis code conversion table
 */
#define	JVR1S	0x81	/*  starting of vertical range  1	*/
#define	JVR1E	0x9f	/*  ending of vertical range  1		*/
#define	JVR2S	0xe0	/*  starting of vertical range  2	*/
#define JVR2E	0xfc	/*  ending of vertical range  2		*/
#define	JHR1S	0x40	/*  starting of horizontal range  1	*/
#define	JHR1E	0x7e	/*  ending of horizontal range  1	*/
#define	JHR2S	0x80	/*  starting of horizontal range  2	*/
#define	JHR2E	0x9e	/*  ending of horizontal range  2	*/
#define	JHR3S	0x9f	/*  starting of horizontal range  3	*/
#define JHR3E	0xfc	/*  ending of horizontal range  3	*/

/*
 *  EUC conversion table
 */
#define SS2	0x8e
#define	CS1S	0xa1
#define CS1E	0xfe


/*
 *  screen width
 */
#define	TOP_M	1		/*  screen top margin	*/
#define	LFT_M	1		/*  screen left margin	*/

/*
 *  default value
 */
#define	DIM_CNT_DFLT	10	/*  initial dimmer count	*/
#define	BELL_LEN_DFLT	32	/*  bell length	*/

/*
 *  max and min value of above values
 */
#define	FONT_W_MAX	16
#define	FONT_W_MIN	5
#define	FONT_H_MAX	32
#define	FONT_H_MIN	8
#define	CHAR_W_MAX	16
#define	CHAR_W_MIN	6
#define	CHAR_H_MAX	32
#define	CHAR_H_MIN	9
#define	CH_POS_MAX	32
#define	CH_POS_MIN	0
#define	UL_POS_MAX	32
#define	UL_POS_MIN	0
#define	SCR_W_MAX	1024
#define	SCR_W_MIN	0
#define	SCR_H_MAX	1024
#define	SCR_H_MIN	0
#define	X_OFST_MAX	1024
#define	X_OFST_MIN	0
#define	Y_OFST_MAX	1024
#define	Y_OFST_MIN	0
#define	RIT_M_MAX	136
#define	RIT_M_MIN	2
#define	BTM_M_MAX	100
#define	BTM_M_MIN	1
#define	DIM_CNT_MAX	32767
#define	DIM_CNT_MIN	1
#define	BELL_LEN_MAX	19200
#define	BELL_LEN_MIN	1

/*
 *  scroll region
 */
struct	region {
	int	top_margin;
	int	btm_margin;
};

/*
 *  cursor position and status
 */
struct	cursor {
	int	csr_x;		/*  cursor position x	*/
	int	csr_y;		/*  cursor position y	*/
	lPoint	csr_p;		/*  cursor point	*/
	int	csr_attributes;	/*  cursor attributes	*/
};

/*
 *  screen information
 */
typedef	struct	screen {
	int	s_term_mode;
	int	s_current_stat;		/*  current status	*/
	struct	esc_sequence  *s_estp;	/*  for escape handler	*/
	int	(*s_esc_handler)();
	int	s_plane;		/*  color bitmap plane #  */
	int	s_bgcol;		/*  back ground color	*/
	char	s_tab_pos[RIT_M_MAX + 1];	/*  tab stop position	*/
	struct	cursor	s_csr;
	struct	region	s_region;
} SCREEN;

#define	ESC_BUF_SIZ	32
#define	PARM_BUF_SIZ	8
#define	AN_BUF_SIZ	32

extern unsigned short fbuf[256];
extern int	fp;
extern int	fpn;
extern lPoint	fpp;
extern int	fpa;

#define	INVALID	-1
#define	TRUE	1
#define	FALSE	0

#define	C_MESS_SIZ	32

D 2
/* MIN and MAX are imported from ../h/param.h */
#ifndef MIN
#define	MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define	MAX(a,b) (((a)>(b))?(a):(b))
#endif
#define	ABS(a)		((a) < 0 ? -(a) : (a))

E 2
extern	int	fcolor;
extern	int	bcolor;

extern	lRectangle	char_r1;
extern	lRectangle	char_r2;
extern	lRectangle	font_r1;
extern	lRectangle	font_r2;

extern	int	font_len1;
extern	int	font_len2;

extern	int	char_w;
extern	int	char_h;
extern	int	char_wx2;
extern	int	font_w;
extern	int	font_h;
extern	int	ch_pos;
extern	int	ul_pos;
extern	int	x_ofst;
extern	int	y_ofst;
extern	int	rit_m;
extern	int	btm_m;
extern	int	scr_w;
extern	int	scr_h;
extern	int	dim_cnt;
extern	int	bell_len;
extern	int	a_dim_on;
E 1
