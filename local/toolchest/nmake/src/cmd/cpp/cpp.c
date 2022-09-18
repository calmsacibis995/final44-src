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
 * C preprocessor
 *
 * AT&T Bell Laboratories
 *
 *	John Reiser	1978	basic buffering mechanism
 *	Joe Steffen	1984	comment and predefined symbol warnings
 *	Glenn Fowler	1985	dynamic allocation, restructuring
 */

#include "cpp.h"
#include <errno.h>

static char stamp[] = "@(#)cpp (AT&T Bell Laboratories) 08/30/85a";
static char *version = stamp + 4;

#define allocate(x)	(struct x*)malloc(sizeof(struct x))
#define copy(s)		strcpy(malloc(strlen(s) + 1),s)

#define defput(c)	{if(bob(p)){outp=inp=p;p=unfill(p);}*--p=(c);}
#define defnum(n,t)	{int i;char *z;for(z=((char*)&(n))+sizeof(t),i=sizeof(t);--i>=0;)defput(*--z);}
#define getnum(n,t)	{int i;char *z;for(z=((char*)&(n)),i=sizeof(t);--i>=0;){if(eob(p))p=refill(p);*z++=(*p++);};}

int		maxsym = MAXSYM;	/* default name length		*/

char		*pbeg, *pbuf, *pend;
char		*outp, *inp;
char		*newp;
int		inppsym;

TABLE		symtab;

#if CROSSREF
FILE		*xout;
int		xline;
int		xready = 0;
#endif

static int	text = 1;	/* output expanded text			*/

#if DEBUG
int		debug = 0;	/* debug output level			*/

struct
{
	int	lookups;	/* number of token lookups		*/
	int	found;		/* number of found token lookups	*/
	int	code1;		/* number of code1 wins			*/
} stats;			/* monitoring stats			*/
#endif

int		fin	= 0;	/* current input file descriptor	*/
int		fout	= 1;	/* current output file descriptor	*/

/*
 * a superimposed code is maintained in code1[] to determine if
 * a symbol has not been hashed  -- if the kth character of a
 * symbol is 'a' and there are no key names whose kth character
 * is 'a' then the key need not be hashed and searched for in 
 * the symbol table
 */

#define tstcode1(c,p)	((code1 + COFF)[c]&(1<<(p)))
#define setcode1(c,p)	((code1 + COFF)[c]|=(1<<(p)))

char	code1[ALFSIZ];
char	*ptrtab;

char	buffer[2 * (MAXBUF + MAXSYM)];	/* the big buffer		*/

char	tmp[MAXPATH];		/* used for formatted output		*/
char	path[MAXPATH];		/* path names constructed here		*/

struct bufinfo			/* side buffer stack			*/
{
	struct bufinfo	*next;		/* next in list			*/
	char		buf[MAXBUF];	/* side buffer			*/
	int		size;		/* # of bytes in buf		*/
};

static struct bufinfo	*curbuf;	/* live buffer stack		*/
static struct bufinfo	*frebuf;	/* free buffer list		*/

static struct			/* macro state info			*/
{
	char	*name;		/* name of macro with actuals		*/
	int	line;		/* line number of call with actuals	*/
	int	pcount;		/* parenthesis level in actual scan	*/
	int	level;		/* # calls since decrease in nesting	*/
	char	*decrease;	/* exceed this to decrease nesting	*/
	int	dam;		/* offset due to buffer shifting	*/
} macro;

int		iflev;			/* #if nesting level		*/
char		ifstack[MAXIF];		/* not dynamic!			*/
int		skip;			/* don't expand text		*/
int		inif;			/* processing #if		*/
#if MATCH_EXTRA
BUCKET		ifmatch[MAXIF];		/* token for ifdef or ifndef	*/
#endif

struct dirinfo				/* -I and <> dir list		*/
{
	struct dirinfo	*next;		/* next in list			*/
	char		*name;		/* direcory name		*/
};

static struct dirinfo	firstdir;		/* always have one	*/
static struct dirinfo	*dirs = &firstdir;	/* the dir list		*/
static struct dirinfo	*lastdir = &firstdir;	/* for easy appending	*/

static char	*defdir;	/* default -H dir overriding CPPINCLUDE	*/

struct definfo			/* command line -D and -U args		*/
{
	struct definfo	*next;	/* next in list				*/
	char		*def;	/* definition				*/
};

int	pflag;		/* don't put out lines "# 12 foo.c"		*/
int	ignoresrc;	/* ignore directory of source file for search()	*/
int	errors;		/* error count					*/
int	init;		/* initial predefinition phase			*/

#if DEFAULT_INCLUDE
jmp_buf	initenv;	/* return to initial phase			*/
#endif

#if QUOTE_ESCAPE
int	quote;		/* type of escaped quote -- " or '		*/
#endif

static struct			/* comment parse info			*/
{
	int	line;		/* line number -- !0 if in comment	*/
	int	pass;		/* pass comments as tokens		*/
#if CHECK_COMMENT
	int	delimiter;	/* line number of last comment delim	*/
	int	leading;	/* !0 if comment had leading text	*/
	int	warning;	/* !0 if warning already given		*/
#endif
} comment;

static struct			/* control directives			*/
{
	BUCKET	assert;
	BUCKET	class;		/* obsolete -- use "#pragma class"	*/
	BUCKET	define;
	BUCKET	elif;
	BUCKET	else_;
	BUCKET	endif;
	BUCKET	ident;		/* obsolete -- use "#pragma ident...	*/
	BUCKET	if_;
	BUCKET	ifdef;
	BUCKET	ifndef;
	BUCKET	include;
	BUCKET	line;
	BUCKET	pragma;
	BUCKET	undef;
} control;

static struct			/* special macros			*/
{
	BUCKET	dynamic;	/* dynamic symbols			*/
} special;

struct incinfo			/* include file info			*/
{
	struct incinfo	*next;	/* next in list				*/
	struct incinfo	*prev;	/* previous in list			*/
	char		*name;	/* file name				*/
	int		nest;	/* nesting level at start of include	*/
#if CHANGE_DIR
	char		*dir;	/* directory name			*/
#endif
	int		fd;	/* file descriptor			*/
	int		line;	/* line number				*/
#if TRIGRAPH
	int		offset;	/* skip offset chars of next read	*/
#endif
	struct bufinfo	*buf;	/* side buffer				*/
#if ONCE_INCLUDE
	struct fileinfo	*info;	/* file id info				*/
#if SCAN
	int		notext;	/* no text has been output		*/
#endif
#endif
};

struct incinfo	firstinc;		/* at least one file		*/
struct incinfo	*infile = &firstinc;	/* include file stack		*/

/*
 * the out* stuff provides block buffered output
 */

#define outc(c)		((*outbufp++=(c))&&(outbufp>=&outbuf[MAXBUF])?outflush():0)
#define outflush()	((write(fout,outbuf,outbufp-outbuf)!=(outbufp-outbuf))?outerr():(outbufp=outbuf,0))

static char	outbuf[MAXBUF];
static char	*outbufp = outbuf;

outb(p, m)
register char	*p, *m;
{
	register char	*b = outbufp;

	if ((b + (m - p)) >= &outbuf[MAXBUF])
	{
		memcpy(b, p, &outbuf[MAXBUF] - b);
		p += &outbuf[MAXBUF] - b;
		b = outbuf;
		if (write(fout, b, MAXBUF) != MAXBUF) outerr();
		while ((m - p) >= MAXBUF)
		{
			if (write(fout, outbuf, MAXBUF) != MAXBUF) outerr();
			p += MAXBUF;
		}
	}
	if (p < m)
	{
		memcpy(b, p, m - p);
		b += m - p;
	}
	outbufp = b;
}

outerr()
{
	extern int	errno;

	switch(errno)
	{
	case EFBIG:
		error(3, "output file too large");
	case ENOSPC:
		error(3, "output file device out of space");
#ifdef EDQUOT
	case EDQUOT:
		error(3, "output file exceeds disk quota");
#endif
	default:
		error(3, "error writing output file");
	}
}

#if ONCE_INCLUDE

#include <sys/types.h>
#include <sys/stat.h>

TABLE	filtab;		/* include file hash				*/

struct fileid		/* unique file identifier			*/
{
	dev_t	dev;	/* device					*/
	ino_t	ino;	/* inode					*/
};

struct fileinfo		/* include file identification info		*/
{
	char		*name;		/* file name			*/
	struct fileid	id;		/* unique identifier		*/
	struct fileinfo	*parent;	/* file including this		*/
	unsigned int	allow:1;	/* allow more than one		*/
#if SCAN
	unsigned int	done:1;		/* already #include'd		*/
#if DEFAULT_INCLUDE
	unsigned int	init:1;		/* init file			*/
#endif
	unsigned int	parameter:1;	/* only has #define's		*/
	unsigned int	used:1;		/* param file used		*/
#endif
};

/*
 * fileid hash
 */

unsigned int
ihash(id, size)
register struct fileid	*id;
{
	return((unsigned)(id->ino&(size - 1)));
}

/*
 * fileid comparison
 */

int
icompare(id1, id2)
register struct fileid	*id1, *id2;
{
	return(id1->ino != id2->ino || id1->dev != id2->dev);
}

