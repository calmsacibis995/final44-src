h20885
s 00003/00002/01012
d D 8.57 95/06/19 09:19:36 eric 179 177
c enable 8BIT-OK in greeting to pass 8 bit data as though F=8
e
s 00001/00001/01013
d R 8.57 95/06/19 09:17:38 eric 178 177
c update (as yet unused) 8BIT-OK signal
e
s 00002/00000/01012
d D 8.56 95/06/18 12:36:49 eric 177 176
c avoid MIMEing RFC1049 messages
e
s 00001/00001/01011
d D 8.55 95/06/13 09:22:40 eric 176 175
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00010/00004/01002
d D 8.54 95/05/28 11:49:05 eric 175 174
c lint
e
s 00004/00018/01002
d D 8.53 95/05/24 08:53:04 eric 174 173
c use strstr() instead of implementing by hand
e
s 00002/00000/01018
d D 8.52 95/05/15 19:00:15 eric 173 172
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00002/00003/01016
d D 8.51 95/04/29 07:43:26 eric 172 171
c documentation
e
s 00001/00003/01018
d D 8.50 95/04/29 07:40:50 eric 171 170
c better (more accurate) labelling of 8bit code
e
s 00002/00001/01019
d D 8.49 95/04/25 09:58:19 eric 170 169
c assume that anything with MIME-Version: is MIME, even if it
c didn't come with BODY=8BITMIME in the envelope
e
s 00001/00001/01019
d D 8.48 95/04/23 14:02:19 eric 169 168
c updates for new DSN drafts
e
s 00017/00006/01003
d D 8.47 95/04/22 14:50:44 eric 168 167
c better use of extended DSN status codes
e
s 00001/00001/01008
d D 8.46 95/04/21 09:56:41 eric 167 166
c update copyright notice
e
s 00008/00005/01001
d D 8.45 95/04/20 06:26:28 eric 166 165
c don't make errors so sticky on SMTP "MAIL FROM:" command; they
c apply to addresses, not to the connection
e
s 00003/00003/01003
d D 8.44 95/04/07 19:16:36 eric 165 164
c up timeouts on data puts to try to accomodate header address resultion
e
s 00001/00001/01005
d D 8.43 95/03/31 16:53:46 eric 164 163
c merge a bit with Sun version
e
s 00001/00001/01005
d D 8.42 95/03/27 11:43:22 eric 163 162
c make DSN info match draft numbers
e
s 00002/00001/01004
d D 8.41 95/03/27 09:25:17 eric 162 161
c more cleanup for DSN drafts
e
s 00025/00022/00980
d D 8.40 95/03/25 07:39:25 eric 161 160
c don't pass through NOTIFY= unless it was given in the SMTP RCPT
e
s 00023/00014/00979
d D 8.39 95/03/21 09:26:32 eric 160 159
c new DSN draft
e
s 00001/00001/00992
d D 8.38 95/03/14 09:10:36 eric 159 158
c change call to expand() to be more rational (and consistent!)
e
s 00002/00002/00991
d D 8.37 95/03/14 08:18:44 eric 158 157
c be more precise on MAXNAME checking
e
s 00002/00002/00991
d D 8.36 95/02/23 15:51:16 eric 157 156
c cleanup to make gcc -Winitialized happier
e
s 00000/00006/00993
d D 8.35 95/02/20 18:59:59 eric 156 155
c fix glitch in "relayed" messages
e
s 00002/00007/00997
d D 8.34 95/02/05 08:03:40 eric 155 154
c cut at 20 January version of DSN document
e
s 00002/00000/01002
d D 8.33 94/12/28 07:32:28 eric 154 153
c fix possible core dump on mail to local programs speaking SMTP
e
s 00006/00003/00996
d D 8.32 94/12/10 11:57:02 eric 153 152
c don't let an error in one envelope from address blow away other
c jobs to the same host later in the queue run
e
s 00005/00003/00994
d D 8.31 94/11/27 11:22:20 eric 152 151
c fix a problem that was causing inappropriate MIME-encoding
e
s 00013/00004/00984
d D 8.30 94/11/23 15:21:02 eric 151 150
c get ORCPT= ESMTP DSN parameter working
e
s 00003/00003/00985
d D 8.29 94/11/22 13:33:30 eric 150 149
c some conditions were reversed
e
s 00035/00017/00953
d D 8.28 94/11/21 21:07:23 eric 149 148
c convert to new DSN draft
e
s 00002/00002/00968
d D 8.27 94/11/19 16:57:23 eric 148 147
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00019/00009/00951
d D 8.26 94/11/08 10:03:13 eric 147 146
c accept "ESMTP" anywhere on any line of the greeting message
c to force running in Extended mode
e
s 00028/00020/00932
d D 8.25 94/11/05 12:27:41 eric 146 145
c tweak EightBitMode and F=8 options to do something useful
e
s 00001/00000/00951
d D 8.24 94/11/04 08:43:15 eric 145 144
c add F=8 mailer flag to force "just send 8" behaviour
e
s 00045/00001/00906
d D 8.23 94/11/04 08:40:13 eric 144 143
c first cut at DSN implementation
e
s 00008/00008/00899
d D 8.22 94/10/26 09:01:11 eric 143 142
c include host name we are chatting with when diagnosing protocol error
e
s 00019/00004/00888
d D 8.21 94/07/23 07:59:19 eric 142 141
c MIME 8 to 7 bit support
e
s 00003/00005/00889
d D 8.20 94/07/03 11:47:44 eric 141 140
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00015/00000/00879
d D 8.19 94/06/17 11:06:27 eric 140 139
c fixes for MIME body type support
e
s 00006/00003/00873
d D 8.18 94/01/24 08:01:27 eric 139 138
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00013/00002/00863
d D 8.17 94/01/05 09:20:11 eric 138 137
c try to make sure that path-addrs always have <angle brackets>
e
s 00001/00001/00864
d D 8.16 93/12/22 05:11:15 eric 137 136
c avoid misleading error message if an SMTP mailer drops core
e
s 00007/00002/00858
d D 8.15 93/12/10 12:43:18 eric 136 135
c avoid stupid failures if 421 error is returned during connection startup
e
s 00017/00004/00843
d D 8.14 93/11/08 09:48:02 eric 135 134
c avoid having errors on quit requeue the current job -- this is
c not sensible under connection caching
e
s 00003/00001/00844
d D 8.13 93/10/24 07:44:10 eric 134 133
c give immediate error reply to 5xx greeting message
e
s 00001/00001/00844
d D 8.12 93/10/21 07:18:55 eric 133 132
c allow dumping of MCI cache to syslog for debugging
e
s 00010/00000/00835
d D 8.11 93/10/15 08:34:25 eric 132 131
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00003/00000/00832
d D 8.10 93/09/25 12:39:23 eric 131 130
c comment regarding CheckLoopBack
e
s 00001/00001/00831
d D 8.9 93/09/24 07:14:20 eric 130 129
c hooks for future features
e
s 00001/00001/00831
d D 8.8 93/08/14 14:54:43 eric 129 128
c react reasonably with negative e_msgsize and SIZE parameter
e
s 00008/00002/00824
d D 8.7 93/07/28 14:23:34 eric 128 127
c drop null pointer dereference if XDEBUG defined
e
s 00010/00000/00816
d D 8.6 93/07/27 21:37:19 eric 127 126
c improved messages on error return
e
s 00001/00001/00815
d D 8.5 93/07/19 20:50:06 eric 126 125
c SGI IRIX & ANSI C portability
e
s 00004/00005/00812
d D 8.4 93/07/13 12:58:14 eric 125 124
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00010/00006/00807
d D 8.3 93/07/11 11:50:12 eric 124 123
c additional tweaking on message timeout code to allow for possible
c DNS timeouts
e
s 00056/00010/00757
d D 8.2 93/07/11 06:52:17 eric 123 122
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00765
d D 8.1 93/06/07 10:32:41 bostic 122 121
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00766
d D 6.34 93/06/05 17:07:43 eric 121 120
c lint-style cleanup
e
s 00011/00008/00756
d D 6.33 93/06/03 17:01:26 eric 120 119
c print better diagnostic information on sfgets timeouts
e
s 00000/00001/00764
d D 6.32 93/05/27 11:37:02 eric 119 118
c prototype functions
e
s 00029/00001/00736
d D 6.31 93/05/21 18:59:51 eric 118 117
c avoid unexpected multiline replies to HELO packet -- it breaks
c Pony Express on VMS; instead use a two line 220 greeting with ESMTP as the
c first word of the second line
e
s 00001/00001/00736
d D 6.30 93/05/12 07:59:50 eric 117 116
c don't botch message display (if it begins with digits)
e
s 00001/00001/00736
d D 6.29 93/05/04 15:45:02 eric 116 115
c update for MIME encapsulated error messages
e
s 00002/00001/00735
d D 6.28 93/04/29 20:34:44 eric 115 114
c implement g mailer flag
e
s 00103/00016/00633
d D 6.27 93/04/26 14:43:44 eric 114 113
c use "a" mailer flag to attempt to use ESMTP; send SIZE=
c on MAIL command if it is supported
e
s 00002/00002/00647
d D 6.26 93/04/18 08:55:43 eric 113 112
c avoid NULL mci_out syserr; creates bogus error messages
e
s 00000/00001/00649
d D 6.25 93/04/13 14:44:57 eric 112 111
c improve setproctitle info
e
s 00002/00002/00648
d D 6.24 93/04/10 09:27:40 eric 111 110
c fix loopback detection
e
s 00031/00023/00619
d D 6.23 93/04/09 14:21:35 eric 110 109
c don't reset SmtpReplyBuffer on fatal errors -- VERY BAD BUG!
e
s 00033/00012/00609
d D 6.22 93/04/04 16:03:16 eric 109 108
c IDENT cleanup; move loopback checking from srvr to user smtp
e
s 00001/00001/00620
d D 6.21 93/04/01 13:31:15 eric 108 107
c use e_statmsg for logging of OK status
e
s 00003/00003/00618
d D 6.20 93/03/30 10:23:31 eric 107 106
c change connection probing to use RSET instead of NOOP
e
s 00001/00000/00620
d D 6.19 93/03/29 17:24:05 eric 106 105
c save message from final 250 line
e
s 00001/00001/00619
d D 6.18 93/03/29 12:41:47 eric 105 104
c fix typo bugs
e
s 00002/00003/00618
d D 6.17 93/03/18 19:34:57 eric 104 103
c there can be errors on mci_out if the other end shuts down early
e
s 00015/00001/00606
d D 6.16 93/03/16 09:16:04 eric 103 102
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00004/00000/00603
d D 6.15 93/03/14 08:29:53 eric 102 101
c compile warning cleanups
e
s 00006/00007/00597
d D 6.14 93/02/23 06:31:28 eric 101 100
c overhaul status of SMTP reply codes
e
s 00003/00003/00601
d D 6.13 93/02/21 12:43:33 eric 100 99
c don't be so reluctant to give verbose information
e
s 00010/00010/00594
d D 6.12 93/02/21 09:56:12 eric 99 98
c generalize read timeout
e
s 00005/00005/00599
d D 6.11 93/02/19 09:21:22 eric 98 97
c fix a variety of bugs found by Eric Wassenaar <e07@nikhef.nl>
e
s 00003/00002/00601
d D 6.10 93/02/18 20:22:07 eric 97 96
c move the meta-characters from C0 into C1 space
e
s 00001/00001/00602
d D 6.9 93/02/18 15:11:49 eric 96 95
c change logging of 4yz error codes
e
s 00005/00005/00598
d D 6.8 93/02/16 18:29:37 eric 95 94
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00031/00000/00572
d D 6.7 93/02/15 12:00:22 eric 94 93
c improve some error messages; fix quoted :include:s; check for some
c other buffer overflows; log SMTP protocol errors
e
s 00012/00000/00560
d D 6.6 93/02/14 19:04:44 eric 93 92
c fix another problem in the MCI state machine
e
s 00003/00001/00557
d D 6.5 93/02/12 11:51:09 eric 92 91
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00010/00007/00548
d D 6.4 93/01/28 08:05:31 eric 91 90
c fix mci_state after sending RSET command
e
s 00009/00003/00546
d D 6.3 93/01/21 15:18:26 eric 90 89
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00039/00037/00510
d D 6.2 93/01/01 13:06:26 eric 89 88
c pass read timeouts as parameter; fix deferred error reporting
e
s 00000/00000/00547
d D 6.1 92/12/21 16:08:08 eric 88 87
c Release 6
e
s 00004/00002/00543
d D 5.27 92/12/18 07:30:22 eric 87 86
c log host name on reply: read error message
e
s 00001/00001/00544
d D 5.26 92/12/15 12:34:41 eric 86 85
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00007/00002/00538
d D 5.25 92/11/16 17:52:11 eric 85 84
c make it use varargs/stdarg and vsprintf
e
s 00005/00005/00535
d D 5.24 92/11/14 11:34:02 eric 84 83
c (partially) ANSI-fy it
e
s 00000/00001/00540
d D 5.23 92/07/12 14:09:27 eric 83 82
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00076/00069/00465
d D 5.22 92/07/11 18:51:29 eric 82 81
c open connection caching
e
s 00124/00083/00410
d D 5.21 92/05/31 13:51:14 eric 81 78
i 80 79
c checkpoint: putting in connection caching
e
s 00046/00047/00447
d D 5.20.1.2 92/05/29 10:57:39 eric 80 79
c more connection caching hacks
e
s 00007/00016/00487
d D 5.20.1.1 92/02/26 14:04:57 eric 79 78
c partial hooks for caching all email connections; won't work
c because it could result in too many connections, and some could
c time out.
e
s 00001/00001/00502
d D 5.20 92/02/24 21:15:40 eric 78 77
c allow on-line comments; don't double-parse RCPT To: addresses;
c warn on truncated lines; do some sanity checks on .cf file descriptor
e
s 00008/00013/00495
d D 5.19 92/01/05 09:21:28 eric 77 76
c clean up #ifdef configuration to more cleanly match the modern age
e
s 00021/00008/00487
d D 5.18 92/01/03 07:41:42 eric 76 75
c mark tempfail during initial usersmtp open to avoid extra connections
c in the future
e
s 00001/00001/00494
d D 5.17 91/12/15 13:59:32 eric 75 74
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00001/00001/00494
d D 5.16 91/03/02 17:15:35 bostic 74 73
c ANSI
e
s 00001/00011/00494
d D 5.15 90/06/01 19:05:04 bostic 73 72
c new copyright notice
e
s 00002/00001/00503
d D 5.14 90/04/19 17:03:29 bostic 72 71
c don't NULL deref if smtpmessage() is passed a NULL mailer
c bug report 4.3BSD-tahoe/usr.sbin/14
e
s 00009/00000/00495
d D 5.13 89/01/19 15:56:28 bostic 71 70
c make ps more informative; from Rick Adams/David Comay
e
s 00000/00006/00495
d D 5.12 89/01/01 17:17:55 bostic 70 69
c remove DEBUG
e
s 00001/00001/00500
d D 5.11 88/11/18 08:33:31 karels 69 68
c pipe down! losing a network connection is a normal event!
e
s 00011/00009/00490
d D 5.10 88/06/30 15:00:02 bostic 68 67
c install approved copyright notice
e
s 00024/00020/00475
d D 5.9 88/03/13 19:53:31 bostic 67 66
c add Berkeley specific header
e
s 00000/00001/00495
d D 5.8 86/12/17 16:05:35 eric 66 65
c delete unneeded #include <ctype.h>
e
s 00000/00001/00496
d D 5.7 86/04/02 16:02:02 eric 65 64
c don't run around clearing EF_FATALERRS -- this often applies to another
c address.  Drop uid/gid check in sameaddr -- it causes more problems
c than it fixes.
e
s 00002/00002/00495
d D 5.6 85/09/30 21:34:43 eric 64 63
m 
c clean up some aspects of error message display
e
s 00000/00000/00497
d D 5.5 85/09/19 01:25:57 eric 63 61
i 62
m 
c incorporate SMI changes -- still experimental
e
s 00007/00000/00490
d D 5.3.1.1 85/09/19 00:56:18 eric 62 60
m 
c SMI changes (somewhat)
e
s 00001/00001/00489
d D 5.4 85/09/17 19:24:28 eric 61 60
m 
c facilities in syslog
e
s 00004/00002/00486
d D 5.3 85/06/08 10:31:19 eric 60 59
m 
c lint for 4.3 release
e
s 00002/00003/00486
d D 5.2 85/06/07 22:20:57 miriam 59 58
m 
c Resolve duplicate SccsId
e
s 00014/00000/00475
d D 5.1 85/06/07 15:17:45 dist 58 57
m 
c Add copyright
e
s 00030/00002/00445
d D 4.12 85/05/24 11:01:53 eric 57 56
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00001/00001/00446
d D 4.11 85/04/04 17:38:55 miriam 56 55
m 
c Change LOG_ERR to LOG_MAIL
e
s 00001/00000/00446
d D 4.10 84/08/11 16:56:48 eric 55 54
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00001/00001/00445
d D 4.9 84/03/11 16:56:13 eric 54 53
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00001/00001/00445
d D 4.8 84/03/11 13:38:35 eric 53 52
m 
c fixes from Greg Satz <satz@sri-tsc.ARPA>, mostly for PDP's
e
s 00006/00007/00440
d D 4.7 83/11/13 18:08:34 eric 52 51
m 
c Fixes two nasty problems, both pointed out by Bill Nowicki at Stanford:
c I/O errors on input in collect would cause infinite loops, and a protocol
c error (or other error that would call smtpquit abnormally) would cause
c core dumps
e
s 00001/00001/00446
d D 4.6 83/10/29 12:01:29 eric 51 50
m 
c add newline to "deferred" message in usersmtp.c
e
s 00007/00000/00440
d D 4.5 83/10/01 16:58:10 eric 50 49
m 
c clean up error handling in general; make sure that something gets logged
c in the transcript if the connection cannot be established; clean up Teus
c Hagen's mod to arpadate.c to match the sendmail coding style.
e
s 00025/00011/00415
d D 4.4 83/09/07 09:45:17 eric 49 48
m 
c Increase timeout for greeting message to five minutes; remember to close
c the connection properly if we get a failure during connection establishment.
e
s 00016/00010/00410
d D 4.3 83/09/05 14:33:40 eric 48 47
m 
c Cut down the amount of bulk that is sent in SMTP error messages, by
c trying to log only real errors in the transcript.  -v mode is unchanged.
e
s 00018/00001/00402
d D 4.2 83/08/31 17:42:37 eric 47 46
m 
c fix problem with timeouts caused by change in EINTR semantics in 4.2bsd;
c add a two minute timeout on the greeting message in user smtp to detect
c hung connections
e
s 00000/00000/00403
d D 4.1 83/07/25 19:47:02 eric 46 45
m 
c 4.2 release version
e
s 00001/00001/00402
d D 3.43 83/03/26 14:24:18 eric 45 44
m 213
c increase buffer size in smtpmessage
e
s 00022/00009/00381
d D 3.42 83/02/20 12:28:25 eric 44 43
m 190
c Avoid loops in the auto-closedown code
e
s 00003/00002/00387
d D 3.41 83/02/02 12:54:21 eric 43 42
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00005/00000/00384
d D 3.40 83/01/18 20:37:57 eric 42 41
m 
c pause() after reply error if 18.100 set -- so that Sam can try to track
c down the state of the connection in the CMU-CS-A problem.
e
s 00002/00002/00382
d D 3.39 83/01/16 13:14:47 eric 41 40
m 152
c Change mailer spec to have labelled fields for future expansion.
c **** This delta invalidates previous configuration files ****
e
s 00004/00005/00380
d D 3.38 83/01/15 17:41:04 eric 40 39
m 149
c be sure everything gets appropriately externalized; canonname goes away,
c since everything is now done by remotename
e
s 00004/00003/00381
d D 3.37 83/01/09 15:43:01 eric 39 38
m 
c fix CRLF problem when sending SMTP commands; make newstr() and crlf()
c into macros
e
s 00052/00038/00332
d D 3.36 83/01/06 10:48:49 eric 38 37
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00002/00000/00368
d D 3.35 83/01/05 17:57:03 eric 37 36
m 
c curiouser and curiouser.....  a read error on the reply from a QUIT will
c cause another QUIT command, and thus an fclose(NULL).  Some sites seem
c to be sending a 421 Shutting down and then closing without waiting for
c the QUIT, so this happens....
e
s 00022/00008/00346
d D 3.34 83/01/05 10:18:55 eric 36 35
m 
c improve error recovery for bizarre SMTP cases; unfortunately CMU has
c decided to start working again, so the strangest parts are untested.
e
s 00005/00002/00349
d D 3.33 83/01/04 17:45:37 eric 35 34
m 
c Ignore SIGPIPE early (in main rather than in deliver) so that rude hosts
c that close the connection early don't cause us to die -- in particular,
c CMU-CS-A (nee CMU-10A) was doing this after the DATA command; the problem
c went away quite mysteriously, so I have no idea why it happened
e
s 00003/00003/00348
d D 3.32 83/01/01 21:26:09 eric 34 33
m 123
c Put CRLF on all lines in user SMTP.  Pass this info down to
c innumerable routines.
e
s 00017/00013/00334
d D 3.31 83/01/01 18:15:07 eric 33 32
m 122
c Use a more resilient algorithm to handle the special case of an SMTP
c connection that is going down spontaneously (with a 421 reply code)
e
s 00007/00007/00340
d D 3.30 82/12/05 13:47:21 eric 32 31
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00051/00035/00296
d D 3.29 82/11/28 16:01:24 eric 31 30
m 
c implement SMTP auto-shutdown on 421 codes; clean up some error processing
c items, particularly in SMTP; don't reinstantiate error message bodies after
c queueing; other minor changes.  This is all cleanup from 3.253.
e
s 00001/00002/00330
d D 3.28 82/11/28 00:23:33 eric 30 29
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00006/00003/00326
d D 3.27 82/11/24 17:16:31 eric 29 28
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00020/00000/00309
d D 3.26 82/11/21 17:19:26 eric 28 27
m 026
c preliminary hacks for multiple SMTP transactions per connection: make
c assignment of multiple queue id's more efficient, make prefixes two
c characters (e.g., qfAA99999), pass the file name to freeze and thaw,
c add a mailer flag saying we are talking to one of our own kind.
e
s 00010/00001/00299
d D 3.25 82/10/09 19:06:41 eric 27 26
m 002
c Handle Reverse-Path in some reasonable way.  You must put the 'X'
c flag (M_FULLSMTP) in the local mailer's flags to get this line.
e
s 00002/00002/00298
d D 3.24 82/10/07 08:51:10 eric 26 25
c never use ruleset 3 alone -- perhaps the standard use of ruleset
c three should go now, since noone uses it alone.
e
s 00005/00005/00295
d D 3.23 82/09/21 10:12:28 eric 25 24
c put 050 in from of recursive smtp messages
e
s 00002/00002/00298
d D 3.22 82/09/06 17:00:33 eric 24 23
c user SMTP fixes to talk to ISI
e
s 00002/00002/00298
d D 3.21 82/09/05 18:03:51 eric 23 22
c clean up canonname
e
s 00008/00006/00292
d D 3.20 82/08/31 10:06:12 eric 22 21
c clean up reply code processing some more; in particular, give more
c detail in many messages.  process connection failures correctly.
e
s 00008/00006/00290
d D 3.19 82/08/29 17:33:00 eric 21 20
c fix serious botch in SMTP reply code delta; change a bunch of
c "Internal error" codes to a new "Remote protocol error" -- so that
c I don't get blamed for things that other systems do.
e
s 00020/00013/00276
d D 3.18 82/08/29 16:52:37 eric 20 19
c do a better job at interpreting SMTP reply codes
e
s 00000/00002/00289
d D 3.17 82/08/08 21:16:00 eric 19 18
c make "sleep" work correctly even in the face of other events; clean
c up the queue processing: child queue runs now go away when done.  more
c debugging logging is needed to verify that this works right though.
e
s 00006/00011/00285
d D 3.16 82/08/08 17:02:54 eric 18 17
c more general event mechanism
e
s 00004/00004/00292
d D 3.15 82/08/08 01:03:35 eric 17 16
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00001/00000/00295
d D 3.14 82/07/05 20:55:16 eric 16 15
c improve debugging: flush transcript before doing things that might
c take a long time; add some info to debugging output
e
s 00028/00002/00267
d D 3.13 82/07/05 12:03:05 eric 15 13
c put timeouts on net reads
e
s 00008/00000/00269
d D 3.12.1.1 82/07/04 10:28:37 eric 14 13
c do some stuff to add a "HOPS" command -- it seems like it would
c be easier and smarter to count Mail-From: lines.
e
s 00017/00018/00252
d D 3.12 82/06/19 20:47:29 eric 13 12
c improve SMTP error reporting
e
s 00001/00001/00269
d D 3.11 82/05/31 18:50:51 eric 12 11
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00000/00000/00270
d D 3.10 82/05/31 15:33:01 eric 11 9
i 10
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00007/00006/00263
d D 3.9.1.1 82/05/29 18:21:17 eric 10 9
c try to install envelopes.  is this really worth it???
e
s 00030/00005/00239
d D 3.9 82/03/06 12:09:46 eric 9 8
c clean up error handling in IPC case; fix a minor bug in headers in
c queueing code; make SMTP mail multi user per connect.
e
s 00000/00001/00244
d D 3.8 82/01/10 21:58:04 eric 8 7
c cleanup from cbosgd (Mark Horton) testing; some internals, mostly
c configuration.  This tries to make the configuration file (cf.m4) be
c much more general, but I fear it is doomed to failure -- it may be
c better to just tell people to roll their own.
e
s 00002/00002/00243
d D 3.7 81/12/06 12:40:43 eric 7 6
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00006/00000/00239
d D 3.6 81/12/05 11:54:15 eric 6 5
c put the SMTP and queueing code on compilation flags so that sendmail
c will fit on non-ID PDP-11's (ugh); put the ugly UUCP hack on a
c compilation flag also to emphasize that it sucks eggs; makefile
c cleanup.
e
s 00017/00014/00222
d D 3.5 81/11/21 09:58:13 eric 5 4
c convert to SMTP draft 3
e
s 00103/00176/00133
d D 3.4 81/11/11 20:24:17 eric 4 3
c integrate user SMTP into sendmail itself.  If there is no $u arg
c in the mailer argument list, SMTP is run.  This can be used directly
c over the Ethernet or to any clever mailer.  We still need to edit
c spooled control files to remove recipients that have been successfully
c sent during queue processing.
e
s 00094/00029/00215
d D 3.3 81/11/08 12:39:25 eric 3 2
c detects errors in a reasonable way.  however, it only works
c with one user at a time, due to the problems of returning separate
c error returns per user.  We should run smtp between sendmail and the
c individual mailers.....
e
s 00096/00035/00148
d D 3.2 81/11/07 22:00:32 eric 2 1
c fix a number of bugs to get the actual case working over the ether.
c this version seems to work correctly if there are no errors, but any
c error sends it into strange places.
e
s 00183/00000/00000
d D 3.1 81/10/31 10:11:38 eric 1 0
c date and time created 81/10/31 10:11:38 by eric
e
u
U
f b 
f i 
t
T
I 58
/*
I 68
D 167
 * Copyright (c) 1983 Eric P. Allman
E 167
I 167
 * Copyright (c) 1983, 1995 Eric P. Allman
E 167
E 68
D 67
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 67
I 67
D 122
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 122
I 122
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 122
 *
D 73
 * Redistribution and use in source and binary forms are permitted
D 68
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 68
I 68
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
E 73
I 73
 * %sccs.include.redist.c%
E 73
E 68
 */
