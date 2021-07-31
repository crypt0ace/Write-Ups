```
Legacy - 10.10.10.4
```

#Ports Open - 139,445

#Detail of Ports
>139	netbios
>445	microsoft ds

#Findings + Exploitaion
>found "Windows XP microsoft-ds" running on port 445
>metasploit has a module for it
>used the exploit
	ms08-067
>got a meterpreter shell
>used 'getsystem' to get root
>ROOT!!!