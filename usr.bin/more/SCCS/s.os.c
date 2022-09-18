h30061
s 00002/00002/00255
d D 8.1 93/06/06 15:37:02 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00257
d D 5.12 91/03/01 15:12:07 bostic 12 11
c ANSI
e
s 00001/00012/00257
d D 5.11 90/06/01 17:04:31 bostic 11 10
c new copyright notice
e
s 00002/00001/00267
d D 5.10 89/05/11 13:36:51 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00044/00085/00224
d D 5.9 88/11/22 16:51:40 bostic 9 8
c less -> more
e
s 00002/00004/00307
d D 5.8 88/07/25 12:05:08 bostic 8 7
c update copyright notice
e
s 00012/00011/00299
d D 5.7 88/07/22 12:07:02 bostic 7 6
c use malloc, not calloc; lint cleanups;
e
s 00000/00014/00310
d D 5.6 88/07/21 19:15:07 bostic 6 5
c rip out GLOB define; make default
e
s 00001/00003/00323
d D 5.5 88/07/21 19:07:11 bostic 5 4
c rip out SIGSETMASK define
e
s 00002/00005/00324
d D 5.4 88/07/21 19:04:53 bostic 4 3
c rip out GET_TIME define
e
s 00000/00019/00329
d D 5.3 88/07/21 19:02:44 bostic 3 2
c rip out PERROR define
e
s 00000/00015/00348
d D 5.2 88/07/21 19:01:26 bostic 2 1
c rip out STAT define
e
s 00363/00000/00000
d D 5.1 88/07/21 18:53:09 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 13
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 8
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 8
D 11
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 8
 * by the University of California, Berkeley.  The name of the
E 8
I 8
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 8
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Operating system dependent routines.
 *
 * Most of the stuff in here is based on Unix, but an attempt
 * has been made to make things work on other operating systems.
 * This will sometimes result in a loss of functionality, unless
 * someone rewrites code specifically for the new operating system.
 *
 * The makefile provides defines to decide whether various
 * Unix features are present.
 */

D 9
#include <stdio.h>
E 9
I 9
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
E 9
#include <signal.h>
#include <setjmp.h>
D 9
#include "less.h"
E 9
I 9
#include <stdio.h>
#include <less.h>
I 10
#include "pathnames.h"
E 10
E 9

D 9
char *getenv();
E 9
I 9
int reading;
E 9

D 9
public int reading;

E 9
extern int screen_trashed;

static jmp_buf read_label;

/*
 * Pass the specified command to a shell to be executed.
 * Like plain "system()", but handles resetting terminal modes, etc.
 */
D 9
	public void
E 9
lsystem(cmd)
	char *cmd;
{
	int inp;
	char cmdbuf[256];
D 9
	char *shell;
E 9
I 9
	char *shell, *getenv();
E 9

	/*
	 * Print the command which is to be executed,
	 * unless the command starts with a "-".
	 */
	if (cmd[0] == '-')
		cmd++;
	else
	{
		lower_left();
		clear_eol();
		putstr("!");
		putstr(cmd);
		putstr("\n");
	}

	/*
	 * De-initialize the terminal and take out of raw mode.
	 */
	deinit();
	flush();
	raw_mode(0);

	/*
	 * Restore signals to their defaults.
	 */
	init_signals(0);

	/*
	 * Force standard input to be the terminal, "/dev/tty",
	 * even if less's standard input is coming from a pipe.
	 */
	inp = dup(0);
D 9
	close(0);
	if (open("/dev/tty", 0) < 0)
		dup(inp);
E 9
I 9
	(void)close(0);
D 10
	if (open("/dev/tty", O_RDONLY, 0) < 0)
E 10
I 10
	if (open(_PATH_TTY, O_RDONLY, 0) < 0)
E 10
		(void)dup(inp);
E 9

	/*
	 * Pass the command to the system to be executed.
	 * If we have a SHELL environment variable, use
	 * <$SHELL -c "command"> instead of just <command>.
	 * If the command is empty, just invoke a shell.
	 */
	if ((shell = getenv("SHELL")) != NULL && *shell != '\0')
	{
		if (*cmd == '\0')
			cmd = shell;
		else
		{
D 7
			sprintf(cmdbuf, "%s -c \"%s\"", shell, cmd);
E 7
I 7
			(void)sprintf(cmdbuf, "%s -c \"%s\"", shell, cmd);
E 7
			cmd = cmdbuf;
		}
	}
	if (*cmd == '\0')
		cmd = "sh";

D 9
	system(cmd);
E 9
I 9
	(void)system(cmd);
E 9

	/*
	 * Restore standard input, reset signals, raw mode, etc.
	 */
D 9
	close(0);
	dup(inp);
	close(inp);
E 9
I 9
	(void)close(0);
	(void)dup(inp);
	(void)close(inp);
E 9

	init_signals(1);
	raw_mode(1);
	init();
	screen_trashed = 1;
#if defined(SIGWINCH) || defined(SIGWIND)
	/*
	 * Since we were ignoring window change signals while we executed
	 * the system command, we must assume the window changed.
	 */
	winch();
#endif
}

