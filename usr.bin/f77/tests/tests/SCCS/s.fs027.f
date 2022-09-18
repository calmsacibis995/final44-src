h58083
s 00028/00000/00000
d D 5.1 90/06/17 17:27:09 bostic 1 0
c date and time created 90/06/17 17:27:09 by bostic
e
u
U
t
T
I 1
      subroutine fs027(ivon01)
c     comment section
c
c     fs027
c
c         this subroutine is called by the main program fm026.  the
c     subroutine argument is incremented by 1 and control returned
c     to the calling program.
c
c      references
c        american national standard programming language fortran,
c              x3.9-1978
c
c        section 15.6, subroutines
c        section 15.8, return statement
c
c     test section
c
c         subroutine subprogram
c
c     increment argument by 1 and return to calling program.
c
      ivon02 = ivon01
      ivon02 = ivon02 + 1
      ivon01 = ivon02
      ivon02 = 300
      return
      end
E 1
