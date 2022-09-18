h58994
s 00002/00000/00606
d D 8.35 95/06/05 07:21:58 eric 130 129
c avoid infinite loops if malloc fails
e
s 00008/00004/00598
d D 8.34 95/05/28 11:49:36 eric 129 128
c lint
e
s 00001/00001/00601
d D 8.33 95/04/21 09:57:08 eric 128 127
c update copyright notice
e
s 00001/00003/00601
d D 8.32 95/03/31 10:51:56 eric 127 126
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00055/00008/00549
d D 8.31 95/03/31 09:05:32 eric 126 125
c buffer error messages during collect phase (better implementation)
e
s 00036/00014/00521
d D 8.30 94/10/16 11:09:33 eric 125 124
c avoid recursive calls to syserr if malloc fails
e
s 00000/00000/00535
d D 8.29 94/10/07 12:20:14 eric 124 123
x 123
c 
e
s 00002/00001/00534
d D 8.28 94/09/03 08:43:58 eric 123 122
c avoid dropping message submitted on stdin if the address resolves
c to a $#error address with a tempfail code
e
s 00002/00002/00533
d D 8.27 94/04/18 07:03:26 eric 122 121
c avoid using %m in syslog calls because it conflicts with HP-UX
e
s 00002/00002/00533
d D 8.26 94/03/11 14:42:00 eric 121 120
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00002/00000/00533
d D 8.25 94/03/07 12:10:28 eric 120 119
c fix CNAME loop problem: gave error messages and requeued messages
e
s 00001/00001/00532
d D 8.24 94/03/01 13:18:42 eric 119 118
c avoid having long "to" strinsg overflow the error message buffer
e
s 00005/00002/00528
d D 8.23 94/02/06 19:28:57 eric 118 117
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00017/00002/00513
d D 8.22 94/02/06 09:33:31 eric 117 116
c log user name on SYSERRs, since these can have security implications
e
s 00001/00001/00514
d D 8.21 94/02/03 08:07:53 eric 116 115
c restore -ba mode for UK Grey book
e
s 00009/00009/00506
d D 8.20 94/01/15 12:38:54 eric 115 114
c Unicos portability changes
e
s 00002/00002/00513
d D 8.19 94/01/08 17:29:17 eric 114 113
c fix problem that was causing the ctladdr of whoever ran the daemon
c (usually root) to own the delivery process
e
s 00022/00004/00493
d D 8.18 93/12/17 07:05:43 eric 113 112
c fix botch with Name server: error codes
e
s 00004/00004/00493
d D 8.17 93/12/16 07:24:42 eric 112 111
c always include host name on DNS-related errors
e
s 00006/00004/00491
d D 8.16 93/12/10 17:30:18 eric 111 110
c improve error messages -- avoid "Error 0" syndrome
e
s 00000/00002/00495
d D 8.15 93/11/08 09:46:05 eric 110 109
c general portability changes
e
s 00006/00007/00491
d D 8.14 93/10/29 20:19:27 eric 109 108
c fix to error handling -- set error flags even if HoldErrs set
c (this reverts to previous behaviour, except sets Errors on 6xx codes)
e
s 00007/00006/00491
d D 8.13 93/10/28 19:39:29 eric 108 107
c Errors++ any time an error message is actually printed
e
s 00003/00000/00494
d D 8.12 93/10/21 07:18:53 eric 107 106
c allow dumping of MCI cache to syslog for debugging
e
s 00002/00000/00492
d D 8.11 93/10/17 10:00:10 eric 106 105
c additional debugging information for too many open files problem
e
s 00005/00001/00487
d D 8.10 93/10/03 07:08:35 eric 105 104
c always prefer fatal error messages rather than temp error messages
e
s 00008/00003/00480
d D 8.9 93/09/19 19:22:19 eric 104 103
c avoid syserr on final 221 message; this can occur if the other end
c closes prematurely
e
s 00004/00000/00479
d D 8.8 93/08/14 11:30:40 eric 103 102
c add debugging to putoutmsg
e
s 00002/00001/00477
d D 8.7 93/08/06 21:18:40 eric 102 101
c fix null pointer reference in syslog message
e
s 00007/00004/00471
d D 8.6 93/07/22 11:27:53 eric 101 100
c fix bogus error message with open timeout in :include: -- this also
c fixes a bug that caused resolver errnos to conflict with real errnos
e
s 00005/00001/00470
d D 8.5 93/07/21 11:45:45 eric 100 99
c old 4.3BSD changes
e
s 00018/00004/00453
d D 8.4 93/07/17 13:48:18 eric 99 98
c allow 6xx codes to mean "warnings sent to postmaster"
e
s 00005/00007/00452
d D 8.3 93/07/16 10:28:36 eric 98 97
c clean up error handling, including concept of local error handling
e
s 00010/00007/00449
d D 8.2 93/07/11 06:52:33 eric 97 96
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00454
d D 8.1 93/06/07 10:30:21 bostic 96 95
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00020/00432
d D 6.23 93/05/25 19:04:28 eric 95 94
c try to improve closed connection error handling
e
s 00008/00006/00444
d D 6.22 93/05/24 12:50:16 eric 94 93
c don't go into recursive syserr loop if error printing syserr
e
s 00004/00000/00446
d D 6.21 93/05/22 10:05:02 eric 93 92
c avoid writing an error message announcing that you can't write the
c message
e
s 00002/00001/00444
d D 6.20 93/05/21 18:58:42 eric 92 91
c pessimize on channel flushing
e
s 00008/00008/00437
d D 6.19 93/05/17 10:56:16 eric 91 90
c type conflicts
e
s 00002/00004/00443
d D 6.18 93/05/17 10:28:13 eric 90 89
c first cut at merged map/alias implementation
e
s 00001/00001/00446
d D 6.17 93/05/04 20:43:01 eric 89 88
c fix some bogus messages being printed in mailq command
e
s 00002/00001/00445
d D 6.16 93/05/03 12:23:59 eric 88 87
c improve error logging on OutChannel I/O errors
e
s 00006/00000/00440
d D 6.15 93/04/30 15:15:50 eric 87 86
c clean up error message printing, especially for deferred messages
e
s 00002/00003/00438
d D 6.14 93/04/30 12:54:37 eric 86 85
c fix comment on message()
e
s 00005/00000/00436
d D 6.13 93/04/18 10:07:17 eric 85 84
c Extended Load Average (XLA) hooks
e
s 00005/00000/00431
d D 6.12 93/04/13 17:36:03 eric 84 83
c check for I/O errors on OutChannel
e
s 00002/00002/00429
d D 6.11 93/03/26 07:45:05 eric 83 82
c portability
e
s 00002/00002/00429
d D 6.10 93/03/26 06:59:07 eric 82 81
c fix problem with prototype mismatches
e
s 00004/00000/00427
d D 6.9 93/03/23 18:06:30 eric 81 80
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00013/00001/00414
d D 6.8 93/03/17 10:35:22 eric 80 79
c attempts to handle ENFILE conditions better
e
s 00001/00001/00414
d D 6.7 93/03/06 10:52:57 eric 79 78
c don't automatically print errno in usrerr -- it can be too misleading
e
s 00009/00014/00406
d D 6.6 93/02/23 06:31:38 eric 78 77
c overhaul status of SMTP reply codes
e
s 00001/00001/00419
d D 6.5 93/02/16 18:29:57 eric 77 76
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00011/00003/00409
d D 6.4 93/02/15 16:44:51 eric 76 75
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00002/00000/00410
d D 6.3 93/01/28 10:15:47 eric 75 74
c System 5 compatibility, misc fixes
e
s 00024/00008/00386
d D 6.2 93/01/21 15:18:36 eric 74 73
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00000/00000/00394
d D 6.1 92/12/21 16:08:25 eric 73 72
c Release 6
e
s 00001/00001/00393
d D 5.17 92/12/20 11:14:19 eric 72 71
c change random constants to be #defines
e
s 00033/00015/00361
d D 5.16 92/11/16 17:52:16 eric 71 70
c make it use varargs/stdarg and vsprintf
e
s 00003/00003/00373
d D 5.15 92/11/14 11:34:15 eric 70 69
c (partially) ANSI-fy it
e
s 00001/00001/00375
d D 5.14 92/01/18 07:57:19 eric 69 68
c drop mode a (ARPA FTP) -- NCP is gone forever.....
e
s 00003/00003/00373
d D 5.13 92/01/05 09:21:34 eric 68 67
c clean up #ifdef configuration to more cleanly match the modern age
e
s 00007/00000/00369
d D 5.12 91/12/15 13:59:36 eric 67 66
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00003/00001/00366
d D 5.11 91/03/02 17:15:23 bostic 66 65
c ANSI
e
s 00001/00011/00366
d D 5.10 90/06/01 19:01:46 bostic 65 64
c new copyright notice
e
s 00011/00009/00366
d D 5.9 88/06/30 14:58:58 bostic 64 63
c install approved copyright notice
e
s 00016/00010/00359
d D 5.8 88/03/13 19:52:05 bostic 63 62
c add Berkeley specific header
e
s 00005/00000/00364
d D 5.7 85/11/22 11:29:06 miriam 62 61
m 
c Errstring() now will print out a message for the Name Server error 
c code TRY_AGAIN - "Host Name Lookup Failure".
e
s 00003/00003/00361
d D 5.6 85/10/24 10:35:47 eric 61 60
m 
c don't create a queue name in syserr; permit trailing blanks and quoted
c commas in aliases.
e
s 00006/00007/00358
d D 5.5 85/09/30 21:34:09 eric 60 59
m 
c clean up some aspects of error message display
e
s 00000/00000/00365
d D 5.4 85/09/19 01:25:11 eric 59 57
i 58
m 
c incorporate SMI changes -- still experimental
e
s 00048/00003/00317
d D 5.2.1.1 85/09/19 00:55:18 eric 58 56
m 
c SMI changes (somewhat)
e
s 00001/00001/00319
d D 5.3 85/09/17 19:21:38 eric 57 56
m 
c facilities in syslog
e
s 00000/00002/00320
d D 5.2 85/06/07 22:10:35 miriam 56 55
m 
c Resolve duplicate SccsId
e
s 00014/00000/00308
d D 5.1 85/06/07 15:05:31 dist 55 54
m 
c Add copyright
e
s 00001/00001/00307
d D 4.6 85/04/04 17:41:52 miriam 54 53
m 
c Change LOG_ERR to LOG_MAIL
e
s 00003/00003/00305
d D 4.5 84/08/11 18:07:28 eric 53 52
m 
c fix typo
e
s 00013/00009/00295
d D 4.4 84/08/11 17:55:36 eric 52 51
m 
c changes from Tom Ferrin <ucsfcgl!tef>: don't drop messages on the floor
c if no local mailer available; give real "errno" message in syserr.
e
s 00030/00006/00274
d D 4.3 83/10/01 16:56:52 eric 51 50
m 
c clean up error handling in general; make sure that something gets logged
c in the transcript if the connection cannot be established; clean up Teus
c Hagen's mod to arpadate.c to match the sendmail coding style.
e
s 00003/00003/00277
d D 4.2 83/09/05 14:33:32 eric 50 49
m 
c Cut down the amount of bulk that is sent in SMTP error messages, by
c trying to log only real errors in the transcript.  -v mode is unchanged.
e
s 00000/00000/00280
d D 4.1 83/07/25 19:42:54 eric 49 48
m 
c 4.2 release version
e
s 00001/00001/00279
d D 3.40 83/01/05 10:18:42 eric 48 47
m 
c improve error recovery for bizarre SMTP cases; unfortunately CMU has
c decided to start working again, so the strangest parts are untested.
e
s 00001/00001/00279
d D 3.39 83/01/01 16:02:35 eric 47 46
m 
c tag syserr's specially in the log so they can be grep'ed out easily
e
s 00002/00002/00278
d D 3.38 82/12/05 13:45:37 eric 46 45
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00024/00012/00256
d D 3.37 82/11/28 16:00:43 eric 45 44
m 
c implement SMTP auto-shutdown on 421 codes; clean up some error processing
c items, particularly in SMTP; don't reinstantiate error message bodies after
c queueing; other minor changes.  This is all cleanup from 3.253.
e
s 00008/00000/00260
d D 3.36 82/11/28 00:20:29 eric 44 43
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00001/00001/00259
d D 3.35 82/11/24 18:43:48 eric 43 42
m 
c lint it
e
s 00002/00002/00258
d D 3.34 82/11/24 17:14:55 eric 42 41
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00002/00002/00258
d D 3.33 82/11/17 09:35:38 eric 41 40
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00002/00001/00258
d D 3.32 82/11/13 17:54:17 eric 40 39
m 071
c avoid printing out extra messages when the transcript is not instantiated
e
s 00009/00006/00250
d D 3.31 82/11/07 16:14:35 eric 39 38
m 041
c make all mailer output go to the transcript if running server smtp; this
c has the effect of making some significant changes in the output structure
c to handle such things as -em and -as together
e
s 00040/00006/00216
d D 3.30 82/09/21 10:13:30 eric 38 37
c add nmessage (to not add "to..." tag); improve handling of error
c status setting
e
s 00008/00002/00214
d D 3.29 82/08/29 15:52:11 eric 37 36
c give 554 message on syserr (instead of 451) if errno == 0; as it
c was some permanent errors appeared transient
e
s 00002/00001/00214
d D 3.28 82/08/22 19:02:46 eric 36 35
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00006/00000/00209
d D 3.27 82/08/15 17:33:02 eric 35 34
c make VRFY and EXPN work more correctly (VRFY still gives an OK even
c if the target is a list); this adds the QuickAbort option
e
s 00003/00006/00206
d D 3.26 82/08/08 01:02:15 eric 34 33
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00027/00008/00185
d D 3.25 82/07/31 16:57:08 eric 33 32
c arrange to print errno properly in syserr's
e
s 00013/00025/00180
d D 3.24 82/07/25 13:11:14 eric 32 31
c clean up error handling
e
s 00002/00000/00203
d D 3.23 82/06/25 19:38:19 eric 31 30
c add debugging information to server smtp code: _debug to set
c Debug, _verbose to set verbose, and _showq to show the send queue
c (already existant, just a name change)
e
s 00001/00001/00202
d D 3.22 82/06/07 07:54:39 eric 30 29
c make transcripts verbose always; misc. message cleanup, etc.
e
s 00002/00002/00201
d D 3.21 82/05/31 15:36:03 eric 29 28
c don't output SMTP/FTP error codes in transcript file
e
s 00002/00002/00201
d D 3.20 82/05/22 01:37:13 eric 28 27
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00002/00000/00201
d D 3.19 82/03/06 12:08:52 eric 27 26
c clean up error handling in IPC case; fix a minor bug in headers in
c queueing code; make SMTP mail multi user per connect.
e
s 00006/00004/00195
d D 3.18 81/12/06 13:30:17 eric 26 25
c increase buffer sizes (it's so embarrasing when the error routines
c core dump) and strip quote bits from messages.
e
s 00001/00001/00198
d D 3.17 81/12/06 12:38:05 eric 25 24
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00002/00001/00197
d D 3.16 81/11/08 17:26:27 eric 24 23
c LINT
e
s 00001/00001/00197
d D 3.15 81/11/07 15:41:14 eric 23 22
c clean up to compile & work on ARPAVAX; move stat file to
c /usr/lib/sendmail.st; fix bug in syserr with error codes
e
s 00083/00041/00115
d D 3.14 81/10/31 22:12:15 eric 22 21
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00003/00005/00153
d D 3.13 81/10/26 14:21:58 eric 21 20
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00009/00001/00149
d D 3.12 81/10/22 09:14:25 eric 20 19
c implement HELP and MRSQ -- MRSQ is a partial implementation
c of old MTP -- in particular, To: fields in MAIL commands are not yet
c implemented.  The "message" routine now takes first args of the form
c "999-" to specify continuation.
e
s 00009/00009/00141
d D 3.11 81/10/19 22:26:52 eric 19 18
c implement SMTP mode -- doesn't support source routing or the
c HELP command, and doesn't give the correct code on VRFY or forwarding.
c Maybe someday....
e
s 00001/00001/00149
d D 3.10 81/09/06 19:48:17 eric 18 17
c cleanup, commenting, linting, etc.
e
s 00000/00002/00150
d D 3.9 81/08/20 15:13:48 eric 17 16
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00005/00002/00147
d D 3.8 81/08/18 17:12:44 eric 16 15
c factor out ARPANET FTP reply codes into conf.c
e
s 00005/00003/00144
d D 3.7 81/08/18 16:47:04 eric 15 14
c convert to really do arpanet reply codes right (maybe)
e
s 00015/00014/00132
d D 3.6 81/08/09 15:02:27 eric 14 13
c lint it
e
s 00003/00001/00143
d D 3.5 81/08/09 12:25:53 eric 13 12
c use <crlf> in arpanet mode
e
s 00056/00009/00088
d D 3.4 81/08/08 13:51:35 eric 12 11
c give arpanet-style error messages on -a
e
s 00002/00002/00095
d D 3.3 81/03/20 09:44:56 eric 11 10
c change name (again); from postbox to sendmail
e
s 00002/00001/00095
d D 3.2 81/03/07 15:32:23 eric 10 9
c lint fixes
e
s 00002/00002/00094
d D 3.1 81/03/07 14:26:23 eric 9 8
c ----- delivermail ==> postbox -----
e
s 00002/00002/00094
d D 2.3 81/02/28 11:50:33 eric 8 7
c install VAX mpx file logging
e
s 00002/00000/00094
d D 2.2 81/01/10 12:07:27 eric 7 6
c flush output after printing errors   just   in    case
e
s 00000/00000/00094
d D 2.1 80/11/05 11:00:24 eric 6 5
c release 2
e
s 00001/00001/00093
d D 1.5 80/10/21 22:39:39 eric 5 4
c EX_UNAVAIL => EX_UNAVAILABLE
e
s 00006/00006/00088
d D 1.4 80/10/18 16:48:53 eric 4 3
c cleanup for dbm stuff: Error => Errors; move local host
c detection into parse; misc cleanup
e
s 00000/00014/00094
d D 1.3 80/08/02 13:48:59 eric 3 2
c cleaned up comments
e
s 00002/00000/00106
d D 1.2 80/07/25 22:03:38 eric 2 1
c add ID keywords
e
s 00106/00000/00000
d D 1.1 80/06/23 08:24:06 eric 1 0
e
u
U
f b 
f i 
t
T
I 55
/*
I 64
D 128
 * Copyright (c) 1983 Eric P. Allman
E 128
I 128
 * Copyright (c) 1983, 1995 Eric P. Allman
E 128
E 64
D 63
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 63
I 63
D 96
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 96
I 96
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 96
 *
D 65
 * Redistribution and use in source and binary forms are permitted
D 64
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 64
I 64
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
E 65
I 65
 * %sccs.include.redist.c%
E 65
E 64
 */
