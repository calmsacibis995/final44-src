/*
 * $Id: paths.h,v 1.11 1993/03/25 12:47:28 jch Exp $
 */

/* %(Copyright.header) */


/* Gated specific Paths from configuration */

#define	_PATH_CONFIG	"@(_path_config)"
#define	_PATH_DEFS	"@(_path_defs)"
#define	_PATH_DUMP	"@(_path_dump)"
#define	_PATH_DUMPDIR	"@(_path_dumpdir)"
#define	_PATH_PID	"@(_path_pid)"
#define	_PATH_VERSION	"@(_path_version)"
#define	_PATH_BINDIR	"@(BINDIR)"
#define	_PATH_SBINDIR	"@(SBINDIR)"

/* System specific paths (not everyone runs BSD 4.4, do they) */
#ifndef	_PATH_DEVNULL
#define	_PATH_DEVNULL		"/dev/null"
#endif	/* _PATH_DEVNULL */

#ifndef	_PATH_DEV
#define	_PATH_DEV	"/dev"
#endif	/* _PATH_DEV */

#ifndef	_PATH_KMEM
#define	_PATH_KMEM	"/dev/kmem"
#endif	/* _PATH_KMEM */

#ifndef	_PATH_TTY
#define	_PATH_TTY	"/dev/tty"
#endif	/* _PATH_TTY */

#ifndef	_PATH_UNIX
#define	_PATH_UNIX	"@(_path_unix)"
#endif	/* _PATH_UNIX */

#ifndef	_PATH_VARTMP
#define	_PATH_VARTMP	"/usr/tmp"
#endif	/* _PATH_VARTMP */

/* Non-path information */
#ifndef	CONFIG_MODE
#define	CONFIG_MODE	@(CONFIG_MODE)
#endif	/* CONFIG_MODE */

#ifndef	GDC_GROUP
#define	GDC_GROUP	"@(GDC_GROUP)"
#endif	/* GDC_GROUP */

#ifndef	NAME_GATED
#define	NAME_GATED	"@(GATED)"
#endif	/* NAME_GATED */

#ifndef	NAME_GDC
#define	NAME_GDC	"@(GDC)"
#endif	/* NAME_GDC */

#ifndef	NAME_RIPQUERY
#define	NAME_RIPQUERY	"@(RIPQUERY)"
#endif	/* NAME_RIPQUERY */

#ifndef	NAME_OSPF_MONITOR
#define	NAME_OSPF_MONITOR	"@(OSPF_MONITOR)"
#endif	/* NAME_OSPF_MONITOR */


/*
 * %(Copyright)
 */
