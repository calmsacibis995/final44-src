;Date: 26 Feb 1981 1147-PST (Thursday)
;From: fateman
;To: jkf
;Subject: wanna try this again with open-compiled > ?
;
; ___________________________________________________________________________
; |             |   Program       | UCILISP | INTERLISP | MACLISP |Franz/VAX|
; |-------------+-----------------+---------+-----------+---------+---------|
; |             |   TARAI-4*      |   57.0  |    26.0   |  22.8   |  73.0   |
; |             |-----------------+---------+-----------+---------+---------|
; | Interpreter | numerical SORT  |   53.9  |    63.7   |  55.0   |         |
; |             | of (1 2... 100) |         |           |         |         |
; |-------------+-----------------+---------+-----------+---------+---------|
; |             |   TARAI-4*      |    2.90 |    15.0   |   0.69  | 5.3, 4.1|**
; |             |-----------------+---------+-----------+---------+---------|
; |  Compiler   | numerical SORT  |    5.62 |    22.8   |   1.46  |         |
; |             | of (1 2... 100) |         |           |         |         |
; |-------------+-----------------+---------+-----------+---------+---------|
;
; (*) TARAI-4 is (TAK 4 2 0), where TAK is an interesting function
; defined by Mr. Ikuo Takeuchi.
;(declare (localf tak))
(declare (special count begin end))
(defun benchmark (n type)
  (setq count nil)
  (do ((x n (1- x)))
      ((zerop x))
      (setq count (cons nil count)))
  (setq begin (ptime))
  (do ((y count (cdr y)))
      ((null y))
     ; (tak 4 2 0)
     (cond ((null type) (tak 18 12 6))	; used in interlisp tests
	   (t (takf 18 12 6)))
      )
  (setq end (ptime))
  (print "begin " )(print begin)(terpr)
  (print "end ") (print end) (terpr)
  (print "runs ") (print n)(terpr)
  (print "avg ")(print (quotient (diff (car end) (car begin))
				 (times 60.0 n))) 
  (terpr))

 (defun tak (x y z)
	(cond ((>& x y)
	       (tak (tak (1- x) y z) 
		    (tak (1- y) z x)
		    (tak (1- z) x y) ))
	      (t z) ))
;(**) 5.3 with (1- x) etc [no other declarations, so greaterp is closed comp.]
;     4.1 with local function declaration (fast subroutine call)
;     times on VAX 11/780 at Berkeley
;
; What sort program was used?
;
;; VAX tests were run on a 780.



;; here it is with FUNCALL. An extra argument is passed, which also
;; costs some small amount. Note that the reference to the function-cell
;; by #'takfsub is "taken-out-of-the-loop." This may explain the Lispm result.
	
;(defun takf (x y z)
; (takfsub #'takfsub x y z))
(defun takf (x y z)
   (takfsub (getd 'takfsub) x y z))

'(defun takfsub (f x y z)
   (cond ((not (<& y x)) z)
	 (t (funcall f f (funcall f f (1- x) y z)
		     (funcall f f (1- y) z x)
		     (funcall f f (1- z) x y)))))
		     
 (defun takfsub (f x y z)
   (cond ((not (<& y x)) z)
	 (t (bcdcall f f (bcdcall f f (1- x) y z)
		     (bcdcall f f (1- y) z x)
		     (bcdcall f f (1- z) x y)))))
 
 
		     
 



