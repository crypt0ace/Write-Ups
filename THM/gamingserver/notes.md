#found possible username:
	john

#found the uploads folder from directory scan and in robots.txt

#found a dictionary file in the uploads folder

#used it to ssh brute force, no luck

#found a secret directory

#found the id_rsa key

#was password protected so used ssh2john with the wordlist found in uploads folder

#got the pass
	letmein

#used it to get ssh

#found the lxd vuln
	Ubuntu 18.04 - 'lxd' Privilege Escalation

#got root