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
 * make archive access routines
 */

#include "make.h"

extern int		scanar();
extern int		openar();
extern void		closear();

/*
 * these routines simultaneously support all archive formats
 * there is no sgetl() and sputl() on the pdp11 so
 * some formats are omitted for that machine
 */

#define NAR	2		/* maximum number of simultaneous opens	*/

#define arpointer(x)	(((x)>=0&&(x)<NAR&&artab[x].fd)?&artab[x]:(struct arinfo*)0)

struct arinfo			/* open archive info			*/
{
	FILE	*fd;		/* archive file descriptor		*/
	int	type;		/* current archive type			*/
	long	first;		/* offset of first member header	*/
	long	sym_offset;	/* offset of symbol directory		*/
	long	sym_number;	/* the number of symbols		*/
	long	sym_size;	/* length of symbol directory member	*/
};

static struct arinfo	artab[NAR];	/* open archive table		*/

static int		ntouched;	/* count of touched members	*/

#define ARpdp	1		/* old					*/
#define AR5	2		/* 5.0					*/
#define ARport	3		/* portable				*/
#define ARrand	4		/* portable with ranlib (BSD)		*/

/*
 * definitions for the different archive formats
 */

#define ARpdpMAG	0177545		/* old format magic number	*/
#define SARpdpMAG	2		/* ARpdpMAG length		*/

#define AR5MAG		"<ar>"		/* 5.0 format magic string	*/
#define SAR5MAG		4		/* AR5MAG length		*/

#define ARportMAG	"!<arch>\n"	/* Port. (6.0) magic string	*/
#define SARportMAG	8		/* ARportMAG length		*/
#define ARFportMAG	"`\n"		/* Port. (6.0) end of header	*/
#define SARFportMAG	2		/* ARFportMAG length		*/
#define ARportSYM	"/"		/* Port. (6.0) sym dir name	*/
#define SARportSYM	1		/* ARportSYM length		*/

#define ARrandSYM	"__.SYMDEF"	/* Port. (BSD) sym dir name	*/
#define SARrandSYM	9		/* ARrandSYM length		*/

/*
 * these are the archive file headers for the archive formats
 * if an archive format is changed then the new structure
 * is added to the list and the appropriate cases must be added
 * to openar() and scanar()
 */

struct		/* pdp11 -- old archive format				*/
{
	char	ar_name[14];		/* '\0' terminated		*/
	long	ar_date;		/* native representation	*/
	char	ar_uid;			/* 	"			*/
	char	ar_gid;			/* 	"			*/
	int	ar_mode;		/* 	"			*/
	long	ar_size;		/* 	"			*/
} ar_pdp;

struct		/* UNIX 5.0 archive header format			*/
{
	char	ar_magic[SAR5MAG];	/* AR5MAG			*/
	char	ar_name[16];		/* '\0' terminated		*/
	char	ar_date[4];		/* sgetl() accessed		*/
	char	ar_syms[4];		/* sgetl() accessed		*/
} arh_5;

struct		/* UNIX 5.0 archive symbol format			*/
{
	char	sym_name[8];		/* ' ' terminated		*/
	char	sym_ptr[4];		/* sgetl() accessed		*/
} ars_5;

struct		/* UNIX 5.0 archive member format			*/
{
	char	arf_name[16];		/* '\0' terminated		*/
	char	arf_date[4];		/* sgetl() accessed		*/
	char	arf_uid[4];		/*	"			*/
	char	arf_gid[4];		/*	"			*/
	char	arf_mode[4];		/*	"			*/
	char	arf_size[4];		/*	"			*/
} arf_5;

struct		/* Portable (6.0) archive format			*/
{
	char	ar_name[16];	/* '/' terminated			*/
	char	ar_date[12];	/* left-adj; decimal char*; blank fill	*/
	char	ar_uid[6];	/*	"				*/
	char	ar_gid[6];	/*	"				*/
	char	ar_mode[8];	/* left-adj; octal char*; blank fill	*/
	char	ar_size[10];	/* left-adj; decimal char*; blank fill	*/
	char	ar_fmag[2];	/* end-of-header string (ARFportMAG)	*/
} ar_port;

/*
 * open an archive and determine its type (version)
 */

