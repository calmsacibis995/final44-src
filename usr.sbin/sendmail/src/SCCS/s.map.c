h48642
s 00000/00001/02963
d D 8.79 95/06/20 10:46:44 eric 116 115
c h_errno now in conf.h
e
s 00000/00030/02964
d D 8.78 95/06/15 19:24:14 eric 115 114
c change bestmx map to not do resolver domain searching (RES_DNSRCH)
e
s 00003/00003/02991
d D 8.77 95/06/13 09:23:20 eric 114 113
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00001/00001/02993
d D 8.76 95/06/12 17:26:37 eric 113 112
c keep looking for a dotted address in text_ and nis_getcanonname
e
s 00003/00003/02991
d D 8.75 95/06/12 06:17:08 eric 112 111
c fix incorrect stat usage for program map
e
s 00068/00044/02926
d D 8.74 95/06/10 12:15:01 eric 111 110
c improved domain heuristics in {nis,text}_getcanonname
e
s 00040/00013/02930
d D 8.73 95/06/10 10:32:35 eric 110 109
c improve exit status handling for program map code
e
s 00127/00111/02816
d D 8.72 95/06/05 08:06:58 eric 109 108
c move getcanonname up so that NIS wouldn't be #undefed
e
s 00044/00023/02883
d D 8.71 95/05/30 17:24:46 eric 108 107
c fix a problem that causes NIS and NIS+ lookups to strip names for DNS lookups
e
s 00000/00001/02906
d D 8.70 95/05/28 19:49:14 eric 107 106
c lint
e
s 00003/00004/02904
d D 8.69 95/05/28 11:50:19 eric 106 105
c lint
e
s 00028/00004/02880
d D 8.68 95/05/26 07:50:03 eric 105 104
c add -q map flag to avoid quote stripping; clean up domain addition
c in nis_getcanonname and nisplus_getcanonname
e
s 00021/00001/02863
d D 8.67 95/05/25 11:39:12 eric 104 103
c patches for Hesiod
e
s 00005/00005/02859
d D 8.66 95/05/24 16:24:06 eric 103 102
c hosts file can be space separated instead of tab separated
e
s 00009/00006/02855
d D 8.65 95/05/24 08:53:25 eric 102 101
c search for /yp/ in filename instead of accessing /var/yp/Makefile
e
s 00007/00004/02854
d D 8.64 95/05/23 16:29:52 eric 101 100
c fix a glitch with NIS+ that can cause null pointer derefs
e
s 00005/00014/02853
d D 8.63 95/05/23 10:21:26 eric 100 99
c Hesiod doesn't dynamically allocate space, despite the claims in
c the documentation
e
s 00001/00001/02866
d D 8.62 95/05/19 16:00:19 eric 99 98
c fix compile problems on various platforms
e
s 00002/00002/02865
d D 8.61 95/05/15 16:03:22 eric 98 97
c fix compile problems on Solaris and HP-UX
e
s 00005/00032/02862
d D 8.60 95/05/15 15:38:59 eric 97 96
c improved implementation for E line -- slightly cleaner -- plus
c resulting simplifications in map.c for NIS+
e
s 00080/00000/02814
d D 8.59 95/05/14 08:43:00 eric 96 95
c implement Fx|prog and "program" map class
e
s 00421/00000/02393
d D 8.58 95/05/13 15:06:16 eric 95 94
c put getcanonname into service switch
e
s 00002/00001/02391
d D 8.57 95/04/24 20:39:00 eric 94 93
c lint
e
s 00001/00001/02391
d D 8.56 95/04/21 09:57:51 eric 93 92
c update copyright notice
e
s 00001/00000/02391
d D 8.55 95/04/13 14:25:26 eric 92 91
c make sure the the MF_OPEN and MF_WRITABLE bits are cleared after the
c maps are closed
e
s 00018/00016/02373
d D 8.54 95/04/11 06:53:54 eric 91 90
c clean up problem causing unlocked map files during alias rebuild
c when compiled with !HASFLOCK
e
s 00000/00002/02389
d D 8.53 95/04/10 09:27:32 eric 90 89
c eliminate old (bogus) debugging code
e
s 00004/00002/02387
d D 8.52 95/04/07 07:15:17 eric 89 88
c improve error output on NIS maps
e
s 00001/00003/02388
d D 8.51 95/03/31 10:52:31 eric 88 87
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00004/00004/02387
d D 8.50 95/03/14 08:19:14 eric 87 86
c be more precise on MAXNAME checking
e
s 00001/00001/02390
d D 8.49 95/03/13 19:59:44 eric 86 85
c NIS on IRIX fixes
e
s 00006/00005/02385
d D 8.48 95/03/12 17:03:36 eric 85 84
c default -z to white space on text maps; use -z: to get old behaviour
e
s 00004/00003/02386
d D 8.47 95/03/10 09:43:43 eric 84 83
c portability for IRIX
e
s 00065/00002/02324
d D 8.46 95/03/07 07:39:52 eric 83 82
c allow -A flag to support appendable aliases
e
s 00002/00027/02324
d D 8.45 95/02/28 11:08:38 eric 82 81
c change to nisplus_default_domain per Sun's request
e
s 00001/00001/02350
d D 8.44 95/02/23 15:50:29 eric 81 80
c cleanup to make gcc -Winitialized happier
e
s 00001/00003/02350
d D 8.43 95/02/21 05:49:24 eric 80 79
c minor patch for Hesiod
e
s 00021/00021/02332
d D 8.42 95/02/17 12:47:07 eric 79 77
c use far more generalized map support
e
s 00000/00000/01303
d D 8.25.1.1 95/02/10 07:51:39 eric 78 60
i 71
c dual buffers no longer necessary due to change in sendtolist
e
s 00005/00003/02348
d D 8.41 95/02/09 17:02:22 eric 77 76
c improved locking for alias files
e
s 00030/00000/02321
d D 8.40 95/01/26 11:06:03 eric 76 75
c add bestmx map
e
s 00002/00009/02319
d D 8.39 95/01/24 08:26:33 eric 75 74
c change NetInfo property handling to not use hacks
e
s 00046/00013/02282
d D 8.38 94/12/10 09:30:18 eric 74 73
c if a non-optional map cannot be opened, queue mail that needs it
e
s 00003/00000/02292
d D 8.37 94/11/22 13:33:19 eric 73 72
c debugging
e
s 00002/00001/02290
d D 8.36 94/11/13 15:54:41 eric 72 71
c allow map defs without file names in map_parse
e
s 00002/00001/02289
d D 8.35 94/11/08 10:06:55 eric 71 70
x 28
c dual map buffers are no longer necessary due to copy in sendtolist()
e
s 00002/00002/02299
d D 8.34 94/10/25 17:19:38 eric 70 69
c compile problems on various platforms
e
s 00001/00001/02300
d D 8.33 94/10/24 21:19:24 eric 69 68
c get it to compile on other environments
e
s 00588/00004/01713
d D 8.32 94/10/24 18:32:43 eric 68 67
c first cut at service switch abstraction
e
s 00078/00000/01639
d D 8.31 94/10/23 14:19:19 eric 67 66
c first cut at NeXT NetInfo map class -- still somewhat crude
e
s 00042/00000/01597
d D 8.30 94/10/18 06:37:55 eric 66 65
c add hesiod changes
e
s 00339/00059/01258
d D 8.29 94/08/21 15:23:18 eric 65 64
c new map classes in preparation for service abstraction
e
s 00001/00001/01316
d D 8.28 94/05/29 07:34:49 eric 64 63
c avoid logging alias stats if you have no db code defined
e
s 00008/00008/01309
d D 8.27 94/05/20 07:07:42 eric 63 62
c avoid reference to uninitialized fd if !HASFLOCK
e
s 00006/00002/01311
d D 8.26 94/05/18 12:10:01 eric 62 60
c avoid reference to uninitialized "fd" if !HASFLOCK
e
s 00010/00002/01311
d R 8.26 94/05/18 10:44:55 eric 61 60
c fix obscure case of uninitialized variable (only for OLD_NEWDB)
e
s 00008/00008/01305
d D 8.25 94/04/17 07:05:47 eric 60 59
c make OLD_NEWDB a #if instead of #ifdef; autoconfigure it for old
c versions of BSD/386
e
s 00003/00000/01310
d D 8.24 94/04/13 09:54:04 eric 59 58
c debugging in ndbm_map_close
e
s 00003/00002/01307
d D 8.23 94/04/12 08:21:00 eric 58 57
c don't complain about no NIS domain for optional NIS maps
e
s 00011/00003/01298
d D 8.22 94/02/18 13:00:45 eric 57 56
c avoid core dump if NIS compiled in and NIS map is specified, but
c NIS is not running
e
s 00004/00004/01297
d D 8.21 94/01/22 16:12:31 eric 56 55
c make HASFLOCK a 0/1 definition so Linux can turn it off
e
s 00024/00009/01277
d D 8.20 93/12/11 08:26:14 eric 55 54
c open non-alias maps before initializing alias maps
e
s 00018/00002/01268
d D 8.19 93/11/27 15:05:26 eric 54 53
c fix file locking on DBM alias files -- had a race condition
e
s 00001/00001/01269
d D 8.18 93/11/25 11:22:34 eric 53 52
c fix YP_MASTER_NAME to be consistent with SunOS
e
s 00024/00005/01246
d D 8.17 93/10/15 08:35:05 eric 52 51
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00011/00005/01240
d D 8.16 93/10/01 08:02:42 eric 51 50
c check for NULL when debug printing some fields
e
s 00006/00000/01239
d D 8.15 93/09/27 14:53:09 eric 50 49
c add additional checkfd012 calls
e
s 00011/00002/01228
d D 8.14 93/09/25 12:16:20 eric 49 48
c clean up errors when no database at all can be opened
e
s 00003/00001/01227
d D 8.13 93/09/24 06:44:53 eric 48 47
c avoid comment that gets confused with an ANSI trigraph
e
s 00018/00007/01210
d D 8.12 93/09/02 17:19:16 eric 47 46
c improvements to alias file locking code
e
s 00030/00017/01187
d D 8.11 93/08/30 12:36:13 eric 46 45
c old version of db->sync didn't take a flags arg; be more
c conservative about file locking
e
s 00004/00000/01200
d D 8.10 93/08/28 09:35:50 eric 45 44
c HP-UX portability
e
s 00010/00008/01190
d D 8.9 93/08/23 08:32:40 eric 44 43
c add "ext" argument to lockfile so you can accurately tell what file
c is being locked in logging/error messages
e
s 00020/00001/01178
d D 8.8 93/08/17 09:52:03 eric 43 42
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00002/00002/01177
d D 8.7 93/08/14 11:32:04 eric 42 41
c eliminate YPCOMPAT (do this automatically if NIS and NDBM are defined)
e
s 00007/00000/01172
d D 8.6 93/07/28 08:09:50 eric 41 40
c output YP_MASTER_NAME and YP_LAST_MODIFIED without null bytes.
e
s 00004/00004/01168
d D 8.5 93/07/26 09:22:17 eric 40 39
c signal and file locking portability changes
e
s 00002/00004/01170
d D 8.4 93/07/19 20:50:23 eric 39 38
c SGI IRIX & ANSI C portability
e
s 00008/00000/01166
d D 8.3 93/07/16 10:23:57 eric 38 37
c fix !defined(NDBM) && !defined(NEWDB) case
e
s 00058/00015/01108
d D 8.2 93/07/11 06:52:57 eric 37 36
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/01121
d D 8.1 93/06/07 10:31:00 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/01120
d D 6.28 93/06/05 17:08:17 eric 35 34
c lint-style cleanup
e
s 00002/00001/01121
d D 6.27 93/06/01 17:54:59 eric 34 33
c don't rebuild non-alias database maps on -bi
e
s 00001/00001/01121
d D 6.26 93/05/30 08:55:08 eric 33 32
c check mod time on .pag file instead of .dir -- it gets updated
c more reliably
e
s 00010/00000/01112
d D 6.25 93/05/29 04:13:54 eric 32 31
c do early sync of empty database to disk -- at least the header
c will be there
e
s 00060/00008/01052
d D 6.24 93/05/29 03:28:20 eric 31 30
c improved locking to avoid errors during alias rebuild
e
s 00001/00001/01059
d D 6.23 93/05/28 15:04:28 eric 30 29
c fix YPCOMPAT mode
e
s 00091/00017/00969
d D 6.22 93/05/28 07:00:57 eric 29 28
c change alias initialization to general map initialization
e
s 00021/00010/00965
d D 6.21 93/05/27 10:37:15 eric 28 27
c use multiple output buffers to avoid conflict between maps and aliases
e
s 00017/00001/00958
d D 6.20 93/05/25 19:05:48 eric 27 26
c lock NEWDB files during access
e
s 00009/00003/00950
d D 6.19 93/05/24 08:30:04 eric 26 25
c debugging core dumps if av == NULL
e
s 00010/00002/00943
d D 6.18 93/05/22 11:52:48 eric 25 24
c alias maps include null byte; don't add .db if it already exits
e
s 00017/00009/00928
d D 6.17 93/05/22 09:44:03 eric 24 23
c documentation update
e
s 00013/00031/00924
d D 6.16 93/05/21 20:29:48 eric 23 22
c cleanup for NIS maps
e
s 00104/00294/00851
d D 6.15 93/05/21 18:58:02 eric 22 21
c changes to merge alias and map implementations
e
s 00954/00322/00191
d D 6.14 93/05/17 10:28:30 eric 21 20
c first cut at merged map/alias implementation
e
s 00000/00001/00513
d D 6.13 93/05/01 12:47:38 eric 20 19
c oops...  can't #undef __P on vangogh
e
s 00004/00003/00510
d D 6.12 93/05/01 12:26:43 eric 19 18
c minor tweaking of syslog levels & compile fixes for SunOS & Ultrix
e
s 00002/00000/00511
d D 6.11 93/05/01 09:03:01 eric 18 17
c locking for DBM files
e
s 00005/00001/00506
d D 6.10 93/04/26 13:27:23 eric 17 16
c obey INCLNULL flag in NIS maps
e
s 00009/00003/00498
d D 6.9 93/04/14 14:38:50 eric 16 15
c return status information from map lookups and from there from 
c rewrite; this allows higher level code to queue if the name server is down
e
s 00005/00000/00496
d D 6.8 93/04/04 16:20:10 eric 15 14
c crude initialization of map_rebuild -- needs work yet
e
s 00009/00008/00487
d D 6.7 93/03/25 10:26:55 eric 14 13
c fix some minor glitches
e
s 00000/00001/00495
d D 6.6 93/03/17 09:55:32 eric 13 12
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00007/00007/00489
d D 6.5 93/02/18 20:22:46 eric 12 11
c move the meta-characters from C0 into C1 space
e
s 00001/00002/00495
d D 6.4 93/01/28 17:04:58 eric 11 10
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00001/00000/00496
d D 6.3 93/01/28 10:16:03 eric 10 9
c System 5 compatibility, misc fixes
e
s 00003/00002/00493
d D 6.2 93/01/21 15:18:57 eric 9 8
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00000/00000/00495
d D 6.1 92/12/21 16:08:56 eric 8 7
c Release 6
e
s 00012/00001/00483
d D 5.7 92/12/18 16:03:12 eric 7 6
c do validity checking on NIS map creation
e
s 00110/00011/00374
d D 5.6 92/12/18 12:03:21 eric 6 5
c add NIS map type; log message-id in same line as from logging
e
s 00003/00003/00382
d D 5.5 92/12/09 09:24:17 eric 5 4
c reverse sense of -f in K field
e
s 00008/00000/00377
d D 5.4 92/12/08 09:46:05 eric 4 3
c make years in $t be four digits; do case folding for DBM databases
c in map.c if MF_MAPCASE set
e
s 00012/00000/00365
d D 5.3 92/11/16 11:41:29 eric 3 2
c add -f (fold case) flag to keyed database lookups
e
s 00020/00004/00345
d D 5.2 92/11/15 19:24:48 eric 2 1
c allow specification of arbitrary string on successful db match
e
s 00349/00000/00000
d D 5.1 92/11/15 16:10:08 eric 1 0
c date and time created 92/11/15 16:10:08 by eric
e
u
U
t
T
I 1
/*
D 93
 * Copyright (c) 1992 Eric P. Allman.
E 93
I 93
 * Copyright (c) 1992, 1995 Eric P. Allman.
E 93
D 36
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "sendmail.h"
D 11
#include <sys/file.h>
I 10
#include <sys/fcntl.h>
E 11
I 11
D 13
#include <fcntl.h>
E 13
E 11
E 10

D 21
#ifdef DBM_MAP
E 21
I 21
#ifdef NDBM
E 21
D 84
#include <ndbm.h>
E 84
I 84
# include <ndbm.h>
E 84
#endif
D 21
#if defined(HASH_MAP) || defined(BTREE_MAP)
E 21
I 21
#ifdef NEWDB
E 21
I 19
D 20
#undef __P
E 20
E 19
D 84
#include <db.h>
E 84
I 84
# include <db.h>
E 84
#endif
I 6
D 21
#ifdef NIS_MAP
E 21
I 21
#ifdef NIS
E 21
D 84
#include <rpcsvc/ypclnt.h>
E 84
I 84
D 86
# include <rpcsvc/yp_prot.h>
E 86
I 86
D 102
  struct dom_binding { int dummy; };	/* needed on IRIX */
E 102
I 102
  struct dom_binding;	/* forward reference needed on IRIX */
E 102
E 86
# include <rpcsvc/ypclnt.h>
E 84
#endif
E 6

D 21

#ifdef DBM_MAP

E 21
/*
D 21
**  DBM_MAP_INIT -- DBM-style map initialization
E 21
I 21
**  MAP.C -- implementations for various map classes.
E 21
**
I 21
**	Each map class implements a series of functions:
**
**	bool map_parse(MAP *map, char *args)
**		Parse the arguments from the config file.  Return TRUE
**		if they were ok, FALSE otherwise.  Fill in map with the
**		values.
**
D 24
**	char *map_lookup(MAP *map, char buf[], int bufsize,
**			 char **args, int *pstat)
**		Look up the key given in buf in the given map.  If found,
**		do any rewriting the map wants (including "args" if desired)
E 24
I 24
**	char *map_lookup(MAP *map, char *key, char **args, int *pstat)
**		Look up the key in the given map.  If found, do any
**		rewriting the map wants (including "args" if desired)
E 24
**		and return the value.  Set *pstat to the appropriate status
D 24
**		on error and return NULL.
E 24
I 24
**		on error and return NULL.  Args will be NULL if called
**		from the alias routines, although this should probably
**		not be relied upon.  It is suggested you call map_rewrite
**		to return the results -- it takes care of null termination
**		and uses a dynamically expanded buffer as needed.
E 24
**
**	void map_store(MAP *map, char *key, char *value)
**		Store the key:value pair in the map.
**
D 22
**	void map_rebuild(MAP *map, FILE *fp, int automatic)
**		Rebuild the map.  If automatic is set, this is an
**		auto-rebuild.
**
E 22
**	bool map_open(MAP *map, int mode)
D 24
**		Open the map for the indicated mode.  Return TRUE if it
**		was opened successfully, FALSE otherwise.
E 24
I 24
**		Open the map for the indicated mode.  Mode should
**		be either O_RDONLY or O_RDWR.  Return TRUE if it
**		was opened successfully, FALSE otherwise.  If the open
**		failed an the MF_OPTIONAL flag is not set, it should
**		also print an error.  If the MF_ALIAS bit is set
**		and this map class understands the @:@ convention, it
**		should call aliaswait() before returning.
E 24
**
**	void map_close(MAP *map)
**		Close the map.
I 95
**
**	This file also includes the implementation for getcanonname.
**	It is currently implemented in a pretty ad-hoc manner; it ought
**	to be more properly integrated into the map structure.
E 95
*/

