.PH ""
.PF "'Copyright (c) 1984, 1985, 1986, 1987''AT&T All Rights Reserved'"
.ds HF 3 3 3 3 3 3
.nr Hb 6
.nr Cl 5
.de CW
.nf
.br
.sp
.ps 14
.vs 18p
.ta 16m/3u 32m/3u 48m/3u 64m/3u 80m/3u 96m/3u
.cs B 24
.ft B
..
.de CN
.ta 0.5i 1i 1.5i 2i 2.5i 3i 3.5i 4i 4.5i 5.5i 6i
.vs
.ps
.cs B
.ft R
.sp
.fi
..
.SK
.CW
int
pre_or_post (f, count, index, rc)
struct field_item **f;
int	count;
int	index;
int	rc;
{
	/* Body */
~
	return (new index);
}
.CN
.SK
.CW
main ()
{
	~
	extern int help_routine ();
	~
	Set_Help (f[0], "Enter a date.", FALSE, TRUE,
		help_routine);
	~
}

help_routine (field_ptr)
struct field_item *field_ptr;
{
	long    Time_loc;
	char   *C_time;
	char sbuf[80];

	Time_loc = (long) time (0);
	C_time = (char *) ctime (&Time_loc);
	C_time[strlen(C_time) - 1] = '\0';

	sprintf (sbuf, "Today's date is: %s", C_time);
	prhlp (field_ptr, sbuf, FALSE, FALSE);
}
.CN
.SK
.CW
cmregex (field_ptr)
register struct field_item     *field_ptr;
{
    extern char *__loc1;
    extern char *regex ();
    char *rc;
    char *error;

    error = "Cannot match or complete the pattern.";
    if (!cm_start (field_ptr, error, error)) return;

    if (field_ptr -> cmflg & CMHLP)
    {
        field_ptr -> cmflg |= CMNOP;
        if (field_ptr -> fnflg & FNHLP)
            return;

        prhlp (field_ptr, "Enter pattern to be matched.",
            FALSE, FALSE);
        return;
    }

    rc = regex (field_ptr -> keywords, field_ptr -> txbuf);
    if ((rc != NULL) && (__loc1 == field_ptr -> txbuf))
    {
        if (field_ptr -> cmflg & CMCMP)
        {
            complete (field_ptr, field_ptr -> txbuf);
            field_ptr -> cmflg |= CMREP;
        }
        return;
    }

    error_fields = error;
    field_ptr -> cmflg |= CMNOP;
}
.CN
.SK
.CW
main ()
{
    extern int mybrkchar ();
    ~
    Def_Char_Action (CTRL(D), NORMAL, regchar, 0);
    Def_Char_Action (CTRL(X), BREAK, mybrkchar, EOF_LIST);
    ~
}

mybrkchar (field_ptr, rc)
struct field_item *field_ptr;
char    rc;
{
    brkchar (field_ptr, K_EOF);
    return (TRUE);
}
.CN
.SK
.CW
main ()
{
	~
	extern int read_routine ();
	~
	Set_Reader (field_ptr, read_routine);
	~
}
.CN
