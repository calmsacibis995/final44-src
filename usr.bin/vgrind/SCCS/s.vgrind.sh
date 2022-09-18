h61922
s 00002/00002/00115
d D 8.1 93/06/06 22:20:37 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/00115
d D 5.9 92/09/15 11:07:58 elan 17 16
c Added SCCS keywords.
e
s 00032/00006/00111
d D 5.8 92/09/01 12:09:20 elan 16 15
c vtroff = psroff
e
s 00002/00011/00115
d D 5.7 91/04/16 16:53:00 bostic 15 14
c new copyright; att/bsd/shared
e
s 00001/00001/00125
d D 5.6 89/05/01 15:14:43 mckusick 14 13
c correct pathname for the macros
e
s 00012/00013/00114
d D 5.5 89/05/01 08:39:26 bostic 13 12
c file system reorganization; pathnames.h
e
s 00015/00006/00112
d D 5.4 88/10/25 19:38:57 bostic 12 11
c written by Bill Joy; Berkeley specific copyright
e
s 00001/00001/00117
d D 5.3 85/11/13 03:56:17 lepreau 11 10
c csh gets -f flag
e
s 00001/00001/00117
d D 5.2 85/07/22 18:50:33 bloom 10 9
c why was the shell changed?
e
s 00006/00002/00112
d D 5.1 85/06/06 09:28:10 dist 9 8
c Add copyright
e
s 00006/00001/00108
d D 1.8 82/10/21 22:31:39 mckusick 8 7
c allow slashes in file names
e
s 00091/00036/00018
d D 1.7 81/03/29 01:23:18 presott 7 6
c The macro dfinition names have been changed to not interfere
c with other macro packages for troff.
e
s 00001/00001/00053
d D 1.6 81/03/15 17:09:33 presott 6 5
c Because I fucked the last one up
e
s 00014/00007/00040
d D 1.5 81/03/15 17:06:21 presott 5 4
c fixed the -f stuff
e
s 00004/00002/00043
d D 1.4 81/03/15 16:24:13 presott 4 3
c do the -f stuff correctly
e
s 00009/00003/00036
d D 1.3 81/03/15 16:08:43 presott 3 2
c know about the -f stuff
e
s 00000/00000/00039
d D 1.2 81/01/20 00:54:27 root 2 1
c a new table driven vgrind -- presotto
e
s 00039/00000/00000
d D 1.1 80/11/30 15:56:46 root 1 0
c date and time created 80/11/30 15:56:46 by root
e
u
U
t
T
I 8
D 9
#! /bin/csh
E 9
I 9
D 10
#!/bin/sh -
E 10
I 10
D 11
#! /bin/csh
E 11
I 11
D 12
#! /bin/csh -f
E 12
I 12
#!/bin/csh -f
E 12
E 11
E 10
E 9
E 8
I 1
#
I 8
D 9
#	%W%	(Berkeley)	%G%
E 9
I 9
D 12
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 12
I 12
D 18
# Copyright (c) 1980 The Regents of the University of California.
# All rights reserved.
E 18
I 18
# Copyright (c) 1980, 1993
#	The Regents of the University of California.  All rights reserved.
E 18
E 12
#
D 12
#	%W% (Berkeley) %G%
E 12
I 12
D 15
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 15
I 15
D 16
# %sccs.include.redist.sh%
E 16
I 16
D 17
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#	This product includes software developed by the University of
#	California, Berkeley and its contributors.
# 4. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
E 17
I 17
# %sccs.include.redist.sh%
E 17
E 16
E 15
E 12
E 9
#
E 8
D 12
# vgrind
E 12
I 12
D 16
#	%W% (Berkeley) %G%
E 16
I 16
D 17
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
E 16
E 12
#
I 16
#	@(#)vgrind.sh	5.8 (Berkeley) 8/3/92
E 17
I 17
#       %W% (Berkeley) %G%
E 17
#
E 16
I 15

