h04899
s 00001/00001/00044
d D 1.3 93/06/02 13:56:57 elan 3 2
c pid_t changes from short to long.
e
s 00004/00004/00041
d D 1.2 93/05/25 15:32:16 elan 2 1
c support for 4.4BSD
e
s 00045/00000/00000
d D 1.1 93/02/17 11:51:02 elan 1 0
c date and time created 93/02/17 11:51:02 by elan
e
u
U
t
T
I 1
D 2
/* AUTOMATICALLY GENERATED; DO NOT EDIT! */ 
E 2
#ifndef _G_config_h
#define _G_config_h
#define _G_LIB_VERSION "2.3"
#define _G_NAMES_HAVE_UNDERSCORE 1
#define _G_DOLLAR_IN_LABEL 1
#define _G_HAVE_ST_BLKSIZE 1
typedef unsigned long _G_clock_t;
typedef unsigned long _G_dev_t;
D 2
typedef quad_t _G_fpos_t;
E 2
I 2
typedef long long _G_fpos_t;
E 2
typedef unsigned long _G_gid_t;
typedef unsigned long _G_ino_t;
typedef unsigned short _G_mode_t;
typedef unsigned short _G_nlink_t;
typedef long long _G_off_t;
D 3
typedef short _G_pid_t;
E 3
I 3
typedef long _G_pid_t;
E 3
typedef int _G_ptrdiff_t;
typedef unsigned int _G_sigset_t;
typedef unsigned int _G_size_t;
typedef long _G_time_t;
typedef unsigned long _G_uid_t;
typedef unsigned short _G_wchar_t;
typedef int _G_ssize_t;
typedef char* /* default */ _G_va_list;
#define _G_signal_return_type void
#define _G_sprintf_return_type int
#define _G_BUFSIZ 1024 
#define _G_FOPEN_MAX 20 
#define _G_FILENAME_MAX 1024 
#define _G_NULL 0 /* default */
D 2
#ifdef _G_USE_PROTOS
E 2
I 2
/* #ifdef _G_USE_PROTOS*/
E 2
#define _G_ARGS(ARGLIST) ARGLIST
I 2
/*
E 2
#else
#define _G_ARGS(ARGLIST) (...)
D 2
#endif
E 2
I 2
#endif */
E 2
/* #define _G_SYSV */
#define _G_HAVE_SYS_RESOURCE 0
#define _G_HAVE_SYS_SOCKET 1
#define _G_HAVE_SYS_WAIT 1
#define _G_HAVE_UNISTD 1
#define _G_HAVE_DIRENT 1
#define _G_HAVE_CURSES 1
/* #define _G_BROKEN_SIGNED_CHAR */
/* #define _G_FRIEND_BUG */
#endif /* !_G_config_h */
E 1
