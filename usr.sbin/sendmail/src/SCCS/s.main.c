h14001
s 00003/00001/01884
d D 8.139 95/06/22 07:02:47 eric 488 487
c debugging patches; minor long class name patches
e
s 00010/00003/01875
d D 8.138 95/06/21 08:47:20 eric 487 486
c properly tweak SevenBitInput flag when -B is given
e
s 00007/00000/01871
d D 8.137 95/06/21 07:12:29 eric 486 485
c close passwd file before setuid() "just in case"
e
s 00006/00003/01865
d D 8.136 95/06/21 07:08:30 eric 485 484
c allow symbolic ruleset names in -bt mode
e
s 00001/00001/01867
d D 8.135 95/06/20 09:37:19 eric 484 483
c avoid infinite loop on /tryflags
e
s 00001/00000/01867
d D 8.134 95/06/20 07:06:36 eric 483 482
c unsetenv HOSTALIASES in -q runs for security
e
s 00001/00000/01866
d D 8.133 95/06/19 07:39:31 eric 482 481
c release HUP signal before re-execing sendmail
e
s 00003/00000/01863
d D 8.132 95/06/18 11:53:18 eric 481 480
c add class `m' to include message subtypes that can be treated
c as though rfc822
e
s 00033/00002/01830
d D 8.131 95/06/17 10:23:35 eric 480 479
c improved debugging
e
s 00001/00001/01831
d D 8.130 95/06/13 09:46:45 eric 479 478
c tweak a couple of #if => #ifdef for compile purposes
e
s 00003/00003/01829
d D 8.129 95/06/13 09:22:45 eric 478 477
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00002/00002/01830
d D 8.128 95/06/12 17:25:57 eric 477 476
c make labels of configuration stuff clearer
e
s 00001/00001/01831
d D 8.127 95/06/11 20:26:32 eric 476 475
c fix buffer overflow -- causes core dumps on some malloc impls
e
s 00015/00013/01817
d D 8.126 95/06/11 09:49:10 eric 475 473
c tweak intro configuration debugging
e
s 00016/00014/01816
d R 8.126 95/06/11 09:48:21 eric 474 473
c tweak initial intro debugging
e
s 00001/00001/01829
d D 8.125 95/06/10 16:07:10 eric 473 472
c use -d99.100 to avoid dropping into background
e
s 00001/00000/01829
d D 8.124 95/06/10 12:38:53 eric 472 471
c count children.  Someday we might reject connections on this basis.
e
s 00001/00000/01828
d D 8.123 95/06/10 11:46:38 eric 471 470
c ignore -t in -bd mode
e
s 00033/00002/01795
d D 8.122 95/06/10 07:37:49 eric 470 469
c print OS compile flags (sigh)
e
s 00004/00003/01793
d D 8.121 95/05/30 19:24:00 eric 469 468
c change RealUserName from an array to a pointer; move defn to sendmail.h
e
s 00001/00001/01795
d D 8.120 95/05/29 15:57:07 eric 468 467
c force -oee to really always return zero
e
s 00001/00003/01795
d D 8.119 95/05/29 09:03:06 eric 467 466
c use wordinclass routine for brevity
e
s 00010/00005/01788
d D 8.118 95/05/28 11:49:15 eric 466 465
c lint
e
s 00001/00000/01792
d D 8.117 95/05/27 09:46:48 eric 465 464
c don't send bounces to postmaster on -bv
e
s 00006/00000/01786
d D 8.116 95/05/27 08:15:39 eric 464 463
c force Prog and File mailers to never have F=m
e
s 00012/00019/01774
d D 8.115 95/05/27 07:45:59 eric 463 462
c clean up test mode; putenv can fail
e
s 00004/00001/01789
d D 8.114 95/05/25 11:37:56 eric 462 461
c preinitialized $=m late, so that .cf can redefined $m
e
s 00001/00001/01789
d D 8.113 95/05/19 17:18:25 eric 461 460
c re-word /mx output to be more precise
e
s 00001/00000/01789
d D 8.112 95/05/19 15:59:11 eric 460 459
c avoid core dump on non-zero-initialized memory
e
s 00006/00004/01783
d D 8.111 95/05/17 09:11:55 eric 459 458
c clean up compile flag output
e
s 00002/00000/01785
d D 8.110 95/05/16 21:08:04 eric 458 457
c vendor hooks (for Sun)
e
s 00001/00001/01784
d D 8.109 95/05/15 16:03:18 eric 457 456
c fix compile problems on Solaris and HP-UX
e
s 00014/00015/01771
d D 8.108 95/05/15 15:38:54 eric 456 455
c improved implementation for E line -- slightly cleaner -- plus
c resulting simplifications in map.c for NIS+
e
s 00064/00027/01722
d D 8.107 95/05/15 15:01:53 eric 455 454
c add "E" line to config file to set or propogate environment
c variables to children
e
s 00003/00000/01746
d D 8.106 95/05/15 07:30:56 eric 454 453
c probe interface configuration for other possible names
e
s 00037/00007/01709
d D 8.105 95/05/11 12:29:35 eric 453 452
c add /try and ${macro} syntaxes to -bt mode; eliminate ?
e
s 00006/00004/01710
d D 8.104 95/04/22 10:53:09 eric 452 451
c fixes to MIME code
e
s 00001/00001/01713
d D 8.103 95/04/21 09:56:52 eric 451 450
c update copyright notice
e
s 00000/00003/01714
d D 8.102 95/04/19 10:36:30 eric 450 449
c need to make ColonOkInAddr do something real
e
s 00001/00000/01716
d D 8.101 95/04/13 14:24:41 eric 449 447
c don't double-initialized aliases on -bs
e
s 00001/00001/01715
d R 8.101 95/04/09 17:41:27 eric 448 447
c clean up group handling for sender & envelope addresses
e
s 00004/00001/01712
d D 8.100 95/04/09 13:46:30 eric 447 446
c fix handling of group phrase: addr1, addr2, ... addrN; syntax
e
s 00004/00000/01709
d D 8.99 95/04/09 11:57:39 eric 446 445
c minor cleanup from last set of changes
e
s 00181/00132/01528
d D 8.98 95/04/08 14:47:31 eric 445 444
c add /mx command to test mode
e
s 00055/00002/01605
d D 8.97 95/04/07 19:20:03 eric 444 443
c portability changes for Sony NEWS stations; print compile flags on -d0
e
s 00001/00001/01606
d D 8.96 95/04/02 09:28:31 eric 443 442
c MIME cleanup to get header line parsing right
e
s 00001/00001/01606
d D 8.95 95/03/31 15:46:43 eric 442 441
c more type hacking for non-Posix/ANSI systems
e
s 00001/00003/01606
d D 8.94 95/03/31 10:51:46 eric 441 440
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00004/00007/01605
d D 8.93 95/03/27 09:25:22 eric 440 439
c more cleanup for DSN drafts
e
s 00007/00002/01605
d D 8.92 95/03/21 16:41:50 eric 439 438
c improved debugging for envelope flags
e
s 00001/00001/01606
d D 8.91 95/03/14 09:10:42 eric 438 437
c change call to expand() to be more rational (and consistent!)
e
s 00006/00000/01601
d D 8.90 95/03/11 18:02:11 eric 437 436
c more MIME cleanup
e
s 00017/00017/01584
d D 8.89 95/03/10 12:21:50 eric 436 435
c improved security when opening files
e
s 00001/00000/01600
d D 8.88 95/03/05 12:21:47 eric 435 434
c add vendor-dependent macro initialization hooks
e
s 00000/00002/01600
d D 8.87 95/03/05 11:57:08 eric 434 432
i 433
c add "strict" parameter to denlstring to allow continuations
e
s 00002/00002/01482
d D 8.55.1.7 95/03/05 10:09:54 eric 433 431
c add concept of "strict adherence" to newline standard
e
s 00000/00000/01600
d D 8.86 95/02/28 15:42:02 eric 432 430
i 431
c incorporate fixes from 8.6.11
e
s 00001/00000/01483
d D 8.55.1.6 95/02/28 15:39:27 eric 431 429
c reset group id on -X flag as well as user id
e
s 00003/00003/01596
d D 8.85 95/02/28 14:43:10 eric 430 427
c incorporate fixes from 8.6.11
e
s 00001/00001/01482
d D 8.55.1.5 95/02/28 14:42:35 eric 429 428
c fix FS= environment bug
e
s 00014/00002/01469
d D 8.55.1.4 95/02/28 10:58:45 eric 428 424
c multiple glitches in 8.6.10 -- see ../RELEASE_NOTES for details
e
s 00001/00001/01598
d D 8.84 95/02/23 15:51:09 eric 427 426
c cleanup to make gcc -Winitialized happier
e
s 00014/00002/01585
d D 8.83 95/02/22 11:03:58 eric 426 425
c be able to use symbolic ruleset names in -bt mode
e
s 00002/00001/01585
d D 8.82 95/02/19 13:25:35 eric 425 423
c simplified implementation of new 'T' line
e
s 00000/00000/01471
d D 8.55.1.3 95/02/10 09:40:43 eric 424 422
i 423
c drat -- another one
e
s 00005/00001/01581
d D 8.81 95/02/10 09:39:49 eric 423 421
c another possible newline.....
e
s 00000/00000/01467
d D 8.55.1.2 95/02/10 09:30:00 eric 422 420
i 421
c more bogus newline deletion
e
s 00001/00001/01581
d D 8.80 95/02/10 09:29:03 eric 421 419
c more security hacking (avoiding bogus newlines in strings)
e
s 00000/00000/01467
d D 8.55.1.1 95/02/10 07:37:41 eric 420 394
i 419
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00019/00005/01563
d D 8.79 95/02/10 07:16:36 eric 419 418
c fix security problem: avoid newlines in command line or IDENT input
e
s 00002/00003/01566
d D 8.78 95/02/06 08:06:27 eric 418 417
c give X-Authentication-Warning: on -f flag unless user is trusted
e
s 00009/00000/01560
d D 8.77 95/01/25 07:37:10 eric 417 416
c pre-initialize name server to avoid trashing _res.retry in
c gethostbyanyaddr
e
s 00001/00003/01559
d D 8.76 95/01/24 08:28:29 eric 416 415
c use wordinclass() abstraction for searching classes
e
s 00035/00009/01527
d D 8.75 95/01/07 10:35:40 eric 415 414
c arrange for "kill -1" to re-exec sendmail
e
s 00000/00002/01536
d D 8.74 95/01/04 16:33:12 eric 414 413
c allow -M to define macros on all architectures (not just Ultrix)
e
s 00003/00000/01535
d D 8.73 94/12/10 12:11:44 eric 413 412
c fix problem with RES_DEBUG setting before res_init()
e
s 00001/00001/01534
d D 8.72 94/12/05 10:05:27 eric 412 411
c do sender logging as early as possible
e
s 00001/00027/01534
d D 8.71 94/11/27 11:20:18 eric 411 410
c improved debugging
e
s 00005/00001/01556
d D 8.70 94/11/25 09:05:54 eric 410 409
c improve DSN handling somewhat + some bug fixes
e
s 00000/00007/01557
d D 8.69 94/10/25 17:19:31 eric 409 408
c compile problems on various platforms
e
s 00004/00002/01560
d D 8.68 94/10/23 14:18:26 eric 408 407
c print mail uid/gid in debugging output
e
s 00056/00004/01506
d D 8.67 94/10/16 09:05:00 eric 407 406
c expand -bt mode some more
e
s 00000/00004/01510
d D 8.66 94/09/09 16:46:57 eric 406 405
c change setproctitle definitions to use SPT_TYPE variable a la
c SFS_TYPE and LA_TYPE; this allows for a cleaner integration of new types
e
s 00008/00004/01506
d D 8.65 94/08/18 06:45:56 eric 405 404
c add -O option to set long option names
e
s 00001/00001/01509
d D 8.64 94/08/17 08:08:58 eric 404 402
c make all flags be printed in hex rather than octal (except file modes)
e
s 00001/00001/01509
d R 8.64 94/08/07 16:31:30 eric 403 402
c allow V7 config files (to make long option names safe)
e
s 00003/00003/01507
d D 8.63 94/07/23 07:59:23 eric 402 401
c MIME 8 to 7 bit support
e
s 00019/00001/01491
d D 8.62 94/07/03 11:47:51 eric 401 400
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00004/00000/01488
d D 8.61 94/07/02 05:53:10 eric 400 399
c don't lose .cf syntax errors when Oem set
e
s 00003/00000/01485
d D 8.60 94/06/25 10:21:07 eric 399 398
c complain if you can't find a fully-qualified host name: too many
c sites get this wrong
e
s 00018/00005/01467
d D 8.59 94/06/20 06:28:22 eric 398 397
c restore -ba mode
e
s 00001/00002/01471
d D 8.58 94/06/17 17:39:49 eric 397 396
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00001/00001/01472
d D 8.57 94/06/17 11:12:43 eric 396 395
c Cray fixes from Eric Wassenaar
e
s 00028/00008/01445
d D 8.56 94/05/15 08:16:33 eric 395 394
c clean up setting of numeric IP addresses (and debug them properly)
e
s 00021/00008/01432
d D 8.55 94/04/15 09:20:13 eric 394 393
c try to catch cases of $j getting munged in daemon process
e
s 00006/00002/01434
d D 8.54 94/04/12 08:38:25 eric 393 392
c updates for Intergraph CLIX
e
s 00001/00001/01435
d D 8.53 94/04/12 08:20:36 eric 392 391
c updates for picky C compilers
e
s 00002/00002/01434
d D 8.52 94/03/11 14:41:56 eric 391 390
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00000/00007/01436
d D 8.51 94/03/08 10:32:13 eric 390 389
c avoid "warning: user foo owned process using -bs" if mail is sent
c from foo
e
s 00001/00001/01442
d D 8.50 94/03/07 10:46:19 eric 389 388
c fix handling of -d command line flag
e
s 00001/00000/01442
d D 8.49 94/02/06 19:28:52 eric 388 387
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00003/00000/01439
d D 8.48 94/02/03 08:07:48 eric 387 386
c restore -ba mode for UK Grey book
e
s 00000/00001/01439
d D 8.47 94/01/15 12:38:47 eric 386 385
c Unicos portability changes
e
s 00014/00007/01426
d D 8.46 94/01/09 11:09:15 eric 385 384
c improve obsolete flag processing -- it choked on new format flags
e
s 00001/00001/01432
d D 8.45 94/01/08 17:29:07 eric 384 383
c fix problem that was causing the ctladdr of whoever ran the daemon
c (usually root) to own the delivery process
e
s 00013/00000/01420
d D 8.44 93/12/15 08:16:50 eric 383 382
c have SIGUSR1 call and print ruleset 89
e
s 00001/00001/01419
d D 8.43 93/12/10 17:46:30 eric 382 381
c add a "recursion level" argument to rewrite() to detect loops politely
e
s 00002/00001/01418
d D 8.42 93/12/10 17:19:56 eric 381 380
c add bufsize parameter to prescan
e
s 00008/00001/01411
d D 8.41 93/12/02 07:29:33 eric 380 379
c print $j and check that $j is in $=w on SIGUSR1
e
s 00023/00000/01389
d D 8.40 93/12/01 14:13:22 eric 379 378
c dump state on SIGUSR1
e
s 00002/00003/01387
d D 8.39 93/11/27 15:05:46 eric 378 377
c minor cleanup of $j definition
e
s 00007/00000/01383
d D 8.38 93/11/27 06:59:45 eric 377 376
c more attempts to catch fd 0/1/2 lossage
e
s 00001/00000/01382
d D 8.37 93/11/14 08:28:07 eric 376 375
c set $=k as documented
e
s 00013/00006/01369
d D 8.36 93/11/12 12:52:32 eric 375 374
c add null -O flag for NeXT -- Mail.app uses this, but why?
e
s 00001/00001/01374
d D 8.35 93/11/08 14:25:56 eric 374 373
c add argc & argv to init_md call to enhance extensibility
e
s 00002/00000/01373
d D 8.34 93/11/08 14:24:18 eric 373 372
c debug output (uname failures)
e
s 00015/00002/01358
d D 8.33 93/10/24 10:34:00 eric 372 371
c fix possible core dump in -bt mode
e
s 00002/00000/01358
d D 8.32 93/10/23 12:45:27 eric 371 370
c open file debugging
e
s 00002/00000/01356
d D 8.31 93/10/21 07:19:13 eric 370 369
c drop X-Authentication-Warning: about using -f for the time being
e
s 00018/00006/01338
d D 8.30 93/10/15 08:34:28 eric 369 368
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00003/00000/01341
d D 8.29 93/10/08 15:54:35 eric 368 367
c 8.6.1: A/UX and Encore UMAX V patches; fix to not toss error messages
c too early
e
s 00002/00001/01339
d D 8.28 93/09/25 07:24:51 eric 367 366
c fix problem when 0, 1, or 2 are closed when sendmail starts up
e
s 00002/00001/01338
d D 8.27 93/09/22 09:02:55 eric 366 365
c get sendmail.cf name from a routine (so it can autoconfigure on NeXt)
e
s 00004/00000/01335
d D 8.26 93/09/04 11:50:48 eric 365 364
c more attempts to find the fd 1 closed error
e
s 00002/00002/01333
d D 8.25 93/08/22 17:07:44 eric 364 363
c add restrictqrun privacy option
e
s 00012/00004/01323
d D 8.24 93/08/21 16:36:44 eric 363 362
c include other legal short names in the $=w class, e.g., vangogh.cs
e
s 00006/00025/01321
d D 8.23 93/08/20 11:51:56 eric 362 361
c more on elimination of frozen config files
e
s 00005/00216/01341
d D 8.22 93/08/20 08:17:07 eric 361 360
c delete FROZENCONFIG support
e
s 00003/00001/01554
d D 8.21 93/08/19 14:52:47 eric 360 359
c improved debugging
e
s 00010/00009/01545
d D 8.20 93/08/17 09:50:48 eric 359 358
c use xputs instead of printf for macro values
e
s 00014/00004/01540
d D 8.19 93/08/16 15:24:30 eric 358 357
c fix $w setting to be true short name
e
s 00012/00004/01532
d D 8.18 93/08/15 08:39:04 eric 357 356
c predefine $e, $l, $n, $o, and $q
e
s 00018/00016/01518
d D 8.17 93/08/15 08:08:39 eric 356 355
c change $w default on config level 5
e
s 00000/00009/01534
d D 8.16 93/08/08 15:08:07 eric 355 354
c POSIX and Linux changes
e
s 00001/00001/01542
d D 8.15 93/08/07 11:57:49 eric 354 353
c don't chdir(QueueDir) in -bt mode
e
s 00006/00003/01537
d D 8.14 93/08/06 21:16:46 eric 353 352
c fix problem causing slow delivery warning to fail if OP set;
c fstat can return -1 on some bizarre networks
e
s 00004/00001/01536
d D 8.13 93/07/29 08:31:01 eric 352 351
c make certain that $j is part of $=w
e
s 00019/00007/01518
d D 8.12 93/07/27 21:36:19 eric 351 350
c fix statistics gathering; NeXT portability
e
s 00009/00010/01516
d D 8.11 93/07/26 09:21:54 eric 350 349
c signal and file locking portability changes
e
s 00011/00005/01515
d D 8.10 93/07/23 10:14:25 eric 349 348
c fix non-return of addresses presented on the command line
e
s 00000/00009/01520
d D 8.9 93/07/22 11:06:32 eric 348 347
c fix problem causing bogus delivery of SIGTTIN on POSIX systems
e
s 00001/00013/01528
d D 8.8 93/07/20 15:35:39 eric 347 346
c more portability changes, including ConvexOS support
e
s 00009/00002/01532
d D 8.7 93/07/19 16:30:45 eric 346 345
c include M flag on Ultrix for DECnet compatibility
e
s 00000/00003/01534
d D 8.6 93/07/19 11:30:36 eric 345 344
c HASSETEUID => HASSETREUID and changes to avoid having to do
c setuid(getuid()) in main.
e
s 00015/00000/01522
d D 8.5 93/07/18 14:47:46 eric 344 343
c write command line information in pid file
e
s 00029/00020/01493
d D 8.4 93/07/16 10:33:15 eric 343 342
c global error handling; fix problem leaving incoming SMTP connection
c in FIN_WAIT_2 for extended periods; bug in -X setvbuf call
e
s 00026/00010/01487
d D 8.3 93/07/13 12:58:18 eric 342 341
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00031/00012/01466
d D 8.2 93/07/11 06:52:24 eric 341 340
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00005/00005/01473
d D 8.1 93/06/07 10:30:41 bostic 340 339
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01477
d D 6.70 93/06/05 17:07:45 eric 339 338
c lint-style cleanup
e
s 00005/00005/01473
d D 6.69 93/05/30 08:55:27 eric 338 337
c set RES_DEBUG earlier
e
s 00002/00002/01476
d D 6.68 93/05/28 07:00:39 eric 337 336
c change alias initialization to general map initialization
e
s 00000/00006/01478
d D 6.67 93/05/27 11:37:10 eric 336 335
c prototype functions
e
s 00001/00000/01483
d D 6.66 93/05/24 08:33:45 eric 335 334
c declare macvalue
e
s 00000/00001/01483
d D 6.65 93/05/22 08:57:53 eric 334 333
c AIX compatibility changes; clean up map initialization functions
e
s 00002/00002/01482
d D 6.64 93/05/17 10:56:10 eric 333 332
c type conflicts
e
s 00001/00001/01483
d D 6.63 93/05/13 10:40:55 eric 332 331
c log sendmail version during SMTP startup
e
s 00005/00001/01479
d D 6.62 93/05/06 10:24:24 eric 331 330
c fix bug causing mail to be returned in -bv mode
e
s 00002/00002/01478
d D 6.61 93/05/03 12:26:15 eric 330 329
c first cut at updated alias implementation
e
s 00001/00001/01479
d D 6.60 93/04/30 12:54:03 eric 329 328
c don't change alpha case on header field names
e
s 00000/00001/01480
d D 6.59 93/04/27 18:51:33 eric 328 327
c move #include <sys/stat.h> into conf.h
e
s 00000/00004/01481
d D 6.58 93/04/26 16:08:40 eric 327 326
c clean up setsid handling
e
s 00011/00001/01474
d D 6.57 93/04/18 10:07:13 eric 326 325
c Extended Load Average (XLA) hooks
e
s 00006/00002/01469
d D 6.56 93/04/15 07:41:12 eric 325 324
c add e_bodytype and B queue line and -B flag for body type information
e
s 00006/00001/01465
d D 6.55 93/04/14 14:38:35 eric 324 323
c return status information from map lookups and from there from 
c rewrite; this allows higher level code to queue if the name server is down
e
s 00010/00003/01456
d D 6.54 93/04/10 09:28:23 eric 323 322
c implement $&x for deferred macro expansion; some POSIX compatibility
e
s 00002/00000/01457
d D 6.53 93/04/04 16:03:18 eric 322 321
c IDENT cleanup; move loopback checking from srvr to user smtp
e
s 00018/00013/01439
d D 6.52 93/04/04 13:56:51 eric 321 320
c RFC 1413 (IDENT) protocol support
e
s 00002/00002/01450
d D 6.51 93/04/01 14:59:11 eric 320 319
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00004/00003/01448
d D 6.50 93/03/30 12:30:57 eric 319 318
c don't give a warning if -f is being used to set id to yourself
e
s 00001/00001/01450
d D 6.49 93/03/29 12:42:22 eric 318 317
c make heuristic on when -d doesn't have an argument more like old
c behaviour
e
s 00001/00001/01450
d D 6.48 93/03/26 08:13:50 eric 317 316
c simplify content of X-Authentication-Warning: header
e
s 00001/00001/01450
d D 6.47 93/03/26 07:45:02 eric 316 315
c portability
e
s 00003/00002/01448
d D 6.46 93/03/25 14:27:05 eric 315 314
c define $=w to include long host name
e
s 00002/00001/01448
d D 6.45 93/03/23 19:50:42 eric 314 313
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00114/00049/01335
d D 6.44 93/03/23 18:06:26 eric 313 312
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00015/00015/01369
d D 6.43 93/03/19 08:50:41 eric 312 311
c move SendMode and ErrorMode into the envelope
e
s 00000/00001/01384
d D 6.42 93/03/18 19:37:50 eric 311 310
c avoid extra unnecessary creation of queue files solely for an
c unneeded id
e
s 00011/00002/01374
d D 6.41 93/03/18 11:11:31 eric 310 309
c OSF/1 on Alpha portability enhancements
e
s 00001/00001/01375
d D 6.40 93/03/18 10:56:14 eric 309 308
c restore e_sender as sending address sans decorations
e
s 00008/00002/01368
d D 6.39 93/03/17 10:35:17 eric 308 307
c attempts to handle ENFILE conditions better
e
s 00003/00002/01367
d D 6.38 93/03/17 09:55:12 eric 307 306
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00013/00010/01356
d D 6.37 93/03/16 18:06:08 eric 306 305
c pass envelope to disconnect to avoid another use of CurEnv; make
c disconnect more POSIXish
e
s 00001/00001/01365
d D 6.36 93/03/05 08:35:37 eric 305 304
c fix daemon startup log message
e
s 00011/00009/01355
d D 6.35 93/03/04 22:25:58 eric 304 303
c set RealHostName under all circumstances
e
s 00004/00000/01360
d D 6.34 93/03/04 08:03:31 eric 303 302
c exit on bad parameters
e
s 00000/00012/01360
d D 6.33 93/03/03 15:18:13 eric 302 301
c don't write PidFile until we are actually about ready to accept
c connections
e
s 00004/00004/01368
d D 6.32 93/03/01 12:43:45 eric 301 300
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00000/00001/01372
d D 6.31 93/03/01 06:53:30 eric 300 299
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00018/00001/01355
d D 6.30 93/02/28 18:43:29 eric 299 298
c allow command line limitations to individual queue runs
e
s 00010/00000/01346
d D 6.29 93/02/28 11:03:06 eric 298 297
c changes for better logging of mail submitters
e
s 00017/00000/01329
d D 6.28 93/02/28 09:46:39 eric 297 296
c log daemon startup
e
s 00022/00001/01307
d D 6.27 93/02/26 08:18:14 eric 296 295
c require FROZENCONFIG compile flag to get frozen config code
e
s 00002/00002/01306
d D 6.26 93/02/24 10:19:21 eric 295 294
c fix yet another problem with new owner-foo implementation
e
s 00001/00018/01307
d D 6.25 93/02/22 16:59:05 eric 294 293
c delete -R flag (RcptLogFile handling)
e
s 00001/00001/01324
d D 6.24 93/02/21 14:59:52 eric 293 292
c use 022 as default umask
e
s 00003/00000/01322
d D 6.23 93/02/21 14:34:39 eric 292 291
c ignore process group signals -- some front ends screw this up
e
s 00001/00001/01321
d D 6.22 93/02/21 12:44:20 eric 291 290
c insist on level 4 config file to send errors from <>
e
s 00012/00004/01310
d D 6.21 93/02/20 13:46:28 eric 290 289
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00001/00001/01313
d D 6.20 93/02/19 10:35:21 eric 289 288
c fix glitch with \001 => \201 changes
e
s 00001/00001/01313
d D 6.19 93/02/19 09:21:26 eric 288 287
c fix a variety of bugs found by Eric Wassenaar <e07@nikhef.nl>
e
s 00002/00002/01312
d D 6.18 93/02/18 20:22:14 eric 287 286
c move the meta-characters from C0 into C1 space
e
s 00006/00004/01308
d D 6.17 93/02/18 15:12:18 eric 286 285
c change -bt so that -v always prints prompts
e
s 00005/00005/01307
d D 6.16 93/02/16 18:29:43 eric 285 284
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00010/00002/01302
d D 6.15 93/02/14 14:41:31 eric 284 283
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00017/00015/01287
d D 6.14 93/02/12 11:51:11 eric 283 282
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00001/00002/01301
d D 6.13 93/01/28 17:04:48 eric 282 281
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00007/00000/01296
d D 6.12 93/01/28 10:15:41 eric 281 280
c System 5 compatibility, misc fixes
e
s 00005/00000/01291
d D 6.11 93/01/26 11:36:27 eric 280 279
c some (iffy) changes to prevent suppressing the actual sender
c during a queue run (interaction with C line in qf file)
e
s 00005/00002/01286
d D 6.10 93/01/22 17:20:11 eric 279 278
c fix -e compat flag; a few compilation warnings; improve error messages
e
s 00018/00001/01270
d D 6.9 93/01/21 15:18:30 eric 278 277
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00014/00000/01257
d D 6.8 93/01/20 13:21:41 eric 277 276
c fix problem with address delimitor inside quotes; define $k and $=k
c to be the name (from the uname call)
e
s 00006/00002/01251
d D 6.7 93/01/18 14:32:14 eric 276 275
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00000/00014/01253
d D 6.6 93/01/13 18:38:07 eric 275 274
c environment handling simplification/bug fix; handle commas inside
c comments; properly limit large messages in -obq mode
e
s 00022/00002/01245
d D 6.5 93/01/10 14:26:40 eric 274 273
c jgm+@CMU.EDU: check mtime of thaw file against .cf and sendmail binary
e
s 00015/00001/01232
d D 6.4 93/01/02 13:59:55 eric 273 272
c changes to recognize special mailer types (e.g., file) early
e
s 00000/00003/01233
d D 6.3 93/01/01 13:30:03 eric 272 271
c fix botch in invalidaddr() routine
e
s 00009/00000/01227
d D 6.2 93/01/01 13:07:51 eric 271 270
c report wierd characters in -bt mode
e
s 00000/00000/01227
d D 6.1 92/12/21 16:08:13 eric 270 269
c Release 6
e
s 00010/00004/01217
d D 5.64 92/12/20 11:47:37 eric 269 268
c bug fixes for getopt changes
e
s 00023/00039/01198
d D 5.63 92/12/20 11:12:45 eric 268 266
i 267
c getopt-ify it
e
s 00108/00085/01129
d D 5.62.1.1 92/12/19 15:10:07 bostic 267 266
c first pass at a getopt interface
e
s 00008/00002/01206
d D 5.62 92/12/15 17:17:27 eric 266 265
c restore # as comment symbol in .forward/:include:; extend -p flag;
c remove = option (use V instead)
e
s 00012/00000/01196
d D 5.61 92/12/15 13:43:37 eric 265 264
c sendmail -p sets protocol
e
s 00001/00004/01195
d D 5.60 92/11/16 17:52:12 eric 264 263
c make it use varargs/stdarg and vsprintf
e
s 00017/00017/01182
d D 5.59 92/11/14 11:34:06 eric 263 262
c (partially) ANSI-fy it
e
s 00012/00003/01187
d D 5.58 92/11/06 11:28:00 eric 262 261
c some debugging hooks for -bt mode
e
s 00002/00001/01188
d D 5.57 92/09/23 15:04:25 eric 261 260
c fix bug in envp handling in main(); always put trailing dot on
c results of MX lookups
e
s 00010/00003/01179
d D 5.56 92/09/22 16:40:20 eric 260 259
c a variety of bug minor bug fixes; add file locking when writing
c to a UNIX file; strip out dangerous envariables
e
s 00002/00002/01180
d D 5.55 92/07/20 08:02:52 eric 259 258
c portability changes
e
s 00016/00014/01166
d D 5.54 92/07/19 10:19:56 eric 258 257
c fix bogus envelope problem in clock-driven queue runs; misc. fixes
e
s 00010/00010/01170
d D 5.53 92/07/12 14:09:31 eric 257 256
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00007/00004/01173
d D 5.52 92/07/12 11:57:30 eric 256 255
c child pid not getting changed; \quoted names were still forwarded
e
s 00009/00002/01168
d D 5.51 92/07/12 06:59:37 eric 255 254
c security hacks: make F .cf line a little more careful; don't
c close more than 256 files
e
s 00017/00003/01153
d D 5.50 92/07/11 18:51:32 eric 254 253
c open connection caching
e
s 00007/00005/01149
d D 5.49 92/05/25 13:13:25 eric 253 252
c add generalized database mapping (using the K config line and
c $( ... $) syntaxes); $[ ... $] is now a special case
e
s 00006/00001/01148
d D 5.48 92/05/06 08:56:59 eric 252 251
c use putenv (Sys 5 standard) instead of setenv (completely nonstandard)
e
s 00001/00001/01148
d D 5.47 92/04/16 18:40:10 eric 251 250
c try to eliminate some of the CurEnv globals
e
s 00007/00000/01142
d D 5.46 92/03/20 20:54:22 eric 250 249
c check for configuration level higher than we understand
e
s 00014/00002/01128
d D 5.45 92/02/21 20:57:42 eric 249 248
c from Bryan Costales: several smallish changes, mostly to clean
c up debugging output.  The major change is that test mode (-bt)
c doesn't automatically run through ruleset three any more.
e
s 00001/00002/01129
d D 5.44 92/01/18 07:57:14 eric 248 247
c drop mode a (ARPA FTP) -- NCP is gone forever.....
e
s 00005/00000/01126
d D 5.43 92/01/05 09:21:30 eric 247 246
c clean up #ifdef configuration to more cleanly match the modern age
e
s 00005/00004/01121
d D 5.42 92/01/04 15:32:55 eric 246 245
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00005/00000/01120
d D 5.41 91/12/21 10:30:17 eric 245 244
c don't set FullName in daemon run
e
s 00027/00001/01093
d D 5.40 91/12/20 20:01:20 eric 244 243
c add -R flag to log incoming raw recipients for analysis
e
s 00002/00000/01092
d D 5.39 91/12/13 14:54:22 eric 243 242
c some System V hacks....
e
s 00002/00001/01090
d D 5.38 91/12/12 11:42:12 eric 242 241
c define $m macro to have the domain part of $w
e
s 00002/00004/01089
d D 5.37 91/11/22 13:54:54 eric 241 240
c don't complain if sendmail.fc doesn't exist (this is not an error)
e
s 00000/00006/01093
d D 5.36 91/11/20 18:26:08 eric 240 239
c from costales@icsi.Berkeley.EDU: print rulesets with symbolic name
c instead of control characters; allow # comments in :include: files
e
s 00010/00000/01089
d D 5.35 91/10/03 01:45:41 eric 239 238
c when initializing the $=w class, make sure it is only one word --
c otherwise it will never match
e
s 00016/00002/01073
d D 5.34 91/10/02 13:21:19 eric 238 237
c check to see if hostname has changed in thaw(); if it has, ignore
c the frozen config (with the wrong hostname)
e
s 00005/00003/01070
d D 5.33 91/07/26 14:59:35 eric 237 236
c fix setting of RES_DEBUG option
e
s 00002/00001/01071
d D 5.32 91/03/02 17:15:24 bostic 236 235
c ANSI
e
s 00001/00001/01071
d D 5.31 90/07/20 14:18:56 bostic 235 234
c added field name q_ruser; need to update NullAddress
e
s 00007/00002/01065
d D 5.30 90/06/29 20:49:34 karels 234 233
c use daemon() call
e
s 00001/00011/01066
d D 5.29 90/06/01 19:02:19 bostic 233 232
c new copyright notice
e
s 00004/00006/01073
d D 5.28 90/04/18 15:53:06 bostic 232 231
c thaw() needs OutChannel if an error occurs
e
s 00017/00007/01062
d D 5.27 90/04/16 08:05:22 rick 231 230
c complain if cant use frozen config file
e
s 00004/00002/01065
d D 5.26 89/01/24 21:43:12 bostic 230 229
c ifdef openlog for 4.2BSD systems
e
s 00000/00016/01067
d D 5.25 89/01/01 17:17:23 bostic 229 228
c remove DEBUG
e
s 00001/00001/01082
d D 5.24 88/12/05 20:04:11 bostic 228 227
c minor cleanups for cray
e
s 00012/00001/01071
d D 5.23 88/11/18 16:32:16 karels 227 226
c disallow non-root from starting daemon or queue mode;
c unset HOSTALIASES for daemon or queue mode
e
s 00018/00010/01054
d D 5.22 88/11/17 22:02:21 karels 226 225
c more cleanup, fix some inappropriate syserr's
e
s 00002/00000/01062
d D 5.21 88/09/20 23:45:13 eric 225 224
c some cleanup of I option handling
e
s 00001/00000/01061
d D 5.20 88/09/20 18:20:20 bostic 224 223
c needs sys/files.h noww
e
s 00002/00002/01059
d D 5.19 88/07/15 09:22:18 bostic 223 222
c we know how many file descriptors are available now
e
s 00011/00009/01050
d D 5.18 88/06/30 14:59:09 bostic 222 221
c install approved copyright notice
e
s 00010/00014/01049
d D 5.17 88/04/19 13:39:51 bostic 221 220
c add RES_DEBUG to res.options if debug flag set
e
s 00000/00002/01063
d D 5.16 88/04/01 16:50:49 bostic 220 219
c remove V6 #ifdefs
e
s 00018/00012/01047
d D 5.15 88/03/13 19:52:17 bostic 219 218
c add Berkeley specific header
e
s 00001/00001/01058
d D 5.14 87/12/21 11:56:51 bostic 218 217
c make ANSI C compatible
e
s 00003/00000/01056
d D 5.13 87/03/24 09:11:39 bostic 217 216
c always uses local time
e
s 00004/00000/01052
d D 5.12 86/10/14 17:21:05 eric 216 215
c make sure that 0, 1, and 2 are open to avoid confusing syslog;
c from Steve Schoch <schoch@orion.arpa>
e
s 00025/00005/01027
d D 5.11 86/01/30 11:01:28 eric 215 214
c fix .forward files that include yourself; this was a bug in sameaddr
c that may have caused some other problems
e
s 00004/00001/01028
d D 5.10 85/12/07 08:16:38 eric 214 212
m 
c several small bugs: don't die if no environment, don't look in
c ESM_DEADLETTER state in savemail; lowercase before getpwnam to
c allow upper case regular names in alias file
e
s 00002/00002/01027
d D 5.9.1.1 85/11/18 20:16:53 eric 213 212
m 
c attempt at clearing header in error envelopes
e
s 00002/00002/01027
d D 5.9 85/09/30 21:34:12 eric 212 211
m 
c clean up some aspects of error message display
e
s 00013/00010/01016
d D 5.8 85/09/24 15:09:36 eric 211 210
m 
c don't step on user environment
e
s 00007/00000/01019
d D 5.7 85/09/19 13:35:35 eric 210 209
m 
c lint
e
s 00000/00001/01019
d D 5.6 85/09/19 01:25:19 eric 209 207
i 208
m 
c incorporate SMI changes -- still experimental
e
s 00041/00006/00978
d D 5.4.1.1 85/09/19 00:55:29 eric 208 206
m 
c SMI changes (somewhat)
e
s 00001/00001/00983
d D 5.5 85/09/17 19:21:46 eric 207 206
m 
c facilities in syslog
e
s 00008/00003/00976
d D 5.4 85/06/08 10:27:36 eric 206 205
m 
c lint for 4.3 release
e
s 00012/00012/00967
d D 5.3 85/06/08 00:04:51 eric 205 204
m 
c lint
e
s 00000/00002/00979
d D 5.2 85/06/07 22:12:19 miriam 204 203
m 
c Resolve duplicate SccsId
e
s 00020/00000/00961
d D 5.1 85/06/07 16:01:45 dist 203 202
m 
c Add copyright
e
s 00002/00004/00959
d D 4.18 85/05/24 10:55:57 eric 202 201
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00003/00003/00960
d D 4.17 85/04/09 14:12:03 ralph 201 200
m 
c fix order of setgid's, openlog has three arguments.
e
s 00007/00008/00956
d D 4.16 85/02/15 09:26:47 eric 200 199
m 
c fix some bugs with -C flag; one with queuing from Teus
e
s 00017/00018/00947
d D 4.15 84/12/05 23:14:27 eric 199 198
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00005/00003/00960
d D 4.14 84/08/11 23:18:17 eric 198 197
m 
c Add $[ and $] as RHS operators to look up the contents and pass them
c to maphostname; maphostname currently looks them up in /etc/hosts and
c converts them to canonical form, but could be turned into a general
c name server.....   huzzah!!
e
s 00005/00002/00958
d D 4.13 84/08/11 18:59:58 eric 197 196
m 
c define external representations of hostname lookup characters
e
s 00006/00005/00954
d D 4.12 84/08/11 17:48:04 eric 196 195
m 
c Assorted changes from Guy Harris <rlgvax!guy>: mostly lint & USG
e
s 00002/00002/00957
d D 4.11 84/08/11 16:50:29 eric 195 194
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00005/00000/00954
d D 4.10 84/08/05 10:03:41 eric 194 192
m 
c alway reset uid and gid immediately if alternate config file
e
s 00001/00000/00954
d D 4.9.1.1 84/06/17 16:17:15 eric 193 192
m 
c abortive attempt to install a name server.... sigh.
e
s 00001/00001/00953
d D 4.9 84/03/17 16:23:51 eric 192 191
m 
c fix usage message
e
s 00001/00001/00953
d D 4.8 84/03/11 16:52:59 eric 191 190
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00002/00001/00952
d D 4.7 83/12/27 22:49:42 eric 190 189
m 
c don't close files immediately before exec of mailer so that we can log;
c use FIOCLEX instead.  Suggested by Tom Ferrin, UCSF CGL.
e
s 00018/00015/00935
d D 4.6 83/11/10 09:05:11 eric 189 188
m 
c Be able to override the hostname in the configuration file when frozen
e
s 00017/00009/00933
d D 4.5 83/10/16 16:07:08 eric 188 187
m 
c Postpone opening the alias DBM file until after the fork in srvrsmtp so
c that the alias database is as current as possible; thanks to dagobah!efo
c (Eben Ostby) for this one.
e
s 00006/00001/00936
d D 4.4 83/10/02 15:31:18 eric 187 186
m 
c Use old environment after the thaw; credit rhc for this.
e
s 00005/00000/00932
d D 4.3 83/09/05 15:02:08 eric 186 185
m 
c Fix security hole caused by being able to freeze the configuration
c without owning the .fc file.
e
s 00001/00001/00931
d D 4.2 83/08/28 14:43:27 eric 185 184
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00000/00000/00932
d D 4.1 83/07/25 19:44:08 eric 184 183
m 
c 4.2 release version
e
s 00001/00001/00931
d D 3.160 83/05/07 11:27:43 eric 183 182
m 237
c Pass the size of the buffer to myhostname.
e
s 00002/00001/00930
d D 3.159 83/04/30 15:12:19 eric 182 181
m 
c lint
e
s 00001/00000/00930
d D 3.158 83/04/17 17:14:18 eric 181 180
m 221
c fix bogus errno problems
e
s 00002/00000/00928
d D 3.157 83/03/07 09:57:14 eric 180 179
m 203
c Don't pass EX_TEMPFAIL code out (since we have already taken responsibility
c for delivering the message anyway).
e
s 00010/00000/00918
d D 3.156 83/02/03 10:28:42 eric 179 178
m 160
c $e macro is now SMTP entry message (so that configuration version can
c be included).
e
s 00003/00002/00915
d D 3.155 83/02/03 07:52:52 eric 178 177
m 168
c Make mailer size limits a per-mailer parameter (M field in the mailer
c descriptor)
e
s 00016/00006/00901
d D 3.154 83/02/02 12:51:12 eric 177 176
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00005/00000/00902
d D 3.153 83/02/01 20:46:31 eric 176 175
m 166
c don't call printqueue() if queueing is turned off
e
s 00004/00000/00898
d D 3.152 83/01/17 21:40:26 eric 175 174
m 158
c Set the $w macro to the hostname if at all possible to allow generic
c configuration tables.
e
s 00005/00002/00893
d D 3.151 83/01/16 13:12:51 eric 174 173
m 152
c Change mailer spec to have labelled fields for future expansion.
c **** This delta invalidates previous configuration files ****
e
s 00015/00029/00880
d D 3.150 83/01/06 18:08:23 eric 173 172
m 
c fix a botch in argument processing such that it used the last flag as
c a recipient if there were no other recipients (e.g., with "-t")
e
s 00016/00007/00893
d D 3.149 83/01/04 18:51:20 eric 172 171
m 
c Don't try to drop our controlling TTY except when we are starting up a
c daemon; this can cause UUCP jobs to hang waiting for carrier on a dialin
c line (completely contrary to the intent).  Many thanks to Keith Sklower
c for pointing this one out.  However, that damned parameter to disconnect()
c has reappeared!
e
s 00001/00000/00899
d D 3.148 83/01/04 17:44:12 eric 171 170
m 
c Ignore SIGPIPE early (in main rather than in deliver) so that rude hosts
c that close the connection early don't cause us to die -- in particular,
c CMU-CS-A (nee CMU-10A) was doing this after the DATA command; the problem
c went away quite mysteriously, so I have no idea why it happened
e
s 00008/00000/00891
d D 3.147 82/12/30 16:56:31 eric 170 169
m 113
c close files 3 through 20 before startup to insure sufficient resources
e
s 00033/00011/00858
d D 3.146 82/12/14 19:22:52 eric 169 168
m 106
c fix freeze mode to do something more interesting that refreezing (over
c and over and over and .......)
e
s 00011/00004/00858
d D 3.145 82/12/14 16:56:08 eric 168 167
m 105
c Add "print mail queue" mode (-bp flag or call as "mailq")
e
s 00001/00000/00861
d D 3.144 82/12/09 11:16:33 eric 167 166
m 095
c be able to match the inverse of a class using the $~x syntax
e
s 00010/00609/00851
d D 3.143 82/12/05 13:43:45 eric 166 165
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00020/00020/01440
d D 3.142 82/11/28 10:21:04 eric 165 164
m 
c fix a number of problems left over from yesterday's delta.  The big
c triumph is being able to delete the parameter from disconnect().
e
s 00199/00289/01261
d D 3.141 82/11/28 00:16:56 eric 164 163
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00005/00006/01545
d D 3.140 82/11/24 18:42:34 eric 163 162
m 
c lint it
e
s 00116/00058/01435
d D 3.139 82/11/24 17:13:31 eric 162 161
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00035/00017/01458
d D 3.138 82/11/21 17:18:18 eric 161 160
m 026
c preliminary hacks for multiple SMTP transactions per connection: make
c assignment of multiple queue id's more efficient, make prefixes two
c characters (e.g., qfAA99999), pass the file name to freeze and thaw,
c add a mailer flag saying we are talking to one of our own kind.
e
s 00001/00001/01474
d D 3.137 82/11/18 21:32:49 eric 160 159
m 080
c Correctly run "sendmail -q" (had a reversed condition on QueueIntvl)
e
s 00061/00012/01414
d D 3.136 82/11/18 08:54:56 eric 159 158
m 060,
m 073
c disconnect input, output, signals, etc. when running in background
e
s 00012/00012/01414
d D 3.135 82/11/17 10:19:20 eric 158 157
m 060
c fix botch in daemon code (it only ran the queue)
e
s 00053/00082/01373
d D 3.134 82/11/17 09:33:08 eric 157 156
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00001/00000/01454
d D 3.133 82/11/14 15:34:22 eric 156 155
m 075
c Explicitly inherit e_oldstyle from BlankEnvelope to MainEnvelope
e
s 00026/00017/01428
d D 3.132 82/11/13 17:59:55 eric 155 154
m 069
c clean up argument structure -- put -I and -Z on options.  Add a
c "-bp" option to (eventually) print the queue.  If called as "mailq"
c assume "-bp"; if called as "newaliases", assume "-bi"
e
s 00001/00001/01444
d D 3.131 82/11/07 16:13:12 eric 154 153
m 041
c make all mailer output go to the transcript if running server smtp; this
c has the effect of making some significant changes in the output structure
c to handle such things as -em and -as together
e
s 00170/00041/01275
d D 3.130 82/11/05 13:11:38 eric 153 152
m 062
c arrange to freeze the configuration file for quick startup -- this
c technique requires reprocessing the argv so that flag settings don't
c get lost, and is really rather of a hack.
e
s 00024/00003/01292
d D 3.129 82/11/04 15:21:39 eric 152 151
m 019
c don't unlink qf & df files on ^C
e
s 00028/00008/01267
d D 3.128 82/11/04 13:26:00 eric 151 150
m 037
c put header conditionals into the .cf file
e
s 00002/00002/01273
d D 3.127 82/11/03 10:28:45 eric 150 149
m 058
c Put temporary file mode on the F option
e
s 00035/00011/01240
d D 3.126 82/10/16 15:24:22 eric 149 148
m 027
c Put list of login names able to use -f in the .cf file.
e
s 00004/00000/01247
d D 3.125 82/10/16 13:21:48 eric 148 147
m 010
c Arrange for MD_FORK to work well with -v so that we can use it as the
c default.  This was really a separate bug, but I have just lumped it in
c here -- the problem came up with stty tostop.
e
s 00006/00001/01241
d D 3.124 82/10/13 21:54:34 eric 147 146
m 023
c Don't interrupt the process doing accepts (have a separate process
c running the queue) to avoid a large pile of 4.1[abc] bugs.  When
c something more stable comes out, I will change this.
e
s 00003/00001/01239
d D 3.123 82/10/11 09:50:30 eric 146 145
m 016
c have auto-queueups print a polite message in the log (rather than an
c obnoxious "Temporary Failure").  Adds a new routine "logdelivery".
e
s 00015/00000/01225
d D 3.122 82/10/09 18:08:32 eric 145 144
m 013
c print a status indication when a message is autoqueued, either from
c a -bq flag or a NoConnect
e
s 00016/00012/01209
d D 3.121 82/10/09 09:03:00 eric 144 143
m 001
c Extend test mode to be able to handle multiple addresses, etc.; this lets
c me test forward-path specs more easily
e
s 00013/00002/01208
d D 3.120 82/10/07 00:08:31 eric 143 142
c allow passing through multiple rewriting sets in test mode
e
s 00031/00000/01179
d D 3.119 82/10/06 22:53:19 eric 142 140
c add test mode (MD_TEST, -bt)
e
s 00031/00000/01179
d R 3.119 82/10/06 11:43:32 eric 141 140
c add test mode (MD_TEST, -bt)
e
s 00047/00166/01132
d D 3.118 82/09/26 17:02:56 eric 140 139
c Put more configuration into setoption; merge some of the argv processing
c with this; move configuration information out of conf.c into the .cf
c file.  Since a lot of stuff will default to zero, a new .cf file is
c required.
e
s 00027/00011/01271
d D 3.117 82/09/26 14:44:39 eric 139 138
c completely instantiate queue files for all mail, even if not needed;
c fix a bug that would probably come up once every ten years in creating
c the queue id.  should merge argv flag processing with option processing.
e
s 00027/00007/01255
d D 3.116 82/09/24 19:38:44 eric 138 137
c change option implementation; define a bunch of interesting options.
e
s 00000/00005/01262
d D 3.115 82/09/24 09:34:49 eric 137 136
c arrange to be able to define options; put precedences in .cf file;
c send errors to an Errors-To: field; fix a serious bug causing mail
c to not be delivered to anyone if there were any errors.
e
s 00001/00001/01266
d D 3.114 82/09/22 10:50:05 eric 136 135
c don't put commas in non-address fields; have -bq clean up its temp files
e
s 00020/00018/01247
d D 3.113 82/09/12 16:42:19 eric 135 134
c change inheritance for macros in envelopes; be able to canonicalize
c non-domained names by appending domain from sender; call ruleset 3
c explicitly before doing other rulesets; some general cleanup.
e
s 00035/00030/01230
d D 3.112 82/09/11 17:17:50 eric 134 133
c don't assign $s to be the sending host (this mucks up Received:
c lines) -- instead just use HELO messages; chdir into queue directory
c and make all pathnames relative; be more conservative in creating
c queue id's -- in the event you get file table overflows, etc.
e
s 00014/00011/01246
d D 3.111 82/09/08 22:12:33 eric 133 132
c fix a nasty botch in 3.194 that killed SMTP in daemon mode.   sigh......
e
s 00013/00001/01244
d D 3.110 82/09/08 21:17:45 eric 132 131
c try to avoid "Interrupted system call" on wait in deliver and on
c writes; fix returned message to have proper sender; handle extra
c mailer output more cleverly.
e
s 00001/00001/01244
d D 3.109 82/09/06 17:13:41 eric 131 130
c increase log level needed to print "entered" message.
e
s 00001/00001/01244
d D 3.108 82/09/06 16:23:20 eric 130 129
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00013/00008/01232
d D 3.107 82/09/05 18:08:15 eric 129 128
c change $g processing from a macro substitution per mailer to two sets
c of rewriting rules per mailer -- one each for sender and recipient
c fields; convert to NBS standard on Return-Receipt-To: and Precedence:
c fields; clean up From: processing code and generalize it to all
c sender fields; tune debugging code; clean up canonname.
c **** This delta invalidates previous configuration files ****
e
s 00003/00003/01237
d D 3.106 82/09/05 11:44:54 eric 128 127
c add $* to match zero or more and $> to make a "subroutine" call
e
s 00004/00000/01236
d D 3.105 82/09/01 10:22:49 eric 127 126
c log entering uid & pid
e
s 00002/00002/01234
d D 3.104 82/08/27 11:10:32 eric 126 125
c release e_id after fork in daemon code; ignore events scheduled by
c another process
e
s 00002/00000/01234
d D 3.103 82/08/25 23:18:02 eric 125 124
c assign a new queue id to all jobs coming in via TCP
e
s 00006/00002/01228
d D 3.102 82/08/25 16:17:57 eric 124 123
c apply ruleset 4 to rewrite addresses in the body of the message; fix
c a clock.c bug that caused it to lose events; more time cleanup.
e
s 00019/00016/01211
d D 3.101 82/08/25 11:19:55 eric 123 122
c clean up time manipulation to always be current; assign job
c id's earlier to make sure there is always one with a message.
e
s 00013/00000/01214
d D 3.100 82/08/24 19:40:36 eric 122 121
c log more info (on log level 11); try to detect wild accept loops;
c some minor cleanup and debugging checks; fix NoConnect option to;
c only apply to expensive mailers (regardless of sendqueue order)
e
s 00008/00000/01206
d D 3.99 82/08/24 10:26:43 eric 121 120
c diagnose reentry of main()
e
s 00005/00005/01201
d D 3.98 82/08/23 11:57:20 eric 120 119
c clean up queueing; log time in queue.
c **** This delta invalidates mqueue files ****
e
s 00004/00003/01202
d D 3.97 82/08/22 23:06:16 eric 119 118
c change $i to $j; $i is now queue id; put "Received:" format in .cf
c file; minor cleanup
e
s 00097/00008/01108
d D 3.96 82/08/22 19:01:44 eric 118 117
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00007/00002/01109
d D 3.95 82/08/17 16:09:10 eric 117 116
c check for length of queue directory name; do verify even on error
e
s 00024/00030/01087
d D 3.94 82/08/08 01:00:31 eric 116 115
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00015/00009/01102
d D 3.93 82/08/07 11:11:41 eric 115 114
c clean up comments
e
s 00009/00007/01102
d D 3.92 82/07/31 12:56:32 eric 114 113
c By default, just queue up the mail for most mailers and deliver
c from the queue.  This avoids the wild process problem in netnews
c (or so we hope).
e
s 00005/00000/01104
d D 3.91 82/07/27 23:01:11 eric 113 112
c clean up semantics of daemon mode to facilitate use of other IPC;
c if you can't create a socket assume there is another sendmail running
c and exit; move some code to main.c because it is not part of creating
c a connection.
e
s 00013/00000/01091
d D 3.90 82/07/14 11:18:59 eric 112 111
c disconnect sendmail from the controlling tty in daemon mode.
e
s 00001/00000/01090
d D 3.89 82/07/14 10:59:52 eric 111 110
c arrange for MotherPid to be correct in daemon mode
e
s 00008/00000/01082
d D 3.88 82/07/14 10:45:39 eric 110 109
c fork automatically in daemon mode (but only if no debugging)
e
s 00001/00001/01081
d D 3.87 82/07/14 09:23:13 eric 109 108
c don't accidently unlink a null pointer in finis(); change the way
c it decides whether to do the unlink.
e
s 00006/00001/01076
d D 3.86 82/07/05 13:18:08 eric 108 107
c don't deliver the message if there were errors during collection
e
s 00004/00001/01073
d D 3.85 82/07/05 12:37:04 eric 107 106
c check for errors before opening a daemon connection
e
s 00019/00003/01055
d D 3.84 82/07/02 20:51:24 eric 106 105
c arrange to not lose temporary queue control files (tf files)
c if you interrupt a queue run process.
e
s 00003/00000/01055
d D 3.83 82/06/26 12:33:21 eric 105 104
c take environment variable "NAME" to determine what your full name
c is; this is overridden by -F.
e
s 00001/00000/01054
d D 3.82 82/06/26 11:56:23 eric 104 103
c add _kill command to SMTP.  this is probably dangerous in the
c outside world.
e
s 00003/00001/01051
d D 3.81 82/06/18 11:58:09 eric 103 102
c believe host name on SMTP "HELO" line
e
s 00002/00002/01050
d D 3.80 82/06/17 10:43:20 eric 102 101
c fix botch in -Q flag (sets AliasFile rather than QueueDir)
e
s 00010/00013/01042
d D 3.79 82/06/06 23:05:23 eric 101 99
c implement alias owner feature.  this actually works for any user.
c basically, if the alias owner-xxx exists, errors sending to xxx will be
c sent to that alias rather than to the sender.
e
s 00012/00000/01055
d D 3.78.1.1 82/06/06 20:13:15 eric 100 99
c first cut at putting mailing list maintainers in -- there is a
c much better way though.
e
s 00003/00003/01052
d D 3.78 82/05/31 18:49:55 eric 99 98
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00037/00021/01018
d D 3.77 82/05/31 17:10:57 eric 98 97
c eliminate -V, -D, -p flags in favor of a single flag "-bx"
c (be in mode x).
e
s 00004/00002/01035
d D 3.76 82/05/31 15:32:26 eric 97 96
i 95
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00003/00001/00997
d D 3.75 82/05/29 20:00:35 eric 96 94
c allow the user with name "daemon" to send mail as anyone s/he wants.
e
s 00041/00004/00994
d D 3.74.1.1 82/05/29 18:20:25 eric 95 94
c try to install envelopes.  is this really worth it???
e
s 00029/00027/00969
d D 3.74 82/05/22 01:38:12 eric 94 93
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00002/00003/00994
d D 3.73 82/03/27 19:56:37 eric 93 92
c compensate for bug in getlogin: can return the empty string ("")
c for certain error conditions rather than the NULL pointer.
e
s 00001/00001/00996
d D 3.72 82/03/20 16:12:33 eric 92 91
c 16 bit changes -- should have no effect on VAX binaries to
c speak of.
e
s 00010/00010/00987
d D 3.71 82/03/06 16:11:59 eric 91 90
c get queue scanning working correctly in conjunction with daemon mode
e
s 00008/00001/00989
d D 3.70 82/03/06 15:35:20 eric 90 89
c have daemon mode assume SMTP mode
e
s 00028/00010/00962
d D 3.69 82/03/06 14:16:10 eric 89 88
c collapse special character processing into macro processing for
c simplicity of code.
e
s 00003/00003/00969
d D 3.68 82/03/06 12:09:24 eric 88 87
c clean up error handling in IPC case; fix a minor bug in headers in
c queueing code; make SMTP mail multi user per connect.
e
s 00007/00002/00965
d D 3.67 82/02/27 11:37:50 eric 87 86
c implement "return receipt requested".
e
s 00007/00001/00960
d D 3.66 82/02/26 21:56:15 eric 86 85
c implement daemon mode
e
s 00003/00012/00958
d D 3.65 82/02/26 19:02:01 eric 85 84
c default to OldStyle headers -- this turns out to be needed so that it
c will work right when running as a server.
e
s 00010/00000/00960
d D 3.64 82/02/20 18:54:14 eric 84 83
c ******  Hack to make all local mail have old-style headers  ******
e
s 00039/00000/00921
d D 3.63 82/02/20 12:59:52 eric 83 82
c expand macros in rewriting rules early to allow multi-word macros to
c be processed correctly.
e
s 00006/00000/00915
d D 3.62 82/02/20 12:10:02 eric 82 81
c implement -c flag: don't try to deliver expensive mail immediately
e
s 00036/00000/00879
d D 3.61 82/02/04 20:30:40 eric 81 80
c add host aliasing; add -p flag.  this version doesn't yet know about
c replacing the text of the host alias into the message however.  syntax
c is grotty: "/hostmatch:%s@newhost" or whatever.
e
s 00005/00000/00874
d D 3.60 82/01/23 14:16:31 eric 80 79
c let the user define "$x" to be whatever they want (i.e., don't redefine
c it if already defined).
e
s 00025/00011/00849
d D 3.59 82/01/10 21:57:38 eric 79 78
c cleanup from cbosgd (Mark Horton) testing; some internals, mostly
c configuration.  This tries to make the configuration file (cf.m4) be
c much more general, but I fear it is doomed to failure -- it may be
c better to just tell people to roll their own.
e
s 00001/00001/00859
d D 3.58 81/12/06 12:39:25 eric 78 77
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00011/00000/00849
d D 3.57 81/12/05 14:14:12 eric 77 76
c insert SMTP "Mail-From:" line.
e
s 00020/00000/00829
d D 3.56 81/12/05 11:53:47 eric 76 75
c put the SMTP and queueing code on compilation flags so that sendmail
c will fit on non-ID PDP-11's (ugh); put the ugly UUCP hack on a
c compilation flag also to emphasize that it sucks eggs; makefile
c cleanup.
e
s 00001/00004/00828
d D 3.55 81/11/22 19:17:50 eric 75 74
c Edit queue control files when running queue (assuming there are still
c recipients left).  Also, modify the MsgPriority to be the absolute
c number (not the Priority: value); this allows us to include aging into
c the priority algorithm.
e
s 00001/00001/00831
d D 3.54 81/11/21 18:42:54 eric 74 72
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00003/00002/00830
d D 3.53.1.1 81/11/21 15:48:16 eric 73 72
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00001/00002/00831
d D 3.53 81/11/08 17:26:42 eric 72 71
c LINT
e
s 00008/00002/00825
d D 3.52 81/11/07 21:58:15 eric 71 70
c copy printname for parsing From person
e
s 00021/00049/00806
d D 3.51 81/10/31 22:12:51 eric 70 69
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00001/00002/00854
d D 3.50 81/10/31 10:05:12 eric 69 68
c buffer standard output (or rather, don't unbuffer)
e
s 00007/00001/00849
d D 3.49 81/10/27 12:24:57 eric 68 67
c experimental version combining queueing with daemon operation.
c I'm sure this doesn't work -- if only because the wait()s are funny.
e
s 00016/00006/00834
d D 3.48 81/10/27 10:50:56 eric 67 66
c More queueing cleanup: implement timeouts (still one-stage),
c properly implement priorities (didn't work before), and miscellaneous
c cleanup.
e
s 00109/00063/00731
d D 3.47 81/10/26 14:22:38 eric 66 65
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00018/00002/00776
d D 3.46 81/10/23 19:38:14 eric 65 64
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00017/00011/00761
d D 3.45 81/10/22 09:43:37 eric 64 63
c take fullname from /etc/passwd if Smtp mode and sender name
c is indeed local.  Also accepts names more often; this is probably
c a disaster for sender verification.
e
s 00003/00000/00769
d D 3.44 81/10/20 11:36:28 eric 63 62
c clean up the SMTP stuff some more
e
s 00102/00084/00667
d D 3.43 81/10/19 22:27:21 eric 62 61
c implement SMTP mode -- doesn't support source routing or the
c HELP command, and doesn't give the correct code on VRFY or forwarding.
c Maybe someday....
e
s 00045/00020/00706
d D 3.42 81/10/17 16:58:08 eric 61 60
c initial prep to put in Daemon mode
e
s 00006/00001/00720
d D 3.41 81/10/12 10:04:22 eric 60 59
c throw in some "errno = 0;"'s to make syserr's more accurate;
c take any -f flag if debug mode and uid==euid.
e
s 00002/00000/00719
d D 3.40 81/09/24 10:30:47 eric 59 58
c changes to work under a V6 system -- mostly compilation flags
e
s 00000/00001/00719
d D 3.39 81/09/16 17:16:23 eric 58 57
c have .forward ownership stick harder than :include: ownership:
c this prevents cretins from using writable root files for nastiness.
c all this is pointless if /usr/lib/aliases is writable though....
e
s 00001/00000/00719
d D 3.38 81/09/16 16:39:47 eric 57 56
c be REALLY clever and inherit uid/gid from owner of :include:
c files also...   solves problem of alias to non-secure file
e
s 00005/00000/00714
d D 3.37 81/09/16 16:08:10 eric 56 55
c run as the user forwarding mail after a .forward operation;
c fix a bug in .forwarding that caused recursive expansion;
c restrict mail to programs, files, and with :include: for security
c reasons.
e
s 00001/00017/00713
d D 3.36 81/09/12 17:34:08 eric 55 54
c match on full name for local users
e
s 00002/00028/00728
d D 3.35 81/09/12 15:49:00 eric 54 53
c change From: processing to reduce the number of Original-From:
c lines; change allocation of global variables.
e
s 00003/00006/00753
d D 3.34 81/09/07 14:12:51 eric 53 52
c fix up umask; allow setuid on files to take recipient owner;
c factor some configuration info into conf.c
e
s 00034/00052/00725
d D 3.33 81/09/07 12:33:41 eric 52 51
c add auto-rebuild on alias database; fix some aliasing bugs;
c add statistics to rebuild; slight code restructuring; change
c version handling one last (?) time
e
s 00018/00027/00759
d D 3.32 81/09/06 19:48:57 eric 51 50
c cleanup, commenting, linting, etc.
e
s 00001/00000/00785
d D 3.31 81/09/01 11:43:38 eric 50 49
c add "suppress return-to-sender" function
e
s 00014/00010/00771
d D 3.30 81/08/31 21:21:48 eric 49 48
c collect mail statistics; change minor configuration
e
s 00004/00000/00777
d D 3.29 81/08/27 11:43:02 eric 48 47
c on -t, use argument list as a supress list
e
s 00001/00004/00776
d D 3.28 81/08/25 16:01:59 eric 47 46
c change processing of <LWSP> in addresses
e
s 00013/00002/00767
d D 3.27 81/08/24 14:05:42 eric 46 45
c Add "-t" option to read To:, Cc:, and Bcc: lines to get recipients
e
s 00006/00002/00763
d D 3.26 81/08/23 12:08:55 eric 45 44
c plug assorted security holes
e
s 00041/00036/00724
d D 3.25 81/08/22 14:33:26 eric 44 43
c add $b macro (really current date); move basic macro defn to
c before processing arguments (for -D); fix UNIX From problem
e
s 00006/00001/00754
d D 3.24 81/08/21 17:59:15 eric 43 42
c add -V flag to verify addresses
e
s 00012/00000/00743
d D 3.23 81/08/21 16:45:00 eric 42 41
c add the $y macro as the tty name.
e
s 00000/00002/00743
d D 3.22 81/08/20 15:14:27 eric 41 40
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00008/00003/00737
d D 3.21 81/08/18 17:13:03 eric 40 39
c factor out ARPANET FTP reply codes into conf.c
e
s 00059/00028/00681
d D 3.20 81/08/18 16:47:25 eric 39 38
c convert to really do arpanet reply codes right (maybe)
e
s 00008/00002/00701
d D 3.19 81/08/18 10:47:23 eric 38 37
c -C defaults to sendmail.cf, -A defaults to aliases.
e
s 00012/00001/00691
d D 3.18 81/08/18 10:39:08 eric 37 36
c put alias.{dir,pag} initialization into sendmail rather than
c a different program (on -I flag).
e
s 00010/00001/00682
d D 3.17 81/08/10 16:57:00 eric 36 35
c totally rework aliasing scheme -- sucks when no DBM now,
c but works better for the usual case; fix some quoting problems
c (and how many did I add?); remove .mailer feature since .forward
c will simulate this happily
e
s 00019/00001/00664
d D 3.16 81/08/09 19:08:30 eric 35 34
c put mailer definitions into configuration file
e
s 00026/00035/00639
d D 3.15 81/08/09 15:03:28 eric 34 33
c lint it
e
s 00016/00000/00658
d D 3.14 81/08/09 12:45:26 eric 33 32
c allow users to have a .mailcf which augments /usr/lib/sendmail.cf
e
s 00001/00001/00657
d D 3.13 81/08/09 10:23:54 eric 32 31
c fix minor botch in -F code
e
s 00021/00007/00637
d D 3.12 81/08/09 10:14:39 eric 31 30
c change to debugging levels; add -F to set full name;
c change old -F to -C (for configuration file)
e
s 00083/00049/00561
d D 3.11 81/08/08 17:47:48 eric 30 29
c add another set of rewrite rules to process From: address;
c this will allow generalized from address processing in an
c internet
e
s 00007/00000/00603
d D 3.10 81/08/08 14:00:54 eric 29 28
c preliminary groundbreaking for verbose mode
e
s 00066/00061/00537
d D 3.9 81/03/28 13:36:57 eric 28 27
c pass Full-Name field internally to do forwards correctly
e
s 00012/00011/00586
d D 3.8 81/03/28 12:02:47 eric 27 26
c put much more info in cf file (e.g., headers)
e
s 00011/00011/00586
d D 3.7 81/03/20 09:44:59 eric 26 25
c change name (again); from postbox to sendmail
e
s 00040/00025/00557
d D 3.6 81/03/11 10:46:12 eric 25 24
c general cleanup, esp. macro processor
e
s 00010/00006/00572
d D 3.5 81/03/09 13:22:51 eric 24 23
c first step at rewriting rules, etc.
e
s 00003/00000/00575
d D 3.4 81/03/07 17:45:44 eric 23 22
c drop stupid concatenation stuff; add hi_pptr
e
s 00003/00001/00572
d D 3.3 81/03/07 15:33:46 eric 22 21
c lint fixes
e
s 00018/00018/00555
d D 3.2 81/03/07 14:27:29 eric 21 20
c ----- delivermail ==> postbox -----
e
s 00069/00007/00504
d D 3.1 81/03/04 09:34:48 eric 20 19
c install fancy header stuff
e
s 00001/00001/00510
d D 2.4 81/02/28 11:50:40 eric 19 18
c install VAX mpx file logging
e
s 00024/00001/00487
d D 2.3 81/01/10 13:56:32 eric 18 17
c allow "eric" "at" "berkeley" as three separate arguments
e
s 00001/00001/00487
d D 2.2 81/01/08 18:18:44 eric 17 15
c convert to new log scheme
e
s 00026/00025/00463
d D 2.1.1.1 80/11/21 12:34:46 eric 16 15
c abortive attempt to make headers to (e.g.) msgs work
e
s 00000/00000/00488
d D 2.1 80/11/05 11:01:41 eric 15 13
c release 2
e
s 00006/00000/00488
d R 1.12 80/10/27 17:53:23 eric 14 13
c put diagnostic output in transcript file also.
e
s 00002/00002/00486
d D 1.11 80/10/18 16:49:34 eric 13 12
c cleanup for dbm stuff: Error => Errors; move local host
c detection into parse; misc cleanup
e
s 00000/00001/00488
d D 1.10 80/10/11 20:04:48 eric 12 11
c fix MsgId so that sizeof returns > 0
e
s 00014/00228/00475
d D 1.9 80/10/11 18:12:11 eric 11 10
c cleanup to simplify configuration & fix minor bugs
e
s 00001/00002/00702
d D 1.8 80/10/11 13:44:29 eric 10 9
c arranged to print Version on -d
e
s 00026/00002/00678
d D 1.7 80/10/11 12:58:02 eric 9 8
c allow multi-line fields in headers
e
s 00021/00003/00659
d D 1.6 80/08/07 18:37:51 eric 8 5
c allow UUCP to use -f/-r; this solution is cludgy (see comments in code)
e
s 00000/00085/00662
d D 1.5 80/08/02 13:49:10 eric 5 4
c cleaned up comments
e
s 00002/00000/00745
d D 1.4 80/07/25 22:03:43 eric 4 3
c add ID keywords
e
s 00010/00003/00735
d D 1.3 80/07/25 21:40:00 eric 3 2
c changed "-ee" flag to work with BerkNet better
e
s 00006/00006/00732
d D 1.2 80/06/24 23:47:06 eric 2 1
c try to synchronize error messages more carefully
e
s 00738/00000/00000
d D 1.1 80/06/23 08:24:16 eric 1 0
e
u
U
f b 
f i 
t
T
I 203
/*
I 222
D 451
 * Copyright (c) 1983 Eric P. Allman
E 451
I 451
 * Copyright (c) 1983, 1995 Eric P. Allman
E 451
E 222
D 219
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 219
I 219
D 340
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 340
I 340
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 340
 *
D 233
 * Redistribution and use in source and binary forms are permitted
D 222
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 222
I 222
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
E 233
I 233
 * %sccs.include.redist.c%
E 233
E 222
 */
E 219

#ifndef lint
D 340
char copyright[] =
D 219
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 219
I 219
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 219
 All rights reserved.\n";
E 340
I 340
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 340
D 219
#endif not lint
E 219
I 219
#endif /* not lint */
E 219

#ifndef lint
D 219
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 219
I 219
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 219

E 203
I 66
D 221
# define  _DEFINE
E 66
I 1
D 41
# include <stdio.h>
E 41
# include <signal.h>
D 41
# include <ctype.h>
E 41
I 20
D 166
# include <pwd.h>
I 116
# include <time.h>
E 166
E 116
I 112
D 195
# include <sys/ioctl.h>
E 195
I 195
# include <sgtty.h>
E 195
E 112
I 61
D 66
# include <sys/types.h>
# include <sys/stat.h>
E 61
I 54
# define  _DEFINE
E 66
E 54
E 20
D 21
# include "dlvrmail.h"
E 21
I 21
D 26
# include "postbox.h"
E 26
I 26
# include "sendmail.h"
E 221
I 221
#define	_DEFINE
E 221
I 172
D 196
# include <sys/file.h>
E 196
E 172
I 66
D 166
# include <sys/stat.h>
E 166
E 66
E 26
E 21
D 116
# ifdef LOG
D 19
# include <log.h>
E 19
I 19
# include <syslog.h>
E 19
# endif LOG
E 116

I 276
D 300
#include <unistd.h>
E 300
E 276
I 234
D 268
#include <sys/param.h>
E 268
E 234
I 224
D 282
#include <sys/file.h>
I 281
#include <sys/fcntl.h>
E 282
I 282
D 307
#include <fcntl.h>
E 307
I 307
#include "sendmail.h"
I 395
D 441
#include <netdb.h>
E 441
E 395
E 307
E 282
E 281
I 254
D 328
#include <sys/stat.h>
E 328
E 254
E 224
I 221
D 350
#include <signal.h>
E 350
D 386
#include <sgtty.h>
E 386
D 307
#include "sendmail.h"
E 307
I 281
D 391
#ifdef NAMED_BIND
E 391
I 391
#if NAMED_BIND
E 391
E 281
D 397
#include <arpa/nameser.h>
E 397
#include <resolv.h>
I 281
#endif
I 313
D 441
#include <pwd.h>
E 441
E 313
E 281

E 221
I 206
# ifdef lint
D 208
char	edata;
E 208
I 208
char	edata, end;
E 208
D 343
# endif lint
E 343
I 343
# endif /* lint */
E 343

E 206
I 4
D 78
static char	SccsId[] = "%W%	%G%";
E 78
I 78
D 204
SCCSID(%W%	%Y%	%G%);
E 78

E 204
E 4
/*
D 21
**  DELIVERMAIL -- Deliver mail to a set of destinations
E 21
I 21
D 26
**  POSTBOX -- Post mail to a set of destinations.
E 26
I 26
**  SENDMAIL -- Post mail to a set of destinations.
E 26
E 21
**
**	This is the basic mail router.  All user mail programs should
D 21
**	call this routine to actually deliver mail.  Delivermail in
E 21
I 21
D 26
**	call this routine to actually deliver mail.  Postbox in
E 26
I 26
**	call this routine to actually deliver mail.  Sendmail in
E 26
E 21
**	turn calls a bunch of mail servers that do the real work of
**	delivering the mail.
**
D 21
**	Delivermail is driven by tables defined in config.c.  This
E 21
I 21
D 26
**	Postbox is driven by tables defined in conf.c.  This
E 26
I 26
D 115
**	Sendmail is driven by tables defined in conf.c.  This
E 26
E 21
**	file will be different from system to system, but the rest
**	of the code will be the same.  This table could be read in,
**	but it seemed nicer to have it compiled in, since deliver-
**	mail will potentially be exercised a lot.
E 115
I 115
**	Sendmail is driven by tables read in from /usr/lib/sendmail.cf
**	(read by readcf.c).  Some more static configuration info,
**	including some code that you may want to tailor for your
**	installation, is in conf.c.  You may also want to touch
**	daemon.c (if you have some other IPC mechanism), acct.c
**	(to change your accounting), names.c (to adjust the name
**	server mechanism).
E 115
**
**	Usage:
D 21
**		/etc/delivermail [-f name] [-a] [-q] [-v] [-n] [-m] addr ...
E 21
I 21
D 26
**		/etc/postbox [-f name] [-a] [-q] [-v] [-n] [-m] addr ...
E 26
I 26
D 115
**		/etc/sendmail [-f name] [-a] [-q] [-v] [-n] [-m] addr ...
E 115
I 115
D 164
**		/etc/sendmail [flags] addr ...
E 164
I 164
**		/usr/lib/sendmail [flags] addr ...
E 164
E 115
E 26
E 21
**
D 164
**	Positional Parameters:
**		addr -- the address to deliver the mail to.  There
**			can be several.
E 164
I 164
**		See the associated documentation for details.
E 164
**
D 164
**	Flags:
**		-f name		The mail is from "name" -- used for
**				the header in local mail, and to
**				deliver reports of failures to.
**		-r name		Same as -f; however, this flag is
**				reserved to indicate special processing
**				for remote mail delivery as needed
**				in the future.  So, network servers
**				should use -r.
I 31
**		-Ffullname	Select what the full-name should be
**				listed as.
E 31
**		-a		This mail should be in ARPANET std
D 31
**				format (not used).
E 31
I 31
D 51
**				format.
E 51
I 51
**				format (obsolete version).
D 115
**		-am		Called from an FTP "MAIL" command.
**		-af		Called from an FTP "MLFL" command.
E 115
I 115
**		-as		Speak SMTP.
E 115
E 51
E 31
**		-n		Don't do aliasing.  This might be used
**				when delivering responses, for
**				instance.
D 115
**		-d		Run in debug mode.
E 115
I 115
**		-dN		Run with debugging set to level N.
E 115
**		-em		Mail back a response if there was an
**				error in processing.  This should be
**				used when the origin of this message
**				is another machine.
**		-ew		Write back a response if the user is
**				still logged in, otherwise, act like
**				-em.
**		-eq		Don't print any error message (just
**				return exit status).
**		-ep		(default)  Print error messages
**				normally.
I 3
**		-ee		Send BerkNet style errors.  This
**				is equivalent to MailBack except
**				that it has gives zero return code
**				(unless there were errors during
**				returning).  This used to be
**				"EchoBack", but you know how the old
**				software bounces.
E 3
**		-m		In group expansion, send to the
**				sender also (stands for the Mail metoo
**				option.
**		-i		Do not terminate mail on a line
**				containing just dot.
**		-s		Save UNIX-like "From" lines on the
**				front of messages.
I 29
**		-v		Give blow-by-blow description of
**				everything that happens.
I 46
**		-t		Read "to" addresses from message.
**				Looks at To:, Cc:, and Bcc: lines.
I 51
**		-I		Initialize the DBM alias files from
**				the text format files.
E 51
E 46
I 31
**		-Cfilename	Use alternate configuration file.
I 36
**		-Afilename	Use alternate alias file.
E 36
**		-DXvalue	Define macro X to have value.
I 115
**		-bv		Verify addresses only.
**		-bd		Run as a daemon.  Berkeley 4.2 only.
**		-bf		Fork after address verification.
**		-bq		Queue up for later delivery.
**		-ba		Process mail completely.
E 115
E 31
E 29
**
**	Return Codes:
**		As defined in <sysexits.h>.
**
**		These codes are actually returned from the auxiliary
**		mailers; it is their responsibility to make them
**		correct.
**
D 5
**	Defined Constants:
**		none
**
E 5
**	Compilation Flags:
D 11
**		BADMAIL -- the mailer used for local mail doesn't
**			return the standard set of exit codes.  This
**			causes the name to be looked up before mail
**			is ever sent.
E 11
**		LOG -- if set, everything is logged.
D 11
**		MESSAGEID -- if set, the Message-Id field is added
**			to the message header if one does not already
**			exist.  This can be used to delete duplicate
**			messages.
E 11
**
E 164
D 51
**	Compilation Instructions:
D 21
**		cc -c -O main.c config.c deliver.c parse.c
E 21
I 21
**		cc -c -O main.c conf.c deliver.c parse.c
E 21
**		cc -n -s *.o -lS
**		chown root a.out
**		chmod 755 a.out
D 21
**		mv a.out delivermail
E 21
I 21
D 26
**		mv a.out postbox
E 26
I 26
**		mv a.out sendmail
E 26
E 21
**
D 5
**	Requires:
**		signal (sys)
**		setbuf (sys)
**		initlog (libX)
**		open (sys)
**		lseek (sys)
**		close (sys)
**		dup (sys)
**		printf (sys)
**		syserr
**		atoi (sys)
**		freopen (sys)
**		openxscript
**		maketemp
**		getname
**		strcmp (sys)
**		getuid (sys)
**		parse
**		usrerr
**		finis
**		sendto
**		alias
**		recipient
**		nxtinq
**		deliver
**
E 5
**	Deficiencies:
**		It ought to collect together messages that are
**			destined for a single host and send these
**			to the auxiliary mail server together.
**		It should take "user at host" as three separate
**			parameters and combine them into one address.
**
E 51
**	Author:
D 164
**		Eric Allman, UCB/INGRES
E 164
I 164
**		Eric Allman, UCB/INGRES (until 10/81)
**			     Britton-Lee, Inc., purveyors of fine
**				database computers (from 11/81)
I 244
**			     Now back at UCB at the Mammoth project.
E 244
**		The support of the INGRES Project and Britton-Lee is
**			gratefully acknowledged.  Britton-Lee in
**			particular had absolutely nothing to gain from
**			my involvement in this project.
E 164
D 5
**
**	History:
**		12/26/79 -- first written.
E 5
*/


D 221



E 221
D 11
char	ArpaFmt;	/* mail is expected to be in ARPANET format */
char	FromFlag;	/* from person is explicitly specified */
char	Debug;		/* run in debug mode */
char	MailBack;	/* mail back response on error */
D 3
char	EchoBack;	/* echo the message on error */
E 3
I 3
char	BerkNet;	/* called from BerkNet */
E 3
char	WriteBack;	/* write back response on error */
char	HasXscrpt;	/* if set, the transcript file exists */
char	NoAlias;	/* don't do aliasing */
char	ForceMail;	/* mail even if already sent a copy */
char	MeToo;		/* send to the sender also if in a group expansion */
char	SaveFrom;	/* save From lines on the front of messages */
char	IgnrDot;	/* if set, ignore dot when collecting mail */
char	Error;		/* set if errors */
char	SuprErrs;	/* supress errors if set */
E 11
I 11
D 39
bool	ArpaFmt;	/* mail is expected to be in ARPANET format */
E 39
I 39
D 54
int	ArpaMode;	/* specifies the ARPANET mode */
E 39
bool	FromFlag;	/* from person is explicitly specified */
D 31
bool	Debug;		/* run in debug mode */
E 31
bool	MailBack;	/* mail back response on error */
bool	BerkNet;	/* called from BerkNet */
bool	WriteBack;	/* write back response on error */
bool	HasXscrpt;	/* if set, the transcript file exists */
bool	NoAlias;	/* don't do aliasing */
bool	ForceMail;	/* mail even if already sent a copy */
bool	MeToo;		/* send to the sender also if in a group expansion */
bool	SaveFrom;	/* save From lines on the front of messages */
bool	IgnrDot;	/* if set, ignore dot when collecting mail */
D 13
bool	Error;		/* set if errors */
E 13
bool	SuprErrs;	/* supress errors if set */
I 29
bool	Verbose;	/* set if blow-by-blow desired */
I 46
bool	GrabTo;		/* if set, read recipient addresses from msg */
I 48
bool	DontSend;	/* mark recipients as QDONTSEND */
I 50
bool	NoReturn;	/* don't return content of letter to sender */
I 53
int	OldUmask;	/* umask when called */
E 53
E 50
E 48
E 46
I 31
int	Debug;		/* debug level */
E 31
E 29
I 13
int	Errors;		/* count of errors */
I 36
int	AliasLevel;	/* current depth of aliasing */
E 54
E 36
E 13
E 11
D 66
char	InFileName[] = "/tmp/mailtXXXXXX";
char	Transcript[] = "/tmp/mailxXXXXXX";
E 66
D 21
addrq	From;		/* the from person */
E 21
I 21
D 54
ADDRESS	From;		/* the from person */
E 21
char	*To;		/* the target person */
I 20
D 27
char	*FullName;	/* full name of sender */
E 27
E 20
D 12
char	MsgId[MAXNAME];	/* the message-id for this letter */
E 12
int	HopCount;	/* hop count */
int	ExitStat;	/* the exit status byte */
D 21
addrq	SendQ;		/* queue of people to send to */
addrq	AliasQ;		/* queue of people who turned out to be aliases */
E 21
I 21
D 25
ADDRESS	SendQ;		/* queue of people to send to */
ADDRESS	AliasQ;		/* queue of people who turned out to be aliases */
E 25
E 21
I 20
HDR	*Header;	/* header list */
I 24
D 39
char	*Macro[128];	/* macros */
E 39
I 25
long	CurTime;	/* current time */
D 44
char	FromLine[80];	/* holds From line (UNIX style header) */
E 44
I 35
int	NextMailer = 0;	/* "free" index into Mailer struct */
struct mailer	*Mailer[MAXMAILERS+1];	/* definition of mailers */
E 54
I 54
D 94
int	NextMailer = 0;		/* "free" index into Mailer struct */
E 94
I 94
D 195
int		NextMailer = 0;	/* "free" index into Mailer struct */
E 195
I 195
int		NextMailer;	/* "free" index into Mailer struct */
E 195
E 94
I 62
D 166
static char	*FullName;	/* sender's full name */
E 166
I 166
char		*FullName;	/* sender's full name */
E 166
I 151
ENVELOPE	BlankEnvelope;	/* a "blank" envelope */
E 151
I 94
ENVELOPE	MainEnvelope;	/* the envelope around the basic letter */
I 208
ADDRESS		NullAddress =	/* a null address */
D 235
		{ "", "", "" };
E 235
I 235
		{ "", "", NULL, "" };
I 278
D 351
char		*UserEnviron[MAXUSERENVIRON + 1];
E 351
I 351
D 455
char		*UserEnviron[MAXUSERENVIRON + 2];
E 351
				/* saved user environment */
E 455
I 321
D 469
char		RealUserName[256];	/* the actual user id on this host */
E 469
I 344
char		*CommandLineArgs;	/* command line args for pid file */
I 369
bool		Warn_Q_option = FALSE;	/* warn about Q option use */
I 415
char		**SaveArgv;	/* argument vector for re-execing */
E 415
E 369
E 344
E 321
E 278
E 235
E 208
E 94
E 62
E 54
E 35
E 25
E 24
E 20

I 208
/*
**  Pointers for setproctitle.
**	This allows "ps" listings to give more useful information.
D 362
**	These must be kept out of BSS for frozen configuration files
**		to work.
E 362
*/

D 406
# ifdef SETPROCTITLE
E 406
char		**Argv = NULL;		/* pointer to argument vector */
char		*LastArgv = NULL;	/* end of argv */
D 263
# endif SETPROCTITLE
E 263
I 263
D 406
# endif /* SETPROCTITLE */
E 406
E 263

I 244
D 294
/*
**  The file in which to log raw recipient information.
**	This is logged before aliasing, forwarding, and so forth so we
**	can see how our addresses are being used.  For example, this
**	would give us the names of aliases (instead of what they alias
**	to), the pre-MX hostnames, and so forth.
**
**	This is specified on the command line, not in the config file,
**	and is therefore really only useful for logging SMTP RCPTs.
*/

char		*RcptLogFile = NULL;	/* file name */

E 294
I 268
static void	obsolete();

E 268
E 244
E 208
I 90
#ifdef DAEMON
#ifndef SMTP
ERROR %%%%   Cannot have daemon mode without SMTP   %%%% ERROR
D 263
#endif SMTP
#endif DAEMON
E 263
I 263
#endif /* SMTP */
#endif /* DAEMON */
E 263
E 90

I 250
D 291
#define MAXCONFIGLEVEL	3	/* highest config version level known */
E 291
I 291
D 356
#define MAXCONFIGLEVEL	4	/* highest config version level known */
E 356
I 356
D 401
#define MAXCONFIGLEVEL	5	/* highest config version level known */
E 401
I 401
#define MAXCONFIGLEVEL	6	/* highest config version level known */
E 401
E 356
E 291

I 466
int
E 466
I 267
D 268
static void obsolete();

E 268
E 267
E 250
D 221




I 90

E 221
E 90
D 187
main(argc, argv)
E 187
I 187
main(argc, argv, envp)
E 187
	int argc;
	char **argv;
I 187
	char **envp;
E 187
{
	register char *p;
I 266
D 356
	register char *q;
E 356
E 266
I 153
D 173
	int ac;
E 173
	char **av;
E 153
I 28
D 66
	char *realname;
E 66
I 31
D 62
	char *fullname = NULL;
E 62
E 31
E 28
D 21
	extern char *maketemp();
E 21
I 21
D 39
	extern char *collect();
E 39
E 21
D 20
	extern char *getname();
E 20
I 20
D 93
	extern char *getlogin();
E 93
E 20
I 16
	char *locname;
E 16
D 427
	extern int finis();
E 427
D 21
	extern addrq *parse();
	register addrq *q;
E 21
I 21
D 34
	extern ADDRESS *parse();
	register ADDRESS *q;
E 34
E 21
	extern char Version[];
D 34
	extern int errno;
E 34
D 267
	char *from;
E 267
I 267
	char *ep, *from;
E 267
D 22
	register int i;
E 22
	typedef int (*fnptr)();
I 151
	STAB *st;
E 151
I 18
D 28
	char nbuf[MAXLINE];
E 28
I 28
D 52
	char nbuf[MAXLINE];		/* holds full name */
E 52
E 28
I 20
D 62
	struct passwd *pw;
E 62
D 34
	extern char *newstr();
D 24
	extern char *Macro[];
E 24
	extern char *index();
I 22
	extern char *strcpy(), *strcat();
E 34
I 34
D 66
	extern char *arpadate();
E 34
I 23
D 27
	extern char *makemsgid();
E 27
I 24
D 49
	char *cfname;
I 36
	char *aliasname;
E 49
I 49
	extern char *AliasFile;		/* location of alias file */
	extern char *ConfFile;		/* location of configuration file */
	extern char *StatFile;		/* location of statistics summary */
E 66
E 49
E 36
I 25
	register int i;
I 260
	int j;
E 260
I 153
D 169
	int pass = 0;
E 169
I 169
D 189
	bool readconfig = FALSE;
E 189
I 189
D 361
	bool readconfig = TRUE;
E 361
E 189
E 169
E 153
I 43
D 98
	bool verifyonly = FALSE;	/* only verify names */
E 98
I 45
D 202
	bool safecf = TRUE;		/* this conf file is sys default */
E 202
E 45
E 43
D 66
	char pbuf[10];			/* holds pid */
	char tbuf[10];			/* holds "current" time */
	char cbuf[5];			/* holds hop count */
	char dbuf[30];			/* holds ctime(tbuf) */
I 42
	char ybuf[10];			/* holds tty id */
E 66
I 63
D 119
	char ibuf[30];			/* holds HostName */
E 119
I 119
D 151
	char jbuf[30];			/* holds HostName */
E 151
E 119
I 67
	bool queuemode = FALSE;		/* process queue requests */
I 215
D 362
	bool nothaw;
E 362
I 255
	bool safecf = TRUE;
I 369
	bool warn_C_flag = FALSE;
	char warn_f_flag = '\0';
E 369
E 255
E 215
E 67
E 63
E 42
I 37
D 155
	bool aliasinit = FALSE;
I 153
	bool dofreeze = FALSE;		/* freeze the .cf file after read */
E 155
E 153
I 151
	static bool reenter = FALSE;
I 274
D 466
	char *argv0 = argv[0];
E 466
I 313
	struct passwd *pw;
E 313
I 308
	struct stat stb;
I 395
	struct hostent *hp;
E 395
I 313
D 321
	char realuser[256];
E 321
E 313
E 308
E 274
D 212
	char jbuf[30];			/* holds HostName */
E 212
I 212
D 238
	char jbuf[30];			/* holds MyHostName */
E 238
I 238
D 267
	char jbuf[60];			/* holds MyHostName */
I 256
	extern int DtableSize;
E 267
I 267
	char jbuf[MAXHOSTNAMELEN];	/* holds MyHostName */
I 469
	static char rnamebuf[MAXNAME];	/* holds RealUserName */
E 469
D 268
	extern int DtableSize, optind;
E 268
I 268
	extern int DtableSize;
	extern int optind;
E 268
E 267
E 256
E 238
E 212
E 151
I 42
D 66
	extern char *ttyname();
E 66
I 61
D 62
	char cfbuf[60];			/* holds .cf filename */
E 62
D 296
	extern bool safefile();
E 296
I 65
D 151
	STAB *st;
E 151
I 66
	extern time_t convtime();
I 95
D 466
	extern putheader(), putbody();
E 466
I 121
D 151
	static bool reenter = FALSE;
E 151
I 151
D 336
	extern ENVELOPE *newenvelope();
E 336
I 152
D 236
	extern intsig();
E 236
I 236
	extern void intsig();
E 236
I 175
D 177
	extern char *myhostname();
E 177
I 177
D 395
	extern char **myhostname();
E 395
I 395
	extern struct hostent *myhostname();
E 395
I 182
	extern char *arpadate();
I 298
D 321
	extern char *getrealhostname();
E 321
I 321
	extern char *getauthinfo();
I 366
	extern char *getcfname();
E 366
I 335
D 336
	extern char *macvalue();
E 336
E 335
E 321
E 298
I 187
D 275
	extern char **environ;
E 275
I 268
	extern char *optarg;
I 278
	extern char **environ;
I 379
D 394
	extern void dumpstate();
E 394
I 394
	extern void sigusr1();
I 415
	extern void sighup();
I 466
	extern void initmacros __P((ENVELOPE *));
E 466
E 415
E 394
E 379
E 278
E 268
E 187
E 182
E 177
E 175
E 152
E 151

I 169
	/*
	**  Check to see if we reentered.
	**	This would normally happen if e_putheader or e_putbody
	**	were NULL when invoked.
	*/

E 169
	if (reenter)
	{
		syserr("main: reentered!");
		abort();
	}
	reenter = TRUE;
E 121
E 95
I 73
	extern ADDRESS *recipient();
E 73
E 66
E 65
E 61
E 42
E 37
D 34
	extern char *sprintf();
I 33
# ifndef V6
	extern char *getenv();
# endif V6
E 34
E 33
E 25
E 24
E 23
E 22
E 20
E 18
I 16
	bool canrename;
E 16

I 368
	/* do machine-dependent initializations */
D 374
	init_md();
E 374
I 374
	init_md(argc, argv);
E 374

I 379
D 415
	/* arrange to dump state on signal */
E 415
#ifdef SIGUSR1
I 415
	/* arrange to dump state on user-1 signal */
E 415
D 394
	setsignal(SIGUSR1, dumpstate);
E 394
I 394
	setsignal(SIGUSR1, sigusr1);
E 394
#endif

E 379
E 368
I 247
D 258
#ifdef SYSTEM5
E 247
I 243
D 246
# ifndef SYSTEM5
E 243
I 217
	/* Enforce use of local time */
	unsetenv("TZ");
I 243
# endif
E 246
I 246
	/* Enforce use of local time (null string overrides this) */
	if (TimeZoneSpec == NULL)
		unsetenv("TZ");
	else if (TimeZoneSpec[0] != '\0')
D 252
		setenv("TZ", TimeZoneSpec);
E 252
I 252
	{
		p = xalloc(strlen(TimeZoneSpec) + 4);
		(void) strcpy(p, "TZ=");
		(void) strcat(p, TimeZoneSpec);
		putenv(p);
	}
E 252
I 247
#else
E 258
I 258
D 259
#ifndef SYSTEM5
E 259
I 259
D 347
#ifndef SYS5TZ
E 259
E 258
	/* enforce use of kernel-supplied time zone information */
	unsetenv("TZ");
#endif
E 247
E 246
E 243

E 347
I 256
	/* in 4.4BSD, the table can be huge; impose a reasonable limit */
D 342
	DtableSize = getdtablesize();
E 342
I 342
	DtableSize = getdtsize();
E 342
	if (DtableSize > 256)
		DtableSize = 256;

E 256
E 217
I 208
D 211
# ifdef SETPROCTITLE
E 211
E 208
I 169
	/*
I 208
D 211
	**  Save start and extent of argv for setproctitle.
	*/

	Argv = argv;
	LastArgv = argv[argc - 1] + strlen(argv[argc - 1]);
# endif SETPROCTITLE

	/*
E 211
E 208
I 170
	**  Be sure we have enough file descriptors.
I 216
	**	But also be sure that 0, 1, & 2 are open.
E 216
	*/

I 216
D 223
	i = open("/dev/null", 2);
E 223
I 223
D 392
	i = open("/dev/null", O_RDWR);
E 392
I 392
	i = open("/dev/null", O_RDWR, 0);
E 392
E 223
D 308
	while (i >= 0 && i < 2)
		i = dup(i);
E 308
I 308
D 353
	if (fstat(STDIN_FILENO, &stb) < 0)
E 353
I 353
	if (fstat(STDIN_FILENO, &stb) < 0 && errno != EOPNOTSUPP)
E 353
		(void) dup2(i, STDIN_FILENO);
D 353
	if (fstat(STDOUT_FILENO, &stb) < 0)
E 353
I 353
	if (fstat(STDOUT_FILENO, &stb) < 0 && errno != EOPNOTSUPP)
E 353
		(void) dup2(i, STDOUT_FILENO);
D 353
	if (fstat(STDERR_FILENO, &stb) < 0)
E 353
I 353
	if (fstat(STDERR_FILENO, &stb) < 0 && errno != EOPNOTSUPP)
E 353
		(void) dup2(i, STDERR_FILENO);
D 367
	(void) close(i);
E 367
I 367
	if (i != STDIN_FILENO && i != STDOUT_FILENO && i != STDERR_FILENO)
		(void) close(i);
E 367
E 308
E 216
D 199
	for (i = 3; i < 20; i++)
E 199
I 199
D 223
	for (i = 3; i < 50; i++)
E 223
I 223
D 255
	for (i = getdtablesize(); i > 2; --i)
E 255
I 255
D 256
	i = getdtablesize();
E 256

D 256
	/* in 4.4BSD, the table can be huge; impose a reasonable limit */
	if (i > 256)
		i = 256;
E 256
I 256
	i = DtableSize;
E 256
D 276
	while (--i > 2)
E 255
E 223
E 199
		(void) close(i);
E 276
I 276
	while (--i > 0)
	{
		if (i != STDIN_FILENO && i != STDOUT_FILENO && i != STDERR_FILENO)
			(void) close(i);
	}
E 276
	errno = 0;

I 231
D 393
#ifdef LOG_MAIL
E 393
I 393
#ifdef LOG
# ifdef LOG_MAIL
E 393
	openlog("sendmail", LOG_PID, LOG_MAIL);
D 393
#else 
E 393
I 393
# else 
E 393
	openlog("sendmail", LOG_PID);
I 393
# endif
E 393
#endif 

I 407
	tTsetup(tTdvect, sizeof tTdvect, "0-99.1");

E 407
E 231
I 210
D 312
	/*
	**  Set default values for variables.
	**	These cannot be in initialized data space.
	*/

	setdefaults();

E 312
E 210
I 200
	/* set up the blank envelope */
	BlankEnvelope.e_puthdr = putheader;
	BlankEnvelope.e_putbody = putbody;
	BlankEnvelope.e_xfp = NULL;
I 208
	STRUCTCOPY(NullAddress, BlankEnvelope.e_from);
E 208
D 213
	CurEnv = &BlankEnvelope;
I 208
	STRUCTCOPY(NullAddress, MainEnvelope.e_from);
E 213
I 213
	STRUCTCOPY(BlankEnvelope, MainEnvelope);
	CurEnv = &MainEnvelope;
E 213
E 208

I 312
	/*
	**  Set default values for variables.
	**	These cannot be in initialized data space.
	*/

	setdefaults(&BlankEnvelope);

E 312
I 296
	RealUid = getuid();
	RealGid = getgid();

I 313
D 441
	pw = getpwuid(RealUid);
E 441
I 441
	pw = sm_getpwuid(RealUid);
E 441
	if (pw != NULL)
D 321
		(void) strcpy(realuser, pw->pw_name);
E 321
I 321
D 469
		(void) strcpy(RealUserName, pw->pw_name);
E 469
I 469
		(void) strcpy(rnamebuf, pw->pw_name);
E 469
E 321
	else
D 321
		(void) sprintf(realuser, "Unknown UID %d", RealUid);
E 321
I 321
D 469
		(void) sprintf(RealUserName, "Unknown UID %d", RealUid);
E 469
I 469
		(void) sprintf(rnamebuf, "Unknown UID %d", RealUid);
	RealUserName = rnamebuf;
E 469
E 321

I 342
D 345
	/* our real uid will have to be root -- we will trash this later */
	setuid((uid_t) 0);
I 344

E 345
	/* save command line arguments */
	i = 0;
	for (av = argv; *av != NULL; )
		i += strlen(*av++) + 1;
I 415
	SaveArgv = (char **) xalloc(sizeof (char *) * (argc + 1));
E 415
	CommandLineArgs = xalloc(i);
	p = CommandLineArgs;
D 415
	for (av = argv; *av != NULL; )
E 415
I 415
	for (av = argv, i = 0; *av != NULL; )
E 415
	{
I 415
		SaveArgv[i++] = newstr(*av);
E 415
		if (av != argv)
			*p++ = ' ';
		strcpy(p, *av++);
		p += strlen(p);
	}
I 415
	SaveArgv[i] = NULL;
E 415
E 344

E 342
E 313
E 296
I 267
	/* Handle any non-getoptable constructions. */
	obsolete(argv);

E 267
E 200
	/*
E 170
	**  Do a quick prescan of the argument list.
D 362
	**	We do this to find out if we can potentially thaw the
	**	configuration file.  If not, we do the thaw now so that
	**	the argument processing applies to this run rather than
	**	to the run that froze the configuration.
E 362
	*/
D 267

E 169
I 52
	argv[argc] = NULL;
I 169
D 173
	ac = argc;
E 173
	av = argv;
E 267
I 267
D 268
#ifdef DBM
#define	GETOPTSTR	"b:C:c:d:e:F:f:h:I:i:m:no:p:q:R:r:s:T:tv:"
#else
#define	GETOPTSTR	"b:C:c:d:e:F:f:h:i:m:no:p:q:R:r:s:T:tv:"
#endif
E 268
E 267
I 215
D 362
	nothaw = FALSE;
E 362
I 362

E 362
I 310
D 313
#ifdef __alpha
E 313
I 313
D 341
#ifdef __osf__
E 313
D 325
#define OPTIONS		"b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvx"
E 325
I 325
#define OPTIONS		"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvx"
E 341
I 341
#if defined(__osf__) || defined(_AIX3)
D 346
#define OPTIONS		"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvX:x"
E 346
I 346
D 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvX:x"
E 405
I 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:IimnO:o:p:q:r:sTtvX:x"
E 405
E 346
E 341
E 325
D 375
#else
E 310
E 215
D 173
	while (--ac > 0)
E 173
I 173
D 199
	while (*++av != NULL)
E 199
I 199
D 267
	while ((p = *++av) != NULL)
E 199
E 173
	{
D 173
		if (strncmp(*++av, "-C", 2) == 0 || strncmp(*av, "-bz", 3) == 0)
E 173
I 173
D 199
		if (strncmp(*av, "-C", 2) == 0 || strncmp(*av, "-bz", 3) == 0)
E 199
I 199
		if (strncmp(p, "-C", 2) == 0)
E 267
I 267
D 268
	while ((j = getopt(argc, argv, GETOPTSTR)) != EOF)
		switch(j)
E 268
I 268
D 269
	while ((j = getopt(argc, argv, "b:C:d:")) != EOF)
E 269
I 269
D 279
#define OPTIONS		"b:C:cd:eF:f:h:Iimno:p:q:R:r:sTtv"
E 279
I 279
D 294
#define OPTIONS		"b:C:cd:e:F:f:h:Iimno:p:q:R:r:sTtv"
E 294
I 294
D 325
#define OPTIONS		"b:C:cd:e:F:f:h:Iimno:p:q:r:sTtv"
E 325
I 325
D 341
#define OPTIONS		"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtv"
E 341
I 341
D 346
#define OPTIONS		"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvX:"
E 346
I 346
# if defined(ultrix)
#  define OPTIONS	"B:b:C:cd:e:F:f:h:IiM:mno:p:q:r:sTtvX:"
# else
#  define OPTIONS	"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvX:"
# endif
E 375
E 346
E 341
E 325
I 310
#endif
I 375
#if defined(ultrix)
D 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:IiM:mno:p:q:r:sTtvX:"
E 405
I 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:IiM:mnO:o:p:q:r:sTtvX:"
E 405
#endif
I 444
#if defined(sony_news)
# define OPTIONS	"B:b:C:cd:E:e:F:f:h:IiJ:mnO:o:p:q:r:sTtvX:"
#endif
E 444
D 409
#if defined(NeXT)
D 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:IimnOo:p:q:r:sTtvX:"
E 405
I 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:IimnO:o:p:q:r:sTtvX:"
E 405
#endif
E 409
#ifndef OPTIONS
D 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:Iimno:p:q:r:sTtvX:"
E 405
I 405
# define OPTIONS	"B:b:C:cd:e:F:f:h:IimnO:o:p:q:r:sTtvX:"
E 405
#endif
E 375
E 310
E 294
E 279
	while ((j = getopt(argc, argv, OPTIONS)) != EOF)
E 269
	{
		switch (j)
E 268
E 267
		{
D 267
			ConfFile = &p[2];
			if (ConfFile[0] == '\0')
				ConfFile = "sendmail.cf";
E 267
I 267
D 362
		  case 'b':
			if (optarg[0] == 'z' && optarg[1] == '\0')
				nothaw = TRUE;
			break;

		  case 'C':
			ConfFile = optarg;
E 267
D 200
			readconfig = safecf = FALSE;
E 200
I 200
D 202
			safecf = FALSE;
E 202
E 200
D 201
			setuid(getruid());
E 201
D 205
			setgid(getrgid());
I 201
			setuid(getruid());
E 205
I 205
D 342
			(void) setgid(getrgid());
			(void) setuid(getruid());
E 342
I 342
			(void) setgid(RealGid);
			(void) setuid(RealUid);
E 342
I 255
			safecf = FALSE;
E 255
E 205
E 201
D 200
			readcf(ConfFile, FALSE);
E 200
E 199
E 173
D 215
			break;
E 215
I 215
			nothaw = TRUE;
E 215
I 199
D 267
		}
		else if (strncmp(p, "-bz", 3) == 0)
D 215
			break;
E 215
I 215
			nothaw = TRUE;
D 229
# ifdef DEBUG
E 229
		else if (strncmp(p, "-d", 2) == 0)
		{
E 267
I 267
			break;

E 362
		  case 'd':
E 267
D 407
			tTsetup(tTdvect, sizeof tTdvect, "0-99.1");
E 407
D 267
			tTflag(&p[2]);
E 267
I 267
			tTflag(optarg);
E 267
			setbuf(stdout, (char *) NULL);
D 444
			printf("Version %s\n", Version);
E 444
I 267
			break;
D 268
		  case 'c': case 'e': case 'F': case 'f': case 'h': case 'i': 
		  case 'm': case 'n': case 'o': case 'p': case 'q': case 'R': 
		  case 'r': case 's': case 'T': case 't': case 'v': 
#ifdef DBM
		  case 'I': 
#endif
			break;
		  default:
			ExitStat = EX_USAGE;
			finis();
			break;
E 268
E 267
		}
I 268
	}
E 268
D 229
# endif DEBUG
E 229
E 215
E 199
D 267
	}
E 267
I 232

I 444
	if (tTd(0, 1))
	{
		int ll;
		extern char *CompileOptions[];

D 459
		printf("Version %s", Version);
E 459
I 459
D 475
		printf("Version %s\nCompiled with:\t", Version);
E 475
I 475
		printf("Version %s\n Compiled with:", Version);
E 475
E 459
		av = CompileOptions;
D 459
		ll = 100;
E 459
I 459
		ll = 7;
E 459
		while (*av != NULL)
		{
			if (ll + strlen(*av) > 63)
			{
				putchar('\n');
				ll = 0;
			}
			if (ll == 0)
I 459
			{
E 459
				putchar('\t');
D 459
			else
				putchar(' ');
E 459
I 459
				putchar('\t');
			}
D 475
			putchar(' ');
E 475
I 475
			else
				putchar(' ');
E 475
E 459
			printf("%s", *av);
			ll += strlen(*av++) + 1;
		}
		putchar('\n');
	}
I 470
	if (tTd(0, 10))
	{
		int ll;
		extern char *OsCompileOptions[];
E 470

I 470
D 475
		printf("OS Defines:\t", Version);
E 475
I 475
		printf("    OS Defines:", Version);
E 475
		av = OsCompileOptions;
		ll = 7;
		while (*av != NULL)
		{
			if (ll + strlen(*av) > 63)
			{
				putchar('\n');
				ll = 0;
			}
			if (ll == 0)
			{
				putchar('\t');
				putchar('\t');
			}
D 475
			putchar(' ');
E 475
I 475
			else
				putchar(' ');
E 475
			printf("%s", *av);
			ll += strlen(*av++) + 1;
		}
		putchar('\n');
#ifdef _PATH_UNIX
D 475
		printf("Unix path:\t  %s\n", _PATH_UNIX);
E 475
I 475
D 477
		printf("     Unix path:\t%s\n", _PATH_UNIX);
E 477
I 477
		printf("Kernel symbols:\t%s\n", _PATH_UNIX);
E 477
E 475
#endif
D 475
		printf("Config file:\t  %s\n", getcfname());
		printf("Proc Id file:\t  %s\n", PidFile);
E 475
I 475
		printf("   Config file:\t%s\n", getcfname());
D 477
		printf("  Proc Id file:\t%s\n", PidFile);
E 477
I 477
		printf("      Pid file:\t%s\n", PidFile);
E 477
E 475
	}

E 470
E 444
	InChannel = stdin;
	OutChannel = stdout;

I 296
D 361
# ifdef FROZENCONFIG
E 296
E 232
D 173
	if (ac <= 0)
E 173
I 173
D 199
	if (*av == NULL)
E 199
I 199
D 215
	if (p == NULL)
E 215
I 215
	if (!nothaw)
E 215
E 199
E 173
D 274
		readconfig = !thaw(FreezeFile);
E 274
I 274
		readconfig = !thaw(FreezeFile, argv0);
I 296
# else
	readconfig = TRUE;
# endif
E 296
E 274
I 187
D 275

D 268
	/* reset the environment after the thaw */
D 211
	environ = envp;
E 211
I 211
D 260
	for (i = 0; i < MAXUSERENVIRON && envp[i] != NULL; i++)
		UserEnviron[i] = newstr(envp[i]);
	UserEnviron[i] = NULL;
E 260
I 260
D 267
	i = j = 0;
	while (j < MAXUSERENVIRON && (p = envp[i++]) != NULL)
E 267
I 267
	
E 268
	/* strip out "dangerous" environment variables */
	(void) unsetenv("FS");
	for (i = 1; (p = envp[i++]) != NULL;)
E 267
	{
I 261
D 267
		/* strip out "dangerous" envariables */
E 261
		if (strncmp(p, "FS=", 3) == 0 || strncmp(p, "LD_", 3) == 0)
E 267
I 267
		if (strncmp(p, "LD_", 3) == 0)
		{
D 268
			p[0] = '\1';
E 268
I 268
			/* hack: change this name to be non-special */
			p[0] = '\201';
E 268
E 267
			continue;
D 267
		UserEnviron[j++] = newstr(p);
E 267
I 267
		}
E 267
	}
D 267
	UserEnviron[j] = NULL;
E 260
	environ = UserEnviron;
E 267
I 267
	environ = envp;
E 275
E 267

E 361
D 351
# ifdef SETPROCTITLE
E 351
	/*
I 278
	**  Move the environment so setproctitle can use the space at
	**  the top of memory.
	*/

D 455
	for (i = j = 0; j < MAXUSERENVIRON && (p = envp[i]) != NULL; i++)
	{
D 429
D 430
		if (strncmp(p, "FS=", 3) == 0 || strncmp(p, "LD_", 3) == 0)
E 430
I 430
		if (strncmp(p, "IFS=", 4) == 0 || strncmp(p, "LD_", 3) == 0)
E 430
E 429
I 429
		if (strncmp(p, "IFS=", 4) == 0 || strncmp(p, "LD_", 3) == 0)
E 429
			continue;
		UserEnviron[j++] = newstr(p);
	}
	UserEnviron[j] = NULL;
	environ = UserEnviron;
E 455
I 455
	for (i = 0; envp[i] != NULL; i++)
		continue;
D 476
	environ = (char **) xalloc(sizeof (char *) * i);
E 476
I 476
	environ = (char **) xalloc(sizeof (char *) * (i + 1));
E 476
	for (i = 0; envp[i] != NULL; i++)
		environ[i] = newstr(envp[i]);
I 460
	environ[i] = NULL;
E 460
E 455

I 456
	/* and prime the child environment */
	setuserenv("AGENT", "sendmail");

E 456
I 351
D 406
# ifdef SETPROCTITLE
E 406
E 351
	/*
E 278
	**  Save start and extent of argv for setproctitle.
	*/

	Argv = argv;
D 214
	LastArgv = envp[i - 1] + strlen(envp[i - 1]);
E 214
I 214
D 261
	if (i > 0)
E 261
I 261
D 278
	if (--i > 0)
E 278
I 278
	if (i > 0)
E 278
E 261
		LastArgv = envp[i - 1] + strlen(envp[i - 1]);
	else
		LastArgv = argv[argc - 1] + strlen(argv[argc - 1]);
E 214
D 263
# endif SETPROCTITLE
E 263
I 263
D 406
# endif /* SETPROCTITLE */
E 406
E 263
E 211
E 187

D 232
	/*
	**  Now do basic initialization
	*/

E 169
I 62
	InChannel = stdin;
	OutChannel = stdout;
E 232
I 116
D 118
	MsgId = "<none>";
E 118
E 116
E 62
E 52
D 350
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
D 34
		signal(SIGINT, finis);
	signal(SIGTERM, finis);
E 34
I 34
D 152
		(void) signal(SIGINT, finis);
E 152
I 152
		(void) signal(SIGINT, intsig);
E 152
I 45
	if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
D 152
		(void) signal(SIGHUP, finis);
E 45
	(void) signal(SIGTERM, finis);
E 152
I 152
		(void) signal(SIGHUP, intsig);
	(void) signal(SIGTERM, intsig);
I 171
	(void) signal(SIGPIPE, SIG_IGN);
E 350
I 350
	if (setsignal(SIGINT, SIG_IGN) != SIG_IGN)
		(void) setsignal(SIGINT, intsig);
D 415
	if (setsignal(SIGHUP, SIG_IGN) != SIG_IGN)
		(void) setsignal(SIGHUP, intsig);
E 415
	(void) setsignal(SIGTERM, intsig);
	(void) setsignal(SIGPIPE, SIG_IGN);
E 350
E 171
E 152
E 34
D 69
	setbuf(stdout, (char *) NULL);
E 69
I 53
D 293
	OldUmask = umask(0);
E 293
I 293
	OldUmask = umask(022);
E 293
I 98
D 157
	Mode = MD_DEFAULT;
E 157
I 157
	OpMode = MD_DELIVER;
E 157
I 104
D 290
	MotherPid = getpid();
E 290
I 105
D 220
# ifndef V6
E 220
	FullName = getenv("NAME");
D 220
# endif V6
E 220
E 105
E 104
E 98
I 95
D 200

D 151
	/* set up the main envelope */
	MainEnvelope.e_puthdr = putheader;
	MainEnvelope.e_putbody = putbody;
I 120
D 123
	time(&CurTime);
	MainEnvelope.e_ctime = CurTime;
E 123
I 123
D 124
	MainEnvelope.e_ctime = curtime();
E 124
E 123
E 120
E 95
I 94
	CurEnv = &MainEnvelope;
E 151
I 151
	/* set up the blank envelope */
	BlankEnvelope.e_puthdr = putheader;
	BlankEnvelope.e_putbody = putbody;
I 166
	BlankEnvelope.e_xfp = NULL;
E 166
	CurEnv = &BlankEnvelope;
E 200
E 151
I 95

I 338
D 391
#ifdef NAMED_BIND
E 391
I 391
#if NAMED_BIND
E 391
	if (tTd(8, 8))
I 428
	{
		res_init();
E 428
I 413
	{
		res_init();
E 413
		_res.options |= RES_DEBUG;
I 428
	}
E 428
I 413
	}
E 413
#endif

E 338
I 164
D 199
	/* make sure we have a clean slate */
D 190
	closeall();
E 190
I 190
	for (i = 3; i < 50; i++)
		(void) close(i);
E 190

E 199
E 164
E 95
E 94
E 53
D 230
# ifdef LOG
E 230
I 230
D 231
#ifdef LOG_MAIL
E 230
D 17
	initlog("delivermail", 0, LOG_INDEP);
E 17
I 17
D 21
	openlog("delivermail", 0);
E 21
I 21
D 26
	openlog("postbox", 0);
E 26
I 26
D 166
	openlog("sendmail", 0);
E 166
I 166
D 201
	openlog("sendmail", LOG_PID);
E 201
I 201
D 207
D 208
	openlog("sendmail", LOG_PID, 0);
E 208
I 208
	openlog("sendmail", LOG_PID, LOG_MAIL);
E 208
E 207
I 207
D 209
	openlog("sendmail", LOG_PID, LOG_MAIL);
E 209
E 207
E 201
E 166
E 26
E 21
E 17
D 230
# endif LOG
E 230
I 230
#else 
	openlog("sendmail", LOG_PID);
#endif 
E 231
E 230
I 70
D 153
	openxscrpt();
E 153
I 153
D 162
	Xscript = stderr;
E 162
I 162
D 166
	Xscript = NULL;
E 166
E 162
E 153
E 70
D 116
# ifdef DEBUG
# ifdef DEBUGFILE
	if ((i = open(DEBUGFILE, 1)) > 0)
	{
D 34
		lseek(i, 0L, 2);
		close(1);
		dup(i);
		close(i);
E 34
I 34
		(void) lseek(i, 0L, 2);
		(void) close(1);
		(void) dup(i);
		(void) close(i);
E 34
		Debug++;
	}
# endif DEBUGFILE
D 10
	if (Debug)
		printf("%s\n", Version);
E 10
# endif
E 116
	errno = 0;
I 44
D 66

	/*
	**  Initialize and define basic system macros.
	**	Collect should be called first, so that the time
	**	corresponds to the time that the messages starts
	**	getting sent, rather than when it is first composed.
	*/

E 66
E 44
	from = NULL;
I 179

D 189
	/* initialize some macros, etc. */
E 179
I 85
D 94
	OldStyle = TRUE;
E 94
I 94
D 140
	CurEnv->e_oldstyle = TRUE;
I 114
	NoConnect = TRUE;
E 140
E 114
E 94
E 85
I 83
	initmacros();
I 179

	/* hostname */
E 179
I 175
D 177
	p = myhostname();
	if (p != NULL && *p != '\0')
E 177
I 177
D 183
	av = myhostname(jbuf);
E 183
I 183
	av = myhostname(jbuf, sizeof jbuf);
E 183
	if (jbuf[0] != '\0')
E 189
I 189
D 361
	if (readconfig)
E 189
	{
D 189
		p = newstr(jbuf);
E 177
		define('w', p, CurEnv);
I 177
		setclass('w', p);
	}
	while (av != NULL && *av != NULL)
		setclass('w', *av++);
E 189
I 189
		/* initialize some macros, etc. */
D 357
		initmacros();
E 357
I 357
		initmacros(CurEnv);
E 361
I 361
	/* initialize some macros, etc. */
	initmacros(CurEnv);
I 435
	init_vendor_macros(CurEnv);
E 435
E 361
E 357
E 189
I 179

D 189
	/* version */
	define('v', Version, CurEnv);
E 189
I 189
D 313
		/* hostname */
		av = myhostname(jbuf, sizeof jbuf);
		if (jbuf[0] != '\0')
		{
I 277
			struct	utsname	utsname;
E 277
I 239
D 266
			register char *q;
E 266
			extern char *strchr();
E 313
I 313
D 361
		/* version */
		define('v', Version, CurEnv);
	}
E 361
I 361
	/* version */
	define('v', Version, CurEnv);
E 361
E 313

E 239
I 215
D 229
#ifdef DEBUG
E 229
D 313
			if (tTd(0, 4))
				printf("canonical name: %s\n", jbuf);
D 229
#endif DEBUG
E 229
E 215
			p = newstr(jbuf);
			define('w', p, CurEnv);
E 313
I 313
	/* hostname */
D 395
	av = myhostname(jbuf, sizeof jbuf);
E 395
I 395
	hp = myhostname(jbuf, sizeof jbuf);
E 395
	if (jbuf[0] != '\0')
	{
		struct	utsname	utsname;
D 334
		extern char *strchr();
E 334
E 313
I 239

D 313
			q = strchr(jbuf, '.');
			if (q != NULL)
			{
D 242
				*q = '\0';
E 242
I 242
				*q++ = '\0';
E 242
				p = newstr(jbuf);
I 242
				define('m', q, CurEnv);
E 242
			}
I 277
			setclass('w', p);
E 313
I 313
		if (tTd(0, 4))
			printf("canonical name: %s\n", jbuf);
D 378
		p = newstr(jbuf);
E 378
D 356
		define('w', p, CurEnv);
E 356
I 356
D 358
		if (ConfigLevel < 5)
			define('w', p, CurEnv);
E 358
I 358
		define('w', newstr(jbuf), CurEnv);	/* must be new string */
E 358
E 356
I 352
D 378
		define('j', p, CurEnv);
E 352
I 315
		setclass('w', p);
E 378
I 378
		define('j', newstr(jbuf), CurEnv);
		setclass('w', jbuf);
E 378
E 315
E 313

D 313
			if (uname(&utsname) >= 0)
				p = utsname.nodename;
			else
			{
				makelower(jbuf);
				p = jbuf;
			}
			if (tTd(0, 4))
				printf("UUCP nodename: %s\n", p);
			p = newstr(p);
			define('k', p, CurEnv);
E 277
E 239
			setclass('w', p);
		}
		while (av != NULL && *av != NULL)
E 313
I 313
D 356
		q = strchr(jbuf, '.');
		if (q != NULL)
E 356
I 356
		p = strchr(jbuf, '.');
		if (p != NULL)
E 356
E 313
I 215
		{
D 229
#ifdef DEBUG
E 229
D 313
			if (tTd(0, 4))
				printf("\ta.k.a.: %s\n", *av);
D 229
#endif DEBUG
E 229
E 215
			setclass('w', *av++);
E 313
I 313
D 356
			*q++ = '\0';
D 315
			p = newstr(jbuf);
E 315
			define('m', q, CurEnv);
I 315
			p = newstr(jbuf);
			setclass('w', p);
E 356
I 356
D 363
			*p++ = '\0';
			if (*p != '\0')
				define('m', newstr(p), CurEnv);
			setclass('w', jbuf);
E 363
I 363
			if (p[1] != '\0')
			{
				define('m', newstr(&p[1]), CurEnv);
D 462
				setclass('m', &p[1]);
E 462
			}
			while (p != NULL && strchr(&p[1], '.') != NULL)
			{
				*p = '\0';
				setclass('w', jbuf);
				*p++ = '.';
				p = strchr(p, '.');
			}
E 363
E 356
E 315
E 313
I 215
		}
I 356
D 358
		if (ConfigLevel >= 5)
			define('w', newstr(jbuf), CurEnv);
E 358
E 356
I 313
D 315
		setclass('w', p);
E 315
E 313
E 215

D 313
		/* version */
		define('v', Version, CurEnv);
E 313
I 313
		if (uname(&utsname) >= 0)
			p = utsname.nodename;
		else
		{
I 373
			if (tTd(0, 22))
				printf("uname failed (%s)\n", errstring(errno));
E 373
			makelower(jbuf);
			p = jbuf;
		}
		if (tTd(0, 4))
D 395
			printf("UUCP nodename: %s\n", p);
E 395
I 395
			printf(" UUCP nodename: %s\n", p);
E 395
		p = newstr(p);
		define('k', p, CurEnv);
I 376
		setclass('k', p);
E 376
		setclass('w', p);
E 313
	}
I 313
D 395
	while (av != NULL && *av != NULL)
E 395
I 395
	if (hp != NULL)
E 395
	{
D 395
		if (tTd(0, 4))
			printf("\ta.k.a.: %s\n", *av);
		setclass('w', *av++);
E 395
I 395
		for (av = hp->h_aliases; av != NULL && *av != NULL; av++)
		{
			if (tTd(0, 4))
				printf("\ta.k.a.: %s\n", *av);
			setclass('w', *av);
		}
D 396
		if (hp->h_addrtype == AF_INET && hp->h_length == 4)
E 396
I 396
D 397
		if (hp->h_addrtype == AF_INET && hp->h_length == IPADDRSIZE)
E 397
I 397
		if (hp->h_addrtype == AF_INET && hp->h_length == INADDRSZ)
E 397
E 396
		{
			register int i;

			for (i = 0; hp->h_addr_list[i] != NULL; i++)
			{
				char ipbuf[100];

				sprintf(ipbuf, "[%s]",
					inet_ntoa(*((struct in_addr *) hp->h_addr_list[i])));
				if (tTd(0, 4))
					printf("\ta.k.a.: %s\n", ipbuf);
				setclass('w', ipbuf);
			}
		}
E 395
	}
E 313
E 189

I 454
	/* probe interfaces and locate any additional names */
	load_if_names();

E 454
	/* current time */
D 182
	define('b', arpadate(NULL), CurEnv);
E 182
I 182
	define('b', arpadate((char *) NULL), CurEnv);
E 182
E 179
E 177
E 175
E 83
I 20
D 24
	initmacs();
E 24
I 24
D 26
	cfname = "postbox.cf";
E 26
I 26
D 27
	cfname = "sendmail.cf";
E 27
I 27
D 35
	cfname = "/usr/lib/sendmail.cf";
E 35
I 35
D 49
	cfname = CONFFILE;
I 36
	aliasname = ALIASFILE;
E 49
E 36
E 35
E 27
E 26
E 24
E 20

I 44
D 66
	/* process id */
	(void) sprintf(pbuf, "%d", getpid());
	define('p', pbuf);

	/* hop count */
	(void) sprintf(cbuf, "%d", HopCount);
	define('c', cbuf);

	/* time as integer, unix time, arpa time */
	(void) time(&CurTime);
	(void) sprintf(tbuf, "%ld", &CurTime);
	define('t', tbuf);
	(void) strcpy(dbuf, ctime(&CurTime));
	*index(dbuf, '\n') = '\0';
	define('d', dbuf);
	p =  newstr(arpadate(dbuf));
	define('a', p);
	define('b', p);

	/* version */
	define('v', Version);

	/* tty name */
	p = ttyname(2);
	if (p != NULL)
	{
		if (rindex(p, '/') != NULL)
			p = rindex(p, '/') + 1;
		strcpy(ybuf, p);
		define('y', ybuf);
	}

E 66
E 44
	/*
I 313
	**  Find our real host name for future logging.
	*/

D 321
	p = getrealhostname(STDIN_FILENO);
	if (p != NULL)
		RealHostName = newstr(p);
	else
		RealHostName = "localhost";
E 321
I 321
	p = getauthinfo(STDIN_FILENO);
	define('_', p, CurEnv);
E 321

	/*
E 313
I 138
D 140
	**  Do initial configuration.
	**	This involves deciding what our configuration file will
	**	be and then running it.  Later we will parse the rest of
	**	the arguments, some of which may override the configuration
	**	file.
	**		Notice the problem here: user configuration files
	**		will override the command line options.  Ugh.
E 140
I 140
	** Crack argv.
E 140
	*/

D 140
	if (argc > 1 && (p = *++argv)[0] == '-')
E 140
I 140
D 153
	while (--argc > 0 && (p = *++argv)[0] == '-')
E 153
I 153
D 169
  crackargs:
E 169
D 173
	ac = argc;
E 173
	av = argv;
D 169
	pass++;
E 169
I 155
D 263
	p = rindex(*av, '/');
E 263
I 263
	p = strrchr(*av, '/');
E 263
	if (p++ == NULL)
		p = *av;
	if (strcmp(p, "newaliases") == 0)
D 157
		setoption('b', "i", FALSE, TRUE);
E 157
I 157
		OpMode = MD_INITALIAS;
E 157
	else if (strcmp(p, "mailq") == 0)
D 157
		setoption('b', "p", FALSE, TRUE);
E 157
I 157
		OpMode = MD_PRINT;
I 196
	else if (strcmp(p, "smtpd") == 0)
		OpMode = MD_DAEMON;
E 196
E 157
E 155
D 173
	while (--ac > 0 && (p = *++av)[0] == '-')
E 173
I 173
D 267
	while ((p = *++av) != NULL && p[0] == '-')
E 173
E 153
E 140
	{
D 140
		/* trim off special leading parameters */
		if (p[1] == 'C')
E 140
I 140
		switch (p[1])
E 267
I 267

	optind = 1;
D 268
	while ((j = getopt(argc, argv, GETOPTSTR)) != EOF)
		switch(j)
E 268
I 268
D 269
	while ((j = getopt(argc, argv, "b:C:c:d:e:F:f:h:I:i:m:no:p:q:R:r:s:T:tv:")) != EOF)
E 269
I 269
	while ((j = getopt(argc, argv, OPTIONS)) != EOF)
E 269
	{
		switch (j)
E 268
E 267
E 140
		{
D 140
			/* set configuration file */
E 140
I 140
D 157
		  case 'a':	/* arpanet format */
			ArpaMode = TRUE;
			if (p[2] == 's')
E 157
I 157
		  case 'b':	/* operations mode */
D 267
			switch (p[2])
E 267
I 267
D 268
			switch(j = *optarg)
E 268
I 268
			switch (j = *optarg)
E 268
E 267
E 157
			{
D 157
				/* running smtp */
# ifdef SMTP
				Smtp = TRUE;
# else SMTP
E 157
I 157
			  case MD_DAEMON:
D 227
# ifndef DAEMON
E 227
I 227
# ifdef DAEMON
D 342
				if (getuid() != 0) {
E 342
I 342
				if (RealUid != 0) {
E 342
					usrerr("Permission denied");
					exit (EX_USAGE);
				}
				(void) unsetenv("HOSTALIASES");
# else
E 227
D 226
				syserr("Daemon mode not implemented");
E 226
I 226
				usrerr("Daemon mode not implemented");
				ExitStat = EX_USAGE;
E 226
				break;
D 263
# endif DAEMON
E 263
I 263
# endif /* DAEMON */
E 263
			  case MD_SMTP:
# ifndef SMTP
E 157
D 226
				syserr("I don't speak SMTP");
E 226
I 226
				usrerr("I don't speak SMTP");
				ExitStat = EX_USAGE;
E 226
I 157
				break;
E 157
D 263
# endif SMTP
E 263
I 263
# endif /* SMTP */
E 263
I 157
D 248
			  case MD_ARPAFTP:
E 248
			  case MD_DELIVER:
			  case MD_VERIFY:
			  case MD_TEST:
			  case MD_INITALIAS:
			  case MD_PRINT:
I 387
D 398
#ifdef MAYBE_NEXT_RELEASE
E 398
			  case MD_ARPAFTP:
D 398
#endif
E 398
E 387
I 296
D 361
#ifdef FROZENCONFIG
E 296
			  case MD_FREEZE:
I 296
#endif
E 361
E 296
D 267
				OpMode = p[2];
E 267
I 267
				OpMode = j;
E 267
				break;

I 296
D 361
#ifndef FROZENCONFIG
E 361
			  case MD_FREEZE:
				usrerr("Frozen configurations unsupported");
				ExitStat = EX_USAGE;
				break;
D 361
#endif
E 361

E 296
			  default:
D 226
				syserr("Invalid operation mode %c", p[2]);
E 226
I 226
D 267
				usrerr("Invalid operation mode %c", p[2]);
E 267
I 267
				usrerr("Invalid operation mode %c", j);
E 267
				ExitStat = EX_USAGE;
E 226
				break;
E 157
			}
I 325
			break;

		  case 'B':	/* body type */
D 419
			CurEnv->e_bodytype = newstr(optarg);
E 419
I 419
D 487
			if (strcasecmp(optarg, "7bit") == 0 ||
			    strcasecmp(optarg, "8bitmime") == 0)
				CurEnv->e_bodytype = newstr(optarg);
E 487
I 487
			if (strcasecmp(optarg, "7BIT") == 0)
			{
				CurEnv->e_bodytype = "7BIT";
				SevenBitInput = TRUE;
			}
			else if (strcasecmp(optarg, "8BITMIME") == 0)
			{
				CurEnv->e_bodytype = "8BITMIME";
				SevenBitInput = FALSE;
			}
E 487
			else
				usrerr("Illegal body type %s", optarg);
E 419
E 325
			break;

D 199
		  case 'C':	/* select configuration file */
E 140
			ConfFile = &p[2];
			if (ConfFile[0] == '\0')
				ConfFile = "sendmail.cf";
I 153
			safecf = FALSE;
E 199
I 199
		  case 'C':	/* select configuration file (already done) */
I 313
D 342
			if (getuid() != 0)
E 342
I 342
			if (RealUid != 0)
E 342
D 369
				auth_warning(CurEnv,
					"Processed by %s with -C %s",
D 321
					realuser, optarg);
E 321
I 321
					RealUserName, optarg);
E 369
I 369
				warn_C_flag = TRUE;
E 369
I 362
			ConfFile = optarg;
I 486
			endpwent();
E 486
			(void) setgid(RealGid);
			(void) setuid(RealUid);
			safecf = FALSE;
E 362
E 321
E 313
E 199
E 153
D 140
			safecf = FALSE;
		}
	}
E 140
I 140
			break;
E 140

D 140
	/* now run the system configuration file */
	readcf(ConfFile, safecf);
E 140
I 140
D 221
# ifdef DEBUG
E 221
I 221
D 229
#ifdef DEBUG
E 229
E 221
D 215
		  case 'd':	/* debug */
E 215
I 215
D 362
		  case 'd':	/* debugging -- redo in case frozen */
E 215
			tTsetup(tTdvect, sizeof tTdvect, "0-99.1");
D 267
			tTflag(&p[2]);
E 267
I 267
			tTflag(optarg);
E 267
			setbuf(stdout, (char *) NULL);
E 362
I 362
		  case 'd':	/* debugging -- already done */
E 362
I 225
D 237
#ifdef NAMED_BIND
E 225
I 221
			_res.options |= RES_DEBUG;
I 225
#endif
E 237
E 225
E 221
D 215
			printf("Version %s\n", Version);
E 215
			break;
D 221
# endif DEBUG
E 221
I 221
D 229
#endif
E 229
E 221
E 140

D 140
	/*
E 138
	** Crack argv.
	*/

D 138
	while (--argc > 0 && (p = *++argv)[0] == '-')
E 138
I 138
	for (; --argc > 0 && (p = *argv)[0] == '-'; argv++)
E 138
	{
		switch (p[1])
		{
		  case 'r':	/* obsolete -f flag */
E 140
		  case 'f':	/* from address */
I 140
		  case 'r':	/* obsolete -f flag */
E 140
D 267
			p += 2;
D 173
			if (*p == '\0')
E 173
I 173
			if (*p == '\0' && ((p = *++av) == NULL || *p == '-'))
E 173
			{
D 153
				p = *++argv;
				if (--argc <= 0 || *p == '-')
E 153
I 153
				p = *++av;
D 173
				if (--ac <= 0 || *p == '-')
E 173
I 173
				if (p == NULL || *p == '-')
E 173
E 153
				{
D 226
					syserr("No \"from\" person");
E 226
I 226
					usrerr("No \"from\" person");
					ExitStat = EX_USAGE;
E 226
D 153
					argc++;
					argv--;
E 153
I 153
D 173
					ac++;
E 173
					av--;
E 153
					break;
				}
			}
E 267
D 153
			if (from != NULL)
E 153
I 153
D 169
			if (from != NULL && pass <= 1)
E 169
I 169
			if (from != NULL)
E 169
E 153
			{
D 226
				syserr("More than one \"from\" person");
E 226
I 226
				usrerr("More than one \"from\" person");
				ExitStat = EX_USAGE;
E 226
				break;
			}
D 208
			from = p;
E 208
I 208
D 267
			from = newstr(p);
E 267
I 267
D 419
			from = newstr(optarg);
E 419
I 419
D 428
D 430
			from = newstr(denlstring(optarg));
E 430
I 430
D 434
			from = newstr(denlstring(optarg, TRUE));
E 434
E 430
E 428
I 428
D 433
			from = newstr(denlstring(optarg, TRUE));
E 433
I 433
			from = newstr(denlstring(optarg, TRUE, TRUE));
E 433
E 428
E 419
I 313
D 319
			auth_warning(CurEnv,
				"%s set sender to %s using -%c",
				realuser, from, j);
E 319
I 319
D 321
			if (strcmp(realuser, from) != 0)
E 321
I 321
			if (strcmp(RealUserName, from) != 0)
E 321
D 369
				auth_warning(CurEnv,
					"%s set sender to %s using -%c",
D 321
					realuser, from, j);
E 321
I 321
					RealUserName, from, j);
E 369
I 369
				warn_f_flag = j;
E 369
E 321
E 319
E 313
E 267
E 208
			break;

I 31
		  case 'F':	/* set full name */
D 51
			fullname = &p[2];
E 51
I 51
D 267
			p += 2;
D 173
			if (*p == '\0')
E 173
I 173
			if (*p == '\0' && ((p = *++av) == NULL || *p == '-'))
E 173
			{
D 153
				p = *++argv;
				if (--argc <= 0 || *p == '-')
E 153
I 153
D 173
				p = *++av;
				if (--ac <= 0 || *p == '-')
E 153
				{
					syserr("Bad -F flag");
D 153
					argc++;
					argv--;
E 153
I 153
					ac++;
					av--;
E 153
					break;
				}
E 173
I 173
D 226
				syserr("Bad -F flag");
E 226
I 226
				usrerr("Bad -F flag");
				ExitStat = EX_USAGE;
E 226
				av--;
				break;
E 173
			}
D 62
			fullname = p;
E 62
I 62
D 208
			FullName = p;
E 208
I 208
			FullName = newstr(p);
E 267
I 267
D 421
			FullName = newstr(optarg);
E 421
I 421
D 423
			FullName = newstr(denlstring(optarg));
E 423
I 423
			FullName = newstr(optarg);
E 423
E 421
E 267
E 208
E 62
E 51
			break;

E 31
		  case 'h':	/* hop count */
D 267
			p += 2;
D 173
			if (*p == '\0')
E 173
I 173
			if (*p == '\0' && ((p = *++av) == NULL || !isdigit(*p)))
E 267
I 267
			CurEnv->e_hopcount = strtol(optarg, &ep, 10);
			if (*ep)
E 267
E 173
			{
D 153
				p = *++argv;
				if (--argc <= 0 || *p < '0' || *p > '9')
E 153
I 153
D 173
				p = *++av;
				if (--ac <= 0 || *p < '0' || *p > '9')
E 153
				{
					syserr("Bad hop count (%s)", p);
D 153
					argc++;
					argv--;
E 153
I 153
					ac++;
					av--;
E 153
					break;
				}
E 173
I 173
D 226
				syserr("Bad hop count (%s)", p);
E 226
I 226
D 267
				usrerr("Bad hop count (%s)", p);
E 267
I 267
				usrerr("Bad hop count (%s)", optarg);
E 267
				ExitStat = EX_USAGE;
E 226
D 267
				av--;
E 267
				break;
E 173
			}
D 164
			HopCount = atoi(p);
E 164
I 164
D 267
			CurEnv->e_hopcount = atoi(p);
E 267
E 164
			break;
D 155

D 140
		  case 'e':	/* error message disposition */
			switch (p[2])
			{
			  case 'p':	/* print errors normally */
				break;	/* (default) */

			  case 'q':	/* be silent about it */
D 34
				freopen("/dev/null", "w", stdout);
E 34
I 34
				(void) freopen("/dev/null", "w", stdout);
E 34
				break;

			  case 'm':	/* mail back */
D 70
				MailBack++;
				openxscrpt();
E 70
I 70
				MailBack = TRUE;
				HoldErrs = TRUE;
E 70
				break;

D 3
			  case 'e':	/* echo back */
				EchoBack++;
E 3
I 3
			  case 'e':	/* do berknet error processing */
D 70
				BerkNet++;
E 3
				openxscrpt();
E 70
I 70
				BerkNet = TRUE;
				HoldErrs = TRUE;
E 70
				break;

			  case 'w':	/* write back (or mail) */
D 70
				WriteBack++;
				openxscrpt();
E 70
I 70
				WriteBack = TRUE;
				HoldErrs = TRUE;
E 70
				break;
			}
			break;

# ifdef DEBUG
		  case 'd':	/* debug */
D 31
			Debug++;
I 10
D 27
			printf("%s\n", Version);
E 27
I 27
			printf("Version %s\n", Version);
E 31
I 31
D 116
			Debug = atoi(&p[2]);
			if (Debug <= 0)
				Debug = 1;
E 116
I 116
			tTsetup(tTdvect, sizeof tTdvect, "0-99.1");
			tTflag(&p[2]);
E 116
I 69
D 72
			setbuf(stdout, NULL);
E 72
I 72
			setbuf(stdout, (char *) NULL);
E 72
E 69
D 116
			printf("Version %s Debug %d\n", Version, Debug);
E 116
I 116
			printf("Version %s\n", Version);
E 116
E 31
E 27
E 10
			break;
I 20

D 61
		  case 'D':	/* redefine internal macro */
E 61
I 61
		  case 'M':	/* redefine internal macro */
E 61
D 24
			if (!isupper(p[2]))
				usrerr("Invalid flag: %s", p);
			else
				Macro[p[2] - 'A'] = &p[3];
E 24
I 24
D 39
			Macro[p[2]] = &p[3];
E 39
I 39
			define(p[2], &p[3]);
E 39
E 24
			break;
E 20
# endif DEBUG
I 24

I 116
		  case 'L':	/* logging */
			LogLevel = atoi(&p[2]);
			break;

E 116
D 31
		  case 'F':	/* select control file */
E 31
I 31
		  case 'C':	/* select configuration file */
E 31
D 38
			cfname = &p[2];
E 38
I 38
D 138
			if (p[2] == '\0')
D 49
				cfname = "sendmail.cf";
E 49
I 49
				ConfFile = "sendmail.cf";
E 49
			else
D 49
				cfname = &p[2];
E 49
I 49
				ConfFile = &p[2];
E 49
I 45
			safecf = FALSE;
E 138
E 45
E 38
			break;
I 36

		  case 'A':	/* select alias file */
D 38
			aliasname = &p[2];
E 38
I 38
			if (p[2] == '\0')
D 49
				aliasname = "aliases";
E 49
I 49
				AliasFile = "aliases";
E 49
			else
D 49
				aliasname = &p[2];
E 49
I 49
				AliasFile = &p[2];
E 49
E 38
			break;
I 66

		  case 'Q':	/* select queue dir */
			if (p[2] == '\0')
D 102
				AliasFile = "mqueue";
E 102
I 102
				QueueDir = "mqueue";
E 102
			else
D 102
				AliasFile = &p[2];
E 102
I 102
D 117
				QueueDir = &p[2];
E 117
I 117
D 134
			{
				if (strlen(&p[2]) > 50)
					syserr("Absurd length Queue path");
				else
					QueueDir = &p[2];
			}
E 134
I 134
				QueueDir = &p[2];
E 134
E 117
E 102
			break;

		  case 'T':	/* set timeout interval */
			TimeOut = convtime(&p[2]);
			break;
E 66
E 36
E 24
		
		  case 'n':	/* don't alias */
D 114
			NoAlias++;
E 114
I 114
			NoAlias = TRUE;
E 114
			break;

E 140
I 37
# ifdef DBM
		  case 'I':	/* initialize alias DBM file */
			aliasinit = TRUE;
I 52
			Verbose = TRUE;
E 52
			break;
# endif DBM
E 155
D 140

E 37
		  case 'm':	/* send to me too */
D 114
			MeToo++;
E 114
I 114
			MeToo = TRUE;
E 114
			break;

		  case 'i':	/* don't let dot stop me */
D 114
			IgnrDot++;
E 114
I 114
			IgnrDot = TRUE;
E 114
			break;

I 43
D 98
		  case 'V':	/* verify only */
			verifyonly = TRUE;
			break;

E 98
E 43
		  case 'a':	/* arpanet format */
D 39
			ArpaFmt++;
E 39
I 39
D 70
			switch (p[2])
E 70
I 70
			ArpaMode = TRUE;
			if (p[2] == 's')
E 70
			{
D 70
			  case 'f':	/* mail from file connection */
				ArpaMode = ARPA_FILE;
				break;

			  case 'm':	/* mail over telnet connection */
				ArpaMode = ARPA_MAIL;
				break;

			  default:
				ArpaMode = ARPA_OLD;
				break;
E 70
I 70
				/* running smtp */
I 76
# ifdef SMTP
E 76
				Smtp = TRUE;
I 76
# else SMTP
				syserr("I don't speak SMTP");
# endif SMTP
E 76
E 70
			}
E 39
			break;
I 82

# ifdef QUEUE
D 114
		  case 'c':	/* don't connect to non-local mailers */
			NoConnect = TRUE;
E 114
I 114
		  case 'c':	/* connect to non-local mailers */
			NoConnect = FALSE;
E 114
			break;
# endif QUEUE
E 140
E 82
		
D 140
		  case 's':	/* save From lines in headers */
D 114
			SaveFrom++;
E 114
I 114
			SaveFrom = TRUE;
E 140
I 140
		  case 'n':	/* don't alias */
			NoAlias = TRUE;
E 140
E 114
I 29
			break;

D 140
		  case 'v':	/* give blow-by-blow description */
D 114
			Verbose++;
E 114
I 114
			Verbose = TRUE;
			NoConnect = FALSE;
E 140
I 140
		  case 'o':	/* set option */
D 267
			setoption(p[2], &p[3], FALSE, TRUE);
E 267
I 267
D 312
			setoption(*optarg, optarg + 1, FALSE, TRUE);
E 312
I 312
			setoption(*optarg, optarg + 1, FALSE, TRUE, CurEnv);
I 405
			break;

		  case 'O':	/* set option (long form) */
			setoption(' ', optarg, FALSE, TRUE, CurEnv);
E 405
E 312
E 267
E 140
E 114
E 29
			break;

I 265
		  case 'p':	/* set protocol */
D 267
			p += 2;
			if (*p == '\0' && ((p = *++av) == NULL || !isdigit(*p)))
			{
				usrerr("Bad -p (protocol) flag");
				ExitStat = EX_USAGE;
				av--;
				break;
			}
D 266
			define('r', newstr(p), CurEnv);
E 266
I 266
			q = strchr(p, ':');
E 267
I 267
D 356
			q = strchr(optarg, ':');
E 267
			if (q != NULL)
				*q++ = '\0';
E 356
I 356
			p = strchr(optarg, ':');
			if (p != NULL)
I 419
			{
E 419
				*p++ = '\0';
I 419
				if (*p != '\0')
				{
					ep = xalloc(strlen(p) + 1);
					cleanstrcpy(ep, p, MAXNAME);
					define('s', ep, CurEnv);
				}
			}
E 419
E 356
D 267
			if (*p != '\0')
				define('r', newstr(p), CurEnv);
E 267
I 267
			if (*optarg != '\0')
D 419
				define('r', newstr(optarg), CurEnv);
E 267
D 288
			if (*q != '\0')
E 288
I 288
D 356
			if (q != NULL && *q != '\0')
E 288
				define('s', newstr(q), CurEnv);
E 356
I 356
			if (p != NULL && *p != '\0')
				define('s', newstr(p), CurEnv);
E 419
I 419
			{
				ep = xalloc(strlen(optarg) + 1);
				cleanstrcpy(ep, optarg, MAXNAME);
				define('r', ep, CurEnv);
			}
E 419
E 356
E 266
			break;

E 265
I 46
D 140
		  case 't':	/* read recipients from message */
			GrabTo = TRUE;
			break;

I 61
D 98
		  case 'D':	/* run as a daemon */
E 98
I 98
		  case 'b':	/* operations mode */
			Mode = p[2];
			switch (Mode)
			{
			  case MD_DAEMON:	/* run as a daemon */
E 98
I 86
#ifdef DAEMON
E 86
D 98
			Daemon = TRUE;
D 62
			MailBack = TRUE;
E 62
I 62
D 86
			/* explicit fall-through */
E 86
I 86
D 90
#else
E 90
I 90
			ArpaMode = Smtp = TRUE;
E 98
I 98
				ArpaMode = Smtp = TRUE;
E 98
#else DAEMON
E 90
D 98
			syserr("Daemon mode not implemented");
E 98
I 98
				syserr("Daemon mode not implemented");
E 98
#endif DAEMON
I 98
				break;

			  case '\0':	/* default: do full delivery */
				Mode = MD_DEFAULT;
				/* fall through....... */

			  case MD_DELIVER:	/* do everything (default) */
			  case MD_FORK:		/* fork after verification */
			  case MD_QUEUE:	/* queue only */
			  case MD_VERIFY:	/* verify only */
				break;

			  default:
				syserr("Unknown operation mode -b%c", Mode);
				exit(EX_USAGE);
			}
E 98
			break;
E 86

E 140
D 70
		  case 'p':	/* run SMTP protocol */
			Smtp = TRUE;
			ArpaMode = ARPA_SMTP;
E 62
			break;

E 70
I 66
		  case 'q':	/* run queue files at intervals */
I 76
# ifdef QUEUE
I 227
D 254
			if (getuid() != 0) {
				usrerr("Permission denied");
				exit (EX_USAGE);
E 254
I 254
D 283
			if (getuid() != 0)
			{
				struct stat stbuf;

				/* check to see if we own the queue directory */
				if (stat(QueueDir, &stbuf) < 0)
					syserr("main: cannot stat %s", QueueDir);
				if (stbuf.st_uid != getuid())
				{
					/* nope, really a botch */
					usrerr("Permission denied");
					exit (EX_NOPERM);
				}
E 254
			}
E 283
			(void) unsetenv("HOSTALIASES");
I 260
			FullName = NULL;
E 260
E 227
E 76
I 67
			queuemode = TRUE;
E 67
D 91
			QueueIntvl = atoi(&p[1]);
E 91
I 91
D 267
			QueueIntvl = convtime(&p[2]);
E 267
I 267
D 299
			QueueIntvl = convtime(optarg);
E 299
I 299
			switch (optarg[0])
			{
			  case 'I':
				QueueLimitId = newstr(&optarg[1]);
				break;

			  case 'R':
				QueueLimitRecipient = newstr(&optarg[1]);
				break;

			  case 'S':
				QueueLimitSender = newstr(&optarg[1]);
				break;

			  default:
D 314
				QueueIntvl = convtime(optarg);
E 314
I 314
				QueueIntvl = convtime(optarg, 'm');
E 314
				break;
			}
E 299
E 267
E 91
I 76
D 263
# else QUEUE
E 263
I 263
# else /* QUEUE */
E 263
D 226
			syserr("I don't know about queues");
E 226
I 226
			usrerr("I don't know about queues");
			ExitStat = EX_USAGE;
E 226
D 263
# endif QUEUE
E 263
I 263
# endif /* QUEUE */
E 263
E 76
D 67
			if (QueueIntvl == 0)
				QueueIntvl = 60*60;
E 67
			break;

I 81
D 98
		  case 'p':	/* fork politely after initial verification */
			ForkOff = TRUE;
			break;

E 98
D 85
		  case 'o':	/* take old-style headers (no commas) */
			OldStyle = TRUE;
E 85
I 85
D 140
		  case 'o':	/* take new-style headers (with commas) */
D 94
			OldStyle = FALSE;
E 94
I 94
			CurEnv->e_oldstyle = FALSE;
E 140
I 140
		  case 't':	/* read recipients from message */
			GrabTo = TRUE;
E 140
E 94
E 85
			break;

I 341
		  case 'X':	/* traffic log file */
I 486
			endpwent();
E 486
I 431
			setgid(RealGid);
E 431
D 342
			setuid(getuid());
E 342
I 342
			setuid(RealUid);
E 342
			TrafficLogFile = fopen(optarg, "a");
			if (TrafficLogFile == NULL)
			{
				syserr("cannot open %s", optarg);
				break;
			}
#ifdef HASSETVBUF
D 343
			setvbuf(TrafficLogFile, NULL, _IOLBF, BUFSIZ);
E 343
I 343
			setvbuf(TrafficLogFile, NULL, _IOLBF, 0);
E 343
#else
			setlinebuf(TrafficLogFile);
#endif
			break;

E 341
I 153
D 155
		  case 'Z':	/* freeze the configuration file */
			dofreeze = TRUE;
			break;

E 155
E 153
E 81
E 66
E 61
E 46
D 140
		  default:
			/* at Eric Schmidt's suggestion, this will not be an error....
			syserr("Unknown flag %s", p);
			... seems that upward compatibility will be easier. */
E 140
I 140
			/* compatibility flags */
D 157
		  case 'b':	/* operations mode */
E 157
		  case 'c':	/* connect to non-local mailers */
D 279
		  case 'e':	/* error message disposition */
E 279
		  case 'i':	/* don't let dot stop me */
		  case 'm':	/* send to me too */
		  case 'T':	/* set timeout interval */
		  case 'v':	/* give blow-by-blow description */
D 267
			setoption(p[1], &p[2], FALSE, TRUE);
E 267
I 267
D 269
			setoption(j, optarg, FALSE, TRUE);
E 269
I 269
D 312
			setoption(j, "T", FALSE, TRUE);
E 312
I 312
			setoption(j, "T", FALSE, TRUE, CurEnv);
E 312
I 279
			break;

		  case 'e':	/* error message disposition */
I 346
D 414
# if defined(ultrix)
E 414
		  case 'M':	/* define macro */
D 414
# endif
E 414
E 346
D 312
			setoption(j, optarg, FALSE, TRUE);
E 312
I 312
			setoption(j, optarg, FALSE, TRUE, CurEnv);
E 312
E 279
E 269
E 267
E 140
			break;
I 140

		  case 's':	/* save From lines in headers */
D 267
			setoption('f', &p[2], FALSE, TRUE);
E 267
I 267
D 269
			setoption('f', optarg, FALSE, TRUE);
E 269
I 269
D 312
			setoption('f', "T", FALSE, TRUE);
E 312
I 312
			setoption('f', "T", FALSE, TRUE, CurEnv);
E 312
E 269
E 267
			break;
I 155

# ifdef DBM
		  case 'I':	/* initialize alias DBM file */
D 157
			setoption('b', "i", FALSE, TRUE);
E 157
I 157
			OpMode = MD_INITALIAS;
E 157
			break;
D 244
# endif DBM
E 244
I 244
# endif /* DBM */
D 294

		  case 'R':	/* log raw recipient info */
D 267
			p += 2;
			if (*p == '\0' && ((p = *++av) == NULL || *p == '-'))
			{
				usrerr("Bad -R flag");
				ExitStat = EX_USAGE;
				av--;
				break;
			}
			RcptLogFile = newstr(p);
E 267
I 267
			RcptLogFile = newstr(optarg);
E 267
			break;
E 294
I 267

I 310
D 313
# ifdef __alpha
E 313
I 313
D 341
# ifdef __osf__
E 313
		  case 'x':	/* random flag that DEC OSF/1 mailx passes */
E 341
I 341
# if defined(__osf__) || defined(_AIX3)
		  case 'x':	/* random flag that OSF/1 & AIX mailx passes */
I 375
D 409
			break;
# endif
# if defined(NeXT)
		  case 'O':	/* random flag that NeXT Mail.app passes */
E 409
E 375
E 341
			break;
# endif
I 444
# if defined(sony_news)
		  case 'E':
		  case 'J':	/* ignore flags for Japanese code conversion
				   impremented on Sony NEWS */
			break;
# endif
E 444

E 310
		  default:
			ExitStat = EX_USAGE;
			finis();
			break;
E 267
E 244
E 155
E 140
		}
I 268
	}
E 268
D 267
	}
E 267
I 267
	av += optind;
E 267
I 237
D 338

#ifdef NAMED_BIND
D 283
	if (tTd(8, 1))
E 283
I 283
	if (tTd(8, 8))
E 283
		_res.options |= RES_DEBUG;
#endif
E 338
E 237

D 39
	if (from != NULL && ArpaFmt)
		syserr("-f and -a are mutually exclusive");
I 24

E 39
I 25
	/*
D 44
	**  Read control file and initialize system macros.
	**	Collect should be called first, so that the time
	**	corresponds to the time that the messages starts
	**	getting sent, rather than when it is first composed.
E 44
I 44
D 61
	**  Read control file.
E 61
I 61
D 118
	**  Read system control file.
E 118
I 118
	**  Do basic initialization.
	**	Read system control file.
E 118
I 65
	**	Extract special fields for local use.
E 65
E 61
E 44
	*/

I 377
D 478
#ifdef XDEBUG
E 478
I 478
#if XDEBUG
E 478
	checkfd012("before readcf");
#endif
I 458
	vendor_pre_defaults(CurEnv);
E 458
E 377
I 194
D 199
	if (!safecf)
	{
		setgid(getrgid());
		setuid(getruid());
	}
E 199
E 194
I 127
D 153
# ifdef LOG
D 131
	if (LogLevel > 8)
E 131
I 131
	if (LogLevel > 10)
E 131
		syslog(LOG_DEBUG, "entered, uid=%d, pid=%d", getuid(), getpid());
# endif LOG
I 140
	readcf(ConfFile, safecf);
E 153
I 153
D 169
	if (pass <= 1)
	{
D 155
		if (!safecf || dofreeze || !thaw())
E 155
I 155
D 157
		if (!safecf || Mode == MD_FREEZE || !thaw())
E 157
I 157
D 161
		if (!safecf || OpMode == MD_FREEZE || !thaw())
E 161
I 161
		if (!safecf || OpMode == MD_FREEZE || !thaw(FreezeFile))
E 161
E 157
E 155
			readcf(ConfFile, safecf);
		else
			goto crackargs;
	}
E 169
I 169
D 202
	if (!safecf || OpMode == MD_FREEZE || readconfig)
		readcf(ConfFile, safecf);
E 202
I 202
D 361
	if (OpMode == MD_FREEZE || readconfig)
D 255
		readcf(ConfFile);
E 255
I 255
D 257
		readcf(ConfFile, safecf);
E 257
I 257
		readcf(ConfFile, safecf, CurEnv);
E 361
I 361
D 366
	readcf(ConfFile, safecf, CurEnv);
E 366
I 366
	readcf(getcfname(), safecf, CurEnv);
I 458
	vendor_post_defaults(CurEnv);
I 462

	/* set up the $=m class now, after .cf has a chance to redefine $m */
	expand("\201m", jbuf, sizeof jbuf, CurEnv);
	setclass('m', jbuf);
E 462
E 458
E 366
E 361
I 358

	if (tTd(0, 1))
	{
D 359
		printf("SYSTEM IDENTITY (after readcf):\n");
		printf("\t    (short domain name) $w = %s\n",
			macvalue('w', CurEnv));
		printf("\t(canonical domain name) $j = %s\n",
			macvalue('j', CurEnv));
		printf("\t       (subdomain name) $m = %s\n",
			macvalue('m', CurEnv));
		printf("\t            (node name) $k = %s\n",
			macvalue('k', CurEnv));
E 359
I 359
D 475
		printf("SYSTEM IDENTITY (after readcf):");
		printf("\n\t    (short domain name) $w = ");
E 475
I 475
		printf("\n============ SYSTEM IDENTITY (after readcf) ============");
		printf("\n      (short domain name) $w = ");
E 475
		xputs(macvalue('w', CurEnv));
D 475
		printf("\n\t(canonical domain name) $j = ");
E 475
I 475
		printf("\n  (canonical domain name) $j = ");
E 475
		xputs(macvalue('j', CurEnv));
D 475
		printf("\n\t       (subdomain name) $m = ");
E 475
I 475
		printf("\n         (subdomain name) $m = ");
E 475
		xputs(macvalue('m', CurEnv));
D 475
		printf("\n\t            (node name) $k = ");
E 475
I 475
		printf("\n              (node name) $k = ");
E 475
		xputs(macvalue('k', CurEnv));
D 475
		printf("\n");
E 475
I 475
		printf("\n========================================================\n\n");
E 475
E 359
	}
I 369

	/*
I 428
	**  Initialize name server if it is going to be used.
	*/

#if NAMED_BIND
	if (!bitset(RES_INIT, _res.options))
		res_init();
#endif

	/*
E 428
I 417
	**  Initialize name server if it is going to be used.
	*/

#if NAMED_BIND
	if (UseNameServer && !bitset(RES_INIT, _res.options))
		res_init();
#endif

	/*
E 417
	**  Process authorization warnings from command line.
	*/

	if (warn_C_flag)
		auth_warning(CurEnv, "Processed by %s with -C %s",
			RealUserName, ConfFile);
I 370
D 418
/*
E 370
	if (warn_f_flag != '\0')
E 418
I 418
D 467
	if (warn_f_flag != '\0' &&
D 425
	    stab(RealUserName, ST_TRUSTED, ST_FIND) == NULL)
E 425
I 425
	    ((st = stab(RealUserName, ST_CLASS, ST_FIND)) == NULL ||
	     !bitnset('t', st->s_class)))
E 467
I 467
	if (warn_f_flag != '\0' && !wordinclass(RealUserName, 't'))
E 467
E 425
E 418
		auth_warning(CurEnv, "%s set sender to %s using -%c",
			RealUserName, from, warn_f_flag);
I 370
D 418
*/
E 418
E 370
	if (Warn_Q_option)
		auth_warning(CurEnv, "Processed from queue %s", QueueDir);
E 369
E 358
E 257
E 255
E 202

I 400
	/* supress error printing if errors mailed back or whatever */
	if (CurEnv->e_errormode != EM_PRINT)
		HoldErrs = TRUE;

E 400
I 258
D 259
#ifdef SYSTEM5
E 259
I 259
D 347
#ifdef SYS5TZ
E 347
E 259
	/* Enforce use of local time (null string overrides this) */
	if (TimeZoneSpec == NULL)
		unsetenv("TZ");
	else if (TimeZoneSpec[0] != '\0')
D 347
	{
		p = xalloc(strlen(TimeZoneSpec) + 4);
		(void) strcpy(p, "TZ=");
		(void) strcat(p, TimeZoneSpec);
		putenv(p);
	}
#endif
E 347
I 347
D 351
		setenv("TZ", TimeZoneSpec, 1);
E 351
I 351
D 455
	{
		char **evp = UserEnviron;
		char tzbuf[100];
E 351
E 347

I 351
		strcpy(tzbuf, "TZ=");
		strcpy(&tzbuf[3], TimeZoneSpec);

		while (*evp != NULL && strncmp(*evp, "TZ=", 3) != 0)
			evp++;
		if (*evp == NULL)
		{
			*evp++ = newstr(tzbuf);
			*evp = NULL;
		}
		else
			*evp++ = newstr(tzbuf);
	}
E 455
I 455
D 457
		setenv("TZ", TimeZoneSpec, TRUE);
E 457
I 457
		setuserenv("TZ", TimeZoneSpec);
E 457
E 455
I 444
	tzset();
E 444

E 351
E 258
I 250
	if (ConfigLevel > MAXCONFIGLEVEL)
	{
		syserr("Warning: .cf version level (%d) exceeds program functionality (%d)",
			ConfigLevel, MAXCONFIGLEVEL);
	}
I 353

	if (MeToo)
		BlankEnvelope.e_flags |= EF_METOO;
E 353
I 341

D 352

E 352
E 341
I 283
D 436
# ifdef QUEUE
D 342
	if (queuemode && getuid() != 0)
E 342
I 342
D 364
	if (queuemode && RealUid != 0)
E 364
I 364
	if (queuemode && RealUid != 0 && bitset(PRIV_RESTRICTQRUN, PrivacyFlags))
E 364
E 342
	{
		struct stat stbuf;

		/* check to see if we own the queue directory */
		if (stat(QueueDir, &stbuf) < 0)
			syserr("main: cannot stat %s", QueueDir);
D 342
		if (stbuf.st_uid != getuid())
E 342
I 342
		if (stbuf.st_uid != RealUid)
E 342
		{
			/* nope, really a botch */
D 364
			usrerr("Permission denied");
E 364
I 364
			usrerr("You do not have permission to process the queue");
E 364
			exit (EX_NOPERM);
		}
	}
# endif /* QUEUE */
I 304

E 436
E 304
E 283
E 250
E 169
D 155
	if (dofreeze)
E 155
I 155
D 157
	switch (Mode)
E 157
I 157
	switch (OpMode)
E 157
E 155
	{
I 296
D 361
# ifdef FROZENCONFIG
E 296
I 155
	  case MD_FREEZE:
I 186
		/* this is critical to avoid forgeries of the frozen config */
D 201
		setuid(getuid());
E 201
D 205
		setgid(getgid());
I 201
		setuid(getuid());
E 205
I 205
D 342
		(void) setgid(getgid());
		(void) setuid(getuid());
E 342
I 342
		(void) setgid(RealGid);
		(void) setuid(RealUid);
E 342
E 205
E 201

		/* freeze the configuration */
E 186
E 155
D 161
		freeze();
E 161
I 161
		freeze(FreezeFile);
E 161
		exit(EX_OK);
I 296
# endif
E 296
I 155

E 361
D 415
	  case MD_INITALIAS:
		Verbose = TRUE;
		break;
I 245

E 415
	  case MD_DAEMON:
		/* remove things that don't make sense in daemon mode */
		FullName = NULL;
I 471
		GrabTo = FALSE;
E 471
I 415

		/* arrange to restart on hangup signal */
		setsignal(SIGHUP, sighup);
E 415
I 298
		break;
I 415

	  case MD_INITALIAS:
		Verbose = TRUE;
		/* fall through... */

	  default:
		/* arrange to exit cleanly on hangup signal */
		setsignal(SIGHUP, intsig);
		break;
E 415
I 313
D 390

	  case MD_SMTP:
		if (RealUid != 0)
			auth_warning(CurEnv,
				"%s owned process doing -bs",
D 321
				realuser);
E 321
I 321
				RealUserName);
E 321
		break;
E 390
E 313
D 304

	  default:
		/* find our real host name */
		p = getrealhostname(STDIN_FILENO);
		if (p != NULL)
			RealHostName = newstr(p);
		else
			RealHostName = "localhost";
E 298
		break;
E 304
E 245
D 168

	  case MD_PRINT:
		usrerr("mailq mode not yet implemented");
		finis();
E 168
E 155
	}
I 423

	/* full names can't have newlines */
	if (FullName != NULL && strchr(FullName, '\n') != NULL)
D 428
D 430
		FullName = newstr(denlstring(FullName));
E 430
I 430
D 434
		FullName = newstr(denlstring(FullName, TRUE));
E 434
E 430
E 428
I 428
D 433
		FullName = newstr(denlstring(FullName, TRUE));
E 433
I 433
		FullName = newstr(denlstring(FullName, TRUE, TRUE));
E 433
E 428
E 423
I 304

D 313
	/*
	**  Find our real host name for future logging.
	*/

	p = getrealhostname(STDIN_FILENO);
	if (p != NULL)
		RealHostName = newstr(p);
	else
		RealHostName = "localhost";
E 304
E 153
E 140
E 127
I 27
D 44
	/* process id */
E 27
D 34
	sprintf(pbuf, "%d", getpid());
E 34
I 34
	(void) sprintf(pbuf, "%d", getpid());
E 34
	define('p', pbuf);
I 27

	/* hop count */
E 27
D 34
	sprintf(cbuf, "%d", HopCount);
E 34
I 34
	(void) sprintf(cbuf, "%d", HopCount);
E 34
	define('c', cbuf);
I 27

	/* time as integer, unix time, arpa time */
E 27
D 34
	time(&CurTime);
	sprintf(tbuf, "%ld", &CurTime);
E 34
I 34
	(void) time(&CurTime);
	(void) sprintf(tbuf, "%ld", &CurTime);
E 34
	define('t', tbuf);
D 34
	strcpy(dbuf, ctime(&CurTime));
E 34
I 34
	(void) strcpy(dbuf, ctime(&CurTime));
E 34
	*index(dbuf, '\n') = '\0';
	define('d', dbuf);
I 27
	define('a', arpadate(dbuf));
E 27

I 27
	/* version */
	define('v', Version);
I 42

	/* tty name */
	p = ttyname(2);
	if (p != NULL)
	{
		if (rindex(p, '/') != NULL)
			p = rindex(p, '/') + 1;
		strcpy(ybuf, p);
		define('y', ybuf);
	}
E 42

E 44
E 27
E 25
D 45
	readcf(cfname);
E 45
I 45
D 49
	readcf(cfname, safecf);
E 49
I 49
D 138
	readcf(ConfFile, safecf);
E 138
I 66
D 132
	initsys();
E 132
E 66
I 65

E 313
I 148
	/* do heuristic mode adjustment */
	if (Verbose)
D 157
		setoption('b', "a", TRUE, FALSE);
E 157
I 157
	{
		/* turn off noconnect option */
D 312
		setoption('c', "F", TRUE, FALSE);
E 312
I 312
		setoption('c', "F", TRUE, FALSE, CurEnv);
E 312
E 157

I 157
		/* turn on interactive delivery */
D 312
		setoption('d', "", TRUE, FALSE);
E 312
I 312
		setoption('d', "", TRUE, FALSE, CurEnv);
E 312
	}

I 341
	if (ConfigLevel < 3)
	{
		UseErrorsTo = TRUE;
	}

E 341
E 157
E 148
	/* our name for SMTP codes */
E 65
I 63
D 95
	(void) expand("$i", ibuf, &ibuf[sizeof ibuf - 1]);
E 95
I 95
D 119
	expand("$i", ibuf, &ibuf[sizeof ibuf - 1], CurEnv);
E 95
	HostName = ibuf;
E 119
I 119
D 191
	expand("$j", jbuf, &jbuf[sizeof jbuf - 1], CurEnv);
E 191
I 191
D 289
	expand("\001j", jbuf, &jbuf[sizeof jbuf - 1], CurEnv);
E 289
I 289
D 438
	expand("\201j", jbuf, &jbuf[sizeof jbuf - 1], CurEnv);
E 438
I 438
	expand("\201j", jbuf, sizeof jbuf, CurEnv);
E 438
E 289
E 191
D 212
	HostName = jbuf;
E 212
I 212
	MyHostName = jbuf;
I 399
	if (strchr(jbuf, '.') == NULL)
		message("WARNING: local host name (%s) is not qualified; fix $j in config file",
			jbuf);
E 399
I 352

	/* make certain that this name is part of the $=w class */
	setclass('w', MyHostName);
E 352
E 212
E 119
E 63
E 49
E 45
I 33

I 65
D 273
	/* the indices of local and program mailers */
E 273
I 273
	/* the indices of built-in mailers */
E 273
	st = stab("local", ST_MAILER, ST_FIND);
	if (st == NULL)
		syserr("No local mailer defined");
	else
		LocalMailer = st->s_mailer;
I 273

E 273
	st = stab("prog", ST_MAILER, ST_FIND);
	if (st == NULL)
		syserr("No prog mailer defined");
	else
I 464
	{
E 464
		ProgMailer = st->s_mailer;
I 464
		clrbitn(M_MUSER, ProgMailer->m_flags);
	}
E 464
I 273

	st = stab("*file*", ST_MAILER, ST_FIND);
	if (st == NULL)
		syserr("No *file* mailer defined");
	else
I 464
	{
E 464
		FileMailer = st->s_mailer;
I 464
		clrbitn(M_MUSER, FileMailer->m_flags);
	}
E 464

	st = stab("*include*", ST_MAILER, ST_FIND);
	if (st == NULL)
		syserr("No *include* mailer defined");
	else
		InclMailer = st->s_mailer;

I 401
D 447
	/* heuristic tweaking of local mailer for back compat */
E 447
	if (ConfigLevel < 6)
	{
I 447
D 450
		/* need config support for group:; handling */
		ColonOkInAddr = TRUE;

E 450
		/* heuristic tweaking of local mailer for back compat */
E 447
		if (LocalMailer != NULL)
		{
			setbitn(M_ALIASABLE, LocalMailer->m_flags);
			setbitn(M_HASPWENT, LocalMailer->m_flags);
			setbitn(M_TRYRULESET5, LocalMailer->m_flags);
			setbitn(M_CHECKINCLUDE, LocalMailer->m_flags);
			setbitn(M_CHECKPROG, LocalMailer->m_flags);
			setbitn(M_CHECKFILE, LocalMailer->m_flags);
			setbitn(M_CHECKUDB, LocalMailer->m_flags);
		}
		if (ProgMailer != NULL)
			setbitn(M_RUNASRCPT, ProgMailer->m_flags);
		if (FileMailer != NULL)
			setbitn(M_RUNASRCPT, FileMailer->m_flags);
I 455

		/* propogate some envariables into children */
D 456
		setuserenv("AGENT", "sendmail");
E 456
		setuserenv("ISP", NULL);
		setuserenv("SYSTYPE", NULL);
E 455
	}
E 401
E 273

I 455
D 456
	/* guarantee non-empty environment to children */
	if (UserEnviron[0] == NULL)
		setuserenv("AGENT", "sendmail");

E 456
E 455
I 437
D 452
	/* initialize standard MIME classes */
	setclass('n', "message/rfc822");
	setclass('n', "message/partial");
	setclass('n', "message/external-body");
E 452
I 452
	/* MIME Content-Types that cannot be transfer encoded */
E 452
	setclass('n', "multipart/signed");
I 452

I 481
	/* MIME message/* subtypes that can be treated as messages */
	setclass('m', "rfc822");

E 481
	/* MIME Content-Transfer-Encodings that can be encoded */
	setclass('e', "7bit");
	setclass('e', "8bit");
	setclass('e', "binary");
E 452

E 437
I 134
	/* operate in queue directory */
D 354
	if (chdir(QueueDir) < 0)
E 354
I 354
	if (OpMode != MD_TEST && chdir(QueueDir) < 0)
E 354
	{
		syserr("cannot chdir(%s)", QueueDir);
D 341
		exit(EX_SOFTWARE);
E 341
I 341
		ExitStat = EX_SOFTWARE;
E 341
I 168
	}
I 436

# ifdef QUEUE
	if (queuemode && RealUid != 0 && bitset(PRIV_RESTRICTQRUN, PrivacyFlags))
	{
		struct stat stbuf;

		/* check to see if we own the queue directory */
		if (stat(".", &stbuf) < 0)
			syserr("main: cannot stat %s", QueueDir);
		if (stbuf.st_uid != RealUid)
		{
			/* nope, really a botch */
			usrerr("You do not have permission to process the queue");
			exit (EX_NOPERM);
		}
	}
# endif /* QUEUE */
E 436

I 303
	/* if we've had errors so far, exit now */
D 341
	if (ExitStat != EX_OK)
E 341
I 341
	if (ExitStat != EX_OK && OpMode != MD_TEST)
I 342
	{
I 486
		endpwent();
E 486
		setuid(RealUid);
E 342
E 341
		exit(ExitStat);
I 342
	}
I 377

D 478
#ifdef XDEBUG
E 478
I 478
#if XDEBUG
E 478
	checkfd012("before main() initmaps");
#endif
E 377
E 342

E 303
	/*
D 188
	**  If printing the queue, go off and do that.
E 188
I 188
	**  Do operation-mode-dependent initialization.
E 188
	*/

D 188
	if (OpMode == MD_PRINT)
E 188
I 188
	switch (OpMode)
E 188
	{
I 188
	  case MD_PRINT:
		/* print the queue */
E 188
I 176
#ifdef QUEUE
E 176
		dropenvelope(CurEnv);
		printqueue();
I 486
		endpwent();
E 486
I 342
		setuid(RealUid);
E 342
		exit(EX_OK);
I 176
D 263
#else QUEUE
E 263
I 263
#else /* QUEUE */
E 263
		usrerr("No queue to print");
		finis();
D 263
#endif QUEUE
E 263
I 263
#endif /* QUEUE */
E 263
E 176
E 168
D 188
	}
E 188

E 134
E 65
I 59
D 61
# ifndef V6
E 59
D 53
# ifndef V6
E 53
	p = getenv("HOME");
	if (p != NULL)
	{
		char cfbuf[60];
E 61
I 61
D 188
	/*
	**  Initialize aliases.
	*/
E 61

D 61
		define('z', p);
D 34
		expand("$z/.mailcf", cfbuf, &cfbuf[sizeof cfbuf - 1]);
E 34
I 34
		(void) expand("$z/.mailcf", cfbuf, &cfbuf[sizeof cfbuf - 1]);
E 34
		if (access(cfbuf, 2) == 0)
D 45
			readcf(cfbuf);
E 45
I 45
			readcf(cfbuf, FALSE);
E 45
	}
I 59
# endif V6
E 59
D 53
# endif V6
E 53
I 35

E 61
I 36
D 37
	initaliases(aliasname);
E 37
I 37
D 49
	initaliases(aliasname, aliasinit);
E 49
I 49
D 155
	initaliases(AliasFile, aliasinit);
E 155
I 155
D 157
	initaliases(AliasFile, Mode == MD_INITALIAS);
E 157
I 157
	initaliases(AliasFile, OpMode == MD_INITALIAS);
E 157
E 155
E 49
D 164
# ifdef DBM
E 164
D 155
	if (aliasinit)
E 155
I 155
D 157
	if (Mode == MD_INITALIAS)
E 157
I 157
	if (OpMode == MD_INITALIAS)
E 188
I 188
	  case MD_INITALIAS:
		/* initialize alias database */
D 257
		initaliases(AliasFile, TRUE);
E 257
I 257
D 330
		initaliases(AliasFile, TRUE, CurEnv);
E 330
I 330
D 337
		initaliases(TRUE, CurEnv);
E 337
I 337
		initmaps(TRUE, CurEnv);
I 486
		endpwent();
E 486
I 342
		setuid(RealUid);
E 342
E 337
E 330
E 257
E 188
E 157
E 155
		exit(EX_OK);
I 188

	  case MD_DAEMON:
I 449
	  case MD_SMTP:
E 449
		/* don't open alias database -- done in srvrsmtp */
		break;

	  default:
		/* open the alias database */
D 257
		initaliases(AliasFile, FALSE);
E 257
I 257
D 330
		initaliases(AliasFile, FALSE, CurEnv);
E 330
I 330
D 337
		initaliases(FALSE, CurEnv);
E 337
I 337
		initmaps(FALSE, CurEnv);
E 337
E 330
E 257
		break;
	}
E 188
D 164
# endif DBM
E 164
E 37

E 36
D 229
# ifdef DEBUG
E 229
D 116
	if (Debug > 15)
E 116
I 116
	if (tTd(0, 15))
E 116
	{
I 61
		/* print configuration table (or at least part of it) */
E 61
D 440
		printrules();
E 440
I 440
		if (tTd(0, 90))
			printrules();
E 440
		for (i = 0; i < MAXMAILERS; i++)
		{
D 440
			register struct mailer *m = Mailer[i];
I 177
			int j;
E 177

			if (m == NULL)
				continue;
D 92
			printf("mailer %d: %s %s %o %s\n", i, m->m_name,
E 92
I 92
D 129
			printf("mailer %d: %s %s %lo %s\n", i, m->m_name,
E 92
			       m->m_mailer, m->m_flags, m->m_from);
E 129
I 129
D 174
			printf("mailer %d: %s %s %lo %d %d\n", i, m->m_name,
			       m->m_mailer, m->m_flags, m->m_s_rwset, m->m_r_rwset);
E 174
I 174
D 177
			printf("mailer %d (%s): P=%s F=%lo S=%d R=%d E=", i,
			       m->m_name, m->m_mailer, m->m_flags, m->m_s_rwset,
			       m->m_r_rwset);
E 177
I 177
D 178
			printf("mailer %d (%s): P=%s S=%d R=%d F=", i, m->m_name,
				m->m_mailer, m->m_s_rwset, m->m_r_rwset);
E 178
I 178
D 285
			printf("mailer %d (%s): P=%s S=%d R=%d M=%ld F=", i, m->m_name,
				m->m_mailer, m->m_s_rwset, m->m_r_rwset,
				m->m_maxsize);
E 285
I 285
D 408
			printf("mailer %d (%s): P=%s S=%d/%d R=%d/%d M=%ld F=", i, m->m_name,
E 408
I 408
D 411
			printf("mailer %d (%s): P=%s S=%d/%d R=%d/%d M=%ld U=%d:%d F=",
				i, m->m_name,
E 408
				m->m_mailer, m->m_se_rwset, m->m_sh_rwset,
D 408
				m->m_re_rwset, m->m_rh_rwset, m->m_maxsize);
E 408
I 408
				m->m_re_rwset, m->m_rh_rwset, m->m_maxsize,
				m->m_uid, m->m_gid);
E 408
E 285
E 178
			for (j = '\0'; j <= '\177'; j++)
				if (bitnset(j, m->m_flags))
D 205
					putchar(j);
E 205
I 205
					(void) putchar(j);
E 205
D 410
			printf(" E=");
E 410
I 410
			printf("L=%d E=", m->m_linelimit);
E 410
E 177
			xputs(m->m_eol);
I 410
			if (m->m_defcharset != NULL)
				printf(" C=%s", m->m_defcharset);
			if (m->m_mtstype != NULL)
				printf(" T=%s", m->m_mtstype);
E 410
I 249
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
E 249
			printf("\n");
E 411
I 411
			printmailer(m);
E 440
I 440
			if (Mailer[i] != NULL)
				printmailer(Mailer[i]);
E 440
E 411
E 174
E 129
		}
	}
D 229
# endif DEBUG
E 229
E 35
E 33
E 24

I 142
	/*
I 151
	**  Switch to the main envelope.
	*/

D 295
	CurEnv = newenvelope(&MainEnvelope);
E 295
I 295
	CurEnv = newenvelope(&MainEnvelope, CurEnv);
E 295
I 156
D 162
	MainEnvelope.e_oldstyle = BlankEnvelope.e_oldstyle;
E 162
I 162
	MainEnvelope.e_flags = BlankEnvelope.e_flags;
E 162
E 156

	/*
E 151
	**  If test mode, read addresses from stdin and process.
	*/

D 157
	if (Mode == MD_TEST)
E 157
I 157
	if (OpMode == MD_TEST)
E 157
	{
I 262
D 286
		bool terminal = isatty(fileno(stdin));
E 286
E 262
		char buf[MAXLINE];

D 144
		printf("TEST MODE\nEnter <ruleset> <address>\n");
E 144
I 144
D 249
		printf("ADDRESS TEST MODE\nEnter <ruleset> <address>\n");
E 249
I 249
D 262
		printf("ADDRESS TEST MODE (ruleset 3 NOT automatically invoked)\n");
		printf("Enter <ruleset> <address>\n");
E 262
I 262
D 286
		if (terminal)
E 286
I 286
		if (isatty(fileno(stdin)))
			Verbose = TRUE;

		if (Verbose)
E 286
		{
			printf("ADDRESS TEST MODE (ruleset 3 NOT automatically invoked)\n");
			printf("Enter <ruleset> <address>\n");
		}
E 262
E 249
E 144
		for (;;)
		{
I 466
			extern void testmodeline __P((char *, ENVELOPE *));

E 466
D 445
			register char **pvp;
I 144
			char *q;
E 144
D 198
			extern char **prescan();
E 198
D 163
			extern char **rewrite();
E 163
I 143
D 144
			char *q;
E 144
I 144
D 301
			extern char *DelimChar;
E 301
I 301
			auto char *delimptr;
E 301
I 271
			extern bool invalidaddr();
I 372
			extern char *crackaddr();
E 372
E 271
E 144
E 143

E 445
D 262
			printf("> ");
E 262
I 262
D 286
			if (terminal)
E 286
I 286
			if (Verbose)
E 286
				printf("> ");
E 262
D 205
			fflush(stdout);
E 205
I 205
			(void) fflush(stdout);
E 205
			if (fgets(buf, sizeof buf, stdin) == NULL)
				finis();
I 463
			p = strchr(buf, '\n');
			if (p != NULL)
				*p = '\0';
E 463
I 262
D 286
			if (!terminal)
E 286
I 286
			if (!Verbose)
E 286
D 463
				printf("> %s", buf);
E 463
I 463
				printf("> %s\n", buf);
E 463
D 372
			if (buf[0] == '#')
E 372
I 372
D 445
			switch (buf[0])
			{
			  case '#':
E 372
				continue;
I 372

D 398
#ifdef MAYBENEXTRELEASE
			  case 'C':		/* try crackaddr */
E 398
I 398
			  case '?':		/* try crackaddr */
E 398
			  	q = crackaddr(&buf[1]);
			  	xputs(q);
			  	printf("\n");
			  	continue;
D 398
#endif
E 398
I 398

			  case '.':		/* config-style settings */
				switch (buf[1])
				{
				  case 'D':
D 407
					define(buf[2], &buf[3], CurEnv);
E 407
I 407
					define(buf[2], newstr(&buf[3]), CurEnv);
E 407
					break;

				  case 'C':
					setclass(buf[2], &buf[3]);
					break;

I 407
				  case 'S':		/* dump rule set */
					{
						int rs;
						struct rewrite *rw;
I 426
						char *cp;
						STAB *s;
E 426

D 426
						if (buf[2] == '\n')
E 426
I 426
						if ((cp = strchr(buf, '\n')) != NULL)
							*cp = '\0';
						if (cp == buf+2)
E 426
							continue;
D 426
						rs = atoi(&buf[2]);
E 426
I 426
						s = stab(buf+2, ST_RULESET, ST_FIND);
						if (s == NULL)
						{
							if (!isdigit(buf[2]))
								continue;
							rs = atoi(buf+2);
						}
						else
							rs = s->s_ruleset;
E 426
						if (rs < 0 || rs > MAXRWSETS)
							continue;
						if ((rw = RewriteRules[rs]) == NULL)
							continue;
						do
						{
							char **s;
							putchar('R');
							s = rw->r_lhs;
							while (*s != NULL)
							{
								xputs(*s++);
								putchar(' ');
							}
							putchar('\t');
							putchar('\t');
							s = rw->r_rhs;
							while (*s != NULL)
							{
								xputs(*s++);
								putchar(' ');
							}
							putchar('\n');
						} while (rw = rw->r_next);
					}
					break;

E 407
				  default:
					printf("Unknown config command %s", buf);
					break;
D 407
				  }
				  continue;
E 407
I 407
				}
				continue;

			  case '-':		/* set command-line-like opts */
				switch (buf[1])
				{
				  case 'd':
					if (buf[2] == '\n')
						tTflag("");
					else
						tTflag(&buf[2]);
					break;

				  default:
					printf("Unknown \"-\" command %s", buf);
					break;
				}
				continue;
E 407
E 398
			}

E 372
E 262
D 143
			for (p = buf; *p != '\0' && !isspace(*p); p++)
E 143
I 143
D 228
			for (p = buf; isspace(*p); *p++)
E 228
I 228
D 287
			for (p = buf; isspace(*p); p++)
E 287
I 287
			for (p = buf; isascii(*p) && isspace(*p); p++)
E 287
E 228
E 143
				continue;
I 143
			q = p;
D 287
			while (*p != '\0' && !isspace(*p))
E 287
I 287
			while (*p != '\0' && !(isascii(*p) && isspace(*p)))
E 287
				p++;
E 143
D 144
			while (isspace(*p))
				*p++ = '\0';
E 144
			if (*p == '\0')
I 271
			{
				printf("No address!\n");
E 271
				continue;
I 271
			}
E 271
D 144
			pvp = prescan(p, '\n');
			rewrite(pvp, 3);
D 143
			rewrite(pvp, atoi(buf));
E 143
I 143
			p = q;
			while (*p != '\0')
E 144
I 144
			*p = '\0';
I 271
D 372
			if (invalidaddr(p + 1))
E 372
I 372
			if (invalidaddr(p + 1, NULL))
E 372
D 272
			{
				printf("Invalid control characters in address\n");
E 272
				continue;
D 272
			}
E 272
E 271
			do
E 144
			{
D 144
				q = p;
				while (*p != '\0' && *p++ != ',')
E 144
I 144
D 198
				pvp = prescan(++p, ',');
E 198
I 198
D 336
				extern char **prescan();
E 336
				char pvpbuf[PSBUFSIZE];

D 301
				pvp = prescan(++p, ',', pvpbuf);
E 301
I 301
D 381
				pvp = prescan(++p, ',', pvpbuf, &delimptr);
E 381
I 381
				pvp = prescan(++p, ',', pvpbuf, sizeof pvpbuf,
D 443
					      &delimptr);
E 443
I 443
					      &delimptr, NULL);
E 443
E 381
E 301
E 198
				if (pvp == NULL)
E 144
					continue;
D 144
				rewrite(pvp, atoi(q));
			}
E 144
I 144
D 249
				rewrite(pvp, 3);
E 249
				p = q;
				while (*p != '\0')
				{
D 323
					rewrite(pvp, atoi(p));
E 323
I 323
D 324
					rewrite(pvp, atoi(p), CurEnv);
E 324
I 324
					int stat;

D 382
					stat = rewrite(pvp, atoi(p), CurEnv);
E 382
I 382
					stat = rewrite(pvp, atoi(p), 0, CurEnv);
E 382
					if (stat != EX_OK)
						printf("== Ruleset %s status %d\n",
							p, stat);
E 324
E 323
					while (*p != '\0' && *p++ != ',')
						continue;
				}
D 301
			} while (*(p = DelimChar) != '\0');
E 301
I 301
			} while (*(p = delimptr) != '\0');
E 445
I 445
			testmodeline(buf, CurEnv);
E 445
E 301
E 144
E 143
		}
	}

I 158
# ifdef QUEUE
	/*
	**  If collecting stuff from the queue, go start doing that.
	*/

D 160
	if (queuemode && OpMode != MD_DAEMON && QueueIntvl != 0)
E 160
I 160
	if (queuemode && OpMode != MD_DAEMON && QueueIntvl == 0)
E 160
	{
I 483
		(void) unsetenv("HOSTALIASES");
E 483
D 257
		runqueue(FALSE);
E 257
I 257
D 258
		runqueue(FALSE, CurEnv);
E 258
I 258
		runqueue(FALSE);
E 258
E 257
		finis();
	}
D 263
# endif QUEUE
E 263
I 263
# endif /* QUEUE */
E 263

E 158
E 142
I 132
D 133
	initsys();

E 133
E 132
I 86
D 164
#ifdef DAEMON
E 164
E 86
	/*
I 61
	**  If a daemon, wait for a request.
	**	getrequests will always return in a child.
I 91
	**	If we should also be processing the queue, start
D 107
	**	doing it in background.
E 107
I 107
	**		doing it in background.
	**	We check for any errors that might have happened
	**		during startup.
E 107
E 91
	*/

D 98
	if (Daemon)
E 98
I 98
D 147
	if (Mode == MD_DAEMON)
E 147
I 147
D 157
	if (Mode == MD_DAEMON || QueueIntvl != 0)
E 157
I 157
	if (OpMode == MD_DAEMON || QueueIntvl != 0)
E 157
E 147
E 98
I 91
	{
I 297
		char dtype[200];

E 297
I 110
D 116
		if (Debug == 0)
E 116
I 116
D 470
		if (!tTd(0, 1))
E 470
I 470
D 473
		if (!tTd(52, 100))
E 473
I 473
		if (!tTd(99, 100))
E 473
E 470
E 116
		{
I 290
D 302
			FILE *pidf;

E 302
E 290
I 112
			/* put us in background */
E 112
			i = fork();
			if (i < 0)
				syserr("daemon: cannot fork");
			if (i != 0)
				exit(0);
I 112
D 302

D 290
			/* get our pid right */
E 112
I 111
			MotherPid = getpid();
E 290
I 290
			if (OpMode == MD_DAEMON)
			{
				pidf = fopen(PidFile, "w");
				if (pidf != NULL)
				{
					fprintf(pidf, "%d\n", getpid());
					fclose(pidf);
				}
			}
E 302
E 290
I 122
D 159
# ifdef LOG
			if (LogLevel > 11)
				syslog(LOG_DEBUG, "background daemon, pid=%d",
				       MotherPid);
# endif LOG
E 159
E 122
I 112

			/* disconnect from our controlling tty */
D 159
			i = open("/dev/tty", 2);
			if (i >= 0)
			{
				(void) ioctl(i, TIOCNOTTY, 0);
				(void) close(i);
			}
			errno = 0;
E 159
I 159
D 165
			disconnect(FALSE);
E 165
I 165
D 172
			disconnect();
E 172
I 172
D 306
			disconnect(TRUE);
E 306
I 306
D 343
			disconnect(TRUE, CurEnv);
E 343
I 343
			disconnect(2, CurEnv);
E 343
E 306
E 172
E 165
E 159
E 112
E 111
		}
I 297

		dtype[0] = '\0';
		if (OpMode == MD_DAEMON)
			strcat(dtype, "+SMTP");
		if (QueueIntvl != 0)
		{
D 336
			extern char *pintvl();

E 336
			strcat(dtype, "+queueing@");
			strcat(dtype, pintvl(QueueIntvl, TRUE));
		}
		if (tTd(0, 1))
			strcat(dtype, "+debugging");

I 393
#ifdef LOG
E 393
D 305
		syslog(LOG_INFO, "starting %s daemon", dtype);
E 305
I 305
D 332
		syslog(LOG_INFO, "starting daemon: %s", dtype + 1);
E 332
I 332
		syslog(LOG_INFO, "starting daemon (%s): %s", Version, dtype + 1);
I 393
#endif
E 393
E 332
I 326
#ifdef XLA
		xla_create_file();
#endif
E 326
E 305
E 297
I 164

E 164
E 110
# ifdef QUEUE
		if (queuemode)
I 147
		{
E 147
D 257
			runqueue(TRUE);
E 257
I 257
D 258
			runqueue(TRUE, CurEnv);
E 258
I 258
			runqueue(TRUE);
E 258
E 257
I 147
D 157
			if (Mode != MD_DAEMON)
E 157
I 157
			if (OpMode != MD_DAEMON)
E 157
				for (;;)
					pause();
		}
E 147
D 263
# endif QUEUE
E 263
I 263
# endif /* QUEUE */
E 263
I 107
D 164
		checkerrors(CurEnv);
E 164
I 164
		dropenvelope(CurEnv);

#ifdef DAEMON
E 164
I 125
D 126
		dropenvelope(CurEnv);
		CurEnv->e_id = CurEnv->e_qf = CurEnv->e_df = NULL;
E 126
E 125
E 107
E 91
		getrequests();
I 113

		/* at this point we are in a child: reset state */
I 157
D 326
		OpMode = MD_SMTP;
E 326
E 157
I 126
D 164
		dropenvelope(CurEnv);
D 162
		CurEnv->e_id = CurEnv->e_qf = CurEnv->e_df = NULL;
E 126
		FatalErrors = FALSE;
E 162
I 162
		CurEnv->e_id = CurEnv->e_df = NULL;
		CurEnv->e_flags &= ~EF_FATALERRS;
E 164
I 164
D 295
		(void) newenvelope(CurEnv);
E 295
I 295
		(void) newenvelope(CurEnv, CurEnv);
I 321

		/*
		**  Get authentication data
		*/

		p = getauthinfo(fileno(InChannel));
		define('_', p, CurEnv);

E 321
E 295
E 164
E 162
D 166
		openxscrpt();
E 166
I 166
D 311
		openxscript(CurEnv);
E 311
E 166
D 133
		initsys();
E 133
E 113
I 91
D 164
	}
E 164
E 91
I 86
D 263
#endif DAEMON
E 263
I 263
#endif /* DAEMON */
E 263
I 164
	}
E 164
E 86
D 62

E 62
I 62
D 123
	
I 76
# ifdef SMTP
E 76
E 62
	/*
E 61
D 16
D 28
	** Get a temp file.
E 28
I 28
D 62
	**  Figure out the real user executing us.
I 60
	**	Getlogin can return errno != 0 on non-errors.
E 62
I 62
	**  If running SMTP protocol, start collecting and executing
	**  commands.  This will never return.
I 68
D 91
	**	If we should also be processing the queue, start
	**	doing it in background.
E 91
E 68
E 62
E 60
E 28
	*/
E 123
D 158

D 21
	p = maketemp();
E 21
I 21
D 28
	p = collect();
E 21
	if (from == NULL)
		from = p;
I 23
D 27
	if (MsgId == NULL)
		MsgId = makemsgid();
E 23
# ifdef DEBUG
	if (Debug)
D 20
		printf("Message-Id: <%s>\n", MsgId);
E 20
I 20
		printf("Message-Id: %s\n", MsgId);
E 20
# endif DEBUG
E 27

	/*
	**  Figure out who it's coming from.
E 16
I 16
	**  Find out who the person is as far as the local system is
	**  concerned.
	**
E 16
D 8
	**	If we are root or "network", then allow -f.  Otherwise,
	**	insist that we figure it out ourselves.
E 8
I 8
	**	Under certain circumstances allow the user to say who
	**	s/he is (using -f or -r).  These are:
	**	1.  The user's uid is zero (root).
	**	2.  The user's login name is "network" (mail from
	**	    a network server).
	**	3.  The user's login name is "uucp" (mail from the
	**	    uucp network).
	**	4.  The address the user is trying to claim has a
	**	    "!" character in it (since #3 doesn't do it for
	**	    us if we are dialing out).
	**	A better check to replace #3 & #4 would be if the
	**	effective uid is "UUCP" -- this would require me
	**	to rewrite getpwent to "grab" uucp as it went by,
	**	make getname more nasty, do another passwd file
	**	scan, or compile the UID of "UUCP" into the code,
	**	all of which are reprehensible.
	**
	**	Assuming all of these fail, we figure out something
	**	ourselves.
E 8
	*/

E 28
D 16
D 61
	errno = 0;
D 20
	p = getname();
	if (p == NULL || p[0] == '\0')
E 20
I 20
	p = getlogin();
I 60
	errno = 0;
E 60
	if (p == NULL)
E 61
I 61
D 62
	if (!Daemon)
E 61
E 20
E 16
I 16
	locname = getname();
	if (locname == NULL || locname[0] == '\0')
E 16
	{
I 61
		errno = 0;
		p = getlogin();
		errno = 0;
	}
	if (Daemon || p == NULL)
	{
E 61
D 20
		syserr("Who are you? (uid=%d)", getuid());
		finis();
E 20
I 20
		extern struct passwd *getpwuid();
		int uid;
E 62
I 62
D 123
	if (Smtp)
I 68
D 91
	{
I 76
# ifdef QUEUE
E 76
		if (queuemode)
			runqueue(TRUE);
I 76
# endif QUEUE
E 91
E 76
E 68
		smtp();
I 68
D 91
	}
E 91
I 76
# endif SMTP
E 76
E 68
E 62

E 123
I 76
# ifdef QUEUE
E 76
D 53
		uid = getuid();
# ifdef V6
		uid &= 0377;
# endif
E 53
I 53
D 62
		uid = getruid();
E 53
		pw = getpwuid(uid);
		if (pw == NULL)
			syserr("Who are you? (uid=%d)", uid);
		else
			p = pw->pw_name;
E 20
	}
I 20
	else
	{
		extern struct passwd *getpwnam();

		pw = getpwnam(p);
		if (pw == NULL)
			syserr("Who are you? (name=%s)", p);
	}
	if (p == NULL || p[0] == '\0' || pw == NULL)
		finis();
E 20
D 28
	errno = 0;
E 28
I 28

	realname = p;

E 62
I 61
	/*
I 66
	**  If collecting stuff from the queue, go start doing that.
	*/

D 67
	if (QueueIntvl > 0)
E 67
I 67
D 91
	if (queuemode)
E 91
I 91
D 98
	if (queuemode && !Daemon)
E 98
I 98
D 157
	if (queuemode && Mode != MD_DAEMON)
E 157
I 157
	if (queuemode && OpMode != MD_DAEMON)
E 157
E 98
E 91
E 67
	{
D 68
		runqueue();
E 68
I 68
		runqueue(FALSE);
E 68
		finis();
	}
I 76
# endif QUEUE
E 158
E 76
D 162

I 123
D 124
	/* give this transaction an id */
E 124
I 124
D 133
	/*
	**  Give this envelope a reality.
	**	I.e., an id and a creation time.
	*/

E 124
	(void) queuename(CurEnv, '\0');
I 124
	CurEnv->e_ctime = curtime();
E 133
I 133
	/* do basic system initialization */
	initsys();
E 162
E 133
E 124
	
# ifdef SMTP
E 123
	/*
I 123
	**  If running SMTP protocol, start collecting and executing
	**  commands.  This will never return.
	*/

D 157
	if (Smtp)
E 157
I 157
D 384
	if (OpMode == MD_SMTP)
E 384
I 384
	if (OpMode == MD_SMTP || OpMode == MD_DAEMON)
E 384
E 157
D 257
		smtp();
E 257
I 257
		smtp(CurEnv);
E 257
D 263
# endif SMTP
E 263
I 263
# endif /* SMTP */
E 263

I 349
	if (OpMode == MD_VERIFY)
	{
		CurEnv->e_sendmode = SM_VERIFY;
		CurEnv->e_errormode = EM_QUIET;
I 465
		PostMasterCopy = NULL;
E 465
	}
	else
	{
		/* interactive -- all errors are global */
D 412
		CurEnv->e_flags |= EF_GLOBALERRS;
E 412
I 412
		CurEnv->e_flags |= EF_GLOBALERRS|EF_LOGSENDER;
E 412
	}

E 349
	/*
E 123
E 66
D 62
	**  Process passwd file entry.
E 62
I 62
D 162
	**  Set the sender
E 162
I 162
	**  Do basic system initialization and set the sender
E 162
E 62
	*/

I 307
D 323
# ifndef SYSTEM5
E 323
E 307
I 292
D 348
	/* make sendmail immune from process group signals */
I 323
# ifdef _POSIX_JOB_CONTROL
	(void) setpgid(0, getpid());
# else
D 341
# ifndef SYSTEM5
E 341
I 341
#  ifndef SYSTEM5
E 341
E 323
	(void) setpgrp(0, getpid());
I 341
#  endif
E 341
I 307
# endif
I 323
D 341
# endif
E 341
E 323
E 307

E 348
E 292
I 162
D 257
	initsys();
E 257
I 257
	initsys(CurEnv);
E 257
E 162
D 62
	/* run user's .mailcf file */
	define('z', pw->pw_dir);
	(void) expand("$z/.mailcf", cfbuf, &cfbuf[sizeof cfbuf - 1]);
	if (safefile(cfbuf, getruid(), S_IREAD))
		readcf(cfbuf, FALSE);
E 62
I 62
D 251
	setsender(from);
E 251
I 251
D 301
	setsender(from, CurEnv);
E 301
I 301
D 309
	setsender(from, CurEnv, NULL);
E 309
I 309
	setsender(from, CurEnv, NULL, FALSE);
I 322
	if (macvalue('s', CurEnv) == NULL)
		define('s', RealHostName, CurEnv);
E 322
E 309
E 301
E 251
E 62

E 61
D 62
	/* extract full name from passwd file */
D 31
	if (pw != NULL && pw->pw_gecos != NULL)
E 31
I 31
	if ((fullname == NULL || fullname[0] == '\0') &&
	    pw != NULL && pw->pw_gecos != NULL)
E 31
	{
D 55
		register char *nb;
E 55
I 52
		char nbuf[MAXNAME];
E 52

D 55
		nb = nbuf;
		p = pw->pw_gecos;
		while (*p != '\0' && *p != ',' && *p != ';')
		{
			if (*p == '&')
			{
D 34
				strcpy(nb, realname);
E 34
I 34
				(void) strcpy(nb, realname);
E 34
				*nb = toupper(*nb);
				while (*nb != '\0')
					nb++;
				p++;
			}
			else
				*nb++ = *p++;
		}
		*nb = '\0';
E 55
I 55
		buildfname(pw->pw_gecos, realname, nbuf);
E 55
D 39
		if (!ArpaFmt && from == NULL && nbuf[0] != '\0')
E 39
I 39
		if (ArpaMode == ARPA_NONE && from == NULL && nbuf[0] != '\0')
E 39
D 31
			define('x', nbuf);
E 31
I 31
D 52
			fullname = nbuf;
E 52
I 52
			fullname = newstr(nbuf);
E 52
E 31
	}
I 31
	if (fullname != NULL && fullname[0] != '\0')
D 32
		define('x', nbuf);
E 32
I 32
		define('x', fullname);
E 32
E 31

D 39
	/*
	** Get a temp file.
	*/

	p = collect();
	if (from == NULL)
		from = p;

E 39
D 30
	/*
	**  Figure out who to claim it's coming from.
	**	Under certain circumstances allow the user to say who
	**	s/he is (using -f or -r).  These are:
	**	1.  The user's uid is zero (root).
	**	2.  The user's login name is "network" (mail from
	**	    a network server).
	**	3.  The user's login name is "uucp" (mail from the
	**	    uucp network).
	**	4.  The address the user is trying to claim has a
	**	    "!" character in it (since #3 doesn't do it for
	**	    us if we are dialing out).
	**	A better check to replace #3 & #4 would be if the
	**	effective uid is "UUCP" -- this would require me
	**	to rewrite getpwent to "grab" uucp as it went by,
	**	make getname more nasty, do another passwd file
	**	scan, or compile the UID of "UUCP" into the code,
	**	all of which are reprehensible.
	**
	**	Assuming all of these fail, we figure out something
	**	ourselves.
	*/
E 30
I 30
	setfrom(from, realname);
E 30

E 62
E 28
D 16
D 30
	if (from != NULL)
E 16
I 16

	canrename = TRUE;
	if (strcmp(locname, "network") != 0 && strcmp(locname, "uucp") != 0 &&
	    getuid() != 0 && from != NULL && index(from, '!') == NULL)
E 16
	{
D 8
		if (strcmp(p, "network") != 0 && getuid() != 0 /* && strcmp(p, From) != 0 */ )
E 8
I 8
D 16
D 28
		if (strcmp(p, "network") != 0 && strcmp(p, "uucp") != 0 &&
E 28
I 28
		if (strcmp(realname, "network") != 0 && strcmp(realname, "uucp") != 0 &&
E 28
		    index(from, '!') == NULL && getuid() != 0)
E 8
		{
			/* network sends -r regardless (why why why?) */
D 28
			/* syserr("%s, you cannot use the -f flag", p); */
E 28
I 28
			/* syserr("%s, you cannot use the -f flag", realname); */
E 28
			from = NULL;
		}
E 16
I 16
		canrename = FALSE;
		from = NULL;
E 16
	}
D 16
D 28
	if (from == NULL || from[0] == '\0')
E 16
I 16

	/*
	** Get a temp file.
	*/

	p = maketemp(from);
	if (from == NULL)
E 16
D 20
		from = p;
E 20
I 20
	{
		from = newstr(p);
E 28

D 28
		/* extract full name from passwd file */
		if (pw != NULL && pw->pw_gecos != NULL)
		{
			register char *nb;
E 28
I 28
	if (from == NULL)
		from = newstr(realname);
E 28

D 28
			nb = nbuf;
			p = pw->pw_gecos;
			while (*p != '\0' && *p != ',' && *p != ';')
			{
				if (*p == '&')
				{
					strcpy(nb, from);
					*nb = toupper(*nb);
					while (*nb != '\0')
						nb++;
					p++;
				}
				else
					*nb++ = *p++;
			}
			*nb = '\0';
			if (nbuf[0] != '\0')
D 27
				FullName = newstr(nbuf);
E 27
I 27
				define('x', newstr(nbuf));
E 27
		}
	}
E 20
I 16
# ifdef DEBUG
	if (Debug)
		printf("Message-Id: <%s>\n", MsgId);
# endif DEBUG
	if (from == NULL || from[0] == '\0')
		from = locname;
E 16
	else
		FromFlag++;
E 28
	SuprErrs = TRUE;
	if (parse(from, &From, 0) == NULL)
	{
		/* too many arpanet hosts generate garbage From addresses ....
		syserr("Bad from address `%s'", from);
		.... so we will just ignore this address */
		from = p;
