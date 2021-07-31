```
Vulnversity - 10.10.150.99
```

#Ports Open - 21,22,139,445,3128,3333

#Detail of Ports
>21		ftp
>22		ssh
>139	smb
>445	smb
>3128	squid proxy
>3333	http

#Findings + Exploitation
>gobuster found a internal directory
>upload form found
>accepts .phtml
>uploaded webshell
>got a shell back

>found /bin/systemctl SUID/SGID perms
>exploit using GTFOBins
>got ROOT!!!