/* 
 *
 * Copyright 1987 by the Massachusetts Institute of Technology.
 *
 * For copying and distribution information,
 * please see the file <mit-copyright.h>.
 *
 * $UCB$
 * $Revision: 1.3 $
 * $Date: 1994/02/08 17:50:42 $
 * $State: Exp $
 * $Source: /a/guest/dglo/nuk/kpropd/RCS/kpropd.c,v $
 * $Author: dglo $
 * $Locker: dglo $
 *
 * $Log: kpropd.c,v $
 * Revision 1.3  1994/02/08  17:50:42  dglo
 * Get things working
 *
 * Revision 1.2  1994/01/21  00:12:28  dglo
 * Use paths from include/krb_paths.h
 * Get things compiling cleanly in our environment
 *
 * Revision 1.1  1994/01/20  23:08:29  dglo
 * Initial revision
 *
 * Revision 1.2  1993/08/03  00:17:49  dglo
 * HP-UX bug fixes
 *
 * Revision 1.1  1993/07/29  21:44:11  dglo
 * Initial revision
 *
 * Revision 4.5  92/10/23  15:45:46  tytso
 * Make it possible to specify the location of the kdb_util program.
 * 
 * Revision 4.4  91/06/15  03:20:51  probe
 * Fixed <sys/types.h> inclusion
 * 
 * Revision 4.3  89/05/16  15:06:04  wesommer
 * Fix operator precedence stuff.
 * Programmer: John Kohl.
 * 
 * Revision 4.2  89/03/23  10:24:00  jtkohl
 * NOENCRYPTION changes
 * 
 * Revision 4.1  89/01/24  20:33:48  root
 * name change
 * 
 * Revision 4.0  89/01/24  18:45:06  wesommer
 * Original version; programmer: wesommer
 * auditor: jon
 * 
 * Revision 4.5  88/01/08  18:07:46  jon
 * formatting and rcs header changes
 */

/*
 * This program is run on slave servers, to catch updates "pushed"
 * from the master kerberos server in a realm.
 */

#ifndef	lint
static char rcsid_kpropd_c[] =
"$Header: /a/guest/dglo/nuk/kpropd/RCS/kpropd.c,v 1.3 1994/02/08 17:50:42 dglo Exp dglo $";
#endif	lint

#include <mit-copyright.h>

#include <ctype.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <des.h>
#include <krb.h>
#include <krb_db.h>
#include <klog.h>
#include <prot.h>
#include <kdc.h>

#include "kprop.h"

#ifdef SWW
#include "krb_paths.h"
#include "compat-proto.h"
#else /* !SWW */
#include "pathnames.h"
#endif /* SWW */
#include "sys_proto.h"

static char kprop_version[KPROP_PROT_VERSION_LEN] = KPROP_PROT_VERSION;

extern int errno;
extern char *sys_errlist[];
int     debug = 0;

const char   *logfile = _PATH_KPROP_LOG;
const char   *master = KRB_MASTER;

char    errmsg[256];
int     pause_int = 300;	/* 5 minutes in seconds */

static void usage __P((void));
int main __P((int, char **));
static void recv_clear __P((int, int));
static void recv_auth __P((int, int, int, struct sockaddr_in *,
			   struct sockaddr_in *, AUTH_DAT *));
static void SlowDeath __P((void));
static unsigned long get_data_checksum __P((int, Key_schedule));

static char    buf[KPROP_BUFSIZ+64 /* leave room for private msg overhead */];

static void usage()
{
    fprintf(stderr, "\nUsage: kpropd [-r realm] [-s srvtab] [-l logfile] [-P kdb_util]\n\t\t[-m master] fname\n\n");
    SlowDeath();
}

