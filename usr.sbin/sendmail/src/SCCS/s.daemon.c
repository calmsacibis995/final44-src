h62165
s 00000/00007/01666
d D 8.105 95/06/20 10:46:34 eric 289 288
c h_errno now in conf.h
e
s 00001/00001/01672
d D 8.104 95/06/20 09:37:37 eric 288 287
c better error message
e
s 00001/00001/01672
d D 8.103 95/06/15 11:35:31 eric 287 286
c change name of NoMXforCanon to HasWildcardMX -- old name was too confusing
e
s 00024/00024/01649
d D 8.102 95/06/13 09:22:59 eric 286 285
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00028/00025/01645
d D 8.101 95/06/12 17:27:16 eric 285 284
c clean up myhostname to be better about finding dotted names in the face of
c poorly configured NIS systems
e
s 00002/00001/01668
d D 8.100 95/06/11 12:01:10 eric 284 283
c fix core dump in myhostname
e
s 00001/00003/01668
d D 8.99 95/06/10 12:54:13 eric 283 282
c allow symbolic service names on [IPC] mailers
e
s 00002/00002/01669
d D 8.98 95/06/10 12:38:58 eric 282 281
c count children.  Someday we might reject connections on this basis.
e
s 00021/00009/01650
d D 8.97 95/06/10 07:38:18 eric 281 280
c more myhostname cleanup (why is this so hard?!?)
e
s 00000/00009/01659
d D 8.96 95/05/31 08:49:50 eric 280 279
c move SMTP startup logging to daemon.c so that $_ is set
e
s 00000/00001/01668
d D 8.95 95/05/30 19:24:09 eric 279 278
c change RealUserName from an array to a pointer; move defn to sendmail.h
e
s 00001/00001/01668
d D 8.94 95/05/30 17:25:41 eric 278 277
c move setproctitle() to be before every accept to fix problem
c that looses process title after fork() in BSD-OS 2.0
e
s 00001/00001/01668
d D 8.93 95/05/27 15:29:10 eric 277 276
c patch from John Hawkinson
e
s 00005/00004/01664
d D 8.92 95/05/23 16:44:00 eric 276 275
c compilation glitches on several systems.
e
s 00087/00002/01581
d D 8.91 95/05/22 08:30:01 eric 275 274
c add option to print IP source routing info
e
s 00002/00002/01581
d D 8.90 95/05/19 16:00:14 eric 274 273
c fix compile problems on various platforms
e
s 00013/00002/01570
d D 8.89 95/05/17 07:20:47 eric 273 272
c handle AF_LINK addresses on 4.4BSD networking
e
s 00001/00001/01571
d D 8.88 95/05/16 21:17:17 eric 272 271
c woops -- compilation glitch
e
s 00004/00001/01568
d D 8.87 95/05/16 21:08:30 eric 271 270
c fix possible null pointer dereference in debugging code
e
s 00002/00000/01567
d D 8.86 95/05/15 07:30:39 eric 270 269
c prevent host name buffer overflows
e
s 00005/00000/01562
d D 8.85 95/05/13 08:19:32 eric 269 268
c make DaemonPortOptions values case insensitive & include error on
c unrecognized values
e
s 00001/00000/01561
d D 8.84 95/04/25 07:13:06 eric 268 267
c fix problem sending to user@domain where "domain" has an entry
c but no A or MX records; problem only occurs if it matches as the
c last entry in the resolver search list
e
s 00001/00000/01560
d D 8.83 95/04/24 20:30:17 eric 267 266
c fix (another) botch in IDENT code
e
s 00003/00000/01557
d D 8.82 95/04/22 14:50:54 eric 266 265
c better use of extended DSN status codes
e
s 00001/00001/01556
d D 8.81 95/04/21 09:57:20 eric 265 264
c update copyright notice
e
s 00003/00007/01554
d D 8.80 95/04/20 09:15:46 eric 264 263
c give a message in "delayed" messages caused by name server timeouts
e
s 00001/00001/01560
d D 8.79 95/04/11 06:52:37 eric 263 262
c random minor code cleanup
e
s 00001/00001/01560
d D 8.78 95/04/09 15:53:00 eric 262 261
c add HasWildcardMX suboption to ResolverOptions for special case
e
s 00004/00001/01557
d D 8.77 95/04/08 14:02:57 eric 261 260
c just log failure to find "smtp" service instead of syserring
e
s 00011/00014/01547
d D 8.76 95/03/31 10:52:03 eric 260 258
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00001/00002/01531
d D 8.48.1.5 95/03/28 18:36:30 eric 259 254
i 255
c fix botch in IDENT code
e
s 00008/00000/01553
d D 8.75 95/03/27 11:43:03 eric 258 257
c ignore IDENT responses with OSTYPE == OTHER
e
s 00002/00002/01551
d D 8.74 95/03/14 09:11:02 eric 257 256
c change call to expand() to be more rational (and consistent!)
e
s 00008/00002/01545
d D 8.73 95/03/14 08:18:59 eric 256 255
c be more precise on MAXNAME checking
e
s 00001/00001/01546
d D 8.72 95/03/14 07:55:19 eric 255 253
c fix glitch in IDENT processing that caused it to always fail
e
s 00001/00001/01531
d D 8.48.1.4 95/02/28 15:40:21 eric 254 252
c ibuf type wrong
e
s 00010/00014/01537
d D 8.71 95/02/28 13:40:06 eric 253 251
c fix over-used static buffer
e
s 00009/00008/01523
d D 8.48.1.3 95/02/28 10:58:49 eric 252 249
i 251
c multiple glitches in 8.6.10 -- see ../RELEASE_NOTES for details
e
s 00013/00005/01538
d D 8.70 95/02/24 07:24:18 eric 251 250
c loop on ident result
e
s 00009/00007/01534
d D 8.69 95/02/23 15:50:57 eric 250 247
c cleanup to make gcc -Winitialized happier
e
s 00002/00006/01521
d D 8.48.1.2 95/02/09 17:28:48 eric 249 248
c use cleanstrcpy for copying IDENT string
e
s 00000/00000/01527
d D 8.48.1.1 95/02/07 10:25:07 eric 248 227
i 239
c fix security problem that allows users to put bogus data in qf file
e
s 00001/00001/01540
d D 8.68 95/02/06 07:52:15 eric 247 246
c change for new DSN draft
e
s 00002/00004/01539
d D 8.67 95/01/24 08:27:35 eric 246 245
c fix byte ordering for DaemonAddr; use wordinclass abstraction
e
s 00000/00009/01543
d D 8.66 95/01/07 13:29:56 eric 245 244
c always compile IDENTPROTO in; just default the timeout to zero if
c it doesn't normally work on some system.  This is to avoid having
c to recompile sendmail when a kernel patch comes out.
e
s 00002/00000/01550
d D 8.65 95/01/07 10:35:45 eric 244 243
c arrange for "kill -1" to re-exec sendmail
e
s 00004/00004/01546
d D 8.64 94/12/15 06:24:27 eric 243 242
c fix bogus #ifdef NAMED_BIND (should be #if)
e
s 00001/00003/01549
d D 8.63 94/12/05 15:17:28 eric 242 241
c allow the case where a host name isn't know to gethostbyname --
c as might happen if you were uucp-only (common for Linux, apparently)
e
s 00013/00000/01539
d D 8.62 94/12/05 09:15:41 eric 241 240
c implement DialDelay option
e
s 00006/00005/01533
d D 8.61 94/11/27 15:22:30 eric 240 239
c more DSN hacking
e
s 00009/00003/01529
d D 8.60 94/11/19 16:56:17 eric 239 238
c validate IDENT protocol return value
e
s 00001/00002/01531
d D 8.59 94/08/16 08:20:07 eric 238 237
c fix initial daemon socket open
e
s 00007/00002/01526
d D 8.58 94/07/02 08:17:21 eric 237 236
c re-open daemon socket on accept() error -- there's a bug in SVR4
c that causes it to get "stuck" in an EPROTO state
e
s 00002/00002/01526
d D 8.57 94/07/02 07:45:06 eric 236 235
c avoid SIGTTOU on SVR4 when calling getpeername in background
e
s 00024/00018/01504
d D 8.56 94/06/25 10:20:31 eric 235 234
c updates to really wait for DNS to come up at system boot time;
c this has a lot of heuristics built in
e
s 00002/00001/01520
d D 8.55 94/06/18 09:46:55 eric 234 233
c fall back to gethostbyname even if DNS lookup fails
e
s 00004/00005/01517
d D 8.54 94/06/17 17:40:00 eric 233 232
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00006/00006/01516
d D 8.53 94/06/17 11:12:53 eric 232 231
c Cray fixes from Eric Wassenaar
e
s 00016/00000/01506
d D 8.52 94/05/29 08:06:10 eric 231 230
c avoid automatic DNS domain extensions if you look up an address
c that has a dot on it after deleting the dot for /etc/hosts compatibility
e
s 00001/00001/01505
d D 8.51 94/05/18 10:45:19 eric 230 229
c close daemon socket early to limit possible race condition
e
s 00002/00019/01504
d D 8.50 94/05/15 08:16:38 eric 229 228
c clean up setting of numeric IP addresses (and debug them properly)
e
s 00002/00000/01521
d D 8.49 94/05/15 07:08:02 eric 228 227
c print numeric a.k.a. info
e
s 00002/00000/01519
d D 8.48 94/04/18 06:48:20 eric 227 226
c sleep between retries
e
s 00062/00045/01457
d D 8.47 94/04/18 06:47:39 eric 226 225
c from Eric Wassenaar: retry socket open if failure is due to
c transient condition
e
s 00047/00044/01455
d D 8.46 94/04/17 11:58:37 eric 225 224
c cleanup to avoid bogus listen() if we are just going to close the socket
e
s 00033/00023/01466
d D 8.45 94/04/17 11:13:24 eric 224 223
c insist on a dot in our hostname if you are running DNS
e
s 00098/00067/01391
d D 8.44 94/04/17 07:43:30 eric 223 222
c instead of using accept(0) to turn off connections (which pretty
c much never works), close and later re-open the connection
e
s 00011/00013/01447
d D 8.43 94/04/16 07:36:07 eric 222 221
c bug fixes for $j sanity check and hostname must have dot heuristic
e
s 00033/00000/01427
d D 8.42 94/04/15 09:20:18 eric 221 220
c try to catch cases of $j getting munged in daemon process
e
s 00014/00002/01413
d D 8.41 94/04/13 11:10:56 eric 220 219
c another try to avoid dot-less canonical names
e
s 00014/00009/01401
d D 8.40 94/04/12 14:38:38 eric 219 218
c changes to make inetd and rsh invocations work better
e
s 00014/00000/01396
d D 8.39 94/03/13 09:21:14 eric 218 217
c if gethostbyname fails with a trailing dot, try it without the dot
c for NIS & /etc/hosts back compatibility
e
s 00010/00010/01386
d D 8.38 94/03/11 14:42:12 eric 217 216
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00004/00000/01392
d D 8.37 94/02/08 08:54:14 eric 216 215
c change a daemon child process title ASAP
e
s 00014/00002/01378
d D 8.36 94/02/08 07:55:57 eric 215 214
c fix references to h_errno that weren't in #ifdef NAMED_BIND
e
s 00001/00000/01379
d D 8.35 94/02/06 19:28:58 eric 214 213
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00005/00004/01374
d D 8.34 94/02/06 12:53:29 eric 213 212
c code cleanup
e
s 00009/00010/01369
d D 8.33 94/02/05 12:29:45 eric 212 211
c allow $s to be set to NULL for locally generated mail
e
s 00003/00000/01376
d D 8.32 94/01/22 16:23:57 eric 211 210
c allow setting of ident timeout to zero to turn it off
e
s 00000/00001/01376
d D 8.31 94/01/22 10:29:25 eric 210 209
c avoid unnecessary <sys/time.h> inclusion
e
s 00000/00001/01377
d D 8.30 94/01/08 17:29:20 eric 209 208
c fix problem that was causing the ctladdr of whoever ran the daemon
c (usually root) to own the delivery process
e
s 00003/00004/01375
d D 8.29 93/12/22 10:14:38 eric 208 206
c clean up error messages a bit more
e
s 00003/00004/01375
d R 8.29 93/12/22 09:48:17 eric 207 206
c more cleanup of that message
e
s 00010/00004/01369
d D 8.28 93/12/22 09:23:45 eric 206 205
c improve "Recipient domain name server timed out" message
e
s 00008/00005/01365
d D 8.27 93/12/17 07:06:03 eric 205 204
c default to "smtp" service == 25 for NeXT machines (which are broken)
e
s 00002/00002/01368
d D 8.26 93/11/25 11:23:22 eric 204 203
c work around Ultrix problem: gethostbyname can return large h_length
e
s 00003/00003/01367
d D 8.25 93/11/20 07:29:06 eric 203 202
c IDENTPROTO is a #if not a #ifdef to make it easier to turn it off
e
s 00002/00001/01368
d D 8.24 93/11/14 08:27:09 eric 202 201
c if getpeername returns a family 0 address, assume localhost
e
s 00006/00005/01363
d D 8.23 93/11/11 08:00:11 eric 201 200
c portability changes for Motorola SysV88
e
s 00002/00000/01366
d D 8.22 93/11/08 09:47:29 eric 200 199
c portability to systems that don't have unix domain sockets
e
s 00005/00004/01361
d D 8.21 93/10/31 11:30:10 eric 199 198
c hack to give better error message on DNS timeout
e
s 00002/00002/01363
d D 8.20 93/10/24 14:10:52 eric 198 197
c hooks to make eventual sockaddr_un work properly
e
s 00004/00003/01361
d D 8.19 93/10/23 17:19:02 eric 197 196
c ident fix for multihomed host
e
s 00025/00004/01339
d D 8.18 93/10/21 07:20:14 eric 196 195
c tentative attempts to print UNIX domain sockets properly
e
s 00001/00001/01342
d D 8.17 93/10/17 10:00:11 eric 195 194
c additional debugging information for too many open files problem
e
s 00014/00004/01329
d D 8.16 93/10/16 08:49:51 eric 194 193
c check for possibility of fdopen returning null
e
s 00002/00002/01331
d D 8.15 93/09/22 10:03:05 eric 193 192
c compile cleanup on various systems (mostly AUX)
e
s 00000/00001/01333
d D 8.14 93/09/19 19:23:27 eric 192 191
c NeXT portability changes; cleanup of <sys/wait.h> assumptions
e
s 00010/00010/01324
d D 8.13 93/09/03 09:19:42 eric 191 190
c patch to receive socket code
e
s 00030/00000/01304
d D 8.12 93/09/02 09:45:19 eric 190 189
c arrange to tweak send and receive buffer sizes
e
s 00002/00002/01302
d D 8.11 93/08/27 10:42:57 eric 189 188
c htons(port) if integer port is given
e
s 00000/00004/01304
d D 8.10 93/08/23 10:20:14 eric 188 187
c don't need duplicate declaration of inet_ntoa
e
s 00008/00017/01300
d D 8.9 93/08/23 10:17:32 eric 187 186
c instead of MyIpAddrs, put all [...] names in $=w
e
s 00001/00000/01316
d D 8.8 93/08/23 08:25:12 eric 186 185
c reset SmtpPhase on initial connection so messages are accurate
e
s 00001/00001/01315
d D 8.7 93/08/14 19:14:28 eric 185 184
c add TimeOuts.to_ident to set IDENT protocol timeout
e
s 00005/00002/01311
d D 8.6 93/07/29 08:31:41 eric 184 183
c don't call newstr() macro with arguments with subroutine calls, since
c it double-evaluates
e
s 00002/00003/01311
d D 8.5 93/07/26 09:22:02 eric 183 182
c signal and file locking portability changes
e
s 00008/00000/01306
d D 8.4 93/07/18 14:47:49 eric 182 181
c write command line information in pid file
e
s 00002/00022/01304
d D 8.3 93/07/16 10:30:48 eric 181 180
c SCO cleanup; misc logging adjustments
e
s 00020/00000/01306
d D 8.2 93/07/13 12:58:32 eric 180 179
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00002/00002/01304
d D 8.1 93/06/07 10:29:43 bostic 179 178
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/01306
d D 6.52 93/05/27 11:37:31 eric 178 177
c prototype functions
e
s 00002/00001/01307
d D 6.51 93/05/27 07:45:51 eric 177 176
c fix byte swapping problem in ident code
e
s 00015/00016/01293
d D 6.50 93/05/24 08:30:31 eric 176 175
c remember to dot terminate host name lookups
e
s 00026/00035/01283
d D 6.49 93/05/17 10:28:17 eric 175 174
c first cut at merged map/alias implementation
e
s 00001/00001/01317
d D 6.48 93/05/14 13:52:29 eric 174 173
c use newstr for e_message consistently
e
s 00003/00000/01315
d D 6.47 93/05/13 09:28:02 eric 173 172
c add debugging
e
s 00007/00001/01308
d D 6.46 93/05/11 08:17:49 eric 172 171
c avoid some implicit dependencies on NETINET
e
s 00006/00001/01303
d D 6.45 93/05/07 07:38:00 eric 171 170
c add ListenQueueSize keyword to O (Daemon Options) option
e
s 00007/00001/01297
d D 6.44 93/05/04 20:43:03 eric 170 169
c fix some bogus messages being printed in mailq command
e
s 00038/00009/01260
d D 6.43 93/05/03 12:25:50 eric 169 168
c cache name canonification lookups (in case someone's name
c server is hanging)
e
s 00002/00000/01267
d D 6.42 93/04/30 15:15:55 eric 168 167
c clean up error message printing, especially for deferred messages
e
s 00008/00007/01259
d D 6.41 93/04/21 12:52:42 eric 167 166
c patches to XLA code
e
s 00017/00001/01249
d D 6.40 93/04/18 10:07:19 eric 166 165
c Extended Load Average (XLA) hooks
e
s 00001/00001/01249
d D 6.39 93/04/16 08:48:38 eric 165 164
c fix compilation problem when IDENTPROTO is not defined
e
s 00001/00001/01249
d D 6.38 93/04/15 16:31:07 eric 164 163
c minor botch: use htons on ident port name
e
s 00053/00004/01197
d D 6.37 93/04/14 14:38:48 eric 163 162
c return status information from map lookups and from there from 
c rewrite; this allows higher level code to queue if the name server is down
e
s 00000/00002/01201
d D 6.36 93/04/14 07:34:27 eric 162 161
c move IDENTPROTO #define into conf.h; default it off for ULTRIX
e
s 00017/00000/01186
d D 6.35 93/04/12 14:18:20 eric 161 160
c shorten timeout on reverse name lookup to avoid conflict with
c higher level timeouts
e
s 00021/00002/01165
d D 6.34 93/04/12 09:03:35 eric 160 159
c more socket code generalization
e
s 00016/00010/01151
d D 6.33 93/04/04 16:03:21 eric 159 158
c IDENT cleanup; move loopback checking from srvr to user smtp
e
s 00221/00058/00940
d D 6.32 93/04/04 13:56:57 eric 158 157
c RFC 1413 (IDENT) protocol support
e
s 00004/00004/00994
d D 6.31 93/04/01 08:11:29 eric 157 156
c getservbyname gets a "service", not a "server"
e
s 00001/00000/00997
d D 6.30 93/04/01 08:06:19 eric 156 155
c set CurHostName any time you create a connection to that host
e
s 00088/00023/00909
d D 6.29 93/03/30 12:38:46 eric 155 154
c more network family generalization
e
s 00001/00000/00931
d D 6.28 93/03/30 10:03:40 eric 154 153
c zero CurHostAddr to avoid logging garbage if no addresses can be bound
e
s 00001/00001/00930
d D 6.27 93/03/29 17:40:01 eric 153 152
c inet_aton is too modern for Sun.....
e
s 00084/00011/00847
d D 6.26 93/03/29 12:43:43 eric 152 151
c allow setting of server options
e
s 00008/00001/00850
d D 6.25 93/03/24 07:21:53 eric 151 150
c clean up logging of email received from localhost
e
s 00009/00000/00842
d D 6.24 93/03/23 19:50:51 eric 150 149
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00002/00002/00840
d D 6.23 93/03/23 16:33:56 eric 149 148
c bleah...  one more time
e
s 00002/00003/00840
d D 6.22 93/03/23 16:31:20 eric 148 147
c one more instance of sa_len to delete
e
s 00067/00029/00776
d D 6.21 93/03/23 15:37:06 eric 147 146
c fix generalized socket code so that it doesn't screw up on older
c vendor's systems; put INET support on separate compilation flag
e
s 00108/00032/00697
d D 6.20 93/03/19 16:24:25 eric 146 145
c initial hooks for ISO networking
e
s 00000/00004/00729
d D 6.19 93/03/18 19:37:53 eric 145 144
c avoid extra unnecessary creation of queue files solely for an
c unneeded id
e
s 00001/00015/00732
d D 6.18 93/03/14 08:31:19 eric 144 143
c back out setproctitle changes; they trash argv before everything
c has been properly saved
e
s 00015/00001/00732
d D 6.17 93/03/13 22:51:52 eric 143 142
c setproctitle on getcanonname
e
s 00003/00003/00730
d D 6.16 93/03/09 09:15:54 eric 142 141
c log the correct IP address in relay= field even if the connection
c doesn't complete
e
s 00009/00028/00724
d D 6.15 93/03/07 16:16:05 eric 141 140
c use transienterror() all places where we do this sort of mapping
e
s 00002/00001/00750
d D 6.14 93/03/05 15:09:46 eric 140 139
c avoid loops on nameserver NO_DATA errors; getsockname can return
c zero length names on SunOS
e
s 00010/00000/00741
d D 6.13 93/03/03 15:18:16 eric 139 138
c don't write PidFile until we are actually about ready to accept
c connections
e
s 00009/00001/00732
d D 6.12 93/03/02 09:35:13 eric 138 137
c allow sending to [hostname] to bypass MX lookup
e
s 00057/00000/00676
d D 6.11 93/02/28 11:03:12 eric 137 136
c changes for better logging of mail submitters
e
s 00005/00000/00671
d D 6.10 93/02/28 09:24:01 eric 136 135
c log actual delivery host
e
s 00001/00002/00670
d D 6.9 93/02/23 08:59:57 eric 135 134
c more System V compatibility changes (ugh)
e
s 00004/00004/00668
d D 6.8 93/02/23 06:31:45 eric 134 133
c overhaul status of SMTP reply codes
e
s 00035/00004/00637
d D 6.7 93/02/21 09:54:58 eric 133 132
c do special check to for IP address matching our own
e
s 00000/00006/00641
d D 6.6 93/02/15 16:44:58 eric 132 131
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00002/00002/00645
d D 6.5 93/02/14 14:41:37 eric 131 130
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00040/00034/00607
d D 6.4 93/01/28 10:15:48 eric 130 129
c System 5 compatibility, misc fixes
e
s 00001/00001/00640
d D 6.3 93/01/22 17:20:21 eric 129 128
c fix -e compat flag; a few compilation warnings; improve error messages
e
s 00002/00002/00639
d D 6.2 93/01/01 13:08:49 eric 128 127
c don't convert CurrentLA to float just for printing
e
s 00000/00000/00641
d D 6.1 92/12/21 16:08:40 eric 127 126
c Release 6
e
s 00001/00002/00640
d D 5.54 92/12/15 12:34:49 eric 126 125
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00001/00015/00641
d D 5.53 92/11/15 19:24:43 eric 125 124
c allow specification of arbitrary string on successful db match
e
s 00015/00012/00641
d D 5.52 92/11/15 16:10:59 eric 124 123
c finish support for generalized maps
e
s 00006/00006/00647
d D 5.51 92/11/14 11:34:23 eric 123 122
c (partially) ANSI-fy it
e
s 00006/00001/00647
d D 5.50 92/11/04 12:14:53 eric 122 121
c fix a variety of small bugs noticed by bcx
e
s 00002/00002/00646
d D 5.49 92/09/22 16:40:25 eric 121 120
c a variety of bug minor bug fixes; add file locking when writing
c to a UNIX file; strip out dangerous envariables
e
s 00009/00000/00639
d D 5.48 92/07/13 16:27:43 eric 120 119
c miscellaneous changes to improve logging and messages
e
s 00005/00001/00634
d D 5.47 92/07/12 14:39:09 eric 119 118
c lint
e
s 00003/00002/00632
d D 5.46 92/07/11 18:51:43 eric 118 117
c open connection caching
e
s 00000/00000/00634
d D 5.45 92/05/31 13:51:19 eric 117 115
i 116 113
c checkpoint: putting in connection caching
e
s 00002/00002/00594
d D 5.42.1.2 92/05/29 10:56:42 eric 116 113
c more connection caching hacks
e
s 00048/00027/00588
d D 5.44 92/05/25 13:13:37 eric 115 114
c add generalized database mapping (using the K config line and
c $( ... $) syntaxes); $[ ... $] is now a special case
e
s 00026/00009/00589
d D 5.43 92/03/20 22:33:03 eric 114 112
c reject connections more quickly if load average goes up;
c try to time out on opens of .forward files on hung filesystems
e
s 00004/00006/00592
d D 5.42.1.1 92/02/26 14:05:01 eric 113 112
c partial hooks for caching all email connections; won't work
c because it could result in too many connections, and some could
c time out.
e
s 00034/00025/00564
d D 5.42 92/01/04 15:33:10 eric 112 111
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00003/00000/00586
d D 5.41 91/12/17 16:11:56 eric 111 110
c add ENOSR (no streams resources) to list of temporary failure conditions
e
s 00002/00005/00584
d D 5.40 91/12/14 12:36:55 eric 110 109
c fix race condition in queue file locking; generalize getla
e
s 00014/00011/00575
d D 5.39 91/10/05 10:07:08 eric 109 108
c return indication of whether nameserver found a match
e
s 00001/00001/00585
d D 5.38 91/09/03 18:38:12 leres 108 107
c Fix argument mistatch in call to inet_ntoa() (it causes problems on the
c sparc).
e
s 00007/00004/00579
d D 5.37 91/03/02 17:15:16 bostic 107 106
c ANSI
e
s 00001/00011/00582
d D 5.36 90/06/01 19:01:01 bostic 106 105
c new copyright notice
e
s 00004/00002/00589
d D 5.35 90/04/19 16:57:18 bostic 105 104
c NULL dereference; bug report 4.3BSD-tahoe/usr.sbin/11
e
s 00001/00001/00590
d D 5.34 90/04/19 16:44:44 bostic 104 103
c fdopens are wrong; bug report 4.3BSD/usr.lib/137
e
s 00001/00001/00590
d D 5.33 90/04/18 12:15:37 bostic 103 102
c don't break old makefiles; bug report 4.3BSD/usr.lib/114
e
s 00010/00004/00581
d D 5.32 90/04/16 08:10:41 rick 102 101
c check if e_xfp is null before flushing it
c move load average into a global so dont need to recalculate for every job
e
s 00001/00001/00584
d D 5.31 90/01/30 13:09:04 mckusick 101 100
c proper cast in printf (4.3BSD-tahoe/usr.lib/10)
e
s 00006/00001/00579
d D 5.30 89/01/19 15:56:23 bostic 100 99
c make ps more informative; from Rick Adams/David Comay
e
s 00000/00014/00580
d D 5.29 89/01/01 17:16:58 bostic 99 98
c remove DEBUG
e
s 00004/00013/00590
d D 5.28 88/11/17 10:32:01 karels 98 97
c expunge debugging/nonstandard/trojan horse commands from smtp,
c logging attempts to use them; log name/address of host from which mail received
c ("mail from" may not include it or may lie); don't allow debug to affect
c permissions locally; change some of the non-system syserrs to syslog at lower
c priority; still need to unifdef remaining debug code
e
s 00011/00002/00592
d D 5.27 88/09/20 22:15:33 eric 97 96
c add I option to insist on Internet domain server; add NAMED_BIND
c compile option to compile in named routines.
e
s 00011/00009/00583
d D 5.26 88/06/30 14:58:36 bostic 96 95
c install approved copyright notice
e
s 00036/00056/00556
d D 5.25 88/04/01 15:43:17 bostic 95 94
c redo maphostname
e
s 00023/00020/00589
d D 5.24 88/03/24 09:04:27 bostic 94 93
c add Berkeley specific header
e
s 00002/00000/00607
d D 5.23 87/12/21 12:22:14 bostic 93 92
c fix #ifdef DAEMON, there was an extra #else
e
s 00001/00000/00606
d D 5.22 87/07/27 17:09:11 bostic 92 91
c checked in for eric; new message
e
s 00006/00001/00600
d D 5.21 86/07/21 10:31:48 bloom 91 90
c fix possible buffer overflow problem, use specific routine for 
c canonicalizing host names not gethostbyname
e
s 00015/00004/00586
d D 5.20 86/06/30 16:20:43 bloom 90 89
c try multiple addresses in SMTP connect
e
s 00005/00001/00585
d D 5.19 86/05/06 18:04:41 bloom 89 88
c Fix problem with not closing sockets upon errors when opening connections
e
s 00000/00004/00586
d D 5.18 86/04/02 16:00:22 eric 88 87
c don't run around clearing EF_FATALERRS -- this often applies to another
c address.  Drop uid/gid check in sameaddr -- it causes more problems
c than it fixes.
e
s 00003/00023/00587
d D 5.17 86/01/05 19:56:47 eric 87 86
m 
c cleanup for various compilation flags and reasonable organization
e
s 00006/00004/00604
d D 5.16 85/12/26 14:46:11 eric 86 85
m 
c cleanup (comments only)
e
s 00010/00010/00598
d D 5.15 85/12/17 23:53:12 eric 85 84
m 
c lint
e
s 00027/00002/00581
d D 5.14 85/12/09 10:26:26 miriam 84 83
m 
c Modify maphostname to do a gethostbyaddr if first character in name 
c is a bracket.
e
s 00016/00005/00567
d D 5.13 85/11/13 11:11:50 miriam 83 82
m 
c Take into account the possible error return values from gethostbyname().
e
s 00004/00003/00568
d D 5.12 85/09/24 15:49:01 eric 82 81
m 
c clean up queue output somewhat (push null jobs to end); set
c SO_REUSEADDR and SO_KEEPALIVE on daemon sockets in the hopes of making
c dead connections disappear faster
e
s 00002/00002/00569
d D 5.11 85/09/19 13:35:46 eric 81 80
m 
c lint
e
s 00002/00000/00569
d D 5.10 85/09/19 10:34:43 eric 80 79
m 
c don't catch extraneous children
e
s 00000/00001/00569
d D 5.9 85/09/19 01:25:26 eric 79 77
i 78
m 
c incorporate SMI changes -- still experimental
e
s 00001/00004/00551
d D 5.4.1.1 85/09/19 00:55:37 eric 78 73
m 
c SMI changes (somewhat)
e
s 00024/00018/00548
d D 5.8 85/09/17 21:42:42 eric 77 76
m 
c use SIGCHLD to catch processes as suggested by Serge Granik
e
s 00001/00001/00565
d D 5.7 85/09/17 19:24:15 eric 76 75
m 
c facilities in syslog
e
s 00008/00002/00558
d D 5.6 85/08/07 16:43:57 miriam 75 74
m 
c Update format of setsockopt to use 4.3 syntax.
e
s 00005/00000/00555
d D 5.5 85/07/26 11:00:53 miriam 74 73
m 
c Check errno after gethostbyname to see if name server unable to return 
c a get a valid answer because authoritative name server is down.
e
s 00028/00014/00527
d D 5.4 85/06/08 10:29:45 eric 73 72
m 
c lint for 4.3 release
e
s 00005/00005/00536
d D 5.3 85/06/08 00:28:54 eric 72 71
m 
c lint
e
s 00002/00005/00539
d D 5.2 85/06/07 22:03:26 miriam 71 70
m 
c Resolve duplicate SccsId
e
s 00014/00000/00530
d D 5.1 85/06/07 14:39:11 dist 70 69
m 
c Add copyright
e
s 00001/00001/00529
d D 4.12 85/05/24 10:59:46 eric 69 68
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00061/00000/00469
d D 4.11 84/08/11 23:19:14 eric 68 67
m 
c Add $[ and $] as RHS operators to look up the contents and pass them
c to maphostname; maphostname currently looks them up in /etc/hosts and
c converts them to canonical form, but could be turned into a general
c name server.....   huzzah!!
e
s 00001/00001/00468
d D 4.10 84/08/11 17:18:49 eric 67 66
m 
c fix stupid syntax error
e
s 00010/00002/00459
d D 4.9 84/08/11 16:56:45 eric 66 65
m 
c don't add ".ARPA" (or whatever net name) to names that already have
c a dot in them; pull NetName out of initialized data space so that
c it can be changed in frozen configuration files
e
s 00012/00003/00449
d D 4.8 84/08/11 16:51:39 eric 65 64
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00003/00000/00449
d D 4.7 84/08/11 14:34:25 eric 64 63
m 
c handle hosts where gethostname does not return the canonical address
e
s 00001/00002/00448
d D 4.6 84/03/11 21:21:07 eric 63 62
m 
c fix argument to gethostname left over from some old interface....
e
s 00004/00002/00446
d D 4.5 84/03/11 16:13:46 eric 62 61
m 
c make network name configurable
e
s 00006/00002/00442
d D 4.4 83/08/28 14:44:55 eric 61 60
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00002/00001/00442
d D 4.3 83/08/06 10:37:46 eric 60 59
m 
c Clear errno before trying connect in an attempt to track down EPERM
c problems.
e
s 00000/00004/00443
d D 4.2 83/07/27 22:56:32 eric 59 58
m 
c Don't uppercase hostname in myhostname so that it can be used as a
c UUCP name.
e
s 00000/00000/00447
d D 4.1 83/07/25 19:45:15 eric 58 57
m 
c 4.2 release version
e
s 00003/00006/00444
d D 3.55 83/07/13 10:38:04 eric 57 56
m 
c Delete "load limiting" for SMTP connections (a bad ethernet board can
c hang up all incoming mail); use sfgets in collect (same reason); check
c for I/O error in collect (from Bill Nowicki); switch date format to
c RFC822 style.
e
s 00001/00001/00449
d D 3.54 83/07/01 23:01:21 wnj 56 55
m 
c wait.h -> sys/wait.h
e
s 00009/00004/00441
d D 3.53 83/05/07 11:28:25 eric 55 54
m 237
c Pass the size of the buffer to myhostname.
e
s 00001/00000/00444
d D 3.52 83/03/12 18:05:40 eric 54 53
m 196
c take ECONNRESET (Connection reset by peer) as a temporary error during
c connection initiation.
e
s 00006/00000/00438
d D 3.51 83/02/26 15:05:52 eric 53 52
m 162
c map host name for $w macro to upper case -- this is more conventional
e
s 00002/00001/00436
d D 3.50 83/02/24 18:54:21 eric 52 51
m 162
c Fix bug in $w and $=w setup
e
s 00036/00020/00401
d D 3.49 83/02/18 12:43:05 eric 51 50
m 183
m 187
c Add HELO hostname verification; put in hack to print lots of info if we
c get an EPERM (Not owner) on a connect.
e
s 00050/00000/00371
d D 3.48 83/02/08 10:51:20 eric 50 49
m 167
m 172
m 173
m 174
c clean up problems when QUEUE compile flag not defined; clean up hostname
c code to run on non-4.1c systems; fix use of -oeq (quiet on errors) flag.
e
s 00001/00001/00370
d D 3.47 83/01/17 12:31:57 eric 49 48
m 155
c fix bug that caused "\r\n" string in TCP mailer definition to turn
c into something else -- causing all TCP connections to hang.
e
s 00011/00000/00360
d D 3.46 83/01/16 22:08:35 eric 48 47
m 
c put in socket debugging on a debug flag to help Sam find the CMU-CS-A
c problem -- this probably won't work with early 4.1c systems.
e
s 00002/00003/00358
d D 3.45 83/01/16 17:26:43 eric 47 46
m 153
c make the maximum number of simultaneous SMTP connections an option
e
s 00035/00010/00326
d D 3.44 83/01/08 19:54:08 eric 46 45
m 
c release daemon resources when running the queue
e
s 00001/00001/00335
d D 3.43 83/01/06 10:40:58 eric 45 44
m 
c lint
e
s 00001/00000/00335
d D 3.42 83/01/04 13:09:27 eric 44 43
m 
c take EHOSTDOWN as a temporary failure
e
s 00002/00001/00333
d D 3.41 83/01/03 13:44:25 eric 43 42
m 
c take ENETUNREACH (Network unreachable) as a transient error -- this
c probably isn't usually right, but it seem safer in the long run....
e
s 00001/00000/00333
d D 3.40 83/01/02 15:33:48 eric 42 41
m 124
c Take errno 65, "Host is unreachable", to be a recoverable error
e
s 00004/00003/00329
d D 3.39 82/12/29 17:39:48 eric 41 40
m 112
c don't htons(sp->s_port) in makeconnection
e
s 00004/00002/00328
d D 3.38 82/12/24 08:15:05 eric 40 39
m 108
c Change parse to parseaddr for BB&N TCP/IP implementation; clean up
c comments in daemon.c to simplify the poor alternate protocol type.
e
s 00001/00001/00329
d D 3.37 82/12/16 10:14:25 sam 39 38
m 
c port numbers now returned byte swapped
e
s 00105/00109/00225
d D 3.36 82/12/13 17:28:58 eric 38 37
x 36
m 085
c NEW-IPC: convert to 4.1c
e
s 00001/00001/00358
d D 3.35 82/12/05 13:47:09 eric 37 36
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00026/00001/00333
d D 3.34 82/11/21 15:35:38 eric 36 35
m 085
c First part of 4.1c conversion
e
s 00024/00001/00310
d D 3.33 82/11/20 12:43:46 eric 35 34
m 083
c Accept user@[net.host.logical.imp] syntax
e
s 00010/00004/00301
d D 3.32 82/10/22 09:02:59 eric 34 33
x 30
m 023
c part of a heuristic hill climbing algorithm to minimize the number of
c IPC bugs that come crawling over me.
e
s 00004/00001/00300
d D 3.31 82/10/13 21:55:16 eric 33 32
m 023
c Don't interrupt the process doing accepts (have a separate process
c running the queue) to avoid a large pile of 4.1[abc] bugs.  When
c something more stable comes out, I will change this.
e
s 00010/00001/00291
d D 3.30 82/10/07 08:50:14 eric 32 31
c try again to work around the kernel problems in IPC connects when
c interrupted.
e
s 00001/00003/00291
d D 3.29 82/10/07 01:40:12 eric 31 30
c bother.... it takes time to close a socket
e
s 00010/00008/00284
d D 3.28 82/09/30 22:29:55 eric 30 29
c workaround in daemon accept code for 4.1a kernel bug: if an accept
c gets an EINTR and then a valid accept before the interrupt returns,
c the connection will be lost forever (at least, as I understand it).
e
s 00008/00007/00284
d D 3.27 82/08/25 21:22:18 eric 29 28
c sigh....  more fun and games in the daemon code to try to guess right.
e
s 00002/00026/00289
d D 3.26 82/08/25 19:44:41 eric 28 27
c recreate a socket after every failed accept()
e
s 00005/00007/00310
d D 3.25 82/08/25 11:21:54 eric 27 26
c clean up time manipulation to always be current; assign job
c id's earlier to make sure there is always one with a message.
e
s 00025/00000/00292
d D 3.24 82/08/24 19:41:39 eric 26 25
c log more info (on log level 11); try to detect wild accept loops;
c some minor cleanup and debugging checks; fix NoConnect option to;
c only apply to expensive mailers (regardless of sendqueue order)
e
s 00006/00005/00286
d D 3.23 82/08/15 11:53:12 eric 25 24
c allow ETIMEDOUT or EINTR as in accept call
e
s 00009/00009/00282
d D 3.22 82/08/08 01:03:29 eric 24 23
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00002/00000/00289
d D 3.21 82/07/31 16:57:29 eric 23 22
c don't give error on ETIMEDOUT on accept() call.
e
s 00040/00016/00249
d D 3.20 82/07/27 23:01:30 eric 22 21
c clean up semantics of daemon mode to facilitate use of other IPC;
c if you can't create a socket assume there is another sendmail running
c and exit; move some code to main.c because it is not part of creating
c a connection.
e
s 00001/00000/00264
d D 3.19 82/07/05 20:55:10 eric 21 20
c improve debugging: flush transcript before doing things that might
c take a long time; add some info to debugging output
e
s 00002/00000/00262
d D 3.18 82/07/02 10:00:24 eric 20 19
c be paranoid about resetting the "FatalErrors" flag -- always reset
c after forking for daemon or queue mode.  This will prevent false error
c return delivery.
e
s 00001/00000/00261
d D 3.17 82/06/30 22:39:06 eric 19 18
c open a separate transcript in the child of a daemon.
e
s 00002/00003/00259
d D 3.16 82/06/26 13:10:55 eric 18 17
c lint
e
s 00001/00000/00261
d D 3.15 82/06/16 14:50:47 eric 17 16
c allow ECONNREFUSED (connection refused) as a temp error
e
s 00031/00003/00230
d D 3.14 82/06/07 23:52:01 eric 16 15
c allow multiple connections
e
s 00003/00003/00230
d D 3.13 82/05/31 18:50:56 eric 15 14
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00006/00000/00227
d D 3.12 82/05/22 01:26:44 eric 14 12
c add some other temporary failure conditions to ipc connection
e
s 00007/00000/00227
d R 3.12 82/05/22 00:06:28 eric 13 12
c extend the list of "temporary failure" returns from the list of
c IPC temporary failures.
e
s 00007/00001/00220
d D 3.11 82/05/06 20:21:23 eric 12 11
c allow socket number on [IPC] connections -- eventually this
c could be used to handle other low-level protocols.
e
s 00000/00001/00221
d D 3.10 82/03/22 22:38:01 eric 11 10
c continue the impossible task of tracking Bill Joy
e
s 00002/00003/00220
d D 3.9 82/03/06 14:52:15 eric 10 9
c arrange to be able to accept a connection from any host.
e
s 00074/00000/00149
d D 3.8 82/03/05 10:12:59 eric 9 8
c include direct connect on outgoing mail if the pathname is "[IPC]" --
c this gives minimal number of processes for ethernet mail.
e
s 00001/00001/00148
d D 3.7 82/02/26 22:03:20 eric 8 7
c switch to the correct port (IPPORT_SMTP).
e
s 00088/00005/00061
d D 3.6 82/02/26 21:56:32 eric 7 6
c implement daemon mode
e
s 00001/00001/00065
d D 3.5 81/12/06 12:40:50 eric 6 5
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00001/00001/00065
d D 3.4 81/11/08 17:27:09 eric 5 4
c LINT
e
s 00037/00019/00029
d D 3.3 81/10/27 11:49:13 eric 4 2
c sketch out eventual implementation of daemon.
e
s 00191/00008/00040
d D 3.2.1.1 81/10/27 08:37:20 eric 3 2
c try to cram in the MPX stuff -- is this really worth it?  NO!
e
s 00002/00002/00046
d D 3.2 81/10/26 14:23:34 eric 2 1
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00048/00000/00000
d D 3.1 81/10/17 16:56:40 eric 1 0
c date and time created 81/10/17 16:56:40 by eric
e
u
U
f b 
f i 
t
T
I 70
/*
I 96
D 265
 * Copyright (c) 1983 Eric P. Allman
E 265
I 265
 * Copyright (c) 1983, 1995 Eric P. Allman
E 265
E 96
D 94
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 94
I 94
D 179
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 179
I 179
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 179
 *
D 106
 * Redistribution and use in source and binary forms are permitted
D 96
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 96
I 96
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
E 106
I 106
 * %sccs.include.redist.c%
E 106
E 96
 */
