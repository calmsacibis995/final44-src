h30852
s 00024/00001/01995
d D 8.88 95/06/16 10:12:03 eric 286 285
c check for attacks against the qf file
e
s 00002/00000/01994
d D 8.87 95/06/10 12:39:02 eric 285 284
c count children.  Someday we might reject connections on this basis.
e
s 00001/00001/01993
d D 8.86 95/06/10 12:15:58 eric 284 283
c mailq can sometimes reject a legitimate user
e
s 00012/00001/01982
d D 8.85 95/05/28 11:50:05 eric 283 282
c lint
e
s 00025/00010/01958
d D 8.84 95/05/28 07:02:02 eric 282 281
c better implementation of MaxQueueRun -- doesn't have QUEUESEGSIZE
c granularity
e
s 00001/00001/01967
d D 8.83 95/05/27 09:36:38 eric 281 280
c make the maximum number of jobs in one queue run an option
e
s 00075/00022/01893
d D 8.82 95/05/27 09:16:17 eric 280 279
c dynmically extend the queue size
e
s 00009/00009/01906
d D 8.81 95/05/18 07:13:41 eric 279 278
c portability fix for broken C compiler on NEC EWS-UX/V.
e
s 00007/00001/01908
d D 8.80 95/04/22 12:00:16 eric 278 277
c log skipped queue runs
e
s 00001/00001/01908
d D 8.79 95/04/21 09:57:38 eric 277 276
c update copyright notice
e
s 00000/00002/01909
d D 8.78 95/04/19 10:18:02 eric 276 275
c don't need extern long atol() -- done in stdlib.h
e
s 00001/00001/01910
d D 8.77 95/04/03 09:31:21 eric 275 274
c clean up problems with MIME 8 to 7 bit conversions
e
s 00001/00001/01910
d D 8.76 95/03/31 16:54:03 eric 274 273
c merge a bit with Sun version
e
s 00002/00003/01909
d D 8.75 95/03/31 10:52:19 eric 273 272
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00020/00007/01892
d D 8.74 95/03/27 09:25:48 eric 272 271
c more cleanup for DSN drafts
e
s 00006/00006/01893
d D 8.73 95/03/21 15:58:57 eric 271 270
c fix -bp mode to print reasonable size
e
s 00032/00024/01867
d D 8.72 95/03/21 15:28:38 eric 270 269
c eliminate `D' line in qf file
e
s 00014/00008/01877
d D 8.71 95/03/21 13:21:06 eric 269 268
c remove picky check of qf file name
e
s 00000/00015/01885
d D 8.70 95/03/21 09:27:01 eric 268 267
c new DSN draft
e
s 00002/00012/01898
d D 8.69 95/03/21 06:46:16 eric 267 266
c back out E qf line
e
s 00001/00001/01909
d D 8.68 95/03/14 09:11:17 eric 266 265
c change call to expand() to be more rational (and consistent!)
e
s 00005/00005/01905
d D 8.67 95/03/14 08:19:08 eric 265 264
c be more precise on MAXNAME checking
e
s 00031/00002/01879
d D 8.66 95/03/05 14:34:13 eric 264 263
c changes suggested by *Hobbit*; SafeFileEnvironment option
e
s 00005/00006/01876
d D 8.65 95/03/05 11:57:18 eric 263 261
i 262
c add "strict" parameter to denlstring to allow continuations
e
s 00008/00008/01537
d D 8.41.1.3 95/03/05 10:10:02 eric 262 260
c add concept of "strict adherence" to newline standard
e
s 00004/00006/01876
d D 8.64 95/02/28 14:43:19 eric 261 259
i 260
c incorporate fixes from 8.6.11
e
s 00008/00008/01537
d D 8.41.1.2 95/02/28 10:58:54 eric 260 258
c multiple glitches in 8.6.10 -- see ../RELEASE_NOTES for details
e
s 00001/00000/01879
d D 8.63 95/02/23 15:50:40 eric 259 257
c cleanup to make gcc -Winitialized happier
e
s 00002/00006/01543
d D 8.41.1.1 95/02/10 07:38:01 eric 258 236
i 257
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00010/00010/01869
d D 8.62 95/02/10 07:16:49 eric 257 256
c fix security problem: avoid newlines in command line or IDENT input
e
s 00001/00007/01878
d D 8.61 95/02/05 08:04:07 eric 256 255
c cut at 20 January version of DSN document
e
s 00012/00012/01873
d D 8.60 94/12/29 06:59:31 eric 255 254
c generalize queue order configuration
e
s 00002/00001/01883
d D 8.59 94/12/10 07:46:53 eric 254 253
c log transaction delay as well as queue delay (for ordering lists)
e
s 00015/00005/01869
d D 8.58 94/11/23 15:21:12 eric 253 252
c get ORCPT= ESMTP DSN parameter working
e
s 00002/00002/01872
d D 8.57 94/11/23 07:25:45 eric 252 251
c oops.... off by one error
e
s 00014/00000/01860
d D 8.56 94/11/23 07:19:18 eric 251 250
c save OMTS and ENVID parameters in queue file
e
s 00002/00002/01858
d D 8.55 94/11/22 22:25:09 eric 250 249
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00004/00004/01856
d D 8.54 94/11/21 21:07:42 eric 249 248
c convert to new DSN draft
e
s 00001/00001/01859
d D 8.53 94/11/19 16:57:43 eric 248 247
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00009/00004/01851
d D 8.52 94/11/11 06:04:25 eric 247 246
c include sequence number in queue runs
e
s 00102/00007/01753
d D 8.51 94/11/04 08:40:39 eric 246 245
c first cut at DSN implementation
e
s 00005/00001/01755
d D 8.50 94/09/08 15:20:23 eric 245 244
c attempt to allow udb rewriting of envelope senders; still not
c quite right, but I can't really test it without a network connection
e
s 00001/00001/01755
d D 8.49 94/08/22 19:09:22 eric 244 243
c repair MinQueueAge code
e
s 00025/00008/01731
d D 8.48 94/08/18 08:17:17 eric 243 242
c implement minimum queue age between deliveries
e
s 00016/00005/01723
d D 8.47 94/08/15 18:07:27 eric 242 241
c store dev information in qf file; add RFC 1428-specified
c Content-Type: text/plain; charset=unknown-8bit header to messages
c being converted from 8 -> 7 bit with no specific Content-Type
e
s 00001/00000/01727
d D 8.46 94/08/09 09:06:04 eric 241 240
c add comment about device major/minor info
e
s 00026/00000/01701
d D 8.45 94/08/07 17:42:12 eric 240 239
c DECWRL extensions to qf file
e
s 00164/00014/01537
d D 8.44 94/08/07 16:14:56 eric 239 238
c allow sorting by host name instead of by message priority
e
s 00006/00000/01545
d D 8.43 94/07/23 10:12:36 eric 238 237
c tweaks & bug fixes to MIME algorithm
e
s 00000/00000/01545
d D 8.42 94/07/23 07:59:49 eric 237 236
c MIME 8 to 7 bit support
e
s 00001/00001/01544
d D 8.41 94/04/18 15:17:12 eric 236 235
c when creating the df file, be sure you truncate any existing file
e
s 00004/00002/01541
d D 8.40 94/03/06 09:00:36 eric 235 234
c reset ExitStat between individual jobs to prevent bogus behaviour
e
s 00001/00001/01542
d D 8.39 94/02/01 09:36:09 eric 234 233
c fix bogus printf keyletter
e
s 00009/00003/01534
d D 8.38 94/01/24 08:01:48 eric 233 232
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00004/00001/01533
d D 8.37 94/01/22 09:01:04 eric 232 231
c Apollo/POSIX changes -- leading pathname of // can legally have
c different semantics; ensure that this never happens when building pathnames
e
s 00001/00001/01533
d D 8.36 94/01/09 09:22:35 eric 231 230
c fix problem causing excessive rewriting of headers being queued
e
s 00009/00003/01525
d D 8.35 94/01/01 12:53:29 eric 230 229
c fix bogosity in H lines in queue file for null $x expansions
e
s 00005/00004/01523
d D 8.34 93/12/29 09:30:27 eric 229 228
c move SIGCHLD setsignal call so that first zombie is caught
e
s 00004/00011/01523
d D 8.33 93/12/22 09:55:53 eric 228 227
c more error message cleanup
e
s 00002/00001/01532
d D 8.32 93/12/17 08:14:42 eric 227 226
c don't output null headers into queue file
e
s 00001/00000/01532
d D 8.31 93/12/16 17:47:55 eric 226 225
c define $i during queue runs
e
s 00017/00015/01515
d D 8.30 93/12/11 13:53:57 eric 225 224
c avoid problems if a tf file already exists; improve logging
e
s 00003/00000/01527
d D 8.29 93/11/20 06:52:10 eric 224 223
c more attempts to trap fd 0 1 2 problem
e
s 00005/00000/01522
d D 8.28 93/11/13 07:57:30 eric 223 222
c two processes had the connection cache causing improper QUITs
e
s 00001/00001/01521
d D 8.27 93/10/29 19:24:40 eric 222 221
c improved logging (log ctladdr on recipients
e
s 00001/00001/01521
d D 8.26 93/10/28 19:37:54 eric 221 220
c avoid duplicate reads of Errors-To: list
e
s 00001/00003/01521
d D 8.25 93/10/27 09:17:31 eric 220 219
c check fflush, fclose, and fsync return values in a few critical places
e
s 00001/00001/01523
d D 8.24 93/10/23 16:45:34 eric 219 218
c fix a problem causing C mailer flag to be ignored if the message
c was queued
e
s 00020/00007/01504
d D 8.23 93/10/23 12:47:06 eric 218 217
c open file debugging; avoid creating excess tf files on first queueup
e
s 00001/00000/01510
d D 8.22 93/10/21 07:20:52 eric 217 216
c turn off GrabTo when reading the queue to avoid duplicate deliveries
e
s 00005/00007/01505
d D 8.21 93/10/16 08:50:01 eric 216 215
c check for possibility of fdopen returning null
e
s 00005/00005/01507
d D 8.20 93/10/08 15:54:51 eric 215 214
c 8.6.1: A/UX and Encore UMAX V patches; fix to not toss error messages
c too early
e
s 00003/00000/01509
d D 8.19 93/09/26 19:08:43 eric 214 213
c fix problem causing "c" option (don't connect to expensive mailers)
c to be ignored in some SMTP runs.
e
s 00004/00001/01505
d D 8.18 93/09/21 15:32:59 eric 213 212
c avoid duplicate error messages
e
s 00011/00002/01495
d D 8.17 93/09/18 11:41:54 eric 212 211
c relax queue filename validation for AIX and other pid > 32000 OSes
e
s 00002/00001/01495
d D 8.16 93/08/25 19:47:02 eric 211 210
c print a message for jobs that disappear between reading the queue
c and printing the queue
e
s 00004/00004/01492
d D 8.15 93/08/23 08:32:33 eric 210 209
c add "ext" argument to lockfile so you can accurately tell what file
c is being locked in logging/error messages
e
s 00001/00001/01495
d D 8.14 93/08/22 17:07:51 eric 209 208
c add restrictqrun privacy option
e
s 00004/00001/01492
d D 8.13 93/08/20 08:08:59 eric 208 207
c fix screwed up error message returns in some situations
e
s 00017/00018/01476
d D 8.12 93/08/19 13:37:00 eric 207 206
c fix obscure lost mail problem if fcntl locking used (ugh)
e
s 00034/00016/01460
d D 8.11 93/08/16 10:08:28 eric 206 205
c fix obscure race condition
e
s 00001/00001/01475
d D 8.10 93/08/07 11:58:51 eric 205 204
c don't delete apparently bogus queue files so eagerly
e
s 00002/00001/01474
d D 8.9 93/07/29 08:31:52 eric 204 203
c don't call newstr() macro with arguments with subroutine calls, since
c it double-evaluates
e
s 00023/00007/01452
d D 8.8 93/07/27 21:36:55 eric 203 202
c try to recover more gracefully from existing tf file condition
e
s 00002/00003/01457
d D 8.7 93/07/26 09:22:09 eric 202 201
c signal and file locking portability changes
e
s 00001/00001/01459
d D 8.6 93/07/19 20:50:18 eric 201 200
c SGI IRIX & ANSI C portability
e
s 00013/00010/01447
d D 8.5 93/07/17 13:50:26 eric 200 199
c don't announce qf name to srvrsmtp-generated queue runs; don't create
c a bogus q_alias on queue runs (this causes error messages to act differently
c between regular and queue runs).
e
s 00002/00000/01455
d D 8.4 93/07/16 10:33:39 eric 199 198
c fix problem leaving incoming SMTP connection in FIN_WAIT_2 for
c extended periods
e
s 00002/00002/01453
d D 8.3 93/07/13 12:58:45 eric 198 197
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00009/00001/01446
d D 8.2 93/07/11 06:52:48 eric 197 196
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/01445
d D 8.1 93/06/07 10:31:34 bostic 196 195
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/01444
d D 6.61 93/06/03 17:02:48 eric 195 194
c really truly deliver server smtp messages in background
e
s 00001/00001/01444
d D 6.60 93/05/30 08:54:49 eric 194 193
c fsync queue files
e
s 00001/00001/01444
d D 6.59 93/05/28 07:00:49 eric 193 192
c change alias initialization to general map initialization
e
s 00000/00013/01445
d D 6.58 93/05/27 11:37:45 eric 192 191
c prototype functions
e
s 00001/00004/01457
d D 6.57 93/05/22 08:58:02 eric 191 190
c AIX compatibility changes; clean up map initialization functions
e
s 00001/00001/01460
d D 6.56 93/05/04 15:45:18 eric 190 189
c update for MIME encapsulated error messages
e
s 00002/00002/01459
d D 6.55 93/05/03 17:24:06 eric 189 188
c ANSI fixes
e
s 00004/00004/01457
d D 6.54 93/05/03 12:25:14 eric 188 187
c clean up extra "C" line in qf file; first cut at new alias scheme
e
s 00001/00001/01460
d D 6.53 93/05/01 12:26:35 eric 187 186
c minor tweaking of syslog levels & compile fixes for SunOS & Ultrix
e
s 00000/00001/01461
d D 6.52 93/04/27 18:51:57 eric 186 185
c move #include <sys/stat.h> into conf.h
e
s 00001/00001/01461
d D 6.51 93/04/26 13:28:05 eric 185 184
c use FileMailer instead of ProgMailer
e
s 00006/00007/01456
d D 6.50 93/04/26 12:44:55 eric 184 183
c fix misinterpretation of ctladdr when it goes through the queue;
c this causes the setuid bit on files to be ignored
e
s 00049/00028/01414
d D 6.49 93/04/17 10:34:57 eric 183 182
c improve error printing (changes format of C line in qf)
e
s 00008/00000/01434
d D 6.48 93/04/15 19:03:41 eric 182 181
c fixes to handle null messages -- why did this break?
e
s 00022/00004/01412
d D 6.47 93/04/15 07:41:19 eric 181 180
c add e_bodytype and B queue line and -B flag for body type information
e
s 00003/00001/01413
d D 6.46 93/04/04 16:03:25 eric 180 179
c IDENT cleanup; move loopback checking from srvr to user smtp
e
s 00004/00003/01410
d D 6.45 93/04/01 15:04:35 eric 179 178
c free work queue entry even if skipping the job
e
s 00001/00001/01412
d D 6.44 93/04/01 14:59:30 eric 178 177
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00008/00002/01405
d D 6.43 93/04/01 13:54:19 eric 177 176
c do immediate requeue if expanding aliases during queue run (from SMTP)
e
s 00003/00004/01404
d D 6.42 93/04/01 13:30:06 eric 176 175
c always do sendall, even if errors in queue file; save qf name properly
e
s 00001/00001/01407
d D 6.41 93/04/01 08:09:54 eric 175 174
c don't abort an entire queue run after a single locked file
e
s 00037/00021/01371
d D 6.40 93/03/30 15:49:58 eric 174 173
c hooks for eventual better handling of SMTP recipients
e
s 00004/00000/01388
d D 6.39 93/03/25 09:10:40 eric 173 172
c catch "unable to create locked temp file" condition
e
s 00003/00003/01385
d D 6.38 93/03/19 13:00:05 eric 172 171
c keep c0 static, otherwise it is undefined if no pid change
e
s 00054/00007/01334
d D 6.37 93/03/19 11:46:44 eric 171 170
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00001/00001/01340
d D 6.36 93/03/19 08:51:03 eric 170 169
c move SendMode and ErrorMode into the envelope
e
s 00009/00000/01332
d D 6.35 93/03/19 08:30:40 eric 169 168
c check for error writing queue control files
e
s 00004/00000/01328
d D 6.34 93/03/18 19:37:55 eric 168 167
c avoid extra unnecessary creation of queue files solely for an
c unneeded id
e
s 00001/00001/01327
d D 6.33 93/03/18 16:41:00 eric 167 166
c glitch on queue printing
e
s 00007/00001/01321
d D 6.32 93/03/18 16:38:26 eric 166 165
c accept old-format queue files
e
s 00016/00009/01306
d D 6.31 93/03/18 15:28:30 eric 165 164
c add one more letter to queue names to encode the hour; this makes
c queue ids more likely to be unique during any particular day
e
s 00002/00017/01313
d D 6.30 93/03/18 10:56:39 eric 164 163
c restore e_sender as sending address sans decorations
e
s 00000/00001/01330
d D 6.29 93/03/17 10:46:21 eric 163 162
c flock requires sys/file.h
e
s 00002/00008/01329
d D 6.28 93/03/17 10:35:24 eric 162 161
c attempts to handle ENFILE conditions better
e
s 00016/00059/01321
d D 6.27 93/03/17 09:55:24 eric 161 160
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00012/00009/01368
d D 6.26 93/03/16 09:16:24 eric 160 159
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00015/00001/01362
d D 6.25 93/03/06 10:52:15 eric 159 158
c always let root print queue; look at group set if available
e
s 00001/00001/01362
d D 6.24 93/03/06 10:03:50 eric 158 157
c minor bug in analyzing stat return status
e
s 00001/00001/01362
d D 6.23 93/03/01 13:15:33 eric 157 156
c yet more logging
e
s 00001/00001/01362
d D 6.22 93/03/01 12:44:01 eric 156 155
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00038/00001/01325
d D 6.21 93/02/28 18:43:35 eric 155 154
c allow command line limitations to individual queue runs
e
s 00001/00002/01325
d D 6.20 93/02/27 11:57:49 eric 154 153
c fix problem that caused looping in .forward files on queue runs only
e
s 00023/00002/01304
d D 6.19 93/02/26 08:20:48 eric 153 152
c add restrictmailq privacy flag; better
c transient error handling
e
s 00001/00001/01305
d D 6.18 93/02/24 10:19:38 eric 152 151
c fix yet another problem with new owner-foo implementation
e
s 00001/00001/01305
d D 6.17 93/02/23 06:31:54 eric 151 150
c overhaul status of SMTP reply codes
e
s 00001/00001/01305
d D 6.16 93/02/21 14:12:30 eric 150 149
c clean up shouldqueue function
e
s 00002/00000/01304
d D 6.15 93/02/21 09:52:44 eric 149 148
c fix "lost" queue run problem
e
s 00002/00002/01302
d D 6.14 93/02/20 13:46:48 eric 148 147
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00012/00005/01292
d D 6.13 93/02/19 09:22:25 eric 147 146
c handle cases where flock() returns EOPNOTSUPP or other errors
e
s 00001/00001/01296
d D 6.12 93/02/18 20:22:39 eric 146 145
c move the meta-characters from C0 into C1 space
e
s 00030/00009/01267
d D 6.11 93/02/16 18:30:11 eric 145 144
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00001/00001/01275
d D 6.10 93/02/14 14:41:44 eric 144 143
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00001/00000/01275
d D 6.9 93/02/12 14:36:33 eric 143 142
c fix System V compatibility -- again
e
s 00000/00003/01275
d D 6.8 93/01/28 17:04:53 eric 142 141
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00003/00000/01275
d D 6.7 93/01/28 10:15:55 eric 141 140
c System 5 compatibility, misc fixes
e
s 00001/00000/01274
d D 6.6 93/01/26 11:36:38 eric 140 139
c some (iffy) changes to prevent suppressing the actual sender
c during a queue run (interaction with C line in qf file)
e
s 00004/00004/01270
d D 6.5 93/01/21 15:18:52 eric 139 138
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00001/00000/01273
d D 6.4 93/01/18 14:32:29 eric 138 137
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00004/00000/01269
d D 6.3 93/01/13 18:38:20 eric 137 136
c environment handling simplification/bug fix; handle commas inside
c comments; properly limit large messages in -obq mode
e
s 00006/00006/01263
d D 6.2 93/01/09 14:45:42 eric 136 135
c tuning of queueing functions as recommended by John Gardiner Myers
c <jgm+@CMU.EDU>; return mail headers (no body) on messages with negative
c precedence; minor other bug fixes
e
s 00000/00000/01269
d D 6.1 92/12/21 16:08:50 eric 135 134
c Release 6
e
s 00020/00016/01249
d D 5.51 92/12/15 12:34:54 eric 134 133
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00013/00013/01252
d D 5.50 92/11/14 11:34:35 eric 133 132
c (partially) ANSI-fy it
e
s 00025/00000/01240
d D 5.49 92/10/03 10:40:57 eric 132 131
c security fixes: check mode and owner of qf files
e
s 00001/00000/01239
d D 5.48 92/09/22 16:40:29 eric 131 130
c a variety of bug minor bug fixes; add file locking when writing
c to a UNIX file; strip out dangerous envariables
e
s 00002/00001/01237
d D 5.47 92/07/20 22:20:17 eric 130 129
c do clean connection closing on queue runs
e
s 00038/00028/01200
d D 5.46 92/07/19 10:20:05 eric 129 128
c fix bogus envelope problem in clock-driven queue runs; misc. fixes
e
s 00001/00001/01227
d D 5.45 92/07/13 16:27:50 eric 128 127
c miscellaneous changes to improve logging and messages
e
s 00000/00001/01228
d D 5.44 92/07/12 14:39:15 eric 127 126
c lint
e
s 00026/00023/01203
d D 5.43 92/07/12 14:09:58 eric 126 125
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00020/00003/01206
d D 5.42 92/07/12 07:26:53 eric 125 124
c many fixes to controlling user code; fix Neil Rickert's hack using
c CNAME for someone else's host
e
s 00063/00152/01146
d D 5.41 92/07/12 07:01:31 eric 124 123
c clean up controlling user implementation; all those global variables
c weren't needed
e
s 00001/00001/01297
d D 5.40 92/07/11 18:51:53 eric 123 122
c open connection caching
e
s 00018/00001/01280
d D 5.39 92/05/10 07:15:12 eric 122 121
c make C option safe; output values of $r and $s macros to qf; allow
c long messages in queue files
e
s 00001/00001/01280
d D 5.38 92/04/16 18:40:18 eric 121 120
c try to eliminate some of the CurEnv globals
e
s 00029/00015/01252
d D 5.37 91/12/14 19:39:46 eric 120 119
c convert lockf implementation to use fcntl directly
e
s 00098/00075/01169
d D 5.36 91/12/14 12:37:00 eric 119 118
c fix race condition in queue file locking; generalize getla
e
s 00008/00002/01236
d D 5.35 91/12/13 12:09:36 eric 118 117
c fix lockf code; have getcanonname recognize canonical names
e
s 00001/00001/01237
d D 5.34 91/12/05 18:47:30 eric 117 116
c oops.....
e
s 00035/00006/01203
d D 5.33 91/12/05 17:50:19 eric 116 115
c hacks for systems with lockf, not flock
e
s 00001/00001/01208
d D 5.32 91/03/12 17:30:58 eric 115 114
c k option specifies checkpoint interval (default 10);
c qf file is rewritten after k successful deliveries.
c (ref bug 4.3BSD-reno/usr.bin/10)
e
s 00001/00001/01208
d D 5.31 91/03/02 17:15:27 bostic 114 113
c ANSI
e
s 00001/00011/01208
d D 5.30 90/06/01 19:02:48 bostic 113 112
c new copyright notice
e
s 00026/00024/01193
d D 5.29 90/05/11 13:29:36 rick 112 111
c fixed a race condition in the locking when there are LOTS of queue runs
e
s 00194/00000/01023
d D 5.28 90/04/18 13:53:53 bostic 111 110
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00066/00072/00957
d D 5.27 90/04/16 08:12:20 rick 110 109
c fix shouldqueue to not get load average for evey file in queue
c new queue locking code that uses flock()
e
s 00000/00020/01029
d D 5.26 89/01/01 17:17:37 bostic 109 108
c remove DEBUG
e
s 00005/00000/01044
d D 5.25 88/11/17 22:02:29 karels 108 107
c more cleanup, fix some inappropriate syserr's
e
s 00011/00009/01033
d D 5.24 88/06/30 14:59:23 bostic 107 106
c install approved copyright notice
e
s 00024/00018/01018
d D 5.23 88/03/13 19:52:42 bostic 106 105
c add Berkeley specific header
e
s 00003/00001/01033
d D 5.22 86/10/14 18:05:54 eric 105 104
c don't let "locked job" messages remove transcript & lock
e
s 00006/00000/01028
d D 5.21 86/04/17 20:17:24 eric 104 103
c don't ignore aliasing during queue runs in conjunction with -bd
e
s 00006/00001/01022
d D 5.20 86/03/08 14:11:35 eric 103 102
c improve debugging in queue routines; don't output error addresses that
c are duplicates or otherwise marked as "don't send"
e
s 00031/00015/00992
d D 5.19 86/01/05 18:48:12 eric 102 101
m 
c rewrite reply-to and resent-reply-to; save errorqueueu in qf file;
c some performance hacking; some alias handling cleanup; delete leading
c spaces from SMTP lines
e
s 00001/00001/01006
d D 5.18 85/12/17 21:35:02 eric 101 100
m 
c patch to clearenvelope to avoid dereferencing garbage pointers
e
s 00010/00000/00997
d D 5.17 85/10/13 15:03:15 eric 100 99
m 
c fix botch with reapchild getting queue runs before intended wait
e
s 00001/00001/00996
d D 5.16 85/09/25 11:02:12 eric 99 98
m 
c DO use Ruleset 4 when defining $f -- it's very necessary (fix for <>
c will have to be done in configuration); pretty up mailq -v slightly
e
s 00008/00004/00989
d D 5.15 85/09/24 15:48:56 eric 98 97
m 
c clean up queue output somewhat (push null jobs to end); set
c SO_REUSEADDR and SO_KEEPALIVE on daemon sockets in the hopes of making
c dead connections disappear faster
e
s 00008/00002/00985
d D 5.14 85/09/21 16:23:49 eric 97 96
m 
c don't include ctime as part of priority, since the value affects the results of
c shouldqueue; we go back to adding ctime into the workcmpf in queue.c
e
s 00001/00001/00986
d D 5.13 85/09/21 15:51:55 eric 96 95
m 
c change sign on WkTimeFact so that is closer to what most people want
e
s 00011/00022/00976
d D 5.12 85/09/21 14:44:16 eric 95 94
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00015/00004/00983
d D 5.11 85/09/21 10:31:19 eric 94 93
m 
c add -v mode to mailq to print priorities as well (this should be extended
c in the future); fix some problems in the savemail state machine.
e
s 00003/00006/00984
d D 5.10 85/09/19 22:00:56 eric 93 92
m 
c use rename instead of link/unlink
e
s 00001/00001/00989
d D 5.9 85/09/19 20:48:17 eric 92 91
m 
c pretty up "Skipping ..." message
e
s 00001/00002/00989
d D 5.8 85/09/19 15:57:43 eric 91 90
m 
c updates to make it possible to run the queue in one process; this
c permits a database of host status to be built
e
s 00005/00002/00986
d D 5.7 85/09/19 13:35:29 eric 90 89
m 
c lint
e
s 00023/00000/00965
d D 5.6 85/09/19 12:18:20 eric 89 88
m 
c performance hacks
e
s 00090/00025/00875
d D 5.5 85/09/19 00:45:03 eric 88 87
m 
c SMI changes (somewhat)
e
s 00005/00001/00895
d D 5.4 85/06/08 10:26:47 eric 87 86
m 
c lint for 4.3 release
e
s 00009/00009/00887
d D 5.3 85/06/08 00:02:07 eric 86 85
m 
c lint
e
s 00002/00006/00894
d D 5.2 85/06/07 22:34:08 miriam 85 84
m 
c Resolve duplicate Sccsid.  Remove unused variable.
e
s 00014/00000/00886
d D 5.1 85/06/07 15:08:01 dist 84 83
m 
c Add copyright
e
s 00002/00002/00884
d D 4.5 85/02/15 09:26:30 eric 83 82
m 
c fix some bugs with -C flag; one with queuing from Teus
e
s 00021/00084/00865
d D 4.4 84/12/06 10:34:17 eric 82 81
m 
c back out attempt to use flock in the queue -- we don't in gerneral have
c an open file descriptor available.
e
s 00255/00042/00694
d D 4.3 84/12/05 23:13:28 eric 81 80
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00001/00001/00735
d D 4.2 84/03/11 16:52:15 eric 80 79
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00000/00000/00736
d D 4.1 83/07/25 19:43:35 eric 79 78
m 
c 4.2 release version
e
s 00001/00001/00735
d D 3.76 83/07/02 18:33:43 sam 78 77
m 
c include fix
e
s 00001/00001/00735
d D 3.75 83/06/11 20:59:15 eric 77 76
m 
c %d => %ld in mailq for PDP-11's
e
s 00004/00008/00732
d D 3.74 83/05/18 11:55:43 eric 76 75
m 
c Minor formatting change so that the entire text of the message can
c be printed.
e
s 00011/00000/00729
d D 3.73 83/04/23 12:54:19 eric 75 74
m 230
c Don't put Resent-*: lines in queue file to prevent outputing them
c inappropriately in the sent message.
e
s 00000/00001/00729
d D 3.72 83/03/12 15:39:45 eric 74 73
m 207
c Don't artifically add a "from: $q" when running the queue -- this seems
c to cause the from line in the qf file to be ignored.
e
s 00013/00003/00717
d D 3.71 83/02/02 12:53:39 eric 73 72
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00001/00000/00719
d D 3.70 83/01/17 09:31:58 eric 72 71
m 154
c define a newline in "nullmailer" so that queue files get written with
c newlines between the "H" lines.
e
s 00008/00000/00711
d D 3.69 83/01/08 19:53:24 eric 71 70
m 
c release daemon resources when running the queue
e
s 00001/00000/00710
d D 3.68 83/01/08 13:48:30 eric 70 69
m 
c be sure to open a new transcript on every queue run; when returning
c an SMTP transcript, only send the last half (i.e., that part which
c describes the sending half).
e
s 00008/00002/00702
d D 3.67 83/01/06 10:47:20 eric 69 68
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00009/00010/00695
d D 3.66 83/01/04 10:58:42 eric 68 67
m 
c fix botch that causes sendmail to core dump when there are large
c numbers of requests
e
s 00021/00006/00684
d D 3.65 83/01/03 18:01:43 eric 67 66
m 
c give more useful error messages (including the errno that caused
c a temporary failure); reflect these messages out to mailq
e
s 00001/00001/00689
d D 3.64 83/01/03 13:19:20 eric 66 65
m 
c print "request" instead of "requests" if there is only one request
e
s 00000/00044/00690
d D 3.63 83/01/03 13:01:47 eric 65 64
m 
c process timeouts like normal errors, so that they will get delivered to
c the correct address (i.e., the Errors-To: address)
e
s 00008/00001/00726
d D 3.62 83/01/03 11:28:18 eric 64 63
m 
c fix botch in reading the queue that caused it to throw away the last
c entry it read -- this was particulary obvious with only one entry in
c the queue.
e
s 00039/00019/00688
d D 3.61 83/01/02 14:27:16 eric 63 62
m 
c clean up output of mailq mode
e
s 00002/00002/00705
d D 3.60 83/01/01 21:25:53 eric 62 61
m 123
c Put CRLF on all lines in user SMTP.  Pass this info down to
c innumerable routines.
e
s 00091/00008/00616
d D 3.59 82/12/14 16:57:44 eric 61 60
m 105
c Add "print mail queue" mode (-bp flag or call as "mailq")
e
s 00001/00001/00623
d D 3.58 82/12/13 18:25:43 eric 60 59
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00003/00006/00621
d D 3.57 82/12/05 13:46:39 eric 59 58
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00002/00000/00625
d D 3.56 82/11/28 16:00:58 eric 58 57
m 
c implement SMTP auto-shutdown on 421 codes; clean up some error processing
c items, particularly in SMTP; don't reinstantiate error message bodies after
c queueing; other minor changes.  This is all cleanup from 3.253.
e
s 00008/00010/00617
d D 3.55 82/11/28 10:22:31 eric 57 56
m 
c fix a number of problems left over from yesterday's delta.  The big
c triumph is being able to delete the parameter from disconnect().
e
s 00071/00055/00556
d D 3.54 82/11/28 00:22:39 eric 56 55
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00007/00009/00604
d D 3.53 82/11/24 18:44:38 eric 55 54
m 
c lint it
e
s 00015/00024/00598
d D 3.52 82/11/24 17:15:38 eric 54 53
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00001/00001/00621
d D 3.51 82/11/17 09:37:01 eric 53 52
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00000/00000/00622
d D 3.50 82/11/13 17:55:36 eric 52 51
x 51 49
m 068
c drop old dir hack
e
s 00007/00001/00630
d D 3.49 82/11/04 15:17:35 eric 51 50
m 056
c fix bug in back compat dir code
e
s 00002/00002/00629
d D 3.48 82/11/03 10:29:31 eric 50 49
m 058
c Put temporary file mode on the F option
e
s 00009/00000/00622
d D 3.47 82/11/03 09:00:42 eric 49 48
m 056
c Arrange for queue.c to aapt to systems w/o new directory code
e
s 00001/00001/00621
d D 3.46 82/10/07 00:08:11 eric 48 47
c <ndir.h> => <dir.h> for maximum portability
e
s 00000/00005/00622
d D 3.45 82/09/26 14:46:07 eric 47 46
c completely instantiate queue files for all mail, even if not needed;
c fix a bug that would probably come up once every ten years in creating
c the queue id.  should merge argv flag processing with option processing.
e
s 00007/00002/00620
d D 3.44 82/09/22 10:51:08 eric 46 45
c don't put commas in non-address fields; have -bq clean up its temp files
e
s 00002/00003/00620
d D 3.43 82/09/21 10:10:45 eric 45 44
c output headers with commas into the queue
e
s 00008/00018/00615
d D 3.42 82/09/11 17:18:24 eric 44 43
c don't assign $s to be the sending host (this mucks up Received:
c lines) -- instead just use HELO messages; chdir into queue directory
c and make all pathnames relative; be more conservative in creating
c queue id's -- in the event you get file table overflows, etc.
e
s 00001/00001/00632
d D 3.41 82/09/06 16:24:57 eric 43 42
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00027/00093/00606
d D 3.40 82/08/27 16:04:58 eric 42 41
c simplify timeout code; allow multiple simultaneous queue runs so that
c large messages don't freeze things up; fix EINTR problem in sfgets;
c clean up canonname to be really correct; lots of misc. cleanup
e
s 00002/00002/00697
d D 3.39 82/08/25 11:21:39 eric 41 40
c clean up time manipulation to always be current; assign job
c id's earlier to make sure there is always one with a message.
e
s 00011/00008/00688
d D 3.38 82/08/25 10:46:38 eric 40 39
c log locked files in queuer; don't mistakenly start up two runqueue's
e
s 00002/00002/00694
d D 3.37 82/08/24 19:56:05 eric 39 38
c put queueup log messages on a higher logging level
e
s 00009/00000/00687
d D 3.36 82/08/24 19:41:45 eric 38 37
c log more info (on log level 11); try to detect wild accept loops;
c some minor cleanup and debugging checks; fix NoConnect option to;
c only apply to expensive mailers (regardless of sendqueue order)
e
s 00010/00009/00677
d D 3.35 82/08/23 11:59:57 eric 37 36
c clean up queueing; log time in queue.
c **** This delta invalidates mqueue files ****
e
s 00037/00049/00649
d D 3.34 82/08/22 19:03:33 eric 36 35
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00002/00017/00696
d D 3.33 82/08/17 20:43:18 eric 35 34
c handle folded lines in queue file properly
e
s 00002/00001/00711
d D 3.32 82/08/17 16:15:49 eric 34 33
c don't process core files; process headers properly when running queue.
e
s 00021/00003/00691
d D 3.31 82/08/15 17:34:08 eric 33 32
c make headers work properly when a message is queued up; this involves
c expanding the header before it is written into the queue.  However, it
c also means that we don't have to store the macro definitions (?)
e
s 00017/00002/00677
d D 3.30 82/08/15 11:51:45 eric 32 31
c know about continuation lines in queue files: necessary for headers
e
s 00029/00031/00650
d D 3.29 82/08/08 21:16:07 eric 31 30
c make "sleep" work correctly even in the face of other events; clean
c up the queue processing: child queue runs now go away when done.  more
c debugging logging is needed to verify that this works right though.
e
s 00002/00003/00679
d D 3.28 82/08/08 17:01:50 eric 30 29
c don't give an error when the link fails -- another daemon could have
c grabbed it
e
s 00013/00007/00669
d D 3.27 82/08/08 01:03:57 eric 29 28
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00002/00001/00674
d D 3.26 82/07/27 23:05:04 eric 28 27
c don't attempt delivery if you get an error reading the queue file.
e
s 00032/00027/00643
d D 3.25 82/07/20 19:39:04 eric 27 26
c be smarter about when to rerun the queue when you are in repeated
c queue mode.
e
s 00003/00000/00667
d D 3.24 82/07/14 09:23:31 eric 26 25
c don't accidently unlink a null pointer in finis(); change the way
c it decides whether to do the unlink.
e
s 00005/00002/00662
d D 3.23 82/07/05 20:52:40 eric 25 24
c improve configuration on timeout
e
s 00003/00001/00661
d D 3.22 82/07/05 12:03:12 eric 24 23
c put timeouts on net reads
e
s 00006/00002/00656
d D 3.21 82/07/02 20:52:51 eric 23 22
c arrange to not lose temporary queue control files (tf files)
c if you interrupt a queue run process.
e
s 00001/00000/00657
d D 3.20 82/07/02 10:00:35 eric 22 21
c be paranoid about resetting the "FatalErrors" flag -- always reset
c after forking for daemon or queue mode.  This will prevent false error
c return delivery.
e
s 00004/00004/00653
d D 3.19 82/06/07 07:55:12 eric 21 20
c make transcripts verbose always; misc. message cleanup, etc.
e
s 00001/00001/00656
d D 3.18 82/06/06 23:05:51 eric 20 19
c implement alias owner feature.  this actually works for any user.
c basically, if the alias owner-xxx exists, errors sending to xxx will be
c sent to that alias rather than to the sender.
e
s 00002/00000/00655
d D 3.17 82/05/31 19:03:53 eric 19 18
c make temp files the correct modes in all cases
e
s 00013/00013/00642
d D 3.16 82/05/31 18:51:02 eric 18 17
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00005/00002/00650
d D 3.15 82/05/31 17:11:30 eric 17 16
c eliminate -V, -D, -p flags in favor of a single flag "-bx"
c (be in mode x).
e
s 00005/00003/00647
d D 3.14 82/05/31 15:33:06 eric 16 14
i 15
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00092/00028/00558
d D 3.13.1.1 82/05/29 18:21:25 eric 15 14
c try to install envelopes.  is this really worth it???
e
s 00012/00010/00574
d D 3.13 82/05/22 01:39:09 eric 14 13
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00008/00009/00576
d D 3.12 82/05/05 20:28:12 glickman 13 12
c Modified to use new directory access routines.
e
s 00001/00000/00584
d D 3.11 82/03/06 16:12:25 eric 12 11
c get queue scanning working correctly in conjunction with daemon mode
e
s 00003/00000/00581
d D 3.10 82/02/26 21:56:37 eric 11 10
c implement daemon mode
e
s 00016/00010/00565
d D 3.9 82/02/20 12:05:09 eric 10 9
c don't expand macros in queued requests until delivery time -- means
c passing the macro definitions through also.
e
s 00003/00005/00572
d D 3.8 81/12/06 12:40:54 eric 9 8
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00006/00000/00571
d D 3.7 81/12/05 11:54:23 eric 8 7
c put the SMTP and queueing code on compilation flags so that sendmail
c will fit on non-ID PDP-11's (ugh); put the ugly UUCP hack on a
c compilation flag also to emphasize that it sucks eggs; makefile
c cleanup.
e
s 00032/00047/00539
d D 3.6 81/11/22 19:18:15 eric 7 6
c Edit queue control files when running queue (assuming there are still
c recipients left).  Also, modify the MsgPriority to be the absolute
c number (not the Priority: value); this allows us to include aging into
c the priority algorithm.
e
s 00006/00010/00580
d D 3.5 81/11/21 18:44:24 eric 6 4
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00002/00001/00589
d D 3.4.1.1 81/11/21 15:50:58 eric 5 4
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00006/00006/00584
d D 3.4 81/11/08 17:27:14 eric 4 3
c LINT
e
s 00052/00009/00538
d D 3.3 81/10/27 12:25:14 eric 3 2
c experimental version combining queueing with daemon operation.
c I'm sure this doesn't work -- if only because the wait()s are funny.
e
s 00091/00023/00456
d D 3.2 81/10/27 10:51:23 eric 2 1
c More queueing cleanup: implement timeouts (still one-stage),
c properly implement priorities (didn't work before), and miscellaneous
c cleanup.
e
s 00479/00000/00000
d D 3.1 81/10/27 08:38:53 eric 1 0
c date and time created 81/10/27 08:38:53 by eric
e
u
U
f b 
f i 
t
T
I 84
/*
I 107
D 277
 * Copyright (c) 1983 Eric P. Allman
E 277
I 277
 * Copyright (c) 1983, 1995 Eric P. Allman
E 277
E 107
D 106
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 106
I 106
D 196
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 196
I 196
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 196
 *
D 113
 * Redistribution and use in source and binary forms are permitted
D 107
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 107
I 107
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
E 113
I 113
 * %sccs.include.redist.c%
E 113
E 107
 */
E 106

D 85
#ifndef lint
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 85
D 106

E 106
E 84
I 1
# include "sendmail.h"
I 106

#ifndef lint
#ifdef QUEUE
static char sccsid[] = "%W% (Berkeley) %G% (with queueing)";
#else
static char sccsid[] = "%W% (Berkeley) %G% (without queueing)";
#endif
#endif /* not lint */

E 106
D 186
# include <sys/stat.h>
E 186
D 13
# include <sys/dir.h>
E 13
I 13
D 48
# include <ndir.h>
E 48
I 48
D 78
# include <dir.h>
E 78
I 78
D 191
# include <sys/dir.h>
E 191
I 143
D 163
# include <sys/file.h>
E 163
E 143
I 110
D 142
# include <sys/file.h>
E 142
E 110
E 78
E 48
E 13
I 2
D 202
# include <signal.h>
E 202
E 2
# include <errno.h>
I 111
D 273
# include <pwd.h>
E 273
E 111
I 81
D 82
# ifdef FLOCK
# include <sys/file.h>
# endif FLOCK
E 82
E 81
D 120

I 8
D 106
# ifndef QUEUE
I 87
# ifndef lint
E 87
D 9
static char	SccsId[] =	"%W%	%G%	(no queueing)";
E 9
I 9
D 85
SCCSID(%W%	%Y%	%G%	(no queueing));
E 85
I 85
static char	SccsId[] = "%W% (Berkeley) %G%	(no queueing)";
I 87
# endif not lint
E 87
E 85
E 9
# else QUEUE

I 87
# ifndef lint
E 87
E 8
D 9
static char	SccsId[] =	"%W%	%G%";
E 9
I 9
D 85
SCCSID(%W%	%Y%	%G%);
E 85
I 85
static char	SccsId[] = "%W% (Berkeley) %G%";
I 87
# endif not lint
E 106
I 106
# ifdef QUEUE
E 106
E 87
E 85
E 9

E 120
I 116
D 142
# ifdef LOCKF
E 142
D 120
# include <unistd.h>
E 120
I 120
D 161
# include <fcntl.h>
E 161
E 120
D 142
# endif
E 142
I 141
D 144
# ifdef SYSTEM5
E 144
I 144
D 191
# ifndef MAXNAMLEN
E 191
E 144
# include <dirent.h>
D 191
# endif
E 191
E 141

I 120
# ifdef QUEUE

E 120
E 116
/*
I 56
**  Work queue.
*/

struct work
{
	char		*w_name;	/* name of control file */
I 239
	char		*w_host;	/* name of recipient host */
	bool		w_lock;		/* is message locked? */
E 239
	long		w_pri;		/* priority of message, see below */
I 97
	time_t		w_ctime;	/* creation time of message */
E 97
I 88
D 95
	long		w_ctime;	/* creation time of message */
E 95
E 88
	struct work	*w_next;	/* next in queue */
};

typedef struct work	WORK;
I 110
D 119
extern int la;
E 119
E 110

WORK	*WorkQ;			/* queue of things to be done */
I 246

#define QF_VERSION	1	/* version number of this queue format */
E 246
/*
E 56
**  QUEUEUP -- queue a message up for future transmission.
**
D 56
**	The queued message should already be in the correct place.
**	This routine just outputs the control file as appropriate.
**
E 56
**	Parameters:
D 15
**		df -- location of the data file.  The name will
**			be transformed into a control file name.
E 15
I 15
**		e -- the envelope to queue up.
I 17
**		queueall -- if TRUE, queue all addresses, rather than
**			just those with the QQUEUEUP flag set.
I 56
**		announce -- if TRUE, tell when you are queueing up.
E 56
E 17
E 15
**
**	Returns:
D 110
**		none.
E 110
I 110
D 119
**		locked FILE* to q file
E 119
I 119
**		none.
E 119
E 110
**
**	Side Effects:
D 56
**		The current request (only unsatisfied addresses)
**			are saved in a control file.
E 56
I 56
**		The current request are saved in a control file.
I 119
**		The queue file is left locked.
E 119
E 56
*/

I 283
void
E 283
I 110
D 119
FILE *
E 119
E 110
D 15
queueup(df)
	char *df;
E 15
I 15
D 17
queueup(e)
E 17
I 17
D 56
queueup(e, queueall)
E 56
I 56
queueup(e, queueall, announce)
E 56
E 17
	register ENVELOPE *e;
I 17
	bool queueall;
I 56
	bool announce;
E 56
E 17
E 15
{
D 36
	char cf[MAXNAME];
E 36
I 36
D 112
	char *tf;
E 112
	char *qf;
E 36
D 15
	register FILE *f;
E 15
I 15
D 33
	char buf[MAXNAME];
E 33
I 33
D 112
	char buf[MAXLINE];
E 112
I 112
D 119
	char buf[MAXLINE], tf[MAXLINE];
E 119
E 112
E 33
D 36
	register FILE *cfp;
E 36
I 36
	register FILE *tfp;
E 36
E 15
D 9
	register int i;
E 9
	register HDR *h;
D 9
	register char *p;
E 9
I 6
	register ADDRESS *q;
I 119
	int fd;
	int i;
	bool newid;
I 122
	register char *p;
E 122
E 119
I 69
	MAILER nullmailer;
I 233
	MCI mcibuf;
E 233
I 124
D 183
	ADDRESS *lastctladdr;
E 183
I 125
D 164
	static ADDRESS *nullctladdr = NULL;
E 164
E 125
E 124
I 110
D 112
	int fd;
E 112
I 112
D 119
	int fd, ret;
E 119
I 119
	char buf[MAXLINE], tf[MAXLINE];
I 283
	extern void printctladdr __P((ADDRESS *, FILE *));
E 283
I 122
D 192
	extern char *macvalue();
E 192
I 124
D 183
	extern ADDRESS *getctladdr();
E 183
E 124
E 122
E 119
E 112
E 110
E 69
I 9
D 36
	extern char *mktemp();
E 36
I 10
D 55
	register int i;
E 55
E 10
E 9
E 6

D 7
	/* create control file name from data file name */
	strcpy(cf, df);
	p = rindex(cf, '/');
	if (p == NULL || *++p != 'd')
	{
		syserr("queueup: bad df name %s", df);
		return;
	}
	*p = 'c';
E 7
I 7
	/*
I 125
D 164
	**  If we don't have nullctladdr, create one
	*/

	if (nullctladdr == NULL)
	{
		nullctladdr = (ADDRESS *) xalloc(sizeof *nullctladdr);
		bzero((char *) nullctladdr, sizeof nullctladdr);
	}

	/*
E 164
E 125
D 81
	**  Create control file.
E 81
I 81
D 82
	**  Create control file if necessary.
E 82
I 82
	**  Create control file.
E 82
E 81
	*/
E 7

D 7
	/* create control file */
E 7
I 7
D 18
	strcpy(cf, QueueDir);
D 15
	strcat(cf, "/cfXXXXXX");
E 15
I 15
	strcat(cf, "/tfXXXXXX");
E 18
I 18
D 36
	(void) strcpy(cf, QueueDir);
	(void) strcat(cf, "/tfXXXXXX");
E 18
E 15
	(void) mktemp(cf);
E 7
D 15
	f = fopen(cf, "w");
	if (f == NULL)
E 15
I 15
	cfp = fopen(cf, "w");
	if (cfp == NULL)
E 36
I 36
D 81
	tf = newstr(queuename(e, 't'));
	tfp = fopen(tf, "w");
E 81
I 81
D 82
	tfp = e->e_qfp;
E 82
I 82
D 112
	tf = newstr(queuename(e, 't'));
D 110
	tfp = fopen(tf, "w");
E 82
E 81
	if (tfp == NULL)
E 110
I 110
	fd = open(tf, O_CREAT|O_WRONLY, FileMode);
	if (fd < 0)
E 110
E 36
E 15
	{
D 36
		syserr("queueup: cannot create control file %s", cf);
E 36
I 36
D 81
		syserr("queueup: cannot create temp file %s", tf);
E 36
		return;
E 81
I 81
D 82
		tf = newstr(queuename(e, 't'));
		tfp = fopen(tf, "w");
		if (tfp == NULL)
		{
			syserr("queueup: cannot create temp file %s", tf);
			return;
		}
		(void) chmod(tf, FileMode);
E 82
I 82
		syserr("queueup: cannot create temp file %s", tf);
D 110
		return;
E 110
I 110
		return NULL;
E 110
E 82
E 81
	}
E 112
I 112
D 116
	do {
E 116
I 116
D 119
	do
E 119
I 119
D 218
	newid = (e->e_id == NULL);
E 218
I 218
	newid = (e->e_id == NULL) || !bitset(EF_INQUEUE, e->e_flags);
E 218
I 206

	/* if newid, queuename will create a locked qf file in e->lockfp */
E 206
	strcpy(tf, queuename(e, 't'));
	tfp = e->e_lockfp;
	if (tfp == NULL)
		newid = FALSE;
I 206

	/* if newid, just write the qf file directly (instead of tf file) */
E 206
D 218
	if (newid)
E 218
I 218
	if (!newid)
E 218
E 119
	{
E 116
D 119
		strcpy(tf, queuename(e, 't'));
		fd = open(tf, O_CREAT|O_WRONLY|O_EXCL, FileMode);
D 116
		if (fd < 0) {
			if ( errno != EEXIST) {
E 116
I 116
		if (fd < 0)
E 119
I 119
D 218
		tfp = e->e_lockfp;
	}
	else
	{
E 218
		/* get a locked tf file */
D 203
		for (i = 100; --i >= 0; )
E 203
I 203
		for (i = 0; i < 128; i++)
E 203
E 119
		{
I 120
D 161
# ifdef LOCKF
			struct flock lfd;
# endif
E 161
I 161
D 192
			extern bool lockfile();
E 161

E 192
E 120
D 119
			if (errno != EEXIST)
E 119
I 119
			fd = open(tf, O_CREAT|O_WRONLY|O_EXCL, FileMode);
			if (fd < 0)
E 119
			{
E 116
D 119
				syserr("queueup: cannot create temp file %s",
					tf);
				return NULL;
E 119
I 119
D 203
				if (errno == EEXIST)
					continue;
I 173
notemp:
E 173
D 162
				syserr("queueup: cannot create temp file %s", tf);
				return;
E 162
I 162
				syserr("!queueup: cannot create temp file %s", tf);
E 203
I 203
				if (errno != EEXIST)
					break;
#ifdef LOG
				if (LogLevel > 0 && (i % 32) == 0)
D 225
					syslog(LOG_ALERT, "queueup: cannot create %s: %s",
						tf, errstring(errno));
E 225
I 225
					syslog(LOG_ALERT, "queueup: cannot create %s, uid=%d: %s",
						tf, geteuid(), errstring(errno));
E 225
#endif
D 225
				continue;
E 225
E 203
E 162
E 119
			}
D 116
		} else {
			if (flock(fd, LOCK_EX|LOCK_NB) < 0) {
E 116
I 116
D 119
		}
		else
		{
E 119
D 161
# ifdef LOCKF
D 119
			if (lockf(fd, F_TLOCK, 0) < 0)
			{
D 118
				if (errno != EACCES)
E 118
I 118
				if (errno != EACCES && errno != EAGAIN)
E 118
					syserr("cannot lockf(%s)", tf);
				close(fd);
				fd = -1;
			}
E 119
I 119
D 120
			if (lockf(fd, F_TLOCK, 0) >= 0)
E 120
I 120
			lfd.l_type = F_WRLCK;
			lfd.l_whence = lfd.l_start = lfd.l_len = 0;
			if (fcntl(fd, F_SETLK, &lfd) >= 0)
E 161
I 161
D 225

D 210
			if (lockfile(fd, tf, LOCK_EX|LOCK_NB))
E 210
I 210
			if (lockfile(fd, tf, NULL, LOCK_EX|LOCK_NB))
E 210
E 161
E 120
				break;
E 225
I 225
			else
			{
				if (lockfile(fd, tf, NULL, LOCK_EX|LOCK_NB))
					break;
E 225
I 203
#ifdef LOG
D 225
			else if (LogLevel > 0 && (i % 32) == 0)
				syslog(LOG_ALERT, "queueup: cannot lock %s: %s",
					tf, errstring(errno));
E 225
I 225
				else if (LogLevel > 0 && (i % 32) == 0)
					syslog(LOG_ALERT, "queueup: cannot lock %s: %s",
						tf, errstring(errno));
E 225
#endif
I 225
				close(fd);
			}
E 225
E 203
D 161
			if (errno != EACCES && errno != EAGAIN)
				syserr("cannot lockf(%s)", tf);
E 119
# else
D 119
			if (flock(fd, LOCK_EX|LOCK_NB) < 0)
			{
E 116
				if (errno != EWOULDBLOCK)
					syserr("cannot flock(%s)", tf);
				close(fd);
				fd = -1;
			}
E 119
I 119
			if (flock(fd, LOCK_EX|LOCK_NB) >= 0)
				break;
			if (errno != EWOULDBLOCK)
				syserr("cannot flock(%s)", tf);
E 119
I 116
# endif
E 161
I 161

E 161
I 119
D 225
			close(fd);
I 173
D 203
			sleep(i);
E 203
I 203

E 225
			if ((i % 32) == 31)
			{
				/* save the old temp file away */
				(void) rename(tf, queuename(e, 'T'));
			}
			else
				sleep(i % 32);
E 203
E 173
E 119
E 116
		}
I 173
D 216
		if (fd < 0)
D 203
			goto notemp;
E 203
I 203
			syserr("!queueup: cannot create temp file %s", tf);
E 203
E 173
D 119
	} while (fd < 0);
E 119

E 112
I 19
D 36
	(void) chmod(cf, 0600);
E 36
I 36
D 50
	(void) chmod(tf, 0600);
E 50
I 50
D 81
	(void) chmod(tf, FileMode);
E 81
I 81
D 82
	else
		tf = NULL;
E 82
I 82
D 110
	(void) chmod(tf, FileMode);
E 110
I 110
D 119
	tfp = fdopen(fd, "w");
E 119
I 119
		tfp = fdopen(fd, "w");
E 216
I 216
		if (fd < 0 || (tfp = fdopen(fd, "w")) == NULL)
I 224
		{
			printopenfds(TRUE);
E 224
D 225
			syserr("!queueup: cannot create queue temp file %s", tf);
E 225
I 225
			syserr("!queueup: cannot create queue temp file %s, uid=%d",
				tf, geteuid());
E 225
I 224
		}
E 224
E 216
	}
E 119
E 110
E 82
E 81
E 50
E 36
E 19

D 109
# ifdef DEBUG
E 109
D 29
	if (Debug)
E 29
I 29
	if (tTd(40, 1))
E 29
D 15
		printf("queued in %s\n", cf);
E 15
I 15
D 36
		printf("queueing in %s\n", cf);
E 36
I 36
D 81
		printf("queueing in %s\n", tf);
E 81
I 81
D 208
		printf("queueing %s\n", e->e_id);
E 208
I 208
D 218
		printf("\n>>>>> queueing %s >>>>>\n", e->e_id);
E 218
I 218
D 246
		printf("\n>>>>> queueing %s%s >>>>>\n", e->e_id,
			newid ? " (new id)" : "");
E 246
I 246
		printf("\n>>>>> queueing %s%s queueall=%d >>>>>\n", e->e_id,
			newid ? " (new id)" : "", queueall);
I 272
	if (tTd(40, 3))
	{
		extern void printenvflags();

		printf("  e_flags=");
		printenvflags(e);
	}
E 272
	if (tTd(40, 32))
	{
		printf("  sendq=");
		printaddr(e->e_sendqueue, TRUE);
	}
E 246
	if (tTd(40, 9))
	{
		printf("  tfp=");
		dumpfd(fileno(tfp), TRUE, FALSE);
		printf("  lockfp=");
		if (e->e_lockfp == NULL)
			printf("NULL\n");
		else
			dumpfd(fileno(e->e_lockfp), TRUE, FALSE);
	}
E 218
E 208
E 81
E 36
E 15
D 109
# endif DEBUG
E 109

	/*
I 15
	**  If there is no data file yet, create one.
	*/

D 270
	if (e->e_df == NULL)
E 270
I 270
	if (!bitset(EF_HAS_DF, e->e_flags))
E 270
	{
		register FILE *dfp;
I 270
		char dfname[20];
E 270
I 240
		struct stat stbuf;
E 240
I 58
D 283
		extern putbody();
E 283
E 58

D 18
		strcpy(buf, QueueDir);
		strcat(buf, "/dfXXXXXX");
E 18
I 18
D 36
		(void) strcpy(buf, QueueDir);
		(void) strcat(buf, "/dfXXXXXX");
E 18
		e->e_df = newstr(mktemp(buf));
E 36
I 36
D 204
		e->e_df = newstr(queuename(e, 'd'));
E 204
I 204
D 270
		e->e_df = queuename(e, 'd');
		e->e_df = newstr(e->e_df);
E 204
E 36
D 110
		dfp = fopen(e->e_df, "w");
		if (dfp == NULL)
E 110
I 110
D 236
		fd = open(e->e_df, O_WRONLY|O_CREAT, FileMode);
E 236
I 236
		fd = open(e->e_df, O_WRONLY|O_CREAT|O_TRUNC, FileMode);
E 270
I 270
		strcpy(dfname, queuename(e, 'd'));
		fd = open(dfname, O_WRONLY|O_CREAT|O_TRUNC, FileMode);
E 270
E 236
D 216
		if (fd < 0)
E 110
D 162
		{
			syserr("queueup: cannot create %s", e->e_df);
D 18
			fclose(cfp);
E 18
I 18
D 36
			(void) fclose(cfp);
E 36
I 36
D 119
			(void) fclose(tfp);
E 36
E 18
D 110
			return;
E 110
I 110
			return NULL;
E 119
I 119
			if (!newid)
D 160
				(void) fclose(tfp);
E 160
I 160
				(void) xfclose(tfp, "queueup tfp", e->e_id);
E 160
			return;
E 119
E 110
		}
E 162
I 162
			syserr("!queueup: cannot create %s", e->e_df);
E 162
I 19
D 50
		(void) chmod(e->e_df, 0600);
E 50
I 50
D 110
		(void) chmod(e->e_df, FileMode);
E 110
I 110
		dfp = fdopen(fd, "w");
E 216
I 216
		if (fd < 0 || (dfp = fdopen(fd, "w")) == NULL)
D 225
			syserr("!queueup: cannot create data temp file %s",
				e->e_df);
E 225
I 225
			syserr("!queueup: cannot create data temp file %s, uid=%d",
D 270
				e->e_df, geteuid());
E 270
I 270
				dfname, geteuid());
E 270
I 240
		if (fstat(fd, &stbuf) < 0)
			e->e_dfino = -1;
		else
I 242
		{
			e->e_dfdev = stbuf.st_dev;
E 242
			e->e_dfino = stbuf.st_ino;
I 242
		}
I 270
		e->e_flags |= EF_HAS_DF;
E 270
E 242
E 240
E 225
E 216
E 110
E 50
E 19
D 56
		(*e->e_putbody)(dfp, Mailer[1], FALSE);
E 56
I 56
D 59
		(*e->e_putbody)(dfp, ProgMailer, FALSE);
E 59
I 59
D 62
		(*e->e_putbody)(dfp, ProgMailer, FALSE, e);
E 62
I 62
D 69
		(*e->e_putbody)(dfp, ProgMailer, FALSE, e, FALSE);
E 69
I 69
D 185
		(*e->e_putbody)(dfp, ProgMailer, e);
E 185
I 185
D 190
		(*e->e_putbody)(dfp, FileMailer, e);
E 190
I 190
D 233
		(*e->e_putbody)(dfp, FileMailer, e, NULL);
E 233
I 233
		bzero(&mcibuf, sizeof mcibuf);
		mcibuf.mci_out = dfp;
		mcibuf.mci_mailer = FileMailer;
D 248
		(*e->e_putbody)(&mcibuf, e, NULL);
E 248
I 248
D 256
		(*e->e_putbody)(&mcibuf, e, NULL, 0);
E 256
I 256
		(*e->e_putbody)(&mcibuf, e, NULL);
E 256
E 248
E 233
E 190
E 185
E 69
E 62
E 59
E 56
D 18
		fclose(dfp);
E 18
I 18
D 160
		(void) fclose(dfp);
E 160
I 160
		(void) xfclose(dfp, "queueup dfp", e->e_id);
E 160
I 58
		e->e_putbody = putbody;
E 58
E 18
	}

	/*
E 15
	**  Output future work requests.
I 56
D 102
	**	Priority should be first, since it is read by orderq.
E 102
I 102
	**	Priority and creation time should be first, since
	**	they are required by orderq.
E 102
E 56
	*/

I 246
	/* output queue version number (must be first!) */
	fprintf(tfp, "V%d\n", QF_VERSION);

E 246
I 56
	/* output message priority */
	fprintf(tfp, "P%ld\n", e->e_msgpriority);

I 61
	/* output creation time */
	fprintf(tfp, "T%ld\n", e->e_ctime);

I 240
D 242
	/* output inode number of data file */
I 241
	/* XXX should probably include device major/minor too */
E 241
	fprintf(tfp, "I%ld\n", e->e_dfino);

E 242
	/* output last delivery time */
	fprintf(tfp, "K%ld\n", e->e_dtime);

	/* output number of delivery attempts */
	fprintf(tfp, "N%d\n", e->e_ntries);

I 242
	/* output inode number of data file */
	/* XXX should probably include device major/minor too */
	if (e->e_dfino != -1)
		fprintf(tfp, "I%d/%d/%ld\n",
			major(e->e_dfdev), minor(e->e_dfdev), e->e_dfino);

E 242
E 240
E 61
E 56
D 181
	/* output name of data file */
E 181
I 181
D 270
	/* output type and name of data file */
E 270
I 270
	/* output body type */
E 270
	if (e->e_bodytype != NULL)
		fprintf(tfp, "B%s\n", e->e_bodytype);
E 181
D 15
	fprintf(f, "D%s\n", df);
E 15
I 15
D 36
	fprintf(cfp, "D%s\n", e->e_df);
E 36
I 36
D 270
	fprintf(tfp, "D%s\n", e->e_df);
E 270
E 36
E 15

I 67
	/* message from envelope, if it exists */
	if (e->e_message != NULL)
D 257
		fprintf(tfp, "M%s\n", e->e_message);
E 257
I 257
D 260
		fprintf(tfp, "M%s\n", denlstring(e->e_message));
E 260
I 260
D 262
		fprintf(tfp, "M%s\n", denlstring(e->e_message, FALSE));
E 262
I 262
		fprintf(tfp, "M%s\n", denlstring(e->e_message, TRUE, FALSE));
E 262
E 260
E 257

I 171
	/* send various flag bits through */
	p = buf;
	if (bitset(EF_WARNING, e->e_flags))
		*p++ = 'w';
	if (bitset(EF_RESPONSE, e->e_flags))
		*p++ = 'r';
I 238
	if (bitset(EF_HAS8BIT, e->e_flags))
		*p++ = '8';
E 238
	*p++ = '\0';
	if (buf[0] != '\0')
		fprintf(tfp, "F%s\n", buf);

E 171
I 122
D 180
	/* $r and $s macro values */
E 180
I 180
	/* $r and $s and $_ macro values */
E 180
	if ((p = macvalue('r', e)) != NULL)
D 257
		fprintf(tfp, "$r%s\n", p);
E 257
I 257
D 260
		fprintf(tfp, "$r%s\n", denlstring(p));
E 260
I 260
D 262
		fprintf(tfp, "$r%s\n", denlstring(p, FALSE));
E 262
I 262
		fprintf(tfp, "$r%s\n", denlstring(p, TRUE, FALSE));
E 262
E 260
E 257
	if ((p = macvalue('s', e)) != NULL)
D 257
		fprintf(tfp, "$s%s\n", p);
E 257
I 257
D 260
		fprintf(tfp, "$s%s\n", denlstring(p));
E 260
I 260
D 262
		fprintf(tfp, "$s%s\n", denlstring(p, FALSE));
E 262
I 262
		fprintf(tfp, "$s%s\n", denlstring(p, TRUE, FALSE));
E 262
E 260
E 257
I 180
	if ((p = macvalue('_', e)) != NULL)
D 257
		fprintf(tfp, "$_%s\n", p);
E 257
I 257
D 260
		fprintf(tfp, "$_%s\n", denlstring(p));
E 260
I 260
D 262
		fprintf(tfp, "$_%s\n", denlstring(p, FALSE));
E 262
I 262
		fprintf(tfp, "$_%s\n", denlstring(p, TRUE, FALSE));
E 262
E 260
E 257
E 180

E 122
E 67
	/* output name of sender */
D 14
	fprintf(f, "S%s\n", From.q_paddr);
E 14
I 14
D 15
	fprintf(f, "S%s\n", CurEnv->e_from.q_paddr);
E 15
I 15
D 36
	fprintf(cfp, "S%s\n", e->e_from.q_paddr);
E 36
I 36
D 245
D 258
	fprintf(tfp, "S%s\n", e->e_from.q_paddr);
E 245
I 245
	if (bitnset(M_UDBENVELOPE, e->e_from.q_mailer->m_flags))
		p = e->e_sender;
	else
		p = e->e_from.q_paddr;
D 257
	fprintf(tfp, "S%s\n", p);
E 257
I 257
D 261
	fprintf(tfp, "S%s\n", denlstring(p));
E 258
I 258
D 260
	fprintf(tfp, "S%s\n", denlstring(e->e_from.q_paddr));
E 260
I 260
D 262
	fprintf(tfp, "S%s\n", denlstring(e->e_from.q_paddr, FALSE));
E 262
I 262
D 263
	fprintf(tfp, "S%s\n", denlstring(e->e_from.q_paddr, TRUE, FALSE));
E 262
E 261
I 261
	fprintf(tfp, "S%s\n", denlstring(p, FALSE));
E 263
I 263
	fprintf(tfp, "S%s\n", denlstring(p, TRUE, FALSE));
E 263
E 261
E 260
E 258
E 257
E 245
E 36
E 15
E 14

I 251
	/* output ESMTP-supplied "original" information */
	if (e->e_envid != NULL)
D 257
		fprintf(tfp, "Z%s\n", e->e_envid);
E 257
I 257
D 258
D 261
		fprintf(tfp, "Z%s\n", denlstring(e->e_envid));
E 261
I 261
D 263
		fprintf(tfp, "Z%s\n", denlstring(e->e_envid, FALSE));
E 263
I 263
		fprintf(tfp, "Z%s\n", denlstring(e->e_envid, TRUE, FALSE));
E 263
E 261
E 258
E 257
D 256
	if (e->e_omts != NULL)
		fprintf(tfp, "O%s\n", e->e_omts);
E 256

E 251
D 37
	/* output timeout */
D 15
	fprintf(f, "T%ld\n", TimeOut);
E 15
I 15
D 36
	fprintf(cfp, "T%ld\n", TimeOut);
E 36
I 36
	fprintf(tfp, "T%ld\n", TimeOut);
E 37
I 37
D 61
	/* output creation time */
	fprintf(tfp, "T%ld\n", e->e_ctime);
E 37
E 36
E 15

E 61
I 2
D 56
	/* output message priority */
D 7
	fprintf(f, "P%d\n", MsgPriority);
E 7
I 7
D 14
	fprintf(f, "P%ld\n", MsgPriority);
E 14
I 14
D 15
	fprintf(f, "P%ld\n", CurEnv->e_msgpriority);
E 15
I 15
D 36
	fprintf(cfp, "P%ld\n", e->e_msgpriority);
E 36
I 36
	fprintf(tfp, "P%ld\n", e->e_msgpriority);
E 36
E 15
E 14
E 7

E 56
I 15
D 57
	/* output message class */
D 36
	fprintf(cfp, "C%d\n", e->e_class);
E 36
I 36
	fprintf(tfp, "C%d\n", e->e_class);
E 36

E 57
E 15
I 10
D 54
	/* output macro definitions */
I 33
	/* I don't think this is needed any more.....
E 33
	for (i = 0; i < 128; i++)
	{
D 15
		extern char *Macro[128];
		register char *p = Macro[i];
E 15
I 15
		register char *p = e->e_macro[i];
E 15

		if (p != NULL && i != (int) 'b')
D 15
			fprintf(f, "M%c%s\n", i, p);
E 15
I 15
D 36
			fprintf(cfp, "M%c%s\n", i, p);
E 36
I 36
			fprintf(tfp, "M%c%s\n", i, p);
E 36
E 15
	}
I 33
	.....  */
E 33

E 54
E 10
E 2
D 129
	/* output list of recipient addresses */
E 129
I 129
D 267
	/* output list of error recipients */
E 129
I 124
D 183
	lastctladdr = NULL;
E 183
I 183
D 188
	printctladdr(NULL, tfp);
E 188
I 188
	printctladdr(NULL, NULL);
E 188
E 183
I 129
	for (q = e->e_errorqueue; q != NULL; q = q->q_next)
	{
D 160
		if (!bitset(QDONTSEND, q->q_flags))
E 160
I 160
		if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
E 160
		{
D 183
			ADDRESS *ctladdr;

			ctladdr = getctladdr(q);
D 164
			if (ctladdr == NULL && q->q_alias != NULL)
				ctladdr = nullctladdr;
E 164
			if (ctladdr != lastctladdr)
			{
				printctladdr(ctladdr, tfp);
				lastctladdr = ctladdr;
			}
E 183
I 183
			printctladdr(q, tfp);
E 183
D 257
			fprintf(tfp, "E%s\n", q->q_paddr);
E 257
I 257
D 260
			fprintf(tfp, "E%s\n", denlstring(q->q_paddr));
E 260
I 260
D 262
			fprintf(tfp, "E%s\n", denlstring(q->q_paddr, FALSE));
E 262
I 262
			fprintf(tfp, "E%s\n", denlstring(q->q_paddr, TRUE, FALSE));
E 262
E 260
E 257
		}
	}

E 267
	/* output list of recipient addresses */
I 267
	printctladdr(NULL, NULL);
E 267
E 129
E 124
D 6
	for (i = 0; Mailer[i] != NULL; i++)
E 6
I 6
D 14
	for (q = SendQueue; q != NULL; q = q->q_next)
E 14
I 14
D 15
	for (q = CurEnv->e_sendqueue; q != NULL; q = q->q_next)
E 15
I 15
	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
E 15
E 14
E 6
	{
D 6
		register ADDRESS *q;

		for (q = Mailer[i]->m_sendq; q != NULL; q = q->q_next)
		{
			if (!bitset(QQUEUEUP, q->q_flags))
				continue;
			fprintf(f, "R%s\n", q->q_paddr);
		}
E 6
I 6
D 7
		if (!bitset(QQUEUEUP, q->q_flags))
			continue;
		fprintf(f, "R%s\n", q->q_paddr);
E 7
I 7
D 57
# ifdef DEBUG
D 29
		if (Debug > 0)
E 29
I 29
		if (tTd(40, 1))
E 29
		{
			printf("queueing ");
			printaddr(q, FALSE);
		}
# endif DEBUG
E 57
D 17
		if (bitset(QQUEUEUP, q->q_flags))
E 17
I 17
D 33
		if (queueall || bitset(QQUEUEUP, q->q_flags))
E 33
I 33
D 115
		if (queueall ? !bitset(QDONTSEND, q->q_flags) :
E 115
I 115
D 153
		if (queueall ? !bitset(QDONTSEND|QSENT, q->q_flags) :
E 115
			       bitset(QQUEUEUP, q->q_flags))
E 153
I 153
		if (bitset(QQUEUEUP, q->q_flags) ||
D 160
		    (queueall && !bitset(QDONTSEND|QSENT, q->q_flags)))
E 160
I 160
		    (queueall && !bitset(QDONTSEND|QBADADDR|QSENT, q->q_flags)))
E 160
E 153
I 46
		{
I 111
D 124
			char *ctluser, *getctluser();
E 124
I 124
D 183
			ADDRESS *ctladdr;
E 124

D 124
			if ((ctluser = getctluser(q)) != NULL)
				fprintf(tfp, "C%s\n", ctluser);
E 124
I 124
D 125
			if ((ctladdr = getctladdr(q)) != lastctladdr)
E 125
I 125
			ctladdr = getctladdr(q);
D 164
			if (ctladdr == NULL && q->q_alias != NULL)
				ctladdr = nullctladdr;
E 164
			if (ctladdr != lastctladdr)
E 125
			{
				printctladdr(ctladdr, tfp);
				lastctladdr = ctladdr;
			}
E 183
I 183
			printctladdr(q, tfp);
I 253
			if (q->q_orcpt != NULL)
D 257
				fprintf(tfp, "Q%s\n", q->q_orcpt);
E 257
I 257
D 258
D 261
				fprintf(tfp, "Q%s\n", denlstring(q->q_orcpt));
E 261
I 261
D 263
				fprintf(tfp, "Q%s\n", denlstring(q->q_orcpt, FALSE));
E 263
I 263
				fprintf(tfp, "Q%s\n",
					denlstring(q->q_orcpt, TRUE, FALSE));
E 263
E 261
E 257
E 253
E 183
E 124
E 111
E 46
E 33
E 17
D 15
			fprintf(f, "R%s\n", q->q_paddr);
E 15
I 15
D 36
			fprintf(cfp, "R%s\n", q->q_paddr);
E 36
I 36
D 246
			fprintf(tfp, "R%s\n", q->q_paddr);
E 246
I 246
			putc('R', tfp);
			if (bitset(QPRIMARY, q->q_flags))
				putc('P', tfp);
			if (bitset(QPINGONSUCCESS, q->q_flags))
				putc('S', tfp);
			if (bitset(QPINGONFAILURE, q->q_flags))
				putc('F', tfp);
			if (bitset(QPINGONDELAY, q->q_flags))
				putc('D', tfp);
D 249
			if (bitset(QHASRETPARAM, q->q_flags))
E 249
I 249
D 268
			if (bitset(QHAS_RET_PARAM, q->q_flags))
E 249
			{
D 249
				if (bitset(QNOBODYRETURN, q->q_flags))
E 249
I 249
				if (bitset(QRET_HDRS, q->q_flags))
E 249
					putc('N', tfp);
				else
					putc('B', tfp);
			}
E 268
			putc(':', tfp);
D 257
			fprintf(tfp, "%s\n", q->q_paddr);
E 257
I 257
D 261
			fprintf(tfp, "%s\n", denlstring(q->q_paddr));
E 258
I 258
D 260
			fprintf(tfp, "R%s\n", denlstring(q->q_paddr));
E 260
I 260
D 262
			fprintf(tfp, "R%s\n", denlstring(q->q_paddr, FALSE));
E 262
I 262
D 263
			fprintf(tfp, "R%s\n", denlstring(q->q_paddr, TRUE, FALSE));
E 262
E 261
I 261
			fprintf(tfp, "%s\n", denlstring(q->q_paddr, FALSE));
E 263
I 263
			fprintf(tfp, "%s\n", denlstring(q->q_paddr, TRUE, FALSE));
E 263
E 261
E 260
E 258
E 257
E 246
I 56
			if (announce)
			{
				e->e_to = q->q_paddr;
D 151
				message(Arpa_Info, "queued");
E 151
I 151
				message("queued");
E 151
D 145
				if (LogLevel > 4)
E 145
I 145
				if (LogLevel > 8)
E 145
D 123
					logdelivery("queued");
E 123
I 123
D 157
					logdelivery("queued", e);
E 157
I 157
D 222
					logdelivery(NULL, NULL, "queued", e);
E 222
I 222
D 254
					logdelivery(NULL, NULL, "queued", NULL, e);
E 254
I 254
					logdelivery(NULL, NULL, "queued",
						    NULL, (time_t) 0, e);
E 254
E 222
E 157
E 123
				e->e_to = NULL;
			}
I 57
D 109
#ifdef DEBUG
E 109
			if (tTd(40, 1))
			{
				printf("queueing ");
				printaddr(q, FALSE);
			}
D 109
#endif DEBUG
E 109
E 57
E 56
I 46
		}
E 46
E 36
E 15
E 7
E 6
	}

I 102
D 129
	/* output list of error recipients */
	for (q = e->e_errorqueue; q != NULL; q = q->q_next)
	{
D 103
		fprintf(tfp, "E%s\n", q->q_paddr);
E 103
I 103
		if (!bitset(QDONTSEND, q->q_flags))
I 111
		{
D 124
			char *ctluser, *getctluser();
E 124
I 124
			ADDRESS *ctladdr;
E 124

D 124
			if ((ctluser = getctluser(q)) != NULL)
				fprintf(tfp, "C%s\n", ctluser);
E 124
I 124
D 125
			if ((ctladdr = getctladdr(q)) != lastctladdr)
E 125
I 125
			ctladdr = getctladdr(q);
			if (ctladdr == NULL && q->q_alias != NULL)
				ctladdr = nullctladdr;
			if (ctladdr != lastctladdr)
E 125
			{
				printctladdr(ctladdr, tfp);
				lastctladdr = ctladdr;
			}
E 124
E 111
			fprintf(tfp, "E%s\n", q->q_paddr);
I 111
		}
E 111
E 103
	}

E 129
E 102
D 56
	/* output headers for this message */
I 33
	define('g', "$f");
E 56
I 56
	/*
	**  Output headers for this message.
	**	Expand macros completely here.  Queue run will deal with
	**	everything as absolute headers.
	**		All headers that must be relative to the recipient
	**		can be cracked later.
I 69
	**	We set up a "null mailer" -- i.e., a mailer that will have
	**	no effect on the addresses as they are output.
E 69
	*/

I 69
D 73
	bzero(&nullmailer, sizeof nullmailer);
E 73
I 73
	bzero((char *) &nullmailer, sizeof nullmailer);
E 73
D 145
	nullmailer.m_r_rwset = nullmailer.m_s_rwset = -1;
E 145
I 145
	nullmailer.m_re_rwset = nullmailer.m_rh_rwset =
D 219
			nullmailer.m_se_rwset = nullmailer.m_sh_rwset = -1;
E 219
I 219
D 231
			nullmailer.m_se_rwset = nullmailer.m_sh_rwset = 0;
E 231
I 231
			nullmailer.m_se_rwset = nullmailer.m_sh_rwset = -1;
E 231
E 219
E 145
I 72
	nullmailer.m_eol = "\n";
I 233
	bzero(&mcibuf, sizeof mcibuf);
	mcibuf.mci_mailer = &nullmailer;
	mcibuf.mci_out = tfp;
E 233
E 72

E 69
D 80
	define('g', "$f", e);
E 80
I 80
D 146
	define('g', "\001f", e);
E 146
I 146
	define('g', "\201f", e);
E 146
E 80
E 56
E 33
D 14
	for (h = Header; h != NULL; h = h->h_link)
E 14
I 14
D 15
	for (h = CurEnv->e_header; h != NULL; h = h->h_link)
E 15
I 15
	for (h = e->e_header; h != NULL; h = h->h_link)
E 15
E 14
	{
I 73
		extern bool bitzerop();

I 75
		/* don't output null headers */
E 75
E 73
		if (h->h_value == NULL || h->h_value[0] == '\0')
			continue;
I 75

		/* don't output resent headers on non-resent messages */
		if (bitset(H_RESENT, h->h_flags) && !bitset(EF_RESENT, e->e_flags))
			continue;

I 230
		/* expand macros; if null, don't output header at all */
		if (bitset(H_DEFAULT, h->h_flags))
		{
D 266
			(void) expand(h->h_value, buf, &buf[sizeof buf], e);
E 266
I 266
			(void) expand(h->h_value, buf, sizeof buf, e);
E 266
			if (buf[0] == '\0')
				continue;
		}

E 230
		/* output this header */
E 75
D 15
		fprintf(f, "H");
E 15
I 15
D 36
		fprintf(cfp, "H");
E 36
I 36
		fprintf(tfp, "H");
I 75

		/* if conditional, output the set of conditions */
E 75
E 36
E 15
D 73
		if (h->h_mflags != 0 && bitset(H_CHECK|H_ACHECK, h->h_flags))
D 15
			mfdecode(h->h_mflags, f);
D 10
		fprintf(f, "%s: ", h->h_field);
		if (bitset(H_DEFAULT, h->h_flags))
		{
			char buf[MAXLINE];

			(void) expand(h->h_value, buf, &buf[sizeof buf]);
			fprintf(f, "%s\n", buf);
		}
		else
			fprintf(f, "%s\n", h->h_value);
E 10
I 10
		fprintf(f, "%s: %s\n", h->h_field, h->h_value);
E 15
I 15
D 36
			mfdecode(h->h_mflags, cfp);
D 33
		fprintf(cfp, "%s: %s\n", h->h_field, h->h_value);
E 33
I 33
		fprintf(cfp, "%s: ", h->h_field);
E 36
I 36
			mfdecode(h->h_mflags, tfp);
E 73
I 73
		if (!bitzerop(h->h_mflags) && bitset(H_CHECK|H_ACHECK, h->h_flags))
		{
			int j;

D 86
			putc('?', tfp);
E 86
I 86
			(void) putc('?', tfp);
E 86
			for (j = '\0'; j <= '\177'; j++)
				if (bitnset(j, h->h_mflags))
D 86
					putc(j, tfp);
			putc('?', tfp);
E 86
I 86
					(void) putc(j, tfp);
			(void) putc('?', tfp);
E 86
		}
I 75

		/* output the header: expand macros, convert addresses */
E 75
E 73
D 45
		fprintf(tfp, "%s: ", h->h_field);
E 45
E 36
		if (bitset(H_DEFAULT, h->h_flags))
		{
D 230
			(void) expand(h->h_value, buf, &buf[sizeof buf], e);
D 36
			fprintf(cfp, "%s\n", buf);
E 36
I 36
D 45
			fprintf(tfp, "%s\n", buf);
E 45
I 45
D 227
			fprintf(tfp, "%s: %s\n", h->h_field, buf);
E 227
I 227
			if (buf[0] != '\0')
				fprintf(tfp, "%s: %s\n", h->h_field, buf);
E 230
I 230
			fprintf(tfp, "%s: %s\n", h->h_field, buf);
E 230
E 227
E 45
E 36
		}
D 46
		else
E 46
I 46
		else if (bitset(H_FROM|H_RCPT, h->h_flags))
E 46
D 36
			fprintf(cfp, "%s\n", h->h_value);
E 36
I 36
D 45
			fprintf(tfp, "%s\n", h->h_value);
E 45
I 45
D 54
			commaize(h, h->h_value, tfp, e->e_oldstyle, NULL);
E 54
I 54
D 55
			commaize(h, h->h_value, tfp,
				 bitset(EF_OLDSTYLE, e->e_flags), NULL);
E 55
I 55
		{
D 126
			commaize(h, h->h_value, tfp, bitset(EF_OLDSTYLE, e->e_flags),
D 62
				 (MAILER *) NULL);
E 62
I 62
D 69
				 (MAILER *) NULL, FALSE);
E 69
I 69
				 &nullmailer);
E 126
I 126
D 171
			commaize(h, h->h_value, tfp,
				 bitset(EF_OLDSTYLE, e->e_flags),
E 171
I 171
			bool oldstyle = bitset(EF_OLDSTYLE, e->e_flags);
I 197
			FILE *savetrace = TrafficLogFile;
E 197

I 197
			TrafficLogFile = NULL;

E 197
			if (bitset(H_FROM, h->h_flags))
				oldstyle = FALSE;

D 233
			commaize(h, h->h_value, tfp, oldstyle,
E 171
				 &nullmailer, e);
E 233
I 233
			commaize(h, h->h_value, oldstyle, &mcibuf, e);
E 233
I 197

			TrafficLogFile = savetrace;
E 197
E 126
E 69
E 62
		}
E 55
E 54
I 46
		else
			fprintf(tfp, "%s: %s\n", h->h_field, h->h_value);
E 46
E 45
E 36
E 33
E 15
E 10
	}

	/*
	**  Clean up.
I 286
	**
	**	Write a terminator record -- this is to prevent
	**	scurrilous crackers from appending any data.
E 286
	*/

I 286
	fprintf(tfp, ".\n");

E 286
I 169
D 220
	fflush(tfp);
I 194
	fsync(fileno(tfp));
E 194
	if (ferror(tfp))
E 220
I 220
	if (fflush(tfp) < 0 || fsync(fileno(tfp)) < 0 || ferror(tfp))
E 220
	{
		if (newid)
			syserr("!552 Error writing control file %s", tf);
		else
			syserr("!452 Error writing control file %s", tf);
	}

E 169
I 82
D 110
	(void) fclose(tfp);
E 110
I 110
D 112
	if (flock(fileno(tfp), LOCK_EX|LOCK_NB) < 0)
	{
		syserr("cannot flock(%s)", tf);
	}

E 112
E 110
E 82
D 15
	(void) fclose(f);
E 15
I 15
D 36
	(void) fclose(cfp);
	(void) strcpy(buf, QueueDir);
	(void) strcat(buf, "/cfXXXXXX");
	(void) mktemp(buf);
	if (link(cf, buf) < 0)
		syserr("cannot link(%s, %s), df=%s", cf, buf, e->e_df);
E 36
I 36
D 81
	(void) fclose(tfp);
E 81
D 119
	qf = queuename(e, 'q');
I 56
D 81
	holdsigs();
E 56
	(void) unlink(qf);
	if (link(tf, qf) < 0)
		syserr("cannot link(%s, %s), df=%s", tf, qf, e->e_df);
E 36
	else
D 18
		unlink(cf);
E 18
I 18
D 36
		(void) unlink(cf);
E 36
I 36
		(void) unlink(tf);
I 56
	rlsesigs();
E 81
I 81
D 112
	if (tf != NULL)
	{
D 82
# ifdef FLOCK
		(void) flock(fileno(tfp), LOCK_EX|LOCK_NB);
		if (rename(tf, qf) < 0)
			syserr("cannot rename(%s, %s), df=%s", tf, qf, e->e_df);
# else FLOCK
E 82
D 93
		holdsigs();
E 93
		(void) unlink(qf);
D 93
		if (link(tf, qf) < 0)
			syserr("cannot link(%s, %s), df=%s", tf, qf, e->e_df);
		else
			(void) unlink(tf);
		rlsesigs();
E 93
I 93
		if (rename(tf, qf) < 0)
D 110
			syserr("cannot unlink(%s, %s), df=%s", tf, qf, e->e_df);
E 110
I 110
			syserr("cannot rename(%s, %s), df=%s", tf, qf, e->e_df);
E 110
		errno = 0;
E 93
D 82
# endif FLOCK
E 82
	}
E 112
I 112
	if (rename(tf, qf) < 0)
		syserr("cannot rename(%s, %s), df=%s", tf, qf, e->e_df);
E 119
I 119
	if (!newid)
	{
I 206
		/* rename (locked) tf to be (locked) qf */
E 206
		qf = queuename(e, 'q');
		if (rename(tf, qf) < 0)
D 225
			syserr("cannot rename(%s, %s), df=%s", tf, qf, e->e_df);
E 225
I 225
D 270
			syserr("cannot rename(%s, %s), df=%s, uid=%d",
				tf, qf, e->e_df, geteuid());
E 270
I 270
			syserr("cannot rename(%s, %s), uid=%d",
				tf, qf, geteuid());
E 270
E 225
I 206

		/* close and unlock old (locked) qf */
E 206
		if (e->e_lockfp != NULL)
D 160
			(void) fclose(e->e_lockfp);
E 160
I 160
			(void) xfclose(e->e_lockfp, "queueup lockfp", e->e_id);
E 160
		e->e_lockfp = tfp;
	}
	else
		qf = tf;
E 119
	errno = 0;
I 218
	e->e_flags |= EF_INQUEUE;
E 218
E 112
D 82
	(void) fclose(tfp);
	e->e_qfp = NULL;
E 82
E 81
E 56
D 47
	e->e_qf = NULL;
E 47
E 36
I 26

I 29
# ifdef LOG
	/* save log info */
D 39
	if (LogLevel > 9)
D 36
		syslog(LOG_INFO, "%s queueup: cf=%s, df=%s\n", MsgId, buf, e->e_df);
E 36
I 36
		syslog(LOG_INFO, "%s queueup: qf=%s, df=%s\n", e->e_id, qf, e->e_df);
E 39
I 39
D 145
	if (LogLevel > 15)
E 145
I 145
	if (LogLevel > 79)
E 145
D 270
		syslog(LOG_DEBUG, "%s: queueup, qf=%s, df=%s\n", e->e_id, qf, e->e_df);
E 270
I 270
		syslog(LOG_DEBUG, "%s: queueup, qf=%s", e->e_id, qf);
E 270
E 39
E 36
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
I 208

	if (tTd(40, 1))
		printf("<<<<< done queueing %s <<<<<\n\n", e->e_id);
E 208
E 133
I 110
D 194
	fflush(tfp);
E 194
D 119
	return tfp;
E 119
I 119
	return;
E 119
E 110
D 47

E 29
D 46
	/* disconnect this temp file from the job */
E 46
I 46
	/* disconnect this temp file from the job; don't requeue later */
E 46
	e->e_df = NULL;
I 46
	e->e_dontqueue = TRUE;
E 47
E 46
E 26
E 18
E 15
}
I 124

I 283
void
E 283
printctladdr(a, tfp)
D 183
	ADDRESS *a;
E 183
I 183
	register ADDRESS *a;
E 183
	FILE *tfp;
{
D 183
	char *u;
	struct passwd *pw;
	extern struct passwd *getpwuid();
E 183
I 183
	char *uname;
	register struct passwd *pw;
	register ADDRESS *q;
	uid_t uid;
	static ADDRESS *lastctladdr;
	static uid_t lastuid;
D 192
	extern ADDRESS *getctladdr();
E 192
E 183

I 183
	/* initialization */
E 183
D 188
	if (a == NULL)
E 188
I 188
D 200
	if (a == NULL || tfp == NULL)
E 200
I 200
	if (a == NULL || a->q_alias == NULL || tfp == NULL)
E 200
E 188
	{
D 183
		fprintf(tfp, "C\n");
E 183
I 183
D 188
		if (lastctladdr != NULL)
E 188
I 188
		if (lastctladdr != NULL && tfp != NULL)
E 188
			fprintf(tfp, "C\n");
		lastctladdr = NULL;
		lastuid = 0;
E 183
		return;
	}
D 183
	if (a->q_uid == 0 || (pw = getpwuid(a->q_uid)) == NULL)
		u = DefUser;
E 183
I 183

	/* find the active uid */
	q = getctladdr(a);
	if (q == NULL)
		uid = 0;
E 183
	else
D 183
		u = pw->pw_name;
	fprintf(tfp, "C%s\n", u);
E 183
I 183
		uid = q->q_uid;
I 200
	a = a->q_alias;
E 200

D 200
	/* if a is an alias, use that for printing */
	if (a->q_alias != NULL)
		a = a->q_alias;

E 200
	/* check to see if this is the same as last time */
	if (lastctladdr != NULL && uid == lastuid &&
	    strcmp(lastctladdr->q_paddr, a->q_paddr) == 0)
		return;
	lastuid = uid;
	lastctladdr = a;

D 273
	if (uid == 0 || (pw = getpwuid(uid)) == NULL)
E 273
I 273
	if (uid == 0 || (pw = sm_getpwuid(uid)) == NULL)
E 273
D 184
		uname = DefUser;
E 184
I 184
		uname = "";
E 184
	else
		uname = pw->pw_name;

D 257
	fprintf(tfp, "C%s:%s\n", uname, a->q_paddr);
E 257
I 257
D 260
	fprintf(tfp, "C%s:%s\n", uname, denlstring(a->q_paddr));
E 260
I 260
D 262
	fprintf(tfp, "C%s:%s\n", uname, denlstring(a->q_paddr, FALSE));
E 262
I 262
	fprintf(tfp, "C%s:%s\n", uname, denlstring(a->q_paddr, TRUE, FALSE));
E 262
E 260
E 257
E 183
}
D 246

E 246
E 124
/*
**  RUNQUEUE -- run the jobs in the queue.
**
**	Gets the stuff out of the queue in some presumably logical
**	order and processes them.
**
**	Parameters:
D 88
**		none.
E 88
I 88
**		forkflag -- TRUE if the queue scanning should be done in
**			a child process.  We double-fork so it is not our
**			child and we don't have to clean up after it.
E 88
**
**	Returns:
**		none.
**
**	Side Effects:
**		runs things in the mail queue.
*/

I 2
D 3
bool	ReorderQueue;
E 3
I 3
D 42
bool	ReorderQueue;		/* if set, reorder the send queue */
int	QueuePid;		/* pid of child running queue */
E 3

E 42
E 2
D 3
runqueue()
E 3
I 3
D 126
runqueue(forkflag)
E 126
I 126
D 129
runqueue(forkflag, e)
E 129
I 129
ENVELOPE	QueueEnvelope;		/* the queue run envelope */

I 259
void
E 259
runqueue(forkflag)
E 129
E 126
	bool forkflag;
I 126
D 129
	register ENVELOPE *e;
E 129
E 126
E 3
{
I 89
D 192
	extern bool shouldqueue();
E 192
I 129
	register ENVELOPE *e;
I 247
	int njobs;
	int sequenceno = 0;
E 247
	extern ENVELOPE BlankEnvelope;
D 192
	extern ENVELOPE *newenvelope();
E 192
E 129

E 89
D 2
	/*
	**  Order the existing work requests.
	*/
E 2
I 2
D 42
	extern reordersig();
E 42
I 42
D 56
	register int i;
E 42
E 2

E 56
I 3
D 27
	if (QueueIntvl != 0)
	{
D 4
		signal(SIGALRM, reordersig);
		alarm(QueueIntvl);
E 4
I 4
		(void) signal(SIGALRM, reordersig);
D 18
		(void) alarm((unsigned) QueueIntvl);
E 18
I 18
		(void) alarm(QueueIntvl);
E 18
E 4
	}
E 27
I 27
	/*
I 89
	**  If no work will ever be selected, don't even bother reading
	**  the queue.
	*/

I 110
D 119
	la = getla();	/* get load average */
E 119
I 119
	CurrentLA = getla();	/* get load average */
E 119

E 110
D 136
	if (shouldqueue(-100000000L))
E 136
I 136
D 150
	if (shouldqueue(-100000000L, curtime()))
E 150
I 150
	if (shouldqueue(0L, curtime()))
E 150
E 136
	{
I 278
		char *msg = "Skipping queue run -- load average too high";

E 278
		if (Verbose)
D 278
			printf("Skipping queue run -- load average too high\n");
E 278
I 278
			printf("%s\n", msg);
#ifdef LOG
		if (LogLevel > 8)
			syslog(LOG_INFO, "runqueue: %s", msg);
#endif
E 278
I 149
		if (forkflag && QueueIntvl != 0)
			(void) setevent(QueueIntvl, runqueue, TRUE);
E 149
D 129

		if (forkflag)
			return;
		finis();
E 129
I 129
		return;
E 129
	}

	/*
E 89
	**  See if we want to go off and do other useful work.
	*/
E 27

	if (forkflag)
	{
D 42
		QueuePid = dofork();
		if (QueuePid > 0)
E 42
I 42
		int pid;
I 229
#ifdef SIGCHLD
		extern void reapchild();
E 229

I 229
		(void) setsignal(SIGCHLD, reapchild);
#endif

E 229
		pid = dofork();
		if (pid != 0)
E 42
		{
I 100
D 114
			extern reapchild();
E 114
I 114
D 229
			extern void reapchild();
E 114

E 229
E 100
D 42
			/* parent */
E 42
I 42
			/* parent -- pick up intermediate zombie */
I 100
#ifndef SIGCHLD
E 100
D 56
			do
			{
				auto int stat;

				i = wait(&stat);
			} while (i >= 0 && i != pid);
E 56
I 56
			(void) waitfor(pid);
I 285
#else
			CurChildren++;
E 285
I 100
D 133
#else SIGCHLD
E 133
I 133
D 229
#else /* SIGCHLD */
E 133
D 202
			(void) signal(SIGCHLD, reapchild);
E 202
I 202
			(void) setsignal(SIGCHLD, reapchild);
E 229
E 202
D 133
#endif SIGCHLD
E 133
I 133
#endif /* SIGCHLD */
E 133
E 100
E 56
E 42
I 31
			if (QueueIntvl != 0)
D 42
				setevent(QueueIntvl, reordersig, TRUE);
E 42
I 42
D 55
				setevent(QueueIntvl, runqueue, TRUE);
E 55
I 55
				(void) setevent(QueueIntvl, runqueue, TRUE);
E 55
E 42
E 31
			return;
		}
I 42
		/* child -- double fork */
I 100
#ifndef SIGCHLD
E 100
		if (fork() != 0)
			exit(EX_OK);
I 100
D 133
#else SIGCHLD
E 133
I 133
#else /* SIGCHLD */
E 133
D 202
		(void) signal(SIGCHLD, SIG_DFL);
E 202
I 202
		(void) setsignal(SIGCHLD, SIG_DFL);
E 202
D 133
#endif SIGCHLD
E 133
I 133
#endif /* SIGCHLD */
E 133
E 100
E 42
D 31
		else
D 4
			alarm(0);
E 4
I 4
D 18
			(void) alarm((unsigned) 0);
E 18
I 18
			(void) alarm(0);
E 31
E 18
E 4
	}
I 88

D 110
	setproctitle("running queue");
E 110
I 110
	setproctitle("running queue: %s", QueueDir);
I 140
D 154
	ForceMail = TRUE;
E 154
E 140
E 110

E 88
I 38
# ifdef LOG
D 145
	if (LogLevel > 11)
E 145
I 145
	if (LogLevel > 69)
E 145
D 42
		syslog(LOG_DEBUG, "runqueue, pid=%d", getpid());
E 42
I 42
D 129
		syslog(LOG_DEBUG, "runqueue %s, pid=%d", QueueDir, getpid());
E 129
I 129
		syslog(LOG_DEBUG, "runqueue %s, pid=%d, forkflag=%d",
			QueueDir, getpid(), forkflag);
E 129
E 42
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
E 133
E 38

E 3
D 2
	orderq();
E 2
I 2
D 27
	for (;;)
E 27
I 27
	/*
I 71
	**  Release any resources used by the daemon code.
	*/

# ifdef DAEMON
	clrdaemon();
D 133
# endif DAEMON
E 133
I 133
# endif /* DAEMON */
E 133

I 214
	/* force it to run expensive jobs */
	NoConnect = FALSE;

E 214
	/*
I 129
	**  Create ourselves an envelope
	*/

	CurEnv = &QueueEnvelope;
D 152
	e = newenvelope(&QueueEnvelope);
E 152
I 152
	e = newenvelope(&QueueEnvelope, CurEnv);
E 152
	e->e_flags = BlankEnvelope.e_flags;

	/*
E 129
I 104
	**  Make sure the alias database is open.
	*/

D 126
	initaliases(AliasFile, FALSE);
E 126
I 126
D 188
	initaliases(AliasFile, FALSE, e);
E 188
I 188
D 193
	initaliases(FALSE, e);
E 193
I 193
	initmaps(FALSE, e);
E 193
E 188
E 126

	/*
E 104
E 71
D 31
	**  Arrange to reorder the queue at polite intervals.
	*/

	if (QueueIntvl != 0)
E 27
	{
D 27
		/*
		**  Order the existing work requests.
		*/
E 27
I 27
		(void) signal(SIGALRM, reordersig);
		(void) alarm(QueueIntvl);
	}
E 27
E 2

D 2
	/*
	**  Process them once at a time.
	**	The queue could be reordered while we do this to take
	**	new requests into account.  If so, the existing job
	**	will be finished but the next thing taken off WorkQ
	**	may be something else.
	*/
E 2
I 2
D 27
		orderq();
E 27
I 27
	/*
E 31
	**  Start making passes through the queue.
	**	First, read and sort the entire queue.
	**	Then, process the work in that order.
	**		But if you take too long, start over.
D 42
	**	There is a race condition at the end -- we could get
	**		a reorder signal after finishing the queue.
	**		In this case we will hang for one more queue
	**		interval -- clearly a botch, but rare and
	**		relatively innocuous.
E 42
	*/
E 27
E 2

D 2
	while (WorkQ != NULL)
	{
		WORK *w = WorkQ;
E 2
I 2
D 27
		if (WorkQ == NULL)
		{
			/* no work?  well, maybe later */
			if (QueueIntvl == 0)
				break;
D 3
			sleep(QueueIntvl);
E 3
I 3
			pause();
E 3
			continue;
		}
E 2

E 27
I 27
D 42
	for (;;)
	{
		/* order the existing work requests */
		orderq();
E 42
I 42
	/* order the existing work requests */
D 63
	orderq();
E 63
I 63
D 90
	(void) orderq();
E 90
I 90
D 247
	(void) orderq(FALSE);
E 247
I 247
	njobs = orderq(FALSE);
E 247
E 90
E 63
E 42
I 31

D 42
		/* arrange to reorder later */
E 31
E 27
D 2
		WorkQ = WorkQ->w_next;
		dowork(w);
		free(w->w_name);
		free((char *) w);
E 2
I 2
		ReorderQueue = FALSE;
I 31
		if (QueueIntvl != 0)
			setevent(QueueIntvl, reordersig, FALSE);
E 31
D 3
		if (QueueIntvl != 0)
		{
			signal(SIGALRM, reordersig);
			alarm(QueueIntvl);
		}
E 3

D 27
		/*
		**  Process them once at a time.
		**	The queue could be reordered while we do this to take
		**	new requests into account.  If so, the existing job
		**	will be finished but the next thing taken off WorkQ
		**	may be something else.
		*/

E 27
I 27
		/* process them once at a time */
E 27
		while (WorkQ != NULL)
		{
			WORK *w = WorkQ;

			WorkQ = WorkQ->w_next;
			dowork(w);
			free(w->w_name);
			free((char *) w);
			if (ReorderQueue)
				break;
		}

I 27
		/* if we are just doing one pass, then we are done */
E 27
		if (QueueIntvl == 0)
D 31
			break;
E 31
I 31
			finis();
E 31
I 27

		/* wait for work -- note (harmless) race condition here */
D 31
		if (!ReorderQueue)
E 31
I 31
		while (!ReorderQueue)
		{
			if (forkflag)
				finis();
E 31
			pause();
I 31
		}
E 31
E 27
E 2
	}
I 11
D 31

	/* no work to do -- just exit */
	finis();
E 31
E 11
}
/*
I 2
D 31
**  REORDERSIG -- catch the alarm signal and tell sendmail to reorder queue.
E 31
I 31
**  REORDERSIG -- catch the reorder signal and tell sendmail to reorder queue.
E 31
**
**	Parameters:
D 31
**		none.
E 31
I 31
**		parent -- if set, called from parent (i.e., not
**			really doing the work).
E 31
**
**	Returns:
**		none.
**
**	Side Effects:
**		sets the "reorder work queue" flag.
*/

D 31
reordersig()
E 31
I 31
reordersig(parent)
	bool parent;
E 31
{
D 3
	ReorderQueue = TRUE;
E 3
I 3
D 31
	if (QueuePid == 0)
E 31
I 31
	if (!parent)
E 42
I 42
	/* process them once at a time */
	while (WorkQ != NULL)
E 42
E 31
	{
D 42
		/* we are in a child doing queueing */
		ReorderQueue = TRUE;
E 42
I 42
		WORK *w = WorkQ;
I 174
D 192
		extern bool shouldqueue();
E 192
E 174
E 42
I 40

D 42
		/* arrange to get this signal again */
		setevent(QueueIntvl, reordersig, FALSE);
E 42
I 42
		WorkQ = WorkQ->w_next;
D 126
		dowork(w);
E 126
I 126
D 174
		dowork(w, e);
E 174
I 174

		/*
		**  Ignore jobs that are too expensive for the moment.
		*/

I 247
		sequenceno++;
E 247
		if (shouldqueue(w->w_pri, w->w_ctime))
		{
			if (Verbose)
D 247
				printf("\nSkipping %s\n", w->w_name + 2);
E 247
I 247
				printf("\nSkipping %s (sequence %d of %d)\n",
					w->w_name + 2, sequenceno, njobs);
E 247
D 175
			return;
E 175
I 175
D 179
			continue;
E 179
E 175
		}
D 179

D 177
		dowork(w->w_name + 2, ForkQueueRuns, e);
E 177
I 177
		dowork(w->w_name + 2, ForkQueueRuns, FALSE, e);
E 179
I 179
		else
		{
D 207
			dowork(w->w_name + 2, ForkQueueRuns, FALSE, e);
E 207
I 207
			pid_t pid;
			extern pid_t dowork();

I 247
			if (Verbose)
				printf("\nRunning %s (sequence %d of %d)\n",
					w->w_name + 2, sequenceno, njobs);
E 247
			pid = dowork(w->w_name + 2, ForkQueueRuns, FALSE, e);
			errno = 0;
D 235
			(void) waitfor(pid);
E 235
I 235
			if (pid != 0)
				(void) waitfor(pid);
E 235
E 207
		}
E 179
E 177
E 174
E 126
		free(w->w_name);
I 239
		if (w->w_host)
			free(w->w_host);
E 239
		free((char *) w);
E 42
E 40
	}
D 42
	else
	{
D 31
		/* we are in a parent -- poke child or start new one */
E 31
I 31
		/*
		**  In parent.  If the child still exists, we want
		**  to do nothing.  If the child is gone, we will
		**  start up a new one.
		**  If the child exists, it is responsible for
		**  doing a queue reorder.
		**  This code really sucks.
		*/

E 31
		if (kill(QueuePid, SIGALRM) < 0)
		{
			/* no child -- get zombie & start new one */
			static int st;

D 4
			wait(&st);
E 4
I 4
			(void) wait(&st);
E 4
D 31
			QueuePid = dofork();
			if (QueuePid == 0)
			{
				/* new child; run queue */
D 4
				runqueue();
E 4
I 4
				runqueue(FALSE);
E 4
				finis();
			}
E 31
I 31
			runqueue(TRUE);
E 31
		}
I 40
		else
			setevent(QueueIntvl, reordersig, TRUE);
E 40
	}
E 42
I 42
D 105
	finis();
E 105
I 105

	/* exit without the usual cleanup */
D 130
	exit(ExitStat);
E 130
I 130
	e->e_id = NULL;
	finis();
E 130
E 105
E 42
D 40

	/*
	**  Arrange to get this signal again.
	*/

I 12
D 31
	(void) signal(SIGALRM, reordersig);
E 12
D 4
	alarm(QueueIntvl);
E 4
I 4
D 18
	(void) alarm((unsigned) QueueIntvl);
E 18
I 18
	(void) alarm(QueueIntvl);
E 31
I 31
	setevent(QueueIntvl, reordersig, parent);
E 40
E 31
E 18
E 4
E 3
}
/*
E 2
**  ORDERQ -- order the work queue.
**
**	Parameters:
D 88
**		none.
E 88
I 88
**		doall -- if set, include everything in the queue (even
**			the jobs that cannot be run because the load
**			average is too high).  Otherwise, exclude those
**			jobs.
E 88
**
**	Returns:
D 68
**		none.
E 68
I 68
**		The number of request in the queue (not necessarily
**		the number of requests in WorkQ however).
E 68
**
**	Side Effects:
**		Sets WorkQ to the queue of available work, in order.
*/

D 102
# define WLSIZE		120	/* max size of worklist per sort */
E 102
I 102
# define NEED_P		001
# define NEED_T		002
I 155
# define NEED_R		004
# define NEED_S		010
E 155
E 102

I 280
static WORK	*WorkList = NULL;
static int	WorkListSize = 0;

I 283
int
E 283
E 280
I 49
# ifndef DIR
# define DIR		FILE
# define direct		dir
# define opendir(d)	fopen(d, "r")
D 51
# define readdir(f)	(fread(dbuf, sizeof dbuf, 1, f) > 0 ? &dbuf : 0)
E 51
I 51
# define readdir(f)	((fread(&dbuf, sizeof dbuf, 1, f) > 0) ? &dbuf : 0)
E 51
static struct dir	dbuf;
# define closedir(f)	fclose(f)
# endif DIR

E 49
D 88
orderq()
E 88
I 88
orderq(doall)
	bool doall;
E 88
{
D 13
	struct direct d;
E 13
I 13
D 191
	register struct direct *d;
E 191
I 191
	register struct dirent *d;
E 191
E 13
	register WORK *w;
D 95
	register WORK **wp;		/* parent of w */
E 95
D 13
	register FILE *f;
E 13
I 13
	DIR *f;
E 13
	register int i;
D 9
	struct stat st;
E 9
D 68
	WORK wlist[WLSIZE];
E 68
I 68
D 102
	WORK wlist[WLSIZE+1];
E 102
I 102
D 280
	WORK wlist[QUEUESIZE+1];
E 280
E 102
E 68
D 63
	int wn = 0;
E 63
I 63
	int wn = -1;
E 63
D 239
	extern workcmpf();
E 239
I 239
	int wc;
E 239
D 44
	extern char *QueueDir;
E 44

I 155
	if (tTd(41, 1))
	{
		printf("orderq:\n");
		if (QueueLimitId != NULL)
			printf("\tQueueLimitId = %s\n", QueueLimitId);
		if (QueueLimitSender != NULL)
			printf("\tQueueLimitSender = %s\n", QueueLimitSender);
		if (QueueLimitRecipient != NULL)
			printf("\tQueueLimitRecipient = %s\n", QueueLimitRecipient);
	}

E 155
	/* clear out old WorkQ */
	for (w = WorkQ; w != NULL; )
	{
		register WORK *nw = w->w_next;

		WorkQ = nw;
		free(w->w_name);
I 239
		if (w->w_host)
			free(w->w_host);
E 239
		free((char *) w);
		w = nw;
	}

	/* open the queue directory */
D 13
	f = fopen(QueueDir, "r");
E 13
I 13
D 44
	f = opendir(QueueDir);
E 44
I 44
	f = opendir(".");
E 44
E 13
	if (f == NULL)
	{
D 44
		syserr("orderq: cannot open %s", QueueDir);
E 44
I 44
		syserr("orderq: cannot open \"%s\" as \".\"", QueueDir);
E 44
D 63
		return;
E 63
I 63
		return (0);
E 63
	}

	/*
	**  Read the work directory.
	*/

D 13
	while (wn < WLSIZE && fread((char *) &d, sizeof d, 1, f) == 1)
E 13
I 13
D 63
	while (wn < WLSIZE && (d = readdir(f)) != NULL)
E 63
I 63
	while ((d = readdir(f)) != NULL)
E 63
E 13
	{
D 44
		char cbuf[MAXNAME];
E 44
D 56
		char lbuf[MAXNAME];
E 56
		FILE *cf;
I 212
		register char *p;
E 212
I 56
D 265
		char lbuf[MAXNAME];
E 265
I 265
		char lbuf[MAXNAME + 1];
E 265
I 139
D 192
		extern bool shouldqueue();
E 192
I 155
		extern bool strcontainedin();
E 155
E 139
E 56
D 44
		register char *p;
E 44

		/* is this an interesting entry? */
I 51
		if (d->d_ino == 0)
			continue;
# ifdef DEBUG
		if (tTd(40, 10))
			printf("orderq: %12s\n", d->d_name);
# endif DEBUG
E 51
D 13
		if (d.d_ino == 0 || d.d_name[0] != 'c')
E 13
I 13
D 34
		if (d->d_name[0] != 'c')
E 34
I 34
D 36
		if (d->d_name[0] != 'c' || d->d_name[1] != 'f')
E 36
I 36
		if (d->d_name[0] != 'q' || d->d_name[1] != 'f')
E 36
E 34
E 13
			continue;

I 155
		if (QueueLimitId != NULL &&
		    !strcontainedin(QueueLimitId, d->d_name))
			continue;

I 269
#ifdef PICKY_QF_NAME_CHECK
E 269
E 155
I 145
D 165
		if (strlen(d->d_name) != 9)
E 165
I 165
D 166
		if (strlen(d->d_name) != 10)
E 166
I 166
		/*
		**  Check queue name for plausibility.  This handles
		**  both old and new type ids.
		*/

D 212
		i = strlen(d->d_name);
		if (i != 9 && i != 10)
E 212
I 212
		p = d->d_name + 2;
		if (isupper(p[0]) && isupper(p[2]))
			p += 3;
		else if (isupper(p[1]))
			p += 2;
		else
			p = d->d_name;
		for (i = 0; isdigit(*p); p++)
			i++;
		if (i < 5 || *p != '\0')
E 212
E 166
E 165
		{
			if (Verbose)
				printf("orderq: bogus qf name %s\n", d->d_name);
D 269
#ifdef LOG
			if (LogLevel > 3)
D 187
				syslog(LOG_NOTICE, "orderq: bogus qf name %s",
E 187
I 187
				syslog(LOG_CRIT, "orderq: bogus qf name %s",
E 269
I 269
# ifdef LOG
			if (LogLevel > 0)
				syslog(LOG_ALERT, "orderq: bogus qf name %s",
E 269
E 187
					d->d_name);
D 269
#endif
E 269
I 269
# endif
E 269
D 265
			if (strlen(d->d_name) >= MAXNAME)
				d->d_name[MAXNAME - 1] = '\0';
E 265
I 265
D 274
			if (strlen(d->d_name) > MAXNAME)
E 274
I 274
			if (strlen(d->d_name) > (SIZE_T) MAXNAME)
E 274
				d->d_name[MAXNAME] = '\0';
E 265
			strcpy(lbuf, d->d_name);
			lbuf[0] = 'Q';
			(void) rename(d->d_name, lbuf);
			continue;
		}
I 269
#endif
E 269

E 145
D 44
		/* yes -- find the control file location */
D 18
		strcpy(cbuf, QueueDir);
		strcat(cbuf, "/");
E 18
I 18
		(void) strcpy(cbuf, QueueDir);
		(void) strcat(cbuf, "/");
E 18
		p = &cbuf[strlen(cbuf)];
D 13
		strncpy(p, d.d_name, DIRSIZ);
		p[DIRSIZ] = '\0';
E 13
I 13
D 18
		strcpy(p, d->d_name);
E 18
I 18
		(void) strcpy(p, d->d_name);
E 18
E 13

		/* open control file */
		cf = fopen(cbuf, "r");
E 44
I 44
D 63
		/* yes -- open control file */
E 63
I 63
D 269
		/* yes -- open control file (if not too many files) */
E 269
I 269
		/* open control file (if not too many files) */
E 269
D 102
		if (++wn >= WLSIZE)
E 102
I 102
D 280
		if (++wn >= QUEUESIZE)
E 102
			continue;
E 280
I 280
D 282
		if (++wn >= WorkListSize)
E 282
I 282
		if (++wn > MaxQueueRun && MaxQueueRun > 0)
E 282
		{
I 282
# ifdef LOG
			if (wn == MaxQueueRun + 1 && LogLevel > 0)
				syslog(LOG_ALERT, "WorkList for %s maxed out at %d",
						QueueDir, MaxQueueRun);
# endif
			continue;
		}
		if (wn >= WorkListSize)
		{
I 283
			extern void grow_wlist __P((void));

E 283
E 282
			grow_wlist();
			if (wn >= WorkListSize)
				continue;
		}
E 280
I 155

E 155
E 63
		cf = fopen(d->d_name, "r");
E 44
		if (cf == NULL)
		{
D 21
			syserr("orderq: cannot open %s", cbuf);
E 21
I 21
			/* this may be some random person sending hir msgs */
			/* syserr("orderq: cannot open %s", cbuf); */
I 64
D 109
#ifdef DEBUG
E 109
			if (tTd(41, 2))
				printf("orderq: cannot open %s (%d)\n",
					d->d_name, errno);
D 109
#endif DEBUG
E 109
E 64
			errno = 0;
I 64
			wn--;
E 64
E 21
			continue;
		}
I 7
D 44
		wlist[wn].w_name = newstr(cbuf);
E 44
I 44
D 102
		wlist[wn].w_name = newstr(d->d_name);
E 102
I 102
D 280
		w = &wlist[wn];
E 280
I 280
		w = &WorkList[wn];
E 280
		w->w_name = newstr(d->d_name);
I 239
		w->w_host = NULL;
		w->w_lock = !lockfile(fileno(cf), w->w_name, NULL, LOCK_SH|LOCK_NB);
E 239
E 102
E 44
E 7

I 98
		/* make sure jobs in creation don't clog queue */
D 102
		wlist[wn].w_pri = 0x7fffffff;
		wlist[wn].w_ctime = 0;
E 102
I 102
		w->w_pri = 0x7fffffff;
		w->w_ctime = 0;
E 102

E 98
		/* extract useful information */
D 7
		wlist[wn].w_pri = PRI_NORMAL;
E 7
D 102
		while (fgets(lbuf, sizeof lbuf, cf) != NULL)
E 102
I 102
		i = NEED_P | NEED_T;
I 155
		if (QueueLimitSender != NULL)
			i |= NEED_S;
D 239
		if (QueueLimitRecipient != NULL)
E 239
I 239
D 255
		if (SortQueueByHost || QueueLimitRecipient != NULL)
E 255
I 255
		if (QueueSortOrder == QS_BYHOST || QueueLimitRecipient != NULL)
E 255
E 239
			i |= NEED_R;
E 155
		while (i != 0 && fgets(lbuf, sizeof lbuf, cf) != NULL)
E 102
		{
I 90
D 276
			extern long atol();
E 276
I 155
			extern bool strcontainedin();
E 155

E 90
D 56
			fixcrlf(lbuf, TRUE);

			switch (lbuf[0])
E 56
I 56
D 88
			if (lbuf[0] == 'P')
E 88
I 88
			switch (lbuf[0])
E 88
E 56
			{
D 7
			  case 'D':		/* data file name */
				if (stat(&lbuf[1], &st) < 0)
				{
					syserr("orderq: cannot stat %s", &lbuf[1]);
					(void) fclose(cf);
					(void) unlink(cbuf);
					wn--;
					continue;
				}
				wlist[wn].w_name = newstr(cbuf);
				wlist[wn].w_size = st.st_size;
				break;

E 7
D 56
			  case 'P':		/* message priority */
E 56
D 7
				wlist[wn].w_pri = atoi(&lbuf[1]);
E 7
I 7
D 88
				(void) sscanf(&lbuf[1], "%ld", &wlist[wn].w_pri);
E 88
I 88
			  case 'P':
D 102
				wlist[wn].w_pri = atol(&lbuf[1]);
E 102
I 102
				w->w_pri = atol(&lbuf[1]);
				i &= ~NEED_P;
E 102
E 88
E 7
				break;
I 97

			  case 'T':
D 102
				wlist[wn].w_ctime = atol(&lbuf[1]);
E 102
I 102
				w->w_ctime = atol(&lbuf[1]);
				i &= ~NEED_T;
E 102
				break;
I 155

			  case 'R':
D 239
				if (QueueLimitRecipient != NULL &&
E 239
I 239
				if (w->w_host == NULL &&
				    (p = strrchr(&lbuf[1], '@')) != NULL)
					w->w_host = newstr(&p[1]);
				if (QueueLimitRecipient == NULL ||
E 239
				    strcontainedin(QueueLimitRecipient, &lbuf[1]))
					i &= ~NEED_R;
				break;

			  case 'S':
				if (QueueLimitSender != NULL &&
				    strcontainedin(QueueLimitSender, &lbuf[1]))
					i &= ~NEED_S;
				break;
E 155
E 97
I 88
D 95

			  case 'T':
				wlist[wn].w_ctime = atol(&lbuf[1]);
				break;
E 95
E 88
			}
		}
D 63
		wn++;
E 63
		(void) fclose(cf);
I 89

D 102
		if (!doall && shouldqueue(wlist[wn].w_pri))
E 102
I 102
D 136
		if (!doall && shouldqueue(w->w_pri))
E 136
I 136
D 155
		if (!doall && shouldqueue(w->w_pri, w->w_ctime))
E 155
I 155
		if ((!doall && shouldqueue(w->w_pri, w->w_ctime)) ||
		    bitset(NEED_R|NEED_S, i))
E 155
E 136
E 102
		{
			/* don't even bother sorting this job in */
I 239
			free(w->w_name);
			if (w->w_host)
				free(w->w_host);
E 239
			wn--;
		}
E 89
	}
D 13
	(void) fclose(f);
E 13
I 13
	(void) closedir(f);
I 64
	wn++;
E 64
E 13

D 239
	/*
	**  Sort the work directory.
	*/
E 239
I 239
D 280
	wc = min(wn, QUEUESIZE);
E 280
I 280
	wc = min(wn, WorkListSize);
E 280
E 239

D 68
	qsort(wlist, wn, sizeof *wlist, workcmpf);
E 68
I 68
D 87
	qsort(wlist, min(wn, WLSIZE), sizeof *wlist, workcmpf);
E 87
I 87
D 102
	qsort((char *) wlist, min(wn, WLSIZE), sizeof *wlist, workcmpf);
E 102
I 102
D 239
	qsort((char *) wlist, min(wn, QUEUESIZE), sizeof *wlist, workcmpf);
E 239
I 239
D 255
	if (!SortQueueByHost)
E 255
I 255
	if (QueueSortOrder == QS_BYHOST)
E 255
	{
D 255
		extern workcmpf0();
E 239
E 102
E 87
E 68

I 239
		/*
		**  Simple sort based on queue priority only.
		*/

		qsort((char *) wlist, wc, sizeof *wlist, workcmpf0);
	}
	else
	{
E 255
		extern workcmpf1();
		extern workcmpf2();

		/*
		**  Sort the work directory for the first time,
		**  based on host name, lock status, and priority.
		*/

D 280
		qsort((char *) wlist, wc, sizeof *wlist, workcmpf1);
E 280
I 280
		qsort((char *) WorkList, wc, sizeof *WorkList, workcmpf1);
E 280

		/*
		**  If one message to host is locked, "lock" all messages
		**  to that host.
		*/

		i = 0;
		while (i < wc)
		{
D 280
			if (!wlist[i].w_lock)
E 280
I 280
			if (!WorkList[i].w_lock)
E 280
			{
				i++;
				continue;
			}
D 280
			w = &wlist[i];
E 280
I 280
			w = &WorkList[i];
E 280
			while (++i < wc)
			{
D 280
				if (wlist[i].w_host == NULL &&
E 280
I 280
				if (WorkList[i].w_host == NULL &&
E 280
				    w->w_host == NULL)
D 280
					wlist[i].w_lock = TRUE;
				else if (wlist[i].w_host != NULL &&
E 280
I 280
					WorkList[i].w_lock = TRUE;
				else if (WorkList[i].w_host != NULL &&
E 280
					 w->w_host != NULL &&
D 280
					 strcmp(wlist[i].w_host, w->w_host) == 0)
					wlist[i].w_lock = TRUE;
E 280
I 280
					 strcmp(WorkList[i].w_host, w->w_host) == 0)
					WorkList[i].w_lock = TRUE;
E 280
				else
					break;
			}
		}

		/*
		**  Sort the work directory for the second time,
		**  based on lock status, host name, and priority.
		*/

D 280
		qsort((char *) wlist, wc, sizeof *wlist, workcmpf2);
E 280
I 280
		qsort((char *) WorkList, wc, sizeof *WorkList, workcmpf2);
E 280
I 255
	}
	else
	{
		extern workcmpf0();

		/*
		**  Simple sort based on queue priority only.
		*/

D 280
		qsort((char *) wlist, wc, sizeof *wlist, workcmpf0);
E 280
I 280
		qsort((char *) WorkList, wc, sizeof *WorkList, workcmpf0);
E 280
E 255
	}

E 239
	/*
	**  Convert the work list into canonical form.
I 56
	**	Should be turning it into a list of envelopes here perhaps.
E 56
	*/

D 95
	wp = &WorkQ;
E 95
I 95
	WorkQ = NULL;
E 95
D 68
	for (i = 0; i < wn; i++)
E 68
I 68
D 102
	for (i = min(wn, WLSIZE); --i >= 0; )
E 102
I 102
D 239
	for (i = min(wn, QUEUESIZE); --i >= 0; )
E 239
I 239
	for (i = wc; --i >= 0; )
E 239
E 102
E 68
	{
		w = (WORK *) xalloc(sizeof *w);
D 280
		w->w_name = wlist[i].w_name;
I 239
		w->w_host = wlist[i].w_host;
		w->w_lock = wlist[i].w_lock;
E 239
D 7
		w->w_size = wlist[i].w_size;
E 7
		w->w_pri = wlist[i].w_pri;
I 97
		w->w_ctime = wlist[i].w_ctime;
E 280
I 280
		w->w_name = WorkList[i].w_name;
		w->w_host = WorkList[i].w_host;
		w->w_lock = WorkList[i].w_lock;
		w->w_pri = WorkList[i].w_pri;
		w->w_ctime = WorkList[i].w_ctime;
E 280
E 97
I 88
D 95
		w->w_ctime = wlist[i].w_ctime;
E 88
		w->w_next = NULL;
		*wp = w;
		wp = &w->w_next;
E 95
I 95
		w->w_next = WorkQ;
		WorkQ = w;
E 95
	}
I 280
	free(WorkList);
	WorkList = NULL;
E 280

D 109
# ifdef DEBUG
E 109
D 29
	if (Debug)
E 29
I 29
	if (tTd(40, 1))
E 29
	{
		for (w = WorkQ; w != NULL; w = w->w_next)
D 2
			printf("%32s: sz=%ld\n", w->w_name, w->w_size);
E 2
I 2
D 7
			printf("%32s: pri=%-2d sz=%ld\n", w->w_name, w->w_pri,
			     w->w_size);
E 7
I 7
			printf("%32s: pri=%ld\n", w->w_name, w->w_pri);
E 7
E 2
	}
D 109
# endif DEBUG
E 109
I 63

D 64
	return (wn + 1);
E 64
I 64
	return (wn);
E 64
E 63
}
I 282
/*
**  GROW_WLIST -- make the work list larger
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Adds another QUEUESEGSIZE entries to WorkList if possible.
**		It can fail if there isn't enough memory, so WorkListSize
**		should be checked again upon return.
*/
E 282
I 280

I 283
void
E 283
grow_wlist()
{
	if (tTd(41, 1))
		printf("grow_wlist: WorkListSize=%d\n", WorkListSize);
D 281
	if (WorkListSize >= MAXQUEUESIZE)
E 281
I 281
D 282
	if (MaxQueueRun > 0 && WorkListSize >= MaxQueueRun)
E 281
	{
# ifdef LOG
		if (LogLevel > 0)
			syslog(LOG_ALERT, "WorkList for %s maxed out at %d",
					QueueDir, WorkListSize);
# endif
	}
	else if (WorkList == NULL)
E 282
I 282
	if (WorkList == NULL)
E 282
	{
		WorkList = (WORK *) xalloc(sizeof(WORK) * (QUEUESEGSIZE + 1));
		WorkListSize = QUEUESEGSIZE;
	}
	else
	{
		int newsize = WorkListSize + QUEUESEGSIZE;
		WORK *newlist = (WORK *) realloc((char *)WorkList,
					  (unsigned)sizeof(WORK) * (newsize + 1));

		if (newlist != NULL)
		{
			WorkListSize = newsize;
			WorkList = newlist;
# ifdef LOG
			if (LogLevel > 1)
			{
				syslog(LOG_NOTICE, "grew WorkList for %s to %d",
						QueueDir, WorkListSize);
			}
		}
		else if (LogLevel > 0)
		{
			syslog(LOG_ALERT, "FAILED to grow WorkList for %s to %d",
					QueueDir, newsize);
# endif
		}
	}
	if (tTd(41, 1))
		printf("grow_wlist: WorkListSize now %d\n", WorkListSize);
}
E 280
/*
D 29
**	WORKCMPF -- compare function for ordering work.
E 29
I 29
D 239
**  WORKCMPF -- compare function for ordering work.
E 239
I 239
**  WORKCMPF0 -- simple priority-only compare function.
E 239
E 29
**
**	Parameters:
**		a -- the first argument.
**		b -- the second argument.
**
**	Returns:
D 68
**		-1 if a < b
E 68
I 68
D 95
**		1 if a < b
E 68
**		0 if a == b
D 68
**		1 if a > b
E 68
I 68
**		-1 if a > b
E 95
I 95
**		-1 if a < b
**		 0 if a == b
**		+1 if a > b
E 95
E 68
**
**	Side Effects:
**		none.
*/

I 283
int
E 283
D 68
# define PRIFACT	1800		/* bytes each priority point is worth */

E 68
D 239
workcmpf(a, b)
E 239
I 239
workcmpf0(a, b)
E 239
D 7
	WORK *a;
	WORK *b;
E 7
I 7
	register WORK *a;
	register WORK *b;
E 7
{
D 7
	register long aval;
	register long bval;

	aval = a->w_size - PRIFACT * a->w_pri;
	bval = b->w_size - PRIFACT * b->w_pri;

	if (aval == bval)
E 7
I 7
D 88
	if (a->w_pri == b->w_pri)
E 88
I 88
D 95
	long pa = a->w_pri + a->w_ctime;
	long pb = b->w_pri + b->w_ctime;
E 95
I 95
D 97
	long pa = a->w_pri;
	long pb = b->w_pri;
E 97
I 97
D 136
	long pa = a->w_pri + a->w_ctime;
	long pb = b->w_pri + b->w_ctime;
E 136
I 136
	long pa = a->w_pri;
	long pb = b->w_pri;
E 136
E 97
E 95

	if (pa == pb)
E 88
E 7
D 239
		return (0);
E 239
I 239
		return 0;
E 239
D 7
	else if (aval > bval)
E 7
I 7
D 88
	else if (a->w_pri > b->w_pri)
E 88
I 88
	else if (pa > pb)
E 88
E 7
D 68
		return (1);
	else
E 68
D 95
		return (-1);
I 68
	else
E 95
D 239
		return (1);
E 239
I 239
		return 1;
E 239
I 95
	else
D 239
		return (-1);
E 239
I 239
		return -1;
E 239
E 95
E 68
}
/*
I 239
**  WORKCMPF1 -- first compare function for ordering work based on host name.
**
**	Sorts on host name, lock status, and priority in that order.
**
**	Parameters:
**		a -- the first argument.
**		b -- the second argument.
**
**	Returns:
**		<0 if a < b
**		 0 if a == b
**		>0 if a > b
**
**	Side Effects:
**		none.
*/

I 283
int
E 283
workcmpf1(a, b)
	register WORK *a;
	register WORK *b;
{
	int i;

	/* host name */
	if (a->w_host != NULL && b->w_host == NULL)
		return 1;
	else if (a->w_host == NULL && b->w_host != NULL)
		return -1;
	if (a->w_host != NULL && b->w_host != NULL &&
	    (i = strcmp(a->w_host, b->w_host)))
		return i;

	/* lock status */
	if (a->w_lock != b->w_lock)
		return b->w_lock - a->w_lock;

	/* job priority */
	return a->w_pri - b->w_pri;
}
/*
**  WORKCMPF2 -- second compare function for ordering work based on host name.
**
**	Sorts on lock status, host name, and priority in that order.
**
**	Parameters:
**		a -- the first argument.
**		b -- the second argument.
**
**	Returns:
**		<0 if a < b
**		 0 if a == b
**		>0 if a > b
**
**	Side Effects:
**		none.
*/

I 283
int
E 283
workcmpf2(a, b)
	register WORK *a;
	register WORK *b;
{
	int i;

	/* lock status */
	if (a->w_lock != b->w_lock)
		return a->w_lock - b->w_lock;

	/* host name */
	if (a->w_host != NULL && b->w_host == NULL)
		return 1;
	else if (a->w_host == NULL && b->w_host != NULL)
		return -1;
	if (a->w_host != NULL && b->w_host != NULL &&
	    (i = strcmp(a->w_host, b->w_host)))
		return i;

	/* job priority */
	return a->w_pri - b->w_pri;
}
/*
E 239
**  DOWORK -- do a work request.
**
**	Parameters:
D 174
**		w -- the work request to be satisfied.
E 174
I 174
**		id -- the ID of the job to run.
**		forkflag -- if set, run this in background.
I 177
**		requeueflag -- if set, reinstantiate the queue quickly.
**			This is used when expanding aliases in the queue.
I 195
**			If forkflag is also set, it doesn't wait for the
**			child.
E 195
E 177
**		e - the envelope in which to run it.
E 174
**
**	Returns:
D 207
**		none.
E 207
I 207
**		process id of process that is running the queue job.
E 207
**
**	Side Effects:
**		The work request is satisfied if possible.
*/

I 207
pid_t
E 207
D 126
dowork(w)
E 126
I 126
D 174
dowork(w, e)
E 126
	register WORK *w;
E 174
I 174
D 177
dowork(id, forkflag, e)
E 177
I 177
dowork(id, forkflag, requeueflag, e)
E 177
	char *id;
	bool forkflag;
I 177
	bool requeueflag;
E 177
E 174
I 126
	register ENVELOPE *e;
E 126
{
D 207
	register int i;
E 207
I 207
	register pid_t pid;
E 207
I 88
D 174
	extern bool shouldqueue();
E 174
I 119
	extern bool readqf();
E 119
E 88
D 56
	auto int xstat;
E 56

D 109
# ifdef DEBUG
E 109
D 29
	if (Debug)
E 29
I 29
	if (tTd(40, 1))
E 29
D 7
		printf("dowork: %s size %ld pri %d\n", w->w_name,
		    w->w_size, w->w_pri);
E 7
I 7
D 174
		printf("dowork: %s pri %ld\n", w->w_name, w->w_pri);
E 174
I 174
		printf("dowork(%s)\n", id);
E 174
E 7
D 109
# endif DEBUG
E 109

	/*
D 88
	**  Fork for work.
E 88
I 88
D 174
	**  Ignore jobs that are too expensive for the moment.
E 88
	*/

D 88
	i = fork();
	if (i < 0)
E 88
I 88
D 136
	if (shouldqueue(w->w_pri))
E 136
I 136
	if (shouldqueue(w->w_pri, w->w_ctime))
E 136
E 88
	{
D 88
		syserr("dowork: cannot fork");
E 88
I 88
		if (Verbose)
D 92
			printf("\nSkipping %s\n", w->w_name);
E 92
I 92
			printf("\nSkipping %s\n", w->w_name + 2);
E 92
E 88
		return;
	}

I 88
	/*
E 174
	**  Fork for work.
	*/

D 174
	if (ForkQueueRuns)
E 174
I 174
	if (forkflag)
E 174
	{
D 207
		i = fork();
		if (i < 0)
E 207
I 207
		pid = fork();
		if (pid < 0)
E 207
		{
			syserr("dowork: cannot fork");
D 207
			return;
E 207
I 207
			return 0;
E 207
		}
I 223
		else if (pid > 0)
		{
			/* parent -- clean out connection cache */
			mci_flush(FALSE, NULL);
		}
E 223
	}
	else
	{
D 207
		i = 0;
E 207
I 207
		pid = 0;
E 207
	}

E 88
D 207
	if (i == 0)
E 207
I 207
	if (pid == 0)
E 207
	{
I 110
D 119
		FILE *qflock, *readqf();
I 116

E 119
E 116
E 110
I 81
D 82
		FILE *qfp;

E 82
E 81
I 15
D 55
		char buf[MAXNAME];

E 55
E 15
		/*
		**  CHILD
I 15
D 44
		**	Change the name of the control file to avoid
D 23
		**	duplicate deliveries.   Then run the file as
		**	though we had just read it.
E 23
I 23
		**		duplicate deliveries.   Then run the file
		**		as though we had just read it.
E 44
I 44
		**	Lock the control file to avoid duplicate deliveries.
		**		Then run the file as though we had just read it.
E 44
		**	We save an idea of the temporary name so we
		**		can recover on interrupt.
E 23
E 15
		*/

I 33
		/* set basic modes, etc. */
E 33
I 24
		(void) alarm(0);
I 70
D 91
		closexscript(CurEnv);
E 70
E 24
I 22
D 54
		FatalErrors = FALSE;
E 54
I 54
		CurEnv->e_flags &= ~EF_FATALERRS;
E 91
I 91
D 101
		clearenvelope(CurEnv);
E 101
I 101
D 126
		clearenvelope(CurEnv, FALSE);
E 126
I 126
		clearenvelope(e, FALSE);
E 126
E 101
E 91
E 54
E 22
D 171
		QueueRun = TRUE;
E 171
I 171
D 213
		e->e_flags |= EF_QUEUERUN;
E 213
I 213
		e->e_flags |= EF_QUEUERUN|EF_GLOBALERRS;
E 213
E 171
I 57
D 65
		SendMode = SM_DELIVER;
E 65
E 57
I 16
D 56
		MailBack = TRUE;
E 56
I 56
D 170
		ErrorMode = EM_MAIL;
E 170
I 170
		e->e_errormode = EM_MAIL;
E 170
E 56
I 36
D 54
		CurEnv->e_qf = w->w_name;
E 54
D 44
		CurEnv->e_id = &w->w_name[strlen(QueueDir) + 3];
E 44
I 44
D 126
		CurEnv->e_id = &w->w_name[2];
E 126
I 126
D 174
		e->e_id = &w->w_name[2];
E 174
I 174
		e->e_id = id;
I 217
D 221
		GrabTo = FALSE;
E 221
I 221
		GrabTo = UseErrorsTo = FALSE;
I 235
		ExitStat = EX_OK;
E 235
E 221
E 217
I 199
		if (forkflag)
I 213
		{
E 213
D 207
			disconnect(0, e);
E 207
I 207
			disconnect(1, e);
I 213
			OpMode = MD_DELIVER;
		}
E 213
E 207
E 199
E 174
E 126
E 44
I 38
# ifdef LOG
D 129
		if (LogLevel > 11)
E 129
I 129
D 145
		if (LogLevel > 12)
E 145
I 145
		if (LogLevel > 76)
E 145
E 129
D 40
			syslog(LOG_DEBUG, "dowork, pid=%d, id=%s", getpid(),
			       CurEnv->e_id);
E 40
I 40
D 126
			syslog(LOG_DEBUG, "%s: dowork, pid=%d", CurEnv->e_id,
E 126
I 126
			syslog(LOG_DEBUG, "%s: dowork, pid=%d", e->e_id,
E 126
			       getpid());
E 40
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
E 133
E 38
E 36
I 33

		/* don't use the headers from sendmail.cf... */
D 126
		CurEnv->e_header = NULL;
E 126
I 126
		e->e_header = NULL;
E 126
D 55
		chompheader("from: $q", TRUE);
E 55
I 55
D 74
		(void) chompheader("from: $q", TRUE);
E 74
E 55

D 81
		/* create the link to the control file during processing */
E 81
I 81
D 82
		FileName = queuename(CurEnv, 'q');
		qfp = fopen(FileName, "r");
		if (qfp == NULL)
			exit(EX_OK);

E 82
D 110
		/* lock the control file during processing */
D 82
# ifdef FLOCK
		if (flock(fileno(qfp), LOCK_EX|LOCK_NB) < 0)
# else FLOCK
E 82
E 81
E 33
E 16
I 15
D 36
		(void) strcpy(buf, QueueDir);
		(void) strcat(buf, "/tfXXXXXX");
		(void) mktemp(buf);
		if (link(w->w_name, buf) < 0)
E 36
I 36
		if (link(w->w_name, queuename(CurEnv, 'l')) < 0)
E 110
I 110
D 119
		/* read the queue control file */
		/*  and lock the control file during processing */
D 116
		if ((qflock=readqf(CurEnv, TRUE)) == NULL)
E 116
I 116
		if ((qflock = readqf(CurEnv, TRUE)) == NULL)
E 119
I 119
		/* read the queue control file -- return if locked */
D 126
		if (!readqf(CurEnv))
E 126
I 126
D 200
		if (!readqf(e))
E 200
I 200
D 228
		if (!readqf(e, !requeueflag))
E 228
I 228
		if (!readqf(e))
E 228
E 200
E 126
E 119
E 116
E 110
I 81
D 82
# endif FLOCK
E 82
E 81
E 36
		{
D 30
			syserr("dowork: link(%s, %s)", w->w_name, buf);

			/* it's ok to lie -- it will be run later */
E 30
I 30
D 36
			/* this can happen normally; another queuer sneaks in */
			/* syserr("dowork: link(%s, %s)", w->w_name, buf); */
E 36
I 36
D 110
			/* being processed by another queuer */
I 40
# ifdef LOG
			if (LogLevel > 4)
				syslog(LOG_DEBUG, "%s: locked", CurEnv->e_id);
# endif LOG
E 110
E 40
E 36
E 30
D 88
			exit(EX_OK);
E 88
I 88
D 174
			if (ForkQueueRuns)
E 174
I 174
			if (tTd(40, 4))
				printf("readqf(%s) failed\n", e->e_id);
			if (forkflag)
E 174
				exit(EX_OK);
			else
D 235
				return;
E 235
I 235
				return 0;
E 235
E 88
		}
I 23
D 36
		ControlFile = newstr(buf);
E 23
		(void) unlink(w->w_name);
E 36

D 59
		/* create ourselves a transcript file */
E 15
I 2
		openxscrpt();
I 15

E 59
D 110
		/* do basic system initialization */
E 15
E 2
		initsys();
D 15
		readqf(w->w_name);
E 15
I 15

		/* read the queue control file */
D 36
		readqf(buf);
E 36
I 36
D 54
		readqf(CurEnv->e_qf);
E 54
I 54
D 56
		readqf(queuename(CurEnv, 'q'));
E 56
I 56
D 61
		readqf(CurEnv);
E 61
I 61
D 81
		readqf(CurEnv, TRUE);
E 81
I 81
D 82
		readqf(qfp, CurEnv, TRUE);
		(void) fclose(qfp);
E 82
I 82
		readqf(CurEnv, TRUE);
E 110
E 82
E 81
E 61
E 56
D 126
		CurEnv->e_flags |= EF_INQUEUE;
E 54
E 36
I 34
D 56
		eatheader();
E 56
I 56
		eatheader(CurEnv);
E 126
I 126
		e->e_flags |= EF_INQUEUE;
D 139
		eatheader(e);
E 139
I 139
D 171
		eatheader(e, TRUE);
E 171
I 171
D 178
		eatheader(e);
E 178
I 178
D 243
		eatheader(e, requeueflag);
E 243
E 178
I 177

D 243
		if (requeueflag)
			queueup(e, TRUE, FALSE);
E 243
I 243
		/* if this has been tried recently, let it be */
D 244
		if (e->e_ntries > 0 && (curtime() - e->e_dtime) > MinQueueAge)
E 244
I 244
		if (e->e_ntries > 0 && (curtime() - e->e_dtime) < MinQueueAge)
E 244
		{
			char *howlong = pintvl(curtime() - e->e_dtime, TRUE);
E 243
E 177
E 171
E 139
E 126
E 56
E 34

D 243
		/* do the delivery */
E 15
D 20
		sendall(FALSE);
E 20
I 20
D 28
		sendall(CurEnv, FALSE);
E 28
I 28
D 54
		if (!FatalErrors)
E 54
I 54
D 126
		if (!bitset(EF_FATALERRS, CurEnv->e_flags))
E 54
D 53
			sendall(CurEnv, FALSE);
E 53
I 53
			sendall(CurEnv, SM_DELIVER);
E 126
I 126
D 176
		if (!bitset(EF_FATALERRS, e->e_flags))
			sendall(e, SM_DELIVER);
E 176
I 176
		sendall(e, SM_DELIVER);
E 243
I 243
			e->e_flags |= EF_KEEPQUEUE;
			if (Verbose || tTd(40, 8))
				printf("%s: too young (%s)\n",
					e->e_id, howlong);
#ifdef LOG
			if (LogLevel > 19)
				syslog(LOG_DEBUG, "%s: too young (%s)",
					e->e_id, howlong);
#endif
		}
		else
		{
			eatheader(e, requeueflag);
E 243
E 176
E 126
E 53
E 28
E 20
I 15

I 243
			if (requeueflag)
				queueup(e, TRUE, FALSE);

			/* do the delivery */
			sendall(e, SM_DELIVER);
		}

E 243
I 110
D 112
		fclose(qflock);
E 112
E 110
D 65
		/* if still not sent, perhaps we should time out.... */
E 15
I 2
# ifdef DEBUG
D 29
		if (Debug > 2)
E 29
I 29
		if (tTd(40, 3))
E 29
D 37
			printf("CurTime=%ld, TimeOut=%ld\n", CurTime, TimeOut);
E 37
I 37
D 41
			printf("CurTime=%ld, TimeOut=%ld\n", CurTime,
E 41
I 41
			printf("curtime=%ld, TimeOut=%ld\n", curtime(),
E 41
					     CurEnv->e_ctime + TimeOut);
E 37
# endif DEBUG
D 14
		if (QueueUp && CurTime > TimeOut)
E 14
I 14
D 37
		if (CurEnv->e_queueup && CurTime > TimeOut)
E 37
I 37
D 41
		if (CurEnv->e_queueup && CurTime > CurEnv->e_ctime + TimeOut)
E 41
I 41
D 54
		if (CurEnv->e_queueup && curtime() > CurEnv->e_ctime + TimeOut)
E 41
E 37
E 14
			timeout(w);
E 54
I 54
		if (curtime() > CurEnv->e_ctime + TimeOut)
			CurEnv->e_flags |= EF_TIMEOUT;
E 54
E 2
D 7
		if (!QueueUp)
			(void) unlink(w->w_name);
E 7
I 7
D 15
		(void) unlink(w->w_name);
E 15
I 15
D 36

		/* get rid of the temporary file -- a new cf will be made */
I 23
		ControlFile = NULL;
E 23
		(void) unlink(buf);
E 36

E 65
		/* finish up and exit */
E 15
E 7
D 2
		else if (CurTime > TimeOut)
			timeout(w);
E 2
D 88
		finis();
E 88
I 88
D 174
		if (ForkQueueRuns)
E 174
I 174
		if (forkflag)
E 174
			finis();
		else
D 126
			dropenvelope(CurEnv);
E 126
I 126
			dropenvelope(e);
E 126
I 112
D 119
		fclose(qflock);
E 119
E 112
E 88
	}
I 88
D 195
	else
E 195
I 195
D 207
	else if (!requeueflag)
E 195
	{
		/*
		**  Parent -- pick up results.
		*/
E 88

D 88
	/*
	**  Parent -- pick up results.
	*/

	errno = 0;
D 56
	while ((i = wait(&xstat)) > 0 && errno != EINTR)
	{
		if (errno == EINTR)
		{
			errno = 0;
		}
	}
E 56
I 56
	(void) waitfor(i);
E 88
I 88
		errno = 0;
		(void) waitfor(i);
	}
E 207
I 207
	e->e_id = NULL;
	return pid;
E 207
E 88
E 56
}
/*
**  READQF -- read queue file and set up environment.
**
**	Parameters:
I 81
D 82
**		qfp -- the file pointer for the qf file.
E 82
E 81
D 56
**		cf -- name of queue control file.
E 56
I 56
**		e -- the envelope of the job to run.
I 200
D 228
**		announcefile -- if set, announce the name of the queue
**			file in error messages.
E 228
E 200
I 61
D 119
**		full -- if set, read in all information.  Otherwise just
**			read in info needed for a queue print.
E 119
E 61
E 56
**
**	Returns:
D 110
**		none.
E 110
I 110
D 119
**		FILE * pointing to flock()ed fd so it can be closed
**		after the mail is delivered
E 119
I 119
**		TRUE if it successfully read the queue file.
**		FALSE otherwise.
E 119
E 110
**
**	Side Effects:
D 119
**		cf is read and created as the current job, as though
**		we had been invoked by argument.
E 119
I 119
**		The queue file is returned locked.
E 119
*/

I 118
D 120
# ifdef LOCKF
# define RDLK_MODE	"r+"
# else
# define RDLK_MODE	"r"
# endif

E 120
E 118
I 110
D 119
FILE *
E 110
D 56
readqf(cf)
	char *cf;
E 56
I 56
D 61
readqf(e)
E 61
I 61
D 81
readqf(e, full)
E 81
I 81
D 82
readqf(qfp, e, full)
	register FILE *qfp;
E 82
I 82
readqf(e, full)
E 119
I 119
bool
D 200
readqf(e)
E 200
I 200
D 228
readqf(e, announcefile)
E 228
I 228
readqf(e)
E 228
E 200
E 119
E 82
E 81
E 61
	register ENVELOPE *e;
I 200
D 228
	bool announcefile;
E 228
E 200
I 61
D 119
	bool full;
E 119
E 61
E 56
{
I 82
D 176
	char *qf;
E 176
	register FILE *qfp;
I 124
D 127
	int fd;
E 127
	ADDRESS *ctladdr;
I 132
	struct stat st;
E 132
E 124
E 82
D 81
	register FILE *f;
E 81
D 35
	char buf[MAXLINE];
E 35
I 35
D 134
	char buf[MAXFIELD];
E 134
I 134
	char *bp;
I 246
	int qfver = 0;
	register char *p;
I 253
	char *orcpt = NULL;
I 286
	bool nomore = FALSE;
E 286
E 253
E 246
I 176
	char qf[20];
E 176
	char buf[MAXLINE];
E 134
E 35
I 32
D 55
	register char *p;
	register int i;
E 55
I 55
D 192
	extern char *fgetfolded();
E 192
I 90
D 276
	extern long atol();
E 276
I 111
D 124
	int gotctluser = 0;
E 111
I 110
	int fd;
E 124
I 124
	extern ADDRESS *setctluser();
I 264
	extern void loseqfile();
E 264
E 124
I 120
D 161
# ifdef LOCKF
	struct flock lfd;
# endif
E 161
I 161
D 192
	extern bool lockfile();
E 192
E 161
E 120
E 110
E 90
I 56
D 81
	register char *p;
E 81
E 56
E 55
E 32
I 5
	extern ADDRESS *sendto();
E 5

	/*
D 81
	**  Open the file created by queueup.
	*/

D 56
	f = fopen(cf, "r");
E 56
I 56
	p = queuename(e, 'q');
	f = fopen(p, "r");
E 56
	if (f == NULL)
	{
D 56
		syserr("readqf: no cf file %s", cf);
E 56
I 56
		syserr("readqf: no control file %s", p);
E 56
		return;
	}
I 56
	FileName = p;
	LineNumber = 0;
E 56

	/*
E 81
	**  Read and process the file.
	*/

I 82
D 176
	qf = queuename(e, 'q');
E 176
I 176
	strcpy(qf, queuename(e, 'q'));
E 176
D 118
	qfp = fopen(qf, "r");
E 118
I 118
D 120
	qfp = fopen(qf, RDLK_MODE);
E 120
I 120
	qfp = fopen(qf, "r+");
E 120
E 118
	if (qfp == NULL)
	{
I 174
		if (tTd(40, 8))
			printf("readqf(%s): fopen failure (%s)\n",
				qf, errstring(errno));
E 174
D 110
		syserr("readqf: no control file %s", qf);
		return;
E 110
I 110
		if (errno != ENOENT)
			syserr("readqf: no control file %s", qf);
I 132
		return FALSE;
	}

I 206
D 210
	if (!lockfile(fileno(qfp), qf, LOCK_EX|LOCK_NB))
E 210
I 210
	if (!lockfile(fileno(qfp), qf, NULL, LOCK_EX|LOCK_NB))
E 210
	{
		/* being processed by another queuer */
D 243
		if (tTd(40, 8))
			printf("readqf(%s): locked\n", qf);
		if (Verbose)
E 243
I 243
		if (Verbose || tTd(40, 8))
E 243
			printf("%s: locked\n", e->e_id);
# ifdef LOG
		if (LogLevel > 19)
			syslog(LOG_DEBUG, "%s: locked", e->e_id);
# endif /* LOG */
		(void) fclose(qfp);
		return FALSE;
	}

E 206
	/*
	**  Check the queue file for plausibility to avoid attacks.
	*/

	if (fstat(fileno(qfp), &st) < 0)
	{
		/* must have been being processed by someone else */
I 174
		if (tTd(40, 8))
			printf("readqf(%s): fstat failure (%s)\n",
				qf, errstring(errno));
E 174
		fclose(qfp);
		return FALSE;
	}

D 134
	if (st.st_uid != 0 || (st.st_mode & 07777) != FileMode)
E 134
I 134
D 205
	if (st.st_uid != geteuid() || (st.st_mode & 07777) != FileMode)
E 205
I 205
D 269
	if (st.st_uid != geteuid())
E 269
I 269
	if (st.st_uid != geteuid() || bitset(S_IWOTH|S_IWGRP, st.st_mode))
E 269
E 205
E 134
	{
# ifdef LOG
		if (LogLevel > 0)
		{
			syslog(LOG_ALERT, "%s: bogus queue file, uid=%d, mode=%o",
				e->e_id, st.st_uid, st.st_mode);
		}
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
I 174
		if (tTd(40, 8))
			printf("readqf(%s): bogus file\n", qf);
E 174
E 133
D 206
		fclose(qfp);
E 206
I 197
D 264
		rename(qf, queuename(e, 'Q'));
E 264
I 264
		loseqfile(e, "bogus file uid in mqueue");
E 264
I 206
		fclose(qfp);
E 206
E 197
E 132
D 119
		return NULL;
E 119
I 119
		return FALSE;
E 119
E 110
	}
I 110

I 116
D 161
# ifdef LOCKF
D 120
	if (lockf(fileno(qfp), F_TLOCK, 0) < 0)
E 120
I 120
	lfd.l_type = F_WRLCK;
	lfd.l_whence = lfd.l_start = lfd.l_len = 0;
	if (fcntl(fileno(qfp), F_SETLK, &lfd) < 0)
E 120
# else
E 116
	if (flock(fileno(qfp), LOCK_EX|LOCK_NB) < 0)
I 116
# endif
E 161
I 161
D 206
	if (!lockfile(fileno(qfp), qf, LOCK_EX|LOCK_NB))
E 206
I 206
	if (st.st_size == 0)
E 206
E 161
E 116
	{
D 119
# ifdef LOG
E 119
D 147
		/* being processed by another queuer */
		if (Verbose)
D 112
			printf("%s: locked", CurEnv->e_id);
E 112
I 112
D 126
			printf("%s: locked\n", CurEnv->e_id);
E 126
I 126
			printf("%s: locked\n", e->e_id);
E 147
I 147
D 161
		if (errno == EWOULDBLOCK)
		{
			/* being processed by another queuer */
			if (Verbose)
				printf("%s: locked\n", e->e_id);
E 161
I 161
D 206
		/* being processed by another queuer */
I 174
		if (tTd(40, 8))
			printf("readqf(%s): locked\n", qf);
E 174
		if (Verbose)
			printf("%s: locked\n", e->e_id);
E 161
E 147
E 126
I 119
# ifdef LOG
D 128
		if (LogLevel > 9)
E 128
I 128
D 145
		if (LogLevel > 10)
E 145
I 145
D 147
		if (LogLevel > 19)
E 145
E 128
D 126
			syslog(LOG_DEBUG, "%s: locked", CurEnv->e_id);
E 126
I 126
			syslog(LOG_DEBUG, "%s: locked", e->e_id);
E 147
I 147
D 161
			if (LogLevel > 19)
				syslog(LOG_DEBUG, "%s: locked", e->e_id);
E 161
I 161
		if (LogLevel > 19)
			syslog(LOG_DEBUG, "%s: locked", e->e_id);
E 161
E 147
E 126
E 119
E 112
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
I 147
D 161
		}
		else
		{
			syserr("%s: flock failure", e->e_id);
		}
E 161
E 147
E 133
		(void) fclose(qfp);
E 206
I 206
		/* must be a bogus file -- just remove it */
		(void) unlink(qf);
		fclose(qfp);
E 206
D 119
		return NULL;
E 119
I 119
		return FALSE;
E 119
	}

I 182
D 206
	if (st.st_size == 0)
E 206
I 206
	if (st.st_nlink == 0)
E 206
	{
D 206
		/* must be a bogus file -- just remove it */
		(void) unlink(qf);
E 206
I 206
		/*
		**  Race condition -- we got a file just as it was being
		**  unlinked.  Just assume it is zero length.
		*/

E 206
		fclose(qfp);
		return FALSE;
	}

E 182
I 119
D 206
	/* save this lock */
E 206
I 206
	/* good file -- save this lock */
E 206
	e->e_lockfp = qfp;

E 119
	/* do basic system initialization */
D 126
	initsys();
E 126
I 126
	initsys(e);
I 226
	define('i', e->e_id, e);
E 226
E 126

E 110
D 200
	FileName = qf;
E 200
I 200
D 228
	if (announcefile)
		FileName = qf;
E 228
E 200
E 82
I 81
	LineNumber = 0;
I 200
	e->e_flags |= EF_GLOBALERRS;
	OpMode = MD_DELIVER;
E 200
E 81
I 7
D 21
	if (Verbose)
D 14
		message(Arpa_Info, "Running %s (from %s)", cf, From.q_paddr);
E 14
I 14
		message(Arpa_Info, "Running %s", cf);
E 14

E 21
I 21
D 24
	message(Arpa_Info, "Running %s", cf);
E 24
I 24
D 61
	if (Verbose)
E 61
I 61
D 119
	if (Verbose && full)
E 119
I 119
D 247
	if (Verbose)
E 119
E 61
D 56
		printf("\nRunning %s\n", cf);
E 56
I 56
		printf("\nRunning %s\n", e->e_id);
E 247
I 124
	ctladdr = NULL;
I 242
	e->e_dfino = -1;
I 270
	e->e_msgsize = -1;
E 270
E 242
E 124
E 56
E 24
E 21
E 7
D 32
	while (fgets(buf, sizeof buf, f) != NULL)
E 32
I 32
D 35
	p = buf;
	while (fgets(p, sizeof buf - (p - buf), f) != NULL)
E 35
I 35
D 81
	while (fgetfolded(buf, sizeof buf, f) != NULL)
E 81
I 81
D 134
	while (fgetfolded(buf, sizeof buf, qfp) != NULL)
E 134
I 134
	while ((bp = fgetfolded(buf, sizeof buf, qfp)) != NULL)
E 134
E 81
E 35
E 32
	{
I 171
		register char *p;
E 171
I 137
D 270
		struct stat st;
E 270
I 246
		u_long qflags;
		ADDRESS *q;
E 246

E 137
I 103
D 109
# ifdef DEBUG
E 109
		if (tTd(40, 4))
D 134
			printf("+++++ %s\n", buf);
D 109
# endif DEBUG
E 109
E 103
D 32
		fixcrlf(buf, TRUE);
E 32
I 32
D 35
		/*
		**  Collect any continuation lines...
		*/

		i = fgetc(f);
		if (i != EOF)
			ungetc(i, f);
		if (i == ' ' || i == '\t')
		{
			p += strlen(p);
			continue;
		}
		fixcrlf(p, TRUE);
E 32

E 35
		switch (buf[0])
E 134
I 134
			printf("+++++ %s\n", bp);
I 286
		if (nomore)
		{
			/* hack attack */
			syserr("SECURITY ALERT: extra data in qf: %s", bp);
			fclose(qfp);
			loseqfile(e, "bogus queue line");
			return FALSE;
		}
E 286
		switch (bp[0])
E 134
		{
I 246
		  case 'V':		/* queue file version number */
			qfver = atoi(&bp[1]);
			if (qfver > QF_VERSION)
			{
				syserr("Version number in qf (%d) greater than max (%d)",
					qfver, QF_VERSION);
			}
			break;

E 246
I 111
		  case 'C':		/* specify controlling user */
D 124
			setctluser(&buf[1]);
			gotctluser = 1;
E 124
I 124
D 134
			ctladdr = setctluser(&buf[1]);
E 134
I 134
			ctladdr = setctluser(&bp[1]);
E 134
E 124
			break;

I 253
		  case 'Q':		/* original recipient */
			orcpt = newstr(&bp[1]);
			break;

E 253
E 111
		  case 'R':		/* specify recipient */
D 5
D 6
			sendto(&buf[1], 1, (ADDRESS *) NULL);
E 6
I 6
D 14
			sendto(&buf[1], 1, (ADDRESS *) NULL, &SendQueue);
E 14
I 14
D 43
			sendto(&buf[1], 1, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 43
I 43
D 56
			sendto(&buf[1], (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 56
I 56
D 60
			sendto(&buf[1], (ADDRESS *) NULL, &e->e_sendqueue);
E 60
I 60
D 124
			sendtolist(&buf[1], (ADDRESS *) NULL, &e->e_sendqueue);
E 124
I 124
D 126
			sendtolist(&buf[1], ctladdr, &e->e_sendqueue);
E 126
I 126
D 134
			sendtolist(&buf[1], ctladdr, &e->e_sendqueue, e);
E 134
I 134
D 148
			sendtolist(&bp[1], ctladdr, &e->e_sendqueue, e);
E 148
I 148
D 246
			(void) sendtolist(&bp[1], ctladdr, &e->e_sendqueue, e);
E 246
I 246
			p = bp;
			qflags = 0;
			if (qfver >= 1)
			{
				/* get flag bits */
				while (*++p != '\0' && *p != ':')
				{
					switch (*p)
					{
					  case 'S':
						qflags |= QPINGONSUCCESS;
						break;

					  case 'F':
						qflags |= QPINGONFAILURE;
						break;

					  case 'D':
						qflags |= QPINGONDELAY;
D 268
						break;

					  case 'B':
D 249
						qflags |= QHASRETPARAM;
E 249
I 249
						qflags |= QHAS_RET_PARAM;
E 249
						break;

					  case 'N':
D 249
						qflags |= QHASRETPARAM|QNOBODYRETURN;
E 249
I 249
						qflags |= QHAS_RET_PARAM|QRET_HDRS;
E 268
E 249
						break;

					  case 'P':
						qflags |= QPRIMARY;
						break;
					}
				}
			}
			else
				qflags |= QPRIMARY;
			q = parseaddr(++p, NULLADDR, RF_COPYALL, '\0', NULL, e);
D 253
			if (q == NULL)
				break;
			q->q_alias = ctladdr;
			q->q_flags |= qflags;
D 250
			(void) recipient(q, &e->e_sendqueue, e);
E 250
I 250
			(void) recipient(q, &e->e_sendqueue, 0, e);
E 253
I 253
			if (q != NULL)
			{
				q->q_alias = ctladdr;
				q->q_flags |= qflags;
				q->q_orcpt = orcpt;
				(void) recipient(q, &e->e_sendqueue, 0, e);
			}
			orcpt = NULL;
E 253
E 250
E 246
E 148
E 134
E 126
E 124
E 60
E 56
E 43
E 14
E 6
E 5
I 5
			(void) sendto(&buf[1], 1, (ADDRESS *) NULL, 0);
E 5
			break;

I 102
		  case 'E':		/* specify error recipient */
D 124
			sendtolist(&buf[1], (ADDRESS *) NULL, &e->e_errorqueue);
E 124
I 124
D 126
			sendtolist(&buf[1], ctladdr, &e->e_errorqueue);
E 126
I 126
D 134
			sendtolist(&buf[1], ctladdr, &e->e_errorqueue, e);
E 134
I 134
D 148
			sendtolist(&bp[1], ctladdr, &e->e_errorqueue, e);
E 148
I 148
D 250
			(void) sendtolist(&bp[1], ctladdr, &e->e_errorqueue, e);
E 250
I 250
D 267
			(void) sendtolist(&bp[1], ctladdr, &e->e_errorqueue, 0, e);
E 267
I 267
			/* no longer used */
E 267
E 250
E 148
E 134
E 126
E 124
			break;

E 102
		  case 'H':		/* header */
D 61
			(void) chompheader(&buf[1], FALSE);
E 61
I 61
D 119
			if (full)
				(void) chompheader(&buf[1], FALSE);
E 119
I 119
D 126
			(void) chompheader(&buf[1], FALSE);
E 126
I 126
D 134
			(void) chompheader(&buf[1], FALSE, e);
E 134
I 134
D 275
			(void) chompheader(&bp[1], FALSE, e);
E 275
I 275
			(void) chompheader(&bp[1], FALSE, NULL, e);
E 275
E 134
E 126
E 119
E 61
			break;

I 67
		  case 'M':		/* message */
D 134
			e->e_message = newstr(&buf[1]);
E 134
I 134
D 215
			e->e_message = newstr(&bp[1]);
E 215
I 215
			/* ignore this; we want a new message next time */
E 215
E 134
			break;

E 67
		  case 'S':		/* sender */
I 14
D 15
			if (Verbose)
				message(Arpa_Info, "Sender: %s", &buf[1]);
E 15
E 14
D 2
			setsender(&buf[1]);
E 2
I 2
D 121
			setsender(newstr(&buf[1]));
E 121
I 121
D 126
			setsender(newstr(&buf[1]), CurEnv);
E 126
I 126
D 134
			setsender(newstr(&buf[1]), e);
E 134
I 134
D 156
			setsender(newstr(&bp[1]), e);
E 156
I 156
D 164
			setsender(newstr(&bp[1]), e, NULL);
E 164
I 164
			setsender(newstr(&bp[1]), e, NULL, TRUE);
E 164
E 156
E 134
E 126
E 121
E 2
			break;

I 181
		  case 'B':		/* body type */
			e->e_bodytype = newstr(&bp[1]);
			break;

E 181
		  case 'D':		/* data file name */
I 61
D 119
			if (!full)
				break;
E 119
E 61
D 16
			InFileName = newstr(&buf[1]);
			TempFile = fopen(InFileName, "r");
E 16
I 16
D 56
			CurEnv->e_df = newstr(&buf[1]);
			TempFile = fopen(CurEnv->e_df, "r");
E 56
I 56
D 134
			e->e_df = newstr(&buf[1]);
E 134
I 134
D 270
			e->e_df = newstr(&bp[1]);
E 134
D 59
			TempFile = fopen(e->e_df, "r");
E 56
E 16
			if (TempFile == NULL)
E 59
I 59
			e->e_dfp = fopen(e->e_df, "r");
			if (e->e_dfp == NULL)
I 145
			{
E 145
E 59
D 16
				syserr("readqf: cannot open %s", InFileName);
E 16
I 16
D 56
				syserr("readqf: cannot open %s", CurEnv->e_df);
E 56
I 56
				syserr("readqf: cannot open %s", e->e_df);
I 137
D 145
			if (fstat(fileno(e->e_dfp), &st) >= 0)
E 145
I 145
				e->e_msgsize = -1;
			}
			else if (fstat(fileno(e->e_dfp), &st) >= 0)
I 242
			{
E 242
E 145
				e->e_msgsize = st.st_size;
I 242
				e->e_dfdev = st.st_dev;
				e->e_dfino = st.st_ino;
			}
E 270
I 270
			/* obsolete -- ignore */
E 270
E 242
E 137
E 56
E 16
			break;

D 37
		  case 'T':		/* timeout */
			(void) sscanf(&buf[1], "%ld", &TimeOut);
E 37
I 37
		  case 'T':		/* init time */
D 56
			(void) sscanf(&buf[1], "%ld", &CurEnv->e_ctime);
E 56
I 56
D 88
			(void) sscanf(&buf[1], "%ld", &e->e_ctime);
E 88
I 88
D 134
			e->e_ctime = atol(&buf[1]);
E 134
I 134
			e->e_ctime = atol(&bp[1]);
I 240
			break;

		  case 'I':		/* data file's inode number */
D 242
			e->e_dfino = atol(&buf[1]);
E 242
I 242
			if (e->e_dfino == -1)
				e->e_dfino = atol(&buf[1]);
E 242
			break;

		  case 'K':		/* time of last deliver attempt */
			e->e_dtime = atol(&buf[1]);
			break;

		  case 'N':		/* number of delivery attempts */
			e->e_ntries = atoi(&buf[1]);
E 240
E 134
E 88
E 56
E 37
			break;

I 2
		  case 'P':		/* message priority */
D 7
			MsgPriority = atoi(&buf[1]);
E 7
I 7
D 14
			(void) sscanf(&buf[1], "%ld", &MsgPriority);
E 14
I 14
D 56
			(void) sscanf(&buf[1], "%ld", &CurEnv->e_msgpriority);
E 56
I 56
D 88
			(void) sscanf(&buf[1], "%ld", &e->e_msgpriority);
E 88
I 88
D 95
			e->e_msgpriority = atol(&buf[1]);
E 88
E 56
E 14

			/* make sure that big things get sent eventually */
D 14
			MsgPriority -= WKTIMEFACT;
E 14
I 14
D 56
			CurEnv->e_msgpriority -= WKTIMEFACT;
E 56
I 56
			e->e_msgpriority -= WKTIMEFACT;
E 95
I 95
D 96
			e->e_msgpriority = atol(&buf[1]) - WkTimeFact;
E 96
I 96
D 134
			e->e_msgpriority = atol(&buf[1]) + WkTimeFact;
E 134
I 134
			e->e_msgpriority = atol(&bp[1]) + WkTimeFact;
E 134
E 96
E 95
E 56
E 14
I 10
			break;

I 171
		  case 'F':		/* flag bits */
I 286
			if (strncmp(bp, "From ", 5) == 0)
			{
				/* we are being spoofed! */
				syserr("SECURITY ALERT: bogus qf line %s", bp);
				fclose(qfp);
				loseqfile(e, "bogus queue line");
				return FALSE;
			}
E 286
			for (p = &bp[1]; *p != '\0'; p++)
			{
				switch (*p)
				{
				  case 'w':	/* warning sent */
					e->e_flags |= EF_WARNING;
					break;

				  case 'r':	/* response */
					e->e_flags |= EF_RESPONSE;
I 238
					break;

				  case '8':	/* has 8 bit data */
					e->e_flags |= EF_HAS8BIT;
E 238
					break;
				}
			}
I 251
D 256
			break;

		  case 'O':		/* original MTS from ESMTP */
D 252
			e->e_omts = newstr(&bp[2]);
E 252
I 252
			e->e_omts = newstr(&bp[1]);
E 256
E 252
			break;

		  case 'Z':		/* original envelope id from ESMTP */
D 252
			e->e_envid = newstr(&bp[2]);
E 252
I 252
			e->e_envid = newstr(&bp[1]);
E 252
E 251
			break;

E 171
I 122
		  case '$':		/* define macro */
D 134
			define(buf[1], newstr(&buf[2]), e);
E 134
I 134
			define(bp[1], newstr(&bp[2]), e);
E 134
			break;

E 122
I 88
D 286
		  case '\0':		/* blank line; ignore */
E 286
I 286
		  case '.':		/* terminate file */
			nomore = TRUE;
E 286
			break;

E 88
I 15
D 56
		  case 'C':		/* message class */
			(void) sscanf(&buf[1], "%hd", &CurEnv->e_class);
			break;

E 56
E 15
D 67
		  case 'M':		/* define macro */
D 56
			define(buf[1], newstr(&buf[2]));
E 56
I 56
D 61
			define(buf[1], newstr(&buf[2]), e);
E 61
I 61
			if (full)
				define(buf[1], newstr(&buf[2]), e);
E 61
E 56
E 10
E 7
			break;

E 67
E 2
		  default:
D 56
			syserr("readqf(%s): bad line \"%s\"", cf, buf);
E 56
I 56
D 88
			syserr("readqf(%s): bad line \"%s\"", e->e_id, buf);
E 88
I 88
D 189
			syserr("readqf(%s:%d): bad line \"%s\"", e->e_id,
E 189
I 189
D 228
			syserr("readqf: bad line \"%s\"", e->e_id,
E 189
D 134
				LineNumber, buf);
E 134
I 134
				LineNumber, bp);
E 228
I 228
D 234
			syserr("readqf: %s: line %s: bad line \"%s\"",
E 234
I 234
			syserr("readqf: %s: line %d: bad line \"%s\"",
E 234
				qf, LineNumber, bp);
E 228
E 134
E 88
E 56
D 197
			break;
E 197
I 197
			fclose(qfp);
D 264
			rename(qf, queuename(e, 'Q'));
E 264
I 264
			loseqfile(e, "unrecognized line");
E 264
			return FALSE;
E 197
		}
I 134

		if (bp != buf)
			free(bp);
E 134
I 111
D 124
		/*
		**  The `C' queue file command operates on the next line,
		**  so we use "gotctluser" to maintain state as follows:
		**      0 - no controlling user,
		**      1 - controlling user has been set but not used,
		**      2 - controlling user must be used on next iteration.
		*/
		if (gotctluser == 1)
			gotctluser++;
		else if (gotctluser == 2)
		{
			clrctluser();
			gotctluser = 0;
		}
