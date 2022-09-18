#define FATAL_DADDR	-1
struct preop {
	long	gen;
	ino_t	ino;
	u_long	op;
	daddr_t	lbn;
};

struct dirop {
	daddr_t	pbn;
	int	nfrags;
};

struct slot {
	daddr_t block;
	int off;
	int found;
};


void init_recover(void);
void IALLOC_RECOVER(DB *dbp, IALLOC_args *argp);
void CREATE_RECOVER(DB *dbp, CREATE_args *argp);
void REMOVE_RECOVER(DB *dbp, REMOVE_args *argp);
void LINK_RECOVER(DB *dbp, LINK_args *argp);
void SYMLINK_RECOVER(DB *dbp, SYMLINK_args *argp);
void RENAME_RECOVER(DB *dbp, RENAME_args *argp);
void ALLOC_RECOVER(DB *dbp, ALLOC_args *argp);
void ABORT_RECOVER(DB *dbp, ABORT_args *argp);
void LOGICAL_RECOVER(DB *dbp, LOGICAL_args *argp);

int	add_entry(struct dinode *dip, ino_t new_ino, char *name,
	int namelen, int mode, struct slot *freep);
daddr_t	bindex(struct dinode *dip, daddr_t lbn, daddr_t bn);
daddr_t	bmap(struct dinode *dip, daddr_t lbn);
struct dirent * finddir(struct dinode *dip, char *name, int name_length,
	struct slot *freep);
int	dirok(struct dirent *dp, int space);

int	lffs_checkfrag(int nfrags, daddr_t pref);
daddr_t	lffs_findblock(int nfrags, daddr_t pref);
void	lffs_frag_setclr(daddr_t start, int nfrags, int allocit);
int	lffs_inode_setclr(ino_t ino, int isdir, int allocit);
void	make_newdir(ino_t newino, ino_t parentino, daddr_t lbn, int mode);
int	remdir(struct dinode *dip, struct dirent *dp, struct slot *locp);
void	truncate_inode(struct dinode *dip, off_t size);
