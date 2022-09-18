h55960
s 00002/00000/02857
d D 8.160 95/06/21 07:12:42 eric 506 505
c close passwd file before setuid() "just in case"
e
s 00002/00001/02855
d D 8.159 95/06/18 12:36:38 eric 505 504
c avoid MIMEing RFC1049 messages
e
s 00004/00006/02852
d D 8.158 95/06/13 09:23:06 eric 504 503
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00001/00001/02857
d D 8.157 95/06/13 08:11:20 eric 503 502
c fix possible null pointer dereference
e
s 00012/00001/02846
d D 8.156 95/06/10 12:54:16 eric 502 501
c allow symbolic service names on [IPC] mailers
e
s 00059/00030/02788
d D 8.155 95/05/31 08:01:39 eric 501 500
c better handling of dead.letter -- involves mailfile changes
e
s 00011/00002/02807
d D 8.154 95/05/28 11:49:56 eric 500 499
c lint
e
s 00019/00006/02790
d D 8.153 95/05/27 08:16:22 eric 499 498
c force *file* mailer to have setuid bit semantics even when a program
e
s 00001/00001/02795
d D 8.152 95/05/25 16:18:24 eric 498 497
c file mailer should run as default uid, not as sender
e
s 00002/00000/02794
d D 8.151 95/05/15 19:00:29 eric 497 496
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00001/00024/02793
d D 8.150 95/05/15 15:02:12 eric 496 495
c add "E" line to config file to set or propogate environment
c variables to children
e
s 00001/00001/02816
d D 8.149 95/04/25 06:45:11 eric 495 494
c make file mailer semantics switch off of P=[FILE]
e
s 00006/00006/02811
d D 8.148 95/04/24 20:31:36 eric 494 493
c efficiency improvements
e
s 00002/00054/02815
d D 8.147 95/04/23 14:03:04 eric 493 492
c updates for new DSN drafts
e
s 00043/00032/02826
d D 8.146 95/04/22 14:50:57 eric 492 491
c better use of extended DSN status codes
e
s 00006/00003/02852
d D 8.145 95/04/22 11:07:28 eric 491 490
c improved DSN status codes
e
s 00001/00001/02854
d D 8.144 95/04/21 09:57:32 eric 490 489
c update copyright notice
e
s 00004/00000/02851
d D 8.143 95/04/20 08:40:24 eric 489 488
c add Nice=N mailer option
e
s 00002/00002/02849
d D 8.142 95/03/31 16:53:58 eric 488 487
c merge a bit with Sun version
e
s 00001/00001/02850
d D 8.141 95/03/31 15:46:53 eric 487 486
c more type hacking for non-Posix/ANSI systems
e
s 00000/00001/02851
d D 8.140 95/03/31 10:52:11 eric 486 485
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00001/00004/02851
d D 8.139 95/03/30 15:25:34 eric 485 484
c fix another problem with improperly trashed e_lockfp on vfork
e
s 00011/00001/02844
d D 8.138 95/03/29 09:49:55 eric 484 482
c don't propogate RET or NOTIFY parameters down through mailing lists
e
s 00000/00000/02411
d D 8.84.1.4 95/03/28 18:26:09 eric 483 471
i 480
c avoid running out of file descriptors problem on vfork systems
e
s 00001/00000/02844
d D 8.137 95/03/27 09:25:41 eric 482 481
c more cleanup for DSN drafts
e
s 00001/00001/02843
d D 8.136 95/03/24 11:21:11 eric 481 480
c compile glitch
e
s 00001/00004/02843
d D 8.135 95/03/23 20:03:31 eric 480 479
c avoid running out of file descriptors problem on vfork systems
e
s 00009/00007/02838
d D 8.134 95/03/22 21:47:59 eric 479 478
c compile problem if !HASFLOCK
e
s 00042/00035/02803
d D 8.133 95/03/21 16:41:21 eric 478 477
c if all addresses are expensive, don't bother forking (for performance)
e
s 00022/00016/02816
d D 8.132 95/03/21 15:28:31 eric 477 476
c eliminate `D' line in qf file
e
s 00002/00002/02830
d D 8.131 95/03/21 09:26:55 eric 476 475
c new DSN draft
e
s 00006/00006/02826
d D 8.130 95/03/14 09:11:11 eric 475 474
c change call to expand() to be more rational (and consistent!)
e
s 00008/00008/02824
d D 8.129 95/03/14 08:19:02 eric 474 473
c be more precise on MAXNAME checking
e
s 00004/00001/02828
d D 8.128 95/03/11 18:02:22 eric 473 472
c more MIME cleanup
e
s 00001/00001/02828
d D 8.127 95/03/11 13:42:45 eric 472 470
c fix several MIME boundary-condition problems
e
s 00011/00006/02403
d D 8.84.1.3 95/03/05 14:55:31 eric 471 468
c fix new file creation
e
s 00034/00006/02795
d D 8.126 95/03/05 14:34:06 eric 470 469
c changes suggested by *Hobbit*; SafeFileEnvironment option
e
s 00000/00000/02801
d D 8.125 95/03/05 09:37:11 eric 469 467
i 468
c improved security for points where setuid has returned to sender
e
s 00024/00002/02385
d D 8.84.1.2 95/03/05 08:26:16 eric 468 463
c various security bulletproofing
e
s 00011/00016/02768
d D 8.124 95/02/23 15:50:44 eric 467 466
c cleanup to make gcc -Winitialized happier
e
s 00001/00001/02783
d D 8.123 95/02/21 10:03:49 eric 466 465
c compiler glitch -- variable used before set
e
s 00008/00001/02776
d D 8.122 95/02/20 19:00:02 eric 465 464
c fix glitch in "relayed" messages
e
s 00010/00007/02767
d D 8.121 95/02/19 07:43:49 eric 464 462
c updated status codes for DSNs
e
s 00000/00000/02387
d D 8.84.1.1 95/02/10 07:37:55 eric 463 426
i 460 454
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00005/00007/02769
d D 8.120 95/02/05 08:04:01 eric 462 461
c cut at 20 January version of DSN document
e
s 00029/00010/02747
d D 8.119 94/12/10 07:46:47 eric 461 460
c log transaction delay as well as queue delay (for ordering lists)
e
s 00001/00000/02756
d D 8.118 94/12/01 08:41:11 eric 460 459
c fix problem with left over df files after hop count exceeded
e
s 00002/00001/02754
d D 8.117 94/11/27 16:36:42 eric 459 458
c don't set q_statmta if the current host name is null
e
s 00056/00006/02699
d D 8.116 94/11/27 15:22:37 eric 458 457
c more DSN hacking
e
s 00006/00000/02699
d D 8.115 94/11/27 11:20:05 eric 457 456
c improved debugging
e
s 00003/00003/02696
d D 8.114 94/11/25 09:06:15 eric 456 455
c improve DSN handling somewhat + some bug fixes
e
s 00013/00001/02686
d D 8.113 94/11/22 22:25:01 eric 455 454
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00001/00001/02686
d D 8.112 94/11/21 21:06:40 eric 454 453
c avoid core dump on debugging if e->e_message == NULL
e
s 00001/00001/02686
d D 8.111 94/11/20 20:28:49 eric 453 452
c compile glitches
e
s 00003/00003/02684
d D 8.110 94/11/20 17:54:04 eric 452 451
c patch for !HASFLOCK
e
s 00010/00010/02677
d D 8.109 94/11/20 13:50:20 eric 451 450
c allow files referenced in aliases to write files as the default uid
e
s 00007/00005/02680
d D 8.108 94/11/19 16:57:36 eric 450 449
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00049/00046/02636
d D 8.107 94/11/13 10:14:04 eric 449 448
c move fork up so that e-mails to multiple lists don't create
c "fork storms"
e
s 00013/00016/02669
d D 8.106 94/11/11 07:24:25 eric 448 447
c avoid core dump if df file cannot be opened
e
s 00001/00006/02684
d D 8.105 94/11/08 11:49:02 eric 447 446
c allow per-mailer default character set (applies to INCOMING mailer)
e
s 00006/00003/02684
d D 8.104 94/11/05 15:09:41 eric 446 445
c clear MCIF_CVT8TO7 bit from cached MCI structures
e
s 00059/00002/02628
d D 8.103 94/11/04 08:40:33 eric 445 444
c first cut at DSN implementation
e
s 00004/00000/02626
d D 8.102 94/10/17 09:26:20 eric 444 443
c flush cached SMTP connections before programatic deliveries
e
s 00007/00001/02619
d D 8.101 94/10/16 10:34:58 eric 443 442
c better logging of connection open/usage
e
s 00010/00002/02610
d D 8.100 94/10/15 08:55:43 eric 442 441
c allow option to set default character set for MIME
e
s 00005/00001/02607
d D 8.99 94/09/08 15:20:00 eric 441 440
c attempt to allow udb rewriting of envelope senders; still not
c quite right, but I can't really test it without a network connection
e
s 00003/00003/02605
d D 8.98 94/09/04 13:56:34 eric 440 439
c fix bug that causes infinite loop on naked CR character
e
s 00003/00001/02605
d D 8.97 94/08/27 14:08:12 eric 439 438
c add _FORCE_MAIL_LOCAL_=yes environment for DG-UX (euch!)
e
s 00014/00001/02592
d D 8.96 94/08/15 18:07:22 eric 438 437
c store dev information in qf file; add RFC 1428-specified
c Content-Type: text/plain; charset=unknown-8bit header to messages
c being converted from 8 -> 7 bit with no specific Content-Type
e
s 00004/00002/02589
d D 8.95 94/08/15 10:13:49 eric 437 436
c avoid bogosity on zero line limit
e
s 00002/00002/02589
d D 8.94 94/08/14 06:56:11 eric 436 435
c fix compile error on other systems
e
s 00017/00000/02574
d D 8.93 94/08/07 17:42:06 eric 435 434
c DECWRL extensions to qf file
e
s 00014/00011/02560
d D 8.92 94/08/07 13:46:45 eric 434 433
c generalized U= mailer field to cleanly override DefUid
e
s 00006/00001/02565
d D 8.91 94/08/07 12:27:59 eric 433 432
c allow U= flag on mailer to run as specific user id
e
s 00163/00024/02403
d D 8.90 94/08/07 10:02:37 eric 432 431
c first cut at full 8-bit data capability
e
s 00013/00002/02414
d D 8.89 94/07/23 10:12:30 eric 431 430
c tweaks & bug fixes to MIME algorithm
e
s 00039/00013/02377
d D 8.88 94/07/23 07:59:43 eric 430 429
c MIME 8 to 7 bit support
e
s 00004/00005/02386
d D 8.87 94/07/03 11:48:26 eric 429 428
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00006/00000/02385
d D 8.86 94/06/19 06:40:21 eric 428 427
c reset h_errno in a few critical places to avoid spurious errors
e
s 00000/00001/02385
d D 8.85 94/06/17 17:40:09 eric 427 426
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00001/00001/02385
d D 8.84 94/05/13 13:25:43 eric 426 424
c avoid returning error AND re-queueing for ``user@.'' address
e
s 00000/00001/02385
d R 8.84 94/05/12 09:43:51 eric 425 424
c be sure to return an error message on "too many hops" -- if a
c message was being sent to an alias it would be dropped becasue the
c queue wasn't completely instantiated
e
s 00005/00002/02381
d D 8.83 94/04/29 09:29:20 eric 424 423
c fix problem with error messages on host names that have %s
e
s 00002/00003/02381
d D 8.82 94/04/18 15:30:29 eric 423 422
c fix relay= logging on queued messages
e
s 00003/00001/02381
d D 8.81 94/04/14 09:42:41 eric 422 421
c give return-receipt on delivery to mailing lists (instead of to the
c members of that list) and suppress Return-Receipt-To: in subsequent
c deliveries to avoid denial of service attacks and generally improve
c the semantics
e
s 00001/00000/02381
d D 8.80 94/04/12 16:32:09 eric 421 420
c avoid bogus relay= logging
e
s 00003/00000/02378
d D 8.79 94/04/12 08:21:37 eric 420 419
c deliver all mail in a new session; this solves some security problems
e
s 00012/00012/02366
d D 8.78 94/03/11 14:42:05 eric 419 418
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00004/00000/02374
d D 8.77 94/03/07 12:10:30 eric 418 417
c fix CNAME loop problem: gave error messages and requeued messages
e
s 00001/00001/02373
d D 8.76 94/03/04 17:21:23 eric 417 416
c avoid possible bogus pointer dereferences if there are %'s in the
c 250 response from DATA
e
s 00006/00000/02368
d D 8.75 94/03/04 08:48:18 eric 416 415
c make sure that you don't get bogus addresses queued up on
c name server problems and split envelopes
e
s 00002/00001/02366
d D 8.74 94/02/26 07:21:31 eric 415 414
c tune short syslog buffers even more; have "too many hops" message
c send to postmaster & be sure to completely deinstantiate the queue
e
s 00002/00002/02365
d D 8.73 94/02/14 17:17:18 eric 414 413
c fix problem that can cause mailer output to be discarded in some circumstances
e
s 00002/00002/02365
d D 8.72 94/02/07 08:35:25 eric 413 412
c fix extra commas in short buffer syslogging
e
s 00024/00004/02343
d D 8.71 94/02/06 19:29:05 eric 412 411
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00002/00002/02345
d D 8.70 94/02/06 13:06:56 eric 411 410
c improve logging
e
s 00005/00008/02342
d D 8.69 94/02/06 12:52:38 eric 410 409
c try to limit the overhead on split envelopes
e
s 00009/00006/02341
d D 8.68 94/02/06 12:24:53 eric 409 407
c tighten up short syslog buffers even more
e
s 00025/00034/02313
d D 8.67.1.1 94/02/06 12:08:03 eric 408 407
c preliminary try at controlling fd usage; doesn't work right
c because main envelope qf doesn't get instantiated early enough
e
s 00002/00001/02345
d D 8.67 94/02/05 12:29:51 eric 407 406
c allow $s to be set to NULL for locally generated mail
e
s 00004/00004/02342
d D 8.66 94/01/27 07:05:54 eric 406 405
c change logging so that IP addresses always use [angle brackets]
e
s 00038/00032/02308
d D 8.65 94/01/24 08:01:40 eric 405 404
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00001/00001/02339
d D 8.64 94/01/22 16:12:26 eric 404 403
c make HASFLOCK a 0/1 definition so Linux can turn it off
e
s 00002/00001/02338
d D 8.63 94/01/15 12:38:23 eric 403 402
c restore old prog mailer handling -- programs executed from
c an alias (but not through a .forward) are run as daemon
e
s 00014/00010/02325
d D 8.62 94/01/12 12:38:38 eric 402 401
c some cleanup for short syslog buffers
e
s 00007/00004/02328
d D 8.61 94/01/08 17:29:23 eric 401 400
c fix problem that was causing the ctladdr of whoever ran the daemon
c (usually root) to own the delivery process
e
s 00002/00001/02330
d D 8.60 94/01/06 10:15:36 eric 400 399
c give proper reply code on tempfail
e
s 00000/00011/02331
d D 8.59 94/01/05 09:22:41 eric 399 398
c improvements to local program access lockouts
e
s 00011/00000/02331
d D 8.58 93/12/24 06:29:25 eric 398 397
c fixes to restrict users who don't have a "regular" login shell (i.e.,
c not listed in /etc/shells) from forwarding to a program or file; they can
c write their .forward file from another machine and then get in.
e
s 00003/00003/02328
d D 8.57 93/12/22 07:56:23 eric 397 396
c fix null pointer dereference
e
s 00001/00001/02330
d D 8.56 93/12/22 05:11:18 eric 396 395
c avoid misleading error message if an SMTP mailer drops core
e
s 00008/00001/02323
d D 8.55 93/12/14 14:05:57 eric 395 394
c fix problem of local mailer being called with uid of receiver,
c not uid of sender -- this was an unintended semantic change
e
s 00000/00003/02324
d D 8.54 93/12/12 08:36:50 eric 394 393
c avoid bogus pointer dereference in shortened logdelivery format
e
s 00002/00003/02325
d D 8.53 93/12/10 18:01:26 eric 393 392
c move SmtpError decl out -- two identical decl's seem to be confusing gcc
e
s 00003/00008/02325
d D 8.52 93/12/10 14:56:09 eric 392 391
c adjust ctladdr processing
e
s 00081/00020/02252
d D 8.51 93/12/10 12:51:18 eric 391 390
c deal with possibility of very short syslog buffers (for SVR4)
e
s 00013/00004/02259
d D 8.50 93/12/10 11:34:46 eric 390 389
c fix problem that caused mailers returning EX_IOERR or EX_OSERR to
c drop the error message
e
s 00001/00001/02262
d D 8.49 93/12/02 14:40:02 eric 389 388
c fix typo in logdeliver() that truncated part of the log
e
s 00001/00006/02262
d D 8.48 93/12/02 10:17:51 eric 388 387
c fix bogus implementation of name overflow limiting
e
s 00001/00001/02267
d D 8.47 93/12/01 14:27:06 eric 387 386
c minor typos
e
s 00001/00001/02267
d D 8.46 93/11/30 08:27:12 eric 386 385
c fix typo -- setuid => setgid
e
s 00054/00003/02214
d D 8.45 93/11/30 08:22:25 eric 385 384
c try to keep syslog entries reasonably short
e
s 00001/00001/02216
d D 8.44 93/11/27 08:02:02 eric 384 383
c fix problem that allowed Deferred: messages to override fatal messages
e
s 00009/00004/02208
d D 8.43 93/11/25 11:22:50 eric 383 382
c don't try to print the hostname on -bv if there is none.
e
s 00003/00002/02209
d D 8.42 93/11/20 06:52:29 eric 382 381
c curhost can be null if running SMTP to a program: avoid core dumps
e
s 00008/00001/02203
d D 8.41 93/11/14 08:26:42 eric 381 380
c improve diagnosis of null host name/signature
e
s 00002/00000/02202
d D 8.40 93/11/13 07:28:07 eric 380 379
c set group ids completely before calling programs
e
s 00001/00000/02201
d D 8.39 93/11/09 06:41:17 eric 379 378
c improve responsiveness to load average
e
s 00003/00006/02198
d D 8.38 93/11/08 09:54:09 eric 378 377
c be much less trusting about setuid in mailfile -- still works for the
c .forward case because ctladdr != NULL there
e
s 00045/00021/02159
d D 8.37 93/10/29 19:24:31 eric 377 376
c improved logging (log ctladdr on recipients
e
s 00000/00004/02180
d D 8.36 93/10/23 12:46:29 eric 376 375
c fix problems causing excessive numbers of open files
e
s 00002/00003/02182
d D 8.35 93/10/21 07:18:48 eric 375 374
c allow dumping of MCI cache to syslog for debugging
e
s 00001/00000/02184
d D 8.34 93/10/17 12:00:35 eric 374 373
c fix handling of pre-parsing address errors
e
s 00002/00000/02182
d D 8.33 93/10/17 10:00:16 eric 373 372
c additional debugging information for too many open files problem
e
s 00023/00001/02159
d D 8.32 93/10/16 08:49:54 eric 372 371
c check for possibility of fdopen returning null
e
s 00035/00010/02125
d D 8.31 93/10/15 08:34:52 eric 371 370
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00000/00005/02135
d D 8.30 93/10/08 15:54:45 eric 370 369
c 8.6.1: A/UX and Encore UMAX V patches; fix to not toss error messages
c too early
e
s 00007/00000/02133
d D 8.29 93/10/03 07:29:04 eric 369 368
c free message during startup so that the printed message is as
c fresh as possible
e
s 00004/00001/02129
d D 8.28 93/10/02 06:58:02 eric 368 367
c be more generous at assigning the home directory to $z
e
s 00000/00007/02130
d D 8.27 93/09/29 13:12:43 eric 367 366
c improve connection caching by making [host] look like host after
c hostsignature call
e
s 00001/00002/02136
d D 8.26 93/09/26 19:08:37 eric 366 365
c fix problem causing "c" option (don't connect to expensive mailers)
c to be ignored in some SMTP runs.
e
s 00004/00001/02134
d D 8.25 93/09/21 15:32:52 eric 365 364
c avoid duplicate error messages
e
s 00000/00005/02135
d D 8.24 93/09/19 19:23:29 eric 364 363
c NeXT portability changes; cleanup of <sys/wait.h> assumptions
e
s 00002/00002/02138
d D 8.23 93/09/18 22:07:38 eric 363 362
c print more information on "too many hops" message
e
s 00010/00000/02130
d D 8.22 93/09/05 14:53:40 eric 362 361
c more attempts to catch bad fd 1 bug
e
s 00021/00008/02109
d D 8.21 93/09/04 11:50:55 eric 361 360
c more attempts to find the fd 1 closed error
e
s 00005/00002/02112
d D 8.20 93/09/02 17:18:40 eric 360 359
c better error messages
e
s 00024/00020/02090
d D 8.19 93/09/02 09:43:54 eric 359 358
c POSIX changes
e
s 00001/00000/02109
d D 8.18 93/08/30 12:35:15 eric 358 357
c fix missing trailing \0 problem
e
s 00004/00001/02105
d D 8.17 93/08/28 09:36:13 eric 357 356
c clean up No ! in UUCP! message
e
s 00001/00000/02105
d D 8.16 93/08/23 08:25:15 eric 356 355
c reset SmtpPhase on initial connection so messages are accurate
e
s 00000/00004/02105
d D 8.15 93/08/21 07:22:54 eric 355 354
c more NeXT portability changes; use initgroups when reading .forward files
e
s 00014/00003/02095
d D 8.14 93/08/20 12:12:59 eric 354 353
c avoid duplicate error message deliveries
e
s 00002/00017/02096
d D 8.13 93/08/20 08:08:55 eric 353 352
c fix screwed up error message returns in some situations
e
s 00021/00042/02092
d D 8.12 93/08/19 13:36:56 eric 352 351
c fix obscure lost mail problem if fcntl locking used (ugh)
e
s 00025/00019/02109
d D 8.11 93/08/08 10:55:33 eric 351 350
c print uids being used when execing a mailer
e
s 00004/00003/02124
d D 8.10 93/08/06 21:16:19 eric 350 349
c fix problem causing slow delivery warning to fail if OP set
e
s 00002/00001/02125
d D 8.9 93/07/29 08:31:47 eric 349 348
c don't call newstr() macro with arguments with subroutine calls, since
c it double-evaluates
e
s 00015/00016/02111
d D 8.8 93/07/26 09:22:05 eric 348 347
c signal and file locking portability changes
e
s 00002/00002/02125
d D 8.7 93/07/22 11:27:57 eric 347 346
c fix bogus error message with open timeout in :include: -- this also
c fixes a bug that caused resolver errnos to conflict with real errnos
e
s 00004/00000/02123
d D 8.6 93/07/20 19:24:45 eric 346 345
c RISCOS and SGI fixes; fix error handling (caused error messages to
c be discarded in some circumstances)
e
s 00001/00001/02122
d D 8.5 93/07/17 17:06:34 eric 345 344
c clean up semantics: QDONTSEND says don't ever send, and diables QQUEUEUP
c (previously, it meant don't send in this run)
e
s 00022/00035/02101
d D 8.4 93/07/16 10:28:40 eric 344 343
c clean up error handling, including concept of local error handling
e
s 00004/00000/02132
d D 8.3 93/07/13 12:58:41 eric 343 342
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00040/00061/02092
d D 8.2 93/07/11 06:52:43 eric 342 341
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/02151
d D 8.1 93/06/07 10:29:53 bostic 341 340
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/02153
d D 6.82 93/06/05 17:08:05 eric 340 339
c lint-style cleanup
e
s 00002/00001/02152
d D 6.81 93/06/05 09:10:10 eric 339 338
c don't send warning messages in response to warning messages
e
s 00007/00000/02146
d D 6.80 93/06/03 16:59:35 eric 338 337
c don't deliver messages that have had a fatal error during collection
e
s 00000/00014/02146
d D 6.79 93/05/27 11:37:40 eric 337 336
c prototype functions
e
s 00006/00001/02154
d D 6.78 93/05/21 08:20:26 eric 336 335
c log more information on -bv "deliverable" message
e
s 00001/00001/02154
d D 6.77 93/05/17 10:56:18 eric 335 334
c type conflicts
e
s 00000/00001/02155
d D 6.76 93/05/17 10:32:56 eric 334 333
c delete unneeded and conflicting errstring declarations
e
s 00002/00004/02154
d D 6.75 93/05/14 13:51:52 eric 333 332
c give better error message on "can't exec" error
e
s 00001/00001/02157
d D 6.74 93/05/13 14:25:19 eric 332 331
c fix code that does MX fallback to avoid null ptr refs
e
s 00005/00000/02153
d D 6.73 93/05/12 08:00:26 eric 331 330
c allow 421 instead of initial greeting message to go to next MX
e
s 00002/00002/02151
d D 6.72 93/05/05 08:11:29 eric 330 329
c create dead.letter with FileMode instead of 0666
e
s 00014/00003/02139
d D 6.71 93/05/04 15:45:14 eric 329 328
c update for MIME encapsulated error messages
e
s 00004/00000/02138
d D 6.70 93/04/29 20:35:41 eric 328 327
c implement b mailer flag
e
s 00010/00001/02128
d D 6.69 93/04/27 22:06:04 eric 327 326
c fix bug that can cause senders to be queued as recipients if the
c name server is down when the mail is initially sent
e
s 00000/00001/02129
d D 6.68 93/04/27 18:51:48 eric 326 325
c move #include <sys/stat.h> into conf.h
e
s 00005/00005/02125
d D 6.67 93/04/26 13:28:00 eric 325 324
c use FileMailer instead of ProgMailer
e
s 00001/00005/02129
d D 6.66 93/04/26 13:13:59 eric 324 323
c have getmxrr look at $=w to determine local host name
e
s 00006/00000/02128
d D 6.65 93/04/26 12:43:00 eric 323 322
c debugging printf in mailfile
e
s 00004/00002/02124
d D 6.64 93/04/19 09:19:38 eric 322 321
c change remotename to use flag bits instead of individual parameters;
c add a pstat parameter to return status information up
e
s 00009/00000/02117
d D 6.63 93/04/17 08:48:20 eric 321 320
c turn off DEFNAMES and DNSRCH in hostsignature for old config file
c compatibility
e
s 00048/00025/02069
d D 6.62 93/04/14 07:48:01 eric 320 319
c let the $@ clause of an SMTP mailer be a colon separated list of
c hosts; these will be searched like MX records
e
s 00001/00001/02093
d D 6.61 93/04/12 14:48:54 eric 319 318
c reset statmsg before each mailer invocation to avoid bogus messages
c in log
e
s 00022/00000/02072
d D 6.60 93/04/03 07:20:11 eric 318 317
c add Directory mailer field
e
s 00006/00002/02066
d D 6.59 93/04/01 14:59:25 eric 317 316
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00024/00011/02044
d D 6.58 93/04/01 14:10:41 eric 316 315
c give more info on error messages
e
s 00006/00004/02049
d D 6.57 93/04/01 13:30:57 eric 315 313
c clear FATALERRS indication in cloned envelope; use e_statmsg for
c logging of OK status
e
s 00139/00126/01927
d D 6.56.1.1 93/03/30 13:28:35 eric 314 313
c attempt at quick RCPT response
e
s 00040/00004/02013
d D 6.56 93/03/29 12:44:55 eric 313 312
c additional checking on pipe file handling
e
s 00790/00809/01227
d D 6.55 93/03/26 06:41:38 eric 312 311
c try to fall back to MX sites if there is a failure anywhere
c in delivery (not just in connection establishment)
e
s 00025/00019/02011
d D 6.54 93/03/25 10:03:52 eric 311 310
c improve error reporting; open new transcript on envelope cloning
e
s 00003/00003/02027
d D 6.53 93/03/19 16:24:32 eric 310 309
c initial hooks for ISO networking
e
s 00030/00007/02000
d D 6.52 93/03/19 11:46:40 eric 309 308
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00004/00002/02003
d D 6.51 93/03/19 08:50:59 eric 308 307
c move SendMode and ErrorMode into the envelope
e
s 00004/00008/02001
d D 6.50 93/03/19 08:30:20 eric 307 306
c POSIX changes; use dup2
e
s 00006/00003/02003
d D 6.49 93/03/18 19:35:49 eric 306 305
c make certain we always enqueue split envelopes
e
s 00009/00000/01997
d D 6.48 93/03/18 15:12:23 eric 305 304
c add logging on envelope splitting; some debugging
e
s 00003/00005/01994
d D 6.47 93/03/18 10:56:30 eric 304 303
c restore e_sender as sending address sans decorations
e
s 00003/00006/01996
d D 6.46 93/03/17 09:55:20 eric 303 302
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00001/00001/02001
d D 6.45 93/03/16 18:06:12 eric 302 301
c pass envelope to disconnect to avoid another use of CurEnv; make
c disconnect more POSIXish
e
s 00089/00065/01913
d D 6.44 93/03/16 09:16:19 eric 301 300
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00013/00003/01965
d D 6.43 93/03/14 08:54:21 eric 300 299
c pass TZ variable to children (for System V)
e
s 00000/00013/01968
d D 6.42 93/03/14 08:31:22 eric 299 298
c back out setproctitle changes; they trash argv before everything
c has been properly saved
e
s 00022/00010/01959
d D 6.41 93/03/13 22:50:43 eric 298 297
c fix SysExMsg printing; setproctitle on getmxrr
e
s 00001/00012/01968
d D 6.40 93/03/07 16:16:08 eric 297 296
c use transienterror() all places where we do this sort of mapping
e
s 00002/00002/01978
d D 6.39 93/03/06 10:52:59 eric 296 295
c don't automatically print errno in usrerr -- it can be too misleading
e
s 00022/00022/01958
d D 6.38 93/03/06 09:32:29 eric 295 294
c improve logging to reduce redundancy
e
s 00002/00002/01978
d D 6.37 93/03/06 08:32:12 eric 294 293
c allow host on local addresses; don't do domain extension on
c return path, ever -- for <> addresses
e
s 00009/00000/01971
d D 6.36 93/03/04 22:26:21 eric 293 292
c diagnose null signature
e
s 00007/00003/01964
d D 6.35 93/03/03 15:17:40 eric 292 291
c limit number of arguments to each invocation of syslog for portability
e
s 00023/00026/01944
d D 6.34 93/03/01 16:25:39 eric 291 290
c change logging to use more keyword=value style logging
e
s 00034/00023/01936
d D 6.33 93/03/01 13:15:29 eric 290 289
c yet more logging
e
s 00001/00001/01958
d D 6.32 93/02/28 11:33:02 eric 289 288
c arrange for all prog mail to run as daemon
e
s 00010/00007/01949
d D 6.31 93/02/28 11:03:16 eric 288 287
c changes for better logging of mail submitters
e
s 00030/00002/01926
d D 6.30 93/02/28 09:24:03 eric 287 286
c log actual delivery host
e
s 00001/00001/01927
d D 6.29 93/02/28 08:52:20 eric 286 285
c don't send errors to <>
e
s 00001/00001/01927
d D 6.28 93/02/27 11:56:44 eric 285 284
c fix a problem in owner- stuff that "loses" data files
e
s 00004/00003/01924
d D 6.27 93/02/26 08:19:32 eric 284 283
c better handling of transient errors
e
s 00000/00001/01927
d D 6.26 93/02/24 10:19:34 eric 283 282
c fix yet another problem with new owner-foo implementation
e
s 00144/00040/01784
d D 6.25 93/02/24 05:36:54 eric 282 281
c propagate alias owner information back to envelope sender
e
s 00001/00001/01823
d D 6.24 93/02/23 08:59:59 eric 281 280
c more System V compatibility changes (ugh)
e
s 00017/00021/01807
d D 6.23 93/02/23 06:31:50 eric 280 279
c overhaul status of SMTP reply codes
e
s 00009/00005/01819
d D 6.22 93/02/22 17:02:51 eric 279 278
c don't go into queue mode when you want verify mode
e
s 00002/00002/01822
d D 6.21 93/02/21 15:52:37 eric 278 277
c M_LOCAL => M_LOCALMAILER to avoid conflict with Ultrix <sys/mount.h>
e
s 00003/00000/01821
d D 6.20 93/02/21 09:53:21 eric 277 276
c try to catch exec problem with automounter
e
s 00019/00002/01802
d D 6.19 93/02/20 13:46:44 eric 276 275
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00000/00008/01804
d D 6.18 93/02/19 16:15:06 eric 275 274
c let HPUX use initgroups; -DHASINITGROUPS if you have one
e
s 00015/00008/01797
d D 6.17 93/02/18 20:22:35 eric 274 273
c move the meta-characters from C0 into C1 space
e
s 00007/00005/01798
d D 6.16 93/02/16 18:30:07 eric 273 272
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00002/00002/01801
d D 6.15 93/02/14 14:41:40 eric 272 271
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00001/00000/01802
d D 6.14 93/02/12 11:51:26 eric 271 270
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00008/00000/01794
d D 6.13 93/01/28 10:15:51 eric 270 269
c System 5 compatibility, misc fixes
e
s 00025/00000/01769
d D 6.12 93/01/26 11:36:35 eric 269 268
c some (iffy) changes to prevent suppressing the actual sender
c during a queue run (interaction with C line in qf file)
e
s 00002/00000/01767
d D 6.11 93/01/25 15:04:15 eric 268 267
c log all instances of setting stat to EX_INTERNAL (Internal error)
e
s 00001/00000/01766
d D 6.10 93/01/21 15:18:48 eric 267 266
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00009/00007/01757
d D 6.9 93/01/18 14:32:25 eric 266 265
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00004/00001/01760
d D 6.8 93/01/13 18:38:15 eric 265 264
c environment handling simplification/bug fix; handle commas inside
c comments; properly limit large messages in -obq mode
e
s 00002/00003/01759
d D 6.7 93/01/10 13:23:41 eric 264 263
c change checkcompat() to return an exit status
e
s 00138/00034/01624
d D 6.6 93/01/10 12:56:51 eric 263 262
c MX piggybacking, based on code from John Myers@CMU; allow checkcompat
c to return -1 to mean tempfail; bug fix in m_mno computation
e
s 00005/00003/01653
d D 6.5 93/01/10 09:50:16 eric 262 261
c let checkcompat return -1 to indicate temporary failure
e
s 00007/00002/01649
d D 6.4 93/01/09 14:45:38 eric 261 260
c tuning of queueing functions as recommended by John Gardiner Myers
c <jgm+@CMU.EDU>; return mail headers (no body) on messages with negative
c precedence; minor other bug fixes
e
s 00006/00009/01645
d D 6.3 93/01/02 14:00:07 eric 260 259
c changes to recognize special mailer types (e.g., file) early
e
s 00020/00000/01634
d D 6.2 93/01/01 13:09:26 eric 259 258
c debugging information (print MCI structure)
e
s 00000/00000/01634
d D 6.1 92/12/21 16:08:47 eric 258 257
c Release 6
e
s 00000/00001/01634
d D 5.67 92/12/20 11:14:23 eric 257 256
c change random constants to be #defines
e
s 00010/00010/01625
d D 5.66 92/11/14 11:34:31 eric 256 255
c (partially) ANSI-fy it
e
s 00003/00001/01632
d D 5.65 92/11/04 12:14:58 eric 255 254
c fix a variety of small bugs noticed by bcx
e
s 00001/00001/01632
d D 5.64 92/07/14 13:09:03 eric 254 253
c fix "user open" setproctitle message
e
s 00001/00001/01632
d D 5.63 92/07/14 13:06:54 eric 253 252
c fix from address on "too many hops" message
e
s 00001/00000/01632
d D 5.62 92/07/13 16:27:47 eric 252 251
c miscellaneous changes to improve logging and messages
e
s 00000/00002/01632
d D 5.61 92/07/12 14:39:11 eric 251 250
c lint
e
s 00008/00008/01626
d D 5.60 92/07/12 14:09:52 eric 250 249
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00004/00002/01630
d D 5.59 92/07/12 11:57:42 eric 249 248
c child pid not getting changed; \quoted names were still forwarded
e
s 00002/00007/01630
d D 5.58 92/07/12 10:14:14 eric 248 247
c make eight-bit clean; backslashes are carried through as-is
e
s 00292/00285/01345
d D 5.57 92/07/11 18:51:48 eric 247 246
c open connection caching
e
s 00023/00008/01607
d D 5.56 92/05/31 13:51:22 eric 246 244
i 245 243
c checkpoint: putting in connection caching
e
s 00020/00012/01587
d D 5.54.1.2 92/05/29 10:55:05 eric 245 243
c more connection caching hacks
e
s 00014/00006/01590
d D 5.55 92/05/25 15:53:08 eric 244 242
c ignore setuid bits on files if address was passed through a .forward
c or :include: file -- this avoids a security problem that comes up
c with System V Release 4, reported by Dave Borman
e
s 00061/00058/01538
d D 5.54.1.1 92/02/26 14:05:04 eric 243 242
c partial hooks for caching all email connections; won't work
c because it could result in too many connections, and some could
c time out.
e
s 00024/00007/01572
d D 5.54 92/02/26 06:57:58 eric 242 241
c check I/O status when appending to files
e
s 00006/00018/01573
d D 5.53 92/01/05 09:21:41 eric 241 240
c clean up #ifdef configuration to more cleanly match the modern age
e
s 00014/00009/01577
d D 5.52 92/01/04 15:33:18 eric 240 239
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00020/00007/01566
d D 5.51 91/12/15 13:59:46 eric 239 238
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00009/00008/01564
d D 5.50 91/12/14 19:39:42 eric 238 237
c convert lockf implementation to use fcntl directly
e
s 00011/00025/01561
d D 5.49 91/12/14 12:36:56 eric 237 236
c fix race condition in queue file locking; generalize getla
e
s 00031/00015/01555
d D 5.48 91/12/13 12:54:59 eric 236 235
c change lockf code to avoid race condition
e
s 00026/00000/01544
d D 5.47 91/12/13 12:13:18 eric 235 233
c fix lockf code; have getcanonname recognize canonical names
e
s 00023/00000/01544
d R 5.47 91/12/13 12:09:32 eric 234 233
c fix lockf code; have getcanonname recognize canonical names
e
s 00012/00004/01532
d D 5.46 91/12/05 17:50:15 eric 233 232
c hacks for systems with lockf, not flock
e
s 00001/00001/01535
d D 5.45 91/10/11 12:46:08 eric 232 231
c fixes for user database and new config files
e
s 00004/00002/01532
d D 5.44 91/10/05 10:05:02 eric 231 230
c if config level >=2, don't reset RES_DEFNAMES|RES_DNSRCH
e
s 00002/00002/01532
d D 5.43 91/10/03 14:39:01 eric 230 229
c some changes to enhance compatibility with SunOS sendmail
e
s 00008/00001/01526
d D 5.42 91/07/25 07:47:40 eric 229 228
c fix botch in file locking when checkpoints kick in
e
s 00001/00000/01526
d D 5.41 91/03/21 11:49:11 bostic 228 227
c <arpa/nameser.h> needs <sys/param.h> for endian stuff
e
s 00022/00004/01504
d D 5.40 91/03/12 17:31:06 eric 227 226
c k option specifies checkpoint interval (default 10);
c qf file is rewritten after k successful deliveries.
c (ref bug 4.3BSD-reno/usr.bin/10)
e
s 00002/00000/01506
d D 5.39 91/03/02 17:15:18 bostic 226 225
c ANSI
e
s 00001/00011/01505
d D 5.38 90/06/01 19:01:15 bostic 225 224
c new copyright notice
e
s 00001/00001/01515
d D 5.37 90/05/30 10:05:12 bostic 224 223
c unsigned sizeof test < 0; bug report 4.3BSD/usr.lib/156
e
s 00002/00000/01514
d D 5.36 90/04/24 12:24:14 eric 223 222
c don't change semantics of uid setting for local mail delivery; this
c would require a .cf file change
e
s 00002/00001/01512
d D 5.35 90/04/19 17:01:43 bostic 222 221
c disk error check, case-insensitive list-owner lookup
c bug report 4.3BSD-tahoe/usr.sbin/13
e
s 00001/00001/01512
d D 5.34 90/04/19 16:59:09 bostic 221 220
c don't prepend a '>' to "From:" lines; bug report 4.3BSD-tahoe/usr.sbin/12
e
s 00004/00001/01509
d D 5.33 90/04/19 16:44:48 bostic 220 219
c fdopens are wrong; bug report 4.3BSD/usr.lib/137
e
s 00003/00003/01507
d D 5.32 90/04/19 10:01:39 bostic 219 218
c uninitialized file pointers
e
s 00011/00004/01499
d D 5.31 90/04/18 13:53:28 bostic 218 217
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00001/00001/01502
d D 5.30 90/04/18 12:15:27 bostic 217 216
c don't break old makefiles; bug report 4.3BSD/usr.lib/114
e
s 00030/00005/01473
d D 5.29 90/04/16 08:08:42 rick 216 215
c fix bug in delivering to files where can't read dfAA*
c (open file before setuid)
c new queue locking code based around flock()
e
s 00002/00002/01476
d D 5.28 89/02/16 16:26:21 bostic 215 214
c SMTP does not imply IPC; bug report 4.3BSD-tahoe/usr.lib/6
e
s 00009/00002/01469
d D 5.27 89/02/15 11:50:05 bostic 214 213
c #ifdef h_errno on NAMED_BIND
e
s 00000/00014/01471
d D 5.26 89/01/01 17:17:02 bostic 213 212
c remove DEBUG
e
s 00003/00003/01482
d D 5.25 88/11/18 17:34:54 karels 212 211
c fix buffer handling botch for logging "to" addresses to same
c destination host (4.3BSD usr.lib/113)
e
s 00006/00003/01479
d D 5.24 88/10/22 13:49:06 bostic 211 210
c use F_SETFD instead of FIOCLEX; F_SETFD is in S3/S5, and we're not
c real concerned about V6/V7/4.1BSD anymore
e
s 00021/00005/01461
d D 5.23 88/09/20 22:15:11 eric 210 209
c add I option to insist on Internet domain server; add NAMED_BIND
c compile option to compile in named routines.
e
s 00011/00009/01455
d D 5.22 88/06/30 14:58:40 bostic 209 208
c install approved copyright notice
e
s 00001/00010/01463
d D 5.21 88/05/05 12:40:12 bostic 208 207
c remove ifdef's on FIOCLEX; never got turned on since sys/ioctl.h
c wasn't included
e
s 00046/00030/01427
d D 5.20 88/04/19 13:45:58 bostic 207 206
c unless interactive, don't pound name server; restructure getmxrr logic
c fix "Connecting to" messages
e
s 00005/00005/01452
d D 5.19 88/04/01 16:36:34 bostic 206 205
c if get MX record, note what site we're *really* connecting too
e
s 00022/00044/01435
d D 5.18 88/04/01 15:36:45 bostic 205 204
c map certain errors in getmxrr; minor speedup/cleanup
e
s 00000/00006/01479
d D 5.17 88/03/24 09:00:08 bostic 204 203
c MXDOMAIN is always in place
e
s 00016/00010/01469
d D 5.16 88/03/13 19:51:48 bostic 203 202
c add Berkeley specific header
e
s 00001/00001/01478
d D 5.15 87/12/12 17:29:28 bostic 202 201
c add h_errno as an extern
e
s 00007/00001/01472
d D 5.14 87/07/27 17:08:10 bostic 201 200
c bug report 4.3BSD/usr.lib/50; fix user@[a.b.c.d]
e
s 00001/00001/01472
d D 5.13 86/10/23 10:10:58 eric 200 199
c Fix security bug allowing writing to arbitrary files; from Bart Miller
c at U. Wisconsin.
e
s 00011/00011/01462
d D 5.12 86/10/14 17:25:09 eric 199 198
c make global variables begin with cap letters -- Please!!
e
s 00000/00000/01473
d D 5.11 86/07/21 11:21:19 bloom 198 195
i 197 196
c MX branch merge
e
s 00023/00030/01450
d D 5.10.1.2 86/07/21 11:06:34 bloom 197 196
c clean up code a bit, move MX query, getmxrr is smarter
e
s 00055/00021/01425
d D 5.10.1.1 86/07/01 15:17:03 bloom 196 195
c add Name Server MX support from satz@su-sierra.arpa, fix macro usage
e
s 00006/00000/01440
d D 5.10 86/03/02 14:05:41 eric 195 194
c always ignore SIGCHLD in openmailer; get SccsId correct in alias.c
e
s 00001/00001/01439
d D 5.9 85/12/17 23:53:29 eric 194 193
m 
c lint
e
s 00016/00005/01424
d D 5.8 85/11/22 11:31:05 miriam 193 192
m 
c Call errstring() to print out Name Server error code TRY_AGAIN message -
c "Host Name Lookup Failure".
e
s 00006/00000/01423
d D 5.7 85/09/30 21:34:19 eric 192 191
m 
c clean up some aspects of error message display
e
s 00001/00001/01422
d D 5.6 85/09/24 15:09:43 eric 191 190
m 
c don't step on user environment
e
s 00029/00007/01394
d D 5.5 85/09/19 00:45:16 eric 190 189
m 
c SMI changes (somewhat)
e
s 00003/00002/01398
d D 5.4 85/06/16 16:03:41 eric 189 188
m 
c arrange for a useful error message if the mailer fork fails
e
s 00004/00004/01396
d D 5.3 85/06/08 00:15:07 eric 188 187
m 
c lint
e
s 00000/00002/01400
d D 5.2 85/06/07 22:05:38 miriam 187 186
m 
c Resolve duplicate SccsId
e
s 00014/00000/01388
d D 5.1 85/06/07 14:40:15 dist 186 185
m 
c Add copyright
e
s 00017/00001/01371
d D 4.10 85/05/24 10:58:08 eric 185 184
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00004/00001/01368
d D 4.9 84/08/11 17:55:46 eric 184 183
m 
c changes from Tom Ferrin <ucsfcgl!tef>: don't drop messages on the floor
c if no local mailer available; give real "errno" message in syserr.
e
s 00002/00002/01367
d D 4.8 84/08/11 16:51:02 eric 183 182
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00005/00000/01364
d D 4.7 84/08/11 13:22:27 eric 182 181
m 
c E flag will > escape From lines (for files)
e
s 00010/00011/01354
d D 4.6 84/03/11 16:53:44 eric 181 180
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00013/00020/01352
d D 4.5 83/12/27 22:51:03 eric 180 179
m 
c don't close files immediately before exec of mailer so that we can log;
c use FIOCLEX instead.  Suggested by Tom Ferrin, UCSF CGL.
e
s 00001/00001/01371
d D 4.4 83/11/13 18:07:10 eric 179 178
m 
c Fixes two nasty problems, both pointed out by Bill Nowicki at Stanford:
c I/O errors on input in collect would cause infinite loops, and a protocol
c error (or other error that would call smtpquit abnormally) would cause
c core dumps
e
s 00003/00012/01369
d D 4.3 83/10/01 16:57:09 eric 178 177
m 
c clean up error handling in general; make sure that something gets logged
c in the transcript if the connection cannot be established; clean up Teus
c Hagen's mod to arpadate.c to match the sendmail coding style.
e
s 00013/00001/01368
d D 4.2 83/08/28 14:44:04 eric 177 176
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00000/00000/01369
d D 4.1 83/07/25 19:44:34 eric 176 175
m 
c 4.2 release version
e
s 00003/00001/01366
d D 3.154 83/05/20 11:46:44 eric 175 174
m 238
m 239
c Don't stack processes when VRFY fails.
c Give an error message on multiple RCPT commands with a bad address.
e
s 00001/00001/01366
d D 3.153 83/05/04 11:29:05 eric 174 173
m 235
c fix botch in 3.338 -- arguments reversed
e
s 00010/00010/01357
d D 3.152 83/05/04 11:15:42 eric 173 172
m 235
c Don't send domain-based UUCP addresses to UGLYUUCP hosts
e
s 00005/00001/01362
d D 3.151 83/04/30 15:13:14 eric 172 171
m 
c lint
e
s 00003/00000/01360
d D 3.150 83/04/17 17:14:45 eric 171 170
m 221
c fix bogus errno problems
e
s 00011/00000/01349
d D 3.149 83/02/20 12:28:40 eric 170 169
m 190
c Avoid loops in the auto-closedown code
e
s 00007/00000/01342
d D 3.148 83/02/03 07:53:34 eric 169 168
m 168
c Make mailer size limits a per-mailer parameter (M field in the mailer
c descriptor)
e
s 00010/00010/01332
d D 3.147 83/02/02 12:51:59 eric 168 167
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00009/00014/01333
d D 3.146 83/01/15 17:39:59 eric 167 166
m 149
c be sure everything gets appropriately externalized; canonname goes away,
c since everything is now done by remotename
e
s 00023/00033/01324
d D 3.145 83/01/06 10:44:19 eric 166 165
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00001/00000/01356
d D 3.144 83/01/04 19:53:04 eric 165 164
m 
c externalize $g macro using ruleset 4 also
e
s 00001/00001/01355
d D 3.143 83/01/04 18:51:46 eric 164 163
m 
c Don't try to drop our controlling TTY except when we are starting up a
c daemon; this can cause UUCP jobs to hang waiting for carrier on a dialin
c line (completely contrary to the intent).  Many thanks to Keith Sklower
c for pointing this one out.  However, that damned parameter to disconnect()
c has reappeared!
e
s 00000/00004/01356
d D 3.142 83/01/04 17:44:48 eric 163 162
m 
c Ignore SIGPIPE early (in main rather than in deliver) so that rude hosts
c that close the connection early don't cause us to die -- in particular,
c CMU-CS-A (nee CMU-10A) was doing this after the DATA command; the problem
c went away quite mysteriously, so I have no idea why it happened
e
s 00013/00006/01347
d D 3.141 83/01/04 13:10:04 eric 162 161
m 
c change format of deferred message to be consistent with other messages
e
s 00037/00010/01316
d D 3.140 83/01/03 18:00:50 eric 161 160
m 
c give more useful error messages (including the errno that caused
c a temporary failure); reflect these messages out to mailq
e
s 00041/00010/01285
d D 3.139 83/01/03 13:01:18 eric 160 159
m 
c process timeouts like normal errors, so that they will get delivered to
c the correct address (i.e., the Errors-To: address)
e
s 00016/00013/01279
d D 3.138 83/01/01 21:24:54 eric 159 158
m 123
c Put CRLF on all lines in user SMTP.  Pass this info down to
c innumerable routines.
e
s 00002/00002/01290
d D 3.137 82/12/13 18:23:45 eric 158 157
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00028/00012/01264
d D 3.136 82/12/05 13:44:25 eric 157 156
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00045/00030/01231
d D 3.135 82/11/28 16:00:05 eric 156 155
m 
c implement SMTP auto-shutdown on 421 codes; clean up some error processing
c items, particularly in SMTP; don't reinstantiate error message bodies after
c queueing; other minor changes.  This is all cleanup from 3.253.
e
s 00001/00001/01260
d D 3.134 82/11/28 10:21:48 eric 155 154
m 
c fix a number of problems left over from yesterday's delta.  The big
c triumph is being able to delete the parameter from disconnect().
e
s 00154/00456/01107
d D 3.133 82/11/28 00:18:36 eric 154 153
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00000/00058/01563
d D 3.132 82/11/24 18:43:20 eric 153 152
m 
c lint it
e
s 00020/00047/01601
d D 3.131 82/11/24 17:14:10 eric 152 151
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00017/00010/01631
d D 3.130 82/11/18 08:55:49 eric 151 150
m 060,
m 073
c disconnect input, output, signals, etc. when running in background
e
s 00071/00009/01570
d D 3.129 82/11/17 09:34:19 eric 150 149
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00004/00000/01575
d D 3.128 82/11/14 15:13:17 eric 149 148
m 074
c fix quote processing on program mailers
e
s 00006/00006/01569
d D 3.127 82/11/13 17:58:25 eric 148 147
m 021
c #ifdef VFORK => #ifdef VMUNIX
e
s 00002/00002/01573
d D 3.126 82/11/07 16:13:47 eric 147 146
m 041
c make all mailer output go to the transcript if running server smtp; this
c has the effect of making some significant changes in the output structure
c to handle such things as -em and -as together
e
s 00009/00003/01566
d D 3.125 82/11/03 09:48:09 eric 146 145
m 049
c Arrange to strip quote bits in message header; move SPACESUB into
c conf.c; change SpaceSub to unquoted dot
e
s 00001/00001/01568
d D 3.124 82/10/25 08:22:55 eric 145 144
m 040
c Don't send closing protocol to SMTP if you haven't opened the
c connection; this happens if checkcompat fails on the only recipient.
e
s 00001/00001/01568
d D 3.123 82/10/16 13:43:00 eric 144 143
m 024
c Fix debug statement in sendall
e
s 00030/00010/01539
d D 3.122 82/10/11 09:50:59 eric 143 142
m 016
c have auto-queueups print a polite message in the log (rather than an
c obnoxious "Temporary Failure").  Adds a new routine "logdelivery".
e
s 00002/00000/01547
d D 3.121 82/10/09 19:06:05 eric 142 141
m 002
c Handle Reverse-Path in some reasonable way.  You must put the 'X'
c flag (M_FULLSMTP) in the local mailer's flags to get this line.
e
s 00009/00004/01538
d D 3.120 82/10/09 18:10:46 eric 141 140
m 013
c print a status indication when a message is autoqueued, either from
c a -bq flag or a NoConnect
e
s 00002/00001/01540
d D 3.119 82/10/09 17:21:58 eric 140 139
m 008
c Force -v override of deferred connect
e
s 00001/00001/01540
d D 3.118 82/10/09 17:10:12 eric 139 138
m 004
c Only put the "from" person on the error queue if an error actually
c occured -- prevents many "duplicate supressed" messages, etc.
e
s 00002/00000/01539
d D 3.117 82/09/26 14:45:15 eric 138 137
c completely instantiate queue files for all mail, even if not needed;
c fix a bug that would probably come up once every ten years in creating
c the queue id.  should merge argv flag processing with option processing.
e
s 00024/00004/01515
d D 3.116 82/09/24 09:37:35 eric 137 136
c arrange to be able to define options; put precedences in .cf file;
c send errors to an Errors-To: field; fix a serious bug causing mail
c to not be delivered to anyone if there were any errors.
e
s 00008/00003/01511
d D 3.115 82/09/21 10:08:39 eric 136 135
c output headers with commas into the queue
e
s 00005/00001/01509
d D 3.114 82/09/16 20:23:49 eric 135 134
c drop ":...;" stuff -- it screws it up aliases; pass parameters to
c subroutines (this also adds $@ and $: features to subr calls); check
c overflow of "tobuf" on smtp deliveries, which caused core dumps on
c large mailing lists
e
s 00002/00003/01508
d D 3.113 82/09/12 16:42:42 eric 134 133
c change inheritance for macros in envelopes; be able to canonicalize
c non-domained names by appending domain from sender; call ruleset 3
c explicitly before doing other rulesets; some general cleanup.
e
s 00001/00003/01510
d D 3.112 82/09/08 23:55:12 eric 133 132
c fix stupid bug in wait code to dispose of "Interrupted system call" message
e
s 00007/00002/01506
d D 3.111 82/09/08 21:18:40 eric 132 131
c try to avoid "Interrupted system call" on wait in deliver and on
c writes; fix returned message to have proper sender; handle extra
c mailer output more cleverly.
e
s 00005/00001/01503
d D 3.110 82/09/06 19:54:45 eric 131 130
c more hacking on oldstyle -- always assume sender fields are in new
c style so that locally generated fields are edited correctly.
e
s 00001/00001/01503
d D 3.109 82/09/06 18:46:57 eric 130 129
c fix botch in "at"s in headers
e
s 00009/00023/01495
d D 3.108 82/09/06 16:23:52 eric 129 128
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00030/00067/01488
d D 3.107 82/09/05 18:02:57 eric 128 127
c change from m_from (macro from rewrite) to using a pair of rewriting
c rules; convert Return-Receipt-To: and Precedence: to NBS standard;
c correctly process all sender fields
e
s 00022/00029/01533
d D 3.106 82/08/31 10:05:16 eric 127 126
c clean up reply code processing some more; in particular, give more
c detail in many messages.  process connection failures correctly.
e
s 00011/00001/01551
d D 3.105 82/08/29 23:31:10 eric 126 125
c handle comments and quotes in headers; still doesn't deal with
c backslashes however -- prescan should be cleaned up to deal with
c this case.  it turns out there are many bugs in prescan; it should
c be extensively rewritten.
e
s 00003/00001/01549
d D 3.104 82/08/29 16:52:04 eric 125 124
c do a better job at interpreting SMTP reply codes
e
s 00001/00001/01549
d D 3.103 82/08/25 11:20:31 eric 124 123
c clean up time manipulation to always be current; assign job
c id's earlier to make sure there is always one with a message.
e
s 00004/00006/01546
d D 3.102 82/08/24 19:40:59 eric 123 122
c log more info (on log level 11); try to detect wild accept loops;
c some minor cleanup and debugging checks; fix NoConnect option to;
c only apply to expensive mailers (regardless of sendqueue order)
e
s 00009/00002/01543
d D 3.101 82/08/23 11:58:54 eric 122 121
c clean up queueing; log time in queue.
c **** This delta invalidates mqueue files ****
e
s 00011/00004/01534
d D 3.100 82/08/22 19:02:10 eric 121 120
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00005/00000/01533
d D 3.99 82/08/17 16:06:55 eric 120 119
c fix verify mode (only worked in verbose mode)
e
s 00140/00108/01393
d D 3.98 82/08/15 11:55:04 eric 119 118
c split off "commaize()" routine; fix bug that caused garbage in headers
e
s 00001/00092/01500
d D 3.97 82/08/08 16:54:40 eric 118 117
c move remotename() to parse.c; log errors at a higher level than successes
e
s 00012/00019/01580
d D 3.96 82/08/08 01:01:12 eric 117 116
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00034/00006/01565
d D 3.95 82/08/07 11:12:38 eric 116 115
c Fix address rewriting so that multiple spaces and tabs work properly
e
s 00002/00001/01569
d D 3.94 82/07/05 20:54:39 eric 115 114
c improve debugging: flush transcript before doing things that might
c take a long time; add some info to debugging output
e
s 00003/00001/01567
d D 3.93 82/07/02 09:43:06 eric 114 113
c take special care in outputing error messages to the transcript;
c a little bit of paranoia never hurt a mail system.
e
s 00002/00009/01566
d D 3.92 82/06/26 14:53:12 eric 113 112
c clean up error messages on SMTP temporary failures resulting from
c failure to connect properly.
e
s 00006/00005/01569
d D 3.91 82/06/26 13:09:59 eric 112 111
c lint
e
s 00004/00000/01570
d D 3.90 82/06/23 12:10:50 eric 111 110
c check prescan return values in remotename
e
s 00001/00001/01569
d D 3.89 82/06/19 21:13:54 eric 110 109
c remember to put a newline at the end of the UGLYUUCP line
e
s 00003/00003/01567
d D 3.88 82/06/19 20:46:58 eric 109 108
c improve SMTP error reporting
e
s 00001/00001/01569
d D 3.87 82/06/16 14:29:26 eric 108 107
c fix botch in outputing "recipient" type lines (e.g., To:)
e
s 00029/00010/01541
d D 3.86 82/06/07 23:55:12 eric 107 106
c call the routine putline to output lines to mailers.  this lets us
c implement line length limits, etc. for full SMTP compatibility.
e
s 00029/00022/01522
d D 3.85 82/06/07 07:53:57 eric 106 105
c make transcripts verbose always; misc. message cleanup, etc.
e
s 00006/00022/01538
d D 3.84 82/06/07 07:05:52 eric 105 104
c strip out xlate stuff -- this belongs at a different level
e
s 00004/00001/01556
d D 3.83 82/06/06 23:13:16 eric 104 103
c avoid loops by not sending to owner-owner-* -- just send to
c owner-owner instead
e
s 00093/00012/01464
d D 3.82 82/06/06 23:04:17 eric 103 102
c implement alias owner feature.  this actually works for any user.
c basically, if the alias owner-xxx exists, errors sending to xxx will be
c sent to that alias rather than to the sender.
e
s 00015/00008/01461
d D 3.81 82/05/31 18:48:07 eric 102 101
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00002/00000/01467
d D 3.80 82/05/31 15:30:52 eric 101 99
i 100
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00118/00120/01349
d D 3.79.1.1 82/05/29 18:18:54 eric 100 99
c try to install envelopes.  is this really worth it???
e
s 00022/00022/01447
d D 3.79 82/05/22 01:36:18 eric 99 98
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00002/00002/01467
d D 3.78 82/05/20 17:44:59 eric 98 97
c add dfopen as a "determined fopen" -- it retries if it gets recoverable
c errors.  we use it for returning mail (to dead.letter) and creating the
c temp file.  the whole idea is to avoid dropping things on the floor on
c heavily loaded systems.  this is untested, since it seems impossible to
c fill up the inode or file tables on this VAX (but it works if the open
c succeeds).
e
s 00016/00007/01453
d D 3.77 82/05/15 12:29:09 eric 97 96
c add the 'R' flag to mailers, saying to rewrite the recipient addresses
c to be relative to the recipient.  This makes reply code easy, but
c confuses user mail programs that are expecting to have to rewrite
c recipient addresses.  In general, the receiving host must be "smart"
c for this to work.
e
s 00005/00001/01455
d D 3.76 82/05/06 20:20:42 eric 96 95
c allow socket number on [IPC] connections -- eventually this
c could be used to handle other low-level protocols.
e
s 00005/00000/01451
d D 3.75 82/03/27 20:14:43 eric 95 94
c delete neat remotename feature, because it doesn't work right in
c UUCPland -- and breaks stupid hosts.  'Twill be fixed, I promise.  Time
c must be spent figuring out how to define the civilized versus the
c uncivilized world.
e
s 00002/00005/01449
d D 3.74 82/03/20 16:11:51 eric 94 93
c 16 bit changes -- should have no effect on VAX binaries to
c speak of.
e
s 00037/00033/01417
d D 3.73 82/03/06 15:07:55 eric 93 92
c give correct error message in SMTP if some of the addresses are not ok
e
s 00007/00004/01443
d D 3.72 82/03/06 12:08:24 eric 92 91
c clean up error handling in IPC case; fix a minor bug in headers in
c queueing code; make SMTP mail multi user per connect.
e
s 00014/00005/01433
d D 3.71 82/03/05 10:44:50 eric 91 90
c remove silly $U dependency in UGLYUUCP code
e
s 00052/00001/01386
d D 3.70 82/03/05 10:12:04 eric 90 89
c include direct connect on outgoing mail if the pathname is "[IPC]" --
c this gives minimal number of processes for ethernet mail.
e
s 00063/00032/01324
d D 3.69 82/02/27 11:36:47 eric 89 88
c implement "return receipt requested".
e
s 00047/00003/01309
d D 3.68 82/02/22 19:31:06 eric 88 87
c be much mroe clever about splitting up addresses when doing header
c rewriting.
e
s 00016/00005/01296
d D 3.67 82/02/20 19:15:31 eric 87 86
c make rewriting of addresses in headers really work.  This adds the $q
c macro.  The rewriting of the From: address is still ad hoc and should
c be integrated into this format.
c Note:  old .cf files will not work with this version.
e
s 00132/00003/01169
d D 3.66 82/02/20 16:56:31 eric 86 85
c output names in a nice comma-separated fashion in messages -- this
c opens up other possibilities
e
s 00025/00003/01147
d D 3.65 82/02/20 12:09:03 eric 85 84
c implement -c flag: don't try to deliver expensive mail immediately
e
s 00000/00002/01150
d D 3.64 82/02/15 09:39:19 eric 84 83
c pass lint
e
s 00000/00003/01152
d D 3.63 82/02/04 20:29:21 eric 83 82
c add host aliasing; add -p flag.  this version doesn't yet know about
c replacing the text of the host alias into the message however.  syntax
c is grotty: "/hostmatch:%s@newhost" or whatever.
e
s 00002/00003/01153
d D 3.62 82/01/23 14:18:39 eric 82 81
c add M_UGLYUUCP flag; only catch filenames if the "/" is leading.
e
s 00005/00003/01151
d D 3.61 82/01/05 09:58:58 eric 81 80
c fix botch in UGLYUUCP code -- gave "remote from <dest>" instead of
c "remote from <source>"
e
s 00001/00001/01153
d D 3.60 81/12/06 12:37:31 eric 80 79
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00039/00009/01115
d D 3.59 81/12/05 11:52:58 eric 79 78
c put the SMTP and queueing code on compilation flags so that sendmail
c will fit on non-ID PDP-11's (ugh); put the ugly UUCP hack on a
c compilation flag also to emphasize that it sucks eggs; makefile
c cleanup.
e
s 00004/00001/01120
d D 3.58 81/11/27 21:47:43 eric 78 77
c make the trigger be stricter (path must end "/uux") so that mail
c forwarded to another machine will work right.  this delta should also
c be removed when the other goes.
e
s 00011/00001/01110
d D 3.57 81/11/27 21:36:44 eric 77 76
c this is a stupid hack to put "remote from <host>" lines on the From
c lines going to UUCP mail.  someday i hope to rip out this stupidity.
c it is triggered by any mailer named "uucp" -- it ought to be a special
c flag, but i refuse to legitimize antique hacky mistakes.
e
s 00027/00009/01084
d D 3.56 81/11/22 19:16:12 eric 76 75
c Edit queue control files when running queue (assuming there are still
c recipients left).  Also, modify the MsgPriority to be the absolute
c number (not the Priority: value); this allows us to include aging into
c the priority algorithm.
e
s 00013/00017/01080
d D 3.55 81/11/21 18:45:11 eric 75 73
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00003/00003/01094
d D 3.54.1.1 81/11/21 15:45:19 eric 74 73
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00001/00001/01096
d D 3.54 81/11/21 09:57:38 eric 73 72
c convert to SMTP draft 3
e
s 00196/00048/00901
d D 3.53 81/11/11 20:23:24 eric 72 71
c integrate user SMTP into sendmail itself.  If there is no $u arg
c in the mailer argument list, SMTP is run.  This can be used directly
c over the Ethernet or to any clever mailer.  We still need to edit
c spooled control files to remove recipients that have been successfully
c sent during queue processing.
e
s 00022/00010/00927
d D 3.52 81/10/31 22:11:41 eric 71 70
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00022/00000/00915
d D 3.51 81/10/27 12:24:27 eric 70 69
c experimental version combining queueing with daemon operation.
c I'm sure this doesn't work -- if only because the wait()s are funny.
e
s 00030/00008/00885
d D 3.50 81/10/26 14:21:25 eric 69 68
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00007/00007/00886
d D 3.49 81/10/23 19:37:01 eric 68 67
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00041/00000/00852
d D 3.48 81/10/19 22:26:26 eric 67 66
c implement SMTP mode -- doesn't support source routing or the
c HELP command, and doesn't give the correct code on VRFY or forwarding.
c Maybe someday....
e
s 00003/00001/00849
d D 3.47 81/10/12 10:04:01 eric 66 65
c throw in some "errno = 0;"'s to make syserr's more accurate;
c take any -f flag if debug mode and uid==euid.
e
s 00002/00002/00848
d D 3.46 81/10/08 22:55:19 eric 65 64
c ignore interrupts and hangups while calling mailer.
e
s 00032/00008/00818
d D 3.45 81/10/02 10:07:10 eric 64 63
c use ruleset 2 to rewrite names after the $g translate (to fix some
c forwarding problems; do a read check in putmessage (just in case
c the temp file disappeared); some general cleanup.
e
s 00064/00011/00762
d D 3.44 81/09/29 18:22:33 eric 63 62
c change processing of From: person; basically, this mod deletes the
c Original-From: line if redundant with the generated From: line, uses
c the Original-From: line for the From: line if possible, and a host of
c other such trivialities.
e
s 00001/00001/00772
d D 3.43 81/09/23 09:52:11 eric 62 61
c fix bug in file modes when mailing to files that didn't exist before;
c add an 'F' line to the .cf file that will read class entries from
c another file, given a scanf string to do the parsing.
e
s 00025/00008/00748
d D 3.42 81/09/20 10:56:23 eric 61 60
c be more careful in resetting uid
e
s 00007/00000/00749
d D 3.41 81/09/20 10:46:18 eric 60 59
c don't let a mailer ever execute as root (that should solve the
c security problems!) -- essentially just map root into someone else.
c Adds yet another configuration variable (should this be in the .cf file?
e
s 00002/00000/00747
d D 3.40 81/09/16 16:24:08 eric 59 58
c last delta was too paranoid -- this increases the number of
c cases that work (but is still safe -- I hope)
e
s 00024/00008/00723
d D 3.39 81/09/16 16:07:32 eric 58 57
c run as the user forwarding mail after a .forward operation;
c fix a bug in .forwarding that caused recursive expansion;
c restrict mail to programs, files, and with :include: for security
c reasons.
e
s 00001/00003/00730
d D 3.38 81/09/14 12:18:45 eric 57 56
c fix bug in mailers that only take one address at a time
e
s 00036/00007/00697
d D 3.37 81/09/12 15:48:28 eric 56 55
c change From: processing to reduce the number of Original-From:
c lines; change allocation of global variables.
e
s 00019/00002/00685
d D 3.36 81/09/07 14:12:21 eric 55 54
c fix up umask; allow setuid on files to take recipient owner;
c factor some configuration info into conf.c
e
s 00034/00016/00653
d D 3.35 81/09/06 19:47:51 eric 54 53
c cleanup, commenting, linting, etc.
e
s 00003/00002/00666
d D 3.34 81/09/06 12:13:19 eric 53 52
c return mail on error (ignore QDONTSEND)
e
s 00001/00001/00667
d D 3.33 81/09/06 10:27:01 eric 52 51
c fix botch in $u argument processing
e
s 00004/00001/00664
d D 3.32 81/08/31 21:21:12 eric 51 50
c collect mail statistics; change minor configuration
e
s 00000/00002/00665
d D 3.31 81/08/29 19:12:56 eric 50 49
c delete H_DELETE -- can be simulated with H_ACHECK
e
s 00011/00001/00656
d D 3.30 81/08/23 12:08:40 eric 49 48
c plug assorted security holes
e
s 00085/00024/00572
d D 3.29 81/08/22 20:33:17 eric 48 47
c drop into subprocess when delivering to a file so we can setuid(getuid())
e
s 00015/00001/00581
d D 3.28 81/08/22 17:51:48 eric 47 46
c Arrange to pull full name out of From line if found; includes
c Original-From: hacking (oh so ugly).  There's got to be a better way
c to do this...
e
s 00004/00001/00578
d D 3.27 81/08/22 14:33:50 eric 46 45
c fix UNIX From problem
e
s 00002/00002/00577
d D 3.26 81/08/21 18:17:54 eric 45 44
c drop M_FINAL, change some other defined constant names
e
s 00002/00005/00577
d D 3.25 81/08/20 15:13:18 eric 44 43
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00000/00242/00582
d D 3.24 81/08/20 14:33:30 eric 43 42
c split deliver.c and sendto.c
e
s 00004/00004/00820
d D 3.23 81/08/18 17:12:29 eric 42 41
c factor out ARPANET FTP reply codes into conf.c
e
s 00042/00028/00782
d D 3.22 81/08/18 16:46:37 eric 41 40
c convert to really do arpanet reply codes right (maybe)
e
s 00057/00003/00753
d D 3.21 81/08/18 11:38:34 eric 40 39
c allow :include: specs
e
s 00004/00023/00752
d D 3.20 81/08/12 13:09:55 eric 39 38
c ignore broken pipe signals, since some "mailers" may not want
c to read their input.
e
s 00004/00002/00771
d D 3.19 81/08/10 18:14:38 eric 38 37
c fix botch with $z macro that confused forwarding
e
s 00048/00045/00725
d D 3.18 81/08/10 16:55:55 eric 37 36
c totally rework aliasing scheme -- sucks when no DBM now,
c but works better for the usual case; fix some quoting problems
c (and how many did I add?); remove .mailer feature since .forward
c will simulate this happily
e
s 00028/00038/00742
d D 3.17 81/08/09 15:02:01 eric 36 35
c lint it
e
s 00041/00012/00739
d D 3.16 81/08/09 12:34:10 eric 35 34
c add private incoming mailers; add q_home field to ADDRESS struct;
c some general cleanup
e
s 00009/00005/00742
d D 3.15 81/08/08 16:08:15 eric 34 33
c efficiency hacks with QBADADDR and QGOODADDR; don't call
c mailer if nothing to send
e
s 00007/00001/00740
d D 3.14 81/08/08 15:04:46 eric 33 32
c implement blow-by-blow verbose mode
e
s 00002/00003/00739
d D 3.13 81/08/08 13:50:00 eric 32 31
c fix botch with returned messages
e
s 00010/00002/00732
d D 3.12 81/08/04 11:27:39 eric 31 30
c retry forks on failure
e
s 00001/00001/00733
d D 3.11 81/04/27 21:52:14 eric 30 29
c fix botch in |prog form
e
s 00005/00002/00729
d D 3.10 81/03/28 13:36:26 eric 29 28
c pass Full-Name field internally to do forwards correctly
e
s 00011/00047/00720
d D 3.9 81/03/28 12:02:23 eric 28 27
c put much more info in cf file (e.g., headers)
e
s 00002/00002/00765
d D 3.8 81/03/20 09:44:43 eric 27 26
c change name (again); from postbox to sendmail
e
s 00210/00201/00557
d D 3.7 81/03/12 10:56:47 eric 26 25
c merge letters to the same host into one message
e
s 00055/00157/00703
d D 3.6 81/03/11 10:45:16 eric 25 24
c general cleanup, esp. macro processor
e
s 00038/00059/00822
d D 3.5 81/03/09 13:21:16 eric 24 23
c first step at rewriting rules, etc.
e
s 00007/00007/00874
d D 3.4 81/03/07 16:59:02 eric 23 22
c change q_mailer to be index, not pointer
e
s 00005/00007/00876
d D 3.3 81/03/07 16:26:32 eric 22 20
c lint fixes
e
s 00004/00007/00876
d R 3.3 81/03/07 15:31:46 eric 21 20
c lint fixes
e
s 00027/00020/00856
d D 3.2 81/03/07 14:25:43 eric 20 19
c ----- delivermail ==> postbox -----
e
s 00200/00107/00676
d D 3.1 81/03/04 09:33:58 eric 19 18
c install fancy header stuff
e
s 00022/00016/00761
d D 2.6 81/02/28 11:50:18 eric 18 17
c install VAX mpx file logging
e
s 00003/00001/00774
d D 2.5 81/02/05 08:01:28 eric 17 16
c always issued a delivermail error message regardless of M_QUIET
e
s 00001/00001/00774
d D 2.4 81/01/08 18:18:30 eric 16 15
c convert to new log scheme
e
s 00017/00004/00758
d D 2.3 80/11/21 12:57:39 eric 15 14
c have right user & time come out for msgs
e
s 00002/00001/00760
d D 2.2 80/11/20 19:58:07 eric 14 12
c make dates be taken as date sent rather than date delivered
e
s 00012/00003/00758
d D 2.1.1.1 80/11/20 09:54:20 eric 13 12
c experimental save date technique
e
s 00000/00000/00761
d D 2.1 80/11/05 11:02:01 eric 12 11
c release 2
e
s 00009/00004/00752
d D 1.11 80/10/27 19:27:23 eric 11 10
c count & record message size
e
s 00004/00000/00752
d D 1.10 80/10/27 19:09:17 eric 10 9
c fix botch in SIGPIPE catching; map diagnostic to std out in mailers
e
s 00002/00002/00750
d D 1.9 80/10/26 16:50:14 eric 9 8
c exit => _exit in child
e
s 00002/00002/00750
d D 1.8 80/10/21 22:39:20 eric 8 7
c EX_UNAVAIL => EX_UNAVAILABLE
e
s 00003/00026/00749
d D 1.7 80/10/18 16:50:03 eric 7 6
c cleanup for dbm stuff: Error => Errors; move local host
c detection into parse; misc cleanup
e
s 00017/00000/00758
d D 1.6 80/10/17 13:41:57 mark 6 5
c uses dbm package for alias file to make it faster
e
s 00008/00008/00750
d D 1.5 80/10/11 18:11:31 eric 5 4
c cleanup to simplify configuration & fix minor bugs
e
s 00001/00105/00757
d D 1.4 80/08/02 13:48:34 eric 4 3
c cleaned up comments
e
s 00002/00000/00860
d D 1.3 80/07/25 22:03:11 eric 3 2
c add ID keywords
e
s 00000/00002/00860
d D 1.2 80/06/24 23:33:56 eric 2 1
c attempted fixes to quote problem(s)
e
s 00862/00000/00000
d D 1.1 80/06/23 08:23:47 eric 1 0
e
u
U
f b 
f i 
t
T
I 186
/*
I 209
D 490
 * Copyright (c) 1983 Eric P. Allman
E 490
I 490
 * Copyright (c) 1983, 1995 Eric P. Allman
E 490
E 209
D 203
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 203
I 203
D 341
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 341
I 341
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 341
 *
D 225
 * Redistribution and use in source and binary forms are permitted
D 209
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 209
I 209
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
E 225
I 225
 * %sccs.include.redist.c%
E 225
E 209
 */
E 203

#ifndef lint
D 203
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 203
I 203
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 203

E 186
I 1
D 44
# include <stdio.h>
# include <pwd.h>
E 44
D 205
# include <signal.h>
I 19
D 44
# include <ctype.h>
E 44
I 39
# include <errno.h>
I 55
D 69
# include <sys/types.h>
# include <sys/stat.h>
E 69
E 55
E 39
E 19
D 20
# include "dlvrmail.h"
E 20
I 20
D 27
# include "postbox.h"
E 27
I 27
# include "sendmail.h"
I 69
# include <sys/stat.h>
I 193
# include <netdb.h>
E 205
I 205
D 217
#include <sendmail.h>
E 217
I 217
#include "sendmail.h"
E 217
D 281
#include <sys/signal.h>
E 281
I 281
D 348
#include <signal.h>
E 348
E 281
D 326
#include <sys/stat.h>
E 326
I 208
D 211
#include <sys/ioctl.h>
E 211
E 208
D 486
#include <netdb.h>
E 486
I 211
D 303
#include <fcntl.h>
E 303
E 211
#include <errno.h>
I 359
D 364
#include <sys/wait.h>
E 364
E 359
I 210
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
I 228
D 257
#include <sys/param.h>
E 257
E 228
E 210
I 207
D 427
#include <arpa/nameser.h>
E 427
#include <resolv.h>
I 342

extern int	h_errno;
E 342
I 210
D 364
#endif
I 235
D 238
#ifdef LOCKF
#include <unistd.h>
#endif
E 238
E 235
E 210
E 207
E 205
E 193
E 69
E 27
E 20
D 117
# ifdef LOG
D 18
# include <log.h>
E 18
I 18
# include <syslog.h>
E 18
# endif LOG
E 117

I 359
#ifndef WEXITSTATUS
# define WEXITSTATUS(st)	(((st) >> 8) & 0377)
E 364
#endif

I 393
extern char	SmtpError[];

E 393
E 359
I 3
D 80
static char SccsId[] = "%W%	%G%";
E 80
I 80
D 187
SCCSID(%W%	%Y%	%G%);
E 80

E 187
E 3
/*
I 312
**  SENDALL -- actually send all the messages.
**
**	Parameters:
**		e -- the envelope to send.
**		mode -- the delivery mode to use.  If SM_DEFAULT, use
**			the current e->e_sendmode.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Scans the send lists and sends everything it finds.
**		Delivers any appropriate error messages.
**		If we are running in a non-interactive mode, takes the
**			appropriate action.
*/

I 467
void
E 467
sendall(e, mode)
	ENVELOPE *e;
	char mode;
{
	register ADDRESS *q;
	char *owner;
	int otherowners;
D 408
	register ENVELOPE *ee;
	ENVELOPE *splitenv = NULL;
E 408
I 317
D 478
	bool announcequeueup;
E 478
I 449
	bool oldverbose = Verbose;
I 478
	bool somedeliveries = FALSE;
E 478
	int pid;
I 452
D 467
	char *qid;
E 467
I 467
	extern void sendenvelope();
E 467
E 452
E 449
E 317
I 314
	int pid;
#ifdef LOCKF
	struct flock lfd;
#endif
E 314

I 338
D 344
	if (bitset(EF_FATALERRS, e->e_flags))
E 344
I 344
	/*
	**  If we have had global, fatal errors, don't bother sending
	**  the message at all if we are in SMTP mode.  Local errors
	**  (e.g., a single address failing) will still cause the other
	**  addresses to be sent.
	*/

D 401
	if (bitset(EF_FATALERRS, e->e_flags) && OpMode == MD_SMTP)
E 401
I 401
	if (bitset(EF_FATALERRS, e->e_flags) &&
	    (OpMode == MD_SMTP || OpMode == MD_DAEMON))
E 401
E 344
	{
D 344
		/* this will get a return message -- so don't send it */
E 344
		e->e_flags |= EF_CLRQUEUE;
		return;
	}

E 338
	/* determine actual delivery mode */
I 379
	CurrentLA = getla();
E 379
	if (mode == SM_DEFAULT)
	{
D 337
		extern bool shouldqueue();

E 337
		mode = e->e_sendmode;
		if (mode != SM_VERIFY &&
		    shouldqueue(e->e_msgpriority, e->e_ctime))
			mode = SM_QUEUE;
I 317
D 478
		announcequeueup = mode == SM_QUEUE;
E 478
E 317
	}
I 317
D 478
	else
		announcequeueup = FALSE;
E 478
E 317

	if (tTd(13, 1))
	{
I 478
		extern void printenvflags();

E 478
D 354
		printf("\nSENDALL: mode %c, e_from ", mode);
E 354
I 354
		printf("\n===== SENDALL: mode %c, id %s, e_from ",
			mode, e->e_id);
E 354
		printaddr(&e->e_from, FALSE);
I 478
		printf("\te_flags = ");
		printenvflags(e);
E 478
		printf("sendqueue:\n");
		printaddr(e->e_sendqueue, TRUE);
	}

	/*
	**  Do any preprocessing necessary for the mode we are running.
	**	Check to make sure the hop count is reasonable.
	**	Delete sends to the sender in mailing lists.
	*/

	CurEnv = e;

	if (e->e_hopcount > MaxHopCount)
	{
		errno = 0;
I 460
D 478
		queueup(e, TRUE, announcequeueup);
E 478
I 478
		queueup(e, TRUE, mode == SM_QUEUE);
E 478
E 460
I 415
		e->e_flags |= EF_FATALERRS|EF_PM_NOTIFY|EF_CLRQUEUE;
E 415
D 363
		syserr("554 too many hops %d (%d max): from %s, to %s",
E 363
I 363
D 491
		syserr("554 too many hops %d (%d max): from %s via %s, to %s",
E 491
I 491
		syserr("554 Too many hops %d (%d max): from %s via %s, to %s",
E 491
E 363
			e->e_hopcount, MaxHopCount, e->e_from.q_paddr,
D 363
			e->e_sendqueue->q_paddr);
E 363
I 363
D 407
			RealHostName, e->e_sendqueue->q_paddr);
E 407
I 407
			RealHostName == NULL ? "localhost" : RealHostName,
			e->e_sendqueue->q_paddr);
I 491
		e->e_sendqueue->q_status = "5.4.6";
E 491
E 407
E 363
		return;
	}

D 327
	if (!MeToo)
E 327
I 327
	/*
	**  Do sender deletion.
	**
	**	If the sender has the QQUEUEUP flag set, skip this.
	**	This can happen if the name server is hosed when you
	**	are trying to send mail.  The result is that the sender
	**	is instantiated in the queue as a recipient.
	*/

D 350
	if (!MeToo && !bitset(QQUEUEUP, e->e_from.q_flags))
E 350
I 350
	if (!bitset(EF_METOO, e->e_flags) &&
	    !bitset(QQUEUEUP, e->e_from.q_flags))
E 350
E 327
	{
D 337
		extern ADDRESS *recipient();

E 337
		if (tTd(13, 5))
		{
			printf("sendall: QDONTSEND ");
			printaddr(&e->e_from, FALSE);
		}
		e->e_from.q_flags |= QDONTSEND;
D 455
		(void) recipient(&e->e_from, &e->e_sendqueue, e);
E 455
I 455
		(void) recipient(&e->e_from, &e->e_sendqueue, 0, e);
E 455
	}

I 314
# ifdef QUEUE
	if ((mode == SM_QUEUE || mode == SM_FORK ||
	     (mode != SM_VERIFY && SuperSafe)) &&
	    !bitset(EF_INQUEUE, e->e_flags))
	{
		/* be sure everything is instantiated in the queue */
		queueup(e, TRUE, mode == SM_QUEUE);
	}
#endif /* QUEUE */

	switch (mode)
	{
	  case SM_VERIFY:
		Verbose = TRUE;
		break;

	  case SM_QUEUE:
  queueonly:
		e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
		return;

	  case SM_FORK:
		if (e->e_xfp != NULL)
			(void) fflush(e->e_xfp);

# ifdef LOCKF
		/*
		**  Since lockf has the interesting semantic that the
		**  lock is lost when we fork, we have to risk losing
		**  the lock here by closing before the fork, and then
		**  trying to get it back in the child.
		*/

		if (e->e_lockfp != NULL)
		{
			(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
			e->e_lockfp = NULL;
		}
# endif /* LOCKF */

		pid = fork();
		if (pid < 0)
		{
			goto queueonly;
		}
		else if (pid > 0)
		{
			/* be sure we leave the temp files to our child */
			e->e_id = e->e_df = NULL;
# ifndef LOCKF
			if (e->e_lockfp != NULL)
			{
				(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
				e->e_lockfp = NULL;
			}
# endif

			/* close any random open files in the envelope */
			if (e->e_dfp != NULL)
			{
				(void) xfclose(e->e_dfp, "sendenvelope", "dfp");
				e->e_dfp = NULL;
			}
			if (e->e_xfp != NULL)
			{
				(void) xfclose(e->e_xfp, "sendenvelope", "xfp");
				e->e_xfp = NULL;
			}
			return;
		}

		/* double fork to avoid zombies */
		if (fork() > 0)
			exit(EX_OK);

		/* be sure we are immune from the terminal */
		disconnect(FALSE, e);

# ifdef LOCKF
		/*
		**  Now try to get our lock back.
		*/

		lfd.l_type = F_WRLCK;
		lfd.l_whence = lfd.l_start = lfd.l_len = 0;
		e->e_lockfp = fopen(queuename(e, 'q'), "r+");
		if (e->e_lockfp == NULL ||
		    fcntl(fileno(e->e_lockfp), F_SETLK, &lfd) < 0)
		{
			/* oops....  lost it */
			if (tTd(13, 1))
				printf("sendenvelope: %s lost lock: lockfp=%x, %s\n",
					e->e_id, e->e_lockfp, errstring(errno));

# ifdef LOG
			if (LogLevel > 29)
				syslog(LOG_NOTICE, "%s: lost lock: %m",
					e->e_id);
# endif /* LOG */
			exit(EX_OK);
		}
# endif /* LOCKF */

		/*
		**  Close any cached connections.
		**
		**	We don't send the QUIT protocol because the parent
		**	still knows about the connection.
		**
		**	This should only happen when delivering an error
		**	message.
		*/

		mci_flush(FALSE, NULL);

		break;
	}

E 314
	/*
I 314
	**  If we haven't fully expanded aliases, do it now
	*/

	if (bitset(EF_VRFYONLY, e->e_flags))
	{
		e->e_flags &= ~EF_VRFYONLY;
		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			extern ADDRESS *recipient();

			if (bitset(QVERIFIED, q->q_flags))
				recipient(q, &e->e_sendqueue, e);
		}
	}

	/*
E 314
	**  Handle alias owners.
	**
	**	We scan up the q_alias chain looking for owners.
	**	We discard owners that are the same as the return path.
	*/

	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
		register struct address *a;

		for (a = q; a != NULL && a->q_owner == NULL; a = a->q_alias)
			continue;
		if (a != NULL)
			q->q_owner = a->q_owner;
				
		if (q->q_owner != NULL &&
		    !bitset(QDONTSEND, q->q_flags) &&
		    strcmp(q->q_owner, e->e_from.q_paddr) == 0)
			q->q_owner = NULL;
	}
		
	owner = "";
	otherowners = 1;
	while (owner != NULL && otherowners > 0)
	{
		owner = NULL;
		otherowners = 0;

		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (bitset(QDONTSEND, q->q_flags))
				continue;

			if (q->q_owner != NULL)
			{
				if (owner == NULL)
					owner = q->q_owner;
				else if (owner != q->q_owner)
				{
					if (strcmp(owner, q->q_owner) == 0)
					{
						/* make future comparisons cheap */
						q->q_owner = owner;
					}
					else
					{
						otherowners++;
					}
					owner = q->q_owner;
				}
			}
			else
			{
				otherowners++;
			}
I 478

			/*
			**  If this mailer is expensive, and if we don't
			**  want to make connections now, just mark these
			**  addresses and return.  This is useful if we
			**  want to batch connections to reduce load.  This
			**  will cause the messages to be queued up, and a
			**  daemon will come along to send the messages later.
			*/

			if (bitset(QBADADDR|QQUEUEUP, q->q_flags))
				continue;
			if (NoConnect && !Verbose &&
			    bitnset(M_EXPENSIVE, q->q_mailer->m_flags))
			{
				q->q_flags |= QQUEUEUP;
				e->e_to = q->q_paddr;
				message("queued");
				if (LogLevel > 8)
					logdelivery(q->q_mailer, NULL,
						    "queued", NULL,
						    (time_t) 0, e);
				e->e_to = NULL;
			}
			else
			{
				somedeliveries = TRUE;
			}
E 478
		}

		if (owner != NULL && otherowners > 0)
		{
I 408
			register ENVELOPE *ee;
E 408
			extern HDR *copyheader();
			extern ADDRESS *copyqueue();

			/*
			**  Split this envelope into two.
			*/

			ee = (ENVELOPE *) xalloc(sizeof(ENVELOPE));
			*ee = *e;
			ee->e_id = NULL;
			(void) queuename(ee, '\0');

			if (tTd(13, 1))
				printf("sendall: split %s into %s\n",
					e->e_id, ee->e_id);

			ee->e_header = copyheader(e->e_header);
			ee->e_sendqueue = copyqueue(e->e_sendqueue);
			ee->e_errorqueue = copyqueue(e->e_errorqueue);
D 315
			ee->e_flags = e->e_flags & ~(EF_INQUEUE|EF_CLRQUEUE);
E 315
I 315
D 422
			ee->e_flags = e->e_flags & ~(EF_INQUEUE|EF_CLRQUEUE|EF_FATALERRS);
E 422
I 422
D 484
			ee->e_flags = e->e_flags & ~(EF_INQUEUE|EF_CLRQUEUE|EF_FATALERRS|EF_SENDRECEIPT);
E 484
I 484
			ee->e_flags = e->e_flags & ~(EF_INQUEUE|EF_CLRQUEUE|EF_FATALERRS|EF_SENDRECEIPT|EF_RET_PARAM);
E 484
			ee->e_flags |= EF_NORECEIPT;
E 422
E 315
			setsender(owner, ee, NULL, TRUE);
			if (tTd(13, 5))
			{
				printf("sendall(split): QDONTSEND ");
				printaddr(&ee->e_from, FALSE);
			}
			ee->e_from.q_flags |= QDONTSEND;
			ee->e_dfp = NULL;
			ee->e_xfp = NULL;
D 376
			ee->e_lockfp = NULL;
E 376
D 477
			ee->e_df = NULL;
E 477
			ee->e_errormode = EM_MAIL;
D 408
			ee->e_sibling = splitenv;
			splitenv = ee;
E 408
			
			for (q = e->e_sendqueue; q != NULL; q = q->q_next)
I 484
			{
E 484
				if (q->q_owner == owner)
I 416
				{
E 416
					q->q_flags |= QDONTSEND;
I 416
					q->q_flags &= ~QQUEUEUP;
				}
I 484
			}
E 484
E 416
			for (q = ee->e_sendqueue; q != NULL; q = q->q_next)
I 484
			{
E 484
				if (q->q_owner != owner)
I 416
				{
E 416
					q->q_flags |= QDONTSEND;
I 416
					q->q_flags &= ~QQUEUEUP;
				}
I 484
				else
				{
					/* clear DSN parameters */
					q->q_flags &= ~(QHASNOTIFY|QPINGONSUCCESS);
					q->q_flags |= QPINGONFAILURE|QPINGONDELAY;
				}
			}
E 484
E 416

D 477
			if (e->e_df != NULL && mode != SM_VERIFY)
E 477
I 477
			if (mode != SM_VERIFY && bitset(EF_HAS_DF, e->e_flags))
E 477
			{
I 477
				char df1buf[20], df2buf[20];

E 477
				ee->e_dfp = NULL;
D 349
				ee->e_df = newstr(queuename(ee, 'd'));
E 349
I 349
D 477
				ee->e_df = queuename(ee, 'd');
				ee->e_df = newstr(ee->e_df);
E 349
				if (link(e->e_df, ee->e_df) < 0)
E 477
I 477
				strcpy(df1buf, queuename(e, 'd'));
				strcpy(df2buf, queuename(ee, 'd'));
				if (link(df1buf, df2buf) < 0)
E 477
				{
					syserr("sendall: link(%s, %s)",
D 477
						e->e_df, ee->e_df);
E 477
I 477
						df1buf, df2buf);
E 477
				}
			}
D 410

			if (mode != SM_VERIFY)
				openxscript(ee);
E 410
#ifdef LOG
			if (LogLevel > 4)
D 411
				syslog(LOG_INFO, "%s: clone %s",
					ee->e_id, e->e_id);
E 411
I 411
				syslog(LOG_INFO, "%s: clone %s, owner=%s",
					ee->e_id, e->e_id, owner);
E 411
#endif
I 408
			CurEnv = ee;
			sendenvelope(ee, mode, announcequeueup);
			dropenvelope(ee);
E 408
		}
	}

I 408
	/*
	**  Split off envelopes have been sent -- now send original
	*/

E 408
	if (owner != NULL)
	{
		setsender(owner, e, NULL, TRUE);
		if (tTd(13, 5))
		{
			printf("sendall(owner): QDONTSEND ");
			printaddr(&e->e_from, FALSE);
		}
		e->e_from.q_flags |= QDONTSEND;
		e->e_errormode = EM_MAIL;
I 422
		e->e_flags |= EF_NORECEIPT;
E 422
	}

I 478
	/* if nothing to be delivered, just queue up everything */
	if (!somedeliveries && mode != SM_QUEUE && mode != SM_VERIFY)
		mode = SM_QUEUE;

E 478
D 314
D 408
# ifdef QUEUE
	if ((mode == SM_QUEUE || mode == SM_FORK ||
	     (mode != SM_VERIFY && SuperSafe)) &&
	    !bitset(EF_INQUEUE, e->e_flags))
E 408
I 408
	if (otherowners > 0 && tTd(13, 1))
E 408
	{
D 408
		/* be sure everything is instantiated in the queue */
D 317
		queueup(e, TRUE, mode == SM_QUEUE);
E 317
I 317
D 478
		queueup(e, TRUE, announcequeueup);
E 478
I 478
		queueup(e, TRUE, mode == SM_QUEUE);
E 478
E 317
		for (ee = splitenv; ee != NULL; ee = ee->e_sibling)
D 317
			queueup(ee, TRUE, mode == SM_QUEUE);
E 317
I 317
D 478
			queueup(ee, TRUE, announcequeueup);
E 478
I 478
			queueup(ee, TRUE, mode == SM_QUEUE);
E 478
E 408
I 408
		printf("\nsendall: Split queue; remaining queue:\n");
		printaddr(e->e_sendqueue, TRUE);
E 408
E 317
	}
D 408
#endif /* QUEUE */
E 408

E 314
D 408
D 449
	if (splitenv != NULL)
	{
		if (tTd(13, 1))
		{
			printf("\nsendall: Split queue; remaining queue:\n");
			printaddr(e->e_sendqueue, TRUE);
		}

		for (ee = splitenv; ee != NULL; ee = ee->e_sibling)
		{
			CurEnv = ee;
I 410
			if (mode != SM_VERIFY)
				openxscript(ee);
E 410
			sendenvelope(ee, mode);
I 410
			dropenvelope(ee);
E 410
		}

		CurEnv = e;
	}
	sendenvelope(e, mode);
D 410

	for (; splitenv != NULL; splitenv = splitenv->e_sibling)
		dropenvelope(splitenv);
E 410
E 408
I 408
	CurEnv = e;
	sendenvelope(e, mode, announcequeueup);
E 408
}

D 408
sendenvelope(e, mode)
E 408
I 408
sendenvelope(e, mode, announcequeueup)
E 408
	register ENVELOPE *e;
	char mode;
I 408
	bool announcequeueup;
E 408
{
D 314
	bool oldverbose;
	int pid;
E 314
	register ADDRESS *q;
D 314
D 348
#ifdef LOCKF
E 348
I 348
D 352
#ifndef HASFLOCK
E 348
	struct flock lfd;
#endif
E 352
I 352
	char *qf;
	char *id;
I 435
	bool didany;
E 435
I 408

# ifdef QUEUE
	if ((mode == SM_QUEUE || mode == SM_FORK ||
	     (mode != SM_VERIFY && SuperSafe)) &&
	    !bitset(EF_INQUEUE, e->e_flags))
	{
		/* be sure everything is instantiated in the queue */
		queueup(e, TRUE, announcequeueup);
	}
#endif /* QUEUE */
E 408
E 352

E 449
I 344
	/*
D 449
	**  If we have had global, fatal errors, don't bother sending
	**  the message at all if we are in SMTP mode.  Local errors
	**  (e.g., a single address failing) will still cause the other
	**  addresses to be sent.
E 449
I 449
	**  If we belong in background, fork now.
E 449
	*/

D 401
	if (bitset(EF_FATALERRS, e->e_flags) && OpMode == MD_SMTP)
E 401
I 401
D 449
	if (bitset(EF_FATALERRS, e->e_flags) &&
	    (OpMode == MD_SMTP || OpMode == MD_DAEMON))
E 401
	{
		e->e_flags |= EF_CLRQUEUE;
		return;
	}

E 344
	oldverbose = Verbose;
E 449
I 315
D 319
	e->e_statmsg = NULL;
E 319
E 315
	switch (mode)
	{
	  case SM_VERIFY:
		Verbose = TRUE;
		break;

	  case SM_QUEUE:
  queueonly:
D 478
		e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
E 478
I 478
		if (e->e_nrcpts > 0)
			e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
E 478
		return;

	  case SM_FORK:
		if (e->e_xfp != NULL)
			(void) fflush(e->e_xfp);

D 348
# ifdef LOCKF
E 348
I 348
D 404
# ifndef HASFLOCK
E 404
I 404
# if !HASFLOCK
E 404
E 348
		/*
D 348
		**  Since lockf has the interesting semantic that the
		**  lock is lost when we fork, we have to risk losing
E 348
I 348
D 352
		**  Since fcntl lockin has the interesting semantic that
		**  the lock is lost when we fork, we have to risk losing
E 348
		**  the lock here by closing before the fork, and then
		**  trying to get it back in the child.
E 352
I 352
		**  Since fcntl locking has the interesting semantic that
		**  the lock is owned by a process, not by an open file
		**  descriptor, we have to flush this to the queue, and
		**  then restart from scratch in the child.
E 352
		*/

D 352
		if (e->e_lockfp != NULL)
		{
			(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
			e->e_lockfp = NULL;
		}
D 348
# endif /* LOCKF */
E 348
I 348
# endif /* HASFLOCK */
E 352
I 352
D 479
		/* save id for future use */
D 452
		id = e->e_id;
E 452
I 452
		qid = e->e_id;
E 479
I 479
		{
			/* save id for future use */
			char *qid = e->e_id;
E 479
E 452
E 352
E 348

I 352
D 479
		/* now drop the envelope in the parent */
		e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
I 365
D 375
		e->e_flags &= ~EF_FATALERRS;
E 375
E 365
		dropenvelope(e);
E 479
I 479
			/* now drop the envelope in the parent */
			e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
			dropenvelope(e);
E 479

D 479
		/* and reacquire in the child */
D 452
		(void) dowork(id, TRUE, FALSE, e);
E 452
I 452
		(void) dowork(qid, TRUE, FALSE, e);
E 479
I 479
			/* and reacquire in the child */
			(void) dowork(qid, TRUE, FALSE, e);
		}
E 479
E 452

		return;

# else /* HASFLOCK */

E 352
		pid = fork();
		if (pid < 0)
		{
			goto queueonly;
		}
		else if (pid > 0)
		{
D 352
			/* be sure we leave the temp files to our child */
			e->e_id = e->e_df = NULL;
D 348
# ifndef LOCKF
E 348
I 348
# ifdef HASFLOCK
E 352
E 348
D 353
			if (e->e_lockfp != NULL)
			{
				(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
				e->e_lockfp = NULL;
			}
D 352
# endif
E 352

			/* close any random open files in the envelope */
			if (e->e_dfp != NULL)
			{
				(void) xfclose(e->e_dfp, "sendenvelope", "dfp");
				e->e_dfp = NULL;
			}
			if (e->e_xfp != NULL)
			{
				(void) xfclose(e->e_xfp, "sendenvelope", "xfp");
				e->e_xfp = NULL;
			}
E 353
I 353
D 354
			/* now drop the envelope in the parent */
			e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
E 354
I 354
			/* be sure we leave the temp files to our child */
			/* can't call unlockqueue to avoid unlink of xfp */
			if (e->e_lockfp != NULL)
D 477
				(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
E 477
I 477
				(void) xfclose(e->e_lockfp, "sendenvelope lockfp", e->e_id);
E 477
			e->e_lockfp = NULL;

			/* close any random open files in the envelope */
			closexscript(e);
			if (e->e_dfp != NULL)
D 477
				(void) xfclose(e->e_dfp, "sendenvelope", e->e_df);
E 477
I 477
				(void) xfclose(e->e_dfp, "sendenvelope dfp", e->e_id);
E 477
			e->e_dfp = NULL;
D 477
			e->e_id = e->e_df = NULL;
E 477
I 477
			e->e_id = NULL;
			e->e_flags &= ~EF_HAS_DF;
E 477
I 412

			/* catch intermediate zombie */
			(void) waitfor(pid);
E 412
E 354
E 353
			return;
		}

		/* double fork to avoid zombies */
D 412
		if (fork() > 0)
E 412
I 412
		pid = fork();
		if (pid > 0)
E 412
			exit(EX_OK);

		/* be sure we are immune from the terminal */
D 344
		disconnect(FALSE, e);
E 344
I 344
		disconnect(1, e);
E 344

I 412
		/* prevent parent from waiting if there was an error */
		if (pid < 0)
		{
			e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
			finis();
		}

E 412
D 348
# ifdef LOCKF
E 348
I 348
D 352
# ifndef HASFLOCK
E 352
E 348
		/*
D 352
		**  Now try to get our lock back.
		*/

		lfd.l_type = F_WRLCK;
		lfd.l_whence = lfd.l_start = lfd.l_len = 0;
		e->e_lockfp = fopen(queuename(e, 'q'), "r+");
		if (e->e_lockfp == NULL ||
		    fcntl(fileno(e->e_lockfp), F_SETLK, &lfd) < 0)
		{
			/* oops....  lost it */
			if (tTd(13, 1))
				printf("sendenvelope: %s lost lock: lockfp=%x, %s\n",
					e->e_id, e->e_lockfp, errstring(errno));

# ifdef LOG
			if (LogLevel > 29)
				syslog(LOG_NOTICE, "%s: lost lock: %m",
					e->e_id);
# endif /* LOG */
			exit(EX_OK);
		}
D 348
# endif /* LOCKF */
E 348
I 348
# endif /* HASFLOCK */
E 348

		/*
E 352
		**  Close any cached connections.
		**
		**	We don't send the QUIT protocol because the parent
		**	still knows about the connection.
		**
		**	This should only happen when delivering an error
		**	message.
		*/

		mci_flush(FALSE, NULL);
I 352

# endif /* HASFLOCK */
E 352

		break;
	}
E 314
I 314
	bool oldverbose = Verbose;
E 314

I 449
	if (splitenv != NULL)
	{
		if (tTd(13, 1))
		{
			printf("\nsendall: Split queue; remaining queue:\n");
			printaddr(e->e_sendqueue, TRUE);
		}

		for (ee = splitenv; ee != NULL; ee = ee->e_sibling)
		{
			CurEnv = ee;
			if (mode != SM_VERIFY)
				openxscript(ee);
			sendenvelope(ee, mode);
			dropenvelope(ee);
		}

		CurEnv = e;
	}
	sendenvelope(e, mode);
	Verbose = oldverbose;
}

I 467
void
E 467
sendenvelope(e, mode)
	register ENVELOPE *e;
	char mode;
{
	register ADDRESS *q;
D 467
	char *qf;
E 467
D 452
	char *id;
E 452
	bool didany;

E 449
	/*
I 449
	**  If we have had global, fatal errors, don't bother sending
	**  the message at all if we are in SMTP mode.  Local errors
	**  (e.g., a single address failing) will still cause the other
	**  addresses to be sent.
	*/

	if (bitset(EF_FATALERRS, e->e_flags) &&
	    (OpMode == MD_SMTP || OpMode == MD_DAEMON))
	{
		e->e_flags |= EF_CLRQUEUE;
		return;
	}

	/*
E 449
	**  Run through the list and send everything.
I 346
	**
	**	Set EF_GLOBALERRS so that error messages during delivery
	**	result in returned mail.
E 346
	*/

	e->e_nsent = 0;
I 346
	e->e_flags |= EF_GLOBALERRS;
I 435
	didany = FALSE;
E 435
I 369

D 370
	/* be sure to use any new error message */
	if (e->e_message != NULL)
		free(e->e_message);
	e->e_message = NULL;

E 370
	/* now run through the queue */
E 369
E 346
	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
I 362
D 504
#ifdef XDEBUG
E 504
I 504
#if XDEBUG
E 504
		char wbuf[MAXNAME + 20];

		(void) sprintf(wbuf, "sendall(%s)", q->q_paddr);
		checkfd012(wbuf);
#endif
E 362
		if (mode == SM_VERIFY)
		{
			e->e_to = q->q_paddr;
			if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
D 336
				message("deliverable");
E 336
I 336
			{
D 383
				message("deliverable: mailer %s, host %s, user %s",
					q->q_mailer->m_name,
					q->q_host,
					q->q_user);
E 383
I 383
				if (q->q_host != NULL && q->q_host[0] != '\0')
					message("deliverable: mailer %s, host %s, user %s",
						q->q_mailer->m_name,
						q->q_host,
						q->q_user);
				else
					message("deliverable: mailer %s, user %s",
						q->q_mailer->m_name,
						q->q_user);
E 383
			}
E 336
		}
		else if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
		{
# ifdef QUEUE
			/*
			**  Checkpoint the send list every few addresses
			*/

			if (e->e_nsent >= CheckpointInterval)
			{
				queueup(e, TRUE, FALSE);
				e->e_nsent = 0;
			}
# endif /* QUEUE */
			(void) deliver(e, q);
I 435
			didany = TRUE;
E 435
		}
	}
D 449
	Verbose = oldverbose;
E 449
I 435
	if (didany)
	{
		e->e_dtime = curtime();
		e->e_ntries++;
	}
E 435
I 362

D 504
#ifdef XDEBUG
E 504
I 504
#if XDEBUG
E 504
	checkfd012("end of sendenvelope");
#endif
E 362
D 344

	/*
	**  Now run through and check for errors.
	*/

	if (mode == SM_VERIFY)
	{
		return;
	}

	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
		if (tTd(13, 3))
		{
			printf("Checking ");
			printaddr(q, FALSE);
		}

		/* only send errors if the message failed */
D 315
		if (!bitset(QBADADDR, q->q_flags))
E 315
I 315
		if (!bitset(QBADADDR, q->q_flags) ||
		    bitset(QDONTSEND, q->q_flags))
E 315
			continue;

I 343
		if (tTd(13, 3))
			printf("FATAL ERRORS\n");

E 343
		e->e_flags |= EF_FATALERRS;

		if (q->q_owner == NULL && strcmp(e->e_from.q_paddr, "<>") != 0)
			(void) sendtolist(e->e_from.q_paddr, NULL,
					  &e->e_errorqueue, e);
	}
E 344

	if (mode == SM_FORK)
		finis();
}
/*
**  DOFORK -- do a fork, retrying a couple of times on failure.
**
**	This MUST be a macro, since after a vfork we are running
**	two processes on the same stack!!!
**
**	Parameters:
**		none.
**
**	Returns:
**		From a macro???  You've got to be kidding!
**
**	Side Effects:
**		Modifies the ==> LOCAL <== variable 'pid', leaving:
**			pid of child in parent, zero in child.
**			-1 on unrecoverable error.
**
**	Notes:
**		I'm awfully sorry this looks so awful.  That's
**		vfork for you.....
*/

# define NFORKTRIES	5

# ifndef FORK
# define FORK	fork
# endif

# define DOFORK(fORKfN) \
{\
	register int i;\
\
	for (i = NFORKTRIES; --i >= 0; )\
	{\
		pid = fORKfN();\
		if (pid >= 0)\
			break;\
		if (i > 0)\
			sleep((unsigned) NFORKTRIES - i);\
	}\
}
/*
**  DOFORK -- simple fork interface to DOFORK.
**
**	Parameters:
**		none.
**
**	Returns:
**		pid of child in parent.
**		zero in child.
**		-1 on error.
**
**	Side Effects:
**		returns twice, once in parent and once in child.
*/

I 500
int
E 500
dofork()
{
D 467
	register int pid;
E 467
I 467
	register int pid = -1;
E 467

	DOFORK(fork);
	return (pid);
}
/*
E 312
D 54
**  DELIVER -- Deliver a message to a particular address.
E 54
I 54
**  DELIVER -- Deliver a message to a list of addresses.
E 54
**
I 54
**	This routine delivers to everyone on the same host as the
**	user on the head of the list.  It is clever about mailers
**	that don't handle multiple users.  It is NOT guaranteed
**	that it will deliver to all these addresses however -- so
**	deliver should be called once for each address on the
**	list.
**
E 54
D 26
**	Algorithm:
**		Compute receiving network (i.e., mailer), host, & user.
**		If local, see if this is really a program name.
**		Build argument for the mailer.
**		Create pipe through edit fcn if appropriate.
**		Fork.
**			Child: call mailer
**		Parent: call editfcn if specified.
**		Wait for mailer to finish.
**		Interpret exit status.
**
E 26
**	Parameters:
I 154
**		e -- the envelope to deliver.
E 154
D 54
**		to -- the address to deliver the message to.
E 54
I 54
D 69
**		to -- head of the address list to deliver to.
E 69
I 69
**		firstto -- head of the address list to deliver to.
E 69
E 54
D 100
**		editfcn -- if non-NULL, we want to call this function
**			to output the letter (instead of just out-
**			putting it raw).
E 100
**
**	Returns:
**		zero -- successfully delivered.
**		else -- some failure, see ExitStat for more info.
**
**	Side Effects:
**		The standard input is passed off to someone.
D 26
**
**	WARNING:
**		The standard input is shared amongst all children,
**		including the file pointer.  It is critical that the
**		parent waits for the child to finish before forking
**		another child.
E 26
D 25
**
D 4
**	Requires:
**		buildargv
**		giveresponse
**		fork (sys)
**		rewind (sys)
**		execv (sys)
**		exit (sys)
**		wait (sys)
**		syserr
**		getpwnam (sys)
**		endpwent (sys)
**		initlog
**		flagset
**		usrerr
**		pipe (sys)
**		close (sys)
**		dup (sys)
**		setuid (sys)
**		getuid (sys)
**		signal (sys)
**		fdopen (sys[v7] or conf.c[v6])
**		fclose (sys)
**		printf (sys)
**		stripquotes
**		mailfile
**		index (sys)
**
E 4
**	Called By:
**		main
**		savemail
**
**	Files:
D 4
**		standard input -- must be openned to the message to
E 4
I 4
**		standard input -- must be opened to the message to
E 4
**			deliver.
E 25
D 4
**
**	History:
**		3/5/80 -- modified rather extensively to change the
**			internal form of addresses.
**		12/26/79 -- written.
E 4
*/

I 467
int
E 467
D 69
deliver(to, editfcn)
D 20
	addrq *to;
E 20
I 20
	ADDRESS *to;
E 69
I 69
D 100
deliver(firstto, editfcn)
E 100
I 100
D 154
deliver(firstto)
E 154
I 154
deliver(e, firstto)
	register ENVELOPE *e;
E 154
E 100
	ADDRESS *firstto;
E 69
E 20
D 100
	int (*editfcn)();
E 100
{
D 26
	register struct mailer *m;
E 26
D 64
	char *host;
	char *user;
E 64
I 64
	char *host;			/* host being sent to */
	char *user;			/* user being sent to */
E 64
D 37
	extern struct passwd *getpwnam();
E 37
	char **pvp;
D 26
	extern char **buildargv();
	auto int st;
	register int i;
E 26
I 26
	register char **mvp;
E 26
	register char *p;
D 26
	int pid;
	int pvect[2];
	extern FILE *fdopen();
E 26
I 26
D 64
	register struct mailer *m;
E 64
I 64
D 154
	register struct mailer *m;	/* mailer for this recipient */
E 154
I 154
D 167
	register MAILER *m;	/* mailer for this recipient */
E 154
E 64
D 127
	register int i;
E 127
E 26
D 36
	extern int errno;
E 36
D 26
	FILE *mfile;
E 26
D 19
	extern putheader();
E 19
I 19
D 100
	extern putmessage();
E 100
E 19
D 26
	extern pipesig();
E 26
I 14
D 19
	extern bool GotHdr;
E 19
I 15
D 36
	extern char *index();
E 36
I 20
	extern bool checkcompat();
I 26
	char *pv[MAXPV+1];
D 36
	extern char *newstr();
E 36
D 64
	char tobuf[MAXLINE];
E 64
I 64
D 135
	char tobuf[MAXLINE];		/* text line of to people */
E 135
I 135
	char tobuf[MAXLINE-50];		/* text line of to people */
E 135
E 64
	char buf[MAXNAME];
E 167
I 167
	register MAILER *m;		/* mailer for this recipient */
E 167
I 58
	ADDRESS *ctladdr;
I 247
	register MCI *mci;
E 247
D 167
	extern ADDRESS *getctladdr();
I 64
	char tfrombuf[MAXNAME];		/* translated from person */
	extern char **prescan();
E 167
I 69
	register ADDRESS *to = firstto;
I 72
	bool clever = FALSE;		/* running user smtp to this mailer */
D 117
	bool tempfail = FALSE;
E 117
I 76
D 467
	ADDRESS *tochain = NULL;	/* chain of users in this mailer call */
E 467
I 467
	ADDRESS *tochain = NULL;	/* users chain in this mailer call */
E 467
I 106
D 154
	bool notopen = TRUE;		/* set if connection not quite open */
E 154
I 127
D 205
	register int rcode;		/* response code */
E 205
I 205
D 239
	int rcode;		/* response code */
E 239
I 239
	int rcode;			/* response code */
D 301
	char *from;			/* pointer to from person */
E 301
I 263
	char *firstsig;			/* signature of firstto */
I 312
D 467
	int pid;
E 467
I 467
	int pid = -1;
E 467
	char *curhost;
I 461
	time_t xstart;
E 461
	int mpvect[2];
	int rpvect[2];
E 312
E 263
E 239
E 205
I 167
	char *pv[MAXPV+1];
D 304
	char tobuf[MAXLINE-50];		/* text line of to people */
E 304
I 304
	char tobuf[TOBUFSIZE];		/* text line of to people */
E 304
D 474
	char buf[MAXNAME];
D 301
	char tfrombuf[MAXNAME];		/* translated from person */
E 301
I 239
	char rpathbuf[MAXNAME];		/* translated return path */
E 474
I 474
	char buf[MAXNAME + 1];
	char rpathbuf[MAXNAME + 1];	/* translated return path */
E 474
E 239
D 262
	extern bool checkcompat();
E 262
I 262
	extern int checkcompat();
I 500
	extern void markfailure __P((ENVELOPE *, ADDRESS *, MCI *, int));
E 500
E 262
D 337
	extern ADDRESS *getctladdr();
	extern char *remotename();
I 247
D 312
	extern MCI *openmailer();
E 312
I 263
	extern char *hostsignature();
E 337
I 312
D 372
	extern FILE *fdopen();
E 372
I 371
D 393
	extern char SmtpError[];
E 393
E 371
E 312
E 263
E 247
E 167
E 127
E 106
E 76
E 72
E 69
E 64
E 58
D 36
	extern char *expand();
E 36
D 57
	bool firstone;
E 57
E 26
E 20
E 15
E 14

I 66
	errno = 0;
E 66
D 26
	/*
	**  Compute receiving mailer, host, and to addreses.
	**	Do some initialization first.  To is the to address
	**	for error messages.
I 25
	**	Also, define the standard per-address macros.
E 25
	*/
E 26
I 26
D 53
	if (bitset(QDONTSEND, to->q_flags))
E 53
I 53
D 74
D 106
	if (!ForceMail && bitset(QDONTSEND, to->q_flags))
E 106
I 106
D 284
	if (bitset(QDONTSEND, to->q_flags))
E 284
I 284
D 301
	if (bitset(QDONTSEND|QQUEUEUP, to->q_flags))
E 301
I 301
	if (bitset(QDONTSEND|QBADADDR|QQUEUEUP, to->q_flags))
E 301
E 284
E 106
E 74
I 74
	if (!ForceMail && bitset(QDONTSEND|QPSEUDO, to->q_flags))
E 74
E 53
		return (0);
E 26

I 210
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
E 210
I 207
	/* unless interactive, try twice, over a minute */
D 401
	if (OpMode == MD_DAEMON || OpMode == MD_SMTP) {
E 401
I 401
	if (OpMode == MD_DAEMON || OpMode == MD_SMTP)
	{
E 401
		_res.retrans = 30;
		_res.retry = 2;
	}
I 210
D 214
#endif NAMED_BIND
E 214
I 214
#endif 
E 214
E 210

E 207
I 100
	m = to->q_mailer;
	host = to->q_host;
I 311
	CurEnv = e;			/* just in case */
I 319
	e->e_statmsg = NULL;
I 371
	SmtpError[0] = '\0';
I 466
	xstart = curtime();
E 466
E 371
E 319
E 311

E 100
D 26
	To = to->q_paddr;
D 23
	m = to->q_mailer;
E 23
I 23
	m = Mailer[to->q_mailer];
E 23
	user = to->q_user;
	host = to->q_host;
D 7
	Error = 0;
E 7
I 7
	Errors = 0;
E 7
	errno = 0;
I 25
	define('u', user);		/* to user */
	define('h', host);		/* to host */
	define('g', m->m_from);		/* translated from address */
E 26
E 25
D 213
# ifdef DEBUG
E 213
D 117
	if (Debug)
E 117
I 117
	if (tTd(10, 1))
E 117
D 26
		printf("deliver(%s [%d, `%s', `%s'])\n", To, m, host, user);
E 26
I 26
D 410
		printf("\n--deliver, mailer=%d, host=`%s', first user=`%s'\n",
D 68
			to->q_mailer, to->q_host, to->q_user);
E 68
I 68
D 100
			to->q_mailer->m_mno, to->q_host, to->q_user);
E 100
I 100
			m->m_mno, host, to->q_user);
E 410
I 410
		printf("\n--deliver, id=%s, mailer=%s, host=`%s', first user=`%s'\n",
			e->e_id, m->m_name, host, to->q_user);
E 410
I 373
	if (tTd(10, 100))
		printopenfds(FALSE);
E 373
E 100
E 68
E 26
D 213
# endif DEBUG
E 213
I 100
D 106
	if (Verbose)
		message(Arpa_Info, "Connecting to %s.%s...", host, m->m_name);
E 106
E 100
D 478

I 85
D 100
	m = to->q_mailer;
	host = to->q_host;

E 100
E 85
	/*
I 85
	**  If this mailer is expensive, and if we don't want to make
	**  connections now, just mark these addresses and return.
	**	This is useful if we want to batch connections to
	**	reduce load.  This will cause the messages to be
	**	queued up, and a daemon will come along to send the
	**	messages later.
	**		This should be on a per-mailer basis.
	*/

D 140
	if (NoConnect && !QueueRun && bitset(M_EXPENSIVE, m->m_flags))
E 140
I 140
D 168
	if (NoConnect && !QueueRun && bitset(M_EXPENSIVE, m->m_flags) &&
E 168
I 168
D 309
	if (NoConnect && !QueueRun && bitnset(M_EXPENSIVE, m->m_flags) &&
E 168
	    !Verbose)
E 309
I 309
D 366
	if (NoConnect && !bitset(EF_QUEUERUN, e->e_flags) &&
	    bitnset(M_EXPENSIVE, m->m_flags) && !Verbose)
E 366
I 366
	if (NoConnect && bitnset(M_EXPENSIVE, m->m_flags) && !Verbose)
E 366
E 309
E 140
	{
D 99
		QueueUp = TRUE;
E 99
I 99
D 103
		CurEnv->e_queueup = TRUE;
E 103
E 99
		for (; to != NULL; to = to->q_next)
D 123
			if (!bitset(QDONTSEND, to->q_flags))
E 123
I 123
D 141
			if (!bitset(QDONTSEND, to->q_flags) &&
			    to->q_mailer == firstto->q_mailer)
E 123
				to->q_flags |= QQUEUEUP|QDONTSEND;
E 141
I 141
		{
D 284
			if (bitset(QDONTSEND, to->q_flags) || to->q_mailer != m)
E 284
I 284
D 301
			if (bitset(QDONTSEND|QQUEUEUP, to->q_flags) ||
E 301
I 301
			if (bitset(QDONTSEND|QBADADDR|QQUEUEUP, to->q_flags) ||
E 301
			    to->q_mailer != m)
E 284
				continue;
D 345
			to->q_flags |= QQUEUEUP|QDONTSEND;
E 345
I 345
			to->q_flags |= QQUEUEUP;
E 345
D 154
			CurEnv->e_to = to->q_paddr;
E 154
I 154
			e->e_to = to->q_paddr;
I 421
D 423
			define('h', NULL, e);
E 423
E 421
E 154
D 143
			giveresponse(EX_TEMPFAIL, TRUE, m);
E 143
I 143
D 280
			message(Arpa_Info, "queued");
E 280
I 280
			message("queued");
E 280
D 273
			if (LogLevel > 4)
E 273
I 273
			if (LogLevel > 8)
E 273
D 247
				logdelivery("queued");
E 247
I 247
D 290
				logdelivery("queued", e);
E 290
I 290
D 377
				logdelivery(m, NULL, "queued", e);
E 377
I 377
D 461
				logdelivery(m, NULL, "queued", NULL, e);
E 461
I 461
				logdelivery(m, NULL, "queued", NULL, xstart, e);
E 461
E 377
E 290
E 247
E 143
		}
D 154
		CurEnv->e_to = NULL;
E 154
I 154
		e->e_to = NULL;
E 154
E 141
		return (0);
	}
E 478

	/*
E 85
I 20
D 26
	**  Check to see that these people are allowed to talk to each other.
E 26
I 26
	**  Do initial argv setup.
	**	Insert the mailer name.  Notice that $x expansion is
	**	NOT done on the mailer name.  Then, if the mailer has
	**	a picky -f flag, we insert it as appropriate.  This
	**	code does not check for 'pv' overflow; this places a
	**	manifest lower limit of 4 for MAXPV.
I 85
D 128
	**		We rewrite the from address here, being careful
	**		to also rewrite it again using ruleset 2 to
	**		eliminate redundancies.
E 128
I 128
	**		The from address rewrite is expected to make
	**		the address relative to the other end.
E 128
E 85
E 26
	*/
D 85

D 26
	if (!checkcompat(to))
		return(giveresponse(EX_UNAVAILABLE, TRUE, m));
E 26
I 26
D 68
	m = Mailer[to->q_mailer];
E 68
I 68
	m = to->q_mailer;
E 68
	host = to->q_host;
E 85
D 64
	define('g', m->m_from);		/* translated from address */
E 64
I 64

	/* rewrite from address, using rewriting rules */
D 100
	(void) expand(m->m_from, buf, &buf[sizeof buf - 1]);
E 100
I 100
D 128
	expand(m->m_from, buf, &buf[sizeof buf - 1], CurEnv);
E 128
I 128
D 154
	expand("$f", buf, &buf[sizeof buf - 1], CurEnv);
E 154
I 154
D 181
	expand("$f", buf, &buf[sizeof buf - 1], e);
E 181
I 181
D 239
	expand("\001f", buf, &buf[sizeof buf - 1], e);
E 181
E 154
E 128
E 100
D 167
	mvp = prescan(buf, '\0');
I 154
	rewrite(mvp, 3);
	rewrite(mvp, 1);
E 154
D 128
	if (mvp == NULL)
	{
		syserr("bad mailer from translate \"%s\"", buf);
		return (EX_SOFTWARE);
	}
	rewrite(mvp, 2);
E 128
I 128
	rewrite(mvp, m->m_s_rwset);
I 165
	rewrite(mvp, 4);
E 165
E 128
	cataddr(mvp, tfrombuf, sizeof tfrombuf);
E 167
I 167
	(void) strcpy(tfrombuf, remotename(buf, m, TRUE, TRUE));
E 239
I 239
D 250
	(void) strcpy(rpathbuf, remotename(e->e_returnpath, m, TRUE, TRUE));
E 250
I 250
D 273
	(void) strcpy(rpathbuf, remotename(e->e_returnpath, m, TRUE, TRUE, e));
E 273
I 273
D 301
	(void) strcpy(rpathbuf, remotename(e->e_returnpath, m, TRUE, FALSE,
E 301
I 301
D 322
	(void) strcpy(rpathbuf, remotename(e->e_from.q_paddr, m, TRUE, FALSE,
E 301
D 294
					   TRUE, e));
E 294
I 294
					   TRUE, FALSE, e));
E 322
I 322
	rcode = EX_OK;
D 441
	(void) strcpy(rpathbuf, remotename(e->e_from.q_paddr, m,
E 441
I 441
	if (bitnset(M_UDBENVELOPE, e->e_from.q_mailer->m_flags))
		p = e->e_sender;
	else
		p = e->e_from.q_paddr;
	(void) strcpy(rpathbuf, remotename(p, m,
E 441
					   RF_SENDERADDR|RF_CANONICAL,
					   &rcode, e));
E 322
E 294
E 273
E 250
D 301
	if (e->e_returnpath == e->e_sender)
	{
		from = rpathbuf;
	}
	else
	{
D 250
		(void) strcpy(tfrombuf, remotename(e->e_sender, m, TRUE, TRUE));
E 250
I 250
D 273
		(void) strcpy(tfrombuf, remotename(e->e_sender, m, TRUE, TRUE, e));
E 273
I 273
		(void) strcpy(tfrombuf, remotename(e->e_sender, m, TRUE, FALSE,
D 294
						   TRUE, e));
E 294
I 294
						   TRUE, FALSE, e));
E 294
E 273
E 250
		from = tfrombuf;
	}
E 301
E 239
E 167
D 304

D 154
	define('g', tfrombuf);		/* translated sender address */
E 64
	define('h', host);		/* to host */
E 154
I 154
D 239
	define('g', tfrombuf, e);		/* translated sender address */
E 239
I 239
D 301
	define('f', e->e_returnpath, e);	/* raw return path */
	define('<', rpathbuf, e);		/* translated return path */
	define('g', from, e);			/* translated sender */
E 301
I 301
	define('f', e->e_from.q_paddr, e);	/* raw return path */
E 304
	define('g', rpathbuf, e);		/* translated return path */
E 301
E 239
	define('h', host, e);			/* to host */
E 154
	Errors = 0;
D 66
	errno = 0;
E 66
	pvp = pv;
	*pvp++ = m->m_argv[0];
E 26

D 26
	/*
E 20
	**  Remove quote bits from user/host.
	*/
E 26
I 26
	/* insert -f or -r flag as appropriate */
D 168
	if (bitset(M_FOPT|M_ROPT, m->m_flags) && FromFlag)
E 168
I 168
	if (FromFlag && (bitnset(M_FOPT, m->m_flags) || bitnset(M_ROPT, m->m_flags)))
E 168
	{
D 168
		if (bitset(M_FOPT, m->m_flags))
E 168
I 168
		if (bitnset(M_FOPT, m->m_flags))
E 168
			*pvp++ = "-f";
		else
			*pvp++ = "-r";
D 36
		expand("$g", buf, &buf[sizeof buf - 1]);
E 36
I 36
D 100
		(void) expand("$g", buf, &buf[sizeof buf - 1]);
E 100
I 100
D 154
		expand("$g", buf, &buf[sizeof buf - 1], CurEnv);
E 154
I 154
D 181
		expand("$g", buf, &buf[sizeof buf - 1], e);
E 181
I 181
D 239
		expand("\001g", buf, &buf[sizeof buf - 1], e);
E 181
E 154
E 100
E 36
		*pvp++ = newstr(buf);
E 239
I 239
		*pvp++ = newstr(rpathbuf);
E 239
	}
E 26

D 26
	for (p = user; (*p++ &= 0177) != '\0'; )
		continue;
	if (host != NULL)
		for (p = host; (*p++ &= 0177) != '\0'; )
			continue;
	
E 26
	/*
D 26
	**  Strip quote bits from names if the mailer wants it.
E 26
I 26
	**  Append the other fixed parts of the argv.  These run
	**  up to the first entry containing "$u".  There can only
	**  be one of these, and there are only a few more slots
	**  in the pv after it.
E 26
	*/

D 20
	if (flagset(M_STRIPQ, m->m_flags))
E 20
I 20
D 26
	if (bitset(M_STRIPQ, m->m_flags))
E 26
I 26
	for (mvp = m->m_argv; (p = *++mvp) != NULL; )
E 26
E 20
	{
D 26
		stripquotes(user);
		stripquotes(host);
E 26
I 26
D 181
		while ((p = index(p, '$')) != NULL)
E 181
I 181
D 256
		while ((p = index(p, '\001')) != NULL)
E 256
I 256
D 274
		while ((p = strchr(p, '\001')) != NULL)
E 256
E 181
			if (*++p == 'u')
				break;
		if (p != NULL)
E 274
I 274
		/* can't use strchr here because of sign extension problems */
		while (*p != '\0')
		{
			if ((*p++ & 0377) == MACROEXPAND)
			{
				if (*p == 'u')
					break;
			}
		}

		if (*p != '\0')
E 274
			break;

		/* this entry is safe -- go ahead and process it */
D 36
		expand(*mvp, buf, &buf[sizeof buf - 1]);
E 36
I 36
D 100
		(void) expand(*mvp, buf, &buf[sizeof buf - 1]);
E 100
I 100
D 154
		expand(*mvp, buf, &buf[sizeof buf - 1], CurEnv);
E 154
I 154
D 474
		expand(*mvp, buf, &buf[sizeof buf - 1], e);
E 474
I 474
D 475
		expand(*mvp, buf, &buf[sizeof buf], e);
E 475
I 475
		expand(*mvp, buf, sizeof buf, e);
E 475
E 474
E 154
E 100
E 36
		*pvp++ = newstr(buf);
		if (pvp >= &pv[MAXPV - 3])
		{
D 280
			syserr("Too many parameters to %s before $u", pv[0]);
E 280
I 280
			syserr("554 Too many parameters to %s before $u", pv[0]);
E 280
			return (-1);
		}
E 26
	}
I 72

I 90
	/*
	**  If we have no substitution for the user name in the argument
	**  list, we know that we must supply the names otherwise -- and
	**  SMTP is the answer!!
	*/

E 90
E 72
I 26
	if (*mvp == NULL)
D 72
		syserr("No $u in mailer argv for %s", pv[0]);
E 72
I 72
	{
		/* running SMTP */
I 79
# ifdef SMTP
E 79
		clever = TRUE;
		*pvp = NULL;
I 90
D 106

		/* send the initial SMTP protocol */
E 90
D 92
		i = smtpinit(m, pv, (ADDRESS *) NULL);
		giveresponse(i, TRUE, m);
E 92
I 92
D 102
		smtpinit(m, pv, (ADDRESS *) NULL);
E 102
I 102
		i = smtpinit(m, pv, (ADDRESS *) NULL);
E 102
E 92
I 79
# ifdef QUEUE
E 79
		if (i == EX_TEMPFAIL)
D 103
		{
D 99
			QueueUp = TRUE;
E 99
I 99
			CurEnv->e_queueup = TRUE;
E 103
E 99
			tempfail = TRUE;
D 103
		}
E 103
I 79
# endif QUEUE
E 106
D 256
# else SMTP
E 256
I 256
# else /* SMTP */
E 256
I 90
		/* oops!  we don't implement SMTP */
E 90
D 280
		syserr("SMTP style mailer");
E 280
I 280
D 371
		syserr("554 SMTP style mailer");
E 371
I 371
		syserr("554 SMTP style mailer not implemented");
E 371
E 280
		return (EX_SOFTWARE);
D 256
# endif SMTP
E 256
I 256
# endif /* SMTP */
E 256
E 79
	}
E 72
E 26

	/*
D 26
	**  See if this user name is "special".
	**	If the user is a program, diddle with the mailer spec.
	**	If the user name has a slash in it, assume that this
	**		is a file -- send it off without further ado.
	**		Note that this means that editfcn's will not
	**		be applied to the message.
E 26
I 26
	**  At this point *mvp points to the argument with $u.  We
	**  run through our address list and append all the addresses
	**  we can.  If we run out of space, do not fret!  We can
	**  always send another copy later.
E 26
	*/

D 23
	if (m == &Mailer[0])
E 23
I 23
D 26
	if (m == Mailer[0])
E 26
I 26
	tobuf[0] = '\0';
D 57
	firstone = TRUE;
E 57
D 99
	To = tobuf;
E 99
I 99
D 154
	CurEnv->e_to = tobuf;
E 154
I 154
	e->e_to = tobuf;
E 154
E 99
I 58
	ctladdr = NULL;
I 461
D 466
	xstart = curtime();
E 466
E 461
I 263
	firstsig = hostsignature(firstto->q_mailer, firstto->q_host, e);
E 263
E 58
	for (; to != NULL; to = to->q_next)
E 26
E 23
	{
D 26
		if (*user == '|')
E 26
I 26
		/* avoid sending multiple recipients to dumb mailers */
D 57
		if (!firstone && !bitset(M_MUSER, m->m_flags))
E 57
I 57
D 168
		if (tobuf[0] != '\0' && !bitset(M_MUSER, m->m_flags))
E 168
I 168
		if (tobuf[0] != '\0' && !bitnset(M_MUSER, m->m_flags))
E 168
E 57
			break;

		/* if already sent or not for this host, don't send */
D 53
		if (bitset(QDONTSEND, to->q_flags) || strcmp(to->q_host, host) != 0)
E 53
I 53
D 74
D 106
		if ((!ForceMail && bitset(QDONTSEND, to->q_flags)) ||
E 74
I 74
		if ((!ForceMail && bitset(QDONTSEND|QPSEUDO, to->q_flags)) ||
E 74
D 75
		    strcmp(to->q_host, host) != 0)
E 75
I 75
		    strcmp(to->q_host, host) != 0 || to->q_mailer != firstto->q_mailer)
E 106
I 106
D 284
		if (bitset(QDONTSEND, to->q_flags) ||
E 284
I 284
D 301
		if (bitset(QDONTSEND|QQUEUEUP, to->q_flags) ||
E 301
I 301
		if (bitset(QDONTSEND|QBADADDR|QQUEUEUP, to->q_flags) ||
E 301
E 284
D 263
		    strcmp(to->q_host, host) != 0 ||
		    to->q_mailer != firstto->q_mailer)
E 263
I 263
		    to->q_mailer != firstto->q_mailer ||
		    strcmp(hostsignature(to->q_mailer, to->q_host, e), firstsig) != 0)
E 263
E 106
E 75
E 53
			continue;
I 135

		/* avoid overflowing tobuf */
D 154
		if (sizeof tobuf - (strlen(to->q_paddr) + strlen(tobuf) + 1) < 0)
E 154
I 154
D 224
		if (sizeof tobuf - (strlen(to->q_paddr) + strlen(tobuf) + 2) < 0)
E 224
I 224
		if (sizeof tobuf < (strlen(to->q_paddr) + strlen(tobuf) + 2))
E 224
E 154
			break;
E 135
I 58

I 76
D 213
# ifdef DEBUG
E 213
D 117
		if (Debug)
E 117
I 117
		if (tTd(10, 1))
E 117
		{
			printf("\nsend to ");
			printaddr(to, FALSE);
		}
D 213
# endif DEBUG
E 213

D 93
		/* link together the chain of recipients */
		if (!bitset(QDONTSEND, to->q_flags))
		{
			to->q_tchain = tochain;
			tochain = to;
		}

E 93
E 76
		/* compute effective uid/gid when sending */
D 68
		if (to->q_mailer == MN_PROG)
E 68
I 68
D 392
		if (to->q_mailer == ProgMailer)
E 68
			ctladdr = getctladdr(to);
E 392
I 392
D 395
		ctladdr = getctladdr(to);
E 395
I 395
D 429
		/* XXX perhaps this should be to->q_mailer != LocalMailer ?? */
		/* XXX perhaps it should be a mailer flag? */
		if (to->q_mailer == ProgMailer || to->q_mailer == FileMailer)
E 429
I 429
		if (bitnset(M_RUNASRCPT, to->q_mailer->m_flags))
E 429
I 398
D 399
		{
E 399
E 398
			ctladdr = getctladdr(to);
I 398
D 399
			if (ctladdr != NULL &&
			    bitset(QBOGUSSHELL, ctladdr->q_flags))
			{
				/* user has no valid shell on this machine */
				usrerr("550 User %s doesn't have a valid shell on %s",
					ctladdr->q_ruser, MyHostName);
				giveresponse(EX_UNAVAILABLE, m, NULL, ctladdr, e);
				continue;
			}
		}
E 399
E 398
E 395
E 392

I 457
		if (tTd(10, 2))
		{
			printf("ctladdr=");
			printaddr(ctladdr, FALSE);
		}

E 457
E 58
		user = to->q_user;
D 99
		To = to->q_paddr;
E 99
I 99
D 154
		CurEnv->e_to = to->q_paddr;
E 154
I 154
		e->e_to = to->q_paddr;
E 154
E 99
D 301
		to->q_flags |= QDONTSEND;
E 301
I 269
		if (tTd(10, 5))
		{
			printf("deliver: QDONTSEND ");
			printaddr(to, FALSE);
		}
I 301
		to->q_flags |= QDONTSEND;
E 301
E 269
I 72
D 113
		if (tempfail)
I 76
		{
E 76
			to->q_flags |= QQUEUEUP;
E 72
D 54
		firstone = FALSE;

E 54
D 76
# ifdef DEBUG
		if (Debug)
			printf("   send to `%s'\n", user);
# endif DEBUG
E 76
I 76
			continue;
		}
E 113
E 76

		/*
		**  Check to see that these people are allowed to
		**  talk to each other.
		*/

I 169
		if (m->m_maxsize != 0 && e->e_msgsize > m->m_maxsize)
		{
D 200
			usrerr("Message is too large; %ld bytes max", m->m_maxsize);
E 200
D 429
			NoReturn = TRUE;
E 429
I 429
D 476
			e->e_flags |= EF_NORETURN;
E 476
I 476
			e->e_flags |= EF_NO_BODY_RETN;
I 492
D 500
			mci->mci_status = "5.2.3";
E 500
I 500
			to->q_status = "5.2.3";
E 500
E 492
E 476
E 429
I 200
D 280
			usrerr("Message is too large; %ld bytes max", m->m_maxsize);
E 280
I 280
			usrerr("552 Message is too large; %ld bytes max", m->m_maxsize);
E 280
E 200
D 290
			giveresponse(EX_UNAVAILABLE, m, e);
E 290
I 290
D 377
			giveresponse(EX_UNAVAILABLE, m, NULL, e);
E 377
I 377
D 461
			giveresponse(EX_UNAVAILABLE, m, NULL, ctladdr, e);
E 461
I 461
			giveresponse(EX_UNAVAILABLE, m, NULL, ctladdr, xstart, e);
E 461
E 377
E 290
			continue;
		}
I 428
#if NAMED_BIND
		h_errno = 0;
#endif
E 428
E 169
D 250
		if (!checkcompat(to))
E 250
I 250
D 262
		if (!checkcompat(to, e))
E 262
I 262
		rcode = checkcompat(to, e);
D 263
		if (r <= 0)
E 263
I 263
D 264
		if (rcode <= 0)
E 264
I 264
		if (rcode != EX_OK)
E 264
E 263
E 262
E 250
E 26
		{
I 343
D 458
			markfailure(e, to, rcode);
E 458
I 458
			markfailure(e, to, NULL, rcode);
E 458
E 343
D 26
			user++;
D 23
			m = &Mailer[1];
E 23
I 23
			m = Mailer[1];
E 26
I 26
D 154
			giveresponse(EX_UNAVAILABLE, TRUE, m);
E 154
I 154
D 161
			giveresponse(EX_UNAVAILABLE, m);
E 161
I 161
D 262
			giveresponse(EX_UNAVAILABLE, m, e);
E 262
I 262
D 264
			giveresponse(rcode == 0 ? EX_UNAVAILABLE : EX_TEMPFAIL,
				     m, e);
E 264
I 264
D 290
			giveresponse(rcode, m, e);
E 290
I 290
D 377
			giveresponse(rcode, m, NULL, e);
E 377
I 377
D 461
			giveresponse(rcode, m, NULL, ctladdr, e);
E 461
I 461
			giveresponse(rcode, m, NULL, ctladdr, xstart, e);
E 461
E 377
E 290
E 264
E 262
E 161
E 154
			continue;
E 26
E 23
		}
D 26
		else
E 26
I 26

		/*
D 37
		**  Remove quote bits from user/host.
E 37
I 37
		**  Strip quote bits from names if the mailer is dumb
		**	about them.
E 37
		*/

D 37
		for (p = user; (*p++ &= 0177) != '\0'; )
			continue;
		if (host != NULL)
			for (p = host; (*p++ &= 0177) != '\0'; )
				continue;
		
		/*
		**  Strip quote bits from names if the mailer wants it.
		*/

E 37
D 168
		if (bitset(M_STRIPQ, m->m_flags))
E 168
I 168
		if (bitnset(M_STRIPQ, m->m_flags))
E 168
E 26
		{
I 26
D 37
			stripquotes(user);
			stripquotes(host);
E 37
I 37
D 248
			stripquotes(user, TRUE);
			stripquotes(host, TRUE);
E 37
		}
I 37
		else
		{
			stripquotes(user, FALSE);
			stripquotes(host, FALSE);
E 248
I 248
			stripquotes(user);
			stripquotes(host);
E 248
		}
E 37

I 149
		/* hack attack -- delivermail compatibility */
		if (m == ProgMailer && *user == '|')
			user++;

E 149
		/*
I 106
D 154
		**  Do initial connection setup if needed.
		*/

		if (notopen)
		{
			message(Arpa_Info, "Connecting to %s.%s...", host, m->m_name);
# ifdef SMTP
			if (clever)
			{
				/* send the initial SMTP protocol */
D 127
				i = smtpinit(m, pv, (ADDRESS *) NULL);
E 127
I 127
				rcode = smtpinit(m, pv, (ADDRESS *) NULL);
E 127
D 117
# ifdef QUEUE
				if (i == EX_TEMPFAIL)
					tempfail = TRUE;
# endif QUEUE
E 117
			}
# ifdef SMTP
			notopen = FALSE;
		}

		/*
E 106
I 93
		**  Pass it to the other host if we are running SMTP.
		*/

		if (clever)
		{
# ifdef SMTP
D 127
			i = smtprcpt(to);
			if (i != EX_OK)
E 127
I 127
			if (rcode == EX_OK)
				rcode = smtprcpt(to);
			if (rcode != EX_OK)
E 127
			{
D 127
# ifdef QUEUE
				if (i == EX_TEMPFAIL)
E 127
I 127
				if (rcode == EX_TEMPFAIL)
E 127
D 103
				{
D 99
					QueueUp = TRUE;
E 99
I 99
					CurEnv->e_queueup = TRUE;
E 103
E 99
					to->q_flags |= QQUEUEUP;
D 103
				}
E 103
				else
D 127
# endif QUEUE
E 127
D 113
				{
E 113
					to->q_flags |= QBADADDR;
D 113
					giveresponse(i, TRUE, m);
				}
E 113
I 113
D 127
				giveresponse(i, TRUE, m);
E 127
I 127
				giveresponse(rcode, TRUE, m);
E 127
E 113
			}
# else SMTP
			syserr("trying to be clever");
# endif SMTP
		}

		/*
E 154
E 93
I 41
		**  If an error message has already been given, don't
		**	bother to send to this address.
		**
		**	>>>>>>>>>> This clause assumes that the local mailer
		**	>> NOTE >> cannot do any further aliasing; that
		**	>>>>>>>>>> function is subsumed by sendmail.
		*/

D 113
		if (bitset(QBADADDR, to->q_flags))
E 113
I 113
		if (bitset(QBADADDR|QQUEUEUP, to->q_flags))
E 113
			continue;

I 51
		/* save statistics.... */
D 68
		Stat.stat_nt[to->q_mailer]++;
		Stat.stat_bt[to->q_mailer] += kbytes(MsgSize);
E 68
I 68
D 154
		Stat.stat_nt[to->q_mailer->m_mno]++;
D 99
		Stat.stat_bt[to->q_mailer->m_mno] += kbytes(MsgSize);
E 99
I 99
		Stat.stat_bt[to->q_mailer->m_mno] += kbytes(CurEnv->e_msgsize);
E 154
I 154
		markstats(e, to);
E 154
E 99
E 68

E 51
		/*
E 41
		**  See if this user name is "special".
		**	If the user name has a slash in it, assume that this
D 100
		**	is a file -- send it off without further ado.
		**	Note that this means that editfcn's will not
		**	be applied to the message.  Also note that
		**	this type of addresses is not processed along
D 99
		**	with the others, so we fudge on the To person.
E 99
I 99
		**	with the others, so we fudge on the CurEnv->e_to person.
E 100
I 100
		**	is a file -- send it off without further ado.  Note
		**	that this type of addresses is not processed along
		**	with the others, so we fudge on the To person.
E 100
E 99
		*/

D 35
		if (m == Mailer[0])
E 35
I 35
D 45
		if (m == Mailer[M_LOCAL])
E 45
I 45
D 68
		if (m == Mailer[MN_LOCAL])
E 68
I 68
D 260
		if (m == LocalMailer)
E 260
I 260
D 495
		if (m == FileMailer)
E 495
I 495
		if (strcmp(m->m_mailer, "[FILE]") == 0)
E 495
E 260
E 68
E 45
E 35
		{
E 26
D 82
			if (index(user, '/') != NULL)
E 82
I 82
D 260
			if (user[0] == '/')
E 82
			{
D 58
				i = mailfile(user);
E 58
I 58
D 127
				i = mailfile(user, getctladdr(to));
E 58
				giveresponse(i, TRUE, m);
E 127
I 127
D 247
				rcode = mailfile(user, getctladdr(to));
E 247
I 247
				rcode = mailfile(user, getctladdr(to), e);
E 247
D 154
				giveresponse(rcode, TRUE, m);
E 154
I 154
D 161
				giveresponse(rcode, m);
E 161
I 161
				giveresponse(rcode, m, e);
I 227
				if (rcode == EX_OK)
					to->q_flags |= QSENT;
E 227
E 161
E 154
E 127
D 26
				return (i);
E 26
I 26
				continue;
E 26
			}
E 260
I 260
D 377
			rcode = mailfile(user, getctladdr(to), e);
D 290
			giveresponse(rcode, m, e);
E 290
I 290
			giveresponse(rcode, m, NULL, e);
E 377
I 377
D 392
			ADDRESS *caddr = getctladdr(to);

			rcode = mailfile(user, caddr, e);
			giveresponse(rcode, m, NULL, caddr, e);
E 392
I 392
D 501
			rcode = mailfile(user, ctladdr, e);
E 501
I 501
			rcode = mailfile(user, ctladdr, SFF_CREAT, e);
E 501
D 461
			giveresponse(rcode, m, NULL, ctladdr, e);
E 461
I 461
			giveresponse(rcode, m, NULL, ctladdr, xstart, e);
E 461
I 455
			e->e_nsent++;
E 455
E 392
E 377
E 290
			if (rcode == EX_OK)
I 455
			{
E 455
				to->q_flags |= QSENT;
I 455
				if (bitnset(M_LOCALMAILER, m->m_flags) &&
				    (e->e_receiptto != NULL ||
				     bitset(QPINGONSUCCESS, to->q_flags)))
				{
D 493
					to->q_flags |= QREPORT;
E 493
I 493
					to->q_flags |= QDELIVERED;
E 493
I 491
					to->q_status = "2.1.5";
E 491
					fprintf(e->e_xfp, "%s... Successfully delivered\n",
						to->q_paddr);
				}
			}
E 455
I 445
			to->q_statdate = curtime();
E 445
			continue;
E 260
		}
I 26

I 54
		/*
		**  Address is verified -- add this user to mailer
		**  argv, and add it to the print list of recipients.
		*/

I 93
		/* link together the chain of recipients */
D 94
		if (!bitset(QDONTSEND, to->q_flags))
		{
			to->q_tchain = tochain;
			tochain = to;
		}
E 94
I 94
		to->q_tchain = tochain;
		tochain = to;
E 94

E 93
E 54
D 41
		/*
		**  See if the user exists.
		**	Strictly, this is only needed to print a pretty
		**	error message.
		**
		**	>>>>>>>>>> This clause assumes that the local mailer
		**	>> NOTE >> cannot do any further aliasing; that
D 27
		**	>>>>>>>>>> function is subsumed by postbox.
E 27
I 27
		**	>>>>>>>>>> function is subsumed by sendmail.
E 27
		*/

D 34
		if (m == Mailer[0])
E 34
I 34
D 35
		if (m == Mailer[0] && !bitset(QGOODADDR, to->q_flags))
E 35
I 35
		if (bitset(QBADADDR, to->q_flags))
E 35
E 34
		{
D 34
			if (getpwnam(user) == NULL)
E 34
I 34
D 35
			if (bitset(QBADADDR, to->q_flags) || getpwnam(user) == NULL)
E 34
			{
				giveresponse(EX_NOUSER, TRUE, m);
				continue;
			}
E 35
I 35
			giveresponse(EX_NOUSER, TRUE, m);
			continue;
E 35
		}

E 41
		/* create list of users for error messages */
D 156
		if (tobuf[0] != '\0')
D 36
			strcat(tobuf, ",");
		strcat(tobuf, to->q_paddr);
E 36
I 36
			(void) strcat(tobuf, ",");
E 156
I 156
		(void) strcat(tobuf, ",");
E 156
		(void) strcat(tobuf, to->q_paddr);
E 36
D 154
		define('u', user);		/* to user */
I 35
		define('z', to->q_home);	/* user's home */
E 154
I 154
		define('u', user, e);		/* to user */
D 368
		define('z', to->q_home, e);	/* user's home */
E 368
I 368
		p = to->q_home;
		if (p == NULL && ctladdr != NULL)
			p = ctladdr->q_home;
		define('z', p, e);	/* user's home */
E 368
E 154
E 35

D 72
		/* expand out this user */
D 36
		expand(user, buf, &buf[sizeof buf - 1]);
E 36
I 36
D 52
		(void) expand(user, buf, &buf[sizeof buf - 1]);
E 52
I 52
		(void) expand(*mvp, buf, &buf[sizeof buf - 1]);
E 52
E 36
		*pvp++ = newstr(buf);
		if (pvp >= &pv[MAXPV - 2])
E 72
I 72
		/*
D 93
		**  Expand out this user into argument list or
		**  send it to our SMTP server.
E 93
I 93
		**  Expand out this user into argument list.
E 93
		*/

D 93
		if (clever)
E 72
		{
I 79
# ifdef SMTP
E 79
D 72
			/* allow some space for trailing parms */
			break;
E 72
I 72
D 73
			i = smtpmrcp(to);
E 73
I 73
			i = smtprcpt(to);
E 73
D 79
			if (i == EX_TEMPFAIL)
E 79
I 79
			if (i != EX_OK)
E 79
			{
D 79
				QueueUp = TRUE;
				to->q_flags |= QQUEUEUP;
E 79
I 79
# ifdef QUEUE
				if (i == EX_TEMPFAIL)
				{
					QueueUp = TRUE;
					to->q_flags |= QQUEUEUP;
				}
				else
# endif QUEUE
				{
					to->q_flags |= QBADADDR;
					giveresponse(i, TRUE, m);
				}
E 79
			}
D 79
			else if (i != EX_OK)
			{
				to->q_flags |= QBADADDR;
				giveresponse(i, TRUE, m);
			}
E 79
I 79
# else SMTP
			syserr("trying to be clever");
# endif SMTP
E 79
E 72
		}
I 72
		else
E 93
I 93
		if (!clever)
E 93
		{
D 100
			(void) expand(*mvp, buf, &buf[sizeof buf - 1]);
E 100
I 100
D 154
			expand(*mvp, buf, &buf[sizeof buf - 1], CurEnv);
E 154
I 154
D 474
			expand(*mvp, buf, &buf[sizeof buf - 1], e);
E 474
I 474
D 475
			expand(*mvp, buf, &buf[sizeof buf], e);
E 475
I 475
			expand(*mvp, buf, sizeof buf, e);
E 475
E 474
E 154
E 100
			*pvp++ = newstr(buf);
			if (pvp >= &pv[MAXPV - 2])
			{
				/* allow some space for trailing parms */
				break;
			}
		}
E 72
E 26
	}

I 34
	/* see if any addresses still exist */
	if (tobuf[0] == '\0')
I 72
	{
I 79
D 154
# ifdef SMTP
E 79
D 145
		if (clever)
E 145
I 145
		if (clever && !notopen)
E 145
D 109
			smtpquit(pv[0]);
E 109
I 109
			smtpquit(pv[0], FALSE);
E 109
I 79
# endif SMTP
I 101
D 102
		define('g', NULL);
E 102
I 102
		define('g', (char *) NULL);
E 154
I 154
		define('g', (char *) NULL, e);
I 239
D 303
		define('<', (char *) NULL, e);
E 303
E 239
E 154
E 102
E 101
E 79
E 72
		return (0);
I 72
	}
E 72

E 34
I 26
	/* print out messages as full list */
D 99
	To = tobuf;
E 99
I 99
D 154
	CurEnv->e_to = tobuf;
E 154
I 154
D 156
	e->e_to = tobuf;
E 156
I 156
	e->e_to = tobuf + 1;
E 156
E 154
E 99

E 26
D 5
# ifdef BADMAIL
E 5
	/*
D 5
	**  If the mailer doesn't return the proper
	**  exit statuses, check here to see if the
	**  user exists so that we can give a pretty
	**  error message.
E 5
I 5
D 26
	**  See if the user exists.
	**	Strictly, this is only needed to print a pretty
	**	error message.
	**
	**	>>>>>>>>>> This clause assumes that the local mailer
	**	>> NOTE >> cannot do any further aliasing; that
D 20
	**	>>>>>>>>>> function is subsumed by delivermail.
E 20
I 20
	**	>>>>>>>>>> function is subsumed by postbox.
E 26
I 26
	**  Fill out any parameters after the $u parameter.
E 26
E 20
E 5
	*/

D 23
	if (m == &Mailer[0])
E 23
I 23
D 26
	if (m == Mailer[0])
E 26
I 26
D 72
	while (*++mvp != NULL)
E 72
I 72
	while (!clever && *++mvp != NULL)
E 72
E 26
E 23
	{
D 26
		if (getpwnam(user) == NULL)
		{
			giveresponse(EX_NOUSER, TRUE, m);
			return (EX_NOUSER);
		}
E 26
I 26
D 36
		expand(*mvp, buf, &buf[sizeof buf - 1]);
E 36
I 36
D 100
		(void) expand(*mvp, buf, &buf[sizeof buf - 1]);
E 100
I 100
D 154
		expand(*mvp, buf, &buf[sizeof buf - 1], CurEnv);
E 154
I 154
D 474
		expand(*mvp, buf, &buf[sizeof buf - 1], e);
E 474
I 474
D 475
		expand(*mvp, buf, &buf[sizeof buf], e);
E 475
I 475
		expand(*mvp, buf, sizeof buf, e);
E 475
E 474
E 154
E 100
E 36
		*pvp++ = newstr(buf);
		if (pvp >= &pv[MAXPV])
D 280
			syserr("deliver: pv overflow after $u for %s", pv[0]);
E 280
I 280
			syserr("554 deliver: pv overflow after $u for %s", pv[0]);
E 280
E 26
	}
I 26
	*pvp++ = NULL;
E 26
D 5
# endif BADMAIL
E 5

	/*
D 19
	**  If the mailer wants a From line, insert a new editfcn.
	*/

D 14
	if (flagset(M_HDR, m->m_flags) && editfcn == NULL)
E 14
I 14
D 15
	if (flagset(M_HDR, m->m_flags) && editfcn == NULL && !GotHdr)
E 15
I 15
	if (flagset(M_HDR, m->m_flags) && editfcn == NULL && (!GotHdr || flagset(M_FHDR, m->m_flags)))
E 15
E 14
		editfcn = putheader;

	/*
E 19
	**  Call the mailer.
D 19
	**	The argument vector gets built, pipes through 'editfcn'
E 19
I 19
	**	The argument vector gets built, pipes
E 19
	**	are created as necessary, and we fork & exec as
D 19
	**	appropriate.  In the parent, we call 'editfcn'.
E 19
I 19
	**	appropriate.
I 72
	**	If we are running SMTP, we just need to clean up.
E 72
I 35
D 54
	**
	**	Notice the tacky hack to handle private mailers.
E 54
E 35
E 19
	*/
I 395

	/*XXX this seems a bit wierd */
D 403
	if (ctladdr == NULL && bitset(QGOODUID, e->e_from.q_flags))
E 403
I 403
D 498
	if (ctladdr == NULL && m != ProgMailer &&
E 498
I 498
	if (ctladdr == NULL && m != ProgMailer && m != FileMailer &&
E 498
	    bitset(QGOODUID, e->e_from.q_flags))
E 403
		ctladdr = &e->e_from;
E 395

I 223
D 289
	if (ctladdr == NULL)
E 289
I 289
D 392
	if (ctladdr == NULL && m != ProgMailer)
E 289
		ctladdr = &e->e_from;
E 392
E 223
I 154
D 206
	message(Arpa_Info, "Connecting to %s.%s...", host, m->m_name);

E 206
E 154
D 19
	pvp = buildargv(m->m_argv, m->m_flags, host, user, From.q_paddr);
E 19
I 19
D 26
	pvp = buildargv(m, host, user, From.q_paddr);
E 19
	if (pvp == NULL)
E 26
I 26
D 100
	if (editfcn == NULL)
		editfcn = putmessage;
E 100
I 35
D 37
	if (m == Mailer[M_PRIVATE])
	{
D 36
		expand("$z/.mailer", buf, &buf[sizeof buf - 1]);
E 36
I 36
		(void) expand("$z/.mailer", buf, &buf[sizeof buf - 1]);
E 36
		m->m_mailer = buf;
	}
E 37
E 35
D 58
	i = sendoff(m, pv, editfcn);
E 58
I 58
D 218
	if (ctladdr == NULL)
D 99
		ctladdr = &From;
E 99
I 99
D 154
		ctladdr = &CurEnv->e_from;
E 154
I 154
		ctladdr = &e->e_from;
E 218
I 210
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
E 210
I 207
D 231
	_res.options &= ~(RES_DEFNAMES | RES_DNSRCH);		/* XXX */
E 231
I 231
	if (ConfigLevel < 2)
		_res.options &= ~(RES_DEFNAMES | RES_DNSRCH);	/* XXX */
E 231
I 210
#endif
I 247
D 312
	mci = openmailer(m, pv, ctladdr, clever, e);
	if (mci == NULL)
	{
		/* catastrophic error */
D 272
		rcode = -1;
E 272
I 272
		rcode = EX_OSERR;
E 272
		goto give_up;
	}
	else if (mci->mci_state != MCIS_OPEN)
	{
		/* couldn't open the mailer */
		rcode = mci->mci_exitstat;
I 252
		errno = mci->mci_errno;
E 252
		if (rcode == EX_OK)
		{
			/* shouldn't happen */
I 268
D 280
			syserr("deliver: rcode=%d, mci_state=%d, sig=%s",
E 280
I 280
			syserr("554 deliver: rcode=%d, mci_state=%d, sig=%s",
E 280
				rcode, mci->mci_state, firstsig);
E 268
			rcode = EX_SOFTWARE;
		}
	}
	else if (!clever)
	{
		/*
		**  Format and send message.
		*/
E 312

D 312
		putfromline(mci->mci_out, m, e);
		(*e->e_puthdr)(mci->mci_out, m, e);
		putline("\n", mci->mci_out, m);
		(*e->e_putbody)(mci->mci_out, m, e);

		/* get the exit status */
D 311
		rcode = endmailer(mci, pv[0]);
E 311
I 311
		rcode = endmailer(mci, e, pv);
E 311
	}
	else
E 247
E 210
E 207
E 154
E 99
I 79
D 205
# ifdef SMTP
E 79
D 72
	i = sendoff(m, pv, editfcn, ctladdr);
E 72
I 72
	if (clever)
	{
I 197
D 204
# ifdef MXDOMAIN
E 204
		expand("\001w", buf, &buf[sizeof buf - 1], e);
D 199
		if ((nmx = getmxrr(host, mxhosts, MAXMXHOSTS, buf)) < 0)
E 199
I 199
D 201
		if ((Nmx = getmxrr(host, MxHosts, MAXMXHOSTS, buf)) < 0)
E 201
I 201
		if (host[0] == '[')
		{
E 205
I 205
#ifdef SMTP
D 210
	if (clever) {
E 210
I 210
D 247
	if (clever)
E 247
	{
I 246
D 247
		register MCONINFO *mci;
E 247
I 247
		/*
		**  Send the MAIL FROM: protocol
		*/
E 247

E 246
E 210
D 215
		expand("\001w", buf, &buf[sizeof(buf) - 1], e);
E 215
D 247
		rcode = EX_OK;
D 210
		if (host[0] == '[') {
E 210
I 210
#ifdef NAMED_BIND
D 215
		if (host[0] != '[')
E 215
I 215
		if (host[0] && host[0] != '[')
E 247
I 247
		rcode = smtpmailfrom(m, mci, e);
		if (rcode == EX_OK)
E 247
E 215
		{
I 215
D 232
			expand("\001w", buf, &buf[sizeof(buf) - 1], e);
E 232
I 232
D 247
			expand("\001j", buf, &buf[sizeof(buf) - 1], e);
E 232
E 215
			Nmx = getmxrr(host, MxHosts, buf, &rcode);
		}
		else
#endif
		{
E 210
E 205
			Nmx = 1;
			MxHosts[0] = host;
D 205
			rcode = EX_OK;
E 205
D 207
		}
D 205
		else if ((Nmx = getmxrr(host, MxHosts, MAXMXHOSTS, buf)) < 0)
E 201
E 199
		{
			/*
			 * Map errors into standard values
			 */
D 199
			if (nmx == -1)
E 199
I 199
			if (Nmx == -1)
E 199
				rcode = EX_TEMPFAIL;
D 199
			else if (nmx == -3)
E 199
I 199
			else if (Nmx == -3)
E 199
				rcode = EX_NOHOST;
			else
				rcode = EX_UNAVAILABLE;
		}
		else
			rcode = EX_OK;
D 204
#else MXDOMAIN
D 199
		nmx = 1;
		mxhosts[0] = q->q_host;
E 199
I 199
		Nmx = 1;
		MxHosts[0] = q->q_host;
E 199
		rcode = EX_OK;
#endif
E 204
E 197
D 100
		i = smtpfinish(m, editfcn);
E 100
I 100
D 127
		i = smtpfinish(m, CurEnv);
E 100
D 109
		smtpquit(pv[0]);
E 109
I 109
D 125
		smtpquit(pv[0], TRUE);
E 125
I 125
		if (i != EX_OK)
			giveresponse(i, TRUE, m);
		smtpquit(pv[0], i == EX_OK);
E 127
I 127
D 154
		rcode = smtpfinish(m, CurEnv);
E 154
I 154
		/* send the initial SMTP protocol */
D 166
		rcode = smtpinit(m, pv, (ADDRESS *) NULL);
E 166
I 166
D 197
		rcode = smtpinit(m, pv);
E 197
I 197
		if (rcode == EX_OK)
			rcode = smtpinit(m, pv);
E 205
I 205
		else if ((Nmx = getmxrr(host, MxHosts, buf, &rcode)) >= 0 &&
		    (rcode = smtpinit(m, pv)) == EX_OK) {
E 205
E 197
E 166
D 206

E 206
I 206
			message(Arpa_Info, "Connecting to %s.%s...", MxHosts[0],
			    m->m_name);
E 206
D 156
		/* send the recipient list */
		for (to = tochain; to != NULL; to = to->q_tchain)
E 156
I 156
D 205
		if (rcode == EX_OK)
E 156
		{
E 205
D 156
			int i;
E 156
I 156
			/* send the recipient list */
			tobuf[0] = '\0';
D 205
			for (to = tochain; to != NULL; to = to->q_tchain)
			{
				int i;
E 205
I 205
			for (to = tochain; to; to = to->q_tchain) {
				register int i;
				register char *t = tobuf;
E 207
I 207
D 210
		} else
			Nmx = getmxrr(host, MxHosts, buf, &rcode);
		if (Nmx >= 0) {
E 210
I 210
		}
		if (Nmx >= 0)
		{
E 210
D 246
			message(Arpa_Info, "Connecting to %s (%s)...",
			    MxHosts[0], m->m_name);
D 245
			if ((rcode = smtpinit(m, pv)) == EX_OK) {
E 245
I 245
			if ((rcode = smtpinit(m, mci, pv)) == EX_OK)
E 246
I 246
			extern MCONINFO *smtpinit();
E 247
I 247
			register char *t = tobuf;
			register int i;
E 247

D 247
			mci = smtpinit(m, pv, e);
			if (mci != NULL &&
			    mci->mci_state == MCIS_OPEN &&
			    mci->mci_exitstat == EX_OK &&
			    smtpmailfrom(m, mci, e) == EX_OK)
E 247
I 247
			/* send the recipient list */
			tobuf[0] = '\0';
			for (to = tochain; to != NULL; to = to->q_tchain)
E 247
E 246
			{
E 245
I 212
D 247
				register char *t = tobuf;
				register int i;

E 212
				/* send the recipient list */
				tobuf[0] = '\0';
D 245
				for (to = tochain; to; to = to->q_tchain) {
E 245
I 245
				for (to = tochain; to != NULL; to = to->q_tchain)
E 247
I 247
				e->e_to = to->q_paddr;
				if ((i = smtprcpt(to, m, mci, e)) != EX_OK)
E 247
				{
E 245
D 212
					register int i;
					register char *t = tobuf;
E 207
E 205
E 156

E 212
D 156
			if (rcode == EX_OK)
E 156
I 156
D 207
				e->e_to = to->q_paddr;
E 156
D 166
				i = smtprcpt(to);
E 166
I 166
				i = smtprcpt(to, m);
E 166
I 156
D 205
				if (i != EX_OK)
				{
E 205
I 205
				if (i != EX_OK) {
E 205
D 160
					if (i == EX_TEMPFAIL)
						to->q_flags |= QQUEUEUP;
					else
						to->q_flags |= QBADADDR;
E 160
I 160
					markfailure(e, to, i);
E 160
D 161
					giveresponse(i, m);
E 161
I 161
					giveresponse(i, m, e);
E 207
I 207
D 247
					e->e_to = to->q_paddr;
D 245
					if ((i = smtprcpt(to, m)) != EX_OK) {
E 245
I 245
D 246
					if ((i = smtprcpt(to, m, mci)) != EX_OK)
E 246
I 246
					if ((i = smtprcpt(to, m, mci, e)) != EX_OK)
E 246
					{
E 245
						markfailure(e, to, i);
						giveresponse(i, m, e);
					}
D 245
					else {
E 245
I 245
					else
					{
E 245
						*t++ = ',';
						for (p = to->q_paddr; *p; *t++ = *p++);
					}
E 247
I 247
					markfailure(e, to, i);
D 290
					giveresponse(i, m, e);
E 290
I 290
					giveresponse(i, m, mci, e);
E 290
E 247
E 207
E 161
				}
I 207
D 247

				/* now send the data */
				if (tobuf[0] == '\0')
					e->e_to = NULL;
E 247
E 207
D 205
				else
				{
D 188
					strcat(tobuf, ",");
					strcat(tobuf, to->q_paddr);
E 188
I 188
					(void) strcat(tobuf, ",");
					(void) strcat(tobuf, to->q_paddr);
E 205
I 205
D 245
				else {
E 245
I 245
				else
				{
E 245
D 207
					*t++ = ',';
					for (p = to->q_paddr; *p; *t++ = *p++);
E 207
I 207
D 247
					e->e_to = tobuf + 1;
D 245
					rcode = smtpdata(m, e);
E 245
I 245
					rcode = smtpdata(m, mci, e);
E 247
I 247
					*t++ = ',';
					for (p = to->q_paddr; *p; *t++ = *p++)
						continue;
E 247
E 245
E 207
E 205
E 188
				}
I 247
			}
E 247
D 207
			}
E 207

D 207
			/* now send the data */
			if (tobuf[0] == '\0')
				e->e_to = NULL;
E 156
D 205
			else
D 156
				i = rcode;
			if (i != EX_OK)
E 156
			{
E 205
I 205
			else {
E 205
D 156
				if (i == EX_TEMPFAIL)
					to->q_flags |= QQUEUEUP;
				else
					to->q_flags |= QBADADDR;
				giveresponse(rcode, m);
E 156
I 156
				e->e_to = tobuf + 1;
D 166
				rcode = smtpfinish(m, e);
E 166
I 166
				rcode = smtpdata(m, e);
E 207
I 207
D 247
				/* now close the connection */
D 246
				smtpquit(m);
E 246
I 246
				smtpquit(m, mci, e);
E 247
I 247
			/* now send the data */
			if (tobuf[0] == '\0')
			{
				e->e_to = NULL;
				if (bitset(MCIF_CACHED, mci->mci_flags))
					smtprset(m, mci, e);
E 247
E 246
E 207
E 166
E 156
			}
I 247
			else
			{
				e->e_to = tobuf + 1;
				rcode = smtpdata(m, mci, e);
			}

			/* now close the connection */
			if (!bitset(MCIF_CACHED, mci->mci_flags))
				smtpquit(m, mci, e);
E 247
D 156
		}
E 156
D 207

D 156
		/* now send the closing protocol */
		if (rcode == EX_OK)
			rcode = smtpfinish(m, e);
E 154
		if (rcode != EX_OK)
D 154
			giveresponse(rcode, TRUE, m);
E 154
I 154
			giveresponse(rcode, m);
E 154
		smtpquit(pv[0], rcode == EX_OK);
E 156
I 156
			/* now close the connection */
D 166
			smtpquit(pv[0]);
E 166
I 166
D 179
			smtpquit(pv[0], m);
E 179
I 179
			smtpquit(m);
E 207
E 179
E 166
		}
E 156
E 127
E 125
E 109
	}
D 247
	else
I 79
D 205
# endif SMTP
E 205
I 205
#endif /* SMTP */
E 247
I 247
#else /* not SMTP */
E 247
I 206
	{
I 226
D 247
		static int sendoff();

E 226
D 207
		message(Arpa_Info, "Connecting to %s.%s...", host, m->m_name);
E 207
I 207
		message(Arpa_Info, "Connecting to %s (%s)...", host, m->m_name);
E 207
E 206
E 205
E 79
D 100
		i = sendoff(m, pv, editfcn, ctladdr);
E 100
I 100
D 127
		i = sendoff(m, pv, ctladdr);
E 127
I 127
D 154
		rcode = sendoff(m, pv, ctladdr);
E 154
I 154
D 159
		rcode = sendoff(e, m, pv, ctladdr);
E 159
I 159
D 166
		rcode = sendoff(e, m, pv, ctladdr, FALSE);
E 166
I 166
		rcode = sendoff(e, m, pv, ctladdr);
E 247
I 247
D 280
		syserr("deliver: need SMTP compiled to use clever mailer");
E 280
I 280
		syserr("554 deliver: need SMTP compiled to use clever mailer");
E 280
D 272
		rcode = -1;
E 272
I 272
		rcode = EX_CONFIG;
E 272
		goto give_up;
E 247
I 206
	}
I 247
#endif /* SMTP */
E 247
I 210
#ifdef NAMED_BIND
E 210
I 207
D 231
	_res.options |= RES_DEFNAMES | RES_DNSRCH;	/* XXX */
E 231
I 231
	if (ConfigLevel < 2)
		_res.options |= RES_DEFNAMES | RES_DNSRCH;	/* XXX */
E 231
I 210
#endif
E 210
E 207
E 206
E 166
E 159
E 154
E 127
E 100
E 72
E 58

I 247
	/* arrange a return receipt if requested */
D 278
	if (e->e_receiptto != NULL && bitnset(M_LOCAL, m->m_flags))
E 278
I 278
	if (e->e_receiptto != NULL && bitnset(M_LOCALMAILER, m->m_flags))
E 278
	{
		e->e_flags |= EF_SENDRECEIPT;
		/* do we want to send back more info? */
	}

E 247
I 69
	/*
D 156
	**  If we got a temporary failure, arrange to queue the
	**  addressees.
E 156
I 156
	**  Do final status disposal.
	**	We check for something in tobuf for the SMTP case.
	**	If we got a temporary failure, arrange to queue the
	**		addressees.
E 156
	*/

I 247
  give_up:
E 247
I 79
D 127
# ifdef QUEUE
E 79
	if (i == EX_TEMPFAIL)
E 127
I 127
D 156
	if (rcode == EX_TEMPFAIL)
E 156
I 156
	if (tobuf[0] != '\0')
D 161
		giveresponse(rcode, m);
E 161
I 161
D 290
		giveresponse(rcode, m, e);
E 290
I 290
		giveresponse(rcode, m, mci, e);
E 290
E 161
D 227
	if (rcode != EX_OK)
E 156
E 127
D 206
	{
E 206
D 99
		QueueUp = TRUE;
E 99
I 99
D 103
		CurEnv->e_queueup = TRUE;
E 103
E 99
D 76
		for (to = firstto; to != NULL; to = to->q_next)
		{
			if (bitset(QBADADDR, to->q_flags))
				continue;
E 76
I 76
		for (to = tochain; to != NULL; to = to->q_tchain)
E 227
I 227
	for (to = tochain; to != NULL; to = to->q_tchain)
I 247
	{
E 247
		if (rcode != EX_OK)
E 227
E 76
D 156
			to->q_flags |= QQUEUEUP;
E 156
I 156
D 160
		{
			if (rcode == EX_TEMPFAIL)
				to->q_flags |= QQUEUEUP;
			else
				to->q_flags |= QBADADDR;
		}
E 160
I 160
			markfailure(e, to, rcode);
I 227
		else
I 266
		{
E 266
			to->q_flags |= QSENT;
I 266
			e->e_nsent++;
		}
E 266
I 247
	}
E 247
E 227
E 160
E 156
D 76
		}
E 76
D 206
	}
E 206
I 79
D 127
# endif QUEUE
E 127
E 79

I 247
	/*
	**  Restore state and return.
	*/

E 247
E 69
I 66
	errno = 0;
I 101
D 102
	define('g', NULL);
E 102
I 102
D 154
	define('g', (char *) NULL);
E 154
I 154
	define('g', (char *) NULL, e);
I 239
D 303
	define('<', (char *) NULL, e);
E 303
E 239
E 154
E 102
E 101
E 66
D 127
	return (i);
E 127
I 127
	return (rcode);
I 160
}
/*
**  MARKFAILURE -- mark a failure on a specific address.
**
**	Parameters:
**		e -- the envelope we are sending.
**		q -- the address to mark.
**		rcode -- the code signifying the particular failure.
**
**	Returns:
**		none.
**
**	Side Effects:
**		marks the address (and possibly the envelope) with the
**			failure so that an error will be returned or
**			the message will be queued, as appropriate.
*/

markfailure(e, q, rcode)
	register ENVELOPE *e;
	register ADDRESS *q;
	int rcode;
{
I 309
	char buf[MAXLINE];
	extern char *pintvl();

E 309
	if (rcode == EX_OK)
		return;
D 222
	else if (rcode != EX_TEMPFAIL)
E 222
I 222
	else if (rcode != EX_TEMPFAIL && rcode != EX_IOERR && rcode != EX_OSERR)
E 222
		q->q_flags |= QBADADDR;
D 309
	else if (curtime() > e->e_ctime + TimeOut)
E 309
I 309
	else if (curtime() > e->e_ctime + TimeOuts.to_q_return)
E 309
	{
D 309
		extern char *pintvl();
I 161
		char buf[MAXLINE];
E 161

E 309
		if (!bitset(EF_TIMEOUT, e->e_flags))
D 161
			message(Arpa_Info, "Cannot send message for %s",
E 161
I 161
		{
			(void) sprintf(buf, "Cannot send message for %s",
E 161
D 309
				pintvl(TimeOut, FALSE));
E 309
I 309
				pintvl(TimeOuts.to_q_return, FALSE));
E 309
I 161
			if (e->e_message != NULL)
				free(e->e_message);
			e->e_message = newstr(buf);
D 280
			message(Arpa_Info, buf);
E 280
I 280
			message(buf);
E 280
		}
E 161
		q->q_flags |= QBADADDR;
		e->e_flags |= EF_TIMEOUT;
I 267
		fprintf(e->e_xfp, "421 %s... Message timed out\n", q->q_paddr);
E 267
	}
	else
I 309
	{
E 309
		q->q_flags |= QQUEUEUP;
I 309
		if (TimeOuts.to_q_warning > 0 &&
		    curtime() > e->e_ctime + TimeOuts.to_q_warning)
		{
			if (!bitset(EF_WARNING, e->e_flags) &&
			    e->e_class >= 0)
			{
				(void) sprintf(buf,
					"warning: cannot send message for %s",
					pintvl(TimeOuts.to_q_warning, FALSE));
				if (e->e_message != NULL)
					free(e->e_message);
				e->e_message = newstr(buf);
				message(buf);
				e->e_flags |= EF_WARNING|EF_TIMEOUT;
			}
			fprintf(e->e_xfp,
				"%s... Warning: message still undelivered after %s\n",
				q->q_paddr, pintvl(TimeOuts.to_q_warning, FALSE));
			fprintf(e->e_xfp, "Will keep trying until message is %s old\n",
				pintvl(TimeOuts.to_q_return, FALSE));
		}
	}
E 309
E 160
E 127
}
/*
I 48
**  DOFORK -- do a fork, retrying a couple of times on failure.
**
**	This MUST be a macro, since after a vfork we are running
**	two processes on the same stack!!!
**
**	Parameters:
**		none.
**
**	Returns:
**		From a macro???  You've got to be kidding!
**
**	Side Effects:
**		Modifies the ==> LOCAL <== variable 'pid', leaving:
**			pid of child in parent, zero in child.
**			-1 on unrecoverable error.
**
**	Notes:
**		I'm awfully sorry this looks so awful.  That's
**		vfork for you.....
*/

# define NFORKTRIES	5
D 148
# ifdef VFORK
E 148
I 148
D 241
# ifdef VMUNIX
E 148
# define XFORK	vfork
D 148
# else VFORK
E 148
I 148
# else VMUNIX
E 148
# define XFORK	fork
D 148
# endif VFORK
E 148
I 148
# endif VMUNIX
E 241
E 148

I 241
# ifndef FORK
# define FORK	fork
# endif

E 241
# define DOFORK(fORKfN) \
{\
	register int i;\
\
D 189
	for (i = NFORKTRIES; i-- > 0; )\
E 189
I 189
	for (i = NFORKTRIES; --i >= 0; )\
E 189
	{\
		pid = fORKfN();\
		if (pid >= 0)\
			break;\
D 102
		sleep((unsigned) NFORKTRIES - i);\
E 102
I 102
D 189
		sleep(NFORKTRIES - i);\
E 189
I 189
		if (i > 0)\
D 194
			sleep(NFORKTRIES - i);\
E 194
I 194
			sleep((unsigned) NFORKTRIES - i);\
E 194
E 189
E 102
	}\
}
/*
I 70
**  DOFORK -- simple fork interface to DOFORK.
**
**	Parameters:
**		none.
**
**	Returns:
**		pid of child in parent.
**		zero in child.
**		-1 on error.
**
**	Side Effects:
**		returns twice, once in parent and once in child.
*/

dofork()
{
	register int pid;

	DOFORK(fork);
	return (pid);
}
/*
E 70
E 48
D 247
**  SENDOFF -- send off call to mailer & collect response.
**
**	Parameters:
I 154
**		e -- the envelope to mail.
E 154
**		m -- mailer descriptor.
**		pvp -- parameter vector to send to it.
D 100
**		editfcn -- function to pipe it through.
E 100
I 58
**		ctladdr -- an address pointer controlling the
**			user/groupid etc. of the mailer.
I 159
D 166
**		crlf -- set if we want CRLF on the end of lines.
E 166
E 159
E 58
**
**	Returns:
**		exit status of mailer.
**
**	Side Effects:
**		none.
*/
D 207

E 207
I 207
static
E 207
I 31
D 48
#define NFORKTRIES	5

E 48
E 31
D 58
sendoff(m, pvp, editfcn)
E 58
I 58
D 100
sendoff(m, pvp, editfcn, ctladdr)
E 100
I 100
D 154
sendoff(m, pvp, ctladdr)
E 100
E 58
	struct mailer *m;
E 154
I 154
D 159
sendoff(e, m, pvp, ctladdr)
E 159
I 159
D 166
sendoff(e, m, pvp, ctladdr, crlf)
E 166
I 166
sendoff(e, m, pvp, ctladdr)
E 166
E 159
	register ENVELOPE *e;
	MAILER *m;
E 154
	char **pvp;
D 100
	int (*editfcn)();
E 100
I 58
	ADDRESS *ctladdr;
I 159
D 166
	bool crlf;
E 166
E 159
E 58
{
D 72
	auto int st;
E 72
I 72
D 243
	auto FILE *mfile;
	auto FILE *rfile;
E 243
E 72
	register int i;
I 245
	register MCONINFO *mci;
	extern MCONINFO *openmailer();
E 245
I 72
D 100
	extern putmessage();
E 100
E 72
D 243
	int pid;
E 243
I 72

	/*
	**  Create connection to mailer.
	*/

D 243
	pid = openmailer(m, pvp, ctladdr, FALSE, &mfile, &rfile);
	if (pid < 0)
E 243
I 243
	mci = openmailer(m, pvp, ctladdr, FALSE);
	if (mci == NULL)
E 243
		return (-1);

	/*
	**  Format and send message.
I 154
D 163
	**	We ignore broken pipes so that the mailer need not read
	**	its input if it is not convenient to do so (e.g., on
	**	some error).
E 163
E 154
	*/

D 163
	(void) signal(SIGPIPE, SIG_IGN);
E 163
D 100
	if (editfcn == NULL)
		editfcn = putmessage;
	
	(*editfcn)(mfile, m, FALSE);
E 100
I 100
D 159
	putfromline(mfile, m);
D 154
	(*CurEnv->e_puthdr)(mfile, m, CurEnv);
E 154
I 154
	(*e->e_puthdr)(mfile, m, e);
E 159
I 159
D 166
	putfromline(mfile, m, crlf);
	(*e->e_puthdr)(mfile, m, e, crlf);
E 159
E 154
	fprintf(mfile, "\n");
D 154
	(*CurEnv->e_putbody)(mfile, m, FALSE);
E 154
I 154
D 157
	(*e->e_putbody)(mfile, m, FALSE);
E 157
I 157
D 159
	(*e->e_putbody)(mfile, m, FALSE, e);
E 159
I 159
	(*e->e_putbody)(mfile, m, FALSE, e, crlf);
E 166
I 166
D 243
	putfromline(mfile, m);
	(*e->e_puthdr)(mfile, m, e);
	putline("\n", mfile, m);
	(*e->e_putbody)(mfile, m, e);
E 166
E 159
E 157
E 154
E 100
	(void) fclose(mfile);
I 220
	if (rfile != NULL)
		(void) fclose(rfile);
E 243
I 243
	putfromline(mci->mci_out, m);
	(*e->e_puthdr)(mci->mci_out, m, e);
	putline("\n", mci->mci_out, m);
	(*e->e_putbody)(mci->mci_out, m, e);
E 243
E 220

D 243
	i = endmailer(pid, pvp[0]);
E 243
I 243
	i = endmailer(mci, pvp[0]);
E 243
D 154
	giveresponse(i, TRUE, m);
E 154
I 154
D 156
	giveresponse(i, m);
E 156
E 154
I 89

	/* arrange a return receipt if requested */
D 99
	if (RetReceipt && bitset(M_LOCAL, m->m_flags) && i == EX_OK)
E 99
I 99
D 128
	if (CurEnv->e_retreceipt && bitset(M_LOCAL, m->m_flags) && i == EX_OK)
E 128
I 128
D 154
	if (CurEnv->e_receiptto != NULL && bitset(M_LOCAL, m->m_flags))
E 154
I 154
D 168
	if (e->e_receiptto != NULL && bitset(M_LOCAL, m->m_flags))
E 168
I 168
	if (e->e_receiptto != NULL && bitnset(M_LOCAL, m->m_flags))
E 168
E 154
E 128
E 99
	{
D 99
		SendReceipt = TRUE;
		fprintf(Xscript, "%s... successfully delivered\n", To);
E 99
I 99
D 152
		CurEnv->e_sendreceipt = TRUE;
D 128
		fprintf(Xscript, "%s... successfully delivered\n", CurEnv->e_to);
E 128
I 128
		if (ExitStat == EX_OK)
E 152
I 152
D 154
		CurEnv->e_flags |= EF_SENDRECEIPT;
E 154
I 154
		e->e_flags |= EF_SENDRECEIPT;
E 154
D 156
		if (ExitStat == EX_OK && Xscript != NULL)
E 152
			fprintf(Xscript, "%s... successfully delivered\n",
D 154
				CurEnv->e_to);
E 154
I 154
				e->e_to);
E 156
E 154
E 128
E 99
		/* do we want to send back more info? */
	}

E 89
	return (i);
}
/*
E 247
**  ENDMAILER -- Wait for mailer to terminate.
**
**	We should never get fatal errors (e.g., segmentation
**	violation), so we report those specially.  For other
**	errors, we choose a status message (into statmsg),
**	and if it represents an error, we print it.
**
**	Parameters:
**		pid -- pid of mailer.
D 311
**		name -- name of mailer (for error messages).
E 311
I 311
**		e -- the current envelope.
**		pv -- the parameter vector that invoked the mailer
**			(for error messages).
E 311
**
**	Returns:
**		exit code of mailer.
**
**	Side Effects:
**		none.
*/

D 243
endmailer(pid, name)
	int pid;
E 243
I 243
D 311
endmailer(mci, name)
E 311
I 311
endmailer(mci, e, pv)
E 311
D 247
	register MCONINFO *mci;
E 247
I 247
	register MCI *mci;
E 247
E 243
D 311
	char *name;
E 311
I 311
	register ENVELOPE *e;
	char **pv;
E 311
{
D 154
	register int i;
	auto int st;
E 154
I 154
	int st;
E 154

I 243
	/* close any connections */
	if (mci->mci_in != NULL)
D 301
		(void) fclose(mci->mci_in);
E 301
I 301
D 311
		(void) xfclose(mci->mci_in, name, "mci_in");
E 311
I 311
		(void) xfclose(mci->mci_in, pv[0], "mci_in");
E 311
E 301
	if (mci->mci_out != NULL)
D 301
		(void) fclose(mci->mci_out);
E 301
I 301
D 311
		(void) xfclose(mci->mci_out, name, "mci_out");
E 311
I 311
		(void) xfclose(mci->mci_out, pv[0], "mci_out");
E 311
E 301
	mci->mci_in = mci->mci_out = NULL;
	mci->mci_state = MCIS_CLOSED;
D 247
	if (bitset(MCIF_TEMP, mci->mci_flags))
D 246
		xfree(mci);
E 246
I 246
		free(mci);
E 247
E 246

E 243
I 90
	/* in the IPC case there is nothing to wait for */
D 245
	if (pid == 0)
E 245
I 245
	if (mci->mci_pid == 0)
E 245
		return (EX_OK);

	/* wait for the mailer process to die and collect status */
E 90
D 132
	while ((i = wait(&st)) > 0 && i != pid)
		continue;
E 132
I 132
D 154
	do
E 154
I 154
D 245
	st = waitfor(pid);
E 245
I 245
	st = waitfor(mci->mci_pid);
E 245
	if (st == -1)
E 154
	{
D 154
		errno = 0;
		i = wait(&st);
D 133
		if (i < 0 && errno == EINTR)
			continue;
	} while (i >= 0 && i != pid);
E 133
I 133
	} while ((i >= 0 && i != pid) || errno == EINTR);
E 133
E 132
	if (i < 0)
	{
		syserr("wait");
		return (-1);
E 154
I 154
D 311
		syserr("endmailer %s: wait", name);
E 311
I 311
		syserr("endmailer %s: wait", pv[0]);
E 311
		return (EX_SOFTWARE);
E 154
	}
I 90

	/* see if it died a horrid death */
E 90
	if ((st & 0377) != 0)
	{
D 154
		syserr("%s: stat %o", name, st);
E 154
I 154
D 190
		syserr("endmailer %s: stat %o", name, st);
E 154
		ExitStat = EX_UNAVAILABLE;
D 154
		return (-1);
E 154
I 154
		return (EX_UNAVAILABLE);
E 190
I 190
D 311
		syserr("mailer %s died with signal %o", name, st);
E 311
I 311
		syserr("mailer %s died with signal %o", pv[0], st);

		/* log the arguments */
		if (e->e_xfp != NULL)
		{
			register char **av;

			fprintf(e->e_xfp, "Arguments:");
			for (av = pv; *av != NULL; av++)
				fprintf(e->e_xfp, " %s", *av);
			fprintf(e->e_xfp, "\n");
		}

E 311
		ExitStat = EX_TEMPFAIL;
		return (EX_TEMPFAIL);
E 190
E 154
	}
I 90

	/* normal death -- return status */
E 90
D 154
	i = (st >> 8) & 0377;
	return (i);
E 154
I 154
	st = (st >> 8) & 0377;
	return (st);
E 154
}
/*
**  OPENMAILER -- open connection to mailer.
**
**	Parameters:
**		m -- mailer descriptor.
**		pvp -- parameter vector to pass to mailer.
**		ctladdr -- controlling address for user.
**		clever -- create a full duplex connection.
D 243
**		pmfile -- pointer to mfile (to mailer) connection.
**		prfile -- pointer to rfile (from mailer) connection.
E 243
**
**	Returns:
D 90
**		pid of mailer.
E 90
I 90
D 243
**		pid of mailer ( > 0 ).
E 90
**		-1 on error.
I 90
**		zero on an IPC connection.
E 243
I 243
**		The mail connection info struct for this connection.
**		NULL on failure.
E 243
E 90
**
**	Side Effects:
**		creates a mailer in a subprocess.
*/

D 243
openmailer(m, pvp, ctladdr, clever, pmfile, prfile)
E 243
I 243
D 247
MCONINFO *
openmailer(m, pvp, ctladdr, clever)
E 247
I 247
MCI *
openmailer(m, pvp, ctladdr, clever, e)
E 247
E 243
D 154
	struct mailer *m;
E 154
I 154
	MAILER *m;
E 154
	char **pvp;
	ADDRESS *ctladdr;
	bool clever;
I 247
	ENVELOPE *e;
E 247
D 243
	FILE **pmfile;
	FILE **prfile;
E 243
{
	int pid;
I 245
D 247
	register MCONINFO *mci;
E 247
I 247
	register MCI *mci;
E 247
E 245
E 72
D 71
	int pvect[2];
E 71
I 71
	int mpvect[2];
I 72
	int rpvect[2];
E 72
E 71
D 219
	FILE *mfile;
D 72
	extern putmessage();
E 72
I 72
	FILE *rfile;
E 219
I 219
D 243
	FILE *mfile = NULL;
	FILE *rfile = NULL;
E 243
E 219
E 72
D 39
	extern pipesig();
E 39
	extern FILE *fdopen();
I 196
D 197
	char buf[MAXNAME];
E 197
E 196

E 312
D 213
# ifdef DEBUG
E 213
D 117
	if (Debug)
E 117
I 117
	if (tTd(11, 1))
E 117
E 26
	{
D 26
		usrerr("name too long");
		return (-1);
E 26
I 26
D 72
		printf("Sendoff:\n");
E 72
I 72
D 134
		printf("openmailer:\n");
E 134
I 134
		printf("openmailer:");
E 134
E 72
D 312
		printav(pvp);
E 312
I 312
		printav(pv);
E 312
E 26
	}
I 26
D 213
# endif DEBUG
E 213
I 66
	errno = 0;
I 428
#if NAMED_BIND
	h_errno = 0;
#endif
E 428
E 66

I 192
D 458
	CurHostName = m->m_mailer;
E 458
I 458
	CurHostName = NULL;
E 458

E 192
I 90
D 154
# ifdef DAEMON
E 154
	/*
	**  Deal with the special case of mail handled through an IPC
	**  connection.
	**	In this case we don't actually fork.  We must be
	**	running SMTP for this to work.  We will return a
	**	zero pid to indicate that we are running IPC.
I 170
	**  We also handle a debug version that just talks to stdin/out.
E 170
	*/
I 170

I 312
	curhost = NULL;
I 356
	SmtpPhase = NULL;
I 371
	mci = NULL;
E 371
E 356

I 361
D 504
#ifdef XDEBUG
E 504
I 504
#if XDEBUG
E 504
	{
		char wbuf[MAXLINE];

		/* make absolutely certain 0, 1, and 2 are in use */
		sprintf(wbuf, "%s... openmailer(%s)", e->e_to, m->m_name);
		checkfd012(wbuf);
	}
#endif

I 431
	/* check for 8-bit available */
	if (bitset(EF_HAS8BIT, e->e_flags) &&
	    bitnset(M_7BITS, m->m_flags) &&
D 505
	    !bitset(MM_MIME8BIT, MimeMode))
E 505
I 505
	    (!bitset(MM_MIME8BIT, MimeMode) ||
	     bitset(EF_DONT_MIME, e->e_flags)))
E 505
	{
		usrerr("554 Cannot send 8-bit data to 7-bit destination");
		rcode = EX_DATAERR;
I 492
		e->e_status = "5.6.3";
E 492
		goto give_up;
	}

E 431
D 371

E 371
E 361
E 312
D 213
#ifdef DEBUG
E 213
	/* check for Local Person Communication -- not for mortals!!! */
	if (strcmp(m->m_mailer, "[LPC]") == 0)
	{
D 243
		*pmfile = stdout;
		*prfile = stdin;
		return (0);
E 243
I 243
D 245
		mci = xalloc(sizeof *mci);
E 245
I 245
D 247
		mci = (MCONINFO *) xalloc(sizeof *mci);
E 247
I 247
		mci = (MCI *) xalloc(sizeof *mci);
I 249
		bzero((char *) mci, sizeof *mci);
E 249
E 247
E 245
		mci->mci_in = stdin;
		mci->mci_out = stdout;
D 249
		mci->mci_pid = 0;
E 249
D 247
		mci->mci_state = MCIS_OPEN;
E 247
I 247
		mci->mci_state = clever ? MCIS_OPENING : MCIS_OPEN;
E 247
I 246
		mci->mci_mailer = m;
E 246
D 247
		return mci;
E 247
I 247
D 249
		mci->mci_flags = 0;
E 249
E 247
E 243
	}
D 213
#endif DEBUG
E 213
E 170
D 247

D 240
	if (strcmp(m->m_mailer, "[IPC]") == 0)
E 240
I 240
	if (strcmp(m->m_mailer, "[IPC]") == 0 ||
	    strcmp(m->m_mailer, "[TCP]") == 0)
E 247
I 247
	else if (strcmp(m->m_mailer, "[IPC]") == 0 ||
		 strcmp(m->m_mailer, "[TCP]") == 0)
E 247
E 240
	{
I 190
D 241
#ifdef HOSTINFO
E 241
I 241
#ifdef DAEMON
E 241
D 251
		register STAB *st;
		extern STAB *stab();
E 251
D 241
#endif HOSTINFO
E 190
I 154
#ifdef DAEMON
E 241
E 154
D 196
		register int i;
E 196
I 196
D 263
		register int i, j;
E 263
I 263
		register int i;
E 263
E 196
I 112
D 467
		register u_short port;
E 467
I 467
		register u_short port = 0;
E 467
I 247
D 263
		int nmx;
		char *mxhosts[MAXMXHOSTS + 1];
E 263
I 263
D 312
		char *curhost;
E 312
E 263
D 337
		extern MCI *mci_get();
I 263
		extern char *hostsignature();
E 337
E 263
E 247
E 112

I 381
		if (pv[0] == NULL || pv[1] == NULL || pv[1][0] == '\0')
		{
			syserr("null host name for %s mailer", m->m_mailer);
			rcode = EX_CONFIG;
			goto give_up;
		}

E 381
I 192
D 312
		CurHostName = pvp[1];
I 247
D 263
#ifdef NAMED_BIND
		if (CurHostName != NULL && CurHostName[0] != '\0' &&
		    CurHostName[0] != '[')
		{
			int rcode;
			char buf[MAXNAME];
E 263
I 263
		curhost = hostsignature(m, pvp[1], e);
E 312
I 312
		CurHostName = pv[1];
		curhost = hostsignature(m, pv[1], e);
E 312
E 263

I 293
		if (curhost == NULL || curhost[0] == '\0')
		{
D 381
			syserr("null signature");
E 381
I 381
			syserr("null host signature for %s", pv[1]);
E 381
D 312
			return NULL;
E 312
I 312
D 426
			rcode = EX_OSERR;
E 426
I 426
			rcode = EX_CONFIG;
E 426
			goto give_up;
E 312
		}

E 293
D 263
			expand("\001j", buf, &buf[sizeof(buf) - 1], e);
			nmx = getmxrr(CurHostName, mxhosts, buf, &rcode);
			if (nmx < 0)
			{
				mci = mci_get(CurHostName, m);
				mci->mci_exitstat = rcode;
				mci->mci_errno = errno;
			}
		}
		else
#endif
		{
			nmx = 1;
			mxhosts[0] = CurHostName;
		}

E 263
E 247
E 192
		if (!clever)
I 293
		{
E 293
D 280
			syserr("non-clever IPC");
E 280
I 280
			syserr("554 non-clever IPC");
I 293
D 312
			return NULL;
E 312
I 312
D 371
			rcode = EX_OSERR;
E 371
I 371
			rcode = EX_CONFIG;
E 371
			goto give_up;
E 312
		}
E 293
E 280
D 96
		i = makeconnection(pvp[1], pmfile, prfile);
E 96
I 96
D 312
		if (pvp[2] != NULL)
D 112
			i = atoi(pvp[2]);
E 112
I 112
			port = atoi(pvp[2]);
E 312
I 312
		if (pv[2] != NULL)
D 502
			port = atoi(pv[2]);
E 502
I 502
		{
			port = htons(atoi(pv[2]));
			if (port == 0)
			{
				struct servent *sp = getservbyname(pv[2], "tcp");

				if (sp == NULL)
					syserr("Service %s unknown", pv[2]);
				else
					port = sp->s_port;
			}
		}
E 502
E 312
E 112
D 467
		else
D 112
			i = 0;
		i = makeconnection(pvp[1], i, pmfile, prfile);
E 112
I 112
			port = 0;
E 467
I 312
tryhost:
D 371
		mci = NULL;
E 371
E 312
I 196
D 199
		for (j = 0; j < nmx; j++)
E 199
I 199
D 247
		for (j = 0; j < Nmx; j++)
E 247
I 247
D 263
		for (j = 0; j < nmx; j++)
E 263
I 263
		while (*curhost != '\0')
E 263
E 247
E 199
		{
I 263
			register char *p;
D 298
			char hostbuf[MAXNAME];
E 298
I 298
D 474
			static char hostbuf[MAXNAME];
E 474
I 474
			static char hostbuf[MAXNAME + 1];
E 474
E 298

I 312
D 371
			mci = NULL;

E 371
E 312
			/* pull the next host from the signature */
			p = strchr(curhost, ':');
			if (p == NULL)
				p = &curhost[strlen(curhost)];
I 371
			if (p == curhost)
			{
				syserr("deliver: null host name in signature");
I 374
				curhost++;
E 374
				continue;
			}
E 371
			strncpy(hostbuf, curhost, p - curhost);
			hostbuf[p - curhost] = '\0';
			if (*p != '\0')
				p++;
			curhost = p;

E 263
D 199
			CurHostName = mxhosts[j];
E 199
I 199
D 243
			CurHostName = MxHosts[j];
E 243
E 199
D 197
			expand("\001j", buf, &buf[sizeof buf - 1], CurEnv);
			if (sameword(CurHostName, buf))
				break;
E 197
E 196
I 190
D 241
#ifdef HOSTINFO
E 241
D 240
		/* see if we have already determined that this host is fried */
E 240
I 240
			/* see if we already know that this host is fried */
E 240
D 196
		st = stab(pvp[1], ST_HOST, ST_FIND);
		if (st == NULL || st->s_host.ho_exitstat == EX_OK)
			i = makeconnection(pvp[1], port, pmfile, prfile);
		else
I 192
		{
E 192
			i = st->s_host.ho_exitstat;
I 192
			errno = st->s_host.ho_errno;
		}
E 196
I 196
D 199
			st = stab(mxhosts[j], ST_HOST, ST_FIND);
E 199
I 199
D 243
			st = stab(MxHosts[j], ST_HOST, ST_FIND);
E 199
D 207
			if (st == NULL || st->s_host.ho_exitstat == EX_OK)
E 207
I 207
D 240
			if (st == NULL || st->s_host.ho_exitstat == EX_OK) {
				if (j > 1)
					message(Arpa_Info,
					    "Connecting to %s (%s)...",
					    MxHosts[j], m->m_name);
E 207
D 199
				i = makeconnection(mxhosts[j], port, pmfile, prfile);
E 199
I 199
				i = makeconnection(MxHosts[j], port, pmfile, prfile);
E 240
I 240
			if (st == NULL || st->s_host.ho_exitstat == EX_OK)
E 243
I 243
D 247
			CurHostName = MxHosts[j];
			st = stab(CurHostName,
				  ST_MCONINFO + m->m_mno,
				  ST_ENTER);
			mci = &st->s_mci;
D 246
			if (mci->mci_state != MCIS_CLOSED)
E 246
I 246
			if (mci->mci_state == MCIS_OPEN)
E 247
I 247
D 263
			CurHostName = mxhosts[j];
			mci = mci_get(CurHostName, m);
E 263
I 263
			CurHostName = hostbuf;
			mci = mci_get(hostbuf, m);
E 263
			if (mci->mci_state != MCIS_CLOSED)
I 259
			{
				if (tTd(11, 1))
				{
					printf("openmailer: ");
D 375
					mci_dump(mci);
E 375
I 375
					mci_dump(mci, FALSE);
E 375
				}
I 271
				CurHostName = mci->mci_host;
I 443
				message("Using cached connection to %s via %s...",
					hostbuf, m->m_name);
E 443
E 271
E 259
E 247
E 246
D 312
				return mci;
E 312
I 312
				break;
E 312
I 259
			}
E 259
D 246
			if (mci->mci_exitstat == EX_OK)
E 246
I 246
			mci->mci_mailer = m;
D 247
			if (mci->mci_state == MCIS_CLOSED)
E 247
I 247
			if (mci->mci_exitstat != EX_OK)
				continue;

			/* try the connection */
D 254
			setproctitle("%s %s: %s", e->e_id, mxhosts[1], "user open");
E 254
I 254
D 263
			setproctitle("%s %s: %s", e->e_id, mxhosts[j], "user open");
E 263
I 263
			setproctitle("%s %s: %s", e->e_id, hostbuf, "user open");
E 263
E 254
D 280
			message(Arpa_Info, "Connecting to %s (%s)...",
E 280
I 280
D 443
			message("Connecting to %s (%s)...",
E 443
I 443
			message("Connecting to %s via %s...",
E 443
E 280
D 263
				mxhosts[j], m->m_name);
			i = makeconnection(mxhosts[j], port, mci,
E 263
I 263
				hostbuf, m->m_name);
			i = makeconnection(hostbuf, port, mci,
E 263
				bitnset(M_SECURE_PORT, m->m_flags));
			mci->mci_exitstat = i;
			mci->mci_errno = errno;
I 342
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
			mci->mci_herrno = h_errno;
#endif
E 342
			if (i == EX_OK)
E 247
E 246
E 243
			{
I 243
D 247
				/* try the connection */
E 243
				message(Arpa_Info, "Connecting to %s (%s)...",
					MxHosts[j], m->m_name);
D 243
				i = makeconnection(MxHosts[j], port,
					pmfile, prfile,
E 243
I 243
				i = makeconnection(MxHosts[j], port, mci,
E 243
					bitnset(M_SECURE_PORT, m->m_flags));
I 243
				mci->mci_exitstat = i;
				mci->mci_errno = errno;
I 246
				if (i == EX_TEMPFAIL)
					mci->mci_state = MCIS_TEMPFAIL;
				else if (i != EX_OK)
					mci->mci_state = MCIS_ERROR;
				else
					mci->mci_state = MCIS_OPENING;
E 247
I 247
				mci->mci_state = MCIS_OPENING;
				mci_cache(mci);
I 342
				if (TrafficLogFile != NULL)
					fprintf(TrafficLogFile, "%05d == CONNECT %s\n",
						getpid(), hostbuf);
E 342
				break;
E 247
E 246
E 243
E 240
I 207
			}
E 207
E 199
D 247
			else
			{
D 245
				i = st->s_host.ho_exitstat;
				errno = st->s_host.ho_errno;
E 245
I 245
				i = mci->mci_exitstat;
				errno = mci->mci_errno;
E 245
			}
E 196
E 192
D 241
#else HOSTINFO
E 190
D 196
		i = makeconnection(pvp[1], port, pmfile, prfile);
E 196
I 196
D 199
			i = makeconnection(mxhosts[j], port, pmfile, prfile);
E 199
I 199
D 240
			i = makeconnection(MxHosts[j], port, pmfile, prfile);
E 240
I 240
			message(Arpa_Info, "Connecting to %s (%s)...",
				MxHosts[j], m->m_name);
			i = makeconnection(MxHosts[j], port, pmfile, prfile,
				bitnset(M_SECURE_PORT, m->m_flags);
E 240
E 199
E 196
I 190
#endif HOSTINFO
E 241
E 190
E 112
E 96
D 196
		if (i != EX_OK)
I 92
		{
E 196
I 196
D 243
			if (i != EX_OK)
			{
E 196
I 190
D 241
#ifdef HOSTINFO
E 241
D 196
			/* enter status of this host */
			if (st == NULL)
				st = stab(pvp[1], ST_HOST, ST_ENTER);
			st->s_host.ho_exitstat = i;
			st->s_host.ho_errno = errno;
E 196
I 196
				/* enter status of this host */
				if (st == NULL)
D 199
					st = stab(mxhosts[j], ST_HOST, ST_ENTER);
E 199
I 199
					st = stab(MxHosts[j], ST_HOST, ST_ENTER);
E 199
				st->s_host.ho_exitstat = i;
				st->s_host.ho_errno = errno;
E 196
D 241
#endif HOSTINFO
E 241
E 190
D 196
			ExitStat = i;
E 92
			return (-1);
E 196
I 196
				ExitStat = i;
				continue;
			}
			else
				return (0);
E 243
I 243
			if (i == EX_OK)
				return mci;
E 247
I 247
			else if (tTd(11, 1))
				printf("openmailer: makeconnection => stat=%d, errno=%d\n",
					i, errno);
E 247

I 247
D 371

E 371
E 247
			/* enter status of this host */
			setstat(i);
I 371

			/* should print some message here for -v mode */
E 371
E 243
E 196
I 92
		}
I 371
		if (mci == NULL)
		{
			syserr("deliver: no host name");
			rcode = EX_OSERR;
			goto give_up;
		}
E 371
I 249
		mci->mci_pid = 0;
E 249
E 92
D 196
		else
			return (0);
E 196
I 196
D 243
		return (-1);
E 243
I 243
D 247
		return NULL;
E 243
E 196
I 154
#else DAEMON
E 247
I 247
#else /* no DAEMON */
E 247
D 280
		syserr("openmailer: no IPC");
E 280
I 280
		syserr("554 openmailer: no IPC");
E 280
I 259
		if (tTd(11, 1))
			printf("openmailer: NULL\n");
E 259
D 243
		return (-1);
E 243
I 243
D 371
		return NULL;
E 371
I 371
		rcode = EX_UNAVAILABLE;
		goto give_up;
E 371
E 243
D 247
#endif DAEMON
E 247
I 247
#endif /* DAEMON */
E 247
E 154
	}
D 154
# endif DAEMON
E 154
D 247

E 90
E 26
D 32
	rewind(stdin);

E 32
D 19
	/* create a pipe if we will need one */
	if (editfcn != NULL && pipe(pvect) < 0)
E 19
I 19
	/* create a pipe to shove the mail through */
D 71
	if (pipe(pvect) < 0)
E 71
I 71
	if (pipe(mpvect) < 0)
E 247
I 247
	else
E 247
E 71
E 19
	{
I 444
		/* flush any expired connections */
		(void) mci_scan(NULL);

		/* announce the connection to verbose listeners */
E 444
I 443
		if (host == NULL || host[0] == '\0')
			message("Connecting to %s...", m->m_name);
		else
			message("Connecting to %s via %s...", host, m->m_name);
E 443
I 313
D 342
		int i;
		struct stat stbuf;
E 342
I 342
D 361
#ifdef XDEBUG
		char wbuf[MAXLINE];
E 342

		/* make absolutely certain 0, 1, and 2 are in use */
D 342
		for (i = 0; i < 3; i++)
E 342
I 342
		sprintf(wbuf, "%s... openmailer(%s)", e->e_to, m->m_name);
		checkfd012(wbuf);
#endif

E 361
		if (TrafficLogFile != NULL)
E 342
		{
D 342
			if (fstat(i, &stbuf) < 0)
			{
				/* oops.... */
D 316
				syserr("openmailer: fd %d not open", i);
				(void) open("/dev/null", O_RDONLY, 0666);
E 316
I 316
				int fd;
E 342
I 342
			char **av;
E 342

D 342
				syserr("%s... openmailer(%s): fd %d not open",
					e->e_to, m->m_name, i);
				fd = open("/dev/null", O_RDONLY, 0666);
				if (fd != i)
				{
					(void) dup2(fd, i);
					(void) close(fd);
				}
E 316
			}
E 342
I 342
			fprintf(TrafficLogFile, "%05d === EXEC", getpid());
			for (av = pv; *av != NULL; av++)
				fprintf(TrafficLogFile, " %s", *av);
			fprintf(TrafficLogFile, "\n");
E 342
		}

E 313
D 72
		syserr("pipe");
E 72
I 72
D 154
		syserr("pipe (to mailer)");
E 154
I 154
D 247
		syserr("openmailer: pipe (to mailer)");
E 154
E 72
D 243
		return (-1);
E 243
I 243
		return NULL;
E 243
	}
E 247
I 247
		/* create a pipe to shove the mail through */
		if (pipe(mpvect) < 0)
		{
D 316
			syserr("openmailer: pipe (to mailer)");
E 316
I 316
			syserr("%s... openmailer(%s): pipe (to mailer)",
				e->e_to, m->m_name);
E 316
I 259
			if (tTd(11, 1))
				printf("openmailer: NULL\n");
E 259
D 312
			return NULL;
E 312
I 312
			rcode = EX_OSERR;
			goto give_up;
E 312
		}
E 247
I 72

I 79
D 154
# ifdef SMTP
E 154
I 154
D 247
#ifdef SMTP
E 154
E 79
	/* if this mailer speaks smtp, create a return pipe */
	if (clever && pipe(rpvect) < 0)
	{
D 154
		syserr("pipe (from mailer)");
E 154
I 154
		syserr("openmailer: pipe (from mailer)");
E 154
		(void) close(mpvect[0]);
		(void) close(mpvect[1]);
D 243
		return (-1);
E 243
I 243
		return NULL;
E 243
	}
I 79
D 154
# endif SMTP
E 154
I 154
#endif SMTP
E 247
I 247
		/* if this mailer speaks smtp, create a return pipe */
		if (clever && pipe(rpvect) < 0)
		{
D 316
			syserr("openmailer: pipe (from mailer)");
E 316
I 316
			syserr("%s... openmailer(%s): pipe (from mailer)",
				e->e_to, m->m_name);
E 316
			(void) close(mpvect[0]);
			(void) close(mpvect[1]);
I 259
			if (tTd(11, 1))
				printf("openmailer: NULL\n");
E 259
D 312
			return NULL;
E 312
I 312
			rcode = EX_OSERR;
			goto give_up;
E 312
		}
E 247
E 154
E 79

I 90
D 247
	/*
	**  Actually fork the mailer process.
	**	DOFORK is clever about retrying.
I 195
	**
	**	Dispose of SIGCHLD signal catchers that may be laying
	**	around so that endmail will get it.
E 195
	*/
E 247
I 247
		/*
		**  Actually fork the mailer process.
		**	DOFORK is clever about retrying.
		**
		**	Dispose of SIGCHLD signal catchers that may be laying
		**	around so that endmail will get it.
		*/
E 247

I 115
D 117
	fflush(Xscript);				/* for debugging */
E 117
I 117
D 152
	(void) fflush(Xscript);				/* for debugging */
E 152
I 152
D 157
	if (Xscript != NULL)
		(void) fflush(Xscript);			/* for debugging */
E 157
I 157
D 247
	if (CurEnv->e_xfp != NULL)
		(void) fflush(CurEnv->e_xfp);		/* for debugging */
E 157
I 154
	(void) fflush(stdout);
E 247
I 247
		if (e->e_xfp != NULL)
			(void) fflush(e->e_xfp);		/* for debugging */
		(void) fflush(stdout);
E 247
I 195
# ifdef SIGCHLD
D 247
	(void) signal(SIGCHLD, SIG_DFL);
E 247
I 247
D 348
		(void) signal(SIGCHLD, SIG_DFL);
E 348
I 348
		(void) setsignal(SIGCHLD, SIG_DFL);
E 348
E 247
D 256
# endif SIGCHLD
E 256
I 256
# endif /* SIGCHLD */
E 256
E 195
E 154
E 152
E 117
E 115
E 90
E 72
I 31
D 48
	for (i = NFORKTRIES; i-- > 0; )
	{
E 31
I 6
# ifdef VFORK
D 31
	pid = vfork();
E 31
I 31
		pid = vfork();
E 31
# else
E 6
D 31
	pid = fork();
E 31
I 31
		pid = fork();
E 31
I 6
# endif
I 31
		if (pid >= 0)
			break;
D 36
		sleep(NFORKTRIES - i);
E 36
I 36
		sleep((unsigned) NFORKTRIES - i);
E 36
	}
E 48
I 48
D 241
	DOFORK(XFORK);
E 241
I 241
D 247
	DOFORK(FORK);
E 241
I 55
	/* pid is set by DOFORK */
E 55
E 48
E 31
E 6
	if (pid < 0)
	{
I 90
		/* failure */
E 90
D 154
		syserr("Cannot fork");
E 154
I 154
		syserr("openmailer: cannot fork");
E 154
D 19
		if (editfcn != NULL)
		{
			close(pvect[0]);
			close(pvect[1]);
		}
E 19
I 19
D 36
		close(pvect[0]);
		close(pvect[1]);
E 36
I 36
D 71
		(void) close(pvect[0]);
		(void) close(pvect[1]);
E 71
I 71
		(void) close(mpvect[0]);
		(void) close(mpvect[1]);
I 154
#ifdef SMTP
E 154
I 72
		if (clever)
E 247
I 247
		DOFORK(FORK);
		/* pid is set by DOFORK */
		if (pid < 0)
E 247
		{
D 247
			(void) close(rpvect[0]);
			(void) close(rpvect[1]);
E 247
I 247
			/* failure */
D 316
			syserr("openmailer: cannot fork");
E 316
I 316
			syserr("%s... openmailer(%s): cannot fork",
				e->e_to, m->m_name);
E 316
			(void) close(mpvect[0]);
			(void) close(mpvect[1]);
			if (clever)
			{
				(void) close(rpvect[0]);
				(void) close(rpvect[1]);
			}
I 259
			if (tTd(11, 1))
				printf("openmailer: NULL\n");
E 259
D 312
			return NULL;
E 312
I 312
			rcode = EX_OSERR;
			goto give_up;
E 312
E 247
		}
I 154
D 247
#endif SMTP
E 154
E 72
E 71
E 36
E 19
D 243
		return (-1);
E 243
I 243
		return NULL;
E 243
	}
	else if (pid == 0)
	{
I 180
		int i;
I 190
		extern int DtableSize;
E 247
I 247
		else if (pid == 0)
		{
			int i;
I 255
			int saveerrno;
I 499
			struct stat stb;
E 499
I 265
D 300
			char *env[2];
E 300
I 300
D 496
			char **ep;
			char *env[MAXUSERENVIRON];
			extern char **environ;
E 496
E 300
E 265
E 255
			extern int DtableSize;
E 247
E 190

I 468
			if (e->e_lockfp != NULL)
D 480
			{
				fclose(e->e_lockfp);
				e->e_lockfp = NULL;
			}
E 480
I 480
				(void) close(fileno(e->e_lockfp));
E 480

E 468
E 180
D 247
		/* child -- set up input & exec mailer */
I 10
		/* make diagnostic output be standard output */
I 49
D 65
		(void) signal(SIGINT, SIG_DFL);
		(void) signal(SIGHUP, SIG_DFL);
E 65
I 65
		(void) signal(SIGINT, SIG_IGN);
		(void) signal(SIGHUP, SIG_IGN);
E 65
		(void) signal(SIGTERM, SIG_DFL);
E 247
I 247
			/* child -- set up input & exec mailer */
D 351
			/* make diagnostic output be standard output */
E 351
D 348
			(void) signal(SIGINT, SIG_IGN);
			(void) signal(SIGHUP, SIG_IGN);
			(void) signal(SIGTERM, SIG_DFL);
E 348
I 348
			(void) setsignal(SIGINT, SIG_IGN);
			(void) setsignal(SIGHUP, SIG_IGN);
			(void) setsignal(SIGTERM, SIG_DFL);
E 348
E 247
I 71
D 376

I 276
			/* close any other cached connections */
			mci_flush(FALSE, mci);
E 376

I 499
D 503
			if (m != FileMailer || stat(to->q_user, &stb) < 0)
E 503
I 503
			if (m != FileMailer || stat(tochain->q_user, &stb) < 0)
E 503
				stb.st_mode = 0;

E 499
I 489
			/* tweak niceness */
			if (m->m_nice != 0)
				nice(m->m_nice);

E 489
I 351
D 499
			/* reset user and group */
E 499
I 499
			/* reset group id */
E 499
D 433
			if (!bitnset(M_RESTR, m->m_flags))
E 433
I 433
			if (bitnset(M_SPECIFIC_UID, m->m_flags))
D 499
			{
E 499
				(void) setgid(m->m_gid);
D 499
				(void) setuid(m->m_uid);
			}
I 434
			else if (ctladdr != NULL && ctladdr->q_uid != 0)
E 499
I 499
			else if (bitset(S_ISGID, stb.st_mode))
				(void) setgid(stb.st_gid);
			else if (ctladdr != NULL && ctladdr->q_gid != 0)
E 499
			{
				(void) initgroups(ctladdr->q_ruser?
					ctladdr->q_ruser: ctladdr->q_user,
					ctladdr->q_gid);
				(void) setgid(ctladdr->q_gid);
D 499
				(void) setuid(ctladdr->q_uid);
E 499
			}
E 434
			else
E 433
			{
D 434
				if (ctladdr == NULL || ctladdr->q_uid == 0)
				{
D 355
					(void) setgid(DefGid);
E 355
					(void) initgroups(DefUser, DefGid);
E 434
I 434
				(void) initgroups(DefUser, DefGid);
				if (m->m_gid == 0)
E 434
I 380
					(void) setgid(DefGid);
I 434
				else
					(void) setgid(m->m_gid);
I 499
			}

			/* reset user id */
I 506
			endpwent();
E 506
			if (bitnset(M_SPECIFIC_UID, m->m_flags))
				(void) setuid(m->m_uid);
			else if (bitset(S_ISUID, stb.st_mode))
				(void) setuid(stb.st_uid);
			else if (ctladdr != NULL && ctladdr->q_uid != 0)
				(void) setuid(ctladdr->q_uid);
			else
			{
E 499
				if (m->m_uid == 0)
E 434
E 380
					(void) setuid(DefUid);
D 434
				}
E 434
				else
D 434
				{
D 355
					(void) setgid(ctladdr->q_gid);
E 355
					(void) initgroups(ctladdr->q_ruser?
						ctladdr->q_ruser: ctladdr->q_user,
						ctladdr->q_gid);
I 380
D 386
					(void) setuid(ctladdr->q_gid);
E 386
I 386
					(void) setgid(ctladdr->q_gid);
E 386
E 380
					(void) setuid(ctladdr->q_uid);
				}
E 434
I 434
					(void) setuid(m->m_uid);
E 434
			}

			if (tTd(11, 2))
				printf("openmailer: running as r/euid=%d/%d\n",
					getuid(), geteuid());

E 351
I 318
			/* move into some "safe" directory */
			if (m->m_execdir != NULL)
			{
				char *p, *q;
D 474
				char buf[MAXLINE];
E 474
I 474
				char buf[MAXLINE + 1];
E 474

				for (p = m->m_execdir; p != NULL; p = q)
				{
					q = strchr(p, ':');
					if (q != NULL)
						*q = '\0';
D 474
					expand(p, buf, &buf[sizeof buf] - 1, e);
E 474
I 474
D 475
					expand(p, buf, &buf[sizeof buf], e);
E 475
I 475
					expand(p, buf, sizeof buf, e);
E 475
E 474
					if (q != NULL)
						*q++ = ':';
					if (tTd(11, 20))
						printf("openmailer: trydir %s\n",
							buf);
					if (buf[0] != '\0' && chdir(buf) >= 0)
						break;
				}
			}

E 318
E 276
D 247
		/* arrange to filter standard & diag output of command */
D 72
		if (OutChannel != stdout)
E 72
I 72
		if (clever)
E 72
		{
I 72
			(void) close(rpvect[0]);
E 72
			(void) close(1);
I 72
			(void) dup(rpvect[1]);
			(void) close(rpvect[1]);
		}
D 147
		else if (OutChannel != stdout)
E 147
I 147
D 150
		else if (Smtp || HoldErrs)
E 150
I 150
		else if (OpMode == MD_SMTP || HoldErrs)
E 150
E 147
		{
I 154
			/* put mailer output in transcript */
E 154
			(void) close(1);
E 72
D 147
			(void) dup(fileno(OutChannel));
E 147
I 147
D 157
			(void) dup(fileno(Xscript));
E 157
I 157
			(void) dup(fileno(CurEnv->e_xfp));
E 157
E 147
		}
E 71
E 49
D 36
		close(2);
		dup(1);
E 10
		signal(SIGINT, SIG_IGN);
D 19
		if (editfcn != NULL)
E 19
I 19
		close(0);
E 36
I 36
		(void) close(2);
		(void) dup(1);
E 247
I 247
			/* arrange to filter std & diag output of command */
			if (clever)
			{
				(void) close(rpvect[0]);
D 307
				(void) close(1);
				(void) dup(rpvect[1]);
E 307
I 307
D 313
				(void) dup2(rpvect[1], STDOUT_FILENO);
E 313
I 313
				if (dup2(rpvect[1], STDOUT_FILENO) < 0)
				{
D 316
					syserr("Cannot dup pipe %d for stdout",
						rpvect[1]);
E 316
I 316
					syserr("%s... openmailer(%s): cannot dup pipe %d for stdout",
						e->e_to, m->m_name, rpvect[1]);
E 316
					_exit(EX_OSERR);
				}
E 313
E 307
				(void) close(rpvect[1]);
			}
D 401
			else if (OpMode == MD_SMTP || HoldErrs)
E 401
I 401
D 412
			else if (OpMode == MD_SMTP || OpMode == MD_DAEMON || HoldErrs)
E 412
I 412
D 414
			else if ((OpMode == MD_SMTP || OpMode == MD_DAEMON ||
				  HoldErrs) && !DisConnected)
E 414
I 414
			else if (OpMode == MD_SMTP || OpMode == MD_DAEMON ||
				  HoldErrs || DisConnected)
E 414
E 412
E 401
			{
				/* put mailer output in transcript */
D 307
				(void) close(1);
				(void) dup(fileno(e->e_xfp));
E 307
I 307
D 313
				(void) dup2(fileno(e->e_xfp), STDOUT_FILENO);
E 313
I 313
				if (dup2(fileno(e->e_xfp), STDOUT_FILENO) < 0)
				{
D 316
					syserr("Cannot dup xscript %d for stdout",
E 316
I 316
					syserr("%s... openmailer(%s): cannot dup xscript %d for stdout",
						e->e_to, m->m_name,
E 316
						fileno(e->e_xfp));
					_exit(EX_OSERR);
				}
E 313
E 307
			}
D 307
			(void) close(2);
			(void) dup(1);
E 307
I 307
D 313
			(void) dup2(STDOUT_FILENO, STDERR_FILENO);
E 313
I 313
			if (dup2(STDOUT_FILENO, STDERR_FILENO) < 0)
			{
D 316
				syserr("Cannot dup stdout for stderr");
E 316
I 316
				syserr("%s... openmailer(%s): cannot dup stdout for stderr",
					e->e_to, m->m_name);
E 316
				_exit(EX_OSERR);
			}
E 313
E 307
E 247
I 71

D 247
		/* arrange to get standard input */
		(void) close(mpvect[1]);
E 71
D 49
		(void) signal(SIGINT, SIG_IGN);
E 49
		(void) close(0);
E 36
D 71
		if (dup(pvect[0]) < 0)
E 71
I 71
		if (dup(mpvect[0]) < 0)
E 71
E 19
		{
D 19
			close(0);
			if (dup(pvect[0]) < 0)
			{
				syserr("Cannot dup to zero!");
D 9
				exit(EX_OSERR);
E 9
I 9
				_exit(EX_OSERR);
E 9
			}
			close(pvect[0]);
			close(pvect[1]);
E 19
I 19
			syserr("Cannot dup to zero!");
			_exit(EX_OSERR);
E 19
		}
I 19
D 36
		close(pvect[0]);
		close(pvect[1]);
E 36
I 36
D 71
		(void) close(pvect[0]);
		(void) close(pvect[1]);
E 71
I 71
		(void) close(mpvect[0]);
E 71
E 36
E 19
D 20
		if (!flagset(M_RESTR, m->m_flags))
E 20
I 20
D 168
		if (!bitset(M_RESTR, m->m_flags))
E 168
I 168
		if (!bitnset(M_RESTR, m->m_flags))
E 168
I 49
		{
I 60
D 61
			extern int DefUid, DefGid;
E 61
I 61
D 183
			if (ctladdr->q_uid == 0)
E 183
I 183
			if (ctladdr == NULL || ctladdr->q_uid == 0)
E 247
I 247
			/* arrange to get standard input */
			(void) close(mpvect[1]);
D 307
			(void) close(0);
			if (dup(mpvect[0]) < 0)
E 307
I 307
			if (dup2(mpvect[0], STDIN_FILENO) < 0)
E 307
E 247
E 183
			{
D 83
				extern int DefUid, DefGid;
E 61

E 83
E 60
E 49
E 20
D 36
			setuid(getuid());
E 36
I 36
D 58
			(void) setuid(getuid());
I 49
			(void) setgid(getgid());
E 58
I 58
D 61
			(void) setuid(ctladdr->q_uid);
			(void) setgid(ctladdr->q_gid);
I 60
			if (getruid() == 0)
E 61
I 61
D 247
				(void) setgid(DefGid);
I 218
				(void) initgroups(DefUser, DefGid);
E 218
				(void) setuid(DefUid);
E 247
I 247
D 313
				syserr("Cannot dup to zero!");
E 313
I 313
D 316
				syserr("Cannot dup pipe %d for stdin",
					mpvect[0]);
E 316
I 316
				syserr("%s... openmailer(%s): cannot dup pipe %d for stdin",
					e->e_to, m->m_name, mpvect[0]);
E 316
E 313
				_exit(EX_OSERR);
E 247
			}
D 247
			else
E 247
I 247
			(void) close(mpvect[0]);
D 351
			if (!bitnset(M_RESTR, m->m_flags))
E 247
E 61
			{
D 61
				setuid(DefUid);
				setgid(DefGid);
E 61
I 61
D 247
				(void) setgid(ctladdr->q_gid);
I 218
				(void) initgroups(ctladdr->q_ruser?
					ctladdr->q_ruser: ctladdr->q_user,
					ctladdr->q_gid);
E 218
				(void) setuid(ctladdr->q_uid);
E 247
I 247
				if (ctladdr == NULL || ctladdr->q_uid == 0)
				{
					(void) setgid(DefGid);
I 270
D 275
#ifndef SYSTEM5
E 275
E 270
					(void) initgroups(DefUser, DefGid);
I 270
D 275
#endif
E 275
E 270
					(void) setuid(DefUid);
				}
				else
				{
					(void) setgid(ctladdr->q_gid);
I 270
D 275
#ifndef SYSTEM5
E 275
E 270
					(void) initgroups(ctladdr->q_ruser?
						ctladdr->q_ruser: ctladdr->q_user,
						ctladdr->q_gid);
I 270
D 275
#endif
E 275
E 270
					(void) setuid(ctladdr->q_uid);
				}
E 247
E 61
			}
E 351
E 60
E 58
D 247
		}
E 247
E 49
E 36
D 18
# ifdef LOG
D 16
		initlog(NULL, 0, LOG_CLOSE);
E 16
I 16
		closelog();
E 16
# endif LOG
E 18
I 6
D 148
# ifndef VFORK
E 148
I 148
D 154
# ifndef VMUNIX
E 154
I 154

E 154
E 148
D 180
		/*
D 18
		 * We have to be careful with vfork - we can't mung up the
		 * memory but we don't want the mailer to inherit any extra
		 * open files.  Chances are the mailer won't
		 * care about an extra file, but then again you never know.
		 * Actually, we would like to close(fileno(pwf)), but it's
		 * declared static so we can't.  But if we fclose(pwf), which
		 * is what endpwent does, it closes it in the parent too and
		 * the next getpwnam will be slower.  If you have a weird mailer
		 * that chokes on the extra file you should do the endpwent().
		 */
E 18
I 18
		**  We have to be careful with vfork - we can't mung up the
		**  memory but we don't want the mailer to inherit any extra
		**  open files.  Chances are the mailer won't
		**  care about an extra file, but then again you never know.
		**  Actually, we would like to close(fileno(pwf)), but it's
		**  declared static so we can't.  But if we fclose(pwf), which
		**  is what endpwent does, it closes it in the parent too and
		**  the next getpwnam will be slower.  If you have a weird
		**  mailer that chokes on the extra file you should do the
D 148
		**  endpwent().
E 148
I 148
		**  endpwent().			-MRH
E 148
		**
		**  Similar comments apply to log.  However, openlog is
		**  clever enough to set the FIOCLEX mode on the file,
		**  so it will be closed automatically on the exec.
		*/
E 180
I 180
D 247
		/* arrange for all the files to be closed */
D 190
		for (i = 3; i < 50; i++)
E 190
I 190
D 211
		for (i = 3; i < DtableSize; i++)
E 190
D 208
#ifdef FIOCLEX
E 208
			(void) ioctl(i, FIOCLEX, 0);
E 211
I 211
		for (i = 3; i < DtableSize; i++) {
			register int j;
			if ((j = fcntl(i, F_GETFD, 0)) != -1)
				(void)fcntl(i, F_SETFD, j|1);
		}
E 247
I 247
			/* arrange for all the files to be closed */
			for (i = 3; i < DtableSize; i++)
			{
				register int j;
I 351

E 351
				if ((j = fcntl(i, F_GETFD, 0)) != -1)
D 351
					(void)fcntl(i, F_SETFD, j|1);
E 351
I 351
					(void) fcntl(i, F_SETFD, j | 1);
E 351
			}
E 247
E 211
D 208
#else FIOCLEX
			(void) close(i);
#endif FIOCLEX
E 208
E 180

I 300
D 412
			/* set up the mailer environment */
E 412
I 412
D 496
			/*
			**  Set up the mailer environment
I 439
			**	_FORCE_MAIL_LOCAL_ is DG-UX equiv of -d flag.
E 439
			**	TZ is timezone information.
			**	SYSTYPE is Apollo software sys type (required).
			**	ISP is Apollo hardware system type (required).
			*/

E 412
			i = 0;
			env[i++] = "AGENT=sendmail";
I 439
			env[i++] = "_FORCE_MAIL_LOCAL_=yes";
E 439
			for (ep = environ; *ep != NULL; ep++)
			{
D 412
				if (strncmp(*ep, "TZ=", 3) == 0)
E 412
I 412
				if (strncmp(*ep, "TZ=", 3) == 0 ||
				    strncmp(*ep, "ISP=", 4) == 0 ||
				    strncmp(*ep, "SYSTYPE=", 8) == 0)
E 412
					env[i++] = *ep;
			}
D 439
			env[i++] = NULL;
E 439
I 439
			env[i] = NULL;
E 439

E 496
I 420
			/* run disconnected from terminal */
			(void) setsid();

E 420
E 300
E 18
E 6
D 154
		endpwent();
I 6
D 18
# endif
E 18
I 18
# ifdef LOG
		closelog();
# endif LOG
D 148
# endif VFORK
E 148
I 148
# endif VMUNIX
E 154
I 154
D 180
		closeall();
E 154
E 148
I 90

E 180
D 247
		/* try to execute the mailer */
E 90
E 18
E 6
D 191
		execv(m->m_mailer, pvp);
E 191
I 191
		execve(m->m_mailer, pvp, UserEnviron);
E 191
I 90
D 208

E 90
D 180
		/* syserr fails because log is closed */
		/* syserr("Cannot exec %s", m->m_mailer); */
E 180
I 180
#ifdef FIOCLEX
E 208
		syserr("Cannot exec %s", m->m_mailer);
D 208
#else FIOCLEX
E 180
I 17
D 48
		printf("Cannot exec %s\n", m->m_mailer);
E 48
I 48
		printf("Cannot exec '%s' errno=%d\n", m->m_mailer, errno);
E 48
D 36
		fflush(stdout);
E 36
I 36
		(void) fflush(stdout);
I 180
#endif FIOCLEX
E 208
E 180
E 36
E 17
D 8
		exit(EX_UNAVAIL);
E 8
I 8
D 9
		exit(EX_UNAVAILABLE);
E 9
I 9
D 184
		_exit(EX_UNAVAILABLE);
E 184
I 184
D 190
		if (m == LocalMailer)
E 190
I 190
D 233
		if (m == LocalMailer || errno == EIO || errno == EAGAIN ||
		    errno == ENOMEM || errno == EPROCLIM)
E 233
I 233
		if (m == LocalMailer)
E 233
E 190
			_exit(EX_TEMPFAIL);
D 233
		else
			_exit(EX_UNAVAILABLE);
E 233
I 233
		switch (errno)
		{
		  case EIO:
		  case EAGAIN:
		  case ENOMEM:
E 247
I 247
			/* try to execute the mailer */
D 265
			execve(m->m_mailer, pvp, UserEnviron);
E 265
I 265
D 300
			env[0] = "AGENT=sendmail";
			env[1] = NULL;
E 300
D 312
			execve(m->m_mailer, pvp, env);
E 312
I 312
D 487
			execve(m->m_mailer, pv, env);
E 487
I 487
D 496
			execve(m->m_mailer, (ARGV_T) pv, (ARGV_T) env);
E 496
I 496
			execve(m->m_mailer, (ARGV_T) pv, (ARGV_T) UserEnviron);
E 496
E 487
E 312
E 265
I 255
			saveerrno = errno;
E 255
			syserr("Cannot exec %s", m->m_mailer);
D 333
			if (m == LocalMailer)
				_exit(EX_TEMPFAIL);
D 255
			switch (errno)
E 255
I 255
D 297
			switch (saveerrno)
E 255
			{
			  case EIO:
			  case EAGAIN:
			  case ENOMEM:
E 247
# ifdef EPROCLIM
D 247
		  case EPROCLIM:
E 247
I 247
			  case EPROCLIM:
E 247
# endif
I 277
# ifdef ETIMEDOUT
			  case ETIMEDOUT:
# endif
E 297
I 297
			if (transienterror(saveerrno))
E 297
E 277
D 247
			_exit(EX_TEMPFAIL);
E 247
I 247
				_exit(EX_TEMPFAIL);
E 333
I 333
D 429
			if (m == LocalMailer || transienterror(saveerrno))
E 429
I 429
			if (bitnset(M_LOCALMAILER, m->m_flags) ||
			    transienterror(saveerrno))
E 429
				_exit(EX_OSERR);
E 333
D 297
			}
E 297
			_exit(EX_UNAVAILABLE);
E 247
		}
D 247
		_exit(EX_UNAVAILABLE);
E 247
I 247

		/*
		**  Set up return value.
		*/

		mci = (MCI *) xalloc(sizeof *mci);
I 249
		bzero((char *) mci, sizeof *mci);
E 249
		mci->mci_mailer = m;
		mci->mci_state = clever ? MCIS_OPENING : MCIS_OPEN;
I 249
		mci->mci_pid = pid;
E 249
		(void) close(mpvect[0]);
		mci->mci_out = fdopen(mpvect[1], "w");
I 372
		if (mci->mci_out == NULL)
		{
			syserr("deliver: cannot create mailer output channel, fd=%d",
				mpvect[1]);
			(void) close(mpvect[1]);
			if (clever)
			{
				(void) close(rpvect[0]);
				(void) close(rpvect[1]);
			}
			rcode = EX_OSERR;
			goto give_up;
		}
E 372
		if (clever)
		{
			(void) close(rpvect[1]);
			mci->mci_in = fdopen(rpvect[0], "r");
I 372
			if (mci->mci_in == NULL)
			{
				syserr("deliver: cannot create mailer input channel, fd=%d",
					mpvect[1]);
				(void) close(rpvect[0]);
				fclose(mci->mci_out);
				mci->mci_out = NULL;
				rcode = EX_OSERR;
				goto give_up;
			}
E 372
		}
		else
		{
			mci->mci_flags |= MCIF_TEMP;
			mci->mci_in = NULL;
		}
E 247
E 233
E 184
E 9
E 8
	}

I 431
D 446
	if (bitset(EF_HAS8BIT, e->e_flags) && bitnset(M_7BITS, m->m_flags))
		mci->mci_flags |= MCIF_CVT8TO7;

E 446
E 431
D 19
	/* arrange to write out header message if error */
	if (editfcn != NULL)
	{
		close(pvect[0]);
		signal(SIGPIPE, pipesig);
		mfile = fdopen(pvect[1], "w");
		(*editfcn)(mfile);
		fclose(mfile);
	}
E 19
I 19
D 71
	/* write out message to mailer */
D 36
	close(pvect[0]);
	signal(SIGPIPE, pipesig);
E 36
I 36
	(void) close(pvect[0]);
E 71
I 71
	/*
D 72
	**  Format and write message to mailer.
E 72
I 72
D 247
	**  Set up return value.
E 247
I 247
	**  If we are in SMTP opening state, send initial protocol.
E 247
E 72
	*/

I 243
D 245
	mci = xalloc(sizeof *mci);
E 245
I 245
D 247
	mci = (MCONINFO *) xalloc(sizeof *mci);
I 246
	mci->mci_mailer = m;
E 246
E 245
E 243
	(void) close(mpvect[0]);
E 71
D 39
	(void) signal(SIGPIPE, pipesig);
E 39
I 39
D 72
	(void) signal(SIGPIPE, SIG_IGN);
E 72
E 39
E 36
D 71
	mfile = fdopen(pvect[1], "w");
E 71
I 71
D 243
	mfile = fdopen(mpvect[1], "w");
E 243
I 243
	mci->mci_out = fdopen(mpvect[1], "w");
E 243
E 71
D 72
	if (editfcn == NULL)
		editfcn = putmessage;
	(*editfcn)(mfile, m);
D 36
	fclose(mfile);
E 36
I 36
	(void) fclose(mfile);
E 36
E 19

	/*
	**  Wait for child to die and report status.
	**	We should never get fatal errors (e.g., segmentation
	**	violation), so we report those specially.  For other
	**	errors, we choose a status message (into statmsg),
	**	and if it represents an error, we print it.
	*/

	while ((i = wait(&st)) > 0 && i != pid)
		continue;
	if (i < 0)
E 72
I 72
	if (clever)
E 247
I 247
	if (clever && mci->mci_state != MCIS_CLOSED)
E 247
E 72
	{
D 72
		syserr("wait");
		return (-1);
E 72
I 72
D 247
		(void) close(rpvect[1]);
D 243
		rfile = fdopen(rpvect[0], "r");
E 72
D 220
	}
E 220
I 220
	} else
		rfile = NULL;
E 243
I 243
		mci->mci_in = fdopen(rpvect[0], "r");
E 247
I 247
		smtpinit(m, mci, e);
I 259
	}
I 446

	if (bitset(EF_HAS8BIT, e->e_flags) && bitnset(M_7BITS, m->m_flags))
		mci->mci_flags |= MCIF_CVT8TO7;
	else
		mci->mci_flags &= ~MCIF_CVT8TO7;

E 446
	if (tTd(11, 1))
	{
		printf("openmailer: ");
D 375
		mci_dump(mci);
E 375
I 375
		mci_dump(mci, FALSE);
E 375
E 259
E 247
	}
D 247
	else
	{
		mci->mci_flags |= MCIF_TEMP;
		mci->mci_in = NULL;
	}
E 247
E 243
E 220
D 72
	if ((st & 0377) != 0)
	{
		syserr("%s: stat %o", pvp[0], st);
D 8
		ExitStat = EX_UNAVAIL;
E 8
I 8
		ExitStat = EX_UNAVAILABLE;
E 8
		return (-1);
	}
	i = (st >> 8) & 0377;
D 17
	giveresponse(i, FALSE, m);
E 17
I 17
	giveresponse(i, TRUE, m);
E 17
	return (i);
E 72
I 72

D 243
	*pmfile = mfile;
	*prfile = rfile;

	return (pid);
E 243
I 243
D 312
	return mci;
E 312
I 312
	if (mci->mci_state != MCIS_OPEN)
	{
		/* couldn't open the mailer */
		rcode = mci->mci_exitstat;
		errno = mci->mci_errno;
I 342
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
		h_errno = mci->mci_herrno;
#endif
E 342
		if (rcode == EX_OK)
		{
			/* shouldn't happen */
			syserr("554 deliver: rcode=%d, mci_state=%d, sig=%s",
				rcode, mci->mci_state, firstsig);
			rcode = EX_SOFTWARE;
		}
I 331
D 332
		else if (rcode == EX_TEMPFAIL)
E 332
I 332
D 382
		else if (rcode == EX_TEMPFAIL && *curhost != '\0')
E 382
I 382
D 476
		else if (rcode == EX_TEMPFAIL && curhost != NULL && *curhost != '\0')
E 476
I 476
		else if (curhost != NULL && *curhost != '\0')
E 476
E 382
E 332
		{
			/* try next MX site */
			goto tryhost;
		}
E 331
	}
	else if (!clever)
	{
		/*
		**  Format and send message.
		*/

D 405
		putfromline(mci->mci_out, m, e);
		(*e->e_puthdr)(mci->mci_out, m, e);
		putline("\n", mci->mci_out, m);
D 329
		(*e->e_putbody)(mci->mci_out, m, e);
E 329
I 329
		(*e->e_putbody)(mci->mci_out, m, e, NULL);
E 405
I 405
		putfromline(mci, e);
D 430
		(*e->e_puthdr)(mci, e);
E 430
I 430
D 450
		(*e->e_puthdr)(mci, e->e_header, e);
E 430
D 431
		putline("\n", mci);
E 431
		(*e->e_putbody)(mci, e, NULL);
E 450
I 450
D 462
		(*e->e_puthdr)(mci, e->e_header, e, 0);
		(*e->e_putbody)(mci, e, NULL, 0);
E 462
I 462
		(*e->e_puthdr)(mci, e->e_header, e);
		(*e->e_putbody)(mci, e, NULL);
E 462
E 450
E 405
E 329

		/* get the exit status */
		rcode = endmailer(mci, e, pv);
	}
	else
#ifdef SMTP
	{
		/*
		**  Send the MAIL FROM: protocol
		*/

		rcode = smtpmailfrom(m, mci, e);
		if (rcode == EX_OK)
		{
			register char *t = tobuf;
			register int i;

			/* send the recipient list */
			tobuf[0] = '\0';
			for (to = tochain; to != NULL; to = to->q_tchain)
			{
				e->e_to = to->q_paddr;
				if ((i = smtprcpt(to, m, mci, e)) != EX_OK)
				{
D 458
					markfailure(e, to, i);
E 458
I 458
					markfailure(e, to, mci, i);
E 458
D 377
					giveresponse(i, m, mci, e);
E 377
I 377
D 461
					giveresponse(i, m, mci, ctladdr, e);
E 461
I 461
					giveresponse(i, m, mci, ctladdr, xstart, e);
E 461
E 377
				}
				else
				{
					*t++ = ',';
					for (p = to->q_paddr; *p; *t++ = *p++)
						continue;
I 358
					*t = '\0';
E 358
				}
			}

			/* now send the data */
			if (tobuf[0] == '\0')
			{
				rcode = EX_OK;
				e->e_to = NULL;
				if (bitset(MCIF_CACHED, mci->mci_flags))
					smtprset(m, mci, e);
			}
			else
			{
				e->e_to = tobuf + 1;
				rcode = smtpdata(m, mci, e);
			}

			/* now close the connection */
			if (!bitset(MCIF_CACHED, mci->mci_flags))
				smtpquit(m, mci, e);
		}
D 382
		if (rcode != EX_OK && *curhost != '\0')
E 382
I 382
		if (rcode != EX_OK && curhost != NULL && *curhost != '\0')
E 382
		{
			/* try next MX site */
			goto tryhost;
		}
	}
#else /* not SMTP */
	{
		syserr("554 deliver: need SMTP compiled to use clever mailer");
		rcode = EX_CONFIG;
		goto give_up;
	}
#endif /* SMTP */
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
	if (ConfigLevel < 2)
		_res.options |= RES_DEFNAMES | RES_DNSRCH;	/* XXX */
#endif

	/* arrange a return receipt if requested */
D 371
	if (e->e_receiptto != NULL && bitnset(M_LOCALMAILER, m->m_flags))
E 371
I 371
	if (rcode == EX_OK && e->e_receiptto != NULL &&
	    bitnset(M_LOCALMAILER, m->m_flags))
E 371
	{
		e->e_flags |= EF_SENDRECEIPT;
		/* do we want to send back more info? */
	}

	/*
	**  Do final status disposal.
	**	We check for something in tobuf for the SMTP case.
	**	If we got a temporary failure, arrange to queue the
	**		addressees.
	*/

  give_up:
	if (tobuf[0] != '\0')
D 377
		giveresponse(rcode, m, mci, e);
E 377
I 377
D 461
		giveresponse(rcode, m, mci, ctladdr, e);
E 461
I 461
		giveresponse(rcode, m, mci, ctladdr, xstart, e);
E 461
E 377
	for (to = tochain; to != NULL; to = to->q_tchain)
	{
		if (rcode != EX_OK)
D 458
			markfailure(e, to, rcode);
E 458
I 458
			markfailure(e, to, mci, rcode);
E 458
D 465
		else
E 465
I 465
		else if (!bitset(QBADADDR|QQUEUEUP, to->q_flags))
E 465
		{
			to->q_flags |= QSENT;
I 455
			to->q_statdate = curtime();
E 455
			e->e_nsent++;
I 371
D 445
			if (e->e_receiptto != NULL &&
			    bitnset(M_LOCALMAILER, m->m_flags))
E 445
I 445
			if (bitnset(M_LOCALMAILER, m->m_flags) &&
			    (e->e_receiptto != NULL ||
			     bitset(QPINGONSUCCESS, to->q_flags)))
E 445
			{
I 445
D 493
				to->q_flags |= QREPORT;
E 493
I 493
				to->q_flags |= QDELIVERED;
E 493
I 491
				to->q_status = "2.1.5";
E 491
E 445
				fprintf(e->e_xfp, "%s... Successfully delivered\n",
I 465
					to->q_paddr);
			}
			else if (bitset(QPINGONSUCCESS, to->q_flags) &&
I 482
				 bitset(QPRIMARY, to->q_flags) &&
E 482
				 !bitset(MCIF_DSN, mci->mci_flags))
			{
				to->q_flags |= QRELAYED;
				fprintf(e->e_xfp, "%s... relayed; expect no further notifications\n",
E 465
					to->q_paddr);
			}
E 371
		}
	}

	/*
	**  Restore state and return.
	*/
I 361

D 504
#ifdef XDEBUG
E 504
I 504
#if XDEBUG
E 504
	{
		char wbuf[MAXLINE];

		/* make absolutely certain 0, 1, and 2 are in use */
D 365
		sprintf(wbuf, "%s... end of deliver(%s)", e->e_to, m->m_name);
E 365
I 365
		sprintf(wbuf, "%s... end of deliver(%s)",
			e->e_to == NULL ? "NO-TO-LIST" : e->e_to,
			m->m_name);
E 365
		checkfd012(wbuf);
	}
#endif
E 361

	errno = 0;
	define('g', (char *) NULL, e);
	return (rcode);
E 312
E 243
E 72
}
/*
I 312
**  MARKFAILURE -- mark a failure on a specific address.
**
**	Parameters:
**		e -- the envelope we are sending.
**		q -- the address to mark.
I 458
**		mci -- mailer connection information.
E 458
**		rcode -- the code signifying the particular failure.
**
**	Returns:
**		none.
**
**	Side Effects:
**		marks the address (and possibly the envelope) with the
**			failure so that an error will be returned or
**			the message will be queued, as appropriate.
*/

I 500
void
E 500
D 458
markfailure(e, q, rcode)
E 458
I 458
markfailure(e, q, mci, rcode)
E 458
	register ENVELOPE *e;
	register ADDRESS *q;
I 458
	register MCI *mci;
E 458
	int rcode;
{
D 458
	char buf[MAXLINE];
E 458
I 458
	char *stat = NULL;
E 458
D 337
	extern char *pintvl();
E 337

D 390
	if (rcode == EX_OK)
		return;
D 342
	else if (rcode != EX_TEMPFAIL && rcode != EX_IOERR && rcode != EX_OSERR)
		q->q_flags |= QBADADDR;
	else if (curtime() > e->e_ctime + TimeOuts.to_q_return)
	{
		if (!bitset(EF_TIMEOUT, e->e_flags))
		{
			(void) sprintf(buf, "Cannot send message for %s",
				pintvl(TimeOuts.to_q_return, FALSE));
			if (e->e_message != NULL)
				free(e->e_message);
			e->e_message = newstr(buf);
			message(buf);
		}
		q->q_flags |= QBADADDR;
		e->e_flags |= EF_TIMEOUT;
		fprintf(e->e_xfp, "421 %s... Message timed out\n", q->q_paddr);
	}
	else
	{
E 342
I 342
	else if (rcode == EX_TEMPFAIL)
E 390
I 390
	switch (rcode)
	{
	  case EX_OK:
		break;

	  case EX_TEMPFAIL:
	  case EX_IOERR:
	  case EX_OSERR:
E 390
E 342
		q->q_flags |= QQUEUEUP;
D 342
		if (TimeOuts.to_q_warning > 0 &&
		    curtime() > e->e_ctime + TimeOuts.to_q_warning)
		{
			if (!bitset(EF_WARNING, e->e_flags) &&
D 339
			    e->e_class >= 0)
E 339
I 339
			    e->e_class >= 0 &&
			    strcmp(e->e_from.q_paddr, "<>") != 0)
E 339
			{
				(void) sprintf(buf,
					"warning: cannot send message for %s",
					pintvl(TimeOuts.to_q_warning, FALSE));
				if (e->e_message != NULL)
					free(e->e_message);
				e->e_message = newstr(buf);
				message(buf);
				e->e_flags |= EF_WARNING|EF_TIMEOUT;
			}
			fprintf(e->e_xfp,
				"%s... Warning: message still undelivered after %s\n",
				q->q_paddr, pintvl(TimeOuts.to_q_warning, FALSE));
			fprintf(e->e_xfp, "Will keep trying until message is %s old\n",
				pintvl(TimeOuts.to_q_return, FALSE));
		}
	}
E 342
I 342
D 390
	else if (rcode != EX_IOERR && rcode != EX_OSERR)
E 390
I 390
		break;

	  default:
E 390
		q->q_flags |= QBADADDR;
I 390
		break;
	}
I 458

I 492
	/* find most specific error code possible */
E 492
	if (q->q_status == NULL && mci != NULL)
		q->q_status = mci->mci_status;
D 492
	switch (rcode)
E 492
I 492
	if (q->q_status == NULL)
		q->q_status = e->e_status;
	if (q->q_status == NULL)
E 492
	{
D 492
	  case EX_USAGE:
D 464
		stat = "550";
E 464
I 464
		stat = "5.5.4";
E 464
		break;
E 492
I 492
		switch (rcode)
		{
		  case EX_USAGE:
			stat = "5.5.4";
			break;
E 492

D 492
	  case EX_DATAERR:
D 464
		stat = "501";
E 464
I 464
		stat = "5.5.2";
E 464
		break;
E 492
I 492
		  case EX_DATAERR:
			stat = "5.5.2";
			break;
E 492

D 464
	  case EX_NOINPUT:
E 464
D 492
	  case EX_NOUSER:
	  case EX_NOHOST:
I 464
		stat = "5.1.1";
		break;
E 492
I 492
		  case EX_NOUSER:
			stat = "5.1.1";
			break;
E 492

D 492
	  case EX_NOINPUT:
E 464
	  case EX_CANTCREAT:
	  case EX_NOPERM:
D 464
		stat = "550";
E 464
I 464
		stat = "5.3.0";
E 464
		break;
E 492
I 492
		  case EX_NOHOST:
			stat = "5.1.2";
			break;
E 492

D 492
	  case EX_UNAVAILABLE:
	  case EX_SOFTWARE:
	  case EX_OSFILE:
	  case EX_PROTOCOL:
	  case EX_CONFIG:
D 464
		stat = "554";
E 464
I 464
		stat = "5.5.0";
E 464
		break;
E 492
I 492
		  case EX_NOINPUT:
		  case EX_CANTCREAT:
		  case EX_NOPERM:
			stat = "5.3.0";
			break;
E 492

D 492
	  case EX_OSERR:
	  case EX_IOERR:
D 464
		stat = "451";
E 464
I 464
		stat = "4.5.0";
E 464
		break;
E 492
I 492
		  case EX_UNAVAILABLE:
		  case EX_SOFTWARE:
		  case EX_OSFILE:
		  case EX_PROTOCOL:
		  case EX_CONFIG:
			stat = "5.5.0";
			break;
E 492

D 492
	  case EX_TEMPFAIL:
D 464
		stat = "426";
E 464
I 464
		stat = "4.2.0";
E 464
		break;
E 492
I 492
		  case EX_OSERR:
		  case EX_IOERR:
			stat = "4.5.0";
			break;

		  case EX_TEMPFAIL:
			stat = "4.2.0";
			break;
		}
		if (stat != NULL)
			q->q_status = stat;
E 492
	}
D 491
	if (stat != NULL && q->q_status == NULL)
E 491
I 491
D 492
	if (stat != NULL)
E 491
		q->q_status = stat;
E 492

E 458
I 445
	q->q_statdate = curtime();
D 459
	q->q_statmta = newstr(CurHostName);
E 459
I 459
	if (CurHostName != NULL && CurHostName[0] != '\0')
		q->q_statmta = newstr(CurHostName);
E 459
I 458
	if (rcode != EX_OK && q->q_rstatus == NULL)
	{
		char buf[30];

		(void) sprintf(buf, "%d", rcode);
		q->q_rstatus = newstr(buf);
	}
E 458
E 445
E 390
E 342
}
/*
**  ENDMAILER -- Wait for mailer to terminate.
**
**	We should never get fatal errors (e.g., segmentation
**	violation), so we report those specially.  For other
**	errors, we choose a status message (into statmsg),
**	and if it represents an error, we print it.
**
**	Parameters:
**		pid -- pid of mailer.
**		e -- the current envelope.
**		pv -- the parameter vector that invoked the mailer
**			(for error messages).
**
**	Returns:
**		exit code of mailer.
**
**	Side Effects:
**		none.
*/

I 500
int
E 500
endmailer(mci, e, pv)
	register MCI *mci;
	register ENVELOPE *e;
	char **pv;
{
	int st;

	/* close any connections */
	if (mci->mci_in != NULL)
D 397
		(void) xfclose(mci->mci_in, pv[0], "mci_in");
E 397
I 397
		(void) xfclose(mci->mci_in, mci->mci_mailer->m_name, "mci_in");
E 397
	if (mci->mci_out != NULL)
D 397
		(void) xfclose(mci->mci_out, pv[0], "mci_out");
E 397
I 397
		(void) xfclose(mci->mci_out, mci->mci_mailer->m_name, "mci_out");
E 397
	mci->mci_in = mci->mci_out = NULL;
	mci->mci_state = MCIS_CLOSED;

	/* in the IPC case there is nothing to wait for */
	if (mci->mci_pid == 0)
		return (EX_OK);

	/* wait for the mailer process to die and collect status */
	st = waitfor(mci->mci_pid);
	if (st == -1)
	{
		syserr("endmailer %s: wait", pv[0]);
		return (EX_SOFTWARE);
	}

D 359
	/* see if it died a horrid death */
	if ((st & 0377) != 0)
E 359
I 359
	if (WIFEXITED(st))
E 359
	{
D 359
		syserr("mailer %s died with signal %o", pv[0], st);
E 359
I 359
		/* normal death -- return status */
		return (WEXITSTATUS(st));
	}
E 359

D 359
		/* log the arguments */
		if (e->e_xfp != NULL)
		{
			register char **av;
E 359
I 359
	/* it died a horrid death */
D 397
	syserr("mailer %s died with signal %o", pv[0], st);
E 397
I 397
D 400
	syserr("mailer %s died with signal %o", mci->mci_mailer->m_name, st);
E 400
I 400
	syserr("451 mailer %s died with signal %o",
		mci->mci_mailer->m_name, st);
E 400
E 397
E 359

D 359
			fprintf(e->e_xfp, "Arguments:");
			for (av = pv; *av != NULL; av++)
				fprintf(e->e_xfp, " %s", *av);
			fprintf(e->e_xfp, "\n");
		}
E 359
I 359
	/* log the arguments */
D 396
	if (e->e_xfp != NULL)
E 396
I 396
	if (pv != NULL && e->e_xfp != NULL)
E 396
	{
		register char **av;
E 359

D 359
		ExitStat = EX_TEMPFAIL;
		return (EX_TEMPFAIL);
E 359
I 359
		fprintf(e->e_xfp, "Arguments:");
		for (av = pv; *av != NULL; av++)
			fprintf(e->e_xfp, " %s", *av);
		fprintf(e->e_xfp, "\n");
E 359
	}

D 359
	/* normal death -- return status */
	st = (st >> 8) & 0377;
	return (st);
E 359
I 359
	ExitStat = EX_TEMPFAIL;
	return (EX_TEMPFAIL);
E 359
}
/*
E 312
**  GIVERESPONSE -- Interpret an error response from a mailer
**
**	Parameters:
**		stat -- the status code from the mailer (high byte
**			only; core dumps must have been taken care of
**			already).
D 154
**		force -- if set, force an error message output, even
**			if the mailer seems to like to print its own
**			messages.
E 154
D 290
**		m -- the mailer descriptor for this mailer.
E 290
I 290
**		m -- the mailer info for this mailer.
**		mci -- the mailer connection info -- can be NULL if the
**			response is given before the connection is made.
I 377
**		ctladdr -- the controlling address for the recipient
**			address(es).
I 461
**		xstart -- the transaction start time, for computing
**			transaction delays.
E 461
E 377
**		e -- the current envelope.
E 290
**
**	Returns:
D 20
**		none.
E 20
I 20
D 36
**		stat.
E 36
I 36
**		none.
E 36
E 20
**
**	Side Effects:
D 7
**		Error may be set.
E 7
I 7
**		Errors may be incremented.
E 7
**		ExitStat may be set.
D 54
**
D 4
**	Requires:
**		usrerr
**		syserr
**		flagset
**		logmsg (sys)
**
E 4
**	Called By:
**		deliver
E 54
D 4
**
**	History:
**		2/18/80 -- broken from deliver.
E 4
*/

I 500
void
E 500
D 154
giveresponse(stat, force, m)
E 154
I 154
D 172
/*ARGSUSED*/
E 172
D 161
giveresponse(stat, m)
E 161
I 161
D 290
giveresponse(stat, m, e)
E 290
I 290
D 377
giveresponse(stat, m, mci, e)
E 377
I 377
D 461
giveresponse(stat, m, mci, ctladdr, e)
E 461
I 461
giveresponse(stat, m, mci, ctladdr, xstart, e)
E 461
E 377
E 290
E 161
E 154
	int stat;
D 109
	int force;
E 109
I 109
D 154
	bool force;
E 109
	register struct mailer *m;
E 154
I 154
	register MAILER *m;
I 290
	register MCI *mci;
I 377
	ADDRESS *ctladdr;
I 461
	time_t xstart;
E 461
E 377
E 290
I 161
	ENVELOPE *e;
E 161
E 154
{
D 335
	register char *statmsg;
E 335
I 335
	register const char *statmsg;
E 335
	extern char *SysExMsg[];
	register int i;
D 202
	extern int N_SysEx;
E 202
I 202
D 214
	extern int N_SysEx, h_errno;
E 214
I 214
	extern int N_SysEx;
D 342
#ifdef NAMED_BIND
	extern int h_errno;
#endif
E 342
E 214
E 202
I 11
D 51
	extern long MsgSize;
E 51
D 161
	char buf[30];
E 161
I 161
	char buf[MAXLINE];
I 298
D 334
	extern char *errstring();
E 334
E 298
I 172

D 290
#ifdef lint
	if (m == NULL)
		return;
#endif lint
E 172
E 161
I 22
D 36
	extern char *sprintf();
E 36
E 22
E 11

E 290
I 54
	/*
	**  Compute status message from code.
	*/

E 54
	i = stat - EX__BASE;
D 154
	if (i < 0 || i > N_SysEx)
		statmsg = NULL;
E 154
I 154
	if (stat == 0)
I 313
	{
E 313
		statmsg = "250 Sent";
I 313
D 315
		if (e->e_message != NULL)
E 315
I 315
		if (e->e_statmsg != NULL)
E 315
		{
D 315
			(void) sprintf(buf, "%s (%s)", statmsg, e->e_message);
E 315
I 315
			(void) sprintf(buf, "%s (%s)", statmsg, e->e_statmsg);
E 315
			statmsg = buf;
		}
	}
E 313
	else if (i < 0 || i > N_SysEx)
	{
		(void) sprintf(buf, "554 unknown mailer error %d", stat);
		stat = EX_UNAVAILABLE;
		statmsg = buf;
	}
I 161
	else if (stat == EX_TEMPFAIL)
	{
D 178
		extern char *sys_errlist[];
		extern int sys_nerr;

E 178
D 162
		(void) sprintf(buf, "%.3s ", SysExMsg[i]);
		if (errno > 0 && errno < sys_nerr)
E 162
I 162
D 298
		(void) strcpy(buf, SysExMsg[i]);
E 298
I 298
		(void) strcpy(buf, SysExMsg[i] + 1);
E 298
I 214
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
E 214
D 193
		if (errno != 0)
E 193
I 193
		if (h_errno == TRY_AGAIN)
E 193
E 162
D 298
		{
D 162
			(void) strcat(buf, sys_errlist[errno]);
			(void) strcat(buf, " [deferred]");
E 162
I 162
D 178
			(void) strcat(buf, ": ");
			if (errno > 0 && errno < sys_nerr)
				(void) strcat(buf, sys_errlist[errno]);
			else
			{
				char xbuf[30];
E 178
I 178
			extern char *errstring();
E 178

E 298
I 185
D 193
			statmsg = errstring(errno);
E 193
I 193
D 347
			statmsg = errstring(h_errno+MAX_ERRNO);
E 347
I 347
			statmsg = errstring(h_errno+E_DNSBASE);
E 347
E 193
D 298
		}
E 298
		else
I 214
#endif
E 214
		{
I 193
			if (errno != 0)
D 298
			{
				extern char *errstring();

E 298
				statmsg = errstring(errno);
D 298
			}
E 298
			else
			{
E 193
#ifdef SMTP
D 193
			extern char SmtpError[];
E 193
I 193
D 393
				extern char SmtpError[];
E 193

E 393
D 193
			statmsg = SmtpError;
E 193
I 193
				statmsg = SmtpError;
E 193
D 256
#else SMTP
E 256
I 256
#else /* SMTP */
E 256
D 193
			statmsg = NULL;
E 193
I 193
				statmsg = NULL;
E 193
D 256
#endif SMTP
E 256
I 256
#endif /* SMTP */
E 256
I 193
			}
E 193
		}
		if (statmsg != NULL && statmsg[0] != '\0')
		{
E 185
D 178
				(void) sprintf(xbuf, "Error %d", errno);
				(void) strcat(buf, xbuf);
			}
E 178
I 178
			(void) strcat(buf, ": ");
D 185
			(void) strcat(buf, errstring(errno));
E 185
I 185
			(void) strcat(buf, statmsg);
E 185
E 178
E 162
		}
D 162
		else
			(void) strcat(buf, "deferred");
E 162
		statmsg = buf;
	}
I 342
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
	else if (stat == EX_NOHOST && h_errno != 0)
	{
D 347
		statmsg = errstring(h_errno + MAX_ERRNO);
E 347
I 347
		statmsg = errstring(h_errno + E_DNSBASE);
E 347
D 424
		(void) sprintf(buf, "%s (%s)", SysExMsg[i], statmsg);
E 424
I 424
		(void) sprintf(buf, "%s (%s)", SysExMsg[i] + 1, statmsg);
E 424
		statmsg = buf;
	}
#endif
E 342
E 161
E 154
	else
I 185
	{
E 185
		statmsg = SysExMsg[i];
I 298
		if (*statmsg++ == ':')
		{
			(void) sprintf(buf, "%s: %s", statmsg, errstring(errno));
			statmsg = buf;
		}
E 298
I 185
	}
E 185
I 154

	/*
	**  Print the message as appropriate
	*/

E 154
D 161
	if (stat == 0)
E 161
I 161
	if (stat == EX_OK || stat == EX_TEMPFAIL)
I 371
	{
		extern char MsgBuf[];

E 371
E 161
I 33
D 154
	{
E 33
D 41
		statmsg = "ok";
E 41
I 41
D 45
		if (bitset(M_FINAL, m->m_flags))
E 45
I 45
D 123
		if (bitset(M_LOCAL, m->m_flags))
E 45
			statmsg = "delivered";
		else
			statmsg = "queued";
E 123
I 123
D 127
		statmsg = "sent";
E 123
E 41
I 33
D 106
		if (Verbose)
D 41
			message("050", "ok");
E 41
I 41
D 42
			message("050", statmsg);
E 42
I 42
			message(Arpa_Info, statmsg);
E 106
I 106
		message(Arpa_Info, statmsg);
E 127
I 127
		statmsg = "250 sent";
E 154
D 280
		message(Arpa_Info, &statmsg[4]);
E 280
I 280
D 296
		message(&statmsg[4]);
E 296
I 296
D 417
		message(&statmsg[4], errstring(errno));
E 417
I 417
		message("%s", &statmsg[4]);
E 417
I 371
		if (stat == EX_TEMPFAIL && e->e_xfp != NULL)
			fprintf(e->e_xfp, "%s\n", &MsgBuf[4]);
	}
E 371
E 296
E 280
E 127
E 106
E 42
E 41
D 154
	}
E 154
I 79
D 127
# ifdef QUEUE
E 127
E 79
I 69
D 161
	else if (stat == EX_TEMPFAIL)
D 154
	{
E 154
D 106
		if (Verbose)
			message(Arpa_Info, "transmission deferred");
E 106
I 106
D 123
		message(Arpa_Info, "transmission deferred");
E 123
I 123
D 141
		message(Arpa_Info, "deferred");
E 141
I 141
D 143
		message(Arpa_Info, "queued");
E 143
I 143
		message(Arpa_Info, "deferred");
E 161
E 143
E 141
E 123
E 106
D 154
	}
E 154
I 79
D 127
# endif QUEUE
E 127
E 79
E 69
E 33
	else
	{
I 424
		char mbuf[8];

E 424
D 7
		Error++;
E 7
I 7
		Errors++;
I 154
D 296
		usrerr(statmsg);
E 296
I 296
D 424
		usrerr(statmsg, errstring(errno));
E 424
I 424
		sprintf(mbuf, "%.3s %%s", statmsg);
		usrerr(mbuf, &statmsg[4]);
E 424
E 296
E 154
I 92
D 152
		FatalErrors = TRUE;
E 152
I 152
D 156
		CurEnv->e_flags |= EF_FATALERRS;
E 156
E 152
E 92
E 7
D 154
		if (statmsg == NULL && m->m_badstat != 0)
		{
			stat = m->m_badstat;
			i = stat - EX__BASE;
# ifdef DEBUG
			if (i < 0 || i >= N_SysEx)
				syserr("Bad m_badstat %d", stat);
			else
# endif DEBUG
D 114
			statmsg = SysExMsg[i];
E 114
I 114
				statmsg = SysExMsg[i];
E 114
		}
		if (statmsg == NULL)
			usrerr("unknown mailer response %d", stat);
D 20
		else if (force || !flagset(M_QUIET, m->m_flags))
E 20
I 20
D 33
		else if (force || !bitset(M_QUIET, m->m_flags))
E 33
I 33
		else if (force || !bitset(M_QUIET, m->m_flags) || Verbose)
E 33
E 20
D 127
			usrerr("%s", statmsg);
E 127
I 127
			usrerr(statmsg);
E 127
I 114
D 152
		else
E 152
I 152
		else if (Xscript != NULL)
E 152
D 127
			fprintf(Xscript, "%s\n", statmsg);
E 127
I 127
			fprintf(Xscript, "%s\n", &statmsg[4]);
E 154
E 127
E 114
	}

	/*
	**  Final cleanup.
	**	Log a record of the transaction.  Compute the new
	**	ExitStat -- if we already had an error, stick with
	**	that.
	*/

D 11
# ifdef LOG
E 11
D 154
	if (statmsg == NULL)
D 11
		logmsg(LOG_INFO, "%s->%s: error %d", From.q_paddr, To, stat);
	else
		logmsg(LOG_INFO, "%s->%s: %s", From.q_paddr, To, statmsg);
E 11
I 11
	{
D 36
		sprintf(buf, "error %d", stat);
E 36
I 36
D 127
		(void) sprintf(buf, "error %d", stat);
E 127
I 127
		(void) sprintf(buf, "554 error %d", stat);
E 127
E 36
		statmsg = buf;
	}

D 143
# ifdef LOG
E 143
I 143
	/* log it in the system log */
E 154
E 143
D 18
	logmsg(LOG_INFO, "%s->%s: %ld: %s", From.q_paddr, To, MsgSize, statmsg);
E 18
I 18
D 99
	syslog(LOG_INFO, "%s->%s: %ld: %s", From.q_paddr, To, MsgSize, statmsg);
E 99
I 99
D 117
	syslog(LOG_INFO, "%s->%s: %ld: %s", CurEnv->e_from.q_paddr, CurEnv->e_to, CurEnv->e_msgsize, statmsg);
E 117
I 117
D 118
	if (LogLevel > 1)
E 118
I 118
D 273
	if (LogLevel > ((stat == 0 || stat == EX_TEMPFAIL) ? 3 : 2))
E 273
I 273
	if (LogLevel > ((stat == EX_TEMPFAIL) ? 8 : (stat == EX_OK) ? 7 : 6))
E 273
E 118
D 121
		syslog(LOG_INFO, "%s: to=%s, stat=%s", MsgId, CurEnv->e_to, statmsg);
E 121
I 121
D 122
		syslog(LOG_INFO, "%s: to=%s, stat=%s", CurEnv->e_id,
				  CurEnv->e_to, statmsg);
E 122
I 122
D 143
	{
		extern char *pintvl();
E 143
I 143
D 247
		logdelivery(&statmsg[4]);
E 247
I 247
D 290
		logdelivery(&statmsg[4], e);
E 290
I 290
D 377
		logdelivery(m, mci, &statmsg[4], e);
E 377
I 377
D 461
		logdelivery(m, mci, &statmsg[4], ctladdr, e);
E 461
I 461
		logdelivery(m, mci, &statmsg[4], ctladdr, xstart, e);
E 461
E 377
E 290
E 247
E 143

I 418
	if (tTd(11, 2))
		printf("giveresponse: stat=%d, e->e_message=%s\n",
D 454
			stat, e->e_message);
E 454
I 454
			stat, e->e_message == NULL ? "<NULL>" : e->e_message);
E 454

E 418
D 143
		syslog(LOG_INFO, "%s: to=%s, delay=%s, stat=%s", CurEnv->e_id,
D 124
		       CurEnv->e_to, pintvl(CurTime - CurEnv->e_ctime, TRUE),
E 124
I 124
		       CurEnv->e_to, pintvl(curtime() - CurEnv->e_ctime, TRUE),
E 124
D 127
		       statmsg);
E 127
I 127
		       &statmsg[4]);
E 127
	}
E 122
E 121
E 117
E 99
E 18
E 11
# endif LOG
E 143
I 143
D 154
	/* set the exit status appropriately */
E 154
E 143
I 79
D 127
# ifdef QUEUE
E 127
E 79
D 5
	if (ExitStat == EX_OK)
		ExitStat = stat;
E 5
I 5
D 69
	setstat(stat);
E 69
I 69
	if (stat != EX_TEMPFAIL)
I 79
D 127
# endif QUEUE
E 127
E 79
		setstat(stat);
I 161
D 384
	if (stat != EX_OK)
E 384
I 384
	if (stat != EX_OK && (stat != EX_TEMPFAIL || e->e_message == NULL))
E 384
	{
		if (e->e_message != NULL)
			free(e->e_message);
		e->e_message = newstr(&statmsg[4]);
	}
I 162
	errno = 0;
I 214
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
E 214
I 193
	h_errno = 0;
I 214
#endif
E 214
E 193
E 162
E 161
I 143
}
/*
**  LOGDELIVERY -- log the delivery in the system log
**
I 385
**	Care is taken to avoid logging lines that are too long, because
**	some versions of syslog have an unfortunate proclivity for core
**	dumping.  This is a hack, to be sure, that is at best empirical.
**
E 385
**	Parameters:
D 290
**		stat -- the message to print for the status
E 290
I 290
**		m -- the mailer info.  Can be NULL for initial queue.
**		mci -- the mailer connection info -- can be NULL if the
**			log is occuring when no connection is active.
**		stat -- the message to print for the status.
I 377
**		ctladdr -- the controlling address for the to list.
I 461
**		xstart -- the transaction start time, used for
**			computing transaction delay.
E 461
E 377
**		e -- the current envelope.
E 290
**
**	Returns:
**		none
**
**	Side Effects:
**		none
*/

I 500
void
E 500
I 385
D 391
#ifndef SYSLOG_BUFSIZE
# define SYSLOG_BUFSIZE	1024
#endif

E 391
E 385
D 247
logdelivery(stat)
E 247
I 247
D 290
logdelivery(stat, e)
E 290
I 290
D 377
logdelivery(m, mci, stat, e)
E 377
I 377
D 461
logdelivery(m, mci, stat, ctladdr, e)
E 461
I 461
logdelivery(m, mci, stat, ctladdr, xstart, e)
E 461
E 377
	MAILER *m;
	register MCI *mci;
E 290
E 247
D 500
	char *stat;
E 500
I 500
	const char *stat;
E 500
I 377
	ADDRESS *ctladdr;
I 461
	time_t xstart;
E 461
E 377
I 247
	register ENVELOPE *e;
E 247
{
I 287
D 291
	char *delay;
E 291
I 291
# ifdef LOG
I 377
	register char *bp;
I 385
	register char *p;
	int l;
E 385
E 377
E 291
I 290
D 340
	char *curhost;
E 340
I 291
D 295
	char *mname;
	char *relay;
	char *hostdetail;
E 295
I 292
	char buf[512];
E 292
E 291
E 290
E 287
D 337
	extern char *pintvl();
I 291
	extern char *macvalue();
E 337
E 291

I 391
#  if (SYSLOG_BUFSIZE) >= 256
E 391
D 291
# ifdef LOG
E 291
I 290
D 295
	if (mci != NULL && mci->mci_host != NULL)
		curhost = mci->mci_host;
	else
		curhost = CurHostName;
E 295
I 295
D 377
	(void) sprintf(buf, "delay=%s", pintvl(curtime() - e->e_ctime, TRUE));
E 377
I 377
	bp = buf;
	if (ctladdr != NULL)
	{
		strcpy(bp, ", ctladdr=");
D 385
		strcat(bp, ctladdr->q_paddr);
E 385
I 385
D 388
		l = strlen(ctladdr->q_paddr);
		if (l > 83)
			sprintf(bp, "%.40s...%s",
				ctladdr->q_paddr, ctladdr->q_paddr + l - 40);
		else
			strcat(bp, ctladdr->q_paddr);
E 388
I 388
D 389
		strcpy(bp, shortenstring(ctladdr->q_paddr, 83));
E 389
I 389
		strcat(bp, shortenstring(ctladdr->q_paddr, 83));
E 389
E 388
E 385
		bp += strlen(bp);
		if (bitset(QGOODUID, ctladdr->q_flags))
		{
			(void) sprintf(bp, " (%d/%d)",
					ctladdr->q_uid, ctladdr->q_gid);
			bp += strlen(bp);
		}
	}
E 377
E 295

I 377
D 461
	(void) sprintf(bp, ", delay=%s", pintvl(curtime() - e->e_ctime, TRUE));
E 461
I 461
	sprintf(bp, ", delay=%s", pintvl(curtime() - e->e_ctime, TRUE));
E 461
	bp += strlen(bp);

I 461
	if (xstart != (time_t) 0)
	{
		sprintf(bp, ", xdelay=%s", pintvl(curtime() - xstart, TRUE));
		bp += strlen(bp);
	}

E 461
E 377
E 290
D 247
	syslog(LOG_INFO, "%s: to=%s, delay=%s, stat=%s", CurEnv->e_id,
	       CurEnv->e_to, pintvl(curtime() - CurEnv->e_ctime, TRUE), stat);
E 247
I 247
D 287
	syslog(LOG_INFO, "%s: to=%s, delay=%s, stat=%s", e->e_id,
	       e->e_to, pintvl(curtime() - e->e_ctime, TRUE), stat);
E 287
I 287
D 291
	delay = pintvl(curtime() - e->e_ctime, TRUE);
D 288
	if (strcmp(stat, "Sent") != 0 || CurHostName == NULL)
E 288
I 288
D 290
	if (strcmp(stat, "Sent") != 0 || CurHostName == NULL ||
	    strcmp(CurHostName, "localhost") == 0)
E 290
I 290
	if (strcmp(stat, "Sent") != 0 || m == NULL || curhost == NULL ||
	    strcmp(curhost, "localhost") == 0)
E 291
I 291
D 295
	if (curhost == NULL || curhost[0] == '/')
E 295
I 295
	if (m != NULL)
E 295
E 291
E 290
E 288
	{
D 291
		syslog(LOG_INFO, "%s: to=%s, delay=%s, stat=%s",
		       e->e_id, e->e_to, delay, stat);
E 291
I 291
D 295
		hostdetail = macvalue('h', e);
		if (hostdetail == NULL || hostdetail[0] == '\0')
			hostdetail = "local";
E 295
I 295
D 377
		(void) strcat(buf, ", mailer=");
		(void) strcat(buf, m->m_name);
E 377
I 377
		(void) strcpy(bp, ", mailer=");
		(void) strcat(bp, m->m_name);
		bp += strlen(bp);
E 377
E 295
E 291
	}
D 295
	else
E 295
I 295

	if (mci != NULL && mci->mci_host != NULL)
E 295
	{
D 288
		char *p;
E 288
I 288
D 291
		char *p1, *p2;
E 288
		extern char *macvalue();

D 290
		if (CurHostName[0] == '/')
E 290
I 290
		if (curhost[0] == '/')
E 290
		{
D 288
			p = macvalue('h', e);
			if (p == NULL || p[0] == '\0')
				p = "local";
E 288
I 288
			p1 = macvalue('h', e);
			if (p1 == NULL || p1[0] == '\0')
				p1 = "local";
D 290
			p2 = CurHostName;
E 290
I 290
			p2 = curhost;
E 290
E 288
		}
E 291
# ifdef DAEMON
D 291
		else
		{
			extern struct sockaddr_in CurHostAddr;
			extern char *inet_ntoa();
E 291
I 291
D 310
		extern struct sockaddr_in CurHostAddr;
		extern char *inet_ntoa();
E 310
I 310
		extern SOCKADDR CurHostAddr;
D 337
		extern char *anynet_ntoa();
E 337
E 310
I 295
# endif
E 295
E 291

D 288
			p = inet_ntoa(CurHostAddr.sin_addr);
E 288
I 288
D 290
			p1 = CurHostName;
E 290
I 290
D 291
			p1 = curhost;
E 290
			p2 = inet_ntoa(CurHostAddr.sin_addr);
E 288
		}
E 291
I 291
D 295
		hostdetail = inet_ntoa(CurHostAddr.sin_addr);
# else
		hostdetail = "?";
E 295
I 295
D 377
		(void) strcat(buf, ", relay=");
		(void) strcat(buf, mci->mci_host);
E 377
I 377
		(void) strcpy(bp, ", relay=");
		(void) strcat(bp, mci->mci_host);
E 377

# ifdef DAEMON
D 377
		(void) strcat(buf, " (");
D 310
		(void) strcat(buf, inet_ntoa(CurHostAddr.sin_addr));
E 310
I 310
		(void) strcat(buf, anynet_ntoa(&CurHostAddr));
E 310
		(void) strcat(buf, ")");
E 377
I 377
D 406
		(void) strcat(bp, " (");
E 406
I 406
		(void) strcat(bp, " [");
E 406
		(void) strcat(bp, anynet_ntoa(&CurHostAddr));
D 406
		(void) strcat(bp, ")");
E 406
I 406
		(void) strcat(bp, "]");
E 406
E 377
E 295
E 291
# endif
D 290
		syslog(LOG_INFO, "%s: to=%s, delay=%s, stat=Sent to %s (%s)",
D 288
		       e->e_id, e->e_to, delay, p, CurHostName);
E 288
I 288
		       e->e_id, e->e_to, delay, p1, p2);
E 290
I 290
D 291
		syslog(LOG_INFO, "%s: to=%s, delay=%s, mailer=%s, stat=Sent to %s (%s)",
		       e->e_id, e->e_to, delay, m->m_name, p1, p2);
E 291
E 290
E 288
	}
I 291
D 295

	if (m != NULL)
		mname = m->m_name;
E 295
D 423
	else
E 423
I 423
	else if (strcmp(stat, "queued") != 0)
E 423
D 295
		mname = "(unknown)";
E 295
I 295
	{
		char *p = macvalue('h', e);
E 295

D 292
	syslog(LOG_INFO, "%s: to=%s, delay=%s, mailer=%s, relay=%s (%s), stat=%s",
	       e->e_id, e->e_to, pintvl(curtime() - e->e_ctime, TRUE),
	       mname, curhost, hostdetail, stat);
E 292
I 292
D 295
	(void) sprintf(buf, "delay=%s, mailer=%s, relay=%s (%s)",
	       pintvl(curtime() - e->e_ctime, TRUE),
	       mname, curhost, hostdetail);
E 295
I 295
		if (p != NULL && p[0] != '\0')
		{
D 377
			(void) strcat(buf, ", relay=");
			(void) strcat(buf, p);
E 377
I 377
			(void) strcpy(bp, ", relay=");
			(void) strcat(bp, p);
E 377
		}
	}
I 382
	bp += strlen(bp);
I 385

D 391
	if ((bp - buf) > (sizeof buf - 220))
E 391
I 391
#define STATLEN		(((SYSLOG_BUFSIZE) - 100) / 4)
#if (STATLEN) < 63
# undef STATLEN
# define STATLEN	63
#endif
#if (STATLEN) > 203
# undef STATLEN
# define STATLEN	203
#endif

	if ((bp - buf) > (sizeof buf - ((STATLEN) + 20)))
E 391
	{
		/* desperation move -- truncate data */
D 391
		bp = buf + sizeof buf - 217;
E 391
I 391
		bp = buf + sizeof buf - ((STATLEN) + 17);
E 391
		strcpy(bp, "...");
		bp += 3;
	}

	(void) strcpy(bp, ", stat=");
	bp += strlen(bp);
D 391
	l = strlen(stat);
#define STATLEN		(((SYSLOG_BUFSIZE) - 100) / 8)
#if (STATLEN) < 30
# undef STATLEN
# define STATLEN	30
#endif
#if (STATLEN) > 100
# undef STATLEN
# define STATLEN	100
#endif
	if (l > (STATLEN * 2 + 3))
		sprintf(bp, "%.*s...%s", STATLEN, stat, stat + l - STATLEN);
	else
		(void) strcpy(bp, stat);
E 391
I 391

	(void) strcpy(bp, shortenstring(stat, (STATLEN)));
E 391
E 385
E 382
E 295
		
D 377
	syslog(LOG_INFO, "%s: to=%s, %s, stat=%s",
E 377
I 377
D 385
	syslog(LOG_INFO, "%s: to=%s%s, stat=%s",
E 377
	       e->e_id, e->e_to, buf, stat);
E 385
I 385
	l = SYSLOG_BUFSIZE - 100 - strlen(buf);
	p = e->e_to;
D 488
	while (strlen(p) >= l)
E 488
I 488
	while (strlen(p) >= (SIZE_T) l)
E 488
	{
		register char *q = strchr(p + l, ',');

D 387
		if (*q == NULL)
E 387
I 387
		if (q == NULL)
E 387
			break;
		syslog(LOG_INFO, "%s: to=%.*s [more]%s",
			e->e_id, ++q - p, p, buf);
		p = q;
	}
	syslog(LOG_INFO, "%s: to=%s%s", e->e_id, p, buf);
I 391

#  else		/* we have a very short log buffer size */

D 402
	l = SYSLOG_BUFSIZE - 40;
E 402
I 402
D 415
	l = SYSLOG_BUFSIZE - 80;
E 415
I 415
	l = SYSLOG_BUFSIZE - 85;
E 415
E 402
	p = e->e_to;
	while (strlen(p) >= l)
	{
		register char *q = strchr(p + l, ',');

		if (q == NULL)
			break;
		syslog(LOG_INFO, "%s: to=%.*s [more]",
			e->e_id, ++q - p, p);
		p = q;
	}
	syslog(LOG_INFO, "%s: to=%s", e->e_id, p);

	if (ctladdr != NULL)
	{
		bp = buf;
		strcpy(buf, "ctladdr=");
		bp += strlen(buf);
		strcpy(bp, shortenstring(ctladdr->q_paddr, 83));
		bp += strlen(buf);
		if (bitset(QGOODUID, ctladdr->q_flags))
		{
			(void) sprintf(bp, " (%d/%d)",
					ctladdr->q_uid, ctladdr->q_gid);
			bp += strlen(bp);
		}
		syslog(LOG_INFO, "%s: %s", e->e_id, buf);
	}
D 402
	syslog(LOG_INFO, "%s: delay=%s",
		e->e_id, pintvl(curtime() - e->e_ctime, TRUE));
E 402
I 402
	bp = buf;
	sprintf(bp, "delay=%s", pintvl(curtime() - e->e_ctime, TRUE));
	bp += strlen(bp);
I 461
	if (xstart != (time_t) 0)
	{
		sprintf(bp, ", xdelay=%s", pintvl(curtime() - xstart, TRUE));
		bp += strlen(bp);
	}
E 461
E 402

	if (m != NULL)
D 402
		syslog(LOG_INFO, "%s: mailer=%s", e->e_id, m->m_name);
E 402
I 402
	{
		sprintf(bp, ", mailer=%s", m->m_name);
		bp += strlen(bp);
	}
I 409
	syslog(LOG_INFO, "%s: %s", e->e_id, buf);
E 409
E 402

I 409
	buf[0] = '\0';
E 409
	if (mci != NULL && mci->mci_host != NULL)
	{
# ifdef DAEMON
		extern SOCKADDR CurHostAddr;
# endif

D 402
		(void) strcpy(buf, mci->mci_host);
E 402
I 402
D 409
		sprintf(bp, ", relay=%s", mci->mci_host);
E 409
I 409
D 413
		sprintf(buf, ", relay=%s", mci->mci_host);
E 413
I 413
		sprintf(buf, "relay=%s", mci->mci_host);
E 413
E 409
E 402

# ifdef DAEMON
D 402
		(void) strcat(buf, " (");
		(void) strcat(buf, anynet_ntoa(&CurHostAddr));
		(void) strcat(buf, ")");
E 402
I 402
D 406
		(void) strcat(bp, " (");
E 406
I 406
D 409
		(void) strcat(bp, " [");
E 406
		(void) strcat(bp, anynet_ntoa(&CurHostAddr));
D 406
		(void) strcat(bp, ")");
E 406
I 406
		(void) strcat(bp, "]");
E 409
I 409
		(void) strcat(buf, " [");
		(void) strcat(buf, anynet_ntoa(&CurHostAddr));
		(void) strcat(buf, "]");
E 409
E 406
E 402
# endif
D 402
		syslog(LOG_INFO, "%s: relay=%s", e->e_id, buf);
E 402
	}
D 423
	else
E 423
I 423
	else if (strcmp(stat, "queued") != 0)
E 423
	{
		char *p = macvalue('h', e);

		if (p != NULL && p[0] != '\0')
D 402
			syslog(LOG_INFO, "%s: relay=%s", e->e_id, p);
E 402
I 402
D 409
			sprintf(bp, ", relay=%s", p);
E 409
I 409
D 413
			sprintf(buf, ", relay=%s", p);
E 413
I 413
			sprintf(buf, "relay=%s", p);
E 413
E 409
E 402
	}
I 402
D 409
	syslog(LOG_INFO, "%s: %s", e->e_id, buf);
E 409
I 409
	if (buf[0] != '\0')
		syslog(LOG_INFO, "%s: %s", e->e_id, buf);
E 409
E 402

D 394
	strcpy(bp, ", stat=");
	bp += strlen(bp);

E 394
	syslog(LOG_INFO, "%s: stat=%s", e->e_id, shortenstring(stat, 63));
#  endif /* short log buffer */
E 391
E 385
E 292
E 291
E 287
E 247
D 256
# endif LOG
E 256
I 256
# endif /* LOG */
E 256
E 143
E 69
E 5
D 36
	return (stat);
E 36
}
/*
D 19
**  PUTHEADER -- insert the From header into some mail
E 19
I 19
D 100
**  PUTMESSAGE -- output a message to the final mailer.
E 100
I 100
**  PUTFROMLINE -- output a UNIX-style from line (or whatever)
E 100
E 19
**
D 19
**	For mailers such as 'msgs' that want the header inserted
**	into the mail, this edit filter inserts the From line and
D 13
**	then passes the rest of the message through.
E 19
I 19
D 100
**	This routine takes care of recreating the header from the
**	in-core copy, etc.
E 100
I 100
**	This can be made an arbitrary message separator by changing $l
E 100
E 19
E 13
I 13
**	then passes the rest of the message through.  If we have
**	managed to extract a date already, use that; otherwise,
**	use the current date/time.
E 13
**
I 100
D 181
**	One of the ugliest hacks seen by human eyes is
**	contained herein: UUCP wants those stupid
D 154
**	"remote from <host>" lines.  Why oh why does a
E 154
I 154
**	"emote from <host>" lines.  Why oh why does a
E 154
**	well-meaning programmer such as myself have to
**	deal with this kind of antique garbage????
E 181
I 181
**	One of the ugliest hacks seen by human eyes is contained herein:
**	UUCP wants those stupid "remote from <host>" lines.  Why oh why
**	does a well-meaning programmer such as myself have to deal with
**	this kind of antique garbage????
E 181
**
E 100
**	Parameters:
D 19
**		fp -- the file pointer for the output.
E 19
I 19
D 100
**		fp -- file to output onto.
**		m -- a mailer descriptor.
I 72
**		xdot -- if set, hide lines beginning with dot.
E 100
I 100
D 405
**		fp -- the file to output to.
**		m -- the mailer describing this entry.
E 405
I 405
**		mci -- the connection information.
**		e -- the envelope.
E 405
I 159
D 166
**		crlf -- set if we want a CRLF at the end of the line.
E 166
E 159
E 100
E 72
E 19
**
**	Returns:
D 19
**		none
E 19
I 19
D 100
**		none.
E 100
I 100
**		none
E 100
E 19
**
**	Side Effects:
D 19
**		Puts a "From" line in UNIX format, and then
**			outputs the rest of the message.
**
D 4
**	Requires:
**		fprintf (sys)
**		fgets (sys)
**		fputs (sys)
**		time (sys)
**		ctime (sys)
**		ferror (sys)
**		syserr
**		setstat
**
E 4
**	Called By:
**		deliver
E 19
I 19
D 100
**		The message is written onto fp.
E 100
I 100
**		outputs some text to fp.
E 100
E 19
D 4
**
**	History:
**		1/8/80 -- written.
E 4
*/

I 500
void
E 500
D 19
putheader(fp)
	register FILE *fp;
E 19
I 19
D 72
putmessage(fp, m)
E 72
I 72
D 100
putmessage(fp, m, xdot)
E 72
	FILE *fp;
	struct mailer *m;
I 72
	bool xdot;
E 100
I 100
D 159
putfromline(fp, m)
E 159
I 159
D 166
putfromline(fp, m, crlf)
E 166
I 166
D 247
putfromline(fp, m)
E 247
I 247
D 405
putfromline(fp, m, e)
E 247
E 166
E 159
	register FILE *fp;
	register MAILER *m;
E 405
I 405
putfromline(mci, e)
	register MCI *mci;
E 405
I 247
	ENVELOPE *e;
E 247
E 100
E 72
E 19
{
I 173
D 181
	char *template = "$l\n";
E 181
I 181
D 274
	char *template = "\001l\n";
E 274
I 274
	char *template = "\201l\n";
E 274
E 181
E 173
D 19
	char buf[MAXLINE + 1];
	long tim;
	extern char *ctime();
E 19
I 19
D 100
	char buf[BUFSIZ];
E 100
I 100
	char buf[MAXLINE];
E 100
D 72
	register int i;
E 72
D 54
	HDR *h;
E 19
I 15
	register char *p;
E 54
I 54
D 89
	register HDR *h;
E 54
D 19
	extern char *index();
E 19
I 19
	extern char *arpadate();
D 28
	extern char *hvalue();
E 28
	bool anyheader = FALSE;
D 25
	extern char *translate();
E 25
I 25
D 36
	extern char *expand();
E 36
E 25
I 22
	extern char *capitalize();
I 56
	extern char *hvalue();
	extern bool samefrom();
I 63
	char *of_line;
E 89
E 63
E 56
E 22
E 19
E 15
I 13
	extern char SentDate[];
E 13

I 25
D 54
	/* output "From" line unless supressed */
E 54
I 54
D 100
	/*
	**  Output "From" line unless supressed
I 77
	**
	**  >>>>>>>>>>	One of the ugliest hacks seen by human eyes is
	**  >>>>>>>>>>	contained herein: UUCP wants those stupid
D 81
	**  >> NOTE >>	"remote from <host>" lines.  Why oh why does a
	**  >>>>>>>>>>	well-meaning programmer such as myself have to
E 81
I 81
D 91
	**  >>>>>>>>>>	"remote from <host>" lines.  Why oh why does a
	**  >> NOTE >>	well-meaning programmer such as myself have to
E 91
I 91
	**  >> NOTE >>	"remote from <host>" lines.  Why oh why does a
	**  >>>>>>>>>>	well-meaning programmer such as myself have to
E 91
E 81
	**  >>>>>>>>>>	deal with this kind of antique garbage????
I 81
D 91
	**  >>>>>>>>>>  This even depends on the local UUCP host name
	**  >>>>>>>>>>  being in the $U macro!!!!
E 91
E 81
E 77
	*/
E 100
I 100
D 168
	if (bitset(M_NHDR, m->m_flags))
E 168
I 168
D 405
	if (bitnset(M_NHDR, m->m_flags))
E 405
I 405
	if (bitnset(M_NHDR, mci->mci_mailer->m_flags))
E 405
E 168
		return;
E 100

E 54
D 100
	if (!bitset(M_NHDR, m->m_flags))
D 46
		fprintf(fp, "%s\n", FromLine);
E 46
I 46
	{
E 100
D 77
		(void) expand("$l", buf, &buf[sizeof buf - 1]);
E 77
I 77
D 78
		if (strcmp(m->m_name, "uucp") == 0)
E 78
I 78
D 79
		register char *p = rindex(m->m_mailer, '/');
E 79
I 79
D 504
# ifdef UGLYUUCP
E 504
D 84
		char *p = rindex(m->m_mailer, '/');
E 79

E 84
D 82
		if (p != NULL && strcmp(p, "/uux") == 0 &&
		    strcmp(m->m_name, "uucp") == 0)
E 82
I 82
D 100
		if (bitset(M_UGLYUUCP, m->m_flags))
E 82
E 78
D 81
			(void) expand("From $f  $d remote from $h", buf,
E 81
I 81
D 91
			(void) expand("From $f  $d remote from $U", buf,
E 91
I 91
		{
			extern char *macvalue();
			char *sys = macvalue('g');
			char *bang = index(sys, '!');
E 100
I 100
D 168
	if (bitset(M_UGLYUUCP, m->m_flags))
E 168
I 168
D 405
	if (bitnset(M_UGLYUUCP, m->m_flags))
E 405
I 405
	if (bitnset(M_UGLYUUCP, mci->mci_mailer->m_flags))
E 405
E 168
	{
D 173
		extern char *macvalue();
D 134
		char *sys = macvalue('g');
E 134
I 134
		char *sys = macvalue('g', CurEnv);
E 134
		char *bang = index(sys, '!');
E 173
I 173
		char *bang;
		char xbuf[MAXLINE];
E 173
E 100

I 173
D 181
		expand("$g", buf, &buf[sizeof buf - 1], CurEnv);
E 181
I 181
D 239
		expand("\001g", buf, &buf[sizeof buf - 1], CurEnv);
E 239
I 239
D 247
		expand("\001<", buf, &buf[sizeof buf - 1], CurEnv);
E 247
I 247
D 274
		expand("\001<", buf, &buf[sizeof buf - 1], e);
E 274
I 274
D 301
		expand("\201<", buf, &buf[sizeof buf - 1], e);
E 301
I 301
D 475
		expand("\201g", buf, &buf[sizeof buf - 1], e);
E 475
I 475
		expand("\201g", buf, sizeof buf, e);
E 475
E 301
E 274
E 247
E 239
E 181
D 256
		bang = index(buf, '!');
E 256
I 256
		bang = strchr(buf, '!');
E 256
E 173
D 100
			if (bang == NULL)
				syserr("No ! in UUCP! (%s)", sys);
			else
				*bang = '\0';
			(void) expand("From $f  $d remote from $g", buf,
E 91
E 81
					&buf[sizeof buf - 1]);
I 91
			*bang = '!';
		}
E 100
I 100
		if (bang == NULL)
D 173
			syserr("No ! in UUCP! (%s)", sys);
E 173
I 173
D 280
			syserr("No ! in UUCP! (%s)", buf);
E 280
I 280
D 357
			syserr("554 No ! in UUCP! (%s)", buf);
E 357
I 357
		{
			errno = 0;
			syserr("554 No ! in UUCP From address! (%s given)", buf);
		}
E 357
E 280
E 173
E 100
E 91
		else
I 154
		{
E 154
I 79
D 100
# endif UGLYUUCP
E 79
			(void) expand("$l", buf, &buf[sizeof buf - 1]);
E 77
		fprintf(fp, "%s\n", buf);
E 100
I 100
D 173
			*bang = '\0';
D 110
		expand("From $f  $d remote from $g", buf,
E 110
I 110
D 154
		expand("From $f  $d remote from $g\n", buf,
E 110
				&buf[sizeof buf - 1], CurEnv);
		*bang = '!';
E 154
I 154
			expand("From $f  $d remote from $g\n", buf,
					&buf[sizeof buf - 1], CurEnv);
			*bang = '!';
E 173
I 173
			*bang++ = '\0';
D 174
			(void) sprintf(xbuf, "From %s  $d remote from %s\n", buf, bang);
E 174
I 174
D 181
			(void) sprintf(xbuf, "From %s  $d remote from %s\n", bang, buf);
E 181
I 181
D 274
			(void) sprintf(xbuf, "From %s  \001d remote from %s\n", bang, buf);
E 274
I 274
			(void) sprintf(xbuf, "From %s  \201d remote from %s\n", bang, buf);
E 274
E 181
E 174
			template = xbuf;
E 173
		}
E 154
E 100
	}
E 46
D 100

E 25
D 13
D 15
	time(&tim);
	fprintf(fp, "From %s %s", From.q_paddr, ctime(&tim));
E 13
I 13
	fprintf(fp, "From %s ", From.q_paddr);
	if (SentDate[0] == '\0')
	{
		time(&tim);
		fprintf(fp, "%s", ctime(&tim));
	}
	else
		fprintf(fp, "%s", SentDate);
E 13
	while (fgets(buf, sizeof buf, stdin) != NULL && !ferror(fp))
E 15
I 15
D 19
	/* output the header part */
	fgets(buf, sizeof buf, stdin);
	if (strncmp(buf, "From ", 5) != 0 || (p = index(&buf[5], ' ')) == NULL)
E 19
I 19
D 28
	/* clear all "used" bits */
E 28
I 28
D 54
	/* output all header lines */
E 54
I 54
	/*
	**  Output all header lines
	*/

I 89
	putheader(fp, m);

	/*
	**  Output the body of the message
	*/

	if (TempFile != NULL)
	{
		rewind(TempFile);
		while (!ferror(fp) && fgets(buf, sizeof buf, TempFile) != NULL)
			fprintf(fp, "%s%s", xdot && buf[0] == '.' ? "." : "", buf);

		if (ferror(TempFile))
		{
			syserr("putmessage: read error");
D 92
			setstat(EX_IOERR);
E 92
I 92
			ExitStat = EX_IOERR;
E 92
		}
	}

	(void) fflush(fp);
	if (ferror(fp) && errno != EPIPE)
	{
		syserr("putmessage: write error");
D 92
		setstat(EX_IOERR);
E 92
I 92
		ExitStat = EX_IOERR;
E 92
	}
	errno = 0;
E 100
I 100
D 173
	else
E 173
D 256
# endif UGLYUUCP
E 256
I 256
D 504
# endif /* UGLYUUCP */
E 504
E 256
D 173
		expand("$l\n", buf, &buf[sizeof buf - 1], CurEnv);
E 173
I 173
D 247
	expand(template, buf, &buf[sizeof buf - 1], CurEnv);
E 247
I 247
D 475
	expand(template, buf, &buf[sizeof buf - 1], e);
E 475
I 475
	expand(template, buf, sizeof buf, e);
E 475
E 247
E 173
D 107
	fputs(buf, fp);
E 107
I 107
D 159
	putline(buf, fp, bitset(M_FULLSMTP, m->m_flags));
E 159
I 159
D 166
	putline(buf, fp, crlf, bitset(M_FULLSMTP, m->m_flags));
E 166
I 166
D 405
	putline(buf, fp, m);
E 405
I 405
D 472
	putline(buf, mci);
E 472
I 472
D 491
	putxline(buf, mci, FALSE);
E 491
I 491
	putxline(buf, mci, PXLF_NOTHINGSPECIAL);
E 491
E 472
E 405
E 166
E 159
E 107
E 100
}
/*
D 100
**  PUTHEADER -- put the header part of a message
E 100
I 100
D 154
**  PUTHEADER -- put the header part of a message from the in-core copy
E 100
**
**	Parameters:
**		fp -- file to put it on.
**		m -- mailer to use.
I 100
**		e -- envelope to use.
E 100
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

D 100
putheader(fp, m)
E 100
I 100
putheader(fp, m, e)
E 100
	register FILE *fp;
	register struct mailer *m;
I 100
	register ENVELOPE *e;
E 100
{
	char buf[BUFSIZ];
	register HDR *h;
	extern char *arpadate();
D 100
	bool anyheader = FALSE;
E 100
	extern char *capitalize();
D 134
	extern char *hvalue();
E 134
D 153
	extern bool samefrom();
E 153
D 128
	char *of_line;
E 128
I 107
	char obuf[MAXLINE];
D 153
	register char *obp;
E 153
	bool fullsmtp = bitset(M_FULLSMTP, m->m_flags);
E 107

I 142
	if (bitset(M_LOCAL, m->m_flags) && fullsmtp)
		fprintf(fp, "Return-Path: <%s>\n", e->e_from);
E 142
E 89
I 63
D 128
	of_line = hvalue("original-from");
E 128
E 63
E 54
E 28
D 99
	for (h = Header; h != NULL; h = h->h_link)
E 99
I 99
D 100
	for (h = CurEnv->e_header; h != NULL; h = h->h_link)
E 100
I 100
	for (h = e->e_header; h != NULL; h = h->h_link)
E 100
E 99
D 28
		h->h_flags &= ~H_USED;

	/* output date if needed by mailer */
	p = hvalue("date");
D 20
	if (flagset(M_NEEDDATE, m->m_flags) && p == NULL)
E 20
I 20
	if (bitset(M_NEEDDATE, m->m_flags) && p == NULL)
E 20
		p = arpadate(Date);
	if (p != NULL)
E 28
E 19
	{
I 54
		register char *p;
I 56
D 99
		char *origfrom = OrigFrom;
E 99
I 99
D 100
		char *origfrom = CurEnv->e_origfrom;
E 100
I 100
D 128
		char *origfrom = e->e_origfrom;
E 100
E 99
I 63
		bool nooutput;
E 128
E 63
E 56

I 63
D 128
		nooutput = FALSE;
E 128
E 63
E 54
D 19
		time(&tim);
		fprintf(fp, "From %s %s", From.q_paddr, ctime(&tim));
		fputs(buf, fp);
E 19
I 19
D 28
		fprintf(fp, "Date: %s\n", p);
		anyheader = TRUE;
E 19
	}
D 19
	else
		fprintf(fp, "From %s %s", From.q_paddr, &p[1]);
E 19

D 19
	/* output the body */
	while (!ferror(fp) && fgets(buf, sizeof buf, stdin) != NULL)
E 15
		fputs(buf, fp);
E 19
I 19
	/* output from line if needed by mailer */
	p = hvalue("from");
D 20
	if (flagset(M_NEEDFROM, m->m_flags) && p == NULL)
E 20
I 20
	if (bitset(M_NEEDFROM, m->m_flags) && p == NULL)
E 20
	{
D 22
		char frombuf[MAXLINE];
E 22
		extern char *FullName;

D 22
		p = translate("$f", From.q_mailer, From.q_paddr, NULL, NULL);
E 22
I 22
D 23
		p = translate("$f", From.q_mailer, From.q_paddr, (char *) NULL, (char *) NULL);
E 23
I 23
D 24
		p = translate("$f", Mailer[From.q_mailer], From.q_paddr, (char *) NULL, (char *) NULL);
E 24
I 24
D 25
		p = translate("$g", Mailer[From.q_mailer], From.q_paddr, (char *) NULL, (char *) NULL);
E 25
I 25
		expand("$g", buf, &buf[sizeof buf - 1]);
E 25
E 24
E 23
E 22
		if (FullName != NULL)
D 25
			fprintf(fp, "From: %s <%s>\n", FullName, p);
E 25
I 25
			fprintf(fp, "From: %s <%s>\n", FullName, buf);
E 25
		else
D 25
			fprintf(fp, "From: %s\n", p);
		free(p);
E 25
I 25
			fprintf(fp, "From: %s\n", buf);
E 25
		anyheader = TRUE;
	}
	else if (p != NULL)
	{
		fprintf(fp, "From: %s\n", p);
		anyheader = TRUE;
	}

	/* output message-id field if needed */
	p = hvalue("message-id");
D 20
	if (flagset(M_MSGID, m->m_flags) && p == NULL)
E 20
I 20
	if (bitset(M_MSGID, m->m_flags) && p == NULL)
E 20
		p = MsgId;
	if (p != NULL)
	{
		fprintf(fp, "Message-Id: %s\n", p);
		anyheader = TRUE;
	}

	/* output any other header lines */
	for (h = Header; h != NULL; h = h->h_link)
	{
D 20
		if (flagset(H_USED, h->h_flags))
E 20
I 20
		if (bitset(H_USED, h->h_flags))
E 28
I 28
D 29
		if (bitset(H_CHECK, h->h_flags) && bitset(H_DEFAULT, h->h_flags) &&
		    !bitset(h->h_mflags, m->m_flags))
E 29
I 29
D 50
		if (bitset(H_DELETE, h->h_flags))
E 29
E 28
E 20
			continue;
E 50
I 29
		if (bitset(H_CHECK|H_ACHECK, h->h_flags) && !bitset(h->h_mflags, m->m_flags))
D 47
			continue;
E 47
I 47
D 86
		{
			p = ")><(";		/* can't happen (I hope) */
E 86
D 63
			goto checkfrom;
E 63
I 63
D 128
			nooutput = TRUE;
E 128
I 128
			continue;
E 128
E 63
D 86
		}
E 86
I 63

D 128
		/* use From: line from message if generated is the same */
E 128
I 119
		p = h->h_value;
E 119
E 63
E 47
E 29
D 28
		fprintf(fp, "%s: %s\n", capitalize(h->h_field), h->h_value);
E 28
I 28
D 56
		if (bitset(H_DEFAULT, h->h_flags))
E 56
I 56
D 128
		if (strcmp(h->h_field, "from") == 0 && origfrom != NULL &&
D 63
		    strcmp(m->m_from, "$f") == 0)
E 63
I 63
		    strcmp(m->m_from, "$f") == 0 && of_line == NULL)
E 128
I 128
		if (bitset(H_DEFAULT, h->h_flags))
E 128
E 63
E 56
		{
I 56
D 128
			p = origfrom;
			origfrom = NULL;
		}
		else if (bitset(H_DEFAULT, h->h_flags))
		{
E 128
I 116
			/* macro expand value if generated internally */
E 116
E 56
D 36
			expand(h->h_value, buf, &buf[sizeof buf]);
E 36
I 36
D 100
			(void) expand(h->h_value, buf, &buf[sizeof buf]);
E 100
I 100
D 128
			expand(h->h_value, buf, &buf[sizeof buf], e);
E 128
I 128
			expand(p, buf, &buf[sizeof buf], e);
E 128
E 100
E 36
			p = buf;
		}
I 86
D 128
		else if (bitset(H_ADDR, h->h_flags))
		{
D 119
			register int opos;
			bool firstone = TRUE;

			/*
			**  Output the address list translated by the
			**  mailer and with commas.
			*/

			p = h->h_value;
E 119
			if (p == NULL || *p == '\0' || nooutput)
				continue;
D 107
			fprintf(fp, "%s: ", capitalize(h->h_field));
E 107
I 107
D 119
			obp = obuf;
D 112
			sprintf(obp, "%s: ", capitalize(h->h_field));
E 112
I 112
			(void) sprintf(obp, "%s: ", capitalize(h->h_field));
E 112
E 107
			opos = strlen(h->h_field) + 2;
I 107
			obp += opos;
I 116

			/*
			**  Run through the list of values.
			*/

E 116
E 107
			while (*p != '\0')
			{
D 116
				register char *name = p;
E 116
I 116
				register char *name;
E 116
				extern char *remotename();
				char savechar;

D 116
				/* find the end of the name */
E 116
I 116
				/*
				**  Find the end of the name.  New style names
				**  end with a comma, old style names end with
				**  a space character.  However, spaces do not
				**  necessarily delimit an old-style name -- at
				**  signs mean keep going.
				*/

				/* clean up the leading trash in source */
				while (*p != '\0' && (isspace(*p) || *p == ','))
					p++;
				name = p;

				/* find end of name */
E 116
D 88
				while (*p != '\0' && *p != ',' &&
				       (OldStyle ? (!isspace(*p)) : TRUE))
					p++;
E 88
I 88
				while (*p != '\0' && *p != ',')
				{
					extern bool isatword();
					char *oldp;

D 99
					if (!OldStyle || !isspace(*p))
E 99
I 99
D 100
					if (!CurEnv->e_oldstyle || !isspace(*p))
E 100
I 100
					if (!e->e_oldstyle || !isspace(*p))
E 100
E 99
					{
						p++;
						continue;
					}
I 116

					/* look to see if we have an at sign */
E 116
					oldp = p;
					while (*p != '\0' && isspace(*p))
						p++;
I 116

E 116
					if (*p != '@' && !isatword(p))
					{
						p = oldp;
						break;
					}
					p += *p == '@' ? 1 : 2;
					while (*p != '\0' && isspace(*p))
						p++;
				}
I 116
				/* at the end of one complete name */

				/* strip off trailing white space */
				while (p >= name && (isspace(*p) || *p == ','))
					p--;
				if (++p == name)
					continue;
E 116
E 88
				savechar = *p;
				*p = '\0';

				/* translate the name to be relative */
D 87
				name = remotename(name);
E 87
I 87
D 97
				name = remotename(name, m);
E 97
I 97
				name = remotename(name, m, FALSE);
E 97
E 87
				if (*name == '\0')
I 116
				{
					*p = savechar;
E 116
					continue;
I 116
				}
E 116

				/* output the name with nice formatting */
				opos += strlen(name);
				if (!firstone)
					opos += 2;
				if (opos > 78 && !firstone)
				{
D 107
					fprintf(fp, ",\n        ");
E 107
I 107
					(void) sprintf(obp, ",\n");
					putline(obuf, fp, fullsmtp);
					obp = obuf;
					(void) sprintf(obp, "        ");
					obp += strlen(obp);
E 107
D 87
					opos = 8;
E 87
I 87
					opos = 8 + strlen(name);
E 87
				}
				else if (!firstone)
D 107
					fprintf(fp, ", ");
				fprintf(fp, "%s", name);
E 107
I 107
				{
					(void) sprintf(obp, ", ");
					obp += 2;
				}
				(void) sprintf(obp, "%s", name);
				obp += strlen(obp);
E 107
				firstone = FALSE;
D 116

				/* clean up the source string */
E 116
				*p = savechar;
D 116
				while (*p != '\0' && (isspace(*p) || *p == ','))
					p++;
E 116
			}
D 107
			fprintf(fp, "\n");
E 107
I 107
D 112
			strcpy(obp, "\n");
E 112
I 112
			(void) strcpy(obp, "\n");
E 112
D 108
			putline(obp, fp, fullsmtp);
E 108
I 108
			putline(obuf, fp, fullsmtp);
E 119
I 119
			commaize(p, capitalize(h->h_field), fp, e->e_oldstyle, m);
E 119
E 108
E 107
			nooutput = TRUE;
		}
E 128
E 86
D 119
		else
			p = h->h_value;
E 119
I 29
D 63
		if (*p == '\0')
E 63
I 63
		if (p == NULL || *p == '\0')
E 63
			continue;
E 29
D 63
		fprintf(fp, "%s: %s\n", capitalize(h->h_field), p);
E 28
		h->h_flags |= H_USED;
		anyheader = TRUE;
E 63
I 47

D 128
		/* hack, hack -- output Original-From field if different */
D 63
	checkfrom:
D 56
		if (strcmp(h->h_field, "from") == 0)
E 56
I 56
		if (strcmp(h->h_field, "from") == 0 && origfrom != NULL &&
		    !samefrom(p, origfrom) && hvalue("original-from") == NULL)
E 63
I 63
		if (strcmp(h->h_field, "from") == 0 && origfrom != NULL)
E 128
I 128
		if (bitset(H_FROM|H_RCPT, h->h_flags))
E 128
E 63
E 56
		{
D 56
			extern char *hvalue();
			char *ofrom = hvalue("original-from");

			if (ofrom != NULL && strcmp(p, ofrom) != 0)
				fprintf(fp, "Original-From: %s\n", ofrom);
E 56
I 56
D 63
			fprintf(fp, "Original-From: %s\n", origfrom);
E 63
I 63
D 128
			/* output new Original-From line if needed */
			if (of_line == NULL && !samefrom(p, origfrom))
D 100
			{
E 100
D 107
				fprintf(fp, "Original-From: %s\n", origfrom);
E 107
I 107
			{
				(void) sprintf(obuf, "Original-From: %s\n", origfrom);
				putline(obuf, fp, fullsmtp);
			}
E 107
D 100
				anyheader = TRUE;
			}
E 100
			if (of_line != NULL && !nooutput && samefrom(p, of_line))
			{
				/* delete Original-From: line if redundant */
				p = of_line;
				of_line = NULL;
			}
E 128
I 128
			/* address field */
D 131
			commaize(h, p, fp, e->e_oldstyle, m);
E 131
I 131
D 152
			bool oldstyle = e->e_oldstyle;
E 152
I 152
			bool oldstyle = bitset(EF_OLDSTYLE, e->e_flags);
E 152

			if (bitset(H_FROM, h->h_flags))
				oldstyle = FALSE;
			commaize(h, p, fp, oldstyle, m);
E 131
E 128
		}
D 128
		else if (strcmp(h->h_field, "original-from") == 0 && of_line == NULL)
			nooutput = TRUE;

		/* finally, output the header line */
		if (!nooutput)
E 128
I 128
		else
E 128
		{
I 128
			/* vanilla header line */
E 128
D 107
			fprintf(fp, "%s: %s\n", capitalize(h->h_field), p);
E 107
I 107
			(void) sprintf(obuf, "%s: %s\n", capitalize(h->h_field), p);
			putline(obuf, fp, fullsmtp);
E 107
D 128
			h->h_flags |= H_USED;
E 128
E 63
D 100
			anyheader = TRUE;
E 100
E 56
		}
I 128
		h->h_flags |= H_USED;
E 128
E 47
	}
I 119
}
/*
**  COMMAIZE -- output a header field, making a comma-translated list.
**
**	Parameters:
D 128
**		p -- the field to output.
**		tag -- the tag to associate with it.
E 128
I 128
**		h -- the header field to output.
**		p -- the value to put in it.
E 128
**		fp -- file to put it to.
**		oldstyle -- TRUE if this is an old style header.
D 136
**		m -- a pointer to the mailer descriptor.
E 136
I 136
**		m -- a pointer to the mailer descriptor.  If NULL,
**			don't transform the name at all.
E 136
**
**	Returns:
**		none.
**
**	Side Effects:
**		outputs "p" to file "fp".
*/

D 128
commaize(p, tag, fp, oldstyle, m)
E 128
I 128
commaize(h, p, fp, oldstyle, m)
	register HDR *h;
E 128
	register char *p;
D 128
	char *tag;
E 128
	FILE *fp;
	bool oldstyle;
D 128
	MAILER *m;
E 128
I 128
	register MAILER *m;
E 128
{
D 128
	register int opos;
	bool firstone = TRUE;
	char obuf[MAXLINE];
E 128
	register char *obp;
I 128
	int opos;
E 128
D 136
	bool fullsmtp = bitset(M_FULLSMTP, m->m_flags);
E 136
I 136
	bool fullsmtp = FALSE;
E 136
I 128
	bool firstone = TRUE;
	char obuf[MAXLINE];
E 128

	/*
	**  Output the address list translated by the
	**  mailer and with commas.
	*/

# ifdef DEBUG
	if (tTd(14, 2))
D 128
		printf("commaize(%s: %s)\n", tag, p);
E 128
I 128
		printf("commaize(%s: %s)\n", h->h_field, p);
E 128
# endif DEBUG

I 136
	if (m != NULL && bitset(M_FULLSMTP, m->m_flags))
		fullsmtp = TRUE;

E 136
	obp = obuf;
D 128
	(void) sprintf(obp, "%s: ", tag);
	opos = strlen(tag) + 2;
E 128
I 128
	(void) sprintf(obp, "%s: ", capitalize(h->h_field));
	opos = strlen(h->h_field) + 2;
E 128
	obp += opos;

	/*
	**  Run through the list of values.
	*/

	while (*p != '\0')
	{
		register char *name;
D 128
		extern char *remotename();
E 128
		char savechar;
I 126
D 129
		int commentlevel;
		bool inquote;
E 129
I 128
		extern char *remotename();
I 129
		extern char *DelimChar;		/* defined in prescan */
E 129
E 128
E 126

		/*
		**  Find the end of the name.  New style names
		**  end with a comma, old style names end with
		**  a space character.  However, spaces do not
		**  necessarily delimit an old-style name -- at
		**  signs mean keep going.
		*/

D 129
		/* clean up the leading trash in source */
		while (*p != '\0' && (isspace(*p) || *p == ','))
E 129
I 129
		/* find end of name */
		while (isspace(*p) || *p == ',')
E 129
			p++;
		name = p;
D 129

		/* find end of name */
D 126
		while (*p != '\0' && *p != ',')
E 126
I 126
		commentlevel = 0;
		inquote = FALSE;
		while (*p != '\0' && (*p != ',' || commentlevel > 0 || inquote))
E 129
I 129
		for (;;)
E 129
E 126
		{
D 129
			extern bool isatword();
E 129
			char *oldp;
I 129
			extern bool isatword();
E 129

I 126
D 129
			if (*p == '(')
				commentlevel++;
			else if (*p == ')' && commentlevel > 0)
				commentlevel--;
			else if (*p == '"')
				inquote = !inquote;
E 126
			if (!oldstyle || !isspace(*p))
			{
				p++;
				continue;
			}
E 129
I 129
D 130
			(void) prescan(name, oldstyle ? ' ' : ',');
E 130
I 130
			(void) prescan(p, oldstyle ? ' ' : ',');
E 130
			p = DelimChar;
E 129

			/* look to see if we have an at sign */
			oldp = p;
			while (*p != '\0' && isspace(*p))
				p++;

			if (*p != '@' && !isatword(p))
			{
				p = oldp;
				break;
			}
			p += *p == '@' ? 1 : 2;
			while (*p != '\0' && isspace(*p))
				p++;
		}
		/* at the end of one complete name */

		/* strip off trailing white space */
		while (p >= name && (isspace(*p) || *p == ',' || *p == '\0'))
			p--;
		if (++p == name)
			continue;
		savechar = *p;
		*p = '\0';

		/* translate the name to be relative */
D 128
		name = remotename(name, m, FALSE);
E 128
I 128
D 136
		name = remotename(name, m, bitset(H_FROM, h->h_flags));
E 136
I 136
		if (m != NULL)
			name = remotename(name, m, bitset(H_FROM, h->h_flags));
E 136
E 128
		if (*name == '\0')
		{
			*p = savechar;
			continue;
		}

		/* output the name with nice formatting */
D 146
		opos += strlen(name);
E 146
I 146
		opos += qstrlen(name);
E 146
		if (!firstone)
			opos += 2;
		if (opos > 78 && !firstone)
		{
			(void) sprintf(obp, ",\n");
			putline(obuf, fp, fullsmtp);
			obp = obuf;
			(void) sprintf(obp, "        ");
			obp += strlen(obp);
			opos = 8 + strlen(name);
		}
		else if (!firstone)
		{
			(void) sprintf(obp, ", ");
			obp += 2;
		}
D 146
		(void) sprintf(obp, "%s", name);
		obp += strlen(obp);
E 146
I 146

		/* strip off quote bits as we output */
		while (*name != '\0')
		{
			if (bitset(0200, *name))
				*obp++ = '\\';
			*obp++ = *name++ & ~0200;
		}
E 146
		firstone = FALSE;
		*p = savechar;
	}
	(void) strcpy(obp, "\n");
	putline(obuf, fp, fullsmtp);
E 119
D 54

E 54
D 100
	if (anyheader)
		fprintf(fp, "\n");
E 100
D 89

D 54
	/* output the body of the message */
E 54
I 54
	/*
	**  Output the body of the message
	*/

E 54
D 32
	while (!ferror(fp) && (i = read(0, buf, BUFSIZ)) > 0)
E 32
I 32
D 44
	rewind(stdin);
	while (!ferror(fp) && (i = fread(buf, 1, BUFSIZ, stdin)) > 0)
E 44
I 44
D 64
	rewind(TempFile);
	while (!ferror(fp) && (i = fread(buf, 1, BUFSIZ, TempFile)) > 0)
E 44
E 32
D 36
		fwrite(buf, 1, i, fp);
E 36
I 36
		(void) fwrite(buf, 1, i, fp);
E 64
I 64
	if (TempFile != NULL)
	{
		rewind(TempFile);
D 72
		while (!ferror(fp) && (i = fread(buf, 1, BUFSIZ, TempFile)) > 0)
			(void) fwrite(buf, 1, i, fp);
E 72
I 72
		while (!ferror(fp) && fgets(buf, sizeof buf, TempFile) != NULL)
			fprintf(fp, "%s%s", xdot && buf[0] == '.' ? "." : "", buf);
E 72
E 64
E 36

I 64
		if (ferror(TempFile))
		{
			syserr("putmessage: read error");
			setstat(EX_IOERR);
		}
	}

D 69
	fflush(fp);
E 69
I 69
	(void) fflush(fp);
E 69
E 64
E 19
D 39
	if (ferror(fp))
E 39
I 39
	if (ferror(fp) && errno != EPIPE)
E 39
	{
D 19
		syserr("putheader: write error");
E 19
I 19
		syserr("putmessage: write error");
E 19
		setstat(EX_IOERR);
	}
D 39
}
/*
**  PIPESIG -- Handle broken pipe signals
**
**	This just logs an error.
**
**	Parameters:
**		none
**
**	Returns:
**		none
**
**	Side Effects:
**		logs an error message.
D 4
**
**	Requires:
**		syserr
**
**	History:
**		1/17/80 -- written.
E 4
*/

pipesig()
{
	syserr("Broken pipe");
I 10
D 36
	signal(SIGPIPE, SIG_IGN);
E 36
I 36
	(void) signal(SIGPIPE, SIG_IGN);
E 39
I 39
	errno = 0;
E 89
I 88
}
/*
E 154
I 100
**  PUTBODY -- put the body of a message.
**
**	Parameters:
D 405
**		fp -- file to output onto.
D 166
**		m -- a mailer descriptor.
**		xdot -- if set, use SMTP hidden dot algorithm.
E 166
I 166
**		m -- a mailer descriptor to control output format.
E 405
I 405
**		mci -- the connection information.
E 405
E 166
I 157
**		e -- the envelope to put out.
I 329
**		separator -- if non-NULL, a message separator that must
**			not be permitted in the resulting message.
I 450
D 462
**		flags -- to modify the behaviour.
E 462
E 450
E 329
E 157
**
**	Returns:
**		none.
**
**	Side Effects:
**		The message is written onto fp.
*/

I 432
/* values for output state variable */
#define OS_HEAD		0	/* at beginning of line */
#define OS_CR		1	/* read a carriage return */
#define OS_INLINE	2	/* putting rest of line */

I 500
void
E 500
E 432
D 157
putbody(fp, m, xdot)
E 157
I 157
D 159
putbody(fp, m, xdot, e)
E 159
I 159
D 166
putbody(fp, m, xdot, e, crlf)
E 166
I 166
D 329
putbody(fp, m, e)
E 329
I 329
D 405
putbody(fp, m, e, separator)
E 329
E 166
E 159
E 157
	FILE *fp;
D 154
	struct mailer *m;
E 154
I 154
	MAILER *m;
E 405
I 405
D 450
putbody(mci, e, separator)
E 450
I 450
D 462
putbody(mci, e, separator, flags)
E 462
I 462
putbody(mci, e, separator)
E 462
E 450
	register MCI *mci;
E 405
E 154
D 166
	bool xdot;
E 166
I 157
	register ENVELOPE *e;
I 329
	char *separator;
I 450
D 462
	int flags;
E 462
E 450
E 329
E 157
{
D 166
	char buf[MAXLINE + 1];
I 107
	bool fullsmtp = bitset(M_FULLSMTP, m->m_flags);
E 166
I 166
	char buf[MAXLINE];
E 166
E 107

	/*
	**  Output the body of the message
	*/

I 448
D 477
	if (e->e_dfp == NULL && e->e_df != NULL)
E 477
I 477
	if (e->e_dfp == NULL && bitset(EF_HAS_DF, e->e_flags))
E 477
	{
D 477
		e->e_dfp = fopen(e->e_df, "r");
E 477
I 477
		char *df = queuename(e, 'd');

		e->e_dfp = fopen(df, "r");
E 477
		if (e->e_dfp == NULL)
			syserr("putbody: Cannot open %s for %s from %s",
D 477
			e->e_df, e->e_to, e->e_from.q_paddr);
E 477
I 477
				df, e->e_to, e->e_from.q_paddr);
E 477
	}
E 448
I 102
D 154
#ifdef lint
	/* m will be needed later for complete smtp emulation */
	if (m == NULL)
		return;
#endif lint

E 154
E 102
D 157
	if (TempFile != NULL)
E 157
I 157
	if (e->e_dfp == NULL)
E 157
	{
D 157
		rewind(TempFile);
E 157
I 157
D 448
		if (e->e_df != NULL)
E 448
I 448
		if (bitset(MCIF_INHEADER, mci->mci_flags))
E 448
		{
D 448
			e->e_dfp = fopen(e->e_df, "r");
			if (e->e_dfp == NULL)
D 216
				syserr("Cannot open %s", e->e_df);
E 216
I 216
				syserr("putbody: Cannot open %s for %s from %s",
D 350
				e->e_df, e->e_to, e->e_from);
E 350
I 350
				e->e_df, e->e_to, e->e_from.q_paddr);
E 448
I 448
			putline("", mci);
			mci->mci_flags &= ~MCIF_INHEADER;
E 448
E 350
E 216
		}
D 448
		else
I 430
		{
			if (bitset(MCIF_INHEADER, mci->mci_flags))
			{
				putline("", mci);
				mci->mci_flags &= ~MCIF_INHEADER;
			}
E 430
D 159
			putline("<<< No Message Collected >>>", fp, fullsmtp);
E 159
I 159
D 166
			putline("<<< No Message Collected >>>", fp, crlf, fullsmtp);
E 166
I 166
D 405
			putline("<<< No Message Collected >>>", fp, m);
E 405
I 405
			putline("<<< No Message Collected >>>", mci);
I 432
			goto endofmessage;
E 432
I 430
		}
E 448
I 448
		putline("<<< No Message Collected >>>", mci);
		goto endofmessage;
E 448
I 435
	}
D 448
	if (e->e_dfp != NULL && e->e_dfino == (ino_t) 0)
E 448
I 448
	if (e->e_dfino == (ino_t) 0)
E 448
	{
		struct stat stbuf;

		if (fstat(fileno(e->e_dfp), &stbuf) < 0)
			e->e_dfino = -1;
		else
I 438
		{
			e->e_dfdev = stbuf.st_dev;
E 438
			e->e_dfino = stbuf.st_ino;
I 438
		}
E 438
E 435
E 430
E 405
E 166
E 159
	}
D 432
	if (e->e_dfp != NULL)
E 432
I 432
	rewind(e->e_dfp);

I 497
#if MIME8TO7
E 497
	if (bitset(MCIF_CVT8TO7, mci->mci_flags))
E 432
	{
I 473
		char *boundaries[MAXMIMENESTING + 1];

E 473
D 432
		rewind(e->e_dfp);
E 432
I 432
D 438
		/* do 8 to 7 bit MIME conversion */
E 438
I 438
		/*
		**  Do 8 to 7 bit MIME conversion.
		*/

		/* make sure it looks like a MIME message */
E 438
		if (hvalue("MIME-Version", e->e_header) == NULL)
			putline("MIME-Version: 1.0", mci);
I 438

D 442
		/* as recommended by RFC 1428 section 3... */
E 442
		if (hvalue("Content-Type", e->e_header) == NULL)
D 442
			putline("Content-Type: text/plain; charset=unknown-8bit", mci);
E 442
I 442
		{
D 447
			char *charset = DefaultCharSet;

			/* as recommended by RFC 1428 section 3... */
			if (charset == NULL)
				charset = "unknown-8bit";
E 447
			sprintf(buf, "Content-Type: text/plain; charset=%s",
D 447
				charset);
E 447
I 447
				defcharset(e));
E 447
			putline(buf, mci);
		}
E 442

		/* now do the hard work */
E 438
D 473
		mime8to7(mci, e->e_header, e, NULL);
E 473
I 473
		boundaries[0] = NULL;
		mime8to7(mci, e->e_header, e, boundaries, M87F_OUTER);
E 473
	}
	else
I 497
#endif
E 497
	{
		int ostate;
		register char *bp;
		register char *pbp;
		register int c;
		int padc;
		char *buflim;
D 467
		int pos;
E 467
I 467
		int pos = 0;
E 467
		char peekbuf[10];
E 432
E 157
D 166
		buf[0] = '.';
D 157
		while (!ferror(fp) && fgets(&buf[1], sizeof buf - 1, TempFile) != NULL)
E 157
I 157
		while (!ferror(fp) &&
		       fgets(&buf[1], sizeof buf - 1, e->e_dfp) != NULL)
		{
E 157
D 107
			fputs((xdot && buf[1] == '.') ? buf : &buf[1], fp);
E 107
I 107
D 159
			putline((xdot && buf[1] == '.') ? buf : &buf[1], fp, fullsmtp);
E 159
I 159
			putline((xdot && buf[1] == '.') ? buf : &buf[1], fp, crlf, fullsmtp);
E 159
I 157
		}
E 166
I 166
D 405
		while (!ferror(fp) && fgets(buf, sizeof buf, e->e_dfp) != NULL)
E 405
I 405
D 430
		while (!ferror(mci->mci_out) && fgets(buf, sizeof buf, e->e_dfp) != NULL)
E 430
I 430

D 432
		if (bitset(MCIF_CVT8TO7, mci->mci_flags))
E 432
I 432
		/* we can pass it through unmodified */
		if (bitset(MCIF_INHEADER, mci->mci_flags))
E 432
E 430
E 405
I 182
		{
D 405
			if (buf[0] == 'F' && bitnset(M_ESCFROM, m->m_flags) &&
E 405
I 405
D 430
			if (buf[0] == 'F' &&
			    bitnset(M_ESCFROM, mci->mci_mailer->m_flags) &&
E 405
D 221
			    strncmp(buf, "From", 4) == 0)
E 221
I 221
			    strncmp(buf, "From ", 5) == 0)
E 221
D 188
				putc('>', fp);
E 188
I 188
D 405
				(void) putc('>', fp);
E 405
I 405
				(void) putc('>', mci->mci_out);
E 405
I 329
			if (buf[0] == '-' && buf[1] == '-' && separator != NULL)
E 430
I 430
D 432
			/* do 8 to 7 bit MIME conversion */
			if (hvalue("MIME-Version", e->e_header) == NULL)
				putline("MIME-Version: 1.0", mci);
			mime8to7(mci, e->e_header, e, NULL);
E 432
I 432
			putline("", mci);
			mci->mci_flags &= ~MCIF_INHEADER;
E 432
		}
D 432
		else
E 432
I 432

		/* determine end of buffer; allow for short mailer lines */
		buflim = &buf[sizeof buf - 1];
D 437
		if (mci->mci_mailer->m_linelimit < sizeof buf - 1)
E 437
I 437
		if (mci->mci_mailer->m_linelimit > 0 &&
		    mci->mci_mailer->m_linelimit < sizeof buf - 1)
E 437
			buflim = &buf[mci->mci_mailer->m_linelimit - 1];

		/* copy temp file to output with mapping */
		ostate = OS_HEAD;
		bp = buf;
		pbp = peekbuf;
		while (!ferror(mci->mci_out))
E 432
		{
D 432
			/* we can pass it through unmodified */
			if (bitset(MCIF_INHEADER, mci->mci_flags))
E 432
I 432
			register char *xp;

			if (pbp > peekbuf)
				c = *--pbp;
D 494
			else if ((c = fgetc(e->e_dfp)) == EOF)
E 494
I 494
			else if ((c = getc(e->e_dfp)) == EOF)
E 494
				break;
			if (bitset(MCIF_7BIT, mci->mci_flags))
				c &= 0x7f;
			switch (ostate)
E 432
E 430
			{
D 430
				/* possible separator */
				int sl = strlen(separator);
E 430
I 430
D 432
				putline("", mci);
				mci->mci_flags &= ~MCIF_INHEADER;
			}
			while (!ferror(mci->mci_out) &&
			       fgets(buf, sizeof buf, e->e_dfp) != NULL)
			{
E 432
I 432
			  case OS_HEAD:
				if (c != '\r' && c != '\n' && bp < buflim)
				{
					*bp++ = c;
					break;
				}

				/* check beginning of line for special cases */
				*bp = '\0';
				pos = 0;
				padc = EOF;
E 432
				if (buf[0] == 'F' &&
				    bitnset(M_ESCFROM, mci->mci_mailer->m_flags) &&
				    strncmp(buf, "From ", 5) == 0)
D 432
					(void) putc('>', mci->mci_out);
E 432
I 432
				{
					padc = '>';
				}
E 432
				if (buf[0] == '-' && buf[1] == '-' &&
				    separator != NULL)
				{
					/* possible separator */
					int sl = strlen(separator);
E 430

D 430
				if (strncmp(&buf[2], separator, sl) == 0)
D 405
					(void) putc(' ', fp);
E 405
I 405
					(void) putc(' ', mci->mci_out);
E 430
I 430
					if (strncmp(&buf[2], separator, sl) == 0)
D 432
						(void) putc(' ', mci->mci_out);
E 432
I 432
						padc = ' ';
E 432
				}
D 432
				putline(buf, mci);
E 432
I 432
				if (buf[0] == '.' &&
				    bitnset(M_XDOT, mci->mci_mailer->m_flags))
				{
					padc = '.';
				}

				/* now copy out saved line */
				if (TrafficLogFile != NULL)
				{
					fprintf(TrafficLogFile, "%05d >>> ", getpid());
					if (padc != EOF)
D 494
						fputc(padc, TrafficLogFile);
E 494
I 494
						putc(padc, TrafficLogFile);
E 494
					for (xp = buf; xp < bp; xp++)
D 494
						fputc(*xp, TrafficLogFile);
E 494
I 494
						putc(*xp, TrafficLogFile);
E 494
					if (c == '\n')
						fputs(mci->mci_mailer->m_eol,
						      TrafficLogFile);
				}
				if (padc != EOF)
				{
D 494
					fputc(padc, mci->mci_out);
E 494
I 494
					putc(padc, mci->mci_out);
E 494
					pos++;
				}
				for (xp = buf; xp < bp; xp++)
D 494
					fputc(*xp, mci->mci_out);
E 494
I 494
					putc(*xp, mci->mci_out);
E 494
				if (c == '\n')
				{
					fputs(mci->mci_mailer->m_eol,
					      mci->mci_out);
					pos = 0;
				}
				else
				{
					pos += bp - buf;
D 440
					*pbp++ = c;
E 440
I 440
					if (c != '\r')
						*pbp++ = c;
E 440
				}
				bp = buf;

				/* determine next state */
				if (c == '\n')
					ostate = OS_HEAD;
				else if (c == '\r')
					ostate = OS_CR;
				else
					ostate = OS_INLINE;
				continue;

			  case OS_CR:
				if (c == '\n')
				{
					/* got CRLF */
					fputs(mci->mci_mailer->m_eol, mci->mci_out);
					if (TrafficLogFile != NULL)
					{
						fputs(mci->mci_mailer->m_eol,
						      TrafficLogFile);
					}
					ostate = OS_HEAD;
					continue;
				}

				/* had a naked carriage return */
				*pbp++ = c;
				c = '\r';
D 436
				goto putchar;
E 436
I 436
				goto putch;
E 436

			  case OS_INLINE:
				if (c == '\r')
				{
					ostate = OS_CR;
					continue;
				}
D 436
putchar:
E 436
I 436
putch:
E 436
D 437
				if (pos > mci->mci_mailer->m_linelimit &&
E 437
I 437
				if (mci->mci_mailer->m_linelimit > 0 &&
				    pos > mci->mci_mailer->m_linelimit &&
E 437
				    c != '\n')
				{
					putc('!', mci->mci_out);
					fputs(mci->mci_mailer->m_eol, mci->mci_out);
					if (TrafficLogFile != NULL)
					{
						fprintf(TrafficLogFile, "!%s",
							mci->mci_mailer->m_eol);
					}
					ostate = OS_HEAD;
					*pbp++ = c;
					continue;
				}
				if (TrafficLogFile != NULL)
D 494
					fputc(c, TrafficLogFile);
E 494
I 494
					putc(c, TrafficLogFile);
E 494
				putc(c, mci->mci_out);
				pos++;
D 440
				if (c == '\n')
					ostate = OS_HEAD;
E 440
I 440
				ostate = c == '\n' ? OS_HEAD : OS_INLINE;
E 440
				break;
E 432
E 430
E 405
			}
E 329
E 188
E 182
D 405
			putline(buf, fp, m);
E 405
I 405
D 430
			putline(buf, mci);
E 430
E 405
I 182
		}
I 432
	}
E 432
E 182
E 166
E 157
E 107

D 157
		if (ferror(TempFile))
E 157
I 157
D 432
		if (ferror(e->e_dfp))
E 157
		{
D 371
			syserr("putbody: read error");
E 371
I 371
			syserr("putbody: %s: read error", e->e_df);
E 371
			ExitStat = EX_IOERR;
		}
E 432
I 432
	if (ferror(e->e_dfp))
	{
D 477
		syserr("putbody: %s: read error", e->e_df);
E 477
I 477
		syserr("putbody: df%s: read error", e->e_id);
E 477
		ExitStat = EX_IOERR;
E 432
	}

I 432
endofmessage:
E 432
I 328
	/* some mailers want extra blank line at end of message */
D 405
	if (bitnset(M_BLANKEND, m->m_flags) && buf[0] != '\0' && buf[0] != '\n')
		putline("", fp, m);
E 405
I 405
	if (bitnset(M_BLANKEND, mci->mci_mailer->m_flags) &&
	    buf[0] != '\0' && buf[0] != '\n')
		putline("", mci);
E 405

E 328
D 405
	(void) fflush(fp);
	if (ferror(fp) && errno != EPIPE)
E 405
I 405
	(void) fflush(mci->mci_out);
	if (ferror(mci->mci_out) && errno != EPIPE)
E 405
	{
		syserr("putbody: write error");
		ExitStat = EX_IOERR;
	}
	errno = 0;
}
/*
I 282
D 301
**  PARENTBODY -- put the body of the parent of a message.
**
**	Parameters:
**		fp -- file to output onto.
**		m -- a mailer descriptor to control output format.
**		e -- the envelope whose parent to put out.
**
**	Returns:
**		none.
**
**	Side Effects:
**		The message is written onto fp.
*/

parentbody(fp, m, e)
	FILE *fp;
	MAILER *m;
	register ENVELOPE *e;
{
	putbody(fp, m, e->e_parent);
}
/*
E 301
E 282
E 100
D 154
**  ISATWORD -- tell if the word we are pointing to is "at".
**
**	Parameters:
**		p -- word to check.
**
**	Returns:
**		TRUE -- if p is the word at.
**		FALSE -- otherwise.
**
**	Side Effects:
**		none.
*/

bool
isatword(p)
	register char *p;
{
	extern char lower();

	if (lower(p[0]) == 'a' && lower(p[1]) == 't' &&
	    p[2] != '\0' && isspace(p[2]))
		return (TRUE);
	return (FALSE);
E 88
I 86
D 118
}
/*
**  REMOTENAME -- return the name relative to the current mailer
**
**	Parameters:
**		name -- the name to translate.
I 97
**		force -- if set, forces rewriting even if the mailer
**			does not request it.  Used for rewriting
**			sender addresses.
E 97
**
**	Returns:
**		the text string representing this address relative to
**			the receiving mailer.
**
**	Side Effects:
**		none.
**
**	Warnings:
**		The text string returned is tucked away locally;
**			copy it if you intend to save it.
*/

char *
D 87
remotename(name)
E 87
I 87
D 97
remotename(name, m)
E 97
I 97
remotename(name, m, force)
E 97
E 87
	char *name;
I 87
	struct mailer *m;
I 97
	bool force;
E 97
E 87
{
I 95
D 97
# ifdef NOTDEF
E 97
E 95
	static char buf[MAXNAME];
	char lbuf[MAXNAME];
	extern char *macvalue();
	char *oldf = macvalue('f');
I 87
	char *oldx = macvalue('x');
	char *oldg = macvalue('g');
E 87
	extern char **prescan();
	register char **pvp;
I 87
	extern char *getxpart();
I 102
	extern ADDRESS *buildaddr();
E 102
E 87

	/*
I 97
	**  See if this mailer wants the name to be rewritten.  There are
	**  many problems here, owing to the standards for doing replies.
	**  In general, these names should only be rewritten if we are
	**  sending to another host that runs sendmail.
	*/

	if (!bitset(M_RELRCPT, m->m_flags) && !force)
D 102
		return;
E 102
I 102
		return (name);
E 102

	/*
E 97
	**  Do general rewriting of name.
	**	This will also take care of doing global name translation.
	*/

I 87
	define('x', getxpart(name));
E 87
	pvp = prescan(name, '\0');
I 111
	if (pvp == NULL)
		return (name);
E 111
D 105
	for (;;)
E 105
I 105
	rewrite(pvp, 1);
	rewrite(pvp, 3);
	if (**pvp == CANONNET)
E 105
	{
D 105
		rewrite(pvp, 1);
		rewrite(pvp, 3);
		if (**pvp == CANONNET)
		{
			auto ADDRESS a;
			register char *p;
			extern char *hostalias();

			/* oops... resolved to something */
			if (buildaddr(pvp, &a) == NULL)
				return (name);
			p = hostalias(&a);
			if (p == NULL)
				return (name);
			pvp = prescan(p, '\0');
		}
		else
		{
			cataddr(pvp, lbuf, sizeof lbuf);
			break;
		}
E 105
I 105
		/* oops... resolved to something */
		return (name);
E 105
	}
I 105
	cataddr(pvp, lbuf, sizeof lbuf);
E 105

	/* make the name relative to the receiving mailer */
	define('f', lbuf);
D 87
	(void) expand(From.q_mailer->m_from, buf, &buf[sizeof buf - 1]);
E 87
I 87
D 100
	(void) expand(m->m_from, buf, &buf[sizeof buf - 1]);
E 100
I 100
	expand(m->m_from, buf, &buf[sizeof buf - 1], CurEnv);
E 100
E 87

	/* rewrite to get rid of garbage we added in the expand above */
	pvp = prescan(buf, '\0');
I 111
	if (pvp == NULL)
		return (name);
E 111
	rewrite(pvp, 2);
D 87
	cataddr(pvp, buf, sizeof buf);
E 87
I 87
	cataddr(pvp, lbuf, sizeof lbuf);
E 87

I 87
	/* now add any comment info we had before back */
	define('g', lbuf);
D 100
	(void) expand("$q", buf, &buf[sizeof buf - 1]);
E 100
I 100
	expand("$q", buf, &buf[sizeof buf - 1], CurEnv);
E 100

E 87
	define('f', oldf);
I 87
	define('g', oldg);
	define('x', oldx);
E 87

# ifdef DEBUG
D 117
	if (Debug > 0)
E 117
I 117
	if (tTd(12, 1))
E 117
		printf("remotename(%s) => `%s'\n", name, buf);
# endif DEBUG
	return (buf);
E 118
I 95
D 97
# else NOTDEF
	/* oh bother, this breaks UUCP......   */
	return (name);
# endif NOTDEF
E 97
E 95
E 86
I 56
}
/*
E 154
D 153
**  SAMEFROM -- tell if two text addresses represent the same from address.
**
**	Parameters:
**		ifrom -- internally generated form of from address.
**		efrom -- external form of from address.
**
**	Returns:
**		TRUE -- if they convey the same info.
**		FALSE -- if any information has been lost.
**
**	Side Effects:
**		none.
*/

bool
samefrom(ifrom, efrom)
	char *ifrom;
	char *efrom;
{
D 63
	return (strcmp(ifrom, efrom) == 0);
E 63
I 63
	register char *p;
	char buf[MAXNAME + 4];

# ifdef DEBUG
D 117
	if (Debug > 7)
E 117
I 117
	if (tTd(3, 8))
E 117
		printf("samefrom(%s,%s)-->", ifrom, efrom);
# endif DEBUG
	if (strcmp(ifrom, efrom) == 0)
		goto success;
	p = index(ifrom, '@');
	if (p == NULL)
		goto failure;
	*p = '\0';
D 102
	strcpy(buf, ifrom);
	strcat(buf, " at ");
E 102
I 102
	(void) strcpy(buf, ifrom);
	(void) strcat(buf, " at ");
E 102
	*p++ = '@';
D 102
	strcat(buf, p);
E 102
I 102
	(void) strcat(buf, p);
E 102
	if (strcmp(buf, efrom) == 0)
		goto success;

  failure:
# ifdef DEBUG
D 117
	if (Debug > 7)
E 117
I 117
	if (tTd(3, 8))
E 117
		printf("FALSE\n");
# endif DEBUG
	return (FALSE);

  success:
# ifdef DEBUG
D 117
	if (Debug > 7)
E 117
I 117
	if (tTd(3, 8))
E 117
		printf("TRUE\n");
# endif DEBUG
	return (TRUE);
E 63
E 56
E 39
E 36
E 10
}
/*
E 153
D 43
**  SENDTO -- Designate a send list.
**
**	The parameter is a comma-separated list of people to send to.
**	This routine arranges to send to all of them.
**
**	Parameters:
**		list -- the send list.
**		copyf -- the copy flag; passed to parse.
**
**	Returns:
**		none
**
**	Side Effects:
**		none.
D 26
**
D 4
**	Requires:
**		parse
**		recipient
**
E 4
**	Called By:
**		main
**		alias
E 26
D 4
**
**	History:
**		1/11/80 -- written.
E 4
*/

I 37
# define MAXRCRSN	10

E 37
sendto(list, copyf)
	char *list;
	int copyf;
{
	register char *p;
	register char *q;
	register char c;
D 20
	addrq *a;
	extern addrq *parse();
E 20
I 20
	ADDRESS *a;
D 36
	extern ADDRESS *parse();
E 36
E 20
	bool more;

	/* more keeps track of what the previous delimiter was */
	more = TRUE;
	for (p = list; more; )
	{
		/* find the end of this address */
I 40
		while (*p == ' ' || *p == '\t')
			p++;
E 40
		q = p;
		while ((c = *p++) != '\0' && c != ',' && c != '\n')
			continue;
		more = c != '\0';
		*--p = '\0';
		if (more)
			p++;

		/* parse the address */
D 20
		if ((a = parse(q, (addrq *) NULL, copyf)) == NULL)
E 20
I 20
		if ((a = parse(q, (ADDRESS *) NULL, copyf)) == NULL)
E 20
			continue;

		/* arrange to send to this person */
D 25
		recipient(a, &SendQ);
E 25
I 25
		recipient(a);
E 25
	}
	To = NULL;
}
/*
**  RECIPIENT -- Designate a message recipient
**
**	Saves the named person for future mailing.
**
D 25
**	Designates a person as a recipient.  This routine
**	does the initial parsing, and checks to see if
**	this person has already received the mail.
**	It also supresses local network names and turns them into
**	local names.
**
E 25
**	Parameters:
**		a -- the (preparsed) address header for the recipient.
D 25
**		targetq -- the queue to add the name to.
E 25
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
D 26
**
D 4
**	Requires:
**		sameaddr
**		parse
**		forward
**		printf (sys)
**		strcmp (sys)
**		nxtinq
**		putonq
**
E 4
**	Called By:
**		sendto
**		main
E 26
D 4
**
**	History:
**		3/5/80 -- modified to know about new internal form
**			for addresses.
**		12/31/79 -- written.
E 4
*/

D 25
recipient(a, targetq)
E 25
I 25
recipient(a)
E 25
D 20
	register addrq *a;
	addrq *targetq;
E 20
I 20
	register ADDRESS *a;
D 25
	ADDRESS *targetq;
E 25
E 20
{
D 20
	register addrq *q;
E 20
I 20
	register ADDRESS *q;
E 20
	register struct mailer *m;
D 22
	register char **pvp;
E 22
D 20
	extern char *xalloc();
E 20
D 37
	extern bool forward();
E 37
I 37
	char buf[MAXNAME];
E 37
D 36
	extern int errno;
	extern bool sameaddr();
E 36

	To = a->q_paddr;
D 23
	m = a->q_mailer;
E 23
I 23
	m = Mailer[a->q_mailer];
E 23
	errno = 0;
# ifdef DEBUG
	if (Debug)
		printf("recipient(%s)\n", To);
# endif DEBUG
D 7

	/*
	**  Don't go to the net if already on the target host.
	**	This is important on the berkeley network, since
	**	it get confused if we ask to send to ourselves.
	**	For nets like the ARPANET, we probably will have
	**	the local list set to NULL to simplify testing.
	**	The canonical representation of the name is also set
	**	to be just the local name so the duplicate letter
	**	suppression algorithm will work.
	*/

	if ((pvp = m->m_local) != NULL)
	{
		while (*pvp != NULL)
		{
			if (strcmp(*pvp++, a->q_host) == 0)
			{
				a->q_mailer = m = &Mailer[0];
				break;
			}
		}
	}
E 7

I 37
	/* break aliasing loops */
	if (AliasLevel > MAXRCRSN)
	{
		usrerr("aliasing/forwarding loop broken");
		return;
	}

E 37
	/*
I 25
	**  Do sickly crude mapping for program mailing, etc.
	*/

D 35
	if (a->q_mailer == 0 && a->q_user[0] == '|')
E 35
I 35
	if (a->q_mailer == M_LOCAL)
E 35
	{
D 35
		a->q_mailer = 1;
D 30
		m++;
E 30
I 30
		m = Mailer[1];
E 30
		a->q_user++;
E 35
I 35
		if (a->q_user[0] == '|')
		{
			a->q_mailer = M_PROG;
			m = Mailer[M_PROG];
			a->q_user++;
		}
D 37
		else
		{
			register struct passwd *pw;

			pw = getpwnam(a->q_user);
			if (pw == NULL)
				a->q_flags |= QBADADDR;
			else
			{
				char xbuf[60];

				a->q_home = newstr(pw->pw_dir);
				define('z', a->q_home);
D 36
				expand("$z/.mailer", xbuf, &xbuf[sizeof xbuf - 1]);
E 36
I 36
				(void) expand("$z/.mailer", xbuf, &xbuf[sizeof xbuf - 1]);
E 36
				if (access(xbuf, 1) == 0)
				{
					a->q_mailer = M_PRIVATE;
					m = Mailer[M_PROG];
				}
			}
		}
E 37
E 35
	}

	/*
E 25
	**  Look up this person in the recipient list.  If they
	**  are there already, return, otherwise continue.
I 25
	**  If the list is empty, just add it.
E 25
	*/

D 25
	if (!ForceMail)
E 25
I 25
	if (m->m_sendq == NULL)
E 25
	{
D 25
		for (q = &SendQ; (q = nxtinq(q)) != NULL; )
			if (sameaddr(q, a, FALSE))
E 25
I 25
		m->m_sendq = a;
	}
	else
	{
		ADDRESS *pq;

		for (q = m->m_sendq; q != NULL; pq = q, q = q->q_next)
		{
			if (!ForceMail && sameaddr(q, a, FALSE))
E 25
			{
# ifdef DEBUG
				if (Debug)
D 25
					printf("(%s in SendQ)\n", a->q_paddr);
E 25
I 25
					printf("(%s in sendq)\n", a->q_paddr);
E 25
# endif DEBUG
I 33
D 34
				if (Verbose)
E 34
I 34
				if (Verbose && !bitset(QDONTSEND, a->q_flags))
E 34
D 42
					message("050", "duplicate supressed");
E 42
I 42
					message(Arpa_Info, "duplicate supressed");
E 42
E 33
				return;
			}
D 25
		for (q = &AliasQ; (q = nxtinq(q)) != NULL; )
			if (sameaddr(q, a, FALSE))
			{
# ifdef DEBUG
				if (Debug)
					printf("(%s in AliasQ)\n", a->q_paddr);
# endif DEBUG
				return;
			}
E 25
I 25
		}

		/* add address on list */
		q = pq;
D 26
		q->q_next = NULL;
E 26
I 26
		q->q_next = a;
E 26
E 25
	}
I 25
	a->q_next = NULL;
E 25

	/*
D 37
	**  See if the user wants hir mail forwarded.
	**	`Forward' must do the forwarding recursively.
E 37
I 37
D 40
	**  Alias the name.
E 40
I 40
	**  Alias the name and handle :include: specs.
E 40
E 37
	*/

D 23
	if (m == &Mailer[0] && !NoAlias && targetq == &SendQ && forward(a))
E 23
I 23
D 25
	if (m == Mailer[0] && !NoAlias && targetq == &SendQ && forward(a))
E 23
		return;
E 25
I 25
D 35
	if (m == Mailer[0] && !NoAlias && forward(a))
E 35
I 35
D 37
	if (m == Mailer[M_LOCAL] && !NoAlias && forward(a))
E 35
D 34
		setbit(QDONTSEND, a->q_flags);
E 34
I 34
		a->q_flags |= QDONTSEND;
E 37
I 37
	if (a->q_mailer == M_LOCAL)
D 40
		alias(a);
E 40
I 40
	{
		if (strncmp(a->q_user, ":include:", 9) == 0)
		{
			a->q_flags |= QDONTSEND;
			include(&a->q_user[9]);
		}
		else
			alias(a);
	}
E 40

	/*
	**  If the user is local and still being sent, verify that
	**  the address is good.  If it is, try to forward.
	**  If the address is already good, we have a forwarding
	**  loop.  This can be broken by just sending directly to
	**  the user (which is probably correct anyway).
	*/

D 41
	if (!bitset(QDONTSEND, a->q_flags) && a->q_mailer == M_LOCAL &&
	    a->q_home == NULL)
E 41
I 41
	if (!bitset(QDONTSEND, a->q_flags) && a->q_mailer == M_LOCAL)
E 41
	{
D 41
		register struct passwd *pw;
		extern struct passwd *getpwnam();
E 41
		char buf[MAXNAME];

		strcpy(buf, a->q_user);
		stripquotes(buf, TRUE);
D 41
		pw = getpwnam(buf);
		if (pw == NULL)
			a->q_flags |= QBADADDR;
E 41
I 41

		/* see if this is to a file */
		if (index(buf, '/') != NULL)
		{
			if (access(buf, 2) < 0)
			{
				a->q_flags |= QBADADDR;
				giveresponse(EX_CANTCREAT, TRUE, m);
			}
		}
E 41
		else
I 38
		{
E 38
D 41
			a->q_home = newstr(pw->pw_dir);
D 38
		if (strcmp(buf, a->q_user) == 0)
			forward(a);
E 38
I 38
			if (strcmp(buf, a->q_user) == 0)
				forward(a);
E 41
I 41
			register struct passwd *pw;
			extern struct passwd *getpwnam();
			pw = getpwnam(buf);
			if (pw == NULL)
			{
				a->q_flags |= QBADADDR;
				giveresponse(EX_NOUSER, TRUE, m);
			}
			else
			{
				a->q_home = newstr(pw->pw_dir);
				if (strcmp(buf, a->q_user) == 0)
					forward(a);
			}
E 41
		}
E 38
	}
I 40
}
/*
**  INCLUDE -- handle :include: specification.
**
**	Parameters:
**		fname -- filename to include.
**
**	Returns:
**		none.
**
**	Side Effects:
**		reads the :include: file and sends to everyone
**		listed in that file.
*/
E 40
E 37
E 34
E 25

D 25
	/*
	**  Put the user onto the target queue.
	*/

	if (targetq != NULL)
	{
		putonq(a, targetq);
	}

E 25
D 40
	return;
E 40
I 40
include(fname)
	char *fname;
{
	char buf[MAXLINE];
	register FILE *fp;

	if (Verbose)
D 42
		message("050", "Including file %s", fname);
E 42
I 42
		message(Arpa_Info, "Including file %s", fname);
E 42
	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		usrerr("Cannot open %s", fname);
		return;
	}

	/* read the file -- each line is a comma-separated list. */
	while (fgets(buf, sizeof buf, fp) != NULL)
	{
		register char *p = index(buf, '\n');

		if (p != NULL)
			*p = '\0';
		if (buf[0] == '\0')
			continue;
		To = fname;
		if (Verbose)
D 42
			message("050", " >> %s", buf);
E 42
I 42
			message(Arpa_Info, " >> %s", buf);
E 42
		sendto(buf, 1);
	}

	fclose(fp);
E 40
D 26
}
/*
**  BUILDARGV -- Build an argument vector for a mail server.
**
**	Using a template defined in config.c, an argv is built.
**	The format of the template is already a vector.  The
**	items of this vector are copied, unless a dollar sign
**	is encountered.  In this case, the next character
**	specifies something else to copy in.  These can be
I 25
**	any macros.  System defined macros are:
E 25
**		$f	The from address.
**		$h	The host.
**		$u	The user.
**		$c	The hop count.
I 25
**	among others.
E 25
**	The vector is built in a local buffer.  A pointer to
**	the static argv is returned.
**
**	Parameters:
D 19
**		tmplt -- a template for an argument vector.
**		flags -- the flags for this server.
E 19
I 19
**		m -- a pointer to the mailer descriptor.
E 19
**		host -- the host name to send to.
**		user -- the user name to send to.
**		from -- the person this mail is from.
**
**	Returns:
**		A pointer to an argv.
**
**	Side Effects:
**		none
**
**	WARNING:
**		Since the argv is staticly allocated, any subsequent
**		calls will clobber the old argv.
**
D 4
**	Requires:
**		printf (sys)
**		sprintf (sys)
**		flagset
**		syserr
**
E 4
**	Called By:
**		deliver
D 4
**
**	History:
**		12/26/79 -- written.
E 4
*/

char **
D 19
buildargv(tmplt, flags, host, user, from)
	char **tmplt;
	int flags;
E 19
I 19
buildargv(m, host, user, from)
	struct mailer *m;
E 19
	char *host;
	char *user;
	char *from;
{
	register char *p;
D 22
	register char *q;
E 22
	static char *pv[MAXPV+1];
	char **pvp;
	char **mvp;
	static char buf[512];
D 22
	register char *bp;
E 22
D 19
	char pbuf[30];
E 19
I 19
D 25
	extern char *translate();
E 25
I 25
	extern char *expand();
	extern char *newstr();
E 25
E 19

	/*
	**  Do initial argv setup.
	**	Insert the mailer name.  Notice that $x expansion is
	**	NOT done on the mailer name.  Then, if the mailer has
	**	a picky -f flag, we insert it as appropriate.  This
	**	code does not check for 'pv' overflow; this places a
	**	manifest lower limit of 4 for MAXPV.
	*/

	pvp = pv;
D 22
	bp = buf;

E 22
D 19
	*pvp++ = tmplt[0];
E 19
I 19
	*pvp++ = m->m_argv[0];
E 19

	/* insert -f or -r flag as appropriate */
D 19
	if (flagset(M_FOPT|M_ROPT, flags) && FromFlag)
E 19
I 19
D 20
	if (flagset(M_FOPT|M_ROPT, m->m_flags) && FromFlag)
E 20
I 20
	if (bitset(M_FOPT|M_ROPT, m->m_flags) && FromFlag)
E 20
E 19
	{
D 19
		if (flagset(M_FOPT, flags))
E 19
I 19
D 20
		if (flagset(M_FOPT, m->m_flags))
E 20
I 20
		if (bitset(M_FOPT, m->m_flags))
E 20
E 19
			*pvp++ = "-f";
		else
			*pvp++ = "-r";
D 19
		*pvp++ = From.q_paddr;
E 19
I 19
D 25
		*pvp++ = translate(from, m, from, user, host);
E 25
I 25
		expand(from, buf, &buf[sizeof buf - 1]);
		*pvp++ = newstr(buf);
E 25
E 19
	}

	/*
	**  Build the rest of argv.
	**	For each prototype parameter, the prototype is
D 25
	**	scanned character at a time.  If a dollar-sign is
	**	found, 'q' is set to the appropriate expansion,
	**	otherwise it is null.  Then either the string
	**	pointed to by q, or the original character, is
	**	interpolated into the buffer.  Buffer overflow is
E 25
I 25
	**	scanned character at a time.  Buffer overflow is
E 25
	**	checked.
	*/

D 19
	for (mvp = tmplt; (p = *++mvp) != NULL; )
E 19
I 19
	for (mvp = m->m_argv; (p = *++mvp) != NULL; )
E 19
	{
		if (pvp >= &pv[MAXPV])
		{
			syserr("Too many parameters to %s", pv[0]);
			return (NULL);
		}
D 19
		*pvp++ = bp;
		for (; *p != '\0'; p++)
E 19
I 19
D 25
		*pvp++ = translate(p, m, from, user, host);
E 25
I 25
		expand(p, buf, &buf[sizeof buf - 1]);
		*pvp++ = newstr(buf);
E 25
	}
	*pvp = NULL;

# ifdef DEBUG
	if (Debug)
	{
		printf("Interpolated argv is:\n");
		for (mvp = pv; *mvp != NULL; mvp++)
			printf("\t%s\n", *mvp);
	}
# endif DEBUG

	return (pv);
E 26
}
/*
E 43
D 25
**  TRANSLATE -- translate a string using $x escapes.
**
**	Parameters:
**		s -- string to translate.
**		m -- pointer to mailer descriptor.
**
**	Returns:
**		pointer to translated string.
**
**	Side Effects:
**		none.
*/

char *
translate(s, m, from, user, host)
	register char *s;
	struct mailer *m;
	char *from;
	char *user;
	char *host;
{
D 24
	register char *q;
E 24
	char buf[MAXNAME];
D 24
	register char *bp;
	char *stack = NULL;
E 24
	char pbuf[10];
	extern char *newstr();
	extern char *Macro[];
I 22
	extern char *sprintf();
I 24
	extern char *trans2();
E 24
E 22

D 24
	bp = buf;
restart:
E 24
I 24
	/* predefine system macros */
	Macro['f'] = From.q_paddr;
	Macro['g'] = m->m_from;
	Macro['u'] = user;
	Macro['h'] = host;
	sprintf(pbuf, "%d", HopCount);
	Macro['c'] = pbuf;
E 24

I 24
	trans2(s, buf, &buf[sizeof buf - 1]);

E 24
# ifdef DEBUG
	if (Debug)
I 24
		printf("translate ==> '%s'\n", buf);
# endif DEBUG

	return (newstr(buf));
}

/*
**  TRANS2 -- internal routine to translate.
*/

char *
trans2(s, bp, buflim)
	register char *s;
	register char *bp;
	char *buflim;
{
	register char *q;
	extern char *Macro[];

# ifdef DEBUG
	if (Debug)
E 24
		printf("translate(%s)\n", s);
# endif DEBUG
I 24

E 24
	for (; *s != '\0'; s++)
	{
		/* q will be the interpolated quantity */
		q = NULL;
		if (*s == '$')
E 19
D 24
		{
D 19
			/* q will be the interpolated quantity */
			q = NULL;
			if (*p == '$')
E 19
I 19
			if (isupper(*++s))
				q = Macro[*s - 'A'];
			else
E 19
			{
D 19
				switch (*++p)
E 19
I 19
				switch (*s)
E 19
				{
				  case 'f':	/* from person */
I 19
					if (stack == NULL && m != NULL)
					{
						stack = s;
						s = m->m_from;
						goto restart;
					}
E 19
					q = from;
					break;
E 24
I 24
			q = Macro[*++s];
E 24

D 24
				  case 'u':	/* user */
					q = user;
					break;

				  case 'h':	/* host */
					q = host;
					break;

				  case 'c':	/* hop count */
					sprintf(pbuf, "%d", HopCount);
					q = pbuf;
					break;
				}
			}
I 19
		}
E 19

E 24
D 19
			/*
			**  Interpolate q or output one character
			**	Strip quote bits as we proceed.....
			*/
E 19
I 19
		/*
		**  Interpolate q or output one character
		**	Strip quote bits as we proceed.....
		*/
E 19

D 19
			if (q != NULL)
			{
				while (bp < &buf[sizeof buf - 1] && (*bp++ = *q++) != '\0')
					continue;
				bp--;
D 2
				if (q[-2] == '"')
					bp--;
E 2
			}
			else if (bp < &buf[sizeof buf - 1])
				*bp++ = *p;
E 19
I 19
		if (q != NULL)
D 24
		{
			while (bp < &buf[sizeof buf - 1] && (*bp++ = *q++) != '\0')
				continue;
			bp--;
E 19
		}
D 19
		*bp++ = '\0';
		if (bp >= &buf[sizeof buf - 1])
			return (NULL);
E 19
I 19
		else if (bp < &buf[sizeof buf - 1])
E 24
I 24
			bp = trans2(q, bp, buflim);
		else if (bp < buflim - 1)
E 24
			*bp++ = *s;
E 19
	}
D 19
	*pvp = NULL;

# ifdef DEBUG
	if (Debug)
E 19
I 19
D 24
	if (stack != NULL)
E 19
	{
D 19
		printf("Interpolated argv is:\n");
		for (mvp = pv; *mvp != NULL; mvp++)
			printf("\t%s\n", *mvp);
E 19
I 19
		s = stack;
		s++;
		stack = NULL;
		goto restart;
E 19
	}
I 19
	*bp++ = '\0';
	if (bp >= &buf[sizeof buf - 1])
		return (NULL);
# ifdef DEBUG
	if (Debug)
		printf("translate ==> '%s'\n", buf);
E 19
# endif DEBUG
D 19

	return (pv);
E 19
I 19
	return (newstr(buf));
E 24
I 24
	*bp = '\0';
	return (bp);
E 24
E 19
}
/*
E 25
**  MAILFILE -- Send a message to a file.
**
I 55
**	If the file has the setuid/setgid bits set, but NO execute
**	bits, sendmail will try to become the owner of that file
**	rather than the real user.  Obviously, this only works if
**	sendmail runs as root.
**
I 154
**	This could be done as a subordinate mailer, except that it
**	is used implicitly to save messages in ~/dead.letter.  We
**	view this as being sufficiently important as to include it
**	here.  For example, if the system is dying, we shouldn't have
**	to create another process plus some pipes to save the message.
**
E 154
E 55
**	Parameters:
**		filename -- the name of the file to send to.
I 58
**		ctladdr -- the controlling address header -- includes
**			the userid/groupid to be when sending.
I 501
**		sfflags -- flags for opening.
**		e -- the current envelope.
E 501
E 58
**
**	Returns:
**		The exit code associated with the operation.
**
**	Side Effects:
**		none.
D 48
**
D 4
**	Requires:
**		fgets (sys)
**		fputs (sys)
**		fprintf (sys)
**		fopen (sys)
**		fclose (sys)
**		ferror (sys)
**		time (sys)
**		ctime (sys)
**		rewind (sys)
**
E 4
**	Called By:
**		deliver
E 48
D 4
**
**	History:
**		3/5/80 -- written.
E 4
*/

I 500
int
E 500
D 58
mailfile(filename)
E 58
I 58
D 247
mailfile(filename, ctladdr)
E 247
I 247
D 501
mailfile(filename, ctladdr, e)
E 501
I 501
mailfile(filename, ctladdr, sfflags, e)
E 501
E 247
E 58
	char *filename;
I 58
	ADDRESS *ctladdr;
I 501
	int sfflags;
E 501
I 247
	register ENVELOPE *e;
E 247
E 58
{
D 25
	char buf[MAXLINE];
E 25
	register FILE *f;
I 48
D 467
	register int pid;
E 467
I 467
	register int pid = -1;
E 467
I 216
D 247
	ENVELOPE *e = CurEnv;
E 247
I 244
	int mode;
E 244
E 216
D 54
	register int i;
E 54
E 48
D 25
	auto long tim;
	extern char *ctime();
I 22
	extern long time();
E 25
E 22

I 323
	if (tTd(11, 1))
	{
		printf("mailfile %s\n  ctladdr=", filename);
		printaddr(ctladdr, FALSE);
	}

I 342
	if (e->e_xfp != NULL)
		fflush(e->e_xfp);

E 342
E 323
D 48
	f = fopen(filename, "a");
	if (f == NULL)
		return (EX_CANTCREAT);
E 48
I 48
	/*
	**  Fork so we can change permissions here.
	**	Note that we MUST use fork, not vfork, because of
	**	the complications of calling subroutines, etc.
	*/
E 48
D 34
	
E 34
I 34

E 34
D 25
	/* output the timestamp */
	time(&tim);
	fprintf(f, "From %s %s", From.q_paddr, ctime(&tim));
	rewind(stdin);
	while (fgets(buf, sizeof buf, stdin) != NULL)
	{
		fputs(buf, f);
		if (ferror(f))
		{
			fclose(f);
			return (EX_IOERR);
		}
	}
E 25
I 25
D 48
	putmessage(f, Mailer[1]);
E 25
	fputs("\n", f);
D 36
	fclose(f);
E 36
I 36
	(void) fclose(f);
E 36
	return (EX_OK);
E 48
I 48
	DOFORK(fork);

	if (pid < 0)
		return (EX_OSERR);
	else if (pid == 0)
	{
		/* child -- actually write to file */
D 55
		(void) setuid(getuid());
		(void) setgid(getgid());
E 55
I 55
		struct stat stb;
I 468
		struct stat fsb;
E 468
I 405
		MCI mcibuf;
I 471
		int oflags = O_WRONLY|O_APPEND;
E 471
I 470
		int oflags = O_WRONLY|O_APPEND;
E 470
E 405
I 61
D 83
		extern int DefUid, DefGid;
E 83
E 61

I 468
		if (e->e_lockfp != NULL)
D 485
		{
			fclose(e->e_lockfp);
			e->e_lockfp = NULL;
		}
E 485
I 485
			(void) close(fileno(e->e_lockfp));
E 485

E 468
E 55
I 49
D 348
		(void) signal(SIGINT, SIG_DFL);
		(void) signal(SIGHUP, SIG_DFL);
		(void) signal(SIGTERM, SIG_DFL);
E 348
I 348
		(void) setsignal(SIGINT, SIG_DFL);
		(void) setsignal(SIGHUP, SIG_DFL);
		(void) setsignal(SIGTERM, SIG_DFL);
E 348
I 55
D 188
		umask(OldUmask);
E 188
I 188
		(void) umask(OldUmask);
I 501
		e->e_to = filename;
		ExitStat = EX_OK;
E 501
I 242

I 470
#ifdef HASLSTAT
		if ((SafeFileEnv != NULL ? lstat(filename, &stb)
					 : stat(filename, &stb)) < 0)
#else
E 470
E 242
E 188
		if (stat(filename, &stb) < 0)
I 471
		{
E 471
I 470
#endif
		{
E 470
I 171
D 242
		{
			errno = 0;
E 242
E 171
D 62
			stb.st_mode = 0;
E 62
I 62
D 330
			stb.st_mode = 0666;
E 330
I 330
			stb.st_mode = FileMode;
I 468
D 470
D 471
		else if (bitset(0111, stb.st_mode) || stb.st_nlink != 1)
E 471
I 471
			oflags |= O_CREAT|O_EXCL;
		}
		else if (bitset(0111, stb.st_mode))
E 471
E 470
I 470
			oflags |= O_CREAT|O_EXCL;
		}
		else if (bitset(0111, stb.st_mode) || stb.st_nlink != 1 ||
			 (SafeFileEnv != NULL && !S_ISREG(stb.st_mode)))
E 470
			exit(EX_CANTCREAT);
E 468
E 330
I 244
		mode = stb.st_mode;
E 244
I 171
D 242
		}
E 242
I 242

		/* limit the errors to those actually caused in the child */
		errno = 0;
		ExitStat = EX_OK;

E 242
E 171
E 62
D 468
		if (bitset(0111, stb.st_mode))
			exit(EX_CANTCREAT);
E 468
I 59
D 378
		if (ctladdr == NULL)
D 99
			ctladdr = &From;
E 99
I 99
D 216
			ctladdr = &CurEnv->e_from;
E 216
I 216
			ctladdr = &e->e_from;
I 244
		else
E 378
I 378
D 501
		if (ctladdr != NULL)
E 501
I 501
		if (ctladdr != NULL || bitset(SFF_RUNASREALUID, sfflags))
E 501
E 378
		{
			/* ignore setuid and setgid bits */
			mode &= ~(S_ISGID|S_ISUID);
		}

E 244
		/* we have to open the dfile BEFORE setuid */
D 244
		if (e->e_dfp == NULL &&  e->e_df != NULL)
E 244
I 244
D 477
		if (e->e_dfp == NULL && e->e_df != NULL)
E 477
I 477
		if (e->e_dfp == NULL && bitset(EF_HAS_DF, e->e_flags))
E 477
E 244
		{
D 477
			e->e_dfp = fopen(e->e_df, "r");
E 477
I 477
			char *df = queuename(e, 'd');

			e->e_dfp = fopen(df, "r");
E 477
D 242
			if (e->e_dfp == NULL) {
E 242
I 242
			if (e->e_dfp == NULL)
			{
E 242
				syserr("mailfile: Cannot open %s for %s from %s",
D 244
				e->e_df, e->e_to, e->e_from);
E 244
I 244
D 350
					e->e_df, e->e_to, e->e_from);
E 350
I 350
D 477
					e->e_df, e->e_to, e->e_from.q_paddr);
E 477
I 477
					df, e->e_to, e->e_from.q_paddr);
E 477
E 350
E 244
			}
		}

I 470
D 481
		if (SafeFileEnv != NULL && SafeFileEnv[0] != NULL)
E 481
I 481
		if (SafeFileEnv != NULL && SafeFileEnv[0] != '\0')
E 481
		{
			int i;

			if (chroot(SafeFileEnv) < 0)
			{
				syserr("mailfile: Cannot chroot(%s)",
					SafeFileEnv);
				exit(EX_CANTCREAT);
			}
			i = strlen(SafeFileEnv);
			if (strncmp(SafeFileEnv, filename, i) == 0)
				filename += i;
		}
		if (chdir("/") < 0)
			syserr("mailfile: cannot chdir(/)");

E 470
E 216
E 99
E 59
D 244
		if (!bitset(S_ISGID, stb.st_mode) || setgid(stb.st_gid) < 0)
E 244
I 244
D 501
		if (!bitset(S_ISGID, mode) || setgid(stb.st_gid) < 0)
E 501
I 501
		/* select a new user to run as */
		if (!bitset(SFF_RUNASREALUID, sfflags))
E 501
E 244
D 58
			(void) setgid(getgid());
E 58
I 58
D 61
			(void) setgid(ctladdr->q_gid);
E 61
I 61
		{
D 218
			if (ctladdr->q_uid == 0)
E 218
I 218
D 242
			if (ctladdr->q_uid == 0) {
E 242
I 242
D 378
			if (ctladdr->q_uid == 0)
E 378
I 378
D 451
			if (ctladdr == NULL || ctladdr->q_uid == 0)
E 378
			{
E 242
E 218
D 355
				(void) setgid(DefGid);
E 355
I 270
D 275
#ifndef SYSTEM5
E 275
E 270
D 218
			else
E 218
I 218
				(void) initgroups(DefUser, DefGid);
I 270
D 275
#endif
E 275
E 270
D 242
			} else {
E 242
I 242
			}
			else
			{
E 451
I 451
D 501
			if (ctladdr != NULL && ctladdr->q_uid != 0)
E 451
E 242
E 218
D 355
				(void) setgid(ctladdr->q_gid);
E 355
I 270
D 275
#ifndef SYSTEM5
E 275
E 270
I 218
D 244
				(void) initgroups(ctladdr->q_ruser?
					ctladdr->q_ruser: ctladdr->q_user,
E 244
I 244
				(void) initgroups(ctladdr->q_ruser ?
					ctladdr->q_ruser : ctladdr->q_user,
E 244
					ctladdr->q_gid);
E 501
I 501
			if (bitset(S_ISUID, mode))
			{
				RealUserName = NULL;
				RealUid = stb.st_uid;
			}
			else if (ctladdr != NULL && ctladdr->q_uid != 0)
			{
				if (ctladdr->q_ruser != NULL)
					RealUserName = ctladdr->q_ruser;
				else
					RealUserName = ctladdr->q_user;
				RealUid = ctladdr->q_uid;
			}
			else if (FileMailer != NULL && FileMailer->m_uid != 0)
			{
				RealUserName = DefUser;
				RealUid = FileMailer->m_uid;
			}
			else
			{
				RealUserName = DefUser;
				RealUid = DefUid;
			}

			/* select a new group to run as */
			if (bitset(S_ISGID, mode))
				RealGid = stb.st_gid;
			else if (ctladdr != NULL && ctladdr->q_uid != 0)
				RealGid = ctladdr->q_gid;
E 501
I 270
D 275
#endif
E 275
E 270
D 451
			}
E 451
I 451
			else if (FileMailer != NULL && FileMailer->m_gid != 0)
D 501
				(void) initgroups(DefUser, FileMailer->m_gid);
E 501
I 501
				RealGid = FileMailer->m_gid;
E 501
			else
D 501
				(void) initgroups(DefUser, DefGid);
E 501
I 501
				RealGid = DefGid;
E 501
E 451
E 218
		}
E 61
E 58
D 244
		if (!bitset(S_ISUID, stb.st_mode) || setuid(stb.st_uid) < 0)
E 244
I 244
D 501
		if (!bitset(S_ISUID, mode) || setuid(stb.st_uid) < 0)
E 501
I 501

		/* last ditch */
		if (!bitset(SFF_ROOTOK, sfflags))
E 501
E 244
D 58
			(void) setuid(getuid());
E 58
I 58
D 61
			(void) setuid(ctladdr->q_uid);
E 61
I 61
		{
D 378
			if (ctladdr->q_uid == 0)
E 378
I 378
D 451
			if (ctladdr == NULL || ctladdr->q_uid == 0)
E 378
				(void) setuid(DefUid);
			else
E 451
I 451
D 501
			if (ctladdr != NULL && ctladdr->q_uid != 0)
E 451
				(void) setuid(ctladdr->q_uid);
I 451
			else if (FileMailer != NULL && FileMailer->m_uid != 0)
				(void) setuid(FileMailer->m_uid);
			else
				(void) setuid(DefUid);
E 501
I 501
			if (RealUid == 0)
				RealUid = DefUid;
			if (RealGid == 0)
				RealGid = DefGid;
E 501
E 451
		}
I 242
D 501
		FileName = filename;
		LineNumber = 0;
E 242
E 61
E 58
E 55
E 49
D 98
		f = fopen(filename, "a");
E 98
I 98
D 330
		f = dfopen(filename, "a");
E 330
I 330
D 470
D 471
		f = dfopen(filename, O_WRONLY|O_CREAT|O_APPEND, FileMode);
E 471
I 471
		f = dfopen(filename, oflags, FileMode);
E 471
E 470
I 470
		f = dfopen(filename, oflags, FileMode);
E 501
I 501

		/* now set the group and user ids */
I 506
		endpwent();
E 506
		if (RealUserName != NULL)
			(void) initgroups(RealUserName, RealGid);
		else
			(void) setgid(RealGid);
		(void) setuid(RealUid);

		sfflags |= SFF_NOPATHCHECK;
		sfflags &= ~SFF_OPENASROOT;
		f = safefopen(filename, oflags, FileMode, sfflags);
E 501
E 470
E 330
E 98
		if (f == NULL)
I 242
		{
D 279
			message("cannot open");
E 279
I 279
D 280
			extern char Arpa_PSyserr[];

			message(Arpa_PSyserr, "cannot open");
E 280
I 280
D 360
			message("554 cannot open");
E 360
I 360
			message("554 cannot open: %s", errstring(errno));
I 468
D 501
			exit(EX_CANTCREAT);
		}
		if (fstat(fileno(f), &fsb) < 0 ||
D 470
D 471
		    stb.st_nlink != fsb.st_nlink ||
		    stb.st_dev != fsb.st_dev ||
		    stb.st_ino != fsb.st_ino ||
		    stb.st_uid != fsb.st_uid)
E 471
I 471
		    !bitset(O_CREAT, oflags) &&
		     (stb.st_nlink != fsb.st_nlink ||
		      stb.st_dev != fsb.st_dev ||
		      stb.st_ino != fsb.st_ino ||
		      stb.st_uid != fsb.st_uid))
E 471
E 470
I 470
		    (!bitset(O_CREAT, oflags) &&
		     (stb.st_nlink != fsb.st_nlink ||
		      stb.st_dev != fsb.st_dev ||
		      stb.st_ino != fsb.st_ino ||
		      stb.st_uid != fsb.st_uid)))
E 470
		{
			message("554 cannot write: file changed after open");
E 501
E 468
E 360
E 280
E 279
E 242
			exit(EX_CANTCREAT);
I 242
		}
E 242

D 72
		putmessage(f, Mailer[1]);
E 72
I 72
D 100
		putmessage(f, Mailer[1], FALSE);
E 100
I 100
D 154
		putfromline(f, Mailer[1]);
		(*CurEnv->e_puthdr)(f, Mailer[1], CurEnv);
E 154
I 154
D 159
		putfromline(f, ProgMailer);
		(*CurEnv->e_puthdr)(f, ProgMailer, CurEnv);
E 159
I 159
D 166
		putfromline(f, ProgMailer, FALSE);
		(*CurEnv->e_puthdr)(f, ProgMailer, CurEnv, FALSE);
E 159
E 154
D 107
		fprintf(f, "\n");
E 107
I 107
		fputs("\n", f);
E 107
D 154
		(*CurEnv->e_putbody)(f, Mailer[1], FALSE);
E 154
I 154
D 157
		(*CurEnv->e_putbody)(f, ProgMailer, FALSE);
E 157
I 157
D 159
		(*CurEnv->e_putbody)(f, ProgMailer, FALSE, CurEnv);
E 159
I 159
		(*CurEnv->e_putbody)(f, ProgMailer, FALSE, CurEnv, FALSE);
E 159
E 157
E 154
E 100
E 72
		fputs("\n", f);
E 166
I 166
D 247
		putfromline(f, ProgMailer);
E 247
I 247
D 325
		putfromline(f, ProgMailer, e);
E 247
D 250
		(*CurEnv->e_puthdr)(f, ProgMailer, CurEnv);
E 250
I 250
		(*e->e_puthdr)(f, ProgMailer, e);
E 250
		putline("\n", f, ProgMailer);
D 250
		(*CurEnv->e_putbody)(f, ProgMailer, CurEnv);
E 250
I 250
		(*e->e_putbody)(f, ProgMailer, e);
E 250
		putline("\n", f, ProgMailer);
E 325
I 325
D 405
		putfromline(f, FileMailer, e);
		(*e->e_puthdr)(f, FileMailer, e);
		putline("\n", f, FileMailer);
D 329
		(*e->e_putbody)(f, FileMailer, e);
E 329
I 329
		(*e->e_putbody)(f, FileMailer, e, NULL);
E 329
		putline("\n", f, FileMailer);
E 405
I 405
		bzero(&mcibuf, sizeof mcibuf);
		mcibuf.mci_mailer = FileMailer;
		mcibuf.mci_out = f;
		if (bitnset(M_7BITS, FileMailer->m_flags))
			mcibuf.mci_flags |= MCIF_7BIT;

		putfromline(&mcibuf, e);
D 430
		(*e->e_puthdr)(&mcibuf, e);
E 430
I 430
D 450
		(*e->e_puthdr)(&mcibuf, e->e_header, e);
E 430
D 431
		putline("\n", &mcibuf);
E 431
		(*e->e_putbody)(&mcibuf, e, NULL);
E 450
I 450
D 462
		(*e->e_puthdr)(&mcibuf, e->e_header, e, 0);
		(*e->e_putbody)(&mcibuf, e, NULL, 0);
E 462
I 462
		(*e->e_puthdr)(&mcibuf, e->e_header, e);
		(*e->e_putbody)(&mcibuf, e, NULL);
E 462
E 450
		putline("\n", &mcibuf);
E 405
E 325
I 242
		if (ferror(f))
		{
D 279
			message("I/O error");
E 279
I 279
D 280
			extern char Arpa_TSyserr[];

			message(Arpa_TSyserr, "I/O error");
E 280
I 280
D 360
			message("451 I/O error");
E 360
I 360
			message("451 I/O error: %s", errstring(errno));
E 360
E 280
E 279
			setstat(EX_IOERR);
		}
E 242
E 166
D 301
		(void) fclose(f);
E 301
I 301
		(void) xfclose(f, "mailfile", filename);
E 301
		(void) fflush(stdout);
I 61

D 98
		/* reset ISUID & ISGID bits */
E 98
I 98
		/* reset ISUID & ISGID bits for paranoid systems */
E 98
D 69
		(void) chmod(filename, stb.st_mode);
E 69
I 69
		(void) chmod(filename, (int) stb.st_mode);
E 69
E 61
D 242
		exit(EX_OK);
E 242
I 242
		exit(ExitStat);
E 242
I 54
		/*NOTREACHED*/
E 54
	}
	else
	{
		/* parent -- wait for exit status */
D 154
		register int i;
		auto int stat;
E 154
I 154
		int st;
E 154

D 154
		while ((i = wait(&stat)) != pid)
		{
			if (i < 0)
			{
				stat = EX_OSERR << 8;
				break;
			}
		}
I 49
		if ((stat & 0377) != 0)
			stat = EX_UNAVAILABLE << 8;
E 49
		return ((stat >> 8) & 0377);
E 154
I 154
		st = waitfor(pid);
D 359
		if ((st & 0377) != 0)
			return (EX_UNAVAILABLE);
E 359
I 359
		if (WIFEXITED(st))
			return (WEXITSTATUS(st));
E 359
		else
I 360
		{
			syserr("child died on signal %d", st);
E 360
D 359
			return ((st >> 8) & 0377);
E 359
I 359
			return (EX_UNAVAILABLE);
I 360
		}
E 360
E 359
I 216
		/*NOTREACHED*/
E 216
E 154
	}
E 48
D 312
}
I 67
/*
**  SENDALL -- actually send all the messages.
**
**	Parameters:
I 103
**		e -- the envelope to send.
E 103
D 150
**		verifyonly -- if set, only give verification messages.
E 150
I 150
D 177
**		mode -- the delivery mode to use.
E 177
I 177
**		mode -- the delivery mode to use.  If SM_DEFAULT, use
D 308
**			the current SendMode.
E 308
I 308
**			the current e->e_sendmode.
E 308
E 177
E 150
**
**	Returns:
**		none.
**
**	Side Effects:
**		Scans the send lists and sends everything it finds.
I 103
**		Delivers any appropriate error messages.
I 150
**		If we are running in a non-interactive mode, takes the
**			appropriate action.
E 150
E 103
*/

D 103
sendall(verifyonly)
E 103
I 103
D 150
sendall(e, verifyonly)
E 150
I 150
sendall(e, mode)
E 150
	ENVELOPE *e;
E 103
D 150
	bool verifyonly;
E 150
I 150
	char mode;
E 150
{
D 75
	register int i;
E 75
I 75
	register ADDRESS *q;
I 120
D 301
	bool oldverbose;
I 150
	int pid;
E 301
I 282
	char *owner;
	int otherowners;
I 306
	register ENVELOPE *ee;
E 306
	ENVELOPE *splitenv = NULL;
E 282
I 227
D 266
	int nsent;
E 266
I 238
D 303
# ifdef LOCKF
	struct flock lfd;
# endif
E 303
E 238
E 227
I 216
D 219
	FILE *lockfp, *queueup();
E 219
I 219
D 237
	FILE *lockfp = NULL, *queueup();
E 237
E 219
E 216
I 196
D 197
	register char *p;
	char user[MAXNAME];
	char buf[MAXNAME];
E 197
E 196
I 177

	/* determine actual delivery mode */
	if (mode == SM_DEFAULT)
	{
D 190
		extern int QueueLA;
E 190
I 190
		extern bool shouldqueue();
E 190

D 190
		if (getla() > QueueLA)
E 190
I 190
D 261
		if (shouldqueue(e->e_msgpriority))
E 261
I 261
D 279
		if (shouldqueue(e->e_msgpriority, e->e_ctime))
E 279
I 279
D 308
		mode = SendMode;
E 308
I 308
		mode = e->e_sendmode;
E 308
		if (mode != SM_VERIFY &&
		    shouldqueue(e->e_msgpriority, e->e_ctime))
E 279
E 261
E 190
			mode = SM_QUEUE;
D 279
		else
			mode = SendMode;
E 279
	}
E 177
E 150
E 120
E 75
D 103
	typedef int (*fnptr)();
E 103

I 76
D 154
# ifdef DEBUG
E 154
I 154
D 213
#ifdef DEBUG
E 213
E 154
D 117
	if (Debug > 1)
E 117
I 117
D 137
	if (tTd(13, 2))
E 137
I 137
	if (tTd(13, 1))
E 137
E 117
	{
D 99
		printf("\nSendQueue:\n");
		printaddr(SendQueue, TRUE);
E 99
I 99
D 137
		printf("\nSend Queue:\n");
E 137
I 137
D 144
		printf("\nSENDALL: verify %d, sendqueue:\n");
E 144
I 144
D 150
		printf("\nSENDALL: verify %d, sendqueue:\n", verifyonly);
E 150
I 150
D 301
		printf("\nSENDALL: mode %c, sendqueue:\n", mode);
E 301
I 301
		printf("\nSENDALL: mode %c, e_from ", mode);
		printaddr(&e->e_from, FALSE);
		printf("sendqueue:\n");
E 301
E 150
E 144
E 137
D 103
		printaddr(CurEnv->e_sendqueue, TRUE);
E 103
I 103
		printaddr(e->e_sendqueue, TRUE);
E 103
E 99
	}
D 154
# endif DEBUG
E 154
I 154
D 213
#endif DEBUG
E 213
E 154
E 76
D 75
	for (i = 0; Mailer[i] != NULL; i++)
	{
		ADDRESS *q;
E 75

D 75
		for (q = Mailer[i]->m_sendq; q != NULL; q = q->q_next)
E 75
I 75
D 99
	for (q = SendQueue; q != NULL; q = q->q_next)
E 99
I 99
D 103
	for (q = CurEnv->e_sendqueue; q != NULL; q = q->q_next)
E 103
I 103
	/*
D 150
	**  Run through the list and send everything.
E 150
I 150
	**  Do any preprocessing necessary for the mode we are running.
I 154
	**	Check to make sure the hop count is reasonable.
	**	Delete sends to the sender in mailing lists.
E 154
E 150
	*/

I 150
D 154
# ifdef QUEUE
	if (mode == SM_QUEUE)
E 154
I 154
	CurEnv = e;

D 230
	if (e->e_hopcount > MAXHOP)
E 230
I 230
	if (e->e_hopcount > MaxHopCount)
E 230
E 154
	{
D 154
		register ADDRESS *q;
E 154
I 154
D 216
		syserr("sendall: too many hops (%d max)", MAXHOP);
E 216
I 216
		errno = 0;
D 280
		syserr("sendall: too many hops %d (%d max): from %s, to %s",
E 280
I 280
		syserr("554 too many hops %d (%d max): from %s, to %s",
E 280
D 230
			e->e_hopcount, MAXHOP, e->e_from, e->e_to);
E 230
I 230
D 253
			e->e_hopcount, MaxHopCount, e->e_from, e->e_to);
E 253
I 253
D 266
			e->e_hopcount, MaxHopCount, e->e_from.q_paddr, e->e_to);
E 266
I 266
			e->e_hopcount, MaxHopCount, e->e_from.q_paddr,
			e->e_sendqueue->q_paddr);
E 266
E 253
E 230
E 216
		return;
	}
E 154

D 151
		for (q = CurEnv->e_sendqueue; q != NULL; q = q->q_next)
E 151
I 151
D 154
		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
E 151
		{
			if (!bitset(QDONTSEND, q->q_flags))
			{
D 151
				CurEnv->e_to = q->q_paddr;
E 151
I 151
				e->e_to = q->q_paddr;
E 151
				message(Arpa_Info, "queued");
				if (LogLevel > 4)
					logdelivery("queued");
			}
D 151
			CurEnv->e_to = NULL;
E 151
I 151
			e->e_to = NULL;
E 151
		}
E 154
I 154
	if (!MeToo)
	{
I 175
		extern ADDRESS *recipient();

E 175
D 301
		e->e_from.q_flags |= QDONTSEND;
E 301
I 269
		if (tTd(13, 5))
		{
			printf("sendall: QDONTSEND ");
			printaddr(&e->e_from, FALSE);
		}
I 301
		e->e_from.q_flags |= QDONTSEND;
E 301
E 269
D 175
		recipient(&e->e_from, &e->e_sendqueue);
E 175
I 175
D 250
		(void) recipient(&e->e_from, &e->e_sendqueue);
E 250
I 250
		(void) recipient(&e->e_from, &e->e_sendqueue, e);
E 250
E 175
E 154
	}
I 154

I 282
	/*
	**  Handle alias owners.
	**
	**	We scan up the q_alias chain looking for owners.
	**	We discard owners that are the same as the return path.
	*/

	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
		register struct address *a;

		for (a = q; a != NULL && a->q_owner == NULL; a = a->q_alias)
			continue;
		if (a != NULL)
			q->q_owner = a->q_owner;
				
D 301
		if (q->q_owner != NULL && !bitset(QDONTSEND, q->q_flags) &&
		    strcmp(q->q_owner, e->e_returnpath) == 0)
E 301
I 301
		if (q->q_owner != NULL &&
		    !bitset(QDONTSEND, q->q_flags) &&
		    strcmp(q->q_owner, e->e_from.q_paddr) == 0)
E 301
			q->q_owner = NULL;
	}
		
	owner = "";
	otherowners = 1;
	while (owner != NULL && otherowners > 0)
	{
		owner = NULL;
		otherowners = 0;

		for (q = e->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (bitset(QDONTSEND, q->q_flags))
				continue;

			if (q->q_owner != NULL)
			{
				if (owner == NULL)
					owner = q->q_owner;
				else if (owner != q->q_owner)
				{
					if (strcmp(owner, q->q_owner) == 0)
					{
						/* make future comparisons cheap */
						q->q_owner = owner;
					}
					else
					{
						otherowners++;
					}
					owner = q->q_owner;
				}
			}
			else
			{
				otherowners++;
			}
		}

		if (owner != NULL && otherowners > 0)
		{
D 306
			register ENVELOPE *ee;
E 306
D 283
			extern ENVELOPE *newenvelope();
E 283
			extern HDR *copyheader();
			extern ADDRESS *copyqueue();

I 301
			/*
			**  Split this envelope into two.
			*/

E 301
			ee = (ENVELOPE *) xalloc(sizeof(ENVELOPE));
D 301
			STRUCTCOPY(*e, *ee);
E 301
I 301
			*ee = *e;
E 301
			ee->e_id = NULL;
D 301
			ee->e_parent = e;
E 301
I 301
			(void) queuename(ee, '\0');

			if (tTd(13, 1))
				printf("sendall: split %s into %s\n",
					e->e_id, ee->e_id);

E 301
			ee->e_header = copyheader(e->e_header);
			ee->e_sendqueue = copyqueue(e->e_sendqueue);
			ee->e_errorqueue = copyqueue(e->e_errorqueue);
			ee->e_flags = e->e_flags & ~(EF_INQUEUE|EF_CLRQUEUE);
D 301
			ee->e_returnpath = owner;
			ee->e_putbody = parentbody;
E 301
I 301
D 304
			(void) parseaddr(owner, &ee->e_from, 1, '\0', NULL, ee);
E 304
I 304
			setsender(owner, ee, NULL, TRUE);
E 304
			if (tTd(13, 5))
			{
				printf("sendall(split): QDONTSEND ");
				printaddr(&ee->e_from, FALSE);
			}
			ee->e_from.q_flags |= QDONTSEND;
			ee->e_dfp = NULL;
			ee->e_xfp = NULL;
			ee->e_lockfp = NULL;
			ee->e_df = NULL;
I 308
			ee->e_errormode = EM_MAIL;
E 308
E 301
			ee->e_sibling = splitenv;
			splitenv = ee;
			
			for (q = e->e_sendqueue; q != NULL; q = q->q_next)
				if (q->q_owner == owner)
					q->q_flags |= QDONTSEND;
			for (q = ee->e_sendqueue; q != NULL; q = q->q_next)
				if (q->q_owner != owner)
					q->q_flags |= QDONTSEND;

			if (e->e_df != NULL && mode != SM_VERIFY)
			{
				ee->e_dfp = NULL;
D 285
				ee->e_df = queuename(ee, 'd');
E 285
I 285
				ee->e_df = newstr(queuename(ee, 'd'));
E 285
				if (link(e->e_df, ee->e_df) < 0)
				{
					syserr("sendall: link(%s, %s)",
						e->e_df, ee->e_df);
				}
			}
I 301

			if (mode != SM_VERIFY)
D 311
			{
				char xfbuf1[20], xfbuf2[20];

				(void) strcpy(xfbuf1, queuename(e, 'x'));
				(void) strcpy(xfbuf2, queuename(ee, 'x'));
				if (link(xfbuf1, xfbuf2) < 0)
				{
					syserr("sendall: link(%s, %s)",
						xfbuf1, xfbuf2);
				}
			}
E 311
I 311
				openxscript(ee);
E 311
I 305
#ifdef LOG
			if (LogLevel > 4)
				syslog(LOG_INFO, "%s: clone %s",
					ee->e_id, e->e_id);
#endif
E 305
E 301
		}
	}

	if (owner != NULL)
D 301
		e->e_returnpath = owner;
E 301
I 301
	{
D 304
		(void) parseaddr(owner, &e->e_from, 1, '\0', NULL, e);
E 304
I 304
		setsender(owner, e, NULL, TRUE);
E 304
		if (tTd(13, 5))
		{
			printf("sendall(owner): QDONTSEND ");
			printaddr(&e->e_from, FALSE);
		}
		e->e_from.q_flags |= QDONTSEND;
I 308
		e->e_errormode = EM_MAIL;
E 308
	}
E 301

E 282
# ifdef QUEUE
E 154
D 152
	if (mode == SM_QUEUE || mode == SM_FORK ||
	    (mode != SM_VERIFY && SuperSafe))
E 152
I 152
	if ((mode == SM_QUEUE || mode == SM_FORK ||
	     (mode != SM_VERIFY && SuperSafe)) &&
	    !bitset(EF_INQUEUE, e->e_flags))
I 306
	{
		/* be sure everything is instantiated in the queue */
E 306
E 152
D 151
		queueup(CurEnv, TRUE);
E 151
I 151
D 154
		queueup(e, TRUE);
E 154
I 154
D 216
		queueup(e, TRUE, mode == SM_QUEUE);
E 216
I 216
D 237
		lockfp = queueup(e, TRUE, mode == SM_QUEUE);
E 237
I 237
		queueup(e, TRUE, mode == SM_QUEUE);
I 306
		for (ee = splitenv; ee != NULL; ee = ee->e_sibling)
			queueup(ee, TRUE, mode == SM_QUEUE);
	}
E 306
E 237
E 216
E 154
E 151
D 256
#endif QUEUE
E 256
I 256
#endif /* QUEUE */
E 256

I 282
	if (splitenv != NULL)
	{
I 301
D 306
		register ENVELOPE *ee;

E 306
E 301
		if (tTd(13, 1))
		{
			printf("\nsendall: Split queue; remaining queue:\n");
			printaddr(e->e_sendqueue, TRUE);
		}

D 301
		while (splitenv != NULL)
E 301
I 301
		for (ee = splitenv; ee != NULL; ee = ee->e_sibling)
E 301
		{
D 301
			sendall(splitenv, mode);
			splitenv = splitenv->e_sibling;
E 301
I 301
			CurEnv = ee;
			sendenvelope(ee, mode);
E 301
		}

		CurEnv = e;
	}
I 301
	sendenvelope(e, mode);
E 301

I 301
	for (; splitenv != NULL; splitenv = splitenv->e_sibling)
		dropenvelope(splitenv);
}

sendenvelope(e, mode)
	register ENVELOPE *e;
	char mode;
{
	bool oldverbose;
	int pid;
	register ADDRESS *q;
I 303
#ifdef LOCKF
	struct flock lfd;
#endif
E 303

E 301
E 282
E 150
I 120
	oldverbose = Verbose;
D 150
	if (verifyonly)
E 150
I 150
	switch (mode)
	{
	  case SM_VERIFY:
E 150
		Verbose = TRUE;
I 150
		break;

	  case SM_QUEUE:
I 236
  queueonly:
E 236
D 151
		CurEnv->e_df = CurEnv->e_qf = NULL;
		CurEnv->e_dontqueue = TRUE;
E 151
I 151
D 152
		e->e_df = e->e_qf = NULL;
		e->e_dontqueue = TRUE;
E 151
		finis();
E 152
I 152
		e->e_flags |= EF_INQUEUE|EF_KEEPQUEUE;
I 236
D 237
		if (lockfp != NULL)
			(void) fclose(lockfp);
E 237
E 236
E 152
		return;

	  case SM_FORK:
I 151
D 152
		(void) fflush(Xscript);
E 152
I 152
D 157
		if (Xscript != NULL)
			(void) fflush(Xscript);
E 157
I 157
		if (e->e_xfp != NULL)
			(void) fflush(e->e_xfp);
I 236

# ifdef LOCKF
		/*
		**  Since lockf has the interesting semantic that the
D 238
		**  lock is lost when we close the file in the parent,
		**  we'll risk losing the lock here by closing before
		**  the fork, and then trying to get it back in the
		**  child.
E 238
I 238
		**  lock is lost when we fork, we have to risk losing
		**  the lock here by closing before the fork, and then
		**  trying to get it back in the child.
E 238
		*/

D 237
		if (lockfp != NULL)
E 237
I 237
		if (e->e_lockfp != NULL)
E 237
		{
D 237
			(void) fclose(lockfp);
			lockfp = NULL;
E 237
I 237
D 301
			(void) fclose(e->e_lockfp);
E 301
I 301
			(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
E 301
			e->e_lockfp = NULL;
E 237
		}
# endif /* LOCKF */

E 236
E 157
E 152
E 151
		pid = fork();
		if (pid < 0)
		{
D 236
			mode = SM_DELIVER;
			break;
E 236
I 236
			goto queueonly;
E 236
		}
		else if (pid > 0)
I 151
		{
			/* be sure we leave the temp files to our child */
D 152
			e->e_id = e->e_df = e->e_qf = NULL;
			e->e_dontqueue = TRUE;
			Transcript = NULL;
E 152
I 152
			e->e_id = e->e_df = NULL;
I 236
# ifndef LOCKF
E 236
I 216
D 237
			if (lockfp != NULL)
				(void) fclose(lockfp);
E 237
I 237
			if (e->e_lockfp != NULL)
I 269
			{
E 269
D 301
				(void) fclose(e->e_lockfp);
E 301
I 301
				(void) xfclose(e->e_lockfp, "sendenvelope", "lockfp");
E 301
I 269
				e->e_lockfp = NULL;
			}
E 269
E 237
I 236
# endif
I 269

			/* close any random open files in the envelope */
			if (e->e_dfp != NULL)
			{
D 301
				(void) fclose(e->e_dfp);
E 301
I 301
				(void) xfclose(e->e_dfp, "sendenvelope", "dfp");
E 301
				e->e_dfp = NULL;
			}
			if (e->e_xfp != NULL)
			{
D 301
				(void) fclose(e->e_xfp);
E 301
I 301
				(void) xfclose(e->e_xfp, "sendenvelope", "xfp");
E 301
				e->e_xfp = NULL;
			}
E 269
E 236
E 216
E 152
E 151
			return;
I 151
		}
E 151

		/* double fork to avoid zombies */
		if (fork() > 0)
			exit(EX_OK);

D 151
		/* now arrange to run the queue */
		HoldErrs = MailBack = TRUE;
		Verbose = FALSE;
E 151
I 151
		/* be sure we are immune from the terminal */
D 155
		disconnect(TRUE);
E 155
I 155
D 164
		disconnect();
E 164
I 164
D 302
		disconnect(FALSE);
E 302
I 302
		disconnect(FALSE, e);
E 302
I 235

# ifdef LOCKF
		/*
D 236
		**  When our parent closed lockfp, we lost the lock.
		**  Try to get it back now.
E 236
I 236
		**  Now try to get our lock back.
E 236
		*/

I 238
		lfd.l_type = F_WRLCK;
		lfd.l_whence = lfd.l_start = lfd.l_len = 0;
E 238
D 236
		if (lockfp != NULL)
E 236
I 236
D 237
		lockfp = fopen(queuename(e, 'q'), "r+");
		if (lockfp == NULL || lockf(fileno(lockfp), F_TLOCK, 0) < 0)
E 237
I 237
		e->e_lockfp = fopen(queuename(e, 'q'), "r+");
		if (e->e_lockfp == NULL ||
D 238
		    lockf(fileno(e->e_lockfp), F_TLOCK, 0) < 0)
E 238
I 238
		    fcntl(fileno(e->e_lockfp), F_SETLK, &lfd) < 0)
E 238
E 237
E 236
		{
D 236
			if (fseek(lockfp, 0, SEEK_SET) != 0 ||
			    lockf(fileno(lockfp), F_TLOCK, 0) < 0)
			{
				/* oops....  lost it */
E 236
I 236
			/* oops....  lost it */
I 305
			if (tTd(13, 1))
				printf("sendenvelope: %s lost lock: lockfp=%x, %s\n",
					e->e_id, e->e_lockfp, errstring(errno));

E 305
E 236
# ifdef LOG
D 236
				if (LogLevel > 5)
					syslog(LOG_NOTICE, "%s: lost lock",
						CurEnv->e_id);
E 236
I 236
D 273
			if (LogLevel > 5)
E 273
I 273
			if (LogLevel > 29)
E 273
				syslog(LOG_NOTICE, "%s: lost lock: %m",
D 247
					CurEnv->e_id);
E 247
I 247
					e->e_id);
E 247
E 236
# endif /* LOG */
D 236
				fclose(lockfp);
				exit(EX_OK);
			}
E 236
I 236
			exit(EX_OK);
E 236
		}
# endif /* LOCKF */
E 235
E 164
E 155

I 276
		/*
		**  Close any cached connections.
		**
		**	We don't send the QUIT protocol because the parent
		**	still knows about the connection.
		**
		**	This should only happen when delivering an error
		**	message.
		*/

		mci_flush(FALSE, NULL);

E 276
E 151
		break;
	}

	/*
	**  Run through the list and send everything.
	*/

I 227
D 266
	nsent = 0;
E 266
I 266
	e->e_nsent = 0;
E 266
E 227
I 196
D 197
restart:
E 197
E 196
E 150
E 120
	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
E 103
E 99
	{
D 150
		if (verifyonly)
E 150
I 150
		if (mode == SM_VERIFY)
E 150
E 75
		{
D 75
			if (verifyonly)
E 75
I 75
D 99
			To = q->q_paddr;
E 99
I 99
D 151
			CurEnv->e_to = q->q_paddr;
E 151
I 151
			e->e_to = q->q_paddr;
E 151
E 99
			if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
E 75
D 106
			{
D 75
				To = q->q_paddr;
D 74
				if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
E 74
I 74
				if (!bitset(QDONTSEND|QBADADDR|QPSEUDO, q->q_flags))
E 74
				{
D 68
					if (q->q_mailer == MN_LOCAL || q->q_mailer == MN_PROG)
E 68
I 68
					if (bitset(M_LOCAL, q->q_mailer->m_flags))
E 68
						message(Arpa_Info, "deliverable");
					else
						message(Arpa_Info, "queueable");
				}
E 75
I 75
				if (bitset(M_LOCAL, q->q_mailer->m_flags))
					message(Arpa_Info, "deliverable");
				else
					message(Arpa_Info, "queueable");
E 75
			}
E 106
I 106
D 280
				message(Arpa_Info, "deliverable");
E 280
I 280
				message("deliverable");
E 280
E 106
D 75
			else
				(void) deliver(q, (fnptr) NULL);
E 75
		}
I 75
D 227
		else
I 196
D 197
		{
			if (strcmp(q->q_mailer->m_mailer, "[IPC]") == 0 &&
			    !bitset(QDONTSEND, q->q_flags))
			{
				if ((nmx = getmxrr(q->q_host, mxhosts, MAXMXHOSTS)) < 0)
				{
					mxhosts[0] = q->q_host;
					nmx = 1;
				}
				/* we get this mail */
				expand("\001j", buf, &buf[sizeof buf - 1], e);
				if (sameword(mxhosts[0], buf))
				{
					strcpy(user, q->q_user);
					if (p = index(user, '@'))
						*p = '\0';
					sendtolist(user, q, &e->e_sendqueue);
					goto restart;
				}
			}
E 197
E 196
D 100
			(void) deliver(q, (fnptr) NULL);
E 100
I 100
D 154
			(void) deliver(q);
E 154
I 154
			(void) deliver(e, q);
E 227
I 227
D 301
		else if (!bitset(QDONTSEND, q->q_flags))
E 301
I 301
		else if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
E 301
		{
I 229
# ifdef QUEUE
E 229
			/*
			**  Checkpoint the send list every few addresses
			*/

D 266
			if (nsent >= CheckpointInterval)
E 266
I 266
			if (e->e_nsent >= CheckpointInterval)
E 266
			{
D 229
				queueup(e, TRUE, FALSE);
E 229
I 229
D 237
				FILE *nlockfp;

				nlockfp = queueup(e, TRUE, FALSE);
				if (lockfp != NULL)
					fclose(lockfp);
				lockfp = nlockfp;
E 237
I 237
				queueup(e, TRUE, FALSE);
E 237
E 229
D 266
				nsent = 0;
E 266
I 266
				e->e_nsent = 0;
E 266
			}
I 229
# endif /* QUEUE */
E 229
D 266
			if (deliver(e, q) == EX_OK)
				nsent++;
E 266
I 266
			(void) deliver(e, q);
E 266
		}
E 227
I 196
D 197
		}
E 197
E 196
E 154
I 103
	}
I 120
	Verbose = oldverbose;
E 120

	/*
	**  Now run through and check for errors.
	*/

D 150
	if (verifyonly)
E 150
I 150
D 216
	if (mode == SM_VERIFY)
E 216
I 216
D 237
	if (mode == SM_VERIFY) {
		if (lockfp != NULL)
			(void) fclose(lockfp);
E 237
I 237
	if (mode == SM_VERIFY)
I 301
	{
E 301
E 237
E 216
E 150
		return;
I 301
	}
E 301
I 216
D 237
	}
E 237
E 216

	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
D 282
		register ADDRESS *qq;

E 282
I 137
D 213
# ifdef DEBUG
E 213
		if (tTd(13, 3))
		{
			printf("Checking ");
			printaddr(q, FALSE);
		}
D 213
# endif DEBUG
E 213

E 137
D 152
		if (bitset(QQUEUEUP, q->q_flags))
			e->e_queueup = TRUE;
E 152
I 152
		/* only send errors if the message failed */
		if (!bitset(QBADADDR, q->q_flags))
			continue;
I 301

		e->e_flags |= EF_FATALERRS;
E 301
E 152
D 137
		if (!bitset(QBADADDR, q->q_flags))
			continue;
E 137

D 282
		/* we have an address that failed -- find the parent */
		for (qq = q; qq != NULL; qq = qq->q_alias)
		{
			char obuf[MAXNAME + 6];
			extern char *aliaslookup();

			/* we can only have owners for local addresses */
D 168
			if (!bitset(M_LOCAL, qq->q_mailer->m_flags))
E 168
I 168
D 278
			if (!bitnset(M_LOCAL, qq->q_mailer->m_flags))
E 278
I 278
			if (!bitnset(M_LOCALMAILER, qq->q_mailer->m_flags))
E 278
E 168
				continue;

			/* see if the owner list exists */
			(void) strcpy(obuf, "owner-");
D 104
			(void) strcat(obuf, qq->q_user);
E 104
I 104
			if (strncmp(qq->q_user, "owner-", 6) == 0)
				(void) strcat(obuf, "owner");
			else
				(void) strcat(obuf, qq->q_user);
I 222
D 261
			makelower(obuf);
E 261
I 261
			if (!bitnset(M_USR_UPPER, qq->q_mailer->m_flags))
				makelower(obuf);
E 261
E 222
E 104
			if (aliaslookup(obuf) == NULL)
				continue;
I 137

D 213
# ifdef DEBUG
E 213
			if (tTd(13, 4))
				printf("Errors to %s\n", obuf);
D 213
# endif DEBUG
E 213

D 152
			/* add in an errors-to field */
				/*   ugh... must happen before delivery.....
			addheader("errors-to", newstr(obuf), e);
				.... i guess this should go in sendto */

			/* only send errors if the message failed */
			if (!bitset(QBADADDR, q->q_flags))
				break;
E 137

E 152
			/* owner list exists -- add it to the error queue */
D 154
			qq->q_flags &= ~QPRIMARY;
D 129
			sendto(obuf, 1, qq, &e->e_errorqueue);
E 129
I 129
			sendto(obuf, qq, &e->e_errorqueue);
E 129
			MailBack = TRUE;
E 154
I 154
D 158
			sendto(obuf, (ADDRESS *) NULL, &e->e_errorqueue);
E 158
I 158
D 250
			sendtolist(obuf, (ADDRESS *) NULL, &e->e_errorqueue);
E 250
I 250
D 276
			sendtolist(obuf, (ADDRESS *) NULL, &e->e_errorqueue, e);
E 276
I 276
			(void) sendtolist(obuf, (ADDRESS *) NULL,
					  &e->e_errorqueue, e);
E 276
I 261

			/* and set the return path to point to it */
			e->e_returnpath = newstr(obuf);

E 261
E 250
E 158
D 183
			ErrorMode == EM_MAIL;
E 183
I 183
			ErrorMode = EM_MAIL;
E 183
E 154
			break;
		}

		/* if we did not find an owner, send to the sender */
D 139
		if (qq == NULL)
E 139
I 139
		if (qq == NULL && bitset(QBADADDR, q->q_flags))
E 139
D 129
			sendto(e->e_from.q_paddr, 1, qq, &e->e_errorqueue);
E 129
I 129
D 158
			sendto(e->e_from.q_paddr, qq, &e->e_errorqueue);
E 158
I 158
D 250
			sendtolist(e->e_from.q_paddr, qq, &e->e_errorqueue);
E 250
I 250
D 276
			sendtolist(e->e_from.q_paddr, qq, &e->e_errorqueue, e);
E 276
I 276
			(void) sendtolist(e->e_from.q_paddr, qq,
E 282
I 282
D 286
		if (q->q_owner == NULL)
E 286
I 286
		if (q->q_owner == NULL && strcmp(e->e_from.q_paddr, "<>") != 0)
E 286
			(void) sendtolist(e->e_from.q_paddr, NULL,
E 282
					  &e->e_errorqueue, e);
E 276
E 250
E 158
E 129
	}
I 216
D 237

	/* this removes the lock on the file */
	if (lockfp != NULL)
		(void) fclose(lockfp);
E 237
E 216
I 150

	if (mode == SM_FORK)
		finis();
E 312
I 263
}
/*
**  HOSTSIGNATURE -- return the "signature" for a host.
**
**	The signature describes how we are going to send this -- it
**	can be just the hostname (for non-Internet hosts) or can be
**	an ordered list of MX hosts.
**
**	Parameters:
**		m -- the mailer describing this host.
**		host -- the host name.
**		e -- the current envelope.
**
**	Returns:
**		The signature for this host.
**
**	Side Effects:
**		Can tweak the symbol table.
*/

char *
hostsignature(m, host, e)
	register MAILER *m;
	char *host;
	ENVELOPE *e;
{
	register char *p;
	register STAB *s;
	int i;
	int len;
D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
	int nmx;
	auto int rcode;
I 320
	char *hp;
	char *endp;
I 321
D 467
	int oldoptions;
E 467
I 467
	int oldoptions = _res.options;
E 467
E 321
E 320
	char *mxhosts[MAXMXHOSTS + 1];
D 324
	static char myhostbuf[MAXNAME];
E 324
I 298
D 299
#ifdef SETPROCTITLE
	char ptbuf[MAXNAME];
	extern char ProcTitleBuf[MAXNAME];
E 299
E 298
#endif
I 298
D 299
#endif
E 299
E 298

	/*
	**  Check to see if this uses IPC -- if not, it can't have MX records.
	*/

	p = m->m_mailer;
	if (strcmp(p, "[IPC]") != 0 && strcmp(p, "[TCP]") != 0)
	{
		/* just an ordinary mailer */
		return host;
	}

	/*
D 367
	**  If it is a numeric address, just return it.
	*/

	if (host[0] == '[')
		return host;

	/*
E 367
	**  Look it up in the symbol table.
	*/

	s = stab(host, ST_HOSTSIG, ST_ENTER);
	if (s->s_hostsig != NULL)
		return s->s_hostsig;

	/*
	**  Not already there -- create a signature.
	*/

D 419
#ifdef NAMED_BIND
E 419
I 419
#if NAMED_BIND
E 419
I 321
	if (ConfigLevel < 2)
D 467
	{
		oldoptions = _res.options;
E 467
		_res.options &= ~(RES_DEFNAMES | RES_DNSRCH);	/* XXX */
D 467
	}
E 467

E 321
D 324
	if (myhostbuf[0] == '\0')
D 274
		expand("\001j", myhostbuf, &myhostbuf[sizeof myhostbuf - 1], e);
E 274
I 274
		expand("\201j", myhostbuf, &myhostbuf[sizeof myhostbuf - 1], e);
E 274

E 324
I 298
D 299
#ifdef SETPROCTITLE
	(void) strcpy(ptbuf, ProcTitleBuf);
	setproctitle("getmxrr(%s)", host);
#endif

E 299
E 298
D 320
	nmx = getmxrr(host, mxhosts, myhostbuf, &rcode);
I 298
D 299

#ifdef SETPROCTITLE
	setproctitle(NULL, ptbuf);
#endif
E 299

E 298
	if (nmx <= 0)
E 320
I 320
	for (hp = host; hp != NULL; hp = endp)
E 320
	{
D 320
		register MCI *mci;
		extern int errno;
		extern MCI *mci_get();
E 320
I 320
		endp = strchr(hp, ':');
		if (endp != NULL)
			*endp = '\0';
E 320

D 320
		/* update the connection info for this host */
		mci = mci_get(host, m);
		mci->mci_exitstat = rcode;
		mci->mci_errno = errno;
E 320
I 320
D 324
		nmx = getmxrr(hp, mxhosts, myhostbuf, &rcode);
E 324
I 324
		nmx = getmxrr(hp, mxhosts, TRUE, &rcode);
E 324
E 320

D 320
		/* and return the original host name as the signature */
		s->s_hostsig = host;
		return host;
	}
E 320
I 320
		if (nmx <= 0)
		{
			register MCI *mci;
D 378
			extern int errno;
E 378
D 337
			extern MCI *mci_get();
E 337
E 320

D 320
	len = 0;
	for (i = 0; i < nmx; i++)
	{
		len += strlen(mxhosts[i]) + 1;
	}
	s->s_hostsig = p = xalloc(len);
	for (i = 0; i < nmx; i++)
	{
		if (i != 0)
E 320
I 320
			/* update the connection info for this host */
			mci = mci_get(hp, m);
			mci->mci_exitstat = rcode;
			mci->mci_errno = errno;
I 342
D 419
#ifdef NAMED_BIND
E 419
I 419
D 467
#if NAMED_BIND
E 467
E 419
			mci->mci_herrno = h_errno;
D 467
#endif
E 467
E 342

			/* and return the original host name as the signature */
			nmx = 1;
			mxhosts[0] = hp;
		}

		len = 0;
		for (i = 0; i < nmx; i++)
		{
			len += strlen(mxhosts[i]) + 1;
		}
		if (s->s_hostsig != NULL)
			len += strlen(s->s_hostsig) + 1;
		p = xalloc(len);
		if (s->s_hostsig != NULL)
		{
			(void) strcpy(p, s->s_hostsig);
			free(s->s_hostsig);
			s->s_hostsig = p;
			p += strlen(p);
E 320
			*p++ = ':';
D 320
		strcpy(p, mxhosts[i]);
		p += strlen(p);
E 320
I 320
		}
		else
			s->s_hostsig = p;
		for (i = 0; i < nmx; i++)
		{
			if (i != 0)
				*p++ = ':';
			strcpy(p, mxhosts[i]);
			p += strlen(p);
		}
		if (endp != NULL)
			*endp++ = ':';
E 320
	}
	makelower(s->s_hostsig);
I 321
	if (ConfigLevel < 2)
		_res.options = oldoptions;
E 321
#else
	/* not using BIND -- the signature is just the host name */
	s->s_hostsig = host;
#endif
	if (tTd(17, 1))
		printf("hostsignature(%s) = %s\n", host, s->s_hostsig);
	return s->s_hostsig;
I 445
D 493
}
/*
**  SETSTATUS -- set the address status for return messages
**
**	Parameters:
**		a -- the address to set.
**		msg -- the text of the message, which must be in standard
**			SMTP form (3 digits, a space, and a message).
**
**	Returns:
**		none.
*/

setstatus(a, msg)
	register ADDRESS *a;
	char *msg;
{
	char buf[MAXLINE];

D 456
	if (a->q_status != NULL)
		free(a->q_status);
E 456
I 456
	if (a->q_rstatus != NULL)
		free(a->q_rstatus);
E 456
D 488
	if (strlen(msg) > 4)
E 488
I 488
	if (strlen(msg) > (SIZE_T) 4)
E 488
	{
		register char *p, *q;
		int parenlev = 0;

		strncpy(buf, msg, 4);
		p = &buf[4];
		*p++ = '(';
D 453
		for (q = &msg[4]; *q != NULL; q++)
E 453
I 453
		for (q = &msg[4]; *q != '\0'; q++)
E 453
		{
			switch (*q)
			{
			  case '(':
				parenlev++;
				break;

			  case ')':
				if (parenlev > 0)
					parenlev--;
				else
					*p++ = '\\';
				break;
			}
			*p++ = *q;
		}
		while (parenlev-- >= 0)
			*p++ = ')';
		*p++ = '\0';
		msg = buf;
	}
D 456
	a->q_status = newstr(msg);
E 456
I 456
	a->q_rstatus = newstr(msg);
E 493
E 456
E 445
E 263
E 150
D 154
}
/*
**  CHECKERRORS -- check a queue of addresses and process errors.
**
**	Parameters:
**		e -- the envelope to check.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Arranges to queue all tempfailed messages in q
**			or deliver error responses.
*/

checkerrors(e)
	register ENVELOPE *e;
{
I 121
D 153
	register ADDRESS *q;

E 153
E 121
# ifdef DEBUG
D 117
	if (Debug > 0)
E 117
I 117
	if (tTd(4, 1))
E 117
	{
D 115
		printf("\ncheckerrors: errorqueue:\n");
E 115
I 115
D 152
		printf("\ncheckerrors: FatalErrors %d, errorqueue:\n");
E 152
I 152
		printf("\ncheckerrors: e_flags %o, errorqueue:\n", e->e_flags);
E 152
E 115
		printaddr(e->e_errorqueue, TRUE);
	}
# endif DEBUG

	/* mail back the transcript on errors */
D 152
	if (FatalErrors)
		savemail();

	/* queue up anything laying around */
I 122
	if (e->e_dontqueue)
		return;
E 122
D 121
	if (e->e_queueup)
E 121
I 121
	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
E 121
	{
I 121
		if (bitset(QQUEUEUP, q->q_flags))
		{
E 121
# ifdef QUEUE
D 121
		queueup(e, FALSE);
E 121
I 121
			queueup(e, FALSE);
I 138
			e->e_df = e->e_qf = NULL;
			e->e_dontqueue = TRUE;
E 138
E 121
# else QUEUE
D 121
		syserr("finis: trying to queue %s", e->e_df);
E 121
I 121
			syserr("checkerrors: trying to queue %s", e->e_df);
E 121
# endif QUEUE
I 121
			break;
		}
E 121
E 103
E 100
E 75
	}
E 152
I 152
	if (bitset(EF_FATALERRS, e->e_flags))
		savemail(e);
E 154
E 152
}
E 67
E 1
