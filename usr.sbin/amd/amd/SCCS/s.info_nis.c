h64704
s 00002/00002/00219
d D 8.1 93/06/06 11:40:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00002/00211
d D 5.4 92/02/09 08:48:19 pendry 4 3
c merge in new release
e
s 00003/00002/00210
d D 5.3 91/05/12 15:55:31 pendry 3 2
c checkpoint for network tape
e
s 00115/00011/00097
d D 5.2 91/03/17 13:33:22 pendry 2 1
c from amd5.3 alpha11
e
s 00108/00000/00000
d D 5.1 90/06/29 12:01:06 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: info_nis.c,v 5.2 90/06/23 22:19:32 jsp Rel $
E 2
I 2
D 3
 * $Id: info_nis.c,v 5.2.1.3 91/03/17 17:47:31 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: info_nis.c,v 5.2.1.4 91/05/07 22:18:01 jsp Alpha $
E 4
I 4
 * $Id: info_nis.c,v 5.2.2.1 1992/02/09 15:08:32 jsp beta $
E 4
 *
E 3
 */

/*
 * Get info from NIS map
 */

#include "am.h"

#ifdef HAS_NIS_MAPS
#include <rpcsvc/yp_prot.h>
#include <rpcsvc/ypclnt.h>

/*
 * Figure out the nis domain name
 */
static int determine_nis_domain(P_void)
{
I 4
static	int nis_not_running = 0;

E 4
D 2
static	 char default_domain[YPMAXDOMAIN];
E 2
I 2
	char default_domain[YPMAXDOMAIN];
E 2

I 4
	if (nis_not_running)
		return ENOENT;

E 4
	if (getdomainname(default_domain, sizeof(default_domain)) < 0) {
I 4
		nis_not_running = 1;
E 4
		plog(XLOG_ERROR, "getdomainname: %m");
		return EIO;
	}

D 2
	domain = default_domain;
	if (!*domain) {
		plog(XLOG_ERROR, "YP domain name is not set");
E 2
I 2
	if (!*default_domain) {
D 4
		plog(XLOG_ERROR, "NIS domain name is not set");
E 4
I 4
		nis_not_running = 1;
		plog(XLOG_WARNING, "NIS domain name is not set.  NIS ignored.");
E 4
E 2
		return ENOENT;
	}
I 4

E 4
I 2
	domain = strdup(default_domain);
E 2

	return 0;
}

I 2

#ifdef HAS_NIS_RELOAD
struct nis_callback_data {
	mnt_map *ncd_m;
	char *ncd_map;
	void (*ncd_fn)();
};

E 2
/*
I 2
 * Callback from yp_all
 */
static int callback(status, key, kl, val, vl, data)
int status;
char *key;
int kl;
char *val;
int vl;
struct nis_callback_data *data;
{
	if (status == YP_TRUE) {
		/*
		 * Add to list of maps
		 */
		char *kp = strnsave(key, kl);
		char *vp = strnsave(val, vl);
		(*data->ncd_fn)(data->ncd_m, kp, vp);

		/*
		 * We want more ...
		 */
		return FALSE;
	} else {
		/*
		 * NOMORE means end of map - otherwise log error
		 */
		if (status != YP_NOMORE) {
			/*
			 * Check what went wrong
			 */
			int e = ypprot_err(status);

#ifdef DEBUG
			plog(XLOG_ERROR, "yp enumeration of %s: %s, status=%d, e=%d",
					data->ncd_map, yperr_string(e), status, e);
#else
			plog(XLOG_ERROR, "yp enumeration of %s: %s", data->ncd_map, yperr_string(e));
#endif
		}

		return TRUE;
	}
}

int nis_reload P((mnt_map *m, char *map, void (*fn)()));
int nis_reload(m, map, fn)
mnt_map *m;
char *map;
void (*fn)();
{
	struct ypall_callback cbinfo;
	int error;
	struct nis_callback_data data;

	if (!domain) {
		error = determine_nis_domain();
		if (error)
			return error;
	}

	data.ncd_m = m;
	data.ncd_map = map;
	data.ncd_fn = fn;
	cbinfo.data = (voidp) &data;
	cbinfo.foreach = callback;

	error = yp_all(domain, map, &cbinfo);

	if (error)
		plog(XLOG_ERROR, "error grabbing nis map of %s: %s", map, yperr_string(ypprot_err(error)));

	return error;
}
#endif /* HAS_NIS_RELOAD */

/*
E 2
 * Try to locate a key using NIS.
D 2
 * Modify time is ignored in NIS - XXX
E 2
 */
int nis_search P((mnt_map *m, char *map, char *key, char **val, time_t *tp));
int nis_search(m, map, key, val, tp)
mnt_map *m;
char *map;
char *key;
char **val;
time_t *tp;
{
	int outlen;
	int res;
I 2
	int order;
E 2

I 2
	/*
	 * Make sure domain initialised
	 */
E 2
	if (!domain) {
		int error = determine_nis_domain();
		if (error)
			return error;
	}

I 2
	/*
	 * Check if map has changed
	 */
	if (yp_order(domain, map, &order))
		return EIO;
	if ((time_t) order > *tp) {
		*tp = (time_t) order;
		return -1;
	}

	/*
	 * Lookup key
	 */
E 2
	res = yp_match(domain, map, key, strlen(key), val, &outlen);

	/*
	 * Do something interesting with the return code
	 */
	switch (res) {
	case 0:
		return 0;

	case YPERR_KEY:
		return ENOENT;

	default:
		plog(XLOG_ERROR, "%s: %s", map, yperr_string(res));
		return EIO;
	}
}

D 2
int nis_init P((char *map));
int nis_init(map)
E 2
I 2
int nis_init P((char *map, time_t *tp));
int nis_init(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
D 2
	char *name = 0;
E 2
I 2
	int order;
E 2

	if (!domain) {
		int error = determine_nis_domain();
		if (error)
			return error;
	}

	/*
	 * To see if the map exists, try to find
	 * a master for it.
	 */
D 2
	if (yp_master(domain, map, &name))
E 2
I 2
	if (yp_order(domain, map, &order))
E 2
		return ENOENT;
D 2
	free(name);
E 2
I 2
	*tp = (time_t) order;
#ifdef DEBUG
	dlog("NIS master for %s@%s has order %d", map, domain, order);
#endif
E 2
	return 0;
}
#endif /* HAS_NIS_MAPS */
E 1