#if SCAN
int		scan = 0;		/* scan for dependency info */
#endif

/*
 * check if (open) file can be included
 * 0 returned if file cannot be included
 * otherwise fileinfo pointer returned
 */

struct fileinfo*
chkinc(fd, allow)
int	fd;	/* open file descriptor */
int	allow;	/* allow multiple includes on this file */
{
	register struct fileinfo	*f;
	struct fileid			id;
	struct stat			st;

	if (fstat(fd, &st) < 0) return((struct fileinfo*)0);
	id.ino = st.st_ino;
	id.dev = st.st_dev;
	if (f = (struct fileinfo*)gethash(filtab, &id))
	{
		if (allow) f->allow = 1;
		return(f->allow || f->parent == infile->info ? f : (struct fileinfo*)0);
	}
	else
	{
		f = allocate(fileinfo);
		f->id = id;
		f->parent = infile->info;
		f->allow = allow;
#if SCAN && DEFAULT_INCLUDE
		f->init = init;
#endif
		(void)puthash(filtab, &f->id, (GENERIC)f);
		return(f);
	}
}
#endif

/*
 * output line number info
 */

lineinfo()
{
	if (!pflag)
	{
		(void)sprintf(tmp, "%c %d \"%s\"\n", SALT, infile->line, infile->name);
		outb(tmp, tmp + strlen(tmp));
	}
}

#if SCAN
/*
 * output scan info
 */

scaninfo(s1, s2, s3, s4)
char	*s1, *s2, *s3, *s4;
{
	(void)sprintf(tmp, "%s info %s %s %s %s\n", control.pragma->name, s1, s2, s3, s4);
	outb(tmp, tmp + strlen(tmp));
}
#endif

/*
 * data structure guide
 *
 * most of the scanning takes place in the buffer:
 *
 *  (low address)                                             (high address)
 *  pbeg                           pbuf                                 pend
 *  |      <-- MAXBUF chars -->      |         <-- MAXBUF chars -->        |
 *  _______________________________________________________________________
 * |_______________________________________________________________________|
 *          |               |               |
 *          |<-- waiting -->|               |<-- waiting -->
 *          |    to be      |<-- current -->|    to be
 *          |    written    |    token      |    scanned
 *          |               |               |
 *          outp            inp             p
 *
 *  *outp   first char not yet written to output file
 *  *inp    first char of current token
 *  *p      first char not yet scanned
 *
 * macro expansion: write from *outp to *inp (chars waiting to be written),
 * ignore from *inp to *p (chars of the macro call), place generated
 * characters in front of *p (in reverse order), update pointers,
 * resume scanning.
 *
 * symbol table pointers point to just beyond the end of macro definitions;
 * the first preceding character is the number of formal parameters.
 * the appearance of a formal in the body of a definition is marked by
 * 3 chars: the char WARN, the char 'A' and a char containing the parameter
 * number.  the first char of a definition is preceded by a zero character.
 *
 * when macro expansion attempts to back up over the beginning of the
 * buffer, some characters preceding *pend are saved in a side buffer,
 * the side buffer is stacked on 'curbuf', and the rest of the main
 * buffer is moved to the right.  the number of chars in the buffer
 * is kept in 'curbuf->size' since it may contain null chars.
 *
 * similar action is taken when an 'include' statement is processed,
 * except that the main buffer must be completely emptied.  the array
 * element 'infile->buf' records the last side buffer saved when
 * file 'infile->name' was included.  these buffers remain dormant
 * while the file is being read, and are reactivated at end-of-file.
 *
 * 'curbuf' is the linked list of all pending side buffers.  the sublist
 * from 'curbuf' to 'infile->buf' contains all the "live" side buffers.
 * the buffers in the sublist starting at 'infile->prev->buf' to the
 * end are dormant, waiting for end-of-file on the current file.
 *
 * space for side buffers is obtained from a special version of malloc()
 * (malloc() tuned for no free()'s).  'frebuf' is a linked list of
 * side buffers which are available for use.
 *
 * the char WARN must not appear in the input text.  internally WARN
 * is followed by a single char and an optional argument.  the possible
 * WARN sequences are:
 *
 *	WARN A (char)n		the n'th actual argument is placed here
 *	WARN D (char*)p		temporarily define the macro that p points to
 *	WARN S			separate the preceding and next token
 *	WARN U (char*)p		temporarily undef the macro that p points to
 *	WARN X			disable the expansion of the next symbol
 */

dump()
{
	/*
	 * write part of buffer which lies between  outp  and  inp.
	 * this should be a direct call to 'write', but the system slows
	 * to a crawl if it has to do an unaligned copy.  thus we buffer.
	 */

	register char	*p = outp, *m = inp, *op;

	if (p >= m || skip) return;
#if SCAN
	if (pflag || scan)
#else
	if (pflag)
#endif
	{
		op = p;
		while (p < m && isspace(*p)) p++;
		if (p >= m) return;
#if SCAN
		if (scan) infile->notext = 0;
#endif
		p = op;
	}
	if (text)
	{
		outb(p, m);
		outp = m;
	}
}

char*
refill(p)
register char	*p;
{
	/*
	 * dump buffer.  save chars from inp to p.  read into buffer at pbuf,
	 * contiguous with p.  update pointers, return new p.
	 */

	register char	*np, *op;
	register int	n;
	struct bufinfo	*bp;

	dump();
	op = inp;
	np = pbuf - (p - op);
	if (bob(np + 1))
	{
		error(2, "token too long");
		np = pbeg;
		p = op + MAXBUF;
	}
	macro.dam += np - op;
	outp = inp = np;
	/* MAY OVERLAP */
	memcpy(np, op, p - op);
	p = pbuf;
	for (;;)
	{
		if (curbuf != infile->buf)
		{
			/*
			 * retrieve hunk of pushed-back macro text
			 */

			memcpy(p, curbuf->buf, curbuf->size);
			pend = p + curbuf->size - 1;

			/*
			 * put the side buffer on the free list
			 */

			bp = curbuf;
			curbuf = bp->next;
			bp->next = frebuf;
			frebuf = bp;
			return(p);
		}
		else 
		{
			/*
			 * get more text from file(s)
			 */

			macro.level = 0;
			if ((n = read(fin, p, MAXBUF)) > 0)
			{
				*(pend = p + n) = '\0';
#if TRIGRAPH
				/*
				 * expand ANSI ??* trigraph sequences
				 * offset avoids unaligned reads when
				 * a trigraph spans a MAXBUF boundary
				 */

				p += infile->offset;
				infile->offset = 0;
				op = pend;
				for (np = op = p; *op;)
				{
					if (*op == '?')
					{
						if (*++op != '?')
						{
							if (!*op)
							{
								if (read(fin, --op, 1) <= 0)
								{
									*np++ = '?';
									break;
								}
								if (*op != '?')
								{
									*np++ = '?';
									*np++ = *op;
									if (lseek(fin, -1, 1) >= 0)
										infile->offset++;
									break;
								}
							}
							else
							{
								*np++ = '?';
								*np++ = *op++;
							}
						}
						if (!*++op)
						{
							if (read(fin, --op, 1) <= 0)
							{
								*np++ = '?';
								*np++ = '?';
								if (lseek(fin, -1, 1) >= 0)
									infile->offset++;
								break;
							}
						}
						switch (*op++)
						{
						case '=':
							*np++ = '#';
							break;
						case '(':
							*np++ = '[';
							break;
						case '/':
							*np++ = '\\';
							break;
						case ')':
							*np++ = ']';
							break;
						case '\'':
							*np++ = '^';
							break;
						case '<':
							*np++ = '{';
							break;
						case '!':
							*np++ = '|';
							break;
						case '>':
							*np++ = '}';
							break;
						case '-':
							*np++ = '~';
							break;
						default:
							error(1, "??%c: invalid trigraph", *(op - 1));
							break;
						}
					}
					else *np++ = *op++;
				}
				*(pend = np) = '\0';
#endif
				return(p);
			}

			/*
			 * end of include file
			 * do some structural consistency checking
			 */

			if (comment.line)
			{
				n = infile->line;
				infile->line = comment.line;
				error(1, "unterminated comment");
				infile->line = n;
				comment.line = 0;

				/*
				 * close off the comment
				 */

				*np++ = '*';
				*np++ = '/';
				*np++ = '\n';
				pend = np;
				*np = '\0';
				return(p);
			}
			if (infile->nest != iflev)
			{
				if (iflev > infile->nest)
					error(2, "missing %d %s%s", iflev - infile->nest, control.endif->name, iflev - infile->nest == 1 ? "" : "'s");
				else error(2, "%d too many %s's", infile->nest - iflev, control.endif->name);
				skip = 0;
				iflev = infile->nest;
			}
			if (macro.pcount)
			{
				n = infile->line;
				infile->line = macro.line;
				error(2, "%s: unterminated macro call", macro.name);
				infile->line = n;
				np = p;

				/*
				 * shut off unterminated quoted string
				 */

				*np++ = '\n';

				/*
				 * supply missing parens and newline
				 */

				n = macro.pcount;
				while (--n >= 0) *np++ = ')';
				*np++ = '\n';
				pend = np;
				*np = '\0';
				return(p);
			}
			if (!infile->prev)
			{
				/*
				 * end of input
				 */

				inp = p;
				dump();
				cleanup();
			}
			close(fin);
#if SCAN
			if (scan)
			{
				infile->info->done = 1;
				if (infile->notext)
				{
					infile->info->parameter = 1;
					scaninfo("parameter", infile->info->name, "", "");
				}
				else infile->prev->notext = 0;
				scaninfo("end", infile->info->name, "", "");
			}
#endif
			infile = infile->prev;
			fin = infile->fd;
#if CHANGE_DIR
			dirs->name = infile->dir;
#endif
			lineinfo();
			crossfile(infile->name);
#if DEFAULT_INCLUDE
			if (init && !infile->prev) longjmp(initenv, 1);
#endif
		}
	}
}

