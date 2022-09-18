#include "idfilt.h"
#include "dev.h"

#ifndef DEVDIR
#define DEVDIR "/usr/lib/font"
#endif

FILE *infile;
char *filename;
int lineno = 0;

float maxx, maxy;
float minx, miny;
float width = 4.0;
float colwid = 6.0;

boolean maxxset, maxyset;
boolean minxset, minyset;
boolean widset, colset;
boolean boundset;
char *device = "va";
char *devdir = DEVDIR;
int RESOLUTION;
float xscale, yscale;


boolean veryfirst = TRUE;

main (argc, argv)
int argc;
char *argv[];
{
	register char *cp;
	char *getenv();

	if (cp = getenv("PRINTER")) device = cp;
	if (cp = getenv("TYPESETTER")) device = cp;
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'F':
			devdir = &argv[1][2];
			break;
		case 'T':
		case 'P':
			device = &argv[1][2];
			break;
		default:
			fprintf (stderr, "ideal filter: unknown flag %c\n", argv[1][1]);
			break;
		}
		argc--;
		argv++;
	}
	fileinit();
	if (argc < 2) {
		infile = stdin;
		lineno = 0;
		interpret (infile);
	} else {
		while (argc-- > 1) {
			if (!(infile = fopen (*++argv, "r"))) {
				fprintf (stderr, "ideal filter: can't open %s\n", *argv);
				exit (1);
			}
			filename = *argv;
			lineno = 0;
			interpret (infile);
			fclose (infile);
		}
	}
	exit (0);
}

fileinit()
{
	int fin;
	struct dev device_info;
	char temp[100];

	sprintf(temp, "%s/dev%s/DESC.out", devdir, device);
	if ((fin = open(temp, 0)) < 0) {
	    fprintf(stderr, "can't open tables for %s\n", temp);
	    exit(1);
	}
	read(fin, &device_info, sizeof(struct dev));
	RESOLUTION = device_info.res;
	close(fin);
}