I 25
		parse(from, &From, 0);
E 25
		FromFlag = FALSE;
	}
	SuprErrs = FALSE;

I 25
	define('f', From.q_paddr);
E 30
D 34
	expand("$l", FromLine, &FromLine[sizeof FromLine - 1]);
E 34
I 34
D 39
	(void) expand("$l", FromLine, &FromLine[sizeof FromLine - 1]);
E 34
E 25
# ifdef DEBUG
	if (Debug)
		printf("From person = \"%s\"\n", From.q_paddr);
# endif DEBUG

E 39
D 46
	if (argc <= 0)
E 46
I 46
D 61
	if (argc <= 0 && !GrabTo)
E 61
I 61
D 98
	if (!Daemon && argc <= 0 && !GrabTo)
E 98
I 98
D 153
	if (Mode != MD_DAEMON && argc <= 0 && !GrabTo)
E 153
I 153
D 157
	if (Mode != MD_DAEMON && ac <= 0 && !GrabTo)
E 157
I 157
D 164
	if (OpMode != MD_DAEMON && ac <= 0 && !GrabTo)
E 164
I 164
D 173
	if (OpMode != MD_ARPAFTP && ac <= 0 && !GrabTo)
E 173
I 173
D 248
	if (OpMode != MD_ARPAFTP && *av == NULL && !GrabTo)
