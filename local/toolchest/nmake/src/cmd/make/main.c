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
 * make - maintain and update programs
 *
 *	S. I. Feldman			1976 original
 *	E. G. Bradford			1979 second generation (augmented make)
 *	V. B. Erickson, J. F. Pellegrin	1982 third generation (build)
 *	G. S. Fowler			1985 fourth generation
 *
 * options:
 *
 *	-b	don't use builtin rules
 *	-c	don't execute but force the input makefiles to be compiled
 *	-d<n>	list level <n> debugging comments
 * 	-f	the next argument is the name of a makefile
 *	-g	the next argument is a global makefile
 *	-h	don't search for implicit file dependencies
 * 	-i	ignore error codes from the shell
 *	-j<n>	put update commands in upto <n> background jobs
 *	-k	continue with sibling deps on error
 *	-l	don't execute but list all symbol and rule definitions
 *	-m	move targets to corresponding source directory
 * 	-n	don't execute but list actions
 *	-o	output equivalent omake makefile
 * 	-q	don't execute but exit 0 if up to date, otherwise exit -1
 *	-r	list rule definitions
 * 	-s	run silently without listing actions
 * 	-t	don't execute but touch (modify time of) out of date rules
 *	-u	don't check for duplicate files
 *	-v	list variable definitions
 *	-x	don't check implicit file dependencies
 *	-A	accept all existing targets
 *	-D	passed to preprocessor
 *	-F	force target updates
 *	-H	search for implicit file and state var dependencies
 *	-I	passed to preprocessor
 *	-M	act as if no target has been made
 *	-O	override explicit rules
 *	-R	force all makefiles to be read
 *	-S	ignore state variable definitions
 *	-T	enable test code
 *	-U	passed to preprocessor
 *	-V	list the current program version
 *
 * debug trace levels are controlled by the -d option
 * debug level n enables tracing for all levels less than or equal to n
 * levels three and higher are enabled with the DEBUG compile switch
 *
 *	level	trace
 *	  0	no trace
 *	  1	basic make trace
 *	  2	major actions
 *	  3	coshell messages
 *	  4	state variables, make object info
 *	  5	makefile input lines
 *	  6	directory and archive scan info, hash table info
 *	  7     files added to hash, detailed hash table info
 *	  8	builtin rule input lines
 *	  9	lexical analyzer states
 */

#include "make.h"

#include <signal.h>

#define NPPARGS	20	/* maximum number of preprocessor args		*/
#define PPOPTS	"DIU"	/* preprocessor option flags			*/

char		*ppargv[NPPARGS+3];		/* make room for 2 more	*/
int		ppargc = 1;			/* always have cmd name	*/

char		null[]		= "";		/* null string		*/
char		flags[32]	= "-";		/* set option flags	*/
char		buf0[MAXCMD];			/* work 0		*/
char		buf1[MAXCMD];			/* work 1		*/
char		buf2[MAXCMD];			/* work 2		*/

char		**args;		/* global argv				*/
unsigned char	*argf;		/* ARG_* flags for args			*/

static int	signals[] =	/* signals caught by interrupt()	*/
{
	SIGHUP,
	SIGINT,
	SIGQUIT,
	SIGILL,
	SIGIOT,
	SIGEMT,
	SIGBUS,
	SIGSEGV,
	SIGSYS,
	SIGALRM,
	SIGTERM,
	0			/* last entry */
};

struct specinfo		special;

struct stateinfo	state;

struct jobinfo		jobs[MAXJOBS];

short			ctype[128];

static struct ruleinfo	*getdyn();
static struct ruleinfo	*rspecial();
static char		*vspecial();
static int		inherit();

#define settype(c,t)	for(s=c;*s;ctype[*s++]|=(t))

/*
 * make entry point
 */

