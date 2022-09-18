(defun mydate nil
   (patom "The date is ")
   (patom (status ctime))
   (terpr)
   (exit 0))
(setq user-top-level 'mydate)
