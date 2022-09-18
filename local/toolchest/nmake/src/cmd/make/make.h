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
 * make common definitions
 */

#include "configure.h"

#include <generic.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <directory.h>
#include <hash.h>

#if DEBUG && !lint
#define	INTERNAL	__FILE__,__LINE__
#else
#define	INTERNAL	3
#endif

#ifndef DMAKEPP
#define DMAKEPP		"/lib/cpp"		/* preprocessor name	*/
#endif
#ifndef DMAKERULES
#define DMAKERULES	"/usr/lib/Makerules.mo"	/* builtin rules name	*/
#endif
#ifndef DMAKESHELL
#define DMAKESHELL	"/bin/sh"		/* shell name		*/
#endif

#define MAKEOBJECT	".mo"		/* make object suffix		*/
#define MAKESOURCE	".mk"		/* make source suffix		*/
#define MAKESTATE	".ms"		/* make state suffix		*/

#define ARUPDATE	"\n$(RANLIB) $(<)" /* archive update command	*/

#define COMMENT		'#'		/* make comment char		*/
#define SALT		'#'		/* preprocessor control char	*/

#define MAKEMAGIC	0177535		/* make object magic number	*/
#define UTOOMANY	03		/* bad .ATTRIBUTE->uattributes	*/

#define clearstate(x)	{register char *p;for(p=(char*)&x;p<((char*)&x+sizeof(x));*p++=0);}
#define getrule(name)	(struct ruleinfo*)gethash(rultab,(name))
#define getvar(name)	(struct varinfo*)gethash(vartab,(name))
#define message		if(state.dump)error
#define putrule(name,r)	puthash(rultab,(name),(GENERIC)(r))
#define putvar(name,v)	puthash(vartab,(name),(GENERIC)(v))
#define rmrule(r)	putrule((r)->name,0)

#define ALLOCATE(x)	(x*)calloc(1,sizeof(x))
#define COPY(x)		strcpy(malloc((unsigned)(strlen(x)+1)),x)

#define NOTYET		0	/* don't know what to do yet		*/
#define UPDATE		1	/* rule in process of being updated	*/
#define MAKING		2	/* executing update commands		*/
#define EXISTS		3	/* rule already exists in desired state	*/
#define FAILED		4	/* rule make failed			*/

#define CURRENT		01	/* target placed in current directory	*/
#define POST		02	/* queue up post commands		*/
#define SUFFIX		04	/* executing suffix update commands	*/

#define ARG_FILE	01	/* arg had -f option			*/
#define ARG_GLOBAL	02	/* arg had -g option			*/
#define ARG_USED	04	/* arg has been used			*/

#define DELETE	(char*)0	/* delete path component in edit()	*/
#define KEEP	(char*)1	/* keep path component in edit()	*/

#define NOTIME	(time_t)(-1)	/* not checked time			*/
#define DEFTIME	(time_t)(0)	/* default (unset) time			*/
#define OLDTIME	(time_t)(1)	/* oldest valid time			*/
#define CURTIME	time((time_t*)0)/* current time				*/

#define MAXCMD		5120	/* maximum shell command list length	*/
#define MAXFIX		20	/* maximum file prefix|suffix length	*/
#define MAXJOBS		10	/* maximum number concurrent jobs + 1	*/
#define MAXNAME		1024	/* maximum file pathname length		*/

#define C_COLEQU	(1<<0)	/* ctype[] for { : = }			*/
#define C_FLAG		(1<<1)	/* ctype[] for set flags		*/
#define C_OP1		(1<<2)	/* ctype[] for first op char		*/
#define C_OP2		(1<<3)	/* ctype[] for second op char		*/
#define C_READONLY	(1<<4)	/* ctype[] for readonly option flags	*/
#define C_SHELL		(1<<5)	/* ctype[] for shell chars to quote	*/
#define C_SPACE		(1<<6)	/* ctype[] for { ' ' \t \v }		*/
#define C_SYMBOL	(1<<7)	/* ctype[] for { ( ) = : | }		*/
#define C_TERMINAL	(1<<8)	/* ctype[] for terminal characters	*/
#define C_VARIABLE	(1<<9)	/* ctype[] for variable name characters	*/

