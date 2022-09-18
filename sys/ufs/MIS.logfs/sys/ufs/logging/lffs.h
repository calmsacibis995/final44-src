#define MAX_STRING	257

/* 
 * Log record types.
 *
 */

#define LFFS_ERROR	-1
#define LFFS_EOF	0
#define	LFFS_CREATE	1
#define	LFFS_MKDIR	2
#define	LFFS_IALLOC	3
#define	LFFS_RMDIR	4
#define LFFS_LINK	5
#define LFFS_SYMLINK	6
#define LFFS_UNLINK	7
#define LFFS_MKNOD	8
#define LFFS_RENAME	9
#define LFFS_ALLOC	10
#define LFFS_DEALLOC	11
#define LFFS_FEXTEND	12
#define	LFFS_IDEALLOC	13
#define LFFS_LOGICAL	14
#define	LFFS_DIRALLOC	15
#define	LFFS_DIRLOGICAL	16
#define	LFFS_DIRFEXTEND	17
#define LFFS_ABORT	18


/* Data structure for ioctl that performs a logged write */

struct lwrite_entry {
	struct 	uio *uio;
	off_t	logrec_begin;
	off_t	logrec_end;
};

extern char *log_names[];
