h52334
s 00004/00001/02399
d D 8.113 95/06/22 07:02:43 eric 294 293
c debugging patches; minor long class name patches
e
s 00004/00000/02396
d D 8.112 95/06/21 18:24:45 eric 293 292
c fix long names on $= $~ and $&
e
s 00001/00001/02395
d D 8.111 95/06/21 10:54:49 eric 292 291
c missing parameter to strtorwset
e
s 00006/00000/02390
d D 8.110 95/06/21 09:26:45 eric 291 290
c better diagnostics on bogus ruleset names
e
s 00001/00000/02389
d D 8.109 95/06/21 07:12:37 eric 290 289
c close passwd file before setuid() "just in case"
e
s 00001/00001/02388
d D 8.108 95/06/21 07:09:54 eric 289 288
c avoid bogus returns in symbolic ruleset names
e
s 00001/00001/02388
d D 8.107 95/06/20 12:15:38 eric 288 287
c allow tabs in P lines
e
s 00001/00001/02388
d D 8.106 95/06/19 18:12:18 eric 287 286
c default scanf on; always use /etc/sendmail.cf regardless of vendor
c preferences
e
s 00004/00004/02385
d D 8.105 95/06/17 10:23:31 eric 286 285
c improved debugging
e
s 00002/00002/02387
d D 8.104 95/06/15 11:35:27 eric 285 284
c change name of NoMXforCanon to HasWildcardMX -- old name was too confusing
e
s 00001/00001/02388
d D 8.103 95/06/12 06:16:40 eric 284 283
c fix inverted debug output
e
s 00014/00010/02375
d D 8.102 95/06/11 06:47:10 eric 283 282
c updates for new DSN drafts
e
s 00007/00000/02378
d D 8.101 95/06/10 18:11:28 eric 282 281
c add DontExpandCnames option -- IETF seems to be moving in this direction
e
s 00005/00000/02371
d D 8.100 95/06/10 12:37:17 eric 281 280
c sample code to set MaxChildren (not now!)
e
s 00008/00001/02363
d D 8.99 95/05/31 08:31:50 eric 280 279
c give warning on duplicate S lines (but append to ruleset anyhow)
e
s 00106/00065/02258
d D 8.98 95/05/30 19:25:18 eric 279 278
c allow symbolic ruleset names on M lines (S= and R=)
e
s 00009/00006/02314
d D 8.97 95/05/30 07:30:58 eric 278 277
c change OA semantics so that all .cf entries are mapped into the
c "files" or "local" alias service type
e
s 00001/00002/02319
d D 8.96 95/05/29 18:13:42 eric 277 276
c fix a comment
e
s 00019/00009/02302
d D 8.95 95/05/28 11:49:51 eric 276 275
c lint
e
s 00006/00000/02305
d D 8.94 95/05/27 09:36:34 eric 275 274
c make the maximum number of jobs in one queue run an option
e
s 00001/00001/02304
d D 8.93 95/05/27 09:07:48 eric 274 273
c clarify comment on T= mailer field
e
s 00001/00001/02304
d D 8.92 95/05/25 11:38:31 eric 273 272
c MD_FREEZE is gone, but MD_INITALIAS is sensitive
e
s 00004/00000/02301
d D 8.91 95/05/15 19:00:26 eric 272 271
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00008/00000/02293
d D 8.90 95/05/15 15:02:08 eric 271 270
c add "E" line to config file to set or propogate environment
c variables to children
e
s 00029/00007/02264
d D 8.89 95/05/14 08:42:52 eric 270 269
c implement Fx|prog and "program" map class
e
s 00006/00000/02265
d D 8.88 95/05/13 15:06:08 eric 269 268
c put getcanonname into service switch
e
s 00011/00009/02254
d D 8.87 95/04/22 14:50:27 eric 268 267
c trim down the number of 8-bit modes to three (m, p, and s)
e
s 00001/00001/02262
d D 8.86 95/04/21 09:57:28 eric 267 266
c update copyright notice
e
s 00005/00000/02258
d D 8.85 95/04/20 08:40:21 eric 266 265
c add Nice=N mailer option
e
s 00014/00000/02244
d D 8.84 95/04/19 10:36:35 eric 265 264
c need to make ColonOkInAddr do something real
e
s 00000/00001/02244
d D 8.83 95/04/19 10:17:58 eric 264 263
c don't need extern long atol() -- done in stdlib.h
e
s 00000/00006/02245
d D 8.82 95/04/10 11:05:11 eric 263 262
c eliminate BrokenSmtpPeers and two line SMTP greeting messages
e
s 00007/00001/02244
d D 8.81 95/04/09 15:53:03 eric 262 261
c add HasWildcardMX suboption to ResolverOptions for special case
e
s 00006/00000/02239
d D 8.80 95/04/09 13:46:35 eric 261 260
c fix handling of group phrase: addr1, addr2, ... addrN; syntax
e
s 00001/00001/02238
d D 8.79 95/04/03 09:31:18 eric 260 259
c clean up problems with MIME 8 to 7 bit conversions
e
s 00002/00002/02237
d D 8.78 95/04/02 09:28:42 eric 259 258
c MIME cleanup to get header line parsing right
e
s 00002/00003/02237
d D 8.77 95/03/31 10:52:08 eric 258 257
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00003/00002/02237
d D 8.76 95/03/26 14:50:18 eric 257 256
c avoid null pointer dereference
e
s 00009/00003/02230
d D 8.75 95/03/21 19:38:21 eric 256 254
c name changes to make the documentation cleaner
e
s 00002/00000/02233
d D 8.74.1.1 95/03/14 18:38:09 eric 255 254
c hacks to make it more IDA-like -- they have other problems
e
s 00003/00003/02230
d D 8.74 95/03/14 09:11:07 eric 254 253
c change call to expand() to be more rational (and consistent!)
e
s 00006/00021/02227
d D 8.73 95/03/10 12:21:59 eric 253 252
c improved security when opening files
e
s 00006/00000/02242
d D 8.72 95/03/05 14:34:03 eric 252 251
c changes suggested by *Hobbit*; SafeFileEnvironment option
e
s 00001/00001/02241
d D 8.71 95/03/05 11:57:15 eric 251 249
i 250
c add "strict" parameter to denlstring to allow continuations
e
s 00001/00000/01658
d D 8.23.1.3 95/03/05 10:35:50 eric 250 243
c fix a problem that would permit people to turn off privacy flags
e
s 00001/00001/02240
d D 8.70 95/02/28 14:43:16 eric 249 248
c incorporate fixes from 8.6.11
e
s 00016/00000/02225
d D 8.69 95/02/24 10:01:02 eric 248 247
c add NoRecipientAction; make Bcc: field truncate instead of delete
e
s 00045/00005/02180
d D 8.68 95/02/20 07:34:00 eric 247 246
c allow symbolic ruleset names
e
s 00013/00021/02172
d D 8.67 95/02/19 13:25:40 eric 246 245
c simplified implementation of new 'T' line
e
s 00007/00007/02186
d D 8.66 95/02/19 07:28:59 eric 245 244
c support for Cray Computer Corp's CSOS
e
s 00001/00001/02192
d D 8.65 95/02/10 09:29:08 eric 244 242
c more security hacking (avoiding bogus newlines in strings)
e
s 00000/00001/01658
d D 8.23.1.2 95/02/10 07:45:05 eric 243 241
c eliminate unnecessary declaration
e
s 00000/00001/02193
d D 8.64 95/02/10 07:44:52 eric 242 240
c eliminate unnecessary declaration
e
s 00000/00000/01659
d D 8.23.1.1 95/02/10 07:37:53 eric 241 199
i 240
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00005/00001/02189
d D 8.63 95/02/10 07:16:46 eric 240 239
c fix security problem: avoid newlines in command line or IDENT input
e
s 00014/00001/02176
d D 8.62 95/02/06 08:06:31 eric 239 238
c give X-Authentication-Warning: on -f flag unless user is trusted
e
s 00039/00006/02138
d D 8.61 95/02/05 08:03:58 eric 238 237
c cut at 20 January version of DSN document
e
s 00015/00000/02129
d D 8.60 95/01/25 11:22:37 eric 237 236
c test for using Hesiod
e
s 00004/00000/02125
d D 8.59 95/01/07 13:29:59 eric 236 235
c always compile IDENTPROTO in; just default the timeout to zero if
c it doesn't normally work on some system.  This is to avoid having
c to recompile sendmail when a kernel patch comes out.
e
s 00009/00000/02116
d D 8.58 95/01/04 16:32:13 eric 235 234
c diagnose unknown options (on a debug flag)
e
s 00001/00007/02115
d D 8.57 94/12/30 07:54:38 eric 234 233
c Timeouts => Timeout
e
s 00001/00001/02121
d D 8.56 94/12/29 08:20:09 eric 233 232
c syntax error fix
e
s 00018/00004/02104
d D 8.55 94/12/29 06:59:28 eric 232 231
c generalize queue order configuration
e
s 00001/00001/02107
d D 8.54 94/12/15 06:28:59 eric 231 230
c compile glitch
e
s 00006/00000/02102
d D 8.53 94/12/05 09:15:44 eric 230 229
c implement DialDelay option
e
s 00001/00001/02101
d D 8.52 94/11/27 15:31:23 eric 229 228
c fix typo
e
s 00025/00013/02077
d D 8.51 94/11/27 15:22:34 eric 228 227
c more DSN hacking
e
s 00042/00000/02048
d D 8.50 94/11/27 11:20:11 eric 227 226
c improved debugging
e
s 00004/00000/02044
d D 8.49 94/11/25 09:06:12 eric 226 225
c improve DSN handling somewhat + some bug fixes
e
s 00001/00001/02043
d D 8.48 94/11/20 20:28:45 eric 225 224
c compile glitches
e
s 00020/00001/02024
d D 8.47 94/11/13 09:52:41 eric 224 223
c set UseNameServer on the basis of whether "dns" is in the service switch
e
s 00107/00053/01918
d D 8.46 94/11/12 18:24:20 eric 223 222
c allow dotted option names
e
s 00004/00000/01967
d D 8.45 94/11/08 11:48:59 eric 222 221
c allow per-mailer default character set (applies to INCOMING mailer)
e
s 00007/00012/01960
d D 8.44 94/10/24 18:32:33 eric 221 220
c first cut at service switch abstraction
e
s 00007/00000/01965
d D 8.43 94/10/17 10:56:25 eric 220 218
c avoid core dumps in rewrite() if the "null RHS" diagnostic is given
e
s 00006/00000/01965
d R 8.43 94/10/17 08:10:34 eric 219 218
c add RewriteEnvelope configuration option
e
s 00020/00002/01945
d D 8.42 94/10/16 20:26:18 eric 218 217
c allow "u" option to take "user:group" as a value
e
s 00001/00001/01946
d D 8.41 94/10/15 09:08:20 eric 217 216
c woops -- typo
e
s 00006/00000/01941
d D 8.40 94/10/15 08:55:41 eric 216 215
c allow option to set default character set for MIME
e
s 00004/00001/01937
d D 8.39 94/10/08 09:22:31 eric 215 214
c fixes for various picky compilers
e
s 00017/00008/01921
d D 8.38 94/09/08 17:57:02 eric 214 213
c prototype long macro name implementation
e
s 00031/00002/01898
d D 8.37 94/08/23 09:10:32 eric 213 212
c allow shortened -O option names
e
s 00009/00001/01891
d D 8.36 94/08/22 08:09:28 eric 212 211
c fix bad diagnosis of null option name
e
s 00019/00005/01873
d D 8.35 94/08/21 15:25:47 eric 211 210
c multiple queue timeouts
e
s 00010/00003/01868
d D 8.34 94/08/20 07:01:28 eric 210 209
c Generalize ReadTimeout option and call it Timeouts; create
c queuereturn, queuewarn, and fileopen timeouts
e
s 00074/00058/01797
d D 8.33 94/08/18 08:22:35 eric 209 208
c add new options for DeliveryNiceness, MinQueueAge, and MaxHostStatAge
e
s 00001/00000/01854
d D 8.32 94/08/07 18:44:49 eric 208 207
c add EightBitMode as long option name
e
s 00001/00001/01853
d D 8.31 94/08/07 16:53:56 eric 207 206
c fix unnecessary dereferences
e
s 00117/00004/01737
d D 8.30 94/08/07 16:15:28 eric 206 205
c allow full-word options
e
s 00000/00001/01741
d D 8.29 94/08/07 13:46:51 eric 205 204
c generalized U= mailer field to cleanly override DefUid
e
s 00054/00000/01688
d D 8.28 94/08/07 12:27:56 eric 204 203
c allow U= flag on mailer to run as specific user id
e
s 00008/00004/01680
d D 8.27 94/07/23 10:12:27 eric 203 202
c tweaks & bug fixes to MIME algorithm
e
s 00034/00001/01650
d D 8.26 94/07/23 07:59:41 eric 202 201
c MIME 8 to 7 bit support
e
s 00000/00003/01651
d D 8.25 94/07/02 05:53:15 eric 201 200
c don't lose .cf syntax errors when Oem set
e
s 00000/00001/01654
d D 8.24 94/06/17 17:40:06 eric 200 199
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00001/00001/01654
d D 8.23 94/03/18 15:30:05 corrigan 199 198
c The 'E' option is not safe
c From: "Michael J. Corrigan" <corrigan@UCSD.EDU>
e
s 00004/00004/01651
d D 8.22 94/03/11 14:41:53 eric 198 197
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00006/00002/01649
d D 8.21 94/02/16 08:46:26 eric 197 196
c clean up debugging in fileclass()
e
s 00006/00000/01645
d D 8.20 94/02/08 08:53:48 eric 196 195
c give specific error message about Fx|... syntax
e
s 00001/00001/01644
d D 8.19 94/01/22 09:00:02 eric 195 194
c improve error message
e
s 00001/00000/01644
d D 8.18 94/01/09 09:00:06 eric 194 193
c allow OITrue without an error message
e
s 00005/00003/01639
d D 8.17 93/12/10 17:20:09 eric 193 192
c add bufsize parameter to prescan
e
s 00002/00000/01640
d D 8.16 93/11/26 18:43:14 eric 192 191
c don't auto-append . to domain names if running without DNS
e
s 00003/00001/01637
d D 8.15 93/11/20 06:53:22 eric 191 190
c diagnose unrecognized I options
e
s 00002/00002/01636
d D 8.14 93/10/31 11:29:46 eric 190 188
c SafeAlias is an interval, not an integer
e
s 00001/00001/01637
d R 8.14 93/10/21 12:28:53 eric 189 188
c consider option "c" to be safe
e
s 00019/00003/01619
d D 8.13 93/10/15 08:34:48 eric 188 187
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00018/00002/01604
d D 8.12 93/09/05 14:53:09 eric 187 186
c diagnose bad V and S lines
e
s 00001/00006/01605
d D 8.11 93/08/21 16:36:23 eric 186 185
c debugging output changes
e
s 00007/00000/01604
d D 8.10 93/08/16 15:24:34 eric 185 184
c fix $w setting to be true short name
e
s 00004/00000/01600
d D 8.9 93/08/14 19:14:30 eric 184 183
c add TimeOuts.to_ident to set IDENT protocol timeout
e
s 00002/00001/01598
d D 8.8 93/08/07 13:25:35 eric 183 182
c only let command line -oL flag raise (never lower) logging level
e
s 00053/00011/01546
d D 8.7 93/08/07 11:50:17 eric 182 181
c allow u and g options to take user and group names respectively
e
s 00002/00001/01555
d D 8.6 93/08/06 21:17:18 eric 181 180
c expand C lines so that $X can work
e
s 00002/00001/01554
d D 8.5 93/07/29 08:31:44 eric 180 179
c don't call newstr() macro with arguments with subroutine calls, since
c it double-evaluates
e
s 00018/00006/01537
d D 8.4 93/07/28 09:05:40 eric 179 178
c map debugging
e
s 00004/00002/01539
d D 8.3 93/07/16 10:24:48 eric 178 176
c add 'w' option
e
s 00087/00001/01540
d D 8.2.1.1 93/07/14 15:24:41 eric 177 176
c early implementation of extended option support
e
s 00004/00004/01537
d D 8.2 93/07/13 12:58:39 eric 176 175
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00002/00002/01539
d D 8.1 93/06/07 10:31:44 bostic 175 174
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/01541
d D 6.43 93/06/05 17:08:03 eric 174 173
c lint-style cleanup
e
s 00010/00000/01532
d D 6.42 93/06/03 19:12:13 eric 173 172
c only use Errors-To: header if 'l' option is set
e
s 00002/00004/01530
d D 6.41 93/05/28 07:12:32 eric 172 171
c defer map open as long as possible
e
s 00000/00003/01534
d D 6.40 93/05/27 11:37:37 eric 171 170
c prototype functions
e
s 00004/00002/01533
d D 6.39 93/05/21 20:29:46 eric 170 169
c cleanup for NIS maps
e
s 00003/00003/01532
d D 6.38 93/05/21 18:58:07 eric 169 168
c changes to merge alias and map implementations
e
s 00003/00002/01532
d D 6.37 93/05/17 10:28:20 eric 168 167
c first cut at merged map/alias implementation
e
s 00001/00001/01533
d D 6.36 93/05/13 09:27:54 eric 167 166
c fix parsing of split header/envelope rewriting rules
e
s 00001/00001/01533
d D 6.35 93/05/04 18:49:03 eric 166 165
c fix a wierdness on handling -o override options
e
s 00005/00001/01529
d D 6.34 93/05/04 15:45:11 eric 165 164
c update for MIME encapsulated error messages
e
s 00002/00002/01528
d D 6.33 93/05/03 19:12:08 eric 164 163
c change option 8 to option 7 (and invert semantics)
e
s 00003/00003/01527
d D 6.32 93/05/03 12:26:24 eric 163 162
c first cut at updated alias implementation
e
s 00000/00001/01530
d D 6.31 93/04/27 18:51:44 eric 162 161
c move #include <sys/stat.h> into conf.h
e
s 00000/00011/01531
d D 6.30 93/04/27 17:24:26 eric 161 160
c move compatibility hooks for S_ISREG et al to conf.h
e
s 00007/00001/01535
d D 6.29 93/04/26 14:42:33 eric 160 159
c extend "b" option to include maximum message size
e
s 00018/00021/01518
d D 6.28 93/04/26 13:13:21 eric 159 158
c clean up handling of F line
e
s 00004/00000/01535
d D 6.27 93/04/21 12:52:45 eric 158 157
c patches to XLA code
e
s 00006/00000/01529
d D 6.26 93/04/18 10:07:22 eric 157 156
c Extended Load Average (XLA) hooks
e
s 00004/00000/01525
d D 6.25 93/04/03 07:20:08 eric 156 155
c add Directory mailer field
e
s 00002/00000/01523
d D 6.24 93/03/30 18:04:04 eric 155 154
c diagnose bogus privacy flags
e
s 00008/00000/01515
d D 6.23 93/03/29 12:44:33 eric 154 153
c O (set daemon options) and V (fallback MX host) options
e
s 00000/00001/01515
d D 6.22 93/03/26 08:06:45 eric 153 152
c MATCHZERO doesn't assign a $N value
e
s 00005/00005/01511
d D 6.21 93/03/23 19:50:55 eric 152 151
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00002/00000/01514
d D 6.20 93/03/23 18:06:39 eric 151 150
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00007/00001/01507
d D 6.19 93/03/19 11:46:38 eric 150 149
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00007/00005/01501
d D 6.18 93/03/19 08:50:56 eric 149 148
c move SendMode and ErrorMode into the envelope
e
s 00001/00000/01505
d D 6.17 93/03/14 08:29:51 eric 148 147
c compile warning cleanups
e
s 00013/00013/01492
d D 6.16 93/03/01 12:43:59 eric 147 146
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00000/00001/01505
d D 6.15 93/03/01 06:53:42 eric 146 145
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00012/00000/01494
d D 6.14 93/02/28 19:47:29 eric 145 144
c check for A= and P= arguments
e
s 00001/00004/01493
d D 6.13 93/02/24 09:12:37 eric 144 143
c allow $@ on LHS to indicate match zero tokens
e
s 00001/00021/01496
d D 6.12 93/02/23 14:45:28 eric 143 142
c delete trusted users code; it's too easy to circumvent
e
s 00098/00005/01419
d D 6.11 93/02/22 17:04:15 eric 142 141
c add R flag (don't prune route-addrs); improve diagnostic checks
e
s 00101/00001/01323
d D 6.10 93/02/21 09:56:17 eric 141 140
c generalize read timeout
e
s 00031/00001/01293
d D 6.9 93/02/20 13:46:43 eric 140 139
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00031/00029/01263
d D 6.8 93/02/18 20:22:32 eric 139 138
c move the meta-characters from C0 into C1 space
e
s 00020/00003/01272
d D 6.7 93/02/16 18:30:04 eric 138 137
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00002/00004/01273
d D 6.6 93/02/12 11:51:23 eric 137 136
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00011/00000/01266
d D 6.5 93/01/28 10:15:49 eric 136 135
c System 5 compatibility, misc fixes
e
s 00037/00000/01229
d D 6.4 93/01/18 14:32:23 eric 135 134
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00001/00000/01228
d D 6.3 93/01/10 12:56:49 eric 134 133
c MX piggybacking, based on code from John Myers@CMU; allow checkcompat
c to return -1 to mean tempfail; bug fix in m_mno computation
e
s 00011/00004/01217
d D 6.2 93/01/02 14:00:04 eric 133 132
c changes to recognize special mailer types (e.g., file) early
e
s 00000/00000/01221
d D 6.1 92/12/21 16:08:46 eric 132 131
c Release 6
e
s 00066/00001/01155
d D 5.55 92/12/18 10:06:37 eric 131 130
c allow I option to arbitrarily set and clear resolver options
e
s 00000/00004/01156
d D 5.54 92/12/15 17:17:32 eric 130 129
c restore # as comment symbol in .forward/:include:; extend -p flag;
c remove = option (use V instead)
e
s 00005/00001/01155
d D 5.53 92/12/15 13:24:07 eric 129 128
c J option sets "search path" for .forward
e
s 00032/00025/01124
d D 5.52 92/12/15 12:34:52 eric 128 127
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00008/00005/01141
d D 5.51 92/12/11 15:01:01 eric 127 126
c don't auto-initialize host map if user has already done it
e
s 00006/00000/01140
d D 5.50 92/11/15 19:24:45 eric 126 125
c allow specification of arbitrary string on successful db match
e
s 00001/00001/01139
d D 5.49 92/11/15 16:11:02 eric 125 124
c finish support for generalized maps
e
s 00005/00005/01135
d D 5.48 92/11/14 11:34:28 eric 124 123
c (partially) ANSI-fy it
e
s 00004/00000/01136
d D 5.47 92/11/04 12:14:56 eric 123 122
c fix a variety of small bugs noticed by bcx
e
s 00002/00002/01134
d D 5.46 92/09/09 06:56:43 eric 122 121
c miscellaneous bug fixes from Bryan Costales and Craig Lant
e
s 00001/00001/01135
d D 5.45 92/07/20 08:03:11 eric 121 120
c portability changes
e
s 00001/00001/01135
d D 5.44 92/07/19 14:47:09 eric 120 119
c option E has to be in a safe environment; otherwise you could point
c at a file that you can't otherwise read
e
s 00002/00001/01134
d D 5.43 92/07/19 14:45:22 eric 119 118
c OE is the same as omitting it
e
s 00004/00000/01131
d D 5.42 92/07/19 14:26:14 eric 118 117
c finish uid_t/gid_t conversion; allow locally customized message for
c prepending to all error returns
e
s 00007/00005/01124
d D 5.41 92/07/12 14:09:50 eric 117 116
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00028/00013/01101
d D 5.40 92/07/12 06:59:40 eric 116 115
c security hacks: make F .cf line a little more careful; don't
c close more than 256 files
e
s 00011/00001/01103
d D 5.39 92/07/11 18:51:46 eric 115 114
c open connection caching
e
s 00004/00000/01100
d D 5.38 92/05/29 10:38:40 eric 114 113
c allow configuration of GECOS matching; do regular aliasing after
c a GECOS match
e
s 00075/00000/01025
d D 5.37 92/05/25 13:13:40 eric 113 112
c add generalized database mapping (using the K config line and
c $( ... $) syntaxes); $[ ... $] is now a special case
e
s 00001/00001/01024
d D 5.36 92/05/10 07:15:10 eric 112 111
c make C option safe; output values of $r and $s macros to qf; allow
c long messages in queue files
e
s 00008/00001/01017
d D 5.35 92/03/20 22:33:05 eric 111 110
c reject connections more quickly if load average goes up;
c try to time out on opens of .forward files on hung filesystems
e
s 00054/00004/00964
d D 5.34 92/02/24 21:15:45 eric 110 109
c allow on-line comments; don't double-parse RCPT To: addresses;
c warn on truncated lines; do some sanity checks on .cf file descriptor
e
s 00005/00000/00963
d D 5.33 92/02/24 16:11:46 eric 109 108
c add new 'V' config line to control configuration syntax version
e
s 00012/00002/00951
d D 5.32 92/02/21 20:57:54 eric 108 107
c from Bryan Costales: several smallish changes, mostly to clean
c up debugging output.  The major change is that test mode (-bt)
c doesn't automatically run through ruleset three any more.
e
s 00018/00007/00935
d D 5.31 92/01/04 15:33:15 eric 107 106
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00008/00002/00934
d D 5.30 91/12/24 10:18:43 eric 106 105
c allow F config line to open a pipe
e
s 00001/00001/00935
d D 5.29 91/10/11 12:46:05 eric 105 104
c fixes for user database and new config files
e
s 00004/00000/00932
d D 5.28 91/10/05 10:04:25 eric 104 103
c add "config level" config parameter
e
s 00006/00006/00926
d D 5.27 91/10/03 14:38:59 eric 103 102
c some changes to enhance compatibility with SunOS sendmail
e
s 00002/00002/00930
d D 5.26 91/10/02 12:59:37 eric 102 101
c reverse sense of w (wildcard MX) flag to default to the safest option,
c instead of the most desirable option.
e
s 00003/00002/00929
d D 5.25 91/09/30 14:28:18 eric 101 100
c fix some debugging output
e
s 00004/00000/00927
d D 5.24 91/07/26 09:34:38 eric 100 99
c hooks for distributed user database system
e
s 00004/00000/00923
d D 5.23 91/07/25 11:12:27 eric 99 98
c some compatibility with SunOS for future work here at Berkeley;
c change NO_WILDCARD_MX compilation flag to configuration option "w".
e
s 00004/00000/00919
d D 5.22 91/03/12 17:31:19 eric 98 97
c k option specifies checkpoint interval (default 10);
c qf file is rewritten after k successful deliveries.
c (ref bug 4.3BSD-reno/usr.bin/10)
e
s 00001/00011/00918
d D 5.21 90/06/01 19:03:08 bostic 97 96
c new copyright notice
e
s 00001/00000/00928
d D 5.20 90/04/18 13:54:02 bostic 96 95
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00001/00001/00927
d D 5.19 89/09/11 08:14:00 rick 95 94
c add missing () to test in if statement to correctly accept -oM[rs]
e
s 00009/00006/00919
d D 5.18 89/01/19 15:12:44 bostic 94 93
c allow -oMr and -oMs; rmail wishes to set them
e
s 00000/00011/00925
d D 5.17 89/01/01 17:17:43 bostic 93 92
c remove DEBUG
e
s 00000/00013/00936
d D 5.16 88/12/28 20:33:19 bostic 92 91
c WIZ vanishes
e
s 00002/00002/00947
d D 5.15 88/11/18 16:33:30 karels 91 90
c getruid uses unitialized var, use getuid (even though -bd is now privileged)
e
s 00004/00000/00945
d D 5.14 88/09/20 22:15:24 eric 90 89
c add I option to insist on Internet domain server; add NAMED_BIND
c compile option to compile in named routines.
e
s 00011/00009/00934
d D 5.13 88/06/30 14:59:29 bostic 89 88
c install approved copyright notice
e
s 00001/00009/00942
d D 5.12 88/04/01 16:50:58 bostic 88 87
c remove V6 #ifdefs
e
s 00016/00010/00935
d D 5.11 88/03/13 19:52:50 bostic 87 86
c add Berkeley specific header
e
s 00004/00000/00941
d D 5.10 86/01/11 00:18:01 eric 86 85
c only check the RHS of aliases during newalias if the "n" option is set;
c this option should probably be set if you are not running the nameserver
e
s 00033/00003/00908
d D 5.9 86/01/10 15:49:22 eric 85 84
c allow multiple words per line in file classes; require a SCANF compilation
c flag to use sscanf in F specs in order to reduce image size
e
s 00009/00003/00902
d D 5.8 86/01/05 19:57:07 eric 84 83
m 
c cleanup for various compilation flags and reasonable organization
e
s 00001/00001/00904
d D 5.7 85/12/07 08:17:13 eric 83 82
m 
c several small bugs: don't die if no environment, don't look in
c ESM_DEADLETTER state in savemail; lowercase before getpwnam to
c allow upper case regular names in alias file
e
s 00013/00001/00892
d D 5.6 85/09/21 14:44:36 eric 82 81
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00004/00000/00889
d D 5.5 85/09/19 12:18:01 eric 81 80
m 
c 'z' option now sets ForkQueueRuns
e
s 00000/00000/00889
d D 5.4 85/09/19 01:26:00 eric 80 78
i 79
m 
c incorporate SMI changes -- still experimental
e
s 00014/00004/00875
d D 5.3.1.1 85/09/19 00:56:23 eric 79 78
m 
c SMI changes (somewhat)
e
s 00003/00003/00876
d D 5.3 85/06/08 00:49:12 eric 78 77
m 
c lint
e
s 00000/00002/00879
d D 5.2 85/06/07 22:15:56 miriam 77 76
m 
c Resolve duplicate SccsId
e
s 00014/00000/00867
d D 5.1 85/06/07 15:09:07 dist 76 75
m 
c Add copyright
e
s 00015/00017/00852
d D 4.13 85/06/02 10:54:29 eric 75 74
x 74
m 
c plug another security hole with command line arguments
e
s 00006/00031/00838
d D 4.12 85/05/24 11:03:02 eric 74 73
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00011/00005/00858
d D 4.11 85/02/15 09:27:53 eric 73 72
m 
c fix some bugs with -C flag; one with queuing from Teus
e
s 00001/00001/00862
d D 4.10 85/02/14 22:43:17 eric 72 71
m 
c "and" file mode bits with 0777
e
s 00019/00011/00844
d D 4.9 84/12/05 23:16:04 eric 71 70
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00003/00002/00852
d D 4.8 84/08/11 23:21:13 eric 70 69
m 
c Add $[ and $] as RHS operators to look up the contents and pass them
c to maphostname; maphostname currently looks them up in /etc/hosts and
c converts them to canonical form, but could be turned into a general
c name server.....   huzzah!!
e
s 00001/00001/00853
d D 4.7 84/08/11 16:57:26 eric 69 68
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00003/00002/00851
d D 4.6 84/08/11 14:37:25 eric 68 67
m 
c allow multiple -M flags -- fix from Liudvikas Bukys
e
s 00006/00000/00847
d D 4.5 84/08/05 11:01:06 eric 67 65
m 
c add B option to set blank substitution character
e
s 00000/00000/00847
d R 4.4.1.1 84/06/17 16:18:47 eric 66 65
m 
c abortive attempt to install a name server.... sigh.
e
s 00018/00000/00829
d D 4.4 84/03/11 16:56:28 eric 65 64
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00007/00000/00822
d D 4.3 84/03/11 16:12:36 eric 64 63
m 
c make network name configurable
e
s 00010/00000/00812
d D 4.2 83/08/28 14:45:50 eric 63 62
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00000/00000/00812
d D 4.1 83/07/25 19:47:11 eric 62 61
m 
c 4.2 release version
e
s 00000/00009/00812
d D 3.59 83/07/13 10:38:29 eric 61 60
m 
c Delete "load limiting" for SMTP connections (a bad ethernet board can
c hang up all incoming mail); use sfgets in collect (same reason); check
c for I/O error in collect (from Bill Nowicki); switch date format to
c RFC822 style.
e
s 00001/00000/00820
d D 3.58 83/05/21 11:01:14 eric 60 59
m 
c Miscellaneous changes for PDP-11's.
c Always send to a login name before a full name.
e
s 00000/00001/00820
d D 3.57 83/04/30 15:15:27 eric 59 58
m 
c lint
e
s 00006/00004/00815
d D 3.56 83/02/08 10:49:54 eric 58 57
m 167
m 172
m 173
m 174
c clean up problems when QUEUE compile flag not defined; clean up hostname
c code to run on non-4.1c systems; fix use of -oeq (quiet on errors) flag.
e
s 00002/00001/00817
d D 3.55 83/02/03 10:29:38 eric 57 56
m 160
c $e macro is now SMTP entry message (so that configuration version can
c be included).
e
s 00005/00000/00813
d D 3.54 83/02/03 07:54:21 eric 56 55
m 168
c Make mailer size limits a per-mailer parameter (M field in the mailer
c descriptor)
e
s 00034/00126/00779
d D 3.53 83/02/02 12:53:58 eric 55 54
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00001/00001/00904
d D 3.52 83/01/17 12:32:10 eric 54 53
m 155
c fix bug that caused "\r\n" string in TCP mailer definition to turn
c into something else -- causing all TCP connections to hang.
e
s 00009/00000/00896
d D 3.51 83/01/16 17:27:43 eric 53 52
m 153
c make the maximum number of simultaneous SMTP connections an option
e
s 00189/00073/00707
d D 3.50 83/01/16 13:14:31 eric 52 51
m 152
c Change mailer spec to have labelled fields for future expansion.
c **** This delta invalidates previous configuration files ****
e
s 00017/00014/00763
d D 3.49 83/01/06 10:48:15 eric 51 50
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00057/00092/00720
d D 3.48 82/11/28 00:23:43 eric 50 49
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00002/00001/00810
d D 3.47 82/11/24 18:45:00 eric 49 48
m 
c lint it
e
s 00011/00004/00800
d D 3.46 82/11/24 17:16:40 eric 48 47
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00001/00000/00803
d D 3.45 82/11/21 17:19:34 eric 47 46
m 026
c preliminary hacks for multiple SMTP transactions per connection: make
c assignment of multiple queue id's more efficient, make prefixes two
c characters (e.g., qfAA99999), pass the file name to freeze and thaw,
c add a mailer flag saying we are talking to one of our own kind.
e
s 00013/00028/00790
d D 3.44 82/11/17 09:37:27 eric 46 45
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00005/00003/00813
d D 3.43 82/11/14 12:26:07 eric 45 44
m 072
c Don't give an error message on unknown options
e
s 00008/00001/00808
d D 3.42 82/11/13 17:56:17 eric 44 43
m 066,
m 069
c require an option to do auto-rebuild of alias database; allow new
c operation modes to replace old ad hoc flags
e
s 00006/00009/00803
d D 3.41 82/11/07 15:32:04 eric 43 42
m 063
c don't flag errors in setting dangerous options when -C is used
e
s 00006/00000/00806
d D 3.40 82/11/03 10:29:45 eric 42 41
m 058
c Put temporary file mode on the F option
e
s 00005/00005/00801
d D 3.39 82/10/28 17:41:39 eric 41 40
m 039,
m 027
c Put the "@:@" trick on the "a" option.  Also, move TrustedUsers into
c sendmail.h (it should have gone here in the first place!)
e
s 00054/00005/00752
d D 3.38 82/10/16 15:25:05 eric 40 39
m 027
c Put list of login names able to use -f in the .cf file.
e
s 00010/00001/00747
d D 3.37 82/10/16 14:44:04 eric 39 38
m 007
c Arrange for a wizards password (the W option).  The SMTP KILL command
c may only be issued if this option is set.  This delta adds the "WIZ"
c command, and changes _KILL => KILL, _DEBUG => DEBUG, _VERBOSE => VERB,
c and _SHOWQ => SHOWQ.
e
s 00001/00000/00747
d D 3.36 82/10/06 11:46:07 eric 38 37
c add test mode (MD_TEST, -bt)
e
s 00131/00007/00616
d D 3.35 82/09/26 17:04:39 eric 37 36
c Put more configuration into setoption; merge some of the argv processing
c with this; move configuration information out of conf.c into the .cf
c file.  Since a lot of stuff will default to zero, a new .cf file is
c required.
e
s 00019/00011/00604
d D 3.34 82/09/26 14:46:21 eric 36 35
c completely instantiate queue files for all mail, even if not needed;
c fix a bug that would probably come up once every ten years in creating
c the queue id.  should merge argv flag processing with option processing.
e
s 00104/00004/00511
d D 3.33 82/09/24 19:39:33 eric 35 34
c change option implementation; define a bunch of interesting options.
e
s 00030/00003/00485
d D 3.32 82/09/24 09:38:47 eric 34 33
c arrange to be able to define options; put precedences in .cf file;
c send errors to an Errors-To: field; fix a serious bug causing mail
c to not be delivered to anyone if there were any errors.
e
s 00001/00000/00487
d D 3.31 82/09/12 16:44:10 eric 33 32
c change inheritance for macros in envelopes; be able to canonicalize
c non-domained names by appending domain from sender; call ruleset 3
c explicitly before doing other rulesets; some general cleanup.
e
s 00021/00024/00466
d D 3.30 82/09/05 18:05:59 eric 32 31
c change $g rewriting to two rewriting rulesets per mailer; tune debugging
e
s 00015/00007/00475
d D 3.29 82/09/05 11:46:04 eric 31 30
c put line numbers on error messages; increase max number of rewriting
c sets; improve diagnostics in several places
e
s 00001/00008/00481
d D 3.28 82/08/23 09:24:05 eric 30 29
c allow continuation lines in .cf file (particularly in headers)
e
s 00006/00001/00483
d D 3.27 82/06/19 21:09:24 eric 29 28
c get rid of comment lines when storing rewriting rules
e
s 00001/00001/00483
d D 3.26 82/05/31 18:50:31 eric 28 27
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00000/00000/00484
d D 3.25 82/05/31 15:32:45 eric 27 26
i 25
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00001/00000/00483
d D 3.24 82/05/30 10:25:28 eric 26 24
c add M_FULLSMTP (``X'' flag in .cf file) for eventual implementation
c of full SMTP.  This version must support such garbage as line limits,
c address length limits, return-path, etc.
e
s 00002/00002/00481
d D 3.23.1.1 82/05/29 18:20:53 eric 25 24
c try to install envelopes.  is this really worth it???
e
s 00001/00000/00482
d D 3.23 82/05/15 12:29:41 eric 24 23
c add the 'R' flag to mailers, saying to rewrite the recipient addresses
c to be relative to the recipient.  This makes reply code easy, but
c confuses user mail programs that are expecting to have to rewrite
c recipient addresses.  In general, the receiving host must be "smart"
c for this to work.
e
s 00003/00003/00479
d D 3.22 82/03/20 16:12:52 eric 23 22
c 16 bit changes -- should have no effect on VAX binaries to
c speak of.
e
s 00029/00020/00453
d D 3.21 82/02/20 13:00:21 eric 22 21
c expand macros in rewriting rules early to allow multi-word macros to
c be processed correctly.
e
s 00001/00000/00472
d D 3.20 82/02/20 12:10:24 eric 21 20
c implement -c flag: don't try to deliver expensive mail immediately
e
s 00001/00000/00471
d D 3.19 82/01/23 14:19:28 eric 20 19
c add M_UGLYUUCP flag for ugly from line
e
s 00001/00001/00470
d D 3.18 81/12/06 12:39:52 eric 19 18
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00000/00001/00471
d D 3.17 81/11/21 18:43:35 eric 18 17
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00039/00006/00433
d D 3.16 81/10/26 14:22:59 eric 17 16
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00004/00000/00435
d D 3.15 81/09/24 10:31:06 eric 16 15
c changes to work under a V6 system -- mostly compilation flags
e
s 00085/00001/00350
d D 3.14 81/09/23 09:52:26 eric 15 14
c fix bug in file modes when mailing to files that didn't exist before;
c add an 'F' line to the .cf file that will read class entries from
c another file, given a scanf string to do the parsing.
e
s 00006/00002/00345
d D 3.13 81/09/06 19:49:15 eric 14 13
c cleanup, commenting, linting, etc.
e
s 00012/00003/00335
d D 3.12 81/08/23 12:09:10 eric 13 12
c plug assorted security holes
e
s 00001/00002/00337
d D 3.11 81/08/21 18:18:49 eric 12 11
c drop M_FINAL, change some other defined constant names
e
s 00000/00002/00339
d D 3.10 81/08/20 15:14:44 eric 11 10
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00001/00000/00340
d D 3.9 81/08/17 09:37:54 eric 10 9
c add header fields from new BB&N proposal ICST/CBOS - 80-2,
c "Specification of a Draft Message Format Standard" for NBS.
e
s 00001/00001/00339
d D 3.8 81/08/10 16:57:31 eric 9 8
c totally rework aliasing scheme -- sucks when no DBM now,
c but works better for the usual case; fix some quoting problems
c (and how many did I add?); remove .mailer feature since .forward
c will simulate this happily
e
s 00154/00004/00186
d D 3.7 81/08/09 19:08:47 eric 8 7
c put mailer definitions into configuration file
e
s 00005/00103/00185
d D 3.6 81/08/09 15:03:41 eric 7 6
c lint it
e
s 00032/00015/00256
d D 3.5 81/08/08 17:48:05 eric 6 5
c add another set of rewrite rules to process From: address;
c this will allow generalized from address processing in an
c internet
e
s 00034/00000/00237
d D 3.4 81/08/08 11:18:07 eric 5 4
c add word classes
e
s 00001/00001/00236
d D 3.3 81/03/28 14:18:24 eric 4 3
c don't throw away some headers
e
s 00004/00000/00233
d D 3.2 81/03/28 12:03:01 eric 3 2
c put much more info in cf file (e.g., headers)
e
s 00001/00001/00232
d D 3.1 81/03/20 09:45:32 eric 2 1
c change name (again); from postbox to sendmail
e
s 00233/00000/00000
d D 1.1 81/03/20 09:39:01 eric 1 0
c date and time created 81/03/20 09:39:01 by eric
e
u
U
f b 
f i 
t
T
I 76
/*
I 89
D 267
 * Copyright (c) 1983 Eric P. Allman
E 267
I 267
 * Copyright (c) 1983, 1995 Eric P. Allman
E 267
E 89
D 87
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 87
I 87
D 175
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 175
I 175
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 175
 *
D 97
 * Redistribution and use in source and binary forms are permitted
D 89
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 89
I 89
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
E 97
I 97
 * %sccs.include.redist.c%
E 97
E 89
 */
E 87

#ifndef lint
D 87
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 87
I 87
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 87

E 76
I 1
D 11
# include <stdio.h>
E 11
D 2
# include "postbox.h"
E 2
I 2
# include "sendmail.h"
I 182
D 258
# include <pwd.h>
E 258
# include <grp.h>
E 182
I 110
D 162
# include <sys/stat.h>
E 162
I 116
D 146
# include <unistd.h>
E 146
I 131
D 198
#ifdef NAMED_BIND
E 198
I 198
#if NAMED_BIND
E 198
D 200
# include <arpa/nameser.h>
E 200
# include <resolv.h>
#endif
E 131
E 116
E 110
E 2
D 11
# include <ctype.h>
E 11

I 136
D 161
/* System 5 compatibility */
#ifndef S_ISREG
#define S_ISREG(foo)	((foo & S_IFREG) == S_IFREG)
#endif
#ifndef S_IWGRP
#define S_IWGRP		020
#endif
#ifndef S_IWOTH
#define S_IWOTH		002
#endif

E 161
E 136
D 19
static char SccsId[] = "%W%	%G%";
E 19
I 19
D 77
SCCSID(%W%	%Y%	%G%);
E 19

E 77
/*
**  READCF -- read control file.
**
**	This routine reads the control file and builds the internal
**	form.
**
I 15
**	The file is formatted as a sequence of lines, each taken
**	atomically.  The first character of each line describes how
**	the line is to be interpreted.  The lines are:
**		Dxval		Define macro x to have value val.
**		Cxword		Put word into class x.
**		Fxfile [fmt]	Read file for lines to put into
**				class x.  Use scanf string 'fmt'
**				or "%s" if not present.  Fmt should
**				only produce one string-valued result.
**		Hname: value	Define header with field-name 'name'
**				and value as specified; this will be
**				macro expanded immediately before
**				use.
**		Sn		Use rewriting set n.
**		Rlhs rhs	Rewrite addresses that match lhs to
**				be rhs.
D 34
**		Mn p f r a	Define mailer.  n - internal name,
**				p - pathname, f - flags, r - rewriting
**				rule for sender, a - argument vector.
E 34
I 34
D 79
**		Mn p f s r a	Define mailer.  n - internal name,
**				p - pathname, f - flags, s - rewriting
**				ruleset for sender, s - rewriting ruleset
**				for recipients, a - argument vector.
E 79
I 79
**		Mn arg=val...	Define mailer.  n is the internal name.
**				Args specify mailer parameters.
E 79
**		Oxvalue		Set option x to value.
**		Pname=value	Set precedence name to value.
I 109
D 188
**		Vversioncode	Version level of configuration syntax.
E 188
I 188
**		Vversioncode[/vendorcode]
**				Version level/vendor name of
**				configuration syntax.
E 188
I 113
**		Kmapname mapclass arguments....
**				Define keyed lookup of a given class.
**				Arguments are class dependent.
I 271
**		Eenvar=value	Set the environment value to the given value.
E 271
E 113
E 109
E 34
**
E 15
**	Parameters:
**		cfname -- control file name.
I 116
**		safe -- TRUE if this is the system config file;
**			FALSE otherwise.
I 117
**		e -- the main envelope.
E 117
E 116
I 13
D 74
D 75
**		safe -- set if this is a system configuration file.
**			Non-system configuration files can not do
**			certain things (e.g., leave the SUID bit on
**			when executing mailers).
E 75
E 74
E 13
**
**	Returns:
**		none.
**
**	Side Effects:
**		Builds several internal tables.
*/

I 276
void
E 276
I 40
D 41
# define MAXTRUST	10		/* maximum number of trusted users */

char	*TrustedUsers[MAXTRUST+1];	/* list of trusted users */

E 41
E 40
D 6
struct rewrite	*RewriteRules;
E 6
I 6
D 31
struct rewrite	*RewriteRules[10];
E 6


E 31
D 13
readcf(cfname)
E 13
I 13
D 74
D 75
readcf(cfname, safe)
E 75
I 75
D 116
readcf(cfname)
E 116
I 116
D 117
readcf(cfname, safe)
E 117
I 117
readcf(cfname, safe, e)
E 117
E 116
E 75
E 74
I 74
readcf(cfname)
E 74
E 13
	char *cfname;
I 116
	bool safe;
I 117
	register ENVELOPE *e;
E 117
E 116
I 13
D 74
D 75
	bool safe;
E 75
E 74
E 13
{
	FILE *cf;
I 40
D 55
	int class;
E 55
	int ruleset = 0;
I 247
D 279
	int nextruleset = MAXRWSETS;
E 279
E 247
	char *q;
D 174
	char **pv;
E 174
I 49
	struct rewrite *rwp = NULL;
I 128
	char *bp;
I 188
	auto char *ep;
E 188
I 135
	int nfuzzy;
I 182
	char *file;
	bool optional;
I 214
	int mid;
E 214
E 182
E 135
E 128
E 49
E 40
	char buf[MAXLINE];
	register char *p;
D 49
	struct rewrite *rwp = NULL;
E 49
D 7
	extern char *xalloc();
E 7
D 171
	extern char **prescan();
E 171
	extern char **copyplist();
I 110
	struct stat statb;
E 110
D 7
	extern char *rindex();
	extern char *newstr();
E 7
I 5
D 40
	int class;
I 6
	int ruleset = 0;
E 40
I 22
	char exbuf[MAXLINE];
I 70
D 193
	char pvpbuf[PSBUFSIZE];
E 193
I 193
	char pvpbuf[MAXLINE + MAXATOM];
I 220
	static char *null_list[1] = { NULL };
E 220
E 193
E 70
I 49
D 171
	extern char *fgetfolded();
E 171
I 57
D 276
	extern char *munchstring();
I 113
	extern void makemapentry();
E 276
I 276
	extern char *munchstring __P((char *, char **));
	extern void fileclass __P((int, char *, char *, bool, bool));
	extern void toomany __P((int, int));
E 276
E 113
E 57
E 49
I 29
D 40
	char *q;
E 40
E 29
E 22
E 6
E 5

I 110
	FileName = cfname;
	LineNumber = 0;

E 110
	cf = fopen(cfname, "r");
	if (cf == NULL)
	{
D 110
		syserr("cannot open %s", cfname);
E 110
I 110
		syserr("cannot open");
E 110
		exit(EX_OSFILE);
	}

I 50
D 110
	FileName = cfname;
E 50
I 31
	LineNumber = 0;
E 110
I 110
	if (fstat(fileno(cf), &statb) < 0)
	{
		syserr("cannot fstat");
		exit(EX_OSFILE);
	}

	if (!S_ISREG(statb.st_mode))
	{
		syserr("not a plain file");
		exit(EX_OSFILE);
	}

	if (OpMode != MD_TEST && bitset(S_IWGRP|S_IWOTH, statb.st_mode))
	{
D 111
		syserr("WARNING: dangerous write permissions");
E 111
I 111
D 273
		if (OpMode == MD_DAEMON || OpMode == MD_FREEZE)
E 273
I 273
		if (OpMode == MD_DAEMON || OpMode == MD_INITALIAS)
E 273
			fprintf(stderr, "%s: WARNING: dangerous write permissions\n",
				FileName);
#ifdef LOG
		if (LogLevel > 0)
			syslog(LOG_CRIT, "%s: WARNING: dangerous write permissions",
				FileName);
#endif
E 111
	}

I 158
#ifdef XLA
	xla_zero();
#endif

E 158
E 110
E 31
D 30
	while (fgets(buf, sizeof buf, cf) != NULL)
E 30
I 30
D 128
	while (fgetfolded(buf, sizeof buf, cf) != NULL)
E 128
I 128
	while ((bp = fgetfolded(buf, sizeof buf, cf)) != NULL)
E 128
E 30
	{
I 108
D 128
		if (buf[0] == '#')
E 128
I 128
		if (bp[0] == '#')
		{
			if (bp != buf)
				free(bp);
E 128
			continue;
I 128
		}
E 128

E 108
I 65
D 139
		/* map $ into \001 (ASCII SOH) for macro expansion */
E 139
I 139
D 214
		/* map $ into \201 for macro expansion */
E 214
I 214
		/* do macro expansion mappings */
E 214
E 139
D 128
		for (p = buf; *p != '\0'; p++)
E 128
I 128
		for (p = bp; *p != '\0'; p++)
E 128
		{
I 110
D 128
			if (*p == '#' && p > buf && ConfigLevel >= 3)
E 128
I 128
			if (*p == '#' && p > bp && ConfigLevel >= 3)
E 128
			{
				/* this is an on-line comment */
				register char *e;

D 139
				switch (*--p)
E 139
I 139
				switch (*--p & 0377)
E 139
				{
D 139
				  case '\001':
E 139
I 139
				  case MACROEXPAND:
E 139
					/* it's from $# -- let it go through */
					p++;
					break;

				  case '\\':
					/* it's backslash escaped */
					(void) strcpy(p, p + 1);
					break;

				  default:
					/* delete preceeding white space */
D 128
					while (isspace(*p) && p > buf)
E 128
I 128
D 139
					while (isspace(*p) && p > bp)
E 139
I 139
					while (isascii(*p) && isspace(*p) && p > bp)
E 139
E 128
						p--;
D 124
					if ((e = index(++p, '\n')) != NULL)
E 124
I 124
					if ((e = strchr(++p, '\n')) != NULL)
E 124
						(void) strcpy(p, e);
					else
						p[0] = p[1] = '\0';
					break;
				}
				continue;
			}

E 110
D 214
			if (*p != '$')
E 214
I 214
			if (*p != '$' || p[1] == '\0')
E 214
				continue;

			if (p[1] == '$')
			{
				/* actual dollar sign.... */
D 78
				strcpy(p, p + 1);
E 78
I 78
				(void) strcpy(p, p + 1);
E 78
				continue;
			}

			/* convert to macro expansion character */
D 139
			*p = '\001';
E 139
I 139
D 214
			*p = MACROEXPAND;
E 214
I 214
			*p++ = MACROEXPAND;

I 293
			/* special handling for $=, $~, and $& */
			if (*p == '=' || *p == '~' || *p == '&')
				p++;

E 293
			/* convert macro name to code */
			*p = macid(p, &ep);
			if (ep != p)
				strcpy(p + 1, ep);
E 214
E 139
		}

		/* interpret this line */
I 188
		errno = 0;
E 188
E 65
D 30
		p = rindex(buf, '\n');
		if (p != NULL)
			*p = '\0';

E 30
D 128
		switch (buf[0])
E 128
I 128
		switch (bp[0])
E 128
		{
D 30
		  case '\n':
E 30
		  case '\0':
D 30
		  case ' ':
		  case '\t':
E 30
		  case '#':		/* comment */
			break;

		  case 'R':		/* rewriting rule */
D 128
			for (p = &buf[1]; *p != '\0' && *p != '\t'; p++)
E 128
I 128
			for (p = &bp[1]; *p != '\0' && *p != '\t'; p++)
E 128
				continue;

			if (*p == '\0')
I 22
			{
E 22
D 31
				syserr("invalid rewrite line \"%s\"", buf);
E 31
I 31
D 50
				syserr("line %d: invalid rewrite line \"%s\"",
					LineNumber, buf);
E 50
I 50
D 128
				syserr("invalid rewrite line \"%s\"", buf);
E 128
I 128
D 195
				syserr("invalid rewrite line \"%s\"", bp);
E 195
I 195
				syserr("invalid rewrite line \"%s\" (tab expected)", bp);
E 195
E 128
E 50
E 31
I 22
				break;
			}

			/* allocate space for the rule header */
			if (rwp == NULL)
			{
				RewriteRules[ruleset] = rwp =
					(struct rewrite *) xalloc(sizeof *rwp);
			}
E 22
			else
			{
D 22
				if (rwp == NULL)
D 6
					RewriteRules = rwp = (struct rewrite *) xalloc(sizeof *rwp);
E 6
I 6
				{
					RewriteRules[ruleset] = rwp =
						(struct rewrite *) xalloc(sizeof *rwp);
				}
E 6
				else
				{
					rwp->r_next = (struct rewrite *) xalloc(sizeof *rwp);
					rwp = rwp->r_next;
				}
				rwp->r_next = NULL;

				rwp->r_lhs = prescan(&buf[1], '\t');
				if (rwp->r_lhs != NULL)
					rwp->r_lhs = copyplist(rwp->r_lhs, TRUE);
				while (*p == '\t')
					p++;
				rwp->r_rhs = prescan(p, '\t');
				if (rwp->r_rhs != NULL)
					rwp->r_rhs = copyplist(rwp->r_rhs, TRUE);
E 22
I 22
				rwp->r_next = (struct rewrite *) xalloc(sizeof *rwp);
				rwp = rwp->r_next;
E 22
			}
I 22
			rwp->r_next = NULL;

			/* expand and save the LHS */
			*p = '\0';
D 25
			(void) expand(&buf[1], exbuf, &exbuf[sizeof exbuf]);
E 25
I 25
D 117
			expand(&buf[1], exbuf, &exbuf[sizeof exbuf], CurEnv);
E 117
I 117
D 128
			expand(&buf[1], exbuf, &exbuf[sizeof exbuf], e);
E 128
I 128
D 254
			expand(&bp[1], exbuf, &exbuf[sizeof exbuf], e);
E 254
I 254
			expand(&bp[1], exbuf, sizeof exbuf, e);
E 254
E 128
E 117
E 25
D 70
			rwp->r_lhs = prescan(exbuf, '\t');
E 70
I 70
D 147
			rwp->r_lhs = prescan(exbuf, '\t', pvpbuf);
E 147
I 147
D 193
			rwp->r_lhs = prescan(exbuf, '\t', pvpbuf, NULL);
E 193
I 193
			rwp->r_lhs = prescan(exbuf, '\t', pvpbuf,
D 259
					     sizeof pvpbuf, NULL);
E 259
I 259
					     sizeof pvpbuf, NULL, NULL);
E 259
E 193
E 147
I 135
			nfuzzy = 0;
E 135
E 70
			if (rwp->r_lhs != NULL)
I 135
			{
				register char **ap;

E 135
				rwp->r_lhs = copyplist(rwp->r_lhs, TRUE);
I 135

				/* count the number of fuzzy matches in LHS */
				for (ap = rwp->r_lhs; *ap != NULL; ap++)
				{
I 142
					char *botch;

					botch = NULL;
E 142
D 139
					switch (**ap)
E 139
I 139
					switch (**ap & 0377)
E 139
					{
					  case MATCHZANY:
					  case MATCHANY:
					  case MATCHONE:
					  case MATCHCLASS:
					  case MATCHNCLASS:
I 144
D 153
					  case CANONHOST:
E 153
E 144
						nfuzzy++;
I 142
						break;

					  case MATCHREPL:
						botch = "$0-$9";
						break;

I 255
#if	0
E 255
					  case CANONNET:
						botch = "$#";
D 144
						break;

					  case CANONHOST:
						botch = "$@";
E 144
						break;

					  case CANONUSER:
						botch = "$:";
						break;
I 255
#endif	/* 0 */
E 255

					  case CALLSUBR:
						botch = "$>";
						break;

					  case CONDIF:
						botch = "$?";
						break;

					  case CONDELSE:
						botch = "$|";
						break;

					  case CONDFI:
						botch = "$.";
						break;

					  case HOSTBEGIN:
						botch = "$[";
						break;

					  case HOSTEND:
						botch = "$]";
						break;

					  case LOOKUPBEGIN:
						botch = "$(";
						break;

					  case LOOKUPEND:
						botch = "$)";
						break;
E 142
					}
I 142
					if (botch != NULL)
						syserr("Inappropriate use of %s on LHS",
							botch);
E 142
				}
			}
E 135
I 123
			else
I 220
			{
E 220
				syserr("R line: null LHS");
I 220
				rwp->r_lhs = null_list;
			}
E 220
E 123

			/* expand and save the RHS */
			while (*++p == '\t')
				continue;
D 25
			(void) expand(p, exbuf, &exbuf[sizeof exbuf]);
E 25
I 25
D 29
			expand(p, exbuf, &exbuf[sizeof exbuf], CurEnv);
E 29
I 29
			q = p;
			while (*p != '\0' && *p != '\t')
				p++;
			*p = '\0';
D 117
			expand(q, exbuf, &exbuf[sizeof exbuf], CurEnv);
E 117
I 117
D 254
			expand(q, exbuf, &exbuf[sizeof exbuf], e);
E 254
I 254
			expand(q, exbuf, sizeof exbuf, e);
E 254
E 117
E 29
E 25
D 70
			rwp->r_rhs = prescan(exbuf, '\t');
E 70
I 70
D 147
			rwp->r_rhs = prescan(exbuf, '\t', pvpbuf);
E 147
I 147
D 193
			rwp->r_rhs = prescan(exbuf, '\t', pvpbuf, NULL);
E 193
I 193
			rwp->r_rhs = prescan(exbuf, '\t', pvpbuf,
D 259
					     sizeof pvpbuf, NULL);
E 259
I 259
					     sizeof pvpbuf, NULL, NULL);
E 259
E 193
E 147
E 70
			if (rwp->r_rhs != NULL)
I 135
			{
				register char **ap;

E 135
				rwp->r_rhs = copyplist(rwp->r_rhs, TRUE);
I 135

				/* check no out-of-bounds replacements */
				nfuzzy += '0';
				for (ap = rwp->r_rhs; *ap != NULL; ap++)
				{
D 139
					if (**ap != MATCHREPL)
E 139
I 139
D 142
					if ((**ap & 0377) != MATCHREPL)
E 139
						continue;
					if ((*ap)[1] <= '0' || (*ap)[1] > nfuzzy)
E 142
I 142
					char *botch;

					botch = NULL;
					switch (**ap & 0377)
E 142
					{
D 142
						syserr("replacement $%c out of bounds",
							(*ap)[1]);
E 142
I 142
					  case MATCHREPL:
						if ((*ap)[1] <= '0' || (*ap)[1] > nfuzzy)
						{
							syserr("replacement $%c out of bounds",
								(*ap)[1]);
						}
						break;

					  case MATCHZANY:
						botch = "$*";
						break;

					  case MATCHANY:
						botch = "$+";
						break;

					  case MATCHONE:
						botch = "$-";
						break;

					  case MATCHCLASS:
						botch = "$=";
						break;

					  case MATCHNCLASS:
						botch = "$~";
						break;
E 142
					}
I 142
					if (botch != NULL)
						syserr("Inappropriate use of %s on RHS",
							botch);
E 142
				}
			}
E 135
I 123
			else
I 220
			{
E 220
				syserr("R line: null RHS");
I 220
				rwp->r_rhs = null_list;
			}
E 220
E 123
E 22
			break;

I 6
		  case 'S':		/* select rewriting set */
D 128
			ruleset = atoi(&buf[1]);
E 128
I 128
D 187
			ruleset = atoi(&bp[1]);
E 187
I 187
D 279
			for (p = &bp[1]; isascii(*p) && isspace(*p); p++)
				continue;
D 247
			if (!isascii(*p) || !isdigit(*p))
E 247
I 247
			if (!isascii(*p))
E 247
			{
				syserr("invalid argument to S line: \"%.20s\"", 
					&bp[1]);
				break;
			}
D 247
			ruleset = atoi(p);
E 187
E 128
I 31
			if (ruleset >= MAXRWSETS || ruleset < 0)
E 247
I 247
			if (isdigit(*p))
E 247
			{
D 50
				syserr("readcf: line %d: bad ruleset %d (%d max)",
					LineNumber, ruleset, MAXRWSETS);
E 50
I 50
D 247
				syserr("bad ruleset %d (%d max)", ruleset, MAXRWSETS);
E 50
				ruleset = 0;
E 247
I 247
				ruleset = atoi(p);
				if (ruleset >= MAXRWSETS / 2 || ruleset < 0)
				{
					syserr("bad ruleset %d (%d max)",
						ruleset, MAXRWSETS / 2);
					ruleset = 0;
				}
			}
			else
			{
				STAB *s;
				char delim;

				q = p;
				while (*p != '\0' && isascii(*p) &&
				       (isalnum(*p) || strchr("-_$", *p) != NULL))
					p++;
				while (isascii(*p) && isspace(*p))
					*p++ = '\0';
				delim = *p;
				if (delim != '\0')
					*p++ = '\0';
				s = stab(q, ST_RULESET, ST_ENTER);
				if (s->s_ruleset != 0)
					ruleset = s->s_ruleset;
				else if (delim == '=')
				{
					ruleset = atoi(p);
					if (ruleset >= MAXRWSETS / 2 || ruleset < 0)
					{
						syserr("bad ruleset %s = %d (%d max)",
							q, ruleset, MAXRWSETS / 2);
						ruleset = 0;
					}
				}
				else if ((ruleset = --nextruleset) < MAXRWSETS / 2)
				{
					syserr("%s: too many named rulesets (%d max)",
						q, MAXRWSETS / 2);
					ruleset = 0;
				}
				s->s_ruleset = ruleset;
E 247
			}
E 279
I 279
			ruleset = strtorwset(&bp[1], NULL, ST_ENTER);
E 279
E 31
D 280
			rwp = NULL;
E 280
I 280
			rwp = RewriteRules[ruleset];
			if (rwp != NULL)
			{
				while (rwp->r_next != NULL)
					rwp = rwp->r_next;
				fprintf(stderr, "WARNING: Ruleset %s redefined\n",
					&bp[1]);
			}
E 280
			break;

E 6
		  case 'D':		/* macro definition */
D 50
			define(buf[1], newstr(&buf[2]));
E 50
I 50
D 57
			define(buf[1], newstr(&buf[2]), CurEnv);
E 57
I 57
D 117
			define(buf[1], newstr(munchstring(&buf[2])), CurEnv);
E 117
I 117
D 128
			define(buf[1], newstr(munchstring(&buf[2])), e);
E 128
I 128
D 147
			define(bp[1], newstr(munchstring(&bp[2])), e);
E 147
I 147
D 180
			define(bp[1], newstr(munchstring(&bp[2], NULL)), e);
E 180
I 180
D 214
			p = munchstring(&bp[2], NULL);
			define(bp[1], newstr(p), e);
E 214
I 214
			mid = macid(&bp[1], &ep);
			p = munchstring(ep, NULL);
			define(mid, newstr(p), e);
E 214
E 180
E 147
E 128
E 117
E 57
E 50
			break;

I 3
		  case 'H':		/* required header line */
D 4
			chompheader(&buf[1], H_DEFAULT);
E 4
I 4
D 7
			chompheader(&buf[1], TRUE);
E 7
I 7
D 117
			(void) chompheader(&buf[1], TRUE);
E 117
I 117
D 128
			(void) chompheader(&buf[1], TRUE, e);
E 128
I 128
D 260
			(void) chompheader(&bp[1], TRUE, e);
E 260
I 260
			(void) chompheader(&bp[1], TRUE, NULL, e);
E 260
E 128
E 117
E 7
E 4
			break;

I 5
		  case 'C':		/* word class */
I 15
D 159
		  case 'F':		/* word class from file */
E 15
D 55
			class = buf[1];
			if (!isalpha(class))
D 50
				goto badline;
E 50
I 50
			{
				syserr("illegal class name %c", class);
				break;
			}
E 50
			if (isupper(class))
				class -= 'A';
			else
				class -= 'a';
I 15
			
E 55
			/* read list of words from argument or file */
D 128
			if (buf[0] == 'F')
E 128
I 128
			if (bp[0] == 'F')
E 128
			{
				/* read from file */
D 128
				for (p = &buf[2]; *p != '\0' && !isspace(*p); p++)
E 128
I 128
D 139
				for (p = &bp[2]; *p != '\0' && !isspace(*p); p++)
E 139
I 139
				for (p = &bp[2];
				     *p != '\0' && !(isascii(*p) && isspace(*p));
				     p++)
E 139
E 128
					continue;
				if (*p == '\0')
					p = "%s";
				else
				{
					*p = '\0';
D 139
					while (isspace(*++p))
E 139
I 139
					while (isascii(*++p) && isspace(*p))
E 139
						continue;
				}
D 55
				fileclass(class, &buf[2], p);
E 55
I 55
D 116
				fileclass(buf[1], &buf[2], p);
E 116
I 116
D 128
				fileclass(buf[1], &buf[2], p, safe);
E 128
I 128
				fileclass(bp[1], &bp[2], p, safe);
E 128
E 116
E 55
				break;
			}
E 15

E 159
D 15
			/* scan the list of words and set class 'i' for all */
E 15
I 15
D 246
			/* scan the list of words and set class for all */
E 15
D 128
			for (p = &buf[2]; *p != '\0'; )
E 128
I 128
D 181
			for (p = &bp[2]; *p != '\0'; )
E 181
I 181
D 214
			expand(&bp[2], exbuf, &exbuf[sizeof exbuf], e);
E 214
I 214
			mid = macid(&bp[1], &ep);
			expand(ep, exbuf, &exbuf[sizeof exbuf], e);
E 214
			for (p = exbuf; *p != '\0'; )
E 246
I 246
		  case 'T':		/* trusted user (set class `t') */
			if (bp[0] == 'C')
E 246
E 181
E 128
			{
I 246
				mid = macid(&bp[1], &ep);
D 254
				expand(ep, exbuf, &exbuf[sizeof exbuf], e);
E 254
I 254
				expand(ep, exbuf, sizeof exbuf, e);
E 254
				p = exbuf;
			}
			else
			{
				mid = 't';
				p = &bp[1];
			}
			while (*p != '\0')
			{
E 246
				register char *wd;
				char delim;
D 59
				register STAB *s;
E 59

D 139
				while (*p != '\0' && isspace(*p))
E 139
I 139
				while (*p != '\0' && isascii(*p) && isspace(*p))
E 139
					p++;
				wd = p;
D 139
				while (*p != '\0' && !isspace(*p))
E 139
I 139
				while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 139
					p++;
				delim = *p;
				*p = '\0';
				if (wd[0] != '\0')
I 142
D 186
				{
					if (tTd(37, 2))
						printf("setclass(%c, %s)\n",
							bp[1], wd);
E 186
E 142
D 55
				{
D 9
					s = stab(wd, ST_ENTER);
E 9
I 9
					s = stab(wd, ST_CLASS, ST_ENTER);
E 9
D 23
					s->s_class |= 1 << class;
E 23
I 23
					s->s_class |= 1L << class;
E 23
				}
E 55
I 55
D 128
					setclass(buf[1], wd);
E 128
I 128
D 214
					setclass(bp[1], wd);
E 214
I 214
					setclass(mid, wd);
E 214
I 142
D 186
				}
E 186
E 142
E 128
E 55
				*p = delim;
			}
I 159
			break;

		  case 'F':		/* word class from file */
D 182
			/* read list of words from argument or file */
			/* read from file */
			for (p = &bp[2];
			     *p != '\0' && !(isascii(*p) && isspace(*p));
			     p++)
				continue;
E 182
I 182
D 214
			for (p = &bp[2]; isascii(*p) && isspace(*p); )
E 214
I 214
			mid = macid(&bp[1], &ep);
			for (p = ep; isascii(*p) && isspace(*p); )
E 214
				p++;
			if (p[0] == '-' && p[1] == 'o')
			{
				optional = TRUE;
				while (*p != '\0' && !(isascii(*p) && isspace(*p)))
					p++;
				while (isascii(*p) && isspace(*p))
D 207
					*p++;
E 207
I 207
					p++;
E 207
			}
			else
				optional = FALSE;
			file = p;
			while (*p != '\0' && !(isascii(*p) && isspace(*p)))
				p++;
E 182
			if (*p == '\0')
				p = "%s";
			else
			{
				*p = '\0';
				while (isascii(*++p) && isspace(*p))
					continue;
			}
D 182
			fileclass(bp[1], &bp[2], p, safe);
E 182
I 182
			fileclass(bp[1], file, p, safe, optional);
E 182
E 159
			break;

I 157
#ifdef XLA
		  case 'L':		/* extended load average description */
			xla_init(&bp[1]);
			break;
#endif

E 157
I 8
		  case 'M':		/* define mailer */
D 13
			makemailer(&buf[1]);
E 13
I 13
D 74
D 75
			makemailer(&buf[1], safe);
E 75
I 75
D 128
			makemailer(&buf[1]);
E 128
I 128
			makemailer(&bp[1]);
E 128
E 75
E 74
I 74
			makemailer(&buf[1]);
E 74
I 34
			break;

		  case 'O':		/* set option */
D 35
			if (buf[2] == '\0')
				Option[buf[1]] = "";
			else
				Option[buf[1]] = newstr(&buf[2]);
E 35
I 35
D 37
			setoption(buf[1], &buf[2]);
E 37
I 37
D 74
D 75
			setoption(buf[1], &buf[2], safe, FALSE);
E 75
I 75
D 116
			setoption(buf[1], &buf[2], TRUE, FALSE);
E 116
I 116
D 128
			setoption(buf[1], &buf[2], safe, FALSE);
E 128
I 128
D 149
			setoption(bp[1], &bp[2], safe, FALSE);
E 149
I 149
			setoption(bp[1], &bp[2], safe, FALSE, e);
E 149
E 128
E 116
E 75
E 74
I 74
			setoption(buf[1], &buf[2], FALSE);
E 74
E 37
E 35
			break;

		  case 'P':		/* set precedence */
			if (NumPriorities >= MAXPRIORITIES)
			{
D 40
				syserr("readcf: line %d: too many P lines, %d max",
					LineNumber, MAXPRIORITIES);
E 40
I 40
				toomany('P', MAXPRIORITIES);
E 40
				break;
			}
D 50
			for (p = &buf[1]; *p != '\0' && *p != '='; p++)
E 50
I 50
D 128
			for (p = &buf[1]; *p != '\0' && *p != '=' && *p != '\t'; p++)
E 128
I 128
D 288
			for (p = &bp[1]; *p != '\0' && *p != '=' && *p != '\t'; p++)
E 288
I 288
			for (p = &bp[1]; *p != '\0' && *p != '='; p++)
E 288
E 128
E 50
				continue;
			if (*p == '\0')
				goto badline;
			*p = '\0';
D 128
			Priorities[NumPriorities].pri_name = newstr(&buf[1]);
E 128
I 128
			Priorities[NumPriorities].pri_name = newstr(&bp[1]);
E 128
			Priorities[NumPriorities].pri_val = atoi(++p);
			NumPriorities++;
E 34
E 13
D 246
			break;

I 40
		  case 'T':		/* trusted user(s) */
D 128
			p = &buf[1];
E 128
I 128
D 143
			p = &bp[1];
E 128
			while (*p != '\0')
			{
D 139
				while (isspace(*p))
E 139
I 139
				while (isascii(*p) && isspace(*p))
E 139
					p++;
				q = p;
D 139
				while (*p != '\0' && !isspace(*p))
E 139
I 139
				while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 139
					p++;
				if (*p != '\0')
					*p++ = '\0';
				if (*q == '\0')
					continue;
				for (pv = TrustedUsers; *pv != NULL; pv++)
					continue;
				if (pv >= &TrustedUsers[MAXTRUST])
				{
					toomany('T', MAXTRUST);
					break;
				}
				*pv = newstr(q);
			}
E 143
I 143
D 239
			/* this option is obsolete, but will be ignored */
E 239
I 239
			p = &buf[1];
			while (*p != '\0')
			{
				while (isspace(*p))
					p++;
				q = p;
				while (*p != '\0' && !isspace(*p))
					p++;
				if (*p != '\0')
					*p++ = '\0';
				if (*q == '\0')
					continue;
				(void) stab(q, ST_TRUSTED, ST_ENTER);
			}
E 246
E 239
E 143
I 109
			break;

		  case 'V':		/* configuration syntax version */
D 128
			ConfigLevel = atoi(&buf[1]);
E 128
I 128
D 187
			ConfigLevel = atoi(&bp[1]);
E 187
I 187
			for (p = &bp[1]; isascii(*p) && isspace(*p); p++)
				continue;
			if (!isascii(*p) || !isdigit(*p))
			{
				syserr("invalid argument to V line: \"%.20s\"", 
					&bp[1]);
				break;
			}
D 188
			ConfigLevel = atoi(p);
E 188
I 188
			ConfigLevel = strtol(p, &ep, 10);
I 265

			/*
			**  Do heuristic tweaking for back compatibility.
			*/

E 265
E 188
E 187
I 185
			if (ConfigLevel >= 5)
			{
				/* level 5 configs have short name in $w */
				p = macvalue('w', e);
				if (p != NULL && (p = strchr(p, '.')) != NULL)
					*p = '\0';
I 294
				if (tTd(35, 9))
					printf("redefine('w' as %s)\n",
						macvalue('w', e));
E 294
			}
I 265
			if (ConfigLevel >= 6)
			{
				ColonOkInAddr = FALSE;
			}

			/*
			**  Look for vendor code.
			*/

E 265
I 188
			if (*ep++ == '/')
			{
				/* extract vendor code */
				for (p = ep; isascii(*p) && isalpha(*p); )
					p++;
				*p = '\0';

				if (!setvendor(ep))
					syserr("invalid V line vendor code: \"%s\"",
						ep);
			}
E 188
E 185
E 128
E 109
			break;

I 113
		  case 'K':
D 128
			makemapentry(&buf[1]);
E 128
I 128
D 278
			makemapentry(&bp[1]);
E 278
I 278
			(void) makemapentry(&bp[1]);
E 278
I 271
			break;

		  case 'E':
			p = strchr(bp, '=');
			if (p != NULL)
				*p++ = '\0';
			setuserenv(&bp[1], p);
E 271
E 128
			break;

E 113
E 40
E 8
E 5
E 3
		  default:
I 5
		  badline:
E 5
D 31
			syserr("unknown control line \"%s\"", buf);
E 31
I 31
D 50
			syserr("readcf: line %d: unknown control line \"%s\"",
				LineNumber, buf);
E 50
I 50
D 128
			syserr("unknown control line \"%s\"", buf);
E 128
I 128
			syserr("unknown control line \"%s\"", bp);
E 128
E 50
E 31
		}
I 128
		if (bp != buf)
			free(bp);
E 128
	}