main(argc, argv)
int		argc;
char		*argv[];
{
	register char			*s;
	register struct ruleinfo	*r;
	register struct list		*p, *q;
	int				i;
	char				name[MAXNAME];

	extern int			interrupt();

	/*
	 * initialize dynamic globals
	 */

#if STRICT_NAME
	special.command = (s = strrchr(argv[0], '/')) ? s + 1 : argv[0];
#else
	special.command = "make";
#endif
	setbuf(stderr, malloc((unsigned)BUFSIZ));
	settype(":=+", C_COLEQU);
	settype(";&()|<>\n \t*?[]$\\'`\"", C_SHELL);
	settype(" \t\v", C_SPACE);
	settype("():|", C_SYMBOL);
	settype("\n\t ;{}[]&\"\\", C_TERMINAL);
	ctype['\0'] |= C_TERMINAL;
	settype("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._", C_VARIABLE);
	args = argv;
	argf = (unsigned char*)malloc(argc * sizeof(unsigned char));
	for (i = 0; i < argc; i++) argf[i] = 0;
	init();

	/*
	 * set the default state
	 */

	state.autocompile = 1;
	state.builtin = 1;
	state.exec = 1;
	state.implicit = 1;
	state.maxjobs = 1;
	state.readstate = 1;
	state.search = 1;
	state.unique = 1;
	state.start = CURTIME;

	/*
	 * read command line options
	 */

	state.readonly = 1;
	setopts(argc, argv, argf);
	state.readonly = 0;
	if (state.compileonly) state.forceread = 1;

	/*
	 * initialize some special variables
	 */

	state.import = 1;
#if RANLIB
	special.arupdate = setvar("ARUPDATE", ARUPDATE);
#else
	special.arupdate = setvar("ARUPDATE", null);
#endif
	(void)vspecial("MAKE", argv[0]);
	(void)vspecial("SHELL", DMAKESHELL);
	special.pp = vspecial("MAKEPP", DMAKEPP);
	special.rules = vspecial("MAKERULES", DMAKERULES);
	state.import = 0;

	/*
	 * initialize the internal rule pointers
	 */

	initrules();

	/*
	 * check for builtin rules file
	 */

	if (state.builtin && *special.rules && !readfile(special.rules))
		error(2, "cannot read %s", special.rules);

	/*
	 * read global makefiles
	 */

	state.builtin = 1;
	for (i = 1; i < argc; i++)
		if (argf[i] & ARG_GLOBAL)
		{
			if (i >= argc - 1) error(2, "no makefile after -g option");
			argf[i] |= ARG_USED;
			argf[++i] |= ARG_USED;
			if (!readfile(argv[i])) error(2, "cannot read %s", argv[i]);
		}
	state.builtin = 0;

	/*
	 * read environment variables
	 */

	message(-2, "reading environment");
	readenv();

	/*
	 * read command line args
	 */

	state.readonly = 1;
	for (i = 1; i < argc; ++i)
		if (!(argf[i] & ARG_USED) && argv[i][0] != '-' && any(argv[i], C_COLEQU|C_SPACE|C_TERMINAL))
		{
			argf[i] |= ARG_USED;
			parse(argv[i], "command argument", i);
		}
	state.readonly = 0;

	/*
	 * read explicit makefiles
	 */

	state.firstfile = 1;
	for (i = 1; i < argc; i++)
		if (argf[i] & ARG_FILE)
		{
			if (i >= argc - 1) error(2, "no makefile after -f option");
			argf[i] |= ARG_USED;
			argf[++i] |= ARG_USED;
			if (!readfile(argv[i])) error(2, "cannot read %s", argv[i]);
		}

	/*
	 * if no explicit makefiles then try .MAKEFILES
	 */

	if (state.firstfile)
		for (p = getdyn(makerule(".MAKEFILES")->name)->deps; p; p = p->next)
			if (readfile(p->item.rule->name))
				break;

	/*
	 * if no explicit or implicit makefiles then try
	 * first arg with MAKESOURCE suffix
	 */

	if (state.firstfile)
		for (i = 1; i < argc; i++)
			if (!(argf[i] & ARG_USED))
			{
				(void)edit(name, argv[i], DELETE, KEEP, DELETE, KEEP, MAKESOURCE);
				if (readfile(name)) argf[i] |= ARG_USED;
				break;
			}

	/*
	 * check and save makefile dependencies
	 */

	readcheck();
	if (state.objectfile) makerule(state.objectfile)->deps = state.dependencies;

	/*
	 * check if makefiles to be compiled
	 */

	if (state.compile && state.objectfile) compile(state.objectfile);

	/*
	 * reset makefile dependency times
	 */

	for (p = state.dependencies; p; p = p->next)
		p->item.rule->time = DEFTIME;

	/*
	 * check for listing of variable and rule definitions
	 */

	if (state.list)
	{
		exhash(rultab, inherit);
		dump(0);
		exit(0);
	}
	if (state.compileonly) exit(0);
	state.autocompile = 0;

	/*
	 * check some special rules (only once!)
	 */

	if (special.prefixes->dynamic) dynamic(special.prefixes);
	if (special.suffixes->dynamic) dynamic(special.suffixes);

	/*
	 * read state variables
	 */

	if (!state.statefile)
	{
		/*
		 * use the base of the first arg if no makefile
		 */

		for (i = 1; i < argc; i++)
			if (!(argf[i] & ARG_USED))
			{
				(void)edit(name, argv[i], DELETE, KEEP, DELETE, KEEP, MAKESTATE);
				state.statefile = COPY(name);
			}
	}
	if (state.readstate) readstate(state.statefile);

	/*
	 * make the makeinit target in foreground if specified
	 * command line variable definitions may be modified by these rules
	 */

	if (r = getrule(".MAKEINIT"))
	{
		state.foreground = state.made = 1;
		make(r);
		state.foreground = state.made = 0;
	}

	/*
	 * check directories to scan
	 */

	if (r = getdyn(".SOURCE"))
		for (p = r->deps; p; p = p->next)
			search(p->item.rule->name);
	else error(1, "no source directory list");
	if (!special.suffixes->deps) error(1, "no suffix list");
	else for (p = special.suffixes->deps; p; p = p->next)
	{
		sprintf(buf0, ".SOURCE%s", p->item.rule->name);
		if (r = getdyn(buf0))
			for (q = r->deps; q; q = q->next)
				search(q->item.rule->name);
	}
	for (p = special.prefixes->deps; p; p = p->next)
	{
		sprintf(buf0, "%s.SOURCE", p->item.rule->name);
		if (r = getdyn(buf0))
			for (q = r->deps; q; q = q->next)
				search(q->item.rule->name);
	}

	/*
	 * check inherited attribute suffixes
	 */

	exhash(rultab, inherit);

	/*
	 * set up signal handlers
	 */

	for (i = 0; signals[i]; i++)
		if (signal(signals[i], interrupt) == SIG_IGN)
			(void)signal(signals[i], SIG_IGN);

	/*
	 * make init target in foreground if specified
	 */

	if (r = getrule(".INIT"))
	{
		state.foreground = 1;
		make(r);
		state.foreground = state.made = 0;
	}

	/*
	 * make command line targets
	 */

	for (i = 1; i < argc; i++)
		if (!(argf[i] & ARG_USED))
		{
			argf[i] |= ARG_USED;
			if (state.firstfile) r = makerule(argv[i]);
			else r = getrule(argv[i]);
			if (!r)
			{
				/*
				 * if a makefile was specified then
				 * try `.TARGET' if `target' not defined
				 */

				*buf0 = '.';
				(void)strcpy(buf0 + 1, argv[i]);
				for (s = buf0 + 1; islower(*s); s++)
					*s = toupper(*s);
				if (*s || !(r = getrule(buf0)))
					r = makerule(argv[i]);
			}
			make(r);
		}

	/*
	 * make .MAIN if no explicit target was specified
	 */

	if (!state.made)
	{
		if (p = special.main->deps)
			for (; p; p = p->next)
				make(p->item.rule);
		else error(2, "no target argument or%s makefile", state.firstfile ? null : " main target specified in");
	}

	/*
	 * finish up
	 */

	finish(0);
	/*NOTREACHED*/
}