#define DBMMODE		0644
I 52

extern bool	aliaswait __P((MAP *, char *, int));
I 111
extern bool	extract_canonname __P((char *, char *, char[]));
E 111
E 52
/*
**  MAP_PARSEARGS -- parse config line arguments for database lookup
**
**	This is a generic version of the map_parse method.
**
E 21
**	Parameters:
D 21
**		map -- the pointer to the actual map
**		mapname -- the name of the map (for error messages)
**		args -- a pointer to the config file line arguments
E 21
I 21
**		map -- the map being initialized.
**		ap -- a pointer to the args on the config line.
E 21
**
**	Returns:
D 21
**		TRUE -- if it could successfully open the map.
E 21
I 21
**		TRUE -- if everything parsed OK.
E 21
**		FALSE -- otherwise.
**
**	Side Effects:
D 21
**		Gives an error if it can't open the map.
E 21
I 21
**		null terminates the filename; stores it in map
E 21
*/

bool
D 21
dbm_map_init(map, mapname, args)
E 21
I 21
map_parseargs(map, ap)
E 21
	MAP *map;
D 21
	char *mapname;
	char *args;
E 21
I 21
	char *ap;
E 21
{
D 21
	DBM *dbm;
E 21
I 21
	register char *p = ap;
E 21

I 37
	map->map_mflags |= MF_TRY0NULL | MF_TRY1NULL;
E 37
D 6
	map_parseargs(map, &args, mapname);
E 6
I 6
D 21
	map_parseargs(map, &args);
E 21
I 21
	for (;;)
	{
		while (isascii(*p) && isspace(*p))
			p++;
		if (*p != '-')
			break;
		switch (*++p)
		{
		  case 'N':
D 22
			map->map_flags |= MF_INCLNULL;
E 22
I 22
			map->map_mflags |= MF_INCLNULL;
I 37
			map->map_mflags &= ~MF_TRY0NULL;
E 37
E 22
			break;

I 37
		  case 'O':
			map->map_mflags &= ~MF_TRY1NULL;
			break;

E 37
		  case 'o':
D 22
			map->map_flags |= MF_OPTIONAL;
E 22
I 22
			map->map_mflags |= MF_OPTIONAL;
E 22
			break;

		  case 'f':
D 22
			map->map_flags |= MF_NOFOLDCASE;
E 22
I 22
			map->map_mflags |= MF_NOFOLDCASE;
E 22
			break;

		  case 'm':
D 22
			map->map_flags |= MF_MATCHONLY;
E 22
I 22
			map->map_mflags |= MF_MATCHONLY;
E 22
			break;

I 83
		  case 'A':
			map->map_mflags |= MF_APPEND;
			break;

I 105
		  case 'q':
			map->map_mflags |= MF_KEEPQUOTES;
			break;

E 105
E 83
		  case 'a':
			map->map_app = ++p;
			break;
I 65

		  case 'k':
			while (isascii(*++p) && isspace(*p))
				continue;
			map->map_keycolnm = p;
			break;

		  case 'v':
			while (isascii(*++p) && isspace(*p))
				continue;
			map->map_valcolnm = p;
			break;

		  case 'z':
			if (*++p != '\\')
				map->map_coldelim = *p;
			else
			{
				switch (*++p)
				{
				  case 'n':
					map->map_coldelim = '\n';
					break;

				  case 't':
					map->map_coldelim = '\t';
					break;

				  default:
					map->map_coldelim = '\\';
				}
			}
			break;
I 83
#ifdef RESERVED_FOR_SUN
		  case 'd':
			map->map_mflags |= MF_DOMAIN_WIDE;
			break;

		  case 's':
			/* info type */
			break;
#endif
E 83
E 65
D 23

		  case 'd':
			map->map_domain = ++p;
			break;
E 23
		}
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
			p++;
		if (*p != '\0')
			*p++ = '\0';
	}
	if (map->map_app != NULL)
		map->map_app = newstr(map->map_app);
I 65
	if (map->map_keycolnm != NULL)
		map->map_keycolnm = newstr(map->map_keycolnm);
	if (map->map_valcolnm != NULL)
		map->map_valcolnm = newstr(map->map_valcolnm);
E 65
D 23
	if (map->map_domain != NULL)
		map->map_domain = newstr(map->map_domain);
E 23

	if (*p != '\0')
	{
		map->map_file = p;
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
			p++;
		if (*p != '\0')
			*p++ = '\0';
		map->map_file = newstr(map->map_file);
	}

	while (*p != '\0' && isascii(*p) && isspace(*p))
		p++;
	if (*p != '\0')
		map->map_rebuild = newstr(p);

E 21
E 6
D 72
	if (map->map_file == NULL)
E 72
I 72
	if (map->map_file == NULL &&
	    !bitset(MCF_OPTFILE, map->map_class->map_cflags))
E 72
I 6
	{
D 21
		syserr("No file name for DBM map %s", mapname);
E 21
I 21
		syserr("No file name for %s map %s",
			map->map_class->map_cname, map->map_mname);
E 21
E 6
		return FALSE;
I 6
	}
E 6
D 21
	dbm = dbm_open(map->map_file, O_RDONLY, 0644);
E 21
I 21
	return TRUE;
}
/*
**  MAP_REWRITE -- rewrite a database key, interpolating %n indications.
**
**	It also adds the map_app string.  It can be used as a utility
**	in the map_lookup method.
**
**	Parameters:
**		map -- the map that causes this.
**		s -- the string to rewrite, NOT necessarily null terminated.
**		slen -- the length of s.
**		av -- arguments to interpolate into buf.
**
**	Returns:
D 71
**		Pointer to rewritten result.
E 71
I 71
**		Pointer to rewritten result.  This is static data that
**		should be copied if it is to be saved!
E 71
**
**	Side Effects:
**		none.
*/

I 28
struct rwbuf
{
	int	rwb_len;	/* size of buffer */
	char	*rwb_buf;	/* ptr to buffer */
};

struct rwbuf	RwBufs[2];	/* buffers for rewriting output */

E 28
char *
map_rewrite(map, s, slen, av)
	register MAP *map;
	register char *s;
	int slen;
	char **av;
{
	register char *bp;
	register char c;
	char **avp;
	register char *ap;
I 28
	register struct rwbuf *rwb;
E 28
	int i;
	int len;
D 28
	static int buflen = -1;
	static char *buf = NULL;
E 28

D 29
	if (tTd(23, 1))
E 29
I 29
	if (tTd(39, 1))
E 29
	{
D 26
		printf("map_rewrite(%.*s), av =\n", slen, s);
		for (avp = av; *avp != NULL; avp++)
			printf("\t%s\n", *avp);
E 26
I 26
		printf("map_rewrite(%.*s), av =", slen, s);
		if (av == NULL)
			printf(" (nullv)");
		else
		{
			for (avp = av; *avp != NULL; avp++)
				printf("\n\t%s", *avp);
		}
		printf("\n");
E 26
	}

I 28
	rwb = RwBufs;
	if (av == NULL)
		rwb++;

E 28
	/* count expected size of output (can safely overestimate) */
	i = len = slen;
	if (av != NULL)
	{
		bp = s;
		for (i = slen; --i >= 0 && (c = *bp++) != 0; )
		{
			if (c != '%')
				continue;
			if (--i < 0)
				break;
			c = *bp++;
			if (!(isascii(c) && isdigit(c)))
				continue;
D 39
			c -= 0;
			for (avp = av; --c >= 0 && *avp != NULL; avp++)
E 39
I 39
			for (avp = av; --c >= '0' && *avp != NULL; avp++)
E 39
				continue;
			if (*avp == NULL)
				continue;
			len += strlen(*avp);
		}
	}
	if (map->map_app != NULL)
		len += strlen(map->map_app);
D 28
	if (buflen < ++len)
E 28
I 28
	if (rwb->rwb_len < ++len)
E 28
	{
		/* need to malloc additional space */
D 28
		buflen = len;
		if (buf != NULL)
			free(buf);
		buf = xalloc(buflen);
E 28
I 28
		rwb->rwb_len = len;
		if (rwb->rwb_buf != NULL)
			free(rwb->rwb_buf);
		rwb->rwb_buf = xalloc(rwb->rwb_len);
E 28
	}

D 28
	bp = buf;
E 28
I 28
	bp = rwb->rwb_buf;
E 28
	if (av == NULL)
	{
		bcopy(s, bp, slen);
		bp += slen;
	}
	else
	{
		while (--slen >= 0 && (c = *s++) != '\0')
		{
			if (c != '%')
			{
  pushc:
				*bp++ = c;
				continue;
			}
			if (--slen < 0 || (c = *s++) == '\0')
				c = '%';
			if (c == '%')
				goto pushc;
			if (!(isascii(c) && isdigit(c)))
			{
				*bp++ = '%';
				goto pushc;
			}
D 39
			c -= '0';
			for (avp = av; --c >= 0 && *avp != NULL; avp++)
E 39
I 39
			for (avp = av; --c >= '0' && *avp != NULL; avp++)
E 39
				continue;
			if (*avp == NULL)
				continue;

			/* transliterate argument into output string */
			for (ap = *avp; (c = *ap++) != '\0'; )
				*bp++ = c;
		}
	}
	if (map->map_app != NULL)
		strcpy(bp, map->map_app);
	else
		*bp = '\0';
D 29
	if (tTd(23, 1))
E 29
I 29
	if (tTd(39, 1))
E 29
D 28
		printf("map_rewrite => %s\n", buf);
	return buf;
E 28
I 28
		printf("map_rewrite => %s\n", rwb->rwb_buf);
	return rwb->rwb_buf;
E 28
}
/*
I 29
**  INITMAPS -- initialize for aliasing
**
**	Parameters:
**		rebuild -- if TRUE, this rebuilds the cached versions.
**		e -- current envelope.
**
**	Returns:
**		none.
**
**	Side Effects:
**		initializes aliases:
**		if NDBM:  opens the database.
**		if ~NDBM: reads the aliases into the symbol table.
*/

I 106
void
E 106
initmaps(rebuild, e)
	bool rebuild;
	register ENVELOPE *e;
{
	extern void map_init();

I 50
D 114
#ifdef XDEBUG
E 114
I 114
#if XDEBUG
E 114
	checkfd012("entering initmaps");
#endif
E 50
	CurEnv = e;
D 55
	stabapply(map_init, rebuild);
E 55
I 55
	if (rebuild)
	{
		stabapply(map_init, 1);
		stabapply(map_init, 2);
	}
	else
	{
		stabapply(map_init, 0);
	}
E 55
I 50
D 114
#ifdef XDEBUG
E 114
I 114
#if XDEBUG
E 114
	checkfd012("exiting initmaps");
#endif
E 50
}