E 67

I 67
# include "sendmail.h"
E 67
D 60
#ifndef lint
D 59
static char	SccsId[] = "%W% (Berkeley) %G%";
E 59
#endif not lint
E 60

I 67
#ifndef lint
#ifdef SMTP
static char sccsid[] = "%W% (Berkeley) %G% (with SMTP)";
#else
static char sccsid[] = "%W% (Berkeley) %G% (without SMTP)";
#endif
#endif /* not lint */

E 67
E 58
I 2
D 66
# include <ctype.h>
E 66
I 15
D 19
# include <signal.h>
E 19
E 15
E 2
I 1
D 8
# include <wellknown.h>
E 8
# include <sysexits.h>
I 57
# include <errno.h>
E 57
D 4
# include <stdio.h>
# include <useful.h>
E 4
I 4
D 67
# include "sendmail.h"
E 67
E 4

I 6
D 67
# ifndef SMTP
I 60
# ifndef lint
E 60
D 7
static char	SccsId[] =	"%W%	%G%	(no SMTP)";
E 7
I 7
D 59
SCCSID(%W%	%Y%	%G%	(no SMTP));
E 59
I 59
static char	SccsId[] = "%W% (Berkeley) %G%	(no SMTP)";
I 60
# endif not lint
E 60
E 59
E 7
# else SMTP

I 60
# ifndef lint
E 60
E 6
D 7
static char	SccsId[] =	"%W%	%G%";
E 7
I 7
D 59
SCCSID(%W%	%Y%	%G%);
E 59
I 59
static char	SccsId[] = "%W% (Berkeley) %G%";
I 60
# endif not lint
E 60
E 59
E 7

I 31

E 67
I 67
# ifdef SMTP
E 67

E 31
/*
I 31
**  USERSMTP -- run SMTP protocol from the user end.
**
**	This protocol is described in RFC821.
*/

#define REPLYTYPE(r)	((r) / 100)		/* first digit of reply code */
#define REPLYCLASS(r)	(((r) / 10) % 10)	/* second digit of reply code */
#define SMTPCLOSING	421			/* "Service Shutting Down" */

I 48
char	SmtpMsgBuffer[MAXLINE];		/* buffer for commands */
E 48
D 33
static char	SmtpReplyBuffer[MAXLINE];	/* buffer for replies */
static FILE	*SmtpOut;			/* output file */
static FILE	*SmtpIn;			/* input file */
static int	SmtpPid;			/* pid of mailer */
static bool	SmtpClosing;			/* set on a forced close */
E 33
I 33
char	SmtpReplyBuffer[MAXLINE];	/* buffer for replies */
I 57
char	SmtpError[MAXLINE] = "";	/* save failure error messages */
E 57
D 79
FILE	*SmtpOut;			/* output file */
FILE	*SmtpIn;			/* input file */
E 79
int	SmtpPid;			/* pid of mailer */
I 127
bool	SmtpNeedIntro;			/* need "while talking" in transcript */
E 127
I 102

D 175
#ifdef __STDC__
extern	smtpmessage(char *f, MAILER *m, MCI *mci, ...);
#endif
E 175
I 175
extern void	smtpmessage __P((char *f, MAILER *m, MCI *mci, ...));
E 175
E 102
D 44
bool	SmtpClosing;			/* set on a forced close */
E 44
I 44
D 80

/* following represents the state of the SMTP connection */
int	SmtpState;			/* connection state, see below */

#define SMTP_CLOSED	0		/* connection is closed */
#define SMTP_OPEN	1		/* connection is open for business */
#define SMTP_SSD	2		/* service shutting down */
E 80
E 44
E 33
/*
E 31
D 4
**  TCP -- TCP/Ethernet/ARPAnet mailer
E 4
I 4
**  SMTPINIT -- initialize SMTP.
E 4
**
D 4
**	This arranges to send a message over the TCP connection.
*/

# define MAXLINE	200

char	*MailCommand =	"/usr/lib/sendmail";
char	*MailUser =	"network";
D 2
char	*MailPassword =	NULL;
FILE	*MailFile;
E 2
I 2
char	*MailPassword =	"mailhack";
FILE	*InConnection;
FILE	*OutConnection;
E 2
bool	Verbose;
I 2
bool	Debug;
I 3
int	Status;			/* exit status */
E 3
E 2

