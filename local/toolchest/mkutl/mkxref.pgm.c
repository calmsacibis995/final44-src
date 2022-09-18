/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*                                                                  
 *
 * mkxref --- reports on functions performed by makefiles
 *
 */
#include	<stdio.h>
#include	<string.h>

extern void exit();

#define MAXLEN 1024

char	assembler[]="AS";
char	binary[]="BN";
char	binval[]="/bin";
int	cmdsw=0;
char	cmdval[] = "COMMAND:";
char	cond[]="!";
char	clr[]=" ";
char	clib[]="/lib/libc.a";
char	debug='0';
char	del[]="d";
char	dir[80];
int	dsw;
char	etcval[]="/etc";
char	file[MAXLEN];
char	fmode[5]="";
char	fgrp[10]="";
char	fown[10]="";
int	fpos;
char	*ftype;
char	home[80];
char	includes[]="IN";
char	*ioflag;
int	len;
char	lib1[]="/lib/lib";
char	lib2[]=".a";
char	library[]="LB";
char	libval[]="/lib";
char	line[MAXLEN];
char	mk[]="MK";
char	manpath[]="/usr/catman";
char	manual[]="MN";
char	manval[]="MANUAL:";
char	path[80];
char	psw='0';
char	rd[]="r";
char	source[]="SR";
char	script[]="SS";
char	st[]="*";
char	wr[]="w";
char	ubinval[]="/usr/bin";
char	ulibval[]="/usr/lib";
char	unknown[]=" ";
char	ulib1[]="/usr/lib/lib";
int	warning;
char	*wflag;

main(argc,argv)
int	argc;
char	*argv[];
{
int	rc;

	if (argc==1 || argc>4) {
		fprintf(stderr, "usage: mkxref path [print] [debug]\n");
		fprintf(stderr, "       print=1 prints detail\n");
		fprintf(stderr, "       print=0 prints NO detail\n");
		fprintf(stderr, "       debug=0 debugging OFF\n");
		fprintf(stderr, "       debug=1 PARTIAL debugging ON\n");
		fprintf(stderr, "       debug=2 FULL debugging ON\n");
		exit(1);
	}
	ftype=clr;
	ioflag=clr;
	strcpy(path, argv[1]);
	strcpy(home, path);
	if (argc>2) psw=argv[2][0];
	if (argc>3) debug=argv[3][0];
	if (debug!='0') printf("Debugging level:%c\n",debug);
	wflag=clr;
	for (;(len=getline())>0;) {
		if (debug!='0') printf("%s\n",line);
		if ((rc = ckman()) != 0) {
			if ((rc=ckcmd())!=0) {
		        	warning=noifs();
				if (debug=='2') printf("WARNING:%d\n",warning);
				if (warning==1) wflag=cond;
				scancmd();
			}
		}
	}
	exit(0);
}
/*
 *
 * GETLINE --- Reads a line of input.
 *             The following RULES are observed:
 *
 *           o Any string enclosed within (`) is ignored.
 * 
 *           o Any string enclosed within ([]) is ignored.
 *
 *           o All TABS are ignored.
 *
 *           o A  ';' is equivalent to a '\n'.
 *
 *           o All characters from a '#' to a '\n' are
 *             considered to be comments and are not placed in
 *             LINE.
 *
 *           o If a '\n' is found in the first position of a line,
 *             it is removed (NO null lines are returned).
 *
 *           o Lines may be continued by ESCAPING the '\n' with a '\'.
 *
 */
