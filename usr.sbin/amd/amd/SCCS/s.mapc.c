h52295
s 00002/00002/00886
d D 8.1 93/06/06 11:40:23 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00887
d D 5.7 93/05/22 02:33:55 pendry 7 6
c fix warning about regexec
e
s 00005/00004/00883
d D 5.6 92/07/30 16:41:29 bostic 6 5
c header corruption
e
s 00009/00005/00878
d D 5.5 92/02/09 08:48:28 pendry 5 4
c merge in new release
e
s 00003/00003/00880
d D 5.4 91/05/12 16:16:49 pendry 4 3
c fixed regerror type
e
s 00003/00002/00880
d D 5.3 91/05/12 15:55:36 pendry 3 2
c checkpoint for network tape
e
s 00410/00108/00472
d D 5.2 91/03/17 13:33:26 pendry 2 1
c from amd5.3 alpha11
e
s 00580/00000/00000
d D 5.1 90/06/29 12:01:08 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 6
/*
E 6
I 6
/*-
E 6
D 2
 * $Id: mapc.c,v 5.2 90/06/23 22:19:37 jsp Rel $
E 2
I 2
D 3
 * $Id: mapc.c,v 5.2.1.7 91/03/17 17:46:52 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
D 5
 *	%W% (Berkeley) %G%
E 5
I 5
D 6
 *	@(#)mapc.c	1.2 (Berkeley) 6/25/91
E 5
I 3
 *
E 6
D 5
 * $Id: mapc.c,v 5.2.1.9 91/05/07 22:18:07 jsp Alpha $
E 5
I 5
 * $Id: mapc.c,v 5.2.2.1 1992/02/09 15:08:38 jsp beta $
E 5
D 6
 *
E 6
E 3
 */
I 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

/*
 * Mount map cache
 */

#include "am.h"
I 2
#ifdef HAS_REGEXP
#include RE_HDR
#endif
E 2

/*
 * Hash table size
 */
#define	NKVHASH	(1 << 2)		/* Power of two */

/*
 * Wildcard key
 */
static char wildcard[] = "*";

/*
 * Map cache types
D 2
 * default, none, incremental, all
E 2
I 2
 * default, none, incremental, all, regexp
 * MAPC_RE implies MAPC_ALL and must be numerically
 * greater.
E 2
 */
D 2
#define	MAPC_DFLT	-1
#define	MAPC_NONE	0
#define	MAPC_INC	1
#define	MAPC_ALL	2
E 2
I 2
#define	MAPC_DFLT	0x000
#define	MAPC_NONE	0x001
#define	MAPC_INC	0x002
#define	MAPC_ROOT	0x004
#define	MAPC_ALL	0x010
#ifdef HAS_REGEXP
#define MAPC_RE		0x020
#define	MAPC_ISRE(m) ((m)->alloc == MAPC_RE)
#else
#define MAPC_ISRE(m) FALSE
#endif
#define	MAPC_CACHE_MASK	0x0ff
#define	MAPC_SYNC	0x100
E 2

I 2
static struct opt_tab mapc_opt[] = {
	{ "all", MAPC_ALL },
	{ "default", MAPC_DFLT },
	{ "inc", MAPC_INC },
	{ "mapdefault", MAPC_DFLT },
	{ "none", MAPC_NONE },
I 5
#ifdef HAS_REGEXP
E 5
	{ "re", MAPC_RE },
	{ "regexp", MAPC_RE },
I 5
#endif
E 5
	{ "sync", MAPC_SYNC },
	{ 0, 0 }
};

E 2
/*
D 2
 * Do a map reload
E 2
I 2
 * Lookup recursion
E 2
 */
D 2
#define mapc_reload_map(m) \
	((*(m)->reload)(m, m->map_name, mapc_add_kv))
E 2
I 2
#define	MREC_FULL	2
#define	MREC_PART	1
#define	MREC_NONE	0
E 2

/*
 * Cache map operations
 */