I 108
	if (ferror(cf))
	{
D 110
		syserr("Error reading %s", cfname);
E 110
I 110
		syserr("I/O read error", cfname);
E 110
		exit(EX_OSFILE);
	}
	fclose(cf);
E 108
I 50
	FileName = NULL;
I 126

I 211
	/* initialize host maps from local service tables */
	inithostmaps();
I 224

	/* determine if we need to do special name-server frotz */
	{
		int nmaps;
		char *maptype[MAXMAPSTACK];
		short mapreturn[MAXMAPACTIONS];

		nmaps = switch_map_find("hosts", maptype, mapreturn);
		UseNameServer = FALSE;
		if (nmaps > 0 && nmaps <= MAXMAPSTACK)
		{
			register int mapno;

			for (mapno = 0; mapno < nmaps && !UseNameServer; mapno++)
			{
				if (strcmp(maptype[mapno], "dns") == 0)
					UseNameServer = TRUE;
			}
		}
I 237

#ifdef HESIOD
		nmaps = switch_map_find("passwd", maptype, mapreturn);
		UseHesiod = FALSE;
		if (nmaps > 0 && nmaps <= MAXMAPSTACK)
		{
			register int mapno;

			for (mapno = 0; mapno < nmaps && !UseHesiod; mapno++)
			{
				if (strcmp(maptype[mapno], "hesiod") == 0)
					UseHesiod = TRUE;
			}
		}
#endif
E 237
	}
