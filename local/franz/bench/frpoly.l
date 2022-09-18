;Date: 23 Apr 1981 1330-PST (Thursday)
;From: RPG@SU-AI
;Subject: FRANZ Benchmark    
;To:   lisptranslators at SU-AI   
;
;Here, below, is the benchmark from Berkeley. It is in roughly
;MacLisp syntax, but let me point out a few things about it.
;
;First, DEFMACRO and the ` (backquote) syntax. DEFMACRO is
;a mechanism for defining macros in MacLisp in which the form
;is broken into named arguments, unlike standard MacLisp macros
;with have exactly 1 argument which is the macro form itself (EQly
;that form). The backquote syntax takes a form and produces code
;to generate that form. A example helpe here:
;
;	`(atom ,e) turns into (list 'atom e)
;	`(signp e ,x) is (list 'signp 'e x)
;
;Thus, , (comma) is the unquoting character.
;For example, then, occurrences of (pcoefp x) in the code
;below turn into (atom x) by the action of the macro
;pcoefp. DEFMACRO provides a form which is substituted for
;the calling form with arguments bound in the obvious manner.
;Here is the equivalent standard MacLisp macro definition of
;pcoefp:
;
;	(defun pcoefp macro (x)
;	       (list 'atom (cadr x)))
;
;To run this benchmark interpretively, I suggest expanding the
;macros once, either at read time or at first runtime. For those
;who need it I can provide this file with macros expanded.
;
;Another hack for defining these macros so that they are expanded
;once only is:
;
;(defun pcoefp macro (x)
;  ((lambda (form)
;    (rplaca x (car form))
;    (rplacd x (cdr form))
;    form)		   ;value of RPLACD assumed to be undefined
;   (list 'atom (cadr x))))
;
;LOCALF seems to be a declaration of LOCAL function names. For MacLisp
;I've commented this out. SPECIAL means that there is a global
;value cell and that binding is dynamic on that cell.
;
;Here is what SIGNP does:
;
;2) SIGNP IS NOW A FSUBR.  THE FIRST ITEM IN THE ARGLIST IS AN
;INDICATOR FOR COMPARISON TO ZERO, E.G., (SIGNP LE N) IS NON-NIL
;IF AND ONLY IF THE VALUE OF N IS A NUMBER LESS THAN OR EQUAL TO 
;ZERO [SIGNP DOES NOT REQUIRE N TO BE OF NUMBER TYPE].  THE
;INDICATORS FOLLOW THE PDP-10 ARITHMETIC COMPARISON INSTRUCTIONS, AND
;SHOULD BE SELF EXPLANATORY:  L E LE GE N G 
;[E means zerop, N means not zerop.]
;
;(RUNTIM) and (STATUS GCTIME) return the number of microseconds of
;total runtime and gctime. Note that gctime is included in
;runtime in MacLisp.
;
;There is a difference between `+' and `PLUS' in Franz, which is
;that + takes 2 arguments, both fixnums (machine integers) and returns
;a fixnum as its result. PLUS takes any number of any type of number and
;returns the most appropriate type number. In the tests below, one of them
;is designed to overflow the VAX machine integer range and drift into
;BIGNUMs, which are any integer larger than the architecture supports. In MacLisp
;and FRANZ there is a BIGNUM packake that allows one to have contiguous
;words of memory represent one number. So, beware of where there are +'s and
;PLUS's. The same is true for - and DIFFERENCE, * and TIMES, / and QUOTIENT,
;> and GREATERP, < and LESSP, etc. Generic arithmetic is closed compiled
;while specific type is open coded.
;
;(ODPP x) tests if X is odd.
;
;= is numeric EQUAL.
;
;PDIFFER1 is mentioned but not defined; is not called for these tests, however.
;
;Here's my transcript of SAIL MacLisp:
;
;(setup)
;(Z 1 1.0 0 (Y 1 1.0 0 (X 1 1.0 0 1.0))) 
;(bench 2)
;(POWER= 2 (0.017 0.0) (0.017 0.0) (0.016 0.0)) 
;(bench 5)
;(POWER= 5 (0.116 0.0) (1.334 1.084) (0.15 0.0)) 
;(bench 10)
;(POWER= 10 (2.534 1.8) (19.733 17.151) (8.983 7.901)) 
;(bench 15)
;(POWER= 15 (16.65 8.832) (112.516 89.298) (63.9 56.749)) 
;
;Which I ran compiled. Times are in seconds.
;
;The following is the benchmark. 
;			-rpg-
;

;;;; Benchmark Commences:

;;; Franz Lisp benchmark from Fateman
;; test from Berkeley based on polynomial arithmetic.

(declare (special ans coef f inc i k qq ss v *x*
		    *alpha *a* *b* *chk *l *p q* u* *var *y*
		    r r2 r3 start res1 res2 res3)
   (special float-format))
'(declare (localf pcoefadd pcplus pcplus1 pplus ptimes ptimes1
		 ptimes2 ptimes3 psimp pctimes pctimes1
		 pplus1))

