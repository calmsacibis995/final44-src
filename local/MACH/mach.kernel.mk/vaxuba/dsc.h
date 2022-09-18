/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dsc.h,v $
 * Revision 2.3  89/03/09  22:33:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:02:16  gm0w
 * 	Changes for cleanup.
 * 
 * 17-Feb-83  Fil Alleva (faa) at Carnegie-Mellon University
 *	Started from the CARL driver to get the CMU asynchronos version
 */

/*------------------------------------------------------------------*
 * DSC.H - user include file for ioctl calls on the DSC
 *------------------------------------------------------------------*
 */

/* these values are critical;
 * dsseq depends on da being 0
 * and ad being 1
 */
#define DA		(0)
#define AD		(1)

/* Number of unibus data paths used
 */
#define NDP			(2)

/*
 * Errors.
 * Returned in ds_err.errors.
 */
#define EDS_ARGS	01	/* missing arguments/parameters */
#define EDS_ACC	02	/* converters in use */
#define EDS_BUFACC	04	/* bad buffer address */
#define EDS_DONE	010	/* converting finished, must reset */
#define EDS_BUFALL	020	/* bad buffer alligment */
#define EDS_CERR	040	/* converter error */
#define EDS_RST	0100	/* dsreset clobbered us */
#define EDS_CNT	0200    /* Odd byte count */
#define EDS_LCK	0400	/* Pages already locked */


/*
 * Channel defines
 */
#define ADCHN0	0
#define ADCHN1	1

#define DACHN0	8
#define DACHN1	9
#define DACHN2	10
#define DACHN3	11

/*
 * reg specifies a sequence register (0-15).
 * conv specifies a converter.
 * dirt specifies the direction when
 * setting up the sequence ram (DSSEQ) or the
 * sampling rate (DSRATE).
 */
struct ds_seq {
	short reg;
	short conv;
	short dirt;			/* shared by DSSEQ and DSRATE */
};

/*
 * Format of returned converter
 * errors.
 */
struct ds_err {
	short dma_csr;
	short asc_csr;
	short errors;
};

/*
 * Ioctl commands.
 */
#define DSSEQ		_IOW(s, 0, struct ds_seq)	/* set sequence */
#define DSRATE		_IOW(s, 1, struct ds_seq)	/* set rate */
#define DS20KHZ	_IO(s, 2)	/* set 20kHz filter */
#define DS6KHZ 	_IO(s, 3)	/* set 6.4 kHz filter */
#define DS3KHZ		_IO(s, 4)	/* set 3.2 kHz filter */
#define DSBYPASS	_IO(s, 5)	/* set bypass filter */
#define DSERRS		_IOR(s, 6, struct ds_err)	/* get errors */
#define DSREQ		_IOW(s, 7, struct ds_seq)	/* set # req to buf */
#define DSLAST		_IOW(s, 12, struct ds_seq)	/* last seq ram */
