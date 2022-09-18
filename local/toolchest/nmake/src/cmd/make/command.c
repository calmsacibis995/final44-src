/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * G. S. Fowler
 * AT&T Bell Laboratories
 */

/*
 * make command execution routines
 */

#include "make.h"

#include <signal.h>

#define MSGFD	9		/* coshell message pipe (4<=MSGFD<=9)	*/

static int	copid = -1;	/* coshell pid (< 0 if no coshell)	*/
static int	cocmd;		/* coshell command fd			*/
static int	comsg;		/* coshell message fd			*/
static int	cojobs;		/* number of current coshell jobs	*/

static void	coshell();
static void	coinit();
static void	cosend();
static void	statetime();

/*
 * execute a command sequence (or touch the current target)
 * rule r contains the command attributes
 * `always' causes cmd to always be executed
 */

void
docmd(r, cmd, always)
register struct ruleinfo	*r;
char				*cmd;
int				always;
{
	char	buf[MAXCMD];

	special.target->status = EXISTS;
	if (cmd)
	{
		state.work = 1;
		if (state.question);
		else if (r->cmdspecial) error(INTERNAL, "`%s' has [cmdspecial] attribute", r->name);
		else if (r->make) parse(cmd, r->name, r->operator ? 0 : 1);
		else if (state.touch)
		{
			r = special.target;
			if (r->state)
			{
				if (!state.silent) error(0, "touch(%s)", r->name);
				if (state.exec)
				{
					r->time = CURTIME;
					state.savestate = 1;
				}
			}
			else if (r->archive)
			{
				if (state.exec)
				{
					touchar(r->name, (char*)0);
					if (r->statedeps || r->search) statetime(r);
				}
			}
			else if (r->link && r->link->archive)
			{
				(void)edit(buf, r->name, DELETE, DELETE, DELETE, KEEP, KEEP);
				if (strcmp(buf, r->name))
				{
					if (!r->uname) r->uname = r->name;
					r->name = putrule(buf, r);
				}
				if (state.exec) touchar(r->link->name, r->name);
				else if (!state.silent) error(0, "touch(%s[%s])", r->link->name, r->name);
			}
			else
			{
				if (!state.silent) error(0, "touch(%s)", r->name);
				if (state.exec)
				{
					touch(r->name);
					if (r->statedeps || r->search) statetime(r);
				}
			}
		}
		else if (state.exec || always)
		{
			(void)expand(cmd, buf);
			coshell(buf);
		}
		else if (!state.silent)
		{
			(void)expand(cmd, buf);
			dumpcmd(stdout, buf, "+ ");
		}
	}
}

#define MAXCMDOPEN	4	/* max number simultaneous cmdopen()'s	*/

static struct
{
	FILE	*fd;		/* returned by cmdopen()		*/
	int	pid;		/* pid used by cmdopen()		*/
} cmdproc[MAXCMDOPEN];

/*
 * fork and exec cmd(argv) with fd as stdin of the command
 * the standard output of cmd is returned
 */

FILE*
cmdopen(fd, cmd, argv)
FILE	*fd;
char	*cmd;
char	**argv;
{
	register int	i, proc;
	int		pio[2];

	for (proc = 0; proc < MAXCMDOPEN; proc++)
		if (!cmdproc[proc].fd) break;
	if (proc >= MAXCMDOPEN) error(INTERNAL, "%s: too many cmdopen() calls", cmd);
	if (pipe(pio)) error(INTERNAL, "cannot create %s pipe", *argv);
	i = fileno(fd);
	switch (cmdproc[proc].pid = vfork())
	{
	case -1:
		error(INTERNAL, "cannot fork %s", *argv);
		break;
	case 0:
		state.child = 1;
		if (i != 0)
		{
			(void)close(0);
			if (dup2(i, 0) != 0)
				error(INTERNAL, "cannot set up %s input", *argv);
			(void)close(i);
		}
		(void)close(1);
		if (dup2(pio[1], 1) != 1)
			error(INTERNAL, "cannot set up %s output", *argv);
		(void)close(pio[0]);
		(void)close(pio[1]);
		execvp(cmd, argv);
		error(INTERNAL, "cannot exec %s", cmd);
		break;
	default:
		state.child = 0;
		(void)close(pio[1]);
		if (i != 0) (void)fclose(fd);
		if (!(cmdproc[proc].fd = fdopen(pio[0], "r")))
			error(INTERNAL, "cannot get %s output", *argv);
		break;
	}
	return(cmdproc[proc].fd);
}