E 248
I 248
	if (*av == NULL && !GrabTo)
E 248
E 173
E 164
E 157
E 153
E 98
I 79
	{
I 343
		CurEnv->e_flags |= EF_GLOBALERRS;
E 343
E 79
E 61
E 46
D 21
		usrerr("Usage: /etc/delivermail [flags] addr...");
E 21
I 21
D 26
		usrerr("Usage: /etc/postbox [flags] addr...");
E 26
I 26
D 192
		usrerr("Usage: /etc/sendmail [flags] addr...");
E 192
I 192
D 208
		usrerr("Usage: /usr/lib/sendmail [flags] addr...");
E 208
I 208
		usrerr("Recipient names must be specified");

		/* collect body for UUCP return */
		if (OpMode != MD_VERIFY)
D 257
			collect(FALSE);
E 257
I 257
D 320
			collect(FALSE, CurEnv);
E 320
I 320
D 402
			collect(FALSE, FALSE, CurEnv);
E 402
I 402
			collect(InChannel, FALSE, FALSE, NULL, CurEnv);
E 402
E 320
E 257
E 208
E 192
I 79
		finis();
D 349
	}
I 157
	if (OpMode == MD_VERIFY)
I 331
	{
E 331
D 312
		SendMode = SM_VERIFY;
E 312
I 312
		CurEnv->e_sendmode = SM_VERIFY;
I 331
		CurEnv->e_errormode = EM_QUIET;
E 349
	}
