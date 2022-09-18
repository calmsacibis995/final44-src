/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_subr.c,v $
 * Revision 2.2  89/07/12  01:11:33  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static	char sccsid[] = "@(#)if_subr.c 1.14 88/02/08 Copyr 1986 Sun Micro";
#endif

/*
 * Device independent subroutines used by Ethernet device drivers.
 * Mostly this code takes care of protocols and sockets and
 * stuff.  Knows about Ethernet in general, but is ignorant of the
 * details of any particular Ethernet chip or board.
 */

#include <sys/param.h>
#include "boot/systm.h"
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/time.h>

#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <net/netisr.h>
#ifdef NIT
#include <net/nit.h>
#endif
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <mon/sunromvec.h>
#include <sys/dir.h>
#include "boot/vnode.h"
#include <ufs/fs.h>
#include "boot/inode.h"
#include <stand/saio.h>
#include "boot/iob.h"
#include <stand/sainet.h>
#include "boot/inet.h"

extern    struct  iob     iob[NFILES];
extern	struct	bootparam	*boot_bp;

extern struct in_addr my_in_addr;
extern struct in_addr null_in_addr;

struct no_nd no_nd;		/* global for now - eliminate later */

static	int	dump_debug = 10;

ethersetup()
{
	int	fdesc;
	struct	iob	*file;
	/*
	 */
	bzero(&my_in_addr, sizeof(struct in_addr));
	bzero(&null_in_addr, sizeof(struct in_addr));
	etherinit(&fdesc, &file);

}

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 * Any hardware-specific initialization is done by the caller.
 */
ether_attach(ifp, unit, name, init, ioctl, output, reset)
	register struct ifnet *ifp;
	int unit;
	char *name;
	int (*init)(), (*ioctl)(), (*output)(), (*reset)();
{

	ifp->if_unit = unit;
	ifp->if_name = name;
	ifp->if_mtu = ETHERMTU;

	ifp->if_addrlist = (struct ifaddr *)kmem_alloc(sizeof (struct ifaddr));
	ifp->if_addrlist->ifa_ifp = ifp;
	ifp->if_addrlist->ifa_next = (struct ifaddr *)0;
	((struct sockaddr_in *)&((ifp->if_addrlist->ifa_addr)))->sin_family = AF_INET;
	ifp->if_init = init;
	ifp->if_ioctl = ioctl;
	ifp->if_output = output;
	ifp->if_reset = reset;
	/*
	 * Added to ensure that routing sees this interface.
	 */
	ifp->if_flags |= (IFF_UP | IFF_RUNNING);
	if_attach(ifp);
}

address_known(ifp)
	struct ifnet *ifp;
{

	return (((struct sockaddr_in *)&((ifp->if_addrlist->ifa_addr)))->sin_addr.s_addr != 0);
}

revarp_myaddr(ifp)
        register struct ifnet *ifp;
{
        register struct sockaddr_in *sin;

        sin = (struct sockaddr_in *)&(ifp->if_addrlist->ifa_addr);
	if (bcmp(&my_in_addr, &null_in_addr, sizeof(struct in_addr)) == 0)	{
		printf("revarp_myaddr: no IP address\n");
		return;
	}
        bcopy(&my_in_addr, &sin->sin_addr, sizeof(struct in_addr));
        if (if_setaddr(ifp, (struct sockaddr *)sin))
		return;
}