#define BEGIN	0
#define NEWLINE	1

static int	state = BEGIN;
static int	speakup = 0;

char*
cotoken(p)
register char	*p;
{
	register int	q;
#if UNDEF_MACRO
	char		*x;
#endif
#if DISABLE_MACRO
	int		disable = 0;
#endif

	if (state != BEGIN) goto prevnl;
	for (;;)
	{
#if DISABLE_MACRO
		disable = 0;
#endif
	again:
		while (!isspc(*p++));
		switch (*(inp = p - 1))
		{
		case 0:
			if (eob(--p))
			{
				p = refill(p);
				goto again;
			}
			else p++;	/* ignore null byte */
			break;
		case '|':
		case '&':
			for (;;)	/* sloscan only */
			{
				if (*p == *inp)
				{
					p++;
					break;
				}
				if (eob(p)) p = refill(p);
				else break;
			}
			break;
		case '=':
		case '!':
			for (;;)	/* sloscan only */
			{
				if (*p == '=')
				{
					p++;
					break;
				}
				if (eob(p)) p = refill(p);
				else break;
			}
			break;
		case '<':
		case '>':
			for (;;)	/* sloscan only */
			{
				if (*p == '=' || *p == *(p - 1))
				{
					p++;
					break;
				}
				if (eob(p)) p = refill(p);
				else break;
			}
			break;
		case '\\':
			for (;;)
			{
				if (*p == '\n')
				{
					p++;
					infile->line++;
					break;
				}
				if (eob(p)) p = refill(p);
#if QUOTE_ESCAPE
				else if (quote)
				{
					p++;
					break;
				}
#endif
				else
				{
#if QUOTE_ESCAPE
					if (*p == '"' || *p == '\'')
					{
						/*
						 * #define x y
						 * #define y z
						 * \"x"
						 * expands to
						 * "z"
						 */

						quote = *p;
						inp = p - 1;
						dump();
						outp = p++;
					}
					else
#endif
#if PLUS_SEP
					if (*p == '+')
					{
						inp = p - 1;
						dump();
						outp = ++p;
					}
					else
#endif
					p++;
					break;
				}
			}
			break;
		case '/':
			for (;;)
			{
				if (*p == '*')
				{
					/*
					 * comment
					 */

					comment.line = infile->line;
#if CHECK_COMMENT
					comment.delimiter = infile->line;
					comment.leading = comment.warning = 0;
#endif
					if (!comment.pass)
					{
#if COMMENT_BLANK
						/*
						 * comments translate to ' '
						 */

						*(p - 1) = ' ';
						inp = p;
#else
						/*
						 * comments terminate tokens
						 * but cause no output
						 */

						inp = p - 1;
#endif
						dump();
						skip++;
					}
					p++;
					for (;;)
					{
						while (!iscom(*p++));
						if (*(p - 1) == '*') for (;;)
						{
							if (*p++ == '/') goto endcom;
							if (eob(--p))
							{
								if (!comment.pass)
								{
									inp = p;
									p = refill(p);
								}
								else if ((p - inp) >= MAXBUF)
								{
									/*
									 * split long comment
									 */

									*p++ = '*';
									*p++ = '/';
									inp = p;
									p = refill(p);
									outp = inp = p -= 2;
									*p++ = '/';
									*p++ = '*';
								}
								else p = refill(p);
							}
							else break;
						}
#if CHECK_COMMENT
						else if (*(p - 1) == '/') for (;;)
						{
							if (*p++ == '*' && comment.line != infile->line && !comment.warning)
							{
								if (comment.leading || comment.delimiter < infile->line - 1)
								{
									error(1, "\"/*\" found in comment starting at line %d", comment.line);
									comment.warning++;
								}
								comment.delimiter = infile->line;
								break;
							}
							if (eob(--p))
							{
								if (!comment.pass)
								{
									inp = p;
									p = refill(p);
								}
								else if ((p - inp) >= MAXBUF)
								{
									/*
									 * split long comment
									 */

									*p++ = '*';
									*p++ = '/';
									inp = p;
									p = refill(p);
									outp = inp = p -= 2;
									*p++ = '/';
									*p++ = '*';
								}
								else p = refill(p);
							}
							else break;
						}
#endif
						else if (*(p - 1) == '\n')
						{
#if CHECK_COMMENT
							comment.leading = 0;
#endif
							infile->line++;
							if (!comment.pass && skip <= 1 && !pflag)
								outc('\n');
						}
#if CHECK_COMMENT
						else if (*(p - 1) == ';' || *(p - 1) == ')')
							comment.leading++;
#endif
						else if (eob(--p))
						{
							if (!comment.pass) p = refill(inp = p);
							else if ((p - inp) >= MAXBUF)
							{
								/*
								 * split long comment
								 */

								*p++ = '*';
								*p++ = '/';
								inp = p;
								p = refill(p);
								outp = inp = p -= 2;
								*p++ = '/';
								*p++ = '*';
							}
							else p = refill(p);
						}
						else p++;	/* ignore null byte */
					}
				endcom:
					comment.line = 0;
					if (!comment.pass)
					{
						outp = inp = p;
						skip--;
						goto again;
					}
					break;
				}
				if (eob(p)) p = refill(p);
				else break;
			}
			break;
		case '"':
		case '\'':
			q = *(p - 1);
#if QUOTE_ESCAPE
			if (quote)
			{
				if (q == quote) quote = 0;
			}
			else
#endif
			for (;;)
			{
				while (!isquo(*p++));
				if (*(p - 1) == q) break;
				if (*(p - 1) == '\n')	/* bare \n terminates quotation */
				{
					error(1, "unterminated %c constant", q);
					p--;
					break;
				}
				if (*(p - 1) == '\\')
					for (;;)
					{
						if (*p == '\n')	/* escaped \n ignored */
						{
							p++;
							infile->line++;
							break;
						}
						if (eob(p)) p = refill(p);
						else
						{
							p++;
							break;
						}
					}
				else if (eob(--p)) p = refill(p);
				else p++;	/* it was a different quote character */
			}
			break;
		case WARN:
			dump();
			if (eob(p)) p = refill(p);
			switch (*p++)
			{
#if UNDEF_MACRO
			case 'D':
				/*
				 * define a temporarily undefined macro
				 */

				getnum(x, char*);
				*(x - 1) &= ~DISABLE;
				break;

			case 'U':
				/*
				 * temporarily undefine a macro
				 */

				getnum(x, char*);
				*(x - 1) |= DISABLE;
				break;
#endif
			case 'N':
				/*
				 * newline in macro call
				 */

				getnum(speakup, int);
				break;
#if DISABLE_MACRO
			case 'X':
				/*
				 * disable expansion of next symbol
				 */

				disable++;
				break;
#endif
			}
			inp = outp = p;
			goto again;
		case '\n':
#if QUOTE_ESCAPE
			if (quote)
			{
				error(1, "unterminated %c constant", quote);
				quote = 0;
			}
#endif
			infile->line++;
			if (isslo)
			{
				state = NEWLINE;
				return(p);
			}
		prevnl:
			if (speakup)
			{
				inp = p;
				dump();
				infile->line = speakup + 1;
				lineinfo();
				speakup = 0;
			}
			state = BEGIN;
			for (;;)
			{
				if (isdelim(*p))
				{
					register char *s = p;

					while (isdelim(*++s));
					if (*s == SALT)
					{
						/*
						 * move the SALT to the front!
						 */

						*s = *p;
						*p = SALT;
					}
				}
				if (*p == SALT) return(++p);
				if (eob(inp = p)) p = refill(p);
				else break;
			}
			goto again;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			for (;;)
			{
				while (isnum(*p++));
				if (eob(--p)) p = refill(p);
				else break;
			}
			break;
		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T':
		case 'U': case 'V': case 'W': case 'X': case 'Y':
		case 'Z': case '_':
		case 'a': case 'b': case 'c': case 'd': case 'e':
		case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't':
		case 'u': case 'v': case 'w': case 'x': case 'y':
		case 'z':
#if DISABLE_MACRO
			if (disable)
			{
				disable = 0;
				goto notdef;
			}
#endif
			if (skip) goto notdef;
			for (;;)
			{
				if (!tstcode1(*(p - 1), 0)) goto notdef;
				if (!tstcode1(*p++, 1)) goto endid;
				if (!tstcode1(*p++, 2)) goto endid;
				if (!tstcode1(*p++, 3)) goto endid;
				if (!tstcode1(*p++, 4)) goto endid;
				if (!tstcode1(*p++, 5)) goto endid;
				if (!tstcode1(*p++, 6)) goto endid;
				if (!tstcode1(*p++, 7)) goto endid;
				while (isid(*p++));
				goto getid;
			endid:
				if (isid(*(p - 1))) goto notdef;
			getid:
				if (eob(--p))
				{
					(void)refill(p);
					p = inp + 1;
					continue;
				}
#if DEBUG
				stats.lookups++;
#endif
				(void)slookup(inp, p, FIND);
				if (newp)
				{
#if DEBUG
					stats.found++;
#endif
					p = newp;
					goto again;
				}
				else break;
			}
			break;
		notdef:
#if DEBUG
			if (!skip) stats.code1++;
#endif
			for (;;)
			{
				while (isid(*p++));
				if (eob(--p)) p = refill(p);
				else break;
			}
			break;
		}
		if (isslo) return(p);
	}
}