getline()
{
int	i, c=0, sw=0, ignore;

	if (debug=='2') printf("ENTERING GETLINE\n");
	line[0]='\0';
	for (i=0; sw==0 && c!=-1 && i>=0; ) {
		ignore=0;
		c=getchar();
		if (c==';') c='\n';
		if (c=='|') c='\n';
		if (c=='^') c='\n';
		if (c==' ' && i==0) ignore=1;
		if (c=='`') {
			ignore=1;
			for (; (c=getchar())!='`' && c!='\n' && c!=-1; );
			if (c=='\n') sw=1;
		}
		if (c=='[') {
			ignore=1;
			for (; (c=getchar())!=']' && c!='\n' && c!=-1; );
			if (c=='\n') sw=1;
		}
		if (c=='\t') ignore=1;
		if (c=='#') for (; (c=getchar())!=';' && c!='\n' && c!=-1;);
		if (c==';') c='\n';
		if (c==-1) {
			sw=1;
			ignore=1;
		}
		if (i==0 && c=='\n') ignore=1;
		if (c=='\n' && i>0) {
			sw=1;
			if (line[i-1]=='\\') {
				ignore=1;
				sw=0;
				i=i-1;
			}
		}
		if(c!='\n' && !ignore) line[i++]=c;
	}
	if (i<0) i=0;
	line[i]='\0';
	if (debug=='2') printf("EXITING GETLINE RC=%d\n",i);
	return(i);
}
/*                                                                  
 *
 * CKCMD --- checks for line=COMMAND:
 *
 */
ckcmd()
{
int	rc=1, i, j;
char	cmd[20];

	if (debug=='2') printf("ENTERING CKCMD\n");
	if ((rc=strncmp(line, cmdval, strlen(cmdval)))==0) {
		for (i=0; i<10; ++i) cmd[i]=' ';
		cmd[i]='\0';
		for (i=9; line[i]!='.' && line[i]!='\0'; ++i) {
			j=i-9;
			cmd[j] = line[i];
		}
	printf("\n\n\n%s\n",cmd);
	}
	if (debug=='2') printf("EXITING CKCMD\n");
	return(rc);
}
/*                                                                  
 *
 * CKBIN --- checks for file prefixed by /bin
 *    returns 0 no match, 1 match
 *
 */
ckbin()
{
int	rc;

	if (debug=='2') printf("ENTERING CKBIN\n");
	rc=strncmp(file, binval, strlen(binval));

	if (rc==0) rc=1;
	else rc=0;
	
	if (debug=='2') printf("EXITING CKBIN RC=%d\n",rc);
	return(rc);
}
/*                                                                  
 *
 * CKUBIN --- checks for file prefixed by /usr/bin
 *    returns 0 no match, 1 match
 *
 */
ckubin()
{
int	rc;

	if (debug=='2') printf("ENTERING CKUBIN\n");
	rc=strncmp(file, ubinval, strlen(ubinval));
	
	if (rc==0) rc=1;
	else rc=0;
	
	if (debug=='2') printf("EXITING CKUBIN RC=%d\n",rc);
	return(rc);
}
/*
 *
 * SCANCMD scans for commands of interest
 *
 */
scancmd()
{
int	rc=0;
	
	if (debug=='2') printf("ENTERING SCANCMD\n");
	nopath();
	if ((rc=strncmp(line, "cc ", 3))==0) scancc();
	if ((rc=strncmp(line, "cd", 2))==0) cd();
	if ((rc=strncmp(line, "chgrp ", 6))==0) dochgrp();
	if ((rc=strncmp(line, "chown ", 6))==0) dochown();
	if ((rc=strncmp(line, "chmod ", 6))==0) dochmod();
	if ((rc=strncmp(line, "cp ", 3))==0) cpfile();
	if ((rc=strncmp(line, "fi", 2))==0) wflag=clr;
	if ((rc=strncmp(line, "install ", 8))==0) install();
	if ((rc=strncmp(line, "ld ", 3))==0) scancc();
	if ((rc=strncmp(line, "ln ", 3))==0) scancc();
	if ((rc=strncmp(line, "make ", 5))==0) make();
	if ((rc=strncmp(line, "rm ", 3))==0) rmfile();
	if (debug=='2') printf("EXITING SCANCMD RC=%d\n",rc);
	return;
}
/*
 *
 * RMFILE --- Handles REMOVE commands
 *
 */
rmfile()
{
int	rc=0, i;

	if (debug=='2') printf("ENTERING RMFILE\n");
	prcmd();
	
	for (i=0; (rc=getlast(i))!=0; ++i) {
		ioflag=del;
		detail();
	}
	if (debug=='2') printf("EXITING RMFILE\n");
	return;
}
/*
 *
 * CPFILE --- Handles COPY commands
 *
 */
