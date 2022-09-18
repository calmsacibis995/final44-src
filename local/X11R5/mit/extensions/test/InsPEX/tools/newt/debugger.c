

/* $XConsortium: debugger.c,v 5.3 91/07/01 09:04:44 rws Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/



/*
 * debugger.c:  the debugger module of NewT
 */

#ifdef SYSV 
#define index strchr
#define rindex strrchr
#include <sys/types.h>
#include <string.h>
#else
#include <strings.h>
#endif

#include "sys/wait.h"
#include "sys/file.h"
#include "signal.h"
#include "looper.h"
#include "debugger.h"

#define MAXSCRATCH 100000	/* max scratch space for storing file images */
#define MAXCHAR 256		/* max char in a line */
#define DEFINC 10		/* default number of lines to list */
#define RUNAGAIN 255		/* to signal a re-run in the middle of a run*/
#define RUNDONE 254		/* to signal end of run */
#define RUNQUIT 253		/* to signal quit */
#define HASHSIZE 97		/* hash table size */

#define eqstr(a,b)  !strcmp((a),(b)) 	/* compare text string */

struct filestrlst {
	FILESTR *filestr;	/* debug structure */
	struct filestrlst *next;/* pointer to next entry */
};

typedef struct filestrlst FILESTRLST;	

FILESTR *N_fstr;		/* current debugging structure */

struct breakstrlst {
	int eventno;		/* event number */
	int lineno;		/* line number */
	FILESTR *filestr;	/* debug structure */
	struct breakstrlst *next;
};

typedef struct breakstrlst BREAKSTRLST;

struct aliasstr {                                               
        char *name;  	   	/* alias name */
        char *actualname;       /* actual name */
        struct aliasstr *next;
};

typedef struct aliasstr ALIASSTR;/* alias structure */
static ALIASSTR *hashtbl[HASHSIZE];/* pointer alias hash table */


static char *	emalloc();
static fatal();
static char *strsave();
char *	calloc();

static FILESTRLST flst = {NULL,NULL}; /* list of debugging structure */
static BREAKSTRLST blst= {0,0,NULL,NULL};  /* list of break structure */

static char    scratch[MAXSCRATCH]; /* scratch space for file images */
static char    *scratchlimit = scratch + MAXSCRATCH - MAXCHAR;
				/* used for boundary check */

int N_resumeat;			/* the line to continue at */
int N_isskip;			/* 1 if user has issued 'cont at ...' command */
int N_isstep;			/* 1 if user has issued 'step' command */
int N_isnext;			/* 1 if user has issued 'next' command */
int N_stepcount;		/* number of 'step' commands */
int N_nextcount;		/* number of 'next' commands */
static int isrunning = 0;	/* 1 if script is running */
static int pfd[2];		/* use to pipe back userbreakpts */
static int pid,cid;		/* parent and child process ids */
static int debugstrnum=0;	/* number of debug structure */
static int breakstrnum=0;	/* number of break structure */
static int curevent=1;		/* current event number of break structure */


/*
 * To initialize debug structure of a file if one doesn't already exist, 
 * or to retrieve the debug structure of this file.
 * The current debug structure is pointed to by "N_fstr".
 */
N_debuguse(filename)
	char *filename;
{
	static char* scratchptr=scratch;
	FILE *fp;
	int inc,i,found;
	FILESTRLST *fl;

	/* see if the debug structure of this file exist */
	for (fl = &flst,found=0;fl->next != NULL && !found; fl= fl->next) {
		if (eqstr(fl->next->filestr->name,filename)) {
			N_fstr = fl->next->filestr;
			found = 1;
		}
	}
	/* if not, create one for this file */
	/* allocate storage for userbreakpts and fileimage */
	/* and read in file image */
	if (!found) {
		fl->next = (FILESTRLST*) emalloc(sizeof(FILESTRLST));
		fl->next->filestr = (FILESTR*) emalloc(sizeof(FILESTR));
		fl->next->filestr->name = filename;
		fl->next->next = NULL;
		N_fstr = fl->next->filestr;
		/* it can be a macro file or the source file */
		if (!(fp=fopen(filename,"r"))) /* it is a macro file */
			if (!(fp=N_fopen_from_path(filename,"r",N_filepath))) 
				fatal("can't open file %s\n",filename);
		for(i=0;;++i) {
			if (scratchptr >= scratchlimit) 
				fatal("run out of scratch space",0);
			N_fstr->fileimage[i] =  fgets(scratchptr,MAXCHAR,fp);
			if (N_fstr->fileimage[i] == NULL)  /* EOF or error */
				break;
			inc = strlen(N_fstr->fileimage[i]) + 1;
			scratchptr += inc;
		}
		N_fstr->maxline = i;
		fclose(fp);
		debugstrnum++;
	}
}

