h55833
s 00051/00044/00179
d D 8.2 95/05/04 17:59:36 christos 4 3
c 
e
s 00002/00002/00221
d D 8.1 93/05/31 15:18:40 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00222
d D 5.2 92/11/29 14:05:35 bostic 2 1
c typo, missing comma
e
s 00223/00000/00000
d D 5.1 91/03/07 20:27:22 bostic 1 0
c date and time created 91/03/07 20:27:22 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Errors and exceptions.
 */

#include "shell.h"
#include "main.h"
#include "options.h"
#include "output.h"
#include "error.h"
I 4
#include "show.h"
E 4
#include <signal.h>
D 4
#ifdef __STDC__
#include "stdarg.h"
#else
#include <varargs.h>	
#endif
E 4
I 4
#include <unistd.h>
E 4
#include <errno.h>


/*
 * Code to handle exceptions in C.
 */

struct jmploc *handler;
int exception;
volatile int suppressint;
volatile int intpending;
char *commandname;


/*
 * Called to raise an exception.  Since C doesn't include exceptions, we
 * just do a longjmp to the exception handler.  The type of exception is
 * stored in the global variable "exception".
 */

void
D 4
exraise(e) {
E 4
I 4
exraise(e) 
	int e;
{
E 4
	if (handler == NULL)
		abort();
	exception = e;
	longjmp(handler->loc, 1);
}


/*
 * Called from trap.c when a SIGINT is received.  (If the user specifies
 * that SIGINT is to be trapped or ignored using the trap builtin, then
 * this routine is not called.)  Suppressint is nonzero when interrupts
 * are held using the INTOFF macro.  The call to _exit is necessary because
 * there is a short period after a fork before the signal handlers are
 * set to the appropriate value for the child.  (The test for iflag is
 * just defensive programming.)
 */

void
onint() {
I 4
	sigset_t sigset;

E 4
	if (suppressint) {
		intpending++;
		return;
	}
	intpending = 0;
D 4
#ifdef BSD
	sigsetmask(0);
#endif
E 4
I 4
	sigemptyset(&sigset);
	sigprocmask(SIG_SETMASK, &sigset, NULL);
E 4
	if (rootshell && iflag)
		exraise(EXINT);
	else
		_exit(128 + SIGINT);
}



void
error2(a, b)
	char *a, *b;
	{
	error("%s: %s", a, b);
}


/*
 * Error is called to raise the error exception.  If the first argument
 * is not NULL then error prints an error message using printf style
 * formatting.  It then raises the error exception.
 */

D 4
#ifdef __STDC__
E 4
I 4
#if __STDC__
E 4
void
D 4
error(char *msg, ...) {
E 4
I 4
error(char *msg, ...)
E 4
#else
void
error(va_alist)
	va_dcl
D 4
	{
E 4
I 4
#endif
{
#if !__STDC__
E 4
	char *msg;
#endif
	va_list ap;
D 4

E 4
	CLEAR_PENDING_INT;
	INTOFF;
D 4
#ifdef __STDC__
E 4
I 4

#if __STDC__
E 4
	va_start(ap, msg);
#else
	va_start(ap);
	msg = va_arg(ap, char *);
#endif
#ifdef DEBUG
	if (msg)
		TRACE(("error(\"%s\") pid=%d\n", msg, getpid()));
	else
		TRACE(("error(NULL) pid=%d\n", getpid()));
#endif
	if (msg) {
		if (commandname)
			outfmt(&errout, "%s: ", commandname);
		doformat(&errout, msg, ap);
		out2c('\n');
	}
	va_end(ap);
	flushall();
	exraise(EXERROR);
}



/*
 * Table of error messages.
 */

struct errname {
	short errcode;		/* error number */
	short action;		/* operation which encountered the error */
	char *msg;		/* text describing the error */
};


#define ALL (E_OPEN|E_CREAT|E_EXEC)

STATIC const struct errname errormsg[] = {
D 4
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
E 4
I 4
	{ EINTR,	ALL,	"interrupted" },
	{ EACCES,	ALL,	"permission denied" },
	{ EIO,		ALL,	"I/O error" },
	{ ENOENT,	E_OPEN,	"no such file" },
	{ ENOENT,	E_CREAT,"directory nonexistent" },
	{ ENOENT,	E_EXEC,	"not found" },
	{ ENOTDIR,	E_OPEN,	"no such file" },
	{ ENOTDIR,	E_CREAT,"directory nonexistent" },
	{ ENOTDIR,	E_EXEC,	"not found" },
	{ EISDIR,	ALL,	"is a directory" },
#ifdef notdef
	{ EMFILE,	ALL,	"too many open files" },
#endif
	{ ENFILE,	ALL,	"file table overflow" },
	{ ENOSPC,	ALL,	"file system full" },
E 4
#ifdef EDQUOT
D 4
	EDQUOT, ALL,	"disk quota exceeded",
E 4
I 4
	{ EDQUOT,	ALL,	"disk quota exceeded" },
E 4
#endif
#ifdef ENOSR
D 4
	ENOSR, ALL,	"no streams resources",
E 4
I 4
	{ ENOSR,	ALL,	"no streams resources" },
E 4
#endif
D 4
	ENXIO, ALL,	"no such device or address",
	EROFS, ALL,	"read-only file system",
	ETXTBSY, ALL,	"text busy",
E 4
I 4
	{ ENXIO,	ALL,	"no such device or address" },
	{ EROFS,	ALL,	"read-only file system" },
	{ ETXTBSY,	ALL,	"text busy" },
E 4
#ifdef SYSV
D 4
	EAGAIN, E_EXEC,	"not enough memory",
E 4
I 4
	{ EAGAIN,	E_EXEC,	"not enough memory" },
E 4
#endif
D 4
	ENOMEM, ALL,	"not enough memory",
E 4
I 4
	{ ENOMEM,	ALL,	"not enough memory" },
E 4
#ifdef ENOLINK
D 2
	ENOLINK, ALL,	"remote access failed"
E 2
I 2
D 4
	ENOLINK, ALL,	"remote access failed",
E 4
I 4
	{ ENOLINK,	ALL,	"remote access failed" },
E 4
E 2
#endif
#ifdef EMULTIHOP
D 4
	EMULTIHOP, ALL,	"remote access failed",
E 4
I 4
	{ EMULTIHOP,	ALL,	"remote access failed" },
E 4
#endif
#ifdef ECOMM
D 4
	ECOMM, ALL,	"remote access failed",
E 4
I 4
	{ ECOMM,	ALL,	"remote access failed" },
E 4
#endif
#ifdef ESTALE
D 4
	ESTALE, ALL,	"remote access failed",
E 4
I 4
	{ ESTALE,	ALL,	"remote access failed" },
E 4
#endif
#ifdef ETIMEDOUT
D 4
	ETIMEDOUT, ALL,	"remote access failed",
E 4
I 4
	{ ETIMEDOUT,	ALL,	"remote access failed" },
E 4
#endif
#ifdef ELOOP
D 4
	ELOOP, ALL,	"symbolic link loop",
E 4
I 4
	{ ELOOP,	ALL,	"symbolic link loop" },
E 4
#endif
D 4
	E2BIG, E_EXEC,	"argument list too long",
E 4
I 4
	{ E2BIG,	E_EXEC,	"argument list too long" },
E 4
#ifdef ELIBACC
D 4
	ELIBACC, E_EXEC,	"shared library missing",
E 4
I 4
	{ ELIBACC,	E_EXEC,	"shared library missing" },
E 4
#endif
D 4
	0, 0,		NULL
E 4
I 4
	{ 0,		0,	NULL },
E 4
};


/*
 * Return a string describing an error.  The returned string may be a
 * pointer to a static buffer that will be overwritten on the next call.
 * Action describes the operation that got the error.
 */

char *
D 4
errmsg(e, action) {
E 4
I 4
errmsg(e, action) 
	int e;
	int action;
{
E 4
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
