/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	openprom_util.c,v $
 * Revision 2.2  91/08/29  22:39:16  berman
 * 	Created this file from SunOS 4.1.1 for use with new ROMS.
 * 	[91/06/11            berman]
 * 
 */
/* #ident "@(#)openprom_util.c 1.1 90/10/29 SMI" */

/*
 * Copyright (c) 1990 Sun Microsystems, Inc.
 */

/*
 * Routines for OBP boot support.
 */

#define	OPENPROMS
#include <mon/sunromvec.h>
#include <sun/openprom.h>
#include <sun/autoconf.h>
#include <scsi/scsi.h>


static int memlistdebug = 0;
#define	dprintf		if (memlistdebug) printf

struct memlist *
getmemlist(name, prop)
	char *name, *prop;
{
	int nodeid;
	int i, j, k, chunks;
	u_int propsize;
	struct dev_reg *rp;
	struct memlist *pmem;
	static caddr_t bufp = (caddr_t)0;
	static u_int left;

	if (bufp == (caddr_t)0) {
		bufp = (caddr_t)(*romp->op_alloc)((caddr_t)0, PAGESIZE);
		left = PAGESIZE;
	}

	/*
	 * First find the right node.
	 */
	nodeid =
	    searchpromtree((*romp->v_config_ops->devr_next)(0), name, bufp);
	if (nodeid == 0)
		return ((struct memlist *)0);
	dprintf("Found %s:%s at node %x\n", name, prop, nodeid);

	/*
	 * Allocate memlist elements, one per dev_reg struct.
	 */
	propsize = (u_int)getproplen(nodeid, prop);
	chunks = propsize / sizeof (struct dev_reg);
	if (chunks == 0)
		return ((struct memlist *)0);

	if (left < (chunks * sizeof (struct memlist))) {
		panic("memlists too big");
	}
	pmem = (struct memlist *)bufp;
	bzero((caddr_t)pmem, (u_int) chunks * sizeof (struct memlist));
	left -= (u_int) chunks * sizeof (struct memlist);
	bufp += (u_int) chunks * sizeof (struct memlist);

	if (left < propsize) {
		panic("memlists too big");
	}
	rp = (struct dev_reg *)bufp;
	bzero((caddr_t)rp, propsize);
	left -= propsize;
	bufp += propsize;

	/*
	 * Fill in memlist chunks.
	 */
	(void)(*romp->v_config_ops->devr_getprop)(nodeid, prop, rp);
	for (i = 0; i < chunks; ++i) {
		dprintf("Chunk %d: addr %x bustype %x size %x\n",
		    i, rp[i].reg_addr, rp[i].reg_bustype, rp[i].reg_size);
		if (rp[i].reg_bustype != OBMEM)
			continue;

		/*
		 * Insert the new element into the array of list nodes
		 * so that the array remains sorted in ascending order.
		 */

		/* Find the first element with a larger address */
		for (j = 0; j < i; j++)
			if (pmem[j].address > (u_int)rp[i].reg_addr)
				break;

		/* Copy following elements up to make room for the new one */
		for (k = i; k > j; --k)
			pmem[k] = pmem[k-1];

		/* Insert the new element */
		pmem[j].address = (u_int)rp[i].reg_addr;
		pmem[j].size = rp[i].reg_size;
	}
	for (i = 1; i < chunks; ++i) {
		if (pmem[i].address)
			pmem[i-1].next = &pmem[i];
	}
	return (pmem);
}

searchpromtree(node, name, buf)
	int node;
	char *name;
	char *buf;
{
	int id;

	*buf = '\0';
	(void)(*romp->v_config_ops->devr_getprop)(node, "name", buf);
	if (strcmp(buf, name) == 0) {
		return (node);
	}
	id = (*romp->v_config_ops->devr_next)(node);
	if (id && (id = searchpromtree(id, name, buf)))
		return (id);
	id = (*romp->v_config_ops->devr_child)(node);
	if (id && (id = searchpromtree(id, name, buf)))
		return (id);
	return (0);
}

static int path_debug = 0;
#undef	dprintf
#define	dprintf		if (path_debug) printf

/*
 * XXX - This doesn't belong here...
 * Convert hex string to u_int. Assumes no leading "0x".
 */