main(argc, argv)
	int argc;
	char **argv;
{
D 2
	extern FILE *openconnection();
E 2
D 3
	register int stat;

E 3
I 2
	while (argc > 1 && argv[1][0] == '-')
	{
		register char *p = *++argv;

		argc--;
		switch (p[1])
		{
		  case 'v':
			Verbose = TRUE;
			break;

		  case 'd':
			Debug = TRUE;
			break;
		}
	}

E 2
	if (argc < 4)
I 2
	{
		if (Debug)
			printf("Usage\n");
E 2
		exit(EX_USAGE);
I 2
	}
E 2

D 2
	MailFile = openconnection(argv[2]);
	if (MailFile == NULL)
E 2
I 2
	if (openconnection(argv[2]) < 0)
E 2
D 3
		exit(EX_TEMPFAIL);
E 3
I 3
		exit(Status);
E 3

D 3
	stat = runsmtp(argv[1], &argv[3]);
E 3
I 3
	Status = runsmtp(argv[1], &argv[3]);
E 3

I 3
	closeconnection();

E 3
I 2
	if (Debug)
D 3
		printf("Finishing with stat %d\n", stat);
E 3
I 3
		printf("Finishing with stat %d\n", Status);
E 3

E 2
D 3
	exit(stat);
E 3
I 3
	exit(Status);
E 3
}
/*
**  OPENCONNECTION -- open connection to SMTP socket
E 4
I 4
**	Opens the connection and sends the initial protocol.
E 4
**
**	Parameters:
D 3
**		none.
E 3
I 3
D 4
**		host -- the name of the host to connect to.  This
**			will be replaced by the canonical name of
**			the host.
E 4
I 4
**		m -- mailer to create connection to.
**		pvp -- pointer to parameter vector to pass to
**			the mailer.
D 38
**		ctladdr -- controlling address for this mailer.
E 38
E 4
E 3
**
**	Returns:
D 3
**		file pointer of connection.
**		NULL on error.
E 3
I 3
D 4
**		File descriptor of connection.
**		-1 on error.
E 4
I 4
D 82
**		appropriate exit status -- EX_OK on success.
I 49
**		If not EX_OK, it should close the connection.
E 82
I 82
**		none.
E 82
E 49
E 4
E 3
**
**	Side Effects:
D 3
**		none.
E 3
I 3
D 4
**		sets 'Status' to represent the problem on error.
E 4
I 4
**		creates connection and sends initial protocol.
E 4
E 3
*/

I 175
void
E 175
I 47
D 89
jmp_buf	CtxGreeting;

E 89
E 47
D 2
FILE *
E 2
D 4
openconnection(host)
	char *host;
E 4
I 4
D 31
# define REPLYTYPE(r)	((r) / 100)
I 20
# define REPLYCLASS(r)	(((r) / 10) % 10)
E 20

static FILE	*SmtpOut;	/* output file */
static FILE	*SmtpIn;	/* input file */
static int	SmtpPid;	/* pid of mailer */
I 9
static int	SmtpErrstat;	/* error status if open fails */
E 9

E 31
D 38
smtpinit(m, pvp, ctladdr)
E 38
I 38
D 80
smtpinit(m, pvp)
E 80
I 80
D 81
smtpinit(m, mci, pvp)
E 81
I 81
D 82
MCONINFO *
smtpinit(m, pvp, e)
E 82
I 82
smtpinit(m, mci, e)
E 82
E 81
E 80
E 38
	struct mailer *m;
I 80
D 81
	MCONINFO *mci;
E 81
E 80
D 82
	char **pvp;
E 82
I 82
	register MCI *mci;
E 82
I 81
	ENVELOPE *e;
E 81
D 38
	ADDRESS *ctladdr;
E 38
E 4
{
D 4
	char cmdbuf[100];
D 2
	extern FILE *rexec();
	register FILE *f;
E 2
I 2
	register int fd;
E 4
I 4
	register int r;
I 47
D 109
	EVENT *gte;
E 109
I 109
	register char *p;
E 109
I 77
D 81
	register STAB *st;
E 77
E 47
	char buf[MAXNAME];
E 81
I 81
D 82
	MCONINFO *mci;
E 82
E 81
I 47
D 74
	extern greettimeout();
E 74
I 74
D 89
	static int greettimeout();
E 89
I 77
D 119
	extern STAB *stab();
E 119
I 118
	extern void esmtp_check();
E 118
I 114
	extern void helo_options();
E 114
I 80
D 82
	extern MCONINFO *openmailer();
E 82
I 82
D 92
	extern MCI *openmailer();
E 92
E 82
E 80
E 77
E 74
E 47
I 15
D 30
	extern tick();
E 30
I 18
D 40
	extern char *canonname();
E 40
E 18
E 15
E 4
E 2

I 89
D 123
	if (tTd(17, 1))
E 123
I 123
	if (tTd(18, 1))
E 123
	{
		printf("smtpinit ");
D 133
		mci_dump(mci);
E 133
I 133
		mci_dump(mci, FALSE);
E 133
	}

E 89
D 4
	/* create the command name */
D 2
	sprintf(cmdbuf, "%s -p", MailCommand);
E 2
I 2
	sprintf(cmdbuf, "%s -as%s%s", MailCommand,
					Verbose ? " -v" : "",
					Debug ? " -d" : "");
E 4
I 4
	/*
	**  Open the connection to the mailer.
	*/
E 4
E 2

I 44
D 70
#ifdef DEBUG
E 70
D 80
	if (SmtpState == SMTP_OPEN)
E 80
I 80
D 81
	if (mci->mci_state == MCIS_OPEN)
E 80
		syserr("smtpinit: already open");
D 70
#endif DEBUG
E 70

E 44
I 9
D 79
	SmtpIn = SmtpOut = NULL;
E 79
I 36
D 44
	SmtpClosing = FALSE;
E 44
I 44
D 80
	SmtpState = SMTP_CLOSED;
E 80
I 80
	mci->mci_state = MCIS_CLOSED;
E 81
E 80
I 57
	SmtpError[0] = '\0';
I 89
	CurHostName = mci->mci_host;		/* XXX UGLY XXX */
I 154
	if (CurHostName == NULL)
		CurHostName = MyHostName;
E 154
I 127
	SmtpNeedIntro = TRUE;
E 127
E 89
I 62
D 81
	SmtpPhase = "user open";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, pvp[1], SmtpPhase);
E 81
I 81
D 82
	setproctitle("%s %s: %s", e->e_id, pvp[1], "user open");
E 81
E 71
E 62
E 57
E 44
E 36
E 9
I 2
D 4
	if (Debug)
		printf("Creating connection to \"%s\" on %s\n", cmdbuf, host);
E 4
I 4
D 38
	SmtpPid = openmailer(m, pvp, ctladdr, TRUE, &SmtpOut, &SmtpIn);
E 38
I 38
D 79
	SmtpPid = openmailer(m, pvp, (ADDRESS *) NULL, TRUE, &SmtpOut, &SmtpIn);
E 79
I 79
	mci = openmailer(m, pvp, (ADDRESS *) NULL, TRUE);
E 79
E 38
I 9
D 81
	if (SmtpPid < 0)
E 81
I 81
	if (mci == NULL)
		return NULL;
	if (mci->mci_state != MCIS_OPENING && mci->mci_state != MCIS_CLOSED)
		return mci;
	mci->mci_phase = "user open";
	mci->mci_state = MCIS_OPENING;
	if (mci->mci_pid < 0)
E 82
I 82
	switch (mci->mci_state)
E 82
E 81
	{
D 31
		SmtpErrstat = ExitStat;
E 31
D 70
# ifdef DEBUG
E 70
D 17
		if (Debug > 0)
E 17
I 17
D 82
		if (tTd(18, 1))
E 17
D 31
			printf("smtpinit: cannot open: Errstat %d errno %d\n",
			   SmtpErrstat, errno);
E 31
I 31
			printf("smtpinit: cannot open %s: stat %d errno %d\n",
			   pvp[0], ExitStat, errno);
E 31
D 70
# endif DEBUG
E 70
I 50
D 81
		if (CurEnv->e_xfp != NULL)
E 81
I 81
		if (e->e_xfp != NULL)
E 81
		{
I 57
			register char *p;
E 57
			extern char *errstring();
I 57
			extern char *statstring();
E 82
I 82
	  case MCIS_ACTIVE:
		/* need to clear old information */
		smtprset(m, mci, e);
D 91
		mci->mci_state = MCIS_OPEN;
E 91
I 91
		/* fall through */
E 91
E 82
E 57

D 51
			fprintf(CurEnv->e_xfp, "421 %s.%s... Deferred: %s",
E 51
I 51
D 57
			fprintf(CurEnv->e_xfp, "421 %s.%s... Deferred: %s\n",
E 51
				pvp[1], m->m_name, errstring(errno));
E 57
I 57
D 82
			if (errno == 0)
			{
				p = statstring(ExitStat);
D 81
				fprintf(CurEnv->e_xfp,
E 81
I 81
				fprintf(e->e_xfp,
E 81
					"%.3s %s.%s... %s\n",
					p, pvp[1], m->m_name, p);
			}
			else
			{
I 71
				r = errno;
E 71
D 81
				fprintf(CurEnv->e_xfp,
E 81
I 81
				fprintf(e->e_xfp,
E 81
					"421 %s.%s... Deferred: %s\n",
					pvp[1], m->m_name, errstring(errno));
I 71
				errno = r;
E 71
			}
E 57
		}
E 50
D 81
		return (ExitStat);
E 81
I 81
		mci->mci_exitstat = ExitStat;
		return mci;
E 82
I 82
	  case MCIS_OPEN:
		return;

	  case MCIS_ERROR:
	  case MCIS_SSD:
		/* shouldn't happen */
		smtpquit(m, mci, e);
I 91
		/* fall through */
E 91

	  case MCIS_CLOSED:
D 101
		syserr("smtpinit: state CLOSED");
E 101
I 101
		syserr("451 smtpinit: state CLOSED");
E 101
		return;

	  case MCIS_OPENING:
		break;
E 82
E 81
	}
I 44
D 80
	SmtpState = SMTP_OPEN;
E 80
I 80
D 81
	mci->mci_state = MCIS_OPEN;
E 81
E 80
E 44
I 15
D 19
	(void) signal(SIGALRM, tick);
E 19
E 15
E 9
E 4

I 82
D 89
	mci->mci_phase = "user open";
E 89
I 89
D 112
	SmtpPhase = mci->mci_phase = "user open";
E 112
E 89
	mci->mci_state = MCIS_OPENING;

E 82
I 3
D 4
	/* verify host name */
	if (rhost(&host) < 0)
	{
		if (Debug)
			printf("Unknown host %s\n", host);
		Status = EX_NOHOST;
		return (-1);
	}
E 4
I 4
	/*
	**  Get the greeting message.
D 47
	**	This should appear spontaneously.
E 47
I 47
D 49
	**	This should appear spontaneously.  Give it two minutes to
E 49
I 49
	**	This should appear spontaneously.  Give it five minutes to
E 49
	**	happen.
E 47
	*/
E 4

I 47
D 89
	if (setjmp(CtxGreeting) != 0)
D 49
		return (EX_TEMPFAIL);
	gte = setevent(120, greettimeout, 0);
E 49
I 49
D 76
		goto tempfail;
E 76
I 76
		goto tempfail1;
E 76
D 53
	gte = setevent(300, greettimeout, 0);
E 53
I 53
	gte = setevent((time_t) 300, greettimeout, 0);
I 62
D 81
	SmtpPhase = "greeting wait";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, CurHostName, SmtpPhase);
E 71
E 62
E 53
E 49
E 47
E 3
E 2
D 4
	/* create connection (we hope) */
D 2
	f = rexec(&host, SHELLSERVER, cmdbuf, &MailUser, NULL);
E 2
I 2
	fd = rexec(&host, SHELLSERVER, cmdbuf, MailUser, MailPassword);
	if (fd < 0)
I 3
	{
		Status = EX_TEMPFAIL;
E 3
		return (-1);
I 3
	}
E 3
	InConnection = fdopen(fd, "r");
	OutConnection = fdopen(fd, "w");
	if (InConnection == NULL || OutConnection == NULL)
I 3
	{
		Status = EX_SOFTWARE;
E 3
		return (-1);
I 3
	}
E 4
I 4
D 38
	r = reply();
E 38
I 38
D 80
	r = reply(m);
E 80
I 80
	r = reply(m, mci);
E 81
I 81
	mci->mci_phase = "greeting wait";
E 89
I 89
D 120
	SmtpPhase = mci->mci_phase = "greeting wait";
E 120
I 120
	SmtpPhase = mci->mci_phase = "client greeting";
E 120
E 89
	setproctitle("%s %s: %s", e->e_id, CurHostName, mci->mci_phase);
D 89
	r = reply(m, mci, e);
E 81
E 80
I 47
	clrevent(gte);
E 89
I 89
D 99
	r = reply(m, mci, e, (time_t) 300);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_initial);
E 114
I 114
D 118
	r = reply(m, mci, e, TimeOuts.to_initial, NULL);
E 118
I 118
	r = reply(m, mci, e, TimeOuts.to_initial, esmtp_check);
E 118
E 114
E 99
E 89
E 47
E 38
D 22
	if (REPLYTYPE(r) != 2)
E 22
I 22
D 134
	if (r < 0 || REPLYTYPE(r) != 2)
E 134
I 134
	if (r < 0 || REPLYTYPE(r) == 4)
E 134
E 22
D 49
		return (EX_TEMPFAIL);
E 49
I 49
D 76
		goto tempfail;
E 76
I 76
		goto tempfail1;
I 134
	if (REPLYTYPE(r) != 2)
		goto unavailable;
E 134
E 76
E 49
E 4
E 3
E 2

D 2
	return (f);
E 2
I 2
D 4
	if (Debug)
		printf("Connection open to %s\n", host);
E 4
I 4
	/*
I 5
	**  Send the HELO command.
D 20
	**	My mother taught me to always introduce myself, even
	**	if it is useless.
E 20
I 20
	**	My mother taught me to always introduce myself.
E 20
	*/

D 38
	smtpmessage("HELO %s", HostName);
	r = reply();
E 38
I 38
D 64
	smtpmessage("HELO %s", m, HostName);
E 64
I 64
D 81
	smtpmessage("HELO %s", m, MyHostName);
E 64
I 62
	SmtpPhase = "HELO wait";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, CurHostName, SmtpPhase);
E 71
E 62
D 80
	r = reply(m);
E 80
I 80
	r = reply(m, mci);
E 81
I 81
D 114
	smtpmessage("HELO %s", m, mci, MyHostName);
D 89
	mci->mci_phase = "HELO wait";
E 89
I 89
	SmtpPhase = mci->mci_phase = "HELO wait";
E 114
I 114
	if (bitnset(M_ESMTP, m->m_flags))
		mci->mci_flags |= MCIF_ESMTP;

tryhelo:
	if (bitset(MCIF_ESMTP, mci->mci_flags))
	{
		smtpmessage("EHLO %s", m, mci, MyHostName);
D 120
		SmtpPhase = mci->mci_phase = "EHLO wait";
E 120
I 120
		SmtpPhase = mci->mci_phase = "client EHLO";
E 120
	}
	else
	{
		smtpmessage("HELO %s", m, mci, MyHostName);
D 120
		SmtpPhase = mci->mci_phase = "HELO wait";
E 120
I 120
		SmtpPhase = mci->mci_phase = "client HELO";
E 120
	}
E 114
E 89
	setproctitle("%s %s: %s", e->e_id, CurHostName, mci->mci_phase);
D 89
	r = reply(m, mci, e);
E 89
I 89
D 99
	r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_helo);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_helo, helo_options);
E 114
E 99
E 89
E 81
E 80
E 38
D 22
	if (REPLYTYPE(r) == 5)
E 22
I 22
	if (r < 0)
D 49
		return (EX_TEMPFAIL);
E 49
I 49
D 76
		goto tempfail;
E 76
I 76
		goto tempfail1;
E 76
E 49
	else if (REPLYTYPE(r) == 5)
I 114
	{
		if (bitset(MCIF_ESMTP, mci->mci_flags))
		{
			/* try old SMTP instead */
			mci->mci_flags &= ~MCIF_ESMTP;
			goto tryhelo;
		}
E 114
E 22
D 49
		return (EX_UNAVAILABLE);
E 49
I 49
		goto unavailable;
I 114
	}
E 114
E 49
D 20
	if (REPLYTYPE(r) != 2)
