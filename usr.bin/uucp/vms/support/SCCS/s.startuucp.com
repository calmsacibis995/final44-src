h64822
s 00000/00000/00076
d D 8.1 93/06/06 22:15:59 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00076/00000/00000
d D 5.1 91/04/24 17:51:34 bostic 1 0
c date and time created 91/04/24 17:51:34 by bostic
e
u
U
t
T
I 1
$!
$! Command procedure to initialize the uucp environment.
$! It is to be invoked from systartup.com.
$!
$! The uucico and uuxqt batch jobs are submitted as the uucp user.
$!
$ assign/system e$disk:[eunice.usr.lib.uucp]uucpmail nyu$uucpmail
$ define/system UUCP_NAME UUCP
$!
$ set_user_cld = F$PARSE("NYU$PRINTER:SETUSER.CLD")
$ if set_user_cld .nes. "" then $ set_user_cld = F$SEARCH(set_user_cld)
$ if set_user_cld .eqs. "" then $ goto err_no_cld
$ set_user = F$PARSE("NYU$PRINTER:SETUSER.EXE")
$ if set_user .nes. "" then $ set_user = F$SEARCH(set_user)
$ if set_user .eqs. "" then $ goto err_no_exe
$ on error then $ goto bad_set_user
$!
$ uucico_file = "E$DISK:[EUNICE.USR.LIB.UUCP]UUCICO.COM;"
$ uucico = F$PARSE( uucico_file )
$ if uucico .nes. "" then $ uucico = F$SEARCH(uucico)
$ if uucico .eqs. "" then $ goto no_uucico
$!
$ uuxqt_file = "E$DISK:[EUNICE.USR.LIB.UUCP]UUXQT.COM;"
$ uuxqt = F$PARSE( uuxqt_file )
$ if uuxqt .nes. "" then $ uuxqt = F$SEARCH(uuxqt)
$ if uuxqt .eqs. "" then $ goto no_uuxqt
$!
$ resubmit = F$PARSE("NYU$BACKUP:RESUBMIT.COM")
$ if resubmit .eqs. "" then $ resubmit = F$SEARCH(resubmit)
$!
$ set command 'set_user_cld'
$ uucp_user = "UUCP"
$ uucp_user = F$LOGICAL("UUCP_NAME")
$ if uucp_user .eqs. "" then $ uucp_user = "UUCP"
$!
$ cur_username = F$GETJPI("","USERNAME")
$ setuser 'uucp_user'
$ ! Submit them
$ on error then $ goto bad_submit
$ if resubmit .nes. "" then $ goto resubmit_it
$!
$ submit/queue=SYS$SPECIAL/keep 'UUCICO' /after="+0:15:0"
$ submit/queue=SYS$SPECIAL/keep 'UUXQT' /after="+0:15:0"
$ goto set_back
$!
$resubmit_it:
$ @'resubmit' UUCICO SYS$SPECIAL 'UUCICO' "/after=""""+0:15:0"""""
$ @'resubmit' UUXQT SYS$SPECIAL 'UUXQT' "/after=""""+0:15:0"""""
$!
$set_back:
$ setuser 'cur_username'
$ exit
$!
$err_no_cld:
$ write sys$output "%STARTUUCP-E-NOCLD, no NYU$PRINTER:SETUSER.CLD file"
$ exit %X0
$!
$err_no_exe:
$ write sys$output "%STARTUUCP-E-NOEXE, no NYU$PRINTER:SETUSER.EXE file"
$ exit %X0
$!
$no_uuxqt:
$ write sys$output "%STARTUUCP-E-NOUUXQT, no ",uuxqt_file," file"
$ exit %X0
$!
$no_UUCICO:
$ write sys$output "%STARTUUCP-E-NOUUCICO, no ",UUCICO_file," file"
$ exit %X0
$!
$bad_set_user:
$ write sys$output "%STARTUUCP-E-BADSETUSER, SETUSER ",UUCP_USER," failed"
$ exit %X0
$!
$bad_submit:
$ write sys$output "%STARTUUCP-E-SUBMITFAIL, submit failed"
$ exit %X0
E 1