typedef void add_fn P((mnt_map*, char*, char*));
D 2
typedef int init_fn P((char*));
E 2
I 2
typedef int init_fn P((char*, time_t*));
E 2
typedef int search_fn P((mnt_map*, char*, char*, char**, time_t*));
typedef int reload_fn P((mnt_map*, char*, add_fn*));
I 2
typedef int mtime_fn P((char*, time_t*));
E 2

static void mapc_sync P((mnt_map*));

/*
 * Map type
 */
typedef struct map_type map_type;
struct map_type {
	char *name;			/* Name of this map type */
	init_fn *init;			/* Initialisation */
	reload_fn *reload;		/* Reload or fill */
	search_fn *search;		/* Search for new entry */
I 2
	mtime_fn *mtime;		/* Find modify time */
E 2
	int def_alloc;			/* Default allocation mode */
};

/*
 * Key-value pair
 */
typedef struct kv kv;
struct kv {
	kv *next;
	char *key;
	char *val;
};

struct mnt_map {
	qelem hdr;
	int refc;			/* Reference count */
D 2
	int alloc;			/* Allocation mode */
E 2
I 2
	short flags;			/* Allocation flags */
	short alloc;			/* Allocation mode */
E 2
	time_t modify;			/* Modify time of map */
	char *map_name;			/* Name of this map */
	char *wildcard;			/* Wildcard value */
	reload_fn *reload;		/* Function to be used for reloads */
	search_fn *search;		/* Function to be used for searching */
I 2
	mtime_fn *mtime;		/* Modify time function */
E 2
	kv *kvhash[NKVHASH];		/* Cached data */
};

/*
 * Map for root node
 */
static mnt_map *root_map;

/*
 * List of known maps
 */
extern qelem map_list_head;
qelem map_list_head = { &map_list_head, &map_list_head };

/*
 * Configuration
 */
 
/* ROOT MAP */
D 2
static int root_init P((char*));
E 2
I 2
static int root_init P((char*, time_t*));
E 2

/* FILE MAPS */
#ifdef HAS_FILE_MAPS
D 2
extern int file_init P((char*));
E 2
I 2
extern int file_init P((char*, time_t*));
E 2
extern int file_reload P((mnt_map*, char*, add_fn*));
extern int file_search P((mnt_map*, char*, char*, char**, time_t*));
I 2
extern int file_mtime P((char*, time_t*));
E 2
#endif /* HAS_FILE_MAPS */

/* Network Information Service (NIS) MAPS */
#ifdef HAS_NIS_MAPS
D 2
extern int nis_init P((char*));
E 2
I 2
extern int nis_init P((char*, time_t*));
#ifdef HAS_NIS_RELOAD
extern int nis_reload P((mnt_map*, char*, add_fn*));
#else
#define nis_reload error_reload
#endif
E 2
extern int nis_search P((mnt_map*, char*, char*, char**, time_t*));
I 2
#define nis_mtime nis_init
E 2
#endif /* HAS_NIS_MAPS */

/* NDBM MAPS */
#ifdef HAS_NDBM_MAPS
#ifdef OS_HAS_NDBM
D 2
extern int ndbm_init P((char*));
E 2
I 2
extern int ndbm_init P((char*, time_t*));
E 2
extern int ndbm_search P((mnt_map*, char*, char*, char**, time_t*));
I 2
#define ndbm_mtime ndbm_init
E 2
#endif /* OS_HAS_NDBM */
#endif /* HAS_NDBM_MAPS */

/* PASSWD MAPS */
#ifdef HAS_PASSWD_MAPS
D 2
extern int passwd_init P((char*));
E 2
I 2
extern int passwd_init P((char*, time_t*));
E 2
extern int passwd_search P((mnt_map*, char*, char*, char**, time_t*));
#endif /* HAS_PASSWD_MAPS */

/* HESIOD MAPS */
#ifdef HAS_HESIOD_MAPS
D 2
extern int hesiod_init P((char*));
E 2
I 2
extern int hesiod_init P((char*, time_t*));
#ifdef HAS_HESIOD_RELOAD
extern int hesiod_reload P((mnt_map*, char*, add_fn*));
#else
#define hesiod_reload error_reload
#endif
E 2
extern int hesiod_search P((mnt_map*, char*, char*, char**, time_t*));
#endif /* HAS_HESIOD_MAPS */

