; This file contains some functions that are not in older versions of Franz,
; but are used in the Maryland hacks.  I've tried to include all the
; necessary functions, but I can make no guarantees.  Send me mail if you
; have problems.
;				-Liz 10/25/82
;				liz.umcp-cs@udel-relay
;

(setq running-under-old-franz t)

; These are necessary for userexec package
(setsyntax '|!| 2)		; redo
(setsyntax '|@| 66)		; escape to shell

(defun tconc (tcell val)
 (let ((newcell (ncons val)))
  (cond ((null tcell)
	   (cons newcell newcell))
	((null (car tcell))
	   (rplaca tcell newcell)
	   (rplacd tcell newcell)
	   tcell)
	(t (rplacd (cdr tcell) newcell)
	   (rplacd tcell newcell)))))

(defun lconc (tcell lst)
  (cond ((null tcell)
	   (cons lst (last lst)))
	((null (car tcell))
	   (rplaca tcell lst)
	   (rplacd tcell (last lst))
	    tcell)
	(t (rplacd (cdr tcell) lst)
	   (rplacd tcell (last lst)))))

; This should probably be a macro, but since I don't want the file to have
; to be loaded at compile time, I'll make it a function.
(defun neq (x y) (not (eq x y)))

(defun tailp (lst tail)
  (cond ((eq lst tail))
	((atom lst) nil)
	(t (tailp (cdr lst) tail))))

; This is just enough of a getsyntax to make the Maryland calls work
(defun getsyntax (char)
  (selectq (apply 'status (list 'syntax char))
     (204 'vseparator)
     (196 'vright-paren)
     (199 'vright-bracket)
      nil))

; Taken from common2.l and modified slightly

(declare (special poport))

(defun tab n
   (prog (nn prt over)
      (setq nn (arg 1))
      (cond ((> n 1) (setq prt (arg 2)))
	    (t (setq prt poport)))
      (cond ((> (setq over (nwritn prt)) nn)
	     (terpri prt)
	     (setq over 0)))
      (spaces (- nn over) prt)))
