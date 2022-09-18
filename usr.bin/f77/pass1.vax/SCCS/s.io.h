h21585
s 00005/00004/00061
d D 5.2 91/04/12 16:08:55 bostic 2 1
c new copyright; att/bsd/shared
e
s 00065/00000/00000
d D 5.1 85/06/07 21:38:35 mckusick 1 0
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

#define NDDATA	1
#define NDLABEL	2
#define NDADDR	3
#define NDNULL	4




typedef
  struct IoAddr
    {
      int stg;
      int memno;
      ftnint offset;
    }
  ioaddr;



typedef
  union IoValue
    {
      Constp cp;
      ftnint label;
      struct IoAddr addr;
    }
  iovalue;



typedef
  struct IoBlock
    {
      struct IoBlock *next;
      int blkno;
      ftnint len;
      struct OffsetList *olist;
    }
  ioblock;



typedef
  struct OffsetList
    {
      struct OffsetList *next;
      ftnint offset;
      int tag;
      union IoValue val;
    }
  offsetlist;




extern ioblock *iodata;

E 1
