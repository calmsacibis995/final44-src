#include "sys/param.h"
#include "sys/conf.h"

dev_t	rootdev = makedev(4, 0);
dev_t	dumpdev = makedev(4, 3);

struct	swdevt swdevt[] = {
	{ makedev(4, 3),	0,	0 },	/* sd0d */
	{ makedev(4, 11),	0,	0 },	/* sd1d */
	{ makedev(4, 19),	0,	0 },	/* sd2d */
	{ NODEV, 0, 0 }
};
