h12728
s 00003/00000/00704
d D 8.44 95/06/10 12:16:21 eric 161 160
c diagnose -t call with no recipients in header
e
s 00001/00001/00703
d D 8.43 95/06/05 07:26:21 eric 160 159
c freespace=>freediskspace, enoughspace=>enoughdiskspace to avoid
c conflicts with some memory allocators (e.g., A/UX)
e
s 00005/00000/00699
d D 8.42 95/05/27 14:37:50 eric 159 158
c log message on too-large message
e
s 00007/00001/00692
d D 8.41 95/05/23 10:20:53 eric 158 157
c log premature end-of-message conditions when collecting messages
e
s 00007/00000/00686
d D 8.40 95/04/29 07:41:28 eric 157 156
c better (more accurate) labelling of 8bit code
e
s 00000/00004/00686
d D 8.39 95/04/25 09:57:42 eric 156 155
c only insist on CRLF for SMTP 8BITMIME
e
s 00005/00005/00685
d D 8.38 95/04/24 20:31:17 eric 155 154
c efficiency improvements
e
s 00005/00000/00685
d D 8.37 95/04/22 14:50:49 eric 154 153
c better use of extended DSN status codes
e
s 00001/00001/00684
d D 8.36 95/04/21 09:57:10 eric 153 152
c update copyright notice
e
s 00001/00001/00684
d D 8.35 95/04/21 09:49:00 eric 152 151
c better debugging message for message termination
e
s 00002/00001/00683
d D 8.34 95/04/07 17:40:27 eric 151 150
c null bytes in headers can cause data to be lost -- just ignore them
e
s 00014/00014/00670
d D 8.33 95/04/03 09:31:16 eric 150 149
c clean up problems with MIME 8 to 7 bit conversions
e
s 00005/00023/00679
d D 8.32 95/03/31 09:05:34 eric 149 148
c buffer error messages during collect phase (better implementation)
e
s 00009/00008/00693
d D 8.31 95/03/21 15:28:20 eric 148 147
c eliminate `D' line in qf file
e
s 00003/00001/00698
d D 8.30 95/03/21 09:52:28 eric 147 146
c fix some compile problems with message sizes
e
s 00002/00002/00697
d D 8.29 95/03/21 09:26:43 eric 146 145
c new DSN draft
e
s 00030/00007/00669
d D 8.28 95/02/24 10:00:59 eric 145 143
c add NoRecipientAction; make Bcc: field truncate instead of delete
e
s 00000/00025/00651
d R 8.28 95/02/24 08:58:32 eric 144 143
c delete Apparently-To: code
e
s 00018/00003/00658
d D 8.27 95/02/23 15:51:03 eric 143 142
c cleanup to make gcc -Winitialized happier
e
s 00001/00014/00660
d D 8.26 94/11/05 12:27:46 eric 142 141
c tweak EightBitMode and F=8 options to do something useful
e
s 00009/00003/00665
d D 8.25 94/10/17 20:31:38 eric 141 140
c if a message exceeds MaxMessageSize, stop pushing the data to
c disk -- it is just a possible denial-of-service attack
e
s 00001/00000/00667
d D 8.24 94/08/18 06:45:16 eric 140 139
c fix problems eating initial From_ line
e
s 00007/00005/00660
d D 8.23 94/08/16 08:19:51 eric 139 138
c fix a couple of bugs having to do with CRLF mapping
e
s 00003/00000/00662
d D 8.22 94/08/15 18:07:20 eric 138 137
c store dev information in qf file; add RFC 1428-specified
c Content-Type: text/plain; charset=unknown-8bit header to messages
c being converted from 8 -> 7 bit with no specific Content-Type
e
s 00000/00001/00662
d D 8.21 94/08/15 10:15:47 eric 137 136
c move hvalue extern declaration into sendmail.h
e
s 00006/00000/00657
d D 8.20 94/08/07 17:42:04 eric 136 135
c DECWRL extensions to qf file
e
s 00246/00190/00411
d D 8.19 94/08/07 10:02:33 eric 135 134
c first cut at full 8-bit data capability
e
s 00021/00000/00580
d D 8.18 94/07/23 10:12:24 eric 134 133
c tweaks & bug fixes to MIME algorithm
e
s 00059/00034/00521
d D 8.17 94/07/23 07:59:28 eric 133 132
c MIME 8 to 7 bit support
e
s 00002/00002/00553
d D 8.16 94/07/03 11:48:13 eric 132 131
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00014/00012/00541
d D 8.15 94/05/29 13:08:53 eric 131 130
c don't time out non-SMTP reads from stdin
e
s 00001/00001/00552
d D 8.14 94/04/18 15:17:10 eric 130 129
c when creating the df file, be sure you truncate any existing file
e
s 00002/00002/00551
d D 8.13 94/04/18 07:03:28 eric 129 128
c avoid using %m in syslog calls because it conflicts with HP-UX
e
s 00026/00009/00527
d D 8.12 94/04/15 11:31:44 eric 128 127
c defer error messages until after the collect is done to get around
c a disagreement with MVS about how the SMTP protocol works
e
s 00027/00001/00509
d D 8.11 94/04/14 09:37:58 eric 127 126
c improve "out of temp space" error message
e
s 00006/00000/00504
d D 8.10 94/04/12 16:11:48 eric 126 125
c speed up reading of messages by reducing system call load
e
s 00005/00002/00499
d D 8.9 94/01/31 17:01:15 eric 125 124
c be a bit less tricky to avoid confusing old C compilers
e
s 00003/00002/00498
d D 8.8 94/01/08 17:29:19 eric 124 123
c fix problem that was causing the ctladdr of whoever ran the daemon
c (usually root) to own the delivery process
e
s 00006/00001/00494
d D 8.7 93/11/17 16:51:04 eric 123 122
c fix problem that caused last header entered with no body to be discarded
e
s 00005/00002/00490
d D 8.6 93/10/27 09:17:29 eric 122 121
c check fflush, fclose, and fsync return values in a few critical places
e
s 00025/00008/00467
d D 8.5 93/10/15 08:34:34 eric 121 120
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00001/00000/00474
d D 8.4 93/08/06 21:19:32 eric 120 119
c fix duplicate error messages if connection lost during DATA when
c one address failed (wierd situation)
e
s 00002/00001/00472
d D 8.3 93/07/29 08:31:40 eric 119 118
c don't call newstr() macro with arguments with subroutine calls, since
c it double-evaluates
e
s 00004/00000/00469
d D 8.2 93/07/27 21:35:53 eric 118 117
c fix statistics gathering
e
s 00002/00002/00467
d D 8.1 93/06/07 10:29:20 bostic 117 116
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00006/00456
d D 6.20 93/06/03 17:01:31 eric 116 115
c print better diagnostic information on sfgets timeouts
e
s 00001/00000/00461
d D 6.19 93/05/30 08:54:47 eric 115 114
c fsync queue files
e
s 00001/00001/00460
d D 6.18 93/05/27 13:02:00 eric 114 113
c Solaris portability changes
e
s 00000/00001/00461
d D 6.17 93/05/27 11:37:22 eric 113 112
c prototype functions
e
s 00001/00002/00461
d D 6.16 93/05/05 08:11:22 eric 112 111
c create dead.letter with FileMode instead of 0666
e
s 00001/00001/00462
d D 6.15 93/04/30 12:53:53 eric 111 110
c don't change alpha case on header field names
e
s 00007/00000/00456
d D 6.14 93/04/27 07:20:47 eric 110 109
c check for message size exceeded
e
s 00006/00002/00450
d D 6.13 93/04/01 14:59:16 eric 109 108
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00000/00001/00452
d D 6.12 93/03/23 18:06:31 eric 108 107
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00001/00001/00452
d D 6.11 93/03/19 11:46:33 eric 107 106
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00004/00000/00449
d D 6.10 93/03/17 10:35:23 eric 106 105
c attempts to handle ENFILE conditions better
e
s 00010/00005/00439
d D 6.9 93/02/28 11:03:11 eric 105 104
c changes for better logging of mail submitters
e
s 00003/00003/00441
d D 6.8 93/02/23 06:31:40 eric 104 103
c overhaul status of SMTP reply codes
e
s 00000/00001/00444
d D 6.7 93/02/21 13:45:35 eric 103 102
c change $d to be current date, not origination date
e
s 00006/00006/00439
d D 6.6 93/02/21 09:56:14 eric 102 101
c generalize read timeout
e
s 00005/00003/00440
d D 6.5 93/02/20 13:46:37 eric 101 100
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00002/00001/00441
d D 6.4 93/02/18 20:22:23 eric 100 99
c move the meta-characters from C0 into C1 space
e
s 00001/00001/00441
d D 6.3 93/01/21 15:18:38 eric 99 98
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00006/00006/00436
d D 6.2 93/01/01 13:08:12 eric 98 97
c pass read timeouts to sfgets
e
s 00000/00000/00442
d D 6.1 92/12/21 16:08:27 eric 97 96
c Release 6
e
s 00015/00013/00427
d D 5.16 92/12/15 12:34:46 eric 96 95
i 94
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00011/00005/00409
d D 5.15 92/12/15 11:49:27 eric 95 93
c print message on too long header line
e
s 00038/00018/00396
d D 5.14.1.1 92/12/15 11:45:17 eric 94 93
c dynamically allocate header buffer
e
s 00003/00003/00411
d D 5.14 92/11/14 11:34:16 eric 93 92
c (partially) ANSI-fy it
e
s 00002/00001/00412
d D 5.13 92/11/04 12:14:48 eric 92 91
c fix a variety of small bugs noticed by bcx
e
s 00031/00028/00382
d D 5.12 92/07/12 14:09:42 eric 91 90
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00409
d D 5.11 92/01/04 15:33:01 eric 90 89
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00010/00007/00400
d D 5.10 92/01/04 11:47:47 eric 89 88
c include defaults for SendMode and ErrorMode; never ignore single dot
c termination when collecting message in SMTP mode.
e
s 00001/00011/00406
d D 5.9 90/06/01 19:00:31 bostic 88 87
c new copyright notice
e
s 00113/00035/00304
d D 5.8 90/04/18 12:35:23 bostic 87 86
c long headers can cause sendmail to loop; bug report 4.3BSD/usr.lib/126
c getc() calls in collect() will never time out; bug report 4.3BSD/usr.lib/127
c mail bounces on transient errors; bug report 4.3BSD/usr.lib/135
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00000/00006/00339
d D 5.7 89/01/01 17:16:54 bostic 86 85
c remove DEBUG
e
s 00003/00001/00342
d D 5.6 88/11/17 22:02:11 karels 85 84
c more cleanup, fix some inappropriate syserr's
e
s 00005/00001/00338
d D 5.5 88/11/17 10:31:58 karels 84 83
c expunge debugging/nonstandard/trojan horse commands from smtp,
c logging attempts to use them; log name/address of host from which mail received
c ("mail from" may not include it or may lie); don't allow debug to affect
c permissions locally; change some of the non-system syserrs to syslog at lower
c priority; still need to unifdef remaining debug code
e
s 00011/00009/00328
d D 5.4 88/06/30 14:58:23 bostic 83 82
c install approved copyright notice
e
s 00016/00010/00321
d D 5.3 88/03/13 19:51:34 bostic 82 81
c add Berkeley specific header
e
s 00001/00001/00330
d D 5.2 85/06/08 00:26:29 eric 81 80
m 
c lint
e
s 00014/00002/00317
d D 5.1 85/06/07 14:30:12 dist 80 79
m 
c Add copyright
e
s 00006/00002/00313
d D 4.5 85/04/28 10:42:13 eric 79 78
m 
c add iferror to loop termination conditions to avoid loops from
c peer resets
e
s 00002/00002/00313
d D 4.4 84/08/11 17:48:50 eric 78 77
m 
c Assorted changes from Guy Harris <rlgvax!guy>: mostly lint & USG
e
s 00010/00001/00305
d D 4.3 84/03/11 13:20:55 eric 77 76
m 
c fix from Bill Nowicki -- don't return an error if the connection times
c out, since we haven't accepted responsibility yet.
e
s 00007/00013/00299
d D 4.2 83/11/13 18:07:52 eric 76 75
m 
c Fixes two nasty problems, both pointed out by Bill Nowicki at Stanford:
c I/O errors on input in collect would cause infinite loops, and a protocol
c error (or other error that would call smtpquit abnormally) would cause
c core dumps
e
s 00000/00000/00312
d D 4.1 83/07/25 19:45:05 eric 75 74
m 
c 4.2 release version
e
s 00009/00010/00303
d D 3.61 83/07/13 10:37:51 eric 74 73
m 
c Delete "load limiting" for SMTP connections (a bad ethernet board can
c hang up all incoming mail); use sfgets in collect (same reason); check
c for I/O error in collect (from Bill Nowicki); switch date format to
c RFC822 style.
e
s 00000/00009/00313
d D 3.60 83/04/17 17:13:40 eric 73 72
m 218
c remove >From hack
e
s 00030/00011/00292
d D 3.59 83/03/12 17:41:40 eric 72 71
m 208
c Check for I/O error on close of temp file -- i.e., last buffer flush
e
s 00000/00012/00303
d D 3.58 83/02/26 11:51:03 eric 71 70
m 193
c log queueid <=> message-id correspondence
e
s 00004/00000/00311
d D 3.57 83/02/18 12:41:52 eric 70 69
m 185
c Give an error if the message is terminated with an EOF and we are
c running SMTP (it must be terminated with a dot).
e
s 00001/00001/00310
d D 3.56 82/12/05 13:45:26 eric 69 68
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00011/00023/00300
d D 3.55 82/11/28 00:20:13 eric 68 67
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00001/00001/00322
d D 3.54 82/11/17 09:35:20 eric 67 66
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00001/00001/00322
d D 3.53 82/11/03 10:29:11 eric 66 65
m 058
c Put temporary file mode on the F option
e
s 00000/00001/00323
d D 3.52 82/09/12 16:43:10 eric 65 64
c change inheritance for macros in envelopes; be able to canonicalize
c non-domained names by appending domain from sender; call ruleset 3
c explicitly before doing other rulesets; some general cleanup.
e
s 00012/00012/00312
d D 3.51 82/08/23 09:23:38 eric 64 63
c allow continuation lines in .cf file (particularly in headers)
e
s 00000/00014/00324
d D 3.50 82/08/22 23:06:54 eric 63 62
c change $i to $j; $i is now queue id; put "Received:" format in .cf
c file; minor cleanup
e
s 00006/00011/00332
d D 3.49 82/08/22 19:02:36 eric 62 61
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00003/00003/00340
d D 3.48 82/08/17 20:44:47 eric 61 60
c Mail-From: ==> Received: for new SMTP spec (RFC821)
e
s 00005/00211/00338
d D 3.47 82/08/17 16:17:17 eric 60 59
c rework header processing: do special purpose header munging in a
c separate routine so that the queue run can do it also.  Also, parse
c From: lines in a fancy way, extracting the address part and turning
c it into a $g macro.
e
s 00001/00001/00548
d D 3.46 82/08/15 11:56:21 eric 59 58
c output message class rather than priority in log
e
s 00008/00000/00541
d D 3.45 82/08/08 16:55:17 eric 58 57
c truncate excessively long header lines
e
s 00034/00005/00507
d D 3.44 82/08/08 01:02:00 eric 57 56
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00002/00000/00510
d D 3.43 82/07/14 09:22:30 eric 56 55
c fix bug in Apparently-To:, outputing too many lines
e
s 00017/00000/00493
d D 3.42 82/07/05 18:49:39 eric 55 54
c add "Apparently-To:" field if no recipients are in the header.
e
s 00004/00000/00489
d D 3.41 82/07/05 13:19:45 eric 54 53
c count Mail-From: lines to avoid loops (simulates hop counts)
e
s 00003/00003/00486
d D 3.40 82/05/31 18:48:55 eric 53 52
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00005/00005/00484
d D 3.39 82/05/31 15:31:25 eric 52 50
i 51
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00002/00002/00487
d D 3.38.1.1 82/05/29 18:19:33 eric 51 50
c try to install envelopes.  is this really worth it???
e
s 00005/00001/00484
d D 3.38 82/05/22 02:05:07 eric 50 49
c add "junk mail" -- error responses are never returned.
e
s 00009/00011/00476
d D 3.37 82/05/22 01:36:57 eric 49 48
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00002/00002/00485
d D 3.36 82/05/20 17:45:29 eric 48 47
c add dfopen as a "determined fopen" -- it retries if it gets recoverable
c errors.  we use it for returning mail (to dead.letter) and creating the
c temp file.  the whole idea is to avoid dropping things on the floor on
c heavily loaded systems.  this is untested, since it seems impossible to
c fill up the inode or file tables on this VAX (but it works if the open
c succeeds).
e
s 00079/00000/00408
d D 3.35 82/02/27 11:37:10 eric 47 46
c implement "return receipt requested".
e
s 00010/00010/00398
d D 3.34 82/02/26 21:55:49 eric 46 45
c implement daemon mode
e
s 00004/00035/00404
d D 3.33 82/02/20 19:15:51 eric 45 44
c make rewriting of addresses in headers really work.  This adds the $q
c macro.  The rewriting of the From: address is still ad hoc and should
c be integrated into this format.
c Note:  old .cf files will not work with this version.
e
s 00006/00003/00433
d D 3.32 82/01/10 21:57:22 eric 44 43
c cleanup from cbosgd (Mark Horton) testing; some internals, mostly
c configuration.  This tries to make the configuration file (cf.m4) be
c much more general, but I fear it is doomed to failure -- it may be
c better to just tell people to roll their own.
e
s 00004/00003/00432
d D 3.31 81/12/06 12:37:54 eric 43 42
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00015/00001/00420
d D 3.30 81/12/05 14:13:51 eric 42 41
c insert SMTP "Mail-From:" line.
e
s 00008/00004/00413
d D 3.29 81/11/22 19:16:58 eric 41 40
c Edit queue control files when running queue (assuming there are still
c recipients left).  Also, modify the MsgPriority to be the absolute
c number (not the Priority: value); this allows us to include aging into
c the priority algorithm.
e
s 00007/00009/00410
d D 3.28 81/10/31 22:12:03 eric 40 39
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00005/00004/00414
d D 3.27 81/10/27 10:50:26 eric 39 38
c More queueing cleanup: implement timeouts (still one-stage),
c properly implement priorities (didn't work before), and miscellaneous
c cleanup.
e
s 00057/00006/00361
d D 3.26 81/10/26 14:21:47 eric 38 37
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00011/00001/00356
d D 3.25 81/10/20 11:36:10 eric 37 36
c clean up the SMTP stuff some more
e
s 00009/00004/00348
d D 3.24 81/10/19 22:26:41 eric 36 35
c implement SMTP mode -- doesn't support source routing or the
c HELP command, and doesn't give the correct code on VRFY or forwarding.
c Maybe someday....
e
s 00002/00002/00350
d D 3.23 81/10/02 10:07:29 eric 35 34
c use ruleset 2 to rewrite names after the $g translate (to fix some
c forwarding problems; do a read check in putmessage (just in case
c the temp file disappeared); some general cleanup.
e
s 00003/00001/00349
d D 3.22 81/09/12 15:48:40 eric 34 33
c change From: processing to reduce the number of Original-From:
c lines; change allocation of global variables.
e
s 00012/00001/00338
d D 3.21 81/09/07 12:33:23 eric 33 32
c add auto-rebuild on alias database; fix some aliasing bugs;
c add statistics to rebuild; slight code restructuring; change
c version handling one last (?) time
e
s 00008/00000/00331
d D 3.20 81/09/07 10:22:55 eric 32 31
c add NOTUNIX compile flag to turn off UNIX "From " line processing
e
s 00011/00008/00320
d D 3.19 81/09/06 19:48:09 eric 31 30
c cleanup, commenting, linting, etc.
e
s 00051/00001/00277
d D 3.18 81/08/22 17:51:59 eric 30 29
c Arrange to pull full name out of From line if found; includes
c Original-From: hacking (oh so ugly).  There's got to be a better way
c to do this...
e
s 00016/00001/00262
d D 3.17 81/08/22 14:31:52 eric 29 28
c fix improper UNIX From line crunching
e
s 00002/00003/00261
d D 3.16 81/08/20 15:13:38 eric 28 27
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00007/00012/00257
d D 3.15 81/08/18 16:46:56 eric 27 26
c convert to really do arpanet reply codes right (maybe)
e
s 00012/00001/00257
d D 3.14 81/08/18 10:00:19 eric 26 25
c insert missing newlines (since a blank line must preceed a message)
e
s 00003/00001/00255
d D 3.13 81/08/17 09:37:35 eric 25 24
c add header fields from new BB&N proposal ICST/CBOS - 80-2,
c "Specification of a Draft Message Format Standard" for NBS.
e
s 00000/00144/00256
d D 3.12 81/08/09 16:39:40 eric 24 23
c arrange for newaliases to work
e
s 00013/00019/00387
d D 3.11 81/08/09 15:02:17 eric 23 22
c lint it
e
s 00008/00006/00398
d D 3.10 81/03/28 14:18:15 eric 22 21
c don't throw away some headers
e
s 00005/00000/00399
d D 3.9 81/03/28 13:36:43 eric 21 20
c pass Full-Name field internally to do forwards correctly
e
s 00106/00104/00293
d D 3.8 81/03/28 12:02:33 eric 20 19
c put much more info in cf file (e.g., headers)
e
s 00001/00001/00396
d D 3.7 81/03/20 09:44:25 eric 19 18
c change name (again); from postbox to sendmail
e
s 00003/00024/00394
d D 3.6 81/03/11 10:45:36 eric 18 17
c general cleanup, esp. macro processor
e
s 00017/00003/00401
d D 3.5 81/03/09 13:21:39 eric 17 16
c first step at rewriting rules, etc.
e
s 00022/00042/00382
d D 3.4 81/03/07 17:45:34 eric 16 15
c drop stupid concatenation stuff; add hi_pptr
e
s 00004/00001/00420
d D 3.3 81/03/07 15:32:06 eric 15 14
c lint fixes
e
s 00005/00023/00416
d D 3.2 81/03/07 14:26:08 eric 14 13
c ----- delivermail ==> postbox -----
e
s 00301/00084/00138
d D 3.1 81/03/04 09:34:30 eric 13 12
c install fancy header stuff
e
s 00001/00001/00221
d D 2.3 80/12/06 17:31:22 eric 12 10
c fix botch with ^D from terminal
e
s 00024/00003/00219
d D 2.2.1.1 80/11/21 12:34:39 eric 11 10
c abortive attempt to make headers to (e.g.) msgs work
e
s 00009/00006/00213
d D 2.2 80/11/20 19:58:00 eric 10 8
c make dates be taken as date sent rather than date delivered
e
s 00048/00002/00217
d D 2.1.1.1 80/11/20 09:54:10 eric 9 8
c experimental save date technique
e
s 00000/00000/00219
d D 2.1 80/11/05 11:00:52 eric 8 7
c release 2
e
s 00004/00001/00215
d D 1.6 80/10/27 19:27:15 eric 7 6
c count & record message size
e
s 00002/00001/00214
d D 1.5 80/10/21 12:57:24 eric 6 5
c avoid bug in ungetc
e
s 00011/00003/00204
d D 1.4 80/10/15 10:19:45 eric 5 3
c try to handle out of disk space problem effectively
e
s 00010/00003/00204
d R 1.4 80/10/15 10:14:33 eric 4 3
c Try to clean up disk space problems
e
s 00002/00000/00205
d D 1.3 80/10/11 20:05:11 eric 3 2
c fix MsgId so that sizeof returns > 0
e
s 00205/00000/00000
d D 1.2 80/10/11 18:12:35 eric 2 1
c cleanup to simplify configuration & fix minor bugs
e
s 00000/00000/00000
d D 1.1 80/10/11 18:10:12 eric 1 0
e
u
U
f b 
t
T
I 80
/*
I 83
D 153
 * Copyright (c) 1983 Eric P. Allman
E 153
I 153
 * Copyright (c) 1983, 1995 Eric P. Allman
E 153
E 83
D 82
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 82
I 82
D 117
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 117
I 117
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 117
 *
D 88
 * Redistribution and use in source and binary forms are permitted
D 83
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 83
I 83
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
E 88
I 88
 * %sccs.include.redist.c%
E 88
E 83
 */
E 82

#ifndef lint
D 82
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 82
I 82
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 82

E 80
I 2
D 28
# include <stdio.h>
# include <ctype.h>
E 28
I 5
# include <errno.h>
E 5
D 14
# include "dlvrmail.h"
E 14
I 14
D 19
# include "postbox.h"
E 19
I 19
# include "sendmail.h"
E 19
E 14
D 80

D 43
static char	SccsId[] = "%W%	%G%";
E 43
I 43
SCCSID(%W%	%Y%	%G%);
E 80
E 43

/*
D 14
**  MAKETEMP -- read & parse message header & make temp file.
E 14
I 14
**  COLLECT -- read & parse message header & make temp file.
E 14
**
**	Creates a temporary file name and copies the standard
D 68
**	input to that file.  While it is doing it, it looks for
**	"From:" and "Sender:" fields to use as the from-person
**	(but only if the -a flag is specified).  It prefers to
**	to use the "Sender:" field.
E 68
I 68
**	input to that file.  Leading UNIX-style "From" lines are
**	stripped off (after important information is extracted).
E 68
**
D 68
**	MIT seems to like to produce "Sent-By:" fields instead
**	of "Sender:" fields.  We used to catch this, but it turns
**	out that the "Sent-By:" field doesn't always correspond
**	to someone real ("___057", for instance), as required by
**	the protocol.  So we limp by.....
**
E 68
**	Parameters:
I 133
**		fp -- file to read.
E 133
D 11
D 40
**		none
E 40
I 40
D 89
**		sayok -- if set, give an ARPANET style message
**			to say we are ready to collect input.
E 89
I 89
D 90
**		smtpmode -- if set, we are running SMTP: give an RFC819
E 90
I 90
**		smtpmode -- if set, we are running SMTP: give an RFC821
E 90
**			style message to say we are ready to collect
**			input, and never ignore a single dot to mean
**			end of message.
I 109
**		requeueflag -- this message will be requeued later, so
**			don't do final processing on it.
I 133
**		hdrp -- the location to stash the header.
E 133
**		e -- the current envelope.
E 109
E 89
E 40
E 11
I 11
**		from -- the person we think it may be from.  If
**			there is a "From" line, we will replace
**			the name of the person by this.  If NULL,
**			do no such replacement.
E 11
**
**	Returns:
D 11
D 27
**		Name of temp file.
E 27
I 27
**		none.
E 27
E 11
I 11
**		Name of the "from" person extracted from the
**		arpanet header.
E 11
**
**	Side Effects:
**		Temp file is created and filled.
D 27
**
**	Called By:
**		main
**
**	Notes:
**		This is broken off from main largely so that the
**		temp buffer can be deallocated.
E 27
I 27
**		The from person may be set.
E 27
*/

I 128
D 149
char	*CollectErrorMessage;
bool	CollectErrno;

E 149
I 135
static jmp_buf	CtxCollectTimeout;
D 143
static int	collecttimeout();
E 143
I 143
static void	collecttimeout();
E 143
static bool	CollectProgress;
static EVENT	*CollectTimeout;

/* values for input state machine */
#define IS_NORM		0	/* middle of line */
#define IS_BOL		1	/* beginning of line */
#define IS_DOT		2	/* read a dot at beginning of line */
#define IS_DOTCR	3	/* read ".\r" at beginning of line */
#define IS_CR		4	/* read a carriage return */

/* values for message state machine */
#define MS_UFROM	0	/* reading Unix from line */
#define MS_HEADER	1	/* reading message header */
#define MS_BODY		2	/* reading message body */

D 149

E 149
I 143
void
E 143
E 135
E 128
I 3
D 7
char	MsgId[MAXNAME];
E 7
I 7
D 13
char	MsgId[MAXNAME];		/* message-id, determined or created */
E 13
I 13
D 20
char	*MsgId;			/* message-id, determined or created */
E 20
E 13
D 49
long	MsgSize;		/* size of message in bytes */
I 28
D 38
FILE	*TempFile;		/* the tempfile (after creation) */
E 38
E 28
I 10
D 13
bool	GotHdr;			/* if set, "From ..." line exists */
E 13
I 13
D 20
char	*Date;			/* UNIX-style origination date */
E 20
E 13
E 10
E 7

E 49
E 3
D 27
char *
E 27
D 11
D 14
maketemp()
E 14
I 14
D 40
collect()
E 40
I 40
D 89
collect(sayok)
	bool sayok;
E 89
I 89
D 91
collect(smtpmode)
E 91
I 91
D 109
collect(smtpmode, e)
E 109
I 109
D 133
collect(smtpmode, requeueflag, e)
E 133
I 133
collect(fp, smtpmode, requeueflag, hdrp, e)
	FILE *fp;
E 133
E 109
E 91
	bool smtpmode;
I 109
	bool requeueflag;
I 133
	HDR **hdrp;
E 133
E 109
I 91
	register ENVELOPE *e;
E 91
E 89
E 40
E 14
E 11
I 11
maketemp(from)
	char *from;
E 11
{
	register FILE *tf;
I 89
	bool ignrdot = smtpmode ? FALSE : IgnrDot;
E 89
D 64
	char buf[MAXFIELD+1];
E 64
I 64
D 87
	char buf[MAXFIELD+2];
E 64
D 13
	static char fbuf[sizeof buf];
	extern char *prescan();
	extern char *matchhdr();
E 13
	register char *p;
E 87
I 87
D 96
	char buf[MAXFIELD], buf2[MAXFIELD];
E 96
I 96
D 131
	char buf[MAXLINE], buf2[MAXLINE];
E 131
I 131
	time_t dbto = smtpmode ? TimeOuts.to_datablock : 0;
E 131
E 96
D 135
	register char *workbuf, *freebuf;
E 135
I 135
	register char *bp;
D 143
	register int c;
E 143
I 143
	int c = '\0';
E 143
E 135
I 121
	bool inputerr = FALSE;
I 133
D 150
	bool headeronly = FALSE;
E 150
I 150
	bool headeronly;
E 150
E 133
I 131
D 135
	char buf[MAXLINE], buf2[MAXLINE];
E 135
I 135
	char *buf;
	int buflen;
	int istate;
	int mstate;
	char *pbp;
	char peekbuf[8];
I 148
	char dfname[20];
E 148
	char bufbuf[MAXLINE];
E 135
E 131
E 121
D 94
	register int workbuflen;
E 94
E 87
D 13
	register bool inheader;
	bool firstline;
E 13
D 31
	char c;
I 5
D 23
	extern int errno;
E 23
I 13
D 20
	register HDR *h;
	HDR **hp;
E 20
	extern bool isheader();
E 31
D 23
	extern char *newstr();
	extern char *xalloc();
D 20
	char *fname;
	char *fvalue;
E 20
	extern char *index(), *rindex();
E 23
D 60
	char *xfrom;
E 60
D 137
	extern char *hvalue();
E 137
I 87
D 135
	extern bool isheader(), flusheol();
E 135
I 135
	extern bool isheader();
I 143
	extern void eatheader();
	extern void tferror();
E 143
E 135
E 87
D 16
	extern char *makemsgid();
E 16
D 20
	struct hdrinfo *hi;
E 20
I 15
D 23
	extern char *strcpy(), *strcat(), *mktemp();
E 23
I 23
D 62
	extern char *mktemp();
I 38
D 60
	static char tempfname[40];
E 60
I 60
	static char tempfname[60];
E 62
E 60
D 44
	extern char *QueueDir;
E 44
I 43
D 65
	extern char *macvalue();
E 65
I 57
D 60
	register HDR *h;
	extern HDR *hrvalue();
E 60
E 57
E 43
E 38
D 31
	extern char *capitalize();
# ifdef DEBUG
E 23
I 20
	HDR *h;
I 23
# endif
E 31
E 23
E 20
E 15
E 13
I 11
	extern char *index();
E 11
E 5

I 128
D 149
	CollectErrorMessage = NULL;
	CollectErrno = 0;
E 149
I 133
D 150
	if (hdrp == NULL)
		hdrp = &e->e_header;
	else
		headeronly = TRUE;
E 150
I 150
	headeronly = hdrp != NULL;
E 150
E 133

E 128
	/*
	**  Create the temp file name and create the file.
	*/

D 23
	mktemp(InFileName);
	close(creat(InFileName, 0600));
E 23
I 23
D 38
	(void) mktemp(InFileName);
	(void) close(creat(InFileName, 0600));
E 23
	if ((tf = fopen(InFileName, "w")) == NULL)
E 38
I 38
D 53
	strcpy(tempfname, QueueDir);
D 51
	strcat(tempfname, "/dfaXXXXXX");
E 51
I 51
	strcat(tempfname, "/dfXXXXXX");
E 53
I 53
D 62
	(void) strcpy(tempfname, QueueDir);
	(void) strcat(tempfname, "/dfXXXXXX");
E 53
E 51
	(void) mktemp(tempfname);
D 48
	(void) close(creat(tempfname, 0600));
	if ((tf = fopen(tempfname, "w")) == NULL)
E 48
I 48
	if ((tf = dfopen(tempfname, "w")) == NULL)
E 62
I 62
D 91
	CurEnv->e_df = newstr(queuename(CurEnv, 'd'));
	if ((tf = dfopen(CurEnv->e_df, "w")) == NULL)
E 91
I 91
D 119
	e->e_df = newstr(queuename(e, 'd'));
E 119
I 119
D 133
	e->e_df = queuename(e, 'd');
	e->e_df = newstr(e->e_df);
E 119
D 112
	if ((tf = dfopen(e->e_df, "w")) == NULL)
E 112
I 112
D 130
	if ((tf = dfopen(e->e_df, O_WRONLY|O_CREAT, FileMode)) == NULL)
E 130
I 130
	if ((tf = dfopen(e->e_df, O_WRONLY|O_CREAT|O_TRUNC, FileMode)) == NULL)
E 133
I 133
	if (!headeronly)
E 133
E 130
E 112
E 91
E 62
E 48
E 38
	{
I 136
		struct stat stbuf;

E 136
D 38
		syserr("Cannot create %s", InFileName);
E 38
I 38
D 62
		syserr("Cannot create %s", tempfname);
E 62
I 62
D 91
		syserr("Cannot create %s", CurEnv->e_df);
E 91
I 91
D 133
		syserr("Cannot create %s", e->e_df);
E 91
E 62
E 38
D 27
		return (NULL);
E 27
I 27
D 44
		return;
E 44
I 44
D 132
		NoReturn = TRUE;
E 132
I 132
		e->e_flags |= EF_NORETURN;
E 132
		finis();
E 133
I 133
D 148
		e->e_df = queuename(e, 'd');
		e->e_df = newstr(e->e_df);
		if ((tf = dfopen(e->e_df, O_WRONLY|O_CREAT|O_TRUNC, FileMode)) == NULL)
E 148
I 148
		strcpy(dfname, queuename(e, 'd'));
		if ((tf = dfopen(dfname, O_WRONLY|O_CREAT|O_TRUNC, FileMode)) == NULL)
E 148
		{
D 148
			syserr("Cannot create %s", e->e_df);
E 148
I 148
			syserr("Cannot create %s", dfname);
E 148
D 146
			e->e_flags |= EF_NORETURN;
E 146
I 146
			e->e_flags |= EF_NO_BODY_RETN;
E 146
			finis();
		}
I 136
		if (fstat(fileno(tf), &stbuf) < 0)
			e->e_dfino = -1;
		else
I 138
		{
			e->e_dfdev = stbuf.st_dev;
E 138
			e->e_dfino = stbuf.st_ino;
I 138
		}
E 138
E 136
		HasEightBits = FALSE;
I 147
		e->e_msgsize = 0;
I 148
		e->e_flags |= EF_HAS_DF;
E 148
E 147
E 133
E 44
E 27
	}
I 48
D 53
	chmod(tempfname, 0600);
E 53
I 53
D 62
	(void) chmod(tempfname, 0600);
E 53
E 48
I 38
D 52
	InFileName = tempfname;
E 52
I 52
	CurEnv->e_df = tempfname;
E 62
I 62
D 66
	(void) chmod(CurEnv->e_df, 0600);
E 66
I 66
D 91
	(void) chmod(CurEnv->e_df, FileMode);
E 91
I 91
D 112
	(void) chmod(e->e_df, FileMode);
E 112
E 91
E 66
E 62
E 52
E 38

I 13
D 31
	/* try to read a UNIX-style From line */
E 31
I 31
	/*
I 42
D 61
	**  Create the Mail-From line if we want to.
E 61
I 61
D 63
	**  Create the Received: line if we want to.
E 61
	*/

D 44
	if (macvalue('s') != NULL)
E 44
I 44
	if (Smtp && macvalue('s') != NULL)
E 44
	{
		char xbuf[50];

D 43
		sprintf(xbuf, "Mail-From: %s$s received by $i at $b",
E 43
I 43
D 61
		(void) sprintf(xbuf, "Mail-From: %s$s received by $i at $b",
E 43
			macvalue('r') == NULL ? "" : "$r host ");
E 61
I 61
		/* this should be in the config file */
		(void) sprintf(xbuf, "Received: from $s by $i with SMTP; $b");
E 61
D 51
		(void) expand(xbuf, buf, &buf[sizeof buf - 1]);
E 51
I 51
		expand(xbuf, buf, &buf[sizeof buf - 1], CurEnv);
E 51
D 43
		chompheader(buf, FALSE);
E 43
I 43
		(void) chompheader(buf, FALSE);
E 43
	}

	/*
E 63
E 42
I 33
	**  Tell ARPANET to go ahead.
	*/

D 40
	if (ArpaMode == ARPA_MAIL)
	{
		extern char Arpa_Enter[];
E 40
I 40
D 89
	if (sayok)
E 89
I 89
	if (smtpmode)
E 89
D 104
		message("354", "Enter mail, end with \".\" on a line by itself");
E 104
I 104
		message("354 Enter mail, end with \".\" on a line by itself");
E 104
E 40

I 150
	if (tTd(30, 2))
		printf("collect\n");

E 150
I 126
D 135
	/* set global timer to monitor progress */
D 131
	sfgetset(TimeOuts.to_datablock);
E 131
I 131
	sfgetset(dbto);
E 131

E 135
E 126
D 40
		message(Arpa_Enter, "Enter mail, end with \".\" on a line by itself");
	}

E 40
	/*
E 33
D 135
	**  Try to read a UNIX-style From line
E 135
I 135
	**  Read the message.
	**
	**	This is done using two interleaved state machines.
	**	The input state machine is looking for things like
	**	hidden dots; the message state machine is handling
	**	the larger picture (e.g., header versus body).
E 135
	*/

E 31
D 46
	if (fgets(buf, sizeof buf, stdin) == NULL)
E 46
I 46
D 74
	if (fgets(buf, sizeof buf, InChannel) == NULL)
E 74
I 74
D 76
	if (sfgets(buf, sizeof buf, InChannel) == NULL)
E 74
E 46
D 27
		return (NULL);
E 27
I 27
		return;
E 76
I 76
D 87
	(void) sfgets(buf, sizeof buf, InChannel);
E 87
I 87
D 96
	if (sfgets(buf, MAXFIELD, InChannel) == NULL)
E 96
I 96
D 98
	if (sfgets(buf, MAXLINE, InChannel) == NULL)
E 98
I 98
D 102
	if (sfgets(buf, MAXLINE, InChannel, ReadTimeout) == NULL)
E 102
I 102
D 116
	if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock) == NULL)
E 116
I 116
D 131
	if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock,
E 131
I 131
D 133
	if (sfgets(buf, MAXLINE, InChannel, dbto,
E 131
			"initial message read") == NULL)
E 133
I 133
D 135
	if (sfgets(buf, MAXLINE, fp, dbto, "initial message read") == NULL)
E 133
E 116
E 102
E 98
E 96
		goto readerr;
E 87
E 76
I 37
	fixcrlf(buf, FALSE);
E 37
I 32
# ifndef NOTUNIX
E 32
E 27
D 33
	if (strncmp(buf, "From ", 5) == 0)
E 33
I 33
D 133
	if (!SaveFrom && strncmp(buf, "From ", 5) == 0)
E 133
I 133
	if (!headeronly && !SaveFrom && strncmp(buf, "From ", 5) == 0)
E 133
E 33
	{
I 87
D 131
		if (!flusheol(buf, InChannel))
E 131
I 131
D 133
		if (!flusheol(buf, InChannel, dbto))
E 133
I 133
		if (!flusheol(buf, fp, dbto))
E 133
E 131
			goto readerr;
E 87
D 91
		eatfrom(buf);
E 91
I 91
		eatfrom(buf, e);
E 91
D 23
		fgets(buf, sizeof buf, stdin);
E 23
I 23
D 46
		(void) fgets(buf, sizeof buf, stdin);
E 46
I 46
D 74
		(void) fgets(buf, sizeof buf, InChannel);
E 74
I 74
D 87
		(void) sfgets(buf, sizeof buf, InChannel);
E 87
I 87
D 96
		if (sfgets(buf, MAXFIELD, InChannel) == NULL)
E 96
I 96
D 98
		if (sfgets(buf, MAXLINE, InChannel) == NULL)
E 98
I 98
D 102
		if (sfgets(buf, MAXLINE, InChannel, ReadTimeout) == NULL)
E 102
I 102
D 116
		if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock) == NULL)
E 116
I 116
D 131
		if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock,
E 131
I 131
D 133
		if (sfgets(buf, MAXLINE, InChannel, dbto,
E 133
I 133
		if (sfgets(buf, MAXLINE, fp, dbto,
E 133
E 131
				"message header read") == NULL)
E 116
E 102
E 98
E 96
			goto readerr;
E 87
E 74
E 46
I 37
		fixcrlf(buf, FALSE);
E 37
E 23
	}
I 32
D 93
# endif NOTUNIX
E 93
I 93
# endif /* NOTUNIX */
E 135
I 135
	buf = bp = bufbuf;
	buflen = sizeof bufbuf;
	pbp = peekbuf;
	istate = IS_BOL;
	mstate = SaveFrom ? MS_HEADER : MS_UFROM;
	CollectProgress = FALSE;
E 135
E 93
E 32

E 13
D 135
	/*
D 42
	**  Copy stdin to temp file & do message editting.
E 42
I 42
D 46
	**  Copy stdin to temp file & do message editing.
E 46
I 46
D 133
	**  Copy InChannel to temp file & do message editing.
E 133
I 133
	**  Copy fp to temp file & do message editing.
E 133
E 46
E 42
D 13
	**	From person gets copied into fbuf.  At the end of
	**	this loop, if fbuf[0] == '\0' then there was no
	**	recognized from person in the message.  We also
	**	save the message id in MsgId.  The
	**	flag 'inheader' keeps track of whether we are
	**	in the header or in the body of the message.
	**	The flag 'firstline' is only true on the first
	**	line of a message.
E 13
	**	To keep certain mailers from getting confused,
	**	and to keep the output clean, lines that look
D 74
	**	like UNIX "From" lines are deleted in the header,
	**	and prepended with ">" in the body.
E 74
I 74
	**	like UNIX "From" lines are deleted in the header.
E 74
	*/
E 135
I 135
D 156
	/* if transmitting binary, don't map NL to EOL */
	if (e->e_bodytype != NULL && strcasecmp(e->e_bodytype, "8BITMIME") == 0)
		e->e_flags |= EF_NL_NOT_EOL;
E 135

E 156
D 13
	inheader = TRUE;
	firstline = TRUE;
	fbuf[0] = '\0';
D 12
	while (fgets(buf, sizeof buf, stdin) != NULL)
E 12
I 12
	while (!feof(stdin) && fgets(buf, sizeof buf, stdin) != NULL)
E 13
I 13
D 38
	for (; !feof(stdin); !feof(stdin) && fgets(buf, sizeof buf, stdin))
E 38
I 38
D 46
	for (; !feof(stdin); !feof(stdin) && fgets(buf, sizeof buf, stdin) != NULL)
E 46
I 46
D 64
	for (; !feof(InChannel); !feof(InChannel) && fgets(buf, sizeof buf, InChannel) != NULL)
E 64
I 64
D 68
	for (; !feof(InChannel); !feof(InChannel) && fgets(buf, MAXFIELD, InChannel) != NULL)
E 68
I 68
D 74
	for (; !feof(InChannel); !feof(InChannel) &&
				 fgets(buf, MAXFIELD, InChannel) != NULL)
E 74
I 74
D 76
	for (; !feof(InChannel); !feof(InChannel) && !ferror(InChannel) &&
				 sfgets(buf, MAXFIELD, InChannel) != NULL)
E 76
I 76
D 87
	do
E 87
I 87
D 135
	workbuf = buf;		/* `workbuf' contains a header field */
	freebuf = buf2;		/* `freebuf' can be used for read-ahead */
	for (;;)
