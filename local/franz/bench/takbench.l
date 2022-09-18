;; tak					-[Mon Apr 26 08:48:39 1982 by jkf]-
;;	tak benchmarks	for lisp timing project
;;
(eval-when (compile eval)
   (or (get 'benchmac 'version) (load 'benchmac)))
(eval-when (load eval)
   (or (get 'format   'version) (load 'format)))

(declare (localf tak-loc takl-loc listgeqp-loc)) 

;--- benchmark   : do all benchmarks
;
(defun benchmark (reps)
   (format t "Tak Benchmarks~%")
   (format t "generic, slow links (translink nil)~%")
   (tak-gen-bench reps)
   (format t "~%generic, fast links (translink t)~%")
   (sstatus translink on)
   (tak-gen-bench reps)
   (format t "~%~%fixnum, slow links ~%")
   (sstatus translink nil)
   (tak-bench reps)
   (format t "~%fixnum, fast links ~%")
   (sstatus translink on)
   (tak-bench reps)
   
   (format t "~2%local functions~%")
   (tak-loc-bench reps)
   
   (sstatus translink nil)
   (format t "~2%takl: tak with lists ~%")
   (format t "slow links~%")
   (takl-bench reps)
   (format t "~%fast links~%")
   (sstatus translink on)
   (takl-bench reps)
   (format t "~%local functions~%")
   (takl-loc-bench reps)
   
   (format t "~3%takf: tak with funcalls~%")
   (sstatus translink nil)
   (format t " slow links~%")
   (takf-bench reps)
   (format t "~% fast links~%")
   (sstatus translink on)
   (takf-bench reps))

(defun tak-bench (n) (benchmac (tak 18 12 6)))
(defun tak-loc-bench (n) (benchmac (tak-loc 18 12 6)))
(defun tak-gen-bench (n) (benchmac (tak-gen 18 12 6)))
(defun takf-bench (n) (benchmac (takf 18 12 6)))
(defun takl-bench (n)
   (benchmac (takl '(t t t t t  t t t t t  t t t t t  t t t)
		   '(t t t t t  t t t t t  t t)
		   '(t t t t t  t))))
(defun takl-loc-bench (n)
   (benchmac (takl-loc '(t t t t t  t t t t t  t t t t t  t t t)
		       '(t t t t t  t t t t t  t t)
		       '(t t t t t  t))))

;--- tak :
;  standard tak, using fixnum functions
(defun tak (x y z)
   (cond ((not (<& y x))
	  z)
	 (t (tak (tak (1- x) y z)
		 (tak (1- y) z x)
		 (tak (1- z) x y)))))

;--- takx : tak with checking for minimum value.
; this is not benchmarked but it does provide interesting results
;
(declare (special minx miny minz))
(defun init () (setq minx 1000 miny 1000 minz 1000))
(defun takx (x y z)
   (cond ((<& x minx)(setq minx x)))
   (cond ((<& y miny)(setq miny y)))
   (cond ((<& z minz)(setq minz z)))
   (cond ((not (<& y x))
	  z)
	 (t (takx (takx (1- x) y z)
		  (takx (1- y) z x)
		  (takx (1- z) x y)))))
;--- tak-gen
;  generic arith tak
(defun tak-gen (x y z)
   (cond ((not (lessp y x))
	  z)
	 (t (tak-gen (tak-gen (sub1 x) y z)
		     (tak-gen (sub1 y) z x)
		     (tak-gen (sub1 z) x y)))))

;--- tak-loc
; like generic tak, but declared as a local function
;
(defun tak-loc (x y z)
   (cond ((not (<& y x))
	  z)
	 (t (tak-loc (tak-loc (1- x) y z)
		     (tak-loc (1- y) z x)
		     (tak-loc (1- z) x y)))))

;--- takf
; tak with funcalls
;
(defun takf (x y z)
   (takfsub #'takfsub x y z))

(defun takfsub (f x y z)
   (cond ((not (<& y x))
	  z)
	 (t (funcall f f (funcall f f  (1- x) y z)
		     (funcall f f (1- y) z x)
		     (funcall f f (1- z) x y)))))

;;--- takl : tak using lists as counters
;
(defun takl (x y z)
   (cond ((listgeqp y x) z)
	 (t (takl (takl (cdr x) y z)
		  (takl (cdr y) z x)
		  (takl (cdr z) x y)))))

;--- listgeqp : t iff list a is longer or the same size as b
;
(defun listgeqp (a b)
   (cond ((null b) t)
	 ((null a) nil)
	 (t (listgeqp (cdr a) (cdr b)))))

;--- local versions of the above
;
(defun takl-loc (x y z)
   (cond ((listgeqp-loc y x) z)
	 (t (takl-loc (takl-loc (cdr x) y z)
		      (takl-loc (cdr y) z x)
		      (takl-loc (cdr z) x y)))))

;--- listgeqp : t iff list a is longer or the same size as b
;
(defun listgeqp-loc (a b)
   (cond ((null b) t)
	 ((null a) nil)
	 (t (listgeqp-loc (cdr a) (cdr b)))))
