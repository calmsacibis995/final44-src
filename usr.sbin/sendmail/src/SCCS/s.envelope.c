h15250
s 00001/00002/00883
d D 8.67 95/06/10 12:23:27 eric 164 163
c fix angle-bracketed-return-path problem; expand EF_IS_MIME
e
s 00000/00004/00885
d D 8.66 95/05/28 11:49:20 eric 163 162
c lint
e
s 00001/00001/00888
d D 8.65 95/05/27 07:44:51 eric 162 161
c make USERDB be a 0/1 option instead of #ifdef/#ifndef
e
s 00002/00002/00887
d D 8.64 95/04/23 14:02:31 eric 161 160
c updates for new DSN drafts
e
s 00004/00000/00885
d D 8.63 95/04/22 15:58:53 eric 160 159
c updates for new status system codes and Multipart/Report drafts
e
s 00001/00001/00884
d D 8.62 95/04/21 09:56:56 eric 159 158
c update copyright notice
e
s 00002/00001/00883
d D 8.61 95/04/13 17:36:09 eric 158 157
c fix postmaster notifications -- it was getting the body in
c some inappropriate cases, and sometimes no message at all; clean up
c dead.letter processing
e
s 00019/00004/00865
d D 8.60 95/04/07 07:29:08 eric 157 156
c fix botch in saving from domain for later insertion onto
c unqualified addresses
e
s 00001/00001/00868
d D 8.59 95/04/02 09:28:35 eric 156 155
c MIME cleanup to get header line parsing right
e
s 00001/00001/00868
d D 8.58 95/03/31 16:53:48 eric 155 154
c merge a bit with Sun version
e
s 00001/00003/00868
d D 8.57 95/03/31 10:51:50 eric 154 153
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00004/00011/00867
d D 8.56 95/03/27 09:25:27 eric 153 152
c more cleanup for DSN drafts
e
s 00075/00003/00803
d D 8.55 95/03/21 16:41:54 eric 152 151
c improved debugging for envelope flags
e
s 00006/00007/00800
d D 8.54 95/03/21 15:28:17 eric 151 150
c eliminate `D' line in qf file
e
s 00006/00016/00801
d D 8.53 95/03/21 09:26:37 eric 150 149
c new DSN draft
e
s 00001/00001/00816
d D 8.52 95/03/14 09:10:46 eric 149 148
c change call to expand() to be more rational (and consistent!)
e
s 00005/00002/00812
d D 8.51 95/03/07 08:30:34 eric 148 146
c line-buffer transcript file
e
s 00001/00001/00750
d D 8.34.1.1 95/02/28 13:25:38 eric 147 130
c make fdopen() mode compatible with open() mode
e
s 00001/00001/00813
d D 8.50 95/02/17 12:51:43 eric 146 145
c fix conflict between open file mode and stdio fdopen mode
e
s 00015/00000/00799
d D 8.49 94/12/01 08:40:43 eric 145 144
c if we have FATALERRS set but no errors in addresses, set errors
c in all the addresses
e
s 00001/00000/00798
d D 8.48 94/11/28 09:16:23 eric 144 143
c restore PRIV_NORECEIPTS flag, even in DSN mode
e
s 00003/00003/00795
d D 8.47 94/11/22 22:24:48 eric 143 142
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00007/00008/00791
d D 8.46 94/11/22 17:47:21 eric 142 141
c cleanup for return-receipts
e
s 00002/00001/00797
d D 8.45 94/11/22 15:34:57 eric 141 140
c avoid sending a message back on bogus failure
e
s 00020/00009/00778
d D 8.44 94/11/21 21:07:28 eric 140 139
c convert to new DSN draft
e
s 00001/00002/00786
d D 8.43 94/11/20 08:56:37 eric 139 138
c check for "<<>>" etc as equivalent to "<>"
e
s 00047/00007/00741
d D 8.42 94/11/04 08:40:19 eric 138 137
c first cut at DSN implementation
e
s 00013/00019/00735
d D 8.41 94/09/08 15:19:54 eric 137 136
c attempt to allow udb rewriting of envelope senders; still not
c quite right, but I can't really test it without a network connection
e
s 00008/00008/00746
d D 8.40 94/08/21 15:25:45 eric 136 135
c multiple queue timeouts
e
s 00004/00001/00750
d D 8.39 94/08/16 08:46:58 eric 135 134
c don't send warning message to owner-* or *-request addresses
e
s 00001/00001/00750
d D 8.38 94/08/15 10:14:22 eric 134 133
c don't send error file with return receipts
e
s 00001/00001/00750
d D 8.37 94/08/08 07:07:30 eric 133 132
c add F=d mailer flag to turn off angle brackets on return path
e
s 00001/00001/00750
d D 8.36 94/07/03 11:47:56 eric 132 131
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00001/00001/00750
d D 8.35 94/05/29 07:31:20 eric 131 130
c clean up Subject: line on warning messages
e
s 00002/00001/00749
d D 8.34 94/04/14 09:40:50 eric 130 129
c add "noreceipts" privacy flag
e
s 00002/00003/00748
d D 8.33 94/02/10 11:24:31 eric 129 128
c better fix to NULL q_home problem
e
s 00002/00000/00749
d D 8.32 94/02/10 09:06:42 eric 128 127
c avoid core dump if $HOME not set
e
s 00001/00001/00748
d D 8.31 94/02/03 08:07:52 eric 127 126
c restore -ba mode for UK Grey book
e
s 00000/00001/00749
d D 8.30 94/01/22 10:29:28 eric 126 125
c avoid unnecessary <sys/time.h> inclusion
e
s 00008/00002/00742
d D 8.29 94/01/22 09:01:02 eric 125 124
c Apollo/POSIX changes -- leading pathname of // can legally have
c different semantics; ensure that this never happens when building pathnames
e
s 00001/00001/00743
d D 8.28 94/01/09 09:22:33 eric 124 123
c fix problem causing excessive rewriting of headers being queued
e
s 00003/00002/00741
d D 8.27 94/01/08 17:29:16 eric 123 122
c fix problem that was causing the ctladdr of whoever ran the daemon
c (usually root) to own the delivery process
e
s 00000/00015/00743
d D 8.26 93/12/24 05:25:46 eric 122 121
c no need to checkfd012() in dropenvelope -- that's a legit failure mode
e
s 00005/00002/00753
d D 8.25 93/12/11 13:53:38 eric 121 120
c arrange to log sender in SMTP even if all RCPTs failed
e
s 00003/00003/00752
d D 8.24 93/12/10 17:46:34 eric 120 119
c add a "recursion level" argument to rewrite() to detect loops politely
e
s 00002/00002/00753
d D 8.23 93/12/10 17:20:03 eric 119 118
c add bufsize parameter to prescan
e
s 00001/00000/00754
d D 8.22 93/12/10 12:41:58 eric 118 117
c avoid sending WARNING message on return-receipts
e
s 00002/00000/00752
d D 8.21 93/12/04 08:07:17 eric 117 116
c fix problem that causes dead.letter to be unwritable
e
s 00001/00001/00751
d D 8.20 93/12/02 10:17:46 eric 116 114
c fix bogus implementation of name overflow limiting
e
s 00003/00001/00751
d D 8.19.1.1 93/11/27 11:51:12 eric 115 114
c sample implementation of buildfname that handles 8-bit characters
e
s 00013/00001/00739
d D 8.19 93/11/20 06:57:29 eric 114 113
c more attempts to trap fd 1 bug
e
s 00001/00001/00739
d D 8.18 93/11/19 07:54:05 eric 113 112
c avoid passing SIZE= parameter into rulesets
e
s 00001/00001/00739
d D 8.17 93/10/31 14:46:26 eric 112 111
c nbuf, not buf
e
s 00021/00004/00719
d D 8.16 93/10/31 10:19:02 eric 111 110
c add explicit check for sender address set to program or file
e
s 00008/00008/00715
d D 8.15 93/10/28 19:39:04 eric 110 109
c dynamically allocate (instead of static) several macros
e
s 00001/00001/00722
d D 8.14 93/10/24 16:28:50 eric 109 108
c repair OutChannel in queue runs
e
s 00006/00000/00717
d D 8.13 93/10/23 12:45:31 eric 108 107
c open file debugging
e
s 00004/00000/00713
d D 8.12 93/10/16 08:49:59 eric 107 106
c check for possibility of fdopen returning null
e
s 00003/00000/00710
d D 8.11 93/09/04 11:50:51 eric 106 105
c more attempts to find the fd 1 closed error
e
s 00001/00001/00709
d D 8.10 93/08/26 11:21:53 eric 105 104
c don't do PostMasterCopy on junk mail
e
s 00003/00003/00707
d D 8.9 93/08/20 08:08:54 eric 104 103
c fix screwed up error message returns in some situations
e
s 00009/00006/00701
d D 8.8 93/08/17 09:51:50 eric 103 102
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00011/00003/00696
d D 8.7 93/08/08 11:00:14 eric 102 101
c be sure to always include angle braces on route-addrs
e
s 00002/00001/00697
d D 8.6 93/07/29 08:31:38 eric 101 100
c don't call newstr() macro with arguments with subroutine calls, since
c it double-evaluates
e
s 00013/00001/00685
d D 8.5 93/07/17 13:49:21 eric 100 99
c better error message handling: don't create bogus return messages;
c print both actual address and q_alias whereever possible
e
s 00026/00018/00660
d D 8.4 93/07/16 10:28:34 eric 99 98
c clean up error handling, including concept of local error handling
e
s 00015/00003/00663
d D 8.3 93/07/13 12:58:22 eric 98 97
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00061/00003/00605
d D 8.2 93/07/11 06:52:28 eric 97 96
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00606
d D 8.1 93/06/07 10:30:16 bostic 96 95
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00600
d D 6.35 93/05/27 11:37:16 eric 95 94
c prototype functions
e
s 00002/00000/00606
d D 6.34 93/05/03 17:21:52 eric 94 93
c if we are in Verbose mode, be sure to set sendmode to SM_DELIVER
e
s 00000/00001/00606
d D 6.33 93/04/27 18:51:40 eric 93 92
c move #include <sys/stat.h> into conf.h
e
s 00001/00001/00606
d D 6.32 93/04/26 19:59:55 eric 92 91
c make tty id buffer large enough for modern names
e
s 00003/00003/00604
d D 6.31 93/04/14 14:38:40 eric 91 90
c return status information from map lookups and from there from 
c rewrite; this allows higher level code to queue if the name server is down
e
s 00006/00006/00601
d D 6.30 93/04/10 09:28:27 eric 90 89
c implement $&x for deferred macro expansion; some POSIX compatibility
e
s 00013/00005/00594
d D 6.29 93/04/04 13:56:56 eric 89 88
c RFC 1413 (IDENT) protocol support
e
s 00001/00001/00598
d D 6.28 93/03/25 14:16:29 eric 88 87
c implement multi-word classes
e
s 00005/00001/00594
d D 6.27 93/03/25 10:03:50 eric 87 86
c improve error reporting; open new transcript on envelope cloning
e
s 00003/00002/00592
d D 6.26 93/03/19 11:46:31 eric 86 85
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00002/00001/00592
d D 6.25 93/03/19 08:50:46 eric 85 84
c move SendMode and ErrorMode into the envelope
e
s 00003/00002/00590
d D 6.24 93/03/18 19:37:08 eric 84 83
c leading blanks in aliases can cause "unparsable" from addresses
e
s 00029/00022/00563
d D 6.23 93/03/18 10:56:22 eric 83 82
c restore e_sender as sending address sans decorations
e
s 00000/00001/00585
d D 6.22 93/03/17 09:55:16 eric 82 81
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00011/00015/00575
d D 6.21 93/03/16 09:16:08 eric 81 80
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00000/00001/00590
d D 6.20 93/03/14 07:36:32 eric 80 79
c change (simplify) user and host UPPER => lower case mapping
e
s 00001/00001/00590
d D 6.19 93/03/03 09:48:46 eric 79 78
c allow prescan to return a null vector; fix some duplicate prescan errs
e
s 00013/00007/00578
d D 6.18 93/03/01 12:43:49 eric 78 77
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00001/00002/00584
d D 6.17 93/03/01 06:53:33 eric 77 76
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00003/00003/00583
d D 6.16 93/02/28 19:57:17 eric 76 75
c hooks for SMTP Service Extensions
e
s 00000/00001/00586
d D 6.15 93/02/26 08:19:38 eric 75 74
c better handling of transient errors
e
s 00004/00004/00583
d D 6.14 93/02/24 10:19:26 eric 74 73
c fix yet another problem with new owner-foo implementation
e
s 00000/00043/00587
d D 6.13 93/02/23 14:45:20 eric 73 72
c delete trusted users code; it's too easy to circumvent
e
s 00004/00004/00626
d D 6.12 93/02/23 06:31:34 eric 72 71
c overhaul status of SMTP reply codes
e
s 00004/00003/00626
d D 6.11 93/02/21 14:12:15 eric 71 70
c $d is current date, not origination date
e
s 00002/00002/00627
d D 6.10 93/02/20 13:46:32 eric 70 69
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00001/00001/00628
d D 6.9 93/02/19 16:17:26 eric 69 68
c more bug fixes from Eric Wassenaar
e
s 00004/00004/00625
d D 6.8 93/02/16 18:29:46 eric 68 67
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00000/00004/00629
d D 6.7 93/02/14 14:41:34 eric 67 66
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00007/00003/00626
d D 6.6 93/02/12 11:51:14 eric 66 65
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00001/00002/00628
d D 6.5 93/01/28 17:04:51 eric 65 64
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00001/00000/00629
d D 6.4 93/01/28 10:15:45 eric 64 63
c System 5 compatibility, misc fixes
e
s 00005/00000/00624
d D 6.3 93/01/26 11:36:30 eric 63 62
c some (iffy) changes to prevent suppressing the actual sender
c during a queue run (interaction with C line in qf file)
e
s 00014/00004/00610
d D 6.2 93/01/18 14:32:18 eric 62 61
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00000/00000/00614
d D 6.1 92/12/21 16:08:18 eric 61 60
c Release 6
e
s 00002/00002/00612
d D 5.33 92/12/08 09:46:02 eric 60 59
c make years in $t be four digits; do case folding for DBM databases
c in map.c if MF_MAPCASE set
e
s 00011/00011/00603
d D 5.32 92/11/14 11:34:09 eric 59 58
c (partially) ANSI-fy it
e
s 00003/00002/00611
d D 5.31 92/09/09 06:56:37 eric 58 57
c miscellaneous bug fixes from Bryan Costales and Craig Lant
e
s 00001/00001/00612
d D 5.30 92/07/19 10:20:00 eric 57 56
c fix bogus envelope problem in clock-driven queue runs; misc. fixes
e
s 00010/00012/00603
d D 5.29 92/07/13 16:27:39 eric 56 55
c miscellaneous changes to improve logging and messages
e
s 00024/00022/00591
d D 5.28 92/07/12 14:09:38 eric 55 54
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00043/00046/00570
d D 5.27 92/05/29 10:44:11 eric 54 53
c move call to udbsender so that full name can potentially be extracted
c from UDB instead of passwd file
e
s 00029/00027/00587
d D 5.26 92/04/16 18:40:14 eric 53 52
c try to eliminate some of the CurEnv globals
e
s 00001/00001/00613
d D 5.25 92/01/18 07:57:17 eric 52 51
c drop mode a (ARPA FTP) -- NCP is gone forever.....
e
s 00028/00001/00586
d D 5.24 91/12/15 13:59:34 eric 51 50
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00001/00004/00586
d D 5.23 91/12/14 12:36:49 eric 50 49
c fix race condition in queue file locking; generalize getla
e
s 00001/00011/00589
d D 5.22 90/06/01 19:01:40 bostic 49 48
c new copyright notice
e
s 00000/00006/00600
d D 5.21 90/04/18 13:54:49 bostic 48 47
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00009/00004/00597
d D 5.20 90/04/16 08:11:19 rick 47 46
c new locking code that uses flock()
e
s 00003/00002/00598
d D 5.19 89/02/27 09:16:43 bostic 46 45
c add types.h for pwd.h
e
s 00000/00004/00600
d D 5.18 89/01/01 17:17:14 bostic 45 44
c remove DEBUG
e
s 00004/00001/00600
d D 5.17 88/11/17 22:02:15 karels 44 43
c more cleanup, fix some inappropriate syserr's
e
s 00011/00007/00590
d D 5.16 88/11/17 10:32:04 karels 43 42
c expunge debugging/nonstandard/trojan horse commands from smtp,
c logging attempts to use them; log name/address of host from which mail received
c ("mail from" may not include it or may lie); don't allow debug to affect
c permissions locally; change some of the non-system syserrs to syslog at lower
c priority; still need to unifdef remaining debug code
e
s 00011/00009/00586
d D 5.15 88/06/30 14:58:53 bostic 42 41
c install approved copyright notice
e
s 00000/00002/00595
d D 5.14 88/04/01 16:50:46 bostic 41 40
c remove V6 #ifdefs
e
s 00016/00010/00581
d D 5.13 88/03/13 19:52:01 bostic 40 39
c add Berkeley specific header
e
s 00015/00007/00576
d D 5.12 85/12/17 21:34:48 eric 39 38
m 
c patch to clearenvelope to avoid dereferencing garbage pointers
e
s 00014/00013/00569
d D 5.11 85/11/21 18:48:49 eric 38 37
m 
c don't duplicate original envelope into error envelope
e
s 00001/00000/00581
d D 5.10 85/09/25 11:02:16 eric 37 36
m 
c DO use Ruleset 4 when defining $f -- it's very necessary (fix for <>
c will have to be done in configuration); pretty up mailq -v slightly
e
s 00000/00001/00581
d D 5.9 85/09/23 21:19:10 eric 36 35
m 
c deliver directly in SMTP if VERB command has been issued; don't
c externalize name using ruleset 4 when defining $f macro: this turns "<>"
c into "", which confuses local mail
e
s 00001/00001/00581
d D 5.8 85/09/21 16:24:10 eric 35 34
m 
c don't include ctime as part of priority, since the value affects the results of
c shouldqueue; we go back to adding ctime into the workcmpf in queue.c
e
s 00001/00000/00581
d D 5.7 85/09/21 14:44:33 eric 34 33
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00001/00001/00580
d D 5.6 85/09/19 17:43:23 eric 33 32
m 
c fix botch in clearenvelope
e
s 00002/00006/00579
d D 5.5 85/09/19 15:57:51 eric 32 31
m 
c updates to make it possible to run the queue in one process; this
c permits a database of host status to be built
e
s 00000/00000/00585
d D 5.4 85/09/19 01:25:49 eric 31 29
i 30
m 
c incorporate SMI changes -- still experimental
e
s 00018/00007/00567
d D 5.3.1.1 85/09/19 00:56:08 eric 30 29
m 
c SMI changes (somewhat)
e
s 00002/00002/00572
d D 5.3 85/06/15 18:52:01 eric 29 28
m 
c fix overzealous removal of df file
e
s 00002/00002/00572
d D 5.2 85/06/07 22:26:48 miriam 28 27
m 
c Resolve duplicate SccsId.  Ifdef variables for TTYNAME code.
e
s 00014/00000/00560
d D 5.1 85/06/07 15:04:37 dist 27 26
m 
c Add copyright
e
s 00008/00002/00552
d D 4.10 85/06/01 15:26:26 eric 26 25
m 
c More changes from Bill Nowicki -- file closing and improved logging.
e
s 00004/00005/00550
d D 4.9 85/04/20 15:14:02 eric 25 24
m 
c don't assume that all apparently local senders have passwd entries
e
s 00008/00175/00547
d D 4.8 84/12/05 23:15:29 eric 24 23
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00002/00001/00720
d D 4.7 84/08/11 23:19:57 eric 23 22
m 
c Add $[ and $] as RHS operators to look up the contents and pass them
c to maphostname; maphostname currently looks them up in /etc/hosts and
c converts them to canonical form, but could be turned into a general
c name server.....   huzzah!!
e
s 00003/00003/00718
d D 4.6 84/08/11 16:55:15 eric 22 21
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00001/00006/00720
d D 4.5 84/05/13 15:45:25 eric 21 20
m 
c remove .mailcf hack -- it's been abused.
e
s 00001/00000/00725
d D 4.4 84/03/11 19:58:35 eric 20 19
m 
c disable UPPER->lower case mapping in RHS's of aliases so that upper
c case letters can be used in file names and as args to programs.
e
s 00001/00001/00724
d D 4.3 84/03/11 16:55:30 eric 19 18
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00001/00001/00724
d D 4.2 83/08/21 15:13:37 eric 18 17
m 
c Don't print out a null pointer in debugging info.
e
s 00000/00000/00725
d D 4.1 83/07/25 19:46:40 eric 17 16
m 
c 4.2 release version
e
s 00001/00001/00724
d D 3.16 83/07/01 23:04:54 wnj 16 15
m 
c 
e
s 00040/00020/00685
d D 3.15 83/04/17 17:13:17 eric 15 14
m 199
m 224
c put true current time on SMTP greeting message; fix *(0) problems
e
s 00012/00005/00693
d D 3.14 83/03/19 14:24:53 eric 14 13
m 211
c Don't have mail from su'ed people come from "daemon"
e
s 00002/00000/00696
d D 3.13 83/03/19 13:14:17 eric 13 12
m 147
c Fix botch of putting incorrect full names on some addresses (usually
c UNIX-to-UNIX Copy)
e
s 00002/00002/00694
d D 3.12 83/03/08 19:22:27 eric 12 11
m 205
c Pass the delimiter character to parseaddr so that we can correctly
c decide between comma and space
e
s 00001/00000/00695
d D 3.11 83/02/25 21:20:12 eric 11 10
m 181
c More attempts at insuring that everything goes through ruleset 4
e
s 00001/00001/00694
d D 3.10 83/02/10 10:00:26 eric 10 9
m 176
c avoid core dump on return receipt processing; clean up return receipt
c message.
e
s 00014/00001/00681
d D 3.9 83/02/08 10:49:32 eric 9 8
m 167
m 172
m 173
m 174
c clean up problems when QUEUE compile flag not defined; clean up hostname
c code to run on non-4.1c systems; fix use of -oeq (quiet on errors) flag.
e
s 00001/00004/00681
d D 3.8 83/02/03 10:30:02 eric 8 7
m 160
c $e macro is now SMTP entry message (so that configuration version can
c be included).
e
s 00001/00001/00684
d D 3.7 83/02/02 12:54:55 eric 7 6
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00035/00003/00650
d D 3.6 83/01/08 13:48:45 eric 6 5
m 
c be sure to open a new transcript on every queue run; when returning
c an SMTP transcript, only send the last half (i.e., that part which
c describes the sending half).
e
s 00001/00008/00652
d D 3.5 83/01/03 13:02:01 eric 5 4
m 
c process timeouts like normal errors, so that they will get delivered to
c the correct address (i.e., the Errors-To: address)
e
s 00002/00002/00658
d D 3.4 82/12/24 08:15:15 eric 4 3
m 108
c Change parse to parseaddr for BB&N TCP/IP implementation; clean up
c comments in daemon.c to simplify the poor alternate protocol type.
e
s 00001/00001/00659
d D 3.3 82/12/13 18:26:43 eric 3 2
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00002/00001/00658
d D 3.2 82/12/09 11:15:37 eric 2 1
m 103
c avoid putting in a full name in network forward operations
e
s 00659/00000/00000
d D 3.1 82/12/05 13:42:10 eric 1 0
m 092
c date and time created 82/12/05 13:42:10 by eric
e
u
U
f b 
f i 
t
T
I 27
/*
I 42
D 159
 * Copyright (c) 1983 Eric P. Allman
E 159
I 159
 * Copyright (c) 1983, 1995 Eric P. Allman
E 159
E 42
D 40
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 40
I 40
D 96
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 96
I 96
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 96
 *
D 49
 * Redistribution and use in source and binary forms are permitted
D 42
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 42
I 42
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 49
I 49
 * %sccs.include.redist.c%
E 49
E 42
 */
E 40

#ifndef lint
D 40
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 40
I 40
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 40

E 27
I 1
D 46
#include <pwd.h>
E 46
I 46
D 77
#include <sys/types.h>
E 77
I 77
#include "sendmail.h"
E 77
E 46
D 16
#include <time.h>
E 16
I 16
D 126
#include <sys/time.h>
E 126
E 16
D 46
#include "sendmail.h"
E 46
D 93
#include <sys/stat.h>
E 93
I 46
D 154
#include <pwd.h>
E 154
I 47
D 65
#include <sys/file.h>
I 64
#include <sys/fcntl.h>
E 65
I 65
D 82
#include <fcntl.h>
E 82
E 65
E 64
E 47
D 77
#include "sendmail.h"
E 77
E 46

D 28
SCCSID(%W%	%Y%	%G%);

E 28
/*
**  NEWENVELOPE -- allocate a new envelope
**
**	Supports inheritance.
**
**	Parameters:
**		e -- the new envelope to fill in.
I 74
**		parent -- the envelope to be the parent of e.
E 74
**
**	Returns:
**		e.
**
**	Side Effects:
**		none.
*/

ENVELOPE *
D 74
newenvelope(e)
E 74
I 74
newenvelope(e, parent)
E 74
	register ENVELOPE *e;
D 74
{
E 74
D 38
	register HDR *bh;
	register HDR **nhp;
E 38
	register ENVELOPE *parent;
I 74
{
E 74
D 163
	extern putheader(), putbody();
I 39
	extern ENVELOPE BlankEnvelope;
E 39
D 38
	extern ENVELOPE BlankEnvelope;
E 38

E 163
D 74
	parent = CurEnv;
D 58
	if (e == CurEnv)
E 58
I 58
	if (e == CurEnv && e->e_parent != NULL)
E 74
I 74
	if (e == parent && e->e_parent != NULL)
E 74
E 58
		parent = e->e_parent;
D 22
	clear((char *) e, sizeof *e);
	bmove((char *) &CurEnv->e_from, (char *) &e->e_from, sizeof e->e_from);
E 22
I 22
D 38
	bzero((char *) e, sizeof *e);
E 38
I 38
D 39
	clearenvelope(e);
E 39
I 39
	clearenvelope(e, TRUE);
E 39
E 38
D 30
	bcopy((char *) &CurEnv->e_from, (char *) &e->e_from, sizeof e->e_from);
E 30
I 30
	if (e == CurEnv)
		bcopy((char *) &NullAddress, (char *) &e->e_from, sizeof e->e_from);
	else
		bcopy((char *) &CurEnv->e_from, (char *) &e->e_from, sizeof e->e_from);
E 30
E 22
	e->e_parent = parent;
	e->e_ctime = curtime();
I 34
D 35
	e->e_msgpriority = parent->e_msgsize + e->e_ctime;
E 35
I 35
D 58
	e->e_msgpriority = parent->e_msgsize;
E 58
I 58
	if (parent != NULL)
		e->e_msgpriority = parent->e_msgsize;
E 58
E 35
E 34
	e->e_puthdr = putheader;
	e->e_putbody = putbody;
D 38
	bh = BlankEnvelope.e_header;
	nhp = &e->e_header;
	while (bh != NULL)
	{
		*nhp = (HDR *) xalloc(sizeof *bh);
D 22
		bmove((char *) bh, (char *) *nhp, sizeof *bh);
E 22
I 22
		bcopy((char *) bh, (char *) *nhp, sizeof *bh);
E 22
		bh = bh->h_link;
		nhp = &(*nhp)->h_link;
	}
E 38
	if (CurEnv->e_xfp != NULL)
		(void) fflush(CurEnv->e_xfp);

	return (e);
}
/*
**  DROPENVELOPE -- deallocate an envelope.
**
**	Parameters:
**		e -- the envelope to deallocate.
**
**	Returns:
**		none.
**
**	Side Effects:
**		housekeeping necessary to dispose of an envelope.
**		Unlocks this queue file.
*/

I 95
void
E 95
dropenvelope(e)
	register ENVELOPE *e;
{
	bool queueit = FALSE;
I 99
D 138
	bool saveit = bitset(EF_FATALERRS, e->e_flags);
E 138
I 138
	bool failure_return = FALSE;
	bool success_return = FALSE;
E 138
E 99
	register ADDRESS *q;
I 66
	char *id = e->e_id;
I 138
D 150
	bool return_no, return_yes;
E 150
E 138
I 97
	char buf[MAXLINE];
E 97
E 66

D 45
#ifdef DEBUG
E 45
	if (tTd(50, 1))
	{
I 152
		extern void printenvflags();

E 152
D 81
		printf("dropenvelope %x id=", e);
E 81
I 81
		printf("dropenvelope %x: id=", e);
E 81
		xputs(e->e_id);
D 81
		printf(" flags=%o\n", e->e_flags);
E 81
I 81
D 121
		printf(", flags=%o\n", e->e_flags);
E 121
I 121
D 152
		printf(", flags=0x%x\n", e->e_flags);
E 152
I 152
		printf(", flags=");
		printenvflags(e);
E 152
E 121
I 97
		if (tTd(50, 10))
		{
			printf("sendq=");
			printaddr(e->e_sendqueue, TRUE);
		}
E 97
E 81
	}
I 66

I 114
D 122
#ifdef XDEBUG
	checkfd012("dropenvelope 1");
#endif

E 122
E 114
I 81
	/* we must have an id to remove disk files */
E 81
	if (id == NULL)
D 81
		id = "(none)";
E 81
I 81
		return;
E 81

E 66
D 45
#endif DEBUG
E 45
#ifdef LOG
I 121
	if (LogLevel > 4 && bitset(EF_LOGSENDER, e->e_flags))
		logsender(e, NULL);
E 121
D 57
	if (LogLevel > 10)
E 57
I 57
D 68
	if (LogLevel > 12)
E 68
I 68
	if (LogLevel > 84)
E 68
E 57
D 121
		syslog(LOG_DEBUG, "dropenvelope, id=%s, flags=%o, pid=%d",
E 121
I 121
		syslog(LOG_DEBUG, "dropenvelope, id=%s, flags=0x%x, pid=%d",
E 121
D 66
				  e->e_id == NULL ? "(none)" : e->e_id,
				  e->e_flags, getpid());
E 66
I 66
				  id, e->e_flags, getpid());
E 66
D 59
#endif LOG
E 59
I 59
#endif /* LOG */
I 121
	e->e_flags &= ~EF_LOGSENDER;
E 121
E 59

I 97
	/* post statistics */
	poststats(StatFile);

E 97
D 81
	/* we must have an id to remove disk files */
	if (e->e_id == NULL)
		return;

E 81
	/*
	**  Extract state information from dregs of send list.
	*/

I 108
	e->e_flags &= ~EF_QUEUERUN;
I 138
D 150
	return_no = return_yes = FALSE;
E 150
E 138
E 108
	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
		if (bitset(QQUEUEUP, q->q_flags))
			queueit = TRUE;
I 99
D 138
		if (!bitset(QDONTSEND, q->q_flags) &&
		    bitset(QBADADDR, q->q_flags))
E 138
I 138

		/* see if a notification is needed */
D 141
		if (bitset(QBADADDR, q->q_flags) &&
E 141
I 141
D 151
		if (e->e_df != NULL &&
		    bitset(QBADADDR, q->q_flags) &&
E 151
I 151
		if (bitset(QBADADDR, q->q_flags) &&
E 151
E 141
		    bitset(QPINGONFAILURE, q->q_flags))
E 138
		{
I 138
			failure_return = TRUE;
E 138
D 139
			if (q->q_owner == NULL &&
			    strcmp(e->e_from.q_paddr, "<>") != 0)
E 139
I 139
			if (q->q_owner == NULL && !emptyaddr(&e->e_from))
E 139
				(void) sendtolist(e->e_from.q_paddr, NULL,
D 143
						  &e->e_errorqueue, e);
E 143
I 143
						  &e->e_errorqueue, 0, e);
E 143
D 100
			saveit = TRUE;
E 100
		}
I 138
D 153
		else if (bitset(QSENT, q->q_flags) &&
		    bitnset(M_LOCALMAILER, q->q_mailer->m_flags) &&
		    bitset(QPINGONSUCCESS, q->q_flags))
E 153
I 153
		else if (bitset(QPINGONSUCCESS, q->q_flags) &&
			 ((bitset(QSENT, q->q_flags) &&
			   bitnset(M_LOCALMAILER, q->q_mailer->m_flags)) ||
D 161
			  bitset(QRELAYED|QEXPLODED, q->q_flags)))
E 161
I 161
			  bitset(QRELAYED|QEXPANDED|QDELIVERED, q->q_flags)))
E 161
E 153
		{
			success_return = TRUE;
D 153
		}
I 140
		else if (bitset(QRELAYED, q->q_flags))
		{
			success_return = TRUE;
		}
E 140
		else
D 150
			continue;

		/* common code for error returns and return receipts */

		/* test for returning the body */
D 140
		if (!bitset(QHASRETPARAM, q->q_flags))
E 140
I 140
D 142
		if (!bitset(QHAS_RET_PARAM, q->q_flags))
E 142
I 142
		if (bitset(QHAS_RET_PARAM, q->q_flags))
E 150
E 142
E 140
		{
D 142
			if (!bitset(EF_NORETURN, e->e_flags))
E 142
I 142
D 150
			if (bitset(QRET_HDRS, q->q_flags))
				return_no = TRUE;
			else
E 142
				return_yes = TRUE;
E 150
I 150
			continue;
E 153
E 150
		}
D 140
		else if (bitset(QNOBODYRETURN, q->q_flags))
E 140
I 140
D 142
		else if (bitset(QRET_HDRS, q->q_flags))
E 140
			return_no = TRUE;
		else
			return_yes = TRUE;
E 142
E 138
E 99
	}
I 138
D 150
	if (return_no && !return_yes)
		e->e_flags |= EF_NORETURN;
E 150
E 138

I 150
	if (e->e_class < 0)
		e->e_flags |= EF_NO_BODY_RETN;

E 150
	/*
I 97
	**  See if the message timed out.
	*/

	if (!queueit)
		/* nothing to do */ ;
D 136
	else if (curtime() > e->e_ctime + TimeOuts.to_q_return)
E 136
I 136
	else if (curtime() > e->e_ctime + TimeOuts.to_q_return[e->e_timeoutclass])
E 136
	{
D 99
		if (!bitset(EF_TIMEOUT, e->e_flags))
		{
			(void) sprintf(buf, "Cannot send message for %s",
				pintvl(TimeOuts.to_q_return, FALSE));
			if (e->e_message != NULL)
				free(e->e_message);
			e->e_message = newstr(buf);
			message(buf);
		}
		e->e_flags |= EF_TIMEOUT|EF_CLRQUEUE;
E 99
I 99
		(void) sprintf(buf, "Cannot send message for %s",
D 136
			pintvl(TimeOuts.to_q_return, FALSE));
E 136
I 136
			pintvl(TimeOuts.to_q_return[e->e_timeoutclass], FALSE));
E 136
		if (e->e_message != NULL)
			free(e->e_message);
		e->e_message = newstr(buf);
		message(buf);
		e->e_flags |= EF_CLRQUEUE;
D 138
		saveit = TRUE;
E 138
I 138
		failure_return = TRUE;
E 138
E 99
D 98
		fprintf(e->e_xfp, "421 Message timed out\n");
E 98
I 98
		fprintf(e->e_xfp, "Message could not be delivered for %s\n",
D 136
			pintvl(TimeOuts.to_q_return, FALSE));
E 136
I 136
			pintvl(TimeOuts.to_q_return[e->e_timeoutclass], FALSE));
E 136
		fprintf(e->e_xfp, "Message will be deleted from queue\n");
		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (bitset(QQUEUEUP, q->q_flags))
I 160
			{
E 160
				q->q_flags |= QBADADDR;
I 160
				q->q_status = "4.4.7";
			}
E 160
		}
E 98
	}
D 136
	else if (TimeOuts.to_q_warning > 0 &&
	    curtime() > e->e_ctime + TimeOuts.to_q_warning)
E 136
I 136
	else if (TimeOuts.to_q_warning[e->e_timeoutclass] > 0 &&
	    curtime() > e->e_ctime + TimeOuts.to_q_warning[e->e_timeoutclass])
E 136
	{
D 140
		if (!bitset(EF_WARNING|EF_RESPONSE, e->e_flags) &&
E 140
I 140
		bool delay_return = FALSE;

		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (bitset(QQUEUEUP, q->q_flags) &&
			    bitset(QPINGONDELAY, q->q_flags))
			{
D 161
				q->q_flags |= QREPORT;
E 161
I 161
				q->q_flags |= QDELAYED;
E 161
				delay_return = TRUE;
			}
		}
		if (delay_return &&
		    !bitset(EF_WARNING|EF_RESPONSE, e->e_flags) &&
E 140
		    e->e_class >= 0 &&
D 135
		    strcmp(e->e_from.q_paddr, "<>") != 0)
E 135
I 135
		    strcmp(e->e_from.q_paddr, "<>") != 0 &&
		    strncasecmp(e->e_from.q_paddr, "owner-", 6) != 0 &&
D 155
		    (strlen(e->e_from.q_paddr) <= 8 ||
E 155
I 155
		    (strlen(e->e_from.q_paddr) <= (SIZE_T) 8 ||
E 155
		     strcasecmp(&e->e_from.q_paddr[strlen(e->e_from.q_paddr) - 8], "-request") != 0))
E 135
		{
			(void) sprintf(buf,
D 131
				"warning: cannot send message for %s",
E 131
I 131
				"Warning: cannot send message for %s",
E 131
D 136
				pintvl(TimeOuts.to_q_warning, FALSE));
E 136
I 136
				pintvl(TimeOuts.to_q_warning[e->e_timeoutclass], FALSE));
E 136
			if (e->e_message != NULL)
				free(e->e_message);
			e->e_message = newstr(buf);
			message(buf);
D 99
			e->e_flags |= EF_WARNING|EF_TIMEOUT;
E 99
I 99
			e->e_flags |= EF_WARNING;
D 138
			saveit = TRUE;
E 138
I 138
			failure_return = TRUE;
E 138
E 99
		}
		fprintf(e->e_xfp,
			"Warning: message still undelivered after %s\n",
D 136
			pintvl(TimeOuts.to_q_warning, FALSE));
E 136
I 136
			pintvl(TimeOuts.to_q_warning[e->e_timeoutclass], FALSE));
E 136
		fprintf(e->e_xfp, "Will keep trying until message is %s old\n",
D 136
			pintvl(TimeOuts.to_q_return, FALSE));
E 136
I 136
			pintvl(TimeOuts.to_q_return[e->e_timeoutclass], FALSE));
E 136
I 98
D 140
		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (bitset(QQUEUEUP, q->q_flags))
				q->q_flags |= QREPORT;
		}
E 140
E 98
	}

I 138
	if (tTd(50, 2))
		printf("failure_return=%d success_return=%d queueit=%d\n",
			failure_return, success_return, queueit);

E 138
	/*
I 145
	**  If we had some fatal error, but no addresses are marked as
	**  bad, mark them _all_ as bad.
	*/

	if (bitset(EF_FATALERRS, e->e_flags) && !failure_return)
	{
		failure_return = TRUE;
		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (!bitset(QDONTSEND, q->q_flags))
				q->q_flags |= QBADADDR;
		}
	}

	/*
E 145
E 97
	**  Send back return receipts as requested.
	*/

I 138
/*
E 138
D 130
	if (e->e_receiptto != NULL && bitset(EF_SENDRECEIPT, e->e_flags))
E 130
I 130
	if (e->e_receiptto != NULL && bitset(EF_SENDRECEIPT, e->e_flags)
	    && !bitset(PRIV_NORECEIPTS, PrivacyFlags))
I 138
*/
	if (e->e_receiptto == NULL)
		e->e_receiptto = e->e_from.q_paddr;
D 142
	if (success_return && strcmp(e->e_receiptto, "<>") != 0)
E 142
I 142
	if (success_return && !failure_return &&
I 144
	    !bitset(PRIV_NORECEIPTS, PrivacyFlags) &&
E 144
	    strcmp(e->e_receiptto, "<>") != 0)
E 142
E 138
E 130
	{
D 10
		auto ADDRESS *rlist;
E 10
I 10
		auto ADDRESS *rlist = NULL;
E 10

I 138
		e->e_flags |= EF_SENDRECEIPT;
E 138
D 3
		sendto(CurEnv->e_receiptto, (ADDRESS *) NULL, &rlist);
E 3
I 3
D 55
		sendtolist(CurEnv->e_receiptto, (ADDRESS *) NULL, &rlist);
E 3
		(void) returntosender("Return receipt", rlist, FALSE);
E 55
I 55
D 70
		sendtolist(e->e_receiptto, (ADDRESS *) NULL, &rlist, e);
E 70
I 70
D 103
		(void) sendtolist(e->e_receiptto, (ADDRESS *) NULL, &rlist, e);
E 103
I 103
D 143
		(void) sendtolist(e->e_receiptto, NULLADDR, &rlist, e);
E 143
I 143
		(void) sendtolist(e->e_receiptto, NULLADDR, &rlist, 0, e);
E 143
E 103
E 70
D 140
		(void) returntosender("Return receipt", rlist, FALSE, e);
E 140
I 140
D 150
		(void) returntosender("Return receipt", rlist, return_yes, e);
E 150
I 150
		(void) returntosender("Return receipt", rlist, FALSE, e);
E 150
E 140
I 118
D 134
		e->e_flags &= ~EF_SENDRECEIPT;
E 134
E 118
E 55
	}
I 134
	e->e_flags &= ~EF_SENDRECEIPT;
E 134

	/*
D 5
	**  See if this message has timed out
	*/

	if (bitset(EF_TIMEOUT, e->e_flags) && queueit)
		timeout(e);

	/*
E 5
	**  Arrange to send error messages if there are fatal errors.
	*/

D 5
	if (bitset(EF_FATALERRS, e->e_flags))
E 5
I 5
D 9
	if (bitset(EF_FATALERRS|EF_TIMEOUT, e->e_flags))
E 9
I 9
D 85
	if (bitset(EF_FATALERRS|EF_TIMEOUT, e->e_flags) && ErrorMode != EM_QUIET)
E 85
I 85
D 99
	if (bitset(EF_FATALERRS|EF_TIMEOUT, e->e_flags) &&
	    e->e_errormode != EM_QUIET)
E 99
I 99
D 138
	if (saveit && e->e_errormode != EM_QUIET)
E 138
I 138
	if (failure_return && e->e_errormode != EM_QUIET)
E 138
E 99
E 85
E 9
E 5
D 142
		savemail(e);
E 142
I 142
D 150
		savemail(e, return_yes || (!return_no && e->e_class >= 0));
E 150
I 150
		savemail(e, !bitset(EF_NO_BODY_RETN, e->e_flags));
E 150
E 142
I 100

I 114
D 122
#ifdef XDEBUG
	checkfd012("dropenvelope 2");
#endif

E 122
E 114
	/*
	**  Arrange to send warning messages to postmaster as requested.
	*/

D 158
	if (bitset(EF_PM_NOTIFY, e->e_flags) && PostMasterCopy != NULL &&
E 158
I 158
	if ((failure_return || bitset(EF_PM_NOTIFY, e->e_flags)) &&
	    PostMasterCopy != NULL &&
E 158
D 105
	    !bitset(EF_RESPONSE, e->e_flags))
E 105
I 105
	    !bitset(EF_RESPONSE, e->e_flags) && e->e_class >= 0)
E 105
	{
		auto ADDRESS *rlist = NULL;

D 103
		(void) sendtolist(PostMasterCopy, (ADDRESS *) NULL, &rlist, e);
E 103
I 103
D 143
		(void) sendtolist(PostMasterCopy, NULLADDR, &rlist, e);
E 143
I 143
		(void) sendtolist(PostMasterCopy, NULLADDR, &rlist, 0, e);
E 143
E 103
		(void) returntosender(e->e_message, rlist, FALSE, e);
	}
E 100

	/*
	**  Instantiate or deinstantiate the queue.
	*/

	if ((!queueit && !bitset(EF_KEEPQUEUE, e->e_flags)) ||
	    bitset(EF_CLRQUEUE, e->e_flags))
	{
I 97
D 104
		if (tTd(50, 2))
			printf("Dropping envelope\n");
E 104
I 104
		if (tTd(50, 1))
D 138
			printf("\n===== Dropping [dq]f%s =====\n\n", e->e_id);
E 138
I 138
D 152
			printf("\n===== Dropping [dq]f%s (queueit=%d, e_flags=%x) =====\n\n",
				e->e_id, queueit, e->e_flags);
E 152
I 152
		{
			extern void printenvflags();

			printf("\n===== Dropping [dq]f%s... queueit=%d, e_flags=",
				e->e_id, queueit);
			printenvflags(e);
		}
E 152
E 138
E 104
E 97
D 30
		if (e->e_dfp != NULL)
			(void) fclose(e->e_dfp);
E 30
I 29
D 151
		if (e->e_df != NULL)
			xunlink(e->e_df);
E 151
I 151
		xunlink(queuename(e, 'd'));
E 151
E 29
D 26
		if (e->e_df != NULL)
			xunlink(e->e_df);
E 26
		xunlink(queuename(e, 'q'));
I 99

#ifdef LOG
		if (LogLevel > 10)
			syslog(LOG_INFO, "%s: done", id);
#endif
E 99
	}
	else if (queueit || !bitset(EF_INQUEUE, e->e_flags))
I 9
	{
#ifdef QUEUE
E 9
D 47
		queueup(e, FALSE, FALSE);
E 47
I 47
D 50
		FILE *lockfp, *queueup();
		lockfp = queueup(e, FALSE, FALSE);
		if (lockfp != NULL)
			(void) fclose(lockfp);
E 50
I 50
D 104
		queueup(e, FALSE, FALSE);
E 104
I 104
		queueup(e, bitset(EF_KEEPQUEUE, e->e_flags), FALSE);
E 104
E 50
E 47
I 9
D 59
#else QUEUE
E 59
I 59
#else /* QUEUE */
E 59
D 72
		syserr("dropenvelope: queueup");
E 72
I 72
		syserr("554 dropenvelope: queueup");
E 72
D 59
#endif QUEUE
E 59
I 59
#endif /* QUEUE */
E 59
	}
E 9

I 114
D 122
#ifdef XDEBUG
	checkfd012("dropenvelope 3");
#endif

E 122
E 114
	/* now unlock the job */
D 6
	if (e->e_xfp != NULL)
		(void) fclose(e->e_xfp);
E 6
I 6
	closexscript(e);
E 6
	unlockqueue(e);

	/* make sure that this envelope is marked unused */
I 26
D 29
	if (e->e_df != NULL)
		xunlink(e->e_df);
E 29
E 26
D 81
	e->e_id = e->e_df = NULL;
E 81
I 30
	if (e->e_dfp != NULL)
D 81
		(void) fclose(e->e_dfp);
E 81
I 81
D 151
		(void) xfclose(e->e_dfp, "dropenvelope", e->e_df);
E 151
I 151
		(void) xfclose(e->e_dfp, "dropenvelope df", e->e_id);
E 151
E 81
E 30
D 6
	e->e_dfp = e->e_xfp = NULL;
E 6
I 6
	e->e_dfp = NULL;
I 81
D 151
	e->e_id = e->e_df = NULL;
E 151
I 151
	e->e_id = NULL;
	e->e_flags &= ~EF_HAS_DF;
E 151
I 106
D 122
#ifdef XDEBUG
D 114
	checkfd012("dropenvelope");
E 114
I 114
	checkfd012("dropenvelope 4");
E 114
#endif
E 122
E 106
E 81
I 62
D 99

#ifdef LOG
D 68
	if (LogLevel >= 10)
E 68
I 68
	if (LogLevel > 74)
E 68
D 66
		syslog(LOG_INFO, "%s: done", e->e_id);
E 66
I 66
		syslog(LOG_INFO, "%s: done", id);
E 66
#endif /* LOG */
E 99
E 62
E 6
}
/*
**  CLEARENVELOPE -- clear an envelope without unlocking
**
**	This is normally used by a child process to get a clean
**	envelope without disturbing the parent.
**
**	Parameters:
**		e -- the envelope to clear.
I 39
**		fullclear - if set, the current envelope is total
**			garbage and should be ignored; otherwise,
**			release any resources it may indicate.
E 39
**
**	Returns:
**		none.
**
**	Side Effects:
**		Closes files associated with the envelope.
**		Marks the envelope as unallocated.
*/

I 95
void
E 95
D 39
clearenvelope(e)
E 39
I 39
clearenvelope(e, fullclear)
E 39
	register ENVELOPE *e;
I 39
	bool fullclear;
E 39
{
I 38
	register HDR *bh;
	register HDR **nhp;
	extern ENVELOPE BlankEnvelope;

E 38
D 39
	/* clear out any file information */
	if (e->e_xfp != NULL)
		(void) fclose(e->e_xfp);
	if (e->e_dfp != NULL)
		(void) fclose(e->e_dfp);
E 39
I 39
	if (!fullclear)
	{
		/* clear out any file information */
		if (e->e_xfp != NULL)
D 81
			(void) fclose(e->e_xfp);
E 81
I 81
			(void) xfclose(e->e_xfp, "clearenvelope xfp", e->e_id);
E 81
		if (e->e_dfp != NULL)
D 81
			(void) fclose(e->e_dfp);
E 81
I 81
D 151
			(void) xfclose(e->e_dfp, "clearenvelope dfp", e->e_df);
E 151
I 151
			(void) xfclose(e->e_dfp, "clearenvelope dfp", e->e_id);
E 151
		e->e_xfp = e->e_dfp = NULL;
E 81
	}
E 39
D 32
	e->e_xfp = e->e_dfp = NULL;
E 32

D 32
	/* now expunge names of objects */
	e->e_df = e->e_id = NULL;

	/* and the flags which are now meaningless */
	e->e_flags = 0;
E 32
I 32
	/* now clear out the data */
D 33
	bzero((char *) e, sizeof *e);
E 33
I 33
	STRUCTCOPY(BlankEnvelope, *e);
I 94
	if (Verbose)
		e->e_sendmode = SM_DELIVER;
E 94
I 38
	bh = BlankEnvelope.e_header;
	nhp = &e->e_header;
	while (bh != NULL)
	{
		*nhp = (HDR *) xalloc(sizeof *bh);
		bcopy((char *) bh, (char *) *nhp, sizeof *bh);
		bh = bh->h_link;
		nhp = &(*nhp)->h_link;
	}
E 38
E 33
E 32
}
/*
D 24
**  UNLOCKQUEUE -- unlock the queue entry for a specified envelope
**
**	Parameters:
**		e -- the envelope to unlock.
**
**	Returns:
**		none
**
**	Side Effects:
**		unlocks the queue for `e'.
*/

