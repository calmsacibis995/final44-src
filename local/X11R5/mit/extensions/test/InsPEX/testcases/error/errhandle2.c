
/* $XConsortium: errhandle2.c,v 5.2 91/07/12 18:28:20 hersh Exp $ */

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
 ## errhand2.c:
 ## Install an error handler, verify that it is called upon a PHIGS error.
 ##
*/


#include "phigs/phigs.h"
#include "fcntl.h"
#include "sys/stat.h"

#define ERRFILE "errorfile"
int flag = 0;

main(argc, argv)
   int argc; char *argv[];
{
	Pint            err;
	Pescape_in_data ei;
	Pescape_out_data *eo;
	int fd;
	struct stat statbuf;
	Perr_mode mode;
        Pstore store;

	tbegintest("errhandle2","test user installed error handler");

	unlink(ERRFILE);
	popen_phigs(ERRFILE, PDEF_MEM_SIZE);
        pcreate_store(&err,&store);
	ei.escape_in_u1.sync_on = PERRSYNC_ON;
        pescape(PUESC_ERRSYNC, &ei,store, &eo);

	pclose_struct();
	if (flag != 1)
		tfprintf("failed: user installed error handler not called\n");
	if (stat(ERRFILE,&statbuf) == -1)
		puts("error in stat()");
	if (statbuf.st_size <=0)
		tfprintf("failed: output to errorfile, file size = %d\n",
			statbuf.st_size);
	pdel_store(store);
	pclose_phigs();

	tendtest();

}

/*
 * perr_hand(errnum,funcnum,fname)
 * user specified error handling function
 */ 
void
perr_hand(errnum,funcnum,fname)
	Pint errnum;
	Pint funcnum;
	char *fname;
{
	flag = 1;
	if (errnum !=  PE_NOT_STOP)
		tfprintf("failed: error number = %d, expected %d\n", 
			errnum,PE_NOT_STOP);
	if (funcnum !=  Pfn_close_struct)
		tfprintf("failed: error number = %d, expected %d\n", 
			errnum,Pfn_close_struct);
	if (strcmp(fname,ERRFILE) != 0)
		tfprintf("failed: function name = %s, expected %s\n", 
			fname,ERRFILE);
	perr_log(errnum,funcnum,fname);
}