/* 
 * debugger command main loop
 * to dispatch command issue by the user during a debugging session
 */
N_debugger(currentln)
	int currentln;
{
#ifdef SYSV
#define R_OK 4
#endif
	int i;
	char ln[MAXCHAR],*lnptr,*homedir;
	char cmd[MAXCHAR],c;
	ALIASSTR *ap,*Lookup();
	int a1,a2,tmpln;
	int n;
        static int firsttime = 1;
        int receive();
 
        if (firsttime) {
                firsttime = 0;
                signal(SIGUSR1,receive);
                pid = getpid();
		if (access(".NewTdbinit",R_OK) == 0) {
			readalias(".NewTdbinit");
		} else if (homedir = (char*) getenv("HOME")) {
			sprintf(ln,"%s/.NewTdbinit",homedir);
		      	if (access(ln,R_OK) == 0) 
				readalias(ln);
		}
        }
	N_isskip = N_isstep = N_isnext = 0;
	for (;;) {
		printf("Debugger> ");
		if (!fgets(ln,MAXCHAR,stdin))  /* EOF or Error */
			exit(0);
		n = sscanf(ln,"%s",cmd);
		if (n == -1)
			continue;
		if (ap = Lookup(cmd)) {
			aliasing(cmd,ap->actualname,ln);
			n = sscanf(ln,"%s",cmd);
			if (n == -1)
				continue;
		}
		if (eqstr(cmd,"list")) {
		    n = sscanf(ln,"%s %d %1s %d",cmd,&a1,&c,&a2);
		    switch (n) {
		    case 1:  /* default list DEFINC lines */
			if (currentln > N_fstr->maxline)
				lister(currentln,currentln);
			else {
			    if ( (tmpln = currentln+DEFINC-1) > N_fstr->maxline)
				tmpln = N_fstr->maxline;
			    lister(currentln,tmpln);
			    currentln = tmpln+1;
			}
			break;
		    case 2:  /* list the nth lines */
			lister(a1,a1);
			currentln = a1+1;
			break;
		    case 4:  /* list a1 to a2 lines */
			if (c == ',') {
			    lister(a1,a2);
			    currentln = a2+1;
			    break;
			}
		    default:
			printf("Debugger: invalid syntax\n");
		    }
		} else if (eqstr(cmd,"step")) {
		    if (!isrunning) 
		        puts("Debugger: can't continue");
		    else {
                        n = sscanf(ln,"%s %d",cmd,&a1);
                        switch (n) {
                        case 1:
			    N_isstep = 1;
			    N_stepcount = 1;
			    return;
                        case 2:
                            N_isstep = 1;
                            N_stepcount = a1;
			    return;
                        default:
                            puts("Debugger: invalid syntax");
                        }
                    }    
		} else if (eqstr(cmd,"next")) {
                    if (!isrunning)
                        puts("Debugger: can't continue");
                    else {  
                        n = sscanf(ln,"%s %d",cmd,&a1);
                        switch (n) {
                        case 1:
                            N_isnext = 1;
                            N_nextcount = 1;
                            return;
                        case 2:
                            N_isnext = 1;
                            N_nextcount = a1;
                            return;
                        default:
                            puts("Debugger: invalid syntax");
                        }   
                    }    
		} else if (eqstr(cmd,"cont")) {
		    if (!isrunning) 
		        puts("Debugger: can't continue");
		    else {
		        n = sscanf(ln,"%s %s %d",cmd,cmd,&a1);
		        switch (n) {
		        case 1:  
			    return;
		        case 3:  
			    if (eqstr(cmd,"at")) {
				if (N_getflag(N_fstr->breakablept,a1)) {
			            N_isskip = 1;
			            N_resumeat = a1;
		                    return;
				} else {
			    	    printf("Debugger: no executable code at line %d\n",a1);
				    break;
				}
			    }
		        default:
			    puts("Debugger: invalid syntax");
			}
		    }
		} else if (eqstr(cmd,"stop")) {
		    n = sscanf(ln,"%s %s %d",cmd,cmd,&a1);
		    switch (n) {
		    case 3:  
			if (eqstr(cmd,"at")) {
			    breakat(a1);
			    break;
			}
		    default:
			printf("Debugger: invalid syntax\n");
		    }
		} else if (eqstr(cmd,"call")) {
			lnptr = index(ln,'c');
			N_interpret(lnptr+4,NULL); /* skip over "call" */
		} else if (eqstr(cmd,"delete")) {
		    n = sscanf(ln,"%s %d",cmd,&a1);
                    switch (n) {
		    case 1:
                        n = sscanf(ln,"%s %s",cmd,cmd);
			if (n == 2 && eqstr(cmd,"all")) 
			    deleteall();
			else
			    printf("Debugger: invalid syntax\n");
			break;
                    case 2:
		    {
	                int cont = 1;

			delete(a1);
			lnptr = index(ln,'d') + 6; /* skip over "delete" */
			while (cont) {
                            n = sscanf(lnptr,"%d %1s %d",&a1,&c,&a2);
			    switch (n) {
			    case 1:
				cont=0;
				break;
			    case 3:
				if (c == ',') {
				    delete(a2);
				    lnptr = index(lnptr,',') + 1;
				    break;
				}
			    default:
				cont=0;
			        printf("Debugger: invalid syntax\n");
			    }
			}
		    }
			break;
                    default:
                        printf("Debugger: invalid syntax\n");
                    }
		} else if (eqstr(cmd,"status")) {
		    inquire();
		} else if (eqstr(cmd,"run")) {
		    run();
		} else if (eqstr(cmd,"quit")) {
			exit(RUNQUIT);
		} else if (eqstr(cmd,"alias")) {
			lnptr = index(ln,'a') + 5;
                        if (sscanf(lnptr,"%s",cmd) == 1) {
				lnptr = index(lnptr,cmd[0]) + strlen(cmd);
				install (cmd,lnptr);
			} else
                        	printf("Debugger: invalid syntax\n");
		} else {
			puts("Debugger: invalid command");
		}
	}
}

