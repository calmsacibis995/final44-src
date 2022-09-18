h10101
s 00002/00002/00099
d D 8.1 93/05/31 15:18:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00101/00000/00000
d D 5.1 91/03/07 20:27:20 bostic 1 0
c date and time created 91/03/07 20:27:20 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "shell.h"
#include "output.h"
#include "errmsg.h"
#include <errno.h>


#define ALL (E_OPEN|E_CREAT|E_EXEC)


struct errname {
	short errcode;		/* error number */
	short action;		/* operation which encountered the error */
	char *msg;		/* text describing the error */
};


STATIC const struct errname errormsg[] = {
	EINTR, ALL,	"interrupted",
	EACCES, ALL,	"permission denied",
	EIO, ALL,		"I/O error",
	ENOENT, E_OPEN,	"no such file",
	ENOENT, E_CREAT,	"directory nonexistent",
	ENOENT, E_EXEC,	"not found",
	ENOTDIR, E_OPEN,	"no such file",
	ENOTDIR, E_CREAT,	"directory nonexistent",
	ENOTDIR, E_EXEC,	"not found",
	EISDIR, ALL,	"is a directory",
/*    EMFILE, ALL,	"too many open files", */
	ENFILE, ALL,	"file table overflow",
	ENOSPC, ALL,	"file system full",
#ifdef EDQUOT
	EDQUOT, ALL,	"disk quota exceeded",
#endif
#ifdef ENOSR
	ENOSR, ALL,	"no streams resources",
#endif
	ENXIO, ALL,	"no such device or address",
	EROFS, ALL,	"read-only file system",
	ETXTBSY, ALL,	"text busy",
#ifdef SYSV
	EAGAIN, E_EXEC,	"not enough memory",
#endif
	ENOMEM, ALL,	"not enough memory",
#ifdef ENOLINK
	ENOLINK, ALL,	"remote access failed"
#endif
#ifdef EMULTIHOP
	EMULTIHOP, ALL,	"remote access failed",
#endif
#ifdef ECOMM
	ECOMM, ALL,	"remote access failed",
#endif
#ifdef ESTALE
	ESTALE, ALL,	"remote access failed",
#endif
#ifdef ETIMEDOUT
	ETIMEDOUT, ALL,	"remote access failed",
#endif
#ifdef ELOOP
	ELOOP, ALL,	"symbolic link loop",
#endif
	E2BIG, E_EXEC,	"argument list too long",
#ifdef ELIBACC
	ELIBACC, E_EXEC,	"shared library missing",
#endif
	0, 0,		NULL
};


/*
 * Return a string describing an error.  The returned string may be a
 * pointer to a static buffer that will be overwritten on the next call.
 * Action describes the operation that got the error.
 */

char *
errmsg(e, action) {
	struct errname const *ep;
	static char buf[12];

	for (ep = errormsg ; ep->errcode ; ep++) {
		if (ep->errcode == e && (ep->action & action) != 0)
			return ep->msg;
	}
	fmtstr(buf, sizeof buf, "error %d", e);
	return buf;
}
E 1
