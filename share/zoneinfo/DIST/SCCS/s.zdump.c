h09912
s 00034/00003/00241
d D 5.2 89/03/17 18:27:52 bostic 2 1
c update from Arthur Olson
e
s 00244/00000/00000
d D 5.1 89/03/17 18:27:20 bostic 1 0
c date and time created 89/03/17 18:27:20 by bostic
e
u
U
t
T
I 1
#ifndef lint
#ifndef NOID
D 2
static char	elsieid[] = "@(#)zdump.c	4.9";
E 2
I 2
static char	elsieid[] = "@(#)zdump.c	4.10";
E 2
#endif /* !defined NOID */
#endif /* !defined lint */

/*
** This code has been made entirely independent of the rest of the time
** conversion package to increase confidence in the verification it provides.
** You can use this code to help in verifying other implementations.
*/

#include <stdio.h>
#include <time.h>
#include <sys/types.h>

#ifndef TRUE
#define TRUE		1
#endif /* !defined TRUE */

#ifndef FALSE
#define FALSE		0
#endif /* !defined TRUE */

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS	0
#endif /* !defined EXIT_SUCCESS */

#ifndef EXIT_FAILURE
#define EXIT_FAILURE	1
#endif /* !defined EXIT_FAILURE */

#ifndef SECSPERMIN
#define SECSPERMIN	60
#endif /* !defined SECSPERMIN */

#ifndef SECSPERHOUR
#define SECSPERHOUR	3600
#endif /* !defined SECSPERHOUR */

#ifndef HOURSPERDAY
#define HOURSPERDAY	24
#endif /* !defined HOURSPERDAY */

#ifndef EPOCH_YEAR
#define EPOCH_YEAR	1970
#endif /* !defined EPOCH_YEAR */

#ifndef DAYSPERNYEAR
#define DAYSPERNYEAR	365
#endif /* !defined DAYSPERNYEAR */

extern char **	environ;
extern int	getopt();
extern char *	malloc();
extern char *	optarg;
extern int	optind;
extern void	tzset();

char *		tzname[2];

static int	longest;
static void	show();
static void	hunt();
static long	delta();
I 2
static char *	ecpyalloc();
E 2

I 2
static char *	progname;

E 2
int
main(argc, argv)
int	argc;
char *	argv[];
{
	register int	i, c;
	register int	vflag;
	register char *	cutoff;
	register int	cutyear;
	register long	cuttime;
	time_t		now;
	time_t		t, newt;
	time_t		hibit;
	struct tm	tm, newtm;

I 2
	progname = argv[0];
E 2
	vflag = 0;
	cutoff = NULL;
	while ((c = getopt(argc, argv, "c:v")) == 'c' || c == 'v')
		if (c == 'v')
			vflag = 1;
		else	cutoff = optarg;
	if (c != EOF || optind == argc - 1 && strcmp(argv[optind], "=") == 0) {
		(void) fprintf(stderr,
			"%s: usage is %s [ -v ] [ -c cutoff ] zonename ...\n",
			argv[0], argv[0]);
		(void) exit(EXIT_FAILURE);
	}
	if (cutoff != NULL)
		cutyear = atoi(cutoff);
	/*
	** VERY approximate.
	*/
	cuttime = (long) (cutyear - EPOCH_YEAR) *
		SECSPERHOUR * HOURSPERDAY * DAYSPERNYEAR;
	(void) time(&now);
	longest = 0;
	for (i = optind; i < argc; ++i)
		if (strlen(argv[i]) > longest)
			longest = strlen(argv[i]);
	for (hibit = 1; (hibit << 1) != 0; hibit <<= 1)
		;
	for (i = optind; i < argc; ++i) {
		register char **	saveenv;
		char *			tzequals;
I 2
		char *			ab;
E 2
		char *			fakeenv[2];

		tzequals = malloc((unsigned) (strlen(argv[i]) + 4));
		if (tzequals == NULL) {
			(void) fprintf(stderr, "%s: can't allocate memory\n",
				argv[0]);
			(void) exit(EXIT_FAILURE);
		}
		(void) sprintf(tzequals, "TZ=%s", argv[i]);
		fakeenv[0] = tzequals;
		fakeenv[1] = NULL;
		saveenv = environ;
		environ = fakeenv;
		(void) tzset();
		free(tzequals);
		environ = saveenv;
		show(argv[i], now, FALSE);
		if (!vflag)
			continue;
		/*
		** Get lowest value of t.
		*/
		t = hibit;
		if (t > 0)		/* time_t is unsigned */
			t = 0;
		show(argv[i], t, TRUE);
		t += SECSPERHOUR * HOURSPERDAY;
		show(argv[i], t, TRUE);
		tm = *localtime(&t);
I 2
		ab = ecpyalloc(tzname[tm.tm_isdst]);
E 2
		for ( ; ; ) {
			if (cutoff != NULL && t >= cuttime)
				break;
			newt = t + SECSPERHOUR * 12;
			if (cutoff != NULL && newt >= cuttime)
				break;
			if (newt <= t)
				break;
			newtm = *localtime(&newt);
			if (delta(&newtm, &tm) != (newt - t) ||
D 2
				newtm.tm_isdst != tm.tm_isdst)
E 2
I 2
				newtm.tm_isdst != tm.tm_isdst ||
				strcmp(tzname[newtm.tm_isdst], ab) != 0) {
E 2
					hunt(argv[i], t, newt);
I 2
					free(ab);
					ab = ecpyalloc(tzname[newtm.tm_isdst]);
			}
E 2
			t = newt;
			tm = newtm;
		}
		/*
		** Get highest value of t.
		*/
		t = ~((time_t) 0);
		if (t < 0)		/* time_t is signed */
			t &= ~hibit;
		t -= SECSPERHOUR * HOURSPERDAY;
		show(argv[i], t, TRUE);
		t += SECSPERHOUR * HOURSPERDAY;
		show(argv[i], t, TRUE);
	}
	if (fflush(stdout) || ferror(stdout)) {
		(void) fprintf(stderr, "%s: Error writing standard output ",
			argv[0]);
		(void) perror("standard output");
		(void) exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	for ( ; ; )
		;
}