E 331
E 312
E 157
E 79
E 26
E 21

	/*
D 164
	**  Process Hop count.
	**	The Hop count tells us how many times this message has
D 21
	**	been processed by delivermail.  If it exceeds some
E 21
I 21
D 26
	**	been processed by postbox.  If it exceeds some
E 26
I 26
	**	been processed by sendmail.  If it exceeds some
E 26
E 21
	**	fairly large threshold, then we assume that we have
	**	an infinite forwarding loop and die.
	*/

	if (++HopCount > MAXHOP)
D 94
		syserr("Infinite forwarding loop (%s->%s)", From.q_paddr, *argv);
E 94
I 94
D 153
		syserr("Infinite forwarding loop (%s->%s)", CurEnv->e_from.q_paddr, *argv);
E 153
I 153
		syserr("Infinite forwarding loop (%s->%s)", CurEnv->e_from.q_paddr, *av);
E 153
E 94

D 2
	/* if we have had errors sofar, drop out now */
	if (Error && ExitStat == EX_OK)
		ExitStat = EX_USAGE;
	if (ExitStat != EX_OK)
		finis();

E 2
	/*
E 164
D 52
	** Scan argv and deliver the message to everyone.
E 52
I 52
	**  Scan argv and deliver the message to everyone.
D 164
	**	Actually, suppress delivery if we are taking To:
	**	lines from the message.
E 164
E 52
	*/

