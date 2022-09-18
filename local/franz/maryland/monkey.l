;  This file contains an example of some production rules written in YAPS.
;  It solves the traditional monkey and bananas problem where the monkey
;  only climb onto boxes that he can reach the top of and where he doesn't
;  stack the boxes, but pushes them next to each other and climbs them like
;  a stair case.
;
;  To run the system, load the file (either monkey.l or .o) and then say
;  (loadfacts data) and (run).  You can say (db) to find out what is in
;  the YAPS database.
;
;				Liz Allen  10/16/82
;

(eval-when (compile) (load 'yaps))

(p take-bananas
	(goal (has monkey bananas))
	(reach monkey -r)
	(height bananas -b)
	(location monkey -x)
	(location bananas -x)
   test	(>= -r -b)
   -->	(fact has monkey bananas)
	(msg "** monkey has the bananas")
	(remove 1)
	)

(p get-to-bananas
	(goal (has monkey bananas))
	(height bananas -h)
	(location bananas -x)
   -->	(fact goal (reach monkey -h) (location monkey -x))
	)

(p can-begin-climb
	(goal (reach monkey -h) (location monkey -x))
	(size monkey -s)
	(location monkey -)
   test	(>= -s -h)
   -->	(remove 1)
	(fact goal (location monkey -x))
	)

(p can-reach
	(goal (reach monkey -h) (location monkey -x))
	(reach monkey -r)
	(location monkey -x)
   test	(>= -r -h)
   -->	(remove 1)
	)

(p climb
	(goal (reach monkey -h) (location monkey -x))
	(box -b -size)
	(reach monkey -r)
	(location -b -x)
	(location monkey -x)
	(size monkey -s)
   test	(>= -r -size)		; the monkey can reach the box
	(<= -h (+ -s -size))	; the box will put him at least as
				;	high as -h
   -->	(remove 1 3)
	(fact reach monkey ^(+ -s -size))
	)

(p find-box
	(goal (reach monkey -h) (location monkey -x))
	(box -b -size)
	(size monkey -s)
   test	(>= (+ -s -size) -h)	; must be able to make reach from box
	(< -size -h)
   -->	(fact goal (reach monkey -size) (location monkey -x))
	(fact goal (location -b -x))
	)

(p at-location
	(goal (location -obj -x))
	(location -obj -x)
   -->	(remove 1)
	)

(p move-box
	(goal (location -b -x))
	(box -b -)
	(location monkey -y)
	(location -b -y)
   test	(<> -x -y)
   -->	(remove 1 3 4)
	(fact location monkey -x)
	(fact location -b -x)
	)

(p prepare-move-box
	(goal (location -b -x))
	(box -b -)
	(location monkey -y)
	(location -b -z)
   test	(<> -x -z)
	(<> -y -z)
   -->	(fact goal (location monkey -z))
	)

(p move-monkey
	(goal (location monkey -x))
	(location monkey -y)
	(reach monkey -r)
	(size monkey -s)
   test	(<> -x -y)
   -->	(remove 1 2)
	(fact location monkey -x)
	(if (<> -r -s)
	    (remove 3)
	    (fact reach monkey -s))
	)

;
; The initial data.
;

(setq data '(
	(goal (has monkey bananas))
	(size monkey 2)
	(location monkey a)
	(location bananas b)
	(reach monkey 2)
	(height bananas 7)
	(box b1 2)
	(location b1 c)
	(box b2 4)
	(location b2 d)
	(box b3 5)
	(location b3 b)
	))
