/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * G. S. Fowler
 * AT&T Bell Laboratories
 */

/*
 * make rule binding routines
 */

#include "make.h"

static struct list	*firstdir;	/* list of directories		*/
static struct list	dot;		/* current directory		*/

static TABLE		filtab;		/* file name hash table		*/

TABLE			oldtab;		/* old var value hash table	*/
TABLE			rultab;		/* rule name hash table		*/
TABLE			vartab;		/* variable name hash table	*/

static void		scandir();
static int		rstat();
static int		unique();
static struct ruleinfo	*bindbase();

extern int		scanar();
extern int		openar();
extern void		closear();

/*
 * initialize runtime static data
 */

void
init()
{
	filtab = mkhash(511, HASH_ALLOCATE, (GENERIC)0, (GENERIC)0, (GENERIC)0, "files");
	oldtab = mkhash( 32, 0, (GENERIC)0, (GENERIC)0, (GENERIC)0, "old-values");
	rultab = mkhash(511, HASH_ALLOCATE, (GENERIC)0, (GENERIC)0, (GENERIC)0, "rules");
	vartab = mkhash(255, HASH_ALLOCATE, (GENERIC)0, (GENERIC)0, (GENERIC)0, "variables");
	dot.item.rule = makerule(".");
}

/*
 * search a directory (archive) and record all entries
 */

void
search(name)
char	*name;
{
	DIR	*dirp;
	int	arfd;

	if (!unique(name)) ;
	else if (firstdir->item.dir->directory && (dirp = opendir(name)))
	{
#if DEBUG
		message(-4, "search directory %s", name);
#endif
		scandir(firstdir->item.dir, dirp);
		closedir(dirp);
	}
	else if ((arfd = openar(name, "r")) >= 0)
	{
#if DEBUG
		message(-4, "search archive %s", name);
#endif
		firstdir->item.dir->archive = 1;
		(void)scanar(firstdir->item.dir, arfd, name, 0);
		closear(arfd);
	}
#if DEBUG
	else message(-6, "search(%s) failed", name);
#endif
}

/*
 * scan a directory and record all entries
 */

static void
scandir(d, dirp)
struct dirinfo	*d;
DIR		*dirp;
{
	register struct direct	*entry;

	while (entry = readdir(dirp))
		(void)addfile(d, entry->d_name, NOTIME);
}

/*
 * stat() that checks for read access
 */

static int
rstat(name, st)
char		*name;
struct stat	*st;
{
	register int	fd;

	if ((fd = open(name, 0)) < 0)
	{
		if (errno == EACCES) error(1, "%s ignored -- not readable", name);
		return(-1);
	}
	if (fstat(fd, st))
	{
		close(fd);
		return(-1);
	}
	close(fd);
	return(0);
}

/*
 * determine if a directory (archive) has already been scanned
 */

static int
unique(name)
char	*name;
{
	register struct list	*p;
	register struct dirinfo	*d;
	struct stat		st;

	if (rstat(name, &st)) return(0);
	for (p = firstdir; p; p = p->next)
		if (st.st_ino == p->item.dir->ino &&
		    st.st_dev == p->item.dir->dev)
			return(0);
	d = ALLOCATE(struct dirinfo);
	d->ino = st.st_ino;
	d->dev = st.st_dev;
	d->archive = 0;
	d->directory = (st.st_mode & S_IFDIR) != 0;
	d->name = COPY(name);
	firstdir = cons((GENERIC)d, firstdir);
	return(1);
}

/*
 * add a directory (archive) entry to the file hash
 */

struct fileinfo*
addfile(d, name, date)
struct dirinfo	*d;
char		*name;
time_t		date;
{
	register struct fileinfo	*i;
	register struct list		*f;

#if DEBUG
	message(-7, "%s: %s %s", d->name, name, stime(date));
#endif
	i = ALLOCATE(struct fileinfo);
	f = (struct list*)gethash(filtab, name);
	i->name = puthash(filtab, (char*)0, (GENERIC)cons((GENERIC)i, f));
	i->dir = d;
	i->time = date;
	return(i);
}