char*
skipbl(p)		/* get next non-blank token */
register char	*p;
{
	do p = cotoken(outp = inp = p); while (isblank(*inp));
	return(p);
}

char*
eatline(p, extra)		/* flush to newline w/extra expected tokens */
register char	*p;
register int	extra;
{
	int	opass;

	opass = comment.pass;
	comment.pass = 0;
	skip++;
	if (isblank(*inp)) p = skipbl(p);
	while (*inp != '\n')
	{
		if (!extra--)
			error(1, "extra character%s \"%.*s%s\" ignored", p > inp + 1 || *p != '\n' ? "s" : "", p - inp, inp, *p == '\n' ? "" : "...");
		p = skipbl(p);
	}
	skip--;
	comment.pass = opass;
	if (pflag) inp = outp = p;
	return(p);
}

char*
unfill(p)
register char	*p;
{
	/*
	 * take <= MAXBUF chars from right end of buffer and put
	 * them on curbuf->buf.  slide rest of buffer to the right,
	 * update pointers, return new p.
	 */

	register char	*np, *op;
	register int	n;
	struct bufinfo	*bp;

	/*
	 * allocate a side buffer
	 */

	if (frebuf)
	{
		bp = frebuf;
		frebuf = frebuf->next;
	}
	else bp = allocate(bufinfo);
	bp->next = curbuf;
	curbuf = bp;
	np = bp->buf;
	op = pend - MAXBUF;
	if (op < p) op = p;

	/*
	 * out with old
	 */

	n = pend - op;
	memcpy(np, op, n);
	np += n;
	op += n;
	while (*np++ = *op++);

	/*
	 * mark end of saved text
	 */

	bp->size = np - bp->buf;
	np = pbuf + MAXBUF;
	op = pend - MAXBUF;
	pend = np;
	if (op < p) op = p;
	n = op - outp;
	np -= n;
	if (bob(np))
	{
		error(2, "token too long");
		n -= pbeg - np - 1;
		np += n;
	}

	/*
	 * slide over new
	 */

	/* MAY OVERLAP */
	memcpy(np, outp, n);
	n = np - outp;
	outp += n;
	inp += n;
	macro.dam += n;
	return(p + n);
}

int
search(file, inctype)
char	*file;
int	inctype;
{
	register int		fd;
	register struct dirinfo	*dp;

	/*
	 * look for included file
	 */

	if (ignoresrc) inctype = 1;
	for (dp = inctype ? dirs->next : dirs; dp; dp = dp->next)
	{
		if (*file == '/' || !*dp->name) strcpy(path, file);
		else
		{
			strcpy(path, dp->name);
#if unix
			strcat(path, "/");
#endif
#if ibm
			strcat(path, ".");
#endif
			strcat(path, file);
		}
		if ((fd = open(path, 0)) >= 0)
		{
#if DEBUG
			error(-2, "search: %s found", path);
#endif
			return(fd);
		}
		else if (errno == EMFILE) error(3, "%s: too many open files", file);
		else if (*file == '/') break;
	}
#if DEBUG
	error(-2, "search: %s not found", file);
#endif
	return( - 1);
}

char*
doincl(p)
register char	*p;
{
	int		inctype;
	register char	*cp;
	char		file[MAXPATH];

	p = skipbl(p);
	cp = file;
	if (*inp++ == '<')
	{
		/*
		 * <> syntax
		 */

		inctype = 1;
		skip++;	/* prevent macro expansion */
		for (;;)
		{
			p = cotoken(outp = inp = p);
			if (*inp == '\n')
			{
				*cp = '\0';
				break;
			}
			else if (*inp == '>')
			{
				p = cotoken(outp = inp = p);
				*cp = '\0';
				break;
			}
			while (inp < p) *cp++ = *inp++;
		}
		skip--;
	}
	else if (*(inp - 1) == '"')	/* regular "" syntax */
	{
		inctype = 0;
		while (inp < p) *cp++ = *inp++;
		if (*--cp == '"') *cp = '\0';
		p = cotoken(outp = inp = p);
	}
	else
	{
		error(2, "bad include syntax -- \" or < expected", 0);
		inctype = 2;
	}
	inp = p = eatline(p, 0);
	dump();
	if (inctype == 2) return(p);
	if (!infile->next)
	{
		infile->next = allocate(incinfo);
		infile->next->prev = infile;
	}

	/*
	 * portability check
	 */

	if (*file == '/' && !strncmp(file, lastdir->name, strlen(lastdir->name)))
		error(1, "%s %c%s...%c may be non-portable", control.include->name, inctype ? '<' : '"', lastdir->name, inctype ? '>' : '"');

	/*
	 * look for included file
	 */

	if ((infile->next->fd = search(file, inctype)) < 0)
	{
		error(2, "cannot find include file %s", file);
#if DEFAULT_INCLUDE
		if (init && !infile->prev) longjmp(initenv, 1);
#endif
	}
	else
	{
		cp = path;
		if (*cp == '.' && *(cp + 1) == '/') cp += 2;
#if ONCE_INCLUDE
		if (!(infile->next->info = chkinc(infile->next->fd, 0)))
		{
			close(infile->next->fd);
			return(p);
		}
#endif
		infile = infile->next;
		fin = infile->fd;
		infile->line = 1;
		infile->name = copy(cp);
		infile->nest = iflev;
#if TRIGRAPH
		infile->offset = 0;
#endif
#if CHANGE_DIR
		infile->dir = dirs->name = trmdir(copy(infile->name));
#endif
		lineinfo();
#if SCAN
		if (scan)
		{
			infile->notext = 1;
			infile->info->name = copy(file);
			scaninfo("include", file, infile->name, "");
		}
#endif
		crossfile(infile->name);

		/*
		 * save current contents of buffer
		 */

		while (!eob(p)) p = unfill(p);
		infile->buf = curbuf;
	}
	return(p);
}

/*
 * the val* stuff supports arbitrary length macro definitions
 */

#define valdeclare	register char *val;char *valold, *valmax, *valnew;int valsiz
#define valinit		val=valold=malloc(valsiz=MAXBUF);valmax=val+valsiz
#define valgrow		(valnew=realloc(valold,valsiz+=MAXBUF),val=valnew+(val-valold),valmax=(valold=valnew)+valsiz)
#define valput(c)	((val>=valmax?valgrow:valmax),*val++=(c))
#define valunput()	(val--)

/*
 * process #define
 */

