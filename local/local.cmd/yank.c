/*
 * yank - give information on tty's connected to the patch panel
 *	  in 570 Evans Hall
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <utmp.h>
#include <ttyent.h>

char	utmp[] = "/etc/utmp";

#define	FTTY	50
struct freetty {
	char	f_term[8];	/* terminal name */
	int	f_busy;		/* found in utmp file */
	long	f_when;		/* time last written */
} freetty[FTTY], *ftty[FTTY];

int	nfttys;			/* number of entries in freetty */

char	*tmof();
int	qucmp();

main()
{
	register struct freetty *fp, **fpp;
	register struct ttyent *tp;
	FILE *tfp;
	int freecount;
	struct utmp ubuf;
	long now;

	fp = freetty;
	setttyent();
	while (tp = getttyent()) {
		if (strcmp(tp->ty_type, "plugboard") == 0) {
			if (fp >= &freetty[FTTY])
				break;
			strncpy(fp->f_term, tp->ty_name, sizeof(fp->f_term));
			fp->f_busy = 0;
			fp++;
		}
	}
	endttyent();
	nfttys = fp - freetty;

	if ((tfp = fopen(utmp, "r")) == NULL) {
	    	perror(utmp);
	    	exit(1);
	}
	now = time(0);
	while (fread(&ubuf, sizeof ubuf, 1, tfp) == 1) {
		if (ubuf.ut_name[0] == '\0')
			continue;
		for (fp = freetty; fp < &freetty[nfttys]; fp++)
			if (!strncmp(fp->f_term, ubuf.ut_line, sizeof ubuf.ut_line)) {
				fp->f_busy = 1;
				break;
			}
	}
	fpp = ftty;
	for (fp = freetty; fp < &freetty[nfttys]; fp++) {
		if (!fp->f_busy) {
			*fpp = fp;
			if ((fp->f_when = ttytime(fp->f_term)) < now)
				fpp++;
		}
	}
	freecount = fpp - ftty;
	if (freecount == 0) {
		printf("All are in use.\n");
		exit(1);
	}
	qsort(ftty, freecount, sizeof(struct freetty *), qucmp);
	printf("tty      idle time\n");
	printf("----     ---------\n");
	for (fpp = ftty; fpp < &ftty[freecount]; fpp++)
		printf("%-8.8s %s\n", (*fpp)->f_term,
			tmof(now - (*fpp)->f_when));
	exit(0);
}

/*
 * Determine how long the given tty has been idle.
 */
long
ttytime(name)
	char *name;
{
	static char ttyname[30] = "/dev/";
	struct stat statb;

	strncpy(ttyname+5, name, sizeof(freetty[0].f_term));
	if (stat(ttyname, &statb) < 0) {
		perror(ttyname);
		return(0);
	}
	return(statb.st_ctime);
}

/*
 * Return a pretty string which gives idle time in
 * hours, minutes, seconds.
 */

char *
tmof(sec)
{
	static char tmbuf[10];
	long s, m, h;

	s = sec % 60;
	sec /= 60;
	m = sec % 60;
	sec /= 60;
	h = sec;
	if (h > 99) {
		strcpy(tmbuf, "+99:59:59");
		return(tmbuf);
	}
	strcpy(tmbuf, "         ");
	if (h != 0)
		place(h, &tmbuf[1], 0);
	if (h != 0 || m != 0)
		place(m, &tmbuf[4], 1);
	sprintf(&tmbuf[7], "%02d", s);
	return(tmbuf);
}

/*
 * Drop the number followed by a : in the given spot (two least sig
 * decimal digits only).
 */

place(d, s, z)
	char *s;
{

	s[0] = (d / 10) % 10 + '0';
	if (!z && s[0] == '0')
		s[0] = ' ';
	s[1] = d % 10 + '0';
	s[2] = ':';
}

/*
 * Comparison routine for qsort.
 * Sort into increasing order by f_when;
 */

qucmp(l, r)
	struct freetty **l, **r;
{

   	if ((*l)->f_when > (*r)->f_when)
		return(1);  
   	if ((*l)->f_when < (*r)->f_when)
		return(-1); 
	return(0); 
}
