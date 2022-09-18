h20907
s 00004/00007/00109
d D 1.2 85/10/02 14:39:35 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00116/00000/00000
d D 1.1 85/10/01 18:09:27 jaap 1 0
c date and time created 85/10/01 18:09:27 by jaap
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint

D 2

 /* tg.c: process included text blocks */

E 2
#include "defs.h"
#include "ext.h"

/*
 * Get a section of text
I 2
 *
 * Note that this doen't work after MAXLIN lines (see over200.c)
 *
E 2
 */

/*
 * This returns an int with the name of the diversion,
 * in maktab we test later in wide() whether the table entry is a
 * pointer to a string, or a character.
 * If it is a character, we now it is a diversion, and know it its width
 * to be in <diversionname>-
 *
 * Very ugly, (looks like we need unions in declaration of structure colstr ?)
 */

gettext(sp, ilin, icol, fn, sz)
char *sp, *fn, *sz;
{
	char line[BUFSIZ];
	char *vs;
	int oname;

D 2
printf(".\\\" -- gettext\n");
E 2
I 2
	dprint(".\\\" -- gettext\n");
E 2
	if(texname == 0)
		error("Too many text block diversions");
	if(textflg == 0){
		printf(".nr %d \\n(.lu\n", SL);
 		/*
		 * remember old line length
		 */
		textflg = 1;
	}
	printf(".eo\n");
	printf(".am %2s\n", reg(icol, CRIGHT));
	printf(".br\n");
	printf(".di %c+\n", texname);
	rstofill();
	if(fn && *fn)
		printf(".nr %d \\n(.f\n.ft %s\n", S1, fn);
	/*
	 * protect font
	 */
	printf(".ft \\n(.f\n");
	vs = vsize[stynum[ilin]][icol];
	if((sz && *sz) || (vs && *vs)){
		printf(".nr %d \\n(.v\n", S2);
		if(vs == 0 || *vs == 0)
			vs = "\\n(.s+2";
		if(sz && *sz)
			printf(".ps %s\n", sz);
		printf(".vs %s\n", vs);
		printf(".if \\n(%du>\\n(.vu .sp \\n(%du-\\n(.vu\n",
									S2, S2);
	}
	if(cll[icol][0])
		printf(".ll %sn\n", cll[icol]);
	else
		printf(".ll \\n(%du*%du/%du\n", SL, ctspan(ilin, icol),
								ncol + 1);
	printf(".if \\n(.l<\\n(%2s .ll \\n(%2su\n", reg(icol, CRIGHT),
							reg(icol, CRIGHT));
	if(ctype(ilin, icol) == 'a')
		printf(".ll -2n\n");
	printf(".in 0\n");
	while(gets1(line)){
		if(line[0] == 'T' && line[1] == '}' && line[2] == tab)
			break;
		if(strcmp("T}", line) == 0)
			break;
		printf("%s\n", line);
	}
	if(fn && *fn)
		printf(".ft \\n(%d\n", S1);
	if(sz && *sz)
		printf(".br\n.ps\n.vs\n");
	printf(".br\n");
	printf(".di\n");
	/*
	 * Height of last complete diversion in register <diversionname>|
	 */
	printf(".nr %c| \\n(dn\n", texname);
	/*
	 * width of last complete diversion in register <diversionname>-
	 */
	printf(".nr %c- \\n(dl\n", texname);
	printf("..\n");
	printf(".ec \\\n");
	/*
	 * copy remainder of line
	 */
	if(line[2])
		strcpy(sp, line + 3);
	else
		*sp = 0;
	oname = texname;
	texname = texstr[++texct];
D 2
/*
printf(".\\\"gettext returns oname, oneme is: %c\n", oname);
*/
E 2
	return(oname);
}

untext(){
	rstofill();
	printf(".nf\n");
	printf(".ll \\n(%du\n", SL);
}
E 1
