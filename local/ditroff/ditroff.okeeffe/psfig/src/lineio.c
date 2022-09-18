/***	
 ***	lineio.c --
 ***	
 ***	Low level i/o for psfig.
 ***	Provides the capability to get and unget lines.
 ***	
 ***	N.Batchelder, 3/8/86.
 ***/

# include <stdio.h>
# include "psfig.h"

/* 
 * This is non-NULL if a line was pushed back.
 */

static char	*ungotten = NULL;

/* 
 * getline:
 * 
 * A lot like fgets, but will return the last line ungotten by ungetline if
 * there is one.
 */

char *
getline(buf, len, file)
char	*buf;
int	len;
FILE	*file;
{
	if (ungotten) {
		(void) strcpy(buf, ungotten);
		ungotten = NULL;
		return buf;
	}

	linenumber++;
	return fgets(buf, len, file);
}

/* 
 * ungetline:
 * 
 * Takes the pointer passed to it and saves it to be returned by getline next
 * time.
 */

ungetline(buf)
char	*buf;
{
	if (ungotten) {
		error("Double ungetline!");
	}
	ungotten = buf;
}

/* end of lineio.c */