/*
 * Start execution of looper script
 */
static run()
{
	int done=0;
#if defined(SYSV) || defined(__convex__)
	int childstatus;
#else
	union wait childstatus;
#endif

	if (N_2process) {
	    if (isrunning) {
		sendback();
		exit(RUNAGAIN);
	    }
	    while (!done) {
                if (pipe(pfd) == -1)
                        fatal("pipe system call",0);
		if (fork()) { /* parent */
                        if (close(pfd[1]) == -1)
                                fatal("close system call 1",0);
			wait (&childstatus);
                        if (close(pfd[0]) == -1)
                                fatal("close system call 2",0);
#if defined(SYSV) || defined(__convex__)
#ifndef WEXITSTATUS
#define WEXITSTATUS(s) ( ((s)>>8) & 0377 )
#endif
#else
#define WEXITSTATUS(s) ((s).w_retcode) 
#endif
			switch(WEXITSTATUS(childstatus)) {
			case RUNQUIT:
			    	exit(0);
			case RUNAGAIN:
			    	break;
			case RUNDONE:
			    	done = 1;
			    	break;
			default:
				printf("Debugger: program died\n");
				done = 1;
				break;
			}
		 } else { /* child */
                        if (close(pfd[0]) == -1)
                                fatal("close system call 3",0);
			isrunning = 1;
                        cid = getpid();
			N_execute(N_funchead->next,EXECUTE_NORMAL);
			sendback();
			puts("Debugger: execution completed");
			exit(RUNDONE);
		 }
	    }
	} else {
	    	isrunning = 1;
		N_execute(N_funchead->next,EXECUTE_NORMAL);
	    	isrunning = 0;
	}
}

/* 
 * send back userbreakpts array(for all files) and break event list to 
 * the parent process, notify its parent by sending a SIGUSR1 signal
 */
static sendback()
{
        FILESTRLST *fl;
	BREAKSTRLST *bl;
	int i;
 
	/* send back userbreakpt for all files */
        for (fl = flst.next,i=0;i<debugstrnum; ++i,fl= fl->next) {
                if (write(pfd[1],(char*)fl->filestr->userbreakpt,MAXBIT) != MAXBIT)
			fatal("write system call 1",0);
	}

	/* send back number of break structure */
        if (write(pfd[1],(char*)&breakstrnum,sizeof(int)) != sizeof(int))
			fatal("write system call 2",0);

	/* send back current event number of break structure */
        if (write(pfd[1],(char*)&curevent,sizeof(int)) != sizeof(int))
			fatal("write system call 3",0);

	/* send back break structures */
        for (bl = blst.next,i=0;i<breakstrnum; ++i,bl= bl->next) {
                if (write(pfd[1],(char*)bl,sizeof(BREAKSTRLST)) != sizeof(BREAKSTRLST))
			fatal("write system call 4",0);
	}
        if (kill(pid,SIGUSR1) == -1)
		fatal("kill system call 1",0);
}

 
/*
 * parent process receive a userbreakpts array for all files and break
 * event list upon receiving a SIGUSR1 signal from the child
 */