I 48
D 164
	if (GrabTo)
		DontSend = TRUE;
E 164
E 48
D 52
	for (; argc-- > 0; argv++)
	{
D 18
		sendto(*argv, 0);
E 18
I 18
		p = argv[1];
		if (argc >= 2 && p[2] == '\0' &&
		    (p[0] == 'a' || p[0] == 'A') &&
		    (p[1] == 't' || p[1] == 'T'))
		{
			if (strlen(argv[0]) + strlen(argv[2]) + 2 > sizeof nbuf)
			{
				usrerr("address overflow");
				p = argv[0];
			}
			else
			{
D 34
				strcpy(nbuf, argv[0]);
				strcat(nbuf, "@");
				strcat(nbuf, argv[2]);
E 34
I 34
				(void) strcpy(nbuf, argv[0]);
				(void) strcat(nbuf, "@");
				(void) strcat(nbuf, argv[2]);
E 34
D 39
				p = nbuf;
E 39
I 39
				p = newstr(nbuf);
E 39
				argv += 2;
				argc -= 2;
			}
		}
		else
			p = argv[0];
		sendto(p, 0);
E 18
	}
E 52
I 52
D 61
	sendtoargv(argv);
E 61
I 61
D 62
	if (Daemon)
		getrecipients();
	else
		sendtoargv(argv);
