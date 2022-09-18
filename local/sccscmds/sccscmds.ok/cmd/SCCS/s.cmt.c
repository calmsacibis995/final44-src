h18442
s 00004/00000/00364
d D 4.6 88/12/22 13:03:33 sam 6 5
c satisfy external ref
e
s 00022/00011/00342
d D 4.5 88/02/02 15:55:53 bostic 5 4
c sprintf doesn't return a pointer to it's first arg, anymore
e
s 00008/00008/00345
d D 4.4 87/02/15 20:57:33 lepreau 4 3
c modern syntax for asgops & inits cause Donn's latest ccom rejects the old.
e
s 00001/00001/00352
d D 4.3 85/05/04 00:34:22 sam 3 2
c purge some of the old grotty local routines; for get add %Q% for man pages
e
s 00001/00001/00352
d D 4.2 82/03/13 16:38:48 eric 2 1
c turn magic numbers into the (already existant but unused) defined constants
e
s 00353/00000/00000
d D 4.1 81/01/15 00:16:27 eric 1 0
c date and time created 81/01/15 00:16:27 by eric
e
u
U
f b 
f i 
t
T
I 1
# include	"../hdr/defines.h"
# include	"../hdr/had.h"

D 4
SCCSID(%W%);
E 4
I 4
static char Sccsid[] = "%W%	%G%";
E 4

struct packet gpkt;
int	num_files, had_ffile;
int	F_Opened, Opened, Domrs, First;
char	*Comments, *Mrs, *ffile;
char	Cstr[BUFSIZ], Mstr[BUFSIZ], Line[BUFSIZ], had[26];
FILE	*iop, *Xiop;
D 4
static	char	ifde[]	"initial file does not exists";
E 4
I 4
static	char ifde[] = "initial file does not exists";
E 4

main(argc,argv)
int argc;
register char *argv[];
{
	register int i;
	register char *p;
	char c;
	extern cmt();
	extern int Fcnt;

	/*
	Flags for 'fatal'.
	*/
	Fflags = FTLEXIT | FTLMSG | FTLCLN;

	/*
	Process arguments.
	*/
	for (i = 1; i < argc; i++)
		if (argv[i][0] == '-' && (c = argv[i][1])) {
			p = &argv[i][2];
			switch (c) {
			case 'f':
				if (*p) {
					ffile = p;
					++had_ffile;
					if (!exists(ffile))
						fatal(ifde);
				}
				break;
			default:
				fatal("unknown key letter (cm1)");
			}
			if (had[c - 'a']++)
				fatal("key letter twice (cm2)");
			argv[i] = 0;
		}
		else num_files++;

	if(num_files == 0)
		fatal("missing file arg (cm3)");

	setsig();
	/*
	Reset flags for 'fatal' so that it will return to 'main'
	rather than exiting.
	*/
D 4
	Fflags =& ~FTLEXIT;
	Fflags =| FTLJMP;
E 4
I 4
	Fflags &= ~FTLEXIT;
	Fflags |= FTLJMP;
E 4

	/*
	Invoke 'cmt' for each file argument. 
	*/
	for (i = 1; i < argc; i++)
		if (p = argv[i])
			do_file(p,cmt);

	exit(Fcnt ? 1 : 0);
}


D 4
static char s_warn[] "WARNING: MR flag is set; `%s' should contain both MR line and comment line\n";
E 4
I 4
static char s_warn[] = "WARNING: MR flag is set; `%s' should contain both MR line and comment line\n";
E 4

D 4
static char ns_warn[] "WARNING: MR flag is not set; `%s' should only contain comment line\n";
E 4
I 4
static char ns_warn[] = "WARNING: MR flag is not set; `%s' should only contain comment line\n";
E 4

