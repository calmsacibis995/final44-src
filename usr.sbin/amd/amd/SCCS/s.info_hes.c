h31514
s 00002/00002/00669
d D 8.1 93/06/06 11:40:05 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00670
d D 5.4 92/02/09 08:48:15 pendry 4 3
c merge in new release
e
s 00011/00009/00660
d D 5.3 91/05/12 15:55:26 pendry 3 2
c checkpoint for network tape
e
s 00593/00011/00076
d D 5.2 91/03/17 13:33:17 pendry 2 1
c from amd5.3 alpha11
e
s 00087/00000/00000
d D 5.1 90/06/29 12:01:05 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: info_hes.c,v 5.2 90/06/23 22:19:30 jsp Rel $
E 2
I 2
D 3
 * $Id: info_hes.c,v 5.2.1.3 91/03/03 20:39:41 jsp Alpha $
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
 * $Id: info_hes.c,v 5.2.1.5 91/05/07 22:17:58 jsp Alpha $
E 4
I 4
 * $Id: info_hes.c,v 5.2.2.1 1992/02/09 15:08:29 jsp beta $
E 4
 *
E 3
 */

/*
 * Get info from Hesiod
I 2
 *
 * Zone transfer code from Bruce Cole <cole@cs.wisc.edu>
E 2
 */

#include "am.h"

#ifdef HAS_HESIOD_MAPS
#include <hesiod.h>

#define	HES_PREFIX	"hesiod."
#define	HES_PREFLEN	7

I 2
#ifdef HAS_HESIOD_RELOAD
#include <arpa/nameser.h>
#include <resolv.h>
#include <sys/uio.h>
#include <netdb.h>

E 2
/*
D 2
 * No way to probe the server - check the map name begins with "hesiod."
E 2
I 2
 * Patch up broken system include files
E 2
 */
D 2
hesiod_init(map)
E 2
I 2
#ifndef C_HS
#define C_HS	4
#endif
#ifndef T_TXT
#define	T_TXT	16
#endif

static int soacnt;
static struct timeval hs_timeout;
static int servernum;
#endif /* HAS_HESIOD_RELOAD */

/*
 * No easy way to probe the server - check the map name begins with "hesiod."
 */
int hesiod_init P((char *map, time_t *tp));
int hesiod_init(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
I 2
#ifdef DEBUG
	dlog("hesiod_init(%s)", map);
#endif
	*tp = 0;
E 2
	return strncmp(map, HES_PREFIX, HES_PREFLEN) == 0 ? 0 : ENOENT;
}


/*
I 2
 * Make Hesiod name.  Skip past the "hesiod."
 * at the start of the map name and append
 * ".automount".  The net effect is that a lookup
 * of /defaults in hesiod.home will result in a
 * call to hes_resolve("/defaults", "home.automount");
 */
I 3
#ifdef notdef
E 3
#define MAKE_HES_NAME(dest, src) sprintf(dest, "%s%s", src + HES_PREFLEN, ".automount")
I 3
#endif
E 3

/*
E 2
 * Do a Hesiod nameserver call.
 * Modify time is ignored by Hesiod - XXX
 */
