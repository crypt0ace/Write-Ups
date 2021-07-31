52.208.113.63


PORT    STATE SERVICE  REASON  VERSION
21/tcp  open  ftp      syn-ack vsftpd 3.0.3
22/tcp  open  ssh      syn-ack OpenSSH 5.9p1 Debian 5ubuntu1.4 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 46:b2:81:be:e0:bc:a7:86:39:39:82:5b:bf:e5:65:58 (RSA)
|_ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC3op12UwFIehC/VLx5tzBbmCUO/IzJlyueCj1/qP7tq3DcrBu9iQbC1gYemElU2FhqHH2KQr9MFrWRJgU4dH0iQOFld1WU9BNjfr6VcLOI+flLQstwWf1mJXEOdDjA98Cx+blYWG62qwXLiW+aq2jLfIZkVjJlp7OueNeocxE0P7ynTqJIadMfeNqNZ1Jc+s7aCBSg0NRSh0FsABAG+BSFhybnKXtApc+RG0QQ3vFpnU0k0PVZvg/qU/Eb6Oimm67d8hjclPbPpQoyvsdyOQG7yVS9eIglTr00ddw2Jn8wrapOa4TcBJGu9cgSgITHR8+htJ1LLj3EtsmJ0pErEv0B
80/tcp  open  http     syn-ack Apache httpd 2.4.29
| http-methods: 
|_  Supported Methods: GET HEAD POST OPTIONS
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: Did not follow redirect to https://robyns-petshop.thm/
443/tcp open  ssl/http syn-ack Apache httpd 2.4.29 ((Ubuntu))
| http-methods: 
|_  Supported Methods: GET HEAD POST OPTIONS
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: Robyn&#039;s Pet Shop
| ssl-cert: Subject: commonName=robyns-petshop.thm/organizationName=Robyns Petshop/stateOrProvinceName=South West/countryName=GB/emailAddress=robyn@robyns-petshop.thm/localityName=Bristol
| Subject Alternative Name: DNS:robyns-petshop.thm, DNS:monitorr.robyns-petshop.thm, DNS:beta.robyns-petshop.thm, DNS:dev.robyns-petshop.thm
| Issuer: commonName=robyns-petshop.thm/organizationName=Robyns Petshop/stateOrProvinceName=South West/countryName=GB/emailAddress=robyn@robyns-petshop.thm/localityName=Bristol
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2021-04-26T12:49:49
| Not valid after:  2022-04-26T12:49:49
| MD5:   5dce ed25 f487 d0f2 f494 459a 07f5 22a4
| SHA-1: 6b75 2c20 4ce7 d0b4 eceb 6006 2c23 ffe0 5fbd ab8e
| -----BEGIN CERTIFICATE-----
| MIIEPzCCAyegAwIBAgIUR0QJModFxIvHdht54RkUHiGI/DAwDQYJKoZIhvcNAQEL
| BQAwgZMxCzAJBgNVBAYTAkdCMRMwEQYDVQQIDApTb3V0aCBXZXN0MRAwDgYDVQQH
| DAdCcmlzdG9sMRcwFQYDVQQKDA5Sb2J5bnMgUGV0c2hvcDEbMBkGA1UEAwwScm9i
| eW5zLXBldHNob3AudGhtMScwJQYJKoZIhvcNAQkBFhhyb2J5bkByb2J5bnMtcGV0
| c2hvcC50aG0wHhcNMjEwNDI2MTI0OTQ5WhcNMjIwNDI2MTI0OTQ5WjCBkzELMAkG
| A1UEBhMCR0IxEzARBgNVBAgMClNvdXRoIFdlc3QxEDAOBgNVBAcMB0JyaXN0b2wx
| FzAVBgNVBAoMDlJvYnlucyBQZXRzaG9wMRswGQYDVQQDDBJyb2J5bnMtcGV0c2hv
| cC50aG0xJzAlBgkqhkiG9w0BCQEWGHJvYnluQHJvYnlucy1wZXRzaG9wLnRobTCC
| ASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKcG1eUxXlKYX81bWa174IxA
| 5hOccDGJfGcn3VXTCOF4FUKIlkdi6nRSN2xP9+ArZeasNwptDuGXfq0VXd56iCID
| e/tHRkf/GSCxvinMDMlOnQjlHAWHD2w41MvqzeHVccAjc+Wqt3ZrYvzB2EKyySwB
| V3tsNjsX2zXLsRJ4HlV0b/2S/4NvxYQNePbZJXgQ+dWxaf2msew0TDix6mdSoU+B
| Q2AJsAWeAaOMcGD9XuLnr5DzCAnv++3ita0EPa3AfVhul2TkY6EKqCNgjURkvq51
| HU2VYzJsdHz7ljMuuAwHeWhvfyLAMo2uv3++iEj/wP6T6mYtUEK72GJT2aXUxYEC
| AwEAAaOBiDCBhTAJBgNVHRMEAjAAMAsGA1UdDwQEAwIF4DBrBgNVHREEZDBighJy
| b2J5bnMtcGV0c2hvcC50aG2CG21vbml0b3JyLnJvYnlucy1wZXRzaG9wLnRobYIX
| YmV0YS5yb2J5bnMtcGV0c2hvcC50aG2CFmRldi5yb2J5bnMtcGV0c2hvcC50aG0w
| DQYJKoZIhvcNAQELBQADggEBAEgV1+l7bsocrxJclJr5no2vtRROmfYuwiJuEtJg
| TbnHEQ6IVzwsd4nou7p9hNXsqBZ4xYpAma/eAbUwr2ncQUAlb5CAVyB8SZLCtNu7
| CZSIrek3Ze6ga7yKfydyYzIZWZWfu73j1bg7HOSkUClu8ha5KNbrTujXH54m6czd
| 9cUCLl4y+mojg7SLhsabRd/ux9tBoZvYpPz16VrGbdGo4FnOks3m5TkvUIIjECmr
| QKRkpnqNxxSnwdfpENHtQemRFDgSBaJhdZWhdwA/Ey+GKFYkajX6eTIeES+k5DAj
| h5tPAp4F0JuZW1VRNgR7Khyx+LUpePf58/4koF5oUEv52gU=
|_-----END CERTIFICATE-----
|_ssl-date: TLS randomness does not represent time
| tls-alpn: 
|_  http/1.1
Service Info: Host: robyns-petshop.thm; OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

NSE: Script Post-scanning.
NSE: Starting runlevel 1 (of 3) scan.
Initiating NSE at 18:02
Completed NSE at 18:02, 0.00s elapsed
NSE: Starting runlevel 2 (of 3) scan.
Initiating NSE at 18:02
Completed NSE at 18:02, 0.00s elapsed
NSE: Starting runlevel 3 (of 3) scan.
Initiating NSE at 18:02
Completed NSE at 18:02, 0.00s elapsed
Read data files from: /usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 70.75 seconds