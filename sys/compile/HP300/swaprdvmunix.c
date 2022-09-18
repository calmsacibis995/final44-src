#include "sys/param.h"
#include "sys/conf.h"

dev_t	rootdev = makedev(2, 0);
dev_t	dumpdev = makedev(2, 1);

struct	swdevt swdevt[] = {
	{ makedev(2, 1),	0,	0 },	/* rd0b */
	{ makedev(2, 9),	0,	0 },	/* rd1b */
	{ NODEV, 0, 0 }
};
