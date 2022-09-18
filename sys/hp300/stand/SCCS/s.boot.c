h56384
s 00002/00002/00159
d D 8.1 93/06/10 21:46:27 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00160
d D 7.8 93/05/24 22:50:03 mckusick 8 7
c fix include directives
e
s 00002/00000/00159
d D 7.7 92/12/26 16:49:43 hibler 7 6
c Utah update (mostly disklabels)
e
s 00005/00005/00154
d D 7.6 92/10/11 10:01:33 bostic 6 5
c make kernel includes standard
e
s 00067/00122/00092
d D 7.5 92/06/18 21:33:36 hibler 5 4
c merge with latest Utah version
e
s 00008/00008/00206
d D 7.4 91/05/05 13:43:14 bostic 4 3
c change includes, UNIX defined in common headers
e
s 00001/00001/00213
d D 7.3 91/05/04 17:17:56 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00002/00212
d D 7.2 90/12/16 16:39:06 bostic 2 1
c kernel reorg
e
s 00214/00000/00000
d D 7.1 90/05/08 22:45:59 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
D 3
/*
E 3
I 3
/*-
E 3
D 9
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#include <sys/param.h>
#include <sys/reboot.h>
E 5
I 5
D 6
#include "sys/param.h"
#include "sys/reboot.h"
E 6
I 6
#include <sys/param.h>
#include <sys/reboot.h>
E 6
E 5
E 4
#include <a.out.h>
D 6
#include "saio.h"
E 6
I 6
D 8
#include <stand/saio.h>
E 8
I 8
#include <stand.att/saio.h>
E 8
E 6
D 2
#include "../sys/reboot.h"
E 2
I 2
D 4
#include "sys/reboot.h"
E 4
E 2

#ifndef INSECURE
D 2
#include "../sys/stat.h"
E 2
I 2
D 6
#include "sys/stat.h"
E 6
I 6
#include <sys/stat.h>
E 6
E 2
struct stat sb;
#endif
D 4

E 4
I 4
D 5
					/* XXX -- see sys/reboot.h */
E 4
#define B_MAKEDEV(a,u,p,t) \
	(((a) << B_ADAPTORSHIFT) | ((u) << B_UNITSHIFT) | \
	 ((p) << B_PARTITIONSHIFT) | ((t) << B_TYPESHIFT))
E 5

I 5
#define	PRTCPU		/* print out cpu type */

E 5
/*
D 5
 * Boot program... arguments in `devtype' and `howto' determine
 * whether boot stops to ask for system name and which device
 * boot comes from.
E 5
I 5
 * Boot program... bits in `howto' determine whether boot stops to
 * ask for system name.  Boot device is derived from ROM provided
 * information.
E 5
 */

D 5
/* Types in `devtype' specifying major device */
char	devname[][2] = {
D 4
	0,0,		/* 0 = ct */
	0,0,		/* 1 = fd */
	'r','d',	/* 2 = rd */
	0,0,		/* 3 = sw */
	's','d',	/* 4 = sd */
E 4
I 4
	'\0', '\0',	/* 0 = ct */
	'\0', '\0',	/* 1 = fd */
	 'r',  'd',	/* 2 = rd */
	'\0', '\0',	/* 3 = sw */
	 's',  'd',	/* 4 = sd */
E 4
};
#define	MAXTYPE	(sizeof(devname) / sizeof(devname[0]))

E 5
D 4
#define	UNIX	"vmunix"
E 4
char line[100];

D 5
int	retry = 0;
E 5
I 5
extern	unsigned opendev;
E 5
extern	char *lowram;
extern	int noconsole;
D 5
extern	int howto, devtype;
E 5
I 5
extern	int howto, bootdev;
E 5

D 5
#define	MSUS (0xfffffedc)
E 5
I 5
#ifdef PRTCPU
D 6
#include "samachdep.h"
E 6
I 6
#include <hp300/stand/samachdep.h>
E 6
#endif
E 5

