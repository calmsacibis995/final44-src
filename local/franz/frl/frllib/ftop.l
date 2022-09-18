(include ldeclar.l)

;;
;;	The main directory where the frl source and objects are
;;	kept should be the value of frl-main-dir.
;;
  
;; (defvar frl-main-dir '//u0//csam//steve//rosenberg)
(declare (special frl-main-dir))

(process |//bin//csh -c 'rm -f //tmp//frl.dir;pwd /| sed "s//\////\//\////g" > //tmp//frl.dir'|)
(let ((frl-dir-file (infile '|//tmp//frl.dir|)))
  (setq frl-main-dir (read frl-dir-file))
  (close frl-dir-file)
  (process |rm -f //tmp//frl.dir|))

(declare (special frl-title franz-not-virgin user-top-level 
		  frl-top-level-init top-level franz-top-level))

(setq frl-title (concat "FRL " (status ctime)))

(defun frl-top-level-init ()
  (prog (initfile initport inifile)
	(princ frl-title)
	(putd 'top-level (getd 'franz-top-level))
	
	; set the load search path to include frl-main-dir for autoloading 
	
	(apply 'sstatus `(load-search-path ,(append1 (status load-search-path)
						     frl-main-dir)))
	
	(terpri)
	;(cond ((probef (setq inifile (concat frl-main-dir "//frlrc.l")))
	       ;(errset (load inifile))))
	(cond ((setq initport (errset 
			       (infile (setq initfile 
					     (concat (getenv '|HOME|) '|//.frlrc|))) 
			       nil))
	       (close (car initport))
	       (cond ((null (errset (load initfile))) 
		      (patom '| Error in .frlrc file |)
		      (terpri)))))
	))

(defun addtosearchlist (val)
  (apply 'sstatus (cons 'load-search-path
			(ncons (append (status load-search-path) 
				       (ncons val)))))
  (status load-search-path))


;;--- find-filename
;; arg: a symbol or string
;; we see if that file exists in any of the directories in the
;; load-search-path.  If it is found, the  full path name is returned
;; This causes a bit of a problem for the file name nil since we
;; we return nil if the file can't be found.

(defun find-filename (name)
  (let ((path (status load-search-path)))
       (do ((ll path (cdr ll))
	    (newname))
	   ((null ll) nil)
	   (cond ((probef (setq newname (cond ((eq '|.| (car ll)) name)
					      (t (concat (car ll) "//" name))))) 
		  (return newname))))))

(sstatus ignoreeof nil)
(putd 'top-level (getd 'frl-top-level-init))
(setq franz-not-virgin nil)
