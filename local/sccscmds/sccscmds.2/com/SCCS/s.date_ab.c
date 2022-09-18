h11256
s 00001/00001/00106
d D 4.6 89/05/10 22:42:40 bostic 6 5
c fix year length defines for tzfile.h
e
s 00004/00000/00103
d D 4.5 87/10/06 19:12:58 bostic 5 4
c fix removal of dysize() from C library
e
s 00014/00014/00089
d D 4.4 87/02/15 16:42:21 lepreau 4 3
c modern syntax for asgops & inits; sccs keywords
e
s 00002/00001/00101
d D 4.3 85/05/03 23:38:12 sam 3 2
c build in day-month table from ctime to avoid local ctime
e
s 00001/00001/00101
d D 4.2 81/01/28 10:52:48 eric 2 1
c fix timezone calculation
e
s 00102/00000/00000
d D 4.1 81/01/15 13:47:30 eric 1 0
c date and time created 81/01/15 13:47:30 by eric
e
u
U
f b 
f i 
t
T
I 1
# include	"../hdr/macros.h"
I 5
# include	<tzfile.h>
E 5

D 4
SCCSID(%W%);
E 4
I 4
static char Sccsid[] = "%W%	%G%";
E 4

/*
	Function to convert date in the form "yymmddhhmmss" to
	standard UNIX time (seconds since Jan. 1, 1970 GMT).
	Units left off of the right are replaced by their
	maximum possible values.

	The function corrects properly for leap year,
	daylight savings time, offset from Greenwich time, etc.

	Function returns -1 if bad time is given (i.e., "730229").
*/
I 5

D 6
#define	dysize(year)	(isleap(year) ? DAYS_PER_LYEAR : DAYS_PER_NYEAR)
E 6
I 6
#define	dysize(year)	(isleap(year) ? DAYSPERLYEAR : DAYSPERNYEAR)
E 6

E 5
char *Datep;


date_ab(adt,bdt)
char *adt;
long *bdt;
{
	int y, t, d, h, m, s, i;
	long tim;
	extern int *localtime();
#define	time_t	long
#include <sys/timeb.h>
	struct timeb timeb;

	ftime(&timeb);
	Datep = adt;

	if((y=g2()) == -2) y = 99;
	if(y<70 || y>99) return(-1);

	if((t=g2()) == -2) t = 12;
	if(t<1 || t>12) return(-1);

	if((d=g2()) == -2) d = mosize(y,t);
	if(d<1 || d>mosize(y,t)) return(-1);

	if((h=g2()) == -2) h = 23;
	if(h<0 || h>23) return(-1);

	if((m=g2()) == -2) m = 59;
	if(m<0 || m>59) return(-1);

	if((s=g2()) == -2) s = 59;
	if(s<0 || s>59) return(-1);

	tim = 0L;
D 4
	y =+ 1900;
E 4
I 4
	y += 1900;
E 4
	for(i=1970; i<y; i++)
D 4
		tim =+ dysize(i);
E 4
I 4
		tim += dysize(i);
E 4
	while(--t)
D 4
		tim =+ mosize(y,t);
	tim =+ d - 1;
	tim =* 24;
	tim =+ h;
	tim =* 60;
	tim =+ m;
I 2
	tim =+ timeb.timezone;			/* GMT correction */
E 2
	tim =* 60;
	tim =+ s;
E 4
I 4
		tim += mosize(y,t);
	tim += d - 1;
	tim *= 24;
	tim += h;
	tim *= 60;
	tim += m;
	tim += timeb.timezone;			/* GMT correction */
	tim *= 60;
	tim += s;
E 4

D 2
	tim =+ timeb.timezone;			/* GMT correction */
E 2
	if(localtime(&tim)[8])
D 4
		tim =+ -1*60*60;		/* daylight savings */
E 4
I 4
		tim += -1*60*60;		/* daylight savings */
E 4
	*bdt = tim;
	return(0);
}


mosize(y,t)
int y, t;
{
D 3
	extern int dmsize[];
E 3
I 3
	static	int dmsize[12] =
	    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
E 3

	if(t==2 && dysize(y)==366) return(29);
	return(dmsize[t-1]);
}


g2()
{
	register int c;
	register char *p;

	for (p = Datep; *p; p++)
		if (numeric(*p))
			break;
	if (*p) {
		c = (*p++ - '0') * 10;
		if (*p)
D 4
			c =+ (*p++ - '0');
E 4
I 4
			c += (*p++ - '0');
E 4
		else
			c = -1;
	}
	else
		c = -2;
	Datep = p;
	return(c);
}
E 1