E 124
E 111
	}
I 56
D 228

I 111
D 124
	/* clear controlling user in case we break out prematurely */
	clrctluser();

E 124
E 111
I 88
D 90
	fclose(qfp);
E 90
I 90
D 110
	(void) fclose(qfp);
E 110
E 90
E 88
	FileName = NULL;
E 228
I 88

	/*
	**  If we haven't read any lines, this queue file is empty.
	**  Arrange to remove it without referencing any null pointers.
	*/

	if (LineNumber == 0)
	{
		errno = 0;
		e->e_flags |= EF_CLRQUEUE | EF_FATALERRS | EF_RESPONSE;
	}
I 270
	else
	{
		/*
		**  Arrange to read the data file.
		*/

		p = queuename(e, 'd');
		e->e_dfp = fopen(p, "r");
		if (e->e_dfp == NULL)
		{
			syserr("readqf: cannot open %s", p);
		}
D 272
		else if (fstat(fileno(e->e_dfp), &st) >= 0)
E 272
I 272
		else
E 272
		{
D 272
			e->e_msgsize = st.st_size;
			e->e_dfdev = st.st_dev;
			e->e_dfino = st.st_ino;
E 272
I 272
			e->e_flags |= EF_HAS_DF;
			if (fstat(fileno(e->e_dfp), &st) >= 0)
			{
				e->e_msgsize = st.st_size;
				e->e_dfdev = st.st_dev;
				e->e_dfino = st.st_ino;
			}
E 272
		}
	}