cpfile()
{
int	suffrc, i;

	if (debug=='2') printf("ENTERING CPFILE\n");
	prcmd();
	for (i=0; (suffrc=getlast(i))!=0; ++i) {
		ioflag=rd;
		if (i==0) ioflag=wr;
		detail();
		if (debug=='2') printf("EXITING CPFILE\n");
	}
	return;
}
/*
 *
 * SCANCC --- processes CC, LD, LN commands
 *
 */
scancc()
{
int	i, rc;
char	hold[MAXLEN];
char	*hflag;

	if (debug=='2') printf("ENTERING SCANCC\n");
	prcmd();
	if (getarg('o')) {
		ioflag=wr;
		ftype=binary;
		detail();
	}
	if (getarg('I')) {
		ioflag=rd;
		ftype=includes;
		detail();
	}
	
	if (getarg('l')) {
		if (file[0]=='\0') {
			strcpy(file, clib);
			ioflag=rd;
			ftype=library;
			detail();
			getarg('l');
		}
	
		if (file[0]!='\0') {    
			strcpy(hold, lib1);
			strcat(hold, file);
			strcat(hold, lib2);
			strcpy(file, hold);
			ioflag=rd;
			ftype=library;
			detail();
			getarg('l');
			strcpy(hold, ulib1);
			strcat(hold, file);
			strcat(hold, lib2);
			strcpy(file, hold);
			hflag=wflag;
			wflag=cond;
			ioflag=rd;
			ftype=library;
			detail();
			wflag=hflag;
		}
	}
	/* get input (may be source or bin ) files */
	for (i=0; (rc=getlast(i)); ++i) {
		ioflag=rd;
		if (line[0]=='l') {
			ftype=binary;
			if (line[1]=='n' && i==0) ioflag=wr;
		}
		detail();
	}
	
	if (debug=='2') printf("EXITING SCANCC\n");
	return;
}
/*
 *
 * NOIFS --- remove IF and THEN and optionally ELSE from LINE
 *
 *    RETURNS: 0 - no change
 *             1 - IF...THEN removed
 *
 */
noifs()
{
int	rc=0, i;
char	hold[MAXLEN];

	if (debug=='2') printf("ENTERING NOIFS\n");
	if ((rc=strncmp(line, "else", 4))==0) rc=1;
	if ((rc=strncmp(line, "then", 4))==0) rc=1;
	if (rc==1) {
		for (i=4; line[i]==' ' && line[i]!='\0'; ++i);
		strcpy(hold, line+i);
		strcpy(line, hold);
	}
	
	if (debug=='2') printf("EXITING NOIFS RC=%d\n",rc);
	return(rc);
}
/*
 *
 * DETAIL --- Prints a DETAIL line for report
 *
 */
detail()
{
int	bin, suffrc;

	if (debug=='2') printf("ENTERING DETAIL\n");
	if (cmdsw==0) setpath();
	if (ftype==clr) {
		bin=ckbin();
		if (!bin) bin=ckubin();
		if (bin) ftype=binary;
		suffrc=suffix();
		if (bin==0 && suffrc==0) ftype=unknown;
	}
	if (cmdsw) printf("%1s%s\n", " ", file);
	else printf("%1s%-50s%-5s%-9s%-9s%-3s%-1s%s\n", " ", file, fmode,fown, fgrp, ftype, ioflag, wflag);
	
	ftype=clr;
	fmode[0] = '\0';
	fgrp[0] = '\0';
	fown[0] = '\0';
	ioflag=clr;
	if (debug=='2') printf("EXITING DETAIL\n");
	return;
}
/*
 *
 * SETPATH --- Converts FILE to FULL PATH NAME
 *
 */