unlockqueue(e)
	ENVELOPE *e;
{
	/* remove the transcript */
#ifdef DEBUG
I 6
# ifdef LOG
	if (LogLevel > 19)
		syslog(LOG_DEBUG, "%s: unlock", e->e_id);
# endif LOG
E 6
	if (!tTd(51, 4))
#endif DEBUG
		xunlink(queuename(e, 'x'));

I 9
# ifdef QUEUE
E 9
	/* last but not least, remove the lock */
	xunlink(queuename(e, 'l'));
I 9
# endif QUEUE
E 9
}
/*
E 24
**  INITSYS -- initialize instantiation of system
**
**	In Daemon mode, this is done in the child.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Initializes the system macros, some global variables,
**		etc.  In particular, the current time in various
**		forms is set.
*/

I 95
void
E 95
D 55
initsys()
E 55
I 55
initsys(e)
	register ENVELOPE *e;
E 55
{
D 15
	auto time_t now;
E 15
D 110
	static char cbuf[5];			/* holds hop count */
D 15
	static char dbuf[30];			/* holds ctime(tbuf) */
E 15
	static char pbuf[10];			/* holds pid */
E 110
I 110
	char cbuf[5];				/* holds hop count */
	char pbuf[10];				/* holds pid */
E 110
I 28
#ifdef TTYNAME
E 28
D 15
	static char tbuf[20];			/* holds "current" time */
E 15
D 92
	static char ybuf[10];			/* holds tty id */
E 92
I 92
	static char ybuf[60];			/* holds tty id */
E 92
	register char *p;
I 28
D 59
#endif TTYNAME
E 59
I 59
#endif /* TTYNAME */
E 59
E 28
D 15
	register struct tm *tm;
E 15
	extern char *ttyname();
D 15
	extern char *arpadate();
	extern struct tm *gmtime();
E 15
D 95
	extern char *macvalue();
E 95
I 95
	extern void settime();
E 95
D 163
	extern char Version[];
E 163

	/*
	**  Give this envelope a reality.
	**	I.e., an id, a transcript, and a creation time.
	*/

D 55
	openxscript(CurEnv);
	CurEnv->e_ctime = curtime();
E 55
I 55
	openxscript(e);
	e->e_ctime = curtime();
E 55

	/*
	**  Set OutChannel to something useful if stdout isn't it.
	**	This arranges that any extra stuff the mailer produces
	**	gets sent back to the user on error (because it is
	**	tucked away in the transcript).
	*/

D 69
	if (OpMode == MD_DAEMON && QueueRun)
E 69
I 69
D 86
	if (OpMode == MD_DAEMON && QueueRun && e->e_xfp != NULL)
E 86
I 86
D 109
	if (OpMode == MD_DAEMON && !bitset(EF_QUEUERUN, e->e_flags) &&
E 109
I 109
	if (OpMode == MD_DAEMON && bitset(EF_QUEUERUN, e->e_flags) &&
E 109
	    e->e_xfp != NULL)
E 86
E 69
D 55
		OutChannel = CurEnv->e_xfp;
E 55
I 55
		OutChannel = e->e_xfp;
E 55

	/*
	**  Set up some basic system macros.
	*/

	/* process id */
	(void) sprintf(pbuf, "%d", getpid());
D 55
	define('p', pbuf, CurEnv);
E 55
I 55
D 110
	define('p', pbuf, e);
E 110
I 110
	define('p', newstr(pbuf), e);
E 110
E 55

	/* hop count */
D 55
	(void) sprintf(cbuf, "%d", CurEnv->e_hopcount);
	define('c', cbuf, CurEnv);
E 55
I 55
	(void) sprintf(cbuf, "%d", e->e_hopcount);
D 110
	define('c', cbuf, e);
E 110
I 110
	define('c', newstr(cbuf), e);
E 110
E 55

	/* time as integer, unix time, arpa time */
D 15
	now = curtime();
	tm = gmtime(&now);
D 8
	(void) sprintf(tbuf, "%02d%02d%02d%02d%02d", tm->tm_year, tm->tm_mon,
E 8
I 8
	(void) sprintf(tbuf, "%02d%02d%02d%02d%02d", tm->tm_year, tm->tm_mon+1,
E 8
			tm->tm_mday, tm->tm_hour, tm->tm_min);
	define('t', tbuf, CurEnv);
	(void) strcpy(dbuf, ctime(&now));
	*index(dbuf, '\n') = '\0';
	if (macvalue('d', CurEnv) == NULL)
		define('d', dbuf, CurEnv);
	p = newstr(arpadate(dbuf));
	if (macvalue('a', CurEnv) == NULL)
		define('a', p, CurEnv);
	define('b', p, CurEnv);
E 15
I 15
D 55
	settime();
E 55
I 55
	settime(e);
E 55
E 15
D 8

	/* version */
	define('v', Version, CurEnv);
E 8

I 24
#ifdef TTYNAME
E 24
	/* tty name */
D 55
	if (macvalue('y', CurEnv) == NULL)
E 55
I 55
	if (macvalue('y', e) == NULL)
E 55
	{
		p = ttyname(2);
		if (p != NULL)
		{
D 59
			if (rindex(p, '/') != NULL)
				p = rindex(p, '/') + 1;
E 59
I 59
			if (strrchr(p, '/') != NULL)
				p = strrchr(p, '/') + 1;
E 59
			(void) strcpy(ybuf, p);
D 55
			define('y', ybuf, CurEnv);
E 55
I 55
			define('y', ybuf, e);
E 55
		}
	}
I 24
D 59
#endif TTYNAME
E 59
I 59
#endif /* TTYNAME */
E 59
E 24
}
/*
I 15
**  SETTIME -- set the current time.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets the various time macros -- $a, $b, $d, $t.
*/

I 95
void
E 95
D 55
settime()
E 55
I 55
settime(e)
	register ENVELOPE *e;
E 55
{
	register char *p;
	auto time_t now;
D 110
	static char tbuf[20];			/* holds "current" time */
	static char dbuf[30];			/* holds ctime(tbuf) */
E 110
I 110
	char tbuf[20];				/* holds "current" time */
	char dbuf[30];				/* holds ctime(tbuf) */
E 110
	register struct tm *tm;
	extern char *arpadate();
	extern struct tm *gmtime();
D 95
	extern char *macvalue();
E 95

	now = curtime();
	tm = gmtime(&now);
D 60
	(void) sprintf(tbuf, "%02d%02d%02d%02d%02d", tm->tm_year, tm->tm_mon+1,
			tm->tm_mday, tm->tm_hour, tm->tm_min);
E 60
I 60
	(void) sprintf(tbuf, "%04d%02d%02d%02d%02d", tm->tm_year + 1900,
			tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min);
E 60
D 55
	define('t', tbuf, CurEnv);
E 55
I 55
D 110
	define('t', tbuf, e);
E 110
I 110
	define('t', newstr(tbuf), e);
E 110
E 55
	(void) strcpy(dbuf, ctime(&now));
D 59
	*index(dbuf, '\n') = '\0';
E 59
I 59
D 71
	*strchr(dbuf, '\n') = '\0';
E 59
D 55
	if (macvalue('d', CurEnv) == NULL)
		define('d', dbuf, CurEnv);
E 55
I 55
	if (macvalue('d', e) == NULL)
		define('d', dbuf, e);
E 71
I 71
	p = strchr(dbuf, '\n');
	if (p != NULL)
		*p = '\0';
D 110
	define('d', dbuf, e);
E 110
I 110
	define('d', newstr(dbuf), e);
E 110
E 71
E 55
D 101
	p = newstr(arpadate(dbuf));
E 101
I 101
	p = arpadate(dbuf);
	p = newstr(p);
E 101
D 55
	if (macvalue('a', CurEnv) == NULL)
		define('a', p, CurEnv);
	define('b', p, CurEnv);
E 55
I 55
	if (macvalue('a', e) == NULL)
		define('a', p, e);
	define('b', p, e);
E 55
}
/*
E 15
D 24
**  QUEUENAME -- build a file name in the queue directory for this envelope.
**
**	Assigns an id code if one does not already exist.
**	This code is very careful to avoid trashing existing files
**	under any circumstances.
**		We first create an nf file that is only used when
**		assigning an id.  This file is always empty, so that
**		we can never accidently truncate an lf file.
**
**	Parameters:
**		e -- envelope to build it in/from.
**		type -- the file type, used as the first character
**			of the file name.
**
**	Returns:
**		a pointer to the new file name (in a static buffer).
**
**	Side Effects:
**		Will create the lf and qf files if no id code is
**		already assigned.  This will cause the envelope
**		to be modified.
*/

char *
queuename(e, type)
	register ENVELOPE *e;
	char type;
{
	static char buf[MAXNAME];
	static int pid = -1;
	char c1 = 'A';
	char c2 = 'A';

	if (e->e_id == NULL)
	{
		char qf[20];
		char lf[20];
		char nf[20];

		/* find a unique id */
		if (pid != getpid())
		{
			/* new process -- start back at "AA" */
			pid = getpid();
			c1 = 'A';
			c2 = 'A' - 1;
		}
		(void) sprintf(qf, "qfAA%05d", pid);
		strcpy(lf, qf);
		lf[0] = 'l';
		strcpy(nf, qf);
		nf[0] = 'n';

		while (c1 < '~' || c2 < 'Z')
		{
			int i;

			if (c2 >= 'Z')
			{
				c1++;
				c2 = 'A' - 1;
			}
			qf[2] = lf[2] = nf[2] = c1;
			qf[3] = lf[3] = nf[3] = ++c2;
# ifdef DEBUG
			if (tTd(7, 20))
				printf("queuename: trying \"%s\"\n", nf);
# endif DEBUG
I 9
# ifdef QUEUE
E 9
			if (access(lf, 0) >= 0 || access(qf, 0) >= 0)
				continue;
			errno = 0;
			i = creat(nf, FileMode);
			if (i < 0)
			{
				(void) unlink(nf);	/* kernel bug */
				continue;
			}
			(void) close(i);
			i = link(nf, lf);
			(void) unlink(nf);
			if (i < 0)
				continue;
			if (link(lf, qf) >= 0)
				break;
			(void) unlink(lf);
I 9
# else QUEUE
			if (close(creat(qf, FileMode)) < 0)
				continue;
# endif QUEUE
E 9
		}
		if (c1 >= '~' && c2 >= 'Z')
		{
			syserr("queuename: Cannot create \"%s\" in \"%s\"",
				lf, QueueDir);
			exit(EX_OSERR);
		}
		e->e_id = newstr(&qf[2]);
		define('i', e->e_id, e);
# ifdef DEBUG
		if (tTd(7, 1))
			printf("queuename: assigned id %s, env=%x\n", e->e_id, e);
I 6
# ifdef LOG
		if (LogLevel > 16)
			syslog(LOG_DEBUG, "%s: assigned id", e->e_id);
# endif LOG
E 6
# endif DEBUG
	}

	if (type == '\0')
		return (NULL);
	(void) sprintf(buf, "%cf%s", type, e->e_id);
# ifdef DEBUG
	if (tTd(7, 2))
		printf("queuename: %s\n", buf);
# endif DEBUG
	return (buf);
}
/*
E 24
**  OPENXSCRIPT -- Open transcript file
**
**	Creates a transcript file for possible eventual mailing or
**	sending back.
**
**	Parameters:
**		e -- the envelope to create the transcript in/for.
**
**	Returns:
**		none
**
**	Side Effects:
**		Creates the transcript file.
*/

I 87
#ifndef O_APPEND
#define O_APPEND	0
#endif

I 95
void
E 95
E 87
openxscript(e)
	register ENVELOPE *e;
{
	register char *p;
I 47
	int fd;
E 47

I 6
D 67
# ifdef LOG
	if (LogLevel > 19)
		syslog(LOG_DEBUG, "%s: openx%s", e->e_id, e->e_xfp == NULL ? "" : " (no)");
D 59
# endif LOG
E 59
I 59
# endif /* LOG */
E 67
E 59
E 6
	if (e->e_xfp != NULL)
		return;
	p = queuename(e, 'x');
D 47
	e->e_xfp = fopen(p, "w");
	if (e->e_xfp == NULL)
E 47
I 47
D 87
	fd = open(p, O_WRONLY|O_CREAT, 0644);
E 87
I 87
	fd = open(p, O_WRONLY|O_CREAT|O_APPEND, 0644);
E 87
	if (fd < 0)
E 47
D 97
		syserr("Can't create %s", p);
	else
D 47
		(void) chmod(p, 0644);
E 47
I 47
		e->e_xfp = fdopen(fd, "w");
E 97
I 97
	{
		syserr("Can't create transcript file %s", p);
		fd = open("/dev/null", O_WRONLY, 0644);
		if (fd < 0)
			syserr("!Can't open /dev/null");
	}
D 146
D 147
	e->e_xfp = fdopen(fd, "w");
E 147
I 147
	e->e_xfp = fdopen(fd, "a");
E 147
E 146
I 146
	e->e_xfp = fdopen(fd, "a");
E 146
I 107
	if (e->e_xfp == NULL)
D 148
	{
E 148
		syserr("!Can't create transcript stream %s", p);
I 108
D 148
	}
E 148
I 148
#ifdef HASSETVBUF
	setvbuf(e->e_xfp, NULL, _IOLBF, 0);
#else
	setlinebuf(e->e_xfp);
#endif
E 148
	if (tTd(46, 9))
	{
		printf("openxscript(%s):\n  ", p);
		dumpfd(fileno(e->e_xfp), TRUE, FALSE);
E 108
	}
E 107
E 97
E 47
I 6
}
/*
**  CLOSEXSCRIPT -- close the transcript file.
**
**	Parameters:
**		e -- the envelope containing the transcript to close.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

I 95
void
E 95
closexscript(e)
	register ENVELOPE *e;
{
	if (e->e_xfp == NULL)
		return;
D 81
	(void) fclose(e->e_xfp);
E 81
I 81
	(void) xfclose(e->e_xfp, "closexscript", e->e_id);
E 81
	e->e_xfp = NULL;
E 6
}
/*
**  SETSENDER -- set the person who this message is from
**
**	Under certain circumstances allow the user to say who
**	s/he is (using -f or -r).  These are:
**	1.  The user's uid is zero (root).
**	2.  The user's login name is in an approved list (typically
**	    from a network server).
**	3.  The address the user is trying to claim has a
**	    "!" character in it (since #2 doesn't do it for
**	    us if we are dialing out for UUCP).
**	A better check to replace #3 would be if the
**	effective uid is "UUCP" -- this would require me
**	to rewrite getpwent to "grab" uucp as it went by,
**	make getname more nasty, do another passwd file
**	scan, or compile the UID of "UUCP" into the code,
**	all of which are reprehensible.
**
**	Assuming all of these fail, we figure out something
**	ourselves.
**
**	Parameters:
**		from -- the person we would like to believe this message
**			is from, as specified on the command line.
I 53
**		e -- the envelope in which we would like the sender set.
I 78
**		delimptr -- if non-NULL, set to the location of the
**			trailing delimiter.
I 83
**		internal -- set if this address is coming from an internal
**			source such as an owner alias.
E 83
E 78
E 53
**
**	Returns:
D 78
**		none.
E 78
I 78
D 83
**		pointer to the delimiter terminating the from address.
E 83
I 83
**		none.
E 83
E 78
**
**	Side Effects:
**		sets sendmail's notion of who the from person is.
*/

I 95
void
E 95
D 53
setsender(from)
E 53
I 53
D 78
setsender(from, e)
E 78
I 78
D 83
char *
setsender(from, e, delimptr)
E 83
I 83
setsender(from, e, delimptr, internal)
E 83
E 78
E 53
	char *from;
I 53
	register ENVELOPE *e;
I 78
	char **delimptr;
I 83
	bool internal;
E 83
E 78
E 53
{
	register char **pvp;
D 24
	register struct passwd *pw = NULL;
E 24
	char *realname = NULL;
I 25
	register struct passwd *pw;
I 78
D 84
	char *delimchar = NULL;
E 84
I 84
	char delimchar;
E 84
E 78
E 25
D 102
	char buf[MAXNAME];
E 102
I 102
	char *bp;
	char buf[MAXNAME + 2];
E 102
I 23
	char pvpbuf[PSBUFSIZE];
I 25
D 154
	extern struct passwd *getpwnam();
E 154
E 25
E 23
D 95
	extern char *macvalue();
	extern char **prescan();
E 95
D 75
	extern bool safefile();
E 75
	extern char *FullName;

D 45
# ifdef DEBUG
E 45
	if (tTd(45, 1))
D 18
		printf("setsender(%s)\n", from);
E 18
I 18
		printf("setsender(%s)\n", from == NULL ? "" : from);
E 18
D 45
# endif DEBUG
E 45

	/*
	**  Figure out the real user executing us.
	**	Username can return errno != 0 on non-errors.
	*/

D 52
	if (QueueRun || OpMode == MD_SMTP || OpMode == MD_ARPAFTP)
E 52
I 52
D 86
	if (QueueRun || OpMode == MD_SMTP)
E 86
I 86
D 123
	if (bitset(EF_QUEUERUN, e->e_flags) || OpMode == MD_SMTP)
E 123
I 123
	if (bitset(EF_QUEUERUN, e->e_flags) || OpMode == MD_SMTP ||
D 127
	    OpMode == MD_DAEMON)
E 127
I 127
	    OpMode == MD_ARPAFTP || OpMode == MD_DAEMON)
E 127
E 123
E 86
E 52
		realname = from;
	if (realname == NULL || realname[0] == '\0')
D 95
	{
		extern char *username();

E 95
		realname = username();
D 24
		errno = 0;
E 24
D 95
	}
E 95
D 24
	if (realname == NULL || realname[0] == '\0')
	{
		extern struct passwd *getpwuid();
E 24

D 24
		pw = getpwuid(getruid());
		if (pw != NULL)
			realname = pw->pw_name;
	}
	if (realname == NULL || realname[0] == '\0')
	{
		syserr("Who are you?");
		realname = "root";
	}

E 24
D 73
	/*
	**  Determine if this real person is allowed to alias themselves.
	*/

	if (from != NULL)
	{
		extern bool trusteduser();

D 43
		if (!trusteduser(realname) &&
# ifdef DEBUG
		    (!tTd(1, 9) || getuid() != geteuid()) &&
# endif DEBUG
E 43
I 43
		if (!trusteduser(realname) && getuid() != geteuid() &&
E 43
D 59
		    index(from, '!') == NULL && getuid() != 0)
E 59
I 59
		    strchr(from, '!') == NULL && getuid() != 0)
E 59
		{
			/* network sends -r regardless (why why why?) */
D 72
			/* syserr("%s, you cannot use the -f flag", realname); */
E 72
I 72
			/* syserr("501 %s, you cannot use the -f flag", realname); */
E 72
			from = NULL;
		}
I 13
D 24
		else if (strcmp(from, realname) != 0)
			pw = NULL;
E 24
E 13
	}

E 73
I 62
D 90
/*
E 62
	SuprErrs = TRUE;
I 62
*/
E 90
I 90
	if (ConfigLevel < 2)
		SuprErrs = TRUE;

E 90
I 84
	delimchar = internal ? '\0' : ' ';
I 111
	e->e_from.q_flags = QBADADDR;
E 111
E 84
E 62
D 4
	if (from == NULL || parse(from, &CurEnv->e_from, 1) == NULL)
E 4
I 4
D 12
	if (from == NULL || parseaddr(from, &CurEnv->e_from, 1) == NULL)
E 12
I 12
D 53
	if (from == NULL || parseaddr(from, &CurEnv->e_from, 1, '\0') == NULL)
E 53
I 53
D 55
	if (from == NULL || parseaddr(from, &e->e_from, 1, '\0') == NULL)
E 55
I 55
D 76
	if (from == NULL || parseaddr(from, &e->e_from, 1, '\0', e) == NULL)
E 76
I 76
D 78
	if (from == NULL || parseaddr(from, &e->e_from, 1, ' ', e) == NULL)
E 78
I 78
	if (from == NULL ||
D 84
	    parseaddr(from, &e->e_from, 1, ' ', delimptr, e) == NULL)
E 84
I 84
D 103
	    parseaddr(from, &e->e_from, 1, delimchar, delimptr, e) == NULL)
E 103
I 103
	    parseaddr(from, &e->e_from, RF_COPYALL|RF_SENDERADDR,
D 111
		      delimchar, delimptr, e) == NULL)