E 20
I 20
	else if (REPLYTYPE(r) != 2)
E 20
D 49
		return (EX_TEMPFAIL);
E 49
I 49
D 76
		goto tempfail;
E 76
I 76
		goto tempfail1;
E 76
E 49

	/*
I 109
	**  Check to see if we actually ended up talking to ourself.
	**  This means we didn't know about an alias or MX, or we managed
	**  to connect to an echo server.
I 131
D 141
	**
	**	If this code remains at all, "CheckLoopBack" should be
	**	a mailer flag.  This is a MAYBENEXTRELEASE feature.
E 141
E 131
	*/

D 111
	p = strchr(SmtpReplyBuffer, ' ');
E 111
I 111
	p = strchr(&SmtpReplyBuffer[4], ' ');
E 111
	if (p != NULL)
D 121
		*p == '\0';
E 121
I 121
		*p = '\0';
E 121
D 111
	if (strcasecmp(SmtpReplyBuffer, MyHostName) == 0)
E 111
I 111
D 130
	if (strcasecmp(&SmtpReplyBuffer[4], MyHostName) == 0)
E 130
I 130
D 141
	if (CheckLoopBack && strcasecmp(&SmtpReplyBuffer[4], MyHostName) == 0)
E 141
I 141
	if (!bitnset(M_NOLOOPCHECK, m->m_flags) &&
	    strcasecmp(&SmtpReplyBuffer[4], MyHostName) == 0)
E 141
E 130
E 111
	{
		syserr("553 %s config error: mail loops back to myself",
			MyHostName);
		mci->mci_exitstat = EX_CONFIG;
		mci->mci_errno = 0;
		smtpquit(m, mci, e);
		return;
	}

	/*
E 109
I 28
	**  If this is expected to be another sendmail, send some internal
	**  commands.
	*/

D 43
	if (bitset(M_INTERNAL, m->m_flags))
E 43
I 43
	if (bitnset(M_INTERNAL, m->m_flags))
E 43
	{
		/* tell it to be verbose */
D 38
		smtpmessage("VERB");
		r = reply();
E 38
I 38
D 81
		smtpmessage("VERB", m);
D 80
		r = reply(m);
E 80
I 80
		r = reply(m, mci);
E 81
I 81
		smtpmessage("VERB", m, mci);
D 89
		r = reply(m, mci, e);
E 89
I 89
D 99
		r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
		r = reply(m, mci, e, TimeOuts.to_miscshort);
E 114
I 114
		r = reply(m, mci, e, TimeOuts.to_miscshort, NULL);
E 114
E 99
E 89
E 81
E 80
E 38
		if (r < 0)
D 49
			return (EX_TEMPFAIL);
E 49
I 49
D 76
			goto tempfail;
E 76
I 76
			goto tempfail2;
E 76
E 49
D 82

		/* tell it we will be sending one transaction only */
D 38
		smtpmessage("ONEX");
		r = reply();
E 38
I 38
D 81
		smtpmessage("ONEX", m);
D 80
		r = reply(m);
E 80
I 80
		r = reply(m, mci);
E 81
I 81
		smtpmessage("ONEX", m, mci);
		r = reply(m, mci, e);
E 81
E 80
E 38
		if (r < 0)
D 49
			return (EX_TEMPFAIL);
E 49
I 49
D 76
			goto tempfail;
E 76
I 76
			goto tempfail2;
E 82
E 76
E 49
	}

I 81
D 136
	mci->mci_state = MCIS_OPEN;
D 82
	return mci;
E 82
I 82
	return;
E 136
I 136
	if (mci->mci_state != MCIS_CLOSED)
	{
		mci->mci_state = MCIS_OPEN;
		return;
	}

	/* got a 421 error code during startup */
E 136
E 82

  tempfail1:
  tempfail2:
	mci->mci_exitstat = EX_TEMPFAIL;
D 89
	mci->mci_errno = errno;
	smtpquit(m, mci, e);
E 89
I 89
	if (mci->mci_errno == 0)
		mci->mci_errno = errno;
	if (mci->mci_state != MCIS_CLOSED)
		smtpquit(m, mci, e);
E 89
D 82
	mci->mci_state = MCIS_TEMPFAIL;
	return mci;
E 82
I 82
	return;
E 82

  unavailable:
	mci->mci_exitstat = EX_UNAVAILABLE;
	mci->mci_errno = errno;
	smtpquit(m, mci, e);
D 82
	mci->mci_state = MCIS_ERROR;
	return mci;
E 82
I 82
	return;
I 118
}
/*
**  ESMTP_CHECK -- check to see if this implementation likes ESMTP protocol
**
D 160
**
E 160
**	Parameters:
**		line -- the response line.
I 147
**		firstline -- set if this is the first line of the reply.
E 147
**		m -- the mailer.
**		mci -- the mailer connection info.
**		e -- the envelope.
**
**	Returns:
**		none.
*/

void
D 147
esmtp_check(line, m, mci, e)
E 147
I 147
esmtp_check(line, firstline, m, mci, e)
E 147
	char *line;
I 147
	bool firstline;
E 147
	MAILER *m;
	register MCI *mci;
	ENVELOPE *e;
{
D 147
	if (strlen(line) < 5)
		return;
	line += 4;
	if (strncmp(line, "ESMTP ", 6) == 0)
		mci->mci_flags |= MCIF_ESMTP;
E 147
I 147
D 160
	while ((line = strchr(++line, 'E')) != NULL)
E 160
I 160
D 174
	register char *l;

	for (l = line; (l = strchr(++l, 'E')) != NULL; )
E 160
	{
D 160
		if (strncmp(line, "ESMTP ", 6) == 0)
E 160
I 160
		if (strncmp(l, "ESMTP ", 6) == 0)
E 160
		{
			mci->mci_flags |= MCIF_ESMTP;
			break;
		}
	}
I 160
	for (l = line; (l = strchr(++l, '8')) != NULL; )
	{
		if (strncmp(l, "8BIT OK", 7) == 0)
		{
			mci->mci_flags |= MCIF_8BITOK;
			break;
		}
	}
E 174
I 174
	if (strstr(line, "ESMTP ") != NULL)
		mci->mci_flags |= MCIF_ESMTP;
D 179
	if (strstr(line, "8BIT OK") != NULL)
E 179
I 179
	if (strstr(line, "8BIT-OK") != NULL)
E 179
		mci->mci_flags |= MCIF_8BITOK;
E 174
E 160
E 147
E 118
E 82
}
I 114
/*
**  HELO_OPTIONS -- process the options on a HELO line.
**
**	Parameters:
**		line -- the response line.
I 147
**		firstline -- set if this is the first line of the reply.
E 147
**		m -- the mailer.
**		mci -- the mailer connection info.
**		e -- the envelope.
**
**	Returns:
**		none.
*/
E 114

I 114
void
D 147
helo_options(line, m, mci, e)
E 147
I 147
helo_options(line, firstline, m, mci, e)
E 147
	char *line;
I 147
	bool firstline;
E 147
	MAILER *m;
	register MCI *mci;
	ENVELOPE *e;
{
	register char *p;

I 147
D 150
	if (!firstline)
E 150
I 150
	if (firstline)
E 150
		return;

E 147
D 164
	if (strlen(line) < 5)
E 164
I 164
	if (strlen(line) < (SIZE_T) 5)
E 164
		return;
	line += 4;
	p = strchr(line, ' ');
	if (p != NULL)
		*p++ = '\0';
	if (strcasecmp(line, "size") == 0)
	{
		mci->mci_flags |= MCIF_SIZE;
		if (p != NULL)
			mci->mci_maxsize = atol(p);
	}
	else if (strcasecmp(line, "8bitmime") == 0)
I 139
	{
E 139
		mci->mci_flags |= MCIF_8BITMIME;
I 139
		mci->mci_flags &= ~MCIF_7BIT;
	}
E 139
	else if (strcasecmp(line, "expn") == 0)
		mci->mci_flags |= MCIF_EXPN;
I 144
D 146
	else if (strcasecmp(line, "dsn") == 0)
E 146
I 146
D 149
	else if (strcasecmp(line, "x-dsn-0") == 0)
E 149
I 149
D 160
	else if (strcasecmp(line, "x-dsn-1") == 0)
E 160
I 160
D 163
	else if (strcasecmp(line, "x-dsn-3") == 0)
E 163
I 163
	else if (strcasecmp(line, "x-dsn-03") == 0)
E 163
E 160
E 149
E 146
		mci->mci_flags |= MCIF_DSN;
E 144
}
/*
**  SMTPMAILFROM -- send MAIL command
**
**	Parameters:
**		m -- the mailer.
**		mci -- the mailer connection structure.
**		e -- the envelope (including the sender to specify).
*/

I 175
int
E 175
E 114
smtpmailfrom(m, mci, e)
	struct mailer *m;
D 82
	MCONINFO *mci;
E 82
I 82
	MCI *mci;
E 82
	ENVELOPE *e;
{
	int r;
I 138
	char *bufp;
I 146
	char *bodytype;
E 146
E 138
D 158
	char buf[MAXNAME];
E 158
I 158
	char buf[MAXNAME + 1];
E 158
I 114
	char optbuf[MAXLINE];
E 114
I 92

D 123
	if (tTd(17, 2))
E 123
I 123
	if (tTd(18, 2))
E 123
		printf("smtpmailfrom: CurHost=%s\n", CurHostName);
E 92

I 114
	/* set up appropriate options to include */
D 129
	if (bitset(MCIF_SIZE, mci->mci_flags))
E 129
I 129
	if (bitset(MCIF_SIZE, mci->mci_flags) && e->e_msgsize > 0)
E 129
		sprintf(optbuf, " SIZE=%ld", e->e_msgsize);
	else
		strcpy(optbuf, "");

I 140
D 146
	if (e->e_bodytype != NULL)
E 146
I 146
	bodytype = e->e_bodytype;
	if (bitset(MCIF_8BITMIME, mci->mci_flags))
E 146
	{
D 146
		if (bitset(MCIF_8BITMIME, mci->mci_flags))
E 146
I 146
		if (bodytype == NULL &&
		    bitset(MM_MIME8BIT, MimeMode) &&
		    bitset(EF_HAS8BIT, e->e_flags) &&
I 177
		    !bitset(EF_DONT_MIME, e->e_flags) &&
E 177
		    !bitnset(M_8BITS, m->m_flags))
			bodytype = "8BITMIME";
		if (bodytype != NULL)
E 146
		{
			strcat(optbuf, " BODY=");
D 146
			strcat(optbuf, e->e_bodytype);
E 146
I 146
			strcat(optbuf, bodytype);
E 146
		}
D 142
		else if (strcasecmp(e->e_bodytype, "7bit") != 0)
E 142
I 142
D 146
		else if (!bitset(MM_CVTMIME, MimeMode) &&
			 strcasecmp(e->e_bodytype, "7bit") != 0)
E 142
		{
			/* cannot just send a 7-bit version */
			usrerr("%s does not support 8BITMIME", mci->mci_host);
			return EX_DATAERR;
		}
E 146
	}
I 146
D 152
	else if (bitnset(M_8BITS, m->m_flags))
E 152
I 152
	else if (bitnset(M_8BITS, m->m_flags) ||
D 171
		 !bitset(EF_HAS8BIT, e->e_flags) ||
		 (e->e_bodytype != NULL &&
		  strcasecmp(e->e_bodytype, "7bit") == 0))
E 171
I 171
D 179
		 !bitset(EF_HAS8BIT, e->e_flags))
E 179
I 179
		 !bitset(EF_HAS8BIT, e->e_flags) ||
		 bitset(MCIF_8BITOK, mci->mci_flags))
E 179
E 171
E 152
	{
		/* just pass it through */
	}
I 173
#if MIME8TO7
E 173
	else if (bitset(MM_CVTMIME, MimeMode) &&
I 177
		 !bitset(EF_DONT_MIME, e->e_flags) &&
E 177
D 152
		 (e->e_bodytype == NULL ? !bitset(MM_PASS8BIT, MimeMode)
					: strcasecmp(e->e_bodytype, "7bit") != 0))
E 152
I 152
D 170
		 (e->e_bodytype != NULL || !bitset(MM_PASS8BIT, MimeMode)))
E 170
I 170
		 (!bitset(MM_PASS8BIT, MimeMode) ||
		  bitset(EF_IS_MIME, e->e_flags)))
E 170
E 152
	{
		/* must convert from 8bit MIME format to 7bit encoded */
		mci->mci_flags |= MCIF_CVT8TO7;
	}
I 173
#endif
E 173
	else if (!bitset(MM_PASS8BIT, MimeMode))
	{
		/* cannot just send a 8-bit version */
		usrerr("%s does not support 8BITMIME", mci->mci_host);
I 168
		mci->mci_status = "5.6.3";
E 168
		return EX_DATAERR;
	}
E 146

I 144
D 149
	if (e->e_envid != NULL && bitset(MCIF_DSN, mci->mci_flags))
E 149
I 149
	if (bitset(MCIF_DSN, mci->mci_flags))
E 149
	{
D 149
		strcat(optbuf, " ENVID=");
		strcat(optbuf, e->e_envid);
E 149
I 149
		if (e->e_envid != NULL)
		{
			strcat(optbuf, " ENVID=");
			strcat(optbuf, e->e_envid);
		}
I 160

		/* RET= parameter */
		if (bitset(EF_RET_PARAM, e->e_flags))
		{
			strcat(optbuf, " RET=");
			if (bitset(EF_NO_BODY_RETN, e->e_flags))
				strcat(optbuf, "HDRS");
			else
				strcat(optbuf, "FULL");
		}
E 160
D 155
		if (e->e_omts != NULL)
		{
			strcat(optbuf, " OMTS=");
			strcat(optbuf, e->e_omts);
		}
E 155
E 149
	}

E 144
E 140
E 114
E 81
	/*
E 28
I 14
	**  Send the HOPS command.
	**	This is non-standard and may give an "unknown command".
	**		This is not an error.
	**	It can give a "bad hop count" error if the hop
	**		count is exceeded.
	*/

	/*
E 14
E 5
	**  Send the MAIL command.
	**	Designates the sender.
	*/
E 4

D 4
	return (0);
E 4
I 4
D 10
	(void) expand("$g", buf, &buf[sizeof buf - 1]);
E 10
I 10
D 54
	expand("$g", buf, &buf[sizeof buf - 1], CurEnv);
E 54
I 54
D 75
	expand("\001g", buf, &buf[sizeof buf - 1], CurEnv);
E 75
I 75
D 81
	expand("\001<", buf, &buf[sizeof buf - 1], CurEnv);
E 75
E 54
E 10
D 18
	smtpmessage("MAIL From:<%s>", buf);
E 18
I 18
D 23
	smtpmessage("MAIL From: %s", canonname(buf));
E 23
I 23
D 24
	smtpmessage("MAIL From: <%s>", canonname(buf));
E 24
I 24
D 26
	smtpmessage("MAIL From:<%s>", canonname(buf));
E 26
I 26
D 27
	smtpmessage("MAIL From:<%s>", canonname(buf, 1));
E 27
I 27
	if (CurEnv->e_from.q_mailer == LocalMailer ||
E 81
I 81
	mci->mci_state = MCIS_ACTIVE;

D 97
	expand("\001<", buf, &buf[sizeof buf - 1], e);
E 97
I 97
D 103
	expand("\201<", buf, &buf[sizeof buf - 1], e);
E 103
I 103
D 115
	if (bitset(EF_RESPONSE, e->e_flags))
E 115
I 115
	if (bitset(EF_RESPONSE, e->e_flags) &&
	    !bitnset(M_NO_NULL_FROM, m->m_flags))
E 115
		(void) strcpy(buf, "");
	else
D 158
		expand("\201g", buf, &buf[sizeof buf - 1], e);
E 158
I 158
D 159
		expand("\201g", buf, &buf[sizeof buf], e);
E 159
I 159
		expand("\201g", buf, sizeof buf, e);
E 159
E 158
I 138
	if (buf[0] == '<')
	{
		/* strip off <angle brackets> (put back on below) */
		bufp = &buf[strlen(buf) - 1];
		if (*bufp == '>')
			*bufp = '\0';
		bufp = &buf[1];
	}
	else
		bufp = buf;
E 138
E 103
E 97
D 141
	if (e->e_from.q_mailer == LocalMailer ||
E 141
I 141
	if (bitnset(M_LOCALMAILER, e->e_from.q_mailer->m_flags) ||
E 141
E 81
D 38
	    !bitset(M_FULLSMTP, m->m_flags))
E 38
I 38
D 43
	    !bitset(M_FROMPATH, m->m_flags))
E 43
I 43
	    !bitnset(M_FROMPATH, m->m_flags))
