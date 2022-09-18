;
;nlispx.l	(Copyright (c)	Richard J. Wood	May 1982)
;               Sept. 1982 	added fix
(eval-when (compile) (load 'uommacs))

(declare 
	(special lispxinputbuffer lispxhistory lispxmacros lispxline
		 lispxmaxprintevents
	 	 piport poport)
	(macros t)
	]

; macros for accessing the history list structure and individual
;	components of events
;
; the history list is of the form:
;	((<list of events>) <current event number> <maximum event number>)
;
; each event is of the form:
;	(<input> <event number> <prompt> <result>)

(defmacro hevents (x) `(car ,x))	; list of events
(defmacro hcureventnum (x) `(cadr ,x))	; current event number
(defmacro hmaxevents (x) `(caddr ,x))	; maximum size of history list

(defmacro einput (x) `(car ,x))		; event input
(defmacro eeventnum (x) `(cadr ,x))	; event number
(defmacro eprompt (x) `(caddr ,x))	; event prompt
(defmacro eresult (x) `(cadddr ,x))	; event result
(defun formevent (&rest x) x)		; form a list for the event

; functions for locating sets of events in the history list


; historyfind:	returns the event occurring in the historylist
;		that corresponds to the eventspec (relative to
;		the currentevent and size of the historylist
;		if not found returns nil

(defun historyfind (historylist currentevent size eventspec)
	(and (eq (length eventspec) 1) 
	     (not (dtpr (car eventspec)))
	     (setq eventspec (car eventspec)))
	(cond ((numberp eventspec)
		(cond ((lessp eventspec 0) (setq eventspec (abs eventspec)))
		      ((greaterp eventspec size)) 	; out of bounds
		      (t (setq eventspec (difference currentevent eventspec))
			 (and (lessp eventspec 1)
			      (setq eventspec (plus size eventspec 1)))))
		(nth eventspec historylist))
	      (t (for bind (expandedpat (editpat eventspec))
		    x on historylist
		    until (editfindp (removelast (einput (car x))) 
				     expandedpat t)
		    finally x)))
	]

(defun historysave (history id input)
	(rplaca history
		(cons (formevent input (hcureventnum history) id (ascii 7))
		      (hevents history)))
	(rplaca (cdr history) (mod (add1 (hcureventnum history))
					 (hmaxevents history)))
	(and (greaterp (length (hevents history)) (hmaxevents history))
	     (rplacd (nth (hmaxevents history) (hevents history)) nil))
	(einput (hevents history))
	]

(defun lispx (lispxx lispxid)
  (let (lispxline lispxtemp lispxhtemp)
	(and (not (eq lispxx '| EOF|))
	     (or (not (dtpr lispxx)) (memq (car lispxx) '(lambda nlambda)))
	     (setq lispxline (lispxreadline piport t)))
	(and (eq lispxx '| EOF|) (terpri))
	(selectq lispxx
	  (|??| (printhistory lispxhistory lispxline))
	  (redo (setq lispxinputbuffer 
			(append (for x in (lispxfind lispxhistory
						     (or lispxline '(-1)))
				     join (append (car x) nil))
				lispxinputbuffer)))
	  (|!!| (setq lispxinputbuffer 
		    (append (for x in (lispxfind lispxhistory '(-1))
				 join (append (car x) nil))
			    lispxinputbuffer)))
	  (|!| (setq lispxinputbuffer 
		   (append (for x in (lispxfind lispxhistory 
						(or lispxline '(-1)) t)
				join (append (car x) nil))
			   lispxinputbuffer)))
	  (cond ((and (atom lispxx)
		      (not (numberp lispxx))
		      (equal (getchar lispxx 1) '|!|))
		   (setq lispxline (cons (readlist (cdr (explode lispxx)))
					 lispxline))
		   (setq lispxinputbuffer
			 (append (for x in (lispxfind lispxhistory lispxline t)
				      join (append (car x) nil))
				 lispxinputbuffer)))
	  	(t (setq lispxhtemp (historysave lispxhistory lispxid
					(append (cons lispxx lispxline)
						(ncons (ascii 10)))))
		   (cond ((setq lispxtemp (lispxmacrop 
						(cond ((atom lispxx) lispxx)
						      (t (car lispxx)))))
				(cond ((atom lispxx))
				      (t (setq lispxline (cdr lispxx)
					       lispxx (car lispxx))))
				(and (greaterp (nwritn) 0) (terpri))
				(msg (L (car (rplaca (cdddr lispxhtemp)
						     (eval (cdr lispxtemp)))))
				     ))
			 (t (and (greaterp (nwritn) 0) (terpri))
			    (msg (L (car
				      (rplaca (cdddr lispxhtemp)
                                         (selectq (length 
						    (setq lispxx
                                                       (cons lispxx lispxline)))
					   (1 (eval (car lispxx)))
					   (2 (apply (car lispxx)(cadr lispxx)))
					   (eval lispxx)))))))))))
	]

(defun lispxfind (historylst linespec &optional lispxflg)
  (let (from thru result)
	(if (null linespec) 
	    then (append (car historylst) nil)
	    elseif (eq (car linespec) 'all)	; (all ev1 ev2 ... evn)
		   then (do ((result (ncons nil))
			     (partialhistorylst (car historylst)
						(cdr partialhistorylst)))
			    ((null (setq partialhistorylst 
						(historyfind partialhistorylst
							     (cadr historylst)
							     (caddr historylst)
							     (cdr linespec))))
				(if (null (car result))
				    then (linespecerr linespec 'userexec-FRAME)
				    else (car result)))
			    (tconc result (car partialhistorylst)))
	    else (setq from (memq 'from linespec)
		       thru (memq 'thru linespec))
		 (if (and (not from) (not thru))	; single event spec
		     then (if (setq result (historyfind (car historylst)
							(cadr historylst)
							(caddr historylst)
							linespec))
			      then (list (car result))
			      elseif lispxflg	; from !
				     then (let ((newlinespec (append linespec
									nil))
						x)
					(setq x (last newlinespec))
					(if (and (car x)
						 (symbolp (car x))
					    	 (rplaca x (uconcat (car x) '$))
					 	 (setq result
							(historyfind 
							  (car historylst)
							  (cadr historylst)
							  (caddr historylst)
							  newlinespec)))
					     then (list (car result))
					     else (linespecerr linespec
							'userexec-FRAME)))
			      else (linespecerr linespec 'userexec-FRAME))
		     else (lispxfindrange historylst linespec from thru)))
	]

(defun lispxfindrange (historylst linespec from thru)
  (let ((oldlinespec linespec)
	(result nil)
	first last)
	(if from
	    then (if (neq from linespec)
		     then (linespecerr oldlinespec 'userexec-FRAME)
		     else (pop linespec))
		 (if thru
		     then (do ((temp (ncons nil) (tconc temp (pop linespec))))
			      ((eq linespec thru)
				 (if (and (car temp) (cdr linespec))
				     then (setq from (car temp)
						thru (cdr linespec))
				     else (linespecerr oldlinespec 
						       'userexec-FRAME))))
		     elseif linespec
			    then (setq from linespec
				       thru (ncons -1))
		     else (linespecerr oldlinespec 'userexec-FRAME))
	    elseif (eq thru linespec)
		   then (if (cdr linespec)
			    then (setq from (ncons -1)
				       thru (cdr linespec))
			    else (linespecerr oldlinespec 'userexec-FRAME))
	    else (do ((temp (ncons nil) (tconc temp (pop linespec))))
		     ((eq linespec thru)
			 (if (and (car temp) (cdr linespec))
			     then (setq from (car temp)
					thru (cdr linespec))
			     else (linespecerr oldlinespec 'userexec-FRAME)))))
	(if (and (setq from (historyfind (car historylst)
					 (cadr historylst)
					 (caddr historylst)
					 from))
		 (setq thru (historyfind (car historylst)
					 (cadr historylst)
					 (caddr historylst)
					 thru)))
	    then (if (tailp thru from)
		     then (setq first from
				last thru)
		     else (setq first thru
				last from))
		 (*catch 'lispxfindrange-FRAME
			 (mapc #'(lambda (event)
				  (push result event)
				  (if (eq event (car last))
				      then (throw result lispxfindrange-FRAME)))
			       first))
		 (if (eq last thru)
		     then (reverse result)
		     else result)
	    else (linespecerr linespec 'userexec-FRAME))
	]
	
(defun lispxmacrop (atm) 
	(assoc atm lispxmacros)
	]

(defun lispxread (&optional (iport piport) &aux val)
	(if lispxinputbuffer
	    then (setq val (pop lispxinputbuffer))
		 (if (eq val (ascii 10))
		     then (lispxread iport)
		     else (msg val B -D)
			  val)
	    else (read iport '| EOF|))
	]

(defun lispxtyipeek (&optional (iport piport))
	(if lispxinputbuffer
	    then (car (exploden (car lispxinputbuffer)))
	    else (tyipeek iport))
	]

(defun lispxreadc (&optional (iport piport) &aux val)
	(if lispxinputbuffer
	    then (setq val (pop lispxinputbuffer))
		 (if (neq val (ascii 10))
		     then (msg val B -D))
		 val
	    else (readc iport))
	]

(if (not (boundp 'running-under-old-franz))
    (setsyntax '|!| 'vcharacter)		  ; redo
    (setsyntax '|@| 'vsingle-character-symbol))	  ; escape to shell

(defun lispxreadline (&optional (iport piport) &optional (readlineflg t))
  (prog (char inbuffer spaceflg)
	(if (equal (lispxtyipeek iport) 10)	; carriage return on line
	    then (lispxreadc iport)
		 (return nil))
	(setq inbuffer (ncons nil))
   loop (if (eq (setq char (lispxtyipeek iport)) 10)
	    then (go eol))
	(selectq (getsyntax (setq char (ascii char)))
	  (vseparator
	       (setq spaceflg t)
	       (lispxreadc iport)
	       (go loop))
	  ((vright-paren vright-bracket)
	       (lispxreadc iport)
	       (or (car inbuffer) 
		   (and readlineflg (tconc inbuffer nil)))
	       (go eol))
	  (progn (tconc inbuffer (lispxread iport))
		 (setq spaceflg nil)
		 (go loop)))
   eol	(if spaceflg
	    then (lispxreadc iport)
		 (patom '|... |)
		 (drain)
		 (setq spaceflg nil)
		 (go loop)
	    else (return (delq (ascii 10) (car inbuffer))))
	]

(defun lispxreadline (&optional (iport piport) &optional (readlineflg t))
  (prog (char inbuffer spaceflg)
	(if (equal (lispxtyipeek iport) 10)	; carriage return on line
	    then (lispxreadc iport)
		 (return nil))
	(setq inbuffer (ncons nil))
   loop (if (eq (setq char (lispxtyipeek iport)) 10)
	    then (go eol))
	(selectq (getsyntax (setq char (ascii char)))
;	(selectq (apply 'status (list 'syntax (setq char (ascii char))))
	  (vseparator
;	  (204 (setq spaceflg t)	; separator character
	       (setq spaceflg t)
	       (lispxreadc iport)
	       (go loop))
	  ((vright-paren vright-bracket)
;	  ((196 199) (lispxreadc iport)	; right paren or bracket
	       (lispxreadc iport)
	       (or (car inbuffer) 
		   (and readlineflg (tconc inbuffer nil)))
	       (go eol))
	  (progn (tconc inbuffer (lispxread iport))
		 (setq spaceflg nil)
		 (go loop)))
   eol	(if spaceflg
	    then (lispxreadc iport)
		 (patom '|... |)
		 (drain)
		 (setq spaceflg nil)
		 (go loop)
	    else (return (delq (ascii 10) (car inbuffer))))
	]

(defun printevent (event)
	(msg (eeventnum event) ".  " (eprompt event)
			 (car (einput event)) -D)
	(mapc #'(lambda (x) (msg B x -D)) (cdr (einput event)))
	(msg (B 4) (eresult event))
	]

(defun printhistory (history line)
	(or (car line) (setq line 
			   (list 'from (minus (min lispxmaxprintevents
				 		(length (hevents history)))))))
	(mapc #'printevent (lispxfind history line))
	]

(defun userexec (&optional (lispxid '_))
  (let ((lispxinputbuffer nil) piport)
     (*catch 'exit_userexec_FRAME
	(do nil (nil)
	    (*catch 'userexec-FRAME
		(do nil (nil)
			(msg (cadr lispxhistory) lispxid -N)
			(lispx (lispxread) lispxid)
			(terpri))
		)))
	]

(defun linespecerr (linespec framename)
	(mapc #'(lambda (x) (msg x B -D)) linespec)
	(msg "??" N)
	(*throw framename nil)
	]
		

(or (boundp 'lispxmacros)
    (setq lispxmacros
      (quote
       ((@ apply 'exec lispxline)	; escape to unix procs
	(des lispxdescribe)		; for flavors and objects
	(fl lispxflavor)		; for describe-flavor
	(| EOF| lispxexitp)		; end of file
	(bye lispxbye)
	(? lispxhelp)))))

;
; lispxdescribe added to give easy mechanism for describing flavors
;
(defun lispxdescribe nil
  (describe (eval (car lispxline)))
  (for x in (cdr lispxline)
       do (lispbreak)
	  (describe (eval x))))

;
; lispxflavor added to give easy mechanism for describing a flavor
;
(defun lispxflavor nil
  (describe-flavor (car lispxline))
  (for x in (cdr lispxline)
       do (lispbreak)
	  (describe-flavor x)))

;
;
; lispxexitp and lispxbye added - liz 10/1/82
;
; If the variable clean-on-bye is bound to the name of a function, the
; function is funcall'ed.  The function must return t in order for
; the exit to occur.  If the function is not defined, the exit occurs
; promptly.
;

(defun lispxexitp nil
  (cond ((not (status isatty))
	   (exit))
	((null (status ignoreeof))
	   (msg 'Goodbye)
	   (exit))
	(t 'EOF)))

(declare (special clean-on-bye))

(defun lispxbye nil
  (or (and (boundp 'clean-on-bye)
	   (getd clean-on-bye)
	   (null (funcall clean-on-bye)))
      (progn (msg 'Goodbye)
	     (exit))))

;
; help at top level
;
(defun lispxhelp nil (msg
"??	review recent events
!	redo specified event or last event
@cmd	execute shell command
des x..	calls describe with the value of each x given
fl n..	calls describe-flavor with each name -- not eval'd
bye	exit lisp unless clean-on-bye is bound to a function which
	returns nil
?	get help message at top level and within lispbreak"))



(or (boundp 'lispxmaxprintevents)
    (setq lispxmaxprintevents 10))	; amount for history print
(defun reset-history (num)
	(and (numberp num) (setq lispxhistory (list nil 0 num)))
	]
(or (boundp 'lispxhistory) (reset-history 100))

; The following functions perform the pattern matching used by
;	the historyfind function.  (These functions were to be
;	part of the structure editor originally.)

(defun editfindp (form pat patflg)
	(if (neq patflg t)
	    then (setq pat (editpat pat)))
	(*catch 'editfindp-FRAME (editsearchprintorder pat form))
	]

(defun editsearchprintorder (pattern expression)
	(if (edit4e pattern expression)
	    then (throw t editfindp-FRAME)
	    elseif (dtpr expression)
		   then (mapc #'(lambda (element)
				   (editsearchprintorder pattern element))
				expression)
			 nil)
	]

(defun edit4e (pat form)
  (let (temp)
	(if (eq pat form)
	    elseif (not (dtpr pat))
		   then (equal pat form)
	    elseif (eq (type pat) 'string) 
		   then (equal pat form)
	    elseif (eq (car pat) '*ANY*)
		   then (*catch 'edit4e-FRAME 
			  (progn (mapc #'(lambda (pat1)
					   (if (setq temp (edit43 pat1 form))
					       then (throw temp edit4e-FRAME)))
					(cdr pat))
				 nil))
	    elseif (eq (car pat) '$)
		   then (Edit4eEsc (cdr pat) form)
	    elseif (eq (car pat) '--)
		   then (if (null (cdr pat))
			    else (*catch 'edit4e-FRAME
				    (progn
				      (mapc #'(lambda (form1)
						(if (setq temp 
							  (edit4e pat form1))
						    then (throw temp 
								edit4e-FRAME)))
					     (cdr form))
				       nil)))
	    elseif (eq (car pat) '==)
		   then (eq (cdr pat) form)
	    else (and (dtpr form)
		      (edit4e (car pat) (car form))
		      (edit4e (cdr pat) (cdr form))))
	]

(defun Edit4eEsc (Pattern Expression)
	(if (memq (type Expression) '(symbol string))
	    then (*catch 'Edit4eEsc-FRAME
			 (Edit4eEsc1 Pattern (explode Expression))))
	]

(defun Edit4eEsc1 (Pattern Expression)
	(if (atom Pattern)
	    then (eq Pattern Expression)
	    elseif (eq (car Pattern) '$)
		   then (if (cdr Pattern)
			    then (map #'(lambda (Form)
					  (if (Edit4eEsc1 (cdr Pattern) Form)
					      then (throw Form 
							  Edit4eEsc-FRAME)))
					Expression)
				 nil
			    else t)	 ;trailing <esc> in pattern
	    elseif (eq (car Pattern) (car Expression))
		   then (Edit4eEsc1 (cdr Pattern) (cdr Expression)))
	]

(defun editpat (Pattern)
  (let (UnpackedAtom)
	(if (atom Pattern)
	    then (if (memq (type Pattern) '(symbol string))
		     then (setq UnpackedAtom (explode Pattern))
			  (if (memq '$ UnpackedAtom)
			      then (cons '$ 
					(mapcon #'(lambda (x)
						     (if (neq (car x) (cadr x))
							 then (list (car x))))
						UnpackedAtom))
			      else Pattern)
		     else Pattern)
	    else (mapcar #'editpat Pattern))
	]