;; if this is an old lisp, translate >& to >
(eval-when (eval compile)
   (or (boundp 'franz-minor-version-number)
       (progn (defmacro >& (x y) `(> ,x ,y))
	      (defmacro =& (x y) `(= ,x ,y)))))


;; Franz uses maclisp hackery here; you can rewrite lots of ways.
(defmacro pointergp (x y) `(>& (get ,x 'order)(get ,y 'order)))

(defmacro pcoefp (e) `(atom ,e))
(defmacro pzerop (x) `(signp e ,x))			;true for 0 or 0.0
(defmacro pzero () 0)
(defmacro cplus (x y) `(plus ,x ,y))
(defmacro ctimes (x y) `(times ,x ,y))


(defun pcoefadd (e c x) (cond ((pzerop c) x)
			      (t (cons e (cons c x)))))

(defun pcplus (c p) (cond ((pcoefp p) (cplus p c))
			  (t (psimp (car p) (pcplus1 c (cdr p))))))

(defun pcplus1 (c x)
       (cond ((null x)
	      (cond ((pzerop c) nil) (t (cons 0 (cons c nil)))))
	     ((pzerop (car x)) (pcoefadd 0 (pplus c (cadr x)) nil))
	     (t (cons (car x) (cons (cadr x) (pcplus1 c (cddr x)))))))
	 
(defun pctimes (c p) (cond ((pcoefp p) (ctimes c p))
			   (t (psimp (car p) (pctimes1 c (cdr p))))))

(defun pctimes1 (c x)
       (cond ((null x) nil)
	     (t (pcoefadd (car x)
			  (ptimes c (cadr x))
			  (pctimes1 c (cddr x))))))

(defun pplus (x y) (cond ((pcoefp x) (pcplus x y))
			 ((pcoefp y) (pcplus y x))
			 ((eq (car x) (car y))
			  (psimp (car x) (pplus1 (cdr y) (cdr x))))
			 ((pointergp (car x) (car y))
			  (psimp (car x) (pcplus1 y (cdr x))))
			 (t (psimp (car y) (pcplus1 x (cdr y))))))

(defun pplus1 (x y)
       (cond ((null x) y)
	     ((null y) x)
	     ((=& (car x) (car y))
	      (pcoefadd (car x)
			(pplus (cadr x) (cadr y))
			(pplus1 (cddr x) (cddr y))))
	     ((>& (car x) (car y))
	      (cons (car x) (cons (cadr x) (pplus1 (cddr x) y))))
	     (t (cons (car y) (cons (cadr y) (pplus1 x (cddr y)))))))

(defun psimp (var x)
       (cond ((null x) 0)
	     ((atom x) x)
	     ((zerop (car x)) (cadr x))
	      (t (cons var x))))

(defun ptimes (x y) (cond ((or (pzerop x) (pzerop y)) (pzero))
			  ((pcoefp x) (pctimes x y))
			  ((pcoefp y) (pctimes y x))
			  ((eq (car x) (car y))
			   (psimp (car x) (ptimes1 (cdr x) (cdr y))))
			  ((pointergp (car x) (car y))
			   (psimp (car x) (pctimes1 y (cdr x))))
			  (t (psimp (car y) (pctimes1 x (cdr y))))))

(defun ptimes1 (*x* y) (prog (u* v)
			       (setq v (setq u* (ptimes2 y)))
			  a    (setq *x* (cddr *x*))
			       (cond ((null *x*) (return u*)))
			       (ptimes3 y)
			       (go a)))

(defun ptimes2 (y) (cond ((null y) nil)
			 (t (pcoefadd (plus (car *x*) (car y))
				      (ptimes (cadr *x*) (cadr y))
				      (ptimes2 (cddr y))))))

(defun ptimes3 (y) 
  (prog (e u c) 
     a1 (cond ((null y) (return nil)))
	(setq e (+ (car *x*) (car y)))
	(setq c (ptimes (cadr y) (cadr *x*) ))
	(cond ((pzerop c) (setq y (cddr y)) (go a1))
	      ((or (null v) (>& e (car v)))
	       (setq u* (setq v (pplus1 u* (list e c))))
	       (setq y (cddr y)) (go a1))
	      ((=& e (car v))
	       (setq c (pplus c (cadr v)))
	       (cond ((pzerop c) (setq u* (setq v (pdiffer1 u* (list (car v) (cadr v))))))
		     (t (rplaca (cdr v) c)))
	       (setq y (cddr y))
	       (go a1)))
     a  (cond ((and (cddr v) (>& (caddr v) e)) (setq v (cddr v)) (go a)))
	(setq u (cdr v))
     b  (cond ((or (null (cdr u)) (< (cadr u) e))
	       (rplacd u (cons e (cons c (cdr u)))) (go e)))
	(cond ((pzerop (setq c (pplus (caddr u) c))) (rplacd u (cdddr u)) (go d))
	      (t (rplaca (cddr u) c)))
     e  (setq u (cddr u))
     d  (setq y (cddr y))
	(cond ((null y) (return nil)))
	(setq e (+ (car *x*) (car y)))
	(setq c (ptimes (cadr y) (cadr *x*)))
     c  (cond ((and (cdr u) (>& (cadr u) e)) (setq u (cddr u)) (go c)))
	(go b))) 

(defun pexptsq (p n)
	(do ((n (quotient n 2) (quotient n 2))
	     (s (cond ((oddp n) p) (t 1))))
	    ((zerop n) s)
	    (setq p (ptimes p p))
	    (and (oddp n) (setq s (ptimes s p))) ))

(defun setup nil
  (putprop 'x 1 'order)
  (putprop 'y 2 'order)
  (putprop 'z 3 'order)
  (setq r (pplus '(x 1 1 0 1) (pplus '(y 1 1) '(z 1 1)))) ; r= x+y+z+1
  (setq r2 (ptimes r 100000)) ;r2 = 100000*r
  (setq r3 (ptimes r 1.0)); r3 = r with floating point coefficients
  )

;; in order to run this in older lisps:

; time various computations of powers of polynomials, not counting
;printing but including gc time ; provide account of g.c. time.

; The following function uses (ptime) for process-time and is thus
;  Franz-specific.

#-franz 
  (defmacro ptime () '`(,(runtime) ,(status gctime)))

(defun bench (n)
  (setq start (ptime)) ;  Franz ticks, 60 per sec, 2nd number is GC
  (pexptsq r n) 
  (setq res1 (ptime))
  (pexptsq r2 n)
  (setq res2 (ptime))
  ; this one requires bignums.
  (pexptsq r3 n)
  (setq res3 (ptime))
  (list 'power=  n (b1 start res1)(b1 res1 res2)(b1 res2 res3)))

; given two ptimes, return (total gc cpu) time in seconds
;
(defun b1 (start end)
   (let ((resolution #-franz 1000000.0 #+franz 60.0))
      (list (quotient (- (car end) (car start)) resolution)
	    (quotient (- (cadr end) (cadr start)) resolution)
	    (quotient (- (- (car end) (car start))
			 (- (cadr end) (cadr start)))
		      resolution))))

;instructions:
;  after loading, type (setup)
; then (bench 2) ; this should be pretty fast.
; then (bench 5)
; then (bench 10)
; then (bench 15)
;... 
(defun frp-bench nil
   (setq float-format "%.5G")
   (allocate 'list 500)
   (allocate 'fixnum 100)
   (allocate 'bignum 70)
   (allocate 'flonum 30)
   (setup)
   (print (bench 2)) (terpr)
   (print (bench 5)) (terpr)
   (print (bench 10)) (terpr)
   (print (bench 15)) (terpr))


   