E 111
I 111
		      delimchar, delimptr, e) == NULL ||
	    bitset(QBADADDR, e->e_from.q_flags) ||
	    e->e_from.q_mailer == ProgMailer ||
	    e->e_from.q_mailer == FileMailer ||
	    e->e_from.q_mailer == InclMailer)
E 111
E 103
E 84
E 78
E 76
E 55
E 53
E 12
E 4
	{
I 26
		/* log garbage addresses for traceback */
D 56
		if (from != NULL)
		{
E 56
D 30
			syslog(LOG_ERR, "Unparseable user %s wants to be %s",
					realname, from);
E 30
I 30
# ifdef LOG
D 56
			if (LogLevel >= 1)
D 43
				syslog(LOG_ERR, "Unparseable user %s wants to be %s",
						realname, from);
E 43
I 43
			    if (realname == from && RealHostName != NULL)
				syslog(LOG_NOTICE,
				    "from=%s unparseable, received from %s",
				    from, RealHostName);
			    else
				syslog(LOG_NOTICE,
				    "Unparseable username %s wants from=%s",
				    realname, from);
E 43
# endif LOG
E 56
I 56
D 68
		if (from != NULL && LogLevel >= 1)
E 68
I 68
		if (from != NULL && LogLevel > 2)
E 68
		{
D 89
			char *host = RealHostName;
E 89
I 89
			char *p;
			char ebuf[MAXNAME * 2 + 2];
E 89

D 89
			if (host == NULL)
				host = MyHostName;
E 89
I 89
			p = macvalue('_', e);
			if (p == NULL)
			{
				char *host = RealHostName;
				if (host == NULL)
					host = MyHostName;
				(void) sprintf(ebuf, "%s@%s", realname, host);
				p = ebuf;
			}
E 89
			syslog(LOG_NOTICE,
D 89
				"from=%s unparseable, received from %s@%s",
				from, realname, host);
E 89
I 89
D 111
				"from=%s unparseable, received from %s",
E 111
I 111
				"setsender: %s: invalid or unparseable, received from %s",
E 111
D 116
				from, p);
E 116
I 116
				shortenstring(from, 83), p);
E 116
E 89
E 56
E 30
		}
