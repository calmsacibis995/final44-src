#include <stdio.h>
#include "format.h"

void
main(int argc, char **argv)
{
	FILE *in, *out;
	char *c, *fbuf[LPP], *out_str = (char *) malloc (4 + strlen(argv[1]));
	char left[100][256], right[100][256];
	int lc = 0, n, x, lsize;

	sprintf(out_str, "%s.tc", argv[1]);

	in = fopen(argv[1], "r");
	out = fopen(out_str, "w");

	for (x = 0; x < LPP; x++)
		fbuf[x] = (char *) malloc (MAXLINE * sizeof (char));

	while ((c = fgetline(in, NULL)) != NULL) {
		lsize = Format(c, fbuf);
		if (lc + lsize <= LPP)
			for (n = 0; n < lsize; n++)
				sprintf(left[lc++],"%s", fbuf[n]);
		else if (lc + lsize <= 2 * LPP) {
			if (lc <= LPP)
				lc = LPP;
			for (n = 0; n < lsize; n++) {
				sprintf(right[lc - LPP],"%s", fbuf[n]);
				lc++;
			}
		} else {
			for (lc = 0; lc < LPP; lc++)
				fprintf(out, "%-40s%-40s\n", left[lc],
							right[lc]);
			fprintf(out, "\n");
			lc = 0;
			for (n = 0; n < lsize; n++)
				sprintf(left[lc++],"%s", fbuf[n]);
		}
	}
	if (lc <= LPP)
		for (n = 0; n < lc; n++)
			fprintf(out, "%-40s\n", left[n]);
	else {
		for (n = 0; n < lc - LPP; n++)
			fprintf(out, "%-40s%-40s\n", left[n], right[n]);
		for (x = n; x < LPP; x++)
			fprintf(out, "%-40s\n", left[x]);
	}
	fprintf(out, "\n");
	fclose(in);
	fclose(out);
}
