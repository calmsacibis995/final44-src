h59724
s 00000/00000/00021
d D 8.1 93/06/09 12:54:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00000/00000
d D 5.1 90/06/30 23:28:28 bostic 1 0
c date and time created 90/06/30 23:28:28 by bostic
e
u
U
t
T
I 1
;	%W% (Berkeley) %G%

; boot file for secondary name server
; Note that there should be one primary entry for each SOA record.

sortlist 128.3.0.0

directory	/etc/namedb

; type    domain		source host/file		backup file

cache     .							root.cache
primary   0.0.127.IN-ADDR.ARPA	localhost.rev

; example secondary server config:
; secondary Berkeley.EDU	128.32.130.11 128.32.133.1	ucbhosts.bak
; secondary 32.128.IN-ADDR.ARPA	128.32.130.11 128.32.133.1	ucbhosts.rev.bak

; example primary server config:
; primary  Berkeley.EDU		ucbhosts
; primary  32.128.IN-ADDR.ARPA	ucbhosts.rev
E 1
