/*
 *  $Id: kvm.c,v 1.12.2.2 1995/05/01 16:25:08 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_NLIST
#define	INCLUDE_FILE

#include "include.h"
#ifndef vax11c
#include <sys/file.h>
#endif				/* vax11c */

/*
 *	Emulation of kvm library for systems that do not have it
 */

struct __kvm {
    int	kvm_fd;
    const char *kvm_nl;
    const char *kvm_core;
    const char *kvm_swap;
    char kvm_errmsg[BUFSIZ];
};
typedef struct __kvm kvm_t;

#if	__GNUC__ > 1
/* To prevent a warning about missing prototypes */

PROTOTYPE(kvm_openfiles,
	  extern kvm_t *,
	  (char *,
	   char *,
	   char *,
	   int,
	   char *));
PROTOTYPE(kvm_close,
	  extern int,
	  (kvm_t *));
PROTOTYPE(kvm_nlist,
	  extern int,
	  (kvm_t *,
	   NLIST_T *,
	   size_t));
PROTOTYPE(kvm_read,
	  extern int,
	  (kvm_t *,
	   u_long,
	   void_t,
	   size_t));
PROTOTYPE(kvm_write,
	  extern int,
	  (kvm_t *,
	   u_long,
	   void_t,
	   size_t));
PROTOTYPE(kvm_geterr,
	  extern char *,
	  (kvm_t *));
#endif


kvm_t *
kvm_openfiles __PF5(nl, char *,
		    core, char *,
		    swap, char *,
		    flags, int,
		    errbuf, char *)
{
#ifndef	vax11c
    int fd;
    kvm_t *kd = (kvm_t *) 0;
    const char *corefile = core ? core : _PATH_KMEM;

    fd = task_floating_socket((task *) 0,
			      open(corefile, flags, 0),
			      corefile);
    if (fd < 0) {
	sprintf(errbuf, "kvm_openfiles: %m");
    } else {
	kd = (kvm_t *) task_mem_calloc((task *) 0, 1, sizeof (kvm_t));

	kd->kvm_fd = fd;
	kd->kvm_nl = nl ? nl : _PATH_UNIX;
	kd->kvm_core = corefile;
	kd->kvm_swap = NULL;
	*kd->kvm_errmsg = (char) 0;
    }

    return kd;
#else	/* vax11c */
    return (kvm_t *) TRUE;
#endif	/* vax11c */
}


int
kvm_close __PF1 (kd, kvm_t *)
{
#ifndef	vax11c
    int rc = 0;

    if (kd->kvm_fd >= 0) {
	rc = close(kd->kvm_fd);
	if (rc != 0) {
	    sprintf(kd->kvm_errmsg, "kvm_close: %m");
	}
    }

    (void) task_mem_free((task *) 0, (void_t) kd);

#endif	/* vax11c */

    return 0;
}


int
kvm_nlist __PF3(kd, kvm_t *,
		nl, NLIST_T *,
		sz, size_t)
{
#ifdef	vax11c
    extern char *Network_Image_File;

    return multinet_kernel_nlist(Network_Image_File, nl);
#else	/* vax11c */
    int rc = NLIST(kd->kvm_nl, nl, sz);

    if (rc < 0 && errno) {
	sprintf(kd->kvm_errmsg, "kvm_nlist: nlist (errno may not be valid): %m");
    }
    return rc;
#endif	/* vax11c */
}


int
kvm_read __PF4(kd, kvm_t *,
	       addr, u_long,
	       buf, void_t,
	       nbytes, size_t)
{
    off_t rc;
#ifdef	vax11c
    rc = klseek(offset);
    if (rc == (off_t) -1) {
	sprintf(kd->kvm_errmsg, "kvm_read: klseek: %m");
    } else {
	rc = klread(buf, nbytes);
	if (rc == (off_t) -1) {
	    sprintf(kd->kvm_errmsg, "kvm_read: klread: %m");
	}
    }
#else	/* vax11c */

    rc = lseek(kd->kvm_fd, (off_t) addr, 0);
    if (rc == (off_t) -1) {
	sprintf(kd->kvm_errmsg, "kvm_read: lseek: %m");
    } else {
	rc = read(kd->kvm_fd, buf, nbytes);
	if (rc == (off_t) -1) {
	    sprintf(kd->kvm_errmsg, "kvm_read: read: %m");
	}
    }
#endif	/* vax11c */

    return rc;
}


int
kvm_write __PF4(kd, kvm_t *,
	       addr, u_long,
	       buf, void_t,
	       nbytes, size_t)
{
    off_t rc;
#ifdef	vax11c
    rc = klseek(offset);
    if (rc == (off_t) -1) {
	sprintf(kvm_errmsg, "kvm_write: klseek: %m");
    } else {
	rc = klwrite(buf, nbytes);
	if (rc == (off_t) -1) {
	    sprintf(kvm_errmsg, "kvm_write: klwrite: %m");
	}
    }
#else	/* vax11c */

    rc = lseek(kd->kvm_fd, (off_t) addr, 0);
    if (rc == (off_t) -1) {
	sprintf(kd->kvm_errmsg, "kvm_write: lseek: %m");
    } else {
	rc = write(kd->kvm_fd, buf, nbytes);
	if (rc == (off_t) -1) {
	    sprintf(kd->kvm_errmsg, "kvm_write: write: %m");
	}
    }
#endif	/* vax11c */

    return rc;
}


char *
kvm_geterr __PF1 (kd, kvm_t *)
{
    return kd->kvm_errmsg;
}


/*
 * %(Copyright)
 */