E 43
E 38
	{
D 38
		smtpmessage("MAIL From:<%s>", canonname(buf, 1));
E 38
I 38
D 40
		smtpmessage("MAIL From:<%s>", m, canonname(buf, 1));
E 40
I 40
D 81
		smtpmessage("MAIL From:<%s>", m, buf);
E 81
I 81
D 114
		smtpmessage("MAIL From:<%s>", m, mci, buf);
E 114
I 114
D 138
		smtpmessage("MAIL From:<%s>%s", m, mci, buf, optbuf);
E 138
I 138
		smtpmessage("MAIL From:<%s>%s", m, mci, bufp, optbuf);
E 138
E 114
E 81
E 40
E 38
	}
	else
	{
D 38
		smtpmessage("MAIL From:<@%s%c%s>", HostName,
			    buf[0] == '@' ? ',' : ':', canonname(buf, 1));
E 38
I 38
D 64
		smtpmessage("MAIL From:<@%s%c%s>", m, HostName,
E 64
I 64
D 81
		smtpmessage("MAIL From:<@%s%c%s>", m, MyHostName,
E 81
I 81
D 114
		smtpmessage("MAIL From:<@%s%c%s>", m, mci, MyHostName,
E 81
E 64
D 40
			buf[0] == '@' ? ',' : ':', canonname(buf, 1));
E 40
I 40
			buf[0] == '@' ? ',' : ':', buf);
E 114
I 114
		smtpmessage("MAIL From:<@%s%c%s>%s", m, mci, MyHostName,
D 138
			buf[0] == '@' ? ',' : ':', buf, optbuf);
E 138
I 138
			*bufp == '@' ? ',' : ':', bufp, optbuf);
E 138
E 114
E 40
E 38
	}
I 62
D 81
	SmtpPhase = "MAIL wait";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, CurHostName, SmtpPhase);
E 71
E 62
E 27
E 26
E 24
E 23
E 18
D 38
	r = reply();
E 38
I 38
D 80
	r = reply(m);
E 80
I 80
	r = reply(m, mci);
E 81
I 81
D 89
	mci->mci_phase = "MAIL wait";
E 89
I 89
D 120
	SmtpPhase = mci->mci_phase = "MAIL wait";
E 120
I 120
	SmtpPhase = mci->mci_phase = "client MAIL";
E 120
E 89
	setproctitle("%s %s: %s", e->e_id, CurHostName, mci->mci_phase);
D 89
	r = reply(m, mci, e);
E 89
I 89
D 99
	r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_mail);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_mail, NULL);
E 114
E 99
E 89
E 81
E 80
E 38
D 22
	if (REPLYTYPE(r) == 4)
E 22
I 22
D 166
	if (r < 0 || REPLYTYPE(r) == 4)
E 166
I 166
	if (r < 0 || r == 421)
E 166
E 22
D 49
		return (EX_TEMPFAIL);
E 49
I 49
D 76
		goto tempfail;
E 76
I 76
D 81
		goto tempfail2;
E 81
I 81
	{
I 166
		/* communications failure/service shutting down */
E 166
		mci->mci_exitstat = EX_TEMPFAIL;
		mci->mci_errno = errno;
		smtpquit(m, mci, e);
D 82
		mci->mci_state = MCIS_TEMPFAIL;
E 82
		return EX_TEMPFAIL;
	}
I 166
	else if (REPLYTYPE(r) == 4)
	{
		return EX_TEMPFAIL;
	}
E 166
E 81
E 76
E 49
D 20
	if (r != 250)
		return (EX_SOFTWARE);
	return (EX_OK);
E 20
I 20
	else if (r == 250)
D 81
		return (EX_OK);
E 81
I 81
	{
D 153
		mci->mci_exitstat = EX_OK;
E 153
		return EX_OK;
	}
I 153
D 168
	else if (r == 501 || r == 553)
E 168
I 168
	else if (r == 501)
E 168
	{
D 166
		/* syntax error in arguments */
		smtpquit(m, mci, e);
E 166
I 166
D 168
		/* syntax error in arguments/mailbox name not allowed */
E 168
I 168
		/* syntax error in arguments */
		mci->mci_status = "5.5.2";
E 168
E 166
		return EX_DATAERR;
	}
I 168
	else if (r == 553)
	{
		/* mailbox name not allowed */
		mci->mci_status = "5.1.3";
		return EX_DATAERR;
	}
E 168
E 153
E 81
	else if (r == 552)
D 49
		return (EX_UNAVAILABLE);
E 49
I 49
D 81
		goto unavailable;
E 81
I 81
	{
D 166
		/* signal service unavailable */
D 153
		mci->mci_exitstat = EX_UNAVAILABLE;
E 153
		smtpquit(m, mci, e);
E 166
I 166
		/* exceeded storage allocation */
I 168
		mci->mci_status = "5.2.2";
E 168
E 166
D 82
		mci->mci_state = MCIS_ERROR;
E 82
		return EX_UNAVAILABLE;
	}
E 81

I 94
#ifdef LOG
D 95
	if (LogLevel >= 4)
E 95
I 95
	if (LogLevel > 1)
E 95
	{
D 143
		syslog(LOG_CRIT, "%s: SMTP MAIL protocol error: %s",
			e->e_id, SmtpReplyBuffer);
E 143
I 143
		syslog(LOG_CRIT, "%s: %s: SMTP MAIL protocol error: %s",
			e->e_id, mci->mci_host, SmtpReplyBuffer);
E 143
	}
#endif

E 94
	/* protocol error -- close up */
D 80
	smtpquit(m);
E 80
I 80
D 81
	smtpquit(m, mci);
E 80
E 49
D 21
	return (EX_SOFTWARE);
E 21
I 21
	return (EX_PROTOCOL);
I 49

D 77
	/* signal a temporary failure */
E 77
D 76
  tempfail:
E 76
I 76
  tempfail1:
D 77
#ifdef HOSTINFO
	{
		register STAB *st;
		extern STAB *stab();
E 77
I 77
	/* log this as an error to avoid sure-to-be-void connections */
D 79
	st = stab(CurHostName, ST_HOST, ST_ENTER);
E 79
I 79
D 80
	st = stab(CurHostName, ST_MCONINFO + m->m_mno, ST_ENTER);
E 79
	st->s_host.ho_exitstat = EX_TEMPFAIL;
	st->s_host.ho_errno = errno;
E 80
I 80
	mci->mci_exitstat = EX_TEMPFAIL;
	mci->mci_errno = errno;
E 80
E 77

D 77
		/* log this as an error to avoid sure-to-be-void connections */
		st = stab(CurHostName, ST_HOST, ST_ENTER);
		st->s_host.ho_exitstat = EX_TEMPFAIL;
		st->s_host.ho_errno = errno;
	}
#endif /* HOSTINFO */

E 77
  tempfail2:
I 77
	/* signal a temporary failure */
E 77
E 76
D 80
	smtpquit(m);
E 80
I 80
	smtpquit(m, mci);
E 80
I 55
D 65
	CurEnv->e_flags &= ~EF_FATALERRS;
E 65
E 55
	return (EX_TEMPFAIL);

D 77
	/* signal service unavailable */
E 77
  unavailable:
I 77
	/* signal service unavailable */
E 77
D 80
	smtpquit(m);
E 80
I 80
	smtpquit(m, mci);
E 80
	return (EX_UNAVAILABLE);
E 81
I 81
	smtpquit(m, mci, e);
D 153
	mci->mci_exitstat = EX_PROTOCOL;
E 153
D 82
	mci->mci_state = MCIS_ERROR;
E 82
	return EX_PROTOCOL;
E 81
E 49
I 47
}
D 89


static
greettimeout()
{
	/* timeout reading the greeting message */
	longjmp(CtxGreeting, 1);
E 47
E 21
E 20
E 4
E 2
}
E 89
/*
I 3
D 4
**	CLOSECONNECTION -- close the connection to the SMTP server.
E 4
I 4
D 5
**  SMTPMRCP -- designate recipient.
E 5
I 5
**  SMTPRCPT -- designate recipient.
E 5
E 4
**
D 4
**	This routine also sends a handshake.
**
E 4
**	Parameters:
D 4
**		none.
E 4
I 4
**		to -- address of recipient.
I 38
**		m -- the mailer we are sending to.
I 89
**		mci -- the connection info for this transaction.
**		e -- the envelope for this transaction.
E 89
E 38
E 4
**
**	Returns:
D 4
**		none.
E 4
I 4
**		exit status corresponding to recipient status.
E 4
**
**	Side Effects:
D 4
**		Closes the connection.
E 4
I 4
**		Sends the mail via SMTP.
E 4
*/

I 175
int
E 175
D 4
closeconnection()
E 4
I 4
D 5
smtpmrcp(to)
E 5
I 5
D 38
smtprcpt(to)
E 38
I 38
D 80
smtprcpt(to, m)
E 80
I 80
D 81
smtprcpt(to, m, mci)
E 81
I 81
smtprcpt(to, m, mci, e)
E 81
E 80
E 38
E 5
	ADDRESS *to;
I 38
	register MAILER *m;
I 80
D 82
	MCONINFO *mci;
E 82
I 82
	MCI *mci;
E 82
I 81
	ENVELOPE *e;
E 81
E 80
E 38
E 4
{
	register int r;
I 144
	char optbuf[MAXLINE];
I 168
	extern char *smtptodsn();
E 168
E 144
I 18
D 40
	extern char *canonname();
E 40
I 40
D 83
	extern char *remotename();
E 83
E 40
E 18

I 9
D 31
	if (SmtpPid < 0)
		return (SmtpErrstat);

E 31
E 9
D 4
	message("QUIT");
E 4
I 4
D 5
	smtpmessage("MRCP To:<%s>", to->q_user);
E 5
I 5
D 18
	smtpmessage("RCPT To:<%s>", to->q_user);
E 18
I 18
D 23
	smtpmessage("RCPT To: %s", canonname(to->q_user));
E 23
I 23
D 24
	smtpmessage("RCPT To: <%s>", canonname(to->q_user));
E 24
I 24
D 26
	smtpmessage("RCPT To:<%s>", canonname(to->q_user));
E 26
I 26
D 38
	smtpmessage("RCPT To:<%s>", canonname(to->q_user, 2));
E 38
I 38
D 40
	smtpmessage("RCPT To:<%s>", m, canonname(to->q_user, 2));
E 40
I 40
D 78
	smtpmessage("RCPT To:<%s>", m, remotename(to->q_user, m, FALSE, TRUE));
E 78
I 78
D 81
	smtpmessage("RCPT To:<%s>", m, to->q_user);
E 81
I 81
D 144
	smtpmessage("RCPT To:<%s>", m, mci, to->q_user);
E 144
I 144
	strcpy(optbuf, "");
	if (bitset(MCIF_DSN, mci->mci_flags))
	{
I 149
D 161
		bool firstone = TRUE;

E 161
I 151
		/* NOTIFY= parameter */
E 151
E 149
D 161
		strcat(optbuf, " NOTIFY=");
D 151
		if (bitset(QPINGONFAILURE, to->q_flags))
E 151
I 151
		if (bitset(QPINGONSUCCESS, to->q_flags))
E 161
I 161
D 162
		if (bitset(QHASNOTIFY, to->q_flags))
E 162
I 162
		if (bitset(QHASNOTIFY, to->q_flags) &&
		    bitset(QPRIMARY, to->q_flags))
E 162
E 161
E 151
		{
D 149
			if (bitset(QPINGONSUCCESS, to->q_flags))
				strcat(optbuf, "ALWAYS");
			else
				strcat(optbuf, "FAILURE");
E 149
I 149
D 151
			strcat(optbuf, "FAILURE");
E 151
I 151
D 161
			strcat(optbuf, "SUCCESS");
E 151
			firstone = FALSE;
E 161
I 161
			bool firstone = TRUE;

			strcat(optbuf, " NOTIFY=");
			if (bitset(QPINGONSUCCESS, to->q_flags))
			{
				strcat(optbuf, "SUCCESS");
				firstone = FALSE;
			}
			if (bitset(QPINGONFAILURE, to->q_flags))
			{
				if (!firstone)
					strcat(optbuf, ",");
				strcat(optbuf, "FAILURE");
				firstone = FALSE;
			}
			if (bitset(QPINGONDELAY, to->q_flags))
			{
				if (!firstone)
					strcat(optbuf, ",");
				strcat(optbuf, "DELAY");
				firstone = FALSE;
			}
			if (firstone)
				strcat(optbuf, "NEVER");
E 161
E 149
		}
D 149
		else
E 149
I 149
D 151
		if (bitset(QPINGONSUCCESS, to->q_flags))
E 151
I 151
D 161
		if (bitset(QPINGONFAILURE, to->q_flags))
E 151
E 149
		{
D 149
			if (bitset(QPINGONSUCCESS, to->q_flags))
				strcat(optbuf, "SUCCESS");
			else
				strcat(optbuf, "NEVER");
E 149
I 149
D 150
			if (firstone)
E 150
I 150
			if (!firstone)
E 150
				strcat(optbuf, ",");
D 151
			strcat(optbuf, "SUCCESS");
E 151
I 151
			strcat(optbuf, "FAILURE");
E 151
			firstone = FALSE;
E 149
		}
D 149
		if (bitset(QHASRETPARAM, to->q_flags))
E 149
I 149
		if (bitset(QPINGONDELAY, to->q_flags))
E 149
		{
I 149
D 150
			if (firstone)
E 150
I 150
			if (!firstone)
E 150
				strcat(optbuf, ",");
			strcat(optbuf, "DELAY");
			firstone = FALSE;
		}
		if (firstone)
			strcat(optbuf, "NEVER");
E 161
D 160

I 151
		/* RET= parameter */
E 151
		if (bitset(QHAS_RET_PARAM, to->q_flags))
		{
E 149
			strcat(optbuf, " RET=");
D 149
			if (bitset(QNOBODYRETURN, to->q_flags))
				strcat(optbuf, "NO");
E 149
I 149
			if (bitset(QRET_HDRS, to->q_flags))
				strcat(optbuf, "HDRS");
E 149
			else
D 149
				strcat(optbuf, "YES");
E 149
I 149
				strcat(optbuf, "FULL");
I 151
		}
E 160

		/* ORCPT= parameter */
		if (to->q_orcpt != NULL)
		{
			strcat(optbuf, " ORCPT=");
			strcat(optbuf, to->q_orcpt);
E 151
E 149
		}
	}
D 156
	else if (bitset(QPINGONSUCCESS, to->q_flags))
	{
		to->q_flags |= QRELAYED;
		fprintf(e->e_xfp, "%s... relayed; expect no further notifications\n",
			to->q_paddr);
	}
E 156
E 144
E 81
E 78
E 40
E 38
E 26
E 24
E 23
E 18
E 5

I 144
	smtpmessage("RCPT To:<%s>%s", m, mci, to->q_user, optbuf);

E 144
I 62
D 81
	SmtpPhase = "RCPT wait";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, CurHostName, SmtpPhase);
E 71
E 62
E 4
D 38
	r = reply();
E 38
I 38
D 80
	r = reply(m);
E 80
I 80
	r = reply(m, mci);
E 81
I 81
D 89
	mci->mci_phase = "RCPT wait";
E 89
I 89
D 120
	SmtpPhase = mci->mci_phase = "RCPT wait";
E 120
I 120
	SmtpPhase = mci->mci_phase = "client RCPT";
E 120
E 89
	setproctitle("%s %s: %s", e->e_id, CurHostName, mci->mci_phase);
D 89
	r = reply(m, mci, e);
E 89
I 89
D 99
	r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_rcpt);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_rcpt, NULL);
I 144
D 169
	setstatus(to, SmtpReplyBuffer);
