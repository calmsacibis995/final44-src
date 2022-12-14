/*
 * timetrim.c
 * 
 * "timetrim" allows setting and adjustment of the system clock frequency
 * trim parameter on Silicon Graphics machines.  The trim value native
 * units are nanoseconds per second (10**-9), so a trim value of 1 makes
 * the system clock step ahead 1 nanosecond more per second than a value
 * of zero.  Xntpd currently uses units of 2**-20 secs for its frequency
 * offset (drift) values; to convert to a timetrim value, multiply by
 * 1E9 / 2**20 (about 954).
 * 
 * "timetrim" with no arguments just prints out the current kernel value.
 * With a numeric argument, the kernel value is set to the supplied value.
 * The "-i" flag causes the supplied value to be added to the kernel value.
 * The "-n" option causes all input and output to be in xntpd units rather
 * than timetrim native units.
 *
 * Note that there is a limit of +-3000000 (0.3%) on the timetrim value
 * which is (silently?) enforced by the kernel.
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/syssgi.h>

#define abs(X) (((X) < 0) ? -(X) : (X))
#define USAGE "usage: timetrim [-n] [[-i] value]\n"
#define SGITONTP(X) ((double)(X) * 1048576.0/1.0e9)
#define NTPTOSGI(X) ((long)((X) * 1.0e9/1048576.0))

main(argc, argv)
int argc;
char **argv;
{
	char *rem;
	int c, incremental = 0, ntpunits = 0;
	long timetrim;
	double value, strtod();
	
	while (--argc && **++argv == '-' && isalpha(argv[0][1])) {
		switch (argv[0][1]) {
		case 'i':
			incremental++;
			break;
		case 'n':
			ntpunits++;
			break;
		default:
			fprintf(stderr, USAGE);
			exit(1);
		}
	}

	if (syssgi(SGI_GETTIMETRIM, &timetrim) < 0) {
		perror("syssgi");
		exit(2);
	}

	if (argc == 0) {
		if (ntpunits)
			fprintf(stdout, "%0.5lf\n", SGITONTP(timetrim));
		else
			fprintf(stdout, "%ld\n", timetrim);
	} else if (argc != 1) {
		fprintf(stderr, USAGE);
		exit(1);
	} else {
		value = strtod(argv[0], &rem);
		if (*rem != '\0') {
			fprintf(stderr, USAGE);
			exit(1);
		}
		if (ntpunits)
			value = NTPTOSGI(value);
		if (incremental)
			timetrim += value;
		else
			timetrim = value;
		if (syssgi(SGI_SETTIMETRIM, timetrim) < 0) {
			perror("syssgi");
			exit(2);
		}
	}
}