E 135
I 135
	if (dbto != 0)
E 135
E 87
E 76
E 74
E 68
E 64
E 46
E 38
E 13
E 12
	{
I 94
D 135
		char *curbuf;
		int curbuffree;
		register int curbuflen;
		char *p;

E 94
I 31
D 76
		register char c;
E 76
I 76
D 87
		int c;
E 76
		extern bool isheader();

I 79
		/* drop out on error */
		if (ferror(InChannel))
E 87
I 87
		/* first, see if the header is over */
		if (!isheader(workbuf))
E 135
I 135
		/* handle possible input timeout */
		if (setjmp(CtxCollectTimeout) != 0)
E 135
		{
D 135
			fixcrlf(workbuf, TRUE);
E 87
			break;
E 135
I 135
#ifdef LOG
			syslog(LOG_NOTICE,
			    "timeout waiting for input from %s during message collect",
			    CurHostName ? CurHostName : "<local machine>");
#endif
			errno = 0;
			usrerr("451 timeout waiting for input during message collect");
			goto readerr;
E 135
I 87
		}
I 135
		CollectTimeout = setevent(dbto, collecttimeout, dbto);
	}
E 135
E 87

E 79
I 58
D 135
		/* if the line is too long, throw the rest away */
D 87
		if (index(buf, '\n') == NULL)
		{
D 76
			while ((c = getc(InChannel)) != '\n')
E 76
I 76
			while ((c = getc(InChannel)) != '\n' && c != EOF)
E 76
				continue;
			/* give an error? */
		}