etherinit(fdesc, file)
	int     *fdesc;
	register struct iob **file;
{
	register struct ifnet *inet_ifp;
	register struct boottab **tablep;
	register struct boottab *dp;
	int	status;
	char	filename[3];
	int     lfdesc;
	register struct iob *lfile;
	int (*init)(), (*ioctl)(), (*output)(), (*reset)();

	extern struct boottab *(devsw[]);


	/*
	 * We are going to open an ether device, so obtain
	 * a file descriptor record (iob).   Getiob exits
	 * if it is out of iobs, so we assume that it returns
	 * a good one.
	 */
	lfdesc = getiob();
	lfile = &iob[lfdesc];

	status = -1;

try:
	for (tablep = devsw;
		(status == -1) && (0 != (dp = *tablep)); tablep++) {

		if ((boot_bp->bp_dev[0] == dp->b_dev[0]) &&
			(boot_bp->bp_dev[1] == dp->b_dev[1]))	{
			/*
			 * Fill in file table and open device.
			 */
			lfile->i_boottab = dp;
			lfile->i_ino.i_dev = tablep-devsw;
			lfile->i_ctlr = boot_bp->bp_ctlr;
			lfile->i_unit = boot_bp->bp_unit;
			lfile->i_boff = boot_bp->bp_part;
			status = opendev(lfdesc, lfile, 0);
			if (status == -1)	{
				dprint(dump_debug, 10,
					"etherinit: could not open '%c%c'\n",
					boot_bp->bp_dev[0],
					boot_bp->bp_dev[1]);
			} else {
			}
		} else {
#ifdef  DUMP_DEBUG
			dprint(dump_debug, 6,
				"etherinit: not '%c%c'\n",
				dp->b_dev[0],
				dp->b_dev[1]);
#endif  /* DUMP_DEBUG */
		}
	}

	if(status == -1)	{
		int c;

	        dprint(dump_debug, 10,
			"no ether device opened\n");
		printf ("input ether device name (");
		for (tablep = devsw; (0 != (dp = *tablep)); tablep++)
			printf ("%c%c%cd[01], ",
			    dp->b_dev[0], dp->b_dev[1], '%');
		printf ("): ");
		boot_bp->bp_dev[0] = getchar();
		boot_bp->bp_dev[1] = getchar();
		c = getchar();				/* CR */
		printf ("\n");
		if ((c == '0') || (c == '1'))
			boot_bp->bp_ctlr = c - '0';
		goto try;
	}


	/*
	 * Then try to attach the ether device.
	 */
	
	inet_ifp = (struct ifnet *)kmem_alloc(sizeof(struct ifnet));
	if (inet_ifp == (struct ifnet *)0)	{
		printf("ether_init: bad kmem_alloc\n");
	}
	ifnet = inet_ifp;
	init = 0;
	ioctl = 0;
	output = lfile->i_si.si_sif->sif_xmit;
	reset = lfile->i_si.si_sif->sif_reset;
	ether_attach(inet_ifp, 0, filename, init, ioctl, output, reset);
	/*
	 * Make the ifp point to the saioreq so that later
	 * we can pass a pointer to the saioreq to if_output().
	 * We are stealing if_lower for this purpose, since
	 * it's not used in a stand-alone system.
	 */
	inet_ifp->if_lower = (struct ifnet *)(&lfile->i_si);
	inet_ifp->if_next = (struct ifnet *)0;
	/*
	 * Pass the result back to the caller (ethersetup())
	 */
	*fdesc = lfdesc;
	*file = lfile;
	/*
	 * Initialise the routing table for this interface.
	 */
	if_rtinit(inet_ifp, RTF_UP);
}

/*
 * Get server address and partition number from si_unit and si_boff.
 *
 * This uses the no_nd struct.
 */
etheropen(sip)
	struct saioreq *sip;
{

	inet_init(sip, &no_nd.no_nd_inet, no_nd.no_nd_buf);

}

/*
 * Strategy routine.  User interface to do reads and writes
 * used to be through here.    No more.    Now we use the
 * ip routines, but the drivers need this stub.
 * We currently don't support writes.
 */
int
etherstrategy(sip, rw)
      register struct saioreq *sip;
      int rw;
{
#ifdef        DUMP_DEBUG
      dprint(dump_debug, 6,
              "etherstrategy(sip 0x%x, rw 0x%x)\n",
              sip,
              rw);
#endif  /* DUMP_DEBUG */
}

set_ether_addr(ip_address, ether_address)
	struct in_addr ip_address;
	struct ether_addr *ether_address;
{
	struct saioreq *sip;
	struct ifnet *ifp;
	struct sainet *sain;
	struct ifnet *if_ifwithaf();
	
	if((ifp = if_ifwithaf(AF_INET)) == (struct ifnet *)0)	{
	        dprint(dump_debug, 10, "set_ether_addr: bad ifp\n");
		return(-1);
	}

	sip = (struct saioreq *)ifp->if_lower;
	sain = &no_nd.no_nd_inet;

	myetheraddr(&sain->sain_myether);
	bcopy(&ip_address, &sain->sain_hisaddr.s_addr, sizeof(ip_address));

	arp(sip, sain, no_nd.no_nd_buf);

	bcopy(&sain->sain_hisether, ether_address, 6);
	return (0);
}