/*
 * close a stream opened by cmdopen()
 */

void
cmdclose(fd)
FILE	*fd;
{
	register int	i, pid;

	for (i = 0; i < MAXCMDOPEN; i++)
		if (fd == cmdproc[i].fd) break;
	if (i < MAXCMDOPEN)
	{
		fclose(fd);
		cmdproc[i].fd = (FILE*)0;
		pid = cmdproc[i].pid;
		while ((i = wait((int*)0)) != pid && i != -1);
	}
#if DEBUG
	else error(INTERNAL, "cmdclose(): fd not opened by cmdopen()");
#endif
}

/*
 * similar to system(), but only one shell is forked
 * MSGFD is used for message sending between the coshell and caller
 *
 * the shell environment remains intact between coshell() calls
 */

static void
coshell(cmd)
register char	*cmd;
{
	if (copid < 0) coinit();
	cosend(cmd);
}

/*
 * initialize the coshell
 */

static void
coinit()
{
	register char	*sh;
	int		pio[2], pex[2];
	int		oforeground, osilent;
	struct ruleinfo	*otarget;

	(void)signal(SIGPIPE, SIG_IGN);
	if (pipe(pio) < 0 || pipe(pex) < 0) error(INTERNAL, "cannot create shell pipes");
	cocmd = pio[1];
	comsg = pex[0];
	switch (copid = vfork())
	{
	case -1:
		error(INTERNAL, "cannot fork shell");
		return;
	case 0:
		state.child = 1;
		setpgrp(getpid(), getpid());	/* NOTE: args may be ignored */
		(void)close(pio[1]);
		(void)close(pex[0]);
		(void)close(MSGFD);
		if (dup2(pex[1], MSGFD) != MSGFD)
			error(INTERNAL, "cannot set up shell message pipe");
		(void)close(pex[1]);
		(void)close(0);
		if (dup2(pio[0], 0) != 0)
			error(INTERNAL, "cannot set up shell input");
		(void)close(pio[0]);
		if (!*(sh = getval("MAKESHELL"))) sh = getval("SHELL");
		execl(sh, "sh", (char*)0);
		error(INTERNAL, "cannot exec %s", sh);
		break;
	default:
		state.child = 0;
		(void)close(pio[0]);
		(void)close(pex[1]);
		oforeground = state.foreground;
		state.foreground = 1;
		osilent = state.silent;
		state.silent = 1;
		otarget = special.target;
		special.target = special.internal;

		/*
		 * send the shell initialization script
		 */

		(void)sprintf(buf2, "\
if alias @='_make_ read'\n\
then\n\
exec %d>&%d %d>&%d %d>&-\n\
function _make_\n\
{\n\
	set +x\n\
	print -nu%d - '\\01' $_id_ \"$@\" '\\01'\n\
}\n\
alias ignore='ignore '\n\
function ignore\n\
{\n\
	set +x\n\
	\"$@\"\n\
	return 0\n\
}\n\
alias silent='set +x;silent '\n\
function silent\n\
{\n\
%s%s		\"$@\"\n\
}\n\
unalias echo\n\
function echo\n\
{\n\
	set +x\n\
	print - \"$@\"\n\
}\n\
unalias pwd\n\
function pwd\n\
{\n\
	set +x\n\
	print - $PWD\n\
}\n\
typeset -xf _make_ ignore silent echo pwd\n\
trap 'set %s$?; _make_ error $1%s' ERR\n\
else\n\
set %ce\n\
fi\n\
%s\
",
			MSGFD-1, MSGFD, MSGFD, MSGFD-1, MSGFD-1,
			MSGFD,
			osilent ? null : "\t\ttrap 'set -x' 0\n",
			state.dump ? "\t\tset -x\n" : null,
			(state.dump || osilent) ? null : "+x ",
			state.ignore ? null : "; exit 1",
			state.ignore ? '+' : '-',
			state.dump ? "set -x" : null);
		cosend(buf2);
		state.foreground = oforeground;
		state.silent = osilent;
		special.target = otarget;
		break;
	}
}

/*
 * send a command to the coshell
 */

