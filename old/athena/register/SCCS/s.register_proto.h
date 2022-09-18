h27865
s 00019/00000/00006
d D 1.2 89/05/17 22:42:48 kfall 2 1
c add UCB header, and a couple of defs
e
s 00006/00000/00000
d D 1.1 88/12/12 20:55:06 kfall 1 0
c date and time created 88/12/12 20:55:06 by kfall
e
u
U
t
T
I 2
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
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
 */

E 2
I 1
#define	APPEND_DB	0x01
I 2
#define	ABORT		0x02
E 2

I 2
#define	GOTKEY_MSG	"GOTKEY"
E 2

struct	keyfile_data {
	C_Block		kf_key;
};
E 1
