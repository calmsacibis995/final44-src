h63903
s 00027/00000/00000
d D 5.1 90/06/17 17:27:13 bostic 1 0
c date and time created 90/06/17 17:27:13 by bostic
e
u
U
t
T
I 1
c
c     comment section
c
c     fs051
c
c          fs051 is a subroutine subprogram which is called by the main
c     program fm050.  no arguments are specified therefore all
c     parameters are passed via unlabeled common.  the subroutine fs051
c     increments the value of a real variable by 1 and returns control
c     to the calling program fm050.
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
c         subroutine subprogram - no arguments
c
      subroutine fs051
      common //rvcn01
      rvcn01 = rvcn01 + 1.0
      return
      end
E 1
