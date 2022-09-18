/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	inline.h,v $
 * Revision 2.4  89/02/25  17:59:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/23  22:18:35  af
 * 	Changes for I386: replace index by strchr (sysV)
 * 	[89/01/09            rvb]
 * 
 *  6-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define sun pcc comment char == '|'
 *
 *  3-Nov-87  David Black (dlb) at Carnegie-Mellon University
 *	Added definitions for multimax inline label expansion.
 *
 */
/*
 * Copyright (c) 1984, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)inline.h	7.1 (Berkeley) 6/5/86
 */

/*
 * COMMENTCHAR is the character delimiting comments in the assembler.
 * LABELCHAR is the character that separates labels from instructions.
 * ARGSEPCHAR is the character that separates arguments in instructions.
 */

#ifdef	sun
#define COMMENTCHAR	'|'
#else	sun
#define COMMENTCHAR	'#'
#endif	sun
#define LABELCHAR	':'
#define ARGSEPCHAR	','

/*
 * Expansion parameters:
 *   QUEUESIZE is the number of instructions to be considered for 
 *	integration of argument pushes and pops
 *   MAXLINELEN is the longest expected input line
 *   MAXARGS is the maximum number of arguments in an assembly instruction
 */
#define QUEUESIZE	16
#define MAXLINELEN	1024
#define MAXARGS		10

/*
 * The following global variables are used to manipulate the queue of
 * recently seen instructions.
 *	line - The queue of instructions.
 *	bufhead - Pointer to next availble queue slot. It is not
 *		considered part of te instruction stream until
 *		bufhead is advanced.
 *	buftail - Pointer to last instruction in queue.
 * Note that bufhead == buftail implies that the queue is empty.
 */
#ifdef	CMU
int pre_read;
#endif	CMU
int bufhead, buftail;
char line[QUEUESIZE][MAXLINELEN];

#define SUCC(qindex) ((qindex) + 1 == QUEUESIZE ? 0 : (qindex) + 1)
#define PRED(qindex) ((qindex) - 1 < 0 ? QUEUESIZE - 1 : (qindex) - 1)

/*
 * Hash table headers should be twice as big as the number of patterns.
 * They must be a power of two.
 */
#define HSHSIZ	128

/*
 * These tables specify the substitutions that are to be done.
 */
struct pats {
	int	args;
	char	*name;
	char	*replace;
	struct	pats *next;
	int	size;
};
struct pats *patshdr[HSHSIZ];
extern struct pats language_ptab[], libc_ptab[], machine_ptab[];
extern struct pats vax_libc_ptab[], vaxsubset_libc_ptab[];
extern struct pats vax_ptab[], vaxsubset_ptab[];

/*
 * This table defines the set of instructions that demark the
 * end of a basic block.
 */
struct inststoptbl {
	char	*name;
	struct	inststoptbl *next;
	int	size;
};
struct inststoptbl *inststoptblhdr[HSHSIZ];
extern struct inststoptbl inststoptable[];

/*
 * Miscellaneous functions.
 */
char *newline(), *copyline(), *doreplaceon();

#ifdef	multimax
/*
 *	Definitions and storage for local label expansion.  labelnum is the 
 *	number for the next generated label (.LInnn).  labelstrings holds
 *	the current translation from labels of the form num$ to real labels.
 */
#define LOC_LABEL_CHAR		'$'
#define LOC_LABEL_BUFLEN	256
#define LOC_LABEL_LIMIT		16

static	labelnum = 1;
char	*labelbufp;
char	labelbuf[LOC_LABEL_BUFLEN];
char	*labelstrings[LOC_LABEL_LIMIT];

#endif	multimax

#ifdef	i386
#define index	strchr
#endif	i386