int
openar(name, mode)
register char	*name;
char		*mode;
{
	int			arfd;
	register struct arinfo	*ar;
	unsigned short		mag_pdp;
	char			mag_5[SAR5MAG];
	char			mag_port[SARportMAG];

	for (arfd = 0; arfd < NAR; arfd++)
		if (!artab[arfd].fd) break;
	if (arfd >= NAR) goto badar;
	ar = &artab[arfd];
	if (!(ar->fd = fopen(name, mode))) goto badar;
	if (fread((char*)&mag_pdp, sizeof(mag_pdp), 1, ar->fd) != 1) goto badar;
	if (mag_pdp == (unsigned short)ARpdpMAG)
	{
		ar->type = ARpdp;
		special.arupdate->value = null;
		ar->first = ftell(ar->fd);
		ar->sym_offset = ar->sym_number = ar->sym_size = 0;
		return(arfd);
	}
	if (fseek(ar->fd, 0L, 0) || fread(mag_5, SAR5MAG, 1, ar->fd) != 1) goto badar;
	if (!strncmp(mag_5, AR5MAG, SAR5MAG))
	{
		ar->type = AR5;
		special.arupdate->value = null;
		if (fseek(ar->fd, 0L, 0) ||
		    fread((char*)&arh_5, sizeof(arh_5), 1, ar->fd) != 1)
			goto badar;
#if pdp11
		error(2, "%s: 5.0 archive format not supported", name);
		goto badar;
#else
		ar->sym_offset = ftell(ar->fd);
		ar->sym_number = sgetl(arh_5.ar_syms);
		ar->first = ar->sym_offset + sizeof(ars_5) * ar->sym_number;
		ar->sym_size = 0;
		return(arfd);
#endif
	}
	if (fseek(ar->fd, 0L, 0) || fread(mag_port, SARportMAG, 1, ar->fd) != 1)
		goto badar;
	if (!strncmp(mag_port, ARportMAG, SARportMAG))
	{
		/*
		 * check for a symbol directory
		 */

		if (fread((char*)&ar_port, sizeof(ar_port), 1, ar->fd) != 1 ||
		    strncmp(ARFportMAG, ar_port.ar_fmag, sizeof(ar_port.ar_fmag)))
			goto badar;
#if pdp11
		error(2, "%s: portable archive format not supported", name);
		goto badar;
#else
		if (!strncmp(ar_port.ar_name, ARportSYM, SARportSYM))
		{
			char s[4];

			ar->type = ARport;
			special.arupdate->value = null;
			if (sscanf(ar_port.ar_size, "%ld", &ar->sym_size) != 1)
				goto badar;
			ar->sym_size += (ar->sym_size & 01);	/* round up */
			if (fread(s, sizeof(s), 1, ar->fd) != 1)
				goto badar;
			ar->sym_number = sgetl(s);
			ar->sym_offset = ftell(ar->fd);
			ar->first = ar->sym_offset + ar->sym_size - sizeof(s);
		}
		else if (!strncmp(ar_port.ar_name, ARrandSYM, SARrandSYM))
		{
			ar->type = ARrand;
			special.arupdate->value = ARUPDATE;
			if (sscanf(ar_port.ar_size, "%ld", &ar->sym_size) != 1)
				goto badar;
			ar->sym_size += (ar->sym_size & 01);	/* round up */
			if (fread((char*)&ar->sym_number, sizeof(ar->sym_number), 1, ar->fd) != 1)
				goto badar;
			ar->sym_offset = ftell(ar->fd);
			ar->first = ar->sym_offset + ar->sym_size - sizeof(ar->sym_number);
		}
		else
		{
			/*
			 * there is no symbol directory
			 */

			ar->type = ARport;
			special.arupdate->value = null;
			ar->sym_size = ar->sym_number = ar->sym_offset = 0;
			ar->first = ftell(ar->fd) - sizeof(ar_port);
		}
		return(arfd);
#endif
	}
badar:
	closear(arfd);
	return(-1);
}

/*
 * close an archive opened by openar()
 */

void
closear(arfd)
int	arfd;
{
	register struct arinfo	*ar;

	if (ar = arpointer(arfd))
	{
		fclose(ar->fd);
		ar->fd = (FILE*)0;
	}
}

/*
 * scan an archive
 * `touch' updates the modify time of preselected members (see touchar())
 * else each member is recorded using addfile()
 */

