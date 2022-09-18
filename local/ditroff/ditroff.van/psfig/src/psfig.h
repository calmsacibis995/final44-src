/***	
 ***	psfig.h --
 ***	
 ***	Standard defines for psfig.
 ***	
 ***	T.Darrell, 3/86.
 ***/

# include <stdio.h>
# include <sys/file.h>

# define TRUE	1
# define FALSE	0

# define UP	1
# define DOWN	2

# define MAXDIRS	12	/* max no. of search dirs */

# define BUFSZ		1024
# define SMBUFSZ	128

# define FGST	".F+"
# define FGEND	".F-"

# define DraftDefault	100
# define BrokenOutLevel	10
# define InLineLevel	1

# define endof(s) (s + strlen(s))

extern		Draft, linenumber, inLineFlag;
extern		psditfix;
extern char	delimSt, delimEnd;
extern char	*XFlush;

extern char	*Strcat(),
		*Strcpy(),
		*getline(),
		*includeFig(),
		*getLab(),
		*abspath(),
		*strsave();

extern char	*malloc(),
		*free(),
		*strcat(),
		*strcpy(),
		*strncpy(),
		*index();

extern void	pushBackItem(),
		setInput();

/* end of psfig.h */