E 224
D 221

E 211
D 127
	/* set up host map */
	strcpy(buf, "host host");
	if (ConfigLevel >= 2)
		strcat(buf, " -a.");
	makemapentry(buf);
E 127
I 127
	if (stab("host", ST_MAP, ST_FIND) == NULL)
	{
		/* user didn't initialize: set up host map */
		strcpy(buf, "host host");
I 192
D 198
#ifdef NAMED_BIND
E 198
I 198
#if NAMED_BIND
E 198
E 192
		if (ConfigLevel >= 2)
			strcat(buf, " -a.");
I 192
#endif
E 192
		makemapentry(buf);
	}
E 221
E 127
E 126
E 50
I 40
}
/*
**  TOOMANY -- signal too many of some option
**
**	Parameters:
**		id -- the id of the error line
**		maxcnt -- the maximum possible values
**
**	Returns:
**		none.
**
**	Side Effects:
**		gives a syserr.
*/

I 276
void
E 276
toomany(id, maxcnt)
D 276
	char id;
E 276
I 276
	int id;
E 276
	int maxcnt;
{
D 50
	syserr("readcf: line %d: too many %c lines, %d max",
	       LineNumber, id, maxcnt);
E 50
I 50
	syserr("too many %c lines, %d max", id, maxcnt);
E 50
E 40
I 15
}
/*
**  FILECLASS -- read members of a class from a file
**
**	Parameters:
**		class -- class to define.
**		filename -- name of file to read.
**		fmt -- scanf string to use for match.
I 182
**		safe -- if set, this is a safe read.
**		optional -- if set, it is not an error for the file to
**			not exist.
E 182
**
**	Returns:
**		none
**
**	Side Effects:
**
**		puts all lines in filename that match a scanf into
**			the named class.
*/

