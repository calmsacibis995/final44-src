/*
 *  $Id: recvmsg.c,v 1.9 1993/04/05 15:27:28 jch Exp $
 */

/* %(Copyright.header) */


#include "include.h"

static caddr_t buf_base;
static int buf_size;

int
recvmsg(s, msg, flags)
int s;
const struct msghdr *msg;
int flags;
{
    register int i, cc, acc;
    extern int errno;
    extern char etext;
    extern char *sbrk();
    char *buf_ptr;

    if ((msg->msg_iovlen < 1) || (msg->msg_iovlen > MSG_MAXIOVLEN)) {
	errno = EINVAL;
	return (-1);
    }
#ifdef	SCM_RIGHTS
    if (msg->msg_control) {
	*msg->msg_control = (char) 0;
    }
#else				/* SCM_RIGHTS */
    if (msg->msg_accrights) {
	*msg->msg_accrights = (char) 0;
    }
#endif				/* SCM_RIGHTS */

    /* only 1 buffer - receive the data directly */
    if (msg->msg_iovlen == 1) {
	NON_INTR(acc, recvfrom(s,
			       msg->msg_iov->iov_base,
			       msg->msg_iov->iov_len,
			       flags,
			       (struct sockaddr *) msg->msg_name,
			       (const int *) &msg->msg_namelen));
	return (acc);
    }
    /* Scan through the iovec's to check lengths and figure out */
    /* maximum buffer size */
    for (acc = i = 0; i < msg->msg_iovlen; i++) {
	register int len = msg->msg_iov[i].iov_len;
	register char *base = msg->msg_iov[i].iov_base;

	if ((len < 0) || (base < &etext) || ((base + len) > sbrk(0))) {
	    errno = EINVAL;
	    return (-1);
	}
	acc += msg->msg_iov[i].iov_len;
    }

    /* Allocate a receive buffer */
    if (acc > buf_size) {
	if (buf_base != NULL) {
	    (void) free(buf_base);
	}
	buf_base = (caddr_t) malloc(acc);
	buf_size = acc;
    }
    if (!buf_base) {
	buf_size = 0;
	errno = ENOMEM;
	return (-1);
    }
    NON_INTR(acc = cc, recvfrom(s,
				buf_base,
				acc,
				flags,
				(struct sockaddr *) msg->msg_name,
				(const int *) &msg->msg_namelen));

    /* Return if error */
    if (cc < 0) {
	return (cc);
    }
    /* Distribute the data as specified in the iovec */
    for (i = 0, buf_ptr = buf_base; acc && (i < msg->msg_iovlen); i++) {
	register int len = msg->msg_iov[i].iov_len;

	(void) memcpy(msg->msg_iov[i].iov_base, buf_ptr, len);
	buf_ptr += len;
	acc -= len;
    }

    /* Return the length read */
    return (cc);
}


/*
 * %(Copyright)
 */
