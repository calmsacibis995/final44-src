/* $XConsortium: looper.lex,v 5.1 91/02/16 09:59:57 rws Exp $ */
/* copyright notice at the end of file */

/*looper.lex: scanner rules for Newt				*/



ID	[a-zA-Z0-9_\$#]*
AR	[-a-zA-Z0-9_\|\+\/\*\=\&\:\$#\.~\[\]\{\}\%\<\>\^\!\\\'\`\?\@]*
INSTR	[ \,\;\(\)]
VA	@[a-zA-Z][a-zA-Z0-9_]*

/* increase size of output table */
%a 30000
%o 8000
%start CMT
%%
^"@#".*		;	/* ignore pca-style comments */
"#".*		{yylval.strval = yytext; return(SHCOMMENT);}
\/\*+\/		;
\/\*+		{BEGIN CMT;}
<CMT>[^\n]*\*\/ {BEGIN 0;}
<CMT>[^\n]*     ;
<CMT>\n		lineno++;
\(		return(LEFT);
\)		return(RIGHT);
\;		return(SEMI);
\,		return(COMMA);
\=		return(EQUAL);
foreach		{if (debug) push(FOREACHSTACK,lineno);return(FOREACH);}
for		{if (debug) push(FORSTACK,lineno);return(FOR);}
end		return(END);
if		{if (debug) push(IFSTACK,lineno);return(IF);}
then		return(THEN);
else		return(ELSE);
endif		return(ENDIF);
macro		return(MACRO);
endmacro	return(ENDMACRO);
source		return(READFILE);
resume		{if (fileindex>0) {
			fclose(yyin);
			yyin=filestack[--fileindex];
			lineno = filelinestack[fileindex];
			filename = filenamestack[fileindex];
			if (debug) N_debuguse(filename);
			if (interactive && fileindex==0) fprintf(stderr,">");
			return(RESUME);
		 } else {
			return(0);
		 }
		}
{ID}		{yylval.strval = yytext; return(IDENT);}
{VA}		{yylval.strval = yytext; return(VAR);}
({AR}|\"({AR}|{INSTR})*\")	{
		/* In string arguments (between double quotes), 
		* spaces, commas, etc. are allowed.
		*/
		yylval.strval = yytext; return(ARG);}
[ \t]		;	/*ignore whitespace */
\n		{
			lineno++;
			if (interactive && fileindex==0) fprintf(stderr,"> ");
		}
%%

/*****************************************************************
Copyright (c) 1989, 1990, 1991,1990 by Sun Microsystems, Inc. and the X Consortium.

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


