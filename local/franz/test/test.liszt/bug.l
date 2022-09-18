(defun test nil (prog nil (catch (return) tag)))

(defun test2 nil (prog nil (catch (go a) tag) a (print 'hi)))

(defun etest2 nil (prog nil (errset (go a)) a (print 'hi)))

(defun etest nil (prog nil (errset (return))))
