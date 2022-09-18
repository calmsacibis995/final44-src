h59697
s 00015/00003/01342
d D 8.79 95/06/18 12:38:24 eric 219 218
c improvements for message savings algorithms from Motonori Nakamura
e
s 00013/00000/01332
d D 8.78 95/06/17 10:36:19 eric 218 217
c message/rfc822 MIME fixes
e
s 00009/00000/01323
d D 8.77 95/06/16 10:27:12 eric 217 216
c insert Content-Transfer-Encoding: 8bit on top level of returned
c messages if necessary
e
s 00001/00001/01322
d D 8.76 95/06/15 14:04:05 eric 216 215
c fix bogus entry in DSN if forwarded to a $#error mailer
e
s 00001/00001/01322
d D 8.75 95/06/14 07:04:20 eric 215 214
c update for new DSN draft
e
s 00093/00015/01230
d D 8.74 95/06/11 06:47:04 eric 214 213
c updates for new DSN drafts
e
s 00016/00012/01229
d D 8.73 95/05/31 08:01:36 eric 213 212
c better handling of dead.letter -- involves mailfile changes
e
s 00000/00005/01241
d D 8.72 95/05/29 15:57:12 eric 212 211
c force -oee to really always return zero
e
s 00006/00002/01240
d D 8.71 95/05/28 11:49:42 eric 211 210
c lint
e
s 00002/00002/01240
d D 8.70 95/05/18 13:09:38 eric 210 209
c clean up version numbers on DSN drafts
e
s 00002/00002/01240
d D 8.69 95/04/24 20:38:57 eric 209 208
c lint
e
s 00061/00044/01181
d D 8.68 95/04/23 14:02:58 eric 208 207
c updates for new DSN drafts
e
s 00004/00003/01221
d D 8.67 95/04/22 15:58:55 eric 207 206
c updates for new status system codes and Multipart/Report drafts
e
s 00003/00000/01221
d D 8.66 95/04/22 14:50:51 eric 206 205
c better use of extended DSN status codes
e
s 00002/00002/01219
d D 8.65 95/04/22 11:06:10 eric 205 204
c default DSNs on
e
s 00001/00001/01220
d D 8.64 95/04/21 09:57:18 eric 204 203
c update copyright notice
e
s 00037/00039/01184
d D 8.63 95/04/13 17:36:11 eric 203 202
c fix postmaster notifications -- it was getting the body in
c some inappropriate cases, and sometimes no message at all; clean up
c dead.letter processing
e
s 00001/00003/01222
d D 8.62 95/03/31 10:52:00 eric 202 201
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00001/00001/01224
d D 8.61 95/03/27 11:43:24 eric 201 200
c make DSN info match draft numbers
e
s 00050/00021/01175
d D 8.60 95/03/27 09:25:36 eric 200 199
c more cleanup for DSN drafts
e
s 00047/00005/01149
d D 8.59 95/03/22 18:09:23 eric 199 198
c more updates for DSN
e
s 00001/00001/01153
d D 8.58 95/03/21 15:28:29 eric 198 197
c eliminate `D' line in qf file
e
s 00007/00009/01147
d D 8.57 95/03/21 09:26:48 eric 197 196
c new DSN draft
e
s 00006/00006/01150
d D 8.56 95/03/14 09:10:59 eric 196 195
c change call to expand() to be more rational (and consistent!)
e
s 00001/00001/01155
d D 8.55 95/03/14 08:18:57 eric 195 194
c be more precise on MAXNAME checking
e
s 00001/00001/01155
d D 8.54 95/03/10 12:21:55 eric 194 193
c improved security when opening files
e
s 00003/00002/01153
d D 8.53 95/03/06 15:11:54 eric 193 192
c fix some race conditions for file opens
e
s 00007/00000/01148
d D 8.52 95/03/05 14:34:00 eric 192 191
c changes suggested by *Hobbit*; SafeFileEnvironment option
e
s 00213/00127/00935
d D 8.51 95/02/05 08:03:53 eric 191 190
c cut at 20 January version of DSN document
e
s 00012/00003/01050
d D 8.50 95/01/07 08:43:38 eric 190 189
c avoid bogus dups
e
s 00002/00002/01051
d D 8.49 94/12/12 09:10:27 eric 189 188
c use X-delivery-status-1 as the report-type and content-type for now
e
s 00006/00000/01047
d D 8.48 94/12/03 08:29:20 eric 188 187
c put DSNs on a compile flag
e
s 00018/00013/01029
d D 8.47 94/11/28 09:16:47 eric 187 186
c more DSN tweaking
e
s 00027/00016/01015
d D 8.46 94/11/27 15:22:28 eric 186 185
c more DSN hacking
e
s 00009/00002/01022
d D 8.45 94/11/27 11:22:39 eric 185 184
c get the final MTS type from the mailer descriptor
e
s 00037/00009/00987
d D 8.44 94/11/25 09:06:07 eric 184 183
c improve DSN handling somewhat + some bug fixes
e
s 00006/00001/00990
d D 8.43 94/11/23 15:21:10 eric 183 182
c get ORCPT= ESMTP DSN parameter working
e
s 00004/00004/00987
d D 8.42 94/11/22 22:24:56 eric 182 181
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00010/00007/00981
d D 8.41 94/11/22 17:47:23 eric 181 180
c cleanup for return-receipts
e
s 00033/00004/00955
d D 8.40 94/11/21 21:07:37 eric 180 179
c convert to new DSN draft
e
s 00001/00001/00958
d D 8.39 94/11/20 08:56:43 eric 179 178
c check for "<<>>" etc as equivalent to "<>"
e
s 00002/00002/00957
d D 8.38 94/11/19 17:13:09 eric 178 177
c change PF_NOBODYPART to be more descriptive of what the flag
c actually does
e
s 00009/00005/00950
d D 8.37 94/11/19 16:57:33 eric 177 176
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00136/00010/00819
d D 8.36 94/11/04 08:40:28 eric 176 175
c first cut at DSN implementation
e
s 00001/00001/00828
d D 8.35 94/10/15 08:29:15 eric 175 174
c if the close of /usr/tmp/dead.letter fails, give a correct error message
e
s 00001/00001/00828
d D 8.34 94/08/15 10:14:24 eric 174 173
c don't send error file with return receipts
e
s 00020/00012/00809
d D 8.33 94/07/23 07:59:33 eric 173 172
c MIME 8 to 7 bit support
e
s 00004/00004/00817
d D 8.32 94/07/03 11:48:19 eric 172 171
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00008/00002/00813
d D 8.31 94/06/19 06:45:05 eric 171 170
c tag return messages with a Precedence: line for easy identification
e
s 00010/00002/00805
d D 8.30 94/05/29 07:31:18 eric 170 169
c clean up Subject: line on warning messages
e
s 00001/00001/00806
d D 8.29 94/05/10 07:09:39 eric 169 168
c avoid core dump from buffer overrun for very long messages
e
s 00001/00001/00806
d D 8.28 94/03/11 14:41:51 eric 168 167
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00003/00002/00804
d D 8.27 94/03/06 09:00:58 eric 167 166
c debugging: print exit status on entry to savemail
e
s 00002/00002/00804
d D 8.26 94/03/04 07:51:33 eric 166 165
c wrong send queue was being passed to returntosender()
e
s 00056/00051/00750
d D 8.25 94/01/24 08:01:36 eric 165 164
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00006/00001/00795
d D 8.24 93/12/18 06:25:04 eric 164 163
c put location of dead.letter on a compile flag
e
s 00001/00001/00795
d D 8.23 93/12/13 07:35:44 eric 163 162
c patches to fix checks when sending to a file
e
s 00001/00001/00795
d D 8.22 93/12/10 16:40:13 eric 162 161
c cleanup of symbolic link checking -- make it less picky
e
s 00002/00001/00794
d D 8.21 93/12/10 12:41:56 eric 161 159
c avoid sending WARNING message on return-receipts
e
s 00007/00003/00792
d D 8.20.1.1 93/12/02 18:31:33 eric 160 159
c try to clean up warning messages
e
s 00001/00002/00794
d D 8.20 93/11/26 18:43:58 eric 159 158
c make the panic state more panicy
e
s 00008/00002/00788
d D 8.19 93/11/25 11:41:12 eric 158 157
c avoid symbolic link attacks
e
s 00001/00000/00789
d D 8.18 93/11/25 09:35:48 eric 157 156
c delete $u in parent envelope to avoid bogus info in Received: lines
e
s 00004/00001/00785
d D 8.17 93/10/31 10:18:12 eric 156 155
c fix test for null error queue
e
s 00001/00001/00785
d D 8.16 93/10/21 12:24:48 eric 155 154
c fix problem causing dates to not always get reset on returned mail
e
s 00001/00003/00785
d D 8.15 93/10/17 12:00:33 eric 154 153
c fix handling of pre-parsing address errors
e
s 00017/00001/00771
d D 8.14 93/10/15 08:34:41 eric 153 152
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00003/00001/00769
d D 8.13 93/09/26 09:15:17 eric 152 151
c compute return message size more cleverly if NoReturn is set
e
s 00003/00001/00767
d D 8.12 93/08/25 19:45:13 eric 151 150
c do more careful checking for address failure
e
s 00001/00001/00767
d D 8.11 93/08/18 19:45:56 eric 150 149
c fix problem that causes core dumps on config files that don't
c understand filename syntax
e
s 00007/00008/00761
d D 8.10 93/08/17 09:51:57 eric 149 148
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00001/00001/00768
d D 8.9 93/08/06 21:16:57 eric 148 147
c fix problem causing slow delivery warning to fail if OP set
e
s 00001/00001/00768
d D 8.8 93/07/23 14:51:44 eric 147 146
c tag returned message with true original from (not localhost)
e
s 00001/00001/00768
d D 8.7 93/07/19 20:50:10 eric 146 145
c SGI IRIX & ANSI C portability
e
s 00011/00001/00758
d D 8.6 93/07/17 14:35:25 eric 145 144
c more information to help identify the error cause
e
s 00011/00016/00748
d D 8.5 93/07/17 13:49:22 eric 144 143
c better error message handling: don't create bogus return messages;
c print both actual address and q_alias whereever possible
e
s 00024/00001/00740
d D 8.4 93/07/16 10:30:21 eric 143 142
c deliver local problems (EX_CONFIG and EX_SOFTWARE) to local postmaster
e
s 00009/00004/00732
d D 8.3 93/07/13 12:58:30 eric 142 141
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00003/00000/00733
d D 8.2 93/07/11 06:52:38 eric 141 140
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00731
d D 8.1 93/06/07 10:31:58 bostic 140 139
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00733
d D 6.44 93/05/27 11:37:29 eric 139 138
c prototype functions
e
s 00010/00007/00724
d D 6.43 93/05/14 13:52:48 eric 138 137
c MIME cleanups
e
s 00003/00002/00728
d D 6.42 93/05/13 09:32:33 eric 137 136
c fix To: lists in error messages
e
s 00006/00004/00724
d D 6.41 93/05/13 09:28:41 eric 136 135
c a bunch of nits in the MIME code
e
s 00002/00001/00726
d D 6.40 93/05/05 08:11:24 eric 135 134
c create dead.letter with FileMode instead of 0666
e
s 00050/00020/00677
d D 6.39 93/05/04 15:45:05 eric 134 133
c update for MIME encapsulated error messages
e
s 00002/00002/00695
d D 6.38 93/04/30 12:54:21 eric 133 132
c don't change alpha case on header field names
e
s 00002/00002/00695
d D 6.37 93/04/27 18:48:48 eric 132 131
c don't ignore postmaster alias for emergency fallback
e
s 00001/00002/00696
d D 6.36 93/04/26 16:15:39 eric 131 130
c fix an uninitialized variable problem
e
s 00001/00001/00697
d D 6.35 93/04/26 13:13:57 eric 130 129
c have getmxrr look at $=w to determine local host name
e
s 00004/00001/00694
d D 6.34 93/04/17 10:34:55 eric 129 128
c improve error printing (changes format of C line in qf)
e
s 00008/00001/00687
d D 6.33 93/04/15 19:03:39 eric 128 127
c fixes to handle null messages -- why did this break?
e
s 00012/00002/00676
d D 6.32 93/04/15 08:27:08 eric 127 126
c discard errors only on responses to responses to responses, not
c responses to responses.
e
s 00028/00004/00650
d D 6.31 93/04/14 13:14:50 eric 126 125
c print a list of the bad addresses on returned email
e
s 00005/00001/00649
d D 6.30 93/04/13 08:43:41 eric 125 124
c redefine $r, $s, and $_ in error envelopes; properly handle
c parseaddr return in ESM_POSTMASTER case
e
s 00005/00004/00645
d D 6.29 93/04/05 08:22:01 eric 124 123
c clean up error return messages
e
s 00001/00001/00648
d D 6.28 93/04/01 14:59:20 eric 123 122
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00001/00001/00648
d D 6.27 93/03/30 10:04:20 eric 122 121
c avoid bogus diagnostic
e
s 00001/00001/00648
d D 6.26 93/03/19 11:46:36 eric 121 120
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00003/00003/00646
d D 6.25 93/03/19 08:50:52 eric 120 119
c move SendMode and ErrorMode into the envelope
e
s 00002/00002/00647
d D 6.24 93/03/19 08:30:56 eric 119 118
c default fallback name is Postmaster, not root
e
s 00003/00001/00646
d D 6.23 93/03/18 10:56:24 eric 118 117
c restore e_sender as sending address sans decorations
e
s 00065/00058/00582
d D 6.22 93/03/16 09:16:15 eric 117 116
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00000/00001/00640
d D 6.21 93/03/14 07:36:38 eric 116 115
c change (simplify) user and host UPPER => lower case mapping
e
s 00002/00002/00639
d D 6.20 93/03/13 22:51:22 eric 115 114
c always return message header, even if NoReturn set
e
s 00007/00000/00634
d D 6.19 93/03/08 18:03:02 eric 114 113
c count recipients and estimate size of return messages
e
s 00004/00004/00630
d D 6.18 93/03/01 12:43:55 eric 113 112
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00000/00001/00634
d D 6.17 93/03/01 06:53:35 eric 112 111
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00007/00001/00628
d D 6.16 93/02/28 09:44:58 eric 111 110
c deliver postmaster copies without a body
e
s 00009/00012/00620
d D 6.15 93/02/28 09:23:40 eric 110 109
c send to return return path even if e_errorqueue already has entries
e
s 00006/00006/00626
d D 6.14 93/02/27 12:00:22 eric 109 108
c fix from Eric Wassenaar for return message suppression
e
s 00003/00003/00629
d D 6.13 93/02/24 10:19:30 eric 108 107
c fix yet another problem with new owner-foo implementation
e
s 00013/00003/00619
d D 6.12 93/02/24 09:52:46 eric 107 106
c fix owner-foo for errors that do occur locallyi
e
s 00009/00009/00613
d D 6.11 93/02/23 06:31:43 eric 106 105
c overhaul status of SMTP reply codes
e
s 00062/00000/00560
d D 6.10 93/02/22 16:59:53 eric 105 104
c add route pruning
e
s 00004/00001/00556
d D 6.9 93/02/21 12:44:26 eric 104 103
c insist on level 4 config file to send errors from <>
e
s 00010/00002/00547
d D 6.8 93/02/21 09:55:22 eric 103 102
c send errors with return path = <>; don't respond to such messages
e
s 00007/00007/00542
d D 6.7 93/02/20 13:46:40 eric 102 101
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00007/00007/00542
d D 6.6 93/02/18 20:22:28 eric 101 100
c move the meta-characters from C0 into C1 space
e
s 00001/00001/00548
d D 6.5 93/02/16 18:30:00 eric 100 99
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00006/00006/00543
d D 6.4 93/02/15 16:44:54 eric 99 98
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00007/00001/00542
d D 6.3 93/01/21 15:18:43 eric 98 97
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00008/00012/00535
d D 6.2 93/01/09 14:45:37 eric 97 96
c tuning of queueing functions as recommended by John Gardiner Myers
c <jgm+@CMU.EDU>; return mail headers (no body) on messages with negative
c precedence; minor other bug fixes
e
s 00000/00000/00547
d D 6.1 92/12/21 16:08:38 eric 96 95
c Release 6
e
s 00001/00001/00546
d D 5.21 92/11/14 11:34:22 eric 95 94
c (partially) ANSI-fy it
e
s 00005/00001/00542
d D 5.20 92/07/20 10:22:55 eric 94 93
c macro expand error messages
e
s 00024/00000/00519
d D 5.19 92/07/19 14:26:06 eric 93 92
c finish uid_t/gid_t conversion; allow locally customized message for
c prepending to all error returns
e
s 00016/00014/00503
d D 5.18 92/07/12 14:09:46 eric 92 91
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00516
d D 5.17 92/07/11 18:51:41 eric 91 90
c open connection caching
e
s 00001/00000/00516
d D 5.16 92/04/16 18:39:49 eric 90 89
c properly set up envelope when returning email
e
s 00001/00000/00515
d D 5.15 91/12/15 13:59:42 eric 89 88
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00002/00000/00513
d D 5.14 90/08/29 14:39:51 eric 88 87
c from Eric Wassenaar at NIKHEF-H, Amsterdam: reset EF_OLDSTYLE bit when
c returning mail
e
s 00001/00011/00512
d D 5.13 90/06/01 19:03:40 bostic 87 86
c new copyright notice
e
s 00001/00000/00522
d D 5.12 89/02/27 09:16:50 bostic 86 85
c add types.h for pwd.h
e
s 00000/00006/00522
d D 5.11 89/01/01 17:17:50 bostic 85 84
c remove DEBUG
e
s 00000/00002/00528
d D 5.10 88/11/17 22:02:33 karels 84 83
c more cleanup, fix some inappropriate syserr's
e
s 00011/00009/00519
d D 5.9 88/06/30 14:59:38 bostic 83 82
c install approved copyright notice
e
s 00016/00010/00512
d D 5.8 88/03/13 19:53:02 bostic 82 81
c add Berkeley specific header
e
s 00005/00000/00517
d D 5.7 85/12/07 08:17:41 eric 81 80
m 
c several small bugs: don't die if no environment, don't look in
c ESM_DEADLETTER state in savemail; lowercase before getpwnam to
c allow upper case regular names in alias file
e
s 00006/00000/00511
d D 5.6 85/09/21 14:44:27 eric 80 79
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00019/00001/00492
d D 5.5 85/09/21 10:31:23 eric 79 78
m 
c add -v mode to mailq to print priorities as well (this should be extended
c in the future); fix some problems in the savemail state machine.
e
s 00001/00001/00492
d D 5.4 85/09/19 13:35:53 eric 78 77
m 
c lint
e
s 00194/00093/00299
d D 5.3 85/09/19 00:45:30 eric 77 76
m 
c SMI changes (somewhat)
e
s 00000/00002/00392
d D 5.2 85/06/07 22:23:55 miriam 76 75
m 
c Resolve duplicate SccsId
e
s 00014/00000/00380
d D 5.1 85/06/07 15:13:01 dist 75 74
m 
c Add copyright
e
s 00000/00000/00380
d D 4.6 85/05/24 11:00:14 eric 74 73
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00007/00007/00373
d D 4.5 84/05/13 14:02:48 eric 73 72
m 
c change "returnto" to "returnq" for PDP-11 compilers
e
s 00001/00000/00379
d D 4.4 84/03/11 19:57:54 eric 72 71
m 
c disable UPPER->lower case mapping in RHS's of aliases so that upper
c case letters can be used in file names and as args to programs.
e
s 00005/00005/00374
d D 4.3 84/03/11 16:54:51 eric 71 70
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00001/00001/00378
d D 4.2 83/08/28 14:45:08 eric 70 69
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00000/00000/00379
d D 4.1 83/07/25 19:45:45 eric 69 68
m 
c 4.2 release version
e
s 00002/00002/00377
d D 3.60 83/03/08 19:22:35 eric 68 67
m 205
c Pass the delimiter character to parseaddr so that we can correctly
c decide between comma and space
e
s 00001/00000/00378
d D 3.59 83/02/26 11:51:30 eric 67 66
m 193
c log queueid <=> message-id correspondence
e
s 00001/00001/00377
d D 3.58 83/02/10 10:00:37 eric 66 65
m 176
c avoid core dump on return receipt processing; clean up return receipt
c message.
e
s 00001/00001/00377
d D 3.57 83/02/02 12:52:56 eric 65 64
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00016/00015/00362
d D 3.56 83/01/06 10:45:55 eric 64 63
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00004/00002/00373
d D 3.55 83/01/03 18:01:23 eric 63 62
m 
c give more useful error messages (including the errno that caused
c a temporary failure); reflect these messages out to mailq
e
s 00007/00005/00368
d D 3.54 83/01/01 21:25:26 eric 62 61
m 123
c Put CRLF on all lines in user SMTP.  Pass this info down to
c innumerable routines.
e
s 00002/00002/00371
d D 3.53 82/12/24 08:14:41 eric 61 60
m 108
c Change parse to parseaddr for BB&N TCP/IP implementation; clean up
c comments in daemon.c to simplify the poor alternate protocol type.
e
s 00002/00002/00371
d D 3.52 82/12/13 18:24:59 eric 60 59
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00014/00012/00359
d D 3.51 82/12/05 13:46:18 eric 59 58
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00047/00040/00324
d D 3.50 82/11/28 00:22:07 eric 58 57
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00001/00001/00363
d D 3.49 82/11/24 18:44:20 eric 57 56
m 
c lint it
e
s 00031/00026/00333
d D 3.48 82/11/24 17:15:19 eric 56 55
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00002/00002/00357
d D 3.47 82/11/17 09:36:35 eric 55 54
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00015/00012/00344
d D 3.46 82/11/04 13:27:16 eric 54 53
m 037
c put header conditionals into the .cf file
e
s 00001/00000/00355
d D 3.45 82/10/09 21:02:17 eric 53 52
m 005
c force a queuename in returntosender to insure that everyone has a
c queue name.
e
s 00001/00001/00354
d D 3.44 82/09/24 09:38:26 eric 52 51
c arrange to be able to define options; put precedences in .cf file;
c send errors to an Errors-To: field; fix a serious bug causing mail
c to not be delivered to anyone if there were any errors.
e
s 00001/00000/00354
d D 3.43 82/09/08 21:19:52 eric 51 50
c try to avoid "Interrupted system call" on wait in deliver and on
c writes; fix returned message to have proper sender; handle extra
c mailer output more cleverly.
e
s 00005/00003/00349
d D 3.42 82/09/06 16:24:40 eric 50 49
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00001/00001/00351
d D 3.41 82/08/22 19:03:03 eric 49 48
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00002/00002/00350
d D 3.40 82/08/08 01:02:57 eric 48 47
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00001/00000/00351
d D 3.39 82/07/05 20:53:43 eric 47 46
c flush fatal errors when returning error messages to avoid error
c message loops
e
s 00008/00002/00343
d D 3.38 82/07/05 13:17:16 eric 46 45
c add debugging info & comments
e
s 00010/00000/00335
d D 3.37 82/06/26 13:53:28 eric 45 44
c more debug information; fix dependencies in makefile
e
s 00001/00002/00334
d D 3.36 82/06/26 13:10:27 eric 44 43
c lint
e
s 00002/00000/00334
d D 3.35 82/06/16 14:48:13 eric 43 42
c make sure there is always someone to return the message to
e
s 00002/00001/00332
d D 3.34 82/06/07 23:55:40 eric 42 41
c call the routine putline to output lines to mailers.  this lets us
c implement line length limits, etc. for full SMTP compatibility.
e
s 00005/00003/00328
d D 3.33 82/06/07 07:54:45 eric 41 40
c make transcripts verbose always; misc. message cleanup, etc.
e
s 00022/00016/00309
d D 3.32 82/06/06 23:05:08 eric 40 38
c implement alias owner feature.  this actually works for any user.
c basically, if the alias owner-xxx exists, errors sending to xxx will be
c sent to that alias rather than to the sender.
e
s 00010/00009/00316
d D 3.31.1.1 82/06/06 20:13:06 eric 39 38
c first cut at putting mailing list maintainers in -- there is a
c much better way though.
e
s 00004/00031/00321
d D 3.31 82/05/31 18:49:30 eric 38 37
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00006/00003/00346
d D 3.30 82/05/31 15:32:07 eric 37 35
i 36
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00082/00073/00267
d D 3.29.1.1 82/05/29 18:20:16 eric 36 35
c try to install envelopes.  is this really worth it???
e
s 00001/00001/00339
d D 3.29 82/05/22 02:05:38 eric 35 34
c add "junk mail" -- error responses are never returned.
e
s 00018/00018/00322
d D 3.28 82/05/22 01:37:56 eric 34 33
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00028/00006/00312
d D 3.27 82/02/27 11:37:31 eric 33 32
c implement "return receipt requested".
e
s 00003/00003/00315
d D 3.26 82/02/15 09:39:40 eric 32 31
c pass lint
e
s 00006/00003/00312
d D 3.25 82/01/01 18:27:07 eric 31 30
c send to dead.letter using sendto/recipient/deliver mechanism rather
c than mailfile; this fixes a bug with the "from" name and seems like
c a better abstraction.
e
s 00001/00001/00314
d D 3.24 81/12/06 12:38:49 eric 30 29
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00004/00002/00311
d D 3.23 81/11/11 20:24:01 eric 29 28
c integrate user SMTP into sendmail itself.  If there is no $u arg
c in the mailer argument list, SMTP is run.  This can be used directly
c over the Ethernet or to any clever mailer.  We still need to edit
c spooled control files to remove recipients that have been successfully
c sent during queue processing.
e
s 00004/00001/00309
d D 3.22 81/10/31 22:12:38 eric 28 27
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00053/00033/00257
d D 3.21 81/10/27 10:50:43 eric 27 26
c More queueing cleanup: implement timeouts (still one-stage),
c properly implement priorities (didn't work before), and miscellaneous
c cleanup.
e
s 00002/00002/00288
d D 3.20 81/10/23 19:38:02 eric 26 25
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00025/00000/00265
d D 3.19 81/10/02 11:05:15 eric 25 24
c arrange to give the correct "from" person on error messages.
e
s 00001/00001/00264
d D 3.18 81/09/16 16:08:01 eric 24 23
c run as the user forwarding mail after a .forward operation;
c fix a bug in .forwarding that caused recursive expansion;
c restrict mail to programs, files, and with :include: for security
c reasons.
e
s 00034/00004/00231
d D 3.17 81/09/06 19:48:51 eric 23 22
c cleanup, commenting, linting, etc.
e
s 00003/00001/00232
d D 3.16 81/09/01 11:43:33 eric 22 21
c add "suppress return-to-sender" function
e
s 00010/00005/00223
d D 3.15 81/08/21 18:51:22 eric 21 20
c return transcript even if no message was collected
e
s 00002/00002/00226
d D 3.14 81/08/21 18:18:34 eric 20 19
c drop M_FINAL, change some other defined constant names
e
s 00001/00002/00227
d D 3.13 81/08/20 15:14:20 eric 19 18
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00001/00001/00228
d D 3.12 81/08/18 17:12:57 eric 18 17
c factor out ARPANET FTP reply codes into conf.c
e
s 00003/00004/00226
d D 3.11 81/08/18 16:47:19 eric 17 16
c convert to really do arpanet reply codes right (maybe)
e
s 00015/00019/00215
d D 3.10 81/08/09 15:03:04 eric 16 15
c lint it
e
s 00013/00008/00221
d D 3.9 81/08/09 12:34:41 eric 15 14
c add private incoming mailers; add q_home field to ADDRESS struct;
c some general cleanup
e
s 00003/00006/00226
d D 3.8 81/08/08 16:06:55 eric 14 13
c fix up response printing
e
s 00003/00002/00229
d D 3.7 81/08/08 13:51:40 eric 13 12
c give arpanet-style error messages on -a
e
s 00001/00001/00230
d D 3.6 81/03/20 09:45:37 eric 12 11
c change name (again); from postbox to sendmail
e
s 00011/00030/00220
d D 3.5 81/03/11 10:46:06 eric 11 10
c general cleanup, esp. macro processor
e
s 00003/00003/00247
d D 3.4 81/03/09 13:22:29 eric 10 9
c first step at rewriting rules, etc.
e
s 00002/00002/00248
d D 3.3 81/03/07 16:59:39 eric 9 8
c change q_mailer to be index, not pointer
e
s 00002/00000/00248
d D 3.2 81/03/07 15:32:58 eric 8 7
c lint fixes
e
s 00003/00003/00245
d D 3.1 81/03/07 14:26:59 eric 7 6
c ----- delivermail ==> postbox -----
e
s 00003/00004/00245
d D 2.2 81/01/10 12:19:34 eric 6 5
c have name of mailer daemon be a configuration parameter
e
s 00000/00000/00249
d D 2.1 80/11/05 11:01:03 eric 5 4
c release 2
e
s 00000/00045/00249
d D 1.4 80/08/02 13:49:50 eric 4 3
c cleaned up comments
e
s 00002/00000/00292
d D 1.3 80/07/25 22:04:16 eric 3 2
c add ID keywords
e
s 00010/00021/00282
d D 1.2 80/07/25 21:40:17 eric 2 1
c changed "-ee" flag to work with BerkNet better
e
s 00303/00000/00000
d D 1.1 80/06/23 08:24:35 eric 1 0
e
u
U
f b 
f i 
t
T
I 75
/*
I 83
D 204
 * Copyright (c) 1983 Eric P. Allman
E 204
I 204
 * Copyright (c) 1983, 1995 Eric P. Allman
E 204
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
D 140
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 140
I 140
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 140
 *
D 87
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
E 87
I 87
 * %sccs.include.redist.c%
E 87
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

I 86
D 112
# include <sys/types.h>
E 112
E 86
E 75
I 1
D 19
# include <stdio.h>
E 19
D 146
# include <pwd.h>
E 146
D 7
# include "dlvrmail.h"
E 7
I 7
D 12
# include "postbox.h"
E 12
I 12
# include "sendmail.h"
I 146
D 202
# include <pwd.h>
E 202
E 146
E 12
E 7

I 3
D 30
static char	SccsId[] = "%W%	%G%";
E 30
I 30
D 76
SCCSID(%W%	%Y%	%G%);
E 30

E 76
E 3
/*
**  SAVEMAIL -- Save mail on error
**
D 58
**	If the MailBack flag is set, mail it back to the originator
E 58
I 58
**	If mailing back errors, mail it back to the originator
E 58
**	together with an error message; otherwise, just put it in
**	dead.letter in the user's home directory (if he exists on
**	this machine).
**
**	Parameters:
D 56
**		none
E 56
I 56
**		e -- the envelope containing the message in error.
I 181
**		sendbody -- if TRUE, also send back the body of the
**			message; otherwise just send the header.
E 181
E 56
**
**	Returns:
**		none
**
**	Side Effects:
**		Saves the letter, by writing or mailing it back to the
**		sender, or by putting it in dead.letter in her home
**		directory.
D 23
**
**		WARNING: the user id is reset to the original user.
E 23
D 4
**
**	Requires:
**		fopen (sys)
**		bmove
**		parse
**		deliver
**		strcpy (sys)
**		strcat (sys)
**		fclose (sys)
**		fgets (sys)
**		fputs (sys)
**		setpwent (sys)
**		getuid (sys)
**		setuid (sys)
**		getgid (sys)
**		setgid (sys)
**		getpwnam (sys)
**		fprintf (sys)
**		ttypath
**		freopen (sys)
**		printf (sys)
**		syserr
**		rewind (sys)
**		time (sys)
**		ferror (sys)
**
**	Called By:
**		finis
**
**	History:
**		12/30/79 -- written.
E 4
*/

I 77
/* defines for state machine */
# define ESM_REPORT	0	/* report to sender's terminal */
# define ESM_MAIL	1	/* mail back to sender */
# define ESM_QUIET	2	/* messages have already been returned */
# define ESM_DEADLETTER	3	/* save in ~/dead.letter */
# define ESM_POSTMASTER	4	/* return to postmaster */
# define ESM_USRTMP	5	/* save in /usr/tmp/dead.letter */
# define ESM_PANIC	6	/* leave the locked queue/transcript files */
# define ESM_DONE	7	/* the message is successfully delivered */

I 164
# ifndef _PATH_VARTMP
#  define _PATH_VARTMP	"/usr/tmp/"
# endif
E 164

I 164

I 211
void
E 211
E 164
E 77
D 6
# define MY_NAME	"~MAILER~DAEMON~"

E 6
D 56
savemail()
E 56
I 56
D 181
savemail(e)
E 181
I 181
savemail(e, sendbody)
E 181
	register ENVELOPE *e;
I 181
	bool sendbody;
E 181
E 56
{
	register struct passwd *pw;
D 77
	register FILE *xfile;
E 77
I 77
	register FILE *fp;
	int state;
D 131
	auto ADDRESS *q;
E 131
I 131
	auto ADDRESS *q = NULL;
I 165
	register char *p;
	MCI mcibuf;
I 203
	int sfflags;
E 203
E 165
E 131
E 77
	char buf[MAXLINE+1];
D 27
	extern errhdr();
D 7
	auto addrq to_addr;
E 7
I 7
	auto ADDRESS to_addr;
E 27
E 7
D 202
	extern struct passwd *getpwnam();
E 202
D 165
	register char *p;
E 165
D 32
	register int i;
E 32
D 16
	auto long tim;
	extern int errno;
E 16
	extern char *ttypath();
D 11
	extern char *ctime();
E 11
D 7
	extern addrq *parse();
E 7
I 7
D 16
	extern ADDRESS *parse();
E 16
E 7
D 58
	static int exclusive;
E 58
I 32
	typedef int (*fnptr)();
I 158
	extern bool writable();
E 158
I 36
D 38
	ENVELOPE errenvelope;
	register ENVELOPE *ee;
E 38
D 49
	extern ENVELOPE *newenvelope();
E 49
E 36
E 32
I 6
D 10
	extern char *DaemonName;
E 10
I 8
D 16
	extern char *strcpy(), *strcat();
D 11
	extern long time();
I 10
	extern char *Macro[];
E 11
I 11
	extern char *expand();
E 16
E 11
E 10
E 8
E 6

I 46
D 85
# ifdef DEBUG
E 85
D 48
	if (Debug)
E 48
I 48
	if (tTd(6, 1))
E 48
D 58
		printf("\nsavemail: exclusive %d\n", exclusive);
E 58
I 58
D 79
		printf("\nsavemail\n");
E 79
I 79
D 117
		printf("\nsavemail, ErrorMode = %c\n", ErrorMode);
E 117
I 117
	{
D 120
		printf("\nsavemail, ErrorMode = %c\n  e_from=", ErrorMode);
E 120
I 120
D 128
		printf("\nsavemail, errormode = %c\n  e_from=", e->e_errormode);
E 128
I 128
D 167
		printf("\nsavemail, errormode = %c, id = %s\n  e_from=",
			e->e_errormode, e->e_id == NULL ? "NONE" : e->e_id);
E 167
I 167
		printf("\nsavemail, errormode = %c, id = %s, ExitStat = %d\n  e_from=",
			e->e_errormode, e->e_id == NULL ? "NONE" : e->e_id,
			ExitStat);
E 167
E 128
E 120
		printaddr(&e->e_from, FALSE);
I 128
	}

	if (e->e_id == NULL)
	{
		/* can't return a message with no id */
		return;
E 128
	}
E 117
E 79
E 58
D 85
# endif DEBUG
E 85

E 46
D 19
	if (exclusive++)
E 19
I 19
D 21
	if (exclusive++ || TempFile == NULL)
E 21
I 21
D 35
	if (exclusive++)
E 35
I 35
D 36
	if (exclusive++ || CurEnv->e_class <= PRI_JUNK)
E 36
I 36
D 58
	if (exclusive++)
E 58
I 58
D 127
	if (bitset(EF_RESPONSE, e->e_flags))
E 58
E 36
E 35
E 21
E 19
		return;
E 127
I 36
D 52
	if (CurEnv->e_class <= PRI_JUNK)
E 52
I 52
D 56
	if (CurEnv->e_class < 0)
E 56
I 56
D 97
	if (e->e_class < 0)
E 56
E 52
	{
D 41
		if (Verbose)
			message(Arpa_Info, "Dumping junk mail");
E 41
I 41
		message(Arpa_Info, "Dumping junk mail");
E 41
		return;
	}
E 97
E 36
I 31
D 40
	ForceMail = TRUE;
E 40
I 40
D 41
	/* ForceMail = TRUE; */
E 41
I 41
D 109
	ForceMail = TRUE;
E 109
I 47
D 56
	FatalErrors = FALSE;
E 56
I 56
D 154
	e->e_flags &= ~EF_FATALERRS;
E 56
E 47
E 41
E 40
E 31

E 154
	/*
	**  In the unhappy event we don't know who to return the mail
	**  to, make someone up.
	*/

D 34
	if (From.q_paddr == NULL)
E 34
I 34
D 39
D 56
	if (CurEnv->e_from.q_paddr == NULL)
E 56
I 56
	if (e->e_from.q_paddr == NULL)
E 56
E 39
I 39
	if (CurEnv->e_returnto == NULL)
E 39
E 34
	{
D 34
		if (parse("root", &From, 0) == NULL)
E 34
I 34
D 39
D 56
		if (parse("root", &CurEnv->e_from, 0) == NULL)
E 56
I 56
D 61
		if (parse("root", &e->e_from, 0) == NULL)
E 61
I 61
D 68
		if (parseaddr("root", &e->e_from, 0) == NULL)
E 68
I 68
D 92
		if (parseaddr("root", &e->e_from, 0, '\0') == NULL)
E 92
I 92
D 113
		if (parseaddr("root", &e->e_from, 0, '\0', e) == NULL)
E 113
I 113
D 118
		if (parseaddr("root", &e->e_from, 0, '\0', NULL, e) == NULL)
E 118
I 118
D 119
		e->e_sender = "root";
E 119
I 119
		e->e_sender = "Postmaster";
E 119
D 149
		if (parseaddr(e->e_sender, &e->e_from, 0, '\0', NULL, e) == NULL)
E 149
I 149
		if (parseaddr(e->e_sender, &e->e_from,
			      RF_COPYPARSE|RF_SENDERADDR, '\0', NULL, e) == NULL)
E 149
E 118
E 113
E 92
E 68
E 61
E 56
E 39
I 39
		CurEnv->e_returnto = parse("root", (ADDRESS *) NULL, 0);
		if (CurEnv->e_returnto == NULL)
E 39
E 34
		{
D 106
			syserr("Cannot parse root!");
E 106
I 106
D 119
			syserr("553 Cannot parse root!");
E 119
I 119
			syserr("553 Cannot parse Postmaster!");
E 119
E 106
			ExitStat = EX_SOFTWARE;
			finis();
		}
	}
I 15
D 34
	To = NULL;
E 34
I 34
D 56
	CurEnv->e_to = NULL;
E 56
I 56
	e->e_to = NULL;
E 56
E 34
E 15

	/*
D 2
	**  If echoing the bad mail, do it.
	**	Output the transcript and a message saying that the
	**	message will be mailed back; then fall through to
	**	the MailBack case.
E 2
I 2
D 77
	**  If called from Eric Schmidt's network, do special mailback.
	**	Fundamentally, this is the mailback case except that
	**	it returns an OK exit status (assuming the return
	**	worked).
I 37
	**  Also, if the from address is not local, mail it back.
E 77
I 77
	**  Basic state machine.
	**
	**	This machine runs through the following states:
	**
	**	ESM_QUIET	Errors have already been printed iff the
	**			sender is local.
	**	ESM_REPORT	Report directly to the sender's terminal.
	**	ESM_MAIL	Mail response to the sender.
	**	ESM_DEADLETTER	Save response in ~/dead.letter.
	**	ESM_POSTMASTER	Mail response to the postmaster.
	**	ESM_PANIC	Save response anywhere possible.
E 77
E 37
E 2
	*/

D 2
	if (EchoBack || WriteBack)
E 2
I 2
D 58
	if (BerkNet)
E 58
I 58
D 77
	if (ErrorMode == EM_BERKNET)
E 77
I 77
	/* determine starting state */
D 120
	switch (ErrorMode)
E 120
I 120
	switch (e->e_errormode)
E 120
E 77
E 58
E 2
	{
I 77
	  case EM_WRITE:
		state = ESM_REPORT;
		break;

	  case EM_BERKNET:
D 212
		/* mail back, but return o.k. exit status */
E 77
D 2
		xfile = fopen(Transcript, "r");
		if (xfile == NULL)
			syserr("Cannot open %s", Transcript);
		fflush(stdout);
	}
	else
		xfile = NULL;

	if (EchoBack)
	{
		while (fgets(buf, sizeof buf, xfile) != NULL)
			fputs(buf, stderr);
		fprintf(stderr, "\nThe unsent mail will be returned to you\n");
E 2
I 2
		ExitStat = EX_OK;
E 2
D 37
		MailBack++;
E 37
I 37
D 58
		MailBack = TRUE;
E 58
I 58
D 77
		ErrorMode = EM_MAIL;
E 58
E 37
	}
I 37
D 39
D 56
	if (!bitset(M_LOCAL, CurEnv->e_from.q_mailer->m_flags))
E 56
I 56
D 65
	if (!bitset(M_LOCAL, e->e_from.q_mailer->m_flags))
E 65
I 65
	if (!bitnset(M_LOCAL, e->e_from.q_mailer->m_flags))
E 65
E 56
E 39
I 39
	if (!bitset(M_LOCAL, CurEnv->e_returnto->q_mailer->m_flags))
E 39
D 58
		MailBack = TRUE;
E 58
I 58
		ErrorMode = EM_MAIL;
E 77
E 58
E 37

D 77
	/*
	**  If writing back, do it.
	**	If the user is still logged in on the same terminal,
	**	then write the error messages back to hir (sic).
D 58
	**	If not, set the MailBack flag so that it will get
	**	mailed back instead.
E 58
I 58
	**	If not, mail back instead.
E 58
	*/
E 77
I 77
		/* fall through.... */
E 77

E 212
D 58
	if (WriteBack)
E 58
I 58
D 77
	if (ErrorMode == EM_WRITE)
E 77
I 77
	  case EM_MAIL:
		state = ESM_MAIL;
		break;

	  case EM_PRINT:
I 79
	  case '\0':
E 79
		state = ESM_QUIET;
		break;

	  case EM_QUIET:
		/* no need to return anything at all */
		return;
I 79

	  default:
D 106
		syserr("savemail: ErrorMode x%x\n");
E 106
I 106
D 120
		syserr("554 savemail: ErrorMode x%x\n");
E 120
I 120
		syserr("554 savemail: bogus errormode x%x\n", e->e_errormode);
E 120
E 106
		state = ESM_MAIL;
		break;
I 127
	}

	/* if this is already an error response, send to postmaster */
	if (bitset(EF_RESPONSE, e->e_flags))
	{
		if (e->e_parent != NULL &&
		    bitset(EF_RESPONSE, e->e_parent->e_flags))
		{
			/* got an error sending a response -- can it */
			return;
		}
		state = ESM_POSTMASTER;
E 127
E 79
	}

	while (state != ESM_DONE)
E 77
E 58
	{
I 79
D 85
# ifdef DEBUG
E 85
		if (tTd(6, 5))
			printf("  state %d\n", state);
D 85
# endif DEBUG
E 85

E 79
D 77
		p = ttypath();
		if (p == NULL || freopen(p, "w", stdout) == NULL)
E 77
I 77
		switch (state)
E 77
		{
I 79
		  case ESM_QUIET:
D 172
			if (e->e_from.q_mailer == LocalMailer)
E 172
I 172
			if (bitnset(M_LOCALMAILER, e->e_from.q_mailer->m_flags))
E 172
				state = ESM_DEADLETTER;
			else
				state = ESM_MAIL;
			break;

E 79
D 37
			MailBack++;
E 37
I 37
D 58
			MailBack = TRUE;
E 58
I 58
D 77
			ErrorMode = EM_MAIL;
E 58
E 37
			errno = 0;
		}
		else
		{
E 77
I 77
		  case ESM_REPORT:

			/*
			**  If the user is still logged in on the same terminal,
			**  then write the error messages back to hir (sic).
			*/

			p = ttypath();
			if (p == NULL || freopen(p, "w", stdout) == NULL)
			{
				state = ESM_MAIL;
				break;
			}

E 77
I 58
D 71
			expand("$n", buf, &buf[sizeof buf - 1], e);
E 71
I 71
D 101
			expand("\001n", buf, &buf[sizeof buf - 1], e);
E 101
I 101
D 196
			expand("\201n", buf, &buf[sizeof buf - 1], e);
E 196
I 196
			expand("\201n", buf, sizeof buf, e);
E 196
E 101
E 71
			printf("\r\nMessage from %s...\r\n", buf);
			printf("Errors occurred while sending mail.\r\n");
E 58
I 28
D 56
			(void) fflush(Xscript);
E 28
I 2
			xfile = fopen(Transcript, "r");
E 56
I 56
D 59
			if (Xscript != NULL)
E 59
I 59
			if (e->e_xfp != NULL)
E 59
I 58
			{
E 58
D 59
				(void) fflush(Xscript);
E 59
I 59
				(void) fflush(e->e_xfp);
E 59
D 58
			xfile = fopen(queuename(e, 'x'), "r");
E 58
I 58
D 77
				xfile = fopen(queuename(e, 'x'), "r");
E 77
I 77
				fp = fopen(queuename(e, 'x'), "r");
E 77
			}
			else
D 77
				xfile = NULL;
E 58
E 56
			if (xfile == NULL)
E 77
I 77
				fp = NULL;
			if (fp == NULL)
E 77
I 58
			{
E 58
D 56
				syserr("Cannot open %s", Transcript);
E 2
D 6
			printf("\r\nMessage from %s\r\n", MY_NAME);
E 6
I 6
D 10
			printf("\r\nMessage from %s\r\n", DaemonName);
E 10
I 10
D 11
			printf("\r\nMessage from %s\r\n", Macro['d']);
E 11
I 11
D 16
			printf("\r\nMessage from %s\r\n", expand("$n", buf, &buf[sizeof buf - 1]));
E 16
I 16
D 36
			(void) expand("$n", buf, &buf[sizeof buf - 1]);
E 36
I 36
			expand("$n", buf, &buf[sizeof buf - 1], CurEnv);
E 56
I 56
				syserr("Cannot open %s", queuename(e, 'x'));
D 58
			expand("$n", buf, &buf[sizeof buf - 1], e);
E 56
E 36
D 17
			printf("\r\nMessage from %s\r\n", buf);
E 17
I 17
			printf("\r\nMessage from %s...\r\n", buf);
E 17
E 16
E 11
E 10
E 6
D 23
			printf("Errors occurred while sending mail, transcript follows:\r\n");
E 23
I 23
			printf("Errors occurred while sending mail; transcript follows:\r\n");
E 23
D 16
			while (fgets(buf, sizeof buf, xfile) && !ferror(stdout))
E 16
I 16
			while (fgets(buf, sizeof buf, xfile) != NULL && !ferror(stdout))
E 16
				fputs(buf, stdout);
E 58
I 58
				printf("Transcript of session is unavailable.\r\n");
			}
			else
			{
				printf("Transcript follows:\r\n");
D 77
				while (fgets(buf, sizeof buf, xfile) != NULL &&
E 77
I 77
				while (fgets(buf, sizeof buf, fp) != NULL &&
E 77
				       !ferror(stdout))
					fputs(buf, stdout);
D 77
				(void) fclose(xfile);
E 77
I 77
D 117
				(void) fclose(fp);
E 117
I 117
				(void) xfclose(fp, "savemail transcript", e->e_id);
E 117
E 77
			}
I 77
			printf("Original message will be saved in dead.letter.\r\n");
E 77
E 58
D 84
			if (ferror(stdout))
D 16
				syserr("savemail: stdout: write err");
I 2
			fclose(xfile);
E 16
I 16
				(void) syserr("savemail: stdout: write err");
E 84
D 58
			(void) fclose(xfile);
E 58
E 16
E 2
D 77
		}
	}
E 77
I 77
			state = ESM_DEADLETTER;
			break;
E 77

D 2
	if (xfile != NULL)
		fclose(xfile);

E 2
D 77
	/*
	**  If mailing back, do it.
	**	Throw away all further output.  Don't do aliases, since
	**	this could cause loops, e.g., if joe mails to x:joe,
	**	and for some reason the network for x: is down, then
	**	the response gets sent to x:joe, which gives a
	**	response, etc.  Also force the mail to be delivered
	**	even if a version of it has already been sent to the
	**	sender.
	*/
E 77
I 77
		  case ESM_MAIL:
D 117
		  case ESM_POSTMASTER:
E 117
			/*
			**  If mailing back, do it.
			**	Throw away all further output.  Don't alias,
			**	since this could cause loops, e.g., if joe
			**	mails to joe@x, and for some reason the network
			**	for @x is down, then the response gets sent to
			**	joe@x, which gives a response, etc.  Also force
			**	the mail to be delivered even if a version of
			**	it has already been sent to the sender.
I 143
			**
			**  If this is a configuration or local software
			**	error, send to the local postmaster as well,
			**	since the originator can't do anything
			**	about it anyway.  Note that this is a full
			**	copy of the message (intentionally) so that
			**	the Postmaster can forward things along.
E 143
I 109
D 117
			**
			**	Clever technique for computing rpath from
			**	Eric Wassenaar <e07@nikhef.nl>.
E 117
E 109
			*/
E 77

I 143
			if (ExitStat == EX_CONFIG || ExitStat == EX_SOFTWARE)
			{
				(void) sendtolist("postmaster",
D 149
					  (ADDRESS *) NULL,
					  &e->e_errorqueue, e);
E 149
I 149
D 182
					  NULLADDR, &e->e_errorqueue, e);
E 182
I 182
					  NULLADDR, &e->e_errorqueue, 0, e);
E 182
E 149
			}
E 143
D 9
	if (MailBack || From.q_mailer != &Mailer[0])
E 9
I 9
D 58
	if (MailBack)
E 58
I 58
D 77
	if (ErrorMode == EM_MAIL)
E 58
E 9
	{
I 43
D 56
		if (CurEnv->e_errorqueue == NULL)
D 44
			sendto(CurEnv->e_from.q_paddr, 1, NULL, &CurEnv->e_errorqueue);
E 44
I 44
D 50
			sendto(CurEnv->e_from.q_paddr, 1, (ADDRESS *) NULL, &CurEnv->e_errorqueue);
E 44
E 43
D 16
		freopen("/dev/null", "w", stdout);
E 16
I 16
D 27
		(void) freopen("/dev/null", "w", stdout);
E 16
		NoAlias++;
		ForceMail++;

		/* fake up an address header for the from person */
		bmove((char *) &From, (char *) &to_addr, sizeof to_addr);
D 6
		if (parse(MY_NAME, &From, -1) == NULL)
E 6
I 6
D 10
		if (parse(DaemonName, &From, -1) == NULL)
E 10
I 10
D 11
		if (parse(Macro['d'], &From, -1) == NULL)
E 11
I 11
D 16
		if (parse(expand("$n", buf, &buf[sizeof buf - 1]), &From, -1) == NULL)
E 16
I 16
		(void) expand("$n", buf, &buf[sizeof buf - 1]);
		if (parse(buf, &From, -1) == NULL)
E 16
E 11
E 10
E 6
		{
			syserr("Can't parse myself!");
			ExitStat = EX_SOFTWARE;
			finis();
		}
I 23
		to_addr.q_next = NULL;
E 23
		i = deliver(&to_addr, errhdr);
		bmove((char *) &to_addr, (char *) &From, sizeof From);
		if (i != 0)
			syserr("Can't return mail to %s", p);
		else
E 27
I 27
D 33
		if (returntosender("Unable to deliver mail") == 0)
E 33
I 33
D 36
		if (returntosender("Unable to deliver mail", TRUE) == 0)
E 36
I 36
D 39
D 40
		if (returntosender("Unable to deliver mail", &CurEnv->e_from, TRUE) == 0)
E 40
I 40
		if (returntosender("Unable to deliver mail", CurEnv->e_errorqueue, TRUE) == 0)
E 50
I 50
			sendto(CurEnv->e_from.q_paddr, (ADDRESS *) NULL,
			       &CurEnv->e_errorqueue);
E 56
I 56
		if (e->e_errorqueue == NULL)
D 60
			sendto(e->e_from.q_paddr, (ADDRESS *) NULL,
E 60
I 60
			sendtolist(e->e_from.q_paddr, (ADDRESS *) NULL,
E 60
			       &e->e_errorqueue);
E 56
D 63
		if (returntosender("Unable to deliver mail",
E 63
I 63
		if (returntosender(e->e_message != NULL ? e->e_message :
				   "Unable to deliver mail",
E 63
D 56
				   CurEnv->e_errorqueue, TRUE) == 0)
E 56
I 56
				   e->e_errorqueue, TRUE) == 0)
E 56
E 50
E 40
E 39
I 39
		if (returntosender("Unable to deliver mail", CurEnv->e_returnto, TRUE) == 0)
E 39
E 36
E 33
E 27
			return;
	}
E 77
I 77
D 117
			if (state == ESM_MAIL)
E 117
I 117
D 179
			if (strcmp(e->e_from.q_paddr, "<>") != 0)
E 179
I 179
			if (!emptyaddr(&e->e_from))
E 179
I 143
			{
E 143
				(void) sendtolist(e->e_from.q_paddr,
D 149
					  (ADDRESS *) NULL,
					  &e->e_errorqueue, e);
E 149
I 149
D 182
					  NULLADDR, &e->e_errorqueue, e);
E 182
I 182
					  NULLADDR, &e->e_errorqueue, 0, e);
E 182
E 149
I 143
			}
E 143

D 143
			/* deliver a cc: to the postmaster if desired */
E 143
I 143
			/*
			**  Deliver a non-delivery report to the
			**  Postmaster-designate (not necessarily
			**  Postmaster).  This does not include the
			**  body of the message, for privacy reasons.
			**  You really shouldn't need this.
			*/

E 143
D 144
			if (PostMasterCopy != NULL)
E 117
			{
D 103
				if (e->e_errorqueue == NULL)
E 103
I 103
D 107
				if (e->e_errorqueue == NULL &&
				    strcmp(e->e_from.q_paddr, "<>") != 0)
E 103
D 102
					sendtolist(e->e_from.q_paddr,
						(ADDRESS *) NULL,
D 92
						&e->e_errorqueue);
E 92
I 92
						&e->e_errorqueue, e);
E 102
I 102
					(void) sendtolist(e->e_from.q_paddr,
E 107
I 107
D 110
				if (e->e_errorqueue == NULL)
				{
					char *rpath;
E 110
I 110
D 117
				char *rpath;
E 117
I 117
				auto ADDRESS *rlist = NULL;
E 144
I 144
			e->e_flags |= EF_PM_NOTIFY;
E 144
E 117
E 110

D 109
					if (strcmp(e->e_returnpath, "<>") != 0)
E 109
I 109
D 110
					if (e->e_returnpath != e->e_sender)
E 109
						rpath = e->e_returnpath;
D 109
					else if (strcmp(e->e_from.q_paddr, "<>") != 0)
						rpath = e->e_from.q_paddr;
E 109
					else
D 109
						rpath = NULL;
					if (rpath != NULL)
E 109
I 109
						rpath = e->e_from.q_paddr;
					if (strcmp(rpath, "<>") != 0)
E 109
						(void) sendtolist(rpath,
E 107
							  (ADDRESS *) NULL,
							  &e->e_errorqueue, e);
I 107
				}
E 110
I 110
D 117
				if (e->e_returnpath != e->e_sender)
					rpath = e->e_returnpath;
				else
					rpath = e->e_from.q_paddr;
				if (strcmp(rpath, "<>") != 0)
					(void) sendtolist(rpath,
E 117
I 117
D 144
				(void) sendtolist(PostMasterCopy,
E 117
						  (ADDRESS *) NULL,
D 117
						  &e->e_errorqueue, e);
E 117
I 117
						  &rlist, e);
				(void) returntosender(e->e_message,
						      rlist, FALSE, e);
			}
I 143

E 144
E 143
D 156
			q = e->e_errorqueue;
E 156
I 156
			/* check to see if there are any good addresses */
			for (q = e->e_errorqueue; q != NULL; q = q->q_next)
				if (!bitset(QBADADDR|QDONTSEND, q->q_flags))
					break;
E 156
			if (q == NULL)
			{
				/* this is an error-error */
				state = ESM_POSTMASTER;
				break;
			}
D 124
			if (returntosender(e->e_message != NULL ? e->e_message :
					   "Unable to deliver mail",
E 124
I 124
D 166
			if (returntosender(e->e_message,
E 124
					   q, (e->e_class >= 0), e) == 0)
E 166
I 166
			if (returntosender(e->e_message, e->e_errorqueue,
D 181
					   (e->e_class >= 0), e) == 0)
E 181
I 181
					   sendbody, e) == 0)
E 181
E 166
			{
				state = ESM_DONE;
				break;
			}
E 117
E 110
E 107
E 102
E 92
I 80

D 117
				/* deliver a cc: to the postmaster if desired */
				if (PostMasterCopy != NULL)
I 111
				{
					auto ADDRESS *rlist = NULL;
E 117
I 117
			/* didn't work -- return to postmaster */
			state = ESM_POSTMASTER;
			break;
E 117

E 111
D 102
					sendtolist(PostMasterCopy,
						(ADDRESS *) NULL,
D 92
						&e->e_errorqueue);
E 92
I 92
						&e->e_errorqueue, e);
E 102
I 102
D 117
					(void) sendtolist(PostMasterCopy,
							  (ADDRESS *) NULL,
D 111
							  &e->e_errorqueue, e);
E 111
I 111
							  &rlist, e);
					(void) returntosender(e->e_message,
							      rlist, FALSE, e);
				}
E 111
E 102
E 92
E 80
				q = e->e_errorqueue;
I 103
				if (q == NULL)
				{
					/* this is an error-error */
					state = ESM_USRTMP;
					break;
				}
E 103
			}
			else
E 117
I 117
		  case ESM_POSTMASTER:
			/*
			**  Similar to previous case, but to system postmaster.
			*/

D 125
			if (parseaddr("postmaster", q, 0, '\0', NULL, e) == NULL)
E 125
I 125
D 132
			q = parseaddr("postmaster", q, 0, '\0', NULL, e);
			if (q == NULL)
E 132
I 132
			q = NULL;
D 182
			if (sendtolist("postmaster", NULL, &q, e) <= 0)
E 182
I 182
			if (sendtolist("postmaster", NULL, &q, 0, e) <= 0)
E 182
E 132
E 125
E 117
			{
D 78
				if (parseaddr("postmaster", &q, 0, '\0') == NULL)
E 78
I 78
D 92
				if (parseaddr("postmaster", q, 0, '\0') == NULL)
E 92
I 92
D 113
				if (parseaddr("postmaster", q, 0, '\0', e) == NULL)
E 113
I 113
D 117
				if (parseaddr("postmaster", q, 0, '\0', NULL, e) == NULL)
E 113
E 92
E 78
				{
D 106
					syserr("cannot parse postmaster!");
E 106
I 106
					syserr("553 cannot parse postmaster!");
E 106
					ExitStat = EX_SOFTWARE;
					state = ESM_USRTMP;
					break;
				}
E 117
I 117
				syserr("553 cannot parse postmaster!");
				ExitStat = EX_SOFTWARE;
				state = ESM_USRTMP;
				break;
E 117
			}
D 124
			if (returntosender(e->e_message != NULL ? e->e_message :
					   "Unable to deliver mail",
E 124
I 124
D 181
			if (returntosender(e->e_message,
E 124
D 92
					   q, TRUE) == 0)
E 92
I 92
D 97
					   q, TRUE, e) == 0)
E 97
I 97
					   q, (e->e_class >= 0), e) == 0)
E 181
I 181
			if (returntosender(e->e_message, q, sendbody, e) == 0)
E 181
E 97
E 92
			{
				state = ESM_DONE;
				break;
			}
E 77

D 77
	/*
	**  Save the message in dead.letter.
	**	If we weren't mailing back, and the user is local, we
	**	should save the message in dead.letter so that the
	**	poor person doesn't have to type it over again --
	**	and we all know what poor typists programmers are.
I 46
D 58
	**	However, if we are running a "smart" protocol, we don't
	**	bother to return the message, since the other end is
	**	expected to handle that.
E 58
E 46
	*/
E 77
I 77
D 117
			state = state == ESM_MAIL ? ESM_POSTMASTER : ESM_USRTMP;
E 117
I 117
			/* didn't work -- last resort */
			state = ESM_USRTMP;
E 117
			break;
E 77

I 13
D 14
	To = NULL;
E 14
E 13
D 16
	setuid(getuid());
	setgid(getgid());
E 16
I 16
D 17
	(void) setuid(getuid());
	(void) setgid(getgid());
E 16
	setpwent();
E 17
I 17
D 28
	if (ArpaMode != ARPA_NONE)
E 28
I 28
D 55
	if (ArpaMode)
E 55
I 55
D 58
	if (OpMode == MD_ARPAFTP || OpMode == MD_SMTP)
E 55
E 28
		return;
E 58
E 17
D 9
	if (From.q_mailer == &Mailer[0] && (pw = getpwnam(From.q_user)) != NULL)
E 9
I 9
D 15
	if (From.q_mailer == 0 && (pw = getpwnam(From.q_user)) != NULL)
E 15
I 15
D 77
	p = NULL;
D 20
	if (From.q_mailer == M_LOCAL)
E 20
I 20
D 26
	if (From.q_mailer == MN_LOCAL)
E 26
I 26
D 34
	if (From.q_mailer == LocalMailer)
E 34
I 34
D 39
D 56
	if (CurEnv->e_from.q_mailer == LocalMailer)
E 56
I 56
	if (e->e_from.q_mailer == LocalMailer)
E 56
E 39
I 39
	if (CurEnv->e_returnto->q_mailer == LocalMailer)
E 39
E 34
E 26
E 20
E 15
E 9
	{
D 15
		/* user has a home directory */
		p = pw->pw_dir;
E 15
I 15
D 34
		if (From.q_home != NULL)
			p = From.q_home;
		else if ((pw = getpwnam(From.q_user)) != NULL)
E 34
I 34
D 39
D 56
		if (CurEnv->e_from.q_home != NULL)
			p = CurEnv->e_from.q_home;
		else if ((pw = getpwnam(CurEnv->e_from.q_user)) != NULL)
E 56
I 56
		if (e->e_from.q_home != NULL)
			p = e->e_from.q_home;
		else if ((pw = getpwnam(e->e_from.q_user)) != NULL)
E 56
E 39
I 39
		if (CurEnv->e_returnto->q_home != NULL)
			p = CurEnv->e_returnto->q_home;
		else if ((pw = getpwnam(CurEnv->e_returnto->q_user)) != NULL)
E 39
E 34
			p = pw->pw_dir;
E 15
	}
D 15
	else
E 15
I 15
	if (p == NULL)
E 15
	{
D 15
		syserr("Can't return mail to %s (pw=%u)", From.q_paddr, pw);
E 15
I 15
D 34
		syserr("Can't return mail to %s", From.q_paddr);
E 34
I 34
D 39
D 56
		syserr("Can't return mail to %s", CurEnv->e_from.q_paddr);
E 56
I 56
		syserr("Can't return mail to %s", e->e_from.q_paddr);
E 56
E 39
I 39
		syserr("Can't return mail to %s", CurEnv->e_returnto->q_paddr);
E 39
E 34
E 15
# ifdef DEBUG
		p = "/usr/tmp";
D 46
# else
		p = NULL;
E 46
# endif
	}
D 21
	if (p != NULL)
E 21
I 21
D 59
	if (p != NULL && TempFile != NULL)
E 59
I 59
	if (p != NULL && e->e_dfp != NULL)
E 59
E 21
	{
I 31
		auto ADDRESS *q;
I 41
		bool oldverb = Verbose;
E 77
I 77
		  case ESM_DEADLETTER:
			/*
			**  Save the message in dead.letter.
			**	If we weren't mailing back, and the user is
			**	local, we should save the message in
			**	~/dead.letter so that the poor person doesn't
			**	have to type it over again -- and we all know
			**	what poor typists UNIX users are.
			*/
E 77
E 41

E 31
D 77
		/* we have a home directory; open dead.letter */
I 58
		define('z', p, e);
D 71
		expand("$z/dead.letter", buf, &buf[sizeof buf - 1], e);
E 71
I 71
		expand("\001z/dead.letter", buf, &buf[sizeof buf - 1], e);
E 71
E 58
I 41
		Verbose = TRUE;
E 41
D 15
		strcpy(buf, p);
		strcat(buf, "/dead.letter");
E 15
I 15
D 18
		message("050", "Saving message in dead.letter");
E 18
I 18
D 58
		message(Arpa_Info, "Saving message in dead.letter");
E 58
I 58
		message(Arpa_Info, "Saving message in %s", buf);
E 58
I 41
		Verbose = oldverb;
E 41
E 18
D 58
		define('z', p);
D 16
		expand("$z/dead.letter", buf, &buf[sizeof buf - 1]);
E 16
I 16
D 36
		(void) expand("$z/dead.letter", buf, &buf[sizeof buf - 1]);
E 36
I 36
D 56
		expand("$z/dead.letter", buf, &buf[sizeof buf - 1], CurEnv);
E 36
E 16
E 15
D 11
		xfile = fopen(buf, "a");
		if (xfile == NULL)
E 11
I 11
D 14
		if (mailfile(buf) != EX_OK)
E 11
D 13
			printf("Cannot save mail, sorry\n");
E 13
I 13
			message("050", "Cannot save mail, sorry");
E 13
		else
D 11
		{
			rewind(stdin);
			errno = 0;
			time(&tim);
			fprintf(xfile, "----- Mail saved at %s", ctime(&tim));
			while (fgets(buf, sizeof buf, stdin) && !ferror(xfile))
				fputs(buf, xfile);
			fputs("\n", xfile);
			if (ferror(xfile))
				syserr("savemail: dead.letter: write err");
			fclose(xfile);
E 11
D 13
			printf("Letter saved in dead.letter\n");
E 13
I 13
			message("050", "Letter saved in dead.letter");
E 14
I 14
D 34
		To = buf;
E 34
I 34
		CurEnv->e_to = buf;
E 56
I 56
		expand("$z/dead.letter", buf, &buf[sizeof buf - 1], e);
E 58
		e->e_to = buf;
E 56
E 34
D 24
		i = mailfile(buf);
E 24
I 24
D 31
		i = mailfile(buf, &From);
E 24
D 15
		giveresponse(i, TRUE, Mailer[0]);
E 15
I 15
D 20
		giveresponse(i, TRUE, Mailer[M_LOCAL]);
E 20
I 20
D 26
		giveresponse(i, TRUE, Mailer[MN_LOCAL]);
E 26
I 26
		giveresponse(i, TRUE, LocalMailer);
E 31
I 31
		q = NULL;
D 32
		sendto(buf, -1, NULL, &q);
		(void) deliver(q, NULL);
E 32
I 32
D 50
		sendto(buf, -1, (ADDRESS *) NULL, &q);
E 50
I 50
D 60
		sendto(buf, (ADDRESS *) NULL, &q);
E 60
I 60
		sendtolist(buf, (ADDRESS *) NULL, &q);
E 60
E 50
D 36
		(void) deliver(q, (fnptr) NULL);
E 36
I 36
D 58
		(void) deliver(q);
E 58
I 58
		(void) deliver(e, q);
E 58
E 36
E 32
E 31
E 26
E 20
E 15
E 14
E 13
D 11
		}
E 11
	}
E 77
I 77
			p = NULL;
D 172
			if (e->e_from.q_mailer == LocalMailer)
E 172
I 172
			if (bitnset(M_HASPWENT, e->e_from.q_mailer->m_flags))
E 172
			{
				if (e->e_from.q_home != NULL)
					p = e->e_from.q_home;
D 202
				else if ((pw = getpwnam(e->e_from.q_user)) != NULL)
E 202
I 202
				else if ((pw = sm_getpwnam(e->e_from.q_user)) != NULL)
E 202
					p = pw->pw_dir;
			}
D 203
			if (p == NULL)
E 203
I 203
			if (p == NULL || e->e_dfp == NULL)
E 203
			{
D 106
				syserr("Can't return mail to %s", e->e_from.q_paddr);
E 106
I 106
D 122
				syserr("554 Can't return mail to %s", e->e_from.q_paddr);
E 122
I 122
D 203
				/* no local directory */
E 203
I 203
				/* no local directory or no data file */
E 203
E 122
E 106
				state = ESM_MAIL;
				break;
			}
D 203
			if (e->e_dfp != NULL)
			{
D 131
				auto ADDRESS *q;
E 131
				bool oldverb = Verbose;
E 203
E 77
D 14
	else
E 14

D 77
	/* add terminator to writeback message */
D 58
	if (WriteBack)
E 58
I 58
	if (ErrorMode == EM_WRITE)
E 58
		printf("-----\r\n");
E 77
I 77
D 203
				/* we have a home directory; open dead.letter */
				define('z', p, e);
D 101
				expand("\001z/dead.letter", buf, &buf[sizeof buf - 1], e);
E 101
I 101
D 196
				expand("\201z/dead.letter", buf, &buf[sizeof buf - 1], e);
E 196
I 196
				expand("\201z/dead.letter", buf, sizeof buf, e);
E 196
E 101
				Verbose = TRUE;
D 106
				message(Arpa_Info, "Saving message in %s", buf);
E 106
I 106
				message("Saving message in %s", buf);
E 106
				Verbose = oldverb;
				e->e_to = buf;
				q = NULL;
D 92
				sendtolist(buf, (ADDRESS *) NULL, &q);
E 92
I 92
D 99
				sendtolist(buf, (ADDRESS *) NULL, &q, e);
E 99
I 99
D 102
				sendtolist(buf, &e->e_from, &q, e);
E 102
I 102
D 182
				(void) sendtolist(buf, &e->e_from, &q, e);
E 182
I 182
				(void) sendtolist(buf, &e->e_from, &q, 0, e);
E 182
E 102
E 99
E 92
D 150
				if (deliver(e, q) == 0)
E 150
I 150
D 151
				if (q != NULL && deliver(e, q) == 0)
E 151
I 151
				if (q != NULL &&
				    !bitset(QBADADDR, q->q_flags) &&
				    deliver(e, q) == 0)
E 151
E 150
					state = ESM_DONE;
				else
					state = ESM_MAIL;
			}
I 81
			else
			{
				/* no data file -- try mailing back */
				state = ESM_MAIL;
			}
E 81
			break;
E 203
I 203
D 213
			/* we have a home directory; open dead.letter */
E 213
I 213
			/* we have a home directory; write dead.letter */
E 213
			define('z', p, e);
			expand("\201z/dead.letter", buf, sizeof buf, e);
			sfflags = SFF_NOSLINK|SFF_CREAT|SFF_REGONLY|SFF_RUNASREALUID;
			e->e_to = buf;
D 213
			goto writefile;
E 213
I 213
			if (mailfile(buf, NULL, sfflags, e) == EX_OK)
			{
				bool oldverb = Verbose;
E 213
E 203

I 213
				Verbose = TRUE;
				message("Saved message in %s", buf);
				Verbose = oldverb;
				state = ESM_DONE;
				break;
			}
			state = ESM_MAIL;
			break;

E 213
		  case ESM_USRTMP:
			/*
			**  Log the mail in /usr/tmp/dead.letter.
			*/

I 97
			if (e->e_class < 0)
			{
				state = ESM_DONE;
				break;
			}

I 192
			if (SafeFileEnv != NULL && SafeFileEnv[0] != '\0')
			{
				state = ESM_PANIC;
				break;
			}

E 192
E 97
D 135
			fp = dfopen("/usr/tmp/dead.letter", "a");
E 135
I 135
D 158
			fp = dfopen("/usr/tmp/dead.letter",
				    O_WRONLY|O_CREAT|O_APPEND, FileMode);
E 158
I 158
D 164
			strcpy(buf, "/usr/tmp/dead.letter");
E 164
I 164
			strcpy(buf, _PATH_VARTMP);
			strcat(buf, "dead.letter");
E 164
D 162
			if (!writable(buf))
E 162
I 162
D 163
			if (!writable(buf, SFF_NOSLINK))
E 163
I 163
D 193
			if (!writable(buf, NULLADDR, SFF_NOSLINK))
E 193
I 193
D 203
			if (!writable(buf, NULLADDR, SFF_NOSLINK|SFF_CREAT))
E 203
I 203
D 219
			sfflags = SFF_NOSLINK|SFF_CREAT|SFF_REGONLY;
E 219

I 219
			sfflags = SFF_NOSLINK|SFF_CREAT|SFF_REGONLY|SFF_ROOTOK;
E 219
D 213
  writefile:
			if (!writable(buf, q, sfflags) ||
E 213
I 213
			if (!writable(buf, NULL, sfflags) ||
E 213
			    (fp = safefopen(buf, O_WRONLY|O_CREAT|O_APPEND,
					    FileMode, sfflags)) == NULL)
E 203
E 193
E 163
E 162
			{
D 203
				state = ESM_PANIC;
E 203
I 203
D 213
				if (state == ESM_USRTMP)
					state = ESM_PANIC;
				else
					state = ESM_MAIL;
E 213
I 213
				state = ESM_PANIC;
E 213
E 203
				break;
			}
D 193
			fp = dfopen(buf, O_WRONLY|O_CREAT|O_APPEND, FileMode);
E 193
I 193
D 203
			fp = safefopen(buf, O_WRONLY|O_CREAT|O_APPEND,
D 194
					FileMode, SFF_NOSLINK);
E 194
I 194
					FileMode, SFF_NOSLINK|SFF_REGONLY);
E 194
E 193
E 158
E 135
			if (fp == NULL)
			{
				state = ESM_PANIC;
				break;
			}
E 203

D 91
			putfromline(fp, ProgMailer);
E 91
I 91
D 99
			putfromline(fp, ProgMailer, e);
E 91
			(*e->e_puthdr)(fp, ProgMailer, e);
			putline("\n", fp, ProgMailer);
			(*e->e_putbody)(fp, ProgMailer, e);
			putline("\n", fp, ProgMailer);
E 99
I 99
D 165
			putfromline(fp, FileMailer, e);
			(*e->e_puthdr)(fp, FileMailer, e);
			putline("\n", fp, FileMailer);
D 134
			(*e->e_putbody)(fp, FileMailer, e);
E 134
I 134
			(*e->e_putbody)(fp, FileMailer, e, NULL);
E 134
			putline("\n", fp, FileMailer);
E 165
I 165
			bzero(&mcibuf, sizeof mcibuf);
			mcibuf.mci_out = fp;
			mcibuf.mci_mailer = FileMailer;
			if (bitnset(M_7BITS, FileMailer->m_flags))
				mcibuf.mci_flags |= MCIF_7BIT;

			putfromline(&mcibuf, e);
D 173
			(*e->e_puthdr)(&mcibuf, e);
			putline("\n", &mcibuf);
E 173
I 173
D 177
			(*e->e_puthdr)(&mcibuf, e->e_header, e);
E 173
			(*e->e_putbody)(&mcibuf, e, NULL);
E 177
I 177
D 191
			(*e->e_puthdr)(&mcibuf, e->e_header, e, 0);
			(*e->e_putbody)(&mcibuf, e, NULL, 0);
E 191
I 191
			(*e->e_puthdr)(&mcibuf, e->e_header, e);
			(*e->e_putbody)(&mcibuf, e, NULL);
E 191
E 177
			putline("\n", &mcibuf);
E 165
E 99
			(void) fflush(fp);
D 203
			state = ferror(fp) ? ESM_PANIC : ESM_DONE;
E 203
I 203
			if (!ferror(fp))
			{
				bool oldverb = Verbose;

				Verbose = TRUE;
				message("Saved message in %s", buf);
				Verbose = oldverb;
I 219
#ifdef LOG
				if (LogLevel > 3)
					syslog(LOG_NOTICE, "Saved message in %s", buf);
#endif
E 219
				state = ESM_DONE;
I 219
				break;
E 219
			}
D 213
			else if (state == ESM_USRTMP)
				state = ESM_PANIC;
			else
				state = ESM_MAIL;
E 213
I 213
			state = ESM_PANIC;
E 213
E 203
D 117
			(void) fclose(fp);
E 117
I 117
D 175
			(void) xfclose(fp, "savemail", "/usr/tmp/dead.letter");
E 175
I 175
			(void) xfclose(fp, "savemail", buf);
E 175
E 117
			break;

		  default:
D 106
			syserr("savemail: unknown state %d", state);
E 106
I 106
			syserr("554 savemail: unknown state %d", state);
E 106

			/* fall through ... */

		  case ESM_PANIC:
D 97
			syserr("savemail: HELP!!!!");
# ifdef LOG
			if (LogLevel >= 1)
				syslog(LOG_ALERT, "savemail: HELP!!!!");
D 95
# endif LOG
E 95
I 95
# endif /* LOG */
E 95

E 97
			/* leave the locked queue & transcript files around */
I 192
			loseqfile(e, "savemail panic");
E 192
I 97
D 106
			syserr("savemail: cannot save rejected email anywhere");
E 106
I 106
D 159
			syserr("554 savemail: cannot save rejected email anywhere");
E 106
E 97
			exit(EX_SOFTWARE);
E 159
I 159
			syserr("!554 savemail: cannot save rejected email anywhere");
E 159
		}
	}
E 77
}
/*
I 27
**  RETURNTOSENDER -- return a message to the sender with an error.
**
**	Parameters:
**		msg -- the explanatory message.
I 40
D 73
**		returnto -- the queue of people to send the message to.
E 73
I 73
**		returnq -- the queue of people to send the message to.
E 73
E 40
I 33
**		sendbody -- if TRUE, also send back the body of the
**			message; otherwise just send the header.
I 92
**		e -- the current envelope.
E 92
E 33
**
**	Returns:
**		zero -- if everything went ok.
**		else -- some error.
**
**	Side Effects:
**		Returns the current message to the sender via
**		mail.
*/

D 38
static char	*ErrorMessage;
E 38
I 33
D 197
static bool	SendBody;
E 33

E 197
I 40
#define MAXRETURNS	6	/* max depth of returning messages */
I 114
#define ERRORFUDGE	100	/* nominal size of error message text */
E 114

I 211
int
E 211
E 40
D 33
returntosender(msg)
E 33
I 33
D 36
returntosender(msg, sendbody)
E 36
I 36
D 73
returntosender(msg, returnto, sendbody)
E 73
I 73
D 92
returntosender(msg, returnq, sendbody)
E 92
I 92
returntosender(msg, returnq, sendbody, e)
E 92
E 73
E 36
E 33
	char *msg;
I 36
D 73
	ADDRESS *returnto;
E 73
I 73
	ADDRESS *returnq;
E 73
E 36
I 33
	bool sendbody;
I 92
	register ENVELOPE *e;
E 92
E 33
{
D 40
	ADDRESS to_addr;
E 40
D 195
	char buf[MAXNAME];
E 195
I 195
D 211
	char buf[MAXNAME + 1];
E 195
D 44
	register int i;
E 44
D 36
	extern errhdr();
E 36
I 36
	extern putheader(), errbody();
E 211
	register ENVELOPE *ee;
I 117
	ENVELOPE *oldcur = CurEnv;
E 117
D 139
	extern ENVELOPE *newenvelope();
E 139
	ENVELOPE errenvelope;
I 40
	static int returndepth;
I 58
	register ADDRESS *q;
I 191
	char *p;
I 211
	char buf[MAXNAME + 1];
	extern void errbody __P((MCI *, ENVELOPE *, char *));
E 211
E 191
I 124

I 138
	if (returnq == NULL)
		return (-1);

E 138
	if (msg == NULL)
		msg = "Unable to deliver mail";
E 124
E 58
E 40
E 36

I 45
D 85
# ifdef DEBUG
E 85
D 48
	if (Debug > 0)
E 48
I 48
	if (tTd(6, 1))
E 48
	{
D 92
		printf("Return To Sender: msg=\"%s\", depth=%d, CurEnv=%x,\n",
		       msg, returndepth, CurEnv);
E 92
I 92
D 117
		printf("Return To Sender: msg=\"%s\", depth=%d, e=%x,\n",
E 117
I 117
D 183
		printf("Return To Sender: msg=\"%s\", depth=%d, e=%x, returnq=",
E 183
I 183
		printf("\n*** Return To Sender: msg=\"%s\", depth=%d, e=%x, returnq=",
E 183
E 117
		       msg, returndepth, e);
E 92
D 77
		printf("\treturnto=");
E 77
I 77
D 117
		printf("\treturnq=");
E 117
E 77
D 58
		printaddr(returnto, FALSE);
E 58
I 58
D 73
		printaddr(returnto, TRUE);
E 73
I 73
		printaddr(returnq, TRUE);
I 183
		if (tTd(6, 20))
		{
			printf("Sendq=");
			printaddr(e->e_sendqueue, TRUE);
		}
E 183
E 73
E 58
	}
D 85
# endif DEBUG
E 85

E 45
I 40
	if (++returndepth >= MAXRETURNS)
	{
		if (returndepth != MAXRETURNS)
D 73
			syserr("returntosender: infinite recursion on %s", returnto->q_paddr);
E 73
I 73
D 106
			syserr("returntosender: infinite recursion on %s", returnq->q_paddr);
E 106
I 106
			syserr("554 returntosender: infinite recursion on %s", returnq->q_paddr);
E 106
E 73
		/* don't "unrecurse" and fake a clean exit */
		/* returndepth--; */
		return (0);
	}

E 40
D 33
	(void) freopen("/dev/null", "w", stdout);
E 33
D 37
	NoAlias++;
E 37
I 37
D 58
	NoAlias = TRUE;
E 58
E 37
D 31
	ForceMail++;
E 31
D 36
	ErrorMessage = msg;
E 36
I 33
D 197
	SendBody = sendbody;
E 197
I 51
D 58
	define('g', "$f");
E 58
I 58
D 71
	define('g', "$f", CurEnv);
E 71
I 71
D 92
	define('g', "\001f", CurEnv);
I 89
	define('<', "\001f", CurEnv);
E 92
I 92
D 101
	define('g', "\001f", e);
	define('<', "\001f", e);
E 101
I 101
D 108
	define('g', "\201f", e);
	define('<', "\201f", e);
E 101
E 92
E 89
E 71
E 58
E 51
I 36
	ee = newenvelope(&errenvelope);
E 108
I 108
D 117
	define('g', e->e_sender, e);
	define('<', e->e_returnpath, e);
E 117
I 117
	define('g', e->e_from.q_paddr, e);
I 157
	define('u', NULL, e);
I 176

	/* initialize error envelope */
E 176
E 157
E 117
	ee = newenvelope(&errenvelope, e);
E 108
I 77
D 101
	define('a', "\001b", ee);
E 101
I 101
	define('a', "\201b", ee);
I 125
	define('r', "internal", ee);
	define('s', "localhost", ee);
	define('_', "localhost", ee);
E 125
E 101
E 77
	ee->e_puthdr = putheader;
	ee->e_putbody = errbody;
I 58
D 148
	ee->e_flags |= EF_RESPONSE;
E 148
I 148
	ee->e_flags |= EF_RESPONSE|EF_METOO;
E 148
I 88
D 92
	if (!bitset(EF_OLDSTYLE, CurEnv->e_flags))
E 92
I 92
	if (!bitset(EF_OLDSTYLE, e->e_flags))
E 92
		ee->e_flags &= ~EF_OLDSTYLE;
E 88
D 73
	ee->e_sendqueue = returnto;
E 73
I 73
	ee->e_sendqueue = returnq;
I 114
D 152
	ee->e_msgsize = e->e_msgsize + ERRORFUDGE;
E 152
I 152
	ee->e_msgsize = ERRORFUDGE;
D 172
	if (!NoReturn)
E 172
I 172
D 197
	if (!bitset(EF_NORETURN, e->e_flags))
E 197
I 197
	if (sendbody)
E 197
E 172
		ee->e_msgsize += e->e_msgsize;
I 203
	else
		ee->e_flags |= EF_NO_BODY_RETN;
E 203
E 152
E 114
E 73
E 58
I 53
D 57
	queuename(ee, '\0');
E 57
I 57
D 59
	(void) queuename(ee, '\0');
E 59
I 59
D 155
	openxscript(ee);
E 155
I 155
	initsys(ee);
E 155
E 59
E 57
E 53
D 54
	addheader("date", "$b", ee);
	addheader("from", "$g (Mail Delivery Subsystem)", ee);
E 54
D 58
	addheader("to", returnto->q_paddr, ee);
E 58
I 58
D 73
	for (q = returnto; q != NULL; q = q->q_next)
E 73
I 73
	for (q = returnq; q != NULL; q = q->q_next)
E 73
	{
I 114
D 137
		if (bitset(QDONTSEND, q->q_flags))
E 137
I 137
		if (bitset(QBADADDR, q->q_flags))
E 137
			continue;

D 137
		ee->e_nrcpts++;
E 137
I 137
D 190
		if (!bitset(QDONTSEND, q->q_flags))
			ee->e_nrcpts++;
E 137

E 190
E 114
I 105
		if (!DontPruneRoutes && pruneroute(q->q_paddr))
I 190
		{
			register ADDRESS *p;

E 190
D 113
			parseaddr(q->q_paddr, q, 0, '\0', e);
E 113
I 113
D 149
			parseaddr(q->q_paddr, q, 0, '\0', NULL, e);
E 149
I 149
			parseaddr(q->q_paddr, q, RF_COPYPARSE, '\0', NULL, e);
I 190
			for (p = returnq; p != NULL; p = p->q_next)
			{
				if (p != q && sameaddr(p, q))
					q->q_flags |= QDONTSEND;
			}
		}

		if (!bitset(QDONTSEND, q->q_flags))
			ee->e_nrcpts++;
E 190
E 149
E 113

E 105
		if (q->q_alias == NULL)
D 133
			addheader("to", q->q_paddr, ee);
E 133
I 133
D 173
			addheader("To", q->q_paddr, ee);
E 173
I 173
			addheader("To", q->q_paddr, &ee->e_header);
E 173
E 133
	}
I 77

I 98
# ifdef LOG
D 100
	if (LogLevel >= 3)
E 100
I 100
	if (LogLevel > 5)
E 100
D 160
		syslog(LOG_INFO, "%s: %s: return to sender: %s",
E 160
I 160
		syslog(LOG_INFO, "%s: %s: returntosender: %s",
E 160
			e->e_id, ee->e_id, msg);
# endif

E 98
E 77
E 58
D 63
	addheader("subject", msg, ee);
E 63
I 63
D 66
	(void) sprintf(buf, "MAIL FAILURE: %s", msg);
E 66
I 66
D 160
D 169
	(void) sprintf(buf, "Returned mail: %s", msg);
E 169
I 169
D 170
	(void) sprintf(buf, "Returned mail: %.*s", sizeof buf - 20, msg);
E 169
E 66
D 133
	addheader("subject", buf, ee);
E 133
I 133
	addheader("Subject", buf, ee);
E 170
I 170
D 171
	if (strncmp(msg, "Warning:", 8) == 0 ||
	    strcmp(msg, "Return receipt") == 0)
E 171
I 171
D 187
	if (strncmp(msg, "Warning:", 8) == 0)
E 187
I 187
	if (SendMIMEErrors)
E 187
E 171
	{
I 187
		addheader("MIME-Version", "1.0", &ee->e_header);
I 217

E 217
		(void) sprintf(buf, "%s.%ld/%s",
			ee->e_id, curtime(), MyHostName);
		ee->e_msgboundary = newstr(buf);
		(void) sprintf(buf,
I 188
D 205
#ifdef DSN
E 205
I 205
#if DSN
E 205
E 188
D 189
			"multipart/report; report-type=delivery-status; boundary=\"%s\"",
E 189
I 189
D 207
			"multipart/report; report-type=X-delivery-status-1; boundary=\"%s\"",
E 207
I 207
D 210
			"multipart/report; report-type=X-delivery-status-2 (draft of April 20, 1995);\n\tboundary=\"%s\"",
E 210
I 210
D 214
			"multipart/report; report-type=X-delivery-status-3 (Draft of May 5, 1995);\n\tboundary=\"%s\"",
E 214
I 214
			"multipart/report; report-type=X-delivery-status-03 (Draft of May 5, 1995);\n\tboundary=\"%s\"",
E 214
E 210
E 207
E 189
I 188
#else
			"multipart/mixed; boundary=\"%s\"",
#endif
E 188
			ee->e_msgboundary);
		addheader("Content-Type", buf, &ee->e_header);
I 217

		p = hvalue("Content-Transfer-Encoding", e->e_header);
		if (p != NULL && strcasecmp(p, "binary") != 0)
			p = NULL;
		if (p == NULL && bitset(EF_HAS8BIT, e->e_flags))
			p = "8bit";
		if (p != NULL)
			addheader("Content-Transfer-Encoding", p, &ee->e_header);
E 217
	}
D 191
	else if (strncmp(msg, "Warning:", 8) == 0)
E 191
I 191
	if (strncmp(msg, "Warning:", 8) == 0)
E 191
	{
E 187
D 209
		addheader("Subject", msg, ee);
E 209
I 209
		addheader("Subject", msg, &ee->e_header);
E 209
I 171
D 173
		addheader("Precedence", "autoreply warning-timeout", ee);
E 173
I 173
D 191
		addheader("Precedence", "autoreply warning-timeout", &ee->e_header);
E 191
I 191
		p = "warning-timeout";
E 191
E 173
E 171
	}
I 171
	else if (strcmp(msg, "Return receipt") == 0)
	{
D 209
		addheader("Subject", msg, ee);
E 209
I 209
		addheader("Subject", msg, &ee->e_header);
E 209
D 173
		addheader("Precedence", "autoreply return-receipt", ee);
E 173
I 173
D 191
		addheader("Precedence", "autoreply return-receipt", &ee->e_header);
E 191
I 191
		p = "return-receipt";
E 191
E 173
	}
E 171
	else
	{
		sprintf(buf, "Returned mail: %.*s", sizeof buf - 20, msg);
D 173
		addheader("Subject", buf, ee);
I 171
		addheader("Precedence", "autoreply failure-message", ee);
E 173
I 173
		addheader("Subject", buf, &ee->e_header);
D 191
		addheader("Precedence", "autoreply failure-message", &ee->e_header);
E 191
I 191
		p = "failure";
E 191
E 173
E 171
	}
I 191
	(void) sprintf(buf, "auto-generated (%s)", p);
	addheader("Auto-Submitted", buf, &ee->e_header);
E 191
E 170
E 160
I 160
	if (strncasecmp(msg, "warning:", 8) != 0)
	{
		(void) sprintf(buf, "Returned mail: %s", msg);
		msg = buf;
	}
	addheader("Subject", msg, ee);
E 160
I 134
D 187
	if (SendMIMEErrors)
	{
I 136
D 173
		addheader("MIME-Version", "1.0", ee);
E 173
I 173
		addheader("MIME-Version", "1.0", &ee->e_header);
E 173
E 136
		(void) sprintf(buf, "%s.%ld/%s",
			ee->e_id, curtime(), MyHostName);
		ee->e_msgboundary = newstr(buf);
D 176
		(void) sprintf(buf, "multipart/mixed; boundary=\"%s\"",
					ee->e_msgboundary);
E 176
I 176
		(void) sprintf(buf,
			"multipart/report; report-type=delivery-status; boundary=\"%s\"",
			ee->e_msgboundary);
E 176
D 173
		addheader("Content-Type", buf, ee);
E 173
I 173
		addheader("Content-Type", buf, &ee->e_header);
E 173
	}
E 187
E 134
E 133
E 63
E 36
E 33

	/* fake up an address header for the from person */
D 34
	bmove((char *) &From, (char *) &to_addr, sizeof to_addr);
E 34
I 34
D 36
	bmove((char *) &CurEnv->e_from, (char *) &to_addr, sizeof to_addr);
E 34
	(void) expand("$n", buf, &buf[sizeof buf - 1]);
D 34
	if (parse(buf, &From, -1) == NULL)
E 34
I 34
	if (parse(buf, &CurEnv->e_from, -1) == NULL)
E 36
I 36
D 40
	bmove((char *) returnto, (char *) &to_addr, sizeof to_addr);
E 40
D 71
	expand("$n", buf, &buf[sizeof buf - 1], CurEnv);
E 71
I 71
D 92
	expand("\001n", buf, &buf[sizeof buf - 1], CurEnv);
E 92
I 92
D 101
	expand("\001n", buf, &buf[sizeof buf - 1], e);
E 101
I 101
D 196
	expand("\201n", buf, &buf[sizeof buf - 1], e);
E 196
I 196
	expand("\201n", buf, sizeof buf, e);
E 196
E 101
E 92
I 90
D 103
	ee->e_sender = ee->e_returnpath = newstr(buf);
E 103
I 103
D 104
	ee->e_returnpath = "<>";
E 104
D 117
	ee->e_sender = newstr(buf);
I 104
	if (ConfigLevel >= 4)
		ee->e_returnpath = "<>";
	else
		ee->e_returnpath = ee->e_sender;
E 104
E 103
E 90
E 71
D 61
	if (parse(buf, &ee->e_from, -1) == NULL)
E 61
I 61
D 68
	if (parseaddr(buf, &ee->e_from, -1) == NULL)
E 68
I 68
D 92
	if (parseaddr(buf, &ee->e_from, -1, '\0') == NULL)
E 92
I 92
D 113
	if (parseaddr(buf, &ee->e_from, -1, '\0', e) == NULL)
E 113
I 113
	if (parseaddr(buf, &ee->e_from, -1, '\0', NULL, e) == NULL)
E 117
I 117
D 149
	if (parseaddr(buf, &ee->e_from, 1, '\0', NULL, e) == NULL)
E 149
I 149
	if (parseaddr(buf, &ee->e_from, RF_COPYALL|RF_SENDERADDR, '\0', NULL, e) == NULL)
E 149
E 117
E 113
E 92
E 68
E 61
E 36
E 34
	{
D 106
		syserr("Can't parse myself!");
E 106
I 106
		syserr("553 Can't parse myself!");
E 106
		ExitStat = EX_SOFTWARE;
I 40
		returndepth--;
E 40
		return (-1);
	}
I 118
	ee->e_sender = ee->e_from.q_paddr;
E 118
I 72
D 116
	loweraddr(&ee->e_from);
E 116
E 72
D 40
	to_addr.q_next = NULL;
I 33
	to_addr.q_flags &= ~QDONTSEND;
E 33
D 36
	i = deliver(&to_addr, errhdr);
D 34
	bmove((char *) &to_addr, (char *) &From, sizeof From);
E 34
I 34
	bmove((char *) &to_addr, (char *) &CurEnv->e_from, sizeof CurEnv->e_from);
E 36
I 36
	ee->e_sendqueue = &to_addr;
E 40
I 40
D 58
	ee->e_sendqueue = returnto;
E 58
E 40
E 36
E 34
I 33

D 34
	/* if From was queued up, put in on SendQueue */
	if (bitset(QQUEUEUP, From.q_flags))
E 34
I 34
D 36
	/* if CurEnv->e_from was queued up, put in on CurEnv->e_sendqueue */
	if (bitset(QQUEUEUP, CurEnv->e_from.q_flags))
E 34
	{
D 34
		From.q_next = SendQueue;
		SendQueue = &From;
E 34
I 34
		CurEnv->e_from.q_next = CurEnv->e_sendqueue;
		CurEnv->e_sendqueue = &CurEnv->e_from;
E 34
	}
E 36
I 36
	/* push state into submessage */
	CurEnv = ee;
D 58
	define('f', "$n");
	define('x', "Mail Delivery Subsystem");
E 58
I 58
D 71
	define('f', "$n", ee);
E 71
I 71
D 101
	define('f', "\001n", ee);
E 101
I 101
	define('f', "\201n", ee);
E 101
E 71
	define('x', "Mail Delivery Subsystem", ee);
I 67
D 98
	eatheader(ee);
E 98
I 98
D 121
	eatheader(ee, FALSE);
E 121
I 121
D 123
	eatheader(ee);
E 123
I 123
	eatheader(ee, TRUE);
E 123
E 121
E 98
E 67
E 58
E 36

I 141
	/* mark statistics */
D 149
	markstats(ee, (ADDRESS *) NULL);
E 149
I 149
	markstats(ee, NULLADDR);
E 149

E 141
I 36
	/* actually deliver the error message */
D 40
	i = deliver(&to_addr);
E 40
I 40
D 55
	sendall(ee, FALSE);
E 55
I 55
D 70
	sendall(ee, SendMode);
E 70
I 70
	sendall(ee, SM_DEFAULT);
E 70
E 55
E 40

D 40
	/* if the error message was "queued", make that happen */
	if (bitset(QQUEUEUP, to_addr.q_flags))
D 38
		queueup(ee);
E 38
I 38
		queueup(ee, FALSE);
E 40
I 40
D 58
	/* do any closing error processing */
	checkerrors(ee);
E 40
E 38

E 58
	/* restore state */
I 49
	dropenvelope(ee);
E 49
D 117
	CurEnv = CurEnv->e_parent;
E 117
I 117
	CurEnv = oldcur;
E 117
I 40
	returndepth--;
E 40

E 36
E 33
D 40
	if (i != 0)
	{
D 34
		syserr("Can't return mail to %s", From.q_paddr);
E 34
I 34
D 36
		syserr("Can't return mail to %s", CurEnv->e_from.q_paddr);
E 36
I 36
		syserr("Can't return mail to %s", to_addr.q_paddr);
E 36
E 34
		return (-1);
	}
E 40
I 40
D 219
	/* should check for delivery errors here */
E 40
	return (0);
E 219
I 219
	/* check for delivery errors */
	if (ee->e_parent == NULL || !bitset(EF_RESPONSE, ee->e_parent->e_flags))
		return 0;
	for (q = ee->e_sendqueue; q != NULL; q = q->q_next)
	{
		if (bitset(QSENT, q->q_flags))
			return 0;
	}
	return -1;
E 219
}
/*
E 27
D 36
**  ERRHDR -- Output the header for error mail.
E 36
I 36
D 38
**  ERRHEADER -- Output the header for error mail.
E 36
**
D 36
**	This is the edit filter to error mailbacks.
E 36
I 36
**	Parameters:
**		xfile -- the transcript file.
**		fp -- the output file.
E 36
**
I 36
**	Returns:
**		none
**
**	Side Effects:
**		Outputs the header for an error message.
*/

errheader(fp, m)
	register FILE *fp;
	register struct mailer *m;
{
	/*
	**  Output header of error message.
	*/

	putheader(fp, m);
}
/*
E 38
**  ERRBODY -- output the body of an error message.
**
**	Typically this is a copy of the transcript plus a copy of the
**	original offending message.
**
E 36
D 27
**	Algorithm:
**		Output fixed header.
**		Output the transcript part.
**		Output the original message.
**
E 27
**	Parameters:
D 64
**		xfile -- the transcript file.
E 64
D 165
**		fp -- the output file.
I 29
D 36
**		xdot -- if set, use smtp hidden dot algorithm.
E 36
I 36
D 64
**		xdot -- if set, use the SMTP hidden dot algorithm.
E 64
I 64
**		m -- the mailer to output to.
E 165
I 165
**		mci -- the mailer connection information.
E 165
E 64
I 59
**		e -- the envelope we are working in.
I 173
**		separator -- any possible MIME separator.
I 177
**		flags -- to modify the behaviour.
E 177
E 173
I 62
D 64
**		crlf -- set if we want CRLF's at the end of lines.
E 64
E 62
E 59
E 36
E 29
**
**	Returns:
**		none
**
**	Side Effects:
D 27
**		input from xfile
**		output to fp
**
D 4
**	Requires:
**		read (sys)
**		write (sys)
**		open (sys)
**		close (sys)
**		syserr
**		rewind (sys)
**		fflush (sys)
**		fprintf (sys)
**		fileno (sys)
**
E 4
**	Called By:
**		deliver
E 27
I 27
D 36
**		Outputs the current message with an appropriate
**		error header.
E 36
I 36
**		Outputs the body of an error message.
E 36
E 27
D 4
**
**	History:
**		12/28/79 -- written.
E 4
*/

I 211
void
E 211
D 27

E 27
D 23
errhdr(fp)
E 23
I 23
D 29
errhdr(fp, m)
E 29
I 29
D 36
errhdr(fp, m, xdot)
E 36
I 36
D 59
errbody(fp, m, xdot)
E 59
I 59
D 62
errbody(fp, m, xdot, e)
E 62
I 62
D 64
errbody(fp, m, xdot, e, crlf)
E 64
I 64
D 165
errbody(fp, m, e)
E 64
E 62
E 59
E 36
E 29
E 23
	register FILE *fp;
I 23
	register struct mailer *m;
E 165
I 165
D 173
errbody(mci, e)
E 173
I 173
D 177
errbody(mci, e, separator)
E 177
I 177
D 191
errbody(mci, e, separator, flags)
E 191
I 191
errbody(mci, e, separator)
E 191
E 177
E 173
	register MCI *mci;
E 165
I 29
D 64
	bool xdot;
E 64
I 59
	register ENVELOPE *e;
I 173
	char *separator;
E 173
I 62
D 64
	bool crlf;
E 64
E 62
E 59
E 29
E 23
{
D 11
	char copybuf[512];
	register int i;
	register int xfile;
E 11
I 11
D 36
	char buf[MAXLINE];
E 36
	register FILE *xfile;
I 25
D 36
	extern char *macvalue();
	char *oldfmac;
	char *oldgmac;
E 36
I 36
D 126
	char buf[MAXLINE];
E 126
I 42
D 64
	bool fullsmtp = bitset(M_FULLSMTP, m->m_flags);
E 64
I 56
	char *p;
I 126
	register ADDRESS *q;
	bool printheader;
I 197
	bool sendbody;
E 197
I 177
D 191
	int pflags = flags;
E 191
E 177
	char buf[MAXLINE];
I 191
D 214
	extern char *xtextify();
E 214
I 214
	extern char *xuntextify();
E 214
E 191
E 126
E 56
E 42
E 36
E 25
E 11
D 16
	extern int errno;
E 16

I 173
	if (bitset(MCIF_INHEADER, mci->mci_flags))
	{
		putline("", mci);
		mci->mci_flags &= ~MCIF_INHEADER;
	}
E 173
I 117
	if (e->e_parent == NULL)
	{
		syserr("errbody: null parent");
D 134
		putline("\n", fp, m);
E 134
D 165
		putline("   ----- Original message lost -----\n", fp, m);
E 165
I 165
		putline("   ----- Original message lost -----\n", mci);
E 165
		return;
	}

E 117
I 54
	/*
I 134
	**  Output MIME header.
	*/

	if (e->e_msgboundary != NULL)
	{
D 165
		putline("This is a MIME-encapsulated message", fp, m);
		putline("", fp, m);
E 165
I 165
		putline("This is a MIME-encapsulated message", mci);
		putline("", mci);
E 165
		(void) sprintf(buf, "--%s", e->e_msgboundary);
D 165
		putline(buf, fp, m);
		putline("", fp, m);
E 165
I 165
		putline(buf, mci);
		putline("", mci);
E 165
	}

	/*
I 145
	**  Output introductory information.
	*/

D 153
	sprintf(buf, "The original message was received at %s", arpadate(NULL));
E 153
I 153
	for (q = e->e_parent->e_sendqueue; q != NULL; q = q->q_next)
		if (bitset(QBADADDR, q->q_flags))
			break;
D 154
	if (q == NULL)
E 154
I 154
D 161
	if (q == NULL && !bitset(EF_FATALERRS, e->e_parent->e_flags))
E 161
I 161
	if (q == NULL &&
	    !bitset(EF_FATALERRS|EF_SENDRECEIPT, e->e_parent->e_flags))
E 161
E 154
	{
		putline("    **********************************************",
D 165
			fp, m);
E 165
I 165
			mci);
E 165
		putline("    **      THIS IS A WARNING MESSAGE ONLY      **",
D 165
			fp, m);
E 165
I 165
			mci);
E 165
		putline("    **  YOU DO NOT NEED TO RESEND YOUR MESSAGE  **",
D 165
			fp, m);
E 165
I 165
			mci);
E 165
		putline("    **********************************************",
D 165
			fp, m);
		putline("", fp, m);
E 165
I 165
			mci);
		putline("", mci);
E 165
	}
	sprintf(buf, "The original message was received at %s",
		arpadate(ctime(&e->e_parent->e_ctime)));
E 153
D 165
	putline(buf, fp, m);
E 165
I 165
	putline(buf, mci);
E 165
D 147
	expand("from \201_", buf, &buf[sizeof buf - 1], e);
E 147
I 147
D 196
	expand("from \201_", buf, &buf[sizeof buf - 1], e->e_parent);
E 196
I 196
	expand("from \201_", buf, sizeof buf, e->e_parent);
E 196
E 147
D 165
	putline(buf, fp, m);
	putline("", fp, m);
E 165
I 165
	putline(buf, mci);
	putline("", mci);
E 165

	/*
E 145
E 134
I 93
	**  Output error message header (if specified and available).
	*/

D 174
	if (ErrMsgFile != NULL)
E 174
I 174
	if (ErrMsgFile != NULL && !bitset(EF_SENDRECEIPT, e->e_parent->e_flags))
E 174
	{
		if (*ErrMsgFile == '/')
		{
			xfile = fopen(ErrMsgFile, "r");
			if (xfile != NULL)
			{
				while (fgets(buf, sizeof buf, xfile) != NULL)
I 94
				{
D 196
					expand(buf, buf, &buf[sizeof buf - 1], e);
E 196
I 196
					expand(buf, buf, sizeof buf, e);
E 196
E 94
D 165
					putline(buf, fp, m);
E 165
I 165
					putline(buf, mci);
E 165
I 94
				}
E 94
				(void) fclose(xfile);
D 126
				fprintf(fp, "\n");
E 126
I 126
D 165
				putline("\n", fp, m);
E 165
I 165
				putline("\n", mci);
E 165
E 126
			}
		}
		else
		{
D 94
			putline(ErrMsgFile, fp, m);
E 94
I 94
D 196
			expand(ErrMsgFile, buf, &buf[sizeof buf - 1], e);
E 196
I 196
			expand(ErrMsgFile, buf, sizeof buf, e);
E 196
D 165
			putline(buf, fp, m);
E 94
D 126
			fprintf(fp, "\n");
E 126
I 126
D 134
			putline("\n", fp, m);
E 134
I 134
			putline("", fp, m);
E 165
I 165
			putline(buf, mci);
			putline("", mci);
E 165
E 134
E 126
		}
	}

	/*
I 126
	**  Output message introduction
	*/

	printheader = TRUE;
	for (q = e->e_parent->e_sendqueue; q != NULL; q = q->q_next)
	{
D 142
		if (bitset(QBADADDR, q->q_flags))
E 142
I 142
D 181
		if (bitset(QBADADDR|QREPORT, q->q_flags))
E 181
I 181
D 200
		if (bitset(QBADADDR|QREPORT|QRELAYED, q->q_flags))
E 200
I 200
D 208
		if (bitset(QBADADDR|QREPORT|QRELAYED|QEXPLODED, q->q_flags))
E 208
I 208
		if (bitset(QBADADDR, q->q_flags))
E 208
E 200
E 181
E 142
		{
D 200
			if (printheader)
			{
D 134
				putline("The following addresses failed:\n",
E 134
I 134
D 142
				putline("   ----- The following addresses failed -----",
E 142
I 142
D 176
				putline("   ----- The following addresses had delivery problems -----",
E 176
I 176
				putline("   ----- The following addresses have delivery notifications -----",
E 176
E 142
E 134
D 165
					fp, m);
E 165
I 165
					mci);
E 165
				printheader = FALSE;
			}
E 200
D 129
			sprintf(buf, "\t%s\n", q->q_paddr);
E 129
I 129
D 144
			if (q->q_alias != NULL)
D 134
				sprintf(buf, "\t%s\n", q->q_alias->q_paddr);
E 134
I 134
D 142
				putline(q->q_alias->q_paddr, fp, m);
E 142
I 142
				strcpy(buf, q->q_alias->q_paddr);
E 142
E 134
			else
D 134
				sprintf(buf, "\t%s\n", q->q_paddr);
E 129
			putline(buf, fp, m);
E 134
I 134
D 142
				putline(q->q_paddr, fp, m);
E 142
I 142
				strcpy(buf, q->q_paddr);
E 144
I 144
D 208
			strcpy(buf, q->q_paddr);
E 144
			if (bitset(QBADADDR, q->q_flags))
D 144
				strcat(buf, "  (hard error -- address deleted)");
E 144
I 144
				strcat(buf, "  (unrecoverable error)");
I 200
			else if (!bitset(QPRIMARY, q->q_flags))
E 208
I 208
			if (!bitset(QPINGONFAILURE, q->q_flags))
E 208
				continue;
E 200
I 181
D 208
			else if (bitset(QRELAYED, q->q_flags))
				strcat(buf, "  (relayed to non-DSN-aware mailer)");
E 181
I 176
			else if (bitset(QSENT, q->q_flags))
				strcat(buf, "  (successfully delivered)");
I 200
			else if (bitset(QEXPLODED, q->q_flags))
				strcat(buf, "  (expanded by mailing list)");
E 208
I 208
			p = "unrecoverable error";
		}
		else if (!bitset(QPRIMARY, q->q_flags))
			continue;
		else if (bitset(QRELAYED, q->q_flags))
			p = "relayed to non-DSN-aware mailer";
		else if (bitset(QDELIVERED, q->q_flags))
		{
			if (bitset(QEXPANDED, q->q_flags))
				p = "successfully delivered to mailing list";
E 208
E 200
E 176
E 144
			else
D 144
				strcat(buf, "  (temporary failure -- will retry)");
E 144
I 144
D 208
				strcat(buf, "  (transient failure)");
I 200
			if (printheader)
			{
				putline("   ----- The following addresses have delivery notifications -----",
					mci);
				printheader = FALSE;
			}
E 208
I 208
				p = "successfully delivered to mailbox";
		}
		else if (bitset(QEXPANDED, q->q_flags))
			p = "expanded by alias";
		else if (bitset(QDELAYED, q->q_flags))
			p = "transient failure";
		else
			continue;

		if (printheader)
		{
			putline("   ----- The following addresses have delivery notifications -----",
				mci);
			printheader = FALSE;
		}

		sprintf(buf, "%s  (%s)", q->q_paddr, p);
		putline(buf, mci);
		if (q->q_alias != NULL)
		{
			strcpy(buf, "    (expanded from: ");
			strcat(buf, q->q_alias->q_paddr);
			strcat(buf, ")");
E 208
E 200
E 144
D 165
			putline(buf, fp, m);
E 165
I 165
			putline(buf, mci);
E 165
I 144
D 208
			if (q->q_alias != NULL)
			{
				strcpy(buf, "    (expanded from: ");
				strcat(buf, q->q_alias->q_paddr);
				strcat(buf, ")");
D 165
				putline(buf, fp, m);
E 165
I 165
				putline(buf, mci);
E 165
			}
E 208
E 144
E 142
E 134
		}
	}
	if (!printheader)
D 165
		putline("\n", fp, m);
E 165
I 165
		putline("\n", mci);
E 165

	/*
E 126
E 93
	**  Output transcript of errors
	*/

E 54
I 25
D 36
	oldfmac = macvalue('f');
	define('f', "$n");
	oldgmac = macvalue('g');
	define('g', m->m_from);

E 36
E 25
D 11
	if ((xfile = open(Transcript, 0)) < 0)
		syserr("Cannot open %s", Transcript);
E 11
D 16
	fflush(stdout);
E 16
I 16
	(void) fflush(stdout);
I 28
D 36
	(void) fflush(Xscript);
E 36
E 28
E 16
I 11
D 56
	if ((xfile = fopen(Transcript, "r")) == NULL)
E 56
I 56
D 59
	p = queuename(CurEnv->e_parent, 'x');
E 59
I 59
	p = queuename(e->e_parent, 'x');
E 59
	if ((xfile = fopen(p, "r")) == NULL)
E 56
I 54
	{
E 54
D 56
		syserr("Cannot open %s", Transcript);
E 56
I 56
		syserr("Cannot open %s", p);
E 56
I 54
D 117
		fprintf(fp, "  ----- Transcript of session is unavailable -----\n");
E 117
I 117
D 126
		putline("  ----- Transcript of session is unavailable -----\n", fp, m);
E 126
I 126
D 165
		putline("   ----- Transcript of session is unavailable -----\n", fp, m);
E 165
I 165
		putline("   ----- Transcript of session is unavailable -----\n", mci);
E 165
E 126
E 117
	}
	else
	{
D 117
		fprintf(fp, "   ----- Transcript of session follows -----\n");
E 117
I 117
D 165
		putline("   ----- Transcript of session follows -----\n", fp, m);
E 165
I 165
D 208
		putline("   ----- Transcript of session follows -----\n", mci);
E 208
I 208
		printheader = TRUE;
E 208
E 165
E 117
D 56
		(void) fflush(Xscript);
E 56
I 56
D 59
		if (Xscript != NULL)
			(void) fflush(Xscript);
E 59
I 59
		if (e->e_xfp != NULL)
			(void) fflush(e->e_xfp);
E 59
E 56
		while (fgets(buf, sizeof buf, xfile) != NULL)
I 208
		{
			if (printheader)
				putline("   ----- Transcript of session follows -----\n", mci);
			printheader = FALSE;
E 208
D 62
			putline(buf, fp, fullsmtp);
E 62
I 62
D 64
			putline(buf, fp, crlf, fullsmtp);
E 64
I 64
D 165
			putline(buf, fp, m);
E 165
I 165
			putline(buf, mci);
I 208
		}
E 208
E 165
E 64
E 62
D 117
		(void) fclose(xfile);
E 117
I 117
		(void) xfclose(xfile, "errbody xscript", p);
E 117
	}
E 54
E 11
	errno = 0;
I 23

I 188
D 205
#ifdef DSN
E 205
I 205
#if DSN
E 205
E 188
	/*
I 176
	**  Output machine-readable version.
	*/

	if (e->e_msgboundary != NULL)
	{
		putline("", mci);
		(void) sprintf(buf, "--%s", e->e_msgboundary);
		putline(buf, mci);
D 189
		putline("Content-Type: message/delivery-status", mci);
E 189
I 189
D 191
		putline("Content-Type: message/X-delivery-status-1", mci);
E 191
I 191
D 201
		putline("Content-Type: message/X-delivery-status-2 (Draft of 20 January 1995)", mci);
E 201
I 201
D 208
		putline("Content-Type: message/X-delivery-status-04 (Draft of 20 January 1995)", mci);
E 208
I 208
D 210
		putline("Content-Type: message/X-delivery-status-04a (Draft of 04 April 1995)", mci);
E 210
I 210
D 214
		putline("Content-Type: message/X-delivery-status-04a (Draft of April 4, 1995)", mci);
E 214
I 214
		putline("Content-Type: message/X-delivery-status-05 (Draft of May 29, 1995)", mci);
E 214
E 210
E 208
E 201
E 191
E 189
		putline("", mci);

		/*
		**  Output per-message information.
		*/

D 180
		/* Original-MTS-Type: is optional */
E 180
I 180
D 191
		/* OMTS from MAIL FROM: line */
		if (e->e_parent->e_omts != NULL)
		{
			(void) sprintf(buf, "Original-MTS-Type: %s",
				e->e_parent->e_omts);
			putline(buf, mci);
		}
E 180

E 191
		/* original envelope id from MAIL FROM: line */
		if (e->e_parent->e_envid != NULL)
		{
			(void) sprintf(buf, "Original-Envelope-Id: %s",
D 191
				e->e_parent->e_envid);
E 191
I 191
D 214
				xtextify(e->e_parent->e_envid));
E 214
I 214
				xuntextify(e->e_parent->e_envid));
E 214
E 191
			putline(buf, mci);
		}

D 180
		/* Final-MTS-Type: is optional (always INET?) */
E 180
I 180
D 191
		/* Final-MTS-Type: is required -- our type */
D 185
		putline("Final-MTS-Type: Internet", mci);
E 185
I 185
		if (e->e_parent->e_from.q_mailer->m_mtstype == NULL)
			putline("Final-MTS-Type: Internet", mci);
		else
		{
			(void) sprintf(buf, "Final-MTS-Type: %s",
				e->e_parent->e_from.q_mailer->m_mtstype);
			putline(buf, mci);
		}
E 185
E 180

		/* Final-MTA: seems silly -- this is in the From: line */
		(void) sprintf(buf, "Final-MTA: %s", MyHostName);
E 191
I 191
		/* Reporting-MTA: is us (required) */
D 208
		p = e->e_parent->e_from.q_mailer->m_mtatype;
		if (p == NULL)
			p = "dns";
D 199
		(void) sprintf(buf, "Reporting-MTA: %s; %s", p, MyHostName);
E 199
I 199
		(void) sprintf(buf, "Reporting-MTA: %s; %s", p,
E 208
I 208
D 214
		(void) sprintf(buf, "Reporting-MTA: dns; %s",
E 208
			xtextify(MyHostName));
E 214
I 214
		(void) sprintf(buf, "Reporting-MTA: dns; %s", MyHostName);
E 214
E 199
E 191
		putline(buf, mci);

I 208
		/* DSN-Gateway: not relevant since we are not translating */

E 208
I 180
D 191
		/* Received-From: shows where we got this message from */
E 191
I 191
		/* Received-From-MTA: shows where we got this message from */
E 191
D 184
		expand("Received-From: \201_", buf, &buf[sizeof buf - 1],
				e->e_parent);
		putline(buf, mci);
E 184
I 184
		if (RealHostName != NULL)
		{
D 191
			(void) sprintf(buf, "Received-From: %s", RealHostName);
E 191
I 191
			/* XXX use $s for type? */
			p = e->e_parent->e_from.q_mailer->m_mtatype;
			if (p == NULL)
				p = "dns";
			(void) sprintf(buf, "Received-From-MTA: %s; %s",
D 199
				p, RealHostName);
E 199
I 199
D 214
				p, xtextify(RealHostName));
E 214
I 214
				p, RealHostName);
E 214
E 199
E 191
			putline(buf, mci);
		}
E 184

		/* Arrival-Date: -- when it arrived here */
		(void) sprintf(buf, "Arrival-Date: %s",
			arpadate(ctime(&e->e_parent->e_ctime)));
		putline(buf, mci);

E 180
		/*
		**  Output per-address information.
		*/

		for (q = e->e_parent->e_sendqueue; q != NULL; q = q->q_next)
		{
			register ADDRESS *r;
I 200
			char *action;
E 200

D 200
			if (!bitset(QBADADDR|QREPORT|QRELAYED, q->q_flags))
E 200
I 200
			if (bitset(QBADADDR, q->q_flags))
D 208
				action = "failure";
E 208
I 208
				action = "failed";
E 208
			else if (!bitset(QPRIMARY, q->q_flags))
E 200
				continue;
I 208
			else if (bitset(QDELIVERED, q->q_flags))
			{
				if (bitset(QEXPANDED, q->q_flags))
					action = "delivered (to mailing list)";
				else
					action = "delivered (to mailbox)";
			}
E 208
I 200
			else if (bitset(QRELAYED, q->q_flags))
D 208
				action = "relayed";
			else if (bitset(QEXPLODED, q->q_flags))
				action = "delivered (to mailing list)";
			else if (bitset(QSENT, q->q_flags) &&
				 bitnset(M_LOCALMAILER, q->q_mailer->m_flags))
				action = "delivered (final delivery)";
			else if (bitset(QREPORT, q->q_flags))
E 208
I 208
				action = "relayed (to non-DSN-aware mailer)";
			else if (bitset(QEXPANDED, q->q_flags))
				action = "expanded (to multi-recipient alias)";
			else if (bitset(QDELAYED, q->q_flags))
E 208
				action = "delayed";
			else
				continue;

E 200
			putline("", mci);

D 180
			/* Rcpt: -- the name from the RCPT command */
E 180
I 180
D 186
			/* Recipient: -- the name from the RCPT command */
E 180
			for (r = q; r->q_alias != NULL; r = r->q_alias)
				continue;
D 180
			(void) sprintf(buf, "Rcpt: %s", r->q_paddr);
E 180
I 180
			(void) sprintf(buf, "Recipient: %s", r->q_paddr);
E 186
I 186
D 191
			/* Recipient: -- use name of alias */
			r = q;
			if (r->q_alias != NULL)
				r = r->q_alias;
			p = r->q_user;
			if (strchr(p, '@') == NULL)
				(void) sprintf(buf, "Recipient: %s@%s",
					p, MyHostName);
E 191
I 191
			/* Original-Recipient: -- passed from on high */
			if (q->q_orcpt != NULL)
			{
				(void) sprintf(buf, "Original-Recipient: %s",
D 214
					xtextify(q->q_orcpt));
E 214
I 214
					q->q_orcpt);
E 214
				putline(buf, mci);
			}

			/* Final-Recipient: -- the name from the RCPT command */
			p = e->e_parent->e_from.q_mailer->m_addrtype;
			if (p == NULL)
				p = "rfc822";
			for (r = q; r->q_alias != NULL; r = r->q_alias)
				continue;
			if (strchr(r->q_user, '@') == NULL)
D 199
				(void) sprintf(buf, "Final-Recipient: %s; %s@%s",
					p, xtextify(r->q_user), MyHostName);
E 199
I 199
			{
				(void) sprintf(buf, "Final-Recipient: %s; %s@",
D 214
					p, xtextify(r->q_user));
				strcat(buf, xtextify(MyHostName));
E 214
I 214
					p, r->q_user);
				strcat(buf, MyHostName);
E 214
			}
E 199
E 191
			else
I 199
			{
E 199
D 191
				(void) sprintf(buf, "Recipient: %s",
					p);
E 191
I 191
				(void) sprintf(buf, "Final-Recipient: %s; %s",
D 214
					p, xtextify(r->q_user));
E 214
I 214
					p, r->q_user);
E 214
I 199
			}
E 199
E 191
E 186
E 180
			putline(buf, mci);

I 200
			/* X-Actual-Recipient: -- the real problem address */
D 216
			if (r != q)
E 216
I 216
			if (r != q && q->q_user[0] != '\0')
E 216
			{
				if (strchr(q->q_user, '@') == NULL)
				{
					(void) sprintf(buf, "X-Actual-Recipient: %s; %s@",
D 214
						p, xtextify(q->q_user));
					strcat(buf, xtextify(MyHostName));
E 214
I 214
						p, q->q_user);
					strcat(buf, MyHostName);
E 214
				}
				else
				{
					(void) sprintf(buf, "X-Actual-Recipient: %s; %s",
D 214
						p, xtextify(q->q_user));
E 214
I 214
						p, q->q_user);
E 214
				}
				putline(buf, mci);
			}

E 200
			/* Action: -- what happened? */
D 200
			if (bitset(QBADADDR, q->q_flags))
D 191
				putline("Action: failed", mci);
E 191
I 191
				putline("Action: failure", mci);
E 191
			else if (bitset(QQUEUEUP, q->q_flags))
				putline("Action: delayed", mci);
			else if (bitset(QRELAYED, q->q_flags))
				putline("Action: relayed", mci);
			else
				putline("Action: delivered", mci);
E 200
I 200
			sprintf(buf, "Action: %s", action);
			putline(buf, mci);
E 200

			/* Status: -- what _really_ happened? */
			strcpy(buf, "Status: ");
I 186
D 191
			if (q->q_status == NULL)
				q->q_status = q->q_fstatus;
E 191
E 186
			if (q->q_status != NULL)
				strcat(buf, q->q_status);
I 184
D 186
			else if (q->q_fstatus != NULL)
				strcat(buf, q->q_fstatus);
E 186
E 184
			else if (bitset(QBADADDR, q->q_flags))
D 191
				strcat(buf, "500");
E 191
I 191
				strcat(buf, "5.0.0");
E 191
			else if (bitset(QQUEUEUP, q->q_flags))
D 191
				strcat(buf, "400");
E 191
I 191
				strcat(buf, "4.0.0");
E 191
D 200
			else if (bitset(QRELAYED, q->q_flags))
D 191
				strcat(buf, "601");
E 191
I 191
				strcat(buf, "6.0.1");
E 200
E 191
			else
D 191
				strcat(buf, "200");
E 191
I 191
				strcat(buf, "2.0.0");
E 191
			putline(buf, mci);

D 191
			/* Date: -- fine granularity */
E 191
I 191
			/* Remote-MTA: -- who was I talking to? */
			p = q->q_mailer->m_mtatype;
			if (p == NULL)
				p = "dns";
			(void) sprintf(buf, "Remote-MTA: %s; ", p);
			if (q->q_statmta != NULL)
				p = q->q_statmta;
D 200
			else if (q->q_host != NULL)
E 200
I 200
			else if (q->q_host != NULL && q->q_host[0] != '\0')
E 200
				p = q->q_host;
			else
				p = NULL;
			if (p != NULL)
			{
				strcat(buf, p);
				p = &buf[strlen(buf) - 1];
				if (*p == '.')
					*p = '\0';
				putline(buf, mci);
			}

			/* Diagnostic-Code: -- actual result from other end */
			if (q->q_rstatus != NULL)
			{
				p = q->q_mailer->m_diagtype;
				if (p == NULL)
					p = "smtp";
				(void) sprintf(buf, "Diagnostic-Code: %s; %s",
D 199
					p, q->q_rstatus);
E 199
I 199
D 200
					p, xtextify(q->q_rstatus));
E 200
I 200
D 208
					p, q->q_rstatus);
E 208
I 208
D 214
					p, xtextify(q->q_rstatus));
E 214
I 214
					p, q->q_rstatus);
E 214
E 208
E 200
E 199
				putline(buf, mci);
			}

			/* Last-Attempt-Date: -- fine granularity */
E 191
			if (q->q_statdate == (time_t) 0L)
				q->q_statdate = curtime();
D 191
			(void) sprintf(buf, "Date: %s",
E 191
I 191
			(void) sprintf(buf, "Last-Attempt-Date: %s",
E 191
				arpadate(ctime(&q->q_statdate)));
			putline(buf, mci);

D 191
			/* Final-Log-Id: -- why isn't this per-message? */
			(void) sprintf(buf, "Final-Log-Id: %s", e->e_id);
			putline(buf, mci);
I 180

E 191
D 208
			/* Expiry-Date: -- for delayed messages only */
E 208
I 208
			/* Will-Retry-Until: -- for delayed messages only */
E 208
			if (bitset(QQUEUEUP, q->q_flags) &&
			    !bitset(QBADADDR, q->q_flags))
			{
				time_t xdate;

				xdate = e->e_ctime + TimeOuts.to_q_return[e->e_timeoutclass];
D 208
				sprintf(buf, "Expiry-Date: %s",
E 208
I 208
				sprintf(buf, "Will-Retry-Until: %s",
E 208
					arpadate(ctime(&xdate)));
				putline(buf, mci);
			}
E 180
D 191

D 184
			/* Original-Rcpt: -- passed from on high */
E 184
I 184
			/* Original-Recipient: -- passed from on high */
E 184
			if (q->q_orcpt != NULL)
			{
D 184
				(void) sprintf(buf, "Original-Rcpt: %s",
E 184
I 184
				(void) sprintf(buf, "Original-Recipient: %s",
E 184
					q->q_orcpt);
				putline(buf, mci);
			}

D 184
			/* Final-Rcpt: -- if through alias */
E 184
I 184
D 186
			/* Final-Recipient: -- if through alias */
E 184
			if (q->q_alias != NULL)
			{
D 184
				(void) sprintf(buf, "Final-Rcpt: %s",
E 184
I 184
				(void) sprintf(buf, "Final-Recipient: %s",
E 184
					q->q_paddr);
				putline(buf, mci);
			}
E 186
I 186
			/* Final-Recipient: -- the name from the RCPT command */
			for (r = q; r->q_alias != NULL; r = r->q_alias)
				continue;
D 187
			(void) sprintf(buf, "Final-Recipient: %s", r->q_paddr);
E 187
I 187
			if (strchr(r->q_user, '@') == NULL)
				(void) sprintf(buf, "Final-Recipient: %s@%s",
					r->q_user, MyHostName);
			else
				(void) sprintf(buf, "Final-Recipient: %s",
					r->q_user);
E 187
			putline(buf, mci);
E 186

			/* Final-Status: -- same as Status?  XXX */
I 184
D 186
			if (q->q_fstatus != NULL && q->q_status != NULL)
E 186
I 186
			if (q->q_fstatus != NULL && q->q_fstatus != q->q_status)
E 186
			{
				(void) sprintf(buf, "Final-Status: %s",
					q->q_fstatus);
				putline(buf, mci);
			}
E 184

D 185
			/* Remote-MTS-Type: -- always INET?  XXX */
E 185
I 185
			/* Remote-MTS-Type: -- depends on mailer */
E 185
I 184
			if (q->q_mailer->m_mtstype != NULL)
			{
				(void) sprintf(buf, "Remote-MTS-Type: %s",
					q->q_mailer->m_mtstype);
				putline(buf, mci);
			}
E 184

			/* Remote-MTA: -- who was I talking to? */
			if (q->q_statmta != NULL)
			{
				(void) sprintf(buf, "Remote-MTA: %s",
					q->q_statmta);
				putline(buf, mci);
			}
I 186
			else if (q->q_host != NULL)
			{
				(void) sprintf(buf, "Remote-MTA: %s",
					q->q_host);
				putline(buf, mci);
			}
E 186

D 184
			/* Remote-Rcpt: -- same as Final-Rcpt?  XXX */
E 184
I 184
D 186
			/* Remote-Recipient: -- same as Final-Recipient?  XXX */
			if (strcmp(q->q_user, q->q_paddr) != 0)
E 186
I 186
			/* Remote-Recipient: -- recipient passed to far end */
			if (strcmp(q->q_user, r->q_paddr) != 0)
E 186
			{
				(void) sprintf(buf, "Remote-Recipient: %s",
					q->q_user);
				putline(buf, mci);
			}
E 184

D 184
			/* Remote-Status: -- same as Final-Status?  XXX */
E 184
I 184
			/* Remote-Status: -- return code from remote mailer */
			if (q->q_rstatus != NULL)
			{
				(void) sprintf(buf, "Remote-Status: %s",
					q->q_rstatus);
				putline(buf, mci);
			}
E 191
E 184
		}
	}
I 188
#endif
E 188

	/*
E 176
I 25
D 36
	**  Output "From" line unless supressed
	*/

	if (!bitset(M_NHDR, m->m_flags))
	{
		(void) expand("$l", buf, &buf[sizeof buf - 1]);
		fprintf(fp, "%s\n", buf);
	}

	/*
E 25
	**  Output header of error message.
	*/

	if (bitset(M_NEEDDATE, m->m_flags))
	{
		(void) expand("$b", buf, &buf[sizeof buf - 1]);
		fprintf(fp, "Date: %s\n", buf);
	}
	if (bitset(M_NEEDFROM, m->m_flags))
	{
		(void) expand("$g", buf, &buf[sizeof buf - 1]);
		fprintf(fp, "From: %s (Mail Delivery Subsystem)\n", buf);
	}
E 23
D 34
	fprintf(fp, "To: %s\n", To);
E 34
I 34
	fprintf(fp, "To: %s\n", CurEnv->e_to);
E 34
D 27
	fprintf(fp, "Subject: Unable to deliver mail\n");
E 27
I 27
	fprintf(fp, "Subject: %s\n", ErrorMessage);
E 27
I 25

	/*
	**  End of error message header
	*/

	define('f', oldfmac);
	define('g', oldgmac);
E 25
I 23

	/*
E 36
D 54
	**  Output transcript of errors
	*/

E 23
D 36
	fprintf(fp, "\n   ----- Transcript of session follows -----\n");
E 36
I 36
	fprintf(fp, "   ----- Transcript of session follows -----\n");
E 36
I 28
	(void) fflush(Xscript);
E 28
D 11
	fflush(fp);
	while ((i = read(xfile, copybuf, sizeof copybuf)) > 0)
		write(fileno(fp), copybuf, i);
E 11
I 11
D 16
	while (fgets(xfile, buf, sizeof buf) != NULL)
E 16
I 16
	while (fgets(buf, sizeof buf, xfile) != NULL)
E 16
D 42
		fputs(buf, fp);
E 42
I 42
		putline(buf, fp, fullsmtp);
E 42
I 23

	/*
E 54
	**  Output text of original message
	*/

E 23
E 11
D 21
	fprintf(fp, "\n   ----- Unsent message follows -----\n");
D 16
	fflush(fp);
E 16
I 16
	(void) fflush(fp);
E 16
D 11
	rewind(stdin);
	while ((i = read(fileno(stdin), copybuf, sizeof copybuf)) > 0)
		write(fileno(fp), copybuf, i);
E 11
I 11
	putmessage(fp, Mailer[1]);
E 21
I 21
D 22
	if (TempFile != NULL)
E 22
I 22
D 172
	if (NoReturn)
E 172
I 172
D 176
	if (bitset(EF_NORETURN, e->e_flags))
E 176
I 176
D 197
	if (bitset(EF_NORETURN, e->e_parent->e_flags))
E 176
E 172
D 115
		fprintf(fp, "\n   ----- Return message suppressed -----\n\n");
D 59
	else if (TempFile != NULL)
E 59
I 59
	else if (e->e_parent->e_dfp != NULL)
E 115
I 115
		SendBody = FALSE;
E 197
I 177
D 178
	if (!SendBody)
		pflags |= PF_NOBODYPART;
E 178
I 178
D 191
	if (!SendBody && e->e_msgboundary != NULL)
		pflags |= PF_DELETEMIMEHDRS;
E 191
E 178
E 177
I 134
D 165
	putline("", fp, m);
E 165
I 165
	putline("", mci);
E 165
E 134
D 117
	if (e->e_parent->e_dfp != NULL)
E 117
I 117
D 198
	if (e->e_parent->e_df != NULL)
E 198
I 198
	if (bitset(EF_HAS_DF, e->e_parent->e_flags))
E 198
E 117
E 115
E 59
E 22
	{
I 197
D 203
		sendbody = !bitset(EF_NO_BODY_RETN, e->e_parent->e_flags);
E 203
I 203
		sendbody = !bitset(EF_NO_BODY_RETN, e->e_parent->e_flags) &&
			   !bitset(EF_NO_BODY_RETN, e->e_flags);
E 203

E 197
D 33
		fprintf(fp, "\n   ----- Unsent message follows -----\n");
		(void) fflush(fp);
D 29
		putmessage(fp, Mailer[1]);
E 29
I 29
		putmessage(fp, Mailer[1], xdot);
E 33
I 33
D 176
		if (SendBody)
D 134
		{
D 64
			fprintf(fp, "\n   ----- Unsent message follows -----\n");
E 64
I 64
			putline("\n", fp, m);
E 134
D 145
			putline("   ----- Unsent message follows -----\n", fp, m);
E 145
I 145
D 165
			putline("   ----- Original message follows -----\n", fp, m);
E 165
I 165
			putline("   ----- Original message follows -----\n", mci);
E 176
I 176
		if (e->e_msgboundary == NULL)
		{
D 197
			if (SendBody)
E 197
I 197
			if (sendbody)
E 197
				putline("   ----- Original message follows -----\n", mci);
			else
				putline("   ----- Message header follows -----\n", mci);
			(void) fflush(mci->mci_out);
		}
E 176
E 165
E 145
E 64
D 134
			(void) fflush(fp);
D 36
			putmessage(fp, Mailer[1], xdot);
E 36
I 36
D 38
			putheader(fp, Mailer[1], CurEnv->e_parent);
E 38
I 38
D 59
			putheader(fp, m, CurEnv->e_parent);
E 59
I 59
D 62
			putheader(fp, m, e->e_parent);
E 62
I 62
D 64
			putheader(fp, m, e->e_parent, crlf);
E 62
E 59
E 38
			fprintf(fp, "\n");
D 38
			putbody(fp, Mailer[1], xdot);
E 38
I 38
D 59
			putbody(fp, m, xdot);
E 59
I 59
D 62
			putbody(fp, m, xdot, e->e_parent);
E 62
I 62
			putbody(fp, m, xdot, e->e_parent, crlf);
E 64
I 64
			putheader(fp, m, e->e_parent);
			putline("\n", fp, m);
			putbody(fp, m, e->e_parent);
E 64
E 62
E 59
E 38
E 36
		}
E 134
		else
D 134
		{
D 64
			fprintf(fp, "\n  ----- Message header follows -----\n");
E 64
I 64
			putline("\n", fp, m);
E 134
D 136
			putline("  ----- Message header follows -----\n", fp, m);
E 136
I 136
D 165
			putline("   ----- Message header follows -----\n", fp, m);
E 136
E 64
D 134
			(void) fflush(fp);
D 38
			putheader(fp, Mailer[1]);
E 38
I 38
D 58
			putheader(fp, m, CurEnv);
E 58
I 58
D 59
			putheader(fp, m, CurEnv->e_parent);
E 59
I 59
D 62
			putheader(fp, m, e->e_parent);
E 62
I 62
D 64
			putheader(fp, m, e->e_parent, crlf);
E 64
I 64
			putheader(fp, m, e->e_parent);
E 134
I 134
		(void) fflush(fp);
E 165
I 165
D 176
			putline("   ----- Message header follows -----\n", mci);
		(void) fflush(mci->mci_out);
E 165

		if (e->e_msgboundary != NULL)
E 176
		{
D 165
			putline("", fp, m);
E 165
I 165
D 181
			putline("", mci);
E 181
E 165
			(void) sprintf(buf, "--%s", e->e_msgboundary);
I 218

E 218
D 165
			putline(buf, fp, m);
D 136
			(void) sprintf(buf, "Content-Type: %s/rfc822",
				SendBody ? "message" : "X-message-header");
			putline(buf, fp, m);
E 136
I 136
			putline("Content-Type: message/rfc822", fp, m);
E 136
			putline("", fp, m);
E 165
I 165
			putline(buf, mci);
D 191
			putline("Content-Type: message/rfc822", mci);
E 191
I 191
D 207
			(void) sprintf(buf, "Content-Type: message/rfc822%s",
D 197
				mci, SendBody ? "" : "-headers");
E 197
I 197
D 203
				mci, sendbody ? "" : "-headers");
E 203
I 203
				sendbody ? "" : "-headers");
E 207
I 207
			(void) sprintf(buf, "Content-Type: %s",
				sendbody ? "message/rfc822"
					 : "text/rfc822-headers");
E 207
E 203
E 197
			putline(buf, mci);
I 218

			p = hvalue("Content-Transfer-Encoding", e->e_parent->e_header);
			if (p != NULL && strcasecmp(p, "binary") != 0)
				p = NULL;
			if (p == NULL && bitset(EF_HAS8BIT, e->e_parent->e_flags))
				p = "8bit";
			if (p != NULL)
			{
				(void) sprintf(buf, "Content-Transfer-Encoding: %s",
					p);
				putline(buf, mci);
			}
E 218
E 191
D 181
			putline("", mci);
E 181
E 165
E 134
E 64
E 62
E 59
E 58
E 38
		}
I 181
		putline("", mci);
E 181
I 134
D 165
		putheader(fp, m, e->e_parent);
		putline("", fp, m);
E 165
I 165
D 173
		putheader(mci, e->e_parent);
		putline("", mci);
E 173
I 173
D 177
		putheader(mci, e->e_parent->e_header, e->e_parent);
E 177
I 177
D 191
		putheader(mci, e->e_parent->e_header, e->e_parent, pflags);
E 191
I 191
		putheader(mci, e->e_parent->e_header, e->e_parent);
E 191
E 177
E 173
E 165
D 197
		if (SendBody)
E 197
I 197
		if (sendbody)
E 197
D 165
			putbody(fp, m, e->e_parent, e->e_msgboundary);
E 165
I 165
D 177
			putbody(mci, e->e_parent, e->e_msgboundary);
E 177
I 177
D 191
			putbody(mci, e->e_parent, e->e_msgboundary, pflags);
E 177
E 165
I 136
		else
E 191
I 191
			putbody(mci, e->e_parent, e->e_msgboundary);
		else if (e->e_msgboundary == NULL)
E 191
I 173
		{
			putline("", mci);
E 173
D 138
			putline("", fp, m);
E 136
		if (e->e_msgboundary != NULL)
		{
I 136
			putline("", fp, m);
E 136
			(void) sprintf(buf, "--%s--", e->e_msgboundary);
			putline(buf, fp, m);
		}
E 138
I 138
D 165
			putline("   ----- Message body suppressed -----", fp, m);
E 165
I 165
			putline("   ----- Message body suppressed -----", mci);
I 173
		}
E 173
E 165
E 138
E 134
E 33
E 29
	}
D 191
	else
E 191
I 191
	else if (e->e_msgboundary == NULL)
E 191
D 64
		fprintf(fp, "\n  ----- No message was collected -----\n\n");
E 64
I 64
	{
D 134
		putline("\n", fp, m);
E 134
D 165
		putline("  ----- No message was collected -----\n", fp, m);
E 165
I 165
		putline("  ----- No message was collected -----\n", mci);
E 165
D 134
		putline("\n", fp, m);
E 134
	}
I 134

I 138
	if (e->e_msgboundary != NULL)
	{
D 165
		putline("", fp, m);
E 165
I 165
		putline("", mci);
E 165
		(void) sprintf(buf, "--%s--", e->e_msgboundary);
D 165
		putline(buf, fp, m);
E 165
I 165
		putline(buf, mci);
E 165
	}
E 138
D 165
	putline("", fp, m);
E 165
I 165
	putline("", mci);
E 165
E 134
E 64
I 23

	/*
	**  Cleanup and exit
	*/

E 23
E 21
E 11
D 16
	close(xfile);
E 16
I 16
D 54
	(void) fclose(xfile);
E 54
E 16
	if (errno != 0)
D 36
		syserr("errhdr: I/O error");
E 36
I 36
		syserr("errbody: I/O error");
I 191
}
/*
**  SMTPTODSN -- convert SMTP to DSN status code
**
**	Parameters:
**		smtpstat -- the smtp status code (e.g., 550).
**
**	Returns:
**		The DSN version of the status code.
*/

char *
smtptodsn(smtpstat)
	int smtpstat;
{
I 206
	if (smtpstat < 0)
		return "4.4.2";

E 206
	switch (smtpstat)
	{
	  case 450:	/* Req mail action not taken: mailbox unavailable */
		return "4.2.0";

	  case 451:	/* Req action aborted: local error in processing */
		return "4.3.0";

	  case 452:	/* Req action not taken: insufficient sys storage */
		return "4.3.1";

	  case 500:	/* Syntax error, command unrecognized */
		return "5.5.2";

	  case 501:	/* Syntax error in parameters or arguments */
		return "5.5.4";

	  case 502:	/* Command not implemented */
		return "5.5.1";

	  case 503:	/* Bad sequence of commands */
		return "5.5.1";

	  case 504:	/* Command parameter not implemented */
		return "5.5.4";

	  case 550:	/* Req mail action not taken: mailbox unavailable */
		return "5.2.0";

	  case 551:	/* User not local; please try <...> */
		return "5.1.6";

	  case 552:	/* Req mail action aborted: exceeded storage alloc */
		return "5.2.2";

	  case 553:	/* Req action not taken: mailbox name not allowed */
		return "5.1.3";

	  case 554:	/* Transaction failed */
		return "5.0.0";
	}

	if ((smtpstat / 100) == 2)
		return "2.0.0";
	if ((smtpstat / 100) == 4)
		return "4.0.0";
	return "5.0.0";
}
/*
**  XTEXTIFY -- take regular text and turn it into DSN-style xtext
**
**	Parameters:
**		t -- the text to convert.
**
**	Returns:
**		The xtext-ified version of the same string.
*/

char *
xtextify(t)
	register char *t;
{
	register char *p;
	int l;
	int nbogus;
	static char *bp = NULL;
	static int bplen = 0;

	/* figure out how long this xtext will have to be */
	nbogus = l = 0;
	for (p = t; *p != '\0'; p++)
	{
		register int c = (*p & 0xff);

		/* ASCII dependence here -- this is the way the spec words it */
D 200
		if (c < '!' || c > '~' || c == '+' || c == '\\' || c == '(')
E 200
I 200
D 208
		if ((c < ' ' || c > '~' || c == '+' || c == '\\' || c == '(') &&
		    c != '\t')
E 208
I 208
		if (c < '!' || c > '~' || c == '+' || c == '\\' || c == '(')
E 208
E 200
			nbogus++;
		l++;
	}
	if (nbogus == 0)
		return t;
	l += nbogus * 2 + 1;

	/* now allocate space if necessary for the new string */
	if (l > bplen)
	{
		if (bp != NULL)
			free(bp);
		bp = xalloc(l);
		bplen = l;
	}

	/* ok, copy the text with byte expansion */
	for (p = bp; *t != '\0'; )
	{
		register int c = (*t++ & 0xff);

		/* ASCII dependence here -- this is the way the spec words it */
		if (c < '!' || c > '~' || c == '+' || c == '\\' || c == '(')
		{
			*p++ = '+';
			*p++ = "0123456789abcdef"[c >> 4];
			*p++ = "0123456789abcdef"[c & 0xf];
		}
		else
			*p++ = c;
	}
	*p = '\0';
I 214
	return bp;
}
/*
**  XUNTEXTIFY -- take xtext and turn it into plain text
**
**	Parameters:
**		t -- the xtextified text.
**
**	Returns:
**		The decoded text.  No attempt is made to deal with
**		null strings in the resulting text.
*/

char *
xuntextify(t)
	register char *t;
{
	register char *p;
	int l;
	static char *bp = NULL;
	static int bplen = 0;

	/* heuristic -- if no plus sign, just return the input */
	if (strchr(t, '+') == NULL)
		return t;

	/* xtext is always longer than decoded text */
	l = strlen(t);
	if (l > bplen)
	{
		if (bp != NULL)
			free(bp);
		bp = xalloc(l);
		bplen = l;
	}

	/* ok, copy the text with byte compression */
	for (p = bp; *t != '\0'; t++)
	{
		register int c = *t & 0xff;

		if (c != '+')
		{
			*p++ = c;
			continue;
		}

		c = *++t & 0xff;
		if (!isascii(c) || !isxdigit(c))
		{
			/* error -- first digit is not hex */
			usrerr("bogus xtext: +%c", c);
			t--;
			continue;
		}
		if (isdigit(c))
			c -= '0';
		else if (isupper(c))
			c -= 'A' - 10;
		else
			c -= 'a' - 10;
		*p = c << 4;

		c = *++t & 0xff;
		if (!isascii(c) || !isxdigit(c))
		{
			/* error -- second digit is not hex */
			usrerr("bogus xtext: +%x%c", *p >> 4, c);
			t--;
			continue;
		}
		if (isdigit(c))
			c -= '0';
		else if (isupper(c))
			c -= 'A' - 10;
		else
			c -= 'a' - 10;
		*p++ |= c;
	}
E 214
	return bp;
I 199
}
/*
**  XTEXTOK -- check if a string is legal xtext
**
**	Xtext is used in Delivery Status Notifications.  The spec was
**	taken from draft-ietf-notary-mime-delivery-04.txt.
**
**	Parameters:
**		s -- the string to check.
**
**	Returns:
**		TRUE -- if 's' is legal xtext.
**		FALSE -- if it has any illegal characters in it.
*/

bool
xtextok(s)
	char *s;
{
	int c;

	while ((c = *s++) != '\0')
	{
		if (c == '+')
		{
			c = *s++;
			if (!isascii(c) || !isxdigit(c))
				return FALSE;
			c = *s++;
			if (!isascii(c) || !isxdigit(c))
				return FALSE;
		}
D 215
		else if (c < '!' || c > '~' || c == '\\' || c == '(')
E 215
I 215
		else if (c < '!' || c > '~' || c == '=')
E 215
			return FALSE;
	}
	return TRUE;
E 199
E 191
I 105
}
/*
**  PRUNEROUTE -- prune an RFC-822 source route
** 
**	Trims down a source route to the last internet-registered hop.
**	This is encouraged by RFC 1123 section 5.3.3.
** 
**	Parameters:
**		addr -- the address
** 
**	Returns:
**		TRUE -- address was modified
**		FALSE -- address could not be pruned
** 
**	Side Effects:
**		modifies addr in-place
*/

I 211
bool
E 211
pruneroute(addr)
	char *addr;
{
D 168
#ifdef NAMED_BIND
E 168
I 168
#if NAMED_BIND
E 168
	char *start, *at, *comma;
	char c;
	int rcode;
	char hostbuf[BUFSIZ];
	char *mxhosts[MAXMXHOSTS + 1];

	/* check to see if this is really a route-addr */
	if (*addr != '<' || addr[1] != '@' || addr[strlen(addr) - 1] != '>')
		return FALSE;
	start = strchr(addr, ':');
	at = strrchr(addr, '@');
	if (start == NULL || at == NULL || at < start)
		return FALSE;

	/* slice off the angle brackets */
	strcpy(hostbuf, at + 1);
	hostbuf[strlen(hostbuf) - 1] = '\0';

	while (start)
	{
D 130
		if (getmxrr(hostbuf, mxhosts, "", &rcode) > 0)
E 130
I 130
		if (getmxrr(hostbuf, mxhosts, FALSE, &rcode) > 0)
E 130
		{
			strcpy(addr + 1, start + 1);
			return TRUE;
		}
		c = *start;
		*start = '\0';
		comma = strrchr(addr, ',');
		if (comma && comma[1] == '@')
			strcpy(hostbuf, comma + 2);
		else
			comma = 0;
		*start = c;
		start = comma;
	}
#endif
	return FALSE;
E 105
E 36
}
E 1
