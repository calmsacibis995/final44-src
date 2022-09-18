h58428
s 00002/00002/00026
d D 8.1 93/06/06 15:49:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00015/00020
d D 5.1 91/02/03 13:35:48 bostic 4 3
c fix copyright notice
e
s 00003/00004/00032
d D 1.3 90/06/19 17:06:04 kfall 3 2
c use _PASSWORD_LEN definition in include/pwd.h
e
s 00005/00005/00031
d D 1.2 90/06/18 19:23:38 kfall 2 1
c change sizing on structures
e
s 00036/00000/00000
d D 1.1 90/06/18 17:35:38 kfall 1 0
c date and time created 90/06/18 17:35:38 by kfall
e
u
U
f b 
t
T
I 1
D 4

/*
E 4
I 4
/*-
E 4
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 4
 */

/*
 * kpasswd_proto
 *
 * definitions for the kpasswd "protocol"
D 4
 * (We hope this to be temporary until a real admin protocol is worked out)
E 4
I 4
 * (We hope this to be temporary until a real admin protocol is worked out.)
E 4
 */

D 2
#define	MSGSIZE	255
E 2
I 2
D 3
#define	MAX_PW_LEN	256
E 3
E 2
struct kpasswd_data {
D 2
	C_Block	random_key;
	char	secure_msg[MSGSIZE];
E 2
I 2
	des_cblock random_key;
D 3
	char secure_msg[MAX_PW_LEN];
E 3
I 3
	char secure_msg[_PASSWORD_LEN];
E 3
E 2
};
I 4

E 4
struct update_data {
D 2
	char	pw[255];
	char	secure_msg[MSGSIZE];
E 2
I 2
D 3
	char pw[MAX_PW_LEN];
	char secure_msg[MAX_PW_LEN];
E 3
I 3
	char pw[_PASSWORD_LEN];
	char secure_msg[_PASSWORD_LEN];
E 3
E 2
};
#define	SERVICE		"kpasswd"
D 4
#define	SECURE_STRING	"Kerberos password update program -- 12/9/88 UC Berkeley"
E 4
I 4
#define	SECURE_STRING \
	"Kerberos password update program -- 12/9/88 UC Berkeley"
E 4
E 1