E 15
D 5
set b=/usr/lib
E 5
I 5
D 6
set b=.
E 6
I 6
D 13
set b=/usr/lib
E 13
E 6
E 5
D 7
set o=
set t=
E 7
I 7
set voptions=
set options=
set files=
E 7
I 5
set f=''
E 5
D 7
set wide = ""
E 7
I 7
set head=""
I 13
set vf=/usr/libexec/vfontedpr
D 14
set tm=/usr/share/lib/tmac
E 14
I 14
set tm=/usr/share/tmac
E 14
E 13
E 7
top:
D 7
if ($#argv > 1) then
	switch ($1:q)
E 7
I 7
if ($#argv > 0) then
    switch ($1:q)
E 7

I 5
D 7
	case -f:
		set f='filter'
		shift
		goto top
E 7
I 7
    case -f:
	set f='filter'
	set options = "$options $1:q"
	shift
	goto top
E 7

E 5
D 7
	case -t:
		set t=-t
		shift
		goto top
E 7
I 7
    case -t:
	set voptions = "$voptions -t"
	shift
	goto top
E 7

D 7
	case -o*:
		set o=$1:q
		shift
		goto top
E 7
I 7
    case -o*:
	set voptions="$voptions $1:q"
	shift
	goto top
E 7
I 5

E 5
D 7
	case -W:
		set wide = "-W"
		shift
		goto top
	endsw
E 7
I 7
    case -W:
	set voptions = "$voptions -W"
	shift
	goto top

    case -d:
	if ($#argv < 2) then
	    echo "vgrind: $1:q option must have argument"
	    goto done
	else
	    set options = ($options $1:q $2)
	    shift
	    shift
	    goto top
	endif
			
    case -h:
	if ($#argv < 2) then
	    echo "vgrind: $1:q option must have argument"
	    goto done
	else
	    set head="$2"
	    shift
	    shift
	    goto top
	endif
			
    case -*:
	set options = "$options $1:q"
	shift
	goto top

    default:
	set files = "$files $1:q"
	shift
	goto top
    endsw
E 7
endif
if (-r index) then
D 7
	echo > nindex
	foreach i ($*:q)
		echo "/ $i /d" >> nindex
	end
	sed -f nindex index >xindex
D 3
	$b/vfontedpr $*:q | \
		/bin/sh -c "vtroff $t $wide -rx1 $o -i -mvgrind 2>> xindex"
E 3
I 3
D 5
	if (f == "-f") then
E 5
I 5
	if ($f == 'filter') then
	    $b/vfontedpr -f $*:q | cat /usr/lib/tmac/tmac.vgrind -
E 7
I 7
    echo > nindex
    foreach i ($files)
D 8
	echo "/ $i /d" >> nindex
E 8
I 8
	#	make up a sed delete command for filenames
	#	being careful about slashes.
	echo "? $i ?d" | sed -e "s:/:\\/:g" -e "s:?:/:g" >> nindex
E 8
    end
    sed -f nindex index >xindex
    if ($f == 'filter') then
	if ("$head" != "") then
D 13
	    $b/vfontedpr $options -h "$head" $files | cat $b/tmac/tmac.vgrind -
E 13
I 13
	    $vf $options -h "$head" $files | cat $tm/tmac.vgrind -
E 13
E 7
	else
E 5
D 7
	    $b/vfontedpr $*:q | \
		    /bin/sh -c "vtroff $t $wide -rx1 $o -i -mvgrind 2>> xindex"
E 7
I 7
D 13
	    $b/vfontedpr $options $files | cat $b/tmac/tmac.vgrind -
E 13
I 13
	    $vf $options $files | cat $tm/tmac.vgrind -
E 13
E 7
D 5
	else
D 4
	    $b/vfontedpr $*:q
E 4
I 4
	    $b/vfontedpr $*:q | cat /usr/lib/tmac/tmac.vgrind -
E 5
	endif
E 4
E 3
D 7
	sort -df +0 -2 xindex >index
	rm nindex xindex
E 7
I 7
    else
	if ("$head" != "") then
D 13
	    $b/vfontedpr $options -h "$head" $files | \
		/bin/sh -c "vtroff -rx1 $voptions -i -mvgrind 2>> xindex"
E 13
I 13
	    $vf $options -h "$head" $files | \
D 16
		sh -c "vtroff -rx1 $voptions -i -mvgrind 2>> xindex"
E 16
I 16
		sh -c "psroff -rx1 $voptions -i -mvgrind 2>> xindex"
E 16
E 13
	else
D 13
	    $b/vfontedpr $options $files | \
		/bin/sh -c "vtroff -rx1 $voptions -i -mvgrind 2>> xindex"
E 13
I 13
	    $vf $options $files | \
D 16
		sh -c "vtroff -rx1 $voptions -i -mvgrind 2>> xindex"
E 16
I 16
		sh -c "psroff -rx1 $voptions -i -mvgrind 2>> xindex"
E 16
E 13
	endif
    endif
    sort -df +0 -2 xindex >index
    rm nindex xindex
E 7
else
D 3
	$b/vfontedpr $*:q | vtroff $t $wide -i $o -mvgrind
E 3
I 3
D 5
	if (f == "-f") then
	    $b/vfontedpr $*:q | vtroff $t $wide -i $o -mvgrind
E 5
I 5
D 7
	if ($f == 'filter') then
	    $b/vfontedpr -f $*:q | cat /usr/lib/tmac/tmac.vgrind -
E 7
I 7
    if ($f == 'filter') then
	if ("$head" != "") then
D 13
	    $b/vfontedpr $options -h "$head" $files | cat $b/tmac/tmac.vgrind -
E 13
I 13
	    $vf $options -h "$head" $files | cat $tm/tmac.vgrind -
E 13
E 7
E 5
	else
D 4
	    $b/vfontedpr $*:q
E 4
I 4
D 5
	    $b/vfontedpr $*:q | cat /usr/lib/tmac/tmac.vgrind -
E 5
I 5
D 7
	    $b/vfontedpr $*:q | vtroff $t $wide -i $o -mvgrind
E 7
I 7
D 13
	    $b/vfontedpr $options $files | cat $b/tmac/tmac.vgrind -
E 13
I 13
	    $vf $options $files | cat $tm/tmac.vgrind -
E 13
E 7
E 5
	endif
I 7
    else
	if ("$head" != "") then
D 13
	    $b/vfontedpr $options -h "$head" $files \
		| vtroff -i $voptions -mvgrind
E 13
I 13
D 16
	    $vf $options -h "$head" $files | vtroff -i $voptions -mvgrind
E 16
I 16
	    $vf $options -h "$head" $files | psroff -i $voptions -mvgrind
E 16
E 13
	else
D 13
	    $b/vfontedpr $options $files \
		| vtroff -i $voptions -mvgrind
E 13
I 13
D 16
	    $vf $options $files | vtroff -i $voptions -mvgrind
E 16
I 16
	    $vf $options $files | psroff -i $voptions -mvgrind
E 16
E 13
	endif
    endif
E 7
E 4
E 3
endif
I 7

done:
E 7
E 1