E 169
I 169
	to->q_rstatus = newstr(SmtpReplyBuffer);
E 169
I 168
	to->q_status = smtptodsn(r);
E 168
E 144
E 114
E 99
E 89
E 81
E 80
E 38
I 4
D 22
	if (REPLYTYPE(r) == 4)
E 22
I 22
	if (r < 0 || REPLYTYPE(r) == 4)
E 22
D 168
		return (EX_TEMPFAIL);
E 168
I 168
		return EX_TEMPFAIL;
E 168
D 20
	if (r != 250)
E 20
I 20
D 21
	else if (REPLYCLASS(r) == 5)
E 20
		return (EX_NOUSER);
E 21
E 4
D 20

D 4
	if (Debug)
		printf("Closing connection, reply = %d\n", r);
E 4
I 4
	return (EX_OK);
E 20
I 20
	else if (REPLYTYPE(r) == 2)
D 168
		return (EX_OK);
E 168
I 168
		return EX_OK;
E 168
D 21
	return (EX_SOFTWARE);
E 21
I 21
	else if (r == 550 || r == 551 || r == 553)
D 168
		return (EX_NOUSER);
E 168
I 168
		return EX_NOUSER;
E 168
	else if (r == 552 || r == 554)
D 168
		return (EX_UNAVAILABLE);
E 168
I 168
		return EX_UNAVAILABLE;
E 168
I 94

#ifdef LOG
D 95
	if (LogLevel >= 4)
E 95
I 95
	if (LogLevel > 1)
E 95
	{
D 143
		syslog(LOG_CRIT, "%s: SMTP RCPT protocol error: %s",
			e->e_id, SmtpReplyBuffer);
E 143
I 143
		syslog(LOG_CRIT, "%s: %s: SMTP RCPT protocol error: %s",
			e->e_id, mci->mci_host, SmtpReplyBuffer);
E 143
	}
#endif

E 94
	return (EX_PROTOCOL);
E 21
E 20
E 4
}
/*
E 3
D 4
**  RUNSMTP -- run the SMTP protocol over connection.
E 4
I 4
D 38
**  SMTPFINISH -- finish up sending all the SMTP protocol.
E 38
I 38
**  SMTPDATA -- send the data and clean up the transaction.
E 38
E 4
**
**	Parameters:
D 4
**		fr -- from person.
**		tolist -- list of recipients.
E 4
I 4
**		m -- mailer being sent to.
D 10
**		editfcn -- a function to call to output the
**			text of the message with.
E 10
I 10
**		e -- the envelope for this message.
E 10
E 4
D 2
**		mf -- mail connection file.
E 2
**
**	Returns:
D 4
**		none.
E 4
I 4
D 5
**		exit status corresponding to DOIT command.
E 5
I 5
**		exit status corresponding to DATA command.
E 5
E 4
**
**	Side Effects:
D 4
**		Sends the mail via SMTP.
E 4
I 4
**		none.
E 4
*/

I 123
static jmp_buf	CtxDataTimeout;
I 126
D 157
static int	datatimeout();
E 157
I 157
static void	datatimeout();
E 157
E 126

I 175
int
E 175
E 123
I 3
D 4
# define REPLYTYPE(r)	((r) / 100)

E 3
D 2
runsmtp(fr, tolist, mf)
E 2
I 2
runsmtp(fr, tolist)
E 2
	char *fr;
	char **tolist;
E 4
I 4
D 10
smtpfinish(m, editfcn)
E 10
I 10
D 38
smtpfinish(m, e)
E 38
I 38
D 80
smtpdata(m, e)
E 80
I 80
smtpdata(m, mci, e)
E 80
E 38
E 10
	struct mailer *m;
I 80
D 82
	register MCONINFO *mci;
E 82
I 82
	register MCI *mci;
E 82
E 80
D 10
	int (*editfcn)();
E 10
I 10
	register ENVELOPE *e;
E 10
E 4
D 2
	FILE *mf;
E 2
{
	register int r;
I 123
	register EVENT *ev;
	time_t timeout;
I 124
D 125
	time_t mintimeout;
E 125
E 124
D 126
	static int datatimeout();
E 126
E 123
D 4
	register char **t;
	char buf[MAXLINE];
E 4

I 9
D 31
	if (SmtpPid < 0)
		return (SmtpErrstat);

E 31
E 9
D 3
	/* get greeting message */
E 3
I 3
	/*
D 4
	**  Get the greeting message.
	**	This should appear spontaneously.
	*/

E 3
D 2
	r = reply(mf);
E 2
I 2
	r = reply();
E 2
D 3
	if (r / 100 != 2)
E 3
I 3
	if (REPLYTYPE(r) != 2)
E 3
		return (EX_TEMPFAIL);

D 3
	/* send the mail command */
D 2
	fprintf(mf, "MAIL From:<%s>\r\n", fr);
	r = reply(mf);
E 2
I 2
	message("MAIL From:<%s>\r\n", fr);
E 3
I 3
	/*
	**  Send the MAIL command.
	**	Designates the sender.
	*/

	message("MAIL From:<%s>", fr);
E 3
	r = reply();
I 3
	if (REPLYTYPE(r) == 4)
		return (EX_TEMPFAIL);
E 3
E 2
	if (r != 250)
		return (EX_SOFTWARE);

D 3
	/* send the recipients */
E 3
I 3
	/*
	**  Send the recipients.
	*/

E 3
	for (t = tolist; *t != NULL; t++)
	{
D 2
		fprintf(mf, "MRCP To:<%s>\r\n", *t);
		r = reply(mf);
E 2
I 2
D 3
		message("MRCP To:<%s>\r\n", *t);
E 3
I 3
		message("MRCP To:<%s>", *t);
E 3
		r = reply();
I 3
		if (REPLYTYPE(r) == 4)
			return (EX_TEMPFAIL);
E 3
E 2
		if (r != 250)
			return (EX_NOUSER);
	}

D 3
	/* send the data */
D 2
	fprintf(mf, "DATA\r\n");
	r = reply(mf);
E 2
I 2
	message("DATA\r\n");
E 3
I 3
	/*
E 4
	**  Send the data.
D 38
	**	Dot hiding is done here.
E 38
I 38
	**	First send the command and check that it is ok.
	**	Then send the data.
	**	Follow it up with a dot to terminate.
	**	Finally get the results of the transaction.
E 38
	*/

D 4
	message("DATA");
E 4
I 4
D 38
	smtpmessage("DATA");
E 4
E 3
	r = reply();
E 38
I 38
	/* send the command and check ok to proceed */
D 81
	smtpmessage("DATA", m);
I 62
	SmtpPhase = "DATA wait";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, CurHostName, SmtpPhase);
E 71
E 62
D 80
	r = reply(m);
E 80
I 80
	r = reply(m, mci);
E 81
I 81
	smtpmessage("DATA", m, mci);
D 89
	mci->mci_phase = "DATA wait";
E 89
I 89
D 120
	SmtpPhase = mci->mci_phase = "DATA wait";
E 120
I 120
	SmtpPhase = mci->mci_phase = "client DATA 354";
E 120
E 89
	setproctitle("%s %s: %s", e->e_id, CurHostName, mci->mci_phase);
D 89
	r = reply(m, mci, e);
E 89
I 89
D 99
	r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_datainit);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_datainit, NULL);
E 114
E 99
E 89
E 81
E 80
E 38
I 3
D 22
	if (REPLYTYPE(r) == 4)
E 22
I 22
	if (r < 0 || REPLYTYPE(r) == 4)
I 93
	{
		smtpquit(m, mci, e);
E 93
E 22
		return (EX_TEMPFAIL);
I 93
	}
E 93
E 3
E 2
D 20
	if (r != 354)
E 20
I 20
	else if (r == 554)
I 93
	{
		smtprset(m, mci, e);
E 93
		return (EX_UNAVAILABLE);
I 93
	}
E 93
	else if (r != 354)
I 93
	{
I 94
#ifdef LOG
D 95
		if (LogLevel >= 4)
E 95
I 95
		if (LogLevel > 1)
E 95
		{
D 143
			syslog(LOG_CRIT, "%s: SMTP DATA-1 protocol error: %s",
				e->e_id, SmtpReplyBuffer);
E 143
I 143
			syslog(LOG_CRIT, "%s: %s: SMTP DATA-1 protocol error: %s",
				e->e_id, mci->mci_host, SmtpReplyBuffer);
E 143
		}
#endif
E 94
		smtprset(m, mci, e);
E 93
E 20
D 21
		return (EX_SOFTWARE);
E 21
I 21
		return (EX_PROTOCOL);
I 93
	}
E 93
E 21
D 4
	while (fgets(buf, sizeof buf, stdin) != NULL)
	{
		/* change trailing newline to crlf */
		register char *p = index(buf, '\n');

		if (p != NULL)
			*p = '\0';
D 3
		if (buf[0] == '.')
D 2
			fprintf(mf, ".");
		fprintf(mf, "%s\r\n", buf);
E 2
I 2
			message(".");
		message("%s\r\n", buf);
E 3
I 3
		message("%s%s", buf[0] == '.' ? "." : "", buf);
E 3
E 2
	}
D 2
	fprintf(mf, ".\r\n");
	r = reply(mf);
E 2
I 2
D 3
	message(".\r\n");
E 3
I 3
	message(".");
E 4
I 4
D 10
	(*editfcn)(SmtpOut, m, TRUE);
E 10
I 10
D 34
	(*e->e_puthdr)(SmtpOut, m, CurEnv);
	fprintf(SmtpOut, "\n");
D 32
	(*e->e_putbody)(SmtpOut, m, TRUE);
E 32
I 32
	(*e->e_putbody)(SmtpOut, m, TRUE, CurEnv);
E 34
I 34
D 38
	(*e->e_puthdr)(SmtpOut, m, CurEnv, TRUE);
	fprintf(SmtpOut, "\r\n");
	(*e->e_putbody)(SmtpOut, m, TRUE, CurEnv, TRUE);
E 34
E 32
E 10
	smtpmessage(".");
E 4
E 3
	r = reply();
E 38
I 38

I 124
	/*
	**  Set timeout around data writes.  Make it at least large
	**  enough for DNS timeouts on all recipients plus some fudge
	**  factor.  The main thing is that it should not be infinite.
	*/

E 124
I 123
	if (setjmp(CtxDataTimeout) != 0)
	{
		mci->mci_errno = errno;
		mci->mci_exitstat = EX_TEMPFAIL;
		mci->mci_state = MCIS_ERROR;
D 124
#ifdef LOG
		syslog(LOG_NOTICE, "%s: timeout writing message to %s",
			e->e_id, mci->mci_host);
#endif
E 124
		syserr("451 timeout writing message to %s", mci->mci_host);
		smtpquit(m, mci, e);
		return EX_TEMPFAIL;
	}

D 125
	timeout = e->e_msgsize / 64;
D 124
	if (timeout < (time_t) 60)
		timeout = 60;
E 124
I 124
	mintimeout = e->e_nrcpts * 90 + 60;
	if (timeout < mintimeout)
		timeout = mintimeout;
E 125
I 125
	timeout = e->e_msgsize / 16;
D 165
	if (timeout < (time_t) 60)
		timeout = (time_t) 60;
	timeout += e->e_nrcpts * 90;
E 165
I 165
	if (timeout < (time_t) 600)
		timeout = (time_t) 600;
	timeout += e->e_nrcpts * 300;
E 165
E 125
E 124
	ev = setevent(timeout, datatimeout, 0);

E 123
D 142
	/* now output the actual message */
D 80
	(*e->e_puthdr)(SmtpOut, m, CurEnv);
	putline("\n", SmtpOut, m);
	(*e->e_putbody)(SmtpOut, m, CurEnv);
E 80
I 80
D 81
	(*e->e_puthdr)(mci->mci_out, m, CurEnv);
E 81
I 81
D 139
	(*e->e_puthdr)(mci->mci_out, m, e);
E 81
	putline("\n", mci->mci_out, m);
D 81
	(*e->e_putbody)(mci->mci_out, m, CurEnv);
E 81
I 81
D 116
	(*e->e_putbody)(mci->mci_out, m, e);
E 116
I 116
	(*e->e_putbody)(mci->mci_out, m, e, NULL);
E 139
I 139
	(*e->e_puthdr)(mci, e);
	putline("\n", mci);
E 142
I 142
	/*
	**  Output the actual message.
	*/
D 146

	if (!bitset(MCIF_8BITMIME, mci->mci_flags) &&
I 145
	    !bitnset(M_8BITS, m->m_flags) &&
E 145
	    e->e_bodytype != NULL &&
	    strcasecmp(e->e_bodytype, "7bit") != 0)
	{
		/* must convert from 8bit MIME format to 7bit encoded */
		mci->mci_flags |= MCIF_CVT8TO7;
	}
E 146

D 148
	(*e->e_puthdr)(mci, e->e_header, e);
E 142
	(*e->e_putbody)(mci, e, NULL);
E 148
I 148
D 155
	(*e->e_puthdr)(mci, e->e_header, e, 0);
	(*e->e_putbody)(mci, e, NULL, 0);
E 155
I 155
	(*e->e_puthdr)(mci, e->e_header, e);
	(*e->e_putbody)(mci, e, NULL);
E 155
E 148
I 142

	/*
	**  Cleanup after sending message.
	*/
E 142
E 139
E 116
E 81
E 80

I 123
	clrevent(ev);

I 132
	if (ferror(mci->mci_out))
	{
		/* error during processing -- don't send the dot */
		mci->mci_errno = EIO;
		mci->mci_exitstat = EX_IOERR;
		mci->mci_state = MCIS_ERROR;
		smtpquit(m, mci, e);
		return EX_IOERR;
	}

E 132
E 123
	/* terminate the message */
D 39
	fprintf(SmtpOut, ".%s\n", bitset(M_CRLF, m->m_flags) ? "\r" : "");
	nmessage(Arpa_Info, ">>> .");
E 39
I 39
D 41
	fprintf(SmtpOut, ".%s", crlf(m));
E 41
I 41
D 80
	fprintf(SmtpOut, ".%s", m->m_eol);
E 80
I 80
	fprintf(mci->mci_out, ".%s", m->m_eol);
I 123
	if (TrafficLogFile != NULL)
		fprintf(TrafficLogFile, "%05d >>> .\n", getpid());
E 123
E 80
E 41
D 100
	if (Verbose && !HoldErrs)
E 100
I 100
	if (Verbose)
E 100
D 101
		nmessage(Arpa_Info, ">>> .");
E 101
I 101
		nmessage(">>> .");
E 101
E 39

	/* check for the results of the transaction */
I 62
D 81
	SmtpPhase = "result wait";
I 71
	setproctitle("%s %s: %s", CurEnv->e_id, CurHostName, SmtpPhase);
E 71
E 62
D 80
	r = reply(m);
E 80
I 80
	r = reply(m, mci);
E 80
E 38
I 3
D 22
	if (REPLYTYPE(r) == 4)
E 22
I 22
	if (r < 0 || REPLYTYPE(r) == 4)
E 81
I 81
D 89
	mci->mci_phase = "result wait";
E 89
I 89
D 120
	SmtpPhase = mci->mci_phase = "result wait";
E 120
I 120
	SmtpPhase = mci->mci_phase = "client DATA 250";
E 120
E 89
	setproctitle("%s %s: %s", e->e_id, CurHostName, mci->mci_phase);
D 89
	r = reply(m, mci, e);
E 89
I 89
D 99
	r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_datafinal);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_datafinal, NULL);
E 114
E 99
E 89
	if (r < 0)
I 93
	{
		smtpquit(m, mci, e);
E 93
E 81
E 22
		return (EX_TEMPFAIL);
I 93
	}
E 93
I 81
	mci->mci_state = MCIS_OPEN;
I 106
D 108
	e->e_message = newstr(&SmtpReplyBuffer[4]);
E 108
I 108
	e->e_statmsg = newstr(&SmtpReplyBuffer[4]);
E 108
E 106
	if (REPLYTYPE(r) == 4)
		return (EX_TEMPFAIL);
E 81
E 3
E 2
D 20
	if (r != 250)
		return (EX_SOFTWARE);
D 5

D 3
	/* force delivery */
