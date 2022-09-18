(declare (special interpret-mode))

(include ldeclar)

(defun defmvar macro (decl)
  `(defvar ,@(cdr decl)))

(defmvar interpret-mode nil 
  |True if user wants files loaded in interpretively|)

(defun loadfiles files
  (mapc '(lambda (file) 
		 (cond (interpret-mode (patom '|[Loading: |)
				       (patom file)
				       (patom '|]|)
				       (terpri)
				       (load (concat file '|.l|)))
		       (t (load file))))
	(listify files))
  nil)

(defun initial-syntax ()
  (setsyntax '/[ 'macro 'readbracketlist)
  (setsyntax '/] 66.)
  )

(defun frl-syntax ()
  ;;;   (setsyntax '/$ 'macro '/$-readmacro) 
  ;;;	This was the "$" readmacro which causes problems.
  (setsyntax '/@ 'macro '/@-readmacro)
  (setsyntax '/% 'macro '/%-readmacro)
  (setsyntax '/! 'macro '/!-readmacro)
  (setsyntax '/& 'macro '/&-readmacro))

(Def Macro (macro (L) `(Def ,(cadr L)
			    (Macro ,(caddr L)
				   (Progn ,.(cdddr L))))))

(Defun linel (tty) 80)

(Defun charpos (tty) (nwritn tty))

(defun readbracketlist nil
  (do ((x (read) (read)) (list nil))
      ((eq x '/]) (cons 'list (nreverse list)))
      (setq list (cons (cond ((and (not (atom x)) (eq (car x) 'atsign)) (cadr x))
			     ((and (eq (typep x) 'list) (eq (car x) 'list)) x)
			     ((list 'quote x))) list))))

;;; (defun /readmacro () (list 'altmode (read)))
(DEFUN /@-READMACRO NIL (LIST 'ATSIGN (READ)))
(DEFUN /%-READMACRO NIL (LIST 'PERCENTSIGN (READ)))
(DEFUN /!-READMACRO NIL (LIST 'EXCLAMATION (READ)))
(DEFUN /&-READMACRO NIL (LIST 'AMPERSAND (READ)))

;;
;;	Modification to the pp to print '@', '%', '!', and '&' .
;;	This version comes with opus 36 franz lisp.
;;
(putprop 'atsign '|@| 'printmacrochar)
(putprop 'percentsign '|%| 'printmacrochar)
(putprop 'exclamation '|!| 'printmacrochar)
(putprop 'ampersand '|&| 'printmacrochar)

(defun frl-define-switches ()
  ;; Controls FRL tracing; FTRACE package is autoloadable, but these 
  ;; switches are needed always. Several other flags are used throughout 
  ;; FRL. They are set when the files are read. See INITIALIZE-SWITCHES (in
  ;; FDUMP) for a list of them along with their default values.
  (setq *trace-create* nil   *trace-destroy* nil   *trace-if-added* nil
	*trace-if-removed* nil   *trace-if-needed* nil   *trace-instantiate*
	nil)
  (comment switches)
  ;; LISP Switches
  (setq prin1 '/#prin1)	; Set top level print to pretty print.
  ;; FRL Switches
  (setq *frames* nil)         ; the system frame list
  (setq *new-frames* nil)     ; the system "new frame" list
  (setq fassert t)            ; interpret fassert forms
  (setq deframe t)            ; interpret DEFRAME forms
  (setq *fgensym* 0)          ; counter used to generate unique frame names.
  (setq *verbose* nil)
  (setq *debug* nil)
  (setq *break-on-warning* nil *break-on-error* nil))

(defun loadlisplibrary ()
  ((lambda (interpret-mode)		; always load compiled version of 
					; the lisp library files.
	   ;;(loadfiles  '//usr//lib//lisp//auxfns1
		       ;;'//usr//lib//lisp//backquote
		       ;;'//usr//lib//lisp//auxfns0
		       ;;'//usr//lib//lisp//toplevel
		       ;;'//usr//lib//lisp//machacks)
	   (loadfiles 
	    'auxfns1
	    'backquote
	    'auxfns0
	    'toplevel
	    'machacks))
   nil))

;;;
;;;
;;;                 FRL Utility Files
;;;
(defun frl-utility-load ()
  (loadfiles 'frl//util//cntrl
	     'frl//util//set
	     'frl//util//util
	     'frl//util//sutil
	     'frl//util//ftrace))

;;
;;	We only need macros at compile time thus, we only load them in.
;;
;;	frl-utility-macro-load loads only the utility files needed at compile time.
;;
(defun frl-utility-macro-load ()
  (loadfiles 'frl//util//cntrl
	     'frl//util//set
	     'frl//util//util))
;;;
;;;            Basic FRL  Files
;;;

(defun frl-basic-load ()
  (loadfiles 'frl//faccess
	     'frl//fmacro
	     'frl//futil
	     'frl//flist
	     'frl//fherit
	     'frl//fassert
	     'frl//raccess
	     'frl//freq
	     'frl//ttyio
	     'frl//fdump
	     'frl//fask
	     'frl//thing
	     'frl//thing1))

;;
;;	at compile time for files in frl/ and a few others, we need to
;;	load the following files of macros and initial functions.
;;

(defun frl-basic-macro-load ()
  (loadfiles 'frl//faccess
	     'frl//fassert
	     'frl//fmacro
	     'frl//raccess))

(defun dhl-macro-load ()
  (loadfiles 'dhl//rule
	     'dhl//domain))

(defun dhl-load ()
  (loadfiles 'dhl//rframes
	     'dhl//rule
	     'dhl//domain
	     'dhl//rule2
	     'dhl//satisfy
	     'dhl//cmatch))

;;;
;;;                   Oil Stuff - a demo for frl with oil shipments.
;;;

(defun oil-load ()
  (loadfiles 'oil//foil
	     'oil//oil
	     'oil//demo))

(defun talk-load ()
  (loadfiles 'talk//pidgin
	     'talk//ftalk0
	     'talk//frmish
	     'talk//rulish)
  (talk))

(defun rule-load ()
  (loadfiles 'rule//sentin
	     'rule//rule
	     'rule//rtemp
	     ;;;"think"
	     ))


;;; This redefinition of #princ is necessary until the print package is
;;; up. Request also does not work until the bug to progv is fixed in
;;; a later version of FRANZ (if then). Also the following alternative
;;; to shout seems as good and is simpler that the set of shout functions
;;; which do not do in FRANZ what they did in maclisp.

(defun /#princ (x) (princ x))

;;; ttyio has a redefinition of prin1 and #prin1 for the same reason

(defun speak (message)
       (prog ()
             (setq message (squash message))
             (terpri)
             loop
             (cond (message (princ (car message))
                            (princ '| |)
                            (setq message (cdr message))
                            (go loop))
                   (t (return t)))))

(defun squash (s)
         (cond ((null s) nil)
               ((atom s) (list s))
               (t (append (squash (car s))
                          (squash (cdr s))))))


;;; There is a request5 function in ttyio to use until progv is fixed.
;;; There is also a request6 function for the same reason.

;;
;; define #print like this for now until it is replaced.
;;
(defun /#print macro (x)
  `(mapc '(lambda (y)
		  ($prpr y)
		  (terpri))
	 ,@(cdr x)))
