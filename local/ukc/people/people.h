/*
 *	people.h	1.1	5/6/87
 *	header file for the database routines used to access
 *	the address structure
 */

/*
 *	Structure of each individual data line in a record
 */
struct li
{	char	*base;
	char	*key;
	char	*data;
};

#define MAXCHARS	1024	/* Maximum size of a data line */

#define	FOUND	0		/* As opposed to EOF */

typedef struct li Li;

#define MAXLINES	100

extern Li rec[];	/* Current input record */

#define STREQ(a, b)	(*(a) == *(b) && strcmp((a), (b)) == 0)


extern char *progname;

/*
 *	forward routine defs
 */
char	*index();
char	*rindex();
char	*malloc();
char	*tokstart();
char	*getenv();
char	*tokend();
Li	*search();
