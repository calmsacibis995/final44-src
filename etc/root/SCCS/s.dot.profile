h41441
s 00004/00001/00011
d D 8.5 94/03/26 05:57:31 bostic 8 7
c remove '.' from the path
c export TERM for single user shells
c From: Mike Karels <karels@BSDI.COM>
e
s 00000/00001/00012
d D 8.4 94/03/19 10:24:09 bostic 7 6
c TERM is put into the environment by login
e
s 00000/00003/00013
d D 8.3 94/03/19 10:22:21 bostic 6 5
c login sets HOME, don't bother here
e
s 00011/00003/00005
d D 8.2 94/03/17 06:31:34 bostic 5 4
c cleanup pass
e
s 00000/00000/00008
d D 8.1 93/06/09 12:56:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00007
d D 5.3 92/04/02 14:15:06 bostic 3 2
c dot shouldn't be in root's path at all
e
s 00003/00002/00005
d D 5.2 92/03/21 11:16:53 bostic 2 1
c root logins should always start with a umask of 022
e
s 00007/00000/00000
d D 5.1 90/06/25 11:43:06 bostic 1 0
c date and time created 90/06/25 11:43:06 by bostic
e
u
U
t
T
I 1
D 3
PATH=/sbin:/usr/sbin:/bin:/usr/bin:/usr/local:/usr/contrib:.
E 3
I 3
D 8
PATH=/sbin:/usr/sbin:/bin:/usr/bin:
E 8
I 8
PATH=/sbin:/usr/sbin:/bin:/usr/bin
E 8
E 3
D 5
echo 'erase ^?, kill ^U, intr ^C'
stty crt erase  kill  intr 
E 5
export PATH
I 5

BLOCKSIZE=1k
export BLOCKSIZE
I 8

#export TERM for single user shells.
export TERM
E 8

E 5
D 6
HOME=/root
D 2
export HOME
export TERM
E 2
I 2
D 5
export HOME TERM
E 5
I 5
export HOME
E 5

E 6
I 5
D 7
export TERM
E 7
echo 'erase ^H, kill ^U, intr ^C status ^T'
stty erase '^H' kill '^U' intr '^C' status '^T' crt

E 5
umask 022
I 5

echo "Don't login as root, use the su command."
E 5
E 2
E 1