int
scanar(d, arfd, name, touch)
struct dirinfo	*d;
int		arfd;
char		*name;
int		touch;
{
	register struct arinfo		*ar;
	register char			*s;
	register struct ruleinfo	*r;
	char				*err, *member;
	char				buf[32];
	long				ptr, patch;
	time_t				date;

	if (!(ar = arpointer(arfd))) return(0);
	err = "seek";
	member = null;
	(void)fseek(ar->fd, ar->first, 0);
	ptr = 0;
	patch = -1;
	switch (ar->type)
	{
	case ARpdp:
		member = buf;
		while (!fseek(ar->fd, ptr, 1))
		{
			if (fread((char*)&ar_pdp, sizeof(ar_pdp), 1, ar->fd) != 1)
			{
				if (feof(ar->fd)) return(1);
				else
				{
					err = "read";
					break;
				}
			}
			(void)strncpy(member, ar_pdp.ar_name, 14);
			member[14] = '\0';
			if (!touch) (void)addfile(d, member, (time_t)ar_pdp.ar_date);
			else if ((r = getrule(member)) && r->touch)
			{
				r->touch = 0;
				r->time = CURTIME;
				if (r->statedeps)
				{
					sprintf(buf, "%s()", member);
					makerule(buf)->time = r->time;
					state.savestate = 1;
				}
				ar_pdp.ar_date = r->time;
				if (fseek(ar->fd, -(long)sizeof(ar_pdp), 1)) break;
				if (fwrite((char*)&ar_pdp, sizeof(ar_pdp), 1, ar->fd) != 1)
				{
					err = "write";
					break;
				}
				if (!state.silent) error(0, "touch(%s[%s])", name, member);
				ntouched--;
			}
			ptr = ar_pdp.ar_size;
			ptr += (ptr & 01);
		}
		break;
#if !pdp11
	case AR5:
		member = arf_5.arf_name;
		while (!fseek(ar->fd, ptr, 1))
		{
			if (fread((char*)&arf_5, sizeof(arf_5), 1, ar->fd) != 1)
			{
				if (feof(ar->fd)) return(1);
				else
				{
					err = "read";
					break;
				}
			}
			if (s = strchr(member, ' ')) *s = '\0';
			if (!touch) (void)addfile(d, member, (time_t)sgetl(arf_5.arf_date));
			else if ((r = getrule(member)) && r->touch)
			{
				r->touch = 0;
				r->time = CURTIME;
				if (r->statedeps)
				{
					sprintf(buf, "%s()", member);
					makerule(buf)->time = r->time;
					state.savestate = 1;
				}
				sputl(r->time, arf_5.arf_date);
				if (fseek(ar->fd, -(long)sizeof(arf_5), 1)) break;
				if (fwrite((char*)&arf_5, sizeof(arf_5), 1, ar->fd) != 1)
				{
					err = "write";
					break;
				}
				if (!state.silent) error(0, "touch(%s[%s])", name, member);
				ntouched--;
			}
			ptr = sgetl(arf_5.arf_size);
			ptr += (ptr & 01);
		}
		break;
	case ARport:
	case ARrand:
		member = ar_port.ar_name;
		while (!fseek(ar->fd, ptr, 1))
		{
			if (fread((char*)&ar_port, sizeof(ar_port), 1, ar->fd) != 1 ||
			    strncmp(ar_port.ar_fmag, ARFportMAG, SARFportMAG))
			{
				if (feof(ar->fd))
				{
					if (!touch) return(1);
					else if (!patch && ar->type == ARrand && ar->sym_offset)
					{
						/*
						 * patch symbol directory time
						 */

						patch = 5;
						if (fseek(ar->fd, (long)SARportMAG, 0)) break;
						ptr = 0;
						continue;
					}
					else return(1);
				}
				else
				{
					err = "read";
					break;
				}
			}
			if (s = strchr(member, '/')) *s = '\0';
			else if (s = strchr(member, ' ')) *s = '\0';
			if (!touch)
			{
				if (sscanf(ar_port.ar_date, "%ld", &date) != 1)
				{
					err = "date field";
					break;
				}
				(void)addfile(d, member, date);
			}
			else if (patch > 0 || (r = getrule(member)) && r->touch)
			{
				date = CURTIME;
				if (patch <= 0)
				{
					patch = 0;
					r->touch = 0;
					r->time = date;
					if (r->statedeps)
					{
						sprintf(buf, "%s()", member);
						makerule(buf)->time = date;
						state.savestate = 1;
					}
				}
				if (fseek(ar->fd, -(long)sizeof(ar_port), 1)) break;
				sprintf(buf, "%-12ld", date + patch);
				(void)strncpy(ar_port.ar_date, buf, 12);
				if (fwrite((char*)&ar_port, sizeof(ar_port), 1, ar->fd) != 1)
				{
					err = "write";
					break;
				}
				if (patch > 0) return(1);
				if (!state.silent) error(0, "touch(%s[%s])", name, member);
				ntouched--;
			}
			if (sscanf(ar_port.ar_size, "%ld", &ptr) != 1)
			{
				err = "size field";
				break;
			}
			ptr += (ptr & 01);
		}
		break;
#endif
	}
	error(1, "%s error %s %s%s archive %s",
		err,
		touch ? "touching" : "scanning",
		member,
		*member ? " in" : null,
		name);
	return(0);
}

/*
 * check for any untouched r->touch members
 */

/*ARGSUSED*/
static int
chktouch(s, r)
char		*s;
struct ruleinfo	*r;
{
	if (r->touch)
	{
		r->touch = 0;
		error(1, "archive member %s not touched", r->name);
	}
	return(0);
}

/*
 * touch the modify time of an archive member (and the archive itself!)
 */

void
touchar(name, member)
char		*name;
register char	*member;
{
	register struct ruleinfo	*r;
	int				arfd;

	if (member)
	{
		if (!(r = getrule(member)))
			error(INTERNAL, "%s[%s] not scanned", name, member);
		else
		{
			r->touch = 1;
			ntouched++;
		}
	}
	else if ((arfd = openar(name, "r+")) >= 0)
	{
		(void)scanar((struct dirinfo*)0, arfd, name, 1);
		closear(arfd);
		if (ntouched > 0)
		{
			message(-2, "checking %d untouched members in %s", ntouched, name);
			exhash(rultab, chktouch);
		}
		ntouched = 0;
	}
}
