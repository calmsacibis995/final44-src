;
; This is a stripped down version of the original toplevel to be used
; with the U of Maryland userexec (based on INTERLISP's top level) in
; nlispx.  The user may still change the toplevel by setting
; user-top-level to something else; if he sets it to nil, userexec and
; resets, he will go back to using the userexec.  This file also retains
; the autoload code.
;
;				liz 10/82
;

; special atoms:
(declare (special errlist tpl-errlist user-top-level
		  franz-not-virgin piport ER%tpl ER%all
		  $ldprint evalhook funcallhook
		  franz-minor-version-number
		  top-level-eof * ** *** + ++ +++ ^w)
         (localf autorunlisp cvtsearchpathtolist)
	 (macros t))

(setq top-level-eof (gensym 'Q)
      tpl-errlist nil
      errlist nil
      user-top-level nil )

; franz-top-level rewritten to always call userexec - liz 10/5/82

(def franz-top-level (lambda nil
  (cond ((or (not (boundp 'franz-not-virgin))
	     (null franz-not-virgin))
	   (setq franz-not-virgin t)
	   (cond ((not (autorunlisp))
		    (patom (status version))
		    ; franz-minor-version-number defined in version.l
		    (cond ((boundp 'franz-minor-version-number)
			   (patom franz-minor-version-number)))
		    (terpr)
		    (read-in-lisprc-file)))))
  (putd 'reset (getd 'franz-reset))
  ; just call userexec or whatever user-top-level is - liz 10/5/82
  (for do (or (and (boundp 'user-top-level) (getd user-top-level))
	      (setq user-top-level 'userexec))
	  (catch (funcall user-top-level) 'top-level-catch))))


; redefine break to call lispbreak - liz 10/5/82
(defmacro break (message &optional (pred t))
  `(*break ,pred ',message))

(def *break
  (lambda (pred message)
     (let ((^w nil))
	  (cond (pred (terpr)
		      (patom "Break ")
		      (patom message)
		      (terpr)
		      (lispbreak))))))

; this reset function is designed to work with the franz-top-level.
; When franz-top-level begins, it makes franz-reset be reset. 
; when a reset occurs now, we set the global variable tpl-errlist to 
; the current value of errlist and throw to top level.  At top level,
; then tpl-errlist will be evaluated.
(def franz-reset
  (lambda nil
	  (terpr)
	  (setq tpl-errlist errlist)
	  (errset (*throw 'top-level-catch 'reset)
		  nil)
	  (old-reset-function)))


(declare (special $ldprint))

;--- read-in-lisprc-file
; search for a lisp init file.  Look first in . then in $HOME
; look first for .o , then .l and then "",
; look for file bodies .lisprc and then lisprc
; 
(def read-in-lisprc-file
   (lambda nil
      (setq break-level-count 0	; do this in case break
	    debug-level-count 0)   ; occurs during readin
      (*catch '(break-catch top-level-catch)
	      (do ((dirs `("." ,(getenv 'HOME)) (cdr dirs))
		   ($ldprint nil $ldprint))	; prevent messages
		  ((null dirs))
		  (cond ((do ((name '(".lisprc" "lisprc") (cdr name)))
			     ((null name))
			     (cond ((do ((ext '(".o" ".l" "") (cdr ext))
					 (file))
					((null ext))
					(cond ((probef
						  (setq file (concat (car dirs)
								     "/"
								     (car name)
								     (car ext))))
					       (cond ((atom (errset (load file)))
						      (patom
							 "Error loading lisp init file ")
						      (print file)
						      (terpr)
						      (return 'error)))
					       (return t))))
				    (return t))))
			 (return t)))))))

(putd 'top-level (getd 'franz-top-level))

; if this is the first time this file has been read in, then 
; make franz-reset be the reset function, but remember the original
; reset function as old-reset-function.  We need the old reset function
; if we are going to allow the user to change top-levels, for in 
; order to do that we really have to jump all the way up to the top.
(cond ((null (getd 'old-reset-function))
       (putd 'old-reset-function (getd 'reset))))


;---- autoloader functions

(def undef-func-handler
  (lambda (args)
    (prog (funcnam file)
	  (setq funcnam (caddddr args))
	  (cond ((symbolp funcnam) 
		 (cond ((setq file (get funcnam 'autoload))
			(cond ($ldprint
			       (patom "[autoload ") (patom file)
			       (patom "]")(terpr)))
			(load file))
		       (t (return nil)))
		 (cond ((getd funcnam) (return (ncons funcnam)))
		       (t (patom "Autoload file " ) (print file)
			  (patom " does not contain function ")
			  (print funcnam)
			  (terpr)
			  (return nil))))))))

(setq ER%undef 'undef-func-handler)

(declare (special $ldprint))
;--- autorunlisp :: check if this lisp is supposed to run a program right
; away.
;
(defun autorunlisp nil
  (cond ((and (> (argv -1) 2) (equal (argv 1) '-f))
	 (let ((progname (argv 2))
	       ($ldprint nil)
	       (searchlist nil))	; don't give fasl messages
	      (setq searchlist (cvtsearchpathtolist (getenv 'PATH)))
	      ; give two args to load to insure that a fasl is done.
	      (cond ((null 
		      (errset (load-autorunobject progname searchlist)))
		     (exit 0))
		    (t t))))))


(defun cvtsearchpathtolist (path)
  (do ((x (explodec path) (cdr x))
       (names nil)
       (cur nil))
      ((null x) 
       (nreverse names))
      (cond ((or (eq ': (car x)) 
		 (and (null (cdr x)) (setq cur (cons (car x) cur))))
	     (cond (cur (setq names (cons (implode (nreverse cur))
					  names))
			(setq cur nil))
		   (t (setq names (cons '|.| names)))))
	    (t (setq cur (cons (car x) cur))))))

(defun load-autorunobject (name search)
  (cond ((memq (getchar name 1) '(/ |.|))
	 (cond ((probef name) (fasl name))
	       (t (error "From lisp autorun: can't find file to load"))))
	(t (do ((xx search (cdr xx))
		(fullname))
	       ((null xx) (error "Can't find file to execute "))
	       (cond ((probef (setq fullname (concat (car xx) "/" name)))
		      (return (fasl-a-file fullname nil nil))))))))

(defun debug fexpr (args)
  (load 'fix)	; load in fix package
  (eval (cons 'debug args)))	; enter debug through eval

;-- default autoloader properties

(putprop 'trace (concat lisp-library-directory "/trace") 'autoload)
(putprop 'step (concat lisp-library-directory "/step") 'autoload)
(putprop 'editf (concat lisp-library-directory "/cmuedit") 'autoload)
(putprop 'editv (concat lisp-library-directory "/cmuedit") 'autoload)
(putprop 'editp (concat lisp-library-directory "/cmuedit") 'autoload)
(putprop 'edite (concat lisp-library-directory "/cmuedit") 'autoload)

(putprop 'defstruct (concat lisp-library-directory "/struct") 'autoload)
(putprop 'cgol      (concat lisp-library-directory "/cgol")   'autoload)
