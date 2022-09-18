h26571
s 00004/00004/00634
d D 5.5 94/04/02 10:00:59 bostic 5 4
c copyright cleanup
e
s 00478/00256/00160
d D 5.4 93/06/05 12:38:31 bostic 4 3
c new version from Chris Torek
e
s 00082/00005/00334
d D 5.3 93/06/05 11:21:34 bostic 3 2
c checkpoint; Van's new version, but it doesn't work either
e
s 00051/00051/00288
d D 5.2 92/07/20 15:50:13 bostic 2 1
c minor cleanup, update, fix argument processing (which I broke)
e
s 00339/00000/00000
d D 5.1 92/07/20 12:09:03 bostic 1 0
c date and time created 92/07/20 12:09:03 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
#ifndef lint
char copyright[] =
D 5
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
#include <sys/param.h>
#include <sys/ioctl.h>
D 4
#include <hp300/dev/scsireg.h>
E 4

D 4
#include <fcntl.h>
E 4
I 4
#include <dev/scsi/scsi.h>
#include <dev/scsi/disk.h>
#include <dev/scsi/disktape.h>
#include <dev/scsi/scsi_ioctl.h>

#define COMPAT_HPSCSI

E 4
#include <errno.h>
D 4
#include <unistd.h>
#include <stdlib.h>
E 4
I 4
#include <fcntl.h>
E 4
#include <stdio.h>
I 4
#include <stdlib.h>
E 4
#include <string.h>
I 4
#include <unistd.h>
E 4

D 4
struct scsi_inquiry inqbuf;
struct {
	int blks;
	int blksize;
} capbuf;
struct {
	struct scsi_modesense_hdr h;
	u_char p[126-12];
} msbuf;
I 3
u_char mselbuf[24];
E 3