/*
 * Like read() system call, but is deliberately interruptable.
 * A call to intread() from a signal handler will interrupt
 * any pending iread().
 */
D 9
	public int
E 9
iread(fd, buf, len)
	int fd;
	char *buf;
	int len;
{
	register int n;

	if (setjmp(read_label))
		/*
		 * We jumped here from intread.
		 */
		return (READ_INTR);

	flush();
	reading = 1;
	n = read(fd, buf, len);
	reading = 0;
	if (n < 0)
		return (-1);
	return (n);
}

D 9
	public void
E 9
intread()
{
D 5
#if SIGSETMASK
	sigsetmask(0);
#endif
E 5
I 5
D 9
	sigsetmask(0L);
E 9
I 9
	(void)sigsetmask(0L);
E 9
E 5
	longjmp(read_label, 1);
}

D 4
#if GET_TIME
E 4
D 9
	public long
get_time()
{
D 4
	long t;
E 4
I 4
	time_t time();
E 4

D 4
	time(&t);
	return (t);
E 4
I 4
	return(time((long *)NULL));
E 4
}
D 4
#endif
E 4

E 9
/*
 * Expand a filename, substituting any environment variables, etc.
 * The implementation of this is necessarily very operating system
 * dependent.  This implementation is unabashedly only for Unix systems.
 */
D 6
#if GLOB

E 6
FILE *popen();

D 9
	public char *
E 9
I 9
char *
E 9
glob(filename)
	char *filename;
{
	FILE *f;
	char *p;
	int ch;
D 7
	char *cmd;
E 7
I 7
D 9
	char *cmd, *malloc();
E 7
	static char buffer[FILENAME];
E 9
I 9
	char *cmd, *malloc(), *getenv();
	static char buffer[MAXPATHLEN];
E 9

	if (filename[0] == '#')
		return (filename);

	/*
	 * We get the shell to expand the filename for us by passing
	 * an "echo" command to the shell and reading its output.
	 */
	p = getenv("SHELL");
	if (p == NULL || *p == '\0')
	{
		/*
		 * Read the output of <echo filename>.
		 */
D 7
		cmd = calloc(strlen(filename)+8, sizeof(char));
E 7
I 7
		cmd = malloc((u_int)(strlen(filename)+8));
E 7
		if (cmd == NULL)
			return (filename);
D 7
		sprintf(cmd, "echo \"%s\"", filename);
E 7
I 7
		(void)sprintf(cmd, "echo \"%s\"", filename);
E 7
	} else
	{
		/*
		 * Read the output of <$SHELL -c "echo filename">.
		 */
D 7
		cmd = calloc(strlen(p)+12);
E 7
I 7
		cmd = malloc((u_int)(strlen(p)+12));
E 7
		if (cmd == NULL)
			return (filename);
D 7
		sprintf(cmd, "%s -c \"echo %s\"", p, filename);
E 7
I 7
		(void)sprintf(cmd, "%s -c \"echo %s\"", p, filename);
E 7
	}

	if ((f = popen(cmd, "r")) == NULL)
		return (filename);
	free(cmd);

	for (p = buffer;  p < &buffer[sizeof(buffer)-1];  p++)
	{
		if ((ch = getc(f)) == '\n' || ch == EOF)
			break;
		*p = ch;
	}
	*p = '\0';
D 9
	pclose(f);
	return (buffer);
E 9
I 9
	(void)pclose(f);
	return(buffer);
E 9
}
D 6