E 63

#ifndef lint
D 63
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 63
I 63
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 63

E 55
I 1
D 17
# include <stdio.h>
I 12
# include <ctype.h>
E 17
E 12
D 9
# include "dlvrmail.h"
E 9
I 9
D 11
# include "postbox.h"
E 11
I 11
# include "sendmail.h"
I 58
# include <errno.h>
I 62
D 127
# include <netdb.h>
I 117
# include <pwd.h>
E 127
E 117
E 62
E 58
E 11
E 9
D 34
# ifdef LOG
D 8
# include <log.h>
E 8
I 8
# include <syslog.h>
E 8
# endif LOG
E 34

I 2
D 25
static char	SccsId[] = "%W%	%G%";
E 25
I 25
D 56
SCCSID(%W%	%Y%	%G%);
E 25

E 56
I 15
D 21
extern bool	HasXscrpt;

E 21
E 15
E 2
/*
D 4
**  ERR -- Print error message.
E 4
I 4
**  SYSERR -- Print error message.
E 4
**
**	Prints an error message via printf to the diagnostic
**	output.  If LOG is defined, it logs it also.
**
I 80
**	If the first character of the syserr message is `!' it will
**	log this as an ALERT message and exit immediately.  This can
**	leave queue files in an indeterminate state, so it should not
**	be used lightly.
**
E 80
**	Parameters:
D 125
**		f -- the format string
**		a, b, c, d, e -- parameters
E 125
I 125
**		fmt -- the format string.  If it does not begin with
**			a three-digit SMTP reply code, either 554 or
**			451 is assumed depending on whether errno
**			is set.
**		(others) -- parameters
E 125
**
**	Returns:
D 14
**		-1 always
E 14
I 14
**		none
I 35
**		Through TopFrame if QuickAbort is set.
E 35
E 14
**
**	Side Effects:
D 4
**		Sets Error.
**		Sets ExitStat.
E 4
I 4
**		increments Errors.
**		sets ExitStat.
E 4
D 3
**
**	Requires:
**		sprintf (sys)
**		printf (sys)
**		logmsg
**
**	History:
**		12/29/79 -- written.
E 3
*/

