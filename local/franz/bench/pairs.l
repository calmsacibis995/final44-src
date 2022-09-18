;Date:  8 Apr 1981 1428-PST (Wednesday)
;From: RPG@SU-AI
;Subject: Timing benchmark   
;To:   "@LSPTRN.DIS[P,DOC]" at SU-AI   
;
;The following is the first of the timing benchmarks to be tried.  As such
;it is fairly simple. It is simply a combinatorial pairing function that
;takes 2 sets (represented as lists), a matching function, and some other
;constraints, and produces a set of possible pairings of items from each
;set. The example below produces 2592 possible pairings. I've included the
;entire testing program, which is at the bottom, along with the test data,
;which are stored in global variables. Below is reproduced the timings from
;the SAIL KL running with a load average of .75. The output of the test
;program is the number of pairings, the runtime (EBOX time on the KL), and
;the gctime (EBOX time).  The first run involves COREing up in response to
;list space exhaustion, which results in the large gctime for the first
;run: the other runs are in the resulting core images. I suggest you also
;run it a few times to get a stable set of readings.
;
;It would be nice to get some results from you for the LISP meeting at SRI
;on wednesday, but that may not be possible.
;			-rpg-
;2592 
;(RUNTIME 1.948) 	;in seconds
;(GCTIME 29.711) 
;
;2592 
;(RUNTIME 1.887) 
;(GCTIME 2.599) 
;
;2592 
;(RUNTIME 1.886) 
;(GCTIME 2.565) 
;
;2592 
;(RUNTIME 1.892) 
;(GCTIME 1.922) 
;
;2592 
;(RUNTIME 1.895) 
;(GCTIME 1.973) 
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(DEFUN PAIRS (X Y MUST-APPEAR FUN APPLY-CONSTRAINTS CONSTRAINTS
	      NIL-PAIRS) 
       ((LAMBDA (XXX) 
	 (MAPCAN 
	  (FUNCTION(LAMBDA (I) 
	      (PROGN
	       (COND
		(MUST-APPEAR
		 (*CATCH
		  'OUT
		  (PROGN
		   (MAPC 
		    (FUNCTION(LAMBDA (I) (COND ((MEMBER (CDR I) MUST-APPEAR)
					 (*THROW 'OUT T)))))
		    I)
		   NIL)))
		(T)))
	      (LIST I)))
	  XXX)) 
	(MAPCAR (FUNCTION(LAMBDA (I) (CDR I)))
		(COND ((< (LENGTH X)
			  (+ (COND (NIL-PAIRS 1) (T 0)) (LENGTH Y)))
		       (PAIRS1 (MAKE-POSSIBILITY-1 X
						   Y
						   FUN
						   APPLY-CONSTRAINTS
						   CONSTRAINTS
						   NIL-PAIRS)))
		      (T (PAIRS2 (MAKE-POSSIBILITY-2 Y
						     X
						     FUN
						     APPLY-CONSTRAINTS
						     CONSTRAINTS
						     NIL-PAIRS)))))))


(DEFUN MAKE-POSSIBILITY-1 (X Y FUN APPLY-CONSTRAINTS CONSTRAINTS
			   NIL-PAIRS) 
       ((LAMBDA (N) 
	 ((LAMBDA (Q) 
	   (COND
	    (NIL-PAIRS (MAPC (FUNCTION(LAMBDA (I) (RPLACD I
						   (LIST* '(NIL)
							  (CDR I)))))
			     Q))
	    (Q)))
	  (MAPCAN 
	   (FUNCTION(LAMBDA (I) 
	      (PROGN
	       (SETQ N 0)
	       ((LAMBDA (A) (AND A
				 (OR (NULL CONSTRAINTS)
				     (NULL APPLY-CONSTRAINTS)
				     (FUNCALL APPLY-CONSTRAINTS
					      CONSTRAINTS))
				 (LIST (LIST* I A))))
		(MAPCAN 
		 (FUNCTION(LAMBDA (J) ((LAMBDA (Q) (COND (Q (NCONS Q))))
				(PROGN (SETQ N (1+ N))
				       (COND ((OR (NULL FUN)
						  (FUNCALL FUN I J))
					      (LIST* N J)))))))
		 Y)))))
	   X)))
	0))


(DEFUN MAKE-POSSIBILITY-2 (X Y FUN APPLY-CONSTRAINTS CONSTRAINTS
			   NIL-PAIRS) 
       ((LAMBDA (N) 
	 ((LAMBDA (Q) 
	   (COND
	    (NIL-PAIRS (MAPC (FUNCTION(LAMBDA (I) (RPLACD I
						   (LIST* '(NIL)
							  (CDR I)))))
			     Q))
	    (Q)))
	  (MAPCAN 
	   (FUNCTION(LAMBDA (I) 
	      (PROGN
	       (SETQ N 0)
	       ((LAMBDA (A) (AND A
				 (OR (NULL CONSTRAINTS)
				     (NULL APPLY-CONSTRAINTS)
				     (FUNCALL APPLY-CONSTRAINTS
					      CONSTRAINTS))
				 (LIST (LIST* I A))))
		(MAPCAN 
		 (FUNCTION(LAMBDA (J) ((LAMBDA (Q) (COND (Q (NCONS Q))))
				(PROGN (SETQ N (1+ N))
				       (COND ((OR (NULL FUN)
						  (FUNCALL FUN J I))
					      (LIST* N J)))))))
		 Y)))))
	   X)))
	0))


(DEFUN PAIRS1 (L) 
       (COND
	((NULL L) '((NIL)))
	(T
	 ((LAMBDA (CAND POSS) 
	   (MAPCAN 
	    (FUNCTION(LAMBDA (PAIRS) 
	       (PROGN
		((LAMBDA (AVOID ANS) 
		  (MAPCAN 
		   (FUNCTION(LAMBDA (I) 
			     ((LAMBDA (Q) (COND (Q (NCONS Q))))
			      (PROGN (COND ((CAR (MEMBER (CAR I)
							 AVOID))
					    (LIST* AVOID ANS))
					   (T (LIST* (LIST* (CAR I)
							    AVOID)
						     (LIST* CAND
							    (CDR I))
						     ANS)))))))
		   POSS))
		 (CAR PAIRS)
		 (CDR PAIRS)))))
	    (PAIRS1 (CDR L))))
	  (CAAR L)
	  (CDAR L)))))


(DEFUN PAIRS2 (L) 
       (COND
	((NULL L) '((NIL)))
	(T
	 ((LAMBDA (CAND POSS) 
	   (MAPCAN 
	    (FUNCTION(LAMBDA (PAIRS) 
	       (PROGN
		((LAMBDA (AVOID ANS) 
		  (MAPCAN 
		   (FUNCTION(LAMBDA (I) 
			     ((LAMBDA (Q) (COND (Q (NCONS Q))))
			      (PROGN (COND ((CAR (MEMBER (CAR I)
							 AVOID))
					    (LIST* AVOID ANS))
					   (T (LIST* (LIST* (CAR I)
							    AVOID)
						     (LIST* (CDR I)
							    CAND)
						     ANS)))))))
		   POSS))
		 (CAR PAIRS)
		 (CDR PAIRS))))) 
	    (PAIRS2 (CDR L))))
	  (CAAR L)
	  (CDAR L)))))

(declare (special a b))
(setq a '(
	  (1 2)
	  (7 8)
	  (9 0)
	  (a b c)
	  (a b c)
	  (d e f)
	  (d e f)
	  (g h i)
	  (g h i)
	  (j k l)
	  (m n o)
	  (p q r)
	  ))
(setq b '(
	  (a b c)
	  (j k l)
	  (d e f)
	  (p q r)
	  (g h i)
	  (9 0)
	  (a b c)
	  (p q r)
	  (7 8)
	  (j k l)
	  (2 1)
	  (3 2)
	  (8 7)
	  (9 8)
	  (0 9)
	  (m n o)
	  (d e f)
	  (j k l)
	  (m n o)
	  (d e f)
	  (p q r)
	  (g h i)
	  ))

(defun test ()
 ((lambda (t1 x gt)
	  (setq x (pairs a b () 'equal () () ()))
	  (setq t1 (- #-Franz (runtime) 
		      #+Franz (car (ptime)) 
		      t1))
	  (setq gt (- #-Franz (status gctime)
		      #+Franz (cadr (ptime)) 
		      gt))
	  (print (length x))
	  (print (list 'runtime
		       (QUOTIENT (FLOAT  (- t1 gt))
				 #-Franz 1000000.
				 #+Franz 60.)))
	  (print (list 'gctime
		       (quotient (float gt) 
				 #-Franz 1000000.
				 #+Franz 60.)))
	  #+Franz (terpri))
  #-Franz (runtime) #+Franz (car (ptime)) 
  ()
  #-Franz (status gctime)
  #+Franz (cadr (ptime))))

(defun endoffuncs nil nil)


