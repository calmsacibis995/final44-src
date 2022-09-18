h29509
s 00002/00002/00193
d D 8.1 93/06/10 22:30:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00195/00000/00000
d D 7.1 92/12/13 03:50:26 akito 1 0
c date and time created 92/12/13 03:50:26 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * scsi.c -- front end of SCSI test commands
 * by A.Fujita, FEB-09-1992
 */

#include <sys/param.h>
#include <luna68k/dev/scsireg.h>
#include <luna68k/stand/status.h>


int scsi_device = 6;

#define SENSBUFF 8					/* %G%P%$%9%I%i%$%P$G%;%s%9%G!<%? */
							/* $ND9$5$r#8%P%$%H0JFb$K8GDj$7$F */
u_char	sensbuff[SENSBUFF];				/* #80J>e$OL50UL#$G$"$k!#         */

static struct scsi_inquiry inquirybuf;
static struct scsi_fmt_cdb inquiry = {
	6,
	CMD_INQUIRY, 0, 0, 0, sizeof(inquirybuf), 0
};

static u_long capacitybuf[2];
struct scsi_fmt_cdb capacity = {
	10,
	CMD_READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


int
scsi(argc, argv)
	int   argc;
	char *argv[];
{
	register char *p;
	register int i, status;

	if (argc < 2) {
		printf("This command is required subcommand !!\n");
		return(ST_ERROR);
	}

	if (!strcmp(argv[1], "device")) {
		if (argc > 2) {
			i = 0;
			for (p = argv[2]; *p != NULL; p++) {
				i = i * 10 + *p - '0';
			}
			if ( i < 8 && i >= 0) {
				scsi_device = i;
			}
		}
		printf("Current Device ID: %d\n", scsi_device);
	} else if (!strcmp(argv[1], "test_unit_rdy")) {
				/* CTLR  SLAVE  LUN */
		scsi_test_unit_rdy(   0, scsi_device,   0);
	} else if (!strcmp(argv[1], "request_sense")) {
			        /* CTLR  SLAVE  LUN */
		scsi_request_sense(   0, scsi_device,   0, sensbuff, SENSBUFF);
	} else if (!strcmp(argv[1], "inquiry")) {
		if (scsi_immed_command(   0, scsi_device,   0, &inquiry,
				       (u_char *) &inquirybuf, sizeof(inquirybuf)) == 0) {
			printf("Type:\t0x%x\n",		inquirybuf.type);
			printf("Qualifier:\t0x%x\n",	inquirybuf.qual);
			printf("Version:\t0x%x\n",	inquirybuf.version);
			printf("RDF:\t0x%x\n",		inquirybuf.rsvd);
			
			printf("Vender ID:\t");
			for (i = 0; i < 8; i++)
				printf("%c", inquirybuf.vendor_id[i]);
			printf("\n");
			
			printf("Product ID:\t");
			for (i = 0; i < 16; i++)
				printf("%c", inquirybuf.product_id[i]);
			printf("\n");
			
			printf("Revision:\t");
			for (i = 0; i < 4; i++)
				printf("%c", inquirybuf.rev[i]);
			printf("\n");
		}
	} else if (!strcmp(argv[1], "read_capacity")) {
		if (scsi_immed_command(   0, scsi_device,   0, &capacity,
				       (u_char *) &capacitybuf, sizeof(capacitybuf)) == 0) {
			printf("Logical Block Address:\t%d (0x%x)\n",
			       capacitybuf[0], capacitybuf[0]);
			printf("Block Length:\t\t%d (0x%x)\n",
			       capacitybuf[1], capacitybuf[1]);
		}
	} else if (!strcmp(argv[1], "trace")) {
		for (i = 0; i < 7; i++) {
			printf("SCSI ID %d .... ", i);
			status = scsi_test_unit_rdy( 0, i, 0);
			if (status >= 0)
				printf("found.\n");
			else
				printf("no.\n");
		}
	} else if (!strcmp(argv[1], "format_unit")) {
		i = 0;
		while (i == 0) {
			printf("Do you really want to format SCSI %d device ? [y/n]: ",
			       scsi_device);
			i = cngetc();
			printf("\n");
			if ((i != 'y') && (i != 'Y') && (i != 'n') && (i != 'N'))
				i = 0;
		}

		if ((i == 'y') || (i == 'Y'))
			status = scsi_format_unit( 0, scsi_device, 0);
	}

	return(ST_NORMAL);
}

static struct scsi_fmt_cdb scsi_cdb = {
	10,
	0,  0, 0, 0, 0, 0, 0, 0, 0, 0
};

int
scsi_read_raw(target, blk, nblk, buff, len)
	u_int   target;
	u_int   blk;
	u_int   nblk;
	u_char *buff;
	u_int   len;
{
	register struct scsi_fmt_cdb *cdb = &scsi_cdb;

	cdb->cdb[0] = CMD_READ_EXT;
	
	cdb->cdb[2] = (blk & 0xff000000) >> 24;
	cdb->cdb[3] = (blk & 0x00ff0000) >> 16;
	cdb->cdb[4] = (blk & 0x0000ff00) >>  8;
	cdb->cdb[5] = (blk & 0x000000ff);
	
	cdb->cdb[7] = (nblk & 0xff00) >> 8;
	cdb->cdb[8] = (nblk & 0x00ff);
	
	if (scsi_immed_command(0, target, 0, cdb, buff, len) == 0)
		return(1);
	else
		return(0);
}

int
scsi_read(blk, buff, len)
	u_int   blk;
	u_char *buff;
	u_int   len;
{
	u_int   nblk = len >> DEV_BSHIFT;
	
	return(scsi_read_raw(scsi_device, blk, nblk, buff, len));
}

int
scsi_write(blk, buff, len)
	u_int   blk;
	u_char *buff;
	u_int   len;
{
	register struct scsi_fmt_cdb *cdb = &scsi_cdb;

	cdb->cdb[0] = CMD_WRITE_EXT;
	
	cdb->cdb[2] = (blk & 0xff000000) >> 24;
	cdb->cdb[3] = (blk & 0x00ff0000) >> 16;
	cdb->cdb[4] = (blk & 0x0000ff00) >>  8;
	cdb->cdb[5] = (blk & 0x000000ff);
	
	cdb->cdb[7] = ((len >> DEV_BSHIFT) & 0xff00) >> 8;
	cdb->cdb[8] = ((len >> DEV_BSHIFT) & 0x00ff);
	
	if (scsi_immed_command(0, scsi_device, 0, cdb, buff, len) == 0)
		return(1);
	else
		return(0);
}
E 1
