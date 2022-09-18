/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*	@(#)main.c	1.2	*/

# include "defs.h"
#if MKCV && !lint /* MKCV */
static char	stamp[] = "@(#)mkcv1 (AT&T Bell Laboratories) 08/30/85a";
#endif /* MKCV */
/*
command make to update programs.
Flags:	'd'  print out debugging comments
	'p'  print out a version of the input graph
	's'  silent mode--don't print out commands
	'f'  the next argument is the name of the description file;
	     makefile is the default
	'i'  ignore error codes from the shell
	'S'  stop after any command fails (normally do parallel work)
	'n'   don't issue, just print, commands
	't'   touch (update time of) files but don't issue command
	'q'   don't do anything, but check if object is up to date;
	      returns exit code 0 if up to date, -1 if not
*/

char makefile[] = "makefile";
char Nullstr[] = "";
char Makefile[] =	"Makefile";
char RELEASE[] = "RELEASE";
/* MKCV */

NAMEBLOCK mainname ;
NAMEBLOCK firstname;
LINEBLOCK sufflist;
VARBLOCK firstvar;
PATTERN firstpat ;
OPENDIR firstod;


#include <signal.h>
VOID (*sigivalue)() = SIG_DFL; /* MKCV */
VOID (*sigqvalue)() = SIG_DFL; /* MKCV */
int waitpid=0;

#if MKCV /* MKCV */
struct vartrans			/* variable translation		*/
{
	char	*old;		/* old name			*/
	char	*new;		/* new name			*/
	char	*dval;		/* default value		*/
	char	*nval;		/* new value			*/
};

struct vartrans vars[] =
{
	"AS",		"AS",		"as",		"$$(AS)",
	"ASFLAGS",	"ASFLAGS",	"",		"$$(ASFLAGS)",
	"CC",		"CC",		"cc",		"$$(CC)",
	"CFLAGS",	"CCFLAGS",	"-O",		"$$(CCFLAGS)",
	"GET",		"GET",		"get",		"$$(GET)",
	"GFLAGS",	"GETFLAGS",	"",		"$$(GETFLAGS)",
	"LD",		"LD",		"ld",		"$$(LD)",
	"LDFLAGS",	"LDFLAGS",	"",		"$$(LDFLAGS)",
	"LEX",		"LEX",		"lex",		"$$(LEX)",
	"LFLAGS",	"LEXFLAGS",	"",		"$$(LEXFLAGS)",
	"MAKE",		"MAKE",		"make",		"$$(MAKE)",
	"MAKEFLAGS",	(char*)0,	"",		"$$(-)",
	"MFLAGS",	(char*)0,	"",		"$$(-)",
	"YACC",		"YACC",		"yacc",		"$$(YACC)",
	"YFLAGS",	"YACCFLAGS",	"-d",		"$$(YACCFLAGS)",
	(char*)0,	(char*)0,	(char*)0,	(char*)0
};

int Mflags=MH_DEP|NOEX;
CHARSTAR prompt="exec ";

#else /* MKCV */

int Mflags=MH_DEP;
CHARSTAR prompt="\t";	/* other systems -- pick what you want */

#endif /* MKCV */

int ndocoms=0;
int okdel=YES;

char junkname[20];
char funny[128];




char Makeflags[]="MAKEFLAGS";

main(argc,argv)
int argc;
CHARSTAR argv[];
{
	register NAMEBLOCK p;
	int i; /* MKCV */
	int descset, nfargs;
	TIMETYPE tjunk;
	/* MKCV */
	CHARSTAR s; /* MKCV */
#ifdef unix
	int intrupt();



#endif

#ifdef METERFILE
	meter(METERFILE);
#endif

	descset = 0;

	for(s = "#|=^();&<>*?[]:$`'\"\\\n" ; *s ; ++s)
		funny[*s] |= META;
	for(s = "\n\t :=;{}&>|" ; *s ; ++s)
		funny[*s] |= TERMINAL;
	funny['\0'] |= TERMINAL;

	TURNON(INTRULE);		/* Default internal rules, turned on */

/*
 *	Set command line flags
 */

	getmflgs();				/* Init $(MAKEFLAGS) variable */
	setflags(argc, argv);

	setvar("$","$");


/*
 *	Read command line "=" type args and make them readonly.
 */
	TURNON(INARGS|EXPORT);
	if(IS_ON(DBUG))printf("Reading \"=\" type args on command line.\n");
	for(i=1; i<argc; ++i)
		if(argv[i]!=0 && argv[i][0]!=MINUS && (eqsign(argv[i]) == YES) )
			argv[i] = 0;
	TURNOFF(INARGS|EXPORT);

/*
 *	Read internal definitions and rules.
 */

	if( IS_ON(INTRULE) )
	{
		if(IS_ON(DBUG))printf("Reading internal rules.\n");
		rdd1((FILE*)0); /* MKCV */
	}

/*
 *	Done with internal rules, now.
 */
	TURNOFF(INTRULE);

/*
 *	Read environment args.  Let file args which follow override.
 *	unless 'e' in MAKEFLAGS variable is set.
 */
	if( any( (varptr(Makeflags))->varval, 'e') )
		TURNON(ENVOVER);
	if(IS_ON(DBUG))printf("Reading environment.\n");
	TURNON(EXPORT);
	readenv();
	TURNOFF(EXPORT|ENVOVER);

/*
 *	Read command line "-f" arguments.
 */

	rdmakecomm();

	for(i = 1; i < argc; i++)
		if( argv[i] && argv[i][0] == MINUS && argv[i][1] == 'f' && argv[i][2] == CNULL)
		{
			argv[i] = 0;
			if(i >= argc-1)
				fatal("No description argument after -f flag");
			if( rddescf(argv[++i], YES) )
				fatal1("Cannot open %s", argv[i]);
			argv[i] = 0;
			++descset;
		}


/*
 *	If no command line "-f" args then look for some form of "makefile"
 */
	if( !descset )
#ifdef unix
		if( rddescf(makefile, NO))
		if( rddescf(Makefile, NO))
		if( rddescf(makefile, YES))
			rddescf(Makefile, YES);

#endif
#ifdef gcos
		rddescf(makefile, NO);
#endif


	if(IS_ON(PRTR)) printdesc(NO);

	if( srchname(".IGNORE") ) TURNON(IGNERR);
	if( srchname(".SILENT") ) TURNON(SIL);
	if(p=srchname(".SUFFIXES")) sufflist = p->linep;
	if( !sufflist ) fprintf(stderr,"No suffix list.\n");

#ifdef unix
	sigivalue = signal(SIGINT,SIG_IGN); /* MKCV */
	sigqvalue = signal(SIGQUIT,SIG_IGN); /* MKCV */
	enbint(intrupt);
#endif

#if MKCV /* MKCV */
	cvtvar();
	cvtsrcobj();
#endif /* MKCV */

	nfargs = 0;

	for(i=1; i<argc; ++i)
		if((s=argv[i]) != 0)
		{
			if((p=srchname(s)) == 0)
			{
				p = makename(s);
			}
			++nfargs;
			doname(p, 0, &tjunk);
			if(IS_ON(DBUG)) printdesc(YES);
		}

/*
	If no file arguments have been encountered, make the first
	name encountered that doesn't start with a dot
	*/

	if(nfargs == 0)
		if(mainname == 0)
			fatal("No arguments or description file");
		else
		{
			doname(mainname, 0, &tjunk);
			if(IS_ON(DBUG)) printdesc(YES);
		}

	exit(0);
}



#ifdef unix
intrupt()
{
	CHARSTAR p;
	NAMEBLOCK q;

	if(okdel && IS_OFF(NOEX) && IS_OFF(TOUCH) &&
	   (p=varptr("@")->varval) && 
	   (q=srchname(p)) && 
	   (exists(q)>0) &&
	   !isprecious(p) )
	{
		if(isdir(p))
			fprintf(stderr, "\n*** %s NOT REMOVED.",p);
		else if(unlink(p) == 0)
			fprintf(stderr, "\n***  %s removed.", p);
	}
	if(junkname[0])
		unlink(junkname);
	fprintf(stderr, "\n");
	exit(2);
}




isprecious(p)
CHARSTAR p;
{
	register NAMEBLOCK np;
	register LINEBLOCK lp;
	register DEPBLOCK dp;

	if(np = srchname(".PRECIOUS"))
	    for(lp = np->linep ; lp ; lp = lp->nextline)
		for(dp = lp->depp ; dp; dp = dp->nextdep)
			if(equal(p, dp->depname->namep))
				return(YES);

	return(NO);
}


enbint(k)
VOID (*k)(); /* MKCV */
{
	if(sigivalue != SIG_IGN) /* MKCV */
		(void)signal(SIGINT,k); /* MKCV */
	if(sigqvalue != SIG_IGN) /* MKCV */
		(void)signal(SIGQUIT,k); /* MKCV */
}
#endif

extern CHARSTAR builtin[];

CHARSTAR *linesptr=builtin;

FILE * fin;
/* MKCV */

rdmakecomm()
{
#ifdef PWB
	register char *nlog;
	char s[128];
	CHARSTAR concat(), getenv();

	if(rddescf( concat((nlog=getenv("HOME")),"/makecomm",s), NO))
		rddescf( concat(nlog,"/Makecomm",s), NO);

	if(rddescf("makecomm", NO))
		rddescf("Makecomm", NO);
#endif
}

extern int yyline;
extern CHARSTAR zznextc;
rddescf(descfile, flg)
CHARSTAR descfile;
int flg;			/* if YES try s.descfile */
{
	FILE * k;

/* read and parse description */

	if(equal(descfile, "-"))
		return( rdd1(stdin) );

retry:
	if( (k = fopen(descfile,"r")) != NULL)
	{
		if(IS_ON(DBUG))printf("Reading %s\n", descfile);
		return( rdd1(k) );
	}

	if(flg == NO)
		return(1);
	if(get(descfile, CD, varptr(RELEASE)->varval) == NO)
		return(1);
	flg = NO;
	goto retry;

}




rdd1(k)
FILE * k;
{
	fin = k;
	yyline = 0;
	zznextc = 0;

	if( yyparse() )
		fatal("Description file error");

	if(fin != NULL)
		fclose(fin);

	return(0);
}

printdesc(prntflag)
int prntflag;
{
	NAMEBLOCK p;
	VARBLOCK vp;
	OPENDIR od;
	/* MKCV */

#ifdef unix
	if(prntflag)
	{
		fprintf(stderr,"Open directories:\n");
		for(od=firstod; od!=0; od = od->nextopendir)
			fprintf(stderr,"\t%ul: %s\n", od->dirfc, od->dirn); /* MKCV */
	}
#endif

	if(firstvar != 0) fprintf(stderr,"Macros:\n");
	for(vp=firstvar; vp!=0; vp=vp->nextvar)
		if(vp->v_aflg == NO)
			printf("%s = %s\n" , vp->varname , vp->varval);
		else
		{
			CHAIN pch;

			fprintf(stderr,"Lookup chain: %s\n\t", vp->varname);
			for(pch = (CHAIN)vp->varval; pch; pch = pch->nextchain)
				fprintf(stderr," %s",
					((NAMEBLOCK)pch->datap)->namep);
			fprintf(stderr,"\n");
		}

	for(p=firstname; p!=0; p = p->nextname)
		prname(p, prntflag);
	printf("\n");
	fflush(stdout);
}

prname(p, prntflag)
register NAMEBLOCK p;
{
	register LINEBLOCK lp;
	register DEPBLOCK dp;
	register SHBLOCK sp;

	if(p->linep != 0)
		printf("\n\n%s:",p->namep);
	else
		fprintf(stderr, "\n\n%s", p->namep);
	if(prntflag)
	{
		fprintf(stderr,"  done=%d",p->done);
	}
	if(p==mainname) fprintf(stderr,"  (MAIN NAME)");
	for(lp = p->linep ; lp!=0 ; lp = lp->nextline)
	{
		if( dp = lp->depp )
		{
			fprintf(stderr,"\n depends on:");
			for(; dp!=0 ; dp = dp->nextdep)
				if(dp->depname != 0)
				{
					printf(" %s", dp->depname->namep);
					printf(" ");
				}
		}
		if(sp = lp->shp)
		{
			printf("\n");
			fprintf(stderr," commands:\n");
			for( ; sp!=0 ; sp = sp->nextsh)
				printf("\t%s\n", sp->shbp);
		}
	}
}


setflags(ac, av)
int ac;
CHARSTAR *av;
{
	register int i, j;
	register char c;
	int flflg=0;			/* flag to note `-f' option. */

	for(i=1; i<ac; ++i)
	{
		if(flflg)
		{
			flflg = 0;
			continue;
		}
		if(av[i]!=0 && av[i][0]==MINUS)
		{
			if(any(av[i], 'f'))
				flflg++;
			for(j=1 ; (c=av[i][j])!=CNULL ; ++j)
				optswitch(c);
			if(flflg)
				av[i] = "-f";
			else
				av[i] = 0;
		}
	}
}


/*
 *	Handle a single char option.
 */
optswitch(c)
register char c;
{

	switch(c)
	{

	case 'e':	/* environment override flag */
		setmflgs(c);
		break;

	case 'd':	/* debug flag */
		TURNON(DBUG);
		setmflgs(c);
		break;

	case 'p':	/* print description */
		TURNON(PRTR);
		break;

	case 's':	/* silent flag */
		TURNON(SIL);
		setmflgs(c);
		break;

	case 'i':	/* ignore errors */
		TURNON(IGNERR);
		setmflgs(c);
		break;

	case 'S':
		TURNOFF(KEEPGO);
		setmflgs(c);
		break;

	case 'k':
		TURNON(KEEPGO);
		setmflgs(c);
		break;

	case 'n':	/* do not exec any commands, just print */
		TURNON(NOEX);
		setmflgs(c);
		break;

	case 'r':	/* turn off internal rules */
		TURNOFF(INTRULE);
		break;

	case 't':	/* touch flag */
		TURNON(TOUCH);
		setmflgs(c);
		break;

	case 'q':	/* question flag */
		TURNON(QUEST);
		setmflgs(c);
		break;

	case 'g':	/* turn default $(GET) of files not found */
		TURNON(GET);
		setmflgs(c);
		break;

	case 'm':	/* print memory map */
		TURNON(MEMMAP);
		setmflgs(c);
		break;

	case 'b':	/* use MH version of test for whether a cmd exists */
		TURNON(MH_DEP);
		setmflgs(c);
		break;
	case 'B':	/* turn off -b flag */
		TURNOFF(MH_DEP);
		setmflgs(c);
		break;

	case 'f':	/* Named makefile; already handled by setflags(). */
		break;

	default:
		fatal1("Unknown flag argument %c", c);
	}
}

/*
 *	getmflgs() set the cmd line flags into an EXPORTED variable
 *	for future invocations of make to read.
 */


getmflgs()
{
	register VARBLOCK vpr;
	register CHARSTAR *pe;
	register CHARSTAR p;

	vpr = varptr(Makeflags);
	setvar(Makeflags, "ZZZZZZZZZZZZZZZZ");
	vpr->varval[0] = CNULL;
	vpr->envflg = YES;
	vpr->noreset = YES;
	optswitch('b');
	for(pe = environ; *pe; pe++)
	{
		if(sindex(*pe, "MAKEFLAGS=") == 0)
		{
			for(p = (*pe)+sizeof Makeflags; *p; p++)
				optswitch(*p);
			return;
		}
	}
}

/*
 *	setmflgs(c) sets up the cmd line input flags for EXPORT.
 */

setmflgs(c)
register char c;
{
	register VARBLOCK vpr;
	register CHARSTAR p;

	vpr = varptr(Makeflags);
	for(p = vpr->varval; *p; p++)
	{
		if(*p == c)
			return;
	}
	*p++ = c;
	*p = CNULL;
}

#if MKCV /* MKCV */
/*
 * convert some variable definitions for the new format
 */

cvtvar()
{
	register struct vartrans	*v;
	register VARBLOCK		vp;
	register char			*s;
	int				dup;

	for (v = vars; v->old; v++)
	{
		vp = srchvar(v->old);
		if (v->new && strcmp(vp->varval, v->dval))
			(void)printf("setv %s = %s\n", v->new, vp->varval);
		(void)setvar(v->old, v->nval);
	}
	for(vp = firstvar; vp; vp = vp->nextvar)
	{
		if (!(dup = !strcmp(vp->varname, "$")))
		{
			for (v = vars; v->old; v++)
			{
				if (!strcmp(vp->varname, v->old) && !strcmp(vp->varval, v->nval))
				{
					dup = 1;
					break;
				}
			}
		}
		if (!dup && vp->v_aflg == NO)
		{
			s = vp->varval;
			while (s = strchr(s, '\n'))
			{
				if (s > vp->varval && *(s - 1) == '\\') *(s - 1) = ' ';
				*s = ' ';
			}
			(void)printf("symb %s %s\n", vp->varname, vp->varval);
		}
	}
}

/*
 * output list of suffixes that can generate .o targets
 */

cvtsrcobj()
{
	register LINEBLOCK	lp;
	register DEPBLOCK	sp;
	register char		*s;
	char			buf[32];

	printf("rule .GENERATE.o\n");
	for (lp = sufflist; lp; lp = lp->nextline)
		for (sp = lp->depp; sp; sp = sp->nextdep)
		{
			s = sp->depname->namep;
			if (s[strlen(s) - 1] != '~')
			{
				sprintf(buf, "%s.o", s);
				if (srchname(buf))
				{
					printf("make %s\n", s);
					printf("done %s\n", s);
				}
			}
		}
	printf("done .GENERATE.o\n");
}
#endif /* MKCV */
