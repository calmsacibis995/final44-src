/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"
#include "windows.h"

/*
 *	cflush (buf,n,blength)
 *
 *		put n-mcol characters starting at buf+mcol on the
 *			screen at current mline,mcol.  This is
 *			assumed not to overflow one line.
 *			Has a lot of help from wxputl.c.
 *
 *	wcflush() - exactly like cflush in vt.d but with blength
 *
 */

cflush (cp, n)
{
	wcflush (cp, n, n);
}

wcflush (cp, n, blength)
register CHAR  *cp;
int     n;
int blength;
{
	register CHAR  *mp;
	register int    x;
	register int    y;
	int     jnk;
	int	over_lap;

	mp = cmap[mline];
	jnk = scrjnk[mline];
	if (jnk <= SCRWID)
		mp[jnk] = 0;

	if (blength >= DLOOK)
	{
		for (y = mcol, x = jnk; x >= y; x--)
		{
			if ((mp[x] != ' ') &&
				(mp[x] != 0))
			{
				break;
			}
		}
		for (over_lap = x; x >= y; x--)
		{
			if (mp[x] != cp[x])
			{
				over_lap = x;
				break;
			}
		}
	}

	cp[n] = EOM;			/* Mark end of line */
	cp += mcol;

	while (*cp != EOM)
	{
		if (mcol >= jnk)
		{
			while (mcol > jnk)
			{
				if (IN)
					mp[jnk++] = 0;
				else
					mp[jnk++] = ' ';
			}
			mp[jnk++] = 0;
		}

		if (*cp == mp[mcol])
		{
			cp++;
			mcol++;
			continue;
		}

		if ((*cp == ' ') && (mp[mcol] == 0))
		{
			if (!IN)
				mp[mcol] = ' ';

			cp++;
			mcol++;
			continue;
		}

/*
 *	Character was not there, we must do some work here!
 *
 */
		if ((mcol != scrcol) || (mline != scrlin))
			sgo (mline, mcol);

		if (blength < DLOOK)
			goto NOINS;

		if (DELC)
		{
			if(mp[mcol] == 0)
				goto NOINS;

			if ((*cp & VT_VIDEO) ||
				(mp[mcol] & VT_VIDEO))
					goto NOINS;

			for (x = 1; x < DLOOK; x++)
			{
				y = x + mcol + lDELC;
				if ((y >= jnk) ||
					(y > over_lap))
					goto NODEL;
				if (cp[x] & VT_VIDEO)
					goto NODEL;
				if(mp[x + mcol] == 0)
					goto NODEL;

				if (*cp == mp[x + mcol])
				{
					for (y = 1; y < lDELC; y++)
					{
						if (cp[y] != mp[x + y + mcol])
							goto NODEL;
					}
/*
 *	Delete x characters from under the cursor
 *
 */
					vputch (0);
					SREGION = SCRWID - mcol;
					if (DELMODE && (osert == 0))
					{
						eprintf (INSERTM);
						osert++;
					}
					while (x--)
					{

						eprintf (DELC);
						jnk = lshift (scrlin, mcol, jnk - 1);
						if (over_lap >= mcol)
							over_lap--;
					}
					mcol += lDELC;
					cp += lDELC;
					scrjnk[scrlin] = jnk;
					goto donec;
				}
			}
			goto NODEL;
		}
		else
		{

/*
 *	Now see if insertion will help.
 *
 */

	NODEL: 
			if ((INSERTC || INSERTM) &&
					(jnk > mcol + lINSC))
			{
				if ((*cp & VT_VIDEO) ||
					(mp[mcol] & VT_VIDEO))
						goto NOINS;

				if ((jnk + lINSC) > (SCRWID + 1))
		   			goto NOINS;

				for (x = 1; x < ILOOK; x++)
				{
					if (cp[x] & VT_VIDEO)
						goto NOINS;

					y = x + mcol + lINSC;
					if ((y >= jnk) ||
						(y > over_lap))
						goto NOINS;

					if (cp[x] == mp[mcol])
					{
						for (y = 1; y < lINSC; y++)
						{
							if (cp[x + y] != mp[y + mcol])
								goto NOINS;
						}

						vputch (0);
						SREGION = jnk - mcol;
						mcol += x;
						if ((osert == 0) && INSERTM)
						{
							eprintf (INSERTM);
							osert++;
						}
						while (x--)
						{
							if (INSERTC)
								eprintf (INSERTC);

							vputch (*cp);

							if (INSERTP)
								eprintf (INSERTP);

							scrjnk[scrlin] = jnk;
							jnk = rshift (scrlin, scrcol + 1, mp[scrcol]);
							mp[scrcol++] = *cp++;
							if (over_lap >= mcol)
								over_lap++;
						}
						mcol += lINSC;
						cp += lINSC;
						goto donec;
					}
				}
			}
		}

NOINS:
 		if (osert)
			unsert ();

		if (((EOVER == FALSE) &&
		     (TUNDER) &&
		     (((*cp & VT_CHAR) == '_') &&
		      (*cp != mp[mcol]))) ||
		    ((NESTANDOUT) &&
		     (mp[mcol] & VT_VIDEO) &&
		     ((mp[mcol] & VT_VIDEO) != (*cp & VT_VIDEO))))
		{
			vputch (0);
			eprintf (CLINE);
			mp[mcol] = 0;
			while (*cp != EOM)
			{
				if (*cp == ' ')
				{
					cp++;
					mp[mcol++] = ' ';
					continue;
				}
				if ((mcol != scrcol) || (mline != scrlin))
					sgo (mline, mcol);
				vputch(*cp);
				mp[scrcol++] = *cp;
				cp++;
				mcol++;
			}

			blength = mcol;
			while (blength < jnk)
			{
				if (mp[blength] == ' ')
				{
					blength++;
					continue;
				}
				if ((blength != scrcol) || (mline != scrlin))
					sgo (mline, blength);
				vputch(mp[scrcol++]);
				blength++;
			}

			jnk = scrcol;
			blength = 0;
			scrjnk[mline] = jnk;
			goto donec;
		}
		else
		{
			if ((TUNDER) &&
			    (EOVER) &&
			    ((*cp & VT_CHAR) == '_') &&
			    (mp[mcol]) &&
			    (mp[mcol] != ' '))
			{
				putchar (' ');
				putchar ('\010');
				vputch (*cp);
			}
			else
				vputch (*cp);
		}

		mp[scrcol++] = *cp;
		cp++;
		mcol++;
donec:
 		continue;
	}

	if ((blength >= DLOOK) && 
		((mcol < jnk) || (scrjnk[mline] > jnk)))
	{
		blength = mcol;
		while (blength < jnk)
		{
			if ((mp[blength]) &&
				(mp[blength] != ' '))
			{
				clrl ();
				break;
			}
			blength++;
		}
		scrjnk[mline] = mcol;
	}
	else
	{
		scrjnk[mline] = jnk;
	}

	if ((scrcol > SCRWID) && SCRWRAP)
	{
		scrlin++;
		scrcol = 0;
	}
}