/*
 * clean up and exit
 */

finish(n)
int	n;
{
	struct ruleinfo	*r;
	static int	phase = 0;

	if (phase == 0)
	{
		if (!state.cleanup)
		{
			/*
			 * initial phase -- start delicate cleanup actions
			 */

			state.cleanup = 1;
			message(-1, "%s cleanup", n < 0 ? "interrupt" : n > 0 ? "error" : "normal");

			/*
			 * ignore interrupts for some important actions
			 */

			state.interrupt = 1;

			/*
			 * put all jobs in foreground
			 */

			state.jobs = 0;
			state.list = 0;
		}

		/*
		 * wait for any job(s) to finish
		 */

		while (cowait() >= 0);

		/*
		 * save state variables
		 */

		phase = 1;
		savestate(state.statefile);

		/*
		 * enable interrupts
		 */

		state.interrupt = 0;
		phase = 2;
	}
	if (phase == 1)
	{
		phase = 4;

		/*
		 * error during delicate phase 1 -- exit right away
		 */

#if DEBUG
		if (n < 0) error(INTERNAL, "interrupt during cleanup phase 1");
#endif
		n = 3;
	}
	if (phase == 2)
	{
		phase = 3;

		/*
		 * execute post commands and make done target if specified
		 */

		dopost();
		if (r = getrule(".DONE")) make(r);
	}
	if (phase == 3)
	{
		phase = 4;

		/*
		 * kill the coshell and dump
		 */
		
		cokill(SIGKILL);
		dump(state.debug <= -6);
	}
	if (phase == 4)
	{
		/*
		 * exit
		 */

		message(-1, "%s exit", n < 0 ? "interrupt" : n > 0 ? "error" : "normal");
		if (n >= 0) exit(n);
	}
}