#else

	public char *
glob(filename)
	char *filename;
{
	return (filename);
}

#endif

E 6

D 9
/*
 * Returns NULL if the file can be opened and
 * is an ordinary file, otherwise an error message
 * (if it cannot be opened or is a directory, etc.)
 */

D 2
#if STAT

E 2
#include <sys/types.h>
#include <sys/stat.h>

	public char *
E 9
I 9
char *
E 9
bad_file(filename, message, len)
D 9
	char *filename;
	char *message;
	unsigned int len;
E 9
I 9
	char *filename, *message;
	u_int len;
E 9
{
I 9
	extern int errno;
E 9
	struct stat statbuf;
I 7
D 9
	char *strcat();
E 9
I 9
	char *strcat(), *strerror();
E 9
E 7

D 9
	if (stat(filename, &statbuf) < 0)
		return (errno_message(filename, message, len));

	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
	{
E 9
I 9
	if (stat(filename, &statbuf) < 0) {
		(void)sprintf(message, "%s: %s", filename, strerror(errno));
		return(message);
	}
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
E 9
		static char is_dir[] = " is a directory";
D 9
		strtcpy(message, filename, len-sizeof(is_dir)-1);
E 9
I 9

		strtcpy(message, filename, (int)(len-sizeof(is_dir)-1));
E 9
D 7
		strcat(message, is_dir);
E 7
I 7
		(void)strcat(message, is_dir);
E 7
D 9
		return (message);
E 9
I 9
		return(message);
E 9
	}
D 9
	if ((statbuf.st_mode & S_IFMT) != S_IFREG)
	{
		static char not_reg[] = " is not a regular file";
		strtcpy(message, filename, len-sizeof(not_reg)-1);
D 7
		strcat(message, not_reg);
E 7
I 7
		(void)strcat(message, not_reg);
E 7
		return (message);
	}
	return (NULL);
E 9
I 9
	return((char *)NULL);
E 9
}
D 2

#else

	public char *
bad_file(filename, message, len)
	char *filename;
	char *message;
	unsigned int len;
{
	return (NULL);
}

#endif
E 2

/*
D 9
 * errno_message: Return an error message based on the value of "errno".
 * okreadfail: Return true if the previous failure of a read
 *	(on the input tty) should be considered ok.
E 9
I 9
 * Copy a string, truncating to the specified length if necessary.
 * Unlike strncpy(), the resulting string is guaranteed to be null-terminated.
E 9
 */
D 9

D 3
#if PERROR

E 3
extern char *sys_errlist[];
extern int sys_nerr;
extern int errno;

	public char *
errno_message(filename, message, len)
	char *filename;
	char *message;
	unsigned int len;
E 9
I 9
D 12
static
E 12
strtcpy(to, from, len)
	char *to, *from;
	int len;
E 9
{
D 9
	char *p;
	char msg[16];
E 9
I 9
	char *strncpy();
E 9

D 9
	if (errno < sys_nerr)
		p = sys_errlist[errno];
	else
	{
D 7
		sprintf(msg, "Error %d", errno);
E 7
I 7
		(void)sprintf(msg, "Error %d", errno);
E 7
		p = msg;
	}
	strtcpy(message, filename, len-strlen(p)-3);
D 7
	strcat(message, ": ");
	strcat(message, p);
E 7
I 7
	(void)strcat(message, ": ");
	(void)strcat(message, p);
E 7
	return (message);
E 9
I 9
	(void)strncpy(to, from, (int)len);
	to[len-1] = '\0';
E 9
}
I 9

E 9
D 3

#else

	public char *
errno_message(filename, message, len)
	char *filename;
	char *message;
	unsigned int len;
{
	static char msg[] = ": cannot open";

	strtcpy(message, filename, len-sizeof(msg)-1);
	strcat(message, msg);
	return (message);
}

#endif
E 3
E 1
