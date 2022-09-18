h25355
s 00001/00001/00043
d D 8.4 94/04/02 10:06:15 pendry 7 6
c add 1994 copyright
e
s 00000/00001/00044
d D 8.3 94/04/02 09:09:01 pendry 6 5
c new pw_copy.h file for passwd
e
s 00021/00000/00024
d D 8.2 94/04/02 07:56:53 pendry 5 4
c prettyness police
e
s 00002/00002/00022
d D 8.1 93/06/06 14:27:03 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00002/00014
d D 5.3 91/02/12 22:38:00 bostic 3 2
c rework the password subsystem
e
s 00001/00011/00015
d D 5.2 90/06/01 16:45:15 bostic 2 1
c new copyright notice
e
s 00026/00000/00000
d D 5.1 89/02/22 17:23:48 bostic 1 0
c date and time created 89/02/22 17:23:48 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
D 7
 * Copyright (c) 1988, 1993
E 7
I 7
 * Copyright (c) 1988, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

I 5
struct passwd;

E 5
D 3
struct entry {
E 3
I 3
typedef struct _entry {
E 3
	char *prompt;
	int (*func)(), restricted, len;
	char *except, *save;
D 3
};
E 3
I 3
} ENTRY;
E 3

I 3
/* Field numbers. */
#define	E_BPHONE	8
#define	E_HPHONE	9
#define	E_LOCATE	10
#define	E_NAME		7
#define	E_SHELL		12

extern ENTRY list[];
E 3
extern uid_t uid;
I 5

int	 atot __P((char *, time_t *));
void	 display __P((int, struct passwd *));
void	 edit __P((struct passwd *));
char    *ok_shell __P((char *));
int	 p_change __P((char *, struct passwd *, ENTRY *));
int	 p_class __P((char *, struct passwd *, ENTRY *));
int	 p_expire __P((char *, struct passwd *, ENTRY *));
int	 p_gecos __P((char *, struct passwd *, ENTRY *));
int	 p_gid __P((char *, struct passwd *, ENTRY *));
int	 p_hdir __P((char *, struct passwd *, ENTRY *));
int	 p_login __P((char *, struct passwd *, ENTRY *));
int	 p_login __P((char *, struct passwd *, ENTRY *));
int	 p_passwd __P((char *, struct passwd *, ENTRY *));
int	 p_shell __P((char *, struct passwd *, ENTRY *));
int	 p_uid __P((char *, struct passwd *, ENTRY *));
D 6
void	 pw_copy __P((int, int, struct passwd *));
E 6
char    *ttoa __P((time_t));
int	 verify __P((struct passwd *));
E 5
E 1
