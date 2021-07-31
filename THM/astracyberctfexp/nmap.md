Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-30 03:50 EDT
Nmap scan report for 10.10.59.236 (10.10.59.236)
Host is up (0.68s latency).

PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.10 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 a0:b1:e6:54:33:68:65:3b:30:b6:b8:1b:eb:99:11:4e (RSA)
|   256 1b:5f:27:d3:d0:19:ee:bb:d7:6b:e8:d4:6a:5e:2b:33 (ECDSA)
|_  256 b5:dc:5d:d3:cb:50:27:8d:fa:c1:fc:e2:6b:4c:57:ee (ED25519)
80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
| http-robots.txt: 1 disallowed entry 
|_/*.txt.txt.bak
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: zerocool's site
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