E 94

D 71
#ifndef lint
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 71
D 94

E 94
E 70
I 9
D 95
# include <errno.h>
E 9
I 1
# include "sendmail.h"
E 95
I 95
#include <errno.h>
I 135
D 183
#include <signal.h>
E 183
E 135
D 103
#include <sendmail.h>
E 103
I 103
#include "sendmail.h"
E 103
E 95
I 3
# include <sys/mx.h>
E 3

D 6
static char	SccsId[] =	"%W%	%G%";
E 6
I 6
D 7
SCCSID(%W%	%Y%	%G%);
E 7
I 7
D 73
#ifndef DAEMON
E 73
I 73
D 94
# ifndef DAEMON
# ifndef lint
E 73
D 71
SCCSID(%W%	%Y%	%G%	(w/o daemon mode));
E 71
I 71
static char	SccsId[] = "%W% (Berkeley) %G%	(w/o daemon mode)";
E 71
D 73
#else
E 73
I 73
# endif not lint
# else
E 94
I 94
#ifndef lint
#ifdef DAEMON
static char sccsid[] = "%W% (Berkeley) %G% (with daemon mode)";
#else
static char sccsid[] = "%W% (Berkeley) %G% (without daemon mode)";
#endif
#endif /* not lint */
E 94
E 73
E 7
E 6

I 102
D 110
int la;	/* load average */