D 2
	fprintf(mf, "DOIT\r\n");
	r = reply(mf);
E 2
I 2
	message("DOIT\r\n");
E 3
I 3
	/*
	**  Make the actual delivery happen.
	*/

D 4
	message("DOIT");
E 4
I 4
	smtpmessage("DOIT");
E 4
E 3
	r = reply();
E 2
	if (r != 250)
		return (EX_TEMPFAIL);

E 5
D 2
	fprintf(mf, "QUIT\r\n");
	r = reply(mf);
E 2
I 2
D 3
	message("QUIT\r\n");
	r = reply();
E 2
	if (r != 221)
		return (EX_SOFTWARE);

E 3
	return (EX_OK);
E 20
I 20
	else if (r == 250)
		return (EX_OK);
	else if (r == 552 || r == 554)
		return (EX_UNAVAILABLE);
I 94
#ifdef LOG
D 95
	if (LogLevel >= 4)
E 95
I 95
	if (LogLevel > 1)
E 95
	{
D 143
		syslog(LOG_CRIT, "%s: SMTP DATA-2 protocol error: %s",
			e->e_id, SmtpReplyBuffer);
E 143
I 143
		syslog(LOG_CRIT, "%s: %s: SMTP DATA-2 protocol error: %s",
			e->e_id, mci->mci_host, SmtpReplyBuffer);
E 143
	}
#endif
E 94
D 21
	return (EX_SOFTWARE);
E 21
I 21
	return (EX_PROTOCOL);
E 21
E 20
}
I 123


D 157
static int
E 157
I 157
static void
E 157
datatimeout()
{
	longjmp(CtxDataTimeout, 1);
}
E 123
/*
I 4
**  SMTPQUIT -- close the SMTP connection.
**
**	Parameters:
D 52
**		name -- name of mailer we are quitting.
E 52
I 52
**		m -- a pointer to the mailer.
E 52
I 13
D 31
**		showresp -- if set, give a response message.
E 31
E 13
**
**	Returns:
**		none.
**
**	Side Effects:
**		sends the final protocol and closes the connection.
*/

I 175
void
E 175
D 13
smtpquit(name)
E 13
I 13
D 31
smtpquit(name, showresp)
E 31
I 31
D 38
smtpquit(name)
E 38
I 38
D 52
smtpquit(name, m)
E 38
E 31
E 13
	char *name;
E 52
I 52
D 79
smtpquit(m)
E 52
I 38
	register MAILER *m;
E 79
I 79
D 80
smtpquit(mci)
E 80
I 80
D 81
smtpquit(mci, m)
E 80
	register MCONINFO *mci;
E 81
I 81
smtpquit(m, mci, e)
E 81
I 80
	register MAILER *m;
I 81
D 82
	register MCONINFO *mci;
E 82
I 82
	register MCI *mci;
E 82
	ENVELOPE *e;
E 81
E 80
E 79
E 38
I 13
D 31
	bool showresp;
E 31
E 13
{
D 31
	register int i;
E 31
I 31
D 135
	int i;
E 135
I 135
	bool oldSuprErrs = SuprErrs;
E 135
E 31

I 135
	/*
	**	Suppress errors here -- we may be processing a different
	**	job when we do the quit connection, and we don't want the 
	**	new job to be penalized for something that isn't it's
	**	problem.
	*/

	SuprErrs = TRUE;

E 135
D 9
	smtpmessage("QUIT");
	(void) reply();
	(void) fclose(SmtpIn);
	(void) fclose(SmtpOut);
	i = endmailer(SmtpPid, name);
E 9
I 9
D 31
	if (SmtpPid < 0)
E 31
I 31
D 36
	if (SmtpClosing)
	{
		SmtpClosing = FALSE;
E 36
I 36
D 82
	/* if the connection is already closed, don't bother */
D 79
	if (SmtpIn == NULL)
E 79
I 79
D 80
	if (mci->mci_state == MCI_CLOSED)
E 80
I 80
	if (mci->mci_state == MCIS_CLOSED)
E 80
E 79
E 36
E 31
D 13
	{
		i = SmtpErrstat;
	}
	else
	{
		smtpmessage("QUIT");
		(void) reply();
		(void) fclose(SmtpIn);
		(void) fclose(SmtpOut);
		i = endmailer(SmtpPid, name);
	}
E 9
	giveresponse(i, TRUE, LocalMailer);
E 13
I 13
		return;
I 36

	/* send the quit message if not a forced quit */
E 82
I 82
	/* send the quit message if we haven't gotten I/O error */
E 82
D 44
	if (!SmtpClosing)
E 44
I 44
D 80
	if (SmtpState == SMTP_OPEN || SmtpState == SMTP_SSD)
E 80
I 80
D 81
	if (mci->mci_state == MCIS_OPEN || mci->mci_state == MCIS_SSD)
E 81
I 81
	if (mci->mci_state != MCIS_ERROR)
E 81
E 80
E 44
	{
I 120
		SmtpPhase = "client QUIT";
E 120
D 38
		smtpmessage("QUIT");
		(void) reply();
E 38
I 38
D 81
		smtpmessage("QUIT", m);
D 80
		(void) reply(m);
E 38
I 37
D 44
		if (SmtpClosing)
E 44
I 44
		if (SmtpState == SMTP_CLOSED)
E 80
I 80
		(void) reply(m, mci);
E 81
I 81
		smtpmessage("QUIT", m, mci);
D 89
		(void) reply(m, mci, e);
E 89
I 89
D 99
		(void) reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
		(void) reply(m, mci, e, TimeOuts.to_quit);
E 114
I 114
		(void) reply(m, mci, e, TimeOuts.to_quit, NULL);
I 135
		SuprErrs = oldSuprErrs;
E 135
E 114
E 99
E 89
E 81
		if (mci->mci_state == MCIS_CLOSED)
I 135
		{
			SuprErrs = oldSuprErrs;
E 135
E 80
E 44
			return;
I 135
		}
E 135
E 37
E 36
I 31
	}

E 31
D 36
	smtpmessage("QUIT");
D 31
	(void) reply();
E 31
I 31
	i = reply();
	if (i != 221)
		syserr("smtpquit %s: reply %d", name, i);
E 36
I 36
D 79
	/* now actually close the connection */
E 36
E 31
	(void) fclose(SmtpIn);
	(void) fclose(SmtpOut);
I 36
	SmtpIn = SmtpOut = NULL;
I 44
	SmtpState = SMTP_CLOSED;
E 44

	/* and pick up the zombie */
E 36
D 52
	i = endmailer(SmtpPid, name);
E 52
I 52
	i = endmailer(SmtpPid, m->m_argv[0]);
E 79
I 79
	/* now actually close the connection and pick up the zombie */
D 105
	i = endmailer(mci, m->m_argv[0]);
E 105
I 105
D 135
	i = endmailer(mci, e, m->m_argv);
E 105
E 79
E 52
D 31
	if (showresp)
D 30
		giveresponse(i, TRUE, LocalMailer);
E 30
I 30
		giveresponse(i, LocalMailer);
E 31
I 31
	if (i != EX_OK)
D 52
		syserr("smtpquit %s: stat %d", name, i);
E 52
I 52
D 101
		syserr("smtpquit %s: stat %d", m->m_argv[0], i);
E 101
I 101
		syserr("451 smtpquit %s: stat %d", m->m_argv[0], i);
E 135
I 135
D 137
	(void) endmailer(mci, e, m->m_argv);
E 137
I 137
	(void) endmailer(mci, e, NULL);
E 137

	SuprErrs = oldSuprErrs;
E 135
E 101
E 52
E 31
E 30
E 13
}
/*
I 82
**  SMTPRSET -- send a RSET (reset) command
*/

I 175
void
E 175
smtprset(m, mci, e)
	register MAILER *m;
	register MCI *mci;
	ENVELOPE *e;
{
	int r;

I 120
	SmtpPhase = "client RSET";
E 120
	smtpmessage("RSET", m, mci);
D 89
	r = reply(m, mci, e);
E 89
I 89
D 91
	r = reply(m, mci, e, ReadTimeout);
E 89
	if (r < 0 || REPLYTYPE(r) == 4)
		return EX_TEMPFAIL;
E 91
I 91
D 99
	r = reply(m, mci, e, (time_t) 300);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_rset);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_rset, NULL);
E 114
E 99
	if (r < 0)
		mci->mci_state = MCIS_ERROR;
E 91
	else if (REPLYTYPE(r) == 2)
D 91
		return EX_OK;
	else
		return EX_PROTOCOL;
E 91
I 91
	{
		mci->mci_state = MCIS_OPEN;
		return;
	}
	smtpquit(m, mci, e);
E 91
}
/*
D 107
**  SMTPNOOP -- send a NOOP (no operation) command to check the connection state
E 107
I 107
**  SMTPPROBE -- check the connection state
E 107
*/

I 175
int
E 175
D 107
smtpnoop(mci)
E 107
I 107
smtpprobe(mci)
E 107
	register MCI *mci;
{
	int r;
	MAILER *m = mci->mci_mailer;
	extern ENVELOPE BlankEnvelope;
	ENVELOPE *e = &BlankEnvelope;

I 120
	SmtpPhase = "client probe";
E 120
D 107
	smtpmessage("NOOP", m, mci);
E 107
I 107
	smtpmessage("RSET", m, mci);
E 107
D 89
	r = reply(m, mci, e);
E 89
I 89
D 99
	r = reply(m, mci, e, ReadTimeout);
E 99
I 99
D 114
	r = reply(m, mci, e, TimeOuts.to_miscshort);
E 114
I 114
	r = reply(m, mci, e, TimeOuts.to_miscshort, NULL);
E 114
E 99
E 89
D 98
	if (REPLYTYPE(r) != 2)
E 98
I 98
	if (r < 0 || REPLYTYPE(r) != 2)
E 98
		smtpquit(m, mci, e);
	return r;
}
/*
E 82
E 4
**  REPLY -- read arpanet reply
**
**	Parameters:
D 2
**		mf -- mail file.
E 2
I 2
D 38
**		none.
E 38
I 38
**		m -- the mailer we are reading the reply from.
I 89
**		mci -- the mailer connection info structure.
**		e -- the current envelope.
**		timeout -- the timeout for reads.
I 114
D 172
**		pfunc -- processing function for second and subsequent
**			lines of response -- if null, no special
**			processing is done.
E 172
I 172
**		pfunc -- processing function called on each line of response.
**			If null, no special processing is done.
E 172
E 114
E 89
E 38
E 2
**
**	Returns:
**		reply code it reads.
**
**	Side Effects:
**		flushes the mail file.
*/

I 175
int
E 175
D 2
reply(mf)
	FILE *mf;
E 2
I 2
D 38
reply()
E 38
I 38
D 80
reply(m)
E 80
I 80
D 81
reply(mci, m)
	MCONINFO *mci;
E 81
I 81
D 89
reply(m, mci, e)
E 89
I 89
D 114
reply(m, mci, e, timeout)
E 114
I 114
reply(m, mci, e, timeout, pfunc)
E 114
E 89
E 81
E 80
I 43
	MAILER *m;
I 81
D 82
	MCONINFO *mci;
E 82
I 82
	MCI *mci;
E 82
	ENVELOPE *e;
I 114
	time_t timeout;
	void (*pfunc)();