I 2
int hesiod_search P((mnt_map *m, char *map, char **pval, time_t *tp));
E 2
int hesiod_search(m, map, key, pval, tp)
mnt_map *m;
char *map;
char *key;
char **pval;
time_t *tp;
{
	int error;
D 3
	char hes_map[MAXPATHLEN];
E 3
I 3
	char hes_key[MAXPATHLEN];
E 3
	char **rvec;
I 2
#ifdef DEBUG
	dlog("hesiod_search(m=%x, map=%s, key=%s, pval=%x tp=%x)", m, map, key, pval, tp);
#endif
D 3
	MAKE_HES_NAME(hes_map, map);
E 3
I 3
	/*MAKE_HES_NAME(hes_map, map);*/
	sprintf(hes_key, "%s.%s", key, map+HES_PREFLEN);
E 3

E 2
	/*
D 2
	 * Make Hesiod name.  Skip past the "hesiod."
	 * at the start of the map name and append
	 * ".automount".  The net effect is that a lookup
	 * of /defaults in hesiod.home will result in a
	 * call to hes_resolve("/defaults", "home.automount");
	 */
	sprintf(hes_map, "%s%s", map + HES_PREFLEN, ".automount");
	/*
E 2
	 * Call the resolver
	 */
I 2
#ifdef DEBUG
D 3
	dlog("hesiod_search: hes_resolve(%s, %s)", key, hes_map);
E 3
I 3
	dlog("hesiod_search: hes_resolve(%s, %s)", hes_key, "automount");
E 3
#ifdef HAS_HESIOD_RELOAD
	if (debug_flags & D_FULL)
		_res.options |= RES_DEBUG;
#endif
#endif
E 2
D 3
	rvec = hes_resolve(key, hes_map);
E 3
I 3
	rvec = hes_resolve(hes_key, "automount");
E 3
	/*
	 * If a reply was forthcoming then return
	 * it (and free subsequent replies)
	 */
	if (rvec && *rvec) {
		*pval = *rvec;
		while (*++rvec)
			free(*rvec);
		return 0;
	}

	/*
	 * Otherwise reflect the hesiod error into a Un*x error
	 */
I 2
#ifdef DEBUG
	dlog("hesiod_search: Error: %d", hes_error());
#endif
E 2
	switch (hes_error()) {
	case HES_ER_NOTFOUND:	error = ENOENT; break;
	case HES_ER_CONFIG:	error = EIO; break;
	case HES_ER_NET:	error = ETIMEDOUT; break;
	default:		error = EINVAL; break;
	}
I 2
#ifdef DEBUG
	dlog("hesiod_search: Returning: %d", error);
#endif
E 2
	return error;
}
I 2

#ifdef HAS_HESIOD_RELOAD
/*
 * Zone transfer...
 */

#define MAXHSNS 8
#define MAX_NSADDR 16

static char *hs_domain;
static mnt_map *hs_map;
static int hs_nscount;
static char nsaddr_list[MAX_NSADDR][sizeof(struct in_addr)];

int hesiod_reload P((mnt_map *m, char *map, void (*fn)()));
int hesiod_reload(m, map, fn)
mnt_map *m;
char *map;
void (*fn)();
{
D 3
	char hes_map[MAXPATHLEN];
E 3
	char *zone_name, *cp;
	short domainlen;
	int status;

#ifdef DEBUG
	dlog("hesiod_reload (%x %s %x)", m, map, fn);
#endif DEBUG
	if (status = res_init()) {
#ifdef DEBUG
		dlog("hesiod_reload: res_init failed with %d", status);
#endif
		return(status);
	}
	_res.retrans = 90;
	hs_map = m;
	domainlen = strlen(hostdomain);
D 3
	MAKE_HES_NAME(hes_map, map);
	zone_name = hes_to_bind("", hes_map);
E 3
I 3
	zone_name = hes_to_bind(map+HES_PREFLEN, "automount");
E 3
	if (*zone_name == '.')
		zone_name++;
	hs_domain = zone_name;
	/* Traverse the DNS tree until we find an SOA we can transfer from.
	 (Our initial zone_name is likely to just be a subtree of a
	 real zone). */
	do {
		/* If we can't find any NS records, go up a level in the
		   DNS tree */
		if (hs_get_ns_list(zone_name) == 0 &&
		    hs_zone_transfer(zone_name) == 0)
			return(0);
		/* Move up DNS tree by one component */
		if (cp = strchr(zone_name, '.'))
			zone_name = ++cp;
		else
			break;
	} while (strlen(zone_name) >= domainlen);
#ifdef DEBUG
	dlog("hesiod_reload: Giving up on %s", hs_domain);
#endif
	return(-1);
}

hs_zone_transfer(domain)
char *domain;
{
	int status, len;
	char buf[PACKETSZ];
	/* Want to make sure ansbuf is well alligned */
	long ansbuf[PACKETSZ/sizeof(long)];

#ifdef DEBUG
	dlog("hs_zone_transfer (%s)", domain);
#endif
	if ((len = res_mkquery(QUERY, domain, C_HS, T_AXFR,
			       (char *)NULL, 0, NULL, buf, PACKETSZ)) == -1) {
#ifdef DEBUG
		dlog("hs_zone_transfer: res_mkquery failed");
#endif
		errno = 0;
		return(-1);
	}
	if ((status = hs_res_send(buf, len, (char *)ansbuf, PACKETSZ)) == -1) {
#ifdef DEBUG
	    dlog("hs_zone_transfer: hs_res_send failed.  status %d errno %d",
		 status, errno);
#endif
		errno = 0;
		return(-1);
	}
	return(0);
}