E 110
E 102
I 94
#ifdef DAEMON

E 94
I 7
D 38
# include <sys/socket.h>
D 11
# include <wellknown.h>
E 11
# include <net/in.h>
I 16
# include <wait.h>
E 38
I 38
D 73
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
D 56
#include <wait.h>
E 56
I 56
#include <sys/wait.h>
E 73
I 73
D 78
# include <sys/socket.h>
# include <netinet/in.h>
E 78
D 260
# include <netdb.h>
E 260
I 77
D 135
# include <sys/signal.h>
E 135
E 77
D 192
# include <sys/wait.h>
E 192
D 210
# include <sys/time.h>
E 210
I 187
# include <arpa/inet.h>
E 187
D 135
# include <sys/resource.h>
E 135
E 73
E 56
E 38
E 16

I 161
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
D 233
# include <arpa/nameser.h>
E 233
# include <resolv.h>
#endif

I 275
#if IP_SRCROUTE
# include <netinet/in_systm.h>
# include <netinet/ip.h>
# include <netinet/ip_var.h>
#endif

E 275
E 161
I 146
D 155
#ifdef NETISO
# include <netiso/iso.h>
#endif

E 155
E 146
I 73
D 94
# ifndef lint
E 73
D 71
SCCSID(%W%	%Y%	%G%	(with daemon mode));
E 71
I 71
static char	SccsId[] = "%W% (Berkeley) %G% (with daemon mode)";
I 73
# endif not lint
I 93
# endif
E 93
E 73
E 71

I 93
# ifdef DAEMON
E 94
E 93
E 7
/*
**  DAEMON.C -- routines to use when running as a daemon.
I 22
**
**	This entire file is highly dependent on the 4.2 BSD
**	interprocess communication primitives.  No attempt has
**	been made to make this file portable to Version 7,
**	Version 6, MPX files, etc.  If you should try such a
**	thing yourself, I recommend chucking the entire file
**	and starting from scratch.  Basic semantics are:
**
**	getrequests()
**		Opens a port and initiates a connection.
**		Returns in a child.  Must set InChannel and
**		OutChannel appropriately.
I 46
**	clrdaemon()
**		Close any open files associated with getting
**		the connection; this is used when running the queue,
**		etc., to avoid having extra file descriptors during
**		the queue run and to avoid confusing the network
**		code (if it cares).
E 46
D 112
**	makeconnection(host, port, outfile, infile)
E 112
I 112
**	makeconnection(host, port, outfile, infile, usesecureport)
E 112
**		Make a connection to the named host on the given
**		port.  Set *outfile and *infile to the files
**		appropriate for communication.  Returns zero on
**		success, else an exit status describing the
**		error.
D 87
**
**	The semantics of both of these should be clean.
E 87
I 87
D 119
**	maphostname(hbuf, hbufsize)
E 119
I 119
D 124
**	maphostname(hbuf, hbufsize, avp)
E 119
**		Convert the entry in hbuf into a canonical form.  It
**		may not be larger than hbufsize.
E 124
I 124
D 175
**	maphostname(map, hbuf, hbufsiz, avp)
E 175
I 175
**	host_map_lookup(map, hbuf, avp, pstat)
E 175
**		Convert the entry in hbuf into a canonical form.
E 124
E 87
E 22
*/
I 146
D 178

extern char	*anynet_ntoa();
E 178
E 146
I 3

static FILE	*MailPort;	/* port that mail comes in on */
E 3
D 2

static int	DaemonPipe;
E 2
/*
**  GETREQUESTS -- open mail IPC port and get requests.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Waits until some interesting activity occurs.  When
**		it does, a child is created to process it, and the
**		parent waits for completion.  Return from this
D 40
**		routine is always in the child.
E 40
I 40
**		routine is always in the child.  The file pointers
**		"InChannel" and "OutChannel" should be set to point
**		to the communication channel.
E 40
*/

I 16
D 47
# define MAXCONNS	4	/* maximum simultaneous sendmails */

E 47
I 38
D 46
struct sockaddr_in SendmailAddress;
E 46
I 46
D 112
struct sockaddr_in	SendmailAddress;/* internet address of sendmail */
D 62
int	DaemonSocket = -1;		/* fd describing socket */
E 62
I 47
D 57
int	MaxConnections = 4;		/* maximum simultaneous sendmails */
E 57
E 47
E 46

E 112
I 62
D 152
int	DaemonSocket	= -1;		/* fd describing socket */
E 152
I 152
int		DaemonSocket	= -1;		/* fd describing socket */
SOCKADDR	DaemonAddr;			/* socket for incoming */
I 171
int		ListenQueueSize = 10;		/* size of listen queue */
I 190
int		TcpRcvBufferSize = 0;		/* size of TCP receive buffer */
int		TcpSndBufferSize = 0;		/* size of TCP send buffer */
E 190
E 171
E 152
D 66
char	*NetName	= "ARPA";	/* name of home (local?) network */
E 66
I 66
D 112
char	*NetName;			/* name of home (local?) network */
E 112
E 66

I 250
void
E 250
E 62
E 38
E 16
getrequests()
{
I 38
D 46
	int s;
E 46
	int t;
E 38
I 16
D 77
	union wait status;
E 77
D 57
	int numconnections = 0;
E 57
I 38
D 40
	struct sockaddr otherend;
E 40
D 205
	register struct servent *sp;
E 205
I 82
D 223
	int on = 1;
E 223
I 114
	bool refusingconnections = TRUE;
I 139
	FILE *pidf;
I 201
	int socksize;
I 221
D 286
#ifdef XDEBUG
E 286
I 286
#if XDEBUG
E 286
	bool j_has_dot;
#endif
E 221
E 201
E 139
E 114
I 112
D 147
	struct sockaddr_in srvraddr;
E 147
I 147
D 152
	SOCKADDR srvraddr;
E 152
E 147
E 112
E 82
I 77
D 107
	extern reapchild();
E 107
I 107
	extern void reapchild();
E 107
E 77
E 38

I 38
	/*
	**  Set up the address for the mailer.
	*/

D 152
	sp = getservbyname("smtp", "tcp");
	if (sp == NULL)
E 152
I 152
	if (DaemonAddr.sin.sin_family == 0)
		DaemonAddr.sin.sin_family = AF_INET;
	if (DaemonAddr.sin.sin_addr.s_addr == 0)
		DaemonAddr.sin.sin_addr.s_addr = INADDR_ANY;
	if (DaemonAddr.sin.sin_port == 0)
E 152
	{
I 205
		register struct servent *sp;

E 205
D 134
		syserr("server \"smtp\" unknown");
E 134
I 134
D 152
		syserr("554 server \"smtp\" unknown");
E 134
D 45
		return (-1);
E 45
I 45
		goto severe;
E 152
I 152
		sp = getservbyname("smtp", "tcp");
		if (sp == NULL)
		{
D 157
			syserr("554 server \"smtp\" unknown");
E 157
I 157
			syserr("554 service \"smtp\" unknown");
E 157
D 205
			goto severe;
E 205
I 205
			DaemonAddr.sin.sin_port = htons(25);
E 205
		}
I 180
D 181
#ifdef _SCO_unix_
		DaemonAddr.sin.sin_port = htons(sp->s_port);
#else
E 181
E 180
D 205
		DaemonAddr.sin.sin_port = sp->s_port;
E 205
I 205
		else
			DaemonAddr.sin.sin_port = sp->s_port;
E 205
I 180
D 181
#endif
E 181
E 180
E 152
E 45
	}
D 112
	SendmailAddress.sin_family = AF_INET;
	SendmailAddress.sin_addr.s_addr = INADDR_ANY;
D 39
	SendmailAddress.sin_port = htons(sp->s_port);
E 39
I 39
	SendmailAddress.sin_port = sp->s_port;
E 112
I 112
D 147
	srvraddr.sin_family = AF_INET;
	srvraddr.sin_addr.s_addr = INADDR_ANY;
	srvraddr.sin_port = sp->s_port;
E 147
I 147
D 152
	srvraddr.sin.sin_family = AF_INET;
	srvraddr.sin.sin_addr.s_addr = INADDR_ANY;
	srvraddr.sin.sin_port = sp->s_port;
E 152
E 147
E 112
E 39

	/*
	**  Try to actually open the connection.
	*/

D 99
# ifdef DEBUG
E 99
	if (tTd(15, 1))
D 112
		printf("getrequests: port 0x%x\n", SendmailAddress.sin_port);
E 112
I 112
D 147
		printf("getrequests: port 0x%x\n", srvraddr.sin_port);
E 147
I 147
D 152
		printf("getrequests: port 0x%x\n", srvraddr.sin.sin_port);
E 152
I 152
		printf("getrequests: port 0x%x\n", DaemonAddr.sin.sin_port);
E 152
E 147
E 112
D 99
# endif DEBUG
E 99

	/* get a socket for the SMTP connection */
D 46
	s = socket(AF_INET, SOCK_STREAM, 0, 0);
	if (s < 0)
E 46
I 46
D 73
	DaemonSocket = socket(AF_INET, SOCK_STREAM, 0, 0);
E 73
I 73
D 160
	DaemonSocket = socket(AF_INET, SOCK_STREAM, 0);
E 160
I 160
D 223
	DaemonSocket = socket(DaemonAddr.sa.sa_family, SOCK_STREAM, 0);
E 160
E 73
	if (DaemonSocket < 0)
E 46
	{
		/* probably another daemon already */
		syserr("getrequests: can't create socket");
	  severe:
# ifdef LOG
		if (LogLevel > 0)
D 76
D 78
			syslog(LOG_SALERT, "cannot get connection");
E 78
I 78
D 129
			syslog(LOG_ALERT, "cannot get connection");
E 129
I 129
			syslog(LOG_ALERT, "problem creating SMTP socket");
E 129
E 78
E 76
I 76
D 79
			syslog(LOG_ALERT, "cannot get connection");
E 79
E 76
D 123
# endif LOG
E 123
I 123
# endif /* LOG */
E 123
		finis();
	}
E 223
I 223
D 225
	socksize = opendaemonsocket();
E 225
I 225
	socksize = opendaemonsocket(TRUE);
E 225
E 223
I 48

D 99
#ifdef DEBUG
E 99
D 223
	/* turn on network debugging? */
D 121
	if (tTd(15, 15))
E 121
I 121
	if (tTd(15, 101))
E 121
D 75
		(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_DEBUG, 0, 0);
E 75
I 75
D 82
	{
		int on = 1;
E 82
		(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_DEBUG, (char *)&on, sizeof on);
D 82
	}
E 82
E 75
D 99
#endif DEBUG
E 99
I 82

	(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
	(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);
E 82

I 191
#ifdef SO_RCVBUF
	if (TcpRcvBufferSize > 0)
	{
		if (setsockopt(DaemonSocket, SOL_SOCKET, SO_RCVBUF,
D 193
			       &TcpRcvBufferSize,
E 193
I 193
			       (char *) &TcpRcvBufferSize,
E 193
			       sizeof(TcpRcvBufferSize)) < 0)
			syserr("getrequests: setsockopt(SO_RCVBUF)");
	}
#endif

E 191
E 48
D 46
	if (bind(s, &SendmailAddress, sizeof SendmailAddress, 0) < 0)
E 46
I 46
D 73
	if (bind(DaemonSocket, &SendmailAddress, sizeof SendmailAddress, 0) < 0)
E 73
I 73
D 107
	if (bind(DaemonSocket, &SendmailAddress, sizeof SendmailAddress) < 0)
E 107
I 107
D 112
	if (bind(DaemonSocket,
	    (struct sockaddr *)&SendmailAddress, sizeof SendmailAddress) < 0)
E 112
I 112
D 147
	if (bind(DaemonSocket, (struct sockaddr *)&srvraddr, sizeof srvraddr) < 0)
E 147
I 147
D 152
	if (bind(DaemonSocket, &srvraddr.sa, sizeof srvraddr) < 0)
E 152
I 152
D 160
	if (bind(DaemonSocket, &DaemonAddr.sa, sizeof DaemonAddr) < 0)
E 160
I 160
	switch (DaemonAddr.sa.sa_family)
	{
# ifdef NETINET
	  case AF_INET:
D 201
		t = sizeof DaemonAddr.sin;
E 201
I 201
		socksize = sizeof DaemonAddr.sin;
E 201
		break;
# endif

# ifdef NETISO
	  case AF_ISO:
D 201
		t = sizeof DaemonAddr.siso;
E 201
I 201
		socksize = sizeof DaemonAddr.siso;
E 201
		break;
# endif

	  default:
D 201
		t = sizeof DaemonAddr;
E 201
I 201
		socksize = sizeof DaemonAddr;
E 201
		break;
	}

D 201
	if (bind(DaemonSocket, &DaemonAddr.sa, t) < 0)
E 201
I 201
	if (bind(DaemonSocket, &DaemonAddr.sa, socksize) < 0)
E 201
E 160
E 152
E 147
E 112
E 107
E 73
E 46
	{
		syserr("getrequests: cannot bind");
D 46
		close(s);
E 46
I 46
		(void) close(DaemonSocket);
E 46
		goto severe;
	}
D 46
	listen(s, 10);
E 46
I 46
D 73
	listen(DaemonSocket, 10);
E 73
I 73
D 114
	if (listen(DaemonSocket, 10) < 0)
	{
		syserr("getrequests: cannot listen");
		(void) close(DaemonSocket);
		goto severe;
	}
E 114
E 73
E 46

E 223
I 77
D 81
	signal(SIGCHLD, reapchild);
E 81
I 81
D 183
	(void) signal(SIGCHLD, reapchild);
E 183
I 183
	(void) setsignal(SIGCHLD, reapchild);
E 183
I 139

	/* write the pid to the log file for posterity */
	pidf = fopen(PidFile, "w");
	if (pidf != NULL)
	{
I 182
		extern char *CommandLineArgs;

		/* write the process id on line 1 */
E 182
		fprintf(pidf, "%d\n", getpid());
I 182

		/* line 2 contains all command line flags */
		fprintf(pidf, "%s\n", CommandLineArgs);

		/* flush and close */
E 182
		fclose(pidf);
	}

I 221
D 286
#ifdef XDEBUG
E 286
I 286
#if XDEBUG
E 286
	{
D 222
		char *j = macvalue('j', CurEnv);
E 222
I 222
		char jbuf[MAXHOSTNAMELEN];
E 222
E 221
E 139
E 81

I 221
D 222
		j_has_dot = j != NULL && strchr(j, '.') != NULL;
E 222
I 222
D 257
		expand("\201j", jbuf, &jbuf[sizeof jbuf - 1], CurEnv);
E 257
I 257
		expand("\201j", jbuf, sizeof jbuf, CurEnv);
E 257
		j_has_dot = strchr(jbuf, '.') != NULL;
E 222
	}
#endif

E 221
E 77
D 99
# ifdef DEBUG
E 99
	if (tTd(15, 1))
D 46
		printf("getrequests: %d\n", s);
E 46
I 46
		printf("getrequests: %d\n", DaemonSocket);
E 46
D 99
# endif DEBUG
E 99

E 38
E 16
D 3
D 7
	syserr("Daemon mode not yet implemented");
I 2
D 4
	getrecipients();
E 4
E 2
	exit(EX_USAGE);
E 3
I 3
	char *portname = "/dev/mailbox";

E 3
I 2
D 4
	/* initsys(); */
I 3

	/*
	**  Create "/dev/mailbox"
	*/

	if (Debug)
		portname = "mailbox";
	unlink(portname);
	MailPort = mpx(portname, 0222);
	if (MailPort < 0)
	{
		syserr("cannot create %s", portname);
		exit(EX_OSFILE);
	}
	chmod(portname, 0222);

	/*
	**  Wait for connection.
	*/

	for (;;)
	{
		i = read(MailPort, line, sizeof line);
		if (i < 0)
		{
			if (errno == EINTR)
				continue;
			syserr("mpx read");
			errct++;
			if (errct > 1000)
			{
				syserr("mpx read: too many errors");
				finis();
			}
			sleep(5);
			continue;
		}
		mpxcrack(line, i);
	}
E 3
E 2
}
/*
D 3
**  GETRECIPIENTS -- do a sendto to all recipients.
E 3
I 3
**  MPXCRACK -- parse & handle an input line.
E 3
**
**	Parameters:
I 3
**		rec -- the input record.
**		bc -- the byte count for rec.
**
**	Returns:
**		nothing
**
**	Side Effects:
**		rec is processed.
*/

# define skip(rec, n)	((struct rh *) (((char *) rec) + n))

mpxcrack(rec, bc)
	register struct rh *rec;
	int bc;
{
	struct rh *endrec;

	endrec = skip(rec, bc);

	while (rec < endrec)
	{
		if (rec->count == 0)
		{
			/* control record from mpx file */
			mpxcontrol(rec);
		}
		else
		{
			/* data record -- process message */
			syserr("data record!!");
		}
		rec->count += rec->ccount;
		if (rec->count & 01)
			rec->count++;
		rec = skip(rec, rec->count + sizeof *rec);
	}
}
/*
**  MPXCONTROL -- handle mpx control messages.
**
**	Parameters:
**		rec -- control message.
**
**	Returns:
E 3
**		none.
**
I 3
**	Side Effects:
**		as necessary for that control message.
*/

short NoIoctl[] = { M_IOANS };

mpxcontrol(rec)
	register struct rh *rec;
{
	register int cmd;
	register short val;
	register short *ap;
# ifdef MPXDEBUG
	char dbbuf[100];
# endif MPXDEBUG

# ifdef DEBUG
	if (Debug > 7)
		printf("%d byte control message\n", rec->ccount);
# endif DEBUG

	ap = (short *) (((char *) rec) + sizeof *rec);
	cmd = *ap++ & 0377;
	val = *ap++;
# ifdef MPXDEBUG
	logmsg(LOG_DEBUG, "mpxctl ch=%x cmd=%d val=%d", rec->index, cmd, val);
# endif MPXDEBUG

	switch (cmd)
	{
	  case M_WATCH:		/* attempted connect; value is uid */
# ifdef DEBUG
		if (Debug > 7)
			printf("WATCH, uid=%d\n", val);
# endif DEBUG
		attach(rec->index, MailPort);
		InChannel = extract(rec->index, MailPort);
		RealUid = val;
		detach(rec->index, MailPort);
		i = fork();
		if (i < 0)
		{
			syserr("daemon: cannot fork");
		}
		else if (i > 0)
		{
			/* parent -- wait for child */
			auto int st;

			(void) wait(&st);
		}
		else
		{
			/* child */
			smtp();
			syserr("smtp returns");
			exit(EX_SOFTWARE);
		}
		break;

	  case M_CLOSE:		/* close channel; value is unused */
# ifdef DEBUG
		if (Debug > 7)
			printf("CLOSE, val=%d\n", val);
# endif DEBUG
		detach(rec->index, MailPort);
		break;

	  case M_IOCTL:
# ifdef DEBUG
		if (Debug > 7)
			printf("IOCTL, val=%d\n", val);
# endif DEBUG
		wmpxctl(rec->index, NoIoctl, sizeof NoIoctl);
		break;

	  default:
		syserr("unknown mpx cmd %d, val=%d\n", cmd, val);
		break;
	}
}
/*
**  WMPXCTL -- write mpx control message
**
**	Parameters:
**		index -- index to write to.
**		buf -- place to write.
**		len -- length to write.
**
E 3
**	Returns:
**		none.
**
**	Side Effects:
D 3
**		The set of recipients for this request are
**		collected and designated as recipients.
E 3
I 3
**		writes to MailPort.
E 3
*/
E 4

E 7
D 3
D 4
getrecipients()
E 3
I 3
wmpxctl(index, buf, cnt)
	int index;
	char *buf;
	int cnt;
E 3
{
D 3
	return;
E 4
I 4
	for (;;)
	{
I 61
		register int pid;
E 61
I 51
		auto int lotherend;
I 114
		extern bool refuseconnections();
I 250
		extern int getla();
E 250
E 114
D 98
		struct sockaddr_in otherend;
E 98
I 61
D 110
		extern int RefuseLA;
E 110
I 100
D 102
		register int la;
E 102
E 100
E 61

E 51
I 38
D 61
		/* wait for a connection */
E 38
		register int pid;
E 61
I 61
		/* see if we are rejecting connections */
D 100
		while (getla() > RefuseLA)
E 100
I 100
D 110
		while ((la = getla()) > RefuseLA)
E 110
I 110
D 114
		while ((CurrentLA = getla()) > RefuseLA)
E 114
I 114
		CurrentLA = getla();
		if (refuseconnections())
E 114
E 110
		{
D 101
			setproctitle("rejecting connections: load average: %.2f", la);
E 101
I 101
D 110
			setproctitle("rejecting connections: load average: %.2f", (double)la);
E 110
I 110
D 114
			setproctitle("rejecting connections: load average: %.2f", (double)CurrentLA);
E 114
I 114
D 223
			if (!refusingconnections)
E 223
I 223
			if (DaemonSocket >= 0)
E 223
			{
D 223
				/* don't queue so peer will fail quickly */
				(void) listen(DaemonSocket, 0);
				refusingconnections = TRUE;
E 223
I 223
				/* close socket so peer will fail quickly */
				(void) close(DaemonSocket);
				DaemonSocket = -1;
E 223
			}
I 223
			refusingconnections = TRUE;
E 223
D 128
			setproctitle("rejecting connections: load average: %.2f",
				(double)CurrentLA);
E 128
I 128
D 282
			setproctitle("rejecting connections: load average: %d",
				CurrentLA);
E 282
E 128
E 114
E 110
E 101
E 100
D 223
			sleep(5);
E 223
I 223
			sleep(15);
E 223
I 114
			continue;
E 114
I 100
		}
E 100
E 61
D 18
		auto int st;
E 18
I 7
D 38
		register int port;
E 38
E 7

I 237
		/* arrange to (re)open the socket if necessary */
D 238
		if (DaemonSocket < 0)
			(void) opendaemonsocket(FALSE);
E 238
E 237
I 114
		if (refusingconnections)
		{
I 238
			(void) opendaemonsocket(FALSE);
E 238
D 237
			/* start listening again */
D 171
			if (listen(DaemonSocket, 10) < 0)
E 171
I 171
D 223
			if (listen(DaemonSocket, ListenQueueSize) < 0)
E 171
			{
				syserr("getrequests: cannot listen");
				(void) close(DaemonSocket);
				goto severe;
			}
E 223
I 223
D 225
			if (DaemonSocket < 0)
				(void) opendaemonsocket();
E 225
I 225
			(void) opendaemonsocket(FALSE);
E 237
E 225
E 223
D 278
			setproctitle("accepting connections");
E 278
			refusingconnections = FALSE;
		}
I 221

D 286
#ifdef XDEBUG
E 286
I 286
#if XDEBUG
E 286
		/* check for disaster */
		{
D 246
			register STAB *s;
E 246
D 222
			char *j = macvalue('j', CurEnv);
E 222
I 222
			char jbuf[MAXHOSTNAMELEN];
E 222

D 222
			if (j == NULL ||
			    (s = stab(j, ST_CLASS, ST_FIND)) == NULL ||
E 222
I 222
D 257
			expand("\201j", jbuf, &jbuf[sizeof jbuf - 1], CurEnv);
E 257
I 257
			expand("\201j", jbuf, sizeof jbuf, CurEnv);
E 257
D 246
			if ((s = stab(jbuf, ST_CLASS, ST_FIND)) == NULL ||
E 222
			    !bitnset('w', s->s_class))
E 246
I 246
			if (!wordinclass(jbuf, 'w'))
E 246
			{
				dumpstate("daemon lost $j");
				syslog(LOG_ALERT, "daemon process doesn't have $j in $=w; see syslog");
				abort();
			}
D 222
			else if (j_has_dot && strchr(j, '.') == NULL)
E 222
I 222
			else if (j_has_dot && strchr(jbuf, '.') == NULL)
E 222
			{
				dumpstate("daemon $j lost dot");
				syslog(LOG_ALERT, "daemon process $j lost dot; see syslog");
				abort();
			}
		}
#endif
E 221

E 114
I 61
		/* wait for a connection */
I 278
		setproctitle("accepting connections");
E 278
I 100
D 114
		setproctitle("accepting connections");
E 114
E 100
E 61
D 38
		/*
		**  Wait for a connection.
		*/
E 38
I 38
		do
		{
D 51
			auto int lotherend;
			struct sockaddr otherend;
E 38

E 51
D 7
		/* MailPort = getconnection(); */
E 7
I 7
D 38
		while ((port = getconnection()) < 0)
E 38
I 38
			errno = 0;
D 98
			lotherend = sizeof otherend;
D 46
			t = accept(s, &otherend, &lotherend, 0);
E 46
I 46
D 73
			t = accept(DaemonSocket, &otherend, &lotherend, 0);
E 73
I 73
			t = accept(DaemonSocket, &otherend, &lotherend);
E 98
I 98
D 201
			lotherend = sizeof RealHostAddr;
E 201
I 201
			lotherend = socksize;
E 201
D 107
			t = accept(DaemonSocket, &RealHostAddr, &lotherend);
E 107
I 107
			t = accept(DaemonSocket,
			    (struct sockaddr *)&RealHostAddr, &lotherend);
E 107
E 98
E 73
E 46
		} while (t < 0 && errno == EINTR);
		if (t < 0)
E 38
		{
D 33
			syserr("getrequests: getconnection failed");
E 33
I 33
D 38
# ifdef LOG
			if (LogLevel > 0)
				syslog(LOG_SALERT, "cannot get connection");
# endif LOG
E 33
D 22
			sleep(30);
E 22
I 22
			finis();
E 38
I 38
			syserr("getrequests: accept");
I 237

			/* arrange to re-open the socket next time around */
			(void) close(DaemonSocket);
			DaemonSocket = -1;
E 237
			sleep(5);
			continue;
E 38
E 22
		}
E 7

I 7
		/*
		**  Create a subprocess to process the mail.
		*/

D 99
# ifdef DEBUG
E 99
D 24
		if (Debug > 1)
E 24
I 24
		if (tTd(15, 2))
E 24
D 38
			printf("getrequests: forking (port = %d)\n", port);
E 38
I 38
			printf("getrequests: forking (fd = %d)\n", t);
E 38
D 99
# endif DEBUG
E 99

E 7
		pid = fork();
		if (pid < 0)
		{
			syserr("daemon: cannot fork");
			sleep(10);
I 7
D 15
			close(port);
E 15
I 15
D 38
			(void) close(port);
E 38
I 38
			(void) close(t);
E 38
E 15
E 7
			continue;
		}

		if (pid == 0)
		{
I 184
			char *p;
E 184
I 51
D 158
			extern struct hostent *gethostbyaddr();
			register struct hostent *hp;
D 78
			extern char *RealHostName;	/* srvrsmtp.c */
E 78
			char buf[MAXNAME];
E 158
I 158
			extern char *hostnamebyanyaddr();
I 244
			extern void intsig();
E 244
E 158
I 126
D 146
			extern char *inet_ntoa();
E 146
E 126

E 51
			/*
			**  CHILD -- return to caller.
I 51
			**	Collect verified idea of sending host.
E 51
			**	Verify calling user id if possible here.
I 20
D 22
			**	Make sure we reset state from parent.
E 22
E 20
			*/

I 80
D 81
			signal(SIGCHLD, SIG_DFL);
E 81
I 81
D 183
			(void) signal(SIGCHLD, SIG_DFL);
E 183
I 183
			(void) setsignal(SIGCHLD, SIG_DFL);
I 244
			(void) setsignal(SIGHUP, intsig);
E 244
I 230
			(void) close(DaemonSocket);
E 230
I 214
			DisConnected = FALSE;
E 214
E 183
I 166
D 209
			OpMode = MD_SMTP;
E 209
E 166
E 81

I 216
			setproctitle("startup with %s",
				anynet_ntoa(&RealHostAddr));

E 216
E 80
I 51
			/* determine host name */
D 85
			hp = gethostbyaddr(&otherend.sin_addr, sizeof otherend.sin_addr, AF_INET);
E 85
I 85
D 98
			hp = gethostbyaddr((char *) &otherend.sin_addr, sizeof otherend.sin_addr, AF_INET);
E 98
I 98
D 146
			hp = gethostbyaddr((char *) &RealHostAddr.sin_addr, sizeof RealHostAddr.sin_addr, AF_INET);
E 146
I 146
D 147
			hp = gethostbyaddr(RealHostAddr.sa_u.sa_data,
					   sizeof RealHostAddr.sa_u.sa_data,
					   RealHostAddr.sa_family);
E 147
I 147
D 158
			switch (RealHostAddr.sa.sa_family)
			{
#ifdef NETINET
			  case AF_INET:
				hp = gethostbyaddr((char *) &RealHostAddr.sin.sin_addr,
					sizeof RealHostAddr.sin.sin_addr,
					AF_INET);
				break;
#endif
E 158
I 158
D 184
			RealHostName = newstr(hostnamebyanyaddr(&RealHostAddr));
E 184
I 184
			p = hostnamebyanyaddr(&RealHostAddr);
I 270
			if (strlen(p) > MAXNAME)
				p[MAXNAME] = '\0';
E 270
			RealHostName = newstr(p);
I 216
			setproctitle("startup with %s", p);
E 216
E 184
E 158

D 158
#ifdef NETISO
			  case AF_ISO:
				hp = gethostbyaddr((char *) &RealHostAddr.siso.siso_addr,
					sizeof RealHostAddr.siso.siso_addr,
					AF_ISO);
				break;
#endif

			  default:
				hp = gethostbyaddr(RealHostAddr.sa.sa_data,
					   sizeof RealHostAddr.sa.sa_data,
					   RealHostAddr.sa.sa_family);
				break;
			}

E 147
E 146
E 98
E 85
			if (hp != NULL)
D 62
				(void) sprintf(buf, "%s.ARPA", hp->h_name);
E 62
I 62
D 66
				(void) sprintf(buf, "%s.%s", hp->h_name, NetName);
E 66
I 66
D 98
			{
E 98
D 72
				strcpy(buf, hp->h_name);
E 72
I 72
				(void) strcpy(buf, hp->h_name);
E 72
D 98
				if (NetName != NULL && NetName[0] != '\0' &&
D 67
				    index(hp->h_name), '.') == NULL)
E 67
I 67
				    index(hp->h_name, '.') == NULL)
E 67
				{
D 72
					strcat(buf, ".");
					strcat(buf, NetName);
E 72
I 72
					(void) strcat(buf, ".");
					(void) strcat(buf, NetName);
E 72
				}
			}
E 98
E 66
E 62
			else
D 65
				/* this should produce a dotted quad */
				(void) sprintf(buf, "%lx", otherend.sin_addr.s_addr);
E 65
I 65
			{
D 126
				extern char *inet_ntoa();

E 126
				/* produce a dotted quad */
				(void) sprintf(buf, "[%s]",
D 98
					inet_ntoa(otherend.sin_addr));
E 98
I 98
D 146
					inet_ntoa(RealHostAddr.sin_addr));
E 146
I 146
					anynet_ntoa(&RealHostAddr));
E 146
E 98
			}

E 158
I 120
D 280
#ifdef LOG
D 131
			if (LogLevel > 9)
E 131
I 131
D 181
			if (LogLevel > 10)
E 181
I 181
			if (LogLevel > 11)
E 181
E 131
			{
				/* log connection information */
				syslog(LOG_INFO, "connect from %s (%s)",
D 146
					buf, inet_ntoa(RealHostAddr.sin_addr));
E 146
I 146
D 158
					buf, anynet_ntoa(&RealHostAddr));
E 158
I 158
					RealHostName, anynet_ntoa(&RealHostAddr));