E 87
I 87
D 131
		if (!flusheol(workbuf, InChannel))
E 131
I 131
D 133
		if (!flusheol(workbuf, InChannel, dbto))
E 133
I 133
		if (!flusheol(workbuf, fp, dbto))
E 133
E 131
			goto readerr;
E 87

E 58
I 37
D 64
		fixcrlf(buf, FALSE);
E 64
I 64
D 87
		fixcrlf(buf, TRUE);
E 87
I 87
		/* it's okay to toss '\n' now (flusheol() needed it) */
		fixcrlf(workbuf, TRUE);
E 87
E 64

E 37
E 31
D 13
		if (inheader && isalnum(buf[0]))
E 13
I 13
D 87
		/* see if the header is over */
		if (!isheader(buf))
			break;
E 87
I 87
D 94
		workbuflen = strlen(workbuf);
E 94
I 94
		curbuf = workbuf;
		curbuflen = strlen(curbuf);
D 96
		curbuffree = MAXFIELD - curbuflen;
E 96
I 96
		curbuffree = MAXLINE - curbuflen;
E 96
		p = curbuf + curbuflen;
E 94
E 87

		/* get the rest of this field */
E 135
I 135
	for (;;)
	{
		if (tTd(30, 35))
			printf("top, istate=%d, mstate=%d\n", istate, mstate);
E 135
D 46
		while ((c = getc(stdin)) == ' ' || c == '\t')
E 46
I 46
D 87
		while ((c = getc(InChannel)) == ' ' || c == '\t')
E 87
I 87
		for (;;)
E 87
E 46
E 13
		{
I 94
D 135
			int clen;

E 94
D 13
			/* get the rest of this field */
			while ((c = getc(stdin)) == ' ' || c == '\t')
			{
				p = &buf[strlen(buf)];
				*p++ = c;
				if (fgets(p, sizeof buf - (p - buf), stdin) == NULL)
					break;
			}
D 6
			ungetc(c, stdin);
E 6
I 6
			if (c != EOF)
				ungetc(c, stdin);
E 13
I 13
D 87
			p = &buf[strlen(buf)];
I 64
			*p++ = '\n';
E 64
			*p++ = c;
D 46
			if (fgets(p, sizeof buf - (p - buf), stdin) == NULL)
E 46
I 46
D 64
			if (fgets(p, sizeof buf - (p - buf), InChannel) == NULL)
E 64
I 64
D 74
			if (fgets(p, MAXFIELD - (p - buf), InChannel) == NULL)
E 74
I 74
			if (sfgets(p, MAXFIELD - (p - buf), InChannel) == NULL)
E 87
I 87
D 96
			if (sfgets(freebuf, MAXFIELD, InChannel) == NULL)
E 96
I 96
D 98
			if (sfgets(freebuf, MAXLINE, InChannel) == NULL)
E 98
I 98
D 102
			if (sfgets(freebuf, MAXLINE, InChannel, ReadTimeout) == NULL)
E 102
I 102
D 116
			if (sfgets(freebuf, MAXLINE, InChannel, TimeOuts.to_datablock) == NULL)
E 116
I 116
D 133
			if (sfgets(freebuf, MAXLINE, InChannel,
D 131
					TimeOuts.to_datablock,
E 131
I 131
					dbto,
E 133
I 133
			if (sfgets(freebuf, MAXLINE, fp, dbto,
E 133
E 131
					"message header read") == NULL)
E 135
I 135
			if (pbp > peekbuf)
				c = *--pbp;
			else
E 135
E 116
E 102
E 98
E 96
D 123
				goto readerr;
E 123
I 123
			{
D 135
				freebuf[0] = '\0';
				break;
E 135
I 135
D 150
				while (!feof(InChannel) && !ferror(InChannel))
E 150
I 150
				while (!feof(fp) && !ferror(fp))
E 150
				{
					errno = 0;
D 150
					c = fgetc(InChannel);
E 150
I 150
D 155
					c = fgetc(fp);
E 155
I 155
					c = getc(fp);
E 155
E 150
					if (errno != EINTR)
						break;
D 150
					clearerr(InChannel);
E 150
I 150
					clearerr(fp);
E 150
				}
				CollectProgress = TRUE;
D 150
				if (TrafficLogFile != NULL)
E 150
I 150
				if (TrafficLogFile != NULL && !headeronly)
E 150
				{
					if (istate == IS_BOL)
						fprintf(TrafficLogFile, "%05d <<< ",
							getpid());
					if (c == EOF)
						fprintf(TrafficLogFile, "[EOF]\n");
					else
D 155
						fputc(c, TrafficLogFile);
E 155
I 155
						putc(c, TrafficLogFile);
E 155
				}
				if (c == EOF)
					goto readerr;
				if (SevenBitInput)
					c &= 0x7f;
				else
					HasEightBits |= bitset(0x80, c);
D 147
				e->e_msgsize++;
E 147
I 147
				if (!headeronly)
					e->e_msgsize++;
E 147
E 135
			}
I 135
			if (tTd(30, 94))
				printf("istate=%d, c=%c (0x%x)\n",
					istate, c, c);
			switch (istate)
			{
			  case IS_BOL:
				if (c == '.')
				{
					istate = IS_DOT;
					continue;
				}
				break;
E 135
E 123

D 135
			/* is this a continuation line? */
			if (*freebuf != ' ' && *freebuf != '\t')
E 135
I 135
			  case IS_DOT:
				if (c == '\n' && !ignrdot &&
				    !bitset(EF_NL_NOT_EOL, e->e_flags))
					goto readerr;
				else if (c == '\r' &&
					 !bitset(EF_CRLF_NOT_EOL, e->e_flags))
				{
					istate = IS_DOTCR;
					continue;
				}
				else if (c != '.' ||
					 (OpMode != MD_SMTP &&
					  OpMode != MD_DAEMON &&
					  OpMode != MD_ARPAFTP))
				{
					*pbp++ = c;
					c = '.';
				}
E 135
E 87
E 74
E 64
E 46
				break;
I 37
D 64
			fixcrlf(p, FALSE);
E 64
I 64
D 87
			fixcrlf(p, TRUE);
E 87
I 87

D 131
			if (!flusheol(freebuf, InChannel))
E 131
I 131
D 133
			if (!flusheol(freebuf, InChannel, dbto))
E 133
I 133
D 135
			if (!flusheol(freebuf, fp, dbto))
E 133
E 131
				goto readerr;
E 135
I 135
			  case IS_DOTCR:
				if (c == '\n')
					goto readerr;
				else
				{
					/* push back the ".\rx" */
					*pbp++ = c;
					*pbp++ = '\r';
					c = '.';
				}
				break;
E 135

D 94
			/* yes; append line to `workbuf' if there's room */
			if (workbuflen < MAXFIELD-3)
E 94
I 94
D 135
			fixcrlf(freebuf, TRUE);
D 96
			clen = strlen(freebuf);
E 96
I 96
			clen = strlen(freebuf) + 1;
E 135
I 135
			  case IS_CR:
D 139
				if (c != '\n')
E 139
I 139
				if (c == '\n')
					istate = IS_BOL;
				else
E 139
				{
D 150
					ungetc(c, InChannel);
E 150
I 150
					ungetc(c, fp);
E 150
					c = '\r';
I 139
					istate = IS_NORM;
E 139
				}
D 139
				else if (!bitset(EF_CRLF_NOT_EOL, e->e_flags))
					istate = IS_BOL;
				break;
E 139
I 139
				goto bufferchar;
E 139
			}
E 135
E 96

D 135
			/* if insufficient room, dynamically allocate buffer */
			if (clen >= curbuffree)
E 135
I 135
D 139
			if (c == '\r')
E 139
I 139
			if (c == '\r' && !bitset(EF_CRLF_NOT_EOL, e->e_flags))
E 139
E 135
E 94
			{
D 94
				register char *p = workbuf + workbuflen;
				register char *q = freebuf;
E 94
I 94
D 135
				/* reallocate buffer */
				int nbuflen = ((p - curbuf) + clen) * 2;
				char *nbuf = xalloc(nbuflen);
E 135
I 135
				istate = IS_CR;
				continue;
			}
			else if (c == '\n' && !bitset(EF_NL_NOT_EOL, e->e_flags))
				istate = IS_BOL;
			else
				istate = IS_NORM;
E 135
E 94

I 139
bufferchar:
E 139
D 94
				/* we have room for more of this field */
				fixcrlf(freebuf, TRUE);
D 92
				*p++ = '\n'; workbuflen++;
E 92
I 92
				*p++ = '\n';
				workbuflen++;
E 92
				while(*q != '\0' && workbuflen < MAXFIELD-1)
				{
					*p++ = *q++;
					workbuflen++;
				}
				*p = '\0';
E 94
I 94
D 96
				p = nbuf + (p - curbuf);
				curbuffree = nbuflen - (p - workbuf) - clen;
				bcopy(curbuf, nbuf, p - curbuf);
E 96
I 96
D 135
				p = nbuf + curbuflen;
				curbuffree = nbuflen - curbuflen;
				bcopy(curbuf, nbuf, curbuflen);
E 96
				if (curbuf != buf && curbuf != buf2)
					free(curbuf);
				curbuf = nbuf;
E 135
I 135
			if (mstate == MS_BODY)
			{
				/* just put the character out */
D 141
				fputc(c, tf);
E 141
I 141
				if (MaxMessageSize <= 0 ||
				    e->e_msgsize <= MaxMessageSize)
D 155
					fputc(c, tf);
E 155
I 155
					putc(c, tf);
E 155
E 141
				continue;
E 135
E 94
			}
I 94
D 96
			bcopy(freebuf, p, clen);
			p += clen;
E 96
I 96
D 135
			*p++ = '\n';
			bcopy(freebuf, p, clen - 1);
			p += clen - 1;
E 96
			curbuffree -= clen;
I 96
			curbuflen += clen;
E 96
E 94
E 87
E 64
E 37
E 13
E 6
		}
I 94
		*p++ = '\0';
E 135
E 94
I 13
D 23
		if (c != EOF)
			ungetc(c, stdin);
E 23
I 23
D 46
		if (!feof(stdin))
			(void) ungetc(c, stdin);
E 46
I 46
D 79
		if (!feof(InChannel))
E 79
I 79
D 87
		if (!feof(InChannel) && !ferror(InChannel))
E 79
			(void) ungetc(c, InChannel);
E 87
E 46
E 23
E 13

D 13
		if (!IgnrDot && buf[0] == '.' && (buf[1] == '\n' || buf[1] == '\0'))
			break;
E 13
I 13
D 49
		MsgSize += strlen(buf);
E 49
I 49
D 87
		CurEnv->e_msgsize += strlen(buf);
E 87
I 87
D 91
		CurEnv->e_msgsize += workbuflen;
E 91
I 91
D 94
		e->e_msgsize += workbuflen;
E 94
I 94
D 135
		e->e_msgsize += curbuflen;
E 135
I 135
			/* header -- buffer up */
			if (bp >= &buf[buflen - 2])
			{
				char *obuf;
E 135
E 94
E 91
E 87
E 49
E 13

D 13
		/* are we still in the header? */
		if ((buf[0] == '\n' || buf[0] == '\0') && inheader)
E 13
I 13
D 135
		/*
I 87
		**  The working buffer now becomes the free buffer, since
		**  the free buffer contains a new header field.
		**
		**  This is premature, since we still havent called
		**  chompheader() to process the field we just created
		**  (so the call to chompheader() will use `freebuf').
		**  This convolution is necessary so that if we break out
		**  of the loop due to H_EOH, `workbuf' will always be
		**  the next unprocessed buffer.
		*/
E 135
I 135
				if (mstate != MS_HEADER)
					break;
E 135

D 135
		{
			register char *tmp = workbuf;
			workbuf = freebuf;
			freebuf = tmp;
E 135
I 135
				/* out of space for header */
				obuf = buf;
				if (buflen < MEMCHUNKSIZE)
					buflen *= 2;
				else
					buflen += MEMCHUNKSIZE;
				buf = xalloc(buflen);
				bcopy(obuf, buf, bp - obuf);
				bp = &buf[bp - obuf];
				if (obuf != bufbuf)
					free(obuf);
			}
D 151
			*bp++ = c;
E 151
I 151
			if (c != '\0')
				*bp++ = c;
E 151
			if (istate == IS_BOL)
				break;
E 135
		}
I 135
		*bp = '\0';
E 135

D 135
		/*
E 87
		**  Snarf header away.
		*/
E 135
I 135
nextstate:
		if (tTd(30, 35))
			printf("nextstate, istate=%d, mstate=%d, line = \"%s\"\n",
				istate, mstate, buf);
		switch (mstate)
		{
I 143
			extern int chompheader();

E 143
		  case MS_UFROM:
			mstate = MS_HEADER;
			if (strncmp(buf, "From ", 5) == 0)
			{
I 143
				extern void eatfrom();

E 143
I 140
				bp = buf;
E 140
				eatfrom(buf, e);
				continue;
			}
			/* fall through */
E 135

D 20
		/* strip off trailing newline */
		p = rindex(buf, '\n');
		if (p != NULL)
			*p = '\0';

		/* find canonical name */
		fname = buf;
		p = index(buf, ':');
		fvalue = &p[1];
		while (isspace(*--p))
			continue;
		*++p = '\0';
		makelower(fname);

		/* strip field value on front */
		if (*fvalue == ' ')
			fvalue++;

		/* search header list for this header */
		for (hp = &Header, h = Header; h != NULL; hp = &h->h_link, h = h->h_link)
E 13
		{
D 13
			inheader = FALSE;
			if (MsgId[0] == '\0')
E 13
I 13
D 14
			if (strcmp(fname, h->h_field) == 0 && flagset(H_CONCAT|H_DEFAULT, h->h_flags))
E 14
I 14
			if (strcmp(fname, h->h_field) == 0 && bitset(H_DEFAULT, h->h_flags))
E 14
				break;
		}
I 16

		/* see if it is a known type */
		for (hi = HdrInfo; hi->hi_field != NULL; hi++)
		{
			if (strcmp(hi->hi_field, fname) == 0)
				break;
		}

		/* if this means "end of header" quit now */
		if (bitset(H_EOH, hi->hi_flags))
E 20
I 20
D 22
		if (bitset(H_EOH, chompheader(buf, 0)))
E 22
I 22
D 87
		if (bitset(H_EOH, chompheader(buf, FALSE)))
E 87
I 87
D 91
		if (bitset(H_EOH, chompheader(freebuf, FALSE)))
E 91
I 91
D 94
		if (bitset(H_EOH, chompheader(freebuf, FALSE, e)))
E 94
I 94
D 135
		if (bitset(H_EOH, chompheader(curbuf, FALSE, e)))
E 94
E 91
E 87
E 22
E 20
			break;
E 135
I 135
		  case MS_HEADER:
			if (!isheader(buf))
			{
				mstate = MS_BODY;
				goto nextstate;
			}
E 135
I 94

D 135
		/*
		**  If the buffer was dynamically allocated, free it.
		*/
E 135
I 135
			/* check for possible continuation line */
			do
			{
D 150
				clearerr(InChannel);
E 150
I 150
				clearerr(fp);
E 150
				errno = 0;
D 150
				c = fgetc(InChannel);
E 150
I 150
D 155
				c = fgetc(fp);
E 155
I 155
				c = getc(fp);
E 155
E 150
			} while (errno == EINTR);
			if (c != EOF)
D 150
				ungetc(c, InChannel);
E 150
I 150
				ungetc(c, fp);
E 150
			if (c == ' ' || c == '\t')
			{
				/* yep -- defer this */
				continue;
			}
E 135

D 135
		if (curbuf != buf && curbuf != buf2)
			free(curbuf);
E 94
D 20

		/* create/fill in a new node */
E 16
		if (h == NULL)
		{
			/* create a new node */
D 14
# ifdef DEBUG
			if (Debug)
				printf("new field '%s', value '%s'\n", fname, fvalue);
# endif DEBUG
E 14
			*hp = h = (HDR *) xalloc(sizeof *h);
			h->h_field = newstr(fname);
			h->h_value = NULL;
			h->h_link = NULL;
D 16
			h->h_flags = 0;

			/* see if it is a known type */
			for (hi = HdrInfo; hi->hi_field != NULL; hi++)
E 13
			{
D 13
				makemsgid();
				if (UseMsgId)
					fprintf(tf, "Message-Id: <%s>\n", MsgId);
E 13
I 13
				if (strcmp(hi->hi_field, h->h_field) == 0)
				{
					h->h_flags = hi->hi_flags;
					break;
				}
E 13
			}
E 16
I 16
			h->h_flags = hi->hi_flags;
E 16
I 13
		}
D 14
		else if (flagset(H_DEFAULT, h->h_flags))
E 14
I 14
D 16
		else if (bitset(H_DEFAULT, h->h_flags))
E 14
		{
			/* overriding default, throw out old value */
E 16
I 16
		if (h->h_value != NULL)
E 16
E 13
D 14
# ifdef DEBUG
			if (Debug)
D 13
				printf("EOH\n");
E 13
I 13
				printf("overriding '%s', old='%s', new='%s'\n",
				       fname, h->h_value, fvalue);
E 13
# endif DEBUG
E 14
I 13
			free(h->h_value);
D 16
			h->h_value = NULL;
E 13
		}
E 16
I 16
		h->h_value = newstr(fvalue);
E 16

D 13
		/* Hide UNIX-like From lines */
D 9
D 10
		if (buf[0] == 'F' && buf[1] == 'r' && buf[2] == 'o' &&
		    buf[3] == 'm' && buf[4] == ' ')
E 10
I 10
		if (strncmp(buf, "From ", 5) == 0)
E 13
I 13
D 16
		/* do something with the value */
		if (h->h_value == NULL)
E 13
E 10
E 9
I 9
		if (strncmp(buf, "From ", 5) == 0)
E 9
		{
D 10
			if (firstline && !SaveFrom)
I 9
			{
				savedate(buf);
E 9
				continue;
I 9
			}
E 9
			fputs(">", tf);
I 7
			MsgSize++;
E 10
I 10
D 13
			if (!firstline)
			{
				fputs(">", tf);
				MsgSize++;
			}
			else
I 11
			{
E 11
				GotHdr++;
E 13
I 13
D 14
# ifdef DEBUG
			if (Debug)
				printf("installing '%s: %s'\n", fname, fvalue);
# endif DEBUG
E 14
			h->h_value = newstr(fvalue);
E 13
I 11
				if (from != NULL)
				{
					fputs("From ", tf);
					fputs(from, tf);
					MsgSize += strlen(from) + 5;
					p = index(&buf[5], ' ');
					if (p != NULL)
					{
						fputs(p, tf);
						MsgSize += strlen(p);
					}
					continue;
				}
			}
E 11
E 10
E 7
		}
D 13

		if (inheader && !isspace(buf[0]))
E 13
I 13
		else
E 13
		{
D 13
			/* find out if this is really a header */
			for (p = buf; *p != ':' && *p != '\0' && !isspace(*p); p++)
				continue;
			while (*p != ':' && isspace(*p))
				p++;
			if (*p != ':')
			{
				inheader = FALSE;
E 13
I 13
D 15
			register int len;
E 15
I 15
			register unsigned len;
E 15

			/* concatenate the two values */
E 13
D 14
# ifdef DEBUG
D 13
				if (Debug)
					printf("EOH?\n");
E 13
I 13
			if (Debug)
				printf("concat '%s: %s' with '%s'\n", fname,
				       h->h_value, fvalue);
E 13
# endif DEBUG
E 14
D 13
			}
E 13
I 13
			len = strlen(h->h_value) + strlen(fvalue) + 2;
			p = xalloc(len);
			strcpy(p, h->h_value);
			strcat(p, ",");
			strcat(p, fvalue);
			free(h->h_value);
			h->h_value = p;
E 13
		}
E 16
I 16
		/* save the location of this field */
		if (hi->hi_pptr != NULL)
			*hi->hi_pptr = h->h_value;
E 20
E 16
I 13
D 76
	}
E 76
I 76
D 87
	} while (sfgets(buf, MAXFIELD, InChannel) != NULL);
E 87
I 87
	}
E 87
E 76
E 13

D 13
		if (inheader)
		{
			/* find the sender */
			p = matchhdr(buf, "sender");
			if (p == NULL && fbuf[0] == '\0')
				p = matchhdr(buf, "from");
			if (p != NULL)
				prescan(p, fbuf, &fbuf[sizeof fbuf - 1], '\0');
E 13
I 13
D 86
# ifdef DEBUG
E 86
D 57
	if (Debug)
E 57
I 57
	if (tTd(30, 1))
E 57
		printf("EOH\n");
D 86
# endif DEBUG
E 86
E 13

I 133
	if (headeronly)
	{
		if (*workbuf != '\0')
			syserr("collect: lost first line of message");
		goto readerr;
	}

E 133
D 13
			/* find the message id */
			p = matchhdr(buf, "message-id");
			if (p != NULL && MsgId[0] == '\0')
				prescan(p, MsgId, &MsgId[sizeof MsgId - 1], '\0');
E 13
I 13
D 87
	/* throw away a blank line */
D 64
	if (buf[0] == '\n')
E 64
I 64
	if (buf[0] == '\0')
E 64
I 37
D 76
	{
E 76
E 37
D 23
		fgets(buf, sizeof buf, stdin);
E 23
I 23
D 46
		(void) fgets(buf, sizeof buf, stdin);
E 46
I 46
D 64
		(void) fgets(buf, sizeof buf, InChannel);
E 46
I 37
		fixcrlf(buf, FALSE);
E 64
I 64
D 74
		(void) fgets(buf, MAXFIELD, InChannel);
E 74
I 74
		(void) sfgets(buf, MAXFIELD, InChannel);
E 87
I 87
	if (*workbuf == '\0')
	{
		/* throw away a blank line */
D 96
		if (sfgets(buf, MAXFIELD, InChannel) == NULL)
E 96
I 96
D 98
		if (sfgets(buf, MAXLINE, InChannel) == NULL)
E 98
I 98
D 102
		if (sfgets(buf, MAXLINE, InChannel, ReadTimeout) == NULL)
E 102
I 102
D 116
		if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock) == NULL)
E 116
I 116
D 131
		if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock,
E 131
I 131
D 133
		if (sfgets(buf, MAXLINE, InChannel, dbto,
E 133
I 133
		if (sfgets(buf, MAXLINE, fp, dbto,
E 133
E 131
				"message separator read") == NULL)
E 116
E 102
E 98
E 96
			goto readerr;
	}
	else if (workbuf == buf2)	/* guarantee `buf' contains data */
		(void) strcpy(buf, buf2);
E 87
E 74
D 76
		fixcrlf(buf, TRUE);
E 64
	}
E 76
E 37
E 23

	/*
	**  Collect the body of the message.
	*/

D 46
	for (; !feof(stdin); !feof(stdin) && fgets(buf, sizeof buf, stdin) != NULL)
E 46
I 46
D 68
	for (; !feof(InChannel); !feof(InChannel) && fgets(buf, sizeof buf, InChannel) != NULL)
E 68
I 68
D 74
	for (; !feof(InChannel); !feof(InChannel) &&
				 fgets(buf, sizeof buf, InChannel) != NULL)
E 74
I 74
D 76
	for (; !feof(InChannel); !feof(InChannel) && !ferror(InChannel) &&
				 sfgets(buf, sizeof buf, InChannel) != NULL)
E 76
I 76
D 121
	do
E 121
I 121
	for (;;)
E 121
E 76
E 74
E 68
E 46
	{
I 26
D 68
		register int i;
E 68
I 36
		register char *bp = buf;
E 36

I 37
D 64
		fixcrlf(buf, FALSE);
E 64
I 64
		fixcrlf(buf, TRUE);
E 64

E 37
E 26
		/* check for end-of-message */
D 89
		if (!IgnrDot && buf[0] == '.' && (buf[1] == '\n' || buf[1] == '\0'))
E 89
I 89
		if (!ignrdot && buf[0] == '.' && (buf[1] == '\n' || buf[1] == '\0'))
E 135
I 135
			/* trim off trailing CRLF or NL */
			if (*--bp != '\n' || *--bp != '\r')
				bp++;
			*bp = '\0';
D 150
			if (bitset(H_EOH, chompheader(buf, FALSE, e)))
E 150
I 150
			if (bitset(H_EOH, chompheader(buf, FALSE, hdrp, e)))
E 150
				mstate = MS_BODY;
E 135
E 89
			break;

I 36
D 135
		/* check for transparent dot */
D 67
		if (Smtp && *bp == '.')
E 67
I 67
D 68
		if (OpMode == MD_SMTP && *bp == '.')
E 68
I 68
D 89
		if (OpMode == MD_SMTP && !IgnrDot && bp[0] == '.' && bp[1] == '.')
E 89
I 89
D 124
		if (OpMode == MD_SMTP && bp[0] == '.' && bp[1] == '.')
E 124
I 124
		if ((OpMode == MD_SMTP || OpMode == MD_DAEMON) &&
		    bp[0] == '.' && bp[1] == '.')
E 124
E 89
E 68
E 67
			bp++;
E 135
I 135
		  case MS_BODY:
			if (tTd(30, 1))
				printf("EOH\n");
			if (headeronly)
				goto readerr;
			bp = buf;
E 135

E 36
I 32
D 73
# ifndef NOTUNIX
E 32
		/* Hide UNIX-like From lines */
D 36
		if (strncmp(buf, "From ", 5) == 0)
E 36
I 36
		if (strncmp(bp, "From ", 5) == 0)
E 36
		{
			fputs(">", tf);
D 49
			MsgSize++;
E 49
I 49
			CurEnv->e_msgsize++;
E 49
E 13
		}
I 32
# endif NOTUNIX
E 32
I 7
D 26
		MsgSize += strlen(buf);
E 26
I 26

E 73
D 135
		/*
		**  Figure message length, output the line to the temp
		**  file, and insert a newline if missing.
		*/
E 135
I 135
			/* toss blank line */
			if ((!bitset(EF_CRLF_NOT_EOL, e->e_flags) &&
				bp[0] == '\r' && bp[1] == '\n') ||
			    (!bitset(EF_NL_NOT_EOL, e->e_flags) &&
				bp[0] == '\n'))
			{
				break;
			}
E 135

D 36
		i = strlen(buf);
E 36
I 36
D 68
		i = strlen(bp);
E 36
D 49
		MsgSize += i;
E 49
I 49
D 64
		CurEnv->e_msgsize += i;
E 64
I 64
		CurEnv->e_msgsize += i + 1;
E 68
I 68
D 91
		CurEnv->e_msgsize += strlen(bp) + 1;
E 91
I 91
D 135
		e->e_msgsize += strlen(bp) + 1;
E 91
E 68
E 64
E 49
E 26
E 7
D 36
		fputs(buf, tf);
I 26
		if (buf[i - 1] != '\n')
E 36
I 36
		fputs(bp, tf);
D 64
		if (bp[i - 1] != '\n')
E 36
			fputs("\n", tf);
E 64
I 64
		fputs("\n", tf);
E 64
E 26
D 13
		firstline = FALSE;
E 13
		if (ferror(tf))
D 72
		{
D 5
			syserr("Cannot write %s", InFileName);
			clearerr(tf);
			break;
E 5
I 5
			if (errno == ENOSPC)
			{
D 23
				freopen(InFileName, "w", tf);
E 23
I 23
D 52
				(void) freopen(InFileName, "w", tf);
E 52
I 52
				(void) freopen(CurEnv->e_df, "w", tf);
E 52
E 23
				fputs("\nMAIL DELETED BECAUSE OF LACK OF DISK SPACE\n\n", tf);
D 35
				syserr("Out of disk space for temp file");
E 35
I 35
D 37
				syserr("collect: Out of disk space for temp file");
E 37
I 37
				usrerr("452 Out of disk space for temp file");
E 37
E 35
			}
			else
D 35
				syserr("Cannot write %s", InFileName);
E 35
I 35
D 52
				syserr("collect: Cannot write %s", InFileName);
E 52
I 52
				syserr("collect: Cannot write %s", CurEnv->e_df);
E 52
E 35
D 23
			freopen("/dev/null", "w", tf);
E 23
I 23
			(void) freopen("/dev/null", "w", tf);
E 23
E 5
		}
E 72
I 72
D 91
			tferror(tf);
E 91
I 91
			tferror(tf, e);
E 91
E 72
D 76
	}
E 76
I 76
D 96
	} while (sfgets(buf, MAXFIELD, InChannel) != NULL);
E 96
I 96
D 98
	} while (sfgets(buf, MAXLINE, InChannel) != NULL);
