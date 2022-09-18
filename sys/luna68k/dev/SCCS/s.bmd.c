h24883
s 00002/00002/00701
d D 8.1 93/06/10 22:16:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00205/00003/00498
d D 7.5 92/12/29 08:07:29 akito 5 4
c add bmd_printf()
e
s 00048/00115/00453
d D 7.4 92/12/20 12:36:54 akito 4 3
c add bmd_on(), bmd_off()
e
s 00004/00031/00564
d D 7.3 92/12/19 09:53:55 akito 3 2
c use fb_adjust() for screen origin adjustment
e
s 00002/00002/00593
d D 7.2 92/12/13 03:51:48 akito 2 1
c make kernel includes standard
e
s 00595/00000/00000
d D 7.1 92/11/17 17:04:50 akito 1 0
c date and time created 92/11/17 17:04:50 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
I 4

E 4
/*

 * bmd.c --- Bitmap-Display raw-level driver routines
 *
 *	by A.Fujita, SEP-09-1992
 */

I 5
#undef	BMD_PRINTF
E 5

D 2
#include "param.h"
#include "systm.h"
E 2
I 2
#include <sys/param.h>
#include <sys/systm.h>
E 2

extern u_short bmdfont[][20];

#define isprint(c)	( c < 0x20 ? 0 : 1)

/*
D 3
 *  RFCNT register
 */

struct bmd_rfcnt {
	short	rfc_hcnt;
	short	rfc_vcnt;
};


/*
E 3
 *  Width & Hight
 */

#define	PB_WIDTH	2048				/* Plane Width   (Bit) */
#define	PB_HIGHT	1024				/* Plane Hight   (Bit) */
#define PL_WIDTH	64				/* Plane Width  (long) */
#define PS_WIDTH	128				/* Plane Width  (long) */
#define P_WIDTH		256				/* Plane Width  (Byte) */

#define SB_WIDTH	1280				/* Screen Width  (Bit) */
#define	SB_HIGHT	1024				/* Screen Hight  (Bit) */
#define SL_WIDTH	40				/* Screen Width (Long) */
#define S_WIDTH		160				/* Screen Width (Byte) */

#define FB_WIDTH	12				/* Font Width    (Bit) */
#define FB_HIGHT	20				/* Font Hight    (Bit) */


#define NEXT_LINE(addr)				( addr +  (PL_WIDTH * FB_HIGHT) )
#define SKIP_NEXT_LINE(addr)			( addr += (PL_WIDTH - SL_WIDTH) )


void	bmd_add_new_line();

void	bmd_draw_char();
void	bmd_reverse_char();
void	bmd_erase_char();
void	bmd_erase_screen();
void	bmd_scroll_screen();

I 5
void	bmd_escape();
E 5

I 5

E 5
struct bmd_linec {
	struct bmd_linec *bl_next;
	struct bmd_linec *bl_prev;
	int	bl_col;
	int	bl_end;
	u_char	bl_line[128];
};

struct bmd_softc {
	int	bc_stat;
	char   *bc_raddr;
	char   *bc_waddr;
	int	bc_xmin;
	int	bc_xmax;
	int	bc_ymin;
	int	bc_ymax;
	int	bc_col;
	int	bc_row;
	struct bmd_linec *bc_bl;
	char	bc_escseq[8];
	char   *bc_esc;
	void  (*bc_escape)();
};

#define	STAT_NORMAL	0x0000
#define	STAT_ESCAPE	0x0001
D 4
#define	STAT_INSERT	0x0100
E 4
I 4
#define	STAT_STOP	0x0002
E 4

struct	bmd_softc bmd_softc;
struct	bmd_linec bmd_linec[52];

D 5
void	bmd_escape();
E 5
I 5
int	bmd_initflag = 0;
E 5
D 4
void	bmd_escape_0();
void	bmd_escape_1();
E 4

D 4

E 4
/*
 * Escape-Sequence
 */

I 4
#define push_ESC(p, c)		*(p)->bc_esc++ = c; *(p)->bc_esc = '\0'

