;;;
;;;	Blit/etty function key interpreter
;;;
(defun
    (Blit-pad c
    (setq c (get-tty-character))
	    (if
		    (= c 'A') (prefix-argument-loop
		    		(previous-line))
		    (= c 'B') (prefix-argument-loop
				(next-line))
		    (= c 'C') (prefix-argument-loop
				(backward-character))
		    (= c 'D') (prefix-argument-loop
				(forward-character))
		    (= c 'E') (prefix-argument-loop
				(backward-word))
		    (= c 'F') (prefix-argument-loop
				(progn (scroll-one-line-down)
					(beginning-of-window)
					(beginning-of-line)))
		    (= c 'G') (prefix-argument-loop
				(progn (scroll-one-line-up)
					(end-of-window)
					(beginning-of-line)))
		    (= c 'H') (prefix-argument-loop
				(forward-word))
		    (message "Blit Cursor Pad Key Undefined.")
		)
	)
)
(bind-to-key "Blit-pad" "^XO")