char*
dodef(p)
char	*p;
{
	valdeclare;
	register char	*pin, *cf;
	char		**pf, **qf;
	int		c, params;
	int		ex_blank; /* ignore extra blanks in token-string */
	int		sav_pass = comment.pass;
#if SALT_MACRO
	int		actquote;	/* quote actual */
#endif
	BUCKET		np;
	char		*nvalue;
	char		*formal[MAXFRM]; /* formal[n-1] is name of nth formal */
	char		formtxt[MAXBUF]; /* space for formal names */

	/*
	 * first char in np->value encodes macro parameters
	 *
	 *		0		symbol
	 *		1		macro with no formals
	 *		k>1		macro with k-1 formals
	 */

	skip++;	/* prevent macro expansion during 'define' */
	p = skipbl(p);
	pin = inp;
	if (!isident(*pin))
	{
		error(2, "invalid macro name");
		while (*inp != '\n') p = skipbl(p);
		return(p);
	}
	if (inppsym)
	{
		*--pin = SALT;
		np = slookup(pin, p, ENTER|SPECIAL);
		pin++;
	}
	else
	{
		np = slookup(pin, p, ENTER);
 		crossinfo("D", np->name, infile->line);
	}
	params = 0;
	p = cotoken(outp = inp = p);
	pin = inp;
	if (*pin == '(')	/* with parameters; identify the formals */
	{
 		crossinfo("F", np->name, infile->line);
		params++;
		cf = formtxt;
		pf = formal;
		for (;;)
		{
			p = skipbl(p);
			pin = inp;
			if (*pin == '\n')
			{
				infile->line--;
				p--;
				error(2, "%s: missing )", np->name);
				break;
			}
			if (*pin == ')') break;
			if (*pin == ',') continue;
			if (!isident(*pin))
			{
				c = *p;
				*p = '\0';
				error(2, "bad formal: %s", pin);
				*p = c;
			}
			else if (pf >= &formal[MAXFRM])
			{
				c = *p;
				*p = '\0';
				error(2, "%s: too many formals -- %d max", pin, MAXFRM);
				*p = c;
			}
			else
			{
				*pf++ = cf;
				while (pin < p) *cf++ = *pin++;
				*cf++ = '\0';
				params++;
 				crossinfo("F", *(pf - 1), infile->line);
			}
		}
	}
	else if (*pin == '\n')
	{
		infile->line--;
		p--;
	}
	else if (!isblank(*pin)) p = pin;
	valinit;
	valput('\0');
	comment.pass = 1;/* make cotoken() return comments as tokens	*/
	ex_blank = 1;	/* collapse delimiters into one blank		*/
#if SALT_MACRO
	actquote = 0;	/* quote next actual				*/
#endif
	for (;;)	/* accumulate definition until newline		*/
	{
		p = cotoken(outp = inp = p);
		pin = inp;
		if (*pin == '\\')
		{
			if (*(pin + 1) == '\n')
			{
				/*
				 * ignore escaped newline
				 */

#if NEWLINE_BLANK
				if (!ex_blank)
				{
					/*
					 * replace it with a blank
					 */

					valput(' ');
					ex_blank = 1;
				}
#endif
				if (!pflag) outc('\n');
				continue;
			}
		}
		else if (*pin == '\n') break;
		else if (isblank(*pin))
		{
			/*
			 * skip extra blanks
			 */

			if (ex_blank) continue;

			/*
			 * force it to be a "real" blank
			 */

			*pin = ' ';
			ex_blank = 1;
		}
		else if (*pin == '/' && *(pin + 1) == '*')
		{
			/*
			 * skip comment except for \n's
			 */

			if (pflag) pin = p;
			else while (pin < p)
				if (*pin++ == '\n')
					outc('\n');
#if COMMENT_BLANK
			if (!ex_blank)
			{
				ex_blank = 1;
				valput(' ');
			}
#else
			ex_blank = 0;
#endif
			continue;
		}
#if SALT_MACRO
		else if (*pin == SALT)
		{
			p = cotoken(outp = inp = p);
			pin = inp;
			if (*pin == SALT)
			{
				if (ex_blank) valunput();
				else ex_blank = 1;
				valput('S');
				valput(WARN);
			}
			else
			{
				actquote = 1;
				p = pin;
			}
			continue;
		}
#endif
		else ex_blank = 0;
		if (params)
		{
			/*
			 * mark the appearance of formals in the definiton
			 */

			if (isident(*pin))
			{
				c = *p;
				*p = '\0';
				for (qf = pf; --qf >= formal;)
				{
					if (**qf == *pin && !strcmp(*qf, pin))
					{
#if MACRO_FORMAL
 						crossinfo("R", *qf, infile->line);
#endif
#if SALT_MACRO
						if (actquote)
						{
							valput('\\');
							valput('"');
						}
#endif
						valput(qf - formal + 1);
						valput('A');
						valput(WARN);
#if SALT_MACRO
						if (actquote) valput('"');
#endif
						pin = p;
						break;
					}
				}
				*p = c;
			}
#if QUOTE_FORMAL
			else if (*pin == '"' || *pin == '\'')
			{
				/*
				 * inside quotation marks, too
				 */

				char	q = *pin;

				valput(*pin++);
				while (pin < p && *pin != q)
				{
					while (pin < p && !isid(*pin))
					{
						if (*pin == '\n' && *(pin - 1) == '\\')
						{
							if (!pflag) outc('\n');
							val--;	/* no \ */
							pin++;	/* no \n */
						}
						else valput(*pin++);
					}
					for (cf = pin; cf < p && isid(*cf); cf++);
					c = *cf;
					*cf = '\0';
					for (qf = pf; --qf >= formal;)
					{
						if (**qf == *pin && !strcmp(*qf, pin))
						{
							valput(qf - formal + 1);
							valput('A');
							valput(WARN);
							pin = cf;
							break;
						}
					}
					*cf = c;
					while (pin < cf) valput(*pin++);
				}
			}
#endif
		}
#if SALT_MACRO
		actquote = 0;
#endif
#if DISABLE_MACRO
		if (pin < p && isid(*pin) && *pin == *np->name)
		{
			c = *p;
			*p = '\0';
			if (!strcmp(pin, np->name))
			{
				/*
				 * disable a macro name in its definition
				 */

				valput('X');
				valput(WARN);
			}
			*p = c;
		}
#endif
		while (pin < p)
			if (*pin == '\n' && *(pin - 1) == '\\')
			{
				if (!pflag) outc('\n');
				val--;		/* no \ */
				pin++;		/* no \n */
			}
			else valput(*pin++);
	}
	comment.pass = sav_pass;

	/*
	 * if token-string ended with a blank
	 * then it is unnecessary -- throw away
	 */

	if (*(val - 1) == ' ') val--;
	if (init) params |= PREDEF;
	valput(params);
	nvalue = val;
	valput('\0');
#if SCAN
	if (scan)
	{
		cf = (char*)&infile->info;
		for (c = 0; c < sizeof(struct fileinfo*); c++)
			valput(*cf++);
	}
#endif
	if (cf = np->value)
	{
		/*
		 * redefinition -- check if new is different from old
		 */

		cf--;
		while (*--cf);
		if (strcmp(++cf, valold))
		{
			/*
			 * redefinition is different from old
			 */

			infile->line--;
			error(1, "%s redefined", np->name);
			infile->line++;
			np->value = nvalue;
#if SCAN
			if (scan) valput('\0');
#endif
		}
		else val = valold;
	}
	else
	{
		np->value = nvalue;
#if SCAN
		if (scan) valput('\0');
#endif
	}
	skip--;
	inp = pin;

	/*
	 * this realloc() always shrinks
	 */

	(void)realloc(valold, val - valold);
	return(p);
}

/*
 * process #assert
 */

char*
doass(p)
register char	*p;
{
	register char	*pin, *pa;
	char		argtxt[MAXBUF];	/* space for predicate argument */
	BUCKET		np;
	int		i;
	char		*val, *valold;

	skip++;
	p = skipbl(p);
	pin = inp;
	if (!isident(*pin))
	{
		error(2, "invalid predicate name");
		while (*inp != '\n') p = skipbl(p);
		return(p);
	}
	for (pa = argtxt; pin < p; *pa++ = *pin++);
	p = cotoken(outp = inp = p);
	if (*inp != '(')
	{
		error(2, "predicate argument missing");
		while (*inp != '\n') p = skipbl(p);
		return(p);
	}
	*pa++ = '(';
	for (;;)
	{
		p = skipbl(p);
		pin = inp;
		if (*pin == '\n')
		{
			infile->line--;
			p--;
			error(2, "missing ) in assertion");
			break;
		}
		else if (*pin == ')') break;
		while (pin < p) *pa++ = *pin++;
	}
	*pa++ = ')';
	*pa = '\0';
	pa = argtxt;
	while (*inp != '\n') p = skipbl(p);
#if DEBUG
	error(-4, "assert(%s)", pa);
#endif
	np = lookup(pa, ENTER|SPECIAL);
	val = valold = malloc(MAXBUF);
	*val++ = '1';
	*val++ = '\0';
	np->value = val;
#if SCAN
	if (scan)
	{
		pa = (char*)&infile->info;
		for (i = 0; i < sizeof(struct fileinfo*); i++)
			*val++ = *pa++;
	}
#endif
	*val++ = '\0';

	/*
	 * this realloc() always shrinks
	 */

	(void)realloc(valold, val - valold);
	skip--;
	return(p);
}

#define fasscan()	ptrtab = fastab + COFF
#define sloscan()	ptrtab = slotab + COFF

/*
 * find and handle preprocessor control lines
 */