E 4
void
bmd_escape(c)
	int c;
{
	register struct bmd_softc *bp = &bmd_softc;

D 4
	switch (c) {

	case '[':
		bp->bc_escape = bmd_escape_0;
		break;

	default:
		bp->bc_stat &= ~STAT_ESCAPE;
		bp->bc_esc = &bp->bc_escseq[0];
		bp->bc_escape = bmd_escape;
		break;
	}
}

void
bmd_escape_0(c)
	int c;
{
	register struct bmd_softc *bp = &bmd_softc;
	register struct	bmd_linec *bq = bp->bc_bl;

	switch (c) {

	case 'A':
		if (bp->bc_row > bp->bc_ymin) {
			bp->bc_row--;
		}
		break;

	case 'C':
		if (bq->bl_col < bp->bc_xmax - 1) {
			bq->bl_col++;
		}
		break;

	case 'K':
		if (bq->bl_col < bp->bc_xmax) {
			register int col;
			for (col = bq->bl_col; col < bp->bc_xmax; col++)
				bmd_erase_char(bp->bc_raddr,
					       bp->bc_waddr,
					       col, bp->bc_row);
		}
		bq->bl_end = bq->bl_col;
		break;

	case 'H':
		bq->bl_col = bq->bl_end = bp->bc_xmin;
		bp->bc_row = bp->bc_ymin;
		break;

	default:
/*
		*bp->bc_esc++ = c;
		bp->bc_escape = bmd_escape_1;
		return;
 */
		break;
	}

E 4
	bp->bc_stat &= ~STAT_ESCAPE;
	bp->bc_esc = &bp->bc_escseq[0];
D 4
	bp->bc_escape = bmd_escape;
E 4
I 4
/*	bp->bc_escape = bmd_escape;	*/
E 4
}

D 4
void
bmd_escape_1(c)
	int c;
{
	register struct bmd_softc *bp = &bmd_softc;
	register struct	bmd_linec *bq = bp->bc_bl;
	register int col = 0, row = 0;
	register char *p;

	switch (c) {

	case 'J':
		bp->bc_stat &= ~STAT_ESCAPE;
		bp->bc_esc = &bp->bc_escseq[0];
		bp->bc_escape = bmd_escape;
		break;

	case 'H':
		for (p = &bp->bc_escseq[0]; *p != ';'; p++)
			row = (row * 10) + (*p - 0x30);
		p++;
		for (p = &bp->bc_escseq[0]; p != bp->bc_esc; p++)
			col = (col * 10) + (*p - 0x30);

		bq->bl_col = col + bp->bc_xmin;
		bp->bc_row = row + bp->bc_ymin;

		bp->bc_stat &= ~STAT_ESCAPE;
		bp->bc_esc = &bp->bc_escseq[0];
		bp->bc_escape = bmd_escape;
		break;

	default:
		*bp->bc_esc++ = c;
		break;
	}
}


E 4
/*
 * Entry Routine
 */

bmdinit()
{
D 3
	volatile register struct bmd_rfcnt *bmd_rfcnt = (struct bmd_rfcnt *) 0xB1000000;
E 3
	register struct bmd_softc *bp = &bmd_softc;
	register struct bmd_linec *bq;
	register int i;
D 3
	struct bmd_rfcnt rfcnt;
E 3

I 3
	bp->bc_raddr = (char *) 0xB10C0008;		/* plane-0 hardware address */
	bp->bc_waddr = (char *) 0xB1080008;		/* common bitmap hardware address */

E 3
	/*
	 *  adjust plane position
	 */

D 3
	bp->bc_raddr = (char *) 0xB10C0008;		/* plane-0 hardware address */
	bp->bc_waddr = (char *) 0xB1080008;		/* common bitmap hardware address */
	rfcnt.rfc_hcnt = 7;				/* shift left   16 dot */
	rfcnt.rfc_vcnt = -27;				/* shift down    1 dot */
	*bmd_rfcnt = rfcnt;
E 3
I 3
	fb_adjust(7, -27);
E 3

	bp->bc_stat  = STAT_NORMAL;

	bp->bc_xmin  = 8;
	bp->bc_xmax  = 96;
	bp->bc_ymin  = 2;
	bp->bc_ymax  = 48;

	bp->bc_row = bp->bc_ymin;

	for (i = bp->bc_ymin; i < bp->bc_ymax; i++) {
		bmd_linec[i].bl_next = &bmd_linec[i+1];
		bmd_linec[i].bl_prev = &bmd_linec[i-1];
	}
	bmd_linec[bp->bc_ymax-1].bl_next = &bmd_linec[bp->bc_ymin];
	bmd_linec[bp->bc_ymin].bl_prev = &bmd_linec[bp->bc_ymax-1];

	bq = bp->bc_bl = &bmd_linec[bp->bc_ymin];
	bq->bl_col = bq->bl_end = bp->bc_xmin;

	bp->bc_col = bp->bc_xmin;

	bp->bc_esc = &bp->bc_escseq[0];
	bp->bc_escape = bmd_escape;

	bmd_erase_screen((u_long *) bp->bc_waddr);	/* clear screen */

							/* turn on  cursole */
	bmd_reverse_char(bp->bc_raddr,
			 bp->bc_waddr,
			 bq->bl_col, bp->bc_row);
I 5

	bmd_initflag = 1;
E 5
D 3
}

