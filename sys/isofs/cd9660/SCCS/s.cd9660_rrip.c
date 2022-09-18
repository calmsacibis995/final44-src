h13458
s 00015/00013/00649
d D 8.6 94/12/05 21:55:27 mckusick 6 5
c update from mycroft
e
s 00001/00001/00661
d D 8.5 94/08/17 17:06:22 mckusick 5 4
c actually it wasn't a buglet afterall
e
s 00019/00016/00643
d D 8.4 94/06/14 11:57:04 mkm 4 3
c formatting; symlink fixes (from Wolfgang Solfrank via mycroft)
e
s 00001/00001/00658
d D 8.3 94/06/01 17:42:14 mckusick 3 2
c buglet
e
s 00055/00055/00604
d D 8.2 94/01/23 23:50:48 mckusick 2 1
c isofs => cd9660 naming convention
e
s 00659/00000/00000
d D 8.1 94/01/21 18:28:58 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
I 6
#include <sys/systm.h>
E 6
#include <sys/namei.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/kernel.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/time.h>

#include <isofs/cd9660/iso.h>
D 2
#include <isofs/cd9660/isofs_node.h>
#include <isofs/cd9660/isofs_rrip.h>
E 2
I 2
#include <isofs/cd9660/cd9660_node.h>
#include <isofs/cd9660/cd9660_rrip.h>
E 2
#include <isofs/cd9660/iso_rrip.h>

/*
 * POSIX file attribute
 */
static int
D 2
isofs_rrip_attr(p,ana)
E 2
I 2
cd9660_rrip_attr(p,ana)
E 2
	ISO_RRIP_ATTR *p;
	ISO_RRIP_ANALYZE *ana;
{
D 6
	ana->inop->inode.iso_mode = isonum_731(p->mode_l);
	ana->inop->inode.iso_uid = (uid_t)isonum_731(p->uid_l);
	ana->inop->inode.iso_gid = (gid_t)isonum_731(p->gid_l);
	ana->inop->inode.iso_links = isonum_731(p->links_l);
E 6
I 6
	ana->inop->inode.iso_mode = isonum_733(p->mode);
	ana->inop->inode.iso_uid = isonum_733(p->uid);
	ana->inop->inode.iso_gid = isonum_733(p->gid);
	ana->inop->inode.iso_links = isonum_733(p->links);
E 6
	ana->fields &= ~ISO_SUSP_ATTR;
	return ISO_SUSP_ATTR;
}

static void
D 2
isofs_rrip_defattr(isodir,ana)
E 2
I 2
cd9660_rrip_defattr(isodir,ana)
E 2
	struct iso_directory_record *isodir;
	ISO_RRIP_ANALYZE *ana;
{
	/* But this is a required field! */
	printf("RRIP without PX field?\n");
D 2
	isofs_defattr(isodir,ana->inop,NULL);
E 2
I 2
	cd9660_defattr(isodir,ana->inop,NULL);
E 2
}

/*
 * Symbolic Links
 */