E 158
E 146
			}
#endif

E 280
I 167
D 230
			(void) close(DaemonSocket);
E 230
D 194
			InChannel = fdopen(t, "r");
			OutChannel = fdopen(dup(t), "w");
E 194
I 194
			if ((InChannel = fdopen(t, "r")) == NULL ||
			    (t = dup(t)) < 0 ||
			    (OutChannel = fdopen(t, "w")) == NULL)
			{
				syserr("cannot open SMTP server channel, fd=%d", t);
				exit(0);
			}
E 194

E 167
E 120
			/* should we check for illegal connection here? XXX */
I 166
#ifdef XLA
			if (!xla_host_ok(RealHostName))
			{
D 167
				message("421 Too many sessions for this host");
E 167
I 167
				message("421 Too many SMTP sessions for this host");
E 167
				exit(0);
			}
#endif
E 166

E 65
D 158
			RealHostName = newstr(buf);
E 158
D 166

E 166
E 51
I 20
D 22
			FatalErrors = FALSE;
E 22
E 20
I 7
D 38
			InChannel = fdopen(port, "r");
			OutChannel = fdopen(port, "w");
E 38
I 38
D 46
			close(s);
E 46
I 46
D 167
			(void) close(DaemonSocket);
E 46
			InChannel = fdopen(t, "r");
D 69
			OutChannel = fdopen(t, "w");
E 69
I 69
			OutChannel = fdopen(dup(t), "w");
E 167
E 69
E 38
I 19
D 22
			openxscrpt();
E 19
E 7
			initsys();
E 22
I 7
D 99
# ifdef DEBUG
E 99
D 24
			if (Debug > 1)
E 24
I 24
			if (tTd(15, 2))
E 24
				printf("getreq: returning\n");
D 99
# endif DEBUG
E 99
I 26
D 145
# ifdef LOG
			if (LogLevel > 11)
				syslog(LOG_DEBUG, "connected, pid=%d", getpid());
D 123
# endif LOG
E 123
I 123
# endif /* LOG */
E 145
E 123
E 26
E 7
			return;
		}
I 282

		CurChildren++;
E 282

D 77
		/*
		**  PARENT -- wait for child to terminate.
		**	Perhaps we should allow concurrent processing?
		*/

I 7
# ifdef DEBUG
D 24
		if (Debug > 1)
E 24
I 24
		if (tTd(15, 2))
E 24
		{
			sleep(2);
			printf("getreq: parent waiting\n");
		}
# endif DEBUG

E 77
E 7
D 5
		wait(&st);
E 5
I 5
D 16
		(void) wait(&st);
E 16
I 16
		/* close the port so that others will hang (for a while) */
E 16
I 7
D 15
		close(port);
E 15
I 15
D 38
		(void) close(port);
E 38
I 38
		(void) close(t);
E 38
I 16
D 77

D 57
		/* pick up old zombies; implement load limiting */
		numconnections++;
D 47
		while (wait3(&status, numconnections < MAXCONNS ? WNOHANG : 0, 0) > 0)
E 47
I 47
		while (wait3(&status, numconnections < MaxConnections ? WNOHANG : 0, 0) > 0)
E 47
			numconnections--;
E 57
I 57
		/* pick up old zombies */
D 73
		while (wait3(&status, WNOHANG, 0) > 0)
E 73
I 73
		while (wait3(&status, WNOHANG, (struct rusage *) 0) > 0)
E 73
			continue;
E 77
E 57
E 16
E 15
E 7
E 5
	}
I 40
	/*NOTREACHED*/
I 223
}
/*
**  OPENDAEMONSOCKET -- open the SMTP socket
**
**	Deals with setting all appropriate options.  DaemonAddr must
**	be set up in advance.
**
**	Parameters:
D 225
**		none
E 225
I 225
**		firsttime -- set if this is the initial open.
E 225
**
**	Returns:
**		Size in bytes of the daemon socket addr.
**
**	Side Effects:
**		Leaves DaemonSocket set to the open socket.
**		Exits if the socket cannot be created.
*/

I 226
#define MAXOPENTRIES	10	/* maximum number of tries to open connection */

E 226
int
D 225
opendaemonsocket()
E 225
I 225
opendaemonsocket(firsttime)
	bool firsttime;
E 225
{
	int on = 1;
D 250
	int socksize;
E 250
I 250
	int socksize = 0;
E 250
I 226
	int ntries = 0;
	int saveerrno;
E 226

	if (tTd(15, 2))
		printf("opendaemonsocket()\n");

D 225
	DaemonSocket = socket(DaemonAddr.sa.sa_family, SOCK_STREAM, 0);
	if (DaemonSocket < 0)
E 225
I 225
D 226
	if (firsttime || DaemonSocket < 0)
E 226
I 226
	do
E 226
E 225
	{
I 227
		if (ntries > 0)
			sleep(5);
E 227
D 225
		/* probably another daemon already */
		syserr("opendaemonsocket: can't create server SMTP socket");
	  severe:
E 225
I 225
D 226
		DaemonSocket = socket(DaemonAddr.sa.sa_family, SOCK_STREAM, 0);
		if (DaemonSocket < 0)
E 226
I 226
		if (firsttime || DaemonSocket < 0)
E 226
		{
D 226
			/* probably another daemon already */
			syserr("opendaemonsocket: can't create server SMTP socket");
		  severe:
E 226
I 226
			DaemonSocket = socket(DaemonAddr.sa.sa_family, SOCK_STREAM, 0);
			if (DaemonSocket < 0)
			{
				/* probably another daemon already */
				saveerrno = errno;
				syserr("opendaemonsocket: can't create server SMTP socket");
			  severe:
E 226
E 225
# ifdef LOG
D 225
		if (LogLevel > 0)
			syslog(LOG_ALERT, "problem creating SMTP socket");
E 225
I 225
D 226
			if (LogLevel > 0)
				syslog(LOG_ALERT, "problem creating SMTP socket");
E 226
I 226
				if (LogLevel > 0)
					syslog(LOG_ALERT, "problem creating SMTP socket");
E 226
E 225
# endif /* LOG */
D 225
		finis();
	}
E 225
I 225
D 226
			finis();
		}
E 226
I 226
				DaemonSocket = -1;
				continue;
			}
E 226
E 225

D 225
	/* turn on network debugging? */
	if (tTd(15, 101))
		(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_DEBUG, (char *)&on, sizeof on);
E 225
I 225
D 226
		/* turn on network debugging? */
		if (tTd(15, 101))
			(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_DEBUG, (char *)&on, sizeof on);
E 226
I 226
			/* turn on network debugging? */
			if (tTd(15, 101))
				(void) setsockopt(DaemonSocket, SOL_SOCKET,
						  SO_DEBUG, (char *)&on,
						  sizeof on);
E 226
E 225

D 225
	(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
	(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);
E 225
I 225
D 226
		(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
		(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);
E 226
I 226
			(void) setsockopt(DaemonSocket, SOL_SOCKET,
					  SO_REUSEADDR, (char *)&on, sizeof on);
			(void) setsockopt(DaemonSocket, SOL_SOCKET,
					  SO_KEEPALIVE, (char *)&on, sizeof on);
E 226
E 225

#ifdef SO_RCVBUF
D 225
	if (TcpRcvBufferSize > 0)
	{
		if (setsockopt(DaemonSocket, SOL_SOCKET, SO_RCVBUF,
			       (char *) &TcpRcvBufferSize,
			       sizeof(TcpRcvBufferSize)) < 0)
			syserr("getrequests: setsockopt(SO_RCVBUF)");
	}
E 225
I 225
D 226
		if (TcpRcvBufferSize > 0)
		{
			if (setsockopt(DaemonSocket, SOL_SOCKET, SO_RCVBUF,
				       (char *) &TcpRcvBufferSize,
				       sizeof(TcpRcvBufferSize)) < 0)
				syserr("getrequests: setsockopt(SO_RCVBUF)");
		}
E 226
I 226
			if (TcpRcvBufferSize > 0)
			{
				if (setsockopt(DaemonSocket, SOL_SOCKET,
					       SO_RCVBUF,
					       (char *) &TcpRcvBufferSize,
					       sizeof(TcpRcvBufferSize)) < 0)
					syserr("getrequests: setsockopt(SO_RCVBUF)");
			}
E 226
E 225
#endif

D 225
	switch (DaemonAddr.sa.sa_family)
	{
E 225
I 225
D 226
		switch (DaemonAddr.sa.sa_family)
		{
E 226
I 226
			switch (DaemonAddr.sa.sa_family)
			{
E 226
E 225
D 286
# ifdef NETINET
E 286
I 286
# if NETINET
E 286
D 225
	  case AF_INET:
		socksize = sizeof DaemonAddr.sin;
		break;
E 225
I 225
D 226
		  case AF_INET:
			socksize = sizeof DaemonAddr.sin;
			break;
E 226
I 226
			  case AF_INET:
				socksize = sizeof DaemonAddr.sin;
				break;
E 226
E 225
# endif

D 286
# ifdef NETISO
E 286
I 286
# if NETISO
E 286
D 225
	  case AF_ISO:
		socksize = sizeof DaemonAddr.siso;
		break;
E 225
I 225
D 226
		  case AF_ISO:
			socksize = sizeof DaemonAddr.siso;
			break;
E 226
I 226
			  case AF_ISO:
				socksize = sizeof DaemonAddr.siso;
				break;
E 226
E 225
# endif

D 225
	  default:
		socksize = sizeof DaemonAddr;
		break;
	}
E 225
I 225
D 226
		  default:
			socksize = sizeof DaemonAddr;
			break;
		}
E 226
I 226
			  default:
				socksize = sizeof DaemonAddr;
				break;
			}
E 226
E 225

D 225
	if (bind(DaemonSocket, &DaemonAddr.sa, socksize) < 0)
	{
		syserr("getrequests: cannot bind");
		(void) close(DaemonSocket);
		goto severe;
E 225
I 225
D 226
		if (bind(DaemonSocket, &DaemonAddr.sa, socksize) < 0)
E 226
I 226
			if (bind(DaemonSocket, &DaemonAddr.sa, socksize) < 0)
			{
				saveerrno = errno;
				syserr("getrequests: cannot bind");
				(void) close(DaemonSocket);
				goto severe;
			}
		}
		if (!firsttime && listen(DaemonSocket, ListenQueueSize) < 0)
E 226
		{
D 226
			syserr("getrequests: cannot bind");
E 226
I 226
			saveerrno = errno;
			syserr("getrequests: cannot listen");
E 226
			(void) close(DaemonSocket);
			goto severe;
		}
E 225
D 226
	}
D 225
	if (listen(DaemonSocket, ListenQueueSize) < 0)
E 225
I 225
	if (!firsttime && listen(DaemonSocket, ListenQueueSize) < 0)
E 225
	{
		syserr("getrequests: cannot listen");
		(void) close(DaemonSocket);
		goto severe;
	}
	return socksize;
E 226
I 226
		return socksize;
	} while (ntries++ < MAXOPENTRIES && transienterror(saveerrno));
I 235
	syserr("!opendaemonsocket: server SMTP socket wedged: exiting");
E 235
	finis();
E 226
E 223
I 77
}
/*
D 87
**  REAPCHILD -- pick up the body of my child, lest it become a zombie
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Picks up zombies.
*/

reapchild()
{
	union wait status;

	while (wait3(&status, WNOHANG, (struct rusage *) NULL) > 0)
		continue;
E 77
I 46
}
/*
E 87
**  CLRDAEMON -- reset the daemon connection
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		releases any resources used by the passive daemon.
*/

I 250
void
E 250
clrdaemon()
{
	if (DaemonSocket >= 0)
		(void) close(DaemonSocket);
	DaemonSocket = -1;
I 152
}
/*
**  SETDAEMONOPTIONS -- set options for running the daemon
**
**	Parameters:
**		p -- the options line.
**
**	Returns:
**		none.
*/