bmdadjust(hcnt, vcnt)
	short hcnt, vcnt;
{
	volatile register struct bmd_rfcnt *bmd_rfcnt = (struct bmd_rfcnt *) 0xB1000000;
	struct bmd_rfcnt rfcnt;

	printf("bmdadjust: hcnt = %d, vcnt = %d\n", hcnt, vcnt);

	rfcnt.rfc_hcnt = hcnt;			/* shift left   16 dot */
	rfcnt.rfc_vcnt = vcnt;			/* shift down    1 dot */

	*bmd_rfcnt = rfcnt;
E 3
}

bmdputc(c)
	register int c;
{
D 5
	register struct bmd_softc *bp = &bmd_softc;
	register struct bmd_linec *bq = bp->bc_bl;
E 5
I 5
	register struct bmd_softc *bp;
	register struct bmd_linec *bq;
E 5
	register int i;

I 5
	if (!bmd_initflag)
		bmdinit();

	bp = &bmd_softc;
	bq = bp->bc_bl;

E 5
I 4
							/* skip out, if STAT_STOP */
	if (bp->bc_stat & STAT_STOP)
		return(c);

E 4
	c &= 0x7F;
							/* turn off cursole */
	bmd_reverse_char(bp->bc_raddr,
			 bp->bc_waddr,
			 bq->bl_col, bp->bc_row);
							/* do escape-sequence */
I 4

E 4
	if (bp->bc_stat & STAT_ESCAPE) {
		*bp->bc_esc++ = c;
		(*bp->bc_escape)(c);
		goto done;
	}

	if (isprint(c)) {
		bmd_draw_char(bp->bc_raddr, bp->bc_waddr,
			      bq->bl_col, bp->bc_row, c);
		bq->bl_col++;
		bq->bl_end++;
		if (bq->bl_col >= bp->bc_xmax) {
			bq->bl_col = bq->bl_end = bp->bc_xmin;
			bp->bc_row++;
			if (bp->bc_row >= bp->bc_ymax) {
				bmd_scroll_screen((u_long *) bp->bc_raddr,
						  (u_long *) bp->bc_waddr,
						  bp->bc_xmin, bp->bc_xmax,
						  bp->bc_ymin, bp->bc_ymax);

				bp->bc_row = bp->bc_ymax - 1;
			}
		}
	} else {
		switch (c) {
		case 0x08:				/* BS */
			if (bq->bl_col > bp->bc_xmin) {
				bq->bl_col--;
			}
			break;

		case 0x09:				/* HT */
		case 0x0B:				/* VT */
			i = ((bq->bl_col / 8) + 1) * 8;
			if (i < bp->bc_xmax) {
				bq->bl_col = bq->bl_end = i;
			}
			break;

		case 0x0A:				/* NL */
			bp->bc_row++;
			if (bp->bc_row >= bp->bc_ymax) {
				bmd_scroll_screen((u_long *) bp->bc_raddr,
						  (u_long *) bp->bc_waddr,
						  bp->bc_xmin, bp->bc_xmax,
						  bp->bc_ymin, bp->bc_ymax);

				bp->bc_row = bp->bc_ymax - 1;
			}
			break;

		case 0x0D:				/* CR */
			bq->bl_col = bp->bc_xmin;
			break;

		case 0x1b:				/* ESC */
I 4
			bmdputc('<');
			bmdputc('E');
			bmdputc('S');
			bmdputc('C');
			bmdputc('>');
/*
E 4
			bp->bc_stat |= STAT_ESCAPE;
			*bp->bc_esc++ = 0x1b;
I 4
 */
E 4
			break;

		case 0x7F:				/* DEL */
			if (bq->bl_col > bp->bc_xmin) {
				bq->bl_col--;
				bmd_erase_char(bp->bc_raddr,
					       bp->bc_waddr,
					       bq->bl_col, bp->bc_row);
			}
			break;

		default:
			break;
		}
	}

 done:
							/* turn on  cursole */
	bmd_reverse_char(bp->bc_raddr,
			 bp->bc_waddr,
			 bq->bl_col, bp->bc_row);

	return(c);
}