static void
cosend(cmd)
char	*cmd;
{
	register int	id, n;
	char		*toff, *ton;

	while (cojobs >= state.maxjobs && cowait() >= 0);
	for (id = 0; id < state.maxjobs; id++)
		if (!jobs[id].target)
			break;
	special.target->status = MAKING;
	jobs[id].target = special.target;
	jobs[id].errors = 0;
	cojobs++;
	toff = (state.dump || state.silent) ? null : "set +x\n";
	ton = (state.dump || state.silent) ? null : "set -x\n";
	(void)sprintf(buf0, "{\n%s", toff);
	n = strlen(buf0);
	if (!state.foreground && state.jobs)
	{
		(void)sprintf(buf0 + n, "trap 'set %s$?; _make_ error $1%s' ERR\n",
			(state.dump || state.silent) ? null : "+x ",
			state.ignore ? null : "; exit 1");
		n += strlen(buf0 + n);
	}
	(void)sprintf(buf0 + n, "_id_=%d\n%s%s\n%s_make_ exit\n%s}</dev/null",
		id, ton, cmd, toff, ton);
	n += strlen(buf0 + n);
	if (!state.foreground && state.jobs)
	{
		(void)sprintf(buf0 + n, "&\n%s_make_ start %d $!\n%s",
			toff, id, ton);
		n += strlen(buf0 + n);
	}
	(void)sprintf(buf0 + n, "\n");
	n += strlen(buf0 + n);
#if DEBUG
	if (state.debug <= -3) dumpcmd(stderr, buf0, "make: (debug 3) shell: ");
#endif
	if (write(cocmd, buf0, n) != n)
	{
		jobs[id].target = (struct ruleinfo*)0;
		cojobs--;
		error(2, "cannot send `%s' commands to shell", special.target->name);
	}
	if (state.foreground) (void)complete(NIL, special.target);
}

/*
 * coshell _make_ command definitions
 */

#define X_ERROR		0
#define X_EXIT		1
#define X_READ		2
#define X_START		3

static char	*cmds[] =	/* coshell _make_ commands	*/
{
	"error",		/* X_ERROR			*/
	"exit",			/* X_EXIT			*/
	"read",			/* X_READ			*/
	"start",		/* X_START			*/
	(char*)0		/* last				*/
};

/*
 * interpret coshell _make_ commands until the
 * completion message is received
 */

int
cowait()
{
	register char			*s;
	register int			n, x;
	register struct ruleinfo	*r;
	int				id, clear;
	char				*cmd, *data;
	static int			cmdnum = 0;

	if (cojobs <= 0) return(-1);
#if DEBUG
	if (state.debug <= -3)
	{
		message(-3, "jobs:");
		for (n = 0; n < state.maxjobs; n++)
			if (r = jobs[n].target)
				message(-3, "\t[%d] %s", n, r->name);
	}
#endif
	for (clear = 0;;)
	{
		/*
		 * read and parse a coshell _make_ command line of the form
		 *
		 *	<delim> <id> <command> <data> <delim>
		 *         %c    %d     %s       %s      %c
		 *
		 * <delim> must not occur in any other context
		 */

		s = buf0;
		x = comsg;
		if (read(x, s, 1) != 1) break;
		n = *s;
		while (read(x, s, 1) == 1 && *s++ != n);
		if (*--s != n) break;
		*s = '\0';
		for (s = buf0; ctype[*s] & C_SPACE; s++);
		id = atoi(s);
		while (*s && !(ctype[*s] & C_SPACE)) s++;
		while (ctype[*s] & C_SPACE) s++;
		cmd = s;
		while (*s && !(ctype[*s] & C_SPACE)) s++;
		if (*s) *s++ = '\0';
		while (ctype[*s] & C_SPACE) s++;
		data = s;
#if DEBUG
		message(-3, "coshell message = `%d %s%s%s'", id, cmd, *data ? " " : null, data);
#endif

		/*
		 * now interpret the command
		 */

		for (x = 0; cmds[x] && strcmp(cmds[x], cmd); x++);
		if (x != X_START && !jobs[id].target) error(INTERNAL, "_make_ %s: coshell status sequencing error", cmd);
		switch (x)
		{
		case X_ERROR:
			/*
			 * <data> is the error exit code for a single command
			 */

			n = atoi(data);
			if (!n)
			{
				error(1, "the shell does not have trap on command error");
				break;
			}
			if (!state.ignore || state.keepgoing) jobs[id].errors++;
			error(0, "*** exit code %d making `%s'", n, jobs[id].target->name);
			if (state.ignore) break;
			clear = 1;
			/* fall through ... */

		case X_EXIT:
			/*
			 * a command packet has completed
			 */

			r = jobs[id].target;
			jobs[id].target = (struct ruleinfo*)0;
			r->status = jobs[id].errors ? FAILED : EXISTS;
			if (r->statedeps || r->search) statetime(r);
			if (jobs[id].pid)
			{
				/*
				 * avoid the dreaded zombie
				 */

				(void)sprintf(buf0, "%swait %d\n%s",
					(state.dump || state.silent) ? null : "set +x\n",
					jobs[id].pid,
					(state.dump || state.silent) ? null : "set -x\n");
				n = strlen(buf0);
#if DEBUG
				if (state.debug <= -3) dumpcmd(stderr, buf0, "make: (debug 3) shell: ");
#endif
				if (write(cocmd, buf0, n) != n)
					error(2, "cannot send zombie wait command to shell");
				jobs[id].pid = 0;
			}
			cojobs--;
			if (!clear) return(jobs[id].errors);
			else if (cojobs <= 0) finish(1);
			break;

		case X_READ:
			/*
			 * <data> is a line for make to read and parse
			 */

			parse(data, "coshell command", ++cmdnum);
			break;
		
		case X_START:
			/*
			 * <data> is the id and pid for a background job
			 */

			id = atoi(data);
			for (s = data; *s && !(ctype[*s] & C_SPACE); s++);
			while (ctype[*s] & C_SPACE) s++;
			jobs[id].pid = atoi(s);
			break;
		
		default:
			/*
			 * unknown command
			 */

			error(1, "_make_ %s: unknown command from shell", cmd);
			break;
		}
	}
	cojobs = 0;
	if (!state.cleanup && !state.interrupt) error(2, "lost contact with shell");
	return(-1);
}

