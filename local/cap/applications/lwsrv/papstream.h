/* " Author: cck    Date: 87/09/05 17:23:10  " */
/* " Header: papstream.h,v 1.1 87/09/05 17:23:10 cck Rel  " */
/* " Revision: 1.1  " */

/*
 * papstream - UNIX AppleTalk: simple stream handling for pap connections
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986,1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  Created sept 5, 1987 by cck from lwsrv
 *
 */

typedef struct {			/* PAP stream interface PFILE */
  int p_cno;				/* pap connection number */
  int p_cnt;				/* count of chars in ptr */
  int p_flg;				/* flags */
  char *p_ptr;				/* ptr to input chars */
  char *p_buf;				/* buf for input */
  int p_bufsiz;				/* size of buffer */
} p_iobuf, PFILE;

#define P_IOEOF 020			/* eof occured */
#define P_IOCLS 040			/* pap stream is closed */
#define P_IOERR 0100			/* error occured */

#define p_eof(p)	(((p)->p_flg & P_IOEOF) != 0)
#define p_iscls(p)	(((p)->p_flg & P_IOCLS) != 0)
#define p_clrcls(p)	(((p)->p_flg &= ~P_IOCLS))
#define p_isopn(p)	(((p)->p_flg & P_IOCLS) == 0)
#define p_papcno(p)	((p)->p_cno)
  
/* Fast mode - just comment out if you want to use routine instead */
#define p_getc(p) ((--((p)->p_cnt) < 0) ? p_fillbuf(p) : 0xff&(*(p)->p_ptr++))

void p_clreof();
PFILE *p_opn();
void p_cls();
void p_write();
int p_fillbuf();
#ifndef p_getc
int p_getc();
#endif