I 276
void
E 276
D 116
fileclass(class, filename, fmt)
E 116
I 116
D 182
fileclass(class, filename, fmt, safe)
E 182
I 182
fileclass(class, filename, fmt, safe, optional)
E 182
E 116
	int class;
	char *filename;
	char *fmt;
I 116
	bool safe;
I 182
	bool optional;
E 182
E 116
{
D 85
	register FILE *f;
E 85
I 85
	FILE *f;
I 116
D 253
	struct stat stbuf;
E 253
I 253
	int sff;
I 270
	int pid;
	register char *p;
E 270
E 253
E 116
E 85
	char buf[MAXLINE];

I 197
	if (tTd(37, 2))
		printf("fileclass(%s, fmt=%s)\n", filename, fmt);

E 197
I 196
	if (filename[0] == '|')
	{
D 270
		syserr("fileclass: pipes (F%c%s) not supported due to security problems",
			class, filename);
		return;
E 270
I 270
		auto int fd;
		int i;
		char *argv[MAXPV + 1];

		i = 0;
		for (p = strtok(&filename[1], " \t"); p != NULL; p = strtok(NULL, " \t"))
		{
			if (i >= MAXPV)
				break;
			argv[i++] = p;
		}
		argv[i] = NULL;
		pid = prog_open(argv, &fd, CurEnv);
		if (pid < 0)
			f = NULL;
		else
			f = fdopen(fd, "r");
E 270
	}
E 196
D 106
	f = fopen(filename, "r");
E 106
I 106
D 116
	if (filename[0] == '|')
		f = popen(filename + 1, "r");
	else
		f = fopen(filename, "r");
E 116
I 116
D 253
	if (stat(filename, &stbuf) < 0)
	{
I 197
		if (tTd(37, 2))
			printf("  cannot stat (%s)\n", errstring(errno));
E 197
D 182
		syserr("fileclass: cannot stat %s", filename);
E 182
I 182
		if (!optional)
			syserr("fileclass: cannot stat %s", filename);
E 182
		return;
	}
	if (!S_ISREG(stbuf.st_mode))
	{
		syserr("fileclass: %s not a regular file", filename);
		return;
	}
	if (!safe && access(filename, R_OK) < 0)
	{
		syserr("fileclass: access denied on %s", filename);
		return;
	}
	f = fopen(filename, "r");
E 116
E 106
	if (f == NULL)
E 253
I 253
D 270
	sff = SFF_REGONLY;
	if (safe)
		sff |= SFF_OPENASROOT;
	f = safefopen(filename, O_RDONLY, 0, sff);
E 270
I 270
	else
	{
		pid = -1;
		sff = SFF_REGONLY;
		if (safe)
			sff |= SFF_OPENASROOT;
		f = safefopen(filename, O_RDONLY, 0, sff);
	}
E 270
D 257
	if (f == NULL && !optional)
E 257
I 257
	if (f == NULL)
E 257
E 253
	{
D 116
		syserr("cannot open %s", filename);
E 116
I 116
D 257
		syserr("fileclass: cannot open %s", filename);
E 257
I 257
		if (!optional)
			syserr("fileclass: cannot open %s", filename);
E 257
E 116
		return;
	}

	while (fgets(buf, sizeof buf, f) != NULL)
	{
D 276
		register STAB *s;
E 276
I 85
		register char *p;
D 287
# ifdef SCANF
E 287
I 287
# if SCANF
E 287
E 85
		char wordbuf[MAXNAME+1];

		if (sscanf(buf, fmt, wordbuf) != 1)
			continue;
D 85
		s = stab(wordbuf, ST_CLASS, ST_ENTER);
D 23
		s->s_class |= 1 << class;
E 23
I 23
D 55
		s->s_class |= 1L << class;
E 55
I 55
		setbitn(class, s->s_class);
E 85
I 85
		p = wordbuf;
D 124
# else SCANF
E 124
I 124
# else /* SCANF */
E 124
		p = buf;
D 124
# endif SCANF
E 124
I 124
# endif /* SCANF */
E 124

		/*
		**  Break up the match into words.
		*/

		while (*p != '\0')
		{
			register char *q;

			/* strip leading spaces */
D 139
			while (isspace(*p))
E 139
I 139
			while (isascii(*p) && isspace(*p))
E 139
				p++;
			if (*p == '\0')
				break;

			/* find the end of the word */
			q = p;
D 139
			while (*p != '\0' && !isspace(*p))
E 139
I 139
			while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 139
				p++;
			if (*p != '\0')
				*p++ = '\0';

			/* enter the word in the symbol table */
D 197
			s = stab(q, ST_CLASS, ST_ENTER);
			setbitn(class, s->s_class);
E 197
I 197
			setclass(class, q);
E 197
		}
E 85
E 55
E 23
	}

D 17
	fclose(f);
E 17
I 17
D 106
	(void) fclose(f);
E 106
I 106
D 116
	if (filename[0] == '|')
		(void) pclose(f);
	else
		(void) fclose(f);
E 116
I 116
	(void) fclose(f);
I 270
	if (pid > 0)
		(void) waitfor(pid);
E 270
E 116
E 106
E 17
E 15
I 8
}
/*
**  MAKEMAILER -- define a new mailer.
**
**	Parameters:
D 52
**		line -- description of mailer.  This is in tokens
**			separated by white space.  The fields are:
**			* the name of the mailer, as refered to
**			  in the rewriting rules.
**			* the pathname of the program to fork to
**			  execute it.
**			* the options needed by this program.
**			* the macro string needed to translate
**			  a local "from" name to one that can be
**			  returned to this machine.
**			* the argument vector (a series of parameters).
E 52
I 52
**		line -- description of mailer.  This is in labeled
**			fields.  The fields are:
D 228
**			   P -- the path to the mailer
**			   F -- the flags associated with the mailer
E 228
**			   A -- the argv for this mailer
D 228
**			   S -- the sender rewriting set
**			   R -- the recipient rewriting set
E 228
I 228
**			   C -- the character set for MIME conversions
**			   D -- the directory to run in
E 228
**			   E -- the eol string
I 228
**			   F -- the flags associated with the mailer
**			   L -- the maximum line length
**			   M -- the maximum message size
I 266
**			   N -- the niceness at which to run
E 266
**			   P -- the path to the mailer
**			   R -- the recipient rewriting set
**			   S -- the sender rewriting set
**			   T -- the mailer type (for DSNs)
**			   U -- the uid to run as
E 228
**			The first word is the canonical name of the mailer.
E 52
I 13
D 74
D 75
**		safe -- set if this is a safe configuration file.
E 75
E 74
E 13
**
**	Returns:
**		none.
**
**	Side Effects:
**		enters the mailer into the mailer table.
*/
E 8

I 276
void
E 276
D 7
/*
	printrules();
*/
}
/*
**  RWCRACK -- crack rewrite line.
**
**	Parameters:
**		l -- line to crack.
**
**	Returns:
**		local copy of cracked line.
**
**	Side Effects:
**		none.
*/