I 14
D 98
# ifdef lint
int	sys_nerr;
char	*sys_errlist[];
# endif lint
E 98
I 32
D 48
static char	MsgBuf[BUFSIZ*2];	/* text of most recent message */
E 48
I 48
D 126
char	MsgBuf[BUFSIZ*2];	/* text of most recent message */
E 126
I 126
char	MsgBuf[BUFSIZ*2];		/* text of most recent message */
char	HeldMessageBuf[sizeof MsgBuf];	/* for held messages */
E 126
E 48
E 32

I 66
D 100
static void fmtmsg();
E 100
I 100
D 129
static void	fmtmsg();
E 129
I 129
extern void	putoutmsg __P((char *, bool, bool));
extern void	puterrmsg __P((char *));
static void	fmtmsg __P((char *, const char *, const char *, int, const char *, va_list));
E 129

D 121
#if defined(NAMED_BIND) && !defined(NO_DATA)
E 121
I 121
#if NAMED_BIND && !defined(NO_DATA)
E 121
# define NO_DATA	NO_ADDRESS
#endif
E 100

I 82
void
E 82
E 66
E 14
/*VARARGS1*/
D 71
syserr(fmt, a, b, c, d, e)
E 71
I 71
D 74
syserr(fmt VA_ARG_FORMAL)
E 74
I 74
#ifdef __STDC__
I 81
D 82
void
E 82
E 81
D 91
syserr(char *fmt, ...)
E 91
I 91
syserr(const char *fmt, ...)
E 91
#else
syserr(fmt, va_alist)
E 74
E 71
D 91
	char *fmt;
E 91
I 91
	const char *fmt;
E 91
I 71
D 74
	VA_ARG_DECL
E 74
I 74
	va_dcl