struct dirinfo				/* individual directory info	*/
{
	char		*name;		/* directory name		*/
	dev_t		dev;		/* device number for unique()	*/
	ino_t		ino;		/* inode number for unique()	*/
	unsigned int	archive:1;	/* directory is an archive	*/
	unsigned int	directory:1;	/* directory is a real directory*/
};

struct fileinfo				/* file info			*/
{
	char		*name;		/* name sans directory		*/
	struct dirinfo	*dir;		/* directory containing file	*/
	time_t		time;		/* modify time			*/
};

struct jobinfo				/* job info			*/
{
	struct ruleinfo	*target;	/* target for job		*/
	int		errors;		/* error count for job		*/
	int		pid;		/* pid for job			*/
};

/*
 * unbound rule name access -- shared in r->data
 */

#define uname		data
#define unbound(r)	((r)->uname?(r)->uname:(r)->name)

struct ruleinfo				/* rule info			*/
{
	char		*name;		/* rule name			*/
	struct ruleinfo	*link;		/* backward|forward link	*/
	char		*data;		/* unbound name or state value	*/
	struct list	*deps;		/* dependencies			*/
	char		*precmds;	/* pre-commands			*/
	char		*poscmds;	/* post-commands		*/
	time_t		time;		/* modify time			*/
	unsigned long	uattributes;	/* user attributes		*/
	unsigned int	archive:1;	/* rule bound to archive file	*/
	unsigned int	attribute:1;	/* rule is a special attribute	*/
	unsigned int	bound:1;	/* rule has been bound		*/
	unsigned int	cmdspecial:1;	/* pre|post cmds not strings	*/
	unsigned int	compiled:1;	/* rule has been compiled	*/
	unsigned int	current:1;	/* target(suffix) produced in .	*/
	unsigned int	dontcare:1;	/* don't care if rule made	*/
	unsigned int	dynamic:1;	/* must do dynamic expansion	*/
	unsigned int	foreground:1;	/* run precmds in foreground	*/
	unsigned int	fullsearch:1;	/* deps generated by fullsearch	*/
	unsigned int	immediate:1;	/* rule needs immediate action	*/
	unsigned int	implicit:1;	/* force implicit dep checks	*/
	unsigned int	make:1;		/* make (not sh) precmds	*/
	unsigned int	mark:1;		/* temporary mark		*/
	unsigned int	member:1;	/* rule bound to archive member	*/
	unsigned int	notouch:1;	/* don't touch after precmds	*/
	unsigned int	null:1;		/* allow null suffix rule	*/
	unsigned int	operator:1;	/* rule is an operator		*/
	unsigned int	parameter:1;	/* rule bound to parameter file	*/
	unsigned int	posalways:1;	/* always do poscmds		*/
	unsigned int	post:1;		/* make after parent target	*/
	unsigned int	prealways:1;	/* always do precmds		*/
	unsigned int	search:1;	/* file(suffix) can be searched	*/
	unsigned int	searched:1;	/* bound file has been searched	*/
	unsigned int	status:3;	/* disposition of rule		*/
	unsigned int	state:1;	/* rule bound to state variable	*/
	unsigned int	statedeps:1;	/* rule has state variable deps	*/
	unsigned int	target:1;	/* rule is an explicit target	*/
	unsigned int	touch:1;	/* bound file to be touched	*/
	unsigned int	use:1;		/* rule is a .USE script	*/
};