I 56
D 59
# endif LOG
E 59
I 59
# endif /* LOG */
E 59
E 56
E 26
D 62
		from = newstr(realname);
D 4
		(void) parse(from, &CurEnv->e_from, 1);
E 4
I 4
D 12
		(void) parseaddr(from, &CurEnv->e_from, 1);
E 12
I 12
D 30
		(void) parseaddr(from, &CurEnv->e_from, 1, '\0');
E 30
I 30
D 53
		if (parseaddr(from, &CurEnv->e_from, 1, '\0') == NULL &&
		    parseaddr("postmaster", &CurEnv->e_from, 1, '\0') == NULL)
E 53
I 53
D 55
		if (parseaddr(from, &e->e_from, 1, '\0') == NULL &&
		    parseaddr("postmaster", &e->e_from, 1, '\0') == NULL)
E 55
I 55
		if (parseaddr(from, &e->e_from, 1, '\0', e) == NULL &&
		    parseaddr("postmaster", &e->e_from, 1, '\0', e) == NULL)
E 62
I 62
		if (from != NULL)
I 111
		{
			if (!bitset(QBADADDR, e->e_from.q_flags))
			{
				/* it was a bogus mailer in the from addr */
I 160
				e->e_status = "5.1.7";
E 160
				usrerr("553 Invalid sender address");
			}
E 111
			SuprErrs = TRUE;
I 111
		}