cmt(file)
register char *file;
{
	extern char had_dir, had_standinp;
	extern	char	*Sflags[];
D 2
	extern	char	Pgmr[8];
E 2
I 2
	extern	char	Pgmr[SZLNAM];
E 2
	char	line[BUFSIZ];
	int	fowner, downer, user;

	/*
	Set up to return to caller ('main') from 'fatal'.
	*/
	if (setjmp(Fjmp))
		return;

	sinit(&gpkt,file,1);	/* init packet and open file */

	if (lockit(auxf(gpkt.p_file,'z'),2,getpid()))
		fatal("cannot create lock file (cm4)");

	if (num_files > 1 || had_dir || had_standinp)
		printf("\n%s:\n",gpkt.p_file);

	First = 1;
	gpkt.p_reopen = 1;
	do_delt(&gpkt);		/* read delta table for First time */
	finduser(&gpkt);
	doflags(&gpkt);		/* get flags (see if v flag is set) */
	permiss(&gpkt);

	/*
	Check that user is either owner of file or
	directory, or is one who made the initial delta
	*/

	fstat(fileno(gpkt.p_iop),&Statbuf);
	fowner = Statbuf.st_uid & 0377;
	copy(gpkt.p_file,line);		/* temporary for dname() */
	if (stat(dname(line),&Statbuf))
		downer = -1;
	else downer = Statbuf.st_uid & 0377;
	user = getuid() & 0377;
	if (user != fowner || user != downer)
D 5
		if (!equal(Pgmr,logname()))
			fatal(sprintf(Error,
				"you are neither owner nor '%s' (rc4)",Pgmr));
E 5
I 5
		if (!equal(Pgmr,logname())) {
			sprintf(Error, "you are neither owner nor '%s' (rc4)",Pgmr);
			fatal(Error);
		}
E 5

	if ((HADF && had_ffile)) {
		if (Sflags[VALFLAG - 'a'])
			fprintf(stderr,s_warn,ffile);
		else fprintf(stderr,ns_warn,ffile);
		sleep(5);
	}
	flushto(&gpkt,EUSERTXT,1);
	gpkt.p_chkeof = 1;	/* indicate that EOF is okay */
	while (getline(&gpkt))	/* this will read body checking for cor */
		;

	gpkt.p_upd = 1;		/* x-file is to be used */
	gpkt.p_wrttn = 1;	/* prevent printing of header line */
	getline(&gpkt);		/* skip over old header record */
	gpkt.p_wrttn = 1;

	/*
	Write new header.
	*/
D 5
	putline(&gpkt,sprintf(Line,"%c%c00000\n",CTLCHAR,HEAD));
E 5
I 5
	sprintf(Line,"%c%c00000\n",CTLCHAR,HEAD);
	putline(&gpkt,Line);
E 5
	do_delt(&gpkt);		/* read delta table second time */

	flushto(&gpkt,EUSERNAM,0);
	flushto(&gpkt,EUSERTXT,0);
	while(getline(&gpkt))
		;

	flushline(&gpkt,0);	/* flush buffer, fix header, and close */
	rename(auxf(gpkt.p_file,'x'),gpkt.p_file);
	xrm(&gpkt);
	unlockit(auxf(gpkt.p_file,'z'),getpid());
	return;
}


D 4
static	char	cle[]	"comment line for initial delta already exists";
E 4
I 4
static	char cle[] = "comment line for initial delta already exists";
E 4

do_delt(pkt)
register struct packet *pkt;
{
	int	n;
D 4
	int	did_zero 0;
E 4
I 4
	int	did_zero = 0;
E 4
	struct deltab dt;
	struct stats stats;

	while(getstats(pkt,&stats)) {
		if(getadel(pkt,&dt) != BDELTAB)
			fmterr(pkt);
		if(dt.d_type == 'D' && dt.d_pred == 0) {
			copy(dt.d_pgmr,Pgmr);
			if (First)
				did_zero++;
			else {
				putline(pkt,0);
				fixintdel();
			}
		}
		while((n = getline(pkt)) != NULL)
			if (pkt->p_line[0] != CTLCHAR)
				break;
			else {
				switch(pkt->p_line[1]) {
				case EDELTAB:
					break;
				case INCLUDE:
				case EXCLUDE:
				case IGNORE:
				case MRNUM:
					continue;
				case COMMENTS:
					if (First)
						if(did_zero)
							fatal(cle);
					continue;
				default:
					fmterr(pkt);
				}
				break;
			}
		if (n ==NULL || pkt->p_line[0] != CTLCHAR)
			fmterr(pkt);
	}
	First = 0;
}


getadel(pkt,dt)
register struct packet *pkt;
register struct deltab *dt;
{
	if (getline(pkt) == NULL)
		fmterr(pkt);
	return(del_ab(pkt->p_line,dt,pkt));
}


