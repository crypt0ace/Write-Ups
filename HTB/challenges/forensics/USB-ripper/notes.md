```
USB Ripper - Forensics
```

>found a way to track USB events using USBrip
>used the command
	sudo usbrip events violations ./auth.json -f ./syslog
>found one violation
>a MD5 hash was found in the Serial Number coloumn
	71DF5A33EFFDEA5B1882C9FBDC1240C6
>cracked it using crackstation.net
	mychemicalromance
>flag.txt
	HTB	{mychemicalromance}