static receive()
{
	FILESTRLST *fl;	/* pointer to debug structure list */
	BREAKSTRLST *bl,*btrace,*bstr;
	int i;

	/* receive userbreakpt for all files */
        for (fl=flst.next,i=0;i<debugstrnum;++i,fl=fl->next) {
		if (read(pfd[0],(char*)fl->filestr->userbreakpt,MAXBIT)!= MAXBIT)
			fatal("read system call 1",0);
	}

	/* delete invalid break structures */
	freebreakstrlst(&blst);

	/* receive back number of break structure */
	if (read(pfd[0],(char*)&breakstrnum,sizeof(int))!= sizeof(int))
		fatal("read system call 2",0);

	/* receive current event number of break structure */
	if (read(pfd[0],(char*)&curevent,sizeof(int))!= sizeof(int))
		fatal("read system call 3",0);

	/* receive and rebuilt break structures */
        for (btrace= &blst,i=0;i<breakstrnum; ++i,btrace= btrace->next) {
		bstr = (BREAKSTRLST*) emalloc(sizeof(BREAKSTRLST));
                if (read(pfd[0],(char*)bstr,sizeof(BREAKSTRLST)) != sizeof(BREAKSTRLST))
			fatal("read system call 4",0);
		btrace->next = bstr;
	}
        signal(SIGUSR1,receive);
}

/*
 * recursively freeing break structure list
 */
static freebreakstrlst(bl)
	BREAKSTRLST *bl;
{
	if (bl->next != NULL) {
		freebreakstrlst(bl->next);
		free(bl->next);
	}
}

/*
 * debug command "list"
 */
static lister(start,end)
	int start,end;
{
	int i;

        if (end > N_fstr->maxline) 
                printf("Debugger: %s has only %d lines\n",N_fstr->name,N_fstr->maxline);
	else if ( start <= 0 || start > end)
                printf("Debugger: invalid argument\n");
        else
		for (i=start-1;N_fstr->fileimage[i] != NULL && i <end ; ++i) 
			printf("	%d %s",i+1,N_fstr->fileimage[i]);
}

/*
 * debug command "stop"
 */
static breakat(line)
	int line;
{
	BREAKSTRLST *bstr;

	if (line > N_fstr->maxline ) 
                printf("Debugger: %s has only %d lines\n",N_fstr->name,N_fstr->maxline);
	else if (!N_getflag(N_fstr->breakablept,line))
		printf("Debugger: no executable code at line %d\n",line);
	else if (N_getflag(N_fstr->userbreakpt,line))
		printf("Debugger: this break point has been registered\n"); 
	else { 
		N_setflag(N_fstr->userbreakpt,line);
		bstr = (BREAKSTRLST*) emalloc(sizeof(BREAKSTRLST));
		bstr->eventno = curevent++;
		bstr->lineno = line;
		bstr->filestr = N_fstr;
		bstr->next = blst.next;
		blst.next = bstr;
		breakstrnum++;
		printf("Debugger: (%d) stop at %s:%d\n",bstr->eventno,N_fstr->name,line);
	}
}

/* 
 * set the flag corresponding to "line" in "str" (userbreakpt or breakablept)
 */
N_setflag(str,line)
	char *str;
	int line;
{
        int offset,idx;
        unsigned char mask;

	idx = (line-1)/8;
        offset = (line-1)%8;
        mask = 1 << offset;
        str[idx] |= mask;
}

/*
 * clear the flag corresponding to "line" in "str" (userbreakpt or breakablept)
 */
static clearflag(str,line)
        char *str; 
        int line; 
{
        int offset,idx; 
        unsigned char mask; 
 
        idx = (line-1)/8; 
        offset = (line-1)%8;
        mask = ~(1 << offset);
        str[idx] &= mask;
}


/*
 * get the flag corresponding to "line" in "str" (userbreakpt or breakablept)
 */