static int
D 2
isofs_rrip_slink(p,ana)
E 2
I 2
cd9660_rrip_slink(p,ana)
E 2
	ISO_RRIP_SLINK  *p;
	ISO_RRIP_ANALYZE *ana;
{
	register ISO_RRIP_SLINK_COMPONENT *pcomp;
	register ISO_RRIP_SLINK_COMPONENT *pcompe;
	int len, wlen, cont;
	char *outbuf, *inbuf;
	
	pcomp = (ISO_RRIP_SLINK_COMPONENT *)p->component;
	pcompe = (ISO_RRIP_SLINK_COMPONENT *)((char *)p + isonum_711(p->h.length));
	len = *ana->outlen;
	outbuf = ana->outbuf;
	cont = ana->cont;
	
	/*
	 * Gathering a Symbolic name from each component with path
	 */
	for (;
	     pcomp < pcompe;
	     pcomp = (ISO_RRIP_SLINK_COMPONENT *)((char *)pcomp + ISO_RRIP_SLSIZ
						  + isonum_711(pcomp->clen))) {
		
		if (!cont) {
			if (len < ana->maxlen) {
				len++;
				*outbuf++ = '/';
			}
		}
		cont = 0;
		
		inbuf = "..";
		wlen = 0;
		
		switch (*pcomp->cflag) {
			
		case ISO_SUSP_CFLAG_CURRENT:
			/* Inserting Current */
			wlen = 1;
			break;
			
		case ISO_SUSP_CFLAG_PARENT:
			/* Inserting Parent */
			wlen = 2;
			break;
			
		case ISO_SUSP_CFLAG_ROOT:
			/* Inserting slash for ROOT */
			/* start over from beginning(?) */
			outbuf -= len;
			len = 0;
			break;
			
		case ISO_SUSP_CFLAG_VOLROOT:
			/* Inserting a mount point i.e. "/cdrom" */
			/* same as above */
			outbuf -= len;
			len = 0;
			inbuf = ana->imp->im_mountp->mnt_stat.f_mntonname;
			wlen = strlen(inbuf);
			break;
			
		case ISO_SUSP_CFLAG_HOST:
			/* Inserting hostname i.e. "kurt.tools.de" */
			inbuf = hostname;
			wlen = hostnamelen;
			break;
			
		case ISO_SUSP_CFLAG_CONTINUE:
			cont = 1;
			/* fall thru */
		case 0:
			/* Inserting component */
			wlen = isonum_711(pcomp->clen);
			inbuf = pcomp->name;
			break;
		default:
			printf("RRIP with incorrect flags?");
			wlen = ana->maxlen + 1;
			break;
		}
		
		if (len + wlen > ana->maxlen) {
			/* indicate error to caller */
			ana->cont = 1;
			ana->fields = 0;
			ana->outbuf -= *ana->outlen;
			*ana->outlen = 0;
			return 0;
		}
		
		bcopy(inbuf,outbuf,wlen);
		outbuf += wlen;
		len += wlen;
		
	}
	ana->outbuf = outbuf;
	*ana->outlen = len;
	ana->cont = cont;
	
	if (!isonum_711(p->flags)) {
		ana->fields &= ~ISO_SUSP_SLINK;
		return ISO_SUSP_SLINK;
	}
	return 0;
}

/*
 * Alternate name
 */
static int
D 2
isofs_rrip_altname(p,ana)
E 2
I 2
cd9660_rrip_altname(p,ana)
E 2
	ISO_RRIP_ALTNAME *p;
	ISO_RRIP_ANALYZE *ana;
{
	char *inbuf;
	int wlen;
	int cont;
	
	inbuf = "..";
	wlen = 0;
	cont = 0;
	
	switch (*p->flags) {
	case ISO_SUSP_CFLAG_CURRENT:
		/* Inserting Current */
		wlen = 1;
		break;
		
	case ISO_SUSP_CFLAG_PARENT:
		/* Inserting Parent */
		wlen = 2;
		break;
		
	case ISO_SUSP_CFLAG_HOST:
		/* Inserting hostname i.e. "kurt.tools.de" */
		inbuf = hostname;
		wlen = hostnamelen;
		break;
		
	case ISO_SUSP_CFLAG_CONTINUE:
		cont = 1;
		/* fall thru */
	case 0:
		/* Inserting component */
		wlen = isonum_711(p->h.length) - 5;
		inbuf = (char *)p + 5;
		break;
		
	default:
		printf("RRIP with incorrect NM flags?\n");
		wlen = ana->maxlen + 1;
		break;
	}
	
	if ((*ana->outlen += wlen) > ana->maxlen) {
		/* treat as no name field */
		ana->fields &= ~ISO_SUSP_ALTNAME;
		ana->outbuf -= *ana->outlen - wlen;
		*ana->outlen = 0;
		return 0;
	}
	
	bcopy(inbuf,ana->outbuf,wlen);
	ana->outbuf += wlen;
	
	if (!cont) {
		ana->fields &= ~ISO_SUSP_ALTNAME;
		return ISO_SUSP_ALTNAME;
	}
	return 0;
}

static void
D 2
isofs_rrip_defname(isodir,ana)
E 2
I 2
cd9660_rrip_defname(isodir,ana)
E 2
	struct iso_directory_record *isodir;
	ISO_RRIP_ANALYZE *ana;
{
	strcpy(ana->outbuf,"..");
	switch (*isodir->name) {
	default:
		isofntrans(isodir->name,isonum_711(isodir->name_len),
			   ana->outbuf,ana->outlen,
			   1,isonum_711(isodir->flags)&4);
		break;
	case 0:
		*ana->outlen = 1;
		break;
	case 1:
		*ana->outlen = 2;
		break;
	}
}

