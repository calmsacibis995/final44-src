*** /nbsd/usr/src/bin/date.c	Sun May 18 21:43:36 1986
--- /usr/src/bin/date.c	Tue Mar 24 13:03:02 1987
***************
*** 11,17 ****
  #endif not lint
  
  #ifndef lint
! static char sccsid[] = "@(#)date.c	4.19 (Berkeley) 5/18/86";
  #endif not lint
  
  /*
--- 11,17 ----
  #endif not lint
  
  #ifndef lint
! static char sccsid[] = "@(#)date.c	4.20 (Berkeley) 3/24/87";
  #endif not lint
  
  /*
***************
*** 19,223 ****
   */
  
  #include <sys/param.h>
- #include <stdio.h>
  #include <sys/time.h>
  #include <sys/file.h>
  #include <errno.h>
  #include <syslog.h>
  #include <utmp.h>
  
! #define WTMP	"/usr/adm/wtmp"
  
! struct	timeval tv, now;
! struct	timezone tz;
! char	*ap, *ep, *sp;
! int	uflag, nflag;
! int	retval;
  
! char	*timezone();
! static	int dmsize[12] =
!     { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
! static	char *usage = "usage: date [-n] [-u] [yymmddhhmm[.ss]]\n";
  
! struct utmp wtmp[2] = {
  	{ "|", "", "", 0 },
  	{ "{", "", "", 0 }
  };
  
! char	*ctime();
! char	*asctime();
! struct	tm *localtime();
! struct	tm *gmtime();
! char	*strcpy(), *strncpy();
! char	*username, *getlogin();
! long	time();
! uid_t	getuid();
! 
! main(argc, argv)
! 	int argc;
! 	char *argv[];
  {
! 	register char *tzn;
  
! 	openlog("date", LOG_ODELAY, LOG_AUTH);
! 	(void) gettimeofday(&tv, &tz);
! 	now = tv;
! 
! 	while (argc > 1 && argv[1][0] == '-') {
! 		while (*++argv[1])
! 		    switch ((int)argv[1][0]) {
! 
! 		    case 'n':
! 			nflag++;
  			break;
! 
! 		    case 'u':
! 			uflag++;
  			break;
! 
! 		    default:
! 			fprintf(stderr, usage);
  			exit(1);
  		}
! 		argc--;
! 		argv++;
! 	}
! 	if (argc > 2) {
! 		fprintf(stderr, usage);
  		exit(1);
  	}
- 	if (argc == 1) 
- 		goto display;
  
! 	if (getuid() != 0) {
! 		fprintf(stderr, "You are not superuser: date not set\n");
  		retval = 1;
  		goto display;
  	}
- 	username = getlogin();
- 	if (username == NULL || *username == '\0')  /* single-user or no tty */
- 		username = "root";
  
! 	ap = argv[1];
  	wtmp[0].ut_time = tv.tv_sec;
! 	if (gtime()) {
! 		fprintf(stderr, usage);
  		retval = 1;
  		goto display;
  	}
! 	/* convert to GMT assuming local time */
! 	if (uflag == 0) {
! 		tv.tv_sec += (long)tz.tz_minuteswest*60;
! 		/* now fix up local daylight time */
  		if (localtime((time_t *)&tv.tv_sec)->tm_isdst)
! 			tv.tv_sec -= 60*60;
  	}
! 	if (nflag || !settime(tv)) {
! 		int wf;
! 
! 		if (settimeofday(&tv, (struct timezone *)0) < 0) {
  			perror("settimeofday");
  			retval = 1;
  			goto display;
  		}
! 		if ((wf = open(WTMP, O_WRONLY|O_APPEND)) >= 0) {
! 			(void) time((time_t *)&wtmp[1].ut_time);
! 			(void) write(wf, (char *)wtmp, sizeof(wtmp));
! 			(void) close(wf);
  		}
  	}
- 	syslog(LOG_NOTICE, "set by %s", username);
  
  display:
! 	(void) gettimeofday(&tv, (struct timezone *)0);
  	if (uflag) {
  		ap = asctime(gmtime((time_t *)&tv.tv_sec));
  		tzn = "GMT";
! 	} else {
! 		struct tm *tp;
  		tp = localtime((time_t *)&tv.tv_sec);
  		ap = asctime(tp);
! 		tzn = timezone(tz.tz_minuteswest, tp->tm_isdst);
  	}
! 	printf("%.20s", ap);
! 	if (tzn)
! 		printf("%s", tzn);
! 	printf("%s", ap+19);
  	exit(retval);
  }
  
! gtime()
  {
! 	register int i, year, month;
! 	int day, hour, mins, secs;
! 	struct tm *L;
! 	char x;
  
! 	ep = ap;
! 	while(*ep) ep++;
! 	sp = ap;
! 	while(sp < ep) {
! 		x = *sp;
! 		*sp++ = *--ep;
! 		*ep = x;
  	}
! 	sp = ap;
! 	(void) gettimeofday(&tv, (struct timezone *)0);
  	L = localtime((time_t *)&tv.tv_sec);
! 	secs = gp(-1);
! 	if (*sp != '.') {
! 		mins = secs;
! 		secs = 0;
! 	} else {
! 		sp++;
! 		mins = gp(-1);
  	}
! 	hour = gp(-1);
! 	day = gp(L->tm_mday);
! 	month = gp(L->tm_mon+1);
! 	year = gp(L->tm_year);
! 	if (*sp)
! 		return (1);
! 	if (month < 1 || month > 12 ||
! 	    day < 1 || day > 31 ||
! 	    mins < 0 || mins > 59 ||
! 	    secs < 0 || secs > 59)
! 		return (1);
  	if (hour == 24) {
  		hour = 0;
- 		day++;
  	}
! 	if (hour < 0 || hour > 23)
! 		return (1);
  	tv.tv_sec = 0;
! 	year += 1900;
! 	for (i = 1970; i < year; i++)
! 		tv.tv_sec += dysize(i);
! 	/* Leap year */
! 	if (dysize(year) == 366 && month >= 3)
! 		tv.tv_sec++;
  	while (--month)
! 		tv.tv_sec += dmsize[month-1];
! 	tv.tv_sec += day-1;
! 	tv.tv_sec = 24*tv.tv_sec + hour;
! 	tv.tv_sec = 60*tv.tv_sec + mins;
! 	tv.tv_sec = 60*tv.tv_sec + secs;
! 	return (0);
  }
  
- gp(dfault)
- {
- 	register int c, d;
- 
- 	if (*sp == 0)
- 		return (dfault);
- 	c = (*sp++) - '0';
- 	d = (*sp ? (*sp++) - '0' : 0);
- 	if (c < 0 || c > 9 || d < 0 || d > 9)
- 		return (-1);
- 	return (c+10*d);
- }
- 
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
--- 19,232 ----
   */
  
  #include <sys/param.h>
  #include <sys/time.h>
  #include <sys/file.h>
  #include <errno.h>
  #include <syslog.h>
  #include <utmp.h>
+ #include <tzfile.h>
+ #include <stdio.h>
+ #include <ctype.h>
+ #include <strings.h>
  
! #define	WTMP		"/usr/adm/wtmp"
! #define	ATOI2(ar)	(ar[0] - '0') * 10 + (ar[1] - '0'); ar += 2;
  
! static struct timeval	tv;
! static int	retval;
  
! static int	dmsize[] =
! 	{ -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  
! static struct utmp	wtmp[2] = {
  	{ "|", "", "", 0 },
  	{ "{", "", "", 0 }
  };
  
! main(argc,argv)
! 	int	argc;
! 	char	**argv;
  {
! 	extern int	optind;
! 	extern char	*optarg;
! 	static char	usage[] = "usage: date [-nu] [-d dst] [-t timezone] [yymmddhhmm[.ss]]\n";
! 	struct timezone	tz;
! 	char	*ap,			/* time string */
! 		*tzn;			/* time zone */
! 	int	ch,			/* getopts char */
! 		uflag,			/* do it in GMT */
! 		nflag,			/* only set time locally */
! 		wf;			/* wtmp file descriptor */
! 	long	time();
! 	uid_t	getuid();
! 	char	*username, *getlogin();
  
! 	nflag = uflag = 0;
! 	while ((ch = getopt(argc,argv,"d:nut:")) != EOF)
! 		switch((char)ch) {
! 		case 'd':
! 			tz.tz_dsttime = atoi(optarg) ? 1 : 0;
  			break;
! 		case 'n':
! 			nflag = 1;
  			break;
! 		case 't':
! 			tz.tz_minuteswest = atoi(optarg);
! 			break;
! 		case 'u':
! 			uflag = 1;
! 			break;
! 		default:
! 			fputs(usage,stderr);
  			exit(1);
  		}
! 	argc -= optind;
! 	argv += optind;
! 
! 	if (argc > 1) {
! 		fputs(usage,stderr);
  		exit(1);
  	}
  
! 	if ((tz.tz_minuteswest || tz.tz_dsttime) &&
! 	    settimeofday((struct timeval *)NULL,&tz)) {
! 		perror("settimeofday");
  		retval = 1;
  		goto display;
  	}
  
! 	if (gettimeofday(&tv,&tz)) {
! 		perror("gettimeofday");
! 		exit(1);
! 	}
! 
! 	if (!argc)
! 		goto display;
! 
  	wtmp[0].ut_time = tv.tv_sec;
! 	if (gtime(*argv)) {
! 		fputs(usage,stderr);
  		retval = 1;
  		goto display;
  	}
! 
! 	if (!uflag) {		/* convert to GMT assuming local time */
! 		tv.tv_sec += (long)tz.tz_minuteswest * SECS_PER_MIN;
! 				/* now fix up local daylight time */
  		if (localtime((time_t *)&tv.tv_sec)->tm_isdst)
! 			tv.tv_sec -= SECS_PER_HOUR;
  	}
! 	if (nflag || !netsettime(tv)) {
! 		if (settimeofday(&tv,(struct timezone *)0)) {
  			perror("settimeofday");
  			retval = 1;
  			goto display;
  		}
! 		if ((wf = open(WTMP,O_WRONLY|O_APPEND)) < 0)
! 			fputs("date: can't write wtmp file.\n",stderr);
! 		else {
! 			(void)time((time_t *)&wtmp[1].ut_time);
! 			/*NOSTRICT*/
! 			(void)write(wf,(char *)wtmp,sizeof(wtmp));
! 			(void)close(wf);
  		}
  	}
  
+ 	username = getlogin();
+ 	if (!username || *username == '\0')	/* single-user or no tty */
+ 		username = "root";
+ 	syslog(LOG_AUTH | LOG_NOTICE,"date set by %s",username);
+ 
  display:
! 	if (gettimeofday(&tv,(struct timezone *)0)) {
! 		perror("gettimeofday");
! 		exit(1);
! 	}
  	if (uflag) {
  		ap = asctime(gmtime((time_t *)&tv.tv_sec));
  		tzn = "GMT";
! 	}
! 	else {
! 		struct tm	*tp;
! 
  		tp = localtime((time_t *)&tv.tv_sec);
  		ap = asctime(tp);
! 		tzn = tp->tm_zone;
  	}
! 	printf("%.20s%s%s",ap,tzn,ap + 19);
  	exit(retval);
  }
  
! /*
!  * gtime --
!  *	convert user's time into number of seconds
!  */
! static
! gtime(ap)
! 	register char	*ap;		/* user argument */
  {
! 	register int	year, month;
! 	register char	*C;		/* pointer into time argument */
! 	struct tm	*L;
! 	int	day, hour, mins, secs;
  
! 	for (secs = 0, C = ap;*C;++C) {
! 		if (*C == '.') {		/* seconds provided */
! 			if (strlen(C) != 3)
! 				return(1);
! 			*C = NULL;
! 			secs = (C[1] - '0') * 10 + (C[2] - '0');
! 			break;
! 		}
! 		if (!isdigit(*C))
! 			return(-1);
  	}
! 
  	L = localtime((time_t *)&tv.tv_sec);
! 	year = L->tm_year;			/* defaults */
! 	month = L->tm_mon + 1;
! 	day = L->tm_mday;
! 
! 	switch ((int)(C - ap)) {		/* length */
! 		case 10:			/* yymmddhhmm */
! 			year = ATOI2(ap);
! 		case 8:				/* mmddhhmm */
! 			month = ATOI2(ap);
! 		case 6:				/* ddhhmm */
! 			day = ATOI2(ap);
! 		case 4:				/* hhmm */
! 			hour = ATOI2(ap);
! 			mins = ATOI2(ap);
! 			break;
! 		default:
! 			return(1);
  	}
! 
! 	if (*ap || month < 1 || month > 12 || day < 1 || day > 31 ||
! 	     mins < 0 || mins > 59 || secs < 0 || secs > 59)
! 		return(1);
  	if (hour == 24) {
+ 		++day;
  		hour = 0;
  	}
! 	else if (hour < 0 || hour > 23)
! 		return(1);
! 
  	tv.tv_sec = 0;
! 	year += TM_YEAR_BASE;
! 	if (isleap(year) && month > 2)
! 		++tv.tv_sec;
! 	for (--year;year >= EPOCH_YEAR;--year)
! 		tv.tv_sec += isleap(year) ? DAYS_PER_LYEAR : DAYS_PER_NYEAR;
  	while (--month)
! 		tv.tv_sec += dmsize[month];
! 	tv.tv_sec += day - 1;
! 	tv.tv_sec = HOURS_PER_DAY * tv.tv_sec + hour;
! 	tv.tv_sec = MINS_PER_HOUR * tv.tv_sec + mins;
! 	tv.tv_sec = SECS_PER_MIN * tv.tv_sec + secs;
! 	return(0);
  }
  
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
***************
*** 236,243 ****
   * notifies the master that a correction is needed.
   * Returns 1 on success, 0 on failure.
   */
! settime(tv)
! 	struct timeval tv;
  {
  	int s, length, port, timed_ack, found, err;
  	long waittime;
--- 245,253 ----
   * notifies the master that a correction is needed.
   * Returns 1 on success, 0 on failure.
   */
! static
! netsettime(ntv)
! 	struct timeval ntv;
  {
  	int s, length, port, timed_ack, found, err;
  	long waittime;
***************
*** 250,259 ****
  
  	sp = getservbyname("timed", "udp");
  	if (sp == 0) {
! 		fprintf(stderr, "udp/timed: unknown service\n");
  		retval = 2;
  		return (0);
! 	}	
  	dest.sin_port = sp->s_port;
  	dest.sin_family = AF_INET;
  	dest.sin_addr.s_addr = htonl((u_long)INADDR_ANY);
--- 260,269 ----
  
  	sp = getservbyname("timed", "udp");
  	if (sp == 0) {
! 		fputs("udp/timed: unknown service\n",stderr);
  		retval = 2;
  		return (0);
! 	}
  	dest.sin_port = sp->s_port;
  	dest.sin_family = AF_INET;
  	dest.sin_addr.s_addr = htonl((u_long)INADDR_ANY);
***************
*** 276,291 ****
  		}
  	}
  	if (port == IPPORT_RESERVED / 2) {
! 		fprintf(stderr, "date: All ports in use\n");
  		goto bad;
  	}
  	msg.tsp_type = TSP_SETDATE;
  	msg.tsp_vers = TSPVERSION;
! 	(void) gethostname(hostname, sizeof (hostname));
  	(void) strncpy(msg.tsp_name, hostname, sizeof (hostname));
  	msg.tsp_seq = htons((u_short)0);
! 	msg.tsp_time.tv_sec = htonl((u_long)tv.tv_sec);
! 	msg.tsp_time.tv_usec = htonl((u_long)tv.tv_usec);
  	length = sizeof (struct sockaddr_in);
  	if (connect(s, &dest, length) < 0) {
  		perror("date: connect");
--- 286,304 ----
  		}
  	}
  	if (port == IPPORT_RESERVED / 2) {
! 		fputs("date: All ports in use\n",stderr);
  		goto bad;
  	}
  	msg.tsp_type = TSP_SETDATE;
  	msg.tsp_vers = TSPVERSION;
! 	if (gethostname(hostname, sizeof (hostname))) {
! 		perror("gethostname");
! 		goto bad;
! 	}
  	(void) strncpy(msg.tsp_name, hostname, sizeof (hostname));
  	msg.tsp_seq = htons((u_short)0);
! 	msg.tsp_time.tv_sec = htonl((u_long)ntv.tv_sec);
! 	msg.tsp_time.tv_usec = htonl((u_long)ntv.tv_usec);
  	length = sizeof (struct sockaddr_in);
  	if (connect(s, &dest, length) < 0) {
  		perror("date: connect");
***************
*** 343,350 ****
  		}
  	}
  	if (timed_ack == -1)
! 		fprintf(stderr,
! 		    "date: Can't reach time daemon, time set locally.\n");
  bad:
  	(void)close(s);
  	retval = 2;
--- 356,363 ----
  		}
  	}
  	if (timed_ack == -1)
! 		fputs("date: Can't reach time daemon, time set locally.\n",
! 		    stderr);
  bad:
  	(void)close(s);
  	retval = 2;
