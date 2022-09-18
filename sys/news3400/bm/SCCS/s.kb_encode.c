h50950
s 00002/00002/00365
d D 8.1 93/06/10 23:49:25 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00367
d D 7.5 93/03/09 23:33:12 utashiro 5 4
c cleanup header and machine dependency.
e
s 00014/00014/00355
d D 7.4 92/12/17 02:34:59 utashiro 4 3
c make kernel includes standard
e
s 00002/00000/00367
d D 7.3 92/12/16 21:12:05 utashiro 3 2
c Added declarations of static functions.
e
s 00003/00001/00364
d D 7.2 92/07/28 17:31:19 bostic 2 1
c update from Kazumasa Utashiro
e
s 00365/00000/00000
d D 7.1 92/06/04 15:55:38 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
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
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: kb_encode.c,v 4.300 91/06/09 06:14:51 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "../include/fix_machine_type.h"
E 4
I 4
D 5
#include <machine/fix_machine_type.h>
E 4

E 5
#ifdef IPC_MRX
D 4
#include "../../h/param.h"
I 2
#include "../../h/systm.h"
E 2
#include "../../h/types.h"
#include "../../h/ioctl.h"
#include "../../iop/keyboard.h"
#include "../../iop/kbreg.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <news3400/iop/keyboard.h>
#include <news3400/iop/kbreg.h>
E 4
#else
D 4
#include "param.h"
I 2
#include "systm.h"
E 2
#include "types.h"
#include "ioctl.h"
#include "../iop/keyboard.h"
#include "../iop/kbreg.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <news3400/iop/keyboard.h>
#include <news3400/iop/kbreg.h>
E 4
#endif
D 4
#include "malloc.h"
E 4
I 4
#include <sys/malloc.h>
E 4

extern int tmode;
extern int country;
extern Pfk_table pfk_table[];
extern Pfk_table pfk_init[];
extern Key_table *key_table_addr;

int	kbd_status;
int	shifttype;
extern int iscaps;

I 3
static kbd_shift(), kbd_pfunc(), kbd_normal(), put_kana();

E 3
/*
 *	kbd_encode(c)
 *		int c;		keyboard address code
 *
 *	kbd_encode() converts keyboard address code to character code.
 *	kbd_encode() calls back machine dependent function
 *
 *		put_code(buf, cnt)
 *			char *buf;	encoded characters
 *			int cnt;	character count
 *
 *	to store encoded data.
 */
kbd_encode(c)
	register int c;
{
	register Key_table *kp;
	register int c_mask;

	c_mask = c & 0x7f;
	c &= 0xff;
	if (c_mask > N_KEY)
		return (0);
	kp = &key_table_addr[c_mask];
	if (c & OFF)
		kp->key_flags &= ~KEY_PRESS;
	else if ((kp->key_flags & KEY_PRESS) && 
	    ((kbd_status & KBD_NOTREPT) || (kp->key_flags & NOT_REPT)))
		return (0);
	else
		kp->key_flags |= KEY_PRESS;

	if (kp->key_flags & (PSH_SHFT|SW_SHFT)) {
		kbd_shift(c);
		return (0);
	}
	if ((kp->key_flags & ALT_FUNC) && (kbd_status & KBD_ALT) ||
	    (kp->key_flags & PRG_FUNC))
		return (kbd_pfunc(c));
	return (kbd_normal(c));
}


#define KFLAGSW(a, b)	((a) ? (kbd_status |= (b)) : (kbd_status &= ~(b)))
#define	LOCKTYPE(a, b)	(shifttype = ((a) ? (a) : (b)))

static
kbd_shift(c)
	register int c;
{
	register Key_table *kp = &key_table_addr[c & 0x7f];
	register int push = (c & OFF) == 0;

	switch (kp->normal_code) {

	case S_CTRL:
		KFLAGSW(push, KBD_CTRL);
		break;

	case S_RSHFT:
		KFLAGSW(push, KBD_RSHIFT);
		break;

	case S_LSHFT:
		KFLAGSW(push, KBD_LSHIFT);
		break;

	case S_ALT:
		KFLAGSW(push, KBD_ALT);
		break;

	case S_CAPS:
		if (push) {
			kbd_status ^= KBD_CAPS;
			LOCKTYPE(iscaps, CAPSLOCK);
		}
		break;

	case S_AN:
		if (push) {
			kbd_status &= ~KBD_KANA;
		}
		break;

	case S_KANA:
		if (push) {
			switch (country) {
			case K_JAPANESE_J:
				kbd_status |= KBD_KANA;
			default:
				break;
			}
		}
		break;

	case S_ALTGR:
		KFLAGSW(push, KBD_ALTGR);
		break;

	default:
		break;

	}
	return (0);
}

static
kbd_pfunc(c)
	register int c;
{
	register Pfk_table *kp;

	if (c & OFF)
		return (0);
	for (kp = pfk_table; kp < pfk_table + N_PFK; kp++) {
		if (kp->pfk_addr != c)
			continue;
		if (kbd_status & KBD_SHIFT)
			return (put_code(kp->pfk_shift.key_string,
			    kp->pfk_shift.key_length));
		return (put_code(kp->pfk_normal.key_string,
		    kp->pfk_normal.key_length));
	}
	return (0);
}

#define	PUT(cond, code, len)		((cond) ? put_code(code, len) : 0)
#define	PUT_KANA(cond, code, len)	((cond) ? put_kana(code, len) : 0)