/*
 * touch the modify time of a file
 * warn if the file does not exist
 */

void
touch(name)
register char	*name;
{
	register int	fd, touched;
	char		c;
	int		found;
	struct stat	st;

	touched = 0;
	if ((fd = open(name, 2)) >= 0)
	{
		found = 1;
		fstat(fd, &st);

		/*
		 * don't touch files that have already been touched
		 * this properly synchronizes links
		 */

		if (st.st_mtime > state.start) touched = 1;
		else if (read(fd, &c, 1) != 1)
		{
			close(fd);
			if ((fd = creat(name, 0666)) >= 0) touched = 1;
		}
		else if (lseek(fd, 0L, 0) >= 0 && write(fd, &c, 1) == 1) touched = 1;
		close(fd);
	}
	else found = (errno == ENOENT ? 0 : 1);
	if (!touched) error(1, "cannot touch %s%s", name, found ? null : " -- file does not exist");
}

/*
 * low level for bindfile()
 */

static struct ruleinfo*
bindbase(name, force)
char	*name;
int	force;
{
	register struct ruleinfo	*r;
	register struct list		*d, *p;
	struct list			*files;
	struct stat			st;
	int				found;
	time_t				tm;
	char				*s;
	char				dir[MAXNAME];
	char				fil[MAXNAME];

	if (r = getrule(name))
	{
		if (r->bound) return(r);
		else if (r->state) return((struct ruleinfo*)0);
	}
	(void)edit(dir, name, KEEP, KEEP, DELETE, DELETE, DELETE);
	if (*dir && *dir != '/')
	{
		(void)strcpy(fil, name);
		if (s = strchr(dir, '/')) *s = '\0';
		for (p = (struct list*)gethash(filtab, dir); p; p = p->next)
			if (!p->item.file->dir->archive)
				(void)addfile(p->item.file->dir, name, NOTIME);
		if (s) *s = '/';
	}
	else (void)edit(fil, name, DELETE, DELETE, KEEP, KEEP, KEEP);
	if (*dir == '/' || !(files = (struct list*)gethash(filtab, fil)))
	{
		if (*dir || (r && r->dontcare)) tm = rstat(name, &st) ? DEFTIME : st.st_mtime;
		else if (force) tm = CURTIME;
		else tm = DEFTIME;
		if (!r)
		{
			if (!force) return((struct ruleinfo*)0);
			r = makerule(name);
		}
		r->time = tm;
	}
	else
	{
		int			i;
		struct ruleinfo		*x;
		struct list		*dirs[4];

		if (!r) r = makerule(name);
		i = 0;
		if (x = getrule(".SOURCE")) dirs[i++] = x->deps;
		(void)edit(dir, fil, DELETE, DELETE, DELETE, ".SOURCE", KEEP);
		if (dir[7] && (x = getrule(dir))) dirs[i++] = x->deps;
		(void)edit(dir, fil, DELETE, DELETE, KEEP, ".SOURCE", DELETE);
		if (dir[0] != '.' && (x = getrule(dir))) dirs[i++] = x->deps;
		dirs[i++] = &dot;
		found = 0;

		/*
		 * the nested loops preserve the directory search order
		 *
		 * 	.		current directory
		 * 	x..SOURCE	prefix directory (if prefix)
		 * 	.SOURCE.x	suffix directory (if suffix)
		 * 	.SOURCE		default source directory
		 */

		while (i-- > 0)
			for (d = dirs[i]; d; d = d->next)
				for (p = files; p; p = p->next)
		{
			if (p->item.file->dir->archive)
			{
				if ((d == &dot) && r->link->archive && !strcmp(r->link->name, p->item.file->dir->name))
				{
					if (r->member) error(1, "%s is duplicated in %s", r->name, r->link->name);
					else if (p->item.file->time >= r->time)
					{
						r->member = 1;
						r->time = p->item.file->time;
					}
				}
			}
			else if (!strcmp(d->item.rule->name, p->item.file->dir->name))
			{
				if (!found || state.unique)
				{
					if (!strcmp(p->item.file->dir->name, "."))
						(void)strcpy(fil, name);
					else (void)strcopy(strcopy(strcopy(fil, p->item.file->dir->name), "/"), name);
					if (p->item.file->time == NOTIME)
						p->item.file->time = rstat(fil, &st) ? DEFTIME : st.st_mtime;
					if (!p->item.file->time);
					else if (found)
					{
						/*
						 * cheat by only checking the modify times
						 * this avoids saving dev and ino in fileinfo
						 */

						if (p->item.file->time != r->time)
							error(1, "%s is duplicated by %s", r->name, fil);
					}
					else
					{
						/*
						 * bind the rule to file name fil
						 * saving the unbound name
						 */

						found = 1;
						s = r->name;
						r->name = putrule(fil, r);
						if (strcmp(r->name, s)) r->uname = s;
						r->time = p->item.file->time;
						r->member = 0;
					}
				}
			}
		}
	}
	return(r);
}

