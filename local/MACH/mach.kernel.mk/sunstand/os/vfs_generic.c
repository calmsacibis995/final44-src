/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vfs_generic.c,v $
 * Revision 2.2  89/07/12  01:15:45  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */

#ifndef lint
static  char sccsid[] = "@(#)vfs_generic.c 1.10 88/02/08 Copyr 1983 Sun Micro";
#endif


/*
 * Mostly stolen from estale:/usr.MC68020/estale/sys/sys/sun/swapgeneric.c
 */

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/vm.h>
#include "boot/systm.h"
#include <sys/reboot.h>
#include <sys/file.h>
#include <sys/vfs.h>
#undef KERNEL
#undef NFS
#include <sys/mount.h>

#include <machine/pte.h>
#include <sundev/mbvar.h>
#include <mon/sunromvec.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include "boot/protosw.h"
#include <net/if.h>
#include <stand/saio.h>

#undef MOUNT_MAXTYPE
#define MOUNT_MAXTYPE  2

/*
 * Beware: in the following table, the entries must appear
 * in the slot corresponding to their major device number.
 *
 * This is because other routines index into this table
 * using the major() of the dev_t returned by getblockdev.
 */

extern struct boottab sddriver;
extern struct boottab xydriver;
extern struct boottab xddriver;

struct  bdevlist {
	char	*bl_name;
	struct	boottab	*bl_driver;
	dev_t	bl_root;
} bdevlist[] = {
	"", 0, 0,				/* (0, 0) */
	"", 0, 0,				/* (1, 0) */
	"", 0, 0,				/* (2, 0) */
	"xy", &xydriver, makedev(3, 0),		/* (3, 0) */
	"", 0, 0,				/* (4, 0) */
	"", 0, 0,				/* (5, 0) */
	"", 0, 0,				/* (6, 0) */
	"sd", &sddriver, makedev(7, 0),		/* (7, 0) */
	"xd", &xddriver, makedev(8, 0),		/* (8, 0) */
  0,
};

int	dump_debug = 10;

/*
 * What it does:
 */

struct vfssw *
getfstype(askfor, fsname)
	char *askfor;
	char *fsname;
{
	int fstype;

	if (boothowto & RB_ASKNAME) {
		for (fsname[0] = '\0'; fsname[0] == '\0'; ) {
			printf("%s filesystem type ( ", askfor);
			for (fstype = 0; fstype < MOUNT_MAXTYPE; fstype++) {
				if (vfssw[fstype].vsw_name)
					printf("%s ", vfssw[fstype].vsw_name);
			}
			printf(" ): ");
			(void) gets(fsname);
			for (fstype = 0; fstype < MOUNT_MAXTYPE; fstype++) {
				if (vfssw[fstype].vsw_name == 0) {
					continue;
				}
				if (*fsname == '\0') {
					(void) strcpy(fsname, vfssw[fstype].vsw_name);
					return (&vfssw[fstype]);
				}
				if (strcmp(vfssw[fstype].vsw_name, fsname)==0) {
					return (&vfssw[fstype]);
				}
			}
			printf("Unknown filesystem type '%s'\n", fsname);
			*fsname = '\0';
		}
	} else if (*fsname) {
		for (fstype = 0; fstype < MOUNT_MAXTYPE; fstype++) {
			if (vfssw[fstype].vsw_name == 0) {
				continue;
			}
			if (strcmp(vfssw[fstype].vsw_name, fsname) == 0) {
				return (&vfssw[fstype]);
			}
		}
	}
	return ((struct vfssw *)0);
}

/*
 * If booted with ASKNAME prompt on the console for a filesystem
 * name and return it.
 */
getfsname(askfor, name)
	char *askfor;
	char *name;
{

	if (boothowto & RB_ASKNAME) {
		printf("%s name: ", askfor);
		(void) gets(name);
	}
}

/*
 * Return the device number and name of the frist block
 * block device in the bdevlist that cna be opened.
 * If booted with the -a flag ask user for device name.
 * Name must be at least 128 bytes long.
 * askfor is one of "root" or "swap".
 */
