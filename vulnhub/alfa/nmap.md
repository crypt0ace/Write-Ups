Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-24 13:47 EDT
Nmap scan report for box.box (192.168.10.9)
Host is up (0.00067s latency).

PORT      STATE SERVICE     VERSION
21/tcp    open  ftp         vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_drwxr-xr-x    2 0        0            4096 Dec 17 12:02 thomas
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to ::ffff:192.168.10.10
|      Logged in as ftp
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      At session startup, client count was 2
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
80/tcp    open  http        Apache httpd 2.4.38 ((Debian))
|_http-server-header: Apache/2.4.38 (Debian)
|_http-title: Alfa IT Solutions
139/tcp   open  netbios-ssn Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
445/tcp   open  netbios-ssn Samba smbd 4.9.5-Debian (workgroup: WORKGROUP)
65111/tcp open  ssh         OpenSSH 7.9p1 Debian 10+deb10u2 (protocol 2.0)
| ssh-hostkey: 
|   2048 ad:3e:8d:45:48:b1:63:88:63:47:64:e5:62:28:6d:02 (RSA)
|   256 1d:b3:0c:ca:5f:22:a4:17:d6:61:b5:f7:2c:50:e9:4c (ECDSA)
|_  256 42:15:88:48:17:42:69:9b:b6:e1:4e:3e:81:0b:68:0c (ED25519)
Service Info: Host: ALFA; OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

Host script results:
|_clock-skew: mean: -19m59s, deviation: 34m37s, median: 0s
|_nbstat: NetBIOS name: ALFA, NetBIOS user: <unknown>, NetBIOS MAC: <unknown> (unknown)
| smb-os-discovery: 
|   OS: Windows 6.1 (Samba 4.9.5-Debian)
|   Computer name: alfa
|   NetBIOS computer name: ALFA\x00
|   Domain name: \x00
|   FQDN: alfa
|_  System time: 2021-03-24T18:48:06+01:00
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)
| smb2-security-mode: 
|   2.02: 
|_    Message signing enabled but not required
| smb2-time: 
|   date: 2021-03-24T17:48:05
|_  start_date: N/A

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 15.56 seconds
