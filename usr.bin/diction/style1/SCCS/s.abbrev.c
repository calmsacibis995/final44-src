h12621
s 00000/00000/00072
d D 8.1 93/06/06 14:34:09 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00004/00070
d D 4.4 91/04/27 16:33:15 bostic 5 4
c all of the .c's are really .h's...
e
s 00006/00002/00068
d D 4.3 91/04/17 17:15:30 bostic 4 3
c new copyright; att/bsd/shared
e
s 00070/00000/00000
d D 4.2 82/11/06 16:58:27 rrh 3 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00070/00000/00000
d R 4.2 82/11/06 16:30:44 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00000/00000/00000
d D 4.1 82/11/06 16:29:58 rrh 1 0
c Not used in oldest version available at Berkeley
e
u
U
t
T
I 4
/*-
 * %sccs.include.proprietary.c%
I 5
 *
 *	%W% (Berkeley) %G%
E 5
 */
D 5

E 4
I 3
#ifndef lint
D 4
static char abbrev_sccsid[] = "%W%	(Berkeley)	%E%";
#endif not lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5
E 4

struct dict abbrev_d[] = {
"St",'N',
"Dr",'N',
"Drs",'N',
"Mr",'N',
"Mrs",'N',
"Ms",'N',
"Rev",'N',
"No",'Y',
"Nos",'Y',
"NO",'Y',
"NOs",'Y',
"no",'Y',
"Fig",'Y',
"Figs",'Y',
"Dept",'Y',
"Depts",'Y',
"dept",'Y',
"depts",'Y',
"Eq",'Y',
"Eqs",'Y',
"eq",'Y',
"eqs",'Y',
"dB",'Y',
"vs",'P',
"in",'Y',
"ft",'Y',
"yr",'Y',
"ckts",'Y',
"mi",'Y',
"Jr",'J',
"jr",'J',
"Ch",'Y',
"ch",'Y',
"Ref",'Y',
"Refs",'Y',
"ref",'Y',
"refs",'Y',
"Inc",'J',
"Co",'N',
"Corp",'N',
"Jan",'N',
"Feb",'N',
"Mar",'N',
"Apr",'N',
"Jun",'N',
"Aug",'N',
"Sept",'N',
"Oct",'N',
"Nov",'N',
"Dec",'N',
"Sen",'Y',
"Sens",'Y',
"Rep",'Y',
"Hon",'Y',
"Gov",'Y',
"Lt",'Y',
"Col",'Y',
"Comdr",'Y',
"Cmdr",'Y',
"Capt",'Y',
"Calif",'N',
"Ky",'N',
"Va",'N',
0,0
};
E 3
I 1
E 1