interpret (infile)
register FILE *infile;
{
	char buf[250];

	int numitems;
	char cmd[10];
	int i[10];
	float f[30];
	char *string;


	while (fgets (buf, sizeof buf, infile)) {
		lineno++;
		idjusttext (buf);
		if (buf[0] == '.') {
			if (buf[1] == 'I') {
				switch (buf[2]) {
				case 'S':
					numitems = sscanf (buf, "%s %d %d %d %d %d %d",
						cmd, &i[0], &i[1], &i[2], &i[3], &i[4], &i[5]
					);
					idstart (numitems, i);
					maxxset = minxset = FALSE;
					maxyset = minyset = FALSE;
					colset = boundset = widset = FALSE;
					break;
				case 'E':
					idendE ();
					break;
				case 'F':
					idendF ();
					break;
				default:
					break;
				}
			} else if (buf[1] == '.' && buf[2] == '.') {
				sscanf (buf, "%s", cmd);
				if (!boundset) {
					if (strcmp (cmd, "...maxx") == 0) {
						sscanf (buf, "%s %f",
							cmd, &f[0]
						);
						idmaxx (f[0]);
					} else if (strcmp (cmd, "...maxy") == 0) {
						sscanf (buf, "%s %f",
							cmd, &f[0]
						);
						idmaxy (f[0]);
					} else if (strcmp (cmd, "...minx") == 0) {
						sscanf (buf, "%s %f",
							cmd, &f[0]
						);
						idminx (f[0]);
					} else if (strcmp (cmd, "...miny") == 0) {
						sscanf (buf, "%s %f",
							cmd, &f[0]
						);
						idminy (f[0]);
					} else if (strcmp (cmd, "...width") == 0) {
						sscanf (buf, "%s %f",
							cmd, &f[0]
						);
						idwidth (f[0]);
					} else if (strcmp (cmd, "...colwid") == 0) {
						sscanf (buf, "%s %f",
							cmd, &f[0]
						);
						idcolwid (f[0]);
					} else if (strcmp (cmd, "...obbox") == 0) {
						if (!veryfirst) {
							maxxset = maxyset = TRUE;
							minxset = minyset = TRUE;
							boundset = TRUE;
						}
					} else if (strcmp (cmd, "...noerase") == 0) {
						idnoerase ();
					} else if (strcmp (cmd, "...yeserase") == 0) {
						idyeserase ();
					} else {
						idendbound ();
						veryfirst = FALSE;
					}
				}
				if (boundset) {
					if (strcmp (cmd, "...line") == 0) {
						sscanf (buf, "%s %f %f %f %f",
							cmd, &f[0], &f[1], &f[2], &f[3]
						);
						idline (f[0], f[1], f[2], f[3]);
					} else if (strcmp (cmd, "...circle") == 0) {
						sscanf (buf, "%s %f %f %f",
							cmd, &f[0], &f[1], &f[2]
						);
						idcircle (f[0], f[1], f[2]);
					} else if (strcmp (cmd, "...arc") == 0) {
						sscanf (buf, "%s %f %f %f %f %f %f %f %f %f",
							cmd, &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7], &f[8]
						);
						idarc (f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7], f[8]);
					} else if (strcmp (cmd, "...left") == 0) {
						sscanf (buf, "%s %f %f",
							cmd, &f[0], &f[1]
						);
						buf[strlen(buf)-1] = '\0';
						string = buf;
						while (*string != '\'')
							string ++;
						idleft (f[0], f[1], string);
					} else if (strcmp (cmd, "...center") == 0) {
						sscanf (buf, "%s %f %f",
							cmd, &f[0], &f[1]
						);
						buf[strlen(buf)-1] = '\0';
						string = buf;
						while (*string != '\'')
							string ++;
						idcenter (f[0], f[1], string);
					} else if (strcmp (cmd, "...right") == 0) {
						sscanf (buf, "%s %f %f",
							cmd, &f[0], &f[1]
						);
						buf[strlen(buf)-1] = '\0';
						string = buf;
						while (*string != '\'')
							string ++;
						idright (f[0], f[1], string);
					} else if (strcmp (cmd, "...spline") == 0) {
						sscanf (buf, "%s %f %f",
							cmd, &f[0], &f[1]
						);
						idspline (f[0], f[1]);
					} else if (strcmp (cmd, "...knot") == 0) {
						sscanf (buf, "%s %f %f",
							cmd, &f[0], &f[1]
						);
						idknot (f[0], f[1]);
					} else if (strcmp (cmd, "...endspline") == 0) {
						idendspline ();
					}
				}
			}
		}
	}
}

void idmaxx (x)
float x;
{
	if (!maxxset) {
		maxx = x;
		maxxset = TRUE;
	}
}

void idmaxy (y)
float y;
{
	if (!maxyset) {
		maxy = y;
		maxyset = TRUE;
	}
}

void idminx (x)
float x;
{
	if (!minxset) {
		minx = x;
		minxset = TRUE;
	}
}

void idminy (y)
float y;
{
	if (!minyset) {
		miny = y;
		minyset = TRUE;
	}
}

void idwidth (wid)
float wid;
{
	if (!widset) {
		width = wid;
		widset = TRUE;
	}
}

void idcolwid (wid)
float wid;
{
	if (!colset) {
		colwid = wid;
		colset = TRUE;
	}
}


void idjusttext (str)
char *str;
{
	if (
		strncmp (str, ".IE", 3) &&
		strncmp (str, "...knot", 7) &&
		strncmp (str, "...endspline", 12) &&
		strncmp (str, "...left", 7) &&
		strncmp (str, "...center", 9) &&
		strncmp (str, "...right", 8)
	)
		fputs (str, stdout);
}

void idstart ()
{
}

void idendbound ()
{
	if (boundset)
		return;
	idminx (-6.0);
	idmaxy (6.0);
	idmaxx (6.0);
	idminy (-6.0);
	if (maxx - minx < 0.2) {
		maxx += 1;
		minx -= 1;
	}
	if (maxy - miny < 0.2) {
		maxy += 1;
		miny -= 1;
	}
	xscale = width*RESOLUTION/(maxx - minx);
	yscale = - xscale;
	minx -= 0.5*(colwid - width)*RESOLUTION/xscale;
	maxx += 0.5*(colwid - width)*RESOLUTION/xscale;
	boundset = TRUE;
	printf (".ne %4.2fi\n", yscale*(miny - maxy)/RESOLUTION);
}

