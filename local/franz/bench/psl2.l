; compatibility package
(def de (macro (x) (cons 'defun (cdr x))))
;old: (def igreaterp (macro (x) (cons '> (cdr x))))
(def igreaterp (macro (x) (cons '>& (cdr x))))
;old: (def ilessp (macro (x) (cons '< (cdr x))))
(def ilessp (macro (x) (cons '<& (cdr x))))
(def iadd1 (macro (x) (cons '1+ (cdr x))))
(def isub1 (macro (x) (cons '1- (cdr x))))
(def itimes2 (macro (x) (cons '* (cdr x))))
(declare (special TestList TestList2))

(de PrepareTest (n)
   (prog (list i)
      (setq i 0 list nil)
      top
      (cond ((ilessp n i) (return list)))
      (setq i (iadd1 i)
	    list (cons nil list))
      (go top)))
	    
      
(de RealEmptyTest ()
   (prog (l1 l2)
      (setq l1 TestList)
      top
      (setq l2 TestList)
      again
      (cond ((null (setq l2 (cdr l2)))
	     (cond ((null (setq l1 (cdr l1)))
		    (return nil))
		   (t (go top))))
	    (t (go again)))))

(de RealEmptyTest2 ()
   (prog (l1 l2)
      (setq l1 TestList2)
      top
      (setq l2 TestList2)
      again
      (cond ((null (setq l2 (cddr l2)))
	     (cond ((null (setq l1 (cddr l1)))
		    (return nil))
		   (t (go top))))
	    (t (go again)))))

(defun time ()
   (prog (time)
      (setq time (ptime))
      (return (list (* 17 (car time)) (* 17 (cadr time))))))

(def TimeEval
   (macro (Form)
	  (list
	     'prog '(start end gctime totaltime)
	     '(setq start (time))
	     (cadr Form)
	     '(setq end (time))
	     '(setq totaltime (difference (car end) (car start))
		    gctime (difference (cadr end) (cadr start)))
	     '(return (list 'run (difference totaltime gctime)
			    'gc gctime
			    'total totaltime)))))

(setq TestList (PrepareTest 1000))
(setq TestList2 (PrepareTest 2000))

(de benchmark nil
   (princ "RealEmptyTest 1000000 ")
   (princ (TimeEval (RealEmptyTest)))
   (terpr)
   (princ "RealEmptyTest2 1000000 ")
   (princ (TimeEval (RealEmptyTest2)))
   (terpr))

(sstatus translink t)
