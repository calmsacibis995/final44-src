h47852
s 00070/00000/00000
d D 5.1 90/09/03 18:58:40 sklower 1 0
c date and time created 90/09/03 18:58:40 by sklower
e
u
U
t
T
I 1
/*
 * x25_can_callin(person)
 * x25_can_callout(person)
 *	Boolean functions for determining if `person'
 * 	can charge an incoming (login) or outgoing X.25
 *	call locally, using the file /etc/x25users.  Each line
 *	of x25users is of the form
 *		user [in|out]
 *	If "in" or "out" is given, the user may place incoming
 *	or outgoing calls only.  Otherwise, the user may place both.
 *	Lines starting with # are comments.
 */

#include <stdio.h>

#define CALL_OUT	(1<<0)	/* can charge outgoing calls locally */
#define CALL_IN		(1<<1)	/* can charge incoming calls locally */
static char Users[] = "/etc/x25users";

x25_can_callout(who)
	char *who;
{
	return (lookup(who) & CALL_OUT) != 0;
}

x25_can_callin(who)
	char *who;
{
	return (lookup(who) & CALL_IN) != 0;
}

	static int
lookup(who)
	char *who;
{
	FILE *f;
	int r;

	if ((f = fopen(Users, "r")) == NULL)
		return 0;
	r = dolookup(f, who);
	fclose(f);
	return r;
}

	static int
dolookup(f, who)
	FILE *f;
	char *who;
{
	char buf[256], name[50], arg[50];
	int n;
	
	while (fgets(buf, sizeof buf, f) != NULL) {
		if (buf[0] == '#')
			continue;
		n = sscanf(buf, "%s%s", name, arg);
		if (n < 1)
			continue;
		if (strcmp(name, who) != 0)
			continue;
		if (n == 1)
			return CALL_IN|CALL_OUT;
		if (strcmp(arg, "in") == 0)
			return CALL_IN;
		if (strcmp(arg, "out") == 0)
			return CALL_OUT;
	}
	return 0;
}
E 1
