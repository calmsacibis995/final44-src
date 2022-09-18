/*
 *      Copyright (c) 1984, 1985, 1986 AT&T

 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* @(#)expand.c	1.3 */
/*
 *	UNIX shell
 *
 *	S. R. Bourne
 *	Rewritten by David Korn
 *	AT&T Bell Laboratories
 *
 */

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/dir.h>
#include	"defs.h"
#include	"brkincr.h"
#include	"stak.h"
#include	"sym.h"
#include	"shtype.h"

void	rm_files();
int	expand();

extern	STKPTR locstak(),endstak();
extern	FILE *fdopen();
extern	char *movstr();
extern	char *strrchr();
extern	void trim();


/* globals (file name generation) and alternation
 *
 * "*" in params matches r.e ".*"
 * "?" in params matches r.e. "."
 * "[...]" in params matches character class
 * "[!...] or [^...] "" whose members are complement of "..."
 * "[...a-z...]" in params matches a through z.
 * "...{c,b,a}" expands to "...c ...b ...a" (alternation)
 *
 */

static void	addg();
static int totalcount;
static int hadbrc;
static int brcerr;

expand(as,nomatchflg)
char *as;
{
	totalcount = 0;
	hadbrc = 0;
	brcerr = 0;
	expand1(as,nomatchflg);
	return(totalcount);
}

expand1(as,nomatchflg)
char *as;
{
	register char *cp = as;
	int count;
	int cclass = 0;

	if (brcerr || (!hadbrc && eq(as,"{}")))
		goto nobraces;
	while(*cp) {
		switch (*cp) {
		case ESCAPE:
			cp++;
			break;
		case '[':
			cclass = 1;
			if (*(cp+1)==']')
				cp++;
			break;
		case ']':
			cclass = 0;
			break;
		case '{':
			if (!cclass) {
				hadbrc = 1;
				execbrc(as);
				return;
			}
			break;
		}
		cp++;
	}

nobraces:
	count = expand2(as,0,nomatchflg);
	if (count == 0 && hadbrc) {
		/*
		 * doing alternation, add to arg chain anyway
		 */
		as = cpystak(as);
		trim(as);
		addg("",as,0,0);
		totalcount += 1;
	}
	else {
		totalcount += count;
	}
	if (gchain)
		gchain->argflag |= A_MAKE;
}

/*
 * ...{a,b,c} alternation
 */
execbrc(as)
char *as;
{
	register char *s, c, savec, *rb;
	register char *endbrace, *startelem, *endelem;
	char *restbuf = (char *)locstak();
	int  brclev = 0;

	for (s = as; *s; s++)
		;
	endstak(restbuf + (s-as+1));

	/*
	 * copy up to brace
	 */
	s = as;
	rb = restbuf;
	while(c = *s++) {
		if (c == ESCAPE) {
			*rb++ = ESCAPE;
			c = *s++;
		} else if (c == '{')
			break;
		*rb++ = c;
	}

	/*
	 * locate closing brace.
	 */
	for (endbrace = s; *endbrace; endbrace++)
	switch (*endbrace) {
	case ESCAPE:
		endbrace++;
		continue;
	case '{':
		brclev++;
		continue;
	case '}':
		if (brclev == 0)
			goto pend;
		brclev--;
		continue;
	case '[': {	/* skip chars inside cclass */
		register char *cp = endbrace;
		if (*++cp == ']')	/* [] means include ']' in cclass */
			cp++;
		for (; *cp && *cp != ']'; cp++)
			if (*cp == ESCAPE)
				cp++;
		if (*cp)
			endbrace = cp;
		continue;
	        }
	}
pend:	
	dprint("*endbrace == %c\n", *endbrace);
	if (*endbrace == '\0') {
		dprint("brace error\n");
		/* brace error - give up */
		hadbrc = 0;
		brcerr = 1;
		expand1(as);
	}
	brclev = 0;
	/*
	 * for each element in brace, strap it to
	 * restbuf, append everything after endbrace,
	 * and (recursively) call expand with restbuf.
	 */
	for (startelem = endelem = s; endelem <= endbrace; endelem++)
	switch (*endelem) {
	case ESCAPE:
		endelem++;
		continue;
	case '{':
		brclev++;
		continue;
	case '}':
		if (brclev) {
			brclev--; 
			continue;
		}
		goto doit;	
	case ',':
		if (brclev)
			continue;
doit:
		savec = *endelem;
		*endelem = '\0';
		strcpy(rb,startelem);
		strcat(rb,endbrace+1);
		*endelem = savec;
		expand1(restbuf, 0);
		startelem = endelem+1;
		continue;
	case '[': {
		register char *cp = endelem;

		if (*++cp == ']')  /* [] means include ']' in cclass */
			cp++;
		for (; *cp && *cp != ']'; cp++)
			if (*cp == ESCAPE)
				cp++;
		if (*cp)
			endelem = cp;
		continue;
		}
	}
}
	