char*
ppcontrol(p)
register char	*p;
{
	register BUCKET	np;
	int		extra;
#if MATCH_EXTRA
	int		i;
#endif

	for (;;)
	{
		fasscan();
		p = cotoken(p);
		if (*inp == '\n') ++inp;
		dump();
		sloscan();

		/*
		 * don't expand control names
		 * this allows new controls to be added without
		 * the chance of being clobbered by statements
		 * such as "#define include ???"
		 */

		skip++;
		p = skipbl(p);
		*--inp = SALT;
		outp = inp;
		np = slookup(inp, p, FIND);
		skip--;
		extra = -1;
		if (np == control.define)
		{
			if (!skip)
			{
				p = dodef(p); 
				continue;
			}
		}
		else if (np == control.include)
		{
			if (!skip)
			{
				p = doincl(p);
				continue;
			}
		}
		else if (np == control.ifndef)
		{
			if (++iflev >= MAXIF) error(3, "unreasonable if nesting -- %d max", MAXIF);
			skip++;
			p = skipbl(p);
			np = slookup(inp, p, DEFINED);
			skip--;
			if (skip || !np->value) ifstack[iflev] = KEPT;
			else
			{
				skip++;
				ifstack[iflev] = SKIP;
			}
			extra = 1;
#if MATCH_EXTRA
			ifmatch[iflev] = np;
#endif
			crossinfo("R", xcopy(inp, p), infile->line);
		}
		else if (np == control.ifdef)
		{
			if (++iflev >= MAXIF) error(3, "unreasonable if nesting -- %d max", MAXIF);
			skip++;
			p = skipbl(p);
			np = slookup(inp, p, DEFINED);
			skip--;
			if (skip || np->value) ifstack[iflev] = KEPT;
			else
			{
				skip++;
				ifstack[iflev] = SKIP;
			}
			extra = 1;
#if MATCH_EXTRA
			ifmatch[iflev] = np;
#endif
			crossinfo("R", xcopy(inp, p), infile->line);
		}
		else if (np == control.endif)
		{
			if (iflev <= 0) error(2, "if-less %s", np->name);
			else
			{
				if ((ifstack[iflev] & SKIP) && !--skip) lineinfo();
#if MATCH_EXTRA
				if (ifmatch[iflev])
				{
					skip++;
					p = skipbl(p);
					if (*inp == '!') p = skipbl(p);
					if (*inp != '\n' && strncmp(ifmatch[iflev]->name, inp, p - inp))
						error(1, "%.*s does not match %s in %s", p - inp, inp, ifmatch[iflev]->name, control.endif->name);
					skip--;
				}
#endif
				iflev--;
			}
			extra = 1;
		}
		else if (np == control.else_ || np == control.elif)
		{
			if (iflev <= 0) error(2, "if-less %s", np->name);
			else if (skip <= 1)
			{
				if (ifstack[iflev] & ELSE) error(2, "%s follows %s", control.else_->name, np->name);
				if (np == control.elif) np = control.if_;
				else if (*p == '\n')
				{
					np = (BUCKET)0;
					ifstack[iflev] |= ELSE;
				}
				else
				{
					skip++;
					p = skipbl(p);
					*--inp = SALT;
					np = slookup(inp, p, FIND);
					++inp;
					skip--;
					if (np != control.if_ && np != control.ifdef && np != control.ifndef)
					{
						ifstack[iflev] |= ELSE;
#if MATCH_EXTRA
						if (ifmatch[iflev])
						{
							skip++;
							if (*inp == '!') p = skipbl(p);
							if (*inp != '\n' && strncmp(ifmatch[iflev]->name, inp, p - inp))
								error(1, "%.*s does not match %s in %s", p - inp, inp, ifmatch[iflev]->name, control.else_->name);
							skip--;
						}
						extra = 1;
#else
						extra = 0;
#endif
					}
				}
				if (ifstack[iflev] & KEPT)
				{
					if (!skip)
					{
						ifstack[iflev] |= SKIP;
						skip++;
					}
				}
				else
				{
					register int	take;

					if (np == control.if_)
					{
						newp = p;
						take = eval();
						p = newp;
					}
					else if (np == control.ifdef || np == control.ifndef)
					{
						skip++;
						p = skipbl(p);
						take = (slookup(inp, p, DEFINED)->value != 0) == (np == control.ifdef);
						skip--;
						extra = 1;
					}
					else take = 1;
					if (take)
					{
						ifstack[iflev] &= ~SKIP;
						ifstack[iflev] |= KEPT;
						if (skip) skip--;
						if (np)
						{
							infile->line--;
							lineinfo();
							infile->line++;
						}
						else lineinfo();
					}
				}
			}
		}
		else if (np == control.undef)
		{
			if (!skip)
			{
				skip++;
				p = skipbl(p);
				(void)slookup(inp, p, REMOVE);
				skip--;
				extra = 1;
			}
			crossinfo("R", xcopy(inp, p), infile->line);
		}
		else if (np == control.if_)
		{
			if (++iflev >= MAXIF) error(3, "unreasonable if nesting -- %d max", MAXIF);
			newp = p;
			crossline(infile->line);
#if MATCH_EXTRA
			skip++;
			newp = skipbl(newp);
			if ((i = *inp) == '!') newp = skipbl(p = newp);
			ifmatch[iflev] = slookup(inp, newp, DEFINED);
			if (i == '!') *--p = '!';
			newp = p;
			skip--;
#endif
			if (skip || eval()) ifstack[iflev] = KEPT;
			else
			{
				ifstack[iflev] = SKIP;
				skip++;
			}
			p = newp;
		}
		else if (np == control.line || (isdigit(*inp) && (inp = p)))
		{
			if (!skip && !pflag)
			{
				register char *s;
				register int ln;

				outp = inp = p;
				*--outp = '#';

				/*
				 * make sure that the whole
				 * directive has been read
				 */

				s = p;
				while (*s && *s != '\n') s++;
				if (eob(s)) p = refill(s);

				/*
				 * eat the line number
				 */

				s = inp;
				while (isblank(*s)) s++;
				ln = 0;
				while (isdigit(*s)) ln = ln * 10 + *s++ - '0';
				if (ln) infile->line = ln - 1;
				else error(2, "bad number for %s", control.line->name);

				/*
				 * eat the optional "filename"
				 */

				while (isblank(*s)) s++;
				if (*s != '\n')
				{
					if (*s != '"') error(2, "bad file for %s", control.line->name);
					else
					{
						register char *t = tmp;

						for (;;)
						{
							if (*++s == '"') break;
							else if (!*s || *s == '\n')
							{
								error(2, "bad file for %s", control.line->name);
								break;
							}
							*t++ = *s;
						}
						*t++ = '\0';
						t = tmp;
						if (strcmp(t, infile->name))
							infile->name = copy(t);
					}
				}

				/*
				 * push it all along to be eventually printed
				 */

				while (*inp != '\n') p = cotoken(p);
				continue;
			}
		}
		else if (np == control.pragma)
		{
			int	val, savch;
			char	*op;

			op = inp;
			p = skipbl(p);
			if (*inp == '\n') break;
			if (*inp == 'n' && *(inp + 1) == 'o')
			{
				inp += 2;
				val = 0;
			}
			else val = 1;
			savch = *p;
			*p = '\0';
			if (!strcmp(inp, "class")) errors = val ? CLASSCODE : 0;
#if ONCE_INCLUDE
			else if (!strcmp(inp, "multiple")) infile->info->allow = val;
#endif
			else if (!strcmp(inp, "text")) text = val;
			else if (!pflag)
			{
				/*
				 * pass it on to the output
				 */

#if !NEW_IDENT
				/*
				 * delete the !NEW_IDENT code when the
				 * compiler accepts `#pragma ident="..."'
				 */

				if (!strcmp(inp, "ident"))
				{
					/*
					 * translate to #ident for old compiler
					 */
	
					*p = savch;
					outc(SALT);
					while (*inp != '\n')
					{
						if (*inp == '=') *inp = ' ';
						p = cotoken(p);
					}
				}
				else
				{
#endif
				*p = savch;
				outb(np->name, np->name + strlen(np->name));
				*--inp = ' ';
				while (*inp != '\n')
					p = cotoken(p);
#if !NEW_IDENT
				}
#endif
			}
			else *p = savch;
		}
		else if (np == control.assert)
		{
			if (!skip)
			{
				p = doass(p); 
				continue;
			}
		}
		else if (np == control.ident)
		{
			error(1, "%s: use `%s ident=\"...\"' instead", np->name, control.pragma->name);
			if (!pflag)
				while (*inp != '\n')
					p = cotoken(p);
		}
		else if (np == control.class)
		{
			error(1, "%s: use `%s class' instead", np->name, control.pragma->name);
			errors = CLASSCODE;
		}
		else if (*++inp == '\n')
		{
			/*
			 * null directive
			 */

			outp = inp;
		}
		else error(1, "%-.*s: undefined control", p - inp, inp);
		p = eatline(p, extra);
	}
}

BUCKET
stsym(s)
register char	*s;
{
	register char	*p;
	char		buf[MAXBUF];

	/*
	 * make definition look exactly like end of #define line
	 * copy to avoid running off end of world when param list is at end
	 */

	p = buf + inppsym;
	while (*p++ = *s++);
	p = buf + inppsym;

	/*
	 * skip the first identifier
	 */

	while (isid(*p) || *p == '(' || *p == ')') p++;
	if (*p == '=')
	{
		*p++ = ' '; 
		while (*p++);
	}
	else
	{
		s = " 1";
		while (*p++ = *s++);
	}
	pend = p;
	*--p = '\n';
	sloscan();
	(void)dodef(buf + inppsym);
	return(symtab->lastbucket);
}

/*
 * define an internal symbol that will not expand in the input text
 */

BUCKET
ppsym(s)
char	*s;
{
	register BUCKET	sp;

	/*
	 * inppsym prepends SALT onto s
	 */

	inppsym = 1;
	sp = stsym(s);
	inppsym = 0;
#if SCAN
	*sp->value = 1;
#endif
	return(sp);
}

/*VARARGS2*/
error(lev, s, a1, a2, a3, a4)
char	*s;
{
#if DEBUG
	if (lev < debug) return;
	if (lev < 0)
	{
		if (debug <  - 1) fprintf(stderr, "(debug %d) ", -lev);
		else fprintf(stderr, "(debug) ");
	}
#endif
	if (*infile->name) fprintf(stderr, "%s: ", infile->name);
	fprintf(stderr, "%d: ", infile->line);
	if (lev == 1) fprintf(stderr, "warning: ");
	fprintf(stderr, s, a1, a2, a3, a4);
	fprintf(stderr, "\n");
	if (lev > 1 && errors < CLASSCODE - 1) errors++;
	if (lev > 2) cleanup();
}

