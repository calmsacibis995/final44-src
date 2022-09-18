h10547
s 00002/00002/00561
d D 8.1 93/06/10 23:49:22 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00088/00559
d D 7.3 93/03/09 23:33:11 utashiro 3 2
c cleanup header and machine dependency.
e
s 00016/00016/00631
d D 7.2 92/12/17 02:34:58 utashiro 2 1
c make kernel includes standard
e
s 00647/00000/00000
d D 7.1 92/06/04 15:55:37 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: kb_ctrl.c,v 4.300 91/06/09 06:14:49 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 *	Keyboard driver
 */

D 2
#include "../include/fix_machine_type.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 2

E 3
#ifdef IPC_MRX
D 2
#include "../../h/ioctl.h"
#include "../../iop/keyboard.h"
#include "../../iop/kbreg.h"
E 2
I 2
#include <sys/ioctl.h>
#include <news3400/iop/keyboard.h>
#include <news3400/iop/kbreg.h>
E 2
#else
D 2
#include "ioctl.h"
#include "param.h"
#include "systm.h"
#include "types.h"
#include "../iop/keyboard.h"
#include "../iop/kbreg.h"
E 2
I 2
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <news3400/iop/keyboard.h>
#include <news3400/iop/kbreg.h>
E 2
#endif

extern int tmode;
extern int kbd_status;

int iscaps = 0;
int change_country = K_JAPANESE_J;
int country;

extern Key_table default_table[];

#ifdef CPU_SINGLE
extern Key_table key_table[];
Key_table *key_table_addr = key_table;
#endif

#ifdef CPU_DOUBLE
Key_table *key_table_addr = default_table;
#endif

#ifdef CPU_SINGLE
#include "ms.h"
D 2
#include "clist.h"	
#include "ttydev.h"
#include "tty.h"
#include "../sio/scc.h"
#include "time.h"
#include "../iop/mouse.h"
E 2
I 2
#include <sys/clist.h>	
#include <sys/ttydev.h>
#include <sys/tty.h>
#include <news3400/sio/scc.h>
#include <sys/time.h>
#include <news3400/iop/mouse.h>
E 2

extern int cnrint();

kbd_open(chan)
	int chan;
{
	register int i;

D 3
#ifdef news700
	scc_open(chan);
#endif
#if defined(news1700) || defined(news1200) || defined(news3400)
E 3
I 3
#if defined(news3400)
E 3
	kbm_open(chan);
#endif
	return (0);
}

kbd_read(chan, buf, n)
	int chan;
	char *buf;
	int n;
{
D 3
#ifdef news700
	register int i;

	for (i = n; i > 0; i--)
		*buf++ = scc_getc(chan);
	return (n);
#endif
E 3
#if defined(news1700) || defined(news1200)

	return (kbd_read_raw(chan, buf, n));
#endif
}

kbd_write(chan, buf, n)
	int chan;
	char *buf;
	int n;
{
D 3
#ifdef news700
	register int i;
E 3

D 3
	for (i = 0; i < n; i++) {
		scc_putc(SCC_KEYBOARD, *buf++);
#ifndef NO_PRE_EMPT
		if (i % 4 == 0) PRE_EMPT;
#endif
	}
	return (n);
#endif /* news700 */
#if defined(news1700) || defined(news1200) || defined(news3400)

E 3
I 3
#if defined(news3400)
E 3
	return (kbm_write(SCC_KEYBOARD, buf, n));
#endif
}

kbd_back(buf, len)
	register char *buf;
	register int len;
{
	int s;

	while (--len >= 0) {
		s = spltty();
		cnrint(*buf++);
		(void) splx(s);
	}
	return (0);
}

#define	KBPRI	(PZERO+1)

struct clist scode_buf;
struct clist keyboard_buf;
char	kb_rwait;

kbd_flush()
{

	ndflush(&scode_buf, scode_buf.c_cc);
	return (0);
}

static
kbd_put_raw(scode)
	int scode;
{
	extern char kb_busy;

	if (kb_busy) {
		if (scode_buf.c_cc < CBSIZE)
			putc(scode, &scode_buf);
		if (kb_rwait) {
			kb_rwait = 0;
			wakeup((caddr_t)&kb_rwait);
		}
	}
	return (scode);
	
}

