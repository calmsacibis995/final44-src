
/* $XConsortium: errhandle1.c,v 5.2 91/07/12 18:27:56 hersh Exp $ */

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
 ## errhandle1.c:
 ## Verify that error output is directed to standard error by default,
 ## or to the specified error file.
 ## Verify the default error handling mode is OFF, set and inquire the current
 ## error handling mode.
 ## Verify that if error handling mode is turn OFF, no error messages
 ## are genreated.
*/


#include "phigs/phigs.h"
#include "fcntl.h"
#include "sys/stat.h"

#define ERRFILE "errorfile"

int redirect_stderr();

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

	tbegintest("errhandle1","test error output file and error mode");

	/* test that default error output goes to stderr */

	unlink(ERRFILE);
	popen_phigs(NULL, PDEF_MEM_SIZE);
	pcreate_store(&err,&store);
	if (err) printf("error %d in pcreate_store",err);

	ei.escape_in_u1.sync_on = PERRSYNC_ON;
        pescape(PUESC_ERRSYNC, &ei, store, &eo);

	fd = redirect_stderr(ERRFILE);
	pclose_struct();
	if (fstat(fd,&statbuf) == -1)
		puts("error in fstat()");
	if (statbuf.st_size <=0)
		tfprintf("failed: output to stderr, file size = %d\n",
			statbuf.st_size);
	pclose_phigs();

	/* test that error output goes to user specfied file */

	unlink(ERRFILE);
	popen_phigs(ERRFILE, PDEF_MEM_SIZE);
	ei.escape_in_u1.sync_on = PERRSYNC_ON;
        pescape(PUESC_ERRSYNC, &ei, store, &eo);

	pclose_struct();
	if (stat(ERRFILE,&statbuf) == -1)
		puts("error in stat()");
	if (statbuf.st_size <=0)
		tfprintf("failed: output to errorfile, file size = %d\n",
			statbuf.st_size);
	pclose_phigs();


	/* testing error handling mode */

	unlink(ERRFILE);
	popen_phigs(ERRFILE, PDEF_MEM_SIZE);
	ei.escape_in_u1.sync_on = PERRSYNC_ON;
        pescape(PUESC_ERRSYNC, &ei, store, &eo);

	/* test that default error handling mode is ON */
	
	pinq_err_hand_mode(&err,&mode);
	if (err)
		printf("error %d in pinq_err_hand_mode",err);
        if (mode != PERR_ON) 
                tfprintf("failed: default err hand mode=%d,expected %d\n",
                        mode,PERR_ON);

	/* set error handling mode to OFF */
	pset_err_hand_mode(PERR_OFF);

	/* verify that error handling mode is set to OFF */
	pinq_err_hand_mode(&err,&mode);
	if (err)
		printf("error %d in pinq_err_hand_mode",err);
        if (mode != PERR_OFF) 
                tfprintf("failed: current err hand mode=%d,expected %d\n",
                        mode,PERR_OFF);

	/* 
	 * verify that when error handling mode is OFF, no error 
	 * output is generated  
	 */

	pclose_struct();
	if (stat(ERRFILE,&statbuf) != -1) {
		tfprintf("failed: error handling not disabled, file size=%d\n",
			statbuf.st_size);
	}
	pdel_store(store);
	pclose_phigs();

	tendtest();
}

/* 
 * redirect_stderr(filename)
 * redirect standard error to the specified file, return the file descriptor
 */

int
redirect_stderr(filename)
	char *filename;
{
	int fd;

	fd = open(ERRFILE,O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		puts("error in open()");
	if (close(2) == -1)
		puts("error in close()");
	if (dup(fd) != 2)
		puts("error in dup()");
	return(fd);
}