char **
rwcrack(l)
	register char *l;
{
	char *av[MAXATOM];
	int ac = 0;
	register char **avp;
	char buf[MAXNAME];
	register char *b;
	bool wasdelim = FALSE;
	char *delims = ":@!^.";
	extern char *index();
	bool tchange;
	extern char *newstr(), *xalloc();

	for (avp = av; *l != '\0' && *l != '\n'; avp++)
	{
		b = buf;
		tchange = FALSE;
		while (!tchange)
		{
			if (*l != '$')
			{
				if (wasdelim || index(delims, *l) != NULL)
					tchange = TRUE;
				wasdelim = (index(delims, *l) != NULL);
				if (wasdelim)
					tchange = TRUE;
				*b++ = *l++;
				continue;
			}

			tchange = TRUE;
			switch (*++l)
			{
			  case '$':		/* literal $ */
				*b++ = *l;
				break;

			  case '+':		/* match anything */
				*b++ = MATCHANY;
				*b++ = *++l;
				break;

			  case '-':		/* match one token */
				*b++ = MATCHONE;
				*b++ = *++l;
				break;

			  case '#':		/* canonical net name */
				*b++ = CANONNET;
				break;

			  case '@':		/* canonical host name */
				*b++ = CANONHOST;
				break;

			  case ':':		/* canonical user name */
				*b++ = CANONUSER;
				break;

			  default:
				*b++ = '$';
				l--;
				break;
			}
			l++;
		}

		/* save the argument we have collected */
		*b = '\0';
		*avp = newstr(buf);
		ac++;
	}

	/* allocate new space for vector */
	ac++;
	*avp = NULL;
	avp = (char **) xalloc(ac * sizeof *av);
	bmove(av, avp, ac * sizeof *av);

	return (avp);
E 7
I 7
D 8
# ifdef DEBUG
	if (Debug > 6)
		printrules();
# endif DEBUG
E 8
I 8
D 52
# define SETWORD \
		{ \
			while (*p != '\0' && isspace(*p)) \
				p++; \
			q = p; \
			while (*p != '\0' && !isspace(*p)) \
				p++; \
			if (*p != '\0') \
				*p++ = '\0'; \
		}

E 52
D 13
makemailer(line)
E 13
I 13
D 74
D 75
makemailer(line, safe)
E 75
I 75
makemailer(line)
E 75
E 74
I 74
makemailer(line)
E 74
E 13
	char *line;
I 13
D 74
D 75
	bool safe;
E 75
E 74
E 13
{
	register char *p;
D 52
	register char *q;
E 52
I 32
	register struct mailer *m;
	register STAB *s;
	int i;
E 32
D 52
	char *mname;
	char *mpath;
D 17
	int mopts;
E 17
I 17
	u_long mopts;
D 32
	extern u_long mfencode();
E 17
	char *mfrom;
	register struct mailer *m;
E 32
I 32
	short mrset, msset;
E 32
	char *margv[MAXPV + 1];
E 52
I 52
	char fcode;
I 138
	auto char *endp;
E 138
E 52
D 32
	register int i;
E 32
I 32
D 55
	extern u_long mfencode();
E 55
E 32
	extern int NextMailer;
I 52
	extern char **makeargv();
	extern char *munchstring();
D 147
	extern char *DelimChar;
E 147
I 56
D 264
	extern long atol();
E 264
E 56
E 52
I 16
D 32
	STAB *s;
E 32
E 16

I 52
	/* allocate a mailer and set up defaults */
	m = (struct mailer *) xalloc(sizeof *m);
	bzero((char *) m, sizeof *m);
D 133
	m->m_mno = NextMailer;
E 133
	m->m_eol = "\n";
I 204
	m->m_uid = m->m_gid = 0;
E 204

	/* collect the mailer name */
D 139
	for (p = line; *p != '\0' && *p != ',' && !isspace(*p); p++)
E 139
I 139
	for (p = line; *p != '\0' && *p != ',' && !(isascii(*p) && isspace(*p)); p++)
E 139
		continue;
	if (*p != '\0')
		*p++ = '\0';
	m->m_name = newstr(line);

	/* now scan through and assign info from the fields */
	while (*p != '\0')
	{
I 147
		auto char *delimptr;

E 147
D 139
		while (*p != '\0' && (*p == ',' || isspace(*p)))
E 139
I 139
		while (*p != '\0' && (*p == ',' || (isascii(*p) && isspace(*p))))
E 139
			p++;

		/* p now points to field code */
		fcode = *p;
		while (*p != '\0' && *p != '=' && *p != ',')
			p++;
		if (*p++ != '=')
		{
D 108
			syserr("`=' expected");
E 108
I 108
			syserr("mailer %s: `=' expected", m->m_name);
E 108
			return;
		}
D 139
		while (isspace(*p))
E 139
I 139
		while (isascii(*p) && isspace(*p))
E 139
			p++;

		/* p now points to the field body */
D 147
		p = munchstring(p);
E 147
I 147
		p = munchstring(p, &delimptr);
E 147

		/* install the field into the mailer struct */
		switch (fcode)
		{
		  case 'P':		/* pathname */
			m->m_mailer = newstr(p);
			break;

		  case 'F':		/* flags */
D 55
			m->m_flags = mfencode(p);
E 55
I 55
			for (; *p != '\0'; p++)
D 108
				setbitn(*p, m->m_flags);
E 108
I 108
D 139
				if (!isspace(*p))
E 139
I 139
				if (!(isascii(*p) && isspace(*p)))
E 139
					setbitn(*p, m->m_flags);
E 108
E 55
D 74
D 75
			if (!safe)
D 55
				m->m_flags &= ~M_RESTR;
E 55
I 55
				clrbitn(M_RESTR, m->m_flags);
E 75
E 74
E 55
			break;

		  case 'S':		/* sender rewriting ruleset */
		  case 'R':		/* recipient rewriting ruleset */
D 138
			i = atoi(p);
E 138
I 138
D 279
			i = strtol(p, &endp, 10);
E 138
			if (i < 0 || i >= MAXRWSETS)
			{
				syserr("invalid rewrite set, %d max", MAXRWSETS);
E 279
I 279
			i = strtorwset(p, &endp, ST_ENTER);
			if (i < 0)
E 279
				return;
D 279
			}
E 279
			if (fcode == 'S')
D 138
				m->m_s_rwset = i;
E 138
I 138
				m->m_sh_rwset = m->m_se_rwset = i;
E 138
			else
D 138
				m->m_r_rwset = i;
E 138
I 138
				m->m_rh_rwset = m->m_re_rwset = i;

			p = endp;
D 167
			if (*p == '/')
E 167
I 167
			if (*p++ == '/')
E 167
			{
D 279
				i = strtol(p, NULL, 10);
				if (i < 0 || i >= MAXRWSETS)
				{
					syserr("invalid rewrite set, %d max",
						MAXRWSETS);
E 279
I 279
D 292
				i = strtorwset(p, NULL);
E 292
I 292
				i = strtorwset(p, NULL, ST_ENTER);
E 292
				if (i < 0)
E 279
					return;
D 279
				}
E 279
				if (fcode == 'S')
					m->m_sh_rwset = i;
				else
					m->m_rh_rwset = i;
			}
E 138
			break;

		  case 'E':		/* end of line string */
			m->m_eol = newstr(p);
			break;

		  case 'A':		/* argument vector */
			m->m_argv = makeargv(p);
I 56
			break;

		  case 'M':		/* maximum message size */
			m->m_maxsize = atol(p);
E 56
			break;
I 107

		  case 'L':		/* maximum line length */
			m->m_linelimit = atoi(p);
I 266
			break;

		  case 'N':		/* run niceness */
			m->m_nice = atoi(p);
E 266
			break;
I 156

		  case 'D':		/* working directory */
			m->m_execdir = newstr(p);
I 204
			break;

I 222
		  case 'C':		/* default charset */
			m->m_defcharset = newstr(p);
			break;

I 226
D 238
		  case 'T':		/* MTS Type */
			m->m_mtstype = newstr(p);
E 238
I 238
D 274
		  case 'T':		/* MTA Type */
E 274
I 274
		  case 'T':		/* MTA-Name/Address/Diagnostic types */
I 283
			/* extract MTA name type; default to "dns" */
E 283
E 274
			m->m_mtatype = newstr(p);
			p = strchr(m->m_mtatype, '/');
			if (p != NULL)
			{
				*p++ = '\0';
				if (*p == '\0')
					p = NULL;
			}
D 283
			if (p == NULL)
				m->m_addrtype = m->m_mtatype;
			else
			{
				m->m_addrtype = p;
E 283
I 283
			if (*m->m_mtatype == '\0')
				m->m_mtatype = "dns";

			/* extract address type; default to "rfc822" */
			m->m_addrtype = p;
			if (p != NULL)
E 283
				p = strchr(p, '/');
D 283
			}
E 283
			if (p != NULL)
			{
				*p++ = '\0';
				if (*p == '\0')
					p = NULL;
			}
D 283
			if (p == NULL)
				m->m_diagtype = m->m_mtatype;
			else
				m->m_diagtype = p;
E 283
I 283
			if (m->m_addrtype == NULL || *m->m_addrtype == '\0')
				m->m_addrtype = "rfc822";

			/* extract diagnostic type; default to "smtp" */
			m->m_diagtype = p;
			if (m->m_diagtype == NULL || *m->m_diagtype == '\0')
				m->m_diagtype = "smtp";
E 283
E 238
			break;

E 226
E 222
		  case 'U':		/* user id */
			if (isascii(*p) && !isdigit(*p))
			{
				char *q = p;
				struct passwd *pw;

				while (isascii(*p) && isalnum(*p))
					p++;
				while (isascii(*p) && isspace(*p))
					*p++ = '\0';
				if (*p != '\0')
					*p++ = '\0';
D 258
				pw = getpwnam(q);
E 258
I 258
				pw = sm_getpwnam(q);
E 258
				if (pw == NULL)
					syserr("readcf: mailer U= flag: unknown user %s", q);
				else
				{
					m->m_uid = pw->pw_uid;
					m->m_gid = pw->pw_gid;
				}
			}
			else
			{
				auto char *q;

				m->m_uid = strtol(p, &q, 0);
				p = q;
			}
			while (isascii(*p) && isspace(*p))
				p++;
			if (*p == '\0')
				break;
			if (isascii(*p) && !isdigit(*p))
			{
				char *q = p;
				struct group *gr;

				while (isascii(*p) && isalnum(*p))
					p++;
				*p++ = '\0';
				gr = getgrnam(q);
				if (gr == NULL)
					syserr("readcf: mailer U= flag: unknown group %s", q);
				else
					m->m_gid = gr->gr_gid;
			}
			else
			{
				m->m_gid = strtol(p, NULL, 0);
			}
D 205
			setbitn(M_SPECIFIC_UID, m->m_flags);
E 205
E 204
			break;
E 156
E 107
		}

D 147
		p = DelimChar;
E 147
I 147
		p = delimptr;
E 147
	}

I 107
D 228
	/* do some heuristic cleanup for back compatibility */
	if (bitnset(M_LIMITS, m->m_flags))
	{
		if (m->m_linelimit == 0)
			m->m_linelimit = SMTPLINELIM;
D 121
		if (!bitnset(M_8BITS, m->m_flags))
E 121
I 121
		if (ConfigLevel < 2)
E 121
			setbitn(M_7BITS, m->m_flags);
	}

E 228
I 145
	/* do some rationality checking */
	if (m->m_argv == NULL)
	{
		syserr("M%s: A= argument required", m->m_name);
		return;
	}
	if (m->m_mailer == NULL)
	{
		syserr("M%s: P= argument required", m->m_name);
		return;
	}

E 145
E 107
D 133
	/* now store the mailer away */
E 133
E 52
	if (NextMailer >= MAXMAILERS)
	{
D 31
		syserr("Too many mailers defined");
E 31
I 31
D 50
		syserr("readcf: line %d: too many mailers defined (%d max)",
			LineNumber, MAXMAILERS);
E 50
I 50
		syserr("too many mailers defined (%d max)", MAXMAILERS);
E 50
E 31
		return;
	}
I 52
D 133
	Mailer[NextMailer++] = m;
E 133
I 133

I 228
	/* do some heuristic cleanup for back compatibility */
	if (bitnset(M_LIMITS, m->m_flags))
	{
		if (m->m_linelimit == 0)
			m->m_linelimit = SMTPLINELIM;
		if (ConfigLevel < 2)
			setbitn(M_7BITS, m->m_flags);
	}

D 238
	if (ConfigLevel < 6 && m->m_mtstype == NULL &&
E 238
I 238
	if (ConfigLevel < 6 &&
E 238
	    (strcmp(m->m_mailer, "[IPC]") == 0 ||
D 229
	     strcmp(m->m_mailer, "[TCP]") == NULL)))
E 229
I 229
D 231
	     strcmp(m->m_mailer, "[TCP]") == NULL))
E 231
I 231
	     strcmp(m->m_mailer, "[TCP]") == 0))
E 231
E 229
D 238
		m->m_mtstype = "Internet";
E 238
I 238
	{
		if (m->m_mtatype == NULL)
			m->m_mtatype = "dns";
		if (m->m_addrtype == NULL)
			m->m_addrtype = "rfc822";
		if (m->m_diagtype == NULL)
			m->m_diagtype = "smtp";
	}
E 238

	/* enter the mailer into the symbol table */
E 228
E 133
	s = stab(m->m_name, ST_MAILER, ST_ENTER);
D 133
	s->s_mailer = m;
E 133
I 133
	if (s->s_mailer != NULL)
	{
		i = s->s_mailer->m_mno;
		free(s->s_mailer);
	}
	else
	{
		i = NextMailer++;
	}
	Mailer[i] = s->s_mailer = m;
I 134
	m->m_mno = i;
E 134
E 133
}
/*
**  MUNCHSTRING -- translate a string into internal form.
**
**	Parameters:
**		p -- the string to munch.
I 147
**		delimptr -- if non-NULL, set to the pointer of the
**			field delimiter character.
E 147
**
**	Returns:
**		the munched string.
D 147
**
**	Side Effects:
**		Sets "DelimChar" to point to the string that caused us
**		to stop.
E 147
*/
E 52

D 52
	/* collect initial information */
	p = line;
	SETWORD;
	mname = q;
	SETWORD;
	mpath = q;
	SETWORD;
D 17
	mopts = crackopts(q);
E 17
I 17
	mopts = mfencode(q);
E 17
I 13
	if (!safe)
		mopts &= ~M_RESTR;
E 13
	SETWORD;
D 32
	mfrom = q;
E 32
I 32
	msset = atoi(q);
	SETWORD;
	mrset = atoi(q);
E 52
I 52
char *
D 147
munchstring(p)
E 147
I 147
munchstring(p, delimptr)
E 147
	register char *p;
I 147
	char **delimptr;
E 147
{
	register char *q;
	bool backslash = FALSE;
	bool quotemode = FALSE;
	static char buf[MAXLINE];
D 147
	extern char *DelimChar;
E 147
E 52
E 32

D 52
	if (*p == '\0')
E 52
I 52
	for (q = buf; *p != '\0'; p++)
E 52
	{
D 31
		syserr("invalid M line in configuration file");
E 31
I 31
D 50
		syserr("readcf: line %d: invalid M line in configuration file",
			LineNumber);
E 50
I 50
D 52
		syserr("invalid M line in configuration file");
E 50
E 31
		return;
E 52
I 52
		if (backslash)
		{
			/* everything is roughly literal */
I 54
			backslash = FALSE;
E 54
			switch (*p)
			{
			  case 'r':		/* carriage return */
				*q++ = '\r';
				continue;

			  case 'n':		/* newline */
				*q++ = '\n';
				continue;

			  case 'f':		/* form feed */
				*q++ = '\f';
				continue;

			  case 'b':		/* backspace */
				*q++ = '\b';
				continue;
			}
			*q++ = *p;
D 54
			backslash = FALSE;
E 54
		}
		else
		{
			if (*p == '\\')
				backslash = TRUE;
			else if (*p == '"')
				quotemode = !quotemode;
			else if (quotemode || *p != ',')
				*q++ = *p;
			else
				break;
		}
E 52
	}
I 32
D 52
	if (msset >= MAXRWSETS || mrset >= MAXRWSETS)
	{
		syserr("readcf: line %d: invalid rewrite set, %d max",
			LineNumber, MAXRWSETS);
		return;
	}
E 52
E 32

D 52
	/* allocate a mailer */
	m = (struct mailer *) xalloc(sizeof *m);
	m->m_name = newstr(mname);
	m->m_mailer = newstr(mpath);
	m->m_flags = mopts;
D 32
	m->m_from = newstr(mfrom);
E 32
I 32
	m->m_r_rwset = mrset;
	m->m_s_rwset = msset;
E 32
D 50
	m->m_badstat = EX_UNAVAILABLE;
E 50
D 18
	m->m_sendq = NULL;
E 18
I 16
	m->m_mno = NextMailer;
E 16
	Mailer[NextMailer++] = m;
E 52
I 52
D 147
	DelimChar = p;
E 147
I 147
	if (delimptr != NULL)
		*delimptr = p;
E 147
	*q++ = '\0';
	return (buf);
}
/*
**  MAKEARGV -- break up a string into words
**
**	Parameters:
**		p -- the string to break up.
**
**	Returns:
**		a char **argv (dynamically allocated)
**
**	Side Effects:
**		munges p.
*/
E 52

D 52
	/* collect the argument vector */
	for (i = 0; i < MAXPV - 1 && *p != '\0'; i++)
E 52
I 52
char **
makeargv(p)
	register char *p;
{
	char *q;
	int i;
	char **avp;
	char *argv[MAXPV + 1];

	/* take apart the words */
	i = 0;
	while (*p != '\0' && i < MAXPV)
E 52
	{
D 52
		SETWORD;
		margv[i] = newstr(q);
E 52
I 52
		q = p;
D 139
		while (*p != '\0' && !isspace(*p))
E 139
I 139
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 139
			p++;
D 139
		while (isspace(*p))
E 139
I 139
		while (isascii(*p) && isspace(*p))
E 139
			*p++ = '\0';
		argv[i++] = newstr(q);
E 52
	}
D 52
	margv[i++] = NULL;
E 52
I 52
	argv[i++] = NULL;
E 52

D 52
	/* save the argv */
D 14
	m->m_argv = (char **) xalloc(sizeof margv[0] * i);
E 14
I 14
D 28
	m->m_argv = (char **) xalloc((unsigned) (sizeof margv[0] * i));
E 28
I 28
	m->m_argv = (char **) xalloc(sizeof margv[0] * i);
E 28
E 14
	bmove((char *) margv, (char *) m->m_argv, sizeof margv[0] * i);
I 16
	s = stab(m->m_name, ST_MAILER, ST_ENTER);
	s->s_mailer = m;
E 52
I 52
	/* now make a copy of the argv */
	avp = (char **) xalloc(sizeof *avp * i);
D 69
	bmove((char *) argv, (char *) avp, sizeof *avp * i);
E 69
I 69
	bcopy((char *) argv, (char *) avp, sizeof *avp * i);
E 69

	return (avp);
E 52
E 16
E 8
E 7
}
/*
**  PRINTRULES -- print rewrite rules (for debugging)
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		prints rewrite rules.
*/

I 276
void
E 276
I 14
D 93
# ifdef DEBUG

E 93
E 14
printrules()
{
	register struct rewrite *rwp;
I 6
	register int ruleset;
E 6

D 6
	for (rwp = RewriteRules; rwp != NULL; rwp = rwp->r_next)
E 6
I 6
	for (ruleset = 0; ruleset < 10; ruleset++)
E 6
	{
D 6
		register char **av;
E 6
I 6
		if (RewriteRules[ruleset] == NULL)
			continue;
D 32
		printf("\n----Rule Set %d:\n", ruleset);
E 32
I 32
		printf("\n----Rule Set %d:", ruleset);
E 32
E 6

D 6
		printf("\n");
		for (av = rwp->r_lhs; *av != NULL; av++)
E 6
I 6
		for (rwp = RewriteRules[ruleset]; rwp != NULL; rwp = rwp->r_next)
E 6
		{
D 6
			xputs(*av);
			putchar('_');
E 6
I 6
D 32
			register char **av;

			printf("\n");
			for (av = rwp->r_lhs; *av != NULL; av++)
			{
				xputs(*av);
				putchar('_');
			}
			printf("\n\t");
			for (av = rwp->r_rhs; *av != NULL; av++)
			{
				xputs(*av);
				putchar('_');
			}
			printf("\n");
E 32
I 32
			printf("\nLHS:");
			printav(rwp->r_lhs);
			printf("RHS:");
			printav(rwp->r_rhs);
E 32
E 6
		}
D 6
		printf("\n\t");
		for (av = rwp->r_rhs; *av != NULL; av++)
		{
			xputs(*av);
			putchar('_');
		}
		printf("\n");
E 6
	}
I 8
}
I 227
/*
**  PRINTMAILER -- print mailer structure (for debugging)
**
**	Parameters:
**		m -- the mailer to print
**
**	Returns:
**		none.
*/
E 227
I 14

I 276
void
E 276
I 227
printmailer(m)
	register MAILER *m;
{
	int j;

	printf("mailer %d (%s): P=%s S=%d/%d R=%d/%d M=%ld U=%d:%d F=",
		m->m_mno, m->m_name,
		m->m_mailer, m->m_se_rwset, m->m_sh_rwset,
		m->m_re_rwset, m->m_rh_rwset, m->m_maxsize,
		m->m_uid, m->m_gid);
	for (j = '\0'; j <= '\177'; j++)
		if (bitnset(j, m->m_flags))
			(void) putchar(j);
	printf(" L=%d E=", m->m_linelimit);
	xputs(m->m_eol);
	if (m->m_defcharset != NULL)
		printf(" C=%s", m->m_defcharset);
D 238
	if (m->m_mtstype != NULL)
		printf(" T=%s", m->m_mtstype);
E 238
I 238
	printf(" T=%s/%s/%s",
		m->m_mtatype == NULL ? "<undefined>" : m->m_mtatype,
		m->m_addrtype == NULL ? "<undefined>" : m->m_addrtype,
		m->m_diagtype == NULL ? "<undefined>" : m->m_diagtype);
E 238
	if (m->m_argv != NULL)
	{
		char **a = m->m_argv;

		printf(" A=");
		while (*a != NULL)
		{
			if (a != m->m_argv)
				printf(" ");
			xputs(*a++);
		}
	}
	printf("\n");
}
E 227
D 93
# endif DEBUG
E 93
E 14
/*
D 17
**  CRACKOPTS -- crack mailer options
E 17
I 17
D 55
**  MFENCODE -- crack mailer options
E 17
**
**	These options modify the functioning of the mailer
**	from the configuration table.
**
**	Parameters:
**		p -- pointer to vector of options.
**
**	Returns:
**		option list in binary.
**
**	Side Effects:
**		none.
*/

struct optlist
{
	char	opt_name;	/* external name of option */
D 23
	int	opt_value;	/* internal name of option */
E 23
I 23
	u_long	opt_value;	/* internal name of option */
E 23
};
struct optlist	OptList[] =
{
I 51
	'A',	M_ARPAFMT,
	'C',	M_CANONICAL,
	'D',	M_NEEDDATE,
	'e',	M_EXPENSIVE,
	'F',	M_NEEDFROM,
E 51
	'f',	M_FOPT,
D 51
	'r',	M_ROPT,
E 51
I 51
	'h',	M_HST_UPPER,
	'I',	M_INTERNAL,
	'L',	M_LIMITS,
	'l',	M_LOCAL,
	'M',	M_MSGID,
	'm',	M_MUSER,
	'n',	M_NHDR,
E 51
D 50
	'q',	M_QUIET,
E 50
I 50
	'P',	M_RPATH,
I 51
	'p',	M_FROMPATH,
D 52
	'R',	M_CRLF,
E 52
	'r',	M_ROPT,
E 51
E 50
	'S',	M_RESTR,
D 51
	'n',	M_NHDR,
D 12
	'l',	M_NOHOST,
E 12
I 12
	'l',	M_LOCAL,
E 51
E 12
	's',	M_STRIPQ,
D 51
	'm',	M_MUSER,
	'F',	M_NEEDFROM,
	'D',	M_NEEDDATE,
	'M',	M_MSGID,
E 51
I 51
	'U',	M_UGLYUUCP,
E 51
	'u',	M_USR_UPPER,
D 51
	'h',	M_HST_UPPER,
E 51
	'x',	M_FULLNAME,
D 51
	'A',	M_ARPAFMT,
I 20
	'U',	M_UGLYUUCP,
I 21
	'e',	M_EXPENSIVE,
I 24
D 32
	'R',	M_RELRCPT,
E 32
I 26
	'X',	M_FULLSMTP,
I 33
	'C',	M_CANONICAL,
I 47
	'I',	M_INTERNAL,
E 51
I 51
	'X',	M_XDOT,
E 51
E 47
E 33
E 26
E 24
E 21
E 20
I 10
D 12
	'L',	M_FINAL,
E 12
E 10
D 14
	0,	0
E 14
I 14
	'\0',	0
E 14
};

D 17
crackopts(p)
E 17
I 17
u_long
mfencode(p)
E 17
	register char *p;
{
	register struct optlist *o;
D 17
	register int opts = 0;
E 17
I 17
	register u_long opts = 0;
E 17

	while (*p != '\0')
	{
		for (o = OptList; o->opt_name != '\0' && o->opt_name != *p; o++)
			continue;
D 52
		if (o->opt_name == '\0')
			syserr("bad mailer option %c", *p);
E 52
		opts |= o->opt_value;
		p++;
	}
	return (opts);
I 17
}
/*
**  MFDECODE -- decode mailer flags into external form.
**
**	Parameters:
**		flags -- value of flags to decode.
**		f -- file to write them onto.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

mfdecode(flags, f)
	u_long flags;
	FILE *f;
{
	register struct optlist *o;

	putc('?', f);
	for (o = OptList; o->opt_name != '\0'; o++)
	{
		if ((o->opt_value & flags) == o->opt_value)
		{
			flags &= ~o->opt_value;
			putc(o->opt_name, f);
		}
	}
	putc('?', f);
I 35
}
/*
E 55
**  SETOPTION -- set global processing option
**
**	Parameters:
**		opt -- option name.
**		val -- option value (as a text string).
I 37
D 74
D 75
**		safe -- if set, this came from a system configuration file.
E 75
I 75
**		safe -- set if this came from a configuration file.
**			Some options (if set from the command line) will
**			reset the user id to avoid security problems.
E 75
E 74
**		sticky -- if set, don't let other setoptions override
**			this value.
I 149
**		e -- the main envelope.
E 149
E 37
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets options as implied by the arguments.
*/

D 37
setoption(opt, val)
E 37
I 37
D 39
static int	StickyOpt[128 / sizeof (int)];
E 39
I 39
D 55
static int	StickyOpt[128 / sizeof (int)];	/* set if option is stuck */
extern char	*WizWord;			/* the stored wizard password */
E 55
I 55
static BITMAP	StickyOpt;		/* set if option is stuck */
I 276
extern void	settimeout __P((char *, char *));
E 276
D 84
extern char	*WizWord;		/* the stored wizard password */
E 84
I 64
D 107
extern char	*NetName;		/* name of home (local) network */
E 107
I 84
D 92
# ifdef SMTP
# ifdef WIZ
extern char	*WizWord;		/* the stored wizard password */
# endif WIZ
# endif SMTP
E 92
E 84
E 64
E 55
I 53
D 61
#ifdef DAEMON
D 55
extern int	MaxConnections;			/* max simult. SMTP conns */
E 55
I 55
extern int	MaxConnections;		/* max simult. SMTP conns */
E 55
#endif DAEMON
E 61
E 53
E 39