/*
 * wait until all rules in list p (or rule r) have status EXISTS or FAILED
 * return the number of FAILED rules
 */

int
complete(p, r)
register struct list		*p;
register struct ruleinfo	*r;
{
	register int	errors = 0;
	struct list	tmp;

	if (!p && r)
	{
		p = &tmp;
		p->item.rule = r;
		p->next = NIL;
	}
	while (p)
	{
		r = p->item.rule;
		if (r->status == MAKING)
		{
			message(-1, "waiting for `%s'", r->name);
			if (cowait() < 0)
				error(INTERNAL, "`%s' never made", r->name);
		}
		else
		{
			if (r->status == FAILED) errors++;
			p = p->next;
		}
	}
	return(errors);
}

/*
 * called when coshell is hung
 */

static void
cohung()
{
	error(1, "the shell probably has a non-terminated child");
	kill(copid, SIGTERM);
}

/*
 * kill the coshell and its children with sig
 */

void
cokill(sig)
int	sig;
{
	int		i;
	int		(*asig)(), (*isig)(), (*qsig)();

	if (copid >= 0)
	{
		if (sig == SIGKILL)
		{
			while (cowait() >= 0);
			if (state.jobs && write(cocmd, "wait\n", 5) != 5)
				error(2, "cannot send final wait command to shell");
			(void)close(comsg);
			(void)close(cocmd);
			asig = signal(SIGALRM, cohung);
			isig = signal(SIGINT, SIG_IGN);
			qsig = signal(SIGQUIT, SIG_IGN);
			alarm(3);
			while ((i = wait((int*)0)) != copid && i != -1);
			(void)signal(SIGALRM, asig);
			(void)signal(SIGINT, isig);
			(void)signal(SIGQUIT, qsig);
			copid = -1;
		}
		else killpg(copid, sig);
	}
}

/*
 * update internal time of files with state variable dependencies
 */

static void
statetime(r)
register struct ruleinfo	*r;
{
	char		nam[MAXNAME];
	struct stat	sbuf;

	if (r->status == FAILED) r->time = DEFTIME;
	else
	{
		if (!stat(r->name, &sbuf)) r->time = sbuf.st_mtime;
		if (r->search && !state.touch) (void)finddeps(r);
	}
	(void)edit(nam, unbound(r), DELETE, r->member ? DELETE : KEEP, DELETE, KEEP, KEEP);
	(void)strcat(nam, "()");
	makerule(nam)->time = r->time;
	state.savestate = 1;
}
