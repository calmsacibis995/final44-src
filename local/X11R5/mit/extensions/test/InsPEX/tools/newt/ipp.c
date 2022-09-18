


/* $XConsortium: ipp.c,v 5.2 92/02/25 10:16:07 mor Exp $ */

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
 * ipp.c:
 *
 * IPP creates functions that serve as the interface bewtween
 * the interpreter and the user library by providing a 
 * implementation independent generic function call environment. 
 * In addition, IPP creates codes for the creation of hash tables 
 * for functions and integer constants.
 */

#include <stdio.h>
#include <ctype.h>
#ifdef SYSV 
#define index strchr
#define rindex strrchr
#include <string.h>
#else
#include <strings.h>
#endif
#include "config.h"

#define MAXTOK 3		/* maximum token stack size */
#define MAXLEN 256		/* maximum string length */
#define MAXFILES 16		/* maximum number of files */
#define HASHSIZE 3097		/* hash table size */

typedef enum {
	E_MAXTOK, E_ID, E_EOF, E_DUPNAME, E_MAXSTR,
	E_SYNTAX, E_CHR, E_MAXARG,
	E_CMD,  E_READ, E_WRITE, 
	E_MALLOC
	} ERROR;   	/* error type */

typedef enum {
	T_ID, T_LEFTP, T_RIGHTP, T_COMMA, T_ASTER, T_VARARG, T_EXC, T_SEMI,
	T_EOF
	} TOKEN;	/* token type */

typedef enum {
	S_START, S_INARG, S_NEXTARG , S_ARGLST, S_VARARG, S_INRET,
	} STATE;	/* state type */

typedef struct {
	TOKEN token;
	char word[MAXLEN];
} TSTACK;			/* token stack type */


static TSTACK tokstack[MAXTOK];	/* token stack */
static int stackptr=0;		/* token stack pointer */

static int line; 		/* line number */
static char *pgm_name;		/* program name */
static char *kfiles[MAXFILES];	/* constant file names */
static int kcount=0;		/* constant file count */
static char *ifiles[MAXFILES];	/* include file names */
static int icount=0;		/* include file count */
static char *ufiles[MAXFILES];	/* interface file names */
static int ucount=0;		/* interface file count */
static char *dotc = "interface.c";/* default output .c file */
static char *doth = "interface.h";/* default output .h file */
static char cfile[MAXLEN];	/* non default output .c file */
static char hfile[MAXLEN];	/* non default output .h file */
static FILE *dotcfp,*dothfp;	/* file pointers */
static char *libprefix=NULL; /* non default file prefix */
static char *includefile = NULL;/* an optional usr include file name */
static char *menu = "stdin";	/* menu file name */
static int newstyle = 0;	/* old style requires extra level of
				   indirection for procedure arguments in 
				   .c file */

#define VALID_ID(c) 	isalnum(c) || c == '_'
#define FILLWORD(c)  *w++ = c; *w = '\0';

struct plist {
	char 	*name;
	int  	argc;
	int	vararg;
	char    *args[MAXARG];
	int	ret;
	int  	escape;
	struct 	plist	*next;
}; 

typedef struct plist PLIST;	/* hash table content structure */
static PLIST *hashtbl[HASHSIZE];/* pointer hash table */

static char* emalloc();

/* 
 * ipp main program
 */
