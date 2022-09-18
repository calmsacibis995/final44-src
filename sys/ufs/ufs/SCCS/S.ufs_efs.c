h59734
s 00004/00003/00874
d D 4.3 82/10/31 14:01:00 root 3 2
c fix headers (still grossly wrong, though!)
e
s 00008/00022/00869
d D 4.2 82/08/01 19:22:04 sam 2 1
c new ioctl's
e
s 00891/00000/00000
d D 4.1 82/07/25 16:19:28 sam 1 0
c date and time created 82/07/25 16:19:28 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

#include "efs.h"
#if NEFS > 0

#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/file.h"
#include "../h/inode.h"
#include "../h/buf.h"
#include "../h/mbuf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/stat.h"
#include "../h/ioctl.h"
D 3
#include "../net/in.h"
#include "../net/in_systm.h"
#include "../net/route.h"
E 3
#include "../h/efs.h"
I 3

#include "../net/route.h"
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 3

int efs_major = -1;
int efs_init;

#define DEFINE_U unsigned int Save_Count; off_t Save_Offset; \
		 caddr_t Save_Base; char Save_Segflg;

#define SAVE_U() {Save_Count = u.u_count; Save_Base = u.u_base; \
		  Save_Offset = u.u_offset; Save_Segflg = u.u_segflg;}

#define RESTORE_U() {u.u_count = Save_Count; u.u_base = Save_Base; \
		     u.u_offset = Save_Offset; u.u_segflg = Save_Segflg;}

#define SETUP_U(base, count, segflg) {u.u_base = ((caddr_t)(base)); \
				      u.u_count = ((unsigned int)(count)); \
				      u.u_segflg = ((char)(segflg));}

#define IN_KERNEL (1)

#define PB_GET(pbp)	{if ((pbp = efs_freepb) != NULL)  \
				efs_freepb = pbp->pb_link;}
#define PB_FREE(pbp)	{pbp->pb_link = efs_freepb; pbp->pb_fp = NULL; \
				efs_freepb = pbp;}

char *efspnamescan();
off_t efsfilesize();
struct hosttable *efshostlookup();
struct patchboard *efsfplookup();

efsopen(dev, rw, trf)
	dev_t dev;
{
	register struct patchboard *pbp;
	register struct args {
		char *a_path;
		int a_mode;
	} *uap = (struct args*) u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct socket *so;
	short int mode;
	register int i;
	int err;
	DEFINE_U;

	/* one-time initialization */
	if (!efs_init) {
		for (pbp = efs_patchboard; pbp < &efs_patchboard[EFS_NPB];pbp++)
			PB_FREE(pbp);
		efs_major = major(dev);
		efs_init++;
	}
	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->a_path, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	PB_GET(pbp);
	if (pbp == NULL) {
		u.u_error = ENOBUFS;
		return;
	}
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs open/create packet */
	cb.efs_cmd = (trf == 0) ? EFS_OPEN : EFS_CREAT;
	/*
	 *  Decrement uap->mode for open syscalls because
	 *  open() [sys2.c] increments it before calling
	 *  open1() [sys2.c].
	 */
	mode = uap->a_mode;
	if (cb.efs_cmd == EFS_OPEN)
		mode--;
	cb.efs_mode = htons(mode);
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	cb.efs_cmask = htons(u.u_cmask);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR) {
		err = cb.efs_error;
		goto out2;
	}
	RESTORE_U();
	/* Successful connection */
	pbp->pb_filesize = ntohl(cb.efs_size);
	pbp->pb_fp = getf(u.u_r.r_val1);  /* ufalloc() [fio.c] set r_val1 */
	pbp->pb_so = so;
	return;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	PB_FREE(pbp);
	u.u_error = err;
}

efsclose(dev, flag, fp, exiting)
	dev_t dev;
	struct file *fp;
{
	register struct patchboard *pbp;
	struct efs_controlblock cb;
	register int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;
	if ((pbp = efsfplookup(fp)) == NULL)
		return;
	cb.efs_cmd = EFS_CLOSE;
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
out1:
	RESTORE_U();
	soclose(pbp->pb_so, exiting);
	PB_FREE(pbp);
	u.u_error = err;
}

