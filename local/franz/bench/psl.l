;; file psl.l				-[Sat Feb 27 18:50:41 1982 by jkf]-
; benchmark submitted by griss@utah-20
;
(sstatus translink t)
; Macros to make rest be same in Franz and PSL
(def de (macro (x) (cons 'defun (cdr x))))
;old: (def igreaterp (macro (x) (cons '> (cdr x))))
(def igreaterp (macro (x) (cons '>& (cdr x))))
;old: (def ilessp (macro (x) (cons '< (cdr x))))
(def ilessp (macro (x) (cons '<& (cdr x))))
(def iadd1 (macro (x) (cons '1+ (cdr x))))
(def isub1 (macro (x) (cons '1- (cdr x))))
(def itimes2 (macro (x) (cons '* (cdr x))))
; Preallocate space to avoid GC etc
(allocate 'fixnum 500)
(allocate 'list 500)
(setq $gcprint t)
; The Timer
;; time returns a list (total-cpu-time total-gc-time)
;	where total-cpu-time == total-run-time + total-gc-time
;	time is in 60ths of a second, we adjust to milliseconds
(defun time ()
   (prog (time)
      (setq time (ptime))
      (return (list (* 17 (car time)) (* 17 (cadr time))))))

(defun reclaim () (gc))

(de TestSetup ()
(progn
    (MakeLongList)
    (setq EvalForm '(setq Foo (cadr '(1 2 3))))
    (setq InternName 'SomeReasonablyLongName)))

(de MakeLongList ()
(prog (I)
    (setq LongList '(a b c d e f g h i j k l m n o p q r s t u v w x y z))
    (setq I 0)
loop
    (cond ((igreaterp I 5) (return nil)))
    (setq LongList (append LongList LongList))
    (setq I (iadd1 I))
    (go loop)))

(de EmptyTest (N)  
(prog (I)
    (setq I 0)
loop
    (cond ((igreaterp I N) (return nil)))
    (setq I (iadd1 I))
    (go loop)))

(de SlowEmptyTest (N)
(prog (I)
    (setq I 0)
loop
    (cond ((greaterp I N) (return nil)))
    (setq I (add1 I))
    (go loop)))

(de ReverseTest (N)
(prog (I)
    (setq I 0)
loop
    (cond ((igreaterp I N) (return nil)))
    (reverse LongList)
    (setq I (iadd1 I))
    (go loop)))

(de LengthTest (N)
(prog (I)
    (setq I 0)
loop
    (cond ((igreaterp I N) (return nil)))
    (length LongList)
    (setq I (iadd1 I))
    (go loop)))

(de Fact (N)
    (cond ((ilessp N 2) 1) (t (itimes2 N (Fact (isub1 N))))))

(de ArithmeticTest (N)
(prog (I)
    (setq I 0)
loop
    (cond ((igreaterp I N) (return nil)))
    (Fact 9)
    (setq I (iadd1 I))
    (go loop)))

(de EvalTest (N)
(prog (I)
    (setq I 0)
loop
    (cond ((igreaterp I N) (return nil)))
    (eval EvalForm)
    (setq I (iadd1 I))
    (go loop)))

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

(de tak (x y z)
  (cond ((null (ilessp y x))  z)
	(t (tak (tak (isub1 x) y z)
		(tak (isub1 y) z x)
		(tak (isub1 z) x y)))))

(de gtak (x y z)
  (cond ((null (lessp y x))  z)
	(t (gtak (gtak (sub1 x) y z)
		(gtak (sub1 y) z x)
		(gtak (sub1 z) x y)))))

(declare (localf ltak))

(de ltak (x y z)
  (cond ((null (ilessp y x))  z)
	(t (ltak (ltak (isub1 x) y z)
		(ltak (isub1 y) z x)
		(ltak (isub1 z) x y)))))

(de gtsta (F)
  (prog (I)
    (setq I 1)
Loop
    (cond ((igreaterp I 100000) (return nil)))
    (apply F (list I))
    (setq I (iadd1 I))
    (go Loop)))

(de gtstb (F)
  (prog (I)
    (setq I 1)
Loop
    (cond ((igreaterp I 100000) (return nil)))
    (funcall F I)
    (setq I (iadd1 I))
    (go Loop)))

(de g0 (X) X) 
(de g1 (X) (iadd1 X))

(de nreverse (x)
  (nreconc x nil))

(de nreconc (x y)
 (prog (z)
   L (cond ((atom x) (return y)))
      (setq z x)
      (setq x (cdr x))
      (setq y (rplacd z y))
      (go L)))

(de nnils (N)
  (prog (LST i)
    (setq i 0)
loop
    (cond ((igreaterp i N) (return LST)))
    (setq LST (cons nil LST))
    (setq i (iadd1 i))
    (go loop)))

(de nils (N)
  (setq XX (nnils N))
  N)

(de nr ()
  (setq XX (nreverse XX))
  nil)


;The code used to call it:
(de benchmark ()
;(load 'franz-timer)
(TestSetup)
(princ "EmptyTest 10000		")
(princ (TimeEval (EmptyTest 10000)))
(terpri)
(reclaim)
(princ "SlowEmptyTest 10000	")
(princ (TimeEval (SlowEmptyTest 10000)))
(terpri)
(reclaim)
(princ "ReverseTest 10		")
(princ (TimeEval (ReverseTest 10)))
(terpri)
(reclaim)
(princ "LengthTest 100		")
(princ (TimeEval (LengthTest 100)))
(terpri)
(reclaim)
(princ "ArithmeticTest 10000	")
(princ (TimeEval (ArithmeticTest 10000)))
(terpri)
(reclaim)
(princ "EvalTest 10000		")
(princ (TimeEval (EvalTest 10000)))
(terpri)
(reclaim)
(princ "tak 18 12 6		")
(princ (TimeEval (tak 18 12 6)))
(terpri)
(reclaim)
(princ "gtak 18 12 6		")
(princ (TimeEval (gtak 18 12 6)))
(terpri)
(reclaim)
(princ "ltak 18 12 6		")
(princ (TimeEval (ltak 18 12 6)))
(terpri)
(reclaim)
(princ "gtstb g0		")
(princ (TimeEval (gtstb 'g0)))
(terpri)
(reclaim)
(princ "gtstb g1		")
(princ (TimeEval (gtstb 'g1)))
(terpri)
(reclaim)
)