main( argc, argv)
	int argc;
	char **argv;
{
	FILE *kfp,*menufp = stdin;	/* file pointers */
	extern int optind;
	extern char *optarg;
	int c,i;
	char *slash;

	pgm_name = argv[0];
        if (argc == 1 && isatty(0) ) error(E_CMD);
	/*
	 * process cmd line arguments
	 */
	while ((c = getopt(argc,argv,"k:i:u:l:n")) != EOF) {
		switch(c) {
		case 'k':
			kfiles[kcount++] = optarg;
			break;
		case 'i':
			ifiles[icount++] = optarg;
			break;
		case 'u':
			ufiles[ucount++] = optarg;
			break;
		case 'l':
			/* libprefix should be basename of -l argument */
			if ((slash = rindex(optarg, '/')) == NULL) {
				libprefix = optarg;
			} else {
				libprefix = slash+1;
			}
			if (strlen(optarg) > MAXLEN - 3)
				error(E_MAXSTR,optarg);
			sprintf(cfile,"%s.c",optarg);
			sprintf(hfile,"%s.h",optarg);
			dotc = cfile;
			doth = hfile;
			break;
		case 'n':
			newstyle = 1;
			break;
		case '?':
			exit(1);
                }                 
	}

	if (! (dotcfp = fopen(dotc,"w"))) 
		error(E_WRITE,dotc);
	if (! (dothfp = fopen(doth,"w"))) 
		error(E_WRITE,doth);

	/* processes menu file */
	W_fcnbegin();
	if (optind < argc) {
		for (;optind < argc; optind++) {
			if (!(menufp = fopen((menu = argv[optind]),"r")) )
				error(E_READ,menu);
			DO_menu(menufp,dotcfp);	
		}
	} else
		DO_menu(menufp,dotcfp);	
	W_fcnend();

	/* processes constant file */
	if (kcount) {
		W_kbegin();
		for (i=0;i<kcount;++i) {
			if (kfp = fopen(kfiles[i],"r"))
				DO_kfile(kfp,kfiles[i]);	
			else
				error(E_READ,kfiles[i]);
		}
		W_kend();
	} else  { /* create N_makehashconst function still */
		if (libprefix && strcmp(libprefix,"interface")) {
			fprintf(dotcfp,"void\nN_%sconst()\n{\n",libprefix);
		} else
			fprintf(dotcfp,"void\nN_makehashconst()\n{\n");
		for (i=0;i<ucount;++i)
			fprintf(dotcfp,"\textern void N_%sonst();\n",ufiles[i]);
		fprintf(dotcfp,"\n");
		for (i=0;i<ucount;++i)
			fprintf(dotcfp,"\tN_%sconst();\n",ufiles[i]);
		fprintf(dotcfp,"}\n\n");
	}
	fclose(dotcfp);
	return(0);
}




/*
 * gettoken(infp,infile,word)
 * return from input or token stack the next input token 
 * and assign the token string to word
 */
static TOKEN
gettoken(infp,infile,word)
	FILE *infp;	
	char *word,*infile;
{
	TOKEN poptok(), gettok();

	if (stackptr)
		return(poptok(word));
	else
		return(gettok(infp,infile,word));
}

/*
 * poptok(word)
 * Retrieve a token and its string value from the stack
 */
static TOKEN
poptok(word)
        char *word;
{
        --stackptr;
        strcpy(word,tokstack[stackptr].word);
        return(tokstack[stackptr].token);
}

/*
 * pushtok(token,word)
 * Push a token and its string value into the stack
 */
static
pushtok(token,word)
        TOKEN token;
        char *word;
{
        tokstack[stackptr].token = token;
        strcpy(tokstack[stackptr].word,word);
        stackptr++;
}

	
/*
 * gettok(infp,infile,word)
 * return the next input token and assign the token string to word
 */
static TOKEN 
gettok(infp,infile,word)
	FILE *infp;
	char *word,*infile;
{
	int c,previous,count=1;
	char *w=word;
	enum {
		S_NEUTRAL, S_INID
	} state = S_NEUTRAL;

	while ( (c=fgetc(infp)) != EOF) {
		switch(state) {
		case S_NEUTRAL:
			switch(c) {
			case '(':
				FILLWORD(c)
				return(T_LEFTP);
			case ')':
				FILLWORD(c)
				return(T_RIGHTP);
			case '*':
				FILLWORD(c)
				return(T_ASTER);
			case ',':
				FILLWORD(c)
				return(T_COMMA);
			case ';':
				FILLWORD(c)
				return(T_SEMI);
			case '!':
				FILLWORD(c)
				return(T_EXC);
			case '\n':
				line++;
				continue;
			case ' ':
			case '\t':
				continue;
			case '/':
				if (fgetc(infp) == '*') {
				  	if ((previous=fgetc(infp))== '\n') line++;
					while ((c=fgetc(infp)) != EOF) {
						if (c == '\n') line++;
						if (c == '/' && previous == '*')
							break;
						else
							previous = c;
					}
					if (c == EOF)
						error(E_EOF,infile);
				} else
					error(E_CHR,infile,&c);
				continue;
			default:
				if (isalpha(c) || c == '_') {
					*w++ = c;
					state = S_INID;
				}
				else 
					error(E_CHR,infile,&c);
				continue;
			}
		case S_INID:
			if (VALID_ID(c)) 
				if (++count < MAXLEN)
					*w++ = c;
				else {
					*w = '\0';
					error(E_MAXTOK,infile,word);
				}
			else {
				ungetc(c, infp);
				*w = '\0';
				if (strcmp(word,"VARARG"))
					return(T_ID);
				else
					return(T_VARARG);
			}
			continue;
		}
	}
	return(T_EOF);
}
         
				
		
