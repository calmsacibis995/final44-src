;;; START OF BENCHMARK

;;; These specials are referred to globally, so you might want
;;; to do a GLOBALVARS definition here. PLACE is a function that returns
;;; a fixnum

(declare (special size classmax typemax d)
	 (fixnum (place fixnum fixnum)
		 size classmax typemax d))

;;; This is used to make the code late look good. The syntax #.TRUE makes the
;;; reader substitute the value of TRUE into the read stream

(setq true t false ())
(declare (setq true t false ()))

;;; This is for the testing printout, which I will show later

;(defmacro tab () '(tyo 9.))

;;; Here are the values of those globals

(setq size 511.)
(setq classmax 3.)
(setq typemax 12.)
(setq d 8.)

(declare (special iii kount)
	 (fixnum iii i j k kount m n))

;;; PIECECOUNT, CLASS, and PIECEMAX are 1 dimensional, fixnum arrays,
;;; and PUZZLE and P are pointer arrays with 1 dimension

(declare (array* (fixnum piececount 1 class 1 piecemax 1)
		 (notype puzzle 1 p 2)))

;;; MacLisp has 0-based arrays, and we need to go from 1 up to classmax

(array piececount fixnum (1+ classmax))
(array class fixnum (1+ typemax))
(array piecemax fixnum (1+ typemax))
(array puzzle t (1+ size))
(array p t (1+ typemax) (1+ size))

;;; In PASCAL this was:
;;; function fit (i : pieceType; j : position) : boolean;
;;;
;;; label	1;
;;; var	k	:	position;
;;;
;;; begin
;;;	fit := false;
;;;	for k := 0 to pieceMax[i] do
;;;		if p[i,k] then if puzzle[j+k] then goto 1;
;;;	fit := true;
;;; 1:
;;; end;
;;; Great style, eh?

(defun fit (i j)
 (let ((end (piecemax i)))
      (do ((k 0 (1+ k)))
	  ((> k end) #.true)
	  (cond ((p i k)
		 (cond ((puzzle (+ j k))
			(return #.false))))))))

;;; The commented stuff is for the optional printout
;;; (store (puzzle i) <value>) stores <value> into the ith position of
;;; the array PUZZLE.

(defun place (i j)
       (let ((end (piecemax i)))
	    (do ((k 0 (1+ k)))
		((> k end))
		(cond ((p i k) 
		       (store (puzzle (+ j k)) #.true))))
		 (store (piececount (class i)) (- (piececount (class i)) 1))
	    (do ((k j (1+ k)))
		((> k size)

;		 (terpri)
;		 (princ "Puzzle filled") 

		 0)
		(cond ((not (puzzle k))
		       (return k))))))

(defun remove (i j)
       (let ((end (piecemax i)))
	    (do ((k 0 (1+ k)))
		((> k end))
		(cond ((p i k) (store (puzzle (+ j k)) #.false))))
	    (store (piececount (class i)) (+ (piececount (class i)) 1))))

(defun trial (j)
       (let ((k 0))
	    (do ((i 0 (1+ i)))
		((> i typemax) (setq kount (1+ kount)) 
			       #.false)
		(cond ((not (= (piececount (class i)) 0))
		       (cond ((fit i j)
			      (setq k (place i j))
			      (cond ((or (trial k)
					 (= k 0))

;				     (terpri)
;				     (princ "Piece") (tab)
;				     (princ (+ i 1)) (tab)
;				     (princ "at")(tab)(princ (+ k 1))

				     (setq kount (+ kount 1))
				     (return #.true))
				    (t (remove i j))))))))))

(defun definepiece (iclass ii jj kk)
       (let ((index 0))
	    (do ((i 0 (1+ i)))
		((> i ii))
		(do ((j 0 (1+ j)))
		    ((> j jj))
		    (do ((k 0 (1+ k)))
			((> k kk))
			(setq index  (+ i (* d (+ j (* d k)))))
			(store (p iii index) #.true))))
	    (store (class iii) iclass)
	    (store (piecemax iii) index)
	    (cond ((not (= iii typemax))
		   (setq iii (+ iii 1))))))

;;; This is the initialization and testing function

(defun start ()
       (do ((m 0 (1+ m)))
	   ((> m size))
	   (store (puzzle m) #.true)) 
       (do ((i 1 (1+ i)))
	   ((> i 5))
	   (do ((j 1 (1+ j)))
	       ((> j 5))
	       (do ((k 1 (1+ k)))
		   ((> k 5))
		   (store (puzzle (+ i (* d (+ j (* d k))))) #.false))))
       (do ((i 0 (1+ i)))
	   ((> i typemax))
	   (do ((m 0 (1+ m)))
	       ((> m size))
	       (store (p i m) #.false)))
       (setq iii 0)
       (definePiece 0 3 1 0)
       (definePiece 0 1 0 3)
       (definePiece 0 0 3 1)
       (definePiece 0 1 3 0)
       (definePiece 0 3 0 1)
       (definePiece 0 0 1 3)

       (definePiece 1 2 0 0)
       (definePiece 1 0 2 0)
       (definePiece 1 0 0 2)

       (definePiece 2 1 1 0)
       (definePiece 2 1 0 1)
       (definePiece 2 0 1 1)

       (definePiece 3 1 1 1)

       (store (pieceCount 0) 13.)
       (store (pieceCount 1) 3)
       (store (pieceCount 2) 1)
       (store (pieceCount 3) 1)
       (let ((m (+ 1 (* d (+ 1 d))))
	     (n 0)(kount 0))
	    (cond ((fit 0 m) (setq n (place 0 m)))
		  (t (terpri)(princ "Error")))
	    (cond ((trial n) 
		   (terpri)(princ "success in ")(princ kount) (princ " trials")) 
		  (t (terpri)(princ "failure"))) 
	    (terpri)))

;;; Here's how I time it at SAIL
(defun timit ()
       ((lambda (t1 x gt)
		(start)
		(setq t1 (- (runtime) t1))
		(setq gt (- (status gctime) gt))
		(print (list 'runtime
			     (//$ (float  (- t1 gt))
				  1000000.0)))
		(print (list 'gctime
			     (//$ (float gt) 1000000.0))))
	(runtime) ()(status gctime)))

;;; END OF BENCHMARK

Here's what it types out in verbose mode (those commented out lines
put back in) when I do (TIMIT). Use this to debug your version. 

Puzzle filled
Piece	1	at	1
Piece	8	at	354
Piece	7	at	330
Piece	3	at	291
Piece	13	at	278
Piece	12	at	276
Piece	5	at	275
Piece	1	at	267
Piece	1	at	219
Piece	3	at	203
Piece	1	at	202
Piece	1	at	154
Piece	9	at	138
Piece	2	at	110
Piece	2	at	108
Piece	1	at	106
Piece	3	at	90
success in 2005 trials
(RUNTIME 8.736) 
(GCTIME 0.363) 
T 

This is what it types without the printing stuff

success in 2005 trials
(RUNTIME 8.736) 
(GCTIME 0.363) 
T 

Have fun with this one.
			-rpg-


