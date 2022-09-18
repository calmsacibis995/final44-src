/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	des.c,v $
 * Revision 2.4  89/07/11  17:38:09  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:52:24  jjc]
 * 
 * Revision 2.3  89/03/09  21:41:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:50:42  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 *  5-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Use different names for uio segment flag field and uio
 *	segment flag values in Mach.
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)des.c 1.1 86/02/03 Copyr 1984 Sun Micro";
#endif

/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
 */

/*
 *  Des Chip driver - for AMD AmZ8068 (AMD9518)
 */
#include <des.h>
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/des.h>
#include <machine/pte.h>
#include <sundev/mbvar.h>
#include <mon/am8068.h>

/*
 * Driver information for auto-configuration stuff.
 */
int	desprobe();
struct	mb_device *desinfo[1];
struct	mb_driver desdriver = {
	desprobe, 0, 0, 0, 0, 0,
	sizeof (struct deschip), "des", desinfo, 0, 0, 0,
};

#define NDESCHAN	10
struct des_softc {
	struct	deschip *des_addr;
	struct	desstate {
		struct	deskey dest_key;
		struct	desivec	dest_ivec;
		char	dest_open;
		char	dest_init;
	} deschan[NDESCHAN];
} des;
struct buf desbuf;

desprobe(reg)
	caddr_t reg;
{
	int i;
	register struct deschip *desbase = (struct deschip *)reg;
	register int c;

	if ((c = pokec((char *)&desbase->d_selector, DESR_CMD_STAT)) != 0)
		return (0);
	if ((c = pokec((char *)&desbase->d_reg, DESC_RESET)) != 0)
		return (0);
	for (i = 0; i < 100; i++) /* wait for reset */
		continue;
	if ((c = pokec((char *)&desbase->d_selector, DESR_MODE)) != 0)
		return (0);
	c = peekc((char *)&desbase->d_reg);
	if (c == -1)
		return 0;
	if ((c&0xf)  != DESM_MC_SE)
		return (0);
	des.des_addr = (struct deschip *)reg;
	return (sizeof (struct deschip));
}

/*ARGSUSED*/
desopen(dev, flag)
	dev_t dev;
	int flag;
{
 	int unit = minor(dev);
	register struct desstate *ds = &des.deschan[unit];

	if (unit >= NDESCHAN || des.des_addr == 0)
		return (ENXIO);
	if (ds->dest_open)
		return (EBUSY);
	ds->dest_open = 1;
	ds->dest_init = 0;
	return (0);
}

/*ARGSUSED*/
desclose(dev, flag)
	dev_t dev;
	int flag;
{
 	int unit = minor(dev);
	register struct desstate *ds = &des.deschan[unit];
	int i;

	ds->dest_init = 0;
	ds->dest_open = 0;
	for (i=0; i<8; i++)
		ds->dest_key.des_key[i] = 0;	/* for security */
}

/*ARGSUSED*/
desioctl(dev, cmd, data, flag)
	dev_t dev;
	int cmd, flag;
	caddr_t data;
{
 	int unit = minor(dev);
	register struct desstate *ds = &des.deschan[unit];
	register struct deskey *dm;
	register struct desivec *iv;
	register struct desblock *db;
	register short i;

	if (ds->dest_init == 0 && cmd != DESIOCSETKEY)
		return (EINVAL);

	switch(cmd) {

	case DESIOCSETKEY:
		dm = (struct deskey *)data;
		if (dm->des_dir != ENCRYPT && dm->des_dir != DECRYPT)
			return (EINVAL);
		if (dm->des_mode != ECB && dm->des_mode != CBC)
			return (EINVAL);
		ds->dest_key = *dm;
		for (i=0; i<8; i++)
			ds->dest_ivec.des_ivec[i] = 0;
		ds->dest_init = 1;
		break;

	case DESIOCGETKEY:
		dm = (struct deskey *)data;
		*dm = ds->dest_key;
		break;

	case DESIOCSETIVEC:
		iv = (struct desivec *)data;
		ds->dest_ivec = *iv;
		break;

	case DESIOCGETIVEC:
		iv = (struct desivec *)data;
		*iv = ds->dest_ivec;
		break;

	case DESIOCBLOCK:
		db = (struct desblock *)data;
		return (desblock(dev, db->des_data, db->des_len));

	case DESIOCCHUNK:
		desdoit(ds, (u_char *)data, 8);
		return (0);

	default:
		return (ENOTTY);
	}
	return (0);
}

/* 
 * Process a block of data
 * This is very much like a driver read since we modify the
 * user's buffer
 */
