h38520
s 00004/00004/00169
d D 1.3 88/03/23 19:34:05 jaap 3 2
c Ugly fix to generate same output again, a sun is like a tahoe...
e
s 00038/00004/00135
d D 1.2 88/03/18 17:48:51 jaap 2 1
c fixes for tahoe
e
s 00139/00000/00000
d D 1.1 88/03/18 17:45:31 jaap 1 0
c date and time created 88/03/18 17:45:31 by jaap
e
u
U
t
T
I 1
/*
 * lowest level io
 *
 * The Harris has a weird protocol, which wil be maintained by
 * a different programme (now called harprot, will be changed into
 * a typesetter spooler in near future).
 *
 * Due to thenature of the harris is a slight protocol to harprot
 * necessary as well:
 *	Operator messages are ruined if they aren't at the end of a buffer
 *
 * So to harprot we send a buffer with a header containing a bufferlenght
D 2
 * and (for histrorical reasons, the amount of paper used.)
E 2
I 2
 * and (for historical reasons, the amount of paper used.)
E 2
 * The paper use will have to be counted by harprot in future.
 *
I 2
D 3
#ifdef tahoe
E 3
I 3
#if tahoe || sun
E 3
 * For the sake of compbatibilty we will generate the same file format
 * as on the vaxes
D 3
#endif tahoe
E 3
I 3
#endif tahoe || sun
E 3
 *
E 2
 */

I 2
#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif

E 2
#include <stdio.h>
#include "hcodes.h"
#include "llio.h"

char	obuf[BUFSIZE];
char	*obufp = obuf;
char	*eobufp = &obuf[BUFSIZE-1];
int	typeset;	/* if set, we are really typesetting */

extern int	fcut;	/* if set, we have just cut the paper */
D 2
extern int	papuse;	/* used paper in feed */
E 2
I 2
extern unsigned	short	papuse;	/* used paper in feed */
E 2
extern int	tf;
extern char	harcode;
extern int	eflag;


oput( c )
char	c;
{
	typeset = 1;

	if( fcut ) {		/* See harris manual, appendix D */
		fcut = 0;
		oput(VMV);
		oput(0);
		oput(0);
	}
	if( obufp > eobufp)
		flusho();
	*obufp++ = c & BMASK;
}

flusho()
D 2
{	int length, i;
E 2
I 2
{	unsigned short length;
	int i;
E 2
	if ( length = (int )(obufp - obuf )) {
		if ( !papuse )
			papuse++;	/* account always at least 1 foot */
		/* for testing only */
		/*papuse = 1;*/
I 2
#ifdef vax
E 2
		if ( write( tf, (char *)&length, 2) != 2 ||
		     write( tf, (char *)&papuse, 2) != 2 ||
D 2
		     (i = write( tf, obuf, length)) <= 0) {
E 2
I 2
		     (i = write( tf, obuf, length)) != length) {
E 2
			printf("dhar: write error\n");
			exit(1);
		}
I 2
#endif vax
D 3
#ifdef tahoe
E 3
I 3
#if tahoe || sun
E 3
		{	char c1, c2;
			c1 = length & BMASK;
			c2 = (length >> 8) & BMASK;
			if( write(tf, &c1, 1) != 1 ||
			    write(tf, &c2, 1) != 1) {
				printf("dhar: write error\n");
				exit(1);
			}
			c1 = papuse & BMASK;
			c2 = (papuse >> 8) & BMASK;
			if( write(tf, &c1, 1) != 1 ||
			    write(tf, &c2, 1) != 1) {
				printf("dhar: write error\n");
				exit(1);
			}
			if((i = write( tf, obuf, length)) != length) {
				printf("dhar: write error\n");
				exit(1);
			}
		}
D 3
#endif tahoe
E 3
I 3
#endif tahoe || sun
E 3
E 2
		obufp = obuf;
	}
}

xflusho(nbytes)
int nbytes;
{
	if ( obufp > &obuf[BUFSIZE - nbytes])
		flusho();
}

flushchar()
{
	if( harcode ) {
		oput(harcode);
		oput(0); oput(0);
		harcode = 0;
	}
}

ex()
{	if(!typeset)
		return;
	if(!fcut)
		cut();
	fcut = 0;
	oput(EOT);
	oput(STP);
	operator("End of job");
	typeset = 0;
	if(eflag) {
		fprintf( stderr, "Don't forget to bring the machine");
		fprintf( stderr, " back in a normal state\n");
		eflag--;
	}
}

operator( s )
char	*s;
{	register int i, j, n;
	char buf[PANEL_SIZE];	
	n = 0;
	while ( *s ) {		/* ascii from harris, stupid fools */
		if( *s >= 'a' && *s <= 'z')
			*s += 'A' - 'a';
		if(*s == '{')
			*s = 0136;
		if(*s == '}')
			*s = 0137;
		if( *s < 040 || *s > 0137) {
			error( !FATAL, "illegal char %o to display", *s);
			s++;
			continue;
		}
		buf[n++] = *s++;
		if( n >= PANEL_SIZE)
			break;
	}
	/*
	 * now center the message and send it away
	 */
	if( n <= PANEL_SIZE && n > 0) {
		flusho(PANEL_SIZE + 1);
			/*
			 * always flushing the buffer seems to be better
			 */
		oput(OPR);
		i = ( PANEL_SIZE - n ) / 2;
		for( j = 0; j < i; j++)
			oput(' ');
		for( j = 0; j < n; j++)
			oput(buf[j]);
		for( j = i + n; j < PANEL_SIZE; j++)
			oput(' ');
		flusho();
	}
}
E 1