I 250
void
E 250
setdaemonoptions(p)
	register char *p;
{
I 155
	if (DaemonAddr.sa.sa_family == AF_UNSPEC)
		DaemonAddr.sa.sa_family = AF_INET;

E 155
	while (p != NULL)
	{
		register char *f;
		register char *v;

		while (isascii(*p) && isspace(*p))
			p++;
		if (*p == '\0')
			break;
		f = p;
		p = strchr(p, ',');
		if (p != NULL)
			*p++ = '\0';
		v = strchr(f, '=');
		if (v == NULL)
			continue;
		while (isascii(*++v) && isspace(*v))
			continue;
I 269
		if (isascii(*f) && isupper(*f))
			*f = tolower(*f);
E 269

		switch (*f)
		{
D 155
		  case 'P':		/* port */
		  case 'p':
E 155
I 155
		  case 'F':		/* address family */
E 155
			if (isascii(*v) && isdigit(*v))
D 155
				DaemonAddr.sin.sin_port = atoi(v);
E 155
I 155
				DaemonAddr.sa.sa_family = atoi(v);
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
			else if (strcasecmp(v, "inet") == 0)
				DaemonAddr.sa.sa_family = AF_INET;
#endif
D 286
#ifdef NETISO
E 286
I 286
#if NETISO
E 286
			else if (strcasecmp(v, "iso") == 0)
				DaemonAddr.sa.sa_family = AF_ISO;
#endif
D 286
#ifdef NETNS
E 286
I 286
#if NETNS
E 286
			else if (strcasecmp(v, "ns") == 0)
				DaemonAddr.sa.sa_family = AF_NS;
#endif
D 286
#ifdef NETX25
E 286
I 286
#if NETX25
E 286
			else if (strcasecmp(v, "x.25") == 0)
				DaemonAddr.sa.sa_family = AF_CCITT;
#endif
E 155
			else
D 155
			{
				register struct servent *sp;
E 155
I 155
				syserr("554 Unknown address family %s in Family=option", v);
			break;
E 155

D 155
				sp = getservbyname(v, "tcp");
				if (sp == NULL)
					syserr("554 server \"%s\" unknown", v);
E 155
I 155
		  case 'A':		/* address */
			switch (DaemonAddr.sa.sa_family)
			{
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
			  case AF_INET:
				if (isascii(*v) && isdigit(*v))
D 246
					DaemonAddr.sin.sin_addr.s_addr = inet_network(v);
E 246
I 246
					DaemonAddr.sin.sin_addr.s_addr = htonl(inet_network(v));
E 246
E 155
				else
D 155
					DaemonAddr.sin.sin_port = sp->s_port;
E 155
I 155
				{
					register struct netent *np;

					np = getnetbyname(v);
					if (np == NULL)
						syserr("554 network \"%s\" unknown", v);
					else
						DaemonAddr.sin.sin_addr.s_addr = np->n_net;
				}
				break;
#endif

			  default:
				syserr("554 Address= option unsupported for family %d",
					DaemonAddr.sa.sa_family);
				break;
E 155
			}
			break;

D 155
		  case 'A':		/* address */
		  case 'a':
			if (isascii(*v) && isdigit(*v))
D 153
				(void) inet_aton(v, &DaemonAddr.sin.sin_addr);
E 153
I 153
				DaemonAddr.sin.sin_addr.s_addr = inet_network(v);
E 153
			else
E 155
I 155
		  case 'P':		/* port */
			switch (DaemonAddr.sa.sa_family)
E 155
			{
D 155
				register struct netent *np;
E 155
I 155
				short port;
E 155

D 155
				np = getnetbyname(v);
				if (np == NULL)
					syserr("554 network \"%s\" unknown", v);
E 155
I 155
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
			  case AF_INET:
				if (isascii(*v) && isdigit(*v))
D 189
					DaemonAddr.sin.sin_port = atoi(v);
E 189
I 189
					DaemonAddr.sin.sin_port = htons(atoi(v));
E 189
E 155
				else
D 155
					DaemonAddr.sin.sin_addr.s_addr = np->n_net;
E 155
I 155
				{
					register struct servent *sp;

					sp = getservbyname(v, "tcp");
					if (sp == NULL)
D 157
						syserr("554 server \"%s\" unknown", v);
E 157
I 157
						syserr("554 service \"%s\" unknown", v);
E 157
					else
I 180
D 181
					{
#ifdef _SCO_unix_
						DaemonAddr.sin.sin_port = htons(sp->s_port);
#else
E 181
E 180
						DaemonAddr.sin.sin_port = sp->s_port;
I 180
D 181
#endif
					}
E 181
E 180
				}
				break;
#endif

D 286
#ifdef NETISO
E 286
I 286
#if NETISO
E 286
			  case AF_ISO:
				/* assume two byte transport selector */
				if (isascii(*v) && isdigit(*v))
D 189
					port = atoi(v);
E 189
I 189
					port = htons(atoi(v));
E 189
				else
				{
					register struct servent *sp;

					sp = getservbyname(v, "tcp");
					if (sp == NULL)
D 157
						syserr("554 server \"%s\" unknown", v);
E 157
I 157
						syserr("554 service \"%s\" unknown", v);
E 157
					else
						port = sp->s_port;
				}
				bcopy((char *) &port, TSEL(&DaemonAddr.siso), 2);
				break;
#endif

			  default:
				syserr("554 Port= option unsupported for family %d",
					DaemonAddr.sa.sa_family);
				break;
E 155
			}
I 171
			break;

		  case 'L':		/* listen queue size */
			ListenQueueSize = atoi(v);
E 171
			break;
I 190

		  case 'S':		/* send buffer size */
			TcpSndBufferSize = atoi(v);
			break;

		  case 'R':		/* receive buffer size */
			TcpRcvBufferSize = atoi(v);
			break;
I 269

		  default:
			syserr("554 DaemonPortOptions parameter \"%s\" unknown", f);
E 269
E 190
		}
	}
E 152
E 46
E 40
E 4
E 3
I 3
	struct wh wbuf;

	wbuf.index = index;
	wbuf.count = 0;
	wbuf.ccount = cnt;
	wbuf.data = buf;
	write(MailPort, &wbuf, sizeof wbuf);
E 3
}
I 7
/*
D 38
**  GETCONNECTION -- make a connection with the outside world
**
I 34
**	This routine is horribly contorted to try to get around a bunch
**	of 4.1a IPC bugs.  There appears to be nothing we can do to make
**	it "right" -- the code to interrupt accepts just doesn't work
**	right.  However, this is an attempt to minimize the probablity
**	of problems.
**
E 34
**	Parameters:
**		none.
**
**	Returns:
**		The port for mail traffic.
**
**	Side Effects:
**		Waits for a connection.
*/

I 16
#define IPPORT_PLAYPORT	3055		/* random number */

E 16
D 8
struct sockaddr_in SendmailAddress = { AF_INET, IPPORT_SENDMAIL };
E 8
I 8
struct sockaddr_in SendmailAddress = { AF_INET, IPPORT_SMTP };
E 8

getconnection()
{
D 36
	register int s;
E 36
I 36
	int s;
#ifdef NVMUNIX
	int t;
#endif NVMUNIX
E 36
D 10
	char *host = "localhost";
E 10
	struct sockaddr otherend;

	/*
	**  Set up the address for the mailer.
	*/

D 10
	SendmailAddress.sin_addr.s_addr = rhost(&host);
E 10
I 10
	SendmailAddress.sin_addr.s_addr = 0;
I 12
	SendmailAddress.sin_port = IPPORT_SMTP;
I 16
# ifdef DEBUG
D 24
	if (Debug > 0)
E 24
I 24
	if (tTd(15, 15))
E 24
		SendmailAddress.sin_port = IPPORT_PLAYPORT;
# endif DEBUG
	SendmailAddress.sin_port = htons(SendmailAddress.sin_port);
E 16
E 12
E 10

	/*
	**  Try to actually open the connection.
	*/

# ifdef DEBUG
D 24
	if (Debug)
E 24
I 24
	if (tTd(15, 1))
E 24
D 10
		printf("getconnection (%s)\n", host);
E 10
I 10
		printf("getconnection\n");
E 10
# endif DEBUG

D 22
	s = socket(SOCK_STREAM, 0, &SendmailAddress, SO_ACCEPTCONN);
I 16
	if (s < 0)
E 22
I 22
D 29
	for (;;)
E 29
I 29
D 30
D 34
	for (;; sleep(10))
E 34
I 34
	for (;; sleep(15))
E 34
E 30
I 30
	for (;;)
E 30
E 29
E 22
	{
I 32
		int i;

E 32
I 26
D 27
		int acptcnt;
E 27
I 27
D 28
		int acptcnt;			/* for debugging */
		time_t lasttick;		/* for debugging */
E 27

E 28
E 26
D 22
		sleep(10);
		return (s);
	}
E 22
I 22
		/* get a socket for the SMTP connection */
I 36
#ifdef NVMUNIX
		s = socket(AF_INET, SOCK_STREAM, 0, 0);
		bind(s, &SendmailAddress, sizeof SendmailAddress, 0);
		listen(s, 10);
#else NVMUNIX
E 36
D 32
		s = socket(SOCK_STREAM, 0, &SendmailAddress, SO_ACCEPTCONN);
E 32
I 32
		/* do loop is to avoid 4.1b kernel bug (?) */
D 34
		i = 50;
E 34
I 34
		i = 60;
E 34
		do
		{
			s = socket(SOCK_STREAM, 0, &SendmailAddress, SO_ACCEPTCONN);
			if (s < 0)
D 34
				sleep(5);
E 34
I 34
				sleep(10);
E 34
		} while (--i > 0 && s < 0);
I 36
#endif NVMUNIX
E 36
E 32
		if (s < 0)
		{
			/* probably another daemon already */
			syserr("getconnection: can't create socket");
D 29
			break;
E 29
I 29
			return (-1);
E 29
		}
E 22
E 16

# ifdef DEBUG
D 22
	if (Debug)
		printf("getconnection: %d\n", s);
E 22
I 22
D 24
		if (Debug)
E 24
I 24
		if (tTd(15, 1))
E 24
			printf("getconnection: %d\n", s);
E 22
# endif DEBUG
D 16
	accept(s, &otherend);
E 16
I 16
D 22
	if (accept(s, &otherend) < 0)
	{
		syserr("accept");
E 22
I 22

		/* wait for a connection */
I 26
D 27
		(void) time(&CurTime);
E 27
I 27
D 28
		lasttick = curtime();
E 27
		acptcnt = 0;
E 26
D 25
		if (accept(s, &otherend) >= 0)
E 25
I 25
		do
		{
I 26
D 27
			long now;

E 27
E 26
			errno = 0;
			(void) accept(s, &otherend);
I 26
D 27
			(void) time(&now);
			if (now == CurTime)
E 27
I 27
			if (lasttick == curtime())
E 27
			{
				if(++acptcnt > 2)
				{
					syserr("wild accept");
					/* abort(); */
					break;
				}
			}
			else
			{
D 27
				CurTime = now;
E 27
I 27
				lasttick = curtime();
E 27
				acptcnt = 0;
			}
E 26
		} while (errno == ETIMEDOUT || errno == EINTR);
		if (errno == 0)
E 28
I 28
D 29
		if (accept(s, &otherend) >= 0)
E 28
E 25
			break;
E 29
I 29
D 30
		do
		{
			errno = 0;
I 36
#ifdef NVMUNIX
			lotherend = sizeof otherend;
			t = accept(s, &otherend, &lotherend, 0);
			if (t >= 0)
				return (t);
#else NVMUNIX
E 36
			if (accept(s, &otherend) >= 0)
				return (s);
I 36
#endif NVMUNIX
E 36
		} while (errno == EINTR);
E 29
D 25

		/* probably innocuous -- retry */
I 23
		if (errno == ETIMEDOUT)
			continue;
E 25
E 23
		syserr("getconnection: accept");
E 30
I 30
		/* contorted code is due to a 4.1a kernel bug */
		errno = 0;
		if (accept(s, &otherend) >= 0)
			return (s);
E 30
E 22
D 18
		close(s);
E 18
I 18
D 34
		(void) close(s);
E 34
I 30
		if (errno != EINTR)
D 31
		{
E 31
			syserr("getconnection: accept");
D 31
			sleep(5);
		}
E 31
I 31
		sleep(5);
I 34
		(void) close(s);
E 34
E 31
E 30
E 18
D 22
		return (-1);
E 22
I 22
D 28
		sleep(20);
E 28
I 28
D 29
		sleep(10);
E 29
E 28
E 22
	}
E 16
D 29

	return (s);
E 29
I 9
}
/*
E 38
**  MAKECONNECTION -- make a connection to an SMTP socket on another machine.
**
**	Parameters:
**		host -- the name of the host.
I 12
**		port -- the port number to connect to.
E 12
D 113
**		outfile -- a pointer to a place to put the outfile
**			descriptor.
**		infile -- ditto for infile.
E 113
I 113
**		mci -- a pointer to the mail connection information
**			structure to be filled in.
E 113
I 112
**		usesecureport -- if set, use a low numbered (reserved)
**			port to provide some rudimentary authentication.
E 112
**
**	Returns:
**		An exit code telling whether the connection could be
**			made and if not why not.
**
**	Side Effects:
**		none.
*/

I 136
D 146
struct sockaddr_in	CurHostAddr;		/* address of current host */
E 146
I 146
SOCKADDR	CurHostAddr;		/* address of current host */
E 146

E 136
I 118
int
E 118
I 83
D 97
int	h_errno;	/*this will go away when code implemented*/

E 97
E 83
D 12
makeconnection(host, outfile, infile)
E 12
I 12
D 112
makeconnection(host, port, outfile, infile)
E 112
I 112
D 113
makeconnection(host, port, outfile, infile, usesecureport)
E 113
I 113
makeconnection(host, port, mci, usesecureport)
E 113
E 112
E 12
	char *host;
I 12
D 18
	int port;
E 18
I 18
	u_short port;
E 18
E 12
D 113
	FILE **outfile;
	FILE **infile;
E 113
I 113
D 118
	register MCONINFO *mci;
E 118
I 118
	register MCI *mci;
E 118
E 113
I 112
	bool usesecureport;
E 112
{
D 90
	register int s;
E 90
I 90
D 250
	register int i, s;
E 250
I 250
	register int i = 0;
	register int s;
E 250
	register struct hostent *hp = (struct hostent *)NULL;
D 112
	extern char *inet_ntoa();
E 112
I 112
D 146
	struct sockaddr_in addr;
E 146
I 146
	SOCKADDR addr;
E 146
E 112
E 90
I 89
	int sav_errno;
I 112
D 146
	extern char *inet_ntoa();
E 146
I 146
	int addrlen;
I 241
	bool firstconnect;
E 241
E 146
E 112
I 97
D 217
#ifdef NAMED_BIND
E 217
I 217
D 289
#if NAMED_BIND
E 217
	extern int h_errno;
#endif
E 289
E 97
E 89

	/*
	**  Set up the address for the mailer.
I 35
	**	Accept "[a.b.c.d]" syntax for host name.
E 35
	*/

I 97
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
E 97
I 83
	h_errno = 0;
I 97
#endif
E 97
	errno = 0;
I 154
	bzero(&CurHostAddr, sizeof CurHostAddr);
I 186
	SmtpPhase = mci->mci_phase = "initial connection";
E 186
I 156
	CurHostName = host;
E 156
E 154

E 83
D 35
	if ((SendmailAddress.sin_addr.s_addr = rhost(&host)) == -1)
E 35
I 35
	if (host[0] == '[')
	{
D 51
		long hid = 0;
		int i, j;
		register char *p = host;
E 51
I 51
		long hid;
D 123
		register char *p = index(host, ']');
E 123
I 123
		register char *p = strchr(host, ']');
E 123
E 51

D 51
		for (i = 3; i >= 0 && *p != ']' && *p != '\0'; i--)
E 51
I 51
		if (p != NULL)
E 51
		{
D 51
			j = 0;
			while (isdigit(*++p))
				j = j * 10 + (*p - '0');
			if (*p != (i == 0 ? ']' : '.') || j > 255 || j < 0)
				break;
			hid |= j << ((3 - i) * 8);
E 51
I 51
			*p = '\0';
I 172
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
E 172
			hid = inet_addr(&host[1]);
I 138
			if (hid == -1)
I 172
#endif
E 172
			{
				/* try it as a host name (avoid MX lookup) */
D 260
				hp = gethostbyname(&host[1]);
E 260
I 260
				hp = sm_gethostbyname(&host[1]);
E 260
I 218
				if (hp == NULL && p[-1] == '.')
				{
I 231
D 243
#ifdef NAMED_BIND
E 243
I 243
#if NAMED_BIND
E 243
					int oldopts = _res.options;

					_res.options &= ~(RES_DEFNAMES|RES_DNSRCH);
#endif
E 231
					p[-1] = '\0';
D 260
					hp = gethostbyname(&host[1]);
E 260
I 260
					hp = sm_gethostbyname(&host[1]);
E 260
					p[-1] = '.';
I 231
D 243
#ifdef NAMED_BIND
E 243
I 243
#if NAMED_BIND
E 243
					_res.options = oldopts;
#endif
E 231
				}
E 218
				*p = ']';
				goto gothostent;
			}
E 138
			*p = ']';
E 51
		}
D 51
		if (i >= 0 || *p != ']' || *++p != '\0')
E 51
I 51
D 138
		if (p == NULL || hid == -1)
E 138
I 138
		if (p == NULL)
E 138
E 51
		{
D 134
			usrerr("Invalid numeric domain spec \"%s\"", host);
E 134
I 134
			usrerr("553 Invalid numeric domain spec \"%s\"", host);
I 266
			mci->mci_status = "5.1.2";
E 266
E 134
			return (EX_NOHOST);
		}
D 112
		SendmailAddress.sin_addr.s_addr = hid;
E 112
I 112
D 146
		addr.sin_addr.s_addr = hid;
E 146
I 146
D 147
		addr.sa_family = AF_INET;
		addr.sa_len = sizeof hid;
		addr.sa_u.sa_inet.sin_addr.s_addr = hid;
E 147
I 147
D 172
		addr.sin.sin_family = AF_INET;
E 172
I 172
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
		addr.sin.sin_family = AF_INET;		/*XXX*/
E 172
		addr.sin.sin_addr.s_addr = hid;
I 172
#endif
E 172
E 147
E 146
E 112
	}
D 38
	else if ((SendmailAddress.sin_addr.s_addr = rhost(&host)) == -1)
E 35
		return (EX_NOHOST);
E 38
I 38
	else
	{
I 218
		register char *p = &host[strlen(host) - 1];

E 218
D 90
		register struct hostent *hp = gethostbyname(host);

E 90
I 90
D 260
		hp = gethostbyname(host);
E 260
I 260
		hp = sm_gethostbyname(host);
E 260
I 218
		if (hp == NULL && *p == '.')
		{
I 231
D 243
#ifdef NAMED_BIND
E 243
I 243
#if NAMED_BIND
E 243
			int oldopts = _res.options;

			_res.options &= ~(RES_DEFNAMES|RES_DNSRCH);
#endif
E 231
			*p = '\0';
D 260
			hp = gethostbyname(host);
E 260
I 260
			hp = sm_gethostbyname(host);
E 260
			*p = '.';
I 231
D 243
#ifdef NAMED_BIND
E 243
I 243
#if NAMED_BIND
E 243
			_res.options = oldopts;
#endif
E 231
		}
E 218
I 138
gothostent:
E 138
E 90
I 74
D 83
		if (errno == ETIMEDOUT)
		{
			CurEnv->e_flags &= ~EF_FATALERRS;
			return (EX_TEMPFAIL);
		}
E 83
E 74
D 51
		if (hp == 0)
E 51
I 51
		if (hp == NULL)
I 83
		{
I 97
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
E 97
D 240
			if (errno == ETIMEDOUT || h_errno == TRY_AGAIN)
E 240
I 240
			/* check for name server timeouts */
			if (errno == ETIMEDOUT || h_errno == TRY_AGAIN ||
			    (errno == ECONNREFUSED && UseNameServer))
			{
D 247
				mci->mci_status = "466";
E 247
I 247
				mci->mci_status = "4.4.3";
E 247
E 240
D 88
			{
				CurEnv->e_flags &= ~EF_FATALERRS;
E 88
				return (EX_TEMPFAIL);
I 97
D 240

			/* if name server is specified, assume temp fail */
			if (errno == ECONNREFUSED && UseNameServer)
				return (EX_TEMPFAIL);
E 240
I 240
			}
E 240
#endif
E 97
D 88
			}
E 88
D 86
#ifdef notdef
			if (h_errno == NO_ADDRESS)
				;		/*look for mail forwarder records*/
#endif notdef
E 86
I 86
D 132

			/*
			**  XXX Should look for mail forwarder record here
			**  XXX if (h_errno == NO_ADDRESS).
			*/

E 132
E 86
E 83
E 51
			return (EX_NOHOST);
I 83
		}
E 83
D 65
		bmove(hp->h_addr, (char *) &SendmailAddress.sin_addr, hp->h_length);
E 65
I 65
D 112
		bcopy(hp->h_addr, (char *) &SendmailAddress.sin_addr, hp->h_length);
E 112
I 112
D 146
		bcopy(hp->h_addr, (char *) &addr.sin_addr, hp->h_length);
E 146
I 146
D 147
		addr.sa_family = hp->h_addrtype;
		addr.sa_len = hp->h_length;
		if (addr.sa_family == AF_INET)
E 147
I 147
		addr.sa.sa_family = hp->h_addrtype;
		switch (hp->h_addrtype)
		{
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
		  case AF_INET:
E 147
			bcopy(hp->h_addr,
D 147
				&addr.sa_u.sa_inet.sin_addr,
E 147
I 147
				&addr.sin.sin_addr,
E 147
D 204
				hp->h_length);
E 204
I 204
D 232
				sizeof addr.sin.sin_addr);
E 232
I 232
D 233
				IPADDRSIZE);
E 233
I 233
				INADDRSZ);
E 233
E 232
E 204
D 147
		else
E 147
I 147
			break;
#endif

		  default:
E 147
			bcopy(hp->h_addr,
D 147
				addr.sa_u.sa_data,
E 147
I 147
				addr.sa.sa_data,
E 147
				hp->h_length);
I 147
			break;
		}
E 147
E 146
E 112
I 90
		i = 1;
E 90
E 65
	}

	/*
	**  Determine the port number.
	*/

E 38
I 12
D 41
	if (port == 0)
E 41
I 41
D 283
	if (port != 0)
D 112
		SendmailAddress.sin_port = htons(port);
E 112
I 112
D 146
		addr.sin_port = htons(port);
E 146
I 146
		port = htons(port);
E 146
E 112
	else
E 283
I 283
	if (port == 0)
E 283
E 41
D 38
		port = IPPORT_SMTP;
E 38
I 38
	{
		register struct servent *sp = getservbyname("smtp", "tcp");

		if (sp == NULL)
		{
D 134
			syserr("makeconnection: server \"smtp\" unknown");
E 134
I 134
D 157
			syserr("554 makeconnection: server \"smtp\" unknown");
E 157
I 157
D 261
			syserr("554 makeconnection: service \"smtp\" unknown");
E 261
I 261
#ifdef LOG
			if (LogLevel > 2)
				syslog(LOG_ERR, "makeconnection: service \"smtp\" unknown");
#endif
E 261
E 157
E 134
D 131
			return (EX_OSFILE);
E 131
I 131
D 205
			return (EX_OSERR);
E 205
I 205
			port = htons(25);
E 205
E 131
		}
I 180
D 181
#ifdef _SCO_unix_
		port = htons(sp->s_port);
#else
E 181
E 180
D 41
		port = sp->s_port;
E 41
I 41
D 112
		SendmailAddress.sin_port = sp->s_port;
E 112
I 112
D 146
		addr.sin_port = sp->s_port;
E 146
I 146
D 205
		port = sp->s_port;
E 205
I 205
		else
			port = sp->s_port;
E 205
I 180
D 181
#endif
E 181
E 180
E 146
E 112
E 41
	}
E 38
D 16
	SendmailAddress.sin_port = port;
E 16
I 16
D 41
	SendmailAddress.sin_port = htons(port);
E 41
E 16
E 12

I 146
D 147
	switch (addr.sa_family)
E 147
I 147
	switch (addr.sa.sa_family)
