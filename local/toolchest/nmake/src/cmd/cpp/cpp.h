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
 * C preprocessor definitions and global references
 *
 * AT&T Bell Laboratories
 */

#include "configure.h"

#if !NOMACHDEP
#include "machdep.h"
#endif

#include <stdio.h>
#include <ctype.h>
#include <hash.h>
#include <generic.h>

/*
 * the MAX* symbols define the only static limitations
 */

#define MAXSYMNMLEN	255	/* maximum symbol name length		*/
#define MAXPATH		1024	/* maximum file path length		*/
#define MAXFRM		31	/* maximum macro formals/actuals	*/
#define MAXIF		128	/* maximum #if nesting			*/

#define SYMNMLEN	8	/* truncated symbol name length		*/

#if FLEXNAMES
#define MAXSYM		MAXSYMNMLEN
#else
#define MAXSYM		SYMNMLEN
#endif

#ifndef CPPINCLUDE
#define CPPINCLUDE	"/usr/include"
#endif

#ifndef CPPDEFAULT
#define CPPDEFAULT	"default.h"
#endif

#define DEFAULT		(GENERIC)0
#define NOTFOUND	(GENERIC)1

#define CLASSCODE	27	/* exit status if #pragma class seen	*/

#define SALT	'#'

extern char	*pbeg, *pbuf, *pend;
extern char	*outp, *inp;
extern char	*newp;

#if CROSSREF
#define crossinfo(type,name,line) if(xready)fprintf(xout,"%s%*.s\t%05d\n",type,maxsym,name,line)
#define crossfile(name)		fprintf(xout,"\"%s\"\n",name)
#define crossline(line)		xline=line
#define crossready(val)		xready=val

extern char	*xcopy();
extern int	xline;
extern int	xready;
extern FILE	*xout;
#else
#define crossinfo(type,name,line)
#define crossfile(name)
#define crossline(line)
#define crossready()
#endif

#if DEBUG
extern int	debug;
#endif

#if SCAN
extern int	scan;
#endif

#define BLANK	001
#define DELIM	002
#define IDENT	004
#define NUMBR	010

#define IB	001
#define SB	002
#define NB	004
#define CB	010
#define QB	020
#define WB	040

extern char	fastab[];
extern char	slotab[];
extern char	toktyp[];
extern char	*ptrtab;

#define isslo		(ptrtab == (slotab + COFF))
#define isid(a)		((fastab + COFF)[a] & IB)
#define isspc(a)	(ptrtab[a] & SB)
#define isnum(a)	((fastab + COFF)[a] & NB)
#define iscom(a)	((fastab + COFF)[a] & CB)
#define isquo(a)	((fastab + COFF)[a] & QB)
#define iswarn(a)	((fastab + COFF)[a] & WB)

#define isblank(a)	((toktyp + COFF)[a] == BLANK)
#define isdelim(a)	((toktyp + COFF)[a] == DELIM)
#define isident(a)	((toktyp + COFF)[a] == IDENT)
#define isnumbr(a)	((toktyp + COFF)[a] == NUMBR)

#define eob(a)		((a) >= pend)
#define bob(a)		(pbeg >= (a))

extern char	buffer[];
extern char	tmp[];

#define DEFINED	001	/* check if symbol defined -- used by #if	*/
#define ENTER	002	/* enter new symbol definition			*/
#define FIND	004	/* find symbol definition			*/
#define REMOVE	010	/* remove symbol definition			*/
#define SPECIAL	020	/* enter a special symbol			*/

#define DISABLE	(ALFSIZ>>1)	/* macro temporarily disabled		*/
#define FORMALS	((ALFSIZ>>2)-1)	/* number of macro formals		*/
#define PREDEF	(ALFSIZ>>2)	/* macro predefined			*/

#define WARN	'\376'	/* special character not legal ASCII or EBCDIC	*/

#define KEPT	01	/* a part of this if was true			*/
#define SKIP	02	/* skip this part of if				*/
#define ELSE	04	/* already had else part of if			*/

extern int	iflev;
extern char	ifstack[];
extern int	skip;

extern int	pflag;
extern int	ignoresrc;
extern int	maxsym;
extern int	errors;
extern int	init;

extern char	*copy(), *subst(), *trmdir();
extern BUCKET	stsym(), lookup(), slookup();

#if DEFAULT_INCLUDE
#include <setjmp.h>
extern jmp_buf	initenv;
#endif

extern TABLE	symtab;

extern char	*getenv(), *skipbl(), *cotoken(), *eatline();
extern char	*strcpy(), *strcat();
extern char	*malloc(), *realloc();
extern void	free();
extern int	eval();
