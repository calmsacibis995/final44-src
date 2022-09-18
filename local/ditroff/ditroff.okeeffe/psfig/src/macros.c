/***	
 ***	macros.c --
 ***	
 ***	The macro handling stuff for psfig.
 ***	
 ***	N.Batchelder, 3/8/86.
 ***/

# include "psfig.h"

# define MaxMacros	100

/* 
 * Our table of macros. The end is marked by a pointer (macp). Entries may
 * have NULL for their name (if they have been deleted).
 */

struct mac {
	char	*name;
	char	*value;
};

static struct mac	macros[MaxMacros];
static struct mac	*macp = macros;

/* 
 * isMacro:
 * 
 * Look up a name. If it is a macro, point to the value through an argument,
 * and return 1. If it isn't, return 0.
 */

int
isMacro(nm, valp)
char	*nm;
char	**valp;
{
	struct mac	*mp;

	for (mp = macros; mp < macp; mp++) {
		if (!strcmp(nm, mp->name)) {
			*valp = mp->value;
			return 1;
		}
	}

	return 0;
}

/* 
 * addMacro:
 * 
 * Takes a name and a value and enters into the table.
 */

addMacro(n, v)
char	*n;
char	*v;
{
	char		*strsave();
	struct mac	*mp;

	if (macp >= macros+MaxMacros) {
		/* 
		 * Table is full. Attempt to compact it.
		 */
		
		for (mp = macros; mp < macp; mp++) {
			if (mp->name == NULL) {
				mp->name = --macp->name;
				mp->value = macp->value;
			}
		}

		if (macp >= macros+MaxMacros) {
			error("macro table overflow");
		}
	}

	macp->name = strsave(n);
	macp->value = strsave(v);
	macp++;
}

/* 
 * deleteMacro:
 * 
 * Removes the given name from the table.
 */

deleteMacro(nm)
char	*nm;
{
	struct mac	*mp;

	for (mp = macros; mp < macp; mp++) {
		if (!strcmp(nm, mp->name)) {
			mp->name = NULL;
		}
	}
}

/* 
 * strsave:
 * 
 * Stashes its argument away somewhere and returns a new pointer to it.
 */

# define NSAVETAB	4096

static char	*savetab;
static int	saveleft;

char *
strsave(cp)
register char *cp;
{
	register int len;

	len = strlen(cp) + 1;
	if (len > saveleft) {
		saveleft = NSAVETAB;
		if (len > saveleft)
			saveleft = len;
		savetab = malloc((unsigned) saveleft);
		if (savetab == 0) {
			error("no more string memory");
		}
	}
	(void) strncpy(savetab, cp, len);
	cp = savetab;
	savetab += len;
	saveleft -= len;

	return cp;
}

/* end of macros.c */