E 147
	{
I 172
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
E 172
	  case AF_INET:
D 147
		addr.sa_u.sa_inet.sin_port = port;
E 147
I 147
		addr.sin.sin_port = port;
E 147
		addrlen = sizeof (struct sockaddr_in);
		break;
I 172
#endif
E 172

D 286
#ifdef NETISO
E 286
I 286
#if NETISO
E 286
	  case AF_ISO:
		/* assume two byte transport selector */
		bcopy((char *) &port, TSEL((struct sockaddr_iso *) &addr), 2);
		addrlen = sizeof (struct sockaddr_iso);
		break;
#endif

	  default:
D 147
		syserr("Can't connect to address family %d", addr.sa_family);
E 147
I 147
		syserr("Can't connect to address family %d", addr.sa.sa_family);
E 147
		return (EX_NOHOST);
	}

E 146
	/*
	**  Try to actually open the connection.
	*/

I 166
#ifdef XLA
	/* if too many connections, don't bother trying */
	if (!xla_noqueue_ok(host))
		return EX_TEMPFAIL;
#endif

I 241
	firstconnect = TRUE;
E 241
E 166
I 90
D 130
again:
E 90
D 99
# ifdef DEBUG
E 99
D 24
	if (Debug)
E 24
I 24
	if (tTd(16, 1))
E 24
D 90
		printf("makeconnection (%s)\n", host);
E 90
I 90
		printf("makeconnection (%s [%s])\n", host,
D 108
		    inet_ntoa(SendmailAddress.sin_addr.s_addr));
E 108
I 108
D 112
		    inet_ntoa(SendmailAddress.sin_addr));
E 112
I 112
		    inet_ntoa(addr.sin_addr));
E 112
E 108
E 90
D 99
# endif DEBUG
E 99

I 36
#ifdef NVMUNIX
	s = socket(AF_INET, SOCK_STREAM, 0, 0);
#else NVMUNIX
E 36
D 15
	s = socket(SOCK_STREAM, 0, 0, 0);
E 15
I 15
D 38
	s = socket(SOCK_STREAM, 0, (struct sockaddr_in *) 0, 0);
E 38
I 38
D 73
	s = socket(AF_INET, SOCK_STREAM, 0, 0);
E 73
I 73
D 112
	s = socket(AF_INET, SOCK_STREAM, 0);
E 112
I 112
	if (usesecureport)
E 130
I 130
	for (;;)
E 130
	{
D 130
		int rport = IPPORT_RESERVED - 1;
E 130
I 130
		if (tTd(16, 1))
D 146
			printf("makeconnection (%s [%s])\n", host,
			    inet_ntoa(addr.sin_addr));
E 146
I 146
			printf("makeconnection (%s [%s])\n",
				host, anynet_ntoa(&addr));
E 146
E 130

I 142
		/* save for logging */
		CurHostAddr = addr;

E 142
D 130
		s = rresvport(&rport);
	}
	else
	{
		s = socket(AF_INET, SOCK_STREAM, 0);
	}
E 112
E 73
E 38
I 36
#endif NVMUNIX
E 36
E 15
	if (s < 0)
	{
D 112
		syserr("makeconnection: no socket");
E 112
I 89
		sav_errno = errno;
I 112
		syserr("makeconnection: no socket");
E 112
E 89
		goto failure;
	}
E 130
I 130
		if (usesecureport)
		{
			int rport = IPPORT_RESERVED - 1;
E 130

D 99
# ifdef DEBUG
E 99
D 24
	if (Debug)
E 24
I 24
D 130
	if (tTd(16, 1))
E 24
D 118
		printf("makeconnection: %d\n", s);
E 118
I 118
		printf("makeconnection: fd=%d\n", s);
E 130
I 130
			s = rresvport(&rport);
		}
		else
		{
			s = socket(AF_INET, SOCK_STREAM, 0);
		}
		if (s < 0)
		{
			sav_errno = errno;
D 288
			syserr("makeconnection: no socket");
E 288
I 288
			syserr("makeconnection: cannot create socket");
E 288
			goto failure;
		}
I 190

#ifdef SO_SNDBUF
		if (TcpSndBufferSize > 0)
		{
			if (setsockopt(s, SOL_SOCKET, SO_SNDBUF,
D 193
				       &TcpSndBufferSize,
E 193
I 193
				       (char *) &TcpSndBufferSize,
E 193
				       sizeof(TcpSndBufferSize)) < 0)
				syserr("makeconnection: setsockopt(SO_SNDBUF)");
D 191
		}
#endif

#ifdef SO_RCVBUF
		if (TcpRcvBufferSize > 0)
		{
			if (setsockopt(s, SOL_SOCKET, SO_RCVBUF,
				       &TcpRcvBufferSize,
				       sizeof(TcpRcvBufferSize)) < 0)
				syserr("makeconnection: setsockopt(SO_RCVBUF)");
E 191
		}
#endif
E 190
E 130
E 118
I 48

D 130
	/* turn on network debugging? */
D 121
	if (tTd(16, 14))
E 121
I 121
	if (tTd(16, 101))
E 121
D 75
		(void) setsockopt(s, SOL_SOCKET, SO_DEBUG, 0, 0);
E 75
I 75
	{
		int on = 1;
		(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_DEBUG, (char *)&on, sizeof on);
	}
E 75
E 48
D 99
# endif DEBUG
E 99
I 21
D 24
	fflush(Xscript);				/* for debugging */
E 24
I 24
D 37
	(void) fflush(Xscript);				/* for debugging */
E 37
I 37
D 102
	(void) fflush(CurEnv->e_xfp);			/* for debugging */
E 102
I 102
	if (CurEnv->e_xfp != NULL)
		(void) fflush(CurEnv->e_xfp);		/* for debugging */
E 102
I 60
	errno = 0;					/* for debugging */
E 60
E 37
I 36
#ifdef NVMUNIX
	bind(s, &SendmailAddress, sizeof SendmailAddress, 0);
	if (connect(s, &SendmailAddress, sizeof SendmailAddress, 0) < 0)
#else NVMUNIX
E 36
E 24
E 21
D 38
	if (connect(s, &SendmailAddress) < 0)
E 38
I 38
D 112
	SendmailAddress.sin_family = AF_INET;
D 49
	bind(s, &SendmailAddress, sizeof SendmailAddress, 0);
E 49
I 49
D 51
	/* bind(s, &SendmailAddress, sizeof SendmailAddress, 0); */
E 51
E 49
D 73
	if (connect(s, &SendmailAddress, sizeof SendmailAddress, 0) < 0)
E 73
I 73
D 107
	if (connect(s, &SendmailAddress, sizeof SendmailAddress) < 0)
E 107
I 107
	if (connect(s,
	    (struct sockaddr *)&SendmailAddress, sizeof SendmailAddress) < 0)
E 112
I 112
	addr.sin_family = AF_INET;
	if (connect(s, (struct sockaddr *) &addr, sizeof addr) < 0)
E 112
E 107
E 73
E 38
I 36
#endif NVMUNIX
E 36
	{
E 130
I 130
		if (tTd(16, 1))
			printf("makeconnection: fd=%d\n", s);

		/* turn on network debugging? */
		if (tTd(16, 101))
		{
			int on = 1;
D 226
			(void) setsockopt(DaemonSocket, SOL_SOCKET, SO_DEBUG,
E 226
I 226
			(void) setsockopt(s, SOL_SOCKET, SO_DEBUG,
E 226
					  (char *)&on, sizeof on);
		}
		if (CurEnv->e_xfp != NULL)
			(void) fflush(CurEnv->e_xfp);		/* for debugging */
		errno = 0;					/* for debugging */
D 146
		addr.sin_family = AF_INET;
		if (connect(s, (struct sockaddr *) &addr, sizeof addr) >= 0)
E 146
I 146
		if (connect(s, (struct sockaddr *) &addr, addrlen) >= 0)
E 146
			break;
I 241

		/* if running demand-dialed connection, try again */
		if (DialDelay > 0 && firstconnect)
		{
			if (tTd(16, 1))
				printf("Connect failed (%s); trying again...\n",
					errstring(sav_errno));
			firstconnect = FALSE;
			sleep(DialDelay);
			continue;
		}
E 241

		/* couldn't connect.... figure out why */
E 130
I 89
		sav_errno = errno;
		(void) close(s);
I 90
D 250
		if (hp && hp->h_addr_list[i])
E 250
I 250
		if (hp != NULL && hp->h_addr_list[i])
E 250
		{
I 146
D 175
			extern char *errstring();

E 175
E 146
I 130
			if (tTd(16, 1))
D 146
				printf("Connect failed; trying new address....\n");
E 130
D 112
			bcopy(hp->h_addr_list[i++],
			    (char *)&SendmailAddress.sin_addr, hp->h_length);
E 112
I 112
			bcopy(hp->h_addr_list[i++], (char *) &addr.sin_addr,
E 146
I 146
				printf("Connect failed (%s); trying new address....\n",
					errstring(sav_errno));
D 147
			if (addr.sa_family == AF_INET)
E 147
I 147
			switch (addr.sa.sa_family)
			{
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
			  case AF_INET:
E 147
				bcopy(hp->h_addr_list[i++],
D 147
				      &addr.sa_u.sa_inet.sin_addr,
E 147
I 147
				      &addr.sin.sin_addr,
E 147
D 204
				      hp->h_length);
E 204
I 204
D 232
				      sizeof addr.sin.sin_addr);
E 232
I 232
D 233
				      IPADDRSIZE);
E 233
I 233
				      INADDRSZ);
E 233
E 232
E 204
D 147
			else
E 147
I 147
				break;
#endif

			  default:
E 147
				bcopy(hp->h_addr_list[i++],
D 147
					addr.sa_u.sa_data,
E 147
I 147
					addr.sa.sa_data,
E 147
E 146
					hp->h_length);
I 147
				break;
			}
E 147
E 112
D 130
			goto again;
E 130
I 130
			continue;
E 130
		}

E 90
E 89
		/* failure, decide if temporary or not */
	failure:
I 167
#ifdef XLA
		xla_host_end(host);
#endif
E 167
D 89
		switch (errno)
E 89
I 89
D 141
		switch (sav_errno)
E 141
I 141
		if (transienterror(sav_errno))
			return EX_TEMPFAIL;
D 146
		else if (sav_errno == EPERM)
E 141
E 89
		{
D 141
		  case EISCONN:
		  case ETIMEDOUT:
I 14
		  case EINPROGRESS:
		  case EALREADY:
		  case EADDRINUSE:
I 44
		  case EHOSTDOWN:
E 44
		  case ENETDOWN:
		  case ENETRESET:
		  case ENOBUFS:
I 17
		  case ECONNREFUSED:
I 54
		  case ECONNRESET:
E 54
I 42
		  case EHOSTUNREACH:
I 43
		  case ENETUNREACH:
I 111
#ifdef ENOSR
		  case ENOSR:
#endif
E 111
E 43
E 42
E 17
E 14
			/* there are others, I'm sure..... */
I 65
D 88
			CurEnv->e_flags &= ~EF_FATALERRS;
E 88
E 65
			return (EX_TEMPFAIL);

I 51
		  case EPERM:
E 141
			/* why is this happening? */
			syserr("makeconnection: funny failure, addr=%lx, port=%x",
D 112
				SendmailAddress.sin_addr.s_addr, SendmailAddress.sin_port);
E 112
I 112
				addr.sin_addr.s_addr, addr.sin_port);
E 112
D 60
			/* explicit fall-through */
E 60
I 60
			return (EX_TEMPFAIL);
I 141
		}
E 146
		else
		{
D 175
			extern char *errstring();
E 141
E 60

E 175
E 51
D 141
		  default:
I 92
D 102
			message(Arpa_Info, "%s", errstring(sav_errno));
E 92
			return (EX_UNAVAILABLE);
E 102
I 102
			{
				extern char *errstring();

D 134
				message(Arpa_Info, "%s", errstring(sav_errno));
E 134
I 134
				message("%s", errstring(sav_errno));
E 134
				return (EX_UNAVAILABLE);
			}
E 141
I 141
			message("%s", errstring(sav_errno));
I 166
D 167
#ifdef XLA
			xla_host_end(host);
#endif
E 167
E 166
			return (EX_UNAVAILABLE);
E 141
E 102
		}
	}

	/* connection ok, put it into canonical form */
D 116
	*outfile = fdopen(s, "w");
D 104
	*infile = fdopen(s, "r");
E 104
I 104
	*infile = fdopen(dup(s), "r");
E 116
I 116
D 194
	mci->mci_out = fdopen(s, "w");
	mci->mci_in = fdopen(dup(s), "r");
E 194
I 194
	if ((mci->mci_out = fdopen(s, "w")) == NULL ||
	    (s = dup(s)) < 0 ||
D 195
	    (mci->mci_in = fdopen(dup(s), "r")) == NULL)
E 195
I 195
	    (mci->mci_in = fdopen(s, "r")) == NULL)
E 195
	{
		syserr("cannot open SMTP client channel, fd=%d", s);
		return EX_TEMPFAIL;
	}
E 194
I 136
D 142

	/* save for logging */
	CurHostAddr = addr;
E 142
E 136
E 116
E 104

D 43
	return (0);
E 43
I 43
	return (EX_OK);
E 43
E 9
}
I 50
/*
**  MYHOSTNAME -- return the name of this host.
**
**	Parameters:
**		hostbuf -- a place to return the name of this host.
I 55
**		size -- the size of hostbuf.
E 55
**
**	Returns:
**		A list of aliases for this host.
**
**	Side Effects:
D 133
**		none.
E 133
I 133
D 187
**		Sets the MyIpAddrs buffer to a list of my IP addresses.
E 187
I 187
**		Adds numeric codes to $=w.
E 187
E 133
*/

I 133
D 187
struct in_addr	MyIpAddrs[MAXIPADDR + 1];

E 187
E 133
D 229
char **
E 229
I 229
struct hostent *
E 229
D 55
myhostname(hostbuf)
E 55
I 55
myhostname(hostbuf, size)
E 55
	char hostbuf[];
I 55
	int size;