E 270
I 110
D 119
	return qfp;
E 119
I 119
	return TRUE;
E 119
E 110
E 88
E 56
D 65
}
/*
**  TIMEOUT -- process timeout on queue file.
**
**	Parameters:
D 54
**		w -- pointer to work request that timed out.
E 54
I 54
**		e -- the envelope that timed out.
E 54
**
**	Returns:
**		none.
**
**	Side Effects:
**		Returns a message to the sender saying that this
**		message has timed out.
*/

D 54
timeout(w)
	register WORK *w;
E 54
I 54
timeout(e)
	register ENVELOPE *e;
E 54
{
I 25
	char buf[MAXLINE];
D 37
	extern char *TextTimeOut;
E 37
I 37
	extern char *pintvl();
E 37

E 25
D 2
	printf("timeout(%s)\n", w->w_name);
E 2
I 2
# ifdef DEBUG
D 29
	if (Debug > 0)
E 29
I 29
	if (tTd(40, 3))
E 29
D 54
		printf("timeout(%s)\n", w->w_name);
E 54
I 54
		printf("timeout(%s)\n", e->e_id);
E 54
# endif DEBUG
I 54
	e->e_to = NULL;
E 54
I 16
	message(Arpa_Info, "Message has timed out");
E 16

	/* return message to sender */
D 15
	(void) returntosender("Cannot send mail for three days");
E 15
I 15
D 25
	(void) returntosender("Cannot send mail for three days",
			      &CurEnv->e_from, TRUE);
E 25
I 25
D 37
	(void) sprintf(buf, "Cannot send mail for %s", TextTimeOut);
E 37
I 37
	(void) sprintf(buf, "Cannot send mail for %s", pintvl(TimeOut, FALSE));
E 37
D 54
	(void) returntosender(buf, &CurEnv->e_from, TRUE);
E 54
I 54
	(void) returntosender(buf, &e->e_from, TRUE);
E 54
E 25
E 15

	/* arrange to remove files from queue */
D 14
	QueueUp = FALSE;
E 14
I 14
D 37
	CurEnv->e_queueup = FALSE;
E 37
I 37
D 54
	CurEnv->e_dontqueue = TRUE;
E 54
I 54
	e->e_flags |= EF_CLRQUEUE;
E 65
I 61
}
/*
**  PRINTQUEUE -- print out a representation of the mail queue
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Prints a listing of the mail queue on the standard output.
*/

