;
;uomfuncs.l:	(Copyright (c)	Richard J. Wood	May 1982)
;
(declare 	(macros t)
 		(special poport piport
			 OriginalTopLevel DateOfSysout FileName 
			 user-top-level franz-not-virgin)
	]

(eval-when (compile) (load 'uommacs))

; like (putd 'tofn (getd 'fromfn)) except will do a copy if the third
; argument is t
(defun movd (fromfn tofn &optional (copyflg nil))
	(cond (copyflg (putd tofn (copy (getd fromfn))))
	      (t (putd tofn (getd fromfn))))
        tofn
	]

; equivalent to (nthcdr (sub1 position) form) except that this one doesn't
; blow up when form is an atom.
(defun nth (position form)
	(cond ((onep position) form)
	      ((atom form) nil)
	      ((zerop position) (cons nil form))
	      ((greaterp position 0) (nth (sub1 position) (cdr form))))
	]

(defun mklist (obj &optional flg)
	(cond ((dtpr obj) obj)
	      ((null obj) (and flg (ncons nil)))
	      (t `(,obj))))

;returns copy of lst with the last element removed.
(defun removelast (lst)
	(and (cdr lst) (cons (car lst) (removelast (cdr lst)))))

(defun load* fexpr (filenames)
       (mapc #'(lambda (fname) (msg (load fname))) filenames)
	]

(defun sysout fexpr (filename)
	(setq OriginalTopLevel user-top-level)
	(setq DateOfSysout (date))
	(setq FileName (car filename))
	(setq franz-not-virgin nil)	; force startup
	(setq user-top-level 'SysoutGreeting)
	(apply 'dumplisp filename)
	(setq user-top-level OriginalTopLevel)
	(setq franz-not-virgin t)	; reset to normal
	FileName
	]

(defun SysoutGreeting (&aux (numargs (sub1 (argv -1)))
		            (temp 0))
	(cond ((eq (argv 1) '-f) (setq temp 2)
			(and (eq (argv 2) '-b) (setq temp 3)))
	      ((eq (argv 1) '-b) (setq temp 1))
	      (t (msg '< FileName '> N DateOfSysout)))
	(do nil ((not (greaterp numargs temp))
			(setq user-top-level OriginalTopLevel))
		(load (argv (setq temp (add1 temp)))))
	]

; rplacad does a rplaca and rplacd on the given cons cell (returns the cell)

(defun rplacad (cell new-car new-cdr)
  (rplaca cell new-car)
  (rplacd cell new-cdr))

;  The following functions are for formatting output and are used by
;  msg -- see uommacs.l

(defun spaces (n &optional (oport poport))
  (for i from 1 to n do (patom '| | oport)))

(defun common-tabs (n &optional (oport poport))
  (for i from 1 to n bind (tab (ascii 9)) do (patom tab oport)))

(defun crlf (n &optional (oport poport))
  (for i from 1 to n do (terpri oport)))

(defun column (n &optional (oport poport))
  (let ((over (nwritn oport)))
       (setq n (1- n))
       (cond ((eq n 0)		; for column 1, don't insert blank
		(and (> over 0) (terpr oport)))
	     ((< over n)	; cursor not past the desired column
		(spaces (- n over) oport))
	     (t (terpr oport)
		(spaces n oport)))))

; The yesp function, used by query

(defun yesp (x)
  (if (or (symbolp x) (stringp x))
      (setq x (getchar x 1))
      (or (eq x 'y) (eq x 'Y))))

; The readline function.
;

(defun readline (&optional (iport piport) &optional eof)
  (prog (char inbuffer spaceflg)
	(for being (x (tyipeek iport))
	     until (and (eq x -1) (return eof))
	     until (eq x 10)
	     while (eq (getsyntax (ascii x)) 'vseperator)
	     do (readc iport)
	     finally (and (eq x 10) (readc iport)))
	(setq inbuffer (ncons nil))
   loop (setq char (tyipeek iport))
	(if (eq char -1)	; -1 means eof
	    (readc iport)
	    (return (or (car inbuffer) eof)))
	(if (eq char 10)
	    (go eol))
	(selectq (getsyntax (ascii char))
	  (vseparator
	       (setq spaceflg t)
	       (readc iport)
	       (go loop))
	  ((vright-paren vright-bracket)
	       (readc iport)
	       (or (car inbuffer) (tconc inbuffer nil))
	       (go done))
	  (progn (tconc inbuffer (read iport))
		 (setq spaceflg nil)
		 (go loop)))
   eol	(if spaceflg
	    then (readc iport)
		 (patom '|... |)
		 (drain)
		 (setq spaceflg nil)
		 (go loop))
   done (return (car inbuffer))))

; define prin1 and prin2 to agree with INTERLISP which is what
; we're used to at Maryland; print will not be what we're used to.

(movd 'patom 'prin1)
(movd 'print 'prin2)