E 111
		if (from == realname ||
D 76
		    parseaddr(from = newstr(realname), &e->e_from, 1, '\0', e) == NULL)
E 76
I 76
D 78
		    parseaddr(from = newstr(realname), &e->e_from, 1, ' ', e) == NULL)
E 78
I 78
D 103
		    parseaddr(from = newstr(realname), &e->e_from, 1, ' ', NULL, e) == NULL)
E 103
I 103
		    parseaddr(from = newstr(realname), &e->e_from,
			      RF_COPYALL|RF_SENDERADDR, ' ', NULL, e) == NULL)
E 103
E 78
E 76
E 62
E 55
E 53
		{
I 111
			char nbuf[100];

E 111
D 62
			syserr("setsender: can't even parse postmaster!");
E 62
I 62
			SuprErrs = TRUE;
D 76
			if (parseaddr("postmaster", &e->e_from, 1, '\0', e) == NULL)
E 76
I 76
D 78
			if (parseaddr("postmaster", &e->e_from, 1, ' ', e) == NULL)
E 78
I 78
D 103
			if (parseaddr("postmaster", &e->e_from, 1, ' ', NULL, e) == NULL)
E 103
I 103
D 111
			if (parseaddr("postmaster", &e->e_from, RF_COPYALL,
				      ' ', NULL, e) == NULL)
E 111
I 111
D 112
			expand("\201n", buf, &buf[sizeof buf], e);
E 112
I 112
D 149
			expand("\201n", nbuf, &nbuf[sizeof nbuf], e);
E 149
I 149
			expand("\201n", nbuf, sizeof nbuf, e);
E 149
E 112
			if (parseaddr(from = newstr(nbuf), &e->e_from,
				      RF_COPYALL, ' ', NULL, e) == NULL &&
			    parseaddr(from = "postmaster", &e->e_from,
			    	      RF_COPYALL, ' ', NULL, e) == NULL)
E 111
E 103
E 78
E 76
D 72
				syserr("setsender: can't even parse postmaster!");
E 72
I 72
				syserr("553 setsender: can't even parse postmaster!");
E 72
E 62
		}