N_getflag(str,line)
        char *str; 
        int line; 
{
        int offset,idx; 
        unsigned char mask; 
 
        idx = (line-1)/8; 
        offset = (line-1)%8;
        mask = 1 << offset;
        return((int)str[idx] & mask);
}

/*
 * debug command "delete"
 */
static delete(event)
        int event;
{
	BREAKSTRLST *bl,*btrace;
	int found = 0;

	for (btrace= &blst,bl=btrace->next;bl!=NULL&&!found;btrace=bl,bl=bl->next) {
		if (bl->eventno == event) {
			btrace->next = bl->next;
			free(bl);
                	clearflag(bl->filestr->userbreakpt,bl->lineno);
			found = 1;
		}
	}
	if (!found)
                printf("Debugger: no such event\n");
}


/*
 * debug command "delete all"
 */
static deleteall()
{
        BREAKSTRLST *bl,*btrace;
        int found = 0;

        for (btrace= &blst,bl=btrace->next;bl!=NULL;btrace=bl,bl=bl->next) {
        	free(bl);
                clearflag(bl->filestr->userbreakpt,bl->lineno);
        }
}                 
 

/*
 * debug command "status" 
 */
static inquire()
{
	BREAKSTRLST *bl;

	for (bl=blst.next;bl!=NULL;bl=bl->next) {
		printf("Debugger: (%d) stop at %s:%d\n",bl->eventno,bl->filestr->name,bl->lineno);
	}
}

/*
 * print fatal error message and exit
 */
static
fatal(s,t)
        char *s,*t;
{
        fprintf(stderr,"Debugger error: ");
        fprintf(stderr,s,t);
        puts("");
	fflush(stdout);
	fflush(stderr);
        exit(1);
}

/*
 * process .NewTdbinit
 */
static readalias(filename)
	char *filename;
{
	FILE *fp;
	char ln[MAXCHAR],cmd[MAXCHAR],*lnptr;
	int n;

	if (!(fp=fopen(filename,"r")))
			fatal("can't open file %s\n",filename);
	while (fgets(ln,MAXCHAR,fp)) {
		n = sscanf(ln,"%s",cmd);
		if (n == -1)
			continue;
		if (eqstr(cmd,"alias")) {
			lnptr = index(ln,'a') + 5;
                        if (sscanf(lnptr,"%s",cmd) == 1) {
				lnptr = index(lnptr,cmd[0]) + strlen(cmd);
				install (cmd,lnptr);
			}
		} else
			printf("Debugger: invalid command %s in file %s\n",cmd,filename);
	}
}

/*
 * remake input line for alias processing
 */
aliasing(name,actualname,ln)
	char *name,*actualname,*ln;
{
	char tmpln[MAXCHAR],*ptr;

	strcpy(tmpln,ln);
	ptr = index(tmpln,name[0]) + strlen(name);
	sprintf(ln,"%s %s",actualname,ptr);
}

/*
 * Retrieve hash value
 */
static
hash(s)
        char *s;
{
        int hashval;

        for (hashval = 0; *s != '\0'; )
                hashval += *s++;
        return(hashval % HASHSIZE);
}

static
install(name,actualname)
        char *name,*actualname;
{
        ALIASSTR *ap, *Lookup();
        int hashval;

        if (ap=Lookup(name))   {
		free(ap->name);
		free(ap->actualname);
                ap->name = strsave(name);
                ap->actualname = strsave(actualname);
	} else {
                ap = (ALIASSTR *) emalloc(sizeof(ALIASSTR));
                ap->name = strsave(name);
                ap->actualname = strsave(actualname);
                hashval = hash(name);
                ap->next = hashtbl[hashval];
                hashtbl[hashval] = ap;
        }
}

/*
 * Retrieve an entry from the alias hash tbl.
 */
static ALIASSTR *
Lookup(name)
        char *name;
{
        ALIASSTR *ap;
         
        for (ap = hashtbl[ hash(name) ]; ap != NULL; ap = ap->next)
                if ( eqstr(name, ap->name) )
                        return(ap); /* found it */
        return((ALIASSTR*)NULL); /* not found */
}


/*
 * Copy and save a string.
 */
static char *
strsave(s)
        char *s;
{
        char *p;

        p = emalloc(strlen(s)+1);
        strcpy(p,s);
        return(p);
}

/*
 * Allocate memory.
 */
static char *
emalloc(size)
        int size;
{
        char *p;

        if (! (p=calloc(size,sizeof(char))))
                fatal("calloc() failed");
        return(p);
}
 
