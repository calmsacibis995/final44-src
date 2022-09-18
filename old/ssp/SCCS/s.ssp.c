h12387
s 00072/00000/00000
d D 4.1 80/10/01 17:28:34 bill 1 0
c date and time created 80/10/01 17:28:34 by bill
e
u
U
t
T
I 1
static char *sccsid = "%W% (Berkeley) %G%";
#include <stdio.h>
/*
 * ssp - single space output
 *
 * Bill Joy UCB August 25, 1977
 *
 * Compress multiple empty lines to a single empty line.
 * Option - compresses to nothing.
 */

char	poof, hadsome;

int	ibuf[256];


main(argc, argv)
	int argc;
	char *argv[];
{
	register int c;
	FILE *f;

	argc--, argv++;
	do {
		while (argc > 0 && argv[0][0] == '-') {
			poof = 1;
			argc--, argv++;
		}
	f = stdin;
		if (argc > 0) {
			if ((f=fopen(argv[0], "r")) == NULL) {
				fflush(f);
				perror(argv[0]);
				exit(1);
			}
			argc--, argv++;
		}
		for (;;) {
			c = getc(f);
			if (c == -1)
				break;
			if (c != '\n') {
				hadsome = 1;
				putchar(c);
				continue;
			}
			/*
			 * Eat em up
			 */
			if (hadsome)
				putchar('\n');
			c = getc(f);
			if (c == -1)
				break;
			if (c != '\n') {
				putchar(c);
				hadsome = 1;
				continue;
			}
			do
				c = getc(f);
			while (c == '\n');
			if (!poof && hadsome)
				putchar('\n');
			if (c == -1)
				break;
			putchar(c);
			hadsome = 1;
		}
	} while (argc > 0);
}
E 1