#endif
E 74
E 71
{
I 52
	register char *p;
	int olderrno = errno;
I 80
	bool panic;
I 117
#ifdef LOG
	char *uname;
	struct passwd *pw;
	char ubuf[80];
#endif
E 117
E 80
I 71
	VA_LOCAL_DECL
E 71
E 52
D 14
	extern int errno;
E 14
D 26
	static char errbuf[MAXLINE+1];
E 26
I 26
D 32
	static char errbuf[2*BUFSIZ];
E 32
E 26
D 14
	register char *p;
E 14
D 22
	extern char *sys_errlist[];
	extern int sys_nerr;
I 10
D 14
	extern char *sprintf();
E 14
I 12
	register char *eb = errbuf;
E 22
I 16
D 37
	extern char Arpa_Syserr[];
E 37
I 37
D 78
	extern char Arpa_PSyserr[];
	extern char Arpa_TSyserr[];
E 78
D 52
	register char *p;
E 52
E 37
I 32
D 34
	char *saveto = CurEnv->e_to;
E 34
E 32
E 16
E 12
E 10

I 80
	panic = *fmt == '!';
	if (panic)
		fmt++;

E 80
D 12
	sprintf(errbuf, fmt, a, b, c, d, e);
E 12
I 12
D 22
	/* add arpanet error number if not present */
	if (!isdigit(*fmt))
	{
D 14
		strcpy(eb, "455 ");
E 14
I 14
D 16
		(void) strcpy(eb, "455 ");
E 16
I 16
		(void) strcpy(eb, Arpa_Syserr);
		eb[3] = ' ';
E 16
E 14
		eb += 4;
	}
E 22
I 22
D 32
	/* format the error message */
D 23
	fmtmsg(errbuf, Arpa_Syserr, NULL, fmt, a, b, c, d, e);
E 23
I 23
D 24
	fmtmsg(errbuf, NULL, Arpa_Syserr, fmt, a, b, c, d, e);
E 24
I 24
	fmtmsg(errbuf, (char *) NULL, Arpa_Syserr, fmt, a, b, c, d, e);
E 32
I 32
	/* format and output the error message */
D 33
	CurEnv->e_to = NULL;
	message(Arpa_Syserr, fmt, a, b, c, d, e);
	CurEnv->e_to = saveto;
E 33
I 33
D 34
	fmtmsg(MsgBuf, NULL, Arpa_Syserr, fmt, a, b, c, d, e);
E 34
I 34
D 37
	fmtmsg(MsgBuf, (char *) NULL, Arpa_Syserr, fmt, a, b, c, d, e);
E 37
I 37
D 52
	if (errno == 0)
E 52
I 52
	if (olderrno == 0)
E 52
D 78
		p = Arpa_PSyserr;
E 78
I 78
		p = "554";
E 78
	else
D 78
		p = Arpa_TSyserr;
E 78
I 78
		p = "451";
E 78
D 52
	fmtmsg(MsgBuf, (char *) NULL, p, fmt, a, b, c, d, e);
E 52
I 52
D 71
	fmtmsg(MsgBuf, (char *) NULL, p, olderrno, fmt, a, b, c, d, e);
E 71
I 71
	VA_START(fmt);
	fmtmsg(MsgBuf, (char *) NULL, p, olderrno, fmt, ap);
	VA_END;
E 71
E 52
E 37
E 34
D 39
	putmsg(MsgBuf);
E 39
I 39
D 45
	putmsg(MsgBuf, HoldErrs);
E 45
I 45
	puterrmsg(MsgBuf);
E 45
E 39
E 33
E 32
E 24
E 23
E 22

I 125
	/* save this message for mailq printing */
	if (!panic)
	{
		if (CurEnv->e_message != NULL)
			free(CurEnv->e_message);
		CurEnv->e_message = newstr(MsgBuf + 4);
	}

E 125
D 22
	/* put error message into buffer */
D 14
	sprintf(eb, fmt, a, b, c, d, e);
E 14
I 14
	(void) sprintf(eb, fmt, a, b, c, d, e);
E 14
E 12
	if (errno != 0)
E 22
I 22
D 32
	/* output error message to transcript */
D 29
	fprintf(Xscript, "%s\n", errbuf);
E 29
I 29
	fprintf(Xscript, "%s\n", &errbuf[4]);
E 29

	/* output error message to output channel if appropriate */
	if (!HoldErrs)
E 22
	{
I 31
		(void) fflush(stdout);
E 31
D 12
		p = &errbuf[strlen(errbuf)];
E 12
I 12
D 22
		eb += strlen(eb);
E 12
		if (errno < sys_nerr && errno > 0)
D 12
			sprintf(p, ": %s", sys_errlist[errno]);
E 12
I 12
D 14
			sprintf(eb, ": %s", sys_errlist[errno]);
E 14
I 14
			(void) sprintf(eb, ": %s", sys_errlist[errno]);
E 22
I 22
		if (ArpaMode)
			fprintf(OutChannel, "%s\r\n", errbuf);
E 22
E 14
E 12
		else
D 12
			sprintf(p, ": error %d", errno);
E 12
I 12
D 14
			sprintf(eb, ": error %d", errno);
E 14
I 14
D 22
			(void) sprintf(eb, ": error %d", errno);
E 22
I 22
			fprintf(OutChannel, "sendmail: %s\n", &errbuf[4]);
		(void) fflush(OutChannel);
E 22
E 14
E 12
	}
D 9
	printf("delivermail: %s\n", errbuf);
E 9
I 9
D 11
	printf("postbox: %s\n", errbuf);
E 11
I 11
D 12
	printf("sendmail: %s\n", errbuf);
E 12
I 12

E 32
I 32
D 38
	/* mark the error as having occured */
E 32
D 15
	if (ArpaFmt)
E 15
I 15
D 21
	if (ArpaMode != ARPA_NONE && !HasXscrpt)
E 21
I 21
D 22
	if (ArpaMode != ARPA_NONE && Transcript == NULL)
E 21
E 15
D 13
		printf("%s\n", errbuf);
E 13
I 13
D 19
		printf("%s\r\n", errbuf);
E 19
I 19
		fprintf(OutChannel, "%s\r\n", errbuf);
E 19
E 13
	else
D 19
		printf("sendmail: %s\n", &errbuf[4]);
E 12
E 11
E 9
I 7
D 14
	fflush(stdout);
E 14
I 14
	(void) fflush(stdout);
E 19
I 19
		fprintf(OutChannel, "sendmail: %s\n", &errbuf[4]);
	(void) fflush(OutChannel);
E 22
E 19
E 14
E 7
D 4
	Error++;
E 4
I 4
	Errors++;
I 27
	FatalErrors = TRUE;
E 27
E 4

E 38
	/* determine exit status if not already set */
	if (ExitStat == EX_OK)
	{
D 52
		if (errno == 0)
E 52
I 52
		if (olderrno == 0)
E 52
			ExitStat = EX_SOFTWARE;
		else
D 5
			ExitStat = EX_UNAVAIL;
E 5
I 5
			ExitStat = EX_OSERR;
I 120
		if (tTd(54, 1))
			printf("syserr: ExitStat = %d\n", ExitStat);
E 120
E 5
	}

I 44
D 61
	/* insure that we have a queue id for logging */
E 44
I 36
	(void) queuename(CurEnv, '\0');
E 61
E 36
# ifdef LOG
I 117
D 127
	pw = getpwuid(getuid());
E 127
I 127
	pw = sm_getpwuid(getuid());
E 127
	if (pw != NULL)
		uname = pw->pw_name;
	else
	{
		uname = ubuf;
		sprintf(ubuf, "UID%d", getuid());
	}

E 117
D 8
	logmsg(LOG_ERR, "%s->%s: %s", From.q_paddr, To, errbuf);
E 8
I 8
D 18
	syslog(LOG_ERR, "%s->%s: %s", From.q_paddr, To, errbuf);
E 18
I 18
D 28
	syslog(LOG_ERR, "%s->%s: %s", From.q_paddr, To, &errbuf[4]);
E 28
I 28
D 32
	syslog(LOG_ERR, "%s->%s: %s", CurEnv->e_from.q_paddr, CurEnv->e_to, &errbuf[4]);
E 32
I 32
D 34
	syslog(LOG_ERR, "%s->%s: %s", CurEnv->e_from.q_paddr, CurEnv->e_to, &MsgBuf[4]);
E 34
I 34
	if (LogLevel > 0)
D 36
		syslog(LOG_ERR, "%s: %s", MsgId, &MsgBuf[4]);
E 36
I 36
D 47
		syslog(LOG_ERR, "%s: %s", CurEnv->e_id, &MsgBuf[4]);
E 47
I 47
D 54
		syslog(LOG_ERR, "%s: SYSERR: %s", CurEnv->e_id, &MsgBuf[4]);
E 54
I 54
D 57
		syslog(LOG_MAIL, "%s: SYSERR: %s", CurEnv->e_id, &MsgBuf[4]);
E 57
I 57
D 61
		syslog(LOG_CRIT, "%s: SYSERR: %s", CurEnv->e_id, &MsgBuf[4]);
E 61
I 61
D 80
		syslog(LOG_CRIT, "%s: SYSERR: %s",
E 80
I 80
D 117
		syslog(panic ? LOG_ALERT : LOG_CRIT, "%s: SYSERR: %s",
E 117
I 117
		syslog(panic ? LOG_ALERT : LOG_CRIT, "%s: SYSERR(%s): %s",
E 117
E 80
			CurEnv->e_id == NULL ? "NOQUEUE" : CurEnv->e_id,
D 117
			&MsgBuf[4]);
E 117
I 117
			uname, &MsgBuf[4]);
E 117
E 61
E 57
E 54
E 47
E 36
E 34
E 32
E 28
E 18
E 8
D 70
# endif LOG
E 70
I 70
# endif /* LOG */
I 106
	if (olderrno == EMFILE)
I 107
	{
E 107
		printopenfds(TRUE);
I 107
		mci_dump_all(TRUE);
	}
E 107
E 106
I 80
	if (panic)
I 85
	{
#ifdef XLA
		xla_all_end();
#endif
I 130
		if (tTd(0, 1))
			abort();
E 130
E 85
		exit(EX_OSERR);
I 85
	}
E 85
E 80
E 70
	errno = 0;
I 35
	if (QuickAbort)
		longjmp(TopFrame, 2);
E 35
D 14
	return (-1);
E 14
}
/*
**  USRERR -- Signal user error.
**
**	This is much like syserr except it is for user errors.
**
**	Parameters:
D 125
**		fmt, a, b, c, d -- printf strings
E 125
I 125
**		fmt -- the format string.  If it does not begin with
**			a three-digit SMTP reply code, 501 is assumed.
**		(others) -- printf strings
E 125
**
**	Returns:
D 14
**		-1
E 14
I 14
**		none
I 35
**		Through TopFrame if QuickAbort is set.
E 35
E 14
**
**	Side Effects:
D 4
**		sets Error.
E 4
I 4
**		increments Errors.
E 4
D 3
**
**	Requires:
**		printf (sys)
**
**	History:
**		1/1/80 -- written.
E 3
*/

/*VARARGS1*/
D 71
usrerr(fmt, a, b, c, d, e)
E 71
I 71
D 74
usrerr(fmt VA_ARG_FORMAL)
E 74
I 74
D 82
#ifdef __STDC__
E 82
I 81
void
I 82
#ifdef __STDC__
E 82
E 81
D 91
usrerr(char *fmt, ...)
E 91
I 91
usrerr(const char *fmt, ...)
E 91
#else
usrerr(fmt, va_alist)
E 74
E 71
D 91
	char *fmt;
E 91
I 91
	const char *fmt;
E 91
I 71
D 74
	VA_ARG_DECL
E 74
I 74
	va_dcl
#endif
E 74
E 71
{
I 71
	VA_LOCAL_DECL
E 71
D 110
	extern char SuprErrs;
I 16
D 78
	extern char Arpa_Usrerr[];
E 78
I 52
	extern int errno;
E 110
E 52
E 16

	if (SuprErrs)
D 10
		return;
E 10
I 10
D 14
		return (0);
E 14
I 14
		return;
E 14
E 10
D 12

E 12
D 4
	Error++;
E 4
I 4
D 38
	Errors++;
I 27
	FatalErrors = TRUE;
E 38
E 27
E 4
D 12
	if (To != NULL)
E 12
I 12

D 16
	message("450", fmt, a, b, c, d, e);
E 16
I 16
D 33
	message(Arpa_Usrerr, fmt, a, b, c, d, e);
E 33
I 33
D 52
	fmtmsg(MsgBuf, CurEnv->e_to, Arpa_Usrerr, fmt, a, b, c, d, e);
E 52
I 52
D 71
	fmtmsg(MsgBuf, CurEnv->e_to, Arpa_Usrerr, errno, fmt, a, b, c, d, e);
E 71
I 71
	VA_START(fmt);
D 78
	fmtmsg(MsgBuf, CurEnv->e_to, Arpa_Usrerr, errno, fmt, ap);
E 78
I 78
D 79
	fmtmsg(MsgBuf, CurEnv->e_to, "501", errno, fmt, ap);
E 79
I 79
	fmtmsg(MsgBuf, CurEnv->e_to, "501", 0, fmt, ap);
E 79
E 78
	VA_END;
E 71
E 52
D 39
	putmsg(MsgBuf);
E 39
I 39
D 45
	putmsg(MsgBuf, HoldErrs);
E 45
I 45
	puterrmsg(MsgBuf);
E 45
E 39
I 38

I 125
	/* save this message for mailq printing */
	if (MsgBuf[0] == '5' || (CurEnv->e_message == NULL && MsgBuf[0] == '4'))
	{
		if (CurEnv->e_message != NULL)
			free(CurEnv->e_message);
		CurEnv->e_message = newstr(MsgBuf + 4);
	}

E 125
I 67
# ifdef LOG
D 77
	if (LogLevel > 1 && LogUsrErrs)
E 77
I 77
	if (LogLevel > 3 && LogUsrErrs)
E 77
		syslog(LOG_NOTICE, "%s: %s",
			CurEnv->e_id == NULL ? "NOQUEUE" : CurEnv->e_id,
			&MsgBuf[4]);
D 70
# endif LOG
E 70
I 70
# endif /* LOG */
E 70

E 67
E 38
I 35
	if (QuickAbort)
		longjmp(TopFrame, 1);
E 35
E 33
E 16
D 14
	return (-1);
E 14
}
/*
**  MESSAGE -- print message (not necessarily an error)
**
**	Parameters:
D 86
**		num -- the default ARPANET error number (in ascii)
**		msg -- the message (printf fmt) -- if it begins
**			with a digit, this number overrides num.
E 86
I 86
**		msg -- the message (printf fmt) -- it can begin with
**			an SMTP reply code.  If not, 050 is assumed.
E 86
D 125
**		a, b, c, d, e -- printf arguments
E 125
I 125
**		(others) -- printf arguments
E 125
**
**	Returns:
**		none
**
**	Side Effects:
**		none.
*/

I 14
/*VARARGS2*/
E 14
D 71
message(num, msg, a, b, c, d, e)
	register char *num;
	register char *msg;
E 71
I 71
D 74
message(num, msg VA_ARG_FORMAL)
E 74
I 74
D 83
#ifdef __STDC__
E 83
I 81
void
I 83
#ifdef __STDC__
E 83
E 81
D 78
message(char *num, char *msg, ...)
E 78
I 78
D 91
message(char *msg, ...)
E 91
I 91
message(const char *msg, ...)
E 91
E 78
#else
D 78
message(num, msg, va_alist)
E 74
	char *num;
E 78
I 78
message(msg, va_alist)
E 78
D 91
	char *msg;
E 91
I 91
	const char *msg;
E 91
D 74
	VA_ARG_DECL
E 74
I 74
	va_dcl
#endif
E 74
E 71
{
I 71
	VA_LOCAL_DECL

E 71
D 22
	/* compute error number */
	if (isdigit(*msg))
E 22
I 22
D 26
	char errbuf[MAXLINE];
E 26
I 26
D 32
	char errbuf[2*BUFSIZ];
E 26

E 32
	errno = 0;
D 28
	fmtmsg(errbuf, To, num, msg, a, b, c, d, e);
E 28
I 28
D 32
	fmtmsg(errbuf, CurEnv->e_to, num, msg, a, b, c, d, e);
E 32
I 32
D 52
	fmtmsg(MsgBuf, CurEnv->e_to, num, msg, a, b, c, d, e);
E 52
I 52
D 71
	fmtmsg(MsgBuf, CurEnv->e_to, num, 0, msg, a, b, c, d, e);
E 71
I 71
	VA_START(msg);
D 78
	fmtmsg(MsgBuf, CurEnv->e_to, num, 0, msg, ap);
E 78
I 78
	fmtmsg(MsgBuf, CurEnv->e_to, "050", 0, msg, ap);
E 78
	VA_END;
E 71
E 52
I 33
D 39
	putmsg(MsgBuf);
E 39
I 39
D 97
	putmsg(MsgBuf, FALSE);
E 97
I 97
D 126
	putoutmsg(MsgBuf, FALSE);
E 126
I 126
	putoutmsg(MsgBuf, FALSE, FALSE);
E 126
I 125

	/* save this message for mailq printing */
	if (MsgBuf[0] == '5' || (CurEnv->e_message == NULL && MsgBuf[0] == '4'))
	{
		if (CurEnv->e_message != NULL)
			free(CurEnv->e_message);
		CurEnv->e_message = newstr(MsgBuf + 4);
	}
E 125
E 97
E 39
}
/*
I 38
**  NMESSAGE -- print message (not necessarily an error)
**
**	Just like "message" except it never puts the to... tag on.
**
**	Parameters:
D 125
**		num -- the default ARPANET error number (in ascii)
E 125
**		msg -- the message (printf fmt) -- if it begins
D 58
**			with a digit, this number overrides num.
E 58
I 58
D 125
**			with three digits, this number overrides num.
E 58
**		a, b, c, d, e -- printf arguments
E 125
I 125
**			with a three digit SMTP reply code, that is used,
**			otherwise 050 is assumed.
**		(others) -- printf arguments
E 125
**
**	Returns:
**		none
**
**	Side Effects:
**		none.
*/

/*VARARGS2*/
D 71
nmessage(num, msg, a, b, c, d, e)
	register char *num;
	register char *msg;
E 71
I 71
D 74
nmessage(num, msg VA_ARG_FORMAL)
E 74
I 74
D 83
#ifdef __STDC__
E 83
I 81
void
I 83
#ifdef __STDC__
E 83
E 81
D 78
nmessage(char *num, char *msg, ...)
E 78
I 78
D 91
nmessage(char *msg, ...)
E 91
I 91
nmessage(const char *msg, ...)
E 91
E 78
#else
D 78
nmessage(num, msg, va_alist)
E 74
	char *num;
E 78
I 78
nmessage(msg, va_alist)
E 78
D 91
	char *msg;
E 91
I 91
	const char *msg;
E 91
D 74
	VA_ARG_DECL
E 74
I 74
	va_dcl
#endif
E 74
E 71
{
I 71
	VA_LOCAL_DECL

E 71
	errno = 0;
D 43
	fmtmsg(MsgBuf, NULL, num, msg, a, b, c, d, e);
E 43
I 43
D 52
	fmtmsg(MsgBuf, (char *) NULL, num, msg, a, b, c, d, e);
E 52
I 52
D 71
	fmtmsg(MsgBuf, (char *) NULL, num, 0, msg, a, b, c, d, e);
E 71
I 71
	VA_START(msg);
D 78
	fmtmsg(MsgBuf, (char *) NULL, num, 0, msg, ap);
E 78
I 78
	fmtmsg(MsgBuf, (char *) NULL, "050", 0, msg, ap);
E 78
	VA_END;
E 71
E 52
E 43
D 39
	putmsg(MsgBuf);
E 39
I 39
D 97
	putmsg(MsgBuf, FALSE);
E 97
I 97
D 126
	putoutmsg(MsgBuf, FALSE);
E 126
I 126
	putoutmsg(MsgBuf, FALSE, FALSE);
E 126
E 97
E 39
}
/*
E 38
D 97
**  PUTMSG -- output error message to transcript and channel
E 97
I 97
**  PUTOUTMSG -- output error message to transcript and channel
E 97
**
**	Parameters:
**		msg -- message to output (in SMTP format).
I 39
**		holdmsg -- if TRUE, don't output a copy of the message to
**			our output channel.
I 126
**		heldmsg -- if TRUE, this is a previously held message;
**			don't log it to the transcript file.
E 126
E 39
**
**	Returns:
**		none.
**
**	Side Effects:
**		Outputs msg to the transcript.
**		If appropriate, outputs it to the channel.
**		Deletes SMTP reply code number as appropriate.
*/
E 33
E 32
E 28

I 129
void
E 129
I 33
D 39
putmsg(msg)
E 39
I 39
D 97
putmsg(msg, holdmsg)
E 97
I 97
D 126
putoutmsg(msg, holdmsg)
E 126
I 126
putoutmsg(msg, holdmsg, heldmsg)
E 126
E 97
E 39
	char *msg;
I 39
	bool holdmsg;
I 126
	bool heldmsg;
E 126
E 39
{
I 103
	/* display for debugging */
	if (tTd(54, 8))
D 126
		printf("--- %s%s\n", msg, holdmsg ? " (held)" : "");
E 126
I 126
		printf("--- %s%s%s\n", msg, holdmsg ? " (hold)" : "",
			heldmsg ? " (held)" : "");
E 126

E 103
E 33
D 50
	/* output to transcript */
D 29
	fprintf(Xscript, "%s\n", errbuf);
E 29
I 29
D 32
	fprintf(Xscript, "%s\n", &errbuf[4]);
E 32
I 32
D 33
	fprintf(Xscript, "%s\n", Smtp ? MsgBuf : &MsgBuf[4]);
E 33
I 33
D 40
	fprintf(Xscript, "%s\n", Smtp ? msg : &msg[4]);
E 40
I 40
D 42
	if (Xscript != OutChannel)
E 42
I 42
D 46
	if (Xscript != NULL)
E 42
D 41
		fprintf(Xscript, "%s\n", Smtp ? msg : &msg[4]);
E 41
I 41
		fprintf(Xscript, "%s\n", OpMode == MD_SMTP ? msg : &msg[4]);
E 46
I 46
	if (CurEnv->e_xfp != NULL)
		fprintf(CurEnv->e_xfp, "%s\n", OpMode == MD_SMTP ? msg : &msg[4]);
E 50
I 50
	/* output to transcript if serious */
D 99
	if (CurEnv->e_xfp != NULL && (msg[0] == '4' || msg[0] == '5'))
E 99
I 99
D 126
	if (CurEnv->e_xfp != NULL && strchr("456", msg[0]) != NULL)
E 126
I 126
	if (!heldmsg && CurEnv->e_xfp != NULL && strchr("456", msg[0]) != NULL)
E 126
E 99
		fprintf(CurEnv->e_xfp, "%s\n", msg);
E 50
E 46
E 41
E 40
E 33
E 32
E 29

	/* output to channel if appropriate */
D 30
	if (!HoldErrs)
E 30
I 30
D 32
	if (!HoldErrs && (Verbose || errbuf[0] != '0'))
E 32
I 32
D 33
	if (!HoldErrs && (Verbose || MsgBuf[0] != '0'))
E 33
I 33
D 39
	if (!HoldErrs && (Verbose || msg[0] != '0'))
E 39
I 39
D 95
	if (!holdmsg && (Verbose || msg[0] != '0'))
E 39
E 33
E 32
E 30
E 22
	{
I 31
		(void) fflush(stdout);
E 31
D 22
		num = msg;
		msg += 4;
E 22
I 22
D 41
		if (ArpaMode)
E 41
I 41
D 69
		if (OpMode == MD_SMTP || OpMode == MD_ARPAFTP)
E 69
I 69
		if (OpMode == MD_SMTP)
E 69
E 41
D 32
			fprintf(OutChannel, "%s\r\n", errbuf);
E 32
I 32
D 33
			fprintf(OutChannel, "%s\r\n", MsgBuf);
E 33
I 33
			fprintf(OutChannel, "%s\r\n", msg);
E 33
E 32
		else
D 32
			fprintf(OutChannel, "%s\n", &errbuf[4]);
E 32
I 32
D 33
			fprintf(OutChannel, "%s\n", &MsgBuf[4]);
E 33
I 33
			fprintf(OutChannel, "%s\n", &msg[4]);
E 33
E 32
D 92
		(void) fflush(OutChannel);
E 92
I 92
		if (msg[3] == ' ')
			(void) fflush(OutChannel);
E 92
I 84
		if (ferror(OutChannel))
		{
I 93
D 94
			int saveerrno = errno;

			(void) freopen("/dev/null", "w", OutChannel);
E 94
I 94
			/* can't call syserr, 'cause we are using MsgBuf */
E 94
E 93
			HoldErrs = TRUE;
E 95
I 95
D 126
	if (holdmsg || (!Verbose && msg[0] == '0'))
E 126
I 126
	if (!Verbose && msg[0] == '0')
E 126
		return;
I 126
	if (holdmsg)
	{
		/* save for possible future display */
		strcpy(HeldMessageBuf, msg);
		return;
	}
E 126

I 99
	/* map warnings to something SMTP can handle */
	if (msg[0] == '6')
		msg[0] = '5';

E 99
	(void) fflush(stdout);
D 114
	if (OpMode == MD_SMTP)
E 114
I 114
D 116
	if (OpMode == MD_SMTP || OpMode == MD_DAEMON)
E 116
I 116
D 118
	if (OpMode == MD_SMTP || OpMode == MD_DAEMON || OpMode == MD_ARPAFTP)
E 118
I 118

	/* if DisConnected, OutChannel now points to the transcript */
	if (!DisConnected &&
	    (OpMode == MD_SMTP || OpMode == MD_DAEMON || OpMode == MD_ARPAFTP))
E 118
E 116
E 114
		fprintf(OutChannel, "%s\r\n", msg);
	else
		fprintf(OutChannel, "%s\n", &msg[4]);
I 97
	if (TrafficLogFile != NULL)
		fprintf(TrafficLogFile, "%05d >>> %s\n", getpid(),
D 114
			OpMode == MD_SMTP ? msg : &msg[4]);
E 114
I 114
			(OpMode == MD_SMTP || OpMode == MD_DAEMON) ? msg : &msg[4]);
E 114
E 97
	if (msg[3] == ' ')
		(void) fflush(OutChannel);
D 118
	if (!ferror(OutChannel))
E 118
I 118
	if (!ferror(OutChannel) || DisConnected)
E 118
		return;

D 104
	/* error on output -- if reporting lost channel, just ignore it */
	if (feof(InChannel) || ferror(InChannel))
E 104
I 104
	/*
	**  Error on output -- if reporting lost channel, just ignore it.
	**  Also, ignore errors from QUIT response (221 message) -- some
	**	rude servers don't read result.
	*/

	if (feof(InChannel) || ferror(InChannel) || strncmp(msg, "221", 3) == 0)
E 104
		return;

	/* can't call syserr, 'cause we are using MsgBuf */
	HoldErrs = TRUE;
E 95
I 93
D 94
			errno = saveerrno;
E 93
D 88
			syserr("putmsg: error on output channel");
E 88
I 88
			syserr("putmsg: error on output channel sending \"%s\"",
				msg);
E 94
I 94
#ifdef LOG
D 95
			if (LogLevel > 0)
				syslog(LOG_CRIT,
					"%s: SYSERR: putmsg (%s): error on output channel sending \"%s\"",
					CurEnv->e_id == NULL ? "NOQUEUE" : CurEnv->e_id,
					CurHostName, msg);
E 95
I 95
	if (LogLevel > 0)
		syslog(LOG_CRIT,
D 97
			"%s: SYSERR: putmsg (%s): error on output channel sending \"%s\"",
E 97
I 97
D 104
			"%s: SYSERR: putoutmsg (%s): error on output channel sending \"%s\"",
E 104
I 104
D 122
			"%s: SYSERR: putoutmsg (%s): error on output channel sending \"%s\": %m",
E 122
I 122
			"%s: SYSERR: putoutmsg (%s): error on output channel sending \"%s\": %s",
E 122
E 104
E 97
			CurEnv->e_id == NULL ? "NOQUEUE" : CurEnv->e_id,
D 102
			CurHostName, msg);
E 102
I 102
			CurHostName == NULL ? "NO-HOST" : CurHostName,
D 122
			msg);
E 122
I 122
			msg, errstring(errno));
E 122
E 102
E 95
#endif
E 94
E 88
D 95
		}