E 62
I 62
D 153
	sendtoargv(argv);
E 153
I 153
D 257
	sendtoargv(av);
E 257
I 257
	sendtoargv(av, CurEnv);
E 257
E 153
E 62
E 61
E 52

I 2
D 108
	/* if we have had errors sofar, drop out now */
E 108
I 108
	/* if we have had errors sofar, arrange a meaningful exit stat */
E 108
D 13
	if (Error && ExitStat == EX_OK)
E 13
I 13
	if (Errors > 0 && ExitStat == EX_OK)
E 13
		ExitStat = EX_USAGE;
D 39
	if (ExitStat != EX_OK)
E 39
I 39
D 43
	if (ArpaMode > ARPA_OLD && ExitStat != EX_OK)
E 43
I 43
D 46
	if ((ArpaMode > ARPA_OLD && ExitStat != EX_OK) || verifyonly)
E 46
I 46
D 52
	if ((ArpaMode > ARPA_OLD && ExitStat != EX_OK) ||
	    (verifyonly && !GrabTo))
E 52
I 52
D 70
	if (ArpaMode > ARPA_OLD && ExitStat != EX_OK)
E 52
E 46
E 43
E 39
		finis();
E 70
D 85

I 39
D 52
	/* no errors, tell arpanet to go ahead */
	To = NULL;
	if (ArpaMode == ARPA_MAIL)
D 40
		message("350", "Enter mail, end with \".\" on a line by itself");
E 40
I 40
	{
		extern char Arpa_Enter[];

		message(Arpa_Enter, "Enter mail, end with \".\" on a line by itself");
	}
E 40
	errno = 0;

E 52
E 39
E 2
	/*
I 84
	**  Hack attack!
	**	If the sender is local, we will default to old style
	**	headers.  Ugh ugh ugh.  But oh-so-necessary under the
	**	circumstances.
	*/

	if (bitset(M_LOCAL, From.q_mailer->m_flags))
		OldStyle = TRUE;
E 85

	/*
E 84
D 25
	**  See if we have anyone to send to at all.
	*/

	if (nxtinq(&SendQ) == NULL && ExitStat == EX_OK)
	{
		syserr("Noone to send to!");
		ExitStat = EX_USAGE;
		finis();
	}

	/*
E 25
D 39
	**  Do aliasing.
	**	First arrange that the person who is sending the mail
	**	will not be expanded (unless explicitly requested).
E 39
I 39
	**  Read the input mail.
E 39
	*/

I 48
D 164
	DontSend = FALSE;
E 164
E 48
I 39
D 52
	collect();
E 52
I 52
D 94
	To = NULL;
E 94
I 94
	CurEnv->e_to = NULL;
E 94
D 60
	errno = 0;
E 60
D 98
	if (!verifyonly || GrabTo)
E 98
I 98
D 157
	if (Mode != MD_VERIFY || GrabTo)
E 157
I 157
	if (OpMode != MD_VERIFY || GrabTo)
I 343
	{
		CurEnv->e_flags |= EF_GLOBALERRS;
E 343
E 157
E 98
D 70
		collect();
E 70
I 70
D 257
		collect(FALSE);
E 257
I 257
D 320
		collect(FALSE, CurEnv);
E 320
I 320
D 402
		collect(FALSE, FALSE, CurEnv);
E 402
I 402
		collect(InChannel, FALSE, FALSE, NULL, CurEnv);
E 402
I 343
	}
E 343
E 320
E 257
E 70
I 60
	errno = 0;
I 81
D 351

D 157
	/*
	**  If we don't want to wait around for actual delivery, this
	**  is a good time to fork off.
	**	We have examined what we can without doing actual
	**		delivery, so we will inform our caller of
	**		whatever we can now.
	**	Since the parent process will go away immediately,
	**		the child will be caught by init.
	**	If the fork fails, we will just continue in the
	**		parent; this is perfectly safe, albeit
	**		slower than it must be.
I 108
D 137
	**	If we have errors sofar, this seems like a good time
	**		to dispose of them.
E 137
E 108
	*/
I 108
D 137

D 117
	if (ExitStat != EX_OK)
E 117
I 117
	if (ExitStat != EX_OK && Mode != MD_VERIFY)
E 117
		finis();
E 137
E 108

I 145
# ifdef QUEUE
	if (Mode == MD_QUEUE)
	{
		register ADDRESS *q;

		for (q = CurEnv->e_sendqueue; q != NULL; q = q->q_next)
		{
			if (!bitset(QDONTSEND, q->q_flags))
			{
				CurEnv->e_to = q->q_paddr;
D 146
				giveresponse(EX_TEMPFAIL, TRUE, q->q_mailer);
E 146
I 146
				message(Arpa_Info, "queued");
				if (LogLevel > 4)
					logdelivery("queued");
E 146
			}
			CurEnv->e_to = NULL;
		}
	}
E 145
I 139
	if (Mode == MD_QUEUE || Mode == MD_FORK ||
	    (Mode != MD_VERIFY && SuperSafe))
		queueup(CurEnv, TRUE);

E 139
D 98
	if (ForkOff)
E 98
I 98
	if (Mode == MD_FORK)
E 98
	{
		if (fork() > 0)
		{
			/* parent -- quit */
			exit(ExitStat);
		}
I 122
# ifdef LOG
		if (LogLevel > 11)
			syslog(LOG_DEBUG, "background delivery, pid=%d", getpid());
# endif LOG
E 122
	}
I 98
	else if (Mode == MD_QUEUE)
	{
D 139
		queueup(CurEnv, TRUE);
E 139
I 139
		CurEnv->e_df = CurEnv->e_qf = NULL;
		CurEnv->e_dontqueue = TRUE;
E 139
D 136
		exit(ExitStat);
E 136
I 136
		finis();
E 136
	}
E 98

E 157
E 81
I 66
D 164
	initsys();
E 66
E 60
E 52

E 164
D 44
	(void) expand("$l", FromLine, &FromLine[sizeof FromLine - 1]);
E 44
D 52
# ifdef DEBUG
	if (Debug)
		printf("From person = \"%s\"\n", From.q_paddr);
# endif DEBUG
I 46

	if (verifyonly && GrabTo)
		finis();
E 46

E 52
I 49
	/* collect statistics */
D 65
	Stat.stat_nf[From.q_mailer]++;
	Stat.stat_bf[From.q_mailer] += kbytes(MsgSize);
E 65
I 65
D 94
	Stat.stat_nf[From.q_mailer->m_mno]++;
	Stat.stat_bf[From.q_mailer->m_mno] += kbytes(MsgSize);
E 94
I 94
D 164
	Stat.stat_nf[CurEnv->e_from.q_mailer->m_mno]++;
	Stat.stat_bf[CurEnv->e_from.q_mailer->m_mno] += kbytes(CurEnv->e_msgsize);
E 164
I 164
	if (OpMode != MD_VERIFY)
		markstats(CurEnv, (ADDRESS *) NULL);
E 351
E 164
E 94
E 65

E 49
D 164
	/*
	**  Arrange that the person who is sending the mail
	**  will not be expanded (unless explicitly requested).
	*/

E 164
I 52
D 229
# ifdef DEBUG
E 229
D 116
	if (Debug)
E 116
I 116
	if (tTd(1, 1))
E 116
D 94
		printf("From person = \"%s\"\n", From.q_paddr);
E 94
I 94
		printf("From person = \"%s\"\n", CurEnv->e_from.q_paddr);
E 94
D 229
# endif DEBUG
E 229

E 52
E 39
I 25
D 94
	From.q_flags |= QDONTSEND;
E 94
I 94
D 164
	CurEnv->e_from.q_flags |= QDONTSEND;
E 94
E 25
	if (!MeToo)
D 25
		recipient(&From, &AliasQ);
E 25
I 25
D 73
D 74
		recipient(&From);
E 74
I 74
D 94
		recipient(&From, &SendQueue);
E 74
E 73
I 73
		(void) recipient(&From);
E 73
E 25
	To = NULL;
E 94
I 94
		recipient(&CurEnv->e_from, &CurEnv->e_sendqueue);
	CurEnv->e_to = NULL;
E 94
D 36
	alias();
E 36
D 25
	if (nxtinq(&SendQ) == NULL && ExitStat == EX_OK)
	{
/*
		syserr("Vacant send queue; probably aliasing loop");
		ExitStat = EX_SOFTWARE;
		finis();
*/
		recipient(&From, &SendQ);
	}
E 25

E 164
	/*
	**  Actually send everything.
I 52
	**	If verifying, just ack.
E 52
	*/

I 164
	CurEnv->e_from.q_flags |= QDONTSEND;
I 280
	if (tTd(1, 5))
	{
		printf("main: QDONTSEND ");
		printaddr(&CurEnv->e_from, FALSE);
	}
E 280
	CurEnv->e_to = NULL;
E 164
D 25
	for (q = &SendQ; (q = nxtinq(q)) != NULL; )
		deliver(q, (fnptr) NULL);
E 25
I 25
D 62
	for (i = 0; Mailer[i] != NULL; i++)
	{
		ADDRESS *q;
E 62
I 62
D 98
	sendall(verifyonly);
E 98
I 98
D 101
	sendall(Mode == MD_VERIFY);
E 101
I 101
D 157
	sendall(CurEnv, Mode == MD_VERIFY);
E 157
I 157
D 185
	sendall(CurEnv, SendMode);
E 185
I 185
	sendall(CurEnv, SM_DEFAULT);
E 185
E 157
E 101
E 98
E 62

D 62
		for (q = Mailer[i]->m_sendq; q != NULL; q = q->q_next)
		{
D 34
			deliver(q, (fnptr) NULL);
E 34
I 34
D 52
			(void) deliver(q, (fnptr) NULL);
E 52
I 52
			if (verifyonly)
			{
				To = q->q_paddr;
				if (!bitset(QDONTSEND|QBADADDR, q->q_flags))
				{
					if (q->q_mailer == MN_LOCAL || q->q_mailer == MN_PROG)
						message(Arpa_Info, "deliverable");
					else
						message(Arpa_Info, "queueable");
				}
			}
			else
				(void) deliver(q, (fnptr) NULL);
E 52
E 34
		}
	}
E 25

E 62
	/*
D 331
	** All done.
E 331
I 331
	**  All done.
	**	Don't send return error message if in VERIFY mode.
E 331
	*/

I 39
D 94
	To = NULL;
E 94
I 94
D 164
	CurEnv->e_to = NULL;
E 94
D 70
	if (Errors == 0)
	{
		switch (ArpaMode)
		{
			static char *okmsg = "Mail accepted";
I 40
			extern char Arpa_Fmsg[], Arpa_Mmsg[];
E 40

		  case ARPA_FILE:
D 40
			message("252", okmsg);
E 40
I 40
			message(Arpa_Fmsg, okmsg);
E 40
			break;

		  case ARPA_MAIL:
D 40
			message("256", okmsg);
E 40
I 40
			message(Arpa_Mmsg, okmsg);
E 40
			break;
		}
	}
E 70
I 49
D 52
	poststats(StatFile);
E 52
I 52
D 98
	if (!verifyonly)
E 98
I 98
D 157
	if (Mode != MD_VERIFY)
E 157
I 157
	if (OpMode != MD_VERIFY)
E 157
E 98
		poststats(StatFile);
E 164
E 52
E 49
E 39
	finis();
I 30
}
/*
D 164
**  SETFROM -- set the person who this message is from
E 164
I 164
D 166
**  SETSENDER -- set the person who this message is from
E 164
**
**	Under certain circumstances allow the user to say who
**	s/he is (using -f or -r).  These are:
**	1.  The user's uid is zero (root).
D 149
**	2.  The user's login name is "network" (mail from
**	    a network server).
**	3.  The user's login name is "uucp" (mail from the
**	    uucp network).
**	4.  The address the user is trying to claim has a
**	    "!" character in it (since #3 doesn't do it for
**	    us if we are dialing out).
**	A better check to replace #3 & #4 would be if the
E 149
I 149
**	2.  The user's login name is in an approved list (typically
**	    from a network server).
**	3.  The address the user is trying to claim has a
**	    "!" character in it (since #2 doesn't do it for
**	    us if we are dialing out for UUCP).
**	A better check to replace #3 would be if the
E 149
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
D 164
**		from -- the person it is from.
**		realname -- the actual person executing sendmail.
I 39
**			If NULL, then take whoever we previously
**			thought was the from person.
E 164
I 164
**		from -- the person we would like to believe this message
**			is from, as specified on the command line.
E 164
E 39
**
**	Returns:
**		none.
**
**	Side Effects:
**		sets sendmail's notion of who the from person is.
*/

D 164
setfrom(from, realname)
E 164
I 164
setsender(from)
E 164
	char *from;
D 164
	char *realname;
