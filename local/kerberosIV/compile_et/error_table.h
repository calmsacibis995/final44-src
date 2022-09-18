#ifndef _ET

#ifndef __STDC__
#define const
#endif

extern int errno;
typedef struct {
	const char	**msgs;
	int		base;
	int		n_msgs;
} error_table;
extern error_table **_et_list;

#define	ERROR_CODE	"int"	/* type used for error codes */

#define	ERRCODE_RANGE	8	/* # of bits to shift table number */
#define	BITS_PER_CHAR	6	/* # bits to shift per character in name */

#define _ET
#endif
