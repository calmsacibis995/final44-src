
#ifdef SOLARIS
#  define LOOKUP_MACRO		/* support 'L' ang 'G' command */
#  define SUN_STYLE_MACRO_M	/* sun's $m  derivation */
#  define NSSWITCH		/* name service switch */
#  define NISPLUS		/* NIS+ table lookup */
#  define TEXT			/* text table lookup */
#  define PERCENT_MATCH		/* % variable matching */
#  define SUNLOOKUP		/* sun style map look up */
#  define CONTENT_LENGTH	/* generate content_length header */
#  define CHECK_INDIRECT_SELF_REF /* check indirect self reference */
#  define MULI_HOME_HOST
#  define REMOTE_MODE		/* support remotely mounted mail box */
#  define EXTENDED_TIMEOUT	/* support extended queue timeout */
#  define SUN_STYLE_MACRO_K	/* sun's $k derivation */

#ifdef NSSWITCH
#  define MAP_EXIT_STAT	/* map lookup always exit with a status flag */
#endif

#  define DOMAIN_WIDE_ALIAS_SUPPORT	  /* host independent address */
#endif

#ifdef LOOKUP_MACRO
# define SENDMAIL_MAP_NISPLUS "sendmailvars.org_dir"
# define SENDMAIL_MAP_FILE "/etc/mail/sendmailvars"
#endif
