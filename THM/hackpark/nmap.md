Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-29 03:43 EDT
Nmap scan report for hackpark.thm (10.10.176.54)
Host is up (0.49s latency).

PORT     STATE SERVICE            VERSION
80/tcp   open  http               Microsoft IIS httpd 8.5
| http-methods: 
|_  Potentially risky methods: TRACE
| http-robots.txt: 6 disallowed entries 
| /Account/*.* /search /search.aspx /error404.aspx 
|_/archive /archive.aspx
|_http-server-header: Microsoft-IIS/8.5
|_http-title: hackpark | hackpark amusements
3389/tcp open  ssl/ms-wbt-server?
| ssl-cert: Subject: commonName=hackpark
| Not valid before: 2021-03-28T07:35:34
|_Not valid after:  2021-09-27T07:35:34
|_ssl-date: 2021-03-29T07:44:23+00:00; +1s from scanner time.
Service Info: OS: Windows; CPE: cpe:/o:microsoft:windows

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 27.62 seconds
                                                                