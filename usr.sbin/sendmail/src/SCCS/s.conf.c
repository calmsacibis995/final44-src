h46399
s 00000/00004/03694
d D 8.203 95/06/20 10:46:38 eric 418 417
c h_errno now in conf.h
e
s 00000/00000/03698
d D 8.202 95/06/19 17:10:08 eric 417 416
x 414
c back out check for /etc/sendmail.cf change -- instead, just
c always use sendmail.cf directly
e
s 00025/00000/03676
d D 8.201 95/06/19 07:39:36 eric 416 415
c release HUP signal before re-execing sendmail
e
s 00002/00005/03674
d D 8.200 95/06/18 08:07:56 eric 415 414
c try short host name for files hosts service (as well as nis)
e
s 00003/00000/03676
d D 8.199 95/06/16 10:27:37 eric 414 413
c if /etc/sendmail.cf exists, use it regardless of existence of
c vendor path
e
s 00006/00003/03670
d D 8.198 95/06/15 08:41:37 eric 413 412
c allow trusted users to have untrusted shells
e
s 00010/00002/03663
d D 8.197 95/06/15 08:22:25 eric 412 411
c updates for A/UX
e
s 00001/00001/03664
d D 8.196 95/06/13 09:46:52 eric 411 410
c tweak a couple of #if => #ifdef for compile purposes
e
s 00003/00003/03662
d D 8.195 95/06/13 09:23:13 eric 410 409
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00002/00002/03663
d D 8.194 95/06/11 12:01:29 eric 409 408
c make sm_getpwuid definition match prototype; move some debugging
e
s 00001/00001/03664
d D 8.193 95/06/10 14:55:39 eric 408 407
c fix definition for ANSI compilers
e
s 00000/00040/03665
d D 8.192 95/06/10 12:15:22 eric 407 406
c TRY_VERSIONED_CF_NAME is a botch -- consider mailstats
e
s 00023/00005/03682
d D 8.191 95/06/10 12:09:05 eric 406 405
c more clever connection refusals
e
s 00004/00002/03683
d D 8.190 95/06/10 11:30:02 eric 405 404
c improve case where service.switch exists but is missing a service
e
s 00049/00000/03636
d D 8.189 95/06/10 07:37:44 eric 404 403
c print OS compile flags (sigh)
e
s 00007/00003/03629
d D 8.188 95/06/10 06:29:21 eric 403 402
c non-DEC OSF/1 doesn't have svc.conf
e
s 00010/00010/03622
d D 8.187 95/06/05 07:26:26 eric 402 401
c freespace=>freediskspace, enoughspace=>enoughdiskspace to avoid
c conflicts with some memory allocators (e.g., A/UX)
e
s 00001/00001/03631
d D 8.186 95/05/31 15:16:07 eric 401 400
c default prog mailer must have internal form of $u
e
s 00042/00019/03590
d D 8.185 95/05/30 08:08:27 eric 400 399
c add trace flags in sm_gethostbyname
e
s 00023/00026/03586
d D 8.184 95/05/30 07:31:03 eric 399 398
c change OA semantics so that all .cf entries are mapped into the
c "files" or "local" alias service type
e
s 00012/00003/03600
d D 8.183 95/05/29 18:17:24 eric 398 397
c implementation of aliases that puts first unqualified A option
c as local; rest of A options after switched lookup
e
s 00018/00005/03585
d D 8.182 95/05/29 17:49:19 eric 397 396
c put use of getconfattr() on a separate USEGETCONFATTR compile flag;
c in my opinion getconfattr() is fundamentally misdesigned
e
s 00021/00000/03569
d D 8.181 95/05/29 10:27:49 eric 396 395
c try using getconfattr to find legal shells on AIX
e
s 00001/00001/03568
d D 8.180 95/05/29 09:26:43 eric 395 394
c try to fix a compile glitch on some HP-UX installations
e
s 00005/00001/03564
d D 8.179 95/05/28 11:50:09 eric 394 393
c lint
e
s 00002/00002/03563
d D 8.178 95/05/27 09:08:17 eric 393 392
c T= fields were wrong for default prog and *file* mailers
e
s 00069/00004/03496
d D 8.177 95/05/27 07:47:09 eric 392 391
c include putenv() implementation that doesn't depend on setenv()
e
s 00029/00001/03471
d D 8.176 95/05/25 11:38:47 eric 391 390
c fix some NIS problems
e
s 00037/00000/03435
d D 8.175 95/05/25 06:24:38 eric 390 389
c support for SunOS 4.0.3 and the LUNA
e
s 00059/00015/03376
d D 8.174 95/05/24 08:54:35 eric 389 388
c portability for Japanese workstations from Motonori Nakamura
e
s 00001/00001/03390
d D 8.173 95/05/23 16:44:36 eric 388 387
c allow use of seteuid() on systems that have new Posix semantics
e
s 00002/00000/03389
d D 8.172 95/05/19 16:33:28 eric 387 386
c forward declarations to fix compiler problems
e
s 00008/00000/03381
d D 8.171 95/05/19 16:16:16 eric 386 385
c add forward declarations to keep gcc from complaining
e
s 00001/00001/03380
d D 8.170 95/05/19 16:00:16 eric 385 384
c fix compile problems on various platforms
e
s 00003/00000/03378
d D 8.169 95/05/17 09:12:16 eric 384 383
c include NISPLUS in list of compile flags
e
s 00021/00012/03357
d D 8.168 95/05/17 07:20:50 eric 383 382
c handle AF_LINK addresses on 4.4BSD networking
e
s 00025/00000/03344
d D 8.167 95/05/16 21:07:59 eric 382 381
c vendor hooks (for Sun)
e
s 00001/00001/03343
d D 8.166 95/05/16 09:39:52 eric 381 380
c let any shell work on V1 configurations for back compat
e
s 00001/00001/03343
d D 8.165 95/05/16 06:40:02 eric 380 379
c "program" maps can be used for aliases
e
s 00004/00000/03340
d D 8.164 95/05/15 19:00:35 eric 379 378
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00002/00000/03338
d D 8.163 95/05/15 07:37:26 eric 378 377
c cleanup of LA_READKSYM code from Motonori NAKAMURA <motonori@cs.ritsumei.ac.jp>
e
s 00116/00005/03222
d D 8.162 95/05/15 07:31:01 eric 377 376
c probe interface configuration for other possible names
e
s 00094/00045/03133
d D 8.161 95/05/14 20:19:30 eric 376 375
c more cleanup from Motonori Nakamura
e
s 00005/00000/03173
d D 8.160 95/05/14 08:42:55 eric 375 374
c implement Fx|prog and "program" map class
e
s 00010/00000/03163
d D 8.159 95/05/13 15:06:11 eric 374 373
c put getcanonname into service switch
e
s 00002/00000/03161
d D 8.158 95/05/13 08:18:56 eric 373 372
c remove sendmail.cf versioning (except on compile flag) -- confusing
e
s 00009/00000/03152
d D 8.157 95/04/25 17:08:13 eric 372 371
c HP-UX 10.0 portability changes
e
s 00001/00001/03151
d D 8.156 95/04/25 06:45:18 eric 371 370
c make file mailer semantics switch off of P=[FILE]
e
s 00003/00001/03149
d D 8.155 95/04/23 20:28:23 eric 370 369
c hack to get around compile problem on HPs when running in ANSI mode
e
s 00002/00002/03148
d D 8.154 95/04/23 14:03:11 eric 369 368
c updates for new DSN drafts
e
s 00004/00002/03146
d D 8.153 95/04/22 14:51:04 eric 368 367
c better use of extended DSN status codes
e
s 00038/00000/03110
d D 8.152 95/04/21 10:58:07 eric 367 366
c check for .cf files with version extensions
e
s 00001/00001/03109
d D 8.151 95/04/21 09:57:41 eric 366 365
c update copyright notice
e
s 00062/00000/03048
d D 8.150 95/04/07 19:18:39 eric 365 364
c include compile options as text in the object file
e
s 00005/00000/03043
d D 8.149 95/04/05 12:30:24 eric 364 363
c FreeBSD 2.0 cleanup
e
s 00002/00002/03041
d D 8.148 95/03/31 16:57:16 eric 363 362
c simplify prototypes -- works better for older systems
e
s 00001/00000/03042
d D 8.147 95/03/31 16:54:05 eric 362 361
c merge a bit with Sun version
e
s 00001/00001/03041
d D 8.146 95/03/31 15:35:20 eric 361 360
c more type glitching for maximum portability
e
s 00032/00000/03010
d D 8.145 95/03/31 15:05:59 eric 360 359
c add local_hostname_length so Ultrix will link against BIND 4.9
e
s 00005/00009/03005
d D 8.144 95/03/31 14:16:26 eric 359 358
c fix some typos
e
s 00043/00016/02971
d D 8.143 95/03/31 10:52:22 eric 358 357
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00010/00002/02977
d D 8.142 95/03/29 09:53:50 eric 357 356
c preliminary code to allow automatic checking of NIS aliases
e
s 00005/00003/02974
d D 8.141 95/03/21 09:27:04 eric 356 355
c new DSN draft
e
s 00003/00005/02974
d D 8.140 95/03/12 17:03:57 eric 355 354
c add userdb map class
e
s 00003/00002/02976
d D 8.139 95/03/10 09:30:45 eric 354 352
c portability fix for ConvexOS
e
s 00002/00000/02357
d D 8.89.1.3 95/03/07 09:48:56 eric 353 350
c have to self-declar h_errno if using BIND 4.9.3 (ugh)
e
s 00003/00003/02975
d D 8.138 95/03/05 12:39:08 eric 352 351
c Solaris 2.4 changes
e
s 00020/00000/02958
d D 8.137 95/03/05 12:21:51 eric 351 349
c add vendor-dependent macro initialization hooks
e
s 00000/00000/02357
d D 8.89.1.2 95/03/01 16:35:56 eric 350 347
i 349
c hacks to local getopt to avoid link problems with Linux
e
s 00002/00002/02956
d D 8.136 95/03/01 16:35:06 eric 349 348
c hacks to local getopt to avoid link problems with Linux
e
s 00000/00000/02958
d D 8.135 95/02/28 13:37:22 eric 348 346
i 347
c don't require /SENDMAIL/ANY/SHELL/ for null pw_shell entries
e
s 00006/00000/02351
d D 8.89.1.1 95/02/28 10:58:58 eric 347 301
c multiple glitches in 8.6.10 -- see ../RELEASE_NOTES for details
e
s 00002/00002/02950
d D 8.134 95/02/24 10:01:05 eric 346 345
c add NoRecipientAction; make Bcc: field truncate instead of delete
e
s 00006/00006/02946
d D 8.133 95/02/24 06:48:17 eric 345 344
c change way statfs.f_bavail is handled to be more general
e
s 00015/00001/02937
d D 8.132 95/02/23 15:50:35 eric 344 343
c cleanup to make gcc -Winitialized happier
e
s 00004/00003/02934
d D 8.131 95/02/19 07:29:03 eric 343 342
c support for Cray Computer Corp's CSOS
e
s 00025/00001/02912
d D 8.130 95/02/19 06:46:39 eric 342 341
c HP-UX specific load average computation (works for multiprocessor;
c undocumented in HP-UX 9.0)
e
s 00007/00003/02906
d D 8.129 95/02/10 14:48:54 eric 341 340
c refuse connections if there isn't enough disk space on the
c queue partition
e
s 00001/00001/02908
d D 8.128 95/01/30 11:29:55 eric 340 339
c #ifdef NAMED_BIND => #if
e
s 00057/00001/02852
d D 8.127 95/01/26 11:06:52 eric 339 338
c add several new map types; beginnings of hosts switched lookup
e
s 00023/00007/02830
d D 8.126 95/01/07 13:29:12 eric 338 337
c AIX fixes
e
s 00001/00001/02836
d D 8.125 95/01/04 16:32:36 eric 337 336
c SVR4 statvfs fix
e
s 00001/00001/02836
d D 8.124 94/12/28 07:31:55 eric 336 335
c portability fixes for Amdahl UTS System V 2.1.5
e
s 00001/00001/02836
d D 8.123 94/12/05 14:06:30 eric 335 334
c patches for Altos System V
e
s 00002/00002/02835
d D 8.122 94/11/27 10:17:32 eric 334 333
c prog and *file* mailers need "o" flag for V6 configs
e
s 00002/00002/02835
d D 8.121 94/11/22 13:33:45 eric 333 332
c don't close seq maps -- this causes double-closes
e
s 00001/00001/02836
d D 8.120 94/11/22 09:35:45 eric 332 331
c "switch" class is not rebuildable -- only the underlying types are
e
s 00007/00000/02830
d D 8.119 94/11/22 08:18:31 eric 331 330
c IRIX64 and DG-UX updates
e
s 00046/00028/02784
d D 8.118 94/11/20 20:28:30 eric 330 329
c don't create maps that won't be used -- there is too much
c overhead in opening them, and it can cause error messages
e
s 00001/00000/02811
d D 8.117 94/11/19 16:57:46 eric 329 328
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00001/00001/02810
d D 8.116 94/11/13 15:54:37 eric 328 327
c allow map defs without file names in map_parse
e
s 00001/00001/02810
d D 8.115 94/11/13 09:52:44 eric 327 326
c set UseNameServer on the basis of whether "dns" is in the service switch
e
s 00001/00001/02810
d D 8.114 94/11/12 18:24:25 eric 326 325
c allow dotted option names
e
s 00007/00004/02804
d D 8.113 94/11/04 08:40:42 eric 325 324
c first cut at DSN implementation
e
s 00001/00001/02807
d D 8.112 94/10/25 17:19:35 eric 324 323
c compile problems on various platforms
e
s 00016/00005/02792
d D 8.111 94/10/24 21:19:20 eric 323 322
c get it to compile on other environments
e
s 00246/00002/02551
d D 8.110 94/10/24 18:32:36 eric 322 321
c first cut at service switch abstraction
e
s 00017/00000/02536
d D 8.109 94/10/23 14:53:35 eric 321 320
c set VendorCode
e
s 00080/00015/02456
d D 8.108 94/10/23 14:19:14 eric 320 319
c first cut at NeXT NetInfo map class -- still somewhat crude
e
s 00006/00000/02465
d D 8.107 94/10/18 06:37:52 eric 319 318
c add hesiod changes
e
s 00002/00005/02463
d D 8.106 94/10/17 11:08:32 eric 318 317
c "host" map class works even without DNS_BIND
e
s 00016/00001/02452
d D 8.105 94/10/16 18:57:20 eric 317 316
c debug output in shouldqueue()
e
s 00002/00000/02451
d D 8.104 94/10/08 09:22:27 eric 316 315
c fixes for various picky compilers
e
s 00036/00033/02415
d D 8.103 94/09/09 16:47:22 eric 315 314
c change setproctitle definitions to use SPT_TYPE variable a la
c SFS_TYPE and LA_TYPE; this allows for a cleaner integration of new types
e
s 00065/00009/02383
d D 8.102 94/08/21 15:23:36 eric 314 313
c new map classes in preparation for service abstraction; multiple
c queue timeouts
e
s 00029/00028/02363
d D 8.101 94/08/17 08:10:02 eric 313 312
c add H_CTE for content-transfer-encoding; don't output it when you
c are going to be doing 8to7 bit MIME translation, which will add one
e
s 00008/00000/02383
d D 8.100 94/08/09 07:56:18 eric 312 311
c setproctitle updates for AIX
e
s 00000/00013/02383
d D 8.99 94/08/07 16:15:17 eric 311 310
c make BrokenSmtpPeers a runtime option
e
s 00002/00001/02394
d D 8.98 94/07/23 07:59:52 eric 310 309
c MIME 8 to 7 bit support
e
s 00003/00009/02392
d D 8.97 94/07/03 11:48:33 eric 309 308
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00001/00001/02400
d D 8.96 94/07/02 07:25:43 eric 308 307
c fix freespace() computation on Ultrix
e
s 00003/00001/02398
d D 8.95 94/06/27 08:36:23 eric 307 306
c explicitly declare h_errno -- not declared in BIND 4.9.3?
e
s 00015/00005/02384
d D 8.94 94/06/25 08:40:20 eric 306 305
c relax chownsafe rules a bit
e
s 00002/00002/02387
d D 8.93 94/06/19 11:13:37 eric 305 304
c generalize nlist value masking
e
s 00030/00000/02359
d D 8.92 94/06/19 07:34:17 eric 304 303
c avoid denial-of-service attacks caused by setting resource limits
c low before calling sendmail
e
s 00003/00002/02356
d D 8.91 94/06/19 06:37:09 eric 303 302
c portability fixes for DG/UX 5.4.3
e
s 00009/00002/02349
d D 8.90 94/05/17 08:10:45 eric 302 301
c portability for System V Release 4
e
s 00001/00000/02350
d D 8.89 94/04/18 15:30:08 eric 301 300
c fix UNIXWARE
e
s 00005/00005/02345
d D 8.88 94/04/14 10:43:09 eric 300 299
c fix possible compile probelem with FSHIFT
e
s 00001/00000/02349
d D 8.87 94/04/14 09:40:52 eric 299 298
c add "noreceipts" privacy flag
e
s 00004/00001/02345
d D 8.86 94/04/12 15:42:11 eric 298 297
c IRIX cleanup
e
s 00011/00003/02335
d D 8.85 94/04/12 09:01:01 eric 297 296
c UnixWare changes
e
s 00020/00000/02318
d D 8.84 94/04/12 08:38:34 eric 296 295
c updates for Intergraph CLIX
e
s 00001/00001/02317
d D 8.83 94/04/12 08:20:32 eric 295 294
c updates for picky C compilers
e
s 00009/00012/02309
d D 8.82 94/03/06 09:31:13 eric 294 293
c have Linux getla() not hold the file open
e
s 00001/00003/02320
d D 8.81 94/03/05 11:49:30 eric 293 292
c Linux portability changes
e
s 00003/00003/02320
d D 8.80 94/03/05 10:17:48 eric 292 291
c more Linux changes
e
s 00053/00000/02270
d D 8.79 94/03/03 08:35:11 eric 291 290
c Linux portability changes; add LA_PROCSTR
e
s 00001/00003/02269
d D 8.78 94/02/21 07:10:34 eric 290 289
c DomainOS updates
e
s 00088/00030/02184
d D 8.77 94/02/19 08:41:49 eric 289 288
c replace strtol implementation with one that works
e
s 00012/00004/02202
d D 8.76 94/02/14 10:53:55 eric 288 287
c avoid linking fpathconf if not necessary
e
s 00049/00000/02157
d D 8.75 94/02/10 09:06:28 eric 287 286
c portability fix for Apollo
e
s 00001/00001/02156
d D 8.74 94/02/06 19:32:30 eric 286 285
c fix minor compile glitch
e
s 00003/00000/02154
d D 8.73 94/02/06 19:29:11 eric 285 284
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00003/00000/02151
d D 8.72 94/02/05 11:15:20 eric 284 283
c add error if SETPROCTITLE and HASSETPROCTITLE are both set
e
s 00004/00000/02147
d D 8.71 94/02/03 08:07:13 eric 283 282
c portability fixes for BSD/386 and Solaris 2.3
e
s 00001/00001/02146
d D 8.70 94/02/02 17:46:36 eric 282 281
c fix botch in HP-UX version of chownsafe -- condition reversed
e
s 00001/00001/02146
d D 8.69 94/02/01 08:23:53 eric 281 280
c HP-UX fixes
e
s 00001/00001/02146
d D 8.68 94/01/31 17:00:51 eric 280 279
c fix hpux compile flag
e
s 00051/00000/02096
d D 8.67 94/01/31 16:59:53 eric 279 278
c cleanup of _POSIX_CHOWN_RESTRICTED stuff
e
s 00001/00001/02095
d D 8.66 94/01/22 16:12:23 eric 278 277
c make HASFLOCK a 0/1 definition so Linux can turn it off
e
s 00002/00002/02094
d D 8.65 94/01/22 08:59:45 eric 277 276
c Apollo & NeXT portability fixes
e
s 00023/00018/02073
d D 8.64 94/01/15 12:37:02 eric 276 275
c change method of declaring statfs(2) functionality
e
s 00004/00002/02087
d D 8.63 94/01/15 09:20:19 eric 275 274
c change shell wildcard convention to start with leading slash
e
s 00030/00009/02059
d D 8.62 94/01/09 11:09:45 eric 274 273
c HP-UX compatibility: use correct /etc/shells default
e
s 00034/00000/02034
d D 8.61 94/01/05 10:20:12 eric 273 272
c syslog portability for HP-UX; fix typo for OSF/1 pid file
e
s 00002/00002/02032
d D 8.60 94/01/05 09:20:54 eric 272 271
c allow * in /etc/shells to match anything
e
s 00007/00003/02027
d D 8.59 94/01/03 09:31:11 eric 271 270
c Convex portability
e
s 00001/00001/02029
d D 8.58 93/12/27 14:54:50 eric 270 269
c minor comment typo
e
s 00123/00000/01907
d D 8.57 93/12/26 08:40:23 eric 269 268
c add NeXT NetInfo support
e
s 00051/00126/01856
d D 8.56 93/12/26 06:07:54 eric 268 267
c clean up implementation if you don't have getusershell(3) in libc
e
s 00001/00001/01981
d D 8.55 93/12/24 10:11:56 eric 267 266
c make NEEDGETUSERSHELL a 0/1 flag instead of a def/ndef flag
e
s 00145/00000/01837
d D 8.54 93/12/24 07:57:04 eric 266 265
c go ahead and actually implement getusershell in compat mode; too many
c systems don't have it
e
s 00006/00002/01831
d D 8.53 93/12/18 05:57:25 eric 265 264
c NEXTSTEP 3.x compatibility changes
e
s 00003/00003/01830
d D 8.52 93/12/16 05:38:52 eric 264 263
c adjust declaration of getopt for ANSI C compilers
e
s 00002/00002/01831
d D 8.51 93/12/11 17:31:09 eric 263 262
c Solaris compiler fixes
e
s 00001/00000/01832
d D 8.50 93/12/02 15:58:18 eric 262 261
c Solaris portability
e
s 00004/00000/01828
d D 8.49 93/12/01 14:31:04 eric 261 259
c solaris portability -- proper declarations
e
s 00004/00000/01828
d R 8.49 93/12/01 14:27:11 eric 260 259
c minor typos
e
s 00012/00001/01816
d D 8.48 93/11/20 07:15:05 eric 259 258
c clarify setvendor()
e
s 00001/00001/01816
d D 8.47 93/11/17 10:07:18 eric 258 257
c portability for AIX
e
s 00006/00001/01811
d D 8.46 93/11/14 08:26:20 eric 257 256
c make proctitle padding adjustable
e
s 00042/00000/01770
d D 8.45 93/11/14 07:49:58 eric 256 254
c Solaris portability fixes
e
s 00042/00000/01770
d R 8.45 93/11/14 07:49:12 eric 255 254
c Solaris portability changes
e
s 00003/00001/01767
d D 8.44 93/11/08 14:26:00 eric 254 253
c add argc & argv to init_md call to enhance extensibility
e
s 00048/00001/01720
d D 8.43 93/11/08 09:45:20 eric 253 252
c portability changes for MACH386
e
s 00002/00000/01719
d D 8.42 93/10/21 12:28:13 eric 252 251
c fix errno race condition
e
s 00058/00002/01661
d D 8.41 93/10/15 08:34:58 eric 251 250
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00020/00003/01643
d D 8.40 93/10/08 15:54:54 eric 250 249
c 8.6.1: A/UX and Encore UMAX V patches; fix to not toss error messages
c too early
e
s 00001/00001/01645
d D 8.39 93/09/30 07:21:00 eric 249 248
c re-enable Return-Receipt-To:
e
s 00019/00000/01627
d D 8.38 93/09/24 07:14:22 eric 248 247
c hooks for future features
e
s 00002/00002/01625
d D 8.37 93/09/22 10:03:08 eric 247 246
c compile cleanup on various systems (mostly AUX)
e
s 00013/00001/01614
d D 8.36 93/09/22 09:02:50 eric 246 245
c get sendmail.cf name from a routine (so it can autoconfigure on NeXt)
e
s 00000/00002/01615
d D 8.35 93/09/19 19:23:23 eric 245 244
c NeXT portability changes; cleanup of <sys/wait.h> assumptions
e
s 00005/00000/01612
d D 8.34 93/09/04 12:34:27 eric 244 243
c allocate trace flag to checkcompat()
e
s 00001/00001/01611
d D 8.33 93/09/02 17:15:08 eric 243 242
c fix syntax problem
e
s 00002/00002/01610
d D 8.32 93/09/02 09:44:54 eric 242 241
c AUX compatibility
e
s 00022/00004/01590
d D 8.31 93/09/02 07:43:44 eric 241 240
c more checks for lock syserr failure
e
s 00004/00002/01590
d D 8.30 93/08/30 12:36:29 eric 240 239
c report more information on failed file locks
e
s 00010/00005/01582
d D 8.29 93/08/26 08:39:56 eric 239 238
c add LA_SHORT for SCO UNIX (ugh)
e
s 00001/00001/01586
d D 8.28 93/08/23 09:34:01 eric 238 237
c fix bug in enoughspace
e
s 00001/00001/01586
d D 8.27 93/08/23 08:53:52 eric 237 236
c freespace portability fixes for IRIX
e
s 00014/00006/01573
d D 8.26 93/08/23 08:32:36 eric 236 235
c add "ext" argument to lockfile so you can accurately tell what file
c is being locked in logging/error messages
e
s 00002/00001/01577
d D 8.25 93/08/22 17:07:55 eric 235 234
c add restrictqrun privacy option
e
s 00001/00001/01577
d D 8.24 93/08/22 16:48:36 eric 234 233
c SCO fixes (old bug snuck back in)
e
s 00003/00009/01575
d D 8.23 93/08/21 07:22:58 eric 233 232
c more NeXT portability changes; use initgroups when reading .forward files
e
s 00058/00028/01526
d D 8.22 93/08/20 13:18:30 eric 232 231
c announce amount of actual free space in EHLO SIZE line
e
s 00000/00001/01554
d D 8.21 93/08/20 11:52:05 eric 231 230
c more on elimination of frozen config files
e
s 00033/00000/01522
d D 8.20 93/08/19 07:01:08 eric 230 229
c NeXT load average
e
s 00027/00000/01495
d D 8.19 93/08/15 11:07:32 eric 229 228
c fix problem on Ultrix -- fcntl locking doesn't auto-release locks
c when the file is closed
e
s 00007/00002/01488
d D 8.18 93/08/14 14:54:45 eric 228 227
c react reasonably with negative e_msgsize and SIZE parameter
e
s 00003/00000/01487
d D 8.17 93/08/14 11:29:59 eric 227 226
c BSD/386 (BSDI) support
e
s 00011/00001/01476
d D 8.16 93/08/08 15:08:11 eric 226 225
c POSIX and Linux changes
e
s 00014/00002/01463
d D 8.15 93/08/07 11:58:14 eric 225 224
c work around lockf bug in SunOS
e
s 00001/00002/01464
d D 8.14 93/08/06 21:20:11 eric 224 223
c Solaris and NeXT portability
e
s 00003/00038/01463
d D 8.13 93/07/27 21:38:12 eric 223 222
c portability enhancements: NeXT and SCO
e
s 00028/00012/01473
d D 8.12 93/07/26 09:22:12 eric 222 221
c signal and file locking portability changes
e
s 00004/00004/01481
d D 8.11 93/07/24 08:05:54 eric 221 220
c prefer HASGETDTABLESIZE over _SC_OPEN_MAX: a disturbingly large
c number of systems define _SC_OPEN_MAX in the header files but then
c don't implement the sysconf() syscall.
e
s 00004/00001/01481
d D 8.10 93/07/22 08:42:44 eric 220 219
c SCO UNIX changes
e
s 00001/00002/01481
d D 8.9 93/07/21 20:06:31 eric 219 218
c bulk clear flock structure -- some systems apparently have some
c additional fields that will cause "bad argument" messages
e
s 00125/00000/01358
d D 8.8 93/07/21 11:45:47 eric 218 217
c old 4.3BSD changes
e
s 00001/00001/01357
d D 8.7 93/07/20 19:51:40 eric 217 216
c updates for Convex, NEWS-OS 4.1C (Sony), and UNIOS-B 1.6 (Omron)
e
s 00050/00052/01308
d D 8.6 93/07/20 15:35:46 eric 216 215
c more portability changes, including ConvexOS support
e
s 00002/00002/01358
d D 8.5 93/07/19 20:50:20 eric 215 214
c SGI IRIX & ANSI C portability
e
s 00002/00002/01358
d D 8.4 93/07/16 10:23:23 eric 214 213
c SCO compatibility
e
s 00018/00031/01342
d D 8.3 93/07/13 12:58:48 eric 213 212
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00015/00005/01358
d D 8.2 93/07/11 06:52:51 eric 212 211
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/01361
d D 8.1 93/06/07 10:29:29 bostic 211 210
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/01363
d D 6.63 93/06/05 17:08:12 eric 210 209
c lint-style cleanup
e
s 00010/00007/01354
d D 6.62 93/05/29 03:50:06 eric 209 208
c don't redefine FSHIFT if it is already defined
e
s 00012/00002/01349
d D 6.61 93/05/28 14:43:46 eric 208 207
c catch wierd waitpid infinite loop
e
s 00010/00003/01341
d D 6.60 93/05/22 08:58:05 eric 207 206
c AIX compatibility changes; clean up map initialization functions
e
s 00076/00000/01268
d D 6.59 93/05/21 18:58:12 eric 206 205
c changes to merge alias and map implementations
e
s 00002/00002/01266
d D 6.58 93/05/20 15:40:08 eric 205 204
c compatibility for Sun BSD
e
s 00000/00002/01268
d D 6.57 93/05/17 10:32:50 eric 204 203
c delete unneeded and conflicting errstring declarations
e
s 00000/00092/01270
d D 6.56 93/05/17 10:28:23 eric 203 202
c first cut at merged map/alias implementation
e
s 00004/00002/01358
d D 6.55 93/05/13 10:43:46 eric 202 201
c try to make setproctitle port to NET/bsd and BSD/386 better
e
s 00001/00001/01359
d D 6.54 93/05/11 08:17:29 eric 201 200
c have *file* mailer output all appropriate flags
e
s 00014/00002/01346
d D 6.53 93/05/04 20:41:47 eric 200 199
c adjust setproctitle for 4.4BSD (to avoid problem with warn())
e
s 00001/00001/01347
d D 6.52 93/05/03 19:12:12 eric 199 198
c change option 8 to option 7 (and invert semantics)
e
s 00001/00000/01347
d D 6.51 93/05/03 12:26:28 eric 198 197
c first cut at updated alias implementation
e
s 00005/00003/01342
d D 6.50 93/04/28 12:26:28 eric 197 196
c add hooks to allow unlocking
e
s 00004/00007/01341
d D 6.49 93/04/27 18:47:47 eric 196 195
c compile flag hpux ==> __hpux
e
s 00001/00000/01347
d D 6.48 93/04/27 07:03:00 eric 195 194
c add x400-received to list of H_TRACE fields
e
s 00014/00000/01333
d D 6.47 93/04/26 16:08:46 eric 194 193
c clean up setsid handling
e
s 00008/00000/01325
d D 6.46 93/04/21 12:52:24 eric 193 192
c HPUX compatibility changes in getla()
e
s 00005/00000/01320
d D 6.45 93/04/18 10:07:25 eric 192 191
c Extended Load Average (XLA) hooks
e
s 00001/00001/01319
d D 6.44 93/03/29 12:45:19 eric 191 190
c default PrivacyFlags to zero (.cf file can only set flags)
e
s 00018/00009/01302
d D 6.43 93/03/25 09:12:27 eric 190 189
c add dequote pseudo-map
e
s 00008/00000/01303
d D 6.42 93/03/23 19:50:57 eric 189 188
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00003/00001/01300
d D 6.41 93/03/23 18:06:41 eric 188 187
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00004/00001/01297
d D 6.40 93/03/19 11:46:47 eric 187 186
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00003/00003/01295
d D 6.39 93/03/19 09:06:21 eric 186 185
c if you are su'ed to root, send email as who you are, not as root
e
s 00005/00004/01293
d D 6.38 93/03/19 08:51:06 eric 185 184
c move SendMode and ErrorMode into the envelope
e
s 00001/00001/01296
d D 6.37 93/03/17 13:02:04 eric 184 183
c minor glitch -- add paren
e
s 00071/00001/01226
d D 6.36 93/03/17 09:55:27 eric 183 182
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00000/00000/01227
d D 6.35 93/03/14 08:31:26 eric 182 181
x 181
c back out setproctitle changes; they trash argv before everything
c has been properly saved
e
s 00024/00013/01214
d D 6.34 93/03/13 22:48:30 eric 181 180
c allow push/pop setproctitle
e
s 00100/00000/01127
d D 6.33 93/03/07 16:16:14 eric 180 179
c use transienterror() all places where we do this sort of mapping
e
s 00004/00001/01123
d D 6.32 93/03/02 14:26:48 eric 179 178
c portability updates, mostly ultrix
e
s 00020/00009/01104
d D 6.31 93/03/01 12:44:05 eric 178 177
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00000/00001/01113
d D 6.30 93/03/01 06:53:44 eric 177 176
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00001/00000/01113
d D 6.29 93/02/26 08:20:27 eric 176 175
c add restrictmailq privacy flag
e
s 00001/00001/01112
d D 6.28 93/02/23 14:12:48 eric 175 174
c fix botch on #if line
e
s 00024/00020/01089
d D 6.27 93/02/23 10:09:59 eric 174 173
c make HASUSTAT more consistent
e
s 00018/00001/01091
d D 6.26 93/02/23 09:00:04 eric 173 172
c more System V compatibility changes (ugh)
e
s 00002/00012/01090
d D 6.25 93/02/23 06:31:59 eric 172 171
c overhaul status of SMTP reply codes
e
s 00029/00002/01073
d D 6.24 93/02/21 14:34:16 eric 171 170
c generalize enoughspace -- fixes from Eric Wassenaar again
e
s 00003/00001/01072
d D 6.23 93/02/21 14:12:33 eric 170 169
c clean up shouldqueue function
e
s 00004/00004/01069
d D 6.22 93/02/21 12:07:15 eric 169 168
c use bavail (non-superuser available) instead of bfree (superuser avail)
e
s 00001/00001/01072
d D 6.21 93/02/21 10:37:18 eric 168 167
c spelling error
e
s 00002/00002/01071
d D 6.20 93/02/21 09:56:20 eric 167 166
c generalize read timeout
e
s 00007/00000/01066
d D 6.19 93/02/20 14:21:26 eric 166 165
c syslog when low on disk space
e
s 00065/00000/01001
d D 6.18 93/02/20 13:46:50 eric 165 164
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00022/00000/00979
d D 6.17 93/02/19 16:15:10 eric 164 163
c let HPUX use initgroups; -DHASINITGROUPS if you have one
e
s 00003/00000/00976
d D 6.16 93/02/19 09:21:32 eric 163 162
c fix a variety of bugs found by Eric Wassenaar <e07@nikhef.nl>
e
s 00002/00002/00974
d D 6.15 93/02/18 20:22:41 eric 162 161
c move the meta-characters from C0 into C1 space
e
s 00010/00004/00966
d D 6.14 93/02/14 14:41:48 eric 161 160
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00002/00002/00968
d D 6.13 93/02/12 11:51:30 eric 160 159
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00062/00006/00908
d D 6.12 93/01/28 10:15:58 eric 159 158
c System 5 compatibility, misc fixes
e
s 00008/00005/00906
d D 6.11 93/01/22 17:20:15 eric 158 157
c fix -e compat flag; a few compilation warnings; improve error messages
e
s 00006/00002/00905
d D 6.10 93/01/21 15:18:55 eric 157 156
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00059/00000/00848
d D 6.9 93/01/20 13:22:05 eric 156 155
c fix problem with address delimitor inside quotes; define $k and $=k
c to be the name (from the uname call)
e
s 00003/00005/00845
d D 6.8 93/01/10 13:23:45 eric 155 154
c change checkcompat() to return an exit status
e
s 00004/00004/00846
d D 6.7 93/01/10 12:56:55 eric 154 153
c MX piggybacking, based on code from John Myers@CMU; allow checkcompat
c to return -1 to mean tempfail; bug fix in m_mno computation
e
s 00023/00017/00827
d D 6.6 93/01/09 14:45:44 eric 153 152
c tuning of queueing functions as recommended by John Gardiner Myers
c <jgm+@CMU.EDU>; return mail headers (no body) on messages with negative
c precedence; minor other bug fixes
e
s 00003/00000/00841
d D 6.5 93/01/02 14:18:18 eric 152 151
c define prog mailer by default
e
s 00014/00000/00827
d D 6.4 93/01/02 14:00:10 eric 151 150
c changes to recognize special mailer types (e.g., file) early
e
s 00004/00004/00823
d D 6.3 93/01/01 13:09:04 eric 150 149
c don't malloc before calling thaw
e
s 00002/00002/00825
d D 6.2 92/12/30 11:00:58 eric 149 148
c put return-receipt-to on a conf.c flag (but don't set it);
c fix minor syslog problem
e
s 00000/00000/00827
d D 6.1 92/12/21 16:08:52 eric 148 147
c Release 6
e
s 00000/00001/00827
d D 5.49 92/12/20 11:14:27 eric 147 146
c change random constants to be #defines
e
s 00012/00000/00816
d D 5.48 92/12/18 12:03:19 eric 146 145
c add NIS map type; log message-id in same line as from logging
e
s 00002/00002/00814
d D 5.47 92/12/16 16:41:13 eric 145 144
c tweak some of the configurations to up some values
e
s 00007/00003/00809
d D 5.46 92/11/16 17:52:20 eric 144 143
c make it use varargs/stdarg and vsprintf
e
s 00038/00009/00774
d D 5.45 92/11/15 19:24:47 eric 143 142
c allow specification of arbitrary string on successful db match
e
s 00006/00006/00777
d D 5.44 92/11/15 16:11:04 eric 142 141
c finish support for generalized maps
e
s 00004/00004/00779
d D 5.43 92/11/14 11:34:37 eric 141 140
c (partially) ANSI-fy it
e
s 00025/00000/00758
d D 5.42 92/09/09 06:56:46 eric 140 139
c miscellaneous bug fixes from Bryan Costales and Craig Lant
e
s 00041/00000/00717
d D 5.41 92/07/20 08:03:18 eric 139 138
c portability changes
e
s 00003/00002/00714
d D 5.40 92/07/12 14:10:02 eric 138 137
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00715
d D 5.39 92/07/12 12:47:43 eric 137 136
c fix botch in filling out to LastArgv
e
s 00011/00008/00705
d D 5.38 92/07/12 12:34:49 eric 136 135
c change setproctitle so it will print sendmail: in 4.4bsd
e
s 00002/00000/00711
d D 5.37 92/07/11 18:51:55 eric 135 134
c open connection caching
e
s 00076/00003/00635
d D 5.36 92/05/25 13:13:42 eric 134 133
c add generalized database mapping (using the K config line and
c $( ... $) syntaxes); $[ ... $] is now a special case
e
s 00021/00000/00617
d D 5.35 92/03/20 22:33:08 eric 133 132
c reject connections more quickly if load average goes up;
c try to time out on opens of .forward files on hung filesystems
e
s 00000/00005/00617
d D 5.34 92/01/05 09:21:46 eric 132 131
c clean up #ifdef configuration to more cleanly match the modern age
e
s 00001/00000/00621
d D 5.33 92/01/04 15:33:23 eric 131 130
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00002/00000/00619
d D 5.32 92/01/04 11:47:52 eric 130 129
c include defaults for SendMode and ErrorMode; never ignore single dot
c termination when collecting message in SMTP mode.
e
s 00071/00016/00548
d D 5.31 91/12/14 12:37:03 eric 129 128
c fix race condition in queue file locking; generalize getla
e
s 00022/00013/00542
d D 5.30 91/11/20 16:37:52 eric 128 127
c don't assume getloadavg exists
e
s 00001/00000/00554
d D 5.29 91/10/03 14:39:05 eric 127 126
c some changes to enhance compatibility with SunOS sendmail
e
s 00001/00000/00553
d D 5.28 91/03/12 17:30:53 eric 126 125
c k option specifies checkpoint interval (default 10);
c qf file is rewritten after k successful deliveries.
c (ref bug 4.3BSD-reno/usr.bin/10)
e
s 00003/00003/00550
d D 5.27 91/03/02 17:15:14 bostic 125 124
c ANSI
e
s 00001/00011/00552
d D 5.26 90/06/01 19:00:41 bostic 124 123
c new copyright notice
e
s 00005/00004/00558
d D 5.25 90/04/19 16:55:33 bostic 123 122
c allocate space for pw_name; bug report 4.3BSD-tahoe/usr.sbin/10
e
s 00003/00002/00559
d D 5.24 90/04/19 10:02:47 bostic 122 121
c move pathnames into pathnames.h
e
s 00019/00000/00542
d D 5.23 90/04/18 13:54:26 bostic 121 120
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00001/00000/00541
d D 5.22 90/04/16 12:00:20 rick 120 119
c forgot an extern int la; for load avarage.
e
s 00003/00003/00538
d D 5.21 90/04/16 08:06:37 rick 119 118
c dont recalculate load average for EVERY job in the queue
e
s 00013/00017/00528
d D 5.20 89/05/29 17:56:55 mckusick 118 117
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00002/00002/00543
d D 5.19 89/05/11 14:12:33 bostic 117 116
c file reorg, pathnames.h, paths.h
e
s 00001/00003/00544
d D 5.18 89/02/27 09:16:39 bostic 116 115
c add types.h for pwd.h
e
s 00011/00009/00536
d D 5.17 88/06/30 14:58:27 bostic 115 114
c install approved copyright notice
e
s 00001/00165/00544
d D 5.16 88/04/01 16:50:40 bostic 114 113
c remove V6 #ifdefs
e
s 00016/00010/00693
d D 5.15 88/03/13 19:51:37 bostic 113 112
c add Berkeley specific header
e
s 00001/00001/00702
d D 5.14 86/01/10 16:33:45 eric 112 111
c adjust WkTimeFact so that -q1h will lower relative priorities of
c jobs over long periods, rather than leave them toward the top of the queue
e
s 00031/00000/00672
d D 5.13 86/01/05 19:56:34 eric 111 110
m 
c cleanup for various compilation flags and reasonable organization
e
s 00002/00000/00670
d D 5.12 86/01/05 18:47:52 eric 110 109
m 
c rewrite reply-to and resent-reply-to; save errorqueueu in qf file;
c some performance hacking; some alias handling cleanup; delete leading
c spaces from SMTP lines
e
s 00001/00000/00669
d D 5.11 85/12/17 23:52:53 eric 109 108
m 
c lint
e
s 00012/00005/00657
d D 5.10 85/09/30 21:06:00 eric 108 107
m 
c fixes in setproctitle to avoid problems with titles longer than
c argv + env
e
s 00000/00000/00662
d D 5.9 85/09/24 15:09:33 eric 107 106
m 
c don't step on user environment
e
s 00001/00001/00661
d D 5.8 85/09/21 15:51:58 eric 106 105
m 
c change sign on WkTimeFact so that is closer to what most people want
e
s 00006/00000/00656
d D 5.7 85/09/21 14:44:24 eric 105 104
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00000/00000/00656
d D 5.6 85/09/19 01:25:15 eric 104 102
i 103
m 
c incorporate SMI changes -- still experimental
e
s 00102/00004/00553
d D 5.3.1.1 85/09/19 00:55:24 eric 103 100
m 
c SMI changes (somewhat)
e
s 00002/00002/00556
d D 5.5 85/08/13 18:20:25 miriam 102 101
m 
c Correct error check for lseek as kernel memory is a negative binary value.
e
s 00002/00001/00556
d D 5.4 85/07/31 10:47:53 miriam 101 100
m 
c Make sure getpwuid returns a valid entry before setting myname.
e
s 00003/00027/00554
d D 5.3 85/06/08 10:27:23 eric 100 99
m 
c lint for 4.3 release
e
s 00000/00004/00581
d D 5.2 85/06/07 22:01:37 miriam 99 98
m 
c Resolve duplicate SccsId
e
s 00014/00000/00571
d D 5.1 85/06/07 14:34:54 dist 98 97
m 
c Add copyright
e
s 00006/00002/00565
d D 4.9 85/05/06 20:05:00 eric 97 96
m 
c check syscall return values in a few questions; thanks go to Ian Darwin's
c rudely public ragging on this one.
e
s 00006/00006/00561
d D 4.8 85/05/01 21:23:37 miriam 96 95
m 
c slight rearrangement for efficency
e
s 00010/00000/00557
d D 4.7 85/05/01 16:44:09 miriam 95 94
m 
c Correct for the getlogin problem in username()
e
s 00046/00001/00511
d D 4.6 84/12/05 23:14:07 eric 94 93
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00003/00003/00509
d D 4.5 84/08/11 14:56:30 eric 93 92
m 
c pull configurable vars out of initialized data for freeze files
e
s 00004/00000/00508
d D 4.4 83/08/28 15:37:15 eric 92 91
m 
c set FIOCLEX on /dev/kmem file when getting load average
e
s 00002/00002/00506
d D 4.3 83/08/28 14:59:54 eric 91 90
m 
c Change QueueLA and RefuseLA to 8 and 12 respectively
e
s 00055/00001/00453
d D 4.2 83/08/28 14:43:08 eric 90 89
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00000/00000/00454
d D 4.1 83/07/25 19:43:58 eric 89 88
m 
c 4.2 release version
e
s 00004/00000/00450
d D 3.71 83/04/30 15:11:59 eric 88 87
m 
c lint
e
s 00010/00005/00440
d D 3.70 83/03/06 16:31:01 eric 87 86
m 201
c Handle messages with "Resent-xxx:" header lines properly (basically mark
c the message as being resent); ignore incoming From: lines if their text
c exactly matches our machine-readable address exactly -- this causes the
c full name to be added when called from (e.g.) MH.  Both of these mode are
c to improve interaction with MH.
e
s 00000/00045/00445
d D 3.69 83/02/08 10:50:56 eric 86 85
m 167
m 172
m 173
m 174
c clean up problems when QUEUE compile flag not defined; clean up hostname
c code to run on non-4.1c systems; fix use of -oeq (quiet on errors) flag.
e
s 00004/00010/00486
d D 3.68 83/02/03 07:53:21 eric 85 84
m 168
c Make mailer size limits a per-mailer parameter (M field in the mailer
c descriptor)
e
s 00021/00012/00475
d D 3.67 83/02/02 12:51:46 eric 84 83
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00036/00000/00451
d D 3.66 83/01/17 21:41:23 eric 83 82
m 158
c Set the $w macro to the hostname if at all possible to allow generic
c configuration tables.
e
s 00061/00002/00390
d D 3.65 82/11/28 00:18:23 eric 82 81
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00002/00002/00390
d D 3.64 82/11/17 09:34:03 eric 81 80
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00003/00003/00389
d D 3.63 82/11/05 13:12:28 eric 80 79
m 062
c arrange to freeze the configuration file for quick startup -- this
c technique requires reprocessing the argv so that flag settings don't
c get lost, and is really rather of a hack.
e
s 00019/00028/00373
d D 3.62 82/11/04 13:26:42 eric 79 78
m 037
c put header conditionals into the .cf file
e
s 00006/00000/00395
d D 3.61 82/11/03 09:47:56 eric 78 77
m 049
c Arrange to strip quote bits in message header; move SPACESUB into
c conf.c; change SpaceSub to unquoted dot
e
s 00002/00002/00393
d D 3.60 82/10/27 20:43:43 eric 77 76
m 044
c strip out bcc: and resent-bcc: always
e
s 00000/00035/00395
d D 3.59 82/09/26 17:03:58 eric 76 75
c Put more configuration into setoption; merge some of the argv processing
c with this; move configuration information out of conf.c into the .cf
c file.  Since a lot of stuff will default to zero, a new .cf file is
c required.
e
s 00001/00000/00429
d D 3.58 82/09/26 14:45:04 eric 75 74
c completely instantiate queue files for all mail, even if not needed;
c fix a bug that would probably come up once every ten years in creating
c the queue id.  should merge argv flag processing with option processing.
e
s 00001/00001/00428
d D 3.57 82/09/24 09:37:23 eric 74 73
c arrange to be able to define options; put precedences in .cf file;
c send errors to an Errors-To: field; fix a serious bug causing mail
c to not be delivered to anyone if there were any errors.
e
s 00026/00012/00403
d D 3.56 82/09/05 18:00:25 eric 73 72
c correctly process all sender fields; clean up sender processing code
e
s 00004/00003/00411
d D 3.55 82/08/29 15:52:00 eric 72 71
c give 554 message on syserr (instead of 451) if errno == 0; as it
c was some permanent errors appeared transient
e
s 00000/00001/00414
d D 3.54 82/08/23 11:58:32 eric 71 70
c clean up queueing; log time in queue.
c **** This delta invalidates mqueue files ****
e
s 00001/00001/00414
d D 3.53 82/08/17 20:44:31 eric 70 69
c Mail-From: ==> Received: for new SMTP spec (RFC821)
e
s 00001/00001/00414
d D 3.52 82/08/15 17:31:38 eric 69 68
c mark From: lines with a bit; this should be used later instead of a
c direct strcmp with "from"
e
s 00001/00001/00414
d D 3.51 82/08/08 16:53:36 eric 68 67
c change default log level to 9
e
s 00003/00002/00412
d D 3.50 82/08/08 00:38:36 eric 67 66
c don't delete bcc: lines; force message-id output; default logging level
e
s 00001/00000/00413
d D 3.49 82/07/05 20:52:48 eric 66 65
c improve configuration on timeout
e
s 00004/00003/00409
d D 3.48 82/07/05 12:02:24 eric 65 64
c put timeouts on net reads
e
s 00002/00002/00410
d D 3.47 82/05/31 17:10:15 eric 64 63
c eliminate -V, -D, -p flags in favor of a single flag "-bx"
c (be in mode x).
e
s 00002/00002/00410
d D 3.46 82/05/22 01:36:06 eric 63 62
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00000/00002/00412
d D 3.45 82/05/05 20:42:59 glickman 62 61
c Removed whoami.h.
e
s 00001/00001/00413
d D 3.44 82/03/22 22:12:21 eric 61 60
c 16 bit fixes
e
s 00005/00005/00409
d D 3.43 82/02/20 19:15:21 eric 60 59
c make rewriting of addresses in headers really work.  This adds the $q
c macro.  The rewriting of the From: address is still ad hoc and should
c be integrated into this format.
c Note:  old .cf files will not work with this version.
e
s 00001/00001/00413
d D 3.42 81/12/06 12:37:20 eric 59 58
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00001/00000/00413
d D 3.41 81/12/05 14:13:35 eric 58 57
c insert SMTP "Mail-From:" line.
e
s 00004/00000/00409
d D 3.40 81/12/05 11:52:48 eric 57 56
c put the SMTP and queueing code on compilation flags so that sendmail
c will fit on non-ID PDP-11's (ugh); put the ugly UUCP hack on a
c compilation flag also to emphasize that it sucks eggs; makefile
c cleanup.
e
s 00001/00001/00408
d D 3.39 81/11/07 15:41:02 eric 56 55
c clean up to compile & work on ARPAVAX; move stat file to
c /usr/lib/sendmail.st; fix bug in syserr with error codes
e
s 00002/00015/00407
d D 3.38 81/10/31 22:11:27 eric 55 54
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00005/00000/00417
d D 3.37 81/10/26 14:21:13 eric 54 53
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00002/00002/00415
d D 3.36 81/10/23 19:36:50 eric 53 52
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00002/00001/00415
d D 3.35 81/10/22 10:25:19 eric 52 51
c move stats file to /usr/lib; put location of sendmail.hf in conf.c
e
s 00008/00002/00408
d D 3.34 81/10/17 16:57:29 eric 51 50
c initial prep to put in Daemon mode
e
s 00001/00001/00409
d D 3.33 81/09/24 10:52:31 eric 50 49
c fix botch in ING70 code
e
s 00011/00000/00399
d D 3.32 81/09/24 10:30:15 eric 49 47
c changes to work under a V6 system -- mostly compilation flags
e
s 00001/00006/00393
d D 3.31.1.1 81/09/23 18:22:44 eric 48 47
c break some configuration into conf.h -- simplifies makefile changes
c on different machines.  But there are still conditional libraries, so
c this may not be a good idea.....
e
s 00008/00000/00391
d D 3.31 81/09/20 10:46:08 eric 47 46
c don't let a mailer ever execute as root (that should solve the
c security problems!) -- essentially just map root into someone else.
c Adds yet another configuration variable (should this be in the .cf file?
e
s 00001/00001/00390
d D 3.30 81/09/12 15:48:18 eric 46 45
c change From: processing to reduce the number of Original-From:
c lines; change allocation of global variables.
e
s 00076/00000/00315
d D 3.29 81/09/07 14:12:11 eric 45 44
c fix up umask; allow setuid on files to take recipient owner;
c factor some configuration info into conf.c
e
s 00015/00000/00300
d D 3.28 81/09/06 19:47:42 eric 44 43
c cleanup, commenting, linting, etc.
e
s 00009/00006/00291
d D 3.27 81/09/01 11:43:16 eric 43 42
c add "suppress return-to-sender" function
e
s 00012/00000/00285
d D 3.26 81/08/31 21:21:02 eric 42 41
c collect mail statistics; change minor configuration
e
s 00003/00003/00282
d D 3.25 81/08/29 19:15:28 eric 41 40
c drop unneccessary H_FORCE bits
e
s 00002/00002/00283
d D 3.24 81/08/29 19:13:08 eric 40 39
c delete H_DELETE -- can be simulated with H_ACHECK
e
s 00003/00003/00282
d D 3.23 81/08/24 14:05:15 eric 39 38
c Add "-t" option to read To:, Cc:, and Bcc: lines to get recipients
e
s 00001/00000/00284
d D 3.22 81/08/22 17:51:38 eric 38 37
c Arrange to pull full name out of From line if found; includes
c Original-From: hacking (oh so ugly).  There's got to be a better way
c to do this...
e
s 00002/00002/00282
d D 3.21 81/08/21 18:17:44 eric 37 36
c drop M_FINAL, change some other defined constant names
e
s 00011/00039/00273
d D 3.20 81/08/21 16:44:51 eric 36 35
c add the $y macro as the tty name.
e
s 00000/00001/00312
d D 3.19 81/08/20 15:13:07 eric 35 34
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00022/00000/00291
d D 3.18 81/08/18 17:12:20 eric 34 33
c factor out ARPANET FTP reply codes into conf.c
e
s 00023/00017/00268
d D 3.17 81/08/17 09:36:50 eric 33 32
c add header fields from new BB&N proposal ICST/CBOS - 80-2,
c "Specification of a Draft Message Format Standard" for NBS.
e
s 00010/00190/00275
d D 3.16 81/08/09 19:07:59 eric 32 31
c put mailer definitions into configuration file
e
s 00008/00003/00457
d D 3.15 81/08/09 15:01:51 eric 31 30
c lint it
e
s 00023/00008/00437
d D 3.14 81/08/09 12:34:02 eric 30 29
c add private incoming mailers; add q_home field to ADDRESS struct;
c some general cleanup
e
s 00002/00058/00443
d D 3.13 81/04/01 23:37:10 eric 29 28
c eliminate useless garbage
e
s 00003/00002/00498
d D 3.12 81/03/28 13:36:16 eric 28 27
c pass Full-Name field internally to do forwards correctly
e
s 00003/00003/00497
d D 3.11 81/03/28 12:02:13 eric 27 26
c put much more info in cf file (e.g., headers)
e
s 00003/00003/00497
d D 3.10 81/03/20 09:44:32 eric 26 25
c change name (again); from postbox to sendmail
e
s 00007/00008/00493
d D 3.9 81/03/12 10:56:37 eric 25 24
c merge letters to the same host into one message
e
s 00021/00034/00480
d D 3.8 81/03/11 10:45:05 eric 24 23
c general cleanup, esp. macro processor
e
s 00012/00106/00502
d D 3.7 81/03/09 13:20:50 eric 23 22
c first step at rewriting rules, etc.
e
s 00024/00050/00584
d D 3.6 81/03/07 18:18:47 eric 22 21
c split local configurations into seperate files
e
s 00014/00011/00620
d D 3.5 81/03/07 17:45:16 eric 21 20
c drop stupid concatenation stuff; add hi_pptr
e
s 00098/00039/00533
d D 3.4 81/03/07 16:58:37 eric 20 19
c change q_mailer to be index, not pointer
e
s 00000/00053/00572
d D 3.3 81/03/07 15:31:25 eric 19 18
c lint fixes
e
s 00035/00006/00590
d D 3.2 81/03/07 14:25:21 eric 18 17
c ----- delivermail ==> postbox -----
e
s 00065/00002/00531
d D 3.1 81/03/04 09:33:46 eric 17 16
c install fancy header stuff
e
s 00006/00000/00527
d D 2.6 81/02/15 10:03:56 eric 16 15
c add onyx machine
e
s 00009/00001/00518
d D 2.5 81/02/07 10:28:36 eric 15 14
c add ARPAVAX; default to NETV6MAIL at Berkeley
e
s 00013/00001/00506
d D 2.4 81/01/10 12:38:34 eric 14 13
c add an "ArpaLocal"
e
s 00007/00002/00500
d D 2.3 81/01/10 12:19:42 eric 13 12
c have name of mailer daemon be a configuration parameter
e
s 00006/00001/00496
d D 2.2 80/11/21 12:57:28 eric 12 11
c have right user & time come out for msgs
e
s 00000/00000/00497
d D 2.1 80/11/05 11:01:17 eric 11 10
c release 2
e
s 00002/00002/00495
d D 1.10 80/10/21 22:38:44 eric 10 9
c EX_UNAVAIL => EX_UNAVAILABLE
e
s 00034/00005/00463
d D 1.9 80/10/20 13:12:45 eric 9 8
c tried to clean up for non-berkeley site
e
s 00088/00031/00380
d D 1.8 80/10/11 18:11:18 eric 8 7
c cleanup to simplify configuration & fix minor bugs
e
s 00007/00007/00404
d D 1.7 80/10/03 16:45:32 eric 7 6
c MyLocNam => MyLocName for consistency with main.c
e
s 00001/00001/00410
d D 1.6 80/09/27 11:21:55 eric 6 5
c don't ignore host in comparing UUCP addresses
e
s 00016/00008/00395
d D 1.5 80/08/12 13:48:46 eric 5 4
c add UUCP local address & remove cruft
e
s 00000/00039/00403
d D 1.4 80/08/02 13:48:26 eric 4 3
c cleaned up comments
e
s 00002/00000/00440
d D 1.3 80/07/25 22:02:56 eric 3 2
c add ID keywords
e
s 00002/00002/00438
d D 1.2 80/06/24 23:33:44 eric 2 1
c attempted fixes to quote problem(s)
e
s 00440/00000/00000
d D 1.1 80/06/23 08:23:40 eric 1 0
e
u
U
f b 
f i 
t
T
I 98
/*
I 115
D 366
 * Copyright (c) 1983 Eric P. Allman
E 366
I 366
 * Copyright (c) 1983, 1995 Eric P. Allman
E 366
E 115
D 113
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 113
I 113
D 211
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 211
I 211
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 211
 *
D 124
 * Redistribution and use in source and binary forms are permitted
D 115
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 115
I 115
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
E 124
I 124
 * %sccs.include.redist.c%
E 124
E 115
 */
E 113

#ifndef lint
D 113
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 113
I 113
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 113

I 215
# include "sendmail.h"
# include "pathnames.h"
E 215
E 98
I 1
D 35
# include <stdio.h>
E 35
D 116
# include <pwd.h>
E 116
I 92
# include <sys/ioctl.h>
I 165
# include <sys/param.h>
I 262
D 358
# include <netdb.h>
E 262
I 173
D 222
# include <signal.h>
E 222
E 173
E 165
I 103
D 116
# ifdef sun
E 116
D 147
# include <sys/param.h>
E 147
D 116
# endif sun
E 116
I 116
# include <pwd.h>
E 358
E 116
E 103
E 92
D 18
# include "dlvrmail.h"
E 18
I 18
D 26
# include "postbox.h"
E 26
I 26
D 215
# include "sendmail.h"
I 122
# include "pathnames.h"
E 215
E 122
E 26
E 18
I 3

D 8
static char SccsId[] = "%W%	%G%";
E 3
# include <whoami.h>

E 8
/*
D 18
**  CONF.C -- Delivermail Configuration Tables.
E 18
I 18
D 26
**  CONF.C -- Postbox Configuration Tables.
E 26
I 26
**  CONF.C -- Sendmail Configuration Tables.
E 26
E 18
**
**	Defines the configuration of this installation.
**
D 8
**	The first table describes available mailers.  This is
**	just a list of argument vectors, with the following
**	codes embedded:
**		$u -- insert the user name.
**		$h -- insert the host name.
**		$f -- insert the from person name.
**		$c -- insert the hop count.
**	This stuff is interpreted in buildmail.  There are two
**	important conventions here: entry zero must be the
**	local mailer & entry one must be the shell.
E 8
I 8
D 132
**	Compilation Flags:
D 29
**		HASARPA -- set if this machine has a connection to
**			the Arpanet.
**		HASUUCP -- set if this machine has a connection to
**			the UUCP network.
E 29
D 32
**		NETV6MAIL -- set if you want to use "v6mail" that
**			comes with the Berkeley network.  Normally
**			/bin/mail will work fine, but around Berkeley
**			we use v6mail because it is a "fixed target".
I 15
**			Also, only v6mail has the "/dev/mail" stuff
**			in it (for biff(1)).
E 32
E 15
D 114
**		V6 -- running on a version 6 system.  This determines
**			whether to define certain routines between
**			the two systems.  If you are running a funny
**			system, e.g., V6 with long tty names, this
**			should be checked carefully.
E 114
I 90
**		VMUNIX -- running on a Berkeley UNIX system.
E 90
I 9
D 29
**		DUMBMAIL -- set if your /bin/mail doesn't have the
**			-d flag.
E 29
E 9
E 8
**
E 132
D 8
**	The second table gives a list of special characters.  This
**	table is scanned linearly by parse() until an entry is
**	found using one of the magic characters.  Other fields
**	give more information on how to handle it.
**
**	Defined Constants:
**		M_* -- indices into Mailer, used only in this module.
**
**	Defines:
**		Mailer -- the mailer descriptor table.
**		ParseTab -- the parse table.
**
**	Notes:
**		Ingres 11/70 version.
**
**	History:
**		3/5/80 -- Generalized to use <whoami.h>.
**		12/26/79 -- written for Ingres 11/70.
E 8
I 8
**	Configuration Variables:
D 9
**		ArpaHost -- the name of the host through which arpanet
**			mail will be sent.
E 9
I 9
D 23
**		ArpaHost -- the arpanet name of the host through
**			which arpanet mail will be sent.
E 9
**		MyLocName -- the name of the host on a local network.
**			This is used to disambiguate the contents of
**			ArpaHost among many hosts who may be sharing
**			a gateway.
I 14
**		DaemonName -- the name of this agent for use in
**			error messages, typically "~MAILER~DAEMON~"
**			at this host on the local net.
E 14
I 9
**		ArpaLocal -- a list of local names for this host on
**			the arpanet.  Only functional if HASARPA set.
**		UucpLocal -- ditto for the Arpanet.
**		BerkLocal -- ditto for the Berknet.
E 23
E 9
D 32
**		Mailer -- a table of mailers known to the system.
D 29
**			The fields are:
E 29
I 29
**			This should be fairly static.  The fields are:
E 29
**			- the pathname of the mailer.
**			- a list of flags describing the properties
**			  of this mailer:
**			   M_FOPT -- if set, the mailer has a picky "-f"
**				option.  In this mode, the mailer will
**				only accept the "-f" option if the
**				sender is actually "root", "network",
**				and possibly (but not necessarily) if
**				the -f argument matches the real sender.
**				The effect is that if the "-f" option
D 18
**				is given to delivermail then it will be
E 18
I 18
D 26
**				is given to postbox then it will be
E 26
I 26
**				is given to sendmail then it will be
E 26
E 18
**				passed through (as arguments 1 & 2) to
**				the mailer.
**			   M_ROPT -- identical to M_FOPT, except uses
**				-r instead.
**			   M_QUIET -- if set, don't print a message if
**				the mailer returns bad status.
**			   M_RESTR -- if set, this mailer is restricted
**				to use by "daemon"; otherwise, we do a
**				setuid(getuid()) before calling the
**				mailer.
D 24
**			   M_HDR -- if set, the mailer wants us to
**				insert a UNIX "From" line before
E 24
I 24
**			   M_NHDR -- if set, the mailer doesn't want us
**				to insert a UNIX "From" line before
E 24
**				outputing.
I 12
D 24
**			   M_FHDR -- if set, the header that we
**				generate will be used literally, so
**				we must force it to be correct.  The
**				effect is that we generate a header
**				even if one exists.
E 24
E 12
**			   M_NOHOST -- if set, this mailer doesn't care
**				about the host part (e.g., the local
**				mailer).
**			   M_STRIPQ -- if set, strip quote (`"')
**				characters out of parameters as you
**				transliterate them into the argument
**				vector.  For example, the local mailer
**				is called directly, so these should be
**				stripped, but the program-mailer (i.e.,
**				csh) should leave them in.
I 17
**			   M_NEEDDATE -- this mailer requires a Date:
**				field in the message.
**			   M_NEEDFROM -- this mailer requires a From:
**				field in the message.
**			   M_MSGID -- this mailer requires a Message-Id
**				field in the message.
D 24
**			   M_COMMAS -- this mailer wants comma-
**				seperated To: and Cc: fields.
**			   M_ARPAFMT == M_NEEDDATE|M_NEEDFROM|M_MSGID|
**				M_COMMAS.
E 24
I 24
**			   M_ARPAFMT == M_NEEDDATE|M_NEEDFROM|M_MSGID.
E 24
E 17
**			- an exit status to use as the code for the
**			  error message print if the mailer returns
**			  something we don't understand.
**			- A list of names that are to be considered
**			  "local" (and hence are stripped off) for
**			  this mailer.
**			- An argument vector to be passed to the
D 29
**			  mailer with the following substitutions:
**			   $f - the from person name.
**			   $u - the target user name.
**			   $h - the target user host.
**			   $c - the hop count.
E 29
I 29
**			  mailer; this is macro substituted.
E 29
**			>>>>>>>>>> Entry zero must be for the local
**			>> NOTE >> mailer and entry one must be for
**			>>>>>>>>>> the shell.
E 32
D 23
**		ParseTab -- a table driving the parsing process.  Each
**			entry contains:
**			- a character that will trigger this entry.
**			- an index into the Mailer table.
D 18
**			- a word of flags, described in dlvrmail.h.
E 18
I 18
**			- a word of flags, described in postbox.h.
E 18
**			- an argument.  If we have P_MAP, it is the
**			  character to turn the trigger character into.
**			  If we have P_MOVE, it is the site to send it
**			  to, using the mailer specified above.
I 9
**			This table will almost certainly have to be
**			changed on your site if you have anything more
**			than the UUCP net.
E 23
I 17
**		HdrInfo -- a table describing well-known header fields.
**			Each entry has the field name and some flags,
D 33
**			which can be:
D 21
**			H_CONCAT -- if there is more than one field
**				of this name, turn it into a comma-
**				seperated list.
**			H_DELETE -- delete this field.
E 21
I 21
**			- H_EOH -- this field is equivalent to a blank
**			  line; i.e., it signifies end of header.
**			- H_DELETE -- delete this field.
**			There is also a field pointing to a pointer
**			that should be set to point to this header.
E 33
I 33
**			which are described in sendmail.h.
I 44
D 76
**		StdTimezone -- name of local timezone in standard time
**			(V6 only).
**		DstTimezone -- name of local timezone in daylight savings
**			time (V6 only).
E 76
E 44
E 33
I 32
**
**	Notes:
**		I have tried to put almost all the reasonable
**		configuration information into the configuration
**		file read at runtime.  My intent is that anything
**		here is a function of the version of UNIX you
**		are running, or is really static -- for example
**		the headers are a superset of widely used
**		protocols.  If you find yourself playing with
**		this file too much, you may be making a mistake!
E 32
E 21
E 17
E 9
E 8
*/




I 8
D 59
static char SccsId[] = "%W%	%G%";
E 59
I 59
D 99
SCCSID(%W%	%Y%	%G%);
E 59
E 8
D 48

I 8

D 9
char	*ArpaHost = "Berkeley";	/* host name of gateway on Arpanet */
E 9
D 19
bool	UseMsgId = FALSE;	/* don't put message id's in anywhere */

E 19
D 62
# include <whoami.h>		/* definitions of machine id's at berkeley */
D 32

I 9
# ifdef BERKELEY
I 14
D 29

E 29
E 14
D 23
char	*ArpaHost = "Berkeley";	/* host name of gateway on Arpanet */
I 17
D 22
char	*UucpHost = "ucbvax";	/* host name of gateway on UUCP net */
E 22
# define BerkHost   MyLocName	/* host name of gateway on Berk net */
E 23
E 17
I 15
# define NETV6MAIL		/* use /usr/net/bin/v6mail for local delivery */
E 15
I 14
D 29

E 14
D 22
# else BERKELEY
I 14

E 14
char	*ArpaHost = "[unknown]";
char	*MyLocName = sysname;
# define HASUUCP		/* default to having UUCP net */
char	*UucpLocal[] = { sysname, NULL };
I 14

E 14
# endif BERKELEY

I 14

E 22
/* Specific Configurations for Berkeley Machines */

D 22
/* Berkeley people: mail changes to csvax:eric or they will be lost! */
E 22
I 22
/* Berkeley people: mail changes to ingvax:eric or they will be lost! */
E 22

E 14
E 9
E 8
# ifdef ING70
D 22
static char	*BerkLocal[] = { "i", "ingres", "ing70", NULL };
I 5
D 14
# define ArpaLocal	NULL
E 14
I 14
char		*ArpaLocal = { "berkeley", "ucb", NULL };
E 14
E 5
D 7
char		*MyLocNam = "Ing70";
E 7
I 7
char		*MyLocName = "Ing70";
I 13
char		*DaemonName = "Ing70:~MAILER~DAEMON~";
E 13
E 7
# define HASARPA
# define V6
E 22
I 22
# include "c.ing70.h"
E 22
# endif ING70

# ifdef INGVAX
D 9
/* untested */
E 9
D 22
static char	*BerkLocal[] = { "j", "ingvax", NULL };
D 7
char		*MyLocNam = "IngVax";
E 7
I 7
char		*MyLocName = "IngVax";
I 13
char		*DaemonName = "IngVax:~MAILER~DAEMON~";
E 22
I 22
# include "c.ingvax.h"
E 22
E 13
E 7
# endif INGVAX

# ifdef CSVAX
D 9
/* untested */
E 9
D 22
static char	*BerkLocal[] = { "v", "csvax", "vax", NULL };
D 5
char		*MyLocNam = "CSVax";
E 5
I 5
static char	*UucpLocal[] = { "ucbvax", "ernie", NULL };
D 7
char		*MyLocNam = "CSVAX";
E 7
I 7
char		*MyLocName = "CSVAX";
I 13
char		*DaemonName = "CSVAX:~MAILER~DAEMON~";
E 13
E 7
E 5
# define HASUUCP
E 22
I 22
# include "c.csvax.h"
E 22
D 15
# define NETV6MAIL
E 15
# endif CSVAX
I 15

# ifdef ARPAVAX
D 22
static char	*BerkLocal[] = { "r", "arpavax", NULL };
char		*MyLocName = "ARPAVAX";
char		*DaemonName = "ARPAVAX:~MAILER~DAEMON~";
E 22
I 22
# include "c.arpavax.h"
E 22
# endif ARPAVAX
E 15

# ifdef CORY
D 13
/* untested */
E 13
D 22
static char	*BerkLocal[] = { "y", "cory", NULL };
D 7
char		*MyLocNam = "Cory";
E 7
I 7
char		*MyLocName = "Cory";
I 13
char		*DaemonName = "Cory:~MAILER~DAEMON~";
E 22
I 22
# include "c.cory.h"
E 22
E 13
E 7
# endif CORY

I 16
# ifdef ONYX
D 22
static char	*BerkLocal[[] = { "x", "onyx", NULL };
char		*MyLocName = "Onyx";
char		*DaemonName = "Onyx:~MAILER~DAEMON~";
E 22
I 22
# include "c.onyx.h"
E 22
# endif ONYX

E 16
# ifdef IMAGE
D 22
/* untested */
static char	*BerkLocal[] = { "m", "image", NULL };
D 7
char		*MyLocNam = "Image";
E 7
I 7
char		*MyLocName = "Image";
I 13
char		*DaemonName = "Image:~MAILER~DAEMON~";
E 13
E 7
# define V6
E 22
I 22
# include "c.image.h"
E 22
# endif IMAGE

# ifdef ESVAX
D 13
/* untested */
E 13
D 22
static char	*BerkLocal[] = { "o", "esvax", NULL };
D 5
char		*MyLocNam = "ESVax";
E 5
I 5
D 7
char		*MyLocNam = "ESVAX";
E 7
I 7
char		*MyLocName = "ESVAX";
I 13
char		*DaemonName = "ESVAX:~MAILER~DAEMON~";
E 22
I 22
# include "c.esvax.h"
E 22
E 13
E 7
E 5
# endif ESVAX

# ifdef EECS40
D 22
/* untested */
static char	*BerkLocal[] = { "z", "eecs40", NULL };
D 7
char		*MyLocNam = "EECS40";
E 7
I 7
char		*MyLocName = "EECS40";
I 13
char		*DaemonName = "EECS40:~MAILER~DAEMON~";
E 13
E 7
# define V6
E 22
I 22
# include "c.eecs40.h"
E 22
# endif EECS40

I 22
# else BERKELEY
E 22
I 5

I 22
D 23
char	*ArpaHost = "[unknown]";
char	*MyLocName = sysname;
E 23
# define HASUUCP		/* default to having UUCP net */
D 23
char	*UucpLocal[] = { sysname, NULL };
# define BerkMerge	NULL	/* don't merge any berknet sites */
# define UucpMerge	NULL	/* don't merge any UUCP sites */
E 23

E 29
# endif BERKELEY



E 22
D 23
# ifndef HASARPA
# define ArpaLocal	NULL
# endif HASARPA

# ifndef HASUUCP
# define UucpLocal	NULL
# endif HASUUCP


E 23
E 5
D 20
struct mailer Mailer[] =
E 20
I 20
/* local mail -- must be #0 */
static char	*LocalArgv[] =
E 20
{
D 20
	/* local mail -- must be #0 */
	{
E 20
I 20
	"...local%mail",
	"-d",
	"$u",
	NULL
};

static struct mailer	LocalMailer =
{
E 20
# ifdef NETV6MAIL
D 20
		"/usr/net/bin/v6mail",
E 20
I 20
D 24
	"/usr/net/bin/v6mail",
E 24
I 24
	"local",	"/usr/net/bin/v6mail",
E 24
E 20
# else
D 20
		"/bin/mail",
E 20
I 20
D 24
	"/bin/mail",
E 24
I 24
	"local",	"/bin/mail",
E 24
E 20
# endif
D 17
		M_ROPT|M_NOHOST|M_STRIPQ,	EX_NOUSER,	NULL,
E 17
I 17
D 20
		M_ROPT|M_NOHOST|M_STRIPQ|M_ARPAFMT,	EX_NOUSER,	NULL,
		"$f",		NULL,
E 17
		{ "...local%mail", "-d", "$u", NULL }
	},
	/* pipes through programs -- must be #1 */
	{
		"/bin/csh",
D 10
		M_HDR|M_NOHOST,			EX_UNAVAIL,	NULL,
E 10
I 10
D 12
		M_HDR|M_NOHOST,			EX_UNAVAILABLE,	NULL,
E 12
I 12
		M_HDR|M_FHDR|M_NOHOST,		EX_UNAVAILABLE,	NULL,
I 17
		"$f",		NULL,
E 17
E 12
E 10
		{ "...prog%mail", "-fc", "$u", NULL }
	},
	/* local berkeley mail */
	{
		"/usr/net/bin/sendberkmail",
D 2
		M_FOPT|M_HDR,			EX_UNAVAIL,	BerkLocal,
E 2
I 2
D 10
		M_FOPT|M_HDR|M_STRIPQ,		EX_UNAVAIL,	BerkLocal,
E 10
I 10
		M_FOPT|M_HDR|M_STRIPQ,		EX_UNAVAILABLE,	BerkLocal,
I 17
		"$B:$f",	NULL,
E 17
E 10
E 2
		{ "...berk%mail", "-m", "$h", "-t", "$u", "-h", "$c", NULL }
	},
	/* arpanet mail */
	{
		"/usr/lib/mailers/arpa",
D 2
		0,				0,		NULL,
E 2
I 2
D 5
		M_STRIPQ,			0,		NULL,
E 5
I 5
D 17
		M_STRIPQ,			0,		ArpaLocal,
E 17
I 17
		M_STRIPQ|M_ARPAFMT,		0,		ArpaLocal,
		"$f@$A",	NULL,
E 17
E 5
E 2
		{ "...arpa%mail", "$f", "$h", "$u", NULL }
	},
	/* uucp mail (cheat & use Bell's v7 mail) */
	{
D 5
# ifdef UCKMAIL
		"/bin/badmail",
# else
E 5
		"/bin/mail",
D 5
# endif
		M_ROPT|M_NOHOST|M_STRIPQ,	EX_NOUSER,	NULL,
E 5
I 5
D 6
		M_ROPT|M_NOHOST|M_STRIPQ,	EX_NOUSER,	UucpLocal,
E 6
I 6
		M_ROPT|M_STRIPQ,		EX_NOUSER,	UucpLocal,
I 17
		"$U!$f",	NULL,
E 20
I 20
D 23
	M_ROPT|M_NOHOST|M_STRIPQ|M_ARPAFMT,	EX_NOUSER,	NULL,
	"$f",		NULL,			LocalArgv,
E 23
I 23
D 24
	"local",	M_ROPT|M_NOHOST|M_STRIPQ|M_ARPAFMT,	EX_NOUSER,
	"$f",		LocalArgv,
E 24
I 24
	M_ROPT|M_NOHOST|M_STRIPQ|M_ARPAFMT|M_MUSER|M_NHDR,
	EX_NOUSER,	"$f",		LocalArgv,	NULL,
E 24
E 23
};

D 24
/* pipes through programs -- must be #1 */
E 24
I 24
/* pipes through programs -- must be #1 -- also used for files */
E 24
static char	*ProgArgv[] =
{
	"...prog%mail",
	"-fc",
	"$u",
	NULL
};

static struct mailer	ProgMailer =
{
D 24
	"/bin/csh",
D 23
	M_HDR|M_FHDR|M_NOHOST,			EX_UNAVAILABLE,	NULL,
	"$f",		NULL,			ProgArgv,
E 23
I 23
	"prog",		M_HDR|M_FHDR|M_NOHOST,			EX_UNAVAILABLE,
	"$f",		ProgArgv,
E 24
I 24
	"prog",		"/bin/csh",
	M_NOHOST|M_ARPAFMT,
	EX_UNAVAILABLE, "$f",		ProgArgv,	NULL,
E 24
E 23
};

I 30
/* user-private mailers -- must be #2 */
static char	*PrivArgv[] =
{
	"...priv%mail",
	"$u",
	NULL
};

static struct mailer	PrivMailer =
{
	"priv",		NULL,
	M_ROPT|M_NOHOST|M_STRIPQ|M_ARPAFMT,
	EX_UNAVAILABLE,	"$f",		PrivArgv,	NULL,
};

E 30
/* local berkeley mail */
static char	*BerkArgv[] =
{
	"...berk%mail",
	"-m",
	"$h",
D 25
	"-t",
	"$u",
E 25
	"-h",
	"$c",
I 25
	"-t",
	"$u",
E 25
	NULL
};

static struct mailer	BerkMailer =
{
D 24
	"/usr/net/bin/sendberkmail",
D 23
	M_FOPT|M_HDR|M_STRIPQ,			EX_UNAVAILABLE,	BerkLocal,
D 22
	"$B:$f",	NULL,			BerkArgv,
E 22
I 22
	"$B:$f",	BerkMerge,		BerkArgv,
E 23
I 23
	"berk",		M_FOPT|M_HDR|M_STRIPQ,			EX_UNAVAILABLE,
	"$B:$f",	BerkArgv,
E 24
I 24
	"berk",		"/usr/net/bin/sendberkmail",
D 25
	M_FOPT|M_ARPAFMT|M_STRIPQ|M_MUSER,
E 25
I 25
D 28
	M_FOPT|M_ARPAFMT|M_STRIPQ,
E 28
I 28
	M_FOPT|M_NEEDDATE|M_FULLNAME|M_STRIPQ,
E 28
E 25
	EX_UNAVAILABLE,	"$B:$f",	BerkArgv,	NULL,
E 24
E 23
E 22
};

/* arpanet mail */
static char	*ArpaArgv[] =
{
	"...arpa%mail",
	"$f",
	"$h",
	"$u",
	NULL
};

static struct mailer	ArpaMailer =
{
D 24
	"/usr/lib/mailers/arpa",
D 23
	M_STRIPQ|M_ARPAFMT,			0,		ArpaLocal,
	"$f@$A",	NULL,			ArpaArgv,
E 23
I 23
	"arpa",		M_STRIPQ|M_ARPAFMT,			0,
	"$f@$A",	ArpaArgv,
E 24
I 24
	"arpa",		"/usr/lib/mailers/arpa",
	M_STRIPQ|M_ARPAFMT|M_USR_UPPER,
	0,		"$f@$A",	ArpaArgv,	NULL,
E 24
E 23
};

/* uucp mail (cheat & use Bell's v7 mail) */
static char	*UucpArgv[] =
{
	"...uucp%mail",
E 20
E 17
E 6
E 5
D 24
# ifdef DUMBMAIL
E 24
I 24
D 25
# ifndef DUMBMAIL
E 24
D 20
		{ "...uucp%mail", "$h!$u", NULL }
# else
		{ "...uucp%mail", "-d", "$h!$u", NULL }
E 20
I 20
	"-d",
E 20
# endif DUMBMAIL
D 20
	},
E 20
I 20
	"$h!$u",
E 25
I 25
	"-",
	"$h!rmail",
	"($u)",
E 25
	NULL
E 20
};

I 20
static struct mailer	UucpMailer =
{
D 24
	"/bin/mail",
D 23
	M_ROPT|M_STRIPQ,			EX_NOUSER,	UucpLocal,
D 22
	"$U!$f",	NULL,			UucpArgv,
E 22
I 22
	"$U!$f",	UucpMerge,		UucpArgv,
E 23
I 23
	"uucp",		M_ROPT|M_STRIPQ,			EX_NOUSER,
	"$U!$f",	UucpArgv,
E 24
I 24
D 25
	"uucp",		"/bin/mail",
E 25
I 25
	"uucp",		"/usr/bin/uux",
E 25
D 28
	M_ROPT|M_STRIPQ|M_ARPAFMT|M_MUSER,
E 28
I 28
	M_ROPT|M_STRIPQ|M_NEEDDATE|M_FULLNAME|M_MUSER,
E 28
	EX_NOUSER,	"$U!$f",	UucpArgv,	NULL,
E 24
E 23
E 22
};

struct mailer	*Mailer[] =
{
	&LocalMailer,		/* 0 -- must be 0 */
	&ProgMailer,		/* 1 -- must be 1 */
D 30
	&BerkMailer,		/* 2 */
	&ArpaMailer,		/* 3 */
	&UucpMailer,		/* 4 */
E 30
I 30
	&PrivMailer,		/* 2 -- must be 2 */
	&BerkMailer,		/* 3 */
	&ArpaMailer,		/* 4 */
	&UucpMailer,		/* 5 */
E 30
I 23
	NULL
E 23
};

D 23
# define NMAILERS	(sizeof Mailer / sizeof Mailer[0])
E 23
I 23
D 24
# define NMAILERS	((sizeof Mailer / sizeof Mailer[0]) - 1)
E 23

E 24
E 20
D 30
# define M_LOCAL	0
I 20
# define M_PROG		1
E 20
# define M_BERK		2
# define M_ARPA		3
# define M_UUCP		4
E 30
I 30
/* offsets for arbitrary mailers */
# define M_BERK		2	/* berknet */
# define M_ARPA		3	/* arpanet */
# define M_UUCP		4	/* UUCPnet */
E 30
I 20
D 24

/* list of messages for each mailer (sorted by host) */
ADDRESS		MailList[NMAILERS];
E 24
E 20



E 32
I 9
D 23
# ifdef BERKELEY
E 9
struct parsetab ParseTab[] =
{
	':',	M_BERK,		P_ONE,				NULL,
# ifdef HASARPA
	'@',	M_ARPA,		P_HLAST|P_USR_UPPER,		NULL,
# else
	'@',	M_BERK,		P_HLAST|P_USR_UPPER|P_MOVE,	"ing70",
# endif HASARPA
	'^',	-1,		P_MAP,				"!",
# ifdef HASUUCP
	'!',	M_UUCP,		0,				NULL,
# else
	'!',	M_BERK,		P_MOVE,				"csvax",
# endif HASUUCP
	'.',	-1,		P_MAP|P_ONE,			":",
	'\0',	M_LOCAL,	P_MOVE,				"",
};
I 9
# else BERKELEY
struct parsetab ParseTab[] =
{
# ifdef HASARPA
	'@',	M_ARPA,		P_HLAST|P_USR_UPPER,		NULL,
# endif HASARPA
# ifdef HASUUCP
	'^',	-1,		P_MAP,				"!",
	'!',	M_UUCP,		0,				NULL,
# endif HASUUCP
	'\0',	M_LOCAL,	P_MOVE,				"",
};
# endif BERKELEY
E 23
I 17

E 62

E 99
/*
E 48
I 48
/*
E 48
**  Header info table
I 21
**	Final (null) entry contains the flags used for any other field.
I 33
**
**	Not all of these are actually handled specially by sendmail
**	at this time.  They are included as placeholders, to let
**	you know that "someday" I intend to have sendmail do
**	something with them.
E 33
E 21
*/

struct hdrinfo	HdrInfo[] =
{
I 73
D 79
		/* date information */
	"posted-date",		0,			0,
E 73
D 21
	"date",		0,
	"from",		0,
	"to",		H_CONCAT,
	"cc",		H_CONCAT,
	"subject",	0,
	"message-id",	0,
	NULL,		0
E 21
I 21
D 27
	"date",		0,			NULL,
	"from",		0,			NULL,
E 27
I 27
D 33
	"date",		H_CHECK,		M_NEEDDATE,
	"from",		H_CHECK,		M_NEEDFROM,
I 28
	"full-name",	H_ACHECK,		M_FULLNAME,
E 28
E 27
	"to",		0,			NULL,
	"cc",		0,			NULL,
	"subject",	0,			NULL,
D 27
	"message-id",	0,			&MsgId,
E 27
I 27
	"message-id",	H_CHECK,		M_MSGID,
E 27
	"message",	H_EOH,			NULL,
	NULL,		0,			NULL,
E 33
I 33
	"date",			H_CHECK,		M_NEEDDATE,
D 60
	"from",			H_CHECK,		M_NEEDFROM,
E 60
I 60
D 69
	"from",			H_ADDR|H_CHECK,		M_NEEDFROM,
E 69
I 69
D 73
	"from",			H_ADDR|H_FROM|H_CHECK,	M_NEEDFROM,
E 73
I 73
	"resent-date",		0,			0,
	"received-date",	H_CHECK,		M_LOCAL,
E 79
		/* originator fields, most to least significant  */
D 79
	"resent-sender",	H_FROM,			0,
	"resent-from",		H_FROM,			0,
	"sender",		H_FROM,			0,
	"from",			H_FROM|H_CHECK,		M_NEEDFROM,
E 73
E 69
E 60
I 38
D 40
	"original-from",	H_DELETE,		0,		/* internal */
E 40
I 40
D 46
	"original-from",	H_ACHECK,		0,		/* internal */
E 46
I 46
D 74
	"original-from",	0,			0,
E 74
E 46
E 40
E 38
D 60
	"sender",		0,			0,
E 60
I 60
D 73
	"sender",		H_ADDR,			0,
E 73
E 60
	"full-name",		H_ACHECK,		M_FULLNAME,
D 39
	"to",			0,			0,
	"cc",			0,			0,
	"bcc",			0,			0,
E 39
I 39
D 41
	"to",			H_ADDR|H_FORCE,		0,
	"cc",			H_ADDR|H_FORCE,		0,
D 40
	"bcc",			H_ADDR|H_DELETE|H_FORCE,0,
E 40
I 40
	"bcc",			H_ADDR|H_ACHECK|H_FORCE,0,
E 41
I 41
D 60
	"to",			H_ADDR,			0,
	"cc",			H_ADDR,			0,
	"bcc",			H_ADDR|H_ACHECK,	0,
E 60
I 60
D 73
	"to",			H_ADDR|H_RCPT,		0,
	"cc",			H_ADDR|H_RCPT,		0,
D 67
	"bcc",			H_ADDR|H_ACHECK|H_RCPT,	0,
E 60
E 41
E 40
E 39
	"message-id",		H_CHECK,		M_MSGID,
E 67
I 67
	"bcc",			H_ADDR|H_RCPT,		0,
E 73
I 73
	"received-from",	H_CHECK,		M_LOCAL,
	"return-receipt-to",	H_FROM,			0,
I 74
	"errors-to",		H_FROM,			0,
E 79
I 79
D 87
	"resent-sender",	H_FROM,
	"resent-from",		H_FROM,
E 87
I 87
D 313
	"resent-sender",	H_FROM|H_RESENT,
	"resent-from",		H_FROM|H_RESENT,
I 110
	"resent-reply-to",	H_FROM|H_RESENT,
E 110
E 87
	"sender",		H_FROM,
	"from",			H_FROM,
I 110
	"reply-to",		H_FROM,
E 110
	"full-name",		H_ACHECK,
D 149
	"return-receipt-to",	H_FROM,
	"errors-to",		H_FROM,
E 149
I 149
D 249
	"return-receipt-to",	H_FROM /* |H_RECEIPTTO */,
E 249
I 249
	"return-receipt-to",	H_FROM|H_RECEIPTTO,
E 249
	"errors-to",		H_FROM|H_ERRORSTO,
E 313
I 313
	"resent-sender",		H_FROM|H_RESENT,
	"resent-from",			H_FROM|H_RESENT,
	"resent-reply-to",		H_FROM|H_RESENT,
	"sender",			H_FROM,
	"from",				H_FROM,
	"reply-to",			H_FROM,
	"full-name",			H_ACHECK,
	"return-receipt-to",		H_FROM|H_RECEIPTTO,
	"errors-to",			H_FROM|H_ERRORSTO,
E 313
I 189

E 189
E 149
E 79
E 74
		/* destination fields */
D 79
	"to",			H_RCPT,			0,
	"resent-to",		H_RCPT,			0,
	"cc",			H_RCPT,			0,
	"resent-cc",		H_RCPT,			0,
D 77
	"bcc",			H_RCPT,			0,
	"resent-bcc",		H_RCPT,			0,
E 77
I 77
	"bcc",			H_RCPT|H_ACHECK,	0,
	"resent-bcc",		H_RCPT|H_ACHECK,	0,
E 79
I 79
D 313
	"to",			H_RCPT,
D 87
	"resent-to",		H_RCPT,
E 87
I 87
	"resent-to",		H_RCPT|H_RESENT,
E 87
	"cc",			H_RCPT,
D 87
	"resent-cc",		H_RCPT,
E 87
I 87
	"resent-cc",		H_RCPT|H_RESENT,
E 87
	"bcc",			H_RCPT|H_ACHECK,
D 87
	"resent-bcc",		H_RCPT|H_ACHECK,
E 87
I 87
	"resent-bcc",		H_RCPT|H_ACHECK|H_RESENT,
I 140
	"apparently-to",	H_RCPT,
E 313
I 313
	"to",				H_RCPT,
	"resent-to",			H_RCPT|H_RESENT,
	"cc",				H_RCPT,
	"resent-cc",			H_RCPT|H_RESENT,
D 346
	"bcc",				H_RCPT|H_ACHECK,
	"resent-bcc",			H_RCPT|H_ACHECK|H_RESENT,
E 346
I 346
	"bcc",				H_RCPT|H_STRIPVAL,
	"resent-bcc",			H_RCPT|H_STRIPVAL|H_RESENT,
E 346
	"apparently-to",		H_RCPT,
E 313
I 189

E 189
E 140
E 87
E 79
E 77
		/* message identification and control */
I 87
D 313
	"message-id",		0,
	"resent-message-id",	H_RESENT,
E 87
E 73
D 79
	"message-id",		0,			0,
I 73
	"resent-message-id",	0,			0,
	"precedence",		0,			0,
E 73
E 67
	"message",		H_EOH,			0,
	"text",			H_EOH,			0,
E 79
I 79
	"message",		H_EOH,
	"text",			H_EOH,
E 313
I 313
	"message-id",			0,
	"resent-message-id",		H_RESENT,
	"message",			H_EOH,
	"text",				H_EOH,
E 313
I 189

E 189
I 87
		/* date fields */
D 313
	"date",			0,
	"resent-date",		H_RESENT,
E 313
I 313
	"date",				0,
	"resent-date",			H_RESENT,
E 313
I 189

E 189
E 87
E 79
D 73
	"posted-date",		0,			0,
	"return-receipt-to",	0,			0,
D 37
	"received-date",	H_CHECK,		M_FINAL,
	"received-from",	H_CHECK,		M_FINAL,
E 37
I 37
	"received-date",	H_CHECK,		M_LOCAL,
	"received-from",	H_CHECK,		M_LOCAL,
E 37
	"precedence",		0,			0,
I 58
D 70
	"mail-from",		H_FORCE,		0,
E 70
I 70
	"received",		H_FORCE,		0,
E 70
E 58
	"via",			H_FORCE,		0,
E 73
I 73
		/* trace fields */
D 79
	"received",		H_TRACE|H_FORCE,	0,
	"via",			H_TRACE|H_FORCE,	0,
	"mail-from",		H_TRACE|H_FORCE,	0,
E 79
I 79
D 313
	"received",		H_TRACE|H_FORCE,
I 195
	"x400-received",	H_TRACE|H_FORCE,
E 195
	"via",			H_TRACE|H_FORCE,
	"mail-from",		H_TRACE|H_FORCE,
E 313
I 313
	"received",			H_TRACE|H_FORCE,
	"x400-received",		H_TRACE|H_FORCE,
	"via",				H_TRACE|H_FORCE,
	"mail-from",			H_TRACE|H_FORCE,
E 313
I 189

		/* miscellaneous fields */
D 313
	"comments",		H_FORCE,
D 212
	"return-path",		H_ACHECK,
E 212
I 212
	"return-path",		H_FORCE|H_ACHECK,
E 313
I 313
	"comments",			H_FORCE,
	"return-path",			H_FORCE|H_ACHECK,
	"content-transfer-encoding",	H_CTE,
I 329
	"content-type",			H_CTYPE,
I 362
	"content-length",		H_ACHECK,
E 362
E 329
E 313
E 212
E 189
E 79

E 73
D 79
	NULL,			0,			0,
E 79
I 79
	NULL,			0,
E 79
E 33
E 21
};
I 34


D 172
/*
**  ARPANET error message numbers.
*/
E 172

D 55
# ifdef NEWFTP
/* these are almost all unchecked */
char	Arpa_Info[] =	"010";	/* arbitrary info: this is WRONG! */
char	Arpa_Enter[] =	"354";	/* start mail input */
char	Arpa_Mmsg[] =	"250";	/* mail successful (MAIL cmd) */
char	Arpa_Fmsg[] =	"250";	/* mail successful (MLFL cmd) */
char	Arpa_Syserr[] =	"450";	/* some (transient) system error */
char	Arpa_Usrerr[] =	"550";	/* some (fatal) user error */
# else NEWFTP
E 55
D 72
char	Arpa_Info[] =	"050";	/* arbitrary info */
D 55
char	Arpa_Enter[] =	"350";	/* start mail input */
char	Arpa_Mmsg[] =	"256";	/* mail successful (MAIL cmd) */
char	Arpa_Fmsg[] =	"250";	/* mail successful (MLFL cmd) */
char	Arpa_Syserr[] =	"455";	/* some (transient) system error */
char	Arpa_Usrerr[] =	"450";	/* some (fatal) user error */
# endif NEWFTP
E 55
I 55
char	Arpa_Syserr[] =	"451";	/* some (transient) system error */
char	Arpa_Usrerr[] =	"554";	/* some (fatal) user error */
E 72
I 72
D 172
char	Arpa_Info[] =		"050";	/* arbitrary info */
char	Arpa_TSyserr[] =	"451";	/* some (transient) system error */
char	Arpa_PSyserr[] =	"554";	/* some (permanent) system error */
D 161
char	Arpa_Usrerr[] =		"554";	/* some (fatal) user error */
E 161
I 161
char	Arpa_Usrerr[] =		"501";	/* some (fatal) user error */
E 161
E 72
E 55
I 42



E 172
D 80


E 80
/*
**  Location of system files/databases/etc.
*/

D 76
char	*AliasFile =	"/usr/lib/aliases";	/* alias file */
E 76
D 117
char	*ConfFile =	"/usr/lib/sendmail.cf";	/* runtime configuration */
D 52
char	*StatFile =	"/usr/eric/mailstats";	/* statistics summary */
E 52
I 52
D 56
char	*StatFile =	"/usr/lib/mailstats";	/* statistics summary */
E 56
I 56
D 76
char	*StatFile =	"/usr/lib/sendmail.st";	/* statistics summary */
E 56
char	*HelpFile =	"/usr/lib/sendmail.hf";	/* help file */
I 57
# ifdef QUEUE
E 57
I 54
char	*QueueDir =	"/usr/spool/mqueue";	/* queue of saved mail */
I 57
# else QUEUE
char	*QueueDir =	"/tmp";			/* location of temp files */
# endif QUEUE
E 76
E 57
D 80
char	*XcriptFile =	"/tmp/mailxXXXXXX";	/* template for transcript */
E 80
I 80
char	*FreezeFile =	"/usr/lib/sendmail.fc";	/* frozen version of above */
E 117
I 117
D 122
char	*ConfFile =	"/etc/sendmail.cf";	/* runtime configuration */
char	*FreezeFile =	"/etc/sendmail.fc";	/* frozen version of above */
E 122
I 122
D 246
char	*ConfFile =	_PATH_SENDMAILCF;	/* runtime configuration */
E 246
D 231
char	*FreezeFile =	_PATH_SENDMAILFC;	/* frozen version of above */
E 231
I 165
char	*PidFile =	_PATH_SENDMAILPID;	/* stores daemon proc id */
E 165
E 122
E 117


E 80
I 78

/*
I 165
**  Privacy values
*/

struct prival PrivacyValues[] =
{
	"public",		PRIV_PUBLIC,
	"needmailhelo",		PRIV_NEEDMAILHELO,
D 168
	"needexpnnelo",		PRIV_NEEDEXPNHELO,
E 168
I 168
	"needexpnhelo",		PRIV_NEEDEXPNHELO,
E 168
	"needvrfyhelo",		PRIV_NEEDVRFYHELO,
	"noexpn",		PRIV_NOEXPN,
	"novrfy",		PRIV_NOVRFY,
I 176
D 235
	"restrictmailq",	PRIV_RESTRMAILQ,
E 235
I 235
	"restrictmailq",	PRIV_RESTRICTMAILQ,
	"restrictqrun",		PRIV_RESTRICTQRUN,
E 235
I 188
	"authwarnings",		PRIV_AUTHWARNINGS,
I 299
	"noreceipts",		PRIV_NORECEIPTS,
E 299
E 188
E 176
	"goaway",		PRIV_GOAWAY,
D 188
	NULL,			PRIV_PUBLIC,
E 188
I 188
	NULL,			0,
E 188
};



/*
E 165
D 103
**  Some other configuration....
E 103
I 103
**  Miscellaneous stuff.
E 103
*/

D 90
char	SpaceSub =	'.';
E 90
I 90
D 93
char	SpaceSub =	'.';	/* character to replace <lwsp> in addrs */
D 91
int	QueueLA =	12;	/* if load average > 12, just queue */
int	RefuseLA =	25;	/* if load average > 25, refuse connections */
E 91
I 91
int	QueueLA =	8;	/* load avg > QueueLA -> just queue */
int	RefuseLA =	12;	/* load avg > RefuseLA -> refuse connections */
E 93
I 93
D 103
char	SpaceSub;		/* character to replace <lwsp> in addrs */
int	QueueLA;		/* load avg > QueueLA -> just queue */
int	RefuseLA;		/* load avg > RefuseLA -> refuse connections */
E 103
I 103
int	DtableSize =	50;		/* max open files; reset in 4.2bsd */
I 248
D 311


/*
**  Following should be config parameters (and probably will be in
**  future releases).  In the meantime, setting these is considered
**  unsupported, and is intentionally undocumented.
*/

#ifdef BROKENSMTPPEERS
bool	BrokenSmtpPeers = TRUE;		/* set if you have broken SMTP peers */
#else
bool	BrokenSmtpPeers = FALSE;	/* set if you have broken SMTP peers */
#endif
E 311
D 309
#ifdef NOLOOPBACKCHECK
bool	CheckLoopBack = FALSE;		/* set to check HELO loopback */
#else
bool	CheckLoopBack = TRUE;		/* set to check HELO loopback */
#endif

E 309
E 248
I 120
D 129
extern int la;				/* load average */
E 129
E 120
/*
**  SETDEFAULTS -- set default values
**
**	Because of the way freezing is done, these must be initialized
**	using direct code.
**
**	Parameters:
D 185
**		none.
E 185
I 185
**		e -- the default envelope.
E 185
**
**	Returns:
**		none.
**
**	Side Effects:
**		Initializes a bunch of global variables to their
**		default values.
*/

I 187
#define DAYS		* 24 * 60 * 60

I 344
void
E 344
E 187
D 185
setdefaults()
E 185
I 185
setdefaults(e)
	register ENVELOPE *e;
E 185
{
I 314
	int i;
I 344
	extern void inittimeouts();
	extern void setdefuser();
	extern void setupmaps();
	extern void setupmailers();
E 344

E 314
D 153
	QueueLA = 8;
	QueueFactor = 10000;
	RefuseLA = 12;
	SpaceSub = ' ';
I 105
	WkRecipFact = 1000;
	WkClassFact = 1800;
D 106
	WkTimeFact = -600;
E 106
I 106
D 112
	WkTimeFact = 600;
E 112
I 112
	WkTimeFact = 9000;
E 153
I 153
	SpaceSub = ' ';				/* option B */
	QueueLA = 8;				/* option x */
	RefuseLA = 12;				/* option X */
	WkRecipFact = 30000L;			/* option y */
	WkClassFact = 1800L;			/* option z */
	WkTimeFact = 90000L;			/* option Z */
	QueueFactor = WkRecipFact * 20;		/* option q */
E 153
E 112
E 106
D 145
	FileMode = 0644;
E 145
I 145
D 213
	FileMode = (getuid() != geteuid()) ? 0644 : 0600;
E 213
I 213
	FileMode = (RealUid != geteuid()) ? 0644 : 0600;
E 213
E 145
D 153
	DefUid = 1;
	DefGid = 1;
I 126
	CheckpointInterval = 10;
I 127
D 145
	MaxHopCount = MAXHOP;
E 145
I 145
	MaxHopCount = 17;
E 145
I 130
	SendMode = SM_FORK;
	ErrorMode = EM_PRINT;
I 131
	EightBit = FALSE;
I 135
	MaxMciCache = 1;
	MciCacheTimeout = 300;
E 153
I 153
						/* option F */
	DefUid = 1;				/* option u */
	DefGid = 1;				/* option g */
	CheckpointInterval = 10;		/* option C */
	MaxHopCount = 25;			/* option h */
D 185
	SendMode = SM_FORK;			/* option d */
	ErrorMode = EM_PRINT;			/* option e */
E 185
I 185
	e->e_sendmode = SM_FORK;		/* option d */
	e->e_errormode = EM_PRINT;		/* option e */
E 185
D 199
	EightBit = FALSE;			/* option 8 */
E 199
I 199
D 310
	SevenBit = FALSE;			/* option 7 */
E 310
I 310
	SevenBitInput = FALSE;			/* option 7 */
E 310
E 199
	MaxMciCache = 1;			/* option k */
	MciCacheTimeout = 300;			/* option K */
	LogLevel = 9;				/* option L */
D 167
	ReadTimeout = 2 * 60 * 60;		/* option r */
	TimeOut = 3 * 24 * 60 * 60;		/* option T */
E 167
I 167
D 326
	settimeouts(NULL);			/* option r */
E 326
I 326
	inittimeouts(NULL);			/* option r */
E 326
D 187
	TimeOut = 5 * 24 * 60 * 60;		/* option T */
E 187
I 187
D 314
	TimeOuts.to_q_return = 5 DAYS;		/* option T */
	TimeOuts.to_q_warning = 0;		/* option T */
E 314
I 188
D 191
	PrivacyFlags = PRIV_AUTHWARNINGS;	/* option p */
E 191
I 191
	PrivacyFlags = 0;			/* option p */
I 379
#if MIME8TO7
E 379
I 310
	MimeMode = MM_CVTMIME|MM_PASS8BIT;	/* option 8 */
I 379
#else
	MimeMode = MM_PASS8BIT;
#endif
E 379
I 314
	for (i = 0; i < MAXTOCLASS; i++)
	{
		TimeOuts.to_q_return[i] = 5 DAYS;	/* option T */
		TimeOuts.to_q_warning[i] = 0;		/* option T */
	}
I 322
	ServiceSwitchFile = "/etc/service.switch";
I 374
	HostsFile = _PATH_HOSTS;
E 374
E 322
E 314
E 310
E 191
E 188
E 187
E 167
E 153
E 135
E 131
E 130
E 127
E 126
I 121
	setdefuser();
I 198
D 203
	setupaliases();
E 203
E 198
I 134
	setupmaps();
I 151
	setupmailers();
E 151
E 134
E 121
E 105
}
I 121


/*
**  SETDEFUSER -- set/reset DefUser using DefUid (for initgroups())
*/

I 344
void
E 344
setdefuser()
{
	struct passwd *defpwent;
I 150
	static char defuserbuf[40];
E 150

D 150
	if (DefUser != NULL)
		free(DefUser);
E 150
I 150
	DefUser = defuserbuf;
E 150
D 358
	if ((defpwent = getpwuid(DefUid)) != NULL)
E 358
I 358
	if ((defpwent = sm_getpwuid(DefUid)) != NULL)
E 358
D 150
		DefUser = newstr(defpwent->pw_name);
E 150
I 150
		strcpy(defuserbuf, defpwent->pw_name);
E 150
	else
D 150
		DefUser = newstr("nobody");
E 150
I 150
		strcpy(defuserbuf, "nobody");
E 150
D 203
}
I 134
/*
**  SETUPMAPS -- set up map classes
**
**	Since these are compiled in, they cannot be in the config file.
**
*/
E 134

I 134
setupmaps()
{
	register STAB *s;
D 143
	MAPCLASS *hostmapclass;
E 143
I 143
D 190
	extern bool host_map_init();
E 143
	extern char *maphostname();
E 190
E 134
E 121
E 103
E 93
E 91
E 90
E 78
E 54
E 52
I 44
D 76


I 47
/*
**  Other configuration.
*/

D 65
int	DefUid = 1;		/* the uid to execute mailers as */
int	DefGid = 1;		/* ditto for gid */
I 54
D 61
time_t	TimeOut = 3*24*60*60;	/* default timeout for queue files */
E 61
I 61
time_t	TimeOut = 3*24*60*60L;	/* default timeout for queue files */
E 65
I 65
int	DefUid =	1;		/* the uid to execute mailers as */
int	DefGid =	1;		/* ditto for gid */
time_t	TimeOut =	3*24*60*60L;	/* default timeout for queue files */
I 66
D 71
char	*TextTimeOut =	"three days";	/* text of above for error messages */
E 71
E 66
int	ReadTimeout =	10*60;		/* timeout on external reads */
I 67
D 68
int	LogLevel =	2;		/* default logging level */
E 68
I 68
int	LogLevel =	9;		/* default logging level */
I 75
bool	SuperSafe =	TRUE;		/* always create qf file */
E 75
E 68
E 67
E 65
E 61
E 54


E 47

/*
**  V6 system configuration.
*/

# ifdef V6
char	*StdTimezone =	"PST";		/* std time timezone */
char	*DstTimezone =	"PDT";		/* daylight time timezone */
# endif V6
E 76
E 44
E 42
E 34
D 23
/*
**  INITMACS -- initialize predefined macros.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Macros array gets initialized.
*/

char	*Macro[26];

# define MACRO(x)	Macro[x - 'A']

initmacs()
{
	MACRO('A') = ArpaHost;
	MACRO('B') = BerkHost;
	MACRO('U') = UucpHost;
D 19
}
E 17
E 9
/*
**  GETNAME -- Get the current users login name.
**
**	This is in config.c because it is somewhat machine dependent.
**	Examine it carefully for your installation.
**
**	Algorithm:
**		See if the person is logged in.  If so, return
**			the name s/he is logged in as.
**		Look up the user id in /etc/passwd.  If found,
**			return that name.
**		Return NULL.
**
**	Parameters:
**		none
**
**	Returns:
**		The login name of this user.
**		NULL if this person is noone.
**
**	Side Effects:
**		none
**
D 4
**	Requires:
**		getlogin (sys)
**		getpwuid (sys)
**		getuid (sys)
**
E 4
**	Called By:
**		main
D 4
**
**	History:
**		12/26/79 -- written.
E 4
*/

char *
getname()
{
	register char *p;
	register struct passwd *w;
	extern char *getlogin();
	extern struct passwd *getpwuid();
	static char namebuf[9];

	p = getlogin();
	if (p != NULL && p[0] != '\0')
		return (p);
# ifdef V6
	w = getpwuid(getuid() & 0377);
# else
	w = getpwuid(getuid());
# endif V6
	if (w != NULL)
	{
		strcpy(namebuf, w->pw_name);
		return (namebuf);
	}
	return (NULL);
E 19
}
E 23
D 114

# ifdef V6
/*
D 36
**  TTYPATH -- Get the path of the user's tty -- Version 6 version.
E 36
I 36
**  TTYNAME -- return name of terminal.
E 36
**
D 36
**	Returns the pathname of the user's tty.  Returns NULL if
**	the user is not logged in or if s/he has write permission
**	denied.
**
E 36
**	Parameters:
D 36
**		none
E 36
I 36
**		fd -- file descriptor to check.
E 36
**
**	Returns:
D 36
**		pathname of the user's tty.
**		NULL if not logged in or write permission denied.
E 36
I 36
**		pointer to full path of tty.
**		NULL if no tty.
E 36
**
**	Side Effects:
**		none.
D 36
**
**	WARNING:
**		Return value is in a local buffer.
**
D 4
**	Requires:
**		stat (sys)
**		ttyn (sys)
**		open (sys)
**		read (sys)
**		close (sys)
**		seek (sys)
**
E 4
**	Called By:
**		savemail
E 36
D 4
**
**	History:
**		1/12/80 -- written.
E 4
*/
E 114

D 33
# include <sys/types.h>
E 33
D 36
# include <sys/stat.h>

E 36
D 114
char *
D 36
ttypath()
E 36
I 36
ttyname(fd)
	int fd;
E 36
{
D 36
	struct stat stbuf;
	register int i;
E 36
I 36
	register char tn;
E 36
	static char pathn[] = "/dev/ttyx";
D 31
	extern int errno;
E 31

	/* compute the pathname of the controlling tty */
D 36
	if ((i = ttyn(2)) == 'x' && (i = ttyn(1)) == 'x' && (i = ttyn(0)) == 'x')
E 36
I 36
	if ((tn = ttyn(fd)) == NULL)
E 36
	{
		errno = 0;
		return (NULL);
	}
D 36
	pathn[8] = i;

	/* see if we have write permission */
D 18
	if (stat(pathn, &stbuf) < 0 || !flagset(02, stbuf.st_mode))
E 18
I 18
	if (stat(pathn, &stbuf) < 0 || !bitset(02, stbuf.st_mode))
E 18
	{
		errno = 0;
		return (NULL);
	}

	/* see if the user is logged in */
	if (getlogin() == NULL)
		return (NULL);

	/* looks good */
E 36
I 36
	pathn[8] = tn;
E 36
	return (pathn);
}
/*
**  FDOPEN -- Open a stdio file given an open file descriptor.
**
**	This is included here because it is standard in v7, but we
**	need it in v6.
**
**	Algorithm:
**		Open /dev/null to create a descriptor.
**		Close that descriptor.
**		Copy the existing fd into the descriptor.
**
**	Parameters:
**		fd -- the open file descriptor.
**		type -- "r", "w", or whatever.
**
**	Returns:
**		The file descriptor it creates.
**
**	Side Effects:
**		none
**
D 4
**	Requires:
**		fopen (sys)
**
E 4
**	Called By:
**		deliver
**
**	Notes:
**		The mode of fd must match "type".
*/

FILE *
fdopen(fd, type)
	int fd;
	char *type;
{
	register FILE *f;

	f = fopen("/dev/null", type);
D 31
	close(fileno(f));
E 31
I 31
	(void) close(fileno(f));
E 31
	fileno(f) = fd;
	return (f);
}
/*
**  INDEX -- Return pointer to character in string
**
**	For V7 compatibility.
**
**	Parameters:
**		s -- a string to scan.
**		c -- a character to look for.
**
**	Returns:
**		If c is in s, returns the address of the first
**			instance of c in s.
**		NULL if c is not in s.
**
**	Side Effects:
**		none.
D 4
**
**	Requires:
**		none.
**
**	History:
**		3/14/80 -- written.  Why isn't this in -lS?
E 4
*/

I 49
char *
E 49
index(s, c)
	register char *s;
	register char c;
{
	while (*s != '\0')
	{
		if (*s++ == c)
			return (--s);
	}
	return (NULL);
}
I 45
/*
**  UMASK -- fake the umask system call.
**
**	Since V6 always acts like the umask is zero, we will just
**	assume the same thing.
*/

/*ARGSUSED*/
umask(nmask)
{
	return (0);
}


E 114
D 134
/*
E 134
I 134
D 190
	/* set up host name lookup map */
	s = stab("host", ST_MAPCLASS, ST_ENTER);
D 143
	s->s_mapclass.map_init = NULL;
E 143
I 143
	s->s_mapclass.map_init = host_map_init;
E 143
	s->s_mapclass.map_lookup = maphostname;
E 190
I 190
	/* host name lookup map */
	{
		extern bool host_map_init();
		extern char *maphostname();
E 190
D 143
	hostmapclass = &s->s_mapclass;
E 143

D 143
	s = stab("host", ST_MAP, ST_ENTER);
	s->s_map.map_class = hostmapclass;
	s->s_map.map_flags = MF_VALID;

E 143
D 190
	/*
	**  Set up other map classes.
	*/
E 190
I 190
		s = stab("host", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = host_map_init;
		s->s_mapclass.map_lookup = maphostname;
	}

	/* dequote map */
	{
		extern bool dequote_init();
		extern char *dequote_map();

		s = stab("dequote", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = dequote_init;
		s->s_mapclass.map_lookup = dequote_map;
	}
E 190

# ifdef DBM_MAP
	/* dbm file access */
	{
D 143
		extern void dbm_map_init();
E 143
I 143
		extern bool dbm_map_init();
E 143
		extern char *dbm_map_lookup();

		s = stab("dbm", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = dbm_map_init;
		s->s_mapclass.map_lookup = dbm_map_lookup;
	}
# endif

# ifdef BTREE_MAP
	/* new database file access -- btree files */
	{
D 142
		extern void bt_map_init();
		extern char *bt_map_lookup();
E 142
I 142
		extern bool bt_map_init();
		extern char *db_map_lookup();
E 142

		s = stab("btree", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = bt_map_init;
D 142
		s->s_mapclass.map_lookup = bt_map_lookup;
E 142
I 142
		s->s_mapclass.map_lookup = db_map_lookup;
E 142
	}
# endif

# ifdef HASH_MAP
	/* new database file access -- hash files */
	{
D 142
		extern void hash_map_init();
		extern char *hash_map_lookup();
E 142
I 142
		extern bool hash_map_init();
		extern char *db_map_lookup();
E 142

		s = stab("hash", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = hash_map_init;
D 142
		s->s_mapclass.map_lookup = hash_map_lookup;
E 142
I 142
		s->s_mapclass.map_lookup = db_map_lookup;
E 142
	}
# endif

I 146
# ifdef NIS_MAP
	/* NIS map access */
	{
		extern bool nis_map_init();
		extern char *nis_map_lookup();

		s = stab("nis", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = nis_map_init;
		s->s_mapclass.map_lookup = nis_map_lookup;
	}
# endif

E 146
# ifdef USERDB_MAP
	/* user database */
	{
D 143
		extern void udb_map_init();
E 143
I 143
		extern bool udb_map_init();
E 143
		extern char *udb_map_lookup();

		s = stab("udb", ST_MAPCLASS, ST_ENTER);
		s->s_mapclass.map_init = udb_map_init;
		s->s_mapclass.map_lookup = udb_map_lookup;
	}
# endif
E 203
}
I 143
/*
**  HOST_MAP_INIT -- initialize host class structures
*/

I 316
bool	host_map_init __P((MAP *map, char *args));

E 316
bool
D 207
host_map_init(map, mapname, args)
E 207
I 207
host_map_init(map, args)
E 207
	MAP *map;
D 207
	char *mapname;
E 207
	char *args;
{
	register char *p = args;

	for (;;)
	{
D 162
		while (isspace(*p))
E 162
I 162
		while (isascii(*p) && isspace(*p))
E 162
			p++;
		if (*p != '-')
			break;
		switch (*++p)
		{
		  case 'a':
			map->map_app = ++p;
			break;
		}
D 162
		while (*p != '\0' && !isspace(*p))
E 162
I 162
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 162
			p++;
		if (*p != '\0')
			*p++ = '\0';
	}
	if (map->map_app != NULL)
		map->map_app = newstr(map->map_app);
	return TRUE;
}
I 151
/*
**  SETUPMAILERS -- initialize default mailers
*/
E 151

I 344
void
E 344
I 151
setupmailers()
{
	char buf[100];
I 344
	extern void makemailer();
E 344

I 152
D 334
	strcpy(buf, "prog, P=/bin/sh, F=lsD, A=sh -c $u");
E 334
I 334
D 369
	strcpy(buf, "prog, P=/bin/sh, F=lsoD, A=sh -c $u");
E 369
I 369
D 393
	strcpy(buf, "prog, P=/bin/sh, F=lsoD, T=X-Unix, A=sh -c $u");
E 393
I 393
D 401
	strcpy(buf, "prog, P=/bin/sh, F=lsoD, T=DNS/RFC822/X-Unix, A=sh -c $u");
E 401
I 401
	strcpy(buf, "prog, P=/bin/sh, F=lsoD, T=DNS/RFC822/X-Unix, A=sh -c \201u");
E 401
E 393
E 369
E 334
	makemailer(buf);

E 152
D 201
	strcpy(buf, "*file*, P=/dev/null, F=lsDEu, A=FILE");
E 201
I 201
D 334
	strcpy(buf, "*file*, P=/dev/null, F=lsDFMPEu, A=FILE");
E 334
I 334
D 369
	strcpy(buf, "*file*, P=/dev/null, F=lsDFMPEou, A=FILE");
E 369
I 369
D 371
	strcpy(buf, "*file*, P=/dev/null, F=lsDFMPEou, T=X-Unix, A=FILE");
E 371
I 371
D 393
	strcpy(buf, "*file*, P=[FILE], F=lsDFMPEou, T=X-Unix, A=FILE");
E 393
I 393
	strcpy(buf, "*file*, P=[FILE], F=lsDFMPEou, T=DNS/RFC822/X-Unix, A=FILE");
E 393
E 371
E 369
E 334
E 201
	makemailer(buf);

	strcpy(buf, "*include*, P=/dev/null, F=su, A=INCLUDE");
	makemailer(buf);
}
E 151
E 143
/*
I 206
**  SETUPMAPS -- set up map classes
*/

#define MAPDEF(name, ext, flags, parse, open, close, lookup, store) \
	{ \
		extern bool parse __P((MAP *, char *)); \
		extern bool open __P((MAP *, int)); \
		extern void close __P((MAP *)); \
		extern char *lookup __P((MAP *, char *, char **, int *)); \
		extern void store __P((MAP *, char *, char *)); \
		s = stab(name, ST_MAPCLASS, ST_ENTER); \
		s->s_mapclass.map_cname = name; \
		s->s_mapclass.map_ext = ext; \
		s->s_mapclass.map_cflags = flags; \
		s->s_mapclass.map_parse = parse; \
		s->s_mapclass.map_open = open; \
		s->s_mapclass.map_close = close; \
		s->s_mapclass.map_lookup = lookup; \
		s->s_mapclass.map_store = store; \
	}

I 344
void
E 344
setupmaps()
{
	register STAB *s;

#ifdef NEWDB
	MAPDEF("hash", ".db", MCF_ALIASOK|MCF_REBUILDABLE,
		map_parseargs, hash_map_open, db_map_close,
		db_map_lookup, db_map_store);
I 314

E 314
	MAPDEF("btree", ".db", MCF_ALIASOK|MCF_REBUILDABLE,
		map_parseargs, bt_map_open, db_map_close,
		db_map_lookup, db_map_store);
#endif

#ifdef NDBM
	MAPDEF("dbm", ".dir", MCF_ALIASOK|MCF_REBUILDABLE,
		map_parseargs, ndbm_map_open, ndbm_map_close,
		ndbm_map_lookup, ndbm_map_store);
#endif

#ifdef NIS
	MAPDEF("nis", NULL, MCF_ALIASOK,
D 314
		map_parseargs, nis_map_open, nis_map_close,
		nis_map_lookup, nis_map_store);
E 314
I 314
		map_parseargs, nis_map_open, null_map_close,
		nis_map_lookup, null_map_store);
E 314
#endif

I 314
#ifdef NISPLUS
	MAPDEF("nisplus", NULL, MCF_ALIASOK,
		map_parseargs, nisplus_map_open, null_map_close,
		nisplus_map_lookup, null_map_store);
#endif

I 319
#ifdef HESIOD
	MAPDEF("hesiod", NULL, MCF_ALIASOK|MCF_ALIASONLY,
		map_parseargs, null_map_open, null_map_close,
D 339
		hesiod_map_lookup, null_map_store);
E 339
I 339
		hes_map_lookup, null_map_store);
E 339
#endif

I 320
D 410
#ifdef NETINFO
E 410
I 410
#if NETINFO
E 410
	MAPDEF("netinfo", NULL, MCF_ALIASOK,
		map_parseargs, ni_map_open, null_map_close,
		ni_map_lookup, null_map_store);
#endif

E 320
E 319
D 318
#if NAMED_BIND
# if 0
E 318
I 318
#if 0
E 318
	MAPDEF("dns", NULL, 0,
		dns_map_init, null_map_open, null_map_close,
		dns_map_lookup, null_map_store);
D 318
# endif
E 318
I 318
#endif
E 318

I 339
#if NAMED_BIND
	/* best MX DNS lookup */
	MAPDEF("bestmx", NULL, MCF_OPTFILE,
		map_parseargs, null_map_open, null_map_close,
		bestmx_map_lookup, null_map_store);
#endif

E 339
D 318
	/* old name for back compat */
E 318
	MAPDEF("host", NULL, 0,
		host_map_init, null_map_open, null_map_close,
		host_map_lookup, null_map_store);
D 318
#endif
E 318

I 322
	MAPDEF("text", NULL, MCF_ALIASOK,
		map_parseargs, text_map_open, null_map_close,
		text_map_lookup, null_map_store);

E 322
E 314
	MAPDEF("stab", NULL, MCF_ALIASOK|MCF_ALIASONLY,
D 314
		map_parseargs, stab_map_open, stab_map_close,
E 314
I 314
		map_parseargs, stab_map_open, null_map_close,
E 314
		stab_map_lookup, stab_map_store);

	MAPDEF("implicit", NULL, MCF_ALIASOK|MCF_ALIASONLY|MCF_REBUILDABLE,
		map_parseargs, impl_map_open, impl_map_close,
		impl_map_lookup, impl_map_store);

D 314
	/* host DNS lookup */
	MAPDEF("host", NULL, 0,
		host_map_init, null_map_open, null_map_close,
		host_map_lookup, null_map_store);
E 314
I 314
	/* access to system passwd file */
D 328
	MAPDEF("user", NULL, 0,
E 328
I 328
	MAPDEF("user", NULL, MCF_OPTFILE,
E 328
		map_parseargs, user_map_open, null_map_close,
		user_map_lookup, null_map_store);
E 314

	/* dequote map */
	MAPDEF("dequote", NULL, 0,
		dequote_init, null_map_open, null_map_close,
		dequote_map, null_map_store);

D 355
#if 0
# ifdef USERDB
E 355
I 355
D 392
#ifdef USERDB
E 392
I 392
#if USERDB
E 392
E 355
	/* user database */
D 355
	MAPDEF("udb", ".db", 0,
		udb_map_parse, null_map_open, null_map_close,
E 355
I 355
	MAPDEF("userdb", ".db", 0,
		map_parseargs, null_map_open, null_map_close,
E 355
		udb_map_lookup, null_map_store);
D 355
# endif
E 355
#endif
I 314

I 375
	/* arbitrary programs */
D 380
	MAPDEF("program", NULL, 0,
E 380
I 380
	MAPDEF("program", NULL, MCF_ALIASOK,
E 380
		map_parseargs, null_map_open, null_map_close,
		prog_map_lookup, null_map_store);

E 375
	/* sequenced maps */
	MAPDEF("sequence", NULL, MCF_ALIASOK,
D 322
		seq_map_parse, null_map_open, null_map_close,
E 322
I 322
D 333
		seq_map_parse, null_map_open, seq_map_close,
E 333
I 333
		seq_map_parse, null_map_open, null_map_close,
E 333
E 322
		seq_map_lookup, seq_map_store);
I 322

	/* switched interface to sequenced maps */
D 332
	MAPDEF("switch", NULL, MCF_ALIASOK|MCF_REBUILDABLE,
E 332
I 332
	MAPDEF("switch", NULL, MCF_ALIASOK,
E 332
D 333
		map_parseargs, switch_map_open, seq_map_close,
E 333
I 333
		map_parseargs, switch_map_open, null_map_close,
E 333
		seq_map_lookup, seq_map_store);
E 322
E 314
}

#undef MAPDEF
I 314
/*
**  INITHOSTMAPS -- initial host-dependent maps
**
**	This should act as an interface to any local service switch
**	provided by the host operating system.
**
**	Parameters:
**		none
**
**	Returns:
**		none
**
**	Side Effects:
D 322
**		Should define maps "host" and "passwd" as necessary
E 322
I 322
**		Should define maps "host" and "users" as necessary
E 322
**		for this OS.  If they are not defined, they will get
**		a default value later.  It should check to make sure
**		they are not defined first, since it's possible that
**		the config file has provided an override.
*/

void
inithostmaps()
{
I 330
	register int i;
	int nmaps;
I 398
D 399
	STAB *s;
E 399
E 398
	char *maptype[MAXMAPSTACK];
	short mapreturn[MAXMAPACTIONS];
E 330
I 322
	char buf[MAXLINE];

	/*
I 339
	**  Set up default hosts maps.
	*/

#if 0
	nmaps = switch_map_find("hosts", maptype, mapreturn);
	for (i = 0; i < nmaps; i++)
	{
		if (strcmp(maptype[i], "files") == 0 &&
		    stab("hosts.files", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "hosts.files text -k 0 -v 1 /etc/hosts");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
D 340
#ifdef NAMED_BIND
E 340
I 340
#if NAMED_BIND
E 340
		else if (strcmp(maptype[i], "dns") == 0 &&
		    stab("hosts.dns", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "hosts.dns dns A");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
#endif
#ifdef NISPLUS
		else if (strcmp(maptype[i], "nisplus") == 0 &&
		    stab("hosts.nisplus", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "hosts.nisplus nisplus -k name -v address -d hosts.org_dir");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
#endif
#ifdef NIS
		else if (strcmp(maptype[i], "nis") == 0 &&
		    stab("hosts.nis", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "hosts.nis nis -d -k 0 -v 1 hosts.byname");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
#endif
	}
#endif

	/*
E 339
	**  Make sure we have a host map.
	*/

	if (stab("host", ST_MAP, ST_FIND) == NULL)
	{
		/* user didn't initialize: set up host map */
		strcpy(buf, "host host");
#if NAMED_BIND
		if (ConfigLevel >= 2)
			strcat(buf, " -a.");
#endif
D 399
		makemapentry(buf);
E 399
I 399
		(void) makemapentry(buf);
E 399
	}

	/*
	**  Set up default aliases maps
	*/

D 330
	if (stab("aliases.files", ST_MAP, ST_FIND) == NULL)
E 330
I 330
	nmaps = switch_map_find("aliases", maptype, mapreturn);
	for (i = 0; i < nmaps; i++)
E 330
	{
D 330
		strcpy(buf, "aliases.files implicit /etc/aliases");
		makemapentry(buf);
	}
E 330
I 330
		if (strcmp(maptype[i], "files") == 0 &&
		    stab("aliases.files", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "aliases.files implicit /etc/aliases");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
E 330
#ifdef NISPLUS
D 330
	if (stab("aliases.nisplus", ST_MAP, ST_FIND) == NULL)
	{
		strcpy(buf, "aliases.nisplus nisplus -kalias -vexpansion -d mail_aliases.org_dir");
		makemapentry(buf);
	}
E 330
I 330
		else if (strcmp(maptype[i], "nisplus") == 0 &&
		    stab("aliases.nisplus", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "aliases.nisplus nisplus -kalias -vexpansion -d mail_aliases.org_dir");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
E 330
#endif
#ifdef NIS
D 330
	if (stab("aliases.nis", ST_MAP, ST_FIND) == NULL)
	{
		strcpy(buf, "aliases.nis nis -d mail.aliases");
		makemapentry(buf);
	}
E 330
I 330
		else if (strcmp(maptype[i], "nis") == 0 &&
		    stab("aliases.nis", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "aliases.nis nis -d mail.aliases");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
E 330
#endif
I 399
#ifdef HESIOD
		else if (strcmp(maptype[i], "hesiod") == 0 &&
		    stab("aliases.hesiod", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "aliases.hesiod hesiod aliases");
			(void) makemapentry(buf);
		}
#endif
E 399
I 330
	}
E 330
D 398
	if (stab("aliases", ST_MAP, ST_FIND) == NULL)
E 398
I 398
D 399
	s = stab("aliases", ST_MAP, ST_FIND);
	if (s == NULL)
E 399
I 399
	if (stab("aliases", ST_MAP, ST_FIND) == NULL)
E 399
E 398
	{
		strcpy(buf, "aliases switch aliases");
D 399
		makemapentry(buf);
I 398
		s = stab("aliases", ST_MAP, ST_FIND);
E 399
I 399
		(void) makemapentry(buf);
E 399
E 398
	}
D 398
	strcpy(buf, "switch:aliases");
	setalias(buf);
E 398
I 398
D 399
	if (s == NULL)
		syserr("inithostmaps: cannot initialize default aliases map");
	else
	{
		extern MAP *AliasDB[MAXALIASDB + 1];
E 399

D 399
		AliasDB[0] = &s->s_map;
	}
E 398

E 399
#if 0		/* "user" map class is a better choice */
	/*
	**  Set up default users maps.
	*/

D 330
	if (stab("users.files", ST_MAP, ST_FIND) == NULL)
E 330
I 330
	nmaps = switch_map_find("passwd", maptype, mapreturn);
	for (i = 0; i < nmaps; i++)
E 330
	{
D 330
		strcpy(buf, "users.files text -m -z: -k0 -v6 /etc/passwd");
		makemapentry(buf);
	}
E 330
I 330
		if (strcmp(maptype[i], "files") == 0 &&
		    stab("users.files", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "users.files text -m -z: -k0 -v6 /etc/passwd");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
E 330
#ifdef NISPLUS
D 330
	if (stab("users.nisplus", ST_MAP, ST_FIND) == NULL)
	{
		strcpy(buf, "users.nisplus nisplus -m -kname -vhome -d passwd.org_dir");
		makemapentry(buf);
	}
E 330
I 330
		else if (strcmp(maptype[i], "nisplus") == 0 &&
		    stab("users.nisplus", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "users.nisplus nisplus -m -kname -vhome -d passwd.org_dir");
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
E 330
#endif
#ifdef NIS
D 330
	if (stab("users.nis", ST_MAP, ST_FIND) == NULL)
	{
		strcpy(buf, "users.nis nis -m -d passwd.byname");
		makemapentry(buf);
	}
E 330
I 330
		else if (strcmp(maptype[i], "nis") == 0 &&
		    stab("users.nis", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "users.nis nis -m -d passwd.byname");
I 339
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
#endif
#ifdef HESIOD
		else if (strcmp(maptype[i], "hesiod") == 0) &&
		    stab("users.hesiod", ST_MAP, ST_FIND) == NULL)
		{
			strcpy(buf, "users.hesiod hesiod");
E 339
D 399
			makemapentry(buf);
E 399
I 399
			(void) makemapentry(buf);
E 399
		}
E 330
#endif
I 330
	}
E 330
	if (stab("users", ST_MAP, ST_FIND) == NULL)
	{
		strcpy(buf, "users switch -m passwd");
D 399
		makemapentry(buf);
E 399
I 399
		(void) makemapentry(buf);
E 399
	}
#endif
}
/*
**  SWITCH_MAP_FIND -- find the list of types associated with a map
**
**	This is the system-dependent interface to the service switch.
**
**	Parameters:
**		service -- the name of the service of interest.
**		maptype -- an out-array of strings containing the types
**			of access to use for this service.  There can
**			be at most MAXMAPSTACK types for a single service.
I 323
**		mapreturn -- an out-array of return information bitmaps
**			for the map.
E 323
**
**	Returns:
**		The number of map types filled in, or -1 for failure.
*/

I 323
#ifdef SOLARIS
# include <nsswitch.h>
#endif

D 403
#if defined(ultrix) || defined(__osf__)
E 403
I 403
#if defined(ultrix) || (defined(__osf__) && defined(__alpha))
# define _USE_DEC_SVC_CONF_
#endif

#ifdef _USE_DEC_SVC_CONF_
E 403
# include <sys/svcinfo.h>
#endif

E 323
int
D 323
switch_map_find(service, maptype)
E 323
I 323
switch_map_find(service, maptype, mapreturn)
E 323
	char *service;
	char *maptype[MAXMAPSTACK];
I 323
D 327
	short mapreturn[3];
E 327
I 327
	short mapreturn[MAXMAPACTIONS];
E 327
E 323
{
	register FILE *fp;
	int svcno;
	static char buf[MAXLINE];

E 322
#ifdef SOLARIS
I 322
	struct __nsw_switchconfig *nsw_conf;
	enum __nsw_parse_err pserr;
	struct __nsw_lookup *lk;
	int nsw_rc;
	static struct __nsw_lookup lkp0 =
		{ "files", {1, 0, 0, 0}, NULL, NULL };
	static struct __nsw_switchconfig lkp_default =
		{ 0, "sendmail", 3, &lkp0 };

	if ((nsw_conf = __nsw_getconfig(service, &pserr)) == NULL)
		lk = lkp_default.lookups;
	else
		lk = nsw_conf->lookups;
	svcno = 0;
	while (lk != NULL)
	{
		maptype[svcno] = lk->service_name;
		if (lk->actions[__NSW_NOTFOUND] == __NSW_RETURN)
D 323
			map->map_return[MA_NOTFOUND] |= 1 << svcno;
E 323
I 323
			mapreturn[MA_NOTFOUND] |= 1 << svcno;
E 323
		if (lk->actions[__NSW_TRYAGAIN] == __NSW_RETURN)
D 323
			map->map_return[MA_TRYAGAIN] |= 1 << svcno;
E 323
I 323
			mapreturn[MA_TRYAGAIN] |= 1 << svcno;
E 323
		if (lk->actions[__NSW_UNAVAIL] == __NSW_RETURN)
D 323
			map->map_return[MA_TRYAGAIN] |= 1 << svcno;
E 323
I 323
			mapreturn[MA_TRYAGAIN] |= 1 << svcno;
E 323
		svcno++;
I 325
		lk = lk->next;
E 325
	}
	return svcno;
#endif

D 403
#if defined(ultrix) || defined(__osf__)
E 403
I 403
#ifdef _USE_DEC_SVC_CONF_
E 403
	struct svcinfo *svcinfo;
	int svc;

I 374
	for (svcno = 0; svcno < MAXMAPACTIONS; svcno++)
		mapreturn[svcno] = 0;

E 374
D 325
	svc = getsvc();
E 325
I 325
	svcinfo = getsvc();
	if (svcinfo == NULL)
		goto punt;
E 325
	if (strcmp(service, "hosts") == 0)
		svc = SVC_HOSTS;
D 323
	else if strcmp(service, "aliases") == 0)
E 323
I 323
	else if (strcmp(service, "aliases") == 0)
E 323
		svc = SVC_ALIASES;
	else if (strcmp(service, "passwd") == 0)
		svc = SVC_PASSWD;
	else
		return -1;
	for (svcno = 0; svcno < SVC_PATHSIZE; svcno++)
	{
		switch (svcinfo->svcpath[svc][svcno])
		{
		  case SVC_LOCAL:
			maptype[svcno] = "files";
			break;

		  case SVC_YP:
			maptype[svcno] = "nis";
			break;

		  case SVC_BIND:
			maptype[svcno] = "dns";
			break;

#ifdef SVC_HESIOD
		  case SVC_HESIOD:
			maptype[svcno] = "hesiod";
			break;
#endif

		  case SVC_LAST:
D 325
			svcno = SVC_PATHSIZE;
			break;
E 325
I 325
			return svcno;
E 325
		}
	}
	return svcno;
#endif

D 403
#if !defined(SOLARIS) && !defined(ultrix) && !defined(__osf__)
E 403
I 403
#if !defined(SOLARIS) && !defined(_USE_DEC_SVC_CONF_)
E 403
	/*
	**  Fall-back mechanism.
	*/

I 374
	for (svcno = 0; svcno < MAXMAPACTIONS; svcno++)
		mapreturn[svcno] = 0;

E 374
	svcno = 0;
	fp = fopen(ServiceSwitchFile, "r");
	if (fp != NULL)
	{
		while (fgets(buf, sizeof buf, fp) != NULL)
		{
			register char *p;

			p = strpbrk(buf, "#\n");
			if (p != NULL)
				*p = '\0';
			p = strpbrk(buf, " \t");
			if (p != NULL)
				*p++ = '\0';
			if (strcmp(buf, service) != 0)
				continue;

			/* got the right service -- extract data */
			do
			{
				while (isspace(*p))
					p++;
				if (*p == '\0')
					break;
				maptype[svcno++] = p;
				p = strpbrk(p, " \t");
				if (p != NULL)
					*p++ = '\0';
			} while (p != NULL);
D 405
			break;
E 405
I 405
			fclose(fp);
			return svcno;
E 405
		}
I 405

		/* service was not found -- use compiled in default */
E 405
		fclose(fp);
D 405
		return svcno;
E 405
	}
I 325
#endif
E 325

	/* if the service file doesn't work, use an absolute fallback */
I 325
  punt:
I 374
	for (svcno = 0; svcno < MAXMAPACTIONS; svcno++)
		mapreturn[svcno] = 0;
	svcno = 0;
E 374
E 325
	if (strcmp(service, "aliases") == 0)
	{
D 357
		maptype[0] = "files";
		return 1;
E 357
I 357
		maptype[svcno++] = "files";
#ifdef AUTO_NIS_ALIASES
# ifdef NISPLUS
		maptype[svcno++] = "nisplus";
# endif
# ifdef NIS
		maptype[svcno++] = "nis";
# endif
#endif
		return svcno;
E 357
	}
	if (strcmp(service, "hosts") == 0)
	{
# if NAMED_BIND
		maptype[svcno++] = "dns";
# else
#  if defined(sun) && !defined(BSD) && !defined(SOLARIS)
		/* SunOS */
		maptype[svcno++] = "nis";
#  endif
# endif
		maptype[svcno++] = "files";
		return svcno;
	}
	return -1;
E 322
D 325
#endif
E 325
}
E 314
/*
E 206
E 134
D 114
**  GETRUID -- get real user id.
*/

getruid()
{
	return (getuid() & 0377);
}


/*
**  GETRGID -- get real group id.
*/

getrgid()
{
	return (getgid() & 0377);
}


/*
**  GETEUID -- get effective user id.
*/

geteuid()
{
	return ((getuid() >> 8) & 0377);
}


/*
**  GETEGID -- get effective group id.
*/

getegid()
{
	return ((getgid() >> 8) & 0377);
}

# endif V6

# ifndef V6

/*
E 114
D 213
**  GETRUID -- get real user id (V7)
*/

getruid()
{
D 51
	return (getuid());
E 51
I 51
D 64
	if (Daemon)
E 64
I 64
D 81
	if (Mode == MD_DAEMON)
E 81
I 81
	if (OpMode == MD_DAEMON)
E 81
E 64
		return (RealUid);
	else
		return (getuid());
E 51
}


/*
**  GETRGID -- get real group id (V7).
*/

getrgid()
{
D 51
	return (getgid());
E 51
I 51
D 64
	if (Daemon)
E 64
I 64
D 81
	if (Mode == MD_DAEMON)
E 81
I 81
	if (OpMode == MD_DAEMON)
E 81
E 64
		return (RealGid);
	else
		return (getgid());
E 51
}
D 134

E 45
D 114
# endif V6
D 36

# ifndef V6
/*
**  TTYPATH -- Get the path of the user's tty -- Version 7 version.
E 36
I 36
/*
E 114
I 114
/*
E 134
I 134
/*
E 213
E 134
E 114
I 82
**  USERNAME -- return the user id of the logged in user.
**
**	Parameters:
**		none.
**
**	Returns:
**		The login name of the logged in user.
**
**	Side Effects:
**		none.
**
**	Notes:
**		The return value is statically allocated.
*/

char *
username()
{
I 94
	static char *myname = NULL;
E 94
	extern char *getlogin();
I 96
	register struct passwd *pw;
D 125
	extern struct passwd *getpwuid();
E 125
E 96

D 94
	return (getlogin());
E 94
I 94
	/* cache the result */
	if (myname == NULL)
	{
		myname = getlogin();
		if (myname == NULL || myname[0] == '\0')
		{
D 96
			register struct passwd *pw;
			extern struct passwd *getpwuid();
E 96
D 186

E 186
D 213
			pw = getpwuid(getruid());
E 213
I 213
D 358
			pw = getpwuid(RealUid);
E 358
I 358
			pw = sm_getpwuid(RealUid);
E 358
E 213
			if (pw != NULL)
D 123
				myname = pw->pw_name;
E 123
I 123
				myname = newstr(pw->pw_name);
E 123
		}
I 95
D 96
		else {
			register struct passwd *pw;
			extern struct passwd *getpwuid();
E 96
I 96
		else
		{
I 186
D 213
			uid_t uid = getuid();
E 213
I 213
			uid_t uid = RealUid;
E 213
E 186
E 96

D 123
			pw = getpwnam(myname);
D 96
			if(getuid() != pw->pw_uid) {
E 96
I 96
			if(getuid() != pw->pw_uid)
E 123
I 123
			myname = newstr(myname);
D 358
			if ((pw = getpwnam(myname)) == NULL ||
E 358
I 358
			if ((pw = sm_getpwnam(myname)) == NULL ||
E 358
D 186
			      getuid() != pw->pw_uid)
E 186
I 186
			      (uid != 0 && uid != pw->pw_uid))
E 186
E 123
			{
E 96
D 186
				pw = getpwuid(getuid());
E 186
I 186
D 358
				pw = getpwuid(uid);
E 358
I 358
				pw = sm_getpwuid(uid);
E 358
E 186
D 101
				myname = pw->pw_name;
E 101
I 101
				if (pw != NULL)
D 123
					myname = pw->pw_name;
E 123
I 123
					myname = newstr(pw->pw_name);
E 123
E 101
			}
		}
E 95
		if (myname == NULL || myname[0] == '\0')
		{
D 172
			syserr("Who are you?");
E 172
I 172
			syserr("554 Who are you?");
E 172
			myname = "postmaster";
		}
	}

	return (myname);
E 94
}
/*
E 82
**  TTYPATH -- Get the path of the user's tty
E 36
**
**	Returns the pathname of the user's tty.  Returns NULL if
**	the user is not logged in or if s/he has write permission
**	denied.
**
**	Parameters:
**		none
**
**	Returns:
**		pathname of the user's tty.
**		NULL if not logged in or write permission denied.
**
**	Side Effects:
**		none.
**
**	WARNING:
**		Return value is in a local buffer.
**
D 4
**	Requires:
**		stat (sys)
**		ttyn (sys)
**		open (sys)
**		read (sys)
**		close (sys)
**		seek (sys)
**
E 4
**	Called By:
**		savemail
D 4
**
**	History:
**		1/12/80 -- written.
E 4
*/

D 33
# include <sys/types.h>
E 33
D 196
# include <sys/stat.h>

E 196
char *
ttypath()
{
	struct stat stbuf;
	register char *pathn;
D 31
	extern int errno;
E 31
	extern char *ttyname();
I 31
	extern char *getlogin();
E 31

	/* compute the pathname of the controlling tty */
D 82
	if ((pathn = ttyname(2)) == NULL && (pathn = ttyname(1)) == NULL && (pathn = ttyname(0)) == NULL)
E 82
I 82
	if ((pathn = ttyname(2)) == NULL && (pathn = ttyname(1)) == NULL &&
	    (pathn = ttyname(0)) == NULL)
E 82
	{
		errno = 0;
		return (NULL);
	}

	/* see if we have write permission */
D 18
	if (stat(pathn, &stbuf) < 0 || !flagset(02, stbuf.st_mode))
E 18
I 18
	if (stat(pathn, &stbuf) < 0 || !bitset(02, stbuf.st_mode))
E 18
	{
		errno = 0;
		return (NULL);
	}

	/* see if the user is logged in */
	if (getlogin() == NULL)
		return (NULL);

	/* looks good */
	return (pathn);
}
D 36
# endif V6
E 36
I 18
/*
**  CHECKCOMPAT -- check for From and To person compatible.
**
**	This routine can be supplied on a per-installation basis
**	to determine whether a person is allowed to send a message.
**	This allows restriction of certain types of internet
**	forwarding or registration of users.
**
**	If the hosts are found to be incompatible, an error
D 154
**	message should be given using "usrerr" and FALSE should
E 154
I 154
D 368
**	message should be given using "usrerr" and 0 should
E 154
**	be returned.
E 368
I 368
**	message should be given using "usrerr" and an EX_ code
**	should be returned.  You can also set to->q_status to
**	a DSN-style status code.
E 368
**
I 43
D 309
**	'NoReturn' can be set to suppress the return-to-sender
E 309
I 309
D 356
**	EF_NORETURN can be set in e->e_flags to suppress the return-to-sender
E 309
**	function; this should be done on huge messages.
E 356
I 356
**	EF_NO_BODY_RETN can be set in e->e_flags to suppress the
**	body during the return-to-sender function; this should be done
**	on huge messages.  This bit may already be set by the ESMTP
**	protocol.
E 356
**
E 43
**	Parameters:
**		to -- the person being sent to.
**
**	Returns:
D 154
**		TRUE -- ok to send.
**		FALSE -- not ok.
E 154
I 154
D 155
**		+1 -- ok to send.
**		0 -- not ok.
**		-1 -- return TEMPFAIL.
E 155
I 155
**		an exit status
E 155
E 154
**
**	Side Effects:
**		none (unless you include the usrerr stuff)
*/

I 344
int
E 344
D 154
bool
E 154
D 138
checkcompat(to)
E 138
I 138
checkcompat(to, e)
E 138
	register ADDRESS *to;
I 138
	register ENVELOPE *e;
E 138
{
I 88
# ifdef lint
	if (to == NULL)
		to++;
D 214
# endif lint
E 214
I 214
# endif /* lint */
I 244

	if (tTd(49, 1))
		printf("checkcompat(to=%s, from=%s)\n",
			to->q_paddr, e->e_from.q_paddr);

E 244
E 214
E 88
I 54
D 85
# ifdef ING70
E 85
I 85
# ifdef EXAMPLE_CODE
	/* this code is intended as an example only */
E 85
E 54
I 49
	register STAB *s;
I 54
D 85
# endif ING70
E 85
E 54

E 49
I 31
D 43
# ifdef lint
	ADDRESS *x = to;

	to = x;
# endif lint

E 43
I 43
D 53
	if (to->q_mailer != MN_LOCAL && MsgSize > 100000)
E 53
I 53
D 63
	if (to->q_mailer != LocalMailer && MsgSize > 100000)
E 63
I 63
D 85
	if (to->q_mailer != LocalMailer && CurEnv->e_msgsize > 100000)
E 63
E 53
	{
		usrerr("Message exceeds 100000 bytes");
		NoReturn++;
		return (FALSE);
	}
I 49
# ifdef ING70
E 85
	s = stab("arpa", ST_MAILER, ST_FIND);
D 50
	if (s != NULL && From.q_mailer != MN_LOCAL && to->q_mailer == s->st_mailer->m_mno)
E 50
I 50
D 53
	if (s != NULL && From.q_mailer != MN_LOCAL && to->q_mailer == s->s_mailer->m_mno)
E 53
I 53
D 63
	if (s != NULL && From.q_mailer != LocalMailer && to->q_mailer == s->s_mailer)
E 63
I 63
D 82
	if (s != NULL && CurEnv->e_from.q_mailer != LocalMailer && to->q_mailer == s->s_mailer)
E 82
I 82
D 138
	if (s != NULL && CurEnv->e_from.q_mailer != LocalMailer &&
E 138
I 138
D 309
	if (s != NULL && e->e_from.q_mailer != LocalMailer &&
E 309
I 309
	if (s != NULL && strcmp(e->e_from.q_mailer->m_name, "local") != 0 &&
E 309
E 138
	    to->q_mailer == s->s_mailer)
E 82
E 63
E 53
E 50
	{
D 172
		usrerr("No ARPA mail through this machine: see your system administration");
E 172
I 172
		usrerr("553 No ARPA mail through this machine: see your system administration");
E 172
I 85
D 309
		/* NoReturn = TRUE; to supress return copy */
E 309
I 309
D 356
		/* e->e_flags |= EF_NORETURN; to supress return copy */
E 356
I 356
		/* e->e_flags |= EF_NO_BODY_RETN; to supress body on return */
I 368
		to->q_status = "5.7.1";
E 368
E 356
E 309
E 85
D 155
		return (FALSE);
E 155
I 155
		return (EX_UNAVAILABLE);
E 155
	}
D 85
# endif ING70
E 85
I 85
D 141
# endif EXAMPLE_CODE
E 141
I 141
# endif /* EXAMPLE_CODE */
E 141
E 85
E 49
E 43
E 31
D 155
	return (TRUE);
E 155
I 155
	return (EX_OK);
E 155
I 82
}
/*
I 222
**  SETSIGNAL -- set a signal handler
**
**	This is essentially old BSD "signal(3)".
*/

D 247
setsig_t
E 247
I 247
sigfunc_t
E 247
setsignal(sig, handler)
	int sig;
D 247
	setsig_t handler;
E 247
I 247
	sigfunc_t handler;
E 247
{
D 223
#ifdef SYS5SIGNALS
E 223
I 223
D 242
#if defined(SYS5SIGNALS) || defined(BSD4_3)
E 242
I 242
D 412
#if defined(SYS5SIGNALS) || defined(BSD4_3) || defined(_AUX_SOURCE)
E 412
I 412
#if defined(SYS5SIGNALS) || defined(BSD4_3)
E 412
E 242
E 223
	return signal(sig, handler);
#else
	struct sigaction n, o;

	bzero(&n, sizeof n);
	n.sa_handler = handler;
I 302
# ifdef SA_RESTART
	n.sa_flags = SA_RESTART;
# endif
E 302
	if (sigaction(sig, &n, &o) < 0)
		return SIG_ERR;
	return o.sa_handler;
#endif
}
/*
I 416
**  RELEASESIGNAL -- release a held signal
**
**	Parameters:
**		sig -- the signal to release.
**
**	Returns:
**		0 on success.
**		-1 on failure.
*/

int
releasesignal(sig)
	int sig;
{
#ifdef BSD4_3
	return sigsetmask(sigblock(0) & ~(1 << sig));
#else
	sigset_t sset;

	sigemptyset(&sset);
	sigaddset(&sset, sig);
	return sigprocmask(SIG_UNBLOCK, &sset, NULL);
#endif
}
/*
E 416
E 222
**  HOLDSIGS -- arrange to hold all signals
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Arranges that signals are held.
*/

I 344
void
E 344
holdsigs()
{
}
/*
**  RLSESIGS -- arrange to release all signals
**
**	This undoes the effect of holdsigs.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Arranges that signals are released.
*/

I 344
void
E 344
rlsesigs()
{
E 82
}
I 90
/*
I 250
**  INIT_MD -- do machine dependent initializations
**
**	Systems that have global modes that should be set should do
**	them here rather than in main.
*/

#ifdef _AUX_SOURCE
# include	<compat.h>
#endif

I 344
void
E 344
D 254
init_md()
E 254
I 254
init_md(argc, argv)
	int argc;
	char **argv;
E 254
{
#ifdef _AUX_SOURCE
	setcompat(getcompat() | COMPAT_BSDPROT);
#endif
I 321

#ifdef VENDOR_DEFAULT
	VendorCode = VENDOR_DEFAULT;
#else
	VendorCode = VENDOR_BERKELEY;
#endif
E 321
}
/*
I 351
**  INIT_VENDOR_MACROS -- vendor-dependent macro initializations
**
**	Called once, on startup.
**
**	Parameters:
**		e -- the global envelope.
**
**	Returns:
**		none.
**
**	Side Effects:
**		vendor-dependent.
*/

void
init_vendor_macros(e)
	register ENVELOPE *e;
{
}
/*
E 351
E 250
**  GETLA -- get the current load average
**
I 92
**	This code stolen from la.c.
**
E 92
**	Parameters:
**		none.
**
**	Returns:
**		The current load average as an integer.
**
**	Side Effects:
**		none.
*/

D 118
#ifdef VMUNIX
E 118
I 118
D 128
#ifndef sun
E 128
I 128
D 129
#ifdef sun
E 129
I 129
/* try to guess what style of load average we have */
#define LA_ZERO		1	/* always return load average as zero */
D 239
#define LA_INT		2	/* read kmem for avenrun; interpret as int */
E 239
I 239
#define LA_INT		2	/* read kmem for avenrun; interpret as long */
E 239
#define LA_FLOAT	3	/* read kmem for avenrun; interpret as float */
#define LA_SUBR		4	/* call getloadavg */
I 230
#define LA_MACH		5	/* MACH load averages (as on NeXT boxes) */
I 239
#define LA_SHORT	6	/* read kmem for avenrun; interpret as short */
I 291
#define LA_PROCSTR	7	/* read string ("1.17") from /proc/loadavg */
I 376
#define LA_READKSYM	8	/* SVR4: use MIOC_READKSYM ioctl call */
#define LA_DGUX		9	/* special DGUX implementation */
#define LA_HPUX		10	/* special HPUX implementation */
E 376
E 291
E 239
E 230
E 129
E 128
E 118

I 216
/* do guesses based on general OS type */
E 216
I 129
#ifndef LA_TYPE
D 205
#  if defined(sun)
E 205
I 205
D 216
#  if defined(sun) && !defined(BSD)
E 205
#    define LA_TYPE		LA_INT
#  endif
D 161
#  if defined(mips)
     /* Ultrix or RISC/os */
E 161
I 161
#  if defined(mips) || defined(__alpha)
     /* Ultrix or OSF/1 or RISC/os */
E 161
#    define LA_TYPE		LA_INT
#    define LA_AVENRUN		"avenrun"
#  endif
D 196
#  if defined(hpux)
E 196
I 196
#  if defined(__hpux)
E 196
#    define LA_TYPE		LA_FLOAT
I 193
#    define LA_AVENRUN		"avenrun"
E 193
#  endif
I 212
#  if defined(__NeXT__)
#    define LA_TYPE		LA_ZERO
#  endif
E 212
D 159
#  if defined(BSD)
#    define LA_TYPE		LA_SUBR
#  endif
E 159

I 207
/* now do the guesses based on general OS type */
E 207
#  ifndef LA_TYPE
D 159
#    define LA_TYPE		LA_ZERO
E 159
I 159
#   if defined(SYSTEM5)
#    define LA_TYPE		LA_INT
#    define LA_AVENRUN		"avenrun"
#   else
#    if defined(BSD)
#     define LA_TYPE		LA_SUBR
#    else
#     define LA_TYPE		LA_ZERO
#    endif
#   endif
E 159
#  endif
E 216
I 216
# define LA_TYPE	LA_ZERO
E 216
#endif

I 376
#ifndef FSHIFT
# if defined(unixpc)
#  define FSHIFT	5
# endif

# if defined(__alpha) || defined(IRIX)
#  define FSHIFT	10
# endif

# if defined(_AIX3)
#  define FSHIFT	16
# endif
#endif

#ifndef FSHIFT
# define FSHIFT		8
#endif

#ifndef FSCALE
# define FSCALE		(1 << FSHIFT)
#endif

E 376
D 239
#if (LA_TYPE == LA_INT) || (LA_TYPE == LA_FLOAT)
E 239
I 239
D 389
#if (LA_TYPE == LA_INT) || (LA_TYPE == LA_FLOAT) || (LA_TYPE == LA_SHORT)
E 239

E 129
I 118
D 128
getla()
{
	double avenrun[3];

	if (getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0])) < 0)
		return (0);
	return ((int) (avenrun[0] + 0.5));
}

#else /* sun */

E 128
E 118
#include <nlist.h>
I 129
D 183
#include <fcntl.h>
E 183
E 129

I 331
#ifdef IRIX64
# define nlist		nlist64
#endif

E 389
E 331
I 129
#ifndef LA_AVENRUN
D 216
#define LA_AVENRUN	"_avenrun"
E 216
I 216
# ifdef SYSTEM5
#  define LA_AVENRUN	"avenrun"
# else
#  define LA_AVENRUN	"_avenrun"
# endif
E 216
#endif

I 389
#if (LA_TYPE == LA_INT) || (LA_TYPE == LA_FLOAT) || (LA_TYPE == LA_SHORT)

#include <nlist.h>

#ifdef IRIX64
# define nlist		nlist64
#endif

E 389
/* _PATH_UNIX should be defined in <paths.h> */
#ifndef _PATH_UNIX
D 196
#  if defined(hpux)
E 196
I 196
D 216
#  if defined(__hpux)
E 196
#    define _PATH_UNIX		"/hp-ux"
#  endif
#  if defined(mips) && !defined(ultrix)
     /* powerful RISC/os */
#    define _PATH_UNIX		"/unix"
#  endif
I 212
#  if defined(Solaris2)
     /* Solaris 2 */
#    define _PATH_UNIX		"/kernel/unix"
#  endif
E 212
I 159
#  if defined(SYSTEM5)
D 161
#    define _PATH_UNIX		"/unix"
E 161
I 161
#    ifndef _PATH_UNIX
#      define _PATH_UNIX	"/unix"
#    endif
E 161
#  endif
E 159
#  ifndef _PATH_UNIX
#    define _PATH_UNIX		"/vmunix"
#  endif
E 216
I 216
# if defined(SYSTEM5)
#  define _PATH_UNIX	"/unix"
# else
#  define _PATH_UNIX	"/vmunix"
# endif
E 216
#endif

I 412
#ifdef _AUX_SOURCE
struct nlist	Nl[2];
#else
E 412
E 129
D 376
struct	nlist Nl[] =
E 376
I 376
struct nlist	Nl[] =
E 376
{
D 129
	{ "_avenrun" },
E 129
I 129
	{ LA_AVENRUN },
E 129
D 412
#define	X_AVENRUN	0
E 412
	{ 0 },
};
I 412
#endif
#define	X_AVENRUN	0
E 412

I 159
D 209
#if defined(unixpc)
# define FSHIFT		5
I 161
#endif
E 209
I 209
D 376
#ifndef FSHIFT
# if defined(unixpc)
#  define FSHIFT	5
# endif
E 209

D 209
#if defined(__alpha)
# define FSHIFT		10
E 161
#endif
E 209
I 209
D 298
# if defined(__alpha)
E 298
I 298
# if defined(__alpha) || defined(IRIX)
E 298
#  define FSHIFT	10
# endif
I 338

# if defined(_AIX3)
#  define FSHIFT	16
# endif
E 338
I 300
#endif
E 300
E 209

E 159
I 129
D 209
#if (LA_TYPE == LA_INT) && !defined(FSHIFT)
E 209
I 209
D 239
# if (LA_TYPE == LA_INT)
E 239
I 239
D 300
# if (LA_TYPE == LA_INT) || (LA_TYPE == LA_SHORT)
E 239
E 209
#  define FSHIFT	8
I 209
# endif
E 300
I 300
#ifndef FSHIFT
# define FSHIFT		8
E 300
E 209
I 159
#endif
I 209

E 209
D 239
#if (LA_TYPE == LA_INT) && !defined(FSCALE)
E 239
I 239
D 300
#if ((LA_TYPE == LA_INT) || (LA_TYPE == LA_SHORT)) && !defined(FSCALE)
E 239
E 159
#  define FSCALE	(1 << FSHIFT)
E 300
I 300
#ifndef FSCALE
# define FSCALE		(1 << FSHIFT)
E 300
#endif
E 129
I 119

E 376
D 129
extern int la;

E 129
E 119
getla()
{
	static int kmem = -1;
I 129
#if LA_TYPE == LA_INT
E 129
I 103
D 118
# ifdef sun
E 118
	long avenrun[3];
I 129
#else
I 239
# if LA_TYPE == LA_SHORT
	short avenrun[3];
# else
E 239
	double avenrun[3];
I 239
# endif
E 239
#endif
E 129
D 118
# else
E 103
	double avenrun[3];
I 103
# endif
E 118
I 109
D 376
	extern off_t lseek();
E 376
I 159
D 204
	extern char *errstring();
E 204
	extern int errno;
I 376
	extern off_t lseek();
E 376
E 159
E 109
E 103

	if (kmem < 0)
	{
D 102
		kmem = open("/dev/kmem", 0);
E 102
I 102
		kmem = open("/dev/kmem", 0, 0);
E 102
		if (kmem < 0)
I 159
		{
			if (tTd(3, 1))
				printf("getla: open(/dev/kmem): %s\n",
					errstring(errno));
E 159
			return (-1);
I 159
		}
E 159
I 92
D 100
		(void) ioctl(kmem, FIOCLEX, 0);
E 100
I 100
D 129
		(void) ioctl(kmem, (int) FIOCLEX, (char *) 0);
E 100
E 92
		nlist("/vmunix", Nl);
E 129
I 129
		(void) fcntl(kmem, F_SETFD, 1);
I 412

#ifdef _AUX_SOURCE
		strcpy(Nl[X_AVENRUN].n_name, LA_AVENRUN);
#endif
E 412
I 376

E 376
I 338
#ifdef _AIX3
		if (knlist(Nl, 1, sizeof Nl[0]) < 0)
#else
E 338
D 159
		nlist(_PATH_UNIX, Nl);
E 129
		if (Nl[0].n_type == 0)
E 159
I 159
		if (nlist(_PATH_UNIX, Nl) < 0)
I 338
#endif
E 338
		{
			if (tTd(3, 1))
				printf("getla: nlist(%s): %s\n", _PATH_UNIX,
					errstring(errno));
I 193
			return (-1);
		}
		if (Nl[X_AVENRUN].n_value == 0)
		{
			if (tTd(3, 1))
				printf("getla: nlist(%s, %s) ==> 0\n",
					_PATH_UNIX, LA_AVENRUN);
E 193
E 159
			return (-1);
I 159
		}
I 298
D 305
#ifdef IRIX
		Nl[X_AVENRUN].n_value &= 0x7fffffff;
E 305
I 305
#ifdef NAMELISTMASK
		Nl[X_AVENRUN].n_value &= NAMELISTMASK;
E 305
#endif
E 298
E 159
	}
I 159
	if (tTd(3, 20))
		printf("getla: symbol address = %#x\n", Nl[X_AVENRUN].n_value);
E 159
D 97
	(void) lseek(kmem, (long) Nl[X_AVENRUN].n_value, 0);
	(void) read(kmem, avenrun, sizeof(avenrun));
E 97
I 97
D 100
	if (lseek(kmem, (long) Nl[X_AVENRUN].n_value, 0) < 0 ||
	    read(kmem, avenrun, sizeof(avenrun)) < sizeof(avenrun))
E 100
I 100
D 102
	if (lseek(kmem, (off_t) Nl[X_AVENRUN].n_value, 0) < 0 ||
E 102
I 102
D 338
	if (lseek(kmem, (off_t) Nl[X_AVENRUN].n_value, 0) == -1 ||
E 338
I 338
	if (lseek(kmem, (off_t) Nl[X_AVENRUN].n_value, SEEK_SET) == -1 ||
E 338
E 102
	    read(kmem, (char *) avenrun, sizeof(avenrun)) < sizeof(avenrun))
E 100
	{
		/* thank you Ian */
I 159
		if (tTd(3, 1))
			printf("getla: lseek or read: %s\n", errstring(errno));
E 159
		return (-1);
	}
I 129
D 239
#if LA_TYPE == LA_INT
E 239
I 239
D 376
#if (LA_TYPE == LA_INT) || (LA_TYPE == LA_SHORT)
E 376
I 376
# if (LA_TYPE == LA_INT) || (LA_TYPE == LA_SHORT)
E 376
E 239
I 159
	if (tTd(3, 5))
	{
		printf("getla: avenrun = %d", avenrun[0]);
		if (tTd(3, 15))
			printf(", %d, %d", avenrun[1], avenrun[2]);
		printf("\n");
	}
	if (tTd(3, 1))
		printf("getla: %d\n", (int) (avenrun[0] + FSCALE/2) >> FSHIFT);
E 159
E 129
I 103
D 118
# ifdef sun
E 118
	return ((int) (avenrun[0] + FSCALE/2) >> FSHIFT);
I 129
D 376
#else
E 376
I 376
# else /* LA_TYPE == LA_FLOAT */
E 376
I 159
	if (tTd(3, 5))
	{
		printf("getla: avenrun = %g", avenrun[0]);
		if (tTd(3, 15))
			printf(", %g, %g", avenrun[1], avenrun[2]);
		printf("\n");
	}
	if (tTd(3, 1))
		printf("getla: %d\n", (int) (avenrun[0] +0.5));
E 159
	return ((int) (avenrun[0] + 0.5));
D 376
#endif
E 376
I 376
# endif
E 376
E 129
D 118
# else
E 103
E 97
	return ((int) (avenrun[0] + 0.5));
I 103
# endif
E 118
E 103
}

D 118
#else VMUNIX

getla()
{
	return (0);
}

#endif VMUNIX
E 118
I 118
D 128
#endif /* sun */
E 128
I 128
D 376
#else
D 129
#ifdef ultrix
E 129
I 129
#if LA_TYPE == LA_SUBR
E 376
I 376
#endif /* LA_TYPE == LA_INT or LA_SHORT or LA_FLOAT */
E 376
E 129

I 251
D 376
#ifdef DGUX
E 376
I 376
#if LA_TYPE == LA_READKSYM
E 376

I 378
# include <sys/ksym.h>

E 378
D 376
#include <sys/dg_sys_info.h>
E 376
I 376
getla()
{
	static int kmem = -1;
	long avenrun[3];
	extern int errno;
	struct mioc_rksym mirk;
E 376

I 376
	if (kmem < 0)
	{
		kmem = open("/dev/kmem", 0, 0);
		if (kmem < 0)
		{
			if (tTd(3, 1))
				printf("getla: open(/dev/kmem): %s\n",
					errstring(errno));
			return (-1);
		}
		(void) fcntl(kmem, F_SETFD, 1);
	}
	mirk.mirk_symname = LA_AVENRUN;
	mirk.mirk_buf = avenrun;
	mirk.mirk_buflen = sizeof(avenrun);
	if (ioctl(kmem, MIOC_READKSYM, &mirk) < 0)
	{
		if (tTd(3, 1))
			printf("getla: ioctl(MIOC_READKSYM) failed: %s\n",
				errstring(errno));
		return -1;
	}
	if (tTd(3, 5))
	{
		printf("getla: avenrun = %d", avenrun[0]);
		if (tTd(3, 15))
			printf(", %d, %d", avenrun[1], avenrun[2]);
		printf("\n");
	}
	if (tTd(3, 1))
		printf("getla: %d\n", (int) (avenrun[0] + FSCALE/2) >> FSHIFT);
	return ((int) (avenrun[0] + FSCALE/2) >> FSHIFT);
}

#endif /* LA_TYPE == LA_READKSYM */

#if LA_TYPE == LA_DGUX

# include <sys/dg_sys_info.h>

E 376
D 342
int getla()
E 342
I 342
int
getla()
E 342
{
	struct dg_sys_info_load_info load_info;

	dg_sys_info((long *)&load_info,
		DG_SYS_INFO_LOAD_INFO_TYPE, DG_SYS_INFO_LOAD_VERSION_0);
I 331

        if (tTd(3, 1))
                printf("getla: %d\n", (int) (load_info.one_minute + 0.5));
E 331

	return((int) (load_info.one_minute + 0.5));
}

D 376
#else
I 342
# ifdef __hpux
E 376
I 376
#endif /* LA_TYPE == LA_DGUX */
E 376
E 342

I 376
#if LA_TYPE == LA_HPUX

I 386
/* forward declarations to keep gcc from complaining */
E 386
E 376
I 370
struct pst_dynamic;
I 386
struct pst_status;
struct pst_static;
struct pst_vminfo;
struct pst_diskinfo;
struct pst_processor;
struct pst_lv;
struct pst_swapinfo;
E 386

E 370
I 342
D 376
#  include <sys/param.h>
#  include <sys/pstat.h>
E 376
I 376
# include <sys/param.h>
# include <sys/pstat.h>
E 376

int
E 342
E 251
getla()
{
I 342
	struct pst_dynamic pstd;

	if (pstat_getdynamic(&pstd, sizeof(struct pst_dynamic),
D 370
			     (size_t) 1 ,0) == -1)
E 370
I 370
			     (size_t) 1, 0) == -1)
E 370
		return 0;

        if (tTd(3, 1))
                printf("getla: %d\n", (int) (pstd.psd_avg_1_min + 0.5));

	return (int) (pstd.psd_avg_1_min + 0.5);
}

D 376
# else
E 376
I 376
#endif /* LA_TYPE == LA_HPUX */
E 376

I 376
#if LA_TYPE == LA_SUBR

E 376
int
getla()
{
E 342
D 129
	return (0);
E 129
I 129
	double avenrun[3];

	if (getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0])) < 0)
I 159
	{
		if (tTd(3, 1))
			perror("getla: getloadavg failed:");
E 159
		return (-1);
I 159
	}
	if (tTd(3, 1))
		printf("getla: %d\n", (int) (avenrun[0] +0.5));
E 159
	return ((int) (avenrun[0] + 0.5));
E 129
}

I 342
D 376
# endif /* __hpux */
E 342
I 251
#endif /* DGUX */
E 251
#else
E 376
I 376
#endif /* LA_TYPE == LA_SUBR */

E 376
I 230
#if LA_TYPE == LA_MACH
E 230

I 230
/*
D 265
**  This has been tested on NeXT release 2.1.
E 265
I 265
**  This has been tested on NEXTSTEP release 2.1/3.X.
E 265
*/

D 265
#include <mach.h>
E 265
I 265
#if defined(NX_CURRENT_COMPILER_RELEASE) && NX_CURRENT_COMPILER_RELEASE > NX_COMPILER_RELEASE_3_0
# include <mach/mach.h>
#else
# include <mach.h>
#endif
E 265

E 230
getla()
{
I 230
	processor_set_t default_set;
	kern_return_t error;
	unsigned int info_count;
	struct processor_set_basic_info info;
	host_t host;

	error = processor_set_default(host_self(), &default_set);
	if (error != KERN_SUCCESS)
		return -1;
	info_count = PROCESSOR_SET_BASIC_INFO_COUNT;
	if (processor_set_info(default_set, PROCESSOR_SET_BASIC_INFO,
			       &host, (processor_set_info_t)&info,
			       &info_count) != KERN_SUCCESS)
	{
		return -1;
	}
	return (int) (info.load_average + (LOAD_SCALE / 2)) / LOAD_SCALE;
}

I 376
#endif /* LA_TYPE == LA_MACH */
E 376

D 376
#else
E 376
I 291
D 293
#if LA_TYPE == LA_PROC
E 293
I 293
#if LA_TYPE == LA_PROCSTR
E 293
E 291

I 291
/*
**  Read /proc/loadavg for the load average.  This is assumed to be
**  in a format like "0.15 0.12 0.06".
**
**	Initially intended for Linux.  This has been in the kernel
**	since at least 0.99.15.
*/

# ifndef _PATH_LOADAVG
#  define _PATH_LOADAVG	"/proc/loadavg"
# endif

int
E 291
getla()
{
I 291
D 294
	register double avenrun;
E 294
I 294
	double avenrun;
E 294
	register int result;
D 294
	static FILE *fp = NULL;
E 294
I 294
	FILE *fp;
E 294
D 293

D 292
	*avenrun = 0.0;
E 292
I 292
	avenrun = 0.0;
E 293
E 292

D 294
	if (fp == NULL)
E 294
I 294
	fp = fopen(_PATH_LOADAVG, "r");
D 377
	if (fp == NULL) 
E 377
I 377
	if (fp == NULL)
E 377
E 294
	{
D 294
		fp = fopen(_PATH_LOADAVG, "r");
		if (fp == NULL) 
		{
D 292
			if (tTd(3, 2))
E 292
I 292
			if (tTd(3, 1))
E 292
				printf("getla: fopen(%s): %s\n",
					_PATH_LOADAVG, errstring(errno));
			return -1;
		}
E 294
I 294
		if (tTd(3, 1))
			printf("getla: fopen(%s): %s\n",
				_PATH_LOADAVG, errstring(errno));
		return -1;
E 294
	}
D 294
	(void) rewind(fp);
E 294
	result = fscanf(fp, "%lf", &avenrun);
I 294
	fclose(fp);
E 294
	if (result != 1)
	{
D 292
		if (tTd(3, 2))
E 292
I 292
		if (tTd(3, 1))
E 292
			printf("getla: fscanf() = %d: %s\n",
				result, errstring(errno));
		return -1;
	}

E 291
E 230
I 159
	if (tTd(3, 1))
I 291
		printf("getla(): %.2f\n", avenrun);

	return ((int) (avenrun + 0.5));
}

D 376
#else
E 376
I 376
#endif /* LA_TYPE == LA_PROCSTR */
E 376

I 376
#if LA_TYPE == LA_ZERO

E 376
getla()
{
	if (tTd(3, 1))
E 291
		printf("getla: ZERO\n");
E 159
D 129
	double avenrun[3];

	if (getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0])) < 0)
		return (0);
	return ((int) (avenrun[0] + 0.5));
E 129
I 129
	return (0);
E 129
}

I 291
D 376
#endif
E 291
I 230
#endif
E 230
#endif
#endif
E 376
I 376
#endif /* LA_TYPE == LA_ZERO */
E 376
I 287


/*
 * Copyright 1989 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * M.I.T. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL M.I.T.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Authors:  Many and varied...
 */

/* Non Apollo stuff removed by Don Lewis 11/15/93 */
#ifndef lint
static char  rcsid[] = "@(#)$Id: getloadavg.c,v 1.16 1991/06/21 12:51:15 paul Exp $";
#endif /* !lint */

D 290
#   ifdef apollo
E 290
I 290
#ifdef apollo
E 290
# undef volatile
#    include <apollo/base.h>
D 290
#    include <apollo/time.h>
#    include <sys/types.h>
E 290

/* ARGSUSED */
int getloadavg( call_data )
     caddr_t	call_data;	/* pointer to (double) return value */
{
     double *avenrun = (double *) call_data;
     int i;
     status_$t      st;
     long loadav[3];
     proc1_$get_loadav(loadav, &st);
     *avenrun = loadav[0] / (double) (1 << 16);
     return(0);
}
#   endif /* apollo */
E 287
E 128
E 118
I 103
/*
**  SHOULDQUEUE -- should this message be queued or sent?
**
**	Compares the message cost to the load average to decide.
**
**	Parameters:
**		pri -- the priority of the message in question.
I 153
**		ctime -- the message creation time.
E 153
**
**	Returns:
**		TRUE -- if this message should be queued up for the
**			time being.
**		FALSE -- if the load is low enough to send this message.
**
**	Side Effects:
**		none.
*/

bool
D 153
shouldqueue(pri)
E 153
I 153
shouldqueue(pri, ctime)
E 153
	long pri;
I 153
	time_t ctime;
E 153
{
I 317
	bool rval;

	if (tTd(3, 30))
		printf("shouldqueue: CurrentLA=%d, pri=%d: ", CurrentLA, pri);
E 317
D 119
	int la;

	la = getla();
E 119
D 129
	if (la < QueueLA)
E 129
I 129
	if (CurrentLA < QueueLA)
I 317
	{
		if (tTd(3, 30))
			printf("FALSE (CurrentLA < QueueLA)\n");
E 317
E 129
		return (FALSE);
I 317
	}
E 317
I 170
	if (CurrentLA >= RefuseLA)
I 317
	{
		if (tTd(3, 30))
			printf("TRUE (CurrentLA >= RefuseLA)\n");
E 317
		return (TRUE);
E 170
D 129
	return (pri > (QueueFactor / (la - QueueLA + 1)));
E 129
I 129
D 317
	return (pri > (QueueFactor / (CurrentLA - QueueLA + 1)));
E 317
I 317
	}
	rval = pri > (QueueFactor / (CurrentLA - QueueLA + 1));
	if (tTd(3, 30))
		printf("%s (by calculation)\n", rval ? "TRUE" : "FALSE");
	return rval;
E 317
E 129
}
/*
I 133
**  REFUSECONNECTIONS -- decide if connections should be refused
**
**	Parameters:
**		none.
**
**	Returns:
**		TRUE if incoming SMTP connections should be refused
**			(for now).
**		FALSE if we should accept new work.
**
**	Side Effects:
D 406
**		none.
E 406
I 406
**		Sets process title when it is rejecting connections.
E 406
*/

bool
refuseconnections()
{
I 341
D 402
	extern bool enoughspace();
E 402
I 402
	extern bool enoughdiskspace();
I 406
D 408
	extern void setproctitle();
E 408
I 408
	extern void setproctitle __P((char *, ...));
E 408
E 406
E 402

E 341
I 192
#ifdef XLA
	if (!xla_smtp_ok())
		return TRUE;
#endif

E 192
D 406
	/* this is probably too simplistic */
D 170
	return (CurrentLA > RefuseLA);
E 170
I 170
D 341
	return (CurrentLA >= RefuseLA);
E 341
I 341
D 402
	return CurrentLA >= RefuseLA || !enoughspace(MinBlocksFree + 1);
E 402
I 402
	return CurrentLA >= RefuseLA || !enoughdiskspace(MinBlocksFree + 1);
E 406
I 406
	if (CurrentLA >= RefuseLA)
	{
		setproctitle("rejecting connections: load average: %d",
			CurrentLA);
	}
	else if (!enoughdiskspace(MinBlocksFree + 1))
	{
		setproctitle("rejecting connections: min free: %d",
			MinBlocksFree);
	}
	else if (MaxChildren > 0 && CurChildren >= MaxChildren)
	{
		setproctitle("rejecting connections: maximum children: %d",
			CurChildren);
	}
	else
		return FALSE;
	return TRUE;
E 406
E 402
E 341
E 170
}
/*
E 133
**  SETPROCTITLE -- set process title for ps
**
**	Parameters:
D 181
**		fmt -- a printf style format string.
**		a, b, c -- possible parameters to fmt.
E 181
I 181
**		fmt -- a printf style format string.  If NULL, the first
**			parameter is a literal proctitle previously
**			returned by getproctitle.
**		va_alist -- possible parameters to fmt.
E 181
**
**	Returns:
**		none.
**
**	Side Effects:
**		Clobbers argv of our main procedure so ps(1) will
**		display the title.
*/

I 183
D 315
#ifdef SETPROCTITLE
E 315
I 315
#define SPT_NONE	0	/* don't use it at all */
#define SPT_REUSEARGV	1	/* cover argv with title information */
#define SPT_BUILTIN	2	/* use libc builtin */
#define SPT_PSTAT	3	/* use pstat(PSTAT_SETCMD, ...) */
#define SPT_PSSTRINGS	4	/* use PS_STRINGS->... */
D 389
#define SPT_WRITEUDOT	5	/* write u. area in kmem */
E 389
I 389
#define SPT_SYSMIPS	5	/* use sysmips() supported by NEWS-OS 6 */
E 389
E 315
I 312

E 312
I 284
D 315
# ifdef HASSETPROCTITLE
   *** ERROR ***  Cannot have both SETPROCTITLE and HASSETPROCTITLE defined
# endif
E 315
I 315
#ifndef SPT_TYPE
# define SPT_TYPE	SPT_REUSEARGV
#endif
E 315
I 312

E 312
E 284
D 315
# ifdef __hpux
E 315
I 315
#if SPT_TYPE != SPT_NONE && SPT_TYPE != SPT_BUILTIN

# if SPT_TYPE == SPT_PSTAT
E 315
#  include <sys/pstat.h>
# endif
I 200
D 315
# ifdef BSD4_4
E 315
I 315
# if SPT_TYPE == SPT_PSSTRINGS
E 315
#  include <machine/vmparam.h>
#  include <sys/exec.h>
I 227
D 315
#  ifdef __bsdi__
#   undef PS_STRINGS	/* BSDI 1.0 doesn't do PS_STRINGS as we expect */
I 257
#   define PROCTITLEPAD	'\0'
E 315
I 315
#  ifndef PS_STRINGS	/* hmmmm....  apparently not available after all */
#   undef SPT_TYPE
#   define SPT_TYPE	SPT_REUSEARGV
I 364
#  else
#   ifndef NKPDE			/* FreeBSD 2.0 */
#    define NKPDE 63
typedef unsigned int	*pt_entry_t;
#   endif
E 364
E 315
E 257
#  endif
E 227
D 202
#  define SETPROC_STATIC static
E 202
I 202
D 315
#  ifdef PS_STRINGS
#   define SETPROC_STATIC static
#  endif
E 315
E 202
# endif
I 312
D 315
# ifdef _AIX3
#  define PROCTITLEPAD	'\0'
# endif
E 315

E 312
D 315
# ifndef SETPROC_STATIC
E 315
I 315
# if SPT_TYPE == SPT_PSSTRINGS
#  define SETPROC_STATIC	static
# else
E 315
#  define SETPROC_STATIC
# endif
I 312

I 389
# if SPT_TYPE == SPT_SYSMIPS
#  include <sys/sysmips.h>
#  include <sys/sysnews.h>
# endif

E 389
E 312
E 200
D 315
#endif
E 315
I 315
# ifndef SPT_PADCHAR
#  define SPT_PADCHAR	' '
# endif
E 315

I 257
D 315
#ifndef PROCTITLEPAD
# define PROCTITLEPAD	' '
#endif
E 315
I 315
#endif /* SPT_TYPE != SPT_NONE && SPT_TYPE != SPT_BUILTIN */
E 315

I 283
D 315
#ifndef HASSETPROCTITLE
E 315
I 315
#if SPT_TYPE != SPT_BUILTIN
E 315

E 283
E 257
E 183
I 181
char	ProcTitleBuf[MAXLINE];

E 181
/*VARARGS1*/
I 344
void
E 344
D 144
setproctitle(fmt, a, b, c)
E 144
I 144
D 157
setproctitle(fmt VA_ARG_FORMAL)
E 157
I 157
D 315
#ifdef __STDC__
E 315
I 315
# ifdef __STDC__
E 315
setproctitle(char *fmt, ...)
D 315
#else
E 315
I 315
# else
E 315
setproctitle(fmt, va_alist)
E 157
E 144
	char *fmt;
I 144
D 157
	VA_ARG_DECL
E 157
I 157
	va_dcl
D 315
#endif
E 315
I 315
# endif
E 315
E 157
E 144
{
D 315
# ifdef SETPROCTITLE
E 315
I 315
# if SPT_TYPE != SPT_NONE
E 315
	register char *p;
I 108
	register int i;
I 144
D 181
D 200
	char buf[MAXLINE];
E 200
I 200
	SETPROC_STATIC char buf[MAXLINE];
E 200
E 181
	VA_LOCAL_DECL
I 183
D 315
#  ifdef __hpux
E 315
I 315
#  if SPT_TYPE == SPT_PSTAT
E 315
	union pstun pst;
#  endif
I 394
#  if SPT_TYPE == SPT_REUSEARGV
E 394
E 183
E 144
E 108
	extern char **Argv;
	extern char *LastArgv;
I 394
#  endif
E 394
I 108
D 144
	char buf[MAXLINE];
E 144
E 108

D 108
	p = Argv[0];
E 108
I 108
D 136
	(void) sprintf(buf, fmt, a, b, c);
E 136
I 136
D 181
	p = buf;
E 181
I 181
	VA_START(fmt);
	if (fmt == NULL)
	{
		/* restore old proctitle */
		(void) strcpy(ProcTitleBuf, va_arg(ap, char *));
	}
	else
	{
		p = ProcTitleBuf;
E 181
E 136
E 108

D 136
	/* make ps print "(sendmail)" */
I 108
	p = Argv[0];
E 108
	*p++ = '-';
E 136
I 136
D 181
	/* print sendmail: heading for grep */
	(void) strcpy(p, "sendmail: ");
	p += strlen(p);
E 181
I 181
		/* print sendmail: heading for grep */
		(void) strcpy(p, "sendmail: ");
		p += strlen(p);
E 181
E 136

I 136
D 181
	/* print the argument string */
D 144
	(void) sprintf(p, fmt, a, b, c);
E 144
I 144
	VA_START(fmt);
	(void) vsprintf(p, fmt, ap);
E 181
I 181
		/* print the argument string */
		(void) vsprintf(p, fmt, ap);
	}
E 181
	VA_END;
E 144

E 136
D 108
	(void) sprintf(p, fmt, a, b, c);
	p += strlen(p);

	/* avoid confusing ps */
E 108
I 108
D 181
	i = strlen(buf);
I 183

D 315
#  ifdef __hpux
E 315
I 315
#  if SPT_TYPE == SPT_PSTAT
E 315
	pst.pst_command = buf;
	pstat(PSTAT_SETCMD, pst, i, 0, 0);
D 389
#  else
D 200

E 200
I 200
D 202
#   ifdef BSD4_4
E 202
I 202
D 315
#   ifdef PS_STRINGS
E 315
I 315
#   if SPT_TYPE == SPT_PSSTRINGS
E 389
I 389
#  endif
#  if SPT_TYPE == SPT_PSSTRINGS
E 389
E 315
E 202
	PS_STRINGS->ps_nargvstr = 1;
	PS_STRINGS->ps_argvstr = buf;
D 389
#   else
E 389
I 389
#  endif
#  if SPT_TYPE == SPT_SYSMIPS
	sysmips(SONY_SYSNEWS, NEWS_SETPSARGS, buf);
#  endif
#  if SPT_TYPE == SPT_REUSEARGV
E 389
E 200
E 183
E 181
I 181
	i = strlen(ProcTitleBuf);
E 181
D 136
	if (i > LastArgv - p - 2)
E 136
I 136
	if (i > LastArgv - Argv[0] - 2)
E 136
	{
D 136
		i = LastArgv - p - 2;
E 136
I 136
		i = LastArgv - Argv[0] - 2;
E 136
D 181
		buf[i] = '\0';
E 181
I 181
		ProcTitleBuf[i] = '\0';
E 181
	}
D 136
	(void) strcpy(p, buf);
	p += i;
E 136
I 136
D 181
	(void) strcpy(Argv[0], buf);
E 181
I 181
	(void) strcpy(Argv[0], ProcTitleBuf);
E 181
D 137
	p = Argv[i];
E 137
I 137
	p = &Argv[0][i];
E 137
E 136
E 108
	while (p < LastArgv)
D 257
		*p++ = ' ';
E 257
I 257
D 315
		*p++ = PROCTITLEPAD;
E 315
I 315
		*p++ = SPT_PADCHAR;
E 315
I 312
	Argv[1] = NULL;
E 312
E 257
I 200
D 315
#   endif
E 200
I 183
#  endif
E 183
D 141
# endif SETPROCTITLE
E 141
I 141
# endif /* SETPROCTITLE */
E 315
I 315
D 389
#   endif /* SPT_TYPE == SPT_PSSTRINGS */
#  endif /* SPT_TYPE == SPT_PSTAT */
E 389
I 389
#  endif
E 389
# endif /* SPT_TYPE != SPT_NONE */
E 315
E 141
}
I 283

D 315
#endif
E 315
I 315
#endif /* SPT_TYPE != SPT_BUILTIN */
E 315
E 283
I 111
/*
**  REAPCHILD -- pick up the body of my child, lest it become a zombie
**
**	Parameters:
D 343
**		none.
E 343
I 343
**		sig -- the signal that got us here (unused).
E 343
**
**	Returns:
**		none.
**
**	Side Effects:
**		Picks up extant zombies.
*/

D 132
# ifdef VMUNIX
E 132
D 245
# include <sys/wait.h>
D 132
# endif VMUNIX
E 132

E 245
I 125
void
E 125
D 343
reapchild()
E 343
I 343
reapchild(sig)
	int sig;
E 343
{
I 252
	int olderrno = errno;
E 252
I 207
D 212
# ifdef WIFEXITED
E 212
I 212
D 217
# if defined(WIFEXITED) && !defined(__NeXT__)
E 217
I 217
# ifdef HASWAITPID
E 217
E 212
	auto int status;
I 208
	int count;
	int pid;
E 208

D 208
	while (waitpid(-1, &status, WNOHANG) > 0)
		continue;
E 208
I 208
	count = 0;
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		if (count++ > 1000)
		{
I 296
#ifdef LOG
E 296
			syslog(LOG_ALERT, "reapchild: waitpid loop: pid=%d, status=%x",
				pid, status);
I 296
#endif
E 296
			break;
		}
I 406
		CurChildren--;
E 406
	}
E 208
# else
E 207
# ifdef WNOHANG
	union wait status;

D 125
	while (wait3(&status, WNOHANG, (struct rusage *) NULL) > 0)
E 125
I 125
D 212
	while (wait3((int *)&status, WNOHANG, (struct rusage *) NULL) > 0)
E 212
I 212
	while (wait3(&status, WNOHANG, (struct rusage *) NULL) > 0)
E 212
E 125
D 406
		continue;
E 406
I 406
		CurChildren--;
E 406
D 141
# else WNOHANG
E 141
I 141
# else /* WNOHANG */
E 141
	auto int status;

D 125
	while (wait(&status) > 0)
E 125
I 125
D 207
	while (wait((int *)&status) > 0)
E 207
I 207
	while (wait(&status) > 0)
E 207
E 125
D 406
		continue;
E 406
I 406
		CurChildren--;
E 406
D 141
# endif WNOHANG
E 141
I 141
# endif /* WNOHANG */
I 207
# endif
E 207
I 163
D 222
# ifdef SYSTEM5
	(void) signal(SIGCHLD, reapchild);
E 222
I 222
# ifdef SYS5SIGNALS
	(void) setsignal(SIGCHLD, reapchild);
E 222
# endif
I 252
	errno = olderrno;
E 252
E 163
E 141
}
I 139
/*
I 389
**  PUTENV -- emulation of putenv() in terms of setenv()
**
**	Not needed on Posix-compliant systems.
**	This doesn't have full Posix semantics, but it's good enough
**		for sendmail.
**
**	Parameter:
**		env -- the environment to put.
**
**	Returns:
**		none.
*/

#ifdef NEEDPUTENV

D 392
void
E 392
I 392
# if NEEDPUTENV == 2		/* no setenv(3) call available */

int
putenv(str)
	char *str;
{
	char **current;
	int matchlen, envlen=0;
	char *tmp;
	char **newenv;
	static int first=1;
	extern char **environ;

	/*
	 * find out how much of str to match when searching
	 * for a string to replace.
	 */
	if ((tmp = index(str, '=')) == NULL || tmp == str)
		matchlen = strlen(str);
	else
		matchlen = (int) (tmp - str);
	++matchlen;

	/*
	 * Search for an existing string in the environment and find the
	 * length of environ.  If found, replace and exit.
	 */
	for (current=environ; *current; current++) {
		++envlen;

		if (strncmp(str, *current, matchlen) == 0) {
			/* found it, now insert the new version */
			*current = (char *)str;
			return(0);
		}
	}

	/*
	 * There wasn't already a slot so add space for a new slot.
	 * If this is our first time through, use malloc(), else realloc().
	 */
	if (first) {
		newenv = (char **) malloc(sizeof(char *) * (envlen + 2));
		if (newenv == NULL)
			return(-1);

		first=0;
		(void) memcpy(newenv, environ, sizeof(char *) * envlen);
	} else {
		newenv = (char **) realloc((char *)environ, sizeof(char *) * (envlen + 2));
		if (newenv == NULL)
			return(-1);
	}

	/* actually add in the new entry */
	environ = newenv;
	environ[envlen] = (char *)str;
	environ[envlen+1] = NULL;

	return(0);
}

#else			/* implement putenv() in terms of setenv() */

int
E 392
putenv(env)
	char *env;
{
	char *p;
	int l;
	char nbuf[100];

	p = strchr(env, '=');
	if (p == NULL)
D 392
		return;
E 392
I 392
		return 0;
E 392
	l = p - env;
	if (l > sizeof nbuf - 1)
		l = sizeof nbuf - 1;
	bcopy(env, nbuf, l);
	nbuf[l] = '\0';
D 392
	setenv(nbuf, ++p, 1);
E 392
I 392
	return setenv(nbuf, ++p, 1);
E 392
}

I 392
# endif
E 392
#endif
/*
E 389
I 216
D 223
**  SETENV -- set environment variable
**
**	Putenv is more modern, but this is a simpler interface
**
**	Parameters:
**		name -- the name of the envariable.
**		value -- the value of that envariable.
**		overwrite -- if set, overwrite existing value
**			(this is assumed to be set).
**
**	Returns:
**		none.
**
**	Side Effects:
**		The environment is updated.
*/

#ifndef HASSETENV

setenv(name, value, overwrite)
	char *name;
	char *value;
	int overwrite;
{
	register char *p;

	p = xalloc(strlen(name) + strlen(value) + 2);
	strcpy(p, name);
	strcat(p, "=");
	strcat(p, value);
	putenv(p);
}

#endif
/*
E 223
E 216
**  UNSETENV -- remove a variable from the environment
**
**	Not needed on newer systems.
**
**	Parameters:
**		name -- the string name of the environment variable to be
**			deleted from the current environment.
**
**	Returns:
**		none.
**
**	Globals:
**		environ -- a pointer to the current environment.
**
**	Side Effects:
**		Modifies environ.
*/

D 216
#ifdef UNSETENV
E 216
I 216
#ifndef HASUNSETENV
E 216

void
unsetenv(name)
	char *name;
{
	extern char **environ;
	register char **pp;
	int len = strlen(name);

	for (pp = environ; *pp != NULL; pp++)
	{
		if (strncmp(name, *pp, len) == 0 &&
		    ((*pp)[len] == '=' || (*pp)[len] == '\0'))
			break;
	}

	for (; *pp != NULL; pp++)
		*pp = pp[1];
}

D 216
#endif /* UNSETENV */
E 216
I 216
#endif
E 216
I 140
/*
**  GETDTABLESIZE -- return number of file descriptors
**
**	Only on non-BSD systems
**
**	Parameters:
**		none
**
**	Returns:
**		size of file descriptor table
**
**	Side Effects:
**		none
*/

D 213
#ifdef SYSTEM5
E 213
I 213
#ifdef SOLARIS
# include <sys/resource.h>
#endif
E 213

int
D 213
getdtablesize()
E 213
I 213
getdtsize()
E 213
{
I 213
#ifdef RLIMIT_NOFILE
	struct rlimit rl;

	if (getrlimit(RLIMIT_NOFILE, &rl) >= 0)
		return rl.rlim_cur;
#endif

E 213
I 183
D 221
# ifdef _SC_OPEN_MAX
	return sysconf(_SC_OPEN_MAX);
# else
I 213
#  ifdef HASGETDTABLESIZE
E 221
I 221
# ifdef HASGETDTABLESIZE
E 221
	return getdtablesize();
I 221
# else
#  ifdef _SC_OPEN_MAX
	return sysconf(_SC_OPEN_MAX);
E 221
#  else
E 213
E 183
	return NOFILE;
I 213
#  endif
E 213
I 183
# endif
E 183
}
D 213

#endif
E 213
I 156
/*
**  UNAME -- get the UUCP name of this system.
*/

D 160
#ifndef UNAME
E 160
I 160
#ifndef HASUNAME
E 160

int
uname(name)
	struct utsname *name;
{
	FILE *file;
	char *n;

	name->nodename[0] = '\0';

I 158
	/* try /etc/whoami -- one line with the node name */
E 158
	if ((file = fopen("/etc/whoami", "r")) != NULL)
	{
D 158
		(void) fgets(name->nodename, NODE_LENGTH+1, file);
E 158
I 158
		(void) fgets(name->nodename, NODE_LENGTH + 1, file);
E 158
		(void) fclose(file);
D 158
		n = index(name->nodename, '\n');
E 158
I 158
		n = strchr(name->nodename, '\n');
E 158
		if (n != NULL)
			*n = '\0';
		if (name->nodename[0] != '\0')
			return (0);
	}

I 158
	/* try /usr/include/whoami.h -- has a #define somewhere */
E 158
	if ((file = fopen("/usr/include/whoami.h", "r")) != NULL)
	{
		char buf[MAXLINE];

		while (fgets(buf, MAXLINE, file) != NULL)
			if (sscanf(buf, "#define sysname \"%*[^\"]\"",
					NODE_LENGTH, name->nodename) > 0)
				break;
		(void) fclose(file);
		if (name->nodename[0] != '\0')
			return (0);
	}

#ifdef TRUST_POPEN
	/*
	**  Popen is known to have security holes.
	*/

I 158
	/* try uuname -l to return local name */
E 158
	if ((file = popen("uuname -l", "r")) != NULL)
	{
D 158
		(void) fgets(name, NODE_LENGTH+1, file);
E 158
I 158
		(void) fgets(name, NODE_LENGTH + 1, file);
E 158
		(void) pclose(file);
D 158
		n = index(name, '\n');
E 158
I 158
		n = strchr(name, '\n');
E 158
		if (n != NULL)
			*n = '\0';
D 158
		if (name->nodename[0])
E 158
I 158
		if (name->nodename[0] != '\0')
E 158
			return (0);
	}
#endif
D 377
	
E 377
I 377

E 377
	return (-1);
}
D 160
#endif /* UNAME */
E 160
I 160
#endif /* HASUNAME */
I 164
/*
**  INITGROUPS -- initialize groups
**
**	Stub implementation for System V style systems
*/

#ifndef HASINITGROUPS
D 196
# if !defined(SYSTEM5) || defined(hpux)
E 196
I 196
D 222
# if !defined(SYSTEM5) || defined(__hpux)
E 196
#  define HASINITGROUPS
# endif
#endif
E 222

D 222
#ifndef HASINITGROUPS

E 222
initgroups(name, basegid)
	char *name;
	int basegid;
{
	return 0;
}

#endif
I 165
/*
I 194
**  SETSID -- set session id (for non-POSIX systems)
*/

#ifndef HASSETSID

D 212
setsid()
E 212
I 212
pid_t
setsid __P ((void))
E 212
{
I 226
#ifdef TIOCNOTTY
	int fd;

D 295
	fd = open("/dev/tty", 2);
E 295
I 295
	fd = open("/dev/tty", O_RDWR, 0);
E 295
	if (fd >= 0)
	{
		(void) ioctl(fd, (int) TIOCNOTTY, (char *) 0);
		(void) close(fd);
	}
#endif /* TIOCNOTTY */
E 226
D 250
# ifdef SYSTEM5
E 250
I 250
# ifdef SYS5SETPGRP
E 250
D 212
	setpgrp();
E 212
I 212
	return setpgrp();
# else
D 226
	return 0;
E 226
I 226
	return setpgid(0, getpid());
I 296
# endif
}

#endif
/*
**  FSYNC -- dummy fsync
*/

#ifdef NEEDFSYNC

fsync(fd)
	int fd;
{
# ifdef O_SYNC
	return fcntl(fd, F_SETFL, O_SYNC);
# else
	/* nothing we can do */
	return 0;
E 296
E 226
E 212
# endif
}

#endif
/*
I 251
**  DGUX_INET_ADDR -- inet_addr for DG/UX
**
**	Data General DG/UX version of inet_addr returns a struct in_addr
D 303
**	instead of a long.  This patches things.
E 303
I 303
**	instead of a long.  This patches things.  Only needed on versions
**	prior to 5.4.3.
E 303
*/

D 303
#ifdef DGUX
E 303
I 303
#ifdef DGUX_5_4_2
E 303

#undef inet_addr

long
dgux_inet_addr(host)
	char *host;
{
	struct in_addr haddr;

	haddr = inet_addr(host);
	return haddr.s_addr;
}

#endif
/*
E 251
I 218
**  GETOPT -- for old systems or systems with bogus implementations
*/

#ifdef NEEDGETOPT

/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */


/*
** this version hacked to add `atend' flag to allow state machine
** to reset if invoked by the program to scan args for a 2nd time
*/

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)getopt.c	4.3 (Berkeley) 3/9/86";
D 223
#endif LIBC_SCCS and not lint
E 223
I 223
#endif /* LIBC_SCCS and not lint */
E 223

#include <stdio.h>

/*
 * get option letter from argument vector
 */
D 271
int	opterr = 1,		/* if error message should be printed */
	optind = 1,		/* index into parent argv vector */
	optopt;			/* character checked for validity */
E 271
I 271
#ifdef _CONVEX_SOURCE
D 354
extern int	optind, opterr;
E 354
I 354
extern int	optind, opterr, optopt;
extern char	*optarg;
E 354
#else
int	opterr = 1;		/* if error message should be printed */
int	optind = 1;		/* index into parent argv vector */
D 354
#endif
E 354
D 349
int	optopt;			/* character checked for validity */
E 271
char	*optarg;		/* argument associated with option */
E 349
I 349
int	optopt = 0;		/* character checked for validity */
char	*optarg = NULL;		/* argument associated with option */
I 354
#endif
E 354
E 349

#define BADCH	(int)'?'
#define EMSG	""
#define tell(s)	if (opterr) {fputs(*nargv,stderr);fputs(s,stderr); \
		fputc(optopt,stderr);fputc('\n',stderr);return(BADCH);}

getopt(nargc,nargv,ostr)
D 264
int	nargc;
char	**nargv,
	*ostr;
E 264
I 264
	int		nargc;
	char *const	*nargv;
	const char	*ostr;
E 264
{
	static char	*place = EMSG;	/* option letter processing */
	static char	atend = 0;
	register char	*oli;		/* option letter list index */
D 224
	char	*index();
E 224

	if (atend) {
		atend = 0;
		place = EMSG;
	}
	if(!*place) {			/* update scanning pointer */
D 225
		if(optind >= nargc || *(place = nargv[optind]) != '-' || !*++place) {
E 225
I 225
		if (optind >= nargc || *(place = nargv[optind]) != '-' || !*++place) {
E 225
			atend++;
			return(EOF);
		}
		if (*place == '-') {	/* found "--" */
			++optind;
			atend++;
			return(EOF);
		}
	}				/* option letter okay? */
D 224
	if ((optopt = (int)*place++) == (int)':' || !(oli = index(ostr,optopt))) {
E 224
I 224
	if ((optopt = (int)*place++) == (int)':' || !(oli = strchr(ostr,optopt))) {
E 224
D 225
		if(!*place) ++optind;
E 225
I 225
		if (!*place) ++optind;
E 225
		tell(": illegal option -- ");
	}
	if (*++oli != ':') {		/* don't need argument */
		optarg = NULL;
		if (!*place) ++optind;
	}
	else {				/* need an argument */
		if (*place) optarg = place;	/* no white space */
		else if (nargc <= ++optind) {	/* no arg */
			place = EMSG;
			tell(": option requires an argument -- ");
		}
	 	else optarg = nargv[optind];	/* white space */
		place = EMSG;
		++optind;
	}
	return(optopt);			/* dump back option letter */
}

#endif
/*
**  VFPRINTF, VSPRINTF -- for old 4.3 BSD systems missing a real version
*/

#ifdef NEEDVPRINTF

#define MAXARG	16

vfprintf(fp, fmt, ap)
	FILE *	fp;
	char *	fmt;
	char **	ap;
{
	char *	bp[MAXARG];
	int	i = 0;

	while (*ap && i < MAXARG)
		bp[i++] = *ap++;
	fprintf(fp, fmt, bp[0], bp[1], bp[2], bp[3],
			 bp[4], bp[5], bp[6], bp[7],
			 bp[8], bp[9], bp[10], bp[11],
			 bp[12], bp[13], bp[14], bp[15]);
}

vsprintf(s, fmt, ap)
	char *	s;
	char *	fmt;
	char **	ap;
{
	char *	bp[MAXARG];
	int	i = 0;

	while (*ap && i < MAXARG)
		bp[i++] = *ap++;
	sprintf(s, fmt, bp[0], bp[1], bp[2], bp[3],
			bp[4], bp[5], bp[6], bp[7],
			bp[8], bp[9], bp[10], bp[11],
			bp[12], bp[13], bp[14], bp[15]);
}

#endif
/*
I 266
D 268
**  {GET,SET,END}USERSHELL -- getusershell(3) implementation
E 268
I 268
D 270
**  usershellok -- tell if a user's shell is ok for unrestricted use
E 270
I 270
**  USERSHELLOK -- tell if a user's shell is ok for unrestricted use
E 270
E 268
**
D 268
**	Grabbed from 4.4BSD source tree.
E 268
I 268
**	Parameters:
I 413
**		user -- the name of the user we are checking.
E 413
**		shell -- the user's shell from /etc/passwd
**
**	Returns:
**		TRUE -- if it is ok to use this for unrestricted access.
**		FALSE -- if the shell is restricted.
E 268
*/

D 267
#ifdef NEEDGETUSERSHELL
E 267
I 267
D 268
#if NEEDGETUSERSHELL
E 267

/*
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)getusershell.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */

/*
 * Local shells should NOT be added here.  They should be added in
 * /etc/shells.
 */

E 268
I 268
D 274
#ifndef _PATH_SHELLS
# define _PATH_SHELLS	"/etc/shells"
E 274
I 274
#if !HASGETUSERSHELL

# ifndef _PATH_SHELLS
#  define _PATH_SHELLS	"/etc/shells"
# endif

I 396
# ifdef _AIX3
#  include <userconf.h>
#  include <usersec.h>
# endif

E 396
char	*DefaultUserShells[] =
{
D 338
	"/bin/sh",
E 338
I 338
	"/bin/sh",		/* standard shell */
E 338
	"/usr/bin/sh",
D 338
	"/bin/csh",
E 338
I 338
	"/bin/csh",		/* C shell */
E 338
	"/usr/bin/csh",
#ifdef __hpux
I 372
# ifdef V4FS
	"/usr/bin/rsh",		/* restricted Bourne shell */
	"/usr/bin/ksh",		/* Korn shell */
	"/usr/bin/rksh",	/* restricted Korn shell */
	"/usr/bin/pam",
	"/usr/bin/keysh",	/* key shell (extended Korn shell) */
	"/usr/bin/posix/sh",
# else
E 372
D 338
	"/bin/rsh",
	"/bin/ksh",
	"/bin/rksh",
E 338
I 338
	"/bin/rsh",		/* restricted Bourne shell */
	"/bin/ksh",		/* Korn shell */
	"/bin/rksh",		/* restricted Korn shell */
E 338
	"/bin/pam",
D 338
	"/usr/bin/keysh",
E 338
I 338
	"/usr/bin/keysh",	/* key shell (extended Korn shell) */
E 338
	"/bin/posix/sh",
I 372
# endif
E 372
I 338
#endif
#ifdef _AIX3
	"/bin/ksh",		/* Korn shell */
	"/usr/bin/ksh",
	"/bin/tsh",		/* trusted shell */
	"/usr/bin/tsh",
	"/bin/bsh",		/* Bourne shell */
	"/usr/bin/bsh",
E 338
E 274
#endif
E 268
D 274
#ifndef _PATH_BSHELL
# define _PATH_BSHELL	"/bin/sh"
E 274
I 274
	NULL
};

E 274
#endif
D 274
#ifndef _PATH_CSHELL
# define _PATH_CSHELL	"/bin/csh"
#endif
E 274
D 268
#ifndef _PATH_SHELLS
# define _PATH_SHELLS	"/etc/shells"
#endif
E 268

I 275
#define WILDCARD_SHELL	"/SENDMAIL/ANY/SHELL/"

E 275
D 268
static char *okshells[] = { _PATH_BSHELL, _PATH_CSHELL, NULL };
static char **curshell, **shells, *strings;
static char **initshells __P((void));

/*
 * Get a list of shells from _PATH_SHELLS, if it exists.
 */
char *
getusershell()
E 268
I 268
bool
D 413
usershellok(shell)
E 413
I 413
usershellok(user, shell)
	char *user;
E 413
	char *shell;
E 268
{
D 268
	char *ret;
E 268
I 268
#if HASGETUSERSHELL
	register char *p;
	extern char *getusershell();
E 268

I 347
D 381
	if (shell == NULL || shell[0] == '\0')
E 381
I 381
D 413
	if (shell == NULL || shell[0] == '\0' || ConfigLevel <= 1)
E 413
I 413
	if (shell == NULL || shell[0] == '\0' || wordinclass(user, 't') ||
	    ConfigLevel <= 1)
E 413
E 381
		return TRUE;

E 347
D 268
	if (curshell == NULL)
		curshell = initshells();
	ret = *curshell;
	if (ret != NULL)
		curshell++;
	return (ret);
}
E 268
I 268
	setusershell();
	while ((p = getusershell()) != NULL)
D 272
		if (strcmp(p, shell) == 0)
E 272
I 272
D 275
		if (strcmp(p, shell) == 0 || strcmp(p, "*") == 0)
E 275
I 275
		if (strcmp(p, shell) == 0 || strcmp(p, WILDCARD_SHELL) == 0)
E 275
E 272
			break;
	endusershell();
	return p != NULL;
#else
I 396
D 397
# ifdef _AIX3
E 397
I 397
# if USEGETCONFATTR
E 397
	auto char *v;
# endif
E 396
	register FILE *shellf;
	char buf[MAXLINE];
I 347

D 413
	if (shell == NULL || shell[0] == '\0')
E 413
I 413
	if (shell == NULL || shell[0] == '\0' || wordinclass(user, 't'))
E 413
		return TRUE;
I 396

D 397
# ifdef _AIX3
	/* naturally IBM has a "better" idea..... */
	if (getconfattr(SC_SYS_LOGIN, SC_SHELLS, &v, SEC_LIST) == 0)
E 397
I 397
# if USEGETCONFATTR
	/*
	**  Naturally IBM has a "better" idea.....
	**
	**	What a crock.  This interface isn't documented, it is
	**	considered part of the security library (-ls), and it
	**	only works if you are running as root (since the list
	**	of valid shells is obviously a source of great concern).
	**	I recommend that you do NOT define USEGETCONFATTR,
	**	especially since you are going to have to set up an
	**	/etc/shells anyhow to handle the cases where getconfattr
	**	fails.
	*/

	if (getconfattr(SC_SYS_LOGIN, SC_SHELLS, &v, SEC_LIST) == 0 && v != NULL)
E 397
	{
D 397
		while (v != NULL && *v != '\0')
E 397
I 397
		while (*v != '\0')
E 397
		{
			if (strcmp(v, shell) == 0 || strcmp(v, WILDCARD_SHELL) == 0)
				return TRUE;
			v += strlen(v) + 1;
		}
I 397
		return FALSE;
E 397
	}
# endif
E 396
E 347
E 268

D 268
void
endusershell()
{
	if (shells != NULL)
		free(shells);
	shells = NULL;
	if (strings != NULL)
		free(strings);
	strings = NULL;
	curshell = NULL;
}
E 268
I 268
	shellf = fopen(_PATH_SHELLS, "r");
	if (shellf == NULL)
	{
		/* no /etc/shells; see if it is one of the std shells */
D 274
		return (strcmp(shell, _PATH_CSHELL) == 0 ||
			strcmp(shell, _PATH_BSHELL) == 0);
E 274
I 274
		char **d;

		for (d = DefaultUserShells; *d != NULL; d++)
		{
			if (strcmp(shell, *d) == 0)
				return TRUE;
		}
		return FALSE;
E 274
	}
E 268

D 268
void
setusershell()
{
	curshell = initshells();
}
E 268
I 268
	while (fgets(buf, sizeof buf, shellf) != NULL)
	{
		register char *p, *q;
E 268

D 268
static char **
initshells()
{
	register char **sp, *cp;
	register FILE *fp;
	struct stat statb;

	if (shells != NULL)
		free(shells);
	shells = NULL;
	if (strings != NULL)
		free(strings);
	strings = NULL;
	if ((fp = fopen(_PATH_SHELLS, "r")) == NULL)
		return (okshells);
	if (fstat(fileno(fp), &statb) == -1) {
		(void)fclose(fp);
		return (okshells);
	}
	if ((strings = malloc((u_int)statb.st_size)) == NULL) {
		(void)fclose(fp);
		return (okshells);
	}
	shells = calloc((unsigned)statb.st_size / 3, sizeof (char *));
	if (shells == NULL) {
		(void)fclose(fp);
		free(strings);
		strings = NULL;
		return (okshells);
	}
	sp = shells;
	cp = strings;
	while (fgets(cp, MAXPATHLEN + 1, fp) != NULL) {
		while (*cp != '#' && *cp != '/' && *cp != '\0')
			cp++;
		if (*cp == '#' || *cp == '\0')
E 268
I 268
		p = buf;
		while (*p != '\0' && *p != '#' && *p != '/')
			p++;
		if (*p == '#' || *p == '\0')
E 268
			continue;
D 268
		*sp++ = cp;
		while (!isspace(*cp) && *cp != '#' && *cp != '\0')
			cp++;
		*cp++ = '\0';
E 268
I 268
		q = p;
		while (*p != '\0' && *p != '#' && !isspace(*p))
			p++;
		*p = '\0';
D 272
		if (strcmp(shell, q) == 0)
E 272
I 272
D 275
		if (strcmp(shell, q) == 0 || strcmp("*", q) == 0)
E 275
I 275
		if (strcmp(shell, q) == 0 || strcmp(WILDCARD_SHELL, q) == 0)
E 275
E 272
		{
			fclose(shellf);
			return TRUE;
		}
E 268
	}
D 268
	*sp = NULL;
	(void)fclose(fp);
	return (shells);
}
E 268
I 268
	fclose(shellf);
	return FALSE;
E 268
#endif
I 268
}
E 268
/*
E 266
E 218
E 194
D 232
**  ENOUGHSPACE -- check to see if there is enough free space on the queue fs
E 232
I 232
D 402
**  FREESPACE -- see how much free space is on the queue filesystem
E 402
I 402
**  FREEDISKSPACE -- see how much free space is on the queue filesystem
E 402
E 232
**
**	Only implemented if you have statfs.
**
**	Parameters:
D 178
**		none.
E 178
I 178
D 232
**		msize -- the size to check against.  If zero, we don't yet
**			know how big the message will be, so just check for
**			a "reasonable" amount.
E 232
I 232
**		dir -- the directory in question.
**		bsize -- a variable into which the filesystem
**			block size is stored.
E 232
E 178
**
**	Returns:
D 232
**		TRUE if there is enough space.
**		FALSE otherwise.
E 232
I 232
**		The number of bytes free on the queue filesystem.
**		-1 if the statfs call fails.
**
**	Side effects:
**		Puts the filesystem block size into bsize.
E 232
*/

D 233
#ifndef HASSTATFS
# if defined(BSD4_4) || defined(__osf__)
#  define HASSTATFS
# endif
#endif

E 233
D 276
#ifdef HASSTATFS
I 174
# undef HASUSTAT
E 276
I 276
/* statfs types */
#define SFS_NONE	0	/* no statfs implementation */
#define SFS_USTAT	1	/* use ustat */
#define SFS_4ARGS	2	/* use four-argument statfs call */
#define SFS_VFS		3	/* use <sys/vfs.h> implementation */
#define SFS_MOUNT	4	/* use <sys/mount.h> implementation */
#define SFS_STATFS	5	/* use <sys/statfs.h> implementation */
I 297
#define SFS_STATVFS	6	/* use <sys/statvfs.h> implementation */
E 297

#ifndef SFS_TYPE
# define SFS_TYPE	SFS_NONE
E 276
#endif

D 276
#if defined(HASUSTAT)
E 276
I 276
#if SFS_TYPE == SFS_USTAT
E 276
D 177
# include <sys/types.h>
E 177
D 196
# include <sys/stat.h>
E 196
# include <ustat.h>
#endif
D 276

#ifdef HASSTATFS
E 174
D 171
#include <sys/mount.h>
E 171
I 171
D 220
# if defined(sgi) || defined(apollo)
E 220
I 220
D 233
# if defined(sgi) || defined(apollo) || defined(_SCO_unix_)
E 233
I 233
D 250
# if defined(IRIX) || defined(apollo) || defined(_SCO_unix_)
E 250
I 250
D 251
# if defined(IRIX) || defined(apollo) || defined(_SCO_unix_) || defined(UMAXV)
E 251
I 251
D 258
# if defined(IRIX) || defined(apollo) || defined(_SCO_unix_) || defined(UMAXV) || defined(DGUX)
E 258
I 258
# if defined(IRIX) || defined(apollo) || defined(_SCO_unix_) || defined(UMAXV) || defined(DGUX) || defined(_AIX3)
E 258
E 251
E 250
E 233
E 220
#  include <sys/statfs.h>
# else
D 196
#  if defined(sun) || defined(hpux)
E 196
I 196
D 205
#  if defined(sun) || defined(__hpux)
E 205
I 205
D 216
#  if (defined(sun) && !defined(BSD)) || defined(__hpux)
E 216
I 216
D 233
#  if (defined(sun) && !defined(BSD)) || defined(__hpux) || defined(_CONVEX_SOURCE)
E 233
I 233
D 242
#  if (defined(sun) && !defined(BSD)) || defined(__hpux) || defined(_CONVEX_SOURCE) || defined(NeXT)
E 242
I 242
D 253
#  if (defined(sun) && !defined(BSD)) || defined(__hpux) || defined(_CONVEX_SOURCE) || defined(NeXT) || defined(_AUX_SOURCE)
E 253
I 253
#  if (defined(sun) && !defined(BSD)) || defined(__hpux) || defined(_CONVEX_SOURCE) || defined(NeXT) || defined(_AUX_SOURCE) || defined(MACH386)
E 253
E 242
E 233
E 216
E 205
E 196
#   include <sys/vfs.h>
#  else
D 173
#   include <sys/mount.h>
E 173
I 173
D 174
#   if defined(HASUSTAT)
#    include <sys/types.h>
#    include <sys/stat.h>
#    include ustat.h>
#   else
#    include <sys/mount.h>
#   endif
E 174
I 174
#   include <sys/mount.h>
E 174
E 173
#  endif
# endif
E 276
I 276
#if SFS_TYPE == SFS_4ARGS || SFS_TYPE == SFS_STATFS
# include <sys/statfs.h>
E 276
E 171
#endif
I 276
#if SFS_TYPE == SFS_VFS
# include <sys/vfs.h>
#endif
#if SFS_TYPE == SFS_MOUNT
# include <sys/mount.h>
#endif
I 297
#if SFS_TYPE == SFS_STATVFS
# include <sys/statvfs.h>
#endif
E 297
E 276

D 232
bool
D 178
enoughspace()
E 178
I 178
enoughspace(msize)
	long msize;
E 232
I 232
long
D 402
freespace(dir, bsize)
E 402
I 402
freediskspace(dir, bsize)
E 402
	char *dir;
	long *bsize;
E 232
E 178
{
D 174
#ifdef HASSTATFS
I 171
# if defined(ultrix)
	struct fs_data fs;
#  define f_bavail	fd_bfreen
# else
I 173
#  if defined(HASUSTAT)
E 174
I 174
D 175
#ifdef defined(HASSTATFS) || defined(HASUSTAT)
E 175
I 175
D 276
#if defined(HASSTATFS) || defined(HASUSTAT)
E 175
# if defined(HASUSTAT)
E 276
I 276
#if SFS_TYPE != SFS_NONE
# if SFS_TYPE == SFS_USTAT
E 276
E 174
	struct ustat fs;
	struct stat statbuf;
I 179
#  define FSBLOCKSIZE	DEV_BSIZE
E 179
D 174
#   define f_bavail	f_tfree
E 174
I 174
D 345
#  define f_bavail	f_tfree
E 345
I 345
D 359
#  define FSF_BAVAIL	f_tfree
E 359
I 359
#  define SFS_BAVAIL	f_tfree
E 359
E 345
# else
#  if defined(ultrix)
	struct fs_data fs;
D 345
#   define f_bavail	fd_bfreen
E 345
I 345
D 359
#   define FSF_BAVAIL	fd_bfreen
E 359
I 359
#   define SFS_BAVAIL	fd_bfreen
E 359
E 345
I 179
D 308
#   define FSBLOCKSIZE	fs.fd_bsize
E 308
I 308
#   define FSBLOCKSIZE	1024L
E 308
E 179
E 174
#  else
I 297
#   if SFS_TYPE == SFS_STATVFS
	struct statvfs fs;
I 301
D 337
#    define FSBLOCKSIZE	fs.f_bsize
E 337
I 337
#    define FSBLOCKSIZE	fs.f_frsize
E 337
E 301
#   else
E 297
E 173
E 171
	struct statfs fs;
I 179
D 297
#   define FSBLOCKSIZE	fs.f_bsize
I 220
D 223
#   if defined(_SCO_UNIX_)
E 223
I 223
D 232
#   if defined(_SCO_unix_)
E 232
I 232
D 234
#   if defined(_SCO_UNIX_)
E 234
I 234
D 237
#   if defined(_SCO_unix_)
E 237
I 237
D 277
#   if defined(_SCO_unix_) || defined(IRIX)
E 277
I 277
#   if defined(_SCO_unix_) || defined(IRIX) || defined(apollo)
E 277
E 237
E 234
E 232
E 223
#    define f_bavail f_bfree
E 297
I 297
#    define FSBLOCKSIZE	fs.f_bsize
D 335
#    if defined(_SCO_unix_) || defined(IRIX) || defined(apollo)
E 335
I 335
D 336
#    if defined(_SCO_unix_) || defined(IRIX) || defined(apollo) || defined(ALTOS_SYS_V)
E 336
I 336
D 343
#    if defined(_SCO_unix_) || defined(IRIX) || defined(apollo) || defined(ALTOS_SYS_V) || defined(_UTS)
E 343
I 343
D 345
#    if defined(_SCO_unix_) || defined(IRIX) || defined(apollo) || defined(ALTOS_SYS_V) || defined(_UTS) || defined(_CRAYCOM)
E 343
E 336
E 335
#     define f_bavail f_bfree
#    endif
E 345
E 297
#   endif
E 220
E 179
I 173
#  endif
E 173
I 171
# endif
I 345
D 359
# ifndef FSF_BAVAIL
#  define FSF_BAVAIL f_bavail
E 359
I 359
# ifndef SFS_BAVAIL
#  define SFS_BAVAIL f_bavail
E 359
# endif
E 345
I 178
D 210
	long blocksneeded;
E 210
E 178
E 171
D 344
	extern int errno;
E 344
D 204
	extern char *errstring();
E 204

D 171
	if (MinBlocksFree > 0 && statfs(QueueDir, &fs) >= 0)
E 171
I 171
D 178
	if (MinBlocksFree <= 0)
E 178
I 178
D 232
	if (MinBlocksFree <= 0 && msize <= 0)
E 178
	{
		if (tTd(4, 80))
			printf("enoughspace: no threshold\n");
		return TRUE;
	}
I 178

I 228
	if (msize < 0)
		msize = 0;

E 232
E 228
E 178
D 174
# if defined(sgi) || defined(apollo)
	if (statfs(QueueDir, &fs, sizeof fs, 0) == 0)
E 174
I 174
D 276
# if defined(HASUSTAT)
E 276
I 276
# if SFS_TYPE == SFS_USTAT
E 276
D 232
	if (stat(QueueDir, &statbuf) == 0 && ustat(statbuf.st_dev, &fs) == 0)
E 232
I 232
	if (stat(dir, &statbuf) == 0 && ustat(statbuf.st_dev, &fs) == 0)
E 232
E 174
# else
D 174
#  if defined(ultrix)
	if (statfs(QueueDir, &fs) > 0)
E 174
I 174
D 233
#  if defined(sgi) || defined(apollo)
E 233
I 233
D 250
#  if defined(IRIX) || defined(apollo)
E 250
I 250
D 251
#  if defined(IRIX) || defined(apollo) || defined(UMAXV)
E 251
I 251
D 276
#  if defined(IRIX) || defined(apollo) || defined(UMAXV) || defined(DGUX)
E 276
I 276
#  if SFS_TYPE == SFS_4ARGS
E 276
E 251
E 250
E 233
D 232
	if (statfs(QueueDir, &fs, sizeof fs, 0) == 0)
E 232
I 232
	if (statfs(dir, &fs, sizeof fs, 0) == 0)
E 232
E 174
#  else
I 173
D 174
#   if defined(HASUSTAT)
	if (stat(QueueDir, &statbuf) == 0 && ustat(statbuf.st_dev, &fs) == 0)
E 174
I 174
D 302
#   if defined(ultrix)
D 232
	if (statfs(QueueDir, &fs) > 0)
E 232
I 232
	if (statfs(dir, &fs) > 0)
E 302
I 302
#   if SFS_TYPE == SFS_STATVFS
	if (statvfs(dir, &fs) == 0)
E 302
E 232
E 174
#   else
I 302
#    if defined(ultrix)
	if (statfs(dir, &fs) > 0)
#    else
E 302
E 173
D 232
	if (statfs(QueueDir, &fs) == 0)
E 232
I 232
	if (statfs(dir, &fs) == 0)
I 302
#    endif
E 302
E 232
I 173
#   endif
E 173
#  endif
# endif
E 171
	{
I 232
		if (bsize != NULL)
			*bsize = FSBLOCKSIZE;
D 345
		return (fs.f_bavail);
E 345
I 345
D 359
		return (fs.FSF_BAVAIL);
E 359
I 359
		return (fs.SFS_BAVAIL);
E 359
E 345
	}
I 238
#endif
E 238
	return (-1);
}
/*
D 402
**  ENOUGHSPACE -- check to see if there is enough free space on the queue fs
E 402
I 402
**  ENOUGHDISKSPACE -- is there enough free space on the queue fs?
E 402
**
**	Only implemented if you have statfs.
**
**	Parameters:
**		msize -- the size to check against.  If zero, we don't yet
**		know how big the message will be, so just check for
**		a "reasonable" amount.
**
**	Returns:
**		TRUE if there is enough space.
**		FALSE otherwise.
*/

bool
D 402
enoughspace(msize)
E 402
I 402
enoughdiskspace(msize)
E 402
	long msize;
{
	long bfree, bsize;

	if (MinBlocksFree <= 0 && msize <= 0)
	{
E 232
		if (tTd(4, 80))
I 232
D 402
			printf("enoughspace: no threshold\n");
E 402
I 402
			printf("enoughdiskspace: no threshold\n");
E 402
		return TRUE;
	}

D 402
	if ((bfree = freespace(QueueDir, &bsize)) >= 0)
E 402
I 402
	if ((bfree = freediskspace(QueueDir, &bsize)) >= 0)
E 402
	{
		if (tTd(4, 80))
E 232
D 169
			printf("enoughspace: bfree=%ld, min=%ld\n",
				fs.f_bfree, MinBlocksFree);
		if (fs.f_bfree < MinBlocksFree)
E 169
I 169
D 178
			printf("enoughspace: bavail=%ld, min=%ld\n",
				fs.f_bavail, MinBlocksFree);
		if (fs.f_bavail < MinBlocksFree)
E 178
I 178
D 402
			printf("enoughspace: bavail=%ld, need=%ld\n",
E 402
I 402
			printf("enoughdiskspace: bavail=%ld, need=%ld\n",
E 402
D 232
				fs.f_bavail, msize);
E 232
I 232
				bfree, msize);
E 232

		/* convert msize to block count */
D 179
		msize = msize / fs.f_bsize + 1;
E 179
I 179
D 232
		msize = msize / FSBLOCKSIZE + 1;
E 232
I 232
		msize = msize / bsize + 1;
E 232
E 179
		if (MinBlocksFree >= 0)
			msize += MinBlocksFree;

D 232
		if (fs.f_bavail < msize)
E 232
I 232
		if (bfree < msize)
E 232
E 178
E 169
I 166
		{
#ifdef LOG
			if (LogLevel > 0)
D 228
				syslog(LOG_ALERT, "%s: low on space (have %ld, need %ld)",
D 169
					QueueDir, fs.f_bfree, MinBlocksFree);
E 169
I 169
D 178
					QueueDir, fs.f_bavail, MinBlocksFree);
E 178
I 178
					QueueDir, fs.f_bavail, msize);
E 228
I 228
				syslog(LOG_ALERT,
					"%s: low on space (have %ld, %s needs %ld in %s)",
D 232
					CurEnv->e_id, fs.f_bavail,
E 232
I 232
D 341
					CurEnv->e_id, bfree,
E 232
					CurHostName, msize, QueueDir);
E 341
I 341
					CurEnv->e_id == NULL ? "[NOQUEUE]" : CurEnv->e_id,
					bfree,
					CurHostName == NULL ? "SMTP-DAEMON" : CurHostName,
					msize, QueueDir);
E 341
E 228
E 178
E 169
#endif
E 166
			return FALSE;
I 166
		}
E 166
	}
	else if (tTd(4, 80))
D 178
		printf("enoughspace: min=%ld: %s\n",
			MinBlocksFree, errstring(errno));
E 178
I 178
D 402
		printf("enoughspace failure: min=%ld, need=%ld: %s\n",
E 402
I 402
		printf("enoughdiskspace failure: min=%ld, need=%ld: %s\n",
E 402
			MinBlocksFree, msize, errstring(errno));
E 178
D 238
#endif
E 238
	return TRUE;
}
I 180
/*
**  TRANSIENTERROR -- tell if an error code indicates a transient failure
**
**	This looks at an errno value and tells if this is likely to
**	go away if retried later.
**
**	Parameters:
**		err -- the errno code to classify.
**
**	Returns:
**		TRUE if this is probably transient.
**		FALSE otherwise.
*/

bool
transienterror(err)
	int err;
{
	switch (err)
	{
	  case EIO:			/* I/O error */
	  case ENXIO:			/* Device not configured */
	  case EAGAIN:			/* Resource temporarily unavailable */
	  case ENOMEM:			/* Cannot allocate memory */
	  case ENODEV:			/* Operation not supported by device */
	  case ENFILE:			/* Too many open files in system */
	  case EMFILE:			/* Too many open files */
	  case ENOSPC:			/* No space left on device */
#ifdef ETIMEDOUT
	  case ETIMEDOUT:		/* Connection timed out */
#endif
#ifdef ESTALE
	  case ESTALE:			/* Stale NFS file handle */
#endif
#ifdef ENETDOWN
	  case ENETDOWN:		/* Network is down */
#endif
#ifdef ENETUNREACH
	  case ENETUNREACH:		/* Network is unreachable */
#endif
#ifdef ENETRESET
	  case ENETRESET:		/* Network dropped connection on reset */
#endif
#ifdef ECONNABORTED
	  case ECONNABORTED:		/* Software caused connection abort */
#endif
#ifdef ECONNRESET
	  case ECONNRESET:		/* Connection reset by peer */
#endif
#ifdef ENOBUFS
	  case ENOBUFS:			/* No buffer space available */
#endif
#ifdef ESHUTDOWN
	  case ESHUTDOWN:		/* Can't send after socket shutdown */
#endif
#ifdef ECONNREFUSED
	  case ECONNREFUSED:		/* Connection refused */
#endif
#ifdef EHOSTDOWN
	  case EHOSTDOWN:		/* Host is down */
#endif
#ifdef EHOSTUNREACH
	  case EHOSTUNREACH:		/* No route to host */
#endif
#ifdef EDQUOT
	  case EDQUOT:			/* Disc quota exceeded */
#endif
#ifdef EPROCLIM
	  case EPROCLIM:		/* Too many processes */
#endif
#ifdef EUSERS
	  case EUSERS:			/* Too many users */
#endif
#ifdef EDEADLK
	  case EDEADLK:			/* Resource deadlock avoided */
#endif
#ifdef EISCONN
	  case EISCONN:			/* Socket already connected */
#endif
#ifdef EINPROGRESS
	  case EINPROGRESS:		/* Operation now in progress */
#endif
#ifdef EALREADY
	  case EALREADY:		/* Operation already in progress */
#endif
#ifdef EADDRINUSE
	  case EADDRINUSE:		/* Address already in use */
#endif
#ifdef EADDRNOTAVAIL
	  case EADDRNOTAVAIL:		/* Can't assign requested address */
#endif
I 285
D 286
#ifdef ETXTBSY:
E 286
I 286
#ifdef ETXTBSY
E 286
	  case ETXTBSY:			/* (Apollo) file locked */
#endif
E 285
D 214
#ifdef ENOSR
E 214
I 214
#if defined(ENOSR) && (!defined(ENOBUFS) || (ENOBUFS != ENOSR))
E 214
	  case ENOSR:			/* Out of streams resources */
#endif
		return TRUE;
	}

	/* nope, must be permanent */
I 183
	return FALSE;
}
/*
D 222
**  LOCKFILE -- lock a file using flock or (shudder) lockf
E 222
I 222
**  LOCKFILE -- lock a file using flock or (shudder) fcntl locking
E 222
**
**	Parameters:
**		fd -- the file descriptor of the file.
**		filename -- the file name (for error messages).
I 236
**		ext -- the filename extension.
E 236
**		type -- type of the lock.  Bits can be:
**			LOCK_EX -- exclusive lock.
**			LOCK_NB -- non-blocking.
**
**	Returns:
**		TRUE if the lock was acquired.
**		FALSE otherwise.
*/

bool
D 236
lockfile(fd, filename, type)
E 236
I 236
lockfile(fd, filename, ext, type)
E 236
	int fd;
	char *filename;
I 236
	char *ext;
E 236
	int type;
{
D 222
# ifdef LOCKF
E 222
I 222
D 278
# ifndef HASFLOCK
E 278
I 278
# if !HASFLOCK
E 278
E 222
	int action;
	struct flock lfd;
I 236

	if (ext == NULL)
		ext = "";
E 236
D 222

E 222
I 222
D 377
		
E 377
I 377

E 377
E 222
I 219
	bzero(&lfd, sizeof lfd);
E 219
D 184
	if (bitset(LOCK_EX, type)
E 184
I 184
D 197
	if (bitset(LOCK_EX, type))
E 197
I 197
	if (bitset(LOCK_UN, type))
		lfd.l_type = F_UNLCK;
	else if (bitset(LOCK_EX, type))
E 197
E 184
		lfd.l_type = F_WRLCK;
	else
		lfd.l_type = F_RDLCK;

	if (bitset(LOCK_NB, type))
		action = F_SETLK;
	else
		action = F_SETLKW;
D 219

	lfd.l_whence = lfd.l_start = lfd.l_len = 0;
E 219

I 229
	if (tTd(55, 60))
D 236
		printf("lockfile(%s, action=%d, type=%d): ",
			filename, action, lfd.l_type);
E 236
I 236
		printf("lockfile(%s%s, action=%d, type=%d): ",
			filename, ext, action, lfd.l_type);
E 236

E 229
	if (fcntl(fd, action, &lfd) >= 0)
I 229
	{
		if (tTd(55, 60))
			printf("SUCCESS\n");
E 229
I 225
		return TRUE;
I 229
	}
E 229

I 229
	if (tTd(55, 60))
		printf("(%s) ", errstring(errno));

E 229
	/*
	**  On SunOS, if you are testing using -oQ/tmp/mqueue or
	**  -oA/tmp/aliases or anything like that, and /tmp is mounted
	**  as type "tmp" (that is, served from swap space), the
	**  previous fcntl will fail with "Invalid argument" errors.
	**  Since this is fairly common during testing, we will assume
	**  that this indicates that the lock is successfully grabbed.
	*/

	if (errno == EINVAL)
I 229
	{
		if (tTd(55, 60))
			printf("SUCCESS\n");
E 229
E 225
		return TRUE;
I 229
	}
E 229

	if (!bitset(LOCK_NB, type) || (errno != EACCES && errno != EAGAIN))
D 197
		syserr("cannot lockf(%s)", filename);
E 197
I 197
D 236
		syserr("cannot lockf(%s, %o)", filename, type);
E 236
I 236
D 240
		syserr("cannot lockf(%s%s, %o)", filename, ext, type);
E 240
I 240
D 241
		syserr("cannot lockf(%s%s, fd=%d, type=%o)",
			filename, ext, fd, type);
E 241
I 241
	{
		int omode = -1;
#  ifdef F_GETFL
		int oerrno = errno;

		(void) fcntl(fd, F_GETFL, &omode);
		errno = oerrno;
#  endif
		syserr("cannot lockf(%s%s, fd=%d, type=%o, omode=%o, euid=%d)",
			filename, ext, fd, type, omode, geteuid());
	}
E 241
E 240
E 236
E 197
# else
I 236
	if (ext == NULL)
		ext = "";

E 236
I 229
	if (tTd(55, 60))
D 236
		printf("lockfile(%s, type=%o): ", filename, type);
E 236
I 236
		printf("lockfile(%s%s, type=%o): ", filename, ext, type);
E 236

E 229
	if (flock(fd, type) >= 0)
I 229
	{
		if (tTd(55, 60))
			printf("SUCCESS\n");
E 229
		return TRUE;
I 229
	}
E 229

I 229
	if (tTd(55, 60))
		printf("(%s) ", errstring(errno));

E 229
	if (!bitset(LOCK_NB, type) || errno != EWOULDBLOCK)
D 197
		syserr("cannot flock(%s)", filename);
E 197
I 197
D 236
		syserr("cannot flock(%s, %o)", filename, type);
E 236
I 236
D 240
		syserr("cannot flock(%s%s, %o)", filename, ext, type);
E 240
I 240
D 241
		syserr("cannot flock(%s%s, fd=%d, type=%o)",
			filename, ext, fd, type);
E 241
I 241
	{
		int omode = -1;
#  ifdef F_GETFL
		int oerrno = errno;

		(void) fcntl(fd, F_GETFL, &omode);
		errno = oerrno;
#  endif
		syserr("cannot flock(%s%s, fd=%d, type=%o, omode=%o, euid=%d)",
			filename, ext, fd, type, omode, geteuid());
E 241
E 240
E 236
E 197
D 243
# endif
E 243
I 241
	}
I 243
# endif
E 243
E 241
I 229
	if (tTd(55, 60))
		printf("FAIL\n");
E 229
E 183
	return FALSE;
I 246
}
/*
I 279
**  CHOWNSAFE -- tell if chown is "safe" (executable only by root)
**
**	Parameters:
**		fd -- the file descriptor to check.
**
**	Returns:
**		TRUE -- if only root can chown the file to an arbitrary
**			user.
**		FALSE -- if an arbitrary user can give away a file.
*/

bool
chownsafe(fd)
	int fd;
{
D 280
#ifdef __hpux__
E 280
I 280
#ifdef __hpux
E 280
	char *s;
	int tfd;
	uid_t o_uid, o_euid;
	gid_t o_gid, o_egid;
	bool rval;
	struct stat stbuf;

	o_uid = getuid();
	o_euid = geteuid();
	o_gid = getgid();
	o_egid = getegid();
D 281
	fstat(fildes, &stbuf);
E 281
I 281
	fstat(fd, &stbuf);
E 281
	setresuid(stbuf.st_uid, stbuf.st_uid, -1);
	setresgid(stbuf.st_gid, stbuf.st_gid, -1);
	s = tmpnam(NULL);
	tfd = open(s, O_RDONLY|O_CREAT, 0600);
D 282
	rval = fchown(tfd, DefUid, DefGid) == 0;
E 282
I 282
	rval = fchown(tfd, DefUid, DefGid) != 0;
E 282
	close(tfd);
	unlink(s);
D 388
	setreuid(o_uid, o_euid);
E 388
I 388
	setresuid(o_uid, o_euid, -1);
E 388
	setresgid(o_gid, o_egid, -1);
	return rval;
#else
D 288
# ifdef _PC_CHOWN_RESTRICTED
	return fpathconf(fd, _PC_CHOWN_RESTRICTED) > 0;
# else
#  ifdef BSD
E 288
I 288
# ifdef _POSIX_CHOWN_RESTRICTED
#  if _POSIX_CHOWN_RESTRICTED == -1
	return FALSE;
#  else
E 288
	return TRUE;
I 288
#  endif
# else
#  ifdef _PC_CHOWN_RESTRICTED
D 306
	return fpathconf(fd, _PC_CHOWN_RESTRICTED) > 0;
E 288
#  else
I 288
#   ifdef BSD
E 306
I 306
	int rval;

	/*
	**  Some systems (e.g., SunOS) seem to have the call and the
	**  #define _PC_CHOWN_RESTRICTED, but don't actually implement
	**  the call.  This heuristic checks for that.
	*/

	errno = 0;
	rval = fpathconf(fd, _PC_CHOWN_RESTRICTED);
	if (errno == 0)
		return rval > 0;
#  endif
#  ifdef BSD
E 306
	return TRUE;
D 306
#   else
E 306
I 306
#  else
E 306
E 288
	return FALSE;
I 288
D 306
#   endif
E 306
E 288
#  endif
# endif
#endif
}
/*
I 304
**  RESETLIMITS -- reset system controlled resource limits
**
**	This is to avoid denial-of-service attacks
**
**	Parameters:
**		none
**
**	Returns:
**		none
*/

#if HASSETRLIMIT
# include <sys/resource.h>
#endif

I 344
void
E 344
resetlimits()
{
#if HASSETRLIMIT
	struct rlimit lim;

	lim.rlim_cur = lim.rlim_max = RLIM_INFINITY;
	(void) setrlimit(RLIMIT_CPU, &lim);
	(void) setrlimit(RLIMIT_FSIZE, &lim);
#else
# if HASULIMIT
	(void) ulimit(2, 0x3fffff);
# endif
#endif
}
/*
E 304
E 279
**  GETCFNAME -- return the name of the .cf file.
**
**	Some systems (e.g., NeXT) determine this dynamically.
*/

char *
getcfname()
{
I 414
	struct stat st;
E 414
I 394
D 407
#ifdef TRY_VERSIONED_CF_NAME
E 394
I 367
	int i;
	static char cbuf[200];
I 394
#endif
E 407
E 394

E 367
	if (ConfFile != NULL)
		return ConfFile;
I 269
D 410
#ifdef NETINFO
E 410
I 410
#if NETINFO
E 410
	{
		extern char *ni_propval();
		char *cflocation;

D 320
		cflocation = ni_propval("/locations/sendmail", "sendmail.cf");
E 320
I 320
		cflocation = ni_propval("/locations", NULL, "sendmail",
					"sendmail.cf", '\0');
E 320
		if (cflocation != NULL)
			return cflocation;
	}
#endif
I 367

I 414
	if (stat("/etc/sendmail.cf", &st) >= 0)
		return "/etc/sendmail.cf";
E 414
I 373
D 407
#ifdef TRY_VERSIONED_CF_NAME
E 373
	/*
	**  Try sendmail.8.6.12.cf, then sendmail.8.6.cf, then
	**  sendmail.8.cf, and finally sendmail.cf.
	**
	**	I suppose it should really try a search path here --
	**	e.g., /etc/sendmail.cf, /etc/mail/sendmail.cf,
	**	/usr/lib/sendmail.cf, and so forth.
	*/

	strcpy(cbuf, _PATH_SENDMAILCF);
	i = strlen(cbuf);
	if (strcmp(&cbuf[i - 3], ".cf") == 0)
	{
		char *p;
		extern char Version[];

		strcpy(&cbuf[i - 2], Version);
		p = strchr(&cbuf[i - 2], '/');
		if (p != NULL)
			*p = '\0';
		p = &cbuf[strlen(cbuf)];
		do
		{
			int fd;

			strcpy(p, ".cf");
			if ((fd = open(cbuf, O_RDONLY, 0)) >= 0)
			{
				close(fd);
				return cbuf;
			}
			*p = '\0';
		} while ((p = strrchr(&cbuf[i - 2], '.')) != NULL);
	}
I 373
#endif
E 407
E 373
E 367
E 269
	return _PATH_SENDMAILCF;
I 251
}
/*
**  SETVENDOR -- process vendor code from V configuration line
**
**	Parameters:
**		vendor -- string representation of vendor.
**
**	Returns:
**		TRUE -- if ok.
**		FALSE -- if vendor code could not be processed.
I 259
**
**	Side Effects:
**		It is reasonable to set mode flags here to tweak
**		processing in other parts of the code if necessary.
**		For example, if you are a vendor that uses $%y to
**		indicate YP lookups, you could enable that here.
E 259
*/

bool
setvendor(vendor)
	char *vendor;
{
D 259
	return (strcasecmp(vendor, "Berkeley") == 0);
E 259
I 259
	if (strcasecmp(vendor, "Berkeley") == 0)
I 321
	{
		VendorCode = VENDOR_BERKELEY;
E 321
		return TRUE;
I 321
	}
E 321

	/* add vendor extensions here */
I 321

#ifdef SUN_EXTENSIONS
	if (strcasecmp(vendor, "Sun") == 0)
	{
		VendorCode = VENDOR_SUN;
		return TRUE;
	}
#endif
E 321

	return FALSE;
E 259
E 251
E 246
}
I 253
/*
I 382
**  VENDOR_PRE_DEFAULTS, VENDOR_POST_DEFAULTS -- set vendor-specific defaults
**
**	Vendor_pre_defaults is called before reading the configuration
**	file; vendor_post_defaults is called immediately after.
**
**	Parameters:
**		e -- the global environment to initialize.
**
**	Returns:
**		none.
*/

void
vendor_pre_defaults(e)
	ENVELOPE *e;
{
}


void
vendor_post_defaults(e)
	ENVELOPE *e;
{
}
/*
E 382
**  STRTOL -- convert string to long integer
**
**	For systems that don't have it in the C library.
I 289
**
**	This is taken verbatim from the 4.4-Lite C library.
E 289
*/

#ifdef NEEDSTRTOL

I 289
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)strtol.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */

#include <limits.h>

/*
 * Convert a string to a long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */

E 289
long
D 289
strtol(p, ep, b)
	char *p;
	char **ep;
	int b;
E 289
I 289
strtol(nptr, endptr, base)
	const char *nptr;
	char **endptr;
	register int base;
E 289
{
D 289
	long l = 0;
	char c;
	char maxd;
	int neg = 1;
E 289
I 289
	register const char *s = nptr;
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;
E 289

D 289
	maxd = (b > 10) ? '9' : b + '0';

	if (p && *p == '-') {
		neg = -1;
		p++;
E 289
I 289
	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
E 289
	}
D 289
	while (p && (c = *p)) {
		if (c >= '0' && c <= maxd) {
			l = l*b + *p++ - '0';
			continue;
E 289
I 289
	if (base == 0)
		base = c == '0' ? 8 : 10;

	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set any if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
E 289
		}
D 289
		if (c >= 'A' && c <= 'Z')
			c -= 'A' + 'a';
		c = c - 'a' + 10;
		if (b > c) {
			l = l*b + c;
			p++;
			continue;
		}
		break;
E 289
	}
D 289
	l *= neg;
	if (ep)
		*ep = p;
	return l;
E 289
I 289
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *)(any ? s - 1 : nptr);
	return (acc);
E 289
}

#endif
I 256
/*
I 390
**  STRSTR -- find first substring in string
**
**	Parameters:
**		big -- the big (full) string.
**		little -- the little (sub) string.
**
**	Returns:
**		A pointer to the first instance of little in big.
**		big if little is the null string.
**		NULL if little is not contained in big.
*/

#ifdef NEEDSTRSTR

char *
strstr(big, little)
	char *big;
	char *little;
{
	register char *p = big;
	int l;

	if (*little == '\0')
		return big;
	l = strlen(little);

	while ((p = strchr(p, *little)) != NULL)
	{
		if (strncmp(p, little, l) == 0)
			return p;
		p++;
	}
	return NULL;
}

#endif
/*
E 390
D 358
**  SOLARIS_GETHOSTBY{NAME,ADDR} -- compatibility routines for gethostbyXXX
E 358
I 358
**  SM_GETHOSTBY{NAME,ADDR} -- compatibility routines for gethostbyXXX
E 358
**
D 307
**	Solaris versions prior through 2.3 don't properly deliver a
E 307
I 307
D 358
**	Solaris versions at least through 2.3 don't properly deliver a
E 307
**	canonical h_name field.  This tries to work around it.
E 358
I 358
**	Some operating systems have wierd problems with the gethostbyXXX
**	routines.  For example, Solaris versions at least through 2.3
**	don't properly deliver a canonical h_name field.  This tries to
**	work around these problems.
E 358
*/

D 352
#ifdef SOLARIS
E 352
I 352
D 358
#if defined(SOLARIS) && SOLARIS < 204
E 352
I 307

extern int	h_errno;
E 307

E 358
I 353
extern int	h_errno;

E 353
struct hostent *
D 358
solaris_gethostbyname(name)
E 358
I 358
sm_gethostbyname(name)
E 358
D 263
	char *name;
E 263
I 263
D 363
	const char *name;
E 363
I 363
	char *name;
E 363
E 263
{
I 400
	struct hostent *h;
E 400
I 358
D 389
#if defined(SOLARIS) && SOLARIS < 204
E 389
I 389
#if defined(SOLARIS) && SOLARIS < 204 || defined(sony_news) && defined(__svr4)
E 389
D 418
	extern int h_errno;

E 418
E 358
D 352
# ifdef SOLARIS_2_3
E 352
I 352
# if SOLARIS == 203
E 352
	static struct hostent hp;
	static char buf[1000];
	extern struct hostent *_switch_gethostbyname_r();

D 400
	return _switch_gethostbyname_r(name, &hp, buf, sizeof(buf), &h_errno);
E 400
I 400
	if (tTd(61, 10))
		printf("_switch_gethostbyname_r(%s)... ", name);
	h = _switch_gethostbyname_r(name, &hp, buf, sizeof(buf), &h_errno);
E 400
# else
I 261
	extern struct hostent *__switch_gethostbyname();

E 261
D 400
	return __switch_gethostbyname(name);
E 400
I 400
	if (tTd(61, 10))
		printf("__switch_gethostbyname(%s)... ", name);
	h = __switch_gethostbyname(name);
E 400
# endif
I 358
#else
D 391
	return gethostbyname(name);
E 391
I 391
D 400
	struct hostent *h;
E 400
I 400
D 415
# if defined(NIS)
E 415
E 400
	int nmaps;
D 394
	int i;
E 394
	char *maptype[MAXMAPSTACK];
	short mapreturn[MAXMAPACTIONS];
	char hbuf[MAXNAME];
I 400
D 415
# endif
E 415
E 400

I 400
	if (tTd(61, 10))
		printf("gethostbyname(%s)... ", name);
E 400
	h = gethostbyname(name);
D 415
# if defined(NIS)
E 415
D 400
	if (h != NULL)
		return h;
	nmaps = switch_map_find("hosts", maptype, mapreturn);
	while (--nmaps >= 0)
		if (strcmp(maptype[nmaps], "nis") == 0)
			break;
	if (nmaps >= 0)
E 400
I 400
	if (h == NULL)
E 400
	{
D 400
		/* try short name */
		if (strlen(name) > sizeof hbuf - 1)
			return NULL;
		strcpy(hbuf, name);
		shorten_hostname(hbuf);
E 400
I 400
		if (tTd(61, 10))
			printf("failure\n");
E 400

D 400
		/* if it hasn't been shortened, there's no point */
		if (strcmp(hbuf, name) != 0)
			return gethostbyname(hbuf);
E 400
I 400
		nmaps = switch_map_find("hosts", maptype, mapreturn);
		while (--nmaps >= 0)
D 415
			if (strcmp(maptype[nmaps], "nis") == 0)
E 415
I 415
			if (strcmp(maptype[nmaps], "nis") == 0 ||
			    strcmp(maptype[nmaps], "files") == 0)
E 415
				break;
		if (nmaps >= 0)
		{
			/* try short name */
			if (strlen(name) > sizeof hbuf - 1)
				return NULL;
			strcpy(hbuf, name);
			shorten_hostname(hbuf);

			/* if it hasn't been shortened, there's no point */
			if (strcmp(hbuf, name) != 0)
			{
				if (tTd(61, 10))
					printf("gethostbyname(%s)... ", hbuf);
				h = gethostbyname(hbuf);
			}
		}
E 400
	}
D 415
# endif
E 415
D 400
	return h;
E 400
E 391
#endif
I 400
	if (tTd(61, 10))
	{
		if (h == NULL)
			printf("failure\n");
		else
			printf("%s\n", h->h_name);
	}
	return h;
E 400
E 358
}

struct hostent *
D 358
solaris_gethostbyaddr(addr, len, type)
E 358
I 358
sm_gethostbyaddr(addr, len, type)
E 358
D 263
	char *addr;
E 263
I 263
D 363
	const char *addr;
E 363
I 363
	char *addr;
E 363
E 263
	int len;
	int type;
{
I 358
#if defined(SOLARIS) && SOLARIS < 204
D 418
	extern int h_errno;

E 418
E 358
D 352
# ifdef SOLARIS_2_3
E 352
I 352
# if SOLARIS == 203
E 352
	static struct hostent hp;
	static char buf[1000];
	extern struct hostent *_switch_gethostbyaddr_r();

	return _switch_gethostbyaddr_r(addr, len, type, &hp, buf, sizeof(buf), &h_errno);
# else
I 261
	extern struct hostent *__switch_gethostbyaddr();

E 261
	return __switch_gethostbyaddr(addr, len, type);
# endif
I 358
#else
	return gethostbyaddr(addr, len, type);
#endif
E 358
}
I 358
/*
**  SM_GETPW{NAM,UID} -- wrapper for getpwnam and getpwuid
*/
E 358

D 358
#endif
E 358
I 358
struct passwd *
sm_getpwnam(user)
D 361
	const char *user;
E 361
I 361
	char *user;
E 361
{
D 359
	extern struct passwd *getpwnam();

E 359
	return getpwnam(user);
}

struct passwd *
sm_getpwuid(uid)
D 409
	uid_t uid;
E 409
I 409
	UID_T uid;
E 409
{
D 359
	extern struct passwd *getpwuid();

E 359
	return getpwuid(uid);
}
E 358
I 269
/*
I 377
**  LOAD_IF_NAMES -- load interface-specific names into $=w
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Loads $=w with the names of all the interfaces.
*/

#ifdef SIOCGIFCONF
I 387
struct rtentry;
struct mbuf;
E 387
D 385
# include <netdb.h>
E 385
# include <arpa/inet.h>
I 385
# include <sys/time.h>
E 385
# include <net/if.h>
#endif

void
load_if_names()
{
#ifdef SIOCGIFCONF
D 383
	struct hostent *hp;
E 383
	int s;
I 383
	int i;
E 383
        struct ifconf ifc;
D 383
        struct ifreq *ifr;
E 383
	char interfacebuf[1024];
D 383
	int n;
	extern char *inet_ntoa();
	extern struct hostent *gethostbyaddr();
E 383

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1)
		return;

	/* get the list of known IP address from the kernel */
D 383
        ifc.ifc_len = sizeof(interfacebuf);
E 383
        ifc.ifc_buf = interfacebuf;
I 383
        ifc.ifc_len = sizeof interfacebuf;
E 383
	if (ioctl(s, SIOCGIFCONF, (char *)&ifc) < 0)
	{
		if (tTd(0, 4))
			printf("SIOGIFCONF failed: %s\n", errstring(errno));
I 383
		close(s);
E 383
		return;
	}
I 383
	close(s);
E 383

	/* scan the list of IP address */
D 409
	if (tTd(0, 4))
E 409
I 409
	if (tTd(0, 40))
E 409
		printf("scanning for interface specific names, ifc_len=%d\n",
			ifc.ifc_len);

D 383
        ifr = ifc.ifc_req;
        for (n = ifc.ifc_len / sizeof(struct ifreq); n > 0; n--, ifr++)
        {
E 383
I 383
	for (i = 0; i < ifc.ifc_len; )
	{
		struct ifreq *ifr = (struct ifreq *) &ifc.ifc_buf[i];
		struct sockaddr *sa = &ifr->ifr_addr;
E 383
		struct in_addr ia;
I 383
		struct hostent *hp;
E 383
		char ip_addr[256];
I 383
		extern char *inet_ntoa();
		extern struct hostent *gethostbyaddr();
E 383

I 383
#ifdef BSD4_4_SOCKADDR
		if (sa->sa_len > sizeof ifr->ifr_addr)
			i += sizeof ifr->ifr_name + sa->sa_len;
		else
#endif
			i += sizeof *ifr;

E 383
		if (tTd(0, 20))
D 383
			printf("%s\n", anynet_ntoa((SOCKADDR *) &ifr->ifr_addr));
E 383
I 383
			printf("%s\n", anynet_ntoa((SOCKADDR *) sa));
E 383

		if (ifr->ifr_addr.sa_family != AF_INET)
			continue;

		/* extract IP address from the list*/
D 383
		ia = (((struct sockaddr_in *) (&ifr->ifr_addr))->sin_addr);
E 383
I 383
		ia = (((struct sockaddr_in *) sa)->sin_addr);
E 383

		/* save IP address in text from */
		(void) sprintf(ip_addr, "[%s]",
D 383
			inet_ntoa(((struct sockaddr_in *)(&ifr->ifr_addr))->sin_addr));
E 383
I 383
			inet_ntoa(((struct sockaddr_in *) sa)->sin_addr));
E 383
		if (!wordinclass(ip_addr, 'w'))
		{
			setclass('w', ip_addr);
			if (tTd(0, 4))
				printf("\ta.k.a.: %s\n", ip_addr);
		}

		/* skip "loopback" interface "lo" */
		if (strcmp("lo0", ifr->ifr_name) == 0)
			continue;

		/* lookup name with IP address */
		hp = sm_gethostbyaddr((char *) &ia, sizeof(ia), AF_INET);
		if (hp == NULL)
		{
			syslog(LOG_CRIT, "gethostbyaddr() failed for %s\n",
				inet_ntoa(ia));
			continue;
		}

		/* save its cname */
		if (!wordinclass(hp->h_name, 'w'))
		{
			setclass('w', hp->h_name);
			if (tTd(0, 4))
				printf("\ta.k.a.: %s\n", hp->h_name);
		}

		/* save all it aliases name */
		while (*hp->h_aliases)
		{
			if (!wordinclass(*hp->h_aliases, 'w'))
			{
				setclass('w', *hp->h_aliases);
				if (tTd(0, 4))
				printf("\ta.k.a.: %s\n", *hp->h_aliases);
			}
			hp->h_aliases++;
		}
	}
#endif
}
/*
E 377
**  NI_PROPVAL -- netinfo property value lookup routine
**
**	Parameters:
D 320
**		directory -- the Netinfo directory name.
**		propname -- the Netinfo property name.
E 320
I 320
**		keydir -- the Netinfo directory name in which to search
**			for the key.
**		keyprop -- the name of the property in which to find the
**			property we are interested.  Defaults to "name".
**		keyval -- the value for which we are really searching.
**		valprop -- the property name for the value in which we
**			are interested.
**		sepchar -- if non-nil, this can be multiple-valued, and
**			we should return a string separated by this
**			character.
E 320
**
**	Returns:
**		NULL -- if:
**			1. the directory is not found
**			2. the property name is not found
**			3. the property contains multiple values
**			4. some error occured
**		else -- the location of the config file.
**
I 320
**	Example:
**		To search for an alias value, use:
**		  ni_propval("/aliases", "name", aliasname, "members", ',')
**
E 320
**	Notes:
**      	Caller should free the return value of ni_proval
*/

D 410
#ifdef NETINFO
E 410
I 410
#if NETINFO
E 410

# include <netinfo/ni.h>

# define LOCAL_NETINFO_DOMAIN    "."
# define PARENT_NETINFO_DOMAIN   ".."
# define MAX_NI_LEVELS           256

char *
D 320
ni_propval(directory, propname)
	char *directory;
	char *propname;
E 320
I 320
ni_propval(keydir, keyprop, keyval, valprop, sepchar)
	char *keydir;
	char *keyprop;
	char *keyval;
	char *valprop;
	char sepchar;
E 320
{
D 277
	char *propval;
E 277
I 277
	char *propval = NULL;
E 277
	int i;
I 320
	int j, alen;
E 320
	void *ni = NULL;
	void *lastni = NULL;
	ni_status nis;
	ni_id nid;
	ni_namelist ninl;
I 320
	register char *p;
	char keybuf[1024];
E 320

	/*
I 320
	**  Create the full key from the two parts.
	**
	**	Note that directory can end with, e.g., "name=" to specify
	**	an alternate search property.
	*/

D 324
	i = strlen(keydir) + strlen(keyval) + 2)
E 324
I 324
	i = strlen(keydir) + strlen(keyval) + 2;
E 324
	if (keyprop != NULL)
		i += strlen(keyprop) + 1;
	if (i > sizeof keybuf)
		return NULL;
	strcpy(keybuf, keydir);
	strcat(keybuf, "/");
	if (keyprop != NULL)
	{
		strcat(keybuf, keyprop);
		strcat(keybuf, "=");
	}
	strcat(keybuf, keyval);

	/*
E 320
	**  If the passed directory and property name are found
	**  in one of netinfo domains we need to search (starting
	**  from the local domain moving all the way back to the
	**  root domain) set propval to the property's value
	**  and return it.
	*/

	for (i = 0; i < MAX_NI_LEVELS; ++i)
	{
		if (i == 0)
		{
			nis = ni_open(NULL, LOCAL_NETINFO_DOMAIN, &ni);
		}
		else
		{
			if (lastni != NULL)
				ni_free(lastni);
			lastni = ni;
			nis = ni_open(lastni, PARENT_NETINFO_DOMAIN, &ni);
		}

		/*
		**  Don't bother if we didn't get a handle on a
		**  proper domain.  This is not necessarily an error.
		**  We would get a positive ni_status if, for instance
		**  we never found the directory or property and tried
		**  to open the parent of the root domain!
		*/

		if (nis != 0)
			break;

		/*
		**  Find the path to the server information.
		*/

D 320
		if (ni_pathsearch(ni, &nid, directory) != 0)
E 320
I 320
		if (ni_pathsearch(ni, &nid, keybuf) != 0)
E 320
			continue;

		/*
D 320
		**  Find "host" information.
E 320
I 320
		**  Find associated value information.
E 320
		*/

D 320
		if (ni_lookupprop(ni, &nid, propname, &ninl) != 0)
E 320
I 320
		if (ni_lookupprop(ni, &nid, valprop, &ninl) != 0)
E 320
			continue;

		/*
D 320
		**  If there's only one name in
		**  the list, assume we've got
		**  what we want.
E 320
I 320
		**  See if we have an acceptable number of values.
E 320
		*/

D 320
		if (ninl.ni_namelist_len == 1)
E 320
I 320
		if (ninl.ni_namelist_len <= 0)
			continue;

		if (sepchar == '\0' && ninl.ni_namelist_len > 1)
E 320
		{
D 320
			propval = ni_name_dup(ninl.ni_namelist_val[0]);
			break;
E 320
I 320
			ni_namelist_free(&ninl);
			continue;
E 320
		}
I 320

D 377
		/* 
E 377
I 377
		/*
E 377
		**  Calculate number of bytes needed and build result
		*/

		alen = 1;
		for (j = 0; j < ninl.ni_namelist_len; j++)
			alen += strlen(ninl.ni_namelist_val[j]) + 1;
		propval = p = xalloc(alen);
		for (j = 0; j < ninl.ni_namelist_len; j++)
		{
			strcpy(p, ninl.ni_namelist_val[j]);
			p += strlen(p);
			*p++ = sepchar;
D 377
		} 
E 377
I 377
		}
E 377
		*--p = '\0';

		ni_namelist_free(&ninl);
E 320
	}

	/*
	**  Clean up.
	*/

	if (ni != NULL)
		ni_free(ni);
	if (lastni != NULL && ni != lastni)
		ni_free(lastni);

	return propval;
}

#endif /* NETINFO */
I 273
/*
**  HARD_SYSLOG -- call syslog repeatedly until it works
**
**	Needed on HP-UX, which apparently doesn't guarantee that
**	syslog succeeds during interrupt handlers.
*/

#ifdef __hpux

# define MAXSYSLOGTRIES	100
# undef syslog

I 394
D 395
void
E 395
E 394
# ifdef __STDC__
I 395
void
E 395
hard_syslog(int pri, char *msg, ...)
# else
hard_syslog(pri, msg, va_alist)
	int pri;
	char *msg;
	va_dcl
# endif
{
	int i;
	char buf[SYSLOG_BUFSIZE * 2];
	VA_LOCAL_DECL;

	VA_START(msg);
	vsprintf(buf, msg, ap);
	VA_END;

	for (i = MAXSYSLOGTRIES; --i >= 0 && syslog(pri, "%s", buf) < 0; )
		continue;
}

#endif
I 360
/*
**  LOCAL_HOSTNAME_LENGTH
**
**	This is required to get sendmail to compile against BIND 4.9.x
**	on Ultrix.
*/

#if defined(ultrix) && NAMED_BIND

# include <resolv.h>
# if __RES >= 19931104

int
local_hostname_length(hostname)
	char *hostname;
{
	int len_host, len_domain;

	if (!*_res.defdname)
		res_init();
	len_host = strlen(hostname);
	len_domain = strlen(_res.defdname);
	if (len_host > len_domain &&
	    (strcasecmp(hostname + len_host - len_domain,_res.defdname) == 0) &&
	    hostname[len_host - len_domain - 1] == '.')
		return len_host - len_domain - 1;
	else
		return 0;
}

# endif
#endif
I 365
/*
**  Compile-Time options
*/

char	*CompileOptions[] =
{
#if HESIOD
	"HESIOD",
#endif
D 411
#if LOG
E 411
I 411
#ifdef LOG
E 411
	"LOG",
#endif
#if MATCHGECOS
	"MATCHGECOS",
#endif
#if NAMED_BIND
	"NAMED_BIND",
#endif
#if NDBM
	"NDBM",
#endif
#if NETINET
	"NETINET",
#endif
#if NETINFO
	"NETINFO",
#endif
#if NETISO
	"NETISO",
#endif
#if NETNS
	"NETNS",
#endif
#if NETUNIX
	"NETUNIX",
#endif
#if NETX25
	"NETX25",
#endif
#if NEWDB
	"NEWDB",
#endif
#if NIS
	"NIS",
#endif
I 384
#if NISPLUS
	"NISPLUS",
#endif
E 384
#if SCANF
	"SCANF",
#endif
#if SUID_ROOT_FILES_OK
	"SUID_ROOT_FILES_OK",
#endif
#if USERDB
	"USERDB",
#endif
#if XDEBUG
	"XDEBUG",
#endif
#if XLA
	"XLA",
#endif
	NULL
};
I 404


/*
**  OS compile options.
*/

char	*OsCompileOptions[] =
{
#if HASFLOCK
	"HASFLOCK",
#endif
#if HASGETUSERSHELL
	"HASGETUSERSHELL",
#endif
#if HASINITGROUPS
	"HASINITGROUPS",
#endif
#if HASLSTAT
	"HASLSTAT",
#endif
#if HASSETREUID
	"HASSETREUID",
#endif
#if HASSETSID
	"HASSETSID",
#endif
#if HASSETVBUF
	"HASSETVBUF",
#endif
#if HASUNAME
	"HASUNAME",
#endif
#if IDENTPROTO
	"IDENTPROTO",
#endif
#if IP_SRCROUTE
	"IP_SRCROUTE",
#endif
#if SYS5SETPGRP
	"SYS5SETPGRP",
#endif
#if SYSTEM5
	"SYSTEM5",
#endif
#if USESETEUID
	"USESETEUID",
#endif
	NULL
};
E 404
E 365
E 360
E 273
E 269
E 256
E 253
E 180
E 165
E 164
E 160
E 156
E 140
E 139
E 111
E 103
I 94
D 100
/*
**  DBMCLOSE -- close the DBM file
**
**	This depends on the implementation of the DBM library.  It
**	seems to work for all versions that I have come across.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Closes the current DBM file; dbminit must be
**		called again to continue using the DBM routines.
*/

dbmclose()
{
	extern int pagf, dirf;	/* defined in the DBM package */

	(void) close(pagf);
	(void) close(dirf);
}
E 100
E 94
E 90
I 83
D 86
/*
**  MYHOSTNAME -- return the name of this host.
**
**	Parameters:
D 84
**		none.
E 84
I 84
**		hostbuf -- a place to return the name of this host.
E 84
**
**	Returns:
D 84
**		The name of this host, as best as it can be determined.
E 84
I 84
**		A list of aliases for this host.
E 84
**
**	Side Effects:
**		none.
*/

D 84
char *
myhostname()
{
	static char hostbuf[40];
	register FILE *f;
E 84
I 84
#ifdef VMUNIX
#include <netdb.h>
#endif VMUNIX
E 84

D 84
	hostbuf[0] = '\0';
E 84
I 84
char **
myhostname(hostbuf)
	char hostbuf[];
{
E 84
#ifdef VMUNIX
I 84
	extern struct hostent *gethostbyname();
	struct hostent *hent;

E 84
	gethostname(hostbuf, sizeof hostbuf);
I 84
	hent = gethostbyname(hostbuf);
	if (hent != NULL)
		return (hent->h_aliases);
	else
		return (NULL);
E 84
# else VMUNIX
I 84
	register FILE *f;

	hostbuf[0] = '\0';
E 84
	f = fopen("/usr/include/whoami", "r");
	if (f != NULL)
	{
		(void) fgets(hostbuf, sizeof hostbuf, f);
		fixcrlf(hostbuf, TRUE);
		(void) fclose(f);
	}
I 84
	return (NULL);
E 84
#endif VMUNIX
D 84
	if (strncmp(hostbuf, "ucb", 3) == 0)
		return (&hostbuf[3]);
	else
		return (hostbuf);
E 84
}
E 86
E 83
E 18
E 1