/*
 * catch interrupts
 */

interrupt(sig)
int	sig;
{
	register int			id;
	register struct ruleinfo	*r;
	static int			hadinterrupt = 0;

	/*
	 * temporarily block this signal
	 */

	(void)signal(sig, SIG_IGN);
	freesignal(sig);

	/*
	 * return if already processing an interrupt
	 */

	if (state.interrupt)
	{
		(void)signal(sig, interrupt);
		if (sig == SIGINT || sig == SIGTERM)
		{
			if (hadinterrupt) exit(9);
			hadinterrupt = 1;
			if (sig == SIGINT) error(1, "cleaning up -- one more interrupt clobbers the state variables");
		}
		return;
	}
	state.interrupt = 1;

	/*
	 * flush the output streams
	 */

	fflush(stderr);
	printf("\n");
	fflush(stdout);

	/*
	 * remove any dangling targets
	 */

	for (id = 0; id < state.maxjobs; id++)
		if ((r = jobs[id].target) && r->status == MAKING && !precious(r))
	{
		if (!unlink(r->name)) error(0, "*** %s removed", r->name);
		else if (errno != ENOENT) error(0, "*** %s not removed", r->name);
	}

	/*
	 * make interrupt target in foreground if specified
	 */

	state.jobs = 0;
	if (r = getrule(".INTERRUPT")) make(r);

	/*
	 * pass the interrupt to the coshell
	 */

	if (sig == SIGHUP) cokill(sig);
	else cokill(SIGTERM);

	/*
	 * clean up
	 */

	finish(-1);

	/*
	 * restore the default action and deliver the signal
	 */

	(void)signal(sig, SIG_DFL);
	kill(getpid(), sig);
	pause();
}

/*
 * using .PRECIOUS, determine if a bound rule can be unlinked
 * if .PRECIOUS has no dependencies then all targets are precious
 * rules with .ARCHIVE attribute are always precious
 */

precious(r)
register struct ruleinfo	*r;
{
	register struct ruleinfo	*t;
	register struct list		*p;

	if (r->archive || r == special.internal || state.override) return(1);
	if (t = getdyn(".PRECIOUS"))
	{
		if (!(p = t->deps)) return(1);
		for (; p; p = p->next)
			if (r == p->item.rule)
				return(1);
	}
	return(0);
}


/*
 * set the internal options from the command line arguments
 */

setopts(argc, argv, argf)
int		argc;
char		*argv[];
unsigned char	*argf;
{
	register int	c, i, j, n, v;
	char		flag = ARG_USED;

	for (i = 1; i < argc; i++)
	{
		if (flag != ARG_USED) flag = ARG_USED;
		else if ((!argf || !(argf[i] & ARG_USED)) && (argv[i][0] == '-' || argv[i][0] == '+'))
		{
			v = argv[i][0] == '-';
			if (strchr(PPOPTS, argv[i][1]))
			{
				if (ppargc >= NPPARGS)
					error(1, "too many preprocessor options: `%s' ignored", argv[i]);
				else ppargv[ppargc++] = argv[i];
			}
			else for (j = 1; c = argv[i][j++];)
			{
				for (n = 0; isdigit(argv[i][j]); j++)
					n = n * 10 + argv[i][j] - '0';
				setopt(c, v, n);
				if (c == 'f') flag = ARG_FILE;
				else if (c == 'g') flag = ARG_GLOBAL;
			}
			if (argf) argf[i] |= flag;
		}
	}
}

/*
 * set a single char option
 */