#define hs_server_addr(ns) ((struct in_addr *) nsaddr_list[ns])

hs_res_send(buf, buflen, answer, anslen)
char *buf;
int buflen;
char *answer;
int anslen;
{
	int retry, ns;
	u_short id, len;
	HEADER *hp = (HEADER *) buf;
	struct iovec iov[2];
	static int s = -1;
	int status;
	struct sockaddr_in server;

	soacnt = 0;
	id = hp->id;
	/*
	 * Send request, RETRY times, or until successful
	 */
	for (retry = _res.retry; retry > 0; retry--) {
		for (ns = 0; ns < hs_nscount; ns++) {
			hs_timeout.tv_sec =
				(_res.retrans << (_res.retry - retry))
				/ hs_nscount;
			if (hs_timeout.tv_sec <= 0)
				hs_timeout.tv_sec = 1;
			hs_timeout.tv_usec = 0;
			if (s < 0) {
				s = socket(AF_INET, SOCK_STREAM, 0);
				if (s < 0) {
					continue;
				}
				servernum = ns;
				bcopy(hs_server_addr(ns), &server.sin_addr,
				      sizeof(struct in_addr));
				server.sin_family = AF_INET;
				server.sin_port = htons(NAMESERVER_PORT);
					
				if (connect(s, &server,
					    sizeof(struct sockaddr)) < 0) {
					(void) close(s);
					s = -1;
					continue;
				}
			}
			/*
			 * Send length & message
			 */
			len = htons((u_short)buflen);
			iov[0].iov_base = (caddr_t)&len;
			iov[0].iov_len = sizeof(len);
			iov[1].iov_base = buf;
			iov[1].iov_len = buflen;
			if (writev(s, iov, 2) != sizeof(len) + buflen) {
				(void) close(s);
				s = -1;
				continue;
			}
			status = 0;
			while (s != -1 && soacnt < 2 && status != -2) {
				if ((status =
				     hs_readresp(s, answer, anslen)) == -1) {
					(void) close(s);
					s = -1;
					continue;
				}
			}
			if (status == -2) {
				/* There was a permanent error transfering this
				   zone.  Give up. */
				if (s != -1) {
					(void) close(s);
					s = -1;
				}
				return(-1);
			}
			if (s == -1)
				continue;
			return (0);
		}
	}
	if (errno == 0)
		errno = ETIMEDOUT;
	return (-1);
}

/* Returns:
   0: Success
   -1: Error
   -2: Permanent failure
*/
hs_readresp(s, answer, anslen)
int s;
char *answer;
int anslen;
{
	register int len, n;
	char *cp;

	cp = answer;
	len = sizeof(short);
	while (len != 0 &&
	       (n = hs_res_vcread(s, (char *)cp, (int)len, &hs_timeout)) > 0) {
		cp += n;
		len -= n;
	}
	if (n <= 0)
		return(-1);
	cp = answer;
	if ((len = _getshort(cp)) > anslen) {
#ifdef DEBUG
		dlog("hs_readresp: response too long: %d", len);
#endif
		return(-1);
	}
	while (len != 0 &&
	       (n = hs_res_vcread(s, (char *)cp, (int)len, &hs_timeout)) > 0) {
		cp += n;
		len -= n;
	}
	if (n <= 0)
		return(-1);
	return(hs_parse(answer, answer+PACKETSZ));
}

hs_res_vcread(sock, buf, buflen, timeout)
int sock, buflen;
char *buf;
struct timeval *timeout;
{
	register int n;

	if ((n = hs_res_selwait(sock, timeout)) > 0)
		return(read(sock, buf, buflen));
	else
		return(n);
}

hs_res_selwait(sock, timeout)
int sock;
struct timeval *timeout;
{
	fd_set dsmask;
	register int n;

	/*
	 * Wait for reply
	 */
	FD_ZERO(&dsmask);
	FD_SET(sock, &dsmask);
	n = select(sock+1, &dsmask, (fd_set *)NULL,
		   (fd_set *)NULL, timeout);
	return(n);
}