getstats(pkt,statp)
register struct packet *pkt;
register struct stats *statp;
{
	register char *p;
	extern	char	*satoi();

	p = pkt->p_line;
	if (getline(pkt) == NULL || *p++ != CTLCHAR || *p++ != STATS)
		return(0);
	NONBLANK(p);
	p = satoi(p,&statp->s_ins);
	p = satoi(++p,&statp->s_del);
	satoi(++p,&statp->s_unc);
	return(1);
}

clean_up(n)
{
	if (gpkt.p_file[0])
		unlockit(auxf(gpkt.p_file,'z'),getpid());
	if (gpkt.p_iop)
		fclose(gpkt.p_iop);

	xrm(&gpkt);
	if (exists(auxf(gpkt.p_file,'x')))
		remove(auxf(gpkt.p_file,'x'));	/* remove x-file */
	Xiop = 0;
	if (F_Opened)
		fclose(iop);
	iop = F_Opened = Opened = 0;
	xfreeall();
}


fixintdel()
{

	register char	*p;
	register int	doprmt;
	int	tty[3];
	char	str[128];

	doprmt = 0;
	if (gtty(0,tty) >= 0)
		doprmt++;

	if (!HADF && !had_ffile) {
		Opened++;
		iop = stdin;
	}
	else if (HADF && had_ffile) {
		iop = xfopen(ffile,0);
		doprmt = 0;
		Opened++;
		F_Opened++;
	}
	else if (HADF && !had_ffile)
		doprmt = 0;

	if ((p = Sflags[VALFLAG - 'a'])) {
		if (doprmt)
			printf("MRs? ");
		if (Opened) {
			Mrs = getinput(" ",Mstr);
			mrfixup();
			if (*p && valmrs(&gpkt,p))
				fatal("invalid MRs (de9)");
			putmrs(&gpkt);
		}
D 5
		else putline(&gpkt,sprintf(Line,CTLSTR,CTLCHAR,MRNUM));
E 5
I 5
		else {
			sprintf(Line,CTLSTR,CTLCHAR,MRNUM);
			putline(&gpkt,Line);
		}
E 5
	}
	if (doprmt)
		printf("comments? ");
	if (Opened) {
D 5
		Comments = getinput(sprintf(Line,"\n%c%c ",CTLCHAR,COMMENTS),
			   Cstr);
		putline(&gpkt,sprintf(str,"%c%c ",CTLCHAR,COMMENTS));
E 5
I 5
		sprintf(Line,"\n%c%c ",CTLCHAR,COMMENTS);
		Comments = getinput(Line,Cstr);
		sprintf(str,"%c%c ",CTLCHAR,COMMENTS);
		putline(&gpkt,str);
E 5
		putline(&gpkt,Comments);
		putline(&gpkt,"\n");
	}
D 5
	else putline(&gpkt,sprintf(Line,CTLSTR,CTLCHAR,COMMENTS));
E 5
I 5
	else {
		sprintf(Line,CTLSTR,CTLCHAR,COMMENTS);
		putline(&gpkt,Line);
	}
E 5

	if (F_Opened)
		fclose(iop);
	F_Opened = Opened = 0;
}


getinput(repstr,result)
char *repstr;
char *result;
{
	char line[BUFSIZ];
	register int done, sz;
	register char *p;

	result[0] = 0;
	done = 0;
	setbuf(iop,NULL);
	sz = sizeof(line) - size(repstr);
	while (!done && fgets(line,sz,iop) != NULL) {
D 3
		p = strend(line);
E 3
I 3
		p = index(line, '\0');
E 3
		if (*--p == '\n') {
			if (*--p == '\\') {
				copy(repstr,p);
			}
			else {
				*++p = 0;
				++done;
			}
		}
		else
			fatal("line too long (co18)");
		if ((size(line) + size(result)) > RESPSIZE)
			fatal("response too long (co19)");
		strcat(result,line);
	}
	return(result);
}


putmrs(pkt)
struct packet *pkt;
{
	register char **argv;
	char str[64];
	extern char *Varg[];

D 5
	for (argv = &Varg[VSTART]; *argv; argv++)
		putline(pkt,sprintf(str,"%c%c %s\n",CTLCHAR,MRNUM,*argv));
E 5
I 5
	for (argv = &Varg[VSTART]; *argv; argv++) {
		sprintf(str,"%c%c %s\n",CTLCHAR,MRNUM,*argv);
		putline(pkt,str);
	}
E 5
}
I 6

/* Null routine to satisfy external reference from dodelt() */
escdodelt()
{}
E 6
E 1