u_int
atou(s)
	char *s;
{
	u_int val = 0;
	u_int digit;

	while (*s) {
		if (*s >= '0' && *s <= '9')
			digit = *s++ - '0';
		else if (*s >= 'a' && *s <= 'f')
			digit = *s++ - 'a' + 10;
		else
			break;
		val = (val * 16) + digit;
	}
	return (val);
}

int (*
path_getdecodefunc(dip))()
	struct dev_info *dip;
{
	struct dev_path_ops *dpop;

	for (dpop = dev_path_opstab; dip && dpop->devp_name; ++dpop) {
		if (strcmp(dip->devi_name, dpop->devp_name) == 0)
			return (dpop->devp_decode_regprop);
	}
	return ((int (*)())0);
}

char *(*
path_getencodefunc(dip))()
	struct dev_info *dip;
{
	struct dev_path_ops *dpop;

	for (dpop = dev_path_opstab; dip && dpop->devp_name; ++dpop) {
		if (strcmp(dip->devi_name, dpop->devp_name) == 0)
			return (dpop->devp_encode_reg);
	}
	return ((char *(*)())0);
}

int (*
path_getmatchfunc(dip))()
	struct dev_info *dip;
{
	struct dev_path_ops *dpop;

	for (dpop = dev_path_opstab; dip && dpop->devp_name; ++dpop) {
		if (strcmp(dip->devi_name, dpop->devp_name) == 0)
			return (dpop->devp_match_addr);
	}
	return ((int (*)())0);
}

static char *
path_gettoken(from, to)
	char *from, *to;
{
	while (*from) {
		switch (*from) {
		case '/':
		case '@':
		case ':':
			*to = '\0';
			return (from);
		default:
			*to++ = *from++;
		}
	}
	*to = '\0';
	return (from);
}

struct _p2d {
	char *name;
	char *addrspec;
	int unit;
	struct dev_info *dev;
};

static int
path_findmatch(dip, arg)
	struct dev_info *dip;
	caddr_t arg;
{
	struct _p2d *p2d = (struct _p2d *)arg;
	int (*match_func)();
	extern int obio_match();

	/*
	 * "A Grail? But we already have one!"
	 */
	if (p2d->dev)
		return ((int)(p2d->dev));

	dprintf("\tchecking %s\n", dip->devi_name);
	/*
	 * "These aren't the droids you're looking for. Move along."
	 */
	if ((strcmp(p2d->name, "sd") == 0) &&
	    (strcmp(dip->devi_name, "sr") == 0))
		goto sr_hack;
	if (strcmp(dip->devi_name, p2d->name) != 0)
		return (0);

sr_hack:
	/*
	 * XXX - If no unit is specified, take the first.
	 * There should be some concept of "take the default".
	 */
	if (p2d->addrspec[0] == '\0')
		return ((int)(p2d->dev = dip));

	/*
	 * We may need to call a matching function to decode the address.
	 * First find out if there even is one. Note that the address encoding
	 * is a function of our *parent*.
	 */
	match_func = path_getmatchfunc(dip->devi_parent);
	/*
	 * XXX - No matching function? Use "obio" by default.
	 */
	if (match_func == (int (*)())0)
		match_func = obio_match;

	if (match_func(dip, p2d->addrspec))
		return ((int)(p2d->dev = dip));
	return ((int)(p2d->dev = (struct dev_info *)0));
}

static struct dev_info *
path_matchtoken(name, addrspec, dip)
	char *name, *addrspec;
	struct dev_info *dip;
{
	struct _p2d p2d;

	p2d.name = name;
	p2d.addrspec = addrspec;
	p2d.dev = NULL;
	dprintf("walk layer at %x (%s); looking for '%s' '%s'\n",
	    dip, dip->devi_name, name, addrspec);
	walk_layer(dip->devi_slaves, path_findmatch, (caddr_t)&p2d);
	return (p2d.dev);
}

/*
 * Given a path specifying a node in the prom's device tree,
 * return the kernel's corresponding dev_info node.
 * XXX - doesn't handle units yet.
 */