void idline (x1, y1, x2, y2)
float x1;
float y1;
float x2;
float y2;
{
	long int X1, Y1, X2, Y2;
	boolean shortvert, shorthoriz, nonrectilinear;
	X1 = round(xscale*x1);
	Y1 = round(yscale*y1);
	X2 = round(xscale*x2);
	Y2 = round(yscale*y2);
	shortvert = X1 == X2 && abs(Y1-Y2) < RESOLUTION/2;
	shorthoriz = Y1 == Y2 && abs(X1-X2) < RESOLUTION/2;
	nonrectilinear = X1 != X2 && Y1 != Y2;
	printf ("\\h'%du'\\v'%du'\\D'l %du %du'\\h'%du'\\v'%du'\n.sp -1\n",
		round(xscale*(x1-minx)), round(yscale*(y1-maxy)),
		round(xscale*(x2-x1)), round(yscale*(y2-y1)),
		round(-xscale*(x2-minx)), round(-yscale*(y2-maxy))
	);
}

void idcircle (x0, y0, r)
float x0;
float y0;
float r;
{
	printf ("\\h'%du'\\v'%du'\\D'c %du'\\h'%du'\\v'%du'\n.sp -1\n",
		round(xscale*(x0-r-minx)), round(yscale*(y0-maxy)),
		round(2*xscale*r),
		round(-xscale*(x0+r-minx)), round(-yscale*(y0-maxy))
	);
}

void idarc (x0, y0, x1, y1, x2, y2, t1, t2, r)
float x0;
float y0;
float x1;
float y1;
float x2;
float y2;
float t1;
float t2;
float r;
{
	if (xscale*r > 30000.0)
		idline (x1, y1, x2, y2);
	else {
		printf ("\\h'%du'\\v'%du'\\D'a %du %du %du %du'\\h'%du'\\v'%du'\n.sp -1\n",
			round(xscale*(x1-minx)), round(yscale*(y1-maxy)),
			round(xscale*(x0-x1)), round(yscale*(y0-y1)),
			round(xscale*(x2-x0)), round(yscale*(y2-y0)),
			round(-xscale*(x2-minx)), round(-yscale*(y2-maxy))
		);
	}
}

void idleft (x, y, str)
float x;
float y;
char *str;
{
	str == ++str;
	printf ("\\h'%du'\\v'%du'%s\\h'-\\w'%s'u'\n.sp -1\n",
		round(xscale*(x-minx)), round(yscale*(y-maxy)), str, str);
}

void idcenter (x, y, str)
float x;
float y;
char *str;
{
	str = ++str;
	printf("\\h'%du'\\v'%du'\\h'-\\w'%s'u/2u'%s\\h'-\\w'%s'u/2u'\n.sp -1\n",
		round(xscale*(x-minx)), round(yscale*(y-maxy)), str, str, str);
}

void idright (x, y, str)
float x;
float y;
char *str;
{
	str = ++str;
	printf ("\\h'%du'\\v'%du'\\h'-\\w'%s'u'%s\\h'-\\w'%s'u'\n.sp -1\n",
		round(xscale*(x-minx)), round(yscale*(y-maxy)), str, str, str);
}

void idendE ()
{
	if (boundset)
		printf (".sp %du\n.sp 1\n.sp 1\n", round(yscale*(miny-maxy)));
	printf (".IE\n");
}

void idendF ()
{
}

float osplx, osply;

void idspline (sx, sy)
float sx, sy;
{
	osplx = sx;
	osply = sy;
	printf ("\\h'%du'\\v'%du'\\D'~", round(xscale*(osplx-minx)),
		round(yscale*(osply-maxy)));
}

void idknot (sx, sy)
float sx, sy;
{
	printf (" %du %du", round(xscale*(sx-osplx)), round(yscale*(sy-osply)));
	osplx = sx;
	osply = sy;
}

void idendspline ()
{
	printf ("'\\h'%du'\\v'%du'\n.sp -1\n",
		round(xscale*(minx-osplx)), round(yscale*(maxy-osply)));
}

void idnoerase ()
{
}


void idyeserase ()
{
}