setopt(c, v, n)
int	c, v, n;
{
	char	*s;
	int	number;

	if (state.readonly) ctype[c] |= C_READONLY;
	else if (ctype[c] & C_READONLY) return;
	number = 0;
	switch (c)
	{
	case 'b':	/* don't read builtin rules */
		state.builtin = !v;
		break;
	case 'c':	/* only compile (force) input makefiles */
		state.compileonly = v;
		break;
	case 'd':	/* debug trace flag */
		if (state.dump = v)
		{
			state.debug = n ? -n : -1;
			number = n;
		}
		else state.debug = 0;
		break;
	case 'f':	/* named makefile; already handled by setopts() */
	case 'g':	/* global makefile; already handled by setopts() */
		return;
	case 'h':	/* don't search for implicit file dependencies */
		state.search = !v;
		break;
	case 'i':	/* ignore errors */
		setopt('k', !v, 0);
		state.ignore = v;
		break;
	case 'j':	/* enable jobs */
		if (state.jobs = v)
		{
			state.maxjobs = n ? n : 3;
			if (state.maxjobs >= MAXJOBS) state.maxjobs = MAXJOBS - 1;
			if (state.maxjobs < 1) state.maxjobs = 1;
			if (state.maxjobs == 1) state.jobs = 0;
			else number = n;
		}
		else state.maxjobs = 1;
		break;
	case 'k':	/* continue with sibling deps on error */
		state.ignore = state.keepgoing = v;
		break;
	case 'l':	/* list all definitions; don't make */
		state.list = v;
		return;
	case 'm':	/* move targets to corresponding source directory */
		state.move = v;
		break;
	case 'n':	/* don't execute any commands */
		state.exec = !v;
		break;
	case 'o':	/* output equivalent omake makefile */
		setopt('n', v, 0);
		setopt('F', v, 0);
		state.oldfile = v;
		break;
	case 'q':	/* check if target(s) are up to date */
		setopt('n', v, 0);
		state.question = v;
		break;
	case 'r':	/* dump rule definitions */
		state.ruledump = v;
		break;
	case 's':	/* run silently */
		state.silent = v;
		break;
	case 't':	/* touch out of date targets */
		state.touch = v;
		break;
	case 'u':	/* don't check for duplicate files */
		state.unique = !v;
		break;
	case 'v':	/* list variable definitions */
		state.vardump = v;
		break;
	case 'x':	/* don't check implicit file dependencies */
		state.implicit = !v;
		break;
	case 'A':	/* accept existing targets */
		setopt('S', v, 0);
		state.accept = v;
		break;
	case 'F':	/* force targets to be updated */
		state.force = v;
		break;
	case 'H':	/* search for implicit file and state var dependencies */
#if FULLSEARCH
		state.fullsearch = v;
		break;
#else
		error(1, "-H option not implemented in this version");
		return;
#endif
	case 'M':	/* act as if no target has been made */
		state.nomade = 1;
		return;
	case 'O':	/* override explicit rules */
		state.override = 1;
		break;
	case 'R':	/* force all makefiles to be read */
		state.forceread = state.reread = v;
		break;
	case 'S':	/* ignore state variable definitions */
		state.readstate = !v;
		break;
	case 'T':	/* enable test code */
		state.test = v;
		break;
	case 'V':	/* list program version */
		fprintf(stderr, "%s\n", version);
		fflush(stderr);
		return;
	case '-':
	case '+':
		return;
	default:
		if (!isalpha(c)) error(1, "unknown option `%c'", c);
		break;
	}
	if (!v)
	{
		ctype[c] &= ~C_FLAG;
		if (s = strchr(flags, c))
		{
			while (isdigit(*(s + 1))) s++;
			while (*s = *(s + 1)) s++;
		}
	}
	else if (!strchr(flags, c))
	{
		ctype[c] |= C_FLAG;
		flags[strlen(flags)] = c;
		if (number) sprintf(&flags[strlen(flags)], "%d", number);
	}
}

/*
 * check rule r for immediate action
 * should only be called if r->immediate==1
 */