E 98
I 98
D 102
	} while (sfgets(buf, MAXLINE, InChannel, ReadTimeout) != NULL);
E 102
I 102
D 116
	} while (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock) != NULL);
E 116
I 116
D 121
	} while (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock,
			"message body read") != NULL);
E 121
I 121
D 131
		if (sfgets(buf, MAXLINE, InChannel, TimeOuts.to_datablock,
E 131
I 131
D 133
		if (sfgets(buf, MAXLINE, InChannel, dbto,
E 131
				"message body read") == NULL)
E 133
I 133
		if (sfgets(buf, MAXLINE, fp, dbto, "message body read") == NULL)
E 133
			goto readerr;
E 135
I 135
			/* if not a blank separator, write it out */
D 141
			while (*bp != '\0')
				fputc(*bp++, tf);
E 141
I 141
			if (MaxMessageSize <= 0 ||
			    e->e_msgsize <= MaxMessageSize)
			{
				while (*bp != '\0')
D 155
					fputc(*bp++, tf);
E 155
I 155
					putc(*bp++, tf);
E 155
			}
E 141
			break;
		}
		bp = buf;
E 135
	}
E 121
E 116
E 102
E 98
E 96
I 87

I 121
D 133
	if (feof(InChannel) || ferror(InChannel))
	{
E 133
E 121
readerr:
I 133
	if ((feof(fp) && smtpmode) || ferror(fp))
	{
I 158
		const char *errmsg = errstring(errno);

E 158
E 133
I 123
		if (tTd(30, 1))
D 152
			printf("collect: read error\n");
E 152
I 152
D 158
			printf("collect: %s\n", errstring(errno));
E 158
I 158
			printf("collect: premature EOM: %s\n", errmsg);
#ifdef LOG
		if (LogLevel >= 2)
			syslog(LOG_WARNING, "collect: premature EOM: %s", errmsg);
#endif
E 158
E 152
E 123
I 121
		inputerr = TRUE;
	}
I 126

	/* reset global timer */
D 135
	sfgetset((time_t) 0);
E 135
I 135
	clrevent(CollectTimeout);
E 135
E 126

E 121
E 87
E 76
I 72
D 133
	if (fflush(tf) != 0)
D 91
		tferror(tf);
E 91
I 91
		tferror(tf, e);
I 115
D 122
	(void) fsync(fileno(tf));
E 115
E 91
E 72
D 23
	fclose(tf);
E 23
I 23
	(void) fclose(tf);
E 122
I 122
	if (fsync(fileno(tf)) < 0 || fclose(tf) < 0)
E 133
I 133
	if (headeronly)
		return;

	if (tf != NULL)
E 133
	{
D 128
		syserr("cannot sync message data to disk (%s)", e->e_df);
E 128
I 128
D 133
		tferror(tf, e);
E 128
		finis();
E 133
I 133
		if (fflush(tf) != 0)
			tferror(tf, e);
		if (fsync(fileno(tf)) < 0 || fclose(tf) < 0)
		{
			tferror(tf, e);
			finis();
		}
E 133
	}
E 122
E 23
D 13
	if (MsgId[0] == '\0')
		makemsgid();
E 13
I 13

I 70
D 128
	/* An EOF when running SMTP is an error */
D 79
	if (feof(InChannel) && OpMode == MD_SMTP)
E 79
I 79
D 121
	if ((feof(InChannel) || ferror(InChannel)) && OpMode == MD_SMTP)
E 121
I 121
D 124
	if (inputerr && OpMode == MD_SMTP)
E 124
I 124
	if (inputerr && (OpMode == MD_SMTP || OpMode == MD_DAEMON))
E 128
I 128
D 149
	if (CollectErrorMessage != NULL && Errors <= 0)
E 149
I 149
	/* An EOF when running SMTP is an error */
	if (inputerr && (OpMode == MD_SMTP || OpMode == MD_DAEMON))
E 149
E 128
E 124
E 121
E 79
D 77
		syserr("collect: unexpected close");
E 77
I 77
	{
I 128
D 149
		if (CollectErrno != 0)
		{
			errno = CollectErrno;
D 148
			syserr(CollectErrorMessage, e->e_df);
E 148
I 148
			syserr(CollectErrorMessage, dfname);
E 148
			finis();
		}
		usrerr(CollectErrorMessage);
	}
	else if (inputerr && (OpMode == MD_SMTP || OpMode == MD_DAEMON))
	{
		/* An EOF when running SMTP is an error */
E 149
E 128
I 105
		char *host;
I 121
		char *problem;
E 121
E 105
I 87
D 108
		int usrerr(), syserr();
E 108
I 101

I 105
		host = RealHostName;
		if (host == NULL)
			host = "localhost";

I 121
D 133
		if (feof(InChannel))
E 133
I 133
		if (feof(fp))
E 133
			problem = "unexpected close";
D 133
		else if (ferror(InChannel))
E 133
I 133
		else if (ferror(fp))
E 133
			problem = "I/O error";
		else
			problem = "read timeout";
E 121
E 105
E 101
E 87
D 84
		syserr("collect: unexpected close, from=%s", CurEnv->e_from.q_paddr);
E 84
I 84
D 85
		if (RealHostName)
E 85
I 85
# ifdef LOG
D 101
		if (RealHostName != NULL && LogLevel > 0)
E 101
I 101
D 105
		if (RealHostName != NULL && LogLevel > 0 && feof(InChannel))
E 105
I 105
D 133
		if (LogLevel > 0 && feof(InChannel))
E 133
I 133
		if (LogLevel > 0 && feof(fp))
E 133
E 105
E 101
E 85
			syslog(LOG_NOTICE,
D 105
			    "collect: unexpected close on connection from %s: %m\n",
D 91
			    CurEnv->e_from.q_paddr, RealHostName);
E 91
I 91
			    e->e_from.q_paddr, RealHostName);
E 105
I 105
D 121
			    "collect: unexpected close on connection from %s, sender=%s: %m\n",
			    host, e->e_from.q_paddr);