struct dev_info *
path_to_devi(p)
	char *p;
{
	char name[128], addrspec[128];
	struct dev_info *dip = top_devinfo;

	while (*p && *p == '/')
		++p;
	dprintf("path: '%s'\n", p);
	while (*p) {
		p = path_gettoken(p, name);
		dprintf("name: '%s' remainder: '%s'\n", name, p);
		if (*p == '@')
			p = path_gettoken(++p, addrspec);
		else
			addrspec[0] = '\0';
		dprintf("addrspec: '%s' remainder: '%s'\n", addrspec, p);
		dip = path_matchtoken(name, addrspec, dip);
		if (dip == (struct dev_info *)0)
			break;
		while (*p && *p++ != '/')
			;
	}
	return (dip);
}

/*
 * Given a path "/foo/bar/mumble/disk@blah,blah:part" where
 * part is an integer, return the partition number.
 * XXX - This needs to be designed better. Should part be a block offset,
 * or an integer, rather than a character?
 */
int
get_part_from_path(p)
	char *p;
{
	char *cp;

	cp = p + strlen(p);
	while (--cp != p) {
		if (*cp == ':')
			break;
	}
	if ((cp++ == p) || (*cp == '\0'))
		return (0);
	if (*cp >= 'a' && *cp <= 'z')	/* letter */
		return (*cp - 'a');
	if (*cp >= '0' && *cp <= '9')	/* digit */
		return (*cp - '0');
	return (*cp);			/* raw integer? */
}

static int
path_matchnameunit(dip, arg)
	struct dev_info *dip;
	caddr_t arg;
{
	struct _p2d *p2d = (struct _p2d *)arg;

	if (p2d->dev)
		return ((int)(p2d->dev));

	dprintf("\tchecking %s\n", dip->devi_name);
	if (strcmp(dip->devi_name, p2d->name) != 0)
		return (0);

	/*
	 * XXX - If no unit is specified, take the first.
	 * There should be some concept of "take the default".
	 */
	if (p2d->unit == -1 || p2d->unit == dip->devi_unit)
		return ((int)(p2d->dev = dip));

	return ((int)(p2d->dev = (struct dev_info *)0));
}

static struct dev_info *
path_findnodebyname(name, unit, dip)
	char *name;
	int unit;
	struct dev_info *dip;
{
	struct _p2d p2d;

	p2d.name = name;
	p2d.unit = unit;
	p2d.dev = NULL;
	dprintf("walk tree at %x (%s); looking for '%s' '%d'\n",
	    dip, dip->devi_name, name, unit);
	walk_devs(dip, path_matchnameunit, (caddr_t)&p2d);
	return (p2d.dev);
}

void
devi_to_path(name)
	char *name;
{
	struct dev_info *dip;
	char tmpname[256];
	char addr[64];
	char *cp;
	int unit = 0;
	char part = '\0';
	extern char *strcpy();
	char *(*encode_func)();

	/*
	 * Scan "name", pulling out the unit number and partition.
	 * Null out the unit number in the string so that the device
	 * name becomes null-terminated.
	 * XXX - What about IPI?
	 */
	cp = name;
	while (*cp && *cp > '9')
		++cp;
	while (*cp) {
		if ((*cp < '0') || (*cp > '9'))
			break;
		unit = (unit * 10) + (*cp - '0');
		*cp++ = '\0';
	}
	if (*cp)
		part = *cp;

	/*
	 * Locate the devinfo node for this device.
	 */
	dip = path_findnodebyname(name, unit, top_devinfo);
	*name = '\0';
	if (dip == (struct dev_info *)0)
		return;

	/*
	 * Now trace the tree bottom-to-top, translating each node
	 * into a prom-compatible specifier. Prepend each specifier
	 * to the path already built. Stop at the root node.
	 */
	do {
		/*
		 * Find the appropriate encoding funtion to translate
		 * the node's reg, target/lun, etc. information
		 * to an address specification that the prom can grok.
		 */
		encode_func = path_getencodefunc(dip->devi_parent);
		/*
		 * XXX - No matching function? Use "obio" by default.
		 */
		if (encode_func == (char *(*)())0)
			encode_func = obio_encode_reg;
		(void)encode_func(dip, addr);
		(void)sprintf(tmpname, "/%s@%s%s", dip->devi_name, addr, name);
		(void)strcpy(name, tmpname);
	} while ((dip = dip->devi_parent) && dip->devi_parent);

	if (part) {
		cp = name + strlen(name);
		(void)sprintf(cp, ":%c", part);
	}
	dprintf("name = '%s'\n", name);
}

