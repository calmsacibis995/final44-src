h37773
s 00001/00001/00527
d D 8.4 94/01/12 16:42:24 hibler 20 19
c lint
e
s 00001/00001/00527
d D 8.3 94/01/12 10:27:53 bostic 19 18
c typo
e
s 00014/00005/00514
d D 8.2 94/01/12 09:44:52 bostic 18 17
c lint
e
s 00002/00002/00517
d D 8.1 93/06/10 21:41:00 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00005/00500
d D 7.16 92/12/27 09:46:29 hibler 16 15
c account for new stack alignment
e
s 00008/00002/00497
d D 7.15 92/12/16 17:31:20 mckusick 15 14
c proper acknowledgement
e
s 00013/00011/00486
d D 7.14 92/10/11 09:42:36 bostic 14 13
c make kernel includes standard
e
s 00031/00010/00466
d D 7.13 92/07/24 15:33:13 mckusick 13 12
c update to latest revision of kgdb debugging protocol
e
s 00001/00000/00475
d D 7.12 92/06/22 18:12:05 mckusick 12 11
c have to invalidate instruction cache after setting breakpoints
e
s 00001/00001/00474
d D 7.11 92/06/05 15:37:04 hibler 11 10
c merge latest Utah hp300 code including 68040 support
e
s 00003/00003/00472
d D 7.10 91/06/27 18:40:09 karels 10 9
c make kgdb_dev be dev_t; don't wait for debugger on panic if no kgdb_dev
e
s 00002/00002/00473
d D 7.9 91/05/04 17:56:38 karels 9 8
c u => kstack
e
s 00041/00017/00434
d D 7.8 91/04/20 17:35:29 karels 8 7
c update from lbl: use SL_BUFSIZE, new EXEC message; do printf's here
e
s 00034/00002/00417
d D 7.7 91/03/16 19:23:44 karels 7 6
c add kgdb_connect, kgdb_panic; use normal major dev numbers
e
s 00095/00084/00324
d D 7.6 91/03/12 15:04:24 karels 6 5
c update from van using newer protocol; add kgdb_acc to avoid kernacc
c before kernel_map is set
e
s 00275/00407/00133
d D 7.5 91/03/11 09:16:40 karels 5 4
c much-updated version from van, uses slip framing
e
s 00009/00009/00531
d D 7.4 90/12/16 16:36:16 bostic 4 3
c kernel reorg
e
s 00001/00001/00539
d D 7.3 90/06/22 09:32:28 hibler 3 2
c T_AST -> T_ASTFLT to be more consisent with VAX
e
s 00020/00008/00520
d D 7.2 90/05/25 15:49:58 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00528/00000/00000
d D 7.1 90/05/08 18:09:09 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990 The Regents of the University of California.
E 5
I 5
D 17
 * Copyright (c) 1990 Regents of the University of California.
E 5
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
I 13
D 15
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson and Steven McCanne of Lawrence Berkeley Laboratory.
E 15
I 15
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
E 15
 *
E 13
D 5
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
E 5
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
I 13

E 13
D 5

E 5
/*
D 5
 *
 *    The following gdb commands are supported:
 *
 * command          function                               Return value
 *
 *    g             return the value of the CPU registers  hex data or ENN
 *    G             set the value of the CPU registers     OK or ENN
 *
 *    mAA..AA,LLLL  Read LLLL bytes at address AA..AA      hex data or ENN
 *    MAA..AA,LLLL: Write LLLL bytes at address AA.AA      OK or ENN
 *
 *    c             Resume at current address              SNN   ( signal NN)
 *    cAA..AA       Continue at address AA..AA             SNN
 *
 *    s             Step one instruction                   SNN
 *    sAA..AA       Step one instruction from AA..AA       SNN
 *
 *    k             kill
 *
 *    ?             What was the last sigval ?             SNN   (signal NN)
 *
 * All commands and responses are sent with a packet which includes a
 * checksum.  A packet consists of
 *
 * $<packet info>#<checksum>.
 *
 * where
 * <packet info> :: <characters representing the command or response>
 * <checksum>    :: < two hex digits computed as modulo 256 sum of <packetinfo>>
 *
 * When a packet is received, it is first acknowledged with either '+' or '-'.
 * '+' indicates a successful transfer.  '-' indicates a failed transfer.
 *
 * Example:
 *
 * Host:                  Reply:
 * $m0,10#2a               +$00010203040506070809101112131415#42
 *
 ****************************************************************************/

E 5
I 5
 * "Stub" to allow remote cpu to debug over a serial line using gdb.
 */
E 5
#ifdef KGDB
D 4
#include "param.h"
#include "systm.h"
#include "trap.h"
#include "cpu.h"
#include "psl.h"
#include "reg.h"
#include "frame.h"
#include "buf.h"
E 4
I 4
D 5
#include "sys/param.h"
#include "sys/systm.h"
#include "../include/trap.h"
#include "../include/cpu.h"
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/frame.h"
#include "sys/buf.h"
E 5
I 5
#ifndef lint
D 6
static char rcsid[] = "$Header: kgdb_stub.c,v 1.6 91/03/05 01:15:03 van Exp $";
E 6
I 6
D 8
static char rcsid[] = "$Header: kgdb_stub.c,v 1.9 91/03/08 07:03:13 van Locked $";
E 8
I 8
D 13
static char rcsid[] = "$Header: kgdb_stub.c,v 1.13 91/03/23 13:55:57 mccanne Exp $";
E 13
I 13
D 16
static char rcsid[] = "$Header: kgdb_stub.c,v 1.2 92/07/23 19:37:50 mccanne Exp $";
E 16
I 16
static char rcsid[] = "$Header: /usr/src/sys/hp300/hp300/RCS/kgdb_stub.c,v 1.5 92/12/20 15:49:01 mike Exp $";
E 16
E 13
E 8
E 6
#endif
E 5
E 4