dev_t
getblockdev(askfor, name)
	char *askfor;
	char *name;
{
	register struct bdevlist *bl;
	int unit;
	int part;
 
	if (boothowto & RB_ASKNAME) {
		for (unit = -1; unit == -1; ) {
			printf("%s device ( ", askfor);
			for (bl = bdevlist; bl->bl_name; bl++)
			    if (strcmp(bl->bl_name, "") != 0)
				printf("%s%cd[a-h] ", bl->bl_name, '%');
			printf("): ");
			(void) gets(name);
			if (*name == '\0') {
				bl = bdevlist;
				unit = 0;
				part = 0;
				break;
			}
			for (bl = bdevlist; bl->bl_name; bl++) {
				if (bl->bl_name[0] == name[0] &&
				    bl->bl_name[1] == name[1])
					break;
			}
			if (!bl->bl_name) {
				printf("unknown device name %c%c\n",
				    name[0], name[1]);
				continue;
			}
			if (name[2] < '0' || name[2] > '7') {
				printf("bad/missing unit number\n");
				continue;
			}
			unit = name[2] - '0';
			if (name[3] == '\0') {
				part = 0;
			} else if (name[3] >= 'a' && name[3] <= 'h') {
				part = name[3] - 'a';
			} else {
				printf("bad partition (use a-h)\n");
				unit = -1;
			}
		}
	} else {
		unit = 0;
		part = 0;
		/*
		 * If a name was given find that block device
		 */
		if (*name != '\0') {
			for (bl = bdevlist; bl->bl_name; bl++) {
				if (bl->bl_name[0] == name[0] &&
				    bl->bl_name[1] == name[1]) {
					if (chkroot(bl)) {
						if (name[2] != '\0')
							unit = name[2] - '0';
						if (name[3] != '\0')
							part = name[3] - 'a';
						goto found;
					}
				}
			}
			printf("%c%c%c%c not configured in boot\n",
				name[0], name[1], name[2], name[3]);
			return ((dev_t)0);
		}	
		/*
		 * Look for device we booted from
		 */
		for (bl = bdevlist; bl->bl_name; bl++) {
			register struct bootparam *bp = (*romp->v_bootparam);

			if (!((*bl->bl_name == bp->bp_dev[0]) &&
				(*(bl->bl_name+1) == bp->bp_dev[1])))
				continue;
			/*
			 * This is a cheat.   Since we don't support
			 * the full apparatus of the mb_device list,
			 * we assume the device we were booted from
			 * is openable if we located it in the
			 * bdevlist..
			 */
			unit = bp->bp_unit;
			part = bp->bp_part;
			goto found;
		}
 
		/*
		 * Use first device that can be opened
		 */
		for (bl = bdevlist; bl->bl_name; bl++) {
			if (chkroot(bl)) {
				goto found;
			}
		}
		return ((dev_t)0);
	}	
 
found:
	name[0] = bl->bl_name[0];
	name[1] = bl->bl_name[1];
	name[2] = '0' + unit;
	name[3] = 'a' + part;
	name[4] = '\0';
	return (makedev(major(bl->bl_root), unit*8+part));
}

/*ARGSUSED*/
chkroot(bl)
	register struct bdevlist *bl;
{
#ifdef lint
	bl = bl;
#endif lint
	return (0);
}

sleep (addr, prio)
{
#ifdef  DUMP_DEBUG
        dprint(dump_debug, 10,
		"sleep (addr 0x%x, prio 0x%x)\n",
		addr, prio);
#endif  /* DUMP_DEBUG */
	panic("sleep");

}

/*
 * Arrange that (*fun)(arg) is called in t/hz seconds.
 */
timeout(fun, arg, t)
        int (*fun)();
        caddr_t arg;
        register int t;
{
#ifdef lint
	t = t;
#endif lint
	{
	int	i;

		for(i = 1; i > 0; i--) {
			if(get_udp() != 0) return;
		}
	}

	(*fun)(arg);
	return;
}

/*
 * Wake up all processes sleeping on chan.
 */
wakeup(chan)
        register caddr_t chan;
{
#ifdef  DUMP_DEBUG
        dprint(dump_debug, 0,
		"wakeup(chan 0x%x)\n",
		chan);
#endif  /* DUMP_DEBUG */

}