/*
 * DO_menu (infp)
 * Processes menu file.
 * Applies a finite state machine model to the parser
 */
static
DO_menu(infp)
	FILE *infp;
{
	char word[MAXLEN], lword[MAXLEN], text[MAXLEN], ret[MAXLEN];
	TOKEN token,lookahead;
	int count,argc,escape=0;
	PLIST *H_install(), *pp;
	STATE state = S_START;

	line = 1;
	while ( (token=gettoken(infp,menu,word)) != T_EOF) {
		switch(state) {
		case S_START:
			if (token == T_ID) {
				if ((lookahead=gettok(infp,menu,lword)) == T_LEFTP) {
					if (pp = H_install(word)) {
						argc = 0;
						state = S_ARGLST;
						pp->escape = escape;
						escape = 0;
						pp->ret = 0;
					} else
						error(E_DUPNAME,menu,word);
				} else {
					*ret = 0;
					strcpy(ret,word);
					state = S_INRET;
					pushtok(lookahead,lword);
				}
			} else if (token == T_EXC) {
				escape = 1;
			} else if (token == T_SEMI) {
				;
			} else
				error(E_ID,menu,word);
			continue;
		case S_ARGLST:
			if (token == T_ID) {
				*text = 0;
				strcpy(text,word);
				state = S_INARG;
			} else if (token == T_RIGHTP) {
				W_fcninstall(pp,argc);
				state = S_START;
			} else if (token == T_VARARG) {
				state = S_VARARG;
				pp->vararg = 1;
			} else
				error(E_SYNTAX,menu,word);
			continue;
		case S_VARARG:
			if (token == T_RIGHTP) {
				W_fcninstall(pp,argc);
				state = S_START;
			} else
				error(E_SYNTAX,menu,word);
			continue;
		case S_INRET:
                        if (token == T_ID) 
				if ((lookahead=gettok(infp,menu,lword)) == T_LEFTP) {
					if (pp = H_install(word)) {
						argc = 0;
						state = S_ARGLST;
						pp->escape = escape;
						escape = 0;
						if (strcmp(ret,"void")) {
							pp->ret = 1; 
							W_fcnentry(ret,argc++,pp);
						} else
							pp->ret = 0; 
					} else
						error(E_DUPNAME,menu,word);
				} else {
                                	if (strlen(ret) + strlen(word + 1) < MAXLEN) {
                                        	strcat (ret," ");
                                        	strcat (ret,word);
						pushtok(lookahead,lword);
                                	} else {
                                        	ret[MAXLEN] = '\0';
                                        	error(E_MAXTOK,menu,ret);
                                	}
				}
			else if (token == T_ASTER) 
                                if (strlen(ret) + strlen(word + 1) < MAXLEN) {
                                        strcat (ret," ");
                                        strcat (ret,word);
                                } else {
                                        ret[MAXLEN] = '\0';
                                        error(E_MAXTOK,menu,ret);
                                }
			else
                        	error(E_SYNTAX,menu,ret);
			continue;
		case S_INARG:
			if (token == T_ID || token == T_ASTER) {
				if (strlen(text) + strlen(word + 1) < MAXLEN) {
					strcat (text," ");
					strcat (text,word);
				} else {
					text[MAXLEN] = '\0';
					error(E_MAXTOK,menu,text);
				}
			} else if (token == T_COMMA) {
				/* write argument info to output file */
				W_fcnentry(text,argc++,pp);
				state = S_NEXTARG;
			} else if (token == T_RIGHTP) {
				if (*text) 
					/* write argument info if any */
					W_fcnentry(text,argc++,pp);
				/* done with one predicate ,more output */
				W_fcninstall(pp,argc);
				state = S_START;
			} else
				error(E_SYNTAX,menu,word);
			continue;
		case S_NEXTARG:
			if (token == T_ID) {
				*text = 0;
				strcpy(text,word);
				state = S_INARG;
			} else if (token == T_VARARG) {
				state = S_VARARG;
				pp->vararg = 1;
			} else
				error(E_SYNTAX,menu,word);
			continue;
		}
	}
	if (state != S_START)
		error(E_EOF,menu);
}