int expand2(as,rcnt,nomatchflg)
char *as;
{
	int 	count;
#ifdef BSD_4_2
	DIR 	*dirf;
#else
	FILE 	*dirf;
#endif	/* BSD_4_2 */
	BOOL 	nometa=0;
	BOOL 	dir=0;
	char *rescan = 0;
	char *slashsav = 0;
	register char *s, *cs;
	int quote = 0;
	int slash;
	int add_slash = 1;	/* insert a separator slash */
	char *sname;
	ARGPTR 	schain = gchain;
	/* this union forces enough space for the NULL byte */
	union Dirent
	{
		struct direct	entry;
		char entrybuf[sizeof(struct direct)+1]; /* room for null byte */
	};
	union Dirent dirent;
	struct direct	*entry = &dirent.entry;
#ifndef BSD_4_2
	char dirbuff[BUFSIZ];
#endif	/* BSD_4_2 */
	if(trapnote&SIGSET)
		return(0);
	s=cs=as;
#ifndef BSD_4_2
	entry->d_name[DIRSIZ]=0; /* to end the string */
#endif	/* BSD_4_2 */
	/* check for meta chars */
	{
		register int open = 0;
		slash=0;
		do
		{
			switch(*cs++)
			{
				case 0:
				{
					nometa = '/';
					if (rcnt && slash)
						break;
					else
						return(0);
				}

				case '/':
					slash++;
					open = 0;
					continue;

				case '[':
					open++;
					continue;

				case ']':
					if(open)
						break;
					continue;

				case '?':
				case '*':
					if(rcnt > slash)
						continue;
					cs--;
					break;

				case ESCAPE:
					quote++;
					cs++;
				default:
					continue;
			}
			break;
		}
		while(1);
	}
	while(1)
	{
		if(cs==s)
		{
			s=nullstr;
			break;
		}
		else if(*--cs == '/')
		{
			*cs=nometa;
			if(s==cs)
			{
				s= "/";
				add_slash = 0;
			}
			break;
		}
	}
	if(quote && s!=cs)
	{
		s = cpystak(s);
		trim(s);
	}
	/* special case where there are no meta-chars left in path */
	if(nometa)
	{
		/* read permission on directories not needed */
		if(access(s,0)==0)
		{
			addg(s,nullstr,NIL,0);
			return(1);
		}
		return(0);
	}
	sname = (*s?s:dot);
	if(ftype(sname,S_IFMT,S_IFDIR)
#ifdef BSD_4_2
		   && (dirf=opendir(sname))!=NULL)
#else
		   && (dirf=fdopen(open(sname,0),"r"))!=NULL)
#endif	/* BSD_4_2 */
	{
		dir++;
#ifndef BSD_4_2
		setbuf(dirf,dirbuff);
#endif
	}
	count=0;
	if(*cs==0)
		slashsav = cs++;
	if(dir)
		/* check for rescan */
	{
		register char *rs = cs;
		do
		{
			if(*rs=='/')
			{
				rescan=rs;
				*rs=0;
				gchain=0;
			}
		}
		while(*rs++);
#ifdef BSD_4_2
		while((entry=readdir(dirf)) && (trapnote&SIGSET)==0)
#else
		while(fread((char*)entry,sizeof(struct direct),1,dirf)==1 && (trapnote&SIGSET)==0)
#endif	/* BSD_4_2 */
		{
			if(entry->d_ino==0 || (*entry->d_name=='.' && *cs!='.'))
				continue;

			if(gmatch(entry->d_name, cs))
			{
				addg(s,entry->d_name,rescan,add_slash);
				count++;
			}
		}
#ifdef BSD_4_2
		closedir(dirf);
#else
		closefd(dirf);
#endif	/* BSD_4_2 */
		if(rescan)
		{
			register ARGPTR	rchain;
			rchain=gchain; gchain=schain;
			if(count)
			{
				count=0;
				while(rchain)
				{
					count += expand2(rchain->argval,slash+1);
					rchain=rchain->argchn;
				}
			}
			*rescan='/';
		}
	}
	if(slashsav)
		*slashsav = '/';
	return(count);
}

static  void addg(as1,as2,as3,add_slash)
char *as1, *as2, *as3;
int add_slash;
{
	register char *s1, *s2;
	register int 	c;
	register ARGPTR argp = (ARGPTR)locstak();
	argp->argflag &= ~(A_MAKE|A_RAW);
	s2 = argp->argval;
	s1=as1;
	/* directory */
	while(c = *s1)
	{
		s1++;
		if(c == ESCAPE)
			*s2++ = ESCAPE;
		*s2++ = c;
	}
	if(add_slash && s1 > as1 && *as2)
		*s2++='/';
	s1=as2;
	/* component */
	while(c = *s1++)
	{
		/* escape the ESCAPE characters */
		if(c == ESCAPE)
			*s2++ = ESCAPE;
		*s2++ = c;
	}
	/* rescan */
	if(s1=as3)
	{
		*s2++='/';
		while(*s2++ = *++s1);
	}
	if(is_option(MARKDIR))
	{
		*s2 = 0;
		if(ftype(argp->argval,S_IFMT,S_IFDIR))
			*s2++ = '/';
	}
	endstak(s2);
	argp->argchn= gchain;
	gchain = argp;
}


/*
 * remove tmp files
 * template of the form /tmp/sh$$.???
 */

void	rm_files(template)
register char *template;
{
	register char *cp;
	ARGPTR schain;
	cp = strrchr(template,'.');
	*(cp+1) = 0;
	f_complete(template,"*");
	schain = gchain;
	while(schain)
	{
		unlink(schain->argval);
		schain = schain->argchn;
	}
}

/*
 * file name completion
 * generate the list of files found by adding an suffix to end of name
 * The number of matches is returned
 */

f_complete(name,suffix)
char *name;
register char *suffix;
{
	register char *cp;
	register char *dp;
	gchain =  NULL;
	dp = (char*)locstak();
	cp = movstr(name,dp);
	if(suffix)
		cp =  movstr(suffix,cp);
	endstak(cp);
	return(expand(dp,0));
}

int debug = 0;
#include "io.h"
dprint(fmt,a1,a2,a3,a4,a5,a6,a7)
char *fmt;
{
	char temp[1024];
	if (!debug)
		return;
	sprintf(temp,fmt,a1,a2,a3,a4,a5,a6,a7);
	fputs(temp,output);
	fflush(output);
}
#ifdef notdef
#endif
