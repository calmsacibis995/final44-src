h58620
s 00000/00001/00009
d D 8.4 94/03/19 10:22:21 bostic 5 4
c login sets HOME, don't bother here
e
s 00003/00002/00007
d D 8.3 94/03/17 06:55:17 bostic 4 3
c do the full stty, get status set
e
s 00009/00004/00000
d D 8.2 94/03/17 06:31:33 bostic 3 2
c cleanup pass
e
s 00000/00000/00004
d D 8.1 93/06/09 12:56:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00000/00000
d D 5.1 90/06/25 11:43:02 bostic 1 0
c date and time created 90/06/25 11:43:02 by bostic
e
u
U
t
T
I 1
D 3
tset -Q \?$TERM
stty crt erase ^H
umask 2
echo "Don't login as root, use su"
E 3
I 3
setenv BLOCKSIZE 1k
D 5
setenv HOME ~root
E 5

D 4
stty erase ^H crt 
tset \?$TERM
E 4
I 4
tset -Q \?$TERM
echo 'erase ^H, kill ^U, intr ^C status ^T'
stty erase '^H' kill '^U' intr '^C' status '^T' crt
E 4

umask 022

echo "Don't login as root, use the su command."
E 3
E 1