I 131

D 198
#ifdef NAMED_BIND
E 198
I 198
#if NAMED_BIND
E 198

struct resolverflags
{
	char	*rf_name;	/* name of the flag */
	long	rf_bits;	/* bits to set/clear */
} ResolverFlags[] =
{
	"debug",	RES_DEBUG,
	"aaonly",	RES_AAONLY,
	"usevc",	RES_USEVC,
	"primary",	RES_PRIMARY,
	"igntc",	RES_IGNTC,
	"recurse",	RES_RECURSE,
	"defnames",	RES_DEFNAMES,
	"stayopen",	RES_STAYOPEN,
	"dnsrch",	RES_DNSRCH,
I 194
	"true",		0,		/* to avoid error on old syntax */
E 194
	NULL,		0
};

#endif

I 206
D 209
/* codes for options that have no short name */
/* NOTE: some of these values may be in the list of "safe" options below */
#define O_BSP		0x80	/* have broken SMTP peers */
#define O_SQBH		0x81	/* sort queue by host */

E 209
struct optioninfo
{
	char	*o_name;	/* long name of option */
D 215
	char	o_code;		/* short name of option */
E 215
I 215
	u_char	o_code;		/* short name of option */
E 215
	bool	o_safe;		/* safe for random people to use */
} OptionTab[] =
{
D 209
	"SevenBitInput",	'7',	TRUE,
I 208
	"EightBitMode",		'8',	TRUE,
E 208
	"AliasFile",		'A',	FALSE,
	"AliasWait",		'a',	FALSE,
	"BlankSub",		'B',	FALSE,
	"MinFreeBlocks",	'b',	TRUE,
	"CheckpointInterval",	'C',	TRUE,
	"HoldExpensive",	'c',	FALSE,
	"AutoRebuildAliases",	'D',	FALSE,
	"DeliveryMode",		'd',	TRUE,
	"ErrorHeader",		'E',	FALSE,
	"ErrorMode",		'e',	TRUE,
	"TempFileMode",		'F',	FALSE,
	"SaveFromLine",		'f',	FALSE,
	"MatchGECOS",		'G',	FALSE,
	"HelpFile",		'H',	FALSE,
	"MaxHopCount",		'h',	FALSE,
	"NameServerOptions",	'I',	FALSE,
	"IgnoreDots",		'i',	TRUE,
	"ForwardPath",		'J',	FALSE,
	"SendMimeErrors",	'j',	TRUE,
	"ConnectionCacheSize",	'k',	FALSE,
	"ConnectionCacheTimeout", 'K',	FALSE,
	"UseErrorsTo",		'l',	FALSE,
	"LogLevel",		'L',	FALSE,
	"MeToo",		'm',	TRUE,
	"CheckAliases",		'n',	FALSE,
	"OldStyleHeaders",	'o',	TRUE,
	"DaemonPortOptions",	'O',	FALSE,
	"PrivacyOptions",	'p',	TRUE,
	"PostmasterCopy",	'P',	FALSE,
	"QueueFactor",		'q',	FALSE,
	"QueueDirectory",	'Q',	FALSE,
	"DontPruneRoutes",	'R',	FALSE,
	"ReadTimeout",		'r',	TRUE,
	"StatusFile",		'S',	FALSE,
	"SuperSafe",		's',	TRUE,
	"QueueTimeout",		'T',	FALSE,
	"TimeZoneSpec",		't',	FALSE,
	"UserDatabaseSpec",	'U',	FALSE,
	"DefaultUser",		'u',	FALSE,
	"FallbackMXhost",	'V',	FALSE,
	"Verbose",		'v',	TRUE,
	"TryNullMXList",	'w',	TRUE,
	"QueueLA",		'x',	FALSE,
	"RefuseLA",		'X',	FALSE,
	"RecipientFactor",	'y',	FALSE,
	"ForkQueueRuns",	'Y',	FALSE,
	"ClassFactor",		'z',	FALSE,
	"TimeFactor",		'Z',	FALSE,
	"BrokenSmtpPeers",	O_BSP,	TRUE,
	"SortQueueByHost",	O_SQBH,	TRUE,
	NULL,			'\0',	FALSE,
E 209
I 209
	"SevenBitInput",	'7',		TRUE,
I 272
#if MIME8TO7
E 272
	"EightBitMode",		'8',		TRUE,
I 272
#endif
E 272
	"AliasFile",		'A',		FALSE,
	"AliasWait",		'a',		FALSE,
	"BlankSub",		'B',		FALSE,
	"MinFreeBlocks",	'b',		TRUE,
	"CheckpointInterval",	'C',		TRUE,
	"HoldExpensive",	'c',		FALSE,
	"AutoRebuildAliases",	'D',		FALSE,
	"DeliveryMode",		'd',		TRUE,
	"ErrorHeader",		'E',		FALSE,
	"ErrorMode",		'e',		TRUE,
	"TempFileMode",		'F',		FALSE,
	"SaveFromLine",		'f',		FALSE,
	"MatchGECOS",		'G',		FALSE,
	"HelpFile",		'H',		FALSE,
	"MaxHopCount",		'h',		FALSE,
D 256
	"NameServerOptions",	'I',		FALSE,
E 256
I 256
	"ResolverOptions",	'I',		FALSE,
E 256
	"IgnoreDots",		'i',		TRUE,
	"ForwardPath",		'J',		FALSE,
	"SendMimeErrors",	'j',		TRUE,
	"ConnectionCacheSize",	'k',		FALSE,
	"ConnectionCacheTimeout", 'K',		FALSE,
	"UseErrorsTo",		'l',		FALSE,
	"LogLevel",		'L',		FALSE,
	"MeToo",		'm',		TRUE,
	"CheckAliases",		'n',		FALSE,
	"OldStyleHeaders",	'o',		TRUE,
	"DaemonPortOptions",	'O',		FALSE,
	"PrivacyOptions",	'p',		TRUE,
	"PostmasterCopy",	'P',		FALSE,
	"QueueFactor",		'q',		FALSE,
	"QueueDirectory",	'Q',		FALSE,
	"DontPruneRoutes",	'R',		FALSE,
D 210
	"ReadTimeout",		'r',		TRUE,
E 210
I 210
D 234
	"Timeouts",		'r',		TRUE,
E 234
I 234
	"Timeout",		'r',		TRUE,
E 234
E 210
	"StatusFile",		'S',		FALSE,
	"SuperSafe",		's',		TRUE,
	"QueueTimeout",		'T',		FALSE,
	"TimeZoneSpec",		't',		FALSE,
	"UserDatabaseSpec",	'U',		FALSE,
	"DefaultUser",		'u',		FALSE,
	"FallbackMXhost",	'V',		FALSE,
	"Verbose",		'v',		TRUE,
	"TryNullMXList",	'w',		TRUE,
	"QueueLA",		'x',		FALSE,
	"RefuseLA",		'X',		FALSE,
	"RecipientFactor",	'y',		FALSE,
D 256
	"ForkQueueRuns",	'Y',		FALSE,
E 256
I 256
	"ForkEachJob",		'Y',		FALSE,
E 256
	"ClassFactor",		'z',		FALSE,
D 256
	"TimeFactor",		'Z',		FALSE,
E 256
I 256
	"RetryFactor",		'Z',		FALSE,
E 256
D 263
#define O_BSP		0x80
	"BrokenSmtpPeers",	O_BSP,		TRUE,
E 263
D 232
#define O_SQBH		0x81
	"SortQueueByHost",	O_SQBH,		TRUE,
E 232
I 232
D 233
#define O_QUEUESORTORD,	0x81
E 233
I 233
#define O_QUEUESORTORD	0x81
E 233
	"QueueSortOrder",	O_QUEUESORTORD,	TRUE,
I 269
#define O_HOSTSFILE	0x82
	"HostsFile",		O_HOSTSFILE,	FALSE,
E 269
E 232
D 234
#define O_DNICE		0x82
	"DeliveryNiceness",	O_DNICE,	TRUE,
E 234
#define O_MQA		0x83
	"MinQueueAge",		O_MQA,		TRUE,
#define O_MHSA		0x84
I 235
/*
E 235
	"MaxHostStatAge",	O_MHSA,		TRUE,
I 235
*/
E 235
I 216
#define O_DEFCHARSET	0x85
	"DefaultCharSet",	O_DEFCHARSET,	TRUE,
I 221
#define O_SSFILE	0x86
	"ServiceSwitchFile",	O_SSFILE,	FALSE,
I 230
#define O_DIALDELAY	0x87
	"DialDelay",		O_DIALDELAY,	TRUE,
I 248
#define O_NORCPTACTION	0x88
	"NoRecipientAction",	O_NORCPTACTION,	TRUE,
I 252
#define O_SAFEFILEENV	0x89
	"SafeFileEnvironment",	O_SAFEFILEENV,	FALSE,
I 256
#define O_MAXMSGSIZE	0x8a
	"MaxMessageSize",	O_MAXMSGSIZE,	FALSE,
I 261
#define O_COLONOKINADDR	0x8b
	"ColonOkInAddr",	O_COLONOKINADDR, TRUE,
I 275
#define O_MAXQUEUERUN	0x8c
	"MaxQueueRunSize",	O_MAXQUEUERUN,	TRUE,
I 281
#define O_MAXCHILDREN	0x8d
/*
	"MaxDaemonChildren",	O_MAXCHILDREN,	FALSE,
*/
I 282
#define O_KEEPCNAMES	0x8e
	"DontExpandCnames",	O_KEEPCNAMES,	FALSE,
E 282
E 281
E 275
E 261
E 256
E 252
E 248
E 230
E 221
E 216

	NULL,			'\0',		FALSE,
E 209
};



I 276
void
E 276
E 206
E 131
D 74
D 149
setoption(opt, val, safe, sticky)
E 149
I 149
setoption(opt, val, safe, sticky, e)
E 149
E 74
I 74
setoption(opt, val, sticky)
E 74
E 37
D 206
	char opt;
E 206
I 206
D 276
	u_char opt;
E 276
I 276
	int opt;
E 276
E 206
	char *val;
I 37
D 74
	bool safe;
E 74
	bool sticky;
I 149
	register ENVELOPE *e;
E 149
E 37
{
I 131
	register char *p;
I 206
	register struct optioninfo *o;
I 223
	char *subopt;
I 240
D 242
D 243
	int len;
E 243
E 242
E 240
E 223
E 206
E 131
D 50
	time_t tval;
	int ival;
I 36
	bool bval;
E 50
E 36
D 37
	extern char *HelpFile;			/* defined in conf.c */
E 37
I 37
D 55
	int smask;
	int sindex;
E 55
E 37
I 36
	extern bool atobool();
I 60
	extern time_t convtime();
I 63
	extern int QueueLA;
	extern int RefuseLA;
I 188
	extern bool Warn_Q_option;
E 188
I 71
D 211
	extern bool trusteduser();
E 211
D 171
	extern char *username();
E 171
E 71
E 63
E 60
E 36

I 213
	errno = 0;
E 213
I 206
	if (opt == ' ')
	{
		/* full word options */
I 213
		struct optioninfo *sel;
E 213

		p = strchr(val, '=');
		if (p == NULL)
			p = &val[strlen(val)];
		while (*--p == ' ')
			continue;
		while (*++p == ' ')
			*p = '\0';
I 212
		if (p == val)
		{
			syserr("readcf: null option name");
			return;
		}
E 212
		if (*p == '=')
			*p++ = '\0';
		while (*p == ' ')
			p++;
I 223
		subopt = strchr(val, '.');
		if (subopt != NULL)
			*subopt++ = '\0';
E 223
I 213
		sel = NULL;
E 213
		for (o = OptionTab; o->o_name != NULL; o++)
		{
D 213
			if (strcasecmp(o->o_name, val) == 0)
E 213
I 213
			if (strncasecmp(o->o_name, val, strlen(val)) != 0)
				continue;
			if (strlen(o->o_name) == strlen(val))
			{
				/* completely specified -- this must be it */
				sel = NULL;
E 213
				break;
I 213
			}
			if (sel != NULL)
				break;
			sel = o;
E 213
		}
D 213
		if (o->o_name == NULL)
E 213
I 213
		if (sel != NULL && o->o_name == NULL)
			o = sel;
		else if (o->o_name == NULL)
I 215
		{
E 215
E 213
			syserr("readcf: unknown option name %s", val);
I 215
			return;
		}
E 215
I 213
		else if (sel != NULL)
		{
			syserr("readcf: ambiguous option name %s (matches %s and %s)",
				val, sel->o_name, o->o_name);
			return;
		}
		if (strlen(val) != strlen(o->o_name))
		{
			bool oldVerbose = Verbose;

			Verbose = TRUE;
			message("Option %s used as abbreviation for %s",
				val, o->o_name);
			Verbose = oldVerbose;
		}
E 213
		opt = o->o_code;
		val = p;
	}
	else
	{
		for (o = OptionTab; o->o_name != NULL; o++)
		{
			if (o->o_code == opt)
				break;
		}
I 223
		subopt = NULL;
E 223
	}

E 206
D 93
# ifdef DEBUG
E 93
	if (tTd(37, 1))
D 48
		printf("setoption %c=%s\n", opt, val);
E 48
I 48
D 206
		printf("setoption %c=%s", opt, val);
E 206
I 206
D 212
		printf("setoption %s (0x%x)=%s",
E 212
I 212
	{
		printf(isascii(opt) && isprint(opt) ?
D 223
			    "setoption %s (%c)=%s" : "setoption %s (0x%x)=%s",
E 223
I 223
D 286
			    "setoption %s (%c).%s=%s" :
			    "setoption %s (0x%x).%s=%s",
E 286
I 286
			    "setoption %s (%c).%s=" :
			    "setoption %s (0x%x).%s=",
E 286
E 223
E 212
			o->o_name == NULL ? "<unknown>" : o->o_name,
D 223
			opt, val);
E 223
I 223
			opt,
D 286
			subopt == NULL ? "" : subopt,
			val);
E 286
I 286
			subopt == NULL ? "" : subopt);
		xputs(val);
E 286
E 223
I 212
	}
E 212
E 206
E 48
D 93
# endif DEBUG
E 93

	/*
D 37
	**  First encode this option as appropriate.
E 37
I 37
	**  See if this option is preset for us.
E 37
	*/

I 37
D 55
	sindex = opt;
	smask = 1 << (sindex % sizeof (int));
	sindex /= sizeof (int);
	if (bitset(smask, StickyOpt[sindex]))
E 55
I 55
D 163
	if (bitnset(opt, StickyOpt))
E 163
I 163
D 166
	if (safe && bitnset(opt, StickyOpt))
E 166
I 166
	if (!sticky && bitnset(opt, StickyOpt))
E 166
E 163
E 55
	{
D 93
# ifdef DEBUG
E 93
D 48
		if (tTd(37, 2))
			printf("(ignored)\n");
E 48
I 48
		if (tTd(37, 1))
			printf(" (ignored)\n");
E 48
D 93
# endif DEBUG
E 93
		return;
	}
I 48
D 73
#ifdef DEBUG
	else if (tTd(37, 1))
		printf("\n");
#endif DEBUG
E 73
E 48
D 68
	if (sticky)
D 55
		StickyOpt[sindex] |= smask;
E 55
I 55
		setbitn(opt, StickyOpt);
E 68
E 55

D 71
	if (getruid() == 0)
E 71
I 71
D 74
	/*
	**  Check to see if this option can be specified by this user.
	*/

D 73
	if (!safe && (getruid() == 0 || trusteduser(username())))
E 73
I 73
D 75
	if (!safe && (getruid() == 0 || OpMode == MD_TEST))
E 75
I 75
D 83
	if (!safe && getruid())
E 83
I 83
D 91
	if (!safe && getruid() == 0)
E 91
I 91
D 176
	if (!safe && getuid() == 0)
E 176
I 176
	if (!safe && RealUid == 0)
E 176
E 91
E 83
E 75
E 73
E 71
		safe = TRUE;
I 71
D 112
	if (!safe && index("deiLmorsv", opt) == NULL)
E 112
I 112
D 120
	if (!safe && index("deiLmorsvC", opt) == NULL)
E 120
I 120
D 124
	if (!safe && index("deEiLmorsvC", opt) == NULL)
E 124
I 124
D 129
	if (!safe && strchr("deEiLmorsvC", opt) == NULL)
E 129
I 129
D 140
	if (!safe && strchr("deEiLmorsvC8", opt) == NULL)
E 140
I 140
D 165
	if (!safe && strchr("bdeEiLmoprsvC8", opt) == NULL)
E 165
I 165
D 177
D 178
	if (!safe && strchr("bdeEijLmoprsvC7", opt) == NULL)
E 178
I 178
D 199
	if (!safe && strchr("bCdeEijLmoprsvw7", opt) == NULL)
E 199
I 199
D 206
	if (!safe && strchr("bCdeijLmoprsvw7", opt) == NULL)
E 206
I 206
	if (!safe && !o->o_safe)
E 206
E 199
E 178
E 177
I 177
	if (!safe && strchr("!bdeEijLmoprsvC7", opt) == NULL)
E 177
E 165
E 140
E 129
E 124
E 120
E 112
I 73
	{
D 93
# ifdef DEBUG
E 93
D 94
		if (tTd(37, 1))
D 75
			printf(" (unsafe)\n");
E 75
I 75
			printf(" (unsafe)");
E 75
D 93
# endif DEBUG
E 93
E 73
D 75
		return;
E 75
I 75
D 91
		if (getruid() != geteuid())
E 91
I 91
		if (getuid() != geteuid())
E 94
I 94
D 95
		if (opt != 'M' || val[0] != 'r' && val[0] != 's')
E 95
I 95
		if (opt != 'M' || (val[0] != 'r' && val[0] != 's'))
E 95
E 94
E 91
		{
D 94
			printf("(Resetting uid)\n");
D 78
			setgid(getgid());
			setuid(getuid());
E 78
I 78
			(void) setgid(getgid());
			(void) setuid(getuid());
E 94
I 94
			if (tTd(37, 1))
				printf(" (unsafe)");
D 176
			if (getuid() != geteuid())
E 176
I 176
			if (RealUid != geteuid())
E 176
			{
D 101
				printf("(Resetting uid)\n");
E 101
I 101
				if (tTd(37, 1))
					printf("(Resetting uid)");
I 290
				endpwent();
E 290
E 101
D 176
				(void) setgid(getgid());
				(void) setuid(getuid());
E 176
I 176
				(void) setgid(RealGid);
				(void) setuid(RealUid);
E 176
			}
E 94
E 78
		}
E 75
I 73
	}
E 74
D 93
#ifdef DEBUG
E 93
D 74
D 101
	else if (tTd(37, 1))
E 101
I 101
	if (tTd(37, 1))
E 101
E 74
I 74
	if (tTd(37, 1))
E 74
		printf("\n");
D 93
#endif DEBUG
E 93
E 73
E 71

D 50
	/*
	**  Encode this option as appropriate.
	*/

E 37
	if (index("rT", opt) != NULL)
		tval = convtime(val);
	else if (index("gLu", opt) != NULL)
		ival = atoi(val);
I 42
	else if (index("F", opt) != NULL)
		ival = atooct(val);
E 42
I 36
D 37
	else if (index("s", opt) != NULL)
E 37
I 37
D 41
	else if (index("cfimosv", opt) != NULL)
E 41
I 41
D 44
	else if (index("acfimosv", opt) != NULL)
E 44
I 44
	else if (index("acDfimosv", opt) != NULL)
E 44
E 41
E 37
		bval = atobool(val);
I 37
	else if (index("be", opt) != NULL)
		/* do nothing */ ;
E 37
E 36
	else if (val[0] == '\0')
		val = "";
	else
		val = newstr(val);

	/*
	**  Now do the actual assignment.
	*/

E 50
D 206
	switch (opt)
E 206
I 206
	switch (opt & 0xff)
