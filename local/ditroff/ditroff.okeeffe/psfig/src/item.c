/***	
 ***	item.c --
 ***	
 ***	The item reading abstraction for psfig
 ***	
 ***	N.Batchelder, 3/8/86.
 ***/

# include "item.h"
# include "psfig.h"

# define elif		else if
# define isWhite(c)	((c) == ' ' || (c) == '\t' || (c) == '\n')

static int	endofinput = 0;		/* Have we hit the end? */
static char	cbuf[1000];		/* Where we do all processing */
static char	*cp;			/* Our position in cbuf */
static char	*(*getmore)();		/* Our gimme gimme function */

# define StartOffset	700	/* Where in cbuf to start filling. */

/* 
 * getCh:
 * 
 * Read a character from our input. Returns 0 when no more.
 */

static
char
getCh()
{
	while (!endofinput) {
		if (*cp) {
			return *cp++;
		}

		if (!getmore) {
			endofinput++;
		} elif ((*getmore)(cp = cbuf + StartOffset) == NULL) {
			endofinput++;
		}
	}

	return 0;
}

/* 
 * pushBackCh:
 * 
 * Takes a character and pushes it back. Just like ungetc.
 */

static
pushBackCh(ch)
char	ch;
{
	*--cp = ch;
	endofinput = 0;
}

/* 
 * pushBackStr:
 * 
 * Takes a string and pushes it back into our input so that it will be read
 * next time.
 */

static
pushBackStr(str)
char	*str;
{
	register char	*sp;

	/* 
	 * Find the end of the string.
	 */
	
	for (sp = str; *sp; sp++)
		;

	/* 
	 * Now write it into the buffer backwards from the current point.
	 */
	
	while (--sp >= str) {
		*--cp = *sp;
	}

	if (cp < cbuf) {
		error("pushback overflow");
	}

	if (strlen(str)) {
		endofinput = 0;
	}
}

/* 
 * setInput:
 * 
 * Takes a string and a function, and installs them as the current working
 * text and the function to call to get more when that's used up.
 */

void
setInput(str, morefn)
char	*str;
char	*(*morefn)();
{
	endofinput = 0;
	(void) strcpy(cbuf+StartOffset, str);
	cp = cbuf+StartOffset;
	getmore = morefn;
}

/* 
 * getItem:
 * 
 * Reads the next item (token) from the input and copies it to the buffer
 * provided to it. The return value is the type of the item (enum item).
 */

static char		lastitem[SMBUFSZ];
static enum item	lasttype;
static int		pusheditem = 0;

enum item
getItem(ibuf)
char	*ibuf;
{
	char		ch;		/* Our latest character from getCh */
	char		quote = 0;	/* Our current quote char, if any */
	char		*bp = ibuf;	/* Fills up ibuf */
	enum item	itype;		/* What we eventually return */
	char		*value;		/* The value of a possible macro */

	if (pusheditem) {
		(void) strcpy(ibuf, lastitem);
		pusheditem = 0;
		return lasttype;
	}
		
	/* 
	 * First skip whitespace.
	 */

	while ((ch = getCh()) && isWhite(ch))
		;

	if (ch == 0) {
		return lasttype = iEndOfInput;
	}

	/* 
	 * Do we have a quote character in hand?
	 */

	if (index(Quotes, ch)) {
		quote = ch;
		if (!(ch = getCh())) {
			return lasttype = iEndOfInput;
		}
	}

	/* 
	 * Loop around building up the item.
	 */

	for (;;) {
		if (quote) {
			if (ch == quote) {
				break;
			}
		} elif (isWhite(ch)) {
			pushBackCh(ch);
			break;
		} elif (index(SelfDelim, ch)) {
			break;
		}

		*bp++ = ch;

		if (!(ch = getCh())) {
			break;
		}

		if (bp - ibuf > SMBUFSZ) {
			error("word overflow");
		}
	}
	*bp = '\0';

	if (index(SelfDelim, ch)) {
		if (bp == ibuf) {
			/* It was the first character read */
			switch (ch) {
			case Sep:
				return lasttype = iSeparator;
			case LBrace:
				return lasttype = iLeftBrace;
			case RBrace:
				return lasttype = iRightBrace;
			}
		} else {
			/* It terminated the item */
			pushBackCh(ch);
		}
	}

	/* 
	 * If the thing was quoted, then it is simply a generic word.
	 */
	
	if (quote) {
		return iWord;
	}
	
	/* 
	 * Now we have a word in ibuf. We must check to see if it is a
	 * keyword.
	 */

	if (isKeyword(ibuf, &itype)) {
		return lasttype = itype;
	}

	/* 
	 * Is it a macro?
	 */

	if (isMacro(ibuf, &value)) {
		pushBackStr(value);
		return getItem(ibuf);
	}

	/* 
	 * I guess it was just a generic word after all.
	 */

	return lasttype = iWord;
}

/* 
 * unGetItem:
 * 
 * Takes the text of the last item and causes it to be returned next time.
 */

unGetItem(ibuf)
char	*ibuf;
{
	pusheditem++;
	(void) strcpy(lastitem, ibuf);
}

/* 
 * getString:
 * 
 * Reads a self-delimited string from the input, and returns it in the buffer
 * provided. Self-delimited means that the first non-white character is taken
 * to be the delimiter. No macro expansion is done, and quotes are like
 * anything else.
 * Returns 1 or 0 depending on whether there was a string or not. (A separator
 * or end of input can mean no string).
 */

int
getString(sbuf, len)
char	*sbuf;
int	len;
{
	char	ch;		/* Our latest character from getCh */
	char	delim;		/* This string's delimiter */
	char	*bp = sbuf;	/* Fills up `sbuf' */

	/* 
	 * Skip whitespace.
	 */

	while ((ch = getCh()) && isWhite(ch))
		;

	if (ch == 0 || ch == Sep) {
		return 0;
	}

	delim = ch;

	do {
		ch = getCh();
	} while ((ch != delim) && (bp < sbuf + len) && (*bp++ = ch));

	if (bp == sbuf + len) error("buffer overflow");

	*bp = '\0';
	return 1;
}
	
/* end of item.c */