E 121
I 121
D 129
			    "collect: %s on connection from %s, sender=%s: %m\n",
			    problem, host, e->e_from.q_paddr);
E 129
I 129
			    "collect: %s on connection from %s, sender=%s: %s\n",
			    problem, host, e->e_from.q_paddr, errstring(errno));
E 129
E 121
E 105
E 91
I 85
# endif
E 85
D 87
		usrerr("collect: unexpected close, from=%s", CurEnv->e_from.q_paddr);
E 87
I 87
D 101
		(feof(InChannel) ? usrerr: syserr)
D 91
			("collect: unexpected close, from=%s", CurEnv->e_from.q_paddr);
E 91
I 91
			("collect: unexpected close, from=%s", e->e_from.q_paddr);
E 101
I 101
D 125
		(feof(InChannel) ? usrerr : syserr)
D 104
			("collect: unexpected close on connection, from=%s",
E 104
I 104
D 105
			("451 collect: unexpected close on connection, from=%s",
E 104
				e->e_from.q_paddr);
E 105
I 105
D 121
			("451 collect: unexpected close on connection from %s, from=%s",
				host, e->e_from.q_paddr);
E 121
I 121
			("451 collect: %s on connection from %s, from=%s",
E 125
I 125
D 133
		if (feof(InChannel))
E 133
I 133
		if (feof(fp))
E 133
			usrerr("451 collect: %s on connection from %s, from=%s",
				problem, host, e->e_from.q_paddr);
		else
			syserr("451 collect: %s on connection from %s, from=%s",
E 125
				problem, host, e->e_from.q_paddr);
E 121
E 105
E 101
E 91
E 87
E 84

		/* don't return an error indication */
D 91
		CurEnv->e_to = NULL;
		CurEnv->e_flags &= ~EF_FATALERRS;
E 91
I 91
		e->e_to = NULL;
		e->e_flags &= ~EF_FATALERRS;
I 120
		e->e_flags |= EF_CLRQUEUE;
E 120
E 91

		/* and don't try to deliver the partial message either */
I 121
		if (InChild)
			ExitStat = EX_QUIT;
E 121
		finis();
	}
E 77

E 70
	/*
	**  Find out some information from the headers.
D 16
	**	Examples are who is the from person, the date, the
	**	message-id, etc.
E 16
I 16
D 20
	**	Examples are who is the from person & the date.  Some
	**	fields, e.g., Message-Id, may have been handled by
	**	the hi_pptr mechanism.
E 20
I 20
	**	Examples are who is the from person & the date.
E 20
E 16
	*/

I 57
D 60
	/* message id */
	h = hrvalue("message-id");
	if (h == NULL)
		syserr("No Message-Id spec");
	else if (bitset(H_DEFAULT, h->h_flags))
	{
		(void) expand(h->h_value, buf, &buf[sizeof buf - 1], CurEnv);
		MsgId = newstr(buf);
	}
	else
		MsgId = h->h_value;
# ifdef DEBUG
	if (tTd(30, 1))
		printf("Message-Id: %s\n", MsgId);
# endif DEBUG
E 60
I 60
D 68
	eatheader();
E 68
I 68
D 91
	eatheader(CurEnv);
E 91
I 91
D 99
	eatheader(e);
E 99
I 99
D 107
	eatheader(e, QueueRun);
E 107
I 107
D 109
	eatheader(e);
E 109
I 109
	eatheader(e, !requeueflag);
E 109
E 107
E 99
E 91
E 68
E 60

I 161
	if (GrabTo && e->e_sendqueue == NULL)
		usrerr("No recipient addresses found in header");

E 161
I 118
	/* collect statistics */
	if (OpMode != MD_VERIFY)
I 143
	{
		extern void markstats();

E 143
		markstats(e, (ADDRESS *) NULL);
I 143
	}
E 143

E 118
E 57
I 47
D 60
	/* message priority */
E 47
I 38
D 41
	/* message priority */
	p = hvalue("priority");
	if (p != NULL)
		MsgPriority = priencode(p);
E 41
I 41
	if (!QueueRun)
	{
		/* adjust total priority by message priority */
D 49
		MsgPriority = MsgSize;
E 49
I 49
		CurEnv->e_msgpriority = CurEnv->e_msgsize;
E 49
		p = hvalue("priority");
		if (p != NULL)
D 49
			MsgPriority -= priencode(p) * WKPRIFACT;
E 49
I 49
D 50
			CurEnv->e_msgpriority -= priencode(p) * WKPRIFACT;
E 50
I 50
			CurEnv->e_class = priencode(p);
		else
			CurEnv->e_class = PRI_NORMAL;
		CurEnv->e_msgpriority -= CurEnv->e_class * WKPRIFACT;
E 50
E 49
	}
E 60
I 60
	/*
	**  Add an Apparently-To: line if we have no recipient lines.
	*/
E 60
E 41

I 47
D 60
	/* special handling */
	p = hvalue("special-handling");
	if (p != NULL)
		spechandling(p);

E 47
E 38
	/* from person */
	xfrom = hvalue("sender");
	if (xfrom == NULL)
D 30
		xfrom = hvalue("from");
E 30
I 30
D 34
		xfrom = hvalue("original-from");
E 34
I 34
D 49
		xfrom = OrigFrom;
E 49
I 49
		xfrom = CurEnv->e_origfrom;
E 49
E 34
E 30
I 27
D 40
	if (ArpaMode != ARPA_NONE)
E 40
I 40
	if (ArpaMode)
E 40
D 31
		setfrom(xfrom, NULL);
E 31
I 31
		setfrom(xfrom, (char *) NULL);
E 31
E 27

I 21
	/* full name of from person */
	p = hvalue("full-name");
	if (p != NULL)
		define('x', p);
I 30
	else
	{
D 45
		register char *q;
E 45
I 45
		extern char *getxpart();
E 45

		/*
		**  Try to extract the full name from a general From:
		**  field.  We take anything which is a comment as a
		**  first choice.  Failing in that, we see if there is
		**  a "machine readable" name (in <angle brackets>); if
		**  so we take anything preceeding that clause.
		**
		**  If we blow it here it's not all that serious.
		*/

		p = hvalue("original-from");
I 34
		if (p == NULL)
D 49
			p = OrigFrom;
E 49
I 49
			p = CurEnv->e_origfrom;
E 49
E 34
D 45
		q = index(p, '(');
		if (q != NULL)
		{
			int parenlev = 0;

			for (p = q; *p != '\0'; p++)
			{
				if (*p == '(')
					parenlev++;
				else if (*p == ')' && --parenlev <= 0)
					break;
			}
			if (*p == ')')
			{
				*p = '\0';
				if (*++q != '\0')
					define('x', newstr(q));
				*p = ')';
			}
		}
		else if ((q = index(p, '<')) != NULL)
		{
			char savec;

			while (*--q == ' ')
				continue;
			while (isspace(*p))
				p++;
			savec = *++q;
			*q = '\0';
			if (*p != '\0')
				define('x', newstr(p));
			*q = savec;
		}
E 45
I 45
		p = getxpart(p);
		if (p != NULL)
			define('x', newstr(p));
E 45
	}
E 30

E 21
	/* date message originated */
D 20
	/* we don't seem to have a good way to do canonical conversion ....
E 20
D 25
	p = hvalue("date");
E 25
I 25
	p = hvalue("posted-date");
	if (p == NULL)
		p = hvalue("date");
E 25
	if (p != NULL)
D 20
		Date = newstr(arpatounix(p));
	.... so we will ignore the problem for the time being */
	if (Date == NULL)
E 20
	{
D 18
		auto long t;
E 18
D 20
		extern char *ctime();

D 18
		time(&t);
		Date = newstr(ctime(&t));
E 18
I 18
		Date = newstr(ctime(&CurTime));
E 20
I 20
		define('a', p);
		/* we don't have a good way to do canonical conversion ....
		define('d', newstr(arpatounix(p)));
		.... so we will ignore the problem for the time being */
E 20
E 18
	}
D 16

	/* message id */
	MsgId = hvalue("message-id");
	if (MsgId == NULL)
		MsgId = makemsgid();
E 16

E 60
I 55
D 91
	if (hvalue("to") == NULL && hvalue("cc") == NULL &&
	    hvalue("bcc") == NULL && hvalue("apparently-to") == NULL)
E 91
I 91
D 133
	if (hvalue("to", e) == NULL && hvalue("cc", e) == NULL &&
	    hvalue("bcc", e) == NULL && hvalue("apparently-to", e) == NULL)
E 133
I 133
	if (hvalue("to", e->e_header) == NULL &&
	    hvalue("cc", e->e_header) == NULL &&
	    hvalue("bcc", e->e_header) == NULL &&
	    hvalue("apparently-to", e->e_header) == NULL)
E 133
E 91
	{
		register ADDRESS *q;
I 145
		char *hdr = NULL;
		extern void addheader();
E 145

		/* create an Apparently-To: field */
		/*    that or reject the message.... */
D 91
		for (q = CurEnv->e_sendqueue; q != NULL; q = q->q_next)
E 91
I 91
D 145
		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
E 145
I 145
		switch (NoRecipientAction)
E 145
E 91
		{
I 143
D 145
			extern void addheader();
E 145
I 145
		  case NRA_ADD_APPARENTLY_TO:
			hdr = "Apparently-To";
			break;
E 145

E 143
I 56
D 145
			if (q->q_alias != NULL)
				continue;
E 56
D 86
# ifdef DEBUG
E 86
D 57
			if (Debug > 1)
E 57
I 57
			if (tTd(30, 3))
E 57
				printf("Adding Apparently-To: %s\n", q->q_paddr);
D 86
# endif DEBUG
E 86
D 91
			addheader("apparently-to", q->q_paddr, CurEnv);
E 91
I 91
D 111
			addheader("apparently-to", q->q_paddr, e);
E 111
I 111
D 133
			addheader("Apparently-To", q->q_paddr, e);
E 133
I 133
			addheader("Apparently-To", q->q_paddr, &e->e_header);
E 145
I 145
		  case NRA_ADD_TO:
			hdr = "To";
			break;

		  case NRA_ADD_BCC:
			addheader("Bcc", "", &e->e_header);
			break;

		  case NRA_ADD_TO_UNDISCLOSED:
			addheader("To", "undisclosed-recipients:;", &e->e_header);
			break;
		}

		if (hdr != NULL)
		{
			for (q = e->e_sendqueue; q != NULL; q = q->q_next)
			{
				if (q->q_alias != NULL)
					continue;
				if (tTd(30, 3))
					printf("Adding %s: %s\n",
						hdr, q->q_paddr);
				addheader(hdr, q->q_paddr, &e->e_header);
			}
E 145
E 133
E 111
E 91
		}
	}

I 110
	/* check for message too large */
	if (MaxMessageSize > 0 && e->e_msgsize > MaxMessageSize)
	{
I 154
		e->e_status = "5.2.3";
E 154
		usrerr("552 Message exceeds maximum fixed size (%ld)",
			MaxMessageSize);
I 159
# ifdef LOG
		if (LogLevel > 6)
			syslog(LOG_NOTICE, "%s: message size (%ld) exceeds maximum (%ld)",
				e->e_id, e->e_msgsize, MaxMessageSize);
# endif
E 159
	}

I 134
	/* check for illegal 8-bit data */
	if (HasEightBits)
	{
		e->e_flags |= EF_HAS8BIT;
D 142
		if (bitset(MM_MIME8BIT, MimeMode))
		{
			/* convert it to MIME */
			if (hvalue("MIME-Version", e->e_header) == NULL)
			{
				char mimebuf[20];

				strcpy(mimebuf, "MIME-Version: 1.0");
				chompheader(mimebuf, FALSE, e);
			}
			if (e->e_bodytype == NULL)
				e->e_bodytype = "8BITMIME";
		}
		else if (!bitset(MM_PASS8BIT, MimeMode))
E 142
I 142
		if (!bitset(MM_PASS8BIT|MM_MIME8BIT, MimeMode))
I 154
		{
			e->e_status = "5.6.1";
E 154
E 142
			usrerr("554 Eight bit data not allowed");
I 154
		}
E 154
	}
I 157
	else
	{
		/* if it claimed to be 8 bits, well, it lied.... */
		if (e->e_bodytype != NULL &&
		    strcasecmp(e->e_bodytype, "8BITMIME") == 0)
			e->e_bodytype = "7BIT";
	}
E 157

E 134
E 110
E 55
I 54
D 68
	/* check for hop count overflow */
	if (HopCount > MAXHOP)
		syserr("Too many hops (%d max); probably forwarding loop", MAXHOP);

E 68
E 54
E 13
D 28
	if (freopen(InFileName, "r", stdin) == NULL)
E 28
I 28
D 52
	if ((TempFile = fopen(InFileName, "r")) == NULL)
E 28
		syserr("Cannot reopen %s", InFileName);
E 52
I 52
D 69
	if ((TempFile = fopen(CurEnv->e_df, "r")) == NULL)
E 69
I 69
D 91
	if ((CurEnv->e_dfp = fopen(CurEnv->e_df, "r")) == NULL)
E 69
		syserr("Cannot reopen %s", CurEnv->e_df);
E 91
I 91
D 148
	if ((e->e_dfp = fopen(e->e_df, "r")) == NULL)
E 148
I 148
	if ((e->e_dfp = fopen(dfname, "r")) == NULL)
E 148
I 106
	{
		/* we haven't acked receipt yet, so just chuck this */
E 106
D 148
		syserr("Cannot reopen %s", e->e_df);
E 148
I 148
		syserr("Cannot reopen %s", dfname);
E 148
I 106
		finis();
	}
E 106
E 91
I 87
}
D 135
/*
**  FLUSHEOL -- if not at EOL, throw away rest of input line.
**
**	Parameters:
**		buf -- last line read in (checked for '\n'),
**		fp -- file to be read from.
**
**	Returns:
**		FALSE on error from sfgets(), TRUE otherwise.
**
**	Side Effects:
**		none.
*/
E 135

