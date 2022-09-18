/* 
 * Copyright 1987 by the Massachusetts Institute of Technology.
 *
 * For copying and distribution information,
 * please see the file <mit-copyright.h>.
 *
 * $Revision: 1.2 $
 * $Date: 1994/01/21 00:11:14 $
 * $State: Exp $
 * $Source: /usr/sww/share/src/kerberosIV/kerberosIV/kprop/RCS/kprop.h,v $
 * $Author: dglo $
 * $Locker:  $
 *
 * $Log: kprop.h,v $
 * Revision 1.2  1994/01/21  00:11:14  dglo
 * Moved paths into include/krb_paths.h
 *
 * Revision 1.1  1994/01/20  23:15:32  dglo
 * Initial revision
 *
 * Revision 4.1  92/10/23  15:45:13  tytso
 * Change the location of KPROP_KDBUTIL to be /kerberos/bin/kdb_util.
 * 
 * Revision 4.0  89/01/24  18:44:46  wesommer
 * Original version; programmer: wesommer
 * auditor: jon
 * 
 */

#define KPROP_SERVICE_NAME "rcmd"
#define TGT_SERVICE_NAME "krbtgt"
#define KPROP_PROT_VERSION_LEN 8
#define KPROP_PROT_VERSION "kprop01"
#define KPROP_TRANSFER_PRIVATE 1
#define KPROP_TRANSFER_SAFE 2
#define KPROP_TRANSFER_CLEAR 3
#define KPROP_BUFSIZ 32768
