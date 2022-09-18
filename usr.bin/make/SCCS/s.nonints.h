h59821
s 00018/00010/00096
d D 8.4 95/04/28 17:08:20 christos 11 10
c Updated to the latest version from the NetBSD source
e
s 00091/00090/00015
d D 8.3 94/03/19 15:55:22 christos 10 9
c add prototypes for all external functions
e
s 00002/00000/00103
d D 8.2 94/03/19 10:53:16 bostic 9 8
c The SYSV ${VAR:src=dst} was broken; try:
c SRC=foo.c bar.c
c all:
c 	echo ${SRC:%.c=%.o}
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00002/00101
d D 8.1 93/06/06 15:16:32 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00087/00086/00016
d D 5.7 93/05/24 14:45:52 bostic 7 6
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00002/00000/00100
d D 5.6 91/04/18 16:11:22 bostic 6 5
c add correct copyright notice...
e
s 00012/00000/00088
d D 5.5 91/04/18 16:10:48 bostic 5 4
c add copyright notice
e
s 00003/00003/00085
d D 5.4 90/03/19 09:59:46 bostic 4 3
c Str_BreakString -> brk_string; delete Str_FreeVec; other minor whacks
e
s 00000/00015/00088
d D 5.3 90/03/12 10:42:36 bostic 3 2
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00000/00001/00103
d D 5.2 90/03/12 08:59:41 bostic 2 1
c Str_New -> strdup
e
s 00104/00000/00000
d D 5.1 90/03/11 15:27:42 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 5
/*-
D 8
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 8
I 8
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * %sccs.include.redist.c%
I 6
 *
 *	%W% (Berkeley) %G%
E 6
 */

E 5
I 4
D 10
char **brk_string(), *emalloc(), *str_concat();
E 10
I 10
/* arch.c */
ReturnStatus Arch_ParseArchive __P((char **, Lst, GNode *));
void Arch_Touch __P((GNode *));
void Arch_TouchLib __P((GNode *));
int Arch_MTime __P((GNode *));
int Arch_MemMTime __P((GNode *));
void Arch_FindLib __P((GNode *, Lst));
Boolean Arch_LibOODate __P((GNode *));
void Arch_Init __P((void));
D 11
  
E 11
I 11
void Arch_End __P((void));

E 11
/* compat.c */
void Compat_Run __P((Lst));
E 10

