h62522
s 00028/00000/00000
d D 5.1 90/06/17 17:27:11 bostic 1 0
c date and time created 90/06/17 17:27:11 by bostic
e
u
U
t
T
I 1
      integer function ff029(ivon01)
c
c     comment section
c     ff029
c
c         this function subprogram is called by the main program fm028.
c     the function argument is incremented by 1 and control returned
c     to the calling program.
c
c      references
c        american national standard programming language fortran,
c              x3.9-1978
c
c        section 15.5.1, defining function subprograms and function
c                        statements
c        section 15.8, return statement
c
c     test section
c
c          function subprogram
c
c     increment argument by 1 and return to calling program.
c
      ivon02 = ivon01
      ff029  = ivon02 + 1
      ivon02 = 500
      return
      end
E 1
