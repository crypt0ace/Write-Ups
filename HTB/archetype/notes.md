```
Archetype - 10.10.10.27
```

#Ports Open - 135,139,445,1433

#Detail of Ports
>135	msrpc
>139	netbios
>445	microsoft-ds
>1433	mysql

#Findings + Exploitation
>start w smb
>used the command no output
	smbmap -H 10.10.10.27
>used this to get shares
	smbclient -L \\\10.10.10.27
>found a backups share
>used this command to get it
	smbclient //10.10.10.27/backups
	mget *
>found user and pass for mysql
	ARCHETYPE\sql_svc:M3g4c0rp123
>