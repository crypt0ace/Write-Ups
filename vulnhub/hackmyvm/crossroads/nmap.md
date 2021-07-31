Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-22 03:36 EDT
Nmap scan report for funbox6.box (192.168.10.9)
Host is up (0.00060s latency).

PORT    STATE SERVICE     VERSION
80/tcp  open  http        Apache httpd 2.4.38 ((Debian))
| http-robots.txt: 1 disallowed entry 
|_/crossroads.png
|_http-server-header: Apache/2.4.38 (Debian)
|_http-title: 12 Step Treatment Center | Crossroads Centre Antigua
139/tcp open  netbios-ssn Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
445/tcp open  netbios-ssn Samba smbd 4.9.5-Debian (workgroup: WORKGROUP)
Service Info: Host: CROSSROADS

Host script results:
|_clock-skew: mean: 1h40m02s, deviation: 2h53m12s, median: 2s
|_nbstat: NetBIOS name: CROSSROADS, NetBIOS user: <unknown>, NetBIOS MAC: <unknown> (unknown)
| smb-os-discovery: 
|   OS: Windows 6.1 (Samba 4.9.5-Debian)
|   Computer name: crossroads
|   NetBIOS computer name: CROSSROADS\x00
|   Domain name: \x00
|   FQDN: crossroads
|_  System time: 2021-03-22T02:36:29-05:00
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)
| smb2-security-mode: 
|   2.02: 
|_    Message signing enabled but not required
| smb2-time: 
|   date: 2021-03-22T07:36:29
|_  start_date: N/A

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 14.06 seconds
