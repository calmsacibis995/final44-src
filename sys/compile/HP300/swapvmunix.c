#include "sys/param.h"
#include "sys/conf.h"

dev_t	rootdev = makedev(4, 0);
dev_t	dumpdev = makedev(4, 1);

struct	swdevt swdevt[] = {
	{ makedev(4, 1),	0,	0 },	/* sd0b */
	{ makedev(2, 1),	0,	0 },	/* rd0b */
	{ makedev(4, 9),	0,	0 },	/* sd1b */
	{ makedev(2, 9),	0,	0 },	/* rd1b */
	{ makedev(4, 17),	0,	0 },	/* sd2b */
	{ makedev(2, 17),	0,	0 },	/* rd2b */
	{ NODEV, 0, 0 }
};
