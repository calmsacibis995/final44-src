#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{
    register n = 1;

    if (--argc)
	if ((n = atoi (*++argv)) < 1) exit(1);
    putchar ('');
    while (--n) {
	fflush(stdout);
	sleep(1);
	putchar ('');
    }
}