E 84
I 38
	}
E 95
I 45
}
/*
D 97
**  PUTERRMSG -- like putmsg, but does special processing for error messages
E 97
I 97
**  PUTERRMSG -- like putoutmsg, but does special processing for error messages
E 97
**
**	Parameters:
**		msg -- the message to output.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets the fatal error bit in the envelope as appropriate.
*/
E 45

I 129
void
E 129
D 45
	/* determine error status */
	switch (msg[0])
	{
	  case '5':
D 42
		FatalErrors = TRUE;
E 42
I 42
		CurEnv->e_flags |= EF_FATALERRS;
E 42
		/* fall through.... */
E 45
I 45
puterrmsg(msg)
	char *msg;
{
I 99
	char msgcode = msg[0];

E 99
	/* output the message as usual */
D 97
	putmsg(msg, HoldErrs);
E 97
I 97
D 126
	putoutmsg(msg, HoldErrs);
E 126
I 126
	putoutmsg(msg, HoldErrs, FALSE);
E 126
E 97
E 45

D 45
	  case '4':
		Errors++;
		break;
E 38
E 22
	}
E 45
I 45
	/* signal the error */
D 99
	Errors++;
D 98
	if (msg[0] == '5')
E 98
I 98
	if (msg[0] == '5' && bitset(EF_GLOBALERRS, CurEnv->e_flags))
E 98
		CurEnv->e_flags |= EF_FATALERRS;
E 99
I 99
D 108
	if (msgcode == '6')
E 108
I 108
D 109
	if (!HoldErrs)
E 108
	{
D 108
		/* notify the postmaster */
		CurEnv->e_flags |= EF_PM_NOTIFY;
	}
	else
	{
E 108
		Errors++;
		if (msgcode == '5' && bitset(EF_GLOBALERRS, CurEnv->e_flags))
			CurEnv->e_flags |= EF_FATALERRS;
I 108
	}

E 109
I 109
	Errors++;
E 109
	if (msgcode == '6')
	{
		/* notify the postmaster */
		CurEnv->e_flags |= EF_PM_NOTIFY;
I 109
	}
D 123
	else if (msgcode == '5' && bitset(EF_GLOBALERRS, CurEnv->e_flags))
E 123
I 123
	else if ((msgcode == '4' || msgcode == '5') &&
		 bitset(EF_GLOBALERRS, CurEnv->e_flags))
E 123
	{
		/* mark long-term fatal errors */
		CurEnv->e_flags |= EF_FATALERRS;
E 109
E 108
	}
E 99
E 45
I 22
}
/*
**  FMTMSG -- format a message into buffer.
**
**	Parameters:
**		eb -- error buffer to get result.
**		to -- the recipient tag for this message.
**		num -- arpanet error number.
I 52
**		en -- the error number to display.
E 52
**		fmt -- format of string.
**		a, b, c, d, e -- arguments.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/
E 22

I 24
D 52
/*VARARGS4*/
E 52
I 52
D 71
/*VARARGS5*/
E 71
E 52
E 24
D 22
	/* print arpa format header if needed */