/*
 * Parent or Child Link
 */
static int
D 2
isofs_rrip_pclink(p,ana)
E 2
I 2
cd9660_rrip_pclink(p,ana)
E 2
	ISO_RRIP_CLINK  *p;
	ISO_RRIP_ANALYZE *ana;
{
	*ana->inump = isonum_733(p->dir_loc) << ana->imp->im_bshift;
	ana->fields &= ~(ISO_SUSP_CLINK|ISO_SUSP_PLINK);
	return *p->h.type == 'C' ? ISO_SUSP_CLINK : ISO_SUSP_PLINK;
}

/*
 * Relocated directory
 */
static int
D 2
isofs_rrip_reldir(p,ana)
E 2
I 2
cd9660_rrip_reldir(p,ana)
E 2
	ISO_RRIP_RELDIR  *p;
	ISO_RRIP_ANALYZE *ana;
{
	/* special hack to make caller aware of RE field */
	*ana->outlen = 0;
	ana->fields = 0;
	return ISO_SUSP_RELDIR|ISO_SUSP_ALTNAME|ISO_SUSP_CLINK|ISO_SUSP_PLINK;
}

static int
D 2
isofs_rrip_tstamp(p,ana)
E 2
I 2
cd9660_rrip_tstamp(p,ana)
E 2
	ISO_RRIP_TSTAMP *p;
	ISO_RRIP_ANALYZE *ana;
{
D 6
	unsigned char *ptime;
E 6
I 6
	u_char *ptime;
E 6
	
	ptime = p->time;
	
	/* Check a format of time stamp (7bytes/17bytes) */
	if (!(*p->flags&ISO_SUSP_TSTAMP_FORM17)) {
		if (*p->flags&ISO_SUSP_TSTAMP_CREAT)
			ptime += 7;
		
		if (*p->flags&ISO_SUSP_TSTAMP_MODIFY) {
D 2
			isofs_tstamp_conv7(ptime,&ana->inop->inode.iso_mtime);
E 2
I 2
			cd9660_tstamp_conv7(ptime,&ana->inop->inode.iso_mtime);
E 2
			ptime += 7;
		} else
D 6
			bzero(&ana->inop->inode.iso_mtime,sizeof(struct timeval));
E 6
I 6
			bzero(&ana->inop->inode.iso_mtime,sizeof(struct timespec));
E 6
		
		if (*p->flags&ISO_SUSP_TSTAMP_ACCESS) {
D 2
			isofs_tstamp_conv7(ptime,&ana->inop->inode.iso_atime);
E 2
I 2
			cd9660_tstamp_conv7(ptime,&ana->inop->inode.iso_atime);
E 2
			ptime += 7;
		} else
			ana->inop->inode.iso_atime = ana->inop->inode.iso_mtime;
		
		if (*p->flags&ISO_SUSP_TSTAMP_ATTR)
D 2
			isofs_tstamp_conv7(ptime,&ana->inop->inode.iso_ctime);
E 2
I 2
			cd9660_tstamp_conv7(ptime,&ana->inop->inode.iso_ctime);
E 2
		else
			ana->inop->inode.iso_ctime = ana->inop->inode.iso_mtime;
		
	} else {
		if (*p->flags&ISO_SUSP_TSTAMP_CREAT)
			ptime += 17;
		
		if (*p->flags&ISO_SUSP_TSTAMP_MODIFY) {
D 2
			isofs_tstamp_conv17(ptime,&ana->inop->inode.iso_mtime);
E 2
I 2
			cd9660_tstamp_conv17(ptime,&ana->inop->inode.iso_mtime);
E 2
			ptime += 17;
		} else
D 6
			bzero(&ana->inop->inode.iso_mtime,sizeof(struct timeval));
E 6
I 6
			bzero(&ana->inop->inode.iso_mtime,sizeof(struct timespec));
E 6
		
		if (*p->flags&ISO_SUSP_TSTAMP_ACCESS) {
D 2
			isofs_tstamp_conv17(ptime,&ana->inop->inode.iso_atime);
E 2
I 2
			cd9660_tstamp_conv17(ptime,&ana->inop->inode.iso_atime);
E 2
			ptime += 17;
		} else
			ana->inop->inode.iso_atime = ana->inop->inode.iso_mtime;
		
		if (*p->flags&ISO_SUSP_TSTAMP_ATTR)
D 2
			isofs_tstamp_conv17(ptime,&ana->inop->inode.iso_ctime);
E 2
I 2
			cd9660_tstamp_conv17(ptime,&ana->inop->inode.iso_ctime);
E 2
		else
			ana->inop->inode.iso_ctime = ana->inop->inode.iso_mtime;
		
	}
	ana->fields &= ~ISO_SUSP_TSTAMP;
	return ISO_SUSP_TSTAMP;
}

