h38051
s 00000/00000/00008
d D 8.1 93/06/06 22:16:00 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00000/00000
d D 5.1 91/04/24 17:51:35 bostic 1 0
c date and time created 91/04/24 17:51:35 by bostic
e
u
U
t
T
I 1
$! Command file to clean up the EUNICE directories
$! submitted nightly off the clock
$ assign DONOTPRINT SYS$PRINT
$ set prot=(g:rwed,w:rwed)/def
$ purge sys$manager:uucpclean.log
$ delete/before=2 tmp:*.*.*		! should be done elsewhere
$ sh := $bin:sh sh
$ sh /usr/lib/uucp/uucpclean.sh
E 1