E 4
I 1
D 7
ReturnStatus	Arch_ParseArchive ();
void	Arch_Touch ();
void	Arch_TouchLib ();
int	Arch_MTime ();
int	Arch_MemMTime ();
void	Arch_FindLib ();
Boolean	Arch_LibOODate ();
void	Arch_Init ();
void	Compat_Run();
void	Dir_Init ();
Boolean	Dir_HasWildcards ();
void	Dir_Expand ();
char *	Dir_FindFile ();
int	Dir_MTime ();
void	Dir_AddDir ();
ClientData	Dir_CopyDir ();
char *	Dir_MakeFlags ();
void	Dir_Destroy ();
void	Dir_ClearPath ();
void	Dir_Concat ();
int	Make_TimeStamp ();
Boolean	Make_OODate ();
int	Make_HandleUse ();
void	Make_Update ();
void	Make_DoAllVar ();
Boolean	Make_Run ();
D 3
void	Rmt_Init();
void	Rmt_AddServer ();
Boolean	Rmt_Begin ();
void	Rmt_Exec ();
Boolean	Rmt_ReExport();
int	Rmt_LastID();
void	Rmt_Done ();
E 3
void	Job_Touch ();
Boolean	Job_CheckCommands ();
void	Job_CatchChildren ();
void	Job_CatchOutput ();
void	Job_Make ();
void	Job_Init ();
Boolean	Job_Full ();
Boolean	Job_Empty ();
ReturnStatus	Job_ParseShell ();
int	Job_End ();
void	Job_Wait();
void	Job_AbortAll ();
void	Main_ParseArgLine ();
void	Error ();
void	Fatal ();
void	Punt ();
void	DieHorribly ();
void	Finish ();
void	Parse_Error ();
D 3
Boolean	Parse_AnyExport();
E 3
Boolean	Parse_IsVar ();
void	Parse_DoVar ();
void	Parse_AddIncludeDir ();
void	Parse_File();
Lst	Parse_MainName();
void	Suff_ClearSuffixes ();
Boolean	Suff_IsTransform ();
GNode *	Suff_AddTransform ();
void	Suff_AddSuffix ();
int	Suff_EndTransform ();
Lst	Suff_GetPath ();
void	Suff_DoPaths();
void	Suff_AddInclude ();
void	Suff_AddLib ();
void	Suff_FindDeps ();
void	Suff_SetNull();
void	Suff_Init ();
void	Targ_Init ();
GNode *	Targ_NewGN ();
GNode *	Targ_FindNode ();
Lst	Targ_FindList ();
Boolean	Targ_Ignore ();
Boolean	Targ_Silent ();
Boolean	Targ_Precious ();
void	Targ_SetMain ();
int	Targ_PrintCmd ();
char *	Targ_FmtTime ();
void	Targ_PrintType ();
D 3
void	Rmt_Init();
void	Rmt_AddServer ();
Boolean	Rmt_Begin ();
Boolean	Rmt_ReExport();
void	Rmt_Exec ();
int	Rmt_LastID();
void	Rmt_Done ();
E 3
char *	Str_Concat ();
D 2
char *	Str_New ();
E 2
D 4
char **	Str_BreakString ();
void	Str_FreeVec ();
char *	Str_FindSubstring();
E 4
int	Str_Match();
void	Var_Delete();
void	Var_Set ();
void	Var_Append ();
Boolean	Var_Exists();
char *	Var_Value ();
char *	Var_Parse ();
char *	Var_Subst ();
char *	Var_GetTail();
char *	Var_GetHead();
void	Var_Init ();
I 4
char *	Str_FindSubstring();
E 7
I 7
D 10
char	*Dir_FindFile();
char	*Dir_MakeFlags();
char	*Str_Concat();
char	*Str_FindSubstring();
GNode	*Suff_AddTransform();
GNode	*Targ_FindNode();
char	*Targ_FmtTime();
void	 enomem __P((void));
GNode	*Targ_NewGN();
char	*Var_GetHead();
char	*Var_GetTail();
char	*Var_Parse();
char	*Var_Subst();
char	*Var_Value();
void	 Arch_FindLib();
void	 Arch_Init();
Boolean	 Arch_LibOODate();
int	 Arch_MTime();
int	 Arch_MemMTime();
ReturnStatus	 Arch_ParseArchive();
void	 Arch_Touch();
void	 Arch_TouchLib();
void	 Compat_Run();
void	 DieHorribly();
void	 Dir_AddDir();
void	 Dir_ClearPath();
void	 Dir_Concat();
ClientData	 Dir_CopyDir();
void	 Dir_Destroy();
void	 Dir_Expand();
Boolean	 Dir_HasWildcards();
void	 Dir_Init();
int	 Dir_MTime();
void	 Error __P((const char *, ...));
void	 Fatal __P((const char *, ...));
void	 Finish();
void	 Job_AbortAll();
void	 Job_CatchChildren();
void	 Job_CatchOutput();
Boolean	 Job_CheckCommands();
Boolean	 Job_Empty();
int	 Job_End();
Boolean	 Job_Full();
void	 Job_Init();
void	 Job_Make();
ReturnStatus	 Job_ParseShell();
void	 Job_Touch();
void	 Job_Wait();
void	 Main_ParseArgLine();
void	 Make_DoAllVar();
int	 Make_HandleUse();
Boolean	 Make_OODate();
Boolean	 Make_Run();
int	 Make_TimeStamp();
void	 Make_Update();
void	 Parse_AddIncludeDir();
void	 Parse_DoVar();
void	 Parse_Error __P((int, const char *, ...));
void	 Parse_File();
Boolean	 Parse_IsVar();
Lst	 Parse_MainName();
void	 Punt __P((const char *, ...));
int	 Str_Match();
I 9
char	*Str_SYSVMatch __P((char *, char *, int *len));
void	 Str_SYSVSubst __P((Buffer, char *, char *, int));
E 9
void	 Suff_AddInclude();
void	 Suff_AddLib();
void	 Suff_AddSuffix();
void	 Suff_ClearSuffixes();
void	 Suff_DoPaths();
int	 Suff_EndTransform();
void	 Suff_FindDeps();
Lst	 Suff_GetPath();
void	 Suff_Init();
Boolean	 Suff_IsTransform();
void	 Suff_SetNull();
Lst	 Targ_FindList();
Boolean	 Targ_Ignore();
void	 Targ_Init();
Boolean	 Targ_Precious();
int	 Targ_PrintCmd();
void	 Targ_PrintType();
void	 Targ_SetMain();
Boolean	 Targ_Silent();
void	 Var_Append();
void	 Var_Delete();
Boolean	 Var_Exists();
void	 Var_Init();
void	 Var_Set();
E 10
I 10
/* cond.c */
int Cond_Eval __P((char *));
void Cond_End __P((void));