/*
 * DO_kfile(infp,fname)
 * Processes k file .
 * Applies a finite state machine model to the parser
 */
static
DO_kfile(infp,fname)
	FILE *infp;
	char *fname;
{
        char word[MAXLEN];
        int count;
	TOKEN token;

	line = 1;
	
        while ( (token=gettok(infp,fname,word)) != T_EOF) {
		if (token == T_ID) 
        		fprintf(dotcfp,"\t{\"%s\",(long)%s},\n",word,word);
		else
			error(E_ID,fname,word);
	}
}

/*
 * W_kbegin()
 * Write beginning part of k declaration.
 */
static
W_kbegin()
{
        fprintf(dotcfp,"static\nstruct kstruct {\n\tchar *k_name;\n\tint k_val;\n} ");
        fprintf(dotcfp,"ks[] = {\n");
}

/*
 * W_kend()
 * Write ending part of k declaration .
 */
static
W_kend()
{
	int i;

        fprintf(dotcfp,"\t{NULL,0}\n};\n\n");
	if (libprefix && strcmp(libprefix,"interface"))
        	fprintf(dotcfp,"void\nN_%sconst()\n{\n",libprefix);
	else
        	fprintf(dotcfp,"void\nN_makehashconst()\n{\n");
	for (i=0;i<ucount;++i)
		fprintf(dotcfp,"\textern void N_%sconst();\n",ufiles[i]);
	fprintf(dotcfp,"\tvoid N_installconst();\n\tint i;\n\n");
	for (i=0;i<ucount;++i)
		fprintf(dotcfp,"\tN_%sconst();\n",ufiles[i]);
	fprintf(dotcfp,"\n");
        fprintf(dotcfp,"\tfor(i=0;ks[i].k_name != NULL;++i)\n");
        fprintf(dotcfp,"\t\tN_installconst(ks[i].k_name,ks[i].k_val);\n}\n");
}

/*
 * W_fcnbegin()
 * Writes header info to output file 
 */
static
W_fcnbegin()
{
	int i;

	fprintf(dotcfp, "#define XLIB_ILLEGAL_ACCESS\n");
	fprintf(dotcfp, "#include \"%s\"\n",doth);
	if (icount) {
		for (i=0;i<icount;++i)
			fprintf(dotcfp, "#include \"%s\"\n",ifiles[i]);
	}
	fprintf(dotcfp, "\ntypedef char* ADDR;\n\n");
	if (libprefix && strcmp(libprefix,"interface"))
		fprintf(dotcfp, "void\nN_%sfcn()\n{\n",libprefix);
	else
		fprintf(dotcfp, "void\nN_makehashfcn()\n{\n");
	fprintf(dotcfp, "\tstruct {\n\t\tint size;\n\t\tint size_ifnotptr;\n");
	fprintf(dotcfp, "\t\tchar *type;\n\t} argv[MAXARG];\n");
	for (i=0;i<ucount;++i)
		fprintf(dotcfp,"\textern void N_%sfcn();\n",ufiles[i]);
	fprintf(dotcfp, "\textern void N_installfcn();\n\n");
	for (i=0;i<ucount;++i)
		fprintf(dotcfp,"\tN_%sfcn();\n",ufiles[i]);
	fprintf(dotcfp,"\n");
}

/*
 * W_fcnentry(text,argc,pp)
 * Writes the necessary argument initialization codes per function entry
 */