void
immediate(r)
register struct ruleinfo	*r;
{
	register struct list		*p;
	register struct ruleinfo	*x;

	if (!strcmp(r->name, special.options->name))
	{
		for (p = r->deps; p; p = p->next)
			setopts(2, (&p->item.rule->name) - 1, (unsigned char*)0);
	}
	else if (!strcmp(r->name, special.touch->name))
	{
		for (p = r->deps; p; p = p->next)
		{
			x = p->item.rule;
			message(-1, "touch(%s)", x->name);
			x->bound = 1;
			x->status = EXISTS;
			x->time = CURTIME;
		}
		r->deps = (struct list*)0;
	}
	else if (!strcmp(r->name, special.untouch->name))
	{
		for (p = r->deps; p; p = p->next)
		{
			x = p->item.rule;
			message(-1, "untouch(%s)", x->name);
			x->bound = 0;
			x->member = 0;
			x->status = NOTYET;
			x->time = NOTIME;
		}
		r->deps = (struct list*)0;
	}
#if DEBUG
	else error(INTERNAL, "invalid immediate rule `%s'", r->name);
#endif
}

/*
 * get a rule and expand dynamic dependencies
 */

static struct ruleinfo*
getdyn(name)
char	*name;
{
	register struct ruleinfo	*r;

	if ((r = getrule(name)) && r->dynamic) dynamic(r);
	return(r);
}

/*
 * make a special attribute rule pointer
 */

static struct ruleinfo*
rspecial(s, attribute, immediate)
char	*s;
int	attribute;
int	immediate;
{
	struct ruleinfo	*r;

	r = makerule(s);
	r->attribute = attribute;
	r->compiled = 1;
	r->immediate = immediate;
	return(r);
}

/*
 * make a special variable pointer before readenv()
 */

static char*
vspecial(s, v)
char	*s, *v;
{
	char	*t;

	extern char	*getenv();

	if (t = getenv(s)) v = t;
	(void)setvar(s, v);
	return(v);
}

/*
 * initialize some internal and attribute rule pointers
 */

void
initrules()
{
	rultab->flags &= ~HASH_ALLOCATE;
	special.archive = rspecial(".ARCHIVE", 1, 0);
	special.attribute = rspecial(".ATTRIBUTE", 1, 0);
	special.clear = rspecial(".CLEAR", 1, 0);
	special.current = rspecial(".CURRENT", 1, 0);
	special.dontcare = rspecial(".DONTCARE", 1, 0);
	special.foreground = rspecial(".FOREGROUND", 1, 0);
	special.implicit = rspecial(".IMPLICIT", 1, 0);
	special.insert = rspecial(".INSERT", 1, 0);
	if (!special.internal)
		rmrule(special.target = special.internal = rspecial(".INTERNAL", 0, 0));
	special.main = rspecial(".MAIN", 0, 0);
	special.make = rspecial(".MAKE", 1, 0);
	special.notouch = rspecial(".NOTOUCH", 1, 0);
	special.null = rspecial(".NULL", 1, 0);
	special.operator = rspecial(".OPERATOR", 1, 0);
	special.options = rspecial(".OPTIONS", 0, 1);
	special.post = rspecial(".PARAMETER", 1, 0);
	special.post = rspecial(".POST", 1, 0);
	special.prefixes = rspecial(".PREFIXES", 0, 0);
	special.search = rspecial(".SEARCH", 1, 0);
	special.suffixes = rspecial(".SUFFIXES", 0, 0);
	special.touch = rspecial(".TOUCH", 0, 1);
	special.untouch = rspecial(".UNTOUCH", 0, 1);
	special.use = rspecial(".USE", 1, 0);
	(void)putrule(".WAIT", special.foreground);
	rultab->flags |= HASH_ALLOCATE;

	/*
	 * initialize the inherited attributes
	 */

	special.archive->archive = 1;
	special.current->current = 1;
	special.search->search = 1;
	if (!special.attribute->uattributes) special.attribute->uattributes = 1;
}

/*
 * scan the rules for inherited attribute suffixes
 */

/*ARGSUSED*/
static int
inherit(s, r)
char				*s;
register struct ruleinfo	*r;
{
	register struct list	*p;

	if (r->attribute)
	{
		if (r->uattributes && !r->link && r != special.attribute)
		{
			r->link = special.attribute->link;
			special.attribute->link = r;
		}
		if (r->dynamic) dynamic(r);
		for (p = r->deps; p; p = p->next)
		{
			if (r->archive) p->item.rule->archive = 1;
			if (r->current) p->item.rule->current = 1;
			if (r->search) p->item.rule->search = 1;
			if (r->uattributes) p->item.rule->uattributes |= r->uattributes;
		}
	}
	return(0);
}
