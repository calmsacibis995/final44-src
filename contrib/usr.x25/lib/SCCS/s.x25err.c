h43033
s 00087/00000/00000
d D 5.1 90/09/03 18:58:41 sklower 1 0
c date and time created 90/09/03 18:58:41 by sklower
e
u
U
t
T
I 1
#include <netccitt/x25err.h>

extern	int errno, sys_nerr;
extern	char *sys_errlist[];

char *
x25err(who)
char *who;
{
	register char *ep, *bp;
	static char buf[80];

	switch(errno) {
	case EXRESET:
		ep = "Call reset";
		break;

	case EXROUT:
		ep = "Reset - out of order";
		break;

	case EXRRPE:
		ep = "Reset - remote procedure error";
		break;

	case EXRLPE:
		ep = "Reset - local procedure error";
		break;

	case EXRNCG:
		ep = "Reset - network congestion";
		break;

	case EXCLEAR:
		ep = "Clear - remote directive";
		break;

	case EXCBUSY:
		ep = "Clear - number is busy";
		break;

	case EXCOUT:
		ep = "Clear - out of order";
		break;

	case EXCRPE:
		ep = "Clear - remote procedure error";
		break;

	case EXCRRC:
		ep = "Clear - collect call refused";
		break;

	case EXCINV:
		ep = "Clear - invalid call";
		break;

	case EXCAB:
		ep = "Clear - access barred";
		break;

	case EXCLPE:
		ep = "Clear - local procedure error";
		break;

	case EXCNCG:
		ep = "Clear - network congestion";
		break;

	case EXCNOB:
		ep = "Clear - not obtainable";
		break;

	default:
		ep = errno >= 0 && errno < sys_nerr ?
			sys_errlist[errno] : "Unknown error";
	}
	bp = buf;
	if (who) {
		while (bp < buf+sizeof (buf)-2-1 && (*bp++ = *who++));
		bp[-1] = ':';
		*bp++ = ' ';
	}
	while (bp < buf+sizeof (buf)-1 && (*bp++ = *ep++));
	*bp++ = '\0';
	return (buf);
}
E 1
