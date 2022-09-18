h35314
s 00002/00002/00116
d D 8.1 93/06/06 16:16:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00118
d D 5.5 93/04/18 03:41:40 torek 5 4
c fix broken label handling (rewrite label code completely)
e
s 00003/00002/00116
d D 5.4 93/04/14 06:22:34 elan 4 3
c make sed work on 8-bit objects
c TK checking in for Elan Amir
e
s 00017/00001/00101
d D 5.3 92/08/28 15:25:46 bostic 3 2
c make pmatch a global; move SPACE structure here since main.c
c needs it now
e
s 00004/00002/00098
d D 5.2 92/08/24 21:27:38 bostic 2 1
c make empty RE's work, some minor cleanups, too
e
s 00100/00000/00000
d D 5.1 92/08/23 18:25:52 bostic 1 0
c date and time created 92/08/23 18:25:52 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Diomidis Spinellis.
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis of Imperial College, University of London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Types of address specifications
 */
enum e_atype {
	AT_RE,					/* Line that match RE */
	AT_LINE,				/* Specific line */
	AT_LAST,				/* Last line */
};

/*
 * Format of an address
 */
struct s_addr {
	enum e_atype type;			/* Address type */
	union {
		u_long l;			/* Line number */
		regex_t *r;			/* Regular expression */
	} u;
};

/*
 * Substitution command
 */
struct s_subst {
D 2
	int n;					/* Occurrence to subst 0=g */
E 2
I 2
	int n;					/* Occurrence to subst. */
E 2
	int p;					/* True if p flag */
	char *wfile;				/* NULL if no wfile */
	int wfd;				/* Cached file descriptor */
D 2
	regex_t re;				/* Regular expression */
E 2
I 2
	regex_t *re;				/* Regular expression */
E 2
D 3
	regmatch_t *pmatch;			/* Array of match strucs */
E 3
I 2
	int maxbref;				/* Largest backreference. */
	u_long linenum;				/* Line number. */
E 2
	char *new;				/* Replacement text */
};


/*
 * An internally compiled command.
D 4
 * Initialy, label references are stored in u.t, on a second pass they
E 4
I 4
 * Initialy, label references are stored in t, on a second pass they
E 4
 * are updated to pointers.
 */
struct s_command {
	struct s_command *next;			/* Pointer to next command */
	struct s_addr *a1, *a2;			/* Start and end address */
	char *t;				/* Text for : a c i r w */
	union {
		struct s_command *c;		/* Command(s) for b t { */
		struct s_subst *s;		/* Substitute command */
		u_char *y;			/* Replace command array */
		int fd;				/* File descriptor for w */
	} u;
	char code;				/* Command code */
	u_int nonsel:1;				/* True if ! */
	u_int inrange:1;			/* True if in range */
I 4
D 5
	u_int lused:1;				/* True if label used. */
E 5
E 4
};

/*
 * Types of command arguments recognised by the parser
 */
enum e_args {
	EMPTY,			/* d D g G h H l n N p P q x = \0 */
	TEXT,			/* a c i */
	NONSEL,			/* ! */
	GROUP,			/* { */
	COMMENT,		/* # */
	BRANCH,			/* b t */
	LABEL,			/* : */
	RFILE,			/* r */
	WFILE,			/* w */
	SUBST,			/* s */
	TR			/* y */
};

/*
 * Structure containing things to append before a line is read
 */
struct s_appends {
	enum {AP_STRING, AP_FILE} type;
	char *s;
I 4
	size_t len;
E 4
};
I 3

enum e_spflag {
	APPEND,					/* Append to the contents. */
D 4
	APPENDNL,				/* Append, with newline. */
E 4
	REPLACE,				/* Replace the contents. */
};

/*
 * Structure for a space (process, hold, otherwise).
 */
typedef struct {
	char *space;		/* Current space pointer. */
	size_t len;		/* Current length. */
	int deleted;		/* If deleted. */
	char *back;		/* Backing memory. */
	size_t blen;		/* Backing memory length. */
} SPACE;
E 3

/*
 * Error severity codes:
 */
#define	FATAL		0	/* Exit immediately with 1 */
#define	ERROR		1	/* Continue, but change exit value */
#define	WARNING		2	/* Just print the warning */
#define	COMPILE		3	/* Print error, count and finish script */
#define	COMPILE2	3	/* Print error, count and finish script */
E 1