I 283
void
E 283
printqueue()
{
	register WORK *w;
	FILE *f;
I 63
	int nrequests;
E 63
	char buf[MAXLINE];
I 153

	/*
	**  Check for permission to print the queue
	*/

D 159
	if (bitset(PRIV_RESTRMAILQ, PrivacyFlags))
E 159
I 159
D 198
	if (bitset(PRIV_RESTRMAILQ, PrivacyFlags) && getuid() != 0)
E 198
I 198
D 209
	if (bitset(PRIV_RESTRMAILQ, PrivacyFlags) && RealUid != 0)
E 209
I 209
	if (bitset(PRIV_RESTRICTMAILQ, PrivacyFlags) && RealUid != 0)
E 209
E 198
E 159
	{
		struct stat st;
I 159
# ifdef NGROUPS
		int n;
D 201
		int gidset[NGROUPS];
E 201
I 201
		GIDSET_T gidset[NGROUPS];
E 201
# endif
E 159

D 158
		if (stat(QueueDir, &st) <= 0)
E 158
I 158
		if (stat(QueueDir, &st) < 0)
E 158
		{
			syserr("Cannot stat %s", QueueDir);
			return;
		}
I 159
# ifdef NGROUPS
		n = getgroups(NGROUPS, gidset);
		while (--n >= 0)
		{
			if (gidset[n] == st.st_gid)
				break;
		}
D 284
		if (n < 0)
E 284
I 284
		if (n < 0 && RealGid != st.st_gid)
E 284
# else
E 159
D 198
		if (getgid() != st.st_gid)
E 198
I 198
		if (RealGid != st.st_gid)
E 198
I 159
# endif
E 159
		{
			usrerr("510 You are not permitted to see the queue");
			setstat(EX_NOPERM);
			return;
		}
	}
E 153
I 111
D 124
	char cbuf[MAXLINE];
E 124
E 111

	/*
	**  Read and order the queue.
	*/

D 63
	orderq();
E 63
I 63
D 88
	nrequests = orderq();
E 88
I 88
	nrequests = orderq(TRUE);
E 88
E 63

	/*
	**  Print the work list that we have read.
	*/

	/* first see if there is anything */
D 63
	if (WorkQ == NULL)
E 63
I 63
	if (nrequests <= 0)
E 63
	{
D 63
		printf("\nMail queue is empty\n");
E 63
I 63
		printf("Mail queue is empty\n");
E 63
		return;
	}

I 110
D 119
	la = getla();	/* get load average */
E 119
I 119
	CurrentLA = getla();	/* get load average */
E 119

E 110
D 63
	printf("\n\t\tMail Queue\n");
	printf("--QID-- --Size-- -----Q Time----- --Sender/Recipient--\n");
E 63
I 63
D 66
	printf("\t\tMail Queue (%d requests", nrequests);
E 66
I 66
	printf("\t\tMail Queue (%d request%s", nrequests, nrequests == 1 ? "" : "s");
E 66
D 102
	if (nrequests > WLSIZE)
		printf(", only %d printed", WLSIZE);
E 102
I 102
D 280
	if (nrequests > QUEUESIZE)
		printf(", only %d printed", QUEUESIZE);
E 280
I 280
	if (nrequests > WorkListSize)
		printf(", only %d printed", WorkListSize);
E 280
E 102
D 94
	printf(")\n--QID-- --Size-- -----Q-Time----- ------------Sender/Recipient------------\n");
E 94
I 94
	if (Verbose)
D 99
		printf(")\n--QID-- --Size-- -Priority- -----Q-Time----- --------Sender/Recipient--------\n");
E 99
I 99
D 165
		printf(")\n--QID-- --Size-- -Priority- ---Q-Time--- -----------Sender/Recipient-----------\n");
E 165
I 165
		printf(")\n--Q-ID-- --Size-- -Priority- ---Q-Time--- -----------Sender/Recipient-----------\n");
E 165
E 99
	else
D 165
		printf(")\n--QID-- --Size-- -----Q-Time----- ------------Sender/Recipient------------\n");
E 165
I 165
		printf(")\n--Q-ID-- --Size-- -----Q-Time----- ------------Sender/Recipient------------\n");
E 165
E 94
E 63
	for (w = WorkQ; w != NULL; w = w->w_next)
	{
		struct stat st;
I 63
D 67
		char lf[20];
E 67
		auto time_t submittime = 0;
D 271
		long dfsize = -1;
E 271
I 271
		long dfsize;
E 271
I 171
		int flags = 0;
I 246
		int qfver;
E 246
E 171
I 81
D 85
		int fd;
E 85
D 82
# ifndef FLOCK
E 82
E 81
I 67
D 110
		char lf[20];
E 110
I 81
D 82
# endif FLOCK
E 82
E 81
D 279
		char message[MAXLINE];
E 279
I 279
		char statmsg[MAXLINE];
E 279
I 181
D 265
		char bodytype[MAXNAME];
E 265
I 265
		char bodytype[MAXNAME + 1];
E 265
E 181
I 120
D 161
# ifdef LOCKF
		struct flock lfd;
# endif
E 161
E 120
I 88
D 192
		extern bool shouldqueue();
I 161
		extern bool lockfile();
E 192
E 161
E 88
E 67
E 63

I 211
		printf("%8s", w->w_name + 2);
E 211
I 81
		f = fopen(w->w_name, "r");
		if (f == NULL)
		{
I 211
			printf(" (job completed)\n");
E 211
			errno = 0;
			continue;
		}
I 271
		w->w_name[0] = 'd';
		if (stat(w->w_name, &st) >= 0)
			dfsize = st.st_size;
		else
			dfsize = -1;
E 271
E 81
D 167
		printf("%7s", w->w_name + 2);
E 167
I 167
D 211
		printf("%8s", w->w_name + 2);
E 211
E 167
I 116
D 161
# ifdef LOCKF
D 117
		if (flock(fileno(f), F_TEST, 0) < 0)
E 117
I 117
D 120
		if (lockf(fileno(f), F_TEST, 0) < 0)
E 120
I 120
		lfd.l_type = F_RDLCK;
		lfd.l_whence = lfd.l_start = lfd.l_len = 0;
		if (fcntl(fileno(f), F_GETLK, &lfd) < 0 || lfd.l_type != F_UNLCK)
E 120
E 117
# else
E 116
I 81
D 82
# ifdef FLOCK
		fd = fileno(f);

		if (flock(fd, LOCK_EX|LOCK_NB) < 0)
		{
			printf("*");
		}
		else
		{
			flock(fd, LOCK_UN);
			printf(" ");
		}
# else FLOCK
E 82
E 81
I 63
D 86
		strcpy(lf, w->w_name);
E 86
I 86
D 110
		(void) strcpy(lf, w->w_name);
E 86
		lf[0] = 'l';
		if (stat(lf, &st) >= 0)
E 110
I 110
		if (flock(fileno(f), LOCK_SH|LOCK_NB) < 0)
I 116
# endif
E 161
I 161
D 210
		if (!lockfile(fileno(f), w->w_name, LOCK_SH|LOCK_NB))
E 210
I 210
D 239
		if (!lockfile(fileno(f), w->w_name, NULL, LOCK_SH|LOCK_NB))
E 239
I 239
		if (w->w_lock)
E 239
E 210
E 161
E 116
E 110
			printf("*");
I 88
D 136
		else if (shouldqueue(w->w_pri))
E 136
I 136
		else if (shouldqueue(w->w_pri, w->w_ctime))
E 136
			printf("X");
E 88
		else
			printf(" ");
I 81
D 82
# endif FLOCK
E 82
E 81
		errno = 0;
E 63
D 81
		f = fopen(w->w_name, "r");
		if (f == NULL)
		{
			printf(" (finished)\n");
I 63
			errno = 0;
E 63
			continue;
		}
E 81
I 81

E 81
I 67
D 181
		message[0] = '\0';
E 181
I 181
D 279
		message[0] = bodytype[0] = '\0';
E 279
I 279
		statmsg[0] = bodytype[0] = '\0';
E 279
I 246
		qfver = 0;
E 246
E 181
I 111
D 124
		cbuf[0] = '\0';
E 124
E 111
E 67
D 63
		(void) fstat(fileno(f), &st);
		printf(" %8ld", st.st_size);
E 63
		while (fgets(buf, sizeof buf, f) != NULL)
		{
I 122
			register int i;
I 171
			register char *p;
E 171

E 122
D 63
			auto long ti;

E 63
			fixcrlf(buf, TRUE);
			switch (buf[0])
			{
I 246
			  case 'V':	/* queue file version */
				qfver = atoi(&buf[1]);
				break;

E 246
I 67
			  case 'M':	/* error message */
D 86
				strcpy(message, &buf[1]);
E 86
I 86
D 122
				(void) strcpy(message, &buf[1]);
E 122
I 122
D 279
				if ((i = strlen(&buf[1])) >= sizeof message)
D 171
					i = sizeof message;
E 171
I 171
					i = sizeof message - 1;
E 171
				bcopy(&buf[1], message, i);
				message[i] = '\0';
E 279
I 279
				if ((i = strlen(&buf[1])) >= sizeof statmsg)
					i = sizeof statmsg - 1;
				bcopy(&buf[1], statmsg, i);
				statmsg[i] = '\0';
E 279
E 122
E 86
				break;

I 181
			  case 'B':	/* body type */
				if ((i = strlen(&buf[1])) >= sizeof bodytype)
					i = sizeof bodytype - 1;
				bcopy(&buf[1], bodytype, i);
				bodytype[i] = '\0';
				break;

E 181
E 67
			  case 'S':	/* sender name */
I 67
D 76
				if (message[0] != '\0')
				{
					(void) strcat(buf, " (");
					(void) strcat(buf, message);
					(void) strcat(buf, ")");
				}
E 67
D 63
				printf(" %.20s", &buf[1]);
E 63
I 63
				printf("%8d %.16s %.40s", dfsize,
E 76
I 76
D 77
				printf("%8d %.16s %.45s", dfsize,
E 77
I 77
D 94
				printf("%8ld %.16s %.45s", dfsize,
E 77
E 76
					ctime(&submittime), &buf[1]);
E 94
I 94
				if (Verbose)
D 98
					printf("%8ld %10ld %.16s %.37s", dfsize,
					    w->w_pri, ctime(&submittime),
E 98
I 98
D 171
					printf("%8ld %10ld %.12s %.38s", dfsize,
					    w->w_pri, ctime(&submittime) + 4,
E 171
I 171
					printf("%8ld %10ld%c%.12s %.38s",
					    dfsize,
					    w->w_pri,
					    bitset(EF_WARNING, flags) ? '+' : ' ',
					    ctime(&submittime) + 4,
E 171
E 98
					    &buf[1]);
				else
					printf("%8ld %.16s %.45s", dfsize,
					    ctime(&submittime), &buf[1]);
E 94
I 76
D 181
				if (message[0] != '\0')
D 88
					printf("\n\t\t\t\t  (%.43s)", message);
E 88
I 88
D 98
					printf("\n\t\t (%.62s)", message);
E 98
I 98
					printf("\n\t\t (%.60s)", message);
E 181
I 181
D 279
				if (message[0] != '\0' || bodytype[0] != '\0')
E 279
I 279
				if (statmsg[0] != '\0' || bodytype[0] != '\0')
E 279
				{
					printf("\n    %10.10s", bodytype);
D 279
					if (message[0] != '\0')
						printf("   (%.60s)", message);
E 279
I 279
					if (statmsg[0] != '\0')
						printf("   (%.60s)", statmsg);
E 279
				}
E 181
E 98
E 88
E 76
E 63
				break;
I 119

E 119
I 111
			  case 'C':	/* controlling user */
D 124
				if (strlen(buf) < MAXLINE-3)	/* sanity */
					(void) strcat(buf, ") ");
				cbuf[0] = cbuf[1] = '(';
				(void) strncpy(&cbuf[2], &buf[1], MAXLINE-1);
				cbuf[MAXLINE-1] = '\0';
E 124
I 124
				if (Verbose)
D 125
					printf("\n\t\t\t\t\t (---%.30s---)", &buf[1]);
E 125
I 125
D 165
					printf("\n\t\t\t\t     (---%.34s---)", &buf[1]);
E 165
I 165
					printf("\n\t\t\t\t      (---%.34s---)",
						&buf[1]);
E 165
E 125
E 124
				break;
E 111

			  case 'R':	/* recipient name */
I 246
				p = &buf[1];
				if (qfver >= 1)
				{
					p = strchr(p, ':');
					if (p == NULL)
						break;
					p++;
				}
E 246
I 111
D 124
				if (cbuf[0] != '\0') {
					/* prepend controlling user to `buf' */
					(void) strncat(cbuf, &buf[1],
					              MAXLINE-strlen(cbuf));
					cbuf[MAXLINE-1] = '\0';
					(void) strcpy(buf, cbuf);
					cbuf[0] = '\0';
				}
E 124
E 111
D 63
				printf("\n\t\t\t\t  %.20s", &buf[1]);
E 63
I 63
D 76
				printf("\n\t\t\t\t  %.40s", &buf[1]);
E 76
I 76
D 94
				printf("\n\t\t\t\t  %.45s", &buf[1]);
E 94
I 94
				if (Verbose)
D 98
					printf("\n\t\t\t\t\t     %.37s", &buf[1]);
E 98
I 98
D 165
					printf("\n\t\t\t\t\t %.38s", &buf[1]);
E 165
I 165
D 246
					printf("\n\t\t\t\t\t  %.38s", &buf[1]);
E 246
I 246
					printf("\n\t\t\t\t\t  %.38s", p);
E 246
E 165
E 98
				else
D 165
					printf("\n\t\t\t\t  %.45s", &buf[1]);
E 165
I 165
D 246
					printf("\n\t\t\t\t   %.45s", &buf[1]);
E 246
I 246
					printf("\n\t\t\t\t   %.45s", p);
E 246
E 165
E 94
E 76
E 63
				break;

			  case 'T':	/* creation time */
D 63
				sscanf(&buf[1], "%ld", &ti);
				printf(" %.16s", ctime(&ti));
E 63
I 63
D 86
				sscanf(&buf[1], "%ld", &submittime);
E 86
I 86
D 88
				(void) sscanf(&buf[1], "%ld", &submittime);
E 88
I 88
				submittime = atol(&buf[1]);
E 88
E 86
E 63
D 271
				break;
I 63

			  case 'D':	/* data file name */
				if (stat(&buf[1], &st) >= 0)
					dfsize = st.st_size;
E 271
				break;
I 171

			  case 'F':	/* flag bits */
				for (p = &buf[1]; *p != '\0'; p++)
				{
					switch (*p)
					{
					  case 'w':
						flags |= EF_WARNING;
						break;
					}
				}
E 171
E 63
			}
		}
I 63
		if (submittime == (time_t) 0)
			printf(" (no control file)");
E 63
		printf("\n");
D 86
		fclose(f);
E 86
I 86
		(void) fclose(f);
E 86
	}
E 61
E 54
E 37
E 14
E 2
}
I 8

D 133
# endif QUEUE
E 133
I 133
# endif /* QUEUE */
E 133
I 81
/*
**  QUEUENAME -- build a file name in the queue directory for this envelope.
**
**	Assigns an id code if one does not already exist.
**	This code is very careful to avoid trashing existing files
**	under any circumstances.
D 110
**		We first create an nf file that is only used when
**		assigning an id.  This file is always empty, so that
**		we can never accidently truncate an lf file.
E 110
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
D 110
**		Will create the lf and qf files if no id code is
E 110
I 110
D 119
**		Will create the qf file if no id code is
E 110
**		already assigned.  This will cause the envelope
**		to be modified.
E 119
I 119
**		If no id code is already assigned, queuename will
**		assign an id code, create a qf file, and leave a
**		locked, open-for-write file pointer in the envelope.
E 119
*/

char *
queuename(e, type)
	register ENVELOPE *e;
D 189
	char type;
E 189
I 189
	int type;
E 189
{
D 161
	static char buf[MAXNAME];
E 161
	static int pid = -1;
I 165
D 172
	char c0;
E 165
D 160
	char c1 = 'A';
	char c2 = 'A';
E 160
I 160
	static char c1 = 'A';
	static char c2 = 'A';
E 172
I 172
	static char c0;
	static char c1;
	static char c2;
E 172
I 165
	time_t now;
	struct tm *tm;
E 165
I 161
D 265
	static char buf[MAXNAME];
E 265
I 265
	static char buf[MAXNAME + 1];
E 265
D 192
	extern bool lockfile();
E 192
E 161
E 160

	if (e->e_id == NULL)
	{
		char qf[20];
D 110
		char nf[20];
D 82
# ifndef FLOCK
E 82
		char lf[20];
E 110
D 82
# endif FLOCK
E 82

		/* find a unique id */
		if (pid != getpid())
		{
			/* new process -- start back at "AA" */
			pid = getpid();
I 165
			now = curtime();
			tm = localtime(&now);
			c0 = 'A' + tm->tm_hour;
E 165
			c1 = 'A';
			c2 = 'A' - 1;
		}
D 165
		(void) sprintf(qf, "qfAA%05d", pid);
E 165
I 165
		(void) sprintf(qf, "qf%cAA%05d", c0, pid);
E 165
D 82
# ifndef FLOCK
E 82
D 86
		strcpy(lf, qf);
E 86
I 86
D 110
		(void) strcpy(lf, qf);
E 86
		lf[0] = 'l';
D 82
# endif FLOCK
E 82
D 86
		strcpy(nf, qf);
E 86
I 86
		(void) strcpy(nf, qf);
E 86
		nf[0] = 'n';
E 110

		while (c1 < '~' || c2 < 'Z')
		{
			int i;
I 120
D 161
# ifdef LOCKF
			struct flock lfd;
# endif
E 161
E 120

			if (c2 >= 'Z')
			{
				c1++;
				c2 = 'A' - 1;
			}
D 82
			nf[2] = qf[2] = c1;
			nf[3] = qf[3] = ++c2;
# ifndef FLOCK
			lf[2] = c1;
			lf[3] = c2;
# endif FLOCK
E 82
I 82
D 110
			lf[2] = nf[2] = qf[2] = c1;
			lf[3] = nf[3] = qf[3] = ++c2;
E 110
I 110
D 165
			qf[2] = c1;
			qf[3] = ++c2;
E 165
I 165
			qf[3] = c1;
			qf[4] = ++c2;
E 165
E 110
E 82
D 109
# ifdef DEBUG
E 109
			if (tTd(7, 20))
D 110
				printf("queuename: trying \"%s\"\n", nf);
E 110
I 110
				printf("queuename: trying \"%s\"\n", qf);
E 110
D 109
# endif DEBUG
E 109

D 82
# ifdef FLOCK
			i = open(nf, O_WRONLY|O_CREAT|O_EXCL, FileMode);
			if (i >= 0)
			{
				(void) flock(i, LOCK_EX|LOCK_NB);
				if (link(nf, qf) < 0)
				{
					(void) close(i);
					(void) unlink(nf);
					continue;
				}
				e->e_qfp = fdopen(i, "w");
				(void) unlink(nf);
				break;
			}
# else FLOCK
E 82
D 110
# ifdef QUEUE
			if (access(lf, 0) >= 0 || access(qf, 0) >= 0)
				continue;
			errno = 0;
			i = creat(nf, FileMode);
			if (i < 0)
			{
				(void) unlink(nf);	/* kernel bug */
I 108
				if (errno == ENOSPC) {
E 110
I 110
			i = open(qf, O_WRONLY|O_CREAT|O_EXCL, FileMode);
D 119
			if (i < 0) {
				if (errno != EEXIST) {
E 110
					syserr("queuename: Cannot create \"%s\" in \"%s\"",
D 110
						nf, QueueDir);
E 110
I 110
						qf, QueueDir);
E 110
					exit(EX_UNAVAILABLE);
				}
E 108
D 110
				continue;
			}
			(void) close(i);
			i = link(nf, lf);
			(void) unlink(nf);
			if (i < 0)
				continue;
			if (link(lf, qf) >= 0)
E 110
I 110
			} else {
				(void) close(i);
E 119
I 119
			if (i < 0)
			{
				if (errno == EEXIST)
					continue;
D 215
				syserr("queuename: Cannot create \"%s\" in \"%s\"",
					qf, QueueDir);
E 215
I 215
				syserr("queuename: Cannot create \"%s\" in \"%s\" (euid=%d)",
					qf, QueueDir, geteuid());
E 215
				exit(EX_UNAVAILABLE);
			}
D 161
# ifdef LOCKF
D 120
			if (lockf(i, F_TLOCK, 0) >= 0)
E 120
I 120
			lfd.l_type = F_WRLCK;
			lfd.l_whence = lfd.l_start = lfd.l_len = 0;
			if (fcntl(i, F_SETLK, &lfd) >= 0)
E 120
# else
			if (flock(i, LOCK_EX|LOCK_NB) >= 0)
# endif
E 161
I 161
D 210
			if (lockfile(i, qf, LOCK_EX|LOCK_NB))
E 210
I 210
			if (lockfile(i, qf, NULL, LOCK_EX|LOCK_NB))
E 210
E 161
			{
				e->e_lockfp = fdopen(i, "w");
E 119
E 110
				break;
D 110
			(void) unlink(lf);
# else QUEUE
D 83
			if (close(creat(qf, FileMode)) < 0)
				continue;
E 83
I 83
			if (close(creat(qf, FileMode)) >= 0)
				break;
E 83
# endif QUEUE
E 110
I 110
			}
I 119

			/* a reader got the file; abandon it and try again */
			(void) close(i);
E 119
E 110
D 82
# endif FLOCK
E 82
		}
		if (c1 >= '~' && c2 >= 'Z')
		{
D 215
			syserr("queuename: Cannot create \"%s\" in \"%s\"",
				qf, QueueDir);
E 215
I 215
			syserr("queuename: Cannot create \"%s\" in \"%s\" (euid=%d)",
				qf, QueueDir, geteuid());
E 215
			exit(EX_OSERR);
		}
		e->e_id = newstr(&qf[2]);
		define('i', e->e_id, e);
D 109
# ifdef DEBUG
E 109
		if (tTd(7, 1))
			printf("queuename: assigned id %s, env=%x\n", e->e_id, e);
I 218
		if (tTd(7, 9))
		{
			printf("  lockfd=");
			dumpfd(fileno(e->e_lockfp), TRUE, FALSE);
		}
E 218
# ifdef LOG
D 145
		if (LogLevel > 16)
E 145
I 145
		if (LogLevel > 93)
E 145
			syslog(LOG_DEBUG, "%s: assigned id", e->e_id);
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
E 133
D 109
# endif DEBUG
E 109
	}

	if (type == '\0')
		return (NULL);
	(void) sprintf(buf, "%cf%s", type, e->e_id);
D 109
# ifdef DEBUG
E 109
	if (tTd(7, 2))
		printf("queuename: %s\n", buf);
D 109
# endif DEBUG
E 109
	return (buf);
}
/*
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

I 283
void
E 283
unlockqueue(e)
	ENVELOPE *e;
{
I 160
	if (tTd(51, 4))
		printf("unlockqueue(%s)\n", e->e_id);

E 160
I 119
	/* if there is a lock file in the envelope, close it */
	if (e->e_lockfp != NULL)
D 160
		fclose(e->e_lockfp);
E 160
I 160
		xfclose(e->e_lockfp, "unlockqueue", e->e_id);
E 160
	e->e_lockfp = NULL;

I 168
	/* don't create a queue id if we don't already have one */
	if (e->e_id == NULL)
		return;

E 168
E 119
	/* remove the transcript */
D 109
#ifdef DEBUG
E 109
# ifdef LOG
D 145
	if (LogLevel > 19)
E 145
I 145
	if (LogLevel > 87)
E 145
		syslog(LOG_DEBUG, "%s: unlock", e->e_id);
D 133
# endif LOG
E 133
I 133
# endif /* LOG */
E 133
D 160
	if (!tTd(51, 4))
E 160
I 160
	if (!tTd(51, 104))
E 160
D 109
#endif DEBUG
E 109
		xunlink(queuename(e, 'x'));

I 111
}
/*
D 124
**  GETCTLUSER -- return controlling user if mailing to prog or file
E 124
I 124
**  SETCTLUSER -- create a controlling address
E 124
**
D 124
**	Check for a "|" or "/" at the beginning of the address.  If
**	found, return a controlling username.
E 124
I 124
**	Create a fake "address" given only a local login name; this is
**	used as a "controlling user" for future recipient addresses.
E 124
**
**	Parameters:
D 124
**		a - the address to check out
E 124
I 124
**		user -- the user name of the controlling user.
E 124
**
**	Returns:
D 124
**		Either NULL, if we werent mailing to a program or file,
**		or a controlling user name (possibly in getpwuid's
**		static buffer).
E 124
I 124
**		An address descriptor for the controlling user.
E 124
**
**	Side Effects:
**		none.
*/

D 124
char *
getctluser(a)
	ADDRESS *a;
E 124
I 124
ADDRESS *
setctluser(user)
	char *user;
E 124
{
D 124
	extern ADDRESS *getctladdr();
E 124
I 124
	register ADDRESS *a;
E 124
	struct passwd *pw;
I 183
	char *p;
E 183
D 124
	char *retstr;
E 124

	/*
D 124
	**  Get unquoted user for file, program or user.name check.
	**  N.B. remove this code block to always emit controlling
	**  addresses (at the expense of backward compatibility).
E 124
I 124
	**  See if this clears our concept of controlling user.
E 124
	*/

D 124
	{
		char buf[MAXNAME];
		(void) strncpy(buf, a->q_paddr, MAXNAME);
		buf[MAXNAME-1] = '\0';
		stripquotes(buf, TRUE);
E 124
I 124
D 184
	if (user == NULL || *user == '\0')
D 164
		return NULL;
E 164
I 164
		user = DefUser;
E 184
I 184
D 200
	if (user == NULL)
		user = "";
E 200
I 200
	if (user == NULL || *user == '\0')
		return NULL;
E 200
E 184
E 164
E 124

D 124
		if (buf[0] != '|' && buf[0] != '/')
			return((char *)NULL);
	}

	a = getctladdr(a);		/* find controlling address */

	if (a != NULL && a->q_uid != 0 && (pw = getpwuid(a->q_uid)) != NULL)
		retstr = pw->pw_name;
	else				/* use default user */
		retstr = DefUser;

	if (tTd(40, 5))
		printf("Set controlling user for `%s' to `%s'\n",
		       (a == NULL)? "<null>": a->q_paddr, retstr);

	return(retstr);
}
/*
**  SETCTLUSER - sets `CtlUser' to controlling user
**  CLRCTLUSER - clears controlling user (no params, nothing returned)
**
**	These routines manipulate `CtlUser'.
**
**	Parameters:
**		str  - controlling user as passed to setctluser()
**
**	Returns:
**		None.
**
**	Side Effects:
**		`CtlUser' is changed.
*/

static char CtlUser[MAXNAME];

setctluser(str)
register char *str;
{
	(void) strncpy(CtlUser, str, MAXNAME);
	CtlUser[MAXNAME-1] = '\0';
}

clrctluser()
{
	CtlUser[0] = '\0';
}

/*
**  SETCTLADDR -- create a controlling address
**
**	If global variable `CtlUser' is set and we are given a valid
**	address, make that address a controlling address; change the
**	`q_uid', `q_gid', and `q_ruser' fields and set QGOODUID.
**
**	Parameters:
**		a - address for which control uid/gid info may apply
**
**	Returns:
**		None.	
**
**	Side Effects:
**		Fills in uid/gid fields in address and sets QGOODUID
**		flag if appropriate.
*/

setctladdr(a)
	ADDRESS *a;
{
	struct passwd *pw;

E 124
	/*
D 124
	**  If there is no current controlling user, or we were passed a
	**  NULL addr ptr or we already have a controlling user, return.
E 124
I 124
	**  Set up addr fields for controlling user.
E 124
	*/

D 124
	if (CtlUser[0] == '\0' || a == NULL || a->q_ruser)
		return;

	/*
	**  Set up addr fields for controlling user.  If `CtlUser' is no
	**  longer valid, use the default user/group.
	*/

	if ((pw = getpwnam(CtlUser)) != NULL)
E 124
I 124
	a = (ADDRESS *) xalloc(sizeof *a);
	bzero((char *) a, sizeof *a);
I 183

	p = strchr(user, ':');
	if (p != NULL)
		*p++ = '\0';
E 183
D 184
	if ((pw = getpwnam(user)) != NULL)
E 184
I 184
D 273
	if (*user != '\0' && (pw = getpwnam(user)) != NULL)
E 273
I 273
	if (*user != '\0' && (pw = sm_getpwnam(user)) != NULL)
E 273
E 184
E 124
	{
D 124
		if (a->q_home)
			free(a->q_home);
E 124
D 232
		a->q_home = newstr(pw->pw_dir);
E 232
I 232
		if (strcmp(pw->pw_dir, "/") == 0)
			a->q_home = "";
		else
			a->q_home = newstr(pw->pw_dir);
E 232
		a->q_uid = pw->pw_uid;
		a->q_gid = pw->pw_gid;
D 124
		a->q_ruser = newstr(CtlUser);
E 124
I 124
D 139
		a->q_ruser = newstr(user);
E 139
I 139
D 272
		a->q_user = newstr(user);
E 272
I 184
		a->q_flags |= QGOODUID;
E 184
E 139
E 124
	}
I 272

	if (*user != '\0')
		a->q_user = newstr(user);
	else if (p != NULL)
		a->q_user = newstr(p);
E 272
	else
D 272
	{
E 272
D 184
		a->q_uid = DefUid;
		a->q_gid = DefGid;
E 184
D 139
		a->q_ruser = newstr(DefUser);
E 139
I 139
		a->q_user = newstr(DefUser);
E 139
D 272
	}
E 272

I 138
D 139
	a->q_user = a->q_ruser;
E 139
E 138
D 154
	a->q_flags |= QGOODUID;		/* flag as a "ctladdr"  */
E 154
I 154
D 184
	a->q_flags |= QGOODUID|QPRIMARY;	/* flag as a "ctladdr"  */
E 184
I 184
	a->q_flags |= QPRIMARY;		/* flag as a "ctladdr"  */
E 184
E 154
I 131
	a->q_mailer = LocalMailer;
I 183
	if (p == NULL)
		a->q_paddr = a->q_user;
	else
		a->q_paddr = newstr(p);
E 183
E 131
D 124

	if (tTd(40, 5))
		printf("Restored controlling user for `%s' to `%s'\n",
		       a->q_paddr, a->q_ruser);
E 124
I 124
	return a;
I 264
}
/*
**  LOSEQFILE -- save the qf as Qf and try to let someone know
**
**	Parameters:
**		e -- the envelope (e->e_id will be used).
**		why -- reported to whomever can hear.
**
**	Returns:
**		none.
*/

void
loseqfile(e, why)
	register ENVELOPE *e;
	char *why;
{
I 269
	char *p;
E 269
	char buf[40];

	if (e == NULL || e->e_id == NULL)
		return;
	if (strlen(e->e_id) > sizeof buf - 4)
		return;
	strcpy(buf, queuename(e, 'q'));
D 269
	rename(buf, queuename(e, 'Q'));
E 269
I 269
	p = queuename(e, 'Q');
	if (rename(buf, p) < 0)
		syserr("cannot rename(%s, %s), uid=%d", buf, p, geteuid());
E 269
#ifdef LOG
D 269
	syslog(LOG_ALERT, "Losing %s: %s", buf, why);
E 269
I 269
	else if (LogLevel > 0)
		syslog(LOG_ALERT, "Losing %s: %s", buf, why);
E 269
#endif
E 264
E 124
E 111
D 110
# ifdef QUEUE
D 82
# ifndef FLOCK
E 82
	/* last but not least, remove the lock */
	xunlink(queuename(e, 'l'));
D 82
# endif FLOCK
E 82
# endif QUEUE
E 110
}
E 81
E 8
E 1
