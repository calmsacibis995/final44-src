/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	kern_io.h,v $
 * Revision 2.2  93/11/17  19:07:02  dbg
 * 	Created.
 * 	[93/11/17  19:06:24  dbg]
 * 
 */

/*
 *	Kernel console IO package.
 */

#ifndef	_KERN_IO_H
#define	_KERN_IO_H_

#include <mach/boolean.h>
#include <sys/stdarg.h>

/*
 *	Kernel printing routines.
 *	_doprnt is used by debugger printing as well
 *	as kernel printing routines.
 */
extern void
printf_init(void);

extern void
_doprnt(const char *fmt,
	va_list	*argp,
	void	(*putc)(char, void *),
	int	radix,
	void	*arg);

extern void
printf(const char *format, ...);

extern int
sprintf(char *buf, const char *fmt, ...);

/*
 *	Kernel input routines.
 */
extern int
sscanf(const char *input, const char *fmt, ...);

extern void
safe_gets(char *buf, int maxlen);

/*
 *	Machine-dependent console IO routines.
 *	These do one-character-at-a-time output and
 *	polled input.
 */

extern void
cnputc(int);			/* output character */

extern int
cngetc(void);			/* input character, waiting */

extern int
cnmaygetc(void);		/* input character, return -1 if none */

extern void
cnpollc(boolean_t);		/* switch console to polled mode for
				   cngetc */

#endif	/* _KERN_IO_H_ */