kbd_read_raw(chan, buf, count)
	int chan;
	char *buf;
	register int count;
{
	register int i;
	register int n;
	register int s;

	if (count <= 0)
		return (count);
	s = splscc();
	while ((n = min(scode_buf.c_cc, count)) == 0) {
		kb_rwait = 1;
		sleep((caddr_t)&kb_rwait, KBPRI);
		kb_rwait = 0;
	}
	(void) splx(s);
	for (i = n; i > 0 ; i--)
		*buf++ = getc(&scode_buf);
	return (n);
}

kbd_nread()
{

	return (scode_buf.c_cc);
}

kbd_bell(n)
	register int n;
{

D 3
#if defined(news1700) || defined(news1200) || defined(news3400)
E 3
I 3
#if defined(news3400)
E 3
	(void) kbm_write(SCC_KEYBOARD, NULL, n);
#endif
D 3
#ifdef news700
	kbd_bell_scc(n);
#endif
E 3
	return (0);
}

kbd_putcode(code)
	int code;
{
	int c;

	kbd_put_raw(code);
	kbd_encode(code);
	while ((c = getc(&keyboard_buf)) != -1)
		cnrint(c); 
}

put_code(buf, cnt)
	register char *buf;
	register int cnt;
{

	while (--cnt >= 0)
		putc(*buf++, &keyboard_buf);
}

kb_softint()
{
	int code;
	extern int tty00_is_console;

	while ((code = xgetc(SCC_KEYBOARD)) >= 0) {
D 3
#if defined(news1200) || defined(news3200)		/* BEGIN reiko */
E 3
I 3
#if defined(news3200)		/* BEGIN reiko */
E 3
		if ((code & 0x7f) == KEY_EISUU) {
			int up = code & OFF;
			static int kana = 0;

			if (kana) {
				if (up) {
					kana = 0;
				}
			} else {
				if (up) {
					code = KEY_KANA | OFF;
					kana = 1;
				} else {
					code = KEY_KANA;
				}
			}
		}
#endif

#ifdef NOTDEF /* KU:XXX */
		if (!tty00_is_console) 
#endif
			rst_dimmer_cnt();
#if NMS > 0
		if (!mskeytrigger(0, code & OFF, code & 0x7f))
#endif
		kbd_putcode(code);
	}
}
#endif /* CPU_SINGLE */

#ifdef IPC_MRX
#include "mrx.h"
#include "queue.h"
#include "process.h"
#include "buffer.h"
#include "port.h"
#include "message.h"
#include "machdep.h"
#include "malloc.h"
#include "config.h"
#include "kbms.h"

D 3
#ifdef news1800
#include "scc.h"
#endif

E 3
static struct buffer *kbd_buf;
static int port_kbd_intr;
static int port_kbd_back;
static int port_kbd_ctrl;

keyboard(chan)
	int chan;
{
	int kbd_ctrl(), kbd_output();
	int kbd_read(), kbd_ioctl(), kbd_io();

#ifdef news3800
	extern int (*Xkb_intr)();
	int kb_intr();

	Xkb_intr = kb_intr;
#endif
D 3

#ifdef news1800
	int scc_input(), scc_output();

	if (scc_open(SCC_KEYBOARD) < 0)
		return;
	proc_create("scc_kbread", scc_input, 601, 512, SCC_KEYBOARD);
	proc_create("scc_kbwrite", scc_output, 601, 512, SCC_KEYBOARD);
	while (scc_std_ports[SCC_KEYBOARD][0] == 0)
		proc_sleep_self(100);
#endif
E 3
	kb_ioctl = kbd_ioctl;
	kb_read = kbd_read;
	kbd_init();
	proc_create("kbd_ctrl", kbd_ctrl, 300, DEFAULT_STACK_SIZE, 0);
	proc_create("kbd_output", kbd_output, 300, DEFAULT_STACK_SIZE, 0);
	proc_create("kbd_io", kbd_io, 300, DEFAULT_STACK_SIZE, 0);
}