E 206
	{
I 177
	  case '!':		/* extended options */
		setextoption(val, safe, sticky, e);
		break;

E 177
I 104
D 130
	  case '=':		/* config file generation level */
		ConfigLevel = atoi(val);
		break;

E 130
I 107
D 164
	  case '8':		/* allow eight-bit input */
		EightBit = atobool(val);
E 164
I 164
	  case '7':		/* force seven-bit input */
D 202
		SevenBit = atobool(val);
E 202
I 202
		SevenBitInput = atobool(val);
		break;

I 272
#if MIME8TO7
E 272
	  case '8':		/* handling of 8-bit input */
		switch (*val)
		{
D 203
		  case 'r':		/* reject all 8-bit */
E 203
I 203
D 268
		  case 'r':		/* reject 8-bit, don't convert MIME */
E 203
			MimeMode = 0;
			break;

E 268
D 203
		  case 'c':		/* convert all 8-bit */
E 203
I 203
		  case 'm':		/* convert 8-bit, convert MIME */
E 203
			MimeMode = MM_CVTMIME|MM_MIME8BIT;
			break;

D 203
		  case 'm':		/* minimal encoding */
E 203
I 203
D 268
		  case 'j':		/* "just send 8" */
E 203
			MimeMode = MM_PASS8BIT;
			break;

E 268
		  case 'p':		/* pass 8 bit, convert MIME */
D 268
			MimeMode = MM_PASS8BIT|MM_CVTMIME;
E 268
I 268
			MimeMode = MM_CVTMIME|MM_PASS8BIT;
E 268
			break;

		  case 's':		/* strict adherence */
			MimeMode = MM_CVTMIME;
			break;

I 268
#if 0
		  case 'r':		/* reject 8-bit, don't convert MIME */
			MimeMode = 0;
			break;

		  case 'j':		/* "just send 8" */
			MimeMode = MM_PASS8BIT;
			break;

E 268
D 203
		  case 'e':		/* encode 8 bit if available */
E 203
I 203
		  case 'a':		/* encode 8 bit if available */
E 203
			MimeMode = MM_MIME8BIT|MM_PASS8BIT|MM_CVTMIME;
I 203
			break;

		  case 'c':		/* convert 8 bit to MIME, never 7 bit */
			MimeMode = MM_MIME8BIT;
E 203
			break;
I 268
#endif
E 268

		  default:
			syserr("Unknown 8-bit mode %c", *val);
			exit(EX_USAGE);
		}
E 202
E 164
		break;
I 272
#endif
E 272

E 107
E 104
	  case 'A':		/* set default alias file */
D 50
		AliasFile = val;
I 37
		if (AliasFile[0] == '\0')
E 50
I 50
		if (val[0] == '\0')
E 50
D 163
			AliasFile = "aliases";
E 163
I 163
			setalias("aliases");
E 163
I 50
		else
D 163
			AliasFile = newstr(val);
E 163
I 163
			setalias(val);
E 163
E 50
I 41
		break;

I 71
	  case 'a':		/* look N minutes for "@:@" in alias file */
		if (val[0] == '\0')
D 190
			SafeAlias = 5;
E 190
I 190
			SafeAlias = 5 * 60;		/* five minutes */
E 190
		else
D 190
			SafeAlias = atoi(val);
E 190
I 190
			SafeAlias = convtime(val, 'm');
E 190
		break;

E 71
I 67
	  case 'B':		/* substitution for blank character */
		SpaceSub = val[0];
		if (SpaceSub == '\0')
			SpaceSub = ' ';
		break;

I 140
D 160
	  case 'b':		/* minimum number of blocks free on queue fs */
E 160
I 160
	  case 'b':		/* min blocks free on queue fs/max msg size */
		p = strchr(val, '/');
		if (p != NULL)
		{
			*p++ = '\0';
			MaxMessageSize = atol(p);
		}
E 160
		MinBlocksFree = atol(val);
		break;

E 140
E 67
D 71
	  case 'a':		/* look for "@:@" in alias file */
D 50
		SafeAlias = bval;
E 50
I 50
		SafeAlias = atobool(val);
E 50
E 41
E 37
		break;

E 71
I 37
D 46
	  case 'b':		/* operations mode */
		Mode = *val;
		switch (Mode)
E 46
I 46
	  case 'c':		/* don't connect to "expensive" mailers */
D 50
		NoConnect = bval;
E 50
I 50
		NoConnect = atobool(val);
E 50
		break;

I 79
D 103
	  case 'C':		/* checkpoint after N connections */
		CheckPointLimit = atoi(val);
E 103
I 103
	  case 'C':		/* checkpoint every N addresses */
		CheckpointInterval = atoi(val);
E 103
		break;

E 79
	  case 'd':		/* delivery mode */
		switch (*val)
E 46
		{
D 46
		  case MD_DAEMON:	/* run as a daemon */
#ifdef DAEMON
			ArpaMode = Smtp = TRUE;
#else DAEMON
			syserr("Daemon mode not implemented");
#endif DAEMON
E 46
I 46
		  case '\0':
D 149
			SendMode = SM_DELIVER;
E 149
I 149
			e->e_sendmode = SM_DELIVER;
E 149
E 46
			break;

I 58
		  case SM_QUEUE:	/* queue only */
#ifndef QUEUE
			syserr("need QUEUE to set -odqueue");
D 124
#endif QUEUE
E 124
I 124
#endif /* QUEUE */
E 124
			/* fall through..... */

E 58
D 46
		  case '\0':	/* default: do full delivery */
			Mode = MD_DEFAULT;
			/* fall through....... */

		  case MD_DELIVER:	/* do everything (default) */
		  case MD_FORK:		/* fork after verification */
		  case MD_QUEUE:	/* queue only */
		  case MD_VERIFY:	/* verify only */
I 38
		  case MD_TEST:		/* test addresses */
I 44
		  case MD_PRINT:	/* print queue contents */
		  case MD_INITALIAS:	/* initialize alias database */
		  case MD_FREEZE:	/* freeze config file */
E 46
I 46
		  case SM_DELIVER:	/* do everything */
		  case SM_FORK:		/* fork after verification */
D 58
		  case SM_QUEUE:	/* queue only */
E 58
D 149
			SendMode = *val;
E 149
I 149
			e->e_sendmode = *val;
E 149
E 46
E 44
E 38
			break;

		  default:
D 46
			syserr("Unknown operation mode -b%c", Mode);
E 46
I 46
			syserr("Unknown delivery mode %c", *val);
E 46
			exit(EX_USAGE);
		}
		break;

D 46
	  case 'c':		/* don't connect to "expensive" mailers */
		NoConnect = bval;
I 44
		break;

E 46
	  case 'D':		/* rebuild alias database as needed */
D 50
		AutoRebuild = bval;
E 50
I 50
		AutoRebuild = atobool(val);
E 50
E 44
		break;

I 118
	  case 'E':		/* error message header/header file */
D 119
		ErrMsgFile = newstr(val);
E 119
I 119
		if (*val != '\0')
			ErrMsgFile = newstr(val);
E 119
		break;

E 118
	  case 'e':		/* set error processing mode */
		switch (*val)
		{
D 50
		  case 'p':	/* print errors normally */
			break;	/* (default) */

		  case 'q':	/* be silent about it */
E 50
I 50
		  case EM_QUIET:	/* be silent about it */
E 50
D 58
			(void) freopen("/dev/null", "w", stdout);
D 50
			break;
E 50
I 50
			/* fall through... */
E 50

E 58
D 50
		  case 'm':	/* mail back */
			MailBack = TRUE;
E 50
I 50
		  case EM_MAIL:		/* mail back */
		  case EM_BERKNET:	/* do berknet error processing */
		  case EM_WRITE:	/* write back (or mail) */
E 50
D 201
			HoldErrs = TRUE;
D 50
			break;
E 50
I 50
			/* fall through... */
E 50

E 201
D 50
		  case 'e':	/* do berknet error processing */
			BerkNet = TRUE;
			HoldErrs = TRUE;
E 50
I 50
		  case EM_PRINT:	/* print errors normally (default) */
D 149
			ErrorMode = *val;
E 149
I 149
			e->e_errormode = *val;
E 149
E 50
			break;
D 50

		  case 'w':	/* write back (or mail) */
			WriteBack = TRUE;
			HoldErrs = TRUE;
			break;
E 50
		}
I 42
		break;

	  case 'F':		/* file mode */
D 50
		FileMode = ival;
E 50
I 50
D 72
		FileMode = atooct(val);
E 72
I 72
		FileMode = atooct(val) & 0777;
E 72
E 50
E 42
		break;

	  case 'f':		/* save Unix-style From lines on front */
D 50
		SaveFrom = bval;
E 50
I 50
		SaveFrom = atobool(val);
E 50
		break;

I 114
	  case 'G':		/* match recipients against GECOS field */
		MatchGecos = atobool(val);
		break;

E 114
E 37
D 36
# ifdef V6
	  case 'd':		/* dst timezone name */
		DstTimeZone = val;
		break;
# endif V6

E 36
	  case 'g':		/* default gid */
I 218
  g_opt:
E 218
I 37
D 43
		if (!safe)
			goto syntax;
E 37
		DefGid = ival;
E 43
I 43
D 71
		if (safe)
D 50
			DefGid = ival;
E 50
I 50
			DefGid = atoi(val);
E 71
I 71
D 182
		DefGid = atoi(val);
E 182
I 182
		if (isascii(*val) && isdigit(*val))
			DefGid = atoi(val);
		else
		{
			register struct group *gr;

			DefGid = -1;
			gr = getgrnam(val);
			if (gr == NULL)
D 218
				syserr("readcf: option g: unknown group %s", val);
E 218
I 218
				syserr("readcf: option %c: unknown group %s",
					opt, val);
E 218
			else
				DefGid = gr->gr_gid;
		}
E 182
E 71
E 50
E 43
		break;

	  case 'H':		/* help file */
D 50
		HelpFile = val;
I 37
		if (HelpFile[0] == '\0')
E 50
I 50
		if (val[0] == '\0')
E 50
			HelpFile = "sendmail.hf";
I 50
		else
			HelpFile = newstr(val);
E 50
E 37
		break;

I 103
	  case 'h':		/* maximum hop count */
		MaxHopCount = atoi(val);
		break;

E 103
I 90
	  case 'I':		/* use internet domain name server */
D 131
		UseNameServer = atobool(val);
E 131
I 131
D 198
#ifdef NAMED_BIND
E 198
I 198
#if NAMED_BIND
E 198
D 224
		UseNameServer = TRUE;
E 224
		for (p = val; *p != 0; )
		{
			bool clearmode;
			char *q;
			struct resolverflags *rfp;

			while (*p == ' ')
				p++;
			if (*p == '\0')
				break;
			clearmode = FALSE;
			if (*p == '-')
				clearmode = TRUE;
			else if (*p != '+')
				p--;
			p++;
			q = p;
D 139
			while (*p != '\0' && !isspace(*p))
E 139
I 139
			while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 139
				p++;
			if (*p != '\0')
				*p++ = '\0';
I 262
			if (strcasecmp(q, "HasWildcardMX") == 0)
			{
D 285
				NoMXforCanon = !clearmode;
E 285
I 285
				HasWildcardMX = !clearmode;
E 285
				continue;
			}
E 262
			for (rfp = ResolverFlags; rfp->rf_name != NULL; rfp++)
			{
				if (strcasecmp(q, rfp->rf_name) == 0)
					break;
			}
D 191
			if (clearmode)
E 191
I 191
			if (rfp->rf_name == NULL)
				syserr("readcf: I option value %s unrecognized", q);
			else if (clearmode)
E 191
				_res.options &= ~rfp->rf_bits;
			else
				_res.options |= rfp->rf_bits;
		}
		if (tTd(8, 2))
D 262
			printf("_res.options = %x\n", _res.options);
E 262
I 262
			printf("_res.options = %x, HasWildcardMX = %d\n",
D 284
				_res.options, !NoMXforCanon);
E 284
I 284
D 285
				_res.options, NoMXforCanon);
E 285
I 285
				_res.options, HasWildcardMX);
E 285
E 284
E 262
#else
		usrerr("name server (I option) specified but BIND not compiled in");
#endif
E 131
		break;

E 90
I 37
	  case 'i':		/* ignore dot lines in message */
D 50
		IgnrDot = bval;
E 50
I 50
		IgnrDot = atobool(val);
I 165
		break;

	  case 'j':		/* send errors in MIME (RFC 1341) format */
		SendMIMEErrors = atobool(val);
E 165
I 129
		break;

	  case 'J':		/* .forward search path */
		ForwardPath = newstr(val);
E 129
E 50
D 103
		break;

I 98
	  case 'k':		/* checkpoint every N addresses */
		CheckpointInterval = atoi(val);
E 103
		break;

I 115
	  case 'k':		/* connection cache size */
		MaxMciCache = atoi(val);
D 122
		if (MaxMciCache <= 0)
			MaxMciCache = 1;
E 122
I 122
		if (MaxMciCache < 0)
			MaxMciCache = 0;
E 122
		break;

	  case 'K':		/* connection cache timeout */
D 152
		MciCacheTimeout = convtime(val);
E 152
I 152
		MciCacheTimeout = convtime(val, 'm');
E 152
		break;

I 173
	  case 'l':		/* use Errors-To: header */
		UseErrorsTo = atobool(val);
		break;

E 173
E 115
E 98
E 37
	  case 'L':		/* log level */
D 50
		LogLevel = ival;
E 50
I 50
D 183
		LogLevel = atoi(val);
E 183
I 183
		if (safe || LogLevel < atoi(val))
			LogLevel = atoi(val);
E 183
E 50
		break;

I 37
	  case 'M':		/* define macro */
D 50
		define(val[0], &val[1]);
E 50
I 50
D 240
		define(val[0], newstr(&val[1]), CurEnv);
E 240
I 240
		p = newstr(&val[1]);
		if (!safe)
			cleanstrcpy(p, p, MAXNAME);
		define(val[0], p, CurEnv);
E 240
I 68
		sticky = FALSE;
E 68
E 50
		break;

	  case 'm':		/* send to me too */
D 50
		MeToo = bval;
E 50
I 50
		MeToo = atobool(val);
E 50
		break;
I 64

I 86
	  case 'n':		/* validate RHS in newaliases */
		CheckAliases = atobool(val);
		break;

I 173
	    /* 'N' available -- was "net name" */

E 173
I 154
	  case 'O':		/* daemon options */
		setdaemonoptions(val);
		break;

E 154
E 86
D 107
# ifdef DAEMON
	  case 'N':		/* home (local?) network name */
		NetName = newstr(val);
		break;
# endif DAEMON
E 64
I 53
D 61

#ifdef DAEMON
	  case 'N':		/* maximum simultaneous SMTP connections */
		MaxConnections = atoi(val);
		break;
#endif DAEMON
E 61
E 53

E 107
	  case 'o':		/* assume old style headers */
D 48
		CurEnv->e_oldstyle = bval;
E 48
I 48
D 50
		if (bval)
E 50
I 50
		if (atobool(val))
E 50
			CurEnv->e_flags |= EF_OLDSTYLE;
		else
			CurEnv->e_flags &= ~EF_OLDSTYLE;
I 140
		break;

	  case 'p':		/* select privacy level */
		p = val;
		for (;;)
		{
			register struct prival *pv;
			extern struct prival PrivacyValues[];

			while (isascii(*p) && (isspace(*p) || ispunct(*p)))
				p++;
			if (*p == '\0')
				break;
			val = p;
			while (isascii(*p) && isalnum(*p))
				p++;
			if (*p != '\0')
				*p++ = '\0';

			for (pv = PrivacyValues; pv->pv_name != NULL; pv++)
			{
				if (strcasecmp(val, pv->pv_name) == 0)
					break;
			}
I 155
			if (pv->pv_name == NULL)
				syserr("readcf: Op line: %s unrecognized", val);
E 155
			PrivacyFlags |= pv->pv_flag;
		}
I 250
		sticky = FALSE;
E 250
E 140
I 79
		break;

	  case 'P':		/* postmaster copy address for returned mail */
		PostMasterCopy = newstr(val);
		break;

	  case 'q':		/* slope of queue only function */
		QueueFactor = atoi(val);
E 79
E 48
		break;

E 37
	  case 'Q':		/* queue directory */
D 50
		QueueDir = val;
I 37
		if (QueueDir[0] == '\0')
E 50
I 50
		if (val[0] == '\0')
E 50
			QueueDir = "mqueue";
I 50
		else
			QueueDir = newstr(val);
I 151
		if (RealUid != 0 && !safe)
D 188
			auth_warning(e, "Processed from queue %s", QueueDir);
E 188
I 188
			Warn_Q_option = TRUE;
E 188
E 151
I 142
		break;

	  case 'R':		/* don't prune routes */
		DontPruneRoutes = atobool(val);
E 142
E 50
E 37
		break;

	  case 'r':		/* read timeout */
D 50
		ReadTimeout = tval;
E 50
I 50
D 141
		ReadTimeout = convtime(val);
E 141
I 141
D 223
		settimeouts(val);
E 223
I 223
		if (subopt == NULL)
			inittimeouts(val);
		else
			settimeout(subopt, val);
E 223
E 141
E 50
		break;

	  case 'S':		/* status file */
D 50
		StatFile = val;
I 37
		if (StatFile[0] == '\0')
E 50
I 50
		if (val[0] == '\0')
E 50
			StatFile = "sendmail.st";
I 50
		else
			StatFile = newstr(val);
E 50
E 37
		break;

D 36
# ifdef V6
	  case 's':		/* standard time time zone */
		StdTimeZone = val;
E 36
I 36
	  case 's':		/* be super safe, even if expensive */
D 50
		SuperSafe = bval;
E 50
I 50
		SuperSafe = atobool(val);
E 50
E 36
		break;
D 36
# endif V6
E 36

	  case 'T':		/* queue timeout */
D 50
		TimeOut = tval;
E 50
I 50
D 150
		TimeOut = convtime(val);
E 150
I 150
		p = strchr(val, '/');
		if (p != NULL)
		{
			*p++ = '\0';
D 152
			TimeOuts.to_q_warning = convtime(p);
E 152
I 152
D 211
			TimeOuts.to_q_warning = convtime(p, 'd');
E 211
I 211
D 223
			TimeOuts.to_q_warning[TOC_NORMAL] = convtime(p, 'd');
E 223
I 223
			settimeout("queuewarn", p);
E 223
E 211
E 152
		}
D 152
		TimeOuts.to_q_return = convtime(val);
E 152
I 152
D 211
		TimeOuts.to_q_return = convtime(val, 'h');
E 211
I 211
D 223
		TimeOuts.to_q_return[TOC_NORMAL] = convtime(val, 'h');
E 223
I 223
		settimeout("queuereturn", val);
E 223
E 211
E 152
E 150
E 50
D 88
		break;
E 88
I 88
D 115
		/*FALLTHROUGH*/
E 115
I 115
		break;
E 115
E 88

I 36
	  case 't':		/* time zone name */
I 107
		TimeZoneSpec = newstr(val);
E 107
D 88
# ifdef V6
D 50
		StdTimezone = val;
		DstTimezone = index(val, ',');
E 50
I 50
		StdTimezone = newstr(val);
		DstTimezone = index(StdTimeZone, ',');
E 50
		if (DstTimezone == NULL)
D 50
			goto syntax;
		*DstTimezone++ = '\0';
E 50
I 50
			syserr("bad time zone spec");
		else
			*DstTimezone++ = '\0';
E 50
# endif V6
E 88
		break;

I 100
	  case 'U':		/* location of user database */
D 105
		UdbFileName = newstr(val);
E 105
I 105
		UdbSpec = newstr(val);
E 105
		break;

E 100
E 36
	  case 'u':		/* set default uid */
I 218
		for (p = val; *p != '\0'; p++)
		{
			if (*p == '.' || *p == '/' || *p == ':')
			{
				*p++ = '\0';
				break;
			}
		}
E 218
I 37
D 43
		if (!safe)
			goto syntax;
E 37
		DefUid = ival;
E 43
I 43
D 71
		if (safe)
D 50
			DefUid = ival;
E 50
I 50
			DefUid = atoi(val);
E 71
I 71
D 182
		DefUid = atoi(val);
E 182
I 182
		if (isascii(*val) && isdigit(*val))
			DefUid = atoi(val);
		else
		{
			register struct passwd *pw;

			DefUid = -1;
D 258
			pw = getpwnam(val);
E 258
I 258
			pw = sm_getpwnam(val);
E 258
			if (pw == NULL)
				syserr("readcf: option u: unknown user %s", val);
			else
I 218
			{
E 218
				DefUid = pw->pw_uid;
I 218
				DefGid = pw->pw_gid;
			}
E 218
		}
E 182
I 96
		setdefuser();
I 154
D 218
		break;
E 218
I 218

		/* handle the group if it is there */
		if (*p == '\0')
			break;
		val = p;
		goto g_opt;
E 218

	  case 'V':		/* fallback MX host */
		FallBackMX = newstr(val);
E 154
E 96
E 71
E 50
E 43
		break;

D 37
	  case 'X':		/* transcript file template */
		XcriptFile = val;
E 37
I 37
	  case 'v':		/* run in verbose mode */
D 50
		Verbose = bval;
E 50
I 50
		Verbose = atobool(val);
E 50
D 46
		if (Verbose)
			NoConnect = FALSE;
E 46
E 37
		break;
I 173

D 178
	    /* 'w' available -- was "no wildcard MX matching" */
E 178
I 178
	  case 'w':		/* if we are best MX, try host directly */
		TryNullMXList = atobool(val);
		break;
E 178

	    /* 'W' available -- was wizard password */
E 173
I 39
D 92

D 84
# ifdef DEBUG
E 84
I 84
# ifdef SMTP
# ifdef WIZ
E 84
	  case 'W':		/* set the wizards password */
D 43
		if (!safe)
			goto syntax;
		WizWord = val;
E 43
I 43
D 71
		if (safe)
D 50
			WizWord = val;
E 50
I 50
			WizWord = newstr(val);
E 71
I 71
		WizWord = newstr(val);
E 71
E 50
E 43
		break;
D 84
# endif DEBUG
E 84
I 84
# endif WIZ
# endif SMTP
E 92
E 84
I 63

I 99
D 102
	  case 'w':		/* we have wildcard MX records */
		WildcardMX = atobool(val);
E 102
I 102
D 137
	  case 'w':		/* we don't have wildcard MX records */
		NoWildcardMX = atobool(val);
E 102
		break;

E 137
E 99
	  case 'x':		/* load avg at which to auto-queue msgs */
		QueueLA = atoi(val);
		break;

	  case 'X':		/* load avg at which to auto-reject connections */
		RefuseLA = atoi(val);
		break;
E 63
E 39

I 81
D 82
	  case 'z':		/* fork jobs during queue runs */
E 82
I 82
	  case 'y':		/* work recipient factor */
		WkRecipFact = atoi(val);
		break;

	  case 'Y':		/* fork jobs during queue runs */
E 82
		ForkQueueRuns = atobool(val);
I 82
		break;

	  case 'z':		/* work message class factor */
		WkClassFact = atoi(val);
		break;

	  case 'Z':		/* work time factor */
		WkTimeFact = atoi(val);
I 206
D 263
		break;

	  case O_BSP:		/* SMTP Peers can't handle 2-line greeting */
		BrokenSmtpPeers = atobool(val);
E 263
		break;

D 232
	  case O_SQBH:		/* sort work queue by host first */
		SortQueueByHost = atobool(val);
E 232
I 232
	  case O_QUEUESORTORD:	/* queue sorting order */
		switch (*val)
		{
		  case 'h':	/* Host first */
		  case 'H':
			QueueSortOrder = QS_BYHOST;
			break;

		  case 'p':	/* Priority order */
		  case 'P':
			QueueSortOrder = QS_BYPRIORITY;
			break;

		  default:
			syserr("Invalid queue sort order \"%s\"", val);
		}
I 269
		break;

	  case O_HOSTSFILE:	/* pathname of /etc/hosts file */
		HostsFile = newstr(val);
E 269
E 232
I 209
D 234
		break;

	  case O_DNICE:		/* delivery nice value */
		DeliveryNiceness = atoi(val);
E 234
		break;

	  case O_MQA:		/* minimum queue age between deliveries */
		MinQueueAge = convtime(val, 'm');
		break;

	  case O_MHSA:		/* maximum age of cached host status */
		MaxHostStatAge = convtime(val, 'm');
I 216
		break;

	  case O_DEFCHARSET:	/* default character set for mimefying */
D 217
		DefCharSet = newstr(val);
E 217
I 217
D 244
		DefaultCharSet = newstr(val);
E 244
I 244
D 249
		DefaultCharSet = newstr(denlstring(val));
E 249
I 249
D 251
		DefaultCharSet = newstr(denlstring(val, TRUE));
E 251
I 251
		DefaultCharSet = newstr(denlstring(val, TRUE, TRUE));
E 251
E 249
E 244
E 217
E 216
E 209
E 206
E 82
		break;

I 221
	  case O_SSFILE:	/* service switch file */
		ServiceSwitchFile = newstr(val);
I 230
		break;

	  case O_DIALDELAY:	/* delay for dial-on-demand operation */
		DialDelay = convtime(val, 's');
E 230
		break;
