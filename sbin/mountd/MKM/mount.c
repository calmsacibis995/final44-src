#include <sys/param.h>
#include <sys/ucred.h>
#include <sys/mount.h>
#include <sys/socket.h>
#include <rpc/rpc.h>
#include <netiso/iso.h>

int	MOUNT __P((int, const char *, int, void *));
#define mount MOUNT

/*
 * Just print out mount info, don't actually do it!
 */
MOUNT(type, dir, flags, ptr)
	int type;
	const char *dir;
	int flags;
	void *ptr;
{
	struct ufs_args *args;
	struct ucred *cr;
	int i;

	args = ptr;
	fprintf(stderr, "mount: dir %s, flags 0x%x, spec %s, exflags 0x%x",
	    dir, flags, args->fspec, args->exflags);
	if (args->exflags & MNT_DELEXPORT) {
		fprintf(stderr, "\n");
		return;
	}
	if (args->saddr->sa_family == AF_INET) {
		fprintf(stderr, ", addr %s",
		    inet_ntoa(((struct sockaddr_in *)
		    (args->saddr))->sin_addr.s_addr));
		if (args->msklen > 0)
			fprintf(stderr, ", mask %s\n",
			    inet_ntoa(((struct sockaddr_in *)
			    (args->smask))->sin_addr.s_addr));
		else
			fprintf(stderr, "\n");
	} else if (args->saddr->sa_family == AF_ISO) {
		struct sockaddr_iso *iso;

		iso = (struct sockaddr_iso *)args->saddr;
		fprintf(stderr, ", addr ");
		for (i = 0; i < iso->siso_nlen; i++)
			fprintf(stderr, "%02x.", iso->siso_data[i]);
		fprintf(stderr, "\n");
	}
	cr = &args->anon;
	fprintf(stderr, "\tcred: uid %d", cr->cr_uid);
	if (cr->cr_ngroups > 0)
		fprintf(stderr, ", gid");
	for (i = 0; i < cr->cr_ngroups; i++)
		fprintf(stderr, " %d,", cr->cr_groups[i]);
	fprintf(stderr, "\n");
	return (0);
}