efsread(dev)
	dev_t dev;
{
	register struct patchboard *pbp;
	struct efs_controlblock cb;
	register int err;
	register off_t len;
	DEFINE_U;

	if (minor(dev) > 0) {
		u.u_error = EINVAL;
		return;
	}
	if ((pbp = efsfplookup(getf(*u.u_ap))) == NULL)
		return;
	cb.efs_cmd = EFS_READ;
	cb.efs_offset = htonl(u.u_offset);
	cb.efs_count = htonl(u.u_count);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	RESTORE_U();
	if (cb.efs_cmd == EFS_ERROR) {
		err = cb.efs_error;
		goto out2;
	}
	if ((len = ntohl(cb.efs_size)) > 0) {	/* what really was read */
		u.u_count = len;
		if ((err = soreceive(pbp->pb_so, (struct sockaddr *)0)) != 0)
			goto out2;
		u.u_count = Save_Count-(len-u.u_count);	/* fixup count */
	}
	return;
out1:
	RESTORE_U();
out2:
	u.u_error = err;
}

efswrite(dev)
	dev_t dev;
{
	register struct patchboard *pbp;
	struct efs_controlblock cb;
	register int err;
	DEFINE_U;

	if (minor(dev) > 0) {
		u.u_error = EINVAL;
		return;
	}
	if ((pbp = efsfplookup(getf(*u.u_ap))) == NULL)
		return;
	cb.efs_cmd = EFS_WRITE;
	cb.efs_offset = htonl(u.u_offset);
	cb.efs_count = htonl(u.u_count);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	RESTORE_U();
	if ((err = sosend(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out2;
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
	/* should the actual size written be used to update u_count,
	   u_offset, and u_base? */
out1:
	RESTORE_U();
	if (err == 0 && u.u_offset > pbp->pb_filesize)
		pbp->pb_filesize = u.u_offset;		/* update file size */
out2:
	u.u_error = err;
}

D 2
efsioctl(dev, cmd, arg, flag)
E 2
I 2
efsioctl(dev, cmd, data, flag)
E 2
	dev_t dev;
D 2
	caddr_t arg;
E 2
I 2
	caddr_t data;
E 2
{

I 2
	if (minor(dev) == 0) {
		u.u_error = EINVAL;
		return;
	}
E 2
	switch(cmd) {

	case EFSIOSHTAB:
D 2
		if (minor(dev) == 0) {
			u.u_error = EINVAL;
			return;
		}
E 2
		if (!suser()) {
			u.u_error = EACCES;
			return;
		}
D 2
		if (copyin(arg, efs_hosttable, sizeof efs_hosttable)) {
			u.u_error = EFAULT;
			return;
		}
E 2
I 2
		bcopy(data, (caddr_t)efs_hosttable, sizeof (efs_hosttable));
E 2
		break;

	case EFSIOGHTAB:
D 2
		if (minor(dev) == 0) {
			u.u_error = EINVAL;
			return;
		}
		if (copyout(efs_hosttable, arg, sizeof efs_hosttable)) {
			u.u_error = EFAULT;
			return;
		}
E 2
I 2
		bcopy((caddr_t)efs_hosttable, data, sizeof (efs_hosttable));
E 2
		break;

	case FIONREAD:
D 2
		if (minor(dev) > 0) {
			u.u_error = EINVAL;
			return;
		}
E 2
		/* The code to go here is just like efsread except it sets
		 * efs_cmd to be EFS_IOCTL. The size is returned in efs_size
		 * and this is then copied out to the user at address arg.
		 */
		break;
	}
}

efsfstat(dev)
	dev_t dev;
{
	register struct patchboard *pbp;
	register struct file *fp;
	register struct a {
		int	fdes;
		struct stat *sb;
	} *uap = (struct a *)u.u_ap;
	struct efs_controlblock cb;
	struct stat statb;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	fp = getf(uap->fdes);
	if ((pbp = efsfplookup(fp)) == NULL)
		return;
	cb.efs_cmd = EFS_FSTAT;
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	if (cb.efs_cmd == EFS_ERROR) {
		err = cb.efs_error;
		goto out1;
	}
	SETUP_U(&statb, sizeof statb, IN_KERNEL);
	if ((err = soreceive(pbp->pb_so, (struct sockaddr *)0)) != 0)
		goto out1;
	RESTORE_U();
	/* THIS IS NOT PORTABLE -- SHOULD ntohl ALL THE FIELDS OF STATB */
	if (copyout((caddr_t)&statb, (caddr_t)uap->sb, sizeof statb)) {
		err = EFAULT;
		goto out2;
	}
	return;
out1:
	RESTORE_U();
out2:
	u.u_error = err;
}

efsstat(dev)
	dev_t;
{

	efsstat1(dev, EFS_STAT);
}

efslstat(dev)
	dev_t dev;
{

	efsstat1(dev, EFS_LSTAT);
}


efsstat1(dev, cmd)
	dev_t dev;
	int cmd;
{
	register struct a {
		char	*fname;
		struct stat *sb;
	} *uap = (struct a *)u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->fname, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = cmd;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR) {
		err = cb.efs_error;
		goto out2;
	}
	SETUP_U(&statb, sizeof statb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	/* THIS IS NOT PORTABLE -- SHOULD ntohl ALL THE FIELDS OF STATB */
	if (copyout((caddr_t)&statb, (caddr_t)uap->sb, sizeof statb)) {
		err = EFAULT;
		goto out2;
	}
	RESTORE_U();
	soclose(so, 0);
	return;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efsunlink(dev)
	dev_t dev;
{
	struct a {
		char	*fname;
	} *uap = (struct a *)u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->fname, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = EFS_UNLINK;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efsreadlink(dev)
	dev_t dev;
{
	register struct a {
		char	*name;
		char	*buf;
		int	count;
	} *uap = (struct a *)u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i, size, len;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->name, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = EFS_READLINK;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR) {
		err = cb.efs_error;
		goto out2;
	}
	size = ntohl(cb.efs_size);	/* what really was read */
	len = size > uap->count ? uap->count : size;
	SETUP_U(uap->buf, len, !IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	size -= len;
	u.u_r.r_val1 = len;
	while (size > 0) {	/* strip off rest of unwanted string */
		len = size > sizeof cb ? sizeof cb : size;
		SETUP_U(&cb, len, IN_KERNEL);
		soreceive(so, (struct sockaddr *)0);
		size -= len;
	}
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efschmod(dev)
	dev_t dev;
{
	register struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->fname, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = EFS_CHMOD;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	cb.efs_mode = htons(uap->fmode);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efschown(dev)
	dev_t dev;
{
	register struct a {
		char	*fname;
		int	uid;
		int	gid;
	} *uap = (struct a *)u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->fname, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = EFS_CHOWN;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	cb.efs_owner = htons(uap->uid);
	cb.efs_group = htons(uap->gid);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efssaccess(dev)
	dev_t dev;
{
	register struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(uap->fname, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = EFS_ACCESS;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	cb.efs_mode = htons(uap->fmode);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efsutime(dev, fname, tv)
	dev_t dev;
	char *fname;
	time_t tv[2];
{
	char host[EFS_HTMAX];
	register char *pp;
	register struct hosttable *htp;
	struct efs_controlblock cb;
	struct stat statb;
	struct socket *so;
	register int i;
	int err;
	DEFINE_U;

	if (minor(dev) > 0)
		return;		/* info minor devices */
	if ((pp = efspnamescan(fname, host)) == NULL)
		return;
	if ((htp = efshostlookup(host)) == NULL)
		return;
	if ((err = efsconnect(&so, htp)) != 0)
		goto out1;
	/* now send efs packet */
	cb.efs_cmd = EFS_UTIME;
	cb.efs_uid = htons(u.u_uid);
	cb.efs_gid = htons(u.u_gid);
	for (i = 0; i < (sizeof u.u_grps)/(sizeof (int)); i++)
		cb.efs_grps[i] = htonl(u.u_grps[i]);
	cb.efs_time[0] = htonl(tv[0]);
	cb.efs_time[1] = htonl(tv[1]);
	SAVE_U();
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = sosend(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if ((err = efssendpath(so, pp)) != 0)
		goto out2;
	SETUP_U(&cb, sizeof cb, IN_KERNEL);
	if ((err = soreceive(so, (struct sockaddr *)0)) != 0)
		goto out2;
	if (cb.efs_cmd == EFS_ERROR)
		err = cb.efs_error;
out2:
	RESTORE_U();
	soclose(so, 0);
out1:
	u.u_error = err;
}

efsconnect(aso, htp)
	struct socket **aso;
	register struct hosttable *htp;
{
	struct sockaddr_in sin;
	register int err, s, n;

	for (n = 0; n < 3; n++) {
		/* Should request a reserved port here, but for now take any */
		sin.sin_family = AF_INET;
		sin.sin_port = 0;
		sin.sin_addr.s_addr = 0;
		if ((err = socreate(aso, SOCK_STREAM, 0, &sin, 0)) != 0)
			return (err);
		if ((err = soconnect(*aso, &htp->ht_addr)) == 0) {
			s = splnet();
			while (((*aso)->so_state & SS_ISCONNECTING) 
						&& (*aso)->so_error == 0)
				sleep((caddr_t)&(*aso)->so_timeo, PZERO+1);
			err = (*aso)->so_error;
			(*aso)->so_error = 0;
			splx(s);
			if (!err)
				return (0);
		}
		if (err != ECONNREFUSED)
			break;
		soclose(*aso, 0);
		tsleep((caddr_t)&efs_major, PZERO+1, n+1);	/* delay */
	}
out1:
	soclose(*aso, 0);
	return (err);
}

/*
 * RESTRICTION: efs special file MUST be at level 1 in directory
 *	hierarchy (e.g., /net) and host names must be level 2
 *	(e.g., /net/bespin).
 *
 * GARBAGE -- MUST REWRITE
 */
char *
efspnamescan(ap, hp)
	register char *ap, *hp;
{
	register char c;
	register int len;

	/* scan pathname to determine host */

	do { c = fubyte (ap++); }
	while ((c == '/') && (c != '\0'));

	if (c != '\0')
		do { c = fubyte (ap++); }
		while ((c != '/') && (c != '\0'));

	if (c != '\0')
		do { c = fubyte (ap++); }
		while ((c == '/') && (c != '\0'));

 	if (c == '\0') {
		u.u_error = EEXIST;
		return (NULL);
	}

	*hp++ = c;
	len = 1;
	do { c = fubyte (ap++);  *hp++ = c; }
	while ((c != '/') && (c != '\0') && (++len < EFS_HTMAX));
	*(hp-1) = '\0';

	if (len >= EFS_HTMAX) {
		u.u_error = ENOENT;
		return (NULL);
	}
 	if (c == '\0') {
		u.u_error = EEXIST;
		return (NULL);
	}

	len++;
	while (len++ < EFS_HTMAX)
		*hp++ = '\0';	/* zero out rest of host name */
	return (ap-1);		/* pointer to rest of path */
}

off_t
efsfilesize(fp)
	register struct file *fp;
{
	register struct patchboard *pbp;

	if ((pbp = efsfplookup(fp)) == NULL) {
		printf("efsfilesize: lookup(%x) == NULL\n", fp);
		return (0);
	}
	return (pbp->pb_filesize);
}

struct hosttable *
efshostlookup(host)
	char *host;
{
	register struct hosttable *htp;

	for (htp = efs_hosttable; htp < &efs_hosttable[EFS_NHT]; htp++)
		if (bcmp(host, htp->ht_name, sizeof htp->ht_name) == 0)
			return (htp);
	u.u_error = EADDRNOTAVAIL;
	return (NULL);
}

struct patchboard *
efsfplookup(fp)
	register struct file *fp;
{
	register struct patchboard *pbp;

	for (pbp = efs_patchboard; pbp < &efs_patchboard[EFS_NPB]; pbp++)
		if (pbp->pb_fp == fp)
			return (pbp);
	u.u_error = EBADF;
	return (NULL);
}

efssendpath(so, pp)
	register struct socket *so;
	register char *pp;
{
	register struct buf *bp;
	register char *cp;
	register int len;
	int err;
	DEFINE_U;

	/* put path in system buffer -- yech!! */
	bp = geteblk(MAXPATHLEN);
	len = 0;
	for (cp = bp->b_un.b_addr; *cp = fubyte(pp++); cp++)
		if (++len >= MAXPATHLEN)
			break;
	if (len <= 0 || len >= MAXPATHLEN) {
		err = ENOENT;
		goto out1;
	}
	SAVE_U();
	SETUP_U(bp->b_un.b_addr, len+1, IN_KERNEL);
	err = sosend(so, (struct sockaddr *)0);
	RESTORE_U();
out1:
	brelse(bp);
	return (err);
}

efsreset()
{
}
#endif
E 1
