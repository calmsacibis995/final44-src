
/* $XConsortium: utility.m,v 5.1 91/02/16 10:00:05 rws Exp $ */

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


/****************************************************************/
/*  utility.m: general utility functions			*/
/****************************************************************/

/*********** user's function ***************/
/*
 * Integer, Logical, and Boolean Math functions
 */
int 	plus(int,int)		/* 1st arg gets result of oper */
int 	minus(int,int)		/* performed on later args */
int 	multiply(int,int)
int 	divide(int,int)
int 	equal(int,int)
int 	ifval(int,int,int)	/* like a = b ? c : d; in C lang. */
int 	and(int,int)		/* logical */
int 	or(int,int)
int 	not(int)
int 	bitand(int,int)		/* bit-wise */
int 	bitor(int,int)
int 	bitnot(int)

/* floating point functions */
double 	ftod(float)		/* coverted a float to a double */
int 	fequal(float,float)	/* check equality of two floats */
float 	fplus(float,float)	/* 1st arg gets result of oper */
float 	fminus(float,float)	/* performed on later args */
float 	fmultiply(float,float)
float 	fdivide(float,float)

/*
 * Input/Output Functions
 */
!void	printf(char*,VARARG)
void 	beep()

/*********** Unix, C's function ***************/
/* 
 * C library functions and UNIX system calls
 */
void 	sleep(int)

/* memory functions */
char* 	malloc(int)
void	free(char*)  
 
/*string functions */
char*	strcat(char*, char*)
int 	strcmp(char*,char*)
char* 	strcpy(char*,char*)
int 	strlen(char*)

/* env functions */
char*	getenv(char*)
int	getchar()

void    system(char*)
void 	unlink(char*)