/*
 * bind a rule to a file using *.SOURCE* rules
 * implicit prefix dependencies are checked here
 */

struct ruleinfo*
bindfile(name, force)
char	*name;
int	force;
{
	register struct ruleinfo	*r, *r1;
	register struct list		*p;
	char				tmp[MAXNAME];

	/*
	 * bind the file
	 */

	if ((r = bindbase(name, force)) && r->bound) return(r);

	/*
	 * check for a corresponding prefix file
	 */

	for (p = special.prefixes->deps; p; p = p->next)
		if (p->item.rule->target)
	{
#if DEBUG
		message(-4, "implicit prefix rule: %s", p->item.rule->name);
#endif
		(void)edit(tmp, name, DELETE, DELETE, p->item.rule->name, KEEP, KEEP);
		if ((r1 = bindbase(tmp, 0)) && r1->time)
		{
			if (!r || r->time < r1->time)
			{
				register struct ruleinfo	*otarget;

				r = makerule(name);
				otarget = special.target;
				special.target = r;
				if (dofix(r, p->item.rule, r1, 0))
					error(2, "`%s' prefix rule failed", r->name);
				special.target = otarget;

				/*
				 * generated files inherit the source time
				 */

				r->time = r1->time;
				r->status = NOTYET;
				break;
			}
		}
	}
	if (r)
	{
		/*
		 * check for inherited suffix attributes
		 */

		(void)edit(tmp, r->name, DELETE, DELETE, DELETE, DELETE, KEEP);
		if (r1 = getrule(tmp))
		{
			if (r1->archive) r->archive = 1;
			if (r1->current) r->current = 1;
			if (r1->search) r->search = 1;
			r->uattributes |= r1->uattributes;
		}
		if (r->target && r->archive) (void)search(r->name);
		r->bound = 1;
	}
	return(r);
}

/*
 * bind a rule possibly changing the rule name
 */

struct ruleinfo*
bind(r)
register struct ruleinfo	*r;
{
	register struct ruleinfo	*b;

	if (r->bound) return(r);
	if (r->dynamic) dynamic(r);
	if (b = bindstate(r)) return(b);
	if (b = bindfile(r->name, 0)) return(b);
	r->bound = 1;
	return(r);
}

/*
 * return a pointer to a rule given its name,
 * creating the rule if necessary
 */

struct ruleinfo*
makerule(name)
register char	*name;
{
	register struct ruleinfo	*r;
	register char			*s;

	if (!(r = getrule(name)))
	{
		r = ALLOCATE(struct ruleinfo);
		if ((s = strchr(name, '(')) && name[strlen(name) - 1] == ')' && (s == name || s[-1] != '$'))
		{
			r->compiled = 1;
			r->state = 1;
		}
		else if (!state.autocompile) r->compiled = 1;
		r->name = putrule((char*)0, r);
		r->status = NOTYET;
#if DEBUG
		message(-6, "adding %s `%s'", r->state ? "state variable" : "rule", r->name);
#endif
	}
	return(r);
}
