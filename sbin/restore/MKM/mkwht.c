#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(ac, av)
	int ac;
	char *av[];
{
	char buf[BUFSIZ];

	if (ac != 2) {
		printf("Usage: %s file\n", av[0]);
		exit(1);
	}
	if (mknod(av[1], S_IFWHT, 0) < 0) {
		perror(av[1]);
		exit(2);
	}
	exit(0);
}