static
kbd_normal(c)
	int c;
{
	register Key_table *kp = &key_table_addr[c & 0x7f];

	if (c & OFF)
		return (0);
	if (kbd_status & KBD_ALT)
		return (PUT(kp->key_flags & A, &kp->alt_code, 1));
	if (kbd_status & KBD_CTRL)
		return (PUT(kp->key_flags & C, &kp->ctrl_code, 1));
	if (kbd_status & KBD_ALTGR)
		return (PUT(kp->key_flags & G, &kp->kana_code, 1));
	if (kbd_status & KBD_KANA) {
		if (kbd_status & KBD_SHIFT)
			return (PUT_KANA(kp->key_flags & J, &kp->kshft_code, 1));
		return (PUT_KANA(kp->key_flags & K, &kp->kana_code, 1));
	}
	if (kbd_status & KBD_CAPS) {
		if ((kbd_status & KBD_SHIFT) && (kp->key_flags & S)) {
			if (kp->key_flags & CAP_LOCK) {
				switch (shifttype) {

				case CAPSLOCK:
					return (put_code(&kp->shift_code, 1));

				case SHIFTLOCK:
				case SHIFTLOCK2:
					return (put_code(&kp->normal_code, 1));

				default:
					return (0);
				}
			}
			switch (shifttype) {

			case CAPSLOCK:
			case SHIFTLOCK:
				return (put_code(&kp->shift_code, 1));

			case SHIFTLOCK2:
				return (put_code(&kp->normal_code, 1));

			default:
				return (0);
			}
		}
		if (kp->key_flags & N) {
			if (kp->key_flags & CAP_LOCK)
				return (put_code(&kp->shift_code, 1));
			switch (shifttype) {

			case CAPSLOCK:
			case SHIFTLOCK:
				return (put_code(&kp->normal_code, 1));

			case SHIFTLOCK2:
				return (put_code(&kp->shift_code, 1));

			default:
				return (0);
			}
		}
	}
	if (kbd_status & KBD_SHIFT)
 		return (PUT(kp->key_flags & S, &kp->shift_code, 1));
	return (PUT(kp->key_flags & N, &kp->normal_code, 1));
}

kbd_string(cmd, p)
	int cmd;
	register Pfk_string *p;
{
	register Key_string *pk;

	if (p->pfk_num < 0 || p->pfk_num >= N_PFK)
		return (0);
	switch (p->pfk_shift) {

	case PF_NORMAL:
		pk = &pfk_table[p->pfk_num].pfk_normal;
		break;

	case PF_SHIFT:
		pk = &pfk_table[p->pfk_num].pfk_shift;
		break;

	default:
		return (0);
	}
	switch (cmd) {

	case KIOCSETS:
		if (pk->key_string != NULL) {
			free(pk->key_string, M_DEVBUF);
			pk->key_string = NULL;
			pk->key_length = 0;
		}
		if (pk->key_length = p->pfk_string.key_length) {
			pk->key_string =
			    (char *)malloc(p->pfk_string.key_length, M_DEVBUF, M_WAITOK);
			bcopy(p->pfk_string.key_string, pk->key_string,
			    p->pfk_string.key_length);
		} else
			pk->key_string = NULL;
		bcopy(p->pfk_string.key_string, pk->key_string,
		    p->pfk_string.key_length);
		pk->key_length = p->pfk_string.key_length;
		break;

	case KIOCGETS:
		p->pfk_string.key_length =
D 2
		    MIN(p->pfk_string.key_length, pk->key_length);
E 2
I 2
		    min(p->pfk_string.key_length, pk->key_length);
E 2
		bcopy(pk->key_string, p->pfk_string.key_string,
		    p->pfk_string.key_length);
		break;

	default:
		return (0);
	}
	return (0);
}

kbd_init()
{
	int i;
	Pfk_string pfk_buf;

	for (i = 0; i < N_PFK; i++) {
		pfk_table[i].pfk_addr = pfk_init[i].pfk_addr;
		if (pfk_init[i].pfk_normal.key_length > 0) {
			pfk_buf.pfk_num = i;
			pfk_buf.pfk_shift = PF_NORMAL;
			pfk_buf.pfk_string = pfk_init[i].pfk_normal;
			kbd_string(KIOCSETS, &pfk_buf);
		}
		if (pfk_init[i].pfk_shift.key_length > 0) {
			pfk_buf.pfk_num = i;
			pfk_buf.pfk_shift = PF_SHIFT;
			pfk_buf.pfk_string = pfk_init[i].pfk_shift;
			kbd_string(KIOCSETS, &pfk_buf);
		}
	}
	kbd_status = 0;
}

kbd_repeat(f)
	int f;
{

	if (f)
		kbd_status &= ~KBD_NOTREPT;
	else
		kbd_status |= KBD_NOTREPT;
	return (0);
}


static
put2char(c1, c2)
	int c1, c2;
{
	char buf[2];

	buf[0] = c1;
	buf[1] = c2;
	return (put_code(buf, 2));
}

#define	SS2		0x8e

static
put_kana(s, len)
	register u_char *s;
	int len;
{
	register int i;
	register u_char *p;
	u_char eucbuf[8];

	if (len <= 0)
		return (0);
#ifdef KM_EUC
	if ((tmode == KM_EUC) && ((*s >= 0xa1) && (*s <= 0xdf))) {
		p = eucbuf;
		for (i = len; i > 0; i--) {
			*p++ = SS2;
			*p++ = *s++;
		}
		return (put_code(eucbuf, len * 2));
	}
#endif /* KM_EUC */
	return (put_code(s, len));
}
E 1