I 5
D 14
#include "param.h"
#include "systm.h"
D 8
#include "machine/trap.h"
#include "machine/cpu.h"
#include "machine/psl.h"
#include "machine/reg.h"
#include "frame.h"
E 8
I 8
#include "../include/trap.h"
#include "../include/cpu.h"
#include "../include/psl.h"
#include "../include/reg.h"
#include "../include/frame.h"
E 8
#include "buf.h"
D 6
#include "../hp300/cons.h"
E 6
I 6
D 11
#include "cons.h"
E 11
I 11
#include "hp/dev/cons.h"
E 14
I 14
#include <sys/param.h>
#include <sys/systm.h>
E 14
E 11
E 6

D 14
#include "kgdb_proto.h"
#include "machine/remote-sl.h"
E 14
I 14
#include <machine/trap.h>
#include <machine/cpu.h>
#include <machine/psl.h>
#include <machine/reg.h>
#include <machine/frame.h>

#include <sys/buf.h>
#include <hp/dev/cons.h>

#include <hp300/hp300/kgdb_proto.h>
#include <machine/remote-sl.h>
E 14

E 5
D 6
extern void printf();
extern void bcopy();
E 6
extern int kernacc();
extern void chgkprot();

D 5
/* # of additional (beyond 4) bytes in 680x0 exception frame format n */
static int frame_bytes[16] = {
	4,	4,	8,	4,
	4,	4,	4,	4,
	54,	16,	28,	88,
	4,	4,	4,	4
};
E 5
I 5
D 6
/* (XXX from trap.c) user-mode flag in type */
#define	USER	0x20
E 5

E 6
D 5
#define USER    040             /* (XXX from trap.c) user-mode flag in type */

/*
 * BUFMAX defines the maximum number of characters in inbound/outbound
 * buffers.  At least NUMREGBYTES*2 are needed for register packets.
 */
#define BUFMAX 512

E 5
D 2
int kgdb_dev = -1;		/* remote debugging device (-1 if none) */
int kgdb_baud = 9600;		/* baud rate of serial line */
E 2
I 2
#ifndef KGDBDEV
D 10
#define KGDBDEV -1
E 10
I 10
#define KGDBDEV NODEV
E 10
#endif
#ifndef KGDBRATE
#define KGDBRATE 9600
#endif

D 10
int kgdb_dev = KGDBDEV;		/* remote debugging device (-1 if none) */
E 10
I 10
dev_t kgdb_dev = KGDBDEV;	/* remote debugging device (NODEV if none) */
E 10
int kgdb_rate = KGDBRATE;	/* remote debugging baud rate */
I 5
int kgdb_active = 0;            /* remote debugging active if != 0 */
E 5
E 2
int kgdb_debug_init = 0;	/* != 0 waits for remote at system init */
I 7
int kgdb_debug_panic = 1;	/* != 0 waits for remote on panic */
E 7
D 5
int kgdb_debug = 0;		/* > 0 prints command & checksum errors */
E 5
I 5
int kgdb_debug = 0;
E 5

D 2
extern int dcacngetc();
extern void dcacnputc();
#define GETC (dcacngetc(kgdb_dev))
#define PUTC(c) (dcacnputc(kgdb_dev, c))
E 2
I 2
D 4
#include "../hp300/cons.h"
E 4
I 4
D 5
#include "cons.h"
E 4
E 2

I 2
#define GETC	\
	(constab[major(kgdb_dev)].cn_getc ? \
		(*constab[major(kgdb_dev)].cn_getc)(kgdb_dev) : 0)
#define PUTC(c)	{ \
	if (constab[major(kgdb_dev)].cn_putc) \
		(*constab[major(kgdb_dev)].cn_putc)(kgdb_dev, c); \
E 5
I 5
#define GETC	((*kgdb_getc)(kgdb_dev))
#define PUTC(c)	((*kgdb_putc)(kgdb_dev, c))
#define PUTESC(c) { \
	if (c == FRAME_END) { \
		PUTC(FRAME_ESCAPE); \
		c = TRANS_FRAME_END; \
	} else if (c == FRAME_ESCAPE) { \
		PUTC(FRAME_ESCAPE); \
		c = TRANS_FRAME_ESCAPE; \
I 13
	} else if (c == FRAME_START) { \
		PUTC(FRAME_ESCAPE); \
		c = TRANS_FRAME_START; \
E 13
	} \
	PUTC(c); \
E 5
}
D 13

E 13
E 2
D 5
static char hexchars[] = "0123456789abcdef";
E 5
I 5
static int (*kgdb_getc)();
static int (*kgdb_putc)();
E 5