I 2
/* UNION MAPS */
#ifdef HAS_UNION_MAPS
extern int union_init P((char*, time_t*));
extern int union_search P((mnt_map*, char*, char*, char**, time_t*));
extern int union_reload P((mnt_map*, char*, add_fn*));
#endif /* HAS_UNION_MAPS */

E 2
/* ERROR MAP */
D 2
static int error_init P((char*));
E 2
I 2
static int error_init P((char*, time_t*));
E 2
static int error_reload P((mnt_map*, char*, add_fn*));
static int error_search P((mnt_map*, char*, char*, char**, time_t*));
I 2
static int error_mtime P((char*, time_t*));
E 2

static map_type maptypes[] = {
D 2
	{ "root", root_init, error_reload, error_search, MAPC_ALL },
E 2
I 2
	{ "root", root_init, error_reload, error_search, error_mtime, MAPC_ROOT },
E 2

#ifdef HAS_PASSWD_MAPS
D 2
	{ "passwd", passwd_init, error_reload, passwd_search, MAPC_INC },
#endif /* HAS_PASSWD_MAPS */
E 2
I 2
	{ "passwd", passwd_init, error_reload, passwd_search, error_mtime, MAPC_INC },
#endif
E 2

#ifdef HAS_HESIOD_MAPS
D 2
	{ "hesiod", hesiod_init, error_reload, hesiod_search, MAPC_INC },
#endif /* HAS_HESIOD_MAPS */
E 2
I 2
	{ "hesiod", hesiod_init, hesiod_reload, hesiod_search, error_mtime, MAPC_ALL },
#endif
E 2

I 2
#ifdef HAS_UNION_MAPS
	{ "union", union_init, union_reload, union_search, error_mtime, MAPC_ALL },
#endif

E 2
#ifdef HAS_NIS_MAPS
D 2
	{ "nis", nis_init, error_reload, nis_search, MAPC_INC },
#endif /* HAS_NIS_MAPS */
E 2
I 2
	{ "nis", nis_init, nis_reload, nis_search, nis_mtime, MAPC_INC },
#endif
E 2

#ifdef HAS_NDBM_MAPS
D 2
	{ "ndbm", ndbm_init, error_reload, ndbm_search, MAPC_INC },
#endif /* HAS_NDBM_MAPS */
E 2
I 2
	{ "ndbm", ndbm_init, error_reload, ndbm_search, ndbm_mtime, MAPC_INC },
#endif
E 2

#ifdef HAS_FILE_MAPS
D 2
	{ "file", file_init, file_reload, file_search, MAPC_ALL },
#endif /* HAS_FILE_MAPS */
E 2
I 2
	{ "file", file_init, file_reload, file_search, file_mtime, MAPC_ALL },
#endif
E 2

D 2
	{ "error", error_init, error_reload, error_search, MAPC_NONE },
E 2
I 2
	{ "error", error_init, error_reload, error_search, error_mtime, MAPC_NONE },
E 2
};

/*
 * Hash function
 */
I 2
static unsigned int kvhash_of P((char *key));
E 2
static unsigned int kvhash_of(key)
char *key;
{
	unsigned int i, j;

	for (i = 0; j = *key++; i += j)
		;

	return i % NKVHASH;
}

I 2
void mapc_showtypes P((FILE *fp));
E 2
void mapc_showtypes(fp)
FILE *fp;
{
	map_type *mt;
	char *sep = "";
	for (mt = maptypes; mt < maptypes+sizeof(maptypes)/sizeof(maptypes[0]); mt++) {
		fprintf(fp, "%s%s", sep, mt->name);
		sep = ", ";
	}
}

