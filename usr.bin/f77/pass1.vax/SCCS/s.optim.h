h49975
s 00005/00004/00106
d D 5.2 91/04/12 16:09:02 bostic 2 1
c new copyright; att/bsd/shared
e
s 00110/00000/00000
d D 5.1 85/06/07 21:42:11 mckusick 1 0
c 4.3BSD beta release version
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * structure to hold trees for optimization
 */

typedef struct slt {
	field 		type;
	field		flags;
	short		lineno;
	struct slt	*next, *prev;
	struct slt	*nullslot;
	expptr		expr;
	int		label;
	int		*ctlinfo;
};

typedef struct slt *Slotp;

extern Slotp	firstslot, lastslot;	/* first, last slots in buffer */
extern int	numslots;		/* number of slots */

Slotp newslot(), optbuff(), optinsert();
struct Ctlframe *cpframe();

/*
**      Structures for cse analysis
*/

typedef struct IDblock *idptr;
typedef struct VALUEnode *valuen;
typedef struct IDlist  *idlptr;
typedef struct DUPlist *duplptr;
typedef struct NODElist *nodelptr;

struct IDblock
{
	expptr idaddr;    
	valuen initval, assgnval;
	nodelptr headnodelist;
	struct IDblock *next;
};           

struct VALUEnode
{
	expptr opp;
	expptr *parent;
	int n_dups;
	unsigned is_dead : 1;
	valuen lc,rc,rs;
	idlptr headdeplist;
	duplptr headduplist;
	struct VALUEnode *next;
};

struct IDlist
{
	idptr idp;
	struct IDlist *next;
};

struct DUPlist
{
	expptr *parent;
	struct DUPlist *next;
};

struct NODElist
{
	valuen nodep;
	struct NODElist *next;
};

/*
 * structure to hold information on basic blocks
 */



typedef struct bblock {
	Slotp		first, last;
	idptr		headid;
	valuen		headnode, tailnode;
	struct bblock	*next, *prev;
};

typedef struct bblock *Bblockp;

extern Bblockp	firstblock;		/* first block in buffer */
extern Bblockp	lastblock;		/* last block in buffer */



/* data structure for optloop and regalloc routines */

typedef
  struct regnode
    {
      field vstg;
      field vtype;
      int memno;
      int memoffset;
      unsigned isarrayarg : 1;
    } REGNODE;
E 1