D 135
bool
D 131
flusheol(buf, fp)
E 131
I 131
flusheol(buf, fp, dbto)
E 131
	char *buf;
	FILE *fp;
I 131
	time_t dbto;
E 135
I 135

D 143
static
E 143
I 143
static void
E 143
collecttimeout(timeout)
	time_t timeout;
E 135
E 131
{
D 95
	char junkbuf[MAXLINE], *sfgets();
E 95
D 135
	register char *p = buf;
I 95
D 128
	bool printmsg = TRUE;
E 128
	char junkbuf[MAXLINE];
E 135
I 135
	/* if no progress was made, die now */
	if (!CollectProgress)
		longjmp(CtxCollectTimeout, 1);
E 135
D 113
	extern char *sfgets();
E 113
E 95

D 93
	while (index(p, '\n') == NULL) {
E 93
I 93
D 95
	while (strchr(p, '\n') == NULL) {
E 93
		if (sfgets(junkbuf,MAXLINE,fp) == NULL)
			return(FALSE);
E 95
I 95
D 135
	while (strchr(p, '\n') == NULL)
	{
D 128
		if (printmsg)
D 104
			usrerr("header line too long");
E 104
I 104
			usrerr("553 header line too long");
E 104
		printmsg = FALSE;
E 128
I 128
		CollectErrorMessage = "553 header line too long";
		CollectErrno = 0;
E 128
D 98
		if (sfgets(junkbuf, MAXLINE, fp) == NULL)
E 98
I 98
D 102
		if (sfgets(junkbuf, MAXLINE, fp, ReadTimeout) == NULL)
E 102
I 102
D 116
		if (sfgets(junkbuf, MAXLINE, fp, TimeOuts.to_datablock) == NULL)
E 116
I 116
D 131
		if (sfgets(junkbuf, MAXLINE, fp, TimeOuts.to_datablock,
E 131
I 131
		if (sfgets(junkbuf, MAXLINE, fp, dbto,
E 131
				"long line flush") == NULL)
E 116
E 102
E 98
			return (FALSE);
E 95
		p = junkbuf;
	}

D 95
	return(TRUE);
E 95
I 95
	return (TRUE);
E 135
I 135
	/* otherwise reset the timeout */
	CollectTimeout = setevent(timeout, collecttimeout, timeout);
	CollectProgress = FALSE;
E 135
E 95
E 87
I 72
}
/*
**  TFERROR -- signal error on writing the temporary file.
**
**	Parameters:
**		tf -- the file pointer for the temporary file.
I 149
**		e -- the current envelope.
E 149
**
**	Returns:
**		none.
**
**	Side Effects:
**		Gives an error message.
**		Arranges for following output to go elsewhere.
*/

I 143
void
E 143
D 91
tferror(tf)
E 91
I 91
tferror(tf, e)
E 91
	FILE *tf;
I 91
	register ENVELOPE *e;
E 91
{
I 128
D 149
	CollectErrno = errno;
E 149
E 128
	if (errno == ENOSPC)
	{
I 127
		struct stat st;
		long avail;
		long bsize;

D 132
		NoReturn = TRUE;
E 132
I 132
D 146
		e->e_flags |= EF_NORETURN;
E 146
I 146
		e->e_flags |= EF_NO_BODY_RETN;
E 146
E 132
		if (fstat(fileno(tf), &st) < 0)
			st.st_size = 0;
E 127
D 91
		(void) freopen(CurEnv->e_df, "w", tf);
E 91
I 91
D 148
		(void) freopen(e->e_df, "w", tf);
E 148
I 148
		(void) freopen(queuename(e, 'd'), "w", tf);
E 148
E 91
D 127
		fputs("\nMAIL DELETED BECAUSE OF LACK OF DISK SPACE\n\n", tf);
E 127
I 127
		if (st.st_size <= 0)
			fprintf(tf, "\n*** Mail could not be accepted");
		else if (sizeof st.st_size > sizeof (long))
			fprintf(tf, "\n*** Mail of at least %qd bytes could not be accepted\n",
				st.st_size);
		else
			fprintf(tf, "\n*** Mail of at least %ld bytes could not be accepted\n",
				st.st_size);
		fprintf(tf, "*** at %s due to lack of disk space for temp file.\n",
			MyHostName);
D 160
		avail = freespace(QueueDir, &bsize);
E 160
I 160
		avail = freediskspace(QueueDir, &bsize);
E 160
		if (avail > 0)
		{
			if (bsize > 1024)
				avail *= bsize / 1024;
			else if (bsize < 1024)
				avail /= 1024 / bsize;
			fprintf(tf, "*** Currently, %ld kilobytes are available for mail temp files.\n",
				avail);
		}
I 154
		e->e_status = "4.3.1";
E 154
E 127
D 128
		usrerr("452 Out of disk space for temp file");
E 128
I 128
D 149
		CollectErrorMessage = "452 Out of disk space for temp file";
E 149
I 149
		usrerr("452 Out of disk space for temp file");
E 149
E 128
	}
	else
D 91
		syserr("collect: Cannot write %s", CurEnv->e_df);
E 91
I 91
D 128
		syserr("collect: Cannot write %s", e->e_df);
E 128
I 128
D 149
	{
		CollectErrorMessage = "cannot write message body to disk (%s)";
	}
E 149
I 149
		syserr("collect: Cannot write tf%s", e->e_id);
E 149
E 128
E 91
	(void) freopen("/dev/null", "w", tf);
E 72
E 52
D 13
	return (ArpaFmt && fbuf[0] != '\0' ? fbuf : NULL);
E 13
I 13
D 71

D 60
# ifdef DEBUG
D 57
	if (Debug)
E 57
I 57
	if (tTd(30, 2))
E 57
	{
I 31
		HDR *h;
		extern char *capitalize();

E 31
		printf("----- collected header -----\n");
D 49
		for (h = Header; h != NULL; h = h->h_link)
E 49
I 49
		for (h = CurEnv->e_header; h != NULL; h = h->h_link)
E 49
			printf("%s: %s\n", capitalize(h->h_field), h->h_value);
		printf("----------------------------\n");
	}
# endif DEBUG
I 57

E 60
	/*
	**  Log collection information.
	*/

# ifdef LOG
	if (LogLevel > 1)
D 62
		syslog(LOG_INFO, "%s: from=%s, size=%ld, class=%d\n", MsgId,
		       CurEnv->e_from.q_paddr, CurEnv->e_msgsize,
E 62
I 62
		syslog(LOG_INFO, "%s: from=%s, size=%ld, class=%d\n",
		       CurEnv->e_id, CurEnv->e_from.q_paddr, CurEnv->e_msgsize,
E 62
D 59
		       CurEnv->e_msgpriority);
E 59
I 59
		       CurEnv->e_class);
E 59
# endif LOG
E 57
D 27
	return (ArpaFmt ? xfrom : NULL);
E 27
I 27
	return;
E 71
E 27
E 13
}
/*
I 13
**  EATFROM -- chew up a UNIX style from line and process
**
**	This does indeed make some assumptions about the format
**	of UNIX messages.
**
**	Parameters:
**		fm -- the from line.
**
**	Returns:
**		none.
**
**	Side Effects:
**		extracts what information it can from the header,
D 20
**		such as the Date.
E 20
I 20
**		such as the date.
E 20
*/

I 32
# ifndef NOTUNIX

E 32
I 29
char	*DowList[] =
{
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", NULL
};

E 29
char	*MonthList[] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
	NULL
};

I 143
void
E 143
D 91
eatfrom(fm)
E 91
I 91
eatfrom(fm, e)
E 91
	char *fm;
I 91
	register ENVELOPE *e;
E 91
{
	register char *p;
	register char **dt;

I 29
D 86
# ifdef DEBUG
E 86
D 57
	if (Debug > 1)
E 57
I 57
	if (tTd(30, 2))
E 57
		printf("eatfrom(%s)\n", fm);
D 86
# endif DEBUG
E 86

E 29
	/* find the date part */
	p = fm;
	while (*p != '\0')
	{
		/* skip a word */
		while (*p != '\0' && *p != ' ')
D 78
			*p++;
E 78
I 78
			p++;
E 78
		while (*p == ' ')
D 78
			*p++;
E 78
I 78
			p++;
E 78
D 100
		if (!isupper(*p) || p[3] != ' ' || p[13] != ':' || p[16] != ':')
E 100
I 100
		if (!(isascii(*p) && isupper(*p)) ||
		    p[3] != ' ' || p[13] != ':' || p[16] != ':')
E 100
			continue;

		/* we have a possible date */
D 29
		for (dt = MonthList; *dt != NULL; dt++)
E 29
I 29
		for (dt = DowList; *dt != NULL; dt++)
E 29
			if (strncmp(*dt, p, 3) == 0)
				break;
I 29
		if (*dt == NULL)
			continue;
E 29

I 29
		for (dt = MonthList; *dt != NULL; dt++)
			if (strncmp(*dt, &p[4], 3) == 0)
				break;
E 29
		if (*dt != NULL)
			break;
	}

D 114
	if (*p != NULL)
E 114
I 114
	if (*p != '\0')
E 114
	{
I 20
		char *q;
I 44
		extern char *arpadate();
E 44

E 20
		/* we have found a date */
D 20
		Date = xalloc(25);
		strncpy(Date, p, 25);
		Date[24] = '\0';
E 20
I 20
		q = xalloc(25);
D 81
		strncpy(q, p, 25);
E 81
I 81
		(void) strncpy(q, p, 25);
E 81
		q[24] = '\0';
D 68
		define('d', q);
E 68
I 68
D 91
		define('d', q, CurEnv);
E 91
I 91
D 103
		define('d', q, e);
E 103
E 91
E 68
I 44
		q = arpadate(q);
D 68
		define('a', newstr(q));
E 68
I 68
D 91
		define('a', newstr(q), CurEnv);
E 91
I 91
		define('a', newstr(q), e);
E 91
E 68
E 44
E 20
	}
}
I 32

D 93
# endif NOTUNIX
E 93
I 93
# endif /* NOTUNIX */
E 93
I 38
D 60
/*
**  PRIENCODE -- encode external priority names into internal values.
**
**	Parameters:
**		p -- priority in ascii.
**
**	Returns:
**		priority as a numeric level.
**
**	Side Effects:
**		none.
*/

struct prio
{
	char	*pri_name;	/* external name of priority */
	int	pri_val;	/* internal value for same */
};

static struct prio	Prio[] =
{
D 39
	"normal",		PRI_NORMAL,
E 39
I 39
	"alert",		PRI_ALERT,
E 39
	"quick",		PRI_QUICK,
D 39
	"priority",		PRI_PRIORITY,
	"first-class",		PRI_NORMAL,
E 39
I 39
	"first-class",		PRI_FIRSTCL,
	"normal",		PRI_NORMAL,
E 39
	"second-class",		PRI_SECONDCL,
	"third-class",		PRI_THIRDCL,
I 50
	"junk",			PRI_JUNK,
E 50
	NULL,			PRI_NORMAL,
};

priencode(p)
	char *p;
{
	register struct prio *pl;
I 39
	extern bool sameword();
E 39

	for (pl = Prio; pl->pri_name != NULL; pl++)
	{
D 39
		if (strcmp(p, pl->pri_name) == 0)
E 39
I 39
		if (sameword(p, pl->pri_name))
E 39
			break;
	}
	return (pl->pri_val);
I 47
}
/*
**  SPECHANDLE -- do special handling
**
**	Parameters:
**		p -- pointer to list of special handling words.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets flags as indicated by p.
*/

struct handling
{
	char	*han_name;		/* word to get this magic */
	int	han_what;		/* what to do, see below */
};

/* modes for han_what */
# define	HAN_NONE	0	/* nothing special */
# define	HAN_RRECEIPT	1	/* give return receipt */

struct handling	Handling[] =
{
	"return-receipt-requested",	HAN_RRECEIPT,
	NULL,				HAN_NONE
};

spechandling(p)
	register char *p;
{
	register char *w;
	register struct handling *h;
	extern bool sameword();

	while (*p != '\0')
	{
		/* collect a word to compare to */
		while (*p != '\0' && (*p == ',' || isspace(*p)))
			p++;
		if (*p == '\0')
			break;
		w = p;
		while (*p != '\0' && *p != ',' && !isspace(*p))
			p++;
		if (*p != '\0')
			*p++ = '\0';

		/* scan the special handling table */
		for (h = Handling; h->han_name != NULL; h++)
			if (sameword(h->han_name, w))
				break;

		/* see if we can do anything interesting */
		switch (h->han_what)
		{
		  case HAN_NONE:	/* nothing to be done */
			break;

		  case HAN_RRECEIPT:	/* give return receipt */
D 49
			RetReceipt = TRUE;
E 49
I 49
			CurEnv->e_retreceipt = TRUE;
E 49
# ifdef DEBUG
D 57
			if (Debug > 2)
E 57
I 57
			if (tTd(30, 3))
E 57
				printf(">>> Return receipt requested\n");
# endif DEBUG
			break;

		  default:
			syserr("spechandling: handling %d (%s)", h->han_what, w);
		}
	}
E 47
}
E 60
E 38
E 32
D 24
/*
**  HVALUE -- return value of a header.
**
I 20
**	Only "real" fields (i.e., ones that have not been supplied
**	as a default) are used.
**
E 20
**	Parameters:
**		field -- the field name.
**
**	Returns:
**		pointer to the value part.
**		NULL if not found.
**
**	Side Effects:
**		sets the H_USED bit in the header if found.
*/

char *
hvalue(field)
	char *field;
{
	register HDR *h;

	for (h = Header; h != NULL; h = h->h_link)
	{
D 20
		if (strcmp(h->h_field, field) == 0)
E 20
I 20
		if (!bitset(H_DEFAULT, h->h_flags) && strcmp(h->h_field, field) == 0)
E 20
		{
			h->h_flags |= H_USED;
			return (h->h_value);
		}
	}
	return (NULL);
}
/*
E 13
D 20
**  MAKEMSGID -- Compute a message id for this process.
**
**	This routine creates a message id for a message if
**	it did not have one already.  If the MESSAGEID compile
**	flag is set, the messageid will be added to any message
**	that does not already have one.  Currently it is more
**	of an artifact, but I suggest that if you are hacking,
**	you leave it in -- I may want to use it someday if
**	duplicate messages turn out to be a problem.
**
**	Parameters:
**		none.
**
**	Returns:
D 13
**		none.
E 13
I 13
**		a message id.
E 13
**
**	Side Effects:
D 13
**		Stores a message-id into MsgId.
**
**	Called By:
**		maketemp
E 13
I 13
**		none.
E 13
*/

I 13
char *
E 13
makemsgid()
{
D 18
	auto long t;
D 17
	extern char *MyLocName;
	extern char *ArpaHost;
E 17
I 17
	register char *p;
	extern char *Macro[];
E 18
E 17
I 13
	static char buf[50];
I 15
D 18
	extern long time();
	extern char *sprintf();
E 18
I 18
	extern char *expand();
E 18
E 15
E 13

D 18
	time(&t);
D 13
	sprintf(MsgId, "%ld.%d.%s@%s", t, getpid(), MyLocName, ArpaHost);
E 13
I 13
D 17
	sprintf(buf, "<%ld.%d.%s@%s>", t, getpid(), MyLocName, ArpaHost);
E 17
I 17
	sprintf(buf, "<%ld.%d", t, getpid());
	p = Macro['l'];
	if (p != NULL)
	{
		strcat(buf, ".");
		strcat(buf, p);
	}
	p = Macro['A'];
	if (p != NULL)
	{
		strcat(buf, "@");
		strcat(buf, p);
	}
	strcat(buf, ">");

E 18
I 18
	expand("<$m>", buf, &buf[sizeof buf - 1]);
E 18
E 17
	return (buf);
}
/*
E 20
**  ISHEADER -- predicate telling if argument is a header.
**
**	Parameters:
**		s -- string to check for possible headerness.
**
**	Returns:
**		TRUE if s is a header.
**		FALSE otherwise.
**
**	Side Effects:
**		none.
*/

bool
isheader(s)
	register char *s;
{
	if (!isalnum(*s))
		return (FALSE);
	while (!isspace(*s) && *s != ':')
		s++;
	while (isspace(*s))
		s++;
	return (*s == ':');
I 20
}
/*
**  CHOMPHEADER -- process and save a header line.
**
**	Called by collect and by readcf to deal with header lines.
**
**	Parameters:
**		line -- header as a text line.
D 22
**		stat -- bits to set in the h_flags field.
E 22
I 22
**		def -- if set, this is a default value.
E 22
**
**	Returns:
**		flags for this header.
**
**	Side Effects:
**		The header is saved on the header list.
*/

D 22
chompheader(line, stat)
E 22
I 22
chompheader(line, def)
E 22
	char *line;
D 22
	int stat;
E 22
I 22
	bool def;
E 22
{
	register char *p;
D 23
	extern int errno;
E 23
	register HDR *h;
	HDR **hp;
	extern bool isheader();
D 23
	extern char *newstr();
	extern char *xalloc();
E 23
	char *fname;
	char *fvalue;
D 23
	extern char *index(), *rindex();
E 23
	struct hdrinfo *hi;
D 23
	extern char *strcpy(), *strcat(), *mktemp();
E 23

	/* strip off trailing newline */
	p = rindex(line, '\n');
	if (p != NULL)
		*p = '\0';

	/* find canonical name */
	fname = line;
	p = index(line, ':');
	fvalue = &p[1];
	while (isspace(*--p))
		continue;
	*++p = '\0';
	makelower(fname);

	/* strip field value on front */
	if (*fvalue == ' ')
		fvalue++;

	/* search header list for this header */
	for (hp = &Header, h = Header; h != NULL; hp = &h->h_link, h = h->h_link)
	{
		if (strcmp(fname, h->h_field) == 0 && bitset(H_DEFAULT, h->h_flags))
			break;
	}

	/* see if it is a known type */
	for (hi = HdrInfo; hi->hi_field != NULL; hi++)
	{
		if (strcmp(hi->hi_field, fname) == 0)
			break;
	}

	/* if this means "end of header" quit now */
	if (bitset(H_EOH, hi->hi_flags))
		return (hi->hi_flags);

	/* create/fill in a new node */
	if (h == NULL)
	{
		/* create a new node */
		*hp = h = (HDR *) xalloc(sizeof *h);
		h->h_field = newstr(fname);
		h->h_value = NULL;
		h->h_link = NULL;
D 22
		h->h_flags = hi->hi_flags | stat;
E 22
I 22
		h->h_flags = hi->hi_flags;
E 22
		h->h_mflags = hi->hi_mflags;
	}
I 22
	if (def)
		h->h_flags |= H_DEFAULT;
E 22
	else
D 22
		h->h_flags &= ~H_DEFAULT;
E 22
I 22
		h->h_flags &= ~H_CHECK;
E 22
	if (h->h_value != NULL)
		free(h->h_value);
	h->h_value = newstr(fvalue);

	return (h->h_flags);
E 20
E 13
I 9
}
/*
**  SAVEDATE -- find and save date field from a "From" line
**
**	This will be used by putheader when a From line is created.
**
**	Parameters:
**		buf -- a "From" line.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Saves the "date" part (with newline) in SentDate.
*/

char	SentDate[30];

savedate(buf)
	char *buf;
{
	register char *p;

	for (p = buf; p != '\0'; p++)
	{
		if (*p != ' ')
			continue;
		if (strncmp(p, " Sun ", 5) == 0 ||
		    strncmp(p, " Mon ", 5) == 0 ||
		    strncmp(p, " Tue ", 5) == 0 ||
		    strncmp(p, " Wed ", 5) == 0 ||
		    strncmp(p, " Thu ", 5) == 0 ||
		    strncmp(p, " Fri ", 5) == 0 ||
		    strncmp(p, " Sat ", 5) == 0)
		{
			if (p[4] != ' ' || p[8] != ' ' || p[11] != ' ' ||
			    p[14] != ':' || p[17] != ':' || p[20] != ' ')
				continue;
			strncpy(SentDate, ++p, 25);
			SentDate[24] = '\n';
			SentDate[25] = '\0';
			return;
		}
	}
E 9
}
E 24
E 2
I 1
E 1
