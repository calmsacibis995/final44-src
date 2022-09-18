/*	%M%	%I%	%E%	*/

#include <sys/ioctl.h>
#include <stdio.h>

struct sc750hdr {
	short	sc_cyl;		/* 0150000 + cylinder number */
	short	sc_trksec;	/* (track << 8) | sector */
} sc750hdr;
int	errs;

main(argc, argv)
	int argc;
	char **argv;
{
	int bad = 0;

	argc--, argv++;
	if (!strcmp(*argv, "-b")) {
		bad++;
		argc--, argv++;
	}
	if (argc == 0) {
		fprintf(stderr, "usage: capfix [ -b ] sector ... > /dev/rhp??\n");
		exit(1);
	}
	do {
		int cyl, trk, sec;
		register int i;

		i = atoi(*argv);
		cyl = (i / 32) / 16;
		trk = (i / 32) % 16;
		sec = i % 32;
		if ((((cyl * 16) + trk) * 32 + sec) != i)
			abort();
		fprintf(stderr, "fix sector %d = (cyl,trk,sec) (%d,%d,%d)\n",
		    i, cyl, trk, sec);
		if (bad) {
			sc750hdr.sc_cyl = 0;
			sc750hdr.sc_trksec = 0;
		} else {
			sc750hdr.sc_cyl = 0150000 + cyl;
			sc750hdr.sc_trksec = (trk << 8) | sec;
		}
		lseek(1, i * 512, 0);
		ioctl(1, DKIOCHDR, 0);
		if (write(1, (char *)&sc750hdr, sizeof (sc750hdr)) !=
		    sizeof (sc750hdr)) {
			errs++;
			perror("write");
		}
		argc--, argv++;
	} while (argc > 0);
	exit(errs);
}