setpath()
{
int	i;
char	hold[MAXLEN];

	if (debug=='2') printf("ENTERING SETPATH\n");
	if ((file[0]=='.' && file[1]=='/') || file[0]!='/') {
		i=0;
		if (file[0]=='.' && file[1]=='/') i=2;
		
		if (dsw==0) strcpy(hold, path);
			else
			strcpy(hold, dir);
		
		strcat(hold, "/");
		strcat(hold, file+i);
		strcpy(file, hold);
	}
	dsw=0;
	if (debug=='2') printf("EXITING SETPATH\n");
	return;
}
/*
 *
 * CD --- Updates PATH from CD command
 *
 */
cd()
{
int	rc;
char	*ptr, hold[MAXLEN];

	if (debug=='2') printf("ENTERING CD\n");
	prcmd();
	if ((rc=getlast(0))!=0) {
		/* Handle ./file here */
		while ((rc=strncmp(file,"./",2))==0) {
			strcpy(hold,file+2);
			strcpy(file, hold);
		}
		/* Handle ../file here */
		while ((rc=strncmp(file,"../",3))==0) {
			if((ptr=strrchr(path,'/'))!=NULL) {
				*ptr='\0';
				strcpy(hold,file+3);
				strcpy(file, hold);
			}
			else {
				printf("ERROR: Attempt to cd beneath ROOT.\n       Stopped at ROOT.\n");
				return;
			}
		}
		/* Handle .. here */
		if ((rc=strcmp(file,".."))==0) {
			if ((ptr=strrchr(path,'/'))!=NULL) *ptr='\0';
			else printf("ERROR: Attempt to cd beneath ROOT.\n       Stopped at ROOT.\n");

			return;
		}
		/* Handle . here */
		if ((rc=strcmp(file,"."))==0) return;
	
		/* Handle /file here */
		if (file[0]=='/') strcpy(path, file);
		else {
			strcat(path,"/");
			strcat(path,file);
		}
	}
	/* Handle Null file */
	else strcpy(path,home);
				
	if (debug=='2') printf("EXITING CD\n");
	return;
}
/*
 *
 * INSTALL --- Handles INSTALL commands
 *
 */
install()
{
char	*hflag;
int	i, rc, nsw=0, dfsw=1;

	if (debug=='2') printf("ENTERING INSTALL\n");
	prcmd();
	if (getarg('m')) strcpy(fmode, file);
	if (getarg('g')) strcpy(fgrp, file);
	if (getarg('u')) strcpy(fown, file);

	if (getarg('c')) {
		strcpy(dir, file);
		dsw=1;
	}
	if (getarg('f')) {
		strcpy(dir, file);
		dsw=1;
	}
	if (getarg('n')) {
		strcpy(dir, file);
		dsw=1;
		nsw=1;
	}
	if (dsw) dfsw=0;
	for (i=0; (rc=getlast(i))==1; ++i);
	fpos=i-1;
	rc=getlast(fpos);
	
	if (rc==1) {
		if (dsw) {
			ioflag=wr;
			if (nsw) {
			   hflag=wflag;
			   wflag=cond;
			}
			ftype=binary;
			getlast(fpos);
			detail();
			if (nsw) wflag=hflag;
		}
		ioflag=rd;
		ftype=binary;
		getlast(fpos);
		detail();
	}
	for (i=fpos-1; i>=0 && (rc=getlast(i))==1; --i) {
		 ioflag=wr;
		 ftype=binary;
		 hflag=wflag;
		 wflag=cond;
		 strcpy(dir, file);
		 dsw=1;
		 getlast(fpos);
		 detail();
		 wflag=hflag;
	}
	if (dfsw && fpos==0 && (rc=getarg('i'))==0) {
		hflag=wflag;
		wflag=cond;
		strcpy(dir, binval);
		dsw=1;
		ioflag=wr;
		ftype=binary;
		getlast(fpos);
		detail();
		strcpy(dir, ubinval);
		dsw=1;
		ioflag=wr;
		ftype=binary;
		getlast(fpos);
		detail();
		strcpy(dir, etcval);
		dsw=1;
		ioflag=wr;
		ftype=binary;
		getlast(fpos);
		detail();
		strcpy(dir, libval);
		dsw=1;
		ioflag=wr;
		ftype=binary;
		getlast(fpos);
		detail();
		strcpy(dir, ulibval);
		dsw=1;
		ioflag=wr;
		ftype=binary;
		getlast(fpos);
		detail();
		wflag=hflag;
	}
	if (debug=='2') printf("EXITING INSTALL\n");
	return;
}
/*
 *
 * SUFFIX --- checks file names for suffixes.
 *            a = LIB
 *            c = SRC
 *            o = BIN
 *            s = ASM
 *           mk = MAKE
 *          out = BIN
 *           sh = SHELL SCRIPT
 *
 */