I 2
D 4
static char *reg_error = "?";
void regerror P((char *m));
E 4
I 4
D 5
static const char *reg_error = "?";
void regerror P((const char *m));
E 5
I 5
static Const char *reg_error = "?";
void regerror P((Const char *m));
E 5
E 4
void regerror(m)
D 4
char *m;
E 4
I 4
D 5
const char *m;
E 5
I 5
Const char *m;
E 5
E 4
{
	reg_error = m;
}

E 2
/*
 * Add key and val to the map m.
 * key and val are assumed to be safe copies
 */
I 2
void mapc_add_kv P((mnt_map *m, char *key, char *val));
E 2
void mapc_add_kv(m, key, val)
mnt_map *m;
char *key;
char *val;
{
D 2
	kv **h = &m->kvhash[kvhash_of(key)];
	kv *n = ALLOC(kv);
E 2
I 2
	kv **h;
	kv *n;
	int hash = kvhash_of(key);

#ifdef DEBUG
	dlog("add_kv: %s -> %s", key, val);
#endif

#ifdef HAS_REGEXP
	if (MAPC_ISRE(m)) {
		char keyb[MAXPATHLEN];
		regexp *re;
		/*
		 * Make sure the string is bound to the start and end
		 */
		sprintf(keyb, "^%s$", key);
		re = regcomp(keyb);
		if (re == 0) {
			plog(XLOG_USER, "error compiling RE \"%s\": %s", keyb, reg_error);
			return;
		} else {
			free(key);
			key = (char *) re;
		}
	}
#endif

	h = &m->kvhash[hash];
	n = ALLOC(kv);
E 2
	n->key = key;
	n->val = val;
	n->next = *h;
	*h = n;
}

I 2
void mapc_repl_kv P((mnt_map *m, char *key, char *val));
void mapc_repl_kv(m, key, val)
mnt_map *m;
char *key;
char *val;
{
	kv *k;

	/*
	 * Compute the hash table offset
	 */
	k = m->kvhash[kvhash_of(key)];

	/*
	 * Scan the linked list for the key
	 */
	while (k && !FSTREQ(k->key, key))
		k = k->next;

	if (k) {
		free(k->val);
		k->val = val;
	} else {
		mapc_add_kv(m, key, val);
	}

}

/*
 * Search a map for a key.
 * Calls map specific search routine.
 * While map is out of date, keep re-syncing.
 */
static int search_map P((mnt_map *m, char *key, char **valp));
E 2
static int search_map(m, key, valp)
mnt_map *m;
char *key;
char **valp;
{
	int rc;
	do {
		rc = (*m->search)(m, m->map_name, key, valp, &m->modify);
		if (rc < 0) {
			plog(XLOG_MAP, "Re-synchronizing cache for map %s", m->map_name);
			mapc_sync(m);
		}
	} while (rc < 0);

	return rc;
}

/*
 * Do a wildcard lookup in the map and
 * save the result.
 */
I 2
static void mapc_find_wildcard P((mnt_map *m));
E 2
static void mapc_find_wildcard(m)
mnt_map *m;
{
	/*
	 * Attempt to find the wildcard entry
	 */
	int rc = search_map(m, wildcard, &m->wildcard);

	if (rc != 0)
		m->wildcard = 0;
}

/*
 * Make a duplicate reference to an existing map
 */
#define mapc_dup(m) ((m)->refc++, (m))

/*
I 2
 * Do a map reload
 */
static int mapc_reload_map(m)
mnt_map *m;
{
	int error;
#ifdef DEBUG
	dlog("calling map reload on %s", m->map_name);
#endif
	error = (*m->reload)(m, m->map_name, mapc_add_kv);
	if (error)
		return error;
	m->wildcard = 0;
#ifdef DEBUG
	dlog("calling mapc_search for wildcard");
#endif
	error = mapc_search(m, wildcard, &m->wildcard);
	if (error)
		m->wildcard = 0;
	return 0;
}

/*
E 2
 * Create a new map
 */
