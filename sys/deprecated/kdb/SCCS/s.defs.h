h35894
s 00020/00021/00094
d D 7.10 90/05/03 17:47:58 sklower 10 9
c first crack at torek changes, may need bug fixes
e
s 00001/00001/00114
d D 7.9 90/02/20 22:18:41 mckusick 9 8
c raise limit on maxoff
e
s 00002/00001/00113
d D 7.8 89/09/02 12:46:08 karels 8 7
c add :k (kill kernel), with panic from trap like other traps
e
s 00003/00003/00111
d D 7.7 89/05/05 00:22:02 mckusick 7 6
c get rid of spurious includes
e
s 00003/00003/00111
d D 7.6 89/04/25 11:03:55 mckusick 6 5
c ../machine => machine
e
s 00001/00001/00113
d D 7.5 89/04/25 11:03:30 mckusick 5 4
c make CTRL macro safe for ANSI
e
s 00010/00005/00104
d D 7.4 86/12/15 20:26:43 sam 4 3
c lint
e
s 00001/00001/00108
d D 7.3 86/11/23 13:35:59 sam 3 2
c move machine dependencies to ../machine/kdbparam.h
e
s 00006/00004/00103
d D 7.2 86/11/20 14:42:10 sam 2 1
c miscellaneous cleanups
e
s 00107/00000/00000
d D 7.1 86/11/20 12:21:59 sam 1 0
c date and time created 86/11/20 12:21:59 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 8
 * Copyright (c) 1986 Regents of the University of California.
E 8
I 8
 * Copyright (c) 1986, 1989 Regents of the University of California.
E 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 4

/*
 * adb - string table version; common definitions
 */

#include "param.h"
D 7
#include "dir.h"
D 6
#include "../machine/psl.h"
#include "../machine/pte.h"
E 6
I 6
#include "machine/psl.h"
#include "machine/pte.h"
E 7
E 6
#include "user.h"
#include "proc.h"
I 7

#include "machine/psl.h"
#include "machine/pte.h"
E 7

#include <a.out.h>
#include <ctype.h>

struct	pcb kdbpcb;		/* must go before redef.h */

D 10
#include "redef.h"
E 10
D 3
#include "machine.h"
E 3
I 3
D 6
#include "../machine/kdbparam.h"
E 6
I 6
#include "machine/kdbparam.h"
E 6
E 3

/* access modes */
#define RD	0
#define WT	1

#define NSP	0
#define	ISP	1
#define	DSP	2
#define STAR	4

/*
 * Symbol types, used internally in calls to findsym routine.
 * One the VAX this all degenerates since I & D symbols are indistinct.
 * Basically we get NSYM==0 for `=' command, ISYM==DSYM otherwise.
 */
#define NSYM	0
#define DSYM	1		/* Data space symbol */
#define ISYM	DSYM		/* Instruction space symbol == DSYM on VAX */

#define BKPTSET	1
#define BKPTEXEC 2

I 2
/*
 * setexit/reset tokens..
 */
#define	ERROR	1
#define	NEXT	6
E 2
#define	SINGLE	7
#define	CONTIN	8
I 8
#define	PANIC	9
E 8

D 2
#define MAXCOM	64
#define MAXARG	32
E 2
#define LINSIZ	256
D 9
#define MAXOFF	1024
E 9
I 9
#define MAXOFF	65535
E 9
#define MAXPOS	80
#define MAXLIN	256
#define QUOTE	0200

D 2
#define TRUE	 (-1)
#define FALSE	0
E 2
#define LOBYTE	0377
#define STRIP	0177

#define SP	' '
#define TB	'\t'
#define EOR	'\n'
D 5
#define	CTRL(c)	('c'&037)
E 5
I 5
#define	CTRL(c)	(c&037)
E 5

#define	eqstr(a,b)	(strcmp(a,b)==0)

typedef	unsigned ADDR;
typedef	unsigned POS;

typedef	struct bkpt {
	ADDR	loc;
	ADDR	ins;
	short	count;
	short	initcnt;
	short	flag;
I 2
#define MAXCOM	64
E 2
	char	comm[MAXCOM];
	struct	bkpt *nxtbkpt;
} BKPT, *BKPTR;

typedef	struct {
	char	*rname;
	int	*rkern;
} REGLIST, *REGPTR;

D 10
ADDR	maxoff;
ADDR	localval;
int	mkfault;
long	var[36];
D 4
long	maxstor;
E 4
char	*errflg;
long	dot;
int	dotinc;
long	adrval;
int	adrflg;
long	cntval;
int	cntflg;
E 10
I 10
ADDR	kdbmaxoff;
ADDR	kdblocalval;
int	kdbmkfault;
long	kdbvar[36];
char	*kdberrflg;
long	kdbdot;
int	kdbdotinc;
long	kdbadrval;
int	kdbadrflg;
long	kdbcntval;
int	kdbcntflg;
E 10

/* result type declarations */
D 10
long	inkdot();
D 4
POS	get();
POS	chkget();
E 4
I 4
u_int	get();
u_int	chkget();
u_int	bchkget();
E 4
char	*exform();
D 4
long	round();
E 4
BKPTR	scanbkpt();
E 10
I 10
long	kdbinkdot();
u_int	kdbget();
u_int	kdbchkget();
u_int	kdbbchkget();
char	*kdbexform();
BKPTR	kdbscanbkpt();
E 10

D 10
struct	nlist *symtab, *esymtab;
struct	nlist *cursym;
struct	nlist *lookup();
E 10
I 10
struct	nlist *kdbsymtab, *kdbesymtab;
struct	nlist *kdbcursym;
struct	nlist *kdblookup();
E 10
E 1