static void
hunt(name, lot, hit)
char *	name;
time_t	lot;
time_t	hit;
{
	time_t		t;
	struct tm	lotm;
	struct tm	tm;
I 2
	char *		loab;
E 2

	lotm = *localtime(&lot);
I 2
	loab = ecpyalloc(tzname[lotm.tm_isdst]);
E 2
	while ((hit - lot) >= 2) {
		t = lot / 2 + hit / 2;
		if (t <= lot)
			++t;
		else if (t >= hit)
			--t;
		tm = *localtime(&t);
		if (delta(&tm, &lotm) == (t - lot) &&
D 2
			tm.tm_isdst == lotm.tm_isdst) {
E 2
I 2
			tm.tm_isdst == lotm.tm_isdst &&
			strcmp(tzname[tm.tm_isdst], loab) == 0) {
E 2
				lot = t;
				lotm = tm;
		} else	hit = t;
	}
	show(name, lot, TRUE);
	show(name, hit, TRUE);
I 2
	free(loab);
E 2
}

static long
delta(newp, oldp)
struct tm *	newp;
struct tm *	oldp;
{
	long	result;

	result = newp->tm_hour - oldp->tm_hour;
	if (result < 0)
		result += HOURSPERDAY;
	result *= SECSPERHOUR;
	result += (newp->tm_min - oldp->tm_min) * SECSPERMIN;
	return result + newp->tm_sec - oldp->tm_sec;
}

static void
show(zone, t, v)
char *	zone;
time_t	t;
int	v;
{
	struct tm *		tmp;
	extern struct tm *	localtime();

	(void) printf("%-*s  ", longest, zone);
	if (v)
		(void) printf("%.24s GMT = ", asctime(gmtime(&t)));
	tmp = localtime(&t);
	(void) printf("%.24s", asctime(tmp));
	if (tzname[tmp->tm_isdst] != NULL &&
		*tzname[tmp->tm_isdst] != '\0')
			(void) printf(" %s", tzname[tmp->tm_isdst]);
	if (v) {
		(void) printf(" isdst=%d", tmp->tm_isdst);
#ifdef TM_GMTOFF
		(void) printf(" gmtoff=%ld", tmp->TM_GMTOFF);
#endif /* defined TM_GMTOFF */
	}
	(void) printf("\n");
I 2
}

static char *
ecpyalloc(string)
char *	string;
{
	register char *	result;
	register int	length;

	length = strlen(string);
	result = malloc(length + 1);
	if (result == 0) {
		(void) fprintf(stderr, "%s: can't allocate memory\n", progname);
		(void) exit(EXIT_FAILURE);
	}
	(void) strcpy(result, string);
	return result;
E 2
}
E 1
