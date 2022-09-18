;
;uommacs.l:	(Copyright (c)	Richard J. Wood	May 1982)
;
; Modified by Liz Allen, October 1982.
;
(declare 	(macros t)
 		(special poport)
	]

(eval-when (compile) (load 'uommacs.l))

(defmacro date nil `(status ctime))

(defmacro if (&rest form)
  ((lambda (clause result)
	 (mapc #'(lambda (itm)
			(cond ((eq itm 'then))
			      ((eq itm 'else) (tconc result (car clause))
					      (setq clause (tconc nil t)))
			      ((eq itm 'elseif) (tconc result (car clause))
						(setq clause (ncons nil)))
			      (t (tconc clause itm))))
		(cdr form))
	(cons 'cond (car (cond ((car clause) (tconc result (car clause)))
			       (t result)))))
  (tconc nil (car form))
  (ncons nil))
	]

(defmacro push (&rest form)
	`(setq ,(car form) (append ,(cons 'list (cdr form)) ,(car form)))
	]

(defmacro pop (&rest form)
	`(prog1 (car ,(car form)) (setq ,(car form) (cdr ,(car form))))
	]

(declare (localf BuildSelectqBody))

(defmacro selectq (&rest form)
	(cond ((atom (car form))
			(BuildSelectqBody (car form)
					  (cdr form)
					  (car (last form))))
	      (t `((lambda ,(list '$$selectqvalue$$)
			,(BuildSelectqBody '$$selectqvalue$$
					   (cdr form)
					   (car (last form))))
		   ,(car form))))
	]

(defun BuildSelectqBody (key form last)
	(cons 'cond
		(mapcar #'(lambda (clause)
			(cond ((eq clause last) (list t clause))
			      ((dtpr (car clause))
				  (cons (list 'memq key (list 'quote 
							      (car clause)))
					(cdr clause)))
			      (t (cons (list 'eq key (list 'quote
							   (car clause)))
				       (cdr clause)))))
			form))
	]

;***************************************************************************
;
;	for:	        a macro for generalized looping and mapping.
;                       based loosely on that found in Interlisp.
;
;	copyright:	Randall H. Trigg		1982
;	initial release:	August 1981           Randy Trigg
;	05/10/82	added	keywords from, fromd, quit, being, eachtime.
;                       improved efficiency somewhat.  Removed selectq and if
;                                calls from code.

(declare (special $$FORKEYWORDS$$ COMM)
	 (localf on-hdlr in-hdlr divide-at-key scan-from mkprogn mklist1)
	 (macros t))

(setq $$FORKEYWORDS$$ '(do collect join sum count always initially finally
                        while until when unless let bind never thereis last
			tcollect tjoin from fromd quit being eachtime))

