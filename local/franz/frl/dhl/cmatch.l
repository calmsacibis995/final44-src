(include declar.l)

(eval-when (compile)
  (load 'dhl//rule))

;;
;;	This file was originally created by an expansion of macros on the rules
;;	in the match domain in the file dhl//rmatch.l .
;;	This version is used in the system since it is much faster.
;;	and performs the same function of the match rule-domain.
;;
;;	See dhl//rmatch.l for details of what it does.
;;
;;	modified sept 5, 1981 (dhl) to include the compare frame function
;;	being currently written in dhl//compare.l , in order to make this
;;	more like winston's matcher.  
;;
;;
(declare (localf lbind-to))

(fassert matcher
  (ako ($value (thing)))
  (percent-needed ($value (60. ))))	;; percent of slots which must
					;; match to match two frames.


;;
;;	initial simple way to compare frames, just compare,
;;	and count the differences.
;;

(declare (localf countvalues))

(defun countvalues (frame)
  (cond ((null frame) 0)
	(t (let ((s (fslots frame)))
		(do ((x s (cdr x))
		     (count 0))
		    ((null x) count)
		    (setq count 
			  (+ count (length (fvalues-only frame 
							 (car x))))))))))

(defun match-frames (frame1 frame2)
  (let ((x (compare frame1 frame2)))
       (cond ((null x) nil)
	     (t (lessp 
		 (float (// (* 100 (- (countvalues x) 3))
			    ;dont count ako of diff. and frame slot of diff.
			    (+ (countvalues frame1) 
			       (countvalues frame2))))
		 (float (fvalue-only 'matcher 'percent-needed)))))))

(defun match-frames-1 (frame1 frame2 compare-frame)
  (let ((x (frame-compare frame1 frame2 (newframe 'difference)
			  compare-frame)))
       (cond ((null x) nil)
	     (t (lessp 
		 (float (// (* 100 (1- (countvalues x)))
			    ;dont count ako of diff.
			    (+ (countvalues frame1) 
			       (countvalues frame2))))
		 (float (fvalue-only 'matcher 'percent-needed)))))))

(defun bind-to (a bindings)
  (cond (bindings (lbind-to a bindings))
	(a)))

(defun lbind-to (a bindings)
  (cond ((atom a) a)
	((is-var a)
	 (let ((x (assq (cdr a) bindings)))
	      (cond (x (cdr x))
		    (a))))
	((cons (lbind-to (car a) bindings)
	       (lbind-to (cdr a) bindings)))))

(defun match (:match1 :match2 :bindings)
  (let ((result) (ruledomain 'match)
	(rulequeue nil)
	(:goal (list :match1 :match2 :bindings)))
       (cond ((equal :match1 :match2)
	      (or :bindings (list nil)))
	     ((is-var :match2)
	      (append (list (cons (cdr :match2) :match1))
		      :bindings))
	     ;; ;	if two atoms dont match, try matching their frames.
	     ;; ;
	     ;; ((and (atom :match1) (atom :match2)
		   ;; (frame/? :match1) (frame/? :match2)
		   ;; (match-frames :match1 :match2))
	      ;; :bindings)
	     ((and (not (atom :match1))
		   (not (atom :match2))
		   (not (is-var :match1))
		   (not (is-var :match2)))
	      (let ((b1 (match (car :match1)
			       (bind-to (car :match2)
					:bindings)
			       :bindings)))
		   (cond (b1 (match (cdr :match1)
				    (bind-to (cdr :match2) b1)
				    b1))))))))
