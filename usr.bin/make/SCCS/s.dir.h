h34432
s 00014/00014/00030
d D 8.2 95/04/28 17:08:04 christos 3 2
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00042
d D 8.1 93/06/06 15:14:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00044/00000/00000
d D 5.1 93/05/24 14:47:02 bostic 1 0
c date and time created 93/05/24 14:47:02 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 2
I 2
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* dir.h --
 */

#ifndef	_DIR
#define	_DIR

typedef struct Path {
    char         *name;	    	/* Name of directory */
    int	    	  refCount; 	/* Number of paths with this directory */
    int		  hits;	    	/* the number of times a file in this
				 * directory has been found */
    Hash_Table    files;    	/* Hash table of files in directory */
} Path;

D 3
void	 Dir_AddDir __P((Lst, char *));
void	 Dir_ClearPath __P((Lst));
void	 Dir_Concat __P((Lst, Lst));
ClientData
	    Dir_CopyDir __P((Path *));
void	 Dir_Destroy __P((Path *));
void	 Dir_Expand __P((char *, Lst, Lst));
char	*Dir_FindFile __P((char *, Lst));
Boolean	 Dir_HasWildcards __P((char *));
void	 Dir_Init __P((void));
char	*Dir_MakeFlags __P((char *, Lst));
int	 Dir_MTime __P((GNode *));
void	 Dir_PrintDirectories __P((void));
void	 Dir_PrintPath __P((Lst));
E 3
I 3
void Dir_Init __P((void));
void Dir_End __P((void));
Boolean Dir_HasWildcards __P((char *));
void Dir_Expand __P((char *, Lst, Lst));
char *Dir_FindFile __P((char *, Lst));
int Dir_MTime __P((GNode *));
void Dir_AddDir __P((Lst, char *));
char *Dir_MakeFlags __P((char *, Lst));
void Dir_ClearPath __P((Lst));
void Dir_Concat __P((Lst, Lst));
void Dir_PrintDirectories __P((void));
void Dir_PrintPath __P((Lst));
void Dir_Destroy __P((ClientData));
ClientData Dir_CopyDir __P((ClientData));
E 3

#endif /* _DIR */
E 1
