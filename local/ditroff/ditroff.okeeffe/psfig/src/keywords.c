/***	
 ***	keywords.c --
 ***	
 ***	Keyword recognition function for psfig.
 ***	
 ***	N.Batchelder, 3/8/86.
 ***/

# include "psfig.h"
# include "item.h"

static struct keypair {
	char		*name;
	enum item	itype;
} keytable[] = {
	"figure",	iFigure,
	"space",	iSpace,
	"delim",	iDelim,
	"define",	iDefine,
	"literal",	iLiteral,
	"file",		iFile,
	"width",	iWidth,
	"height",	iHeight,
	"reserve", 	iReserve,
	"clip",		iClip,
	"box",		iBox,
	"level",	iLevel,
	"bounds",	iBounds,
	"global",	iGlobal,
	"safe",		iSafe,
	NULL,		iEndOfInput,
};

/* 
 * isKeyword:
 * 
 * Takes the text of an item and returns whether or not it is a keyword.
 * If it is, then it fills in the exact item type in the pointed to enum item.
 */

int
isKeyword(buf, iptr)
char		*buf;
enum item	*iptr;
{
	struct keypair	*keyp;

	for (keyp = keytable; keyp->name; keyp++) {
		if (!strcmp(buf, keyp->name)) {
			/* 
			 * A match!
			 */
			
			*iptr = keyp->itype;
			return 1;
		}
	}

	return 0;
}

/* end of keywords.c */

