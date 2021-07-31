# Nmap 7.91 scan initiated Sat Mar 20 07:20:31 2021 as: nmap -A -sC -p 80,22 -oA nmap.md funbox6.box
Nmap scan report for funbox6.box (192.168.10.9)
Host is up (0.00060s latency).

PORT   STATE SERVICE VERSION


22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.10 (Ubuntu Linux; protocol 2.0)
	| ssh-hostkey: 
	|   2048 0e:4f:3c:37:75:8a:a4:4d:bb:17:50:1b:ec:93:02:15 (RSA)
	|   256 d7:dc:fc:b1:76:d6:76:13:da:ea:c4:30:04:bc:da:d2 (ECDSA)
	|_  256 51:19:47:a6:29:c8:22:10:c2:73:34:ad:de:7f:57:d3 (ED25519)


80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
	|_http-generator: WordPress 5.5.1
	|_http-server-header: Apache/2.4.18 (Ubuntu)
	|_http-title: Funbox: Gamble hall &#8211; OPENED


Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Sat Mar 20 07:20:54 2021 -- 1 IP address (1 host up) scanned in 23.29 seconds