D 4
bmdclear()
E 4
I 4
/*
 *
 */

bmd_on()
E 4
{
I 4
	bmdinit();
}

bmd_off()
{
E 4
	register struct bmd_softc *bp = &bmd_softc;
D 4
	register struct bmd_linec *bq = bp->bc_bl;
E 4

I 4
	bp->bc_stat |= STAT_STOP;
E 4
	bmd_erase_screen((u_long *) bp->bc_waddr);	/* clear screen */
I 4
}
E 4

D 4
	bq->bl_col = bq->bl_end = bp->bc_xmin;
	bp->bc_row = bp->bc_ymin;
E 4
I 4
bmd_clear()
{
	register struct bmd_softc *bp = &bmd_softc;
	register struct bmd_linec *bq = bp->bc_bl;
E 4

I 4
	bmd_erase_screen((u_long *) bp->bc_waddr);	/* clear screen */

E 4
	bmd_reverse_char(bp->bc_raddr,
			 bp->bc_waddr,
			 bq->bl_col, bp->bc_row);	/* turn on  cursole */
}

I 4
bmd_home()
{
	register struct bmd_softc *bp = &bmd_softc;
	register struct bmd_linec *bq = bp->bc_bl;
E 4

D 4
/*
 *
 */
E 4
I 4
	bmd_reverse_char(bp->bc_raddr,
			 bp->bc_waddr,
			 bq->bl_col, bp->bc_row);	/* turn off cursole */
E 4

D 4
void
bmd_add_new_line()
{
}
E 4
I 4
	bq->bl_col = bq->bl_end = bp->bc_xmin;
	bp->bc_row = bp->bc_ymin;
E 4

I 4
	bmd_reverse_char(bp->bc_raddr,
			 bp->bc_waddr,
			 bq->bl_col, bp->bc_row);	/* turn on  cursole */
}
E 4

/*
 *  charactor operation routines
 */

