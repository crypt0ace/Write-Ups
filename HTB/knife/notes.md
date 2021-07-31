```
Knife - 10.129.136.197
```

#Ports Open - 22,80

#Detail of Ports
>22		ssh
>80		http

#Findings + Exploitation
>found it is running PHP 8.1.0-dev using nikto
>found a exploit for it
	https://github.com/flast101/php-8.1.0-dev-backdoor-rce
>used reverse shell to get in
>got james/.ssh
>added public RSA key to auth_keys
>ssh in the machine
>sudo -l shows knife vulnerable
>made a ruby file with bash in it
	echo "system("/bin/bash") >> exp.rb"
>used knife to execute it
>sudo knife exec exp.rb
>got ROOT!!!