static void
D 2
isofs_rrip_deftstamp(isodir,ana)
E 2
I 2
cd9660_rrip_deftstamp(isodir,ana)
E 2
	struct iso_directory_record  *isodir;
	ISO_RRIP_ANALYZE *ana;
{
D 2
	isofs_deftstamp(isodir,ana->inop,NULL);
E 2
I 2
	cd9660_deftstamp(isodir,ana->inop,NULL);
E 2
}

/*
 * POSIX device modes
 */
static int
D 2
isofs_rrip_device(p,ana)
E 2
I 2
cd9660_rrip_device(p,ana)
E 2
	ISO_RRIP_DEVICE *p;
	ISO_RRIP_ANALYZE *ana;
{
D 6
	unsigned high, low;
E 6
I 6
	u_int high, low;
E 6
	
D 6
	high = isonum_733(p->dev_t_high_l);
	low  = isonum_733(p->dev_t_low_l);
E 6
I 6
	high = isonum_733(p->dev_t_high);
	low  = isonum_733(p->dev_t_low);
E 6
	
D 4
	if ( high == 0 ) {
		ana->inop->inode.iso_rdev = makedev( major(low), minor(low) );
	} else {
		ana->inop->inode.iso_rdev = makedev( high, minor(low) );
	}
E 4
I 4
	if (high == 0)
		ana->inop->inode.iso_rdev = makedev(major(low), minor(low));
	else
		ana->inop->inode.iso_rdev = makedev(high, minor(low));
E 4
	ana->fields &= ~ISO_SUSP_DEVICE;
	return ISO_SUSP_DEVICE;
}

/*
 * Flag indicating
 */
static int
D 2
isofs_rrip_idflag(p,ana)
E 2
I 2
cd9660_rrip_idflag(p,ana)
E 2
	ISO_RRIP_IDFLAG *p;
	ISO_RRIP_ANALYZE *ana;
{
	ana->fields &= isonum_711(p->flags)|~0xff; /* don't touch high bits */
	/* special handling of RE field */
	if (ana->fields&ISO_SUSP_RELDIR)
D 2
		return isofs_rrip_reldir(p,ana);
E 2
I 2
		return cd9660_rrip_reldir(p,ana);
E 2
	
	return ISO_SUSP_IDFLAG;
}

/*
 * Continuation pointer
 */
static int
D 2
isofs_rrip_cont(p,ana)
E 2
I 2
cd9660_rrip_cont(p,ana)
E 2
	ISO_RRIP_CONT *p;
	ISO_RRIP_ANALYZE *ana;
{
	ana->iso_ce_blk = isonum_733(p->location);
	ana->iso_ce_off = isonum_733(p->offset);
	ana->iso_ce_len = isonum_733(p->length);
	return ISO_SUSP_CONT;
}

/*
 * System Use end
 */
static int
D 2
isofs_rrip_stop(p,ana)
E 2
I 2
cd9660_rrip_stop(p,ana)
E 2
	ISO_SUSP_HEADER *p;
	ISO_RRIP_ANALYZE *ana;
{
D 4
	/* stop analyzing */
	ana->fields = 0;
E 4
	return ISO_SUSP_STOP;
}

/*
 * Extension reference
 */
static int
D 2
isofs_rrip_extref(p,ana)
E 2
I 2
cd9660_rrip_extref(p,ana)
E 2
	ISO_RRIP_EXTREF *p;
	ISO_RRIP_ANALYZE *ana;
{
	if (isonum_711(p->len_id) != 10
	    || bcmp((char *)p + 8,"RRIP_1991A",10)
	    || isonum_711(p->version) != 1)
		return 0;
	ana->fields &= ~ISO_SUSP_EXTREF;
	return ISO_SUSP_EXTREF;
}