yyerror(s)
char	*s;
{
	error(2, "%s in %s expression", s, control.if_->name);
}

BUCKET
lookup(namep, enterf)
char	*namep;
int	enterf;
{
	register char			*np;
	register int			i;
	register BUCKET			sp;
	static struct hashbucket	null;

	/*
	 * namep had better not be too long
	 */

	if (gethash(symtab, namep) != NOTFOUND)
	{
		sp = symtab->lastbucket;
		if (enterf == REMOVE) sp->value = DEFAULT;
#if SCAN
		else if (scan && sp->value && !*sp->value)
		{
			char		*p;
			struct fileinfo	*f;

			np = (char*)&f;
			p = sp->value;
			for (i = 0; i < sizeof(struct fileinfo*); i++)
				*np++ = *++p;
			if (f->done)
			{
				if (f->parameter)
				{
					np = sp->value - 1;
					i = *np;
					*np = '\0';
					while (*--np);
					scaninfo("reference", f->name, sp->name, ++np);
					*(sp->value - 1) = i;
					f->used = 1;
				}
				*sp->value = 1;
			}
		}
#endif
	}
	else if (enterf & ENTER)
	{
		(void)puthash(symtab, (char*)0, DEFAULT);
		sp = symtab->lastbucket;
		if (!(enterf & SPECIAL))
		{
			/*
			 * update the superimposed code(s)
			 */

			np = namep;
			setcode1(*np++, 0);
			if (*np)
			{
			 setcode1(*np++, 1);
			 if (*np)
			 {
			  setcode1(*np++, 2);
			  if (*np)
			  {
			   setcode1(*np++, 3);
			   if (*np)
			   {
			    setcode1(*np++, 4);
			    if (*np)
			    {
			     setcode1(*np++, 5);
			     if (*np)
			     {
			      setcode1(*np++, 6);
			      if (*np) setcode1(*np, 7);
			     }
			    }
			   }
			  }
			 }
			}
		}
	}
	else
	{
#if MATCH_EXTRA
		if (enterf == DEFINED)
		{
			sp = lookup(namep, ENTER);
#if SCAN
			if (scan) scaninfo("reference", "-", namep, "");
#endif
		}
		else
#else
#if SCAN
		if (enterf == DEFINED && scan)
		{
			sp = lookup(namep, ENTER);
			scaninfo("reference", "-", namep, "");
		}
		else
#endif
#endif
		sp = &null;
	}
	return(sp);
}

BUCKET
slookup(p1, p2, enterf)
register char	*p1, *p2;
int		enterf;
{
	register char	*p3;
	char		c2, c3;
	BUCKET		np;

	/*
	 * mark end of token and truncate to maxsym chars or less
	 */

	c2 = *p2;
	*p2 ='\0';
	if ((p2 - p1) > maxsym) p3 = p1 + maxsym;
	else p3 = p2;
	c3 = *p3;
	*p3 ='\0';
	np = lookup(p1, enterf);
	*p3 = c3;
	*p2 = c2;
	if (np->value && !skip) newp = subst(p2, np);
	else newp = 0;
	return(np);
}

static char	*prednam;	/* in - predicate name, out - assertion	*/
static int	predlen;	/* in - predicate name length		*/

/*
 * check for first (in symbol table) assertion of predicate
 */

static int
predass(s, sp)
register char	*s;
BUCKET		sp;
{
	if (!strncmp(s, prednam, predlen))
	{
		prednam = s;
		return(-1);
	}
	return(0);
}

#define MAXRECUR	2000		/* deepest recursion level	*/

char*
subst(p, sp)
register char	*p;
BUCKET		sp;
{
	register char	*ca, *vp;
	int		params;
	char		*actual[MAXFRM]; /* actual[n-1] is text of nth actual */
	char		acttxt[MAXBUF];	/* space for actuals */

	if (!(vp = sp->value) || (*(vp - 1) & DISABLE)) return(p);
	if ((p - macro.decrease) <= macro.dam)
	{
		if (++macro.level > MAXRECUR)
		{
			error(2, "%s: macro recursion", sp->name);
			return(p);
		}
	}
	else macro.level = 0;	/* level decreased */
	macro.decrease = p;	/* new target for decrease in level */
	macro.dam = 0;
	macro.name = sp->name;
	crossinfo("R", macro.name, infile->line);
	dump();
	if (params = (*--vp & FORMALS))
	{
		register char	**pa;

		/*
		 * definition calls for parameters
		 */

		ca = acttxt;
		pa = actual;
		if (params > 1) params--;
		sloscan();

		/*
		 * no expansion during search for actuals
		 */

		skip++;
		macro.pcount = 0;
		macro.line = infile->line;
		do p = skipbl(p); while (*inp == '\n');	/* skip \n too */
		if (*inp == '(')
		{
			for (macro.pcount = 1; macro.pcount;)
			{
				*ca++ = '\0';
				for (;;)
				{
					outp = inp = p;
					p = cotoken(p);
					if (*inp == '(') macro.pcount++;
					if (*inp == ')' && --macro.pcount == 0)
					{
						params--;
						break;
					}
					if (macro.pcount == 1 && *inp == ',')
					{
						params--;
						break;
					}
					while (inp < p)
					{
						/*
						 *  toss newlines in arguments
						 *  to macros - keep problems
						 *  to a minimum.
						 *  if a backslash is just
						 *  before the newline, assume
						 *  it is in a string and
						 *  leave it in.
						 */

						if (*inp == '\n' && *(inp - 1) != '\\')
							*inp = ' ';
						if (*(ca - 1) || !isblank(*inp))
							*ca++ = *inp++;
						else inp++;
					}
					if (ca > &acttxt[MAXBUF])
						error(2, "%s: actuals too long", sp->name);
				}
				if (pa >= &actual[MAXFRM]) error(1, "%s: too many actuals", sp->name);
				else *pa++ = ca;
			}
		}
		if (macro.line != infile->line)
		{
			/*
			 * embedded newline in macro call
			 */

			defnum(infile->line, int);
			defput('N');
			defput(WARN);
		}
		if (params) error(1, "%s: not enough actuals", sp->name);

		/*
		 * missing actuals are set to null string
		 */

		while (--params >= 0) *pa++ = "" + 1;
		
		/*
		 * check for special macros
		 */

		if (sp == special.dynamic)
		{
			long		clock;
			extern char	*ctime();

			vp = ca;
			*vp++ = '\0';
			for (ca = actual[0]; *(ca - 1); ca--);

			/*
			 * check for assertion with ca as predicate
			 */

			prednam = ca;
			predlen = strlen(ca);
			exhash(symtab, predass);

			/*
			 * in order of expected appearance
			 */

			if (prednam != ca)
			{
				vp = acttxt;
				*vp++ = '"';
				(void)strcpy(vp, prednam + predlen + 1);
				*(vp + strlen(vp) - 1) = '"';
			}
			else if (!strcmp(ca, "LINE"))
				(void)sprintf(vp, "%d", infile->line);
			else if (!strcmp(ca, "FILE"))
				(void)sprintf(vp, "\"%s\"", infile->name);
			else if (!strcmp(ca, "DATE"))
			{
				(void)time(&clock);
				vp = ctime(&clock) + 3;
				*vp++ = '\0';
				*(vp + 20) = '\0';
				(void)strcpy(vp + 7, vp + 16);
			}
			else if (!strcmp(ca, "TIME"))
			{
				(void)time(&clock);
				vp = ctime(&clock) + 10;
				*vp++ = '\0';
				*(vp + 8) = '\0';
			}
			else
			{
				error(1, "%s(%s): not defined", sp->name, ca);
				vp = "\"\"";
			}
			while (*vp++);
			vp--;
		}
		skip--;
		fasscan();
	}
	else if (inif)
	{
		if (*p == '(') return(0);
	}
	else if (!isslo && (*(sp->value - 1) & PREDEF) && *sp->name != '_')
		error(1, "predefined symbol \"%s\" referenced outside of %s", sp->name, control.if_->name);

#if UNDEF_MACRO
	/*
	 * disable macro so it is not expanded in its definition
	 */

	defnum(sp->value, char*);
	defput('D');
	defput(WARN);
#endif

	/*
	 * push definition onto front of input stack
	 */

	for (;;)
	{
		while (!iswarn(*--vp)) defput(*vp);
		if (*vp-- == WARN)
		{
			if (*vp == 'A')
			{
				/*
				 * insert actual parameter
				 */

#if UNDEF_MACRO
				defnum(sp->value, char*);
				defput('U');
				defput(WARN);
#endif
				ca = actual[*--vp - 1];
				while (*--ca) defput(*ca);
#if UNDEF_MACRO
				defnum(sp->value, char*);
				defput('D');
				defput(WARN);
#endif
			}
			else
			{
				/*
				 * pass it along
				 */

				defput(*vp);
				defput(WARN);
			}
		}
		else break;
	}
#if UNDEF_MACRO
	defnum(sp->value, char*);
	defput('U');
	defput(WARN);
#endif
	return(outp = inp = p);
}

char*
trmdir(s)
register char	*s;
{
	register char	*p = s;

	while (*p++);
	p--;
	while (p > s && *--p != '/');
#if unix
	if (p == s) *p++ = '.';
#endif
	*p = '\0';
	return(s);
}