I 248

	  case O_NORCPTACTION:	/* what to do if no recipient */
		if (strcasecmp(val, "none") == 0)
			NoRecipientAction = NRA_NO_ACTION;
		else if (strcasecmp(val, "add-to") == 0)
			NoRecipientAction = NRA_ADD_TO;
		else if (strcasecmp(val, "add-apparently-to") == 0)
			NoRecipientAction = NRA_ADD_APPARENTLY_TO;
		else if (strcasecmp(val, "add-bcc") == 0)
			NoRecipientAction = NRA_ADD_BCC;
		else if (strcasecmp(val, "add-to-undisclosed") == 0)
			NoRecipientAction = NRA_ADD_TO_UNDISCLOSED;
		else
			syserr("Invalid NoRecipientAction: %s", val);
I 252

	  case O_SAFEFILEENV:	/* chroot() environ for writing to files */
		SafeFileEnv = newstr(val);
I 256
		break;

	  case O_MAXMSGSIZE:	/* maximum message size */
D 276
		MaxMessageSize = atol(p);
E 276
I 276
		MaxMessageSize = atol(val);
E 276
I 261
		break;

	  case O_COLONOKINADDR:	/* old style handling of colon addresses */
D 276
		ColonOkInAddr = atobool(p);
E 276
I 276
		ColonOkInAddr = atobool(val);
E 276
I 275
		break;

	  case O_MAXQUEUERUN:	/* max # of jobs in a single queue run */
D 276
		MaxQueueRun = atol(p);
E 276
I 276
		MaxQueueRun = atol(val);
E 276
E 275
E 261
E 256
		break;
I 281

	  case O_MAXCHILDREN:	/* max # of children of daemon */
		MaxChildren = atoi(val);
I 282
		break;

	  case O_KEEPCNAMES:	/* don't expand CNAME records */
		DontExpandCnames = atobool(val);
		break;
E 282
E 281
E 252
E 248

E 221
E 81
	  default:
I 235
		if (tTd(37, 1))
		{
			if (isascii(opt) && isprint(opt))
				printf("Warning: option %c unknown\n", opt);
			else
				printf("Warning: option 0x%x unknown\n", opt);
		}
E 235
D 36
		syserr("setoption: line %d: illegal option %c", LineNumber, opt);
E 36
I 36
D 45
	  syntax:
		syserr("setoption: line %d: syntax error on \"%c%s\"",
		       LineNumber, opt, val);
E 45
E 36
		break;
	}
I 68
	if (sticky)
		setbitn(opt, StickyOpt);
E 68
I 45
D 276
	return;
E 276
I 177
}
/*
**  SETEXTOPTION -- set extended option
**
**	This is a bogus attempt to do what sendmail should have done
**	in the first place.  Parses "name=value" options.
**
**	Parameters:
**		opt -- pointer to the string option.
**		safe -- from setoption.
**		sticky -- from setoption.
**		e -- the envelope.
**
**	Returns:
**		none.
*/

struct extopts
{
	char	*xo_name;	/* option name */
	short	xo_code;	/* option code */
	short	xo_flags;	/* flag bits */
};

/* bits for xo_flags */
#define XOF_SAFE	0x0001	/* this option is safe */
#define XOF_STICKY	0x0100	/* this option has been given & is sticky */

struct extopts	ExtOpts[] =
{
#define XO_TRYNULLMXLIST	1
	"trynullmxlist",	XO_TRYNULLMXLIST,	XOF_SAFE,
#define XO_MAXCODE		1
	NULL,			-1,			0
};


setextoption(opt, safe, sticky, e)
	register char *opt;
	bool safe;
	bool sticky;
	register ENVELOPE *e;
{
	register char *val;
	register struct extopts *xo;
	extern bool atobool();

	val = strchr(opt, '=');
	if (val != NULL)
		*val++ = '\0';

	for (xo = ExtOpts; xo->xo_name != NULL; xo++)
	{
		if (strcasecmp(xo->xo_name, opt) == 0)
			break;
	}

	if (!sticky && bitset(XOF_STICKY, xo->xo_flags))
		return;

	if (!safe && !bitset(XOF_SAFE, xo->xo_flags))
	{
		if (RealUid != geteuid())
		{
			(void) setgid(RealGid);
			(void) setuid(RealUid);
		}
	}

	switch (xo->xo_code)
	{
	  case XO_TRYNULLMXLIST:
		TryNullMXList = atobool(val);
		break;

	  default:
		syserr("Unknown extended option \"%s\"", opt);
		return;
	}

	if (sticky)
		xo->xo_flags |= XOF_STICKY;
E 177
I 55
}
/*
D 245
**  SETCLASS -- set a word into a class
E 245
I 245
**  SETCLASS -- set a string into a class
E 245
**
**	Parameters:
D 245
**		class -- the class to put the word in.
**		word -- the word to enter
E 245
I 245
**		class -- the class to put the string in.
**		str -- the string to enter
E 245
**
**	Returns:
**		none.
**
**	Side Effects:
**		puts the word into the symbol table.
*/

I 276
void
E 276
D 245
setclass(class, word)
E 245
I 245
setclass(class, str)
E 245
	int class;
D 245
	char *word;
E 245
I 245
	char *str;
E 245
{
	register STAB *s;

I 137
	if (tTd(37, 8))
D 186
		printf("%s added to class %c\n", word, class);
E 186
I 186
D 245
		printf("setclass(%c, %s)\n", class, word);
E 186
E 137
	s = stab(word, ST_CLASS, ST_ENTER);
E 245
I 245
D 294
		printf("setclass(%c, %s)\n", class, str);
E 294
I 294
		printf("setclass(%s, %s)\n", macname(class), str);
E 294
	s = stab(str, ST_CLASS, ST_ENTER);
E 245
	setbitn(class, s->s_class);
I 113
}
/*
**  MAKEMAPENTRY -- create a map entry
**
**	Parameters:
**		line -- the config file line
**
**	Returns:
D 277
**		TRUE if it successfully entered the map entry.
**		FALSE otherwise (usually syntax error).
E 277
I 277
D 278
**		none.
E 278
I 278
**		A pointer to the map that has been created.
**		NULL if there was a syntax error.
E 278
E 277
**
**	Side Effects:
**		Enters the map into the dictionary.
*/

D 278
void
E 278
I 278
MAP *
E 278
makemapentry(line)
	char *line;
{
	register char *p;
	char *mapname;
	char *classname;
D 179
	register STAB *map;
E 179
I 179
	register STAB *s;
E 179
	STAB *class;

D 139
	for (p = line; isspace(*p); p++)
E 139
I 139
	for (p = line; isascii(*p) && isspace(*p); p++)
E 139
		continue;
D 139
	if (!isalnum(*p))
E 139
I 139
	if (!(isascii(*p) && isalnum(*p)))
E 139
	{
		syserr("readcf: config K line: no map name");
D 278
		return;
E 278
I 278
		return NULL;
E 278
	}

	mapname = p;
D 139
	while (isalnum(*++p))
E 139
I 139
D 221
	while (isascii(*++p) && isalnum(*p))
E 221
I 221
	while ((isascii(*++p) && isalnum(*p)) || *p == '.')
E 221
E 139
		continue;
	if (*p != '\0')
		*p++ = '\0';
D 139
	while (isspace(*p))
E 139
I 139
	while (isascii(*p) && isspace(*p))
E 139
		p++;
D 139
	if (!isalnum(*p))
E 139
I 139
	if (!(isascii(*p) && isalnum(*p)))
E 139
	{
		syserr("readcf: config K line, map %s: no map class", mapname);
D 278
		return;
E 278
I 278
		return NULL;
E 278
	}
	classname = p;
D 139
	while (isalnum(*++p))
E 139
I 139
	while (isascii(*++p) && isalnum(*p))
E 139
		continue;
	if (*p != '\0')
		*p++ = '\0';
D 139
	while (isspace(*p))
E 139
I 139
	while (isascii(*p) && isspace(*p))
E 139
		p++;

	/* look up the class */
	class = stab(classname, ST_MAPCLASS, ST_FIND);
	if (class == NULL)
	{
		syserr("readcf: map %s: class %s not available", mapname, classname);
D 278
		return;
E 278
I 278
		return NULL;
E 278
	}

	/* enter the map */
D 179
	map = stab(mapname, ST_MAP, ST_ENTER);
D 168
	map->s_map.map_class = &class->s_mapclass;
E 168
I 168
D 169
	map->s_map.map_class = class->s_mapclass;
E 169
I 169
	map->s_map.map_class = &class->s_mapclass;
E 169
	map->s_map.map_mname = newstr(mapname);
E 179
I 179
	s = stab(mapname, ST_MAP, ST_ENTER);
	s->s_map.map_class = &class->s_mapclass;
	s->s_map.map_mname = newstr(mapname);
E 179
E 168

D 125
	if ((*class->s_mapclass.map_init)(&map->s_map, p))
E 125
I 125
D 168
	if ((*class->s_mapclass.map_init)(&map->s_map, mapname, p))
E 168
I 168
D 169
	if ((*class->s_mapclass->map_parse)(&map->s_map, p))
E 168
E 125
		map->s_map.map_flags |= MF_VALID;
E 169
I 169
D 170
	if ((*class->s_mapclass.map_parse)(&map->s_map, p))
		map->s_map.map_mflags |= MF_VALID;
E 170
I 170
D 172
	/* XXX shouldn't open the map here -- wait until usage time */
	if (class->s_mapclass.map_parse(&map->s_map, p) &&
	    class->s_mapclass.map_open(&map->s_map, O_RDONLY))
		map->s_map.map_mflags |= MF_VALID|MF_OPEN;
E 172
I 172
D 179
	if (class->s_mapclass.map_parse(&map->s_map, p))
		map->s_map.map_mflags |= MF_VALID;
E 179
I 179
	if (class->s_mapclass.map_parse(&s->s_map, p))
		s->s_map.map_mflags |= MF_VALID;

	if (tTd(37, 5))
	{
		printf("map %s, class %s, flags %x, file %s,\n",
			s->s_map.map_mname, s->s_map.map_class->map_cname,
			s->s_map.map_mflags,
			s->s_map.map_file == NULL ? "(null)" : s->s_map.map_file);
		printf("\tapp %s, domain %s, rebuild %s\n",
			s->s_map.map_app == NULL ? "(null)" : s->s_map.map_app,
			s->s_map.map_domain == NULL ? "(null)" : s->s_map.map_domain,
			s->s_map.map_rebuild == NULL ? "(null)" : s->s_map.map_rebuild);
	}
I 278

	return &s->s_map;
I 279
}
/*
**  STRTORWSET -- convert string to rewriting set number
**
**	Parameters:
**		p -- the pointer to the string to decode.
**		endp -- if set, store the trailing delimiter here.
**		stabmode -- ST_ENTER to create this entry, ST_FIND if
**			it must already exist.
**
**	Returns:
**		The appropriate ruleset number.
**		-1 if it is not valid (error already printed)
*/

int
strtorwset(p, endp, stabmode)
	char *p;
	char **endp;
	int stabmode;
{
	int ruleset;
	static int nextruleset = MAXRWSETS;

	while (isascii(*p) && isspace(*p))
		p++;
	if (!isascii(*p))
	{
		syserr("invalid ruleset name: \"%.20s\"", p);
		return -1;
	}
	if (isdigit(*p))
	{
		ruleset = strtol(p, endp, 10);
		if (ruleset >= MAXRWSETS / 2 || ruleset < 0)
		{
			syserr("bad ruleset %d (%d max)",
				ruleset, MAXRWSETS / 2);
			ruleset = -1;
		}
	}
	else
	{
		STAB *s;
		char delim;
		char *q;

		q = p;
		while (*p != '\0' && isascii(*p) &&
		       (isalnum(*p) || strchr("-_$", *p) != NULL))
			p++;
I 291
		if (q == p || !isalpha(*q))
		{
			/* no valid characters */
			syserr("invalid ruleset name: \"%.20s\"", q);
			return -1;
		}
E 291
		while (isascii(*p) && isspace(*p))
			*p++ = '\0';
		delim = *p;
		if (delim != '\0')
			*p = '\0';
		s = stab(q, ST_RULESET, stabmode);
		if (delim != '\0')
			*p = delim;

		if (s == NULL)
		{
			syserr("unknown ruleset %s", q);
			return -1;
		}

		if (stabmode == ST_ENTER && delim == '=')
		{
D 289
			ruleset = strtol(p, endp, 10);
E 289
I 289
			ruleset = strtol(++p, endp, 10);
E 289
			if (ruleset >= MAXRWSETS / 2 || ruleset < 0)
			{
				syserr("bad ruleset %s = %d (%d max)",
					q, ruleset, MAXRWSETS / 2);
				ruleset = -1;
			}
		}
		else
		{
			if (endp != NULL)
				*endp = p;
			if (s->s_ruleset > 0)
				ruleset = s->s_ruleset;
			else if ((ruleset = --nextruleset) < MAXRWSETS / 2)
			{
				syserr("%s: too many named rulesets (%d max)",
					q, MAXRWSETS / 2);
				ruleset = -1;
			}
		}
		if (s->s_ruleset > 0 && ruleset >= 0 && ruleset != s->s_ruleset)
		{
			syserr("%s: ruleset changed value (old %d, new %d)",
				q, ruleset, s->s_ruleset);
			ruleset = s->s_ruleset;
		}
		else if (ruleset > 0)
		{
			s->s_ruleset = ruleset;
		}
	}
	return ruleset;
E 279
E 278
E 179
E 172
E 170
E 169
I 141
}
/*
D 223
**  SETTIMEOUTS -- parse and set timeout values
E 223
I 223
**  INITTIMEOUTS -- parse and set timeout values
E 223
**
**	Parameters:
**		val -- a pointer to the values.  If NULL, do initial
**			settings.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Initializes the TimeOuts structure
*/

I 184
#define SECONDS
E 184
#define MINUTES	* 60
#define HOUR	* 3600

I 276
void
E 276
D 223
settimeouts(val)
E 223
I 223
inittimeouts(val)
E 223
	register char *val;
{
	register char *p;
I 148
	extern time_t convtime();
E 148

	if (val == NULL)
	{
		TimeOuts.to_initial = (time_t) 5 MINUTES;
		TimeOuts.to_helo = (time_t) 5 MINUTES;
		TimeOuts.to_mail = (time_t) 10 MINUTES;
		TimeOuts.to_rcpt = (time_t) 1 HOUR;
		TimeOuts.to_datainit = (time_t) 5 MINUTES;
		TimeOuts.to_datablock = (time_t) 1 HOUR;
		TimeOuts.to_datafinal = (time_t) 1 HOUR;
		TimeOuts.to_rset = (time_t) 5 MINUTES;
		TimeOuts.to_quit = (time_t) 2 MINUTES;
		TimeOuts.to_nextcommand = (time_t) 1 HOUR;
		TimeOuts.to_miscshort = (time_t) 2 MINUTES;
I 236
#if IDENTPROTO
E 236
I 184
		TimeOuts.to_ident = (time_t) 30 SECONDS;
I 236
#else
		TimeOuts.to_ident = (time_t) 0 SECONDS;
#endif
E 236
I 210
		TimeOuts.to_fileopen = (time_t) 60 SECONDS;
E 210
E 184
		return;
	}

	for (;; val = p)
	{
		while (isascii(*val) && isspace(*val))
			val++;
		if (*val == '\0')
			break;
		for (p = val; *p != '\0' && *p != ','; p++)
			continue;
		if (*p != '\0')
			*p++ = '\0';

		if (isascii(*val) && isdigit(*val))
		{
			/* old syntax -- set everything */
D 152
			TimeOuts.to_mail = convtime(val);
E 152
I 152
			TimeOuts.to_mail = convtime(val, 'm');
E 152
			TimeOuts.to_rcpt = TimeOuts.to_mail;
			TimeOuts.to_datainit = TimeOuts.to_mail;
			TimeOuts.to_datablock = TimeOuts.to_mail;
			TimeOuts.to_datafinal = TimeOuts.to_mail;
			TimeOuts.to_nextcommand = TimeOuts.to_mail;
			continue;
		}
		else
		{
D 210
			register char *q = strchr(val, '=');
E 210
I 210
			register char *q = strchr(val, ':');
E 210
D 223
			time_t to;
E 223

D 210
			if (q == NULL)
E 210
I 210
			if (q == NULL && (q = strchr(val, '=')) == NULL)
E 210
			{
				/* syntax error */
				continue;
			}
			*q++ = '\0';
D 152
			to = convtime(q);
E 152
I 152
D 223
			to = convtime(q, 'm');
E 223
I 223
			settimeout(val, q);
		}
	}
}
/*
**  SETTIMEOUT -- set an individual timeout
**
**	Parameters:
**		name -- the name of the timeout.
**		val -- the value of the timeout.
**
**	Returns:
**		none.
*/
E 223
E 152

I 276
void
E 276
D 223
			if (strcasecmp(val, "initial") == 0)
				TimeOuts.to_initial = to;
			else if (strcasecmp(val, "mail") == 0)
				TimeOuts.to_mail = to;
			else if (strcasecmp(val, "rcpt") == 0)
				TimeOuts.to_rcpt = to;
			else if (strcasecmp(val, "datainit") == 0)
				TimeOuts.to_datainit = to;
			else if (strcasecmp(val, "datablock") == 0)
				TimeOuts.to_datablock = to;
			else if (strcasecmp(val, "datafinal") == 0)
				TimeOuts.to_datafinal = to;
			else if (strcasecmp(val, "command") == 0)
				TimeOuts.to_nextcommand = to;
			else if (strcasecmp(val, "rset") == 0)
				TimeOuts.to_rset = to;
			else if (strcasecmp(val, "helo") == 0)
				TimeOuts.to_helo = to;
			else if (strcasecmp(val, "quit") == 0)
				TimeOuts.to_quit = to;
			else if (strcasecmp(val, "misc") == 0)
				TimeOuts.to_miscshort = to;
I 184
			else if (strcasecmp(val, "ident") == 0)
				TimeOuts.to_ident = to;
I 210
			else if (strcasecmp(val, "fileopen") == 0)
				TimeOuts.to_fileopen = to;
			else if (strcasecmp(val, "queuewarn") == 0)
D 211
				TimeOuts.to_q_warning = to;
E 211
I 211
				TimeOuts.to_q_warning[TOC_NORMAL] = to;
E 211
			else if (strcasecmp(val, "queuereturn") == 0)
D 211
				TimeOuts.to_q_return = to;
E 211
I 211
				TimeOuts.to_q_return[TOC_NORMAL] = to;
			else if (strcasecmp(val, "queuewarn.normal") == 0)
				TimeOuts.to_q_warning[TOC_NORMAL] = to;
			else if (strcasecmp(val, "queuereturn.normal") == 0)
				TimeOuts.to_q_return[TOC_NORMAL] = to;
			else if (strcasecmp(val, "queuewarn.urgent") == 0)
				TimeOuts.to_q_warning[TOC_URGENT] = to;
			else if (strcasecmp(val, "queuereturn.urgent") == 0)
				TimeOuts.to_q_return[TOC_URGENT] = to;
			else if (strcasecmp(val, "queuewarn.non-urgent") == 0)
				TimeOuts.to_q_warning[TOC_NONURGENT] = to;
			else if (strcasecmp(val, "queuereturn.non-urgent") == 0)
				TimeOuts.to_q_return[TOC_NONURGENT] = to;
E 211
E 210
E 184
			else
				syserr("settimeouts: invalid timeout %s", val);
E 223
I 223
settimeout(name, val)
	char *name;
	char *val;
{
	register char *p;
	time_t to;
	extern time_t convtime();

	to = convtime(val, 'm');
	p = strchr(name, '.');
	if (p != NULL)
		*p++ = '\0';

	if (strcasecmp(name, "initial") == 0)
		TimeOuts.to_initial = to;
	else if (strcasecmp(name, "mail") == 0)
		TimeOuts.to_mail = to;
	else if (strcasecmp(name, "rcpt") == 0)
		TimeOuts.to_rcpt = to;
	else if (strcasecmp(name, "datainit") == 0)
		TimeOuts.to_datainit = to;
	else if (strcasecmp(name, "datablock") == 0)
		TimeOuts.to_datablock = to;
	else if (strcasecmp(name, "datafinal") == 0)
		TimeOuts.to_datafinal = to;
	else if (strcasecmp(name, "command") == 0)
		TimeOuts.to_nextcommand = to;
	else if (strcasecmp(name, "rset") == 0)
		TimeOuts.to_rset = to;
	else if (strcasecmp(name, "helo") == 0)
		TimeOuts.to_helo = to;
	else if (strcasecmp(name, "quit") == 0)
		TimeOuts.to_quit = to;
	else if (strcasecmp(name, "misc") == 0)
		TimeOuts.to_miscshort = to;
	else if (strcasecmp(name, "ident") == 0)
		TimeOuts.to_ident = to;
	else if (strcasecmp(name, "fileopen") == 0)
		TimeOuts.to_fileopen = to;
	else if (strcasecmp(name, "queuewarn") == 0)
	{
		to = convtime(val, 'h');
D 225
		if (p == NULL || strcmp(p, "*") == NULL)
E 225
I 225
		if (p == NULL || strcmp(p, "*") == 0)
E 225
		{
			TimeOuts.to_q_warning[TOC_NORMAL] = to;
			TimeOuts.to_q_warning[TOC_URGENT] = to;
			TimeOuts.to_q_warning[TOC_NONURGENT] = to;
E 223
		}
I 223
		else if (strcasecmp(p, "normal") == 0)
			TimeOuts.to_q_warning[TOC_NORMAL] = to;
		else if (strcasecmp(p, "urgent") == 0)
			TimeOuts.to_q_warning[TOC_URGENT] = to;
		else if (strcasecmp(p, "non-urgent") == 0)
			TimeOuts.to_q_warning[TOC_NONURGENT] = to;
		else
			syserr("settimeout: invalid queuewarn subtimeout %s", p);
E 223
	}
I 223
	else if (strcasecmp(name, "queuereturn") == 0)
	{
		to = convtime(val, 'd');
		if (p == NULL || strcmp(p, "*") == 0)
		{
			TimeOuts.to_q_return[TOC_NORMAL] = to;
			TimeOuts.to_q_return[TOC_URGENT] = to;
			TimeOuts.to_q_return[TOC_NONURGENT] = to;
		}
		else if (strcasecmp(p, "normal") == 0)
			TimeOuts.to_q_return[TOC_NORMAL] = to;
		else if (strcasecmp(p, "urgent") == 0)
			TimeOuts.to_q_return[TOC_URGENT] = to;
		else if (strcasecmp(p, "non-urgent") == 0)
			TimeOuts.to_q_return[TOC_NONURGENT] = to;
		else
			syserr("settimeout: invalid queuereturn subtimeout %s", p);
	}
	else
		syserr("settimeout: invalid timeout %s", name);
E 223
E 141
E 113
E 55
D 50

  syntax:
	syserr("setoption: line %d: syntax error on \"%c%s\"",
	       LineNumber, opt, val);
E 50
E 45
E 35
E 17
E 8
}
E 1