D 5
char rom2mdev[] = {
	0,	/*  0 - none */
	0,	/*  1 - none */
	0,	/*  2 - none */
	0,	/*  3 - none */
	0,	/*  4 - none */
	0,	/*  5 - none */
	0,	/*  6 - none */
	0,	/*  7 - none */
	0,	/*  8 - none */
	0,	/*  9 - none */
	0,	/* 10 - none */
	0,	/* 11 - none */
	0,	/* 12 - none */
	0,	/* 13 - none */
	4,	/* 14 - SCSI disk */
	0,	/* 15 - none */
	2,	/* 16 - CS/80 device on HPIB */
	2,	/* 17 - CS/80 device on HPIB */
	0,	/* 18 - none */
	0,	/* 19 - none */
	0,	/* 20 - none */
	0,	/* 21 - none */
	0,	/* 22 - none */
	0,	/* 23 - none */
	0,	/* 24 - none */
	0,	/* 25 - none */
	0,	/* 26 - none */
	0,	/* 27 - none */
	0,	/* 28 - none */
	0,	/* 29 - none */
	0,	/* 30 - none */
	0,	/* 31 - none */
};

E 5
main()
{
D 5
	register type, part, unit, io;
E 5
	register char *cp;
I 5
	int io, retry, type;
#ifdef PRTCPU
	extern int machineid;
E 5

I 5
	printf("\nHP");
	switch (machineid) {
	case HP_320:
		cp = "320"; break;
	case HP_330:
		cp = "318/319/330"; break;
	case HP_340:
		cp = "340"; break;
	case HP_350:
		cp = "350"; break;
	case HP_360:
		cp = "360"; break;
	case HP_370:
		cp = "370"; break;
	case HP_375:
		cp = "345/375/400"; break;
	case HP_380:
		cp = "380/425"; break;
I 7
	case HP_433:
		cp = "433"; break;
E 7
	default:
		cp = "???"; break;
	}
	printf("%s CPU\nBoot\n", cp);
#else
E 5
	printf("\nBoot\n");
I 5
#endif
E 5
#ifdef JUSTASK
	howto = RB_ASKNAME|RB_SINGLE;
#else
D 5
	type = (devtype >> B_TYPESHIFT) & B_TYPEMASK;
	unit = (devtype >> B_UNITSHIFT) & B_UNITMASK;
	unit += 8 * ((devtype >> B_ADAPTORSHIFT) & B_ADAPTORMASK);
	part = (devtype >> B_PARTITIONSHIFT) & B_PARTITIONMASK;
E 5
	if ((howto & RB_ASKNAME) == 0) {
D 5
		if ((devtype & B_MAGICMASK) != B_DEVMAGIC) {
			/*
			 * we have to map the ROM device type codes
			 * to Unix major device numbers.
			 */
			type = rom2mdev[*(char *)MSUS & 0x1f];
			devtype = (devtype &~ (B_TYPEMASK << B_TYPESHIFT))
				  | (type << B_TYPESHIFT);
		}
		if (type >= 0 && type <= MAXTYPE && devname[type][0]) {
			cp = line;
			*cp++ = devname[type][0];
			*cp++ = devname[type][1];
			*cp++ = '(';
			if (unit >= 10)
				*cp++ = unit / 10 + '0';
			*cp++ = unit % 10 + '0';
			*cp++ = ',';
			*cp++ = part + '0';
			*cp++ = ')';
			strcpy(cp, UNIX);
		} else
			howto = RB_SINGLE|RB_ASKNAME;
E 5
I 5
		type = (bootdev >> B_TYPESHIFT) & B_TYPEMASK;
		if ((unsigned)type < ndevs && devsw[type].dv_name)
			strcpy(line, UNIX);
		else
			howto |= RB_SINGLE|RB_ASKNAME;
E 5
	}
#endif
D 5
	for (;;) {
E 5
I 5
	for (retry = 0;;) {
E 5
		if (!noconsole && (howto & RB_ASKNAME)) {
			printf(": ");
			gets(line);
I 5
			if (line[0] == 0) {
				strcpy(line, UNIX);
				printf(": %s\n", line);
			}
E 5
		} else
			printf(": %s\n", line);
		io = open(line, 0);
		if (io >= 0) {
#ifndef INSECURE
			(void) fstat(io, &sb);
			if (sb.st_uid || (sb.st_mode & 2)) {
				printf("non-secure file, will not load\n");
I 5
				close(io);
E 5
				howto = RB_SINGLE|RB_ASKNAME;
				continue;
			}
#endif
D 5
			if (howto & RB_ASKNAME) {
				/*
				 * Build up devtype register to pass on to
				 * booted program.
				 */ 
				cp = line;
				for (type = 0; type <= MAXTYPE; type++)
					if ((devname[type][0] == cp[0]) && 
					    (devname[type][1] == cp[1]))
					    	break;
				if (type <= MAXTYPE) {
					cp += 3;
					unit = *cp++ - '0';
					if (*cp >= '0' && *cp <= '9')
						unit = unit * 10 + *cp++ - '0';
					cp++;
					part = atol(cp);
					devtype = B_MAKEDEV(unit >> 3, unit & 7, part, type);
				}
			}
			devtype |= B_DEVMAGIC;
			copyunix(howto, devtype, io);
E 5
I 5
			copyunix(howto, opendev, io);
E 5
			close(io);
D 5
			howto = RB_SINGLE|RB_ASKNAME;
E 5
I 5
			howto |= RB_SINGLE|RB_ASKNAME;
E 5
		}
D 5
	bad:
E 5
		if (++retry > 2)
D 5
			howto = RB_SINGLE|RB_ASKNAME;
E 5
I 5
			howto |= RB_SINGLE|RB_ASKNAME;
E 5
	}
}

/*ARGSUSED*/
copyunix(howto, devtype, io)
D 5
	register howto;		/* d7 contains boot flags */
	register devtype;	/* d6 contains boot device */
	register io;
E 5
I 5
	register int howto;	/* d7 contains boot flags */
	register u_int devtype;	/* d6 contains boot device */
	register int io;
E 5
{
	struct exec x;
	register int i;
	register char *load;	/* a5 contains load addr for unix */
	register char *addr;

D 5
	i = read(io, (char *)&x, sizeof x);
	if (i != sizeof x ||
	    (x.a_magic != 0407 && x.a_magic != 0413 && x.a_magic != 0410))
		_stop("Bad format\n");
E 5
I 5
	i = read(io, (char *)&x, sizeof(x));
	if (i != sizeof(x) ||
	    (x.a_magic != OMAGIC && x.a_magic != ZMAGIC && x.a_magic != NMAGIC)) {
		printf("Bad format\n");
		return;
	}
E 5
	printf("%d", x.a_text);
D 5
	if (x.a_magic == 0413 && lseek(io, 0x400, 0) == -1)
E 5
I 5
	if (x.a_magic == ZMAGIC && lseek(io, 0x400, L_SET) == -1)
E 5
		goto shread;
	load = addr = lowram;
	if (read(io, (char *)addr, x.a_text) != x.a_text)
		goto shread;
	addr += x.a_text;
D 5
	if (x.a_magic == 0413 || x.a_magic == 0410)
E 5
I 5
	if (x.a_magic == ZMAGIC || x.a_magic == NMAGIC)
E 5
		while ((int)addr & CLOFSET)
			*addr++ = 0;
	printf("+%d", x.a_data);
	if (read(io, addr, x.a_data) != x.a_data)
		goto shread;
	addr += x.a_data;
	printf("+%d", x.a_bss);
	x.a_bss += 128*512;	/* slop */
	for (i = 0; i < x.a_bss; i++)
		*addr++ = 0;
	x.a_entry += (int)lowram;
	printf(" start 0x%x\n", x.a_entry);
#ifdef __GNUC__
	asm("	movl %0,d7" : : "m" (howto));
	asm("	movl %0,d6" : : "m" (devtype));
	asm("	movl %0,a5" : : "a" (load));
#endif
	(*((int (*)()) x.a_entry))();
D 5
	exit();
E 5
I 5
	return;
E 5
shread:
D 5
	_stop("Short read\n");
E 5
I 5
	printf("Short read\n");
	return;
E 5
}
E 1