void
map_init(s, rebuild)
	register STAB *s;
	int rebuild;
{
	register MAP *map;

	/* has to be a map */
	if (s->s_type != ST_MAP)
		return;

	map = &s->s_map;
	if (!bitset(MF_VALID, map->map_mflags))
		return;

	if (tTd(38, 2))
D 55
		printf("map_init(%s:%s)\n",
E 55
I 55
D 65
		printf("map_init(%s:%s, %d)\n",
E 65
I 65
		printf("map_init(%s:%s, %s, %d)\n",
E 65
E 55
D 51
			map->map_class->map_cname, map->map_file);
E 51
I 51
			map->map_class->map_cname == NULL ? "NULL" :
				map->map_class->map_cname,
I 65
			map->map_mname == NULL ? "NULL" : map->map_mname,
E 65
D 55
			map->map_file == NULL ? "NULL" : map->map_file);
E 55
I 55
			map->map_file == NULL ? "NULL" : map->map_file,
			rebuild);
E 55
E 51

I 55
	if (rebuild == (bitset(MF_ALIAS, map->map_mflags) &&
		    bitset(MCF_REBUILDABLE, map->map_class->map_cflags) ? 1 : 2))
	{
		if (tTd(38, 3))
			printf("\twrong pass\n");
		return;
	}

E 55
	/* if already open, close it (for nested open) */
	if (bitset(MF_OPEN, map->map_mflags))
	{
		map->map_class->map_close(map);
		map->map_mflags &= ~(MF_OPEN|MF_WRITABLE);
	}

D 55
	if (rebuild)
E 55
I 55
	if (rebuild == 2)
E 55
	{
D 34
		if (bitset(MCF_REBUILDABLE, map->map_class->map_cflags))
E 34
I 34
D 55
		if (bitset(MF_ALIAS, map->map_mflags) &&
		    bitset(MCF_REBUILDABLE, map->map_class->map_cflags))
E 34
			rebuildaliases(map, FALSE);
E 55
I 55
		rebuildaliases(map, FALSE);
E 55
	}
	else
	{
		if (map->map_class->map_open(map, O_RDONLY))
		{
			if (tTd(38, 4))
D 55
				printf("%s:%s: valid\n",
E 55
I 55
D 65
				printf("\t%s:%s: valid\n",
E 65
I 65
				printf("\t%s:%s %s: valid\n",
E 65
E 55
D 51
					map->map_class->map_cname,
					map->map_file);
E 51
I 51
					map->map_class->map_cname == NULL ? "NULL" :
						map->map_class->map_cname,
I 65
					map->map_mname == NULL ? "NULL" :
						map->map_mname,
E 65
					map->map_file == NULL ? "NULL" :
						map->map_file);
E 51
			map->map_mflags |= MF_OPEN;
		}
D 74
		else if (tTd(38, 4))
D 55
			printf("%s:%s: invalid: %s\n",
E 55
I 55
D 65
			printf("\t%s:%s: invalid: %s\n",
E 65
I 65
			printf("\t%s:%s %s: invalid: %s\n",
E 65
E 55
D 51
				map->map_class->map_cname,
				map->map_file,
E 51
I 51
				map->map_class->map_cname == NULL ? "NULL" :
					map->map_class->map_cname,
I 65
				map->map_mname == NULL ? "NULL" :
					map->map_mname,
E 65
				map->map_file == NULL ? "NULL" :
					map->map_file,
E 51
				errstring(errno));
E 74
I 74
		else
		{
			if (tTd(38, 4))
				printf("\t%s:%s %s: invalid: %s\n",
					map->map_class->map_cname == NULL ? "NULL" :
						map->map_class->map_cname,
					map->map_mname == NULL ? "NULL" :
						map->map_mname,
					map->map_file == NULL ? "NULL" :
						map->map_file,
					errstring(errno));
			if (!bitset(MF_OPTIONAL, map->map_mflags))
			{
				extern MAPCLASS BogusMapClass;

				map->map_class = &BogusMapClass;
				map->map_mflags |= MF_OPEN;
			}
		}
E 74
	}
}
/*
I 109
**  GETCANONNAME -- look up name using service switch
**
**	Parameters:
**		host -- the host name to look up.
**		hbsize -- the size of the host buffer.
**		trymx -- if set, try MX records.
**
**	Returns:
**		TRUE -- if the host was found.
**		FALSE -- otherwise.
*/

bool
getcanonname(host, hbsize, trymx)
	char *host;
	int hbsize;
	bool trymx;
{
	int nmaps;
	int mapno;
	bool found = FALSE;
	auto int stat;
	char *maptype[MAXMAPSTACK];
	short mapreturn[MAXMAPACTIONS];
D 116
	extern int h_errno;
E 116

	nmaps = switch_map_find("hosts", maptype, mapreturn);
	for (mapno = 0; mapno < nmaps; mapno++)
	{
		int i;

		if (tTd(38, 20))
			printf("getcanonname(%s), trying %s\n",
				host, maptype[mapno]);
		if (strcmp("files", maptype[mapno]) == 0)
		{
			extern bool text_getcanonname __P((char *, int, int *));

			found = text_getcanonname(host, hbsize, &stat);
		}
#ifdef NIS
		else if (strcmp("nis", maptype[mapno]) == 0)
		{
			extern bool nis_getcanonname __P((char *, int, int *));

			found = nis_getcanonname(host, hbsize, &stat);
		}
#endif
#ifdef NISPLUS
		else if (strcmp("nisplus", maptype[mapno]) == 0)
		{
			extern bool nisplus_getcanonname __P((char *, int, int *));

			found = nisplus_getcanonname(host, hbsize, &stat);
		}
#endif
#if NAMED_BIND
		else if (strcmp("dns", maptype[mapno]) == 0)
		{
			extern bool dns_getcanonname __P((char *, int, bool, int *));

			found = dns_getcanonname(host, hbsize, trymx, &stat);
		}
#endif
		else
		{
			found = FALSE;
			stat = EX_UNAVAILABLE;
		}
		if (found)
			break;

		/* see if we should continue */
		if (stat == EX_TEMPFAIL)
			i = MA_TRYAGAIN;
		else if (stat == EX_NOHOST)
			i = MA_NOTFOUND;
		else
			i = MA_UNAVAIL;
		if (bitset(1 << mapno, mapreturn[i]))
			break;
	}

	if (found)
	{
		char *d;

		if (tTd(38, 20))
			printf("getcanonname(%s), found\n", host);

		/*
		**  If returned name is still single token, compensate
		**  by tagging on $m.  This is because some sites set
		**  up their DNS or NIS databases wrong.
		*/

		if ((d = strchr(host, '.')) == NULL || d[1] == '\0')
		{
			d = macvalue('m', CurEnv);
			if (d != NULL &&
			    hbsize > (int) (strlen(host) + strlen(d) + 1))
			{
				if (host[strlen(host) - 1] != '.')
					strcat(host, ".");
				strcat(host, d);
			}
			else
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	if (tTd(38, 20))
		printf("getcanonname(%s), failed, stat=%d\n", host, stat);

#if NAMED_BIND
	if (stat == EX_NOHOST)
		h_errno = HOST_NOT_FOUND;
	else
		h_errno = TRY_AGAIN;
#endif

	return FALSE;
}
/*
I 111
**  EXTRACT_CANONNAME -- extract canonical name from /etc/hosts entry
**
**	Parameters:
**		name -- the name against which to match.
**		line -- the /etc/hosts line.
**		cbuf -- the location to store the result.
**
**	Returns:
**		TRUE -- if the line matched the desired name.
**		FALSE -- otherwise.
*/

bool
extract_canonname(name, line, cbuf)
	char *name;
	char *line;
	char cbuf[];
{
	int i;
	char *p;
	bool found = FALSE;
	extern char *get_column();

	cbuf[0] = '\0';
	if (line[0] == '#')
		return FALSE;

D 113
	for (i = 1; !found; i++)
E 113
I 113
	for (i = 1; ; i++)
E 113
	{
		char nbuf[MAXNAME + 1];

		p = get_column(line, i, '\0', nbuf);
		if (p == NULL)
			break;
		if (cbuf[0] == '\0' ||
		    (strchr(cbuf, '.') == NULL && strchr(p, '.') != NULL))
			strcpy(cbuf, p);
		if (strcasecmp(name, p) == 0)
			found = TRUE;
	}
	if (found && strchr(cbuf, '.') == NULL)
	{
		/* try to add a domain on the end of the name */
		char *domain = macvalue('m', CurEnv);

		if (domain != NULL &&
		    strlen(domain) + strlen(cbuf) + 1 < MAXNAME)
		{
			p = &cbuf[strlen(cbuf)];
			*p++ = '.';
			strcpy(p, domain);
		}
	}
	return found;
}
/*
E 111
E 109
E 29
**  NDBM modules
*/

#ifdef NDBM

/*
**  DBM_MAP_OPEN -- DBM-style map open
*/

bool
ndbm_map_open(map, mode)
	MAP *map;
	int mode;
{
D 43
	DBM *dbm;
E 43
I 43
	register DBM *dbm;
	struct stat st;
E 43

D 29
	if (tTd(27, 2))
E 29
I 29
	if (tTd(38, 2))
E 29
D 65
		printf("ndbm_map_open(%s, %d)\n", map->map_file, mode);
E 65
I 65
		printf("ndbm_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);
E 65

I 22
	if (mode == O_RDWR)
		mode |= O_CREAT|O_TRUNC;

E 22
	/* open the database */
	dbm = dbm_open(map->map_file, mode, DBMMODE);
E 21
	if (dbm == NULL)
	{
I 52
D 77
#ifdef MAYBENEXTRELEASE
E 77
		if (aliaswait(map, ".pag", FALSE))
			return TRUE;
D 77
#endif
E 77
E 52
D 2
		syserr("Cannot open DBM database %s", map->map_file);
E 2
I 2
D 22
		if (!bitset(MF_OPTIONAL, map->map_flags))
E 22
I 22
		if (!bitset(MF_OPTIONAL, map->map_mflags))
E 22
			syserr("Cannot open DBM database %s", map->map_file);
E 2
		return FALSE;
	}
D 21
	map->map_db = (void *) dbm;
E 21
I 21
	map->map_db1 = (void *) dbm;
I 22
D 54
	if (mode == O_RDONLY && bitset(MF_ALIAS, map->map_mflags))
D 33
		aliaswait(map, ".dir");
E 33
I 33
D 52
		aliaswait(map, ".pag");
I 43
	if (fstat(dbm_dirfno(dbm), &st) >= 0)
E 52
I 52
		if (!aliaswait(map, ".pag", TRUE))
E 54
I 54
	if (mode == O_RDONLY)
	{
		if (bitset(MF_ALIAS, map->map_mflags) &&
		    !aliaswait(map, ".pag", TRUE))
E 54
			return FALSE;
I 54
	}
	else
	{
		int fd;

		/* exclusive lock for duration of rebuild */
		fd = dbm_dirfno((DBM *) map->map_db1);
		if (fd >= 0 && !bitset(MF_LOCKED, map->map_mflags) &&
		    lockfile(fd, map->map_file, ".dir", LOCK_EX))
			map->map_mflags |= MF_LOCKED;
	}
E 54
	if (fstat(dbm_dirfno((DBM *) map->map_db1), &st) >= 0)
E 52
		map->map_mtime = st.st_mtime;
E 43
E 33
E 22
E 21
	return TRUE;
}
D 21
/*
E 21
I 21


/*
E 21
**  DBM_MAP_LOOKUP -- look up a datum in a DBM-type map
D 21
**
**	Parameters:
**		map -- the map to look up in.
**		buf -- a pointer to to the buffer containing the key.
**			This is a null terminated string.
**		bufsiz -- the size of buf -- note that this is in general
**			larger that strlen(buf), and buf can be changed
**			in place if desired.
**		av -- arguments from the config file (can be interpolated
**			into the final result).
I 16
**		statp -- pointer to status word (out-parameter).
E 16
**
**	Returns:
**		A pointer to the rewritten result.
**		NULL if not found in the map.
E 21
*/

char *
D 16
dbm_map_lookup(map, buf, bufsiz, av)
E 16
I 16
D 21
dbm_map_lookup(map, buf, bufsiz, av, statp)
E 21
I 21
ndbm_map_lookup(map, name, av, statp)
E 21
E 16
	MAP *map;
D 21
	char buf[];
	int bufsiz;
E 21
I 21
	char *name;
E 21
	char **av;
I 16
	int *statp;
E 16
{
	datum key, val;
I 46
	int fd;
E 46
I 21
	char keybuf[MAXNAME + 1];
E 21

D 21
	key.dptr = buf;
	key.dsize = strlen(buf);
E 21
I 21
D 29
	if (tTd(27, 20))
E 29
I 29
	if (tTd(38, 20))
E 29
D 65
		printf("ndbm_map_lookup(%s)\n", name);
E 65
I 65
		printf("ndbm_map_lookup(%s, %s)\n",
			map->map_mname, name);
E 65

	key.dptr = name;
	key.dsize = strlen(name);
E 21
I 4
D 5
	if (bitset(MF_FOLDCASE, map->map_flags))
E 5
I 5
D 22
	if (!bitset(MF_NOFOLDCASE, map->map_flags))
E 22
I 22
	if (!bitset(MF_NOFOLDCASE, map->map_mflags))
E 22
E 5
	{
D 21
		register char *p;

		for (p = buf; *p != '\0'; p++)
D 12
			if (isupper(*p))
E 12
I 12
			if (isascii(*p) && isupper(*p))
E 12
				*p = tolower(*p);
E 21
I 21
		if (key.dsize > sizeof keybuf - 1)
			key.dsize = sizeof keybuf - 1;
		bcopy(key.dptr, keybuf, key.dsize + 1);
		makelower(keybuf);
		key.dptr = keybuf;
E 21
	}
E 4
D 22
	if (bitset(MF_INCLNULL, map->map_flags))
E 22
I 22
D 37
	if (bitset(MF_INCLNULL, map->map_mflags))
E 22
		key.dsize++;
E 37
I 18
D 19
	(void) lockfile(dbm_dirfno(map->map_db), map->map_file, LOCK_SH);
E 18
	val = dbm_fetch(map->map_db, key);
I 18
	(void) lockfile(dbm_dirfno(map->map_db), map->map_file, LOCK_UN);
E 19
I 19
D 21
	(void) lockfile(dbm_dirfno((DBM *) map->map_db), map->map_file, LOCK_SH);
	val = dbm_fetch((DBM *) map->map_db, key);
	(void) lockfile(dbm_dirfno((DBM *) map->map_db), map->map_file, LOCK_UN);
E 21
I 21
D 44
	(void) lockfile(dbm_dirfno((DBM *) map->map_db1), map->map_file, LOCK_SH);
E 44
I 44
D 46
	(void) lockfile(dbm_dirfno((DBM *) map->map_db1), map->map_file,
			".dir", LOCK_SH);
E 46
I 46
	fd = dbm_dirfno((DBM *) map->map_db1);
D 47
	if (fd >= 0)
E 47
I 47
	if (fd >= 0 && !bitset(MF_LOCKED, map->map_mflags))
E 47
		(void) lockfile(fd, map->map_file, ".dir", LOCK_SH);
E 46
E 44
D 37
	val = dbm_fetch((DBM *) map->map_db1, key);
E 37
I 37
	val.dptr = NULL;
	if (bitset(MF_TRY0NULL, map->map_mflags))
	{
		val = dbm_fetch((DBM *) map->map_db1, key);
		if (val.dptr != NULL)
			map->map_mflags &= ~MF_TRY1NULL;
	}
	if (val.dptr == NULL && bitset(MF_TRY1NULL, map->map_mflags))
	{
		key.dsize++;
		val = dbm_fetch((DBM *) map->map_db1, key);
		if (val.dptr != NULL)
			map->map_mflags &= ~MF_TRY0NULL;
	}
E 37
D 44
	(void) lockfile(dbm_dirfno((DBM *) map->map_db1), map->map_file, LOCK_UN);
E 44
I 44
D 46
	(void) lockfile(dbm_dirfno((DBM *) map->map_db1), map->map_file,
			".dir", LOCK_UN);
E 46
I 46
D 47
	if (fd >= 0)
E 47
I 47
	if (fd >= 0 && !bitset(MF_LOCKED, map->map_mflags))
E 47
		(void) lockfile(fd, map->map_file, ".dir", LOCK_UN);
E 46
E 44
E 21
E 19
E 18
	if (val.dptr == NULL)
		return NULL;
D 6
	map_rewrite(val.dptr, val.dsize, buf, bufsiz, av);
E 6
I 6
D 21
	if (!bitset(MF_MATCHONLY, map->map_flags))
		map_rewrite(val.dptr, val.dsize, buf, bufsiz, av);
E 6
	return buf;
E 21
I 21
D 22
	if (bitset(MF_MATCHONLY, map->map_flags))
E 22
I 22
	if (bitset(MF_MATCHONLY, map->map_mflags))
E 22
D 37
		av = NULL;
	return map_rewrite(map, val.dptr, val.dsize, av);
E 37
I 37
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, val.dptr, val.dsize, av);
E 37
E 21
}

D 21
#endif /* DBM_MAP */

#ifdef BTREE_MAP
E 21

/*
D 21
**  BTREE_MAP_INIT -- BTREE-style map initialization
**
**	Parameters:
**		map -- the pointer to the actual map
**		mapname -- the name of the map (for error messages)
**		args -- a pointer to the config file line arguments
**
**	Returns:
**		TRUE -- if it could successfully open the map.
**		FALSE -- otherwise.
**
**	Side Effects:
**		Gives an error if it can't open the map.
E 21
I 21
**  DBM_MAP_STORE -- store a datum in the database
E 21
*/

I 21
void
ndbm_map_store(map, lhs, rhs)
	register MAP *map;
	char *lhs;
	char *rhs;
{
	datum key;
	datum data;
	int stat;

D 29
	if (tTd(27, 12))
E 29
I 29
	if (tTd(38, 12))
E 29
D 65
		printf("ndbm_map_store(%s, %s)\n", lhs, rhs);
E 65
I 65
		printf("ndbm_map_store(%s, %s, %s)\n",
			map->map_mname, lhs, rhs);
E 65

	key.dsize = strlen(lhs);
	key.dptr = lhs;

	data.dsize = strlen(rhs);
	data.dptr = rhs;

D 22
	if (bitset(MF_INCLNULL, map->map_flags))
E 22
I 22
	if (bitset(MF_INCLNULL, map->map_mflags))
E 22
	{
		key.dsize++;
		data.dsize++;
	}

	stat = dbm_store((DBM *) map->map_db1, key, data, DBM_INSERT);
	if (stat > 0)
	{
D 83
		usrerr("050 Warning: duplicate alias name %s", lhs);
E 83
I 83
		if (!bitset(MF_APPEND, map->map_mflags))
			usrerr("050 Warning: duplicate alias name %s", lhs);
		else
		{
			static char *buf = NULL;
			static int bufsiz = 0;
I 94
			auto int xstat;
E 94
			datum old;

D 94
			old.dptr = ndbm_map_lookup(map, key.dptr, NULL);
E 94
I 94
			old.dptr = ndbm_map_lookup(map, key.dptr, NULL, &xstat);
E 94
			if (old.dptr != NULL && *old.dptr != '\0')
			{
				old.dsize = strlen(old.dptr);
				if (data.dsize + old.dsize + 2 > bufsiz)
				{
					if (buf != NULL)
						(void) free(buf);
					bufsiz = data.dsize + old.dsize + 2;
					buf = xalloc(bufsiz);
				}
				sprintf(buf, "%s,%s", data.dptr, old.dptr);
				data.dsize = data.dsize + old.dsize + 1;
				data.dptr = buf;
				if (tTd(38, 9))
					printf("ndbm_map_store append=%s\n", data.dptr);
			}
		}
E 83
		stat = dbm_store((DBM *) map->map_db1, key, data, DBM_REPLACE);
	}
	if (stat != 0)
		syserr("readaliases: dbm put (%s)", lhs);
}


/*
D 22
**  DBM_MAP_REBUILD -- rebuild DBM database
E 22
I 22
**  NDBM_MAP_CLOSE -- close the database
E 22
*/

void
D 22
ndbm_map_rebuild(map, fp, automatic)
	register MAP *map;
	FILE *fp;
	int automatic;
{
	register DBM *db;
	int i;
	char buf[MAXNAME];

	if (tTd(27, 2))
		printf("ndbm_map_rebuild(%s)\n", map->map_file);

	db = dbm_open(map->map_file, O_RDWR|O_CREAT|O_TRUNC, DBMMODE);
	if (db == NULL)
	{
		syserr("ndbm_map_rebuild: cannot create %s", buf);
		return;
	}
	map->map_db1 = (void *) db;
	map->map_flags |= MF_WRITABLE|MF_VALID;
}

/*
**  NDBM_ACLOSE -- close the database
*/

void
E 22
ndbm_map_close(map)
	register MAP  *map;
{
I 59
	if (tTd(38, 9))
D 65
		printf("ndbm_map_close(%s, %x)\n", map->map_file, map->map_mflags);
E 65
I 65
		printf("ndbm_map_close(%s, %s, %x)\n",
			map->map_mname, map->map_file, map->map_mflags);
E 65

E 59
D 22
	if (bitset(MF_WRITABLE, map->map_flags))
E 22
I 22
	if (bitset(MF_WRITABLE, map->map_mflags))
E 22
	{
D 42
#ifdef YPCOMPAT
E 42
I 42
#ifdef NIS
E 42
I 41
		bool inclnull;
E 41
		char buf[200];

I 41
		inclnull = bitset(MF_INCLNULL, map->map_mflags);
		map->map_mflags &= ~MF_INCLNULL;

E 41
D 102
		(void) sprintf(buf, "%010ld", curtime());
		ndbm_map_store(map, "YP_LAST_MODIFIED", buf);
E 102
I 102
		if (strstr(map->map_file, "/yp/") != NULL)
		{
			(void) sprintf(buf, "%010ld", curtime());
			ndbm_map_store(map, "YP_LAST_MODIFIED", buf);
E 102

D 53
		(void) myhostname(buf, sizeof buf);
E 53
I 53
D 102
		(void) gethostname(buf, sizeof buf);
E 53
		ndbm_map_store(map, "YP_MASTER_NAME", buf);
E 102
I 102
			(void) gethostname(buf, sizeof buf);
			ndbm_map_store(map, "YP_MASTER_NAME", buf);
		}
E 102
I 41

		if (inclnull)
			map->map_mflags |= MF_INCLNULL;
E 41
#endif

		/* write out the distinguished alias */
		ndbm_map_store(map, "@", "@");
	}
	dbm_close((DBM *) map->map_db1);
}

#endif
/*
D 31
**  HASH (NEWDB) Modules
E 31
I 31
**  NEWDB (Hash and BTree) Modules
E 31
*/

#ifdef NEWDB

/*
D 31
**  BTREE_MAP_PARSE -- BTREE-style map initialization
E 31
I 31
**  BT_MAP_OPEN, HASH_MAP_OPEN -- database open primitives.
**
**	These do rather bizarre locking.  If you can lock on open,
**	do that to avoid the condition of opening a database that
**	is being rebuilt.  If you don't, we'll try to fake it, but
**	there will be a race condition.  If opening for read-only,
**	we immediately release the lock to avoid freezing things up.
**	We really ought to hold the lock, but guarantee that we won't
**	be pokey about it.  That's hard to do.
E 31
*/

E 21
bool
D 21
bt_map_init(map, mapname, args)
E 21
I 21
bt_map_open(map, mode)
E 21
	MAP *map;
D 21
	char *mapname;
	char *args;
E 21
I 21
	int mode;
E 21
{
	DB *db;
I 25
	int i;
I 31
	int omode;
I 46
	int fd;
E 46
I 43
	struct stat st;
E 43
E 31
E 25
I 21
D 87
	char buf[MAXNAME];
E 87
I 87
	char buf[MAXNAME + 1];
E 87
E 21

D 6
	map_parseargs(map, &args, mapname);
E 6
I 6
D 21
	map_parseargs(map, &args);
E 6
	if (map->map_file == NULL)
I 6
	{
		syserr("No file name for BTREE map %s", mapname);
E 6
		return FALSE;
I 6
	}
E 6
	db = dbopen(map->map_file, O_RDONLY, 0644, DB_BTREE, NULL);
E 21
I 21
D 29
	if (tTd(27, 2))
E 29
I 29
	if (tTd(38, 2))
E 29
D 65
		printf("bt_map_open(%s, %d)\n", map->map_file, mode);
E 65
I 65
		printf("bt_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);
E 65

I 22
D 31
	if (mode == O_RDWR)
		mode |= O_CREAT|O_TRUNC;
E 31
I 31
	omode = mode;
	if (omode == O_RDWR)
	{
		omode |= O_CREAT|O_TRUNC;
D 40
#if defined(O_EXLOCK) && !defined(LOCKF)
E 40
I 40
D 56
#if defined(O_EXLOCK) && defined(HASFLOCK)
E 56
I 56
#if defined(O_EXLOCK) && HASFLOCK
E 56
E 40
		omode |= O_EXLOCK;
D 60
# if !defined(OLD_NEWDB)
E 60
I 60
# if !OLD_NEWDB
E 60
	}
	else
	{
		omode |= O_SHLOCK;
# endif
#endif
	}
E 31

E 22
D 25
	(void) sprintf(buf, "%s.db", map->map_file);
E 25
I 25
	(void) strcpy(buf, map->map_file);
	i = strlen(buf);
	if (i < 3 || strcmp(&buf[i - 3], ".db") != 0)
		(void) strcat(buf, ".db");
E 25
D 24
	db = dbopen(buf, mode, 0644, DB_BTREE, NULL);
E 24
I 24
D 31
	db = dbopen(buf, mode, DBMMODE, DB_BTREE, NULL);
E 31
I 31
	db = dbopen(buf, omode, DBMMODE, DB_BTREE, NULL);
E 31
E 24
E 21
	if (db == NULL)
	{
I 52
#ifdef MAYBENEXTRELEASE
		if (aliaswait(map, ".db", FALSE))
			return TRUE;
#endif
E 52
D 2
		syserr("Cannot open BTREE database %s", map->map_file);
E 2
I 2
D 22
		if (!bitset(MF_OPTIONAL, map->map_flags))
E 22
I 22
		if (!bitset(MF_OPTIONAL, map->map_mflags))
E 22
			syserr("Cannot open BTREE database %s", map->map_file);
E 2
		return FALSE;
	}
I 31
D 40
#if !defined(OLD_NEWDB) && !defined(LOCKF)
E 40
I 40
D 56
#if !defined(OLD_NEWDB) && defined(HASFLOCK)
E 56
I 56
D 60
#if !defined(OLD_NEWDB) && HASFLOCK
E 60
I 60
D 62
#if !OLD_NEWDB && HASFLOCK
E 62
I 62
#if !OLD_NEWDB
E 62
E 60
E 56
I 46
	fd = db->fd(db);
I 62
D 63
#endif
#if HASFLOCK
E 62
E 46
E 40
# if !defined(O_EXLOCK)
E 63
I 63
D 91
# if HASFLOCK
#  if !defined(O_EXLOCK)
E 91
I 91
# if defined(O_EXLOCK) && HASFLOCK
	if (fd >= 0)
	{
		if (mode == O_RDONLY)
			(void) lockfile(fd, map->map_file, ".db", LOCK_UN);
		else
			map->map_mflags |= MF_LOCKED;
	}
# else
E 91
E 63
D 46
	if (mode == O_RDWR)
D 44
		(void) lockfile(db->fd(db), map->map_file, LOCK_EX);
E 44
I 44
		(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_EX);
E 46
I 46
	if (mode == O_RDWR && fd >= 0)
D 47
		(void) lockfile(fd, map->map_file, ".db", LOCK_EX);
E 47
I 47
	{
		if (lockfile(fd, map->map_file, ".db", LOCK_EX))
			map->map_mflags |= MF_LOCKED;
	}
E 47
E 46
E 44
D 63
# else
E 63
I 63
D 91
#  else
E 63
D 46
	if (mode == O_RDONLY)
D 44
		(void) lockfile(db->fd(db), map->map_file, LOCK_UN);
E 44
I 44
		(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_UN);
E 46
I 46
	if (mode == O_RDONLY && fd >= 0)
		(void) lockfile(fd, map->map_file, ".db", LOCK_UN);
I 47
	else
		map->map_mflags |= MF_LOCKED;
I 63
#  endif
E 91
E 63
E 47
E 46
E 44
# endif
#endif
I 32

	/* try to make sure that at least the database header is on disk */
	if (mode == O_RDWR)
I 46
D 60
#ifdef OLD_NEWDB
E 60
I 60
#if OLD_NEWDB
E 60
		(void) db->sync(db);
#else
E 46
		(void) db->sync(db, 0);

I 43
D 46
#ifndef OLD_NEWDB
	if (fstat(db->fd(db), &st) >= 0)
E 46
I 46
	if (fd >= 0 && fstat(fd, &st) >= 0)
E 46
		map->map_mtime = st.st_mtime;
#endif

E 43
E 32
E 31
D 21
	map->map_db = (void *) db;
E 21
I 21
	map->map_db2 = (void *) db;
I 22
	if (mode == O_RDONLY && bitset(MF_ALIAS, map->map_mflags))
D 52
		aliaswait(map, ".db");
E 52
I 52
		if (!aliaswait(map, ".db", TRUE))
			return FALSE;
E 52
E 22
E 21
	return TRUE;
}

D 21
#endif /* BTREE_MAP */

#ifdef HASH_MAP
E 21

/*
**  HASH_MAP_INIT -- HASH-style map initialization
D 21
**
**	Parameters:
**		map -- the pointer to the actual map
**		mapname -- the name of the map (for error messages)
**		args -- a pointer to the config file line arguments
**
**	Returns:
**		TRUE -- if it could successfully open the map.
**		FALSE -- otherwise.
**
**	Side Effects:
**		Gives an error if it can't open the map.
E 21
*/

bool
D 21
hash_map_init(map, mapname, args)
E 21
I 21
hash_map_open(map, mode)
E 21
	MAP *map;
D 21
	char *mapname;
	char *args;
E 21
I 21
	int mode;
E 21
{
	DB *db;
I 25
	int i;
I 31
	int omode;
I 46
	int fd;
E 46
I 43
	struct stat st;
E 43
E 31
E 25
I 21
D 87
	char buf[MAXNAME];
E 87
I 87
	char buf[MAXNAME + 1];
E 87
E 21

D 6
	map_parseargs(map, &args, mapname);
E 6
I 6
D 21
	map_parseargs(map, &args);
E 6
	if (map->map_file == NULL)
I 6
	{
		syserr("No file name for HASH map %s", mapname);
E 6
		return FALSE;
I 6
	}
E 6
	db = dbopen(map->map_file, O_RDONLY, 0644, DB_HASH, NULL);
E 21
I 21
D 29
	if (tTd(27, 2))
E 29
I 29
	if (tTd(38, 2))
E 29
D 65
		printf("hash_map_open(%s, %d)\n", map->map_file, mode);
E 65
I 65
		printf("hash_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);
E 65

I 22
D 31
	if (mode == O_RDWR)
		mode |= O_CREAT|O_TRUNC;
E 31
I 31
	omode = mode;
	if (omode == O_RDWR)
	{
		omode |= O_CREAT|O_TRUNC;
D 40
#if defined(O_EXLOCK) && !defined(LOCKF)
E 40
I 40
D 56
#if defined(O_EXLOCK) && defined(HASFLOCK)
E 56
I 56
#if defined(O_EXLOCK) && HASFLOCK
E 56
E 40
		omode |= O_EXLOCK;
D 60
# if !defined(OLD_NEWDB)
E 60
I 60
# if !OLD_NEWDB
E 60
	}
	else
	{
		omode |= O_SHLOCK;
# endif
#endif
	}
E 31

E 22
D 25
	(void) sprintf(buf, "%s.db", map->map_file);
E 25
I 25
	(void) strcpy(buf, map->map_file);
	i = strlen(buf);
	if (i < 3 || strcmp(&buf[i - 3], ".db") != 0)
		(void) strcat(buf, ".db");
E 25
D 24
	db = dbopen(buf, mode, 0644, DB_HASH, NULL);
E 24
I 24
D 31
	db = dbopen(buf, mode, DBMMODE, DB_HASH, NULL);
E 31
I 31
	db = dbopen(buf, omode, DBMMODE, DB_HASH, NULL);
E 31
E 24
E 21
	if (db == NULL)
	{
I 52
#ifdef MAYBENEXTRELEASE
		if (aliaswait(map, ".db", FALSE))
			return TRUE;
#endif
E 52
D 2
		syserr("Cannot open HASH database %s", map->map_file);
E 2
I 2
D 22
		if (!bitset(MF_OPTIONAL, map->map_flags))
E 22
I 22
		if (!bitset(MF_OPTIONAL, map->map_mflags))
E 22
			syserr("Cannot open HASH database %s", map->map_file);
E 2
		return FALSE;
	}
I 31
D 40
#if !defined(OLD_NEWDB) && !defined(LOCKF)
E 40
I 40
D 56
#if !defined(OLD_NEWDB) && defined(HASFLOCK)
E 56
I 56
D 60
#if !defined(OLD_NEWDB) && HASFLOCK
E 60
I 60
D 62
#if !OLD_NEWDB && HASFLOCK
E 62
I 62
#if !OLD_NEWDB
E 62
E 60
E 56
I 46
	fd = db->fd(db);
I 62
D 63
#endif
#if HASFLOCK
E 62
E 46
E 40
# if !defined(O_EXLOCK)
E 63
I 63
D 91
# if HASFLOCK
#  if !defined(O_EXLOCK)
E 91
I 91
# if defined(O_EXLOCK) && HASFLOCK
	if (fd >= 0)
	{
		if (mode == O_RDONLY)
			(void) lockfile(fd, map->map_file, ".db", LOCK_UN);
		else
			map->map_mflags |= MF_LOCKED;
	}
# else
E 91
E 63
D 46
	if (mode == O_RDWR)
D 44
		(void) lockfile(db->fd(db), map->map_file, LOCK_EX);
E 44
I 44
		(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_EX);
E 46
I 46
	if (mode == O_RDWR && fd >= 0)
D 47
		(void) lockfile(fd, map->map_file, ".db", LOCK_EX);
E 47
I 47
	{
		if (lockfile(fd, map->map_file, ".db", LOCK_EX))
			map->map_mflags |= MF_LOCKED;
	}
E 47
E 46
E 44
D 63
# else
E 63
I 63
D 91
#  else
E 63
D 46
	if (mode == O_RDONLY)
D 44
		(void) lockfile(db->fd(db), map->map_file, LOCK_UN);
E 44
I 44
		(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_UN);
E 46
I 46
	if (mode == O_RDONLY && fd >= 0)
		(void) lockfile(fd, map->map_file, ".db", LOCK_UN);
I 47
	else
		map->map_mflags |= MF_LOCKED;
I 63
#  endif
E 91
E 63
E 47
E 46
E 44
# endif
#endif
I 32

	/* try to make sure that at least the database header is on disk */
	if (mode == O_RDWR)
I 46
D 60
#ifdef OLD_NEWDB
E 60
I 60
#if OLD_NEWDB
E 60
		(void) db->sync(db);
#else
E 46
		(void) db->sync(db, 0);

I 43
D 46
#ifndef OLD_NEWDB
	if (fstat(db->fd(db), &st) >= 0)
E 46
I 46
	if (fd >= 0 && fstat(fd, &st) >= 0)
E 46
		map->map_mtime = st.st_mtime;
#endif

E 43
E 32
E 31
D 21
	map->map_db = (void *) db;
E 21
I 21
	map->map_db2 = (void *) db;
I 22
	if (mode == O_RDONLY && bitset(MF_ALIAS, map->map_mflags))
D 52
		aliaswait(map, ".db");
E 52
I 52
		if (!aliaswait(map, ".db", TRUE))
			return FALSE;
E 52
E 22
E 21
	return TRUE;
}

D 21
#endif /* HASH_MAP */

#if defined(BTREE_MAP) || defined(HASH_MAP)
E 21

/*
**  DB_MAP_LOOKUP -- look up a datum in a BTREE- or HASH-type map
D 21
**
**	Parameters:
**		map -- the map to look up in.
**		buf -- a pointer to to the buffer containing the key.
**			This is a null terminated string.
**		bufsiz -- the size of buf -- note that this is in general
**			larger that strlen(buf), and buf can be changed
**			in place if desired.
**		av -- arguments from the config file (can be interpolated
**			into the final result).
I 16
**		statp -- pointer to status word (out-parameter).
E 16
**
**	Returns:
**		A pointer to the rewritten result.
**		NULL if not found in the map.
E 21
*/

char *
D 16
db_map_lookup(map, buf, bufsiz, av)
E 16
I 16
D 21
db_map_lookup(map, buf, bufsiz, av, statp)
E 21
I 21
db_map_lookup(map, name, av, statp)
E 21
E 16
	MAP *map;
D 21
	char buf[];
	int bufsiz;
E 21
I 21
	char *name;
E 21
	char **av;
I 16
	int *statp;
E 16
{
	DBT key, val;
I 27
	register DB *db = (DB *) map->map_db2;
	int st;
	int saveerrno;
I 46
	int fd;
E 46
E 27
I 21
	char keybuf[MAXNAME + 1];
E 21

D 21
	key.data = buf;
	key.size = strlen(buf);
I 3
D 5
	if (bitset(MF_FOLDCASE, map->map_flags))
E 5
I 5
	if (!bitset(MF_NOFOLDCASE, map->map_flags))
E 5
	{
		register char *p;
E 21
I 21
D 29
	if (tTd(27, 20))
E 29
I 29
	if (tTd(38, 20))
E 29
D 65
		printf("db_map_lookup(%s)\n", name);
E 65
I 65
		printf("db_map_lookup(%s, %s)\n",
			map->map_mname, name);
E 65
E 21

D 21
		for (p = buf; *p != '\0'; p++)
D 12
			if (isupper(*p))
E 12
I 12
			if (isascii(*p) && isupper(*p))
E 12
				*p = tolower(*p);
	}
E 21
I 21
	key.size = strlen(name);
	if (key.size > sizeof keybuf - 1)
		key.size = sizeof keybuf - 1;
	key.data = keybuf;
	bcopy(name, keybuf, key.size + 1);
D 22
	if (!bitset(MF_NOFOLDCASE, map->map_flags))
E 22
I 22
	if (!bitset(MF_NOFOLDCASE, map->map_mflags))
E 22
		makelower(keybuf);
E 21
E 3
D 22
	if (bitset(MF_INCLNULL, map->map_flags))
E 22
I 22
D 37
	if (bitset(MF_INCLNULL, map->map_mflags))
E 22
		key.size++;
E 37
D 2
	if ((*((DB *) map->map_db)->get)((DB *) map->map_db, &key, &val, 0) != 0)
E 2
I 2
D 21
	if (((DB *) map->map_db)->get((DB *) map->map_db, &key, &val, 0) != 0)
E 21
I 21
D 27
	if (((DB *) map->map_db2)->get((DB *) map->map_db2, &key, &val, 0) != 0)
E 27
I 27
D 60
#ifndef OLD_NEWDB
E 60
I 60
#if !OLD_NEWDB
E 60
D 44
	(void) lockfile(db->fd(db), map->map_file, LOCK_SH);
E 44
I 44
D 47
	(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_SH);
E 47
I 47
	fd = db->fd(db);
	if (fd >= 0 && !bitset(MF_LOCKED, map->map_mflags))
		(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_SH);
E 47
E 44
#endif
D 37
	st = db->get(db, &key, &val, 0);
E 37
I 37
	st = 1;
	if (bitset(MF_TRY0NULL, map->map_mflags))
	{
		st = db->get(db, &key, &val, 0);
		if (st == 0)
			map->map_mflags &= ~MF_TRY1NULL;
	}
	if (st != 0 && bitset(MF_TRY1NULL, map->map_mflags))
	{
		key.size++;
		st = db->get(db, &key, &val, 0);
		if (st == 0)
			map->map_mflags &= ~MF_TRY0NULL;
	}
E 37
	saveerrno = errno;
D 60
#ifndef OLD_NEWDB
E 60
I 60
#if !OLD_NEWDB
E 60
D 44
	(void) lockfile(db->fd(db), map->map_file, LOCK_UN);
E 44
I 44
D 46
	(void) lockfile(db->fd(db), map->map_file, ".db", LOCK_UN);
E 46
I 46
D 47
	fd = db->fd(db);
	if (fd >= 0)
E 47
I 47
	if (fd >= 0 && !bitset(MF_LOCKED, map->map_mflags))
E 47
		(void) lockfile(fd, map->map_file, ".db", LOCK_UN);
E 46
E 44
#endif
	if (st != 0)
	{
		errno = saveerrno;
		if (st < 0)
			syserr("db_map_lookup: get (%s)", name);
E 27
E 21
E 2
		return NULL;
I 27
	}
E 27
D 6
	map_rewrite(val.data, val.size, buf, bufsiz, av);
E 6
I 6
D 21
	if (!bitset(MF_MATCHONLY, map->map_flags))
		map_rewrite(val.data, val.size, buf, bufsiz, av);
E 6
	return buf;
E 21
I 21
D 22
	if (bitset(MF_MATCHONLY, map->map_flags))
E 22
I 22
	if (bitset(MF_MATCHONLY, map->map_mflags))
E 22
D 37
		av = NULL;
	return map_rewrite(map, val.data, val.size, av);
E 37
I 37
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, val.data, val.size, av);
E 37
E 21
}

D 21
#endif /* BTREE_MAP || HASH_MAP */
/*
**  MAP_PARSEARGS -- parse config line arguments for database lookup
**
**	Parameters:
**		map -- the map being initialized.
**		pp -- an indirect pointer to the config line.  It will
**			be replaced with a pointer to the next field
**			on the line.
D 6
**		mapname -- the name of the map (for errors).
E 6
**
**	Returns:
**		none
**
**	Side Effects:
**		null terminates the filename; stores it in map
E 21
I 21

/*
**  DB_MAP_STORE -- store a datum in the NEWDB database
E 21
*/

D 6
map_parseargs(map, pp, mapname)
E 6
I 6
D 21
map_parseargs(map, pp)
E 6
	MAP *map;
	char **pp;
E 21
I 21
void
db_map_store(map, lhs, rhs)
	register MAP *map;
	char *lhs;
	char *rhs;
E 21
D 6
	char *mapname;
E 6
{
D 21
	register char *p = *pp;
E 21
I 21
	int stat;
	DBT key;
	DBT data;
	register DB *db = map->map_db2;
E 21

D 21
	for (;;)
E 21
I 21
D 29
	if (tTd(27, 20))
E 29
I 29
	if (tTd(38, 20))
E 29
D 65
		printf("db_map_store(%s, %s)\n", lhs, rhs);
E 65
I 65
		printf("db_map_store(%s, %s, %s)\n",
			map->map_mname, lhs, rhs);
E 65

	key.size = strlen(lhs);
	key.data = lhs;

	data.size = strlen(rhs);
	data.data = rhs;

D 22
	if (bitset(MF_INCLNULL, map->map_flags))
E 22
I 22
	if (bitset(MF_INCLNULL, map->map_mflags))
E 22
E 21
	{
D 12
		while (isspace(*p))
E 12
I 12
D 21
		while (isascii(*p) && isspace(*p))
E 12
			p++;
		if (*p != '-')
			break;
		switch (*++p)
		{
		  case 'N':
			map->map_flags |= MF_INCLNULL;
			break;
E 21
I 21
		key.size++;
		data.size++;
	}
E 21
I 2

D 21
		  case 'o':
			map->map_flags |= MF_OPTIONAL;
I 3
			break;
E 21
I 21
	stat = db->put(db, &key, &data, R_NOOVERWRITE);
	if (stat > 0)
	{
D 83
		usrerr("050 Warning: duplicate alias name %s", lhs);
E 83
I 83
		if (!bitset(MF_APPEND, map->map_mflags))
			usrerr("050 Warning: duplicate alias name %s", lhs);
		else
		{
			static char *buf = NULL;
			static int bufsiz = 0;
			DBT old;

			old.data = db_map_lookup(map, key.data, NULL, &stat);
			if (old.data != NULL)
			{
				old.size = strlen(old.data);
				if (data.size + old.size + 2 > bufsiz)
				{
					if (buf != NULL)
						(void) free(buf);
					bufsiz = data.size + old.size + 2;
					buf = xalloc(bufsiz);
				}
				sprintf(buf, "%s,%s", data.data, old.data);
				data.size = data.size + old.size + 1;
				data.data = buf;
				if (tTd(38, 9))
					printf("db_map_store append=%s\n", data.data);
			}
		}
E 83
		stat = db->put(db, &key, &data, 0);
	}
	if (stat != 0)
		syserr("readaliases: db put (%s)", lhs);
}
E 21

D 21
		  case 'f':
D 5
			map->map_flags |= MF_FOLDCASE;
E 5
I 5
			map->map_flags |= MF_NOFOLDCASE;
E 5
E 3
			break;
E 21

I 6
D 21
		  case 'm':
			map->map_flags |= MF_MATCHONLY;
			break;
E 21
I 21
/*
D 22
**  HASH_MAP_REBUILD -- rebuild hash database
*/
E 21

E 6
D 21
		  case 'a':
			map->map_app = ++p;
			break;
E 21
I 21
void
db_map_rebuild(map, fp, automatic, e)
	register MAP *map;
	FILE *fp;
	int automatic;
	ENVELOPE *e;
{
	register DB *db;
	char buf[MAXNAME];
E 21
I 6

D 21
		  case 'd':
			map->map_domain = ++p;
			break;
E 6
E 2
		}
D 12
		while (*p != '\0' && !isspace(*p))
E 12
I 12
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 12
			p++;
I 2
		if (*p != '\0')
D 14
			*p++ = 0;
E 14
I 14
			*p++ = '\0';
E 21
I 21
	if (tTd(27, 2))
		printf("hash_map_rebuild(%s)\n", map->map_file);

	(void) strcpy(buf, map->map_file);
	(void) strcat(buf, ".db");
	db = dbopen(buf, O_RDWR|O_CREAT|O_TRUNC, DBMMODE, DB_HASH, NULL);
	if (db == NULL)
	{
		syserr("hash_map_rebuild: cannot create %s", buf);
		return;
E 21
E 14
E 2
	}
I 2
D 21
	if (map->map_app != NULL)
		map->map_app = newstr(map->map_app);
I 6
	if (map->map_domain != NULL)
		map->map_domain = newstr(map->map_domain);
E 21
I 21
	map->map_db2 = db;
	map->map_flags |= MF_WRITABLE|MF_VALID;
}
E 21
E 6
E 2

D 14
	if (*p == '\0')
D 6
	{
		syserr("No file name for map %s", mapname);
E 6
		return NULL;
D 6
	}
E 6
	map->map_file = p;
D 12
	while (*p != '\0' && !isspace(*p))
E 12
I 12
	while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 12
		p++;
E 14
D 21
	if (*p != '\0')
E 21
I 21

/*
E 22
**  DB_MAP_CLOSE -- add distinguished entries and close the database
*/

void
db_map_close(map)
	MAP *map;
{
	register DB *db = map->map_db2;

D 29
	if (tTd(27, 9))
E 29
I 29
	if (tTd(38, 9))
E 29
D 22
		printf("db_map_close(%s, %x)\n", map->map_file, map->map_flags);
E 22
I 22
D 65
		printf("db_map_close(%s, %x)\n", map->map_file, map->map_mflags);
E 65
I 65
		printf("db_map_close(%s, %s, %x)\n",
			map->map_mname, map->map_file, map->map_mflags);
E 65
E 22

D 22
	if (bitset(MF_WRITABLE, map->map_flags))
E 22
I 22
	if (bitset(MF_WRITABLE, map->map_mflags))
E 22
E 21
D 14
		*p++ = '\0';
I 2
	map->map_file = newstr(map->map_file);
E 14
I 14
	{
D 21
		map->map_file = p;
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
			p++;
		if (*p != '\0')
			*p++ = '\0';
		map->map_file = newstr(map->map_file);
E 21
I 21
		/* write out the distinguished alias */
		db_map_store(map, "@", "@");
E 21
	}
I 15

D 21
	while (*p != '\0' && isascii(*p) && isspace(*p))
		p++;
E 15
E 14
E 2
	*pp = p;
I 15
	if (*p != '\0')
		map->map_rebuild = newstr(p);
E 21
I 21
	if (db->close(db) != 0)
		syserr("readaliases: db close failure");
E 21
E 15
}
I 6
D 21

# ifdef NIS_MAP
E 21

I 21
#endif
/*
**  NIS Modules
*/

# ifdef NIS

I 45
# ifndef YPERR_BUSY
#  define YPERR_BUSY	16
# endif

E 45
E 21
/*
D 21
**  NIS_MAP_INIT -- initialize DBM map
**
**	Parameters:
**		map -- the pointer to the actual map.
**		mapname -- the name of the map (for error messages).
**		args -- a pointer to the config file line arguments.
**
**	Returns:
**		TRUE -- if it could successfully open the map.
**		FALSE -- otherwise.
**
**	Side Effects:
**		Prints an error if it can't open the map.
E 21
I 21
**  NIS_MAP_OPEN -- open DBM map
E 21
*/

bool
D 21
nis_map_init(map, mapname, args)
E 21
I 21
nis_map_open(map, mode)
E 21
	MAP *map;
D 21
	char *mapname;
	char *args;
E 21
I 21
	int mode;
E 21
{
I 7
	int yperr;
I 23
	register char *p;
	auto char *vp;
	auto int vsize;
E 23
D 106
	char *master;
E 106

E 7
D 21
	/* parse arguments */
	map_parseargs(map, &args);
	if (map->map_file == NULL)
	{
		syserr("No NIS map name for map %s", mapname);
		return FALSE;
	}
E 21
I 21
D 29
	if (tTd(27, 2))
E 29
I 29
	if (tTd(38, 2))
E 29
D 65
		printf("nis_map_open(%s)\n", map->map_file);
E 65
I 65
		printf("nis_map_open(%s, %s)\n",
			map->map_mname, map->map_file);
E 65

I 22
	if (mode != O_RDONLY)
	{
D 49
		errno = ENODEV;
E 49
I 49
		/* issue a pseudo-error message */
#ifdef ENOSYS
		errno = ENOSYS;
#else
# ifdef EFTYPE
		errno = EFTYPE;
# else
		errno = ENXIO;
# endif
#endif
E 49
		return FALSE;
	}

E 22
E 21
D 23
	if (map->map_domain == NULL)
		yp_get_default_domain(&map->map_domain);
D 7
	return TRUE;
E 7
I 7

	/* check to see if this map actually exists */
	yperr = yp_master(map->map_domain, map->map_file, &master);
	if (yperr == 0)
		return TRUE;
D 22
	if (!bitset(MF_OPTIONAL, map->map_flags))
E 22
I 22
	if (!bitset(MF_OPTIONAL, map->map_mflags))
E 22
		syserr("Cannot bind to domain %s: %s", map->map_domain,
			yperr_string(yperr));
	return FALSE;
E 7
}
D 21
/*
E 21
I 21

bool
nis_map_open(map, mode)
	MAP *map;
	int mode;
{
	register char *p;
	int yperr;
	auto char *vp;
	auto int vsize;

E 23
	p = strchr(map->map_file, '@');
	if (p != NULL)
	{
		*p++ = '\0';
		if (*p != '\0')
			map->map_domain = p;
	}
I 23

E 23
D 57
	if (map->map_domain == NULL)
		yp_get_default_domain(&map->map_domain);

E 57
	if (*map->map_file == '\0')
		map->map_file = "mail.aliases";
I 57

	if (map->map_domain == NULL)
	{
		yperr = yp_get_default_domain(&map->map_domain);
		if (yperr != 0)
		{
D 58
			syserr("NIS map %s specified, but NIS not running\n",
				map->map_file);
E 58
I 58
			if (!bitset(MF_OPTIONAL, map->map_mflags))
D 74
				syserr("NIS map %s specified, but NIS not running\n",
E 74
I 74
				syserr("421 NIS map %s specified, but NIS not running\n",
E 74
					map->map_file);
E 58
			return FALSE;
		}
	}
E 57

I 23
	/* check to see if this map actually exists */
E 23
	yperr = yp_match(map->map_domain, map->map_file, "@", 1,
			&vp, &vsize);
D 29
	if (tTd(27, 10))
E 29
I 29
	if (tTd(38, 10))
E 29
		printf("nis_map_open: yp_match(%s, %s) => %s\n",
			map->map_domain, map->map_file, yperr_string(yperr));
	if (yperr == 0 || yperr == YPERR_KEY || yperr == YPERR_BUSY)
D 77
		return TRUE;
E 77
I 77
	{
		if (!bitset(MF_ALIAS, map->map_mflags) ||
		    aliaswait(map, NULL, TRUE))
			return TRUE;
	}
E 77
I 23

	if (!bitset(MF_OPTIONAL, map->map_mflags))
D 74
		syserr("Cannot bind to domain %s: %s", map->map_domain,
E 74
I 74
D 89
		syserr("421 Cannot bind to domain %s: %s", map->map_domain,
E 74
			yperr_string(yperr));
E 89
I 89
	{
		syserr("421 Cannot bind to map %s in domain %s: %s",
			map->map_file, map->map_domain, yperr_string(yperr));
	}
E 89

E 23
	return FALSE;
}


/*
E 21
**  NIS_MAP_LOOKUP -- look up a datum in a NIS map
D 21
**
**	Parameters:
**		map -- the map to look up in.
**		buf -- a pointer to to the buffer containing the key.
**			This is a null terminated string.
**		bufsiz -- the size of buf -- note that this is in general
**			larger that strlen(buf), and buf can be changed
**			in place if desired.
**		av -- arguments from the config file (can be interpolated
**			into the final result).
I 16
**		statp -- pointer to status word (out-parameter).
E 16
**
**	Returns:
**		A pointer to the rewritten result.
**		NULL if not found in the map.
E 21
*/

char *
D 16
nis_map_lookup(map, buf, bufsiz, av)
E 16
I 16
D 21
nis_map_lookup(map, buf, bufsiz, av, statp)
E 21
I 21
nis_map_lookup(map, name, av, statp)
E 21
E 16
	MAP *map;
D 21
	char buf[];
	int bufsiz;
E 21
I 21
	char *name;
E 21
	char **av;
I 16
	int *statp;
E 16
{
	char *vp;
D 9
	int *vsize;
E 9
I 9
	auto int vsize;
I 17
	int buflen;
I 23
	int yperr;
E 23
I 21
	char keybuf[MAXNAME + 1];
E 21
E 17
E 9

D 21
	if (!bitset(MF_NOFOLDCASE, map->map_flags))
	{
		register char *p;
E 21
I 21
D 29
	if (tTd(27, 20))
E 29
I 29
	if (tTd(38, 20))
E 29
D 65
		printf("nis_map_lookup(%s)\n", name);
E 65
I 65
		printf("nis_map_lookup(%s, %s)\n",
			map->map_mname, name);
E 65
E 21

D 21
		for (p = buf; *p != '\0'; p++)
D 12
			if (isupper(*p))
E 12
I 12
			if (isascii(*p) && isupper(*p))
E 12
				*p = tolower(*p);
	}
D 9
	if (yp_match(map->map_domain, map->map_file, buf, bufsiz, &vp, &vsize) != 0)
E 9
I 9
D 17
	if (yp_match(map->map_domain, map->map_file, buf, strlen(buf) + 1,
E 17
I 17
	buflen = strlen(buf);
E 21
I 21
	buflen = strlen(name);
	if (buflen > sizeof keybuf - 1)
		buflen = sizeof keybuf - 1;
	bcopy(name, keybuf, buflen + 1);
D 22
	if (!bitset(MF_NOFOLDCASE, map->map_flags))
E 22
I 22
	if (!bitset(MF_NOFOLDCASE, map->map_mflags))
E 22
		makelower(keybuf);
E 21
D 22
	if (bitset(MF_INCLNULL, map->map_flags))
E 22
I 22
D 37
	if (bitset(MF_INCLNULL, map->map_mflags))
E 37
I 37
	yperr = YPERR_KEY;
	if (bitset(MF_TRY0NULL, map->map_mflags))
	{
		yperr = yp_match(map->map_domain, map->map_file, keybuf, buflen,
			     &vp, &vsize);
		if (yperr == 0)
			map->map_mflags &= ~MF_TRY1NULL;
	}
	if (yperr == YPERR_KEY && bitset(MF_TRY1NULL, map->map_mflags))
	{
E 37
E 22
		buflen++;
D 21
	if (yp_match(map->map_domain, map->map_file, buf, buflen,
E 17
		     &vp, &vsize) != 0)
E 21
I 21
D 37
	yperr = yp_match(map->map_domain, map->map_file, keybuf, buflen,
		     &vp, &vsize);
E 37
I 37
		yperr = yp_match(map->map_domain, map->map_file, keybuf, buflen,
			     &vp, &vsize);
		if (yperr == 0)
			map->map_mflags &= ~MF_TRY0NULL;
	}
E 37
	if (yperr != 0)
	{
		if (yperr != YPERR_KEY && yperr != YPERR_BUSY)
D 22
			map->map_flags &= ~MF_VALID;
E 22
I 22
D 23
			map->map_mflags &= ~MF_VALID;
E 23
I 23
			map->map_mflags &= ~(MF_VALID|MF_OPEN);
E 23
E 22
E 21
E 9
		return NULL;
D 21
	if (!bitset(MF_MATCHONLY, map->map_flags))
		map_rewrite(vp, vsize, buf, bufsiz, av);
	return buf;
E 21
I 21
	}
D 22
	if (bitset(MF_MATCHONLY, map->map_flags))
E 22
I 22
	if (bitset(MF_MATCHONLY, map->map_mflags))
E 22
D 37
		av = NULL;
D 23
	return map_rewrite(map, val.dptr, val.dsize, av);
E 23
I 23
	return map_rewrite(map, vp, vsize, av);
E 37
I 37
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, vp, vsize, av);
E 37
E 23
E 21
}

I 95

/*
**  NIS_GETCANONNAME -- look up canonical name in NIS
*/

bool
nis_getcanonname(name, hbsize, statp)
	char *name;
	int hbsize;
	int *statp;
{
	char *vp;
	auto int vsize;
	int keylen;
	int yperr;
	static bool try0null = TRUE;
	static bool try1null = TRUE;
	static char *yp_domain = NULL;
D 106
	char *domain, *p;
E 106
I 106
	char *domain;
E 106
D 108
	char host_record[MAXLINE];
	char buf[MAXNAME];
E 108
D 111
	char *cname;
E 111
I 108
	char host_record[MAXLINE];
D 111
	char fbuf[MAXNAME];
E 111
I 111
	char cbuf[MAXNAME];
E 111
	char nbuf[MAXNAME + 1];
E 108
	extern char *get_column();

	if (tTd(38, 20))
		printf("nis_getcanonname(%s)\n", name);

D 108
	shorten_hostname(name);
E 108
I 108
	if (strlen(name) >= sizeof nbuf)
	{
		*statp = EX_UNAVAILABLE;
		return FALSE;
	}
	(void) strcpy(nbuf, name);
	shorten_hostname(nbuf);
E 108

	/* we only accept single token search key */
D 108
	if (strchr(name, '.'))
E 108
I 108
	if (strchr(nbuf, '.'))
E 108
	{
		*statp = EX_NOHOST;
		return FALSE;
	}

D 108
	keylen = strlen(name);
E 108
I 108
	keylen = strlen(nbuf);
E 108

	if (yp_domain == NULL)
		yp_get_default_domain(&yp_domain);
D 108
	makelower(name);
E 108
I 108
	makelower(nbuf);
E 108
	yperr = YPERR_KEY;
	if (try0null)
	{
D 108
		yperr = yp_match(yp_domain, "hosts.byname", name, keylen,
E 108
I 108
		yperr = yp_match(yp_domain, "hosts.byname", nbuf, keylen,
E 108
			     &vp, &vsize);
		if (yperr == 0)
			try1null = FALSE;
	}
	if (yperr == YPERR_KEY && try1null)
	{
		keylen++;
D 108
		yperr = yp_match(yp_domain, "hosts.byname", name, keylen,
E 108
I 108
		yperr = yp_match(yp_domain, "hosts.byname", nbuf, keylen,
E 108
			     &vp, &vsize);
		if (yperr == 0)
			try0null = FALSE;
	}
	if (yperr != 0)
	{
		if (yperr == YPERR_KEY)
			*statp = EX_NOHOST;
		else if (yperr == YPERR_BUSY)
			*statp = EX_TEMPFAIL;
		else
			*statp = EX_UNAVAILABLE;
		return FALSE;
	}
	strncpy(host_record, vp, vsize);
	host_record[vsize] = '\0';
D 103
	cname = get_column(host_record, 1, '\t', buf);
E 103
I 103
	if (tTd(38, 44))
		printf("got record `%s'\n", host_record);
D 108
	cname = get_column(host_record, 1, '\0', buf);
E 108
I 108
D 111
	cname = get_column(host_record, 1, '\0', fbuf);
E 108
E 103
	if (cname == NULL)
E 111
I 111
	if (!extract_canonname(nbuf, host_record, cbuf))
E 111
	{
		/* this should not happen, but.... */
		*statp = EX_NOHOST;
		return FALSE;
	}
D 111

D 105
	if (hbsize >= strlen(cname))
E 105
I 105
	if (strchr(cname, '.') != NULL)
E 111
I 111
	if (hbsize < strlen(cbuf))
E 111
E 105
	{
D 105
		strcpy(name, cname);
E 105
I 105
D 111
		domain = "";
E 111
I 111
		*statp = EX_UNAVAILABLE;
		return FALSE;
E 111
	}
D 111
	else
	{
		domain = macvalue('m', CurEnv);
		if (domain == NULL)
			domain = "";
	}
	if (hbsize >= strlen(cname) + strlen(domain) + 1)
	{
		if (domain[0] == '\0')
			strcpy(name, vp);
		else
			sprintf(name, "%s.%s", vp, domain);
E 105
		*statp = EX_OK;
		return TRUE;
	}
	*statp = EX_UNAVAILABLE;
	return FALSE;
E 111
I 111
	strcpy(name, cbuf);
	*statp = EX_OK;
	return TRUE;
E 111
}

E 95
D 21
#endif /* NIS_MAP */
E 21
I 21
D 65

/*
D 22
**  NIS_ASTORE
E 22
I 22
**  NIS_MAP_STORE
E 22
*/

void
nis_map_store(map, lhs, rhs)
	MAP *map;
	char *lhs;
	char *rhs;
{
	/* nothing */
}

D 22
/*
**  NIS_AREBUILD
*/
E 22

D 22
void
nis_map_rebuild(map, fp, automatic, e)
	MAP *map;
	FILE *fp;
	int automatic;
	ENVELOPE *e;
{
	if (tTd(27, 2))
		printf("nis_map_rebuild(%s)\n", map->map_file);
}


E 22
/*
D 22
**  NIS_ACLOSE
E 22
I 22
**  NIS_MAP_CLOSE
E 22
*/

void
nis_map_close(map)
	MAP *map;
{
	/* nothing */
}

#endif /* NIS */
E 65
I 65
#endif
E 65
E 21
E 6
/*
I 68
**  NISPLUS Modules
**
**	This code donated by Sun Microsystems.
*/

#ifdef NISPLUS

#undef NIS /* symbol conflict in nis.h */
#include <rpcsvc/nis.h>
#include <rpcsvc/nislib.h>

#define EN_col(col)	zo_data.objdata_u.en_data.en_cols.en_cols_val[(col)].ec_value.ec_value_val
#define COL_NAME(res,i)	((res->objects.objects_val)->TA_data.ta_cols.ta_cols_val)[i].tc_name
#define COL_MAX(res)	((res->objects.objects_val)->TA_data.ta_cols.ta_cols_len)
#define PARTIAL_NAME(x)	((x)[strlen(x) - 1] != '.')

/*
**  NISPLUS_MAP_OPEN -- open nisplus table
*/

bool
nisplus_map_open(map, mode)
	MAP *map;
	int mode;
{
	register char *p;
	char qbuf[MAXLINE + NIS_MAXNAMELEN];
	nis_result *res = NULL;
	u_int objs_len;
	nis_object *obj_ptr;
	int retry_cnt, max_col, i;

	if (tTd(38, 2))
		printf("nisplus_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);

	if (mode != O_RDONLY)
	{
		errno = ENODEV;
		return FALSE;
	}

	if (*map->map_file == '\0')
		map->map_file = "mail_aliases.org_dir";

	if (PARTIAL_NAME(map->map_file) && map->map_domain == NULL)
	{
		/* set default NISPLUS Domain to $m */
		extern char *nisplus_default_domain();

		map->map_domain = newstr(nisplus_default_domain());
		if (tTd(38, 2))
			printf("nisplus_map_open(%s): using domain %s\n",
				 map->map_file, map->map_domain);
	}
	if (!PARTIAL_NAME(map->map_file))
		map->map_domain = newstr("");

	/* check to see if this map actually exists */
	if (PARTIAL_NAME(map->map_file))
		sprintf(qbuf, "%s.%s", map->map_file, map->map_domain);
	else
		strcpy(qbuf, map->map_file);
	
	retry_cnt = 0;
	while (res == NULL || res->status != NIS_SUCCESS)
	{
		res = nis_lookup(qbuf, FOLLOW_LINKS);
		switch (res->status)
		{
		  case NIS_SUCCESS:
		  case NIS_TRYAGAIN:
		  case NIS_RPCERROR:
		  case NIS_NAMEUNREACHABLE:
			break;

		  default:		/* all other nisplus errors */
#if 0
			if (!bitset(MF_OPTIONAL, map->map_mflags))
D 74
				syserr("Cannot find table %s.%s: %s",
E 74
I 74
				syserr("421 Cannot find table %s.%s: %s",
E 74
					map->map_file, map->map_domain,
					nis_sperrno(res->status));
#endif
			errno = EBADR;
			return FALSE;
		}
		sleep(2);		/* try not to overwhelm hosed server */
		if (retry_cnt++ > 4)
		{
			errno = EBADR;
			return FALSE;
		}
	}

	if (NIS_RES_NUMOBJ(res) != 1 ||
	    (NIS_RES_OBJECT(res)->zo_data.zo_type != TABLE_OBJ))
	{
		if (tTd(38, 10))
			printf("nisplus_map_open: %s is not a table\n", qbuf);
#if 0
		if (!bitset(MF_OPTIONAL, map->map_mflags))
D 74
			syserr("%s.%s: %s is not a table",
E 74
I 74
			syserr("421 %s.%s: %s is not a table",
E 74
				map->map_file, map->map_domain,
				nis_sperrno(res->status));
#endif
		errno = EBADR;
		return FALSE;
	}
	/* default key column is column 0 */
	if (map->map_keycolnm == NULL)
		map->map_keycolnm = newstr(COL_NAME(res,0));

	max_col = COL_MAX(res);
	
	/* verify the key column exist */
	for (i=0; i< max_col; i++)
	{
		if (!strcmp(map->map_keycolnm, COL_NAME(res,i)))
			break;
	}
	if (i == max_col)
	{
		if (tTd(38, 2))
			printf("nisplus_map_open(%s): can not find key column %s\n",
				map->map_file, map->map_keycolnm);
		errno = EBADR;
		return FALSE;
	}

	/* default value column is the last column */
	if (map->map_valcolnm == NULL)
	{
		map->map_valcolno = max_col - 1;
		return TRUE;
	}

	for (i=0; i< max_col; i++)
	{
		if (strcmp(map->map_valcolnm, COL_NAME(res,i)) == 0)
		{
			map->map_valcolno = i;
			return TRUE;
		}
	}

	if (tTd(38, 2))
		printf("nisplus_map_open(%s): can not find column %s\n",
			 map->map_file, map->map_keycolnm);
	errno = EBADR;
	return FALSE;
}


/*
**  NISPLUS_MAP_LOOKUP -- look up a datum in a NISPLUS table
*/

char *
nisplus_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
	char *vp;
	auto int vsize;
	int buflen;
	char search_key[MAXNAME + 1];
	char qbuf[MAXLINE + NIS_MAXNAMELEN];
	nis_result *result;

	if (tTd(38, 20))
		printf("nisplus_map_lookup(%s, %s)\n",
			map->map_mname, name);

	if (!bitset(MF_OPEN, map->map_mflags))
	{
		if (nisplus_map_open(map, O_RDONLY))
			map->map_mflags |= MF_OPEN;
		else
		{
			*statp = EX_UNAVAILABLE;
			return NULL;
		}
	}
		
	buflen = strlen(name);
	if (buflen > sizeof search_key - 1)
		buflen = sizeof search_key - 1;
	bcopy(name, search_key, buflen + 1);
	if (!bitset(MF_NOFOLDCASE, map->map_mflags))
		makelower(search_key);

	/* construct the query */
	if (PARTIAL_NAME(map->map_file))
		sprintf(qbuf, "[%s=%s],%s.%s", map->map_keycolnm,
			search_key, map->map_file, map->map_domain);
	else
		sprintf(qbuf, "[%s=%s],%s", map->map_keycolnm,
			search_key, map->map_file);

	if (tTd(38, 20))
		printf("qbuf=%s\n", qbuf);
	result = nis_list(qbuf, FOLLOW_LINKS | FOLLOW_PATH, NULL, NULL);
	if (result->status == NIS_SUCCESS)
	{
		int count;
		char *str;

		if ((count = NIS_RES_NUMOBJ(result)) != 1)
		{
			if (LogLevel > 10)
				syslog(LOG_WARNING,
				  "%s:Lookup error, expected 1 entry, got (%d)",
				    map->map_file, count);

			/* ignore second entry */
			if (tTd(38, 20))
				printf("nisplus_map_lookup(%s), got %d entries, additional entries ignored\n",
					name, count);
		}

		vp = ((NIS_RES_OBJECT(result))->EN_col(map->map_valcolno));
		/* set the length of the result */
		if (vp == NULL)
			vp = "";
		vsize = strlen(vp);
		if (tTd(38, 20))
			printf("nisplus_map_lookup(%s), found %s\n",
				name, vp);
		if (bitset(MF_MATCHONLY, map->map_mflags))
			str = map_rewrite(map, name, strlen(name), NULL);
		else
			str = map_rewrite(map, vp, vsize, av);
		nis_freeresult(result);
#ifdef MAP_EXIT_STAT
		*statp = EX_OK;
#endif
		return str;
	}
	else
	{
#ifdef MAP_EXIT_STAT
		if (result->status == NIS_NOTFOUND)
			*statp = EX_NOTFOUND;
		else if (result->status == NIS_TRYAGAIN)
			*statp = EX_TEMPFAIL;
		else
		{
			*statp = EX_UNAVAILABLE;
			map->map_mflags &= ~(MF_VALID|MF_OPEN);
		}
#else
		if ((result->status != NIS_NOTFOUND) &&
		    (result->status != NIS_TRYAGAIN))
			map->map_mflags &= ~(MF_VALID|MF_OPEN);
#endif
	}
	if (tTd(38, 20))
		printf("nisplus_map_lookup(%s), failed\n", name);
	nis_freeresult(result);
	return NULL;
}


I 95

/*
**  NISPLUS_GETCANONNAME -- look up canonical name in NIS+
*/

bool
nisplus_getcanonname(name, hbsize, statp)
	char *name;
	int hbsize;
	int *statp;
{
	char *vp;
	auto int vsize;
	int buflen;
D 97
	char buf1[MAXLINE + NIS_MAXNAMELEN];
	static char *nis_path = NULL;
	static char nis_path_buf[MAXLINE];
E 97
I 97
D 108
	char buf[MAXLINE + NIS_MAXNAMELEN];
E 108
E 97
	nis_result *result;
	char *p;
	int len;
I 108
	char nbuf[MAXNAME + 1];
	char qbuf[MAXLINE + NIS_MAXNAMELEN];
E 108

D 97
	if (nis_path == NULL)
	{
		char *ptr;
		char pathbuf[MAXLINE];

		strcpy(buf1, macvalue('m', CurEnv));
		strcat(buf1, ".");
		/* try the host tabe in $m */
		if (hosts_table_ok(buf1))
			strcpy(pathbuf, buf1);
		else
			strcpy(pathbuf, "$");

		nis_path = nis_path_buf;
		sprintf(nis_path, "NIS_PATH=%s", pathbuf);
	}

	if (nis_path[0] != '\0')
		putenv(nis_path);
	else
		syslog(LOG_WARNING, "no NIS+ path defined");

E 97
D 108
	shorten_hostname(name);
E 108
I 108
	if (strlen(name) >= sizeof nbuf)
	{
		*statp = EX_UNAVAILABLE;
		return FALSE;
	}
	(void) strcpy(nbuf, name);
	shorten_hostname(nbuf);
E 108

D 108
	p = strchr(name, '.');
E 108
I 108
	p = strchr(nbuf, '.');
E 108
	if (p == NULL)
	{
		/* single token */
D 97
		sprintf(buf1, "[name=%s],hosts.org_dir", name);
E 97
I 97
D 108
		sprintf(buf, "[name=%s],hosts.org_dir", name);
E 108
I 108
		sprintf(qbuf, "[name=%s],hosts.org_dir", nbuf);
E 108
E 97
	}
	else if (p[1] != '\0')
	{
D 108
		/* multi token -- take only first token in name buf */
E 108
I 108
		/* multi token -- take only first token in nbuf */
E 108
		*p = '\0';
D 97
		sprintf(buf1, "[name=%s],hosts.org_dir.%s", name, &p[1]);
E 97
I 97
D 108
		sprintf(buf, "[name=%s],hosts.org_dir.%s", name, &p[1]);
E 108
I 108
		sprintf(qbuf, "[name=%s],hosts.org_dir.%s", nbuf, &p[1]);
E 108
E 97
	}
	else
	{
		*statp = EX_NOHOST;
		return FALSE;
	}

	if (tTd(38, 20))
D 98
		printf("\nnisplus_getcanoname(%s), qbuf=%s\n%s\n",
D 97
			 name, buf1, nis_path);
E 97
I 97
			 name, buf, nis_path);
E 98
I 98
		printf("\nnisplus_getcanoname(%s), qbuf=%s\n",
D 108
			 name, buf);
E 108
I 108
			 name, qbuf);
E 108
E 98
E 97

D 97
	result = nis_list(buf1, EXPAND_NAME|FOLLOW_LINKS|FOLLOW_PATH,
E 97
I 97
D 108
	result = nis_list(buf, EXPAND_NAME|FOLLOW_LINKS|FOLLOW_PATH,
E 108
I 108
	result = nis_list(qbuf, EXPAND_NAME|FOLLOW_LINKS|FOLLOW_PATH,
E 108
E 97
		NULL, NULL);
D 97

	/* unset NIS_PATH, just in case */
	unsetenv("NIS_PATH");
E 97

	if (result->status == NIS_SUCCESS)
	{
		int count;
		char *str;
		char *domain;

		if ((count = NIS_RES_NUMOBJ(result)) != 1)
		{
#ifdef LOG
			if (LogLevel > 10)
				syslog(LOG_WARNING,
				       "nisplus_getcanonname: Lookup error, expected 1 entry, got (%d)",
				       count);
#endif

			/* ignore second entry */
			if (tTd(38, 20))
				printf("nisplus_getcanoname(%s), got %d entries, addtional entries ignores\n", name);
		}

		if (tTd(38, 20))
			printf("nisplus_getcanoname(%s), found in directory \"%s\"\n",
			       name, (NIS_RES_OBJECT(result))->zo_domain);


		vp = ((NIS_RES_OBJECT(result))->EN_col(0));
		vsize = strlen(vp);
		if (tTd(38, 20))
			printf("nisplus_getcanonname(%s), found %s\n",
				name, vp);
D 105
		domain = macvalue('m', CurEnv);
D 101
		if (hbsize > (vsize + ((int) strlen(domain))))
E 101
I 101
		if (domain == NULL)
E 105
I 105
		if (strchr(vp, '.') != NULL)
		{
E 105
			domain = "";
I 105
		}
		else
		{
			domain = macvalue('m', CurEnv);
			if (domain == NULL)
				domain = "";
		}
E 105
		if (hbsize > vsize + (int) strlen(domain) + 1)
E 101
		{
D 101
			sprintf(name, "%s.%s", vp, domain);
E 101
I 101
			if (domain[0] == '\0')
				strcpy(name, vp);
			else
				sprintf(name, "%s.%s", vp, domain);
E 101
			*statp = EX_OK;
		}
		else
			*statp = EX_NOHOST;
		nis_freeresult(result);
		return TRUE;
	}
	else
	{
		if (result->status == NIS_NOTFOUND)
			*statp = EX_NOHOST;
		else if (result->status == NIS_TRYAGAIN)
			*statp = EX_TEMPFAIL;
		else
D 101
		{
E 101
			*statp = EX_UNAVAILABLE;
D 101
		}
E 101
	}
	if (tTd(38, 20))
		printf("nisplus_getcanonname(%s), failed, status=%d, nsw_stat=%d\n",
			name, result->status, *statp);
	nis_freeresult(result);
	return FALSE;
}


E 95
char *
nisplus_default_domain()
{
D 87
	static char default_domain[MAXNAME] = "";
E 87
I 87
	static char default_domain[MAXNAME + 1] = "";
E 87
D 82
	nis_result *res = NULL;
E 82
	char *p;

	if (default_domain[0] != '\0')
		return(default_domain);
	
D 82
	if (VendorCode == VENDOR_SUN && ConfigLevel < 2)
	{
		/* for old config, user nis+ local directory        */
		/* have to be backward compatible with bugs too :-( */
		p = nis_local_directory();
		strcpy(default_domain, p);
		return default_domain;
	}

	if ((p = macvalue('m', CurEnv)) == NULL)
	{
		p = nis_local_directory();
		strcpy(default_domain, p);
		return default_domain;
	}

E 82
I 82
	p = nis_local_directory();
E 82
	strcpy(default_domain, p);
D 82
	if (PARTIAL_NAME(default_domain))
		strcat(default_domain, ".");

	res = nis_lookup(default_domain, FOLLOW_LINKS);
	if (res->status == NIS_NOTFOUND)
	{
		p = nis_local_directory();
		strcpy(default_domain, p);
	}
	return(default_domain);
E 82
I 82
	return default_domain;
E 82
}

#endif /* NISPLUS */
/*
E 68
I 66
**  HESIOD Modules
D 80
**
**	Only works for aliases (for now).
E 80
*/

#ifdef HESIOD

I 79
#include <hesiod.h>

E 79
char *
hes_map_lookup(map, name, av, statp)
        MAP *map;
        char *name;
        char **av;
        int *statp;
{
D 79
	struct hes_postoffice *pobox;
	char keybuf[MAXNAME + 1];
E 79
I 79
	char **hp;
D 100
	char *retdata = NULL;
E 100
D 107
	int i;
E 107
E 79

	if (tTd(38, 20))
D 79
		printf("hes_map_lookup(%s)\n", name);
E 79
I 79
		printf("hes_map_lookup(%s, %s)\n", map->map_file, name);
E 79

D 79
	pobox = hes_getmailhost(name);
	if (pobox == NULL)
E 79
I 79
D 104
	hp = hes_resolve(name, map->map_file);
E 104
I 104
	if (name[0] == '\\')
	{
		char *np;
		int nl;
		char nbuf[MAXNAME];

		nl = strlen(name);
		if (nl < sizeof nbuf - 1)
			np = nbuf;
		else
			np = xalloc(strlen(name) + 2);
		np[0] = '\\';
		strcpy(&np[1], name);
		hp = hes_resolve(np, map->map_file);
		if (np != nbuf)
			free(np);
	}
	else
	{
		hp = hes_resolve(name, map->map_file);
	}
E 104
D 100
	if (hp == NULL)
E 100
I 100
	if (hp == NULL || hp[0] == NULL)
E 100
E 79
		return NULL;
D 79

	/* We only know how to deal with the SMTP types right now */
	if (strcmp(pobox->po_type, "SMTP") != 0 &&
	    strcmp(pobox->po_type, "ESMTP") != 0)
		return NULL;

	/* if just checking for a match, we are done */
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, name, strlen(name), NULL);

	/* Do the rewriting with new values */
	if (strlen(pobox->po_name) + strlen(pobox->po_host) + 1 > sizeof keybuf)
E 79
I 79
	
D 100
	if (hp[0] != NULL)
E 79
I 68
	{
D 79
		*statp = EX_DATAERR;
E 68
		return NULL;
E 79
I 79
D 90
		if (tTd(38, 20))
D 80
			printf("  %d %s\n", i, p);
E 80
I 80
			printf("  %d %s\n", i, hp[0]);
E 90
E 80
		if (bitset(MF_MATCHONLY, map->map_mflags))
			retdata = map_rewrite(map, name, strlen(name), NULL);
		else
			retdata = map_rewrite(map, hp[0], strlen(hp[0]), av);
E 79
I 68
	}
E 68
D 79
	(void) sprintf(keybuf, "%s@%s", pobox->po_name, pobox->po_host);
	return map_rewrite(map, keybuf, strlen(keybuf), av);
E 79
I 79

	for (i = 0; hp[i] != NULL; i++)
		free(hp[i]);
	free(hp);
	return retdata;
E 100
I 100
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, hp[0], strlen(hp[0]), av);
E 100
E 79
}

#endif
/*
I 67
**  NeXT NETINFO Modules
*/

D 114
#ifdef NETINFO
E 114
I 114
#if NETINFO
E 114

#define NETINFO_DEFAULT_DIR		"/aliases"
#define NETINFO_DEFAULT_PROPERTY	"members"


/*
**  NI_MAP_OPEN -- open NetInfo Aliases
*/

D 68
bool 
E 68
I 68
bool
E 68
ni_map_open(map, mode)
	MAP *map;
	int mode;
{
	char *p;

	if (tTd(38, 20))
		printf("ni_map_open: %s\n", map->map_file);

D 75
	p = strchr(map->map_file, '@');
	if (p != NULL)
	{
		*p++ = '\0';
		if (*p != '\0')
			map->map_domain = p;
	}
E 75
	if (*map->map_file == '\0')
		map->map_file = NETINFO_DEFAULT_DIR;

D 75
	if (map->map_domain == NULL)
		map->map_domain = NETINFO_DEFAULT_PROPERTY;
E 75
I 75
	if (map->map_valcolnm == NULL)
		map->map_valcolnm = NETINFO_DEFAULT_PROPERTY;
E 75

D 70
	if (map->map_sepchar == '\0' && bitset(MF_ALIAS, map->map_mflags))
		map->map_sepchar = ',';
E 70
I 70
	if (map->map_coldelim == '\0' && bitset(MF_ALIAS, map->map_mflags))
		map->map_coldelim = ',';
E 70

	return TRUE;
}


/*
**  NI_MAP_LOOKUP -- look up a datum in NetInfo
*/

char *
ni_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
	char *res;
	char *propval;
	extern char *ni_propval();

	if (tTd(38, 20))
D 68
		printf("ni_map_lookup(%s, %s)\n", 
E 68
I 68
		printf("ni_map_lookup(%s, %s)\n",
E 68
			map->map_mname, name);

	propval = ni_propval(map->map_file, map->map_keycolnm, name,
			     map->map_valcolnm, map->map_coldelim);

D 68
	if (propval == NULL) 
E 68
I 68
	if (propval == NULL)
E 68
		return NULL;

	if (bitset(MF_MATCHONLY, map->map_mflags))
		res = map_rewrite(map, name, strlen(name), NULL);
	else
		res = map_rewrite(map, propval, strlen(propval), av);
	free(propval);
	return res;
}

#endif
/*
I 68
**  TEXT (unindexed text file) Modules
**
**	This code donated by Sun Microsystems.
*/


/*
**  TEXT_MAP_OPEN -- open text table
*/

bool
text_map_open(map, mode)
	MAP *map;
	int mode;
{
	struct stat sbuf;

	if (tTd(38, 2))
		printf("text_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);

	if (mode != O_RDONLY)
	{
		errno = ENODEV;
		return FALSE;
	}

	if (*map->map_file == '\0')
	{
		if (tTd(38, 2))
			printf("text_map_open: file name required\n");
		return FALSE;
	}

	if (map->map_file[0] != '/')
	{
		if (tTd(38, 2))
			printf("text_map_open(%s): file name must be fully qualified\n",
				map->map_file);
		return FALSE;
	}
	/* check to see if this map actually accessable */
	if (access(map->map_file, R_OK) <0)
		return FALSE;

	/* check to see if this map actually exist */
	if (stat(map->map_file, &sbuf) <0)
	{
		if (tTd(38, 2))
			printf("text_map_open(%s): can not stat %s\n",
				map->map_file, map->map_file);
		return FALSE;
	}

	if (!S_ISREG(sbuf.st_mode))
	{
		if (tTd(38, 2))
			printf("text_map_open(%s): %s is not a file\n",
				map->map_file, map->map_file);
		return FALSE;
	}

	if (map->map_keycolnm == NULL)
		map->map_keycolno = 0;
	else
	{
		if (!isdigit(*map->map_keycolnm))
		{
			if (tTd(38, 2))
				printf("text_map_open(%s): -k should specify a number, not %s\n",
					map->map_file, map->map_keycolnm);
			return FALSE;
		}
		map->map_keycolno = atoi(map->map_keycolnm);
	}

	if (map->map_valcolnm == NULL)
		map->map_valcolno = 0;
	else
	{
		if (!isdigit(*map->map_valcolnm))
		{
			if (tTd(38, 2))
				printf("text_map_open(%s): -v should specify a number, not %s\n",
					map->map_file, map->map_valcolnm);
			return FALSE;
		}
		map->map_valcolno = atoi(map->map_valcolnm);
	}

D 85
	if (map->map_coldelim == '\0')
		map->map_coldelim = ':';

E 85
	if (tTd(38, 2))
	{
D 85
		printf("text_map_open(%s): delimiter = %c\n",
			map->map_file, map->map_coldelim);
E 85
I 85
		printf("text_map_open(%s): delimiter = ",
			map->map_file);
		if (map->map_coldelim == '\0')
			printf("(white space)\n");
		else
			printf("%c\n", map->map_coldelim);
E 85
	}

	return TRUE;
}


/*
**  TEXT_MAP_LOOKUP -- look up a datum in a TEXT table
*/

char *
text_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
	char *vp;
	auto int vsize;
	int buflen;
	char search_key[MAXNAME + 1];
	char linebuf[MAXLINE];
	FILE *f;
D 87
	char buf[MAXNAME+1];
E 87
I 87
	char buf[MAXNAME + 1];
E 87
	char delim;
	int key_idx;
	bool found_it;
	extern char *get_column();


	found_it = FALSE;
	if (tTd(38, 20))
		printf("text_map_lookup(%s)\n", name);

	buflen = strlen(name);
	if (buflen > sizeof search_key - 1)
		buflen = sizeof search_key - 1;
	bcopy(name, search_key, buflen + 1);
	if (!bitset(MF_NOFOLDCASE, map->map_mflags))
		makelower(search_key);

	f = fopen(map->map_file, "r");
	if (f == NULL)
	{
		map->map_mflags &= ~(MF_VALID|MF_OPEN);
		*statp = EX_UNAVAILABLE;
		return NULL;
	}
	key_idx = map->map_keycolno;
	delim = map->map_coldelim;
	while (fgets(linebuf, MAXLINE, f))
	{
		char *lf;
		if (linebuf[0] == '#')
			continue; /* skip comment line */
		if (lf = strchr(linebuf, '\n'))
			*lf = '\0';
		if (!strcasecmp(search_key,
				get_column(linebuf, key_idx, delim, buf)))
		{
			found_it = TRUE;
			break;
		}
	}
	fclose(f);
	if (!found_it)
	{
#ifdef MAP_EXIT_STAT
		*statp = EX_NOTFOUND;
#endif
		return(NULL);
	}
	vp = get_column(linebuf, map->map_valcolno, delim, buf);
	vsize = strlen(vp);
#ifdef MAP_EXIT_STAT
	*statp = EX_OK;
#endif
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, vp, vsize, av);
}
I 95


/*
**  TEXT_GETCANONNAME -- look up canonical name in hosts file
*/

bool
text_getcanonname(name, hbsize, statp)
	char *name;
	int hbsize;
	int *statp;
{
D 106
	int buflen;
E 106
D 103
	char delim;
E 103
	int key_idx;
D 111
	char *cname;
E 111
	bool found;
D 106
	char *domain;
E 106
	FILE *f;
	char linebuf[MAXLINE];
	char cbuf[MAXNAME + 1];
D 108
	char buf[MAXNAME + 1];
E 108
I 108
	char fbuf[MAXNAME + 1];
	char nbuf[MAXNAME + 1];
E 108
	extern char *get_column();

D 108
	shorten_hostname(name);
E 108
I 108
	if (strlen(name) >= sizeof nbuf)
	{
		*statp = EX_UNAVAILABLE;
		return FALSE;
	}
	(void) strcpy(nbuf, name);
	shorten_hostname(nbuf);
E 108

	/* we only accept single token search key */
D 108
	if (strchr(name, '.') != NULL)
E 108
I 108
	if (strchr(nbuf, '.') != NULL)
E 108
	{
		*statp = EX_NOHOST;
		return FALSE;
	}

	found = FALSE;

	f = fopen(HostsFile, "r");
	if (f == NULL)
	{
#ifdef MAP_EXIT_STAT
		*statp = EX_UNAVAILABLE;
#endif
		return FALSE;
	}
D 103
	delim = '\t';
E 103
	while (!found && fgets(linebuf, MAXLINE, f) != NULL)
	{
		char *p;

		if (linebuf[0] == '#')
			continue;
		if ((p = strchr(linebuf, '\n')) != NULL)
			*p = '\0';
D 103
		cname = get_column(linebuf, 1, delim, cbuf);
E 103
I 103
D 111
		cname = get_column(linebuf, 1, '\0', cbuf);
E 103
D 108
		if (cname != NULL && strcasecmp(name,  cname) == 0)
E 108
I 108
		if (cname != NULL && strcasecmp(nbuf,  cname) == 0)
E 108
		{
			found = TRUE;
			break;
		}

		key_idx = 2;
D 103
		while ((p = get_column(linebuf, key_idx, delim, buf)) != NULL)
E 103
I 103
D 108
		while ((p = get_column(linebuf, key_idx, '\0', buf)) != NULL)
E 108
I 108
		while ((p = get_column(linebuf, key_idx, '\0', fbuf)) != NULL)
E 108
E 103
		{
D 108
			if (strcasecmp(name, p) == 0)
E 108
I 108
			if (strcasecmp(nbuf, p) == 0)
E 108
			{
				found = TRUE;
				break;
			}
			key_idx++;
		}
E 111
I 111
		found = extract_canonname(nbuf, linebuf, cbuf);
E 111
	}
	fclose(f);
	if (!found)
	{
		*statp = EX_NOHOST;
		return FALSE;
	}

D 111
	if (hbsize >= strlen(cname))
E 111
I 111
	if (hbsize >= strlen(cbuf))
E 111
	{
D 111
		strcpy(name, cname);
E 111
I 111
		strcpy(name, cbuf);
E 111
		*statp = EX_OK;
		return TRUE;
	}
	*statp = EX_UNAVAILABLE;
	return FALSE;
}
E 95
/*
E 68
E 67
E 66
D 21
**  MAP_REWRITE -- rewrite a database key, interpolating %n indications.
E 21
I 21
**  STAB (Symbol Table) Modules
*/


/*
D 22
**  STAB_ALOOKUP -- look up alias in symbol table
E 22
I 22
**  STAB_MAP_LOOKUP -- look up alias in symbol table
E 22
*/

char *
D 35
stab_map_lookup(map, name)
E 35
I 35
stab_map_lookup(map, name, av, pstat)
E 35
	register MAP *map;
	char *name;
I 35
	char **av;
	int *pstat;
E 35
{
	register STAB *s;

D 29
	if (tTd(27, 20))
E 29
I 29
	if (tTd(38, 20))
E 29
D 65
		printf("stab_lookup(%s)\n", name);
E 65
I 65
		printf("stab_lookup(%s, %s)\n",
			map->map_mname, name);
E 65

	s = stab(name, ST_ALIAS, ST_FIND);
	if (s != NULL)
		return (s->s_alias);
	return (NULL);
}


/*
D 22
**  STAB_ASTORE -- store in symtab (actually using during init, not rebuild)
E 22
I 22
**  STAB_MAP_STORE -- store in symtab (actually using during init, not rebuild)
E 22
*/

void
stab_map_store(map, lhs, rhs)
	register MAP *map;
	char *lhs;
	char *rhs;
{
	register STAB *s;

	s = stab(lhs, ST_ALIAS, ST_ENTER);
	s->s_alias = newstr(rhs);
}


/*
D 22
**  STAB_AINIT -- initialize (reads data file)
E 22
I 22
**  STAB_MAP_OPEN -- initialize (reads data file)
**
**	This is a wierd case -- it is only intended as a fallback for
**	aliases.  For this reason, opens for write (only during a
**	"newaliases") always fails, and opens for read open the
**	actual underlying text file instead of the database.
E 22
*/

bool
stab_map_open(map, mode)
	register MAP *map;
	int mode;
{
I 38
	FILE *af;
I 43
	struct stat st;
E 43

E 38
D 35
	FILE *af;

E 35
D 29
	if (tTd(27, 2))
E 29
I 29
	if (tTd(38, 2))
E 29
D 65
		printf("stab_map_open(%s)\n", map->map_file);
E 65
I 65
		printf("stab_map_open(%s, %s)\n",
			map->map_mname, map->map_file);
E 65

	if (mode != O_RDONLY)
I 22
	{
		errno = ENODEV;
E 22
		return FALSE;
I 22
	}
I 38

	af = fopen(map->map_file, "r");
	if (af == NULL)
		return FALSE;
D 64
	readaliases(map, af, TRUE);
E 64
I 64
	readaliases(map, af, FALSE, FALSE);
E 64
I 43

	if (fstat(fileno(af), &st) >= 0)
		map->map_mtime = st.st_mtime;
E 43
	fclose(af);
E 38
E 22

D 22
	af = fopen(map->map_file, "r");
	if (af == NULL)
		return FALSE;
E 22
	return TRUE;
}
D 65


/*
D 22
**  STAB_AREBUILD -- rebuild alias file
E 22
I 22
D 48
**  STAB_MAP_CLOSE -- close symbol table (???)
E 48
I 48
**  STAB_MAP_CLOSE -- close symbol table.
**
**	Since this is in memory, there is nothing to do.
E 48
E 22
*/

void
D 22
stab_map_rebuild(map, fp, automatic, e)
	MAP *map;
	FILE *fp;
	int automatic;
	ENVELOPE *e;
{
	if (tTd(27, 2))
		printf("stab_map_rebuild(%s)\n", map->map_file);

	map->map_flags |= MF_WRITABLE|MF_VALID;
}


/*
**  STAB_ACLOSE -- close symbol table (???)
*/

void
E 22
stab_map_close(map)
	MAP *map;
{
	/* ignore it */
}
E 65
/*
**  Implicit Modules
E 21
**
D 21
**	Parameters:
**		s -- the string to rewrite, NOT necessarily null terminated.
**		slen -- the length of s.
**		buf -- the place to write it.
**		buflen -- the length of buf.
**		av -- arguments to interpolate into buf.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
E 21
I 21
**	Tries several types.  For back compatibility of aliases.
E 21
*/

D 21
map_rewrite(s, slen, buf, buflen, av)
	register char *s;
	int slen;
	char buf[];
	int buflen;
E 21
I 21

/*
D 22
**  IMPL_ALOOKUP -- lookup in best open database
E 22
I 22
**  IMPL_MAP_LOOKUP -- lookup in best open database
E 22
*/

char *
impl_map_lookup(map, name, av, pstat)
	MAP *map;
	char *name;
E 21
	char **av;
I 21
	int *pstat;
E 21
{
D 21
	register char *bp;
	char *buflim;
	register char c;
	char **avp;
	register char *ap;
E 21
I 21
D 29
	if (tTd(27, 20))
E 29
I 29
	if (tTd(38, 20))
E 29
D 65
		printf("impl_map_lookup(%s)\n", name);
E 65
I 65
		printf("impl_map_lookup(%s, %s)\n",
			map->map_mname, name);
E 65
E 21

D 21
	if (tTd(23, 1))
E 21
I 21
#ifdef NEWDB
D 22
	if (bitset(MF_IMPL_HASH, map->map_flags))
E 22
I 22
	if (bitset(MF_IMPL_HASH, map->map_mflags))
E 22
		return db_map_lookup(map, name, av, pstat);
#endif
#ifdef NDBM
D 22
	if (bitset(MF_IMPL_NDBM, map->map_flags))
E 22
I 22
	if (bitset(MF_IMPL_NDBM, map->map_mflags))
E 22
		return ndbm_map_lookup(map, name, av, pstat);
#endif
	return stab_map_lookup(map, name, av, pstat);
}

/*
D 22
**  IMPL_ASTORE -- store in open databases
E 22
I 22
**  IMPL_MAP_STORE -- store in open databases
E 22
*/

void
impl_map_store(map, lhs, rhs)
	MAP *map;
	char *lhs;
	char *rhs;
{
#ifdef NEWDB
D 22
	if (bitset(MF_IMPL_HASH, map->map_flags))
E 22
I 22
	if (bitset(MF_IMPL_HASH, map->map_mflags))
E 22
		db_map_store(map, lhs, rhs);
#endif
#ifdef NDBM
D 22
	if (bitset(MF_IMPL_NDBM, map->map_flags))
E 22
I 22
	if (bitset(MF_IMPL_NDBM, map->map_mflags))
E 22
		ndbm_map_store(map, lhs, rhs);
#endif
	stab_map_store(map, lhs, rhs);
}

/*
**  IMPL_MAP_OPEN -- implicit database open
*/

bool
impl_map_open(map, mode)
	MAP *map;
	int mode;
{
	struct stat stb;

D 29
	if (tTd(27, 2))
E 29
I 29
	if (tTd(38, 2))
E 29
D 52
		printf("impl_map_open(%s)\n", map->map_file);
E 52
I 52
D 65
		printf("impl_map_open(%s, %d)\n", map->map_file, mode);
E 65
I 65
		printf("impl_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);
E 65
E 52

	if (stat(map->map_file, &stb) < 0)
E 21
	{
D 21
		printf("map_rewrite(%.*s), av =\n", slen, s);
		for (avp = av; *avp != NULL; avp++)
			printf("\t%s\n", *avp);
E 21
I 21
		/* no alias file at all */
I 52
		if (tTd(38, 3))
			printf("no map file\n");
E 52
		return FALSE;
E 21
	}

D 21
	bp = buf;
	buflim = &buf[buflen - 2];
	while (--slen >= 0 && (c = *s++) != '\0')
E 21
I 21
#ifdef NEWDB
I 22
	map->map_mflags |= MF_IMPL_HASH;
E 22
	if (hash_map_open(map, mode))
E 21
	{
D 21
		if (c != '%')
		{
  pushc:
			if (bp < buflim)
				*bp++ = c;
			continue;
		}
		if (--slen < 0 || (c = *s++) == '\0')
			c = '%';
		if (c == '%')
			goto pushc;
D 12
		if (!isdigit(c))
E 12
I 12
		if (!(isascii(c) && isdigit(c)))
E 12
		{
			*bp++ = '%';
			goto pushc;
		}
		c -= '0';
		for (avp = av; --c >= 0 && *avp != NULL; avp++)
			continue;
		if (*avp == NULL)
			continue;
E 21
I 21
D 22
		map->map_flags |= MF_IMPL_HASH;
		return TRUE;
E 22
I 22
D 42
#if defined(NDBM) && defined(YPCOMPAT)
E 42
I 42
#if defined(NDBM) && defined(NIS)
E 42
D 30
		if (mode == O_RDONLY || access("/var/yp/Makefile", R_OK) == 0)
E 30
I 30
D 102
		if (mode == O_RDONLY || access("/var/yp/Makefile", R_OK) != 0)
E 102
I 102
		if (mode == O_RDONLY || strstr(map->map_file, "/yp/") == NULL)
E 102
E 30
#endif
			return TRUE;
E 22
	}
I 22
	else
		map->map_mflags &= ~MF_IMPL_HASH;
E 22
#endif
#ifdef NDBM
I 22
	map->map_mflags |= MF_IMPL_NDBM;
E 22
	if (ndbm_map_open(map, mode))
	{
D 22
		map->map_flags |= MF_IMPL_NDBM;
E 22
		return TRUE;
	}
I 22
	else
		map->map_mflags &= ~MF_IMPL_NDBM;
E 22
#endif
E 21

I 22
D 49
#if !defined(NEWDB) && !defined(NDBM)
E 49
I 49
#if defined(NEWDB) || defined(NDBM)
E 49
E 22
D 21
		/* transliterate argument into output string */
		for (ap = *avp; (c = *ap++) != '\0'; )
		{
			if (bp < buflim)
				*bp++ = c;
		}
E 21
I 21
	if (Verbose)
		message("WARNING: cannot open alias database %s", map->map_file);
I 54
#else
	if (mode != O_RDONLY)
		usrerr("Cannot rebuild aliases: no database format defined");
E 54
I 22
#endif
E 22

D 22
	if (stab_map_open(map, mode))
	{
		return TRUE;
E 21
	}
D 21
	*bp++ = '\0';
	if (tTd(23, 1))
		printf("map_rewrite => %s\n", buf);
E 21
I 21

	return FALSE;
E 22
I 22
	return stab_map_open(map, mode);
E 22
}

I 22

E 22
/*
D 22
**  IMPL_AREBUILD -- rebuild alias database
E 22
I 22
**  IMPL_MAP_CLOSE -- close any open database(s)
E 22
*/

void
D 22
impl_map_rebuild(map, fp, automatic, e)
E 22
I 22
impl_map_close(map)
E 22
	MAP *map;
D 22
	FILE *fp;
	int automatic;
	ENVELOPE *e;
E 22
{
I 73
	if (tTd(38, 20))
		printf("impl_map_close(%s, %s, %x)\n",
			map->map_mname, map->map_file, map->map_mflags);
E 73
#ifdef NEWDB
D 22
	DB *ndb;
	char buf[MAXNAME];
#endif

	if (tTd(27, 2))
		printf("impl_map_rebuild(%s)\n", map->map_file);

#ifdef NEWDB
	(void) strcpy(buf, map->map_file);
	(void) strcat(buf, ".db");
	ndb = dbopen(buf, O_RDWR|O_CREAT|O_TRUNC, DBMMODE, DB_HASH, NULL);
	if (ndb == NULL)
E 22
I 22
	if (bitset(MF_IMPL_HASH, map->map_mflags))
E 22
	{
D 22
		syserr("rebuildaliases: cannot create %s", buf);
E 22
I 22
		db_map_close(map);
		map->map_mflags &= ~MF_IMPL_HASH;
E 22
	}
D 22
	else
	{
		map->map_db2 = ndb;
		map->map_flags |= MF_IMPL_HASH;
#if defined(NDBM) && defined(YPCOMPAT)
		if (access("/var/yp/Makefile", R_OK) != 0)
E 22
#endif
D 22
			goto readem;
	}
#endif
E 22

#ifdef NDBM
D 22
	map->map_db1 = (void *) dbm_open(map->map_file, O_RDWR|O_CREAT|O_TRUNC, DBMMODE);
	if (map->map_db1 == NULL)
E 22
I 22
	if (bitset(MF_IMPL_NDBM, map->map_mflags))
E 22
	{
D 22
		syserr("rebuildaliases: cannot create %s.{pag,dir}",
			map->map_file);
E 22
I 22
		ndbm_map_close(map);
		map->map_mflags &= ~MF_IMPL_NDBM;
E 22
	}
D 22
	else
	{
		map->map_flags |= MF_IMPL_NDBM;
	}
E 22
#endif
I 65
}
/*
**  User map class.
**
**	Provides access to the system password file.
*/

/*
**  USER_MAP_OPEN -- open user map
**
**	Really just binds field names to field numbers.
*/

bool
user_map_open(map, mode)
	MAP *map;
	int mode;
{
	if (tTd(38, 2))
		printf("user_map_open(%s)\n", map->map_mname);

	if (mode != O_RDONLY)
	{
		/* issue a pseudo-error message */
#ifdef ENOSYS
		errno = ENOSYS;
#else
# ifdef EFTYPE
		errno = EFTYPE;
# else
		errno = ENXIO;
# endif
#endif
		return FALSE;
	}
	if (map->map_valcolnm == NULL)
		/* nothing */ ;
	else if (strcasecmp(map->map_valcolnm, "name") == 0)
		map->map_valcolno = 1;
	else if (strcasecmp(map->map_valcolnm, "passwd") == 0)
		map->map_valcolno = 2;
	else if (strcasecmp(map->map_valcolnm, "uid") == 0)
		map->map_valcolno = 3;
	else if (strcasecmp(map->map_valcolnm, "gid") == 0)
		map->map_valcolno = 4;
	else if (strcasecmp(map->map_valcolnm, "gecos") == 0)
		map->map_valcolno = 5;
	else if (strcasecmp(map->map_valcolnm, "dir") == 0)
		map->map_valcolno = 6;
	else if (strcasecmp(map->map_valcolnm, "shell") == 0)
		map->map_valcolno = 7;
	else
	{
		syserr("User map %s: unknown column name %s",
			map->map_mname, map->map_valcolnm);
		return FALSE;
	}
	return TRUE;
}


/*
**  USER_MAP_LOOKUP -- look up a user in the passwd file.
*/

D 88
#include <pwd.h>

E 88
char *
user_map_lookup(map, key, av, statp)
	MAP *map;
	char *key;
	char **av;
	int *statp;
{
	struct passwd *pw;

	if (tTd(38, 20))
		printf("user_map_lookup(%s, %s)\n",
			map->map_mname, key);

D 88
	pw = getpwnam(key);
E 88
I 88
	pw = sm_getpwnam(key);
E 88
	if (pw == NULL)
		return NULL;
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, key, strlen(key), NULL);
	else
	{
D 81
		char *rwval;
E 81
I 81
		char *rwval = NULL;
E 81
		char buf[30];

		switch (map->map_valcolno)
		{
		  case 0:
		  case 1:
D 68
			rwval = key;
E 68
I 68
			rwval = pw->pw_name;
E 68
			break;

		  case 2:
			rwval = pw->pw_passwd;
			break;

		  case 3:
			sprintf(buf, "%d", pw->pw_uid);
			rwval = buf;
			break;

		  case 4:
			sprintf(buf, "%d", pw->pw_gid);
			rwval = buf;
			break;

		  case 5:
			rwval = pw->pw_gecos;
			break;

		  case 6:
			rwval = pw->pw_dir;
			break;

		  case 7:
			rwval = pw->pw_shell;
			break;
		}
		return map_rewrite(map, rwval, strlen(rwval), av);
	}
}
/*
I 76
D 115
**  BESTMX -- find the best MX for a name
**
**	This is really a hack, but I don't see any obvious way
**	to generalize it at the moment.
*/

#if NAMED_BIND

char *
bestmx_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
        int nmx;
        auto int rcode;
        char *mxhosts[MAXMXHOSTS + 1];

	nmx = getmxrr(name, mxhosts, FALSE, &rcode);
	if (nmx <= 0)
		return NULL;
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, mxhosts[0], strlen(mxhosts[0]), av);
}

#endif
/*
E 115
I 96
**  Program map type.
**
**	This provides access to arbitrary programs.  It should be used
**	only very sparingly, since there is no way to bound the cost
**	of invoking an arbitrary program.
*/

char *
prog_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
	int i;
	register char *p;
	int fd;
	auto pid_t pid;
I 110
	char *rval;
	int stat;
E 110
	char *argv[MAXPV + 1];
	char buf[MAXLINE];

	if (tTd(38, 20))
		printf("prog_map_lookup(%s, %s) %s\n",
			map->map_mname, name, map->map_file);

	i = 0;
	argv[i++] = map->map_file;
	strcpy(buf, map->map_rebuild);
	for (p = strtok(buf, " \t"); p != NULL; p = strtok(NULL, " \t"))
	{
		if (i >= MAXPV - 1)
			break;
		argv[i++] = p;
	}
	argv[i++] = name;
	argv[i] = NULL;
	pid = prog_open(argv, &fd, CurEnv);
	if (pid < 0)
	{
D 110
		if (tTd(38, 9))
E 110
I 110
		if (!bitset(MF_OPTIONAL, map->map_mflags))
			syserr("prog_map_lookup(%s) failed (%s) -- closing",
				map->map_mname, errstring(errno));
		else if (tTd(38, 9))
E 110
			printf("prog_map_lookup(%s) failed (%s) -- closing",
				map->map_mname, errstring(errno));
		map->map_mflags &= ~(MF_VALID|MF_OPEN);
I 110
		*statp = EX_OSFILE;
E 110
		return NULL;
	}
	i = read(fd, buf, sizeof buf - 1);
D 110
	if (i <= 0 && tTd(38, 2))
		printf("prog_map_lookup(%s): read error %s\n",
E 110
I 110
	if (i < 0)
	{
		syserr("prog_map_lookup(%s): read error %s\n",
E 110
D 99
			map->map_mname, strerror(errno));
E 99
I 99
			map->map_mname, errstring(errno));
I 110
		rval = NULL;
	}
	else if (i == 0 && tTd(38, 2))
	{
		printf("prog_map_lookup(%s): empty answer\n",
			map->map_mname);
		rval = NULL;
	}
E 110
E 99
	if (i > 0)
	{
D 110
		char *rval;

E 110
		buf[i] = '\0';
		p = strchr(buf, '\n');
		if (p != NULL)
			*p = '\0';

		/* collect the return value */
		if (bitset(MF_MATCHONLY, map->map_mflags))
			rval = map_rewrite(map, name, strlen(name), NULL);
		else
			rval = map_rewrite(map, buf, strlen(buf), NULL);

		/* now flush any additional output */
		while ((i = read(fd, buf, sizeof buf)) > 0)
			continue;
D 110
		close(fd);

		/* and wait for the process to terminate */
		*statp = waitfor(pid);

		return rval;
E 110
	}

I 110
	/* wait for the process to terminate */
E 110
	close(fd);
D 110
	*statp = waitfor(pid);
	return NULL;
E 110
I 110
	stat = waitfor(pid);

	if (stat == -1)
	{
		syserr("prog_map_lookup(%s): wait error %s\n",
			map->map_mname, errstring(errno));
		*statp = EX_SOFTWARE;
		rval = NULL;
	}
D 112
	else if (WIFEXITED(*statp))
E 112
I 112
	else if (WIFEXITED(stat))
E 112
	{
D 112
		*statp = WEXITSTATUS(*statp);
E 112
I 112
		*statp = WEXITSTATUS(stat);
E 112
	}
	else
	{
		syserr("prog_map_lookup(%s): child died on signal %d",
D 112
			map->map_mname, *statp);
E 112
I 112
			map->map_mname, stat);
E 112
		*statp = EX_UNAVAILABLE;
		rval = NULL;
	}
	return rval;
E 110
}
/*
E 96
E 76
**  Sequenced map type.
**
**	Tries each map in order until something matches, much like
**	implicit.  Stores go to the first map in the list that can
**	support storing.
I 68
**
**	This is slightly unusual in that there are two interfaces.
**	The "sequence" interface lets you stack maps arbitrarily.
**	The "switch" interface builds a sequence map by looking
**	at a system-dependent configuration file such as
**	/etc/nsswitch.conf on Solaris or /etc/svc.conf on Ultrix.
**
**	We don't need an explicit open, since all maps are
**	opened during startup, including underlying maps.
E 68
*/

/*
**  SEQ_MAP_PARSE -- Sequenced map parsing
*/

bool
seq_map_parse(map, ap)
	MAP *map;
	char *ap;
{
	int maxmap;

	if (tTd(38, 2))
		printf("seq_map_parse(%s, %s)\n", map->map_mname, ap);
	maxmap = 0;
	while (*ap != '\0')
	{
		register char *p;
		STAB *s;

		/* find beginning of map name */
		while (isascii(*ap) && isspace(*ap))
			ap++;
		for (p = ap; isascii(*p) && isalnum(*p); p++)
			continue;
		if (*p != '\0')
			*p++ = '\0';
		while (*p != '\0' && (!isascii(*p) || !isalnum(*p)))
			p++;
		if (*ap == '\0')
		{
			ap = p;
			continue;
		}
		s = stab(ap, ST_MAP, ST_FIND);
		if (s == NULL)
		{
			syserr("Sequence map %s: unknown member map %s",
				map->map_mname, ap);
		}
		else if (maxmap == MAXMAPSTACK)
		{
			syserr("Sequence map %s: too many member maps (%d max)",
				map->map_mname, MAXMAPSTACK);
			maxmap++;
		}
		else if (maxmap < MAXMAPSTACK)
		{
			map->map_stack[maxmap++] = &s->s_map;
		}
		ap = p;
	}
	return TRUE;
}


/*
I 68
**  SWITCH_MAP_OPEN -- open a switched map
**
**	This looks at the system-dependent configuration and builds
**	a sequence map that does the same thing.
**
**	Every system must define a switch_map_find routine in conf.c
**	that will return the list of service types associated with a
**	given service class.
*/

bool
switch_map_open(map, mode)
	MAP *map;
	int mode;
{
	int mapno;
	int nmaps;
	char *maptype[MAXMAPSTACK];

	if (tTd(38, 2))
		printf("switch_map_open(%s, %s, %d)\n",
			map->map_mname, map->map_file, mode);

D 69
	nmaps = switch_map_find(map->map_file, maptype);
E 69
I 69
	nmaps = switch_map_find(map->map_file, maptype, map->map_return);
E 69
	if (tTd(38, 19))
	{
		printf("\tswitch_map_find => %d\n", nmaps);
		for (mapno = 0; mapno < nmaps; mapno++)
			printf("\t\t%s\n", maptype[mapno]);
	}
	if (nmaps <= 0 || nmaps > MAXMAPSTACK)
		return FALSE;

	for (mapno = 0; mapno < nmaps; mapno++)
	{
		register STAB *s;
		char nbuf[MAXNAME + 1];

		if (maptype[mapno] == NULL)
			continue;
		(void) sprintf(nbuf, "%s.%s", map->map_file, maptype[mapno]);
		s = stab(nbuf, ST_MAP, ST_FIND);
		if (s == NULL)
		{
			syserr("Switch map %s: unknown member map %s",
				map->map_mname, nbuf);
		}
		else
		{
			map->map_stack[mapno] = &s->s_map;
			if (tTd(38, 4))
				printf("\tmap_stack[%d] = %s:%s\n",
					mapno, s->s_map.map_class->map_cname,
					nbuf);
		}
	}
	return TRUE;
}


/*
**  SEQ_MAP_CLOSE -- close all underlying maps
*/

I 106
void
E 106
seq_map_close(map)
	MAP *map;
{
	int mapno;

	if (tTd(38, 20))
		printf("seq_map_close(%s)\n", map->map_mname);
	for (mapno = 0; mapno < MAXMAPSTACK; mapno++)
	{
		MAP *mm = map->map_stack[mapno];

		if (mm == NULL || !bitset(MF_OPEN, mm->map_mflags))
			continue;
		mm->map_class->map_close(mm);
I 92
		mm->map_mflags &= ~(MF_OPEN|MF_WRITABLE);
E 92
	}
}


/*
E 68
**  SEQ_MAP_LOOKUP -- sequenced map lookup
*/

char *
seq_map_lookup(map, key, args, pstat)
	MAP *map;
	char *key;
	char **args;
	int *pstat;
{
	int mapno;
	int mapbit = 0x01;

	if (tTd(38, 20))
		printf("seq_map_lookup(%s, %s)\n", map->map_mname, key);

	for (mapno = 0; mapno < MAXMAPSTACK; mapbit <<= 1, mapno++)
	{
		MAP *mm = map->map_stack[mapno];
		int stat = 0;
		char *rv;

		if (mm == NULL)
			continue;
		if (!bitset(MF_OPEN, mm->map_mflags))
		{
			if (bitset(mapbit, map->map_return[MA_UNAVAIL]))
I 68
			{
				*pstat = EX_UNAVAILABLE;
E 68
				return NULL;
I 68
			}
E 68
			continue;
		}
		rv = mm->map_class->map_lookup(mm, key, args, &stat);
		if (rv != NULL)
			return rv;
		if (stat == 0 && bitset(mapbit, map->map_return[MA_NOTFOUND]))
			return NULL;
		if (stat != 0 && bitset(mapbit, map->map_return[MA_TRYAGAIN]))
		{
			*pstat = stat;
			return NULL;
		}
	}
	return NULL;
}


/*
**  SEQ_MAP_STORE -- sequenced map store
*/

void
seq_map_store(map, key, val)
	MAP *map;
	char *key;
	char *val;
{
	int mapno;

	if (tTd(38, 12))
		printf("seq_map_store(%s, %s, %s)\n",
			map->map_mname, key, val);

	for (mapno = 0; mapno < MAXMAPSTACK; mapno++)
	{
		MAP *mm = map->map_stack[mapno];

		if (mm == NULL || !bitset(MF_WRITABLE, mm->map_mflags))
			continue;

		mm->map_class->map_store(mm, key, val);
		return;
	}
	syserr("seq_map_store(%s, %s, %s): no writable map",
		map->map_mname, key, val);
I 95
D 109
}
/*
**  GETCANONNAME -- look up name using service switch
**
**	Parameters:
**		host -- the host name to look up.
**		hbsize -- the size of the host buffer.
**		trymx -- if set, try MX records.
**
**	Returns:
**		TRUE -- if the host was found.
**		FALSE -- otherwise.
*/

bool
getcanonname(host, hbsize, trymx)
	char *host;
	int hbsize;
	bool trymx;
{
	int nmaps;
	int mapno;
	bool found = FALSE;
	auto int stat;
	char *maptype[MAXMAPSTACK];
	short mapreturn[MAXMAPACTIONS];
	extern int h_errno;

	nmaps = switch_map_find("hosts", maptype, mapreturn);
	for (mapno = 0; mapno < nmaps; mapno++)
	{
		int i;

		if (tTd(38, 20))
			printf("getcanonname(%s), trying %s\n",
				host, maptype[mapno]);
		if (strcmp("files", maptype[mapno]) == 0)
			found = text_getcanonname(host, hbsize, &stat);
#ifdef NIS
		else if (strcmp("nis", maptype[mapno]) == 0)
			found = nis_getcanonname(host, hbsize, &stat);
#endif
#ifdef NISPLUS
		else if (strcmp("nisplus", maptype[mapno]) == 0)
			found = nisplus_getcanonname(host, hbsize, &stat);
#endif
#if NAMED_BIND
		else if (strcmp("dns", maptype[mapno]) == 0)
			found = dns_getcanonname(host, hbsize, trymx, &stat);
#endif
		else
		{
			found = FALSE;
			stat = EX_UNAVAILABLE;
		}
		if (found)
			break;

		/* see if we should continue */
		if (stat == EX_TEMPFAIL)
			i = MA_TRYAGAIN;
		else if (stat == EX_NOHOST)
			i = MA_NOTFOUND;
		else
			i = MA_UNAVAIL;
		if (bitset(1 << mapno, mapreturn[i]))
			break;
	}

	if (found)
	{
		char *d;

		if (tTd(38, 20))
			printf("getcanonname(%s), found\n", host);

		/*
		**  If returned name is still single token, compensate
		**  by tagging on $m.  This is because some sites set
		**  up their DNS or NIS databases wrong.
		*/

		if ((d = strchr(host, '.')) == NULL || d[1] == '\0')
		{
			d = macvalue('m', CurEnv);
			if (d != NULL &&
			    hbsize > (int) (strlen(host) + strlen(d) + 1))
			{
				if (host[strlen(host) - 1] != '.')
					strcat(host, ".");
				strcat(host, d);
			}
			else
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	if (tTd(38, 20))
		printf("getcanonname(%s), failed, stat=%d\n", host, stat);

#if NAMED_BIND
	if (stat == EX_NOHOST)
		h_errno = HOST_NOT_FOUND;
	else
		h_errno = TRY_AGAIN;
#endif

	return FALSE;
E 109
E 95
E 65
D 22

	if (!bitset(MF_IMPL_HASH|MF_IMPL_NDBM, map->map_flags))
		return;

  readem:
	map->map_flags |= MF_WRITABLE|MF_VALID;
E 22
}
D 22


/*
**  IMPL_ACLOSE -- close any open database(s)
E 22
I 22
/*
**  NULL stubs
E 22
*/

D 22
void
impl_map_close(map, e)
E 22
I 22
bool
null_map_open(map, mode)
E 22
	MAP *map;
D 22
	ENVELOPE *e;
E 22
I 22
	int mode;
E 22
{
D 22
#ifdef NEWDB
	if (bitset(MF_IMPL_HASH, map->map_flags))
		db_map_close(map, e);
#endif

#ifdef NDBM
	if (bitset(MF_IMPL_NDBM, map->map_flags))
		ndbm_map_close(map, e);
#endif
E 22
I 22
	return TRUE;
E 22
}
D 22
/*
**  SETUPALIASES -- set up aliases classes
*/
E 22

D 22
extern bool	host_map_init __P((MAP *, char *));
extern char	*host_map_lookup __P((MAP *, char *, char **, int *));

extern bool	dequote_init __P((MAP *, char *));
extern char	*dequote_map __P((MAP *, char *, char **, int *));

#if 0
extern bool	udb_map_parse __P((MAP *, char *));
extern char	*udb_map_lookup __P((MAP *, char *, char **, int *));
#endif

static MAPCLASS	MapClasses[] =
E 22
I 22
void
null_map_close(map)
	MAP *map;
E 22
{
D 22
#ifdef NEWDB
	{
		"hash",		".db",	map_parseargs,
		db_map_lookup,		db_map_store,
		db_map_rebuild,		hash_map_open,	db_map_close,
	},
E 22
I 22
	return;
}
E 22

D 22
	{
		"btree",	".db",	map_parseargs,
		db_map_lookup,		db_map_store,
		db_map_rebuild,		bt_map_open,	db_map_close,
	},
#endif

#ifdef NDBM
	{
		"dbm",		".dir",	map_parseargs,
		ndbm_map_lookup,	ndbm_map_store,
		ndbm_map_rebuild,	ndbm_map_open,	ndbm_map_close,
	},
#endif

#ifdef NIS
	{
		"nis",		NULL,	map_parseargs,
		nis_map_lookup,		NULL,
		NULL,			nis_map_open,	nis_map_close,
	},
#endif

	{
		"stab",		NULL,	map_parseargs,
		stab_map_lookup,	stab_map_store,
		NULL,			stab_map_open,	stab_map_close,
	},

	{
		"implicit",	NULL,	map_parseargs,
		impl_map_lookup,	impl_map_store,
		impl_map_rebuild,	impl_map_open,	impl_map_close,
	},

	/* host DNS lookup */
	{
		"host",		NULL,	host_map_init,
		host_map_lookup,	NULL,
		NULL,			NULL,		NULL,
	},

	/* dequote map */
	{
		"dequote",	NULL,	dequote_init,
		dequote_map,		NULL,
		NULL,			NULL,		NULL,
	},

#if 0
# ifdef USERDB
	/* user database */
	{
		"udb",		".db",	udb_map_parse,
		udb_map_lookup,		NULL,
		NULL,			NULL,		NULL,
	},
# endif
#endif

	{
		NULL
	}
};

setupmaps()
E 22
I 22
void
null_map_store(map, key, val)
	MAP *map;
	char *key;
	char *val;
E 22
{
D 22
	register MAPCLASS *mc;
	register STAB *s;

	for (mc = MapClasses; mc->map_cname != NULL; mc++)
	{
		s = stab(mc->map_cname, ST_MAPCLASS, ST_ENTER);
		s->s_mapclass = mc;
	}
E 22
I 22
	return;
E 22
E 21
}
I 74


/*
**  BOGUS stubs
*/

char *
bogus_map_lookup(map, key, args, pstat)
	MAP *map;
	char *key;
	char **args;
	int *pstat;
{
	*pstat = EX_TEMPFAIL;
	return NULL;
}

MAPCLASS	BogusMapClass =
{
	"bogus-map",		NULL,		0,
	NULL,		bogus_map_lookup,	null_map_store,
	null_map_open,	null_map_close,
};
E 74
E 1