struct specinfo				/* special rule and list info	*/
{
	struct ruleinfo	*archive;	/* .ARCHIVE rule pointer	*/
	struct ruleinfo	*attribute;	/* .ATTRIBUTE rule pointer	*/
	struct ruleinfo	*clear;		/* .CLEAR rule pointer		*/
	struct ruleinfo	*current;	/* .CURRENT rule pointer	*/
	struct ruleinfo	*dontcare;	/* .DONTCARE rule pointer	*/
	struct ruleinfo	*foreground;	/* .FOREGROUND rule pointer	*/
	struct ruleinfo	*implicit;	/* .IMPLICIT rule pointer	*/
	struct ruleinfo	*insert;	/* .INSERT rule pointer		*/
	struct ruleinfo	*internal;	/* .INTERNAL rule pointer	*/
	struct ruleinfo	*main;		/* .MAIN rule pointer		*/
	struct ruleinfo	*make;		/* .MAKE rule pointer		*/
	struct ruleinfo	*makefile;	/* first makefile rule pointer	*/
	struct ruleinfo	*notouch;	/* .NOTOUCH rule pointer	*/
	struct ruleinfo	*null;		/* .NULL rule pointer		*/
	struct ruleinfo	*operator;	/* .OPERATOR rule pointer	*/
	struct ruleinfo	*options;	/* .OPTIONS rule pointer	*/
	struct ruleinfo	*parameter;	/* .PARAMETER rule pointer	*/
	struct ruleinfo	*post;		/* .POST rule pointer		*/
	struct ruleinfo	*prefixes;	/* .PREFIXES rule pointer	*/
	struct ruleinfo	*search;	/* .SEARCH rule pointer		*/
	struct ruleinfo	*suffixes;	/* .SUFFIXES rule pointer	*/
	struct ruleinfo	*target;	/* current target rule		*/
	struct ruleinfo	*touch;		/* .TOUCH rule pointer		*/
	struct ruleinfo	*untouch;	/* .UNTOUCH rule pointer	*/
	struct ruleinfo	*use;		/* .USE rule pointer		*/

	struct list	*explicit;	/* target explicit dependencies	*/

	struct varinfo	*arupdate;	/* ARUPDATE variable pointer	*/

	char		*command;	/* command name (from argv[0])	*/
	char		*pp;		/* MAKEPP value			*/
	char		*rules;		/* MAKERULES value		*/
};

struct stateinfo			/* program state info		*/
{
	unsigned char	accept;		/* accept all existing targets	*/
	unsigned char	autocompile;	/* implicitly compile new rules	*/
	unsigned char	builtin;	/* use builtin rules		*/
	unsigned char	checkstate;	/* only check for state vars	*/
	unsigned char	child;		/* currently in child process	*/
	unsigned char	cleanup;	/* in cleanup phase		*/
	unsigned char	compile;	/* compile input makefiles	*/
	unsigned char	compileonly;	/* only compile (force)		*/
	unsigned char	compilestate;	/* compile state variables only	*/
	unsigned char	dump;		/* dump rule and make info	*/
	unsigned char	exec;		/* execute rule commands	*/
	unsigned char	firstfile;	/* first file not read yet	*/
	unsigned char	force;		/* force target updates		*/
	unsigned char	forceread;	/* force makefiles to be read	*/
	unsigned char	foreground;	/* run commands in foreground	*/
	unsigned char	fullsearch;	/* search file and state deps	*/
	unsigned char	ignore;		/* ignore command errors	*/
	unsigned char	implicit;	/* check implicit file deps	*/
	unsigned char	import;		/* vars imported from environ	*/
	unsigned char	interrupt;	/* processing an interrupt	*/
	unsigned char	jobs;		/* run commands in background	*/
	unsigned char	keepgoing;	/* continue with sibling deps	*/
	unsigned char	list;		/* list readable definitions	*/
	unsigned char	made;		/* at least one target made	*/
	unsigned char	mainload;	/* main object file was loaded	*/
	unsigned char	move;		/* move targets to primary dir	*/
	unsigned char	nomade;		/* act as if no targets made	*/
	unsigned char	oldfile;	/* output omake makefile	*/
	unsigned char	question;	/* check if target up to date	*/
	unsigned char	override;	/* override explicit rules	*/
	unsigned char	reading;	/* currently reading makefile	*/
	unsigned char	readonly;	/* current vars|opts readonly	*/
	unsigned char	readstate;	/* read state variable defs	*/
	unsigned char	reread;		/* re-reading input makefiles	*/
	unsigned char	ruledump;	/* dump rule information	*/
	unsigned char	savestate;	/* must save state variables	*/
	unsigned char	search;		/* search for file deps		*/
	unsigned char	silent;		/* run silently			*/
	unsigned char	test;		/* enable test code		*/
	unsigned char	touch;		/* touch out of date targets	*/
	unsigned char	unique;		/* check for duplicates		*/
	unsigned char	vardump;	/* dump variable information	*/
	unsigned char	work;		/* some target has been made	*/

