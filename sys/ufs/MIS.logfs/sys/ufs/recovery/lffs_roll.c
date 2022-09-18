#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <db.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/vnode.h>
#include <sys/stat.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <logging/lffs.h>
#include <logging/lffs_auto.h>
#include <fsck.h>
#include "lffs_roll.h"
#include "lffs_globs.h"

DB *pre_read(int fd);
int open_log(int from_ckp, off_t where);
void log_read(DB *dbp, int fd);
void usage (void);

/*
 * This should be generated automatically in lffs_auto.h.  The
 * parser should be able to generate the maximum possible log
 * records.
 */
#define	MAXLOGREC	512

/* Globals */
char *special;
char *logfile;
char *fsdev;
int verbose;
int no_update;

main(int argc, char **argv)
{
	int ch, logfd;
	daddr_t alt_sb;
	off_t start;
	int from_checkpoint, preread_only;
	DB *dbp;

	special = argv[0];		/* Get command name */

	verbose = 0;
	preread_only = 0;
	no_update = 0;
	alt_sb = 0; /* MIS */
	from_checkpoint = 1;
	while ((ch = getopt(argc, argv, "b:nps:v")) != EOF)
		switch(ch) {
		case 'b':
			alt_sb = atoi(optarg);
			break;
		case 'n':
			no_update = 1;
			break;
		case 'p':
			preread_only = 1;
			break;
		case 's':
			start = (off_t)atoi(optarg);
			from_checkpoint = 0;
			break;
		case 'v':	/* verbose */
			verbose = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	fsdev = *argv++;
	logfile = *argv;

	printf("Recover %s from %s\n", fsdev, logfile);
	if (verbose)
		printf("Argument processing complete.  Running in verbose mode\n");
	logfd = open_log(from_checkpoint, start);
	dbp = pre_read(logfd);
	close(logfd);
	if (preread_only)
		exit(0);
	setup(fsdev);
	fs = sblk.b_un.b_fs;
	logfd = open_log(from_checkpoint, start);
	log_read(dbp, logfd);
	exit(0);
}

void
usage(void)
{
	printf("usage: %s [-npv] -b <sb> <dev> <logfile>\n", special);
	exit(0);
}

void
log_read(DB *dbp, int fd)
{
	char *bp;
	long type;
	size_t len;
	void *rp;

	if (verbose)
		printf("Entering log_read\n");

	bp = NULL;
	len = 0;
	init_recovery();
	while ((rp = lffs_read(fd, &bp, &len, &type)) != NULL)
		lffs_apply_record(dbp, type, rp);

	/*
	 * Need to do cleanup here.  Process any operations still on
	 * the pending operation lists.
	 */
	if (verbose)
		printf("Exiting log_read\n");
	free(bp);
	return;
}
/*
 * Preread the log and find all aborted operations.  Enter the inode number,
 * generation number, and operation type into a hash table.   During actual
 * recovery, we will check the hash table before every abortable operation.
 */

DB *
pre_read(int fd)
{
	struct preop pop;
	struct dirop dop;
	char *bp;
	long type;
	int stat;
	size_t len;
	void *rp;
	DB *dbp;
	DBT key, data, ddata;
	HASHINFO hi;

	if (verbose)
		printf("Entering pre_read\n");

	bp = NULL;
	len = 0;
	hi.bsize = 256;
	hi.ffactor = 15;
	hi.nelem = 50;
	hi.cachesize = 65536;
	hi.hash = NULL;
	hi.lorder = 0;
	data.size = 0;
	data.data = NULL;
	ddata.size = sizeof(struct dirop);
	ddata.data = &dop;
	key.size = sizeof(struct preop);
	key.data = &pop;
	dbp = dbopen(NULL, O_RDWR, 0600, DB_HASH, &hi);
	while ((rp = lffs_read(fd, &bp, &len, &type)) != NULL) {
		stat = 0;
		if (verbose)
			lffs_print(type, rp);

		if (type == LFFS_LOGICAL &&
		    ((LOGICAL_args *)rp)->type == LFFS_DIRLOGICAL) {
			pop.gen = ((LOGICAL_args *)rp)->gen;
			pop.op = LFFS_DIRALLOC;
			pop.ino = ((LOGICAL_args *)rp)->inum;
			pop.lbn = ((LOGICAL_args *)rp)->lbn;
			dop.pbn = 0;
			dop.nfrags = 0;
			stat = (dbp->put)(dbp, &key, &ddata, 0);
		} else if (type == LFFS_ALLOC &&
		    ((ALLOC_args *)rp)->type == LFFS_DIRALLOC) {
			pop.gen = ((ALLOC_args *)rp)->gen;
			pop.op = LFFS_DIRALLOC;
			pop.ino = ((ALLOC_args *)rp)->inum;
			pop.lbn = ((ALLOC_args *)rp)->lbn;
			stat = (dbp->get)(dbp, &key, &ddata, 0);
			if (stat == 1 || ddata.size != sizeof(daddr_t))
				/* MIS -- add more info here */
				fprintf(stderr, "pre_read: log failure. No logical record for allocation record\n");
			else if (stat == 0) {
				dop.pbn = ((ALLOC_args *)rp)->pbn;
				dop.nfrags = ((ALLOC_args *)rp)->nfrags;
				ddata.size = sizeof(struct dirop);
				ddata.data = &dop;
			}
			stat = (dbp->put)(dbp, &key, &ddata, 0);
		} else if (type == REC_ABORT) {
			pop.gen = ((ABORT_args *)rp)->gen;
			pop.op = ((ABORT_args *)rp)->atype;
			pop.ino = ((ABORT_args *)rp)->inum;
			pop.lbn = 0;
			stat = (dbp->put)(dbp, &key, &data, 0);
		}
		if (stat < 0) {
			perror("pre_read:hash error");
			return(NULL);
		} 
		free(rp);
	}

	if (verbose)
		printf("Exiting pre_read\n");
	free(bp);
	return(dbp);
}

int
open_log(int from_ckp, off_t where)
{
	int fd;
	struct stat sbuf;

	fd = open(logfile, O_RDONLY, 0644);
	if (fd < 0)
		perror("log_open/open");
	else if (from_ckp) {
		if (fstat(fd, &sbuf)) {
			perror("log_open/fstat");
			close(fd);
		} else if (verbose)
			printf("Reading from checkpoint %qd\n", sbuf.st_size);
		lseek(fd, sbuf.st_size, SEEK_SET);
	}
	return(fd);
}
