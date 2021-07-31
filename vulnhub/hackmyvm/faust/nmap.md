Starting Nmap 7.91 ( https://nmap.org ) at 2021-04-08 06:51 EDT
Nmap scan report for debian (192.168.43.254)
Host is up (0.00051s latency).

PORT     STATE SERVICE VERSION
22/tcp   open  ssh     OpenSSH 7.9p1 Debian 10+deb10u2 (protocol 2.0)
| ssh-hostkey: 
|   2048 54:0a:75:c5:26:56:f5:b0:5f:6d:e1:e0:77:15:c7:0d (RSA)
|   256 0b:d7:89:52:2d:13:16:cb:74:96:f5:5f:dd:3e:52:8e (ECDSA)
|_  256 5a:90:0c:f5:2b:7f:ba:1c:83:02:4d:e7:a2:a2:1d:5b (ED25519)
80/tcp   open  http    Apache httpd 2.4.38 ((Debian))
|_http-generator: CMS Made Simple - Copyright (C) 2004-2021. All rights reserved.
|_http-server-header: Apache/2.4.38 (Debian)
|_http-title: Home - cool_cms
6660/tcp open  unknown
| fingerprint-strings: 
|   NULL, Socks5: 
|     MESSAGE FOR WWW-DATA:
|     [31m www-data I offer you a dilemma: if you agree to destroy all your stupid work, then you have a reward in my house...
|_    Paul
1 service unrecognized despite returning data. If you know the service/version, please submit the following fingerprint at https://nmap.org/cgi-bin/submit.cgi?new-service :
SF-Port6660-TCP:V=7.91%I=7%D=4/8%Time=606EE04A%P=x86_64-pc-linux-gnu%r(NUL
SF:L,A5,"\n\n\x20\x20\x20MESSAGE\x20FOR\x20WWW-DATA:\n\n\x20\x1b\[31m\x20\
SF:x20www-data\x20I\x20offer\x20you\x20a\x20dilemma:\x20if\x20you\x20agree
SF:\x20to\x20destroy\x20all\x20your\x20stupid\x20work,\x20then\x20you\x20h
SF:ave\x20a\x20reward\x20in\x20my\x20house\.\.\.\n\x20\x20\x20Paul\x20\x1b
SF:\[0m\n")%r(Socks5,A5,"\n\n\x20\x20\x20MESSAGE\x20FOR\x20WWW-DATA:\n\n\x
SF:20\x1b\[31m\x20\x20www-data\x20I\x20offer\x20you\x20a\x20dilemma:\x20if
SF:\x20you\x20agree\x20to\x20destroy\x20all\x20your\x20stupid\x20work,\x20
SF:then\x20you\x20have\x20a\x20reward\x20in\x20my\x20house\.\.\.\n\x20\x20
SF:\x20Paul\x20\x1b\[0m\n");
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 14.68 seconds