E 30
E 12
E 4
	}
	else
		FromFlag = TRUE;
D 53
	CurEnv->e_from.q_flags |= QDONTSEND;
I 20
	loweraddr(&CurEnv->e_from);
E 53
I 53
	e->e_from.q_flags |= QDONTSEND;
I 63
	if (tTd(45, 5))
	{
		printf("setsender: QDONTSEND ");
		printaddr(&e->e_from, FALSE);
	}
E 63
D 80
	loweraddr(&e->e_from);
E 80
E 53
E 20
	SuprErrs = FALSE;

D 24
	if (pw == NULL && CurEnv->e_from.q_mailer == LocalMailer)
E 24
I 24
D 25
	if (CurEnv->e_from.q_mailer == LocalMailer)
E 25
I 25
D 53
	if (CurEnv->e_from.q_mailer == LocalMailer &&
	    (pw = getpwnam(CurEnv->e_from.q_user)) != NULL)
E 53
I 53
D 54
	if (e->e_from.q_mailer == LocalMailer &&
	    (pw = getpwnam(e->e_from.q_user)) != NULL)
E 54
I 54
D 137
	pvp = NULL;
E 137
I 137
D 162
# ifdef USERDB
E 162
I 162
# if USERDB
E 162
E 137
D 132
	if (e->e_from.q_mailer == LocalMailer)
