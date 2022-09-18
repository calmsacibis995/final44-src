(eval-when (eval compile load) (setq ibase 10. obase 10.))

(declare (special pieceCount class pieceMax puzzle p kount)
	 (fixnum m n i j k kount))

(eval-when (eval load compile)
  (setq size 511)
  (setq classMax 3)
  (setq typeMax 12)
  (setq d 8)
  (setq true t)
  (setq false nil))

(setq pieceCount (*array nil 'fixnum (1+ #.classMax)))
(setq class (*array nil 'fixnum (1+ #.typeMax)))
(setq pieceMax (*array nil 'fixnum (1+ #.typeMax)))
(setq puzzle (*array nil t (1+ #.size)))
(setq p (*array nil t (1+ #.typeMax) (1+ #.size)))


(defmacro areff (array . indices)
  `(arraycall fixnum ,array . ,indices))

(defmacro aref (array . indices)
  `(arraycall t ,array . ,indices))

(defun fit (i j)
  (do ((k 0 (1+ k))
       (lim (areff pieceMax i)))
      ((> k lim)
       #.true)
      (if (and (aref p i k)
	       (aref puzzle (+ j k)))
	  (return #.false))))

(defun place (i j)
  (do ((k 0 (1+ k))
       (lim (areff pieceMax i)))
      ((> k lim))
      (if (aref p i k)
	  (setf (aref puzzle (+ j k)) #.true)))
  (setf (areff pieceCount (areff class i))
	(1- (areff pieceCount (areff class i))))
  (do ((k j (1+ k)))
      ((> k #.size)
       (print '|puzzle filled~%|)
       0)
      (if (null (aref puzzle k))
	  (return k))))

(defun remove (i j)
  (do ((k 0 (1+ k))
       (lim (areff pieceMax i)))
      ((> k lim))
      (if (aref p i k)
	  (setf (aref puzzle (+ j k)) #.false)))
  (setf (areff pieceCount (areff class i))
	(1+ (areff pieceCount (areff class i)))))

(defun trial (j)
  (do ((i 0 (1+ i))
       (k 0))
      ((> i #.typeMax)
       (setq kount (1+ kount))
       #.false)
      (if (not (zerop (areff pieceCount (areff class i))))
	  (cond ((fit i j)
		 (setq k (place i j))
		 (cond ((or (trial k) (zerop k))
			(print  '|piece ~d at ~d ~%| )
			(print (1+ i)) (print  (1+ k))
			(setq kount (1+ kount))
			(return #.true))
		       (t (remove i j))))))))

(defmacro fill-pieceMax (nn a b c class)
  `(progn (do i 0 (1+ i) (> i ,a)
	      (do j 0 (1+ j) (> j ,b)
		  (do k 0 (1+ k) (> k ,c)
		      (setf (aref p ,nn (+ i (* #.d (+ j (* #.d k)))))
			    #.true))))
	  (setf (areff class ,nn) ,class)
	  (setf (areff pieceMax ,nn)
		(+ ,a (* ,b #.d) (* ,c #.d #.d)))))

(defun main ()
  (let ((m 0)  (n 0))
       (do m 0 (1+ m) (> m #.size)
	   (setf (aref puzzle m) #.true))
	(print 'startinitit)(terpr) ;-----
       (do i 1 (1+ i) (> i 5)
	   (do j 1 (1+ j) (> j 5)
	       (do k 1 (1+ k) (> k 5)
		   (setf (aref puzzle (+ i (* #.d (+ j (* #.d k)))))
			 #.false))))
	(print 'continit)(terpr) ;-----
       (do i 0 (1+ i) (> i #.typeMax)
	   (do m 0 (1+ m) (> m #.size)
	       (setf (aref p i m) #.false)))
       (print 'initialized)(terpr) ;---debug
       (fill-pieceMax 0 3 1 0 0)
       (fill-pieceMax 1 1 0 3 0)
       (fill-pieceMax 2 0 3 1 0)
       (fill-pieceMax 3 1 3 0 0)
       (fill-pieceMax 4 3 0 1 0)
       (fill-pieceMax 5 0 1 3 0)
       (fill-pieceMax 6 2 0 0 1)
       (fill-pieceMax 7 0 2 0 1)
       (fill-pieceMax 8 0 0 2 1)
       (fill-pieceMax 9 1 1 0 2)
       (fill-pieceMax 10 1 0 1 2)
       (fill-pieceMax 11 0 1 1 2)
       (fill-pieceMax 12 1 1 1 3)
       (print 'endfillpiece)(terpr) ;---jkf
       (setf (areff pieceCount 0) 13)
       (setf (areff pieceCount 1) 3)
       (setf (areff pieceCount 2) 1)
       (setf (areff pieceCount 3) 1)
       (setq m (+ 1 (* #.d (+ 1 (* #.d 1)))))
       (setq kount 0)
       (if (fit 0 m)
	   (setq n (place 0 m))
	   (print  '|error 1~%|))
       (if (trial n)
	   (print  '|success in ~d~%|) (print kount)(terpr)
	   (print  '|failure~%|))))


;; Local Modes:
;; Mode:LISP
;; Fill Column:78
;; Auto Fill Mode:1
;; Comment Column:40
;; END:



