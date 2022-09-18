/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*	%W%	*/
/*
 *	UNIX shell
 *
 *	Bell Telephone Laboratories
 *
 *	This is the wild carding routine from the 6.0 shell.
 *	The '?' chars in this file have been changed to the '%'
 *	char for use with Tabs.  The function addg() was
 *	changed from a static int to an int so that it can be
 *	accessed from cmfile().  These two changes are the
 *	ONLY changes made to the original source. - CDB
 *	
 */

#define ONE_CHAR	'%'
#define STATIC_INT	int

#include	"defs.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/dir.h>

#define 	MAXDIR	64
struct direct	dirbuf[MAXDIR];
int		nxtdir = -1;
int		maxdir = 0;
char		entry[DIRSIZ+1];
char 		*getdir();

/*
 * globals (file name generation)
 *
 * "*" in params matches r.e ".*"
 * "ONE_CHAR" in params matches r.e. "."
 * "[...]" in params matches character class
 * "[...a-z...]" in params matches a through z.
 *
 */
extern int	addg();


expand(as, rcnt)
	char	*as;
{
	int	count, dirf;
	BOOL	dir = 0;
	char	*rescan = 0;
	register char	*s, *cs;
	struct argnod	*schain = gchain;
	struct stat statb;
	BOOL	slash;

	if (trapnote & SIGSET)
		return(0);
	s = cs = as;
	entry[DIRSIZ] = 0;	/* to end the string */
	/*
	 * check for meta chars
	 */
	{
		register BOOL open;

		slash = 0;
		open = 0;
		do
		{
			switch (*cs++)
			{
			case 0:
				if (rcnt && slash)
					break;
				else
					return(0);

			case '/':
				slash++;
				open = 0;
				continue;

			case '[':
				open++;
				continue;

			case ']':
				if (open == 0)
					continue;

			case ONE_CHAR:
			case '*':
				if (rcnt > slash)
					continue;
				else
					cs--;
				break;


			default:
				continue;
			}
			break;
		} while (TRUE);
	}

	for (;;)
	{
		if (cs == s)
		{
			s = nullstr;
			break;
		}
		else if (*--cs == '/')
		{
			*cs = 0;
			if (s == cs)
				s = "/";
			break;
		}
	}

	if ((dirf = open(*s ? s : ".", 0)) > 0)
	{
		if (fstat(dirf, &statb) != -1 &&
		    (statb.st_mode & S_IFMT) == S_IFDIR)
			dir++;
		else
			close(dirf);
	}

	count = 0;
	if (*cs == 0)
		*cs++ = 0200;
	if (dir)		/* check for rescan */
	{
		register char *rs;
		char *e;

		rs = cs;
		do
		{
			if (*rs == '/')
			{
				rescan = rs;
				*rs = 0;
				gchain = 0;
			}
		} while (*rs++);

		while ((e = getdir(dirf)) && (trapnote & SIGSET) == 0)
		{
			if (e[0] == '.' && *cs != '.')
#ifndef BOURNE
				continue;
#else
			{
				if (e[1] == 0)
					continue;
				if (e[1] == '.' && e[2] == 0)
					continue;
			}
#endif

			if (gmatch(e, cs))
			{
				addg(s, e, rescan);
				count++;
			}
		}
		close(dirf);

		if (rescan)
		{
			register struct argnod	*rchain;

			rchain = gchain;
			gchain = schain;
			if (count)
			{
				count = 0;
				while (rchain)
				{
					count += expand(rchain->argval, slash + 1);
					rchain = rchain->argnxt;
				}
			}
			*rescan = '/';
		}
	}

	{
		register char	c;

		s = as;
		while (c = *s)
			*s++ = (c & STRIP ? c : '/');
	}
	return(count);
}

/*
 * read next directory entry
 * and ignore inode == 0
 *
 */

char *
getdir(dirf)
{
	for (;;)
	{
		if (++nxtdir == maxdir)
		{
			int r;

			r = read(dirf, dirbuf, sizeof(dirbuf)) / sizeof(struct direct);
			if (maxdir = r)
				nxtdir = 0;
			else
			{
				nxtdir = -1;
				return(0);
			}
		}

		/* nxtdir is next available entry */
		if (dirbuf[nxtdir].d_ino == 0)
			continue;


		strncpy(entry, dirbuf[nxtdir].d_name, DIRSIZ);
		return(entry);
	}
}


gmatch(s, p)
register char	*s, *p;
{
	register int	scc;
	char		c;

	if (scc = *s++)
	{
		if ((scc &= STRIP) == 0)
			scc=0200;
	}
	switch (c = *p++)
	{
	case '[':
		{
			BOOL ok;
			int lc;
			int notflag = 0;

			ok = 0;
			lc = 077777;
			if (*p == '!')
			{
				notflag = 1;
				p++;
			}
			while (c = *p++)
			{
				if (c == ']')
					return(ok ? gmatch(s, p) : 0);
				else if (c == MINUS)
				{
					if (notflag)
					{
						if (scc < lc || scc > *(p++))
							ok++;
						else
							return(0);
					}
					else
					{
						if (lc <= scc && scc <= (*p++))
							ok++;
					}
				}
				else
				{
					lc = c & STRIP;
					if (notflag)
					{
						if (scc && scc != lc)
							ok++;
						else
							return(0);
					}
					else
					{
						if (scc == lc)
							ok++;
					}
				}
			}
			return(0);
		}

	default:
		if ((c & STRIP) != scc)
			return(0);

	case ONE_CHAR:
		return(scc ? gmatch(s, p) : 0);

	case '*':
		while (*p == '*')
			p++;

		if (*p == 0)
			return(1);
		--s;
		while (*s)
		{
			if (gmatch(s++, p))
				return(1);
		}
		return(0);

	case 0:
		return(scc == 0);
	}
}

/* changed to global for use with cmfile - CDB
was:	static int
is:	int
*/
STATIC_INT
addg(as1, as2, as3)
char	*as1, *as2, *as3;
{
	register char	*s1, *s2;
	register int	c;

	s2 = locstak() + BYTESPERWORD;
	s1 = as1;
	while (c = *s1++)
	{
		if ((c &= STRIP) == 0)
		{
			*s2++ = '/';
			break;
		}
		*s2++ = c;
	}
	s1 = as2;
	while (*s2 = *s1++)
		s2++;
	if (s1 = as3)
	{
		*s2++ = '/';
		while (*s2++ = *++s1);
	}
	makearg(endstak(s2));
}

makearg(args)
	register struct argnod *args;
{
	args->argnxt = gchain;
	gchain = args;
}


