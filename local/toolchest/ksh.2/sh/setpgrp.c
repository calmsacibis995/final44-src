#include <stdio.h>
main(argc, argv) 
	char **argv;
{
	if (argc < 3 || setpgrp(atoi(argv[1]), atoi(argv[2])) < 0)
		fprintf(stderr,"failed\n");
}
