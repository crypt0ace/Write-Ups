Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-26 13:13 EDT
Nmap scan report for 192.168.10.9
Host is up (0.0015s latency).

PORT     STATE SERVICE VERSION
22/tcp   open  ssh     OpenSSH 7.9p1 Debian 10+deb10u2 (protocol 2.0)
| ssh-hostkey: 
|   2048 de:b5:23:89:bb:9f:d4:1a:b5:04:53:d0:b7:5c:b0:3f (RSA)
|   256 16:09:14:ea:b9:fa:17:e9:45:39:5e:3b:b4:fd:11:0a (ECDSA)
|_  256 9f:66:5e:71:b9:12:5d:ed:70:5a:4f:5a:8d:0d:65:d5 (ED25519)
25/tcp   open  smtp    Postfix smtpd
|_smtp-commands: shredder.calipendu.la, PIPELINING, SIZE 10240000, VRFY, ETRN, STARTTLS, ENHANCEDSTATUSCODES, 8BITMIME, DSN, SMTPUTF8, CHUNKING, 
80/tcp   open  http    Apache httpd 2.4.38 ((Debian))
|_http-server-header: Apache/2.4.38 (Debian)
|_http-title: Site doesn't have a title (text/html; charset=UTF-8).
8080/tcp open  http    Apache httpd 2.4.38
| http-auth: 
| HTTP/1.1 401 Unauthorized\x0D
|_  Basic realm=HU?
|_http-server-header: Apache/2.4.38 (Debian)
|_http-title: 401 Unauthorized
Service Info: Hosts:  shredder.calipendu.la, 127.0.0.1; OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 66.56 seconds