E 132
I 132
	if (bitnset(M_CHECKUDB, e->e_from.q_mailer->m_flags))
E 132
E 54
E 53
E 25
E 24
	{
I 24
D 25
		register struct passwd *pw;
E 24
		extern struct passwd *getpwnam();

E 25
I 24
D 54
		/*
		**  Process passwd file entry.
		*/
E 54
I 54
D 137
# ifdef USERDB
E 137
		register char *p;
		extern char *udbsender();
D 137
# endif
E 137
E 54

I 137
		p = udbsender(e->e_from.q_user);
		if (p != NULL)
			from = p;
	}
# endif /* USERDB */

	if (bitnset(M_HASPWENT, e->e_from.q_mailer->m_flags))
	{
E 137
E 24
D 25
		pw = getpwnam(CurEnv->e_from.q_user);
E 25
D 24
	}
E 24
D 54

D 24
	/*
	**  Process passwd file entry.
	*/

	if (pw != NULL)
	{
E 24
		/* extract home directory */
D 53
		CurEnv->e_from.q_home = newstr(pw->pw_dir);
I 21
		define('z', CurEnv->e_from.q_home, CurEnv);
E 53
I 53
		e->e_from.q_home = newstr(pw->pw_dir);
		define('z', e->e_from.q_home, e);
E 53
E 21

I 14
		/* extract user and group id */
D 53
		CurEnv->e_from.q_uid = pw->pw_uid;
		CurEnv->e_from.q_gid = pw->pw_gid;
E 53
I 53
		e->e_from.q_uid = pw->pw_uid;
		e->e_from.q_gid = pw->pw_gid;
E 53
D 21

E 14
		/* run user's .mailcf file */
		define('z', CurEnv->e_from.q_home, CurEnv);
D 19
		expand("$z/.mailcf", buf, &buf[sizeof buf - 1], CurEnv);
E 19
I 19
		expand("\001z/.mailcf", buf, &buf[sizeof buf - 1], CurEnv);
E 19
		if (safefile(buf, getruid(), S_IREAD))
			readcf(buf, FALSE);
E 21

E 54
D 83
		/* if the user has given fullname already, don't redefine */
		if (FullName == NULL)
D 53
			FullName = macvalue('x', CurEnv);
E 53
I 53
			FullName = macvalue('x', e);
E 53
D 15
		if (FullName[0] == '\0')
E 15
I 15
		if (FullName != NULL && FullName[0] == '\0')
E 15
			FullName = NULL;
E 83
I 83
		if (!internal)
		{
D 137
			/* if the user has given fullname already, don't redefine */
E 137
I 137
			/* if the user already given fullname don't redefine */
E 137
			if (FullName == NULL)
				FullName = macvalue('x', e);
			if (FullName != NULL && FullName[0] == '\0')
				FullName = NULL;
E 83
D 137

D 54
		/* extract full name from passwd file */
D 2
		if (FullName == NULL && pw->pw_gecos != NULL)
E 2
I 2
		if (FullName == NULL && pw->pw_gecos != NULL &&
D 53
		    strcmp(pw->pw_name, CurEnv->e_from.q_user) == 0)
E 53
I 53
		    strcmp(pw->pw_name, e->e_from.q_user) == 0)
E 54
I 54
# ifdef USERDB
D 83
		p = udbsender(from);
E 83
I 83
D 103
			p = udbsender(from);
E 103
I 103
			p = udbsender(e->e_from.q_user);
E 103
E 83

D 83
		if (p != NULL)
E 54
E 53
E 2
		{
D 53
			buildfname(pw->pw_gecos, CurEnv->e_from.q_user, buf);
E 53
I 53
D 54
			buildfname(pw->pw_gecos, e->e_from.q_user, buf);
E 53
			if (buf[0] != '\0')
				FullName = newstr(buf);
E 54
I 54
			/*
			**  We have an alternate address for the sender
			*/
E 83
I 83
			if (p != NULL)
			{
				/*
				**  We have an alternate address for the sender
				*/
E 83

D 78
			pvp = prescan(p, '\0', pvpbuf);
E 78
I 78
D 83
			pvp = prescan(p, '\0', pvpbuf, NULL);
E 78
E 54
		}
E 83
I 83
D 119
				pvp = prescan(p, '\0', pvpbuf, NULL);
E 119
I 119
				pvp = prescan(p, '\0', pvpbuf, sizeof pvpbuf, NULL);
E 119
			}
E 83
I 54
# endif /* USERDB */
E 137
I 83
		}
E 83

D 154
		if ((pw = getpwnam(e->e_from.q_user)) != NULL)
E 154
I 154
		if ((pw = sm_getpwnam(e->e_from.q_user)) != NULL)
E 154
		{
			/*
			**  Process passwd file entry.
			*/

D 125

E 125
			/* extract home directory */
D 125
			e->e_from.q_home = newstr(pw->pw_dir);
E 125
I 125
			if (strcmp(pw->pw_dir, "/") == 0)
				e->e_from.q_home = newstr("");
			else
				e->e_from.q_home = newstr(pw->pw_dir);
E 125
			define('z', e->e_from.q_home, e);

			/* extract user and group id */
			e->e_from.q_uid = pw->pw_uid;
			e->e_from.q_gid = pw->pw_gid;
I 117
			e->e_from.q_flags |= QGOODUID;
E 117

			/* extract full name from passwd file */
			if (FullName == NULL && pw->pw_gecos != NULL &&
D 83
			    strcmp(pw->pw_name, e->e_from.q_user) == 0)
E 83
I 83
			    strcmp(pw->pw_name, e->e_from.q_user) == 0 &&
			    !internal)