static
W_fcnentry(text,argc,pp)
	char *text;
	int argc;
	PLIST *pp;
{
	char *p, *strsave();

	if (argc >= MAXARG)
		error(E_MAXARG,menu,pp->name);
	pp->args[argc] = strsave(text);
        fprintf(dotcfp,"\targv[%d].type = \"%s\";\n",argc,text);
        fprintf(dotcfp,"\targv[%d].size = sizeof(%s);\n",argc,text);
        fprintf(dotcfp,"\targv[%d].size_ifnotptr = ",argc);
	if (p = (char*)rindex(text,'*')) {
		*p = '\0';
        	fprintf(dotcfp,"sizeof(%s);\n",text);
	}
	else
        	fprintf(dotcfp,"0;\n");
}

/* 
 * W_fcninstall(pp,argc)
 * Writes one N_installfcn call
 */
static W_fcninstall(pp,argc)
	PLIST *pp;
	int argc;
{
	int retsize;

	pp->argc = argc;
        fprintf(dotcfp,"\tN_installfcn(\"%s\",X_%s,%d,argv,%d,%d);\n\n",pp->name,pp->name,pp->argc,pp->vararg,pp->ret);
}

/*
 * W_fcnend()
 * Writes the interface functions into interface.c and declarations into 
 * interface.h
 */
static
W_fcnend()
{
	int i;
	PLIST *pp;
	int acount;
	char underscore;
	
	if (!libprefix || strcmp(libprefix,"interface"))
		fprintf(dotcfp,"\tN_installfcn(\"dumpvar\",X_dumpvar,0,argv,0,0);\n");
	fprintf(dotcfp,"}\n\n");

	fprintf(dothfp,"#include \"stdio.h\"\n");
	fprintf(dothfp,"#include \"config.h\"\n");
	for (i=0; i<HASHSIZE; ++i) 
	  if (pp=hashtbl[i]) 
	    for (; pp != NULL; pp = pp->next) {
		fprintf(dothfp,"int X_%s();\n",pp->name);
		fprintf(dotcfp,"int\nX_%s(argv)\n",pp->name);
		fprintf(dotcfp,"\tADDR *argv;\n{\n");
		acount=0;
		if (newstyle) {
			underscore = (pp->escape)? '_' : ' ';
			if (pp->ret) {
/*
Eliminate type casting on LHS of operator
				fprintf(dotcfp,"\t*(%s*)argv[0] = %c%s(",pp->args[0],underscore,pp->name);
*/
				fprintf(dotcfp,"\t%s tmp;\n\n",pp->args[0]);
				fprintf(dotcfp,"\ttmp = %c%s(",underscore,pp->name);
				acount++;
			} else
				fprintf(dotcfp,"\t%c%s(",underscore,pp->name);
			if ((!pp->ret && pp->argc) 
				|| (pp->ret && pp->argc>1)) {
				fprintf(dotcfp,"*(%s*)argv[%d]",pp->args[acount],acount);
				acount++;
				for (;acount<pp->argc;acount++) 
					fprintf(dotcfp,", *(%s *)argv[%d]",pp->args[acount],acount);
			}
			if (pp->vararg) {
				if ((!pp->ret && pp->argc) 
					|| (pp->ret && pp->argc>1)) 
					fprintf(dotcfp,",");
				fprintf(dotcfp,"&argv[%d]",acount);
			}
			fprintf(dotcfp,");\n");
			if (pp->ret) 
				fprintf(dotcfp,"\tmemcpy((char*)argv[0],(char*)&tmp,sizeof(%s));\n",pp->args[0]);
			fprintf(dotcfp,"}\n\n");
		} else {
			fprintf(dotcfp,"\treturn(_%s(",pp->name);
			if (pp->argc) {
				fprintf(dotcfp,"argv[%d]",acount++);
				for (;acount<pp->argc;acount++) 
					fprintf(dotcfp,", argv[%d]",acount);
			}
			if (pp->vararg) {
				if (pp->argc) 
					fprintf(dotcfp,",");
				fprintf(dotcfp," &argv[%d]",acount);
			}
			fprintf(dotcfp,"));\n}\n\n");
		}
	}

	if (!libprefix || !strcmp(libprefix,"interface")) {
		fprintf(dotcfp,"int\nX_dumpvar(argv)\n\tADDR *argv;\n{\n");
		if (newstyle)
			fprintf(dotcfp,"\tdumpvar();\n}\n\n");
		else
			fprintf(dotcfp,"\treturn(dumpvar());\n}\n\n");
	}
	fprintf(dothfp,"int X_dumpvar();\n");
	fclose(dothfp);
}