D 15
	if (ArpaFmt)
E 15
I 15
D 21
	if (ArpaMode != ARPA_NONE && !HasXscrpt)
E 21
I 21
	if (ArpaMode != ARPA_NONE && Transcript == NULL)
E 22
I 22
D 66
static
E 66
I 66
static void
E 66
D 52
fmtmsg(eb, to, num, fmt, a, b, c, d, e)
E 52
I 52
D 71
fmtmsg(eb, to, num, eno, fmt, a, b, c, d, e)
E 71
I 71
fmtmsg(eb, to, num, eno, fmt, ap)
E 71
E 52
	register char *eb;
D 129
	char *to;
	char *num;
E 129
I 129
	const char *to;
	const char *num;
E 129
I 52
D 53
	int en;
E 53
I 53
	int eno;
E 53
E 52
D 129
	char *fmt;
E 129
I 129
	const char *fmt;
E 129
I 71
	va_list ap;
E 71
{
	char del;
I 87
	char *meb;
E 87

	/* output the reply code */
D 58
	if (isdigit(*fmt))
E 58
I 58
	if (isdigit(fmt[0]) && isdigit(fmt[1]) && isdigit(fmt[2]))
E 58
E 22
E 21
E 15
D 19
		printf("%.3s ", num);
E 19
I 19
D 20
		fprintf(OutChannel, "%.3s ", num);
E 20
I 20
	{
D 22
		register char del;
E 22
I 22
		num = fmt;
		fmt += 4;
	}
	if (num[3] == '-')
		del = '-';
	else
		del = ' ';
	(void) sprintf(eb, "%3.3s%c", num, del);
	eb += 4;
I 44

	/* output the file name and line number */
	if (FileName != NULL)
	{
		(void) sprintf(eb, "%s: line %d: ", FileName, LineNumber);
		eb += strlen(eb);
	}
E 44
E 22

D 22
		if (num[3] == '-')
			del = '-';
		else
			del = ' ';
		fprintf(OutChannel, "%3.3s%c", num, del);
E 22
I 22
	/* output the "to" person */
	if (to != NULL && to[0] != '\0')
	{
D 119
		(void) sprintf(eb, "%s... ", to);
E 119
I 119
		(void) sprintf(eb, "%s... ", shortenstring(to, 203));
E 119
D 26
		eb += strlen(eb);
E 26
I 26
		while (*eb != '\0')
			*eb++ &= 0177;
E 26
E 22
	}
E 20
E 19

I 87
	meb = eb;

E 87
D 22
	if (To != NULL && To[0] != '\0')
E 12
D 19
		printf("%s... ", To);
D 12
	printf(fmt, a, b, c, d, e);
E 12
I 12
	printf(msg, a, b, c, d, e);
E 19
I 19
		fprintf(OutChannel, "%s... ", To);
	fprintf(OutChannel, msg, a, b, c, d, e);
E 19
I 13
D 15
	if (ArpaFmt)
E 15
I 15
D 21
	if (ArpaMode != ARPA_NONE && !HasXscrpt)
E 21
I 21
	if (ArpaMode != ARPA_NONE && Transcript == NULL)
E 21
E 15
D 19
		printf("\r");
E 13
E 12
	printf("\n");
I 7
D 14
	fflush(stdout);
E 14
I 14
	(void) fflush(stdout);
E 19
I 19
		fprintf(OutChannel, "\r");
	fprintf(OutChannel, "\n");
	(void) fflush(OutChannel);
E 22
I 22
	/* output the message */
D 71
	(void) sprintf(eb, fmt, a, b, c, d, e);
E 71
I 71
	(void) vsprintf(eb, fmt, ap);
E 71
D 26
	eb += strlen(eb);
E 26
I 26
	while (*eb != '\0')
		*eb++ &= 0177;
E 26

	/* output the error code, if any */
D 53
	if (errno != 0)
E 53
I 53
	if (eno != 0)
E 53
	{
D 51
		extern int sys_nerr;
		extern char *sys_errlist[];
		if (errno < sys_nerr && errno > 0)
			(void) sprintf(eb, ": %s", sys_errlist[errno]);
		else
			(void) sprintf(eb, ": error %d", errno);
E 51
I 51
D 90
		extern char *errstring();

E 90
D 53
		(void) sprintf(eb, ": %s", errstring(errno));
E 53
I 53
		(void) sprintf(eb, ": %s", errstring(eno));
E 53
E 51
		eb += strlen(eb);
D 125
	}
I 87

D 89
	if (CurEnv->e_message == NULL)
E 89
I 89
D 105
	if (CurEnv->e_message == NULL && strchr("45", num[0]) != NULL)
E 105
I 105
	if (num[0] == '5' || (CurEnv->e_message == NULL && num[0] == '4'))
	{
		if (CurEnv->e_message != NULL)
			free(CurEnv->e_message);
E 105
E 89
		CurEnv->e_message = newstr(meb);
E 125
I 105
	}
I 126
}
/*
**  BUFFER_ERRORS -- arrange to buffer future error messages
**
**	Parameters:
**		none
**
**	Returns:
**		none.
*/