/*
D 5
 * There are 180 bytes of registers on a 68020 w/68881.  Many of the fpa
 * registers are 12 byte (96 bit) registers.
E 5
I 5
 * Send a message.  The host gets one chance to read it.
E 5
 */
D 5
#define NUMREGBYTES 180

static char inbuffer[BUFMAX];
static char outbuffer[BUFMAX];

static inline int 
hex(ch)
	char ch;
E 5
I 5
static void
kgdb_send(type, bp, len)
	register u_char type;
	register u_char *bp;
	register int len;
E 5
{
D 5
	if ((ch >= '0') && (ch <= '9'))
		return (ch - '0');
	if ((ch >= 'a') && (ch <= 'f'))
		return (ch - ('a' - 10));
	return (0);
}
E 5
I 5
	register u_char csum;
	register u_char *ep = bp + len;
E 5

D 5
/* scan for the sequence $<data>#<checksum>     */
static void 
getpacket(char *buffer)
{
	unsigned char checksum;
	unsigned char xmitcsum;
	int i;
	int count;
	char ch;
E 5
I 5
D 13
	csum = type;
	PUTESC(type)
E 13
I 13
	PUTC(FRAME_START);
	PUTESC(type);
E 13
E 5

I 13
	csum = type;
E 13
D 5
	do {
		/*
		 * wait around for the start character, ignore all other
		 * characters
		 */
		while ((ch = GETC) != '$')
			;
		checksum = 0;
		count = 0;
		xmitcsum = 1;

		/* now, read until a # or end of buffer is found */
		while (count < BUFMAX) {
			ch = GETC;
			if (ch == '#')
				break;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		}
		buffer[count] = 0;

		if (ch == '#') {
			xmitcsum = hex(GETC) << 4;
			xmitcsum += hex(GETC);
			if (kgdb_debug && (checksum != xmitcsum)) {
				printf(
			"bad checksum.  My count = 0x%x, sent=0x%x. buf=%s\n",
					checksum, xmitcsum, buffer);
			}
D 2
			if (checksum != xmitcsum)
E 2
I 2
			if (checksum != xmitcsum) {
E 2
				PUTC('-');	/* failed checksum */
D 2
			else {
E 2
I 2
			} else {
E 2
				PUTC('+');	/* successful transfer */
				/*
				 * if a sequence char is present, reply the
				 * sequence ID
				 */
				if (buffer[2] == ':') {
					PUTC(buffer[0]);
					PUTC(buffer[1]);
					/* remove sequence chars from buffer */
					for (i = 3; i <= count; ++i)
						buffer[i - 3] = buffer[i];
				}
			}
		}
	} while (checksum != xmitcsum);
E 5
I 5
	while (bp < ep) {
		type = *bp++;
		csum += type;
		PUTESC(type)
	}
	csum = -csum;
	PUTESC(csum)
	PUTC(FRAME_END);
E 5
}

D 5
/*
 * send the packet in buffer.  The host gets one chance to read it.  This
 * routine does not wait for a positive acknowledge.
 */
static void 
putpacket(char *buffer)
E 5
I 5
static int
kgdb_recv(bp, lenp)
	u_char *bp;
	int *lenp;
E 5
{
D 5
	unsigned char checksum;
	int count;
	char ch;
E 5
I 5
	register u_char c, csum;
	register int escape, len;
	register int type;
E 5

I 13
restart:
E 13
D 5
	/* $<packet info>#<checksum>. */
	do {
		PUTC('$');
		checksum = 0;
		count = 0;
E 5
I 5
	csum = len = escape = 0;
	type = -1;
	while (1) {
		c = GETC;
		switch (c) {
E 5

D 5
		while (ch = buffer[count]) {
			PUTC(ch);
			checksum += ch;
			count += 1;
		}
		PUTC('#');
		PUTC(hexchars[checksum >> 4]);
		PUTC(hexchars[checksum & 15]);
E 5
I 5
		case FRAME_ESCAPE:
			escape = 1;
			continue;
E 5

D 5
	} while (0);	/* (GETC != '+'); */
E 5
I 5
		case TRANS_FRAME_ESCAPE:
			if (escape)
				c = FRAME_ESCAPE;
			break;
E 5

D 5
}

static inline void 
debug_error(char *format, char *parm)
{
	if (kgdb_debug)
		printf(format, parm);
}

/*
 * Convert at most 'dig' digits of hex data in buf into a value.
 * Stop on non-hex char.  Return a pointer to next char in buf.
 */
static char *
hex2val(char *buf, int *val, int dig)
{
	int i, v;
	char ch;

	v = 0;
	for (i = dig; --i >= 0; ) {
		ch = *buf++;
		if ((ch >= '0') && (ch <= '9'))
			v = (v << 4) | (ch - '0');
		else if ((ch >= 'a') && (ch <= 'f'))
			v = (v << 4) | (ch - ('a' - 10));
		else {
			--buf;
E 5
I 5
		case TRANS_FRAME_END:
			if (escape)
				c = FRAME_END;
E 5
			break;
D 5
		}
	}
	*val = v;
	return (buf);
}
E 5

I 13
		case TRANS_FRAME_START:
			if (escape)
				c = FRAME_START;
			break;
			
		case FRAME_START:
			goto restart;

E 13
D 5
/*
 * convert the integer value 'val' into 'dig' hex digits, placing
 * result in buf.  Return a pointer to the last char put in buf (null).
 */
static char *
val2hex(char *buf, int val, int dig)
{
	for (dig <<= 2; (dig -= 4) >= 0; )
		*buf++ = hexchars[(val >> dig) & 0xf];
	*buf = 0;
	return (buf);
}

/*
 * convert the memory pointed to by mem into hex, placing result in buf.
 * return a pointer to the last char put in buf (null).
 */
static char *
mem2hex(char *buf, char *mem, int count)
{
	if ((count & 1) || ((int)mem & 1)) {
		char ch;

		while(--count >= 0) {
			ch = *mem++;
			*buf++ = hexchars[ch >> 4];
			*buf++ = hexchars[ch & 15];
E 5
I 5
		case FRAME_END:
			if (type < 0 || --len < 0) {
				csum = len = escape = 0;
				type = -1;
				continue;
			}
			if (csum != 0) {
				return (0);
			}
			*lenp = len;
			return type;
E 5
		}
D 5
	} else {
		u_short s;
		u_short *mp = (u_short *)mem;

		for (count >>= 1; --count >= 0; ) {
			s = *mp++;
			*buf++ = hexchars[(s >> 12) & 15];
			*buf++ = hexchars[(s >> 8) & 15];
			*buf++ = hexchars[(s >> 4) & 15];
			*buf++ = hexchars[s & 15];
E 5
I 5
		csum += c;
		if (type < 0) {
			type = c;
			escape = 0;
			continue;
E 5
		}
I 5
D 8
		if (++len > SL_MAXMSG) {
E 8
I 8
D 13
		if (++len > SL_BUFSIZE) {
E 13
I 13
		if (++len > SL_RPCSIZE) {
E 13
E 8
			while (GETC != FRAME_END)
				;
			return (0);
		}
		*bp++ = c;
		escape = 0;
E 5
	}
D 5
	*buf = 0;
	return (buf);
E 5
}

/*
D 5
 * Convert the hex array pointed to by buf into binary to be placed in mem.
 * Return a pointer to next char in buf.
 */
static char *
hex2mem(char *buf, char *mem, int count)
{
	int i;
	unsigned char ch;

	for (i = 0; i < count; ++i) {
		ch = hex(*buf++) << 4;
		ch = ch + hex(*buf++);
		*mem++ = ch;
	}
	return (buf);
}

/*
E 5
 * Translate a trap number into a unix compatible signal value.
 * (gdb only understands unix signal numbers).
 */
static int 
D 5
computeSignal(int type)
E 5
I 5
computeSignal(type)
	int type;
E 5
{
	int sigval;

D 6
	switch (type &~ USER) {
E 6
I 6
	switch (type) {
E 6
	case T_BUSERR:
		sigval = SIGBUS;
D 5
		break;		/* bus error           */
E 5
I 5
		break;
E 5
	case T_ADDRERR:
		sigval = SIGBUS;
D 5
		break;		/* address error       */
E 5
I 5
		break;
E 5
	case T_ILLINST:
		sigval = SIGILL;
D 5
		break;		/* illegal instruction */
E 5
I 5
		break;
E 5
	case T_ZERODIV:
		sigval = SIGFPE;
D 5
		break;		/* zero divide         */
E 5
I 5
		break;
E 5
	case T_CHKINST:
		sigval = SIGFPE;
D 5
		break;		/* chk instruction     */
E 5
I 5
		break;
E 5
	case T_TRAPVINST:
		sigval = SIGFPE;
D 5
		break;		/* trapv instruction   */
E 5
I 5
		break;
E 5
	case T_PRIVINST:
		sigval = SIGILL;
D 5
		break;		/* privilege violation */
E 5
I 5
		break;
E 5
	case T_TRACE:
		sigval = SIGTRAP;
D 5
		break;		/* trace trap          */
E 5
I 5
		break;
E 5
	case T_MMUFLT:
		sigval = SIGSEGV;
		break;
	case T_SSIR:
		sigval = SIGSEGV;
		break;
	case T_FMTERR:
		sigval = SIGILL;
		break;
	case T_FPERR:
		sigval = SIGFPE;
		break;
	case T_COPERR:
		sigval = SIGFPE;
		break;
D 3
	case T_AST:
E 3
I 3
	case T_ASTFLT:
E 3
		sigval = SIGINT;
		break;
	case T_TRAP15:
D 5
		sigval = SIGIOT;
E 5
I 5
		sigval = SIGTRAP;
E 5
		break;
	default:
		sigval = SIGEMT;
		break;
	}
	return (sigval);
}

D 5
#define RESPOND(str) (bcopy(str, outbuffer, sizeof(str)))
E 5
I 5
/*
I 7
D 8
 * Trap into kgdb to Wait for debugger to connect, 
E 8
I 8
 * Trap into kgdb to wait for debugger to connect, 
E 8
 * noting on the console why nothing else is going on.
 */
kgdb_connect(verbose)
	int verbose;
{

	if (verbose)
		printf("kgdb waiting...");
	/* trap into kgdb */
	asm("trap #15;");
	if (verbose)
		printf("connected.\n");
}

/*
 * Decide what to do on panic.
 */
kgdb_panic()
{

D 10
	if (kgdb_active == 0 && kgdb_debug_panic)
E 10
I 10
	if (kgdb_active == 0 && kgdb_debug_panic && kgdb_dev != NODEV)
E 10
		kgdb_connect(1);
}

/*
E 7
 * Definitions exported from gdb.
 */
#define NUM_REGS 18
#define REGISTER_BYTES ((16+2)*4)
#define REGISTER_BYTE(N)  ((N)*4)
E 5

I 5
#define GDB_SR 16
#define GDB_PC 17

E 5
D 6
/*
I 5
 * # of additional bytes in 680x0 exception frame format n.
 */
static int frame_bytes[16] = {
	0, 0, sizeof(struct fmt2), 0,
	0, 0, 0, 0,
	0, sizeof(struct fmt9), sizeof(struct fmtA), sizeof(struct fmtB),
	0, 0, 0, 0
};

/*
 * Translate the values stored in the kernel frame struct to the format
 * understood by gdb.
 */
static void
regs_to_gdb(fp, gdb_regs)
	struct frame *fp;
	u_long *gdb_regs;
E 6
I 6
static inline void
D 18
kgdb_copy(register u_char *src, register u_char *dst, register u_int nbytes)
E 18
I 18
kgdb_copy(src, dst, nbytes)
	register u_char *src, *dst;
	register u_int nbytes;
E 18
E 6
{
D 6
	bcopy((caddr_t)fp->f_regs, (caddr_t)gdb_regs, sizeof(fp->f_regs) + 8);
}
E 6
I 6
	register u_char *ep = src + nbytes;
E 6

D 6
/*
 * Convert gdb register values to kernel format.
 */
static void
gdb_to_regs(fp, gdb_regs)
	struct frame *fp;
	u_long *gdb_regs;
{
	bcopy((caddr_t)gdb_regs, (caddr_t)fp->f_regs, sizeof(fp->f_regs) - 4);
	fp->f_sr = gdb_regs[GDB_SR];
	fp->f_pc = gdb_regs[GDB_PC];
E 6
I 6
	while (src < ep)
		*dst++ = *src++;
E 6
}

I 6
D 16
#define regs_to_gdb(fp, regs) \
	(kgdb_copy((u_char *)((fp)->f_regs), (u_char *)(regs), REGISTER_BYTES))
E 16
I 16
/*
 * There is a short pad word between SP (A7) and SR which keeps the
 * kernel stack long word aligned (note that this is in addition to
 * the stack adjust short that we treat as the upper half of a longword
 * SR).  We must skip this when copying into and out of gdb.
 */
static inline void
D 18
regs_to_gdb(struct frame *fp, u_long *regs)
E 18
I 18
regs_to_gdb(fp, regs)
	struct frame *fp;
	u_long *regs;
E 18
{
	kgdb_copy((u_char *)fp->f_regs, (u_char *)regs, 16*4);
	kgdb_copy((u_char *)&fp->f_stackadj, (u_char *)&regs[GDB_SR], 2*4);
}
E 16

D 16
#define gdb_to_regs(fp, regs) \
	(kgdb_copy((u_char *)(regs), (u_char *)((fp)->f_regs), REGISTER_BYTES))
E 16
I 16
static inline void
D 18
gdb_to_regs(struct frame *fp, u_long *regs)
E 18
I 18
gdb_to_regs(fp, regs)
	struct frame *fp;
D 19
	u_long regs;
E 19
I 19
	u_long *regs;
E 19
E 18
{
	kgdb_copy((u_char *)regs, (u_char *)fp->f_regs, 16*4);
	kgdb_copy((u_char *)&regs[GDB_SR], (u_char *)&fp->f_stackadj, 2*4);
}
E 16

E 6
static u_long reg_cache[NUM_REGS];
I 6
D 8
static u_char inbuffer[SL_MAXMSG+1];
static u_char outbuffer[SL_MAXMSG];
E 8
I 8
D 13
static u_char inbuffer[SL_BUFSIZE];
static u_char outbuffer[SL_BUFSIZE];
E 13
I 13
static u_char inbuffer[SL_RPCSIZE+1];
static u_char outbuffer[SL_RPCSIZE];
E 13
E 8
E 6

/*
E 5
 * This function does all command procesing for interfacing to 
 * a remote gdb.
 */
int 
D 6
kgdb_trap(int type, unsigned code, unsigned v, struct frame *frame)
E 6
I 6
D 18
kgdb_trap(int type, struct frame *frame)
E 18
I 18
kgdb_trap(type, frame)
	int type;
	struct frame *frame;
E 18
E 6
{
D 5
	int sigval;
	int addr, length;
	char *ptr;
E 5
I 5
D 6
	int i;
	u_long length;
	caddr_t addr;
	u_char *cp;
	int out, in;
	int inlen, outlen;
	static u_char inbuffer[SL_MAXMSG+1];
	static u_char outbuffer[SL_MAXMSG];
E 6
I 6
	register u_long len;
	u_char *addr;
	register u_char *cp;
	register u_char out, in;
	register int outlen;
	int inlen;
E 6
	u_long gdb_regs[NUM_REGS];
E 5

D 5
	if (kgdb_dev < 0)
E 5
I 5
D 20
	if (kgdb_dev < 0) {
E 20
I 20
	if ((int)kgdb_dev < 0) {
E 20
E 5
		/* not debugging */
		return (0);
I 5
	}
	if (kgdb_active == 0) {
		if (type != T_TRAP15) {
			/* No debugger active -- let trap handle this. */
			return (0);
		}
D 7
		kgdb_getc = constab[major(kgdb_dev)].cn_getc;
		kgdb_putc = constab[major(kgdb_dev)].cn_putc;
E 7
I 7
		kgdb_getc = 0;
		for (inlen = 0; constab[inlen].cn_probe; inlen++)
		    if (major(constab[inlen].cn_dev) == major(kgdb_dev)) {
			kgdb_getc = constab[inlen].cn_getc;
			kgdb_putc = constab[inlen].cn_putc;
			break;
		}
E 7
D 6
		if (kgdb_getc == 0 || kgdb_putc == 0) {
E 6
I 6
		if (kgdb_getc == 0 || kgdb_putc == 0)
E 6
			return (0);
D 6
		}
E 6
I 6
		/*
D 8
		 * If the packet that woke us up isn't a signal packet,
E 8
I 8
		 * If the packet that woke us up isn't an exec packet,
E 8
		 * ignore it since there is no active debugger.  Also,
		 * we check that it's not an ack to be sure that the 
		 * remote side doesn't send back a response after the
		 * local gdb has exited.  Otherwise, the local host
		 * could trap into gdb if it's running a gdb kernel too.
		 */
D 8
#ifdef notdef
E 8
		in = GETC;
D 8
		if (KGDB_CMD(in) != KGDB_SIGNAL || (in & KGDB_ACK) != 0)
E 8
I 8
		/*
		 * If we came in asynchronously through the serial line,
		 * the framing character is eaten by the receive interrupt,
		 * but if we come in through a synchronous trap (i.e., via
		 * kgdb_connect()), we will see the extra character.
		 */
D 13
		if (in == FRAME_END)
E 13
I 13
		if (in == FRAME_START)
E 13
			in = GETC;

I 13
		/*
		 * Check that this is a debugger exec message.  If so,
		 * slurp up the entire message then ack it, and fall
		 * through to the recv loop.
		 */
E 13
		if (KGDB_CMD(in) != KGDB_EXEC || (in & KGDB_ACK) != 0)
E 8
			return (0);
D 8
#endif
E 8
		while (GETC != FRAME_END)
			;
D 8

E 8
I 8
		/*
		 * Do the printf *before* we ack the message.  This way
		 * we won't drop any inbound characters while we're 
		 * doing the polling printf.
		 */
		printf("kgdb started from device %x\n", kgdb_dev);
		kgdb_send(in | KGDB_ACK, (u_char *)0, 0);
E 8
E 6
		kgdb_active = 1;
	}
	/*
	 * Stick frame regs into our reg cache then tell remote host
	 * that an exception has occured.
	 */
D 6
	if ((type & USER) == 0)
		/*
		 * After a kernel mode trap, the saved sp points at the
		 * PSW and is useless.  The correct saved sp should be
		 * the top of the frame.
		 */
		frame->f_regs[SP] = (int)&frame->F_u +
				    frame_bytes[frame->f_format];
E 6
	regs_to_gdb(frame, gdb_regs);
E 5
D 6

E 6
D 5
	if (kgdb_debug)
		printf("type=%d, code=%d, vector=0x%x, pc=0x%x, sr=0x%x\n",
			type, code, frame->f_vector, frame->f_pc, frame->f_sr);
E 5
I 5
D 8
	outbuffer[0] = computeSignal(type);
	kgdb_send(KGDB_SIGNAL, outbuffer, 1);
E 8
I 8
	if (type != T_TRAP15) {
		/*
		 * Only send an asynchronous SIGNAL message when we hit
		 * a breakpoint.  Otherwise, we will drop the incoming
		 * packet while we output this one (and on entry the other 
		 * side isn't interested in the SIGNAL type -- if it is,
		 * it will have used a signal packet.)
		 */
		outbuffer[0] = computeSignal(type);
		kgdb_send(KGDB_SIGNAL, outbuffer, 1);
	}
E 8
E 5

D 5
	/* reply to host that an exception has occurred */
	sigval = computeSignal(type);
	outbuffer[0] = 'S';
	(void)val2hex(&outbuffer[1], sigval, 2);
	putpacket(outbuffer);

E 5
	while (1) {
D 5
		outbuffer[0] = 0;
		getpacket(inbuffer);
		ptr = inbuffer;
		switch (*ptr++) {
		case '?':
			outbuffer[0] = 'S';
			(void)val2hex(&outbuffer[1], sigval, 2);
E 5
I 5
		in = kgdb_recv(inbuffer, &inlen);
		if (in == 0 || (in & KGDB_ACK))
			/* Ignore inbound acks and error conditions. */
			continue;

		out = in | KGDB_ACK;
D 6
		switch (in) {
E 6
I 6
		switch (KGDB_CMD(in)) {
E 6

		case KGDB_SIGNAL:
D 6
			outbuffer[0] = computeSignal(type);
			outlen = 1;
E 5
			break;
E 6
I 6
			/*
			 * if this command came from a running gdb,
			 * answer it -- the other guy has no way of
			 * knowing if we're in or out of this loop
			 * when he issues a "remote-signal".  (Note
			 * that without the length check, we could
			 * loop here forever if the ourput line is
			 * looped back or the remote host is echoing.)
			 */
			if (inlen == 0) {
				outbuffer[0] = computeSignal(type);
				kgdb_send(KGDB_SIGNAL, outbuffer, 1);
			}
			continue;
E 6
D 5
		case 'g':	/* return the value of the CPU registers */
			ptr = outbuffer;
			if (type & USER)
				ptr = mem2hex(ptr, (char *)frame->f_regs,
					      sizeof(frame->f_regs));
			else {
				ptr = mem2hex(ptr, (char *)frame->f_regs,
					      sizeof(frame->f_regs) - 4);
				addr = (int)&frame->f_pc -
					frame_bytes[frame->f_format];
				ptr = mem2hex(ptr, (char *)&addr, sizeof(addr));
E 5
I 5

		case KGDB_REG_R:
		case KGDB_REG_R | KGDB_DELTA:
			cp = outbuffer;
			outlen = 0;
D 6
			for (i = inbuffer[0]; i < NUM_REGS; ++i) {
				if (reg_cache[i] != gdb_regs[i] ||
E 6
I 6
			for (len = inbuffer[0]; len < NUM_REGS; ++len) {
				if (reg_cache[len] != gdb_regs[len] ||
E 6
				    (in & KGDB_DELTA) == 0) {
D 13
					if (outlen + 5 > SL_MAXMSG) {
E 13
I 13
					if (outlen + 5 > SL_MAXDATA) {
E 13
						out |= KGDB_MORE;
						break;
					}
D 6
					cp[outlen] = i;
					bcopy(&gdb_regs[i], 
					      &cp[outlen + 1], 4);
E 6
I 6
					cp[outlen] = len;
					kgdb_copy((u_char *)&gdb_regs[len],
						  &cp[outlen + 1], 4);
					reg_cache[len] = gdb_regs[len];
E 6
					outlen += 5;
D 6
					reg_cache[i] = gdb_regs[i];
E 6
				}
E 5
			}
D 5
			addr = frame->f_sr;
			ptr = mem2hex(ptr, (char *)&addr, sizeof(addr));
			ptr = mem2hex(ptr, (char *)&frame->f_pc,
				      sizeof(frame->f_pc));
E 5
			break;
D 5
		case 'G':	/* set the value of the CPU registers */
			ptr = hex2mem(ptr, (char *)frame->f_regs,
				      sizeof(frame->f_regs) - 4);
			ptr = hex2mem(ptr, (char *)&addr, sizeof(addr));
			ptr = hex2mem(ptr, (char *)&addr, sizeof(addr));
			frame->f_sr = addr;
			ptr = hex2mem(ptr, (char *)&frame->f_pc,
				      sizeof(frame->f_pc));
			RESPOND("OK");
			break;
E 5
I 5
			
		case KGDB_REG_W:
		case KGDB_REG_W | KGDB_DELTA:
			cp = inbuffer;
D 6
			for (i = 0; i < inlen; i += 5) {
				register int j = cp[i];
E 6
I 6
			for (len = 0; len < inlen; len += 5) {
				register int j = cp[len];
E 6
E 5

D 5
			/* mAA..AA,LLLL  Read LLLL bytes at address AA..AA */
		case 'm':
			ptr = hex2val(ptr, &addr, 8);
			if (*ptr++ != ',') {
				RESPOND("E01");
				debug_error("malformed read memory cmd: %s\n",
					    inbuffer);
				break;
E 5
I 5
D 6
				bcopy(&cp[i + 1], &gdb_regs[j], 4);
E 6
I 6
				kgdb_copy(&cp[len + 1],
					  (u_char *)&gdb_regs[j], 4);
E 6
				reg_cache[j] = gdb_regs[j];
E 5
			}
D 5
			ptr = hex2val(ptr, &length, 8);
			if (length <= 0 || length >= BUFMAX*2) {
				RESPOND("E02");
				if (kgdb_debug)
					printf("bad read memory length: %d\n",
					       length);
				break;
E 5
I 5
			gdb_to_regs(frame, gdb_regs);
			outlen = 0;
			break;
				
		case KGDB_MEM_R:
D 6
			length = inbuffer[0];
			bcopy(&inbuffer[1], &addr, 4);
			if (length + 1 > SL_MAXMSG) {
E 6
I 6
			len = inbuffer[0];
			kgdb_copy(&inbuffer[1], (u_char *)&addr, 4);
D 13
			if (len + 1 > SL_MAXMSG) {
E 13
I 13
			if (len > SL_MAXDATA) {
E 13
E 6
				outlen = 1;
				outbuffer[0] = E2BIG;
D 6
			} else if (!kernacc(addr, length, B_READ)) {
E 6
I 6
			} else if (!kgdb_acc(addr, len, B_READ)) {
E 6
				outlen = 1;
				outbuffer[0] = EFAULT;
			} else {
D 6
				outlen = length + 1;
E 6
I 6
				outlen = len + 1;
E 6
				outbuffer[0] = 0;
D 6
				bcopy(addr, &outbuffer[1], length);
E 6
I 6
				kgdb_copy(addr, &outbuffer[1], len);
E 6
E 5
			}
D 5
			if (! kernacc(addr, length, B_READ)) {
				RESPOND("E03");
				if (kgdb_debug)
					printf("read access violation addr 0x%x len %d\n", addr, length);
				break;
			}
			(void)mem2hex(outbuffer, (char *)addr, length);
E 5
			break;

D 5
			/*
			 * MAA..AA,LLLL: Write LLLL bytes at address AA.AA
			 * return OK
			 */
		case 'M':
			ptr = hex2val(ptr, &addr, 8);
			if (*ptr++ != ',') {
				RESPOND("E01");
				debug_error("malformed write memory cmd: %s\n",
					    inbuffer);
				break;
E 5
I 5
		case KGDB_MEM_W:
D 6
			length = inlen - 4;
			bcopy(inbuffer, &addr, 4);
E 6
I 6
			len = inlen - 4;
			kgdb_copy(inbuffer, (u_char *)&addr, 4);
E 6
			outlen = 1;
D 6
			if (!kernacc(addr, length, B_READ))
E 6
I 6
			if (!kgdb_acc(addr, len, B_READ))
E 6
				outbuffer[0] = EFAULT;
			else {
				outbuffer[0] = 0;
D 6
				if (!kernacc(addr, length, B_WRITE))
					chgkprot(addr, length, B_WRITE);
				bcopy(&inbuffer[4], addr, length);
E 6
I 6
				if (!kgdb_acc(addr, len, B_WRITE))
					chgkprot(addr, len, B_WRITE);
				kgdb_copy(&inbuffer[4], addr, len);
I 12
				ICIA();
E 12
E 6
E 5
			}
D 5
			ptr = hex2val(ptr, &length, 8);
			if (*ptr++ != ':') {
				RESPOND("E01");
				debug_error("malformed write memory cmd: %s\n",
					    inbuffer);
				break;
			}
			if (length <= 0 || length >= BUFMAX*2 - 32) {
				RESPOND("E02");
				if (kgdb_debug)
					printf("bad write memory length: %d\n",
					       length);
				break;
			}
			if (! kernacc(addr, length, B_READ)) {
				RESPOND("E03");
				if (kgdb_debug)
					printf("write access violation addr 0x%x len %d\n", addr, length);
				break;
			}
			if (! kernacc(addr, length, B_WRITE))
				chgkprot(addr, length, B_WRITE);
			(void)hex2mem(ptr, (char *)addr, length);
			RESPOND("OK");
E 5
			break;

D 5
			/*
			 * cAA..AA  Continue at address AA..AA
			 * sAA..AA  Step one instruction from AA..AA
			 * (addresses optional)
			 */
		case 'c':
		case 's':
			/*
			 * try to read optional start address.
			 */
			if (ptr != hex2val(ptr, &addr, 8)) {
				frame->f_pc = addr;
				if (kgdb_debug)
					printf("new pc = 0x%x\n", addr);
			}
			/* deal with the trace bit */
			if (inbuffer[0] == 's')
				frame->f_sr |= PSL_T;
			else
				frame->f_sr &=~ PSL_T;

			if (kgdb_debug)
				printf("restarting at 0x%x\n", frame->f_pc);

E 5
I 5
		case KGDB_KILL:
			kgdb_active = 0;
I 8
			printf("kgdb detached\n");
E 8
			/* fall through */
		case KGDB_CONT:
			kgdb_send(out, 0, 0);
			frame->f_sr &=~ PSL_T;
E 5
			return (1);

D 5
			/* kill the program (same as continue for now) */
		case 'k':
E 5
I 5
		case KGDB_STEP:
			kgdb_send(out, 0, 0);
			frame->f_sr |= PSL_T;
E 5
			return (1);
I 5

I 8
		case KGDB_EXEC:
E 8
		default:
			/* Unknown command.  Ack with a null message. */
			outlen = 0;
			break;
E 5
		}
D 5
		/* reply to the request */
		putpacket(outbuffer);
E 5
I 5
		/* Send the reply */
		kgdb_send(out, outbuffer, outlen);
E 5
	}
I 6
}

/*
 * XXX do kernacc call if safe, otherwise attempt
 * to simulate by simple bounds-checking.
 */
kgdb_acc(addr, len, rw)
	caddr_t addr;
I 18
	int len, rw;
E 18
{
D 9
	extern char proc0paddr[], u[];		/* XXX! */
E 9
I 9
	extern char proc0paddr[], kstack[];	/* XXX */
E 9
	extern char *kernel_map;		/* XXX! */

	if (kernel_map != NULL)
		return (kernacc(addr, len, rw));
	if (addr < proc0paddr + UPAGES * NBPG  ||
D 9
	    u <= addr && addr < u + UPAGES * NBPG)
E 9
I 9
	    kstack <= addr && addr < kstack + UPAGES * NBPG)
E 9
		return (1);
	return (0);
E 6
}
D 18
#endif
E 18
I 18
#endif /* KGDB */
E 18
E 1
