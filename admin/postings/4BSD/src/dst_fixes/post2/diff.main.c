*** /nbsd/usr/src/usr.lib/sendmail/src/main.c	Thu Jan 30 11:03:53 1986
--- main.c	Tue Mar 24 15:30:51 1987
***************
*** 132,137 ****
--- 132,140 ----
  	}
  	reenter = TRUE;
  
+ 	/* Enforce use of local time */
+ 	unsetenv("TZ");
+   
  	/*
  	**  Be sure we have enough file descriptors.
  	*/