/* Returns:
   0: Success
   -1: Error
   -2: Permanent failure
*/
hs_parse(msg, eom)
char *msg, *eom;
{
	register char *cp;
	register HEADER *hp;
	register int n, len;
	int qdcount, ancount;
	char key[PACKETSZ];
	char *key_cpy, *value, *hs_make_value();
	short type;

	hp = (HEADER *)msg;
	if (hp->rcode != NOERROR || hp->opcode != QUERY) {
		char dq[20];
#ifdef DEBUG
		dlog("Bad response (%d) from nameserver %s", hp->rcode, inet_dquad(dq, hs_server_addr(servernum)->s_addr));
#endif DEBUG
		return(-1);
	}
	cp = msg + sizeof(HEADER);
	ancount = ntohs(hp->ancount);
	qdcount = ntohs(hp->qdcount);
	while (qdcount-- > 0)
		cp += dn_skipname(cp, eom) + QFIXEDSZ;
	if (soacnt == 0 && ancount == 0) {
		/* XXX We should look for NS records to find SOA */
#ifdef DEBUG
		dlog("No SOA found");
#endif
		return(-2);
	}
	while (ancount-- > 0 && cp < eom) {
		if ((n = dn_expand(msg, eom, cp, key, PACKETSZ)) < 0)
			break;
		cp += n;
		if ((type = _getshort(cp)) == T_SOA) {
			soacnt++;
		}
		cp += 2*sizeof(u_short) + sizeof(u_long);
		len = _getshort(cp);
		cp += sizeof(u_short);
		/* Check to see if key is in our domain */
		if (type == T_TXT && hs_strip_our_domain(key)) {
			value = hs_make_value(cp, len);
			if (value == NULL)
				return(-1);
			key_cpy = strdup(key);
#ifdef DEBUG
			dlog("hs_parse: Parsed key: %s, value: %s", key,
			     value);
#endif
			mapc_add_kv(hs_map, key_cpy, value);
		}
		cp += len;
		errno = 0;
	}
	return(0);
}

/* Check to see if the domain name in the supplied argument matches
   hs_domain.  Strip hs_domain from supplied argument if so. */
hs_strip_our_domain(name)
char *name;
{
	char *end_pos;
	short targ_len, cur_len;
	
	targ_len = strlen(hs_domain);
	cur_len = strlen(name);
	if (cur_len <= targ_len)
		return(0);
	end_pos = &name[cur_len - targ_len];
	if (strcmp(end_pos, hs_domain) != 0)
		return(0);
	if (*--end_pos != '.')
		return(0);
	*end_pos = '\0';
	return(1);
}

#define MAXDATA 8*1024

char *
hs_make_value(cp, len)
char *cp;
int len;
{
	char *value, *cpcpy, *valuep;
	int cnt, nextcnt, totalcnt, lencpy;
#ifdef DEBUG
	char *dbgname;

	dbgname = &cp[1];
#endif DEBUG

	lencpy = len;
	cpcpy = cp;
	totalcnt = 0;
	cnt = *cpcpy++;
	while (cnt) {
		totalcnt += cnt;
		lencpy -= cnt+1;
		if (lencpy == 0)
			break;
		nextcnt = cpcpy[cnt];
		cpcpy = &cpcpy[cnt+1];
		cnt = nextcnt;
	}
	if (totalcnt < 1 || totalcnt > MAXDATA || totalcnt > len) {
#ifdef DEBUG
		dlog("TXT RR not of expected length (%d %d): %s", totalcnt,
		     len, dbgname);
#endif DEBUG
		return(NULL);
	}
	/* Allocate null terminated string */
	value = (char *) xmalloc(totalcnt+1);
	value[totalcnt] = '\0';
	cnt = *cp++;
	valuep = value;
	while (cnt) {
		bcopy(cp, valuep, cnt);
		len -= cnt+1;
		if (len == 0)
			break;
		valuep = &valuep[cnt];
		nextcnt = cp[cnt];
		cp = &cp[cnt+1];
		cnt = nextcnt;
	}
	return(value);
}

hs_make_ns_query(domain, ansbuf)
char *domain;
char *ansbuf;
{
	int status, len;
	char buf[PACKETSZ];

	if ((len = res_mkquery(QUERY, domain, C_HS, T_NS,
			       (char *)NULL, 0, NULL, buf, PACKETSZ)) == -1) {
#ifdef DEBUG
		dlog("hs_get_ns_list: res_mkquery failed");
#endif
		errno = 0;
		return(-1);
	}
	if ((status = res_send(buf, len, (char *)ansbuf, PACKETSZ)) == -1) {
#ifdef DEBUG
	    dlog("hs_get_ns_list: res_send failed.  status %d errno %d",
		 status, errno);
#endif
		errno = 0;
		return(-1);
	}
	return(0);
}