int
main(argc, argv)
    int     argc;
    char  **argv;
{
    struct sockaddr_in from;
    struct sockaddr_in sockin;
    struct servent *sp;
    int     s, s2, fd, n, fdlock;
    int     from_len;
    char    local_file[256];
    char    local_temp[256];
    struct hostent *hp;
    char    hostname[256];
    char    from_str[128];
    long    kerror;
    AUTH_DAT auth_dat;
    KTEXT_ST ticket;
    char my_instance[INST_SZ];
    char my_realm[REALM_SZ];
    char cmd[1024];
    short net_transfer_mode, transfer_mode;
    Key_schedule session_sched;
    char version[9];
    int c;
    extern char *optarg;
    extern int optind;
    int rflag = 0;
    const char *srvtab = _PATH_KRB_SRVTAB;
    const char *local_db = _PATH_KDB_DBMFILE;
    const char *kdb_util = _PATH_KDB_UTIL;

    if (argv[argc - 1][0] == 'k' && isdigit(argv[argc - 1][1])) {
	argc--;			/* ttys file hack */
    }
    while ((c = getopt(argc, argv, "r:s:d:l:m:P:")) != EOF) {
	switch(c) {
	case 'r':
	    rflag++;
	    strcpy(my_realm, optarg);
	    break;
	case 's':
	    srvtab = optarg;
	    break;
	case 'd':
	    local_db = optarg;
	    break;
	case 'l':
	    logfile = optarg;
	    break;
        case 'm':
	    {
		char *c = strchr(optarg, '.');

		if (c)
		    *c = 0;
		master = optarg;
	    }
	    break;
        case 'P':
	    kdb_util = optarg;
	    break;
	default:
	    usage();
	    break;
	}
    }
    if (optind != argc-1)
	usage();

    kset_logfile(logfile);

    klog(L_KRB_PERR, "\n\n***** kpropd started *****");

    strcpy(local_file, argv[optind]);
    strcat(strcpy(local_temp, argv[optind]), ".tmp");

    if ((sp = getservbyname("krb_prop", "tcp")) == NULL) {
	klog(L_KRB_PERR, "kpropd: tcp/krb_prop: unknown service.");
	SlowDeath();
    }
    bzero(&sockin, sizeof sockin);
    sockin.sin_port = sp->s_port;
    sockin.sin_family = AF_INET;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	sprintf(errmsg, "kpropd: socket: %s", sys_errlist[errno]);
	klog(L_KRB_PERR, errmsg);
	SlowDeath();
    }
    if (bind(s, (struct sockaddr *)&sockin, sizeof sockin) < 0) {
	sprintf(errmsg, "kpropd: bind: %s", sys_errlist[errno]);
	klog(L_KRB_PERR, errmsg);
	SlowDeath();
    }
 
    if (!rflag) {
	kerror = krb_get_lrealm(my_realm,1);
	if (kerror != KSUCCESS) {
	    sprintf (errmsg, "kpropd: Can't get local realm. %s",
		     krb_err_txt[kerror]);
	    klog (L_KRB_PERR, errmsg);
	    SlowDeath();
	}
    }
    
    if (gethostname(my_instance, sizeof(my_instance)) != 0) {
	sprintf(errmsg, "kpropd: gethostname: %s", sys_errlist[errno]);
	klog(L_KRB_PERR, errmsg);
	SlowDeath();
    } else {
      char *c = strchr(my_instance, '.');

      if (c)
	*c = 0;
    }

    listen(s, 5);
    for (;;) {
	from_len = sizeof from;
	if ((s2 = accept(s, (struct sockaddr *)&from, &from_len)) < 0) {
	    sprintf(errmsg, "kpropd: accept: %s", sys_errlist[errno]);
	    klog(L_KRB_PERR, errmsg);
	    continue;
	}
	strcpy(from_str, inet_ntoa(from.sin_addr));

	if ((hp = gethostbyaddr((char *)&(from.sin_addr.s_addr),
				sizeof(from.sin_addr), AF_INET)) == NULL) {
	    strcpy(hostname, "UNKNOWN");
	} else {
	    strcpy(hostname, hp->h_name);
	}

	sprintf(errmsg, "Connection from %s, %s", hostname, from_str);
	klog(L_KRB_PERR, errmsg);

	/* for krb_rd_{priv, safe} */
	n = sizeof sockin;
	if (getsockname (s2, (struct sockaddr *)&sockin, &n) != 0) {
	    fprintf (stderr, "kpropd: can't get socketname.\n");
	    perror ("getsockname");
	    SlowDeath();
	}
	if (n != sizeof (sockin)) {
	    fprintf (stderr, "kpropd: can't get socketname. len");
	    SlowDeath();
	}

	if ((fdlock = open(local_temp, O_WRONLY | O_CREAT, 0600)) < 0) {
	    sprintf(errmsg, "kpropd: open: %s", sys_errlist[errno]);
	    klog(L_KRB_PERR, errmsg);
	    SlowDeath();
	}
	if (flock(fdlock, LOCK_EX | LOCK_NB)) {
	    sprintf(errmsg, "kpropd: flock: %s", sys_errlist[errno]);
	    klog(L_KRB_PERR, errmsg);
	    SlowDeath();
	}
	if ((fd = creat(local_temp, 0600)) < 0) {
	    sprintf(errmsg, "kpropd: creat: %s", sys_errlist[errno]);
	    klog(L_KRB_PERR, errmsg);
	    SlowDeath();
	}
	if ((n = read (s2, buf, sizeof (kprop_version)))
	    != sizeof (kprop_version)) {
	    klog (L_KRB_PERR, "kpropd: can't read kprop protocol version str.");
	    SlowDeath();
	}
	if (strncmp (buf, kprop_version, sizeof (kprop_version))
	    != 0) {
	    sprintf (errmsg, "kpropd: unsupported version %s", buf);
	    klog (L_KRB_PERR, errmsg);
	    SlowDeath();
	}

	if ((n = read (s2, &net_transfer_mode, sizeof (net_transfer_mode)))
	    != sizeof (net_transfer_mode)) {
	    klog (L_KRB_PERR, "kpropd: can't read transfer mode.");
	    SlowDeath();
	}
	transfer_mode = ntohs (net_transfer_mode);
	kerror = krb_recvauth(KOPT_DO_MUTUAL, s2, &ticket,
			      KPROP_SERVICE_NAME,
			      my_instance,
			      &from,
			      &sockin,
			      &auth_dat,
			      srvtab,
			      session_sched,
			      version);
	if (kerror != KSUCCESS) {
	    sprintf (errmsg, "kpropd: %s: Calling getkdata", 
		     krb_err_txt[kerror]);
	    klog (L_KRB_PERR, errmsg);
	    SlowDeath();
	}
	
	/* AUTHORIZATION is done here.  We might want to expand this to
	 * read an acl file at some point, but allowing for now
	 * KPROP_SERVICE_NAME.master@local-realm is fine ... */

	if ((strcmp (KPROP_SERVICE_NAME, auth_dat.pname) != 0) ||
	    (strcmp (master, auth_dat.pinst) != 0) ||
	    (strcmp (my_realm, auth_dat.prealm) != 0)) {
	    klog (L_KRB_PERR, "Authorization denied!");
	    SlowDeath();
	}

	switch (transfer_mode) {
	case KPROP_TRANSFER_PRIVATE: 
	    recv_auth (s2, fd, 1 /* private */, &from, &sockin, &auth_dat);
	    break;
	case KPROP_TRANSFER_SAFE: 
	    recv_auth (s2, fd, 0 /* safe */, &from, &sockin, &auth_dat);
	    break;
	case KPROP_TRANSFER_CLEAR: 
	    recv_clear (s2, fd);
	    break;
	default: 
	    sprintf (errmsg, "kpropd: bad transfer mode %d", transfer_mode);
	    klog (L_KRB_PERR, errmsg);
	    SlowDeath();
	}

	if (transfer_mode != KPROP_TRANSFER_PRIVATE) {
	    klog(L_KRB_PERR, "kpropd: non-private transfers not supported\n");
	    SlowDeath();
#ifdef doesnt_work_yet
	    lseek(fd, (long) 0, L_SET);
	    if (auth_dat.checksum != get_data_checksum (fd, session_sched)) {
		klog(L_KRB_PERR, "kpropd: checksum doesn't match");
		SlowDeath();
	    }
#endif
	} else

        {
	    struct stat st;
	    fstat(fd, &st);
	    if (st.st_size != auth_dat.checksum) {
		klog(L_KRB_PERR, "kpropd: length doesn't match");
		SlowDeath();
	    }
	}
	close(fd);
	close(s2);

	if (rename(local_temp, local_file) < 0) {
	    sprintf(errmsg, "kpropd: rename: %s", sys_errlist[errno]);
	    klog(L_KRB_PERR, errmsg);
	    SlowDeath();
	}

	if (flock(fdlock, LOCK_UN)) {
	    sprintf(errmsg, "kpropd: flock (unlock): %s",
		    sys_errlist[errno]);
	    klog(L_KRB_PERR, errmsg);
	    SlowDeath();
	}
	close(fdlock);
	sprintf(cmd, "%s load %s %s\n", kdb_util, local_file,
		local_db);
	if (system (cmd) != 0) {
	    klog (L_KRB_PERR, "Couldn't load database");
	    SlowDeath();
	}
	klog(L_KRB_PERR, "Loaded %s", local_file);
    }
}

