h18001
s 00000/00000/00091
d D 8.1 93/06/06 16:08:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00086
d D 1.3 91/04/16 14:45:27 bostic 3 2
c new copyright; att/bsd/shared
e
s 00004/00001/00083
d D 1.2 83/08/11 21:00:15 sam 2 1
c standardize sccs keyword lines
e
s 00084/00000/00000
d D 1.1 82/12/15 21:46:24 clemc 1 0
c date and time created 82/12/15 21:46:24 by clemc
e
u
U
t
Original BTL Ratfor System for 4.2
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

E 2
#include "r.h"

int	swlevel	= -1;
int	swexit[5];
int	nextcase[5];

swcode() {
	transfer = 0;
	putcom("switch");
	swlevel++;
	if (swlevel >= 5)
		error("Switches nested > 5");
	swexit[swlevel] = yyval = genlab(1);
	outcode("\tI");
	outnum(yyval);
	outcode(" = ");
	balpar();
	outdon();
	nextcase[swlevel] = 0;
	indent++;
}

getcase() {
	int t, lpar;
	char token[100];

	if (nextcase[swlevel] != 0) {
		outgoto(swexit[swlevel]);
		outcont(nextcase[swlevel]);
	}
	indent--;
	outcode("\tif(.not.(");
	do {
		outcode("I");
		outnum(swexit[swlevel]);
		outcode(".eq.(");
		lpar = 0;
		do {
			if ((t=gtok(token)) == ':')
				break;
			if (t == '(')
				lpar++;
			else if (t == ')')
				lpar--;
			else if (t == ',') {
				if (lpar == 0)
					break;
				}
			outcode(token);
		} while (lpar >= 0);
		if (lpar < 0)
			error("Missing left parenthesis in case");
		if (t == ',')
			outcode(").or.");
	} while (t != ':');
	if (lpar != 0)
		error("Missing parenthesis in case");
	outcode(")))");
	nextcase[swlevel] = genlab(1);
	outgoto(nextcase[swlevel]);
	indent++;
}

getdefault() {
	char token[20];
	if (gnbtok(token) != ':')
		error("Missing colon after default");
	outgoto(swexit[swlevel]);
	outcont(nextcase[swlevel]);
	indent--;
	putcom("default");
	indent++;
}

endsw(n, def) {
	if (def == 0)
		outcont(nextcase[swlevel]);
	swlevel--;
	if (swlevel < -1)
		error("Switches unwound too far");
	indent--;
	outcont(n);
}
E 1