suffix()
{
int	i, rc=0;

	if (debug=='2') printf("ENTERING SUFFIX\n");
	for (i=0; file[i]!='\0'; ++i);
	for (--i; file[i]!='.' && file[i]!=' ' && i>0; --i);
	if (file[i]=='.') {
		if ((rc=strcmp(file+i+1, "a"))==0) {
			rc=1;
			ftype=library;
		}
		if ((rc=strcmp(file+i+1, "c"))==0) {
			rc=1;
			ftype=source;
		}
		if ((rc=strcmp(file+i+1, "mk"))==0) {
			rc=1;
			ftype=mk;
		}
		if ((rc=strcmp(file+i+1, "out"))==0) {
			rc=1;
			ftype=binary;
		}
		if ((rc=strcmp(file+i+1, "o"))==0) {
			rc=1;
			ftype=binary;
		}
		if ((rc=strcmp(file+i+1, "s"))==0) {
			rc=1;
			ftype=assembler;
		}
		if ((rc=strcmp(file+i+1, "sh"))==0) {
			rc=1;
			ftype=script;
		}
	}
	if (debug=='2') printf("EXITING SUFFIX RC=%d\n",rc);
	return(rc);
}
/*
 *
 * GETARG --- Pass this routine a letter and it will look for it
 *            in LINE as -LETTER and set FILE equal to its value.
 *            A return code of 0 says NOT FOUND.
 *
 */
getarg(c1)
char	c1;
{
int	i, rc=0, j=0;

	if (debug=='2') printf("ENTERING GETARG\n");
	for (i=0; line[i]!='\0' && rc==0; ++i)
		if (line[i]=='-' && line[i+1]==c1) {
			for (i=i+2; line[i]==' ';++i);
	
			for (; line[i]!=' ' && line[i]!='-' && line[i]!='\0'; ++i)
				file[j++]=line[i];
	
			file[j]='\0';
			rc=1;
	       }
	if (debug=='2') printf("EXITING GETARG RC=%d\n",rc);
	return(rc);
}
/*
 *
 * GETLAST --- Sets FILE equal to last field in LINE
 *             pass GETLAST position from end (0=last)
 *             GETLAST returns: 0 NOT FOUND
 *                              1 FOUND FILE
 *
 */
getlast(position)
int position;
{
int	i, j, rc=0, k=0, skip, x;

	if (debug=='2') printf("ENTERING GETLAST  POSITION=%d\n",position);
	i=strlen(line)-1;
	for (j=0; j<= position && i>0 ;) {
		for (; line[i]==' ' && i>0; --i); /*no trailing blnks*/
		for (; line[i]!=' ' && i>0; --i); /* move b4 argument */
		if (line[i+1]!='-' && i>1) {
			skip=0;
			for (x=i; line[x]==' ' && x>1; --x); 
			if (line[x-1]=='-' && line[0]=='i' &&
				(line[x]=='c' || line[x]=='f' ||
				 line[x]=='m' || line[x]=='n' ||
				 line[x]=='u' || line[x]=='g')) skip=1;
			if (line[x-1]=='-' && line[0]=='c' &&
				(line[x]=='o' || line[x]=='V' ||
				 line[x]=='t')) skip=1;
			if (line[x-1]=='-' && line[0]=='l' &&
				(line[x]=='o' || line[x]=='V' ||
				 line[x]=='t')) skip=1;
			if (skip!=1 && position==j && i>1) {
				i=i+1;
				for (k=0; line[i]!=' ' && line[i]!='\0'; ++i) file[k++]=line[i];
				file[k]='\0';
				rc=1;
			}
			if (skip!=1) j++;
		}
	}
	if (debug=='2') printf("EXITING GETLAST RC=%d\n", rc);
	return(rc);
}
/*
 *
 * NOPATH --- STRIPS path from PARM
 *
 */