static void
recv_auth (in, out, private, remote, local, ad)
     int in, out;
     int private;
     struct sockaddr_in *remote, *local;
     AUTH_DAT *ad;
    {
      u_long length;
      long kerror;
      int n;
      MSG_DAT msg_data;
      Key_schedule session_sched;

      if (private)
#ifdef NOENCRYPTION
	bzero((char *)session_sched, sizeof(session_sched));
#else
	if (key_sched (ad->session, session_sched)) {
	  klog (L_KRB_PERR, "kpropd: can't make key schedule");
	  SlowDeath();
	}
#endif

      while (1) {
	n = krb_net_read (in, &length, sizeof length);
	if (n == 0) break;
	if (n < 0) {
	  sprintf (errmsg, "kpropd: read: %s", sys_errlist[errno]);
	  klog (L_KRB_PERR, errmsg);
	  SlowDeath();
	}
	length = ntohl (length);
	if (length > sizeof buf) {
	  sprintf (errmsg, "kpropd: read length %d, bigger than buf %d",
		   length, sizeof buf);
	  klog (L_KRB_PERR, errmsg);
	  SlowDeath();
	}
	n = krb_net_read(in, buf, length);
	if (n < 0) {
	  sprintf(errmsg, "kpropd: read: %s", sys_errlist[errno]);
	  klog(L_KRB_PERR, errmsg);
	    SlowDeath();
	  }
	if (private)
	  kerror = krb_rd_priv (buf, n, session_sched, ad->session, 
				remote, local, &msg_data);
	else
	  kerror = krb_rd_safe (buf, n, ad->session,
				remote, local, &msg_data);
	if (kerror != KSUCCESS) {
	  sprintf (errmsg, "kpropd: %s: %s",
		   private ? "krb_rd_priv" : "krb_rd_safe",
		   krb_err_txt[kerror]);
	  klog (L_KRB_PERR, errmsg);
	  SlowDeath();
	}
	if (write(out, msg_data.app_data, msg_data.app_length) != 
	    msg_data.app_length) {
	  sprintf(errmsg, "kpropd: write: %s", sys_errlist[errno]);
	  klog(L_KRB_PERR, errmsg);
	  SlowDeath();
	}
      }
    }