I 2
static mnt_map *mapc_create P((char *map, char *opt));
E 2
static mnt_map *mapc_create(map, opt)
char *map;
char *opt;
{
	mnt_map *m = ALLOC(mnt_map);
	map_type *mt;
D 2
	int alloc = STREQ(opt, "all") ? MAPC_ALL :
		    (STREQ(opt, "inc") ? MAPC_INC :
		    ((STREQ(opt, "default") || STREQ(opt, "mapdefault")) ? MAPC_DFLT :
		    MAPC_NONE));
E 2
I 2
	time_t modify;
	int alloc = 0;
E 2

I 2
	(void) cmdoption(opt, mapc_opt, &alloc);

E 2
	for (mt = maptypes; mt < maptypes+sizeof(maptypes)/sizeof(maptypes[0]); mt++)
D 2
		if ((*mt->init)(map) == 0)
E 2
I 2
		if ((*mt->init)(map, &modify) == 0)
E 2
			break;
I 2
	/* assert: mt in maptypes */
E 2

I 2
	m->flags = alloc & ~MAPC_CACHE_MASK;
	alloc &= MAPC_CACHE_MASK;

	if (alloc == MAPC_DFLT)
		alloc = mt->def_alloc;
	switch (alloc) {
	default:
		plog(XLOG_USER, "Ambiguous map cache type \"%s\"; using \"inc\"", opt);
		alloc = MAPC_INC;
		/* fallthrough... */
	case MAPC_NONE:
	case MAPC_INC:
	case MAPC_ROOT:
		break;
	case MAPC_ALL:
		/*
		 * If there is no support for reload and it was requested
		 * then back off to incremental instead.
		 */
		if (mt->reload == error_reload) {
			plog(XLOG_WARNING, "Map type \"%s\" does not support cache type \"all\"; using \"inc\"", mt->name);
			alloc = MAPC_INC;
		}
		break;
I 5
#ifdef HAS_REGEXP
E 5
	case MAPC_RE:
		if (mt->reload == error_reload) {
			plog(XLOG_WARNING, "Map type \"%s\" does not support cache type \"re\"", mt->name);
			mt = &maptypes[sizeof(maptypes)/sizeof(maptypes[0]) - 1];
			/* assert: mt->name == "error" */
		}
		break;
I 5
#endif
E 5
	}

E 2
#ifdef DEBUG
	dlog("Map for %s coming from maptype %s", map, mt->name);
D 2
#endif /* DEBUG */
	/*
	 * If there is no support for reload and it was requested
	 * then back off to incremental instead.
	 */
	if (mt->reload == error_reload && alloc == MAPC_ALL && mt->def_alloc != MAPC_ALL) {
		plog(XLOG_WARNING, "Map type \"%s\" does not support cache type \"all\"",
					mt->name);
		alloc = MAPC_INC;
	} else if (alloc == MAPC_DFLT)
		alloc = mt->def_alloc;
E 2
I 2
#endif

E 2
	m->alloc = alloc;
	m->reload = mt->reload;
D 2
	m->modify = clocktime();
	m->search = alloc == MAPC_ALL ? error_search : mt->search;
E 2
I 2
	m->modify = modify;
	m->search = alloc >= MAPC_ALL ? error_search : mt->search;
	m->mtime = mt->mtime;
E 2
	bzero((voidp) m->kvhash, sizeof(m->kvhash));
	m->map_name = strdup(map);
	m->refc = 1;
I 2
	m->wildcard = 0;

E 2
	/*
D 2
	 * Attempt to find the wildcard entry
E 2
I 2
	 * synchronize cache with reality
E 2
	 */
D 2
	mapc_find_wildcard(m);
E 2
I 2
	mapc_sync(m);
E 2

D 2
	if (alloc == MAPC_ALL) {
		/*
		 * If cache all is specified then load the cache
		 */
		if (mapc_reload_map(m)) {
			/*
			 * If that doesn't work then fallback to
			 * incremental cache mode
			 */
			m->alloc = MAPC_INC;
		}
	}
E 2
	return m;
}

/*
 * Free the cached data in a map
 */
