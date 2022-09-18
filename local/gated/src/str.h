/*
 * $Id: str.h,v 1.10.2.1 1995/05/01 16:06:57 jch Exp $
 */

/* %(Copyright.header) */


/* Definitions for putting data into and getting data out of packets */
/* in a machine dependent manner. */
#define	PickUp(s, d)	bcopy((caddr_t) s, (caddr_t)&d, sizeof(d));	s += sizeof(d);
#define	PutDown(s, d)	bcopy((caddr_t)&d, (caddr_t) s, sizeof(d));	s += sizeof(d);
#define	PickUpStr(s, d, l)	bcopy((caddr_t) s, (caddr_t) d, l);	s += l;
#define	PutDownStr(s, d, l)	bcopy((caddr_t) d, (caddr_t) s, l);	s += l;

#ifdef	notdef
#define	PickUp(s, d)	{ \
    register int PickUp_i = sizeof(d); \
    d = 0; \
    while (PickUp_i--) { \
	d <<= 8; \
        d |= *s++;
    } \
}
#define	PutDown(s, d)	{
    register int i = sizeof(d);
    register long ii = d;
    register caddr_t cp;

    cp = (s += i);
    while (i--) {
	*--cp = (ii & 0xff);
	ii >>= 8;
    }
}
#define	PickUpStr(s, d, l) {
    register int i = l;
    register char *cp = d;

    while (i--) {
	*cp++ = *s++;
    }
}
#define	PutDownStr(s, d, l) {
    register int i = l;
    register char *cp = s;

    while (i--) {
	*s++ = *cp++;
    }
}
#endif	/* notdef */

PROTOTYPE(gd_uplow,
	  extern char *,
	  (const char *,
	   int));
#define	gd_upper(str)	gd_uplow(str, TRUE)
#define	gd_lower(str)	gd_uplow(str, FALSE)
PROTOTYPEV(fprintf,
	   extern int,
	   (FILE *,
	    const char *,
	    ...));
PROTOTYPEV(vsprintf,
	   extern int,
	   (char *,
	    const char *,
	    va_list *));
PROTOTYPEV(sprintf,
	   extern int,
	   (char *,
	    const char *,
	    ...));
#ifdef	NEED_STRCASECMP
PROTOTYPE(strcasecmp,
	  extern int,
	  (const char *,
	   const char *));
PROTOTYPE(strncasecmp,
	  extern int,
	  (const char *,
	   const char *,
	   size_t));
#endif	/* NEED_STRCASECMP */
#ifdef	NEED_STRERROR
PROTOTYPE(strerror,
	  extern const char *,
	  (int));
#endif	/* NEED_STRERROR */


/*
 * %(Copyright)
 */
