h05230
s 00002/00002/00217
d D 8.1 93/06/11 15:17:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00003/00211
d D 7.2 93/04/27 07:37:11 torek 2 1
c fix openpromcheckid -- was infintely recursive
e
s 00214/00000/00000
d D 7.1 93/04/20 23:38:08 torek 1 0
c date and time created 93/04/20 23:38:08 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 2
 * from: $Header: openprom.c,v 1.2 93/04/20 11:16:14 torek Exp $
E 2
I 2
 * from: $Header: openprom.c,v 1.3 93/04/27 08:56:09 torek Exp $
E 2
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>

#include <machine/bsd_openprom.h>
#include <machine/openpromio.h>

static	int lastnode;			/* speed hack */
extern	int optionsnode;		/* node ID of ROM's options */
I 2
extern	int findroot();			/* returns node ID of top node */
E 2
extern	struct promvec *promvec;

int
openpromopen(dev, flags, mode)
	dev_t dev;
	int flags, mode;
{

	return (0);
}

int
openpromclose(dev, flags, mode)
	dev_t dev;
	int flags, mode;
{

	return (0);
}

I 2
/*
 * Verify target ID is valid (exists in the OPENPROM tree), as
 * listed from node ID sid forward.
 */
E 2
static int
openpromcheckid(sid, tid)
	register int sid, tid;
{
	register struct nodeops *no;

	no = promvec->pv_nodeops;
D 2
	while ((sid = no->no_nextnode(sid)) != 0)
E 2
I 2
	for (; sid != 0; sid = no->no_nextnode(sid))
E 2
		if (sid == tid || openpromcheckid(no->no_child(sid), tid))
			return (1);

	return (0);
}

static int
openpromgetstr(len, user, cpp)
	int len;
	char *user, **cpp;
{
	register int error;
	register char *cp;

	/* Reject obvious bogus requests */
	if ((u_int)len > (8 * 1024) - 1)
		return (ENAMETOOLONG);

	*cpp = cp = malloc(len + 1, M_TEMP, M_WAITOK);
	error = copyin(user, cp, len);
	cp[len] = '\0';
	return (error);
}

int
openpromioctl(dev, cmd, data, flags, p)
	dev_t dev;
	int cmd;
	caddr_t data;
	int flags;
	struct proc *p;
{
	register struct opiocdesc *op;
	register int node, len, ok, error, s;
	char *name, *value, *nextprop;
	register struct nodeops *no;

	/* All too easy... */
	if (cmd == OPIOCGETOPTNODE) {
		*(int *)data = optionsnode;
		return (0);
	}

	/* Verify node id */
	op = (struct opiocdesc *)data;
	node = op->op_nodeid;
	if (node != 0 && node != lastnode && node != optionsnode) {
		/* Not an easy one, must search for it */
		s = splhigh();
D 2
		ok = openpromcheckid(0, node);
E 2
I 2
		ok = openpromcheckid(findroot(), node);
E 2
		splx(s);
		if (!ok)
			return (EINVAL);
		lastnode = node;
	}

	name = value = NULL;
	no = promvec->pv_nodeops;
	error = 0;
	switch (cmd) {

	case OPIOCGET:
		if ((flags & FREAD) == 0)
			return (EBADF);
		if (node == 0)
			return (EINVAL);
		error = openpromgetstr(op->op_namelen, op->op_name, &name);
		if (error)
			break;
		s = splhigh();
		len = no->no_proplen(node, name);
		splx(s);
		if (len > op->op_buflen)
			len = op->op_buflen;
		else
			op->op_buflen = len;
		/* -1 means no entry; 0 means no value */
		if (len <= 0)
			break;
		value = malloc(len, M_TEMP, M_WAITOK);
		s = splhigh();
		(void)no->no_getprop(node, name, value);
		splx(s);
		error = copyout(value, op->op_buf, len);
		break;

	case OPIOCSET:
		if ((flags & FWRITE) == 0)
			return (EBADF);
		if (node == 0)
			return (EINVAL);
		error = openpromgetstr(op->op_namelen, op->op_name, &name);
		if (error)
			break;
		error = openpromgetstr(op->op_buflen, op->op_buf, &value);
		if (error)
			break;
		s = splhigh();
		len = no->no_setprop(node, name, value, op->op_buflen + 1);
		splx(s);
		if (len != op->op_buflen)
			error = EINVAL;
		break;

	case OPIOCNEXTPROP:
		if ((flags & FREAD) == 0)
			return (EBADF);
		if (node == 0)
			return (EINVAL);
		error = openpromgetstr(op->op_namelen, op->op_name, &name);
		if (error)
			break;
		s = splhigh();
		nextprop = no->no_nextprop(node, name);
		splx(s);
		len = strlen(nextprop);
		if (len > op->op_buflen)
			len = op->op_buflen;
		else
			op->op_buflen = len;
		error = copyout(nextprop, op->op_buf, len);
		break;

	case OPIOCGETNEXT:
		if ((flags & FREAD) == 0)
			return (EBADF);
		s = splhigh();
		node = no->no_nextnode(node);
		splx(s);
		*(int *)data = lastnode = node;
		break;

	case OPIOCGETCHILD:
		if ((flags & FREAD) == 0)
			return (EBADF);
		if (node == 0)
			return (EINVAL);
		s = splhigh();
		node = no->no_child(node);
		splx(s);
		*(int *)data = lastnode = node;
		break;

	default:
		return (ENOTTY);
	}

	if (name)
		free(name, M_TEMP);
	if (value)
		free(value, M_TEMP);

	return (error);
}
E 1