yywrap()
{
	return(1);
}

main(argc, argv)
int	argc;
char	*argv[];
{
	register int	i;
	register char	*p, *s;
	struct definfo	*def, *pdefine, *pundef;
	char		*tf;

	pdefine = pundef = (struct definfo*)0;
	infile->name = "";
	dirs->name = ".";
	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-') switch(argv[i][1])
		{
		case 'C':
			comment.pass++;
			break;
		case 'D':
			if (*(argv[i] + 2))
			{
				def = allocate(definfo);
				def->def = argv[i] + 2;
				def->next = pdefine;
				pdefine = def;
			}
			break;
		case 'E':
			break;
#if CROSSREF
		case 'F':
			if (!*(argv[i] + 2)) error(3, "file name omitted for -F option");
			else if (!(xout = fopen(argv[i] + 2, "w")))
				error(3, "cannot create %s\n", argv[i] + 2);
			break;
#endif
		case 'H':
			error(1, "-H option not implemented -- try -S");
			break;
		case 'I':
			if (*(argv[i] + 2) && strcmp(argv[i] + 2, "-"))
			{
				lastdir = lastdir->next = allocate(dirinfo);
				lastdir->name = argv[i] + 2;
			}
			else ignoresrc++;
			break;
		case 'N':
			if (*(argv[i] + 2))
			{
				infile->name = copy(argv[i] + 2);
				crossfile(infile->name);
				dirs->name = trmdir(argv[i] + 2);
			}
			break;
		case 'P':
			pflag++;
			break;
#if SCAN
		case 'S':
			scan++;
			break;
#endif
		case 'T':
			maxsym = SYMNMLEN;/* backward name compatabilty */
			break;
		case 'U':
			if (*(argv[i] + 2))
			{
				def = allocate(definfo);
				def->def = argv[i] + 2;
				def->next = pundef;
				pundef = def;
			}
			break;
		case 'V':
			fprintf(stderr, "%s\n", version);
			break;
		case 'X':
			text = 0;
			break;
		case 'Y':
			defdir = argv[i] + 2;
			break;
#if DEBUG
		case 'd':
			debug--;
			break;
#endif
		case '\0':
			break;
		default: 
			error(1, "unknown option %s", argv[i]);
			break;
		}
		else if (fin == 0)
		{
			if ((fin = open(argv[i], 0)) < 0)
				error(3, "no source file %s", argv[i]);
			close(0);
			infile->name = copy(argv[i]);
			crossfile(infile->name);
			dirs->name = trmdir(argv[i]);
		}
		else if (fout == 1)
		{
			if ((fout = creat(argv[i], 0644)) < 0)
				error(3, "cannot create %s", argv[i]);
			close(1);
		}
		else error(1, "extraneous name %s", argv[i]);
	}
	infile->fd = fin;
	errors = 0;

	/*
	 * after user -I dirs here are the standard include directories
	 */

#if ibm
	p = "BTL$CLIB";
#endif
#if unix
	if (defdir) p = defdir;
	else if (!(p = getenv("CPPINCLUDE")) || !*p) p = CPPINCLUDE;
#endif
	lastdir = lastdir->next = allocate(dirinfo);
	lastdir->name = p;
	lastdir->next = (struct dirinfo*)0;
#if CHANGE_DIR
	infile->dir = dirs->name;
#endif

	/*
	 * set up the hash tables
	 */
	
	symtab = mkhash(2048, HASH_ALLOCATE, (GENERIC)0, (GENERIC)0, NOTFOUND, "defines");
#if ONCE_INCLUDE
	filtab = mkhash(256, HASH_DATA, ihash, icompare, (GENERIC)0, "files");
#endif

	/*
	 * control keywords
	 */

	control.assert	= ppsym("assert");
	control.define	= ppsym("define");
	control.elif	= ppsym("elif");
	control.else_	= ppsym("else");
	control.endif	= ppsym("endif");
	control.if_	= ppsym("if");
	control.ifdef	= ppsym("ifdef");
	control.ifndef	= ppsym("ifndef");
	control.include	= ppsym("include");
	control.line	= ppsym("line");
	control.pragma	= ppsym("pragma");
	control.undef	= ppsym("undef");

	/*
	 * obsolete control keywords
	 */

	control.class	= ppsym("class");
	control.ident	= ppsym("ident");

	/*
	 * special macros
	 */

	special.dynamic	= stsym("ppsymbol(sym)");
#if SCAN
	if (scan) *special.dynamic->value = 1;
#endif
	init = 1;

#if !DEFAULT_INCLUDE
#if unix
	(void)stsym("unix");
#endif
#if ibm
	(void)stsym("ibm");
#endif
#if interdata
	(void)stsym("interdata");
#endif
#if pdp11
	(void)stsym("pdp11");
#endif
#if vax
	(void)stsym("vax");
#endif
#if u370
	(void)stsym("u370");
#endif
#if u3b
	(void)stsym("u3b");
#endif
#if u3b5
	(void)stsym("u3b5");
#endif
#if tss
	(void)stsym("tss");
#endif
#if os
	(void)stsym("os");
#endif
#if mert
	(void)stsym("mert");
#endif
#if RT
	(void)stsym("RT");
#endif
#if RES
	(void)stsym("RES");
#endif
#endif

	infile->line = 1;
	lineinfo();
	tf = infile->name;
#if ONCE_INCLUDE
	/*
	 * enter the input file into file id table
	 */

	infile->info = chkinc(fin, 0);
#endif

#if DEFAULT_INCLUDE
	pbeg = buffer + maxsym;
	pbuf = pbeg + MAXBUF;
	pend = pbuf + MAXBUF;
	iflev = 0;
	ifstack[iflev] = 0;
	skip = 0;
	crossready(1);
	infile->line = 0;
	p = pbuf;
	s = "#include <";
	while (*p = *s++) p++;
	s = CPPDEFAULT;
	while (*p = *s++) p++;
	s = ">\n";
	while (*p = *s++) p++;
	outp = inp = pbuf;
	pend = p;
	if (!setjmp(initenv)) (void)ppcontrol(pbuf);
	crossready(0);
#endif
	init = 0;
	infile->name = "command line";
	infile->line = 1;
	while (pdefine)
	{
		(void)stsym(pdefine->def);
		pdefine = pdefine->next;
	}
	while (pundef)
	{
		for (p = pundef->def; *p; p++)
			if (*p == '=')
			{
				*p = '\0';
				break;
			}
		/*
		 * truncate to maxsym characters if needed
		 */

		if (strlen(pundef->def) > maxsym)
			(pundef->def)[maxsym] = '\0';
		(void)lookup(pundef->def, REMOVE);
		pundef = pundef->next;
	}

	infile->name = tf;
	infile->line = 1;

	pbeg = buffer + maxsym;
	pbuf = pbeg + MAXBUF;
	pend = pbuf + MAXBUF;

	iflev = 0;
	ifstack[iflev] = 0;
	skip = 0;
	outp = inp = pend;
	crossready(1);
	state = NEWLINE;
	(void)ppcontrol(pend);
	cleanup();
}
 
#if CROSSREF
char*
xcopy(ptr1, ptr2)
register char	*ptr1, *ptr2;
{
	static char	name[MAXSYM+1];
	char		*saveptr, ch;
	register char	*ptr3 = name;

	/*
	 * locate end of name; save character there
	 */

	if ((ptr2 - ptr1) > maxsym)
	{
		saveptr = ptr1 + maxsym;
		ch = *saveptr;
		*saveptr = '\0';
	}
	else
	{
		ch = *ptr2;
		*ptr2 = '\0';
		saveptr = ptr2;
	}
	while (*ptr3++ = *ptr1++);	/* copy name */
	*saveptr = ch;	/* replace character */
	return(name);
}
#endif

#if SCAN

/*
 * check for unused parameter files
 */

/*ARGSUSED*/
int
chkuse(id, f)
struct fileid			*id;
register struct fileinfo	*f;
{
	if (f->parameter && !f->used
#if DEFAULT_INCLUDE
			&& !f->init
#endif
			)
		scaninfo("unused", f->name, "", "");
	return(0);
}
#endif

/*
 * cleanup actions
 */

cleanup()
{
	static int	incleanup = 0;

	if (incleanup++) return;
	outflush();
#if SCAN
	if (scan) exhash(filtab, chkuse);
#endif
#if DEBUG
	if (debug < 0)
	{
		register int	i, j, k;

		dumphash((TABLE)0);
		error(0, "lookups=%d found=%d code1=%d", stats.lookups, stats.found, stats.code1);
		error(0, "break = %d", sbrk(0));
		for (i = k = 0; i < ALFSIZ; i++)
			for (j = 0; j < 8; j++)
				if (tstcode1(i, j)) k++;
		error(0, "%d code1 bits set", k);
	}
#endif
	exit(errors ? (errors == CLASSCODE ? CLASSCODE : 2) : 0);
}

/*
 * evaluate an if expression
 */

int
eval()
{
	int		i;
	unsigned long	oskip;
	oskip = skip;
	skip = 0;
	inif = 1;
	i = yyparse();
#if DEBUG
	error(-3, "yyparse(): %s", i ? "true" : "false");
#endif
	inif = 0;
	skip = oskip;
	return(i);
}
