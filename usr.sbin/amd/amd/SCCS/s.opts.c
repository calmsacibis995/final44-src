h41368
s 00002/00002/00807
d D 8.1 93/06/06 11:40:56 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00804
d D 5.6 92/08/01 15:58:23 bostic 6 5
c header corruption
e
s 00005/00004/00803
d D 5.5 92/05/31 10:42:23 pendry 5 4
c code refresh
e
s 00013/00004/00794
d D 5.4 92/02/09 08:48:50 pendry 4 3
c merge in new release
e
s 00004/00003/00794
d D 5.3 91/05/12 15:55:55 pendry 3 2
c checkpoint for network tape
e
s 00093/00045/00704
d D 5.2 91/03/17 13:33:41 pendry 2 1
c from amd5.3 alpha11
e
s 00749/00000/00000
d D 5.1 90/06/29 12:01:14 mckusick 1 0
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
 * $Id: opts.c,v 5.2 90/06/23 22:19:51 jsp Rel $
E 2
I 2
D 3
 * $Id: opts.c,v 5.2.1.5 91/03/17 17:45:34 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
D 4
 *	%W% (Berkeley) %G%
E 4
I 4
D 6
 *	@(#)opts.c	1.3 (Berkeley) 6/26/91
E 4
I 3
 *
E 6
D 4
 * $Id: opts.c,v 5.2.1.7 91/05/07 22:18:24 jsp Alpha $
E 4
I 4
D 5
 * $Id: opts.c,v 5.2.2.1 1992/02/09 15:08:54 jsp beta $
E 5
I 5
 * $Id: opts.c,v 5.2.2.3 1992/05/31 16:34:13 jsp Exp $
E 5
E 4
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

#include "am.h"

D 3
extern char *getenv P((char *));
E 3
I 3
extern char *getenv P((const char *));
E 3

/*
 * static copy of the options with
 * which to play
 */
static struct am_opts fs_static;

static char *opt_host = hostname;
static char *opt_hostd = hostd;
static char nullstr[] = "";
static char *opt_key = nullstr;
static char *opt_map = nullstr;
static char *opt_path = nullstr;

static char *vars[8];

/*
 * Length of longest option name
 */
D 2
#define	NLEN	16
E 2
I 2
#define	NLEN	16	/* conservative */
E 2
#define S(x) (x) , (sizeof(x)-1)
static struct opt {
	char *name;		/* Name of the option */
	int nlen;		/* Length of option name */
	char **optp;		/* Pointer to option value string */
	char **sel_p;		/* Pointer to selector value string */
} opt_fields[] = {
	/* Options in something corresponding to frequency of use */
	{ S("opts"), &fs_static.opt_opts, 0 },
	{ S("host"), 0, &opt_host },
	{ S("hostd"), 0, &opt_hostd },
	{ S("type"), &fs_static.opt_type, 0 },
	{ S("rhost"), &fs_static.opt_rhost, 0 },
	{ S("rfs"), &fs_static.opt_rfs, 0 },
	{ S("fs"), &fs_static.opt_fs, 0 },
	{ S("key"), 0, &opt_key },
	{ S("map"), 0, &opt_map },
	{ S("sublink"), &fs_static.opt_sublink, 0 },
	{ S("arch"), 0, &arch },
	{ S("dev"), &fs_static.opt_dev, 0 },
	{ S("pref"), &fs_static.opt_pref, 0 },
	{ S("path"), 0, &opt_path },
	{ S("autodir"), 0, &auto_dir },
	{ S("delay"), &fs_static.opt_delay, 0 },
	{ S("domain"), 0, &hostdomain },
	{ S("karch"), 0, &karch },
	{ S("cluster"), 0, &cluster },
I 2
	{ S("wire"), 0, &wire },
E 2
	{ S("byte"), 0, &endian },
	{ S("os"), 0, &op_sys },
I 4
	{ S("remopts"), &fs_static.opt_remopts, 0 },
E 4
	{ S("mount"), &fs_static.opt_mount, 0 },
	{ S("unmount"), &fs_static.opt_unmount, 0 },
	{ S("cache"), &fs_static.opt_cache, 0 },
	{ S("user"), &fs_static.opt_user, 0 },
	{ S("group"), &fs_static.opt_group, 0 },
	{ S("var0"), &vars[0], 0 },
	{ S("var1"), &vars[1], 0 },
	{ S("var2"), &vars[2], 0 },
	{ S("var3"), &vars[3], 0 },
	{ S("var4"), &vars[4], 0 },
	{ S("var5"), &vars[5], 0 },
	{ S("var6"), &vars[6], 0 },
	{ S("var7"), &vars[7], 0 },
	{ 0, 0, 0, 0 },
};

typedef struct opt_apply opt_apply;
struct opt_apply {
	char **opt;
	char *val;
};

/*
 * Specially expand the remote host name first
 */
static opt_apply rhost_expansion[] = {
	{ &fs_static.opt_rhost, "${host}" },
	{ 0, 0 },
};
/*
 * List of options which need to be expanded
 * Note that this the order here _may_ be important.
 */
static opt_apply expansions[] = {
/*	{ &fs_static.opt_dir, 0 },	*/
	{ &fs_static.opt_sublink, 0 },
	{ &fs_static.opt_rfs, "${path}" },
	{ &fs_static.opt_fs, "${autodir}/${rhost}${rfs}" },
	{ &fs_static.opt_opts, "rw" },
I 4
	{ &fs_static.opt_remopts, "${opts}" },
E 4
	{ &fs_static.opt_mount, 0 },
	{ &fs_static.opt_unmount, 0 },
	{ 0, 0 },
};

/*
 * List of options which need to be free'ed before re-use
 */
static opt_apply to_free[] = {
	{ &fs_static.fs_glob, 0 },
	{ &fs_static.fs_local, 0 },
	{ &fs_static.fs_mtab, 0 },
/*	{ &fs_static.opt_dir, 0 },	*/
	{ &fs_static.opt_sublink, 0 },
	{ &fs_static.opt_rfs, 0 },
	{ &fs_static.opt_fs, 0 },
	{ &fs_static.opt_rhost, 0 },
	{ &fs_static.opt_opts, 0 },
I 4
	{ &fs_static.opt_remopts, 0 },
E 4
	{ &fs_static.opt_mount, 0 },
	{ &fs_static.opt_unmount, 0 },
	{ &vars[0], 0 },
	{ &vars[1], 0 },
	{ &vars[2], 0 },
	{ &vars[3], 0 },
	{ &vars[4], 0 },
	{ &vars[5], 0 },
	{ &vars[6], 0 },
	{ &vars[7], 0 },
	{ 0, 0 },
};

/*
 * Skip to next option in the string
 */
static char *opt P((char**));
static char *opt(p)
char **p;
{
	char *cp = *p;
	char *dp = cp;
	char *s = cp;

top:
	while (*cp && *cp != ';') {
		if (*cp == '\"') {
			/*
			 * Skip past string
			 */
			cp++;
			while (*cp && *cp != '\"')
				*dp++ = *cp++;
			if (*cp)
				cp++;
		} else {
			*dp++ = *cp++;
		}
	}

	/*
	 * Skip past any remaining ';'s
	 */
	while (*cp == ';')
		cp++;

	/*
	 * If we have a zero length string
	 * and there are more fields, then
	 * parse the next one.  This allows
	 * sequences of empty fields.
	 */
	if (*cp && dp == s)
		goto top;

	*dp = '\0';

	*p = cp;
	return s;
}

D 2
static int eval_opts P((char*));
static int eval_opts(opts)
E 2
I 2
static int eval_opts P((char*, char*));
static int eval_opts(opts, mapkey)
E 2
char *opts;
I 2
char *mapkey;
E 2
{
	/*
	 * Fill in the global structure fs_static by
	 * cracking the string opts.  opts may be
	 * scribbled on at will.
	 */
	char *o = opts;
	char *f;

	/*
	 * For each user-specified option
	 */
	while (*(f = opt(&o))) {
		struct opt *op;
		enum vs_opt { OldSyn, SelEQ, SelNE, VarAss } vs_opt;
		char *eq = strchr(f, '=');
		char *opt;
		if (!eq || eq[1] == '\0' || eq == f) {
			/*
			 * No value, just continue
			 */
D 2
			plog(XLOG_USER, "No value component in \"%s\"", f);
E 2
I 2
			plog(XLOG_USER, "key %s: No value component in \"%s\"", mapkey, f);
E 2
			continue;
		}

		/*
		 * Check what type of operation is happening
		 * !=, =!  is SelNE
		 * == is SelEQ
		 * := is VarAss
		 * = is OldSyn (either SelEQ or VarAss)
		 */
		if (eq[-1] == '!') {		/* != */
			vs_opt = SelNE;
			eq[-1] = '\0';
			opt = eq + 1;
		} else if (eq[-1] == ':') {	/* := */
			vs_opt = VarAss;
			eq[-1] = '\0';
			opt = eq + 1;
		} else if (eq[1] == '=') {	/* == */
			vs_opt = SelEQ;
			eq[0] = '\0';
			opt = eq + 2;
		} else if (eq[1] == '!') {	/* =! */
			vs_opt = SelNE;
			eq[0] = '\0';
			opt = eq + 2;
		} else {			/* = */
			vs_opt = OldSyn;
			eq[0] = '\0';
			opt = eq + 1;
		}

		/*
		 * For each recognised option
		 */
		for (op = opt_fields; op->name; op++) {
			/*
			 * Check whether they match
			 */
			if (FSTREQ(op->name, f)) {
				switch (vs_opt) {
#if AMD_COMPAT <= 5000108
				case OldSyn:
I 2
					plog(XLOG_WARNING, "key %s: Old syntax selector found: %s=%s", mapkey, f, opt);
E 2
					if (!op->sel_p) {
						*op->optp = opt;
						break;
					}
					/* fall through ... */
#endif /* 5000108 */
				case SelEQ:
				case SelNE:
					if (op->sel_p && (STREQ(*op->sel_p, opt) == (vs_opt == SelNE))) {
D 2
						plog(XLOG_MAP, "map selector %s (=%s) did not %smatch %s",
E 2
I 2
						plog(XLOG_MAP, "key %s: map selector %s (=%s) did not %smatch %s",
							mapkey,
E 2
							op->name,
							*op->sel_p,
							vs_opt == SelNE ? "not " : "",
							opt);
						return 0;
					}
					break;

				case VarAss:
					if (op->sel_p) {
D 2
						plog(XLOG_USER, "Can't assign to a selector (%s)", op->name);
E 2
I 2
						plog(XLOG_USER, "key %s: Can't assign to a selector (%s)", mapkey, op->name);
E 2
						return 0;
					}
					*op->optp = opt;
					break;
				}
				break;
			}
		}

		if (!op->name)
D 2
			plog(XLOG_USER, "Unrecognised key \"%s\"", f);
E 2
I 2
			plog(XLOG_USER, "key %s: Unrecognised key/option \"%s\"", mapkey, f);
E 2
	}

	return 1;
}

/*
 * Free an option
 */
static void free_op P((opt_apply*, int));
/*ARGSUSED*/
static void free_op(p, b)
opt_apply *p;
int b;
{
	if (*p->opt) {
		free(*p->opt);
		*p->opt = 0;
	}
}

/*
I 2
 * Normalize slashes in the string.
 */
void normalize_slash P((char *p));
void normalize_slash(p)
char *p;
{
	char *f = strchr(p, '/');
I 5
	char *f0 = f;
E 5
	if (f) {
		char *t = f;
		do {
			/* assert(*f == '/'); */
D 4
			/* copy a single / across */
			*t++ = *f++;
E 4
I 4
D 5
			if (f == t && f[0] == '/' && f[1] == '/') {
E 5
I 5
			if (f == f0 && f[0] == '/' && f[1] == '/') {
E 5
				/* copy double slash iff first */
				*t++ = *f++;
				*t++ = *f++;
			} else {
				/* copy a single / across */
				*t++ = *f++;
			}
E 4

			/* assert(f[-1] == '/'); */
			/* skip past more /'s */
			while (*f == '/')
				f++;

			/* assert(*f != '/'); */
			/* keep copying up to next / */
D 5
			do {
E 5
I 5
			while (*f && *f != '/') {
E 5
				*t++ = *f++;
D 5
			} while (*f && *f != '/');
E 5
I 5
			}
E 5

			/* assert(*f == 0 || *f == '/'); */

		} while (*f);
		*t = 0;			/* derived from fix by Steven Glassman */
	}
}

/*
E 2
 * Macro-expand an option.  Note that this does not
 * handle recursive expansions.  They will go badly wrong.
 * If sel is true then old expand selectors, otherwise
 * don't expand selectors.
 */
static void expand_op P((opt_apply*, int));
static void expand_op(p, sel_p)
opt_apply *p;
int sel_p;
{
/*
 * The BUFSPACE macros checks that there is enough space
 * left in the expansion buffer.  If there isn't then we
 * give up completely.  This is done to avoid crashing the
 * automounter itself (which would be a bad thing to do).
 */
#define BUFSPACE(ep, len) (((ep) + (len)) < expbuf+MAXPATHLEN)
static char expand_error[] = "No space to expand \"%s\"";

	char expbuf[MAXPATHLEN+1];
	char nbuf[NLEN+1];
	char *ep = expbuf;
	char *cp = *p->opt;
	char *dp;
#ifdef DEBUG
	char *cp_orig = *p->opt;
#endif /* DEBUG */
	struct opt *op;

	while (dp = strchr(cp, '$')) {
		char ch;
		/*
		 * First copy up to the $
		 */
		{ int len = dp - cp;
		  if (BUFSPACE(ep, len)) {
			strncpy(ep, cp, len);
			ep += len;
		  } else {
			plog(XLOG_ERROR, expand_error, *p->opt);
			goto out;
		  }
		}
		cp = dp + 1;
		ch = *cp++;
		if (ch == '$') {
			if (BUFSPACE(ep, 1)) {
				*ep++ = '$';
			} else {
				plog(XLOG_ERROR, expand_error, *p->opt);
				goto out;
			}
		} else if (ch == '{') {
			/* Expansion... */
D 2
			enum { E_All, E_Dir, E_File } todo;
E 2
I 2
			enum { E_All, E_Dir, E_File, E_Domain, E_Host } todo;
E 2
			/*
			 * Find closing brace
			 */
			char *br_p = strchr(cp, '}');
			int len;
			/*
			 * Check we found it
			 */
			if (!br_p) {
				/*
				 * Just give up
				 */
				plog(XLOG_USER, "No closing '}' in \"%s\"", *p->opt);
				goto out;
			}
			len = br_p - cp;
			/*
			 * Figure out which part of the variable to grab.
			 */
			if (*cp == '/') {
				/*
				 * Just take the last component
				 */
				todo = E_File;
				cp++;
				--len;
			} else if (br_p[-1] == '/') {
				/*
				 * Take all but the last component
				 */
				todo = E_Dir;
				--len;
I 2
			} else if (*cp == '.') {
				/*
				 * Take domain name
				 */
				todo = E_Domain;
				cp++;
				--len;
			} else if (br_p[-1] == '.') {
				/*
				 * Take host name
				 */
				todo = E_Host;
				--len;
E 2
			} else {
				/*
				 * Take the whole lot
				 */
				todo = E_All;
			}
			/*
			 * Truncate if too long.  Since it won't
			 * match anyway it doesn't matter that
			 * it has been cut short.
			 */
			if (len > NLEN)
				len = NLEN;
			/*
			 * Put the string into another buffer so
			 * we can do comparisons.
			 */
			strncpy(nbuf, cp, len);
			nbuf[len] = '\0';
			/*
			 * Advance cp
			 */
			cp = br_p + 1;
			/*
			 * Search the option array
			 */
			for (op = opt_fields; op->name; op++) {
				/*
				 * Check for match
				 */
				if (len == op->nlen && STREQ(op->name, nbuf)) {
					char xbuf[NLEN+3];
					char *val;
					/*
					 * Found expansion.  Copy
					 * the correct value field.
					 */
					if (!(!op->sel_p == !sel_p)) {
						/*
						 * Copy the string across unexpanded
						 */
						sprintf(xbuf, "${%s%s%s}",
D 2
							todo == E_File ? "/" : "",
E 2
I 2
							todo == E_File ? "/" :
								todo == E_Domain ? "." : "",
E 2
							nbuf,
D 2
							todo == E_Dir ? "/" : "");
E 2
I 2
							todo == E_Dir ? "/" :
								todo == E_Host ? "." : "");
E 2
						val = xbuf;
						/*
						 * Make sure expansion doesn't
						 * munge the value!
						 */
						todo = E_All;
					} else if (op->sel_p) {
						val = *op->sel_p;
					} else {
						val = *op->optp;
					}
					if (val) {
						/*
						 * Do expansion:
						 * ${/var} means take just the last part
						 * ${var/} means take all but the last part
I 2
						 * ${.var} means take all but first part
						 * ${var.} means take just the first part
E 2
						 * ${var} means take the whole lot
						 */
						int vlen = strlen(val);
						char *vptr = val;
						switch (todo) {
						case E_Dir:
							vptr = strrchr(val, '/');
							if (vptr)
								vlen = vptr - val;
							vptr = val;
							break;
						case E_File:
							vptr = strrchr(val, '/');
							if (vptr) {
								vptr++;
								vlen = strlen(vptr);
							} else
								vptr = val;
							break;
I 2
						case E_Domain:
							vptr = strchr(val, '.');
							if (vptr) {
								vptr++;
								vlen = strlen(vptr);
							} else {
								vptr = "";
								vlen = 0;
							}
							break;
						case E_Host:
							vptr = strchr(val, '.');
							if (vptr)
								vlen = vptr - val;
							vptr = val;
							break;
						case E_All:
							break;
E 2
						}
#ifdef DEBUG
					/*dlog("Expanding \"%s\" to \"%s\"", nbuf, val);*/
#endif /* DEBUG */
						if (BUFSPACE(ep, vlen)) {
							strcpy(ep, vptr);
							ep += vlen;
						} else {
							plog(XLOG_ERROR, expand_error, *p->opt);
							goto out;
						}
					}
					/*
					 * Done with this variable
					 */
					break;
				}
			}
			/*
			 * Check that the search was succesful
			 */
			if (!op->name) {
				/*
				 * If it wasn't then scan the
				 * environment for that name
				 * and use any value found
				 */
				char *env = getenv(nbuf);
				if (env) {
					int vlen = strlen(env);

					if (BUFSPACE(ep, vlen)) {
						strcpy(ep, env);
						ep += vlen;
					} else {
						plog(XLOG_ERROR, expand_error, *p->opt);
						goto out;
					}
#ifdef DEBUG
					Debug(D_STR)
					plog(XLOG_DEBUG, "Environment gave \"%s\" -> \"%s\"", nbuf, env);
#endif /* DEBUG */
				} else {
					plog(XLOG_USER, "Unknown sequence \"${%s}\"", nbuf);
				}
			}
		} else {
			/*
			 * Error, error
			 */
			plog(XLOG_USER, "Unknown $ sequence in \"%s\"", *p->opt);
		}
	}

out:
	/*
	 * Handle common case - no expansion
	 */
	if (cp == *p->opt) {
		*p->opt = strdup(cp);
	} else {
		/*
		 * Finish off the expansion
		 */
		if (BUFSPACE(ep, strlen(cp))) {
			strcpy(ep, cp);
			/*ep += strlen(ep);*/
		} else {
			plog(XLOG_ERROR, expand_error, *p->opt);
		}

		/*
		 * Save the exansion
		 */
		*p->opt = strdup(expbuf);
	}

D 2
	/*
	 * Normalize slashes in the string.
	 */
	{ char *f = strchr(*p->opt, '/');
	  if (f) {
		char *t = f;
		do {
			/* assert(*f == '/'); */
			/* copy a single / across */
			*t++ = *f++;
E 2
I 2
	normalize_slash(*p->opt);
E 2

D 2
			/* assert(f[-1] == '/'); */
			/* skip past more /'s */
			while (*f == '/')
				f++;

			/* assert(*f != '/'); */
			/* keep copying up to next / */
			do {
				*t++ = *f++;
			} while (*f && *f != '/');

			/* assert(*f == 0 || *f == '/'); */

		} while (*f);
	  }
	}

E 2
#ifdef DEBUG
	Debug(D_STR) {
		plog(XLOG_DEBUG, "Expansion of \"%s\"...", cp_orig);
		plog(XLOG_DEBUG, "... is \"%s\"", *p->opt);
	}
#endif /* DEBUG */
}

/*
 * Wrapper for expand_op
 */
static void expand_opts P((opt_apply*, int));
static void expand_opts(p, sel_p)
opt_apply *p;
int sel_p;
{
	if (*p->opt) {
		expand_op(p, sel_p);
	} else if (p->val) {
		/*
		 * Do double expansion, remembering
		 * to free the string from the first
		 * expansion...
		 */
		char *s = *p->opt = expand_key(p->val);
		expand_op(p, sel_p);
		free(s);
	}
}

/*
 * Apply a function to a list of options
 */
static void apply_opts(op, ppp, b)
void (*op)();
opt_apply ppp[];
int b;
{
	opt_apply *pp;
	for (pp = ppp; pp->opt; pp++)
		(*op)(pp, b);
}

/*
 * Free the option table
 */
void free_opts(fo)
am_opts *fo;
{
	/*
	 * Copy in the structure we are playing with
	 */
	fs_static = *fo;

	/*
	 * Free previously allocated memory
	 */
	apply_opts(free_op, to_free, FALSE);
}

/*
 * Expand lookup key
 */
char *expand_key(key)
char *key;
{
	opt_apply oa;

	oa.opt = &key; oa.val = 0;
	expand_opts(&oa, TRUE);

	return key;
}

/*
D 2
 * Remove trailing / from a string
E 2
I 2
 * Remove trailing /'s from a string
 * unless the string is a single / (Steven Glassman)
E 2
 */
D 2
static void deslashify(s)
E 2
I 2
void deslashify P((char *s));
void deslashify(s)
E 2
char *s;
{
D 2
	if (s) {
		char *sl = strrchr(s, '/');
		if (sl && sl[1] == '\0')
E 2
I 2
	if (s && *s) {
		char *sl = s + strlen(s);
		while (*--sl == '/' && sl > s)
E 2
			*sl = '\0';
	}
}

int eval_fs_opts(fo, opts, g_opts, path, key, map)
am_opts *fo;
char *opts, *g_opts, *path, *key, *map;
{
	int ok = TRUE;

	free_opts(fo);

	/*
	 * Clear out the option table
	 */
	bzero((voidp) &fs_static, sizeof(fs_static));
	bzero((voidp) vars, sizeof(vars));
	bzero((voidp) fo, sizeof(*fo));

	/*
	 * Set key, map & path before expansion
	 */
	opt_key = key;
	opt_map = map;
	opt_path = path;

	/*
	 * Expand global options
	 */
	fs_static.fs_glob = expand_key(g_opts);

	/*
	 * Expand local options
	 */
	fs_static.fs_local = expand_key(opts);

	/*
	 * Expand default (global) options
	 */
D 2
	if (!eval_opts(fs_static.fs_glob))
E 2
I 2
	if (!eval_opts(fs_static.fs_glob, key))
E 2
		ok = FALSE;

	/*
	 * Expand local options
	 */
D 2
	if (ok && !eval_opts(fs_static.fs_local))
E 2
I 2
	if (ok && !eval_opts(fs_static.fs_local, key))
E 2
		ok = FALSE;

	/*
	 * Normalise remote host name.
	 * 1.  Expand variables
	 * 2.  Normalize relative to host tables
	 * 3.  Strip local domains from the remote host
	 *     name before using it in other expansions.
	 *     This makes mount point names and other things
	 *     much shorter, while allowing cross domain
	 *     sharing of mount maps.
	 */
	apply_opts(expand_opts, rhost_expansion, FALSE);
	if (ok && fs_static.opt_rhost && *fs_static.opt_rhost)
		host_normalize(&fs_static.opt_rhost);

	/*
	 * Macro expand the options.
	 * Do this regardless of whether we are accepting
	 * this mount - otherwise nasty things happen
	 * with memory allocation.
	 */
	apply_opts(expand_opts, expansions, FALSE);

	/*
	 * Strip trailing slashes from local pathname...
	 */
	deslashify(fs_static.opt_fs);

	/*
	 * ok... copy the data back out.
	 */
	*fo = fs_static;

	/*
	 * Clear defined options
	 */
	opt_key = opt_map = opt_path = nullstr;

	return ok;
}
E 1