E 55
{
I 133
	register struct hostent *hp;
E 133
D 260
	extern struct hostent *gethostbyname();
E 260
I 235
	extern bool getcanonname();
D 289
	extern int h_errno;
E 289
E 235
D 51
	struct hostent *hent;
E 51
I 51
D 133
	struct hostent *hp;
E 133
I 52
D 55
	auto int i = 30;
E 55
I 55
D 63
	auto int i = size;
E 63
E 55
I 53
D 59
	register char *p;
E 59
E 53
E 52
E 51

D 52
	gethostname(hostbuf, sizeof hostbuf);
E 52
I 52
D 63
	gethostname(hostbuf, &i);
E 63
I 63
D 73
	gethostname(hostbuf, size);
E 73
I 73
	if (gethostname(hostbuf, size) < 0)
	{
		(void) strcpy(hostbuf, "localhost");
	}
E 73
E 63
E 52
D 51
	hent = gethostbyname(hostbuf);
	if (hent != NULL)
		return (hent->h_aliases);
E 51
I 51
D 260
	hp = gethostbyname(hostbuf);
E 260
I 260
	hp = sm_gethostbyname(hostbuf);
E 260
I 53
D 59
	for (p = hostbuf; *p != '\0'; p++)
		if (islower(*p))
			*p -= 'a' - 'A';
E 59
E 53
D 224
	if (hp != NULL)
E 224
I 224
	if (hp == NULL)
E 224
I 64
D 242
	{
I 222
D 224
		(void) strncpy(hostbuf, hp->h_name, size - 1);
		hostbuf[size - 1] = '\0';
E 222
D 72
		strcpy(hostbuf, hp->h_name);
E 72
I 72
D 133
		(void) strcpy(hostbuf, hp->h_name);
E 133
I 133
D 220
		(void) strncpy(hostbuf, hp->h_name, size - 1);
		hostbuf[size - 1] = '\0';
E 220
I 220
#ifdef NAMED_BIND
D 222
		if (strchr(hp->h_name, '.') == NULL)
E 222
I 222
		/* if still no dot, try DNS directly (i.e., avoid NIS) */
		if (strchr(hostbuf, '.') == NULL)
E 222
		{
			extern bool getcanonname();
E 224
I 224
		syserr("!My host name (%s) does not seem to exist!", hostbuf);
	}
E 242
I 242
		return NULL;
E 242
D 235
	(void) strncpy(hostbuf, hp->h_name, size - 1);
	hostbuf[size - 1] = '\0';
E 235
I 235
	if (strchr(hp->h_name, '.') != NULL || strchr(hostbuf, '.') == NULL)
	{
		(void) strncpy(hostbuf, hp->h_name, size - 1);
		hostbuf[size - 1] = '\0';
	}
E 235
E 224

D 224
			(void) getcanonname(hostbuf, size, TRUE);
E 224
I 224
D 285
#if NAMED_BIND
E 285
D 235
	/* if still no dot, try DNS directly (i.e., avoid NIS problems) */
	if (strchr(hostbuf, '.') == NULL)
E 235
I 235
	/*
D 285
	**  If still no dot, try DNS directly (i.e., avoid NIS problems).
	**  This ought to be driven from the configuration file, but
	**  we are called before the configuration is read.  We could
	**  check for an /etc/resolv.conf file, but that isn't required.
	**  All in all, a bit of a mess.
E 285
I 285
	**  If there is still no dot in the name, try looking for a
	**  dotted alias.
E 285
	*/

D 281
	if (strchr(hostbuf, '.') == NULL &&
	    !getcanonname(hostbuf, size, TRUE) &&
	    h_errno == TRY_AGAIN)
E 281
I 281
	if (strchr(hostbuf, '.') == NULL)
E 281
E 235
	{
D 235
		extern bool getcanonname();
		extern int h_errno;
E 235
I 235
D 250
		struct stat stbuf;
E 235

E 250
D 281
		/* try twice in case name server not yet started up */
D 235
		if (!getcanonname(hostbuf, size, TRUE) &&
		    UseNameServer &&
		    (h_errno != TRY_AGAIN ||
		     (sleep(30), !getcanonname(hostbuf, size, TRUE))))
		{
E 235
I 235
		message("My unqualifed host name (%s) unknown to DNS; sleeping for retry",
			hostbuf);
		sleep(60);
		if (!getcanonname(hostbuf, size, TRUE))
E 235
			errno = h_errno + E_DNSBASE;
E 281
I 281
D 285
		int nmaps;
		int i;
I 284
		auto int stat;
E 284
		char *maptype[MAXMAPSTACK];
		short mapreturn[MAXMAPACTIONS];
E 285
I 285
		char **ha;
E 285

D 285
		nmaps = switch_map_find("hosts", maptype, mapreturn);
		for (i = 0; i < nmaps; i++)
			if (strcmp(maptype[i], "dns") == 0)
				break;
		if (i < nmaps &&
D 284
		    !dns_getcanonname(hostbuf, size, TRUE) &&
E 284
I 284
		    !dns_getcanonname(hostbuf, size, TRUE, &stat) &&
E 284
		    h_errno == TRY_AGAIN)
E 285
I 285
		for (ha = hp->h_aliases; *ha != NULL; ha++)
E 285
		{
D 285
			/* try twice in case name server not yet started up */
			message("My unqualifed host name (%s) unknown to DNS; sleeping for retry",
				hostbuf);
			sleep(60);
			if (!dns_getcanonname(hostbuf, size, TRUE))
				errno = h_errno + E_DNSBASE;
E 285
I 285
			if (strchr(*ha, '.') != NULL)
			{
				(void) strncpy(hostbuf, *ha, size - 1);
				hostbuf[size - 1] = '\0';
				break;
			}
E 285
		}
E 281
D 235
			syserr("!My host name (%s) not known to DNS",
				hostbuf);
E 224
D 222
		}
		else
#else
		{
			(void) strncpy(hostbuf, hp->h_name, size - 1);
			hostbuf[size - 1] = '\0';
E 222
		}
E 235
I 224
	}
E 224
D 285
#endif
E 285
I 285

	/*
	**  If _still_ no dot, wait for a while and try again -- it is
	**  possible that some service is starting up.  This can result
	**  in excessive delays if the system is badly configured, but
	**  there really isn't a way around that, particularly given that
	**  the config file hasn't been read at this point.
	**  All in all, a bit of a mess.
	*/

	if (strchr(hostbuf, '.') == NULL &&
	    !getcanonname(hostbuf, size, TRUE))
	{
		message("My unqualifed host name (%s) unknown; sleeping for retry",
			hostbuf);
		sleep(60);
		(void) getcanonname(hostbuf, size, TRUE);
	}
E 285
E 220
D 229

D 224
		if (hp->h_addrtype == AF_INET && hp->h_length == 4)
E 224
I 224
	if (hp->h_addrtype == AF_INET && hp->h_length == 4)
	{
		register int i;

		for (i = 0; hp->h_addr_list[i] != NULL; i++)
E 224
		{
D 224
			register int i;
E 224
I 224
			char ipbuf[100];
E 224

D 187
			for (i = 0; i < MAXIPADDR; i++)
E 187
I 187
D 224
			for (i = 0; hp->h_addr_list[i] != NULL; i++)
E 187
			{
D 187
				if (hp->h_addr_list[i] == NULL)
					break;
				MyIpAddrs[i].s_addr = *(u_long *) hp->h_addr_list[i];
E 187
I 187
				char ipbuf[100];

				sprintf(ipbuf, "[%s]",
					inet_ntoa(*((struct in_addr *) hp->h_addr_list[i])));
				setclass('w', ipbuf);
E 187
			}
E 224
I 224
			sprintf(ipbuf, "[%s]",
				inet_ntoa(*((struct in_addr *) hp->h_addr_list[i])));
I 228
			if (tTd(0, 4))
				printf("\ta.k.a.: %s\n", ipbuf);
E 228
			setclass('w', ipbuf);
E 224
D 187
			MyIpAddrs[i].s_addr = 0;
E 187
		}
D 224

E 133
E 72
E 64
		return (hp->h_aliases);
E 224
I 64
	}
E 64
E 51
D 224
	else
		return (NULL);
E 224
I 224

	return (hp->h_aliases);
E 229
I 229
	return (hp);
E 229
E 224
}
I 68
D 95
/*
**  MAPHOSTNAME -- turn a hostname into canonical form
**
**	Parameters:
**		hbuf -- a buffer containing a hostname.
**		hbsize -- the size of hbuf.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Looks up the host specified in hbuf.  If it is not
**		the canonical name for that host, replace it with
**		the canonical name.  If the name is unknown, or it
**		is already the canonical name, leave it unchanged.
*/
E 95
E 68
D 109

I 95
/*
E 109
I 109
/*
I 137
D 158
**  GETREALHOSTNAME -- get the real host name asociated with a file descriptor
E 158
I 158
**  GETAUTHINFO -- get the real host name asociated with a file descriptor
E 158
**
I 158
**	Uses RFC1413 protocol to try to get info from the other end.
**
E 158
**	Parameters:
**		fd -- the descriptor
**
**	Returns:
D 158
**		The host name associated with this descriptor, if it can
**			be determined.
**		NULL otherwise.
E 158
I 158
**		The user@host information associated with this descriptor.
E 158
D 212
**
**	Side Effects:
D 158
**		none
E 158
I 158
**		Sets RealHostName to the name of the host at the other end.
E 212
E 158
*/

I 158
D 162
#define IDENTPROTO	1

E 162
D 203
#ifdef IDENTPROTO
E 203
I 203
D 245
#if IDENTPROTO
E 203

E 245
static jmp_buf	CtxAuthTimeout;

D 250
static
E 250
I 250
static void
E 250
authtimeout()
{
	longjmp(CtxAuthTimeout, 1);
}

D 245
#endif

E 245
E 158
char *
D 158
getrealhostname(fd)
E 158
I 158
getauthinfo(fd)
E 158
	int fd;
{
D 158
	register struct hostent *hp;
D 146
	struct sockaddr_in sin;
	int sinlen;
E 146
I 146
D 148
	struct sockaddr sa;
E 148
I 148
	SOCKADDR sa;
E 148
	int salen;
E 146
	char hbuf[MAXNAME];
	extern struct hostent *gethostbyaddr();
E 158
I 158
D 219
	SOCKADDR fa;
E 219
	int falen;
I 165
	register char *p;
E 165
D 203
#ifdef IDENTPROTO
E 203
I 203
D 245
#if IDENTPROTO
E 245
E 203
	SOCKADDR la;
	int lalen;
	register struct servent *sp;
	int s;
	int i;
D 165
	register char *p;
E 165
	EVENT *ev;
I 251
	int nleft;
I 253
	char ibuf[MAXNAME + 1];
E 253
I 252
D 254
	int ibuf[MAXNAME + 1];
E 254
I 254
	char ibuf[MAXNAME + 1];
E 254
E 252
E 251
D 245
#endif
E 245
	static char hbuf[MAXNAME * 2 + 2];
	extern char *hostnamebyanyaddr();
D 279
	extern char RealUserName[];			/* main.c */
E 279
E 158
D 146
	extern char *inet_ntoa();
E 146

D 140
	if (getsockname(fd, (struct sockaddr *) &sin, &sinlen) < 0)
E 140
I 140
D 146
	if (getsockname(fd, (struct sockaddr *) &sin, &sinlen) < 0 ||
	    sinlen <= 0)
E 146
I 146
D 158
	salen = sizeof sa;
D 149
	if (getsockname(fd, &sa, &salen) < 0 || salen <= 0)
E 149
I 149
	if (getsockname(fd, &sa.sa, &salen) < 0 || salen <= 0)
E 149
E 146
E 140
		return NULL;
D 146
	hp = gethostbyaddr((char *) &sin.sin_addr, sizeof sin.sin_addr,
			   sin.sin_family);
E 146
I 146
D 148
	hp = gethostbyaddr(sa.sa_data, sa.sa_len,
			   sa.sa_family);
E 148
I 148
D 149
	hp = gethostbyaddr(sa.sa_data, salen, sa.sa_family);
E 149
I 149
	hp = gethostbyaddr(sa.sa.sa_data, salen, sa.sa.sa_family);
E 149
E 148
E 146
	if (hp != NULL)
		(void) strcpy(hbuf, hp->h_name);
E 158
I 158
D 219
	falen = sizeof fa;
D 202
	if (getpeername(fd, &fa.sa, &falen) < 0 || falen <= 0)
E 202
I 202
	if (getpeername(fd, &fa.sa, &falen) < 0 || falen <= 0 ||
	    fa.sa.sa_family == 0)
E 219
I 219
	falen = sizeof RealHostAddr;
D 236
	if (getpeername(fd, &RealHostAddr.sa, &falen) < 0 || falen <= 0 ||
	    RealHostAddr.sa.sa_family == 0)
E 236
I 236
	if (isatty(fd) || getpeername(fd, &RealHostAddr.sa, &falen) < 0 ||
	    falen <= 0 || RealHostAddr.sa.sa_family == 0)
E 236
E 219
E 202
	{
D 212
		RealHostName = "localhost";
E 212
		(void) sprintf(hbuf, "%s@localhost", RealUserName);
D 159
		if (tTd(29, 1))
E 159
I 159
		if (tTd(9, 1))
E 159
			printf("getauthinfo: %s\n", hbuf);
		return hbuf;
	}

I 219
	if (RealHostName == NULL)
	{
		/* translate that to a host name */
		RealHostName = newstr(hostnamebyanyaddr(&RealHostAddr));
	}

E 219
D 184
	RealHostName = newstr(hostnamebyanyaddr(&fa));
E 184
I 184
D 212
	p = hostnamebyanyaddr(&fa);
	RealHostName = newstr(p);
E 184
	RealHostAddr = fa;

E 212
D 203
#ifdef IDENTPROTO
E 203
I 203
D 245
#if IDENTPROTO
E 245
I 211
	if (TimeOuts.to_ident == 0)
		goto noident;

E 211
E 203
	lalen = sizeof la;
D 219
	if (fa.sa.sa_family != AF_INET ||
E 219
I 219
	if (RealHostAddr.sa.sa_family != AF_INET ||
E 219
	    getsockname(fd, &la.sa, &lalen) < 0 || lalen <= 0 ||
	    la.sa.sa_family != AF_INET)
	{
		/* no ident info */
		goto noident;
	}

	/* create ident query */
D 177
	(void) sprintf(hbuf, "%d,%d\r\n", fa.sin.sin_port, la.sin.sin_port);
E 177
I 177
D 252
D 253
	(void) sprintf(hbuf, "%d,%d\r\n",
E 253
I 253
	(void) sprintf(ibuf, "%d,%d\r\n",
E 253
E 252
I 252
	(void) sprintf(ibuf, "%d,%d\r\n",
E 252
D 219
		ntohs(fa.sin.sin_port), ntohs(la.sin.sin_port));
E 219
I 219
		ntohs(RealHostAddr.sin.sin_port), ntohs(la.sin.sin_port));
E 219
E 177

	/* create local address */
D 197
	bzero(&la, sizeof la);
E 197
I 197
	la.sin.sin_port = 0;
E 197

	/* create foreign address */
	sp = getservbyname("auth", "tcp");
	if (sp != NULL)
I 180
D 181
	{
#ifdef _SCO_unix_
		fa.sin.sin_port = htons(sp->s_port);
#else
E 181
E 180
D 219
		fa.sin.sin_port = sp->s_port;
E 219
I 219
		RealHostAddr.sin.sin_port = sp->s_port;
E 219
I 180
D 181
#endif
	}
E 181
E 180
E 158
	else
D 146
		(void) sprintf(hbuf, "[%s]", inet_ntoa(sin.sin_addr));
E 146
I 146
D 158
		(void) sprintf(hbuf, "[%s]", anynet_ntoa(&sa));
E 158
I 158
D 164
		fa.sin.sin_port = 113;
E 164
I 164
D 219
		fa.sin.sin_port = htons(113);
E 219
I 219
		RealHostAddr.sin.sin_port = htons(113);
E 219
E 164

	s = -1;
	if (setjmp(CtxAuthTimeout) != 0)
	{
		if (s >= 0)
			(void) close(s);
		goto noident;
	}

	/* put a timeout around the whole thing */
D 185
	ev = setevent((time_t) 30, authtimeout, 0);
E 185
I 185
	ev = setevent(TimeOuts.to_ident, authtimeout, 0);
E 185

D 197
	/* connect to foreign IDENT server */
E 197
I 197
	/* connect to foreign IDENT server using same address as SMTP socket */
E 197
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		clrevent(ev);
		goto noident;
	}
D 197
	if (connect(s, &fa.sa, sizeof fa.sin) < 0)
E 197
I 197
	if (bind(s, &la.sa, sizeof la.sin) < 0 ||
D 219
	    connect(s, &fa.sa, sizeof fa.sin) < 0)
E 219
I 219
	    connect(s, &RealHostAddr.sa, sizeof RealHostAddr.sin) < 0)
E 219
E 197
	{
D 213
closeident:
		(void) close(s);
		clrevent(ev);
		goto noident;
E 213
I 213
		goto closeident;
E 213
	}

D 159
	if (tTd(29, 1))
E 159
I 159
	if (tTd(9, 10))
E 159
D 252
D 253
		printf("getauthinfo: sent %s", hbuf);
E 253
I 253
		printf("getauthinfo: sent %s", ibuf);
E 253
E 252
I 252
		printf("getauthinfo: sent %s", ibuf);
E 252

	/* send query */
D 252
D 253
	if (write(s, hbuf, strlen(hbuf)) < 0)
E 253
I 253
	if (write(s, ibuf, strlen(ibuf)) < 0)
E 253
E 252
I 252
	if (write(s, ibuf, strlen(ibuf)) < 0)
E 252
		goto closeident;

	/* get result */
D 251
	i = read(s, hbuf, sizeof hbuf);
E 251
I 251
D 252
D 253
	p = &hbuf[0];
	nleft = sizeof(hbuf);
E 253
I 253
	p = &ibuf[0];
D 255
	nleft = sizeof(ibuf);
E 255
I 255
D 259
	nleft = sizeof ibuf - 1;
E 259
E 255
E 253
E 252
I 252
	p = &ibuf[0];
D 259
	nleft = sizeof(ibuf - 1);
E 259
I 259
	nleft = sizeof ibuf - 1;
E 259
E 252
	while ((i = read(s, p, nleft)) > 0)
	{
		p += i;
		nleft -= i;
	}
E 251
	(void) close(s);
	clrevent(ev);
D 251
	if (i <= 0)
E 251
I 251
D 252
D 253
	if (i < 0 || p == &hbuf[0])
E 253
I 253
	if (i < 0 || p == &ibuf[0])
E 253
E 252
I 252
	if (i < 0 || p == &ibuf[0])
E 252
E 251
		goto noident;
D 251
	if (hbuf[--i] == '\n' && hbuf[--i] == '\r')
		i--;
	hbuf[++i] = '\0';
E 251
I 251

	if (*--p == '\n' && *--p == '\r')
		p--;
	*++p = '\0';
E 251

D 159
	if (tTd(29, 1))
E 159
I 159
	if (tTd(9, 3))
E 159
D 252
D 253
		printf("getauthinfo:  got %s\n", hbuf);
E 253
I 253
		printf("getauthinfo:  got %s\n", ibuf);
E 253
E 252
I 252
		printf("getauthinfo:  got %s\n", ibuf);
E 252

	/* parse result */
D 252
D 253
	p = strchr(hbuf, ':');
E 253
I 253
	p = strchr(ibuf, ':');
E 253
E 252
I 252
	p = strchr(ibuf, ':');
E 252
	if (p == NULL)
	{
		/* malformed response */
		goto noident;
	}
	while (isascii(*++p) && isspace(*p))
		continue;
	if (strncasecmp(p, "userid", 6) != 0)
	{
		/* presumably an error string */
		goto noident;
	}
	p += 6;
	while (isascii(*p) && isspace(*p))
		p++;
	if (*p++ != ':')
	{
		/* either useridxx or malformed response */
		goto noident;
	}

	/* p now points to the OSTYPE field */
I 258
	while (isascii(*p) && isspace(*p))
		p++;
	if (strncasecmp(p, "other", 5) == 0 &&
	    (p[5] == ':' || p[5] == ' ' || p[5] == ',' || p[5] == '\0'))
	{
		/* not useful information */
		goto noident;
	}
E 258
	p = strchr(p, ':');
	if (p == NULL)
	{
		/* malformed response */
		goto noident;
	}
D 159
	p++;
E 159

I 159
	/* 1413 says don't do this -- but it's broken otherwise */
	while (isascii(*++p) && isspace(*p))
		continue;

E 159
D 239
	/* p now points to the authenticated name */
D 212
	(void) sprintf(hbuf, "%s@%s", p, RealHostName);
E 212
I 212
	(void) sprintf(hbuf, "%s@%s",
		p, RealHostName == NULL ? "localhost" : RealHostName);
E 239
I 239
	/* p now points to the authenticated name -- copy carefully */
D 249
D 253
	for (i = 0; i < MAXNAME && *p != '\0'; p++)
	{
		if (isascii(*p) &&
		    (isalnum(*p) || strchr("!#$%&'*+-./^_`{|}~", *p) != NULL))
			hbuf[i++] = *p;
	}
E 253
I 253
	cleanstrcpy(hbuf, p, MAXNAME);
I 267
	i = strlen(hbuf);
E 267
E 253
E 249
I 249
	cleanstrcpy(hbuf, p, MAXNAME);
	i = strlen(hbuf);
E 249
	hbuf[i++] = '@';
	strcpy(&hbuf[i], RealHostName == NULL ? "localhost" : RealHostName);
E 239
E 212
I 159
D 275
	goto finish;
E 275
I 275
	goto postident;
E 275
I 213

closeident:
	(void) close(s);
	clrevent(ev);
E 213
D 245

#endif /* IDENTPROTO */
E 245

noident:
I 212
	if (RealHostName == NULL)
	{
		if (tTd(9, 1))
			printf("getauthinfo: NULL\n");
		return NULL;
	}
E 212
	(void) strcpy(hbuf, RealHostName);

D 275
finish:
E 275
I 275
postident:
#if IP_SRCROUTE
	/*
	**  Extract IP source routing information.
	**
	**	Format of output for a connection from site a through b
	**	through c to d:
	**		loose:      @site-c@site-b:site-a
	**		strict:	   !@site-c@site-b:site-a
	**
	**	o - pointer within ipopt_list structure.
	**	q - pointer within ls/ss rr route data
	**	p - pointer to hbuf
	*/

	if (RealHostAddr.sa.sa_family == AF_INET)
	{
		int ipoptlen, j;
D 276
		char *q;
E 276
I 276
		u_char *q;
E 276
		u_char *o;
		struct in_addr addr;
		struct ipoption ipopt;

		ipoptlen = sizeof ipopt;
		if (getsockopt(fd, IPPROTO_IP, IP_OPTIONS,
			       (char *) &ipopt, &ipoptlen) < 0)
			goto noipsr;
		if (ipoptlen == 0)
			goto noipsr;
D 276
		o = (u_char *) &ipopt.ipopt_list;
E 276
I 276
		o = (u_char *) ipopt.ipopt_list;
E 276
D 277
		while (o != NULL && o < (u_char *) (&ipopt + ipoptlen))
E 277
I 277
		while (o != NULL && o < (u_char *) &ipopt + ipoptlen)
E 277
		{
			switch (*o)
			{
			  case IPOPT_EOL: 
				o = NULL;
				break;

			  case IPOPT_NOP:
				o++;
				break;

			  case IPOPT_SSRR:
			  case IPOPT_LSRR:
				p = &hbuf[strlen(hbuf)];
				sprintf(p, " [%s@%s",
				    *o == IPOPT_SSRR ? "!" : "",
				    inet_ntoa(ipopt.ipopt_dst));
				p += strlen(p);

				/* o[1] is option length */
				j = *++o / sizeof(struct in_addr) - 1;

				/* q skips length and router pointer to data */
				q = o + 2;
				for ( ; j >= 0; j--)
				{
					memcpy(&addr, q, sizeof(addr));
D 276
					p += sprintf(p, "%c%s",
E 276
I 276
					sprintf(p, "%c%s",
E 276
						     j ? '@' : ':',
						     inet_ntoa(addr));
D 276
					q+=sizeof(struct in_addr); 
E 276
I 276
					p += strlen(p);
					q += sizeof(struct in_addr); 
E 276
				}
				o += *o;
				break;

			  default:
				/* Skip over option */
				o += o[1];
				break;
			}
		}
		strcat(hbuf,"]");
		goto postipsr;
	}
#endif

noipsr:
E 275
E 159
D 212
	if (RealHostName[0] != '[')
E 212
I 212
	if (RealHostName != NULL && RealHostName[0] != '[')
E 212
	{
		p = &hbuf[strlen(hbuf)];
		(void) sprintf(p, " [%s]", anynet_ntoa(&RealHostAddr));
	}
I 275

postipsr:
E 275
D 159
	if (tTd(29, 1))
E 159
I 159
	if (tTd(9, 1))
E 159
		printf("getauthinfo: %s\n", hbuf);
E 158
E 146
	return hbuf;
I 158
D 159

#endif /* IDENTPROTO */

noident:
	return NULL;
E 159
E 158
}
/*
E 137
E 109
D 115
 *  MAPHOSTNAME -- turn a hostname into canonical form
 *
 *	Parameters:
 *		hbuf -- a buffer containing a hostname.
 *		hbsize -- the size of hbuf.
 *
 *	Returns:
D 109
 *		none.
E 109
I 109
 *		TRUE if the host name was mapped.
 *		FALSE otherwise.
E 109
 *
 *	Side Effects:
 *		Looks up the host specified in hbuf.  If it is not
 *		the canonical name for that host, replace it with
 *		the canonical name.  If the name is unknown, or it
 *		is already the canonical name, leave it unchanged.
 */
E 115
I 115
D 175
**  MAPHOSTNAME -- turn a hostname into canonical form
E 175
I 175
**  HOST_MAP_LOOKUP -- turn a hostname into canonical form
E 175
**
**	Parameters:
I 124
**		map -- a pointer to this map (unused).
E 124
D 175
**		hbuf -- a buffer containing a hostname.
**		hbsize -- the size of hbuf.
E 175
I 175
**		name -- the (presumably unqualified) hostname.
E 175
I 119
D 176
**		avp -- unused -- for compatibility with other mapping
E 176
I 176
**		av -- unused -- for compatibility with other mapping
E 176
**			functions.
I 163
**		statp -- an exit status (out parameter) -- set to
**			EX_TEMPFAIL if the name server is unavailable.
E 163
E 119
**
**	Returns:
**		The mapping, if found.
**		NULL if no mapping found.
**
**	Side Effects:
**		Looks up the host specified in hbuf.  If it is not
**		the canonical name for that host, return the canonical
**		name.
*/
E 115
I 109

D 115
bool
E 109
E 95
I 68
maphostname(hbuf, hbsize)
E 115
I 115
char *
D 124
maphostname(hbuf, hbsize, avp)
E 124
I 124
D 163
maphostname(map, hbuf, hbsize, avp)
E 163
I 163
D 175
maphostname(map, hbuf, hbsize, avp, statp)
E 175
I 175
D 176
host_map_lookup(map, name, avp, statp)
E 176
I 176
host_map_lookup(map, name, av, statp)
E 176
E 175
E 163
	MAP *map;
E 124
E 115
D 175
	char *hbuf;
	int hbsize;
E 175
I 175
	char *name;
E 175
I 115
D 176
	char **avp;
E 176
I 176
	char **av;
E 176
I 163
	int *statp;
E 163
E 115
{
	register struct hostent *hp;
D 95
	extern struct hostent *gethostbyname();
E 95
I 95
D 232
	u_long in_addr;
E 232
I 232
	struct in_addr in_addr;
E 232
D 105
	char ptr[256];
E 105
I 105
D 124
	char ptr[256], *cp;
E 124
I 124
	char *cp;
I 133
D 250
	int i;
E 250
E 133
E 124
E 105
D 169
	struct hostent *gethostbyaddr();
E 169
I 169
	register STAB *s;
I 199
D 206
	char *timeoutmsg = "Recipient domain nameserver timed out";
E 206
E 199
I 175
D 176
	static char hbuf[MAXNAME];
E 176
I 176
D 256
	char hbuf[MAXNAME];
E 256
I 256
	char hbuf[MAXNAME + 1];
E 256
E 176
E 175
D 260
	extern struct hostent *gethostbyaddr();
E 260
I 215
D 217
#ifdef NAMED_BIND
E 217
I 217
D 289
#if NAMED_BIND
E 217
E 215
	extern int h_errno;
I 215
#endif
E 289
E 215
I 176
D 178
	extern char *map_rewrite();
E 178
E 176
E 169
E 95

I 115
D 124
	/* allow room for trailing dot on correct match */
E 124
I 124
D 125
	/* allow room for null & trailing dot on correct match */
E 125
I 125
D 175
	/* allow room for null */
E 125
	hbsize--;
E 124
D 125
	if (ConfigLevel >= 2)
		hbsize--;
E 125

E 175
E 115
D 84
	makelower(hbuf);
	hp = gethostbyname(hbuf);
E 84
I 84
	/*
D 85
	 * If first character is a bracket, then it is an address
	 * lookup.  Address is copied into a temporary buffer to
	 * strip the brackets and to preserve hbuf if address is
	 * unknown.
	 */
E 85
I 85
D 95
	**  If first character is a bracket, then it is an address
	**  lookup.  Address is copied into a temporary buffer to
	**  strip the brackets and to preserve hbuf if address is
	**  unknown.
	*/
E 85

	if (*hbuf == '[')
	{
		extern struct hostent *gethostbyaddr();
		u_long in_addr;
		char ptr[256];
		char *bptr;

D 85
		strcpy(ptr,hbuf);
E 85
I 85
		(void) strcpy(ptr, hbuf);
E 85
		bptr = index(ptr,']');
		*bptr = '\0';
		in_addr = inet_addr(&ptr[1]);
D 85
		hp = gethostbyaddr(&in_addr, sizeof(struct in_addr), AF_INET);
		if(hp == NULL)
			return(NULL);
E 85
I 85
		hp = gethostbyaddr((char *) &in_addr, sizeof(struct in_addr), AF_INET);
		if (hp == NULL)
			return;
E 85
	}
	else
	{
		makelower(hbuf);
I 91
#ifdef MXDOMAIN
E 95
I 95
D 169
	 * If first character is a bracket, then it is an address
	 * lookup.  Address is copied into a temporary buffer to
	 * strip the brackets and to preserve hbuf if address is
	 * unknown.
	 */
E 169
I 169
	**  See if we have already looked up this name.  If so, just
	**  return it.
	*/
E 169
I 115

I 169
D 175
	s = stab(hbuf, ST_NAMECANON, ST_ENTER);
E 175
I 175
	s = stab(name, ST_NAMECANON, ST_ENTER);
E 175
	if (bitset(NCF_VALID, s->s_namecanon.nc_flags))
	{
I 173
		if (tTd(9, 1))
D 175
			printf("maphostname(%s, %d) => CACHE %s\n",
				hbuf, hbsize, s->s_namecanon.nc_cname);
E 175
I 175
			printf("host_map_lookup(%s) => CACHE %s\n",
D 271
				name, s->s_namecanon.nc_cname);
E 271
I 271
			       name,
			       s->s_namecanon.nc_cname == NULL
					? "NULL"
D 272
					: s->s_namecanon.nc_name);
E 272
I 272
					: s->s_namecanon.nc_cname);
E 272
E 271
E 175
E 173
		errno = s->s_namecanon.nc_errno;
I 215
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
E 215
		h_errno = s->s_namecanon.nc_herrno;
I 215
#endif
E 215
		*statp = s->s_namecanon.nc_stat;
I 199
D 264
		if (CurEnv->e_message == NULL && *statp == EX_TEMPFAIL)
E 264
I 264
		if (*statp == EX_TEMPFAIL)
E 264
D 206
			CurEnv->e_message = newstr(timeoutmsg);
E 206
I 206
		{
I 266
			CurEnv->e_status = "4.4.3";
E 266
D 264
			sprintf(hbuf, "%s: Name server timeout",
E 264
I 264
			usrerr("451 %s: Name server timeout",
E 264
				shortenstring(name, 33));
D 264
			CurEnv->e_message = newstr(hbuf);
E 264
		}
E 206
E 199
		return s->s_namecanon.nc_cname;
	}

	/*
	**  If first character is a bracket, then it is an address
	**  lookup.  Address is copied into a temporary buffer to
D 175
	**  strip the brackets and to preserve hbuf if address is
E 175
I 175
	**  strip the brackets and to preserve name if address is
E 175
	**  unknown.
	*/

E 169
E 115
D 109
	if (*hbuf != '[') {
E 95
		getcanonname(hbuf, hbsize);
		return;
D 95
#else MXDOMAIN
E 91
		hp = gethostbyname(hbuf);
I 91
#endif
E 95
E 91
	}
E 109
I 109
D 175
	if (*hbuf != '[')
E 175
I 175
	if (*name != '[')
E 175
D 115
		return (getcanonname(hbuf, hbsize));
E 115
I 115
	{
I 143
D 144
		bool canonical;
E 144
E 143
I 119
		extern bool getcanonname();
I 143
D 144
#ifdef SETPROCTITLE
		char ptbuf[MAXNAME];
		extern char ProcTitleBuf[MAXNAME];
E 144
E 143

I 150
D 151
		printf("maphostname(%s, %d) => ", hbuf, hbsize);
E 151
I 151
		if (tTd(9, 1))
D 175
			printf("maphostname(%s, %d) => ", hbuf, hbsize);
E 175
I 175
			printf("host_map_lookup(%s) => ", name);
E 175
I 169
		s->s_namecanon.nc_flags |= NCF_VALID;		/* will be soon */
E 169
E 151
E 150
E 119
D 143
		if (getcanonname(hbuf, hbsize))
E 143
I 143
D 144
		(void) strcpy(ptbuf, ProcTitleBuf);
		setproctitle("getcanonname(%s)", hbuf);
#endif SETPROCTITLE

		canonical = getcanonname(hbuf, hbsize);

#ifdef SETPROCTITLE
		setproctitle(NULL, ptbuf);
#endif

		if (canonical)
E 144
I 144
D 175
		if (getcanonname(hbuf, hbsize))
E 175
I 175
D 256
		(void) strcpy(hbuf, name);
E 256
I 256
		if (strlen(name) < sizeof hbuf)
			(void) strcpy(hbuf, name);
		else
		{
			bcopy(name, hbuf, sizeof hbuf - 1);
			hbuf[sizeof hbuf - 1] = '\0';
		}
E 256
D 181
		if (getcanonname(hbuf, sizeof hbuf - 1))
E 181
I 181
D 262
		if (getcanonname(hbuf, sizeof hbuf - 1, TRUE))
E 262
I 262
D 287
		if (getcanonname(hbuf, sizeof hbuf - 1, !NoMXforCanon))
E 287
I 287
		if (getcanonname(hbuf, sizeof hbuf - 1, !HasWildcardMX))
E 287
E 262
E 181
E 175
I 150
		{
			if (tTd(9, 1))
				printf("%s\n", hbuf);
I 169
D 176
			s->s_namecanon.nc_cname = newstr(hbuf);
E 169
E 150
E 144
E 143
D 125
		{
			/* found a match -- add the trailing dot */
			if (ConfigLevel >= 2)
D 122
				(void) strcat(hbuf, ".");
E 122
I 122
			{
				int i = strlen(hbuf) - 1;

				if (hbuf[i] != '.')
					(void) strcpy(&hbuf[++i], ".");
			}
E 125
E 122
			return hbuf;
E 176
I 176
			cp = map_rewrite(map, hbuf, strlen(hbuf), av);
			s->s_namecanon.nc_cname = newstr(cp);
			return cp;
E 176
I 150
		}
E 150
D 125
		}
E 125
		else
I 150
		{
I 163
			register struct hostent *hp;
D 169
			extern int h_errno;
E 169

E 163
D 215
			if (tTd(9, 1))
D 163
				printf("FAIL\n");
E 150
			return NULL;
E 163
I 163
				printf("FAIL (%d)\n", h_errno);
E 215
I 169
			s->s_namecanon.nc_errno = errno;
I 215
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
E 215
			s->s_namecanon.nc_herrno = h_errno;
I 215
			if (tTd(9, 1))
				printf("FAIL (%d)\n", h_errno);
E 215
E 169
			switch (h_errno)
			{
			  case TRY_AGAIN:
I 168
				if (UseNameServer)
D 170
					message("Recipient domain nameserver timed out");
E 170
I 170
				{
I 266
					CurEnv->e_status = "4.4.3";
E 266
D 199
					char *msg = "Recipient domain nameserver timed out";

					message(msg);
E 199
I 199
D 206
					message(timeoutmsg);
E 206
I 206
D 208
					extern char MsgBuf[];

					message("%s: Name server timeout",
E 208
I 208
D 264
					sprintf(hbuf, "%s: Name server timeout",
E 264
I 264
					usrerr("451 %s: Name server timeout",
E 264
E 208
						shortenstring(name, 33));
I 208
D 264
					message("%s", hbuf);
E 208
E 206
E 199
					if (CurEnv->e_message == NULL)
D 174
						CurEnv->e_message = msg;
E 174
I 174
D 199
						CurEnv->e_message = newstr(msg);
E 199
I 199
D 206
						CurEnv->e_message = newstr(timeoutmsg);
E 206
I 206
D 208
						CurEnv->e_message = newstr(MsgBuf + 4);
E 208
I 208
						CurEnv->e_message = newstr(hbuf);
E 264
E 208
E 206
E 199
E 174
				}
E 170
E 168
				*statp = EX_TEMPFAIL;
				break;

			  case HOST_NOT_FOUND:
I 268
			  case NO_DATA:
E 268
				*statp = EX_NOHOST;
				break;

			  case NO_RECOVERY:
				*statp = EX_SOFTWARE;
				break;

			  default:
				*statp = EX_UNAVAILABLE;
				break;
			}
I 215
#else
			if (tTd(9, 1))
				printf("FAIL\n");
			*statp = EX_NOHOST;
#endif
E 215
I 169
			s->s_namecanon.nc_stat = *statp;
E 169
D 234
			if (*statp != EX_TEMPFAIL || UseNameServer)
E 234
I 234
			if ((*statp != EX_TEMPFAIL && *statp != EX_NOHOST) ||
			    UseNameServer)
E 234
				return NULL;

			/*
			**  Try to look it up in /etc/hosts
			*/

D 175
			hp = gethostbyname(hbuf);
E 175
I 175
D 260
			hp = gethostbyname(name);
E 260
I 260
			hp = sm_gethostbyname(name);
E 260
E 175
			if (hp == NULL)
			{
				/* no dice there either */
D 169
				*statp = EX_NOHOST;
E 169
I 169
				s->s_namecanon.nc_stat = *statp = EX_NOHOST;
E 169
				return NULL;
			}

D 169
			*statp = EX_OK;
E 169
I 169
			s->s_namecanon.nc_stat = *statp = EX_OK;
D 176
			s->s_namecanon.nc_cname = newstr(hp->h_name);
E 169
			return hp->h_name;
E 176
I 176
			cp = map_rewrite(map, hp->h_name, strlen(hp->h_name), av);
			s->s_namecanon.nc_cname = newstr(cp);
			return cp;
E 176
E 163
I 150
		}
E 150
	}
E 115
E 109
E 84
D 95
	if (hp != NULL)
	{
		int i = strlen(hp->h_name);

		if (i >= hbsize)
D 91
			hp->h_name[--i] = '\0';
E 91
I 91
			hp->h_name[hbsize - 1] = '\0';
E 91
D 72
		strcpy(hbuf, hp->h_name);
E 72
I 72
		(void) strcpy(hbuf, hp->h_name);
E 72
	}
E 95
I 95
D 105
	*index(strcpy(ptr, hbuf), ']') = '\0';
E 105
I 105
D 123
	if ((cp = index(strcpy(ptr, hbuf), ']')) == NULL)
E 123
I 123
D 124
	if ((cp = strchr(strcpy(ptr, hbuf), ']')) == NULL)
E 124
I 124
D 175
	if ((cp = strchr(hbuf, ']')) == NULL)
E 175
I 175
	if ((cp = strchr(name, ']')) == NULL)
E 175
E 124
E 123
D 109
		return;
E 109
I 109
D 115
		return (FALSE);
E 115
I 115
		return (NULL);
E 115
E 109
	*cp = '\0';
E 105
D 124
	in_addr = inet_addr(&ptr[1]);
E 124
I 124
D 175
	in_addr = inet_addr(&hbuf[1]);
E 175
I 175
D 232
	in_addr = inet_addr(&name[1]);
E 232
I 232
	in_addr.s_addr = inet_addr(&name[1]);
E 232
E 175
I 133
D 187

	/* check to see if this is one of our addresses */
	for (i = 0; MyIpAddrs[i].s_addr != 0; i++)
	{
		if (MyIpAddrs[i].s_addr == in_addr)
		{
D 175
			strncpy(hbuf, MyHostName, hbsize);
			hbuf[hbsize] = '\0';
E 175
I 175
D 176
			strncpy(hbuf, MyHostName, sizeof hbuf - 1);
			hbuf[sizeof hbuf - 1] = '\0';
E 175
			return hbuf;
E 176
I 176
			return map_rewrite(map, MyHostName, strlen(MyHostName), av);
E 176
		}
	}
E 187

	/* nope -- ask the name server */
E 133
E 124
D 232
	hp = gethostbyaddr((char *)&in_addr, sizeof(struct in_addr), AF_INET);
E 232
I 232
D 233
	hp = gethostbyaddr((char *)&in_addr, IPADDRSIZE, AF_INET);
E 233
I 233
D 260
	hp = gethostbyaddr((char *)&in_addr, INADDRSZ, AF_INET);
E 260
I 260
	hp = sm_gethostbyaddr((char *)&in_addr, INADDRSZ, AF_INET);
E 260
E 233
E 232
I 169
	s->s_namecanon.nc_errno = errno;
I 215
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
E 215
	s->s_namecanon.nc_herrno = h_errno;
I 215
#endif
E 215
	s->s_namecanon.nc_flags |= NCF_VALID;		/* will be soon */
E 169
	if (hp == NULL)
I 169
	{
		s->s_namecanon.nc_stat = *statp = EX_NOHOST;
E 169
D 109
		return;
E 109
I 109
D 115
		return (FALSE);
E 115
I 115
		return (NULL);
I 169
	}
E 169

D 133
	/* found a match -- copy and dot terminate */
E 133
I 133
	/* found a match -- copy out */
I 169
D 176
	s->s_namecanon.nc_cname = newstr(hp->h_name);
E 169
E 133
E 115
E 109
D 124
	if (strlen(hp->h_name) >= hbsize)
		hp->h_name[hbsize - 1] = '\0';
E 124
I 124
D 175
	if (strlen(hp->h_name) > hbsize)
		hp->h_name[hbsize] = '\0';
E 175
I 175
	if (strlen(hp->h_name) > sizeof hbuf - 1)
		hp->h_name[sizeof hbuf - 1] = '\0';
E 175
E 124
D 115
	(void)strcpy(hbuf, hp->h_name);
I 109
	return (TRUE);
E 115
I 115
	(void) strcpy(hbuf, hp->h_name);
E 176
I 176
	cp = map_rewrite(map, hp->h_name, strlen(hp->h_name), av);
E 176
I 169
	s->s_namecanon.nc_stat = *statp = EX_OK;
E 169
D 125
	if (ConfigLevel >= 2)
		(void) strcat(hbuf, ".");
E 125
D 176
	return hbuf;
E 176
I 176
	s->s_namecanon.nc_cname = newstr(cp);
	return cp;
E 176
I 146
}
/*
**  ANYNET_NTOA -- convert a network address to printable form.
**
**	Parameters:
**		sap -- a pointer to a sockaddr structure.
**
**	Returns:
**		A printable version of that sockaddr.
*/

I 273
D 274
#ifdef AF_LINK
E 274
I 274
D 286
#ifdef NETLINK
E 286
I 286
#if NETLINK
E 286
E 274
# include <net/if_dl.h>
#endif

E 273
char *
anynet_ntoa(sap)
	register SOCKADDR *sap;
{
	register char *bp;
	register char *ap;
	int l;
D 196
	static char buf[80];
E 196
I 196
	static char buf[100];
E 196
I 151

	/* check for null/zero family */
	if (sap == NULL)
		return "NULLADDR";
	if (sap->sa.sa_family == 0)
		return "0";
E 151

I 196
	switch (sap->sa.sa_family)
	{
D 235
#ifdef MAYBENEXTRELEASE		/*** UNTESTED *** UNTESTED *** UNTESTED ***/
E 235
I 200
D 286
#ifdef NETUNIX
E 286
I 286
#if NETUNIX
E 286
E 200
	  case AF_UNIX:
D 198
	  	if (sap->sun.sun_path[0] != '\0')
	  		sprintf(buf, "[UNIX: %.64s]", sap->sun.sun_path);
E 198
I 198
	  	if (sap->sunix.sun_path[0] != '\0')
	  		sprintf(buf, "[UNIX: %.64s]", sap->sunix.sun_path);
E 198
	  	else
	  		sprintf(buf, "[UNIX: localhost]");
		return buf;
I 200
#endif
E 200
D 235
#endif
E 235

E 196
D 147
	if (sap->sa_family == AF_INET)
E 147
I 147
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
D 196
	if (sap->sa.sa_family == AF_INET)
E 196
I 196
	  case AF_INET:
E 196
E 147
D 188
	{
		extern char *inet_ntoa();

E 188
D 263
		return inet_ntoa(((struct sockaddr_in *) sap)->sin_addr);
E 263
I 263
		return inet_ntoa(sap->sin.sin_addr);
E 263
D 188
	}
E 188
I 147
#endif
E 147

I 273
D 274
#ifdef AF_LINK
E 274
I 274
D 286
#ifdef NETLINK
E 286
I 286
#if NETLINK
E 286
E 274
	  case AF_LINK:
		sprintf(buf, "[LINK: %s]",
			link_ntoa((struct sockaddr_dl *) &sap->sa));
		return buf;
#endif
E 273
I 196
	  default:
D 273
	  	/* this case is only to ensure syntactic correctness */
	  	break;
E 273
I 273
		/* this case is needed when nothing is #defined */
		/* in order to keep the switch syntactically correct */
		break;
E 273
	}

E 196
	/* unknown family -- just dump bytes */
D 147
	(void) sprintf(buf, "Family %d: ", sap->sa_family);
E 147
I 147
	(void) sprintf(buf, "Family %d: ", sap->sa.sa_family);
E 147
	bp = &buf[strlen(buf)];
D 147
	ap = sap->sa_u.sa_data;
	for (l = sap->sa_len; --l >= 0; )
E 147
I 147
	ap = sap->sa.sa_data;
	for (l = sizeof sap->sa.sa_data; --l >= 0; )
E 147
	{
		(void) sprintf(bp, "%02x:", *ap++ & 0377);
		bp += 3;
	}
	*--bp = '\0';
	return buf;
E 146
E 115
E 109
E 95
}
I 158
/*
**  HOSTNAMEBYANYADDR -- return name of host based on address
**
**	Parameters:
**		sap -- SOCKADDR pointer
**
**	Returns:
**		text representation of host name.
**
**	Side Effects:
**		none.
*/
E 158
D 95

E 95
I 95

I 158
char *
hostnamebyanyaddr(sap)
	register SOCKADDR *sap;
{
	register struct hostent *hp;
D 196

I 161
#ifdef NAMED_BIND
E 196
	int saveretry;

I 196
D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
E 196
	/* shorten name server timeout to avoid higher level timeouts */
	saveretry = _res.retry;
	_res.retry = 3;
#endif /* NAMED_BIND */

E 161
	switch (sap->sa.sa_family)
	{
D 286
#ifdef NETINET
E 286
I 286
#if NETINET
E 286
	  case AF_INET:
D 260
		hp = gethostbyaddr((char *) &sap->sin.sin_addr,
E 260
I 260
		hp = sm_gethostbyaddr((char *) &sap->sin.sin_addr,
E 260
D 232
			sizeof sap->sin.sin_addr,
E 232
I 232
D 233
			IPADDRSIZE,
E 233
I 233
			INADDRSZ,
E 233
E 232
			AF_INET);
		break;
#endif

D 286
#ifdef NETISO
E 286
I 286
#if NETISO
E 286
	  case AF_ISO:
D 260
		hp = gethostbyaddr((char *) &sap->siso.siso_addr,
E 260
I 260
		hp = sm_gethostbyaddr((char *) &sap->siso.siso_addr,
E 260
			sizeof sap->siso.siso_addr,
			AF_ISO);
I 196
		break;
#endif

D 235
#ifdef MAYBENEXTRELEASE		/*** UNTESTED *** UNTESTED *** UNTESTED ***/
E 235
	  case AF_UNIX:
		hp = NULL;
E 196
		break;
D 235
#endif
E 235

	  default:
D 260
		hp = gethostbyaddr(sap->sa.sa_data,
E 260
I 260
		hp = sm_gethostbyaddr(sap->sa.sa_data,
E 260
			   sizeof sap->sa.sa_data,
			   sap->sa.sa_family);
		break;
	}
I 161

D 217
#ifdef NAMED_BIND
E 217
I 217
#if NAMED_BIND
E 217
	_res.retry = saveretry;
#endif /* NAMED_BIND */
E 161

	if (hp != NULL)
		return hp->h_name;
	else
	{
		/* produce a dotted quad */
		static char buf[512];

		(void) sprintf(buf, "[%s]", anynet_ntoa(sap));
		return buf;
	}
}

E 158
E 95
E 68
D 123
# else DAEMON
E 123
I 123
# else /* DAEMON */
E 123
I 68
/* code for systems without sophisticated networking */
E 68

/*
**  MYHOSTNAME -- stub version for case of no daemon code.
I 53
**
**	Can't convert to upper case here because might be a UUCP name.
I 55
**
**	Mark, you can change this to be anything you want......
E 55
E 53
*/

char **
D 55
myhostname(hostbuf)
E 55
I 55
myhostname(hostbuf, size)
E 55
	char hostbuf[];
I 55
	int size;
E 55
{
	register FILE *f;

	hostbuf[0] = '\0';
	f = fopen("/usr/include/whoami", "r");
	if (f != NULL)
	{
D 55
		(void) fgets(hostbuf, sizeof hostbuf, f);
E 55
I 55
		(void) fgets(hostbuf, size, f);
E 55
		fixcrlf(hostbuf, TRUE);
		(void) fclose(f);
	}
	return (NULL);
I 137
}
/*
D 158
**  GETREALHOSTNAME -- get the real host name asociated with a file descriptor
E 158
I 158
**  GETAUTHINFO -- get the real host name asociated with a file descriptor
E 158
**
**	Parameters:
**		fd -- the descriptor
**
**	Returns:
**		The host name associated with this descriptor, if it can
**			be determined.
**		NULL otherwise.
**
**	Side Effects:
**		none
*/

char *
D 158
getrealhostname(fd)
E 158
I 158
getauthinfo(fd)
E 158
	int fd;
{
	return NULL;
E 137
}
I 68
/*
**  MAPHOSTNAME -- turn a hostname into canonical form
**
**	Parameters:
I 124
**		map -- a pointer to the database map.
E 124
D 175
**		hbuf -- a buffer containing a hostname.
I 163
**		hbsize -- size of hbuf.
E 175
I 175
**		name -- a buffer containing a hostname.
E 175
E 163
D 124
**		hbsize -- the size of hbuf.
E 124
I 115
**		avp -- a pointer to a (cf file defined) argument vector.
I 163
**		statp -- an exit status (out parameter).
E 163
E 115
**
**	Returns:
D 109
**		none.
E 109
I 109
D 115
**		TRUE if the hostname was mapped.
E 115
I 115
**		mapped host name
E 115
**		FALSE otherwise.
E 109
**
**	Side Effects:
D 175
**		Looks up the host specified in hbuf.  If it is not
E 175
I 175
**		Looks up the host specified in name.  If it is not
E 175
**		the canonical name for that host, replace it with
**		the canonical name.  If the name is unknown, or it
**		is already the canonical name, leave it unchanged.
*/

/*ARGSUSED*/
I 109
D 115
bool
E 109
maphostname(hbuf, hbsize)
E 115
I 115
char *
D 124
maphostname(hbuf, hbsize, avp)
E 124
I 124
D 163
maphostname(map, hbuf, hbsize, avp)
E 163
I 163
D 175
maphostname(map, hbuf, hbsize, avp, statp)
E 175
I 175
host_map_lookup(map, name, avp, statp)
E 175
E 163
	MAP *map;
E 124
E 115
D 175
	char *hbuf;
	int hbsize;
E 175
I 175
	char *name;
E 175
I 115
	char **avp;
I 163
	char *statp;
E 163
E 115
{
I 163
	register struct hostent *hp;

D 175
	hp = gethostbyname(hbuf);
E 175
I 175
D 260
	hp = gethostbyname(name);
E 260
I 260
	hp = sm_gethostbyname(name);
E 260
E 175
	if (hp != NULL)
		return hp->h_name;
	*statp = EX_NOHOST;
E 163
D 109
	return;
E 109
I 109
D 115
	return (FALSE);
E 115
I 115
	return NULL;
E 115
E 109
}
D 87

E 87
E 68
E 50

D 123
#endif DAEMON
E 123
I 123
#endif /* DAEMON */
E 123
E 7
E 1