typedef struct {
	char type[2];
	int (*func)();
	void (*func2)();
	int result;
} RRIP_TABLE;

static int
D 2
isofs_rrip_loop(isodir,ana,table)
E 2
I 2
cd9660_rrip_loop(isodir,ana,table)
E 2
	struct iso_directory_record *isodir;
	ISO_RRIP_ANALYZE *ana;
	RRIP_TABLE *table;
{
	register RRIP_TABLE *ptable;
	register ISO_SUSP_HEADER *phead;
	register ISO_SUSP_HEADER *pend;
	struct buf *bp = NULL;
	int i;
	char *pwhead;
	int result;
	
	/*
	 * Note: If name length is odd,
	 *       it will be padding 1 byte  after the name
	 */
	pwhead = isodir->name + isonum_711(isodir->name_len);
	if (!(isonum_711(isodir->name_len)&1))
		pwhead++;
	
	/* If it's not the '.' entry of the root dir obey SP field */
	if (*isodir->name != 0
	    || isonum_733(isodir->extent) != ana->imp->root_extent)
		pwhead += ana->imp->rr_skip;
	else
		pwhead += ana->imp->rr_skip0;
	
	phead = (ISO_SUSP_HEADER *)pwhead;
	pend = (ISO_SUSP_HEADER *)((char *)isodir + isonum_711(isodir->length));
	
	result = 0;
	while (1) {
		ana->iso_ce_len = 0;
		/*
		 * Note: "pend" should be more than one SUSP header
		 */ 
		while (pend >= phead + 1) {
			if (isonum_711(phead->version) == 1) {
				for (ptable = table; ptable->func; ptable++) {
					if (*phead->type == *ptable->type
					    && phead->type[1] == ptable->type[1]) {
						result |= ptable->func(phead,ana);
						break;
					}
				}
				if (!ana->fields)
					break;
			}
I 4
			if (result&ISO_SUSP_STOP) {
				result &= ~ISO_SUSP_STOP;
				break;
			}
			/* plausibility check */
			if (isonum_711(phead->length) < sizeof(*phead))
				break;
E 4
			/*
			 * move to next SUSP
			 * Hopefully this works with newer versions, too
			 */
			phead = (ISO_SUSP_HEADER *)((char *)phead + isonum_711(phead->length));
		}
		
D 4
		if ( ana->fields && ana->iso_ce_len ) {
E 4
I 4
		if (ana->fields && ana->iso_ce_len) {
E 4
			if (ana->iso_ce_blk >= ana->imp->volume_space_size
			    || ana->iso_ce_off + ana->iso_ce_len > ana->imp->logical_block_size
			    || bread(ana->imp->im_devvp,
D 6
				     ana->iso_ce_blk * ana->imp->logical_block_size / DEV_BSIZE,
				     ana->imp->logical_block_size,NOCRED,&bp))
E 6
I 6
				     ana->iso_ce_blk <<
				     (ana->imp->im_bshift - DEV_BSHIFT),
				     ana->imp->logical_block_size, NOCRED, &bp))
E 6
				/* what to do now? */
				break;
D 6
			phead = (ISO_SUSP_HEADER *)(bp->b_un.b_addr + ana->iso_ce_off);
E 6
I 6
			phead = (ISO_SUSP_HEADER *)(bp->b_data + ana->iso_ce_off);
E 6
			pend = (ISO_SUSP_HEADER *) ((char *)phead + ana->iso_ce_len);
		} else
			break;
	}
	if (bp)
		brelse(bp);
	/*
	 * If we don't find the Basic SUSP stuffs, just set default value
D 4
	 *   ( attribute/time stamp )
E 4
I 4
	 *   (attribute/time stamp)
E 4
	 */
	for (ptable = table; ptable->func2; ptable++)
		if (!(ptable->result&result))
			ptable->func2(isodir,ana);
	
	return result;
}

I 4
/*
 * Get Attributes.
 */
