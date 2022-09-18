h18152
s 00035/00000/00000
d D 5.1 90/06/17 17:27:29 bostic 1 0
c date and time created 90/06/17 17:27:29 by bostic
e
u
U
t
T
I 1
      integer function ff081 (idon01, iddn10, iddn20, idon02)
c
c     comment section
c
c     ff081
c
c         this function subprogram is called by the main program fm080.
c     the function dummy arguments idon01, iddn10 and iddn20 are
c     incremented by 2, 40 and 70 respectively before control is
c     returned to the calling program.  value of the function will be
c     the sum of the actual arguments as passed from calling program.
c
c      references
c        american national standard programming language fortran,
c              x3.9-1978
c
c        section 15.5.1, function subprogram and function statement
c
c     test section
c
c         function subprogram
c
      dimension  iddn10 (5),   iddn20 (4,4)
      ivon01 = idon01
      ivon02 = iddn10(2)
      ivon03 = iddn20(1,3)
      ivon04 = idon02
c
      ff081  = ivon01 + ivon02 + ivon03 + ivon04
      idon01 = ivon01 + 2
      iddn10 (2) = ivon02   + 40
      iddn20 (1,3) = ivon03 + 70
      iddn10 (4) = ivon02 + 40
      return
      end
E 1
