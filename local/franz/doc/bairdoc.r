






(<= 'fx_arg1 'fx_arg2 ...)
(<=& 'x_arg1 'x_arg2)

     RETURNS: t iff (> '_f_x__a_r_g_1 '_f_x__a_r_g_2)  [or  (>&  '_x__a_r_g_1
              '_x__a_r_g_2)]  is nil, otherwise nil.  The general
              fucntion, <=, can take  more  than  two  argu-
              ments.

(>= 'fx_arg1 'fx_arg2)
(>=& 'x_arg1 'x_arg2)

     RETURNS: t  iff  (<  '_f_x__a_r_g_1  '_f_x__a_r_g_2  ...)  [or  (<&
              '_x__a_r_g_1 '_x__a_r_g_2)] is nil, otherwise nil.

     NOTE: The general function, >=, can take more than  two
           arguments.

(litatom 'g_arg)

     RETURNS: t iff g_arg is an atom, but not a number.

(nequal 'g_x 'g_y)

     RETURNS: t iff g_x is not _e_q_u_a_l to g_y, otherwise nil.

(lineread [['p_port] ['s_flag]])

     RETURNS: a list consisting of s-expressions on  a  line
              from  the  port p_port (or piport if p_port is
              not given).  If an s-expression (e.g., a list)
              takes more than one line, or a line terminates
              in a space or  tab,  then  _l_i_n_e_r_e_a_d  continues
              reading until an expression ends at the end of
              a line.

     NOTE: If s_flag is t, then if the first character on  a
           line  is  a  newline, _l_i_n_e_r_e_a_d performs a _t_y_i and
           returns nil.  If s_flag is nil  or  not  present,
           _l_i_n_e_r_e_a_d  does  a  _r_e_a_d  skipping  over any blank
           lines to make sure that an s-expression is  actu-
           ally read.

     SIDE EFFECT: _l_i_n_e_r_e_a_d uses  _r_e_a_d,  advancing  the  port
                  character pointer.








9

9










(defv g_arg1 g_arg2)

     EQUIVALENT TO: (_s_e_t _g__a_r_g_1 _g__a_r_g_2)

(pp-form 'g_form ['p_port] ['n_lmar])

     RETURNS: nil

     SIDE EFFECT: g_form  is  pretty-printed  to  the   port
                  p_port (or poport if p_port is not given).
                  If  _p_p-_f_o_r_m  is  also  supplied  with   an
                  integer  (n_lmar),  that  integer  will be
                  used as a left margin setting  (0  is  the
                  default).   This is the  function which _p_p
                  uses (n_lmar = 0). _p_p-_f_o_r_m does  not  look
                  for  function  definitions  or  values  of
                  variables, it just prints out the form  it
                  is given.

     NOTE: This is useful as a top-level-printer, c.f.  _t_o_p-
           _l_e_v_e_l in Chapter 6.

(sload 's_file1 ...)

     SIDE EFFECT: The files named are opened for reading and
                  each form is read, optionally printed, and
                  evaluated.

     NOTE: What _s_l_o_a_d prints is controlled  by  the  special
           atom  $_s_l_d_p_r_i_n_t.   If  $_s_l_d_p_r_i_n_t  is t (default),
           then if a form  is  recognizable  as  a  function
           definition,  only  the  function name is printed,
           otherwise  the  whole  form   is   printed.    If
           $_s_l_d_p_r_i_n_t is _e_q to _v_a_l_u_e, then the result of each
           form's evaluation will also be printed.  Printing
           the  forms'  values  can be controlled by setting
           _s_l_o_a_d-_p_r_i_n_t equal to the name of the function  to
           be  called.   _s_l_o_a_d recognizes named functions by
           looking at  the  _s_l_o_a_d_p_r_i_n_t_a_r_g  property  of  the
           function  name.   The  value of the _s_l_o_a_d_p_r_i_n_t_a_r_g
           property should be the  argument  number  of  the
           function name.  For the standard Franz Lisp func-
           tions, the properties are already set.

     EXAMPLE: (defprop def 1 sloadprintarg)   ; _T_h_i_s _i_s  _t_h_e
              _d_e_f_a_u_l_t--_d_e_c_l_a_r_i_n_g _t_h_a_t
                                              ; _t_h_e _n_a_m_e  _o_f
              _t_h_e _f_u_n_c_t_i_o_n _d_e_f_i_n_i_t_i_o_n _i_s _t_h_e
                                              ; _f_i_r_s_t  _a_r_g_u_-
              _m_e_n_t.


9

9










          The functions described below are  an  alternative
     to  the  gensym facility.  They generate new symbols by
     attaching counter numbers to the ends of  the  symbols'
     names.   An  example  follows  of how the functions are
     used.


    ____________________________________________________

    -> (initsym joe (john 5))       ; _i_n_i_t_i_a_l_i_z_i_n_g _n_e_w _s_y_m_b_o_l _c_o_u_n_t_e_r_s
    (joe0 john5)
    -> (newsym john)                ; _c_r_e_a_t_e _a _n_e_w _s_y_m_b_o_l
    john6
    -> (newsym chuck)               ; _s_y_m_b_o_l _n_e_e_d _n_o_t _b_e initsym'_e_d
    chuck0
    -> (oldsym john)                ; _g_e_t _c_u_r_r_e_n_t _s_y_m_b_o_l
    john6
    -> (allsym john)                ; _g_e_t _a_l_l _s_y_m_b_o_l_s _b_e_t_w_e_e_n _0 _a_n_d _c_o_u_n_t_e_r
    (john0 john1 john2 john3 john4 john5 john6)
    -> (allsym (john 5))            ; _g_e_t _a_l_l _s_y_m_b_o_l_s _b_e_t_w_e_e_n _5 _a_n_d _c_o_u_n_t_e_r
    (john5 john6)
    -> (remsym joe (john 4))        ; remob _a_l_l _i_n_t_e_r_n_e_d _s_y_m_b_o_l_s
                                    ; _a_s_s_o_c_i_a_t_e_d _w_i_t_h joe _a_n_d _f_r_o_m
                                    ; john4 _t_o _t_h_e _c_u_r_r_e_n_t john
                                    ; _s_y_m_b_o_l--_r_e_t_u_r_n_s _s_y_m_b_o_l_s _w_i_t_h _s_y_m_b_o_l _c_o_u_n_t_e_r_s
                                    ; _b_e_f_o_r_e _d_o_i_n_g remsym
    (joe0 john6)
    -> (symstat joe john)
    ((joe nil) (john 3))
    ____________________________________________________




(initsym g_arg1 ...)

     WHERE:   g_arg_i is a  list  (n_counter_i  s_arg_i)  or  a
              string  s_arg_i  (which  is  equivalent  to  (0
              s_arg_i)).

     RETURNS: a list of interned identifiers using the  sym-
              bol  counters  n_counter_i, i.e., the result of
              concatenating s_arg_i to n_counter_i.

     EXAMPLE: (initsym joe (john 5)) ==> (joe0 john5)

     NOTE: See also newsym, oldsym, allsym, remsym, and sym-
           stat functions.




9

9










(newsym s_arg)

     RETURNS: an interned identifier formed by concatenating
              the  name  s_arg  to  the  symbol  counter for
              s_arg.  The symbol counter is  stored  on  the
              property list of s_arg under _s_y_m_c_t_r.  If there
              is no counter, a counter  of  0  is  used  and
              added  to  the  property list.  Thus, a symbol
              need not be _i_n_i_t_s_y_med.

     EXAMPLE: (initsym joe (john5)) ==> (joe0 john5)
              (newsym john) ==> john6
              (newsym joe) ==> joe1

     NOTE: See also initsym,  oldsym,  allsym,  remsym,  and
           symstat functions.

(oldsym s_arg)

     RETURNS: the  identifier  using  the   current   symbol
              counter  for s_arg, rather than creating a new
              identifier.  If no symbol counter  exists  for
              s_arg, then s_arg is returned.

     NOTE: See also initsym,  newsym,  allsym,  remsym,  and
           symstat functions.

(allsym g_arg)

     WHERE:   g_arg is a list (s_arg n_counter) or a  string
              s_arg (equivalent to (s_arg 0)).

     RETURNS: a list of all the created identifiers  between
              n_counter  and  the current symbol counter for
              s_arg.

     EXAMPLE: (allsym john) ==> (john0 john1 john2)

     NOTE: See also initsym,  newsym,  oldsym,  remsym,  and
           symstat functions.

(remsym g_arg1 ...)

     WHERE:   g_arg_i is a  list  (s_arg_i  n_counter_i)  or  a
              string  s_arg_i (which is equivalent to (s_arg_i
              0)).

     RETURNS: a list of symbols s_arg_i with the current sym-
              bol counters.

     SIDE EFFECT: remsym _r_e_m_o_b's all the created identifiers
                  between   zero   and  the  current  symbol
                  counter for s_arg_i.













     NOTE: See also initsym, newsym oldsym, allsym, and sym-
           stat functions.

(symstat s_arg1 ...)

     RETURNS: a list of pairs consisting of (s_arg_i symctr_i)
              where   symctr_i  is  s_arg_i's  current  symbol
              counter.

     NOTE: See also initsym,  newsym,  oldsym,  allsym,  and
           remsym functions.









































9

9



