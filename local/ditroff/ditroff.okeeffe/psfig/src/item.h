/***	
 ***	item.h --
 ***	
 ***	Definitions for the item stuff for psfig.
 ***	
 ***	N.Batchelder, 3/8/86.
 ***/

/* 
 * These are the different types of items we can return.
 */

enum item {
	iEndOfInput,
	iSeparator,
	iLeftBrace,
	iRightBrace,
	iFile,
	iFigure,
	iSpace,
	iDelim,
	iDefine,
	iLiteral,
	iWidth,
	iHeight,
	iReserve,
	iClip,
	iBox,
	iLevel,
	iBounds,
	iGlobal,
	iSafe,
	iWord,
};

/* 
 * These are the characters that we recognize as special.
 */

# define Quotes		"\"'"
# define SelfDelim	"{};"
# define Sep		';'
# define LBrace		'{'
# define RBrace		'}'

enum item	getItem();

/* end of item.h */