/*
 * H_hash(s)
 * Retrieve hash value
 */
static
H_hash(s)
	char *s;
{
	int hashval;

	for (hashval = 0; *s != '\0'; )
		hashval += *s++;
	return(hashval % HASHSIZE);
}

/*
 * H_install(name)
 * Install a new entry to the hash tbl.
 */
static PLIST *
H_install(name)
	char *name; {
	PLIST *pp, *H_lookup();
	char *strsave();
	int hashval;
	
	if (!(pp = H_lookup(name)) )  { /* not found */ 
		pp = (PLIST *) emalloc(sizeof(PLIST));
		pp->name = strsave(name);
		pp->vararg = 0;
		hashval = H_hash(name);
		pp->next = hashtbl[hashval];
		hashtbl[hashval] = pp;
		return(pp);
	} else
		return(NULL);
}
		
/*
 * H_lookup(name)
 * Retrieve an entry to the hash tbl.
 */
static PLIST *
H_lookup(name)
	char *name;
{
	PLIST *pp;

	for (pp = hashtbl[ H_hash(name) ]; pp != NULL; pp = pp->next)
		if (! strcmp(name, pp->name) )
			return(pp); /* found it */
	return(NULL); /* not found */
}

/*
 * strsave(s)
 * Copy and save a string.
 */
static char *
strsave(s)
	char *s;
{
	char *p=NULL; 
	
	if ( (p = emalloc(strlen(s)+1) ) )
		strcpy(p,s);
	return(p);
}

/*
 * emalloc(size)
 * Allocate memory.
 */
static char *
emalloc(size)
	int size;
{
	char *p;

	if (! (p= (char*)malloc(size)))
		error(E_MALLOC);
	return(p);
}

		
/*
 * error (type, arg1, arg2)
 * Process errors according to the error type given.
 * Print an error message then exit.
 */
static error(type,arg1,arg2)
	ERROR type;
	char  *arg1,*arg2;
{
	fprintf(stderr,"%s: ",pgm_name);
        switch(type) {
	case E_MALLOC:
		fprintf(stderr,"FATAL: malloc failed\n");
		break;
	case E_WRITE:
		fprintf(stderr,"cannot open \"%s\" for writing\n",arg1);
		break;
	case E_READ:
		fprintf(stderr,"cannot open \"%s\" for reading\n",arg1);
		break;
        case E_CMD:
                fprintf(stderr,"usage: %s [-n] [-k src1.k [-k src2.k]...] [-i src1.h [-i src2.h]...] [-u prefix [-u prefix]...] [-l prefix] [src.m...]\n",pgm_name);
		break;
        case E_CHR:
                fprintf(stderr,"\"%s\": line %d: invalid input character '%c'\n",arg1,line,*(int*)arg2);    
		break;
        case E_MAXARG:
                fprintf(stderr,"\"%s\": line %d: exceeding %d arguments for predicate \"%s...\", please modify \"config.h\"\n",arg1,line,MAXARG,arg2);    
		break;
        case E_MAXTOK:
                fprintf(stderr,"\"%s\": line %d: token too long \"%s...\"\n",arg1,line,arg2);    
		break;
        case E_MAXSTR:
                fprintf(stderr,"input string too long \"%s...\"\n",arg1);    
		break;
        case E_EOF:
                fprintf(stderr,"\"%s\": line %d: unexpected end of file\n",arg1,line);    
		break;
        case E_ID:
                fprintf(stderr,"\"%s\": line %d: expecting an identifier at or near \"%s\"\n",arg1,line,arg2);    
		break;
        case E_SYNTAX:
                fprintf(stderr,"\"%s\": line %d: syntax error at or near \"%s\"\n",arg1,line,arg2);    
		break;
        case E_DUPNAME:
                fprintf(stderr,"\"%s\": line %d: duplicate predicate name \"%s\"\n",arg1,line,arg2);    
		break;
        }
        exit(1);
}
