```
LOVE - 10.10.10.239
```

#Ports Open - 139,135,445,443,80,3306,5000

#Detail of Ports
>80		http
>135	msrpc
>139	netbios-ssn
>443	ssl
>445	microsoft-ds
>3306	mysql?
>5000	http

#Findings + Exploitation
>found a staging.love.htb domain
>used 'http://localhost:5000' on it and got creds for the main site
	admin:@LoveIsInTheAir!!!!
>created a msfvenom meterpreter rev shell and uploaded it to admin profile
>got a shell back
>got user.txt

>used msfconsole's local_exploit_suggester to get priv esc suggestions
>used the exploit = 'windows/local/always_install_elevated'
>got ROOT!!
>root.txt = 79282665af1bbe183c0f9109361950fd