E 4
static RRIP_TABLE rrip_table_analyze[] = {
D 2
	{ "PX", isofs_rrip_attr,	isofs_rrip_defattr,	ISO_SUSP_ATTR },
	{ "TF", isofs_rrip_tstamp,	isofs_rrip_deftstamp,	ISO_SUSP_TSTAMP },
	{ "PN", isofs_rrip_device,	0,			ISO_SUSP_DEVICE },
	{ "RR", isofs_rrip_idflag,	0,			ISO_SUSP_IDFLAG },
	{ "CE", isofs_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", isofs_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
I 2
	{ "PX", cd9660_rrip_attr,	cd9660_rrip_defattr,	ISO_SUSP_ATTR },
	{ "TF", cd9660_rrip_tstamp,	cd9660_rrip_deftstamp,	ISO_SUSP_TSTAMP },
	{ "PN", cd9660_rrip_device,	0,			ISO_SUSP_DEVICE },
	{ "RR", cd9660_rrip_idflag,	0,			ISO_SUSP_IDFLAG },
	{ "CE", cd9660_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", cd9660_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
	{ "",	0,			0,			0 }
};

int
D 2
isofs_rrip_analyze(isodir,inop,imp)
E 2
I 2
cd9660_rrip_analyze(isodir,inop,imp)
E 2
	struct iso_directory_record *isodir;
	struct iso_node *inop;
	struct iso_mnt *imp;
{
	ISO_RRIP_ANALYZE analyze;
	
	analyze.inop = inop;
	analyze.imp = imp;
	analyze.fields = ISO_SUSP_ATTR|ISO_SUSP_TSTAMP|ISO_SUSP_DEVICE;
	
D 2
	return isofs_rrip_loop(isodir,&analyze,rrip_table_analyze);
E 2
I 2
	return cd9660_rrip_loop(isodir,&analyze,rrip_table_analyze);
E 2
}

/* 
D 4
 * Get Alternate Name from 'AL' record 
 * If either no AL record or 0 length, 
 *    it will be return the translated ISO9660 name,
E 4
I 4
 * Get Alternate Name.
E 4
 */
static RRIP_TABLE rrip_table_getname[] = {
D 2
	{ "NM", isofs_rrip_altname,	isofs_rrip_defname,	ISO_SUSP_ALTNAME },
	{ "CL", isofs_rrip_pclink,	0,			ISO_SUSP_CLINK|ISO_SUSP_PLINK },
	{ "PL", isofs_rrip_pclink,	0,			ISO_SUSP_CLINK|ISO_SUSP_PLINK },
	{ "RE", isofs_rrip_reldir,	0,			ISO_SUSP_RELDIR },
	{ "RR", isofs_rrip_idflag,	0,			ISO_SUSP_IDFLAG },
	{ "CE", isofs_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", isofs_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
I 2
	{ "NM", cd9660_rrip_altname,	cd9660_rrip_defname,	ISO_SUSP_ALTNAME },
	{ "CL", cd9660_rrip_pclink,	0,			ISO_SUSP_CLINK|ISO_SUSP_PLINK },
	{ "PL", cd9660_rrip_pclink,	0,			ISO_SUSP_CLINK|ISO_SUSP_PLINK },
	{ "RE", cd9660_rrip_reldir,	0,			ISO_SUSP_RELDIR },
	{ "RR", cd9660_rrip_idflag,	0,			ISO_SUSP_IDFLAG },
	{ "CE", cd9660_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", cd9660_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
	{ "",	0,			0,			0 }
};

int
D 2
isofs_rrip_getname(isodir,outbuf,outlen,inump,imp)
E 2
I 2
cd9660_rrip_getname(isodir,outbuf,outlen,inump,imp)
E 2
	struct iso_directory_record *isodir;
	char *outbuf;
	u_short *outlen;
	ino_t *inump;
	struct iso_mnt *imp;
{
	ISO_RRIP_ANALYZE analyze;
	RRIP_TABLE *tab;
	
	analyze.outbuf = outbuf;
	analyze.outlen = outlen;
	analyze.maxlen = NAME_MAX;
	analyze.inump = inump;
	analyze.imp = imp;
	analyze.fields = ISO_SUSP_ALTNAME|ISO_SUSP_RELDIR|ISO_SUSP_CLINK|ISO_SUSP_PLINK;
	*outlen = 0;
	
	tab = rrip_table_getname;
	if (*isodir->name == 0
	    || *isodir->name == 1) {
D 2
		isofs_rrip_defname(isodir,&analyze);
E 2
I 2
		cd9660_rrip_defname(isodir,&analyze);
E 2
		
		analyze.fields &= ~ISO_SUSP_ALTNAME;
		tab++;
	}
	
D 2
	return isofs_rrip_loop(isodir,&analyze,tab);
E 2
I 2
	return cd9660_rrip_loop(isodir,&analyze,tab);
E 2
}

/* 
D 4
 * Get Symbolic Name from 'SL' record 
 *
 * Note: isodir should contains SL record!
E 4
I 4
 * Get Symbolic Link.
E 4
 */
static RRIP_TABLE rrip_table_getsymname[] = {
D 2
	{ "SL", isofs_rrip_slink,	0,			ISO_SUSP_SLINK },
	{ "RR", isofs_rrip_idflag,	0,			ISO_SUSP_IDFLAG },
	{ "CE", isofs_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", isofs_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
I 2
	{ "SL", cd9660_rrip_slink,	0,			ISO_SUSP_SLINK },
	{ "RR", cd9660_rrip_idflag,	0,			ISO_SUSP_IDFLAG },
	{ "CE", cd9660_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", cd9660_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
	{ "",	0,			0,			0 }
};

int
D 2
isofs_rrip_getsymname(isodir,outbuf,outlen,imp)
E 2
I 2
cd9660_rrip_getsymname(isodir,outbuf,outlen,imp)
E 2
	struct iso_directory_record *isodir;
	char *outbuf;
	u_short *outlen;
	struct iso_mnt *imp;
{
	ISO_RRIP_ANALYZE analyze;
	
	analyze.outbuf = outbuf;
D 3
	analyze.outlen = outlen;
E 3
I 3
D 5
	analyze.outlen = 0;
E 5
I 5
	analyze.outlen = outlen;
E 5
E 3
	*outlen = 0;
	analyze.maxlen = MAXPATHLEN;
	analyze.cont = 1;		/* don't start with a slash */
	analyze.imp = imp;
	analyze.fields = ISO_SUSP_SLINK;
	
D 2
	return (isofs_rrip_loop(isodir,&analyze,rrip_table_getsymname)&ISO_SUSP_SLINK);
E 2
I 2
	return (cd9660_rrip_loop(isodir,&analyze,rrip_table_getsymname)&ISO_SUSP_SLINK);
E 2
}

static RRIP_TABLE rrip_table_extref[] = {
D 2
	{ "ER", isofs_rrip_extref,	0,			ISO_SUSP_EXTREF },
	{ "CE", isofs_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", isofs_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
I 2
	{ "ER", cd9660_rrip_extref,	0,			ISO_SUSP_EXTREF },
	{ "CE", cd9660_rrip_cont,	0,			ISO_SUSP_CONT },
	{ "ST", cd9660_rrip_stop,	0,			ISO_SUSP_STOP },
E 2
	{ "",	0,			0,			0 }
};

/*
 * Check for Rock Ridge Extension and return offset of its fields.
D 4
 * Note: We require the ER field.
E 4
I 4
 * Note: We insist on the ER field.
E 4
 */
int
D 2
isofs_rrip_offset(isodir,imp)
E 2
I 2
cd9660_rrip_offset(isodir,imp)
E 2
	struct iso_directory_record *isodir;
	struct iso_mnt *imp;
{
	ISO_RRIP_OFFSET *p;
	ISO_RRIP_ANALYZE analyze;
	
	imp->rr_skip0 = 0;
	p = (ISO_RRIP_OFFSET *)(isodir->name + 1);
	if (bcmp(p,"SP\7\1\276\357",6)) {
		/* Maybe, it's a CDROM XA disc? */
		imp->rr_skip0 = 15;
		p = (ISO_RRIP_OFFSET *)((char *)p + 15);
		if (bcmp(p,"SP\7\1\276\357",6))
			return -1;
	}
	
	analyze.imp = imp;
	analyze.fields = ISO_SUSP_EXTREF;
D 2
	if (!(isofs_rrip_loop(isodir,&analyze,rrip_table_extref)&ISO_SUSP_EXTREF))
E 2
I 2
	if (!(cd9660_rrip_loop(isodir,&analyze,rrip_table_extref)&ISO_SUSP_EXTREF))
E 2
		return -1;
	
	return isonum_711(p->skip);
}
E 1