I 3
struct scsi_fmt_cdb cap = {
	10,
	CMD_READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
struct scsi_fmt_cdb format = {
	6,
	CMD_FORMAT_UNIT, 0, 0, 0, 0, 0
};
E 3
struct scsi_fmt_cdb inq = {
	6,
	CMD_INQUIRY, 0, 0, 0, sizeof(inqbuf), 0
};
D 3
struct scsi_fmt_cdb cap = {
	10,
	CMD_READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0
E 3
I 3
struct scsi_fmt_cdb modeselect = {
	6,
	CMD_MODE_SELECT, 0x11, 0, 0, sizeof(mselbuf), 0
E 3
};
struct scsi_fmt_cdb modesense = {
	6,
	CMD_MODE_SENSE, 0, 0x3f, 0, sizeof(msbuf), 0
};

E 4
int fd;
char *device;

D 4
void	do_command __P((int, struct scsi_fmt_cdb *, u_char *, int));
E 4
I 4
void	scsi_str __P((char *, char *, int));
void	do_command __P((int, struct scsi_cdb *, void *, int));
E 4
I 3
void	do_format __P((void));
E 3
void	print_capacity __P((void));
void	print_inquiry __P((void));
I 4
void	prflags __P((int, const char *));
E 4
u_char *print_mode_page __P((u_char *));
void	print_mode_sense __P((void));
void	usage __P((void));

I 4
#define	N2(c, d)	(((c) << 8) | (d))
#define	N3(b, c, d)	(((b) << 16) | N2(c, d))
#define	N4(a, b, c, d)	(((a) << 24) | N3(b, c, d))

int	sense_pctl;

E 4
int
D 3
main (argc, argv)
E 3
I 3
main(argc, argv)
E 3
	int argc;
	char *argv[];
{
D 4
	int ch;
E 4
I 4
	extern char *optarg;
	int ch, readonly;
E 4

D 4
	while ((ch = getopt(argc, argv, "")) != EOF)
E 4
I 4
	readonly = 0;
	sense_pctl = SCSI_MSENSE_PCTL_CUR;
	while ((ch = getopt(argc, argv, "rp:")) != EOF) {
E 4
		switch(ch) {
I 4
		case 'r':
			readonly = 1;
			break;
		case 'p':		/* mode sense page control */
			switch (*optarg) {
			case 'c':
				sense_pctl = SCSI_MSENSE_PCTL_CUR;
				break;
			case 'd':
				sense_pctl = SCSI_MSENSE_PCTL_DFLT;
				break;
			case 's':
				sense_pctl = SCSI_MSENSE_PCTL_SAVED;
				break;
			case 'v':
				(void)printf(
	"*** note: for variable parameters, 1-bit means ``can write here''\n");
				sense_pctl = SCSI_MSENSE_PCTL_VAR;
				break;
			}
			/* FALLTHROUGH */
E 4
		case '?':
		default:
			usage();
		}
I 4
	}
E 4
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

D 2
	device = argv[1];
	if ((fd = open(device, O_RDONLY, 0)) < 0) {
E 2
I 2
	device = *argv;
D 4
	if ((fd = open(device, O_RDWR, 0)) < 0) {
E 4
I 4
	fd = open(device, readonly ? O_RDONLY : O_RDWR, 0);
	if (fd < 0) {
E 4
E 2
		(void)fprintf(stderr,
		    "scsiformat: %s: %s\n", device, strerror(errno));
		exit(1);
	}
	print_inquiry();
	print_capacity();
	print_mode_sense();
I 3

D 4
	do_format();
E 4
I 4
	if (!readonly)
		do_format();
E 4
E 3
	exit(0);
}

I 4
/*
 * Copy a counted string, trimming trailing blanks, and turning the
 * result into a C-style string.
 */
E 4
void
I 4
scsi_str(src, dst, len)
	register char *src, *dst;
	register int len;
{

	while (src[len - 1] == ' ') {
		if (--len == 0) {
			*dst = 0;
			return;
		}
	}
	bcopy(src, dst, len);
	dst[len] = 0;
}

void
E 4
D 2
do_command(fd, cdb, buf, len)
	int fd;
	struct scsi_fmt_cdb *cdb;
	u_char *buf;
	int len;
{
	static int on = 1;
	static int off = 0;

	if (ioctl(fd, SDIOCSFORMAT, &on) < 0) {
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSFORMAT (on): %s\n", strerror(errno));
		return;
	}
	if (ioctl(fd, SDIOCSCSICOMMAND, cdb) < 0)
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSCSICOMMAND: %s\n", strerror(errno));
	else if (read(fd, buf, len) < 0)
		(void)fprintf(stderr,
		    "scsiformat: read: %s\n", strerror(errno));

	if (ioctl(fd, SDIOCSFORMAT, &off) < 0)
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSFORMAT (off): %s\n", strerror(errno));
}

void
E 2
print_inquiry()
{
D 4
	char idstr[32];
	int i;
E 4
I 4
	register struct scsi_inq_ansi *si;
	int ver;
	struct scsi_inquiry inqbuf;
	char vendor[10], product[17], rev[5];
	static struct scsi_cdb inq = {
		CMD_INQUIRY, 0, 0, 0, sizeof(inqbuf), 0
	};
E 4

D 4
	do_command(fd, &inq, (u_char *)&inqbuf, sizeof(inqbuf));
	printf("%s: ", device);
E 4
I 4
	do_command(fd, &inq, &inqbuf, sizeof(inqbuf));
	(void)printf("%s: ", device);
E 4

D 4
	if (inqbuf.version != 1) {
		printf("type 0x%x, qual 0x%x, ver %d\n", inqbuf.type,
			inqbuf.qual, inqbuf.version);
E 4
I 4
	ver = (inqbuf.si_version >> VER_ANSI_SHIFT) & VER_ANSI_MASK;
	if (ver != 1 && ver != 2) {
		(void)printf("type 0x%x, qual 0x%x, ver 0x%x (ansi %d)\n",
		    inqbuf.si_type, inqbuf.si_qual, inqbuf.si_version, ver);
E 4
		return;
	}
D 4
	switch (inqbuf.type) {
	case 0:		printf("(disk)"); break;
	case 4:		printf("(WORM)"); break;
	case 5:		printf("(CD-ROM)"); break;
	case 7:		printf("(MO-DISK)"); break;
	default:	printf("(??)"); break;
E 4
I 4
	si = (struct scsi_inq_ansi *)&inqbuf;
	switch (si->si_type & TYPE_TYPE_MASK) {

	case TYPE_DAD:
		(void)printf("(disk)");
		break;

	case TYPE_WORM:
		(void)printf("(WORM)");
		break;

	case TYPE_ROM:
		(void)printf("(CD-ROM)");
		break;

	case TYPE_MO:
		(void)printf("(MO-DISK)");
		break;

	case TYPE_JUKEBOX:
		(void)printf("(jukebox)");
		break;

	default:
		(void)printf("(??)");
		break;
E 4
	}
D 4
	bcopy((caddr_t)&inqbuf.vendor_id, (caddr_t)idstr, 28);
	for (i = 27; i > 23; --i)
		if (idstr[i] != ' ')
			break;
	idstr[i+1] = 0;
	for (i = 23; i > 7; --i)
		if (idstr[i] != ' ')
			break;
	idstr[i+1] = 0;
	for (i = 7; i >= 0; --i)
		if (idstr[i] != ' ')
			break;
	idstr[i+1] = 0;
	printf(" %s %s rev %s:", idstr, &idstr[8], &idstr[24]);
E 4
I 4
	scsi_str(si->si_vendor, vendor, sizeof(si->si_vendor));
	scsi_str(si->si_product, product, sizeof(si->si_product));
	scsi_str(si->si_rev, rev, sizeof(si->si_rev));
	(void)printf(" %s %s rev %s:", vendor, product, rev);
E 4
}

void
print_capacity()
{
D 4
	do_command(fd, &cap, (u_char *)&capbuf, sizeof(capbuf));
	printf(" %d blocks of %d bytes each\n", capbuf.blks, capbuf.blksize);
E 4
I 4
	struct scsi_rc rc;		/* for READ CAPACITY */
	static struct scsi_cdb cap = { CMD_READ_CAPACITY };

	do_command(fd, &cap, &rc, sizeof(rc));
	(void)printf(" %d blocks of %d bytes each\n",
	    N4(rc.rc_lbah, rc.rc_lbahm, rc.rc_lbalm, rc.rc_lbal) + 1,
	    N4(rc.rc_blh, rc.rc_blhm, rc.rc_bllm, rc.rc_bll));
E 4
}

I 2
void
print_mode_sense()
{
D 4
	u_char *cp;
	u_char *ep;
E 4
I 4
	register u_char *cp, *ep;
	register struct scsi_ms_bd *bd;
	register int n, i, l, len, bdlen;
#ifdef TEN_BYTE_SENSE
	struct {
		struct	scsi_ms10 ms;
		u_char	p[1023 - sizeof(struct scsi_ms10)];
	} msbuf;
	static struct scsi_cdb modesense = {
		CMD_MODE_SENSE10, SCSI_MSENSE_DBD, 0, 0, 0, 0, 0,
		sizeof(msbuf) >> 8, sizeof (msbuf), 0
	};
E 4

D 4
	do_command(fd, &modesense, (u_char *)&msbuf, sizeof(msbuf));
E 4
I 4
	CDB10(&modesense)->cdb_lbam = sense_pctl | SCSI_MS_PC_ALL;
	do_command(fd, &modesense, &msbuf, sizeof(msbuf));
	len = N2(msbuf.ms.ms_lenh, msbuf.ms.ms_lenl);
	bdlen = N2(msbuf.ms.ms_bdlh, msbuf.ms.ms_bdll);
#else
	struct {
		struct	scsi_ms6 ms;
		u_char	p[255 - sizeof(struct scsi_ms6)];
	} msbuf;
	static struct scsi_cdb modesense = {
		CMD_MODE_SENSE6, 0, 0, 0, sizeof(msbuf), 0
	};
E 4

D 4
	printf("\n%d bytes of mode sense data.  ", msbuf.h.len);
	printf("media type %d, %swrite protected\n", msbuf.h.media_type,
		msbuf.h.wp? "" : "not ");
	if (msbuf.h.block_desc_len) {
		printf("density 0x%x, ", msbuf.h.density);
		if (msbuf.h.number_blocks)
			printf("%d blocks of length %d\n",
				msbuf.h.number_blocks, msbuf.h.block_length);
		else
			printf("all blocks of length %d\n",
				msbuf.h.block_length);
		cp = msbuf.p;
	} else
		cp = &msbuf.h.block_desc_len + 1;

	ep = (u_char *)&msbuf + msbuf.h.len;
E 4
I 4
	CDB6(&modesense)->cdb_lbam = sense_pctl | SCSI_MS_PC_ALL;
	do_command(fd, &modesense, &msbuf, sizeof(msbuf));
	len = msbuf.ms.ms_len;
	bdlen = msbuf.ms.ms_bdl;
#endif
	(void)printf("\n%d bytes of mode sense data. ", len);
	(void)printf("medium type 0x%x, %swrite protected\n",
	    msbuf.ms.ms_mt, msbuf.ms.ms_dsp & SCSI_MS_DSP_WP ? "" : "not ");
	if ((n = bdlen) != 0) {
		bd = (struct scsi_ms_bd *)msbuf.p;
		for (n /= sizeof(*bd); --n >= 0; bd++) {
			(void)printf("\tdensity code 0x%x, ", bd->bd_dc);
			i = N3(bd->bd_nbh, bd->bd_nbm, bd->bd_nbl);
			l = N3(bd->bd_blh, bd->bd_blm, bd->bd_bll);
			if (i)
				(void)printf("%d blocks of length %d\n", i, l);
			else
				(void)printf("all blocks of length %d\n", l);
		}
	}
	/*
	 * Sense header lengths includes the sense header, while mode page
	 * lengths do not ... let's hear it for consistency!
	 */
	cp = msbuf.p + bdlen;
	ep = msbuf.p + len - sizeof(msbuf.ms);
E 4
	while (cp < ep)
		cp = print_mode_page(cp);
}

I 4
void
prflags(v, cp)
	int v;
	register const char *cp;
{
	register const char *np;
	char f, sep;

	for (sep = '<'; (f = *cp++) != 0; cp = np) {
		for (np = cp; *np >= ' ';)
			np++;
		if ((v & (1 << (f - 1))) == 0)
			continue;
		printf("%c%.*s", sep, np - cp, cp);
		sep = ',';
	}
	if (sep != '<')
		putchar('>');
}

static char *
cache_policy(x)
	int x;
{
	static char rsvd[30];

	switch (x) {

	case SCSI_CACHE_DEFAULT:
		return ("default");

	case SCSI_CACHE_KEEPPF:
		return ("toss cmd data, save prefetch");

	case SCSI_CACHE_KEEPCMD:
		return ("toss prefetch data, save cmd");

	default:
		(void)sprintf(rsvd, "reserved %d", x);
		return (rsvd);
	}
	/* NOTREACHED */
}

E 4
E 2
u_char *
print_mode_page(cp)
	u_char *cp;
{
D 4
	int n = cp[1];
	int i;
	char c;
E 4
I 4
	register struct scsi_ms_page_hdr *mp;
	int len, code, i;
	u_char *tp;
	const char *s;
E 4

D 4
	printf("\npage type %d%s (%d bytes): ", cp[0] & 0x7f,
		(cp[0] & 0x80)? " (saveable)" : "", n);
	switch (cp[0] & 0x7f) {
	case 1:
		printf("Error Recovery parameters.\n");
		printf("\tflags = 0x%x ", i = cp[2]);
		c = '<';
		if (i & 0x80) {
			printf("%cAWRE", c);
			c = ',';
		}
		if (i & 0x40) {
			printf("%cARRE", c);
			c = ',';
		}
		if (i & 0x20) {
			printf("%cTB", c);
			c = ',';
		}
		if (i & 0x10) {
			printf("%cRC", c);
			c = ',';
		}
		if (i & 0x08) {
			printf("%cEEC", c);
			c = ',';
		}
		if (i & 0x04) {
			printf("%cPER", c);
			c = ',';
		}
		if (i & 0x02) {
			printf("%cDTE", c);
			c = ',';
		}
		if (i & 0x01) {
			printf("%cDCR", c);
			c = ',';
		}
		if (c == ',')
			printf(">");
E 4
I 4
	mp = (struct scsi_ms_page_hdr *)cp;
	code = mp->mp_psc & SCSI_MS_PC_MASK;
	len = mp->mp_len;
	(void)printf("\npage type %d%s (%d bytes): ",
	    code, mp->mp_psc & SCSI_MS_MP_SAVEABLE ? " (saveable)" : "", len);
	switch (code) {
E 4

D 4
		printf("\n\t%d retries, %d correction span bits,\n", cp[3],
			cp[4]);
		printf("\t%d head offsets, %d data strobe offsets,\n\t",
			cp[5], cp[6]);
		if (cp[7] != 0xff)
			printf("%d", cp[7]);
E 4
I 4
	case SCSI_MS_PC_RWERRREC:
#define	rw ((struct scsi_page_rwerrrec *)(mp + 1))
		(void)printf("Read/Write Error Recovery parameters.\n");
		(void)printf("\tflags = 0x%x", rw->rw_flags);
		prflags(rw->rw_flags,
		    "\10AWRE\7ARRE\6TB\5RC\4EER\3PER\2DTE\1DCR");
		(void)printf(",\n\t%d read retries, %d correction span bits,\n",
		    rw->rw_read_retry, rw->rw_corr_span);
		(void)printf("\t%d head offsets, %d data strobe offsets%s\n",
		    rw->rw_hd_off, rw->rw_ds_off, len > 6 ? "," : ".");
		if (len <= 6)
			break;
		(void)printf("\t%d write retries, ", rw->rw_write_retry);
		i = N2(rw->rw_rtlh, rw->rw_rtll);
		if (i != 0xffff)
			(void)printf("%d", i);
E 4
		else
D 4
			printf("no");
		printf(" recovery time limit.\n");
		cp += 8;
E 4
I 4
			(void)printf("no");
		(void)printf(" recovery time limit.\n");
E 4
		break;
I 4
#undef rw
E 4

D 4
	case 2:
		printf("Disconnect/Reconnect control.\n");
		printf("\tbuffer full ratio %d, buffer empty ratio %d,\n",
			cp[2], cp[3]);
		printf("\ttime limits: %d bus inactivity, ",
			*(u_short *)&cp[4]);
		printf("%d disconnect, %d connect.\n",
			*(u_short *)&cp[6],*(u_short *)&cp[8]);
		cp += 12;
E 4
I 4
	case SCSI_MS_PC_DR:
#define	dr ((struct scsi_page_dr *)(mp + 1))
		(void)printf("Disconnect/Reconnect control.\n");
		(void)printf("\tbuffer full ratio %d, buffer empty ratio %d,\n",
		    dr->dr_full, dr->dr_empty);
		(void)printf("\ttime limits: %d bus inactivity, ",
		    N2(dr->dr_inacth, dr->dr_inactl));
		(void)printf("%d disconnect, %d connect.\n",
		    N2(dr->dr_disconh, dr->dr_disconl),
		    N2(dr->dr_conh, dr->dr_conl));
		(void)printf("\tmaximum burst size %d,\n",
		    N2(dr->dr_bursth, dr->dr_burstl));
		switch (dr->dr_dtdc & SCSI_DR_DTDC_MASK) {
		case SCSI_DR_DTDC_NONE:
			s = "never";
			break;
		case SCSI_DR_DTDC_NOTDATA:
			s = "during data transfer";
			break;
		case SCSI_DR_DTDC_RSVD:
			s = "???";
			break;
		case SCSI_DR_DTDC_NOTD2:
			s = "during and after data transfer";
			break;
		}
		(void)printf("\tsuppress disconnect %s.\n", s);
E 4
		break;
I 4
#undef dr
E 4

D 4
	case 3:
		{
		struct scsi_format *sf = (struct scsi_format *)cp;
		printf("Format parameters.\n");
		printf("\t%d tracks/zone, %d alt.sect./zone, ",
			sf->tracks_per_zone, sf->alt_sect_zone);
		printf("%d alt.tracks/zone,\n\t%d alt.tracks/vol., ",
			sf->alt_tracks_zone, sf->alt_tracks_vol);
		printf("%d sectors/track, %d bytes/sector, interleave %d\n",
			sf->sect_track, sf->data_sect, sf->interleave);
		printf("\ttrack skew %d, cylinder skew %d,\n",
			sf->track_skew_factor, sf->cyl_skew_factor);
		printf("\tdrive type 0x%x ", i = cp[20]);
		c = '<';
		if (i & 0x80) {
			printf("%cSSEC", c);
			c = ',';
E 4
I 4
	case SCSI_MS_PC_FMT:
#define	fmt ((struct scsi_page_fmt *)(mp + 1))
		(void)printf("Format parameters.\n");
		(void)printf("\t%d tracks/zone, %d alt.sect./zone, ",
		    N2(fmt->fmt_tpzh, fmt->fmt_tpzl),
		    N2(fmt->fmt_aspzh, fmt->fmt_aspzl));
		(void)printf("%d alt.tracks/zone,\n\t%d alt.tracks/vol., ",
		    N2(fmt->fmt_atpzh, fmt->fmt_atpzl),
		    N2(fmt->fmt_atpvh, fmt->fmt_atpvl));
		(void)printf("%d sectors/track, %d bytes/phys.sector,\n",
		    N2(fmt->fmt_spth, fmt->fmt_sptl),
		    N2(fmt->fmt_dbppsh, fmt->fmt_dbppsl));
		(void)printf("\tinterleave %d, track skew %d, cyl.skew %d,\n",
		    N2(fmt->fmt_ilh, fmt->fmt_ill),
		    N2(fmt->fmt_tsfh, fmt->fmt_tsfl),
		    N2(fmt->fmt_csfh, fmt->fmt_csfl));
		(void)printf("\tdrive flags 0x%x", fmt->fmt_flags);
		prflags(fmt->fmt_flags, "\10SSEC\7HSEC\6RMB\5SURF");
		(void)printf(".\n");
		break;
#undef fmt

	case SCSI_MS_PC_RDGEOM:
#define rd ((struct scsi_page_rdgeom *)(mp + 1))
		(void)printf("Disk Geometry parameters.\n");
		(void)printf("\t%d cylinders, %d heads,\n",
		    N3(rd->rd_ncylh, rd->rd_ncylm, rd->rd_ncyll),
		    rd->rd_nheads);
		(void)printf("\tstart write precompensation at cyl %d,\n",
		    N3(rd->rd_wpcylh, rd->rd_wpcylm, rd->rd_wpcyll));
		(void)printf("\tstart reduced write current at cyl %d,\n",
		    N3(rd->rd_rwcylh, rd->rd_rwcylm, rd->rd_rwcyll));
		(void)printf("\tseek step rate %f us, landing zone cyl %d,\n",
		    N2(rd->rd_steph, rd->rd_stepl) * 0.1,
		    N3(rd->rd_lcylh, rd->rd_lcylm, rd->rd_lcyll));
		switch (rd->rd_rpl & SCSI_RD_RPL_MASK) {
		case SCSI_RD_RPL_NONE:
			s = "disabled or unsupported";
			break;
		case SCSI_RD_RPL_SLAVE:
			s = "slave";
			break;
		case SCSI_RD_RPL_MASTER:
			s = "master";
			break;
		case SCSI_RD_RPL_MCONTROL:
			s = "master control";
			break;
E 4
		}
D 4
		if (i & 0x40) {
			printf("%cHSEC", c);
			c = ',';
		}
		if (i & 0x20) {
			printf("%cRMB", c);
			c = ',';
		}
		if (i & 0x10) {
			printf("%cSURF", c);
			c = ',';
		}
		if (i & 0x08) {
			printf("%cINS", c);
			c = ',';
		}
		if (i & 0x04) {
			printf("%c?", c);
			c = ',';
		}
		if (i & 0x02) {
			printf("%c?", c);
			c = ',';
		}
		if (i & 0x01) {
			printf("%c?", c);
			c = ',';
		}
		if (c == ',')
			printf(">");
		printf("\n");
		cp += 24;
		}
E 4
I 4
		(void)printf("\trotational synch %s, offset %d/256%s\n",
		    s, rd->rd_roff, len > 18 ? "," : ".");
		if (len > 18)
			(void)printf("\trotation %d rpm.\n",
			    N2(rd->rd_rpmh, rd->rd_rpml));
E 4
		break;
I 4
#undef rd
E 4

D 4
	case 4:
		printf("Disk Geometry parameters.\n");
		printf("\t%d cylinders, %d heads.\n",
			(cp[2] << 16) | (cp[3] << 8) | cp[4], cp[5]);
		cp += cp[1] + 2;
E 4
I 4
	case SCSI_MS_PC_VERRREC:
#define	v ((struct scsi_page_verrrec *)(mp + 1))
		(void)printf("Verify Error Recovery parameters.\n");
		(void)printf("\tflags = 0x%x", v->v_flags);
		prflags(v->v_flags, "\4EER\3PER\2DTE\1DCR");
		(void)printf(",\n\t%d verify retries, %d %s span bits,\n\t",
		    v->v_verify_retry, v->v_corr_span, "correction");
		(void)printf("%d recovery time limit.\n",
		    N2(v->v_rtlh, v->v_rtll));
E 4
		break;
I 4
#undef v
E 4

I 4
	case SCSI_MS_PC_CACHE:
#define cache ((struct scsi_page_cache *)(mp + 1))
		(void)printf("Caching Page.\n");
		(void)printf("\tflags = 0x%x", cache->cache_flags);
		prflags(cache->cache_flags, "\3WCE\2MF\1RCD");
		(void)printf(
		    ",\n\tread retention = %s, write retention = %s,\n",
		    cache_policy(SCSI_CACHE_RDPOLICY(cache->cache_reten)),
		    cache_policy(SCSI_CACHE_WRPOLICY(cache->cache_reten)));
		(void)printf("\tdisable prefetch transfer length = %d,\n",
		    N2(cache->cache_dptlh, cache->cache_dptll));
		(void)printf("\tmin prefetch = %d, max prefetch = %d, ",
		    N2(cache->cache_minpfh, cache->cache_minpfl),
		    N2(cache->cache_maxpfh, cache->cache_maxpfl));
		(void)printf("max prefetch ceiling = %d.\n",
		    N2(cache->cache_mpch, cache->cache_mpcl));
		break;
#undef cache

	case SCSI_MS_PC_CTLMODE:
#define	cm ((struct scsi_page_ctlmode *)(mp + 1))
		(void)printf("Control Mode Page.\n");
		(void)printf("\t%s report log-activity error conditions,\n",
		    cm->cm_rlec & SCSI_CM_RLEC ? "do" : "do not");
		(void)printf("\tqueue algorithm modifier = %d, flags = 0x%x",
		    SCSI_CM_QMOD(cm->cm_qctl),
		    cm->cm_qctl & (SCSI_CM_QERR|SCSI_CM_DQUE));
		prflags(cm->cm_qctl, "\2QERR\1DQUE");
		(void)printf(",\n\tECA/AEN flags = 0x%x", cm->cm_ecaaen);
		prflags(cm->cm_ecaaen, "\10ECA\3RAENP\2UUAENP\1EAENP");
		(void)printf(", AEN holdoff period = %d ms.\n",
		    N2(cm->cm_aenholdh, cm->cm_aenholdl));
		break;
#undef cm

	/*
	 * Vendor Unique, but what the heck.
	 */
	case SCSI_MS_PC_CDCCACHECTL:
#define	ccm ((struct scsi_page_CDCcachectlmode *)(mp + 1))
		(void)printf("CDC-specific Cache Control Mode Page.\n");
		(void)printf("\tflags = 0x%x", ccm->ccm_flags);
		prflags(ccm->ccm_flags, "\7WIE\5ENABLE");
		(void)printf(", table size = %d, prefetch threshold = %d\n",
		    SCSI_CDC_CCM_TBLSZ(ccm->ccm_flags),
		    ccm->ccm_pfthresh);
		(void)printf("\tmaximum %s = %d, maximum %s = %d,\n",
		    "threshold", ccm->ccm_maxthresh,
		    "prefetch multiplier", ccm->ccm_maxpfmult);
		(void)printf("\tminimum %s = %d, minimum %s = %d.\n",
		    "threshold", ccm->ccm_minthresh,
		    "prefetch multiplier", ccm->ccm_minpfmult);
		break;
#undef ccm

E 4
	default:
D 4
		printf("Unknown page type.");
		for (cp += 2, i = 0; i < n; ++i) {
E 4
I 4
		(void)printf("Unknown page type.");
		for (tp = cp + sizeof(*mp), i = 0; i < len; ++i) {
E 4
			if ((i & 7) == 0)
D 4
				printf("\n\t%2d ", i);
			printf(" %02x", *cp++);
E 4
I 4
				(void)printf("\n\t%2d: ", i);
			(void)printf(" %02x", *tp++);
E 4
		}
D 4
		printf("\n");
E 4
I 4
		(void)printf(".\n");
E 4
		break;
	}
D 4
	return (cp);
E 4
I 4
	return (cp + sizeof(*mp) + len);
E 4
}

void
I 3
pr_sense(fd)
	int fd;
{
	static struct scsi_fmt_sense s;
I 4
	register struct scsi_sense *sn;
E 4

	if (ioctl(fd, SDIOCSENSE, &s) < 0)
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSENSE: %s\n", strerror(errno));

	(void)printf("scsi status 0x%x", s.status);
	if (s.status & STS_CHECKCOND) {
D 4
		struct scsi_xsense *sp = (struct scsi_xsense *)s.sense;
E 4
I 4
		sn = (struct scsi_sense *)s.sense;
E 4

D 4
		(void)printf(" sense class %d, code %d", sp->class, sp->code);
		if (sp->class == 7) {
			(void)printf(", key %d", sp->key);
			if (sp->valid)
				(void)printf(", blk %d", *(int *)&sp->info1);
E 4
I 4
		(void)printf(" sense class %d, code %d",
		    SENSE_ECLASS(sn), SENSE_ECODE(sn));
		if (SENSE_ISXSENSE(sn)) {
			(void)printf(", key %d", XSENSE_KEY(sn));
			if (XSENSE_IVALID(sn))
				(void)printf(", blk %d", XSENSE_INFO(sn));
E 4
		}
	}
	(void)printf("\n");
}

void
do_format()
{
D 4
	static int on = 1;
	static int off = 0;
	static u_char fmtbuf[128];
	struct scsi_modesel_hdr *ms = (struct scsi_modesel_hdr *)mselbuf;
E 4
I 4
	struct {
		struct scsi_ms6 ms;		/* mode select header */
		struct scsi_ms_bd bd;		/* block descriptor */
		struct scsi_ms_page_hdr mp;	/* ctl mode page hdr */
		struct scsi_page_ctlmode cm;	/* ctl mode page */
		u_char pad[4];			/* ??? */
	} msel;
	u_char fmtbuf[128];
	static struct scsi_cdb modeselect = {
		CMD_MODE_SELECT6,
		SCSI_MSEL_SCSI2_DATA | SCSI_MSEL_SAVEPAGES, 0, 0,
		sizeof(msel), 0
	};
	static struct scsi_cdb format = { CMD_FORMAT_UNIT };
E 4

D 4
	ms->block_desc_len = 8;
	ms->block_length = 512;
	mselbuf[12] = 32;
	mselbuf[13] = 10;
	mselbuf[14] = 1;
E 4
I 4
	/* want mostly 0s; set them all zero here */
	bzero(&msel, sizeof(msel));
E 4

D 4
	if (ioctl(fd, SDIOCSFORMAT, &on) < 0) {
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSFORMAT (on): %s\n", strerror(errno));
		return;
	}
	if (ioctl(fd, SDIOCSCSICOMMAND, &modeselect) < 0)
		(void)fprintf(stderr,
		    "scsiformat: modeselect cmd: %s\n", strerror(errno));
	else if (write(fd, mselbuf, sizeof(mselbuf)) < 0) {
		(void)fprintf(stderr,
		    "scsiformat: modeselect write: %s\n", strerror(errno));
		pr_sense(fd);
	} else if (ioctl(fd, SDIOCSCSICOMMAND, &format) < 0)
		(void)fprintf(stderr,
		    "scsiformat: format cmd: %s\n", strerror(errno));
	else if (write(fd, fmtbuf, sizeof(fmtbuf)) < 0) {
		(void)fprintf(stderr,
		    "scsiformat: format write: %s\n", strerror(errno));
		pr_sense(fd);
	}
	if (ioctl(fd, SDIOCSFORMAT, &off) < 0)
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSFORMAT (off): %s\n", strerror(errno));
E 4
I 4
	/* one block descriptor */
	msel.ms.ms_bdl = sizeof(struct scsi_ms_bd);

	/* block length = 512 bytes */
	msel.bd.bd_blm = 512 / 256;
	msel.bd.bd_bll = 512 % 256;

	/*
	 * In the following, the mystery pad region is copied from
	 * the original driver.  I have no idea what it is for.
	 * (Anyone got SCSI-2 documents?)
	 */

	/* mode page parameters: report log-activity exception conditions */
	msel.mp.mp_psc = SCSI_MS_PC_CTLMODE;
	msel.mp.mp_len = sizeof(msel.cm) + sizeof(msel.pad);
	msel.cm.cm_rlec = SCSI_CM_RLEC;

	do_command(fd, &modeselect, &msel, sizeof(msel));

	bzero(fmtbuf, sizeof(fmtbuf));
	do_command(fd, &format, fmtbuf, sizeof(fmtbuf));
E 4
}

void
E 3
D 2
print_mode_sense()
E 2
I 2
do_command(fd, cdb, buf, len)
	int fd;
D 4
	struct scsi_fmt_cdb *cdb;
	u_char *buf;
E 4
I 4
	struct scsi_cdb *cdb;
	void *buf;
E 4
	int len;
E 2
{
D 2
	u_char *cp;
	u_char *ep;
E 2
I 2
D 4
	static int on = 1;
	static int off = 0;
E 4
I 4
	static int on = 1, off = 0;
	int user, ret;
E 4
E 2

I 4
	bzero(buf, len);
E 4
D 2
	do_command(fd, &modesense, (u_char *)&msbuf, sizeof(msbuf));
E 2
I 2
	if (ioctl(fd, SDIOCSFORMAT, &on) < 0) {
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSFORMAT (on): %s\n", strerror(errno));
I 4
		if (ioctl(fd, SDIOCGFORMAT, &user) == 0 && user != 0)
			(void)fprintf(stderr, "scsiformat: pid %d has it\n",
			    user);
E 4
		return;
	}
D 4
	if (ioctl(fd, SDIOCSCSICOMMAND, cdb) < 0)
E 4
I 4
	ret = ioctl(fd, SDIOCSCSICOMMAND, cdb);
#ifdef COMPAT_HPSCSI
	if (ret < 0) {
		static const char scsicmdlen[8] = { 6, 10, 0, 0, 0, 12, 0, 0 };
#define	SCSICMDLEN(cmd)	scsicmdlen[(cmd) >> 5]
		struct scsi_fmt_cdb {
			int	len;
			u_char	cdb[28];
		} sc;
#define OSDIOCSCSICOMMAND _IOW('S', 0x3, struct scsi_fmt_cdb)

		sc.len = SCSICMDLEN(cdb->cdb_bytes[0]);
		bcopy(cdb->cdb_bytes, sc.cdb, sc.len);
		ret = ioctl(fd, OSDIOCSCSICOMMAND, &sc);
	}
#endif
	if (ret < 0)
E 4
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSCSICOMMAND: %s\n", strerror(errno));
D 3
	else if (read(fd, buf, len) < 0)
E 3
I 3
	else if (read(fd, buf, len) < 0) {
E 3
		(void)fprintf(stderr,
		    "scsiformat: read: %s\n", strerror(errno));
I 3
		pr_sense(fd);
	}
E 3
E 2

D 2
	printf("\n%d bytes of mode sense data.  ", msbuf.h.len);
	printf("media type %d, %swrite protected\n", msbuf.h.media_type,
		msbuf.h.wp? "" : "not ");
	if (msbuf.h.block_desc_len) {
		printf("density 0x%x, ", msbuf.h.density);
		if (msbuf.h.number_blocks)
			printf("%d blocks of length %d\n",
				msbuf.h.number_blocks, msbuf.h.block_length);
		else
			printf("all blocks of length %d\n",
				msbuf.h.block_length);
		cp = msbuf.p;
	} else
		cp = &msbuf.h.block_desc_len + 1;

	ep = (u_char *)&msbuf + msbuf.h.len;
	while (cp < ep)
		cp = print_mode_page(cp);
E 2
I 2
	if (ioctl(fd, SDIOCSFORMAT, &off) < 0)
		(void)fprintf(stderr,
		    "scsiformat: SDIOCSFORMAT (off): %s\n", strerror(errno));
E 2
}

void
usage()
{
D 4
	(void)fprintf(stderr, "usage: scsiformat device\n");
E 4
I 4
	(void)fprintf(stderr, "usage: scsiformat [-r] [-p c|d|s|v] device\n");
E 4
	exit(1);
}
E 1
