h09460
s 00003/00000/00753
d D 8.80 95/06/10 18:17:31 eric 166 165
c add DontExpandCnames option -- IETF seems to be moving in this direction
e
s 00003/00000/00750
d D 8.79 95/06/10 14:53:56 eric 165 164
c handle news.group.usenet@local.host properly
e
s 00001/00001/00749
d D 8.78 95/05/30 15:02:20 eric 164 163
c one more "include" that needed to be quoted
e
s 00001/00001/00749
d D 8.77 95/05/29 10:25:31 eric 163 162
c StatusFile option should always be defined
e
s 00003/00000/00747
d D 8.76 95/05/27 17:43:51 eric 162 160
c add confMAX_QUEUE_RUN_SIZE
e
s 00003/00000/00747
d R 8.76 95/05/27 17:41:12 eric 161 160
c add confMAXQUEUERUNSIZE
e
s 00001/00001/00746
d D 8.75 95/05/26 06:38:30 eric 160 159
c include is an M4 keyword and has to be quoted
e
s 00007/00001/00740
d D 8.74 95/05/23 12:13:01 eric 159 158
c integrate mail11 support from Barb Dijker
e
s 00017/00003/00724
d D 8.73 95/05/23 10:53:41 eric 158 157
c implement DECNET_RELAY
e
s 00004/00009/00723
d D 8.72 95/05/18 08:23:39 eric 157 156
c eliminate dotted users in favor of plussed users
e
s 00002/00001/00730
d D 8.71 95/05/04 08:46:10 eric 156 155
c fix minor problems in list:; code
e
s 00005/00005/00726
d D 8.70 95/04/22 11:59:13 eric 155 154
c use DSN-style error codes instead of sysexit codes for $#error mailer
e
s 00001/00001/00730
d D 8.69 95/04/21 10:11:45 eric 154 153
c copyright update
e
s 00004/00000/00727
d D 8.68 95/04/21 08:42:31 eric 153 152
c insist on an OSTYPE macro (4.3 defaults don't cut it any more)
e
s 00003/00000/00724
d D 8.67 95/04/19 10:40:17 eric 152 151
c add ColonOkInAddr (confCOLON_OK_IN_ADDR) option
e
s 00000/00003/00724
d D 8.66 95/04/10 11:04:25 eric 151 150
c eliminate BrokenSmtpPeers and two line SMTP greeting messages
e
s 00011/00003/00716
d D 8.65 95/04/10 07:53:45 eric 150 149
c strip off group:; syntax (needed to match new code behaviour)
e
s 00003/00003/00716
d D 8.64 95/03/31 15:07:21 eric 149 148
c fix LOCAL_RELAY and MAIL_HUB so they don't conflict
e
s 00147/00105/00572
d D 8.63 95/03/30 11:00:57 eric 148 147
c clean up option setting and move it to 8.7 long option name syntax
e
s 00001/00001/00676
d D 8.62 95/01/24 07:36:00 eric 147 146
c change SortQueueByHost option to QueueSortOrder
e
s 00003/00005/00674
d D 8.61 95/01/09 12:40:05 eric 146 145
c more fixes in user+mailbox code
e
s 00007/00005/00672
d D 8.60 95/01/07 15:23:02 eric 145 144
c fix plusses in alias names
e
s 00001/00001/00676
d D 8.59 94/11/30 06:54:21 eric 144 143
c fix typo
e
s 00006/00002/00671
d D 8.58 94/11/13 16:46:37 eric 143 142
c accept user+detail
e
s 00021/00007/00652
d D 8.57 94/11/13 15:44:56 eric 142 141
c add LUSER_RELAY and invert sense of FEATURE(notsticky)
e
s 00001/00001/00658
d D 8.56 94/10/16 11:52:55 eric 141 140
c add confRECEIVED_HEADER to set the format of the Received: line
e
s 00003/00000/00656
d D 8.55 94/10/15 08:32:07 eric 140 139
c add confDONT_PRUNE_ROUTES to set option R
e
s 00006/00000/00650
d D 8.54 94/08/17 08:44:43 eric 139 138
c add confSORT_QUEUE_BY_HOST and confBROKEN_SMTP_PEERS
e
s 00002/00002/00648
d D 8.53 94/08/17 08:39:34 eric 138 137
c change to V6 config
e
s 00003/00000/00647
d D 8.52 94/07/23 10:49:18 eric 137 136
c MIME support
e
s 00001/00000/00646
d D 8.51 94/07/21 16:59:23 eric 136 135
c assume that anything in $=D is also notsticky
e
s 00011/00003/00635
d D 8.50 94/07/16 10:21:10 eric 135 134
c add dotted users
e
s 00038/00064/00600
d D 8.49 94/07/02 08:16:36 eric 134 133
c delete OLD_SENDMAIL support
e
s 00002/00002/00662
d D 8.48 94/06/25 10:21:58 eric 133 132
c extend domaintable to be generalized domain mapping
e
s 00001/00000/00663
d D 8.47 94/05/13 13:25:05 eric 132 131
c catch "." as a host name
e
s 00002/00002/00661
d D 8.46 94/05/10 07:31:05 eric 131 130
c fix parsing of null address so MAILER-DAEMON mapping works; fix
c detection of colon in host name
e
s 00001/00006/00662
d D 8.45 94/03/04 09:10:33 eric 130 129
c don't try to turn dotted IP addrs into names
e
s 00001/00000/00667
d D 8.44 94/02/21 17:32:50 eric 129 128
c catch colon in host name -- this can confuse later rules
e
s 00000/00002/00667
d D 8.43 94/02/16 08:44:09 eric 128 127
c move bitdomain and uudomain maps up in ruleset 3
e
s 00001/00001/00668
d D 8.42 94/02/15 08:01:38 eric 127 126
c fix botch in mailertable if you don't get a match
e
s 00001/00001/00668
d D 8.41 94/02/14 17:36:57 eric 126 125
c pass last component of domain name as %2 to mailertalble lookups
e
s 00012/00010/00657
d D 8.40 94/02/14 17:18:28 eric 125 124
c check for local addresses before mailertable; allow "." in mailertable
c to match anything
e
s 00002/00002/00665
d D 8.39 94/02/14 08:31:55 eric 124 123
c default $M to null instead of $j so we can behave differently
e
s 00004/00004/00663
d D 8.38 94/02/13 12:41:35 eric 123 122
x 121
c much more elegant fix to mailertable problem
e
s 00001/00001/00672
d D 8.37 94/02/10 11:49:26 eric 122 121
c don't include "root" in $=L by default
e
s 00019/00013/00654
d D 8.36 94/02/10 10:15:24 eric 121 119
c fix some bugs with mailertables
e
s 00009/00014/00653
d D 8.35.1.1 94/02/10 08:40:43 eric 120 119
c try to fix interaction of MAIL_HUB and LOCAL_RELAY
e
s 00001/00001/00666
d D 8.35 94/02/09 07:29:08 eric 119 118
c be more liberal in catching list:; syntax in S0
e
s 00001/00001/00666
d D 8.34 94/02/06 13:11:02 eric 118 117
c clean up Received: line to handle possibility of $s unset and $_ set
e
s 00005/00002/00662
d D 8.33 94/01/26 17:24:00 eric 117 116
c when mail is auto-sent to $R or $H, qualify it with the receiver, not
c with the sender
e
s 00001/00001/00663
d D 8.32 94/01/23 19:48:06 eric 116 115
c fix news.group.USENET mappings
e
s 00004/00004/00660
d D 8.31 94/01/22 09:05:32 eric 115 114
c allow comma-separated ALIAS_FILE defn; fix problem that caused
c anything in $=w to map to $j
e
s 00001/00001/00663
d D 8.30 94/01/12 06:16:47 eric 114 113
c fix comment on "c" option
e
s 00001/00002/00663
d D 8.29 94/01/07 09:09:26 eric 113 112
c use full domain name in UUCP mailer for consistency with mailertable
e
s 00001/00001/00664
d D 8.28 93/12/21 14:05:29 eric 112 111
c fix [domain literals] when allmasquerade set -- was getting an extra
c masquerade name
e
s 00000/00009/00665
d D 8.27 93/12/20 10:49:54 eric 111 110
c delete CSNET domain support
e
s 00003/00000/00671
d D 8.26 93/12/15 06:36:03 eric 110 109
c add MAILER(pop)
e
s 00004/00005/00667
d D 8.25 93/12/10 15:35:36 eric 109 108
c ensure that $=w names are always considered canonical
e
s 00001/00000/00671
d D 8.24 93/12/10 06:20:07 eric 108 107
c catch @host syntax (i.e., null user name)
e
s 00025/00021/00646
d D 8.23 93/11/30 09:00:51 eric 107 106
c add dot on pseudo-domains for consistency
e
s 00003/00000/00664
d D 8.22 93/11/29 19:02:14 eric 106 105
c cope with colons in address part
e
s 00001/00001/00663
d D 8.21 93/11/23 10:01:29 eric 105 104
c fix typo on UUCP router line
e
s 00004/00002/00660
d D 8.20 93/10/31 11:35:55 eric 104 103
c handle wierd case of <list:;> syntax
e
s 00004/00004/00658
d D 8.19 93/10/15 08:35:21 eric 103 102
c fix mailer:host syntax for UUCP relays
e
s 00003/00000/00659
d D 8.18 93/10/02 06:57:15 eric 102 101
c catch self-literal (e.g., [1.2.3.4]) even if reverse mapping is broken
e
s 00001/00001/00658
d D 8.17 93/09/19 19:58:33 eric 101 100
c avoid infinite loops in !foo format
e
s 00001/00001/00658
d D 8.16 93/08/24 13:48:12 eric 100 99
c fix USE_TZ spec for confTIME_ZONE
e
s 00018/00020/00641
d D 8.15 93/08/21 16:18:26 eric 99 98
c null client support
e
s 00009/00006/00652
d D 8.14 93/08/15 08:44:05 eric 98 97
c V5 config level; Dj optional on confDOMAIN_NAME
e
s 00001/00001/00657
d D 8.13 93/08/14 11:32:47 eric 97 96
c fix M4 botch
e
s 00001/00001/00657
d D 8.12 93/08/08 10:54:10 eric 96 95
c take right-most <> instead of left-most in S3
e
s 00001/00001/00657
d D 8.11 93/08/07 14:20:26 eric 95 94
c log $u on Received: line
e
s 00064/00063/00594
d D 8.10 93/07/26 09:19:14 eric 94 93
c cleanup to reduce the number of quotes needed around defined constants
e
s 00033/00044/00624
d D 8.9 93/07/23 09:44:15 eric 93 92
c default confSMTP_MAILER to "smtp"; make mailer:host processing
c generic (and fix a problem that caused it to be confused with
c route-addr syntax)
e
s 00015/00013/00653
d D 8.8 93/07/22 16:00:55 eric 92 91
c add confLOCAL_MAILER
e
s 00011/00009/00655
d D 8.7 93/07/21 12:12:16 eric 91 90
c add confSMTP_MAILER to select default mailer for SMTP delivery
e
s 00004/00004/00660
d D 8.6 93/07/21 08:59:34 eric 90 89
c move up LOCAL_RULE_0 handling; fix MAILER(usenet)
e
s 00005/00007/00659
d D 8.5 93/07/20 08:22:32 eric 89 88
c avoid "fall off the end" problems if neither SMART_HOST nor MAILER(smtp)
c are defined
e
s 00005/00007/00661
d D 8.4 93/07/18 11:57:29 eric 88 87
c fix some M4 glitches
e
s 00061/00023/00607
d D 8.3 93/07/18 11:14:56 eric 87 86
c add option `w'; break LOCAL_RULE_0 into S98, and process [a.b.c.d]
c syntax through it; accept mailer:hostname on all of the relays
e
s 00020/00008/00610
d D 8.2 93/07/11 08:16:38 eric 86 85
c many changes including: SMART_HOST overrides SMTP mailer (use
c LOCAL_NET_CONFIG instead); add FEATURE(domaintable)
e
s 00002/00002/00616
d D 8.1 93/06/27 18:32:11 bostic 85 84
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00616
d D 6.48 93/06/24 18:16:24 eric 84 82
c concat => CONCAT
e
s 00002/00002/00616
d R 8.1 93/06/08 11:16:15 bostic 83 82
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00616
d D 6.47 93/06/08 11:16:03 eric 82 80
c fix yet another botch in mailertable code -- I hope THIS one is right
e
s 00002/00002/00616
d R 8.1 93/06/07 10:11:05 bostic 81 80
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00616
d D 6.46 93/06/06 21:24:48 eric 80 79
c fix yet more mailertable bugs (sigh)
e
s 00005/00003/00613
d D 6.45 93/06/05 09:28:12 eric 79 78
c if FEATURE(no_canonify), make certain $=w names appear canonica
e
s 00007/00006/00609
d D 6.44 93/06/05 09:22:25 eric 78 77
c back out automatic dot addition on relay names
e
s 00008/00005/00607
d D 6.43 93/06/04 08:07:50 eric 77 76
c add option 'l'; fix mailertable lookup
e
s 00034/00030/00578
d D 6.42 93/06/01 12:04:44 eric 76 75
c put $r into Received: line; ruleset 6 => 96, 7 => 97; fix ruleset
c 90 typo; recognize $=w as local instead of $j (major fix)
e
s 00019/00002/00589
d D 6.41 93/05/28 07:19:40 eric 75 74
c have mailertable look for partial domains as well as full domains
e
s 00004/00005/00587
d D 6.40 93/05/24 09:20:59 eric 74 73
c add FEATURE(always_add_domain); avoid rewriting $=w into $j
c (some hosts have multiple "canonical" names)
e
s 00011/00005/00581
d D 6.39 93/05/21 19:49:02 eric 73 72
c avoid extra qualification of top level pseudo-domains and gateways
e
s 00006/00002/00580
d D 6.38 93/05/11 08:33:13 eric 72 71
c Option 8 => option 7; add Oj (confMIME_FORMAT_ERRORS)
e
s 00001/00001/00581
d D 6.37 93/05/01 17:57:42 eric 71 70
x 70
c undo botch with not stripping trailing dots off addresses
e
s 00014/00014/00568
d D 6.36 93/05/01 08:25:51 eric 70 69
c don't need angle brackets in mailer definitions (just sent through
c S4 anyway); fix UUCP route-addr
e
s 00006/00004/00576
d D 6.35 93/04/14 13:13:01 eric 69 68
c FEATURE(nocanonify) to turn off calls to $[ ... $]; fix some other
c uucp info not deleted by FEATURE(nouucp)
e
s 00000/00007/00580
d D 6.34 93/04/12 14:34:11 eric 68 67
c back out hack to hide unqualified domains behind %-hack -- it breaks
c local aliases and .forward files
e
s 00002/00001/00585
d D 6.33 93/04/10 10:50:44 eric 67 66
c rearrange diversion 6 for FEATURE(bitdomain)
e
s 00007/00000/00579
d D 6.32 93/04/10 10:22:26 eric 66 65
c %-hack single token hostnames behind $s if $r is specified
e
s 00001/00001/00578
d D 6.31 93/04/04 16:05:24 eric 65 64
c log $_ (authenticated sender info) in Received: line
e
s 00010/00000/00569
d D 6.30 93/03/29 17:26:23 eric 64 63
c add O and V options
e
s 00001/00001/00568
d D 6.29 93/03/29 13:47:48 eric 63 62
c typo in the mailertable rule
e
s 00006/00006/00563
d D 6.28 93/03/25 10:56:43 eric 62 61
c fix up quote stripping code
e
s 00012/00003/00557
d D 6.27 93/03/25 10:36:44 eric 61 60
c use dequote map
e
s 00011/00000/00549
d D 6.26 93/03/23 16:14:43 eric 60 59
c hooks for FEATURE(mailertable)
e
s 00003/00003/00546
d D 6.25 93/03/23 07:47:16 eric 59 58
c use "relay" mailer for $H (MAIL_HUB) and $R (LOCAL_RELAY) mail
e
s 00001/00001/00548
d D 6.24 93/03/18 16:01:33 eric 58 57
c clean up confUSERDB_SPEC
e
s 00001/00001/00548
d D 6.23 93/03/18 11:49:16 eric 57 56
c fix typo in list syntax (;: => :;)
e
s 00001/00001/00548
d D 6.22 93/03/15 13:05:24 eric 56 55
c delete $<
e
s 00001/00000/00548
d D 6.21 93/03/15 13:04:26 eric 55 54
c add LOCAL_RULE_1 and LOCAL_RULE_2
e
s 00001/00001/00547
d D 6.20 93/03/08 18:13:21 eric 54 53
c fix infinite loop in <> case
e
s 00005/00002/00543
d D 6.19 93/03/06 09:59:23 eric 53 52
c FEATURE(notsticky) lets UDB get at even specific addresses
e
s 00005/00004/00540
d D 6.18 93/03/05 14:47:00 eric 52 51
c avoid having C flag qualify list:; and error <> syntax
e
s 00001/00000/00543
d D 6.17 93/03/05 07:34:53 eric 51 50
c catch user@ (no host) case -- treat as user@local
e
s 00001/00001/00542
d D 6.16 93/03/03 10:06:58 eric 50 49
c allow redefinition of sendmail.cw path
e
s 00010/00000/00533
d D 6.15 93/03/02 13:48:07 eric 49 48
c extensions for Sam Leffler's FlexFAX software
e
s 00005/00003/00528
d D 6.14 93/03/01 13:42:24 eric 48 47
c change error address convention to avoid conflict with C flag
e
s 00007/00005/00524
d D 6.13 93/02/27 08:25:25 eric 47 46
c add FEATURE(nouucp) support
e
s 00000/00001/00529
d D 6.12 93/02/25 12:46:49 eric 46 45
c fix botch in "r" option
e
s 00001/00001/00529
d D 6.11 93/02/24 09:31:04 eric 45 44
c fix syntax error
e
s 00003/00000/00527
d D 6.10 93/02/24 09:13:20 eric 44 43
c catch null input to S3 as equivalent to <>
e
s 00002/00005/00525
d D 6.9 93/02/23 10:41:48 eric 43 42
c use clever algorithm for de-nesting angle brackets
e
s 00007/00004/00523
d D 6.8 93/02/21 12:41:01 eric 42 41
c adjust timeout values; changes to handle <> properly as an error address indicator
e
s 00001/00001/00526
d D 6.7 93/02/20 15:21:01 eric 41 40
c syntax error in usenet hooks
e
s 00009/00000/00518
d D 6.6 93/02/20 13:48:46 eric 40 39
c add b (minimum free blocks) and p (privacy) options & hook for
c usenet mailer
e
s 00030/00009/00488
d D 6.5 93/02/19 16:30:10 eric 39 38
c add SMART_HOST support and ability to route to local net hosts
c and send remote traffic to UUCP (or other long haul transport agent)
e
s 00000/00003/00497
d D 6.4 93/02/15 12:01:23 eric 38 37
c fix botches with confNO_WILDCARD_MX and confMATCH_GECOS
e
s 00208/00005/00292
d D 6.3 93/02/12 12:10:50 eric 37 36
c make everything configurable on M4 macros
e
s 00015/00005/00282
d D 6.2 93/01/13 16:38:50 eric 36 35
c allow definition of hub machine that gets *all* local traffic
e
s 00000/00000/00287
d D 6.1 92/12/21 16:08:16 eric 35 34
c Release 6
e
s 00004/00016/00283
d D 2.34 92/12/20 13:21:55 eric 34 33
c cleanup for new features and release engineering
e
s 00001/00000/00298
d D 2.33 92/12/07 16:40:55 eric 33 32
c handle multiple <> <> in S3
e
s 00001/00001/00297
d D 2.32 92/11/14 07:59:00 eric 32 31
c hack for BSD version of m4
e
s 00001/00001/00297
d D 2.31 92/11/14 00:42:48 eric 31 30
c change location of "local config" so it can override boilerplate
e
s 00001/00001/00297
d D 2.30 92/11/14 00:22:49 eric 30 29
c fix minor nit
e
s 00001/00002/00297
d D 2.29 92/11/13 23:00:38 eric 29 28
c quote versionid to avoid # problems
e
s 00001/00000/00298
d D 2.28 92/11/13 21:57:45 eric 28 27
c make it so it will work on systems without m4_wrap
e
s 00002/00003/00296
d D 2.27 92/11/13 21:50:28 eric 27 26
c make more portable to other versions of m4
e
s 00041/00036/00258
d D 2.26 92/07/20 08:00:24 eric 26 25
c readability changes
e
s 00001/00001/00293
d D 2.25 92/03/09 12:57:33 eric 25 24
c ruleset 5 should include @ $R on user portion of address
e
s 00004/00004/00290
d D 2.24 92/02/24 16:15:17 eric 24 23
c new configuration version level control line
e
s 00001/00001/00293
d D 2.23 92/01/05 09:23:40 eric 23 22
c spell out options to make local tuning easier
e
s 00010/00007/00284
d D 2.22 91/12/20 18:59:31 eric 22 21
c when forwarding UUCP mail, make it a route-addr to the destination
c to keep it from bouncing back to us
e
s 00009/00009/00282
d D 2.21 91/12/20 12:01:21 eric 21 20
c remember to pay attention to =L class in old sendmail mode
e
s 00001/00000/00290
d D 2.20 91/12/17 16:27:55 eric 20 19
c fix <route-addr> handling in ruleset 4
e
s 00001/00001/00289
d D 2.19 91/12/17 15:59:31 eric 19 18
c oops..... m4 problem
e
s 00014/00015/00276
d D 2.18 91/12/17 15:54:32 eric 18 17
c make NEWSENDMAIL the default
e
s 00013/00011/00278
d D 2.17 91/12/12 10:49:21 eric 17 16
c modifications for CS subdomain server
e
s 00020/00026/00269
d D 2.16 91/12/12 08:24:51 eric 16 15
c checkpoint of hacking for mail.cs.berkeley.edu
e
s 00003/00003/00292
d D 2.15 91/11/22 15:02:04 eric 15 14
c USERDB_FILE => USERDB_SPEC
e
s 00004/00002/00291
d D 2.14 91/10/05 12:53:59 eric 14 13
c work better on old sendmails when relaying local mail
e
s 00064/00032/00229
d D 2.13 91/10/05 12:40:18 eric 13 12
c allowances for new sendmail that can handle reprocessing after
c aliasing (for relay hosts)
e
s 00003/00000/00258
d D 2.12 91/10/03 11:29:04 eric 12 11
c don't add $R to file names, :include:s, or programs
e
s 00007/00007/00251
d D 2.11 91/10/03 01:27:28 eric 11 10
c use $j instead of $w so it can be requalified on power ultrix
e
s 00006/00003/00252
d D 2.10 91/10/03 00:57:17 eric 10 9
c more cleaning up...
e
s 00003/00003/00252
d D 2.9 91/10/03 00:38:40 eric 9 8
c adjust UUCP naming a bit
e
s 00004/00000/00251
d D 2.8 91/10/02 23:53:58 eric 8 7
c allow definitions of names that override $R
e
s 00005/00002/00246
d D 2.7 91/10/02 23:21:52 eric 7 6
c be more conservative on uucp => internet name conversion
e
s 00014/00003/00234
d D 2.6 91/10/02 22:01:03 eric 6 5
c pass host!user through the name server to see if it might be local
e
s 00000/00004/00237
d D 2.5 91/10/02 21:42:54 eric 5 4
c don't tack on local domain -- that really doesn't work
e
s 00026/00019/00215
d D 2.4 91/10/02 21:20:17 eric 4 3
c enhancements for ucbvax
e
s 00006/00005/00228
d D 2.3 91/10/02 18:53:03 eric 3 2
c clean up botched concatenation of m4 commands
e
s 00000/00001/00233
d D 2.2 91/10/02 18:38:51 eric 2 1
c make it work on 4.4bsd m4
e
s 00234/00000/00000
d D 2.1 91/10/02 14:48:10 eric 1 0
c date and time created 91/10/02 14:48:10 by eric
e
u
U
t
T
I 1
divert(-1)
#
D 154
# Copyright (c) 1983 Eric P. Allman
E 154
I 154
# Copyright (c) 1983, 1995 Eric P. Allman
E 154
D 85
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 85
I 85
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 85
#
# %sccs.include.redist.sh%
#
divert(0)

D 29
VERSIONID(%W% (Berkeley) %G%)
I 28
define(`DOIT', `dnl')dnl
E 29
I 29
VERSIONID(`%W% (Berkeley) %G%')
E 29
E 28

I 13
MAILER(local)dnl
E 13

I 24
D 76
ifdef(`_OLD_SENDMAIL_', `dnl',
E 76
I 76
D 134
ifdef(`_OLD_SENDMAIL_',
D 93
`define(`_SET_96_', 6)dnl
E 93
I 93
`define(`_SET_95_', 5)dnl
define(`_SET_96_', 6)dnl
E 93
D 87
define(`_SET_97_', 7)dnl',
E 87
I 87
define(`_SET_97_', 7)dnl
D 98
define(`_SET_98_', 8)dnl',
E 87
E 76
D 42
`# level 3 config file format
V3')
E 42
I 42
`# level 4 config file format
D 76
V4')
E 76
I 76
V4
E 98
I 98
define(`_SET_98_', 8)dnl
define(`confDOMAIN_NAME',
	`ifdef(`NEED_DOMAIN', `$w.$d', `$w')')dnl',
`# level 5 config file format
E 134
I 134
D 138
# level 5 config file format
E 134
V5
E 138
I 138
# level 6 config file format
D 148
V6
E 138
E 98
I 93
D 134
define(`_SET_95_', 95)dnl
E 93
define(`_SET_96_', 96)dnl
D 87
define(`_SET_97_', 97)dnl')
E 87
I 87
define(`_SET_97_', 97)dnl
define(`_SET_98_', 98)dnl')
E 134
I 91
D 93
ifdef(`confSMTP_MAILER',, `define(`confSMTP_MAILER', `esmtp')')dnl
E 93
I 93
ifdef(`confSMTP_MAILER',, `define(`confSMTP_MAILER', `smtp')')dnl
E 93
D 92
define(`_SMTP_', `confSMTP_MAILER')dnl	for readability only
E 92
I 92
ifdef(`confLOCAL_MAILER',, `define(`confLOCAL_MAILER', `local')')dnl
E 148
I 148
V6/Berkeley
divert(-1)

I 153
# do some sanity checking
ifdef(`__OSTYPE__',,
	`errprint(`*** ERROR: No system type defined (use OSTYPE macro)')')

E 153
# pick our default mailers
ifdef(`confSMTP_MAILER',, `define(`confSMTP_MAILER', `smtp')')
ifdef(`confLOCAL_MAILER',, `define(`confLOCAL_MAILER', `local')')
E 148
I 93
ifdef(`confRELAY_MAILER',,
	`define(`confRELAY_MAILER',
		`ifdef(`_MAILER_smtp_', `relay',
D 148
			`ifdef(`_MAILER_uucp', `suucp', `unknown')')')')dnl
E 148
I 148
			`ifdef(`_MAILER_uucp', `suucp', `unknown')')')')
E 148
E 93
define(`_SMTP_', `confSMTP_MAILER')dnl		for readability only
define(`_LOCAL_', `confLOCAL_MAILER')dnl	for readability only
I 93
define(`_RELAY_', `confRELAY_MAILER')dnl	for readability only
E 93
E 92
E 91
E 87
E 76
E 42

I 148
# back compatibility with old config files
ifdef(`confDEF_GROUP_ID',
	`errprint(`*** confDEF_GROUP_ID is obsolete.')
	 errprint(`    Use confDEF_USER_ID with a colon in the value instead.')')
ifdef(`confREAD_TIMEOUT',
	`errprint(`*** confREAD_TIMEOUT is obsolete.')
	 errprint(`    Use individual confTO_<timeout> parameters instead.')')
ifdef(`confMESSAGE_TIMEOUT',
	`define(`_ARG_', index(confMESSAGE_TIMEOUT, /))
	 ifelse(_ARG_, -1,
		`define(`confTO_QUEUERETURN', confMESSAGE_TIMEOUT)',
		`define(`confTO_QUEUERETURN',
			substr(confMESSAGE_TIMEOUT, 0, _ARG_))
		 define(`confTO_QUEUEWARN',
			substr(confMESSAGE_TIMEOUT, eval(_ARG_+1)))')')
ifdef(`confMIN_FREE_BLOCKS', `ifelse(index(confMIN_FREE_BLOCKS, /), -1,,
	`errprint(`*** compound confMIN_FREE_BLOCKS is obsolete.')
	 errprint(`    Use confMAX_MESSAGE_SIZE for the second part of the value.')')')

# clean option definitions below....
define(`_OPTION', `ifdef(`$2', `O $1=$2', `#O $1`'ifelse($3, `',, `=$3')')')dnl

divert(0)dnl

E 148
E 24
D 2

E 2
##################
#   local info   #
##################

I 73
D 99
CP.

E 99
E 73
I 17
Cwlocalhost
E 17
D 16
ifdef(`_USE_CW_FILE_',
E 16
I 16
ifdef(`USE_CW_FILE',
E 16
D 17
`# file containing internet aliases in our primary domain
E 17
I 17
`# file containing names of hosts for which we receive email
E 17
D 50
Fw/etc/sendmail.cw', `dnl')
E 50
I 50
D 94
CONCAT(`Fw', confCW_FILE)', `dnl')
E 94
I 94
Fw`'confCW_FILE',
	`dnl')
I 99
D 148
ifdef(`confDOMAIN_NAME', `
E 148
I 148

E 148
# my official domain name
D 148
Dj`'confDOMAIN_NAME',
	`dnl')
E 148
I 148
# ... define this only if sendmail cannot automatically determine your domain
ifdef(`confDOMAIN_NAME', `Dj`'confDOMAIN_NAME', `#Dj$w.Foo.COM')
E 148
E 99
E 94
E 50

I 99
D 148
ifdef(`_NULL_CLIENT_ONLY_',
`include(../m4/nullrelay.m4)m4exit',
	`dnl')
E 148
I 148
ifdef(`_NULL_CLIENT_ONLY_', `divert(-1)')dnl
E 148

CP.

E 99
ifdef(`UUCP_RELAY',
`# UUCP relay host
D 9
CONCAT(DU, UUCP_RELAY)
E 9
I 9
D 94
CONCAT(DY, UUCP_RELAY)
E 94
I 94
DY`'UUCP_RELAY
E 94
I 73
CPUUCP
E 73
I 37

E 37
E 9
')dnl
ifdef(`BITNET_RELAY',
`#  BITNET relay host
D 94
CONCAT(DB, BITNET_RELAY)
E 94
I 94
DB`'BITNET_RELAY
E 94
I 73
CPBITNET
E 73
I 37

E 37
')dnl
I 158
ifdef(`DECNET_RELAY',
I 159
`define(`_USE_DECNET_SYNTAX_')dnl
E 159
# DECnet relay host
DC`'DECNET_RELAY
CPDECNET

')dnl
E 158
D 111
ifdef(`CSNET_RELAY',
`# CSNET relay host
D 94
CONCAT(DC, CSNET_RELAY)
E 94
I 94
DC`'CSNET_RELAY
E 94
I 73
CPCSNET
E 73
I 37

E 37
')dnl
E 111
I 49
ifdef(`FAX_RELAY',
`# FAX relay host
D 94
CONCAT(DF, FAX_RELAY)
E 94
I 94
DF`'FAX_RELAY
E 94
I 73
CPFAX
E 73

')dnl
E 49
D 39
# my official hostname ($w or $w.$D)
D 11
Dj$w
E 11
I 11
CONCAT(Dj$w, ifdef(`NEED_DOMAIN', .$D))
E 39
I 39
D 99
ifdef(`SMART_HOST',
`# "Smart" UUCP relay host
D 94
CONCAT(DS, SMART_HOST)
E 94
I 94
DS`'SMART_HOST
E 99
I 99
# "Smart" relay host (may be null)
DS`'ifdef(`SMART_HOST', SMART_HOST)
E 99
E 94
E 39
E 11

I 142
ifdef(`LUSER_RELAY',
`# place to which unknown users should be forwarded
Kuser user -m -a<>
DL`'LUSER_RELAY
', `dnl')

I 148
# operators that cannot be in local usernames (i.e., network indicators)
CO @ % ifdef(`_NO_UUCP_', `', `!')

# a class with just dot (for identifying canonical names)
C..

E 148
E 142
D 39
# who I masquerade as (can be $j)
CONCAT(DM, ifdef(`MASQUERADE_NAME', MASQUERADE_NAME, $j))

E 39
I 39
D 99
')dnl
E 99
I 60
ifdef(`MAILER_TABLE',
`# Mailer table (overriding domains)
Kmailertable MAILER_TABLE

')dnl
I 86
ifdef(`DOMAIN_TABLE',
`# Domain table (adding domains)
Kdomaintable DOMAIN_TABLE

')dnl
E 86
E 60
E 39
# who I send unqualified names to (null means deliver locally)
D 94
CONCAT(DR, ifdef(`LOCAL_RELAY', LOCAL_RELAY))
E 94
I 94
DR`'ifdef(`LOCAL_RELAY', LOCAL_RELAY)
E 94

I 36
# who gets all local email traffic ($R has precedence for unqualified names)
D 94
CONCAT(DH, ifdef(`MAIL_HUB', MAIL_HUB))
E 94
I 94
DH`'ifdef(`MAIL_HUB', MAIL_HUB)
E 94

I 39
D 98
# my official hostname ($w or $w.$D)
D 94
CONCAT(Dj$w, ifdef(`NEED_DOMAIN', .$D))
E 94
I 94
Dj$w`'ifdef(`NEED_DOMAIN', .$D)
E 94

E 98
I 98
D 99
ifdef(`confDOMAIN_NAME',
`# my official domain name
Dj`'confDOMAIN_NAME',
	`dnl')
E 99
E 98
D 124
# who I masquerade as (can be $j)
D 94
CONCAT(DM, ifdef(`MASQUERADE_NAME', MASQUERADE_NAME, $j))
E 94
I 94
DM`'ifdef(`MASQUERADE_NAME', MASQUERADE_NAME, $j)
E 124
I 124
D 148
# who I masquerade as (null for no masquerading)
DM`'ifdef(`MASQUERADE_NAME', MASQUERADE_NAME)
E 124
E 94

E 148
E 39
E 36
I 8
D 34
# names that should be delivered locally, even if we have a relay
E 34
I 34
# class L: names that should be delivered locally, even if we have a relay
# class E: names that should be exposed as from this host, even if we masquerade
E 34
D 122
CLroot
E 122
I 122
D 135
#CLroot
E 122
I 34
CEroot
E 135
I 135
D 157
# class D: dotted names, e.g., root.machinename
E 157
#CL root
CE root
E 135
E 34
undivert(5)dnl
I 135
D 157
ifdef(`__DOTTED_USER_LIST__',
	`__DOTTED_USER_LIST__',
	`#CD postmaster')
E 157
E 135
I 17
D 31
undivert(6)dnl
E 31
E 17

E 8
D 3

E 3
D 34
ifdef(`UUCP_NAME',
D 4
# uucp hostnames
E 4
I 4
`# uucp hostnames
E 4
UUCP_NAME
UUCP_ALIASES

# local UUCP connections
D 3
`include(UUCP_HOSTS_FILE)')
E 3
I 3
D 4
`include(UUCP_HOSTS_FILE)',
E 4
I 4
include(UUCP_HOSTS_FILE)',
E 4
`dnl')
E 3

E 34
D 148
# operators that cannot be in local usernames (i.e., network indicators)
D 47
CO @ % !
E 47
I 47
CO @ % ifdef(`_NO_UUCP_', `', `!')
E 47

I 13
# a class with just dot (for identifying canonical names)
C..

E 148
I 61
D 134
ifdef(`_OLD_SENDMAIL_', `dnl',
`# dequoting map
Kdequote dequote')
E 134
I 134
# dequoting map
Kdequote dequote
E 134
E 61
E 13
D 3
# location of user database file (null means no lookup)
ifdef(`USERDB_FILE', `CONCAT(`OU', USERDB_FILE)', `dnl')
E 3
I 3
D 15
ifdef(`USERDB_FILE',
`# location of user database file (null means no lookup)
D 4
CONCAT(`OU', USERDB_FILE)', `dnl')
E 4
I 4
CONCAT(`OU', USERDB_FILE)',
E 15
I 15
D 16
ifdef(`USERDB_SPEC',
`# list of locations of user database file (null means no lookup)
CONCAT(`OU', USERDB_SPEC)',
E 15
`dnl')
E 16
I 16
D 37
# list of locations of user database file (null means no lookup)
OU`'ifdef(`USERDB_SPEC', `USERDB_SPEC')
E 37
E 16
E 4
E 3

I 148
divert(0)dnl
# who I masquerade as (null for no masquerading)
DM`'ifdef(`MASQUERADE_NAME', MASQUERADE_NAME)

E 148
I 67
undivert(6)dnl

E 67
D 16
ifdef(`_NO_WILDCARD_MX_',
`# we can guarantee no wildcard MX records matching our domain
D 3
Ow', `dnl')dnl
E 3
I 3
D 4
Ow', `dnl')
E 4
I 4
Ow',
`dnl')
E 16
I 16
D 37
# set if we can guarantee no wildcard MX records matching our domain
D 23
ifdef(`_NO_WILDCARD_MX_', `', `#')Ow
E 23
I 23
Ow`'ifdef(`_NO_WILDCARD_MX_', `True', `False')
E 37
I 37
######################
#   Special macros   #
######################
E 37
E 23
E 16
E 4
E 3
D 24

I 13
D 18
ifdef(`NEWSENDMAIL',
E 18
I 18
ifdef(`_OLD_SENDMAIL_', `dnl',
E 18
`# level 2 config file format
D 18
O=2', `dnl')
E 18
I 18
O=2')
E 24
E 18

I 37
# SMTP initial login message
D 94
CONCAT(De, confSMTP_LOGIN_MSG)
E 94
I 94
De`'confSMTP_LOGIN_MSG
E 94

# UNIX initial From header format
D 94
CONCAT(Dl, confFROM_LINE)
E 94
I 94
Dl`'confFROM_LINE
E 94

# my name for error messages
D 94
CONCAT(Dn, confMAILER_NAME)
E 94
I 94
Dn`'confMAILER_NAME
E 94

# delimiter (operator) characters
D 94
CONCAT(Do, confOPERATORS)
E 94
I 94
Do`'confOPERATORS
E 94

# format of a total name
D 94
CONCAT(Dq, ifdef(`confFROM_HEADER', confFROM_HEADER,
E 94
I 94
D 134
Dq`'ifdef(`confFROM_HEADER', confFROM_HEADER,
E 94
D 97
	ifdef(`_OLD_SENDMAIL_', `$g$?x ($x)$.', `$?x$x <$g>$|$g$.')))
E 97
I 97
	ifdef(`_OLD_SENDMAIL_', `$g$?x ($x)$.', `$?x$x <$g>$|$g$.'))
E 134
I 134
D 135
Dq`'ifdef(`confFROM_HEADER', confFROM_HEADER, $g$?x ($x)$.', `$?x$x <$g>$|$g$.)
E 135
I 135
Dq`'ifdef(`confFROM_HEADER', confFROM_HEADER, `$?x$x <$g>$|$g$.')
E 135
E 134
E 97
E 37
I 16
D 17
# if new sendmail and we want to ignore UDB for fully qualified user names
# (e.g., "user@thishost" instead of "user"), set this to "@", else set to null
CONCAT(`DO', ifdef(`NEWSENDMAIL', ifdef(`ALWAYS_USE_UDB', `', `@')))

E 17
E 16
E 13
include(`../m4/version.m4')
D 34

D 4
#ifdef(`INTERNET_RELAY',
#`include(../sitedep/nicregistered.m4)')
E 4
I 4
ifdef(`INTERNET_RELAY',
`include(../sitedep/nicregistered.m4)',
`dnl')
E 34
E 4
D 37
include(`../m4/boilerplate.m4')
E 37
I 37

###############
#   Options   #
###############

D 72
# preserve 8 bits on message body on input?
CONCAT(O8, confEIGHT_BIT_INPUT)
E 72
I 72
# strip message body to 7 bits on input?
D 94
CONCAT(O7, confSEVEN_BIT_INPUT)
E 94
I 94
D 148
O7`'confSEVEN_BIT_INPUT
E 148
I 148
_OPTION(SevenBitInput, `confSEVEN_BIT_INPUT')
E 148
E 94
E 72

I 137
# 8-bit data handling
D 148
O8`'confEIGHT_BIT_HANDLING
E 148
I 148
_OPTION(EightBitMode, `confEIGHT_BIT_HANDLING', adaptive)
E 148

E 137
D 148
# wait (in minutes) for alias file rebuild
D 94
CONCAT(Oa, confALIAS_WAIT)
E 94
I 94
Oa`'confALIAS_WAIT
E 148
I 148
# wait for alias file rebuild (default units: minutes)
_OPTION(AliasWait, `confALIAS_WAIT', 5m)
E 148
E 94

# location of alias file
D 94
CONCAT(OA, ifdef(`ALIAS_FILE', ALIAS_FILE, /etc/aliases))
E 94
I 94
D 115
OA`'ifdef(`ALIAS_FILE', ALIAS_FILE, /etc/aliases)
E 115
I 115
D 148
OA`'ifdef(`ALIAS_FILE', `ALIAS_FILE', /etc/aliases)
E 148
I 148
O AliasFile=ifdef(`ALIAS_FILE', `ALIAS_FILE', /etc/aliases)
E 148
E 115
E 94

I 40
# minimum number of free blocks on filesystem
D 94
CONCAT(Ob, confMIN_FREE_BLOCKS)
E 94
I 94
D 148
Ob`'confMIN_FREE_BLOCKS
E 148
I 148
_OPTION(MinFreeBlocks, `confMIN_FREE_BLOCKS', 100)
E 148
E 94

I 148
# maximum message size
_OPTION(MaxMessageSize, `confMAX_MESSAGE_SIZE', 1000000)

E 148
E 40
# substitution for space (blank) characters
D 94
CONCAT(OB, confBLANK_SUB)
E 94
I 94
D 148
OB`'confBLANK_SUB
E 148
I 148
_OPTION(BlankSub, `confBLANK_SUB', _)
E 148
E 94

D 114
# connect to "expensive" mailers on initial submission?
E 114
I 114
# avoid connecting to "expensive" mailers on initial submission?
E 114
D 94
CONCAT(Oc, confCON_EXPENSIVE)
E 94
I 94
D 148
Oc`'confCON_EXPENSIVE
E 148
I 148
_OPTION(HoldExpensive, `confCON_EXPENSIVE')
E 148
E 94

# checkpoint queue runs after every N successful deliveries
D 94
CONCAT(OC, confCHECKPOINT_INTERVAL)
E 94
I 94
D 148
OC`'confCHECKPOINT_INTERVAL
E 148
I 148
_OPTION(CheckpointInterval, `confCHECKPOINT_INTERVAL', 10)
E 148
E 94

# default delivery mode
D 94
CONCAT(Od, confDELIVERY_MODE)
E 94
I 94
D 148
Od`'confDELIVERY_MODE
E 148
I 148
_OPTION(DeliveryMode, `confDELIVERY_MODE', background)
E 148
E 94

# automatically rebuild the alias database?
D 94
CONCAT(OD, confAUTO_REBUILD)
E 94
I 94
D 148
OD`'confAUTO_REBUILD
E 148
I 148
_OPTION(AutoRebuildAliases, `confAUTO_REBUILD')
E 148
E 94

D 94
# error message header/file */
E 94
I 94
# error message header/file
E 94
D 148
ifdef(`confERROR_MESSAGE',
D 84
	concat(OE, confERROR_MESSAGE),
E 84
I 84
D 94
	CONCAT(OE, confERROR_MESSAGE),
E 94
I 94
	OE`'confERROR_MESSAGE,
E 94
E 84
	#OE/etc/sendmail.oE)
E 148
I 148
_OPTION(ErrorHeader, `confERROR_MESSAGE', /etc/sendmail.oE)
E 148

# error mode
D 148
ifdef(`confERROR_MODE',
D 84
	concat(Oe, confERROR_MODE),
E 84
I 84
D 94
	CONCAT(Oe, confERROR_MODE),
E 94
I 94
	Oe`'confERROR_MODE,
E 94
E 84
	#Oep)
E 148
I 148
_OPTION(ErrorMode, `confERROR_MODE', print)
E 148

# save Unix-style "From_" lines at top of header?
D 94
CONCAT(Of, confSAVE_FROM_LINES)
E 94
I 94
D 148
Of`'confSAVE_FROM_LINES
E 148
I 148
_OPTION(SaveFromLine, `confSAVE_FROM_LINES')
E 148
E 94

# temporary file mode
D 94
CONCAT(OF, confTEMP_FILE_MODE)
E 94
I 94
D 148
OF`'confTEMP_FILE_MODE
E 148
I 148
_OPTION(TempFileMode, `confTEMP_FILE_MODE', 0600)
E 148
E 94

# match recipients against GECOS field?
D 94
CONCAT(OG, confMATCH_GECOS)
E 94
I 94
D 148
OG`'confMATCH_GECOS
E 148
I 148
_OPTION(MatchGECOS, `confMATCH_GECOS')
E 148
E 94

D 148
# default GID
D 94
CONCAT(Og, confDEF_GROUP_ID)
E 94
I 94
Og`'confDEF_GROUP_ID
E 94

E 148
# maximum hop count
D 94
CONCAT(Oh, confMAX_HOP)
E 94
I 94
D 148
Oh`'confMAX_HOP
E 148
I 148
_OPTION(MaxHopCount, `confMAX_HOP', 17)
E 148
E 94

# location of help file
D 94
CONCAT(OH, ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf))
E 94
I 94
D 148
OH`'ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf)
E 148
I 148
O HelpFile=ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf)
E 148
E 94

# ignore dots as terminators in incoming messages?
D 94
CONCAT(Oi, confIGNORE_DOTS)
E 94
I 94
D 148
Oi`'confIGNORE_DOTS
E 148
I 148
_OPTION(IgnoreDots, `confIGNORE_DOTS')
E 148
E 94

D 148
# Insist that the BIND name server be running to resolve names
ifdef(`confBIND_OPTS',
D 94
	CONCAT(OI, confBIND_OPTS),
E 94
I 94
	OI`'confBIND_OPTS,
E 94
	#OI)
E 148
I 148
# name resolver options
_OPTION(ResolverOptions, `confBIND_OPTS', +AAONLY)
E 148

I 72
# deliver MIME-encapsulated error messages?
D 94
CONCAT(Oj, confMIME_FORMAT_ERRORS)
E 94
I 94
D 148
Oj`'confMIME_FORMAT_ERRORS
E 148
I 148
_OPTION(SendMimeErrors, `confMIME_FORMAT_ERRORS')
E 148
E 94

E 72
# Forward file search path
D 148
ifdef(`confFORWARD_PATH',
D 94
	CONCAT(OJ, confFORWARD_PATH),
E 94
I 94
	OJ`'confFORWARD_PATH,
E 94
	#OJ/var/forward/$u:$z/.forward.$w:$z/.forward)
E 148
I 148
_OPTION(ForwardPath, `confFORWARD_PATH', /var/forward/$u:$z/.forward.$w:$z/.forward)
E 148

# open connection cache size
D 94
CONCAT(Ok, confMCI_CACHE_SIZE)
E 94
I 94
D 148
Ok`'confMCI_CACHE_SIZE
E 148
I 148
_OPTION(ConnectionCacheSize, `confMCI_CACHE_SIZE', 2)
E 148
E 94

# open connection cache timeout
D 94
CONCAT(OK, confMCI_CACHE_TIMEOUT)
E 94
I 94
D 148
OK`'confMCI_CACHE_TIMEOUT
E 148
I 148
_OPTION(ConnectionCacheTimeout, `confMCI_CACHE_TIMEOUT', 5m)
E 148
E 94

I 77
# use Errors-To: header?
D 94
CONCAT(Ol, confUSE_ERRORS_TO)
E 94
I 94
D 148
Ol`'confUSE_ERRORS_TO
E 148
I 148
_OPTION(UseErrorsTo, `confUSE_ERRORS_TO')
E 148
E 94

E 77
# log level
D 94
CONCAT(OL, confLOG_LEVEL)
E 94
I 94
D 148
OL`'confLOG_LEVEL
E 148
I 148
_OPTION(LogLevel, `confLOG_LEVEL', 10)
E 148
E 94

# send to me too, even in an alias expansion?
D 94
CONCAT(Om, confME_TOO)
E 94
I 94
D 148
Om`'confME_TOO
E 148
I 148
_OPTION(MeToo, `confME_TOO')
E 148
E 94

# verify RHS in newaliases?
D 94
CONCAT(On, confCHECK_ALIASES)
E 94
I 94
D 148
On`'confCHECK_ALIASES
E 148
I 148
_OPTION(CheckAliases, `confCHECK_ALIASES')
E 148
E 94

# default messages to old style headers if no special punctuation?
D 94
CONCAT(Oo, confOLD_STYLE_HEADERS)
E 94
I 94
D 148
Oo`'confOLD_STYLE_HEADERS
E 148
I 148
_OPTION(OldStyleHeaders, `confOLD_STYLE_HEADERS')
E 148
E 94

I 64
# SMTP daemon options
D 148
ifdef(`confDAEMON_OPTIONS',
D 94
	CONCAT(OO, confDAEMON_OPTIONS),
E 94
I 94
	OO`'confDAEMON_OPTIONS,
E 94
	#OOPort=esmtp)
E 148
I 148
_OPTION(DaemonPortOptions, `confDAEMON_OPTIONS', Port=esmtp)
E 148

E 64
I 40
# privacy flags
D 94
CONCAT(Op, confPRIVACY_FLAGS)
E 94
I 94
D 148
Op`'confPRIVACY_FLAGS
E 148
I 148
_OPTION(PrivacyOptions, `confPRIVACY_FLAGS', authwarnings)
E 148
E 94

E 40
# who (if anyone) should get extra copies of error messages
D 148
ifdef(`confCOPY_ERRORS_TO',
D 94
	CONCAT(OP, confCOPY_ERRORS_TO),
E 94
I 94
	OP`'confCOPY_ERRORS_TO,
E 94
	#OPPostmaster)
E 148
I 148
_OPTION(PostMasterCopy, `confCOPY_ERRORS_TO', Postmaster)
E 148

# slope of queue-only function
D 148
ifdef(`confQUEUE_FACTOR',
D 94
	CONCAT(Oq, confQUEUE_FACTOR),
E 94
I 94
	Oq`'confQUEUE_FACTOR,
E 94
	#Oq600000)
E 148
I 148
_OPTION(QueueFactor, `confQUEUE_FACTOR', 600000)
E 148

# queue directory
D 94
CONCAT(OQ, ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue))
E 94
I 94
D 148
OQ`'ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue)
E 148
I 148
O QueueDirectory=ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue)
E 148
E 94

D 148
# read timeout -- now OK per RFC 1123 section 5.3.2
I 42
ifdef(`confREAD_TIMEOUT',
D 94
	CONCAT(Or, confREAD_TIMEOUT),
E 94
I 94
	Or`'confREAD_TIMEOUT,
E 94
	#Ordatablock=10m)
E 148
I 148
# timeouts (many of these)
_OPTION(Timeout.initial, `confTO_INITIAL', 5m)
_OPTION(Timeout.helo, `confTO_HELO', 5m)
_OPTION(Timeout.mail, `confTO_MAIL', 10m)
_OPTION(Timeout.rcpt, `confTO_RCPT', 1h)
_OPTION(Timeout.datainit, `confTO_DATAINIT', 5m)
_OPTION(Timeout.datablock, `confTO_DATABLOCK', 1h)
_OPTION(Timeout.datafinal, `confTO_DATAFINAL', 1h)
_OPTION(Timeout.rset, `confTO_RSET', 5m)
_OPTION(Timeout.quit, `confTO_QUIT', 2m)
_OPTION(Timeout.misc, `confTO_MISC', 2m)
_OPTION(Timeout.command, `confTO_COMMAND', 1h)
_OPTION(Timeout.ident, `confTO_IDENT', 30s)
_OPTION(Timeout.fileopen, `confTO_FILEOPEN', 60s)
_OPTION(Timeout.queuereturn, `confTO_QUEUERETURN', 5d)
_OPTION(Timeout.queuereturn.normal, `confTO_QUEUERETURN_NORMAL', 5d)
_OPTION(Timeout.queuereturn.urgent, `confTO_QUEUERETURN_URGENT', 2d)
_OPTION(Timeout.queuereturn.non-urgent, `confTO_QUEUERETURN_NONURGENT', 7d)
_OPTION(Timeout.queuewarn, `confTO_QUEUEWARN', 4h)
_OPTION(Timeout.queuewarn.normal, `confTO_QUEUEWARN_NORMAL', 4h)
_OPTION(Timeout.queuewarn.urgent, `confTO_QUEUEWARN_URGENT', 1h)
_OPTION(Timeout.queuewarn.non-urgent, `confTO_QUEUEWARN_NONURGENT', 12h)
E 148
E 42
D 46
CONCAT(Or, confREAD_TIMEOUT)
E 46

I 140
# should we not prune routes in route-addr syntax addresses?
D 148
OR`'confDONT_PRUNE_ROUTES
E 148
I 148
_OPTION(DontPruneRoutes, `confDONT_PRUNE_ROUTES')
E 148

E 140
# queue up everything before forking?
D 94
CONCAT(Os, confSAFE_QUEUE)
E 94
I 94
D 148
Os`'confSAFE_QUEUE
E 148
I 148
_OPTION(SuperSafe, `confSAFE_QUEUE')
E 148
E 94

# status file
D 94
CONCAT(OS, ifdef(`STATUS_FILE', STATUS_FILE, /etc/sendmail.st))
E 94
I 94
D 148
OS`'ifdef(`STATUS_FILE', STATUS_FILE, /etc/sendmail.st)
E 148
I 148
D 163
_OPTION(StatusFile, `STATUS_FILE', /etc/sendmail.st)
E 163
I 163
O StatusFile=ifdef(`STATUS_FILE', `STATUS_FILE', /etc/sendmail.st)
E 163
E 148
E 94

D 148
# default message timeout interval
D 94
CONCAT(OT, confMESSAGE_TIMEOUT)
E 94
I 94
OT`'confMESSAGE_TIMEOUT
E 94

E 148
# time zone handling:
#  if undefined, use system default
#  if defined but null, use TZ envariable passed in
#  if defined and non-null, use that info
D 148
ifelse(confTIME_ZONE, `USE_SYSTEM', `#Ot',
D 100
	confTIME_ZONE, `USE_TZ', `',
E 100
I 100
	confTIME_ZONE, `USE_TZ', `Ot',
E 100
D 94
	`CONCAT(Ot, confTIME_ZONE)')
E 94
I 94
	`Ot`'confTIME_ZONE')
E 148
I 148
ifelse(confTIME_ZONE, `USE_SYSTEM', `#O TimeZoneSpec=',
	confTIME_ZONE, `USE_TZ', `O TimeZoneSpec=',
	`O TimeZoneSpec=confTIME_ZONE')
E 148
E 94

D 148
# default UID
D 94
CONCAT(Ou, confDEF_USER_ID)
E 94
I 94
Ou`'confDEF_USER_ID
E 148
I 148
# default UID (can be username or userid:groupid)
_OPTION(DefaultUser, `confDEF_USER_ID', nobody)
E 148
E 94

# list of locations of user database file (null means no lookup)
D 58
CONCAT(OU, ifdef(`USERDB_SPEC', `USERDB_SPEC'))
E 58
I 58
D 148
OU`'ifdef(`confUSERDB_SPEC', `confUSERDB_SPEC')
E 148
I 148
_OPTION(UserDatabaseSpec, `confUSERDB_SPEC', /etc/userdb)
E 148
I 64

# fallback MX host
D 148
ifdef(`confFALLBACK_MX',
D 94
	CONCAT(OV, confFALLBACK_MX),
E 94
I 94
	OV`'confFALLBACK_MX,
E 94
	#OVfall.back.host.net)
E 148
I 148
_OPTION(FallbackMXhost, `confFALLBACK_MX', fall.back.host.net)
E 148
E 64
E 58

I 87
# if we are the best MX host for a site, try it directly instead of config err
D 94
CONCAT(Ow, confTRY_NULL_MX_LIST)
E 94
I 94
D 148
Ow`'confTRY_NULL_MX_LIST
E 148
I 148
_OPTION(TryNullMXList, `confTRY_NULL_MX_LIST')
E 148
E 94

E 87
D 38
# can we guarantee no wildcard MX records matching our domain?
CONCAT(Ow, confNO_WILDCARD_MX)

E 38
# load average at which we just queue messages
D 94
CONCAT(Ox, confQUEUE_LA)
E 94
I 94
D 148
Ox`'confQUEUE_LA
E 148
I 148
_OPTION(QueueLA, `confQUEUE_LA', 8)
E 148
E 94

# load average at which we refuse connections
D 94
CONCAT(OX, confREFUSE_LA)
E 94
I 94
D 148
OX`'confREFUSE_LA
E 148
I 148
_OPTION(RefuseLA, `confREFUSE_LA', 12)
E 148
E 94

# work recipient factor
D 148
ifdef(`confWORK_RECIPIENT_FACTOR',
D 94
	CONCAT(Oy, confWORK_RECIPIENT_FACTOR),
E 94
I 94
	Oy`'confWORK_RECIPIENT_FACTOR,
E 94
	#Oy30000)
E 148
I 148
_OPTION(RecipientFactor, `confWORK_RECIPIENT_FACTOR', 30000)
E 148

# deliver each queued job in a separate process?
D 94
CONCAT(OY, confSEPARATE_PROC)
E 94
I 94
D 148
OY`'confSEPARATE_PROC
E 148
I 148
_OPTION(ForkEachJob, `confSEPARATE_PROC')
E 148
E 94

# work class factor
D 148
ifdef(`confWORK_CLASS_FACTOR',
D 94
	CONCAT(Oz, confWORK_CLASS_FACTOR),
E 94
I 94
	Oz`'confWORK_CLASS_FACTOR,
E 94
	#Oz1800)
E 148
I 148
_OPTION(ClassFactor, `confWORK_CLASS_FACTOR', 1800)
E 148

# work time factor
D 148
ifdef(`confWORK_TIME_FACTOR',
D 94
	CONCAT(OZ, confWORK_TIME_FACTOR),
E 94
I 94
	OZ`'confWORK_TIME_FACTOR,
E 94
	#OZ90000)
E 148
I 148
_OPTION(RetryFactor, `confWORK_TIME_FACTOR', 90000)
E 148

I 139
D 151
# do our SMTP peers choke on multi-line greeting messages?
D 148
O BrokenSmtpPeers=confBROKEN_SMTP_PEERS
E 148
I 148
_OPTION(BrokenSmtpPeers, `confBROKEN_SMTP_PEERS')
E 148

E 151
# shall we sort the queue by hostname first?
D 147
O SortQueueByHost=confSORT_QUEUE_BY_HOST
E 147
I 147
D 148
O QueueSortOrder=confQUEUE_SORT_ORDER
E 148
I 148
_OPTION(QueueSortOrder, `confQUEUE_SORT_ORDER', priority)
E 148
E 147

I 148
# minimum time in queue before retry
_OPTION(MinQueueAge, `confMIN_QUEUE_AGE', 30m)

# default character set
_OPTION(DefaultCharSet, `confDEF_CHAR_SET', iso-8859-1)

# service switch file (ignored on Solaris, Ultrix, OSF/1, others)
_OPTION(ServiceSwitchFile, `confSERVICE_SWITCH_FILE', /etc/service.switch)

# dialup line delay on connection failure
_OPTION(DialDelay, `confDIAL_DELAY', 10s)

# action to take if there are no recipients in the message
_OPTION(NoRecipientAction, `confNO_RCPT_ACTION', add-to-undisclosed)

# chrooted environment for writing to files
_OPTION(SafeFileEnvironment, `confSAFE_FILE_ENV', /arch)

I 152
# are colons OK in addresses?
_OPTION(ColonOkInAddr, `confCOLON_OK_IN_ADDR')

I 162
# how many jobs can you process in the queue?
_OPTION(MaxQueueRunSize, `confMAX_QUEUE_RUN_SIZE', 10000)

I 166
# shall I avoid expanding CNAMEs (violates protocols)?
_OPTION(DontExpandCnames, `confDONT_EXPAND_CNAMES')

E 166
E 162
E 152
E 148
E 139
###########################
#   Message precedences   #
###########################

Pfirst-class=0
Pspecial-delivery=100
I 39
Plist=-30
E 39
Pbulk=-60
Pjunk=-100

#####################
#   Trusted users   #
#####################

I 148
# this is equivalent to setting class "t"
#Ft/etc/sendmail.trusted
E 148
Troot
Tdaemon
Tuucp

#########################
#   Format of headers   #
#########################

D 56
H?P?Return-Path: <$?<$<$|$g$.>
E 56
I 56
H?P?Return-Path: $g
E 56
D 65
HReceived: $?sfrom $s $.by $j ($v/$Z) id $i; $b
E 65
I 65
D 76
HReceived: $?sfrom $s $.$?_($_) $.by $j ($v/$Z) id $i; $b
E 76
I 76
D 95
HReceived: $?sfrom $s $.$?_($_) $.by $j ($v/$Z)$?r with $r$. id $i; $b
E 95
I 95
D 118
HReceived: $?sfrom $s $.$?_($_) $.by $j ($v/$Z)$?r with $r$. id $i$?u for $u$.; $b
E 118
I 118
D 141
HReceived: $?sfrom $s $.$?_($?s$|from $.$_) $.by $j ($v/$Z)$?r with $r$. id $i$?u for $u$.; $b
E 141
I 141
HReceived: confRECEIVED_HEADER
E 141
E 118
E 95
E 76
E 65
H?D?Resent-Date: $a
H?D?Date: $a
H?F?Resent-From: $q
H?F?From: $q
H?x?Full-Name: $x
HSubject:
# HPosted-Date: $a
# H?l?Received-Date: $b
H?M?Resent-Message-Id: <$t.$i@$j>
H?M?Message-Id: <$t.$i@$j>
I 148
ifdef(`_NULL_CLIENT_ONLY_',
	`include(../m4/nullrelay.m4)m4exit',
	`dnl')
E 148
E 37
I 31
D 67
undivert(6)dnl
E 67
E 31
D 4

E 4
#
######################################################################
######################################################################
#####
#####			REWRITING RULES
#####
######################################################################
######################################################################

I 55
undivert(9)dnl
E 55

###########################################
###  Rulset 3 -- Name Canonicalization  ###
###########################################
D 4
`S3
E 4
I 4
S3
E 4

I 44
D 52
# handle null input (translate to <> special case)
D 48
R$@			$@ <@>
E 48
I 48
R$@			$@ <>
E 52
I 52
D 104
# handle null input and list syntax (translate to <@> special case)
E 104
I 104
# handle null input (translate to <@> special case)
E 104
R$@			$@ <@>
D 57
R$*:;$*			$@ $1 ;: <@>
E 57
I 57
D 104
R$*:;$*			$@ $1 :; <@>
E 104
E 57
E 52
E 48

I 150
# strip group: syntax (not inside angle brackets!) and trailing semicolon
R$*			$: $1 <@>			mark addresses
R$* < $* > $* <@>	$: $1 < $2 > $3			unmark <addr>
D 158
R$* :: $* <@>		$: $1 :: $2			unmark host::addr
E 158
I 158
R$* :: $* <@>		$: $1 :: $2			unmark node::addr
E 158
I 156
D 160
R:include: $* <@>	$: :include: $1			unmark :include:...
E 160
I 160
D 164
R:`include': $* <@>	$: :`include': $1			unmark :include:...
E 164
I 164
R:`include': $* <@>	$: :`include': $1			unmark :`include':...
E 164
E 160
E 156
R$* : $* <@>		$: $2				strip colon if marked
R$* <@>			$: $1				unmark
R$* ;			$: $1				strip trailing semi

# null input now results from list:; syntax
R$@			$@ :; <@>

E 150
E 44
D 43
# handle "from:<>" special case
D 26
R$*<>$*			$@@				turn into magic token
E 26
I 26
D 42
R$* < > $*		$@ @				turn into magic token
E 42
I 42
R$* < > $*		$@ <@>				turn into magic token
E 42
E 26

E 43
# basic textual canonicalization -- note RFC733 heuristic here
I 33
D 96
R$*<$*>$*<$*>$*		<$2>$3$4$5			strip multiple <> <>
E 96
I 96
R$*<$*>$*<$*>$*		$2$3<$4>$5			strip multiple <> <>
E 96
E 33
D 43
R$*<$*<$*<$+>$*>$*>$*	$4				3-level <> nesting
R$*<$*<$+>$*>$*		$3				2-level <> nesting
E 43
I 43
R$*<$*<$+>$*>$*		<$3>$5				2-level <> nesting
D 45
R$*<>$*			$@ $<@>				MAIL FROM:<> case
E 45
I 45
D 48
R$*<>$*			$@ <@>				MAIL FROM:<> case
E 48
I 48
D 52
R$*<>$*			$@ <>				MAIL FROM:<> case
E 52
I 52
R$*<>$*			$@ <@>				MAIL FROM:<> case
E 52
E 48
E 45
E 43
R$*<$+>$*		$2				basic RFC821/822 parsing
I 104
D 150

# handle list:; syntax as special case
R$*:;$*			$@ $1 :; <@>
E 150
E 104

# make sure <@a,@b,@c:user@d> syntax is easy to parse -- undone later
D 26
R@$+,$+			@$1:$2				change all "," to ":"
E 26
I 26
R@ $+ , $+		@ $1 : $2			change all "," to ":"
E 26

# localize and dispose of route-based addresses
D 26
R@$+:$+			$@$>6<@$1>:$2			handle <route-addr>
E 26
I 26
D 76
R@ $+ : $+		$@ $>6 < @$1 > : $2		handle <route-addr>
E 76
I 76
D 134
R@ $+ : $+		$@ $>_SET_96_ < @$1 > : $2		handle <route-addr>
E 134
I 134
R@ $+ : $+		$@ $>96 < @$1 > : $2		handle <route-addr>
E 134
E 76
E 26

# find focus for list syntax
D 26
R$+:$*;@$+		$@$>6$1:$2;<@$3>		list syntax
R$+:$*;			$@$1:$2;			list syntax
E 26
I 26
D 76
R $+ : $* ; @ $+	$@ $>6 $1 : $2 ; < @ $3 >	list syntax
E 76
I 76
D 134
R $+ : $* ; @ $+	$@ $>_SET_96_ $1 : $2 ; < @ $3 >	list syntax
E 134
I 134
R $+ : $* ; @ $+	$@ $>96 $1 : $2 ; < @ $3 >	list syntax
E 134
E 76
R $+ : $* ;		$@ $1 : $2;			list syntax
E 26

# find focus for @ syntax addresses
D 26
R$+@$+			$:$1<@$2>			focus on domain
R$+<$+@$+>		$1$2<@$3>			move gaze right
R$+<@$+>		$@$>6$1<@$2>			already canonical
E 26
I 26
R$+ @ $+		$: $1 < @ $2 >			focus on domain
R$+ < $+ @ $+ >		$1 $2 < @ $3 >			move gaze right
D 76
R$+ < @ $+ >		$@ $>6 $1 < @ $2 >		already canonical
E 76
I 76
D 134
R$+ < @ $+ >		$@ $>_SET_96_ $1 < @ $2 >		already canonical
E 134
I 134
R$+ < @ $+ >		$@ $>96 $1 < @ $2 >		already canonical
E 134
E 76
E 26

I 106
# do some sanity checking
R$* < @ $* : $* > $*	$1 < @ $2 $3 > $4		nix colons in addrs

E 106
D 47
# convert old-style addresses to a domain-based address
E 47
I 47
ifdef(`_NO_UUCP_', `dnl',
`# convert old-style addresses to a domain-based address
E 47
D 26
R$-!$+			$@$>6$2<@$1.UUCP>		resolve uucp names
R$+.$-!$+		$@$>6$3<@$1.$2>			domain uucps
R$+!$+			$@$>6$2<@$1.UUCP>		uucp subdomains
E 26
I 26
D 76
R$- ! $+		$@ $>6 $2 < @ $1 .UUCP >	resolve uucp names
R$+ . $- ! $+		$@ $>6 $3 < @ $1 . $2 >		domain uucps
D 47
R$+ ! $+		$@ $>6 $2 < @ $1 .UUCP >	uucp subdomains
E 47
I 47
R$+ ! $+		$@ $>6 $2 < @ $1 .UUCP >	uucp subdomains')
E 76
I 76
D 134
R$- ! $+		$@ $>_SET_96_ $2 < @ $1 .UUCP >	resolve uucp names
R$+ . $- ! $+		$@ $>_SET_96_ $3 < @ $1 . $2 >		domain uucps
R$+ ! $+		$@ $>_SET_96_ $2 < @ $1 .UUCP >	uucp subdomains')
E 134
I 134
R$- ! $+		$@ $>96 $2 < @ $1 .UUCP >	resolve uucp names
R$+ . $- ! $+		$@ $>96 $3 < @ $1 . $2 >		domain uucps
D 158
R$+ ! $+		$@ $>96 $2 < @ $1 .UUCP >	uucp subdomains')
E 134
E 76
E 47
E 26

E 158
I 158
R$+ ! $+		$@ $>96 $2 < @ $1 .UUCP >	uucp subdomains
')
D 159
ifdef(`DECNET_RELAY',
E 159
I 159
ifdef(`_USE_DECNET_SYNTAX_',
E 159
`# convert node::user addresses into a domain-based address
R$- :: $+		$@ $>96 $2 < @ $1 .DECNET >	resolve DECnet names
I 159
R$- . $- :: $+		$@ $>96 $3 < @ $1.$2 .DECNET >	numeric DECnet addr
E 159
',
	`dnl')
E 158
# if we have % signs, take the rightmost one
D 26
R$*%$*			$1@$2				First make them all @s.
R$*@$*@$*		$1%$2@$3			Undo all but the last.
R$*@$*			$@$>6$1<@$2>			Insert < > and finish
E 26
I 26
R$* % $*		$1 @ $2				First make them all @s.
R$* @ $* @ $*		$1 % $2 @ $3			Undo all but the last.
D 76
R$* @ $*		$@ $>6 $1 < @ $2 >		Insert < > and finish
E 76
I 76
D 134
R$* @ $*		$@ $>_SET_96_ $1 < @ $2 >		Insert < > and finish
E 134
I 134
R$* @ $*		$@ $>96 $1 < @ $2 >		Insert < > and finish
E 134
E 76
E 26

# else we must be a local name
I 157
R$*			$@ $>96 $1
E 157


D 76
###############################################
###  Ruleset 6 -- bottom half of ruleset 3  ###
###############################################

E 76
I 76
################################################
D 134
###  Ruleset _SET_96_ -- bottom half of ruleset 3  ###
E 134
I 134
###  Ruleset 96 -- bottom half of ruleset 3  ###
E 134
################################################

E 76
D 4
#
E 4
D 34
#  At this point, everything should be in a local_part@domain format.
D 4
#  This ruleset is primarily responsible for 
E 4

E 34
I 34
D 157
#  At this point, everything should be in a "local_part<@domain>extra" format.
E 157
E 34
D 76
S6
E 76
I 76
D 134
S`'_SET_96_
E 134
I 134
S96
E 134
E 76
D 4
'
E 4
D 17
undivert(2)dnl
E 17

# handle special cases for local names
D 6
R$*<@$=w>$*		$:$1<@$w>$3			no domain at all
R$*<@$=w.UUCP>$*	$:$1<@$w>$3			.UUCP domain
E 6
I 6
D 11
R$* < @ $=w > $*		$: $1 < @ $w > $3		no domain at all
R$* < @ $=w .UUCP> $*		$: $1 < @ $w > $3		.UUCP domain
E 11
I 11
D 13
R$* < @ $=w > $*		$: $1 < @ $j > $3		no domain at all
R$* < @ $=w .UUCP> $*		$: $1 < @ $j > $3		.UUCP domain
E 13
I 13
D 74
R$* < @ $=w > $*		$: $1 < @ $j . > $3		no domain at all
D 26
R$* < @ $=w .UUCP> $*		$: $1 < @ $j . > $3		.UUCP domain
E 26
I 26
R$* < @ $=w . UUCP > $*		$: $1 < @ $j . > $3		.UUCP domain
E 74
I 74
R$* < @ localhost > $*		$: $1 < @ $j . > $2		no domain at all
R$* < @ localhost . $m > $*	$: $1 < @ $j . > $2		local domain
ifdef(`_NO_UUCP_', `dnl',
`R$* < @ localhost . UUCP > $*	$: $1 < @ $j . > $2		.UUCP domain')
I 102
D 115
R$* < @ [ $+ ] > $*		$: $1 < @ [[ $2 ]] > $3		catch [a.b.c.d]
R$* < @ [ $=w ] > $*		$: $1 < @ $j . > $3		self-literal
R$* < @ [[ $+ ]] > $*		$: $1 < @ [ $2 ] > $3		strip dbl [[]]
E 115
I 115
R$* < @ [ $+ ] > $*		$: $1 < @@ [ $2 ] > $3		mark [a.b.c.d]
R$* < @@ $=w > $*		$: $1 < @ $j . > $3		self-literal
D 130
R$* < @@ $+ > $*		$: $1 < @ $2 > $3		strip dbl @@
E 130
I 130
R$* < @@ $+ > $*		$@ $1 < @ $2 > $3		canon IP addr
E 130
E 115
E 102
I 86
ifdef(`DOMAIN_TABLE', `
D 133
# look up unqualified domains in the domain table
R$* < @ $- > $*			$: $1 < @ $(domaintable $2 $) > $3',
E 133
I 133
# look up domains in the domain table
R$* < @ $+ > $*			$: $1 < @ $(domaintable $2 $) > $3',
E 133
`dnl')
E 86
E 74
E 26
I 17
undivert(2)dnl
E 17
E 13
E 11
E 6
D 4
R$*<@$=U.UUCP>$*	$:$1<@$w>$3			UUCP-specific names
E 4

I 66
D 68
# hide non-local unqualified addresses behind sending domain
R$* < @ $&s > $*		$: $1 < @ $&s @ > $2		avoid loops
R$* < @ $- > $*			$: $1 < @ $2 @ $&r > $3		append protocol
R$* < @ $+ @ > $*		$: $1 < @ $2 > $3		local mail
R< @ $- @ $+ > $*		$@ $>6 < @ $&s > : @ $1 $3	route-addr
R$* < @ $- @ $+ >		$@ $>6 $1 % $2 < @ $&s >	non-route-addr

E 68
E 66
I 6
D 7
# if it's really UUCP, don't bother
E 7
I 7
D 69
ifdef(`UUCP_RELAY',
E 69
I 69
ifdef(`_NO_UUCP_', `dnl',
`ifdef(`UUCP_RELAY',
E 69
`# pass UUCP addresses straight through
D 26
R$* < @ $+ . UUCP > $*		$@ $1 < @ $2 .UUCP > $3',
E 26
I 26
D 107
R$* < @ $+ . UUCP > $*		$@ $1 < @ $2 . UUCP > $3',
E 107
I 107
R$* < @ $+ . UUCP > $*		$@ $1 < @ $2 . UUCP . > $3',
E 107
E 26
`# if really UUCP, handle it immediately
E 7
D 13
R$* < @ $=U . UUCP > $*		$@ $1 < @ $2 .UUCP > $3
R$* < @ $=V . UUCP > $*		$@ $1 < @ $2 .UUCP > $3
R$* < @ $=W . UUCP > $*		$@ $1 < @ $2 .UUCP > $3
R$* < @ $=X . UUCP > $*		$@ $1 < @ $2 .UUCP > $3
R$* < @ $=Y . UUCP > $*		$@ $1 < @ $2 .UUCP > $3
E 13
I 13
ifdef(`_CLASS_U_',
D 26
`R$* < @ $=U . UUCP > $*		$@ $1 < @ $2 .UUCP > $3', `dnl')
E 26
I 26
D 107
`R$* < @ $=U . UUCP > $*	$@ $1 < @ $2 . UUCP > $3', `dnl')
E 107
I 107
`R$* < @ $=U . UUCP > $*	$@ $1 < @ $2 . UUCP . > $3', `dnl')
E 107
E 26
ifdef(`_CLASS_V_',
D 26
`R$* < @ $=V . UUCP > $*		$@ $1 < @ $2 .UUCP > $3', `dnl')
E 26
I 26
D 107
`R$* < @ $=V . UUCP > $*	$@ $1 < @ $2 . UUCP > $3', `dnl')
E 107
I 107
`R$* < @ $=V . UUCP > $*	$@ $1 < @ $2 . UUCP . > $3', `dnl')
E 107
E 26
ifdef(`_CLASS_W_',
D 26
`R$* < @ $=W . UUCP > $*		$@ $1 < @ $2 .UUCP > $3', `dnl')
E 26
I 26
D 107
`R$* < @ $=W . UUCP > $*	$@ $1 < @ $2 . UUCP > $3', `dnl')
E 107
I 107
`R$* < @ $=W . UUCP > $*	$@ $1 < @ $2 . UUCP . > $3', `dnl')
E 107
E 26
ifdef(`_CLASS_X_',
D 26
`R$* < @ $=X . UUCP > $*		$@ $1 < @ $2 .UUCP > $3', `dnl')
E 26
I 26
D 107
`R$* < @ $=X . UUCP > $*	$@ $1 < @ $2 . UUCP > $3', `dnl')
E 107
I 107
`R$* < @ $=X . UUCP > $*	$@ $1 < @ $2 . UUCP . > $3', `dnl')
E 107
E 26
ifdef(`_CLASS_Y_',
D 26
`R$* < @ $=Y . UUCP > $*		$@ $1 < @ $2 .UUCP > $3', `dnl')
E 26
I 26
D 107
`R$* < @ $=Y . UUCP > $*	$@ $1 < @ $2 . UUCP > $3', `dnl')
E 107
I 107
`R$* < @ $=Y . UUCP > $*	$@ $1 < @ $2 . UUCP . > $3', `dnl')
E 107
E 26
E 13

# try UUCP traffic as a local address
D 13
R$* < @ $- .UUCP > $*		$: $1 < @ $[ $2 $] .UUCP > $3
D 7
R$* < @ $+ . $+ .UUCP > $*	$@ $1 < @ $2 . $3 > $4
E 7
I 7
R$* < @ $+ . $+ .UUCP > $*	$@ $1 < @ $2 . $3 > $4')
E 13
I 13
D 26
R$* < @ $+ .UUCP > $*			$: $1 < @ $[ $2 $] .UUCP > $3
E 26
I 26
D 107
R$* < @ $+ . UUCP > $*		$: $1 < @ $[ $2 $] . UUCP > $3
E 107
I 107
R$* < @ $+ . UUCP > $*		$: $1 < @ $[ $2 $] . UUCP . > $3
E 107
E 26
D 18
ifdef(`NEWSENDMAIL',
`R$* < @ $+ . .UUCP > $*		$@ $1 < @ $2 . > $3',
`R$* < @ $+ . $+ .UUCP > $*		$@ $1 < @ $2 . $3 > $4')')
E 18
I 18
D 134
ifdef(`_OLD_SENDMAIL_',
D 26
`R$* < @ $+ . $+ .UUCP > $*		$@ $1 < @ $2 . $3 > $4',
D 19
`R$* < @ $+ . .UUCP > $*		$@ $1 < @ $2 . > $3')
E 19
I 19
`R$* < @ $+ . .UUCP > $*		$@ $1 < @ $2 . > $3')')
E 26
I 26
D 107
`R$* < @ $+ . $+ . UUCP > $*		$@ $1 < @ $2 . $3 . > $4',
`R$* < @ $+ . . UUCP > $*		$@ $1 < @ $2 . > $3')')
E 107
I 107
`R$* < @ $+ . $+ . UUCP . > $*		$@ $1 < @ $2 . $3 . > $4',
`R$* < @ $+ . . UUCP . > $*		$@ $1 < @ $2 . > $3')')
E 134
I 134
R$* < @ $+ . . UUCP . > $*		$@ $1 < @ $2 . > $3')
E 134
E 107
E 26
E 19
E 18
E 13
E 7
D 69

E 6
# pass to name server to make hostname canonical
E 69
I 69
')
D 79
ifdef(`_NO_CANONIFY_', `dnl',
E 79
I 79
D 109
ifdef(`_NO_CANONIFY_',
`# make sure local host names appear canonical
R$* < @ $=w > $*		$: $1 < @ $2 . > $3',
E 109
I 109
ifdef(`_NO_CANONIFY_', `dnl',
E 109
E 79
`# pass to name server to make hostname canonical
E 69
D 6
R$* < @ $+ > $*		$: $1 < @ $[ $2 $] > $3		then do anything
E 6
I 6
D 13
R$* < @ $+ > $*			$: $1 < @ $[ $2 $] > $3		then do anything
E 13
I 13
D 73
R$* < @ $* $~. > $*		$: $1 < @ $[ $2 $3 $] > $4
E 73
I 73
D 79
R$* < @ $* $~P > $*		$: $1 < @ $[ $2 $3 $] > $4
E 73
E 13
E 6
D 69

E 69
I 69
')
E 79
I 79
R$* < @ $* $~P > $*		$: $1 < @ $[ $2 $3 $] > $4')

I 107
D 109
# pseudo-domains are always canonical
E 109
I 109
# local host aliases and pseudo-domains are always canonical
R$* < @ $=w > $*		$: $1 < @ $2 . > $3
E 109
R$* < @ $* $=P > $*		$: $1 < @ $2 $3 . > $4
D 109
R$* < @ $* . . > $*		$: $1 < @ $2 . > $3
E 109
I 109
R$* < @ $* . . > $*		$1 < @ $2 . > $3
E 109

E 107
E 79
E 69
I 17
D 74
# handle possible alternate names
R$* < @ $=w . $m . > $*		$: $1 < @ $j . > $3
R$* < @ $=w . $m > $*		$: $1 < @ $j . > $3
E 74
D 128
undivert(8)dnl

E 128
E 17
I 13
# if this is the local hostname, make sure we treat is as canonical
R$* < @ $j > $*			$: $1 < @ $j . > $2
E 13
D 5
# hack to add local domain if nothing sofar has done so
R$* < @ $- > $*		$: $1 < @ $2 @ $w > $3		throw on local host
R$* < @ $- @ $- $* > $*	$: $1 < @ $2 $4 > $5		strip host part only

E 5

I 13

E 13
##################################################
###  Ruleset 4 -- Final Output Post-rewriting  ###
##################################################
S4

D 42
R@			$@				handle <> error addr
E 42
I 42
D 48
R<@>			$@				handle <> error addr
E 48
I 48
D 52
R<>			$@				handle <> error addr
E 52
I 52
D 156
R$*<@>			$@ $1				handle <> and list:;
E 156
I 156
R$* <@>			$@				handle <> and list:;
E 156
E 52
E 48
E 42

D 130
# resolve numeric addresses to name if possible
D 13
R$*<@[$+]>$*		$:$1<@$[[$2]$]>$3		lookup numeric internet addr
E 13
I 13
R$* < @ [ $+ ] > $*	$: $1 < @ $[ [$2] $] > $3	lookup numeric internet addr
E 13

E 130
I 13
# strip trailing dot off possibly canonical name
R$* < @ $+ . > $*	$1 < @ $2 > $3

E 13
# externalize local domain info
D 13
R$*<$+>$*		$1$2$3				defocus
R@$+:@$+:$+		@$1,@$2:$3			<route-addr> canonical
E 13
I 13
R$* < $+ > $*		$1 $2 $3			defocus
R@ $+ : @ $+ : $+	@ $1 , @ $2 : $3		<route-addr> canonical
I 20
R@ $*			$@ @ $1				... and exit
E 20
E 13

D 47
# UUCP must always be presented in old form
D 13
R$+@$-.UUCP		$2!$1				u@h.UUCP => h!u
E 13
I 13
R$+ @ $- . UUCP		$2!$1				u@h.UUCP => h!u
E 47
I 47
ifdef(`_NO_UUCP_', `dnl',
`# UUCP must always be presented in old form
R$+ @ $- . UUCP		$2!$1				u@h.UUCP => h!u')
E 47
E 13

I 159
ifdef(`_USE_DECNET_SYNTAX_',
`# put DECnet back in :: form
R$+ @ $+ . DECNET	$2 :: $1			u@h.DECNET => h::u',
	`dnl')
E 159
# delete duplicate local names
D 11
R$+%$=w@$=w		$1@$w				u%host@host => u@host
E 11
I 11
D 13
R$+%$=w@$=w		$1@$j				u%host@host => u@host
E 13
I 13
R$+ % $=w @ $=w		$1 @ $j				u%host@host => u@host
E 13
E 11
D 4
#R$+%$=w@$=w.$D		$1@$w				u%host@host => u@host
E 4



D 76
#############################################################
###   Ruleset 7 -- recanonicalize and call ruleset zero   ###
###		   (used for recursive calls)		  ###
#############################################################
E 76
I 76
##############################################################
D 134
###   Ruleset _SET_97_ -- recanonicalize and call ruleset zero   ###
E 134
I 134
###   Ruleset 97 -- recanonicalize and call ruleset zero   ###
E 134
###		   (used for recursive calls)		   ###
##############################################################
E 76

D 76
S7
E 76
I 76
D 134
S`'_SET_97_
E 134
I 134
S`'97
E 134
E 76
R$*			$: $>3 $1
R$*			$@ $>0 $1


######################################
###   Ruleset 0 -- Parse Address   ###
######################################

S0
I 48

D 54
R<>			$#local $: <>			special case error msgs
E 54
I 54
D 92
R<@>			$#local $: <>			special case error msgs
E 92
I 92
D 131
R<@>			$#_LOCAL_ $: <>			special case error msgs
E 131
I 131
R<@>			$#_LOCAL_ $: <@>		special case error msgs
E 131
E 92
I 72
D 119
R$*:;<@>		$#error $@ USAGE $: "list:; syntax illegal for recipient addresses"
E 119
I 119
D 155
R$* : $* ;		$#error $@ USAGE $: "list:; syntax illegal for recipient addresses"
E 119
I 108
R<@ $+>			$#error $@ USAGE $: "user address required"
I 129
D 131
R<$* : $* >		$#error $@ USAGE $: "colon illegal in host name part"
E 131
I 131
R$* <$* : $* > $*	$#error $@ USAGE $: "colon illegal in host name part"
I 132
R$* < @ . > $*		$#error $@ USAGE $: "invalid host name"
E 155
I 155
R$* : $* ; <@>		$#error $@ 5.1.3 $: "list:; syntax illegal for recipient addresses"
R<@ $+>			$#error $@ 5.1.1 $: "user address required"
R$* <$* : $* > $*	$#error $@ 5.1.1 $: "colon illegal in host name part"
R$* < @ . > $*		$#error $@ 5.1.2 $: "invalid host name"
E 155
E 132
E 131
E 129
E 108
E 72
E 54
E 48

D 26
# handle numeric address spec
E 26
I 26
ifdef(`_MAILER_smtp_',
`# handle numeric address spec
E 26
D 13
R$*<@[$+]>$*		$:$1<@$[[$2]$]>$3		numeric internet addr
R$*<@[$+]>$*		$#smtp$@[$2]$:$1@[$2]$3		numeric internet spec
E 13
I 13
D 87
R$* < @ [ $+ ] > $*	$: $1 < @ $[ [$2] $] > $3	numeric internet addr
D 26
R$* < @ [ $+ ] > $*	$#smtp $@ [$2] $: $1 @ [$2] $3	numeric internet spec
E 26
I 26
R$* < @ [ $+ ] > $*	$#smtp $@ [$2] $: $1 @ [$2] $3	numeric internet spec',
D 30
`dnl')dnl
E 30
I 30
`dnl')
E 87
I 87
D 88
ifdef(`_NO_CANONIFY_',
`R$* < @ [ $+ ] > $*	$: $1 < @ $[ [$2] $] > $3	numeric internet addr',
	`dnl')
E 88
I 88
D 130
ifdef(`_NO_CANONIFY_', `dnl',
`R$* < @ [ $+ ] > $*	$: $1 < @ $[ [$2] $] > $3	numeric internet addr')
E 130
E 88
D 134
R$* < @ [ $+ ] > $*	$: $>_SET_98_ $1 < @ [ $2 ] > $3	numeric internet spec
E 134
I 134
R$* < @ [ $+ ] > $*	$: $>98 $1 < @ [ $2 ] > $3	numeric internet spec
E 134
D 91
R$* < @ [ $+ ] > $*	$#smtp $@ [$2] $: $1 @ [$2] $3	still numeric: send',
E 91
I 91
D 112
R$* < @ [ $+ ] > $*	$#_SMTP_ $@ [$2] $: $1 @ [$2] $3	still numeric: send',
E 112
I 112
R$* < @ [ $+ ] > $*	$#_SMTP_ $@ [$2] $: $1 < @ [$2] > $3	still numeric: send',
E 112
E 91
	`dnl')
E 87
E 30
E 26
E 13

D 26
#R@			$#error$:Invalid address	handle <> form

E 26
D 13
# now delete the local info -- note $=O to find characters that cause forwarding
D 11
R<@$w>:$*		$@$>7$1				@here:... -> ...
R$*$=O$*<@$w>		$@$>7$1$2$3			...@here -> ...
E 11
I 11
R<@$j>:$*		$@$>7$1				@here:... -> ...
R$*$=O$*<@$j>		$@$>7$1$2$3			...@here -> ...
E 13
I 13
D 14
ifdef(`NEWSENDMAIL',
E 14
I 14
D 16
ifdef(`LOCAL_RELAY',
E 14
`# now delete the local info -- note $=O to find characters that cause forwarding
E 16
I 16
# now delete the local info -- note $=O to find characters that cause forwarding
I 51
D 76
R$* < @ > $*		$@ $>7 $1			user@ => user
E 51
E 16
R< @ $j . > : $*	$@ $>7 $1			@here:... -> ...
R$* $=O $* < @ $j . >	$@ $>7 $1 $2 $3			...@here -> ...
E 76
I 76
D 99
R$* < @ > $*		$@ $>_SET_97_ $1			user@ => user
R< @ $=w . > : $*	$@ $>_SET_97_ $2			@here:... -> ...
R$* $=O $* < @ $=w . >	$@ $>_SET_97_ $1 $2 $3			...@here -> ...
E 99
I 99
D 134
R$* < @ > $*		$@ $>_SET_97_ $1		user@ => user
R< @ $=w . > : $*	$@ $>_SET_97_ $2		@here:... -> ...
R$* $=O $* < @ $=w . >	$@ $>_SET_97_ $1 $2 $3		...@here -> ...
E 134
I 134
R$* < @ > $*		$@ $>97 $1		user@ => user
R< @ $=w . > : $*	$@ $>97 $2		@here:... -> ...
R$* $=O $* < @ $=w . >	$@ $>97 $1 $2 $3		...@here -> ...
E 134
E 99
I 90

# handle local hacks
D 134
R$*			$: $>_SET_98_ $1
E 134
I 134
R$*			$: $>98 $1
E 134
E 90
E 76
I 60
D 121
D 125
ifdef(`MAILER_TABLE',
`
# try mailer table lookup
D 63
R$* < @ $+ > $*		$: $1 < @ $(mailertable $2 $) $3
E 63
I 63
D 75
R$* < @ $+ > $*		$: $1 < @ $(mailertable $2 $) > $3
E 63
D 70
R$* < @ $-:$+ > $*	$# $2 $@ $3 $: $1 < @ $3 > $4	found a match',
E 75
I 75
R$* <@ $+ > $*		$: < $2 > $1 < @ $2 > $3	extract host name
D 77
R<$+ . > $*		$: < $1 > $2			strip trailing dot
R<$- . $+ > $*		$: < $(mailertable .$2 $: $) > $3	lookup
R<$- : $+ > $*		$# $1 $@ $2 $: $3		check -- resolved?
R<$- . $+ > $*		$: $>90 <$2> $3			try domain',
E 77
I 77
R< $+ . > $*		$: < $1 > $2			strip trailing dot
D 80
R< $+ > $*		$: < $(mailertable .$1 $) > $3	lookup
E 80
I 80
D 82
R< $+ > $*		$: < $(mailertable $1 $) > $3	lookup
E 82
I 82
R< $+ > $*		$: < $(mailertable $1 $) > $2	lookup
E 82
E 80
R< $- : $+ > $*		$# $1 $@ $2 $: $3		check -- resolved?
D 82
R< $- . $+ > $*		$: $>90 <$2> $3			try domain',
E 82
I 82
R< $+ > $*		$: $>90 <$1> $2			try domain',
E 82
E 77
E 75
E 70
I 70
R$* < @ $-:$+ > $*	$# $2 $@ $3 $: $1 @ $3 $4	found a match',
E 70
`dnl')
E 125
E 121
E 60
E 13
E 11

# short circuit local delivery so forwarded email works
I 165
ifdef(`_MAILER_usenet_',
`R$+ . USENET < @ $=w . >	$#usenet $: $1		handle usenet specially',
	`dnl')
E 165
I 120
R$* < @ $=w . >		$: < $R @ $H > $1 < @ $2 . >	if both relay & hub ...
R<$+ @ $+ > $* < $+ >	$: $>_SET_95_ < $H > $3 < $4 >	... send direct to hub
R<$* @ $* > $* < $+ >	$: $3 < $4 >
E 120
I 36
D 53
R$+ < @ $j . >		$: $1 < @ $j @ $H >		first try hub
E 53
I 53
D 142
ifdef(`_LOCAL_NOT_STICKY_',
E 142
I 142
ifdef(`_STICKY_LOCAL_DOMAIN_',
`R$+ < @ $=w . >		$: < $H > $1 < @ $2 . >		first try hub
D 143
R< $+ > $+ < $+ >	$#_LOCAL_ $: $2			yep ....
E 143
I 143
D 146
R< $+ > $+ + $* < $+ >	$#_LOCAL_ $@ $3 $: $2		yep (plussed name) ....
R< $+ > $+ < $+ >	$#_LOCAL_ $: $2			yep (nonplussed) ....
E 146
I 146
D 149
R< $+ > $+ < $+ >	$#_LOCAL_ $: $2			yep ....
E 149
I 149
R< $+ > $+ < $+ >	$>95 < $1 > $2 < $3 >		yep ....
E 149
E 146
E 143
D 157
R< > $=D . $+ < $+ >	$#_LOCAL_ $: $1 . $2		dotted name?
E 157
I 143
D 146
R< > $+ + $* < $+ >	$#_LOCAL_ $@ $2 $: $1		plussed name?
E 146
I 146
R< > $+ + $* < $+ >	$#_LOCAL_ $: $1 + $2		plussed name?
E 146
E 143
R< > $+ < $+ >		$#_LOCAL_ $: @ $1			nope, local address',
E 142
D 76
`R$=L < @ $j . >		$#local $: @ $1			special local names
R$+ < @ $j . >		$#local $: $1			dispose directly',
`R$+ < @ $j . >		$: $1 < @ $j @ $H >		first try hub
E 76
I 76
D 92
`R$=L < @ $=w . >		$#local $: @ $1			special local names
R$+ < @ $=w . >		$#local $: $1			dispose directly',
E 92
I 92
D 120
D 149
`R$=L < @ $=w . >		$#_LOCAL_ $: @ $1			special local names
E 149
I 149
`R$=L < @ $=w . >	$#_LOCAL_ $: @ $1		special local names
E 149
D 142
R$+ < @ $=w . >		$#_LOCAL_ $: $1			dispose directly',
E 92
D 107
`R$+ < @ $=w . >		$: $1 < @ $2 @ $H >		first try hub
E 107
I 107
`R$+ < @ $=w . >		$: $1 < @ $2 . @ $H >		first try hub
E 107
E 76
E 53
E 36
D 11
R$+<@$w>		$#local$:$1			local address
E 11
I 11
D 13
R$+<@$j>		$#local$:$1			local address
E 13
I 13
D 14
R$+ < @ $j . >		$#local $: : $1			local address',
E 14
I 14
D 16
ifdef(`NEWSENDMAIL',
`R$+ < @ $j . >		$#local $: : $1			local address',
`R$+ < @ $j . >		$#local $: $1			local address')',
E 14
`# delete local info
R$* < @ $j . > $*	$@ $>7 $1 $2')
E 16
I 16
D 17
R$+ < @ $j . >		$#local $: $O $1		local address
E 16
E 13
E 11

E 17
I 17
D 18
ifdef(`NEWSENDMAIL',
`R$+ < @ $j . >		$#local $: @ $1			local address',
`R$+ < @ $j . >		$#local $: $1			local address')
E 18
I 18
D 134
ifdef(`_OLD_SENDMAIL_',
D 36
`R$+ < @ $j . >		$#local $: $1			local address',
`R$+ < @ $j . >		$#local $: @ $1			local address')
E 36
I 36
D 39
`R$+ < $+ @ $+ >		$#smtp $@ $3 $: $1 < $2 >	yep ....
E 39
I 39
D 70
`R$+ < $+ @ $-:$+ >	$# $3 $@ $4 $: $1 < $2 >	yep ....
D 59
R$+ < $+ @ $+ >		$#smtp $@ $3 $: $1 < $2 >	yep ....
E 59
I 59
R$+ < $+ @ $+ >		$#relay $@ $3 $: $1 < $2 >	yep ....
E 70
I 70
`R$+ < $+ @ $-:$+ >	$# $3 $@ $4 $: $1 $2		yep ....
R$+ < $+ @ $+ >		$#relay $@ $3 $: $1 $2		yep ....
E 70
E 59
E 39
D 92
R$+ < $+ @ >		$#local $: $1			nope, local address',
`R$+ < $+ @ $+ >		$#local $: $1			yep ....
D 53
R$+ < $+ @ >		$#local $: @ $1			nope, local address')
E 53
I 53
R$+ < $+ @ >		$#local $: @ $1			nope, local address')')
E 92
I 92
R$+ < $+ @ >		$#_LOCAL_ $: $1			nope, local address',
`R$+ < $+ @ $+ >		$#_LOCAL_ $: $1			yep ....
R$+ < $+ @ >		$#_LOCAL_ $: @ $1			nope, local address')')
E 134
I 134
R$+ < $+ @ $+ >		$#_LOCAL_ $: $1			yep ....
I 136
R$=D . $+ < $+ @ >	$#_LOCAL_ $: $1 . $2		dotted name?
E 136
R$+ < $+ @ >		$#_LOCAL_ $: @ $1			nope, local address')
E 142
I 142
D 143
R$+ < @ $=w . >		$#_LOCAL_ $: $1			dispose directly')
E 143
I 143
D 144
R$+ + $* < @ $=2 . >	$#_LOCAL_ $@ $2 $: $1		plussed name
E 144
I 144
D 146
R$+ + $* < @ $=w . >	$#_LOCAL_ $@ $2 $: $1		plussed name
E 144
R$+ < @ $=w . >		$#_LOCAL_ $: $1			nonplussed name')
E 146
I 146
R$+ < @ $=w . >		$#_LOCAL_ $: $1			regular local name')
E 146
E 143
E 142
E 134
I 125
ifdef(`MAILER_TABLE',
`
# not local -- try mailer table lookup
R$* <@ $+ > $*		$: < $2 > $1 < @ $2 > $3	extract host name
R< $+ . > $*		$: < $1 > $2			strip trailing dot
R< $+ > $*		$: < $(mailertable $1 $) > $2	lookup
R< $- : $+ > $*		$# $1 $@ $2 $: $3		check -- resolved?
R< $+ > $*		$: $>90 <$1> $2			try domain',
`dnl')
E 125
I 121
ifdef(`MAILER_TABLE',
`
# try mailer table lookup
R$* <@ $+ > $*		$: < $2 > $1 < @ $2 > $3	extract host name
R< $+ . > $*		$: < $1 > $2			strip trailing dot
R< $+ > $*		$: < $(mailertable $1 $) > $2	lookup
R< $- : $+ > $*		$# $1 $@ $2 $: $3		check -- resolved?
R< $+ > $*		$: $>90 <><$1> $2		try domain',
`dnl')

E 121
E 120
I 120
`R$+ < @ $=w . >		$#_LOCAL_ $: $1			dispose directly',
`R$+ < @ $=w . >		$: $>_SET_95_ < $H > $1 < @ $2 . >	sticky local names
R$+ < @ $=w . >		$#_LOCAL_ $: @ $1		sticky local names')
E 120
E 92
E 53
E 36
E 18
E 17
D 87
undivert(3)dnl
E 87
I 87
D 90

# handle local hacks
R$*			$: $>_SET_98_ $1
E 90
E 87
D 17

E 17
I 4
undivert(4)dnl

D 26
# resolve remotely connected UUCP links
E 26
I 26
D 78
# resolve remotely connected UUCP links (if any)
E 78
I 78
ifdef(`_NO_UUCP_', `dnl',
`# resolve remotely connected UUCP links (if any)
E 78
E 26
I 9
D 10
R$* < @ $=V . UUCP > $*		$#smtp $@ $V $: $1<@$2.UUCP>$3
E 9
R$* < @ $=W . UUCP > $*		$#smtp $@ $W $: $1<@$2.UUCP>$3
R$* < @ $=X . UUCP > $*		$#smtp $@ $X $: $1<@$2.UUCP>$3
E 10
I 10
ifdef(`_CLASS_V_',
D 22
`R$* < @ $=V . UUCP > $*		$#smtp $@ $V $: $1<@$2.UUCP>$3', `dnl')
E 22
I 22
D 70
D 87
`R$* < @ $=V . UUCP > $*		$#smtp $@ $V $: <@ $V> : $1 @ $2.UUCP $3',
E 87
I 87
D 93
`R$* < @ $=V . UUCP > $*		$: < $V > <@ $V> : $1 @ $2.UUCP $3
R< $- : $+ > $*			$# $1 $@ $2 $: $3	$=V UUCP routing
D 91
R< $+ > $*			$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*			$#_SMTP_ $@ $1 $: $2
E 91
R<> $*				$: $1			else strip off gunk',
E 93
I 93
D 103
`R$* < @ $=V . UUCP > $*		$: $>_SET_95_ < $V > <@ $V> : $1 @ $2.UUCP $3',
E 103
I 103
D 107
`R$* < @ $=V . UUCP > $*		$: $>_SET_95_ < $V > $1 <@$2.UUCP> $3',
E 107
I 107
D 134
`R$* < @ $=V . UUCP . > $*		$: $>_SET_95_ < $V > $1 <@$2.UUCP.> $3',
E 134
I 134
`R$* < @ $=V . UUCP . > $*		$: $>95 < $V > $1 <@$2.UUCP.> $3',
E 134
E 107
E 103
E 93
E 87
E 70
I 70
`R$* < @ $=V . UUCP > $*		$#smtp $@ $V $: @ $V : $1 @ $2.UUCP $3',
E 70
	`dnl')
E 22
ifdef(`_CLASS_W_',
D 22
`R$* < @ $=W . UUCP > $*		$#smtp $@ $W $: $1<@$2.UUCP>$3', `dnl')
E 22
I 22
D 70
D 87
`R$* < @ $=W . UUCP > $*		$#smtp $@ $W $: <@ $W> : $1 @ $2.UUCP $3',
E 87
I 87
D 93
`R$* < @ $=W . UUCP > $*		$: < $W > <@ $W> : $1 @ $2.UUCP $3
R< $- : $+ > $*			$# $1 $@ $2 $: $3	$=W UUCP routing
D 91
R< $+ > $*			$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*			$#_SMTP_ $@ $1 $: $2
E 91
R<> $*				$: $1			else strip off gunk',
E 93
I 93
D 103
`R$* < @ $=W . UUCP > $*		$: $>_SET_95_ < $W > <@ $W> : $1 @ $2.UUCP $3',
E 103
I 103
D 107
`R$* < @ $=W . UUCP > $*		$: $>_SET_95_ < $W > $1 <@$2.UUCP> $3',
E 107
I 107
D 134
`R$* < @ $=W . UUCP . > $*		$: $>_SET_95_ < $W > $1 <@$2.UUCP.> $3',
E 134
I 134
`R$* < @ $=W . UUCP . > $*		$: $>95 < $W > $1 <@$2.UUCP.> $3',
E 134
E 107
E 103
E 93
E 87
E 70
I 70
`R$* < @ $=W . UUCP > $*		$#smtp $@ $W $: @ $W : $1 @ $2.UUCP $3',
E 70
	`dnl')
E 22
ifdef(`_CLASS_X_',
D 22
`R$* < @ $=X . UUCP > $*		$#smtp $@ $X $: $1<@$2.UUCP>$3', `dnl')
E 22
I 22
D 70
D 87
`R$* < @ $=X . UUCP > $*		$#smtp $@ $X $: <@ $X> : $1 @ $2.UUCP $3',
E 87
I 87
D 93
`R$* < @ $=X . UUCP > $*		$: < $X > <@ $X> : $1 @ $2.UUCP $3
R< $- : $+ > $*			$# $1 $@ $2 $: $3	$=X UUCP routing
D 91
R< $+ > $*			$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*			$#_SMTP_ $@ $1 $: $2
E 91
R<> $*				$: $1			else strip off gunk',
E 93
I 93
D 103
`R$* < @ $=X . UUCP > $*		$: $>_SET_95_ < $X > <@ $X> : $1 @ $2.UUCP $3',
E 103
I 103
D 107
`R$* < @ $=X . UUCP > $*		$: $>_SET_95_ < $X > $1 <@$2.UUCP> $3',
E 107
I 107
D 134
`R$* < @ $=X . UUCP . > $*		$: $>_SET_95_ < $X > $1 <@$2.UUCP.> $3',
E 134
I 134
`R$* < @ $=X . UUCP . > $*		$: $>95 < $X > $1 <@$2.UUCP.> $3',
E 134
E 107
E 103
E 93
E 87
E 70
I 70
`R$* < @ $=X . UUCP > $*		$#smtp $@ $X $: @ $X : $1 @ $2.UUCP $3',
E 70
D 78
	`dnl')
E 78
I 78
	`dnl')')
E 78
E 22
E 10
D 9
R$* < @ $=Y . UUCP > $*		$#smtp $@ $Y $: $1<@$2.UUCP>$3
E 9

E 4
# resolve fake top level domains by forwarding to other hosts
ifdef(`BITNET_RELAY',
D 22
`R$*<@$+.BITNET>$*	$#smtp$@$B$:$1<@$2.BITNET>$3		user@host.BITNET',
E 22
I 22
D 70
D 73
`R$*<@$+.BITNET>$*	$#smtp $@ $B $: $1 <@$2.BITNET> $3	user@host.BITNET',
E 73
I 73
D 78
`R$*<@$+.BITNET>$*	$#smtp $@ $B. $: $1 <@$2.BITNET> $3	user@host.BITNET',
E 78
I 78
D 87
`R$*<@$+.BITNET>$*	$#smtp $@ $B $: $1 <@$2.BITNET> $3	user@host.BITNET',
E 87
I 87
D 93
`R$*<@$+.BITNET>$*	$: < $B > $1 <@$2.BITNET> $3	user@host.BITNET
R< $- : $+ > $*		$# $1 $@ $2 $: $3
D 91
R< $+ > $*		$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*		$#_SMTP_ $@ $1 $: $2
E 91
R<> $*			$: $1				else strip off gunk',
E 93
I 93
D 107
`R$*<@$+.BITNET>$*	$: $>_SET_95_ < $B > $1 <@$2.BITNET> $3	user@host.BITNET',
E 107
I 107
D 134
`R$*<@$+.BITNET.>$*	$: $>_SET_95_ < $B > $1 <@$2.BITNET.> $3	user@host.BITNET',
E 134
I 134
`R$*<@$+.BITNET.>$*	$: $>95 < $B > $1 <@$2.BITNET.> $3	user@host.BITNET',
I 158
	`dnl')
ifdef(`DECNET_RELAY',
`R$*<@$+.DECNET.>$*	$: $>95 < $C > $1 <@$2.DECNET.> $3	user@host.DECNET',
E 158
E 134
E 107
E 93
E 87
E 78
E 73
E 70
I 70
`R$*<@$+.BITNET>$*	$#smtp $@ $B $: $1 @ $2 . BITNET $3	user@host.BITNET',
E 70
E 22
D 111
	`dnl')
ifdef(`CSNET_RELAY',
D 22
`R$*<@$+.CSNET>$*	$#smtp$@$C$:$1<@$2.CSNET>$3		user@host.CSNET',
E 22
I 22
D 70
D 73
`R$*<@$+.CSNET>$*	$#smtp $@ $C $: $1 <@$2.CSNET> $3	user@host.CSNET',
E 73
I 73
D 78
`R$*<@$+.CSNET>$*	$#smtp $@ $C. $: $1 <@$2.CSNET> $3	user@host.CSNET',
E 78
I 78
D 87
`R$*<@$+.CSNET>$*	$#smtp $@ $C $: $1 <@$2.CSNET> $3	user@host.CSNET',
E 87
I 87
D 93
`R$*<@$+.CSNET>$*	$: < $C > $1 <@$2.CSNET> $3	user@host.CSNET
R< $- : $+ > $*		$# $1 $@ $2 $: $3
D 91
R< $+ > $*		$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*		$#_SMTP_ $@ $1 $: $2
E 91
R<> $*			$: $1				else strip off gunk',
E 93
I 93
D 107
`R$*<@$+.CSNET>$*	$: $>_SET_95_ < $C > $1 <@$2.CSNET> $3	user@host.CSNET',
E 107
I 107
`R$*<@$+.CSNET.>$*	$: $>_SET_95_ < $C > $1 <@$2.CSNET.> $3	user@host.CSNET',
E 111
E 107
E 93
E 87
E 78
E 73
E 70
I 70
`R$*<@$+.CSNET>$*	$#smtp $@ $C $: $1 @ $2 . CSNET $3	user@host.CSNET',
E 70
E 22
	`dnl')
I 110
ifdef(`_MAILER_pop_',
`R$+ < @ POP. >		$#pop $: $1			user@POP',
	`dnl')
E 110
I 49
ifdef(`_MAILER_fax_',
D 87
`R$+ < @ $+ .FAX >	$#fax $@ $2 $: $1			user@host.FAX',
E 87
I 87
D 107
`R$+ < @ $+ .FAX >	$#fax $@ $2 $: $1		user@host.FAX',
E 107
I 107
`R$+ < @ $+ .FAX. >	$#fax $@ $2 $: $1		user@host.FAX',
E 107
E 87
`ifdef(`FAX_RELAY',
D 70
D 73
`R$*<@$+.FAX>$*		$#smtp $@ $F $: $1 <@$2.FAX> $3		user@host.FAX',
E 73
I 73
D 78
`R$*<@$+.FAX>$*		$#smtp $@ $F. $: $1 <@$2.FAX> $3	user@host.FAX',
E 78
I 78
D 87
`R$*<@$+.FAX>$*		$#smtp $@ $F $: $1 <@$2.FAX> $3		user@host.FAX',
E 87
I 87
D 93
`R$*<@$+.FAX>$*		$: < $F > $1 <@$2.FAX> $3	user@host.FAX
R< $- : $+ > $*		$# $1 $@ $2 $: $3
D 88
R< $+ > $*		$#smtp $@ $1 $: $2',
E 88
I 88
D 91
R< $+ > $*		$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*		$#_SMTP_ $@ $1 $: $2
E 91
E 88
R<> $*			$: $1				else strip off gunk',
E 93
I 93
D 107
`R$*<@$+.FAX>$*		$: $>_SET_95_ < $F > $1 <@$2.FAX> $3	user@host.FAX',
E 107
I 107
D 134
`R$*<@$+.FAX.>$*		$: $>_SET_95_ < $F > $1 <@$2.FAX.> $3	user@host.FAX',
E 134
I 134
`R$*<@$+.FAX.>$*		$: $>95 < $F > $1 <@$2.FAX.> $3	user@host.FAX',
E 134
E 107
E 93
E 87
E 78
E 73
E 70
I 70
`R$*<@$+.FAX>$*		$#smtp $@ $F $: $1 @ $2 . FAX $3		user@host.FAX',
E 70
	`dnl')')
E 49

D 4
# forward non-local UUCP traffic to our UUCP relay
R$*<@$*.UUCP>$*		$#smtp$@$U$:$1<@$2.UUCP>		uucp mail
E 4
I 4
ifdef(`UUCP_RELAY',
`# forward non-local UUCP traffic to our UUCP relay
D 9
R$*<@$*.UUCP>$*		$#smtp$@$U$:$1<@$2.UUCP>		uucp mail',
E 9
I 9
D 22
R$*<@$*.UUCP>$*		$#smtp$@$Y$:$1<@$2.UUCP>		uucp mail',
E 22
I 22
D 70
D 73
R$*<@$*.UUCP>$*		$#smtp $@ $Y $: <@ $Y> : $1 @ $2.UUCP $3	uucp mail',
E 73
I 73
D 78
R$*<@$*.UUCP>$*		$#smtp $@ $Y. $: <@ $Y> : $1 @ $2.UUCP $3	uucp mail',
E 78
I 78
D 87
R$*<@$*.UUCP>$*		$#smtp $@ $Y $: <@ $Y> : $1 @ $2.UUCP $3	uucp mail',
E 87
I 87
D 93
R$*<@$*.UUCP>$*		$: < $Y > <@ $Y> : $1 @ $2.UUCP $3	uucp mail
R< $- : $+ > $*		$# $1 $@ $2 $: $3
D 88
R< $+ > $*		$#smtp $@ $1 $: $2',
E 88
I 88
D 91
R< $+ > $*		$#smtp $@ $1 $: $2
E 91
I 91
R< $+ > $*		$#_SMTP_ $@ $1 $: $2
E 91
E 88
R<> $*			$: $1				else strip off gunk',
E 93
I 93
D 103
R$*<@$*.UUCP>$*		$: $>_SET_95_ < $Y > <@ $Y> : $1 @ $2.UUCP $3	uucp mail',
E 103
I 103
D 105
R$*<@$*.UUCP>$*		$: $>_SET_95_ < $Y > $1 @ <$2.UUCP> $3	uucp mail',
E 105
I 105
D 107
R$*<@$*.UUCP>$*		$: $>_SET_95_ < $Y > $1 <@$2.UUCP> $3	uucp mail',
E 107
I 107
D 134
R$*<@$*.UUCP.>$*		$: $>_SET_95_ < $Y > $1 <@$2.UUCP.> $3	uucp mail',
E 134
I 134
R$*<@$*.UUCP.>$*		$: $>95 < $Y > $1 <@$2.UUCP.> $3	uucp mail',
E 134
E 107
E 105
E 103
E 93
E 87
E 78
E 73
E 70
I 70
R$*<@$*.UUCP>$*		$#smtp $@ $Y $: @ $Y : $1 @ $2.UUCP $3	uucp mail',
E 70
E 22
E 9
D 26
`ifdef(`_UUCP_LINKED_',
E 26
I 26
`ifdef(`_MAILER_uucp_',
E 26
`# forward other UUCP traffic straight to UUCP
D 70
D 71
R< @ $+ .UUCP > : $+	$#uucp $@ $1 $: $1:$2			@host.UUCP:...
E 71
I 71
D 87
R< @ $+ .UUCP > : $+	$#uucp $@ $1 $: $2			@host.UUCP:...
E 71
E 70
I 70
R< @ $+ .UUCP > : $+	$#uucp $@ $1 $: $2			@host.UUCP:...
E 70
D 13
R$+ < @ $+ .UUCP>	$#uucp $@ $2 $: $1			user@host.UUCP',
E 13
I 13
R$+ < @ $+ .UUCP >	$#uucp $@ $2 $: $1			user@host.UUCP',
E 87
I 87
D 107
R< @ $+ .UUCP > : $+	$#uucp $@ $1 $: $2		@host.UUCP:...
R$+ < @ $+ .UUCP >	$#uucp $@ $2 $: $1		user@host.UUCP',
E 107
I 107
D 113
R< @ $+ .UUCP. > : $+	$#uucp $@ $1 $: $2		@host.UUCP:...
R$+ < @ $+ .UUCP. >	$#uucp $@ $2 $: $1		user@host.UUCP',
E 113
I 113
R$* < @ $+ .UUCP. > $*		$#uucp $@ $2 $: $1 < @ $2 .UUCP. > $3	user@host.UUCP',
E 113
E 107
E 87
E 13
	`dnl')')
E 4
D 88

E 88
I 86
D 90
ifdef(`_MAILER_USENET_', `
E 90
I 90
ifdef(`_MAILER_usenet_', `
E 90
# addresses sent to net.group.USENET will get forwarded to a newsgroup
D 92
R$+ . USENET		$# usenet $: $1',
E 92
I 92
D 107
R$+ . USENET		$#usenet $: $1',
E 107
I 107
D 116
R$+ . USENET.		$#usenet $: $1',
E 116
I 116
R$+ . USENET		$#usenet $: $1',
E 116
E 107
E 92
D 88
`dnl')
E 88
I 88
	`dnl')
E 88

E 86
D 4
# hide behind our internet relay when talking to people in the .ARPA domain
#R$*<@$*.ARPA>$*	$#smtp-nic$@$2.ARPA$:$1<@$2.ARPA>$3	user@host.ARPA

# but speak domains to them if they speak domains too
E 4
I 4
D 26
# deal with other remote names
E 26
I 26
D 39
ifdef(`_MAILER_smtp_',
E 39
I 39
ifdef(`_LOCAL_RULES_',
`# figure out what should stay in our local mail system
D 86
undivert(1)',
`ifdef(`_MAILER_smtp_',
E 39
`# deal with other remote names
E 26
E 4
D 21
R$* < @ $* > $*		$# smtp $@ $2 $: $1 < @ $2 > $3		user@host.domain
E 21
I 21
D 39
R$* < @ $* > $*		$#smtp $@ $2 $: $1 < @ $2 > $3		user@host.domain
I 26
', `dnl')
E 39
I 39
D 70
R$* < @ $* > $*		$#smtp $@ $2 $: $1 < @ $2 > $3		user@host.domain')')
E 86
I 86
undivert(1)', `dnl')

E 86
E 70
I 70
R$* < @ $* > $*		$#smtp $@ $2 $: $1 @ $2 $3		user@host.domain')')
E 70
D 89
ifdef(`SMART_HOST', `
# pass names that still have a host to a smarthost
E 89
I 89
D 99
ifdef(`SMART_HOST',
`# pass names that still have a host to a smarthost
E 99
I 99
# pass names that still have a host to a smarthost (if defined)
E 99
E 89
D 93
R$* < @ $* > $*		$: < $S > $1 < @ $2 > $3	glue on smarthost name
E 93
I 93
D 134
R$* < @ $* > $*		$: $>_SET_95_ < $S > $1 < @ $2 > $3	glue on smarthost name
E 134
I 134
R$* < @ $* > $*		$: $>95 < $S > $1 < @ $2 > $3	glue on smarthost name
E 134
E 93
D 70
D 87
R<$-:$+> $* < @$* > $*	$# $1 $@ $2 $: $3 < @ $4 > $5	if non-null, use it
R<$+> $* < @$* > $*	$#suucp $@ $1 $: $2 < @ $3 > $4	if non-null, use it
E 70
I 70
R<$-:$+> $* < @$* > $*	$# $1 $@ $2 $: $3 @ $4 $5	if non-null, use it
R<$+> $* < @$* > $*	$#suucp $@ $1 $: $2 @ $3 $4	if non-null, use it
E 70
R<> $* < @ $* > $*	$1 < @ $2 > $3			else strip off gunk',
E 87
I 87
D 99
R< $- : $+ > $*		$# $1 $@ $2 $: $3		if non-null, use it
R< $+ > $*		$#suucp $@ $1 $: $2		if non-null, use it
R<> $*			$: $1				else strip off gunk',
E 99
E 87
I 86

E 86
D 89
`ifdef(`_LOCAL_RULES_', `
# reject messages that have host names we do not understand
R$* < @ $* > $*		$#error $@ NOHOST $: Unrecognized host name $2',
D 86
`dnl')')
I 40
ifdef(`_MAILER_USENET_', `
# addresses sent to net.group.USENET will get forwarded to a newsgroup
D 41
R$+ . USENET		$# usenet $@ $1 $: $1
E 41
I 41
R$+ . USENET		$# usenet $: $1')
E 86
I 86
`ifdef(`_MAILER_smtp_',
E 89
D 99
`# deal with other remote names
E 99
I 99
# deal with other remote names
E 99
D 89
R$* < @ $* > $*		$#smtp $@ $2 $: $1 < @ $2 > $3		user@host.domain')')')
E 89
I 89
ifdef(`_MAILER_smtp_',
D 91
`R$* < @$* > $*		$#smtp $@ $2 $: $1 < @ $2 > $3		user@host.domain',
E 91
I 91
`R$* < @$* > $*		$#_SMTP_ $@ $2 $: $1 < @ $2 > $3		user@host.domain',
E 91
D 99
`R$* < @$* > $*		$#error $@NOHOST $: Unrecognized host name $2')')
E 99
I 99
D 155
`R$* < @$* > $*		$#error $@NOHOST $: Unrecognized host name $2')
E 155
I 155
`R$* < @$* > $*		$#error $@ 5.1.2 $: Unrecognized host name $2')
E 155
E 99
E 89
E 86
E 41
E 40
E 39
E 26
E 21

D 13
# see if we forward local names
R$=L			$# local $: $1			special local names
I 12
`R:include:$+		$# local $: :include: $1	included lists'
R|$+			$# local $: |$1			pipes to programs
R/$+			$# local $: /$1			and files
E 12
R$+			$: $1 @ $R
R$+ @			$: $1				no, we don't
R$+ @ $+		$# smtp $@ $2 $: $1		yes, we do
E 13
I 13
D 18
ifdef(`NEWSENDMAIL',
`# handle locally delivered names
D 16
ifdef(`LOCAL_RELAY',
`R$=L			$# local $: : $1		special local names',
	`dnl')
E 16
I 16
D 17
R$=L			$# local $: $O $1		special local names
E 17
I 17
R$=L			$# local $: @ $1		special local names
E 17
E 16
R$+			$# local $: $1			regular local names
D 16
', `ifdef(`LOCAL_RELAY',
`# forward remaining names to local relay
R$+			$# smtp $@ $R $: $1 @ $R',
`# remaining names must be local
R$+			$# local $: $1')')
E 16
I 16
',
E 18
I 18
D 134
ifdef(`_OLD_SENDMAIL_',
E 18
`# forward remaining names to local relay, if any
D 21
R$+			$: $1 < @ $R >
R$+ < @ >		$# local $: $1
D 18
R$+ < @ $+ >		$# smtp $@ $2 $: $1')
E 18
I 18
R$+ < @ $+ >		$# smtp $@ $2 $: $1',
E 21
I 21
D 92
R$=L			$#local $: $1			special local names
E 92
I 92
R$=L			$#_LOCAL_ $: $1			special local names
E 92
D 93
R$+			$: $1 < @ $R >			append relay
D 36
R$+ < @ >		$#local $: $1			if no relay, local
D 22
R$+ < @ $+ >		$#smtp $@ $2 $: $1',		deliver to relay
E 22
I 22
R$+ < @ $+ >		$#smtp $@ $2 $: $1		deliver to relay',
E 36
I 36
R$+ < @ >		$: $1 < @ $H >			no relay, try hub
D 92
R$+ < @ >		$#local $: $1			no relay or hub: local
D 76
R$+ < @ $j  >		$#local $: $1			we are relay/hub: local
E 76
I 76
R$+ < @ $=w  >		$#local $: $1			we are relay/hub: local
E 92
I 92
R$+ < @ >		$#_LOCAL_ $: $1			no relay or hub: local
R$+ < @ $=w  >		$#_LOCAL_ $: $1			we are relay/hub: local
E 92
E 76
I 39
R$+ < @ $-:$+ >		$# $2 $@ $3 $: $1		deliver to relay/hub
E 39
D 59
R$+ < @ $+ >		$#smtp $@ $2 $: $1		deliver to relay/hub',
E 59
I 59
R$+ < @ $+ >		$#relay $@ $2 $: $1		deliver to relay/hub',
E 93
I 93
R$+			$: $>_SET_95_ < $R > $1			try relay
R$+			$: $>_SET_95_ < $H > $1			try hub
R$+			$#_LOCAL_ $: $1			no relay or hub: local',
E 93
E 59
E 36
E 22
E 21
D 62
`# handle locally delivered names
E 62
I 62

`# if this is quoted, strip the quotes and try again
E 134
I 134
# if this is quoted, strip the quotes and try again
E 134
R$+			$: $(dequote $1 $)		strip quotes
D 76
R$* $=O $*		$@ $>7 $1 $2 $3			try again
E 76
I 76
D 101
R$* $=O $*		$@ $>_SET_97_ $1 $2 $3			try again
E 101
I 101
D 134
R$+ $=O $+		$@ $>_SET_97_ $1 $2 $3			try again
E 134
I 134
R$+ $=O $+		$@ $>97 $1 $2 $3			try again
E 134
E 101
E 76

# handle locally delivered names
I 120
R$=L			$: $>_SET_95_ < $H > $1		special local names
E 120
E 62
D 21
R$=L			$# local $: @ $1		special local names
R$+			$# local $: $1			regular local names')
E 21
I 21
D 92
R$=L			$#local $: @ $1			special local names
R$+			$#local $: $1			regular local names
E 92
I 92
R$=L			$#_LOCAL_ $: @ $1			special local names
I 143
D 145
R$+ + $*		$#_LOCAL_ $@ $2 $: $1		plussed local names
E 145
E 143
R$+			$#_LOCAL_ $: $1			regular local names
E 92
E 21
E 18
E 16
E 13

D 13
# remaining names must be local
R$+			$#local$:$1			everything else
E 13
I 13
D 16
ifdef(`LOCAL_RELAY', `ifdef(`NEWSENDMAIL',
E 16
I 16
D 18
ifdef(`NEWSENDMAIL',
E 18
I 18
D 21
ifdef(`_OLD_SENDMAIL_', `dnl',
E 18
E 16
`#
E 21
I 21
D 26
#
E 21
# special rewriting after aliases have been expanded
#
E 26
I 26
###########################################################################
###   Ruleset 5 -- special rewriting after aliases have been expanded   ###
D 145
###		   (new sendmail only)					###
E 145
###########################################################################
E 26
E 13

I 13
S5
I 135

D 157
# if we have a "special dotted user", convert it back to the base name
R$=D . *		$#_LOCAL_ $: $1
R$=D . $+		$#_LOCAL_ $: $1 . *
E 157
I 157
# deal with plussed users so aliases work nicely
R$+ + *			$#_LOCAL_ $@ $&h $: $1
R$+ + $*		$#_LOCAL_ $@ $2 $: $1 + *
E 157
E 135
D 62

D 16
R$+			$# smtp $@ $R $: $1 < @ $R >	send to relay')')
E 16
I 16
D 26
R$+			$: $1 < @ $R >
D 21
R$+ < @ $+ >		$# smtp $@ $2 $: $1		send to relay')
E 21
I 21
D 25
R$+ < @ $+ >		$#smtp $@ $2 $: $1		send to relay')
E 25
I 25
R$+ < @ $+ >		$#smtp $@ $2 $: $1 < @ $2 >	send to relay')
E 26
I 26
D 61
ifdef(`_MAILER_smtp_',
`R$+			$: $1 < @ $R >
E 61
I 61
# if this is quoted, strip the quotes and try again
R$+.			$1				strip trailing dots
R$+			$: $(dequote $1 $)		strip quotes
R$* $=O $*		$>7 $1 $2 $3			try again
E 62

I 142
# prepend an empty "forward host" on the front
R$+			$: <> $1

ifdef(`LUSER_RELAY',
`# send unrecognized local users to a relay host
D 145
R< > $+			$: < $L > $( user $1 $)		look up user
R< $* > $+ <>		$: <> $2			found; strip $L')
E 145
I 145
R< > $+ + $*		$: < $L . > $( user $1 $) + $2
R< > $+			$: < $L . > $( user $1 $)	look up user
R< $* > $+ <> $*	$: < > $2 $3			found; strip $L
R< $* . > $+		$: < $1 > $2			strip extra dot')
E 145

I 145
# handle plussed local names
R< > $+ + $*		$#_LOCAL_ $@ $2 $: $1

E 145
E 142
# see if we have a relay or a hub
D 93
R$+			$: $1 < @ $R >
E 61
D 27
R$+ < @ $+ >		$#smtp $@ $2 $: $1 < @ $2 >	send to relay')',
`dnl')
E 27
I 27
D 36
R$+ < @ $+ >		$#smtp $@ $2 $: $1 < @ $2 >	send to relay')')
E 36
I 36
R$+ < @ >		$: $1 < @ $H >			no relay, try hub
D 76
R$+ < @ $j >		$@ $1				we are relay/hub: local
E 76
I 76
R$+ < @ $=w >		$@ $1				we are relay/hub: local
E 76
I 39
R$+ < @ $-:$+ >		$# $2 $@ $3 $: $1		send to relay or hub
E 39
D 59
R$+ < @ $+ >		$#smtp $@ $2 $: $1		send to relay or hub')')
E 59
I 59
D 61
R$+ < @ $+ >		$#relay $@ $2 $: $1		send to relay or hub')')
E 61
I 61
ifdef(`_MAILER_smtp_',
`R$+ < @ $+ >		$#relay $@ $2 $: $1		send to relay or hub')')
E 93
I 93
D 117
R$+			$: $>_SET_95_ < $R > $1			try relay
R$+			$: $>_SET_95_ < $H > $1			try hub')
E 117
I 117
D 120
D 142
R$+			$: < $R > $1			try relay
E 142
I 142
D 149
R< > $+			$: < $R > $1			try relay
E 149
E 142
R< > $+			$: < $H > $1			try hub
I 149
R< > $+			$: < $R > $1			try relay
E 149
R< > $+			$@ $1				nope, give up
D 134
R< $- : $+ > $+		$: $>_SET_95_ < $1 : $2 > $3 < @ $2 >
R< $+ > $+		$@ $>_SET_95_ < $1 > $2 < @ $1 >')
E 134
I 134
R< $- : $+ > $+		$: $>95 < $1 : $2 > $3 < @ $2 >
R< $+ > $+		$@ $>95 < $1 > $2 < @ $1 >
E 134
E 120
I 120
R$+			$: $>_SET_95_ < $R > $1		try relay
R$+			$: $>_SET_95_ < $H > $1		try hub')
E 120
E 117
E 93
I 75
ifdef(`MAILER_TABLE',
`

D 87
###########################################################################
###  Ruleset 90 -- try domain part of mailertable entry 		###
###		   (new sendmail only)					###
###########################################################################
E 87
I 87
###################################################################
###  Ruleset 90 -- try domain part of mailertable entry 	###
D 145
###		   (new sendmail only)				###
E 145
###################################################################
E 87

S90
D 77
R<$- . $+ > $*		$: < $(mailertable .$2 $: $) > $3	lookup
E 77
I 77
D 93
R<$- . $+ > $*		$: < $(mailertable .$2 $) > $3	lookup
E 93
I 93
D 121
D 123
R<$- . $+ > $*		$: < $(mailertable .$2 $@ $1 $) > $3	lookup
E 93
E 77
R<$- : $+ > $*		$# $1 $@ $2 $: $3		check -- resolved?
D 76
R<$- . $+ > $*		$@ $>99 <$2> $3			no -- strip & try again
E 76
I 76
D 80
R<$- . $+ > $*		$@ $>90 <$2> $3			no -- strip & try again
E 80
I 80
R< . $+ > $*		$@ $>90 <$1> $2			no -- strip & try again
E 80
E 76
R<$*> $*		$@ $2				no match',
E 123
I 123
D 126
R$* <$- . $+ > $*	$: $1$2 < $(mailertable .$3 $@ $1$2 $) > $4	lookup
E 126
I 126
R$* <$- . $+ > $*	$: $1$2 < $(mailertable .$3 $@ $1$2 $@ $2 $) > $4
E 126
R$* <$- : $+ > $*	$# $2 $@ $3 $: $4		check -- resolved?
R$* < . $+ > $*		$@ $>90 $1 . <$2> $3		no -- strip & try again
D 125
R$* < $* > $*		$@ $3				no match',
E 125
I 125
D 127
R$* < . > $*		$: < $(mailertable . $@ $1 $) > $2	try "."
E 127
I 127
R$* < $* > $*		$: < $(mailertable . $@ $1$2 $) > $3	try "."
E 127
R<$- : $+ > $*		$# $1 $@ $2 $: $3		"." found?
R< $* > $*		$@ $2				no mailertable match',
E 125
E 123
E 121
I 121
R<$*> <$- $+ > $*	$: < $1 . $2 > < $3 > $4
R<. $+ > $+		$: < $1 > $2
R< $+ > < > $+		$: < $1 > < . > $2
R<$*> < $+ > $*		$: <$1> < $(mailertable $2 $@ $1 $) > $3	lookup
R<$+> <$- : $+ > $*	$# $2 $@ $3 $: $4		check -- resolved?
R$*			$: $>87 $1
R<$+> < . $+ > $*<$*>	$@ $>90 <$1> <$2> $3<$4>	no -- strip & try again
R$*			$: $>88 $1
R<$+> <$*> $*		$@ $3				no match',
E 121
`dnl')
I 93

###################################################################
D 134
###  Ruleset _SET_95_ -- canonify mailer:host syntax to triple	###
E 134
I 134
###  Ruleset 95 -- canonify mailer:host syntax to triple	###
E 134
###################################################################

D 134
S`'_SET_95_
E 134
I 134
S95
E 134
R< > $*			$@ $1				strip off null relay
R< $- : $+ > $*		$# $1 $@ $2 $: $3		try qualified mailer
R< $=w > $*		$@ $2				delete local host
R< $+ > $*		$#_RELAY_ $@ $1 $: $2		use unqualified mailer
E 93
I 87

###################################################################
D 134
###  Ruleset _SET_98_ -- local part of ruleset zero (can be null)	###
E 134
I 134
###  Ruleset 98 -- local part of ruleset zero (can be null)	###
E 134
###################################################################

D 134
S`'_SET_98_
E 134
I 134
S98
E 134
undivert(3)dnl
E 87
E 75
E 61
E 59
E 36
E 27
E 26
E 25
E 21
E 16
E 13
#
######################################################################
######################################################################
#####
D 27
#####			MAILER DEFINITIONS
E 27
I 27
D 32
#####			`MAILER DEFINITIONS'
E 32
I 32
`#####			MAILER DEFINITIONS'
E 32
E 27
#####
######################################################################
######################################################################
D 17

E 17
undivert(7)dnl
E 1