void
buffer_errors()
{
	HeldMessageBuf[0] = '\0';
	HoldErrs = TRUE;
}
/*
**  FLUSH_ERRORS -- flush the held error message buffer
**
**	Parameters:
**		print -- if set, print the message, otherwise just
**			delete it.
**
**	Returns:
**		none.
*/

void
flush_errors(print)
	bool print;
{
	if (print && HeldMessageBuf[0] != '\0')
		putoutmsg(HeldMessageBuf, FALSE, TRUE);
	HeldMessageBuf[0] = '\0';
	HoldErrs = FALSE;
E 126
E 105
E 87
I 51
}
/*
**  ERRSTRING -- return string description of error code
**
**	Parameters:
D 115
**		errno -- the error number to translate
E 115
I 115
**		errnum -- the error number to translate
E 115
**
**	Returns:
D 115
**		A string description of errno.
E 115
I 115
**		A string description of errnum.
E 115
**
**	Side Effects:
**		none.
*/

D 90
char *
E 90
I 90
const char *
E 90
D 115
errstring(errno)
	int errno;
E 115
I 115
errstring(errnum)
	int errnum;
E 115
{
I 113
	char *dnsmsg;
E 113
D 90
	extern char *sys_errlist[];
E 90
I 90
D 98
	extern const char *const sys_errlist[];
E 90
	extern int sys_nerr;
E 98
D 58
	static char buf[50];
E 58
I 58
D 72
	static char buf[100];
E 72
I 72
	static char buf[MAXLINE];
I 98
# ifndef ERRLIST_PREDEFINED
	extern char *sys_errlist[];
	extern int sys_nerr;
# endif
E 98
E 72
# ifdef SMTP
	extern char *SmtpPhase;
D 60
	extern char *RealHostName;
E 60
D 70
# endif SMTP
E 70
I 70
# endif /* SMTP */
E 70

D 111
# ifdef DAEMON
D 68
# ifdef VMUNIX
E 68
I 68
# ifdef ETIMEDOUT
E 111
E 68
	/*
	**  Handle special network error codes.
	**
	**	These are 4.2/4.3bsd specific; they should be in daemon.c.
	*/

I 113
	dnsmsg = NULL;
E 113
D 115
	switch (errno)
E 115
I 115
	switch (errnum)
E 115
	{
I 111
# if defined(DAEMON) && defined(ETIMEDOUT)
E 111
	  case ETIMEDOUT:
	  case ECONNRESET:
D 115
		(void) strcpy(buf, sys_errlist[errno]);
E 115
I 115
		(void) strcpy(buf, sys_errlist[errnum]);
E 115
		if (SmtpPhase != NULL)
		{
			(void) strcat(buf, " during ");
			(void) strcat(buf, SmtpPhase);
		}
D 60
		if (RealHostName != NULL)
E 60
I 60
		if (CurHostName != NULL)
E 60
		{
			(void) strcat(buf, " with ");
D 60
			(void) strcat(buf, RealHostName);
E 60
I 60
			(void) strcat(buf, CurHostName);
E 60
		}
		return (buf);

	  case EHOSTDOWN:
D 60
		if (RealHostName == NULL)
E 60
I 60
		if (CurHostName == NULL)
E 60
			break;
D 60
		(void) sprintf(buf, "Host %s is down", RealHostName);
E 60
I 60
		(void) sprintf(buf, "Host %s is down", CurHostName);
E 60
		return (buf);

	  case ECONNREFUSED:
D 60
		if (RealHostName == NULL)
E 60
I 60
		if (CurHostName == NULL)
E 60
			break;
D 60
		(void) sprintf(buf, "Connection refused by %s", RealHostName);
E 60
I 60
		(void) sprintf(buf, "Connection refused by %s", CurHostName);
I 62
		return (buf);
I 111
# endif
E 111

I 101
	  case EOPENTIMEOUT:
		return "Timeout on file open";

E 101
I 75
D 121
# ifdef NAMED_BIND
E 121
I 121
# if NAMED_BIND
E 121
E 75
D 76
	  case (TRY_AGAIN+MAX_ERRNO):
		(void) sprintf(buf, "Host Name Lookup Failure");
E 62
E 60
		return (buf);
E 76
I 76
D 101
	  case HOST_NOT_FOUND + MAX_ERRNO:
E 101
I 101
	  case HOST_NOT_FOUND + E_DNSBASE:
E 101
D 112
		return ("Name server: host not found");
E 112
I 112
D 113
		return ("Name server: %s: host not found", CurHostName);
E 113
I 113
		dnsmsg = "host not found";
		break;
E 113
E 112

D 101
	  case TRY_AGAIN + MAX_ERRNO:
E 101
I 101
	  case TRY_AGAIN + E_DNSBASE:
E 101
D 112
		return ("Name server: host name lookup failure");
E 112
I 112
D 113
		return ("Name server: %s: host name lookup failure", CurHostName);
E 113
I 113
		dnsmsg = "host name lookup failure";
		break;
E 113
E 112

D 101
	  case NO_RECOVERY + MAX_ERRNO:
E 101
I 101
	  case NO_RECOVERY + E_DNSBASE:
E 101
D 112
		return ("Name server: non-recoverable error");
E 112
I 112
D 113
		return ("Name server: %s: non-recoverable error", CurHostName);
E 113
I 113
		dnsmsg = "non-recoverable error";
		break;
E 113
E 112

D 101
	  case NO_DATA + MAX_ERRNO:
E 101
I 101
	  case NO_DATA + E_DNSBASE:
E 101
D 112
		return ("Name server: no data known for name");
E 112
I 112
D 113
		return ("Name server: %s: no data known", CurHostName);
E 113
I 113
		dnsmsg = "no data known";
		break;
E 113
E 112
E 76
I 75
# endif
I 111

	  case EPERM:
		/* SunOS gives "Not owner" -- this is the POSIX message */
		return "Operation not permitted";
I 113
	}

	if (dnsmsg != NULL)
	{
		(void) strcpy(buf, "Name server: ");
		if (CurHostName != NULL)
		{
			(void) strcat(buf, CurHostName);
			(void) strcat(buf, ": ");
		}
		(void) strcat(buf, dnsmsg);
		return buf;
E 113
E 111
E 75
	}
D 68
# endif VMUNIX
# endif DAEMON
E 68
I 68
D 111
# endif
# endif
E 111
E 68
E 58

D 115
	if (errno > 0 && errno < sys_nerr)
		return (sys_errlist[errno]);
E 115
I 115
	if (errnum > 0 && errnum < sys_nerr)
		return (sys_errlist[errnum]);
E 115

D 115
	(void) sprintf(buf, "Error %d", errno);
E 115
I 115
	(void) sprintf(buf, "Error %d", errnum);
E 115
	return (buf);
E 51
E 22
E 19
E 14
E 7
D 12
	return (-1);
E 12
}
E 1