static void
recv_clear (in, out)
    int in, out;
    {
      int n;

      while (1) {
	n = read (in, buf, sizeof buf);
	if (n == 0) break;
	if (n < 0) {
	    sprintf (errmsg, "kpropd: read: %s", sys_errlist[errno]);
	    klog (L_KRB_PERR, errmsg);
	    SlowDeath();
	  }
	if (write(out, buf, n) != n) {
	      sprintf(errmsg, "kpropd: write: %s", sys_errlist[errno]);
	      klog(L_KRB_PERR, errmsg);
	      SlowDeath();
	    }
      }
    }

static void 
SlowDeath()
{
    klog(L_KRB_PERR, "kpropd will pause before dying so as not to loop init");
    sleep(pause_int);
    klog(L_KRB_PERR, "AAAAAHHHHhhhh....");
    exit(1);
}

#ifdef doesnt_work_yet
static unsigned long
get_data_checksum(fd, key_sched)
int fd;
Key_schedule key_sched;
{
	unsigned long cksum = 0;
	unsigned long cbc_cksum();
	int n;
	char buf[BUFSIZ];
	char obuf[8];

	while (n = read(fd, buf, sizeof buf)) {
	    if (n < 0) {
		sprintf(errmsg, "kpropd: read (in checksum test): %s",
						sys_errlist[errno]);
		klog(L_KRB_PERR, errmsg);
		SlowDeath();
	    }
#ifndef NOENCRYPTION
	    cksum += cbc_cksum(buf, obuf, n, key_sched, key_sched);
#endif
	  }
	return cksum;
}
#endif