(defmacro for (&rest COMM)
   (let ((var-val '($$val))
         do-args conds var-conds if-conds result body in-on-arg let-args do-stmt
         inits eaches final)
    (do ((key-phrase (divide-at-key COMM)) (key))
        ((null COMM))
        (setq key (car COMM))
	(setq key-phrase (divide-at-key (cdr COMM)))
        (cond
           ((eq key 'while)   
		    (setq conds (cons (list 'not (mkprogn key-phrase)) conds)))
           ((eq key 'until)
		    (setq conds (cons (mkprogn key-phrase) conds)))
           ((eq key 'when)
		    (setq if-conds (cons (mkprogn key-phrase) if-conds)))
           ((eq key 'unless)
		    (setq if-conds (cons (list 'not (mkprogn key-phrase)) 
					 if-conds)))
           ((eq key 'let)
		    (setq let-args (nconc let-args key-phrase)))
           ((eq key 'bind)
		    (setq do-args (nconc do-args (mapcar 'mklist1 key-phrase))))
	   ((eq key 'being)
	    (setq do-args 
		  (nconc do-args 
			 (mapcar #'(lambda (x)
				  (setq x (mklist1 x))
				  (cond ((onep (length x))
					 `(,(car x) nil nil))
					((eq (length x) 2)
					 `(,(car x) ,(cadr x) ,(cadr x)))
					(t x)))
				 key-phrase))))
           ((eq key 'on)
		    (and (cddr key-phrase) (error "missing for keyword"))
                    (setq in-on-arg (car key-phrase))
                    (setq do-args (cons (on-hdlr in-on-arg (cadr key-phrase)) 
					do-args))
                    (setq var-conds (cons (list 'null in-on-arg) var-conds)))
           ((eq key 'in)
		    (and (cddr key-phrase) (error "missing for keyword"))
                    (setq in-on-arg (gensym)
                          let-args (nconc let-args (ncons in-on-arg)))
                    (setq do-args (cons (in-hdlr (car key-phrase) 
						 in-on-arg 
						 (cadr key-phrase))
					do-args))
                    (setq var-conds (cons (list 'null in-on-arg) var-conds)))
	   ((eq key 'from)
	            (and (cddddr key-phrase) (error "missing for keyword"))
	            (let ((var (car key-phrase))
		          (from-arg (cadr key-phrase))
		          (to-arg (caddr key-phrase))
		          (by-arg (cadddr key-phrase)))
	             (setq do-args 
			   (cons
			    `(,var ,from-arg ,(cond ((onep by-arg)
					             `(add1 ,var))
					            (t `(plus ,var ,by-arg))))
			    do-args))
	             (and to-arg (setq var-conds (cons `(greaterp ,var ,to-arg)
						   var-conds)))))
	   ((eq key 'fromd)
	            (and (cddddr key-phrase) (error "missing for keyword"))
	            (let ((var (car key-phrase))
		          (fromd-arg (cadr key-phrase))
		          (to-arg (caddr key-phrase))
		          (by-arg (cadddr key-phrase)))
	             (setq do-args 
			   (cons
			    `(,var ,fromd-arg 
				   ,(cond ((onep by-arg)
					   `(sub1 ,var))
					  (t `(difference ,var ,by-arg))))
			    do-args))
	             (and to-arg (setq var-conds (cons `(lessp ,var ,to-arg)
						   var-conds)))))
           ((eq key 'initially)
		    (setq inits (nconc inits key-phrase)))
	   ((eq key 'eachtime)
		    (setq eaches (nconc eaches key-phrase)))
           ((eq key 'do)
		    (setq body (mkprogn key-phrase)
                          result nil))
           ((eq key 'collect)
		    (setq body `(setq $$val (cons ,(mkprogn key-phrase) $$val))
                          result '(reverse $$val)))
           ((eq key 'tcollect)
		    (setq body `(tconc $$val ,(mkprogn key-phrase))
		           var-val '($$val (ncons nil))
			   result '$$val))
           ((eq key 'join)
		    (setq body `(setq $$val (nconc $$val ,(mkprogn key-phrase)))
                          result '$$val))
           ((eq key 'tjoin)
		    (setq body `(lconc $$val ,(mkprogn key-phrase))
		          var-val '($$val (ncons nil))
			  result '$$val))
           ((eq key 'sum)
		    (setq body `(setq $$val (plus $$val ,(mkprogn key-phrase)))
                          var-val '($$val 0)
                          result '$$val))
           ((eq key 'count)
		    (setq body `(and (setq $$val (add1 $$val)) 
                                     ,(mkprogn key-phrase))
                          var-val '($$val 0)
                          result '$$val))
           ((eq key 'always)
		    (setq body `(or (setq $$val ,(mkprogn key-phrase)) 
                                    (return nil))
                          result '(or $$val t)))
           ((eq key 'never)
		    (setq body `(and ,(mkprogn key-phrase) (return nil))
                          result 't))
           ((eq key 'thereis)
		    (setq body `(and (setq $$val ,(mkprogn key-phrase))
                                     (return $$val))
                          result nil))
	   ((eq key 'quit)
		    (setq body `(return ,(mkprogn key-phrase))
			  result nil))
           ((eq key 'last)
		    (setq body `(setq $$val ,(mkprogn key-phrase))
			  result '$$val))
           ((eq key 'finally)
		    (setq final 
			  (cond ((eq result '$$val) key-phrase)
			        (t (cons `(setq $$val ,result) key-phrase)))))
           (t nil)))

    (and if-conds 
	 (setq body `(and ,@if-conds ,body)))

    (and var-conds (setq conds (nconc var-conds conds)))
    (cond ((cdr conds) (setq conds (cons 'or conds)))
          (t (setq conds (car conds))))
    (and eaches
	 (setq conds `(progn ,@eaches ,conds)))

    (cond (final (setq result final))
	  (t (setq result (list result))))

    (setq do-stmt 
	  `(do ,(cons var-val do-args) (,conds ,@result) ,body))
    (cond ((or inits let-args) `(let ,let-args ,@inits ,do-stmt))
          (t do-stmt))))

(defun on-hdlr (var lst)
   `(,var ,lst (cdr ,var]

(defun in-hdlr (var lst-name lst)
   `(,var (and (setq ,lst-name ,lst)
               (car ,lst-name))
          (and (setq ,lst-name (cdr ,lst-name))
               (car ,lst-name]

; Return a copy of the front of lst up until first occurrence of
; a keyword or a "x in l" phrase.  Has the side effect of setting
; the hung variable COMM to the rest of lst.

(defun divide-at-key (lst)
   (cond ((or (null lst)(memq (car lst) $$FORKEYWORDS$$))
            (setq COMM lst) 
            nil)
         ((memq (cadr lst) '(in on))
            (setq COMM (cons (cadr lst) (cons (car lst) (cddr lst))))
            nil)
	 ((memq (cadr lst) '(from fromd))
	    (setq COMM `(,(cadr lst) ,(car lst) ,@(scan-from (cddr lst))))
	    nil)
         (t (cons (car lst) (divide-at-key (cdr lst))))))

; search down lst for the optional keywords "to" and "by" which are part of the
; "from" syntax - return a list of the var-name, to-arg, and by-arg

(defun scan-from (lst)
  (let ((from-arg (car lst)) 
	to-arg (by-arg 1))
   (setq lst (cdr lst))
   (cond ((eq (car lst) 'to)
	  (setq to-arg (cadr lst))
	  (setq lst (cddr lst))
          (and (eq (car lst) 'by)
	       (setq by-arg (cadr lst))
	       (setq lst (cddr lst))))
	 ((eq (car lst) 'by)
	  (setq by-arg (cadr lst))
	  (setq lst (cddr lst))
          (and (eq (car lst) 'to)
	       (setq to-arg (cadr lst))
	       (setq lst (cddr lst)))))
   `(,from-arg ,to-arg ,by-arg ,@lst)))

; if lst has length 1 then return the car, otherwise stick a progn on the front

(defun mkprogn (lst)
   (cond ((null (cdr lst)) (car lst))
         (t (cons 'progn lst))))

(defun mklist1 (obj)
  (cond ((dtpr obj) obj)
	(t (list obj))))


;***********************************************************************
;	The msg macro  --  Written by Liz Allen
;
; msg takes a list of arguments, prints them and then prints a newline.
; If the special atoms: B, N, T appear, they represent blank, newline and
; tab.
;
; If (B n), (N n) or (T n) appear, they translate into n blank, n newlines,
; and n tabs respectively.  n may either be a constant or a variable.  If
; (P 'port) appears in the first position, the output is redirected to that
; port.  If (C n) appears, the next thing printed will be in column n,
; either on the same line if at least one blank can be printed, or on the
; next line.  Thus,
;
;	(msg "12345678901234567890" B 'foo
;	     (N 2) 'bar (C 10) 'item1 (C 10) 'item2
;	     (N 2) 'baz (T 2) 'tab
;	     N 'foobarr (T x) 'tab)
;
; will output (if x is bound to 2):
;
;	12345678901234567890 foo
;
;	bar      item1
;		 item2
;
;	baz		tab
;	foobarr		tab
;
; If a -N appears in the last position, then the output port is drained
; without doing a newline.  For example:
;
;	(msg "Do you need foo? (y/n) " -N)
;
; will print the question and leave the user on the same line to answer it.
; If a -D appears in the last position, then neither a newline nor a drain
; will be done.  For example:
;
;	(msg 123456789 N "Items" -D)
;	(for x in '(a b c) do (msg (C 9) x))
;
; will print:
;
;	123456789
;	Items   a
;		b
;		c
;
; The -D is necessary since draining the port would throw off the count
; used in the (C 9)
;

(declare (macros t) (special poport piport))

(defmacro msg (&rest lst)
 (let (oport no-terpri-drain drain-only)
  (and (not (atom (car lst)))
       (eq (caar lst) 'P)
       (setq oport (cadr (pop lst))))
  (for x in lst
       unless (selectq x
		((-N D)	(setq drain-only t))
		(-D	(setq no-terpri-drain t))
		 nil)
       collect (setq no-terpri-drain nil
		     drain-only nil)
	       (cond ((stringp x) `(patom ,x))
		     ((atom x)
			(selectq x
			  (B	`(patom '| |))
			  (T	`(patom ',(ascii 9)))
			  (N	`(terpri))
			  `(patom ,x)))
		     (t (selectq (car x)
			  (B	`(spaces ,(cadr x)))
			  (T	`(common-tabs ,(cadr x)))
			  (C	`(column ,(cadr x)))
			  (N	`(crlf ,(cadr x)))
			  (L	`(print ,(cadr x)))
			  `(patom ,x))))
       finally (setq lst $$val))
  (cond (drain-only (setq lst `(,.lst (drain))))
	(no-terpri-drain)
	(t (setq lst `(,.lst (terpri)))))
  (and oport (setq lst (for x in lst collect `(,@x ,oport))))
  `(progn ,.lst)))

; Handy macros for user i/o

(defmacro query (&rest prompt)
  `(progn (msg ,@prompt -N) (yesp (read))))

(defmacro readp (&rest prompt)
  `(progn (msg ,@prompt -N) (read)))

(defmacro readlinep (&rest prompt)
  `(progn (msg ,@prompt -N) (readline)))