int (*reset_dimmer)();

kbd_ctrl()
{
	register int m, n;
	register int select;
	int *len, from, count;
	char *addr;
	int ports[3];
	static char buf[16];

	ports[0] = port_kbd_intr = port_create("kb_intr");
	ports[1] = port_kbd_back = port_create("kb_echoback");
	ports[2] = port_kbd_ctrl = STDPORT;

#ifdef news3800
	*(char *)KEYBD_RESET = 0;
	*(char *)KEYBD_INTE = 1;
#endif
D 3
#ifdef news1800
	count = 1;
	msg_send(scc_std_ports[SCC_KEYBOARD][0], ports[0],
		&count, sizeof (count), 0);
#endif
E 3

	kbd_buf = buffer_alloc(32);
	(void) spl0();
	for (;;) {
		if (buffer_status(kbd_buf) > 0)
			m = 3;
		else
			m = 2;
		if ((select = msg_select(m, ports)) == 0) {
			msg_recv(ports[0], NULL, &addr, &count, 0);
			if (reset_dimmer)
				(*reset_dimmer)();
			while (--count >= 0) {
				if (send_mouse == 0 || (*send_mouse)(*addr) == 0)
					kbd_encode(*addr);
				addr++;
			}
D 3
#ifdef news1800
			count = 1;
			msg_send(scc_std_ports[SCC_KEYBOARD][0], ports[select],
			    &count, sizeof (count), 0);
#endif
E 3
		} else if (select == 1) {	/* ESC [ 6 n */
			msg_recv(ports[select], NULL, &addr, &count, 0);
			put(kbd_buf, addr, count);
		} else {
			msg_recv(ports[select], &from, &len, NULL, 0); 
			n = buffer_status(kbd_buf);
			n = min(n, *len);
			n = get(kbd_buf, buf, min(n, sizeof (buf)));
			msg_send(from, ports[select], buf, n, 0);
		}
	}
}

kbd_output()
{
	char *addr;
	int from, len;
D 3
#ifdef news1800
	register int subport;
E 3

D 3
	subport = port_create("port_kbd_write");
#endif

E 3
	(void) spl0();
	for (;;) {
		msg_recv(STDPORT, &from, &addr, &len, 0);
#ifdef news3800
		len = kbd_write(0, addr, len);
#endif
D 3
#ifdef news1800
		len = kbd_write(subport, addr, len);
#endif
E 3
		msg_send(from, STDPORT, &len, sizeof(len), 0);
	}
}

kbd_io()
{
	struct kb_ctrl_req *req;
	int from, reply;
D 3
#ifdef news1800
	register int sub_port;
E 3

D 3
	sub_port = port_create("port_kbd_sub");
#endif

E 3
	(void) spl0();
	for (;;) {
		msg_recv(STDPORT, &from, &req, NULL, 0);
		if (req->kb_func == KIOCCHTBL || req->kb_func == KIOCOYATBL)
			kbd_ioctl(0, req->kb_func, req->kb_arg);
		else
D 3
#ifdef news1800
			kbd_ioctl(sub_port, req->kb_func, &req->kb_arg);
#else
E 3
			kbd_ioctl(0, req->kb_func, &req->kb_arg);
D 3
#endif
E 3
		reply = req->kb_arg;
		msg_send(from, STDPORT, &reply, sizeof(reply), 0);
	}
}

kbd_read(chan, buf, n)
	int chan;
	char *buf;
	int n;
{
	static int port;
	char *addr;
	int len;

	if (port == 0)
		port = port_create("port_kbd_read");
	if (n <= 0)
		return (0);
	msg_send(port_kbd_ctrl, port, &n, sizeof (n), 0);
	msg_recv(port, NULL, &addr, &len, 0);
	bcopy(addr, buf, len);
	msg_free(port);
	return (len);
}

kbd_write(chan, buf, n)
	int chan;
	char *buf;
	int n;
{
D 3
#ifdef news1800
	return (scc_write(chan, SCC_KEYBOARD, buf, n));
#endif
E 3

#ifdef news3800
	*(char *)BEEP_FREQ = ~(n & 1);
	*(char *)KEYBD_BEEP = 1;
	return (n);
#endif
}