I 2
static void mapc_clear P((mnt_map *m));
E 2
static void mapc_clear(m)
mnt_map *m;
{
	int i;

	/*
	 * For each of the hash slots, chain
	 * along free'ing the data.
	 */
	for (i = 0; i < NKVHASH; i++) {
		kv *k = m->kvhash[i];
		while (k) {
			kv *n = k->next;
D 2
			free(k->key);
E 2
I 2
			free((voidp) k->key);
E 2
			if (k->val)
D 2
				free(k->val);
			free(k);
E 2
I 2
				free((voidp) k->val);
			free((voidp) k);
E 2
			k = n;
		}
	}
	/*
	 * Zero the hash slots
	 */
	bzero((voidp) m->kvhash, sizeof(m->kvhash));
	/*
	 * Free the wildcard if it exists
	 */
	if (m->wildcard) {
		free(m->wildcard);
		m->wildcard = 0;
	}
}

/*
 * Find a map, or create one if it does not exist
 */
I 2
mnt_map *mapc_find P((char *map, char *opt));
E 2
mnt_map *mapc_find(map, opt)
char *map;
char *opt;
{
	mnt_map *m;

	/*
	 * Search the list of known maps to see if
	 * it has already been loaded.  If it is found
	 * then return a duplicate reference to it.
	 * Otherwise make a new map as required and
	 * add it to the list of maps
	 */
	ITER(m, mnt_map, &map_list_head)
		if (STREQ(m->map_name, map))
			return mapc_dup(m);

	m = mapc_create(map, opt);
	ins_que(&m->hdr, &map_list_head);
	return m;
}

/*
 * Free a map.
 */
