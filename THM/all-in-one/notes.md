#ALL IN ONE

```
10.10.231.77
```
>3 ports open. 21,22,80

>Anonymos Login FTP Available but nothing found.

>/wordpress directory found

>wpscan found a username "elyana"

>found another directory /hackathons

>source code shows a cipher and a potential key

>hint suggested vigenere cipher

>found pass

>logged in wordpress

>uploaded shell on index.php and got a reverse call back

>stablize the shell

>found a hint:
	"Elyana's user password is hidden in the system. Find it ;)"

>used this command to find the pass:
	find / -user elyana -type f 2>&1 | grep -v "Permission" | grep -v "No such"

>found a password.txt in "/etc/mysql/conf.d/private.txt"

>elyana's pass:
	elyana:E@syR18ght

>got root by using gtfobins "socat"

>root!