desblock(dev, addr, len)
	char	*addr;
	int	len;
{
	struct uio uio;
	struct iovec iov;
	int desstrategy();

	if (len <= 0 || (len % 8) != 0)
		return (EINVAL);
	iov.iov_base = addr;
	iov.iov_len = len;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = 0;
#ifdef	MACH
	uio.uio_segflg = UIO_USERSPACE;
#else	MACH
	uio.uio_seg = UIOSEG_USER;
#endif	MACH
	uio.uio_resid = len;
	return (physio(desstrategy, &desbuf, dev, B_READ, minphys, &uio));
}

desstrategy(bp)
	register struct buf *bp;
{
	int unit = minor(bp->b_dev);

	desdoit(&des.deschan[unit], (u_char *)bp->b_un.b_addr,
	    (int)bp->b_bcount);
	bp->b_resid = 0;
	iodone(bp);
}

/*
 * Do the real work
 * We only run the chip in ECB mode; implementing CBC externally
 * because I couldn't reliably read the intermediate IVs out of the chip
 * to maintain state between calls to this routine.
 */
desdoit(ds, in, len)
	register struct desstate *ds;
	register u_char *in;
	int len;
{
	register short mode = DESM_M_ONLY | DESM_ECB;
	register u_char *out, *iv;
	u_char *end, nextiv[8];
	register struct deschip *desp = des.des_addr;

	if (ds->dest_key.des_dir == ENCRYPT)
		mode |= DESM_ENCRYPT;
	else
		mode |= DESM_DECRYPT;
	/* 
	 * set mode of DES chip
	 */
        desp->d_selector = DESR_MODE;	/* select mode reg */
	desp->d_reg = mode;
	DELAY(4);

	/* 
	 * load DES key
	 */
	desp->d_selector = DESR_CMD_STAT;	/* select cmd reg */
	if (ds->dest_key.des_dir == ENCRYPT)
		desp->d_reg = DESC_LOAD_E_KEY;	/* load E key */
	else
		desp->d_reg = DESC_LOAD_D_KEY;	/* load D key */
	desp->d_selector = DESR_IO;
	iv = ds->dest_key.des_key;
	desp->d_reg = *iv++; desp->d_reg = *iv++;
	desp->d_reg = *iv++; desp->d_reg = *iv++;
	desp->d_reg = *iv++; desp->d_reg = *iv++;
	desp->d_reg = *iv++; desp->d_reg = *iv++;
	/*
	 * Start the engine
	 */
	desp->d_selector = DESR_CMD_STAT;	/* select cmd reg */
	desp->d_reg = DESC_START;

	end = in + len;
	while (in < end) {
		out = in;
		if (ds->dest_key.des_mode == CBC) {
			if (ds->dest_key.des_dir == ENCRYPT) {
				iv = ds->dest_ivec.des_ivec;
				*out++ ^= *iv++; *out++ ^= *iv++;
				*out++ ^= *iv++; *out++ ^= *iv++;
				*out++ ^= *iv++; *out++ ^= *iv++;
				*out++ ^= *iv++; *out++ ^= *iv++;
			} else {
				iv = nextiv;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
			}
			out = in;
		}
		/* 
		 * feed in 8 bytes of input
		 */
		desp->d_selector = DESR_IO;
		desp->d_reg = *in++; desp->d_reg = *in++;
		desp->d_reg = *in++; desp->d_reg = *in++;
		desp->d_reg = *in++; desp->d_reg = *in++;
		desp->d_reg = *in++; desp->d_reg = *in++;
		desp->d_selector = DESR_CMD_STAT;	/* select cmd reg */
		while (desp->d_reg & DESS_BUSY)
			;
		/*
		 * Swallow 8 bytes of output
		 */
		desp->d_selector = DESR_IO;
		*out++ = desp->d_reg; *out++ = desp->d_reg;
		*out++ = desp->d_reg; *out++ = desp->d_reg;
		*out++ = desp->d_reg; *out++ = desp->d_reg;
		*out++ = desp->d_reg; *out++ = desp->d_reg;
		if (ds->dest_key.des_mode == CBC) {
			out -= 8;
			if (ds->dest_key.des_dir == ENCRYPT) {
				iv = ds->dest_ivec.des_ivec;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
			} else {
				iv = ds->dest_ivec.des_ivec;
				*out++ ^= *iv++; *out++ ^= *iv++;
				*out++ ^= *iv++; *out++ ^= *iv++;
				*out++ ^= *iv++; *out++ ^= *iv++;
				*out++ ^= *iv++; *out++ ^= *iv++;
				iv -= 8;
				out = nextiv;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
				*iv++ = *out++; *iv++ = *out++;
			}
		}
	}
}