E 114
E 81
E 43
E 38
E 2
{
I 109
D 110
	char *bufp = SmtpReplyBuffer;
E 110
I 110
	register char *bufp;
	register int r;
I 114
	bool firstline = TRUE;
E 114
E 110
	char junkbuf[MAXLINE];

E 109
D 2
	fflush(mf);
E 2
I 2
D 4
	fflush(OutConnection);
E 4
I 4
D 80
	(void) fflush(SmtpOut);
E 80
I 80
D 89
	(void) fflush(mci->mci_out);
E 89
I 89
	if (mci->mci_out != NULL)
		(void) fflush(mci->mci_out);
E 89
E 80
E 4
E 2

I 2
D 17
	if (Debug)
E 17
I 17
	if (tTd(18, 1))
E 17
		printf("reply\n");

E 2
D 15
	/* read the input line */
E 15
I 15
	/*
	**  Read the input line, being careful not to hang.
	*/

E 15
D 109
	for (;;)
E 109
I 109
D 110
	for (;; bufp = junkbuf)
E 110
I 110
	for (bufp = SmtpReplyBuffer;; bufp = junkbuf)
E 110
E 109
	{
D 31
		char buf[MAXLINE];
E 31
D 110
		register int r;
E 110
I 15
		register char *p;
I 81
		extern time_t curtime();
E 81
E 15

D 2
		if (fgets(buf, sizeof buf, mf) == NULL)
E 2
I 2
D 4
		if (fgets(buf, sizeof buf, InConnection) == NULL)
E 4
I 4
D 15
		if (fgets(buf, sizeof buf, SmtpIn) == NULL)
E 15
I 15
D 18
		/* arrange to time out the read */
E 18
I 18
		/* actually do the read */
E 18
I 16
D 17
		fflush(Xscript);			/* for debugging */
E 17
I 17
D 29
		(void) fflush(Xscript);			/* for debugging */
E 29
I 29
D 32
		if (Xscript != NULL)
			(void) fflush(Xscript);		/* for debugging */
E 32
I 32
D 81
		if (CurEnv->e_xfp != NULL)
			(void) fflush(CurEnv->e_xfp);	/* for debugging */
E 81
I 81
		if (e->e_xfp != NULL)
			(void) fflush(e->e_xfp);	/* for debugging */
E 81
E 32
E 29
E 17
E 16
D 18
		if (setjmp(TickFrame) != 0)
E 15
E 4
E 2
			return (-1);
I 15
		(void) alarm(ReadTimeout);
E 18
I 18
D 31
		p = sfgets(buf, sizeof buf, SmtpIn);
E 18
D 25

E 25
D 18
		/* actually do the read */
		p = fgets(buf, sizeof buf, SmtpIn);

		/* clean up timeout and check for errors */
		(void) alarm(0);
E 18
		if (p == NULL)
			return (-1);
I 25
		fixcrlf(buf, TRUE);
E 31
I 31
D 33
		if (!SmtpClosing)
		{
			p = sfgets(SmtpReplyBuffer, sizeof SmtpReplyBuffer, SmtpIn);
			if (p == NULL)
				return (-1);
			fixcrlf(SmtpReplyBuffer, TRUE);
		}
E 33
E 31
E 25

I 33
		/* if we are in the process of closing just give the code */
D 44
		if (SmtpClosing)
E 44
I 44
D 80
		if (SmtpState == SMTP_CLOSED)
E 80
I 80
		if (mci->mci_state == MCIS_CLOSED)
E 80
E 44
			return (SMTPCLOSING);

I 103
		if (mci->mci_out != NULL)
			fflush(mci->mci_out);

E 103
		/* get the line from the other side */
D 80
		p = sfgets(SmtpReplyBuffer, sizeof SmtpReplyBuffer, SmtpIn);
E 80
I 80
D 89
		p = sfgets(SmtpReplyBuffer, sizeof SmtpReplyBuffer, mci->mci_in);
E 89
I 89
D 109
		p = sfgets(SmtpReplyBuffer, sizeof SmtpReplyBuffer, mci->mci_in,
			   timeout);
E 109
I 109
D 120
		p = sfgets(bufp, MAXLINE, mci->mci_in, timeout);
E 120
I 120
		p = sfgets(bufp, MAXLINE, mci->mci_in, timeout, SmtpPhase);
E 120
E 109
E 89
I 81
		mci->mci_lastuse = curtime();

E 81
E 80
		if (p == NULL)
I 35
		{
I 123
			bool oldholderrs;
E 123
D 36
			syserr("reply: read error");
E 36
I 36
D 175
			extern char MsgBuf[];		/* err.c */
E 175
D 101
			extern char Arpa_TSyserr[];	/* conf.c */
E 101

I 57
			/* if the remote end closed early, fake an error */
			if (errno == 0)
# ifdef ECONNRESET
				errno = ECONNRESET;
D 84
# else ECONNRESET
E 84
I 84
# else /* ECONNRESET */
E 84
				errno = EPIPE;
D 84
# endif ECONNRESET
E 84
I 84
# endif /* ECONNRESET */
E 84

I 89
			mci->mci_errno = errno;
E 89
E 57
D 87
			message(Arpa_TSyserr, "reply: read error");
E 87
I 87
D 90
			message(Arpa_TSyserr, "reply: read error from %s",
E 90
I 90
			mci->mci_exitstat = EX_TEMPFAIL;
D 101
			message(Arpa_TSyserr, "%s: reply: read error from %s",
E 101
I 101
D 123
			message("451 %s: reply: read error from %s",
E 101
				e->e_id == NULL ? "NOQUEUE" : e->e_id,
E 90
				mci->mci_host);
E 123
I 123
			oldholderrs = HoldErrs;
			HoldErrs = TRUE;
			usrerr("451 reply: read error from %s", mci->mci_host);

E 123
E 87
I 42
D 70
# ifdef DEBUG
E 70
			/* if debugging, pause so we can see state */
			if (tTd(18, 100))
				pause();
D 70
# endif DEBUG
E 70
E 42
D 123
# ifdef LOG
D 56
			syslog(LOG_ERR, "%s", &MsgBuf[4]);
E 56
I 56
D 61
			syslog(LOG_MAIL, "%s", &MsgBuf[4]);
E 61
I 61
D 69
			syslog(LOG_ERR, "%s", &MsgBuf[4]);
E 69
I 69
D 87
			syslog(LOG_INFO, "%s", &MsgBuf[4]);
E 87
I 87
D 95
			if (LogLevel > 0)
E 95
I 95
			if (LogLevel > 1)
E 95
				syslog(LOG_INFO, "%s", &MsgBuf[4]);
E 87
E 69
E 61
E 56
D 84
# endif LOG
E 84
I 84
# endif /* LOG */
E 123
E 84
D 44
			SmtpClosing = TRUE;
E 44
I 44
D 80
			SmtpState = SMTP_CLOSED;
E 80
I 80
D 82
			mci->mci_state = MCIS_CLOSED;
E 82
I 82
			mci->mci_state = MCIS_ERROR;
E 82
E 80
E 44
D 38
			smtpquit("reply error");
E 38
I 38
D 52
			smtpquit("reply error", m);
E 52
I 52
D 81
			smtpquit(m);
E 81
I 81
			smtpquit(m, mci, e);
I 123
D 176
#ifdef XDEBUG
E 176
I 176
#if XDEBUG
E 176
			{
				char wbuf[MAXLINE];
D 128
				sprintf(wbuf, "%s... reply(%s) during %s",
					e->e_to, mci->mci_host, SmtpPhase);
E 128
I 128
				char *p = wbuf;
				if (e->e_to != NULL)
				{
					sprintf(p, "%s... ", e->e_to);
					p += strlen(p);
				}
				sprintf(p, "reply(%s) during %s",
					mci->mci_host, SmtpPhase);
E 128
				checkfd012(wbuf);
			}
#endif
			HoldErrs = oldholderrs;
E 123
E 81
E 52
E 38
E 36
E 35
			return (-1);
I 35
		}
E 35
D 109
		fixcrlf(SmtpReplyBuffer, TRUE);
E 109
I 109
		fixcrlf(bufp, TRUE);
E 109

E 33
D 48
		/* log the input in the transcript for future error returns */
E 48
I 48
D 81
		if (CurEnv->e_xfp != NULL && index("45", SmtpReplyBuffer[0]) != NULL)
E 81
I 81
D 84
		if (e->e_xfp != NULL && index("45", SmtpReplyBuffer[0]) != NULL)
E 84
I 84
D 110
		if (e->e_xfp != NULL && strchr("45", SmtpReplyBuffer[0]) != NULL)
E 110
I 110
D 123
		if (e->e_xfp != NULL && strchr("45", bufp[0]) != NULL)
E 123
I 123
		/* EHLO failure is not a real error */
		if (e->e_xfp != NULL && (bufp[0] == '4' ||
		    (bufp[0] == '5' && strncmp(SmtpMsgBuffer, "EHLO", 4) != 0)))
E 123
E 110
E 84
E 81
		{
			/* serious error -- log the previous command */
I 127
			if (SmtpNeedIntro)
			{
				/* inform user who we are chatting with */
				fprintf(CurEnv->e_xfp,
					"... while talking to %s:\n",
					CurHostName);
				SmtpNeedIntro = FALSE;
			}
E 127
D 109
			if (SmtpMsgBuffer[0] != '\0')
D 81
				fprintf(CurEnv->e_xfp, ">>> %s\n", SmtpMsgBuffer);
E 81
I 81
				fprintf(e->e_xfp, ">>> %s\n", SmtpMsgBuffer);
E 81
			SmtpMsgBuffer[0] = '\0';
E 109
I 109
D 110
			if (bufp[0] != '\0')
				fprintf(e->e_xfp, ">>> %s\n", bufp);
			bufp[0] = '\0';
E 110
I 110
			if (SmtpMsgBuffer[0] != '\0')
				fprintf(e->e_xfp, ">>> %s\n", SmtpMsgBuffer);
			SmtpMsgBuffer[0] = '\0';
E 110
E 109

			/* now log the message as from the other side */
D 81
			fprintf(CurEnv->e_xfp, "<<< %s\n", SmtpReplyBuffer);
E 81
I 81
D 109
			fprintf(e->e_xfp, "<<< %s\n", SmtpReplyBuffer);
E 109
I 109
			fprintf(e->e_xfp, "<<< %s\n", bufp);
E 109
E 81
		}

		/* display the input for verbose mode */
E 48
E 15
D 13
		if (Verbose)
E 13
I 13
D 100
		if (Verbose && !HoldErrs)
E 100
I 100
		if (Verbose)
E 100
E 13
D 25
			fputs(buf, stdout);
I 13
		fputs(buf, Xscript);
E 25
I 25
D 31
			nmessage(Arpa_Info, "%s", buf);
E 31
I 31
D 101
			nmessage(Arpa_Info, "%s", SmtpReplyBuffer);
E 101
I 101
D 109
			nmessage("%s", SmtpReplyBuffer);
E 109
I 109
D 117
			nmessage("%s", bufp);
E 117
I 117
			nmessage("050 %s", bufp);
E 117
I 114

		/* process the line */
D 147
		if (pfunc != NULL && !firstline)
			(*pfunc)(bufp, m, mci, e);
E 147
I 147
		if (pfunc != NULL)
			(*pfunc)(bufp, firstline, m, mci, e);
E 147

		firstline = FALSE;
E 114
E 109
E 101
E 31
D 29
		fprintf(Xscript, "%s\n", buf);
E 29
I 29
D 32
		if (Xscript != NULL)
D 31
			fprintf(Xscript, "%s\n", buf);
E 31
I 31
			fprintf(Xscript, "%s\n", SmtpReplyBuffer);
E 32
I 32
D 35
		if (CurEnv->e_xfp != NULL)
E 35
I 35
D 48
		else if (CurEnv->e_xfp != NULL)
E 35
			fprintf(CurEnv->e_xfp, "%s\n", SmtpReplyBuffer);
E 48
E 32
E 31
E 29
E 25
I 15

		/* if continuation is required, we can go on */
E 15
E 13
D 2
		if (buf[3] == '-')
E 2
I 2
D 31
		if (buf[3] == '-' || !isdigit(buf[0]))
E 31
I 31
D 97
		if (SmtpReplyBuffer[3] == '-' || !isdigit(SmtpReplyBuffer[0]))
E 97
I 97
D 109
		if (SmtpReplyBuffer[3] == '-' ||
		    !(isascii(SmtpReplyBuffer[0]) && isdigit(SmtpReplyBuffer[0])))
E 109
I 109
D 110
		if (bufp[3] == '-' ||
		    !(isascii(bufp[0]) && isdigit(bufp[0])))
E 110
I 110
		if (bufp[3] == '-')
E 110
E 109
E 97
E 31
E 2
			continue;
I 15

I 110
		/* ignore improperly formated input */
		if (!(isascii(bufp[0]) && isdigit(bufp[0])))
			continue;

E 110
		/* decode the reply code */
E 15
D 31
		r = atoi(buf);
E 31
I 31
D 110
		r = atoi(SmtpReplyBuffer);
E 110
I 110
		r = atoi(bufp);
E 110
E 31
I 15

		/* extra semantics: 0xx codes are "informational" */
E 15
D 110
		if (r < 100)
			continue;
E 110
I 110
		if (r >= 100)
			break;
	}
E 110
I 15

I 98
D 110
		/* save temporary failure messages for posterity */
		if (SmtpReplyBuffer[0] == '4' && SmtpError[0] == '\0')
			(void) strcpy(SmtpError, SmtpReplyBuffer);
E 110
I 110
	/*
	**  Now look at SmtpReplyBuffer -- only care about the first
	**  line of the response from here on out.
	*/
E 110

E 98
I 31
D 110
		/* reply code 421 is "Service Shutting Down" */
D 33
		if (r == SMTPCLOSING && !SmtpClosing)
E 33
I 33
D 44
		if (r == SMTPCLOSING)
E 44
I 44
D 80
		if (r == SMTPCLOSING && SmtpState != SMTP_SSD)
E 80
I 80
		if (r == SMTPCLOSING && mci->mci_state != MCIS_SSD)
E 80
E 44
E 33
		{
I 33
			/* send the quit protocol */
I 44
D 80
			SmtpState = SMTP_SSD;
E 80
I 80
			mci->mci_state = MCIS_SSD;
E 80
E 44
E 33
D 38
			smtpquit("SMTP Shutdown");
E 38
I 38
D 52
			smtpquit("SMTP Shutdown", m);
E 52
I 52
D 81
			smtpquit(m);
E 81
I 81
			smtpquit(m, mci, e);
E 81
E 52
E 38
D 44
			SmtpClosing = TRUE;
E 44
		}
E 110
I 110
	/* save temporary failure messages for posterity */
	if (SmtpReplyBuffer[0] == '4' && SmtpError[0] == '\0')
		(void) strcpy(SmtpError, SmtpReplyBuffer);
E 110
I 57
D 98

		/* save temporary failure messages for posterity */
		if (SmtpReplyBuffer[0] == '4' && SmtpError[0] == '\0')
D 96
			(void) strcpy(SmtpError, &SmtpReplyBuffer[4]);
E 96
I 96
			(void) strcpy(SmtpError, SmtpReplyBuffer);
E 98
E 96
E 57

E 31
E 15
D 110
		return (r);
E 110
I 110
	/* reply code 421 is "Service Shutting Down" */
	if (r == SMTPCLOSING && mci->mci_state != MCIS_SSD)
	{
		/* send the quit protocol */
		mci->mci_state = MCIS_SSD;
		smtpquit(m, mci, e);
E 110
	}
I 110

	return (r);
E 110
I 2
}
/*
D 4
**  MESSAGE -- send message to server
E 4
I 4
**  SMTPMESSAGE -- send message to server
E 4
**
**	Parameters:
**		f -- format
I 38
**		m -- the mailer to control formatting.
E 38
**		a, b, c -- parameters
**
**	Returns:
**		none.
**
**	Side Effects:
D 4
**		writes message to OutChannel.
E 4
I 4
D 80
**		writes message to SmtpOut.
E 80
I 80
**		writes message to mci->mci_out.
E 80
E 4
*/

D 4
message(f, a, b, c)
E 4
I 4
/*VARARGS1*/
I 175
void
E 175
D 38
smtpmessage(f, a, b, c)
E 38
I 38
D 80
smtpmessage(f, m, a, b, c)
E 80
I 80
D 85
smtpmessage(f, m, mci, a, b, c)
E 85
I 85
D 90
smtpmessage(f, m, mci VA_ARG_FORMAL)
E 90
I 90
#ifdef __STDC__
smtpmessage(char *f, MAILER *m, MCI *mci, ...)
#else
smtpmessage(f, m, mci, va_alist)
E 90
E 85
E 80
E 38
E 4
	char *f;
I 38
	MAILER *m;
I 80
D 82
	MCONINFO *mci;
E 82
I 82
	MCI *mci;
I 85
D 90
	VA_ARG_DECL
E 90
I 90
	va_dcl
#endif
E 90
E 85
E 82
E 80
E 38
{
D 45
	char buf[100];
E 45
I 45
D 48
	char buf[MAXLINE];
E 45

D 4
	sprintf(buf, f, a, b, c);
E 4
I 4
	(void) sprintf(buf, f, a, b, c);
E 48
I 48
D 85
	(void) sprintf(SmtpMsgBuffer, f, a, b, c);
E 85
I 85
	VA_LOCAL_DECL

D 86
	VA_START(f);
E 86
I 86
	VA_START(mci);
E 86
	(void) vsprintf(SmtpMsgBuffer, f, ap);
	VA_END;
I 103

E 103
E 85
E 48
E 4
I 3
D 12
	strcat(buf, "\r\n");
E 12
I 12
D 13
	(void) strcat(buf, "\r\n");
E 12
E 3
	if (Debug)
		fputs(buf, stdout);
D 4
	fputs(buf, OutConnection);
E 4
I 4
	fputs(buf, SmtpOut);
E 13
I 13
D 17
	if (Debug || (Verbose && !HoldErrs))
E 17
I 17
D 100
	if (tTd(18, 1) || (Verbose && !HoldErrs))
E 100
I 100
	if (tTd(18, 1) || Verbose)
E 100
E 17
D 25
		printf(">>> %s\n", buf);
	fprintf(Xscript, ">>> %s\n", buf);
E 25
I 25
D 48
		nmessage(Arpa_Info, ">>> %s", buf);
D 29
	fprintf(Xscript, " >>> %s\n", buf);
E 29
I 29
D 32
	if (Xscript != NULL)
		fprintf(Xscript, ">>> %s\n", buf);
E 32
I 32
D 35
	if (CurEnv->e_xfp != NULL)
E 35
I 35
	else if (CurEnv->e_xfp != NULL)
E 35
		fprintf(CurEnv->e_xfp, ">>> %s\n", buf);
E 48
I 48
D 101
		nmessage(Arpa_Info, ">>> %s", SmtpMsgBuffer);
E 101
I 101
		nmessage(">>> %s", SmtpMsgBuffer);
I 123
	if (TrafficLogFile != NULL)
		fprintf(TrafficLogFile, "%05d >>> %s\n", getpid(), SmtpMsgBuffer);
E 123
E 101
E 48
E 32
E 29
E 25
D 31
	fprintf(SmtpOut, "%s\r\n", buf);
E 31
I 31
D 44
	if (!SmtpClosing)
E 44
I 44
D 80
	if (SmtpOut != NULL)
E 44
D 38
		fprintf(SmtpOut, "%s\r\n", buf);
E 38
I 38
D 39
		fprintf(SmtpOut, "%s%s\n", bitset(M_CRLF, m->m_flags) ? "\r" : "", buf);
E 39
I 39
D 41
		fprintf(SmtpOut, "%s%s", buf, crlf(m));
E 41
I 41
D 48
		fprintf(SmtpOut, "%s%s", buf, m->m_eol);
E 48
I 48
D 72
		fprintf(SmtpOut, "%s%s", SmtpMsgBuffer, m->m_eol);
E 72
I 72
		fprintf(SmtpOut, "%s%s", SmtpMsgBuffer,
E 80
I 80
	if (mci->mci_out != NULL)
I 103
	{
E 103
		fprintf(mci->mci_out, "%s%s", SmtpMsgBuffer,
E 80
D 82
			m == 0 ? "\r\n" : m->m_eol);
E 82
I 82
			m == NULL ? "\r\n" : m->m_eol);
I 103
D 104
		(void) fflush(mci->mci_out);
		if (ferror(mci->mci_out))
			syserr("smtpmessage: ERROR mci_out");
E 104
	}
D 113
	else
E 113
I 113
	else if (tTd(18, 1))
E 113
I 104
	{
E 104
D 113
		syserr("smtpmessage: NULL mci_out");
E 113
I 113
		printf("smtpmessage: NULL mci_out\n");
E 113
I 104
	}
E 104
E 103
E 82
E 72
E 48
E 41
E 39
E 38
E 31
E 13
E 4
E 2
}
I 6

D 84
# endif SMTP
E 84
I 84
# endif /* SMTP */
E 84
E 6
E 1