I 2
void mapc_free P((mnt_map *m));
E 2
void mapc_free(m)
mnt_map *m;
{
	/*
	 * Decrement the reference count.
	 * If the reference count hits zero
	 * then throw the map away.
	 */
D 2
	if (--m->refc == 0) {
E 2
I 2
	if (m && --m->refc == 0) {
E 2
		mapc_clear(m);
D 2
		free(m->map_name);
E 2
I 2
		free((voidp) m->map_name);
E 2
		rem_que(&m->hdr);
D 2
		free(m);
E 2
I 2
		free((voidp) m);
E 2
	}
}

/*
 * Search the map for the key.
 * Put a safe copy in *pval or return
 * an error code
 */
D 2
int mapc_search(m, key, pval)
E 2
I 2
int mapc_meta_search P((mnt_map *m, char *key, char **pval, int recurse));
int mapc_meta_search(m, key, pval, recurse)
E 2
mnt_map *m;
char *key;
char **pval;
I 2
int recurse;
E 2
{
	int error = 0;
D 2
	kv *k;
E 2
I 2
	kv *k = 0;
E 2

	/*
D 2
	 * Compute the hash table offset
E 2
I 2
	 * Firewall
E 2
	 */
D 2
	k = m->kvhash[kvhash_of(key)];
E 2
I 2
	if (!m) {
		plog(XLOG_ERROR, "Null map request for %s", key);
		return ENOENT;
	}
E 2

D 2
	/*
	 * Scan the linked list for the key
	 */
	while (k && !FSTREQ(k->key, key))
		k = k->next;
E 2
I 2
	if (m->flags & MAPC_SYNC) {
		/*
		 * Get modify time...
		 */
		time_t t;
		error = (*m->mtime)(m->map_name, &t);
		if (error || t > m->modify) {
			m->modify = t;
			plog(XLOG_INFO, "Map %s is out of date", m->map_name);
			mapc_sync(m);
		}
	}
E 2

I 2
	if (!MAPC_ISRE(m)) {
		/*
		 * Compute the hash table offset
		 */
		k = m->kvhash[kvhash_of(key)];

		/*
		 * Scan the linked list for the key
		 */
		while (k && !FSTREQ(k->key, key)) k = k->next;

	}
#ifdef HAS_REGEXP
	else if (recurse == MREC_FULL) {
		/*
		 * Try for an RE match against the entire map.
		 * Note that this will be done in a "random"
		 * order.
		 */

		int i;

		for (i = 0; i < NKVHASH; i++) {
			k = m->kvhash[i];
			while (k) {
D 7
				if (regexec(k->key, key))
E 7
I 7
				if (regexec((regexp *) k->key, key))
E 7
					break;
				k = k->next;
			}
			if (k)
				break;
		}
	}
#endif

E 2
	/*
	 * If found then take a copy
	 */
	if (k) {
		if (k->val)
			*pval = strdup(k->val);
		else
			error = ENOENT;
D 2
	} else if (m->alloc == MAPC_ALL) {
E 2
I 2
	} else if (m->alloc >= MAPC_ALL) {
E 2
		/*
		 * If the entire map is cached then this
		 * key does not exist.
		 */
		error = ENOENT;
	} else {
		/*
		 * Otherwise search the map.  If we are
		 * in incremental mode then add the key
		 * to the cache.
		 */
		error = search_map(m, key, pval);
		if (!error && m->alloc == MAPC_INC)
			mapc_add_kv(m, strdup(key), strdup(*pval));
	}

	/*
	 * If an error, and a wildcard exists,
	 * and the key is not internal then
	 * return a copy of the wildcard.
	 */
D 2
	if (error && m->wildcard && *key != '/') {
		*pval = strdup(m->wildcard);
		return 0;
E 2
I 2
	if (error > 0) {
		if (recurse == MREC_FULL && !MAPC_ISRE(m)) {
			char wildname[MAXPATHLEN];
			char *subp;
			if (*key == '/')
				return error;
			/*
			 * Keep chopping sub-directories from the RHS
			 * and replacing with "/ *" and repeat the lookup.
			 * For example:
			 * "src/gnu/gcc" -> "src / gnu / *" -> "src / *"
			 */
			strcpy(wildname, key);
			while (error && (subp = strrchr(wildname, '/'))) {
				strcpy(subp, "/*");
#ifdef DEBUG
				dlog("mapc recurses on %s", wildname);
#endif
				error = mapc_meta_search(m, wildname, pval, MREC_PART);
				if (error)
					*subp = 0;
			}
			if (error > 0 && m->wildcard) {
				*pval = strdup(m->wildcard);
				error = 0;
			}
		}
E 2
	}

	return error;
}

I 2
int mapc_search P((mnt_map *m, char *key, char **pval));
int mapc_search(m, key, pval)
mnt_map *m;
char *key;
char **pval;
{
	return mapc_meta_search(m, key, pval, MREC_FULL);
}

/*
 * Get map cache in sync with physical representation
 */
static void mapc_sync P((mnt_map *m));
E 2
static void mapc_sync(m)
mnt_map *m;
{
D 2
	mapc_clear(m);
E 2
I 2
	if (m->alloc != MAPC_ROOT) {
		mapc_clear(m);
E 2

D 2
	if (m->alloc == MAPC_ALL)
		if (mapc_reload_map(m))
			m->alloc = MAPC_INC;
	mapc_find_wildcard(m);
E 2
I 2
		if (m->alloc >= MAPC_ALL)
			if (mapc_reload_map(m))
				m->alloc = MAPC_INC;
		/*
		 * Attempt to find the wildcard entry
		 */
		if (m->alloc < MAPC_ALL)
			mapc_find_wildcard(m);
	}
E 2
}

/*
 * Reload all the maps
D 2
 * Called when amd gets hit by a SIGHUP.
E 2
I 2
 * Called when Amd gets hit by a SIGHUP.
E 2
 */
I 2
void mapc_reload(P_void);
E 2
void mapc_reload()
{
	mnt_map *m;

	/*
	 * For all the maps,
	 * Throw away the existing information.
	 * Do a reload
	 * Find the wildcard
	 */
	ITER(m, mnt_map, &map_list_head)
		mapc_sync(m);
}

/*
 * Root map.
 * The root map is used to bootstrap amd.
 * All the require top-level mounts are added
 * into the root map and then the map is iterated
 * and a lookup is done on all the mount points.
 * This causes the top level mounts to be automounted.
 */

D 2
static int root_init(map)
E 2
I 2
static int root_init P((char *map, time_t *tp));
static int root_init(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
I 2
	*tp = clocktime();
E 2
	return strcmp(map, ROOT_MAP) == 0 ? 0 : ENOENT;
}

/*
 * Add a new entry to the root map
 *
 * dir - directory (key)
 * opts - mount options
 * map - map name
 */
I 2
void root_newmap P((char *dir, char *opts, char *map));
E 2
void root_newmap(dir, opts, map)
char *dir;
char *opts;
char *map;
{
	char str[MAXPATHLEN];

	/*
	 * First make sure we have a root map to talk about...
	 */
	if (!root_map)
D 2
		root_map = mapc_find(ROOT_MAP, "all");
E 2
I 2
		root_map = mapc_find(ROOT_MAP, "mapdefault");
E 2

	/*
	 * Then add the entry...
	 */
	dir = strdup(dir);
D 2
	sprintf(str, "cache:=none;type:=auto;fs:=\"%s\";%s", map, opts ? opts : "");
	mapc_add_kv(root_map, dir, strdup(str));
E 2
I 2
	if (map)
		sprintf(str, "cache:=mapdefault;type:=toplvl;fs:=\"%s\";%s",
			map, opts ? opts : "");
	else
		strcpy(str, opts);
	mapc_repl_kv(root_map, dir, strdup(str));
E 2
}

I 2
int mapc_keyiter P((mnt_map *m, void (*fn)(char*,voidp), voidp arg));
int mapc_keyiter(m, fn, arg)
mnt_map *m;
void (*fn)P((char*, voidp));
voidp arg;
{
	int i;
	int c = 0;

	for (i = 0; i < NKVHASH; i++) {
		kv *k = m->kvhash[i];
		while (k) {
			(*fn)(k->key, arg);
			k = k->next;
			c++;
		}
	}

	return c;
}

E 2
/*
 * Iterate of the the root map
 * and call (*fn)() on the key
 * of all the nodes.
 * Finally throw away the root map.
 */
D 2
int root_keyiter(fn)
void (*fn)P((char*));
E 2
I 2
int root_keyiter P((void (*fn)(char*,voidp), voidp arg));
int root_keyiter(fn, arg)
void (*fn)P((char*,voidp));
voidp arg;
E 2
{
D 2
	int i;
	int c = 0;

E 2
	if (root_map) {
D 2
		for (i = 0; i < NKVHASH; i++) {
			kv *k = root_map->kvhash[i];
			while (k) {
				(*fn)(k->key);
				k = k->next;
				c++;
			}
		}
E 2
I 2
		int c = mapc_keyiter(root_map, fn, arg);
#ifdef notdef
E 2
		mapc_free(root_map);
		root_map = 0;
I 2
#endif
		return c;
E 2
	}
D 2
	return c;
E 2
I 2
	return 0;
E 2
}

/*
 * Error map
 */
D 2
static int error_init(map)
E 2
I 2
static int error_init P((char *map, time_t *tp));
static int error_init(map, tp)
E 2
char *map;
I 2
time_t *tp;
E 2
{
I 2
	plog(XLOG_USER, "No source data for map %s", map);
	*tp = 0;
E 2
	return 0;
}

/*ARGSUSED*/
I 2
static int error_search P((mnt_map *m, char *map, char *key, char **pval, time_t *tp));
E 2
static int error_search(m, map, key, pval, tp)
mnt_map *m;
char *map;
char *key;
char **pval;
time_t *tp;
{
	return ENOENT;
}

/*ARGSUSED*/
I 2
static int error_reload P((mnt_map *m, char *map, add_fn *fn));
E 2
static int error_reload(m, map, fn)
mnt_map *m;
char *map;
add_fn *fn;
{
	return ENOENT;
I 2
}

static int error_mtime P((char *map, time_t *tp));
static int error_mtime(map, tp)
char *map;
time_t *tp;
{
	*tp = 0;
	return 0;
E 2
}
E 1