void
bmd_draw_char(raddr, waddr, col, row, c)
	char *raddr;
	char *waddr;
	int col;
	int row;
	int c;
{
	volatile register u_short  *p,  *q, *fp;
	volatile register u_long  *lp, *lq;
	register int i;

	fp = &bmdfont[c][0];

	switch (col % 4) {

	case 0:
		p = (u_short *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		q = (u_short *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		for (i = 0; i < FB_HIGHT; i++) {
			*q = (*p & 0x000F) | (*fp & 0xFFF0);
			p += 128;
			q += 128;
			fp++;
		}
		break;

	case 1:
		lp = (u_long *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		lq = (u_long *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		for (i = 0; i < FB_HIGHT; i++) {
			*lq = (*lp & 0xFFF000FF) | ((u_long)(*fp & 0xFFF0) << 4);
			lp += 64;
			lq += 64;
			fp++;
		}
		break;

	case 2:
		lp = (u_long *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 2 );
		lq = (u_long *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 2 );
		for (i = 0; i < FB_HIGHT; i++) {
			*lq = (*lp & 0xFF000FFF) | ((u_long)(*fp & 0xFFF0) << 8);
			lp += 64;
			lq += 64;
			fp++;
		}
		break;

	case 3:
		p = (u_short *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 4 );
		q = (u_short *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 4 );
		for (i = 0; i < FB_HIGHT; i++) {
			*q = (*p & 0xF000) | ((*fp & 0xFFF0) >> 4);
			p += 128;
			q += 128;
			fp++;
		}
		break;

	default:
		break;
	}
}

void
bmd_reverse_char(raddr, waddr, col, row)
	char *raddr;
	char *waddr;
	int col;
	int row;
{
	volatile register u_short  *p,  *q,  us;
	volatile register u_long  *lp, *lq,  ul;
	register int i;

	switch (col%4) {

	case 0:
		p = (u_short *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		q = (u_short *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		for (i = 0; i < FB_HIGHT; i++) {
			*q = (*p & 0x000F) | (~(*p) & 0xFFF0);
			p += 128;
			q += 128;
		}
		break;

	case 1:
		lp = (u_long *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		lq = (u_long *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ));
		for (i = 0; i < FB_HIGHT; i++) {
			*lq = (*lp & 0xFFF000FF) | (~(*lp) & 0x000FFF00);
			lp += 64;
			lq += 64;
		}
		break;

	case 2:
		lp = (u_long *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 2 );
		lq = (u_long *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 2 );
		for (i = 0; i < FB_HIGHT; i++) {
			*lq = (*lp & 0xFF000FFF) | (~(*lp) & 0x00FFF000);
			lp += 64;
			lq += 64;
		}
		break;

	case 3:
		p = (u_short *) ( raddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 4 );
		q = (u_short *) ( waddr + (( row * FB_HIGHT ) << 8 ) + (( col / 4 ) * 6 ) + 4 );
		for (i = 0; i < FB_HIGHT; i++) {
			*q = (*p & 0xF000) | (~(*p) & 0x0FFF);
			p += 128;
			q += 128;
		}
		break;

	default:
		break;
	}
}

void
bmd_erase_char(raddr, waddr, col, row)
	char *raddr;
	char *waddr;
	int col;
	int row;
{
	bmd_draw_char(raddr, waddr, col, row, 0);

	return;
}


/*
 * screen operation routines
 */

void
bmd_erase_screen(lp)
	volatile register u_long *lp;
{
	register int i, j;

	for (i = 0; i < SB_HIGHT; i++) {
		for (j = 0; j < SL_WIDTH; j++)
			*lp++ = 0;
		SKIP_NEXT_LINE(lp);
	}

	return;
}

void
bmd_scroll_screen(lp, lq, xmin, xmax, ymin, ymax)
	volatile register u_long *lp;
	volatile register u_long *lq;
	int xmin, xmax, ymin, ymax;
{
	register int i, j;

	lp += ((PL_WIDTH * FB_HIGHT) * (ymin + 1));
	lq += ((PL_WIDTH * FB_HIGHT) *  ymin);

	for (i = 0; i < ((ymax - ymin -1) * FB_HIGHT); i++) {
		for (j = 0; j < SL_WIDTH; j++) {
			*lq++ = *lp++;
		}
		lp += (PL_WIDTH - SL_WIDTH);
		lq += (PL_WIDTH - SL_WIDTH);
	}

	for (i = 0; i < FB_HIGHT; i++) {
		for (j = 0; j < SL_WIDTH; j++) {
			*lq++ = 0;
		}
		lq += (PL_WIDTH - SL_WIDTH);
	}

}
I 5


#ifdef	BMD_PRINTF

#include <machine/stdarg.h>

void		bmd_kprintf();
static char *	bmd_sprintn();

void
#ifdef __STDC__
bmd_printf(const char *fmt, ...)
#else
bmd_printf(fmt, va_alist)
	char *fmt;
#endif
{
	va_list ap;

	va_start(ap, fmt);
	bmd_kprintf(fmt, ap);
	va_end(ap);
}

/*
 * Scaled down version of printf(3).
 *
 * Two additional formats:
 *
 * The format %b is supported to decode error registers.
 * Its usage is:
 *
 *	printf("reg=%b\n", regval, "<base><arg>*");
 *
 * where <base> is the output base expressed as a control character, e.g.
 * \10 gives octal; \20 gives hex.  Each arg is a sequence of characters,
 * the first of which gives the bit number to be inspected (origin 1), and
 * the next characters (up to a control character, i.e. a character <= 32),
 * give the name of the register.  Thus:
 *
 *	kprintf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
 *
 * would produce output:
 *
 *	reg=3<BITTWO,BITONE>
 *
 * The format %r passes an additional format string and argument list
 * recursively.  Its usage is:
 *
 * fn(char *fmt, ...)
 * {
 *	va_list ap;
 *	va_start(ap, fmt);
 *	printf("prefix: %r: suffix\n", fmt, ap);
 *	va_end(ap);
 * }
 *
 * Space or zero padding and a field width are supported for the numeric
 * formats only.
 */
void
bmd_kprintf(fmt, ap)
	register const char *fmt;
	va_list ap;
{
	register char *p, *q;
	register int ch, n;
	u_long ul;
	int base, lflag, tmp, width;
	char padc;

	for (;;) {
		padc = ' ';
		width = 0;
		while ((ch = *(u_char *)fmt++) != '%') {
			if (ch == '\0')
				return;
			if (ch == '\n')
				bmdputc('\r');
			bmdputc(ch);
		}
		lflag = 0;
reswitch:	switch (ch = *(u_char *)fmt++) {
		case '0':
			padc = '0';
			goto reswitch;
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			for (width = 0;; ++fmt) {
				width = width * 10 + ch - '0';
				ch = *fmt;
				if (ch < '0' || ch > '9')
					break;
			}
			goto reswitch;
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'b':
			ul = va_arg(ap, int);
			p = va_arg(ap, char *);
			for (q = bmd_sprintn(ul, *p++, NULL); ch = *q--;)
				bmdputc(ch);

			if (!ul)
				break;

			for (tmp = 0; n = *p++;) {
				if (ul & (1 << (n - 1))) {
					bmdputc(tmp ? ',' : '<');
					for (; (n = *p) > ' '; ++p)
						bmdputc(n);
					tmp = 1;
				} else
					for (; *p > ' '; ++p)
						continue;
			}
			if (tmp)
				bmdputc('>');
			break;
		case 'c':
			bmdputc(va_arg(ap, int));
			break;
		case 'r':
			p = va_arg(ap, char *);
			bmd_kprintf(p, va_arg(ap, va_list));
			break;
		case 's':
			p = va_arg(ap, char *);
			while (ch = *p++)
				bmdputc(ch);
			break;
		case 'd':
			ul = lflag ? va_arg(ap, long) : va_arg(ap, int);
			if ((long)ul < 0) {
				bmdputc('-');
				ul = -(long)ul;
			}
			base = 10;
			goto number;
		case 'o':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 8;
			goto number;
		case 'u':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 10;
			goto number;
		case 'x':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 16;
number:			p = bmd_sprintn(ul, base, &tmp);
			if (width && (width -= tmp) > 0)
				while (width--)
					bmdputc(padc);
			while (ch = *p--)
				bmdputc(ch);
			break;
		default:
			bmdputc('%');
			if (lflag)
				bmdputc('l');
			/* FALLTHROUGH */
		case '%':
			bmdputc(ch);
		}
	}
}

/*
 * Put a number (base <= 16) in a buffer in reverse order; return an
 * optional length and a pointer to the NULL terminated (preceded?)
 * buffer.
 */
static char *
bmd_sprintn(ul, base, lenp)
	register u_long ul;
	register int base, *lenp;
{					/* A long in base 8, plus NULL. */
	static char buf[sizeof(long) * NBBY / 3 + 2];
	register char *p;

	p = buf;
	do {
		*++p = "0123456789abcdef"[ul % base];
	} while (ul /= base);
	if (lenp)
		*lenp = p - buf;
	return (p);
}
#endif
E 5
E 1
