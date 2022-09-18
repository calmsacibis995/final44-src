h30146
s 00037/00000/00000
d D 5.1 90/06/17 17:27:24 bostic 1 0
c date and time created 90/06/17 17:27:24 by bostic
e
u
U
t
T
I 1
c
c     comment section
c
c     fs057
c
c          this subroutine is called by the main program fm056.  the
c     single argument passed from fm056 along with a second parameter
c     created in fs057 are then passed via a call to subroutine fs058.
c     a result from an arithmetic operation is returned from fs058 in
c     the first argument.  fs057 accepts this result and returns control
c     to fm056 without any additional processing.
c
c          the values of the arguments that are passed from fm056 to
c     fs057 and returned are saved in an integer array for later
c     verification by the main program.
c
c      references
c        american national standard programming language fortran,
c              x3.9-1978
c
c        section 15.6, subroutines
c        section 15.6.2, subroutine reference
c        section 15.8, return statement
c
c     test section
c
c         subroutine subprogram
c
      subroutine fs057 (ivon01)
      common iacn11 (12)
      iacn11 (1) = ivon01
      ivon02 = 4
      iacn11 (2) = ivon02
      call fs058 (ivon01,ivon02)
      iacn11 (11) = ivon01
      return
      end
E 1
