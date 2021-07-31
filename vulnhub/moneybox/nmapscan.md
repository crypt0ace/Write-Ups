Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-06 09:39 EST
NSE: Loaded 153 scripts for scanning.
NSE: Script Pre-scanning.
NSE: Starting runlevel 1 (of 3) scan.
Initiating NSE at 09:39
Completed NSE at 09:39, 0.00s elapsed
NSE: Starting runlevel 2 (of 3) scan.
Initiating NSE at 09:39
Completed NSE at 09:39, 0.00s elapsed
NSE: Starting runlevel 3 (of 3) scan.
Initiating NSE at 09:39
Completed NSE at 09:39, 0.00s elapsed
Initiating Ping Scan at 09:39
Scanning 192.168.43.80 [2 ports]
Completed Ping Scan at 09:39, 0.00s elapsed (1 total hosts)
Initiating Parallel DNS resolution of 1 host. at 09:39
Completed Parallel DNS resolution of 1 host. at 09:39, 0.01s elapsed
Initiating Connect Scan at 09:39
Scanning MoneyBox (192.168.43.80) [65535 ports]
Discovered open port 22/tcp on 192.168.43.80
Discovered open port 80/tcp on 192.168.43.80
Discovered open port 21/tcp on 192.168.43.80
Completed Connect Scan at 09:39, 11.58s elapsed (65535 total ports)
Initiating Service scan at 09:39
Scanning 3 services on MoneyBox (192.168.43.80)
Completed Service scan at 09:39, 6.09s elapsed (3 services on 1 host)
NSE: Script scanning 192.168.43.80.
NSE: Starting runlevel 1 (of 3) scan.
Initiating NSE at 09:39
NSE: [ftp-bounce 192.168.43.80:21] PORT response: 500 Illegal PORT command.
Completed NSE at 09:40, 2.33s elapsed
NSE: Starting runlevel 2 (of 3) scan.
Initiating NSE at 09:40
Completed NSE at 09:40, 0.03s elapsed
NSE: Starting runlevel 3 (of 3) scan.
Initiating NSE at 09:40
Completed NSE at 09:40, 0.00s elapsed
Nmap scan report for MoneyBox (192.168.43.80)
Host is up, received syn-ack (0.00086s latency).
Scanned at 2021-03-06 09:39:40 EST for 20s
Not shown: 65532 closed ports
Reason: 65532 conn-refused
PORT   STATE SERVICE REASON  VERSION
21/tcp open  ftp     syn-ack vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_-rw-r--r--    1 0        0         1093656 Feb 26 08:48 trytofind.jpg
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to ::ffff:192.168.43.242
|      Logged in as ftp
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      At session startup, client count was 2
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
22/tcp open  ssh     syn-ack OpenSSH 7.9p1 Debian 10+deb10u2 (protocol 2.0)
| ssh-hostkey: 
|   2048 1e:30:ce:72:81:e0:a2:3d:5c:28:88:8b:12:ac:fa:ac (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCWBZjFZOMKU5jDBL6SwW+89IV0wojGRFPnrSIyxVOp/N7sNSln6NttNOQu1gsC4Sp7WziJ+hL5Map7t7YWJ9Rj9lvcaQU48aTtTzEsL5T991Wm3ZNvZjS0yhSL9Scf6VGxoO0EGqV+z3Z1OMKU609bm8PLoNaxfNXl2zDRdyrAN3VBT4jp8zlgfaT0W4kKQJ9u77IiHXBOU+6JrBg1b4F9x/wYT6zXxtGjH3tJTF8g4E6Da2eHOWsq3ERd40M+Oi1v4Du3+bQRd3Z4KVDOQ1utmdyFI+HcrGxjIPqqRAP0h2PLLm4qh/QZBvPO8cAPUdduLLeqmFGn/qg/FP08nBgZ
|   256 01:9d:fa:fb:f2:06:37:c0:12:fc:01:8b:24:8f:53:ae (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBC8xP+l2BvuK5pg2bEpcDV1GAoAI3kIpMznpUyfOJS29SF9N2XyYV1eEcvf0O8exXyxCs+RjVbk+8cxBs8K36CU=
|   256 2f:34:b3:d0:74:b4:7f:8d:17:d2:37:b1:2e:32:f7:eb (ED25519)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIJ92TDnimudy2EtcS6I1ja1fGn+OBm3z2/8rxwcZknEH
80/tcp open  http    syn-ack Apache httpd 2.4.38 ((Debian))
| http-methods: 
|_  Supported Methods: GET POST OPTIONS HEAD
|_http-server-header: Apache/2.4.38 (Debian)
|_http-title: MoneyBox
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 3) scan.
Initiating NSE at 09:40
Completed NSE at 09:40, 0.00s elapsed
NSE: Starting runlevel 2 (of 3) scan.
Initiating NSE at 09:40
Completed NSE at 09:40, 0.00s elapsed
NSE: Starting runlevel 3 (of 3) scan.
Initiating NSE at 09:40
Completed NSE at 09:40, 0.00s elapsed
Read data files from: /usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 21.91 seconds
