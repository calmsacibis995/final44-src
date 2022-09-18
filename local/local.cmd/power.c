#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include </usr/src/usr.bin/tip/pathnames.h>

char *db_array[3] = { _PATH_REMOTE, 0, 0 };

main(ac, av)
	int ac;
	char *av[];
{
	int fd;
	char *host, *pw, *getremcap();
	extern int errno;

	if (ac == 1) {
		if ((host = getenv("HOST")) == NULL) {
			fprintf(stderr, "%s: no host specified\n", av[0]);
			exit(1);
		}
	} else if (ac != 2) {
		printf("Usage: %s host\n", av[0]);
		exit(2);
	} else {
		host = av[1];
	}
	pw = getremcap(av[0], host);
	if ((fd = open(pw, O_NONBLOCK|O_RDONLY)) < 0) {
		fprintf(stderr, "Could not power cycle %s on port %s: %s\n",
		    host, pw, strerror(errno));
		exit(3);
	}
	sleep(2);
	close(fd);
	exit(0);
}

char *
getremcap(cmd, host)
	char *cmd;
	char *host;
{
	char *bp, *pw;
	char *rempath;
	int   stat;

	rempath = getenv("REMOTE");
	if (rempath != NULL) {
		if (*rempath != '/')
			/* we have an entry */
			cgetset(rempath);
		else {	/* we have a path */
			db_array[0] = rempath;
			db_array[1] = _PATH_REMOTE;
		}
	}
	if ((stat = cgetent(&bp, db_array, host)) < 0) {
		switch(stat) {
		case -1:
			fprintf(stderr, "%s: unknown host %s\n", cmd, host);
			break;
		case -2:
			fprintf(stderr, 
			    "%s: can't open host description file\n", cmd);
			break;
		case -3:
			fprintf(stderr, "%s: %s\n", cmd,
			    "possible reference loop in host description file");
			break;
		}
		exit(4);
	}

	if (cgetstr(bp, "pw", &pw) < 0) {
		fprintf(stderr, "%s: host %s has no power port (pw) defined\n",
		    cmd, host);
		exit(5);
	}
	return (pw);
}