kbd_back(buf, len)
	char *buf;
	int len;
{

	msg_send(port_kbd_back, 0, buf, len, 0);
	return (0);
}

kbd_nread()
{

	return (buffer_status(kbd_buf));
}

kbd_flush()
{

	buffer_flush(kbd_buf);
	return (0);
}

#ifdef news3800
kb_intr()
{
	char c;

	if (port_kbd_intr > 0)
		while (*(char *)KBMS_STAT & (1 << b_KBREADY)) {
			c = *(char *)KEYBD_DATA;
			msg_send(port_kbd_intr, 0, &c, sizeof (char), 0);
		}
}
#endif /* news3800 */

kbd_bell(n, port)
	int n, port;
{

#ifdef news3800
	(void) kbd_write(0, NULL, n);
#else
	kbd_bell_scc(n, port);
#endif
	return (0);
}

put_code(buf, cnt)
	char *buf;
	int cnt;
{

	put(kbd_buf, buf, cnt);
}
#endif /* IPC_MRX */

kbd_ioctl(chan, cmd, argp)
	int chan;
	int cmd;
	int *argp;
{
	switch (cmd) {

	case KIOCFLUSH:
		return (kbd_flush());

	case KIOCSETS:
	case KIOCGETS:
		return (kbd_string(cmd, (Pfk_string *)argp));

	case KIOCBELL:
D 3
#ifdef news1800
		return (kbd_bell(*argp, chan));
#else
E 3
		return (kbd_bell(*argp));
D 3
#endif
E 3

	case KIOCBACK:
		if (argp == NULL)
			return (-1);
		if ((int)((Key_string *)argp)->key_string == NULL)
			return (-1);
		if ((int)((Key_string *)argp)->key_length <= 0)
			return (-1);
		return (kbd_back(((Key_string *)argp)->key_string,
		    ((Key_string *)argp)->key_length));

	case KIOCREPT:
		return (kbd_repeat(1));

	case KIOCNRPT:
		return (kbd_repeat(0));

	case KIOCNREAD:
		*argp = kbd_nread();
		return (0);

	case KIOCSETLOCK:
		iscaps = *argp;
		return (0);

	case KIOCGETCNUM:
		*argp = country;
		return (0);

	case KIOCSETCNUM:
		country = *argp;
		change_country = country;
		return (0);

	case KIOCDEFTBL:
		key_table_addr = default_table;
		country = K_JAPANESE_J;
		return (0);

	case KIOCCHTBL:
		key_table_addr = (Key_table *)argp;
		country = change_country;
		return (0);

	case KIOCGETSTAT:
		*argp = kbd_status;
		return (0);

	case KIOCSETSTAT:
		kbd_status = *argp;
		return (0);

	default:
		return (-1);
	}
}

D 3
#ifdef news1800
kbd_bell_scc(n, port)
	register int n, port;
#else
E 3
kbd_bell_scc(n)
	register int n;
D 3
#endif
E 3
{
	register int i;
	static char bell_data[] = {
		0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
		0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
		0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
		0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0
	};

	while (n > 0) {
		i = min(n, sizeof (bell_data));
D 3
#ifdef news1800
		(void) kbd_write(port, bell_data, i);
#else
E 3
		(void) kbd_write(0, bell_data, i);
D 3
#endif
E 3
		n -= i;
	}
}

#ifdef KBDEBUG
scc_error_puts(chan, buf)
	int chan;
	char *buf;
{
	while (*buf) {
		scc_error_write(chan, *buf++, 1);
	}
}

scc_error_write_hex(chan, n, zs)
	int chan;
	unsigned int n;
	int zs;
{
	int i;
	int tmp, al;
	static char hex[] = "0123456789abcdef";

	al = 0;

	for (i = 28; i >= 0; i -= 4) {
		tmp = (n >> i) & 0x0f;
		if (tmp || al || !zs || !i) {
			al++;
			scc_error_write(chan, hex[tmp], 1);
		}
	}
}
#endif /* KBDEBUG */
E 1