static void
add_address(addr)
struct in_addr *addr;
{
	char dq[20];
	bcopy((char *)addr, nsaddr_list[hs_nscount++], sizeof(struct in_addr));
#ifdef DEBUG
	dlog("Adding NS address %s", inet_dquad(dq, addr->s_addr));
#endif DEBUG
}

hs_get_ns_list(domain)
char *domain;
{
	register HEADER *hp;
	int qdcount, nscount;
	register char *cp;
	register int n, len;
	char key[PACKETSZ], name[PACKETSZ], msg[PACKETSZ], *eom;
	register long **hptr;
	struct hostent *ghp;
	int numns;
	char nsname[MAXHSNS][MAXDATA];
	int nshaveaddr[MAXHSNS], i;
	short type;

	if (hs_make_ns_query(domain, msg) == -1)
		return(-1);
	numns = hs_nscount = 0;
	eom = &msg[PACKETSZ];
	bzero(nsname, sizeof(nsname));
	hp = (HEADER *)msg;
	if (hp->rcode != NOERROR || hp->opcode != QUERY) {
#ifdef DEBUG
		dlog("Bad response (%d) from nameserver %#x", hp->rcode,
		      hs_server_addr(servernum)->s_addr);
#endif DEBUG
		return(-1);
	}
	cp = msg + sizeof(HEADER);
	qdcount = ntohs(hp->qdcount);
	while (qdcount-- > 0)
		cp += dn_skipname(cp, eom) + QFIXEDSZ;
	nscount = ntohs(hp->ancount) + ntohs(hp->nscount) + ntohs(hp->arcount);
#ifdef DEBUG
	dlog("hs_get_ns_list: Processing %d response records", nscount);
#endif
	for (;nscount; nscount--) {
		if ((n = dn_expand(msg, eom, cp, key, PACKETSZ)) < 0)
			break;
		cp += n;
		type = _getshort(cp);
		cp += 2*sizeof(u_short) + sizeof(u_long);
		len = _getshort(cp);
		cp += sizeof(u_short);
#ifdef DEBUG
		dlog("hs_get_ns_list: Record type: %d", type);
#endif
		switch (type) {
		case T_NS:
			if (numns >= MAXHSNS || strcasecmp(domain, key) != 0)
				break;
			if ((n = dn_expand(msg, eom, cp, name, PACKETSZ)) < 0)
				break;
#ifdef DEBUG
			dlog("hs_get_ns_list: NS name: %s", name);
#endif
			for (i = 0; i < numns; i++)
				if (strcasecmp(nsname[i], name) == 0)
					break;
			if (i == numns) {
#ifdef DEBUG
				dlog("hs_get_ns_list: Saving name %s", name);
#endif
				strncpy(nsname[numns], name, MAXDATA);
				nshaveaddr[numns] = 0;
				numns++;
			}
			break;
		case T_A:
			if (hs_nscount == MAX_NSADDR)
				break;
			for (i = 0; i < numns; i++) {
				if (strcasecmp(nsname[i], domain) == 0) {
					nshaveaddr[i]++;
					add_address((struct in_addr *) cp);
					break;
				}
			}
			break;
		default:
			break;
		}
		if (hs_nscount == MAX_NSADDR)
			break;
		cp += len;
		errno = 0;
	}
#ifdef  DEBUG
	dlog("hs_get_ns_list: Found %d NS records", numns);
#endif
	for (i = 0; i < numns; i++) {
		if (nshaveaddr[i])
			continue;
		if ((ghp = gethostbyname(nsname[i])) == 0)
			continue;
		for (hptr = (long **)ghp->h_addr_list;
		     *hptr && hs_nscount < MAX_NSADDR; hptr++) {
			add_address((struct in_addr *) *hptr);
		}
	}
	if (hs_nscount)
		return(0);
#ifdef DEBUG
	dlog("No NS records found for %s", domain);
	return(-1);
#endif DEBUG
}
#endif /* HAS_HESIOD_RELOAD */
E 2
#endif /* HAS_HESIOD_MAPS */
E 1
