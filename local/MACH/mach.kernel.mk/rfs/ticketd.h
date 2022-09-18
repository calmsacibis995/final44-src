/*
 * HISTORY
 * $Log:	ticketd.h,v $
 * Revision 2.3  91/11/05  18:28:28  mja
 * 	Add ticketd request union for all request message formats and
 * 	declare maximum size ticket file pathname lengths in each
 * 	request structure so that a client module can allocate them
 * 	without needing to access the ticket file data structures.
 * 	[91/11/05  00:36:32  mja]
 * 
 * Revision 2.2  91/08/01  15:25:46  berman
 * 	Added DESTTKT request type.
 * 	[91/07/23  15:19:09  chs]
 * 
 * 	Created.
 * 	[91/07/22  11:57:28  chs]
 * 
 */
/*
 *
 *  Data structures and defines for interacting with the ticketd.
 *
 */
#ifndef _RFS_TICKETD_H_
#define _RFS_TICKETD_H_

/*
 *  constants from kerberos's krb.h
 */

/* Definition of text structure used to pass text around */
#define		MAX_KTXT_LEN	1250

/* The maximum sizes for aname, realm, sname, and instance +1 */
#define 	ANAME_SZ	40
#define		REALM_SZ	40
#define		SNAME_SZ	40
#define		INST_SZ		40
/* include space for '.' and '@' */
#define		MAX_K_NAME_SZ	(ANAME_SZ + INST_SZ + REALM_SZ + 2)


/*
 *  pathname to ticketd socket
 */

#define TICKETD_SOCKET_PATH "/dev/ticketd/socket"

/*
 *  request types
 */

#define TICKETD_REQ_GENERIC	0
#define TICKETD_REQ_RFS		1
#define TICKETD_REQ_DESTTKT	2

struct ticketd_reqheader {
    int		uid;
    int		type;
};

struct ticketd_req_generic {
    struct ticketd_reqheader header;

    u_short	pathlen;
    char	service[MAX_K_NAME_SZ];
    char	path[MLEN+1];
};

struct ticketd_req_rfs {
    struct ticketd_reqheader header;

    u_short	pathlen;
    struct in_addr  addr;
    char	path[MLEN+1];
};

struct ticketd_req_desttkt {
    struct ticketd_reqheader header;

    u_short	pathlen;
    char	path[MLEN+1];
};

union ticketd_req_un {
    struct ticketd_req_desttkt desttkt;
    struct ticketd_req_generic generic;
    struct ticketd_req_rfs     rfs;
};

/*
 *  reply structures
 */

struct ticketd_reply {
    char    service[ANAME_SZ];	/* Service name */
    char    instance[INST_SZ];	/* Instance */
    char    realm[REALM_SZ];	/* Auth domain */
    char    session[8];		/* Session key */
    int     lifetime;		/* Lifetime */
    int     kvno;		/* Key version number */
    long    issue_date;		/* The issue time */
    long    expr_date;		/* The expiration time */
    char    pname[ANAME_SZ];	/* Principal's name */
    char    pinst[INST_SZ];	/* Principal's instance */

    int		authlen;		/* length of the authenticator */
    int		ticketlen;		/* length of the ticket */
    /* the ticket is included in the authenticator */
    int		ticketoffset;
    char	auth[MAX_KTXT_LEN];	/* the authenticator */
};

#endif _RFS_TICKETD_H_