/* for.c */
int For_Eval __P((char *));
void For_Run  __P((void));

/* main.c */
void Main_ParseArgLine __P((char *));
int main __P((int, char **));
D 11
void Error __P((const char *, ...));
void Fatal __P((const char *, ...));
void Punt __P((const char *, ...));
E 11
I 11
void Error __P((char *, ...));
void Fatal __P((char *, ...));
void Punt __P((char *, ...));
E 11
void DieHorribly __P((void));
I 11
int PrintAddr __P((ClientData, ClientData));
E 11
void Finish __P((int));
D 11
char *emalloc __P((u_int));
E 11
I 11
char *emalloc __P((size_t));
E 11
void enomem __P((void));

/* parse.c */
D 11
void Parse_Error __P((int, const char *, ...));
E 11
I 11
void Parse_Error __P((int, char *, ...));
E 11
Boolean Parse_AnyExport __P((void));
Boolean Parse_IsVar __P((char *));
void Parse_DoVar __P((char *, GNode *));
void Parse_AddIncludeDir __P((char *));
void Parse_File __P((char *, FILE *));
void Parse_Init __P((void));
I 11
void Parse_End __P((void));
E 11
void Parse_FromString __P((char *));
Lst Parse_MainName __P((void));

/* str.c */
I 11
void str_init __P((void));
void str_end __P((void));
E 11
char *str_concat __P((char *, char *, int));
D 11
char **brk_string __P((char *, int *));
E 11
I 11
char **brk_string __P((char *, int *, Boolean));
E 11
char *Str_FindSubstring __P((char *, char *));
int Str_Match __P((char *, char *));
char *Str_SYSVMatch __P((char *, char *, int *len));
void Str_SYSVSubst __P((Buffer, char *, char *, int));

/* suff.c */
void Suff_ClearSuffixes __P((void));
Boolean Suff_IsTransform __P((char *));
GNode *Suff_AddTransform __P((char *));
D 11
int Suff_EndTransform __P((GNode *));
E 11
I 11
int Suff_EndTransform __P((ClientData, ClientData));
E 11
void Suff_AddSuffix __P((char *));
Lst Suff_GetPath __P((char *));
void Suff_DoPaths __P((void));
void Suff_AddInclude __P((char *));
void Suff_AddLib __P((char *));
void Suff_FindDeps __P((GNode *));
void Suff_SetNull __P((char *));
void Suff_Init __P((void));
I 11
void Suff_End __P((void));
E 11
void Suff_PrintAll __P((void));

/* targ.c */
void Targ_Init __P((void));
I 11
void Targ_End __P((void));
E 11
GNode *Targ_NewGN __P((char *));
GNode *Targ_FindNode __P((char *, int));
Lst Targ_FindList __P((Lst, int));
Boolean Targ_Ignore __P((GNode *));
Boolean Targ_Silent __P((GNode *));
Boolean Targ_Precious __P((GNode *));
void Targ_SetMain __P((GNode *));
D 11
int Targ_PrintCmd __P((char *));
E 11
I 11
int Targ_PrintCmd __P((ClientData, ClientData));
E 11
char *Targ_FmtTime __P((time_t));
void Targ_PrintType __P((int));
void Targ_PrintGraph __P((int));

/* var.c */
void Var_Delete __P((char *, GNode *));
void Var_Set __P((char *, char *, GNode *));
void Var_Append __P((char *, char *, GNode *));
Boolean Var_Exists __P((char *, GNode *));
D 11
char *Var_Value __P((char *, GNode *));
E 11
I 11
char *Var_Value __P((char *, GNode *, char **));
E 11
char *Var_Parse __P((char *, GNode *, Boolean, int *, Boolean *));
char *Var_Subst __P((char *, char *, GNode *, Boolean));
char *Var_GetTail __P((char *));
char *Var_GetHead __P((char *));
void Var_Init __P((void));
I 11
void Var_End __P((void));
E 11
void Var_Dump __P((GNode *));
E 10
E 7
E 4
E 1
