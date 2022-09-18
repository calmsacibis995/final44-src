/* $XConsortium: err.h,v 5.1 91/02/16 09:49:04 rws Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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

#ifndef PHG_ERR_H_INCLUDED
#define PHG_ERR_H_INCLUDED

#define ERR_SET_CUR_FUNC( erh, funcnum) \
    ((erh)->cur_func_num = (funcnum))

#define ERR_BUF( erh, errnum) \
    if ( (erh)->mode == PERR_ON) (*(erh)->buf_func)((erh), (errnum))

#define ERR_FLUSH( erh) \
    if ( (erh)->flush_func) (*(erh)->flush_func)( erh)

/* ERR_HANDLE calls the global error handler function */
#define ERR_HANDLE( errnum, funcnum, erf) \
    (*phg_errhandle)((errnum), (funcnum), (erf))

/*** ERR_REPORT called by binding only ***/
#define ERR_REPORT( erh, errnum) \
    if ( (erh)->mode == PERR_ON && (erh)->report_func) \
	(*(erh)->report_func)((erh), (errnum))

/*** ERR_DESTROY called by error code only ***/
#define ERR_DESTROY( erh) \
    if ( (erh)->destroy_func) (*(erh)->destroy_func)(erh)

typedef struct {
    Pint	errnum;
    Pint	funcnum;
} Err_msg;

typedef struct {
    char	*fname;	/* error file name */
} Err_local_data;

typedef struct {
    int		sfd;	/* socket fd for errors from server */
    char	*fname;	/* error file name */
} Err_client_data;

typedef struct {
    int		sfd;		/* fd to write to client */
} Err_remote_data;

typedef struct {
    Perr_mode	mode;
    Perr_mode	err_state;	/* NOT maintained in server */
    int		cur_func_num;
    int		errno;
    void	(*buf_func)();
    void	(*flush_func)();
    void	(*report_func)();
    void	(*destroy_func)();
    union {
	Err_local_data		local;
	Err_client_data		client;
	Err_remote_data		remote;
    }		data;
} Err_struct;

typedef Err_struct	*Err_handle;

extern Err_handle	phg_err_init_local();
extern Err_handle	phg_err_init_client();
extern Err_handle	phg_err_init_remote();

/* declare the global error handler function pointer. */
extern void		(*phg_errhandle)();

#endif
