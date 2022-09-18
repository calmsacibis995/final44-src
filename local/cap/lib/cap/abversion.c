/*
 *  Author: cck    Date: 88/03/19 19:56:46  
 *  Header: abversion.c,v 1.3 88/03/19 19:56:46 cck Rel  
 *  Revision: 1.3  
*/

/*
 * abversion.c - Return version information
 *
 * Copyright (c) 1988 by The Trustees of Columbia University 
 *  in the City of New York.
 *
 *
 * Edit History:
 *
 *  March 1988    CCKim	Created.
 *
 */

#include <netat/appletalk.h>

private struct cap_version myversion;

struct cap_version *
what_cap_version()
{
  extern char Columbia_Copyright[];

  myversion.cv_copyright = Columbia_Copyright;
  myversion.cv_name = "CAP";
  myversion.cv_version = 5;
  myversion.cv_subversion = 0;
  myversion.cv_type = "UDP encapsulation";
  myversion.cv_rmonth = "March";
  myversion.cv_ryear = "1988";
  return(&myversion);
}
