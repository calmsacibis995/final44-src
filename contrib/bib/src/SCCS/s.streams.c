h59956
s 00046/00024/00131
d D 2.5 93/05/27 14:21:38 bostic 8 7
c new version from Dain Samples; checked in by TK
e
s 00014/00005/00141
d D 2.4 87/03/05 20:00:13 garrison 7 6
c nextrecord():  skip comments between references (beginning with #);
c getword():  When ignoring a line, also ignore followingnon-blank
c lines that don't begin with '%'.  Continuation lines were never being
c ignored. (mlvdv)
e
s 00011/00000/00135
d D 2.3 84/10/12 17:34:15 rrh 6 5
c add -d flag to all programs, to change the /usr/lib/bmac directory 
c to whatever the user wants; default is /usr/lib/bmac
e
s 00001/00000/00134
d D 2.2 83/09/23 15:45:29 garrison 5 3
c 
e
s 00002/00001/00133
d R 2.2 83/09/23 15:39:38 garrison 4 3
c Included changes from Arizona
e
s 00000/00000/00134
d D 2.1 83/06/22 14:24:49 garrison 3 2
c Make new release before sending it to Arizona for new changes.
e
s 00003/00001/00131
d D 1.2 83/06/14 16:47:37 rrh 2 1
c add sccs keywords per BSD conventions. Fix format strings so 
c pdp-11 style %D is now %ld, to not interact with sccs
e
s 00132/00000/00000
d D 1.1 83/06/06 11:37:29 garrison 1 0
c date and time created 83/06/06 11:37:29 by garrison
e
u
U
t
T
I 1
D 2
#
E 2
I 2
#ifndef lint
static char sccsid[] = "%W%	%G%";
#endif not lint
I 5
#
E 5
E 2

# include "stdio.h"
# include "streams.h"
# include "ctype.h"
I 8
# include "bib.h"
E 8

I 8

E 8
/*  getword(stream,p,ignore):
        read next sequence of nonspaces on current line into *p.
    null if no more words on current line.
D 7
    %x (x in ignore) terminates line.
E 7
I 7
    %x (x in ignore) terminates line and any following non-blank lines that
       don't begin with '%'
E 7
    all words of the form %a are returned as null.
    *p is a null terminated string (char p[maxstr]).
*/
D 8
getword(stream,p,ignore)
E 8
I 8
getword(stream,p,ignore,bolp)
E 8
FILE *stream;
char *p, *ignore;
D 8
{   char c;
E 8
I 8
int *bolp;
{   int c; /* will always contain the last character seen */
E 8
    char *oldp, *stop;
I 7
    long save;
I 8
    int newbolp;
E 8
E 7

    oldp= p;
    stop= p+maxstr-1;
    do{ c= getc(stream);
    }   while (isspace(c) && c!='\n');

    while (!isspace(c))
    {   *p= c;
        if (p < stop)  p++;
        c= getc(stream);
    }
    *p= NULL;

D 8
    if (oldp[0]=='%')
    {   oldp[0]= NULL;
        if (index(ignore, oldp[1]) != NULL)
D 7
            while (c!='\n') c=getc(stream);
E 7
I 7
	{   do{ while (c!='\n') c=getc(stream);
                save= ftell(stream);
                c= getc(stream);
	    }   while (c!= EOF && !isspace(c) && c!='%');
            pos(save);
	}
E 7
    }
E 8
I 8
    /* if line begins with %, then if following char is one to cause the
     * line to be ignored, then skip to \n.  If the following line is
     * a continuation line, then skip it as well.
     * small BUG in old version: ANY word that began with '%', whether
     * at the beginning of the line or not, could cause the rest of
     * the line to be ignored: this is not the advertised behavior. 
     * modified to ignore %x words, but they do not delete lines unless
     * they occur at the beginning of lines.  -ads
     */
   if (*bolp) {
      if (*oldp == '%') {
	 *oldp = NULL;
	 if (index(ignore, oldp[1]) != NULL) {   
	    do { 
	       while (c != '\n') c=getc(stream);
	       c= getc(stream);
	       }   while (c != EOF && !isspace(c) && c != '%');
	    ungetc(c, stream);
	    *bolp = true;
	    }
	 else *bolp = false;
	 }
      }
   else *bolp = (c == '\n' || c == EOF);
E 8
}



/*  recsize(stream,start):
    returns length of record beginning at start
    (record ends at blank line or eof)
    assumes and retains stream positioned at start
*/
long int recsize(stream,start)
FILE *stream;
long int start;
{   char c;                 /*  length = # of chars from start to beginning */
    long int length;        /*  of current line.  c in current line.        */
    int nonspaces;          /*  nonspaces = # of nonspaces in current line. */

    nonspaces= 0;
    c= getc(stream);
    length= 0L;

D 8
    while ( (c!='\n' || nonspaces!=0) && c!=EOF)
    {   if      (c=='\n')
        {   length= ftell(stream)-start;
            nonspaces= 0;
        }
        else if (!isspace(c))    nonspaces++;
E 8
I 8
    while ((c != '\n' || nonspaces != 0) && c != EOF) {   
      if (c == '\n') {   
	 length= ftell(stream)-start;
         nonspaces= 0;
	 }
      else if (!isspace(c)) nonspaces++;
E 8

D 8
        c= getc(stream);
    }
E 8
I 8
      c= getc(stream);
      }
E 8

    pos(start);
    return(length);
}


/*  nextrecord(stream,x): seeks in stream for first non-blank line
        at or after char x in stream. seeks to eof if x is past last record.
        x is the index of a character in the file (not eof).
    returns position in stream.  (returns EOF, if seeks to EOF)
I 8
    skips comment lines (those beginning with '#')
E 8
*/
long int nextrecord(stream,x)
FILE *stream;
long int x;
{   long int start;         /*  position of the beginning of the line  */
    char c;                 /*      containing c                       */

    pos(x);
    start= x;
    /*  find start of first non-blank record        */
I 7
        c= getc(stream);
E 7
        for(;;)
D 7
        {   c= getc(stream);
            if      (c=='\n')           start= ftell(stream);
            else if (!isspace(c))       break;
E 7
I 7
D 8
        {   if      (c=='\n')          {start= ftell(stream); c= getc(stream);}
            else if (c=='#')           while (c!='\n') c=getc(stream);
            else if (!isspace(c))      break;
            else                       c= getc(stream);
E 8
I 8
        {   if (c == '\n') { start= ftell(stream); c= getc(stream); }
	    else if (c == '#') {
	       /* skip any comment lines */
	       while (c != '\n') c=getc(stream);
	       }
            else if (isspace(c)) c= getc(stream);
	    else                 break;
E 8
E 7
        }

    if (feof(stream))   { pos(start);  start= EOF;  }
    else                pos(start);
    return(start);
}

/*  nextline(stream,x): seeks in stream after first newline at or after
        char x in stream. seeks to eof if x is in last line.
        x is the index of a character in the file (not eof).
    returns position in stream
*/
long int nextline(stream,x)
FILE *stream;
long int x;
{   pos(x);
    while (getc(stream)!='\n') ;
    return(ftell(stream));
}


/*  printline(stream): copies stream up to a newline
*/
printline(stream)
FILE *stream;
{   char c;
    while ((c=getc(stream)) != '\n' && c!=EOF)  putchar(c);
    putchar('\n');
}

/*  getline(stream,p):  store in *p next chars in stream up to \n
        advance stream past \n.
    limit of  maxstr-1 chars may be stored at p.
*/
getline(stream,p)
FILE *stream;
char *p;
{   char *stop;
    stop= p+maxstr-1;
    while ( (*p= getc(stream)) != '\n' && *p!=EOF)
        if (p<stop)    p++;
    *p= NULL;
}
I 6

/* replace string old at the head of subj by new */
strreplace(subj, old, new)
	char *subj, *old, *new;
{
	char buf[128];
	int lg;
	strcpy(buf, &subj[strlen(old)]);
	strcpy(subj, new);
	strcat(subj, buf);
}
E 6
E 1