E 83
			{
D 115
				buildfname(pw->pw_gecos, e->e_from.q_user, buf);
E 115
I 115
				if (buildfname(pw->pw_gecos, e->e_from.q_user, buf) &&
					hvalue("MIME-Version", e) == NULL)
						addheader("MIME-Version", "1.0", e);
E 115
				if (buf[0] != '\0')
					FullName = newstr(buf);
			}
		}
E 54
D 83
		if (FullName != NULL)
E 83
I 83
		if (FullName != NULL && !internal)
E 83
D 53
			define('x', FullName, CurEnv);
E 53
I 53
			define('x', FullName, e);
E 53
	}
D 14

E 14
I 14
D 83
	else
E 83
I 83
D 123
	else if (!internal)
E 123
I 123
	else if (!internal && OpMode != MD_DAEMON)
E 123
E 83
	{
E 14
D 41
#ifndef V6
E 41
D 14
	if (CurEnv->e_from.q_home == NULL)
		CurEnv->e_from.q_home = getenv("HOME");
E 14
I 14
D 53
		if (CurEnv->e_from.q_home == NULL)
			CurEnv->e_from.q_home = getenv("HOME");
E 14
D 41
#endif V6
E 41
D 14
	CurEnv->e_from.q_uid = getuid();
	CurEnv->e_from.q_gid = getgid();
E 14
I 14
		CurEnv->e_from.q_uid = getuid();
		CurEnv->e_from.q_gid = getgid();
E 53
I 53
		if (e->e_from.q_home == NULL)
I 125
		{
E 125
			e->e_from.q_home = getenv("HOME");
I 128
D 129
			if (e->e_from.q_home == NULL)
				e->e_from.q_home = "";
E 128
I 125
			if (strcmp(e->e_from.q_home, "/") == 0)
E 129
I 129
			if (e->e_from.q_home != NULL &&
			    strcmp(e->e_from.q_home, "/") == 0)
E 129
				e->e_from.q_home++;
		}
E 125
D 98
		e->e_from.q_uid = getuid();
		e->e_from.q_gid = getgid();
E 98
I 98
		e->e_from.q_uid = RealUid;
		e->e_from.q_gid = RealGid;
I 117
		e->e_from.q_flags |= QGOODUID;
E 117
E 98
E 53
	}

E 14
D 48
	if (CurEnv->e_from.q_uid != 0)
	{
		DefUid = CurEnv->e_from.q_uid;
		DefGid = CurEnv->e_from.q_gid;
	}

E 48
	/*
	**  Rewrite the from person to dispose of possible implicit
	**	links in the net.
	*/

I 137
D 156
	pvp = prescan(from, delimchar, pvpbuf, sizeof pvpbuf, NULL);
E 156
I 156
	pvp = prescan(from, delimchar, pvpbuf, sizeof pvpbuf, NULL, NULL);
E 156
E 137
D 23
	pvp = prescan(from, '\0');
E 23
I 23
D 54
	pvp = prescan(from, '\0', pvpbuf);
E 54
E 23
	if (pvp == NULL)
I 54
D 78
		pvp = prescan(from, '\0', pvpbuf);
E 78
I 78
D 113
		pvp = prescan(from, '\0', pvpbuf, NULL);
E 113
I 113
D 119
		pvp = prescan(from, delimchar, pvpbuf, NULL);
E 119
I 119
D 137
		pvp = prescan(from, delimchar, pvpbuf, sizeof pvpbuf, NULL);
E 119
E 113
E 78
	if (pvp == NULL)
E 137
E 54
	{
I 79
		/* don't need to give error -- prescan did that already */
E 79
D 43
		syserr("cannot prescan from (%s)", from);
E 43
I 43
D 44
		syslog(LOG_INFO, "cannot prescan from (%s)", from);
E 44
I 44
# ifdef LOG
D 68
		if (LogLevel >= 1)
E 68
I 68
		if (LogLevel > 2)
E 68
			syslog(LOG_NOTICE, "cannot prescan from (%s)", from);
# endif
E 44
D 72
		usrerr("cannot prescan from (%s)", from);
E 72
I 72
D 79
		usrerr("553 cannot prescan from (%s)", from);
E 79
E 72
E 43
		finis();
	}
I 137
D 164
/*
E 164
E 137
D 90
	rewrite(pvp, 3);
	rewrite(pvp, 1);
I 37
	rewrite(pvp, 4);
E 90
I 90
D 91
	rewrite(pvp, 3, e);
	rewrite(pvp, 1, e);
	rewrite(pvp, 4, e);
E 91
I 91
D 120
	(void) rewrite(pvp, 3, e);
	(void) rewrite(pvp, 1, e);
	(void) rewrite(pvp, 4, e);
E 120
I 120
	(void) rewrite(pvp, 3, 0, e);
	(void) rewrite(pvp, 1, 0, e);
	(void) rewrite(pvp, 4, 0, e);
I 137
D 164
*/
E 164
E 137
E 120
E 91
E 90
I 83
D 88
	cataddr(pvp, buf, sizeof buf, '\0');
E 88
I 88
D 102
	cataddr(pvp, NULL, buf, sizeof buf, '\0');
E 88
	e->e_sender = newstr(buf);
E 102
I 102
	bp = buf + 1;
	cataddr(pvp, NULL, bp, sizeof buf - 2, '\0');
D 133
	if (*bp == '@')
E 133
I 133
	if (*bp == '@' && !bitnset(M_NOBRACKET, e->e_from.q_mailer->m_flags))
E 133
	{
		/* heuristic: route-addr: add angle brackets */
		strcat(bp, ">");
		*--bp = '<';
	}
	e->e_sender = newstr(bp);
E 102
	define('f', e->e_sender, e);
E 83
E 37
I 11
D 36
	rewrite(pvp, 4);
E 36
E 11
D 70
	cataddr(pvp, buf, sizeof buf);
E 70
I 70
D 81
	cataddr(pvp, buf, sizeof buf, '\0');
E 70
D 51
	define('f', newstr(buf), CurEnv);
E 51
I 51
D 53
	CurEnv->e_sender = CurEnv->e_returnpath = newstr(buf);
E 53
I 53
	e->e_sender = e->e_returnpath = newstr(buf);
E 81
E 53
D 54

# ifdef USERDB
D 53
	if (CurEnv->e_from.q_mailer == LocalMailer)
E 53
I 53
	if (e->e_from.q_mailer == LocalMailer)
E 53
	{
		extern char *udbsender();
		register char *p = udbsender(from);

		if (p != NULL)
		{
			/*
			**  We have an alternate address for the sender
			*/

			pvp = prescan(p, '\0', pvpbuf);
			if (pvp != NULL)
			{
				rewrite(pvp, 3);
				rewrite(pvp, 1);
				rewrite(pvp, 4);
				cataddr(pvp, buf, sizeof buf);
D 53
				CurEnv->e_sender = newstr(buf);
E 53
I 53
				e->e_sender = newstr(buf);
E 53
			}
		}
	}
# endif /* USERDB */
E 54

D 53
	define('f', CurEnv->e_sender, CurEnv);
E 53
I 53
D 81
	define('f', e->e_sender, e);
E 81
I 81
D 83
	define('f', e->e_from.q_paddr, e);
E 81
E 53
E 51

E 83
	/* save the domain spec if this mailer wants it */
D 7
	if (bitset(M_CANONICAL, CurEnv->e_from.q_mailer->m_flags))
E 7
I 7
D 30
	if (bitnset(M_CANONICAL, CurEnv->e_from.q_mailer->m_flags))
E 30
I 30
D 53
	if (CurEnv->e_from.q_mailer != NULL &&
	    bitnset(M_CANONICAL, CurEnv->e_from.q_mailer->m_flags))
E 53
I 53
D 83
	if (e->e_from.q_mailer != NULL &&
E 83
I 83
D 124
	if (!internal && e->e_from.q_mailer != NULL &&
E 124
I 124
	if (e->e_from.q_mailer != NULL &&
E 124
E 83
	    bitnset(M_CANONICAL, e->e_from.q_mailer->m_flags))
E 53
E 30
E 7
	{
I 157
		char **lastat;
E 157
		extern char **copyplist();

D 157
		while (*pvp != NULL && strcmp(*pvp, "@") != 0)
			pvp++;
		if (*pvp != NULL)
D 53
			CurEnv->e_fromdomain = copyplist(pvp, TRUE);
E 53
I 53
			e->e_fromdomain = copyplist(pvp, TRUE);
E 157
I 157
		/* get rid of any pesky angle brackets */
		(void) rewrite(pvp, 3, 0, e);
		(void) rewrite(pvp, 1, 0, e);
		(void) rewrite(pvp, 4, 0, e);

		/* strip off to the last "@" sign */
		for (lastat = NULL; *pvp != NULL; pvp++)
			if (strcmp(*pvp, "@") == 0)
				lastat = pvp;
		if (lastat != NULL)
		{
			e->e_fromdomain = copyplist(lastat, TRUE);
			if (tTd(45, 3))
			{
				printf("Saving from domain: ");
				printav(e->e_fromdomain);
			}
		}
E 157
E 53
	}
I 152
}
/*
**  PRINTENVFLAGS -- print envelope flags for debugging
**
**	Parameters:
**		e -- the envelope with the flags to be printed.
**
**	Returns:
**		none.
*/

struct eflags
{
	char	*ef_name;
	u_long	ef_bit;
};

struct eflags	EnvelopeFlags[] =
{
	"OLDSTYLE",	EF_OLDSTYLE,
	"INQUEUE",	EF_INQUEUE,
	"NO_BODY_RETN",	EF_NO_BODY_RETN,
	"CLRQUEUE",	EF_CLRQUEUE,
	"SENDRECEIPT",	EF_SENDRECEIPT,
	"FATALERRS",	EF_FATALERRS,
	"KEEPQUEUE",	EF_KEEPQUEUE,
	"RESPONSE",	EF_RESPONSE,
	"RESENT",	EF_RESENT,
	"VRFYONLY",	EF_VRFYONLY,
	"WARNING",	EF_WARNING,
	"QUEUERUN",	EF_QUEUERUN,
	"GLOBALERRS",	EF_GLOBALERRS,
	"PM_NOTIFY",	EF_PM_NOTIFY,
	"METOO",	EF_METOO,
	"LOGSENDER",	EF_LOGSENDER,
	"NORECEIPT",	EF_NORECEIPT,
	"HAS8BIT",	EF_HAS8BIT,
	"NL_NOT_EOL",	EF_NL_NOT_EOL,
	"CRLF_NOT_EOL",	EF_CRLF_NOT_EOL,
	"RET_PARAM",	EF_RET_PARAM,
	"HAS_DF",	EF_HAS_DF,
I 164
	"IS_MIME",	EF_IS_MIME,
E 164
	NULL
};

void
printenvflags(e)
	register ENVELOPE *e;
{
	register struct eflags *ef;
	bool first = TRUE;

	printf("%lx", e->e_flags);
	for (ef = EnvelopeFlags; ef->ef_name != NULL; ef++)
	{
		if (!bitset(ef->ef_bit, e->e_flags))
			continue;
		if (first)
			printf("<%s", ef->ef_name);
		else
			printf(",%s", ef->ef_name);
		first = FALSE;
	}
	if (!first)
		printf(">\n");
E 152
D 73
}
/*
**  TRUSTEDUSER -- tell us if this user is to be trusted.
**
**	Parameters:
**		user -- the user to be checked.
**
**	Returns:
**		TRUE if the user is in an approved list.
**		FALSE otherwise.
**
**	Side Effects:
**		none.
*/

bool
trusteduser(user)
	char *user;
{
	register char **ulist;
	extern char *TrustedUsers[];

	for (ulist = TrustedUsers; *ulist != NULL; ulist++)
		if (strcmp(*ulist, user) == 0)
			return (TRUE);
	return (FALSE);
E 73
}
E 1