E 164
{
	register char **pvp;
D 164
	char frombuf[MAXNAME];
E 164
I 164
	register struct passwd *pw = NULL;
	char *realname = NULL;
	char buf[MAXNAME];
	extern char *macvalue();
E 164
	extern char **prescan();
D 164
	extern char *index();
E 164
I 103
D 135
	extern char *macvalue();
E 135
E 103

I 39
D 164
	if (realname == NULL)
D 94
		realname = From.q_paddr;
E 94
I 94
		realname = CurEnv->e_from.q_paddr;
E 94
I 71

E 164
# ifdef DEBUG
D 116
	if (Debug > 1)
E 116
I 116
D 129
	if (tTd(1, 2))
E 129
I 129
D 164
	if (tTd(1, 1))
E 129
E 116
		printf("setfrom(%s, %s)\n", from, realname);
E 164
I 164
	if (tTd(45, 1))
		printf("setsender(%s)\n", from);
E 164
# endif DEBUG

I 164
	/*
	**  Figure out the real user executing us.
	**	Username can return errno != 0 on non-errors.
	*/

	if (QueueRun || OpMode == MD_SMTP || OpMode == MD_ARPAFTP)
		realname = from;
	if (realname == NULL || realname[0] == '\0')
	{
		extern char *username();

		realname = username();
		errno = 0;
	}
	if (realname == NULL || realname[0] == '\0')
	{
		extern struct passwd *getpwuid();

		pw = getpwuid(getruid());
		if (pw != NULL)
			realname = pw->pw_name;
	}
	if (realname == NULL || realname[0] == '\0')
	{
		syserr("Who are you?");
		realname = "root";
	}

	/*
	**  Determine if this real person is allowed to alias themselves.
	*/

E 164
I 100
	/*
	**  Do validation to determine whether this user is allowed
	**  to change the sender name.
	*/

E 100
E 71
E 39
	if (from != NULL)
	{
D 96
		if (strcmp(realname, "network") != 0 && strcmp(realname, "uucp") != 0 &&
E 96
I 96
D 149
		if (strcmp(realname, "network") != 0 &&
		    strcmp(realname, "uucp") != 0 &&
		    strcmp(realname, "daemon") != 0 &&
E 149
I 149
		extern bool trusteduser();

		if (!trusteduser(realname) &&
E 149
E 96
I 60
# ifdef DEBUG
D 116
		    (Debug == 0 || getuid() != geteuid()) &&
E 116
I 116
D 129
		    (!tTd(1, 1) || getuid() != geteuid()) &&
E 129
I 129
		    (!tTd(1, 9) || getuid() != geteuid()) &&
E 129
E 116
# endif DEBUG
E 60
		    index(from, '!') == NULL && getuid() != 0)
		{
			/* network sends -r regardless (why why why?) */
			/* syserr("%s, you cannot use the -f flag", realname); */
			from = NULL;
		}
	}

I 100
	/*
	**  Parse the sender name.
	**	Arrange to send return messages to the same person.
	**	Set up some environment info.
	*/

E 100
	SuprErrs = TRUE;
D 71
	if (from == NULL || parse(from, &From, 0) == NULL)
E 71
I 71
D 94
	if (from == NULL || parse(from, &From, 1) == NULL)
E 94
I 94
	if (from == NULL || parse(from, &CurEnv->e_from, 1) == NULL)
E 94
E 71
	{
		from = newstr(realname);
D 34
		parse(from, &From, 0);
E 34
I 34
D 71
		(void) parse(from, &From, 0);
E 71
I 71
D 94
		(void) parse(from, &From, 1);
E 94
I 94
		(void) parse(from, &CurEnv->e_from, 1);
E 94
E 71
E 34
	}
	else
		FromFlag = TRUE;
I 164
	CurEnv->e_from.q_flags |= QDONTSEND;
E 164
I 100
	CurEnv->e_returnto = &CurEnv->e_from;
E 100
	SuprErrs = FALSE;
I 164

	if (pw == NULL && CurEnv->e_from.q_mailer == LocalMailer)
	{
		extern struct passwd *getpwnam();

		pw = getpwnam(CurEnv->e_from.q_user);
	}

	/*
	**  Process passwd file entry.
	*/

	if (pw != NULL)
	{
		/* extract home directory */
		CurEnv->e_from.q_home = newstr(pw->pw_dir);

		/* run user's .mailcf file */
		define('z', CurEnv->e_from.q_home, CurEnv);
		expand("$z/.mailcf", buf, &buf[sizeof buf - 1], CurEnv);
		if (safefile(buf, getruid(), S_IREAD))
			readcf(buf, FALSE);

		/* if the user has given fullname already, don't redefine */
		if (FullName == NULL)
			FullName = macvalue('x', CurEnv);
		if (FullName[0] == '\0')
			FullName = NULL;

		/* extract full name from passwd file */
		if (FullName == NULL && pw->pw_gecos != NULL)
		{
			buildfname(pw->pw_gecos, CurEnv->e_from.q_user, buf);
			if (buf[0] != '\0')
				FullName = newstr(buf);
		}
		if (FullName != NULL)
			define('x', FullName, CurEnv);
	}

#ifndef V6
	if (CurEnv->e_from.q_home == NULL)
		CurEnv->e_from.q_home = getenv("HOME");
#endif V6
E 164
I 56
D 94
	From.q_uid = getuid();
	From.q_gid = getgid();
E 94
I 94
	CurEnv->e_from.q_uid = getuid();
	CurEnv->e_from.q_gid = getgid();
E 94
D 164
# ifndef V6
D 94
	From.q_home = getenv("HOME");
E 94
I 94
	CurEnv->e_from.q_home = getenv("HOME");
E 94
# endif V6
E 164
I 81
D 94
	if (From.q_uid != 0)
E 94
I 94
	if (CurEnv->e_from.q_uid != 0)
E 94
	{
D 94
		DefUid = From.q_uid;
		DefGid = From.q_gid;
E 94
I 94
		DefUid = CurEnv->e_from.q_uid;
		DefGid = CurEnv->e_from.q_gid;
E 94
	}
E 81
I 57
D 58
	From.q_flags |= QGOODUID;
E 58
E 57
E 56

	/*
I 77
D 134
	**  Set up the $r and $s macros to show who it came from.
	*/

D 94
	if (From.q_host != NULL && From.q_host[0] != '\0')
E 94
I 94
D 103
	if (CurEnv->e_from.q_host != NULL && CurEnv->e_from.q_host[0] != '\0')
E 103
I 103
	if (macvalue('s') == NULL && CurEnv->e_from.q_host != NULL &&
	    CurEnv->e_from.q_host[0] != '\0')
E 103
E 94
	{
D 94
		define('s', From.q_host);
E 94
I 94
		define('s', CurEnv->e_from.q_host);
E 94

		/* should determine network type here */
	}

	/*
E 134
E 77
	**  Rewrite the from person to dispose of possible implicit
	**	links in the net.
	*/

	pvp = prescan(from, '\0');
	if (pvp == NULL)
	{
		syserr("cannot prescan from (%s)", from);
		finis();
	}
I 135
	rewrite(pvp, 3);
E 135
	rewrite(pvp, 1);
D 47
	frombuf[0] = '\0';
	while (*pvp != NULL)
D 34
		strcat(frombuf, *pvp++);
E 34
I 34
		(void) strcat(frombuf, *pvp++);
E 34

E 47
I 47
D 164
	cataddr(pvp, frombuf, sizeof frombuf);
E 47
	define('f', newstr(frombuf));
E 164
I 164
	cataddr(pvp, buf, sizeof buf);
	define('f', newstr(buf), CurEnv);
E 164
I 135

	/* save the domain spec if this mailer wants it */
	if (bitset(M_CANONICAL, CurEnv->e_from.q_mailer->m_flags))
	{
		extern char **copyplist();

		while (*pvp != NULL && strcmp(*pvp, "@") != 0)
			pvp++;
		if (*pvp != NULL)
			CurEnv->e_fromdomain = copyplist(pvp, TRUE);
	}
I 149
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
E 149
E 135
E 30
}
/*
E 166
**  FINIS -- Clean up and exit.
**
D 5
**	Algorithm:
**		if we should remove the input
**			remove the input
**		exit
**
E 5
**	Parameters:
**		none
**
**	Returns:
**		never
**
**	Side Effects:
D 21
**		exits delivermail
E 21
I 21
D 26
**		exits postbox
E 26
I 26
**		exits sendmail
E 26
E 21
D 51
**
D 5
**	Requires:
**		unlink (sys)
**		exit (sys)
**		savemail
**		InFileName -- the file to remove
**		ExitStat -- the status to exit with
**
E 5
**	Called By:
**		main
**		via signal on interrupt.
**
**	Deficiencies:
**		It may be that it should only remove the input
**			file if there have been no errors.
E 51
D 5
**
**	History:
**		12/26/79 -- written.
E 5
*/

I 427
void
E 427
finis()
{
I 101
D 166
	CurEnv = &MainEnvelope;
I 164
	CurEnv->e_to = NULL;
E 164

E 166
E 101
I 67
D 229
# ifdef DEBUG
E 229
D 87
	if (Debug > 2)
		printf("\n====finis: stat %d\n", ExitStat);
E 87
I 87
D 116
	if (Debug > 0)
E 116
I 116
	if (tTd(2, 1))
E 116
I 101
D 162
	{
E 101
D 88
		printf("\n====finis: stat %d SendReceipt %d\n", ExitStat,
		     SendReceipt);
E 88
I 88
D 94
		printf("\n====finis: stat %d SendReceipt %d FatalErrors %d\n",
		     ExitStat, SendReceipt, FatalErrors);
E 94
I 94
		printf("\n====finis: stat %d sendreceipt %d FatalErrors %d\n",
		     ExitStat, CurEnv->e_sendreceipt, FatalErrors);
I 101
	}
E 162
I 162
D 360
		printf("\n====finis: stat %d e_flags %o\n", ExitStat, CurEnv->e_flags);
E 360
I 360
D 404
		printf("\n====finis: stat %d e_flags %o, e_id=%s\n",
E 404
I 404
D 439
		printf("\n====finis: stat %d e_flags %x, e_id=%s\n",
E 404
			ExitStat, CurEnv->e_flags,
E 439
I 439
	{
		extern void printenvflags();

		printf("\n====finis: stat %d e_id=%s e_flags=",
			ExitStat,
E 439
			CurEnv->e_id == NULL ? "NOQUEUE" : CurEnv->e_id);
I 439
		printenvflags(CurEnv);
	}
E 439
I 371
	if (tTd(2, 9))
		printopenfds(FALSE);
E 371
E 360
E 162
E 101
E 94
E 88
E 87
D 229
# endif DEBUG
E 229
I 87

D 106
	/* send back return receipts as requested */
E 106
I 106
D 164
	/*
D 162
	**  Send back return receipts as requested.
E 162
I 162
	**  Clean up temp files.
E 162
	*/

E 164
I 164
	/* clean up temp files */
I 166
	CurEnv->e_to = NULL;
E 166
E 164
E 106
D 94
	if (SendReceipt && ExitStat == EX_OK)
E 94
I 94
D 129
	if (CurEnv->e_sendreceipt && ExitStat == EX_OK)
E 94
D 95
		returntosender("Return receipt", FALSE);
E 95
I 95
D 99
		returntosender("Return receipt", &CurEnv->e_from, FALSE);
E 99
I 99
		(void) returntosender("Return receipt", &CurEnv->e_from, FALSE);
E 129
I 129
D 162
	if (CurEnv->e_receiptto != NULL &&
	    (CurEnv->e_sendreceipt || ExitStat != EX_OK))
	{
		auto ADDRESS *rlist;
E 162
I 162
	dropenvelope(CurEnv);
I 254

	/* flush any cached connections */
D 290
	mci_flush();
E 290
I 290
	mci_flush(TRUE, NULL);
E 290
E 254
E 162
E 129
E 99
E 95
E 87
D 341

I 129
D 130
		sendto(CurEnv->e_receiptto, 1, (ADDRESS *) NULL, &rlist);
E 130
I 130
D 162
		sendto(CurEnv->e_receiptto, (ADDRESS *) NULL, &rlist);
E 130
		(void) returntosender("Return receipt", rlist, FALSE);
	}

E 162
E 129
E 67
D 101
	/* mail back the transcript on errors */
D 88
	if (ExitStat != EX_OK)
E 88
I 88
	if (FatalErrors)
E 88
		savemail();
E 101
I 101
D 106
	/* do error handling */
E 106
I 106
D 164
	/*
D 162
	**  Arrange to return errors or queue up as appropriate.
	**	If we are running a queue file and exiting abnormally,
	**		be sure we save the queue file.
	**	This clause will arrange to return error messages.
E 162
I 162
	**  And exit.
E 162
	*/
E 164
I 164
	/* post statistics */
	poststats(StatFile);
E 341
E 164

I 326
# ifdef XLA
	/* clean up extended load average stuff */
	xla_all_end();
# endif

E 326
I 164
	/* and exit */
E 164
D 118
	if (ControlFile != NULL)
		CurEnv->e_queueup = TRUE;
E 118
E 106
D 162
	checkerrors(CurEnv);
E 101

I 101
D 106
	/* now clean up bookeeping information */
E 106
I 106
	/*
	**  Now clean up temp files and exit.
	*/

E 106
E 101
D 66
	if (HasXscrpt)
E 66
I 66
	if (Transcript != NULL)
E 66
D 34
		unlink(Transcript);
	unlink(InFileName);
E 34
I 34
D 116
		(void) unlink(Transcript);
E 116
I 116
		xunlink(Transcript);
E 116
D 66
	(void) unlink(InFileName);
E 66
I 66
D 94
	if (QueueUp)
E 94
I 94
D 101
	if (CurEnv->e_queueup)
E 94
I 76
	{
# ifdef QUEUE
E 76
D 75
	{
		if (!QueueRun)
			queueup(InFileName);
	}
E 75
I 75
D 95
		queueup(InFileName);
E 95
I 95
D 98
		queueup(CurEnv);
E 98
I 98
		queueup(CurEnv, FALSE);
E 98
E 95
I 76
# else QUEUE
D 97
		syserr("finis: trying to queue %s", InFileName);
E 97
I 97
		syserr("finis: trying to queue %s", CurEnv->e_df);
E 97
# endif QUEUE
	}
E 76
E 75
	else
E 101
I 101
D 109
	if (!CurEnv->e_queueup)
E 109
I 109
D 118
	if (CurEnv->e_df != NULL)
E 109
E 101
D 97
		(void) unlink(InFileName);
E 97
I 97
D 116
		(void) unlink(CurEnv->e_df);
E 116
I 116
		xunlink(CurEnv->e_df);
E 116
I 106
	if (ControlFile != NULL)
D 116
		(void) unlink(ControlFile);
E 116
I 116
		xunlink(ControlFile);
E 118
I 118
	dropenvelope(CurEnv);
E 162
I 122
# ifdef LOG
D 285
	if (LogLevel > 11)
E 285
I 285
	if (LogLevel > 78)
E 285
		syslog(LOG_DEBUG, "finis, pid=%d", getpid());
D 263
# endif LOG
E 263
I 263
# endif /* LOG */
E 263
I 180
D 468
	if (ExitStat == EX_TEMPFAIL)
E 468
I 468
	if (ExitStat == EX_TEMPFAIL || CurEnv->e_errormode == EM_BERKNET)
E 468
		ExitStat = EX_OK;
I 342

	/* reset uid for process accounting */
I 486
	endpwent();
E 486
	setuid(RealUid);

E 342
E 180
E 122
E 118
E 116
E 106
E 97
E 66
E 34
	exit(ExitStat);
I 152
}
/*
**  INTSIG -- clean up on interrupt
**
D 164
**	This just arranges to call finis.
E 164
I 164
**	This just arranges to exit.  It pessimises in that it
**	may resend a message.
E 164
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
D 164
**		Arranges to not unlink the qf and df files.
E 164
I 164
**		Unlocks the current job.
E 164
*/

I 236
void
E 236
intsig()
{
D 162
	CurEnv->e_df = CurEnv->e_qf = NULL;
E 162
I 162
D 164
	CurEnv->e_df = NULL;
E 162
	finis();
E 164
I 164
	FileName = NULL;
	unlockqueue(CurEnv);
I 326
#ifdef XLA
	xla_all_end();
#endif
I 342

	/* reset uid for process accounting */
I 486
	endpwent();
E 486
	setuid(RealUid);

E 342
E 326
	exit(EX_OK);
E 164
E 152
}
/*
D 11
**  MAKETEMP -- Make temporary file
**
**	Creates a temporary file name and copies the standard
**	input to that file.  While it is doing it, it looks for
**	"From:" and "Sender:" fields to use as the from-person
**	(but only if the -a flag is specified).  It prefers to
**	to use the "Sender:" field -- the protocol says that
**	"Sender:" must come after "From:", so this works easily.
**	MIT seems to like to produce "Sent-By:" fields instead
**	of "Sender:" fields.  We used to catch this, but it turns
**	out that the "Sent-By:" field doesn't always correspond
**	to someone real, as required by the protocol.  So we limp
**	by.....
**
**	Parameters:
**		none
**
**	Returns:
**		Name of temp file.
**
**	Side Effects:
**		Temp file is created and filled.
**
D 5
**	Requires:
**		creat (sys)
**		close (sys)
**		syserr
**		mktemp (sys)
**		fopen (sys)
**		fgets (sys)
**		makemsgid
**		fprintf (sys)
**		fputs (sys)
**		isspace (sys)
**		matchhdr
**		prescan
**		ferror (sys)
**		clearerr (sys)
**		freopen (sys)
**
E 5
**	Called By:
**		main
**
**	Notes:
**		This is broken off from main largely so that the
**		temp buffer can be deallocated.
**
**	Deficiencies:
**		It assumes that the From: field will preceed the
**		Sender: field.  This violates the Arpanet NIC 733
**		protocol, but seems reasonable in practice.  In
**		any case, the only problem is that error responses
**		may be sent to the wrong person.
D 5
**
**	History:
**		12/26/79 -- written.
E 5
*/

char *
maketemp()
{
	register FILE *tf;
D 9
	char buf[MAXLINE+1];
E 9
I 9
	char buf[MAXFIELD+1];
E 9
	static char fbuf[sizeof buf];
	extern char *prescan();
	extern char *matchhdr();
	register char *p;
D 9
	bool inheader;
E 9
I 9
	register bool inheader;
E 9
	bool firstline;
I 9
	char c;
E 9

	/*
	**  Create the temp file name and create the file.
	*/

	mktemp(InFileName);
	close(creat(InFileName, 0600));
	if ((tf = fopen(InFileName, "w")) == NULL)
	{
		syserr("Cannot create %s", InFileName);
		return (NULL);
	}

	/*
	**  Copy stdin to temp file & do message editting.
	**	From person gets copied into fbuf.  At the end of
	**	this loop, if fbuf[0] == '\0' then there was no
	**	recognized from person in the message.  We also
	**	save the message id in MsgId.  The
	**	flag 'inheader' keeps track of whether we are
	**	in the header or in the body of the message.
	**	The flag 'firstline' is only true on the first
	**	line of a message.
	**	To keep certain mailers from getting confused,
	**	and to keep the output clean, lines that look
	**	like UNIX "From" lines are deleted in the header,
	**	and prepended with ">" in the body.
	*/

	inheader = TRUE;
	firstline = TRUE;
	fbuf[0] = '\0';
	while (fgets(buf, sizeof buf, stdin) != NULL)
	{
I 9
		if (inheader && isalnum(buf[0]))
		{
			/* get the rest of this field */
			while ((c = getc(stdin)) == ' ' || c == '\t')
			{
				p = &buf[strlen(buf)];
				*p++ = c;
				if (fgets(p, sizeof buf - (p - buf), stdin) == NULL)
					break;
			}
			ungetc(c, stdin);
		}

E 9
		if (!IgnrDot && buf[0] == '.' && (buf[1] == '\n' || buf[1] == '\0'))
			break;

		/* are we still in the header? */
		if ((buf[0] == '\n' || buf[0] == '\0') && inheader)
		{
			inheader = FALSE;
			if (MsgId[0] == '\0')
			{
				makemsgid();
# ifdef MESSAGEID
				fprintf(tf, "Message-Id: <%s>\n", MsgId);
# endif MESSAGEID
			}
I 9
# ifdef DEBUG
			if (Debug)
				printf("EOH\n");
# endif DEBUG
E 9
		}

		/* Hide UNIX-like From lines */
		if (buf[0] == 'F' && buf[1] == 'r' && buf[2] == 'o' &&
		    buf[3] == 'm' && buf[4] == ' ')
		{
			if (firstline && !SaveFrom)
				continue;
			fputs(">", tf);
		}

		if (inheader && !isspace(buf[0]))
		{
			/* find out if this is really a header */
			for (p = buf; *p != ':' && *p != '\0' && !isspace(*p); p++)
				continue;
			while (*p != ':' && isspace(*p))
				p++;
			if (*p != ':')
I 9
			{
E 9
				inheader = FALSE;
I 9
# ifdef DEBUG
				if (Debug)
					printf("EOH?\n");
# endif DEBUG
			}
E 9
		}

		if (inheader)
		{
			/* find the sender */
			p = matchhdr(buf, "from");
			if (p == NULL)
				p = matchhdr(buf, "sender");
			if (p != NULL)
				prescan(p, fbuf, &fbuf[sizeof fbuf - 1], '\0');

			/* find the message id */
			p = matchhdr(buf, "message-id");
			if (p != NULL && MsgId[0] == '\0')
				prescan(p, MsgId, &MsgId[sizeof MsgId - 1], '\0');
		}
		fputs(buf, tf);
		firstline = FALSE;
		if (ferror(tf))
		{
			syserr("Cannot write %s", InFileName);
			clearerr(tf);
			break;
		}
	}
	fclose(tf);
	if (MsgId[0] == '\0')
		makemsgid();
	if (freopen(InFileName, "r", stdin) == NULL)
		syserr("Cannot reopen %s", InFileName);
	return (ArpaFmt && fbuf[0] != '\0' ? fbuf : NULL);
}
/*
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
**		none.
**
**	Side Effects:
**		Stores a message-id into MsgId.
**
D 5
**	Requires:
**		sprintf (sys)
**		getpid (sys)
**		time (sys)
**
E 5
**	Called By:
**		maketemp
D 5
**
**	History:
**		2/3/80 -- written.
E 5
*/

makemsgid()
{
	auto long t;
	extern char *MyLocName;

	time(&t);
	sprintf(MsgId, "%ld.%d.%s@Berkeley", t, getpid(), MyLocName);
}
/*
E 11
D 166
**  OPENXSCRPT -- Open transcript file
**
**	Creates a transcript file for possible eventual mailing or
**	sending back.
**
**	Parameters:
**		none
**
**	Returns:
**		none
**
**	Side Effects:
D 153
**		Turns the standard output into a special file
**			somewhere.
E 153
I 153
D 164
**		Open the transcript file.
E 164
I 164
**		Creates the transcript file.
E 164
E 153
D 51
**
D 5
**	Requires:
**		mktemp (sys)
**		chmod (sys)
**		freopen (sys)
**		syserr
**		setbuf (sys)
**
E 5
**	Called By:
**		main
E 51
D 5
**
**	History:
**		1/11/80 -- written.
E 5
*/

openxscrpt()
{
I 22
D 153
	extern char *mktemp();
E 153
I 70
	register char *p;
E 70

E 22
D 34
	mktemp(Transcript);
E 34
I 34
D 66
	(void) mktemp(Transcript);
E 34
	HasXscrpt++;
	if (freopen(Transcript, "w", stdout) == NULL)
		syserr("Can't create %s", Transcript);
D 34
	chmod(Transcript, 0600);
E 34
I 34
	(void) chmod(Transcript, 0600);
E 66
I 66
D 70
	(void) mktemp(XcriptFile);
D 67
	if (freopen(XcriptFile, "w", stdout) == NULL)
E 67
I 67
	OutChannel = fopen(XcriptFile, "w");
	if (OutChannel == NULL)
E 70
I 70
D 153
	p = newstr(XcriptFile);
	(void) mktemp(p);
E 153
I 153
	p = queuename(CurEnv, 'x');
E 153
	Xscript = fopen(p, "w");
	if (Xscript == NULL)
E 70
D 162
	{
D 70
		OutChannel = stdout;
E 67
		syserr("Can't create %s", XcriptFile);
E 70
I 70
		Xscript = stdout;
E 162
		syserr("Can't create %s", p);
E 70
I 67
D 162
	}
E 67
D 70
	(void) chmod(XcriptFile, 0600);
	Transcript = XcriptFile;
E 70
I 70
D 153
	Transcript = p;
E 153
D 150
	(void) chmod(p, 0600);
E 150
I 150
D 151
	(void) chmod(p, FileMode);
E 151
I 151
	(void) chmod(p, 0644);
I 153
	Transcript = newstr(p);
E 162
I 162
	else
		(void) chmod(p, 0644);
E 162
E 153
E 151
E 150
E 70
E 66
E 34
D 69
	setbuf(stdout, (char *) NULL);
E 69
I 62
}
/*
D 164
**  SETSENDER -- set sendmail's idea of the sender.
**
**	Parameters:
**		from -- the person we would like to believe this
**			is from.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets the idea of the sender.
*/

setsender(from)
	char *from;
{
	register char *p;
	extern char *getlogin();
	register struct passwd *pw;
	char *realname;
	char cfbuf[40];
I 79
	bool nofullname;
I 80
	extern char *macvalue();
E 80
E 79

	/*
	**  Figure out the real user executing us.
	**	Getlogin can return errno != 0 on non-errors.
	*/

D 64
	if (!Daemon)
E 64
I 64
D 67
	if (!Smtp)
E 67
I 67
D 157
	if (!Smtp && !QueueRun)
E 157
I 157
	if (OpMode != MD_SMTP && !QueueRun)
E 157
E 67
E 64
	{
		errno = 0;
		p = getlogin();
		errno = 0;
I 79
		nofullname = (from != NULL);
E 79
	}
D 64
	if (Daemon || p == NULL)
E 64
I 64
	else
I 79
	{
E 79
		p = from;
I 79
		nofullname = FALSE;
	}
E 79
D 93
	if (p != NULL)
E 93
I 93
	if (p != NULL && p[0] != '\0')
E 93
E 64
	{
I 64
		extern struct passwd *getpwnam();

		pw = getpwnam(p);
		if (pw == NULL)
		{
D 67
			if (!Smtp)
E 67
I 67
D 157
			if (!Smtp && !QueueRun)
E 157
I 157
			if (OpMode != MD_SMTP && !QueueRun)
E 157
E 67
				syserr("Who are you? (name=%s)", p);
			p = NULL;
		}
	}
D 93
	if (p == NULL)
E 93
I 93
	if (p == NULL || p[0] == '\0')
E 93
	{
E 64
		extern struct passwd *getpwuid();
		int uid;

I 79
		nofullname = TRUE;
E 79
		uid = getruid();
		pw = getpwuid(uid);
		if (pw == NULL)
			syserr("Who are you? (uid=%d)", uid);
		else
			p = pw->pw_name;
	}
D 64
	else
	{
		extern struct passwd *getpwnam();

		pw = getpwnam(p);
		if (pw == NULL)
			syserr("Who are you? (name=%s)", p);
	}
E 64
	if (p == NULL || p[0] == '\0' || pw == NULL)
		finis();

	realname = p;

	/*
	**  Process passwd file entry.
	*/

	/* run user's .mailcf file */
	define('z', pw->pw_dir);
D 95
	(void) expand("$z/.mailcf", cfbuf, &cfbuf[sizeof cfbuf - 1]);
E 95
I 95
	expand("$z/.mailcf", cfbuf, &cfbuf[sizeof cfbuf - 1], CurEnv);
E 95
D 79
	if (safefile(cfbuf, getruid(), S_IREAD))
E 79
I 79
	if (!nofullname && safefile(cfbuf, getruid(), S_IREAD))
E 79
		readcf(cfbuf, FALSE);
I 80

	/* if the user has given fullname already, don't redefine */
	if (FullName == NULL)
D 135
		FullName = macvalue('x');
E 135
I 135
		FullName = macvalue('x', CurEnv);
E 135
E 80

	/* extract full name from passwd file */
D 79
	if ((FullName == NULL || FullName[0] == '\0') &&
E 79
I 79
	if (!nofullname && (FullName == NULL || FullName[0] == '\0') &&
E 79
	    pw != NULL && pw->pw_gecos != NULL)
	{
		char nbuf[MAXNAME];

D 73
		buildfname(pw->pw_gecos, realname, nbuf);
E 73
I 73
		fullname(pw, nbuf);
E 73
D 64
		if (ArpaMode == ARPA_NONE && from == NULL && nbuf[0] != '\0')
E 64
I 64
		if (nbuf[0] != '\0')
E 64
			FullName = newstr(nbuf);
	}
	if (FullName != NULL && FullName[0] != '\0')
		define('x', FullName);

	setfrom(from, realname);
I 66
}
/*
E 164
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

initsys()
{
	static char cbuf[5];			/* holds hop count */
	static char dbuf[30];			/* holds ctime(tbuf) */
	static char pbuf[10];			/* holds pid */
D 116
	static char tbuf[10];			/* holds "current" time */
E 116
I 116
	static char tbuf[20];			/* holds "current" time */
E 116
	static char ybuf[10];			/* holds tty id */
	register char *p;
	extern char *ttyname();
	extern char *arpadate();
I 116
	register struct tm *tm;
	extern struct tm *gmtime();
I 123
	auto time_t now;
I 132

	/*
I 133
	**  Give this envelope a reality.
D 153
	**	I.e., an id and a creation time.
E 153
I 153
	**	I.e., an id, a transcript, and a creation time.
E 153
	*/

D 153
	(void) queuename(CurEnv, '\0');
E 153
I 153
	openxscrpt();
E 153
	CurEnv->e_ctime = curtime();

	/*
E 133
	**  Set OutChannel to something useful if stdout isn't it.
I 133
	**	This arranges that any extra stuff the mailer produces
	**	gets sent back to the user on error (because it is
	**	tucked away in the transcript).
E 133
	*/

D 133
	if (Mode == MD_DAEMON || HoldErrs)
E 133
I 133
D 154
	if ((Mode == MD_DAEMON && QueueRun) || HoldErrs)
E 154
I 154
D 157
	if (Mode == MD_DAEMON && QueueRun)
E 157
I 157
	if (OpMode == MD_DAEMON && QueueRun)
E 157
E 154
E 133
		OutChannel = Xscript;

	/*
	**  Set up some basic system macros.
	*/
E 132
E 123
E 116
D 72
	extern long time();
E 72

D 120
	/* convert timeout interval to absolute time */
I 67
	TimeOut -= CurTime;
E 67
	(void) time(&CurTime);
	TimeOut += CurTime;

E 120
	/* process id */
	(void) sprintf(pbuf, "%d", getpid());
D 164
	define('p', pbuf);
E 164
I 164
	define('p', pbuf, CurEnv);
E 164

	/* hop count */
D 164
	(void) sprintf(cbuf, "%d", HopCount);
	define('c', cbuf);
E 164
I 164
	(void) sprintf(cbuf, "%d", CurEnv->e_hopcount);
	define('c', cbuf, CurEnv);
E 164

	/* time as integer, unix time, arpa time */
I 120
D 123
	(void) time(&CurTime);
E 120
D 116
	(void) sprintf(tbuf, "%ld", &CurTime);
E 116
I 116
	tm = gmtime(&CurTime);
E 123
I 123
	now = curtime();
	tm = gmtime(&now);
E 123
	(void) sprintf(tbuf, "%02d%02d%02d%02d%02d", tm->tm_year, tm->tm_mon,
			tm->tm_mday, tm->tm_hour, tm->tm_min);
E 116
D 164
	define('t', tbuf);
E 164
I 164
	define('t', tbuf, CurEnv);
E 164
D 123
	(void) strcpy(dbuf, ctime(&CurTime));
E 123
I 123
	(void) strcpy(dbuf, ctime(&now));
E 123
	*index(dbuf, '\n') = '\0';
D 79
	define('d', dbuf);
	p =  newstr(arpadate(dbuf));
	define('a', p);
E 79
I 79
D 135
	if (macvalue('d') == NULL)
E 135
I 135
	if (macvalue('d', CurEnv) == NULL)
E 135
D 164
		define('d', dbuf);
E 164
I 164
		define('d', dbuf, CurEnv);
E 164
	p = newstr(arpadate(dbuf));
D 135
	if (macvalue('a') == NULL)
E 135
I 135
	if (macvalue('a', CurEnv) == NULL)
E 135
D 164
		define('a', p);
E 79
	define('b', p);
E 164
I 164
		define('a', p, CurEnv);
	define('b', p, CurEnv);
E 164

	/* version */
D 164
	define('v', Version);
E 164
I 164
	define('v', Version, CurEnv);
E 164

	/* tty name */
D 79
	p = ttyname(2);
	if (p != NULL)
E 79
I 79
D 135
	if (macvalue('y') == NULL)
E 135
I 135
	if (macvalue('y', CurEnv) == NULL)
E 135
E 79
	{
D 79
		if (rindex(p, '/') != NULL)
			p = rindex(p, '/') + 1;
		strcpy(ybuf, p);
		define('y', ybuf);
E 79
I 79
		p = ttyname(2);
		if (p != NULL)
		{
			if (rindex(p, '/') != NULL)
				p = rindex(p, '/') + 1;
D 99
			strcpy(ybuf, p);
E 99
I 99
			(void) strcpy(ybuf, p);
E 99
D 164
			define('y', ybuf);
E 164
I 164
			define('y', ybuf, CurEnv);
E 164
		}
E 79
	}
I 83
}
/*
E 166
**  INITMACROS -- initialize the macro system
**
**	This just involves defining some macros that are actually
**	used internally as metasymbols to be themselves.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		initializes several macros to be themselves.
*/

D 89
char	*MetaMacros[] =
E 89
I 89
D 240
struct metamac
E 89
{
D 89
	/* $0 .... are rewrite replacement */
	"$$0",	"$$1",	"$$2",	"$$3",	"$$4",
	"$$5",	"$$6",	"$$7",	"$$8",	"$$9",
E 89
I 89
	char	metaname;
	char	metaval;
};
E 89

E 240
I 89
struct metamac	MetaMacros[] =
{
E 89
D 197
	/* these are important on the LHS */
E 197
I 197
	/* LHS pattern matching characters */
E 197
D 89
	"$$+",	"$$-",	"$$=",
E 89
I 89
D 128
	'+',	MATCHANY,	'-',	MATCHONE,	'=',	MATCHCLASS,
E 128
I 128
D 253
	'*', MATCHZANY,	'+', MATCHANY,	'-', MATCHONE,	'=', MATCHCLASS,
I 167
	'~', MATCHNCLASS,
E 253
I 253
	'*', MATCHZANY,		'+', MATCHANY,		'-', MATCHONE,
	'=', MATCHCLASS,	'~', MATCHNCLASS,
E 253
E 167
E 128
E 89

	/* these are RHS metasymbols */
D 89
	"$$#",	"$$@",	"$$:",
E 89
I 89
D 128
	'#',	CANONNET,	'@',	CANONHOST,	':',	CANONUSER,
E 128
I 128
D 253
	'#', CANONNET,	'@', CANONHOST,	':', CANONUSER,	'>', CALLSUBR,
E 253
I 253
	'#', CANONNET,		'@', CANONHOST,		':', CANONUSER,
	'>', CALLSUBR,
E 253
I 193
	'{', MATCHLOOKUP,		'}', MATCHELOOKUP,
E 193
E 128
E 89

D 89
	NULL
E 89
I 89
D 197
	/* and finally the conditional operations */
E 197
I 197
	/* the conditional operations */
E 197
D 128
	'?',	CONDIF,		'|',	CONDELSE,	'.',	CONDFI,
E 128
I 128
D 253
	'?', CONDIF,	'|', CONDELSE,	'.', CONDFI,
E 253
I 253
	'?', CONDIF,		'|', CONDELSE,		'.', CONDFI,
E 253
I 197

D 323
	/* and finally the hostname lookup characters */
E 323
I 323
	/* the hostname lookup characters */
E 323
D 198
	'{', HOSTBEGIN,	'}', HOSTEND,
E 198
I 198
D 253
	'[', HOSTBEGIN,	']', HOSTEND,
E 253
I 253
	'[', HOSTBEGIN,		']', HOSTEND,
	'(', LOOKUPBEGIN,	')', LOOKUPEND,
I 323

	/* miscellaneous control characters */
	'&', MACRODEXPAND,
E 323
E 253
E 198
E 197
E 128

	'\0'
E 89
};

I 466
void
E 466
D 357
initmacros()
E 357
I 357
initmacros(e)
	register ENVELOPE *e;
E 357
{
D 89
	register char **pp;
E 89
I 89
	register struct metamac *m;
	char buf[5];
	register int c;
E 89

D 89
	for (pp = MetaMacros; *pp != NULL; pp++)
		define((*pp)[2], *pp);
E 89
I 89
	for (m = MetaMacros; m->metaname != '\0'; m++)
	{
		buf[0] = m->metaval;
		buf[1] = '\0';
D 164
		define(m->metaname, newstr(buf));
E 164
I 164
D 357
		define(m->metaname, newstr(buf), CurEnv);
E 357
I 357
		define(m->metaname, newstr(buf), e);
E 357
E 164
	}
	buf[0] = MATCHREPL;
	buf[2] = '\0';
	for (c = '0'; c <= '9'; c++)
	{
		buf[1] = c;
D 164
		define(c, newstr(buf));
E 164
I 164
D 357
		define(c, newstr(buf), CurEnv);
E 357
I 357
		define(c, newstr(buf), e);
E 357
E 164
	}
I 357

	/* set defaults for some macros sendmail will use later */
	define('e', "\201j Sendmail \201v ready at \201b", e);
	define('l', "From \201g  \201d", e);
	define('n', "MAILER-DAEMON", e);
	define('o', ".:@[]", e);
	define('q', "<\201g>", e);
E 357
I 95
}
D 361
/*
D 166
**  NEWENVELOPE -- allocate a new envelope
**
**	Supports inheritance.
**
**	Parameters:
**		e -- the new envelope to fill in.
**
**	Returns:
**		e.
**
**	Side Effects:
**		none.
*/

ENVELOPE *
newenvelope(e)
	register ENVELOPE *e;
{
I 151
	register HDR *bh;
	register HDR **nhp;
I 164
	register ENVELOPE *parent;
E 164

I 164
	parent = CurEnv;
	if (e == CurEnv)
		parent = e->e_parent;
E 164
E 151
D 99
	bmove(CurEnv, e, sizeof *e);
E 99
I 99
D 135
	bmove((char *) CurEnv, (char *) e, sizeof *e);
E 99
	e->e_header = NULL;
	e->e_queueup = FALSE;
I 120
	e->e_dontqueue = FALSE;
E 120
	e->e_oldstyle = FALSE;
D 129
	e->e_retreceipt = FALSE;
E 129
	e->e_sendreceipt = FALSE;
D 129
	e->e_origfrom = NULL;
E 129
I 129
	e->e_receiptto = NULL;
E 129
	e->e_to = NULL;
	e->e_sendqueue = NULL;
I 101
	e->e_errorqueue = NULL;
E 135
I 135
	clear((char *) e, sizeof *e);
D 163
	bmove(&CurEnv->e_from, &e->e_from, sizeof e->e_from);
E 163
I 163
	bmove((char *) &CurEnv->e_from, (char *) &e->e_from, sizeof e->e_from);
E 163
E 135
E 101
D 164
	e->e_parent = CurEnv;
E 164
I 164
	e->e_parent = parent;
E 164
D 135
	e->e_df = NULL;
I 118
	e->e_qf = NULL;
	e->e_id = NULL;
E 135
I 120
D 123
	e->e_ctime = CurTime;
E 123
I 123
	e->e_ctime = curtime();
I 135
D 164
	e->e_puthdr = CurEnv->e_puthdr;
	e->e_putbody = CurEnv->e_putbody;
E 164
I 164
	e->e_puthdr = parent->e_puthdr;
	e->e_putbody = parent->e_putbody;
E 164
I 151
	bh = BlankEnvelope.e_header;
	nhp = &e->e_header;
	while (bh != NULL)
	{
		*nhp = (HDR *) xalloc(sizeof *bh);
		bmove((char *) bh, (char *) *nhp, sizeof *bh);
		bh = bh->h_link;
		nhp = &(*nhp)->h_link;
	}
I 164
	if (Xscript != NULL)
		(void) fflush(Xscript);
E 164
E 151
E 135
E 123
E 120
E 118
I 97

	return (e);
I 118
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
I 162
**		Unlocks this queue file.
E 162
*/

dropenvelope(e)
	register ENVELOPE *e;
{
D 162
	if (e->e_df != NULL)
		xunlink(e->e_df);
	if (e->e_qf != NULL)
		xunlink(e->e_qf);
	if (e->e_id != NULL)
		xunlink(queuename(e, 'l'));
E 162
I 162
	bool queueit = FALSE;
D 164
	bool sendreceipt = bitset(EF_SENDRECEIPT, e->e_flags);
E 164
	register ADDRESS *q;

#ifdef DEBUG
	if (tTd(50, 1))
		printf("dropenvelope %x id=\"%s\" flags=%o\n", e, e->e_id,
			e->e_flags);
#endif DEBUG

	/* we must have an id to remove disk files */
	if (e->e_id == NULL)
		return;

	/*
	**  Extract state information from dregs of send list.
	*/

	for (q = e->e_sendqueue; q != NULL; q = q->q_next)
	{
		if (bitset(QQUEUEUP, q->q_flags))
			queueit = TRUE;
D 164
		if (bitset(QBADADDR, q->q_flags))
			sendreceipt = TRUE;
E 164
	}

	/*
	**  Send back return receipts as requested.
	*/

D 164
	if (e->e_receiptto != NULL && sendreceipt)
E 164
I 164
	if (e->e_receiptto != NULL && bitset(EF_SENDRECEIPT, e->e_flags))
E 164
	{
		auto ADDRESS *rlist;

		sendto(CurEnv->e_receiptto, (ADDRESS *) NULL, &rlist);
		(void) returntosender("Return receipt", rlist, FALSE);
	}

	/*
	**  See if this message has timed out
	*/

	if (bitset(EF_TIMEOUT, e->e_flags) && queueit)
		timeout(e);

	/*
	**  Arrange to send error messages if there are fatal errors.
	*/

	if (bitset(EF_FATALERRS, e->e_flags))
		savemail(e);

	/*
	**  Instantiate or deinstantiate the queue.
	*/

	if ((!queueit && !bitset(EF_KEEPQUEUE, e->e_flags)) ||
	    bitset(EF_CLRQUEUE, e->e_flags))
	{
		if (e->e_df != NULL)
			xunlink(e->e_df);
		xunlink(queuename(e, 'q'));
	}
	else if (queueit || !bitset(EF_INQUEUE, e->e_flags))
D 164
		queueup(e, FALSE);
E 164
I 164
		queueup(e, FALSE, FALSE);
E 164

D 164
	/* in any case, remove the transcript */
E 164
I 164
	/* now unlock the job */
	unlockqueue(e);

	/* make sure that this envelope is marked unused */
	e->e_id = e->e_df = NULL;
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

unlockqueue(e)
	ENVELOPE *e;
{
	/* remove the transcript */
E 164
#ifdef DEBUG
	if (!tTd(51, 4))
#endif DEBUG
		xunlink(queuename(e, 'x'));

	/* last but not least, remove the lock */
	xunlink(queuename(e, 'l'));
E 162
}
/*
**  QUEUENAME -- build a file name in the queue directory for this envelope.
**
**	Assigns an id code if one does not already exist.
I 139
**	This code is very careful to avoid trashing existing files
**	under any circumstances.
D 153
**		We first create an xf file that is only used when
E 153
I 153
**		We first create an nf file that is only used when
E 153
**		assigning an id.  This file is always empty, so that
**		we can never accidently truncate an lf file.
E 139
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
I 161
D 164
	/* these must go in initialized data space for freeze/thaw in smtp */
E 164
	static int pid = -1;
D 164
	static char c1 = 'A';
	static char c2 = 'A';
E 164
I 164
	char c1 = 'A';
	char c2 = 'A';
E 164
E 161

	if (e->e_id == NULL)
	{
D 134
		char counter = 'a' - 1;
		char qf[MAXNAME];
		char lf[MAXNAME];
		int fx;
E 134
I 134
D 161
		char counter = 'A' - 1;
E 161
		char qf[20];
		char lf[20];
I 139
D 153
		char xf[20];
E 153
I 153
		char nf[20];
E 153
E 139
E 134

		/* find a unique id */
D 134
		fx = strlen(QueueDir) + 3;
		(void) sprintf(qf, "%s/qf_%05d", QueueDir, getpid());
E 134
I 134
D 161
		(void) sprintf(qf, "qf_%05d", getpid());
E 161
I 161
		if (pid != getpid())
		{
			/* new process -- start back at "AA" */
			pid = getpid();
			c1 = 'A';
			c2 = 'A' - 1;
		}
		(void) sprintf(qf, "qfAA%05d", pid);
E 161
E 134
		strcpy(lf, qf);
D 134
		lf[fx - 2] = 'l';
E 134
I 134
		lf[0] = 'l';
I 139
D 153
		strcpy(xf, qf);
		xf[0] = 'x';
E 153
I 153
		strcpy(nf, qf);
		nf[0] = 'n';
E 153
E 139
E 134

D 134
		for (;;)
E 134
I 134
D 161
		while (counter < '~')
E 161
I 161
		while (c1 < '~' || c2 < 'Z')
E 161
E 134
		{
D 134
			qf[fx] = lf[fx] = ++counter;
E 134
I 134
D 139
			int fd;
E 139
I 139
			int i;
E 139

D 139
			qf[2] = lf[2] = ++counter;
E 139
I 139
D 153
			qf[2] = lf[2] = xf[2] = ++counter;
E 153
I 153
D 161
			qf[2] = lf[2] = nf[2] = ++counter;
E 161
I 161
			if (c2 >= 'Z')
			{
				c1++;
				c2 = 'A' - 1;
			}
			qf[2] = lf[2] = nf[2] = c1;
			qf[3] = lf[3] = nf[3] = ++c2;
E 161
E 153
E 139
# ifdef DEBUG
			if (tTd(7, 20))
D 139
				printf("queuename: trying \"%s\"\n", lf);
E 139
I 139
D 153
				printf("queuename: trying \"%s\"\n", xf);
E 153
I 153
				printf("queuename: trying \"%s\"\n", nf);
E 153
E 139
# endif DEBUG
E 134
			if (access(lf, 0) >= 0 || access(qf, 0) >= 0)
				continue;
			errno = 0;
D 134
			if (close(creat(lf, 0600)) < 0)
E 134
I 134
D 139
			fd = creat(lf, 0600);
			if (fd < 0)
E 139
I 139
D 150
			i = creat(xf, 0600);
E 150
I 150
D 153
			i = creat(xf, FileMode);
E 153
I 153
			i = creat(nf, FileMode);
E 153
E 150
			if (i < 0)
E 139
			{
D 139
				(void) unlink(lf);	/* kernel bug on ENFILE */
E 139
I 139
D 153
				(void) unlink(xf);	/* kernel bug */
E 153
I 153
				(void) unlink(nf);	/* kernel bug */
E 153
E 139
E 134
				continue;
I 134
			}
D 139
			(void) close(fd);
E 134
			if (link(lf, qf) < 0)
				(void) unlink(lf);
			else
E 139
I 139
			(void) close(i);
D 153
			i = link(xf, lf);
			(void) unlink(xf);
E 153
I 153
			i = link(nf, lf);
			(void) unlink(nf);
E 153
			if (i < 0)
				continue;
			if (link(lf, qf) >= 0)
E 139
				break;
I 139
			(void) unlink(lf);
E 139
		}
I 134
D 161
		if (counter >= '~')
E 161
I 161
		if (c1 >= '~' && c2 >= 'Z')
E 161
		{
			syserr("queuename: Cannot create \"%s\" in \"%s\"",
				lf, QueueDir);
			exit(EX_OSERR);
		}
E 134
D 162
		e->e_qf = newstr(qf);
D 134
		e->e_id = &e->e_qf[fx];
E 134
I 134
		e->e_id = &e->e_qf[2];
E 162
I 162
		e->e_id = newstr(&qf[2]);
E 162
E 134
I 119
D 164
		define('i', e->e_id);
E 164
I 164
		define('i', e->e_id, e);
E 164
E 119
# ifdef DEBUG
		if (tTd(7, 1))
			printf("queuename: assigned id %s, env=%x\n", e->e_id, e);
# endif DEBUG
	}

	if (type == '\0')
		return (NULL);
D 134
	(void) sprintf(buf, "%s/%cf%s", QueueDir, type, e->e_id);
E 134
I 134
	(void) sprintf(buf, "%cf%s", type, e->e_id);
E 134
# ifdef DEBUG
	if (tTd(7, 2))
		printf("queuename: %s\n", buf);
# endif DEBUG
	return (buf);
I 153
}
/*
E 166
**  FREEZE -- freeze BSS & allocated memory
**
**	This will be used to efficiently load the configuration file.
**
**	Parameters:
D 161
**		none.
E 161
I 161
**		freezefile -- the name of the file to freeze to.
E 161
**
**	Returns:
**		none.
**
**	Side Effects:
D 161
**		Writes BSS and malloc'ed memory to FreezeFile
E 161
I 161
**		Writes BSS and malloc'ed memory to freezefile
E 161
*/

I 296
# ifdef FROZENCONFIG

E 296
D 164
struct frz
E 164
I 164
union frz
E 164
{
D 164
	time_t	frzstamp;		/* timestamp on this freeze */
	char	*frzbrk;		/* the current break */
	char	frzver[252];		/* sendmail version */
E 164
I 164
	char		frzpad[BUFSIZ];	/* insure we are on a BUFSIZ boundary */
	struct
	{
		time_t	frzstamp;	/* timestamp on this freeze */
		char	*frzbrk;	/* the current break */
I 208
		char	*frzedata;	/* address of edata */
		char	*frzend;	/* address of end */
E 208
		char	frzver[252];	/* sendmail version */
	} frzinfo;
E 164
};

I 284
D 310
#ifdef __hpux
E 310
I 310
#if defined(__hpux) || defined(__alpha)
E 310
#define BRK_TYPE        int
#define SBRK_TYPE       void *
#else
#define BRK_TYPE        char *
#define SBRK_TYPE       char *
#endif

E 284
D 161
freeze()
E 161
I 161
freeze(freezefile)
	char *freezefile;
E 161
{
	int f;
D 164
	struct frz fhdr;
E 164
I 164
	union frz fhdr;
I 284
	extern SBRK_TYPE sbrk();
E 284
E 164
D 208
	extern char edata;
E 208
I 208
	extern char edata, end;
E 208
D 284
	extern char *sbrk();
E 284
I 166
	extern char Version[];
E 166

D 161
	if (FreezeFile == NULL)
E 161
I 161
	if (freezefile == NULL)
E 161
		return;

	/* try to open the freeze file */
D 161
	f = open(FreezeFile, 1);
E 161
I 161
	f = creat(freezefile, FileMode);
E 161
	if (f < 0)
	{
D 226
		syserr("Cannot freeze");
E 226
I 226
		syserr("Cannot freeze %s", freezefile);
E 226
		errno = 0;
		return;
	}

	/* build the freeze header */
D 164
	fhdr.frzstamp = curtime();
	fhdr.frzbrk = sbrk(0);
	strcpy(fhdr.frzver, Version);
E 164
I 164
	fhdr.frzinfo.frzstamp = curtime();
	fhdr.frzinfo.frzbrk = sbrk(0);
I 208
	fhdr.frzinfo.frzedata = &edata;
	fhdr.frzinfo.frzend = &end;
E 208
D 205
	strcpy(fhdr.frzinfo.frzver, Version);
E 205
I 205
	(void) strcpy(fhdr.frzinfo.frzver, Version);
E 205
E 164

	/* write out the freeze header */
D 163
	if (write(f, &fhdr, sizeof fhdr) != sizeof fhdr ||
	    write(f, &edata, fhdr.frzbrk - &edata) != (fhdr.frzbrk - &edata))
E 163
I 163
	if (write(f, (char *) &fhdr, sizeof fhdr) != sizeof fhdr ||
D 164
	    write(f, (char *) &edata, fhdr.frzbrk - &edata) != (fhdr.frzbrk - &edata))
E 164
I 164
D 196
	    write(f, (char *) &edata, fhdr.frzinfo.frzbrk - &edata) !=
					(fhdr.frzinfo.frzbrk - &edata))
E 196
I 196
	    write(f, (char *) &edata, (int) (fhdr.frzinfo.frzbrk - &edata)) !=
					(int) (fhdr.frzinfo.frzbrk - &edata))
E 196
	{
E 164
E 163
D 226
		syserr("Cannot freeze");
E 226
I 226
		syserr("Cannot freeze %s", freezefile);
E 226
I 164
	}
E 164

	/* fine, clean up */
	(void) close(f);
}
/*
**  THAW -- read in the frozen configuration file.
**
**	Parameters:
D 161
**		none.
E 161
I 161
**		freezefile -- the name of the file to thaw from.
I 274
**		binfile -- the name of the sendmail binary (ok to guess).
E 274
E 161
**
**	Returns:
**		TRUE if it successfully read the freeze file.
**		FALSE otherwise.
**
**	Side Effects:
D 161
**		reads FreezeFile in to BSS area.
E 161
I 161
**		reads freezefile in to BSS area.
E 161
*/

D 161
thaw()
E 161
I 161
D 274
thaw(freezefile)
E 274
I 274
thaw(freezefile, binfile)
E 274
	char *freezefile;
I 274
	char *binfile;
E 274
E 161
{
	int f;
I 238
	register char *p;
E 238
D 164
	struct frz fhdr;
E 164
I 164
	union frz fhdr;
I 238
	char hbuf[60];
I 274
	struct stat fst, sst;
E 274
E 238
E 164
D 218
	extern char edata;
E 218
I 218
	extern char edata, end;
E 218
I 166
	extern char Version[];
I 206
D 284
	extern caddr_t brk();
E 284
I 238
	extern char **myhostname();
D 336
	extern char *macvalue();
E 336
I 284
	extern BRK_TYPE brk();
E 284
E 238
E 206
E 166

D 161
	if (FreezeFile == NULL)
E 161
I 161
	if (freezefile == NULL)
E 161
		return (FALSE);

	/* open the freeze file */
D 161
	f = open(FreezeFile, 0);
E 161
I 161
	f = open(freezefile, 0);
E 161
	if (f < 0)
	{
I 231
D 241
		syslog(LOG_WARNING, "Cannot open frozen config file %s: %m",
			freezefile);
E 241
E 231
		errno = 0;
I 274
		return (FALSE);
	}

	if (fstat(f, &fst) < 0 || stat(ConfFile, &sst) < 0 ||
	    fst.st_mtime < sst.st_mtime)
	{
		syslog(LOG_WARNING, "Freeze file older than config file");
		(void) close(f);
		return (FALSE);
	}

	if (strchr(binfile, '/') != NULL && stat(binfile, &sst) == 0 &&
	    fst.st_mtime < sst.st_mtime)
	{
		syslog(LOG_WARNING, "Freeze file older than binary file");
		(void) close(f);
E 274
		return (FALSE);
	}

	/* read in the header */
D 163
	if (read(f, &fhdr, sizeof fhdr) < sizeof fhdr ||
E 163
I 163
D 231
	if (read(f, (char *) &fhdr, sizeof fhdr) < sizeof fhdr ||
I 208
	    fhdr.frzinfo.frzedata != &edata ||
E 231
I 231
	if (read(f, (char *) &fhdr, sizeof fhdr) < sizeof fhdr)
	{
D 241
		syserr("Cannot read frozen config file");
E 241
I 241
		syslog(LOG_WARNING, "Cannot read frozen config file");
E 241
		(void) close(f);
		return (FALSE);
	}
D 241
	if ( fhdr.frzinfo.frzedata != &edata ||
E 241
I 241
	if (fhdr.frzinfo.frzedata != &edata ||
E 241
E 231
	    fhdr.frzinfo.frzend != &end ||
E 208
E 163
D 164
	    strcmp(fhdr.frzver, Version) != 0)
E 164
I 164
	    strcmp(fhdr.frzinfo.frzver, Version) != 0)
E 164
	{
I 314
		fprintf(stderr, "Wrong version of frozen config file\n");
E 314
I 231
		syslog(LOG_WARNING, "Wrong version of frozen config file");
E 231
		(void) close(f);
		return (FALSE);
	}

	/* arrange to have enough space */
D 164
	if (brk(fhdr.frzbrk) < 0)
E 164
I 164
D 206
	if (brk(fhdr.frzinfo.frzbrk) < 0)
E 206
I 206
D 310
	if (brk(fhdr.frzinfo.frzbrk) == (caddr_t) -1)
E 310
I 310
	if (brk(fhdr.frzinfo.frzbrk) == (BRK_TYPE) -1)
E 310
E 206
E 164
	{
D 164
		syserr("Cannot break to %x", fhdr.frzbrk);
E 164
I 164
		syserr("Cannot break to %x", fhdr.frzinfo.frzbrk);
E 164
		(void) close(f);
		return (FALSE);
	}

	/* now read in the freeze file */
D 163
	if (read(f, &edata, fhdr.frzbrk - &edata) != (fhdr.frzbrk - &edata))
E 163
I 163
D 164
	if (read(f, (char *) &edata, fhdr.frzbrk - &edata) != (fhdr.frzbrk - &edata))
E 164
I 164
D 196
	if (read(f, (char *) &edata, fhdr.frzinfo.frzbrk - &edata) !=
					(fhdr.frzinfo.frzbrk - &edata))
E 196
I 196
	if (read(f, (char *) &edata, (int) (fhdr.frzinfo.frzbrk - &edata)) !=
					(int) (fhdr.frzinfo.frzbrk - &edata))
E 196
E 164
E 163
	{
I 231
		syserr("Cannot read frozen config file");
E 231
		/* oops!  we have trashed memory..... */
D 164
		fprintf(stderr, "Cannot read freeze file\n");
		exit(EX_SOFTWARE);
E 164
I 164
D 205
		write(2, "Cannot read freeze file\n", 24);
E 205
I 205
		(void) write(2, "Cannot read freeze file\n", 24);
E 205
		_exit(EX_SOFTWARE);
E 164
	}

	(void) close(f);
D 238
	return (TRUE);
E 238
I 238

	/* verify that the host name was correct on the freeze */
	(void) myhostname(hbuf, sizeof hbuf);
D 356
	p = macvalue('w', CurEnv);
E 356
I 356
	p = macvalue('j', CurEnv);
E 356
	if (p == NULL)
		p = "";
D 356
	if (strcmp(hbuf, macvalue('w', CurEnv)) == 0)
E 356
I 356
	if (strcmp(hbuf, macvalue('j', CurEnv)) == 0)
E 356
		return (TRUE);
	syslog(LOG_WARNING, "Hostname changed since freeze (%s => %s)",
		p, hbuf);
	return (FALSE);
E 238
I 159
}
I 296

# endif /* FROZENCONFIG */
E 361
E 296
/*
**  DISCONNECT -- remove our connection with any foreground process
**
**	Parameters:
D 165
**		all -- if set, disconnect InChannel and OutChannel also.
E 165
I 165
D 172
**		none.
E 172
I 172
D 343
**		fulldrop -- if set, we should also drop the controlling
**			TTY if possible -- this should only be done when
**			setting up the daemon since otherwise UUCP can
**			leave us trying to open a dialin, and we will
**			wait for the carrier.
E 343
I 343
**		droplev -- how "deeply" we should drop the line.
**			0 -- ignore signals, mail back errors, make sure
**			     output goes to stdout.
**			1 -- also, make stdout go to transcript.
**			2 -- also, disconnect from controlling terminal
**			     (only for daemon mode).
**		e -- the current envelope.
E 343
E 172
E 165
**
**	Returns:
**		none
**
**	Side Effects:
**		Trys to insure that we are immune to vagaries of
**		the controlling tty.
*/

I 466
void
E 466
D 165
disconnect(all)
	bool all;
E 165
I 165
D 172
disconnect()
E 172
I 172
D 306
disconnect(fulldrop)
E 306
I 306
D 343
disconnect(fulldrop, e)
E 306
	bool fulldrop;
E 343
I 343
disconnect(droplev, e)
	int droplev;
E 343
I 306
	register ENVELOPE *e;
E 306
E 172
E 165
{
	int fd;

D 162
#ifdef TIOCNOTTY
	/* drop our controlling TTY completely if possible */
	fd = open("/dev/tty", 2);
	if (fd >= 0)
E 162
I 162
D 229
#ifdef DEBUG
E 229
	if (tTd(52, 1))
D 165
		printf("disconnect(%d): In %d Out %d Xs %d\n", all,
			fileno(InChannel), fileno(OutChannel), fileno(Xscript));
E 165
I 165
D 306
		printf("disconnect: In %d Out %d\n", fileno(InChannel),
						fileno(OutChannel));
E 306
I 306
		printf("disconnect: In %d Out %d, e=%x\n",
			fileno(InChannel), fileno(OutChannel), e);
E 306
E 165
D 470
	if (tTd(52, 5))
E 470
I 470
	if (tTd(52, 100))
E 470
E 162
	{
D 162
		(void) ioctl(fd, TIOCNOTTY, 0);
		(void) close(fd);
E 162
I 162
		printf("don't\n");
		return;
E 162
	}
D 162
#endif TIOCNOTTY
E 162
I 162
D 229
#endif DEBUG
E 229
E 162

	/* be sure we don't get nasty signals */
D 205
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
E 205
I 205
D 350
	(void) signal(SIGHUP, SIG_IGN);
	(void) signal(SIGINT, SIG_IGN);
	(void) signal(SIGQUIT, SIG_IGN);
E 350
I 350
D 415
	(void) setsignal(SIGHUP, SIG_IGN);
E 415
	(void) setsignal(SIGINT, SIG_IGN);
	(void) setsignal(SIGQUIT, SIG_IGN);
E 350
E 205

	/* we can't communicate with our caller, so.... */
D 164
	HoldErrs = MailBack = TRUE;
E 164
I 164
	HoldErrs = TRUE;
D 312
	ErrorMode = EM_MAIL;
E 312
I 312
	CurEnv->e_errormode = EM_MAIL;
E 312
E 164
	Verbose = FALSE;
I 388
	DisConnected = TRUE;
E 388

	/* all input from /dev/null */
D 165
	if (all)
		(void) freopen("/dev/null", "r", InChannel);
E 165
	if (InChannel != stdin)
D 165
		(void) freopen("/dev/null", "r", stdin);
E 165
I 165
	{
		(void) fclose(InChannel);
		InChannel = stdin;
	}
	(void) freopen("/dev/null", "r", stdin);
E 165

	/* output to the transcript */
D 165
	if (all || OutChannel != stdout)
E 165
I 165
	if (OutChannel != stdout)
E 165
	{
I 162
D 165
		if (OutChannel != stdout)
		{
			(void) fclose(OutChannel);
			OutChannel = Xscript;
		}
		(void) fflush(stdout);
E 162
		(void) close(1);
D 162
		(void) dup(fileno(Xscript));
		(void) fclose(OutChannel);
		OutChannel = Xscript;
E 162
I 162
		(void) close(2);
		while ((fd = dup(fileno(Xscript))) < 2 && fd > 0)
			continue;
E 165
I 165
		(void) fclose(OutChannel);
		OutChannel = stdout;
E 165
E 162
	}
I 165
D 166
	if (Xscript == NULL)
		Xscript = fopen("/dev/null", "w");
E 166
I 166
D 306
	if (CurEnv->e_xfp == NULL)
		CurEnv->e_xfp = fopen("/dev/null", "w");
E 306
I 306
D 343
	if (e->e_xfp == NULL)
		fd = open("/dev/null", O_WRONLY, 0666);
	else
		fd = fileno(e->e_xfp);
E 306
E 166
	(void) fflush(stdout);
D 306
	(void) close(1);
	(void) close(2);
D 166
	while ((fd = dup(fileno(Xscript))) < 2 && fd > 0)
E 166
I 166
	while ((fd = dup(fileno(CurEnv->e_xfp))) < 2 && fd > 0)
E 166
		continue;
E 306
I 306
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	if (e->e_xfp == NULL)
		close(fd);
E 343
I 343
	if (droplev > 0)
	{
		if (e->e_xfp == NULL)
			fd = open("/dev/null", O_WRONLY, 0666);
		else
			fd = fileno(e->e_xfp);
		(void) fflush(stdout);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (e->e_xfp == NULL)
			close(fd);
	}
E 343
E 306
E 165
I 162

D 234
#ifdef TIOCNOTTY
E 234
	/* drop our controlling TTY completely if possible */
D 172
	fd = open("/dev/tty", 2);
	if (fd >= 0)
E 172
I 172
D 343
	if (fulldrop)
E 343
I 343
	if (droplev > 1)
E 343
E 172
	{
I 281
D 327
#ifdef SYSTEM5
		(void) setpgrp();
#else
E 327
E 281
I 234
D 264
#if BSD > 43
		daemon(1, 1);
#else
E 264
I 264
		(void) setsid();
I 281
D 327
#endif
E 327
E 281
E 264
D 355
#ifdef TIOCNOTTY
E 234
D 172
		(void) ioctl(fd, TIOCNOTTY, 0);
		(void) close(fd);
E 172
I 172
		fd = open("/dev/tty", 2);
		if (fd >= 0)
		{
D 206
			(void) ioctl(fd, TIOCNOTTY, 0);
E 206
I 206
			(void) ioctl(fd, (int) TIOCNOTTY, (char *) 0);
E 206
			(void) close(fd);
		}
I 199
D 205
		setpgrp(0);
E 205
I 205
D 206
		(void) setpgrp(0);
E 206
I 206
		(void) setpgrp(0, 0);
I 234
#endif /* TIOCNOTTY */
E 355
D 264
#endif /* BSD */
E 264
E 234
E 206
E 205
E 199
I 181
		errno = 0;
E 181
E 172
	}
D 234
#endif TIOCNOTTY
E 234
E 162

I 365
D 478
#ifdef XDEBUG
E 478
I 478
#if XDEBUG
E 478
	checkfd012("disconnect");
#endif

E 365
# ifdef LOG
D 285
	if (LogLevel > 11)
E 285
I 285
	if (LogLevel > 71)
E 285
		syslog(LOG_DEBUG, "in background, pid=%d", getpid());
D 263
# endif LOG
E 263
I 263
# endif /* LOG */
E 263

	errno = 0;
I 267
}

static void
obsolete(argv)
	char *argv[];
{
D 385
	char *ap;
E 385
I 385
	register char *ap;
	register char *op;
E 385

D 339
	while (ap = *++argv)
E 339
I 339
	while ((ap = *++argv) != NULL)
E 339
	{
		/* Return if "--" or not an option of any form. */
		if (ap[0] != '-' || ap[1] == '-')
			return;

I 385
		/* skip over options that do have a value */
		op = strchr(OPTIONS, ap[1]);
		if (op != NULL && *++op == ':' && ap[2] == '\0' &&
D 389
		    argv[1] != NULL && argv[1][0] != '-')
E 389
I 389
D 444
		    ap[1] != 'd' && argv[1] != NULL && argv[1][0] != '-')
E 444
I 444
		    ap[1] != 'd' &&
#if defined(sony_news)
		    ap[1] != 'E' && ap[1] != 'J' &&
#endif
		    argv[1] != NULL && argv[1][0] != '-')
E 444
E 389
		{
			argv++;
			continue;
		}

E 385
		/* If -C doesn't have an argument, use sendmail.cf. */
#define	__DEFPATH	"sendmail.cf"
D 268
		if (ap[1] == 'C' &&
		    !ap[2] && (argv[0] == NULL || argv[0][0] == '-'))
E 268
I 268
D 385
		if (ap[1] == 'C' && ap[2] == '\0' &&
		    (argv[1] == NULL || argv[1][0] == '-'))
E 385
I 385
		if (ap[1] == 'C' && ap[2] == '\0')
E 385
E 268
		{
			*argv = xalloc(sizeof(__DEFPATH) + 2);
			argv[0][0] = '-';
			argv[0][1] = 'C';
			(void)strcpy(&argv[0][2], __DEFPATH);
		}
D 268
		if (ap[1] == 'q' &&
		    !ap[2] && (argv[0] == NULL || argv[0][0] == '-'))
		{
			*argv = xalloc(4);
			argv[0][0] = '-';
			argv[0][1] = 'C';
			argv[0][2] = '1';
			argv[0][3] = '\0';
		}
E 268
I 268

		/* If -q doesn't have an argument, run it once. */
D 385
		if (ap[1] == 'q' && ap[2] == '\0' &&
		    (argv[1] == NULL || argv[1][0] == '-'))
E 385
I 385
		if (ap[1] == 'q' && ap[2] == '\0')
E 385
			*argv = "-q0";
I 269

		/* if -d doesn't have an argument, use 0-99.1 */
D 385
		if (ap[1] == 'd' && ap[2] == '\0' &&
D 318
		    (argv[1] == NULL || argv[1][0] == '-'))
E 318
I 318
		    (argv[1] == NULL || !isdigit(argv[1][0])))
E 385
I 385
		if (ap[1] == 'd' && ap[2] == '\0')
E 385
E 318
			*argv = "-d0-99.1";
I 444

# if defined(sony_news)
		/* if -E doesn't have an argument, use -EC */
		if (ap[1] == 'E' && ap[2] == '\0')
			*argv = "-EC";

		/* if -J doesn't have an argument, use -JJ */
		if (ap[1] == 'J' && ap[2] == '\0')
			*argv = "-JJ";
# endif
E 444
I 313
	}
}
/*
**  AUTH_WARNING -- specify authorization warning
**
**	Parameters:
**		e -- the current envelope.
**		msg -- the text of the message.
**		args -- arguments to the message.
**
**	Returns:
**		none.
*/

D 316
#ifdef __STDC__
E 316
void
I 316
#ifdef __STDC__
E 316
D 333
auth_warning(register ENVELOPE *e, char *msg, ...)
E 333
I 333
auth_warning(register ENVELOPE *e, const char *msg, ...)
E 333
#else
auth_warning(e, msg, va_alist)
	register ENVELOPE *e;
D 333
	char *msg;
E 333
I 333
	const char *msg;
E 333
	va_dcl
#endif
{
	char buf[MAXLINE];
	VA_LOCAL_DECL

	if (bitset(PRIV_AUTHWARNINGS, PrivacyFlags))
	{
		register char *p;
		static char hostbuf[48];
D 395
		extern char **myhostname();
E 395
I 395
		extern struct hostent *myhostname();
E 395

		if (hostbuf[0] == '\0')
			(void) myhostname(hostbuf, sizeof hostbuf);

D 317
		(void) sprintf(buf, "from %s: ", hostbuf);
E 317
I 317
		(void) sprintf(buf, "%s: ", hostbuf);
E 317
		p = &buf[strlen(buf)];
		VA_START(msg);
		vsprintf(p, msg, ap);
		VA_END;
D 329
		addheader("x-authentication-warning", buf, e);
E 329
I 329
D 402
		addheader("X-Authentication-Warning", buf, e);
E 402
I 402
		addheader("X-Authentication-Warning", buf, &e->e_header);
I 444
D 479
#if LOG
E 479
I 479
#ifdef LOG
E 479
		if (LogLevel > 3)
			syslog(LOG_INFO, "%s: Authentication-Warning: %s",
				e->e_id == NULL ? "[NOQUEUE]" : e->e_id, buf);
#endif
I 455
	}
}
/*
**  SETUSERENV -- set an environment in the propogated environment
**
**	Parameters:
**		envar -- the name of the environment variable.
**		value -- the value to which it should be set.  If
**			null, this is extracted from the incoming
**			environment.  If that is not set, the call
**			to setuserenv is ignored.
**
**	Returns:
**		none.
*/

I 466
void
E 466
setuserenv(envar, value)
D 466
	char *envar;
	char *value;
E 466
I 466
	const char *envar;
	const char *value;
E 466
{
	int i;
	char **evp = UserEnviron;
D 456
	char buf[100];
E 456
I 456
	char *p;
E 456

	if (value == NULL)
	{
		value = getenv(envar);
		if (value == NULL)
			return;
	}

	i = strlen(envar);
D 456
	if (i + strlen(value) > sizeof buf - 2)
		return;
E 456
I 456
	p = (char *) xalloc(strlen(value) + i + 2);
	strcpy(p, envar);
	p[i++] = '=';
	strcpy(&p[i], value);
E 456

D 456
	strcpy(buf, envar);
	buf[i++] = '=';
	strcpy(&buf[i], value);

	while (*evp != NULL && strncmp(*evp, buf, i) != 0)
E 456
I 456
	while (*evp != NULL && strncmp(*evp, p, i) != 0)
E 456
		evp++;
	if (*evp != NULL)
	{
D 456
		*evp++ = newstr(buf);
E 456
I 456
		*evp++ = p;
E 456
	}
	else if (evp < &UserEnviron[MAXUSERENVIRON])
	{
D 456
		*evp++ = newstr(buf);
E 456
I 456
		*evp++ = p;
E 456
		*evp = NULL;
E 455
E 444
E 402
E 329
E 313
E 269
E 268
	}
I 456

	/* make sure it is in our environment as well */
D 463
	putenv(p);
E 463
I 463
	if (putenv(p) < 0)
		syserr("setuserenv: putenv(%s) failed", p);
E 463
E 456
I 379
}
/*
D 394
**  DUMPSTATE -- dump state on user signal
E 394
I 394
**  DUMPSTATE -- dump state
E 394
**
**	For debugging.
*/

void
D 394
dumpstate()
E 394
I 394
dumpstate(when)
	char *when;
E 394
{
#ifdef LOG
D 380
	syslog(LOG_DEBUG, "--- dumping state on user signal: open file descriptors: ---");
E 380
I 380
	register char *j = macvalue('j', CurEnv);
D 416
	register STAB *s;
E 416

D 394
	syslog(LOG_DEBUG, "--- dumping state on user signal: $j = %s ---", j);
	s = stab(j, ST_CLASS, ST_FIND);
	if (s == NULL || !bitnset('w', s->s_class))
		syslog(LOG_DEBUG, "*** $j not in $=w ***");
E 394
I 394
	syslog(LOG_DEBUG, "--- dumping state on %s: $j = %s ---",
		when,
		j == NULL ? "<NULL>" : j);
	if (j != NULL)
	{
D 416
		s = stab(j, ST_CLASS, ST_FIND);
		if (s == NULL || !bitnset('w', s->s_class))
E 416
I 416
		if (!wordinclass(j, 'w'))
E 416
			syslog(LOG_DEBUG, "*** $j not in $=w ***");
	}
I 472
	syslog(LOG_DEBUG, "CurChildren = %d", CurChildren);
E 472
E 394
	syslog(LOG_DEBUG, "--- open file descriptors: ---");
E 380
	printopenfds(TRUE);
	syslog(LOG_DEBUG, "--- connection cache: ---");
	mci_dump_all(TRUE);
I 383
	if (RewriteRules[89] != NULL)
	{
		int stat;
		register char **pvp;
		char *pv[MAXATOM + 1];

		pv[0] = NULL;
		stat = rewrite(pv, 89, 0, CurEnv);
		syslog(LOG_DEBUG, "--- ruleset 89 returns stat %d, pv: ---",
			stat);
		for (pvp = pv; *pvp != NULL; pvp++)
			syslog(LOG_DEBUG, "%s", *pvp);
	}
E 383
	syslog(LOG_DEBUG, "--- end of state dump ---");
#endif
I 394
}


void
sigusr1()
{
	dumpstate("user signal");
I 415
}


void
sighup()
{
#ifdef LOG
	if (LogLevel > 3)
		syslog(LOG_INFO, "restarting %s on signal", SaveArgv[0]);
#endif
I 482
	releasesignal(SIGHUP);
E 482
D 442
	execv(SaveArgv[0], SaveArgv);
E 442
I 442
	execv(SaveArgv[0], (ARGV_T) SaveArgv);
E 442
#ifdef LOG
	if (LogLevel > 0)
		syslog(LOG_ALERT, "could not exec %s: %m", SaveArgv[0]);
#endif
	exit(EX_OSFILE);
I 445
}
/*
**  TESTMODELINE -- process a test mode input line
**
**	Parameters:
**		line -- the input line.
**		e -- the current environment.
*/

I 466
void
E 466
testmodeline(line, e)
	char *line;
	ENVELOPE *e;
{
	register char *p;
	char *q;
	auto char *delimptr;
I 453
	int mid;
	ADDRESS a;
I 480
	static int tryflags = RF_COPYNONE;
E 480
E 453
	extern bool invalidaddr();
	extern char *crackaddr();

	switch (line[0])
	{
	  case '#':
		return;

D 453
	  case '?':		/* try crackaddr */
		q = crackaddr(&line[1]);
		xputs(q);
		printf("\n");
		return;

E 453
	  case '.':		/* config-style settings */
		switch (line[1])
		{
		  case 'D':
D 453
			define(line[2], newstr(&line[3]), e);
E 453
I 453
D 463
			p = strchr(line, '\n');
			if (p != NULL)
				*p = '\0';
E 463
			mid = macid(&line[2], &delimptr);
			if (mid != '\0')
				define(mid, newstr(delimptr), e);
E 453
			break;

		  case 'C':
D 488
			setclass(line[2], &line[3]);
E 488
I 488
			mid = macid(&line[2], &delimptr);
			if (mid != '\0')
				setclass(mid, &line[3]);
E 488
			break;

		  case 'S':		/* dump rule set */
			{
				int rs;
				struct rewrite *rw;
D 466
				char *cp;
E 466
				STAB *s;

D 463
				if ((cp = strchr(line, '\n')) != NULL)
					*cp = '\0';
				if (cp == line+2)
E 463
I 463
				if (line[2] == '\0')
E 463
					return;
D 463
				s = stab(line+2, ST_RULESET, ST_FIND);
E 463
I 463
				s = stab(&line[2], ST_RULESET, ST_FIND);
E 463
				if (s == NULL)
				{
					if (!isdigit(line[2]))
						return;
					rs = atoi(line+2);
				}
				else
					rs = s->s_ruleset;
				if (rs < 0 || rs > MAXRWSETS)
					return;
				if ((rw = RewriteRules[rs]) == NULL)
					return;
				do
				{
					char **s;
					putchar('R');
					s = rw->r_lhs;
					while (*s != NULL)
					{
						xputs(*s++);
						putchar(' ');
					}
					putchar('\t');
					putchar('\t');
					s = rw->r_rhs;
					while (*s != NULL)
					{
						xputs(*s++);
						putchar(' ');
					}
					putchar('\n');
				} while (rw = rw->r_next);
			}
			break;

		  default:
			printf("Unknown config command %s", line);
			break;
		}
		return;

	  case '-':		/* set command-line-like opts */
		switch (line[1])
		{
		  case 'd':
D 463
			if (line[2] == '\n')
				tTflag("");
			else
				tTflag(&line[2]);
E 463
I 463
			tTflag(&line[2]);
E 463
			break;

		  default:
			printf("Unknown \"-\" command %s", line);
			break;
		}
		return;

I 453
	  case '$':
		mid = macid(&line[1], NULL);
		if (mid == '\0')
			return;
		p = macvalue(mid, e);
		if (p == NULL)
			printf("Undefined\n");
		else
		{
			xputs(p);
			printf("\n");
		}
		return;

E 453
	  case '/':		/* miscellaneous commands */
D 463
		p = strchr(line, '\n');
		if (p != NULL)
		{
			while (p >= line && isascii(*p) && isspace(*p))
				*p-- = '\0';
		}
E 463
I 463
		p = &line[strlen(line)];
		while (--p >= line && isascii(*p) && isspace(*p))
			*p = '\0';
E 463
		p = strpbrk(line, " \t");
		if (p != NULL)
		{
			while (isascii(*p) && isspace(*p))
				*p++ = '\0';
		}
		else
			p = "";
		if (strcasecmp(&line[1], "mx") == 0)
		{
I 446
#if NAMED_BIND
E 446
			/* look up MX records */
			int nmx;
			int i;
			auto int rcode;
			char *mxhosts[MAXMXHOSTS + 1];

			nmx = getmxrr(p, mxhosts, FALSE, &rcode);
D 461
			printf("%d MX records:\n", nmx);
E 461
I 461
			printf("getmxrr(%s) returns %d value(s):\n", p, nmx);
E 461
			for (i = 0; i < nmx; i++)
				printf("\t%s\n", mxhosts[i]);
I 446
#else
			printf("No MX code compiled in\n");
#endif
I 453
		}
		else if (strcasecmp(&line[1], "try") == 0)
		{
			q = crackaddr(p);
			printf("Cracked address = ");
			xputs(q);
D 480
			printf("\n");
			if (parseaddr(p, &a, RF_COPYNONE, '\0', NULL, e) == NULL)
E 480
I 480
			printf("\nParsing %s %s address\n",
				bitset(RF_HEADERADDR, tryflags) ? "header" : "envelope",
				bitset(RF_SENDERADDR, tryflags) ? "sender" : "recipient");
			if (parseaddr(p, &a, tryflags, '\0', NULL, e) == NULL)
E 480
				printf("Cannot parse\n");
			else if (a.q_host != NULL && a.q_host[0] != '\0')
				printf("mailer %s, host %s, user %s\n",
					a.q_mailer->m_name, a.q_host, a.q_user);
			else
				printf("mailer %s, user %s\n",
					a.q_mailer->m_name, a.q_user);
I 480
		}
		else if (strcasecmp(&line[1], "tryflags") == 0)
		{
D 484
			while (*p != '\n')
E 484
I 484
			for (; *p != '\0'; p++)
E 484
			{
				switch (*p)
				{
				  case 'H':
				  case 'h':
					tryflags |= RF_HEADERADDR;
					break;

				  case 'E':
				  case 'e':
					tryflags &= ~RF_HEADERADDR;
					break;

				  case 'S':
				  case 's':
					tryflags |= RF_SENDERADDR;
					break;

				  case 'R':
				  case 'r':
					tryflags &= ~RF_SENDERADDR;
					break;
				}
			}
E 480
E 453
E 446
		}
		else
		{
			printf("Unknown test command %s\n", line);
		}
		return;
	}

	for (p = line; isascii(*p) && isspace(*p); p++)
		continue;
	q = p;
	while (*p != '\0' && !(isascii(*p) && isspace(*p)))
		p++;
	if (*p == '\0')
	{
		printf("No address!\n");
		return;
	}
	*p = '\0';
	if (invalidaddr(p + 1, NULL))
		return;
	do
	{
		register char **pvp;
		char pvpbuf[PSBUFSIZE];

		pvp = prescan(++p, ',', pvpbuf, sizeof pvpbuf,
			      &delimptr, NULL);
		if (pvp == NULL)
			continue;
		p = q;
		while (*p != '\0')
		{
			int stat;
I 485
			int rs = strtorwset(p, NULL, ST_FIND);
E 485

D 485
			stat = rewrite(pvp, atoi(p), 0, e);
E 485
I 485
			if (rs < 0)
				break;
			stat = rewrite(pvp, rs, 0, e);
E 485
			if (stat != EX_OK)
D 485
				printf("== Ruleset %s status %d\n",
					p, stat);
E 485
I 485
				printf("== Ruleset %s (%d) status %d\n",
					p, rs, stat);
E 485
			while (*p != '\0' && *p++ != ',')
				continue;
		}
	} while (*(p = delimptr) != '\0');
E 445
E 415
E 394
E 379
E 267
E 159
E 153
E 118
E 97
E 95
E 89
E 83
E 66
E 62
}
E 1