nopath()
{
int	i, rc=0;
char	hold[MAXLEN];

	if (debug=='2') printf("ENTERING NOPATH\n");
	for (i=0; line[i]!=' ' && line[i]!='\0'; ++i);
	/*  back up to last '/'  */
	for (; line[i]!='/' && i>0; --i);
	/*  i points to first letter in actual name  */
	/*  if (i) shift line left i spaces            */
	if (i>0) {
		i=i+1;
		strcpy(hold, line+i);
		strcpy(line, hold);
		rc=1;
	}
	if (debug=='2') printf("EXITING NOPATH RC=%d\n", rc);
	return;
}
/*                                                                  
 *
 * CKMAN --- Checks for manual pages
 *
 */
ckman()
{
int	rc=1;

	if (debug=='2') printf("ENTERING CKMAN\n");
	rc=strncmp(line, manval, strlen(manval));
	if (rc==0 && line[8]!='*') {
		printf("\n");
		strcpy(file, manpath);
		strcat(file, "/");
		strcat(file, line+8);
		ftype=manual;
		detail();
	}
	if (line[8]=='*' && rc==0)
	   printf("\n%s\n","  ***** Manual Page(s) NOT FOUND");
	if (debug=='2') printf("EXITING CKMAN RC=%d\n",rc);
	return(rc);
}
/*
 * 
 * MAKE --- Handles make commands
 *
 */
make()
{
	/* For now, just print the command.
	   Preferably the output from the make command should
	   be piped into this program. */

	prcmd();
	return;
}
/*
 *
 * PRCMD --- Prints the command it is processing
 *
 */
prcmd()
{
char	*hflag;

	if (debug=='2') printf("ENTERING PRCMD\n");
	if (psw=='1') {
		cmdsw=1;
		hflag=wflag;
		wflag=clr;
		ftype=unknown;
		strcpy(file, line);
		printf("\n");
		detail();
		wflag=hflag;
		cmdsw=0;
	}
	if (debug=='2') printf("EXITING PRCMD\n");
	return;
}
/*
 *
 * DOCHMOD --- Handles chmod commands
 *
 */
dochmod()
{
int	i=0, rc=0, x;
char	hold[5];

	prcmd();
	while ((rc=getlast(i++))==1);
	i-=2;
	/* there are i arguments on the line 
	   Get the mode to use			*/
	getlast(i);
	/* Save it from destruction 		*/
	strcpy(hold, file);
	for (x=0; x<i; x++) {
		strcpy(fmode, hold);
		getlast(x);
		ioflag=st;
		detail();
	}
	return;
}
/*
 *
 * DOCHOWN --- Handles chown commands
 *
 */
dochown()
{
int	i=0, rc=0, x;
char	hold[9];

	prcmd();
	while ((rc=getlast(i++))==1);
	i-=2;
	/* there are i arguments on the line 
	   Get the owner to use			*/
	getlast(i);
	/* Save it from destruction 		*/
	strcpy(hold, file);
	for (x=0; x<i; x++) {
		strcpy(fown, hold);
		getlast(x);
		ioflag=st;
		detail();
	}
	return;
}
/*
 *
 * DOCHGRP --- Handles chgrp commands
 *
 */
dochgrp()
{
int	i=0, rc=0, x;
char	hold[9];

	prcmd();
	while ((rc=getlast(i++))==1);
	i-=2;
	/* there are i arguments on the line 
	   Get the group to use			*/
	getlast(i);
	/* Save it from destruction 		*/
	strcpy(hold, file);
	for (x=0; x<i; x++) {
		strcpy(fgrp, hold);
		getlast(x);
		ioflag=st;
		detail();
	}
	return;
}