	int		debug;		/* debug level			*/
	int		level;		/* recursion level		*/
	int		maxjobs;	/* max number concurrent jobs	*/

	time_t		ptime;		/* time of previous makefile	*/
	time_t		start;		/* start time of this make	*/

	struct list	*dependencies;	/* makefile dependencies	*/

	char		*objectfile;	/* make object file name	*/
	char		*statefile;	/* state variable file name	*/
};

struct varinfo				/* var = value info		*/
{
	char		*name;		/* name				*/
	char		*value;		/* value			*/
	unsigned int	compiled:1;	/* variable has been compiled	*/
	unsigned int	frozen:1;	/* frozen in make object file	*/
	unsigned int	import:1;	/* imported from environ	*/
	unsigned int	oldvalue:1;	/* compile old value		*/
	unsigned int	readonly:1;	/* only dynamic modifications	*/
	unsigned int	length:16;	/* maximum length of value	*/
};

union info				/* access to some info structs	*/
{
	struct dirinfo		*dir;
	struct fileinfo		*file;
	struct jobinfo		*job;
	struct ruleinfo		*rule;
	struct varinfo		*var;
	struct list		*list;
	char			*string;
};

struct list				/* general list			*/
{
	struct list	*next;		/* next in list			*/
	union info	item;		/* list item			*/
};

#define NIL		((struct list*)0)

extern struct specinfo	special;	/* special rule and list info	*/

extern struct stateinfo	state;		/* make state info		*/

extern struct jobinfo	jobs[];		/* update command job table	*/

extern TABLE		oldtab;		/* old var value hash table	*/
extern TABLE		rultab;		/* rule name hash table		*/
extern TABLE		vartab;		/* variable name hash table	*/

extern char	arupdate[];		/* archive update variable name	*/
extern char	flags[];		/* set option flag characters	*/
extern char	null[];			/* null string			*/
extern char	buf0[];			/* work 0 -- watch recursion!	*/
extern char	buf1[];			/* work 1 -- watch recursion!	*/
extern char	buf2[];			/* work 2 -- watch recursion!	*/

extern short	ctype[];		/* internal character types	*/

extern char	*yyfile;		/* input file name		*/
extern char	*oyyfile;		/* 1 level save for yyfile	*/
extern char	*version;		/* version stamp		*/

extern char		**args;		/* global argv			*/
extern unsigned char	*argf;		/* ARG_* flags for args		*/

extern int	yyline;			/* input file line number	*/

extern int	errno;			/* system call error number	*/
extern int	sys_nerr;		/* highest system call error	*/
extern char	*sys_errlist[];		/* system call error text	*/
extern char	**environ;		/* environment pointer		*/

extern FILE	*yyinput;		/* input file pointer		*/

FILE		*cmdopen();

char		*calloc();
char		*edit();
char		*expand();
char		*gettok();
char		*getval();
char		*malloc();
char		*stime();
char		*strcopy();
char		*strcpy();
char		*strncpy();

int		any();
int		complete();
int		cowait();
int		dofix();
int		isspecial();
int		load();
int		readfile();
int		strcmp();
int		strlen();
int		strmatch();
int		strncmp();

long		settok();

struct fileinfo	*addfile();

struct list	*append();
struct list	*cons();
struct list	*copy();
struct list	*finddeps();

struct ruleinfo	*bind();
struct ruleinfo	*bindfile();
struct ruleinfo	*bindstate();
struct ruleinfo	*makerule();

struct varinfo	*setvar();

time_t		time();

void		adddep();
void		addpost();
void		cmdclose();
void		cokill();
void		compile();
void		docmd();
void		dopost();
void		dump();
void		dumpcmd();
void		dynamic();
void		error();
void		free();
void		immediate();
void		init();
void		initrules();
void		make();
void		parse();
void		readcheck();
void		readenv();
void		readstate();
void		savestate();
void		search();
void		touch();
void		touchar();
void		yyerror();
