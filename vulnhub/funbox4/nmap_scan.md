# Nmap 7.91 scan initiated Thu Feb 18 08:03:13 2021 as: nmap -sV -A -p- -oN nmap_scan.md 192.168.43.227
Nmap scan report for funbox4 (192.168.43.227)
Host is up (0.0011s latency).
Not shown: 65531 closed ports
PORT    STATE SERVICE VERSION
22/tcp  open  ssh     OpenSSH 7.2p2 Ubuntu 4 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 f6:b3:8f:f1:e3:b7:6c:18:ee:31:22:d3:d4:c9:5f:e6 (RSA)
|   256 45:c2:16:fc:3e:a9:fc:32:fc:36:fb:d7:ce:4f:2b:fe (ECDSA)
|_  256 4f:f8:46:72:22:9f:d3:10:51:9c:49:e0:76:5f:25:33 (ED25519)
80/tcp  open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Apache2 Ubuntu Default Page: It works
110/tcp open  pop3    Dovecot pop3d
|_pop3-capabilities: TOP CAPA SASL AUTH-RESP-CODE RESP-CODES UIDL PIPELINING
143/tcp open  imap    Dovecot imapd
|_imap-capabilities: ID LOGIN-REFERRALS LITERAL+ IMAP4rev1 OK more have capabilities SASL-IR Pre-login listed post-login LOGINDISABLEDA0001 IDLE ENABLE
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Thu Feb 18 08:03:37 2021 -- 1 IP address (1 host up) scanned in 23.32 seconds
