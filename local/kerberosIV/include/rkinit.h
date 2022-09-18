/* 
 * $Id: rkinit.h,v 1.1 1994/06/29 23:04:35 dglo Exp dglo $
 * $Source: /a/guest/dglo/nuk/include/RCS/rkinit.h,v $
 * $Author: dglo $
 *
 * Main header file for rkinit library users
 */

#ifndef __RKINIT_H__
#define __RKINIT_H__

#if !defined(lint) && !defined(SABER) && !defined(LOCORE) && defined(RCS_HDRS)
static char *rcsid_rkinit_h = "$Id: rkinit.h,v 1.1 1994/06/29 23:04:35 dglo Exp dglo $";
#endif /* lint || SABER || LOCORE || RCS_HDRS */

#include "bit32.h"
#include <des.h>
#include <krb.h>
#include <sys/param.h>

#ifdef __STDC__
#define RK_PROTO(x) x
#else
#define RK_PROTO(x) ()
#endif /* __STDC__ */

typedef struct {
    char aname[ANAME_SZ + 1];
    char inst[INST_SZ + 1];
    char realm[REALM_SZ + 1];
    char sname[ANAME_SZ + 1];
    char sinst[INST_SZ + 1];
    char username[9];		/* max local name length + 1 */
    char tktfilename[MAXPATHLEN + 1];
    BIT32 lifetime;
} rkinit_info;

#define RKINIT_SUCCESS 0

/* Function declarations */
extern int rkinit RK_PROTO((char *, char *, rkinit_info *, int));
extern char *rkinit_errmsg RK_PROTO((char *));

#endif /* __RKINIT_H__ */
