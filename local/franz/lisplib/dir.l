;;	d i r		:: directory reader.
;;
;; This file provides the function 'dirread' which reads a directory
;; and returns a list of files in the directory.
;; In addition, files which have the form xxx.yyy are returned
;; as (xxx . yyy).
;;
(eval-when (compile eval) (or (get 'jkfmacs 'version) (load 'jkfmacs)))

(defun dirread (fn)
  (let ((por (infile fn)) (totlis))
       (skipbytes 2 por)
       (cond ((not (and (equal #/. (tyi por))
			(zerop (tyi por))))
	      (error "File is not a directory " fn)))
       (skipbytes 28 por)
       ; read each entry

       (do ((lis nil nil) (i) (v1) (v2))
	   ((eq i -1))
	   (setq v1 (tyi por) v2 (tyi por))
	   (If (not (and (zerop v1) (zerop v2)))
	       then (do ((count 1 (1+ count)))
			((eq count 15))
			(setq i (tyi por))
			(cond ((< i 1)
			       (skipbytes (- 14 count) por)
			       (return)))
			(setq lis (cons i lis)))
	       else (skipbytes 14 por))	; null entry, skip

	   (cond (lis (setq totlis (cons (splitdot (nreverse lis)) totlis)))))
       (close por)
       totlis))

(defun skipbytes (n port)
  (do ((i n (1- i)))
      ((= 0 i))
      (tyi port)))


(defun splitdot (lis)
  (do ((xx lis (cdr xx)) (prev nil xx))
      ((or (null xx) (equal #/. (car xx)))
       (cond ((or (null xx) (eq xx lis)) 
	      (cons (implode lis) nil))
	     (t (rplacd prev nil)
		(cons  (implode lis) (implode (cdr xx))))))))
