h48023
s 00001/00001/00021
d D 7.4 90/06/22 17:15:55 mckusick 4 3
c no more u.u_error
e
s 00001/00025/00021
d D 7.3 90/05/29 12:55:30 karels 3 2
c new model of system call dispatch
e
s 00019/00000/00027
d D 7.2 89/07/04 11:06:09 mckusick 2 1
c define initial set of fields for syscontext structure
e
s 00027/00000/00000
d D 7.1 89/05/09 21:36:08 mckusick 1 0
c place holder for eventual structure
e
u
U
t
T
I 1
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
 *
 *	%W% (Berkeley) %G%
 */

#include <user.h>

D 3
/*
 * This file defines the context necessary to do a system call.
 * For the time being it just selects fields from the user structure.
 */
I 2
#define syscontext	user

#define sc_ap		u_ap
#define sc_nd		u_nd
#define sc_retval1	u_r.u_rv.R_val1
#define sc_retval2	u_r.u_rv.R_val2
#define sc_offset	u_r.r_off
#define sc_cdir		u_nd.ni_cdir
#define sc_rdir		u_nd.ni_rdir
#define sc_cred		u_nd.ni_cred
#define sc_uid		u_nd.ni_cred->cr_uid
#define sc_gid		u_nd.ni_cred->cr_groups[0]
#define sc_ruid		u_nd.ni_cred->cr_ruid
#define sc_rgid		u_rgid
#define sc_groups	u_nd.ni_cred->cr_groups
#define sc_ngroups	u_nd.ni_cred->cr_ngroups
#define sc_acflag	u_acflag
#define sc_cmask	u_cmask
#define sc_ofile	u_ofile
E 2

#define RETURN(value)	{ u.u_error = (value); return; }
E 3
I 3
D 4
#define RETURN(value)	{ u.u_error = (value); return (u.u_error); }
E 4
I 4
#define RETURN(value)	{ return (value); }
E 4
E 3
E 1
